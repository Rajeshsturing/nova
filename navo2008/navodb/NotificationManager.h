/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	notification manager
*/


#if !defined(AFX_NOTIFICATIONMANAGER_H__57F5720D_1AFA_46DF_854C_5B8F0A17B340__INCLUDED_)
#define AFX_NOTIFICATIONMANAGER_H__57F5720D_1AFA_46DF_854C_5B8F0A17B340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const long _MAX_SENDING_THREADS = 4;

/////////////////////////////////////////////////////////////////////////////
// CNotificationManager command target

class CNMClientInfo : public CClientInfo
{
public:
	CNMClientInfo(LPCTSTR lpUserName, LPCTSTR lpComputerName,
		notifysinkclass	eNSC,
		SCP<INotificationSink> & rpoNotificationSinkSP) :
		CClientInfo(lpUserName, lpComputerName),
		m_eNSC(eNSC),
		m_poNotificationSinkSP(rpoNotificationSinkSP)
	{
	}
	SCP<INotificationSink> & GetNotificationSink()
	{
		return m_poNotificationSinkSP;
	}
private:
	notifysinkclass			m_eNSC;
	SCP<INotificationSink>	m_poNotificationSinkSP;
};

class CServerNotificationData : public CInterface__
{
public:
	CServerNotificationData() :
		m_nOriginatorCookie(0),
		m_nDestinatorCookie(0),
		m_nEventCode(0)
	{
	}
	long & _originator()
	{
		return m_nOriginatorCookie;
	}
	long & _destinator()
	{
		return m_nDestinatorCookie;
	}
	long & _event()
	{
		return m_nEventCode;
	}
	CSmartOleVariant & _data()
	{
		return m_oDataSOV;
	}
private:
	long			 m_nOriginatorCookie;
	long			 m_nDestinatorCookie;
	long			 m_nEventCode;
	CSmartOleVariant m_oDataSOV;
};

class CNotificationManager;

class CNotificationThread : public CNavoThread
{
public:
	CNotificationThread(CNotificationManager * poNotMan);
	~CNotificationThread();
	virtual int Run();
	virtual CNavoException & GetErrorStorage();
private:
	CNotificationManager * m_poNotMan;
};

class CNotificationManager : public CCmdTargetInterface
{
	DECLARE_DYNCREATE(CNotificationManager)

	CNotificationManager();
public:

	//{{AFX_VIRTUAL(CNotificationManager)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	CNavoException & GetErrorStorage()
	{
		return m_oErrorStorage;
	}

protected:
	virtual ~CNotificationManager();

	//{{AFX_MSG(CNotificationManager)
	//}}AFX_MSG
	BEGIN_INTERFACE_PART(NotificationManager, INotificationManager)
		STDMETHOD(Advise)(IUnknown * pONSinkUnknown, LPCSTR pcUserName,
			LPCSTR pcComputerName, notifysinkclass eNSC, long *pCookie);
	STDMETHOD(UnAdvise)(long nCookie);
	STDMETHOD(NotifySharedVariableChange)(long nOriginatorCookie, long lVarNr, VARIANT vNewValue);
	STDMETHOD(QuerySinks)(long *pDataLength, byte ** lpBinaryData);
	STDMETHOD(NotifyUser)(long nOriginatorCookie, long nDestinatorCookie,
		long lEvenCode, VARIANT * pDataVariant);
	STDMETHOD(NotifyMultipleUsers)(long nOriginatorCookie,
		long nCount, const long * pDestinatorCookies,
		long lEvenCode, VARIANT * pDataVariant);
	STDMETHOD(SetProp)(long nCookie, long nProp, VARIANT vValue);
	STDMETHOD(GetProp)(long nCookie, long nProp, VARIANT * pvValue);
	STDMETHOD(GetProp2)(long nCookie, long nProp, VARIANT * pvValue, long * pHR);
	STDMETHOD(Close)();
	STDMETHOD(QuerySinks2)(long *pDataLength, SAFEARRAY ** lpBinaryData);
	END_INTERFACE_PART(NotificationManager)

	DELEGATE_NAVOERRORINFO_ON_GENERICERRORSTORAGE(CNotificationManager, m_oErrorStorage);

	DECLARE_OLECREATE(CNotificationManager)

	//{{AFX_DISPATCH(CNotificationManager)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	void _start_working_threads();

	void _advise(IUnknown * pONSinkUnknown, LPCSTR pcUserName,
		LPCSTR pcComputerName, notifysinkclass eNSC, long *pCookie);
	void _unadvise(long nCookie);
	void _close();
	void _set_client_prop(long nCookie, long nProp, const VARIANT & rvValue);
	bool _get_client_prop(long nCookie, long nProp, VARIANT * pvValue);
	void _fill_rich_client_info(CClientInfoArray & roClientInfoArray);
	void _fill_cookie_info(CArray<long, long&> & roCookieInfoArray);

	void _put_notify_user(long nOriginatorCookie, long nDestinatorCookie, long lEvenCode, VARIANT * pDataVariant);
	void _put_notify_multiple_users(long nOriginatorCookie, long nCount, const long * pDestinatorCookies,
		long lEvenCode, VARIANT * pDataVariant);

	void _notify_shared_var_change(long nOriginatorCookie, long lVarNr, const VARIANT & rvNewValue);

	void _add_to_queue(CList<SCP<CServerNotificationData>, SCP<CServerNotificationData> &> & roNewList);

	SCP<CServerNotificationData> _retrieve_from_queue();
	void _call_destination(SCP<CServerNotificationData> poSNDSP);

	CSimpleCriticalSection	m_oCookieCS;
	//{{
	CMap<long, long, SCP<CNMClientInfo>, SCP<CNMClientInfo> & > m_oMap;
	//}}
	CGenericErrorStorage m_oErrorStorage;

	//out-of-thread
	CEvent		m_oExitEvent;
	CEvent		m_oNewNotificationEvent;

	CSimpleCriticalSection	m_oNotificationListCS;
	//{{
	CList<SCP<CServerNotificationData>, SCP<CServerNotificationData> &>	m_oNotificationList;
	//}}
	HANDLE	m_hSendingThreads[_MAX_SENDING_THREADS];

	friend class CNotificationThread;
};

inline CNavoException & CNotificationThread::GetErrorStorage()
{
	return m_poNotMan->GetErrorStorage();
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTIFICATIONMANAGER_H__57F5720D_1AFA_46DF_854C_5B8F0A17B340__INCLUDED_)
