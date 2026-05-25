/*
	NAVO Enterprise 2008

	minimal MSADO wrapper
*/

#ifndef _MIN_WRAP_ADO_H_
#define _MIN_WRAP_ADO_H_

namespace MWA 
{
class _Recordset : public COleDispatchDriver
{
public:
	_Recordset() {}		// Calls COleDispatchDriver default constructor
	_Recordset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Recordset(const _Recordset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetProperties();
	long GetAbsolutePosition();
	void SetAbsolutePosition(long nNewValue);
	void SetRefActiveConnection(LPDISPATCH newValue);
	void SetActiveConnection(const VARIANT& newValue);
	VARIANT GetActiveConnection();
	BOOL GetBof();
	VARIANT GetBookmark();
	void SetBookmark(const VARIANT& newValue);
	long GetCacheSize();
	void SetCacheSize(long nNewValue);
	long GetCursorType();
	void SetCursorType(long nNewValue);
	BOOL GetEof();
	LPDISPATCH GetFields();
	long GetLockType();
	void SetLockType(long nNewValue);
	long GetMaxRecords();
	void SetMaxRecords(long nNewValue);
	long GetRecordCount();
	void SetRefSource(LPDISPATCH newValue);
	void SetSource(LPCTSTR lpszNewValue);
	VARIANT GetSource();
	void AddNew(const VARIANT& FieldList, const VARIANT& Values);
	void CancelUpdate();
	void Close();
	void Delete(long AffectRecords);
	VARIANT GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields);
	void Move(long NumRecords, const VARIANT& Start);
	void MoveNext();
	void MovePrevious();
	void MoveFirst();
	void MoveLast();
	void Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options);
	void Requery(long Options);
	void Update(const VARIANT& Fields, const VARIANT& Values);
	long GetAbsolutePage();
	void SetAbsolutePage(long nNewValue);
	long GetEditMode();
	VARIANT GetFilter();
	void SetFilter(const VARIANT& newValue);
	long GetPageCount();
	long GetPageSize();
	void SetPageSize(long nNewValue);
	CString GetSort();
	void SetSort(LPCTSTR lpszNewValue);
	long GetStatus();
	long GetState();
	void UpdateBatch(long AffectRecords);
	void CancelBatch(long AffectRecords);
	long GetCursorLocation();
	void SetCursorLocation(long nNewValue);
	LPDISPATCH NextRecordset(VARIANT* RecordsAffected);
	BOOL Supports(long CursorOptions);
	long GetMarshalOptions();
	void SetMarshalOptions(long nNewValue);
	void Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start);
	void Cancel();
	LPUNKNOWN GetDataSource();
	void SetRefDataSource(LPUNKNOWN newValue);
	LPDISPATCH GetActiveCommand();
	void SetStayInSync(BOOL bNewValue);
	BOOL GetStayInSync();
	CString GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr);
	CString GetDataMember();
	void SetDataMember(LPCTSTR lpszNewValue);
	long CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2);
	LPDISPATCH Clone(long LockType);
	void Resync(long AffectRecords, long ResyncValues);
	void Seek(const VARIANT& KeyValues, long SeekOption);
	void SetIndex(LPCTSTR lpszNewValue);
	CString GetIndex();
	void Save(const VARIANT& Destination, long PersistFormat);
};

class Fields : public COleDispatchDriver
{
public:
	Fields() {}		// Calls COleDispatchDriver default constructor
	Fields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Fields(const Fields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void Refresh();
	LPDISPATCH GetItem(const VARIANT& Index);
	void Delete(const VARIANT& Index);
	void Append(LPCTSTR Name, long Type, long DefinedSize, long Attrib, const VARIANT& FieldValue);
	void Update();
	void Resync(long ResyncValues);
	void CancelUpdate();
};

class Field : public COleDispatchDriver
{
public:
	Field() {}		// Calls COleDispatchDriver default constructor
	Field(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Field(const Field& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetProperties();
	long GetActualSize();
	long GetAttributes();
	long GetDefinedSize();
	CString GetName();
	long GetType();
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
	// method 'GetPrecision' not emitted because of invalid return type or parameter type
	// method 'GetNumericScale' not emitted because of invalid return type or parameter type
	void AppendChunk(const VARIANT& Data);
	VARIANT GetChunk(long Length);
	VARIANT GetOriginalValue();
	VARIANT GetUnderlyingValue();
	LPUNKNOWN GetDataFormat();
	void SetRefDataFormat(LPUNKNOWN newValue);
	// method 'SetPrecision' not emitted because of invalid return type or parameter type
	// method 'SetNumericScale' not emitted because of invalid return type or parameter type
	void SetType(long nNewValue);
	void SetDefinedSize(long nNewValue);
	void SetAttributes(long nNewValue);
	long GetStatus();
};

}

#else
	#error __FILE__ already included
#endif