/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_option_button_		
		klasa bazowa dla radio i checkbox'a
*/

#ifndef _OPTIONBUTTON_NED_H_
#define _OPTIONBUTTON_NED_H_

namespace ned
{

class cned_option_button_ : public cned_rect_container_, public cned_line_consumer_
{
public:
//------ property GET -----------------
	long get_prop_colspan() const;
	virtual bool get_prop_checked(long nItemNr) const = 0;
//------ property SET -----------------
	void set_prop_colspan(long nColSpan);
	virtual void set_prop_border_type(ened_border_style eStyle);

//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);
	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);

	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
protected:
	cned_option_button_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	virtual eSpecialImage _get_image_for_item(long nItemNr) const = 0;
	virtual bool _on_item_selected(long nItemNr,ned_ident idElement) = 0;

	//-------------- drawing helpers ---------------------
	void _get_image_rect(long nItemNr,const ng_point & roCurrPoint,ng_rect & roImageRect) const;
	
	bool _find_image_from_point(const ng_point & roLocalPoint,long & rnElementNr,ned_ident & ridElement);
	bool _on_internal_focus_change(long nItemNr,ned_ident idElement);

	void _invalidate_image_rect(long nItemNr);

	//-------------- rendering support -------------------
	void _compute_final_col_widths(ng_xdist dxAvailWidth,bool bPrinting);
	virtual void add_line(const cned_element_line & roLine);
	virtual void _on_finish_rendering(cned_renderer_ & roRenderer,const ng_size & roFullSize,
		ng_size & roForAllocSize);

	//------------- child management ----------
	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident idChild);

	void _event_set_selection_to(ned_ident idElement,long nElementNr,ned_action_result & roResult,bool bChildClick);

	class column_info
	{
	public:
		column_info();
		
		ng_xdist get_min_width() const;
		ng_xdist get_col_width() const;
		ng_ydist get_min_height() const;

		void update_min_width(ng_xdist xWidth);
		void update_min_height(ng_ydist yHeight);

		void set_col_width(ng_xdist xColWidth);
		
		void reset();
	private:
		ng_xdist	m_xColWidth;		//aktualna szerokoœæ kolumny
		ng_xdist	m_xMinWidth;		//minimalna szerokoœæ kolumny
		ng_ydist	m_yMinHeight;		//minimalna wysokoœæ kolumny
	};
	
	long							m_nInternalFocusInx;
	//----- rendering info --------------------------
	CArray<column_info,column_info&>	m_oColArray;
	CArray<ng_ydist,ng_ydist>			m_oRowHeightArray;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_option_button_::column_info::column_info():
	m_xColWidth(0),
	m_xMinWidth(0),
	m_yMinHeight(0)
{
}

inline ng_xdist cned_option_button_::column_info::get_min_width() const
{
	return m_xMinWidth;
}

inline ng_xdist cned_option_button_::column_info::get_col_width() const
{
	return m_xColWidth;
}

inline ng_ydist cned_option_button_::column_info::get_min_height() const
{
	return m_yMinHeight;
}

inline void cned_option_button_::column_info::update_min_width(ng_xdist xWidth)
{
	m_xMinWidth = max(m_xMinWidth,xWidth);
}

inline void cned_option_button_::column_info::update_min_height(ng_ydist yHeight)
{
	m_yMinHeight += yHeight;
}

inline void cned_option_button_::column_info::set_col_width(ng_xdist xColWidth)
{
	m_xColWidth = xColWidth;
}

inline void cned_option_button_::column_info::reset()
{
	m_xColWidth = 0;
	m_xMinWidth = 0;
	m_yMinHeight = 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline cned_option_button_::cned_option_button_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis):
	cned_rect_container_(poManager,eType,idThis),
	m_nInternalFocusInx(-1)
{
	m_oColArray.Add(column_info());
	set_prop_tabstop(true);
};

//------ property GET -----------------
inline long cned_option_button_::get_prop_colspan() const
{
	return m_oColArray.GetSize();
}

//------ property SET -----------------
inline void cned_option_button_::set_prop_colspan(long nColSpan)
{
	ASSERT(nColSpan >= 1);
	if(get_prop_colspan() == nColSpan)
	{
		return;
	}
	m_oColArray.SetSize(nColSpan);
	
	_size_info_dirty();
	_vse_dirty();
}

inline void cned_option_button_::set_prop_border_type(ened_border_style eStyle)
{
	if(get_prop_border_type() == eStyle)
	{
		return;
	}

	cned_rect_container_::set_prop_border_type(eStyle);

	_size_info_dirty();
	_vse_dirty();
}

//------ ------ ------ ------ ------ ------ ------ ------ ------ ------

inline void cned_option_button_::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	if(rpoChildSP->get_container_ident() == get_ident())
	{
		if(get_child_count() == 1)	//pierwszy
		{
			ASSERT(m_nInternalFocusInx == -1);	//bo nie mo¿e byæ inaczej
			m_nInternalFocusInx = 0;
		}
	}
	cned_rect_container_::on_child_inserted(rpoChildSP);
}

inline void cned_option_button_::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		long nPos = scan_for_child_pos(idChild);
		
		//jeœli internal index jest w³aœnie usuwanym - cofnij o 1
		if(m_nInternalFocusInx == nPos)
		{
			m_nInternalFocusInx--;
		}
	}
	cned_rect_container_::on_child_removing(idChild);
}

inline bool cned_option_button_::_on_internal_focus_change(long nItemNr,ned_ident idElement)
{
	ASSERT(!get_manager()->is_element_hidden(idElement));

	if(!get_manager()->is_element_disabled(idElement))
	{
		if(m_nInternalFocusInx != nItemNr)
		{
			if(m_nInternalFocusInx != -1)
			{
				_invalidate_image_rect(m_nInternalFocusInx);
			}
			
			m_nInternalFocusInx = nItemNr;
			
			if(m_nInternalFocusInx != -1)
			{
				_invalidate_image_rect(m_nInternalFocusInx);
			}
		}

		return true;
	}
	return false;
}

inline void cned_option_button_::_invalidate_image_rect(long nItemNr)
{
	get_manager()->invalidate_paint_rect(get_ident(),nItemNr + 1);
}

//-------------- fill clone -------------- -------------- -------
inline void cned_option_button_::fill_clone(cned_element * poDestination)
{
	cned_rect_container_::fill_clone(poDestination);
	cned_option_button_ * poDestOB = cast_ui<cned_option_button_>(poDestination);
	poDestOB->m_nInternalFocusInx = m_nInternalFocusInx;
	poDestOB->set_prop_colspan(get_prop_colspan());
}

//-------------- rendering support -------------------
inline void cned_option_button_::_on_finish_rendering(cned_renderer_ &,const ng_size & roFullSize,
		ng_size & roForAllocSize)
{
	roForAllocSize = roFullSize;
}


}

#else
	#error __FILE__ already included
#endif

