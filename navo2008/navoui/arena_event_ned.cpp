/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)


	cnui_arena
		- ca³e niezalezne srodowisko graficzne, oparte na oknie Win32

	external event part
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\internal_h1000.h"
#include "arena_manager_ned.h"
#include "arena_ned.h"
#include "window_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cned_arena::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionKBD,roResult);

#ifdef _DEVELOPER_EDITION_
	if(roActionKBD.get_keycode() == VK_F11)
	{
		//wymuœ odmalowanie ca³oœci
		//m_poArenaManagerSP->invalidate_paint_rect(m_poArenaManagerSP->get_screen_arena());
		//return;
		_debug_bDrawResized_as_red = !_debug_bDrawResized_as_red;
	}
#endif

	SCP<cned_window> poWindowSP = get_top_window();
	if(poWindowSP.PointsNull())
	{
		return;
	}

	poWindowSP->on_event_keydown(roActionKBD,roResult);

	//finally call
	_on_after_event(roActionKBD,roResult);
}
	
void cned_arena::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionMouse,roResult);

	_update_last_mouse_position(roActionMouse);

	//OS_API_CALL
	::SetCapture(m_poArenaManagerSP->get_os_window());

	cned_window * poFoundWindow = _find_window_from_point(roActionMouse.get_mouse_position());
	
	if(poFoundWindow == NULL)
	{
		//not on any window - post command "arena click"
		SCP<ned_event_command> poEventCmdSP = _prepare_arena_click_command(roActionMouse.is_LEFT_click());
		roResult.add_info(poEventCmdSP);
		return;
	}

	if(get_top_window().Get() != poFoundWindow)	
	{
		//clicking not on top window
		//post command "activate"
		SCP<ned_event_command> poEventCmdSP = _prepare_acvitate_window_command(poFoundWindow);
		roResult.add_info(poEventCmdSP);
		return;
	}
	
	//click on top window
	poFoundWindow->on_event_mouse_click(roActionMouse,roResult);

	//finally call
	_on_after_event(roActionMouse,roResult);
}

void cned_arena::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionMouse,roResult);

	_update_last_mouse_position(roActionMouse);

	SCP<cned_window> poWindowSP = get_top_window();
	if(poWindowSP.PointsObject())
	{
		poWindowSP->on_event_mouse_endclick(roActionMouse,roResult);
		
		//finally call
		_on_after_event(roActionMouse,roResult);
	}
	//OS_API_CALL
	::ReleaseCapture();
}

void cned_arena::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionMouse,roResult);

	if(!_update_last_mouse_position(roActionMouse))
	{
		return;
	}

	SCP<cned_window> poWindowSP = get_top_window();
	if(poWindowSP.PointsObject())
	{
		//always process message when dragging
		bool bProcess = roActionMouse.is_LEFT_click();
		
		//but when not dragging process only when cursor is over top window
		if(!bProcess)
		{
			//fast test for top window only
			bProcess = poWindowSP->is_inside_hit_area(roActionMouse.get_mouse_position());
		}
		if(bProcess)
		{
			poWindowSP->on_event_mouse_over(roActionMouse,roResult);
			
			_on_after_event(roActionMouse,roResult);
			::SetTimer(m_poArenaManagerSP->get_os_window(),ARENA_TOOLTIP_TIMER_ID,400,NULL);
			return;
		}
	}
	
	cancel_tooltip();
}

void cned_arena::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionMouseWheel,roResult);

	SCP<cned_window> poWindowSP = get_top_window();
	if(poWindowSP.PointsObject())
	{
		poWindowSP->on_event_mouse_wheel(roActionMouseWheel,roResult);
		//finally call
		_on_after_event(roActionMouseWheel,roResult);
	}
}

void cned_arena::on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	//call all windows
	POSITION pos = m_oWindowStack.GetHeadPosition();
	if(pos)
	{
		m_oWindowStack.GetNext(pos)->on_event_timer(true,roActionTimer,roResult);
	}
	while(pos)
	{
		m_oWindowStack.GetNext(pos)->on_event_timer(false,roActionTimer,roResult);
	}
	//finally call
	_on_after_event(roActionTimer,roResult);
}

void cned_arena::on_event_olecontrol(const ned_action_oleevent & roActionOleEvent,ned_action_result & roResult)
{
	//ned_to_do:

	//finally call
	_on_after_event(roActionOleEvent,roResult);
}

//--------------------------------------------------------------------------------
//	on_event_command
//--------------------------------------------------------------------------------

void cned_arena::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	SCP<cned_window> poWindowSP = get_top_window();
	if(poWindowSP.PointsObject())
	{
		poWindowSP->on_event_command(roActionCommand,roResult);
		//finally call
		_on_after_event(roActionCommand,roResult);
	}
}

	
//--------------------------------------------------------------------------------
//	on_event_size_changed
//--------------------------------------------------------------------------------

void cned_arena::on_event_size_changed(ng_dc & roDC,const ng_rect & roArenaRect)
{
	//detect width change
	bool bWidthChanged = (m_poArenaManagerSP->get_screen_arena().get_width() != roArenaRect.get_width());
	m_poArenaManagerSP->set_arena(roArenaRect);

	//notify all windows
	POSITION pos = m_oWindowStack.GetTailPosition();
	while(pos)
	{
		m_oWindowStack.GetPrev(pos)->on_event_size_changed(bWidthChanged);
	}
	
	//info: ten invalidate jest potrzebny, mimo ¿e wy¿ej robimy MoveWindow(,TRUE)
	//które te¿ wysy³a invalidate (i przy okazji maluje zmienione ramki - nonclient area)
	//poniewa¿ _do_paint mo¿e byæ zrobione wczeœniej ni¿ dojdzie do nas WM_PAINT
	//i pozostaje przez ten czas ba³agan na ekranie (np. pokazywanie i ukrywanie 
	//outlookbara

	internal_invalidate_paint_rect(get_screen_arena());
}



//--------------------------------------------------------------------------------
//	on_event_set_cursor
//--------------------------------------------------------------------------------
HCURSOR get_cursor_handle_on_type(eCursorType eCT);

bool cned_arena::on_event_set_cursor()
{
	POINT oScreenPoint;
	//OS_API_CALL
	VERIFY(::GetCursorPos(&oScreenPoint));
	VERIFY(::ScreenToClient(m_poArenaManagerSP->get_os_window(),&oScreenPoint));

	ng_point oPoint(oScreenPoint);
	
	cned_window * poFoundWindow = _find_window_from_point(oPoint);
	if(poFoundWindow != NULL)
	{
		eCursorType eCT = ect_default;
		
		//when over top-window look for element-specific cursor
		if(get_top_window().Get() == poFoundWindow)
		{
			eCT = poFoundWindow->on_event_set_cursor(oPoint);
		}

		HCURSOR hCursor = get_cursor_handle_on_type(eCT);
		if(hCursor != ::GetCursor())
		{
			::SetCursor(hCursor);
		}
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
//	on_event_paint
//--------------------------------------------------------------------------------

void cned_arena::on_event_paint(ned_action_paint & roActionPaint,ned_action_result & roResult)
{
	//first ensure valid arena
	_update_layout_in_all_windows(roActionPaint,roResult);
	
	if(!is_invalid_paint_area())
	{
		//wyjdŸ jeœli nie ma nic do roboty
		return;
	}

	//get invalid area
	ng_rect oInvalidRect;
	m_poArenaManagerSP->get_invalid_paint_area().get_bounding_rect(oInvalidRect);

	_do_paint_animated_rects(roActionPaint.get_dc());

#ifdef _DEVELOPER_EDITION_
	DWORD dw1 = ::GetTickCount();

//	roActionPaint.get_dc().fill_rect_hg(oInvalidRect,Red,Red);
//	SHIFT_PAUSE

#endif
	//prepare device
	if(true && !_is_fast_graphics())
	{
		ng_double_buffer oDB(roActionPaint.get_dc(),oInvalidRect);
#ifdef _DEBUG
		//	ng_dc_statistics oStats(oDB.get_dc(),oRect);
#endif
		oDB.copy_from(roActionPaint.get_dc(),oInvalidRect.get_topleft());

		_do_paint(oDB.get_dc(),oInvalidRect);

		oDB.copy_to(roActionPaint.get_dc(),oInvalidRect.get_topleft());
	}
	else
	{
#ifdef _DEBUG
		//ng_dc_statistics oStats(oDC,oRect);
#endif
		_do_paint(roActionPaint.get_dc(),oInvalidRect);
	}

	//wyczyœæ
	m_poArenaManagerSP->clear_paint_area();

#ifdef _DEVELOPER_EDITION_
	{
		SCP<ng_font> poFontSP = ng_font::create("Tahoma",10000 * 10,false,false,false,false,0);
		ng_rect oRect = m_poArenaManagerSP->get_screen_arena();
		oRect.set_top(oRect.get_bottom() - 20);
		oRect.set_left(oRect.get_right() - 30);
		roActionPaint.get_dc().print_text(oRect,Long2String(::GetTickCount() - dw1),Red,poFontSP);
	}
#endif
}

//---------------- private event -----------------------------------------
void animate_rect(const animate_rect_effect & roARE,ng_dc & roDC);

void cned_arena::_do_paint_animated_rects(ng_dc & roDC)
{
	if(get_prop_animate_windows())
	{
		for(long iter = 0; iter < m_oARE_Array.GetSize(); iter++)
		{
			animate_rect(m_oARE_Array[iter],roDC);
		}
	}

	m_oARE_Array.RemoveAll();
}

void cned_arena::_do_paint(ng_dc & roDC,const ng_rect & roInvalidRect)
{
	//przygotuj malowanie
		//utwórz region na podstawie obszaru do odmalowania
		ng_region oPaintRegion;
		oPaintRegion.from_area(roInvalidRect);
		_prepare_paint_region(oPaintRegion);

	//w regionie jest teraz tylko obszar t³a
	roDC.set_clip_region(oPaintRegion,RGN_COPY);
	//maluj t³o areny
	_do_paint_background(roDC);
	
	//maluj okna
	cned_painter_ oArenaPainter(roDC,roInvalidRect);
	_paint_windows(oArenaPainter);
	//maluj tooltip
}

void cned_arena::_do_paint_background(ng_dc & roDC)
{
	ng_color clrBack;
	ng_color clrBack2;
	if(_metrics().is_windows_look())
	{
		clrBack  = ng_color::system(COLOR_APPWORKSPACE);
		clrBack2 = clrBack;
	}
	else
	{
		clrBack  = m_oBackColor;
		clrBack2 = m_oBackColor2;
	}
	roDC.fill_rect_hg(m_poArenaManagerSP->get_screen_arena(),clrBack,clrBack2);

#ifdef _BETA_EDITION_
	{
		SCP<ng_font> poFontSP = ng_font::create("Tahoma",10000 * 14,false,true,false,false,0);
		ng_rect oRect=m_poArenaManagerSP->get_screen_arena();
		roDC.print_text(oRect,
			"Display Engine (NED) BETA 1.3",RGB(64,0,255),poFontSP);
	}
#endif
#ifdef _DEVELOPER_EDITION_
	{
		roDC.frame_rect(ng_rect(0,0,640,480),1,ng_color(RGB(0,255,0)),NG_FRAME_ALL | NG_FRAME_EDGE_FLAT);
		roDC.frame_rect(ng_rect(0,0,800,600),1,ng_color(RGB(0,255,0)),NG_FRAME_ALL | NG_FRAME_EDGE_FLAT);
	}
#endif
}


void cned_arena::_update_layout_in_all_windows(const ned_action__ & roAction,ned_action_result & roResult)
{
	POSITION pos = m_oWindowStack.GetTailPosition();
	while(pos)
	{
		//ned_to_do: tylko do sprawdzeñ
		ng_rect ned_to_do_ArenaRect = m_poArenaManagerSP->get_screen_arena();
		
		if(ned_to_do_ArenaRect.get_bottom() > 200)
		{
			ned_to_do_ArenaRect.set_bottom(ned_to_do_ArenaRect.get_bottom() - 00);
		}

		m_oWindowStack.GetPrev(pos)->_update_layout_for_display(roAction,roResult,
			ned_to_do_ArenaRect);
	}
}

void cned_arena::_prepare_paint_region(ng_region & roRegion)
{
	//zaczynamy od topmost i jedziemy w g³¹b

	POSITION pos = m_oWindowStack.GetHeadPosition();
	while(pos)
	{
		m_oWindowStack.GetNext(pos)->_prepare_paint_region(roRegion);
	}
}

void cned_arena::_paint_windows(cned_painter_ & roArenaPainter)
{
	//zaczynamy od spodu i malujemy w górê - topmost na koñcu
	//w ten sposób alfy namaluj¹ siê dobrze

	POSITION pos = m_oWindowStack.GetTailPosition();
	while(pos)
	{
		m_oWindowStack.GetPrev(pos)->_paint(roArenaPainter);
	}
}
	

//--- process results of event ---------------
void cned_arena::_on_after_event(const ned_action__ & roAction,ned_action_result & roResult)
{
}


//--------------- command helpers --------------------
SCP<ned_event_command> cned_arena::_prepare_acvitate_window_command(cned_window * poActivatedWindow)
{
	//clicking not on top window
	//post command "activate"
	SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(NEDID_NOTHING));
	SCP<CHyperLinkInfo> poCmdHLISP = NewSCP(new CHyperLinkInfo());
	poCmdHLISP->SetNumProp(GVAR_CMD,CMD_INTERNAL_ACTIVATE);
	poCmdHLISP->SetNumProp(GVAR_PAGE_IID,poActivatedWindow->get_prop_iid());
	poEventCmdSP->set_command(poCmdHLISP);

	return poEventCmdSP;
}

SCP<ned_event_command> cned_arena::_prepare_arena_click_command(bool bLeftClick)
{
	//not on any window - post command "arena click"
	SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(NEDID_NOTHING));
	SCP<CHyperLinkInfo> poCmdHLISP = NewSCP(new CHyperLinkInfo());
	poCmdHLISP->SetNumProp(GVAR_CMD,CMD_INTERNAL_ARENA_CLICK);
	poCmdHLISP->SetNumProp(INTERNALVAR_ARENA_CLICK_BUTTON,bLeftClick ? long(0) : long(2));
	poEventCmdSP->set_command(poCmdHLISP);

	return poEventCmdSP;
}

//-------- tooltip support--------------
//OS_API_CALL
inline static void fill_tool_info(HWND hwndOwner,TOOLINFO & roTI)
{
    roTI.cbSize = sizeof(TOOLINFO);
    roTI.uFlags = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
    roTI.hwnd   = hwndOwner;
	roTI.uId    = UINT(hwndOwner);
	roTI.hinst  = HINSTANCE(NULL);
    roTI.lpszText  = "";
	roTI.rect.left = roTI.rect.right = roTI.rect.top = roTI.rect.bottom = 0;
}

#ifndef TTS_BALLOON
#define TTS_BALLOON             0x40
#endif

static HWND CreateToolTipWindow(HWND hwndOwner)
{
	//initialize common controls
	{
		// Load the ToolTip class from the DLL.
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(icex);
		icex.dwICC  = ICC_BAR_CLASSES;
		
		if(!::InitCommonControlsEx(&icex))
		{
			return HWND(NULL);
		}
	}

	HINSTANCE hInst = AfxGetInstanceHandle();

	// Create the ToolTip control.
    HWND hwndTT = ::CreateWindow(TOOLTIPS_CLASS, TEXT(""),
                          WS_POPUP,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, (HMENU)NULL, hInst,
                          NULL);

	if(hwndTT == HWND(NULL))
	{
		return HWND(NULL);
	}

    // Prepare TOOLINFO structure for use as tracking ToolTip.
    TOOLINFO    ti;
	fill_tool_info(hwndOwner,ti);
    
    // Add the tool to the control
    if(!::SendMessage(hwndTT,TTM_ADDTOOL,0,(LPARAM)&ti))
	{
		return HWND(NULL);
    }
    
    return(hwndTT);    
}


void cned_arena::cancel_tooltip()
{
	m_poArenaIntegrator->cancel_other_tooltips(this);
	_internal_cancel_tooltip();
}

void cned_arena::_internal_cancel_tooltip()
{
	if(m_bToolTipVisible)
	{
		ASSERT(m_hToolTipHwnd != HWND(NULL));
		ASSERT(m_poArenaManagerSP->get_os_window() != HWND(NULL));
	    TOOLINFO    ti;
		fill_tool_info(m_poArenaManagerSP->get_os_window(),ti);
		::SendMessage(m_hToolTipHwnd,TTM_TRACKACTIVATE,(WPARAM)FALSE,(LPARAM)&ti);
		m_bToolTipVisible = false;
	}
	::KillTimer(m_poArenaManagerSP->get_os_window(),ARENA_TOOLTIP_TIMER_ID);
}

void cned_arena::show_tooltip(const ng_string & roText)
{
	m_poArenaIntegrator->cancel_other_tooltips(this);

	if(m_hToolTipHwnd == HWND(NULL))
	{
		//need create
		if(m_poArenaManagerSP->get_os_window() == HWND(NULL))
		{
			//but cannot at this moment
			return;
		}
		m_hToolTipHwnd = CreateToolTipWindow(m_poArenaManagerSP->get_os_window());
	}
	
	//still no tool tip -> exit
	if(m_hToolTipHwnd == HWND(NULL))
	{
		return;
	}
	
	//update text
	//update position
	{
		TOOLINFO    ti;
		fill_tool_info(m_poArenaManagerSP->get_os_window(),ti);
		TCHAR cVeryLongBuffer[ 4096 ];
		ti.lpszText = cVeryLongBuffer;
		::SendMessage(m_hToolTipHwnd,TTM_GETTOOLINFO,(WPARAM)0,(LPARAM)&ti);
		cVeryLongBuffer[4095] = '\0';
		if(_tcscmp(cVeryLongBuffer,roText) != 0)
		{
			ti.lpszText = (LPSTR)(LPCTSTR) roText;
			::SendMessage(m_hToolTipHwnd,TTM_SETTOOLINFO,(WPARAM)0,(LPARAM)&ti);
		}
	}

	if(!m_bToolTipVisible)	//show when not visible
	{
	    TOOLINFO    ti;
		fill_tool_info(m_poArenaManagerSP->get_os_window(),ti);
		
		// Activate (display) the tracking ToolTip. Then, set a global
		// flag value to indicate that the ToolTip is active, so other
		// functions can check to see if it's visible.
		::SendMessage(m_hToolTipHwnd,TTM_TRACKACTIVATE,(WPARAM)TRUE,(LPARAM)&ti);
		m_bToolTipVisible = true;
	}
	
	{
		POINT oScreenPoint;
		//OS_API_CALL
		VERIFY(::GetCursorPos(&oScreenPoint));
		//+ 15 - from MSDN
		oScreenPoint.x += 15;
		oScreenPoint.y += 15;

		//correct tt position - always must fit screen (desktop covers entire screen)
		RECT oTTWndRect;
		::GetWindowRect(m_hToolTipHwnd,&oTTWndRect);
		RECT oDesktopWndRect;
		::GetWindowRect(::GetDesktopWindow(),&oDesktopWndRect);
		oScreenPoint.x = min(oScreenPoint.x,oDesktopWndRect.right - (oTTWndRect.right - oTTWndRect.left));
		oScreenPoint.y = min(oScreenPoint.y,oDesktopWndRect.bottom - (oTTWndRect.bottom - oTTWndRect.top));

		::SendMessage(m_hToolTipHwnd,TTM_TRACKPOSITION,(WPARAM)0,
			(LPARAM)(DWORD) MAKELONG(oScreenPoint.x, oScreenPoint.y));
	}
	::KillTimer(m_poArenaManagerSP->get_os_window(),ARENA_TOOLTIP_TIMER_ID);
}

//~OS_API_CALL

bool cned_arena::_pre_translate_message(MSG &)
{
	return false;
}

