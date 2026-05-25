/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Cache Manager Object Server Class Factory (singleton)
*/


#ifndef _SERWERCLASSFACTORY_H_
#define _SERWERCLASSFACTORY_H_

class CCacheManager;

class CCMPingServer : public CPingServerImpl
{
public:
	CCMPingServer(){}
	virtual void OnDeadClient(long nCookie);
};

class CCacheManagerServerClassFactory : public CNavoClassFactory
{
public:
	CCacheManagerServerClassFactory();
	void InitModuleName(HINSTANCE hInstance);
	virtual SCP <IUnknown> OnCreateObject();
	void OnCloseObject();
	void Uninitialize();
	void RegisterServer();

	void CloseFailedClient();

	void WaitForEnd();
	CCMPingServer			m_oPingServer;
	CGenericErrorStorage	m_oErrorStorage;
private:
	CSimpleCriticalSection	m_oCriticalSection;
	CEvent					m_oFinishedEvent;
	CCacheManager *			m_pCacheManager;
	long					m_nClientCount;
};

extern CCacheManagerServerClassFactory _g_CacheManagerServerClassFactory;

#else
	#error __FILE__ already included
#endif
