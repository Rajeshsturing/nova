/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_parser__
		abstrakcyjna klasa bazowa parserów cned_*


*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"		//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "..\include\treeindex_nui.h"
#include "..\navoscript\scriptscanner.h"
#include "..\navoscript\CacheManagerUser.h"
#include "..\include\scriptuser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navogal\ngal_iface.h"

#include "..\navoui\common_ned_inc.h"		//common includes
#include "..\navoui\extern_ned.h"
#include "..\navoui\group_helper_ned.h"
#include "..\navoui\table_ned.h"
#include "..\navoui\tablesection_ned.h"
#include "..\navoui\tablerow_ned.h"
#include "..\navoui\tablecell_ned.h"
#include "..\navoui\paragraph_ned.h"
#include "..\navoui\page_caption_ned.h"
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\page_ned.h"
#include "..\navoui\window_ned.h"


using namespace ned;

#include "base_xui.h"
#include "element_xui.h"
#include "container_xui.h"
#include "helper_xui.h"
#include "attrib_xui.h"
#include "read_thread_xui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR * pcAttribWidth = _T("width");
const TCHAR * pcAttribHeight = _T("height");
const TCHAR * pcAttribToolTip = _T("tip");
const TCHAR * pcAttribHelp = _T("help");

static const TCHAR * pcAttribDisabled = _T("disable");
static const TCHAR * pcAttribHidden = _T("hide");
static const TCHAR * pcAttribIgnoreSysDisable = _T("ignoresysdisable");
static const TCHAR * pcAttribUserProp = _T("userprop");
static const TCHAR * pcAttribTabStop = _T("tabstop");
static const TCHAR * pcAttribDisableSplit = _T("dontsplit");
static const TCHAR * pcAttribRedirect = _T("customredirect");

SCP<cxmlui_parser__> cxmlui_main_parser::create_parser(const ng_string & roElementString)
{
	long nVariant = 0;
	ened_element_type eType = _lookup_element_type(roElementString, nVariant);
	switch (eType)
	{
	case ned_none:	//not ned_element -> may be special item like <transfer>
		switch (roElementString[0])
		{
		case 'b':		//<body>
			return NewSCP<cxmlui_parser__>(new cxmlui_page_body_parser(this, roElementString));
		case 'c':		//<config> , <cursor>
			if (roElementString[1] == 'u')	//<cursor>
			{
				if (roElementString[2] == 'r')
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_cursor_parser(this, roElementString));
				}
			}
			else
			{
				if (roElementString[1] == 'o')	//<config>
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_config_parser(this, roElementString));
				}
			}
		case 'f':
			if (roElementString[1] == 'i')	//<field>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_field_parser(this, roElementString));
			}
			else
			{
				if (roElementString[1] == 'o')	//<footer>
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_page_footer_parser(this, roElementString));
				}
			}
			break;
		case 'h':		//<header>
			return NewSCP<cxmlui_parser__>(new cxmlui_page_header_parser(this, roElementString));
		case 'i':		//<iid>
			return NewSCP<cxmlui_parser__>(new cxmlui_fixediid_parser(this, roElementString));
		case 'o':		//<ondataentered>, <ongetdata>, <ongotfocus>, <onlostfocus>
			if (roElementString[1] == 'n')
			{
				if (roElementString[2] == 'd')	//<ondataentered>
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_ondataentered_parser(this, roElementString));
				}
				else
				{
					if (roElementString[2] == 'l')		//<onlostfocus>
					{
						return NewSCP<cxmlui_parser__>(new cxmlui_onlostfocus_parser(this, roElementString));
					}
					else
					{
						if (roElementString[2] == 'g')
						{
							if (roElementString[3] == 'e')		//<ongetdata>
							{
								return NewSCP<cxmlui_parser__>(new cxmlui_ongetdata_parser(this, roElementString));
							}
							else
							{
								if (roElementString[3] == 'o')	//<ongotfocus>
								{
									return NewSCP<cxmlui_parser__>(new cxmlui_ongetfocus_parser(this, roElementString));
								}
							}
						}
					}
				}
			}
			break;
		case 'r':
			if (roElementString[1] == 'e')	//<reftypeid>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_reftypeid_parser(this, roElementString));
			}
			break;
		case 's':
			if (roElementString[1] == 'e')	//<searchfield>
			{
				if (roElementString[2] == 'c')	//<secid....>
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_securityid_parser(this, roElementString));
				}
				else
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_searchfield_parser(this, roElementString));
				}
			}
			if (roElementString[1] == 'c')	//<script>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_script_parser(this, roElementString));
			}
			if (roElementString[1] == 't')	//<startpos> or <startfocus>
			{
				if (roElementString == _T("startpos"))
				{
					return NewSCP<cxmlui_parser__>(new cxmlui_startpos_parser(this, roElementString));
				}
				else
				{
					if (roElementString == _T("startfocus"))
					{
						return NewSCP<cxmlui_parser__>(new cxmlui_startfocus_parser(this, roElementString));
					}
				}
			}
			break;
		case 't':
			if (roElementString[1] == 'r') 	//<transfer>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_transfer_parser(this, roElementString));
			}
			if (roElementString[1] == 'y') 	//<typeid>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_typeid_parser(this, roElementString));
			}
			if (roElementString[1] == 'i')	//<title>
			{
				return NewSCP<cxmlui_parser__>(new cxmlui_title_parser(this, roElementString));
			}
			break;
		}
		break;
	case ned_static:
		return NewSCP<cxmlui_parser__>(new cxmlui_static_parser(this, roElementString));
	case ned_button:
		return NewSCP<cxmlui_parser__>(new cxmlui_button_parser(this, roElementString));
	case ned_staticex:
		return NewSCP<cxmlui_parser__>(new cxmlui_staticex_parser(this, roElementString));

	case ned_textedit:
		return NewSCP<cxmlui_parser__>(new cxmlui_textedit_parser(this, roElementString));
	case ned_currency:
		return NewSCP<cxmlui_parser__>(new cxmlui_currency_edit_parser(this, roElementString));
	case ned_intedit:
		return NewSCP<cxmlui_parser__>(new cxmlui_int_edit_parser(this, roElementString));
	case ned_date:
		return NewSCP<cxmlui_parser__>(new cxmlui_date_edit_parser(this, roElementString));
	case ned_timeed:
		return NewSCP<cxmlui_parser__>(new cxmlui_time_edit_parser(this, roElementString));

	case ned_multiline:
	case ned_richedit:
		return NewSCP<cxmlui_parser__>
			(new cxmlui_multi_rich_edit_parser((eType == ned_richedit), this, roElementString));

	case ned_picture:
		return NewSCP<cxmlui_parser__>(new cxmlui_picture_parser(this, roElementString));
	case ned_extern:
		return NewSCP<cxmlui_parser__>(new cxmlui_extern_parser(this, roElementString));
	case ned_table:
	case ned_grid:
		return NewSCP<cxmlui_parser__>
			(new cxmlui_table_parser((eType == ned_grid), this, roElementString));
	case ned_tablesection:
		return NewSCP<cxmlui_parser__>(new cxmlui_table_section_parser(nVariant, this, roElementString));
	case ned_tablerow:
		return NewSCP<cxmlui_parser__>(new cxmlui_table_row_parser(this, roElementString));
	case ned_tablecell:
		return NewSCP<cxmlui_parser__>(new cxmlui_table_cell_parser(this, roElementString));
	case ned_paragraph:
		return NewSCP<cxmlui_parser__>(new cxmlui_paragraph_parser(this, roElementString));
	case ned_vscroll:
		return NewSCP<cxmlui_parser__>(new cxmlui_scroll_parser(false, this, roElementString));
	case ned_hscroll:
		return NewSCP<cxmlui_parser__>(new cxmlui_scroll_parser(true, this, roElementString));

	case ned_breakline:
		return NewSCP<cxmlui_parser__>(new cxmlui_breakline_parser(this, roElementString));
	case ned_breakpage:
		return NewSCP<cxmlui_parser__>(new cxmlui_breakpage_parser(this, roElementString));

	case ned_htmlwindow:
		return NewSCP<cxmlui_parser__>(new cxmlui_web_parser(this, roElementString));
	case ned_olecontrol:
		return NewSCP<cxmlui_parser__>(new cxmlui_olecontrol_parser(this, roElementString));
	case ned_tabmanager:
		return NewSCP<cxmlui_parser__>(new cxmlui_tabmanager_parser(this, roElementString));
	case ned_tabitem:
		return NewSCP<cxmlui_parser__>(new cxmlui_tabitem_parser(this, roElementString));
	case ned_radio:
	case ned_checkbox:
		return NewSCP<cxmlui_parser__>
			(new cxmlui_checkbox_radio_parser((eType == ned_radio), this, roElementString));

	case ned_toplevelpage:
	{
		if (m_oParserStack.IsEmpty())		//must be toplevel page
		{
			return NewSCP<cxmlui_parser__>(new cxmlui_toplevel_parser(this, roElementString));
		}
		else	//subpage
		{
			return NewSCP<cxmlui_parser__>(new cxmlui_page_parser(this, roElementString));
		}
	}
	default:
		;
	}
	ASSERT(false);
	return SCP<cxmlui_parser__>();
}


static void _cocoon_xui_parser_diag(const CString & roMessage)
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
		oLine.Format(_T("%s [base_xui] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

cxmlui_main_parser::~cxmlui_main_parser()
{
	if(!m_strScriptNXID.IsEmpty())
	{
		get_window()->set_prop_script_nxid(m_strScriptNXID);
	}

	if (!m_oScriptCodeString.IsEmpty() || !m_strScriptNXID.IsEmpty())
	{
		CString oDiag;
		oDiag.Format(_T("main_parser done script_len=%d nxid=%s has_app_onstart=%d"),
			m_oScriptCodeString.GetLength(),
			(LPCTSTR)m_strScriptNXID,
			m_oScriptCodeString.Find(_T("app_onstart")) >= 0);
		_cocoon_xui_parser_diag(oDiag);
	}

	if (!m_oScriptCodeString.IsEmpty())
	{
		get_window()->set_prop_script(m_oScriptCodeString);
	}
}

void cxmlui_main_parser::OnStartElement(LPCTSTR lpElement, const CMapStringToString & roAttributes)
{
	ng_string oElementString(lpElement);
	oElementString.MakeLower();

	//TRACEXML	TRACE("<begin %s\n",oElementString);

	SCP<cxmlui_parser__> poElemParserSP = create_parser(oElementString);
	if (poElemParserSP.PointsNull())
	{
		ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE, IDPAGE_NOTAVAILABLE, oElementString);
	}
	ned_ident nIdent = NEDID_NOTHING;
	translate_attrib_ident(roAttributes, nIdent);

	poElemParserSP->begin(nIdent);
	poElemParserSP->attributes(roAttributes);

	m_oParserStack.Push(poElemParserSP);
}

void cxmlui_main_parser::OnEndElement(LPCTSTR lpElement)
{
	ng_string oElementString(lpElement);
	oElementString.MakeLower();
	//TRACEXML	TRACE("end %s >\n",oElementString);

	if (oElementString != get_current_parser()->get_tag())
	{
		ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE, IDPAGE_NOTAVAILABLE, oElementString);
	}
	m_nElementPendingCounter--;
	m_nElementReadCounter++;

	if (m_nElementPendingCounter == 0)
	{
		//chunk finished
		if (get_controller())
		{
			ASSERT(!m_oPageStack.IsEmpty());
			{
				ng_string oProgressTitleString;
				oProgressTitleString.Format(_T("Wczytano ju¿ %d elementów z %s"),
					m_nElementReadCounter, m_oCurrentPageTitleString);
				get_current_page_element()->set_prop_title(oProgressTitleString);
			}

			get_controller()->on_chunk_completed(this);
		}
	}

	m_oParserStack.Pop()->end();
}

void cxmlui_main_parser::start_with_container(SCP<cned_container> poContainerSP)
{
	SCP<cxmlui_container_parser__> poContainerParserSP = NewSCP(new cxmlui_container_parser__(this, ""));
	poContainerParserSP->special_set_cointainer(poContainerSP);

	SCP<cxmlui_parser__> poElemParserSP = NewSCP<cxmlui_parser__>(poContainerParserSP.Get(), true);
	m_oParserStack.Push(poElemParserSP);
}

void cxmlui_main_parser::end_with_container()
{
	m_oParserStack.Pop()->end();
}

void cxmlui_main_parser::OnDataValue(LPCTSTR lpValue)
{
	get_current_parser()->data(lpValue);
}

SCP<cxmlui_parser__> cxmlui_main_parser::get_current_parser()
{
	ASSERT(!m_oParserStack.IsEmpty());
	return m_oParserStack.GetTop();
}

void cxmlui_main_parser::push_typeid(long nTypeId)
{
	m_oTypeIdStack.Push(nTypeId);
}

void cxmlui_main_parser::pop_typeid()
{
	m_oTypeIdStack.Pop();
}

void cxmlui_main_parser::set_current_page_title(const ng_string & roTitleString)
{
	get_current_page_element()->set_prop_title(roTitleString);
	m_oCurrentPageTitleString = roTitleString;
}

void cxmlui_main_parser::push_page_element(cned_page * poPageElement)
{
	m_oPageStack.Push(poPageElement);
}

void cxmlui_main_parser::pop_page_element()
{
	m_oPageStack.Pop()->set_prop_title(m_oCurrentPageTitleString);
}

cned_page * cxmlui_main_parser::get_current_page_element()
{
	if (m_oPageStack.IsEmpty())
	{
		//no page yet processed
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	return m_oPageStack.GetTop();
}

long cxmlui_main_parser::get_current_typeid() const
{
	if (m_oTypeIdStack.IsEmpty())
	{
		//no typeid yet defined
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	return m_oTypeIdStack.GetTop();
}

long cxmlui_main_parser::resolve_field(LPCTSTR lpData, long nTypeId)
{
	//get current typeid
	ASSERT(nTypeId != 0);
	SCP<CStdObjDef> poStdObjDefSP = get_definition_manager()->GetStdObjDef(nTypeId);
	long nFieldNr = _ttol(lpData);

	if (nFieldNr == 0)	//by name
	{
		nFieldNr = poStdObjDefSP->GetFieldIndexAUTO(lpData);
		if (nFieldNr == -1)	//not found
		{
			ThrowNavoException2(ERCO_PARSE_FIELD_NOT_FOUND, IDPAGE_NOTAVAILABLE,
				poStdObjDefSP->GetTableName(), (LPCTSTR)lpData);
		}
	}
	return nFieldNr;
}

ened_element_type cxmlui_main_parser::_lookup_element_type(LPCTSTR lpTag, long & rnVariant)
{
	/*
		manually coded map
	*/
	ASSERT(lpTag);
	switch (lpTag[0])
	{
	case 'b':		//<button>, <br>
		if (lpTag[1] == 'u')
		{
			return ned_button;
		}
		if (lpTag[1] == 'r')
		{
			return ned_breakline;
		}
		break;
	case 'c':		//<checkbox>, <currency>
		if (lpTag[1] == 'u')
		{
			if (lpTag[2] == 'r')
			{
				if (lpTag[3] == 'r')		//also <cursor>,,,
				{
					return ned_currency;
				}
			}
		}
		else
		{
			if (lpTag[1] == 'h')
			{
				return ned_checkbox;
			}
		}
		break;
	case 'd':		//<date>, <docobj>
		if (lpTag[1] == 'a')
		{
			return ned_date;
		}
		if (lpTag[1] == 'o')
		{
			return ned_documentobject;
		}
		break;
	case 'e':		//<edit>, <extern>
		if (lpTag[1] == 'd')
		{
			return ned_textedit;
		}
		if (lpTag[1] == 'x')
		{
			return ned_extern;
		}
		break;
	case 'f':		//<ff>
		if (lpTag[1] == 'f')
		{
			return ned_breakpage;
		}
		break;
	case 'g':		//<grid>
		return ned_grid;
	case 'h':		//<hscroll>
		if (lpTag[1] == 's')
		{
			return ned_hscroll;
		}
		break;
	case 'i':		//<intedit>
		if (lpTag[1] == 'n')
		{
			return ned_intedit;
		}
		break;
	case 'm':		//<multiline>
		return ned_multiline;
		break;
	case 'o':		//<olecontrol>
		if (lpTag[1] == 'l')
		{
			return ned_olecontrol;
		}
		break;
	case 'p':		//<page>, <p>, <picture>
		if (lpTag[1] == '\0')
		{
			return ned_paragraph;
		}
		if (lpTag[1] == 'a')
		{
			return ned_toplevelpage;
		}
		if (lpTag[1] == 'i')
		{
			return ned_picture;
		}
		break;
	case 'r':		//<radio>, <richedit>
		if (lpTag[1] == 'a')
		{
			return ned_radio;
		}
		if (lpTag[1] == 'i')
		{
			return ned_richedit;
		}
		break;
	case 't':		//<t>, <text>, <table>, <time>, <td>, <tr>, <tbody>, <tfoot> , <thead>, <tab>, <tabitem>
					//<tnexthead> <tprevfoot>
		switch (lpTag[1])
		{
		case '\0':
			return ned_static;
		case 'a':
			if (lpTag[2] == 'b')		//table, tab, tabitem
			{
				switch (lpTag[3])
				{
				case '\0':
					return ned_tabmanager;	//<tab>
				case 'l':
					return ned_table;		//<table>
				case 'i':
					return ned_tabitem;		//<tabitem>
				}
			}
			break;
		case 'b':
			rnVariant = long(ned_tse_body);
			return ned_tablesection;
		case 'd':
			return ned_tablecell;
		case 'e':
			return ned_staticex;
		case 'f':
			rnVariant = long(ned_tse_last_footer);
			return ned_tablesection;
		case 'h':
			rnVariant = long(ned_tse_first_header);
			return ned_tablesection;
		case 'i':
			if (lpTag[2] == 'm')
			{
				return ned_timeed;
			}
			break;
		case 'n':	// <tnexthead>
			rnVariant = long(ned_tse_next_hdr);
			return ned_tablesection;
			break;
		case 'p':	// <tprevfoot>
			rnVariant = long(ned_tse_prev_ftr);
			return ned_tablesection;
			break;
		case 'r':
			if (!IsAlpha(lpTag[2]))		//<tr> but not <transfer> etc.
			{
				return ned_tablerow;
			}
			break;
		}
		break;
	case 'v':		//<vscroll>
		return ned_vscroll;
	case 'w':		// <web>
		return ned_htmlwindow;
	}
	return ned_none;
}

SCP<cned_container> cxmlui_element_parser__::get_current_container()
{
	SCP<cxmlui_parser__> poXUIParserSP = m_poContext->get_current_parser();
	cxmlui_container_parser__ * poContainerParser = dynamic_cast<cxmlui_container_parser__ *>(poXUIParserSP.Get());
	if (poContainerParser == NULL)
	{
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	ASSERT(poContainerParser->get_container().PointsObject());
	return poContainerParser->get_container();
}

void cxmlui_element_parser__::attributes(const CMapStringToString & roAttribArray)
{
	SCP<cned_element> poElementSP = get_uielement();

	if (!roAttribArray.IsEmpty())
	{
		ned_declattributes oDeclAttributes;
		translate_common_attrib(oDeclAttributes, roAttribArray);
		poElementSP->set_prop_declattrib(oDeclAttributes, true);
	}

	poElementSP->apply_attributes(get_current_container()->get_current_attributes());

	if (!roAttribArray.IsEmpty())
	{
		ng_xdist nWidth;
		if (translate_attrib_dimension(roAttribArray, pcAttribWidth, nWidth))
		{
			poElementSP->set_prop_extwidth(nWidth);
		}
		ng_ydist nHeight;
		if (translate_attrib_dimension(roAttribArray, pcAttribHeight, nHeight))
		{
			poElementSP->set_prop_extheight(nHeight);
		}
		ng_string oToolTipString;
		if (roAttribArray.Lookup(pcAttribToolTip, oToolTipString))
		{
			poElementSP->set_prop_tooltip_text(oToolTipString);
		}

		if (roAttribArray.Lookup(pcAttribHelp, oToolTipString))
		{
			poElementSP->set_prop_help_text(oToolTipString);
		}

		SCP<cnui_shortkey> poShortKeySP;
		if (translate_attrib_shortkey(roAttribArray, poShortKeySP))
		{
			ASSERT(poShortKeySP.PointsObject());
			poElementSP->set_shortkey(poShortKeySP);
		}
		bool bHidden;
		if (translate_attrib_boolean(roAttribArray, pcAttribHidden, bHidden))
		{
			poElementSP->set_prop_hidden(bHidden);
		}
		bool bIgnoreSysDis;
		if (translate_attrib_boolean(roAttribArray, pcAttribIgnoreSysDisable, bIgnoreSysDis))
		{
			poElementSP->set_prop_ignore_sys_disable(bIgnoreSysDis);
		}
		bool bDisabled;
		if (translate_attrib_boolean(roAttribArray, pcAttribDisabled, bDisabled))
		{
			poElementSP->set_prop_disabled(bDisabled);
		}
		//user properties
		{
			ng_string oUserPropHLIString;
			if (roAttribArray.Lookup(pcAttribUserProp, oUserPropHLIString))
			{
				poElementSP->set_prop_userprop(ReadHLIFromString(oUserPropHLIString));
			}
		}

		bool bTabStop;
		if (translate_attrib_boolean(roAttribArray, pcAttribTabStop, bTabStop))
		{
			poElementSP->set_prop_tabstop(bTabStop);
		}

		bool bDontSplit;
		if (translate_attrib_boolean(roAttribArray, pcAttribDisableSplit, bDontSplit))
		{
			poElementSP->set_prop_split_allowed(!bDontSplit);
		}

		ned_position oDeclPosition;
		if (translate_absolute_position(roAttribArray, oDeclPosition))
		{
			poElementSP->set_decl_position(oDeclPosition);
		}

		long nRedirectIdent;
		if (translate_attrib_long(roAttribArray, pcAttribRedirect, nRedirectIdent))
		{
			poElementSP->set_prop_redirect(nRedirectIdent);
		}
	}
}

void cxmlui_element_parser__::data(LPCTSTR lpData)
{
#ifdef _DEVELOPER_EDITION_

	if (lpData[0] != '\0')
	{
		CString oInfoString;
		oInfoString.Format("Element # %d:Wartoœæ %s nie jest oczekiwana w tym miejscu!", m_poElementSP->get_ident(), lpData);
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oInfoString);
	}

#else
	UNUSED_ALWAYS(lpData);
#endif
}

void read_page_xml(SCP<IStream> poStreamSP, SCP<cned_window> pWindowSP,
	SCP<CDefinitionManager> poDefinitionManagerSP)
{
	SCP<INavoErrorInfo> poNavoErrorInfoSP;

	if (!ParseXML(NewSCP<CSAXHandler__>(new cxmlui_main_parser(NULL, pWindowSP, poDefinitionManagerSP)),
		poStreamSP, poNavoErrorInfoSP))
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(poNavoErrorInfoSP, oNavoException);
		CString oString = "read_page_xml failed";
		ContinueThrowNavoException1(oNavoException, ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
}

void read_part_xml(SCP<IStream> poStreamSP, SCP<cned_window> pWindowSP,
	SCP<CDefinitionManager> poDefinitionManagerSP, SCP<cned_container> poContainerSP)
{
	SCP<cxmlui_main_parser> poMainParserSP = NewSCP(new cxmlui_main_parser(NULL, pWindowSP, poDefinitionManagerSP));
	poMainParserSP->start_with_container(poContainerSP);
	SCP<INavoErrorInfo> poNavoErrorInfoSP;

	if (!ParseXML(NewSCP<CSAXHandler__>(poMainParserSP.Get(), true), poStreamSP, poNavoErrorInfoSP))
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(poNavoErrorInfoSP, oNavoException);
		CString oString = "read_part_xml failed";
		ContinueThrowNavoException1(oNavoException, ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
	poMainParserSP->end_with_container();
}

//---------------------------------------------------------------------------------------------
// reading thread
//---------------------------------------------------------------------------------------------

SCP<cxmlui_reader_thread> cxmlui_reader_thread::create(SCP<cned_window> pWindowSP,
	SCP<CDefinitionManager> poDefinitionManagerSP, SCP<IStream> poStreamSP, long nInitialChunk)
{
	SCP<cxmlui_reader_thread> poReadThreadSP =
		NewSCP(new cxmlui_reader_thread(pWindowSP, poDefinitionManagerSP, poStreamSP, nInitialChunk));
	poReadThreadSP->ResumeThread();
	return poReadThreadSP;
}

cxmlui_reader_thread::cxmlui_reader_thread(SCP<cned_window> pWindowSP,
	SCP<CDefinitionManager> poDefinitionManagerSP, SCP<IStream> poStreamSP, long nInitialChunkSize) :
	CNavoThread(CNavoOleInitHolder::APARTMENT),
	m_pWindowSP(pWindowSP),
	m_poDefinitionManagerSP(poDefinitionManagerSP),
	m_poStreamSP(poStreamSP),
	m_nInitialChunkSize(nInitialChunkSize),
	m_eState(state_none),
	m_poParser(NULL)
{
}

cxmlui_reader_thread::~cxmlui_reader_thread()
{
}

void cxmlui_reader_thread::_clean()
{
	m_poParser = NULL;
	m_pWindowSP = 0;
	m_poDefinitionManagerSP = 0;
	m_poStreamSP = 0;
	m_eState = state_completed;
}

int cxmlui_reader_thread::Run()
{
	m_eState = state_running;
	//zrób
	SCP<INavoErrorInfo> poNavoErrorInfoSP;

	SCP<cxmlui_main_parser> poParserSP = NewSCP(new cxmlui_main_parser(this, m_pWindowSP, m_poDefinitionManagerSP));
	m_poParser = poParserSP;
	poParserSP->set_chunk_size(m_nInitialChunkSize);

	try
	{
		if (!ParseXML(NewSCP<CSAXHandler__>(poParserSP.Get(), true), m_poStreamSP, poNavoErrorInfoSP))
		{
			GetErrorInfoFromInterface(poNavoErrorInfoSP, GetErrorStorage());
			CString oString = "read_page_xml failed";
			GetErrorStorage() += CNavoErrorInfo(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
		}
	}
	catch (...)
	{
		poParserSP = 0;
		_clean();
		//set error state
		m_eState = state_error;
		//release waiting clients
		m_oWorkReadyEvent.SetEvent();
		throw;
	}

	poParserSP = 0;
	_clean();
	//zapal event
#ifdef _DEBUG
	::Sleep(0);		//see Q173260
#endif

	m_oWorkReadyEvent.SetEvent();
	//czekaj na zezwolenie zakoñczenia
	CSingleLock oSlock(&m_oWorkContinueEvent, TRUE);
	return 0;
}

CNavoException & cxmlui_reader_thread::GetErrorStorage()
{
	return m_oErrorStorage;
}


void cxmlui_reader_thread::on_chunk_completed(CSAXHandler__ * poSAXHandler)
{

#ifdef _DEBUG
	::Sleep(0);		//see Q173260
#endif

	ASSERT(m_eState != state_completed);
	m_oWorkReadyEvent.SetEvent();
	CSingleLock oSlock(&m_oWorkContinueEvent, TRUE);

	ASSERT(poSAXHandler != NULL);

	if (m_eState == state_abort)
	{
		poSAXHandler->SetAbort();
	}
}

void cxmlui_reader_thread::abort()
{
	ASSERT(m_eState != state_completed);
	m_eState = state_abort;
	m_oWorkContinueEvent.SetEvent();
}

void cxmlui_reader_thread::complete()
{
	m_oWorkContinueEvent.SetEvent();
}

bool cxmlui_reader_thread::wait_chunk_complete()
{
	//waitevent
	CSingleLock oSlock(&m_oWorkReadyEvent, TRUE);
	//check completed flag
	return (m_eState == state_completed);
}

void cxmlui_reader_thread::next_chunk(long nChunkSize)
{
	TRACE("chunk size = %d\n", nChunkSize);

	ASSERT(m_eState != state_completed);
	ASSERT(m_poParser);
	m_poParser->set_chunk_size(nChunkSize);
	m_oWorkContinueEvent.SetEvent();
}


