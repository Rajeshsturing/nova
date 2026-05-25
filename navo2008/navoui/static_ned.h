/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	ned_static / <t>

	jednoliniowy tekst / hyperlink

*/

#ifndef _STATIC_NED_H_
#define _STATIC_NED_H_

namespace ned
{

class cned_static : public cned_rect_element_
{
public:
//------ property GET -----------------

	virtual void get_prop_value(CSmartOleVariant & roSOV);
	long get_prop_charwidth() const;
	const ng_string & get_prop_text() const;
	SCP<CHyperLinkInfo> & get_prop_hyperlink();

//------ property SET -----------------
	
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_charwidth(long nCharWidth);
	void set_prop_text(const ng_string & roTextString);
	void set_prop_hyperlink(SCP<CHyperLinkInfo> poHyperLinkInfoSP);

//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);
//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
	//-------- page breaking ---------------------------------
	virtual bool is_visually_empty() const;

	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
protected:
	cned_static(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);
	void _create_test_string(ng_string & roString) const;
	void _invalidate_text_paint();

	void _copy_properties(cned_static * poDestinationStatic);

	ng_string	m_oTextString;
	long		m_nDeclCharWidth;				//zadeklarowany rozmiar w znakach
	
	SCP<CHyperLinkInfo> m_poHyperLinkInfoSP;	//opcjonalny hyperlink

	static const long TEXT_PAINT_RECT_ID;
private:
	ng_xdist	m_xTextWidth;					//wyliczona szerokoœæ tekstu

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline cned_static::cned_static(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_element_(poManager,eType,idThis),
	m_nDeclCharWidth(0),
	m_xTextWidth(0)
{
}

//------ property GET -----------------
inline void cned_static::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = get_prop_text();
}

inline long cned_static::get_prop_charwidth() const
{
	return m_nDeclCharWidth;
}

inline const ng_string & cned_static::get_prop_text() const
{
	return m_oTextString;
}

inline SCP<CHyperLinkInfo> & cned_static::get_prop_hyperlink()
{
	return m_poHyperLinkInfoSP;
}

//------ property SET -----------------
inline void cned_static::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_text(ng_string(roSOV.GetBStr()));
}

inline void cned_static::set_prop_charwidth(long nCharWidth)
{
	if(get_prop_charwidth() == nCharWidth)
	{
		return;
	}
	m_nDeclCharWidth = nCharWidth;

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_static::set_prop_text(const ng_string & roTextString)
{
	if(roTextString == get_prop_text())
	{
		return;
	}
	
	long nOldLength = m_oTextString.GetLength();

	m_oTextString = roTextString;
	
	long nNewLength = m_oTextString.GetLength();
	
	//info:
	//dodatkowo robimy invalidate
	//poniewa¿ samo _size_info_dirty nie zapewnia odœwie¿enia
	//gdy¿ sprytny algorytm post_render mo¿e wykluczyæ static'a z odmalowania siê

	_invalidate_all_paint();

	if((get_prop_charwidth() == 0) || (nNewLength >= get_prop_charwidth()) ||
		(nNewLength != nOldLength))
	{
		//patrz: _create_test_string - jeœli string jest krótszy od deklaracji
		//to i tak jest robiona estymacja - zatem rozmiar siê nie zmieni.
		//ostatni warunek nOldLength != nNewLength jest potrzebny przy
		//parent.aligment != left - wtedy ca³y static siê mo¿e przesun¹æ

		_size_info_dirty();
	}
	_vse_dirty();
}

inline void cned_static::set_prop_hyperlink(SCP<CHyperLinkInfo> poHyperLinkInfoSP)
{
	if(poHyperLinkInfoSP.Get() == m_poHyperLinkInfoSP.Get())
	{
		return;
	}
	
	//notifikuj tylko gdy pojawi³ siê / znikn¹³ hyperlink - treœæ nie ma znaczenia
	//dla rozmiaru i wygl¹du

	bool bNotify = (m_poHyperLinkInfoSP.PointsObject() != poHyperLinkInfoSP.PointsObject());
	m_poHyperLinkInfoSP = poHyperLinkInfoSP;

	if(bNotify)
	{
		_invalidate_all_paint();

		set_prop_tabstop(m_poHyperLinkInfoSP.PointsObject());
	}
	_vse_dirty();
}

//--------------event handlers ---------------------------------------
inline eCursorType cned_static::on_event_set_cursor(const ng_point & /*roPoint*/)
{
	return (get_prop_hyperlink().PointsObject() && !get_prop_disabled()) ? ect_hand : ect_default;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_static::_copy_properties(cned_static * poDestinationStatic)
{
	poDestinationStatic->m_oTextString = m_oTextString;
	poDestinationStatic->m_nDeclCharWidth = m_nDeclCharWidth;
}

inline void cned_static::fill_clone(cned_element * poDestination)
{
	cned_rect_element_::fill_clone(poDestination);
	cned_static * poDestStatic = cast_ui<cned_static>(poDestination);
	_copy_properties(poDestStatic);

	if(m_poHyperLinkInfoSP.PointsObject())
	{
		poDestStatic->m_poHyperLinkInfoSP = NewSCP(new CHyperLinkInfo(*m_poHyperLinkInfoSP));
	}
}

inline void cned_static::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_rect_element_::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_static * poDestStatic = cast_ui<cned_static>(poDestination);
	_copy_properties(poDestStatic);

	//dont copy hyperlink !
}

inline bool cned_static::is_visually_empty() const
{
	if(m_oTextString.IsEmpty())
	{
		return true;
	}
	{
		CString oString(m_oTextString);
		oString.TrimLeft();
		oString.TrimRight();

		return (oString.IsEmpty() != FALSE);
	}
}

//--------------- persistency -----------------------------------
inline void cned_static::save(cned_storage_writer & roWriter)
{
	cned_rect_element_::save(roWriter);

	roWriter <<	m_oTextString << m_nDeclCharWidth << m_xTextWidth << m_poHyperLinkInfoSP;
}

inline void cned_static::load(cned_storage_reader & roReader)
{
	cned_rect_element_::load(roReader);

	roReader >> m_oTextString >> m_nDeclCharWidth >> m_xTextWidth >> m_poHyperLinkInfoSP;
}

}

#else
	#error __FILE__ already included
#endif
