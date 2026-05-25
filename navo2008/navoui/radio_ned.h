/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_radiobutton / <radio>
		kontrolka radio-button
*/

#ifndef _RADIOBUTTON_NED_H_
#define _RADIOBUTTON_NED_H_

namespace ned
{
class cned_radio_button : public cned_option_button_
{
//------ property GET -----------------
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	virtual bool get_prop_checked(long nItemNr) const;
	long get_prop_checked_item() const;
//------ property SET -----------------
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_checked_item(long nItemNr);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
private:
	cned_radio_button(cned_element_manager * poManager,const ned_ident idThis);

	virtual eSpecialImage _get_image_for_item(long nItemNr) const;
	virtual bool _on_item_selected(long nItemNr,ned_ident idElement);
	//------------- child management ----------
	virtual void on_child_removing(ned_ident idChild);

	long m_nCheckedItemInx;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_radio_button::cned_radio_button(cned_element_manager * poManager,const ned_ident idThis) :
	cned_option_button_(poManager,ned_radio,idThis),
	m_nCheckedItemInx(-1)
{
}

//------ property GET -----------------
inline bool cned_radio_button::get_prop_checked(long nItemNr) const
{
	return (m_nCheckedItemInx == nItemNr);
}

inline long cned_radio_button::get_prop_checked_item() const
{
	return m_nCheckedItemInx;
}

inline void cned_radio_button::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = long(1+m_nCheckedItemInx);
}

//------ property SET -----------------
inline void cned_radio_button::set_prop_checked_item(long nItemNr)
{
	ASSERT(nItemNr >= 0 && nItemNr < get_child_count());

	if(nItemNr == get_prop_checked_item())
	{
		return;
	}
	
	_invalidate_image_rect(get_prop_checked_item());
	
	m_nCheckedItemInx = nItemNr;

	_invalidate_image_rect(get_prop_checked_item());

	_vse_dirty();
}

inline void cned_radio_button::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_checked_item(roSOV.GetLong() - 1);
}

//------------- child management ----------
inline void cned_radio_button::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		long nPos = scan_for_child_pos(idChild);
		
		//jeœli checked index jest w³aœnie usuwanym to cofnij o 1
		if(m_nCheckedItemInx == nPos)
		{
			m_nCheckedItemInx--;
		}
	}
	cned_option_button_::on_child_removing(idChild);
}

inline eSpecialImage cned_radio_button::_get_image_for_item(long nItemNr) const
{
	bool bFocused = (get_prop_focus() && (nItemNr == m_nInternalFocusInx));

	return (m_nCheckedItemInx == nItemNr) ? 
		(bFocused ? esi_radio_se_fo : esi_radio_se_nf) : 
		(bFocused ? esi_radio_ns_fo : esi_radio_ns_nf);
}

inline bool cned_radio_button::_on_item_selected(long nItemNr,ned_ident idElement)
{
	ASSERT(!get_manager()->is_element_hidden(idElement));
	
	if(!get_manager()->is_element_disabled(idElement))
	{
		if(get_prop_checked_item() != nItemNr)
		{
			set_prop_checked_item(nItemNr);
			return true;
		}
	}
	return false;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_radio_button::fill_clone(cned_element * poDestination)
{
	cned_option_button_::fill_clone(poDestination);
	
	cned_radio_button * poDestRadio = cast_ui<cned_radio_button>(poDestination);
	
	poDestRadio->m_nCheckedItemInx = m_nCheckedItemInx;
}


}

#else
	#error __FILE__ already included
#endif

