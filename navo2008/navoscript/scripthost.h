/*
	NAVO Enterprise (2001)

	ActiveX Script Engine Host
*/

#include "../include/ErrorStorage.h"
#if !defined(AFX_SCRIPTHOST_H__F1935F45_7AA8_4F11_975D_A5CB40295507__INCLUDED_)
#define AFX_SCRIPTHOST_H__F1935F45_7AA8_4F11_975D_A5CB40295507__INCLUDED_

#define _FULL_DEBUG_SUPPORT

class CNamedItemInfo;

class CScriptHostImpl : public CCmdTargetInterface
{
public:
	CScriptHostImpl(const CLSID& rClassId);
	void AddNamedItem(SCP<CNamedItemInfo>& rpoNamedItemSP);
	void Init(LPCOLESTR pScriptCode, LPCTSTR pDocumentName);
	void InitWithNXID(LPCTSTR lpNXID);

	void Invoke(const DISPID id, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);
	void Invoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL)
	{
		Invoke(DispatchGetIdOfName(m_oDispatchSCP, pocName), pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
	};
	eInvokeResult SafeInvoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL)
	{
		DISPID dispid;
		if (!SafeDispatchGetIdOfName(m_oDispatchSCP, pocName, dispid))
		{
			return invoke_notexists;
		}
		
		Invoke(dispid, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
		
		return invoke_ok;
	};
	DISPID GetDISPID(const OLECHAR* pocName) const
	{
		ASSERT(m_oDispatchSCP.PointsObject());
		return DispatchGetIdOfName(m_oDispatchSCP.ConstCastObject(), pocName);
	}
	//{{AFX_VIRTUAL(CScriptHostImpl)
	//}}AFX_VIRTUAL
	virtual ~CScriptHostImpl();
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptHostImpl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	BEGIN_INTERFACE_PART(ActiveScriptSite, IActiveScriptSite)
		HRESULT STDMETHODCALLTYPE GetItemInfo(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown** ppunkItemOut, ITypeInfo** pptinfoOut);
	HRESULT STDMETHODCALLTYPE GetDocVersionString(BSTR* pbstrVersion);
	HRESULT STDMETHODCALLTYPE GetLCID(LCID* plcid);
	HRESULT STDMETHODCALLTYPE OnScriptTerminate(const VARIANT* pvarResult, const EXCEPINFO* pexcepinfo);
	HRESULT STDMETHODCALLTYPE OnStateChange(SCRIPTSTATE ssScriptState);
	HRESULT STDMETHODCALLTYPE OnScriptError(IActiveScriptError* pscripterror);
	HRESULT STDMETHODCALLTYPE OnEnterScript(void);
	HRESULT STDMETHODCALLTYPE OnLeaveScript(void);
	END_INTERFACE_PART(ActiveScriptSite)

	BEGIN_INTERFACE_PART(ActiveScriptSiteWindow, IActiveScriptSiteWindow)
		HRESULT STDMETHODCALLTYPE GetWindow(HWND* phwnd);
	HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);
	END_INTERFACE_PART(ActiveScriptSiteWindow)

#ifdef _FULL_DEBUG_SUPPORT
	BEGIN_INTERFACE_PART(ActiveScriptSiteDebug, IActiveScriptSiteDebug)
		HRESULT STDMETHODCALLTYPE GetDocumentContextFromPosition(
			DWORD dwSourceContext, ULONG uCharacterOffset,
			ULONG uNumChars, IDebugDocumentContext** ppsc);

	HRESULT STDMETHODCALLTYPE GetApplication(IDebugApplication** ppda);

	HRESULT STDMETHODCALLTYPE GetRootApplicationNode(
		IDebugApplicationNode** ppdanRoot);

	HRESULT STDMETHODCALLTYPE OnScriptErrorDebug(
		IActiveScriptErrorDebug* pErrorDebug,
		BOOL* pfEnterDebugger,
		BOOL* pfCallOnScriptErrorWhenContinuing);
	END_INTERFACE_PART(ActiveScriptSiteDebug)
#endif

	DECLARE_INTERFACE_MAP()

public:
	CNavoException& GetErrorStorage()
	{
		return m_oErrorStorage;
	}
private:
	CString GetErrorDesc();
	HRESULT PrepareDebugging(LPCOLESTR pScriptCode);

	SCP <IActiveScript>			m_oActiveScriptSCP;
	SCP <IActiveScriptParse>	m_oActiveScriptParseSCP;
	SCP <IDispatch>				m_oDispatchSCP;
	SCP<IDebugDocumentHelper>	m_poDebugDocHelperSP;

	//error info
	EXCEPINFO					m_oExcepInfo;
	CString						m_oSourceLineTextString;
	DWORD						m_oLineNumber;
	LONG						m_lCharacterPosition;
	CString						m_oDocumentNameString;
	CGenericErrorStorage		m_oErrorStorage;

	CMap<CBStr, LPCWSTR, SCP<CNamedItemInfo>, SCP<CNamedItemInfo>& > m_oNamedItemsMap;

	friend class CScriptUser;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTHOST_H__F1935F45_7AA8_4F11_975D_A5CB40295507__INCLUDED_)
