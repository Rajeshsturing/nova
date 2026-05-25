/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	miscelanous utilities

*/
#include "stdafx.h"
#include <math.h>
#include "..\zlib\zlib.h"
#include "..\include\engineversion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

template <>
UINT AFXAPI HashKey(CICSBStrArgKey key)
{
	LPCWSTR pcStr = key;
	UINT nHash = 0;
	while (*pcStr)
	{
		nHash = (nHash<<5) + nHash + towlower(*pcStr++);
	};
	return nHash;
};

bool Variant2Display(const CSmartOleVariant & roSOV,CString & roString,
							void* lpFormat )
{
	switch(roSOV.Type())
	{
	case VT_BSTR:
		roString = roSOV.GetBStr();
		return true;
	case VT_CY:
	{
		//konwertujemy na postaæ komputerow¹ (decimal = dot)
		CString oTempString(Variant2String(roSOV));
		DWORD dwFlags = (lpFormat != NULL) ? 0 : LOCALE_NOUSEROVERRIDE;
		//konwertujemy na postaæ krajowa
		long nBytes = ::GetCurrencyFormat(GetWorkingLCID(),dwFlags,
			oTempString,(const CURRENCYFMT *)lpFormat,roString.GetBuffer(100),100);
		roString.ReleaseBuffer(nBytes-1);
#ifdef _DEBUG
		if(nBytes == 0)
		{
			DWORD dwLastError = ::GetLastError();
		}
#endif
		return (nBytes!=0);
	}
	case VT_DATE:
	{
		SYSTEMTIME oSYSTEMTIME;
		VERIFY(::VariantTimeToSystemTime(roSOV.GetDate(),&oSYSTEMTIME));
		DWORD dwFlags = (lpFormat != NULL) ? 0 : LOCALE_NOUSEROVERRIDE;

		long nBytes = ::GetDateFormat(GetWorkingLCID(),dwFlags,
			&oSYSTEMTIME,(LPCTSTR)lpFormat,roString.GetBuffer(100),100);
		roString.ReleaseBuffer(nBytes-1);
#ifdef _DEBUG
		if(nBytes == 0)
		{
			DWORD dwLastError = ::GetLastError();
		}
#endif
		return (nBytes!=0);
	}
	case VT_R8:
	{
		ASSERT(false);	//to_do: porz¹dek po Arturze
		CSmartOleVariant oSOV(roSOV);
		oSOV.ChangeType(VT_BSTR);
		CString oString = oSOV.GetBStr();
		bool bReturn = (0 != ::GetNumberFormat( LOCALE_USER_DEFAULT, 0, 
			oString,(const NUMBERFMT *)lpFormat, roString.GetBuffer(100), 100));
		roString.ReleaseBuffer();
		return bReturn;
	}
	case VT_I4:
	{
		roString = Long2String(roSOV.GetLong());
		return true;
	}
	case VT_I2:
	{
		roString = Long2String(roSOV.GetShort());
		return true;
	}
	default:
		ASSERT(false);
	}
	return false;
}

CString String2SQLString(const CString & roString)
{
	CString oResultString;
	LPTSTR pDest = oResultString.GetBuffer(roString.GetLength() * 3);
	LPCTSTR pSrc = (LPCTSTR)roString;
	while(*pSrc)
	{
		switch(*pSrc)
		{
		case '[':
			*pDest++ = '[';
			*pDest++ = '[';
			*pDest++ = ']';
		break;

		//zamykajacy jest poprawnie interpretowany
        //w samotnoœci a Ÿle po podmianie na []]
		//case ']':
		//	*pDest++ = '[';
		//	*pDest++ = ']';
		//	*pDest++ = ']';
		//break;

		case '_':
			*pDest++ = '[';
			*pDest++ = '_';
			*pDest++ = ']';
		break;
		case '%':
			*pDest++ = '[';
			*pDest++ = '%';
			*pDest++ = ']';
		break;
		case '\'':
			*pDest++ = '\'';
			*pDest++ = '\'';
		break;
		default:
			*pDest++ = *pSrc;
		}
		pSrc++;
	}
	*pDest = '\0';
	oResultString.ReleaseBuffer();
	return oResultString;
}

CString DoubleApostrophe(const CString & roString)
{
	CString oResultString;
	LPTSTR pDest = oResultString.GetBuffer(roString.GetLength() * 3);
	LPCTSTR pSrc = (LPCTSTR)roString;

	while(*pSrc)
	{
		switch(*pSrc)
		{
		case '\'':
			*pDest++ = '\'';
			*pDest++ = '\'';
		break;
		default:
			*pDest++ = *pSrc;
		}
		pSrc++;
	}
	*pDest = '\0';
	oResultString.ReleaseBuffer();

	return oResultString;
}


CString Variant2SQLString(const CSmartOleVariant & roSOV)
{
	switch(roSOV.Type())
	{
	case VT_BSTR:
		return DoubleApostrophe(Variant2String(roSOV));
	case VT_DATE:
		return COleDateTime(roSOV.GetDate()).Format(_T("{d '%Y/%m/%d'}"));
	default:
		return Variant2String(roSOV);
	}
}

CString EscapeString(const CString & roString)
{
	long nCount=0;
	LPCTSTR ptr = (LPCTSTR)roString;
	while(*ptr)
	{
		switch(*ptr++)
		{
		case '"':
		case '\\':
			nCount++;
		break;
		default:
			;
		}
	}
	CString oResultString;
	LPTSTR pStr = oResultString.GetBuffer(roString.GetLength() + nCount);
	ptr = (LPCTSTR) roString;
	while(*ptr)
	{
		switch(*ptr)
		{
		case '"':
		case '\\':
			*pStr++ = '\\';
		//nobreak
		default:
			*pStr++ = *ptr++;
		}
	}
	oResultString.ReleaseBuffer(roString.GetLength() + nCount);
	return oResultString;
}

/////////////////////////////////////////////////////////////////////
///				SplitString i koledzy
/////////////////////////////////////////////////////////////////////

static inline bool SplitString_IsSeparator(TCHAR c, TCHAR cSeparator)
{
	return (cSeparator == '\0') ? IsSpace(c) : c == cSeparator;
}

CStringArray & SplitString(const CString &roString,CStringArray &roArray, char cSeparator,bool bAddEmptyItems)
{
	for(int i=0; i < roString.GetLength(); i++)
	{
		CString item;
		// kopiuj do item ciag znakow nie bedacych separatorami
		while(i < roString.GetLength() &&
				!SplitString_IsSeparator(roString[i], cSeparator))
		{
			item += roString[i++];
		}
		if(!item.IsEmpty() || bAddEmptyItems)
		{
			roArray.Add(item);
		}
	}
	return roArray;
}

CStringArray & SplitStringBreakingSpaces(const CString &roString,CStringArray &roArray, bool bAddEmptyItems)
{
	for(int i=0; i < roString.GetLength(); i++)
	{
		CString item;
		// kopiuj do item ciag znakow nie bedacych separatorami
		while(i < roString.GetLength() && !IsBreakingSpace(roString[i]))
		{
			item += roString[i++];
		}
		if(!item.IsEmpty() || bAddEmptyItems)
		{
			roArray.Add(item);
		}
	}
	return roArray;
}

//--------------------------------------
//dzieli OleDateTime na kawa³ki
//--------------------------------------


#define MIN_DATE                (-657434L)  // about year 100
#define MAX_DATE                2958465L    // about year 9999

// Half a second, expressed in days
#define HALF_SECOND  (1.0/172800.0)

// One-based array of days in year at month start
static int rgMonthDays[13] =
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

static BOOL TmFromOleDate(DATE dtSrc, struct tm& tmDest)
{
	// The legal range does not actually span year 0 to 9999.
	if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
		return FALSE;

	long nDays;             // Number of days since Dec. 30, 1899
	long nDaysAbsolute;     // Number of days since 1/1/0
	long nSecsInDay;        // Time in seconds since midnight
	long nMinutesInDay;     // Minutes in day

	long n400Years;         // Number of 400 year increments since 1/1/0
	long n400Century;       // Century within 400 year block (0,1,2 or 3)
	long n4Years;           // Number of 4 year increments since 1/1/0
	long n4Day;             // Day within 4 year block
							//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
	long n4Yr;              // Year within 4 year block (0,1,2 or 3)
	BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

	double dblDate = dtSrc; // tempory serial date

	// If a valid date, then this conversion should not overflow
	nDays = (long)dblDate;

	// Round to the second
	dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

	nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

	dblDate = fabs(dblDate);
	nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

	// Calculate the day of week (sun=1, mon=2...)
	//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
	tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

	// Leap years every 4 yrs except centuries not multiples of 400.
	n400Years = (long)(nDaysAbsolute / 146097L);

	// Set nDaysAbsolute to day within 400-year block
	nDaysAbsolute %= 146097L;

	// -1 because first century has extra day
	n400Century = (long)((nDaysAbsolute - 1) / 36524L);

	// Non-leap century
	if (n400Century != 0)
	{
		// Set nDaysAbsolute to day within century
		nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

		// +1 because 1st 4 year increment has 1460 days
		n4Years = (long)((nDaysAbsolute + 1) / 1461L);

		if (n4Years != 0)
			n4Day = (long)((nDaysAbsolute + 1) % 1461L);
		else
		{
			bLeap4 = FALSE;
			n4Day = (long)nDaysAbsolute;
		}
	}
	else
	{
		// Leap century - not special case!
		n4Years = (long)(nDaysAbsolute / 1461L);
		n4Day = (long)(nDaysAbsolute % 1461L);
	}

	if (bLeap4)
	{
		// -1 because first year has 366 days
		n4Yr = (n4Day - 1) / 365;

		if (n4Yr != 0)
			n4Day = (n4Day - 1) % 365;
	}
	else
	{
		n4Yr = n4Day / 365;
		n4Day %= 365;
	}

	// n4Day is now 0-based day of year. Save 1-based day of year, year number
	tmDest.tm_yday = (int)n4Day + 1;
	tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

	// Handle leap year: before, on, and after Feb. 29.
	if (n4Yr == 0 && bLeap4)
	{
		// Leap Year
		if (n4Day == 59)
		{
			/* Feb. 29 */
			tmDest.tm_mon = 2;
			tmDest.tm_mday = 29;
			goto DoTime;
		}

		// Pretend it's not a leap year for month/day comp.
		if (n4Day >= 60)
			--n4Day;
	}

	// Make n4DaY a 1-based day of non-leap year and compute
	//  month/day for everything but Feb. 29.
	++n4Day;

	// Month number always >= n/32, so save some loop time */
	for (tmDest.tm_mon = (n4Day >> 5) + 1;
		n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

	tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
	if (nSecsInDay == 0)
		tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
	else
	{
		tmDest.tm_sec = (int)nSecsInDay % 60L;
		nMinutesInDay = nSecsInDay / 60L;
		tmDest.tm_min = (int)nMinutesInDay % 60;
		tmDest.tm_hour = (int)nMinutesInDay / 60;
	}

	return TRUE;
}

void OleDate2Parts(const COleDateTime & roOleDateTime,int & nYear,int & nMonth,int & nDay,
				   int & nHour,int & nMin,int & nSecond)
{
	if(roOleDateTime.GetStatus() != COleDateTime::valid)
	{
		ThrowNavoException(ERCO_ERROR_IN_OLEDATE2PARAM,IDPAGE_NOTAVAILABLE);
	}
	
	struct tm tmTemp;
	if(TmFromOleDate(roOleDateTime, tmTemp))
	{
		nYear	= tmTemp.tm_year;
		nMonth	= tmTemp.tm_mon;
		nDay	= tmTemp.tm_mday;
		nHour	= tmTemp.tm_hour;
		nMin	= tmTemp.tm_min; 
		nSecond	= tmTemp.tm_sec;
	}
}

void CParametersSplitter::Do(const TCHAR * pcSource)
{
	while (*pcSource)
	{
		while (*pcSource && (*pcSource == ' ' || *pcSource == '\t'))
		{
			pcSource++;
		};
		if (*pcSource != '-' && *pcSource != '/')
		{
			break;
		};
		pcSource++;
		CString oArgString;
		while (*pcSource && *pcSource != ' ' && *pcSource != '\t')
		{
			oArgString += ToLower(*pcSource++);
		};
		while (*pcSource && (*pcSource == ' ' || *pcSource == '\t'))
		{
			pcSource++;
		};
		CString oValueString;
		if (*pcSource != '-' && *pcSource != '/')
		{
			long lParenthesis = 0;
			bool bQuotationMarks = false;
			if (*pcSource == '(')
			{
				lParenthesis = 1;
				pcSource++;
			}
			else if (*pcSource == '\"')
			{
				bQuotationMarks = true;
				pcSource++;
			};
			bool bDone = false;
			while(*pcSource && !bDone)
			{
				switch(*pcSource)
				{
				case '\0':
					bDone = true;
					break;
				case ' ':
				case '\t':
					if (lParenthesis || bQuotationMarks)
					{
						goto other;
					}
					else
					{
						bDone = true;
					};
					break;
				case '\"':
					if (bQuotationMarks)
					{
						bDone = true;
						pcSource++;
						break;
					}
					else
					{
						goto other;
					};
				case '(':
					if (lParenthesis)
					{
						lParenthesis++;
					};
					goto other;
				case ')':
					if (lParenthesis == 1)
					{
						bDone = true;
						pcSource++;
						break;
					}
					else
					{
						goto other;
					};
					break;
				other:
				default:
					oValueString += *pcSource;
					break;
				};
				if (!bDone)
				{
					pcSource++;
				};
			};
		};
		m_oParametersMap[oArgString] = oValueString;
	};
};

static BOOL inline isident(char c)
{
	return isalnum(c) || c =='_' || c == '"' || c == '.' || c == '-' || c == '+' || c == '%' || c == '#';
}

void CTagSplitter :: Associate (CTagSplittingResult & oTagSplittingResult, 
	const TCHAR *pcFormat, ...)
{
	va_list list;
	va_start (list, pcFormat);
	CArray <CString, CString &> aNamesString, aValuesString;
	aNamesString.SetSize (MAX_ASSOCIATE_ARGUMENTS);
	aValuesString.SetSize (MAX_ASSOCIATE_ARGUMENTS);
	long lSize = 0, lParameterNumber = 0;
//	TRACE("CTagSplitter::Associate: begin.\n");
	while (lSize < MAX_ASSOCIATE_ARGUMENTS && NextItem(aNamesString [lSize], aValuesString [lSize]))
	{
		lSize++;
	};
	while (*pcFormat)
	{
		if (*pcFormat == '%')
		{
			pcFormat++;
			const char *pcName = va_arg (list, char *);
			ASSERT (pcName);
			long lIndex = 0;
			while (lIndex < lSize && aNamesString [lIndex] != pcName)
			{
				lIndex++;
			};
			switch (*pcFormat)
			{
			case 's':
			case 'S':
				{
					CString *poString = va_arg (list, CString *);
					ASSERT (poString);
					if (lIndex < lSize)
					{
						*poString = aValuesString [lIndex];
						oTagSplittingResult.ResultOk (lParameterNumber);
					}
					++lParameterNumber;
				};
				break;
			case 'l':
			case 'd':
			case 'L':
			case 'D':
				{
					long *plValue = va_arg (list, long *);
					ASSERT (plValue);
					if (lIndex < lSize)
					{
						TCHAR *pcEndPoint;
						*plValue = _tcstol(aValuesString [lIndex], &pcEndPoint, 10);
						if (!*pcEndPoint)
						{
							oTagSplittingResult.ResultOk (lParameterNumber);
						};
					};
					++lParameterNumber;
				};
				break;
			};
		};
		pcFormat++;
	};
	va_end (list);
};

bool CTagSplitter::NextItem(CString & roNameString,CString & roValueString, bool bNameUpperCase, bool bValUpperCase)
{
	//skip leading white space
	while(IsBreakingSpace(*m_pCurrPtr))
	{
		m_pCurrPtr++;
	}
	if(*m_pCurrPtr == '\0') 
	{
		return false;
	}
	//collect name
	LPCTSTR lpName = m_pCurrPtr;
	while(isident(*m_pCurrPtr))
	{
		m_pCurrPtr++;
	}
	if(*m_pCurrPtr == '\0')			//unexpected end
	{
		return false;
	}
	if(m_pCurrPtr == lpName)	//empty name
	{
		return false;
	}
	//trim quotation marks
	if(*lpName == '"' && *m_pCurrPtr == '"')
	{
		roNameString = CString(lpName+1,m_pCurrPtr-lpName-1);
	}
	else
	{
		roNameString = CString(lpName,m_pCurrPtr-lpName);
	}
	if(bNameUpperCase)
	{
		roNameString.MakeUpper();
	}
	//search eq sign
	while(*m_pCurrPtr != '=' && *m_pCurrPtr != '\0')
	{
		*m_pCurrPtr++;
	}
	if(*m_pCurrPtr == '\0')			//unexpected end
	{
		return false;
	}
	++m_pCurrPtr;
	//skip white space
	while(IsBreakingSpace(*m_pCurrPtr))
	{
		m_pCurrPtr++;
	}
	if(*m_pCurrPtr == '\0') 
	{
		return false;
	}
	//collect value
	LPCTSTR lpValue = m_pCurrPtr;
	TCHAR cQuotation = '\0';
	if(*m_pCurrPtr == '"' || *m_pCurrPtr == '\'')
	{
		cQuotation = *m_pCurrPtr;
		lpValue++;
		m_pCurrPtr++;
	}
	while(*m_pCurrPtr != '\0')
	{
		if(*m_pCurrPtr == cQuotation)
		{
			break;
		}
		else
		{
			if(cQuotation == '\0')
			{
				if(!isident(*m_pCurrPtr))
				{
					break;
				}
			}
		}
		m_pCurrPtr++;
	}

	roValueString = CString(lpValue,m_pCurrPtr-lpValue);

	if(*m_pCurrPtr == cQuotation && *m_pCurrPtr != '\0')
	{
		m_pCurrPtr++;
	}
	if(bValUpperCase)
	{
		roValueString.MakeUpper();
	}
	return true;
}

bool ParsePropertyName(const TCHAR *pcTagName, long & rlPropNumber, VARTYPE & rnPropType, const TCHAR * & rpcStart, const TCHAR * & rpcTerminator)
{
	while (*pcTagName && IsSpace(*pcTagName))
	{
		pcTagName++;
	};
	if (!*pcTagName)
	{
		return false;
	};

	rpcStart = pcTagName;
	if (ToLower(*pcTagName++) != 'v')
	{
		return false;
	};
	if (!*pcTagName)
	{
		return false;
	};
	if (IsDigit(*pcTagName))
	{
		rnPropType = VT_BSTR;
	}
	else
	{
		switch(ToLower(*pcTagName++))
		{
		case 's':
			rnPropType = VT_BSTR;
			break;
		case 'n':
			rnPropType = VT_I4;
			break;
		case 'd':
			rnPropType = VT_DATE;
			break;
		case 'c':
			rnPropType = VT_CY;
			break;
		default:
			return false;
		};
	};
	TCHAR aNumber[32];
	long lCounter = 0;
	while (lCounter < (sizeof(aNumber)/sizeof(aNumber[0])) && *pcTagName && IsDigit(*pcTagName))
	{
		aNumber[lCounter++] = *pcTagName++;
	};
	if (lCounter == 0)
	{
		return false;
	};
	aNumber[ lCounter ] = '\0';
	while (*pcTagName && IsSpace(*pcTagName))	
	{
		pcTagName++;
	};
	rlPropNumber = _ttol(aNumber);
	rpcTerminator = pcTagName;
	return true;
}

static const CSmartOleVariant __Null_Date_SOV(COleDateTime(DATE(1.0000)));
static const CSmartOleVariant __Null_Time_SOV(long(2500));	//nie ma godziny 25:00 

const CSmartOleVariant & GetNullDateSOV()
{
	return __Null_Date_SOV;
}

const CSmartOleVariant & GetNullTimeSOV()
{
	return __Null_Time_SOV;
}
//----------------------------- setup related helpers ----------------------

static LPCTSTR pcSetupAppName= _T("setup");

LPCTSTR GetSetupAppName()
{
	return pcSetupAppName;
}

bool IsSetupAppName(LPCTSTR lpAppName)
{
	CString oAppNameString(lpAppName);
	oAppNameString.MakeLower();
	return (oAppNameString.Left(_tcslen(GetSetupAppName())) == GetSetupAppName());
}

static bool _bNXMTransport = false;

bool IsNXMTransport()
{
	return _bNXMTransport;
}
void SetNXMTransport(bool bNXMTransport)
{
	_bNXMTransport = bNXMTransport;
}

static LPCTSTR pcNAVO2001RootRegKey = _T("SOFTWARE\\NAVO\\NAVO2002");
static LPCTSTR pcApplicationsRegKey = _T("SOFTWARE\\NAVO\\NAVO2002\\Applications");
static LPCTSTR pcSetupRegKey		= _T("SOFTWARE\\NAVO\\NAVO2002\\Setup");
static LPCTSTR pcDatabaseRegKey		= _T("SOFTWARE\\NAVO\\NAVO2002\\Database");
static LPCTSTR pcSupportRegKey		= _T("SOFTWARE\\NAVO\\NAVO2002\\Support");

LPCTSTR GetNAVO2001RootRegistryKeyName()
{
	return pcNAVO2001RootRegKey;
}

LPCTSTR GetApplicationsRegistryKeyName()
{
	return pcApplicationsRegKey;
}

LPCTSTR GetSetupRegistryKeyName()
{
	return pcSetupRegKey;
}

LPCTSTR GetDatabaseRegistryKeyName()
{
	return pcDatabaseRegKey;
}

LPCTSTR GetSupportRegistryKeyName()
{
	return pcSupportRegKey;
}

LPCTSTR GetNAVO2001EngineVersion()
{
	//UWAGA! Numer wersji musi zgadzaæ siê z zasobami (FILEVERSION i Fileversion)
	static LPCTSTR pcEngineVersionString = _T( ENGINESTRFILEVER );
	return pcEngineVersionString;
}

void StringToUTF8(LPCTSTR lpString,CString & roResultString)
{
#ifdef _UNICODE
	#pragma message( "Unicode todo" )
	ASSERT(false);
#else
	CArray<WCHAR,WCHAR> oWideArray;
	long nLen = strlen(lpString)+1;
	oWideArray.SetSize(nLen);
	VERIFY(::MultiByteToWideChar(CP_ACP, 0, lpString, nLen,oWideArray.GetData(), nLen) == nLen);
	long nReqLen =  ::WideCharToMultiByte(CP_UTF8,0,oWideArray.GetData(),nLen,NULL,0,NULL,NULL);
	VERIFY(::WideCharToMultiByte(CP_UTF8,0,oWideArray.GetData(),nLen,roResultString.GetBuffer(nReqLen),nReqLen,NULL,NULL)==nReqLen);
	roResultString.ReleaseBuffer();
#endif
}

///////////////
#ifndef _MINI_CORE_

void packbuffer(BYTE * pDestBuffer,unsigned long * pDestLen,const BYTE * pSrcBuffer,unsigned long nSrcLen)
{
	if(compress(pDestBuffer,pDestLen,pSrcBuffer,nSrcLen) != Z_OK)
	{
		ThrowNavoException(ERCO_COMPRESSION_FAILED,IDPAGE_NOTAVAILABLE);
	}
}

void unpackbuffer(BYTE * pDestBuffer,unsigned long * pDestLen,const BYTE * pSrcBuffer,unsigned long nSrcLen)
{
	if(uncompress(pDestBuffer,pDestLen,pSrcBuffer,nSrcLen) != Z_OK)
	{
		ThrowNavoException(ERCO_DECOMPRESSION_FAILED,IDPAGE_NOTAVAILABLE);
	}
}

#endif

bool IsSlowConnection_Registry()
{
	bool bSlowConnection = false;
	{
		CString oSlowConnectionString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,GetSupportRegistryKeyName(),
			"SlowConnection",oSlowConnectionString);
		bSlowConnection = (oSlowConnectionString == "Y");
	}
	return bSlowConnection;
}
