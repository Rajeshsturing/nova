/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabmanager / <tab>
		tabmanager
*/

#ifndef _TABMANAGER_NED_H_
#define _TABMANAGER_NED_H_

namespace ned
{
class cned_tabmanager_header_;
class cned_tabmanager_item;

class cned_tabmanager : public cned_rect_container_
{
public:
	//------ property GET -----------------
	long get_prop_active_item_nr() const;
	long get_prop_tabs_in_row() const;
	//------ property SET -----------------
	bool set_prop_active_item_nr(long nActiveItem);
	void set_prop_tabs_in_row(long nTabsInRow);
	
	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
	//------------- child management ----------
	virtual void remove_children(bool bWhileRemovingItself);

	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident nChildIdent);
	//-------------- rendering support -------------------
	virtual void on_child_size_info_dirty(ned_ident idChild);		//dziecko siê zmieni³o
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void apply_attributes(const ned_currattributes & roCurrAttrib);
	virtual void set_fixed_properties();	//ustawia nie-dziedziczone property
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//--------------- notications from item --------------------------- 
	const ng_string & get_item_title(ned_ident idTabItem);
	void set_item_title(ned_ident idTabItem,const ng_string & roTitleString);
	//--------------event handlers ---------------------------------------
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
private:
	cned_tabmanager(cned_element_manager * poManager,const ned_ident idThis);

	void __construct_header();

	ned_ident _get_header_ident() const;
	SCP<cned_tabmanager_header_> _get_header() const;
	SCP<cned_tabmanager_item> get_active_item();

	ned_ident m_idHeader;
	long m_nActiveItemNr;


	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline ned_ident cned_tabmanager::_get_header_ident() const
{
	ASSERT(m_idHeader != NEDID_NOTHING);
	return m_idHeader;
}

inline SCP<cned_tabmanager_header_> cned_tabmanager::_get_header() const
{
	return scp_cast_ui<cned_tabmanager_header_>(get_element_on_ident(_get_header_ident()));
}
	
inline SCP<cned_tabmanager_item> cned_tabmanager::get_active_item()
{
	return scp_cast_ui<cned_tabmanager_item>(get_element_on_ident(get_child_ident_on_pos(get_prop_active_item_nr())));
}

//------ property GET -----------------
inline long cned_tabmanager::get_prop_active_item_nr() const
{
	return m_nActiveItemNr;
}

//------ property SET -----------------
inline bool cned_tabmanager::set_prop_active_item_nr(long nActiveItemNr)
{
	bool bFirstTime = false;

	if(get_prop_active_item_nr() == nActiveItemNr)
	{
		return bFirstTime;
	}

	//hide old, show new
	if(get_prop_active_item_nr() >= 0 && get_prop_active_item_nr() < get_child_count())
	{
		//musimy ukryæ item, poniewa¿ jego dzieci mog¹ mieæ transfery i inne zale¿ne od hidden-tree
		get_active_item()->on_activate(false);
		_get_header()->on_item_activate(get_prop_active_item_nr(),false);
	}
	
	m_nActiveItemNr = nActiveItemNr;
	
	if(get_prop_active_item_nr() >= 0 && get_prop_active_item_nr() < get_child_count())
	{
		//musimy pokazaæ item, poniewa¿ jego dzieci mog¹ mieæ transfery i inne zale¿ne od hidden-tree
		bFirstTime = !get_active_item()->get_already_activated();
		get_active_item()->on_activate(true);
		_get_header()->on_item_activate(get_prop_active_item_nr(),true);
	}

	_vse_dirty();

	return bFirstTime;
}

//-------------- attribute functions -------------------------
inline void cned_tabmanager::apply_attributes(const ned_currattributes & roCurrAttrib)
{
	cned_rect_container_::apply_attributes(roCurrAttrib);
	_get_header()->apply_attributes(roCurrAttrib);
}

//--------------- notications from item --------------------------- 
inline const ng_string & cned_tabmanager::get_item_title(ned_ident idTabItem)
{
	long nChildPosition = scan_for_child_pos(idTabItem);
	ASSERT(nChildPosition >= 0);
	return _get_header()->get_item_title(nChildPosition);
}

inline void cned_tabmanager::set_item_title(ned_ident idTabItem,const ng_string & roTitleString)
{
	long nChildPosition = scan_for_child_pos(idTabItem);
	ASSERT(nChildPosition >= 0);
	_get_header()->set_item_title(nChildPosition,roTitleString);
}

//-------------- fill clone -------------- -------------- -------
inline void cned_tabmanager::fill_clone(cned_element *)
{
	ASSERT(false);	//not supported - write implementation if you really need it
}

inline long cned_tabmanager::get_prop_tabs_in_row() const
{
	return _get_header()->get_prop_tabs_in_row();
}

inline void cned_tabmanager::set_prop_tabs_in_row(long nTabsInRow)
{
	_get_header()->set_prop_tabs_in_row(nTabsInRow);
}

inline void cned_tabmanager::on_child_size_info_dirty(ned_ident idChild)
{
	ASSERT(get_manager()->get_element_container_ident(idChild) == get_ident());
	_size_info_dirty();
}

}

#else
	#error __FILE__ already included
#endif
