/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CScriptBackRestProvider- backup/restore provider based on scripts
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "ScriptBackRestProvider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CScriptBackRestProvider::CScriptBackRestProvider()
{
	EnableAutomation();
}

CScriptBackRestProvider::~CScriptBackRestProvider()
{
}


BEGIN_MESSAGE_MAP(CScriptBackRestProvider, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CScriptBackRestProvider)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CScriptBackRestProvider, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CScriptBackRestProvider)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {623319A0-64BB-47E0-B1E0-4441E76641A7}
static const IID IID_IScriptBackRestProvider =
{ 0x623319a0, 0x64bb, 0x47e0, { 0xb1, 0xe0, 0x44, 0x41, 0xe7, 0x66, 0x41, 0xa7 } };
/////////////////////////////////////////////////////////////////////////////
// CScriptBackRestProvider message handlers
BEGIN_INTERFACE_MAP(CScriptBackRestProvider, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CScriptBackRestProvider, IID_IScriptBackRestProvider, Dispatch)
	INTERFACE_PART(CScriptBackRestProvider, IID_IBackupRestore, BackupRestore)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CScriptBackRestProvider, BackupRestore)  

STDMETHODIMP CScriptBackRestProvider::XBackupRestore::Begin(
	IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,
	ISupplyInfo *pSupplyInfo)
{
	METHOD_PROLOGUE(CScriptBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CScriptBackRestProvider::XBackupRestore::End()
{
	METHOD_PROLOGUE(CScriptBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	
	return S_OK;
}

STDMETHODIMP CScriptBackRestProvider::XBackupRestore::
	GetBackupStream(LPSTR * ppStreamName,LPSTR * ppStreamInfo,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CScriptBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_FALSE;
}

STDMETHODIMP CScriptBackRestProvider::XBackupRestore::
	GetStat(long * pTotalCount,long * pTotalSize)
{
	METHOD_PROLOGUE(CScriptBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CScriptBackRestProvider::XBackupRestore::
	SetRestoreStream(LPSTR pStreamName,LPSTR pStreamInfo,IStream * pDataStream,__int64 i64Length)
{
	METHOD_PROLOGUE(CScriptBackRestProvider, BackupRestore)
	
	ALL_TRY
	{
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}
