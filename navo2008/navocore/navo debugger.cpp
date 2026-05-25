// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "navo debugger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void _DebugMainSink::SetBPause(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x68030001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _DebugMainSink::GetBPause()
{
	BOOL result;
	InvokeHelper(0x68030001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DebugMainSink::message(const VARIANT& pcMsg)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60030002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &pcMsg);
}

void _DebugMainSink::registersink(VARIANT* pSink)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x60030003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pSink);
}

LPDISPATCH _DebugMainSink::GetSink()
{
	LPDISPATCH result;
	InvokeHelper(0x68030000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
