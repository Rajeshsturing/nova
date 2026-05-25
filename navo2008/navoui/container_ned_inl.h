/*
	NAVO Enterprise 2003
	2003-07-01

	navo enhanced display (NED)

	cned_container
		- kontener elementów UI (base class)

	inline part
*/

#ifndef _CONTAINER_NED_INL_H_
#define _CONTAINER_NED_INL_H_

namespace ned
{
//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_container::cned_container(cned_element_manager * poManager,const ened_element_type eType,const ned_ident nIdent) :
	cned_element(poManager,eType,nIdent),
	m_idFirstChild(NEDID_NOTHING),
	m_idLastChild(NEDID_NOTHING),
	m_idLastMeasured(NEDID_NOTHING),
	m_nChildCount(0)
{
}

inline cned_container::~cned_container()
{
}

inline const ned_ident cned_container::get_first_child_ident() const
{
	return m_idFirstChild;
}

inline const ned_ident cned_container::get_last_child_ident() const
{
	return m_idLastChild;
}

inline const long cned_container::get_child_count() const
{
	return m_nChildCount;
}

inline void cned_container::_link_element(const ned_ident idNewElement,const ned_ident idAfter)
{
	ASSERT(idNewElement != NEDID_NOTHING);

	if(idAfter == NEDID_LAST)
	{
link_at_end:
		if(m_idLastChild == NEDID_NOTHING)
		{
			ASSERT(m_idFirstChild == NEDID_NOTHING);
			m_idFirstChild = idNewElement;
		}
		else
		{
			ASSERT(m_idFirstChild != NEDID_NOTHING);
			get_manager()->set_prev_element(idNewElement,m_idLastChild);
			get_manager()->set_next_element(m_idLastChild,idNewElement);
		}
		m_idLastChild = idNewElement;
	}
	else
	{
		if(idAfter == NEDID_NOTHING)
		{
			if(m_idFirstChild == NEDID_NOTHING)
			{
				ASSERT(m_idLastChild == NEDID_NOTHING);
				m_idLastChild = idNewElement;
			}
			else
			{
				ASSERT(m_idLastChild != NEDID_NOTHING);
				get_manager()->set_next_element(idNewElement,m_idFirstChild);
				get_manager()->set_prev_element(m_idFirstChild,idNewElement);
			}
			m_idFirstChild = idNewElement;
		}
		else
		{
			ned_ident idNext = get_manager()->get_next_element(idAfter);
			if(idNext == NEDID_NOTHING)
			{
				goto link_at_end;
			}
			else
			{
				get_manager()->set_next_element(idAfter,idNewElement);
				get_manager()->set_prev_element(idNext,idNewElement);

				get_manager()->set_prev_element(idNewElement,idAfter);
				get_manager()->set_next_element(idNewElement,idNext);
			}
		}
	}

	++m_nChildCount;
}

inline void cned_container::_unlink_element(const ned_ident idElement)
{
	ned_ident idPrev = get_manager()->get_prev_element(idElement);
	ned_ident idNext = get_manager()->get_next_element(idElement);
	if(idNext == NEDID_NOTHING)
	{
		ASSERT(idElement == m_idLastChild);
		m_idLastChild = idPrev;
	}
	else
	{
		get_manager()->set_prev_element(idNext,idPrev);
	}
	if(idPrev == NEDID_NOTHING)
	{
		ASSERT(idElement == m_idFirstChild);
		m_idFirstChild = idNext;
	}
	else
	{
		get_manager()->set_next_element(idPrev,idNext);
	}
	m_nChildCount--;
	
	ASSERT(m_nChildCount >= 0);
}

inline void cned_container::_unlink_all_elements()
{
	m_idFirstChild = NEDID_NOTHING;
	m_idLastChild  = NEDID_NOTHING;
	m_nChildCount = 0;
}

inline const ned_ident cned_container::get_child_ident_on_pos(long nPosition) const
{
	ASSERT(nPosition >= 0 && nPosition < get_child_count());
	ned_ident idChild;

	if(nPosition < get_child_count() / 2)
	{
		idChild =  get_first_child_ident();
		while(idChild != NEDID_NOTHING && nPosition != 0)
		{
			idChild = get_manager()->get_next_element(idChild);
			nPosition--;
		}
	}
	else
	{
		idChild = get_last_child_ident();
		nPosition++;
		while(idChild != NEDID_NOTHING && nPosition != get_child_count())
		{
			idChild = get_manager()->get_prev_element(idChild);
			nPosition++;
		}
	}
	return idChild;
}

inline long cned_container::scan_for_child_pos(ned_ident idChild) const
{
	if(idChild == get_last_child_ident())
	{
		return get_child_count() - 1;
	}
	else
	{
		long nPosition = 0;
		for(ned_ident idTest = get_first_child_ident(); idTest != NEDID_NOTHING;
			idTest = get_manager()->get_next_element(idTest))
		{
			if(idTest == idChild)
			{
				return nPosition;
			}
			nPosition++;
		}
		
		ASSERT(false);
		return -1;
	}
}

inline void cned_container::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->on_child_inserted(rpoChildSP);
	}
	_vse_dirty();
}

inline void cned_container::on_child_removing(ned_ident idChild)
{
	if(_get_last_measured() == idChild)
	{
		_invalidate_last_measured(get_manager()->get_prev_element(idChild));
	}
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->on_child_removing(idChild);
	}
	
	_vse_dirty();
}

//-------------- rendering support -------------------
inline ned_ident cned_container::_get_last_measured() const
{
	return m_idLastMeasured;
}

inline void cned_container::get_children_metrics(const ned_measure_param &)
{
	ASSERT(false); //should not be called
}

//gdy siê zepsu³o
inline void cned_container::_invalidate_last_measured(ned_ident idElement)
{
	m_idLastMeasured = idElement;
}

//gdy naprawiamy
inline void cned_container::_validate_last_measured(ned_ident idElement)
{
//	TRACE("good [%d] of type %d up to [%d]\n",get_ident(),long(get_type()),idElement);
	m_idLastMeasured = idElement;
}


inline void cned_container::on_child_size_info_dirty(ned_ident idChild)
{
	ASSERT(get_manager()->get_element_container_ident(idChild) == get_ident());

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

			cned_filter_children oFilterChildren(this,false,false);
			while(!oFilterChildren.is_end())
			{
				//znaleŸliœmy notifykuj¹ce dziecko, a nie znaleŸliœmy jeszcze ostatniego u³o¿onego
				//-> to jest istotna zmiana -> notyfikuj
				if(oFilterChildren.get_ident() == idChild)
				{
					_invalidate_last_measured(get_manager()->get_prev_element(idChild));

					SCP<cned_container> poContainerSP = get_container();
					if(poContainerSP.PointsObject())
					{
						poContainerSP->on_child_size_info_dirty(get_ident());
					}
					
					_vse_dirty();
					return;
				}
				
				//dotarliœmy do ostatniego dobrego i nie znaleŸliœmy notyfikuj¹cego
				//dziecka -> musi byæ dalej -> zmiana nie jest istotna
				if(oFilterChildren.get_ident() == _get_last_measured())
				{
					return;
				}
				oFilterChildren.move_next();
			}
		}
	}

	ASSERT(is_measure_pending());

	_vse_dirty();
}

inline void cned_container::get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics)
{
	ASSERT(!get_prop_hidden());

	if(is_measure_pending())
	{
		m_oMetrics.reset();
		get_children_metrics(roMParam);

		if(is_normal_width_value(get_prop_extwidth()))
		{
			ng_xdist dxWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
			if(dxWidth > m_oMetrics.get_minimal_width())
			{
				m_oMetrics.update(dxWidth,m_oMetrics.get_minimal_height(),m_oMetrics.get_weight());
			}
		}

		clear_measure_pending();
	}
	roMetrics.update(m_oMetrics);
}

//-------------- attribute functions -------------------------
inline void cned_container::apply_attributes(const ned_currattributes & roCurrAttrib)
{
	cned_element::apply_attributes(roCurrAttrib);

	cned_filter_children oFilterChildren(this,false,false);
	while(!oFilterChildren.is_end())
	{
		oFilterChildren.get_element()->apply_attributes(get_current_attributes());
		oFilterChildren.move_next();
	}
}

//-------------- fill clone -------------- -------------- -------
inline void cned_container::fill_clone(cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	
	cned_container * poDestContainer = cast_ui<cned_container>(poDestination);
	poDestContainer->remove_children(false);
	
	cned_filter_children oFilterChildren(this,false,false);
	while(!oFilterChildren.is_end())
	{
		SCP<cned_element> poSrcElementSP = oFilterChildren.get_element();
		SCP<cned_element> poDestElementSP = 
			poDestContainer->insert_new_element(poSrcElementSP->get_type(),NEDID_NOTHING,NEDID_LAST);
		poSrcElementSP->fill_clone(poDestElementSP);
		
		oFilterChildren.move_next();
	}
	
	ASSERT(get_child_count() == poDestContainer->get_child_count());
}

inline bool cned_container::is_visually_empty() const
{
	if(get_child_count() == 0)
	{
		return true;
	}

	cned_filter_children oFilterChildren(this,true,false);
	while(!oFilterChildren.is_end())
	{
		if(!oFilterChildren.get_element()->is_visually_empty())
		{
			return false;
		}
		oFilterChildren.move_next();
	}
	return true;
}

//-------------- event forwarders -------------- -------------- -------
inline void cned_container::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_mouse_click(roActionMouse,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_mouse_click(roCallStack,roActionMouse,roResult);
	}
}

inline void cned_container::process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_mouse_endclick(roActionMouse,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_mouse_endclick(roCallStack,roActionMouse,roResult);
	}
}

inline void cned_container::process_event_mouse_over(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_mouse_over(roActionMouse,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_mouse_over(roCallStack,roActionMouse,roResult);
	}
}

inline void cned_container::process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_mouse_wheel(roActionMouseWheel,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_mouse_wheel(roCallStack,roActionMouseWheel,roResult);
	}
}

inline void cned_container::process_event_focus(ned_path_to_element & roCallStack,const ned_action_focus & roActionFocus,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_focus(roActionFocus,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_focus(roCallStack,roActionFocus,roResult);
	}
}

inline void cned_container::process_event_timer(ned_path_to_element & roCallStack,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_timer(roActionTimer,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_timer(roCallStack,roActionTimer,roResult);
	}
}

inline void cned_container::process_event_olecontrol(ned_path_to_element & roCallStack,
		const ned_action_oleevent & roActionOleEvent,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_olecontrol(roActionOleEvent,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_olecontrol(roCallStack,roActionOleEvent,roResult);
	}
}

inline void cned_container::process_event_command(ned_path_to_element & roCallStack,const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	if(roCallStack.is_empty())
	{
		roCallStack.target()->on_event_command(roActionCommand,roResult);
	}
	else
	{
		roCallStack.pop()->process_event_command(roCallStack,roActionCommand,roResult);
	}
}

inline eCursorType cned_container::process_event_set_cursor(ned_path_to_element & roCallStack,const ng_point & roPoint)
{
	if(roCallStack.is_empty())
	{
		return roCallStack.target()->on_event_set_cursor(roPoint);
	}
	else
	{
		return roCallStack.pop()->process_event_set_cursor(roCallStack,roPoint);
	}
}

//--------------- persistency -----------------------------------
inline void cned_container::save(cned_storage_writer & roWriter)
{
	cned_element::save(roWriter);

	roWriter << m_idFirstChild << m_idLastChild << m_nChildCount << m_idLastMeasured;
}

inline void cned_container::load(cned_storage_reader & roReader)
{
	cned_element::load(roReader);

	roReader >> m_idFirstChild >> m_idLastChild >> m_nChildCount >> m_idLastMeasured;
}

//--------------------------------------------------------------------------------------
//		cned_rect_container_
//--------------------------------------------------------------------------------------
inline cned_rect_container_::cned_rect_container_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_container(poManager,eType,idThis)
{
}
inline bool cned_rect_container_::abs_render(cned_absolute_renderer & roAbsRenderer,const ned_position & roPosition,
		const ng_point & roFlowPoint)
{
	render(roAbsRenderer);
	_compute_vector_from_position(get_manager(),roPosition,roAbsRenderer.get_arena_rect(),roFlowPoint,
		m_oActualSize,m_oVectorSize);

	//sprawdzamy czy wyliczony rozmiar mieœci siê w dostêpnym
	//jeœli nie to zg³aszamy potrzebê
	ng_rect oRect(ng_point().offset(m_oVectorSize),m_oActualSize);
	
	bool bResult = true;
	if(oRect.get_right() > roAbsRenderer.get_arena_rect().get_right())
	{
		roAbsRenderer.get_arena_rect().set_right(oRect.get_right());
		bResult = false;
	}

	if(oRect.get_bottom() > roAbsRenderer.get_arena_rect().get_bottom())
	{
		roAbsRenderer.get_arena_rect().set_bottom(oRect.get_bottom());
		bResult = false;
	}

	return bResult;
}

inline ened_spr cned_rect_container_::should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const
{
	ng_rect oTestRect(ng_point(roCurrentPoint).offset(m_oVectorSize),m_oActualSize);
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

inline void cned_rect_container_::get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	if(_is_fast_graphics() || get_prop_backcolor().is_opaque())	//jeœli nieprze¿roczysty to ca³y obszar
	{
		roArea += ng_rect(oPaintPoint,m_oActualSize);
	}
	else
	{
		_get_children_opaque_background_area(oPaintPoint,roArea);
	}
}


inline bool cned_rect_container_::is_inside_hit_area(const ng_point & roPoint) const
{
	ng_rect oMyRect;
	cned_rect_container_::get_bounding_rect(-1,oMyRect);
	return oMyRect.is_inside(roPoint);
}

inline bool cned_rect_container_::quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance)
{
	ng_rect oMyRect;
	cned_rect_container_::get_bounding_rect(-1,oMyRect);
	return _quote_rect_distance(eRP,roRefRect,oMyRect,rnDistance);
}

inline void cned_rect_container_::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	roLocalRect = ng_rect(ng_point().offset(m_oVectorSize),m_oActualSize);
}

inline const ng_size & cned_rect_container_::get_actual_size() const
{
	return m_oActualSize;	
}

//-------------- attribute functions -------------------------
inline void cned_rect_container_::set_fixed_properties()
{
	cned_container::set_fixed_properties();
	set_prop_split_allowed(true);
	set_prop_ignore_sys_disable(true);
}

//--------------- persistency -----------------------------------
inline void cned_rect_container_::save(cned_storage_writer & roWriter)
{
	cned_container::save(roWriter);
	roWriter << m_oActualSize;
}

inline void cned_rect_container_::load(cned_storage_reader & roReader)
{
	cned_container::load(roReader);
	roReader >> m_oActualSize;
}

//---------------------------------------------------------------------- 
//------------ cned_filter_children__ ------------------------------------
//---------------------------------------------------------------------- 

template<class NUITYPE>
inline cned_filter_children__<NUITYPE>::cned_filter_children__(const cned_element_manager * poManager,ned_ident idFirst,bool bSkipHidden,bool bSkipNonPrintable) :
	m_poManager(poManager),
	m_bSkipHidden(bSkipHidden),
	m_bSkipNonPrintable(bSkipNonPrintable)
{
	ASSERT(m_poManager != NULL);
	restart_at(idFirst);
}

template<class NUITYPE>
inline cned_filter_children__<NUITYPE>::cned_filter_children__(const cned_container * poContainer,bool bSkipHidden,bool bSkipNonPrintable) :
	m_poManager(poContainer->get_manager()),
	m_bSkipHidden(bSkipHidden),
	m_bSkipNonPrintable(bSkipNonPrintable)
{
	ASSERT(m_poManager != NULL);
	restart_at(poContainer->get_first_child_ident());
}

template<class NUITYPE>
inline void cned_filter_children__<NUITYPE>::restart_at(ned_ident idElement)
{
	m_idCurrent = idElement;
	_find_next_valid();
}

template<class NUITYPE>
inline bool cned_filter_children__<NUITYPE>::_qualify(ned_ident idElement)
{
	if(m_bSkipHidden)
	{
		if(m_poManager->is_element_hidden(idElement))
		{
			return false;
		}
	}
	if(m_bSkipNonPrintable)
	{
		if(!m_poManager->is_element_printable(idElement))
		{
			return false;
		}
	}
	return true;
}

template<class NUITYPE>
inline void cned_filter_children__<NUITYPE>::_find_next_valid()
{
	while(m_idCurrent != NEDID_NOTHING)
	{
		if(_qualify(m_idCurrent))
		{
			return;
		}
		m_idCurrent = m_poManager->get_next_element(m_idCurrent);
	}
}

template<class NUITYPE>
inline bool cned_filter_children__<NUITYPE>::is_end() const
{
	return (m_idCurrent == NEDID_NOTHING);
}

template<class NUITYPE>
inline void cned_filter_children__<NUITYPE>::move_next()
{
	m_idCurrent = m_poManager->get_next_element(m_idCurrent);
	_find_next_valid();
}

template<class NUITYPE>
inline ned_ident cned_filter_children__<NUITYPE>::get_ident() const
{
	return m_idCurrent;
}
	
template<class NUITYPE>
inline SCP<NUITYPE> cned_filter_children__<NUITYPE>::get_element() const
{
	ASSERT(m_idCurrent != NEDID_NOTHING);
	return scp_cast_ui<NUITYPE>(m_poManager->get_element_on_ident(m_idCurrent));
}

//--------------------------------------------------------------------------------------
// œcie¿ka do elementu - stos kontenerów + element
//--------------------------------------------------------------------------------------
inline ned_path_to_element::ned_path_to_element(cned_element * poTargetElement) :
	m_poTargetElementSP(NewSCP(poTargetElement,true))
{
	_build();
}

inline SCP<cned_container> ned_path_to_element::pop()
{
	return m_oStack.Pop();
}

inline SCP<cned_container> ned_path_to_element::top()
{
	return m_oStack.GetTop();
}

inline SCP<cned_element> ned_path_to_element::target()
{
	return m_poTargetElementSP;
}

inline bool ned_path_to_element::is_empty() const
{
	return m_oStack.IsEmpty();
}

inline void ned_path_to_element::_build()
{
	ASSERT(m_poTargetElementSP.PointsObject());

	for(SCP<cned_container> poContainerSP = m_poTargetElementSP->get_container(); 
		poContainerSP.PointsObject(); 
		poContainerSP = poContainerSP->get_container())
	{
		m_oStack.Push(poContainerSP);
	}
}

}

#else
	#error __FILE__ already included
#endif

