/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	top level page element

*/

#ifndef _TOPLEVELPAGE_NED_H_
#define _TOPLEVELPAGE_NED_H_

namespace ned
{

class cned_toplevelpage : public cned_page
{
public:
	void move_to(const ng_size & roArenaPositionSize);
	const ng_size & get_arena_position() const;
	void get_page_rect(ng_rect & roPageRect) const;

	void invalidate_page();
	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
	//------- paint support --------------------
	void prepare_paint_region(ng_region & roCommonRgn);
	void paint(cned_painter_ & roPainter);

	virtual bool is_inside_hit_area(const ng_point & roPoint) const;

	void on_window_on_top(bool bTopmost);	//called when put/removed from top of stack
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);

//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	virtual void process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
//-------- page breaking ---------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);

	void fill_clone_split(cpb_split_manager & roSplitManager,SCP<cned_toplevelpage> poDestPageSP,
		const cned_page_break_param & roPBP,long xAreaX,long yAreaY,long xCount,long yCount);
private:
	cned_toplevelpage(cned_element_manager * poManager);

	//----------------- child management ---------------------
	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident nChildIdent);
	
	virtual void _invalidate_all_paint();

	void _get_scrollable_rect_for_scroll(ng_rect & roRect);
	//------------------ subpage management ------------------
	void _subpage_add(ned_ident idSubPage);
	void _subpage_remove(ned_ident idSubPage);
	void _subpage_move_by(const ng_size & roDistance);
	//------------------ win32 controls management ------------------
	void _win32ctrl_add(ned_ident idWin32Ctrl);
	void _win32ctrl_remove(ned_ident idWin32Ctrl);
	void _win32ctrl_move_by(const ng_size & roDistance);
	//--------------------------------------------------------
	CArray< ned_ident, ned_ident > m_oSubPageArray;	//'subpage' elements (for layer support) 
													// (note: it may be not direct children)
	CArray< ned_ident, ned_ident > m_oWin32Array;	//win32 based controls - need special care

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

class cned_drag_info_toplevelpage : public cned_drag_info__
{
public:
	cned_drag_info_toplevelpage(const ng_point & roStartingArenaPoint);
	virtual bool on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
	virtual bool on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
private:
	ng_point m_oLastPoint;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline void cned_toplevelpage::set_fixed_properties()
{
	cned_page::set_fixed_properties();
	set_prop_extmargins(ng_rect(300,300,300,500));
}

inline void cned_toplevelpage::move_to(const ng_size & roArenaPositionSize)
{
	ng_size oDistanceSize = roArenaPositionSize - m_oVectorSize;
	m_oVectorSize = roArenaPositionSize;
	m_oNormalModeInfo.m_oVectorSize = roArenaPositionSize;

	//move plain win32 ctrls also
	if(oDistanceSize != ng_size())
	{
		_win32ctrl_move_by(oDistanceSize);
		_subpage_move_by(oDistanceSize);
	}
}

inline const ng_size & cned_toplevelpage::get_arena_position() const
{
	return m_oVectorSize;
}

inline void cned_toplevelpage::get_page_rect(ng_rect & roPageRect) const
{
	roPageRect = ng_rect(ng_point().offset(get_arena_position()),get_actual_size());
}

inline void cned_toplevelpage::invalidate_page()
{
	_invalidate_all_paint();
}

}

#else
	#error __FILE__ already included
#endif
