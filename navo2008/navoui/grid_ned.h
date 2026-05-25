/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_grid / <grid>
		tabelka edycyjna
*/

#ifndef _GRID_NED_H_
#define _GRID_NED_H_

namespace ned
{

class cned_grid : public cned_table
{
public:
	virtual SCP<cned_element> create_section(ened_tablesection_enum eSection,const ned_ident idSection);
	virtual void insert_col_into_sections(long nCol);
	virtual void _initiate_allocations(bool bSkipNonPrintable);
	virtual void _measure_columns(const ned_measure_param & roMParam,ng_ydist & ryMinTableHeight);

	ned_ident get_pattern_section_ident();
	SCP<cned_tablesection> get_pattern_section();

//--------------event handlers ---------------------------------------
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
private:
	cned_grid(cned_element_manager * poManager,const ned_ident idThis);

	ned_ident m_idPatternSection;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_grid::cned_grid(cned_element_manager * poManager,const ned_ident idThis) :
	cned_table(poManager,ned_grid,idThis),
	m_idPatternSection(NEDID_NOTHING)
{
}

inline ned_ident cned_grid::get_pattern_section_ident()
{
	return m_idPatternSection;
}

inline SCP<cned_tablesection> cned_grid::get_pattern_section()
{
	ASSERT(get_pattern_section_ident() != NEDID_NOTHING);

	return scp_cast_ui<cned_tablesection>(get_element_on_ident(get_pattern_section_ident()));
}

inline void cned_grid::insert_col_into_sections(long nCol)
{
	cned_table::insert_col_into_sections(nCol);

	if(get_pattern_section_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_pattern_section()->external_insert_col(nCol);
	}
}

inline void cned_grid::_initiate_allocations(bool bSkipNonPrintable)
{
	cned_table::_initiate_allocations(bSkipNonPrintable);

	if(get_pattern_section_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_pattern_section()->_initiate_allocations(bSkipNonPrintable);
	}
}


}

#else
	#error __FILE__ already included
#endif
