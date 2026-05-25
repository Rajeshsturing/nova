/*
	NAVO Enterprise 2003
	2003-04-23

	navo enhanced display (NED)

	scroll_helper__
	
	wsparcie dla scrolowania
*/
#include "stdafx.h"
#include "scroll_helper_ned.h"
#include "picture_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "scrollbar_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void scroll_helper__::_update_controls()
{
	//update controls with new m_oTotalSize,m_oPageSize,m_oPositionSize
	if(_is_vert_bar())
	{
		SCP<cned_vert_scrollbar> poVScrollSP = _get_vert_bar();
		poVScrollSP->set_prop_position(m_oPositionSize.get_dy());
	}
}

ng_xdist scroll_helper__::show_vertical_bar(cned_renderer_ & roRenderer,
										const ng_point & roScrollTopLeft,const ng_ydist yHeight,
										long nTotalRange,long nPageRange)
{
	m_oTotalSize.set_dy(nTotalRange);
	m_oPageSize.set_dy(nPageRange);
	_normalize();

	SCP<cned_vert_scrollbar> poVScrollSP;
	if(!_is_vert_bar())
	{
		poVScrollSP = scp_cast_ui<cned_vert_scrollbar>(_get_manager()->_create_element(ned_vscroll,NEDID_NOTHING));
		poVScrollSP->_set_container(_get_owner());
		poVScrollSP->set_mode_embedded();
		//do-not-link

		poVScrollSP->apply_attributes(_get_owner()->get_current_attributes());
		m_idVertBar = poVScrollSP->get_ident();
		m_oPositionSize.set_dy(0);
	}
	else
	{
		poVScrollSP = _get_vert_bar();
	}

	ASSERT(poVScrollSP.PointsObject());

	poVScrollSP->set_prop_extheight(_get_manager()->to_external(ng_size(0,yHeight)).get_dy());
	poVScrollSP->set_prop_total_range(nTotalRange);
	poVScrollSP->set_prop_page_range(nPageRange);

	//------------------------------------------------------------------------------
	//wylicz rozmiar scroll'a
	//------------------------------------------------------------------------------
	cned_metrics oScrollBarMetrics;
	{
		ned_measure_param oMParam(roRenderer.get_info_dc(),roRenderer.get_paint_mode(),
			roRenderer.get_req_y(),roRenderer.get_complete_arena());
		poVScrollSP->get_metrics(oMParam,oScrollBarMetrics);
	}

	cned_column_renderer oColumnRender(roRenderer,roScrollTopLeft,oScrollBarMetrics.get_minimal_width());
	poVScrollSP->render(oColumnRender);

	return oScrollBarMetrics.get_minimal_width();
}

void scroll_helper__::hide_vertical_bar()
{
	if(_is_vert_bar())
	{
		_get_vert_bar()->remove_children(true);
		_get_manager()->_remove_element(m_idVertBar);
	
		m_oPositionSize.set_dy(0);
		m_oTotalSize.set_dy(0);
		m_oPageSize.set_dy(0);
		_normalize();

		m_idVertBar = NEDID_NOTHING;
	}
}

ng_ydist scroll_helper__::show_horizontal_bar(cned_renderer_ & roRenderer,const ng_point & roScrollTopLeft,const ng_xdist xWidth,long nTotalRange,long nPageRange)
{
	m_oTotalSize.set_dx(nTotalRange);
	m_oPageSize.set_dx(nPageRange);
	_normalize();

	SCP<cned_horiz_scrollbar> poHScrollSP;
	if(!_is_horiz_bar())
	{
		poHScrollSP = scp_cast_ui<cned_horiz_scrollbar>(_get_manager()->_create_element(ned_hscroll,NEDID_NOTHING));
		poHScrollSP->_set_container(_get_owner());
		poHScrollSP->set_mode_embedded();
		//do-not-link

		poHScrollSP->apply_attributes(_get_owner()->get_current_attributes());
		m_idHorizBar = poHScrollSP->get_ident();
		m_oPositionSize.set_dx(0);
	}
	else
	{
		poHScrollSP = _get_horiz_bar();
	}

	ASSERT(poHScrollSP.PointsObject());

	poHScrollSP->set_prop_extwidth(_get_manager()->to_external(ng_size(xWidth,0)).get_dx());
	poHScrollSP->set_prop_total_range(nTotalRange);
	poHScrollSP->set_prop_page_range(nPageRange);

	//------------------------------------------------------------------------------
	//wylicz rozmiar scroll'a
	//------------------------------------------------------------------------------
	cned_metrics oScrollBarMetrics;
	{
		ned_measure_param oMParam(roRenderer.get_info_dc(),roRenderer.get_paint_mode(),
			roRenderer.get_req_y(),roRenderer.get_complete_arena());
		poHScrollSP->get_metrics(oMParam,oScrollBarMetrics);
	}

	cned_column_renderer oColumnRender(roRenderer,roScrollTopLeft,oScrollBarMetrics.get_minimal_width());
	poHScrollSP->render(oColumnRender);

	return oScrollBarMetrics.get_minimal_height();
}

void scroll_helper__::hide_horizontal_bar()
{
	if(_is_horiz_bar())
	{
		_get_horiz_bar()->remove_children(true);
		_get_manager()->_remove_element(m_idHorizBar);
	
		m_oPositionSize.set_dx(0);
		m_oTotalSize.set_dx(0);
		m_oPageSize.set_dx(0);
		_normalize();

		m_idHorizBar = NEDID_NOTHING;
	}
}


bool scroll_helper__::_scroll_is_inside_hit_area(const ng_point & roPoint)
{
	if(_is_vert_bar())
	{
		if(_get_vert_bar()->is_inside_hit_area(roPoint))
		{
			return true;
		}
	}
	if(_is_horiz_bar())
	{
		if(_get_horiz_bar()->is_inside_hit_area(roPoint))
		{
			return true;
		}
	}
	return false;
}

ned_ident scroll_helper__::_scroll_find_element_from_point(const ng_point & roPoint)
{
	if(_is_vert_bar())
	{
		if(_get_vert_bar()->is_inside_hit_area(roPoint))
		{
			ned_ident idElement = _get_vert_bar()->find_element_from_point(roPoint);
			if(idElement != NEDID_NOTHING)
			{
				return idElement;
			}
		}
	}
	if(_is_horiz_bar())
	{
		if(_get_horiz_bar()->is_inside_hit_area(roPoint))
		{
			ned_ident idElement = _get_horiz_bar()->find_element_from_point(roPoint);
			if(idElement != NEDID_NOTHING)
			{
				return idElement;
			}
		}
	}

	return NEDID_NOTHING;
}

//------- paint support ------------------------------------------------------------

void scroll_helper__::_scroll_draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	if(_is_vert_bar())
	{
		_get_vert_bar()->draw_foreground(roForePainter,roCurrentPoint);
	}
	if(_is_horiz_bar())
	{
		_get_horiz_bar()->draw_foreground(roForePainter,roCurrentPoint);
	}
}

void scroll_helper__::_scroll_draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	if(_is_vert_bar())
	{
		_get_vert_bar()->draw_background(roBackPainter,roCurrentPoint);
	}
	if(_is_horiz_bar())
	{
		_get_horiz_bar()->draw_background(roBackPainter,roCurrentPoint);
	}
}


SCP<cned_vert_scrollbar> scroll_helper__::_get_vert_bar()
{
	ASSERT(_is_vert_bar());
	return scp_cast_ui<cned_vert_scrollbar>(_get_manager()->get_element_on_ident(m_idVertBar));
}

SCP<cned_horiz_scrollbar> scroll_helper__::_get_horiz_bar()
{
	ASSERT(_is_horiz_bar());
	return scp_cast_ui<cned_horiz_scrollbar>(_get_manager()->get_element_on_ident(m_idHorizBar));
}

//--------------------------------------------------------------------------------------------------
void scroll_helper__::_physical_scroll(const ng_size & roDistanceSize,ng_dc & roDC,const ng_rect & roScrollableRect)
{
	perform_scroll_param oPSP;
	//setup parameters
	oPSP.m_oArenaCompleteRect = m_poManager->get_screen_arena();
	oPSP.m_oArenaSrcRect = roScrollableRect;
	oPSP.m_oDistance = roDistanceSize;
	oPSP.m_poDC = &roDC;

	_perform_scroll(oPSP);
	
	//consume results
	m_poManager->invalidate_paint_rect(oPSP.m_oArenaInvalidRectX);
	m_poManager->invalidate_paint_rect(oPSP.m_oArenaInvalidRectY);
}
	
//--------------------------------------------------------------------------------------------------
// events
//--------------------------------------------------------------------------------------------------
void scroll_helper__::_scroll_event_wheel(const ned_action_mouse_wheel & roActionMouseWheel,
	ned_action_result & roResult,const ng_rect & roScrollableRect)
{
	ng_size oScrolledSize = _logical_scroll_by(ng_size(0,-roActionMouseWheel.get_delta()));
	
	if(oScrolledSize != ng_size())
	{
		_physical_scroll(oScrolledSize,roActionMouseWheel.get_dc(),roScrollableRect);
		_update_controls();

		roResult.set_processed();
	}
}

void scroll_helper__::_scroll_event_kbd(const ned_action_kbd & roActionKBD,ned_action_result & roResult,
		const ng_rect & roScrollableRect)
{
	ng_size oScrollBySize;
	switch(roActionKBD.get_keycode())
	{
	case VK_UP:
		oScrollBySize.set_dy(-m_oPageSize.get_dy() / 10);
	break;
	case VK_DOWN:
		oScrollBySize.set_dy(m_oPageSize.get_dy() / 10);
	break;
	case VK_LEFT:
		oScrollBySize.set_dx(-m_oPageSize.get_dx() / 10);
	break;
	case VK_RIGHT:
		oScrollBySize.set_dx(m_oPageSize.get_dx() / 10);
	break;
	case VK_PRIOR:
		oScrollBySize.set_dy(-m_oPageSize.get_dy());
	break;
	case VK_NEXT:
		oScrollBySize.set_dy(m_oPageSize.get_dy());
	break;
	}

	ng_size oScrolledSize = _logical_scroll_by(oScrollBySize);
	if(oScrolledSize != ng_size())
	{
		_physical_scroll(oScrolledSize,roActionKBD.get_dc(),roScrollableRect);
		_update_controls();

		roResult.set_processed();
	}
}

void scroll_helper__::_scroll_event_command(const ned_action_command & roActionCommand,
		ned_action_result & roResult,const ng_rect & roScrollableRect)
{
	if(roActionCommand.get_verb() == sccv_scroll_to)
	{
		ng_size oScrollPosSize = get_scroll_pos();
		if(roActionCommand.get_command()->PropertyExists(PROPC_YPOSITION))
		{
			oScrollPosSize.set_dy(roActionCommand.get_command()->GetNumProp(PROPC_YPOSITION));
		}
		if(roActionCommand.get_command()->PropertyExists(PROPC_XPOSITION))
		{
			oScrollPosSize.set_dx(roActionCommand.get_command()->GetNumProp(PROPC_XPOSITION));
		}
		ng_size oScrolledSize = _logical_scroll_to(oScrollPosSize);
		if(oScrolledSize != ng_size())
		{
			_physical_scroll(oScrolledSize,roActionCommand.get_dc(),roScrollableRect);
			_update_controls();

		}
//		roResult.set_processed();
	}
}
