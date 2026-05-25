/*
	NAVO Enterprise 2003
	2003-04-18

	navo enhanced display (NED)


	ned_hscroll / <scrollbar>
	ned_vscroll

	kontrolka scrollbar

	cned_scrollbar__ - wspólna klasa bazowa
*/

#ifndef _SCROLLBAR_NED_H_
#define _SCROLLBAR_NED_H_

namespace ned
{

class cned_scrollbar__ : public cned_rect_container_
{
public:
	//------ property GET -----------------
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	long get_prop_position() const;
	long get_prop_total_range() const;
	long get_prop_page_range() const;

	bool is_mode_embedded() const;
	//------ property SET -----------------
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_position(long nNewPos);
	void set_prop_total_range(long nNewTotalRange);
	void set_prop_page_range(long nPageRange);

	void set_mode_embedded();
	//-------------- rendering support -------------------
	virtual void render(cned_renderer_ & roRenderer);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();	//ustawia nie-dziedziczone property
	virtual void apply_attributes(const ned_currattributes & roCurrAttrib);

	//-------- helpers ---------------
	bool _compute_position_on_local_point(const ng_point & roLocalPoint);
	void _compute_position_on_thumb_target(long nThumbTarget);
	long _get_current_thumb_target() const;

	void _on_action_result(long nOldPosition,ned_action_result & roResult);
protected:
	cned_scrollbar__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	void _construct_children();
	void _normalize();
	void _invalidate_thumb_paint();

	void _get_sliding_rect(const ng_point & roPoint,ng_rect & roSlidingRect) const;
	void _get_thumb_rect(const ng_point & roPoint,ng_rect & roThumbRect) const;
	void _compute_thumb_info(const ng_point & roPoint,long nPosition,long & rnThumbTarget,long & rnThumbSize) const;

	//-------------- rendering support -------------------
	virtual ng_size _prepare_size_while_rendering(cned_renderer_ & roRenderer) = 0;
	//---------------------------
	long		m_nPosition;
	long		m_nTotalRange;	//total range
	long		m_nPageRange;	//'page' range
	
	long		m_nAutoScrollIncrement;	//auto increment while doing auto scroll
	eEventInfoType	m_eNotificationMethod;	//eit_newdata for standalone controls,eit_command for scroll_helper contained controls
};

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

class cned_drag_info_scrollbar : public cned_drag_info__
{
public:
	cned_drag_info_scrollbar(const ng_point & roStartingArenaPoint,
		SCP<cned_scrollbar__> poScrollBarSP);
	virtual bool on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
	virtual bool on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
private:
	SCP<cned_scrollbar__>	m_poScrollbarSP;
	long					m_nInitialOffset;
};
//--------------------------------------------------------------------
// horizontal
//--------------------------------------------------------------------

class cned_horiz_scrollbar : public cned_scrollbar__
{
public:
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual ng_size _prepare_size_while_rendering(cned_renderer_ & roRenderer);
private:
	cned_horiz_scrollbar(cned_element_manager * poManager,const ned_ident idThis);
	
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// vertical
//--------------------------------------------------------------------

class cned_vert_scrollbar : public cned_scrollbar__
{
public:
	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();	//ustawia nie-dziedziczone property
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual ng_size _prepare_size_while_rendering(cned_renderer_ & roRenderer);
private:
	cned_vert_scrollbar(cned_element_manager * poManager,const ned_ident idThis);
	
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_scrollbar__::cned_scrollbar__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_container_(poManager,eType,idThis),
	m_nPosition(0),
	m_nTotalRange(99),
	m_nPageRange(1),
	m_nAutoScrollIncrement(0),
	m_eNotificationMethod(eit_newdata)
{
	_construct_children();
}

//------ property GET -----------------
inline void cned_scrollbar__::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = CSmartOleVariant(get_prop_position(),VT_I4);
}

inline long cned_scrollbar__::get_prop_position() const
{
	return m_nPosition;
}

inline long cned_scrollbar__::get_prop_total_range() const
{
	return m_nTotalRange;
}

inline long cned_scrollbar__::get_prop_page_range() const
{
	return m_nPageRange;
}

inline bool cned_scrollbar__::is_mode_embedded() const
{
	return (m_eNotificationMethod == eit_command);
}

//------ property SET -----------------
inline void cned_scrollbar__::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_position(roSOV.GetLong());
}

inline void cned_scrollbar__::set_prop_position(long nNewPos)
{
	if(get_prop_position() == nNewPos)
	{
		return;
	}

	m_nPosition = nNewPos;
	
	_normalize();
	_invalidate_thumb_paint();

	_vse_dirty();
}

inline void cned_scrollbar__::set_prop_total_range(long nNewTotalRange)
{
	if(get_prop_total_range() == nNewTotalRange)
	{
		return;
	}

	m_nTotalRange = nNewTotalRange;

	_normalize();
	_invalidate_thumb_paint();

	_vse_dirty();
}

inline void cned_scrollbar__::set_prop_page_range(long nPageRange)
{
	if(get_prop_page_range() == nPageRange)
	{
		return;
	}

	m_nPageRange = nPageRange;

	_normalize();

	_invalidate_thumb_paint();

	_vse_dirty();
}

inline void cned_scrollbar__::set_mode_embedded()
{
	m_eNotificationMethod = eit_command;
}

//-------------- attribute functions -------------------------
inline void cned_scrollbar__::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();

	set_prop_border_type(NED_BORDER_STYLE_NONE);
	set_prop_ignore_sys_disable(true);
	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
}

inline void cned_scrollbar__::apply_attributes(const ned_currattributes & roCurrAttrib)
{
	//do not call cned_rect_container_::apply-attrib
	//we want not to copy properties to pictures
	cned_element::apply_attributes(roCurrAttrib);
}

//--------------------------------------------------------------------
inline void cned_scrollbar__::_normalize()
{
	m_nTotalRange	= max(1,m_nTotalRange);
	m_nPageRange	= min(max(1,m_nPageRange),m_nTotalRange);
	m_nPosition		= max(0,min(m_nPosition,m_nTotalRange - m_nPageRange - 1));

	ASSERT(m_nTotalRange > 0);
	ASSERT(m_nPageRange > 0);
}

inline void cned_scrollbar__::_invalidate_thumb_paint()
{
	//ned_to_do: inwalidowanie malowania
	_invalidate_all_paint();
}

inline long cned_scrollbar__::_get_current_thumb_target() const
{
	long nThumbTarget;
	long nThumbSize;

	_compute_thumb_info(ng_point(),get_prop_position(),nThumbTarget,nThumbSize);

	return nThumbTarget;
}

//--------------------------------------------------------------------
// horizontal
//--------------------------------------------------------------------
inline cned_horiz_scrollbar::cned_horiz_scrollbar(cned_element_manager * poManager,const ned_ident idThis) :
	cned_scrollbar__(poManager,ned_hscroll,idThis)
{
}

//--------------------------------------------------------------------
// vertical
//--------------------------------------------------------------------
inline cned_vert_scrollbar::cned_vert_scrollbar(cned_element_manager * poManager,const ned_ident idThis) :
	cned_scrollbar__(poManager,ned_vscroll,idThis)
{
}

//-------------- attribute functions -------------------------
inline void cned_vert_scrollbar::set_fixed_properties()
{
	cned_scrollbar__::set_fixed_properties();
	set_prop_extwidth(NED_MIN_WIDTH);
}

}

#else
	#error __FILE__ already included
#endif

