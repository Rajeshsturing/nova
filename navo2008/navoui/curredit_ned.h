/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_curredit		/ <currency>
		kontrolka edycji currency
*/

#ifndef _CURREDIT_NED_H_
#define _CURREDIT_NED_H_

namespace ned
{

class cned_curredit : public cned_edit__
{
public:
	//------ property GET -----------------
	const ng_string & get_prop_unit() const;
	long get_prop_precision() const;
	const ng_color & get_prop_negative_text_color();
	//------ property SET -----------------
	void set_prop_unit(const ng_string & roUnitString);
	void set_prop_precision(long nDeclPrecision);
	void set_prop_negative_text_color(const ng_color & roColor);

	//---------------------------------------------------------
	// buffer <-> data convertions
	//---------------------------------------------------------
	virtual bool buffer2variant(CSmartOleVariant & roSOV) const;
	virtual bool variant2buffer(const CSmartOleVariant & roSOV);
	//---------------------------------------------------------
	// kbd actions
	//---------------------------------------------------------
	virtual long _act_move(UINT nVKCode,bool bWithCtrl);
	virtual bool _act_delete(bool bWithShift);
	virtual bool _act_backspace(bool bWithShift);
	virtual bool _act_data(UINT nTranslatedChar);
	virtual bool _act_paste_from_string(const ng_string & roString);
	virtual void _act_copy_to_string(ng_string & roString);
	virtual bool _act_cut_to_string(ng_string & roString);
	virtual void _after_got_focus();

	//---------------------------------------------------------
	virtual bool _is_auto_scroll();
	virtual ng_color _get_text_color(bool bTreeDisabled);
	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
	//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
private:
	cned_curredit(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;

	void _copy_properties(cned_curredit * poDestinationCyEdit);
	//--------------------------------------------------------------------
	// helpers
	//--------------------------------------------------------------------
	bool _internal_set_prop_unit(const ng_string & roUnitString);
	bool _internal_set_prop_precision(long nDeclPrecision);

	long __get_digit_nr(long nBufferInx) const;		//zwraca nr nDigitNr dla podanego znaku w buforze
	long __lookup_position(long nDigitNr) const;	//zwraca pozycjê w buforze dla podanego DigitNr

	long __get_unit_pos() const;
	long __get_dot_pos() const;

	void __compose_string(ng_string & roString);	//generate string representation
	void __delete_in_whole_part(long nDigitNr);		//nDigitNr - po obciêciu separatora tysiêcy
	void __insert_in_whole_part(long nValue,long nDigitNr);	//nDigitNr - po obciêciu separatora tysiêcy
	void __delete_in_fractional_part(long nDigitNr);//nDigitNr - UJEMNA pozycja dziesiêtna 
	void __insert_in_fractional_part(long nValue,long nDigitNr); //nDigitNr - UJEMNA pozycja dziesiêtna 

	bool __delete_selection();

	long			m_nDeclPrecision;
	long			m_nActualPrecision;
	ng_string		m_oUnitString;
	COleCurrency	m_oValueCurrency;
	ng_color		m_oNegativeTextColor;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline bool cned_curredit::_is_auto_scroll()
{
	return false;
}

//------ property GET -----------------
inline long cned_curredit::get_prop_precision() const
{
	return m_nDeclPrecision;
}

inline const ng_string & cned_curredit::get_prop_unit() const
{
	return m_oUnitString;
}

inline const ng_color & cned_curredit::get_prop_negative_text_color()
{
	return m_oNegativeTextColor;
}
//------ property SET -----------------
inline bool cned_curredit::_internal_set_prop_precision(long nDeclPrecision)
{
	if(get_prop_precision() == nDeclPrecision)
	{
		return false;
	}

	if(nDeclPrecision < 0 || nDeclPrecision > 4)
	{
		//error: negative precision
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,"");
	}

	m_nDeclPrecision = nDeclPrecision;
	if(m_nActualPrecision < m_nDeclPrecision)
	{
		m_nActualPrecision = m_nDeclPrecision;
	}

	variant2buffer(m_oValueCurrency); //regenerate buffer

	_set_infra_update_pending();
	_vse_dirty();
	return true;
}

inline void cned_curredit::set_prop_precision(long nDeclPrecision)
{
	if(!_internal_set_prop_precision(nDeclPrecision))
	{
		return;
	}

	//samo zaznaczenie infra_update nie powoduje odmalowania - musimy wywo³aæ ma³y update
	_invalidate_internal_paint();		
}

inline bool cned_curredit::_internal_set_prop_unit(const ng_string & roUnitString)
{
	if(get_prop_unit() == roUnitString)
	{
		return false;
	}
	m_oUnitString = roUnitString;

	variant2buffer(m_oValueCurrency);	//regenerate buffer

	_set_infra_update_pending();
	_vse_dirty();
	return true;
}

inline void cned_curredit::set_prop_unit(const ng_string & roUnitString)
{
	if(!_internal_set_prop_unit(roUnitString))
	{
		return;
	}
	//samo zaznaczenie infra_update nie powoduje odmalowania - musimy wywo³aæ ma³y update
	_invalidate_internal_paint();		
}

inline void cned_curredit::set_prop_negative_text_color(const ng_color & roColor)
{
	if(get_prop_negative_text_color() == roColor)
	{
		return;
	}

	m_oNegativeTextColor = roColor;
	
	if (m_oValueCurrency < COleCurrency(0,0))
	{
		_invalidate_internal_paint();
	}
	
	_vse_dirty();
}

//---------------------------------------------------------
// buffer <-> data convertions
//---------------------------------------------------------
inline bool cned_curredit::buffer2variant(CSmartOleVariant & roSOV) const
{
	roSOV = m_oValueCurrency;
	return true;
}

inline bool cned_curredit::variant2buffer(const CSmartOleVariant & roSOV)
{
	m_oValueCurrency = roSOV.GetCurrency();
	ng_string oString;
	__compose_string(oString);
	
	if(oString != m_State.m_oBufferString)
	{
		_set_new_buffer_text(m_State,oString);
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------
// helpers
//--------------------------------------------------------------------
inline long cned_curredit::__get_unit_pos() const
{
	long nUnitLen = m_oUnitString.GetLength();
	return m_State.m_oBufferString.GetLength() - nUnitLen - ((nUnitLen != 0) ? 1 : 0);
}

inline long cned_curredit::__get_dot_pos() const
{
	return __get_unit_pos() - m_nActualPrecision - ((m_nActualPrecision != 0) ? 1 : 0);
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------
inline bool cned_curredit::_act_paste_from_string(const ng_string & roString)
{
	CSmartOleVariant oSOV(roString);
	if(!oSOV.SafeChangeType(VT_CY))
	{
		return false;
	}
	variant2buffer(oSOV);
	return true;
}

inline void cned_curredit::_act_copy_to_string(ng_string & roString)
{
	CSmartOleVariant oSOV(m_oValueCurrency);
	oSOV.ChangeType(VT_BSTR);
	roString = oSOV.GetBStr();
}

inline bool cned_curredit::_act_cut_to_string(ng_string & roString)
{
	_act_copy_to_string(roString);
	return false;
}

//---------------------------------------------------------
inline ng_color cned_curredit::_get_text_color(bool bTreeDisabled)
{
	if(get_prop_disabled() || bTreeDisabled)
	{
		return cned_edit__::_get_text_color(bTreeDisabled);
	}
	else
	{
		return (m_oValueCurrency < COleCurrency(0,0)) ? 
			get_prop_negative_text_color() : 
			get_prop_forecolor();
	}
}

//-------------- fill clone -------------- -------------- -------
inline void cned_curredit::_copy_properties(cned_curredit * poDestinationCyEdit)
{
	poDestinationCyEdit->m_nDeclPrecision	= m_nDeclPrecision;
	poDestinationCyEdit->m_nActualPrecision	= m_nActualPrecision;
	poDestinationCyEdit->m_oUnitString		= m_oUnitString;
	poDestinationCyEdit->m_oValueCurrency	= m_oValueCurrency;
	poDestinationCyEdit->m_oNegativeTextColor= m_oNegativeTextColor;
}

inline void cned_curredit::fill_clone(cned_element * poDestination)
{
	cned_edit__::fill_clone(poDestination);
	cned_curredit * poCurrDest = cast_ui<cned_curredit>(poDestination);
	
	_copy_properties(poCurrDest);
}

//-------- page breaking ---------------------------------
inline void cned_curredit::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_edit__::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_curredit * poCurrDest = cast_ui<cned_curredit>(poDestination);
	_copy_properties(poCurrDest);
}

}

#else
	#error __FILE__ already included
#endif

