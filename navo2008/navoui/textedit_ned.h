/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_textedit		/ <edit>
		kontrolka edycji tekstów
*/

#ifndef _TEXTEDIT_NED_H_
#define _TEXTEDIT_NED_H_

namespace ned
{

class cned_textedit : public cned_edit__
{
public:
	//------ property GET -----------------
	bool get_prop_password() const;
	bool get_prop_clearonly() const;
	//------ property SET -----------------
	void set_prop_password(bool bPassword);
	void set_prop_clearonly(bool bClearOnly);

//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
private:
	//---------------------------------------------------------
	// buffer <-> data convertions
	//---------------------------------------------------------
	virtual bool buffer2variant(CSmartOleVariant & roSOV) const;
	virtual bool variant2buffer(const CSmartOleVariant & roSOV);

	virtual void get_visible_buffer(ng_string & roString) const;
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
	//---------------------------------------------------------
	virtual bool _is_auto_scroll();
	virtual void _after_act_move(long nNewCaretPos,bool bShift);
	virtual void _after_got_focus();
private:
	cned_textedit(cned_element_manager * poManager,const ned_ident idThis);

	bool	m_bPassword;
	bool	m_bClearOnly;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_textedit::cned_textedit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_edit__(poManager,ned_textedit,idThis),
	m_bPassword(false),
	m_bClearOnly(false)
{
}

inline bool cned_textedit::_is_auto_scroll()
{
	return true;
}

//------ property GET -----------------
inline bool cned_textedit::get_prop_password() const
{
	return m_bPassword;
}

inline bool cned_textedit::get_prop_clearonly() const
{
	return m_bClearOnly;
}

//------ property SET -----------------
inline void cned_textedit::set_prop_password(bool bPassword)
{
	if(get_prop_password() == bPassword)
	{
		return;
	}
	m_bPassword = bPassword;

	_set_infra_update_pending();
	//samo zaznaczenie infra_update nie powoduje odmalowania - musimy wywo³aæ ma³y update
	_invalidate_internal_paint();		
	_vse_dirty();
}

inline void cned_textedit::set_prop_clearonly(bool bClearOnly)
{
	if(get_prop_clearonly() == bClearOnly)
	{
		return;
	}
	m_bClearOnly = bClearOnly;
	
	_vse_dirty();
}


//---------------------------------------------------------
// buffer <-> data convertions
//---------------------------------------------------------
inline bool cned_textedit::buffer2variant(CSmartOleVariant & roSOV) const
{
	roSOV = m_State.m_oBufferString;
	return true;
}

inline bool cned_textedit::variant2buffer(const CSmartOleVariant & roSOV)
{
	ng_string oString = roSOV.GetBStr();
	if(oString != m_State.m_oBufferString)
	{
		_set_new_buffer_text(m_State,oString);
		return true;
	}
	return false;
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------
inline bool cned_textedit::_act_paste_from_string(const ng_string & roString)
{
	if(get_prop_clearonly())
	{
		return false;
	}

	_set_new_buffer_text(m_State,roString);

	return true;
}

inline void cned_textedit::_act_copy_to_string(ng_string & roString)
{
	get_visible_buffer(roString);

	if(m_State.is_selection())
	{
		roString = roString.Mid(m_State.m_nCharSelFirst,m_State.m_nCharSelLast - m_State.m_nCharSelFirst);
	}
}

inline bool cned_textedit::_act_cut_to_string(ng_string & roString)
{
	_act_copy_to_string(roString);
	if(get_prop_clearonly())
	{
		return true;
	}
	m_State.delete_selected_chars();
	
	return true;
}

inline void cned_textedit::_after_act_move(long nNewCaretPos,bool bShift)
{
	if(get_prop_clearonly())
	{
		return;
	}

	cned_edit__::_after_act_move(nNewCaretPos,bShift);
}

inline bool cned_textedit::_act_data(UINT nTranslatedChar)
{
	if(get_prop_clearonly())
	{
		return false;
	}
	m_State.insert_char(nTranslatedChar);
	return true;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_textedit::fill_clone(cned_element * poDestination)
{
	cned_edit__::fill_clone(poDestination);
	
	cned_textedit * poTextEditDest = cast_ui<cned_textedit>(poDestination);
	poTextEditDest->m_bPassword = m_bPassword;
	poTextEditDest->m_bClearOnly = m_bClearOnly;
}

inline void cned_textedit::get_visible_buffer(ng_string & roString) const
{
	if(get_prop_password())
	{
		roString = ng_string('*',m_State.m_oBufferString.GetLength());
	}
	else
	{
		roString = m_State.m_oBufferString;
	}
}

}

#else
	#error __FILE__ already included
#endif

