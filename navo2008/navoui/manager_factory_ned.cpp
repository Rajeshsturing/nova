/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
		- manager_elementów

	- dostarcza elementy / swapuje unswapuje elementy
	- dostarcza ró¿ne providery (style, picture itd.)


	'element factory'

*/

#include "stdafx.h"
#include "arena_manager_ned.h"
#include "static_ned.h"
#include "button_ned.h"
#include "picture_ned.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "intedit_ned.h"
#include "textedit_ned.h"
#include "curredit_ned.h"
#include "dateedit_ned.h"
#include "timeedit_ned.h"
#include "multiline_helper_ned.h"
#include "staticex_ned.h"
#include "scroll_helper_ned.h"
#include "multi_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "grid_ned.h"
#include "table_bodysection_ned.h"
#include "tablerow_ned.h"
#include "pattern_tablerow_ned.h"
#include "grid_bodysection_ned.h"
#include "tablecell_ned.h"
#include "optionbutton_ned.h"
#include "checkbox_ned.h"
#include "radio_ned.h"
#include "page_caption_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "break_line_ned.h"
#include "break_page_ned.h"
#include "tabitem_ned.h"
#include "tabmanager_header_ned.h"
#include "tabmanager_ned.h"
#include "extern_ned.h"
#include "win32_ned.h"
#include "olecontrol_ned.h"
#include "web_ned.h"
#include "scrollbar_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SCP<cned_element> cned_element_manager::__construct_element
	(ened_element_type eType,const ned_ident idNewElement)
{
	ASSERT(idNewElement != NEDID_NOTHING);
	SCP<cned_element> poNewElementSP;
	switch(eType)
	{
	case ned_static:
		poNewElementSP = NewSCP<cned_element>(new cned_static(this,ned_static,idNewElement));
	break;
	case ned_staticex:
		poNewElementSP = NewSCP<cned_element>(new cned_staticex(this,idNewElement));
	break;
	case ned_picture:
		poNewElementSP = NewSCP<cned_element>(new cned_picture(this,idNewElement));
	break;
	case ned_button:
		poNewElementSP = NewSCP<cned_element>(new cned_button(this,idNewElement));
	break;
	case ned_subpage:
		poNewElementSP = NewSCP<cned_element>(new cned_page(this,ned_subpage,idNewElement));
	break;
	case ned_toplevelpage:
		ASSERT(idNewElement == NEDID_TOPLEVELPAGE);
		poNewElementSP = NewSCP<cned_element>(new cned_toplevelpage(this));
	break;
	case ned_date:
		poNewElementSP = NewSCP<cned_element>(new cned_dateedit(this,idNewElement));
	break;
	case ned_intedit:
		poNewElementSP = NewSCP<cned_element>(new cned_intedit(this,idNewElement));
	break;
	case ned_textedit:
		poNewElementSP = NewSCP<cned_element>(new cned_textedit(this,idNewElement));
	break;
	case ned_multiline:
		poNewElementSP = NewSCP<cned_element>(new cned_multiedit(this,idNewElement));
	break;
	case ned_currency:
		poNewElementSP = NewSCP<cned_element>(new cned_curredit(this,idNewElement));
	break;
	case ned_timeed:
		poNewElementSP = NewSCP<cned_element>(new cned_timeedit(this,idNewElement));
	break;
	case ned_paragraph:
		poNewElementSP = NewSCP<cned_element>(new cned_paragraph(this,ned_paragraph,idNewElement));
	break;
	case ned_radio:
		poNewElementSP = NewSCP<cned_element>(new cned_radio_button(this,idNewElement));
	break;
	case ned_checkbox:
		poNewElementSP = NewSCP<cned_element>(new cned_checkbox(this,idNewElement));
	break;
	case ned_table:
		poNewElementSP = NewSCP<cned_element>(new cned_table(this,ned_table,idNewElement));
	break;
	case ned_grid:
		poNewElementSP = NewSCP<cned_element>(new cned_grid(this,idNewElement));
	break;
	case ned_tablesection:
		poNewElementSP = NewSCP<cned_element>(new cned_tablesection(this,ned_tablesection,idNewElement));
	break;
	case ned_tablebodysection:
		poNewElementSP = NewSCP<cned_element>(new cned_table_bodysection(this,ned_tablebodysection,idNewElement));
	break;
	case ned_spreadbodysection:
		poNewElementSP = NewSCP<cned_element>(new cned_grid_bodysection(this,idNewElement));
	break;
	case ned_spreadpatternsection:
		poNewElementSP = NewSCP<cned_element>(new cned_grid_patternsection(this,idNewElement));
	break;
	case ned_tablerow:
		poNewElementSP = NewSCP<cned_element>(new cned_tablerow(this,ned_tablerow,idNewElement));
	break;
	case ned_patterntablerow:
		poNewElementSP = NewSCP<cned_element>(new cned_pattern_tablerow(this,idNewElement));
	break;
	case ned_tablecell:
		poNewElementSP = NewSCP<cned_element>(new cned_tablecell(this,idNewElement));
	break;
	case ned_breakline:
		poNewElementSP = NewSCP<cned_element>(new cned_break_line(this,idNewElement));
	break;
	case ned::ned_breakpage:
		poNewElementSP = NewSCP<cned_element>(new cned_break_page(this,idNewElement));
		m_nFormFeedCount++;
	break;
	case ned_tabmanagerheader:
		poNewElementSP = NewSCP<cned_element>(new cned_tabmanager_header_(this,idNewElement));
	break;
	case ned_tabmanager:
		poNewElementSP = NewSCP<cned_element>(new cned_tabmanager(this,idNewElement));
	break;
	case ned_tabitem:
		poNewElementSP = NewSCP<cned_element>(new cned_tabmanager_item(this,idNewElement));
	break;
	case ned_page_widgets:
		poNewElementSP = NewSCP<cned_element>(new cned_page_caption(this,idNewElement));
	break;
	case ned_extern:
		poNewElementSP = NewSCP<cned_element>(new cned_extern(this,idNewElement));
	break;
	case ned_olecontrol:
		poNewElementSP = NewSCP<cned_element>(new cned_olecontrol(this,ned_olecontrol,idNewElement));
	break;
	case ned_htmlwindow:
		poNewElementSP = NewSCP<cned_element>(new cned_web(this,idNewElement));
	break;
	case ned_hscroll:
		poNewElementSP = NewSCP<cned_element>(new cned_horiz_scrollbar(this,idNewElement));
	break;
	case ned_vscroll:
		poNewElementSP = NewSCP<cned_element>(new cned_vert_scrollbar(this,idNewElement));
	break;
	default:
		ASSERT(false);
		//ned_to_do: pozosta³e elementy
	}
	
	ASSERT(poNewElementSP.PointsObject());
	
	//powsta³o to co zamawialiœmy
	ASSERT(poNewElementSP->get_type() == eType);

	return poNewElementSP;
}

