/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
	
	ned_metrics

	klasa grupuj¹ca informacje o wymiarowaniu, opcjach wyœwietlania itd.
*/



#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ned_metrics _g_ned_metrics;

ned_metrics & ned::_metrics()
{
	return _g_ned_metrics;
}

//OS_API_CALL

ned_metrics::ned_metrics() :
	m_bWindowsLook(false),
	m_oVoidDragSize(::GetSystemMetrics(SM_CXDRAG),::GetSystemMetrics(SM_CYDRAG)),
	m_text(*this),
	m_button(*this),
	m_picture(*this),
	m_edit(*this),
	m_dateedit(*this),
	m_timeedit(*this),
	m_optionbtn(*this),
	m_tablecell(*this),
	m_win32_(*this),
	m_multitedit(*this),
	m_page(*this),
	m_bHighContrast(true)
{
}

ned_metrics::_edit::_edit(ned_metrics & rometrics) :
	m_rometrics(rometrics),
	m_clrInvalidData(255,64,64,0)
{
}

ened_border_style ned_metrics::_edit::get_border_type() const
{
	return NED_BORDER_STYLE_SOLID;
}

ned_metrics::_dateedit::_dateedit(ned_metrics & rometrics) :
	_edit(rometrics)
{
	//to_do: uzale¿niæ od ustawieñ systemu
	_tcscpy(m_cDateFormat,_T("yyyy-MM-dd"));
	m_nDateFormatLen = _tcslen(get_format());
	m_cDateSep = '-';

	ASSERT(m_nDateFormatLen > 0);
}

ned_metrics::_timeedit::_timeedit(ned_metrics & rometrics) :
	_edit(rometrics)
{
	m_nTimeFormatLen = 5;
	m_cTimeSep = ':';
}

ned_metrics::_text::_text(ned_metrics & rometrics):
	m_rometrics(rometrics)
{
}

ned_metrics::_button::_button(ned_metrics & rometrics):
	_text(rometrics)
{
}

ned_metrics::_picture::_picture(ned_metrics & rometrics) :
	m_rometrics(rometrics)
{
}

ned_metrics::_currency::_currency()
{
	//to_do: uzale¿niæ od ustawieñ systemu
	m_cDecimalSeparator  = ',';
	m_cThousandSeparator = ' ';
}

