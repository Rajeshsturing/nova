/*
	NAVO Enterprise 2003
	2003-03-27

	navo enhanced display (NED)

	ned_staticex		/ <text>
		kontrolka tekstu wieloliniowego
*/

#ifndef _STATICEX_NED_H_
#define _STATICEX_NED_H_

namespace ned
{

class cned_staticex : public cned_element
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
//-------------- rendering support -------------------
	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics);
	virtual void render(cned_multi_line_renderer & roRenderer);
	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);

	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual void get_bounding_rect(long nElementPart,ng_rect & roLocalRect) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);

	virtual void move_by(long nElementPart,const ng_size & roDistanceSize);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	virtual ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const;
	virtual void _invalidate_all_paint();
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual void do_breaks(cpb_manager__ & roPBManager,const ng_point & roCurrentPoint);
	virtual void fill_clone_for_breaks(cpb_manager__ & roPBManager,long nAreaX,long nAreaY,cned_element * poDestination);
	virtual bool is_visually_empty() const;

	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
private:
	cned_staticex(cned_element_manager * poManager,const ned_ident idThis);
	
	void _render_finish_line(cned_multi_line_renderer & roRenderer,rendering_line & roRendLine,
		multiline_measurer & roMeasurer,bool bWithNewline,const ng_string & roInternalString);
	void _prepare_internal_text(ng_string & roInternalTextString) const;

	ng_string			m_oTextString;			//pe³en tekst
	long				m_nDeclCharWidth;		//zadeklarowany rozmiar w znakach
	SCP<CHyperLinkInfo> m_poHyperLinkInfoSP;
	
	multiline_manager	m_oMLM;					//multi line manager

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

//------ property GET -----------------
inline void cned_staticex::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = get_prop_text();
}

inline long cned_staticex::get_prop_charwidth() const
{
	return m_nDeclCharWidth;
}

inline const ng_string & cned_staticex::get_prop_text() const
{
	return m_oTextString;
}

inline SCP<CHyperLinkInfo> & cned_staticex::get_prop_hyperlink()
{
	return m_poHyperLinkInfoSP;
}

//------ property SET -----------------
inline void cned_staticex::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_text(ng_string(roSOV.GetBStr()));
}

inline void cned_staticex::set_prop_charwidth(long nCharWidth)
{
	if(get_prop_charwidth() == nCharWidth)
	{
		return;
	}
	m_nDeclCharWidth = nCharWidth;

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_staticex::set_prop_text(const ng_string & roTextString)
{
	if(roTextString == m_oTextString)
	{
		return;
	}
	m_oTextString = roTextString;

	//info:
	//dodatkowo robimy invalidate
	//poniewa¿ samo _size_info_dirty nie zapewnia odœwie¿enia
	//gdy¿ sprytny algorytm post_render mo¿e wykluczyæ static'a z odmalowania siê

	_invalidate_all_paint();
	_size_info_dirty();
	_vse_dirty();
}

inline void cned_staticex::set_prop_hyperlink(SCP<CHyperLinkInfo> poHyperLinkInfoSP)
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
inline eCursorType cned_staticex::on_event_set_cursor(const ng_point & /*roPoint*/)
{
	return (get_prop_hyperlink().PointsObject() && !get_prop_disabled()) ? ect_hand : ect_default;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_staticex::fill_clone(cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	cned_staticex * poDestSE = cast_ui<cned_staticex>(poDestination);

	poDestSE->m_oTextString = m_oTextString;
	poDestSE->m_nDeclCharWidth = m_nDeclCharWidth;
	
	if(m_poHyperLinkInfoSP.PointsObject())
	{
		poDestSE->m_poHyperLinkInfoSP = NewSCP(new CHyperLinkInfo(*m_poHyperLinkInfoSP));
	}
}

inline void cned_staticex::fill_clone_for_breaks(cpb_manager__ & roPBManager,long nAreaX,long nAreaY,cned_element * poDestination)
{
	cned_element::fill_clone_for_breaks(roPBManager,nAreaX,nAreaY,poDestination);
	cned_staticex * poDestSE = cast_ui<cned_staticex>(poDestination);

	//do not copy m_oTextString  - do_breaks is responsible for it
	poDestSE->m_nDeclCharWidth = m_nDeclCharWidth;

	//do not copy hyperlink
}

inline bool cned_staticex::is_visually_empty() const
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

inline void cned_staticex::move_by(long nElementPart,const ng_size & roDistanceSize)
{
	m_oMLM.move_by(nElementPart,roDistanceSize);
}

}

#else
	#error __FILE__ already included
#endif
