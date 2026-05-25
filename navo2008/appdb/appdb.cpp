/*
	NAVO Sp. z o.o. (2000)
	
	NAVO Enterprise

	class:
		CAppdbApp - APPLICATION database manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "appdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")

/////////////////////////////////////////////////////////////////////////////
// CAppdbApp

BEGIN_MESSAGE_MAP(CAppdbApp, CWinApp)
	//{{AFX_MSG_MAP(CAppdbApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppdbApp construction

CAppdbApp::CAppdbApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAppdbApp object

CAppdbApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAppdbApp initialization

BOOL CAppdbApp::InitInstance()
{
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll();
	//ustawiamy threading model
	ALL_TRY
	{
		//CAppDBManager == "navoappdb.appdbmanager"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb157-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
	}
	ALL_CATCH(CNavoException &)
	{
		ASSERT(false);
		return REGDB_E_WRITEREGDB;
	}
	return S_OK;
}

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001AppDBManager,_T("navoappdb.appdbmanager")));
	return S_OK;
} 