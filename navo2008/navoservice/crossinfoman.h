/*

	NAVO Enterprise 2008

	Cross Server Information Manager

*/

#ifndef _CROSS_INFO_MAN_H_
#define _CROSS_INFO_MAN_H_

class CCrossInfoUser : public CHyperLinkInfo
{
public:
	CCrossInfoUser();
	~CCrossInfoUser();
	void _set_prop(long nProp,VARIANT * pvValue);
	bool _get_prop(long nProp,VARIANT * pvValue);
	
	const DATE _get_last_access() const
	{
		return m_oLastAccess;
	}
private:
	CSimpleCriticalSection	m_oUserCriticalSection;
	DATE					m_oLastAccess;
};

class CCrossInfoObject;

class CCrossInfoCleaningThread : public CNavoThread
{
public:
	CCrossInfoCleaningThread(CCrossInfoObject * poCrossInfo);
	~CCrossInfoCleaningThread();
	virtual int Run();
	virtual CNavoException & GetErrorStorage();
private:
	void _perform_cleanup();
	CCrossInfoObject * m_poCrossInfo;
};

class CCrossInfoObject : public CCmdTargetWithErrorInfo
{
public:
	CCrossInfoObject();
	~CCrossInfoObject();
	
	void on_kill_users();

	BEGIN_INTERFACE_PART(CrossInfoManager,ICrossInfoManager)
		STDMETHOD(SetProp)(long * pnUserCookie,long nProp,VARIANT * pvValue);
		STDMETHOD(GetProp)(long nUserCookie,long nProp,VARIANT * pvValue);
		STDMETHOD(DeleteUser)(long nUserCookie);
	END_INTERFACE_PART(CrossInfoManager)
	DECLARE_INTERFACE_MAP()
private:
	bool _set_prop(long * pnUserCookie,long nProp,VARIANT * pvValue);
	bool _get_prop(long nUserCookie,long nProp,VARIANT * pvValue);
	void _delete_user(long nUserCookie);

	CSimpleCriticalSection	m_oObjCriticalSection;
	//{{
		long m_nUserIdGenerator;
		CMap<long,long,SCP<CCrossInfoUser>,SCP<CCrossInfoUser> &>	m_oCrossInfoMap;
	//}}
	CEvent	m_oExitEvent;
	HANDLE	m_hCleaningThread;

	friend class CCrossInfoCleaningThread;
};

class CCrossInfoCF : public CNavoClassFactory
{
public:
	CCrossInfoCF();
	void InitModuleName(HINSTANCE hInstance);
	void RegisterServer();
	bool Initialize();
	void Uninitialize();
	virtual SCP <IUnknown> OnCreateObject();
	void Kill();
private:
	CSimpleCriticalSection	m_oCFCriticalSection;
	//{{
		SCP<CCrossInfoObject>	m_poCrossInfoObjectSP;
	//}}
	CGenericErrorStorage	m_oErrorStorage;
};

extern CCrossInfoCF _g_CrossInfoCF;


inline CNavoException & CCrossInfoCleaningThread::GetErrorStorage()
{
	ASSERT(m_poCrossInfo);
	return m_poCrossInfo->GetErrorStorage();
}


#else
	#error __FILE__ already included
#endif
