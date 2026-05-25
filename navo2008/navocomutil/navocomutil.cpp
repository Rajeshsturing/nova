// navocomutil.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "navocomutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CNavocomutilApp, CWinApp)
	//{{AFX_MSG_MAP(CNavocomutilApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavocomutilApp construction

CNavocomutilApp::CNavocomutilApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavocomutilApp object

CNavocomutilApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavocomutilApp initialization

BOOL CNavocomutilApp::InitInstance()
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
	ALL_TRY
	{
		//CStreamFilterObject == "navocomutil.streamfilter"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb16a-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
		//CSystemAutoObject == "navocomutil.system"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb15d-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");

		//CTaskSchedulerManager == "navocomutil.taskman"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb18a-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");

		//caspator_comobject == "navocomutil.aspator"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb190-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
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
	
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001StreamObject,"navocomutil.streamobj"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001StreamFilter,"navocomutil.streamfilter"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001SystemObject,"navocomutil.system"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001HyperSetObject,"navocomutil.hyperset"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2002TaskSchedManObject,"navocomutil.taskman"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2003ASPator,"navocomutil.aspator"));

	return S_OK;
} 

