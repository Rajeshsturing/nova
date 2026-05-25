// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IAdminIndexServer wrapper class

class IAdminIndexServer : public COleDispatchDriver
{
public:
	IAdminIndexServer() {}		// Calls COleDispatchDriver default constructor
	IAdminIndexServer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAdminIndexServer(const IAdminIndexServer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetMachineName();
	void SetMachineName(LPCTSTR lpszNewValue);
	LPDISPATCH AddCatalog(LPCTSTR bstrCatName, LPCTSTR bstrCatLocation);
	void RemoveCatalog(LPCTSTR bstrCatName, BOOL fDelDirectory);
	LPDISPATCH GetCatalogByName(LPCTSTR bstrCatalogName);
	BOOL FindFirstCatalog();
	BOOL FindNextCatalog();
	LPDISPATCH GetCatalog();
	void Start();
	void Stop();
	BOOL IsRunning();
	void EnableCI(BOOL fAutoStart);
	void Pause();
	BOOL IsPaused();
	void Continue();
	void SetLongProperty(LPCTSTR bstrPropName, long lVal);
	long GetLongProperty(LPCTSTR bstrPropName);
	void SetSZProperty(LPCTSTR bstrPropName, LPCTSTR bstrVal);
	CString GetSZProperty(LPCTSTR bstrPropName);
};
/////////////////////////////////////////////////////////////////////////////
// ICatAdm wrapper class

class ICatAdm : public COleDispatchDriver
{
public:
	ICatAdm() {}		// Calls COleDispatchDriver default constructor
	ICatAdm(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICatAdm(const ICatAdm& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void ForceMasterMerge();
	LPDISPATCH AddScope(LPCTSTR bstrScopeName, BOOL fExclude, const VARIANT& vtLogon, const VARIANT& vtPassword);
	void RemoveScope(LPCTSTR bstrScopePath);
	LPDISPATCH GetScopeByPath(LPCTSTR bstrPath);
	LPDISPATCH GetScopeByAlias(LPCTSTR bstrAlias);
	BOOL FindFirstScope();
	BOOL FindNextScope();
	LPDISPATCH GetScope();
	CString GetCatalogName();
	CString GetCatalogLocation();
	long GetWordListCount();
	long GetPersistentIndexCount();
	long GetQueryCount();
	long GetDocumentsToFilter();
	long GetFreshTestCount();
	long GetPctMergeComplete();
	long GetFilteredDocumentCount();
	long GetTotalDocumentCount();
	long GetPendingScanCount();
	long GetIndexSize();
	long GetUniqueKeyCount();
	long GetStateInfo();
	BOOL GetIsUpToDate();
	long GetDelayedFilterCount();
	long StartCatalog();
	long StopCatalog();
	long PauseCatalog();
	long ContinueCatalog();
	BOOL IsCatalogRunning();
	BOOL IsCatalogPaused();
	BOOL IsCatalogStopped();
};
/////////////////////////////////////////////////////////////////////////////
// IScopeAdm wrapper class

class IScopeAdm : public COleDispatchDriver
{
public:
	IScopeAdm() {}		// Calls COleDispatchDriver default constructor
	IScopeAdm(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IScopeAdm(const IScopeAdm& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Rescan(BOOL fFull);
	void SetLogonInfo(LPCTSTR bstrLogon, LPCTSTR bstrPassword);
	CString GetPath();
	void SetPath(LPCTSTR lpszNewValue);
	CString GetAlias();
	void SetAlias(LPCTSTR lpszNewValue);
	BOOL GetExcludeScope();
	void SetExcludeScope(BOOL bNewValue);
	BOOL GetVirtualScope();
	CString GetLogon();
};
/////////////////////////////////////////////////////////////////////////////
// IixssoQuery wrapper class

class IixssoQuery : public COleDispatchDriver
{
public:
	IixssoQuery() {}		// Calls COleDispatchDriver default constructor
	IixssoQuery(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IixssoQuery(const IixssoQuery& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetQuery();
	void SetQuery(LPCTSTR lpszNewValue);
	CString GetSortBy();
	void SetSortBy(LPCTSTR lpszNewValue);
	CString GetGroupBy();
	void SetGroupBy(LPCTSTR lpszNewValue);
	CString GetColumns();
	void SetColumns(LPCTSTR lpszNewValue);
	long GetLocaleID();
	void SetLocaleID(long nNewValue);
	long GetCodePage();
	void SetCodePage(long nNewValue);
	CString GetCatalog();
	void SetCatalog(LPCTSTR lpszNewValue);
	CString GetDialect();
	void SetDialect(LPCTSTR lpszNewValue);
	CString GetOptimizeFor();
	void SetOptimizeFor(LPCTSTR lpszNewValue);
	BOOL GetAllowEnumeration();
	void SetAllowEnumeration(BOOL bNewValue);
	long GetMaxRecords();
	void SetMaxRecords(long nNewValue);
	VARIANT GetStartHit();
	void SetStartHit(VARIANT* newValue);
	long GetResourceUseFactor();
	void SetResourceUseFactor(long nNewValue);
	BOOL GetQueryTimedOut();
	BOOL GetQueryIncomplete();
	BOOL GetOutOfDate();
	CString GetCiScope();
	CString GetCiFlags();
	void SetCiScope(LPCTSTR lpszNewValue);
	void SetCiFlags(LPCTSTR lpszNewValue);
	void SetQueryFromURL(LPCTSTR pwszQuery);
	CString QueryToURL();
	void DefineColumn(LPCTSTR pwszColDefinition);
	LPDISPATCH CreateRecordset(LPCTSTR pwszSequential);
	void Reset();
	void OnStartPage(LPUNKNOWN pUnk);
};
/////////////////////////////////////////////////////////////////////////////
// IixssoUtil wrapper class

class IixssoUtil : public COleDispatchDriver
{
public:
	IixssoUtil() {}		// Calls COleDispatchDriver default constructor
	IixssoUtil(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IixssoUtil(const IixssoUtil& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void AddScopeToQuery(LPDISPATCH pDisp, LPCTSTR pwszScope, LPCTSTR pwszDepth);
	long ISOToLocaleID(LPCTSTR pwszLocale);
	CString LocaleIDToISO(long lcid);
	CString TruncateToWhitespace(LPCTSTR pwszString, long cchLen);
	VARIANT GetArrayElement(VARIANT* pVarIn, long iElement);
	CString HTMLEncode(LPCTSTR pwszString, long CodePage);
	CString URLEncode(LPCTSTR pwszString, long CodePage);
};
