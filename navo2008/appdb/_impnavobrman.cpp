// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "_impnavobrman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IBRSet properties

long IBRSet::GetType()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void IBRSet::SetType(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

CString IBRSet::GetMask()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetMask(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

BOOL IBRSet::GetRecurse()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void IBRSet::SetRecurse(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

CString IBRSet::GetServer()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetServer(LPCTSTR propVal)
{
	SetProperty(0x4, VT_BSTR, propVal);
}

CString IBRSet::GetDatabase()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetDatabase(LPCTSTR propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}

CString IBRSet::GetUser()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetUser(LPCTSTR propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}

CString IBRSet::GetPassword()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetPassword(LPCTSTR propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}

CString IBRSet::GetRemoteserver()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetRemoteserver(LPCTSTR propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}

BOOL IBRSet::GetRelative()
{
	BOOL result;
	GetProperty(0x9, VT_BOOL, (void*)&result);
	return result;
}

void IBRSet::SetRelative(BOOL propVal)
{
	SetProperty(0x9, VT_BOOL, propVal);
}

CString IBRSet::GetName()
{
	CString result;
	GetProperty(0xb, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetName(LPCTSTR propVal)
{
	SetProperty(0xb, VT_BSTR, propVal);
}

CString IBRSet::GetPath()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}

void IBRSet::SetPath(LPCTSTR propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IBRSet operations



/////////////////////////////////////////////////////////////////////////////
// _DNAVOBRM properties

BOOL _DNAVOBRM::GetCompress()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void _DNAVOBRM::SetCompress(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

VARIANT _DNAVOBRM::GetDatastream()
{
	VARIANT result;
	GetProperty(0x3, VT_VARIANT, (void*)&result);
	return result;
}

void _DNAVOBRM::SetDatastream(const VARIANT& propVal)
{
	SetProperty(0x3, VT_VARIANT, &propVal);
}

VARIANT _DNAVOBRM::GetInfostream()
{
	VARIANT result;
	GetProperty(0x4, VT_VARIANT, (void*)&result);
	return result;
}

void _DNAVOBRM::SetInfostream(const VARIANT& propVal)
{
	SetProperty(0x4, VT_VARIANT, &propVal);
}

long _DNAVOBRM::GetSplitsize()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void _DNAVOBRM::SetSplitsize(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

LPDISPATCH _DNAVOBRM::GetSink()
{
	LPDISPATCH result;
	GetProperty(0x5, VT_DISPATCH, (void*)&result);
	return result;
}

void _DNAVOBRM::SetSink(LPDISPATCH propVal)
{
	SetProperty(0x5, VT_DISPATCH, propVal);
}

CString _DNAVOBRM::GetDescription()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}

void _DNAVOBRM::SetDescription(LPCTSTR propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}

CString _DNAVOBRM::GetRootDir()
{
	CString result;
	GetProperty(0x20, VT_BSTR, (void*)&result);
	return result;
}

void _DNAVOBRM::SetRootDir(LPCTSTR propVal)
{
	SetProperty(0x20, VT_BSTR, propVal);
}
/////////////////////////////////////////////////////////////////////////////
// _DNAVOBRM operations

long _DNAVOBRM::restore()
{
	long result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DNAVOBRM::GetProfile(LPCTSTR lpServerName, long nProfile)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lpServerName, nProfile);
	return result;
}

void _DNAVOBRM::SetProfile(LPCTSTR lpServerName, long nProfile, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpServerName, nProfile, lpszNewValue);
}

LPDISPATCH _DNAVOBRM::newbrset()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _DNAVOBRM::backup()
{
	long result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void _DNAVOBRM::addbrset(LPDISPATCH pBRSet)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pBRSet);
}

long _DNAVOBRM::readheader()
{
	long result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void _DNAVOBRM::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
