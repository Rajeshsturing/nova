/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_curredit		/ <currency>
		kontrolka edycji currency
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "curredit_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_curredit::cned_curredit(cned_element_manager * poManager,const ned_ident idThis) :
	cned_edit__(poManager,ned_currency,idThis),
	m_oValueCurrency(0,0),
	m_oNegativeTextColor(Red)
{
#ifdef _DEVELOPER_EDITION_
	_internal_set_prop_unit("BUG");
#endif
	_internal_set_prop_precision(2);
	
	//wzór na d³ugoœæ pocz¹tkow¹ bie¿e siê z konstrukcji
	//"1 234.00 PLN"
	// 5 - znaków przed precinkiem
	// 1 - przecinek
	// precision - dok³adnoœæ wyœwietlania
	// 1 - spacja 
	// unit - jednostka 

	set_prop_charwidth(5 + 1 + get_prop_precision() + 1 + m_oUnitString.GetLength());

	variant2buffer(m_oValueCurrency);
}

void cned_curredit::set_fixed_properties()
{
	//ned_to_do: przemyœleæ czy nie mo¿na tu umieœciæ pewnych rzeczy z ctor'a
	cned_edit__::set_fixed_properties();

	set_prop_alignment(eal_right);
}

//---------------------------------------------------------
// kbd actions
//---------------------------------------------------------

long cned_curredit::_act_move(UINT nVKCode,bool bWithCtrl)
{
	long nUnitPos =  __get_unit_pos();
	
	switch(nVKCode)
	{
	case VK_LEFT:
		if(bWithCtrl)
		{
			long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
			if(nDigitNr >= 0)
			{
				return 0;
			}
			else
			{
				return  __lookup_position(0);
			}
		}
		else
		{
			if(m_State.get_caret_pos() > 0)
			{
				long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
				long nNewPosition = __lookup_position(nDigitNr + 1);
				return nNewPosition;
			}
		}
	break;
	case VK_RIGHT:
		if(bWithCtrl)
		{
			long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
			if(nDigitNr <= 0)
			{
				return __get_unit_pos();
			}
			else
			{
				return  __lookup_position(0);
			}
		}
		else
		{
			if(m_State.get_caret_pos() < nUnitPos)
			{
				long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
				long nNewPosition = __lookup_position(nDigitNr - 1);
				return nNewPosition;
			}
		}
	break;
	case VK_HOME:
		return 0;
	case VK_END:
		return __get_unit_pos();
	default:
		;
	}
	//no change
	return m_State.get_caret_pos();
}

bool cned_curredit::_act_delete(bool /*bWithShift*/)
{
	if(__delete_selection())
	{
		return true;
	}

	long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
	if(nDigitNr < 0 && nDigitNr >= -m_nActualPrecision)
	{
		__delete_in_fractional_part(nDigitNr);
		return true;
	}
	if(nDigitNr > 0)
	{
		__delete_in_whole_part(nDigitNr-1);
	}
	long nMaxDigit = __get_digit_nr(0);
	m_State.move_caret_to(__lookup_position(min(nMaxDigit,nDigitNr-1)),false);
	return true;
}

bool cned_curredit::_act_backspace(bool /*bWithShift*/)
{
	if(__delete_selection())
	{
		return true;
	}

	long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
	if(nDigitNr < -1 && nDigitNr >= -m_nActualPrecision-1)
	{
		__delete_in_fractional_part(nDigitNr+1);
		m_State.move_caret_to(__lookup_position(nDigitNr+1),false);
		return true;
	}
	if(nDigitNr == -1)
	{
		m_State.move_caret_to(__lookup_position(0),false);
		return true;
	}
	if(nDigitNr >= 0)
	{
		__delete_in_whole_part(nDigitNr);
		long nMaxDigit = __get_digit_nr(0);
		m_State.move_caret_to(__lookup_position(min(nMaxDigit,nDigitNr)),false);
		return true;
	}
	//ned_to_do:
	return false;
}

bool cned_curredit::_act_data(UINT nTranslatedChar)
{
	switch(char(nTranslatedChar))
	{
	case '-':
	{
		long nDigitNr = __get_digit_nr(m_State.get_caret_pos());
		m_oValueCurrency = -m_oValueCurrency;
		__compose_string(m_State.m_oBufferString);
		m_State.move_caret_to(__lookup_position(nDigitNr),false);
		return true;
	}
	break;
	case '0':	case '1':	case '2':	case '3':	case '4':	case '5':	case '6':	case '7':	case '8':	case '9':
	{
		__delete_selection();
		long nDigitNr = __get_digit_nr(m_State.get_caret_pos());

		if(nDigitNr < 0 && nDigitNr >= -m_nActualPrecision)
		{
			__insert_in_fractional_part(long(char(nTranslatedChar)-'0'),nDigitNr);
			m_State.move_caret_to(__lookup_position(nDigitNr-1),false);
			return true;
		}
		if(nDigitNr >= 0)
		{
			__insert_in_whole_part(long(char(nTranslatedChar)-'0'),nDigitNr);
			m_State.move_caret_to(__lookup_position(nDigitNr),false);
			return true;
		}
	}
	break;
	default:
		if(char(nTranslatedChar) == '.' || char(nTranslatedChar) == _metrics().currency().get_decimal_separator())
		{
			__delete_selection();
			m_State.move_caret_to(__lookup_position(-1),false);
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------
// helpers
//--------------------------------------------------------------------

//-----------------------
//	__get_digit_nr zwraca nastêpuj¹ce wartoœci:
//
//	|9 |9 |9 |9 |9 |9 |. |9 |9 |9 |9 |
//    6  5  4  3  2  1  0 -1 -2 -3 -4 -5
//-----------------------


inline long cned_curredit::__get_digit_nr(long nBufferInx) const
{
	ASSERT(nBufferInx <= __get_unit_pos());

	long nDotPos =   __get_dot_pos();
	if(nBufferInx > nDotPos)
	{
		return nDotPos - nBufferInx;
	}
	long nDigitNr = 0;
	for(long iter = nBufferInx; iter < nDotPos; iter++)
	{
		if(IsDigit(m_State.m_oBufferString.operator [](iter+0)))
		{
			nDigitNr++;
		}
	}
	return nDigitNr;
}

inline long cned_curredit::__lookup_position(long nDigitNr) const
{
	for(long iter = 0; iter <= m_State.m_oBufferString.GetLength(); iter++)
	{
		if(__get_digit_nr(iter) == nDigitNr)
		{
			return iter;
		}
	}
	ASSERT(false);
	return -1;
}

bool cned_curredit::__delete_selection()
{
	if(m_State.is_selection())
	{
		long nFirstDigit = __get_digit_nr(m_State.m_nCharSelFirst);
		long nLastDigit = __get_digit_nr(m_State.m_nCharSelLast);
		long nCount = nFirstDigit - nLastDigit;
		ASSERT(nCount >= 0);
		if(nLastDigit >= 0)
		{
			while(nCount --)
			{
				__delete_in_whole_part(nLastDigit);
			}
			m_State.move_caret_to(__lookup_position(nLastDigit),false);
		}
		return true;
	}
	return false;
}

void cned_curredit::__compose_string(ng_string & roString)
{
	bool bPositive = (m_oValueCurrency.m_cur.int64 >= 0);
	long nFractionalPart = labs(long(m_oValueCurrency.m_cur.int64 % 10000));
	__int64 nWholePart = __int64(m_oValueCurrency.m_cur.int64 / 10000);
	
	if(nWholePart < 0)
	{
		nWholePart = -nWholePart;
	}

	ASSERT(m_oValueCurrency.m_cur.int64 == 
		(bPositive ? +1 : -1) * (__int64(nWholePart)*10000 + nFractionalPart));
	ASSERT(nWholePart >= 0);
	ASSERT(nFractionalPart >= 0);

	TCHAR cFractionalPart[33];
	TCHAR cWholePart[33];
	
	_ltot(10000+nFractionalPart,cFractionalPart,10);
	_i64tot(nWholePart,cWholePart,10);
	cFractionalPart[0] = _metrics().currency().get_decimal_separator();  //wstaw separator 

	roString.Empty();
	//najpierw znak
	if(m_oValueCurrency.m_cur.Hi < 0)
	{
		roString = "-";
	}
	
	//wstaw separatory tysiêcy	(jesli jest)
	if(_metrics().currency().get_thousand_separator() != '\0')
	{
		long nLen = _tcslen(cWholePart);
		long nPos = nLen;
		long nOffset = (nLen-1) / 3;
		while(nPos > 0)
		{
			cWholePart[ nPos + nOffset ] = cWholePart[ nPos ];
			if((nLen - nPos) % 3 == 0 && nLen != nPos)
			{
				nOffset--;
				cWholePart[ nPos + nOffset ] = _metrics().currency().get_thousand_separator();
			}
			nPos--;
		}
	}
	//przeanalizuj precyzjê i obetnij nieznacz¹ce zera
	ASSERT(_tcslen(cFractionalPart) == 5);	//,0000 .... ,9999
	long nPos = 4;
	while(nPos > m_nDeclPrecision)
	{
		if(cFractionalPart[nPos] != '0')
		{
			break;
		}
		cFractionalPart[nPos] = '\0';
		nPos--;
	}
	m_nActualPrecision = nPos;

	//po³¹cz ca³oœæ
	roString += cWholePart;
	if(m_nActualPrecision > 0)
	{
		roString += cFractionalPart;
	}
	
	if(!m_oUnitString.IsEmpty())
	{
		roString += ' ' + m_oUnitString;
	}
}

inline __int64 power10(long nPower)
{
	ASSERT(nPower >= 0);
	__int64 iresult = 1;
	while(nPower--)
	{
		iresult *= __int64(10);
	}
	return iresult;
}

void cned_curredit::__delete_in_whole_part(long nDigitNr)
{
	ASSERT(nDigitNr >= 0);
	bool bPositive = (m_oValueCurrency.m_cur.int64 >= 0);
	long nFractionalPart = labs(long(m_oValueCurrency.m_cur.int64 % 10000));
	__int64 nWholePart = __int64(m_oValueCurrency.m_cur.int64 / 10000);
	if(nWholePart < 0)
	{
		nWholePart = -nWholePart;
	}
	__int64 nPower10 = power10(nDigitNr);
	nWholePart = __int64(nWholePart / nPower10 / 10) * nPower10 + (nWholePart % nPower10);
	m_oValueCurrency.m_cur.int64 = (bPositive ? +1 : -1) * (__int64(nWholePart) * 10000 + nFractionalPart);

	__compose_string(m_State.m_oBufferString);
}

void cned_curredit::__delete_in_fractional_part(long nDigitNr)
{
	ASSERT(nDigitNr < 0 && nDigitNr >= -m_nActualPrecision);

	long nPower10 = long(power10(5+nDigitNr));
	bool bPositive = (m_oValueCurrency.m_cur.int64 >= 0);
	long nFractionalPart = labs(long(m_oValueCurrency.m_cur.int64 % 10000));
	__int64 nWholePart = __int64(m_oValueCurrency.m_cur.int64 / 10000);
	if(nWholePart < 0)
	{
		nWholePart = -nWholePart;
	}
	nFractionalPart = long(nFractionalPart / nPower10) * nPower10 + (nFractionalPart % (nPower10 / 10)) * 10;
	m_oValueCurrency.m_cur.int64 = (bPositive ? +1 : -1) * (__int64(nWholePart)* 10000 + nFractionalPart);

	__compose_string(m_State.m_oBufferString);
}

void cned_curredit::__insert_in_fractional_part(long nValue,long nDigitNr)
{
	ASSERT(nDigitNr < 0 && nDigitNr >= -m_nActualPrecision);
	ASSERT(nValue >= 0 && nValue <= 9);

	long nPower10 = long(power10(4+nDigitNr));
	bool bPositive = (m_oValueCurrency.m_cur.int64 >= 0);
	long nFractionalPart = labs(long(m_oValueCurrency.m_cur.int64 % 10000));
	__int64 nWholePart = __int64(m_oValueCurrency.m_cur.int64 / 10000);
	if(nWholePart < 0)
	{
		nWholePart = -nWholePart;
	}
	nFractionalPart = long(nFractionalPart / nPower10 / 10) * nPower10 * 10 + 
		nValue * nPower10 + (nFractionalPart % nPower10);
	m_oValueCurrency.m_cur.int64 = (bPositive ? +1 : -1) * (__int64(nWholePart)* 10000 + nFractionalPart);

	__compose_string(m_State.m_oBufferString);
}

void cned_curredit::__insert_in_whole_part(long nValue,long nDigitNr)
{
	ASSERT(nValue >= 0 && nValue <= 9);
	ASSERT(nDigitNr >= 0);
	bool bPositive = (m_oValueCurrency.m_cur.int64 >= 0);
	long nFractionalPart = labs(long(m_oValueCurrency.m_cur.int64 % 10000));
	__int64 nWholePart = __int64(m_oValueCurrency.m_cur.int64 / 10000);
	if(nWholePart < 0)
	{
		nWholePart = -nWholePart;
	}
	if(nWholePart < __int64(10000000000000))
	{
		__int64 nPower10 = power10(nDigitNr);
		nWholePart = __int64(nWholePart / nPower10) * nPower10 * 10 + nValue * nPower10 + (nWholePart % nPower10);
		m_oValueCurrency.m_cur.int64 = (bPositive ? +1 : -1) * (__int64(nWholePart) * 10000 + nFractionalPart);
	
		__compose_string(m_State.m_oBufferString);
	}
}

void cned_curredit::_after_got_focus()
{
	//move caret to dot position and select whole part
	m_State.move_caret_to(__get_dot_pos(),false);
	m_State.m_nCharSelLast = __get_dot_pos();
	m_State.m_nCharSelFirst = 0;
}

