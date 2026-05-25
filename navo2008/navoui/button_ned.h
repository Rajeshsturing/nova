/*
	NAVO Enterprise 2003
	2003-03-28

	navo enhanced display (NED)

	ned_button / <button>

	przycisk

*/

#ifndef _BUTTON_NED_H_
#define _BUTTON_NED_H_

namespace ned
{

class cned_button : public cned_static
{
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
private:
	cned_button(cned_element_manager * poManager,const ned_ident idThis);

	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);
	void _create_test_string(ng_string & roString) const;
	void _get_text_rect(const ng_point & roCurrentPoint,ng_rect & roTextRect);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_button::cned_button(cned_element_manager * poManager,const ned_ident idThis) :
	cned_static(poManager,ned_button,idThis)
{
}

//-------------- attribute functions -------------------------
inline void cned_button::set_fixed_properties()
{
	cned_static::set_fixed_properties();
	set_prop_printable(false);
	set_prop_border_color(_metrics().button().get_border_color());
}

inline void cned_button::_get_text_rect(const ng_point & roCurrentPoint,ng_rect & roTextRect)
{
	roTextRect = ng_rect(roCurrentPoint,m_oActualSize);
	roTextRect.inflate(1-_metrics().button().get_left_margin(),
		1-_metrics().button().get_top_margin());	//t³o czêœciowo pokrywa siê z alpha ramki, dlatego inflate jest 2 a nie 3
}


}

#else
	#error __FILE__ already included
#endif
