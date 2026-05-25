/*
	NAVO Enterprise 2003
	2003-04-04

	navo enhanced display (NED)

	ned_spreadbodysection / <tbody> 
		sekcja body grida
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "scroll_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "grid_ned.h"
#include "table_bodysection_ned.h"
#include "tablerow_ned.h"
#include "pattern_tablerow_ned.h"
#include "grid_bodysection_ned.h"
#include "tablecell_ned.h"
#include "CommandList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

class cned_drag_info_grid_row : public cned_drag_info__
{
public:
	cned_drag_info_grid_row(const ng_point & roStartingArenaPoint,SCP<cned_tablerow> poStartingTableRowSP);
	virtual bool on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
	virtual bool on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
private:

	ng_point m_oLastPoint;
	SCP<cned_tablerow> m_poStartingTableRowSP;
};

//------------- child management ----------

void cned_grid_bodysection::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	ASSERT(rpoChildSP.PointsObject());
	ASSERT(rpoChildSP->get_container().PointsObject());
	
	//ustaw property 'keepline'
	//tylko dzieci naszych dzieci (wnuki) - inne tablecell w subtabelkach nas nie obchodz¹
	if(rpoChildSP->get_container()->get_container_ident() == get_ident())	
	{
		ASSERT(rpoChildSP->get_type() == ned_tablecell);
		
		cned_tablecell * poTableCell = cast_ui<cned_tablecell>(rpoChildSP);
		poTableCell->set_prop_keepline(true);
	}
	
	cned_table_bodysection::on_child_inserted(rpoChildSP);
}

SCP <cned_element> cned_grid_bodysection::insert_new_element(ened_element_type eType,const ned_ident idNew,const ned_ident idAfter)
{
	if(eType == ned_patterntablerow)
	{
		//robimy ma³y redirect
		return _get_grid()->get_pattern_section()->insert_new_element(ned_patterntablerow,idNew,idAfter);
	}
	else
	{
		return cned_table_bodysection::insert_new_element(eType,idNew,idAfter);
	}
}

/*
	procedura aktualizuje iloœæ wyœwietlanych ('roboczych') wierszy, pamiêtanych w sekcji
	na podstawie parametrów:
	- iloœæ wierszy danych m_nTotalDataRows
	- iloœæ max. wyœwietlanych wieszy m_nMaxVisibleDataRows
*/


bool cned_grid_bodysection::_update_working_rows_count()
{
	long nPatternRows = get_pattern_row_count();

	long nNewDataRowCount = min(1 + get_prop_total_datarows() - get_prop_first_visible_datarow(),
		get_prop_max_visible_datarows());

	ASSERT(nNewDataRowCount >= 1 && nNewDataRowCount <= get_prop_total_datarows() + 1);

	long nNewTableRowCount = nPatternRows * nNewDataRowCount;
	
	if(nNewTableRowCount > get_child_count())
	{
		while(nNewTableRowCount > get_child_count())
		{
			long nRowCount = get_child_count();
			for(long iter = 0; iter < nPatternRows; iter++)
			{
				SCP<cned_element> poDestRowSP;
				ASSERT(nRowCount + iter == get_child_count());
				poDestRowSP = insert_new_element(ned_tablerow,NEDID_NOTHING,NEDID_LAST);
				ASSERT(poDestRowSP.PointsObject());
				SCP<cned_pattern_tablerow> poPatternRowSP = get_pattern_row(iter);
				ASSERT(poPatternRowSP.PointsObject());
				poPatternRowSP->fill_clone(poDestRowSP);

				//pattern row jest z definicji ukryty
				//poka¿ skopiowane wiersze
				poDestRowSP->set_prop_hidden(false);
			}
		}
		return true;
	}
	else 
	{
		if(nNewTableRowCount < get_child_count())
		{
			while(nNewTableRowCount < get_child_count())
			{
				remove_element(get_last_child_ident());
			}
			return true;
		}
	}
	return false;	//no change
}

//----------------------------------------------------------------------------------------------
// rendering helper
//----------------------------------------------------------------------------------------------
ng_ydist cned_grid_bodysection::_correct_rendered_section_height(cned_renderer_ &,ng_ydist yHeight)
{
	if(get_prop_total_datarows() - get_prop_first_visible_datarow() < get_prop_min_visible_datarows())
	{
		long nPatternRowCount = get_pattern_row_count();
		
		ASSERT(get_child_count() % nPatternRowCount == 0);	//powinna byæ wielokrotnoœæ !!!
		ASSERT(get_prop_min_visible_datarows() >= 1);
	
		if(get_child_count() != 0)
		{
			yHeight =  yHeight * nPatternRowCount / get_child_count() * get_prop_min_visible_datarows();
		}
	}

	return _get_std_height_for_rendering(yHeight);
}

//--------------------------------------------------------------------
//--------------event handlers ---------------------------------------
//--------------------------------------------------------------------
void cned_grid_bodysection::_supply_datarownr_property(cned_tablerow * poTableRow,ned_action_result & roResult)
{
	long Index = 0;
	while(roResult.get_info(Index).PointsObject())
	{
		if(roResult.get_info(Index)->get_type() == eit_command)
		{
			ned_event_command * poEventCommand = dynamic_cast<ned_event_command *>(roResult.get_info(Index).Get());
			ASSERT(poEventCommand != NULL);
			ASSERT(poEventCommand->get_command().PointsObject());
			poEventCommand->get_command()->SetNumProp(PROPC_ROW,
				/*+1 for external numbering*/ 1 + 
				datarow_nr_from_table_row_nr(get_row_nr(poTableRow->get_ident())));
		}
		
		Index++;
	}
}

void cned_grid_bodysection::_build_in_on_event_keydown(long nTableRowNr,const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	long nNewFirstVisible = get_prop_first_visible_datarow();

	switch(roActionKBD.get_keycode())
	{
	case VK_UP:	//1 wiersz w górê
		{
			if(nTableRowNr == 0)
			{
				if(get_prop_first_visible_datarow() > 0)
				{
					//scroll up
					nNewFirstVisible = get_prop_first_visible_datarow() - 1;
				}

				roResult.set_processed();
			}
		}
		break;
	case VK_DOWN:	//1 wiersz w dó³
		{
			if(nTableRowNr == get_child_count() - 1)
			{
				if(datarow_nr_from_table_row_nr(nTableRowNr) < get_prop_total_datarows())
				{
					nNewFirstVisible = get_prop_first_visible_datarow() + 1;
				}
				roResult.set_processed();
			}
		}
		break;
	case VK_PRIOR:	//widoczna liczba wierszy w górê
		{
			long nPatternRowCount = get_pattern_row_count();
			ASSERT(nPatternRowCount > 0);
			nNewFirstVisible = get_prop_first_visible_datarow() - get_prop_max_visible_datarows();// / nPatternRowCount;
			nNewFirstVisible = max(0,nNewFirstVisible);
		}
		break;
	case VK_NEXT:	//widoczna liczba wierszy w dó³
		{
			long nPatternRowCount = get_pattern_row_count();
			ASSERT(nPatternRowCount > 0);
			nNewFirstVisible = get_prop_first_visible_datarow() + get_prop_max_visible_datarows();// / nPatternRowCount;
			
			nNewFirstVisible = min(nNewFirstVisible,
				max(0,
				1+get_prop_total_datarows() - get_prop_min_visible_datarows() - nTableRowNr));
		}
		break;
	case VK_INSERT:
		{
			if(roActionKBD.is_SHIFT())
			{
				//ned_to_do: ?? insert ??
				SCP<ned_event_row_operation> poEventRowOpSP = NewSCP(new ned_event_row_operation(get_container()->get_ident()));
				poEventRowOpSP->set_data_row_nr(datarow_nr_from_table_row_nr(nTableRowNr));
				poEventRowOpSP->set_operation(ned_event_row_operation::oper_insert);
				roResult.add_info(poEventRowOpSP);
			}
		}
		break;
	case VK_DELETE:
		{
			if(roActionKBD.is_SHIFT())
			{
				//ned_to_do: ?? delete ??
			}
		}
		break;
	case VK_RETURN:	//next
		{
			//ned_to_do: - przechodzenie do 1-szej kolumny nastêpnego wiersza, gdy jesteœmy na koñcu
			//ewentualny scroll

			//jesteœmy w ostatnim wierszu
			if(nTableRowNr == get_child_count() - 1 && datarow_nr_from_table_row_nr(nTableRowNr) < get_prop_total_datarows())
			{
				//sprawdŸ czy ma gdzie 'pójœæ' w tym wierszu

//				ASSERT(get_manager()->get_focus_element() != NUI_IDENT_NOTHING);
//				SCP<cnui_element> poElementSP = get_manager()->_get_element_on_ident(get_manager()->get_focus_element());
//				ASSERT(poElementSP.PointsObject());
				
//				nui_ident idNext = NUI_IDENT_NOTHING;
//				while(poElementSP.Get() != this)
//				{
//					ASSERT(poElementSP->get_container().PointsObject());
//					idNext = poElementSP->get_container()->find_element_next_prev(poElementSP->get_ident(),true);
//					if(idNext != NUI_IDENT_NOTHING)
//					{
//						break;
//					}
//					poElementSP = scp_cast_ui<cnui_element>(poElementSP->get_container());
//					ASSERT(poElementSP.PointsObject());
//				}
//				if(idNext == NUI_IDENT_NOTHING)
//				{
					nNewFirstVisible = get_prop_first_visible_datarow() + 1;
					SCP<cned_tablerow> poLastRowSP = scp_cast_ui<cned_tablerow>(get_element_on_ident(get_last_child_ident()));
					ned_ident idFirstInLastRow = poLastRowSP->find_element_next_prev(NEDID_NOTHING,true);
					if(idFirstInLastRow != NEDID_NOTHING)
					{
						get_manager()->_mark_new_focus_element(idFirstInLastRow);
					}
//				}
			}
		}
		break;
	}

	if(nNewFirstVisible != get_prop_first_visible_datarow())
	{
		set_prop_first_visible_datarow(nNewFirstVisible);
		
		//notify (simulate date_entered event)
		roResult.add_info(NewSCP(new ned_event_newdata(get_container()->get_ident())));
	}
}

//--------------------------------------------------------------------
// process key-down
//--------------------------------------------------------------------

void cned_grid_bodysection::process_event_keydown(ned_path_to_element & roCallStack,const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	SCP<cned_tablerow> poTableRowSP = 
		scp_cast_ui<cned_tablerow>(roCallStack.is_empty() ? roCallStack.target(): roCallStack.top());

	cned_table_bodysection::process_event_keydown(roCallStack,roActionKBD,roResult);
	
	if(!roResult.is_processed())
	{
		_build_in_on_event_keydown(get_row_nr(poTableRowSP->get_ident()),roActionKBD,roResult);
	}
	
	_supply_datarownr_property(poTableRowSP,roResult);
}

//--------------------------------------------------------------------
// process click
//--------------------------------------------------------------------

void cned_grid_bodysection::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	SCP<cned_tablerow> poTableRowSP = 
		scp_cast_ui<cned_tablerow>(roCallStack.is_empty() ? roCallStack.target(): roCallStack.top());

	cned_table_bodysection::process_event_mouse_click(roCallStack,roActionMouse,roResult);
	
	if(!roResult.is_processed() && roActionMouse.is_LEFT_click())
	{
		get_manager()->store_drag_info(NewSCP(new cned_drag_info_grid_row(roActionMouse.get_mouse_position(),poTableRowSP)));
		roResult.set_processed();
	}
}


//--------------------------------------------------------------------
// process end-click
//--------------------------------------------------------------------
void cned_grid_bodysection::process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	SCP<cned_tablerow> poTableRowSP = 
		scp_cast_ui<cned_tablerow>(roCallStack.is_empty() ? roCallStack.target(): roCallStack.top());

	cned_table_bodysection::process_event_mouse_endclick(roCallStack,roActionMouse,roResult);
	
	_supply_datarownr_property(poTableRowSP,roResult);

	//dla right-click'a 
	//budujemy liste operacji na wierszu
	//

	//PATCH 2006-01-23: zmieniono warunek na is_sys_disable - czyli dotyczacy
	//calej strony a nie tylko tego GRID'a
	//czyli nie mozna teraz miec obslugi prawego klawisza dla jednego odblokowanego a drugiego zablokowanego !!!

	if(roActionMouse.is_RIGHT_click() && !get_manager()->is_sys_disable())
	{
		SCP<CCommandList> poCmdListSP = _create_or_get_command_list(roResult,get_ident());
		ASSERT(poCmdListSP.PointsObject());

		//jesli coœ by³o - dodaj separator
		if(!poCmdListSP->IsEmpty())
		{
			poCmdListSP->AddSeparator();
		}
		
		long nTableRowNr = get_row_nr(poTableRowSP->get_ident());
		long nDataRowNr = datarow_nr_from_table_row_nr(nTableRowNr);
		
		/* 
			uwaga! podajemy w PROPC_IDENT grid'a nie w sekcji bo grid ma transfer a nie sekcja 
		*/
		
		//komenda 'wstaw wiersz'
		SCP<CHyperLinkInfo> poInsertRowHLISP = init_control_command_hli(get_container()->get_ident(),sccv_insert_row);
		poInsertRowHLISP->SetNumProp(PROPC_ROW,nDataRowNr);
		//LANGUAGE:PL
		poCmdListSP->AddCommand(_T("&Wstaw wiersz"),poInsertRowHLISP);
		
		if(nTableRowNr < get_child_count() - 1)
		{
			//komenda usuñ wiersz
			SCP<CHyperLinkInfo> poDeleteRowHLISP = init_control_command_hli(get_container()->get_ident(),sccv_delete_row);
			poDeleteRowHLISP->SetNumProp(PROPC_ROW,nDataRowNr);
			//LANGUAGE:PL
			poCmdListSP->AddCommand(_T("&Usuñ wiersz"),poDeleteRowHLISP);
		}
		if(get_child_count() > 1)
		{
			//komenda usuñ wszystko
			SCP<CHyperLinkInfo> poDeleteAllHLISP = init_control_command_hli(get_container()->get_ident(),sccv_delete_all);
			//LANGUAGE:PL
			poCmdListSP->AddCommand(_T("&Usuñ wszystko"),poDeleteAllHLISP);
		}
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
ned_ident cned_grid_bodysection::find_row_from_screen_point(const ng_point & roArenaPoint)
{
	ng_point oPoint = roArenaPoint;
	_get_grid()->_screen2local(oPoint);
	
	//jeœli poza obszarem to zwracamy nothing
	if(!is_inside_hit_area(oPoint))
	{
		return NEDID_NOTHING;
	}
	
	//czy coœ znalaz³
	ned_ident idFoundElement = find_element_from_point(oPoint);
	if(idFoundElement == NEDID_NOTHING)
	{
		return NEDID_NOTHING;
	}

	//szukaj po kolejnych kontenerach w górê a¿ znajdziesz sekcjê
	ned_ident idFinCont = get_manager()->get_element_container_ident(idFoundElement);
	bool bFoundSibling = false;
	while(idFinCont != NEDID_NOTHING)
	{
		if(idFinCont == get_ident())
		{
			bFoundSibling = true;
			break;
		}
		idFoundElement = idFinCont;
		idFinCont = get_manager()->get_element_container_ident(idFinCont);
	}
	if(!bFoundSibling)
	{
		return NEDID_NOTHING;
	}
	
	//znalaz³ wiersz, nale¿acy do tej samej sekcji
	ASSERT(idFoundElement != NEDID_NOTHING);
	ASSERT(get_manager()->get_element_type(idFoundElement) == ned_tablerow);
	
	return idFoundElement;
}

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

cned_drag_info_grid_row::cned_drag_info_grid_row(const ng_point & roStartingArenaPoint,SCP<cned_tablerow> poStartingTableRowSP) :
	cned_drag_info__(roStartingArenaPoint),
	m_oLastPoint(roStartingArenaPoint),
	m_poStartingTableRowSP(poStartingTableRowSP)
{
	ASSERT(m_poStartingTableRowSP.PointsObject());
}


void draw_drag_rect(const ng_rect & roRect,ng_dc & roDC);
HCURSOR get_cursor_handle_on_type(eCursorType eCT);

bool cned_drag_info_grid_row::on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	ng_rect oTblRowRect;
	//ned_to_do: m_poStartingTableRowSP->get_row_rect(oTblRowRect);
	
	ng_rect oOldRect(oTblRowRect);
	oOldRect.offset(m_oLastPoint.distance(m_oStartingPoint));
	ng_rect oNewRect(oTblRowRect);
	oNewRect.offset(roActionMouseDrag.get_mouse_position().distance(m_oStartingPoint));
	
	if(!(oNewRect == oOldRect))
	{
		draw_drag_rect(oOldRect,roActionMouseDrag.get_dc());
		draw_drag_rect(oNewRect,roActionMouseDrag.get_dc());
	}
	
	m_oLastPoint = roActionMouseDrag.get_mouse_position();

	if(!_is_in_void_drag_area(m_oStartingPoint,roActionMouseDrag.get_mouse_position()))
	{
		//ned_to_do: inny kursor ?
		HCURSOR hCursor = get_cursor_handle_on_type(ect_drag);
		if(hCursor != ::GetCursor())
		{
			::SetCursor(hCursor);
		}
	}

	return true;
}

bool cned_drag_info_grid_row::on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	ng_rect oTblRowRect;
	//ned_to_do: m_poStartingTableRowSP->get_row_rect(oTblRowRect);

	ng_rect oOldRect(oTblRowRect);
	oOldRect.offset(m_oLastPoint.distance(m_oStartingPoint));
	draw_drag_rect(oOldRect,roActionMouseDrag.get_dc());

	if(_is_in_void_drag_area(m_oStartingPoint,roActionMouseDrag.get_mouse_position()))
	{
		return true;
	}
	
	SCP<cned_grid_bodysection> poGridBodySectionSP = scp_cast_ui<cned_grid_bodysection>(m_poStartingTableRowSP->get_container());

	//szukamy wiersza
	ned_ident idFinishingElement = poGridBodySectionSP->find_row_from_screen_point(roActionMouseDrag.get_mouse_position());
	
	//nie znalaz³ - ignorujemy
	if(idFinishingElement == NEDID_NOTHING)
	{
		return true;
	}

	//ale to jest ten sam - ignorujemy
	if(idFinishingElement == m_poStartingTableRowSP->get_ident())
	{
		return true;
	}

	long nStartingDataRowNr = 1 + poGridBodySectionSP->
		datarow_nr_from_table_row_nr(poGridBodySectionSP->get_row_nr(m_poStartingTableRowSP->get_ident()));
	long nFinishingDataRowNr = 1 + poGridBodySectionSP->
		datarow_nr_from_table_row_nr(poGridBodySectionSP->get_row_nr(idFinishingElement));
		
	//podajemy ident grid'a który jest grand parentem sekcji - on ma transfer nie sekcja
	SCP<ned_event_row_operation> poEventRowOpSP = 
		NewSCP(new ned_event_row_operation(poGridBodySectionSP->get_container_ident()));
	
	poEventRowOpSP->set_data_row_nr(nStartingDataRowNr);
	poEventRowOpSP->set_second_data_row_nr(nFinishingDataRowNr);
	poEventRowOpSP->set_operation(ned_event_row_operation::oper_move);
	roResult.add_info(poEventRowOpSP);

	return true;
}

