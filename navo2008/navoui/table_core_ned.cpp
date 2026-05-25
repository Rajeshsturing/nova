/*
	NAVO Enterprise 2003
	2003-03-30

	navo enhanced display (NED)

	ned_table
		tabelka
	
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

cned_table::cned_table(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis):
	cned_rect_container_(poManager,eType,idThis),
	m_idNextHeader(NEDID_NOTHING),
	m_idPrevFooter(NEDID_NOTHING),
	m_xLeftSideSpace(MAXLONG)
{
	//init section array with empty slots
	for(ened_tablesection_enum eIter = ned_tse_min; eIter <= ned_tse_max; eIter = ened_tablesection_enum(eIter+1))
	{
		m_idSectionArray[ eIter ] = NEDID_NOTHING;
	}
}

void cned_table::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
}

void cned_table::insert_col_into_sections(long nCol)
{
	cned_filter_children__<cned_tablesection> oTableSectionFilter(this,false,false);
	while(!oTableSectionFilter.is_end())
	{
		oTableSectionFilter.get_element()->external_insert_col(nCol);
		oTableSectionFilter.move_next();
	}

	if(_get_next_header_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_next_header()->external_insert_col(nCol);
	}
	if(_get_prev_footer_ident() != NEDID_NOTHING)	//only if already exists
	{
		get_prev_footer()->external_insert_col(nCol);
	}

	m_oColArray.InsertAt(nCol,column());
}

void cned_table::remove_children(bool bWhileRemovingItself)
{
	ASSERT(bWhileRemovingItself);	//nie powinno siê wo³aæ usuwania sekcji

	cned_filter_children__<cned_tablesection> oTableSectionFilter(this,false,false);
	while(!oTableSectionFilter.is_end())
	{
		SCP<cned_tablesection> poTableSectionSP = oTableSectionFilter.get_element();
		poTableSectionSP->remove_children(true);
		//sekcja nie ma nigdy focusu
		ASSERT(!poTableSectionSP->get_prop_focus());
		get_manager()->_remove_element(poTableSectionSP->get_ident());

		oTableSectionFilter.move_next();
	}

	//reset section array with empty slots
	for(ened_tablesection_enum eIter = ned_tse_min; eIter <= ned_tse_max; eIter = ened_tablesection_enum(eIter+1))
	{
		m_idSectionArray[ eIter ] = NEDID_NOTHING;
	}
}

//-------------------------- section construction support -----------------------------------
SCP<cned_element> cned_table::_internal_create_section(ened_element_type eElementType,ened_tablesection_enum eSection,const ned_ident idSection)
{
#ifdef _DEBUG
	if(eSection == ned_tse_body)
	{
		if(get_type() == ned_table)
		{
			ASSERT(eElementType == ned_tablebodysection);
		}
		else
		{
			ASSERT(get_type() == ned_grid);
			ASSERT(eElementType == ned_spreadbodysection);
		}
	}
#endif

	//create
	SCP <cned_element> poElementSP = get_manager()->_create_element(eElementType,idSection);
	ASSERT(poElementSP.PointsObject());
	
	//init
	poElementSP->_set_container(NewSCP<cned_container>(this,true));
	poElementSP->apply_attributes(get_current_attributes());
	
	if(eSection != ned_tse_pattern && eSection != ned_tse_next_hdr && eSection != ned_tse_prev_ftr)
	{
		ASSERT(eElementType != ned_spreadpatternsection);
		m_idSectionArray[ eSection ] = poElementSP->get_ident();

		_link_element(poElementSP->get_ident(),
			(eSection == ned_tse_min) ? NEDID_NOTHING : 
				_get_section_ident(ened_tablesection_enum(eSection-1)));

		on_child_inserted(poElementSP);
		_size_info_dirty();
	}
	
	//add columns
	SCP<cned_tablesection> poTableSectionSP = scp_cast_ui<cned_tablesection>(poElementSP);
	for(long nCol = 0; nCol < get_col_count(); nCol++)
	{
		poTableSectionSP->external_insert_col(nCol);
	}

	ASSERT(poTableSectionSP->get_col_count() == get_col_count());
	return poElementSP;
}

void cned_table::_create_missing_sections(ened_tablesection_enum eSection)
{
	//create previous sections if not already created
	for(ened_tablesection_enum eIter = ned_tse_min; eIter < eSection; eIter = ened_tablesection_enum(eIter+1))
	{
		if(_get_section_ident(eIter) == NEDID_NOTHING)
		{
			_internal_create_section((eIter == ned_tse_body) ? ned_tablebodysection : ned_tablesection,	
				eIter,NEDID_NOTHING);
		}
	}
}

//------------------------------------------------
SCP<cned_element> cned_table::create_section(ened_tablesection_enum eSection,const ned_ident idSection)
{
	ASSERT(_get_section_ident(eSection) == NEDID_NOTHING);	//call only once

	_create_missing_sections(eSection);

	//now create requested section

	return _internal_create_section((eSection == ned_tse_body) ? ned_tablebodysection : ned_tablesection,
			eSection,idSection);
}

SCP<cned_element> cned_table::create_next_header(const ned_ident idSection)
{
	ASSERT(_get_next_header_ident() == NEDID_NOTHING);
	
	SCP<cned_element> poNextHeaderSectionSP = 
		_internal_create_section(ned_tablesection,ned_tse_next_hdr,idSection);
	
	m_idNextHeader = poNextHeaderSectionSP->get_ident();

	return poNextHeaderSectionSP;
}

SCP<cned_element> cned_table::create_prev_footer(const ned_ident idSection)
{
	ASSERT(_get_prev_footer_ident() == NEDID_NOTHING);
	
	SCP<cned_element> poPrevFooterSectionSP =
		_internal_create_section(ned_tablesection,ned_tse_next_hdr,idSection);
	
	m_idPrevFooter = poPrevFooterSectionSP->get_ident();

	return poPrevFooterSectionSP;
}


//-------------- fill clone -------------- -------------- -------
void cned_table::fill_clone(cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	//dont call direct base class's fill-clone!

	cned_table * poClonedTable = cast_ui<cned_table>(poDestination);
	poClonedTable->create_all_missing_sections();

	cned_filter_children__<cned_tablesection> oSectionFilter(this,true,true);
	cned_filter_children__<cned_tablesection> oDestSectionFilter(poClonedTable,true,true);

	while(!oSectionFilter.is_end())
	{
		oSectionFilter.get_element()->fill_clone(oDestSectionFilter.get_element());
		oSectionFilter.move_next();
		oDestSectionFilter.move_next();
	}
}


void cned_table::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oElementRect(oPaintPoint,m_oActualSize);

	if(oElementRect.get_top() > roSplitInfo.get_max_bottom())
	{
		//next page -> finish current
		roSplitInfo.next_y_page();
	}
	else
	{
		//jesli wystaje -> musimy sprawdzic dzieci
		//jeœli nie -> wszystko w porz¹dku

		if(
			(get_manager()->get_form_feed_count() != 0) || 
			(oElementRect.get_bottom() > roSplitInfo.get_max_bottom())
		  )
		{
			ng_ydist dyHeaderHeight = get_section(ned_tse_first_header)->get_actual_size().get_dy();
			ng_ydist dyFooterHeight = 0;

			if(_get_prev_footer_ident() != NEDID_NOTHING)
			{
				ASSERT(get_prev_footer().PointsObject());
				dyFooterHeight = get_prev_footer()->get_actual_size().get_dy();
			}			

			//redukujemy dostêpn¹ wysokoœæ o rozmiary headera i footera
			const ng_ydist yNextPartMaxHeight = 
				roSplitInfo.get_next_part_max_height() - dyHeaderHeight - dyFooterHeight;
			
			ng_ycoord yFirstParMaxBottom = 
				roSplitInfo.get_actual_bottom() - dyFooterHeight;

			//przypadek ma³ej iloœci miejsca -> przenosimy siê na nastêpn¹ stronê
			if(yFirstParMaxBottom <= 0)
			{
				roSplitInfo.next_y_page();
				yFirstParMaxBottom = roSplitInfo.get_actual_bottom() - oElementRect.get_top() - dyHeaderHeight - dyFooterHeight;
				ASSERT(yFirstParMaxBottom > 0);
			}

			if(oElementRect.get_bottom() > roSplitInfo.get_max_bottom())
			{
				cpb_split_info oTableSplitInfo(roSplitInfo.get_storage(),
					0,yFirstParMaxBottom,
					yNextPartMaxHeight,roSplitInfo.get_next_part_max_width());
				
				get_section(ned_tse_body)->update_split_info(oPaintPoint,oTableSplitInfo);

				roSplitInfo.propagate(oTableSplitInfo.get_actual_bottom(),
					oTableSplitInfo.get_max_bottom());
			}
		}
	}
	
	//--------------------------------------------------------------------------
	//------------------------------ podzia³ poziomy ---------------------------
	//--------------------------------------------------------------------------
	
	const long nColCount = get_col_count();
	ng_xcoord xCurrX = oPaintPoint.get_x() + get_left_side_space();

	for(long nColNr = 0; nColNr < nColCount; nColNr++)
	{
		cned_table::column  & roTableCol = get_column(nColNr);

		ng_xdist xColWidth = roTableCol.get_actual_col_width();
		ng_xdist xRightSpace = roTableCol.get_right_side_space();

		roSplitInfo.update_max_right(xCurrX);

		xCurrX += xColWidth + xRightSpace;
	}
}

//==================================================
// specjalizowany split manager do stosowania z headerami
// footerami tabelek. specjalizacja polega na tym, ¿e
// zwracana jest zawsze ustalona yAreaY
//--------------------------------------------------

class cpb_tbl_hdr_ftr_sm : public cpb_split_manager
{
public:
	cpb_tbl_hdr_ftr_sm(cpb_split_manager & roParentSplitManager,long yAreaY,ng_ycoord yTop);
	virtual long find_y_area(ng_ycoord yPosition);
	virtual SCP<cned_element> get_clone(long xAreaX,long yAreaY,ned_ident idElement);
	virtual void register_clone(long xAreaX,long yAreaY,
		ned_ident idOriginalElement,ned_ident idClonedElement);
	virtual void add_event_param(const cpb_on_split_event_param & roEventParam);
private:
	long m_yAreaY;
	ng_ycoord m_yTop;
	cpb_split_manager & m_roParentSplitManager;
};

cpb_tbl_hdr_ftr_sm::cpb_tbl_hdr_ftr_sm(cpb_split_manager & roParentSplitManager,long yAreaY,ng_ycoord yTop) :
	cpb_split_manager(roParentSplitManager.get_storage()),
	m_roParentSplitManager(roParentSplitManager),
	m_yAreaY(yAreaY),
	m_yTop(yTop)
{
}

long cpb_tbl_hdr_ftr_sm::find_y_area(ng_ycoord)
{
	return m_yAreaY;
}

SCP<cned_element> cpb_tbl_hdr_ftr_sm::get_clone(long xAreaX,long yAreaY,ned_ident idElement)
{
	return m_roParentSplitManager.get_clone(xAreaX,yAreaY,idElement);
}

void cpb_tbl_hdr_ftr_sm::register_clone(long xAreaX,long yAreaY,
		ned_ident idOriginalElement,ned_ident idClonedElement)
{
	m_roParentSplitManager.register_clone(xAreaX,yAreaY,idOriginalElement,idClonedElement);
}

void cpb_tbl_hdr_ftr_sm::add_event_param(const cpb_on_split_event_param & roEventParam)
{
	m_roParentSplitManager.add_event_param(roEventParam);
}

//==================================================

void cned_table::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager)
{
	if(get_col_count() == 0)
	{
		return;
	}

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oElementRect(oPaintPoint,m_oActualSize);
	
	//==================================================
	// part 1 - klonowanie tabelek
	//==================================================

	long xAreaLeft = roSplitManager.find_x_area(oElementRect.get_left());
	long xAreaRight = roSplitManager.find_x_area(oElementRect.get_right());
	long yAreaTop = roSplitManager.find_y_area(oElementRect.get_top());
	long yAreaBottom = roSplitManager.find_y_area(oElementRect.get_bottom());

	ng_ycoord yFirstPartTop = roSplitManager.get_y_area_top(yAreaTop);

	//-- pierwsza strona [xAreaLeft,yAreaTop] - pozycjonowana w pionie i poziomie
	SCP<cned_element> poClonedTableSP = _make_clone_split(roSplitManager,xAreaLeft,yAreaTop);
	TRACE("CLONE:TABLEa %d to [%d,%d] as %d\n", get_ident(),xAreaLeft,yAreaTop,poClonedTableSP->get_ident());

	//--- po³o¿enie wzglêdem kontenera we wsp. external
	//
	//to jest offset od pocz¹tku kontenera, ale jeœli w naszym kontenerze nast¹pi³ podzia³ przed nami
	//to pomniejszony o czêœæ 'powy¿ej' podzia³u (ta która pozosta³a na poprzedniej stronie)

	ng_point oLocalPoint;
	oLocalPoint.offset(0,m_oVectorSize.get_dy() - max(0,yFirstPartTop - roCurrentPoint.get_y()));
	ASSERT(oLocalPoint.get_y() >= 0);
	ng_point oExtLocalPoint = get_manager()->to_external(oLocalPoint);
	ned_position oPosition;
	oPosition.set_top(oExtLocalPoint.get_y());
	
	poClonedTableSP->set_decl_position(oPosition);

	//-- kolejne strony po prawej - pozycjonowane w pionie
	{
		for(long xArea = xAreaLeft + 1; xArea <= xAreaRight; xArea++)
		{
			SCP<cned_element> poClonedTableSP = _make_clone_split(roSplitManager,xArea,yAreaTop);
			poClonedTableSP->set_decl_position(oPosition);
			
			TRACE("CLONE:TABLEb %d to [%d,%d] as %d\n", get_ident(),xArea,yAreaTop,poClonedTableSP->get_ident());
		}
	}

	{
		//-- kolejne strony w dó³
		for(long yArea = yAreaTop + 1; yArea <= yAreaBottom; yArea++)
		{
			for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
			{
				_make_clone_split(roSplitManager,xArea,yArea);		
				
				TRACE("CLONE:TABLEc %d to [%d,%d] as %d\n", get_ident(),xArea,yArea,poClonedTableSP->get_ident());
			}
		}
	}
	
	//==================================================
	// part 2 - ustalanie podzia³u kolumn
	//==================================================
	{
		const long nColCount = get_col_count();
		ng_xcoord xCurrX = oPaintPoint.get_x() + get_left_side_space();

		for(long nColNr = 0; nColNr < nColCount; nColNr++)
		{
			cned_table::column  & roTableCol = get_column(nColNr);

			ng_xdist xColWidth = roTableCol.get_actual_col_width();
			ng_xdist xRightSpace = roTableCol.get_right_side_space();
	
			long xColAreaLeft = roSplitManager.find_x_area(xCurrX);
			xCurrX += xColWidth;
			
			long xColAreaRight = roSplitManager.find_x_area(xCurrX);
			roTableCol.set_split_areas(xColAreaLeft,xColAreaRight);

			xCurrX += xRightSpace;
		}
	}

	//==================================================
	// part 3 - klonowanie body
	//==================================================

	get_section(ned_tse_body)->make_split(oPaintPoint,roSplitManager);
	
	//==================================================
	// part 4 - klonowanie headerów / footerów
	//==================================================

	//------ klonuj header dla 1-szej strony
	{
		cpb_tbl_hdr_ftr_sm oTableHFSplitManager(roSplitManager,yAreaTop,yFirstPartTop);
		get_section(ned_tse_first_header)->make_split(oPaintPoint,oTableHFSplitManager);
	}
	//---- nastêpne strony - jesli jest <tnexthead> to u¿yj
	//---- jeœli nie to u¿yj <thead>
	{
		SCP<cned_tablesection> poNextHeaderSP;
		
		if(_get_next_header_ident() == NEDID_NOTHING)
		{
			poNextHeaderSP = get_section(ned_tse_first_header);
		}
		else
		{
			poNextHeaderSP = get_next_header();
		}
		ASSERT(poNextHeaderSP.PointsObject());
		
		for(long yArea = yAreaTop + 1; yArea <= yAreaBottom; yArea++)
		{
			cpb_tbl_hdr_ftr_sm oTableHFSplitManager(roSplitManager,yArea,yFirstPartTop);
			poNextHeaderSP->make_split(oPaintPoint,oTableHFSplitManager);
		}
	}
	//--- skopiuj footery ---
	{
		if(_get_prev_footer_ident() != NEDID_NOTHING)
		{
			SCP<cned_tablesection> poPrevFootSP = get_prev_footer();
			ASSERT(poPrevFootSP.PointsObject());

			//--- wszystkie strony poza ostatni¹ - u¿yj <tprevfoot> jeœli jest
			//--- albo nic jesli nie ma
			for(long yArea = yAreaTop; yArea < yAreaBottom; yArea++)
			{
				cpb_tbl_hdr_ftr_sm oTableHFSplitManager(roSplitManager,yArea,yFirstPartTop);
				poPrevFootSP->make_split(oPaintPoint,oTableHFSplitManager);
			}
		}
		
	}
	{
		//--- ostatnia strona - u¿yj <tfoot>
		cpb_tbl_hdr_ftr_sm oTableHFSplitManager(roSplitManager,yAreaBottom,yFirstPartTop);
		get_section(ned_tse_last_footer)->make_split(oPaintPoint,oTableHFSplitManager);
	}

	//==================================================
	// part 5 - usuwanie pustych wierszy
	//
	//is_visually_empty dla wierszy powsta³ych w wyniku podzia³u,
	//1-szy, ostatni
	//1-sza ostatnia kolumna
	//
	//==================================================
	if(yAreaTop < yAreaBottom)
	{
		for(long yArea = yAreaTop; yArea <= yAreaBottom; yArea++)
		{
			//-przebieg 1 - sprawdŸ czy usuwac ostatni wiersz
			bool bRemoveLastRow = true;
			bool bRemoveFirstRow = true;
			for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
			{
				SCP<cned_element> poClonedBodySP = roSplitManager.get_clone(xArea,yArea,_get_section_ident(ned_tse_body));
				ASSERT(poClonedBodySP.PointsObject());
				
				cned_tablesection * poClonedBody = cast_ui<cned_tablesection>(poClonedBodySP);
				ASSERT(poClonedBody != NULL);
				ned_ident idLastRow = poClonedBody->get_last_child_ident();
				if(idLastRow == NEDID_NOTHING)
				{
					bRemoveLastRow = false;
				}
				else
				{
					if(bRemoveLastRow)
					{
						bRemoveLastRow = poClonedBody->get_element_on_ident(idLastRow)->is_visually_empty();
					}
				}
				
				ned_ident idFirstRow = poClonedBody->get_first_child_ident();
				if(idFirstRow == NEDID_NOTHING)
				{
					bRemoveFirstRow = false;
				}
				else
				{
					if(bRemoveFirstRow)
					{
						bRemoveFirstRow = poClonedBody->get_element_on_ident(idFirstRow)->is_visually_empty();
					}
				}
			}
			if(bRemoveLastRow)
			{
				//-przebieg 2 - usun ostatni wiersz
				for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
				{
					SCP<cned_element> poClonedBodySP = roSplitManager.get_clone(xArea,yArea,_get_section_ident(ned_tse_body));
					ASSERT(poClonedBodySP.PointsObject());
					cned_tablesection * poClonedBody = cast_ui<cned_tablesection>(poClonedBodySP);
					ASSERT(poClonedBody != NULL);
					ned_ident idLastRow = poClonedBody->get_last_child_ident();
					if(idLastRow != NEDID_NOTHING)
					{
						poClonedBody->remove_element(idLastRow);
						TRACE("TABLE VISEMPTY: removed last row in table %d at area %d,%d\n",get_ident(),xArea,yArea);
					}
				}
			}
			if(bRemoveFirstRow)
			{
				//-przebieg 2 - usun pierwszy wiersz
				for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
				{
					SCP<cned_element> poClonedBodySP = roSplitManager.get_clone(xArea,yArea,_get_section_ident(ned_tse_body));
					ASSERT(poClonedBodySP.PointsObject());
					cned_tablesection * poClonedBody = cast_ui<cned_tablesection>(poClonedBodySP);
					ASSERT(poClonedBody != NULL);
					ned_ident idFirstRow = poClonedBody->get_first_child_ident();
					if(idFirstRow != NEDID_NOTHING)
					{
						poClonedBody->remove_element(idFirstRow);
						TRACE("TABLE VISEMPTY: removed first row in table %d at area %d,%d\n",get_ident(),xArea,yArea);
					}
				}
			}
		}
	}
	
	//==================================================
	// part 6 - rejestrowanie custom eventów
	//==================================================
	{
		ng_string oCustomFunctionName;
		oCustomFunctionName.Format("c%d_on_table_split",get_ident());

		for(long yArea = yAreaTop; yArea <= yAreaBottom; yArea++)
		{
			for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
			{
				SCP<cned_element> poClonedTableSP = roSplitManager.get_clone(xArea,yArea,get_ident());

				cpb_on_split_event_param oOnTableSplitEventParam;
				
					oOnTableSplitEventParam.m_oFunctionNameString = oCustomFunctionName;
					oOnTableSplitEventParam.m_poClonedElementSP = poClonedTableSP;
					oOnTableSplitEventParam.m_xAreaX = xArea;
					oOnTableSplitEventParam.m_yAreaY = yArea;
					oOnTableSplitEventParam.m_xCount = roSplitManager.get_storage().get_x_count();
					oOnTableSplitEventParam.m_yCount = roSplitManager.get_storage().get_y_count();
			
				roSplitManager.add_event_param(oOnTableSplitEventParam);
			}
		}
	}
}

void cned_table::fill_clone_split(cpb_split_manager & roSplitManager,
								  long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_rect_container_::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	
	cned_table * poClonedTable = cast_ui<cned_table>(poDestination);
	poClonedTable->create_all_missing_sections();

	for(ened_tablesection_enum eIter = ned_tse_min; eIter <= ned_tse_max; eIter = ened_tablesection_enum(eIter+1))
	{
		roSplitManager.register_clone(xAreaX,yAreaY,
			_get_section_ident(eIter),poClonedTable->get_section(eIter)->get_ident());
	}
	
	//jeœli istnieje next header - to go TE¯ mapujemy na header klona !
	//analogicznie z prev-footerem

	if(_get_next_header_ident() != NEDID_NOTHING)
	{
		roSplitManager.register_clone(xAreaX,yAreaY,
			_get_next_header_ident(),poClonedTable->get_section(ned_tse_first_header)->get_ident());
	}
	if(_get_prev_footer_ident() != NEDID_NOTHING)
	{
		roSplitManager.register_clone(xAreaX,yAreaY,
			_get_prev_footer_ident(),poClonedTable->get_section(ned_tse_last_footer)->get_ident());
	}
}
