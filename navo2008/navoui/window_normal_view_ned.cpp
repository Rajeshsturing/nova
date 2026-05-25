/*
	NAVO Enterprise 2003
	2003-05-05

	navo enhanced display (NED)

	window
	
	window normal view
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "arena_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------
// cned_normal_window_view 
// normal view
//----------------------------------------------------------------------
cned_normal_window_view::cned_normal_window_view(cned_window * poWindow,SCP<cned_window_sheet> poSheetSP) :
	cned_window_view__(poWindow),
	m_poSheetSP(poSheetSP)
{
}

bool cned_normal_window_view::is_inside_hit_area(const ng_point & roPoint) const
{
	ASSERT(m_poSheetSP.PointsObject());
	return m_poSheetSP->is_inside_hit_area(roPoint);
}


SCP<cned_element> cned_normal_window_view::get_element_on_ident(const ned_ident idElement) const
{
	ASSERT(m_poSheetSP.PointsObject());
	return m_poSheetSP->get_element_on_ident(idElement);
}

SCP<cned_toplevelpage> cned_normal_window_view::get_toplevelpage() const
{
	ASSERT(m_poSheetSP.PointsObject());
	return m_poSheetSP->get_toplevelpage();
}

//--------------------------------------------------------------------------
// paint
//--------------------------------------------------------------------------
void cned_normal_window_view::paint(cned_painter_ & roArenaPainter)
{
	roArenaPainter.set_paint_param(m_oPaintParam);
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->paint(roArenaPainter);
}

void cned_normal_window_view::_prepare_paint_region(ng_region & roRegion)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->_prepare_paint_region(roRegion);
}

void cned_normal_window_view::update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->update_layout(roAction,roResult,roCompletArenaRect,roPaintParam,yReqYcoord);
}

void cned_normal_window_view::update_split_info(cpb_split_info & roSplitInfo)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->update_split_info(roSplitInfo);
}

void cned_normal_window_view::make_split(cpb_split_manager & roSplitManager)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->make_split(roSplitManager);
}

//-------------------------------------------------------------------------------------------------
// click
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_mouse_click(roActionMouse,roResult);
}

//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_timer(bTopWindow,roActionTimer,roResult);
}

//-------------------------------------------------------------------------------------------------
// over
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_mouse_over(roActionMouse,roResult);
}

//-------------------------------------------------------------------------------------------------
// end click
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_mouse_endclick(roActionMouse,roResult);
}


//-------------------------------------------------------------------------------------------------
// mouse wheel
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_mouse_wheel(roActionMouseWheel,roResult);
}

//-------------------------------------------------------------------------------------------------
// key down
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_keydown(roActionKBD,roResult);
}

//---------------------------------------------------------------------------------------------
//	size changed
//---------------------------------------------------------------------------------------------
void cned_normal_window_view::on_event_size_changed(bool bWidthChange)
{
	//ned_to_do: jeœli okno jest typu 'max' to nale¿y je zrenderowaæ ponownie
	//jeœli nie to ewentualnie podajemy scroll'a
	m_poSheetSP->get_page()->set_measure_pending();
}

//---------------------------------------------------------------------------------------------
//	style changed
//---------------------------------------------------------------------------------------------
void cned_normal_window_view::on_event_style_changed()
{
	const ned_currattributes oAttributes;
	m_poSheetSP->apply_attributes(oAttributes);
	m_poSheetSP->set_layout_invalid_to_all();
}

//---------------------------------------------------------------------------------------------
//	set cursor
//---------------------------------------------------------------------------------------------
eCursorType cned_normal_window_view::on_event_set_cursor(const ng_point & roPoint)
{
	ASSERT(m_poSheetSP.PointsObject());
	return m_poSheetSP->on_event_set_cursor(roPoint);
}


//---------------------------------------------------------------------------------------------
//   command
//---------------------------------------------------------------------------------------------
void cned_normal_window_view::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_event_command(roActionCommand,roResult);
}

//-------------------------------------------------------------------------------------------------
// after event
//-------------------------------------------------------------------------------------------------

void cned_normal_window_view::_on_after_event(const ned_action__ & roAction,ned_action_result & roResult)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->_on_after_event(roAction,roResult);
}

//------- transfer support --------
void cned_normal_window_view::set_transfer(ned_ident idElement,SCP<nui_transfer> & rpoTransferSP)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->get_manager()->set_transfer(idElement,rpoTransferSP);
}


SCP<nui_transfer> cned_normal_window_view::get_transfer(ned_ident idElement)
{
	return m_poSheetSP->get_manager()->get_transfer(idElement);
}

void cned_normal_window_view::start_transfer_iterator()
{
	m_poSheetSP->get_manager()->start_transfer_iterator();
}

bool cned_normal_window_view::next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP)
{
	return m_poSheetSP->get_manager()->next_transfer_iterator(ridElement,rpoTransferSP);
}

//-------------- sys disable ---------------
void cned_normal_window_view::set_sys_disable(bool bSysDisable)
{
	ASSERT(m_poSheetSP.PointsObject());

	if(is_sys_disable() != bSysDisable)
	{
		m_poSheetSP->get_manager()->set_sys_disable(bSysDisable);
		invalidate_view();
	}
}

bool cned_normal_window_view::is_sys_disable() const
{
	ASSERT(m_poSheetSP.PointsObject());
	
	return m_poSheetSP->get_manager()->is_sys_disable();
}

//-------------- modified flag --------------
void cned_normal_window_view::set_modified_flag(bool bModified)
{
	ASSERT(m_poSheetSP.PointsObject());

	if(bModified)
	{
		m_poSheetSP->get_manager()->set_modified_flag();
	}
	else
	{
		m_poSheetSP->get_manager()->clear_modified_flag();
	}
}

bool cned_normal_window_view::get_modified_flag() const
{
	return m_poSheetSP->get_manager()->is_modified_flag();
}

long get_next_zoom_in(const long nZoom);
long get_next_zoom_out(const long nZoom);

void cned_normal_window_view::on_event_zoom_in()
{
	set_zoom(get_next_zoom_in(get_zoom()));
}

void cned_normal_window_view::on_event_zoom_out()
{
	set_zoom(get_next_zoom_out(get_zoom()));
}

long cned_normal_window_view::get_zoom() const
{
	ASSERT(m_poSheetSP.PointsObject());
	return m_poSheetSP->get_zoom();
}

void cned_normal_window_view::set_zoom(long nZoom)
{
	if(nZoom == get_zoom())
	{
		return;
	}
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->set_zoom(nZoom);
	invalidate_view();
}


void cned_normal_window_view::invalidate_view()
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->invalidate_sheet();
}

void cned_normal_window_view::on_window_on_top(bool bTopMost)
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->on_window_on_top(bTopMost);
}


//------ property GET -----------------
void cned_normal_window_view::get_prop_official_title(ng_string & roString) const
{
	ASSERT(m_poSheetSP.PointsObject());
	m_poSheetSP->get_prop_title(roString);
}

void cned_normal_window_view::set_layout_invalid_to_all()
{
	m_poSheetSP->set_layout_invalid_to_all();
}
