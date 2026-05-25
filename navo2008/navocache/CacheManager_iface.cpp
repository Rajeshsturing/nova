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

//{{AFX_MSG_MAP(CCacheManager)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CCacheManager, CCmdTargetWithErrorInfo)
	//{{AFX_DISPATCH_MAP(CCacheManager)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {363A7E84-1E76-4632-AA28-674776BAB20A}
static const IID IID_ICacheManager =
{ 0x363a7e84, 0x1e76, 0x4632, { 0xaa, 0x28, 0x67, 0x47, 0x76, 0xba, 0xb2, 0xa } };

BEGIN_INTERFACE_MAP(CCacheManager, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CCacheManager, IID_ICacheManager, Dispatch)
    INTERFACE_PART(CCacheManager, IID_ICachedData, CachedData)
    INTERFACE_PART(CCacheManager, IID_IPingServer, PingServer)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CCacheManager, CachedData)  
DELEGATE_UNKNOWN_INTERFACE(CCacheManager, PingServer)  

// {188cb15c-82a4-4498-87d0-ebd8d9a00fb8}

STDMETHODIMP CCacheManager::XCachedData::Close(BYTE bOK)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		pThis->Close(bOK != '\0');
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::SetOptions(long nOptions)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		pThis->set_options(nOptions);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CCacheManager::XCachedData::StoreDataObject
	(LPCSTR lpFullServerPath,long nTypeId,long nIdObj,long nVersion,long nDataLength,BYTE * pData)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		lpFullServerPath;
		nTypeId;
		nIdObj;
		nVersion;
		nDataLength;
		pData;
		//to_do: zapisywanie obiektów danych w specjalnym storage
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::RetrieveDataObject
	(LPCSTR lpFullServerPath,long nTypeId,long nIdObj,long nVersion,long *pDataLength,BYTE ** ppData)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		lpFullServerPath;
		nTypeId;
		nIdObj;
		nVersion;
		pDataLength;
		ppData;
		//to_do: odczytywanie obiektów danych ze specjalnego storage
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
	GetItem(long IdFile,LPCTSTR lpFullServerPath,
		long DescriptorLength,byte * lpDescriptor,IStream ** ppDataStream,
		/*out*/ navostreaminfo * poNSI)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		*ppDataStream = NULL;
		
		{
			if(!pThis->_get_item(IdFile,lpFullServerPath,DescriptorLength,lpDescriptor,
				ppDataStream,poNSI))
			{
				return S_FALSE;
			}
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
	StoreItem(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,byte * lpDescriptor,
		long TransactionId,
		/*in*/ navostreaminfo * poNSI,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		* ppDataStream = NULL;
		{
			pThis->_store_item(IdFile,lpFullServerPath,DescriptorLength,lpDescriptor,
				TransactionId,poNSI,ppDataStream);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
		RemoveItem(long IdFile,LPCTSTR lpFullServerPath,long DescriptorLength,byte * lpDescriptor,
			long TransactionId)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		pThis->_remove_item(IdFile,lpFullServerPath,DescriptorLength,lpDescriptor,TransactionId);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CCacheManager::XCachedData::BeginTransaction(long * pTransacionId)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		* pTransacionId = 0;
		pThis->_begin_transaction(pTransacionId);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CCacheManager::XCachedData::FinishTransaction(long TransacionId,byte bSuccess)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		pThis->_finish_transaction(TransacionId,bSuccess != '\0');
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::Purge(LPCTSTR lpFullServerPath)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		pThis->_purge(lpFullServerPath);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::GetUniqueIdent(long * pNewId)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		pThis->_get_unique_ident(pNewId);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
	GetCacheInfoGUID(LPCTSTR lpFullServerPath,GUID * pGUID)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		if(!pThis->_get_cacheinfo_guid(lpFullServerPath,pGUID))
		{
			return S_FALSE;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
	FTSQuery(LPCTSTR lpFullServerPath,LPCTSTR lpQuery,ISimpleEnumId ** ppSimpleEnumFileId)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)
	
	ALL_TRY
	{
		return pThis->_fts_query(lpFullServerPath,lpQuery,ppSimpleEnumFileId);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CCacheManager::XCachedData::
	WriteToArchive(LPCSTR lpFullServerPath,IStream * pDestStream)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		SCP<IStream> poStreamSP = NewSCP<IStream>(pDestStream,true);
		pThis->_create_backup_archive(lpFullServerPath,poStreamSP);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XCachedData::
	ReadFromArchive(LPCSTR lpFullServerPath,IStream * pSrcStream)
{
	METHOD_PROLOGUE(CCacheManager, CachedData)

	ALL_TRY
	{
		SCP<IStream> poStreamSP = NewSCP<IStream>(pSrcStream,true);
		pThis->_load_from_backup_archive(lpFullServerPath,poStreamSP);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

//----------------------------------------------------------
//		ping server implementation
//----------------------------------------------------------

STDMETHODIMP CCacheManager::XPingServer::Advise(IUnknown * pPingUnknown,long *pCookie)
{
	METHOD_PROLOGUE(CCacheManager, PingServer)
	
	ALL_TRY
	{
		long nCookie = reinterpret_cast<long>(pPingUnknown);
		_g_CacheManagerServerClassFactory.m_oPingServer.__Advise(pPingUnknown,nCookie);
		*pCookie = nCookie;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCacheManager::XPingServer::UnAdvise(long nCookie)
{
	METHOD_PROLOGUE(CCacheManager, PingServer)
	
	ALL_TRY
	{
		_g_CacheManagerServerClassFactory.m_oPingServer.__UnAdvise(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


