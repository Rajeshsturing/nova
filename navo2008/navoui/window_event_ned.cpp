/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	window
	
	events handling
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"
#include "arena_manager_ned.h"
#include "arena_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----- window live cycle events ---------------
void cned_window::on_window_initial_update()
{
	ASSERT(m_eActiveView == wv_normal);
	//just to start invalidating process
	
	//info:
	// generalnie okno siê odmaluje przy pierwszej okazji
	//w rzadkich sytuacjach (pushpage robione z VB)
	//mo¿e byæ opóŸnienie
	//jeœli bêdzie Ÿle to odkomentuj:

	//	invalidate_paint_rect(ng_rect(0,0,0,0));
}

void cned_window::on_window_final_update()
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->invalidate_view();

	_prepare_special_paint(wse_collapse);
}

void cned_window::on_window_on_top(bool bTopMost,cned_window * poSecondWindow)
{
	_get_active_view()->on_window_on_top(bTopMost);

	if(bTopMost && poSecondWindow != NULL)
	{
		animate_rect_effect oARE;
		
		poSecondWindow->get_toplevelpage()->get_page_rect(oARE.m_oStartingRect);
		get_toplevelpage()->get_page_rect(oARE.m_oEndingRect);

		m_poArena->add_animate_rect_effect(oARE);
	}
}

//---------------------------------------------------------------------------------------------
//	size changed
//---------------------------------------------------------------------------------------------

void cned_window::on_event_size_changed(bool bWidthChange)
{
	m_poNormalViewSP->on_event_size_changed(bWidthChange);
	m_poSheetViewSP->on_event_size_changed(bWidthChange);	
}


//---------------------------------------------------------------------------------------------
//	style changed
//---------------------------------------------------------------------------------------------

void cned_window::on_event_style_changed()
{
	m_poNormalViewSP->on_event_style_changed();
	m_poSheetViewSP->on_event_style_changed();	
}

//---------------------------------------------------------------------------------------------
//	on_event_set_cursor
//---------------------------------------------------------------------------------------------

eCursorType cned_window::on_event_set_cursor(const ng_point & roPoint)
{
	return _get_active_view()->on_event_set_cursor(roPoint);
}

//-------------------------------------------------------------------------------------------------
// click
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	_get_active_view()->on_event_mouse_click(roActionMouse,roResult);
	_on_after_event(roActionMouse,roResult);
	m_poArena->cancel_tooltip();
}

//-------------------------------------------------------------------------------------------------
// over
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	_get_active_view()->on_event_mouse_over(roActionMouse,roResult);
	_on_after_event(roActionMouse,roResult);
	m_poArena->cancel_tooltip();
}

//-------------------------------------------------------------------------------------------------
// end click
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	_get_active_view()->on_event_mouse_endclick(roActionMouse,roResult);
	_on_after_event(roActionMouse,roResult);
	m_poArena->cancel_tooltip();
}

void cned_window::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	_get_active_view()->on_event_mouse_wheel(roActionMouseWheel,roResult);
	_on_after_event(roActionMouseWheel,roResult);
	m_poArena->cancel_tooltip();
}


//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->on_event_timer(bTopWindow,roActionTimer,roResult);
}

//-------------------------------------------------------------------------------------------------
// zoom
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_zoom_in()
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->on_event_zoom_in();
}

void cned_window::on_event_zoom_out()
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->on_event_zoom_out();
}


//-------------------------------------------------------------------------------------------------
// command
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	_get_active_view()->on_event_command(roActionCommand,roResult);
}

void cned_window::_update_layout_for_display(const ned_action__ & roAction,
	ned_action_result & roResult,const ng_rect & roCompleteArena)
{
	cned_paint_param oPaintParam;

	ASSERT(_get_active_view() != NULL);

	_get_active_view()->update_layout(roAction,roResult,roCompleteArena,
		oPaintParam,roCompleteArena.get_bottom());

	_realize_initial_position(roCompleteArena);
	_on_after_event(roAction,roResult);
}

void cned_window::_prepare_paint_region(ng_region & roRegion)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->_prepare_paint_region(roRegion);
}

void cned_window::_paint(cned_painter_ & roArenaPainter)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->paint(roArenaPainter);
}

void cned_window::_prepare_special_paint(ened_window_special_effect eWSE)
{
	ASSERT(m_eActiveView == wv_normal);

	animate_rect_effect oARE;

	//ned_to_do: to nie jest eleganckie rozwi¹zanie,
	//gdy¿ ignoruje fakt istnienia view, a po nimi sheet

	ng_rect oTopPageRect;
	get_toplevelpage()->get_page_rect(oTopPageRect);
	
	const ng_rect & roArenaRect = m_poArena->get_screen_arena();
	
	switch(eWSE)
	{
	case wse_expand:
		oARE.m_oStartingRect = ng_rect(roArenaRect.get_centerpoint(),ng_size());
		oARE.m_oEndingRect = oTopPageRect;
	break;
	case wse_collapse:
		oARE.m_oStartingRect = oTopPageRect;
		oARE.m_oEndingRect = ng_rect(roArenaRect.get_centerpoint(),ng_size());
	break;
	case wse_migrate_to_corner:
		oARE.m_oStartingRect = oTopPageRect;
		oARE.m_oEndingRect = ng_rect(roArenaRect.get_bottomright(),ng_size());
	break;
	case wse_migrate_to_center:
		oARE.m_oStartingRect = ng_rect(roArenaRect.get_bottomright(),ng_size());
		oARE.m_oEndingRect = oTopPageRect;
	break;
	default:
		ASSERT(false);
	}

	m_poArena->add_animate_rect_effect(oARE);
}


//-------------------- event helpers ----------------------------------------

bool cned_window::is_inside_hit_area(const ng_point & roPoint) const
{
	return _get_active_view()->is_inside_hit_area(roPoint);
}


//--- process results of event ---------------
void cned_window::_on_after_event(const ned_action__ & roAction,ned_action_result & roResult)
{
	_get_active_view()->_on_after_event(roAction,roResult);
}

//---------------------------------------------------------------------------------------------
