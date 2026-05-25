/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)


	cnui_arena
		- ca³e niezalezne srodowisko graficzne, oparte na oknie Win32
*/

#ifndef _ARENA_NED_H_
#define _ARENA_NED_H_

namespace ned
{

class cned_arena_manager;
class cned_window;

class cned_arena;

class cned_arena_integrator : public CInterface__
{
public:
	cned_arena_integrator();
	~cned_arena_integrator();
	SCP<cned_arena> create_arena();
	void on_arena_final_release(cned_arena * poArena);
	void cancel_other_tooltips(cned_arena * poArena);
private:
	CArray< cned_arena * , cned_arena * > m_oArenaArray;
};

class cned_arena : public CInterface__
{
public:
	//--- property get ---------------------------
	bool get_prop_animate_windows() const;
	ng_color get_prop_backcolor() const;
	ng_color get_prop_backcolor2() const;
	//--- property set ---------------------------
	void set_prop_animate_windows(bool bAnimate);
	void set_prop_backcolor(ng_color clrBack);
	void set_prop_backcolor2(ng_color clrBack2);

	//----- system connections ---------------------
	void attach_os_window(HWND hWnd);
	void set_providers(const ng_string & roFullCachePathString,SCP<IGlobalInterfaceTable> poGITSP,
		DWORD dwAppDBManager_GIT_Cookie,DWORD dwCachedData_GIT_Cookie);
	//------ window management ------------------
	SCP<cned_window> create_window();
	void on_window_final_release(cned_window * poWindow);

	SCP<cned_window> get_top_window();
	SCP<cned_window> get_bottom_window();
	void add_window_to_stack(SCP<cned_window> poWindowToAddSP,cned_window * poWindowToBeAbove);
	void remove_window_from_stack(cned_window * poWindow);
	void move_window_to_top(SCP<cned_window> poWindowToMoveSP);

	//---------------- events ----------------------
	void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	
	void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult);
	
	void on_event_size_changed(ng_dc & roDC,const ng_rect & roArenaRect);
	void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);
	void on_event_olecontrol(const ned_action_oleevent & roActionOleEvent,ned_action_result & roResult);
	void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	bool on_event_set_cursor();
	
	//---------------- painting related events and methods
		void on_event_paint(ned_action_paint & roActionPaint,ned_action_result & roResult);
	//-------------------- downlinks ---------------------------
		//---------- paint area ----------------
		bool is_invalid_paint_area() const;		//means: is repaint area non empty
		void external_invalidate_paint(const ng_rect & roExternalRepaintRect);
		void internal_invalidate_paint_rect(const ng_rect & roAbsoluteRect);

		void set_current_style(const CSmartOleVariant & roStyleSOV);

	void add_animate_rect_effect(const animate_rect_effect & roARE);

	void cancel_tooltip();
	void show_tooltip(const ng_string & roText);

	const ng_rect & get_screen_arena() const;
	ng_point get_default_window_position(cned_window * poExcludeWindow) const;

	SCP<cned_element_manager> _create_element_manager();

	bool _pre_translate_message(MSG & roMsg);

private:
	cned_arena(cned_arena_integrator * poArenaIntegrator);
	~cned_arena();
	virtual void OnFinalRelease();
	//----- painting helpers -------------------------
	void _do_paint(ng_dc & roDC,const ng_rect & roInvalidRect);
	void _do_paint_background(ng_dc & roDC);
	void _do_paint_animated_rects(ng_dc & roDC);

	void _prepare_paint_region(ng_region & roRegion);
	void _paint_windows(cned_painter_ & roPainter);

	void _update_layout_in_all_windows(const ned_action__ & roAction,ned_action_result & roResult);

	bool _update_last_mouse_position(const ned_action_mouse & roActionMouse);
	//--------------- command helpers --------------------
	static SCP<ned_event_command> _prepare_acvitate_window_command(cned_window * poActivatedWindow);
	static SCP<ned_event_command> _prepare_arena_click_command(bool bLeftClick);
	//------------------------------------------------------------
	void _internal_cancel_tooltip();

	cned_window * _find_window_from_point(const ng_point & roPoint);
	void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult);

	cned_arena_integrator * m_poArenaIntegrator;
	SCP<cned_arena_manager>	m_poArenaManagerSP;
	
	CList< SCP<cned_window>, SCP<cned_window> & > m_oWindowStack;

	CArray<animate_rect_effect,const animate_rect_effect &> m_oARE_Array;

	ng_color	m_oBackColor;
	ng_color	m_oBackColor2;
	bool		m_bAnimateWindows;
	
	//-------- tooltip support--------------
	//OS_API_CALL
	HWND		m_hToolTipHwnd;
	bool		m_bToolTipVisible;
	//--------- mouse over support
	ng_point	m_oLastMousePosition;
	UINT		m_nLastMouseFlags;

	friend class cned_arena_integrator;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline bool cned_arena::_update_last_mouse_position(const ned_action_mouse & roActionMouse)
{
	if(roActionMouse.get_mouse_position() == m_oLastMousePosition &&
		roActionMouse.get_flags() == m_nLastMouseFlags)
	{
		return false;
	}
	
	m_oLastMousePosition = roActionMouse.get_mouse_position();
	m_nLastMouseFlags = roActionMouse.get_flags();
	
	return true;
}

inline void cned_arena::add_animate_rect_effect(const animate_rect_effect & roARE)
{
	m_oARE_Array.Add(roARE);
}

//--- property get ---------------------------
inline bool cned_arena::get_prop_animate_windows() const
{
	return m_bAnimateWindows;
}

//--- property set ---------------------------
inline void cned_arena::set_prop_animate_windows(bool bAnimate)
{
	m_bAnimateWindows = bAnimate;
}

inline ng_color cned_arena::get_prop_backcolor() const
{
	return m_oBackColor;
}

inline ng_color cned_arena::get_prop_backcolor2() const
{
	return m_oBackColor2;
}

//--------------------------------------------------------------

}

#else
	#error __FILE__ already included
#endif
 