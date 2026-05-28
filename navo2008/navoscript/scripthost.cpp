/*
	NAVO Enterprise (2001)

	ActiveX Script Engine Host
*/

#include "stdafx.h"
#include <ActivScp.h>
#include "..\navopx\navopx.h"
#include "..\include\Activdbg.h"
#include "scriptscanner.h"
#include "..\include\scriptuser.h"
#include "scripthost.h"
#include "resource.h"
#include "CompilationResultsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" const IID IID_IActiveScriptSiteDebug =
{ 0x51973C11, 0xCB0C, 0x11d0, {0xB5, 0xC9, 0x00, 0xA0, 0x24, 0x4A, 0x0E, 0x7A} };

extern HINSTANCE _h_NAVOSCRIPT_Instance;

DWORD _g_dwDebugAppCookie = 0;
SCP<IProcessDebugManager>	_g_poProcessDebugManageSP;
SCP<IDebugApplication>		_g_poDebugApplicationSP;

bool						_g_bAllowDebugging =
#ifdef _DEBUG
true;
#else
#ifdef _DEVELOPER_EDITION_
true;
#else
false;
#endif
#endif

static void _cocoon_scripthost_diag(const CString& roMessage)
{
	try
	{
		CFile oFile;
		if (!oFile.Open(_T("C:\\app\\navo-native-diagnostics.log"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			return;
		}

		oFile.SeekToEnd();
		CString oLine;
		CTime oNow = CTime::GetCurrentTime();
		oLine.Format(_T("%s [scripthost] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

static CString _cocoon_scripthost_format_params(DISPPARAMS* pDispParams)
{
	if (pDispParams == NULL)
	{
		return _T("args=null");
	}

	CString oText;
	oText.Format(_T("argc=%u"), pDispParams->cArgs);
	for (UINT iter = 0; iter < pDispParams->cArgs && pDispParams->rgvarg != NULL; iter++)
	{
		CString oArg;
		oArg.Format(_T(" arg%u_vt=0x%04x"), iter, pDispParams->rgvarg[iter].vt);
		oText += oArg;
	}
	return oText;
}

void CleanupScriptEngineEtc()
{
	if (_g_poProcessDebugManageSP.PointsObject())
	{
		_g_poProcessDebugManageSP->RemoveApplication(_g_dwDebugAppCookie);
	}

	_g_poDebugApplicationSP = 0;
	_g_poProcessDebugManageSP = 0;
}

static HRESULT CreateDebugApplication()
{
	if (!_g_bAllowDebugging)
	{
		return S_OK;
	}
#ifdef _DEBUG
	{
		CString oDenyString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(), _T("DenyScriptDebugger"), oDenyString);
		if (oDenyString == "Y")
		{
			_g_bAllowDebugging = FALSE;
			return S_OK;
		}
	}
#endif
	{
		CString oAllowString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(), _T("AllowScriptDebugger"), oAllowString);
		if (oAllowString != "188cb150-82a4-4498-87d0-ebd8d9a00fb8")
		{
			ASSERT(false);		//masz nieprawid³owy wpis w registry
			_g_bAllowDebugging = FALSE;
			return S_OK;
		}
	}
	if (_g_poProcessDebugManageSP.PointsNull())
	{
		try
		{
			_g_poProcessDebugManageSP.CreateInstance(CLSID_ProcessDebugManager,
				CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER);
		}
		catch (...)
		{
			return E_FAIL;
		}
		HRESULT hr = _g_poProcessDebugManageSP->CreateApplication(&_g_poDebugApplicationSP.GetRawPointer());
		if (hr != S_OK)
		{
			return hr;
		}
		ASSERT(_g_poDebugApplicationSP.PointsObject());
		hr = _g_poDebugApplicationSP->SetName(L"NAVO Enterprise 2023");
		if (hr != S_OK)
		{
			return hr;
		}
		hr = _g_poProcessDebugManageSP->AddApplication(_g_poDebugApplicationSP, &_g_dwDebugAppCookie);
		if (hr != S_OK)
		{
			return hr;
		}
	}
	return S_OK;
}

BEGIN_INTERFACE_MAP(CScriptHostImpl, CCmdTargetInterface)
	INTERFACE_PART(CScriptHostImpl, IID_IActiveScriptSite, ActiveScriptSite)
	INTERFACE_PART(CScriptHostImpl, IID_IActiveScriptSiteWindow, ActiveScriptSiteWindow)
#ifdef _FULL_DEBUG_SUPPORT
	INTERFACE_PART(CScriptHostImpl, IID_IActiveScriptSiteDebug, ActiveScriptSiteDebug)
#endif
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CScriptHostImpl, ActiveScriptSite)
DELEGATE_UNKNOWN_INTERFACE(CScriptHostImpl, ActiveScriptSiteWindow)
#ifdef _FULL_DEBUG_SUPPORT
DELEGATE_UNKNOWN_INTERFACE(CScriptHostImpl, ActiveScriptSiteDebug)
#endif

CScriptHostImpl::CScriptHostImpl(const CLSID& rClassId) :
	m_oActiveScriptSCP(rClassId, CLSCTX_ALL),
	m_oLineNumber(0),
	m_lCharacterPosition(0)
{
	EnableAutomation();
	VERIFY(CreateDebugApplication() == S_OK);
	m_oActiveScriptParseSCP.QueryInterface(m_oActiveScriptSCP);

	HRESULT hr = m_oActiveScriptSCP->SetScriptSite(&m_xActiveScriptSite);
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_SETSCRIPTSITE_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	};
	hr = m_oActiveScriptParseSCP->InitNew();
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_SCRIPT_INIT_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}
	memset((LPVOID)&m_oExcepInfo, 0, sizeof(m_oExcepInfo));
}

HRESULT CScriptHostImpl::PrepareDebugging(LPCOLESTR pScriptCode)
{
	if (!_g_bAllowDebugging)
	{
		return S_OK;
	}
	ASSERT(_g_poProcessDebugManageSP.PointsObject());
	//TO_DO maybe addref na debug application
	HRESULT hr = _g_poProcessDebugManageSP->CreateDebugDocumentHelper(NULL, &m_poDebugDocHelperSP.GetRawPointer());
	if (hr != S_OK)
	{
		return hr;
	}
	CBStr oDocumentNameBstr(m_oDocumentNameString);
	ASSERT(_g_poDebugApplicationSP.PointsObject());
	hr = m_poDebugDocHelperSP->Init(_g_poDebugApplicationSP, oDocumentNameBstr, oDocumentNameBstr, TEXT_DOC_ATTR_READONLY);
	if (hr != S_OK)
	{
		return hr;
	}
	hr = m_poDebugDocHelperSP->Attach(NULL);
	if (hr != S_OK)
	{
		return hr;
	}
	hr = m_poDebugDocHelperSP->AddUnicodeText(pScriptCode);
	if (hr != S_OK)
	{
		return hr;
	}
	ULONG scriptLength = wcslen(pScriptCode);
	DWORD dwNothing;
	hr = m_poDebugDocHelperSP->DefineScriptBlock(0, scriptLength, m_oActiveScriptSCP, FALSE, &dwNothing);
	if (hr != S_OK)
	{
		return hr;
	}
	return S_OK;
}

void CScriptHostImpl::AddNamedItem(SCP<CNamedItemInfo>& rpoNamedItemSP)
{
	m_oNamedItemsMap[rpoNamedItemSP->GetName()] = rpoNamedItemSP;

	HRESULT hr = m_oActiveScriptSCP->AddNamedItem(rpoNamedItemSP->GetName(), SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);
	
	if (S_OK != hr)
	{
		ThrowNavoException2(ERCO_SCRIPTENGINE_ADDNAMEFAILED, IDPAGE_NOTAVAILABLE,
			CString(rpoNamedItemSP->GetName()), hr);
	}
}

void CScriptHostImpl::Init(LPCOLESTR pScriptCode, LPCTSTR pDocumentName)
{
	m_oDocumentNameString = CString(pDocumentName);

	VERIFY(PrepareDebugging(pScriptCode) == S_OK);

	HRESULT hr = m_oActiveScriptParseSCP->ParseScriptText(pScriptCode, NULL, NULL, NULL, 0, 0,
		SCRIPTTEXT_ISPERSISTENT, NULL, &m_oExcepInfo);
	if (hr != S_OK)
	{
		ThrowNavoException2(ERCO_SCRIPTENGINE_PARSINGFAILED, IDPAGE_NOTAVAILABLE, (LPCTSTR)GetErrorDesc(),
			SCODE_To_String(hr));
	};
	hr = m_oActiveScriptSCP->SetScriptState(SCRIPTSTATE_CONNECTED);
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_SETSCRIPTSTATE_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	};
	hr = m_oActiveScriptSCP->GetScriptDispatch(NULL, &m_oDispatchSCP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_GETSCRIPTDISPATCH_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	};
	ASSERT(m_oDispatchSCP.PointsObject());
}

void CScriptHostImpl::InitWithNXID(LPCTSTR lpNXID)
{
	SCP<CNamedItemInfo> rpoNamedItemSP;

	if (m_oNamedItemsMap.Lookup(CBStr("nx_"), rpoNamedItemSP))
	{
		DISPID dispid = DispatchGetIdOfName(rpoNamedItemSP->Dispatch(), "module_provider");
		EXCEPINFO ei;
		CSmartOleVariant oNXIDSOV = lpNXID;

		CSmartOleVariant oResultSOV;
		HRESULT hResult = DispatchInvoke(rpoNamedItemSP->Dispatch(), dispid, &oNXIDSOV, 1, &oResultSOV, &ei);

		if (hResult != S_OK)
		{
			ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED, IDPAGE_NOTAVAILABLE, (LPCTSTR)GetErrorDesc(),
				SCODE_To_String(hResult));
		};

		m_oDispatchSCP = NewSCP(oResultSOV.GetDispatch());
		dispid = DispatchGetIdOfName(m_oDispatchSCP, "add_named_item");

		for (POSITION pos = m_oNamedItemsMap.GetStartPosition(); pos != NULL;)
		{
			CBStr strKey;
			SCP<CNamedItemInfo> poNamedItemSP;
			m_oNamedItemsMap.GetNextAssoc(pos, strKey, poNamedItemSP);

			// Execute selected code using data from the map
			CSmartOleVariant oArgumentSOVArray[2];
			oArgumentSOVArray[1] = CSmartOleVariant(poNamedItemSP->GetName());
			oArgumentSOVArray[0] = CSmartOleVariant(poNamedItemSP->Dispatch(), false);

			hResult = DispatchInvoke(m_oDispatchSCP, dispid, oArgumentSOVArray, 2, NULL, &ei);
		}

		ASSERT(m_oDispatchSCP.PointsObject());
	}
}

void CScriptHostImpl::Invoke(const DISPID id, CSmartOleVariant* pArgumentsSOV, long lSize, CSmartOleVariant* poResultSOV)
{
	ALL_TRY
	{
		EXCEPINFO ei;

		HRESULT hResult = DispatchInvoke(m_oDispatchSCP, id, pArgumentsSOV, lSize, poResultSOV, &ei);
		
		if (hResult != S_OK)
		{
			ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED, IDPAGE_NOTAVAILABLE, (LPCTSTR)GetErrorDesc(),
				SCODE_To_String(hResult));
		};
	}
	TOP_ALL_CATCH_(GetErrorStorage());
}

CScriptHostImpl::~CScriptHostImpl()
{
	m_oDispatchSCP = 0;

	ALL_TRY
	{

		HRESULT hResult = m_oActiveScriptSCP->Close();

#ifdef _DEBUG
		ASSERT(hResult == S_OK);
		SCRIPTSTATE ss;
		hResult = m_oActiveScriptSCP->GetScriptState(&ss);
		ASSERT(SCRIPTSTATE_CLOSED == ss);
		UNUSED_ALWAYS(hResult);
#endif

	}
	TOP_ALL_CATCH_(GetErrorStorage());
}

CString CScriptHostImpl::GetErrorDesc()
{
	CString oFullErrorString;
	oFullErrorString.Format(_T("%s:%s\r\nplik %s:linia=%d,znak=%d,tekst=\r\n[%s]"),
		CString(m_oExcepInfo.bstrSource),
		CString(m_oExcepInfo.bstrDescription),
		m_oDocumentNameString,
		m_oLineNumber,
		m_lCharacterPosition,
		m_oSourceLineTextString);

	return oFullErrorString;
}

/////////-------------------------------------------------

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::
GetItemInfo(LPCOLESTR lpItemName, DWORD dwReturnMask, IUnknown** ppIUnknown,
	ITypeInfo** ppTypeInfo)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
		{
			if (ppTypeInfo == NULL)
			{
				return E_INVALIDARG;
			}
			*ppTypeInfo = NULL;
		}

	if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
	{
		if (ppIUnknown == NULL)
		{
			return E_INVALIDARG;
		}
		*ppIUnknown = NULL;
	}

	SCP<CNamedItemInfo> poNamedItemSP;
	if (!pThis->m_oNamedItemsMap.Lookup(lpItemName, poNamedItemSP))
	{
		return TYPE_E_ELEMENTNOTFOUND;
	}
	ASSERT(poNamedItemSP.PointsObject());
	if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
	{
		if (poNamedItemSP->TypeInfo())
		{
			poNamedItemSP->TypeInfo()->AddRef();
			*ppTypeInfo = poNamedItemSP->TypeInfo();
		}
	}
	if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
	{
		ASSERT(poNamedItemSP->Dispatch());	//IDispatch is a must
		poNamedItemSP->Dispatch()->AddRef();
		*ppIUnknown = poNamedItemSP->Dispatch();
	}
	return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::GetDocVersionString(BSTR*)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		return E_NOTIMPL;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::GetLCID(LCID* pLCID)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		ASSERT(pLCID);
	(*pLCID) = GetWorkingLCID();
	return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::OnScriptTerminate(const VARIANT*, const EXCEPINFO* /*pExcepInfo*/)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::OnStateChange(SCRIPTSTATE)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::OnScriptError(IActiveScriptError* pScriptError)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)

		CBStr oErrorLineTextBStr;
	HRESULT hr = pScriptError->GetSourceLineText(&oErrorLineTextBStr.GetRawPointer());
	if (hr == S_OK)
	{
		pThis->m_oSourceLineTextString = CString(oErrorLineTextBStr);
		TRACE1("Script error line=%s\n", pThis->m_oSourceLineTextString);
	}
	DWORD dwSourceContext;
	hr = pScriptError->GetSourcePosition(&dwSourceContext,
		&pThis->m_oLineNumber, &pThis->m_lCharacterPosition);
	ASSERT(hr == S_OK);
	hr = pScriptError->GetExceptionInfo(&pThis->m_oExcepInfo);
	return E_FAIL;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::OnEnterScript()
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSite::OnLeaveScript()
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSite)
		return S_OK;
};

STDMETHODIMP CScriptHostImpl::XActiveScriptSiteWindow::GetWindow(HWND* phWindow)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSiteWindow)
		ASSERT(AfxGetThread());
	if (AfxGetThread()->m_pMainWnd)
	{
		*phWindow = AfxGetThread()->m_pMainWnd->m_hWnd;
	}
	else
	{
		/*
			to jest wymagane, gdy skrypt wykonuje siê bez UI, a chce wyœwietliæ
			komunikat (msg box)
		*/
		*phWindow = ::GetDesktopWindow();
	}
	return S_OK;
}

STDMETHODIMP CScriptHostImpl::XActiveScriptSiteWindow::EnableModeless(BOOL bEnable)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSiteWindow)
		HWND hWnd;
	GetWindow(&hWnd);
	::EnableWindow(hWnd, bEnable);
	return S_OK;
}

#ifdef _FULL_DEBUG_SUPPORT
STDMETHODIMP CScriptHostImpl::XActiveScriptSiteDebug::
GetDocumentContextFromPosition(DWORD dwSourceContext, ULONG uCharacterOffset,
	ULONG uNumChars, IDebugDocumentContext** ppsc)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSiteDebug)

		ASSERT(pThis->m_poDebugDocHelperSP.PointsObject());
	ULONG ulStartPos;
	HRESULT hr = pThis->m_poDebugDocHelperSP->GetScriptBlockInfo(dwSourceContext, NULL,
		&ulStartPos, NULL);
	if (hr != S_OK)
	{
		return hr;
	}
	return pThis->m_poDebugDocHelperSP->CreateDebugDocumentContext(
		ulStartPos + uCharacterOffset, uNumChars, ppsc);
}

STDMETHODIMP CScriptHostImpl::XActiveScriptSiteDebug::GetApplication(IDebugApplication** ppda)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSiteDebug)

		if (!_g_bAllowDebugging)
		{
			return E_NOTIMPL;
		}
	ASSERT(_g_poDebugApplicationSP.PointsObject());
	*ppda = _g_poDebugApplicationSP.Get();
	return S_OK;
}

STDMETHODIMP CScriptHostImpl::XActiveScriptSiteDebug::GetRootApplicationNode(
	/* [out] */ IDebugApplicationNode** ppdanRoot)
{
	METHOD_PROLOGUE(CScriptHostImpl, ActiveScriptSiteDebug)
		ASSERT(_g_poDebugApplicationSP.PointsObject());
	return _g_poDebugApplicationSP->GetRootNode(ppdanRoot);
}

STDMETHODIMP CScriptHostImpl::XActiveScriptSiteDebug::OnScriptErrorDebug(
	IActiveScriptErrorDebug* /*pErrorDebug*/, BOOL* pfEnterDebugger,
	BOOL* pfCallOnScriptErrorWhenContinuing)
{
	*pfEnterDebugger = TRUE;
	*pfCallOnScriptErrorWhenContinuing = TRUE;
	return _g_bAllowDebugging ? S_OK : E_NOTIMPL;
}
#endif
//-------------------------------------------------------------------------------
//	implementation hiding envelope
//-------------------------------------------------------------------------------
CScriptHost::CScriptHost(bool bVB)
{
	m_poImplementation = new CScriptHostImpl(bVB ? CLSID_VBSCRIPT : CLSID_JSCRIPT);
}

CScriptHost::~CScriptHost()
{
	delete m_poImplementation;
}

void CScriptHost::AddNamedItem(SCP<CNamedItemInfo>& rpoNamedItemSP)
{
	ASSERT(m_poImplementation);
	m_poImplementation->AddNamedItem(rpoNamedItemSP);
}

void CScriptHost::Init(LPCOLESTR pScriptCode, LPCTSTR pDocumentName)
{
	ASSERT(m_poImplementation);
	m_poImplementation->Init(pScriptCode, pDocumentName);
}

void CScriptHost::InitWithNXID(LPCTSTR lpNXID)
{
	ASSERT(m_poImplementation);
	m_poImplementation->InitWithNXID(lpNXID);
}

void CScriptHost::Invoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant)
{
	ASSERT(m_poImplementation);
	m_poImplementation->Invoke(pocName, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
}

eInvokeResult CScriptHost::SafeInvoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant)
{
	ASSERT(m_poImplementation);
	return m_poImplementation->SafeInvoke(pocName, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
}

void CScriptHost::Invoke(DISPID dispid, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant)
{
	ASSERT(m_poImplementation);
	m_poImplementation->Invoke(dispid, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
}

DISPID CScriptHost::GetDISPID(const OLECHAR* pocName)
{
	ASSERT(m_poImplementation);

	return m_poImplementation->GetDISPID(pocName);
}

//-----------------------------------------------------
void CScriptUser::_InitScript()
{
	if (m_poScriptHostSP.PointsNull())
	{
		ASSERT(!m_bCompiled);

		//_Compile();
		CString strScriptCode(GetScriptCode());
		CString strNXID(GetScriptNXID());

		m_poScriptHostSP = NewSCP(new CScriptHost());

		_PushNamedItems();

		if (!strNXID.IsEmpty())
		{
			m_poScriptHostSP->InitWithNXID(strNXID);
		}
		else
		{
			CString oDocNameString;
			GetDocumentName(oDocNameString);
			m_poScriptHostSP->Init(CBStr(strScriptCode), oDocNameString);
		}

		for (long iter = 0; iter <= m_oFunctionsArray.GetUpperBound(); iter++)
		{
			DISPID dispid = m_poScriptHostSP->GetDISPID(CBStr(m_oFunctionsArray[iter].m_oNameString));
			m_oFunctionsArray[iter].m_dispid = dispid;
		}
	}
}

void CScriptUser::_Compile()
{
	if (m_bCompiled)
	{
		return;
	}

#ifdef _DEVELOPER_EDITION_

	CString oAllowString;
	SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(), _T("TurnOnVBSCompiler"), oAllowString);
	oAllowString.MakeUpper();
	if (oAllowString != "Y")
	{
		return;
	}

	SCP<IScriptCompiler> poCompilerSP;
	try
	{
		poCompilerSP.CreateInstance(CLSID_NAVO2002VBSCompiler, CLSCTX_ALL);
	}
	catch (...)
	{
		AfxMessageBox("Znaleziono wpis w registry TurnOnVBSCompiler='Y' jednak nie uda³o siê uruchomiæ sprawdzacza kodu!!!!\nPrawdopodobnie nie zarejestrowana biblioteka NAVOVBSC lub jej brak.");
		return;
	}

	if (!poCompilerSP.PointsObject())
	{
		AfxMessageBox("Znaleziono wpis w registry TurnOnVBSCompiler='Y' jednak nie uda³o siê uruchomiæ sprawdzacza kodu!!!!\nPrawdopodobnie nie zarejestrowana biblioteka lub jej brak.");
		return;
	}

	VERIFY(S_OK == poCompilerSP->SetSourceText(GetScriptCode()));
	long iter = 0;
	for (iter = 0; iter <= m_oNIIArray.GetUpperBound(); iter++)
	{
		VERIFY(S_OK == poCompilerSP->DeclareIdent(CString(m_oNIIArray[iter]->GetName())));
	}
	//retrieve errors
	CString oResultsString;
	CString oSourceString;
	GetDocumentName(oResultsString);
	bool bShowResults = false;
	if (poCompilerSP->Compile() != S_OK)
	{
		oResultsString += " FAILED !\r\n=========================================\r\n";
		bShowResults = true;
	}
	else
	{
		oResultsString += " OK!\r\n***********************************\r\n";
	}
	CNavoException oNavoException;
	GetErrorInfoFromInterface(poCompilerSP, oNavoException);

	CNavoExceptionAccessor oNEA(oNavoException);

	for (iter = 0; iter <= oNEA.ErrorInfoArray().GetUpperBound(); iter++)
	{
		long nLineNr = oNEA.ErrorInfoArray()[iter].GetHelpId();
		oResultsString += oNEA.ErrorInfoArray()[iter].GetErrorString() + CString("\r\n");
		long nStart;
		if (S_OK == poCompilerSP->GetLine(nLineNr, &nStart))
		{
			CString oString(GetScriptCode() + nStart, 256);
			oString.Replace("\n", "\r\n");
			oSourceString +=
				"=============== line " + Long2String(nLineNr) + "\r\n" + oString + "\r\n";
		}
		bShowResults = true;
	}
	if (bShowResults)
	{
		CAfxResourceHandleHolder oARHH(_h_NAVOSCRIPT_Instance);
		CCompilationResultsDialog oCRDialog(CWnd::GetActiveWindow());
		oCRDialog.m_oResultsString = oResultsString;
		oCRDialog.m_oSourceString = oSourceString;
		oCRDialog.DoModal();
	}

#endif
	m_bCompiled = true;
}

void CScriptUser::_PushNamedItems()
{
	for (long iter = 0; iter <= m_oNIIArray.GetUpperBound(); iter++)
	{
		m_poScriptHostSP->AddNamedItem(m_oNIIArray[iter]);
	}
	m_oNIIArray.RemoveAll();
}

DISPID CScriptUser::GetDISPID(const OLECHAR* pcFunctionName)
{
	CString oString(pcFunctionName);
	for (long iter = 0; iter <= m_oFunctionsArray.GetUpperBound(); iter++)
	{
		if (m_oFunctionsArray[iter].m_oNameString == oString)
		{
			ASSERT(m_oFunctionsArray[iter].m_dispid != DISPID_NONE);
			return m_oFunctionsArray[iter].m_dispid + m_nTranslateBy_DISPID;
		}
	}
	return DISPID_NONE;
}

HRESULT CScriptUser::__GetIDsOfNames(LPOLESTR* rgszNames, UINT cNames, DISPID* rgDispId)
{
	UINT nOriginalNames = cNames;
	CString oName;
	if (rgszNames != NULL && cNames > 0 && rgszNames[0] != NULL)
	{
		oName = rgszNames[0];
	}

	_InitScript();
	HRESULT hr = S_OK;
	while (cNames)
	{
		rgDispId[cNames - 1] = GetDISPID(rgszNames[cNames - 1]);
		if (rgDispId[cNames - 1] == DISPID_NONE)
		{
			hr = DISP_E_UNKNOWNNAME;
			break;
		}
		cNames--;
	}

	CString oDiag;
	oDiag.Format(_T("__GetIDsOfNames nxid=%s name=%s hr=0x%08lx dispid=%ld cNames=%u functions=%ld"),
		GetScriptNXID(), (LPCTSTR)oName, hr,
		(rgDispId != NULL && nOriginalNames > 0) ? rgDispId[0] : -1,
		nOriginalNames, m_oFunctionsArray.GetSize());
	_cocoon_scripthost_diag(oDiag);

	return hr;
}

HRESULT CScriptUser::__Invoke(DISPID dispId, REFIID riid, LCID lCid, WORD wFlags,
	DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExceptInfo, UINT* puArgError)
{
	dispId -= m_nTranslateBy_DISPID;
	ASSERT(m_poScriptHostSP.PointsObject());
	for (long iter = 0; iter <= m_oFunctionsArray.GetUpperBound(); iter++)
	{
		if (m_oFunctionsArray[iter].m_dispid == dispId)
		{
			CString oFunctionName = m_oFunctionsArray[iter].m_oNameString;
			CString oBeginDiag;
			oBeginDiag.Format(_T("__Invoke begin nxid=%s function=%s dispid=%ld wFlags=0x%04x %s"),
				GetScriptNXID(), (LPCTSTR)oFunctionName, dispId, wFlags,
				(LPCTSTR)_cocoon_scripthost_format_params(pDispParams));
			_cocoon_scripthost_diag(oBeginDiag);

			ASSERT(m_oNIIArray.GetSize() == 0); //name added too late
			HRESULT hr = m_poScriptHostSP->m_poImplementation->m_oDispatchSCP->
				Invoke(dispId, riid, lCid, wFlags, pDispParams, pVarResult, pExceptInfo, puArgError);

			CString oSource;
			CString oDescription;
			SCODE scode = 0;
			WORD wCode = 0;
			VARTYPE vtResult = VT_EMPTY;
			if (pVarResult != NULL)
			{
				vtResult = pVarResult->vt;
			}
			if (pExceptInfo != NULL)
			{
				if (pExceptInfo->bstrSource != NULL)
				{
					oSource = pExceptInfo->bstrSource;
				}
				if (pExceptInfo->bstrDescription != NULL)
				{
					oDescription = pExceptInfo->bstrDescription;
				}
				scode = pExceptInfo->scode;
				wCode = pExceptInfo->wCode;
			}

			CString oEndDiag;
			oEndDiag.Format(_T("__Invoke end nxid=%s function=%s hr=0x%08lx result_vt=0x%04x wCode=%u scode=0x%08lx source=%s desc=%s"),
				GetScriptNXID(), (LPCTSTR)oFunctionName, hr, vtResult, wCode, scode,
				(LPCTSTR)oSource, (LPCTSTR)oDescription);
			_cocoon_scripthost_diag(oEndDiag);
			return hr;
		}
	}

	CString oDiag;
	oDiag.Format(_T("__Invoke member not found nxid=%s dispid=%ld wFlags=0x%04x"),
		GetScriptNXID(), dispId, wFlags);
	_cocoon_scripthost_diag(oDiag);
	return DISP_E_MEMBERNOTFOUND;
}

void CScriptUser::Invoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant)
{
	_InitScript();
	ASSERT(m_poScriptHostSP.PointsObject());
	m_poScriptHostSP->Invoke(pocName, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
}

eInvokeResult CScriptUser::SafeInvoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant)
{
	_InitScript();
	ASSERT(m_poScriptHostSP.PointsObject());
	return m_poScriptHostSP->SafeInvoke(pocName, pArgumentsSmartOleVariant, lSize, poResultSmartOleVariant);
}

