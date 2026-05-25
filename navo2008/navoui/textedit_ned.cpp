/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_textedit		/ <edit>
		kontrolka edycji tekstów
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "textedit_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long cned_textedit::_act_move(UINT nVKCode,bool bWithCtrl)
{
	if(false && get_prop_clearonly())
	{
		if(nVKCode == VK_END)
		{
			return m_State.m_oBufferString.GetLength();
		}
		else
		{
			return m_State.get_caret_pos();
		}
	}

	switch(nVKCode)
	{
	case VK_LEFT:

		if(bWithCtrl)
		{
			return _act_move_left_word(m_State.m_oBufferString,m_State.get_caret_pos());
		}
		else
		{
			return max(0,m_State.get_caret_pos() - 1);
		}
	case VK_RIGHT:
		if(bWithCtrl)
		{
			return _act_move_right_word(m_State.m_oBufferString,
				m_State.get_caret_pos(),m_State.m_oBufferString.GetLength());
		}
		else
		{
			return min(m_State.get_caret_pos() + 1,m_State.m_oBufferString.GetLength());
		}
	case VK_HOME:
		return 0;
	case VK_END:
		return m_State.m_oBufferString.GetLength();
	default:
		return m_State.get_caret_pos();
	}
}

bool cned_textedit::_act_delete(bool /*bWithShift*/)
{ 
	if(m_State.delete_selected_chars())
	{
		return true;
	}
	else
	{
		if(m_State.get_caret_pos() < m_State.m_oBufferString.GetLength())
		{
			m_State.delete_char();
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool cned_textedit::_act_backspace(bool /*bWithShift*/)	//kasowanie z lewej
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
			m_State.delete_char();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void cned_textedit::_after_got_focus()
{
	//move to begin and select all
	m_State.move_caret_to(0,false);
	m_State.m_nCharSelLast = m_State.m_oBufferString.GetLength();
	m_State.m_nCharSelFirst = m_State.get_caret_pos();
}
