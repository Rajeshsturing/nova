/*
	NAVO Enterprise 2003
	2003-04-02

	navo enhanced display (NED)

	ned_tablesection
		sekcja tabelki
	
	rendering
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

//------------------------------------------------------------------------------------------
// get_metrics
//------------------------------------------------------------------------------------------

void cned_tablesection::finish_measure_columns()
{
	//ned_to_do: pêtla nie do koñca, tylko do ostatniego zmierzonego
	//trzeba w measure_column rejestrowaæ ostatni u³o¿ony wiersz
	//i minimum z tego zaznaczaæ jako clear-measure-pending

	for(long nAllocRowNr = 0; nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
	{
		alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
		poAllocRow->normalize_bottom_side_space();
		ned_ident idTblRow = poAllocRow->get_table_row_ident();
		if(idTblRow != NEDID_NOTHING)
		{
			get_element_on_ident(idTblRow)->clear_measure_pending();
		}
	}

	//normalizuj top side space
	if(m_yTopSideSpace == MAXLONG)
	{
		m_yTopSideSpace = 0;
	}
	
	clear_measure_pending();

#ifdef _DEBUG
	dump_cells();
#endif
}

void cned_tablesection::_update_cell_common_border_space(SCP<cned_tablecell> poTableCellSP,long nAllocRowNr,long nColNr)
{
	SCP<cned_table> poTableSP = _get_table();
	long nFramePxWidth = poTableCellSP->_get_frame_px_width();

	//z lewej strony
	long nLeftSpaceAddr = nColNr - poTableCellSP->get_prop_colspan();
	ASSERT(nLeftSpaceAddr >= -1);
	if(nLeftSpaceAddr == -1)
	{
		poTableSP->update_left_side_space(nFramePxWidth);
	}
	else
	{
		poTableSP->get_column(nLeftSpaceAddr).update_right_side_space(nFramePxWidth);
	}
	//z prawej strony
	poTableSP->get_column(nColNr).update_right_side_space(nFramePxWidth);

	//z góry
	long nTopSpaceAddr = nAllocRowNr - poTableCellSP->get_prop_rowspan();
	ASSERT(nTopSpaceAddr >= -1);
	if(nTopSpaceAddr == -1)
	{
		 update_top_side_space(nFramePxWidth);
	}
	else
	{
		 _get_alloc_row(nTopSpaceAddr)->update_bottom_side_space(nFramePxWidth);
	}
	//z do³u
	_get_alloc_row(nAllocRowNr)->update_bottom_side_space(nFramePxWidth);
}

void cned_tablesection::get_cell_common_border_space(cned_tablecell * poTableCell,long nAllocRowNr,long nColNr,ng_rect & roSpaceRect) const
{
	ASSERT(poTableCell != NULL);

	SCP<cned_table> poTableSP = _get_table();
	
	//left
	roSpaceRect.set_left(0);
	long nLeftSpaceAddr = nColNr - poTableCell->get_prop_colspan();
	ASSERT(nLeftSpaceAddr >= -1);
	
	if(nLeftSpaceAddr == -1)
	{
		roSpaceRect.set_left(poTableSP->get_left_side_space());
	}
	else
	{
		roSpaceRect.set_left(poTableSP->get_column(nLeftSpaceAddr).get_right_side_space());
	}

	//right
	roSpaceRect.set_right(poTableSP->get_column(nColNr).get_right_side_space());
	
	//top
	roSpaceRect.set_top(0);
	long nTopSpaceAddr = nAllocRowNr - poTableCell->get_prop_rowspan();
	ASSERT(nTopSpaceAddr >= -1);
	if(nTopSpaceAddr == -1)
	{
		roSpaceRect.set_top(get_top_side_space());
	}
	else
	{
		roSpaceRect.set_top(_get_alloc_row(nTopSpaceAddr)->get_bottom_side_space());
	}

	//bottom
	roSpaceRect.set_bottom(_get_alloc_row(nAllocRowNr)->get_bottom_side_space());

	ASSERT(roSpaceRect.get_left() >= 0);
	ASSERT(roSpaceRect.get_right() >= 0);
	ASSERT(roSpaceRect.get_top() >= 0);
	ASSERT(roSpaceRect.get_bottom() >= 0);
}

//--------------------------------------------------------------------
//	zmierz komórkê i update informacje o szerokoœciach kolumn w tabelce
//--------------------------------------------------------------------

ng_ydist cned_tablesection::_measure_cell(const ned_measure_param & roMParam,
	SCP<cned_tablecell> & rpoTableCellSP,long nAllocRowNr,long nColNr,cned_table::column & roColumn)
{
	ASSERT(rpoTableCellSP.PointsObject());

	ng_xdist xMinInternalCellWidth = 0;

	//1. niech komórka zmierzy siê "wewnêtrznie"
	const cned_metrics & roCellMetrics = rpoTableCellSP->get_metrics(roMParam,xMinInternalCellWidth);
	ASSERT(xMinInternalCellWidth <= roCellMetrics.get_minimal_width());
	
	//2. analizuj wyniki
	long nColSpan = rpoTableCellSP->get_prop_colspan();
	ASSERT(nColSpan >= 1);
	ng_xdist dxSpanMinWidth = roCellMetrics.get_minimal_width();
	
	//3. dla colspanów - odejmij obszar minimalny zarezerwowany w poprzednich kolumnach
	if(nColSpan > 1)
	{
		long nSpanMetric = roCellMetrics.get_weight() / nColSpan;
		SCP<cned_table> poTableSP = _get_table();
		
		while(--nColSpan > 0)
		{
			//zredukuj min. width o szerokoœci uwzglêdnione w poprzednich kolumnach
			ng_xdist xPrevColIntMinWidth = poTableSP->get_column(nColNr - nColSpan).get_internal_min_width();
			dxSpanMinWidth -= xPrevColIntMinWidth;
			xMinInternalCellWidth -= xPrevColIntMinWidth;
			poTableSP->get_column(nColNr - nColSpan).update_weight(nSpanMetric);
		}
		roColumn.update_weight(nSpanMetric);
	}
	else
	{
		roColumn.update_weight(roCellMetrics.get_weight());
	}

	//4. update column info
	roColumn.update_min_width(dxSpanMinWidth);
	roColumn.update_internal_min_width(xMinInternalCellWidth);
	roColumn.set_owns_cells();
	
	//5. set declared col width, but only once
	if(is_auto_width_value(roColumn.get_prop_extwidth()))
	{
		if(rpoTableCellSP->get_prop_colspan() == 1)
		{
			ng_xdist xColWidth = rpoTableCellSP->get_prop_extwidth();
			if(!is_auto_width_value(xColWidth))
			{
				roColumn.set_prop_extwidth(xColWidth);
			}
		}
	}

	_update_cell_common_border_space(rpoTableCellSP,nAllocRowNr,nColNr);

	return roCellMetrics.get_minimal_height();
}



void cned_tablesection::measure_column(const ned_measure_param & roMParam,long nColNr,ng_ydist & ryMinHeight)
{
	SCP<cned_table> poTableSP = _get_table();

	for(long nAllocRowNr = 0; nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
	{
		if(nColNr == 0)
		{
			//to robimy osobno dla ka¿dego wiersza, poniewa¿ w miarê pomiaru
			//mo¿e przybywaæ wierszy alokacji (update-allocations)
			_get_alloc_row(nAllocRowNr)->reset_bottom_side_space();
		}

		//uwaga! roTableCol pobieramy za ka¿dym razem, bo _update_allocations mo¿e realokowaæ
		cned_table::column & roTableColumn = poTableSP->get_column(nColNr);

		SCP<cned_tablecell> poTableCellSP = _get_cell_for_rendering(nAllocRowNr,nColNr);
		if(poTableCellSP.PointsObject())
		{
			ryMinHeight += _measure_cell(roMParam,poTableCellSP,nAllocRowNr,nColNr,roTableColumn);
			
			if(ryMinHeight > roMParam.get_req_y())
			{
//ned_to_do: inc_rend	TRACE("section %d measurement broken at %d row\n",get_ident(),nAllocRowNr);
//ned_to_do: inc_rend	return;
			}
		}

		//zapewnij, ¿e alokacja komórek jest zrobiona 
		const long nAllocateTo = 10 + ((nAllocRowNr + 1) / 10) * 10;
		ASSERT(nAllocateTo >= nAllocRowNr+1);
		_update_allocations(nAllocateTo,roMParam.is_printing());
	}

}

//------------------------------------------------------------------------------------------
// rendering
//------------------------------------------------------------------------------------------

ng_ydist cned_tablesection::_render_cell(cned_renderer_ & roRenderer,
	SCP<cned_tablecell> & rpoTableCellSP,const long nAllocRowNr,const long nColNr,
	const ng_point & roTopLeftPoint,ng_xdist dxWidth)
{
	ASSERT(rpoTableCellSP.PointsObject());

	//1. analiza rowspanu - wyznacz cofniêcie w pionie (o wysokoœæ poprzednich wierszy)
	long nRowSpan = rpoTableCellSP->get_prop_rowspan();
	ASSERT(nAllocRowNr >= nRowSpan - 1);

	ng_ydist yPrevRowHeight = 0;
	while(--nRowSpan > 0)
	{
		alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr-nRowSpan);
		yPrevRowHeight += poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space();
	}
	
	//2. analiza colspanu - wyznacz cofniêcie w poziomie (o szerokoœæ poprzednich komórek)
	long nColSpan = rpoTableCellSP->get_prop_colspan();
	ASSERT(nColNr >= nColSpan - 1);
	
	ng_xdist xPrevColWidth = 0;
	while(--nColSpan > 0)
	{
		cned_table::column & roPrevTabCol = _get_table()->get_column(nColNr - nColSpan);
		xPrevColWidth += roPrevTabCol.get_actual_col_width() + roPrevTabCol.get_right_side_space();
	}

	//przygotuj wspó³rzêdne
	ng_point oTopLeftPoint(roTopLeftPoint);
	oTopLeftPoint.offset(-xPrevColWidth,-yPrevRowHeight);

	cned_transport_renderer oTableCellRend(roRenderer,oTopLeftPoint,dxWidth + xPrevColWidth);
	
	ng_ydist yCellHeight = rpoTableCellSP->render(oTableCellRend,nAllocRowNr,nColNr);

	//zwróæ wysokoœæ zajêt¹ w bie¿¹cym wierszu (a nie ca³¹ komórki)
	return yCellHeight - yPrevRowHeight;
}

ng_ydist cned_tablesection::_render_alloc_row(cned_renderer_ & roRenderer,const long nAllocRowNr,ng_ycoord yCurrTop)
{
	SCP<cned_table> poTableSP = _get_table();

	ng_xcoord xCurrX = poTableSP->get_left_side_space();
	
	CArray<ng_ydist,ng_ydist> oCellHeightArray;
	const long nColCount = get_col_count();
	
	oCellHeightArray.SetSize(nColCount);
	//wyzeruj wysokoœci
	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		oCellHeightArray[ nColNr ] = ng_ydist(0);
	}
	
	//renderuj po kolei wszystkie komórki w wierszu i zapamiêtaj ich wysokoœci

	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		cned_table::column  & roTableCol = poTableSP->get_column(nColNr);

		ng_xdist xColWidth = roTableCol.get_actual_col_width();
		ng_xdist xRightSpace = roTableCol.get_right_side_space();
		
		SCP<cned_tablecell> poTableCellSP = _get_cell_for_rendering(nAllocRowNr,nColNr);
		
		if(poTableCellSP.PointsObject())
		{
			oCellHeightArray[nColNr] = 
				_render_cell(roRenderer,poTableCellSP,nAllocRowNr,nColNr,ng_point(xCurrX,yCurrTop),xColWidth);
		}

		xCurrX += xColWidth + xRightSpace;
	}
	
	//wylicz max. wysokoœæ komórek
	alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
	ng_ydist yRowHeight = 0;

	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		yRowHeight = max(yRowHeight, oCellHeightArray[nColNr] );
	}

	//jeœli wiersz ma rêcznie zadeklarowan¹ wysokoœæ, to j¹ uwzglêdnij
	//(ale tylko gdy jest dopuszczalna)
	{
		ned_ident idTblRow = poAllocRow->get_table_row_ident();

		if(idTblRow != NEDID_NOTHING)
		{
			ng_ydist yDeclRowExtHeight = get_element_on_ident(idTblRow)->get_prop_extheight();
			if(is_normal_height_value(yDeclRowExtHeight))
			{
				ng_ydist yDeclRowPxHeight = get_manager()->to_internal(ng_size(0,yDeclRowExtHeight)).get_dy();
#ifdef _DEBUG
				{
					if(yDeclRowPxHeight < yRowHeight)
					{
						TRACE("declared row height %d < %d for row %d\n",yDeclRowPxHeight,yRowHeight,idTblRow);
					}
				}
#endif
				yRowHeight = max(yRowHeight,yDeclRowPxHeight);
			}
		}
	}

	//wyrównanie wysokoœci komórek w pionie
	for(long nColNr = 0; nColNr < get_col_count(); nColNr++)
	{
		if(yRowHeight != oCellHeightArray[nColNr])
		{
			SCP<cned_tablecell> poTableCellSP = _get_cell_for_rendering(nAllocRowNr,nColNr);
			if(poTableCellSP.PointsObject())
			{
				poTableCellSP->render_increase_height(yRowHeight - oCellHeightArray[nColNr]);
			}
		}
	}

	poAllocRow->set_row_height(yRowHeight);
	yRowHeight += poAllocRow->get_bottom_side_space();

	//zwróc wysokoœæ wiersza + odstêp pod nim
	return yRowHeight;
}

void cned_tablesection::render(cned_renderer_ & roSectionRenderer)
{
	ASSERT(!get_prop_hidden());

	ng_ycoord yCurrTop = get_top_side_space();

	//zmiana szerokoœci ma najwy¿szy priorytet - wtedy trzeba zacz¹æ od pocz¹tku
	//jeœli szerokoœci te same to wyszukaj co siê da pomin¹æ
	//w tym przypadku po prostu przejdŸ dalej
	ned_ident idStartingTableRow = get_first_child_ident();
	long nTblRowNr = 0;
	
	//ned_to_do: inc_rend: restartowanie renderingu
	if(false && roSectionRenderer.get_current_width() == m_oActualSize.get_dx())
	{
		if(_get_last_measured() != NEDID_NOTHING)
		{
			cned_filter_children__<cned_tablerow> oRowFilterChildren(this,false,false);
			while(!oRowFilterChildren.is_end())
			{
				if(oRowFilterChildren.get_ident() == _get_last_measured())
				{
					break;
				}
				oRowFilterChildren.move_next();
				nTblRowNr++;
			}
			if(oRowFilterChildren.get_ident() == NEDID_NOTHING)
			{
				//ned_to_do:
				//wszystko ok
			}
			else
			{
				oRowFilterChildren.move_next();
				nTblRowNr++;
				idStartingTableRow = oRowFilterChildren.get_ident();
				//wyznacz alloc row
				//ned_to_do: wyznacz yCurrTop
			}
		}
	}

	//dla ka¿dego <tr> trzeba przypisaæ wysokoœæ
	//ale niektóre <tr> nie s¹ w alloc row (np. ukryte)
	//dlatego nale¿y analizowaæ czy wiersz by³ procesowany i jeœli nie to przypisaæ mu 0

	cned_filter_children__<cned_tablerow> oRowFilterChildren(this,false,false);
	oRowFilterChildren.restart_at(idStartingTableRow);
	while(nTblRowNr <= m_nLastRowWithAlloc)
	{
		ASSERT(!oRowFilterChildren.is_end());
		SCP<cned_tablerow> poTableRowSP = oRowFilterChildren.get_element();
		
		ng_ydist yRowHeight = 0;
		
		if(poTableRowSP->has_alloc_row_nr())
		{
			ASSERT(!poTableRowSP->get_prop_hidden());

			yRowHeight = _render_alloc_row(roSectionRenderer,poTableRowSP->get_alloc_row_nr(),yCurrTop);
		}

		m_oRowIndex.update_height(poTableRowSP->get_ident(),yRowHeight);
		yCurrTop += yRowHeight;
		
		poTableRowSP->mark_all_rendered();		//notify <tr> that all have been done
		
		roSectionRenderer.__add_to_post_renderer(poTableRowSP->get_ident());

#ifdef _DEBUG
		{
			if(poTableRowSP->has_alloc_row_nr())
			{
		//		TRACE("rowheight [%d]->%d={%d}\n",poTableRowSP->get_ident(),poTableRowSP->get_alloc_row_nr(),yRowHeight);
			}
			else
			{
		//		TRACE("rowheight [%d]->?={0}\n",poTableRowSP->get_ident());
			}
		}
#endif

		//ned_to_do: warunek uwzglêdniaj¹cy wspó³rzêdne bezwzglêdne
		if(yCurrTop > roSectionRenderer.get_req_y())
		{
			//ned_to_do: inc_rend	
		//	break;
		}

		oRowFilterChildren.move_next();
		nTblRowNr++;
	}

	_validate_last_measured((oRowFilterChildren.get_ident() == NEDID_NOTHING) ? NEDID_LAST : oRowFilterChildren.get_ident());

	//here yCurrTop = full virtual size
	yCurrTop = _correct_rendered_section_height(roSectionRenderer,yCurrTop);

	ng_size oSectionSize(roSectionRenderer.get_current_width(),yCurrTop);

	roSectionRenderer.allocate_rect(get_ident(),-1,oSectionSize,m_oActualSize,m_oVectorSize);

#ifdef _DEBUG
//	m_oRowIndex.print();
#endif
}


//-------- page breaking ---------------------------------
void cned_tablesection::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	const long nColCount = get_col_count();
	ng_ycoord yCurrY = oPaintPoint.get_y();

	for(long nAllocRowNr = 0;nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
	{
		alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
		
		if(yCurrY > roSplitInfo.get_max_bottom())
		{
			//next page -> finish current
			roSplitInfo.next_y_page();
		}
		else
		{
			
			//jesli wystaje -> sprawdzamy kolejne komórki
			//jeœli nie -> wszystko w porz¹dku
			
			if(
				(get_manager()->get_form_feed_count() != 0) || 
				(yCurrY + poAllocRow->get_row_height() > roSplitInfo.get_max_bottom())
			  )
			{
				for(long nColNr = 0; nColNr < nColCount; nColNr++)
				{
					DWORD dwCellEncoded = poAllocRow->get_cell_encoded(nColNr);

					if(cell_type_from_encoded(dwCellEncoded) & CELL_TYPE_LT)
					{
						ned_ident idCell = cell_ident_from_encoded(dwCellEncoded);
						if(idCell != 0)
						{
							SCP<cned_tablecell> poTableCellSP = 
								scp_cast_ui<cned_tablecell>(get_element_on_ident(idCell));
							
							poTableCellSP->update_split_info(oPaintPoint,roSplitInfo);
						}
					}
				}
			}
		}
		
		yCurrY += poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space();
	}
}


void cned_tablesection::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	//------ part I - klonowanie wierszy
	{
		ng_point oAllocRowPoint(oPaintPoint);
		
		for(long nAllocRowNr = 0;nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
		{
			alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
			ned_ident idTblRow = poAllocRow->get_table_row_ident();
			if(idTblRow != NEDID_NOTHING)
			{
				ng_rect oTblRowRect(oAllocRowPoint,ng_size(m_oActualSize.get_dx(),poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space()));
	
				//splitujemy siê do ka¿dego obszaru
				long xAreaLeft = roSplitManager.find_x_area(oTblRowRect.get_left());
				long xAreaRight = roSplitManager.find_x_area(oTblRowRect.get_right());
				long yAreaTop = roSplitManager.find_y_area(oTblRowRect.get_top());
				long yAreaBottom = roSplitManager.find_y_area(oTblRowRect.get_bottom());

				for(long yArea = yAreaTop; yArea <= yAreaBottom; yArea++)
				{
					for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
					{
						SCP<cned_element> poClonedTableRowSP =get_element_on_ident(idTblRow)->_make_clone_split(roSplitManager,xArea,yArea);
			
//						TRACE("CLONE:TABLE_ROW %d to [%d,%d] as %d\n", idTblRow,xArea,yArea,
//							poClonedTableRowSP->get_ident());

						if(yAreaTop == yAreaBottom)
						{
							//ustawiamy wysokoœæ wiersza na zrenderowan¹ 
							//dziêki temu w poziomie wszystkie kartki maj¹ 
							//tak¹ sam¹ wysokoœæ wiersza
							//ale tylko dla wierszy, które nie splituj¹ siê w pionie

							poClonedTableRowSP->set_prop_extheight(get_manager()->to_external(
								ng_size(0,poAllocRow->get_row_height())).get_dy());
						}
					}
				}
			}
			
			
			oAllocRowPoint.offset(0,poAllocRow->get_row_height() + poAllocRow->get_bottom_side_space());
		}
	}

	//----- part II - klonowanie komórek
	{
		const long nColCount = get_col_count();
		for(long nAllocRowNr = 0;nAllocRowNr < get_alloc_row_count(); nAllocRowNr++)
		{
			alloc_row * poAllocRow = _get_alloc_row(nAllocRowNr);
			for(long nColNr = 0; nColNr < nColCount; nColNr++)
			{
				DWORD dwCellEncoded = poAllocRow->get_cell_encoded(nColNr);

				if(cell_type_from_encoded(dwCellEncoded) & CELL_TYPE_LT)
				{
					ned_ident idCell = cell_ident_from_encoded(dwCellEncoded);
					
					if(idCell != 0)
					{
						SCP<cned_tablecell> poTableCellSP = scp_cast_ui<cned_tablecell>(get_element_on_ident(idCell));
						poTableCellSP->make_split(oPaintPoint,roSplitManager,nAllocRowNr,nColNr);
					}
				}
			}
		}
	}
}

