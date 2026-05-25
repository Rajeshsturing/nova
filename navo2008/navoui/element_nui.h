/*
	NAVO Enterprise 2008
	15.04.2002
	
	cnui_element
			- klasa bazowa elementów UI
*/


#ifndef _ELEMENT_NUI_H_
#define _ELEMENT_NUI_H_

class cnui_element: public CCmdTargetInterface
{
public:
	//--- measured ---

	

		//obszar w którym kontrolka jest 'aktywna' - mo¿na w ni¹ trafiæ
		//albo poci¹gn¹æ - z regu³y == get_area, ale s¹ kontrolki malujace
		//poza obszarem aktywnym czyli is_inside_hit_area < get_area
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;

	virtual bool should_paint(const cnui_painter & roPainter,const ng_point & roCurrentPoint) const;
	//~XPART

	virtual void finish_render(const ng_point & roCurrentPoint);
	


	//obszar odmalowywany przez kontrolkê
	//impl: dodaj swój obszar do roElementLUArea (nie nadpisuj)
	virtual void get_area(ng_area &) const {};	
	
	//obszary 't³a' :odmalowywany przez kontrolkê (dla przezroczystych = pusty)
	//oraz 'dziury' : zablokowanie malowania w tym obszarze (FUTURE_VERSION: opcja w przysz³oœci)
	//impl: dodaj swój obszar do roElementLUArea (nie nadpisuj)
	virtual void  get_back_areas(ng_area & roBackLUArea) const;

//XPART

//------ property GET -----------------
	nui_ident get_prop_redirect() const;
	virtual void get_prop_value(CSmartOleVariant & roSOV);

	enui_border_style get_prop_border_type() const;

	bool get_prop_ignore_sys_disable() const;

	nui_declattrinx get_prop_declattrib_inx() const;
	
//------ property SET -----------------
	void set_prop_alignment(enui_alignment eAlignment);
	void set_prop_printable(bool bPrintable);

	void set_prop_userprop(SCP<CHyperLinkInfo> & rpoUserPropHLISP);


	//przesuwa kontrolkê, aby punkt referencyjny by³ w roPoint
	ng_size __get_efective_scroll_stack(bool bDownwards);
	
	//draw element on surface

	virtual ng_ycoord render(cnui_renderer__ & roRenderer);

	virtual void measure(cnui_measure_info & roInfo,cnui_measures & roMeasures);
	virtual void add2sheet(cnui_sheet_constructor & roSheetConstructor);


	virtual void OnFinalRelease();

	//fragment support
	virtual void fragment_get_area(ng_area & roElementLUArea,long nFragmentId) const;	


	virtual void on_event_command(const nui_action_command & roActionCommand,nui_action_result & roResult);



	virtual bool save(cnui_storage_write & roStorageWrite);
	virtual void load(cnui_storage_read & roStorageRead);

	void __translate_scroll_stack(ng_rect & roRect,bool bDownwards);


	virtual void on_compact_memory() {}

//------ AUTOMATION -----------------
	//{{AFX_DISPATCH(cnui_element)
	afx_msg void CopyToAUTO(LPDISPATCH pDestElementDispatch);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	//XPART
	
	//special function: containter initiation
	void _resolve_container() const;
	//~XPART


	cnui_element(cnui_element_manager * poManager,const enui_type eType,const nui_ident nIdent);

	//notifikacje o zmianach - funkcje wo³ane z metod obs³ugi kontrolek
	void _mark_repaint(ng_area & roLUArea);
	virtual void _mark_repaint_all();
	void _mark_resized();

	void __internal_always_mark_resized();

	void __translate_scroll_stack(ng_area & roLUArea,bool bDownwards);
};


//XPART


inline const ng_size & cnui_element::get_before_vector() const
{
	return m_oBeforeVectorSize;
}




inline void cnui_element::get_back_areas(ng_area & roBackLUArea) const
{
	if(_is_fast_graphics() || m_oCurrAttrib.get_backcolor().is_opaque())	//jeœli nieprze¿roczysty to ca³y obszar
	{
		get_area(roBackLUArea);
	}
}

inline SCP<CHyperLinkInfo> cnui_element::get_prop_userprop()
{
	return m_poUserPropertiesSP;
}

inline void cnui_element::set_prop_userprop(SCP<CHyperLinkInfo> & rpoUserPropHLISP)
{
	if(get_prop_userprop().Get() == rpoUserPropHLISP.Get())
	{
		return;
	}
	m_poUserPropertiesSP = rpoUserPropHLISP;
	__set_dirty();
}

inline void cnui_element::fragment_get_area(ng_area & roElementLUArea,long nFragmentId) const
{
	nFragmentId;
	ASSERT(nFragmentId == 0);	//ERROR: this function MUST be overridden for fragmented elements
	get_area(roElementLUArea);
}



inline void cnui_element::__translate_scroll_stack(ng_area & roLUArea,bool bDownwards)
{
	roLUArea.offset(__get_efective_scroll_stack(bDownwards));
}

inline void cnui_element::__translate_scroll_stack(ng_rect & roRect,bool bDownwards)
{
	roRect.offset(__get_efective_scroll_stack(bDownwards));
}




#else
	#error __FILE__ already included
#endif
