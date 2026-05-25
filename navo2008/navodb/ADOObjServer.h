/*
	NAVO Enterprise 2001
	ADO Implementation of IObjectServer
*/

#if !defined(AFX_ODBCOBJSERVER_H__F7C141A2_B1C8_48BD_9935_AD308B107092__INCLUDED_)
#define AFX_ODBCOBJSERVER_H__F7C141A2_B1C8_48BD_9935_AD308B107092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlatData;

const DWORD DEFAULT_CACHE_SIZE = 4250;

//---------------------------------- server object cache ----------------

class CFDObjectCache : public CInterface__
{
public:
	CFDObjectCache(DWORD dwCacheSize, bool bTrackDBWrites) :
		m_dwMaxCacheSize(dwCacheSize),
		m_bTrackDBWrites(bTrackDBWrites),
		m_poSharedVarHLISP(NewSCP(new CHyperLinkInfo()))
	{
#ifdef _DEBUG
		m_nCacheUpdates = 0;	//duty
		m_nCacheRequests = 0;
		m_nCacheHits = 0;		//win
		m_nMaxRunningObjects = 0;
#endif
		m_oObjectCacheMap._init_hash_table(1787);

		TRACE("Server cache initialized to max %d size\n", m_dwMaxCacheSize);
	}
	~CFDObjectCache()
	{

		m_poSharedVarHLISP = 0;
		Flush();

#ifdef _DEBUG
		ShowStatistics();
#endif
	}
	bool _is_disabled() const
	{
		return (m_dwMaxCacheSize == 0);
	}
	bool is_tracking_writes() const
	{
		return m_bTrackDBWrites;
	}
	void Flush();
	bool Get(long TypeId, long IdObj, SCP<CFlatData> & rpoFlatDataSP);
	void Set(long TypeId, long IdObj, SCP<CFlatData> &);
	void Remove(long TypeId, long IdObj);
	
	void purge();

	CSimpleCriticalSection & CriticalSection()
	{
		return m_oCS;
	}

	void track_write(long nUserDynamicCookie, const CFlatData & roFlatData);

	void SetSharedVar(long nVarNr, const CSmartOleVariant & roSOV);
	bool GetSharedVar(long nVarNr, CSmartOleVariant & roSOV);

	//do u¿ycia w sekcji
	bool GetMaxIdObj(long TypeId, long & nMaxIdObj);
	void SetMaxIdObj(long TypeId, long nMaxIdObj);
private:
	void _get_system_time(CSmartOleVariant & roSOV);
	void _get_system_date(CSmartOleVariant & roSOV);

	//object cache
	CSimpleCriticalSection	m_oCS;
	//{{
	CIndexedList<__int64, __int64, SCP<CFlatData> > m_oObjectCacheMap;
	CMap<long, long, long, long&> m_oUniqueIdMap;
	//}}
	CSimpleCriticalSection m_oSharedVarCS;
	//{{
	SCP<CHyperLinkInfo> m_poSharedVarHLISP;
	//}}
	CSimpleCriticalSection	m_oTrackWritesCS;
	SCP<IStream>	m_poTrackWritesStreamSP;

#ifdef _DEBUG
	void ShowStatistics();
	long m_nCacheUpdates;	//duty
	long m_nCacheRequests;
	long m_nCacheHits;		//win
	long m_nMaxRunningObjects;
#endif

	DWORD m_dwMaxCacheSize;
	bool  m_bTrackDBWrites;
};

class CDefinitionManagerProvider : public CInterface__
{
public:
	CDefinitionManagerProvider()
	{
	}
	~CDefinitionManagerProvider()
	{
	}

	SCP<CDefinitionManager> _get_definition(LPCTSTR lpAppName);
private:
	SCP<CDefinitionManager> _load_definition(LPCTSTR lpAppName);
	CSimpleCriticalSection	m_oCS;
	//{{
	CMap<CString, LPCTSTR, SCP<CDefinitionManager>, SCP<CDefinitionManager> &> m_oDMMap;
	//}}
};

//---------------------------------- object collection implementation ----------------
class CADOObjServer;

class CObjectCollectionImpl : public CCmdTargetInterface
{
public:
	CObjectCollectionImpl(CADOObjServer * poObjectServer) :
		m_poObjectServer(poObjectServer),
		m_nTotalCount(-1)
	{
	}
	virtual void OnFinalRelease();
	void OpenCollection(long CollectionId, long  IdParent, long * pTotalCount);
	void OpenOnStatement(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause,
		LPCTSTR lpJoinClause, bool bForwardOnly, long nTop);
	void OpenOnFTSQueryResults(long IdMapping, SCP<ISimpleEnumId> poSimpleEnumIdSP);
	bool _requery(long nPositionToKeep, long * pnCount);

	BEGIN_INTERFACE_PART(NAVOObjectCollection, INAVOObjectCollection)
		STDMETHOD(Fetch)(fetchdirection	FetchDirection, long * nCount,
			long * pDataLength, byte ** lpBinaryData, long nAbsolutePosition);
	STDMETHOD(Fetch2)(fetchdirection FetchDirection, long * nCount,
		long * pDataLength, SAFEARRAY ** pBinaryData, long nAbsolutePosition);
	STDMETHOD(GetCount)(long * pnCount);
	STDMETHOD(Refresh)(long nPositionToKeep, long * pnCount);
	END_INTERFACE_PART(NAVOObjectCollection)
	DECLARE_INTERFACE_MAP()
private:
	ADODB::_RecordsetPtr	m_poRecordsetPtr;
	CADOObjServer *			m_poObjectServer;
	long					m_nTotalCount;
};

//---------------------------------- main object server ----------------
class CTransactionHolder;

class CADOObjServer : public CCmdTargetWithErrorInfo
{
public:
	CADOObjServer();
	~CADOObjServer();

	void _clean_up();


	void OnObjectCollection_FinalRelease(CObjectCollectionImpl * poCursor);

	void _get_ADO_errors(CNavoException & roErrorStorage);
	//{{AFX_VIRTUAL(CADOObjServer)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CADOObjServer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	BEGIN_INTERFACE_PART(ObjectServer, IObjectServer)
		STDMETHOD(SetCoManagers)(LPCSTR pcAppName,
			ILockManager * pLockManager, long nLockManCookie,
			long nOptions);
	STDMETHOD(Close)(BYTE bOK);
	STDMETHOD(MakeTransaction)(long nDataLength, byte * lpBinaryData,
		long nBlobInfoCount, transblobinfo * pBlobInfo,
		long nWriteLockCount, const navolock * pNavoLock,
		BYTE bCommit);
	STDMETHOD(MakeTransaction2)(SAFEARRAY * *pBinaryData, long iLockCount, BYTE bCommit,
		/* [in] */ LPCSTR lpExtras,
		/* [out] */ LPSTR *lpResult);
	STDMETHOD(MakeTransaction_Stream)(
		IStream *pSrcStream,
		long IdParent,
		long IdMapping,
		navostreaminfo NSI);
	STDMETHOD(FinishTransaction)(BYTE bSuccess);
	STDMETHOD(GetObjectIfNewer)(long TypeId, long IdObj, long	VersionNoReturn, BYTE bWriteLock,
		long *pDataLength, byte ** lpBinaryData);
	STDMETHOD(GetObjectIfNewer2)(long TypeId, long IdObj, long VersionNoReturn, BYTE bWriteLock,
		long *pDataLength, SAFEARRAY ** lpBinaryData,
		/* [out] */ long *hr);
	STDMETHOD(GetUniqueIdent)(long TypeId, long * pNewId);
	STDMETHOD(FindOnField)(long nTypeId, LPCTSTR lpWhereClause, long * pFoundId);
	STDMETHOD(OpenOnStatement)(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause,
		LPCTSTR lpJoinClause, BYTE bForwardOnly, long nTop, INAVOObjectCollection ** pCollection);
	STDMETHOD(OpenCollection)(long CollectionId, long  IdParent, long * pTotalCount,
		INAVOObjectCollection ** pCollection);
	STDMETHOD(OpenFTSQuery)(long  IdMapping, LPCSTR lpQuery, INAVOObjectCollection ** pCollection);
	STDMETHOD(OpenDiscoRecSet)(LPCTSTR lpSQLClause, IStream ** pADORecordset, navostreaminfo * poNSI);
	STDMETHOD(OpenDiscoRecSet2)(LPCTSTR lpSQLClause, IUnknown **pADORecordset);
	STDMETHOD(CreateADOCommand)(IUnknown **pADOCommand);
	STDMETHOD(CreateADOParameter)(IUnknown **pADOParameter);
	STDMETHOD(Lock_AddItem)(long iInx, long iClass, long iTypeid, long iIdObj, long iExtra,long iLockType);
	STDMETHOD(CanDelete)(long nTypeId, long IdObj, IDispatch ** pADORecordset);
	STDMETHOD(SetProp)(objsrv_prop nProp, VARIANT vValue);
	STDMETHOD(GetProp)(objsrv_prop nProp, VARIANT * pvValue);
	STDMETHOD(ExecSQL)(LPCTSTR lpSQLCommand, long * pRecordsAffected);
	STDMETHOD(SetSharedVariable)(long nOriginatorCookie, long lVarNr, VARIANT nNewValue);
	STDMETHOD(GetSharedVariable)(long lVarNr, VARIANT * pvValue);
	STDMETHOD(GetStream)(long IdParent, long IdMapping, IStream ** pStream,
		navostreaminfo * poNSI, long * pVersion, long * pStreamId);
	STDMETHOD(CreateExtension)(LPCSTR lpExtensionProgId, IDispatch ** pExtensionDisp);
	STDMETHOD(WriteToArchive)(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream * pDestStream);
	STDMETHOD(ReadFromArchive)(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream* pSrcStream);
	STDMETHOD(PurgeCache)();
	END_INTERFACE_PART(ObjectServer)

	BEGIN_INTERFACE_PART(ObjectServerExtensionHost, IObjectServerExtensionHost)
		STDMETHOD(GetDBConnection)(IUnknown ** ppDBConnection);
	//STDMETHOD(GetStoreHub)(IDispatch ** ppNX);
	STDMETHOD(Lock)(navolock oNavoLock);
	STDMETHOD(UnLock)(navolock oNavoLock);
	END_INTERFACE_PART(ObjectServerExtensionHost)

	BEGIN_INTERFACE_PART(PingClient, IPingClient)		//ping client for file cache
		STDMETHOD(Ping)()
	{
		return S_OK;
	}
	END_INTERFACE_PART(PingClient)

	DECLARE_DYNCREATE(CADOObjServer)
	DECLARE_OLECREATE(CADOObjServer)

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CADOObjServer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	//--- engine specific functions ----------
	//--- mssql ------------------------------
	void _login_mssql();
	void _execute_simple_stat_mssql(const CFlatData & roFlatData, stdobjactions Action, long TypeId);
	bool _get_object_mssql(long TypeId, long IdObj, CFlatData ** poFlatData, long & rnLength,
		SCP<CStdObjDef>  & rpoStdObjDefSP);
	void _get_max_idobj_mssql(long TypeId, long & nMaxIdObj);
	void _execute_list_stat_mssql(const CFlatData & roFlatData, long TypeId, long IdObj);
	//----ms jet -----------------------------
	void _login_msjet();
	void _execute_simple_stat_msjet(const CFlatData & roFlatData, stdobjactions Action, long TypeId);
	bool _get_object_msjet(long TypeId, long IdObj, CFlatData ** poFlatData, long & rnLength,
		SCP<CStdObjDef>  & rpoStdObjDefSP);
	void _get_max_idobj_msjet(long TypeId, long & nMaxIdObj);
	void _execute_list_stat_msjet(const CFlatData & roFlatData, long TypeId, long IdObj);
	//----------------------------------------

	//implementation helpers
	void Login(bool bForRestore);
	void Logoff();

	void _begin_transaction();
	void _end_transaction(bool bCommit, long nFileTransactionId);

	void MakeTransaction(long nDataLength, byte * lpBinaryData,
		long nBlobInfoCount, transblobinfo * pBlobInfo,
		long nWriteLockCount, const navolock * pNavoLock,
		bool bCommit);
	void FinishTransaction(bool bSuccess);

	void ExecuteStatement(const CFlatData & roFlatData);
	bool GetObject(long TypeId, long IdObj, CFlatData ** poFlatData);
	void GetMaxIdObj(long TypeId, long & nMaxIdObj);
	void Find(long TypeId, LPCTSTR lpWhereClause, long & rFoundId);

	SCP<CObjectCollectionImpl> MakeFTSQuery(long IdMapping, LPCSTR lpQuery);

	long GetObjectsOnStmt(ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection,
		long TypeId, long IdObj, long nCount, CFlatData ** poFlatData, long nAbsPos = 0);
	long GetIdentsOnStmt(ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection,
		long nCount, CFlatData ** poFlatData, long nAbsPos = 0);
	void GetLongOnSelect(const CString & roSelectString, long & nResultLong);
	void ExecuteSimpleStatement(
		const CFlatData & roFlatData,
		stdobjactions Action,
		long TypeId);
	void ExecuteListStatement(
		const CFlatData & roFlatData,
		long TypeId,
		long IdObj);

	void ExecInsStreamMap(long nIdStream, long nIdParent, long nIdMapping);
	void ExecDelStreamMap(long nIdParent, long nIdMapping);
	long ExecSelStreamMap(long nIdParent, long nIdMapping, long & rnVersion);
	void ExecUpdStreamMap(long nIdParent, long nIdMapping, long nVersion);
	void _sync_cache_stream_counter();

	void purge_cache();
	bool _Move(ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection, long nAbsPos = 0);

	ADODB::_RecordsetPtr OpenDiscoRecSet(LPCTSTR lpSQLClause);

	bool LockSingleObject(long TypeId, long IdObj, bool bRead, bool bLock);

	long ExecSQL(LPCTSTR lpSQLCommand);

	SCP <IStream> GetFile(long IdParent, long IdMapping, navostreaminfo * poNSI,
		long * pVersion, long * pStreamId);
	void StoreFile(long IdParent, long IdMapping, SCP<IStream> & rpoStreamSP, navostreaminfo * poNSI);
	void RemoveFile(long IdParent, long IdMapping);

	HRESULT CommitFiles(long nFileTransactionId);
	HRESULT RollbackFiles(long nFileTransactionId);
	void ComposeCacheName(CString & roString);

	void CheckFileCacheGUID(bool bMustExistInDB, const CString & roPseudoServerString);

	void _update_effective_server();
	HRESULT _restore_database(LPCSTR lpSAUser, LPCSTR lpPwd, const CString & roPseudoServerString, SCP<IStream> poArchiveStreamSP);
	HRESULT _backup_database(LPCSTR lpSAUser, LPCSTR lpPwd, SCP<IStream> poArchiveStreamSP);

	//object cache functions
	//stdobjdef information
	//cooperating managers
	SCP<CDefinitionManager>		m_poDefinitionManagerSP;
	SCP<ILockManager>			m_poLockManagerSP;
	SCP<INotificationManager>	m_poNotificationManagerSP;

	//<file> field storage (implemented on ICachedData object)
	SCP<ICachedData>			m_poCachedDataSP;

	CString	m_oComposedCacheNameString;	//checked against guid cache name string

	long						m_nLockManCookie;
	long						m_nNotifyManCookie;
	long						m_nCachedData_PingCookie;
	bool	m_bCompressTrafficToClient;

	//ado runtime param
	ADODB::_ConnectionPtr				m_poConnectionPtr;
	bool	m_bInTransaction;
	dbenginetype m_EngineType;

	//odbc connection param
	CString m_oUserString;
	CString m_oPwdString;
	CString m_oEffectiveServerString;
	CString m_oDBString;

	SCP<CFDObjectCache> m_poFDObjectCacheSP;
	SCP<CTransactionHolder> m_poCurrentTHSP;
	CNavoOleInitHolder m_oNOIH;

	navolock m_arrLocks[100];

	friend class CTransactionHolder;
	friend class CObjectCollectionImpl;
	friend class CObjectCollectionImpl::XNAVOObjectCollection;
	friend class CWriteLockSingleObjectHolder;
};

class CTransactionHolder : public CInterface__
{
public:
	CTransactionHolder(CADOObjServer & roODBCObjServer) :
		m_roODBCObjServer(roODBCObjServer),
		m_bCommit(false),
		m_nFileTransactionId(0)
	{
		m_roODBCObjServer._begin_transaction();
	}
	long GetFileTransactionId() const
	{
		return m_nFileTransactionId;
	}
	void SetFileTransactionId(long nFileTransactionId)
	{
		m_nFileTransactionId = nFileTransactionId;
	}
	void SetCommit()
	{
		m_bCommit = true;
	}
	void SetRollback()
	{
		m_bCommit = false;
	}
	~CTransactionHolder()
	{
		m_roODBCObjServer._end_transaction(m_bCommit, m_nFileTransactionId);
	}
private:
	bool m_bCommit;
	CADOObjServer & m_roODBCObjServer;
	long m_nFileTransactionId;
};



#endif // !defined(AFX_ODBCOBJSERVER_H__F7C141A2_B1C8_48BD_9935_AD308B107092__INCLUDED_)
