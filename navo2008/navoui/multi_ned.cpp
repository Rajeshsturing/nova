/*
	NAVO Enterprise 2003
	2003-04-07

	navo enhanced display (NED)

	ned_multiedit		/ <multiline>
		kontrolka edycji tekstów wieloliniowych

		core part
*/

#include "stdafx.h"
#include "multiline_helper_ned.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "scroll_helper_ned.h"
#include "multi_ned.h"
#include "CommandList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_multiedit::cned_multiedit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_rect_container_(poManager,ned_multiline,idThis),
	scroll_helper__(poManager,idThis),
	m_bDataValid(true),
	m_bUseEnter(true),
	m_bInfraUpdPending(true)
{
	set_prop_tabstop(true);
}

//-------------- attribute functions -------------------------
void cned_multiedit::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();

	set_prop_forecolor(_metrics().edit().get_forecolor());
	set_prop_backcolor(_metrics().edit().get_backcolor());
	set_prop_backcolor2(_metrics().edit().get_backcolor());
	set_prop_border_type(_metrics().edit().get_border_type());
	set_prop_border_color(_metrics().edit().get_forecolor());
	set_prop_ignore_sys_disable(false);
}

//------ property GET -----------------
void cned_multiedit::get_prop_tooltip_text(ng_string & roText) const
{
	cned_rect_container_::get_prop_tooltip_text(roText);
	if(!roText.IsEmpty())
	{
		roText += " ";
	}
	//LANGUAGE:PL
	roText += _T("(Aby przejœæ do nowej linii naciœnij Ctrl+Enter)");
}

void cned_multiedit::_on_successfull_action(const ned_action__ & roAction,const cstate & roOldState,ned_action_result & roResult)
{
	if(roOldState.get_buffer() != m_State.get_buffer())
	{
		CSmartOleVariant oSOV(m_State.get_buffer());
		SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
		poEventDataSP->set_data(oSOV); 
		roResult.add_info(poEventDataSP);
		set_prop_valid(true);
	}
	else
	{
		roResult.set_processed();
	}
	_set_infra_update_pending();	
	_update_infrastructure(roAction.get_dc(),roOldState,false);
}

//-----------------------------------------------------------------------------------------
long cned_multiedit::_get_line_for_char_pos(long nCharPos) const
{
	//szukamy linii zawieraj¹cej dany znak
	if(m_oMLM.get_line_count() > 0)
	{
		long nFirstChar = 0;
		long nLastChar = -1;
		long nLineNr = m_oMLM.get_line_count() - 1;

		while(m_oMLM.get(nLineNr,nFirstChar,nLastChar))
		{
			if(nFirstChar <= nCharPos)
			{
				return nLineNr;
			}
			nLineNr--;
		}
		ASSERT(false);
		return nLineNr;
	}
	else
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------
// event handlers 
//-------------------------------------------------------------------------------------------------

void cned_multiedit::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	if(roActionKBD.get_keycode() == VK_APPS)
	{
		_fill_command_list(roResult);
		return;
	}

	cstate oOldState = m_State;
	if(_dispatch_action(roActionKBD))
	{
		_on_successfull_action(roActionKBD,oOldState,roResult);
	}
}

UINT translate_keycode_2_character(UINT keycode,UINT scancode);

bool cned_multiedit::_dispatch_action(const ned_action_kbd & roActionKBD)
{
	//lewy Alt + coœtam
	if(!roActionKBD.is_CTRL() && roActionKBD.is_ALT())
	{
		return false;
	}

	//Ctrl + coœtam
	if(roActionKBD.is_CTRL() && !roActionKBD.is_ALT())
	{
		switch(roActionKBD.get_keycode())
		{
		case 'V':
			return _act_paste();
		case 'C':
			_act_copy();
			return false;
		case 'X':
			return _act_cut();
		case VK_RETURN:
			return _act_data(MULTILINE_NEWLINE_CHAR);
		default:
			;
		}
	}

	//normalny (ewentualnie z Shift)
	switch(roActionKBD.get_keycode())
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_END:
	case VK_HOME:
	case VK_UP:
	case VK_DOWN:
	{
		long nNewCaretPos = _act_move(roActionKBD.get_keycode(),roActionKBD.is_CTRL(),roActionKBD.get_dc());
		if(nNewCaretPos != m_State.get_caret_pos() || m_State.is_selection())
		{
			m_State.move_caret_to(nNewCaretPos,roActionKBD.is_SHIFT());
			m_State.m_bCaretOn = true;	//w³¹cz caret podczas przesuwania - lepiej widaæ
			return true;
		}
		else
		{
			return false;
		}
	}
	case VK_DELETE:
		return _act_delete(roActionKBD.is_SHIFT());
	case VK_BACK:
		return _act_backspace(roActionKBD.is_SHIFT());
	case VK_RETURN:
		if(get_prop_use_enter())
		{
			return _act_data(MULTILINE_NEWLINE_CHAR);
		}
	default:
		{
			UINT nTraslatedChar = translate_keycode_2_character(roActionKBD.get_keycode(),roActionKBD.get_scancode());
			if(nTraslatedChar == 0)
			{
				return false;
			}
			return _act_data(nTraslatedChar);
		}
	}
}



bool cned_multiedit::_act_data(UINT nTranslatedChar)
{
	m_State.delete_selected_chars();

	ASSERT(m_State.get_caret_pos() >= 0);			//jeœli piszemy tu musimy mieæ ustawiony kursor

	m_State.__insert_to_buffer(m_State.get_caret_pos(),TCHAR(nTranslatedChar));
	m_State.move_caret_by(+1,false);
	return true;
}

long cned_multiedit::_act_move(UINT nVKCode,bool bWithCtrl,ng_dc & roDC)
{
	switch(nVKCode)
	{
	case VK_LEFT:
		if(bWithCtrl)
		{
			return _act_move_left_word(m_State.get_buffer(),m_State.get_caret_pos());
		}
		else
		{
			return max(0,m_State.get_caret_pos() - 1);
		}
	case VK_RIGHT:
		if(bWithCtrl)
		{
			return _act_move_right_word(m_State.get_buffer(),
				m_State.get_caret_pos(),m_State.get_buffer_size());
		}
		else
		{
			return min(m_State.get_caret_pos() + 1,m_State.get_buffer_size());
		}
	case VK_HOME:
		if(bWithCtrl)
		{
			return 0;
		}
		else
		{
			long nLineNr = _get_line_for_char_pos(m_State.get_caret_pos());
			long nFirstChar = 0;
			long nLastChar = -1;
			if(nLineNr < m_oMLM.get_line_count())
			{
				VERIFY(m_oMLM.get(nLineNr,nFirstChar,nLastChar));
			}
			return nFirstChar;
		}
	case VK_END:
		if(bWithCtrl)
		{
			return m_State.get_buffer_size();
		}
		else
		{
			long nLineNr = _get_line_for_char_pos(m_State.get_caret_pos());
			if(nLineNr >= m_oMLM.get_line_count() - 1)	//ostatnia linia
			{
				return m_State.get_buffer_size();
			}
			else
			{
				//zwróæ 1-znak przed pocz¹tkiem nastêpnej (ze wzglêdu na dziury)
				long nFirstChar;
				long nLastChar;
				VERIFY(m_oMLM.get(++nLineNr,nFirstChar,nLastChar));
				return --nFirstChar;
			}
		}
	case VK_UP:
	{
		if(m_State.m_nCaretLine > 0)
		{
			ASSERT(!m_bInfraUpdPending);
			ng_rect oCaretRect;
			_get_caret_rect(ng_point(),oCaretRect);
			long nNewCharPos = _get_char_pos_for_line_and_dx(oCaretRect.get_left(),m_State.m_nCaretLine-1,roDC);
			if(nNewCharPos >= 0)
			{
				return nNewCharPos;
			}
		}
	}
	break;
	case VK_DOWN:
	{
		if(m_State.m_nCaretLine < m_oMLM.get_line_count() - 1)
		{
			ASSERT(!m_bInfraUpdPending);
			ng_rect oCaretRect;
			_get_caret_rect(ng_point(),oCaretRect);
			long nNewCharPos = _get_char_pos_for_line_and_dx(oCaretRect.get_left(),m_State.m_nCaretLine+1,roDC);
			if(nNewCharPos >= 0)
			{
				return nNewCharPos;
			}
		}
	}
	break;
	default:
		;
	}
	return m_State.get_caret_pos();
}

bool cned_multiedit::_act_delete(bool bWithShift)
{
	if(m_State.delete_selected_chars())
	{
		return true;
	}
	else
	{
		if(m_State.get_caret_pos() < m_State.get_buffer_size())
		{
			m_State.__delete_from_buffer(m_State.get_caret_pos(),1);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool cned_multiedit::_act_backspace(bool bWithShift)
{
	if(m_State.delete_selected_chars())
	{
		return true;
	}
	else
	{
		if(m_State.get_caret_pos() > 0)
		{
			m_State.move_caret_by(-1,false);
			m_State.__delete_from_buffer(m_State.get_caret_pos(),1);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool put_string_to_clipboard_text(const ng_string & roString);
bool get_string_from_clipboard_text(ng_string & roString);


bool cned_multiedit::_act_paste()
{
	ASSERT(!get_prop_disabled());

	CString oString;
	if(!get_string_from_clipboard_text(oString))
	{
		return false;
	}

	return _act_paste_from_string(oString);
}

bool cned_multiedit::_act_cut()
{
	ASSERT(!get_prop_disabled());

	ng_string oStringForCopy;
	if(!_act_cut_to_string(oStringForCopy))
	{
		return false;
	}
	return put_string_to_clipboard_text(oStringForCopy);
}

void cned_multiedit::_act_copy()
{
	ng_string oStringForCopy;
	_act_copy_to_string(oStringForCopy);
	put_string_to_clipboard_text(oStringForCopy);
}

bool cned_multiedit::_act_paste_from_string(const ng_string & roString)
{
	ng_string oInternalTextString;
	text2internaltext(roString,oInternalTextString);

	m_State.delete_selected_chars();

	ASSERT(m_State.get_caret_pos() >= 0);			//jeœli piszemy tu musimy mieæ ustawiony kursor

	m_State.__insert_to_buffer(m_State.get_caret_pos(),oInternalTextString);
	m_State.move_caret_by(oInternalTextString.GetLength(),false);
	return true;
}

void cned_multiedit::_act_copy_to_string(ng_string & roString)
{
	ng_string oInternalTextString;
	if(m_State.is_selection())
	{
		oInternalTextString = m_State.get_buffer().Mid(m_State.get_start_of_selection(),
			m_State.get_end_of_selection() - m_State.get_start_of_selection());
	}
	else
	{
		oInternalTextString = m_State.get_buffer();
	}
	internaltext2text(oInternalTextString,roString);
}

bool cned_multiedit::_act_cut_to_string(ng_string & roString)
{
	if(m_State.is_selection())
	{
		roString = m_State.get_buffer().Mid(m_State.get_start_of_selection(),
			m_State.get_end_of_selection() - m_State.get_start_of_selection());
		m_State.delete_selected_chars();
	}
	else
	{
		roString = m_State.get_buffer();
		m_State.__set_buffer("");
		m_State.move_caret_to(0,false);
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
// mouse click
//-------------------------------------------------------------------------------------------------
void cned_multiedit::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ng_point oLocalPoint(roActionMouse.get_mouse_position());
	_screen2local(oLocalPoint);
	oLocalPoint.offset(get_scroll_pos());
	long nLine = oLocalPoint.get_y() / m_State.m_dyLineHeight;
	cstate oOldState = m_State;

	long nNewCaretPos = _get_char_pos_for_line_and_dx(oLocalPoint.get_x(),nLine,roActionMouse.get_dc());
	if(nNewCaretPos != m_State.get_caret_pos() || m_State.is_selection())
	{
		m_State.move_caret_to(nNewCaretPos,((roActionMouse.get_flags() & MK_SHIFT) == MK_SHIFT));
		m_State.m_bCaretOn = true;	//w³¹cz caret podczas przesuwania - lepiej widaæ
		_on_successfull_action(roActionMouse,oOldState,roResult);
	}

	_set_focus_to_me();
	roResult.set_processed();
}

void cned_multiedit::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_RIGHT_click())
	{
		_fill_command_list(roResult);
	}
}

void cned_multiedit::_fill_command_list(ned_action_result & roResult)
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
void cned_multiedit::on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult)
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
void cned_multiedit::on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult)
{
	if(get_ident() != roActionFocus.get_got_focus_ident())
	{
		//wyrejestruj siê w timerze
		get_manager()->unregister_for_timer(get_ident());
	}
	else
	{
		//zarejestruj siê aby otrzymywaæ timer-notyfikacje (miganie caret'a)
		get_manager()->register_for_timer(get_ident(),5,true);

		cstate oOldState = m_State;
		//move caret to end and select all
		m_State.move_caret_to(_act_move(VK_END,false,roActionFocus.get_dc()),false);

		//need update infrastrucure - selection position etc.
		_set_infra_update_pending();	
		_update_infrastructure(roActionFocus.get_dc(),oOldState,false);
	}

	_invalidate_all_paint();
}

//-------------------------------------------------------------------------------------------------
// command
//-------------------------------------------------------------------------------------------------
void cned_multiedit::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
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
	case sccv_scroll_to:
	{
		ng_rect oScrollableRect;
		ng_point oCurrentPoint;
		_local2screen(oCurrentPoint);
		//tu nie robimy korekty w rodzaju oCurrentPoint.offset(get_scroll_pos());
		//poniewa¿ multiedit nie ma w³asnego local2screen poniewa¿ nie ma dzieci
		//wiêc go nie potrzebuje
		_get_text_rect(oCurrentPoint,oScrollableRect);
		_scroll_event_command(roActionCommand,roResult,oScrollableRect);
	}
	break;
	default:
		cned_rect_container_::on_event_command(roActionCommand,roResult);
	}


	if(bCommandSuccess)
	{
		_on_successfull_action(roActionCommand,oSaveState,roResult);
	}

}

//---------------------------------------------------------------------- 
ned_ident cned_multiedit::find_element_from_point(const ng_point & roPoint)
{
	ASSERT(is_inside_hit_area(roPoint));

	//przelicz na wspó³rzêdne wewnêtrzne
	{
		ng_point oInternalPoint(roPoint);
		oInternalPoint.offset(-m_oVectorSize);
		
		//sprawdzenie scroll'a
		if(_scroll_is_inside_hit_area(oInternalPoint))
		{
			return _scroll_find_element_from_point(oInternalPoint);
		}
	}

	return get_ident();
}

