/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_container*_parser
		parsery ró¿nych nui_elementów (kontenerów)


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
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\paragraph_ned.h"
#include "..\navoui\scrollbar_ned.h"
#include "..\navoui\optionbutton_ned.h"

#include "..\navoui\table_ned.h"
#include "..\navoui\tablesection_ned.h"
#include "..\navoui\grid_ned.h"
#include "..\navoui\table_bodysection_ned.h"
#include "..\navoui\tablerow_ned.h"
#include "..\navoui\pattern_tablerow_ned.h"
#include "..\navoui\grid_bodysection_ned.h"
#include "..\navoui\tablecell_ned.h"

#include "..\navoui\tabitem_ned.h"
#include "..\navoui\tabmanager_header_ned.h"
#include "..\navoui\tabmanager_ned.h"
#include "..\navoui\page_caption_ned.h"
#include "..\navoui\page_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "base_xui.h"
#include "container_xui.h"
#include "attrib_xui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR * pcAttribColSpan		= _T("colspan");
static const TCHAR * pcAttribRowSpan		= _T("rowspan");
static const TCHAR * pcAttribTotalRange		= _T("totalrange");
static const TCHAR * pcAttribPageRange		= _T("pagerange");

static const TCHAR * pcAttribMinVisibleDataRows = _T("minvisiblerows");
static const TCHAR * pcAttribMaxVisibleDataRows = _T("maxvisiblerows");
static const TCHAR * pcAttribForceSingleLine	= _T("keepline");
static const TCHAR * pcAttribTitle				= _T("title");
static const TCHAR * pcAttribTabsInRow			= _T("tabsinrow");
static const TCHAR * pcAttribCaption			= _T("caption");
static const TCHAR * pcAttribLineAlign			= _T("linealign");

extern const TCHAR * pcAttribWidth;
extern const TCHAR * pcAttribHeight;

extern const TCHAR * pcAlignTop;
extern const TCHAR * pcAlignBottom;
extern const TCHAR * pcAlignVCenter;


void cxmlui_toplevel_parser::attributes(const CMapStringToString & roAttribArray)
{
	ned_currattributes oDefaultAttributes;
	SCP<cned_element> poElementSP = get_uielement();

	//set declared attributes if any
	if(!roAttribArray.IsEmpty())
	{
		ned_declattributes oDeclAttributes;
		translate_common_attrib(oDeclAttributes,roAttribArray);
		poElementSP->set_prop_declattrib(oDeclAttributes,true);
	}
	
	poElementSP->apply_attributes(oDefaultAttributes);
	
	if(!roAttribArray.IsEmpty())
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(poElementSP);
		
		CSmartOleVariant oSOV;
		if(translate_attrib_image(roAttribArray,oSOV))
		{
			poPageSP->set_prop_imagesrc(oSOV);
		}
		
		ng_xdist nWidth;
		if(translate_attrib_dimension(roAttribArray,pcAttribWidth,nWidth))
		{
			poPageSP->set_prop_extwidth(nWidth);
		}
		ng_ydist nHeight;
		if(translate_attrib_dimension(roAttribArray,pcAttribHeight,nHeight))
		{
			poPageSP->set_prop_extheight(nHeight);
		}
		
		ng_rect oMarginsRect;
		if(translate_attrib_margins(roAttribArray,oMarginsRect))
		{
			poPageSP->set_prop_extmargins(oMarginsRect);
		}
		
		bool bCaption = true;
		if(translate_attrib_boolean(roAttribArray,pcAttribCaption,bCaption))
		{
			poPageSP->set_prop_caption(bCaption);
		}
	}
}

void cxmlui_table_parser::end()
{
	//stwórz brakujace sekcje
	SCP<cned_table> poTableSP = scp_cast_ui<cned_table>(get_uielement());
	poTableSP->create_all_missing_sections();

	if(m_bGrid)
	{
		SCP<nui_transfer> poTransferSP = m_poContext->get_window()->get_transfer(poTableSP->get_ident());
		if(poTransferSP.PointsObject())
		{
			if(poTransferSP->get_type() == ett_grid_list || poTransferSP->get_type() == ett_grid_cursor)
			{
				//revert to root typeid
				m_poContext->pop_typeid();
				ASSERT(m_poContext->get_current_typeid() != 0);
			}
			else
			{
				ASSERT(poTransferSP->get_type() == ett_custom);
			}
		}
	}
}

void cxmlui_table_section_parser::begin(ned_ident idSection)
{
	SCP<cned_table> poTableSP = scp_cast_ui<cned_table>(get_current_container());

	switch(m_eParseSectionType)
	{
	case ned_tse_next_hdr:
		m_poElementSP = poTableSP->create_next_header(idSection);
	break;
	case ned_tse_prev_ftr:
		m_poElementSP = poTableSP->create_prev_footer(idSection);
	break;
	default:
		m_poElementSP = poTableSP->create_section(m_eParseSectionType,idSection);
	}
}


void cxmlui_table_section_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_container_parser__::attributes(roAttribArray);
	
	//dodatkowe atrybuty dla grid'a
	if(get_uielement()->get_type() == ned_spreadbodysection)
	{
		SCP<cned_grid_bodysection> poGridBodySP = scp_cast_ui<cned_grid_bodysection>(get_uielement());
		ASSERT(poGridBodySP.PointsObject());

		if(!roAttribArray.IsEmpty())
		{
			long nMinVisibleDataRows;
			if(translate_attrib_long(roAttribArray,pcAttribMinVisibleDataRows,nMinVisibleDataRows))
			{
				poGridBodySP->set_prop_min_visible_datarows(nMinVisibleDataRows);
			}
			long nMaxVisibleDataRows;
			if(translate_attrib_long(roAttribArray,pcAttribMaxVisibleDataRows,nMaxVisibleDataRows))
			{
				poGridBodySP->set_prop_max_visible_datarows(nMaxVisibleDataRows);
			}
		}
	}
}

void cxmlui_table_row_parser::begin(ned_ident nIdent)
{
	cxmlui_table_section_parser * poSectionParser = 
		dynamic_cast<cxmlui_table_section_parser *>(m_poContext->get_current_parser().Get());
	
	if(poSectionParser == NULL)
	{
		//error: <tr> must be inside section
		ThrowNavoException(ERCO_TODO,IDPAGE_NOTAVAILABLE);
	}

	ened_element_type eNewRowType = ned_tablerow;

	if(ned_spreadbodysection == get_current_container()->get_type())
	{
		eNewRowType = ned_patterntablerow;
	}

	create_element(eNewRowType,nIdent);
}

void cxmlui_table_cell_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_group_container_parser_::attributes(roAttribArray);
	
	SCP<cned_tablecell> poTableCellSP = scp_cast_ui<cned_tablecell>(get_uielement());
	ASSERT(poTableCellSP.PointsObject());
	
	long nColSpan;
	if(translate_attrib_long(roAttribArray,pcAttribColSpan,nColSpan))
	{
		poTableCellSP->set_prop_colspan(nColSpan);
		//TRACE("colspan=%d ",nColSpan);
	}
	long nRowSpan;
	if(translate_attrib_long(roAttribArray,pcAttribRowSpan,nRowSpan))
	{
		poTableCellSP->set_prop_rowspan(nRowSpan);
		TRACE("rowspan=%d ",nRowSpan);
	}

	//TRACE(">\n");
}

void cxmlui_checkbox_radio_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_container_parser__::attributes(roAttribArray);
	SCP<cned_option_button_> poOptionButtonSP = scp_cast_ui<cned_option_button_>(get_uielement());
	long nColSpan;
	if(translate_attrib_long(roAttribArray,pcAttribColSpan,nColSpan))
	{
		poOptionButtonSP->set_prop_colspan(nColSpan);
	}
}

void cxmlui_scroll_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_paragraph_parser::attributes(roAttribArray);
	SCP<cned_scrollbar__> poScrollBarSP = scp_cast_ui<cned_scrollbar__>(get_uielement());

	long nTotalRange;
	if(translate_attrib_long(roAttribArray,pcAttribTotalRange,nTotalRange))
	{
		poScrollBarSP->set_prop_total_range(nTotalRange);
	}
	long nPageRange;
	if(translate_attrib_long(roAttribArray,pcAttribPageRange,nPageRange))
	{
		poScrollBarSP->set_prop_page_range(nPageRange);
	}
}

void cxmlui_tabitem_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_paragraph_parser::attributes(roAttribArray);
	
	ng_string oTitleString;
	if(roAttribArray.Lookup(pcAttribTitle,oTitleString))
	{
 		SCP<cned_tabmanager_item> poTabItemSP = scp_cast_ui<cned_tabmanager_item>(get_uielement());
		poTabItemSP->set_prop_title(oTitleString);
	}
}

void cxmlui_tabmanager_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_container_parser__::attributes(roAttribArray);
	long nTabsInRow;
	if(translate_attrib_long(roAttribArray,pcAttribTabsInRow,nTabsInRow))
	{
 		SCP<cned_tabmanager> poTabManSP = scp_cast_ui<cned_tabmanager>(get_uielement());
		poTabManSP->set_prop_tabs_in_row(nTabsInRow);
	}
}

void cxmlui_group_container_parser_::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_container_parser__::attributes(roAttribArray);
	
	if(!roAttribArray.IsEmpty())
	{
		SCP<cned_group_helper__> poGroupSP = scp_cast_ui<cned_group_helper__>(get_uielement());
		
		ng_string oValueString;
		if(roAttribArray.Lookup(pcAttribLineAlign,oValueString))
		{
			if(oValueString.CompareNoCase(pcAlignTop) == 0)
			{
				poGroupSP->set_prop_line_alignment(elal_top);
			}
			else if(oValueString.CompareNoCase(pcAlignBottom) == 0)
			{
				poGroupSP->set_prop_line_alignment(elal_bottom);
			}
			else if(oValueString.CompareNoCase(pcAlignVCenter) == 0)
			{
				poGroupSP->set_prop_line_alignment(elal_vcenter);
			}
		}
		bool bKeepLine;
		if(translate_attrib_boolean(roAttribArray,pcAttribForceSingleLine,bKeepLine))
		{
			poGroupSP->set_prop_keepline(bKeepLine);
		}
	}
}

void cxmlui_page_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_group_container_parser_::attributes(roAttribArray);
	SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(get_uielement());
	CSmartOleVariant oSOV;
	if(translate_attrib_image(roAttribArray,oSOV))
	{
		poPageSP->set_prop_imagesrc(oSOV);
	}
	
	bool bCaption = true;
	if(translate_attrib_boolean(roAttribArray,pcAttribCaption,bCaption))
	{
		poPageSP->set_prop_caption(bCaption);
	}
}


