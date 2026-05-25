/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_timeedit		/ <time>
		kontrolka edycji czasu
*/

#ifndef _TIMEEDIT_NED_H_
#define _TIMEEDIT_NED_H_

namespace ned
{

class cned_timeedit : public cned_edit__
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
	//---------------------------------------------------------
	virtual bool _is_auto_scroll();
private:
	cned_timeedit(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_timeedit::cned_timeedit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_edit__(poManager,ned_timeed,idThis)
{
	_set_new_buffer_text(m_State,_metrics().timeedit().get_null_text());
}

inline bool cned_timeedit::_is_auto_scroll()
{
	return false;
}

//-------------- attribute functions -------------------------
inline void cned_timeedit::set_fixed_properties()
{
	cned_edit__::set_fixed_properties();
	set_prop_charwidth(_metrics().timeedit().get_format_len());
}

}

#else
	#error __FILE__ already included
#endif

