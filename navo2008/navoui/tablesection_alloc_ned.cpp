/*
	NAVO Enterprise 2003
	2003-03-30

	navo enhanced display (NED)

	ned_tablesection
		sekcja tabelki
	
	allokacje komórek
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

//------------- child management ----------------------------------------------

void cned_tablesection::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	if(rpoChildSP->get_container_ident() == get_ident())
	{
#ifdef _DEBUG
		{
			if(get_type() ==  ned_spreadpatternsection)
			{
				ASSERT(rpoChildSP->get_type() == ned_patterntablerow);
			}
			else
			{
				ASSERT(rpoChildSP->get_type() == ned_tablerow);
			}
		}
#endif
		long nInsertPosition = 0;
		if(rpoChildSP->get_prev_element_ident() != NEDID_NOTHING)
		{
			nInsertPosition = 1 + m_oRowIndex.get_position(rpoChildSP->get_prev_element_ident());
		}
		m_oRowIndex.insert_at(nInsertPosition,rpoChildSP->get_ident());
		_invalidate_row_with_alloc_nr(nInsertPosition);
	}
	cned_rect_container_::on_child_inserted(rpoChildSP);
}

void cned_tablesection::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		_invalidate_row_with_alloc_ident(idChild);
		m_oRowIndex.remove_element(idChild);
	}
	cned_rect_container_::on_child_removing(idChild);
}

void cned_tablesection::remove_children(bool bWhileRemovingItself)
{
	_invalidate_row_with_alloc_nr(0);
	cned_rect_container_::remove_children(bWhileRemovingItself);
	m_oRowIndex.remove_all();
}

void cned_tablesection::on_child_size_info_dirty(ned_ident idRow)
{
	ASSERT(get_manager()->get_element_container_ident(idRow) == get_ident());

	if(!is_measure_pending())	//tylko jeœli prawid³owy
	{
		set_measure_pending();	//zaznacz ¿e z³y
	
		if(!get_prop_hidden())	//tylko jeœli jest widoczny
		{
			//ogranicz notyfikacjê tylko do przypadku gdy siê 'pogorszy³o'
			//tzn. zepsu³ siê element przed ostatnim u³o¿onym

			if(_get_last_measured() == NEDID_NOTHING)	//wszystko z³e
			{
				return;
			}
			long nChangedRowNr = m_oRowIndex.get_position(idRow);
			long nLastMeasuredRowNr = (_get_last_measured() == NEDID_LAST) ? MAXLONG : m_oRowIndex.get_position(_get_last_measured());
			if(nChangedRowNr <= nLastMeasuredRowNr)
			{
				_invalidate_last_measured(get_manager()->get_prev_element(idRow));

				SCP<cned_container> poContainerSP = get_container();
				if(poContainerSP.PointsObject())
				{
					poContainerSP->on_child_size_info_dirty(get_ident());
				}
			}
		}
	}

	ASSERT(is_measure_pending());

	_vse_dirty();
}

//-------------------------------------------------------------------
//	odtwórz alokacje komórek a¿ do zadanego nr-u wiersza alokacji
//-------------------------------------------------------------------
void cned_tablesection::_update_allocations(long nUpToAllocRowNr,bool bSkipNonPrintable)
{
	ASSERT(m_nLastRowWithAlloc <= get_child_count() - 1);

	/*
	
	ned_to_do: 

	powa¿ny problem polega na tym, ¿e jeœli invalidujemy m_nLastRowWithAlloc,
	to pozostaj¹ nieprawid³owe wiersze alokacji
	jeœli teraz usuwamy wiersze <tr>, to powy¿szy warunek (np. pusta sekcja)
	powoduje ¿e nic nie jest robione z wieraszami alokacji i pêtle
	chodz¹ce na get_alloc_row_count() chodz¹ po œmieciach
	Albo zrobiæ get_valid_alloc_row_count(),
	albo usuwaæ z tablicy nieprawid³owe wiersze 
	- ale uwaga - z jakiegoœ powodu nie chcia³em usuwaæ - byæ mo¿e chodzi o bottom space
	- trzeba to przeanalizowaæ
	*/


	//sprawdŸ czy request jest spe³niony

	long nLastValidAllocRowNr = -1;
	if(m_nLastRowWithAlloc >= 0)
	{
		nLastValidAllocRowNr = get_row(m_nLastRowWithAlloc)->get_alloc_row_nr();
	}
	if(nLastValidAllocRowNr >= nUpToAllocRowNr)
	{
		return;
	}

//	TRACE("_upd_alloc sect=%d, valid(tblrow)=%d, req(allocrow)=%d\n",get_ident(),m_nLastRowWithAlloc,nUpToAllocRowNr);

	//cofnij siê do wiersza który nie ma alienów
	while(nLastValidAllocRowNr >= 0)
	{
		if(!_get_alloc_row(nLastValidAllocRowNr)->has_aliens())
		{
			break;
		}
		nLastValidAllocRowNr--;
	}
	
	ASSERT(get_alloc_row_count() >= nLastValidAllocRowNr + 1);	//mo¿na tylko pomniejszaæ
	
	//clean allocations
	for(long iR = nLastValidAllocRowNr + 1; iR < get_alloc_row_count(); iR++)
	{
//		TRACE("_upd_alloc sect=%d, cleared (allocrow)=%d\n",get_ident(),iR);
		_get_alloc_row(iR)->clean();
	}

	//3. uk³adaj a¿ do spe³nienia ¿¹dania lub koñca tabelki
	
	//uwaga! tutaj nie mo¿emy wrzuciæ filtrowania, poniewa¿
	//chcemy równie¿ oznaczaæ wiersze pomijane (patrz wywo³anie set_alloc_row_nr)

	cned_filter_children__<cned_tablerow> oTableRowFilter(this,false,false);

	if(nLastValidAllocRowNr >= 0)
	{
		ned_ident idLastTblRow = _get_alloc_row(nLastValidAllocRowNr)->get_table_row_ident();
		ASSERT(idLastTblRow != NEDID_NOTHING);
		ned_ident idStartingTblRow = get_manager()->get_next_element(idLastTblRow);
		oTableRowFilter.restart_at(idStartingTblRow);
	}

//	TRACE("_upd_alloc sect=%d, restarted (allocrow)=%d\n",get_ident(),nLastValidAllocRowNr);

	while(!oTableRowFilter.is_end())
	{
		if(nLastValidAllocRowNr >= nUpToAllocRowNr)
		{
			break;
		}

		long nAdvance = 0;
		SCP<cned_tablerow> poTableRowSP = oTableRowFilter.get_element();
		
		//sprawdzamy czy siê kwalifikuje
		bool bPerform = !poTableRowSP->get_prop_hidden();
		if(bPerform)
		{
			if(bSkipNonPrintable)
			{
				bPerform = poTableRowSP->get_prop_printable();
			}
		}

		if(bPerform)
		{
			long nColNr = 0;
			cned_filter_children__<cned_tablecell> oTableCellFilter(poTableRowSP,true,bSkipNonPrintable);
			while(!oTableCellFilter.is_end())
			{
				SCP<cned_tablecell> poTableCellSP = oTableCellFilter.get_element();

				long nColSpan = poTableCellSP->get_prop_colspan();
				long nRowSpan = poTableCellSP->get_prop_rowspan();
				
				while(get_alloc_row_count() < 1 + nLastValidAllocRowNr + nRowSpan)
				{
					_add_alloc_row();
				}
				ASSERT(1 + nLastValidAllocRowNr + nRowSpan <= get_alloc_row_count());
				
				nColNr = _find_free_cell(1 + nLastValidAllocRowNr,nColNr);
				while(nColNr + nColSpan > get_col_count())
				{
					internal_insert_col(get_col_count());
				}
				_alloc_block(poTableCellSP->get_ident(),
					1 + nLastValidAllocRowNr,nColNr,nColSpan,nRowSpan);
				
				//store binding bettwen <TR> and alloc row
				_get_alloc_row(1 + nLastValidAllocRowNr)->assign_row_ident(poTableRowSP->get_ident());
				
				nColNr += nColSpan;
				nAdvance = 1;
				oTableCellFilter.move_next();
			}
		}
		
		nLastValidAllocRowNr += nAdvance;
		poTableRowSP->set_alloc_row_nr(nLastValidAllocRowNr,nAdvance != 0);
		
		ASSERT(poTableRowSP->has_alloc_row_nr() == (nAdvance != 0));
	
		oTableRowFilter.move_next();
	}

	m_oAllocRowArray.SetSize(nLastValidAllocRowNr + 1);

	if(oTableRowFilter.get_ident() == NEDID_NOTHING)
	{
		m_nLastRowWithAlloc = get_child_count() - 1;
	}
	else
	{
		m_nLastRowWithAlloc = get_row_nr(oTableRowFilter.get_ident())- 1;
		ASSERT(nLastValidAllocRowNr >= nUpToAllocRowNr);
	}

#ifdef _DEBUG
//	TRACE("_upd_allc finished sect=%d lastvalid(tblrow)=%d, lastvalid(alloc)=%d\n",
//		get_ident(),m_nLastRowWithAlloc,nLastValidAllocRowNr); 
#endif
}

//-------------------------------------------------------------------

void cned_tablesection::_alloc_block(ned_ident idCell,long nRowNr,long nColNr,long nColSpan,long nRowSpan)
{
	ASSERT(nColSpan >= 1);
	ASSERT(nRowSpan >= 1);

	if(nRowSpan == 1)
	{
		alloc_row * poAllocRow = _get_alloc_row(nRowNr);

		if(nColSpan == 1)
		{
			ASSERT(poAllocRow->get_cell_encoded(nColNr) == 0);
			poAllocRow->set_cell_encoded(nColNr,idCell,CELL_TYPE_LT | CELL_TYPE_RB);
		}
		else
		{
			ASSERT(poAllocRow->get_cell_encoded(nColNr) == 0);
			poAllocRow->set_cell_encoded(nColNr,idCell,CELL_TYPE_LT);
			for(long iC = nColNr + 1; iC < nColNr+nColSpan-1; iC++)
			{
				ASSERT(poAllocRow->get_cell_encoded(iC) == 0);
				poAllocRow->set_cell_encoded(iC,idCell,CELL_TYPE_SPAN);
			}
			ASSERT(poAllocRow->get_cell_encoded(nColNr+nColSpan-1) == 0);
			poAllocRow->set_cell_encoded(nColNr+nColSpan-1,idCell,CELL_TYPE_RB);
		}
	}
	else
	{
		alloc_row * poAllocRow = _get_alloc_row(nRowNr);
		poAllocRow->mark_has_aliens();

		//1-szy wiersz
		ASSERT(poAllocRow->get_cell_encoded(nColNr) == 0);
		poAllocRow->set_cell_encoded(nColNr,idCell,CELL_TYPE_LT);
		
		for(long iC = nColNr + 1; iC < nColNr+nColSpan; iC++)
		{
			ASSERT(poAllocRow->get_cell_encoded(iC) == 0);
			poAllocRow->set_cell_encoded(iC,idCell,CELL_TYPE_SPAN);
		}

		//kolejne wiersze
		for(long iR = nRowNr + 1; iR < nRowNr + nRowSpan; iR++)
		{
			alloc_row * poAllocRow = _get_alloc_row(iR);
			for(long iC = nColNr; iC < nColNr+nColSpan; iC++)
			{
				ASSERT(poAllocRow->get_cell_encoded(iC) == 0);
				poAllocRow->set_cell_encoded(iC,idCell,CELL_TYPE_SPAN);
			}
			poAllocRow->mark_has_aliens();
		}
		//ostatni wiersz - ostatnia komórka
		_get_alloc_row(nRowNr + nRowSpan - 1)->set_cell_encoded(nColNr+nColSpan-1,idCell,CELL_TYPE_RB);
	}
}

#ifdef _DEBUG

void cned_tablesection::dump_cells()
{
	return;

	TRACE("----------------section %d ---------------------\n",get_ident());
	for(long ir = 0; ir < get_alloc_row_count(); ir++)
	{
		CString oString;
		for(long ic = 0; ic < get_col_count(); ic++)
		{
			CString oString2;
			
			DWORD nEncoded = _get_alloc_row(ir)->get_cell_encoded(ic);
			if(cell_ident_from_encoded(nEncoded) == 0)
			{
				oString2 = "[ ...... ]";
			}
			else
			{
				char cCode1  = '?',cCode2 = '?';

				if(cell_type_from_encoded(nEncoded) & CELL_TYPE_LT)
				{
					cCode1 = '<';
				}
				else
				{
					cCode1 = ' ';
				}

				if(cell_type_from_encoded(nEncoded) & CELL_TYPE_RB)
				{
					cCode2 = '>';
				}
				else
				{
					cCode2 = ' ';
				}
				oString2.Format("[%c%6d%c]",cCode1,cell_ident_from_encoded(nEncoded),cCode2);
			}
			oString += oString2;
		}
		ned_ident idTblRow = _get_alloc_row(ir)->get_table_row_ident();
		long nTblRowNr = -1;
		if(idTblRow != NEDID_NOTHING)
		{
			nTblRowNr = get_row_nr(idTblRow);
		}
		TRACE("%4d(%4d=%6d)=%s\n",ir,nTblRowNr,idTblRow,oString);
	}
	TRACE("----------------------------------------\n");
}

#endif

