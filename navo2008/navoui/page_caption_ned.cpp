/*
	NAVO Enterprise 2003
	2003-04-14

	navo enhanced display (NED)

	page caption element

*/

#include "stdafx.h"
#include "static_ned.h"
#include "picture_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------
//helper functions -----------------------------------
//-----------------------------------------------------------------------

SCP<cned_static> cned_page_caption::_get_title() const
{
	ASSERT(NEDID_NOTHING != m_idTitleStatic);
	
	return scp_cast_ui<cned_static>(get_element_on_ident(m_idTitleStatic));
}

SCP<cned_picture> cned_page_caption::_get_maximize_pic() const
{
	ASSERT(NEDID_NOTHING != m_idMaximizePic);

	return scp_cast_ui<cned_picture>(get_element_on_ident(m_idMaximizePic));
}

SCP<cned_picture> cned_page_caption::_get_close_pic() const
{
	ASSERT(NEDID_NOTHING != m_idMaximizePic);

	return scp_cast_ui<cned_picture>(get_element_on_ident(m_idCloseBoxPic));
}

void cned_page_caption::__construct_elements()
{
	//call it only once
	ASSERT(NEDID_NOTHING == m_idTitleStatic);
	ASSERT(NEDID_NOTHING == m_idCloseBoxPic);
	ASSERT(NEDID_NOTHING == m_idMaximizePic);

	//title text
	{
		SCP<cned_static> poTitleStaticSP = 
			scp_cast_ui<cned_static>(get_manager()->_create_element(ned_static,NEDID_NOTHING));
		poTitleStaticSP->_set_container(NewSCP<cned_container>(this,true));
		
		_link_element(poTitleStaticSP->get_ident(),NEDID_LAST);

		//skrótowa wersja bez apply attributes
		poTitleStaticSP->set_fixed_properties();

		ned_font_spec oTitleFontSpec;
		oTitleFontSpec.make_normal();
		oTitleFontSpec.m_nSize = 3;
		oTitleFontSpec.m_oFontNameString = _T("Tahoma");

		poTitleStaticSP->set_prop_fontinx(get_manager()->get_inx_for_font_spec(oTitleFontSpec));
		poTitleStaticSP->set_prop_forecolor(White);
		poTitleStaticSP->set_prop_ignore_sys_disable(true);

		m_idTitleStatic = poTitleStaticSP->get_ident();
	}

	//maximize picture
	{
		SCP<cned_picture> poMaximizePicSP = 
			scp_cast_ui<cned_picture>(get_manager()->_create_element(ned_picture,NEDID_NOTHING));

		poMaximizePicSP->_set_container(NewSCP<cned_container>(this,true));

		_link_element(poMaximizePicSP->get_ident(),NEDID_LAST);

		poMaximizePicSP->set_prop_imagesrc(CSmartOleVariant(-long(esi_maximize),VT_I4));
		poMaximizePicSP->set_fixed_properties();

		poMaximizePicSP->set_prop_ignore_sys_disable(true);
		poMaximizePicSP->set_prop_printable(true);
		ned_position oMPosition;
		//ned_to_do: przenieœæ te sta³e do metrics
		oMPosition.set_right(2540/92*18);	//2540 units/inch * 92dpi * 20 px
		poMaximizePicSP->set_decl_position(oMPosition);
		
		poMaximizePicSP->set_prop_hidden(get_container()->get_type() != ned_toplevelpage);

		m_idMaximizePic = poMaximizePicSP->get_ident();
	}

	//close box picture
	{
		SCP<cned_picture> poCloseBoxPicSP = 
			scp_cast_ui<cned_picture>(get_manager()->_create_element(ned_picture,NEDID_NOTHING));

		poCloseBoxPicSP->_set_container(NewSCP<cned_container>(this,true));

		_link_element(poCloseBoxPicSP->get_ident(),NEDID_LAST);

		poCloseBoxPicSP->set_prop_imagesrc(CSmartOleVariant(-long(esi_close_up),VT_I4));
		poCloseBoxPicSP->set_fixed_properties();
		if(get_container()->get_type() == ned_toplevelpage)
		{
			SCP<CHyperLinkInfo> poHyperLinkInfoSP = NewSCP(new CHyperLinkInfo());
			poHyperLinkInfoSP->SetNumProp(GVAR_CMD,CMD_GOBACK);
			poCloseBoxPicSP->set_prop_hyperlink(poHyperLinkInfoSP);
		}
		poCloseBoxPicSP->set_prop_ignore_sys_disable(true);
		poCloseBoxPicSP->set_prop_printable(true);
		//LANGUAGE:PL
		poCloseBoxPicSP->set_prop_tooltip_text(_T("Zamknij"));
		ned_position oCBPosition;
		//ned_to_do: przenieœæ te sta³e do metrics
		oCBPosition.set_right(2540/92*1);	//2540 units/inch * 92dpi * 2 px
		poCloseBoxPicSP->set_decl_position(oCBPosition);

		m_idCloseBoxPic = poCloseBoxPicSP->get_ident();
	}

	_update_internal_properties();
}

//-------------- property get ---------------
void cned_page_caption::get_prop_title(ng_string & roTitleString) const
{
	roTitleString = _get_title()->get_prop_text();
}

//-------------- property set ---------------
void cned_page_caption::set_prop_title(const ng_string & roTitleString)
{
	_get_title()->set_prop_text(roTitleString);
}


void cned_page_caption::_update_internal_properties()
{
	ng_color oBackColor;
	ng_color oBackColor2;
	SCP<cned_picture> poMaximizePicSP = _get_maximize_pic();

	if(m_bMaximized)
	{
		oBackColor = Transparent;
		oBackColor2 = Transparent;

		if(get_container()->get_type() == ned_toplevelpage)
		{
			SCP<CHyperLinkInfo> poHyperLinkSP = init_control_command_hli(get_container()->get_ident(),sccv_restore);
			poMaximizePicSP->set_prop_hyperlink(poHyperLinkSP);
			//LANGUAGE:PL
			poMaximizePicSP->set_prop_tooltip_text(_T("Przywróc"));
		}
	}
	else
	{
		if(m_bActive)
		{
			oBackColor = ng_color::system(COLOR_ACTIVECAPTION);
			oBackColor2 = ng_color::system(COLOR_GRADIENTACTIVECAPTION);
		}
		else
		{
			oBackColor = ng_color::system(COLOR_INACTIVECAPTION);
			oBackColor2 = ng_color::system(COLOR_INACTIVECAPTION);
		}
	
		if(get_container()->get_type() == ned_toplevelpage)
		{
			SCP<CHyperLinkInfo> poHyperLinkSP = init_control_command_hli(get_container()->get_ident(),sccv_maximize);
			poMaximizePicSP->set_prop_hyperlink(poHyperLinkSP);
			//LANGUAGE:PL
			poMaximizePicSP->set_prop_tooltip_text(_T("Maksymalizuj"));
		}
	}

	set_prop_backcolor(oBackColor);
	set_prop_backcolor2(oBackColor2);

	_get_title()->set_prop_hidden(m_bMaximized);
}

//------------------------------------------------------------------------------------------
// mouse click - forwarder (dblclick on title)
//------------------------------------------------------------------------------------------

void cned_page_caption::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_paragraph::process_event_mouse_click(roCallStack,roActionMouse,roResult);
	
	//w przypadku dbl-click na tytu³ -> wyœlij to samo co klikniêcie na maximize/restore
	if(roCallStack.target()->get_ident() == m_idTitleStatic && roActionMouse.is_DOUBLE_click())
	{
		SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
		poEventCmdSP->set_command(_get_maximize_pic()->get_prop_hyperlink());
		roResult.add_info(poEventCmdSP);
	}
	else
	{
		if(!roResult.is_processed() && roActionMouse.is_LEFT_click())
		{
			SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(get_container());
			if(poPageSP->get_prop_display_mode() == pdm_normal)
			{
				get_manager()->store_drag_info(NewSCP(new cned_drag_info_toplevelpage(roActionMouse.get_mouse_position())));
			}
			roResult.set_processed();
		}
	}
}

//------------------------------------------------------------------------------------------
// mouse click (dblclick on title)
//------------------------------------------------------------------------------------------
void cned_page_caption::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_DOUBLE_click())
	{
		SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
		poEventCmdSP->set_command(_get_maximize_pic()->get_prop_hyperlink());
		roResult.add_info(poEventCmdSP);
	}
	else
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(get_container());
		if(poPageSP->get_prop_display_mode() == pdm_normal)
		{
			get_manager()->store_drag_info(NewSCP(new cned_drag_info_toplevelpage(roActionMouse.get_mouse_position())));
		}
		roResult.set_processed();
	}
}

