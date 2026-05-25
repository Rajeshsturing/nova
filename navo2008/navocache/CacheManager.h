/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManager - local cache manager
*/

#if !defined(AFX_CACHEMANAGER_H__6AE1761E_C76B_4B7C_B291_4C45393137A7__INCLUDED_)
#define AFX_CACHEMANAGER_H__6AE1761E_C76B_4B7C_B291_4C45393137A7__INCLUDED_

/*
	stores single cached item description
*/
class CItemVariantInfo;
class CCacheInfoItem : public CInterface__
{
public:
	CCacheInfoItem(CItemVariantInfo * poIVI) :
		m_poIVI(poIVI)
	{
		ASSERT(m_poIVI);
	}
	void write_to_archive(CArchive & roArchive);
	void read_from_archive(CArchive & roArchive);

	bool compare(long DescriptorLength,BYTE * pcDescriptor)
	{
		if(DescriptorLength != m_oDescriptorArray.GetSize())
		{
			return false;
		}
		return(memcmp(pcDescriptor,m_oDescriptorArray.GetData(),DescriptorLength) == 0);
	}
	void set_descriptor(long DescriptorLength,BYTE * pcDescriptor)
	{
		m_oDescriptorArray.SetSize(DescriptorLength);
		memcpy(m_oDescriptorArray.GetData(),pcDescriptor,DescriptorLength);
	}
	void get_full_path(CString & roFullPathString) const;
	LPCTSTR get_file_name() const
	{
		return m_oFileNameString;
	}
	void _set_file_name(LPCTSTR lpFileName)
	{
		m_oFileNameString = lpFileName;
	}
	static LPCTSTR get_suffix();
	void write_to_backup_archive(SCP<IStream> poOutStreamSP);
	void load_from_backup_archive(SCP<IStream> poInStreamSP);
private:
	CArray<BYTE,BYTE&>	m_oDescriptorArray;			//persistent
	CString				m_oFileNameString;			//cache file name (not full path!). no extension
	CItemVariantInfo *	m_poIVI;

};

/*
	stores single file variants
*/

class CSingleServerPlaceCacheInfo;
class CItemVariantInfo : public CInterface__
{
public:
	CItemVariantInfo(CSingleServerPlaceCacheInfo * poSSI) :
		m_poSSI(poSSI)
	{
		ASSERT(m_poSSI);
	}
	void write_to_archive(CArchive & roArchive);
	void read_from_archive(CArchive & roArchive);

	bool get_info(long DescriptorLength,BYTE * pcDescriptor,SCP<CCacheInfoItem> & rpoCacheItemInfoSP);
	bool is_empty() const
	{
		return (m_oVariantsArray.GetSize() == 0);
	}
	//inside critical section
	//returns true if existed
	bool trans_get_or_create_info(long DescriptorLength,BYTE * pcDescriptor,SCP<CCacheInfoItem> & rpoCacheItemInfoSP);

	bool trans_remove(long DescriptorLength,BYTE * pcDescriptor);

	void get_item_full_path(const CCacheInfoItem * poCII,CString & roFullPathString) const;
	
	LPCTSTR get_sub_dir() const
	{
		return m_oSubDirString;
	}
	void _set_sub_dir(LPCTSTR lpSubDir)
	{
		ASSERT(m_oSubDirString.IsEmpty());
		m_oSubDirString = lpSubDir;
	}
	const navostreaminfo & _get_stream_info() const
	{
		return m_oNSI;
	}
	void _set_stream_info(const navostreaminfo & roNSI)
	{
		_copy_navostreaminfo(roNSI,m_oNSI);
	}
	SCP<CCacheInfoItem> get_item(long nIndex);
	static void supply_extension(CString & roPathString,bool bBlobDB,const navostreaminfo & roNSI);

	void write_to_backup_archive(SCP<IStream> poOutStreamSP);
	void load_from_backup_archive(SCP<IStream> poInStreamSP);
private:
	long _find(long DescriptorLength,BYTE * pcDescriptor);

	//m_poSSI->m_oAtomCS used for synchro

	CArray< SCP<CCacheInfoItem>, SCP<CCacheInfoItem> & > m_oVariantsArray;		//persistent
	navostreaminfo m_oNSI;
	CString m_oSubDirString;
	CSingleServerPlaceCacheInfo * m_poSSI;
};

/*
	stores single server place (ServerPath) description
	equal to single AppDB
*/
class CCacheManager;

class CSingleServerPlaceCacheInfo : public CInterface__
{
public:
	CSingleServerPlaceCacheInfo(CCacheManager * poCacheManager,LPCTSTR lpFullServerPath);
	long _read_info();
	void _write_info();
	bool get_info(long IdFile,SCP<CItemVariantInfo> & rpoFileVariantsInfoSP);

	bool is_dirty() const
	{
		return m_bDirty;
	}
	void set_dirty()
	{
		m_bDirty = true;
	}
	void set_dirty(const CItemVariantInfo * /*poIVI*/)
	{
		m_bDirty = true;
	}
	LPCTSTR _get_GUID() const
	{
		return m_oGUIDString;
	}
	bool is_blob_database() const
	{
		return m_bBlobDataBase;
	}

	void _initialize_first();
	//inside critical section
	void trans_get_or_create_info(long IdFile,SCP<CItemVariantInfo> & rpoFileVariantsInfoSP);
	void trans_remove(long IdFile);

	CSimpleCriticalSection & _get_atom_cs()
	{
		return m_oAtomCS;
	}

	SCP<CSimpleLock> LockItemInfo()
	{
		return NewSCP(new CSimpleLock(m_oItemInfoCS));
	}
	void _get_storage_dir(CString & roDirString) const
	{
		roDirString = m_oStorageDirString;
	}
	void get_item_full_path(const CItemVariantInfo * poIVI,const CCacheInfoItem * poCII,CString & roFullPathString) const;
	void create_item_full_path(long IdFile,CString & roPathString,CString & roFileNameString);
	void upgrade_from_version(long nVersion);

	static void unsetup_indexing_service();
	HRESULT fts_query(LPCTSTR lpQuery,ISimpleEnumId ** ppSimpleEnumFileId);

	void write_to_backup_archive(SCP<IStream> poOutStreamSP);
	void load_from_backup_archive(SCP<IStream> poInStreamSP);

private:
	void _get_subdir_for_ivi(long IdFile,CString & roSubDir);
	void _get_infofile_name(CString & roInfoFileString);
	long _read_from_archive(CArchive & roArchive,LPCTSTR lpFileName);
	void _write_to_archive(CArchive & roArchive);

	void _decode_all(bool bUseOldExtensions);
	void _setup_indexing_service();

	CCacheManager * m_poCacheManager;
	CString m_oFullServerPathString;
	CString m_oStorageDirString;
	CString m_oGUIDString;

	CSimpleCriticalSection	m_oAtomCS;		//for use by CItemVariantInfo

	CSimpleCriticalSection	m_oItemInfoCS;
	//{{
		CMap<long,long,SCP<CItemVariantInfo>,SCP<CItemVariantInfo> & > m_oItemVariantInfoMap;	//persistent
		long m_nGenerator;
	//}}
	bool m_bDirty;
	bool m_bBlobDataBase;
};

 
struct CTransactionRecord : public CInterface__
{
	enum eoperationtype		//transaction record operation type
	{
		trot_update,		
		trot_remove
	};
	CTransactionRecord() : 
		m_IdFile(0)
	{
		_init_navostreaminfo(m_oNSI);
	}

	eoperationtype		m_eOperation;		//true - update  false - remove
	long				m_IdFile;
	CString				m_oRawFullServerPathString;
	CArray<BYTE,BYTE&>	m_oDescriptorArray;
	CString				m_oGeneratedFileNameString;
	navostreaminfo		m_oNSI;
};

class CTransactionInfo : public CInterface__
{
public:
	CTransactionInfo()
	{
	}
	void add_operation(SCP<CTransactionRecord> & rpoTranRecSP)
	{
		m_oRecordsArray.Add(rpoTranRecSP);
	}
	bool get_at(long index,SCP<CTransactionRecord> & rpoTranRecSP)
	{
		ASSERT(index >= 0);
		if(index <= m_oRecordsArray.GetUpperBound())
		{
			rpoTranRecSP = m_oRecordsArray[ index ];
			return true;
		}
		return false;
	}
private:
	CArray< SCP<CTransactionRecord>, SCP<CTransactionRecord> & > m_oRecordsArray;	//transaction log
};

class CCacheManager : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CCacheManager)

	CCacheManager();           // protected constructor used by dynamic creation

	BEGIN_INTERFACE_PART(CachedData,ICachedData)
		STDMETHOD(Close)(BYTE bOK);
		STDMETHOD(GetItem)(long IdFile,LPCTSTR lpFullServerPath,
			long DescriptorLength,/*in*/ byte * lpDescriptor,
			IStream ** ppDataStream,
			/*out*/ navostreaminfo * poNSI);
		STDMETHOD(StoreItem)(long IdFile,LPCTSTR lpFullServerPath,
			long DescriptorLength,/*in*/ byte * lpDescriptor,
			long TransactionId,/*in*/ navostreaminfo * poNSI,
			/*out*/IStream ** ppDataStream);
		STDMETHOD(RemoveItem)(long IdFile,LPCTSTR lpFullServerPath,
			long DescriptorLength,/*in*/ byte * lpDescriptor,
			long TransactionId);
		STDMETHOD(BeginTransaction)(long * pTransacionId);
		STDMETHOD(FinishTransaction)(long TransacionId,byte bSuccess);
		STDMETHOD(Purge)(LPCTSTR lpFullServerPath);
		STDMETHOD(GetUniqueIdent)(long * pNewId);
		STDMETHOD(GetCacheInfoGUID)(LPCTSTR lpFullServerPath,GUID * pGUID);
		STDMETHOD(FTSQuery)(LPCTSTR lpFullServerPath,LPCTSTR lpQuery,
			ISimpleEnumId ** ppSimpleEnumFileId);
		STDMETHOD(SetOptions)(long nOptions);
		STDMETHOD(StoreDataObject)(LPCSTR lpFullServerPath,long nTypeId,long nIdObj,long nVersion,
			long nDataLength,BYTE * pData);
		STDMETHOD(RetrieveDataObject)(LPCSTR lpFullServerPath,long nTypeId,long nIdObj,long nVersion,
			long *pDataLength,BYTE ** ppData);
		STDMETHOD(WriteToArchive)(LPCSTR lpFullServerPath,IStream * pDestStream);
		STDMETHOD(ReadFromArchive)(LPCSTR lpFullServerPath,IStream * pSrcStream);
	END_INTERFACE_PART(CachedData)
	
	BEGIN_INTERFACE_PART(PingServer,IPingServer)
		STDMETHOD(Advise)(IUnknown * pPingUnknown,long *pCookie);
		STDMETHOD(UnAdvise)(long nCookie);
	END_INTERFACE_PART(PingServer)
public:
	LPCTSTR _get_root_dir() const
	{
		return m_oRootDirString;
	}
	virtual ~CCacheManager();
	void Close(bool bOK);
	virtual void OnFinalRelease();
	
	void Add2PendingDelete(const CString & roFileNameString)
	{
		m_oPendingDeleteFileArray.Add(roFileNameString);
	}
	//{{AFX_VIRTUAL(CCacheManager)
	//}}AFX_VIRTUAL
protected:

	//{{AFX_MSG(CCacheManager)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CCacheManager)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	//direct iface reflectors
	bool _get_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,
		IStream ** ppDataStream,navostreaminfo * poNSI);
	void _store_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,
		long TransactionId,
		navostreaminfo * poNSI,IStream ** ppDataStream);
	HRESULT _fts_query(LPCTSTR lpFullServerPath,LPCTSTR lpQuery,ISimpleEnumId ** ppSimpleEnumFileId);

	void _remove_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,long TransactionId);
	void _begin_transaction(long * pTransacionId);
	void _finish_transaction(long TransacionId,bool bSuccess);
	void _purge(LPCTSTR lpFullServerPath);
	void _get_unique_ident(long * pNewId);
	bool _get_cacheinfo_guid(LPCTSTR lpFullServerPath,GUID * pGUID);

	void set_options(long nOptions);

	//global state management
	void _get_global_infofile_name(CString & roString);
	void _read_global_info();
	void _write_global_info();

	void _write_all();

	void _pending_delete();

	//single server management
	bool _get_single_server_info(LPCTSTR lpFullServerPath,
		SCP<CSingleServerPlaceCacheInfo> & rpoSSPCISP);

	void trans_get_or_create_server_info(LPCTSTR lpFullServerPath,
		SCP<CSingleServerPlaceCacheInfo> & rpoSSPCISP);

	void _commit_transaction(SCP<CTransactionInfo> & rpoTransactionInfoSP);
	//---------------------------------------------------------------------------
	void _create_backup_archive(LPCTSTR lpFullServerPath,SCP<IStream> poStreamSP);
	void _load_from_backup_archive(LPCTSTR lpFullServerPath,SCP<IStream> poStreamSP);
	//---------------------------------------------------------------------------
	//data structures
	CSimpleCriticalSection	m_oGlobalCS;
	//{{
		CMap<CString,LPCTSTR,SCP<CSingleServerPlaceCacheInfo>,
			SCP<CSingleServerPlaceCacheInfo> &> m_oGlobalMap;	//persistent
		long m_nUniqueIdent;
	//}}

	CSimpleCriticalSection	m_oTransactionCS;
	//{{
		CMap<long,long, SCP<CTransactionInfo>, SCP<CTransactionInfo> &> m_oTransactionMap;
	//}}

	CSimpleCriticalSection	m_oPendDelCS;
	//{{
		CArray<CString,LPCTSTR> m_oPendingDeleteFileArray;
	//}}

	CString		m_oRootDirString;
	//WAN switch
	bool		m_bCompressTrafficToClient;
};

#endif // !defined(AFX_CACHEMANAGER_H__6AE1761E_C76B_4B7C_B291_4C45393137A7__INCLUDED_)
