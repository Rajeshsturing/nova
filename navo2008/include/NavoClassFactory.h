/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise 2001

	class:

	CNavoClassFactory
	sligthly improved ClassFactory
*/

#ifndef ___NAVO98CLASSFACTORY_H___
#define ___NAVO98CLASSFACTORY_H___

class CNavoClassFactory: public CCmdTargetInterface
{
public:
	CNavoClassFactory(CNavoException & roErrorContext, 
		const CLSID & rIID, LPCTSTR pcClassName, LPCTSTR pcLocalServerName,
		bool bMultipleUse = true,bool bLocalServer = true):
		m_roErrorContext(roErrorContext),
		m_ClassId(rIID),
		m_oClassName(pcClassName),
		m_bMultipleUse(bMultipleUse),
		m_bLocalServer(bLocalServer),
		m_oLocalServerPathString(pcLocalServerName),
		m_bRegistered(false),
		m_bDone(false),
		m_bRunAsService(false)
	{
	};
	~CNavoClassFactory()
	{
	};
	const CLSID	& GetCLSID() const
	{
		return m_ClassId;
	}
	void _set_run_as_service()
	{
		m_bRunAsService = true;
	}
	void _set_service_name(LPCTSTR lpServiceName)
	{
		m_oNTServiceNameString = lpServiceName;
	}
	bool _is_run_as_service() const
	{
		return m_bRunAsService;
	}
	void RegisterServer();
	void UnRegisterServer();
	void Register()
	{
		ASSERT(!m_bDone);
		ASSERT(!m_bRegistered); // drugi raz
		HRESULT hResult = ::CoRegisterClassObject(m_ClassId, &m_xClassFactory,
			CLSCTX_LOCAL_SERVER,
			m_bMultipleUse ? REGCLS_MULTIPLEUSE : REGCLS_SINGLEUSE,
			&m_dwRegister);
		if (hResult != S_OK)
		{
			ThrowNavoException1(ERCO_UNABLE_TO_REGIST_CLASS_FACTORY,IDPAGE_NOTAVAILABLE,SCODE_To_String(hResult));
		};
		m_bRegistered = true;
	};
	void Revoke()
	{
		if (!m_bRegistered)
		{
			return;
		};
		HRESULT hResult = ::CoRevokeClassObject(m_dwRegister);
		if (hResult != S_OK)
		{
			ThrowNavoException1(ERCO_UNABLE_TO_REVOKE_CLASS_OBJ,IDPAGE_NOTAVAILABLE,SCODE_To_String(hResult));
		};
		m_bRegistered = false;
	};
	void Done()
	{
		m_bDone = true;
	}
//private:
	virtual SCP <IUnknown> OnCreateObject() = 0;	//return SCP<>() when object creation impossible

	#undef  AFX_DATA
	#ifdef THIS_IS_NAVOCORE
	   #define AFX_DATA __declspec(dllexport)
	#else
	   #define AFX_DATA __declspec(dllimport)
	#endif

	DECLARE_INTERFACE_MAP();

	#undef  AFX_DATA
	#define AFX_DATA 
 
	BEGIN_INTERFACE_PART(ClassFactory, IClassFactory)
		INIT_INTERFACE_PART(CNavoClassFactory, ClassFactory)
		STDMETHOD(CreateInstance)(LPUNKNOWN iOuter, REFIID iid, LPVOID* ppObject)
		{
			METHOD_PROLOGUE(CNavoClassFactory, ClassFactory);
			ALL_TRY
			{
				if (iOuter)
				{
					return CLASS_E_NOAGGREGATION;
				};
				if(pThis->m_bDone)
				{
					return E_FAIL;
				}
				SCP <IUnknown> iUnknownSCP = pThis->OnCreateObject();
				if(!iUnknownSCP.PointsObject())
				{
					return E_FAIL;
				}
				HRESULT hResult = iUnknownSCP.SafeGet()->QueryInterface(iid, ppObject);
				return hResult;
			}
			TOP_ALL_CATCH(pThis->m_roErrorContext,DISP_E_EXCEPTION)
		};
		STDMETHOD(LockServer)(BOOL)
		{
			return E_FAIL;
		};
	END_INTERFACE_PART(ClassFactory)

	const CLSID		m_ClassId;
	const CString	m_oClassName;
	CString			m_oLocalServerPathString;
	CString			m_oNTServiceNameString;
	const bool		m_bMultipleUse;
	const bool		m_bLocalServer;
	bool			m_bRegistered;
	DWORD			m_dwRegister;
	CNavoException & m_roErrorContext;
	bool			m_bDone;
protected:
	bool			m_bRunAsService;
};

#endif