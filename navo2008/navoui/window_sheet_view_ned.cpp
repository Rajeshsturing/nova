/*
	NAVO Enterprise 2003
	2003-05-05

	navo enhanced display (NED)

	window
	
	window sheet view
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
// cned_sheet_window_view
// page break (print preview) view
//----------------------------------------------------------------------
cned_sheet_window_view::cned_sheet_window_view(cned_window * poWindow) :
	cned_window_view__(poWindow),
	m_nCurrentSheetX(0),
	m_nCurrentSheetY(0),
	m_nZoom(100)
{
	//ned_to_do: na razie tu jest to zafixowane
	//ustawienia jak dla print previev
	//ned_to_do: m_oPaintParam.set_color_translation(ct_grayscale);
	//ned_to_do: m_oPaintParam.set_paint_mode(pm_printpreview);
}

SCP<cned_window_sheet> cned_sheet_window_view::get_current_sheet() const
{
	return get_sheet(m_nCurrentSheetX,m_nCurrentSheetY);
}

SCP<cned_window_sheet> cned_sheet_window_view::get_sheet(long nX,long nY) const
{
	ASSERT(nX >= 0);

	if(nX < m_oSheet2DArray.get_col_count())
	{
		if(nY < m_oSheet2DArray.get_row_count())
		{
			return (const_cast<cned_sheet_window_view*>(this))->m_oSheet2DArray.get_at(nY,nX);
		}
	}
	return SCP<cned_window_sheet> ();
}

void cned_sheet_window_view::add_new_sheet(long nX,long nY,SCP<cned_window_sheet> poSheetSP)
{
	while(nX >= m_oSheet2DArray.get_col_count())
	{
		m_oSheet2DArray.add_col();
	}
	while(nY >= m_oSheet2DArray.get_row_count())
	{
		m_oSheet2DArray.add_row();
	}
	m_oSheet2DArray.set_at(nY,nX,poSheetSP);
}

bool cned_sheet_window_view::is_inside_hit_area(const ng_point & roPoint) const
{
	return get_current_sheet()->is_inside_hit_area(roPoint);
}

SCP<cned_element> cned_sheet_window_view::get_element_on_ident(const ned_ident idElement) const
{
	return get_current_sheet()->get_element_on_ident(idElement);
}

SCP<cned_toplevelpage> cned_sheet_window_view::get_toplevelpage() const
{
	return get_current_sheet()->get_toplevelpage();
}

void cned_sheet_window_view::set_current_sheet_coord(long nX,long nY)
{
	if(nX != m_nCurrentSheetX || nY != m_nCurrentSheetY)
	{
		get_current_sheet()->on_being_current_sheet(false);
		m_nCurrentSheetX = nX;
		m_nCurrentSheetY = nY;
		get_current_sheet()->on_being_current_sheet(true);
	}
}

//------- transfer support --------
void cned_sheet_window_view::set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP)
{
	//ned_to_do:
}

SCP<nui_transfer> cned_sheet_window_view::get_transfer(ned_ident Ident)
{
	//ned_to_do:
	return SCP<nui_transfer> ();
}

void cned_sheet_window_view::start_transfer_iterator()
{
	//ned_to_do:
}

bool cned_sheet_window_view::next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP)
{
	//ned_to_do:
	return false;
}

//-------------- sys disable ---------------
void cned_sheet_window_view::set_sys_disable(bool bSysDisable)
{
	//ned_to_do:
}

bool cned_sheet_window_view::is_sys_disable() const
{
	//ned_to_do:
	return false;
}

//-------------- modified flag --------------
void cned_sheet_window_view::set_modified_flag(bool bModified)
{
	//ned_to_do:
}

bool cned_sheet_window_view::get_modified_flag() const
{
	//ned_to_do:
	return true;
}

long get_next_zoom_in(const long nZoom);
long get_next_zoom_out(const long nZoom);

void cned_sheet_window_view::on_event_zoom_in()
{
	set_zoom(get_next_zoom_in(get_zoom()));
}

void cned_sheet_window_view::on_event_zoom_out()
{
	set_zoom(get_next_zoom_out(get_zoom()));
}

long cned_sheet_window_view::get_zoom() const
{
	//ned_to_do:
	return m_nZoom;
}

void cned_sheet_window_view::set_zoom(long nZoom)
{
	if(nZoom == get_zoom())
	{
		return;
	}
	m_nZoom = nZoom;

	for(long nY = 0; nY < m_oSheet2DArray.get_row_count(); nY++)
	{
		for(long nX = 0; nX < m_oSheet2DArray.get_col_count(); nX++)
		{
			//ned_to_do: jeœli okno jest typu 'max' to nale¿y je zrenderowaæ ponownie
			//jeœli nie to ewentualnie podajemy scroll'a
			get_sheet(nX,nY)->set_zoom(nZoom);
		}
	}
	
	invalidate_view();
}


void cned_sheet_window_view::invalidate_view()
{
	SCP<cned_window_sheet> poCurrentSheetSP = get_current_sheet();
	if(poCurrentSheetSP.PointsObject())
	{
		poCurrentSheetSP->invalidate_sheet();
	}
}

void cned_sheet_window_view::on_window_on_top(bool bTopMost)
{
	get_current_sheet()->on_window_on_top(bTopMost);
}


//--------------------------------------------------------------------------
// paint
//--------------------------------------------------------------------------
void cned_sheet_window_view::paint(cned_painter_ & roArenaPainter)
{
	roArenaPainter.set_paint_param(m_oPaintParam);
	get_current_sheet()->paint(roArenaPainter);
}

void cned_sheet_window_view::_prepare_paint_region(ng_region & roRegion)
{
	get_current_sheet()->_prepare_paint_region(roRegion);
}

void cned_sheet_window_view::update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord)
{
	get_current_sheet()->update_layout(roAction,roResult,roCompletArenaRect,roPaintParam,yReqYcoord);
}

//-------------------------------------------------------------------------------------------------
// click
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	get_current_sheet()->on_event_mouse_click(roActionMouse,roResult);
}

//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	get_current_sheet()->on_event_timer(bTopWindow,roActionTimer,roResult);
}

//-------------------------------------------------------------------------------------------------
// over
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	get_current_sheet()->on_event_mouse_over(roActionMouse,roResult);
}

//-------------------------------------------------------------------------------------------------
// end click
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	get_current_sheet()->on_event_mouse_endclick(roActionMouse,roResult);
}

//-------------------------------------------------------------------------------------------------
// mouse wheel
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	get_current_sheet()->on_event_mouse_wheel(roActionMouseWheel,roResult);
}

//-------------------------------------------------------------------------------------------------
// key down
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::on_event_keydown(const ned_action_kbd &  roActionKBD,ned_action_result & roResult)
{
	get_current_sheet()->on_event_keydown(roActionKBD,roResult);
	
	if(roResult.is_processed())
	{
		return;
	}

	switch(roActionKBD.get_keycode())
	{
	case VK_UP:
	case VK_PRIOR:
		if(roActionKBD.is_CTRL() || (roActionKBD.get_keycode() == VK_PRIOR))
		{
			if(m_nCurrentSheetY > 0)
			{
				set_current_sheet_coord(m_nCurrentSheetX,m_nCurrentSheetY - 1);
				roResult.set_processed();
			};
		}
	break;
	case VK_DOWN:
	case VK_NEXT:
		if(roActionKBD.is_CTRL() || (roActionKBD.get_keycode() == VK_NEXT))
		{
			if(m_nCurrentSheetY < m_oSheet2DArray.get_row_count() - 1)
			{
				set_current_sheet_coord(m_nCurrentSheetX,m_nCurrentSheetY + 1);
				roResult.set_processed();
			}
		}
	break;
	case VK_LEFT:
		if(roActionKBD.is_CTRL())
		{
			if(m_nCurrentSheetX > 0)
			{
				set_current_sheet_coord(m_nCurrentSheetX - 1,m_nCurrentSheetY);
				roResult.set_processed();
			};
		}
	break;
	case VK_RIGHT:
		if(roActionKBD.is_CTRL())
		{
			if(m_nCurrentSheetX < m_oSheet2DArray.get_col_count() - 1)
			{
				set_current_sheet_coord(m_nCurrentSheetX + 1,m_nCurrentSheetY);
				roResult.set_processed();
			}
		}
	break;
	case VK_HOME:
		if(roActionKBD.is_CTRL())
		{
			if(m_nCurrentSheetY > 0 || m_nCurrentSheetX > 0)
			{
				set_current_sheet_coord(0,0);
				roResult.set_processed();
			}
		}
	break;
	case VK_END:
		if(roActionKBD.is_CTRL())
		{
			if((m_nCurrentSheetY < m_oSheet2DArray.get_row_count() - 1) ||
			    (m_nCurrentSheetX < m_oSheet2DArray.get_col_count() - 1))
			{
				set_current_sheet_coord(m_oSheet2DArray.get_col_count() - 1,m_oSheet2DArray.get_row_count() - 1);
				roResult.set_processed();
			}
		}
	break;
	}
}

//---------------------------------------------------------------------------------------------
//	size changed
//---------------------------------------------------------------------------------------------
void cned_sheet_window_view::on_event_size_changed(bool bWidthChange)
{
	for(long nY = 0; nY < m_oSheet2DArray.get_row_count(); nY++)
	{
		for(long nX = 0; nX < m_oSheet2DArray.get_col_count(); nX++)
		{
			//ned_to_do: jeœli okno jest typu 'max' to nale¿y je zrenderowaæ ponownie
			//jeœli nie to ewentualnie podajemy scroll'a
			get_sheet(nX,nY)->get_page()->set_measure_pending();
		}
	}
}

//---------------------------------------------------------------------------------------------
//	set_layout_invalid_to_all
//---------------------------------------------------------------------------------------------
void cned_sheet_window_view::set_layout_invalid_to_all()
{
	for(long nY = 0; nY < m_oSheet2DArray.get_row_count(); nY++)
	{
		for(long nX = 0; nX < m_oSheet2DArray.get_col_count(); nX++)
		{
			get_sheet(nX,nY)->set_layout_invalid_to_all();
		}
	}
}

//---------------------------------------------------------------------------------------------
//	style changed
//---------------------------------------------------------------------------------------------
void cned_sheet_window_view::on_event_style_changed()
{
	const ned_currattributes oAttributes;

	for(long nY = 0; nY < m_oSheet2DArray.get_row_count(); nY++)
	{
		for(long nX = 0; nX < m_oSheet2DArray.get_col_count(); nX++)
		{
			get_sheet(nX,nY)->apply_attributes(oAttributes);
		}
	}
	set_layout_invalid_to_all();
}


//---------------------------------------------------------------------------------------------
//	set cursor
//---------------------------------------------------------------------------------------------
eCursorType cned_sheet_window_view::on_event_set_cursor(const ng_point & roPoint)
{
	return get_current_sheet()->on_event_set_cursor(roPoint);
}


//---------------------------------------------------------------------------------------------
//   command
//---------------------------------------------------------------------------------------------
void cned_sheet_window_view::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	get_current_sheet()->on_event_command(roActionCommand,roResult);
}

//-------------------------------------------------------------------------------------------------
// after event
//-------------------------------------------------------------------------------------------------

void cned_sheet_window_view::_on_after_event(const ned_action__ & roAction,ned_action_result & roResult)
{
	get_current_sheet()->_on_after_event(roAction,roResult);
}

