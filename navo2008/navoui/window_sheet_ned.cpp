/*
	NAVO Enterprise 2003
	2003-05-05

	navo enhanced display (NED)

	window
	
	window sheet object
	
	single sheet
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "arena_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------
// single window sheet
//----------------------------------------------------------------------
cned_window_sheet::cned_window_sheet(cned_arena * poArena,cned_window * poWindow,SCP<cned_element_manager> poElementManagerSP,SCP<cned_toplevelpage> poTopLevelPageSP) :
	m_poArena(poArena),
	m_poWindow(poWindow),
	m_poElementManagerSP(poElementManagerSP),
	m_poTopLevelPageSP(poTopLevelPageSP)
{
	ASSERT(m_poArena);
	ASSERT(m_poWindow);
	ASSERT(m_poElementManagerSP.PointsObject());
	ASSERT(m_poTopLevelPageSP.PointsObject());
}

cned_window_sheet::~cned_window_sheet()
{
	ASSERT(m_poElementManagerSP.PointsObject());
	ASSERT(m_poTopLevelPageSP.PointsObject());

	m_poElementManagerSP->_remove_element(NEDID_TOPLEVELPAGE);
	m_poTopLevelPageSP = 0;
	m_poElementManagerSP->_clean_all();
}

cned_toplevelpage * cned_window_sheet::get_page()
{
	ASSERT(m_poTopLevelPageSP.PointsObject());
	return m_poTopLevelPageSP.Get();
}

cned_element_manager * cned_window_sheet::get_manager()
{
	ASSERT(m_poElementManagerSP.PointsObject());
	return m_poElementManagerSP.Get();
}

const cned_toplevelpage * cned_window_sheet::get_page() const 
{
	ASSERT(m_poTopLevelPageSP.PointsObject());
	return m_poTopLevelPageSP.Get();
}

const cned_element_manager * cned_window_sheet::get_manager() const 
{
	ASSERT(m_poElementManagerSP.PointsObject());
	return m_poElementManagerSP.Get();
}

SCP<cned_element> cned_window_sheet::get_element_on_ident(const ned_ident idElement) const
{
	return get_manager()->get_element_on_ident(idElement);
}

SCP<cned_toplevelpage> cned_window_sheet::get_toplevelpage() const
{
	ASSERT(m_poTopLevelPageSP.PointsObject());
	return const_cast<cned_window_sheet*>(this)->m_poTopLevelPageSP;
}

//--------------------------------------------------------------------------
// paint
//--------------------------------------------------------------------------
void cned_window_sheet::paint(cned_painter_ & roArenaPainter)
{
	get_page()->paint(roArenaPainter);
}

void cned_window_sheet::_prepare_paint_region(ng_region & roRegion)
{
	get_page()->prepare_paint_region(roRegion);
}

void cned_window_sheet::invalidate_sheet()
{
	get_page()->invalidate_page();
}

void cned_window_sheet::on_window_on_top(bool bTopMost)
{
	get_page()->on_window_on_top(bTopMost);
	
	if(bTopMost)
	{
		invalidate_sheet();
	}
}

void cned_window_sheet::on_being_current_sheet(bool bCurrent)
{
	if(bCurrent)
	{
		ng_rect oSheetRect;
		get_sheet_rect(oSheetRect);
		m_poArena->internal_invalidate_paint_rect(oSheetRect);
	}
	else
	{
		invalidate_sheet();
	}
}

void cned_window_sheet::get_sheet_rect(ng_rect & roSheetRect)
{
	get_page()->get_page_rect(roSheetRect);
}

//------ property GET -----------------
void cned_window_sheet::get_prop_title(ng_string & roTitleString) const
{
	get_page()->get_prop_title(roTitleString);
}


//-------------------------------------------------------------------------------------------------
// click
//-------------------------------------------------------------------------------------------------

void cned_window_sheet::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ned_ident idTarget = _find_mouse_target_element(roActionMouse.get_mouse_position());
	get_manager()->update_mouse_over_element(idTarget);

	if(idTarget != NEDID_NOTHING)
	{
		//info: element decyduje czy jest draggowalny i zapamiêtuje drag-info

		if(!get_manager()->is_element_disabled(idTarget))
		{
			ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));
			
			if(oPathToElement.is_empty())
			{
				oPathToElement.target()->on_event_mouse_click(roActionMouse,roResult);
			}
			else
			{
				oPathToElement.pop()->process_event_mouse_click(oPathToElement,roActionMouse,roResult);
			}
			
			//info: ustawienie focus'a jest robione samodzielnie przez element
		}
	}
}

//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------

void cned_window_sheet::on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	if(roActionTimer.get_timerid() == ARENA_TOOLTIP_TIMER_ID)
	{
		if(bTopWindow)
		{
			_prepare_tooltip();
		}
	}
	else
	{
		if(roActionTimer.get_timerid() == ARENA_CONTROL_TIMER_ID)
		{
#ifdef _DEBUG
			//return;	//uncomment to stop timer events - makes debugging easier
#endif
			
			//call other registered time-aware elements
			CArray<ned_ident,ned_ident &> oTimerControlArray;
			get_manager()->get_timer_controls(oTimerControlArray,bTopWindow);
			
			for(long iter = 0; iter < oTimerControlArray.GetSize(); iter++)
			{
				_process_event_timer(oTimerControlArray[iter],roActionTimer,roResult);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// over
//-------------------------------------------------------------------------------------------------

void cned_window_sheet::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ned_ident idOldTarget = get_manager()->get_mouse_over_element();
	ned_ident idTarget = NEDID_NOTHING;
	
	if(!roActionMouse.is_LEFT_click() || is_inside_hit_area(roActionMouse.get_mouse_position()))
	{
		idTarget = _find_mouse_target_element(roActionMouse.get_mouse_position());
	}
	

	if(roActionMouse.is_LEFT_click())	//may be dragging
	{
		if(get_manager()->is_dragging())	//if element is wants dragging
		{
			ned_action_mouse_drag oActionDrag(roActionMouse,get_manager(),idTarget);

			if(get_manager()->get_drag_info()->on_drag_over_event(oActionDrag,roResult))
			{
				goto finish_;
			}
		}
	}
	
	//normal 'over' - not dragging
	{
		if(idOldTarget == idTarget)
		{
			return;	//nad tym samym elementem - nie notyfikuj
		}
		//zmieñ mouse_over_element - stary bêdzie wiedzia³ ¿e to nie nad nim
		get_manager()->update_mouse_over_element(idTarget);
		if(NEDID_NOTHING != idOldTarget)
		{
			_process_event_mouse_over(idOldTarget,roActionMouse,roResult);
		}
		if(NEDID_NOTHING != idTarget)
		{
			_process_event_mouse_over(idTarget,roActionMouse,roResult);
			
		}
	}

finish_:
	;
}

//-------------------------------------------------------------------------------------------------
// end click
//-------------------------------------------------------------------------------------------------

void cned_window_sheet::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ned_ident idTarget = _find_mouse_target_element(roActionMouse.get_mouse_position());

	if(get_manager()->is_dragging())
	{
		ned_action_mouse_drag oActionDrag(roActionMouse,get_manager(),idTarget);
		
		if(get_manager()->get_drag_info()->on_end_drag_event(oActionDrag,roResult))
		{
			goto finish_;
		}
	}
	{
		get_manager()->update_mouse_over_element(idTarget);
	
		if(NEDID_NOTHING != idTarget)
		{
			if(!get_manager()->is_element_disabled(idTarget) || roActionMouse.is_RIGHT_click())
			{
				ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));
				
				if(oPathToElement.is_empty())
				{
					oPathToElement.target()->on_event_mouse_endclick(roActionMouse,roResult);
				}
				else
				{
					oPathToElement.pop()->process_event_mouse_endclick(oPathToElement,roActionMouse,roResult);
				}

			}
		}
	}

finish_:

	get_manager()->clean_drag_info();
}

void cned_window_sheet::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	ned_ident idTarget = _find_mouse_target_element(roActionMouseWheel.get_mouse_position());

	if(idTarget != NEDID_NOTHING)
	{
		ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));
		
		if(oPathToElement.is_empty())
		{
			oPathToElement.target()->on_event_mouse_wheel(roActionMouseWheel,roResult);
		}
		else
		{
			oPathToElement.pop()->process_event_mouse_wheel(oPathToElement,roActionMouseWheel,roResult);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// key down
//-------------------------------------------------------------------------------------------------
static eRelativePosition keycode2rp(UINT nCode)
{
	switch(nCode)
	{
	case VK_UP:
		return rp_above;
	case VK_DOWN:
		return rp_below;
	case VK_LEFT:
		return rp_leftside;
	case VK_RIGHT:
		return rp_righside;
	default:
		ASSERT(false);
		return rp_above;
	}
}

void cned_window_sheet::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
#ifdef _DEVELOPER_EDITION_
#ifdef _DEBUG
	if(roActionKBD.get_keycode() == VK_F6)
	{
		get_manager()->enable_swapping(true);
	}
#endif
#endif

	//start with focused element
	ned_ident idTarget = get_manager()->get_focus_element();
	
	if(NEDID_NOTHING != idTarget)
	{
		if(!get_manager()->is_element_disabled(idTarget))
		{
			_process_event_keydown(idTarget,roActionKBD,roResult);
			if(roResult.is_processed())
			{
				return;
			}
		}
	}

	//scan shortkey code table (redirect keystroke to element with shortkey)

	idTarget = get_manager()->lookup_shortkeys(roActionKBD);
	if(NEDID_NOTHING != idTarget)
	{
		if(!get_manager()->is_element_disabled(idTarget))
		{
			_process_event_keydown(idTarget,roActionKBD,roResult);
			if(roResult.is_processed())
			{
				return;
			}
		}
	}

	//scan shortkey code table again (move focus to element)
	idTarget = get_manager()->lookup_shortkeys(roActionKBD);
	if(NEDID_NOTHING != idTarget)
	{
		if(get_manager()->can_element_accept_focus(idTarget))
		{
			get_manager()->_mark_new_focus_element(idTarget);
		}
		roResult.set_processed();
		return;
	}

	ASSERT(!roResult.is_processed());

	switch(roActionKBD.get_keycode())
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		{
			ned_ident idStart = get_manager()->get_focus_element();
			if(idStart != NEDID_NOTHING)
			{
				ned_ident idFound = get_element_on_ident(idStart)->search_tree_for_nearest_element(keycode2rp(roActionKBD.get_keycode()));
				if(idFound != NEDID_NOTHING)
				{
					ASSERT(get_manager()->can_element_accept_focus(idFound));
					get_manager()->_mark_new_focus_element(idFound);
					roResult.set_processed();
					return;
				}
			}
			
			//push it to page
			get_toplevelpage()->on_event_keydown(roActionKBD,roResult);
		}
	break;
	case VK_PRIOR:
	case VK_NEXT:
		{
			//push it to page
			get_toplevelpage()->on_event_keydown(roActionKBD,roResult);
		}
	break;
	}
}

//---------------------------------------------------------------------------------------------
//	set cursor
//---------------------------------------------------------------------------------------------
eCursorType cned_window_sheet::on_event_set_cursor(const ng_point & roPoint)
{
	ned_ident idTarget = _find_mouse_target_element(roPoint);
	
	if(idTarget != NEDID_NOTHING)
	{
		ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));
		if(oPathToElement.is_empty())
		{
			return oPathToElement.target()->on_event_set_cursor(roPoint);
		}
		else
		{
			return oPathToElement.pop()->process_event_set_cursor(oPathToElement,roPoint);
		}
	}
	return ect_default;
}

//---------------------------------------------------------------------------------------------
//	command
//---------------------------------------------------------------------------------------------

void cned_window_sheet::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ned_ident idTarget = roActionCommand.get_target();
	ASSERT(idTarget != NEDID_NOTHING);

	ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));

	if(oPathToElement.is_empty())
	{
		oPathToElement.target()->on_event_command(roActionCommand,roResult);
	}
	else
	{
		oPathToElement.pop()->process_event_command(oPathToElement,roActionCommand,roResult);
	}
}

//-------------------------------------------------------------------------------------------------
// after event
//-------------------------------------------------------------------------------------------------
void cned_window_sheet::_on_after_event(const ned_action__ & roAction,ned_action_result & roResult)
{
	//1. make focus change -> it can spawn scroll request
	_make_focus_change(roAction.get_dc(),roResult);

	//2. perform scroll requests if any
	ned_ident idFocused = get_manager()->get_focus_element();
	if(idFocused != NEDID_NOTHING)
	{
		//ned_todo: czy jest widoczny
		//jeœli nie to wyœlij zdarzenie aby kontenery siê przeskorolowa³y - najpierw ten nag³êbiej,
		//a potem w górê, a¿ do ca³ej strony
	}
}

//-------------------- event helpers ----------------------------------------

ned_ident cned_window_sheet::_find_mouse_target_element(const ng_point & roArenaPoint)
{
	if(!is_inside_hit_area(roArenaPoint))
	{
		return NEDID_NOTHING;
	}
	return get_page()->find_element_from_point(roArenaPoint);
}

void cned_window_sheet::_make_focus_change(ng_dc & roDC,ned_action_result & roResult)
{
	ASSERT(get_manager() != NULL);

	ned_ident idOldFocus; 
	if(!get_manager()->_consume_focus_change(idOldFocus))
	{
		return; //no change no harm
	}
	

	ned_ident idNewFocus = get_manager()->get_focus_element(); 

	ASSERT(idNewFocus != idOldFocus);

	ned_action_focus oFocusChangeAction(roDC,idNewFocus,idOldFocus);

	//w odwrotnej kolejnoœci (got,lost) przeœlij event do kontrolki (call stack)
	//potrzebne bo scrollable__ mo¿e zrobiæ autoscroll na zmianê focus'a

	if(NEDID_NOTHING != idNewFocus)
	{
		_process_event_focus(idNewFocus,oFocusChangeAction,roResult);
	}
	if(NEDID_NOTHING != idOldFocus)
	{
		_process_event_focus(idOldFocus,oFocusChangeAction,roResult);
	}
	
	//w tradycyjnej kolejnoœci przygotuj eventy
	if(NEDID_NOTHING != idOldFocus)
	{
		SCP<ned_event_lostfocus> poEventDataSP = NewSCP(new ned_event_lostfocus(idOldFocus,idNewFocus));
		roResult.add_info(poEventDataSP);
	}
	if(NEDID_NOTHING != idNewFocus)
	{
		SCP<ned_event_gotfocus> poEventDataSP = NewSCP(new ned_event_gotfocus(idNewFocus,idOldFocus));
		roResult.add_info(poEventDataSP);
	}
}

void cned_window_sheet::_process_event_keydown(const ned_ident idTarget,const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	ASSERT(idTarget != NEDID_NOTHING);

	ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));
	
	if(oPathToElement.is_empty())
	{
		oPathToElement.target()->on_event_keydown(roActionKBD,roResult);
	}
	else
	{
		oPathToElement.pop()->process_event_keydown(oPathToElement,roActionKBD,roResult);
	}
}

void cned_window_sheet::_process_event_focus(const ned_ident idTarget,const ned_action_focus & roFocusAction,ned_action_result & roResult)
{
	ASSERT(idTarget != NEDID_NOTHING);

	ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));

	if(oPathToElement.is_empty())
	{
		oPathToElement.target()->on_event_focus(roFocusAction,roResult);
	}
	else
	{
		oPathToElement.pop()->process_event_focus(oPathToElement,roFocusAction,roResult);
	}
}

void cned_window_sheet::_process_event_timer(const ned_ident idTarget,const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	ASSERT(idTarget != NEDID_NOTHING);

	ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));

	if(oPathToElement.is_empty())
	{
		oPathToElement.target()->on_event_timer(roActionTimer,roResult);
	}
	else
	{
		oPathToElement.pop()->process_event_timer(oPathToElement,roActionTimer,roResult);
	}
}

void cned_window_sheet::_process_event_mouse_over(const ned_ident idTarget,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(idTarget != NEDID_NOTHING);

	ned_path_to_element oPathToElement(get_manager()->get_element_on_ident(idTarget));

	if(oPathToElement.is_empty())
	{
		oPathToElement.target()->on_event_mouse_over(roActionMouse,roResult);
	}
	else
	{
		oPathToElement.pop()->process_event_mouse_over(oPathToElement,roActionMouse,roResult);
	}
}


bool cned_window_sheet::is_inside_hit_area(const ng_point & roPoint) const
{
	return get_page()->is_inside_hit_area(roPoint);
}

//---------------------------------------------------------------------------------------------
//	update_layout
//---------------------------------------------------------------------------------------------
void cned_window_sheet::update_layout(const ned_action__ & roAction,ned_action_result & roResult,
	const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,ng_ycoord yReqYcoord)
{
	_realize_initial_focus();

	if(!get_page()->is_measure_pending())	//nothing new - exit
	{
		return;
	}

#ifdef _DEBUG
	CDebugTimeMeter oDTM("render",1);
#endif

	cned_post_render_manager oPostRenderManager(roPaintParam.is_printing());
	//perform page rendering 	
	cned_top_transport_renderer oWindowRenderer(roAction.get_dc(),yReqYcoord,roPaintParam.get_paint_mode(),
		roCompletArenaRect,oPostRenderManager);
	
	get_page()->render(oWindowRenderer);

	//finish rendering - post render pass

	get_page()->post_render(oPostRenderManager,ng_point());

#ifdef _DEBUG
	if(oPostRenderManager.is_any())
	{
		oPostRenderManager.dump();
	}
#endif
}

long cned_window_sheet::get_zoom() const
{
	return get_manager()->get_zoom();
}

void cned_window_sheet::set_zoom(long nZoom)
{
	get_manager()->set_zoom(nZoom);
}


void cned_window_sheet::update_split_info(cpb_split_info & roSplitInfo)
{
	get_page()->update_split_info(ng_point(),roSplitInfo);
}

void cned_window_sheet::make_split(cpb_split_manager & roSplitManager)
{
	get_page()->make_split(ng_point(),roSplitManager);
}

void cned_window_sheet::_prepare_tooltip()
{
	ned_ident nTargetIdent = get_manager()->get_mouse_over_element();
	if(nTargetIdent == NEDID_NOTHING)
	{
		return;
	}

	//prepare tooltip info
	SCP<cned_element> poTargetSP = get_manager()->get_element_on_ident(nTargetIdent);
	ng_string oTipTextString; 
	poTargetSP->get_prop_tooltip_text(oTipTextString);
	SCP<cnui_shortkey> poShortKeySP = get_manager()->get_shortkey(nTargetIdent);
	if(poShortKeySP.PointsObject())
	{
		//LANGUAGE:PL
		ng_string oShortKeyString = "klawisz skrótu: " + poShortKeySP->GetDescription();

		if(!oTipTextString.IsEmpty())
		{
			oTipTextString += " (" + oShortKeyString + ") ";
		}
		else
		{
			oTipTextString = oShortKeyString;
		}
	}

#ifdef _DEBUG
	oTipTextString += Long2String(nTargetIdent);
#endif

	if(!oTipTextString.IsEmpty())
	{
		m_poArena->show_tooltip(oTipTextString);
	}
	else
	{
		m_poArena->cancel_tooltip();
	}
}

void cned_window_sheet::_realize_initial_focus()
{
	ASSERT(get_manager() != NULL);

	//jesli jest focus to OK
	ned_ident idFocusElement = get_manager()->get_focus_element();
	
	if(idFocusElement != NEDID_NOTHING)
	{
		return;
	}
	ned_ident idDefinedFocus = m_poWindow->get_prop_initial_focus();
	//nie ma - próbujemy wzi¹æ wartoœæ startfocus podan¹ z XML lub VB
	if(NEDID_NOTHING != idDefinedFocus)
	{
		//sprawdŸ czy jest prawid³owa definicja (musi istnieæ i byæ focusowalny)
		SCP<cned_element> poElementSP = get_manager()->get_element_on_ident(idDefinedFocus);
		if(poElementSP.PointsObject())
		{
			if(get_manager()->can_element_accept_focus(idDefinedFocus))
			{
				idFocusElement = idDefinedFocus;
			}
		}
	}

	//nadal nie ma - szukaj pierwszego dopuszczalnego
	if(NEDID_NOTHING == idFocusElement)
	{
		idFocusElement = get_page()->find_element_next_prev(NEDID_NOTHING,true);
	}

	//jeœli coœ znaleŸliœmy - ustaw
	if(NEDID_NOTHING != idFocusElement)
	{
		ASSERT(get_manager()->can_element_accept_focus(idFocusElement));
		get_manager()->_mark_new_focus_element(idFocusElement);
	}
}

void cned_window_sheet::set_layout_invalid_to_all()
{
	get_manager()->set_layout_invalid_to_all();
}

void cned_window_sheet::apply_attributes(const ned_currattributes & roCurrAttrib)
{
	get_page()->apply_attributes(roCurrAttrib);
}
