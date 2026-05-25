/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManager - local cache manager, interface part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "CacheManager.h"
#include "srvclassfactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------------
//direct ICachedData interface reflectors
//-----------------------------------------------------------------------------------
bool CCacheManager::_get_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,
							  IStream ** ppDataStream,navostreaminfo * poNSI)
{
	_init_navostreaminfo(*poNSI);
	poNSI->m_bCompressed = '0';
	//find item
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	if(!_get_single_server_info(lpFullServerPath,poSSPCISP))
	{
		return false;
	}
	ASSERT(poSSPCISP.PointsObject());
	SCP<CItemVariantInfo> poItemVariantInfoSP;
	if(!poSSPCISP->get_info(IdFile,poItemVariantInfoSP))
	{
		return false;
	}
	ASSERT(poItemVariantInfoSP.PointsObject());
	SCP<CCacheInfoItem> poCacheInfoItemSP;
	if(!poItemVariantInfoSP->get_info(DescriptorLength,lpDescriptor,poCacheInfoItemSP))
	{
		return false;
	}
	CString oItemFileNameString;
	poCacheInfoItemSP->get_full_path(oItemFileNameString);

	CFileStatus oFileStatus;
	if(!CFile::GetStatus(oItemFileNameString,oFileStatus))
	{
		//file %d stored as %s does not exists
		ThrowNavoException2(ERCO_CACHE_GET_FILE_FAILED, IDPAGE_NOTAVAILABLE, IdFile, oItemFileNameString);
	}

	_copy_navostreaminfo(poItemVariantInfoSP->_get_stream_info(),*poNSI);

	SCP<IStream> poStreamSP = OpenFileStream(oItemFileNameString,
#ifdef _DEVELOPER_EDITION_
		false,
#else
		!poSSPCISP->is_blob_database(),
#endif
		GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,OPEN_EXISTING);

	if(m_bCompressTrafficToClient)
	{
		poNSI->m_bCompressed = '1';
		poStreamSP = CompressStream(poStreamSP);
	}
	else
	{
		poNSI->m_bCompressed = '0';
	}
	* ppDataStream = poStreamSP.Detach();
	return true;
}

void CCacheManager::_store_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,
	long TransactionId,navostreaminfo * poNSI,IStream ** ppDataStream)
{
	//if in transaction - use it, else create your own "pseudo" transaction
	SCP<CTransactionInfo> poTransactionInfoSP;
	if(TransactionId == 0)
	{
		poTransactionInfoSP = NewSCP(new CTransactionInfo());
	}
	else
	{
		CSimpleLock oSimpleLock(m_oTransactionCS);
		if(!m_oTransactionMap.Lookup(TransactionId,poTransactionInfoSP))
		{
			//invalid transaction id
			ThrowNavoException1(ERCO_CACHE_INVALID_TRANS_ID, IDPAGE_NOTAVAILABLE, TransactionId);
		}
	}
	ASSERT(poTransactionInfoSP.PointsObject());
	
	//create new transaction record
	SCP<CTransactionRecord> poTranRecSP = NewSCP(new CTransactionRecord());
	
	//and fill it
	poTranRecSP->m_eOperation = CTransactionRecord::trot_update;
	poTranRecSP->m_IdFile = IdFile;
	poTranRecSP->m_oDescriptorArray.SetSize(DescriptorLength);
	memcpy(poTranRecSP->m_oDescriptorArray.GetData(),lpDescriptor,DescriptorLength);
	poTranRecSP->m_oRawFullServerPathString = lpFullServerPath;
	poTranRecSP->m_oRawFullServerPathString.MakeLower();
	_copy_navostreaminfo(*poNSI,poTranRecSP->m_oNSI);

	//generate file name and open stream
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	{
		CSimpleLock oSimpleLock(m_oGlobalCS);
		trans_get_or_create_server_info(poTranRecSP->m_oRawFullServerPathString,poSSPCISP);
	}
	ASSERT(poSSPCISP.PointsObject());
	CString oPathString;
	poSSPCISP->create_item_full_path(IdFile,oPathString,poTranRecSP->m_oGeneratedFileNameString);
	NavoCreateDirectoryTree(oPathString);
	CString oFullPathString = oPathString + poTranRecSP->m_oGeneratedFileNameString;
	CItemVariantInfo::supply_extension(oFullPathString,poSSPCISP->is_blob_database(),*poNSI);
	
	* ppDataStream = OpenFileStream(oFullPathString,
#ifdef _DEVELOPER_EDITION_
		false,
#else
		!poSSPCISP->is_blob_database(),
#endif
		GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,CREATE_ALWAYS).Detach();

	//add to transaction
	poTransactionInfoSP->add_operation(poTranRecSP);

	if(TransactionId == 0) //if in immediate mode commit
	{
		_commit_transaction(poTransactionInfoSP);
	}
}

void CCacheManager::_remove_item(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,BYTE * lpDescriptor,long TransactionId)
{
	//if in transaction - use it, else create your own "pseudo" transaction
	SCP<CTransactionInfo> poTransactionInfoSP;
	if(TransactionId == 0)
	{
		poTransactionInfoSP = NewSCP(new CTransactionInfo());
	}
	else
	{
		CSimpleLock oSimpleLock(m_oTransactionCS);
		if(!m_oTransactionMap.Lookup(TransactionId,poTransactionInfoSP))
		{
			//invalid transaction id
			ThrowNavoException1(ERCO_CACHE_INVALID_TRANS_ID, IDPAGE_NOTAVAILABLE, TransactionId);
		}
	}
	ASSERT(poTransactionInfoSP.PointsObject());

	//create new transaction record
	SCP<CTransactionRecord> poTranRecSP = NewSCP(new CTransactionRecord());
	
	//and fill it
	poTranRecSP->m_eOperation = CTransactionRecord::trot_remove;
	poTranRecSP->m_IdFile = IdFile;
	poTranRecSP->m_oDescriptorArray.SetSize(DescriptorLength);
	memcpy(poTranRecSP->m_oDescriptorArray.GetData(),lpDescriptor,DescriptorLength);
	poTranRecSP->m_oRawFullServerPathString = lpFullServerPath;
	poTranRecSP->m_oRawFullServerPathString.MakeLower();

	//add to transaction
	poTransactionInfoSP->add_operation(poTranRecSP);

	if(TransactionId == 0) //if in immediate mode commit
	{
		_commit_transaction(poTransactionInfoSP);
	}
}

void CCacheManager::_begin_transaction(long * pTransacionId)
{
	ASSERT(pTransacionId);
	SCP<CTransactionInfo> poTransactionInfoSP = NewSCP(new CTransactionInfo());
	long nTransId = reinterpret_cast<long>(poTransactionInfoSP.Get());
	ASSERT(nTransId != 0);
	
	{
		CSimpleLock oSimpleLock(m_oTransactionCS);
		m_oTransactionMap[ nTransId ] = poTransactionInfoSP;
	}
	* pTransacionId = nTransId;
}

void CCacheManager::_finish_transaction(long TransacionId,bool bSuccess)
{
	SCP<CTransactionInfo> poTransactionInfoSP;
	{
		CSimpleLock oSimpleLock(m_oTransactionCS);
		if(!m_oTransactionMap.Lookup(TransacionId,poTransactionInfoSP))
		{
			//invalid transaction id
			ThrowNavoException1(ERCO_CACHE_INVALID_TRANS_ID, IDPAGE_NOTAVAILABLE, TransacionId);
		}
		VERIFY(m_oTransactionMap.RemoveKey(TransacionId));
	}
	//finish transaction
	if(bSuccess)
	{
		_commit_transaction(poTransactionInfoSP);
	}
	//if not sucess - just drop info
}

void CCacheManager::_purge(LPCTSTR lpFullServerPath)
{
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	if(!_get_single_server_info(lpFullServerPath,poSSPCISP))
	{
		return;	//no such server
	}
	CString oString;
	poSSPCISP->_get_storage_dir(oString);
	CString oFullServerPathString(lpFullServerPath);
	oFullServerPathString.MakeLower();
	CSimpleLock oSimpleLock(m_oGlobalCS);
	VERIFY(m_oGlobalMap.RemoveKey(oFullServerPathString));

	NavoRemoveDirectoryTree(oString);
}

void CCacheManager::_get_unique_ident(long * pNewId)
{
	ASSERT(pNewId);
	CSimpleLock oSimpleLock(m_oGlobalCS);
	
	//AfxMessageBox("cache A=" + Long2String((*pNewId)) + ";" + Long2String(m_nUniqueIdent));
	//--- update internal counter with supplied value
	//--- returned value must not be less
	if((*pNewId) > m_nUniqueIdent)
	{
		m_nUniqueIdent = (*pNewId);
	}
	(*pNewId) = ++m_nUniqueIdent;

	//AfxMessageBox("cache B=" + Long2String((*pNewId)) + ";" + Long2String(m_nUniqueIdent));

	_write_global_info();	//"commits" changes
}

void CCacheManager::set_options(long nOptions)
{
	if(nOptions & UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT)
	{
		m_bCompressTrafficToClient = true;
	}
}

bool CCacheManager::_get_cacheinfo_guid(LPCTSTR lpFullServerPath,GUID * pGUID)
{
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	if(!_get_single_server_info(lpFullServerPath,poSSPCISP))
	{
		return false;
	}
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(poSSPCISP->_get_GUID()),pGUID);
	ASSERT(hr == S_OK);
	return true;
}

HRESULT CCacheManager::_fts_query(LPCTSTR lpFullServerPath,LPCTSTR lpQuery,ISimpleEnumId ** ppSimpleEnumFileId)
{
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	if(!_get_single_server_info(lpFullServerPath,poSSPCISP))
	{
		return S_FALSE;
	}
	
	return poSSPCISP->fts_query(lpQuery,ppSimpleEnumFileId);
}

void CCacheManager::_commit_transaction(SCP<CTransactionInfo> & rpoTransactionInfoSP)
{
	ASSERT(rpoTransactionInfoSP.PointsObject());

	CSimpleLock oSimpleLock(m_oGlobalCS);
	/*
		teraz jest jeden globalny lock na ca³y system, aby nie by³o problemów
		mo¿na po dok³adnej analizie i testach w miarê prosto zwiêkszyæ równoleg³oœæ pracy
		gdy¿ struktury s¹ na to przygotowane
	*/

	CArray<CString,LPCTSTR> oDeleteFileArray;
	//update all info structures
	long iter = 0;
	SCP<CTransactionRecord>  poTranRecSP;
	SCP<CSingleServerPlaceCacheInfo> poLastSSPISP;
	SCP<CSimpleLock> poItemInfoLockSP;
	while(rpoTransactionInfoSP->get_at(iter,poTranRecSP))
	{
		SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
		trans_get_or_create_server_info(poTranRecSP->m_oRawFullServerPathString,poSSPCISP);
		ASSERT(poSSPCISP.PointsObject());
		
		if(poSSPCISP != poLastSSPISP)
		{
			poItemInfoLockSP = 0;	//to zwalnia bez czekania które mo¿e siê zdarzyæ w lockiteminfo
			poItemInfoLockSP = poSSPCISP->LockItemInfo();
			ASSERT(poItemInfoLockSP.PointsObject());
			poLastSSPISP = poSSPCISP;
		}
		//to_do: lock poSSPCISP
		SCP<CItemVariantInfo> poItemVariantInfoSP;
		poSSPCISP->trans_get_or_create_info(poTranRecSP->m_IdFile,poItemVariantInfoSP);
		ASSERT(poItemVariantInfoSP.PointsObject());

		SCP<CCacheInfoItem> poCacheInfoItemSP;
		if(poItemVariantInfoSP->trans_get_or_create_info(
			poTranRecSP->m_oDescriptorArray.GetSize(),
			poTranRecSP->m_oDescriptorArray.GetData(),poCacheInfoItemSP))
		{
			ASSERT(poCacheInfoItemSP.PointsObject());
			CString oDeleteFileNameString; 
			poCacheInfoItemSP->get_full_path(oDeleteFileNameString);
#ifdef _DEBUG
			{
				if(poTranRecSP->m_eOperation == CTransactionRecord::trot_update)
				{
					//powinien byæ inny
					ASSERT( poTranRecSP->m_oGeneratedFileNameString.CompareNoCase(poCacheInfoItemSP->get_file_name()) );
				}
			}
#endif
			if(!NavoDeleteFile(oDeleteFileNameString))
			{
				oDeleteFileArray.Add(oDeleteFileNameString);
			}
		}
		else
		{
			ASSERT(poCacheInfoItemSP.PointsObject());
			ASSERT(poTranRecSP->m_eOperation == CTransactionRecord::trot_update);
		}
		if(poTranRecSP->m_eOperation == CTransactionRecord::trot_update)
		{
			ASSERT(poCacheInfoItemSP.PointsObject());
			poCacheInfoItemSP->_set_file_name(poTranRecSP->m_oGeneratedFileNameString);
			poItemVariantInfoSP->_set_stream_info(poTranRecSP->m_oNSI);
			poSSPCISP->set_dirty();
		}
		else
		{
			//remove from info
			VERIFY(poItemVariantInfoSP->trans_remove(
				poTranRecSP->m_oDescriptorArray.GetSize(),
				poTranRecSP->m_oDescriptorArray.GetData()));
			
			if(poItemVariantInfoSP->is_empty())
			{
				poSSPCISP->trans_remove(poTranRecSP->m_IdFile);
			}
		}
		iter++;
	}
	
	poItemInfoLockSP = 0;

	if(oDeleteFileArray.GetSize() > 0)
	{
		CSimpleLock oSimpleLock(m_oPendDelCS);
		m_oPendingDeleteFileArray.Append(oDeleteFileArray);
	}
	//save all structures
	_write_all();

}

//----------------------------------------------------------------------------
// backup and restore
//----------------------------------------------------------------------------

void CCacheManager::_create_backup_archive(LPCTSTR lpFullServerPath,SCP<IStream> poStreamSP)
{
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	if(!_get_single_server_info(lpFullServerPath,poSSPCISP))
	{
		return;
	}
	ASSERT(poSSPCISP.PointsObject());

	poSSPCISP->write_to_backup_archive(poStreamSP);
}

void CCacheManager::_load_from_backup_archive(LPCTSTR lpFullServerPath,SCP<IStream> poStreamSP)
{
	//generate file name and open stream
	SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
	{
		CSimpleLock oSimpleLock(m_oGlobalCS);
		trans_get_or_create_server_info(lpFullServerPath,poSSPCISP);
	}

	ASSERT(poSSPCISP.PointsObject());
	
	poSSPCISP->load_from_backup_archive(poStreamSP);

	//save all structures
	_write_all();
}

