/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	OLE helper functions
*/

#ifndef _INTERFACEUTIL_H_
#define _INTERFACEUTIL_H_

HRESULT StdNotifyOnProgress(SCP<INotificationSink> & rpoNotificationSinkSP,
							long nInfoType,long nAdv,long nTotal,LPCTSTR lpMsg);

HRESULT IStream_CopyTo_WithNotify(SCP<INotificationSink> & rpoNotificationSinkSP,
	SCP<IStream> & rpoSrcStreamSP,SCP<IStream> & rpoDestStreamSP,LPCTSTR lpStreamName,__int64 i64StreamSize);


class CStdNotifyOnProgressHolder : public CInterface__
{
public:
	CStdNotifyOnProgressHolder(SCP<INotificationSink> & rpoNotificationSinkSP,
		LPCTSTR lpInitialMsg,LPCTSTR lpFinalMsg) :
		m_poNotificationSinkSP(rpoNotificationSinkSP),
		m_oFinalString(lpFinalMsg)
	{
		StdNotifyOnProgress(m_poNotificationSinkSP,PROGRESS_BEGIN,0,1000,lpInitialMsg);
	}
	~CStdNotifyOnProgressHolder()
	{
		StdNotifyOnProgress(m_poNotificationSinkSP,PROGRESS_END,1000,1000,m_oFinalString);
	}
private:
	CString	m_oFinalString;
	SCP<INotificationSink> m_poNotificationSinkSP;
};

//----------------------------------------------------------------------------
//
// CSupplyInfo__ - generic pure class - simplifies implementation of ISupplyInfo
//
//----------------------------------------------------------------------------
interface ISupplyInfo;

class CSupplyInfo__ : public CCmdTargetInterface
{
public:
	CSupplyInfo__()
	{
		EnableAutomation();
	}
	virtual HRESULT Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer) = 0;
	ISupplyInfo * GetISupplyInfo()
	{
		return &m_xSupplyInfo;
	}
	afx_msg void AskForDataAUTO(long nInfoType, LPCTSTR lpDescription, const VARIANT FAR& varQuestion, VARIANT FAR* pVarAnswer)
	{
		Impl_AskForData(nInfoType,lpDescription,varQuestion,pVarAnswer);
	}
protected:
	BEGIN_INTERFACE_PART(SupplyInfo,ISupplyInfo)
		STDMETHOD(AskForData)
		(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer)
	{
		METHOD_PROLOGUE(CSupplyInfo__, SupplyInfo)

		return pThis->Impl_AskForData(nInfoType,lpDescription,varQuestion,pvarAnswer);
	}
	END_INTERFACE_PART(SupplyInfo)
	DECLARE_INTERFACE_MAP();
	DECLARE_DISPATCH_MAP()
};


//----------------------------------------------------------------------------
//
// CScriptSupplyInfo  - supply info using VB class object with method "askfordata"
//
//----------------------------------------------------------------------------

class CScriptSupplyInfo : public CSupplyInfo__
{
public:
	CScriptSupplyInfo(SCP<IDispatch> & rpoDispatchSP) :
		CSupplyInfo__(),
		m_poDispatchSP(rpoDispatchSP),
		m_dispidAskForData(0),
		m_dispidOnProgress(0)
	{
	}
	virtual HRESULT Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer);
	virtual HRESULT Impl_OnProgress(long nInfoType,long lAdvance,long lTotal,LPSTR lpDescription);

private:
	SCP<IDispatch>	m_poDispatchSP;
	DISPID			m_dispidAskForData;
	DISPID			m_dispidOnProgress;
};

//----------------------------------------------------------------------------
//
// Bazowy Dispatch Forwarer - u¿ywany jest do przekierowywania wywo³añ ze 
// script engine do w³aœciwego IDispatch'a (engine cachuje dispatche dla danej nazwy
// st¹d takie pokrêcone rozwi¹zanie)
//
//----------------------------------------------------------------------------

class CBaseDispatchForwarder__ : public IDispatch
{
public:
	CBaseDispatchForwarder__()
	{
	}
	~CBaseDispatchForwarder__()
	{
	}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject)
	{
		*ppvObject = NULL;
		if(riid == IID_IDispatch || riid == IID_IUnknown)
		{
			AddRef();
			*ppvObject = reinterpret_cast<void*>(this);
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef(void)
	{
		return 2;	//ignore
	}
	virtual ULONG STDMETHODCALLTYPE Release(void)
	{
		return 1;	//ignore
	}
    
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo)
	{
		if(GetDestinationDispatch().PointsObject())
		{
			return GetDestinationDispatch()->GetTypeInfoCount(pctinfo);
		}
		ASSERT(false);
		return E_FAIL;
	}
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo)
	{
		if(GetDestinationDispatch().PointsObject())
		{
			return GetDestinationDispatch()->GetTypeInfo(iTInfo,lcid,ppTInfo);
		}
		ASSERT(false);
		return E_FAIL;
	}
    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid,LPOLESTR *rgszNames,
		UINT cNames,LCID lcid,DISPID *rgDispId)
	{
		if(GetDestinationDispatch().PointsObject())
		{
			return GetDestinationDispatch()->GetIDsOfNames(riid,rgszNames,cNames,lcid,rgDispId);
		}
		ASSERT(false);
		return E_FAIL;
	}
    virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember,REFIID riid,LCID lcid,
        WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr)
	{
		if(GetDestinationDispatch().PointsObject())
		{
			return GetDestinationDispatch()->Invoke(dispIdMember,riid,lcid,wFlags,
				pDispParams,pVarResult,pExcepInfo,puArgErr);
		}
		ASSERT(false);
		return E_FAIL;
	}
private:
	virtual SCP<IDispatch> GetDestinationDispatch() = 0;
};

//----------------------------------------------------------------------------
//	Dispatch forwarder pamiêtaj¹cy Dispatch
//----------------------------------------------------------------------------

class CDispatchForwarder : public CBaseDispatchForwarder__ 
{
public:
	CDispatchForwarder()
	{
	}
	~CDispatchForwarder()
	{
		ASSERT(m_poDispatchSP.PointsNull());	//musi byæ zwolniony
	}
private:
	//for use by our friendly holder
	void SetDestinationDispatch(SCP<IDispatch> & rpoDispatchSP)
	{
		//TRACE1("FORWARDER set to %x\n",(long)(long*)rpoDispatchSP.Get());
		m_poDispatchSP = rpoDispatchSP;
	}
	virtual SCP<IDispatch> GetDestinationDispatch()
	{
		return m_poDispatchSP;
	}
	SCP<IDispatch>	m_poDispatchSP;

	friend class CInvokeForwarderHolder;
};

class CInvokeForwarderHolder : public CInterface__
{
public:
	CInvokeForwarderHolder(CDispatchForwarder & roDispatchForwarder,
		SCP<IDispatch> & rpoDispatchSP) :
		m_oDispatchForwarder(roDispatchForwarder)
	{
		m_poPrevDispatchSP = m_oDispatchForwarder.GetDestinationDispatch();
		m_oDispatchForwarder.SetDestinationDispatch(rpoDispatchSP);
	}
	~CInvokeForwarderHolder()
	{
		m_oDispatchForwarder.SetDestinationDispatch(m_poPrevDispatchSP);
	}
private:
	CDispatchForwarder & m_oDispatchForwarder;
	SCP<IDispatch>		 m_poPrevDispatchSP;
};

//----------------------------------------------------------------------------
//	CDispatchDynamicResolver jest u¿ywany przez CDynamicDispatchForwarer
//----------------------------------------------------------------------------
class CDispatchDynamicResolver
{
public:
	CDispatchDynamicResolver(){}
	virtual SCP<IDispatch> GetDynamicDispatchSP() = 0;
};

class CDynamicDispatchForwarer : public CBaseDispatchForwarder__ 
{
public:
	CDynamicDispatchForwarer() :
		m_pDDR(NULL)
	{
	}
	virtual SCP<IDispatch> GetDestinationDispatch()
	{
		ASSERT(m_pDDR);
		return m_pDDR->GetDynamicDispatchSP();
	}
	void SetDispatchDynamicResolver(CDispatchDynamicResolver * pDDR)
	{
		m_pDDR = pDDR;
	}
private:
	CDispatchDynamicResolver * m_pDDR;
};

/*
	podstawowa implementacja ping-servera
*/
interface IPingClient;

class CNavoLog;

class CPingServerImpl
{
public:
	CPingServerImpl()
	{
	}
	~CPingServerImpl();
	void __Advise(IUnknown * pPingUnknown,long nCookie);
	void __UnAdvise(long nCookie);
	void __PerformPingTest(CNavoLog & roLog);
	virtual void OnDeadClient(long nCookie) = 0;
#ifdef _DEBUG
	bool IsEmpty()
	{
		CSimpleLock oSimpleLock(m_oCookieCS);
		return (m_oMap.GetCount() == 0);
	}
#endif
private:
	CSimpleCriticalSection	m_oCookieCS;
	CMap<long,long,SCP<IPingClient>,SCP<IPingClient> & > m_oMap;
};

template <class T>
inline long AdvisePingServer(IUnknown * poPingClientUnknown,T & oT)
{
	if(IsNXMTransport())
	{
		return -1;
	}
	else
	{
		SCP<IPingServer> poPingServerSP;
		poPingServerSP.QueryInterface(oT);
		long nCookie;
		HRESULT hr = poPingServerSP->Advise(poPingClientUnknown,&nCookie);
		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_PINGSERVER_ADVISE_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
		}
		return nCookie;
	}
}

template <class T>
inline void UnAdvisePingServer(T & oT,long & nCookie)
{
	if(!IsNXMTransport())
	{
		SCP<IPingServer> poPingServerSP;
		poPingServerSP.QueryInterface(oT);

		HRESULT hr = poPingServerSP->UnAdvise(nCookie);
		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_PINGSERVER_UNADVISE_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
		}
	}

	nCookie = 0;
}


inline UINT AFXAPI HashKey(const navolockid & key)
{
	return (UINT) ((key.m_typeid << 16) + key.m_idobj);
}

inline BOOL AFXAPI CompareElements(const navolockid * pElement1, const navolockid * pElement2)
{
	return memcmp(pElement1,pElement2,sizeof(navolockid)) == 0;
}


inline void _force_release(IUnknown * poUnknown)
{
	ASSERT(poUnknown);
	try
	{
		HRESULT hr = ::CoDisconnectObject(poUnknown,0);
		ASSERT(hr == S_OK);
		//while(true)
		//{
		//	poUnknown->Release();
		//}
	}
	catch(...)
	{
		TRACE0("force release threw\n");
	}
}


inline void _init_navostreaminfo(navostreaminfo & roNSI)
{
	memset(&roNSI,0,sizeof(roNSI));
}

inline void _copy_navostreaminfo(const navostreaminfo & roSrcNSI,navostreaminfo & roDestNSI)
{
	memcpy(&roDestNSI,&roSrcNSI,sizeof(navostreaminfo));
}

inline CArchive & AFXAPI operator << (CArchive & oArchive,const navostreaminfo & roSrcNSI)
{
	//uwaga na modyfikacje navostreaminfo !!
	ASSERT(sizeof(roSrcNSI.m_cExt) == sizeof(long));
	oArchive << *(long*)(roSrcNSI.m_cExt);
	return oArchive;
}

inline CArchive & AFXAPI operator >> (CArchive & oArchive,navostreaminfo & roNSI)
{
	//uwaga na modyfikacje navostreaminfo !!
	ASSERT(sizeof(roNSI.m_cExt) == sizeof(long));
	long nTmp;
	oArchive >> nTmp;
	*(long*)(roNSI.m_cExt) = nTmp;
	return oArchive;
}

#else
	#error __FILE__ already included
#endif

