/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CUserDocument - programowalny dokument.
		zarz¹dza stronami i jest odpowiedzialny za jeden cykl dzia³añ u¿ytkownika (task)

		czêœæ AUTOMATION
*/

#include "stdafx.h"

/*



LPDISPATCH CUserDocument::CreateHLIOnHTTPStringAUTO(LPCTSTR lpHyperLinkString)
{
...
		CString oHTTPString(lpHyperLinkString);
		DWORD nBufferLength = (DWORD)oHTTPString.GetLength()*2;
		CString oCanonicString;
		BOOL bResult = ::InternetCanonicalizeUrl(oHTTPString,oCanonicString.GetBuffer(nBufferLength),
				&nBufferLength,ICU_DECODE | ICU_NO_ENCODE);
		oCanonicString.ReleaseBuffer();
		if(!bResult)
		{
			DWORD dwLastError=::GetLastError();
		}

*/

