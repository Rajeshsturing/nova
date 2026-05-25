/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_tablesection / <thead> <tbody> <tfoot>
		sekcja tabelki
*/


#ifndef _TABLESECTION_NED_H_
#define _TABLESECTION_NED_H_

namespace ned
{
class cned_table;
class cned_tablerow;
class cned_tablecell;

//-------------------------------------------------------------------
//long containing cell_encoded_ident has format:
//
//(idCell << 2) | (cell_type bits)

//0 - span cell
//1 - left top corner
//2 - right bottom corner
//3 - both left top and right bottom corner = cell with colspan=1 and rowspan = 1
//(encoded_ident & 0xfffffffc) >> 2 = idCell (ned_ident)

//empty cell is long(0) - not bits 

const DWORD CELL_TYPE_SPAN		= 0;		//just to simplify coding
const DWORD CELL_TYPE_LT		= 1;		//row owned cell, root - left top corner
const DWORD CELL_TYPE_RB		= 2;		//row owned cell, root - right bottom corner (may be _LT too!)

DWORD cell_type_from_encoded(DWORD nEncodedIdent);
ned_ident cell_ident_from_encoded(DWORD nEncodedIdent);
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//  elementy szybkiego indeksu wierszy
//-------------------------------------------------------------------
class ctable_row_leaf_block;

class ctable_row_leaf : public treearray::cleaf<ned_ident>
{
public:
	ctable_row_leaf(ctable_row_leaf_block * poParent,ned_ident idElement);
	ng_ydist get_height() const;
	void set_height(ng_ydist yHeight);
#ifdef _DEBUG
	virtual void print_leaf(long nIndent);
#endif
private:
	ng_ydist m_yHeight;
};

class ctable_row_leaf_block : public treearray::cleaf_block<ned_ident>
{
public:
	ctable_row_leaf_block(treearray::cnode_block<ned_ident> * poParent);
	void update_height(ng_ydist yElementHeight);
	ng_ydist get_height() const;
	ng_ydist get_height_up_to(treearray::cleaf<ned_ident> * poLeaf);
	ctable_row_leaf * lookup_entry_on_height(ng_ydist & ryHeight);

	virtual void on_block_split(treearray::cleaf_block<ned_ident> * poDestLeafBlock,
		SCP< treearray::cleaf<ned_ident> > & rpoMoveLeafSP);
private:
	virtual SCP<treearray::cleaf<ned_ident> > __create_leaf(const ned_ident & roValue);
	ng_ydist m_yHeight;
};

class ctable_row_node_block : public treearray::cnode_block<ned_ident>
{
public:
	ctable_row_node_block(treearray::cnode_block<ned_ident> * poParent);
	void update_height(ng_ydist yElementHeight);
	ng_ydist get_height() const;
	ng_ydist get_height_up_to(SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoLeafBlockSP);
	ctable_row_leaf * lookup_entry_on_height(ng_ydist & ryHeight);

	virtual void on_block_split(treearray::cnode_block<ned_ident> * poDestLeafBlock,
		SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoMoveBlockSP);
	virtual void on_root_promote(SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoOldRootSP);

private:
	ng_ydist m_yHeight;
};

class cindexed_table_row_array : public treearray::cindexed_tree_array<ned_ident,ned_ident>
{
public:
	virtual SCP<treearray::cleaf_block<ned_ident> > __create_leaf_block(treearray::cnode_block<ned_ident> * poParent);
	virtual SCP<treearray::cnode_block<ned_ident> > __create_node_block(treearray::cnode_block<ned_ident> * poParent);
	
	virtual void _remove_leaf(SCP<treearray::cleaf<ned_ident> > poLeafSP,long nIndex);

	void update_height(ned_ident idRow,ng_ydist yHeight);
	ng_ydist get_row_top(ned_ident idRow);
	ned_ident get_row_for_y(ng_ydist yCoord);
private:
	void _update_height(SCP<treearray::cleaf<ned_ident> > poLeafSP,ng_ydist yHeight);
};

//-------------------------------------------------------------------


class cned_tablesection : public cned_rect_container_
{
public:
	long get_col_count() const;

	long get_row_nr(ned_ident idRow);
	ned_ident get_row_ident(long nTblRowNr);
	SCP<cned_tablerow> get_row(long nTblRowNr);

	SCP<cned_table> _get_table() const;
	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
	//------------------ notifications (invalidating allocations) ---------------------
	void on_cell_colspan_change(ned_ident idRow);
	void on_cell_rowspan_change(ned_ident idRow);
	void on_cell_set_change(ned_ident idRow);
	void on_cell_show_hide(ned_ident idRow);
	void on_row_show_hide(ned_ident idRow);


	//common border space - above 1-st row
	void update_top_side_space(ng_ydist yHeight);
	ng_ydist get_top_side_space() const;
	void get_cell_common_border_space(cned_tablecell * poTableCell,long nAllocRowNr,long nColNr,ng_rect & roSpaceRect) const;
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);

	void init_measure_columns();
		void measure_column(const ned_measure_param & roMParam,long nInternalCol,ng_ydist & ryMinHeight);
	void finish_measure_columns();
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);

	//------------- child management ----------
	virtual void remove_children(bool bWhileRemovingItself);

	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
	virtual void on_child_removing(ned_ident nChildIdent);
	virtual void on_child_size_info_dirty(ned_ident idChild);		//dziecko siê zmieni³o

	void external_insert_col(long nCol);		//wstawia kolumnê na ¿¹danie cnui_table
	//-------------------------------------- 
	void _initiate_allocations(bool bSkipNonPrintable);
	//--------------------------------------------------------------
	virtual const ened_element_type get_new_row_type() const;
protected:
	cned_tablesection(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	//--------------------------------------------------------------
	// przydzia³ komórek w przestrzenid 2D ("2D grid allocations")
	//-------------------------------------------------------------------
	// wiersz alokacji tabelki - zawiera 1 lub wiêcej "komórek"
	// wszystkie komórki s¹ widoczne i nale¿¹ do widocznych wierszy <tr>
	// 
	// to nie jest wiersz ze struktury drzewa XML (<tr>) !!
	// obiekt zawiera tylko info o alokacjach komórek - reszta jest w <tr>
	//-------------------------------------------------------------------
	class alloc_row : public CInterface__
	{
	public:
		alloc_row(long nColCount = 0);

		void clean();

		void insert_col(long nCol);
		long get_col_count() const;

		void mark_has_aliens();
		bool has_aliens() const;
		
		DWORD get_cell_encoded(long nCol) const;
		void set_cell_encoded(long nCol,ned_ident Ident,long nType);
		
		void assign_row_ident(ned_ident idRow);
		ned_ident get_table_row_ident() const;

		//------- common bottom space ------------
		void update_bottom_side_space(ng_ydist yHeight);
		ng_ydist get_bottom_side_space() const;
		void reset_bottom_side_space();
		void normalize_bottom_side_space();

		//------- row height -------------
		void set_row_height(ng_ydist yHeight);
		ng_ydist get_row_height() const;
		
		ened_spr should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint,ng_xdist dxSectionWidth) const;
	private:

		CArray<ned_ident,ned_ident>		m_idCellArray;	//kodowane id komórek
		ned_ident						m_idTableRow;	//identyfikator wiersza <tr>
		bool m_bHasAliens;								//czy wiersz zawiera komórki z poprzednich wierszy

		ng_ydist	m_yBottomSideSpace;					//dolna, wspólna czêœæ ramki
		ng_ydist	m_yRowHeight;						//wysokoœæ tego wiersza
	};

	void _invalidate_row_with_alloc_ident(ned_ident idRow);
	void _invalidate_row_with_alloc_nr(long nTblRowNr);		//zmienia zakres wierszy <tr> które maj¹ znacz¹cy alloc

	//--------- drawing ------------------
	void _draw_foreground_alloc_row(cned_fore_painter & roForePainter,const long nAllocRowNr,const ng_point & roCurrentPoint);
	void _draw_background_alloc_row(cned_back_painter & roBackPainter,const long nAllocRowNr,const ng_point & roCurrentPoint);
	//-------------- rendering support -------------------
	void _update_allocations(long nRowNr,bool bSkipNonPrintable);
	SCP<cned_tablecell> _get_cell_for_rendering(long nAllocRowNr,long nColNr) const;
	ng_ydist _measure_cell(const ned_measure_param & roMParam,SCP<cned_tablecell> & rpoTableCellSP,
		long nAllocRowNr,long nColNr,cned_table::column & roColumn);

	void _update_cell_common_border_space(SCP<cned_tablecell> poTableCellSP,long nAllocRowNr,long nColNr);

	ng_ydist _render_alloc_row(cned_renderer_ & roRenderer,const long nAllocRowNr,ng_ycoord yTop);
	ng_ydist _render_cell(cned_renderer_ & roRenderer,SCP<cned_tablecell> & rpoTableCellSP,
		const long nAllocRowNr,const long nColNr,const ng_point & roTopLeftPoint,ng_xdist dxWidth);

	//-------- alloc row helpers --------
	void internal_insert_col(long nCol);
	void _add_alloc_row();
	long _find_free_cell(long nRowNr,long nStartCol);
	void _alloc_block(ned_ident idCell,long nRowNr,long nColNr,long nColSpan,long nRowSpan);
	//------------------------------------

	long get_alloc_row_count() const;	//liczba wierszy w element storage
	alloc_row * _get_alloc_row(long nAllocRowNr);
	const alloc_row * _get_alloc_row(long nAllocRowNr) const;

	virtual ng_ydist _correct_rendered_section_height(cned_renderer_ & roRenderer,ng_ydist yHeight);

#ifdef _DEBUG
	void dump_cells();
#endif


	cindexed_table_row_array				   m_oRowIndex;
	CArray< SCP<alloc_row>, SCP<alloc_row> & > m_oAllocRowArray;
	long m_nLastRowWithAlloc;	//Last Table Row Nr With Valid Alloc
								//numer ostatniego wiersza <tr>, dla którego alokacja jest prawid³owa 
								//(wartoœæ get_alloc_row_nr() jest znacz¹ca)
	ng_ydist	m_yTopSideSpace;		//odstêp powy¿ej 1-szego wiersza

	friend class cned_element_manager;

	friend class cned_tablerow;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//			alloc_row
//--------------------------------------------------------------------
inline cned_tablesection::alloc_row::alloc_row(long nColCount) :
	m_idTableRow(NEDID_NOTHING),
	m_bHasAliens(false),
	m_yRowHeight(0),
	m_yBottomSideSpace(MAXLONG)
{
	m_idCellArray.SetSize(nColCount);
}

inline void cned_tablesection::alloc_row::insert_col(long nCol)
{
	m_idCellArray.InsertAt(nCol,ned_ident(0));
}

inline long cned_tablesection::alloc_row::get_col_count() const
{
	return m_idCellArray.GetSize();
}

inline bool cned_tablesection::alloc_row::has_aliens() const
{
	return m_bHasAliens;
}

inline void cned_tablesection::alloc_row::mark_has_aliens()
{
	m_bHasAliens = true;
}

inline void cned_tablesection::alloc_row::clean()
{
	//free cells setting its id to 0
	memset(m_idCellArray.GetData(),0,m_idCellArray.GetSize() * sizeof(ned_ident));
	
	m_idTableRow = NEDID_NOTHING;
	m_bHasAliens = false;
}

inline DWORD cned_tablesection::alloc_row::get_cell_encoded(long nCol) const
{
	return m_idCellArray[nCol];
}

inline void cned_tablesection::alloc_row::set_cell_encoded(long nCol,ned_ident Ident,long nType)
{
	ASSERT(ned_ident(0) != Ident);
	ASSERT((DWORD(nType) & (CELL_TYPE_LT | CELL_TYPE_RB)) == DWORD(nType));

	m_idCellArray[nCol] = ((((DWORD)Ident) << 2) | ((DWORD)nType));
}

inline void cned_tablesection::alloc_row::assign_row_ident(ned_ident idRow)
{
	ASSERT(m_idTableRow == NEDID_NOTHING || m_idTableRow == idRow);
	m_idTableRow = idRow;
}

inline ned_ident cned_tablesection::alloc_row::get_table_row_ident() const
{
	return m_idTableRow;
}


//----- common border, bottom space ---------------------------
inline void cned_tablesection::alloc_row::update_bottom_side_space(ng_ydist yHeight)
{
	m_yBottomSideSpace = min(m_yBottomSideSpace,yHeight);
}

inline ng_ydist cned_tablesection::alloc_row::get_bottom_side_space() const
{
	ASSERT(m_yBottomSideSpace != MAXLONG);
	return m_yBottomSideSpace;
}

inline void cned_tablesection::alloc_row::reset_bottom_side_space()
{
	m_yBottomSideSpace = MAXLONG;
}

inline void cned_tablesection::alloc_row::normalize_bottom_side_space()
{
	if(m_yBottomSideSpace == MAXLONG)
	{
		m_yBottomSideSpace = 0;
	}
}

//----------------- row dimesion informations -----------------

inline ng_ydist cned_tablesection::alloc_row::get_row_height() const
{
	return m_yRowHeight;
}

inline void cned_tablesection::alloc_row::set_row_height(ng_ydist yHeight)
{
	m_yRowHeight = yHeight;
}

inline ened_spr cned_tablesection::alloc_row::should_paint(const cned_painter_ & roPainter,const ng_point & roInsidePoint,ng_xdist dxSectionWidth) const
{
	ng_rect oTestRect(roInsidePoint,ng_size(dxSectionWidth, get_row_height() + get_bottom_side_space()));
	if(oTestRect.get_top() > roPainter.paint_bottom())
	{
		return spr_below;
	}
	else
	{
		if(oTestRect.get_bottom() < roPainter.paint_top())
		{
			return spr_above;
		}
		else
		{
			return roPainter.in_clip_region(oTestRect) ? spr_inside : spr_other;
		}
	}
}

//------------ cell encoders ----------------------

inline DWORD cell_type_from_encoded(DWORD nEncodedIdent)
{
	return (DWORD(nEncodedIdent) & 0x00000003);
}

inline ned_ident cell_ident_from_encoded(DWORD nEncodedIdent)
{
	return ((DWORD(nEncodedIdent) & 0xfffffffc) >> 2);
}

//--------------------------------------------------------------------
//-------- alloc row helpers --------
//--------------------------------------------------------------------------------
inline cned_tablesection::alloc_row * cned_tablesection::_get_alloc_row(long nAllocRowNr)
{
	ASSERT(m_oAllocRowArray[ nAllocRowNr ] != NULL);

	return m_oAllocRowArray[ nAllocRowNr ];
}

inline const cned_tablesection::alloc_row * cned_tablesection::_get_alloc_row(long nAllocRowNr) const
{
	ASSERT(m_oAllocRowArray[ nAllocRowNr ] != NULL);

	return m_oAllocRowArray[ nAllocRowNr ];
}

inline void cned_tablesection::external_insert_col(long nCol)
{
	for(long iter = 0; iter < m_oAllocRowArray.GetSize(); iter++)
	{
		_get_alloc_row(iter)->insert_col(nCol);
	}
}

inline void cned_tablesection::internal_insert_col(long nCol)
{
	_get_table()->insert_col_into_sections(nCol);
}

inline void cned_tablesection::_add_alloc_row()
{
	SCP<alloc_row> poAllocRowSP = NewSCP(new alloc_row(get_col_count()));
	m_oAllocRowArray.Add(poAllocRowSP);
}

inline long cned_tablesection::_find_free_cell(long nAllocRowNr,long nStartCol)
{
	alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
	long nColCount = get_col_count();
	for(long iC = nStartCol; iC < nColCount; iC++)
	{
		if(poAllocRow->get_cell_encoded(iC) == 0)
		{
			return iC;
		}
	}
	return nColCount;
}

//--------------------------------------------------------------------
inline SCP<cned_table> cned_tablesection::_get_table() const
{
	return scp_cast_ui<cned_table>(get_container());
}

inline long cned_tablesection::get_col_count() const
{
#ifdef _DEBUG
	{
		if(get_alloc_row_count() > 0)
		{
			ASSERT(_get_alloc_row(0)->get_col_count() == _get_table()->get_col_count());
		}
	}
#endif
	return _get_table()->get_col_count();
}

inline long cned_tablesection::get_alloc_row_count() const
{
	return m_oAllocRowArray.GetSize();
}

inline long cned_tablesection::get_row_nr(ned_ident idRow)
{
	return m_oRowIndex.get_position(idRow);
}

inline ned_ident cned_tablesection::get_row_ident(long nTblRowNr)
{
	return m_oRowIndex.get_at(nTblRowNr);
}

inline SCP<cned_tablerow> cned_tablesection::get_row(long nTblRowNr)
{
	ned_ident idRow = get_row_ident(nTblRowNr);
	ASSERT(idRow != NEDID_NOTHING);
	
	return scp_cast_ui<cned_tablerow>(get_element_on_ident(idRow));
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
inline cned_tablesection::cned_tablesection(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_container_(poManager,eType,idThis),
	m_nLastRowWithAlloc(-1),
	m_yTopSideSpace(MAXLONG)
{
}


//----------------------------- various notifications -----------------
//---------- all resulting in alloc change ----------------------------

inline void cned_tablesection::on_cell_colspan_change(ned_ident idRow)
{
	_invalidate_row_with_alloc_ident(idRow);
}

inline void cned_tablesection::on_cell_rowspan_change(ned_ident idRow)
{
	_invalidate_row_with_alloc_ident(idRow);
}

inline void cned_tablesection::on_cell_set_change(ned_ident idRow)
{
	_invalidate_row_with_alloc_ident(idRow);
}

inline void cned_tablesection::on_cell_show_hide(ned_ident idRow)
{
	_invalidate_row_with_alloc_ident(idRow);
}

inline void cned_tablesection::on_row_show_hide(ned_ident idRow)
{
	_invalidate_row_with_alloc_ident(idRow);
}

inline void cned_tablesection::_invalidate_row_with_alloc_nr(long nTblRowNr)
{
	ASSERT(nTblRowNr >= 0 && nTblRowNr <= get_child_count());
	m_nLastRowWithAlloc = min(m_nLastRowWithAlloc,nTblRowNr - 1);

	ASSERT(m_nLastRowWithAlloc >= -1);
}


inline void cned_tablesection::_invalidate_row_with_alloc_ident(ned_ident idRow)
{
	if(m_nLastRowWithAlloc >= 0)
	{
		long nTblRowNr = m_oRowIndex.get_position(idRow);
		_invalidate_row_with_alloc_nr(nTblRowNr);
	
		ASSERT(m_nLastRowWithAlloc < nTblRowNr);
	}
}

inline void cned_tablesection::_initiate_allocations(bool bSkipNonPrintable)
{
	_update_allocations(0,bSkipNonPrintable);
}

//--------------------------------------------------------------------------------
//-------------- rendering support -----------------------------------------------
inline void cned_tablesection::init_measure_columns()
{
	//resetuj upper acommon space
	m_yTopSideSpace = MAXLONG;
}

inline SCP<cned_tablecell> cned_tablesection::_get_cell_for_rendering(long nAllocRowNr,long nColNr) const
{
	//analizuj komórki tylko w momencie ich prawego-dolnego rogu w allocation
	//pomijaj te¿ dziury

	DWORD idCellEncoded = _get_alloc_row(nAllocRowNr)->get_cell_encoded(nColNr);

	if(cell_type_from_encoded(idCellEncoded) & CELL_TYPE_RB)
	{
		ned_ident idCell = cell_ident_from_encoded(idCellEncoded);
		
		//_update_allocations wycina ukryte
		ASSERT(!get_manager()->is_element_hidden(idCell));
		ASSERT(!get_manager()->is_element_in_hidden_tree(idCell));

		SCP<cned_tablecell> poTableCellSP = scp_cast_ui<cned_tablecell>(get_element_on_ident(idCell));
		ASSERT(poTableCellSP.PointsObject());
		return poTableCellSP;
	}

	return SCP<cned_tablecell>();
}

inline void cned_tablesection::update_top_side_space(ng_ydist yHeight)
{
	m_yTopSideSpace = min(m_yTopSideSpace,yHeight);
}

inline ng_ydist cned_tablesection::get_top_side_space() const
{
	ASSERT(m_yTopSideSpace != MAXLONG);
	return m_yTopSideSpace;
}

inline ng_ydist cned_tablesection::_correct_rendered_section_height(cned_renderer_ &,ng_ydist yHeight)
{
	return _get_std_height_for_rendering(yHeight);
}

//-------------- attribute functions -------------------------
inline void cned_tablesection::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_ignore_sys_disable(true);
}

//------------ cindexed_table_row_array ------------------------------------
inline SCP<treearray::cleaf_block<ned_ident> > cindexed_table_row_array::__create_leaf_block(treearray::cnode_block<ned_ident> * poParent)
{
	return NewSCP<treearray::cleaf_block<ned_ident> >(new ctable_row_leaf_block(poParent));
}

inline SCP<treearray::cnode_block<ned_ident> > cindexed_table_row_array::__create_node_block(treearray::cnode_block<ned_ident> * poParent)
{
	return NewSCP<treearray::cnode_block<ned_ident> >(new ctable_row_node_block(poParent));
}

inline SCP<treearray::cleaf<ned_ident> > ctable_row_leaf_block::__create_leaf(const ned_ident & ridRow)
{
	return NewSCP<treearray::cleaf<ned_ident> >(new ctable_row_leaf(this,ridRow));
}

inline void cindexed_table_row_array::_remove_leaf(SCP<treearray::cleaf<ned_ident> > poLeafSP,long nIndex)
{
	_update_height(poLeafSP,0);

	__real_remove_leaf(poLeafSP,nIndex);
}

//------------ ctors --------------------------------
inline ctable_row_leaf::ctable_row_leaf(ctable_row_leaf_block * poParent,ned_ident idElement) :
	treearray::cleaf<ned_ident>(poParent,idElement),
	m_yHeight(0)
{
}

inline ctable_row_leaf_block::ctable_row_leaf_block(treearray::cnode_block<ned_ident> * poParent) :
	treearray::cleaf_block<ned_ident>(poParent),
	m_yHeight(0)
{
}

inline ctable_row_node_block::ctable_row_node_block(treearray::cnode_block<ned_ident> * poParent) :
	treearray::cnode_block<ned_ident>(poParent),
	m_yHeight(0)
{
}

inline void ctable_row_leaf_block::update_height(ng_ydist yElementHeight)
{
	m_yHeight += yElementHeight;
	ASSERT(m_yHeight >= 0);
}

inline void ctable_row_node_block::update_height(ng_ydist yElementHeight)
{
	m_yHeight += yElementHeight;
	ASSERT(m_yHeight >= 0);
}

inline void ctable_row_leaf::set_height(ng_ydist yHeight)
{
	ASSERT(yHeight >= 0);
	m_yHeight = yHeight;
}

//---------------- get height -----------------------

inline ng_ydist ctable_row_leaf::get_height() const
{
	ASSERT(m_yHeight >= 0);
	return m_yHeight;
}

inline ng_ydist ctable_row_leaf_block::get_height() const
{
	ASSERT(m_yHeight >= 0);
	return m_yHeight;
}

inline ng_ydist ctable_row_node_block::get_height() const
{
	ASSERT(m_yHeight >= 0);
	return m_yHeight;
}

//---------------- get height up to -------------------------

inline ng_ydist ctable_row_leaf_block::get_height_up_to(treearray::cleaf<ned_ident> * poLeaf)
{
	ng_ydist yHeight = 0;
	long nLeafPos = _lookup_position(poLeaf);
	for(long iter = 0; iter < nLeafPos; iter++)
	{
		ctable_row_leaf * poTRLeaf = dynamic_cast<ctable_row_leaf *>(m_oLeafArray[iter].Get());
		ASSERT(poTRLeaf);
		yHeight += poTRLeaf->get_height();
	}
	return yHeight;
}

inline ng_ydist ctable_row_node_block::get_height_up_to(SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoLeafBlockSP)
{
	ng_ydist yHeight = 0;
	long nNodePos = _lookup_position(rpoLeafBlockSP,NULL);
	for(long iter = 0; iter < nNodePos; iter++)
	{
		ctable_row_leaf_block * poTRLBlock = dynamic_cast<ctable_row_leaf_block *>(m_oBlockArray[iter].Get());
		if(poTRLBlock != NULL)
		{
			yHeight += poTRLBlock->get_height();
		}
		else
		{
			ctable_row_node_block * poTRNBlock = dynamic_cast<ctable_row_node_block*>(m_oBlockArray[iter].Get());
			ASSERT(poTRNBlock != NULL);
			yHeight += poTRNBlock->get_height();
		}
	}
	return yHeight;
}

//---------------- lookup_entry_on_height -------------------------------
inline ctable_row_leaf * ctable_row_leaf_block::lookup_entry_on_height(ng_ydist & ryHeight)
{
	ASSERT(ryHeight >= 0);
	ASSERT(ryHeight <= get_height() );
	for(long iter = 0; iter < m_oLeafArray.GetSize(); iter++)
	{
		ctable_row_leaf * poTRLeaf = dynamic_cast<ctable_row_leaf *>(m_oLeafArray[iter].Get());
		ASSERT(poTRLeaf);
		if(poTRLeaf->get_height() >= ryHeight)
		{
			return poTRLeaf;
		}
		ryHeight -= poTRLeaf->get_height();
		ASSERT(ryHeight >= 0);
	}
	
	ASSERT(false);
	return NULL;
}

inline ctable_row_leaf * ctable_row_node_block::lookup_entry_on_height(ng_ydist & ryHeight)
{
	ASSERT(ryHeight >= 0);
	ASSERT(ryHeight <= get_height() );
	for(long iter = 0; iter < m_oBlockArray.GetSize(); iter++)
	{
		ng_ydist yBlockHeight;
		ctable_row_leaf_block * poTRLBlock = dynamic_cast<ctable_row_leaf_block *>(m_oBlockArray[iter].Get());
		if(poTRLBlock != NULL)
		{
			yBlockHeight = poTRLBlock->get_height();
			if(yBlockHeight >= ryHeight)
			{
				return poTRLBlock->lookup_entry_on_height(ryHeight);
			}
		}
		else
		{
			ctable_row_node_block * poTRNBlock = dynamic_cast<ctable_row_node_block*>(m_oBlockArray[iter].Get());
			ASSERT(poTRNBlock != NULL);
			yBlockHeight = poTRNBlock->get_height();
			if(yBlockHeight >= ryHeight)
			{
				return poTRNBlock->lookup_entry_on_height(ryHeight);
			}
		}
		ryHeight -= yBlockHeight;
		ASSERT(ryHeight >= 0);
	}
	ASSERT(false);
	return NULL;
}

inline void ctable_row_leaf_block::on_block_split(treearray::cleaf_block<ned_ident> * poDestLeafBlock,
		SCP< treearray::cleaf<ned_ident> > & rpoMoveLeafSP)
{
	ctable_row_leaf_block * pTRLB = dynamic_cast<ctable_row_leaf_block *>(poDestLeafBlock);
	ASSERT(pTRLB);
	ctable_row_leaf * poTRL = dynamic_cast<ctable_row_leaf *>(rpoMoveLeafSP.Get());
	ASSERT(poTRL);

	update_height(-poTRL->get_height());
	pTRLB->update_height(poTRL->get_height());
}

inline void ctable_row_node_block::on_block_split(treearray::cnode_block<ned_ident> * poDestLeafBlock,
					 SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoMoveBlockSP)
{
	ctable_row_node_block * pTRN = dynamic_cast<ctable_row_node_block *>(poDestLeafBlock);
	ASSERT(pTRN);

	ctable_row_leaf_block * poTRLBlock = dynamic_cast<ctable_row_leaf_block *>(rpoMoveBlockSP.Get());
	if(poTRLBlock != NULL)
	{
		update_height(-poTRLBlock->get_height());
		pTRN->update_height(poTRLBlock->get_height());
	}
	else
	{
		ctable_row_node_block * poTRNBlock = dynamic_cast<ctable_row_node_block*>(rpoMoveBlockSP.Get());
		ASSERT(poTRNBlock != NULL);
		update_height(-poTRNBlock->get_height());
		pTRN->update_height(poTRNBlock->get_height());
	}
}

inline void ctable_row_node_block::on_root_promote(SCP< treearray::cnode_or_leaf_block<ned_ident> > & rpoOldRootSP)
{
	ctable_row_leaf_block * poTRLBlock = dynamic_cast<ctable_row_leaf_block *>(rpoOldRootSP.Get());
	if(poTRLBlock != NULL)
	{
		update_height(poTRLBlock->get_height());
	}
	else
	{
		ctable_row_node_block * poTRNBlock = dynamic_cast<ctable_row_node_block*>(rpoOldRootSP.Get());
		ASSERT(poTRNBlock != NULL);
		update_height(poTRNBlock->get_height());
	}
}

//--------------------------------------------------------------

#ifdef _DEBUG
inline void ctable_row_leaf::print_leaf(long nIndent)
{
	CString oTabString('\t',nIndent);
	TRACE("%s<leaf>%d</leaf>\n",oTabString,get_value());
}
#endif

//--------------------------------------------------------------

inline void cindexed_table_row_array::update_height(ned_ident idRow,ng_ydist yHeight)
{
	//find leaf corresponding to idRow
	SCP< treearray::cleaf<ned_ident> > poLeafSP;
	VERIFY(m_oIndexMap.Lookup(idRow,poLeafSP));

	//update height
	_update_height(poLeafSP,yHeight);
}

//--------------------------------------------------------------
inline const ened_element_type cned_tablesection::get_new_row_type() const
{
	return ned_tablerow;
}

//--------------------- formalizm --------------------------------------------
inline void cned_tablesection::get_children_metrics(const ned_measure_param &)
{
	ASSERT(false);	//shouldnt be called
}

//-------------- fill clone -------------- -------------- -------
inline void cned_tablesection::fill_clone(cned_element *)
{
	ASSERT(false);	//shouldnt be called
}



}

#else
	#error __FILE__ already included
#endif
