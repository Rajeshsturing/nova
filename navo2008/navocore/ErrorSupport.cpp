// ===========================================================================
//
// NAVO Enterprise 2001
//
// Error support
//
// error support utils
//
// ===========================================================================
#include "stdafx.h"
#include <afxole.h>
#include "..\navopx\navopx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOCORE_Instance;

__declspec(noreturn) void CSmartOleVariant::ThrowNoMemory()
{
	ThrowNavoException(ERCO_SOV_NOMEMORY, IDPAGE_NOTAVAILABLE);
}

__declspec(noreturn) void CSmartOleVariant::ThrowUnexpectedVariantType(VARTYPE nNewType) const
{
	VARIANT var;
	::VariantInit(&var);
	VERIFY(S_OK == ::VariantCopy(&var,(VARIANT*)this));

	try
	{
		VERIFY(S_OK == ::VariantChangeType(&var,&var,0,VT_BSTR));
	}
	catch(...)
	{
	};

	USES_CONVERSION;
	LPTSTR ptr2ansi = ((var.vt == VT_BSTR) ? OLE2T(var.bstrVal) : "");
	ThrowNavoException3(ERCO_SOV_BADTYPE, IDPAGE_NOTAVAILABLE, ptr2ansi, (long)Type(), (long)nNewType);
}

__declspec(noreturn) void CSmartOleVariant::ThrowCannotChangeType(VARTYPE nNewType)
{
	VARIANT var;
	VariantInit(&var);
	VERIFY(S_OK == ::VariantCopy(&var,(VARIANT*)this));

	try
	{
		VERIFY(S_OK == ::VariantChangeType(&var,&var,0,VT_BSTR));
	}
	catch(...)
	{
	};
	USES_CONVERSION;
	LPTSTR ptr2ansi = ((var.vt == VT_BSTR) ? OLE2T(var.bstrVal) : "");
	ThrowNavoException3(ERCO_SOV_CANNOTCHANGETYPE, IDPAGE_NOTAVAILABLE, ptr2ansi, (long)var.vt, (long)nNewType);
}

__declspec(noreturn) void ThrowFromErrorInfo(HRESULT hResult, IErrorInfo * iErrorInfo)
{
	try
	{
		_bstr_t oDescriptionBStr, oSourceBStr;
		BSTR bStr;
		if (iErrorInfo)
		{
			VERIFY(iErrorInfo->GetDescription(&bStr) == S_OK);
			oDescriptionBStr.Assign(bStr);
			VERIFY(iErrorInfo->GetSource(&bStr) == S_OK);
			oSourceBStr.Assign(bStr);
		};

		USES_CONVERSION;
		LPTSTR pansiSource = OLE2T(oSourceBStr);
		LPTSTR pansiDescription = OLE2T(oDescriptionBStr);
		ThrowNavoException3(ERCO_GENERICCOMERROR, IDPAGE_NOTAVAILABLE, pansiSource, hResult, pansiDescription);
	}
	catch(...)
	{
		if (iErrorInfo)
		{
			iErrorInfo->Release();
		};
		throw;
	};
};

static void _FormatErrorCodeMsg(CString & roMsgString,errorcode lErrorCode, va_list argList)
{
	CString oFormatString;
	if (lErrorCode == ERCO_TODO)
	{
		oFormatString = "%s";
	}
	else
	{
		CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
		VERIFY(oFormatString.LoadString(lErrorCode) != 0);
	}
	roMsgString.FormatV(oFormatString, argList);
}

void NavoFormatErrorMsg(CString & roMsgString,errorcode lErrorCode,...)
{
	va_list argList;
	va_start(argList, lErrorCode);
	_FormatErrorCodeMsg(roMsgString,lErrorCode,argList);
	va_end(argList);
}

void ThrowNavoExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	errorcode lErrorCode,
	long lHelpPageId,
	...)
{
	CString oFormattedString;
	va_list argList;
	va_start(argList, lHelpPageId);
	_FormatErrorCodeMsg(oFormattedString,lErrorCode,argList);
	va_end(argList);

	CString oInfoString;
	oInfoString.Format(_T("%s (%s:%d)"), (LPCTSTR)oFormattedString, pcFileName, lLine);
#ifdef _DEBUG
	int iResult = ::MessageBox(::GetActiveWindow(), 
		_T("Czy rzuciæ wyjatek ?\nTAK-rzuæ\nNIE-ignoruj\nANULUJ-debugger\n") + oInfoString, 
		_T(""), MB_ICONQUESTION | MB_YESNOCANCEL);
	switch (iResult)
	{
	case IDYES:
#endif
		throw CNavoException(CNavoErrorInfo(lErrorCode, lHelpPageId, oInfoString));
#ifdef _DEBUG
		break;
	case IDNO:
		break;
	case IDCANCEL:
		::DebugBreak();
		break;
	};
#endif
};

void ContinueThrowNavoExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	CNavoException & roException,
	errorcode lErrorCode,
	long idHelp,
	...)
{
	CString oFormattedString;
	va_list argList;
	va_start(argList, idHelp);
	_FormatErrorCodeMsg(oFormattedString,lErrorCode,argList);
	va_end(argList);

	CString oInfoString;
	oInfoString.Format(_T("%s (%s:%d)"), (LPCTSTR)oFormattedString, pcFileName, lLine);

#ifdef _DEBUG
	int iResult = ::MessageBox(::GetActiveWindow(), 
		_T("Czy rzuciæ wyj¹tek ?\nTAK-rzuæ\nNIE-ignoruj\nANULUJ-debugger\n") + oInfoString, 
		_T(""), MB_ICONQUESTION | MB_YESNOCANCEL);
	switch (iResult)
	{
	case IDYES:
#endif
		roException += CNavoErrorInfo(lErrorCode, idHelp, oInfoString);
		throw roException;
#ifdef _DEBUG
		break;
	case IDNO:
		break;
	case IDCANCEL:
		::DebugBreak();
		break;
	};
#endif
}

void ThrowNavoAutomationExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	errorcode lErrorCode,
	long lHelpPageId,
	...)
{
	CString oFormattedString;
	va_list argList;
	va_start(argList, lHelpPageId);
	_FormatErrorCodeMsg(oFormattedString,lErrorCode,argList);
	va_end(argList);

	CString oInfoString;
	oInfoString.Format(_T("%s (%s:%d)"), (LPCTSTR)oFormattedString, pcFileName, lLine);

#ifdef _DEBUG
	int iResult = ::MessageBox(0, _T("Jest dobrze! Czy rzucic wyjatek automation ?\nTAK-rzuc\nNIE-ignoruj blad\nANULUJ-debugger") + oInfoString, 
		_T(""), MB_ICONQUESTION | MB_YESNOCANCEL);
	switch (iResult)
	{
	case IDYES:
#endif
		{
			AfxThrowOleDispatchException((WORD)lErrorCode, oInfoString, lHelpPageId);
		};
#ifdef _DEBUG
		break;
	case IDNO:
		break;
	case IDCANCEL:
		::DebugBreak();
		break;
	};
#endif
};

void ThrowNavoAutomationExceptionFromInfoInternal(
	LPCTSTR pcFileName,
	long lLine,
	const CNavoException & roNavoException)
{
	ThrowNavoAutomationExceptionInternal(pcFileName,lLine,
		ERCO_INSIDE_AUTOMATION_FAULT,IDPAGE_NOTAVAILABLE,
		roNavoException.BuildCompleteErrorString());
};

CString GetLastError_To_String(DWORD dwErrorCode)
{
	CString oStr;
	LPTSTR pcText;
	if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
		dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pcText, 0, NULL) == 0 || pcText == NULL)
	{
		ThrowNavoException1(ERCO_INTERNAL_UNKNOWNERROR, IDPAGE_NOTAVAILABLE, dwErrorCode);
	}
	else
	{
		try
		{
			oStr = pcText;
			oStr.Remove('\n');
			oStr.Remove('\r');
			LocalFree(pcText);
		}
		catch(...)
		{
			LocalFree(pcText);
			throw;
		};
	};
	return oStr;
};

CString  SCODE_To_String(SCODE sc)
{
#ifndef _DEBUG
	return Long2String(sc);
#else
	return CString(AfxGetFullScodeString(sc));
#endif
}

#ifndef _MINI_CORE_

bool ErrorInfoFromInterface(IUnknown * pUnknown, CNavoErrorInfo & roNavoErrorInfo)
{
	SCP <INavoErrorInfo> poErrorInfoSP;
	if (!poErrorInfoSP.SafeQueryInterface(pUnknown))
	{
		return false;
	};
	CRPCLoader_via_Archive<CNavoErrorInfo> oRPCLoader(roNavoErrorInfo);
	HRESULT hResult = poErrorInfoSP->RetrieveError(oRPCLoader.GetLength(), oRPCLoader.GetData());
	switch(hResult)
	{
	case S_OK:
		oRPCLoader.Load();
		return true;
	case S_FALSE:
		return false;
	};
	ThrowNavoException(ERCO_ERRORINFO_RETRIEVE_ERROR_FAILED, IDPAGE_NOTAVAILABLE);
}

#endif

CString CNavoErrorInfo::BuildErrorString() const
{
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	CString oPartialString;
	oPartialString.Format(IDS_ERROR_INFO_TEMPL,(long)GetErroCode(),GetErrorString());
	return oPartialString;
}

CString CNavoException::BuildCompleteErrorString() const
{
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	CString oCompleteString;
	for(long iter = 0; iter <= m_oNEIArray.GetUpperBound(); iter++)
	{
		oCompleteString += Long2String(iter+1) + ". " + m_oNEIArray[iter].BuildErrorString() + "\n";
	}
	return oCompleteString;
}

void _fill_excepinfo(EXCEPINFO * pExcepInfo,const CNavoException & roNavoException)
{
	if(pExcepInfo == NULL)
	{
		return;
	}

	CString oDescriptionString;
	NavoFormatErrorMsg(oDescriptionString,ERCO_INSIDE_AUTOMATION_FAULT,
		roNavoException.BuildCompleteErrorString());
	
	pExcepInfo->wCode = (WORD) ERCO_INSIDE_AUTOMATION_FAULT;
	pExcepInfo->bstrDescription = oDescriptionString.AllocSysString();
	pExcepInfo->scode = DISP_E_EXCEPTION;
}
