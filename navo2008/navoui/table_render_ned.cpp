/*
	NAVO Enterprise 2003
	2003-03-30

	navo enhanced display (NED)

	ned_table
		tabelka

	render part
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

//---------------- rendering helpers ------------------------------
void cned_table::_initiate_allocations(bool bSkipNonPrintable)
{
	cned_filter_children__<cned_tablesection> oSectionFilter(this, true, bSkipNonPrintable);

	while (!oSectionFilter.is_end())
	{
		oSectionFilter.get_element()->_initiate_allocations(bSkipNonPrintable);
		oSectionFilter.move_next();
	}

	if (_get_next_header_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_next_header()->_initiate_allocations(bSkipNonPrintable);
	}
	if (_get_prev_footer_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_prev_footer()->_initiate_allocations(bSkipNonPrintable);
	}
}

void cned_table::_measure_columns(const ned_measure_param& roMParam, ng_ydist& ryMinTableHeight)
{
	ryMinTableHeight = 0;
	//reset left-side-space
	m_xLeftSideSpace = MAXLONG;

	cned_filter_children__<cned_tablesection> oSectionFilter(this, true, roMParam.is_printing());

	//inicjowanie pomiaru
	while (!oSectionFilter.is_end())
	{
		oSectionFilter.get_element()->init_measure_columns();
		oSectionFilter.move_next();
	}
	if (_get_next_header_ident() != NEDID_NOTHING)
	{
		get_next_header()->init_measure_columns();
	}
	if (_get_prev_footer_ident() != NEDID_NOTHING)
	{
		get_prev_footer()->init_measure_columns();
	}

	for (long nColNr = 0; nColNr < get_col_count(); nColNr++)
	{
		ng_ydist yMinColHeight = 0;
		get_column(nColNr).reset();

		//zmierz kolumnê we wszystkich sekcjach
		oSectionFilter.restart_at(get_first_child_ident());
		while (!oSectionFilter.is_end())
		{
			oSectionFilter.get_element()->measure_column(roMParam, nColNr, yMinColHeight);
			oSectionFilter.move_next();
		}
		if (_get_next_header_ident() != NEDID_NOTHING)
		{
			get_next_header()->measure_column(roMParam, nColNr, yMinColHeight);
		}
		if (_get_prev_footer_ident() != NEDID_NOTHING)
		{
			get_prev_footer()->measure_column(roMParam, nColNr, yMinColHeight);
		}

		ryMinTableHeight = max(ryMinTableHeight, yMinColHeight);
	}

	oSectionFilter.restart_at(get_first_child_ident());

	while (!oSectionFilter.is_end())
	{
		oSectionFilter.get_element()->finish_measure_columns();
		oSectionFilter.move_next();
	}
	if (_get_next_header_ident() != NEDID_NOTHING)
	{
		get_next_header()->finish_measure_columns();
	}
	if (_get_prev_footer_ident() != NEDID_NOTHING)
	{
		get_prev_footer()->finish_measure_columns();
	}

	//normalize left-side-space
	if (m_xLeftSideSpace == MAXLONG)		//no visible cells in table (or rendered table fragment)
	{
		m_xLeftSideSpace = 0;
	}
}

void cned_table::_compress_columns()
{
	/*
		Kompresja kolum mo¿e siê odbywaæ dopiero na koñcu,
		dlatego, ¿ê komórki o colspan > 1 mog¹ zmieniæ right_side_space
		kolumn po lewej stronie
	*/

	//uwzglêdnij czêœci wspólne w szerokoœciach minimalnych
	if (get_col_count() > 0)
	{
		column& roFirstTableCol = get_column(0);
		roFirstTableCol.normalize_right_side_space();
		if (roFirstTableCol.get_owns_cells())
		{
			roFirstTableCol.m_xMinWidth -= (get_left_side_space() + roFirstTableCol.get_right_side_space());
		}
		else
		{
			ASSERT(roFirstTableCol.get_min_width() == 0);
		}

		ASSERT(roFirstTableCol.get_min_width() >= 0);
	}
	for (long nCol = 1; nCol < get_col_count(); nCol++)
	{
		column& roTableCol = get_column(nCol);
		roTableCol.normalize_right_side_space();
		if (roTableCol.get_owns_cells())
		{
			roTableCol.m_xMinWidth -= (get_column(nCol - 1).get_right_side_space() + roTableCol.get_right_side_space());
		}
		else
		{
			ASSERT(roTableCol.get_min_width() == 0);
		}

		//ASSERT(roTableCol.get_min_width() >= 0);
	}

	//od teraz minimalne szerokoœci nie zawieraj¹ wspólnego obszaru ramek
}

void cned_table::_compute_final_col_widths(ng_xdist dxAvailWidth, bool& rbResetAllRows, ng_xdist& rdxTotalWidth)
{
	ASSERT(!is_measure_pending());

#ifdef _DEBUG
	CDebugTimeMeter oDTM("_compute_final_col_widths", 1);
#endif

	//ASSERT(m_oMetrics.get_minimal_width() <= dxAvailWidth);

	//oblicz now¹ szerokoœæ z uwzglêdnieniem dostêpnego miejsca
	rdxTotalWidth = get_left_side_space();
	rbResetAllRows = false;

	CArray<ng_xdist, ng_xdist> oColWidthArray;
	oColWidthArray.SetSize(get_col_count());

	//zawsze wype³nij wartoœciami minimalnymi
	for (long nCol = 0; nCol < get_col_count(); nCol++)
	{
		oColWidthArray[nCol] = get_column(nCol).get_min_width();
	}

	//---------------- analiza atrybutów ca³ej tabelki --------------------
	ng_xdist dxEfectiveWidth = 0;

	//c) podany rozmiar tabelki - w ramach tej szerokoœci rozci¹gamy proporcjonalnie
	if (is_normal_width_value(get_prop_extwidth()))
	{
		dxEfectiveWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(), 0)).get_dx();
	}
	else
	{
		//b) tryb rozciagania propocjonalnego do dostêpnej szerokoœci - atrybut 'auto' = 'max'
		//a) tryb minimalnej szerokoœci - gdy tabelka ma atrybut 'min'

		dxEfectiveWidth = dxAvailWidth;
	}

	//normalizacja
	dxEfectiveWidth = max(dxEfectiveWidth, m_oMetrics.get_minimal_width());
	dxEfectiveWidth = min(dxEfectiveWidth, dxAvailWidth);

	//---------------- analiza atrybutów kolumn ------------------------

	ng_xdist dxFlexSpace = dxEfectiveWidth - m_oMetrics.get_minimal_width();
	//ASSERT(dxFlexSpace >= 0);

	if (dxFlexSpace < 0)
	{
		dxFlexSpace = 0;
	}

	//przydzielanie szerokoœci kolumnom 'zadeklarowanym'
	//i przy okazji wyszukanie kolumny z atrybutem max
	long nFirstMaxCol = -1;		//kolumna z atrybutem 'max'
	long nLastAutoCol = -1;		//ostatnia kolumna z atrybutem 'auto'
	long nFlexWeight = 0;
	for (long nCol = 0; nCol < get_col_count(); nCol++)
	{
		const column& roTableCol = get_column(nCol);
		if (is_normal_width_value(roTableCol.get_prop_extwidth()))
		{

			ng_xdist dxDeclWidth = get_manager()->to_internal(ng_size(roTableCol.get_prop_extwidth(), 0)).get_dx();
			//nie za w¹sko
			dxDeclWidth = max(dxDeclWidth, roTableCol.get_min_width());
			//nie za szeroko
			if (dxDeclWidth > dxFlexSpace + roTableCol.get_min_width())
			{
				dxDeclWidth = roTableCol.get_min_width() + dxFlexSpace;
			}
			oColWidthArray[nCol] = dxDeclWidth;
			dxFlexSpace -= dxDeclWidth - roTableCol.get_min_width();
			ASSERT(dxFlexSpace >= 0);
		}
		else
		{
			if (is_maximal_width_value(roTableCol.get_prop_extwidth()))
			{
				if (nFirstMaxCol == -1)
				{
					nFirstMaxCol = nCol;
				}
			}
			else
			{
				if (!is_minimal_width_value(roTableCol.get_prop_extwidth()))
				{
					ASSERT(is_auto_width_value(roTableCol.get_prop_extwidth()));
					nFlexWeight += roTableCol.get_weight();
					nLastAutoCol = nCol;
				}
			}
		}
	}
	ASSERT(dxFlexSpace >= 0);

	//b) tryb rozciagania propocjonalnego do dostêpnej szerokoœci - atrybut 'auto' = 'max'
	if (!is_minimal_width_value(get_prop_extwidth()))
	{
		if (nFirstMaxCol != -1)		//daj kolumnie 'max' ca³a woln¹ przestrzeñ
		{
			oColWidthArray[nFirstMaxCol] += dxFlexSpace;
		}
		else
		{
			//tryb proporcjonalny
			if (dxFlexSpace > 0)	//jest jeszcze coœ wolnego do rozdysponowania
			{
				long nFactor = 0;
				if (nFlexWeight > 0)
				{
					nFactor = long(__int64(100000) * __int64(dxFlexSpace) / __int64(nFlexWeight));
					ASSERT(nFactor >= 0);
					if (nFactor > 0)
					{
						for (long nCol = 0; nCol < get_col_count(); nCol++)
						{
							const column& roTableCol = get_column(nCol);
							if (is_auto_width_value(roTableCol.get_prop_extwidth()))
							{
								ng_xdist dxColExt = ng_xdist(long(
									__int64(roTableCol.get_weight()) * __int64(nFactor) / __int64(100000)
									));
								oColWidthArray[nCol] += dxColExt;
								dxFlexSpace -= dxColExt;
							}
						}

						ASSERT(dxFlexSpace >= 0);
						//ostatnia auto dostajae dodatkowo resztê z zaokr¹gleñ
						if (nLastAutoCol != -1)
						{
							oColWidthArray[nLastAutoCol] += dxFlexSpace;
						}
					}
				}
				else	//tryb równych szerokoœci bo nie znamy wag
				{
					if (get_col_count() > 0)
					{
						ng_xdist dxColExt = dxFlexSpace / get_col_count();
						for (long nCol = 0; nCol < get_col_count() - 1; nCol++)
						{
							const column& roTableCol = get_column(nCol);
							if (is_auto_width_value(roTableCol.get_prop_extwidth()))
							{
								oColWidthArray[nCol] += dxColExt;
								dxFlexSpace -= dxColExt;
							}
						}

						ASSERT(dxFlexSpace >= 0);
						//ostatnia auto resztê z zaokr¹gleñ i niezu¿yte przez kolumny nieautomatyczne
						if (nLastAutoCol != -1)
						{
							oColWidthArray[nLastAutoCol] += dxFlexSpace;
						}
					}
				}
			}
		}
	}

	//zastosuj wyliczone szerokoœci
	for (long nCol = 0; nCol < get_col_count(); nCol++)
	{
		column& roTableCol = get_column(nCol);

		ASSERT(oColWidthArray[nCol] >= roTableCol.get_min_width());

		if (oColWidthArray[nCol] != roTableCol.get_actual_col_width())
		{
			roTableCol.set_actual_col_width(oColWidthArray[nCol]);
			rbResetAllRows = true;
		}

#ifdef _DEBUG0

		{
			ng_xdist dxDeclWidth = -1;
			if (is_normal_width_value(roTableCol.get_prop_extwidth()))
			{
				dxDeclWidth = get_manager()->to_internal(ng_size(roTableCol.get_prop_extwidth(), 0)).get_dx();
	}
			TRACE("table[%d]:col[%d],declared=%d,actual=%d\n", get_ident(), nCol, dxDeclWidth,
				roTableCol.get_actual_col_width());
}

#endif

		rdxTotalWidth += oColWidthArray[nCol] + roTableCol.get_right_side_space();
	}
	//ASSERT(rdxTotalWidth <= dxAvailWidth);
}


//--------------------- rendering (public interface) --------------------------

void cned_table::get_children_metrics(const ned_measure_param& roMParam)
{
	ASSERT(!get_prop_hidden());
	_initiate_allocations(roMParam.is_printing());

	//1. collect information from cells
	ng_ydist yMinTableHeight = 0;
	_measure_columns(roMParam, yMinTableHeight);

	//2. "compress" common border space
	_compress_columns();

	//3. analyze information
	ng_xdist dxTotalMinWidth = get_left_side_space();
	long nTotalWeight = 0;
	for (long nCol = 0; nCol < get_col_count(); nCol++)
	{
		const column& roTableCol = get_column(nCol);
		dxTotalMinWidth += roTableCol.get_min_width() + roTableCol.get_right_side_space();
		nTotalWeight += roTableCol.get_weight();
	}

	ASSERT(nTotalWeight >= 0);
	ASSERT(dxTotalMinWidth >= 0);
	ASSERT(yMinTableHeight >= 0);

	m_oMetrics.update(dxTotalMinWidth, yMinTableHeight, nTotalWeight);
}

void cned_table::render(cned_renderer_& roRenderer)
{
	ASSERT(!is_measure_pending());
	ASSERT(!get_prop_hidden());

	ng_size oFullVirtualTableSize;
	ng_size oRequestedTableSize;

	//zapewnij szerokoœæ
	roRenderer.ensure_width(m_oMetrics.get_minimal_width());

	//oblicz nowe szerokoœci kolumn i szerokoœæ tabelki z uwzglêdnieniem aktualnie dostêpnego miejsca
	ng_xdist dxTotalWidth = 0;
	bool bResetAll = false;
	_compute_final_col_widths(roRenderer.get_current_width(), bResetAll, dxTotalWidth);

	cned_filter_children__<cned_tablesection> oSectionFilter(this, true, roRenderer.is_printing());
	ng_ycoord yOffsetInTable = 0;

	//nie by³o zmiany szerokoœci - spróbuj pomin¹æ 'dobre' sekcje
	//ned_to_do: restartowanie renderingu
	if (false && !bResetAll && dxTotalWidth == m_oActualSize.get_dx())
	{
		if (_get_last_measured() != NEDID_NOTHING)
		{
			while (!oSectionFilter.is_end())
			{
				yOffsetInTable += oSectionFilter.get_element()->get_actual_size().get_dy();
				if (oSectionFilter.get_ident() == _get_last_measured())
				{
					//nastêpna sekcja jest nieprawid³owa
					oSectionFilter.move_next();
					break;
				}
				oSectionFilter.move_next();
			}
		}
	}

	cned_column_renderer oSectionRenderer(roRenderer, ng_point(0, yOffsetInTable), dxTotalWidth);

	//renderowanie poszczególnych sekcji
	while (!oSectionFilter.is_end())
	{
		if (bResetAll)
		{
			//ned_to_do: reset wszystkie wiersze
		}

		oSectionFilter.get_element()->render(oSectionRenderer);
		oSectionFilter.move_next();
	}

	//--- w trybie wydruku / printpreview -- chcemy je zrenderowac aby mialy wysokosæ

	if (roRenderer.is_printing())
	{
		cned_column_renderer oNxtHdrPrvFtrRenderer(roRenderer, ng_point(0, yOffsetInTable), dxTotalWidth);

		if (_get_next_header_ident() != NEDID_NOTHING)
		{
			get_next_header()->render(oNxtHdrPrvFtrRenderer);
		}
		if (_get_prev_footer_ident() != NEDID_NOTHING)
		{
			get_prev_footer()->render(oNxtHdrPrvFtrRenderer);
		}
	}

	ng_size oTableSize(dxTotalWidth, _get_std_height_for_rendering(oSectionRenderer.get_current_pos().get_y()));
	roRenderer.allocate_rect(get_ident(), -1, oTableSize, m_oActualSize, m_oVectorSize);
	_validate_last_measured(NEDID_LAST);
}

