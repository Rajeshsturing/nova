/*
	NAVO Enterprise 2008
	15.04.2002
	
	us³ugi do scrollowania
*/

#ifndef _SCROLLER_NUI_H_
#define _SCROLLER_NUI_H_

class scrollable__;
class cnui_element_manager;

class cnui_scrollbar_subelement__
{
public:
	cnui_scrollbar_subelement__(scrollable__ * poScrollable) :
		m_poScrollable(poScrollable),
		m_nRange(1000),
		m_nPosition(0),
		m_bVisible(false)
	{
		ASSERT(poScrollable);
	}
	const ng_rect & get_rect() const;
	void move_by(const ng_size & roSize)
	{
		m_oRectangle.offset(roSize);
	}
	long get_prop_position() const;
	long get_prop_range() const;
	bool get_prop_visible() const;

	bool set_prop_position(long nPosition);
	void set_prop_range(long nRange);
	void set_prop_visible(bool bVisible);

	cnui_element_manager * get_manager() const;
protected:
	virtual void _get_thumb_rect(ng_rect & roRect) const = 0;
	virtual bool _is_size_correct() const = 0;

	scrollable__ *	m_poScrollable;

	ng_rect	m_oRectangle;
	long	m_nRange;
	long	m_nPosition;
	bool	m_bVisible;

};

class cnui_vscroll_subelement : public cnui_scrollbar_subelement__
{
public:
	cnui_vscroll_subelement(scrollable__ * poScrollable) :
	  cnui_scrollbar_subelement__(poScrollable)
	{
	}
	void on_resize_owner(const ng_rect & roOwnerRect,bool bBothScrolls);
	bool _on_event_mouse_click(ng_dc & roDC,const ng_point & roPoint);
	void paint(cnui_painter & roPainter);
private:
	virtual bool _is_size_correct() const;
	void _get_up_arrow_rect(ng_rect & roRect) const;
	void _get_down_arrow_rect(ng_rect & roRect) const;
	virtual void _get_thumb_rect(ng_rect & roRect) const;

	void _get_thumb_range_(ng_ycoord & ryTop,ng_ycoord & rnBottom) const;
};

class cnui_hscroll_subelement : public cnui_scrollbar_subelement__
{
public:
	cnui_hscroll_subelement(scrollable__ * poScrollable) :
	  cnui_scrollbar_subelement__(poScrollable)
	{
	}
	void on_resize_owner(const ng_rect & roOwnerRect,bool bBothScrolls);
	bool _on_event_mouse_click(ng_dc & roDC,const ng_point & roPoint);
	void paint(cnui_painter & roPainter);
private:
	virtual bool _is_size_correct() const;
	void _get_left_arrow_rect(ng_rect & roRect) const;
	void _get_right_arrow_rect(ng_rect & roRect) const;
	virtual void _get_thumb_rect(ng_rect & roRect) const;

	void _get_thumb_range_(ng_xcoord & rxLeft,ng_xcoord & rxRight) const;
};

//------------------------------------------------------------------------ 
// scrollable__ class is abstract class providing scroll support
//------------------------------------------------------------------------ 
class scrollable__
{
public:
	//manages position - no update is performed
	const ng_size & get_prop_scroll_pos() const;
	ng_size get_prop_scroll_range() const;
	void set_prop_scroll_range(const ng_size & roSize);

	//performs scroll logical
	ng_size scroll_to(const ng_size & roNewScrollPos);
	ng_size scroll_by(const ng_size & roDistance);

	//perform physical scroll (bitblt etc.)
	void _scroll(ng_dc & roDC,const ng_size & roScrollDistance);
protected:
	scrollable__(cnui_element * poOwningElement) :
		m_pOwningElement(poOwningElement),
		m_oVScrollSubElement(this),
		m_oHScrollSubElement(this)
	{
	}

	bool set_prop_scroll_pos(const ng_size & roSize);

	//maluje t³o w oparcie o property backcolor,backcolor(2). odejmuje z clipregionu!!
	//uwzglêdnia scroll
	void _scrollable_paint_std_background(cnui_painter & roPainter,const ng_rect & roBackRect);

	void _scrollable_paint(cnui_painter & roPainter);
	void _scrollable_move_by(const ng_size & roDistanceSize);
	void _scrollable_mouse_click(const nui_action_mouse & roActionMouse,nui_action_result & roResult);
	void _scrollable_mouse_drag(eDragPhase eDP,const nui_drag_info & roDragInfo,
		const nui_action_mouse & roActionMouse,nui_action_result & roResult);
	void _scrollable_on_resize(const ng_rect & roRect);
	void _scrollable_show(bool bHorizontal,bool bVertical);
	
	void _scrollable_focus(nui_action_call_stack & roCallStack,const nui_action_focus & roActionFocus,nui_action_result & roResult);
	void _scrollable_mouse_wheel(const nui_action_mouse_wheel & roActionMouseWheel,nui_action_result & roResult);

	//provides scrollable part of element
	virtual void get_scrollable_rect(ng_rect & roRect) = 0;

	cnui_vscroll_subelement m_oVScrollSubElement;
	cnui_hscroll_subelement m_oHScrollSubElement;

	ng_size					m_oScrollPosSize;
	cnui_element *			m_pOwningElement;

	friend class cnui_scrollbar_subelement__;
};

//------------------------------------------------------------------------ 

//------------------------ inlines ---------------------------------
inline const ng_size & scrollable__::get_prop_scroll_pos() const
{
	return m_oScrollPosSize;
}

inline bool scrollable__::set_prop_scroll_pos(const ng_size & roSize)
{
	ng_size oRangeSize = get_prop_scroll_range();
	//normalize position
	ng_size oNormalizedSize(roSize);
	oNormalizedSize.set_dx(max(0,oNormalizedSize.get_dx()));
	oNormalizedSize.set_dx(min(oRangeSize.get_dx(),oNormalizedSize.get_dx()));
	oNormalizedSize.set_dy(max(0,oNormalizedSize.get_dy()));
	oNormalizedSize.set_dy(min(oRangeSize.get_dy(),oNormalizedSize.get_dy()));

	if(get_prop_scroll_pos() == oNormalizedSize)
	{
		return false;
	}
	m_oScrollPosSize = oNormalizedSize;
	return true;
}

inline bool cnui_scrollbar_subelement__::get_prop_visible() const
{
	return m_bVisible;
}

inline long cnui_scrollbar_subelement__::get_prop_position() const
{
	return m_nPosition;
}

inline long cnui_scrollbar_subelement__::get_prop_range() const
{
	return m_nRange;
}

inline const ng_rect & cnui_scrollbar_subelement__::get_rect() const
{
	return m_oRectangle;
}

inline cnui_element_manager * cnui_scrollbar_subelement__::get_manager() const
{
	ASSERT(m_poScrollable != NULL);
	ASSERT(m_poScrollable->m_pOwningElement);
	return m_poScrollable->m_pOwningElement->get_manager();
}

inline void scrollable__::_scrollable_paint(cnui_painter & roPainter)
{
	m_oVScrollSubElement.paint(roPainter);
	m_oHScrollSubElement.paint(roPainter);
}

inline void scrollable__::_scrollable_move_by(const ng_size & roDistanceSize)
{
	m_oVScrollSubElement.move_by(roDistanceSize);
	m_oHScrollSubElement.move_by(roDistanceSize);
}

inline void scrollable__::_scrollable_on_resize(const ng_rect & roRect)
{
	m_oVScrollSubElement.on_resize_owner(roRect,true);
	m_oHScrollSubElement.on_resize_owner(roRect,true);
}

inline void scrollable__::set_prop_scroll_range(const ng_size & roVSize)
{
	m_oVScrollSubElement.set_prop_range(roVSize.get_dy());
	m_oHScrollSubElement.set_prop_range(roVSize.get_dx());
}

inline ng_size scrollable__::get_prop_scroll_range() const
{
	ng_size oSize(ng_xdist(m_oHScrollSubElement.get_prop_range()),
		ng_ydist(m_oVScrollSubElement.get_prop_range()));
	return oSize;
}

inline void scrollable__::_scrollable_show(bool bHorizontal,bool bVertical)
{
	m_oVScrollSubElement.set_prop_visible(bVertical);
	m_oHScrollSubElement.set_prop_visible(bHorizontal);
	
	if(!bVertical || !bHorizontal)
	{
		ng_size oSize(get_prop_scroll_pos());
		
		if(!bVertical)
		{
			oSize.set_dy(0);
		}
		if(!bHorizontal)
		{
			oSize.set_dx(0);
		}
		scroll_to(oSize);
	}
}

#else
	#error __FILE__ already included
#endif


