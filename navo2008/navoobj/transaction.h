/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	CDataObjectModificationSet
		- zbiór u¿ywanych CDataObjectów

	CTransaction

*/

#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

class CFlatData;
class CNavoObjectCoordinator;
class CDefinitionManager;
class CNEO_user;
class CNEO_listuser;
class CNEO_fileuser;
class CNEO_storage;
class CNEO_liststorage;
class CNEO_filestorage;
class CNEO_rollbacklog;
class CDispatchDynamicResolver;
class CNEO_cursor;
class CNEO_lockmap;

//------------------------------------------------------------------------------------
// transaction
//------------------------------------------------------------------------------------
enum eTriggerFiredPhase
{
	tfp_notfired,
	tfp_firingnow,
	tfp_fired,
};

class CNEO_trans;

class CNEO_thread :public CInterface__
{
public:
	virtual SCP<CNEO_trans> CreateSubTransaction();
	CNEO_trans * GetCurrentTransaction() const
	{
		return m_poCurrentTransaction;
	}
	void SetCurrentTransaction(CNEO_trans * poCurrentTransaction);
	~CNEO_thread();

	//transaction 'commit' support
	void begin_transaction();
	void end_transaction();
	long get_transaction_level() const
	{
		return m_nPerformingTransLevel;
	}

	//binary transaction support
	CFlatData & flatdata()
	{
		if (m_poFlatDataSP.PointsNull())
		{
			m_poFlatDataSP = NewSCP(new CFlatData());
		}
		return *m_poFlatDataSP;
	}
	CArray<transblobinfo, transblobinfo &> & blobdata()
	{
		return m_oBlobData;
	}
	CString write2storage(bool bWithCommit, LPCTSTR lpExtras);
	eTriggerFiredPhase was_trigger_fired(long nTypeId, long nIdObj) const;
	void mark_trigger_firingnow(long nTypeId, long nIdObj);
	void mark_trigger_fired(long nTypeId, long nIdObj);
	void clean_transaction();

	bool is_auto_rollback() const;
	void set_auto_rollback(bool bAutoRollback);
private:
	CNEO_thread(CNavoObjectCoordinator * poCoordinator, CNavoException & roErrorStorage, SCP<CHyperLinkInfo> & rpoInitialEnvHLISP);

	CNEO_trans * m_poCurrentTransaction;
	SCP <CHyperLinkInfo> m_poEnvironmentHLISP;
	CNavoObjectCoordinator * m_poCoordinator;
	CNavoException &     m_roErrorStorage;
	long				 m_nPerformingTransLevel;
	bool				 m_bAutoRollBack;

	//binary MakeTransaction data
	SCP<CFlatData>							m_poFlatDataSP;
	CArray<transblobinfo, transblobinfo &>	m_oBlobData;
	CMap< hyper, hyper, eTriggerFiredPhase, eTriggerFiredPhase >		m_oFiredTriggersMap;

	friend class CNavoObjectCoordinator;
};

class CNEO_vlock : public CCmdTargetInterface
{
public:
	CNEO_vlock(CNEO_trans * poTrans, long nClass, long nTypeId, long nIdObj, long nExtra);
	~CNEO_vlock();

	void _set_no_flush()
	{
		m_bFlush = false;
	}
	bool _lock();
	//{{AFX_MSG(CNEO_vlock)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_vlock)
	afx_msg BOOL LockAUTO();
	afx_msg void UnlockAUTO();
	//}}AFX_DISPATCH

	DECLARE_DISPATCH_MAP()
private:
	void _unlock();

	bool m_bOwnsLock;
	bool m_bFlush;
	long m_nClass;
	long m_nTypeId;
	long m_nIdObj;
	long m_nExtra;
	CNEO_trans * m_poTrans;
};

class CNEO_mutex_holder_auto : public CCmdTargetInterface
{
public:
	~CNEO_mutex_holder_auto();
	//{{AFX_MSG(CNEO_mutex_holder_auto)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_mutex_holder_auto)
	//}}AFX_DISPATCH

	DECLARE_DISPATCH_MAP()
private:
	CNEO_mutex_holder_auto(CNEO_trans * poTrans, long nClass, long nTypeId, long nIdObj, long nExtra);

	long m_nClass;
	long m_nTypeId;
	long m_nIdObj;
	long m_nExtra;
	CNEO_trans * m_poTrans;

	friend class CNEO_trans;	//for ctor
};

enum eTransState
{
	trst_commited,			//commited	= no uncommited save
	trst_uncom_ok,			//uncommited with success
	trst_uncom_fail,		//uncommited but failure
};

class CNEO_trans : public CPropertyProvider__
{
public:
	~CNEO_trans();
	void OnNEO_user_FinalRelease(CNEO_user * poUser);
	void OnNEO_listuser_FinalRelease(CNEO_listuser * poListUser);
	void OnNEO_fileuser_FinalRelease(CNEO_fileuser * poFileUser);
	void OnNEO_cursor_FinalRelease(CNEO_cursor * poCursor);

	virtual SCP<CNEO_trans> CreateSubTransaction(bool bStandard);
	CDefinitionManager * GetDefinitionManager();

	SCP<CNEO_user> _new_object(long TypeId, long nParentTypeId, long nParentIdObj);
	SCP<CNEO_user> _get_object(long TypeId, long IdObj, long nParentTypeId, long nParentIdObj);

	SCP<CNEO_listuser> _get_list(long nCollectionId, long IdParent, bool bForNewParent);
	SCP<CNEO_listuser> _get_old_list(long nCollectionId, long nIdParent);

	SCP<CNEO_fileuser> _get_file(long nParentTypeId, long nParentIdObj, long nOuterFieldNr, bool bForNewParent);

	CString _save_changes(bool bWithCommit, LPCTSTR lpExtras);

	void _rollback();
	bool _commit();

	//-- environment get/set/test
	void set_var(long nVarNr, const CSmartOleVariant & croSOV);
	void get_var(long nVarNr, CSmartOleVariant & roSOV);

	virtual bool SafeGetProp(long lNumber, CSmartOleVariant & rSOV) const;

	bool is_var(long nVarNr);

	void _add_message_external_sink(CNavoErrorInfo & roErrorInfo);

	void AddMessage(CNavoErrorInfo & roErrorInfo)
	{
		m_roErrorStorage += roErrorInfo;

		if (m_poMessageSinkDispatchSP.PointsObject())
		{
			_add_message_external_sink(roErrorInfo);
		}
	}
	CNavoObjectCoordinator * _get_coordinator() const
	{
		return m_poCoordinator;
	}
	SCP <CHyperLinkInfo> & GetEnvironment()
	{
		return m_poEnvironmentHLISP;
	}
	void ApplyEnvironment(SCP<CHyperLinkInfo> & rpoHLISP);

	CNavoException & GetErrorStorage()
	{
		return m_roErrorStorage;
	}
	void AddRef_VLock()
	{
		m_dwVLockRefs++;
	}
	void Release_VLock()
	{
		m_dwVLockRefs--;
	}
	bool _is_inside_change_sequence() const;

	bool is_user_modified();
	void set_user_modified(bool bUserModified);

	bool fwd_test_can_delete(long TypeId, long IdObj, SCP<IDispatch> & rpoDiscoRecDispatchSP);
	SCP<INAVOObjectCollection> fwd_open_cursor(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause, LPCTSTR lpJoinClause, bool bForwardOnly, long nTop);

	SCP<CNEO_cursor> CreateRawCursor(long TypeId, LPCTSTR lpWhere, LPCTSTR lpOrderBy, LPCTSTR lpJoin);
	SCP<CNEO_cursor> CreateObjectCursor(long TypeId, long IdCursor);
	SCP<CNEO_cursor> CreateFTSCursor(long TypeId, long nOuterFieldNr, LPCTSTR lpQuery);

	CDispatchDynamicResolver * GetTransaction_DDR();

	eTriggerFiredPhase fwd_was_trigger_fired(long nTypeId, long nIdObj) const
	{
		return m_poThreadSP->was_trigger_fired(nTypeId, nIdObj);
	}

	virtual void get_canonical_string(CString & roDestString) const;

	static SCP<CNEO_trans> FromIDispatch(LPDISPATCH lpDispatch);

	//{{AFX_MSG(CNEO_trans)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_trans)
	afx_msg LPDISPATCH GetObjectAUTO(long TypeId, long IdObj);
	afx_msg LPDISPATCH GetNewObjectAUTO(long TypeId);
	afx_msg void DiscardAUTO();
	afx_msg void AcceptAUTO();
	afx_msg BOOL IsUserModifiedAUTO();
	afx_msg void AddMessageAUTO(long nErrorCode, long IdHelpPage, LPCTSTR lpMsg);
	afx_msg BOOL IsVarAUTO(long Nr);
	afx_msg VARIANT GetVarAUTO(long Nr);
	afx_msg void SetVarAUTO(long Nr, const VARIANT FAR& newValue);
	afx_msg LPDISPATCH CreateSubTransAUTO();
	afx_msg LPDISPATCH CreateNewThreadTransAUTO();
	afx_msg void SetUserModifAUTO(BOOL bNewVal);
	afx_msg long FindStdObjAUTO(long TypeId, LPCTSTR lpWhere);
	afx_msg LPDISPATCH CreateDiscoRecSetAUTO(LPCTSTR lpSQLClause);
	afx_msg LPDISPATCH CreateRawCursorAUTO(long TypeId, LPCTSTR lpWhere, LPCTSTR lpOrderBy, LPCTSTR lpJoin);
	afx_msg LPDISPATCH CreateObjectCursorAUTO(long TypeId, long IdCursor);
	afx_msg LPDISPATCH CreateFTSCursorAUTO(long TypeId, const VARIANT FAR& FieldName, LPCTSTR lpQuery);
	afx_msg BOOL SaveAUTO();
	afx_msg BOOL SaveAndCommitAUTO();
	afx_msg long ExecSQLAUTO(LPCTSTR lpSQLCommand);
	afx_msg BOOL ExclusiveVirtualLockAUTO(long nIdent, long nIdent2);
	afx_msg LPDISPATCH CreateVirtualLockAUTO(long nIdent, long nIdent2);
	afx_msg LPDISPATCH GetAFC_AUTO();
	afx_msg BOOL IsObjectModified_SimpleAUTO(long TypeId, long IdObj);
	afx_msg BSTR ReplaceEnvironmentVarsAUTO(LPCTSTR lpString);
	afx_msg LPDISPATCH GetRealThisAUTO();
	afx_msg LPDISPATCH CreateServerExtensionAUTO(LPCTSTR lpString);
	afx_msg void ActivateMeAUTO();
	afx_msg VARIANT GetServerPropertyAUTO(long Nr);
	afx_msg void SetAutoRollbackAUTO(BOOL bNewVal);

	afx_msg LPDISPATCH GetMutexAUTO(long TypeId, long IdObj, long nExtra);
	afx_msg void ParseXML_AUTO(LPDISPATCH pSinkObject, const VARIANT FAR& rvarStream);
	afx_msg LPDISPATCH GetNX_AUTO();
	afx_msg	void MessageSink_AUTO(LPDISPATCH pSinkObject);
	afx_msg LPDISPATCH CreateHLIAUTO();
	
	afx_msg BSTR Save2AUTO(BOOL bCommit, LPCTSTR lpExtras);

#ifdef _DEBUG
	afx_msg long GetDebugNrAUTO();
#endif
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
public:
	CNEO_trans(CNavoObjectCoordinator * poCoordinator, CNavoException & roErrorStorage,
		bool bStandardMode, CNEO_trans * poPreviousTrans, SCP<CNEO_thread> & rpoThreadSP, SCP<CHyperLinkInfo> & rpoInitialEnvHLISP,
		SCP<IDispatch> poMessageSinkDispatchSP);

	SCP<CNEO_thread> get_thread();

	friend class CNEO_thread;
public:
	void _write_changes(bool bWithCommit);

	//creates 'writable' copy of storage for neo_user
	SCP<CNEO_storage> _copy_on_write_storage(SCP<CNEO_storage> & rpoROStorageSP);
	SCP<CNEO_liststorage> _copy_on_write_liststorage(SCP<CNEO_liststorage> & rpoROListStorageSP);

	SCP<CNEO_storage> _write_lock(SCP<CNEO_storage> & rpoStorageSP, bool & rbSuccess, CNEO_user * poUser);
	void _write_unlock(SCP<CNEO_storage> & rpoStorageSP);
	void release_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra);
	bool aquire_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra);
	void flush_pending_unlocks();

	SCP<CNEO_storage> _search_reference_storage_map(long TypeId, long IdObj);

	void on_mutex_destroyed(long nClass, long nTypeId, long nIdObj, long nExtra);
private:
	bool _exclusive_virtual_lock(long nClass, long nTypeId, long nIdObj, long nExtra);
	SCP<CNEO_vlock> _create_vlock(long nClass, long nTypeId, long nIdObj, long nExtra);

	enum eProvStorRes
	{
		psr_local,
		psr_prevtrans,
		psr_cacheinit,
		psr_cachenoinit
	};

	SCP<CNEO_storage> _provide_storage(long TypeId, long IdObj, bool bForceLoad, eProvStorRes & rePSR);
	SCP<CNEO_liststorage> _provide_liststorage(long nCollectionId, long nIdParent, bool bForNewParent, bool & rbLocalCopy);

	void purge_maps();		//czyœci mapy z nieu¿ywanych storage /list storage
	void evaluate_and_purge_not_needsave_maps(bool bPurge);	//czyœci mapy z niezmienionych i wylicza stan zmian

	void evaluate_storage(SCP<CNEO_storage> & rpoStorageSP);
	void evaluate_list_storage(SCP<CNEO_liststorage> & rpoListStorageSP);
	void evaluate_file_storage(SCP<CNEO_filestorage> & rpoFileStorageSP);

	void release_write_locks();
	void _clean();

	void _copy_workset(CNEO_trans * poDestTrans, bool bChangedOnly);
	//SEPTBUG	void _update_reference_storage();
	void _propagate_workset();

	long fwd_find_stdobj(long TypeId, LPCTSTR lpWhereClause);
	long fwd_ExecSQL(LPCTSTR lpSQLCommand);

	//---------- manages local storage copies ----------------------------
	CNEO_storage * _search_local_storage_map(long TypeId, long IdObj);
	void _add_to_local_storage_map(SCP<CNEO_storage> & rpoStorageSP);
	void _remove_from_local_storage_map(long TypeId, long IdObj);
	void _add_to_reference_storage_map(SCP<CNEO_storage> & rpoStorageSP);
	void _add__or_replace_reference_storage_map(SCP<CNEO_storage> & rpoStorageSP);

	//---------- manages local liststorage copies ------------------------
	CNEO_liststorage * _search_local_liststorage_map(long nCollectionId, long nIdParent);
	void _add_to_local_liststorage_map(SCP<CNEO_liststorage> & rpoListStorageSP);
	void _remove_from_local_liststorage_map(long nCollectionId, long nIdParent);
	void _add_to_reference_liststorage_map(SCP<CNEO_liststorage> & rpoListStorageSP);
	SCP<CNEO_liststorage> _search_reference_liststorage_map(long nCollectionId, long nIdParent);

	//---------- manages local file copies ------------------------
	CNEO_filestorage * _search_local_filestorage_map(long nParentTypeId, long nParentIdObj, long nOuterFieldNr);
	void _add_to_local_filestorage_map(SCP<CNEO_filestorage> & rpoFileStorageSP);
	void _remove_from_local_filestorage_map(SCP<CNEO_filestorage> & rpoFileStorageSP);

	//---------- manages running neo_{list|file}user objects ------------------------
	void _add_to_user_map(CNEO_user * poUser);
	CNEO_user * _search_user_map(long TypeId, long IdObj);
	void _add_to_listuser_map(CNEO_listuser * poListUser);
	CNEO_listuser * _search_listuser_map(long CollectionId, long ParentId);
	void _add_to_fileuser_map(CNEO_fileuser * poFileUser);
	CNEO_fileuser * _search_fileuser_map(long nParentTypeId, long nParentIdObj, long nOuterFieldNr);

	//--------- manages write locks --------------------------------------
	bool _is_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra);
	void _purge_children_and_lists_of_locked_parent(SCP<CNEO_storage> & rpoStorageSP);

	void _propagate_storage_change(SCP<CNEO_storage> & rpoStorageSP);
	void _propagate_liststorage_change(SCP<CNEO_liststorage> & rpoListStorageSP);
	void _propagate_filestorage_change(SCP<CNEO_filestorage> & rpoFileStorageSP);

	void _propagate_commited(eTransState TransState);
	//--------- special functions ----------------------------------------
	SCP<CNEO_user> _get_user_for_ready_storage(SCP<CNEO_storage> & rpoStorageSP);
	//--------- data structures ------------------------------------------

	//running object maps
	CMap<hyper, hyper, CNEO_user *, CNEO_user *>			m_oNEO_userMap;
	CMap<hyper, hyper, CNEO_listuser *, CNEO_listuser *>	m_oNEO_listuserMap;
	CMap<hyper, hyper, CNEO_fileuser *, CNEO_fileuser *>	m_oNEO_fileuserMap;

	//local storage lists
	CIndexedList<hyper, hyper, SCP<CNEO_storage> >		m_oLocalStorageMap;
	CIndexedList<hyper, hyper, SCP<CNEO_liststorage> >	m_oLocalListStorageMap;
	CIndexedList<hyper, hyper, SCP<CNEO_filestorage> >	m_oLocalFileStorageMap;

	//reference maps
	CMap<hyper, hyper, SCP<CNEO_storage>, SCP<CNEO_storage> >			m_oReferenceStorageMap;
	CMap<hyper, hyper, SCP<CNEO_liststorage>, SCP<CNEO_liststorage> > m_oReferenceListStorageMap;

	CArray< SCP<CNEO_vlock>, SCP<CNEO_vlock> > m_oVirtLockArray;

	//pending write locks aquired in this trans
	CNEO_lockmap * m_poLocalLockMap;

	SCP<CNEO_rollbacklog> m_poRollbackLogSP;

	long	m_dwVLockRefs;
	//-------- links etc. ---------------------------
	CNavoObjectCoordinator *	m_poCoordinator;
	CNavoException &			m_roErrorStorage;
	CNEO_trans *				m_poPrevTransaction;
	SCP<CNEO_thread>			m_poThreadSP;
	SCP <CHyperLinkInfo>		m_poEnvironmentHLISP;

	eTransState					m_eTransState;
	bool						m_bStandardMode;
	SCP<CNEO_trans>				m_poAutoSubTransSP;

	SCP<IDispatch>				m_poMessageSinkDispatchSP;
	DISPID						m_dispid_message_sink;

	friend class CNEO_rollbacklog;
	friend class CNEO_rollbackholder;
	friend class CNEO_thread;

	friend class CNEO_performer;
	friend class CNEO_trans_begend_holder;

#ifdef _DEVELOPER_EDITION_
public:
	const long _debug_trans_nr;
	friend class CPageStack;		//for m_poPrevTransaction,m_bStandardMode
#endif
};


//------------------------------------------------------------------------------------
// single sequence rollback holder
//------------------------------------------------------------------------------------
class CNEO_rollbackholder : public CInterface__
{
public:
	CNEO_rollbackholder(SCP<CNEO_trans> & rpoTransSP) :
		m_poTransSP(rpoTransSP),
		m_bOK(false)
	{
		ASSERT(m_poTransSP.PointsObject());
		m_bTopLevel = m_poTransSP->m_poRollbackLogSP->_begin_operation();
	}
	~CNEO_rollbackholder()
	{
		m_poTransSP->m_poRollbackLogSP->_finish_operation(m_bOK);
	}
	bool _is_toplevel() const
	{
		return m_bTopLevel;
	}
	void Success()
	{
		m_bOK = true;
	}
	//registration of various changes
	void _registerundo_objectfieldchange(long nTypeId, long IdObj, long nInternalFldNr,
		const CSmartOleVariant & roOldValueSOV)
	{
		m_poTransSP->m_poRollbackLogSP->_registerundo(
			NewSCP<CNEO_undoitem__>(
				new CNEO_undofieldchange(nTypeId, IdObj, nInternalFldNr, roOldValueSOV)
				));
	}
	void _registerundo_newobjectcreate(long nTypeId, long IdObj)
	{
		m_poTransSP->m_poRollbackLogSP->_registerundo(
			NewSCP<CNEO_undoitem__>(
				new CNEO_undonewobject(nTypeId, IdObj)
				));
	}
	void _registerundo_markdelobject(long nTypeId, long IdObj, bool bOldState)
	{
		m_poTransSP->m_poRollbackLogSP->_registerundo(
			NewSCP<CNEO_undoitem__>(
				new CNEO_undomarkdel(nTypeId, IdObj, bOldState)
				));
	}
	void _registerundo_listinsupddel(long nCollectionId, long IdParent, long nOuterIndex,
		long IdChild)
	{
		ASSERT(nOuterIndex > 0 || nOuterIndex < 0);
		m_poTransSP->m_poRollbackLogSP->_registerundo(
			NewSCP<CNEO_undoitem__>(
				new CNEO_undolistoper(nCollectionId, IdParent, nOuterIndex, IdChild)
				));
	}
	void _registerundo_writelock(long nClass, long nTypeId, long nIdObj, long nExtra)
	{
		m_poTransSP->m_poRollbackLogSP->_registerundo(
			NewSCP<CNEO_undoitem__>(
				new CNEO_undowritelock(nClass, nTypeId, nIdObj, nExtra)
				));
	}
private:
	bool m_bOK;
	bool m_bTopLevel;
	SCP<CNEO_trans> m_poTransSP;
};

inline bool CNEO_thread::is_auto_rollback() const
{
	return m_bAutoRollBack;
}

inline void CNEO_thread::set_auto_rollback(bool bAutoRollback)
{
	m_bAutoRollBack = bAutoRollback;
}

inline SCP<CNEO_thread> CNEO_trans::get_thread()
{
	return m_poThreadSP;
}

#else
#error __FILE__ already included
#endif


