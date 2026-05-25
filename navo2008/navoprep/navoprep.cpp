// navoprep.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "navoprep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")

BEGIN_MESSAGE_MAP(CNavoprepApp, CWinApp)
	//{{AFX_MSG_MAP(CNavoprepApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavoprepApp construction

CNavoprepApp::CNavoprepApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavoprepApp object

CNavoprepApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavoprepApp initialization

BOOL CNavoprepApp::InitInstance()
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
		//CPreprocessorObj == "navoprep.preprocessor"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb166-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
		//CPreprocessedDataCache == "navoprep.datacache"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb189-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
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
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001Preprocessor,_T("navoprep.preprocessor")));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2002PreprocessedDataCache,_T("navoprep.datacache")));
	return S_OK;
} 

