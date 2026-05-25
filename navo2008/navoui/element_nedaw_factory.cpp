/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display automation wrappers (NEDAW)
	
	element definition

*/

#include "stdafx.h"
#include "element_nedaw.h"
#include "container_nedaw.h"

using namespace nedaw;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


SCP<nedaw::cnedaw_element> construct_nedaw(SCP<ned::cned_element> poElementSP)
{
	ASSERT(poElementSP.PointsObject());
	
	switch(poElementSP->get_type())
	{
	case ned::ned_static:
	case ned::ned_button:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_static(poElementSP));
	case ned::ned_staticex:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_staticex(poElementSP));
	case ned::ned_tablecell:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_table_cell(poElementSP));
	case ned::ned_checkbox:
	case ned::ned_radio:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_option_button_(poElementSP));
	case ned::ned_picture:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_picture(poElementSP));
	case ned::ned_textedit:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_textedit(poElementSP));
	case ned::ned_currency:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_curr_edit(poElementSP));
	case ned::ned_date:
	case ned::ned_timeed:
	case ned::ned_intedit:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_edit__(poElementSP));
	case ned::ned_multiline:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_multiedit(poElementSP));
	case ned::ned_olecontrol:
	case ned::ned_htmlwindow:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_olecontrol(poElementSP));
	case ned::ned_table:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_table(poElementSP));
	case ned::ned_grid:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_grid(poElementSP));
	case ned::ned_tablerow:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_tablerow(poElementSP));
	case ned::ned_subpage:
	case ned::ned_toplevelpage:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_page(poElementSP));
	case ned::ned_tabmanager:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_tabmanager(poElementSP));
	case ned::ned_tabitem:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_tabmanager_item(poElementSP));
	case ned::ned_paragraph:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_paragraph(poElementSP));
	case ned::ned_tablesection:
	case ned::ned_tablebodysection:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_table_section(poElementSP));
	case ned::ned_spreadbodysection:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_gridbody_section(poElementSP));
		
	case ned::ned_breakline:
	case ned::ned_breakpage:
	case ned::ned_extern:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_element(poElementSP));
	case ned::ned_hscroll:
	case ned::ned_vscroll:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_scrollbar(poElementSP));
	case ned::ned_page_widgets:
		return NewSCP<nedaw::cnedaw_element>(new cnedaw_pagecaption(poElementSP));
	default:
		ASSERT(false);
		return SCP<nedaw::cnedaw_element>();
	}
}

