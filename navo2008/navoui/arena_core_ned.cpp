/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)


	cnui_arena
		- ca³e niezalezne srodowisko graficzne, oparte na oknie Win32

	core part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "arena_manager_ned.h"
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

//-------------------------------------------------------------------------------------------
//	cned_arena_integrator
//-------------------------------------------------------------------------------------------
cned_arena_integrator::cned_arena_integrator()
{
}

cned_arena_integrator::~cned_arena_integrator()
{
}

SCP<cned_arena> cned_arena_integrator::create_arena()
{
	SCP<cned_arena> poArenaSP = NewSCP(new cned_arena(this));
	m_oArenaArray.Add(poArenaSP.Get());
	return poArenaSP;
}
	
void cned_arena_integrator::on_arena_final_release(cned_arena * poArena)
{
	for(long iter = 0; iter < m_oArenaArray.GetSize(); iter++)
	{
		if(m_oArenaArray[ iter ] == poArena)
		{
			m_oArenaArray.RemoveAt(iter);
			delete poArena;
			return;
		}
	}
	ASSERT(false);	//???
}

void cned_arena_integrator::cancel_other_tooltips(cned_arena * poArena)
{
	for(long iter = 0; iter < m_oArenaArray.GetSize(); iter++)
	{
		if(m_oArenaArray[ iter ] != poArena)
		{
			m_oArenaArray[ iter ]->_internal_cancel_tooltip();
		}
	}
}

//-------------------------------------------------------------------------------------------

const ng_color _g_default_arena_backcolor = ng_color(RGB(0xAB,0xBE,0xE6));

cned_arena::cned_arena(cned_arena_integrator * poArenaIntegrator) :
	m_poArenaIntegrator(poArenaIntegrator),
	m_poArenaManagerSP(NewSCP(new cned_arena_manager())),
	m_oBackColor(_metrics().arena().get_backcolor()),
	m_oBackColor2(_metrics().arena().get_backcolor2()),
	m_hToolTipHwnd(HWND(NULL)),
	m_bToolTipVisible(false),
	m_nLastMouseFlags(0),
	m_bAnimateWindows(true)
{
}

cned_arena::~cned_arena()
{
	if(m_hToolTipHwnd != HWND(NULL))
	{
		::DestroyWindow(m_hToolTipHwnd);
		m_hToolTipHwnd = HWND(NULL);
	}
	//remove all windows before destroing arena
	//this will call cned-window:finalrelease and remove window from stack
	while(!m_oWindowStack.IsEmpty())
	{
		m_oWindowStack.RemoveHead();
	}
}

void cned_arena::OnFinalRelease()
{
	m_poArenaIntegrator->on_arena_final_release(this);
}

//-------------------------------------------------------------------------
//------ window management ------------------
//-------------------------------------------------------------------------

SCP<cned_window> cned_arena::create_window()
{
	return NewSCP(new cned_window(this));
}

SCP<cned_element_manager> cned_arena::_create_element_manager()
{
	return m_poArenaManagerSP->create_element_manager();
}

void cned_arena::on_window_final_release(cned_window * poWindow)
{
	remove_window_from_stack(poWindow);
	delete poWindow;
}

SCP<cned_window> cned_arena::get_top_window()
{
	if(m_oWindowStack.IsEmpty())
	{
		return SCP<cned_window>();
	}
	return m_oWindowStack.GetHead();
}

SCP<cned_window> cned_arena::get_bottom_window()
{
	if(m_oWindowStack.IsEmpty())
	{
		return SCP<cned_window>();
	}
	return m_oWindowStack.GetTail();
}

void cned_arena::add_window_to_stack(SCP<cned_window> poWindowToAddSP,cned_window * poWindowToBeAbove)
{
	cned_window * poOldTopWindow = m_oWindowStack.IsEmpty() ? NULL : m_oWindowStack.GetHead().Get();

	if(poWindowToBeAbove == NULL)
	{
		m_oWindowStack.AddHead(poWindowToAddSP);
	}
	else
	{
		POSITION pos = m_oWindowStack.GetHeadPosition();
		while(pos)
		{
			POSITION pos0 = pos;
			if(m_oWindowStack.GetNext(pos).Get() == poWindowToBeAbove)
			{
				m_oWindowStack.InsertAfter(pos0,poWindowToAddSP);
				goto finish;
			}
		}
		ASSERT(false);	//trying to add below non existing window or window not on stack (assert just for info)
	}
finish:
	{
		cned_window * poNewTopWindow = m_oWindowStack.IsEmpty() ? NULL : m_oWindowStack.GetHead().Get();
		if(poNewTopWindow != poOldTopWindow)
		{
			if(poOldTopWindow != NULL)
			{
				//notyfikacja ¿e przestaje byæ topmost
				poOldTopWindow->on_window_on_top(false,NULL);
			}
			if(poNewTopWindow != NULL)
			{
				//notyfikacja ¿e staje siê topmost 
				poNewTopWindow->on_window_on_top(true,NULL);
			}
		}
	}
	poWindowToAddSP->on_window_initial_update();
}

void cned_arena::remove_window_from_stack(cned_window * poWindow)
{
	ASSERT(poWindow);

	POSITION pos = m_oWindowStack.GetHeadPosition();
	while(pos)
	{
		POSITION pos0 = pos;
		if(m_oWindowStack.GetNext(pos).Get() == poWindow)
		{
			poWindow->on_window_final_update();
			m_oWindowStack.RemoveAt(pos0);
			cned_window * poNewTopWindow = m_oWindowStack.IsEmpty() ? NULL : m_oWindowStack.GetHead().Get();
			if(poNewTopWindow != NULL)
			{
				//notyfikacja nowego okna, ¿e staje siê 'topmost' 
				poNewTopWindow->on_window_on_top(true,NULL);
			}
			return;
		}
	}
}

void cned_arena::move_window_to_top(SCP<cned_window> poWindowToMoveSP)
{
	cned_window * poOldTopWindow = m_oWindowStack.IsEmpty() ? NULL : m_oWindowStack.GetHead().Get();

	ASSERT(poWindowToMoveSP.PointsObject());

	POSITION pos = m_oWindowStack.GetHeadPosition();
	while(pos)
	{
		POSITION pos0 = pos;
		if(m_oWindowStack.GetNext(pos).Get() == poWindowToMoveSP.Get())
		{
			m_oWindowStack.RemoveAt(pos0);
			m_oWindowStack.AddHead(poWindowToMoveSP);

			if(poWindowToMoveSP.Get() != poOldTopWindow)
			{
				if(poOldTopWindow != NULL)
				{
					//notyfikacja ¿e przestaje byæ topmost
					poOldTopWindow->on_window_on_top(false,poWindowToMoveSP.Get());
				}
				if(poWindowToMoveSP.Get() != NULL)
				{
					//notyfikacja ¿e staje siê topmost 
					poWindowToMoveSP->on_window_on_top(true,poOldTopWindow);
				}
			}
			return;
		}
	}
}

cned_window * cned_arena::_find_window_from_point(const ng_point & roPoint)
{
	POSITION pos = m_oWindowStack.GetHeadPosition();
	while(pos)
	{
		cned_window * poWindow = m_oWindowStack.GetNext(pos);
		if(poWindow->is_inside_hit_area(roPoint))
		{
			return poWindow;
		}
	}
	return NULL;
}

ng_point cned_arena::get_default_window_position(cned_window * poExcludeWindow) const
{
	{
		POSITION pos = m_oWindowStack.GetHeadPosition();
		ASSERT(pos);
		const cned_window * poWindow = m_oWindowStack.GetNext(pos);
		ASSERT(poExcludeWindow == poWindow);
		if(pos != NULL)
		{
			poWindow = m_oWindowStack.GetNext(pos);
			const ng_size & roWindowTopLeft = poWindow->get_toplevelpage()->get_arena_position();
			if(roWindowTopLeft.get_dy() < 9 * _metrics().arena().get_default_pos_y_increment() &&
				roWindowTopLeft.get_dx()	< 9 * _metrics().arena().get_default_pos_x_increment())
			{
				ng_point oPoint;
				oPoint.offset(roWindowTopLeft);
				oPoint.offset(_metrics().arena().get_default_pos_x_increment(),
					_metrics().arena().get_default_pos_y_increment());
				return oPoint;
			}
		}
		
		return ng_point();
	}

	ng_size oPosition;
	for(long iter = 0; iter < 10; iter++)
	{
		bool bColision = false;
		POSITION pos = m_oWindowStack.GetHeadPosition();
		while(pos)
		{
			const cned_window * poWindow = m_oWindowStack.GetNext(pos);
			if(poWindow != poExcludeWindow)
			{
				const ng_size & roWindowTopLeft = poWindow->get_toplevelpage()->get_arena_position();
				if(roWindowTopLeft.get_dy() + _metrics().arena().get_default_pos_y_increment() > oPosition.get_dy() &&
					roWindowTopLeft.get_dy() <= oPosition.get_dy())
				{
					if(roWindowTopLeft.get_dx() + _metrics().arena().get_default_pos_x_increment() > oPosition.get_dx() &&
						roWindowTopLeft.get_dx() <= oPosition.get_dx())
					{
						bColision = true;
						break;
					}
				}
			}
		}
		if(!bColision)
		{
			break;
		}
		oPosition = oPosition + 
			ng_size(_metrics().arena().get_default_pos_x_increment(),
					_metrics().arena().get_default_pos_y_increment());
	}

	return ng_point().offset(oPosition);
}

//-------------------------------------------------------------------------
//----- system connections ---------------------
//-------------------------------------------------------------------------
void cned_arena::attach_os_window(HWND hWnd)
{
	ASSERT(m_poArenaManagerSP.PointsObject());
	m_poArenaManagerSP->attach_os_window(hWnd);
}

void cned_arena::set_providers(const ng_string & roFullCachePathString,SCP<IGlobalInterfaceTable> poGITSP,
		DWORD dwAppDBManager_GIT_Cookie,DWORD dwCachedData_GIT_Cookie)
{
	ASSERT(m_poArenaManagerSP.PointsObject());
	
	m_poArenaManagerSP->set_providers(roFullCachePathString,poGITSP,
		dwAppDBManager_GIT_Cookie,dwCachedData_GIT_Cookie);
}

//-------------------- downlinks ---------------------------

bool cned_arena::is_invalid_paint_area() const
{
	return !m_poArenaManagerSP->get_invalid_paint_area().is_empty();
}

void cned_arena::external_invalidate_paint(const ng_rect & roExternalRepaintRect)
{
	m_poArenaManagerSP->invalidate_paint_rect(roExternalRepaintRect);
}

void cned_arena::internal_invalidate_paint_rect(const ng_rect & roAbsoluteRect)
{
	m_poArenaManagerSP->invalidate_paint_rect(roAbsoluteRect);
}

const ng_rect & cned_arena::get_screen_arena() const
{
	return m_poArenaManagerSP->get_screen_arena();
}

//---------------- font provider ----------------
void cned_arena::set_current_style(const CSmartOleVariant & roStyleSOV)
{
	if(!m_poArenaManagerSP->set_current_style(roStyleSOV))
	{
		return;
	}

	POSITION pos = m_oWindowStack.GetTailPosition();
	while(pos)
	{
		m_oWindowStack.GetPrev(pos)->on_event_style_changed();
	}
}


void cned_arena::set_prop_backcolor(ng_color clrBack)
{
	if(get_prop_backcolor() == clrBack)
	{
		return;
	}
	m_oBackColor = clrBack;
	m_poArenaManagerSP->invalidate_paint_rect(m_poArenaManagerSP->get_screen_arena());
}

void cned_arena::set_prop_backcolor2(ng_color clrBack)
{
	if(get_prop_backcolor2() == clrBack)
	{
		return;
	}
	m_oBackColor2 = clrBack;
	m_poArenaManagerSP->invalidate_paint_rect(m_poArenaManagerSP->get_screen_arena());
}


