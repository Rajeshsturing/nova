/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabmanagerheader / header <tab>
		tabmanager-header
		wewnêtrzny kontener w tab-manager
*/

#include "stdafx.h"
#include "static_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "tabitem_ned.h"
#include "tabmanager_header_ned.h"
#include "tabmanager_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--- notifications from tab-manager ----
void cned_tabmanager_header_::on_item_inserted(long nTabNr)
{
	/*
		bie¿¹ca implementacja pozwala dodawaæ zak³adki tylko na koñcu :(
	*/

	//need insert breakline
	if((nTabNr != 0) && ((nTabNr % get_prop_tabs_in_row()) == 0))
	{
		insert_new_element(ned_breakline,NEDID_NOTHING,NEDID_LAST);
	}

	_insert_title_item(NEDID_LAST);
}

void cned_tabmanager_header_::on_item_removed(long nTabNr)
{
	/*
		bie¿¹ca implementacja pozwala usuwaæ æ zak³adki tylko na koñcu :(
	*/

	remove_element(get_last_child_ident());
	if((nTabNr != 0) && ((nTabNr % get_prop_tabs_in_row()) == 0))
	{
		//need remove breakline
		remove_element(get_last_child_ident());
	}
}

ned_fontinx get_bolded_font(cned_element_manager * poManager,const ned_fontinx inxInputFont,bool bBolded);

void cned_tabmanager_header_::on_item_activate(long nTabNr,bool bActivate)
{
	SCP <cned_element> poStaticSP = get_element_on_ident(
		get_child_ident_on_pos(tab_nr_2_child_position(nTabNr)));
	poStaticSP->set_prop_fontinx(get_bolded_font(get_manager(),poStaticSP->get_prop_fontinx(),bActivate));
	poStaticSP->set_prop_border_type(bActivate ? NED_BORDER_STYLE_TABITEM_HEADER_UP : NED_BORDER_STYLE_TABITEM_HEADER_DOWN);
}

const ng_string & cned_tabmanager_header_::get_item_title(long nTabNr)
{
	SCP <cned_static> poStaticSP = scp_cast_ui<cned_static>(get_element_on_ident(
		get_child_ident_on_pos(tab_nr_2_child_position(nTabNr))));
	return poStaticSP->get_prop_text();
}

void cned_tabmanager_header_::set_item_title(long nTabNr,const ng_string & roTitleString)
{
	SCP <cned_static> poStaticSP = scp_cast_ui<cned_static>(get_element_on_ident(
		get_child_ident_on_pos(tab_nr_2_child_position(nTabNr))));
	poStaticSP->set_prop_text(roTitleString);
	poStaticSP->set_prop_charwidth(roTitleString.GetLength() + 2);
}

//----------------------- helpers ---------------------------------------------
void cned_tabmanager_header_::_insert_title_item(ned_ident idAfter)
{
	SCP <cned_static> poStaticSP = scp_cast_ui<cned_static>(insert_new_element(ned_static,NEDID_NOTHING,idAfter));
	SCP<CHyperLinkInfo> poHyperLinkSP = init_control_command_hli(get_container()->get_ident(),sccv_activate_item);
	poHyperLinkSP->SetNumProp(PROPC_VARIANT,poStaticSP->get_ident());
	poStaticSP->set_prop_hyperlink(poHyperLinkSP);
	poStaticSP->apply_attributes(get_current_attributes());
	poStaticSP->set_prop_border_width(2);
	poStaticSP->set_prop_border_type(NED_BORDER_STYLE_TABITEM_HEADER_DOWN);
	poStaticSP->set_prop_alignment(eal_center);
	poStaticSP->set_prop_ignore_sys_disable(true);
}
