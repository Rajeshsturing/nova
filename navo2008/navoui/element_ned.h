/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	element definition

*/

#ifndef _ELEMENT_NED_H_
#define _ELEMENT_NED_H_

namespace nedaw
{
	class cnedaw_element;
}

namespace ned
{
//-- forward declarations -----

class cned_container;
class cned_page;
class cned_toplevelpage;

class cned_storage_writer;
class cned_storage_reader;

enum eRelativePosition
{
	rp_above,		//element above
	rp_below,		//element below
	rp_leftside,	//element to the left
	rp_righside,	//element to the right
};

class cned_element : public CInterface__
{
public:
	const ned_ident get_ident() const;					//this element ident
	const ned_ident get_container_ident() const;		//container ident - may be nothing
	const ned_ident get_next_element_ident() const;		//next element ident
	const ned_ident get_prev_element_ident() const;		//previous element ident

	const ened_element_type get_type() const;			//this element type

	SCP<cned_container> get_container() const;			//container object- may be nothing
	SCP<cned_page> get_page() const;					//zwraca "najbli¿szego" ojca który jest stron¹ (subpage lub toplevel)
	SCP<cned_toplevelpage> get_toplevelpage() const;	//zwraca toppage

	SCP<cned_element>   get_element_on_ident(ned_ident idElement) const;

	cned_element_manager * get_manager();				//element manager
	const cned_element_manager * get_manager() const;

	SCP<nedaw::cnedaw_element> get_my_nedaw();
	SCP<nedaw::cnedaw_element> get_nedaw(ned_ident idElement);
//-------------- rendering support -------------------
	bool is_measure_pending() const;			//czy coœ siê zmieni³o i trzeba mierzyæ

	void set_measure_pending();					//ustaw zmianê
	void clear_measure_pending();				//wyczyæ zmianê (po zrobieniu)

	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics) = 0;
	virtual void render(cned_renderer_ & roRenderer);
	virtual bool abs_render(cned_absolute_renderer & roAbsRenderer,const ned_position & roPosition,
		const ng_point & roFlowPoint);

	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);

	virtual bool is_inside_hit_area(const ng_point & roPoint /*we wspó³rzêdnych kontenera*/) const;
	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect /*we wspó³rzêdnych kontenera*/) const = 0;

	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect /*we wspó³rzêdnych kontenera*/,
		long & rnDistance) = 0;

	virtual void move_by(long nElementPart,const ng_size & roDistanceSize);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	virtual ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const = 0;
	virtual void get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const;
//-------------- attribute functions -------------------------
	virtual void apply_attributes(const ned_currattributes & roCurrAttrib);
	virtual void set_fixed_properties();	//ustawia nie-dziedziczone property
	const ned_currattributes & get_current_attributes() const;

	void set_style_item(long StyleItemId);

//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);

//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//--------------------------------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual void do_breaks(cpb_manager__ & roPBManager,const ng_point & roCurrentPoint);
	virtual void fill_clone_for_breaks(cpb_manager__ & roPBManager,long nAreaX,long nAreaY,cned_element * poDestination);

	virtual bool is_visually_empty() const;
//------ property GET -----------------

	ned_ident get_prop_redirect() const;
	virtual void get_prop_value(CSmartOleVariant & roSOV);

	ned_fontinx get_prop_fontinx() const;
	ng_color get_prop_forecolor() const;
	ng_color get_prop_backcolor() const;
	ng_color get_prop_backcolor2() const;
	
	ened_border_style get_prop_border_type() const;
	long get_prop_border_width() const;
	ng_color get_prop_border_color() const;

	bool get_prop_hidden() const;
	bool get_prop_disabled() const;
	bool get_prop_tabstop() const;
	bool get_prop_split_allowed() const;

	bool get_prop_ignore_sys_disable() const;
	bool get_prop_focus() const;
	ned_declattrinx get_prop_declattrib_inx() const;
	
	ng_xdist get_prop_extwidth() const;
	ng_ydist get_prop_extheight() const;

	ened_alignment get_prop_alignment() const;

	virtual void get_prop_tooltip_text(ng_string & roText) const;
	void get_prop_help_text(ng_string & roText) const;

	bool get_prop_printable() const;

	SCP<CHyperLinkInfo> get_prop_userprop();

//------ property SET -----------------
	void set_prop_redirect(ned_ident nRedirectIdent);

	virtual void set_prop_value(const CSmartOleVariant & roSOV);

	void set_prop_fontinx(ned_fontinx nFontInx);
	void set_prop_forecolor(ng_color nForeColor);
	void set_prop_backcolor(ng_color nBackColor);
	void set_prop_backcolor2(ng_color nBackColor2);

	virtual void set_prop_border_type(ened_border_style eStyle);
	void set_prop_border_width(long nPxWidth);
	void set_prop_border_color(ng_color nColor);

	virtual void set_prop_hidden(bool bHidden);
	void set_prop_disabled(bool bDisabled);
	void set_prop_tabstop(bool bTabStop);
	void set_prop_split_allowed(bool bSplit);

	void set_prop_ignore_sys_disable(bool bIgnoreSysDis);

	void set_prop_declattrib(const ned_declattributes & roDeclAttributes,bool bSizeDirty);

	void set_prop_extwidth(ng_xdist xWidth);
	void set_prop_extheight(ng_ydist yHeight);

	void set_prop_tooltip_text(const ng_string & roToolTipText);
	void set_prop_help_text(const ng_string & roHelpText);

	void set_prop_alignment(ened_alignment eAlignment);
	void set_prop_printable(bool bPrintable);

	void set_prop_userprop(SCP<CHyperLinkInfo> & rpoUserPropHLISP);

//-------------- short key support -------------- -------------- 
	void set_shortkey(SCP<cnui_shortkey> & rpoShortKeySP);
	SCP<cnui_shortkey> get_shortkey();
//------ ~ property  -----------------
	void set_decl_position(const ned_position & roPosition);
	bool get_decl_position(ned_position & roPosition) const;

//------- special functions -------------------
	void _set_container(SCP<cned_container> & rpoContainerSP);

//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);
	virtual void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);
	virtual void on_event_olecontrol(const ned_action_oleevent & roActionOleEvent,ned_action_result & roResult);

	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);

	//----------- splitting helper
	SCP<cned_element> _make_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY);
	//---------- rendering helpers ----------------
	ng_xdist _get_std_width_for_rendering(const cned_renderer_ & roRenderer) const;
	ng_ydist _get_std_height_for_rendering(ng_ydist dyHeightForAuto) const;
//---------- drawing helpers ----------------
	void _draw_std_frame(cned_fore_painter & roForePainter,const ng_rect & roFrameRect);
	void _draw_std_background(cned_back_painter & roBackPainter,const ng_rect & roBackRect);
	//---- paint invalidating --------

	virtual void _invalidate_all_paint() = 0;//mark all painted area need refresh

	//t³umaczenie wspó³rzêdnych (bez uwzglêdniania scrolla)
	void _arena2local(ng_point & roPoint) const;
	void _local2arena(ng_point & roPoint) const;
	void _local2arena(ng_rect & roRect) const;

	//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
	virtual void _screen2local(ng_point & roPoint) const;
	virtual void _local2screen(ng_point & roPoint) const;

	ned_ident search_tree_for_nearest_element(eRelativePosition eRP);

	const ned_element_mini_info & _mini_info() const;
protected:
	cned_element(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);
	~cned_element();

	void _vse_dirty();		//mark VSE dirty
	
	void _size_info_dirty();//mark size info dirty
	
	
	void _store_main_paint_rect(const ng_rect & roRect);
	void _store_extra_paint_rect(long nExtraId,const ng_rect & roRect);

	bool _get_main_paint_rect(ng_rect & roRect);
	bool _get_extra_paint_rect(long nExtraId,ng_rect & roRect);

	void _set_focus_to_me();
//-------------- rendering support -------------------

	ng_size					m_oVectorSize;			//offset to parent container's top left
	cned_metrics			m_oMetrics;
//----------------------------------------------------
	ned_element_mini_info & _mini_info();
private:
	//----------------------------------------------------
	void _vse_clean();
	bool _is_vse_dirty() const;
	//----------------------------------------------------

	virtual void OnFinalRelease();
	void _resolve_container() const;

	//called when element is removed from memory (page destruction, swap, element remove)
	//implementation should release all pointers
	virtual void __internal_cleanup();			

	//called when element is removed from page
	//implementation call internal-cleanup and 
	//frees other resources
	void _on_remove_element();					


	ned_ident				m_idThis;			//"this" ident
	cned_element_manager *	m_poManager;		//element manager (factory)
	SCP<cned_container>		m_poContainerSP;	//'resolved' container

	ned_element_mini_info	m_oMiniInfo;		//mini info

	ned_currattributes		m_oCurrAttrib;		//atrybuty bie¿ace
	ned_declattrinx			m_inxDeclAttrib;	//indeks atrybutów deklarowanych

	SCP<CHyperLinkInfo>		m_poUserPropertiesSP;	//inne property
	ned_ident				m_idRedirectEvents;		//redirect events to 'ident'
	bool					m_bVSE_Dirty;			//virtual storage 'dirty' flag

	friend class cned_element_manager; //for _mini_info
	friend class scroll_helper__;		//for read m_oVectorSize
	friend class cned_page;				//for read m_oVectorSize
};

//----------------------------------------------------------------------------------------------
bool _quote_rect_distance(eRelativePosition eRP,const ng_rect & roRefRect,const ng_rect & roTestRect,long & rnDistance);


SCP<CHyperLinkInfo> init_control_command_hli(ned_ident idDestElement,eStdControlCommandVerb eVerb);

void _compute_vector_from_position(cned_element_manager * poManager,const ned_position & roPosition,
	const ng_rect & roArenaRect,const ng_point & roFlowPoint,
	const ng_size & roSize,ng_size & roVector);

//--------------------------------------------------------------------------
// perform raw (bitblit) but smart scroll
//--------------------------------------------------------------------------

struct perform_scroll_param
{
	//input
	ng_dc * m_poDC;
	ng_rect m_oArenaSrcRect;
	ng_rect m_oArenaCompleteRect;
	ng_size m_oDistance;
	//output
	ng_rect m_oArenaInvalidRectY;
	ng_rect m_oArenaInvalidRectX;
};

void _perform_scroll(perform_scroll_param & roPSP);

//--------------------------------------------------------------------------
//zamienia tekst na postaæ wewnêtrzn¹ (tab <-> spacje, x0d <-> nic
//zwraca true jeœli dokona³ jakiœ zmian
bool text2internaltext(const ng_string & roExternalText,ng_string & roInternalText);
bool internaltext2text(const ng_string & roInternalText,ng_string & roExternalText);
//--------------------------------------------------------------------------
//		cned_rect_element_
//	plain element with rectangle shape (middle level helper class)
//--------------------------------------------------------------------------
class cned_rect_element_ : public cned_element
{
public:
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
//-------------- rendering support -------------------
	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics);
	virtual void render(cned_renderer_ & roRenderer);
	virtual bool abs_render(cned_absolute_renderer & roAbsRenderer,const ned_position & roPosition,
		const ng_point & roFlowPoint);
//--------- drawing ------------------
	virtual ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const;
	virtual void get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const;

	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);
//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);

	//--------------------------------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);

	//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
protected:
	cned_rect_element_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	virtual ng_size _compute_min_size(const ned_measure_param & roMParam) = 0;
	//---- paint invalidating --------
	virtual void _invalidate_all_paint();

	ng_size		m_oActualSize;			//actual size of this element
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

template<class CTARGET>
CTARGET * cast_ui(cned_element * poElement)
{
	CTARGET * poTargetType = static_cast<CTARGET *>(poElement);

	ASSERT(poTargetType);
	ASSERT(dynamic_cast<CTARGET *>(poElement) == poTargetType);
	return poTargetType;
}

template<class CTARGET>
SCP<CTARGET> scp_cast_ui(cned_element * poElement)
{
	CTARGET * poTargetType = static_cast<CTARGET *>(poElement);
	
	ASSERT(poTargetType);
	ASSERT(dynamic_cast<CTARGET *>(poElement) == poTargetType);
	
	return NewSCP<CTARGET>(poTargetType,true);
}


}

#else
	#error __FILE__ already included
#endif
