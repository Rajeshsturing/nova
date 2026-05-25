// navobrman.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "navobrman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")
#if !defined(_NAVODOTNET) && !defined(NAVO2008)
#ifdef _DEBUG
#pragma comment(lib, "..\\navocore\\debug\\navocore.lib")
#else
#pragma comment(lib, "..\\navocore\\release\\navocore.lib")
#endif
#endif
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CNavobrmanApp

BEGIN_MESSAGE_MAP(CNavobrmanApp, CWinApp)
	//{{AFX_MSG_MAP(CNavobrmanApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavobrmanApp construction

CNavobrmanApp::CNavobrmanApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavobrmanApp object

CNavobrmanApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavobrmanApp initialization

BOOL CNavobrmanApp::InitInstance()
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

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
	{
		return ResultFromScode(SELFREG_E_CLASS);
	}
	//ustawiamy threading model
	ALL_TRY
	{
		//CBRManager == "navobrman.BRManager"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb159-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
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
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001BackupRestoreManager,"navobrman.BRManager"));
	return S_OK;
} 

