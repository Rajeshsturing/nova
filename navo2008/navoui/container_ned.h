/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	cned_container
		- kontener elementów UI (base class)
*/

#ifndef _CONTAINER_NED_H_
#define _CONTAINER_NED_H_

namespace nedaw
{
	class cnedaw_container;
}

namespace ned
{
class ned_path_to_element;

class cned_container : public cned_element
{
public:
	const ned_ident get_first_child_ident() const;
	const ned_ident get_last_child_ident() const;
	const long get_child_count() const;

	const ned_ident get_child_ident_on_pos(long nPosition) const;
	long scan_for_child_pos(ned_ident idChild) const;

	virtual SCP <cned_element> insert_new_element(ened_element_type eType,const ned_ident idNew,const ned_ident idAfter);
	void remove_element(ned_ident idElement);

	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
	virtual ned_ident find_element_relative(const ng_rect & roRefRect,const ned_ident nIdStart,eRelativePosition eRP,long & rnBestDistance);

	ned_ident find_element_next_prev(const ned_ident idStart,bool bNext);
//-------------- rendering support -------------------
	virtual void on_child_size_info_dirty(ned_ident idChild);		//dziecko siê zmieni³o
	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics);

	virtual void get_children_metrics(const ned_measure_param & roMParam);

//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_keydown(ned_path_to_element & roCallStack,const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_over(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
	virtual void process_event_focus(ned_path_to_element & roCallStack,const ned_action_focus & roActionFocus,ned_action_result & roResult);
	virtual void process_event_timer(ned_path_to_element & roCallStack,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	virtual void process_event_olecontrol(ned_path_to_element & roCallStack,
		const ned_action_oleevent & roActionOleEvent,ned_action_result & roResult);
	virtual void process_event_command(ned_path_to_element & roCallStack,const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual eCursorType process_event_set_cursor(ned_path_to_element & roCallStack,const ng_point & roPoint);
//-------------- attribute functions -------------------------
	virtual void apply_attributes(const ned_currattributes & roCurrAttrib);

	//------------- child management - overwritable ----------
	virtual void remove_children(bool bWhileRemovingItself);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual bool is_visually_empty() const;
//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);

	//-------- page breaking ---------------------------------
protected:
	cned_container(cned_element_manager * poManager,const ened_element_type eType,const ned_ident nIdent);
	~cned_container();

	//--------------------------------------------------------
	//------------- child management - overwritable ----------

	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident nChildIdent);

//---------- drawing helpers ----------------
	//malowanie kolejnych dzieci
	void _draw_foreground_children(cned_fore_painter & roForePainter,const ng_point & roInsidePaintPoint);
	void _draw_background_children(cned_back_painter & roBackPainter,const ng_point & roInsidePaintPoint);
	void _get_children_opaque_background_area(const ng_point & roInsidePaintPoint,ng_area & roArea) const;

	//--------------------------------------------------------
	void _update_children_split_info(const ng_point & roInsidePoint,cpb_split_info & roSplitInfo);
	void _make_children_split(const ng_point & roInsidePoint,cpb_split_manager & roSplitManager);

	//-------- page breaking ---------------------------------
	//--------------------------------------------------------
	void _post_render_children(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);

	void _link_element(const ned_ident idNewElement,const ned_ident idAfter);
	void _unlink_element(const ned_ident idElement);
	void _unlink_all_elements();

	ned_ident _get_last_measured() const;
	
	//gdy siê zepsu³o
	void _invalidate_last_measured(ned_ident idElement);
	//gdy naprawiamy
	void _validate_last_measured(ned_ident idElement);

	ned_ident		m_idFirstChild;
	ned_ident		m_idLastChild;
	long			m_nChildCount;
//-------------- rendering support -------------------
	ned_ident		m_idLastMeasured;


	friend class nedaw::cnedaw_container;
};


//--------------------------------------------------------------------------------------
//		cned_rect_container_
//	plain container with rectangle shape (middle level helper class)
//--------------------------------------------------------------------------------------
class cned_rect_container_ : public cned_container
{
public:
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
	virtual void get_bounding_rect(long nElementPart,ng_rect & roLocalRect) const;
//-------------- rendering support -------------------
	virtual bool abs_render(cned_absolute_renderer & roAbsRenderer,const ned_position & roPosition,
		const ng_point & roFlowPoint);

	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);
//--------- drawing ------------------
	virtual ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const;
	virtual void get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const;

	const ng_size & get_actual_size() const;

	//--------------------------------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);

	//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
protected:
	cned_rect_container_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident nIdent);
	//---- paint invalidating --------
	virtual void _invalidate_all_paint();

	ng_size		m_oActualSize;			//actual size of this element
};

//---------------------------------------------------------------------- 
// filters children (iterator) according to parameters
//---------------------------------------------------------------------- 

template<class NUITYPE>
class cned_filter_children__
{
public:
	cned_filter_children__(const cned_element_manager * poManager,ned_ident idFirst,bool bSkipHidden,bool bSkipNonPrintable);
	cned_filter_children__(const cned_container * poContainer,bool bSkipHidden,bool bSkipNonPrintable);

	bool is_end() const;
	void move_next();
	ned_ident get_ident() const;
	SCP< NUITYPE > get_element() const;
	virtual void restart_at(ned_ident idElement);
protected:
	bool _qualify(ned_ident idElement);
	virtual void _find_next_valid();

	const cned_element_manager * m_poManager;
	bool m_bSkipHidden;
	bool m_bSkipNonPrintable;
	ned_ident m_idCurrent;
};

typedef cned_filter_children__<cned_element> cned_filter_children;


//--------------------------------------------------------------------------------------
// œcie¿ka do elementu - stos kontenerów + element
//--------------------------------------------------------------------------------------

class ned_path_to_element
{
public:
	ned_path_to_element(cned_element * poTargetElement);
	
	SCP<cned_container> pop();
	SCP<cned_container> top();
	SCP<cned_element> target();
	bool is_empty() const;
private:
	void _build();

	SCP<cned_element> m_poTargetElementSP;
	CEnhancedStack< SCP<cned_container> >	m_oStack;
};



}
#else
	#error __FILE__ already included
#endif

