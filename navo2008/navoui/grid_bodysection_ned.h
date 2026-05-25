/*
	NAVO Enterprise 2003
	2003-04-04

	navo enhanced display (NED)

	ned_spreadbodysection / <tbody> 
		sekcja body grida
*/
#ifndef _GRID_BODY_SECTION_NED_H_
#define _GRID_BODY_SECTION_NED_H_

namespace ned
{
class cned_grid;
class cned_pattern_tablerow;

class cned_grid_bodysection : public cned_table_bodysection
{
public:
	long get_pattern_row_count();
	SCP<cned_pattern_tablerow> get_pattern_row(long nInternalRow);

	//---------- datarow nr <-> table row nr translation --------------
	long datarow_nr_from_table_row_nr(long nTableRowInternalNr);
	long table_row_nr_from_datarow_nr(long nDataRowInternalNr);

//------ property GET -----------------
	long get_prop_min_visible_datarows() const;
	long get_prop_max_visible_datarows() const;
	long get_prop_first_visible_datarow() const;
	long get_prop_total_datarows() const;
//------ property SET -----------------
	void set_prop_min_visible_datarows(long nMinDataRows);
	void set_prop_max_visible_datarows(long nMaxDataRows);
	void set_prop_first_visible_datarow(long nFirstVisible);
	void set_prop_total_datarows(long nTotalDataRows);

	//------------- child management ----------
	virtual SCP <cned_element> insert_new_element(ened_element_type eType,const ned_ident idNew,const ned_ident idAfter);
	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);

	virtual ng_ydist _correct_rendered_section_height(cned_renderer_ & roRenderer,ng_ydist yHeight);

	ned_ident find_row_from_screen_point(const ng_point & roArenaPoint);

//--------------event handlers ---------------------------------------
	virtual void process_event_keydown(ned_path_to_element & roCallStack,const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
private:
	bool _update_working_rows_count();	//aktualizuj liczbê wyœwietlanych wierszy

	void _build_in_on_event_keydown(long nTableRowNr,const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	void _supply_datarownr_property(cned_tablerow * poTableRow,ned_action_result & roResult);

	cned_grid_bodysection(cned_element_manager * poManager,const ned_ident idThis);

	SCP<cned_grid> _get_grid();

	//------- properties ----
	long	m_nMinVisibleDataRows;		//minimalna liczba wyœwietlanych wierszy >= 1 (wiersze danych)
	long	m_nMaxVisibleDataRows;		//maksymalna liczba wyœwietlanych wierszy >= min vis rows (wiersze danych)

	//-------- dynamic values -----
	long	m_nFirstVisibleDataRow;		//pierwszy widoczny (wiersz danych)
	long	m_nTotalDataRows;			//ca³kowita liczba wierszy (wiersze danych)

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// special section - grid pattern
//--------------------------------------------------------------------
class cned_grid_patternsection : public cned_tablesection
{
protected:
	//--------------------------------------------------------------
	virtual const ened_element_type get_new_row_type() const;
private:
	cned_grid_patternsection(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline cned_grid_bodysection::cned_grid_bodysection(cned_element_manager * poManager,const ned_ident idThis) :
	cned_table_bodysection(poManager,ned_spreadbodysection,idThis),
	m_nMinVisibleDataRows(1),
	m_nMaxVisibleDataRows(12),
	m_nFirstVisibleDataRow(0),
	m_nTotalDataRows(-1)
{
}

inline SCP<cned_grid> cned_grid_bodysection::_get_grid()
{
	return scp_cast_ui<cned_grid>(get_container());
}

inline long cned_grid_bodysection::get_pattern_row_count()
{
	return _get_grid()->get_pattern_section()->get_child_count();
}

inline SCP<cned_pattern_tablerow> cned_grid_bodysection::get_pattern_row(long nInternalRow)
{
	return scp_cast_ui<cned_pattern_tablerow>(_get_grid()->get_pattern_section()->get_row(nInternalRow));
}

//------ property GET -----------------
inline long cned_grid_bodysection::get_prop_min_visible_datarows() const
{
	return m_nMinVisibleDataRows;
}

inline long cned_grid_bodysection::get_prop_max_visible_datarows() const
{
	return m_nMaxVisibleDataRows;
}
	
inline long cned_grid_bodysection::get_prop_first_visible_datarow() const
{
	return m_nFirstVisibleDataRow;
}

inline long cned_grid_bodysection::get_prop_total_datarows() const
{
	return m_nTotalDataRows;
}
//------ property SET -----------------
inline void cned_grid_bodysection::set_prop_min_visible_datarows(long nMinDataRows)
{
	ASSERT(nMinDataRows >= 1);
	if(get_prop_min_visible_datarows() == nMinDataRows)
	{
		return;
	}
	m_nMinVisibleDataRows = nMinDataRows;

	if(_update_working_rows_count())
	{
		_size_info_dirty();
	}
	_vse_dirty();
}

inline void cned_grid_bodysection::set_prop_max_visible_datarows(long nMaxDataRows)
{
	ASSERT(nMaxDataRows >= get_prop_min_visible_datarows());
	if(get_prop_max_visible_datarows() == nMaxDataRows)
	{
		return;
	}
	m_nMaxVisibleDataRows = nMaxDataRows;

	if(_update_working_rows_count())
	{
		_size_info_dirty();
	}
	_vse_dirty();
}

inline void cned_grid_bodysection::set_prop_first_visible_datarow(long nFirstVisible)
{
	ASSERT(nFirstVisible >= 0 && nFirstVisible <= get_prop_total_datarows());

	if(get_prop_first_visible_datarow() == nFirstVisible)
	{
		return;
	}
	
	m_nFirstVisibleDataRow = nFirstVisible;
	//ned_to_do: sprawdziæ czy to wszystko, czy coœ jeszcze

	if(_update_working_rows_count())
	{
		_size_info_dirty();
	}
	_vse_dirty();
}

inline void cned_grid_bodysection::set_prop_total_datarows(long nTotalDataRows)
{
	ASSERT(nTotalDataRows >= 0);
	if(get_prop_total_datarows() == nTotalDataRows)
	{
		return;
	}
	
	m_nTotalDataRows = nTotalDataRows;
	m_nFirstVisibleDataRow = min(m_nFirstVisibleDataRow,m_nTotalDataRows);

	if(_update_working_rows_count())
	{
		_size_info_dirty();
	}
	_vse_dirty();
}

//---------- datarow nr <-> table row nr translation --------------
inline long cned_grid_bodysection::datarow_nr_from_table_row_nr(long nTableRowInternalNr)
{
	long nPatternRowCount = get_pattern_row_count();
	ASSERT(nPatternRowCount > 0);
	long nDataRowNr = get_prop_first_visible_datarow() + nTableRowInternalNr / nPatternRowCount;
	return nDataRowNr;
}

inline long cned_grid_bodysection::table_row_nr_from_datarow_nr(long nDataRowInternalNr)
{
	return (nDataRowInternalNr - get_prop_first_visible_datarow()) * get_pattern_row_count();
}

//--------------------------------------------------------------------
// special section - grid pattern
//--------------------------------------------------------------------
inline cned_grid_patternsection::cned_grid_patternsection(cned_element_manager * poManager,const ned_ident idThis):
	cned_tablesection(poManager,ned_spreadpatternsection,idThis)
{
}

//--------------------------------------------------------------
inline const ened_element_type cned_grid_patternsection::get_new_row_type() const
{
	return ned_patterntablerow;
}


}

#else
	#error __FILE__ already included
#endif

