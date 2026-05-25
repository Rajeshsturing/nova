/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CBRSet - backup/restore item description (file group, database,etc.)
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "FileSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBRSet

IMPLEMENT_DYNCREATE(CBRSet, CCmdTarget)

CBRSet::CBRSet() :
	m_bRelative(false),
	m_bResurse(false),
	m_BRSetType(BRSET_INVALID)

{
	EnableAutomation();
	AfxOleLockApp();
}

CBRSet::~CBRSet()
{
	AfxOleUnlockApp();
}


void CBRSet::OnFinalRelease()
{
	CCmdTargetInterface::OnFinalRelease();
}

CString CBRSet::GetDescription() const
{
	CString oResultString;
	switch(GetType())
	{
		case BRSET_FILEGROUP:
			oResultString.Format("%d\t%s\t%s\t%s\t%d\t%d\t",long(BRSET_FILEGROUP),
				m_oNameString,m_oPathString,m_oMaskString,long(m_bResurse),long(m_bRelative));
		break;
		case BRSET_DATABASE_MSSQL:
			oResultString.Format("%d\t%s\t%s\t%s\t%s\t%s\t",long(BRSET_DATABASE_MSSQL),
				m_oNameString,m_oServerString,m_oDBString,m_oUserString,m_oPasswordString);
		break;
		case BRSET_NAVOBRMAN:
		{
			oResultString.Format("%d\t%s\t%s\t",long(BRSET_NAVOBRMAN),
				m_oNameString,m_oRemoteServerString);
			for(long iter = 0; iter <= m_oBRSetArray.GetUpperBound(); iter++)
			{
				oResultString += "[" + m_oBRSetArray[iter]->GetDescription() + "]";
			}
			oResultString += "\t";
		}
		break;
		default:
			ASSERT(false); //unknown type
	}
	return oResultString;
}

LPCTSTR CBRSet::__ReadDescription(LPCTSTR lpDescription)
{
	//read type
	ASSERT(IsDigit(*lpDescription));
	m_BRSetType = BRSetType(*lpDescription - '0');
	lpDescription++;
	ASSERT(*lpDescription == '\t');
	lpDescription++;
	LPCTSTR lpTmp = _tcschr(lpDescription,'\t');
	ASSERT(lpTmp);
	m_oNameString = CString(lpDescription,lpTmp-lpDescription);
	lpDescription = lpTmp;
	ASSERT(*lpDescription == '\t');

	switch(GetType())
	{
	case BRSET_FILEGROUP:		//type<tab>mask<tab>recurse<tab>relative<tab>
	{
		lpDescription++;
		LPCTSTR lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oPathString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;
		
		lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oMaskString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;
		ASSERT(IsDigit(*lpDescription));
		m_bResurse = (*lpDescription != '0');
		lpDescription++;
		ASSERT(*lpDescription == '\t');
		lpDescription++;
		ASSERT(IsDigit(*lpDescription));
		m_bRelative = (*lpDescription != '0');
		lpDescription++;
		ASSERT(*lpDescription == '\t');
		lpDescription++;
	}
	break;
	case BRSET_DATABASE_MSSQL:
	{
		lpDescription++;
		LPCTSTR lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oServerString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;

		lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oDBString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;

		lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oUserString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;

		lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oPasswordString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;
	}
	break;
	case BRSET_NAVOBRMAN:	//type[subsetdescription]<tab>
	{
		lpDescription++;
		LPCTSTR lpTmp = _tcschr(lpDescription,'\t');
		ASSERT(lpTmp);
		m_oRemoteServerString = CString(lpDescription,lpTmp-lpDescription);
		lpDescription = ++lpTmp;

		while(*lpDescription == '[')
		{
			lpDescription++;
			SCP<CBRSet> poSubBRSetSP = NewSCP(new CBRSet());
			lpDescription = poSubBRSetSP->__ReadDescription(lpDescription);
			ASSERT(*lpDescription == ']');
			m_oBRSetArray.Add( poSubBRSetSP );
			lpDescription++;
		}
		ASSERT(*lpDescription == '\t');
		lpDescription++;
	}
	break;
	default:
		ASSERT(false);
	}
	return lpDescription;
}

bool CBRSet::SetDescription(LPCTSTR lpDescription)
{
	m_oBRSetArray.RemoveAll();
	return (*__ReadDescription(lpDescription) == '\0');
}

BEGIN_MESSAGE_MAP(CBRSet, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CBRSet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBRSet, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CBRSet)
	DISP_PROPERTY_EX(CBRSet, "type", GetTypeAUTO, SetTypeAUTO, VT_I4)
	DISP_PROPERTY_EX(CBRSet, "mask", GetMaskAUTO, SetMaskAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "recurse", GetResurseAUTO, SetResurseAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CBRSet, "server", GetServerAUTO, SetServerAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "database", GetDatabaseAUTO, SetDatabaseAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "user", GetUserAUTO, SetUserAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "password", GetPasswordAUTO, SetPasswordAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "remoteserver", GetRemoteserverAUTO, SetRemoteserverAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "relative", GetRelativeAUTO, SetRelativeAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CBRSet, "path", GetPathAUTO, SetPathAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CBRSet, "name", GetNameAUTO, SetNameAUTO, VT_BSTR)
	DISP_FUNCTION(CBRSet, "addbrset", AddBRSetAUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CBRSet, "read", ReadAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CBRSet, "write", WriteAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CBRSet, "getbrset", GetBRSetAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CBRSet, "delbrset", DeleteBRSetAUTO, VT_EMPTY, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBRSet to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D9132922-B5DB-4EDF-8A81-EFB2C27ED613}
static const IID IID_IBRSet =
{ 0xd9132922, 0xb5db, 0x4edf, { 0x8a, 0x81, 0xef, 0xb2, 0xc2, 0x7e, 0xd6, 0x13 } };

BEGIN_INTERFACE_MAP(CBRSet, CCmdTarget)
	INTERFACE_PART(CBRSet, IID_IBRSet, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBRSet message handlers


long CBRSet::GetTypeAUTO() 
{
	return (long)(m_BRSetType);
}

void CBRSet::SetTypeAUTO(long nNewValue) 
{
	m_BRSetType = (BRSetType) nNewValue;
}

BSTR CBRSet::GetMaskAUTO() 
{
	return GetMask().AllocSysString();
}

void CBRSet::SetMaskAUTO(LPCTSTR lpszNewValue) 
{
	m_oMaskString = CString(lpszNewValue);
}

BOOL CBRSet::GetResurseAUTO() 
{
	return (m_bResurse == true);
}

void CBRSet::SetResurseAUTO(BOOL bNewValue) 
{
	m_bResurse = (bNewValue != FALSE);
}

BOOL CBRSet::GetRelativeAUTO()
{
	return (m_bRelative == true);
}

void CBRSet::SetRelativeAUTO(BOOL bNewValue)
{
	m_bRelative = (bNewValue != FALSE);
}

BSTR CBRSet::GetServerAUTO() 
{
	return GetServer().AllocSysString();
}

void CBRSet::SetServerAUTO(LPCTSTR lpszNewValue) 
{
	m_oServerString = CString(lpszNewValue);
}

BSTR CBRSet::GetDatabaseAUTO() 
{
	return GetDatabase().AllocSysString();
}

void CBRSet::SetDatabaseAUTO(LPCTSTR lpszNewValue) 
{
	m_oDBString = CString(lpszNewValue);
}

BSTR CBRSet::GetUserAUTO() 
{
	return m_oUserString.AllocSysString();
}

void CBRSet::SetUserAUTO(LPCTSTR lpszNewValue) 
{
	m_oUserString = CString(lpszNewValue);
}

BSTR CBRSet::GetPasswordAUTO() 
{
	return m_oPasswordString.AllocSysString();
}

void CBRSet::SetPasswordAUTO(LPCTSTR lpszNewValue) 
{
	m_oPasswordString = CString(lpszNewValue);
}

BSTR CBRSet::GetRemoteserverAUTO() 
{
	return GetRemoteServer().AllocSysString();
}

void CBRSet::SetRemoteserverAUTO(LPCTSTR lpszNewValue) 
{
	m_oRemoteServerString = CString(lpszNewValue);
}

BSTR CBRSet::GetPathAUTO() 
{
	return GetPath().AllocSysString();
}

void CBRSet::SetPathAUTO(LPCTSTR lpszNewValue) 
{
	m_oPathString = lpszNewValue;
}

BSTR CBRSet::GetNameAUTO() 
{
	return GetName().AllocSysString();
}

void CBRSet::SetNameAUTO(LPCTSTR lpszNewValue) 
{
	m_oNameString = lpszNewValue;
}

void CBRSet::AddBRSetAUTO(LPDISPATCH lpBRSetDispatch) 
{
	ALL_TRY
	{
		CCmdTarget * poCmdTarget = CCmdTarget::FromIDispatch(lpBRSetDispatch);
		ASSERT(poCmdTarget);
		CBRSet * poBRSet = dynamic_cast<CBRSet*>(poCmdTarget);
		ASSERT(poBRSet);
		m_oBRSetArray.Add( NewSCP(poBRSet,true) );
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH CBRSet::GetBRSetAUTO(long nIter) 
{
	if(nIter >= 0 && nIter <= m_oBRSetArray.GetUpperBound())
	{
		return m_oBRSetArray[nIter]->GetIDispatch(TRUE);
	}
	return NULL;
}


void CBRSet::DeleteBRSetAUTO(long nIter) 
{
	if(nIter >= 0 && nIter <= m_oBRSetArray.GetUpperBound())
	{
		m_oBRSetArray.RemoveAt(nIter);
	}
}

void CBRSet::ReadAUTO(LPCTSTR lpDescription) 
{
	SetDescription(lpDescription);
}

BSTR CBRSet::WriteAUTO() 
{
	return GetDescription().AllocSysString();
}

BEGIN_INTERFACE_MAP(CFileSetBackRestProvider, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CFileSetBackRestProvider, IID_IBackupRestore, BackupRestore)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CFileSetBackRestProvider, BackupRestore)  

bool CFileSetBackRestProvider::PopulateFileList(LPCTSTR lpDir,SCP<INotificationSink> & rpoNotificationSinkSP)
{
	bool bResult = true;
	
	for(long iter = 0; iter <= m_oMaskStringArray.GetUpperBound(); iter++)
	{
		CFileFind oFileFind;
		CString strWildcard(lpDir);
		EnsureEndingBackslash(strWildcard);
		strWildcard += m_oMaskStringArray[iter];
		
		//this directory, with mask;
		BOOL bWorking = oFileFind.FindFile(strWildcard);
		long nIter = 0;
		while (bWorking)
		{
			bWorking = oFileFind.FindNextFile();
			if (oFileFind.IsDots() || oFileFind.IsDirectory())
			{
				continue;
			}
			else
			{
				CFileStatus oFileStatus;
				CFile::GetStatus(oFileFind.GetFilePath(),oFileStatus);
				//to_do: if(oFileStatus.m_mtime > cutoffdate)
				{
					m_oFileArray.Add(oFileFind.GetFilePath());
					m_nTotalSize += oFileStatus.m_size;
				}
			}
			CString oInformationString;
			oInformationString.Format(IDS_COLLECTING_FILE,oFileFind.GetFilePath());
			if(S_OK != StdNotifyOnProgress(rpoNotificationSinkSP,IDS_COLLECTING_FILE,++nIter,-1,oInformationString))
			{
				bResult = false;
				break;
			}
		}
		oFileFind.Close();
	}
	//then subdirs
	if(m_bResurse && bResult)
	{
		CFileFind oFileFind;
		CString strWildcard = CString(lpDir);
		EnsureEndingBackslash(strWildcard);
		strWildcard +="*.*";
		BOOL bWorking = oFileFind.FindFile(strWildcard);
		while (bWorking)
		{
			bWorking = oFileFind.FindNextFile();
			if (oFileFind.IsDots())
			{
				continue;
			}
			if (oFileFind.IsDirectory())
			{
				if(!PopulateFileList(oFileFind.GetFilePath(),rpoNotificationSinkSP))
				{
					bResult = false;
					break;
				}
			}
		}
		oFileFind.Close();
	}
	return bResult;
}

STDMETHODIMP CFileSetBackRestProvider::XBackupRestore::Begin(
	IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,
	ISupplyInfo * pSupplyInfo)
{
	METHOD_PROLOGUE(CFileSetBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		SCP<INotificationSink> poNotificationSinkSP;
		poNotificationSinkSP.SafeQueryInterface(pONSinkUnknown);
		pThis->m_poSupplyInfoSP.SafeQueryInterface(pSupplyInfo);
		pThis->m_bBackup = (bBackup != '\0');
		pThis->ReadDescription(pParameters);
		if(bBackup)
		{
			if(!pThis->PopulateFileList(pThis->m_oPathString,poNotificationSinkSP))
			{
				return ERROR_CANCELLED;
			}
			pThis->m_nCurrentPos = -1;
			pThis->m_nTotalSize  = 0;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CFileSetBackRestProvider::XBackupRestore::End()
{
	METHOD_PROLOGUE(CFileSetBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		if(pThis->m_bBackup)
		{
			pThis->m_oFileArray.RemoveAll();
			pThis->m_nTotalSize  = 0;
		}
		pThis->m_poSupplyInfoSP = 0;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	
	return S_OK;
}

STDMETHODIMP CFileSetBackRestProvider::XBackupRestore::
	GetBackupStream(LPSTR * ppStreamName,LPSTR * ppStreamInfo,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CFileSetBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		//dobry zwyczaj zeruj outpointery
		*ppStreamName = NULL;
		*ppStreamInfo = NULL;
		*ppDataStream = NULL;

		if(!pThis->m_bBackup)
		{
			return E_UNEXPECTED;
		}
next_stream:
		if(++pThis->m_nCurrentPos <= pThis->m_oFileArray.GetUpperBound())
		{
			CString oFileNameString;
			if(pThis->m_bRelative)
			{
				oFileNameString = pThis->m_oFileArray[pThis->m_nCurrentPos].Mid(pThis->m_oPathString.GetLength());
			}
			else
			{
				oFileNameString = pThis->m_oFileArray[pThis->m_nCurrentPos];
			}
retry_open_stream:
			ALL_TRY
			{
				*ppDataStream = OpenFileStream_Read(pThis->m_oFileArray[pThis->m_nCurrentPos]).Detach();
			}
			ALL_CATCH(CNavoException & roNavoException)
			{
				if(SearchExceptionForErrorCode(roNavoException,ERCO_UNABLE_TO_OPEN_FILE))
				{
					CSmartOleVariant oStreamName(pThis->m_oFileArray[pThis->m_nCurrentPos]);
					CSmartOleVariant oResultSOV;
					//to_do: infotype, description
					HRESULT hr = pThis->m_poSupplyInfoSP->AskForData(ERCO_UNABLE_TO_OPEN_FILE,"",oStreamName.GetVariantRef(),&oResultSOV.GetVariantRef());
					ASSERT(hr == S_OK || hr == S_FALSE);
					ASSERT(oResultSOV.Type() == VT_I4);
					switch(oResultSOV.GetLong())
					{
					case IDRETRY:
						goto retry_open_stream;
					case IDIGNORE:
						goto next_stream;
					case IDABORT:
						return ERROR_CANCELLED;
					default:
						ASSERT(false);
					}
				}
				else
				{
					throw;
				}
			};
			*ppStreamName = (LPTSTR) ::NdrOleAllocate(oFileNameString.GetLength() + 1);
			strcpy((LPTSTR) *ppStreamName,oFileNameString);
			return S_OK;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_FALSE;
}

STDMETHODIMP CFileSetBackRestProvider::XBackupRestore::
	GetStat(long * pTotalCount,long * pTotalSize)
{
	METHOD_PROLOGUE(CFileSetBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		*pTotalCount = pThis->m_oFileArray.GetSize();
		*pTotalSize = pThis->m_nTotalSize;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CFileSetBackRestProvider::XBackupRestore::
	SetRestoreStream(LPSTR pStreamName,LPSTR pStreamInfo,IStream * pDataStream,__int64 i64Length)
{
	METHOD_PROLOGUE(CFileSetBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		if(pThis->m_bBackup)
		{
			return E_UNEXPECTED;
		}
		CString oFileNameString;
		if(pThis->m_bRelative)		//pStreamName should be only partial path
		{
			if(pThis->m_poSupplyInfoSP.PointsObject())
			{
				CSmartOleVariant oStreamName(pStreamName);
				CSmartOleVariant oResultSOV;
				//to_do: infotype, description
				HRESULT hr = pThis->m_poSupplyInfoSP->AskForData(ERCO_ASK_FOR_RELATIVE_PATH,"",oStreamName.GetVariantRef(),&oResultSOV.GetVariantRef());
				ASSERT(hr == S_OK || hr == S_FALSE);
				ASSERT(oResultSOV.Type() == VT_BSTR);
				oFileNameString = CString(oResultSOV.GetBStr());
				if(oFileNameString == "")	//answer is cancel
				{
					return ERROR_CANCELLED;
				}
				EnsureEndingBackslash(oFileNameString);
				oFileNameString += CString(pStreamName);
			}
			else
			{
				ASSERT(false);	//relative move without provider !!!
				//to_do
			}
		}
		else
		{
			oFileNameString = pStreamName;
		}
		CString oPathString;
		{
			LPCTSTR pFileName = oFileNameString;
			LPCTSTR pcLastBS = strrchr(pFileName,'\\');
			if(pcLastBS)
			{
				oPathString = CString(pFileName,pcLastBS-pFileName+1);
			}
			else
			{
				oPathString = "";
			}
		}
		if(!oPathString.IsEmpty())
		{
			NavoCreateDirectoryTree(oPathString);
		}
retry_open_stream:
		ALL_TRY
		{
			SaveStreamToFile(NewSCP(pDataStream,true),oFileNameString,false,(ULONGLONG)i64Length);
		}
		ALL_CATCH(CNavoException & roNavoException)
		{
			if(SearchExceptionForErrorCode(roNavoException,ERCO_UNABLE_TO_OPEN_FILE))
			{
					CSmartOleVariant oStreamName(pStreamName);
					CSmartOleVariant oResultSOV;
					//to_do: infotype, description
					HRESULT hr = pThis->m_poSupplyInfoSP->AskForData(ERCO_UNABLE_TO_OPEN_FILE,"",oStreamName.GetVariantRef(),&oResultSOV.GetVariantRef());
					ASSERT(hr == S_OK || hr == S_FALSE);
					ASSERT(oResultSOV.Type() == VT_I4);
					switch(oResultSOV.GetLong())
					{
					case IDRETRY:
						goto retry_open_stream;
					case IDIGNORE:
					{
						ULARGE_INTEGER ulLength;
						ulLength.QuadPart = i64Length;
						IStream_CopyTo(pDataStream,CreateTempFileStream(),ulLength);
					}
					case IDABORT:
						return ERROR_CANCELLED;
					default:
						ASSERT(false);
					}
			}
			else
			{
				throw;
			}
		};
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


