/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Variant <--> binary helpers
*/

#include "stdafx.h"
#include <afxconv.h>

//helper functions
static long _trim_right_spaces(LPTSTR lpsz)
{
	LPTSTR lpsz0 = lpsz;
	LPTSTR lpszLast = NULL;
	while (*lpsz != '\0')
	{
		if (IsSpace((unsigned char)*lpsz))
		{
			if (lpszLast == NULL)
			{
				lpszLast = lpsz;
			}
		}
		else
		{
			lpszLast = NULL;
		}
		lpsz = _tcsinc(lpsz);
	}

	if (lpszLast != NULL)
	{
		// truncate at trailing space start
		*lpszLast = '\0';
		return lpszLast - lpsz0;
	}
	else
		return lpsz - lpsz0;
}

long Variant2BinaryHelper(long nSQLType,const CSmartOleVariant & var,PBYTE pData)
{
	switch(nSQLType)
	{
	case SQLT_SMALL:
		if(pData)
		{
			*(short*)pData = var.GetShort();
		}
		return sizeof(short);
	case SQLT_INT:
	case SQLT_TIME:
		if(pData)
		{
			*(long int*)pData = var.GetLong();
		}
		return sizeof(long);
	case SQLT_DATE:
		if(pData)
		{
			*(DATE*)pData = var.GetDate();
		}
		return sizeof(DATE);
	case SQLT_MONEY:
	case SQLT_QUANTITY:
		if(pData)
		{
			if(var.Type() != VT_CY)
			{
				ASSERT(var.Type() == VT_DECIMAL);
				CSmartOleVariant oSOV(var);
				oSOV.ChangeType(VT_CY);
				*(CY *)pData = oSOV.GetCurrency();
			}
			else
			{
				*(CY *)pData = var.GetCurrency();
			}
		}
		return sizeof(CY);
	case SQLT_IMAGE:
	{
		long nSize;
		ASSERT(var.Type() == (VT_UI1 | VT_ARRAY));
#ifdef _DEBUG
		::SafeArrayGetLBound(var.GetVariantRef().parray, 1, &nSize);
		ASSERT(nSize == 0);		//lower bound should be 0
#endif
		::SafeArrayGetUBound(var.GetVariantRef().parray, 1, &nSize);
		if(pData)
		{
			memcpy(pData,&nSize,sizeof(long));
			pData += sizeof(long);
			void * pArrayData;
			::SafeArrayAccessData(var.GetVariantRef().parray,&pArrayData);
			memcpy(pData,pArrayData,nSize);
			::SafeArrayUnaccessData(var.GetVariantRef().parray);
		}
		return nSize + sizeof(long);
	}
	break;
	default:
		if(nSQLType >= SQLT_CHAR0 && nSQLType < SQLT_SMALL)
		{
			ASSERT(var.Type() == VT_BSTR);
#ifdef _UNICODE
			#pragma message( "Unicode todo" )
			ASSERT(false);
			return -1;
#else
			USES_CONVERSION;
			LPTSTR ptr2ansi = OLE2T(var.GetBStr());
			ASSERT(ptr2ansi);
			long nLength = 1+_trim_right_spaces(ptr2ansi);
			if(pData)
			{
				memcpy(pData,ptr2ansi,nLength);
			}
			return nLength;
#endif
		}
		ASSERT(false);
		return -1;
	}	
}


long Binary2VariantHelper(long nSQLType,CSmartOleVariant & var,PBYTE pData)
{
	ASSERT(pData);

	if(var.Type() != VT_EMPTY) 		//refresh variant
	{
		var.Clear();
	}

	switch(nSQLType)
	{
	case SQLT_SMALL:
		var = *(short*) pData;
		return sizeof(short);
	case SQLT_INT:
	case SQLT_TIME:
		var = *(long*) pData;
		return sizeof(long);
	case SQLT_DATE:
		var = COleDateTime(*(DATE*) pData);
		return sizeof(DATE);
	case SQLT_MONEY:
	case SQLT_QUANTITY:
		var = *(CY *)pData;
		return sizeof(CY);
	case SQLT_IMAGE:
	{
		long nSize = *(long*) pData;
		pData += sizeof(long);
		var.CreateOneDimArray(VT_UI1,nSize);
		void * pArrayData;
		::SafeArrayAccessData(var.GetVariantRef().parray,&pArrayData);
		memcpy(pArrayData,pData,nSize);
		::SafeArrayUnaccessData(var.GetVariantRef().parray);
		return nSize + sizeof(long);
	}
	default:
		if(nSQLType >= SQLT_CHAR0 && nSQLType < SQLT_SMALL)
		{
			var = (LPCTSTR)pData;
			ASSERT(::SysStringLen(const_cast <LPWSTR> (var.GetBStr())) == _tcslen((LPCTSTR)pData) );
			return 1 + _tcslen((LPCTSTR)pData);
		}
		ASSERT(false);
		return -1;
	}	
}
