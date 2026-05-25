/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_dateedit		/ <dateedit>
		kontrolka edycji dat
*/

#ifndef _DATEEDIT_NED_H_
#define _DATEEDIT_NED_H_

namespace ned
{

class cned_dateedit : public cned_edit__
{
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
	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

	virtual void get_prop_tooltip_text(ng_string & roText) const;
	//---------------------------------------------------------
	virtual bool _is_auto_scroll();
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void _fill_command_list(ned_action_result & roResult);
private:
	cned_dateedit(cned_element_manager * poManager,const ned_ident idThis);

	bool __act_set_null(bool bWithShift);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_dateedit::cned_dateedit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_edit__(poManager,ned_date,idThis)
{
	_set_new_buffer_text(m_State,_metrics().dateedit().get_null_text());
}

//---------------------------------------
inline bool cned_dateedit::_is_auto_scroll()
{
	return false;
}

//-------------- attribute functions -------------------------
inline void cned_dateedit::set_fixed_properties()
{
	cned_edit__::set_fixed_properties();
	set_prop_charwidth(_metrics().dateedit().get_format_len());
}

inline bool cned_dateedit::__act_set_null(bool bWithShift)
{
	if(!bWithShift)
	{
		if(m_State.m_nCharSelFirst != 0 || m_State.m_nCharSelLast != _metrics().dateedit().get_format_len())
		{
			return false;
		}
	}
	_set_new_buffer_text(m_State,_metrics().dateedit().get_null_text());

	return true;
}


}

#else
	#error __FILE__ already included
#endif

