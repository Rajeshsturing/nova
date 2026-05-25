/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_intedit		/ <intedit>
		kontrolka edycji integerów
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "intedit_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cned_intedit::cned_intedit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_edit__(poManager,ned_intedit,idThis)
{
	_set_new_buffer_text(m_State,"0");
}

void cned_intedit::set_fixed_properties()
{
	cned_edit__::set_fixed_properties();

	set_prop_charwidth(6);
	set_prop_alignment(eal_right);
}

//--------------------------------------------------------------------
// helpers
//--------------------------------------------------------------------
inline void cned_intedit::_correct_empty_buffer()
{
	if(m_State.m_oBufferString.IsEmpty())
	{
		m_State.m_oBufferString = "0";
		m_State.move_caret_to(1,false);
	}
}

inline void cned_intedit::_correct_zero_buffer()
{
	if(_ttol(m_State.m_oBufferString) == 0)
	{
		m_State.m_oBufferString.Empty();
		m_State.move_caret_to(0,false);
	}
}

//---------------------------------------------------------
// buffer <-> data convertions
//---------------------------------------------------------

bool cned_intedit::buffer2variant(CSmartOleVariant & roSOV) const
{
	roSOV = _ttol(m_State.m_oBufferString);
	return true;
}

bool cned_intedit::variant2buffer(const CSmartOleVariant & roSOV)
{
	long nValue = roSOV.GetLong();
	ng_string oString = Long2String(nValue);
	if(oString != m_State.m_oBufferString)
	{
		_set_new_buffer_text(m_State,oString);
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------
long cned_intedit::_act_move(UINT nVKCode,bool /*bWithCtrl*/)
{
	switch(nVKCode)
	{
	case VK_LEFT:
		if(m_State.get_caret_pos() > 0)
		{
			//nie przesuwaj gdy jest minus
			if(IsDigit(m_State.m_oBufferString.operator []( m_State.get_caret_pos() - 1)))
			{
				return m_State.get_caret_pos() - 1;
			}
		}
	break;
	case VK_RIGHT:
		return min(m_State.get_caret_pos() + 1,m_State.m_oBufferString.GetLength());
	case VK_HOME:
		if(IsDigit(m_State.m_oBufferString[0]))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	case VK_END:
		return m_State.m_oBufferString.GetLength();
	default:
		;
	}
	//no change
	return m_State.get_caret_pos();
}

bool cned_intedit::_act_delete(bool /*bWithShift*/)
{
	if(m_State.delete_selected_chars())
	{
		_correct_empty_buffer();
		return true;
	}
	else
	{
		if(m_State.get_caret_pos() < m_State.m_oBufferString.GetLength())
		{
			m_State.delete_char();
			_correct_empty_buffer();
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool cned_intedit::_act_backspace(bool /*bWithShift*/)
{
	if(m_State.delete_selected_chars())
	{
		_correct_empty_buffer();
		return true;
	}
	else
	{
		if(m_State.get_caret_pos() > 0)
		{
			m_State.move_caret_by(-1,false);
			m_State.delete_char();
			_correct_empty_buffer();
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool cned_intedit::_act_data(UINT nTranslatedChar)
{
	switch(TCHAR(nTranslatedChar))
	{
	case '-':
	{
		ASSERT(m_State.m_oBufferString.GetLength());
		if(IsDigit(m_State.m_oBufferString[0]))	//nie ma minus'a - dodaj
		{
			m_State.m_oBufferString.Insert(0,'-');
			m_State.move_caret_by(+1,false);
		}
		else //jest ju¿ minus - usuñ
		{
			m_State.m_oBufferString.Delete(0,1);
			m_State.move_caret_by(-1,false);
			_correct_empty_buffer();
		}
		return true;
	}
	case '0':	case '1':	case '2':	case '3':	case '4':	case '5':	case '6':	case '7':	case '8':	case '9':
	{
		_correct_zero_buffer();
		m_State.insert_char(TCHAR(nTranslatedChar));
		return true;
	}
	default:
		return false;
	}
}

bool cned_intedit::_act_paste_from_string(const ng_string & roString)
{
	long nValue = _ttol(roString);
	_set_new_buffer_text(m_State,Long2String(nValue));
	return true;
}

void cned_intedit::_act_copy_to_string(ng_string & roString)
{
	if(m_State.is_selection())
	{
		roString = m_State.m_oBufferString.Mid(m_State.m_nCharSelFirst,m_State.m_nCharSelLast - m_State.m_nCharSelFirst);
	}
	else
	{
		roString = m_State.m_oBufferString;
	}
}

bool cned_intedit::_act_cut_to_string(ng_string & roString)
{
	_act_copy_to_string(roString);
	m_State.delete_selected_chars();
	_correct_zero_buffer();
	_correct_empty_buffer();
	return true;
}
