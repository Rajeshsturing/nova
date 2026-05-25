/*
	NAVO Enterprise 2003
	2003-04-23

	navo enhanced display (NED)

	scroll_helper__
	
	wsparcie dla scrolowania
*/

#ifndef _SCROLL_HELPER_NED_H_
#define _SCROLL_HELPER_NED_H_


namespace ned
{

class cned_vert_scrollbar;
class cned_horiz_scrollbar;

class scroll_helper__
{
public:
	void _scroll_screen2local(ng_point & roPoint) const;
protected:
	scroll_helper__(cned_element_manager * poManager,ned_ident idOwner);
	ng_xdist show_vertical_bar(cned_renderer_ & roRenderer,const ng_point & roScrollTopLeft,const ng_ydist yHeight,long nTotalRange,long nPageRange);
	ng_ydist show_horizontal_bar(cned_renderer_ & roRenderer,const ng_point & roScrollTopLeft,const ng_xdist xWidth,long nTotalRange,long nPageRange);
	void hide_vertical_bar();
	void hide_horizontal_bar();

	//------- paint support --------------------
	void _scroll_draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _scroll_draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);

	bool _scroll_is_inside_hit_area(const ng_point & roPoint);
	ned_ident _scroll_find_element_from_point(const ng_point & roPoint);
	//--------------------------------------------------------------------------------------------------
	// events
	//--------------------------------------------------------------------------------------------------
	void _scroll_event_wheel(const ned_action_mouse_wheel & roActionMouseWheel,
		ned_action_result & roResult,const ng_rect & roScrollableRect);
	void _scroll_event_command(const ned_action_command & roActionCommand,
		ned_action_result & roResult,const ng_rect & roScrollableRect);
	void _scroll_event_kbd(const ned_action_kbd & roActionKBD,ned_action_result & roResult,
		const ng_rect & roScrollableRect);
	//------------------------------------
	const ng_size & get_scroll_pos() const;
	const ng_size & get_scroll_total_range() const;

	//------------------------------------
	bool _is_vert_bar() const;
	bool _is_horiz_bar() const;
	SCP<cned_vert_scrollbar> _get_vert_bar();
	SCP<cned_horiz_scrollbar> _get_horiz_bar();
private:
	void _update_controls();
	void _normalize();
	ng_size _logical_scroll_by(const ng_size & roDistanceSize);
	ng_size _logical_scroll_to(const ng_size & roPositionSize);



	void _physical_scroll(const ng_size & roDistanceSize,ng_dc & roDC,const ng_rect & roScrollableRect);

	cned_element_manager * _get_manager();
	const cned_element_manager * _get_manager() const;
	ned_ident _get_owner_ident() const;
	SCP<cned_container> _get_owner() const;

	ned_ident m_idOwner;
	ned_ident m_idVertBar;
	ned_ident m_idHorizBar;
	cned_element_manager * m_poManager;
	
	ng_size   m_oPositionSize;
	ng_size   m_oPageSize;
	ng_size	  m_oTotalSize;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline scroll_helper__::scroll_helper__(cned_element_manager * poManager,ned_ident idOwner) :
	m_poManager(poManager),
	m_idOwner(idOwner),
	m_idVertBar(NEDID_NOTHING),
	m_idHorizBar(NEDID_NOTHING)
{
	ASSERT(m_poManager != NULL);
	ASSERT(idOwner != NEDID_NOTHING);
}

inline cned_element_manager * scroll_helper__::_get_manager()
{
	return m_poManager;
}

inline const cned_element_manager * scroll_helper__::_get_manager() const
{
	return m_poManager;
}

inline ned_ident scroll_helper__::_get_owner_ident() const
{
	return m_idOwner;
}

inline bool scroll_helper__::_is_vert_bar() const
{
	return (m_idVertBar != NEDID_NOTHING);
}

inline bool scroll_helper__::_is_horiz_bar() const
{
	return (m_idHorizBar != NEDID_NOTHING);
}

inline SCP<cned_container> scroll_helper__::_get_owner() const
{
	return scp_cast_ui<cned_container>(_get_manager()->get_element_on_ident(_get_owner_ident()));
}

//------------------------------------
inline const ng_size & scroll_helper__::get_scroll_pos() const
{
	return m_oPositionSize;
}

inline const ng_size & scroll_helper__::get_scroll_total_range() const
{
	return m_oTotalSize;
}

inline void scroll_helper__::_normalize()
{
	m_oTotalSize.set_dx(max(1,m_oTotalSize.get_dx()));
	m_oTotalSize.set_dy(max(1,m_oTotalSize.get_dy()));

	m_oPageSize.set_dx(min(max(1,m_oPageSize.get_dx()),m_oTotalSize.get_dx()));
	m_oPageSize.set_dy(min(max(1,m_oPageSize.get_dy()),m_oTotalSize.get_dy()));

	m_oPositionSize.set_dx(max(0,min(m_oPositionSize.get_dx(),
				m_oTotalSize.get_dx() - m_oPageSize.get_dx() - 1)));

	m_oPositionSize.set_dy(max(0,min(m_oPositionSize.get_dy(),
				m_oTotalSize.get_dy() - m_oPageSize.get_dy() - 1)));

	ASSERT(m_oTotalSize.get_dx() > 0);
	ASSERT(m_oTotalSize.get_dy() > 0);

	ASSERT(m_oPageSize.get_dx() > 0);
	ASSERT(m_oPageSize.get_dy() > 0);
}

inline ng_size scroll_helper__::_logical_scroll_by(const ng_size & roDistanceSize)
{
	if(roDistanceSize == ng_size())
	{
		return ng_size();
	}

	ng_size oOldPositionSize = get_scroll_pos();
	m_oPositionSize = get_scroll_pos() + roDistanceSize;
	_normalize();
	
	return get_scroll_pos() - oOldPositionSize;
}

inline ng_size scroll_helper__::_logical_scroll_to(const ng_size & roPositionSize)
{
	ng_size oOldPositionSize = get_scroll_pos();
	m_oPositionSize = roPositionSize;
	_normalize();

	return get_scroll_pos() - oOldPositionSize;
}

inline void scroll_helper__::_scroll_screen2local(ng_point & roPoint) const
{
	SCP<cned_container> poOwnerContainerSP = _get_owner()->get_container();
	if(poOwnerContainerSP.PointsObject())
	{
		poOwnerContainerSP->_screen2local(roPoint);
	}
	roPoint.offset(-_get_owner()->m_oVectorSize);
}

}

#else
	#error __FILE__ already included
#endif


