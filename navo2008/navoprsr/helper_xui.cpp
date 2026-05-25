/*
	NAVO Enterprise (2002)
	2002-07-13

	helper parsery
		parsery pomocnicze


*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"
#include "..\include\errorstorage.h"		//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "..\include\treeindex_nui.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navogal\ngal_iface.h"

#include "..\navoui\common_ned_inc.h"		//common includes
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
#include "container_xui.h"
#include "helper_xui.h"
#include "attrib_xui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR* pcAttribMode = _T("mode");

static const TCHAR* pcCursorCustom = _T("customquery");

static const TCHAR* pcSecurityIdRead = _T("secidread");
static const TCHAR* pcSecurityIdInsert = _T("secidins");
static const TCHAR* pcSecurityIdUpdate = _T("secidupd");
static const TCHAR* pcSecurityIdDelete = _T("seciddel");

//-------------------------------------------------------------------------------------------------
//	<config> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_config_parser::begin(ned_ident /*nElementIdent*/)
{
	if (m_poContext->get_current_page_element()->get_type() != ned_toplevelpage)
	{
		//error: allowed only for top level page
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
}

//-------------------------------------------------------------------------------------------------
//	<script> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_script_parser::data(LPCTSTR lpData)
{
	if (m_poContext->get_current_page_element()->get_type() != ned_toplevelpage)
	{
		//error: allowed only for top level page
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poContext->add_to_script(lpData);
}

void cxmlui_script_parser::attributes(const CMapStringToString& roAttribArray)
{
	ng_string oScriptNXID;

	if (roAttribArray.Lookup(_T("nxid"), oScriptNXID))
	{
		m_poContext->set_script_nxid(oScriptNXID);
	}
}

//-------------------------------------------------------------------------------------------------
//	<typeid> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_typeid_parser::data(LPCTSTR lpData)
{
	long nTypeId = _ttol(lpData);
	if (nTypeId == 0)
	{
		//error: bad value for typeid
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poContext->get_window()->set_prop_root_typeid(nTypeId);
	m_poContext->push_typeid(nTypeId);
}


//-------------------------------------------------------------------------------------------------
void cxmlui_securityid_parser::data(LPCTSTR lpData)
{
	long idsec = _ttol(lpData);
	if (idsec == 0)
	{
		//error: bad value for securityid
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	if (_tcscmp(get_tag(), pcSecurityIdRead) == 0)
	{
		m_poContext->get_window()->set_prop_secid_read(idsec);
	}
	else
	{
		if (_tcscmp(get_tag(), pcSecurityIdInsert) == 0)
		{
			m_poContext->get_window()->set_prop_secid_insert(idsec);
		}
		else
		{
			if (_tcscmp(get_tag(), pcSecurityIdUpdate) == 0)
			{
				m_poContext->get_window()->set_prop_secid_update(idsec);
			}
			else
			{
				if (_tcscmp(get_tag(), pcSecurityIdDelete) == 0)
				{
					m_poContext->get_window()->set_prop_secid_delete(idsec);
				}
				else
				{

#ifdef _DEVELOPER_EDITION_
					AfxMessageBox("Nieznany securityid...? (" + ng_string(get_tag()) + ")");
#else
					//just ignore
#endif
				}
			}
		}
	}

}

//-------------------------------------------------------------------------------------------------
//	<iid> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_fixediid_parser::data(LPCTSTR lpData)
{
	long nIID = _ttol(lpData);
	if (nIID == 0)
	{
		//error: bad value for iid
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poContext->get_window()->set_prop_iid(nIID);
}

//-------------------------------------------------------------------------------------------------
//	<startpos> parser
//-------------------------------------------------------------------------------------------------

static ened_window_initial_pos DetectInitialPosition(LPCTSTR lpData)
{
	while (IsSpace(*lpData))
	{
		lpData++;
	}

	switch (*lpData)
	{
	case 'c':		//center
	case 'C':
		return wip_center;
	case 'b':		//bottomleft
	case 'B':
		return wip_bottom_left;
	case 't':
	case 'T':		//topright
	{
		if (_tcsnicmp(lpData, _T("topright"), 8) == 0)
		{
			return wip_top_right;
		}
		else
		{
			if (_tcsnicmp(lpData, _T("topleft"), 7) == 0)
			{
				return wip_top_left;
			}
			else
			{
				return wip_default;
			}
		}
	}
	default:
		return wip_default;
	}
}

void cxmlui_startpos_parser::data(LPCTSTR lpData)
{
	if (m_poContext->get_current_page_element()->get_type() != ned_toplevelpage)
	{
		//error: allowed only for top level page
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	ened_window_initial_pos eWIP = DetectInitialPosition(lpData);
	m_poContext->get_window()->set_prop_initial_position(eWIP);
}

//-------------------------------------------------------------------------------------------------
// <title> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_title_parser::begin(ned_ident /*nElementIdent*/)
{
}

void cxmlui_title_parser::data(LPCTSTR lpData)
{
	ng_string oString;
	normalize_data_string(lpData, oString);

	m_poContext->set_current_page_title(oString);
}

//-------------------------------------------------------------------------------------------------
// <startfocus> parser
//-------------------------------------------------------------------------------------------------

void cxmlui_startfocus_parser::data(LPCTSTR lpData)
{
	if (m_poContext->get_current_page_element()->get_type() != ned_toplevelpage)
	{
		//error: allowed only for top level page
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	long nInitialFocusId = _ttol(lpData);
	m_poContext->get_window()->set_prop_initial_focus(nInitialFocusId);
}

//-------------------------------------------------------------------------------------------------
// transfer parser
//-------------------------------------------------------------------------------------------------
void cxmlui_transfer_parser::begin(ned_ident /*nElementIdent*/)
{
	cxmlui_element_parser__* poElementParser = dynamic_cast<cxmlui_element_parser__*>(m_poContext->get_current_parser().Get());
	if (poElementParser == NULL)
	{
		//error: bad context - expected ui element
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_Ident = poElementParser->get_uielement()->get_ident();
}

SCP<nui_transfer> create_transfer(const ng_string& roModeString);

void cxmlui_transfer_parser::attributes(const CMapStringToString& roAttribArray)
{
	ng_string oModeString;
	if (!roAttribArray.Lookup(pcAttribMode, oModeString))
	{
		//to_do: zmieniæ string w zasobach
		ThrowNavoException(ERCO_PARSE_MODE_IS_REQUIRED, IDPAGE_NOTAVAILABLE);
	}

	m_poTransferSP = create_transfer(oModeString);
	ASSERT(m_poTransferSP.PointsObject());
	m_poContext->get_window()->set_transfer(m_Ident, m_poTransferSP);
}

//-------------------------------------------------------------------------------------------------
// field parser
//-------------------------------------------------------------------------------------------------

void cxmlui_transfer_part_parser::begin(ned_ident /*nElementIdent*/)
{
	cxmlui_transfer_parser* poTransferParser = dynamic_cast<cxmlui_transfer_parser*>(m_poContext->get_current_parser().Get());
	if (poTransferParser == NULL)
	{
		//error: bad context - expected <transfer>
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}

	m_poTransferParserSP = NewSCP(poTransferParser, true);
}

void cxmlui_field_parser::data(LPCTSTR lpData)
{
	ASSERT(m_poTransferParserSP.PointsObject());
	nui_transfer_1* poTransfer1 = dynamic_cast<nui_transfer_1*>(m_poTransferParserSP->get_transfer().Get());
	if (poTransfer1 == NULL)
	{
#ifdef _DEVELOPER_EDITION_
		AfxMessageBox("<field> dla tego rodzaju transferu nie ma sensu (" + CString(lpData) + "). Ingorujê!");
		//error: bad context - expected <transfer> of mode with <field> allowed
#else
		//just ignore
#endif
		return;
	}

	//resolve field
	long nFieldNr = m_poContext->resolve_field(lpData, m_poContext->get_current_typeid());
	poTransfer1->set_field(nFieldNr);

	//some additional work
	switch (poTransfer1->get_type())
	{
	case ett_grid_list:
	case ett_grid_cursor:
	{
		long nParentTypeId = m_poContext->get_current_typeid();
		ASSERT(nParentTypeId != 0);
		SCP<CStdObjDef> poStdObjDefSP = m_poContext->get_definition_manager()->GetStdObjDef(nParentTypeId);
		SCP<CStdObjFieldDef>& rpoStdObjFieldDefSP = poStdObjDefSP->GetField(nFieldNr);
		if (rpoStdObjFieldDefSP->GetRelationType() != RELT_LIST ||
			rpoStdObjFieldDefSP->GetReferenceTypeId() == 0)
		{
			//error: bad field for ett_grid_*  tranfer - must be <list>
			ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
		}
		//from now child type is current
		m_poContext->push_typeid(rpoStdObjFieldDefSP->GetReferenceTypeId());
	}
	break;
	case ett_edit_ref:
	case ett_row_edit_ref:
	{
		nui_transfer_2* poTransfer2 = dynamic_cast<nui_transfer_2*>(poTransfer1);
		ASSERT(poTransfer2 != NULL);

		if (poTransfer2->get_reftypeid() == 0)	//not provided yet - resolve 
		{
			//find reftypeid
			long nTypeId = m_poContext->get_current_typeid();
			ASSERT(nTypeId != 0);
			SCP<CStdObjDef> poStdObjDefSP = m_poContext->get_definition_manager()->GetStdObjDef(nTypeId);
			SCP<CStdObjFieldDef>& rpoStdObjFieldDefSP = poStdObjDefSP->GetField(nFieldNr);

			if ((rpoStdObjFieldDefSP->GetRelationType() != RELT_REF &&
				rpoStdObjFieldDefSP->GetRelationType() != RELT_WILDREF) ||
				rpoStdObjFieldDefSP->GetReferenceTypeId() == 0)
			{
				//error: bad field for ett_*_ref
				ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
			}
			poTransfer2->set_reftypeid(rpoStdObjFieldDefSP->GetReferenceTypeId());
		}
	}
	break;
	}
}

void cxmlui_searchfield_parser::data(LPCTSTR lpData)
{
	ASSERT(m_poTransferParserSP.PointsObject());
	nui_transfer_2* poTransfer2 = dynamic_cast<nui_transfer_2*>(m_poTransferParserSP->get_transfer().Get());
	if (poTransfer2 == NULL)
	{
		//error: bad context - expected <transfer> of mode with <searchfield> allowed
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}

	//resolve field
	long nRefTypeId = poTransfer2->get_reftypeid();
	long nFieldNr = m_poContext->resolve_field(lpData, nRefTypeId);
	poTransfer2->set_reffield(nFieldNr);
}

void cxmlui_cursor_parser::data(LPCTSTR lpData)
{
	ASSERT(m_poTransferParserSP.PointsObject());
	nui_transfer_2* poTransfer2 = dynamic_cast<nui_transfer_2*>(m_poTransferParserSP->get_transfer().Get());
	if (poTransfer2 == NULL)
	{
		CString oString;
		oString = "found <cursor> is invalid <transfer> ";
		//error: bad context - expected <transfer> of mode with <searchfield> allowed
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
	ng_string oString;
	normalize_data_string(lpData, oString);

	if (oString.CompareNoCase(pcCursorCustom) == 0)	//special case - custom cursor function
	{
		poTransfer2->set_cursor(CUSTOMCURSORID);
	}
	else
	{
		long nCursorId = _ttol(lpData);
		if (nCursorId == 0)
		{
			//error: cursor must be number or "custom" value
			CString oString;
			oString.Format("cursor must be number or 'customquery' value but got [%s]", lpData);
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
		}
		else
		{
			poTransfer2->set_cursor(nCursorId);
		}
	}
}

void cxmlui_reftypeid_parser::data(LPCTSTR lpData)
{
	long nRefTypeId = _ttol(lpData);
	if (nRefTypeId == 0)
	{
		CString oString;
		oString.Format("<reftypeid> must be valid TYPEID_, but got [%s]", lpData);
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
	nui_transfer_2* poTransfer2 = dynamic_cast<nui_transfer_2*>(m_poTransferParserSP->get_transfer().Get());
	if (poTransfer2 == NULL)
	{
		CString oString;
		oString = "found <reftypeid> is invalid <transfer> ";
		//error: bad context - expected <transfer> of mode with <reftypeid> allowed
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
	poTransfer2->set_reftypeid(nRefTypeId);
}

void cxmlui_inlplacehandler_parser::data(LPCTSTR lpData)
{
	m_poContext->add_to_script(lpData);
}

