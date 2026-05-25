/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_checkbox / <checkbox>
		kontrolka check-box
*/

#ifndef _CHECKBOX_NED_H_
#define _CHECKBOX_NED_H_

namespace ned
{
class cned_checkbox : public cned_option_button_, public scroll_helper__
{
public:
	//------ property GET -----------------
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	virtual bool get_prop_checked(long nItemNr) const;
	//------ property SET -----------------
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_checked(long nItemNr,bool bChecked);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);

	//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
	virtual void _screen2local(ng_point & roPoint) const;
	virtual void _local2screen(ng_point & roPoint) const;

private:
	//------------- child management ----------
	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident idChild);

	virtual eSpecialImage _get_image_for_item(long nItemNr) const;
	virtual bool _on_item_selected(long nItemNr,ned_ident idElement);

	virtual void _on_finish_rendering(cned_renderer_ & roRenderer,const ng_size & roFullSize,
		ng_size & roForAllocSize);

	cned_checkbox(cned_element_manager * poManager,const ned_ident idThis);

	void _set_prop_value_from_string(const ng_string & roNewStateString);

	CArray<bool,bool> m_oItemStateArray;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_checkbox::cned_checkbox(cned_element_manager * poManager,const ned_ident idThis) :
	cned_option_button_(poManager,ned_checkbox,idThis),
	scroll_helper__(poManager,idThis)
{
}

//------ property GET -----------------
inline bool cned_checkbox::get_prop_checked(long nItemNr) const
{
	ASSERT(nItemNr >= 0 && nItemNr <= m_oItemStateArray.GetUpperBound());

	return m_oItemStateArray[ nItemNr ];
}


inline void cned_checkbox::get_prop_value(CSmartOleVariant & roSOV)
{
	ng_string oStateString('0',m_oItemStateArray.GetSize());
	for(long iter=0;iter<=m_oItemStateArray.GetUpperBound();iter++)
	{
		if(m_oItemStateArray[iter])
		{
			oStateString.SetAt(iter,'1');
		}
	}
	roSOV = oStateString;
}

//------ property SET -----------------
inline void cned_checkbox::set_prop_checked(long nItemNr,bool bChecked)
{
	if(get_prop_checked(nItemNr) == bChecked)
	{
		return;
	}

	ASSERT(nItemNr >= 0 && nItemNr <= m_oItemStateArray.GetUpperBound());
	m_oItemStateArray[ nItemNr ] = bChecked;
	
	_invalidate_image_rect(nItemNr);

	_vse_dirty();
}

inline void cned_checkbox::set_prop_value(const CSmartOleVariant & roSOV)
{
	_set_prop_value_from_string(roSOV.GetBStr());
}
//------ ------ ------ ------ ------ ------ ------ ------ ------ ------

inline void cned_checkbox::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	if(rpoChildSP->get_container_ident() == get_ident())
	{
		m_oItemStateArray.Add(false);
	}
	cned_option_button_::on_child_inserted(rpoChildSP);
}

inline void cned_checkbox::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		long nPos = scan_for_child_pos(idChild);
		m_oItemStateArray.RemoveAt(nPos);
	}
	cned_option_button_::on_child_removing(idChild);
}

//------ ------ ------ ------ ------ ------ ------ ------ ------ ------
inline void cned_checkbox::_set_prop_value_from_string(const ng_string & roNewStateString)
{
	ASSERT(roNewStateString.GetLength() == m_oItemStateArray.GetSize());

	for(long iter=0;iter < roNewStateString.GetLength();iter++)
	{
		set_prop_checked(iter,(roNewStateString.GetAt(iter) != '0'));
	}
}

inline eSpecialImage cned_checkbox::_get_image_for_item(long nItemNr) const
{
	ASSERT(nItemNr >= 0 && nItemNr <= m_oItemStateArray.GetUpperBound());
	bool bFocused = (get_prop_focus() && (nItemNr == m_nInternalFocusInx));
	return m_oItemStateArray[nItemNr] ? 
		(bFocused ? esi_check_se_fo : esi_check_se_nf) : 
		(bFocused ? esi_check_ns_fo : esi_check_ns_nf);
}

inline bool cned_checkbox::_on_item_selected(long nItemNr,ned_ident idElement)
{
	ASSERT(!get_manager()->is_element_hidden(idElement));

	if(!get_manager()->is_element_disabled(idElement))
	{
		set_prop_checked(nItemNr,!get_prop_checked(nItemNr));
		return true;
	}
	else
	{
		return false;
	}
}

//-------------- fill clone -------------- -------------- -------
inline void cned_checkbox::fill_clone(cned_element * poDestination)
{
	cned_option_button_::fill_clone(poDestination);
	
	cned_checkbox * poDestCheckBox = cast_ui<cned_checkbox>(poDestination);
	
	poDestCheckBox->m_oItemStateArray.Copy(m_oItemStateArray);
}

//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
inline void cned_checkbox::_screen2local(ng_point & roPoint) const
{
	cned_option_button_::_screen2local(roPoint);
	roPoint.offset(get_scroll_pos());
}

inline void cned_checkbox::_local2screen(ng_point & roPoint) const
{
	cned_option_button_::_local2screen(roPoint);
	roPoint.offset(-get_scroll_pos());
}

}

#else
	#error __FILE__ already included
#endif

