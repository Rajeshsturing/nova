/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	DataObjectCache
	
	podwójny cache dla obiektów CDataObject i CDataObjectList
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navoscript\CacheManagerUser.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobjcache.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "lockmap.h"
#include "localblobcacheuser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_INTERFACE_MAP(CNEO_global_cache, CCmdTargetInterface)
	INTERFACE_PART(CNEO_global_cache, IID_IPingClient, PingClient)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CNEO_global_cache, PingClient)  


CNEO_global_cache::CNEO_global_cache(CDBAccessProxy * poDBAccessProxy,CDefinitionManager * poDefinitionManager) :
	m_poDBAccessProxy(poDBAccessProxy),
	m_poDefinitionManager(poDefinitionManager),
	m_nLocalBlobCache_PingCookie(0)
{
	ASSERT(poDBAccessProxy);
	ASSERT(m_poDefinitionManager);
	
#ifdef _DEBUG
	m_nCacheRequests = 0;
	m_nObjectWasValidHits = 0;
	m_nNewObjects = 0;
	m_nMaxRunningObjects = 0;
#endif
	EnableAutomation();
	m_oRLUStorageMap.InitHashTable( 2111 );
	m_poLockMap = new CNEO_lockmap();
	m_poMutexMap = new CNEO_local_mutex_map();
}

CNEO_global_cache::~CNEO_global_cache()
{
	done();

	delete m_poLockMap;
	m_poLockMap = NULL;

	delete m_poMutexMap;
	m_poMutexMap = NULL;

	_clean_RLU_map();
	
#ifdef _DEBUG
	ShowStatistics();
#endif
}

void CNEO_global_cache::done()
{
	if(m_poLocalBlobCacheSP.PointsObject())
	{
		UnAdvisePingServer(m_poLocalBlobCacheSP,m_nLocalBlobCache_PingCookie);
		VERIFY(S_OK==m_poLocalBlobCacheSP->Close(BYTE(true)));
		m_poLocalBlobCacheSP = 0;
	}
	m_nLocalBlobCache_PingCookie = 0;
}

const long STDOBJCACHE_SECCACHE = 2000;

SCP<CNEO_storage> CNEO_global_cache::new_object(long nTypeId)
{
	ASSERT(m_poDBAccessProxy);
	long nIdObj = m_poDBAccessProxy->GetUniqueIdent(nTypeId);
	SCP<CNEO_storage> poStorageSP = NewSCP(new CNEO_storage(this,nTypeId,nIdObj,m_poDefinitionManager->GetStdObjDef(nTypeId).Get()));

#ifdef _DEBUG
	m_nNewObjects++;
#endif
	
	_add_to_RLU_map(poStorageSP);

	return poStorageSP;
}

CNEO_storage * CNEO_global_cache::_search_RLU_map(long nTypeId,long nIdObj)
{
	CNEO_storage * poStorage;
	if(m_oRLUStorageMap.Lookup(longlong(nTypeId,nIdObj),poStorage))
	{
		return poStorage;
	}
	else
	{
		return NULL;
	}
}

CNEO_liststorage * CNEO_global_cache::_search_list_map(long nCollectionId,long nIdParent)
{
	CNEO_liststorage * poListStorage;
	if(m_oListStorageMap.Lookup(longlong(nCollectionId,nIdParent),poListStorage))
	{
		return poListStorage;
	}
	else
	{
		return NULL;
	}
}


CNEO_filestorage * CNEO_global_cache::_search_file_map(long nParentTypeId,long nParentIdObj,long nOuterFieldNr)
{
	CNEO_filestorage * poFileStorage;
	if(m_oFileStorageMap.Lookup(longlong(_compose_filemapping_id(nParentTypeId,nOuterFieldNr),nParentIdObj),poFileStorage))
	{
		return poFileStorage;
	}
	else
	{
		return NULL;
	}
}

void CNEO_global_cache::_remove_from_RLU_map(CNEO_storage * poStorage)
{
	ASSERT(poStorage);
	VERIFY(m_oRLUStorageMap.RemoveKey(longlong(poStorage->GetType(),poStorage->GetThis())));
}

void CNEO_global_cache::_remove_from_list_map(CNEO_liststorage * poListStorage)
{
	ASSERT(poListStorage);
	VERIFY(m_oListStorageMap.RemoveKey(longlong(poListStorage->GetCollectionId(),poListStorage->GetParentId())));
}

void CNEO_global_cache::_remove_from_file_map(CNEO_filestorage * poFileStorage)
{
	ASSERT(poFileStorage);
	VERIFY(m_oFileStorageMap.RemoveKey( _compose_filestorage_key(poFileStorage) ));
}

void CNEO_global_cache::_add_to_RLU_map(CNEO_storage * poStorage)
{
	ASSERT(poStorage);
	ASSERT(NULL == _search_RLU_map(poStorage->GetType(),poStorage->GetThis()));

	m_oRLUStorageMap[longlong(poStorage->GetType(),poStorage->GetThis())] = poStorage;

#ifdef _DEBUG
	m_nMaxRunningObjects = max(m_nMaxRunningObjects,m_oRLUStorageMap.GetCount());
#endif
	
}

void CNEO_global_cache::_add_to_list_map(CNEO_liststorage * poListStorage)
{
	ASSERT(poListStorage);
	ASSERT(NULL == _search_list_map(poListStorage->GetCollectionId(),poListStorage->GetParentId()));
	m_oListStorageMap[ longlong(poListStorage->GetCollectionId(),poListStorage->GetParentId()) ] = poListStorage;
}

void CNEO_global_cache::_add_to_file_map(CNEO_filestorage * poFileStorage)
{
	ASSERT(poFileStorage);
	ASSERT(NULL == _search_file_map(poFileStorage->GetParentTypeid(),poFileStorage->GetParentId(),
		poFileStorage->GetOuterFieldNr()));
	m_oFileStorageMap[ _compose_filestorage_key(poFileStorage) ] = poFileStorage;
}

eNEO_loadresult CNEO_global_cache::load_object(CNEO_trans * poTrans,long nTypeId,long nIdObj,bool bWriteLock,
	SCP<CNEO_storage> & rpoResultStorageSP,/*out*/bool & rbNeedInit)
{
#ifdef _DEBUG
	m_nCacheRequests++;
#endif

	ASSERT(nIdObj > 0);
	
	//not found in in-use map -> search RLU or 'writelock' request

	long nVersionNoReturn = -1;
	CNEO_storage * poRLUStorage = _search_RLU_map(nTypeId,nIdObj);
	if(poRLUStorage != NULL)
	{
		nVersionNoReturn = poRLUStorage->GetVersion();
	}

	//check: albo nie by³o albo by³o
	ASSERT((poRLUStorage == NULL && nVersionNoReturn == -1) ||
		   (poRLUStorage != NULL && nVersionNoReturn != -1));


	bool bRemoteWriteLock = false;
	if(bWriteLock)
	{
		bRemoteWriteLock = ! m_poLockMap->_search_write_lock_map(LOCKCLASS_OBJECT,nTypeId,nIdObj,0);
	}
	
	/*
		mo¿liwa optymalizacja:
		pamiêtanie 'wieku' (np. :gettickcount()) obiektu
		i nie pobieranie nowszej wersji czêœciej ni¿ np. 10s
	*/

	//call server
	ASSERT(m_poDBAccessProxy);
	CFlatData oFlatData(0,NULL);
	HRESULT hr = m_poDBAccessProxy->BeginGetObject(nTypeId,nIdObj,nVersionNoReturn,bRemoteWriteLock,oFlatData);
	ASSERT(hr == S_OK || hr == S_FALSE || hr == ERROR_LOCK_FAILED || hr == ERROR_EXE_MACHINE_TYPE_MISMATCH);
	
	if(hr == ERROR_LOCK_FAILED)
	{
		ASSERT(bRemoteWriteLock);		//musia³ byæ ¿¹dany
		ASSERT(rpoResultStorageSP.PointsNull());
		return neolr_locked;
	}
	if(hr == ERROR_EXE_MACHINE_TYPE_MISMATCH)		//skasowany, write lock nie zosta³ za³o¿ony
	{
		ASSERT(rpoResultStorageSP.PointsNull());
		return neolr_not_exists;
	}
	
	if(bWriteLock)
	{
		m_poLockMap->_add_write_lock(LOCKCLASS_OBJECT,nTypeId,nIdObj,0);
	}

	if(hr == S_OK)	//new data delivered
	{
		//sprawdzamy, czy nale¿y zast¹piæ czy stworzyæ nowy
		{
			if(poRLUStorage != NULL)	//replace RLU
			{
				rpoResultStorageSP = NewSCP(poRLUStorage,true);
			}
			else	//create new
			{
				rpoResultStorageSP = NewSCP(new CNEO_storage(this,nTypeId,nIdObj,m_poDefinitionManager->GetStdObjDef(nTypeId).Get()));
				_add_to_RLU_map(rpoResultStorageSP);
			}
			ASSERT(rpoResultStorageSP.PointsObject());
		}
		ASSERT(rpoResultStorageSP.PointsObject());
		rpoResultStorageSP->_readbinary(poTrans,oFlatData);
		m_poDBAccessProxy->EndGetObject(oFlatData);
		
		rbNeedInit = true;	//really read from server

		return neolr_ok_newer;
	}
	else	
	{
#ifdef _DEBUG
		m_nObjectWasValidHits++;
#endif
		//skoro nie ma nowszej wersji - to znaczy ¿e mamy gdzieœ tak¹ sam¹ - 
		//bo inaczej sk¹d wzielibyœmy numer wersji ?

		rbNeedInit = false;

		ASSERT(poRLUStorage != NULL);	
		rpoResultStorageSP = NewSCP(poRLUStorage,true);
		return neolr_ok_current;
	}
}

static long _childtypeid_from_collection_id(long CollectionId,CDefinitionManager * poDefinitionManager,
											SCP<CStdObjDef> & rpoObjectDefinitionSP)
{
	ASSERT(poDefinitionManager);
	long nParentTypeId = _extract_parent_typeid(CollectionId);
	long nParentField = _extract_parent_field(CollectionId);
	rpoObjectDefinitionSP = poDefinitionManager->GetStdObjDef(nParentTypeId);
	SCP<CStdObjFieldDef> & rpoFieldDefSP = rpoObjectDefinitionSP->GetField(nParentField);
	ASSERT(rpoFieldDefSP.PointsObject());
	ASSERT(rpoFieldDefSP->GetRelationType() == RELT_LIST);
	
	long nChildTypeId = rpoFieldDefSP ->GetReferenceTypeId();
	ASSERT(nChildTypeId != 0);
	return nChildTypeId;
}

SCP<CNEO_liststorage> CNEO_global_cache::new_list(long CollectionId,long IdParent,bool bParentIsNew)
{
	SCP<CStdObjDef> poObjectDefinitionSP;
	long nChildTypeId = _childtypeid_from_collection_id(CollectionId,m_poDefinitionManager,poObjectDefinitionSP);
	ASSERT(poObjectDefinitionSP.PointsObject());
	SCP<CNEO_liststorage> poResultListStorageSP = 
		NewSCP(new CNEO_liststorage(this,CollectionId,IdParent,nChildTypeId,bParentIsNew,
			poObjectDefinitionSP.Get()));

	_add_to_list_map(poResultListStorageSP);
	return poResultListStorageSP;
}


void CNEO_global_cache::load_list(long CollectionId,long IdParent,bool bParentIsNew,
								  SCP<CNEO_liststorage> & rpoResultListStorageSP)
{
	CNEO_liststorage * poListStorage = _search_list_map(CollectionId,IdParent);
	if(poListStorage != NULL)
	{
		rpoResultListStorageSP = NewSCP(poListStorage,true);
		return;
	}

	SCP<CStdObjDef> poObjectDefinitionSP;
	long nChildTypeId = _childtypeid_from_collection_id(CollectionId,m_poDefinitionManager,poObjectDefinitionSP);
	ASSERT(poObjectDefinitionSP.PointsObject());
	
	rpoResultListStorageSP = NewSCP(new CNEO_liststorage(this,CollectionId,IdParent,nChildTypeId,
		bParentIsNew,poObjectDefinitionSP.Get()));

	if(!bParentIsNew)
	{
		ASSERT(m_poDBAccessProxy);
		CFlatData oFlatData(0,NULL);
		long nCount = 0;
		m_poDBAccessProxy->ReadListCollection(CollectionId,IdParent,oFlatData,nCount);
		ASSERT(nCount >= 0);
		
		if(nCount > 0)
		{
			rpoResultListStorageSP->_readbinary(oFlatData);
			m_poDBAccessProxy->EndGetObject(oFlatData);
		}
	}
	_add_to_list_map(rpoResultListStorageSP);
}


SCP<CNEO_filestorage> CNEO_global_cache::new_file(long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew)
{
	SCP<CNEO_filestorage> poFileStorageSP = NewSCP(new CNEO_filestorage(this,nParentTypeId,nParentIdObj,nOuterFieldNr,bParentIsNew));
	_add_to_file_map(poFileStorageSP);
	return poFileStorageSP;
}

//---------------------- locking management ----------------------------------------
bool CNEO_global_cache::aquire_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	if(m_poLockMap->_search_write_lock_map(nClass,nTypeId,nIdObj,nExtra))
	{
		return false;
	}

	navolock oNavoLock;
	oNavoLock.m_fullid.m_class	= nClass;
	oNavoLock.m_fullid.m_typeid	= nTypeId; 
	oNavoLock.m_fullid.m_idobj	= nIdObj;
	oNavoLock.m_fullid.m_extra	= nExtra;
	oNavoLock.m_type = nlt_exlock;
	if(!m_poDBAccessProxy->LockItems(&oNavoLock,1,true))
	{
		return false;
	}
	m_poLockMap->_add_write_lock(nClass,nTypeId,nIdObj,nExtra);
	return true;
}

void CNEO_global_cache::release_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	m_poLockMap->release_write_lock(nClass,nTypeId,nIdObj,nExtra);
}

void CNEO_global_cache::flush_pending_unlocks()
{
	if(m_poLockMap->_access_pending_unlocks().GetSize() > 0)
	{
		VERIFY(m_poDBAccessProxy->LockItems(m_poLockMap->_access_pending_unlocks().GetData(),
			m_poLockMap->_access_pending_unlocks().GetSize(),false));
	}
	m_poLockMap->_access_pending_unlocks().RemoveAll();
}
	
//-----------------------------------------
bool CNEO_global_cache::aquire_mutex(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	return m_poMutexMap->try_acquire_mutex(nClass,nTypeId,nIdObj,nExtra);
}

void CNEO_global_cache::release_mutex(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	m_poMutexMap->release_mutex(nClass,nTypeId,nIdObj,nExtra);
}

//----------------------------------------------------------------------------------

void CNEO_global_cache::OnNEO_storage_FinalRelease(CNEO_storage * poStorage)
{
	ASSERT(poStorage);
	ASSERT(_search_RLU_map(poStorage->GetType(),poStorage->GetThis()) == poStorage);

	bool bPutInSecondary = false;

	if(poStorage->IsOld())
	{
		if(!poStorage->GetDefinition()->IsVolatile())
		{
			if(m_oRLUStorageMap.GetCount() < STDOBJCACHE_SECCACHE)
			{
				bPutInSecondary = true;
			}
		}
	}

	if(!bPutInSecondary)
	{
		_remove_from_RLU_map(poStorage);
		delete poStorage;
	}
	else
	{
		ASSERT(poStorage == _search_RLU_map(poStorage->GetType(),poStorage->GetThis()));
	}
}

void CNEO_global_cache::OnNEO_liststorage_FinalRelease(CNEO_liststorage * poListStorage)
{
	_remove_from_list_map(poListStorage);
	delete poListStorage;
}

void CNEO_global_cache::OnNEO_filestorage_FinalRelease(CNEO_filestorage * poFileStorage)
{
	_remove_from_file_map(poFileStorage);
	delete poFileStorage;
}

void CNEO_global_cache::_clean_RLU_map()
{
	POSITION pos = m_oRLUStorageMap.GetStartPosition();
	while(pos)
	{
		hyper hyperDummy;
		CNEO_storage * poStorage = NULL;
		m_oRLUStorageMap.GetNextAssoc(pos,hyperDummy,poStorage);
		ASSERT(poStorage);
		delete poStorage;
	}
}

//----------------------------------------------------------------------------------
// local blob cache support
//----------------------------------------------------------------------------------

void CLocalBlobCacheUser::PrepareDescriptor()
{
	m_oDescriptorArray.SetSize(sizeof(m_nStreamId) + sizeof(m_nVersion));
	PBYTE pcData = m_oDescriptorArray.GetData();
	*(long*)pcData = m_nStreamId; pcData += sizeof(m_nStreamId);
	*(long*)pcData = m_nVersion;		
}

void CNEO_global_cache::_init_blob_cache()
{
	if(m_poLocalBlobCacheSP.PointsObject())
	{
		return;
	}
	ASSERT(m_poDBAccessProxy);
	//prepare "full server path"
	CSmartOleVariant oSQLServerSOV;
	CSmartOleVariant oDBNameSOV;
	CSmartOleVariant oServerUIDSOV;
	m_poDBAccessProxy->GetServerProp(objsrv_server,oSQLServerSOV);
	m_poDBAccessProxy->GetServerProp(objsrv_database,oDBNameSOV);
	m_poDBAccessProxy->GetServerProp(objsrv_mainuid,oServerUIDSOV);

	m_oLocalBlobFSPString = "<offline>:" + CString(oSQLServerSOV.GetBStr()) + ":" + CString(oDBNameSOV.GetBStr());
	CString oServerUIDString = oServerUIDSOV.GetBStr();
	if(!oServerUIDString.IsEmpty())
	{
		m_oLocalBlobFSPString += ":" + oServerUIDString;
	}

	m_poLocalBlobCacheSP.CreateInstance(CLSID_NAVO2001_CacheServer,CLSCTX_ALL);
	m_nLocalBlobCache_PingCookie = AdvisePingServer(GetUnknown(),m_poLocalBlobCacheSP);
	ASSERT(m_nLocalBlobCache_PingCookie != 0);
}

void CNEO_global_cache::purge_local_blob_cache()
{
	_init_blob_cache();
	VERIFY(S_OK == m_poLocalBlobCacheSP->Purge(m_oLocalBlobFSPString));
}

void CNEO_global_cache::load_file(long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew, SCP<CNEO_filestorage> & rpoFileStorageSP)
{
	CNEO_filestorage * poFileStorage = _search_file_map(nParentTypeId,nParentIdObj,nOuterFieldNr);
	if(poFileStorage != NULL)
	{
		rpoFileStorageSP = NewSCP(poFileStorage,true);
	}
	else
	{
		rpoFileStorageSP = NewSCP(new CNEO_filestorage(this,nParentTypeId,nParentIdObj,nOuterFieldNr,bParentIsNew));
		if(!bParentIsNew)
		{
		
			navostreaminfo oNSI;
			_init_navostreaminfo(oNSI);
			long nRemoteVersion = -1;
			long nStreamId = 0;
			SCP<IStream> poRemoteStreamSP = m_poDBAccessProxy->GetDataBaseFile(nParentIdObj,
				_compose_filemapping_id(nParentTypeId,nOuterFieldNr),oNSI,nRemoteVersion,nStreamId);
			
			if(poRemoteStreamSP.PointsObject())	//jest na serwerze
			{
				ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
				if(oNSI.m_bCompressed == '1')
				{
					poRemoteStreamSP = UncompressStream(poRemoteStreamSP);
				}

				//czy jest w cache
				_init_blob_cache();
				SCP<CLocalBlobCacheUser> poLBCUSP = 
					NewSCP(new CLocalBlobCacheUser(m_poLocalBlobCacheSP,m_oLocalBlobFSPString,
					nStreamId,nRemoteVersion,poRemoteStreamSP));
				
				CCacheUserHolder oCUH(poLBCUSP);

				SCP<IStream> poStreamSP = oCUH.get_stream();
				if(poStreamSP.PointsObject())
				{
					rpoFileStorageSP->Attach(poStreamSP);
					rpoFileStorageSP->_set_stream_info(oNSI);
				}
				oCUH.OK();
			}
		}
		_add_to_file_map(rpoFileStorageSP);
	}
}

//----------------------------------------------------------------------------------

#ifdef _DEBUG
void CNEO_global_cache::ShowStatistics()
{
	TRACE0("------global object cache statistics----------\n");
	TRACE1("Total requests: %d\n",m_nCacheRequests);
	TRACE1("New objects created: %d\n",m_nNewObjects);
	TRACE1("Object was valid hits: %d\n",m_nObjectWasValidHits);
	TRACE1("Max running objects: %d\n",m_nMaxRunningObjects);
	TRACE1("Cache valid ratio: %d%%\n",
		(m_nCacheRequests==0) ? 0 : (100*m_nObjectWasValidHits) / (m_nCacheRequests));
}
#endif



















