// ===========================================================================
//
// NAVO Enterprise 2001
//
// Core functions
//
// ===========================================================================

#include "stdafx.h"
#include "navocore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "mpr.lib")

#if defined(NAVO2008)
#ifdef _DEBUG
	#pragma comment(lib, "..\\debug\\System\\zlib2008.lib")
#else
	#pragma comment(lib, "..\\release\\System\\zlib2008.lib")
#endif
#else
#ifdef _DEBUG
	#pragma comment(lib, "..\\lib\\debugzlib.lib")
#else
	#pragma comment(lib, "..\\lib\\releasezlib.lib")
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
// CNavocoreApp

BEGIN_MESSAGE_MAP(CNavocoreApp, CWinApp)
	//{{AFX_MSG_MAP(CNavocoreApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavocoreApp construction

CNavocoreApp::CNavocoreApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavocoreApp object

CNavocoreApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavocoreApp initialization
HINSTANCE _h_NAVOCORE_Instance = HINSTANCE(NULL);

BOOL CNavocoreApp::InitInstance()
{
	COleObjectFactory::RegisterAll();
	_h_NAVOCORE_Instance  = m_hInstance;
	return TRUE;
}

HINSTANCE GetNAVOCORE_InstanceHandle()
{
	return _h_NAVOCORE_Instance;
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
	return S_OK;
}

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll(FALSE);
	return S_OK;
} 

