// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IBRSet wrapper class


/////////////////////////////////////////////////////////////////////////////
// IBRSet wrapper class

class IBRSet : public COleDispatchDriver
{
public:
	IBRSet() {}		// Calls COleDispatchDriver default constructor
	IBRSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IBRSet(const IBRSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetType();
	void SetType(long);
	CString GetMask();
	void SetMask(LPCTSTR);
	BOOL GetRecurse();
	void SetRecurse(BOOL);
	CString GetServer();
	void SetServer(LPCTSTR);
	CString GetDatabase();
	void SetDatabase(LPCTSTR);
	CString GetUser();
	void SetUser(LPCTSTR);
	CString GetPassword();
	void SetPassword(LPCTSTR);
	CString GetRemoteserver();
	void SetRemoteserver(LPCTSTR);
	BOOL GetRelative();
	void SetRelative(BOOL);
	CString GetName();
	void SetName(LPCTSTR);
	CString GetPath();
	void SetPath(LPCTSTR);

// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////
// _DNAVOBRM wrapper class

class _DNAVOBRM : public COleDispatchDriver
{
public:
	_DNAVOBRM() {}		// Calls COleDispatchDriver default constructor
	_DNAVOBRM(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DNAVOBRM(const _DNAVOBRM& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	BOOL GetCompress();
	void SetCompress(BOOL);
	VARIANT GetDatastream();
	void SetDatastream(const VARIANT&);
	VARIANT GetInfostream();
	void SetInfostream(const VARIANT&);
	long GetSplitsize();
	void SetSplitsize(long);
	LPDISPATCH GetSink();
	void SetSink(LPDISPATCH);
	CString GetDescription();
	void SetDescription(LPCTSTR);
	CString GetRootDir();
	void SetRootDir(LPCTSTR);

// Operations
public:
	long restore();
	CString GetProfile(LPCTSTR lpServerName, long nProfile);
	void SetProfile(LPCTSTR lpServerName, long nProfile, LPCTSTR lpszNewValue);
	LPDISPATCH newbrset();
	long backup();
	void addbrset(LPDISPATCH pBRSet);
	long readheader();
	void AboutBox();
};
