/*
	NAVO Sp. z o.o. (2000)
	
	NAVO Enterprise

	class:
		Database access object
*/

#include "stdafx.h"
#include "navodb.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\navodef\stdobjdef.h"
#include "..\include\flatdata.h"	//flat data transport
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\DefinitionManager.h"
#include "ADOObjServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")


CNavoLog g_oLog;

/////////////////////////////////////////////////////////////////////////////
// CNavodbApp

BEGIN_MESSAGE_MAP(CNavodbApp, CWinApp)
	//{{AFX_MSG_MAP(CNavodbApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNavodbApp::CNavodbApp()
{
}


CNavodbApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNavodbApp initialization

BOOL CNavodbApp::InitInstance()
{
	m_poDefinitionManProvSP = NewSCP(new CDefinitionManagerProvider());
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	VERIFY(ERROR_SUCCESS == SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,
		GetSetupRegistryKeyName(),_T("MainUID"),m_oMainUIDString));

		CString oLogPathString;
	
	if(ERROR_SUCCESS==SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(),
		_T("NAVODBLogPath"),oLogPathString))
	{
		if(oLogPathString != "")
		{
			g_oLog.Open(oLogPathString);
		}
	}
	return TRUE;
}

int CNavodbApp::ExitInstance()
{
	m_poDefinitionManProvSP = 0;
	return CWinApp::ExitInstance();
}

SCP<CFDObjectCache> CNavodbApp::get_cache_for_cacheuid(LPCTSTR lpObjectCacheUID)
{
	SCP<CFDObjectCache> poFDOObjectCacheSP;
	CSimpleLock oLock(m_oFDObjCacheMapCS);

	if(!m_oFDObjCacheMap.Lookup(lpObjectCacheUID,poFDOObjectCacheSP))
	{
		DWORD dwCacheSize = DEFAULT_CACHE_SIZE;
		if(ERROR_SUCCESS==SafeGetRegistryKeyDword(HKEY_LOCAL_MACHINE, GetDatabaseRegistryKeyName(),
			_T("CacheSize"),dwCacheSize))
		{
			if(dwCacheSize > 25000)
			{
				dwCacheSize = 25000;
			}
		}
		bool bTrackDBWrites = false;

		CString oTrackDBWritesString;
		if(ERROR_SUCCESS==SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetDatabaseRegistryKeyName(),
			_T("TrackDBWrites"),oTrackDBWritesString))
		{
			bTrackDBWrites = (oTrackDBWritesString == "Y");
		}
		poFDOObjectCacheSP = NewSCP(new CFDObjectCache(dwCacheSize,bTrackDBWrites));

		m_oFDObjCacheMap[ lpObjectCacheUID ] = poFDOObjectCacheSP;
	}

	return poFDOObjectCacheSP;
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
		//CLSID_NAVO2001LockManager == "navodb.lockmanager"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb153-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
		//CLSID_NAVO2001_ObjectServer == "navodb.objectserver"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb160-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
		//CLSID_NAVO2001NotificationManager == "navodb.notmanager"
		SetRegistryKeyString(HKEY_CLASSES_ROOT, _T("CLSID\\{188cb150-82a4-4498-87d0-ebd8d9a00fb8}\\InProcServer32"), _T("ThreadingModel"), _T("Both"));
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
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001_ObjectServer,_T("navodb.objectserver")));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001LockManager,_T("navodb.lockmanager")));
	VERIFY(AfxOleUnregisterClass(CLSID_NAVO2001NotificationManager,_T("navodb.notmanager")));
	return S_OK;
} 

