/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	DataObjectCache
	
	podwójny cache dla obiektów CDataObject
*/

#ifndef _DATAOBJCACHE_H_
#define _DATAOBJCACHE_H_

class CDBAccessProxy;
class CDefinitionManager;
class CNEO_storage;
class CNEO_liststorage;
class CNEO_filestorage;
class CNEO_cursor;
enum eNEO_loadresult;
class CNEO_lockmap;
class CNEO_local_mutex_map;

class CNEO_global_cache: public CCmdTargetInterface
{
public:
	CNEO_global_cache(CDBAccessProxy * poDBAccessProxy,CDefinitionManager * poDefinitionManager);
	void done();
	~CNEO_global_cache();

	//creates new object
	SCP<CNEO_storage> new_object(long nTypeId);
	//loads / reloads existing object, optionally can writelock 
	enum eNEO_loadresult load_object(CNEO_trans * poTrans,long nTypeId,long nIdObj,bool bWriteLock,
		SCP<CNEO_storage> & rpoResultStorageSP,/*out*/bool & rbNeedInit);

	SCP<CNEO_liststorage> new_list(long CollectionId,long IdParent,bool bParentIsNew);
	void load_list(long CollectionId,long IdParent,bool bParentIsNew,SCP<CNEO_liststorage> & rpoResultListStorageSP);

	SCP<CNEO_filestorage> new_file(long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew);
	void load_file(long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew, SCP<CNEO_filestorage> & rpoFileStorageSP);

	void OnNEO_storage_FinalRelease(CNEO_storage * poStorage);
	void OnNEO_liststorage_FinalRelease(CNEO_liststorage * poListStorage);
	void OnNEO_filestorage_FinalRelease(CNEO_filestorage * poFileStorage);

	bool aquire_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra);
	void release_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra);
	void flush_pending_unlocks();

	//-----------------------------------------
	bool aquire_mutex(long nClass,long nTypeId,long nIdObj,long nExtra);
	void release_mutex(long nClass,long nTypeId,long nIdObj,long nExtra);
	//-----------------------------------------
	void purge_local_blob_cache();

	CNEO_storage * _search_RLU_map(long nTypeId,long nIdObj);
	CNEO_liststorage * _search_list_map(long nCollectionId,long nIdParent);
	CNEO_filestorage * _search_file_map(long nParentTypeId,long nParentIdObj,long nOuterFieldNr);

	void _remove_from_RLU_map(CNEO_storage * poStorage);

	BEGIN_INTERFACE_PART(PingClient,IPingClient)		//ping client for navodb
		STDMETHOD(Ping)()
		{
			return S_OK;
		}
	END_INTERFACE_PART(PingClient)
	DECLARE_INTERFACE_MAP()
private:
	void _add_to_RLU_map(CNEO_storage * poStorage);
	void _add_to_list_map(CNEO_liststorage * poListStorage);
	void _add_to_file_map(CNEO_filestorage * poFileStorage);

	void _remove_from_list_map(CNEO_liststorage * poListStorage);
	void _remove_from_file_map(CNEO_filestorage * poFileStorage);

	void _init_blob_cache();

	void _clean_RLU_map();

	CDBAccessProxy *	 m_poDBAccessProxy;		//access to object server
	CDefinitionManager * m_poDefinitionManager;	//access to definitions

	SCP<ICachedData>	m_poLocalBlobCacheSP;
	long				m_nLocalBlobCache_PingCookie;
	CString				m_oLocalBlobFSPString;			//"full server path" string;
	
	CMap<hyper,hyper,CNEO_storage *,CNEO_storage *> m_oRLUStorageMap;		//Recently Last Used Map
	
	CMap<hyper,hyper,CNEO_liststorage *,CNEO_liststorage *> m_oListStorageMap;
	CMap<hyper,hyper,CNEO_filestorage *,CNEO_filestorage *> m_oFileStorageMap;

	CNEO_lockmap * m_poLockMap;
	CNEO_local_mutex_map * m_poMutexMap;

#ifdef _DEBUG
	void ShowStatistics();
	long m_nCacheRequests;
	long m_nObjectWasValidHits;
	long m_nNewObjects;
	long m_nMaxRunningObjects;
#endif

};




#else
	#error __FILE__ already included
#endif
