/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	cned_container
		- kontener elementów UI (base class)
*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifdef _DEVELOPER_EDITION_
bool check_can_container_has_that_child(ened_element_type eContainer,ened_element_type eChild)
{
	switch(eContainer)
	{
	case ned_table:
		switch(eChild)
		{
		case ned_tablesection:
		case ned_tablebodysection:
			return true;
		default:
			return false;
		}
	case ned_grid:
		switch(eChild)
		{
		case ned_tablesection:
		case ned_spreadbodysection:
		case ned_spreadpatternsection:
			return true;
		default:
			return false;
		}
	case ned_tablesection:
	case ned_spreadbodysection:
	case ned_tablebodysection:
		return (eChild == ned_tablerow);
	case ned_spreadpatternsection:
		return (eChild == ned_patterntablerow);
	case ned_tablerow:
	case ned_patterntablerow:
		return (eChild == ned_tablecell);
	case ned_tabmanager:
		return (eChild == ned_tabitem);
	}
	switch(eChild)
	{
	case ned_tablecell:
		return (eContainer == ned_tablerow || eContainer == ned_patterntablerow);
	case ned_tablerow:
		return (eContainer == ned_tablesection || eContainer == ned_spreadbodysection || eContainer == ned_tablebodysection);
	case ned_spreadbodysection:
	case ned_spreadpatternsection:
		return (eContainer == ned_grid);
	case ned_tablesection:
		return (eContainer == ned_grid || eContainer == ned_table);
	}
	return true;
}
#endif

SCP <cned_element> cned_container::insert_new_element(ened_element_type eType,const ned_ident idNew,const ned_ident idAfter)
{
#ifdef _DEVELOPER_EDITION_
	if(!check_can_container_has_that_child(get_type(),eType))
	{
		CString oInfoString;
		oInfoString.Format("Kontener typu %d nie mo¿e mieæ dziecka typu %d",
			long(get_type()),long(eType));
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oInfoString);
	}
#endif
	//those types should be created using cned_table::create_section
	ASSERT(eType != ned_tablebodysection && eType != ned_tablesection && 
		eType != ned_spreadpatternsection && eType != ned_spreadbodysection);

	//these type is created only by cned_window::ctor
	ASSERT(eType != ned_toplevelpage);

	SCP <cned_element> poElementSP = get_manager()->_create_element(eType,idNew);
	ASSERT(poElementSP.PointsObject());
	poElementSP->_set_container(NewSCP(this,true));

	_link_element(poElementSP->get_ident(),idAfter);

	on_child_inserted(poElementSP);
	_size_info_dirty();

	return poElementSP;
}

void cned_container::remove_element(ned_ident idElement)
{
	//sprawdzanie czy wywo³anie jest sensowne
	if(get_manager()->get_element_container_ident(idElement) != get_ident())
	{
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,"remove wywo³ane nie dla dziecka");
	}

	//najpierw powiedz mu aby usun¹³ swoje dzieci (wszystkie - trybie 'whileremovingitself')
	if(is_container(get_manager()->get_element_type(idElement)))
	{
		SCP<cned_element> poElementSP = get_element_on_ident(idElement);
		cned_container * poContainer = cast_ui<cned_container>(poElementSP);
		ASSERT(poContainer);
		poContainer->remove_children(true);
	}

	//poinformuj 'górê' ¿e usuwamy
	on_child_removing(idElement);
	_size_info_dirty();

	//wyrzuæ z naszego storage (de facto od³¹cz z listy)
	_unlink_element(idElement);

	//powiedz managerowi aby zniszczy³ element
	get_manager()->_remove_element(idElement);
}

void cned_container::remove_children(bool bWhileRemovingItself)
{
	//usuwanie od 'koñca' - tj . ostatniego elementu

	for(ned_ident idChild = get_last_child_ident(); idChild != NEDID_NOTHING; 
		idChild = get_manager()->get_prev_element(idChild))
	{
		if(is_container(get_manager()->get_element_type(idChild)))
		{
			SCP <cned_element> poElementSP = get_element_on_ident(idChild);
			ASSERT(poElementSP.PointsObject());
			cned_container * poContainer = cast_ui<cned_container>(poElementSP);
			ASSERT(poContainer);
			poContainer->remove_children(true);
		}
		
		on_child_removing(idChild);
	}

	//powiedz managerowi aby zniszczy³ elementy
	for(ned_ident idChild = get_last_child_ident(); idChild != NEDID_NOTHING; 
		idChild = get_manager()->get_prev_element(idChild))
	{
		get_manager()->_remove_element(idChild);
	}

	//wyrzuæ z naszego storage (wszystkie na raz)
	//unlink-all jest na koñcu bo iterator powy¿ej nie mia³by na czym siê iterowaæ :)
	_unlink_all_elements();
	
	if(!bWhileRemovingItself)	//bo jak usuwamy to i tak ta informacja dojdzie 'góry'
	{
		_size_info_dirty();
	}
}

//--------------------------------------------------------
//---------- drawing helpers ----------------

void cned_container::_draw_foreground_children(cned_fore_painter & roForePainter,const ng_point & roInsidePaintPoint)
{
	//roInsidePaintPoint - punkt wnêtrza kontenera, po uwzglêdnieniu jego offsetu i scrolla
	long nPrevTreeDisCnt;
	roForePainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	cned_filter_children oFilter(this,true,roForePainter.is_printing());
	
	ned_position oDummyPosition;

	while(!oFilter.is_end())
	{
		SCP<cned_element> poElementSP = oFilter.get_element();
		if(poElementSP->get_type() != ned_subpage)
		{
			ened_spr eSPR = poElementSP->should_paint(roForePainter,roInsidePaintPoint);
			if(eSPR == spr_inside)
			{
				poElementSP->draw_foreground(roForePainter,roInsidePaintPoint);
			}
			else
			{
				if(eSPR == spr_below)
				{
					//ned_to_do: inc_rend break;
					if(!poElementSP->get_decl_position(oDummyPosition))
					{
						break;
					}
				}
			}
		}
		
		oFilter.move_next();
	}
	
	roForePainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_container::_draw_background_children(cned_back_painter & roBackPainter,const ng_point & roInsidePaintPoint)
{
	//roInsidePaintPoint - punkt wnêtrza kontenera, po uwzglêdnieniu jego offsetu i scrolla
	long nPrevTreeDisCnt;
	roBackPainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	cned_filter_children oFilter(this,true,roBackPainter.is_printing());

	ned_position oDummyPosition;

	while(!oFilter.is_end())
	{
		SCP<cned_element> poElementSP = oFilter.get_element();

		if(poElementSP->get_type() != ned_subpage)
		{
			ened_spr eSPR = poElementSP->should_paint(roBackPainter,roInsidePaintPoint);
			if(eSPR == spr_inside)
			{
				poElementSP->draw_background(roBackPainter,roInsidePaintPoint);
			}
			else
			{
				if(eSPR == spr_below)
				{
					//ned_to_do: inc_rend	break;
					if(!poElementSP->get_decl_position(oDummyPosition))
					{
						break;
					}
				}
			}
		}
		
		oFilter.move_next();
	}

	roBackPainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_container::_get_children_opaque_background_area(const ng_point & roInsidePaintPoint,ng_area & roArea) const
{
	//roInsidePaintPoint - punkt wnêtrza kontenera, po uwzglêdnieniu jego offsetu i scrolla
	cned_filter_children oFilter(this,true,false);
	
	while(!oFilter.is_end())
	{
		SCP<cned_element> poElementSP = oFilter.get_element();
		
		if(poElementSP->get_type() != ned_subpage)
		{
			poElementSP->get_opaque_background_area(roInsidePaintPoint,roArea);
		}
		if(oFilter.get_ident() == _get_last_measured())
		{
			break;
		}
		oFilter.move_next();
	}
}

ned_ident cned_container::find_element_from_point(const ng_point & roPoint)
{
//	ASSERT(is_inside_hit_area(roPoint));

	ng_point oInternalPoint(roPoint);
	oInternalPoint.offset(-m_oVectorSize);

	cned_filter_children oFilter(this,true,false);

	while(!oFilter.is_end())
	{
		SCP <cned_element> poElementSP = oFilter.get_element();
		ASSERT(poElementSP.PointsObject());

		if(poElementSP->is_inside_hit_area(oInternalPoint))
		{
			if(is_container(poElementSP->get_type()))
			{
				return scp_cast_ui<cned_container>(poElementSP)->find_element_from_point(oInternalPoint);
			}
			else
			{
				return poElementSP->get_ident();
			}
		}
		oFilter.move_next();
	}
	return get_ident();
}

ned_ident cned_container::find_element_next_prev(const ned_ident idStart,bool bNext)
{
	ned_ident idIter;

	//inicjowanie w zale¿noœci od kierunku i punktu startu
	if(bNext)
	{
		if(idStart != NEDID_NOTHING)
		{
			idIter = get_manager()->get_next_element(idStart);
		}
		else
		{
			idIter = get_first_child_ident();
		}
	}
	else
	{
		if(idStart != NEDID_NOTHING)
		{
			idIter = get_manager()->get_prev_element(idStart);
		}
		else
		{
			idIter = get_last_child_ident();
		}
	}

	//iterujemy siê a¿ do koñca lub gdy znajdziemy coœ pod spodem
	while(idIter != NEDID_NOTHING)
	{
		if(get_manager()->is_element_tabstop(idIter) && get_manager()->can_element_accept_focus(idIter))
		{
			//OK. znalaz³
			return idIter;
		}
		else
		{
			if(!get_manager()->is_element_hidden(idIter))
			{
				if(is_container(get_manager()->get_element_type(idIter)))
				{
					//szukaj wœród podkontenerów
					SCP <cned_element> poElementSP = get_element_on_ident(idIter);
					cned_container * poContainer = cast_ui<cned_container>(poElementSP);
					ASSERT(poContainer);
					ned_ident idFound = poContainer->find_element_next_prev(NEDID_NOTHING,bNext);
					if(idFound != NEDID_NOTHING)
					{
						return idFound;
					}
				}
			}
		}
		
		if(bNext)
		{
			idIter = get_manager()->get_next_element(idIter);
		}
		else
		{
			idIter = get_manager()->get_prev_element(idIter);
		}
	}

	return NEDID_NOTHING;
}

#ifdef _DEBUG
extern long _debug_quoting_counter;
#endif

ned_ident cned_container::find_element_relative(const ng_rect & roRefRect,const ned_ident idStart,eRelativePosition eRP,long & rnBestDistance)
{
	ng_rect oInternalRefRect(roRefRect);
	oInternalRefRect.offset(-m_oVectorSize);

	ned_ident idBest = NEDID_NOTHING;
	cned_filter_children oFilter(this,true,false);

	while(!oFilter.is_end())
	{
		if(oFilter.get_ident() != idStart)
		{
			if(get_manager()->is_element_tabstop(oFilter.get_ident()) && get_manager()->can_element_accept_focus(oFilter.get_ident()))
			{
				//quote element
#ifdef _DEBUG
				_debug_quoting_counter++;
#endif

				if(oFilter.get_element()->quote_distance(eRP,oInternalRefRect,rnBestDistance))
				{
					idBest = oFilter.get_ident();
					TRACE("FER: improved [%d]-> %d\n", idBest,rnBestDistance);
				}
			}
			else
			{
				//kontener
				if(is_container(get_manager()->get_element_type(oFilter.get_ident())))
				{
					long nDummy = rnBestDistance;
					SCP<cned_element> poElementSP = oFilter.get_element();
					//sprawdŸ czy kontener ma w ogóle jak¹œ szansê
#ifdef _DEBUG
					_debug_quoting_counter++;
#endif
					if(poElementSP->quote_distance(eRP,oInternalRefRect,nDummy))
					{
						//ma szansê - szukaj w nim
						cned_container * poContainer = cast_ui<cned_container>(poElementSP);
						ned_ident idFound = poContainer->find_element_relative(oInternalRefRect,NEDID_NOTHING,eRP,rnBestDistance);
						if(idFound != NEDID_NOTHING)
						{
							idBest = idFound;
						}
					}
				}
			}
		}

		oFilter.move_next();
	}

	return idBest;
}

void cned_container::_post_render_children(cned_post_render_manager & roPostRender,const ng_point & roInsidePaintPoint)
{
	//roInsidePaintPoint - punkt wnêtrza kontenera, po uwzglêdnieniu jego offsetu i scrolla

	cned_filter_children oFilter(this,true,roPostRender.is_printing());

	while(!oFilter.is_end() && roPostRender.is_any())
	{
		if(roPostRender.test_element_remove(oFilter.get_ident()))
		{
			oFilter.get_element()->post_render(roPostRender,roInsidePaintPoint);
		}
		oFilter.move_next();
	}
}

//------------------------------------------------------------------------ 
void cned_container::_update_children_split_info(const ng_point & roInsidePoint,cpb_split_info & roSplitInfo)
{
	//roInsidePoint - punkt ju¿ z uwzglêdnieniem offsetu kontenera - gotowy dla dzieci

	cned_filter_children oFilter(this,true,true);

	while(!oFilter.is_end())
	{
		oFilter.get_element()->update_split_info(roInsidePoint,roSplitInfo);
		oFilter.move_next();
	}
}

void cned_container::_make_children_split(const ng_point & roInsidePoint,cpb_split_manager & roSplitManager)
{
	//roInsidePoint - punkt ju¿ z uwzglêdnieniem offsetu kontenera - gotowy dla dzieci

	cned_filter_children oFilter(this,true,true);

	while(!oFilter.is_end())
	{
		oFilter.get_element()->make_split(roInsidePoint,roSplitManager);
		oFilter.move_next();
	}
}

//-------------- event forwarders -------------- -------------- -------
void cned_container::process_event_keydown(ned_path_to_element & roCallStack,const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	ned_ident idElement = NEDID_NOTHING;
	if(roCallStack.is_empty())
	{
		idElement = roCallStack.target()->get_ident();
		roCallStack.target()->on_event_keydown(roActionKBD,roResult);
	}
	else
	{
		SCP<cned_container> poContainerSP = roCallStack.pop();
		idElement = poContainerSP->get_ident();
		poContainerSP->process_event_keydown(roCallStack,roActionKBD,roResult);
	}

	ASSERT(idElement != NEDID_NOTHING);
	if(!roResult.is_processed())
	{
		switch(roActionKBD.get_keycode())
		{
		case VK_TAB:
		case VK_RETURN:
			{
				ned_ident idNext = find_element_next_prev(idElement,!roActionKBD.is_SHIFT());
				if(idNext != NEDID_NOTHING)
				{
					//przestaw focus 
					get_manager()->_mark_new_focus_element(idNext);
					roResult.set_processed();
				}
			}
		break;
		default:
			;	//not processed
		}
	}
}

//---- paint invalidating --------
void cned_rect_container_::_invalidate_all_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),MAIN_PAINT_RECT_ID);
}

void cned_rect_container_::post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_post_render_children(roPostRender,oPaintPoint);

	ng_rect oNewRect(oPaintPoint,m_oActualSize);
	ng_rect oOldRect;

	_get_main_paint_rect(oOldRect);
	
	if(oOldRect != oNewRect)
	{
		_invalidate_all_paint();
		get_manager()->invalidate_paint_rect(oNewRect);
	}
}

//--------------------------------------------------------
void cned_rect_container_::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
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
			_update_children_split_info(oPaintPoint,roSplitInfo);
		}
	}
}

void cned_rect_container_::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oElementRect(oPaintPoint,m_oActualSize);

	//umieszczamy siê na podstawie top-left
	long xAreaLeft = roSplitManager.find_x_area(oElementRect.get_left());
	long xAreaRight = roSplitManager.find_x_area(oElementRect.get_right());
	long yAreaTop = roSplitManager.find_y_area(oElementRect.get_top());
	long yAreaBottom = roSplitManager.find_y_area(oElementRect.get_bottom());

	for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
	{
		for(long yArea = yAreaTop; yArea <= yAreaBottom; yArea++)
		{
			_make_clone_split(roSplitManager,xArea,yArea);
		}
	}
	_make_children_split(oPaintPoint,roSplitManager);
}

