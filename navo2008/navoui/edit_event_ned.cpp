/*
	NAVO Enterprise 2003
	2003-03-29

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych

	event part
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "CommandList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cned_edit__::_after_got_focus()
{
	//move caret to end and select all
	m_State.move_caret_to(_act_move(VK_END,false),false);
	m_State.m_nCharSelLast = m_State.get_caret_pos();
	m_State.m_nCharSelFirst = 0;
}

//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

class cned_drag_info_edit: public cned_drag_info__
{
public:
	cned_drag_info_edit(const ng_point & roStartingArenaPoint,SCP<cned_edit__> poEditSP);
	virtual bool on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
	virtual bool on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult);
private:

	SCP<cned_edit__> m_poEditSP;
};
//-------------------------------------------------------------------------------------------------
cned_drag_info_edit::cned_drag_info_edit(const ng_point & roStartingArenaPoint,
										 SCP<cned_edit__> poEditSP) :
	cned_drag_info__(roStartingArenaPoint),
	m_poEditSP(poEditSP)
{
	ASSERT(m_poEditSP.PointsObject());
}

bool cned_drag_info_edit::on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	m_poEditSP->_on_event_mouse_selection(roActionMouseDrag,roResult,true);
	return true;
}

bool cned_drag_info_edit::on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	m_poEditSP->_on_event_mouse_selection(roActionMouseDrag,roResult,true);
	return true;
}

//-------------------------------------------------------------------------------------------------
// mouse click
//-------------------------------------------------------------------------------------------------
void cned_edit__::_on_event_mouse_selection(const ned_action_mouse & roActionMouse,ned_action_result & roResult,bool bSelect)
{
	ng_point oLocalPoint(roActionMouse.get_mouse_position());
	_screen2local(oLocalPoint);
	long nNewPosition = _find_char_from_local_point(oLocalPoint,roActionMouse.get_dc());
	if(nNewPosition != m_State.get_caret_pos())
	{
		cstate oSaveState = m_State;
		_after_act_move(nNewPosition,bSelect);
		_on_successfull_action(roActionMouse,oSaveState,roResult);
	}
}

void cned_edit__::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	//ned_to_do:
	if(get_manager()->get_focus_element() == get_ident())
	{
		if(roActionMouse.is_LEFT_click())
		{
			_on_event_mouse_selection(roActionMouse,roResult,(roActionMouse.get_flags() & MK_SHIFT) != 0);
			get_manager()->store_drag_info(
				NewSCP(new cned_drag_info_edit(roActionMouse.get_mouse_position(),
					NewSCP(this,true))));
			roResult.set_processed();
		}
	}
	else
	{
		_set_focus_to_me();
		roResult.set_processed();
	}
}

void cned_edit__::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_RIGHT_click())
	{
		_fill_command_list(roResult);
	}
}

void cned_edit__::_fill_command_list(ned_action_result & roResult)
{
	SCP<ned_event_command_list> poEventCmdListSP = NewSCP(new ned_event_command_list(get_ident()));

	ng_rect oRect;
	get_bounding_rect(0,oRect);
	poEventCmdListSP->m_oStartPoint = oRect.get_bottomleft();
	_local2screen(poEventCmdListSP->m_oStartPoint);

	//komenda kopiuj
	//LANGUAGE:PL
	SCP<CHyperLinkInfo> poCopyHLISP = init_control_command_hli(get_ident(),sccv_copy);
	poEventCmdListSP->get_command_list()->AddCommand(_T("&Kopiuj"),poCopyHLISP);

	if(!get_prop_disabled())
	{
		//komenda paste
		//LANGUAGE:PL
		SCP<CHyperLinkInfo> poPasteHLISP = init_control_command_hli(get_ident(),sccv_paste);
		poEventCmdListSP->get_command_list()->AddCommand(_T("&Wklej"),poPasteHLISP);
	}

	roResult.add_info(poEventCmdListSP);
}

//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------

void cned_edit__::on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	if(roActionTimer.get_timerid() == ARENA_CONTROL_TIMER_ID)
	{
		m_State.m_bCaretOn = !m_State.m_bCaretOn;
		
		_invalidate_caret_paint();

		roResult.set_processed();
	}
}

//-------------------------------------------------------------------------------------------------
// focus
//-------------------------------------------------------------------------------------------------
void cned_edit__::on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult)
{
	cstate oOldState = m_State;
	
	//skasuj selekcjê przy utracie focus'a
	if(get_ident() != roActionFocus.get_got_focus_ident())
	{
		//wyrejestruj siê w timerze
		get_manager()->unregister_for_timer(get_ident());
		m_State.clear_selection();
	}
	else
	{
		//zarejestruj siê aby otrzymywaæ timer-notyfikacje (miganie caret'a)
		get_manager()->register_for_timer(get_ident(),5,true);
		_after_got_focus();
	}
	
	//need update infrastrucure - selection position etc.
	_set_infra_update_pending();	
	_update_infrastructure(roActionFocus.get_dc(),oOldState);

	_invalidate_all_paint();
}

//-------------------------------------------------------------------------------------------------
// command
//-------------------------------------------------------------------------------------------------
void cned_edit__::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(roActionCommand.get_target() == get_ident());

	cstate oSaveState = m_State;
	bool bCommandSuccess = false;

	switch(roActionCommand.get_verb())
	{
	case sccv_put_value:
	{
		set_prop_value(roActionCommand.get_command()->GetProp(PROPC_VARIANT));
		bCommandSuccess = true;
	}
	break;
	case sccv_paste_data:		//PROPC_VARIANT = data value
	{
		bCommandSuccess = _act_paste_from_string(roActionCommand.get_command()->GetStrProp(PROPC_VARIANT));
	}
	break;
	case sccv_paste:
	{
		bCommandSuccess = _act_paste();
	}
	break;
	case sccv_copy:
	{
		_act_copy();
		bCommandSuccess = true;
	}
	break;
	default:
		cned_rect_element_::on_event_command(roActionCommand,roResult);
	}


	if(bCommandSuccess)
	{
		_on_successfull_action(roActionCommand,oSaveState,roResult);
	}
}

