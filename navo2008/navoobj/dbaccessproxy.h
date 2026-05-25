/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDBAccessProxy

	wirtualizuje dostêp do bazy danych
	nie korzysta z niczego poza object serverem (navodb.exe)

	bardzo niskopoziomowy obiekt
*/

#ifndef _DBACCESSPROXY_H_
#define _DBACCESSPROXY_H_

class CFlatData;
class CDefinitionManager;

struct CDBAP_ConnectionParam;
class CDBAccessProxy : public CCmdTargetInterface
{
public:
	CDBAccessProxy(CNavoException & roErrorStorage) :
		m_roErrorStorage(roErrorStorage),
		m_bFirstDBAccess(true),
		m_bShowUI(false),
		m_nLockManager_Cookie(0),
		m_nServerObject_PingCookie(0),
		m_dwLockMan_GIT_Cookie(0),
		m_DynaLockStatShift(0)
	{
		EnableAutomation();

#ifdef _DEBUG
		debug_total_data_read = 0;
		debug_max_data_read = 0;
#endif

	}
	//init/done
	void Init(CDBAP_ConnectionParam & roConnectionParam, SCP<CDefinitionManager> poDefinitionManageSP);
	void Done();
	
	void SetShowUI(bool bShowUI)
	{
		m_bShowUI = bShowUI;
	}
	bool GetShowUI() const
	{
		return m_bShowUI;
	}
	
	//remote operations

	//reads object from server
	//S_OK - object read into roFlatData, S_FALSE - no newer version on server
	//ERROR_LOCK_FAILED - locked
	HRESULT BeginGetObject(long TypeId,long IdObj,long VersionNoReturn,bool bWriteLock,CFlatData & roFlatData); 
	void ReadListCollection(long nCollectionId,long nParentId,CFlatData & roFlatData,long & rnCount);

	bool WriteToArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pDestStream);
	bool ReadFromArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pSrcStream);
	
	//finishes read
	void EndGetObject(CFlatData & roFlatData);
	
	void GetServerRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,CString & roDataString);
	void SetServerRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,LPCTSTR lpValue); 

	long GetUniqueIdent(long TypeId);
	bool LockItems(navolock * poNLI,long nCount,bool bLock);
	
	//transakcja
	CString MakeTransaction(CFlatData & roFlatData,long nBlobCount,
		const transblobinfo * pBlobInfo,
		long nWriteLockCount,const navolock * pNavoLock,bool bCommit, LPCTSTR lpExtras);
	void FinishTransaction(bool bSuccess);
	
	//otwiera zwyk³y kursor
	SCP<INAVOObjectCollection> OpenCursor(long TypeId,LPCTSTR lpWhereClause,LPCTSTR lpOrderByClause,LPCTSTR lpJoinClause,bool bForwardOnly,long nTop);
	
	//otwiera collections dla stdobjlist
	SCP<INAVOObjectCollection> OpenListCollection(long  CollectionId,long  IdParent,long * pTotalCount);

	SCP<INAVOObjectCollection> OpenFTSQuery(long IdMapping,LPCSTR lpQuery);

	//otwiera ADO disconnected recordset
	SCP<IDispatch> OpenDiscoRecSet(LPCTSTR lpSQLClause);
	
	ADODB::_RecordsetPtr _OpenDiscoRecSet(LPCTSTR lpSQLClause);

	bool TestCanDelete(long TypeId,long IdObj,SCP<IDispatch> & rpoDiscoRecDispatchSP);
	SCP<IStream> GetDataBaseFile(long IdParent,long IdMapping,navostreaminfo & roNSI,long & rnVersion,long & rnStreamId);

	long FindStdObj(long TypeId,LPCTSTR lpWhereClause);
	long ExecSQL(LPCTSTR lpSQLCommand);

	void SetSharedVar(long nVarNr,const CSmartOleVariant & roSOV,long nNotifyOriginatorCookie);
	bool GetSharedVar(long nVarNr,CSmartOleVariant & roSOV);

	void SetServerProp(objsrv_prop eSrvProp,const CSmartOleVariant & roSOV);
	void GetServerProp(objsrv_prop eSrvProp,CSmartOleVariant & roSOV);

	SCP<IDispatch> create_server_extension(LPCTSTR lpExtensionProgID);
	//------------------------------------------------------- counted resources ----------
	bool create_counted_resource(LPCTSTR lpResName,long nMaxUsage);
	bool delete_counted_resource(LPCTSTR lpResName);
	long use_counted_resource(LPCTSTR lpResName);
	void release_counted_resource(LPCTSTR lpResName);
	long get_usage_counted_resource(LPCTSTR lpResName);
	//------------------------------------------------------------------------------------

	BEGIN_INTERFACE_PART(PingClient,IPingClient)		//ping client for navodb
		STDMETHOD(Ping)()
		{
			return S_OK;
		}
	END_INTERFACE_PART(PingClient)

	//ping interface
	DECLARE_INTERFACE_MAP()
private:
	bool _lock_items(SCP<ILockManager> & rpoLockManagerSP,navolock * poNLI,long nCount,bool bLock,bool bSilent);
	
	long _get_dynamic_second_lock_delay() const;
	void _register_lock_success();
	void _register_lock_failure();
		
	CNavoException &		m_roErrorStorage;
	SCP<IObjectServer>		m_rpc_poObjectServerSP;
	SCP<ILockManager>		m_rpc_poLockManagerSP;
	DWORD					m_dwLockMan_GIT_Cookie;
	SCP<IServerClient>		m_poServerClientSP;
	SCP<CDefinitionManager> m_poDefinitionManageSP;
	long					m_nLockManager_Cookie;
	long					m_nServerObject_PingCookie;

	//for marshalling
	SCP<IGlobalInterfaceTable>	m_poGITSP;

	bool					m_bFirstDBAccess;

	bool					m_bShowUI;

	DWORD					m_DynaLockStatShift;

	friend class CFirstAccessHolder;

#ifdef _DEBUG
	long	debug_total_data_read;
	long	debug_max_data_read;
#endif
};

#else
	#error __FILE__ already included
#endif
