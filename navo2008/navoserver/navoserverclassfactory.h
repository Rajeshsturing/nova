/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	NAVO Server Class Factory (singleton)
*/

/*
	server representation of connected client
*/

class CNavoServerCF;
class CNavoLog;

class CServerClientObject : public CCmdTargetWithErrorInfo
{
public:
	CServerClientObject();
	~CServerClientObject();

	void _clean_up(bool bNormal);

	BEGIN_INTERFACE_PART(ServerClient,IServerClient)
		STDMETHOD(GetService)(navoservicetype eNST,IUnknown ** ppUnknown);
		STDMETHOD(GetUpdateVersionIfNewer)(long nUpdateType,LPCTSTR lpClientVersion,
			IStream ** ppDataStream,IStream ** ppInfoStream);
		STDMETHOD(AdviseLM)(LPCSTR pcUserName,LPCSTR pcComputerName,long *pCookie);
		STDMETHOD(UnAdviseLM)(long nCookie);
		STDMETHOD(AdviseNM)(IUnknown * pONSinkUnknown,LPCSTR pcUserName,
			LPCSTR pcComputerName,notifysinkclass eNSC,long *pCookie);
		STDMETHOD(UnAdviseNM)(long nCookie);
		STDMETHOD(GetRegistryKeyString)(long hKeyClass,LPCSTR lpSubKey,LPCSTR lpName,LPSTR * plpValue);
		STDMETHOD(SetRegistryKeyString)(long hKeyClass,LPCSTR lpSubKey,LPCSTR lpName,LPCSTR lpValue);
		STDMETHOD(EnumRegistryKeys)(long hKeyClass,LPCSTR lpSubKey,LPSTR * plpValue);
		STDMETHOD(GetUniqueId)(LPSTR * ppUniqueId);
		STDMETHOD(Close2)();
	END_INTERFACE_PART(ServerClient)

	BEGIN_INTERFACE_PART(PingServer,IPingServer)
		STDMETHOD(Advise)(IUnknown * pPingUnknown,long *pCookie);
		STDMETHOD(UnAdvise)(long nCookie);
	END_INTERFACE_PART(PingServer)


	DECLARE_INTERFACE_MAP()
private:
	inline long _get_pseudo_cookie()
	{
		return reinterpret_cast<long>(this);
	}
	//per client subsystems
	SCP<IObjectServer> m_poObjectServerSP;
	SCP<IAppDBManager> m_poAppDBManagerSP;
	long			   m_nLockManagerCookie;
	long			   m_nNotManCookie;
	bool			   m_bCallFinalRelease;
};


class CNavoServerPingServer : public CPingServerImpl
{
public:
	CNavoServerPingServer(){}
	virtual void OnDeadClient(long nCookie);
};
/*
	single class factory for whole server and all subsystems
*/

class CNavoServerCF : public CNavoClassFactory
{
public:
	CNavoServerCF(CNavoLog & roLog,bool bAsService);
	void InitModuleName(HINSTANCE hInstance);
	void RegisterServer();
	bool Initialize();
	void Uninitialize();
	virtual SCP <IUnknown> OnCreateObject();
	void OnFinalReleaseObject(CServerClientObject * poSCO);

	void WaitForEnd();

	SCP<ILockManager>		m_poLockManagerSP;
	SCP<INotificationManager> m_poNofiManagerSP;

	void MarkWasFailedClient()
	{
		m_bWasFailedClients = true;
	}

	long _get_current_client_count() const
	{
		return m_nClientCount;
	}
	CEvent & _get_finished_event()
	{
		return m_oFinishedEvent;
	}
	CEvent & _get_started_event()
	{
		return m_oStartedEvent;
	}
	const CString & GetLocalServerPath() const
	{
		return m_oLocalServerPathString;
	}
    virtual CNavoException & GetErrorStorage()
	{
		return m_oErrorStorage;
	}
	CNavoServerPingServer	m_oPingServer;	//for CServerClientObject objects
private:
	long					m_nClientCount;
	bool					m_bWasFailedClients;
	CGenericErrorStorage	m_oErrorStorage;
	CEvent					m_oFinishedEvent;
	CEvent					m_oStartedEvent;
	CMultipleRunDetector	m_oMRD;

	CNavoLog & m_roLog;
	//subsystems
	//fdcache
	//notification manager
	//appdb-manager-map
};

extern CNavoServerCF _g_NAVOServerCF;
