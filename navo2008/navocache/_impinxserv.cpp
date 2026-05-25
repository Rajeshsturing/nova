// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "_impinxserv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IAdminIndexServer properties

/////////////////////////////////////////////////////////////////////////////
// IAdminIndexServer operations

CString IAdminIndexServer::GetMachineName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAdminIndexServer::SetMachineName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH IAdminIndexServer::AddCatalog(LPCTSTR bstrCatName, LPCTSTR bstrCatLocation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrCatName, bstrCatLocation);
	return result;
}

void IAdminIndexServer::RemoveCatalog(LPCTSTR bstrCatName, BOOL fDelDirectory)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrCatName, fDelDirectory);
}

LPDISPATCH IAdminIndexServer::GetCatalogByName(LPCTSTR bstrCatalogName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrCatalogName);
	return result;
}

BOOL IAdminIndexServer::FindFirstCatalog()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAdminIndexServer::FindNextCatalog()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAdminIndexServer::GetCatalog()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAdminIndexServer::Start()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAdminIndexServer::Stop()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IAdminIndexServer::IsRunning()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAdminIndexServer::EnableCI(BOOL fAutoStart)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fAutoStart);
}

void IAdminIndexServer::Pause()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IAdminIndexServer::IsPaused()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAdminIndexServer::Continue()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAdminIndexServer::SetLongProperty(LPCTSTR bstrPropName, long lVal)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrPropName, lVal);
}

long IAdminIndexServer::GetLongProperty(LPCTSTR bstrPropName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		bstrPropName);
	return result;
}

void IAdminIndexServer::SetSZProperty(LPCTSTR bstrPropName, LPCTSTR bstrVal)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrPropName, bstrVal);
}

CString IAdminIndexServer::GetSZProperty(LPCTSTR bstrPropName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		bstrPropName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// ICatAdm properties

/////////////////////////////////////////////////////////////////////////////
// ICatAdm operations

void ICatAdm::ForceMasterMerge()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH ICatAdm::AddScope(LPCTSTR bstrScopeName, BOOL fExclude, const VARIANT& vtLogon, const VARIANT& vtPassword)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrScopeName, fExclude, &vtLogon, &vtPassword);
	return result;
}

void ICatAdm::RemoveScope(LPCTSTR bstrScopePath)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrScopePath);
}

LPDISPATCH ICatAdm::GetScopeByPath(LPCTSTR bstrPath)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrPath);
	return result;
}

LPDISPATCH ICatAdm::GetScopeByAlias(LPCTSTR bstrAlias)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrAlias);
	return result;
}

BOOL ICatAdm::FindFirstScope()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICatAdm::FindNextScope()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH ICatAdm::GetScope()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString ICatAdm::GetCatalogName()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ICatAdm::GetCatalogLocation()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetWordListCount()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetPersistentIndexCount()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetQueryCount()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetDocumentsToFilter()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetFreshTestCount()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetPctMergeComplete()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetFilteredDocumentCount()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetTotalDocumentCount()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetPendingScanCount()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetIndexSize()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetUniqueKeyCount()
{
	long result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetStateInfo()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICatAdm::GetIsUpToDate()
{
	BOOL result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICatAdm::GetDelayedFilterCount()
{
	long result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::StartCatalog()
{
	long result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::StopCatalog()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::PauseCatalog()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICatAdm::ContinueCatalog()
{
	long result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICatAdm::IsCatalogRunning()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICatAdm::IsCatalogPaused()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICatAdm::IsCatalogStopped()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IScopeAdm properties

/////////////////////////////////////////////////////////////////////////////
// IScopeAdm operations

void IScopeAdm::Rescan(BOOL fFull)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fFull);
}

void IScopeAdm::SetLogonInfo(LPCTSTR bstrLogon, LPCTSTR bstrPassword)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrLogon, bstrPassword);
}

CString IScopeAdm::GetPath()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IScopeAdm::SetPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IScopeAdm::GetAlias()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IScopeAdm::SetAlias(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IScopeAdm::GetExcludeScope()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IScopeAdm::SetExcludeScope(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IScopeAdm::GetVirtualScope()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IScopeAdm::GetLogon()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IixssoQuery properties

/////////////////////////////////////////////////////////////////////////////
// IixssoQuery operations

CString IixssoQuery::GetQuery()
{
	CString result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetQuery(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IixssoQuery::GetSortBy()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetSortBy(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IixssoQuery::GetGroupBy()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetGroupBy(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IixssoQuery::GetColumns()
{
	CString result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetColumns(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IixssoQuery::GetLocaleID()
{
	long result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetLocaleID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IixssoQuery::GetCodePage()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetCodePage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IixssoQuery::GetCatalog()
{
	CString result;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetCatalog(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IixssoQuery::GetDialect()
{
	CString result;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetDialect(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IixssoQuery::GetOptimizeFor()
{
	CString result;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetOptimizeFor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IixssoQuery::GetAllowEnumeration()
{
	BOOL result;
	InvokeHelper(0x60020012, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetAllowEnumeration(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IixssoQuery::GetMaxRecords()
{
	long result;
	InvokeHelper(0x60020014, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetMaxRecords(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT IixssoQuery::GetStartHit()
{
	VARIANT result;
	InvokeHelper(0x60020016, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetStartHit(VARIANT* newValue)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x60020016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IixssoQuery::GetResourceUseFactor()
{
	long result;
	InvokeHelper(0x60020018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetResourceUseFactor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IixssoQuery::GetQueryTimedOut()
{
	BOOL result;
	InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IixssoQuery::GetQueryIncomplete()
{
	BOOL result;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IixssoQuery::GetOutOfDate()
{
	BOOL result;
	InvokeHelper(0x6002001c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IixssoQuery::GetCiScope()
{
	CString result;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IixssoQuery::GetCiFlags()
{
	CString result;
	InvokeHelper(0x6002001e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::SetCiScope(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IixssoQuery::SetCiFlags(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002001e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IixssoQuery::SetQueryFromURL(LPCTSTR pwszQuery)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020021, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pwszQuery);
}

CString IixssoQuery::QueryToURL()
{
	CString result;
	InvokeHelper(0x60020022, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IixssoQuery::DefineColumn(LPCTSTR pwszColDefinition)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pwszColDefinition);
}

LPDISPATCH IixssoQuery::CreateRecordset(LPCTSTR pwszSequential)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020024, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		pwszSequential);
	return result;
}

void IixssoQuery::Reset()
{
	InvokeHelper(0x60020025, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IixssoQuery::OnStartPage(LPUNKNOWN pUnk)
{
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x60020026, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pUnk);
}


/////////////////////////////////////////////////////////////////////////////
// IixssoUtil properties

/////////////////////////////////////////////////////////////////////////////
// IixssoUtil operations

void IixssoUtil::AddScopeToQuery(LPDISPATCH pDisp, LPCTSTR pwszScope, LPCTSTR pwszDepth)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDisp, pwszScope, pwszDepth);
}

long IixssoUtil::ISOToLocaleID(LPCTSTR pwszLocale)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020001, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pwszLocale);
	return result;
}

CString IixssoUtil::LocaleIDToISO(long lcid)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020002, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		lcid);
	return result;
}

CString IixssoUtil::TruncateToWhitespace(LPCTSTR pwszString, long cchLen)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		pwszString, cchLen);
	return result;
}

VARIANT IixssoUtil::GetArrayElement(VARIANT* pVarIn, long iElement)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_PVARIANT VTS_I4;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		pVarIn, iElement);
	return result;
}

CString IixssoUtil::HTMLEncode(LPCTSTR pwszString, long CodePage)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		pwszString, CodePage);
	return result;
}

CString IixssoUtil::URLEncode(LPCTSTR pwszString, long CodePage)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		pwszString, CodePage);
	return result;
}
