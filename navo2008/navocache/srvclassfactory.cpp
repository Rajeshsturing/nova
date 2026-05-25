/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Object Server Class Factory (singleton)
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\navolog.h"
#include "srvclassfactory.h"
#include "CacheManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCacheManagerServerClassFactory _g_CacheManagerServerClassFactory;

CCacheManagerServerClassFactory::CCacheManagerServerClassFactory() :
	CNavoClassFactory(m_oErrorStorage, CLSID_NAVO2001_CacheServer,
		"navocache.manager", "",true,true),
	m_pCacheManager(NULL),
	m_nClientCount(0)
{
}

void CCacheManagerServerClassFactory::InitModuleName(HINSTANCE hInstance)
{
	char cBuffer[ _MAX_PATH ];
	VERIFY(::GetModuleFileName(hInstance,cBuffer,sizeof(cBuffer)) != 0);
	m_oLocalServerPathString = cBuffer;
}

void CCacheManagerServerClassFactory::RegisterServer()
{
	CNavoClassFactory::RegisterServer();

	SetRegistryKeyString(HKEY_CLASSES_ROOT,
			_T("AppID\\{188CB15C-82A4-4498-87D0-EBD8D9A00FB8}"),_T(""),_T("navocache.manager"));

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
			_T("AppID\\{188CB15C-82A4-4498-87D0-EBD8D9A00FB8}"),_T("LaunchPermission"),
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
		_T("AppID\\{188CB15C-82A4-4498-87D0-EBD8D9A00FB8}"),
		_T("AccessPermission"),
		ucaAccessPermission,sizeof(ucaAccessPermission)/sizeof(ucaAccessPermission[0]));
	*/

	//SetRegistryKeyString(HKEY_CLASSES_ROOT,
	//	_T("AppID\\{188CB15C-82A4-4498-87D0-EBD8D9A00FB8}"),
	//	_T("RunAs"),
	//	//_T("Interactive User"));
	//	_T(""));
}

SCP <IUnknown> CCacheManagerServerClassFactory::OnCreateObject()
{
	CSimpleLock oLock(m_oCriticalSection);
	SCP<IUnknown> poUnknownSP;
	if(m_pCacheManager == NULL)
	{
		try
		{
			m_pCacheManager = new CCacheManager();
		}
		catch(...)
		{
			m_oFinishedEvent.SetEvent();
			throw;
		}
		poUnknownSP = m_pCacheManager->GetUnknownSP();
		poUnknownSP->Release();
		//teraz m_pCacheManager powinien mieæ jedn¹ referencjê (m_dwRef==1)
	}
	else
	{
		poUnknownSP = m_pCacheManager->GetUnknownSP();
	}
	ASSERT(poUnknownSP.PointsObject());
	::InterlockedIncrement(&m_nClientCount);
	return poUnknownSP;
}

void CCacheManagerServerClassFactory::OnCloseObject()
{
	CSimpleLock oLock(m_oCriticalSection);
	if(::InterlockedDecrement(&m_nClientCount)==0)
	{
		m_oFinishedEvent.SetEvent();
	}
}

void CCacheManagerServerClassFactory::WaitForEnd()
{
	DWORD dwTimeOut = 
#ifdef _DEBUG
		10000;
#else
		1000;
#endif

	CNavoLog oDummyLog;

	CSingleLock oSingleLock(&m_oFinishedEvent);
	while(!oSingleLock.Lock(dwTimeOut))
	{
	   m_oPingServer.__PerformPingTest(oDummyLog);
	}
	Done();
}

void CCacheManagerServerClassFactory::Uninitialize()
{
	if(m_pCacheManager)
	{
		delete m_pCacheManager;
	}
	m_pCacheManager = NULL;
}

void CCacheManagerServerClassFactory::CloseFailedClient()
{
	ASSERT(m_pCacheManager);
	m_pCacheManager->Close(false);
}

void CCMPingServer::OnDeadClient(long nCookie)
{
	_g_CacheManagerServerClassFactory.CloseFailedClient();
}


