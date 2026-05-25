/*
	NAVO Enterprise 2008
	Copyright (c) 2002 NAVO

	NAVOPERIF object supports peripherials (COM etc.)
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "navoperif.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if !defined(_NAVODOTNET) && !defined(NAVO2008)
#ifdef _DEBUG
#pragma comment(lib, "..\\navocore\\debug\\navocore.lib")
#else
#pragma comment(lib, "..\\navocore\\release\\navocore.lib")
#endif
#endif

BEGIN_MESSAGE_MAP(CNavoperifApp, CWinApp)
	//{{AFX_MSG_MAP(CNavoperifApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNavoperifApp::CNavoperifApp()
{
}

BOOL CNavoperifApp::InitInstance()
{
	COleObjectFactory::RegisterAll();
	return TRUE;
}

CNavoperifApp theApp;

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
		//CComAutoObject == "navoperif.comobject"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb17e-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
		//CPrintingObjectAUTO == "navoperif.printing"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb18f-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
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
	
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2002PerifComObject,"navoperif.comobject"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2003PrintingObject,"navoperif.printing"));

	return S_OK;
} 

