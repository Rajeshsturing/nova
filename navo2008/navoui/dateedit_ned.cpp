/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_dateedit		/ <dateedit>
		kontrolka edycji dat
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "dateedit_ned.h"
#include "commandlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------
// buffer <-> data convertions
//---------------------------------------------------------

bool cned_dateedit::buffer2variant(CSmartOleVariant & roSOV) const
{
	if(m_State.m_oBufferString == _metrics().dateedit().get_null_text())
	{
		roSOV = GetNullDateSOV();
	}
	else
	{
		//OS_API_CALL
		USES_CONVERSION;
		DATE date;
		HRESULT hr = ::VarDateFromStr((LPOLESTR)T2COLE(m_State.m_oBufferString), 
			GetWorkingLCID(),LOCALE_NOUSEROVERRIDE, &date);
		if(hr != S_OK || date < DATE(0.0))
		{
			return false;
		}
		roSOV = COleDateTime(date);
	}
	return true;
}

bool cned_dateedit::variant2buffer(const CSmartOleVariant & roSOV)
{
	ng_string oString;
	if(roSOV == GetNullDateSOV())
	{
		oString = _metrics().dateedit().get_null_text();
	}
	else
	{
		VERIFY(Variant2Display(roSOV,oString,(LPVOID)_metrics().dateedit().get_format()));
	}
	if(!oString.IsEmpty())
	{
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
	}
	return false;
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------

bool cned_dateedit::_act_paste_from_string(const ng_string & roString)
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

void cned_dateedit::_act_copy_to_string(ng_string & roString)
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

bool cned_dateedit::_act_cut_to_string(ng_string & roString)
{
	_act_copy_to_string(roString);
	_set_new_buffer_text(m_State,_metrics().dateedit().get_null_text());
	return true;
}

long cned_dateedit::_act_move(UINT nVKCode,bool bWithCtrl)
{
	switch(nVKCode)
	{
	case VK_LEFT:
		if(m_State.get_caret_pos() > 0)
		{
			//skip separator
			if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()-1) == _metrics().dateedit().get_separator())
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
		if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
		{
			//skip separator
			if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len() - 1)
			{
				if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+1) == _metrics().dateedit().get_separator())
				{
					return m_State.get_caret_pos() + 2;
				}
			}
			//nie separator
			return m_State.get_caret_pos() + 1;
		}
	break;
	case VK_HOME:
		if(!bWithCtrl)
		{
			return 0;
		}
	break;
	case VK_END:
		if(!bWithCtrl)
		{
			return _metrics().dateedit().get_format_len();
		}
	break;
	default:
		;
	}
	//no change
	return m_State.get_caret_pos();
}

bool cned_dateedit::_act_delete(bool bWithShift)
{
	if(__act_set_null(bWithShift))
	{
		return true;
	}
	if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
	{
		if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) != _metrics().dateedit().get_separator())
		{
			m_State.overtype_char('?');
			m_State.move_caret_by(+1,false);
		}
		if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
		{
			if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) == _metrics().dateedit().get_separator())
			{
				m_State.move_caret_by(+1,false);
			}
		}
		return true;
	}
	return false;
}

bool cned_dateedit::_act_backspace(bool bWithShift)
{
	if(__act_set_null(bWithShift))
	{
		return true;
	}

	if(m_State.get_caret_pos() > 0)
	{
		//skip separator
		if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()-1) == _metrics().dateedit().get_separator())
		{
			m_State.move_caret_by(-1,false);
		}
		if(m_State.get_caret_pos() > 0)
		{
			m_State.move_caret_by(-1,false);
			m_State.overtype_char('?');
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool cned_dateedit::_act_data(UINT nTranslatedChar)
{
	ASSERT(m_State.m_oBufferString.GetLength() == _metrics().dateedit().get_format_len());

	//jeœli nie jest na koñcu i jest to cyfra
	if(IsDigit(TCHAR(nTranslatedChar)))
	{
		if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
		{
			//skip separator
			if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) == _metrics().dateedit().get_separator())
			{
				m_State.move_caret_by(+1,false);
			}
			m_State.overtype_char(TCHAR(nTranslatedChar));
			//advance
			if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
			{
				m_State.move_caret_by(+1,false);
			}
			//skip separator
			if(m_State.get_caret_pos() < _metrics().dateedit().get_format_len())
			{
				if(m_State.m_oBufferString.operator [](m_State.get_caret_pos()+0) == _metrics().dateedit().get_separator())
				{
					m_State.move_caret_by(+1,false);
				}
			}
			ASSERT(m_State.get_caret_pos() <= _metrics().dateedit().get_format_len());
			return true;
		}
	}
	return false;
}

//--------------event handlers ---------------------------------------
void cned_dateedit::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	cned_edit__::on_event_keydown(roActionKBD,roResult);
	if(roActionKBD.get_keycode() == VK_APPS)
	{
		_fill_command_list(roResult);
	}
}

void cned_dateedit::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_edit__::on_event_mouse_endclick(roActionMouse,roResult);

	if(roActionMouse.is_RIGHT_click() && !get_prop_disabled())
	{
		_fill_command_list(roResult);
	}
}

void cned_dateedit::_fill_command_list(ned_action_result & roResult)
{
	ASSERT(roResult.get_info(0).PointsObject());
	SCP<CCommandList> poCmdListSP = _retrieve_command_list(roResult.get_info(0));
	ASSERT(poCmdListSP.PointsObject());
	
	SCP<CHyperLinkInfo> poTodayHLISP = NewSCP(new CHyperLinkInfo());
	poTodayHLISP->SetStrProp(GVAR_FUNCTIONHLI,"fcontrol");
	poTodayHLISP->SetNumProp(PROPC_IDENT,long(get_ident()));
	poTodayHLISP->SetNumProp(PROP_FCONTROL_OPERATION,FCONTROL_OPERATION_DATE_TODAY);
	//LANGUAGE:PL
	poCmdListSP->AddCommand(_T("Dzisiaj"),poTodayHLISP);

	SCP<CHyperLinkInfo> poCalendarHLISP = NewSCP(new CHyperLinkInfo());
	poCalendarHLISP->SetStrProp(GVAR_FUNCTIONHLI,"fcontrol");
	poCalendarHLISP->SetNumProp(PROPC_IDENT,long(get_ident()));
	poCalendarHLISP->SetNumProp(PROP_FCONTROL_OPERATION,FCONTROL_OPERATION_DATE_CALENDAR);
	//LANGUAGE:PL
	poCmdListSP->AddCommand(_T("Kalendarz"),poCalendarHLISP);
}


void cned_dateedit::_after_got_focus()
{
	if(m_State.m_oBufferString == _metrics().dateedit().get_null_text() || !get_prop_valid())
	{
		//when null or invalid date move caret to begin and select all
		m_State.move_caret_to(0,false);
		m_State.m_nCharSelLast = _metrics().dateedit().get_format_len();
		m_State.m_nCharSelFirst = m_State.get_caret_pos();
	}
	else
	{
		//move caret to day position and select day
		//LANGUAGE:PL - depends on format yyyy-mm-dd
		m_State.move_caret_to(_metrics().dateedit().get_format_len() - 2,false);
		m_State.m_nCharSelLast = _metrics().dateedit().get_format_len();
		m_State.m_nCharSelFirst = m_State.get_caret_pos();
	}
}

//LANGUAGE:PL
static LPCTSTR _g_cWeekDayName[] =
{
	_T("zapiliœmy ???"),	/*nie wiemy co za dzieñ tygodnia */
	_T("Niedziela"),
	_T("Poniedzia³ek"),
	_T("Wtorek"),
	_T("Œroda"),
	_T("Czwartek"),
	_T("Pi¹tek"),
	_T("Sobota"),
};

void cned_dateedit::get_prop_tooltip_text(ng_string & roText) const
{
	cned_edit__::get_prop_tooltip_text(roText);

	if(!roText.IsEmpty())
	{
		return;
	}
	
	CSmartOleVariant oDateSOV;
	if(!buffer2variant(oDateSOV))
	{
		return;
	}
	if(oDateSOV == GetNullDateSOV())
	{
		return;
	}

	int nDayOfWeek = COleDateTime(oDateSOV.GetDate()).GetDayOfWeek();

	roText = _g_cWeekDayName[ nDayOfWeek ];
}
