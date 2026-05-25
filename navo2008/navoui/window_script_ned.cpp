/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	window

	scripting
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "element_nedaw.h"
#include "window_ned.h"
#include "transfer_nedaw.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOUI_Instance;

static long _g_aStdCmdCode[] =
{
	IDR_SC_FBACK,		//CMD_GOBACK
	IDR_SC_FNEW,		//CMD_NEWFORM
	IDR_SC_FSAVE,		//CMD_SAVEFORM
	IDR_SC_FPRINT,		//CMD_PRINT
	0,					//CMD_NEXTLOGICAL
	0,					//CMD_PREVLOGICAL
	IDR_SC_FUNDO,		//CMD_UNDO
	IDR_SC_FFIRST,		//CMD_FIRSTINCURSOR
	IDR_SC_FPREV,		//CMD_PREVINCURSOR
	IDR_SC_FNEXT,		//CMD_NEXTINCURSOR
	IDR_SC_FLAST,		//CMD_LASTINCURSOR
	0,					//CMD_HELP
	IDR_SC_FCOPY,		//CMD_COPY
	IDR_SC_FPASTE,		//CMD_PASTE
	0,					//CMD_OPTIONS
	0,					//CMD_REFRESH
	IDR_SC_FDELETE,		//CMD_DELETEFORM
	IDR_SC_FPRINTPREVIEW,//CMD_PRINTPREVIEW
	IDR_SC_FSEARCH,		//CMD_SEARCH
	0,					//CMD_QUIT
	0,					//CMD_FOPEN
	0,					//CMD_FCLOSE
	IDR_SC_FSAVEPAGE,	//CMD_SAVEPAGE
	IDR_SC_FENABLEEDIT,	//CMD_ENABLEEDIT
};

static void load_std_code(long Ident, ng_string& roString)
{
	HRSRC hRsrc = ::FindResource(_h_NAVOUI_Instance, MAKEINTRESOURCE(Ident), _T("STDCODE"));
	ASSERT(hRsrc != HRSRC(NULL));
	HGLOBAL hGlobal = ::LoadResource(_h_NAVOUI_Instance, hRsrc);
	ASSERT(hGlobal != HGLOBAL(NULL));
	LPVOID pData = ::LockResource(hGlobal);
	ASSERT(pData != NULL);
	roString = (LPCTSTR)pData;
}

inline static bool _is_std_command_code(long IdCmd)
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	return (_g_aStdCmdCode[IdCmd - CMD_STANDARDFIRST] != 0);
}

inline static void _get_std_command_code(long IdCmd, ng_string& roString)
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	ASSERT(_is_std_command_code(IdCmd));

	load_std_code(_g_aStdCmdCode[IdCmd - CMD_STANDARDFIRST], roString);
}


inline static long find_function_name(CFunctionInfoArray& roFunctionArray, const ng_string& roNameString)
{
	for (long iter = 0; iter <= roFunctionArray.GetUpperBound(); iter++)
	{
		if (roFunctionArray[iter].m_oNameString.CompareNoCase(roNameString) == 0)
		{
			return iter;
		}
	}
	return -1;
}


void cned_window::GetDocumentName(ng_string& roDocNameString)
{
	get_prop_official_title(roDocNameString);
}

struct StdCmdInfo
{
	LPCTSTR m_lpCmdName;
	long	m_nIdCmd;
};

/*
	IMPORTANT!
	kolejnoœæ musi byæ taka sama jak wartoœci CMD_*
	order in array must match CMD_* values (CMD_GOBACK == CMD_STANDARDFIRST)
*/

static StdCmdInfo _g_aStdCmdInfo[] =
{
	{ _T("fback"),			CMD_GOBACK		},
	{ _T("fnew"),			CMD_NEWFORM		},
	{ _T("fsave"),			CMD_SAVEFORM	},
	{ _T("fprint"),			CMD_PRINT		},
	{ NULL,					CMD_NEXTLOGICAL	},
	{ NULL,					CMD_PREVLOGICAL	},
	{ _T("fundo"),			CMD_UNDO		},
	{ _T("ffirst"),			CMD_FIRSTINCURSOR	},
	{ _T("fprev"),			CMD_PREVINCURSOR},
	{ _T("fnext"),			CMD_NEXTINCURSOR},
	{ _T("flast"),			CMD_LASTINCURSOR},
	{ _T("fhelp"),			CMD_HELP		},
	{ _T("fcopy"),			CMD_COPY		},
	{ _T("fpaste"),			CMD_PASTE		},
	{ _T("foptions"),		CMD_OPTIONS		},
	{ _T("frefresh"),		CMD_REFRESH		},
	{ _T("fdelete"),		CMD_DELETEFORM	},
	{ _T("fprintpreview"),	CMD_PRINTPREVIEW},
	{ _T("fsearch"),		CMD_SEARCH		},
	{ NULL,					CMD_QUIT		},
	{ _T("fopen"),			CMD_FOPEN		},
	{ _T("fclose"),			CMD_FCLOSE		},
	{ _T("fsavepage"),		CMD_SAVEPAGE	},
	{ _T("fenableedit"),	CMD_ENABLEEDIT	},
};

inline static LPCTSTR _get_std_command_name(long IdCmd)
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	return _g_aStdCmdInfo[IdCmd - CMD_STANDARDFIRST].m_lpCmdName;
}

void cned_window::setup_defaults(long IdPageTypeCmd, bool bWithCursor)
{
	//------- supply default scripts --------------------

	//for every page
	if (IdPageTypeCmd == CMD_OPEN_MODULE_PAGE)
	{
		return;
	}
	ng_string oStdCodeEveryString;
	load_std_code(IDR_SC_EVERY, oStdCodeEveryString);
	m_oScriptCodeString += oStdCodeEveryString;

	if (!get_prop_is_stdcmd(CMD_SAVEPAGE))
	{
		ng_string oString;
		_get_std_command_code(CMD_SAVEPAGE, oString);
		m_oScriptCodeString += oString;
		set_prop_is_stdcmd(CMD_SAVEPAGE, true);
	}
	if (!get_prop_is_stdcmd(CMD_PRINT))
	{
		ng_string oString;
		_get_std_command_code(CMD_PRINT, oString);
		m_oScriptCodeString += oString;
		set_prop_is_stdcmd(CMD_PRINT, true);
	}
	if (!get_prop_is_stdcmd(CMD_PRINTPREVIEW))
	{
		ng_string oString;
		_get_std_command_code(CMD_PRINTPREVIEW, oString);
		m_oScriptCodeString += oString;
		set_prop_is_stdcmd(CMD_PRINTPREVIEW, true);
	}
	if (!get_prop_is_stdcmd(CMD_COPY))
	{
		ng_string oString;
		_get_std_command_code(CMD_COPY, oString);
		m_oScriptCodeString += oString;
		set_prop_is_stdcmd(CMD_COPY, true);
	}


	m_oFunctionsArray.Add(CFunctionInfo(_get_std_command_name(CMD_SAVEPAGE), true));
	m_oFunctionsArray.Add(CFunctionInfo(_get_std_command_name(CMD_PRINT), true));
	m_oFunctionsArray.Add(CFunctionInfo(_get_std_command_name(CMD_PRINTPREVIEW), true));
	m_oFunctionsArray.Add(CFunctionInfo(_get_std_command_name(CMD_COPY), true));

	//for form page
	if (get_prop_root_typeid() != 0)
	{
		//for commands which are not supplied by programmer, inject standard implementation

		ng_string oInjectString;
		load_std_code(IDR_SC_FORM, oInjectString);

		for (long IdCmd = CMD_STANDARDFIRST; IdCmd <= CMD_STANDARDLAST; IdCmd++)
		{
			//jeœli nie ma komendy dostarczonej przez programistê dostarcz wbudowan¹
			if (!get_prop_is_stdcmd(IdCmd) && _is_std_command_code(IdCmd) != NULL)
			{
				//wyj¹tkiem jest strona typu wizzard, której dostarczamy inny fback
				if (IdCmd == CMD_GOBACK && CMD_OPEN_WIZARD_PAGE == IdPageTypeCmd)
				{
					ng_string oString;
					load_std_code(IDR_SC_FBACKWIZ, oString);
					oInjectString += oString;
				}
				else
				{
					ng_string oString;
					_get_std_command_code(IdCmd, oString);
					oInjectString += oString;
				}

				set_prop_is_stdcmd(IdCmd, true);
				m_oFunctionsArray.Add(CFunctionInfo(_get_std_command_name(IdCmd), true));
			}
		}
		if (!oInjectString.IsEmpty())
		{
			m_oScriptCodeString += oInjectString;
		}
	}

	if (m_bExistsSuggestionTransfer)
	{
		ng_string oString;
		load_std_code(IDR_SC_SUGG, oString);
		m_oScriptCodeString += oString;
	}

	//ned_to_do: if(m_poElementManagerSP->_was_element_with_script_support())
	{
		if (find_function_name(m_oFunctionsArray, _T("fcontrol")) < 0)
		{
			ng_string oString;
			load_std_code(IDR_SC_STD_CONTROL_SUPP, oString);
			m_oScriptCodeString += oString;
			m_oFunctionsArray.Add(CFunctionInfo(_T("fcontrol"), true));
		}
	}

	//------------- setup buttons ---------------------------
	set_prop_button_visible(CMD_GOBACK, true);
	set_prop_button_visible(CMD_PRINT, true);
	set_prop_button_visible(CMD_PRINTPREVIEW, true);
	set_prop_button_visible(CMD_HELP, true);
	set_prop_button_visible(CMD_COPY, true);
	set_prop_button_visible(CMD_SAVEPAGE, true);

	switch (IdPageTypeCmd)
	{
	case CMD_OPEN_STATIC_PAGE:
		break;
	case CMD_OPEN_RECORD_PAGE:
		set_prop_button_visible(CMD_NEWFORM, true);
		set_prop_button_visible(CMD_SAVEFORM, true);
		set_prop_button_visible(CMD_DELETEFORM, true);
		set_prop_button_visible(CMD_REFRESH, true);
		set_prop_button_visible(CMD_UNDO, true);
		set_prop_button_visible(CMD_ENABLEEDIT, true);
		set_prop_button_visible(CMD_PASTE, true);
		if (bWithCursor)
		{
			set_prop_button_visible(CMD_FIRSTINCURSOR, true);
			set_prop_button_visible(CMD_PREVINCURSOR, true);
			set_prop_button_visible(CMD_NEXTINCURSOR, true);
			set_prop_button_visible(CMD_LASTINCURSOR, true);
			set_prop_button_visible(CMD_SEARCH, true);
		}
		break;
	case CMD_OPEN_OLEDOC_PAGE:
		set_prop_button_visible(CMD_SAVEFORM, true);
		break;
	case CMD_OPEN_WIZARD_PAGE:
		set_prop_button_visible(CMD_SAVEFORM, true);
		break;
	default:
		ASSERT(false);
	}
}


static void _cocoon_window_script_diag(const CString & roMessage)
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
		oLine.Format(_T("%s [window_script_ned] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

void cned_window::set_prop_script(const ng_string& roScriptCodeString)
{
	m_oScriptCodeString = ng_string(_T("Option Explicit\r\n")) + roScriptCodeString;

	//scan for std function existence
	m_oFunctionsArray.RemoveAll();
	ScanScriptForProcedures(m_oScriptCodeString, m_oFunctionsArray);

	CString oDiag;
	oDiag.Format(_T("set_prop_script len=%d raw_len=%d has_app_onstart_text=%d function_count=%d app_onstart_index=%d"),
		m_oScriptCodeString.GetLength(),
		roScriptCodeString.GetLength(),
		m_oScriptCodeString.Find(_T("app_onstart")) >= 0,
		m_oFunctionsArray.GetSize(),
		find_function_name(m_oFunctionsArray, _T("app_onstart")));
	_cocoon_window_script_diag(oDiag);

	//detect and mark programmer defined versions of standard commands
	for (long iter = 0; iter <= m_oFunctionsArray.GetUpperBound(); iter++)
	{
		for (long IdCmd = CMD_STANDARDFIRST; IdCmd <= CMD_STANDARDLAST; IdCmd++)
		{
			LPCTSTR pCmdName = _get_std_command_name(IdCmd);
			if (pCmdName != NULL)
			{
				if (_tcsicmp(m_oFunctionsArray[iter].m_oNameString, pCmdName) == 0)
				{
					set_prop_is_stdcmd(IdCmd, true);
					set_prop_button_visible(IdCmd, true);
					break;
				}
			}
		}
	}
}

void cned_window::set_prop_script_nxid(const ng_string& roScriptNXID)
{
	m_strScriptNXID = roScriptNXID;
}


eInvokeResult cned_window::invoke_method(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSOV, const long lSize, CSmartOleVariant* poResultSOV, bool bThrowIfNotExists)
{
	if (bThrowIfNotExists)
	{
		Invoke(pocName, pArgumentsSOV, lSize, poResultSOV);
		return invoke_ok;
	}
	else
	{
		return SafeInvoke(pocName, pArgumentsSOV, lSize, poResultSOV);
	}
}

//-------------------------------------------------------------------------------
// dispatch integration
//-------------------------------------------------------------------------------

const long WINDOW_DISPID_OFFSET = 100;

HRESULT cned_window::Window_GetIDsOfNames(LPOLESTR* rgszNames, UINT cNames, DISPID* rgDispId)
{
	//wbudowane metody cned_window s¹ rzadko u¿ywane,
	//wiêc próbujemy najpierw ze skryptem

	HRESULT hr = __GetIDsOfNames(rgszNames, cNames, rgDispId);

	if (hr == DISP_E_UNKNOWNNAME)
	{
		hr = ((IDispatch*)&m_xDispatch)->GetIDsOfNames(IID_NULL, rgszNames, cNames, LOCALE_SYSTEM_DEFAULT, rgDispId);
		ASSERT(*rgDispId < WINDOW_DISPID_OFFSET);
	}
	else
	{
		//metoda skryptu - zrób offset dispid
		*rgDispId += WINDOW_DISPID_OFFSET;
	}
	return hr;
}

HRESULT cned_window::Window_Invoke(DISPID dispId, REFIID riid, LCID lCid, WORD wFlags, DISPPARAMS* pDispParams,
	VARIANT* pVarResult, EXCEPINFO* pExceptInfo, UINT* puArgError)
{
	if (dispId < WINDOW_DISPID_OFFSET)		//metoda okna
	{
		return ((IDispatch*)&m_xDispatch)->Invoke(dispId, riid, lCid, wFlags, pDispParams, pVarResult, pExceptInfo, puArgError);
	}
	else
	{
		return __Invoke(dispId - WINDOW_DISPID_OFFSET, riid, lCid, wFlags, pDispParams, pVarResult, pExceptInfo, puArgError);
	}
}

eInvokeResult cned_window::fire_user_command(LPCTSTR lpFunctionName, CSmartOleVariant* pArgumentsSmartOleVariant, long lSize, bool bMustExists)
{
	CSmartOleVariant oResultSOV;

	eInvokeResult eResult = invoke_method(CBStr(lpFunctionName), pArgumentsSmartOleVariant, lSize, &oResultSOV, bMustExists);
	if (eResult != invoke_ok)
	{
		return eResult;
	}
	if (oResultSOV.Type() == VT_BOOL)
	{
		return oResultSOV.GetBool() ? invoke_true : invoke_false;
	}
	return invoke_true;
}

eInvokeResult cned_window::fire_std_command(long nCommandId, CSmartOleVariant* pArgumentsSOV, long lSize)
{
	ASSERT(_get_std_command_name(nCommandId) != NULL);
	return fire_user_command(_get_std_command_name(nCommandId), pArgumentsSOV, lSize, true);
}

//-------------------------------------------------------------------------------
//-----------         build-in interface         --------------------------------
//-------------------------------------------------------------------------------

BEGIN_DISPATCH_MAP(cned_window, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(cned_window)
	DISP_PROPERTY_EX(cned_window, "startfocus", GetStartingfocusAUTO, SetStartingfocusAUTO, VT_VARIANT)
	DISP_FUNCTION(cned_window, "getfocuselement", GetFocusElementAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX(cned_window, "modified", GetModifiedFlagAUTO, SetModifiedFlagAUTO, VT_BOOL)
	DISP_FUNCTION(cned_window, "createtransfer", CreateTransferAUTO, VT_DISPATCH, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

VARIANT cned_window::GetStartingfocusAUTO()
{
	ALL_TRY
	{
		CSmartOleVariant oInitialFocusSOV(get_prop_initial_focus(),VT_I4);
		return oInitialFocusSOV.Detach();
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cned_window::SetStartingfocusAUTO(const VARIANT FAR& newValue)
{
	ALL_TRY
	{
		set_prop_initial_focus((reinterpret_cast<const CSmartOleVariant&>(newValue)).GetLong());
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cned_window::GetFocusElementAUTO()
{
	ALL_TRY
	{
		//ned_to_do:		ASSERT(_get_element_manager().PointsObject());

		//ned_to_do:		if(_get_element_manager()->get_focus_element() == NEDID_NOTHING)
				{
					return NULL;
				}

		//ned_to_do:		return get_element_on_ident(_get_element_manager()->get_focus_element())->get_my_nedaw()->GetDispatch(true);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cned_window::GetModifiedFlagAUTO()
{
	ALL_TRY
	{
		return (get_modified_flag() != false);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cned_window::SetModifiedFlagAUTO(BOOL bModified)
{
	ALL_TRY
	{
		set_modified_flag(bModified != FALSE);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

SCP<nui_transfer> create_transfer(const ng_string& roModeString);

LPDISPATCH cned_window::CreateTransferAUTO(LPCTSTR lpTransferMode)
{
	ALL_TRY
	{
		SCP<nui_transfer> poTransferSP = create_transfer(ng_string(lpTransferMode));
		SCP<nedaw::cnedaw_transfer> poNEDAWTransferSP = NewSCP(new nedaw::cnedaw_transfer(poTransferSP),false);
		return poNEDAWTransferSP->GetDispatch(true);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
