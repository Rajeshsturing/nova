/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CBRManager - backup/restore manager
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "FileSet.h"
#include "ScriptBackRestProvider.h"
#include "MSSQLBackRestProvider.h"
#include "BRManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR pcBrManSettingsRegKey = _T("\\BackupRestoreManager");
LPCTSTR pcBrManProfileRegKey = _T("\\Profile");

/////////////////////////////////////////////////////////////////////////////
// CBRManager

IMPLEMENT_DYNCREATE(CBRManager, CCmdTarget)

CBRManager::CBRManager() :
	m_eBackupRestoreState(brs_none)
{
	EnableAutomation();
	AfxOleLockApp();
}

CBRManager::~CBRManager()
{
	AfxOleUnlockApp();
}


static LPCTSTR lpcEndOfProviderMarker = "****";

BEGIN_MESSAGE_MAP(CBRManager, CCmdTargetWithErrorInfo)
	//{{AFX_MSG_MAP(CBRManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// {EC9C2A7F-5256-4824-8F5C-9A36333F06E7}
static const IID IID_IBRManager =
{ 0xec9c2a7f, 0x5256, 0x4824, { 0x8f, 0x5c, 0x9a, 0x36, 0x33, 0x3f, 0x6, 0xe7 } };

BEGIN_INTERFACE_MAP(CBRManager, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CBRManager, IID_IBackupRestore, BackupRestore)
	INTERFACE_PART(CBRManager, IID_IBackupRestoreManager, BackupRestoreManager)
	INTERFACE_PART(CBRManager, IID_IStream, Stream)
END_INTERFACE_MAP()

// {188cb159-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CBRManager, "navobrman.BRManager", 0x188cb159,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

IMPLEMENT_ARRAYENUMERATOR(SCP<CBRSet>)

DELEGATE_UNKNOWN_INTERFACE(CBRManager, BackupRestoreManager)  
DELEGATE_UNKNOWN_INTERFACE(CBRManager, BackupRestore)  
DELEGATE_UNKNOWN_INTERFACE(CBRManager, Stream)  

/////////////////////////////////////////////////////////////////////////////
// CBRManager message handlers

LPUNKNOWN CBRManager::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CArrayEnumerator< SCP<CBRSet> > > poNewArrayEnumSP = NewSCP(new CArrayEnumerator< SCP<CBRSet> >(m_oBRSetArray));
		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

LPDISPATCH CBRManager::NewBRSetAUTO() 
{
	ALL_TRY
	{
		SCP<CBRSet> poBRSetSP = NewSCP(new CBRSet);
		return poBRSetSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CBRManager::AddBRSetAUTO(LPDISPATCH lpDispatch) 
{
	ALL_TRY
	{
		CCmdTarget * poCmdTarget = CCmdTarget::FromIDispatch(lpDispatch);
		ASSERT(poCmdTarget);
		CBRSet * poBRSet = dynamic_cast<CBRSet*>(poCmdTarget);
		ASSERT(poBRSet);
		m_oBRSetArray.Add( NewSCP(poBRSet,true) );
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


HRESULT CBRManager::_PrepareBackup()
{
	long nTotal = m_oBRSetArray.GetUpperBound();
	
	ASSERT(nTotal >= 0);

	CString oInformationString;
	oInformationString.LoadString(IDS_COLLECTING_DATA);
	CString oInformationString2;
	oInformationString2.LoadString(IDS_BACKUP_FINISHED);

	m_poStdNotifyOnProgressHolderSP = NewSCP(new CStdNotifyOnProgressHolder(
				m_poNotificationSinkSP,
				oInformationString,
				oInformationString2));

	//1. create

	for(long iter = 0; iter <= nTotal; iter++)
	{
		if(NotifyOnProgress(IDS_COLLECTING_DATA,1+iter,2+nTotal+nTotal,oInformationString) != S_OK)
		{
			return ERROR_CANCELLED;
		}
		SCP<IBackupRestore> poBackupRestoreSP;
		
		//taka uproszczona wersja monikera (mog³oby byæ CLSID, do tworzenia ró¿nych
		//providerów, ale na razie nie ma tego
		switch(m_oBRSetArray[ iter ]->GetType())
		{
		case BRSET_FILEGROUP:
		{
			poBackupRestoreSP.QueryInterface(NewSCP(new CFileSetBackRestProvider()));
		}
		break;
		case BRSET_NAVOBRMAN:
		{
			CreateRemoteInstance(CLSID_NAVO2001BackupRestoreManager,m_oBRSetArray[ iter ]->GetRemoteServer(),
				&poBackupRestoreSP.GetIID(),poBackupRestoreSP);
		}
		break;
		case BRSET_DATABASE_MSSQL:
		{
			poBackupRestoreSP.QueryInterface(NewSCP(new CMSSQLBackRestProvider()));
		}
		break;
		default:
			ASSERT(false); //unknown type
		}
		ASSERT(poBackupRestoreSP.PointsObject());
		m_oProvidersArray.Add(NewSCP(new CBackupRestoreInitHolder(
			poBackupRestoreSP,m_poNotificationSinkSP,m_poSupplyInfoSP,true,
			m_oBRSetArray[iter]->GetDescription())));
		if(m_oProvidersArray[ m_oProvidersArray.GetUpperBound() ]->GetResult() == ERROR_CANCELLED)
		{
			return ERROR_CANCELLED;
		}
	}
	//2. init
	m_oHeader.m_nProvidersCount = m_oProvidersArray.GetSize();
	for(long iter = 0; iter <= m_oProvidersArray.GetUpperBound(); iter++)
	{
		if(m_oProvidersArray[ iter ]->GetResult() != S_OK)
		{
			if(m_oProvidersArray[ iter ]->GetResult() == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_oProvidersArray[ iter ]->GetPtr(),oNavoException);
				ContinueThrowNavoException(oNavoException,ERCO_BRMAN_PREPARE_BACKUP_FAILED,IDPAGE_NOTAVAILABLE);
			}
			m_oProvidersArray[ iter ]->GetPtr() = 0;
			m_oHeader.m_nProvidersCount--;
			//w nastêpnej linii okreœla siê czy musz¹ udaæ siê wszystkie BRSety,
			//czy mo¿na pomin¹æ niektóre - tutaj jest teraz tak, ¿e musz¹ udaæ siê wszystkie
			return m_oProvidersArray[ iter ]->GetResult();
		}
	}
	ASSERT(m_oProvidersArray.GetSize() == m_oBRSetArray.GetSize());
	ASSERT(m_oProvidersArray.GetSize() > 0);
	m_oReadingState.m_nCurrentProvider = -1;	//set "before first"
	return S_OK;
}

HRESULT CBRManager::_ReadBackup(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	HRESULT hr = S_OK;
	ALL_TRY
	{
		if(m_oReadingState.m_nCurrentProvider == BRMAN_NOT_INITED)
		{
			hr = _PrepareBackup();
			if(hr != S_OK)
			{
				goto cleanup;
			}
			//write header
			CStreamHolder(m_oReadingState.m_poInfoStreamSP).Write(&m_oHeader,sizeof(m_oHeader));
		}
		if(m_oReadingState.m_nCurrentProvider == BRMAN_FINISHED)
		{
			*plBytesRead = 0;
			hr = S_OK;
			goto cleanup;
		}
		long nTotal = m_oProvidersArray.GetUpperBound();
		CString oInformationString;
_read_current_stream:
		//try read from current stream
		if(m_oReadingState.m_poCurrentStreamSP.PointsObject())
		{
			ASSERT(m_oReadingState.m_nCurrentProvider <= m_oProvidersArray.GetUpperBound() && 
				m_oReadingState.m_nCurrentProvider  >= 0);
			hr = m_oReadingState.m_poCurrentStreamSP->Read(pData,lLength,plBytesRead);
			if(hr != S_OK)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_oReadingState.m_poCurrentStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,
					ERCO_BRMAN_BACKUP_FAILED,IDPAGE_NOTAVAILABLE);
			}
			//przeczyta³ coœtam - nie koniec strumienia
			m_oReadingState.m_nCurrentStreamSize += *plBytesRead;
			if(lLength == 0 || *plBytesRead != 0)
			{
				return S_OK;
			}
			
			//write stream size
			CStreamHolder(m_oReadingState.m_poInfoStreamSP).Write(&m_oReadingState.m_nCurrentStreamSize,sizeof(m_oReadingState.m_nCurrentStreamSize));
		}
_get_next_stream:
		//try get next stream from current provider
		if(m_oReadingState.m_nCurrentProvider >= 0)
		{
			ASSERT(m_oReadingState.m_nCurrentProvider <= m_oProvidersArray.GetUpperBound());
			if(m_oProvidersArray[ m_oReadingState.m_nCurrentProvider ]->GetPtr().PointsObject())
			{
				LPSTR pcTmpStreamName;
				LPSTR pcTmpStreamInfo;
				CRemoteFreeHolder oRFHName(pcTmpStreamName);
				CRemoteFreeHolder oRFHInfo(pcTmpStreamInfo);
				SCP<IStream> poStreamSP;
				HRESULT hr = m_oProvidersArray[ m_oReadingState.m_nCurrentProvider ]->GetPtr()->
					GetBackupStream(&pcTmpStreamName,&pcTmpStreamInfo,&poStreamSP.GetRawPointer());
				if(hr == S_OK)
				{
					m_oReadingState.m_oCurrentStreamNameString = pcTmpStreamName;				
					m_oReadingState.m_oCurrentStreamInfoString = pcTmpStreamInfo;
					m_oReadingState.m_poCurrentStreamSP = poStreamSP;
					m_oReadingState.m_nCurrentStreamSize = 0;
					
					CStreamHolder oInfoSH(m_oReadingState.m_poInfoStreamSP);
					oInfoSH.WritePascalString(pcTmpStreamName);
					oInfoSH.WritePascalString(pcTmpStreamInfo);
					
					oInformationString.Format(IDS_BACKUP_OF,pcTmpStreamName);
					if(NotifyOnProgress(IDS_BACKUP_OF,1+1+m_oReadingState.m_nCurrentProvider+nTotal,
						2+nTotal+nTotal,oInformationString) != S_OK)
					{
						hr = ERROR_CANCELLED;
						goto cleanup;
					}
					goto _read_current_stream;
				}
				if(hr == S_FALSE)	//end of provider's streams
				{
					CStreamHolder(m_oReadingState.m_poInfoStreamSP).WritePascalString(lpcEndOfProviderMarker);
				}
				else
				{
					if(hr == DISP_E_EXCEPTION)
					{
						CNavoException oNavoException;
						GetErrorInfoFromInterface(m_oProvidersArray[ m_oReadingState.m_nCurrentProvider ]->GetPtr(),oNavoException);
						ContinueThrowNavoException(oNavoException,
							ERCO_BRMAN_BACKUP_FAILED,IDPAGE_NOTAVAILABLE);
					}
					hr = ERROR_CANCELLED;
					goto cleanup;
				}
			}
		}
		//find next provider
		m_oReadingState.m_nCurrentProvider++;
		while (m_oReadingState.m_nCurrentProvider <= m_oProvidersArray.GetUpperBound() && 
			m_oProvidersArray[ m_oReadingState.m_nCurrentProvider ]->GetPtr().PointsNull())
		{
			m_oReadingState.m_nCurrentProvider++;
		}
		if(m_oReadingState.m_nCurrentProvider <= m_oProvidersArray.GetUpperBound())
		{
			oInformationString.LoadString(IDS_STORING_DATA);
			if(NotifyOnProgress(IDS_STORING_DATA,1+m_oReadingState.m_nCurrentProvider+nTotal,2+nTotal+nTotal,
				oInformationString) != S_OK)
			{
				hr = ERROR_CANCELLED;
				goto cleanup;
			}
			//write providers description
			CStreamHolder(m_oReadingState.m_poInfoStreamSP).WritePascalString(
				m_oBRSetArray[m_oReadingState.m_nCurrentProvider]->GetDescription());
			goto _get_next_stream;
		}
		//no more providers, no more streams, no more data
		oInformationString.LoadString(IDS_BACKUP_FINISHED);
		if(NotifyOnProgress(IDS_BACKUP_FINISHED,2+nTotal+nTotal,2+nTotal+nTotal,oInformationString) != S_OK)
		{
			hr = ERROR_CANCELLED;
			goto cleanup;
		}
		CStreamHolder(m_oReadingState.m_poInfoStreamSP).SeekToBegin();
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		GetErrorStorage() += roNavoException;
		hr = DISP_E_EXCEPTION;
	}
cleanup:
	m_poStdNotifyOnProgressHolderSP = 0;
	
	m_oReadingState.m_poCurrentStreamSP = 0;
	m_oReadingState.m_nCurrentStreamSize = 0;
	
	m_oReadingState.m_nCurrentProvider = BRMAN_FINISHED;
	m_oProvidersArray.RemoveAll();
	*plBytesRead = 0;
	m_poNotificationSinkSP = 0;
	m_poSupplyInfoSP = 0;
	m_oBRSetArray.RemoveAll();
	return hr;
}

/*
					
	hr = IStream_CopyTo_WithNotify(m_poNotificationSinkSP,poStreamSP,
				poDestinationStreamSP,pcStreamName,nStreamSize);

*/

HRESULT CBRManager::_DoRestore(SCP<IStream> & rpoSourceStreamSP,SCP<IStream> & rpoInfoStreamSP)
{
	CString oInformationString;
	oInformationString.LoadString(IDS_RESTORING_DATA);
	CString oInformationString2;
	oInformationString2.LoadString(IDS_RESTORE_FINISHED);

	HRESULT hr = S_OK;
	m_poStdNotifyOnProgressHolderSP = NewSCP(new CStdNotifyOnProgressHolder(
				m_poNotificationSinkSP,
				oInformationString,
				oInformationString2));

	try
	{
		ASSERT(rpoSourceStreamSP.PointsObject());
		ASSERT(rpoInfoStreamSP.PointsObject());
		
		
		CStreamHolder oSourceSH(rpoSourceStreamSP);
		CStreamHolder oInfoSH(rpoInfoStreamSP);
		CBRFileHeader oHeader;
		
		//check header
		if(oInfoSH.Read(&oHeader,sizeof(oHeader)) != sizeof(oHeader))
		{
			hr = E_FAIL;
			goto finish;
		}
		if(oHeader.m_marker != BRF_MARKER)
		{
			hr = E_FAIL;
			goto finish;
		}
		
		for(long iter = oHeader.m_nProvidersCount; iter > 0; iter--)
		{
			if(NotifyOnProgress(IDS_RESTORING_DATA,iter,oHeader.m_nProvidersCount,oInformationString) != S_OK)
			{
				hr = ERROR_CANCELLED;
				goto finish;
			}
			CString oProviderDescString = oInfoSH.ReadPascalString();
			SCP<CBRSet> poBRSetSP = NewSCP(new CBRSet);
			SCP<IBackupRestore> poBackupRestoreSP;
			if(!poBRSetSP->SetDescription(oProviderDescString))
			{
				hr = E_FAIL;
				goto finish;
			}
			switch(poBRSetSP->GetType())
			{
			case BRSET_FILEGROUP:
				{
					poBackupRestoreSP.QueryInterface(NewSCP(new CFileSetBackRestProvider()));
				}
				break;
			case BRSET_NAVOBRMAN:
				{
					CreateRemoteInstance(CLSID_NAVO2001BackupRestoreManager,poBRSetSP->GetRemoteServer(),
						&poBackupRestoreSP.GetIID(),poBackupRestoreSP);
				}
				break;
			case BRSET_DATABASE_MSSQL:
				{
					poBackupRestoreSP.QueryInterface(NewSCP(new CMSSQLBackRestProvider()));
				}
				break;
			default:
				ASSERT(false); //unknown type
			}
			CBackupRestoreInitHolder oBRIH(poBackupRestoreSP,
				m_poNotificationSinkSP,m_poSupplyInfoSP,false,poBRSetSP->GetDescription());
			//now perform restore
			if(oBRIH.GetResult() != S_OK)
			{
				hr = oBRIH.GetResult();
				goto finish;
			}
			for(CString oNameString = oInfoSH.ReadPascalString(); 
			oNameString != CString(lpcEndOfProviderMarker);
			oNameString = oInfoSH.ReadPascalString())
			{
				CString oInfoString = oInfoSH.ReadPascalString();
				__int64 nStreamSize;
				oInfoSH.Read(&nStreamSize,sizeof(nStreamSize));
				hr = oBRIH.GetPtr()->SetRestoreStream((LPSTR)(LPCSTR)oNameString,
					(LPSTR)(LPCSTR)oInfoString,rpoSourceStreamSP,nStreamSize);
				if(hr != S_OK)
				{
					if(hr == DISP_E_EXCEPTION)
					{
						CNavoException oNavoException;
						GetErrorInfoFromInterface(oBRIH.GetPtr(),oNavoException);
						ContinueThrowNavoException(oNavoException,
							ERCO_BRMAN_RESTORE_FAILED,IDPAGE_NOTAVAILABLE);
					}
					goto finish;
				}
				TRACE1("restored:[%s]\n",oNameString);
				
				oInformationString.Format(IDS_RESTORE_OF,oNameString);
				if(NotifyOnProgress(IDS_RESTORE_OF,iter,oHeader.m_nProvidersCount,oInformationString) != S_OK)
				{
					hr = ERROR_CANCELLED;
					goto finish;
				}
			}
		}
		if(NotifyOnProgress(IDS_RESTORE_FINISHED,1,1,oInformationString2) != S_OK)
		{
			hr = ERROR_CANCELLED;
			goto finish;
		}
	}
	catch(...)
	{
		m_oBRSetArray.RemoveAll();
		m_poStdNotifyOnProgressHolderSP = 0;
		throw;
	}
finish:
	m_oBRSetArray.RemoveAll();
	m_poStdNotifyOnProgressHolderSP = 0;
	return hr;
}

void CBRManager::_SetProperty(long nProp,const CSmartOleVariant & roSOV)
{
	if(nProp >= BRMAN_PROP_PROFILE01 && nProp <= BRMAN_PROP_PROFILE09)
	{
		CString oProfileRegKeyString = GetNAVO2001RootRegistryKeyName() + CString(pcBrManSettingsRegKey) +
			CString(pcBrManProfileRegKey);
		CString oProfileValueString;
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oProfileRegKeyString,
			Long2String(nProp-BRMAN_PROP_PROFILE01+1),CString(roSOV.GetBStr()));
		return;
	}
	ASSERT(false);	//unknown property
}

void CBRManager::_GetProperty(long nProp,CSmartOleVariant & roSOV)
{
	if(nProp >= BRMAN_PROP_PROFILE01 && nProp <= BRMAN_PROP_PROFILE09)
	{
		CString oProfileRegKeyString = GetNAVO2001RootRegistryKeyName() + CString(pcBrManSettingsRegKey) +
			CString(pcBrManProfileRegKey);
		CString oProfileValueString;
		LONG nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oProfileRegKeyString,
			Long2String(nProp-BRMAN_PROP_PROFILE01+1),oProfileValueString);
		if(nResult != ERROR_SUCCESS)
		{
			oProfileValueString = "";
		}
		roSOV = oProfileValueString;
		return;
	}
	ASSERT(false);	//unknown property
}

/// slave IBackupRestore
void CBRManager::ReadDescription(LPCSTR lpDescription)
{
	CBRSet oBRSet;
	VERIFY(oBRSet.SetDescription(lpDescription));
	ASSERT(oBRSet.GetType() == BRSET_NAVOBRMAN);
	ASSERT(m_oBRSetArray.GetSize() == 0);
	for(long iter = 0; iter <= oBRSet.GetSubSetArray().GetUpperBound(); iter++)
	{
		m_oBRSetArray.Add(oBRSet.GetSubSetArray()[iter]);
	}
}

