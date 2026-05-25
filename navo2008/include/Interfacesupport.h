/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	COM Interface Support
*/

#ifndef _NAVOOBJECTS_H_
#define _NAVOOBJECTS_H_


//helper macro

#define DELEGATE_UNKNOWN_INTERFACE(objectClass, dualClass) \
    STDMETHODIMP_(ULONG) objectClass::X##dualClass::AddRef() \
    { \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalAddRef(); \
	} \
	STDMETHODIMP_(ULONG) objectClass::X##dualClass::Release() \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalRelease(); \
	} \
	STDMETHODIMP objectClass::X##dualClass::QueryInterface( \
		REFIID iid, LPVOID* ppvObj) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		return pThis->ExternalQueryInterface(&iid, ppvObj); \
	} 

#ifdef _DEBUG
#define DELEGATE_UNKNOWN_INTERFACE_TRACE(objectClass, dualClass) \
    STDMETHODIMP_(ULONG) objectClass::X##dualClass::AddRef() \
    { \
		METHOD_PROLOGUE(objectClass, dualClass) \
		ULONG u=pThis->ExternalAddRef();\
		TRACE3("%s::ADREF(%d)=%d\n",#objectClass "::" #dualClass,(long)(void*)pThis,pThis->m_dwRef); \
		return u; \
	} \
	STDMETHODIMP_(ULONG) objectClass::X##dualClass::Release() \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		ULONG u=pThis->ExternalRelease(); \
		TRACE3("%s::REL(%d)=%d\n",#objectClass "::" #dualClass,(long)(void*)pThis,pThis->m_dwRef); \
		return u; \
	} \
	STDMETHODIMP objectClass::X##dualClass::QueryInterface( \
		REFIID iid, LPVOID* ppvObj) \
	{ \
		METHOD_PROLOGUE(objectClass, dualClass) \
		TRACE3("%s::%s::QI on %d\n",#objectClass,#dualClass,(long)(void*)pThis); \
		return pThis->ExternalQueryInterface(&iid, ppvObj); \
	} 
#endif

class CImplementUnknown
{
public:
	unsigned long STDMETHODCALLTYPE __AddRef()
	{
		ASSERT(m_lRefCount >= 0);
		return ::InterlockedIncrement(&m_lRefCount);
	};
	unsigned long STDMETHODCALLTYPE __Release()
	{
#ifdef _DEBUG
		long lRefCount = m_lRefCount;
#endif
		::InterlockedDecrement(&m_lRefCount);
		ASSERT(m_lRefCount >= 0);
		ASSERT(lRefCount);		//W4189
		return m_lRefCount;
	};
	virtual HRESULT STDMETHODCALLTYPE __QueryInterface(REFIID, void **)
	{
		ASSERT(false);
		return E_FAIL;
	};
	CImplementUnknown():
		m_lRefCount(1)
	{
	};
	const long get_ref_count() const
	{
		return m_lRefCount;
	}
private:
	long m_lRefCount;
};

#define IMPLEMENT_IUNKNOWN \
	public:	\
	CImplementUnknown m_oImplementUnknown; \
	virtual unsigned long STDMETHODCALLTYPE AddRef() { return m_oImplementUnknown.__AddRef(); } \
	virtual unsigned long STDMETHODCALLTYPE Release() \
		{ long lRefCount = m_oImplementUnknown.__Release(); \
		  if(lRefCount==0) OnFinalRelease(); return lRefCount; } \
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID a, void ** b) \
		{ return m_oImplementUnknown.__QueryInterface(a,b); } \
	virtual void OnFinalRelease() {	delete this; }	\
	bool interface_has_references() const	{ return (m_oImplementUnknown.get_ref_count() != 0); }

class CInterface__: public IUnknown		//dawniej SCInterfaceTemplate
{
public:
	IMPLEMENT_IUNKNOWN;
	IUnknown * GetUnknown()
	{
		return (IUnknown *)this;
	};
	SCP <IUnknown> GetUnknownSP()
	{
		return NewSCP <IUnknown> ((IUnknown *)this, true);
	};
protected:
	CInterface__()
	{
	};
	virtual ~CInterface__()
	{
	};
};

#define DELEGATE_UNKNOWN_ON_CMDTARGET \
	public: \
	IUnknown * GetUnknown()   { return (IUnknown *)GetIDispatch(false); }   \
	SCP <IUnknown> GetUnknownSP() { return NewSCP((IUnknown *)GetIDispatch(true)); } \
	IDispatch * GetDispatch(bool bAddRef=false) { return GetIDispatch(bAddRef); }           \
	SCP <IDispatch> GetDispatchSP() { return NewSCP(GetIDispatch(true)); } \
	unsigned long STDMETHODCALLTYPE AddRef() { return InternalAddRef();	}   \
	unsigned long STDMETHODCALLTYPE Release(){ return InternalRelease();}   \
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **pInterface) \
	{ return InternalQueryInterface(&iid, pInterface); };

#ifdef _DEBUG
#define DELEGATE_UNKNOWN_ON_CMDTARGET_TRACE \
	public: \
	IUnknown * GetUnknown()   { return (IUnknown *)GetIDispatch(false); }   \
	SCP <IUnknown> GetUnknownSP() { return NewSCP((IUnknown *)GetIDispatch(true)); } \
	IDispatch * GetDispatch(bool bAddRef=false) { return GetIDispatch(bAddRef); }           \
	SCP <IDispatch> GetDispatchSP() { return NewSCP(GetIDispatch(true)); } \
	unsigned long STDMETHODCALLTYPE AddRef() \
	{ \
		ULONG u=InternalAddRef();	\
		TRACE2("base->ADREF(%d)=%d\n",(long)(void*)this,m_dwRef); \
		return u;\
	}   \
	unsigned long STDMETHODCALLTYPE Release() \
	{ \
		ULONG u=InternalRelease();	\
		TRACE2("base->REL(%d)=%d\n",(long)(void*)this,m_dwRef); \
		return u; \
	}   \
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **pInterface) \
	{ return InternalQueryInterface(&iid, pInterface); };


class CCmdTargetInterfaceTRACE: public CCmdTarget
{
protected:
	CCmdTargetInterfaceTRACE()
	{
	};
	DELEGATE_UNKNOWN_ON_CMDTARGET_TRACE
};
#endif

#undef AFX_DATA
#ifdef THIS_IS_NAVOCORE
	#define AFX_DATA _declspec(dllexport)
#else
	#define AFX_DATA _declspec(dllimport)
#endif

class CCmdTargetInterface: public CCmdTarget
{
protected:
	CCmdTargetInterface()
	{
	};
	DELEGATE_UNKNOWN_ON_CMDTARGET
	DECLARE_DYNCREATE(CCmdTargetInterface)
};

#undef AFX_DATA
#define AFX_DATA

#else
	#error __FILE__ already included
#endif