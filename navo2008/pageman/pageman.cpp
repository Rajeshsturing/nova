// pageman.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "pageman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")
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

#pragma comment(lib, "uuid.lib")

/////////////////////////////////////////////////////////////////////////////
// CPagemanApp

BEGIN_MESSAGE_MAP(CPagemanApp, CWinApp)
	//{{AFX_MSG_MAP(CPagemanApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagemanApp construction

CPagemanApp::CPagemanApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPagemanApp object

CPagemanApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPagemanApp initialization
HINSTANCE _h_PAGEMAN_Instance = HINSTANCE(NULL);


BOOL CPagemanApp::InitInstance()
{
	COleObjectFactory::RegisterAll();
	_h_PAGEMAN_Instance = m_hInstance;
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
		/*
		//register nav2002.exe as navo: protocol handler application
		TCHAR cBuffer[ _MAX_PATH ];
		VERIFY(::GetModuleFileName(AfxGetInstanceHandle(),cBuffer,sizeof(cBuffer)) != 0);
		TCHAR * pLastBS = _tcsrchr(cBuffer,'\\');
		if(pLastBS != NULL)
		{
			*pLastBS = '\0';
			
			CString oNAVO2002ExeString(cBuffer);
			EnsureEndingBackslash(oNAVO2002ExeString);
			oNAVO2002ExeString += "navo2002.exe";
			
			SetRegistryKeyString(HKEY_CLASSES_ROOT, "navo", "", "URL:NAVO Enterprise 2008 Protocol");
			SetRegistryKeyString(HKEY_CLASSES_ROOT, "navo", "URL Protocol", "");
			SetRegistryKeyString(HKEY_CLASSES_ROOT, "navo\\Default Icon","",oNAVO2002ExeString);
			SetRegistryKeyString(HKEY_CLASSES_ROOT, "navo\\shell\\open\\command","",oNAVO2002ExeString + " -i \"%1\"");
		}
		*/

		SetRegistryKeyString(HKEY_CLASSES_ROOT,
				_T("AppID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),_T(""),_T("navo2002.client"));

		SetRegistryKeyString(HKEY_CLASSES_ROOT,
				_T("AppID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),_T("DllSurrogate"),_T(""));

	/*	
		BYTE ucaLaunchPermission[] = 
		{
			0x01,0x00,0x04,0x80,0x30,0x00,0x00,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,
			0x00,0x00,0x02,0x00,0x1c,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
			0x01,0x00,0x00,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,0x2e,0x6b,0x49,
			0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,
			0x2e,0x6b,0x49,0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00
  		};
		SetRegistryKeyBinary(HKEY_CLASSES_ROOT,
				_T("AppID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),_T("LaunchPermission"),
			ucaLaunchPermission,sizeof(ucaLaunchPermission)/sizeof(ucaLaunchPermission[0]));

		BYTE ucaAccessPermission[] = 
		{
			0x01,0x00,0x04,0x80,0x30,0x00,0x00,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,
			0x00,0x00,0x02,0x00,0x1c,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
			0x01,0x00,0x00,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,0x2e,0x6b,0x49,
			0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,
			0x2e,0x6b,0x49,0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00
  		};
		SetRegistryKeyBinary(HKEY_CLASSES_ROOT,
			_T("AppID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),
			_T("AccessPermission"),
			ucaAccessPermission,sizeof(ucaAccessPermission)/sizeof(ucaAccessPermission[0]));

		*/
		/*
			default is "Launching user" which is OK for most cases

			SetRegistryKeyString(HKEY_CLASSES_ROOT,
				_T("AppID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),
				_T("RunAs"),
				_T("Interactive User"));
		*/

		SetRegistryKeyString(HKEY_CLASSES_ROOT,
			_T("CLSID\\{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"),
			_T("AppID"),
			_T("{188cb167-82a4-4498-87d0-ebd8d9a00fb8}"));
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
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001Client,"navo2002.client"));
	return S_OK;
} 

