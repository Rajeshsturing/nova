/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Definition Manager.
	Script generators Part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "stdobjdef.h"
#include "DefinitionManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR ProcedureSuffixOnAction(stdobjactions Action);

CString SQLTypeName(long Type,dbenginetype eEngineType)
{
	switch(Type)
	{
	case SQLT_SMALL:	
		return _T("smallint");
	case SQLT_INT:		
	case SQLT_TIME:
		return (eEngineType==dbet_ms_jet35) ? _T("long") : _T("integer");
	case SQLT_DATE:		
		return _T("datetime");
	case SQLT_MONEY:	
		return (eEngineType==dbet_ms_jet35) ? _T("number") : _T("decimal(12,2)");
	case SQLT_QUANTITY:	
		return (eEngineType==dbet_ms_jet35) ? _T("number") : _T("decimal(14,4)");
	case SQLT_COEFF:	
		return (eEngineType==dbet_ms_jet35) ? _T("number") : _T("decimal(24,12)");
	case SQLT_IMAGE:
		return _T("image");
	case SQLT_CHAR0:	
		return _T("varchar");	//because of MS SQL server padding (see "Using char and varchar Data" article on MSDN)
	case SQLT_VARCHAR0:	
		return _T("varchar");
	default:
		{
			CString oString;
			if (Type > SQLT_CHAR0 && Type < SQLT_VARCHAR0)
			{
				oString.Format(_T("varchar(%u)"),CHARLEN(Type));	//because of MS SQL server padding (see "Using char and varchar Data" article on MSDN)
			}
			else if(Type > SQLT_VARCHAR0 && Type < SQLT_SMALL)
			{
				oString.Format(_T("varchar(%u)"),VARCHARLEN(Type));
			}
			else
			{
				ThrowNavoException1(ERCO_SOFD_INVALID_SQLTYPE,IDPAGE_NOTAVAILABLE,Type);
			}
			return oString;
		}
	}
}

