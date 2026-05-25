/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_table / <table>
		tabelka
*/

#ifndef _TABLE_NED_H_
#define _TABLE_NED_H_

namespace ned
{
class cned_tablesection;

enum ened_tablesection_enum
{
	ned_tse_min				= 0,
	ned_tse_first_header	= ned_tse_min,
	ned_tse_body			= ned_tse_first_header + 1,
	ned_tse_last_footer		= ned_tse_body + 1,
	ned_tse_max				= ned_tse_last_footer,
	
	//'sekcje' wzorcowe, 'trzymane' poza struktur¹
	ned_tse_pattern			= ned_tse_max + 1,
	ned_tse_next_hdr		= ned_tse_pattern + 1,
	ned_tse_prev_ftr		= ned_tse_next_hdr + 1,
};

const long NED_TABLE_SECTION_COUNT = long(ned_tse_max - ned_tse_min + 1);

//-------- page breaking ---------------------------------
const long TBI_FIRSTCOL_MAX = 99999;
const long TBI_LASTCOL_MIN  = -1;

class cned_tablecell;

//-------- page breaking ---------------------------------

class cned_table : public cned_rect_container_
{
public:
	long get_col_count() const;

	virtual void insert_col_into_sections(long nCol);
	virtual void remove_children(bool bWhileRemovingItself);
	//------------------------------------------------
	virtual SCP<cned_element> create_section(ened_tablesection_enum eSection,const ned_ident idSection);
	void create_all_missing_sections();

	SCP<cned_tablesection> get_section(ened_tablesection_enum eSection) const;
	ned_ident _get_section_ident(ened_tablesection_enum eSection) const;

	SCP<cned_element> create_next_header(const ned_ident idSection);
	SCP<cned_element> create_prev_footer(const ned_ident idSection);

	SCP<cned_tablesection> get_next_header() const;
	SCP<cned_tablesection> get_prev_footer() const;
	ned_ident _get_next_header_ident() const;
	ned_ident _get_prev_footer_ident() const;

	//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
	//------------------------------------------------
	// table column
	//------------------------------------------------
	class column
	{
	public:
		column();
	
		ng_xdist get_actual_col_width() const;
		ng_xdist get_min_width() const;
		ng_xdist get_internal_min_width() const;
		ng_xdist get_right_side_space() const;
		ng_xdist get_prop_extwidth() const;

		long get_weight() const;

		void update_right_side_space(ng_xdist xWidth);

		void update_min_width(ng_xdist xWidth);
		void update_internal_min_width(ng_xdist xWidth);
		void update_weight(long nWeight);

		void set_prop_extwidth(ng_xdist xExtWidth);
		void set_actual_col_width(ng_xdist xColWidth);

		void normalize_right_side_space();

		void reset();

		void set_owns_cells();			//jakaœ komórka nale¿y do kolumny
		bool get_owns_cells() const;
		//-------- page breaking -----
		long get_split_area_left() const;
		long get_split_area_right() const;
		void set_split_areas(long xAreaLeft,long xAreaRight);
	private:
		ng_xdist	m_xActualWidth;		//aktualna szerokoœæ kolumny
		ng_xdist	m_xMinWidth;		//minimalna szerokoœæ kolumny
		ng_xdist	m_xInnerMinWidth;	//minimalna wewnêtrzna szerokoœæ kolumny (bez ramek)
		ng_xdist	m_xRightSideSpace;	//odstêp na prawo od kolumny
		ng_xdist	m_xExtDeclWidth;	//szerokoœæ zadeklarowana
		long		m_nWeight;			//"waga" elementu
		bool		m_bOwnsCells;		//czy jakaœ komórka nale¿y do kolumny
		//-------- page breaking ---------------------------------
		long		m_xSplitAreaLeft;	//x-nr kartki na której rozpoczyna siê ta kolumna
		long		m_xSplitAreaRight;	//x-nr kartki na której koñczy siê ta kolumna

		friend class cned_table;
	};
	
	column & get_column(long nColNr);
	const column & get_column(long nColNr) const;
//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);

	void update_left_side_space(ng_xdist xWidth);
	ng_xdist get_left_side_space() const;
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
	//--------------------------------------------------------
protected:
	cned_table(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	virtual void _initiate_allocations(bool bSkipNonPrintable);
	void _compress_columns();
	//------- section creation support ----------
	SCP<cned_element> _internal_create_section(ened_element_type eElementType,ened_tablesection_enum eSection,const ned_ident idSection);
	void _create_missing_sections(ened_tablesection_enum eSection);
	//-------------- rendering support -------------------
	virtual void _measure_columns(const ned_measure_param & roMParam,ng_ydist & ryMinTableHeight);

	void _compute_final_col_widths(ng_xdist dxAvailWidth,bool & rbResetAllRows,ng_xdist & rdxTotalWidth);


	ned_ident m_idSectionArray[ NED_TABLE_SECTION_COUNT ];
	
	//'pattern' sections
	ned_ident m_idNextHeader;
	ned_ident m_idPrevFooter;
	
	//-------------------------------------------------------
	CArray<column,column&>	m_oColArray;
	ng_xdist				m_xLeftSideSpace;	//odstêp na lewo od pierwszej kolumny
	
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline long cned_table::get_col_count() const
{
	return m_oColArray.GetSize();
}

//------------------------------------------------
// table column
//------------------------------------------------
inline cned_table::column::column() :
	m_xActualWidth(0)
{
	reset();
}

inline void cned_table::column::reset()
{
	m_xMinWidth		 = 0;
	m_xInnerMinWidth = 0;
	m_nWeight = 0;
	m_xRightSideSpace = MAXLONG;
	m_xExtDeclWidth = NED_AUTO_WIDTH;
	m_bOwnsCells	= false;


	m_xSplitAreaLeft = 0;
	m_xSplitAreaRight = 0;
}

inline ng_xdist cned_table::column::get_actual_col_width() const
{
	return m_xActualWidth;
}

inline void cned_table::column::set_actual_col_width(ng_xdist xColWidth)
{
	m_xActualWidth = xColWidth;
}

inline ng_xdist cned_table::column::get_min_width() const
{
	return m_xMinWidth;
}

inline ng_xdist cned_table::column::get_internal_min_width() const
{
	return m_xInnerMinWidth;
}

inline ng_xdist cned_table::column::get_right_side_space() const
{
	ASSERT(m_xRightSideSpace != MAXLONG);
	return m_xRightSideSpace;
}

inline long cned_table::column::get_weight() const
{
	return m_nWeight;
}

inline void cned_table::column::update_right_side_space(ng_xdist xWidth)
{
	m_xRightSideSpace = min(m_xRightSideSpace,xWidth);
}

inline void cned_table::column::update_min_width(ng_xdist xWidth)
{
	m_xMinWidth = max(m_xMinWidth,xWidth);
}

inline void cned_table::column::update_internal_min_width(ng_xdist xWidth)
{
	m_xInnerMinWidth = max(m_xInnerMinWidth,xWidth);
}

inline void cned_table::column::update_weight(long nWeight)
{
	m_nWeight += nWeight;
}


inline ng_xdist cned_table::column::get_prop_extwidth() const
{
	return m_xExtDeclWidth;
}

inline void cned_table::column::set_prop_extwidth(ng_xdist xExtWidth)
{
	m_xExtDeclWidth = xExtWidth;
}

inline void cned_table::column::normalize_right_side_space()
{
	if(m_xRightSideSpace == MAXLONG)
	{
		m_xRightSideSpace = 0;
	}
}

inline void cned_table::column::set_owns_cells()
{
	m_bOwnsCells = true;
}

inline bool cned_table::column::get_owns_cells() const
{
	return m_bOwnsCells;
}

//-------- page breaking -----
inline long cned_table::column::get_split_area_left() const
{
	return m_xSplitAreaLeft;
}

inline long cned_table::column::get_split_area_right() const
{
	return m_xSplitAreaRight;
}

inline void cned_table::column::set_split_areas(long xAreaLeft,long xAreaRight)
{
	m_xSplitAreaLeft = xAreaLeft;
	m_xSplitAreaRight = xAreaRight;
}

//--------------------------------------------------------------------
inline cned_table::column & cned_table::get_column(long nColNr)
{
	return m_oColArray[ nColNr ];
}

inline const cned_table::column & cned_table::get_column(long nColNr) const
{
	return m_oColArray[ nColNr ];
}

//--------------------------------------------------------------------
inline ned_ident cned_table::_get_section_ident(ened_tablesection_enum eSection) const
{
	ASSERT(eSection >= ned_tse_min && eSection <= ned_tse_max);
	return m_idSectionArray[ eSection ];
}

inline SCP<cned_tablesection> cned_table::get_section(ened_tablesection_enum eSection) const
{
	ned_ident idSection = _get_section_ident(eSection);
	ASSERT(NEDID_NOTHING != idSection);
	return scp_cast_ui<cned_tablesection>(get_element_on_ident(idSection));
}

inline void cned_table::create_all_missing_sections()
{
	if(_get_section_ident(ned_tse_max) == NEDID_NOTHING)
	{
		create_section(ned_tse_max,NEDID_NOTHING);
	}
}

//--------------------------------------------------------------------

inline SCP<cned_tablesection> cned_table::get_next_header() const
{
	ASSERT(_get_next_header_ident() != NEDID_NOTHING);
	return scp_cast_ui<cned_tablesection>(get_element_on_ident(_get_next_header_ident()));
}

inline SCP<cned_tablesection> cned_table::get_prev_footer() const
{
	ASSERT(_get_prev_footer_ident() != NEDID_NOTHING);
	return scp_cast_ui<cned_tablesection>(get_element_on_ident(_get_prev_footer_ident()));
}

inline ned_ident cned_table::_get_next_header_ident() const
{
	return m_idNextHeader;
}

inline ned_ident cned_table::_get_prev_footer_ident() const
{
	return m_idPrevFooter;
}

//--------------------------------------------------------------------

inline void cned_table::update_left_side_space(ng_xdist xWidth)
{
	m_xLeftSideSpace = min(m_xLeftSideSpace,xWidth);
}

inline ng_xdist cned_table::get_left_side_space() const
{
	ASSERT(MAXLONG != m_xLeftSideSpace);
	return m_xLeftSideSpace;
}

//--------- drawing ------------------
inline void cned_table::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_draw_foreground_children(roForePainter,oPaintPoint);
}

inline void cned_table::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oTableRect(oPaintPoint,m_oActualSize);

	_draw_std_background(roBackPainter,oTableRect);
	_draw_background_children(roBackPainter,oPaintPoint);

	_store_main_paint_rect(oTableRect);
}



}

#else
	#error __FILE__ already included
#endif
