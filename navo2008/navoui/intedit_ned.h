/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_intedit		/ <intedit>
		kontrolka edycji integerów
*/

#ifndef _INTEDIT_NED_H_
#define _INTEDIT_NED_H_

namespace ned
{

class cned_intedit : public cned_edit__
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
	//---------------------------------------------------------
	virtual bool _is_auto_scroll();
	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

	//--------------------------------------------------------------------
	// helpers
	//--------------------------------------------------------------------
	void _correct_empty_buffer();	//insert 0 when buffer is empty
	void _correct_zero_buffer();	//remove zero when buffer is going to be non-zero number

	cned_intedit(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline bool cned_intedit::_is_auto_scroll()
{
	return false;
}


}

#else
	#error __FILE__ already included
#endif

