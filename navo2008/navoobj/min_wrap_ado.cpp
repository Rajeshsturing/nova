/*
	NAVO Enterprise 2008

	MSADO wrapper
*/

#include "stdafx.h"
#include "min_wrap_ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace MWA;
/////////////////////////////////////////////////////////////////////////////
// _Recordset properties

/////////////////////////////////////////////////////////////////////////////
// _Recordset operations

LPDISPATCH _Recordset::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Recordset::GetAbsolutePosition()
{
	long result;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetAbsolutePosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Recordset::SetRefActiveConnection(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Recordset::SetActiveConnection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT _Recordset::GetActiveConnection()
{
	VARIANT result;
	InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL _Recordset::GetBof()
{
	BOOL result;
	InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT _Recordset::GetBookmark()
{
	VARIANT result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::SetBookmark(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Recordset::GetCacheSize()
{
	long result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCacheSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetCursorType()
{
	long result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCursorType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _Recordset::GetEof()
{
	BOOL result;
	InvokeHelper(0x3ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Recordset::GetFields()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Recordset::GetLockType()
{
	long result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetLockType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetMaxRecords()
{
	long result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetRecordCount()
{
	long result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetRefSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Recordset::SetSource(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT _Recordset::GetSource()
{
	VARIANT result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::AddNew(const VARIANT& FieldList, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FieldList, &Values);
}

void _Recordset::CancelUpdate()
{
	InvokeHelper(0x3f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Close()
{
	InvokeHelper(0x3f6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Delete(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

VARIANT _Recordset::GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Rows, &Start, &Fields);
	return result;
}

void _Recordset::Move(long NumRecords, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumRecords, &Start);
}

void _Recordset::MoveNext()
{
	InvokeHelper(0x3fa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MovePrevious()
{
	InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MoveFirst()
{
	InvokeHelper(0x3fc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::MoveLast()
{
	InvokeHelper(0x3fd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Recordset::Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3fe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Source, &ActiveConnection, CursorType, LockType, Options);
}

void _Recordset::Requery(long Options)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3ff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Options);
}

void _Recordset::Update(const VARIANT& Fields, const VARIANT& Values)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x401, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Fields, &Values);
}

long _Recordset::GetAbsolutePage()
{
	long result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetAbsolutePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x417, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Recordset::GetEditMode()
{
	long result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT _Recordset::GetFilter()
{
	VARIANT result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Recordset::SetFilter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Recordset::GetPageCount()
{
	long result;
	InvokeHelper(0x41a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Recordset::GetPageSize()
{
	long result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetPageSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x418, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _Recordset::GetSort()
{
	CString result;
	InvokeHelper(0x407, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::SetSort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x407, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Recordset::GetStatus()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _Recordset::GetState()
{
	long result;
	InvokeHelper(0x41e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::UpdateBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

void _Recordset::CancelBatch(long AffectRecords)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x419, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords);
}

long _Recordset::GetCursorLocation()
{
	long result;
	InvokeHelper(0x41b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetCursorLocation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Recordset::NextRecordset(VARIANT* RecordsAffected)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x41c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecordsAffected);
	return result;
}

BOOL _Recordset::Supports(long CursorOptions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		CursorOptions);
	return result;
}

long _Recordset::GetMarshalOptions()
{
	long result;
	InvokeHelper(0x41d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Recordset::SetMarshalOptions(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Recordset::Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Criteria, SkipRecords, SearchDirection, &Start);
}

void _Recordset::Cancel()
{
	InvokeHelper(0x41f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPUNKNOWN _Recordset::GetDataSource()
{
	LPUNKNOWN result;
	InvokeHelper(0x420, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void _Recordset::SetRefDataSource(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x420, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _Recordset::GetActiveCommand()
{
	LPDISPATCH result;
	InvokeHelper(0x425, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Recordset::SetStayInSync(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _Recordset::GetStayInSync()
{
	BOOL result;
	InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _Recordset::GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x426, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		StringFormat, NumRows, ColumnDelimeter, RowDelimeter, NullExpr);
	return result;
}

CString _Recordset::GetDataMember()
{
	CString result;
	InvokeHelper(0x428, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::SetDataMember(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x428, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _Recordset::CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x429, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Bookmark1, &Bookmark2);
	return result;
}

LPDISPATCH _Recordset::Clone(long LockType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		LockType);
	return result;
}

void _Recordset::Resync(long AffectRecords, long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x400, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AffectRecords, ResyncValues);
}

void _Recordset::Seek(const VARIANT& KeyValues, long SeekOption)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x42a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &KeyValues, SeekOption);
}

void _Recordset::SetIndex(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _Recordset::GetIndex()
{
	CString result;
	InvokeHelper(0x42b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _Recordset::Save(const VARIANT& Destination, long PersistFormat)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x421, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination, PersistFormat);
}


long Fields::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Fields::Refresh()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Fields::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Fields::Delete(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void Fields::Append(LPCTSTR Name, long Type, long DefinedSize, long Attrib, const VARIANT& FieldValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, Type, DefinedSize, Attrib, &FieldValue);
}

void Fields::Update()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Fields::Resync(long ResyncValues)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ResyncValues);
}

void Fields::CancelUpdate()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


LPDISPATCH Field::GetProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Field::GetActualSize()
{
	long result;
	InvokeHelper(0x455, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field::GetAttributes()
{
	long result;
	InvokeHelper(0x45a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Field::GetDefinedSize()
{
	long result;
	InvokeHelper(0x44f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Field::GetName()
{
	CString result;
	InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Field::GetType()
{
	long result;
	InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT Field::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Field::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void Field::AppendChunk(const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x453, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Data);
}

VARIANT Field::GetChunk(long Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x454, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Length);
	return result;
}

VARIANT Field::GetOriginalValue()
{
	VARIANT result;
	InvokeHelper(0x450, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Field::GetUnderlyingValue()
{
	VARIANT result;
	InvokeHelper(0x451, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPUNKNOWN Field::GetDataFormat()
{
	LPUNKNOWN result;
	InvokeHelper(0x45b, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Field::SetRefDataFormat(LPUNKNOWN newValue)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x45b, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void Field::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field::SetDefinedSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x44f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Field::SetAttributes(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x45a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Field::GetStatus()
{
	long result;
	InvokeHelper(0x45c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


