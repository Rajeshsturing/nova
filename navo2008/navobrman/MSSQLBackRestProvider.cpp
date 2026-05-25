/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CMSSQLBackRestProvider- backup/restore provider based for MS SQL 7.0 databases
	(via SQLDMO)
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "MSSQLBackRestProvider.h"
#include "FileSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSSQLBackRestProvider

CMSSQLBackRestProvider::CMSSQLBackRestProvider()
{
	EnableAutomation();
}

CMSSQLBackRestProvider::~CMSSQLBackRestProvider()
{
}

void CMSSQLBackRestProvider::ReadDescription(bool bBackup,LPCSTR lpDescription)
{
	m_oDescriptionString = CString(lpDescription);
	CBRSet oBRSet;
	VERIFY(oBRSet.SetDescription(lpDescription));
	ASSERT(oBRSet.GetType() == BRSET_DATABASE_MSSQL);
	m_oSQLServerString = oBRSet.GetServer();
	m_oDBNameString	   = oBRSet.GetDatabase();
	m_oUserString      = oBRSet.GetUser();
	m_oPasswordString  = oBRSet.GetPassword();
}

BEGIN_MESSAGE_MAP(CMSSQLBackRestProvider, CCmdTarget)
	//{{AFX_MSG_MAP(CMSSQLBackRestProvider)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMSSQLBackRestProvider, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CMSSQLBackRestProvider)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMSSQLBackRestProvider to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D45117A9-D2F0-4CFC-9774-E843E834FDA6}
static const IID IID_IMSSQLBackRestProvider =
{ 0xd45117a9, 0xd2f0, 0x4cfc, { 0x97, 0x74, 0xe8, 0x43, 0xe8, 0x34, 0xfd, 0xa6 } };

BEGIN_INTERFACE_MAP(CMSSQLBackRestProvider, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CMSSQLBackRestProvider, IID_IMSSQLBackRestProvider, Dispatch)
	INTERFACE_PART(CMSSQLBackRestProvider, __uuidof(SQLDMO::BackupSink), BackupSink)
	INTERFACE_PART(CMSSQLBackRestProvider, __uuidof(SQLDMO::RestoreSink), RestoreSink)
	INTERFACE_PART(CMSSQLBackRestProvider, IID_IBackupRestore, BackupRestore)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CMSSQLBackRestProvider, BackupSink)  
DELEGATE_UNKNOWN_INTERFACE(CMSSQLBackRestProvider, RestoreSink)  
DELEGATE_UNKNOWN_INTERFACE(CMSSQLBackRestProvider, BackupRestore)  

//------------------------------------------------------------------
//---------------------------- backup sink interface ---------------
//------------------------------------------------------------------

STDMETHODIMP CMSSQLBackRestProvider::XBackupSink::
	raw_PercentComplete(BSTR bstrMessage,long Percent)
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupSink)

	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLBACKUP_RUNNING,
				pThis->m_oDBNameString,
				pThis->m_oSQLServerString,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLBACKUP_RUNNING,5+Percent,105,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
				pThis->m_poBackup->Abort();
			}
		}
		TRACE1("Percent %s\n",CString(bstrMessage));
		return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}

STDMETHODIMP CMSSQLBackRestProvider::XBackupSink::
	raw_NextMedia(BSTR bstrMessage)
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupSink)

	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLBACKUP_NOSPACE,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLBACKUP_NOSPACE,1,1,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
			}
		}
		pThis->m_poBackup->Abort();
	    return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}

STDMETHODIMP CMSSQLBackRestProvider::XBackupSink::
	raw_Complete(BSTR bstrMessage )
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupSink)
	
	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLBACKUP_COMPLETE,
				pThis->m_oDBNameString,
				pThis->m_oSQLServerString,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLBACKUP_COMPLETE,1,1,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
				pThis->m_poBackup->Abort();
			}
		}
	    return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}

//------------------------------------------------------------------
//---------------------------- restore sink interface ---------------
//------------------------------------------------------------------

STDMETHODIMP CMSSQLBackRestProvider::XRestoreSink::
	raw_PercentComplete(BSTR bstrMessage,long Percent)
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, RestoreSink)

	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLRESTORE_RUNNING,
				pThis->m_oDBNameString,
				pThis->m_oSQLServerString,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLRESTORE_RUNNING,5+Percent,105,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
				pThis->m_poBackup->Abort();
			}
		}
		TRACE1("Percent %s\n",CString(bstrMessage));
		return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}

STDMETHODIMP CMSSQLBackRestProvider::XRestoreSink::
	raw_NextMedia(BSTR bstrMessage)
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, RestoreSink)

	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLRESTORE_NOSPACE,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLRESTORE_NOSPACE,1,1,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
			}
		}
		pThis->m_poBackup->Abort();
	    return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}

STDMETHODIMP CMSSQLBackRestProvider::XRestoreSink::
	raw_Complete(BSTR bstrMessage )
{
    METHOD_PROLOGUE(CMSSQLBackRestProvider, RestoreSink)
	
	ALL_TRY
	{
		if(pThis->m_poNotificationSinkSP.PointsObject())
		{
			CString oInfoString;
			oInfoString.Format(IDS_SQLRESTORE_COMPLETE,
				pThis->m_oDBNameString,
				pThis->m_oSQLServerString,CString(bstrMessage));
			if(S_OK != StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLRESTORE_COMPLETE,1,1,oInfoString))
			{
				pThis->m_hResult = ERROR_CANCELLED;
				pThis->m_poBackup->Abort();
			}
		}
		//------------------------------------
		_bstr_t oStrSQL = "use " + pThis->m_oDBNameString + "\r\n go\r\n" + 
			"n2001_makegrants 'navo2002user' \r\ngo\r\n"
		"update fcdbid set strDBID = '<database>:" + pThis->m_oSQLServerString + ":" +
		pThis->m_oDBNameString + "' \r\ngo\r\n";
		pThis->m_poSQLServer->ExecuteImmediate(oStrSQL,SQLDMO::SQLDMOExec_Default,vtMissing);
		//------------------------------------
	    return S_OK;
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->m_hResult = DISP_E_EXCEPTION;
		pThis->GetErrorStorage() += roNavoException;
	}
	pThis->m_poBackup->Abort();
	return E_ABORT;
}
//------------------------------------------------------------------
//	backuprestore interface
//------------------------------------------------------------------
STDMETHODIMP CMSSQLBackRestProvider::XBackupRestore::Begin(
	IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,
		ISupplyInfo * pSupplyInfo)
{
	METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		pThis->m_bBackup = (bBackup!='\0');
		pThis->m_poNotificationSinkSP.SafeQueryInterface(pONSinkUnknown);

		pThis->m_poSupplyInfoSP.SafeQueryInterface(pSupplyInfo);
		//analyze param
		pThis->ReadDescription(bBackup!='\0',pParameters);

		//to_do: u¿yj ISupplyInfo aby odpytaæ siê (programu nadrzêdnego lub user'a)
		//o najlepszy drive na temp....
		pThis->m_oTempBackupFileString = GenerateUniqueFileName("NB","TMP");

		pThis->m_oTmpBackupFR.SetFileName(pThis->m_oTempBackupFileString);

		CString oInfoString;
		oInfoString.Format(IDS_SQLBACKUP_CONNECTING,pThis->m_oSQLServerString);
		StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLBACKUP_CONNECTING,0,105,oInfoString);

		pThis->m_poSQLServer.CreateInstance("sqldmo.sqlserver");
		try
		{
			pThis->m_poSQLServer->Start(TRUE,_bstr_t(pThis->m_oSQLServerString),
				_bstr_t(pThis->m_oUserString),_bstr_t(pThis->m_oPasswordString));
		}
		catch(_com_error e)
		{
			if(HRESULT_CODE(e.Error()) == ERROR_SERVICE_ALREADY_RUNNING)
			{
				pThis->m_poSQLServer->Connect(_bstr_t(pThis->m_oSQLServerString),
				_bstr_t(pThis->m_oUserString),_bstr_t(pThis->m_oPasswordString));
			}
			else
			{
				throw;
			}
		}
	
		pThis->m_hResult = S_OK;
		if(bBackup)
		{
			pThis->m_poBackup.CreateInstance("sqldmo.backup");
			
			pThis->m_poBackup->Action = SQLDMO::SQLDMOBackup_Database;
			pThis->m_poBackup->Database = _bstr_t(pThis->m_oDBNameString);
			pThis->m_poBackup->Files = _bstr_t("["+pThis->m_oTempBackupFileString+"]");
			
			AfxConnectionAdvise(pThis->m_poBackup,__uuidof(SQLDMO::BackupSink),&pThis->m_xBackupSink,TRUE,
				&pThis->m_dwBackupSinkCookie);
			
			oInfoString.LoadString(IDS_SQLBACKUP_STARTING);
			StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLBACKUP_STARTING,5,105,oInfoString);
			pThis->m_poBackup->SQLBackup(pThis->m_poSQLServer);
		}
		else
		{
			pThis->m_poRestore.CreateInstance("sqldmo.restore");
			pThis->m_poRestore->Files = _bstr_t("["+pThis->m_oTempBackupFileString+"]");
			pThis->m_poRestore->Database = _bstr_t(pThis->m_oDBNameString);

			AfxConnectionAdvise(pThis->m_poRestore,__uuidof(SQLDMO::RestoreSink),&pThis->m_xRestoreSink,TRUE,
				&pThis->m_dwBackupSinkCookie);
		}
		pThis->m_bConsumed = false;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CMSSQLBackRestProvider::XBackupRestore::End()
{
	METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		if(pThis->m_bBackup)
		{
			if(pThis->m_poBackup != 0)
			{
				AfxConnectionUnadvise(pThis->m_poBackup,__uuidof(SQLDMO::BackupSink),&pThis->m_xBackupSink,TRUE,
					pThis->m_dwBackupSinkCookie);
			}
			pThis->m_poBackup = 0;
		}
		else
		{
			AfxConnectionUnadvise(pThis->m_poRestore,__uuidof(SQLDMO::RestoreSink),&pThis->m_xRestoreSink,TRUE,
				pThis->m_dwBackupSinkCookie);
			pThis->m_poRestore = 0;
		}
		pThis->m_poNotificationSinkSP = 0;
		pThis->m_poSQLServer->DisConnect();
		pThis->m_poSQLServer = 0;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	
	return S_OK;
}

STDMETHODIMP CMSSQLBackRestProvider::XBackupRestore::
	GetBackupStream(LPSTR * ppStreamName,LPSTR * ppStreamInfo,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupRestore)
	
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
		if(pThis->m_hResult != S_OK)		//in case of abort etc.
		{
			return pThis->m_hResult;
		}
		if(!pThis->m_bConsumed)
		{
			*ppStreamName = (LPTSTR) ::NdrOleAllocate(pThis->m_oTempBackupFileString.GetLength() + 1);
			strcpy((LPTSTR) *ppStreamName,pThis->m_oTempBackupFileString);
			*ppStreamInfo = (LPTSTR) ::NdrOleAllocate(pThis->m_oDescriptionString.GetLength() + 1);
			strcpy((LPTSTR)*ppStreamInfo,pThis->m_oDescriptionString);
			*ppDataStream = OpenFileStream_Read(pThis->m_oTempBackupFileString).Detach();
			pThis->m_bConsumed = true;
			return S_OK;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_FALSE;
}

STDMETHODIMP CMSSQLBackRestProvider::XBackupRestore::
	GetStat(long * pTotalCount,long * pTotalSize)
{
	METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

const TCHAR * _g_pchNAVO2001Database			= "Database";

STDMETHODIMP CMSSQLBackRestProvider::XBackupRestore::
	SetRestoreStream(LPSTR pStreamName,LPSTR pStreamInfo,IStream * pDataStream,__int64 i64Length)
{
	METHOD_PROLOGUE(CMSSQLBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
		CString oInfoString;
		oInfoString.LoadString(IDS_SQLRESTORE_STARTING);
		StdNotifyOnProgress(pThis->m_poNotificationSinkSP,IDS_SQLRESTORE_STARTING,5,105,oInfoString);

		HRESULT hr = IStream_CopyTo_WithNotify(pThis->m_poNotificationSinkSP,
			NewSCP(pDataStream,true),
			CreateFileStream_Write(pThis->m_oTempBackupFileString),pStreamName,i64Length);
		if(hr != S_OK)
		{
			return hr;
		}
		try
		{
			pThis->m_poRestore->ReplaceDatabase = TRUE;

			HRESULT hr = pThis->m_poRestore->SQLVerify(pThis->m_poSQLServer);
			if(hr != S_OK)
			{
				return hr;
			}
			CString oMasterFileNameString;
			if(!pThis->m_poSupplyInfoSP.PointsObject())
			{
				oMasterFileNameString = (LPCTSTR) pThis->m_poSQLServer->Databases->Item("master")->FileGroups->Item("PRIMARY")->DBFiles->Item(_variant_t(long(1)))->PhysicalName;
				long nLastBS = oMasterFileNameString.ReverseFind('\\');
				oMasterFileNameString = oMasterFileNameString.Left(nLastBS+1);
			}
			SQLDMO::QueryResultsPtr poQueryResults = pThis->m_poRestore->ReadBackupHeader(pThis->m_poSQLServer);
			poQueryResults = pThis->m_poRestore->ReadFileList(pThis->m_poSQLServer);
			CString oMultiString;
			for(long iter = 1; iter <= poQueryResults->Rows; iter++)
			{
				CString oLogicalNameString	= LPCTSTR(poQueryResults->GetColumnString(iter,1));
				CString oPhysicalNameString = LPCTSTR(poQueryResults->GetColumnString(iter,2));
				if(pThis->m_poSupplyInfoSP.PointsObject())
				{
					CSmartOleVariant oPhysicalNameSOV(oPhysicalNameString);
					CSmartOleVariant oResultSOV;
					HRESULT hr = pThis->m_poSupplyInfoSP->AskForData(ERCO_ASK_FOR_DB_LOCATION,
						oLogicalNameString,oPhysicalNameSOV.GetVariantRef(),
						&oResultSOV.GetVariantRef());
					ASSERT(hr == S_OK || hr == S_FALSE);
					ASSERT(oResultSOV.Type() == VT_BSTR);
					CString oAnswerString = oResultSOV.GetBStr();
					if(oAnswerString != "")
					{
						oPhysicalNameString = oAnswerString;
					}
				}
				else
				{
					long nLastDot = oPhysicalNameString.ReverseFind('.');
					CString oExtensionString;
					if(nLastDot != -1)
					{
						oExtensionString = oPhysicalNameString.Mid(nLastDot);
					}
					oPhysicalNameString = oMasterFileNameString + oLogicalNameString + oExtensionString;
				}
				oMultiString += "[" + oLogicalNameString + "] [" + oPhysicalNameString + "]";
			}
			pThis->m_poRestore->Action = SQLDMO::SQLDMORestore_Database;
			pThis->m_poRestore->RelocateFiles = (LPCTSTR)oMultiString;
			pThis->m_poRestore->SQLRestore(pThis->m_poSQLServer);
		}
		catch(_com_error e)
		{
			HRESULT hr = HRESULT_CODE(e.Error());
			if(hr == 3101 /* Exclusive access could not be obtained because the database is in use */)
			{
				ThrowNavoException(ERCO_BRMAN_RESTORE_DB_IN_USE,IDPAGE_NOTAVAILABLE);
			}
			else
			{
				throw;
			}
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}
