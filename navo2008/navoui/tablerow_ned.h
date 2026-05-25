/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_tablerow / <tr>
		wiersz tabelki
*/

#ifndef _TABLEROW_NED_H_
#define _TABLEROW_NED_H_

namespace ned
{
class cned_tablesection;
class cned_table;

class cned_tablerow : public cned_container
{
public:
	virtual void set_prop_hidden(bool bHidden);
	//-------- specific cell notifications ----------------
	void on_cell_colspan_change();
	void on_cell_rowspan_change();
	void on_cell_show_hide();

	//--------------- allocation row binding ------------------
	long get_alloc_row_nr() const;
	void set_alloc_row_nr(long nAllocRowNr,bool bAllocated);
	bool has_alloc_row_nr() const;

	//------------- child management ----------
	virtual void remove_children(bool bWhileRemovingItself);

	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident nChildIdent);
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);
//--------- drawing ------------------
	virtual ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const;
	virtual void _invalidate_all_paint();
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

	void mark_all_rendered();

protected:
	//----- structure helpers -----------
	SCP<cned_tablesection> _get_section() const;
	SCP<cned_table> _get_table() const;

	cned_tablerow(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

private:
	long	m_nAllocRowPseudoNr;			//pseudo nr of alloc row (use only access functions)

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_tablerow::cned_tablerow(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis):
	cned_container(poManager,eType,idThis),
	m_nAllocRowPseudoNr(-2)	//end-marker 
{
#ifdef _DEBUG
	{
		set_alloc_row_nr(-1,false);
		ASSERT(m_nAllocRowPseudoNr == -2); //ensure end-marker consistency
	}
#endif
}

inline void cned_tablerow::set_prop_hidden(bool bHidden)
{
	if(get_prop_hidden() == bHidden)
	{
		return;
	}
	cned_container::set_prop_hidden(bHidden);
	_get_section()->on_row_show_hide(get_ident());
}

//--------------------------------------------------------------------
//----- structure helpers -----------
inline SCP<cned_tablesection> cned_tablerow::_get_section() const
{
	return scp_cast_ui<cned_tablesection>(get_container());
}

inline SCP<cned_table> cned_tablerow::_get_table() const
{
	return scp_cast_ui<cned_table>(get_container()->get_container());
}

//------------- child management ----------
inline void cned_tablerow::remove_children(bool bWhileRemovingItself)
{
	cned_container::remove_children(bWhileRemovingItself);
	_get_section()->on_cell_set_change(get_ident());
}

inline void cned_tablerow::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	if(rpoChildSP->get_container_ident() == get_ident())
	{
		_get_section()->on_cell_set_change(get_ident());
	}
	cned_container::on_child_inserted(rpoChildSP);
}

inline void cned_tablerow::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		_get_section()->on_cell_set_change(get_ident());
	}
	cned_container::on_child_removing(idChild);
}

//--------------------------------------------------------------------
inline void cned_tablerow::on_cell_colspan_change()
{
	 _get_section()->on_cell_colspan_change(get_ident());
}

inline void cned_tablerow::on_cell_rowspan_change()
{
	 _get_section()->on_cell_rowspan_change(get_ident());
}

inline void cned_tablerow::on_cell_show_hide()
{
	_get_section()->on_cell_show_hide(get_ident());
}

//--------------- allocation row binding ------------------
inline long cned_tablerow::get_alloc_row_nr() const
{
	return (m_nAllocRowPseudoNr / 2);
}

inline bool cned_tablerow::has_alloc_row_nr() const
{
	return (m_nAllocRowPseudoNr & 1);
}

inline void cned_tablerow::set_alloc_row_nr(long nAllocRowNr,bool bAllocated)
{
	m_nAllocRowPseudoNr = nAllocRowNr + nAllocRowNr;
	if(bAllocated)
	{
		m_nAllocRowPseudoNr++;
	}
}

inline void cned_tablerow::set_fixed_properties()
{
	cned_container::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_ignore_sys_disable(true);
}

inline void cned_tablerow::mark_all_rendered()
{
	_validate_last_measured(NEDID_LAST);
}

//--------------------- formalizm --------------------------------------------
inline void cned_tablerow::get_children_metrics(const ned_measure_param &)
{
	ASSERT(false);	//shouldnt be called
}

inline ened_spr cned_tablerow::should_paint(const cned_painter_ &,const ng_point &) const
{
	ASSERT(false); //shouldn't be called
	return spr_inside;
}

inline void cned_tablerow::post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint)
{
	roPostRender.test_element_remove(get_ident());

	_post_render_children(roPostRender,roCurrentPoint);
}

inline void cned_tablerow::_invalidate_all_paint()
{
	//invaliduj wszystkie komórki
	cned_filter_children oFilterChildren(this,true,false);
	
	while(!oFilterChildren.is_end())
	{
		oFilterChildren.get_element()->_invalidate_all_paint();
		oFilterChildren.move_next();
	}

	//a oprócz tego sam siebie
	get_manager()->invalidate_paint_rect(get_ident(),MAIN_PAINT_RECT_ID);
}


inline bool cned_tablerow::is_inside_hit_area(const ng_point &) const
{
	ASSERT(false);
	return false;
}

inline bool cned_tablerow::quote_distance(eRelativePosition,const ng_rect &,long &)
{
	return true; //always check cells
}

inline void cned_tablerow::get_bounding_rect(long /*nElementPart*/,ng_rect &) const
{
	ASSERT(false);	//shoud not be called (current usage is only find element relative)
}

}




#else
	#error __FILE__ already included
#endif
