/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2003 NAVO

	navogm - modu³ gospodarki magazynowej (server)

	REV:KB:2003-11-09
*/

#include "stdafx.h"
#include "engineincl.h"
#include "navogmsvr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if !defined(_NAVODOTNET) && !defined(NAVO2008)
#ifdef _DEBUG
#pragma comment(lib, "..\\navocore\\debug\\navocore.lib")
#pragma comment(lib, "..\\navoobj\\debug\\navoobj.lib")
#else
#pragma comment(lib, "..\\navocore\\release\\navocore.lib")
#pragma comment(lib, "..\\navoobj\\release\\navoobj.lib")
#endif
#endif

BEGIN_MESSAGE_MAP(CNavogmSvrApp, CWinApp)
END_MESSAGE_MAP()


CNavoLog g_oLog;

CNavogmSvrApp::CNavogmSvrApp()
{
}

BOOL CNavogmSvrApp::InitInstance()
{
	CString oLogPathString;
	
	if(ERROR_SUCCESS==SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(),
		_T("GMLogPath"),oLogPathString))
	{
		if(oLogPathString != "")
		{
			g_oLog.Open(oLogPathString);
		}
	}
	COleObjectFactory::RegisterAll();
	return TRUE;
}

CNavogmSvrApp theApp;

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
		//CN5GMServerObjAUTO == "navogm.n5gmsvr";
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb17B-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
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

	VERIFY(AfxOleUnregisterClass(CLSID_NAVOGM_N5GMSVR,"navogm.n5gmsvr"));

	return S_OK;
} 

