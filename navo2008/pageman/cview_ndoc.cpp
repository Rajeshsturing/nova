/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_view__
		base view (just for integration)
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navothread.h"		//navo thread
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"
#include "application_ndoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cndoc_view__::cndoc_view__(eViewType eVT,cndoc_mainwindow * poMainWindow) :
	m_poMainWindow(poMainWindow),
	m_eVT(eVT)
{
}

cndoc_view__::~cndoc_view__()
{
}

void cndoc_view__::PostNcDestroy()
{
	delete this;
}

void cndoc_view__::OnFinalRelease()
{
	ASSERT(m_poMainWindow);
	m_poMainWindow->on_view_final_release(this);
}


BEGIN_MESSAGE_MAP(cndoc_view__, CWnd)
	//{{AFX_MSG_MAP(cndoc_view__)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CNavoException & cndoc_view__::GetErrorStorage()
{
	return m_poMainWindow->get_application()->GetErrorStorage();
}


/////////////////////////////////////////////////////////////////////////////
// cndoc_view__ message handlers
/////////////////////////////////////////////////////////////////////////////
// cndoc_navoview

cndoc_navoview::cndoc_navoview(eViewType eVT,cndoc_mainwindow * poMainWindow,SCP<cned_arena> poArenaSP) :
	cndoc_view__(eVT,poMainWindow),
	cndoc_navoview_impl(poMainWindow)
{
	ASSERT(poArenaSP.PointsObject());
	set_arena(poArenaSP);
}

cndoc_navoview::~cndoc_navoview()
{
}

void cndoc_navoview::create()
{
	ASSERT(m_poMainWindow);
	ASSERT(m_poMainWindow->m_hWnd != HWND(NULL));

	//OS_API_CALL
	VERIFY(cndoc_view__::CreateEx(WS_EX_CLIENTEDGE,NULL,"",(WS_CHILD),
		0,0,100,100,m_poMainWindow->m_hWnd,NULL));

	ASSERT(m_hWnd != HWND(NULL));
	attach_window(m_hWnd);
}


BEGIN_MESSAGE_MAP(cndoc_navoview, cndoc_view__)
	//{{AFX_MSG_MAP(cndoc_navoview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_SYSCHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cndoc_navoview message handlers
/////////////////////////////////////////////////////////////////////////////

void cndoc_navoview::OnPaint() 
{
	ALL_TRY
	{
		CPaintDC dc(this); //calls begin-end paint and validates update region
		ng_rect oUpdateRect(dc.m_ps.rcPaint.left,dc.m_ps.rcPaint.top,dc.m_ps.rcPaint.right,dc.m_ps.rcPaint.bottom);
		on_paint_event(oUpdateRect);
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		GetErrorStorage() += roNavoException;
	}
}

void cndoc_navoview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	on_left_button_down_event(nFlags,ng_point(point.x,point.y));
}

void cndoc_navoview::OnLButtonUp(UINT nFlags, CPoint point) 
{
	on_left_button_up_event(nFlags,ng_point(point.x,point.y));
}

void cndoc_navoview::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	on_left_button_dbl_click_event(nFlags,ng_point(point.x,point.y));
}

void cndoc_navoview::OnMouseMove(UINT nFlags, CPoint point) 
{
	on_mouse_move_event(nFlags,ng_point(point.x,point.y));
}

BOOL cndoc_navoview::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) 
{
	//OS_API_CALL
	ScreenToClient(&point);
	on_mouse_wheel_event(nFlags,long(zDelta),ng_point(point.x,point.y));
	return TRUE;
}

void cndoc_navoview::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	on_key_down_event(nChar,nRepCnt,nFlags);
}

void cndoc_navoview::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	ALL_TRY
	{
		if(!on_key_down_event(nChar,nRepCnt,nFlags))
		{
			cndoc_view__::OnSysChar(nChar, nRepCnt, nFlags);
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		GetErrorStorage() += roNavoException;
	}
}

void cndoc_navoview::OnRButtonDown(UINT nFlags, CPoint point) 
{
	on_right_button_down_event(nFlags,ng_point(point.x,point.y));
}

void cndoc_navoview::OnRButtonUp(UINT nFlags, CPoint point) 
{
	on_right_button_up_event(nFlags,ng_point(point.x,point.y));
}

void cndoc_navoview::OnSize(UINT nType, int cx, int cy) 
{
	ALL_TRY
	{
		cndoc_view__::OnSize(nType, cx, cy);
		attach_window(m_hWnd);
		on_size_changed_event();
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		GetErrorStorage() += roNavoException;
	}
}

BOOL cndoc_navoview::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	return (on_set_cursor_event() != false);
}

void cndoc_navoview::OnTimer(UINT nIDEvent)
{
	on_timer_event(nIDEvent);
}

void cndoc_navoview::on_timer_event(UINT nIDEvent)
{
	on_time_elapsed_event(nIDEvent);
}

void cndoc_navoview::update()
{
	update_view();
}

bool cndoc_navoview::on_idle()
{
	on_idle_event();
	return false;
}

void cndoc_navoview::_get_client_rect(ng_rect & roClientRect)
{
	//OS_API_CALL
	RECT oClientWinRect;
	::GetClientRect(m_hWnd,&oClientWinRect);
	roClientRect = ng_rect(oClientWinRect.left,oClientWinRect.top,oClientWinRect.right,oClientWinRect.bottom);
}
