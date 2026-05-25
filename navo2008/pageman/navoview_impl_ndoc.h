/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	26.01.2003

	class:
		cndoc_navoview_impl
	
		implements ned_arena-based window
*/

#ifndef _NAVOVIEW_IMPL_NDOC_H_
#define _NAVOVIEW_IMPL_NDOC_H_

class cndoc_navoview_impl_container_;

class cndoc_navoview_impl : public cndoc_olecontrol_event_sink__
{
public:
	cndoc_navoview_impl(cndoc_navoview_impl_container_ * poContainer);
	~cndoc_navoview_impl();
	virtual CNavoException & _error_storage() = 0;
	virtual void _get_client_rect(ng_rect & roClientRect) = 0;

	//painting and misc
	void on_paint_event(const ng_rect & roUpdateRect);
	void on_size_changed_event();
	bool on_set_cursor_event();
	void on_time_elapsed_event(UINT idTimer);
	void on_idle_event();
	
	//mouse events
	void on_left_button_down_event(UINT nFlags,ng_point oPoint);
	void on_left_button_up_event(UINT nFlags,ng_point oPoint);
	void on_left_button_dbl_click_event(UINT nFlags,ng_point oPoint);
	void on_right_button_down_event(UINT nFlags,ng_point oPoint);
	void on_right_button_up_event(UINT nFlags,ng_point oPoint);
	void on_mouse_move_event(UINT nFlags,ng_point oPoint);
	void on_mouse_wheel_event(UINT nFlags,long zDelta,ng_point oPoint);

	//keyboard events
	bool on_key_down_event(UINT nChar, UINT nRepCnt, UINT nFlags);

	//ole control events
	virtual void on_olecontrol_event(long IdCtrl,AFX_EVENT* pEvent);
	
	void set_arena(SCP<ned::cned_arena> poArenaSP);
	void attach_window(HWND hWindow);
	void update_view();

private:
	void _process_shortcutmenu(ned::ned_action_result & roResult);

	void _do_paint();

	SCP<ned::cned_arena>		m_poArenaSP;
	UINT				m_nLastClickFlags;
	HWND				m_hWindow;
	bool				m_bInsideShortcutMenu;
	cndoc_navoview_impl_container_ * m_poContainer;
};

#else
	#error __FILE__ already included
#endif

