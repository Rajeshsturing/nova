/*
	NAVO Enterprise 2008
	2003-04-03

	cned_tablesection
		sekcja tabelki
		core part
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "tablerow_ned.h"
#include "tablecell_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
void cindexed_table_row_array::_update_height(SCP<treearray::cleaf<ned_ident> > poLeafSP,ng_ydist yHeight)
{
	ASSERT(poLeafSP.PointsObject());
	//update left, get old height and compute delta height
	{
		ctable_row_leaf * poTRF = dynamic_cast<ctable_row_leaf *>(poLeafSP.Get());
		ASSERT(poTRF);
		
		ng_ydist yOldHeight = poTRF->get_height();
		poTRF->set_height(yHeight);
		
		yHeight -= yOldHeight;
	}

	if(yHeight != 0)
	{
		//update leaf-block
		SCP< treearray::cleaf_block<ned_ident> > poLeafBlockSP = poLeafSP->get_parent();
		ctable_row_leaf_block * poTRLB = dynamic_cast<ctable_row_leaf_block *>(poLeafBlockSP.Get());
		ASSERT(poTRLB != NULL);
		poTRLB->update_height(yHeight);
		
		//update all parent node-blocks
		SCP< treearray::cnode_block<ned_ident> > poNodeBlockSP = poLeafBlockSP->get_parent();
		ASSERT(poNodeBlockSP.PointsObject());		//at least one node block
		
		while(poNodeBlockSP.PointsObject())
		{
			ctable_row_node_block * poTRNB = dynamic_cast<ctable_row_node_block *>(poNodeBlockSP.Get());
			ASSERT(poTRNB != NULL);
			poTRNB->update_height(yHeight);
			poNodeBlockSP = poNodeBlockSP->get_parent();
		}
	}
}

ng_ydist cindexed_table_row_array::get_row_top(ned_ident idRow)
{
	//find leaf corresponding to idRow
	SCP< treearray::cleaf<ned_ident> > poLeafSP;
	VERIFY(m_oIndexMap.Lookup(idRow,poLeafSP));

	SCP< treearray::cleaf_block<ned_ident> > poLeafBlockSP = poLeafSP->get_parent();
	ctable_row_leaf_block * poTRLB = dynamic_cast<ctable_row_leaf_block *>(poLeafBlockSP.Get());
	ng_ydist yHeight = poTRLB->get_height_up_to(poLeafSP);
	
	//scan all parent node-blocks
	SCP< treearray::cnode_block<ned_ident> > poParentNodeBlockSP = poLeafBlockSP->get_parent();
	SCP< treearray::cnode_or_leaf_block<ned_ident> > poChildNodeBlockSP = poLeafBlockSP;
	ASSERT(poParentNodeBlockSP.PointsObject());		//at least one node block

	while(poParentNodeBlockSP.PointsObject())
	{
		ctable_row_node_block * poTRNB = dynamic_cast<ctable_row_node_block *>(poParentNodeBlockSP.Get());
		ASSERT(poTRNB != NULL);
		yHeight += poTRNB->get_height_up_to(poChildNodeBlockSP);
		
		poChildNodeBlockSP = poParentNodeBlockSP;
		poParentNodeBlockSP = poParentNodeBlockSP->get_parent();
	}

	return yHeight;
}

ned_ident cindexed_table_row_array::get_row_for_y(ng_ydist yCoord)
{
	ASSERT(yCoord >= 0);
	if(m_poRootSP.PointsObject())
	{
		ctable_row_node_block * poTRNB = dynamic_cast<ctable_row_node_block *>(m_poRootSP.Get());
		if(poTRNB->get_height() >= yCoord)
		{
			ctable_row_leaf * poTRLeaf = poTRNB->lookup_entry_on_height(yCoord);
			ASSERT(poTRLeaf);
			return poTRLeaf->get_value();
		}
	}

	return NEDID_NOTHING;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

void cned_tablesection::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	long nPrevTreeDisCnt;
	roForePainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_point oAllocRowPoint(oPaintPoint);

	for(long nAllocRowNr = 0;nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
	{
		alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);

		ened_spr eSPR = poAllocRow->should_paint(roForePainter,oAllocRowPoint,m_oActualSize.get_dx());
		
		if(eSPR == spr_inside || (eSPR == spr_below && poAllocRow->has_aliens()))
		{
			_draw_foreground_alloc_row(roForePainter,nAllocRowNr,oPaintPoint);
		}
		else
		{
			if(eSPR == spr_below)
			{
				break;
			}
		}

		//po namalowaniu sprawdŸ czy to ju¿ koniec
		ned_ident idTblRow = poAllocRow->get_table_row_ident();
		if(idTblRow != NEDID_NOTHING)
		{
			if(_get_last_measured() == idTblRow)
			{
				break;
			}
		}

		oAllocRowPoint.offset(0,poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space());
	}

	roForePainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_tablesection::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	long nPrevTreeDisCnt;
	roBackPainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_point oAllocRowPoint(oPaintPoint);

	ng_rect oSectionRect(oPaintPoint,m_oActualSize);

	_draw_std_background(roBackPainter,oSectionRect);

	for(long nAllocRowNr = 0;nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
	{
		alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
		ned_ident idTblRow = poAllocRow->get_table_row_ident();
		
		ened_spr eSPR = poAllocRow->should_paint(roBackPainter,oAllocRowPoint,m_oActualSize.get_dx());

		if(eSPR == spr_other || eSPR == spr_inside)
		{
			//malowanie t³a wiersza <tr> - mo¿e mieæ zadeklarowany 
			//inny kolor ni¿ komórka - w przypadku gdy s¹ dziury w wierszu
			//trzeba namalowaæ ca³y wiersz w jego kolorze
			if(idTblRow != NEDID_NOTHING)
			{
#ifdef _DEBUG
				ng_point oRowPoint(oPaintPoint);
				oRowPoint.offset(0,m_oRowIndex.get_row_top(idTblRow));
				ASSERT(oAllocRowPoint.get_y() == oRowPoint.get_y());
#endif
				ng_rect oTblRowRect(oAllocRowPoint,ng_size(m_oActualSize.get_dx(),poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space()));
				get_element_on_ident(idTblRow)->_draw_std_background(roBackPainter,oTblRowRect);
				get_manager()->store_paint_rect(idTblRow,MAIN_PAINT_RECT_ID,oTblRowRect);
			}
		}

		if(eSPR == spr_inside || (eSPR == spr_below && poAllocRow->has_aliens()))
		{
			_draw_background_alloc_row(roBackPainter,nAllocRowNr,oPaintPoint);
		}
		else
		{
			if(eSPR == spr_below)
			{
				break;
			}
		}

		//po namalowaniu sprawdŸ czy to ju¿ koniec
		if(idTblRow != NEDID_NOTHING)
		{
			if(_get_last_measured() == idTblRow)
			{
				break;
			}
		}

		oAllocRowPoint.offset(0,poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space());
	}

	_store_main_paint_rect(oSectionRect);

	roBackPainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_tablesection::_draw_foreground_alloc_row(cned_fore_painter & roForePainter,
	const long nAllocRowNr,const ng_point & roCurrentPoint)
{
	const long nColCount = get_col_count();

	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		SCP<cned_tablecell> poTableCellSP = _get_cell_for_rendering(nAllocRowNr,nColNr);
		
		if(poTableCellSP.PointsObject())
		{
			poTableCellSP->draw_foreground(roForePainter,roCurrentPoint,nAllocRowNr,nColNr);
		}
	}
}

void cned_tablesection::_draw_background_alloc_row(cned_back_painter & roBackPainter,
	const long nAllocRowNr,const ng_point & roCurrentPoint)
{
	const long nColCount = get_col_count();

	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		SCP<cned_tablecell> poTableCellSP = _get_cell_for_rendering(nAllocRowNr,nColNr);
		
		if(poTableCellSP.PointsObject())
		{
			poTableCellSP->draw_background(roBackPainter,roCurrentPoint);
		}
	}
}

ned_ident cned_tablesection::find_element_from_point(const ng_point & roPoint)
{
#ifdef _DEBUG
//	CDebugTimeMeter oDTM("section::find_element_from_point");
#endif

	ASSERT(is_inside_hit_area(roPoint));

	ng_point oInternalPoint(roPoint);
	oInternalPoint.offset(-m_oVectorSize);

	//znajdŸ wiersz
	ned_ident idRow = m_oRowIndex.get_row_for_y(oInternalPoint.get_y());
	if(idRow != NEDID_NOTHING)
	{
		//get-row-for-y zwraca równie¿ wiersze nie maj¹ce alokacji (prawid³owo z jego punktu widzenia
		//ale ogólnie bez sensu)
		//dlatego musimy pomin¹æ wiersze zdegenerowane

		SCP<cned_tablerow> poTableRowSP;
		
		while(idRow != NEDID_NOTHING)
		{
			poTableRowSP = scp_cast_ui<cned_tablerow>(get_element_on_ident(idRow));
			if(poTableRowSP->has_alloc_row_nr())
			{
				break;
			}
			idRow = poTableRowSP->get_next_element_ident();
			poTableRowSP = 0;
		}
		
		if(poTableRowSP.PointsObject())
		{
			long nAllocRowNr = poTableRowSP->get_alloc_row_nr();
			
			//ned_to_do: ten kod bêdzie prawdopodobnie mo¿na uwspólniæ ...
			
			//szukaj komórki
			const long nColCount = get_col_count();
			for(long nColNr = 0; nColNr < nColCount; nColNr++)
			{
				ned_ident idCell = cell_ident_from_encoded(_get_alloc_row(nAllocRowNr)->get_cell_encoded(nColNr));
				if(idCell != 0)
				{
					ASSERT(idCell != NEDID_NOTHING);
					SCP<cned_tablecell> poTableCellSP = scp_cast_ui<cned_tablecell>(get_element_on_ident(idCell));
					if(poTableCellSP->is_inside_hit_area(oInternalPoint))
					{
						return poTableCellSP->find_element_from_point(oInternalPoint);
					}
				}
			}
			//wolna przetrzeñ w komórce
			return idRow;
		}
	}

	return get_ident();
}


