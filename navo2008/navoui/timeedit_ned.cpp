/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_timeedit		/ <time>
		kontrolka edycji czasu
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "timeedit_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------
// buffer <-> data convertions
//---------------------------------------------------------

bool cned_timeedit::buffer2variant(CSmartOleVariant & roSOV) const
{
	if(m_State.m_oBufferString == _metrics().timeedit().get_null_text())
	{
		roSOV = GetNullTimeSOV();
	}
	else
	{
		if(m_State.m_oBufferString.Find('?') != -1)
		{
			return false;
		}
		long nHours = atol(LPCTSTR(m_State.m_oBufferString));
		long nMinutes = atol(LPCTSTR(m_State.m_oBufferString)+3);
		if(nMinutes > 60)
		{
			return false;
		}
		if(nHours > 23)
		{
			return false;
		}
		roSOV = CSmartOleVariant(long(nHours*100+nMinutes));
	}
	return true;
}

bool cned_timeedit::variant2buffer(const CSmartOleVariant & roSOV)
{
	ng_string oString;
	ASSERT(roSOV.Type() == VT_I4);
	if(roSOV == GetNullTimeSOV())
	{
		oString = _metrics().timeedit().get_null_text();
	}
	else
	{
		long nTimeValue = roSOV.GetLong();
		oString.Format("%02d:%02d",nTimeValue/100,nTimeValue%100);
	}
	ASSERT(!oString.IsEmpty());
	if(oString != m_State.m_oBufferString)
	{
		/*
			jeœli jesteœmy w trakcie edycji (mamy focus)
			i ktoœ próbuje przypisaæ coœ do kontrolki
			a nasza wartoœæ jest nieprawid³owa, to ignorujemy przypisanie
		*/
		if(get_prop_focus())		//gdy mamy focus
		{
			CSmartOleVariant oTestSOV;
			if(!buffer2variant(oTestSOV))	//ale nasza wartoœæ jest nieprawid³owa
			{
				return false;				//to ignoruj wartoœæ podan¹ 
			}
		}
		_set_new_buffer_text(m_State,oString);
		return true;
	}
	return false;
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------

long cned_timeedit::_act_move(UINT nVKCode,bool /*bWithCtrl*/)
{
	switch(nVKCode)
	{
	case VK_LEFT:
		if(m_State.get_caret_pos() > 0)
		{
			//skip separator
			if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()-1) == _metrics().timeedit().get_separator())
			{
				ASSERT(m_State.get_caret_pos() - 2 >= 0);
				return m_State.get_caret_pos() - 2;
			}
			else
			{
				return m_State.get_caret_pos() - 1;
			}
		}
	break;
	case VK_RIGHT:
		if(m_State.get_caret_pos() < _metrics().timeedit().get_format_len())
		{
			//skip separator
			if(m_State.get_caret_pos() < _metrics().timeedit().get_format_len() - 1)
			{
				if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+1) == _metrics().timeedit().get_separator())
				{
					return m_State.get_caret_pos() + 2;
				}
			}
			//nie separator
			return m_State.get_caret_pos() + 1;
		}
	break;
	case VK_HOME:
		return 0;
	case VK_END:
		return _metrics().timeedit().get_format_len();
	default:
		;
	}
	//no change
	return m_State.get_caret_pos();
}

bool cned_timeedit::_act_delete(bool /*bWithShift*/)
{
	if(m_State.m_nCharSelFirst == 0 && m_State.m_nCharSelLast == _metrics().timeedit().get_format_len())
	{
		_set_new_buffer_text(m_State,_metrics().timeedit().get_null_text());
		return true;
	}
	if(m_State.get_caret_pos() < _metrics().timeedit().get_format_len())
	{
		if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) != '?')
		{
			m_State.overtype_char('?');
			return true;
		}
	}
	return false;
}

bool cned_timeedit::_act_backspace(bool bWithShift)
{
	long nNewCaretPos = _act_move(VK_LEFT,false);
	if(nNewCaretPos != m_State.get_caret_pos() || m_State.is_selection())
	{
		m_State.move_caret_to(nNewCaretPos,bWithShift);
		m_State.overtype_char('?');
		return true;
	}
	return false;
}

bool cned_timeedit::_act_data(UINT nTranslatedChar)
{
	bool bChange = false;
	if(m_State.get_caret_pos() < _metrics().timeedit().get_format_len() && m_State.get_caret_pos() >= 0)
	{
		//at separator - just move
		if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) == _metrics().timeedit().get_separator())
		{
			m_State.move_caret_by(+1,false);
			bChange = true;
		}
		else //replace char
			if(IsDigit(TCHAR(nTranslatedChar)))
			{
				long nVal = TCHAR(nTranslatedChar) - '0';
				//--------------------------------
				switch(m_State.get_caret_pos())
				{
				case 0:		//allowed 0,1,2
					if(nVal >= 3)
					{
						goto skip;
					}
				break;
				case 1:		//allowed 0-9 when [0] = 0,1 or 0,1,2,3,3 when [0] = 2
					if(m_State.m_oBufferString[0] == '2')
					{
						if(nVal >= 4)
						{
							goto skip;
						}
					}
				break;
				case 3:		//allowed 0,5
					if(nVal >= 6)
					{
						goto skip;
					}
				}
				//--------------------------------
				m_State.overtype_char(nTranslatedChar);
				m_State.move_caret_by(+1,false);
				//at separator - do auto move
				if(m_State.get_caret_pos() < _metrics().timeedit().get_format_len())
				{
					if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) == _metrics().timeedit().get_separator())
					{
						m_State.move_caret_by(+1,false);
					}
				}
				bChange = true;
skip:
				; //noaction
			}
	}
	return bChange;
}

bool cned_timeedit::_act_paste_from_string(const ng_string & roString)
{
	//sprawdzamy czy zawartoœæ jest prawid³owa
	ng_string oSaveString(m_State.m_oBufferString);
	m_State.m_oBufferString = roString;
	CSmartOleVariant oTestSOV;
	if(!buffer2variant(oTestSOV))
	{
		//nie dobra - odtwarzamy
		m_State.m_oBufferString = oSaveString;
		return false;
	}
	_set_new_buffer_text(m_State,roString);
	return true;
}

void cned_timeedit::_act_copy_to_string(ng_string & roString)
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

bool cned_timeedit::_act_cut_to_string(ng_string & roString)
{
	_act_copy_to_string(roString);
	return false;
}

void cned_timeedit::_after_got_focus()
{
	//move caret to begin and select all
	m_State.move_caret_to(0,false);
	m_State.m_nCharSelLast = m_State.m_oBufferString.GetLength();
	m_State.m_nCharSelFirst = 0;
}
