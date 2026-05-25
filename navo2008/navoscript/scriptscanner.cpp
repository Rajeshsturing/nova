/*
	NAVO Enterprise (2001)
	
	Script Code Scanner

	scans script for function (sub) names and marks which exists
*/

#include "stdafx.h"
#include "scriptscanner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// recognizes following syntax
/// <white>sub<white>name<etc>,  or
/// <white>function<white>name<etc>,  or


const long nTokenSubLen			= 3;
const long nTokenFunctionLen	= 8;
LPCTSTR lpTokenSub				= _T("sub");
LPCTSTR lpTokenFunction			= _T("function");

enum WhatFound
{
	notfound,
	subfound,
	functfound
};

void ScanScriptForProcedures(LPCTSTR lpScriptCode, CFunctionInfoArray & roFunctionInfoArray,
							 LPCTSTR lpRequiredPrefix /*= NULL*/)
{
	ASSERT(lpScriptCode);
	LPCTSTR lpPtr = lpScriptCode;
	while(*lpPtr)
	{
		LPCTSTR lpEndOfLine = _tcschr(lpPtr,'\n');
		if(lpEndOfLine == NULL)
		{
			ASSERT(_tcslen(lpPtr) > 0);
			lpEndOfLine = lpPtr + _tcslen(lpPtr) - 1;
		}
		//skip leading whitespace
		while(lpPtr < lpEndOfLine && IsSpace(*lpPtr))
		{
			lpPtr++;
		}
		WhatFound eWF = notfound;
		if(_tcsnicmp(lpPtr,lpTokenSub,nTokenSubLen) == 0)
		{
			eWF = subfound;
			lpPtr += nTokenSubLen;
		}
		else if(_tcsnicmp(lpPtr,lpTokenFunction,nTokenFunctionLen) == 0)
		{
			eWF = functfound;
			lpPtr += nTokenFunctionLen;
		}
		if(eWF != notfound)	// sub or function - search for name
		{
			//must be at least one whitespace char
			if(IsSpace(*lpPtr))
			{
				//skip space before name
				while(lpPtr < lpEndOfLine && IsSpace(*lpPtr))
				{
					lpPtr++;
				}
				LPCTSTR lpBegin = lpPtr;
				while(lpPtr < lpEndOfLine && IsAlphaNum(*lpPtr))
				{
					lpPtr++;
				}
				CString oFunctionNameString(lpBegin,lpPtr-lpBegin);
				bool bAdd = true;
				if(lpRequiredPrefix != NULL)
				{
					if(oFunctionNameString.Find(lpRequiredPrefix) != 0)
					{
						bAdd = false;
					}
				}
				if(bAdd)
				{
					roFunctionInfoArray.Add(CFunctionInfo(oFunctionNameString,eWF==functfound));
				}
			}
		}
		lpPtr = lpEndOfLine + 1;
	};
	
//	TRACE1("Found %d functions\n",roFunctionInfoArray.GetSize());
}
