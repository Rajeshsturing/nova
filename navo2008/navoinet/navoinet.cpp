// navoinet.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "navoinet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

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
// CNavoinetApp

BEGIN_MESSAGE_MAP(CNavoinetApp, CWinApp)
	//{{AFX_MSG_MAP(CNavoinetApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNavoinetApp::CNavoinetApp()
{
}


CNavoinetApp theApp;

HINSTANCE _h_NAVOINET_Instance = HINSTANCE(NULL);

BOOL CNavoinetApp::InitInstance()
{
	COleObjectFactory::RegisterAll();
	_h_NAVOINET_Instance  = m_hInstance;
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
		//CWebTransfer == "navoinet.webtransfer"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb174-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
		//CMailSession == "navoinet.Mail"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb173-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
		//CSocketStream == "navoinet.socket"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb178-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
		//CNAVOPOP3Client == "navoinet.POP3Client"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\{188cb17f-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32", "ThreadingModel", "Both");
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
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001InetMail,"navoinet.Mail"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001InetTransfer,"navoinet.webtransfer"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001SocketStream,"navoinet.socket"));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2002POP3Client,"navoinet.POP3Client"));
	return S_OK;
} 

void CNavoinetApp::InitSockets()
{
	if(m_poSCHSP.PointsNull())
	{
		m_poSCHSP = NewSCP(new CStartupCleanupHolder(2,2));
	}
}

int CNavoinetApp::ExitInstance() 
{
	m_poSCHSP = 0;
	
	return CWinApp::ExitInstance();
}

void _navo_init_sockets()
{
	theApp.InitSockets();
}

