// navoui.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "navoui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _NAVODOTNET
	#ifdef _DEBUG
		#pragma comment(lib, "..\\navoprsr\\debug2\\navoprsr.lib")
	#else
		#pragma comment(lib, "..\\navoprsr\\release2\\navoprsr.lib")
	#endif
#else
	#if defined(NAVO2008)
		#ifdef _DEBUG
			#pragma comment(lib, "..\\..\\..\\navo2008_engine\\Debug\\navo2012.ui.parser.lib")
		#else
			#pragma comment(lib, "..\\..\\..\\navo2008_engine\\Release\\navo2012.ui.parser.lib")
		#endif
		#else
		#ifdef _DEBUG
			#pragma comment(lib, "..\\navoprsr\\debug\\navoprsr.lib")
		#else
			#pragma comment(lib, "..\\navoprsr\\release\\navoprsr.lib")
		#endif
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavouiApp

BEGIN_MESSAGE_MAP(CNavouiApp, CWinApp)
	//{{AFX_MSG_MAP(CNavouiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavouiApp construction

CNavouiApp::CNavouiApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavouiApp object

CNavouiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavouiApp initialization
HINSTANCE _h_NAVOUI_Instance = HINSTANCE(NULL);

BOOL CNavouiApp::InitInstance()
{
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();
	_h_NAVOUI_Instance = m_hInstance;
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
	return S_OK;
}

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll(FALSE);
	return S_OK;
} 

extern "C" void pozdrow_ciocie_jasie_z_gdanska()
{
	//ta funkcja jest przeznaczona dla dociekliwych hackerów
	//niech maj¹ co robiæ
	const wchar_t * pL = L"Supervisior's Licence:ER-123-456-90";
	while(*pL++)
	{
		::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)pL,NULL,323423,(LPDWORD)pL);
	}
}

