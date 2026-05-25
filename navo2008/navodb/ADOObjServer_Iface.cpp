/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	Object Server (on ADO)
*/

#include "stdafx.h"
#include "navodb.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\navodef\stdobjdef.h"
#include "..\include\flatdata.h"	//flat data transport
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\DefinitionManager.h"
#include "ADOObjServer.h"
#include "NAVODB_Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOP_ALL_CATCH_DB(__a__, _to_return_) \
	ALL_CATCH(const CNavoException & roNavoException)\
	{\
		(__a__) += (roNavoException);\
		pThis->_get_ADO_errors((__a__));\
		return (_to_return_);\
	};

IMPLEMENT_DYNCREATE(CADOObjServer, CCmdTargetInterface)

BEGIN_DISPATCH_MAP(CADOObjServer, CCmdTargetWithErrorInfo)
	//{{AFX_DISPATCH_MAP(CADOObjServer)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {C910854A-6FA2-4800-895A-61A8431F3E75}
static const IID IID_IODBCObjServer =
{ 0xc910854a, 0x6fa2, 0x4800, { 0x89, 0x5a, 0x61, 0xa8, 0x43, 0x1f, 0x3e, 0x75 } };

BEGIN_INTERFACE_MAP(CADOObjServer, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CADOObjServer, IID_IPingClient, PingClient)
	INTERFACE_PART(CADOObjServer, IID_IObjectServer, ObjectServer)
	INTERFACE_PART(CADOObjServer, IID_IODBCObjServer, Dispatch)
	INTERFACE_PART(CADOObjServer, IID_IObjectServerExtensionHost, ObjectServerExtensionHost)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CADOObjServer, ObjectServer)
DELEGATE_UNKNOWN_INTERFACE(CADOObjServer, PingClient)
DELEGATE_UNKNOWN_INTERFACE(CADOObjServer, ObjectServerExtensionHost)

// {188cb160-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CADOObjServer, "navodb.objectserver", 0x188cb160, 0x82a4, 0x4498, 0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)


/////////////////////////////////////////////////////////////////////////////
// CADOObjServer interface implementation

STDMETHODIMP CADOObjServer::XObjectServer::
SetCoManagers(LPCSTR pcAppName, ILockManager* pLockManager, long nLockManCookie, long nOptions)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->m_poCachedDataSP.CreateInstance(CLSID_NAVO2001_CacheServer, CLSCTX_ALL);
		pThis->m_nCachedData_PingCookie = AdvisePingServer(pThis->GetUnknown(), pThis->m_poCachedDataSP);
		ASSERT(pThis->m_nCachedData_PingCookie);

		pThis->m_poDefinitionManagerSP = theApp.m_poDefinitionManProvSP->_get_definition(pcAppName);
		pThis->m_poLockManagerSP = NewSCP(pLockManager, true);
		pThis->m_nLockManCookie = nLockManCookie;
		if (nOptions & UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT)
		{
			pThis->m_bCompressTrafficToClient = true;
			pThis->m_poCachedDataSP->SetOptions(UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT);
		}
		//pozosta³oœci 
		pThis->m_poNotificationManagerSP = SCP<INotificationManager>();
		pThis->m_nNotifyManCookie = 0;

	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
Close(BYTE bOK)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->_clean_up();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
MakeTransaction_Stream(IStream* pStream,
	long IdParent,
	long IdMapping,
	navostreaminfo NSI)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

	{
		if (pThis->m_poCurrentTHSP.PointsNull())
		{
			pThis->m_poCurrentTHSP = NewSCP(new CTransactionHolder(*pThis));
		}

		ASSERT(pThis->m_poCurrentTHSP.PointsObject());

		if (pStream != NULL)
		{
			pThis->StoreFile(IdParent, IdMapping, NewSCP<IStream>(pStream, true), &NSI);
		}
		else
		{
			pThis->RemoveFile(IdParent, IdMapping);
		}
	}

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
MakeTransaction2(SAFEARRAY** pBinaryData, long iLockCount, BYTE bCommit, LPCSTR lpExtras, LPSTR* ppResult)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

	{
		//dobry zwyczaj zeruj outpointery
		*ppResult = NULL;

		CString strResult = "+";

		*ppResult = (LPTSTR) ::NdrOleAllocate(strResult.GetLength() + 1);

		strcpy((LPTSTR)*ppResult, strResult);

		long nDataLength = 0;
		void* _pBinaryData = 0;

		if (pBinaryData)
		{
			SafeArrayAccessData(*pBinaryData, &_pBinaryData);
			SafeArrayGetUBound(*pBinaryData, 1, &nDataLength);
			nDataLength++;
		}

		HRESULT hr = MakeTransaction(nDataLength, (byte*)_pBinaryData, 0, NULL, iLockCount, pThis->m_arrLocks, bCommit);

		if (pBinaryData)
		{
			SafeArrayUnaccessData(*pBinaryData);
		}
	}

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
MakeTransaction(long nDataLength, byte* lpBinaryData,
	long nBlobInfoCount, transblobinfo* pBlobInfo,
	long nWriteLockCount, const navolock* pNavoLock,
	BYTE bCommit)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->MakeTransaction(nDataLength, lpBinaryData, nBlobInfoCount, pBlobInfo,
			nWriteLockCount, pNavoLock, bCommit != '\0');
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}


STDMETHODIMP CADOObjServer::XObjectServer::FinishTransaction(BYTE bSuccess)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->FinishTransaction(bSuccess != '\0');
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

class CWriteLockSingleObjectHolder
{
public:
	CWriteLockSingleObjectHolder(long nTypeId, long nIdObj, CADOObjServer* poADOObjServer) :
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj),
		m_poADOObjServer(poADOObjServer),
		m_bLockSuccessfull(false)
	{
		ASSERT(m_poADOObjServer);
	}
	bool Lock()
	{
		ASSERT(m_poADOObjServer);
		m_bLockSuccessfull = m_poADOObjServer->LockSingleObject(m_nTypeId, m_nIdObj, false, true);
		return m_bLockSuccessfull;
	}
	void ReleaseHolder()
	{
		m_poADOObjServer = NULL;	//means ok and dtor will not unlock
	}
	~CWriteLockSingleObjectHolder()
	{
		if (m_bLockSuccessfull && m_poADOObjServer != NULL)
		{
			m_poADOObjServer->LockSingleObject(m_nTypeId, m_nIdObj, false, false);
		}
	}
private:
	bool	m_bLockSuccessfull;
	long	m_nTypeId;
	long	m_nIdObj;
	CADOObjServer* m_poADOObjServer;
};

STDMETHODIMP CADOObjServer::XObjectServer::
GetObjectIfNewer2(long TypeId, long IdObj, long VersionNoReturn, BYTE bWriteLock,
	long* pDataLength, SAFEARRAY** pSABinData,
	/* [out] */ long* pHR)
{
	byte* pBinaryData;
	HRESULT hr = GetObjectIfNewer(TypeId, IdObj, VersionNoReturn, bWriteLock, pDataLength, &pBinaryData);

	if (hr == S_OK)
	{
		*pSABinData = SafeArrayCreateVector(VT_UI1, 0, *pDataLength);
		void* pSafeArrayData;
		SafeArrayAccessData(*pSABinData, &pSafeArrayData);
		memcpy(pSafeArrayData, pBinaryData, *pDataLength);
		SafeArrayUnaccessData(*pSABinData);
		NdrOleFree(pBinaryData);
	}

	*pHR = hr;

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
GetObjectIfNewer(long TypeId, long IdObj, long VersionNoReturn, BYTE bWriteLock,
	long* pDataLength, byte** lpBinaryData)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)
		/*
			return S_OK; when function sucessed, else error
			* pDataLength = 0 where no newer version else real data length
		*/
		ALL_TRY
	{
		*pDataLength = 0;
		*lpBinaryData = NULL;

		ASSERT(IdObj);
		CWriteLockSingleObjectHolder oWLSOH(TypeId, IdObj, pThis);

		if (bWriteLock)
		{
			if (!oWLSOH.Lock())
			{
				return ERROR_LOCK_FAILED;
			}
		}

		SCP<CFlatData> poFlatDataSP;
		ASSERT(pThis->m_poFDObjectCacheSP.PointsObject());
		if (!pThis->m_poFDObjectCacheSP->Get(TypeId, IdObj, poFlatDataSP))
		{
			CFlatData* poFlatData;
			if (pThis->GetObject(TypeId, IdObj, &poFlatData))
			{
				//must already be in cache
#ifdef _DEBUG
				{
					if (!pThis->m_poFDObjectCacheSP->_is_disabled())
					{
						SCP<CStdObjDef> poStdObjDefSP = pThis->m_poDefinitionManagerSP->GetStdObjDef(TypeId);
						ASSERT(poStdObjDefSP);
						if (!poStdObjDefSP->IsVolatile() && poStdObjDefSP->IsCacheOnServer())
						{
							SCP<CFlatData> poTestFlatDataSP;
							CSimpleLock oSimpleLock(pThis->m_poFDObjectCacheSP->CriticalSection());
							ASSERT(pThis->m_poFDObjectCacheSP->Get(TypeId, IdObj, poTestFlatDataSP));
						}
					}
				}
#endif
				CFlatData::CFDHeader oFDHeader(*poFlatData);
				if (oFDHeader.VersionId() > VersionNoReturn)		//send only newer
				{
					RPCCopy(poFlatData->GetDataPtr(), poFlatData->GetDataLen(), pDataLength, lpBinaryData);
				}
				delete poFlatData;
			}
			else
			{
				//zwracamy taki dziwny kod b³êdu jako znak rozpoznawczy
				//¿e nie mo¿na pobraæ rekordu (zosta³ np. skasowany o takim id)
				ASSERT(poFlatData == NULL);
				return ERROR_EXE_MACHINE_TYPE_MISMATCH;
			}
		}
		else
		{
			ASSERT(poFlatDataSP.PointsObject());
			CFlatData::CFDHeader oFDHeader(*poFlatDataSP);
			if (oFDHeader.VersionId() > VersionNoReturn)		//send only newer
			{
				RPCCopy(poFlatDataSP->GetDataPtr(), poFlatDataSP->GetDataLen(), pDataLength, lpBinaryData);
			}
		}

		oWLSOH.ReleaseHolder();
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
GetUniqueIdent(long TypeId, long* pNewId)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pNewId = -1;
		pThis->GetMaxIdObj(TypeId, *pNewId);
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
FindOnField(long nTypeId, LPCTSTR lpWhereClause, long* pFoundId)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->Find(nTypeId, lpWhereClause, *pFoundId);
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
OpenOnStatement(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause,
	LPCTSTR lpJoinClause, BYTE bForwardOnly, long nTop, INAVOObjectCollection** pCollection)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pCollection = NULL;
		SCP<CObjectCollectionImpl> poObjectCollectionImplSP =
			NewSCP(new CObjectCollectionImpl(pThis));
		poObjectCollectionImplSP->OpenOnStatement(TypeId, lpWhereClause, lpOrderByClause, lpJoinClause, boolean(bForwardOnly) != '\0', nTop);

		SCP<INAVOObjectCollection> pICollectionSP;
		pICollectionSP.QueryInterface(poObjectCollectionImplSP);
		*pCollection = pICollectionSP.Detach();
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
OpenCollection(long CollectionId, long  IdParent, long* pTotalCount,
	INAVOObjectCollection** pCollection)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pCollection = NULL;
		SCP<CObjectCollectionImpl> poObjectCollectionImplSP =
			NewSCP(new CObjectCollectionImpl(pThis));
		poObjectCollectionImplSP->OpenCollection(CollectionId, IdParent, pTotalCount);

		SCP<INAVOObjectCollection> pICollectionSP;
		pICollectionSP.QueryInterface(poObjectCollectionImplSP);
		*pCollection = pICollectionSP.Detach();
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
OpenFTSQuery(long  IdMapping, LPCSTR lpQuery, INAVOObjectCollection** pCollection)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pCollection = NULL;
		SCP<CObjectCollectionImpl> poObjectCollImplSP = pThis->MakeFTSQuery(IdMapping, lpQuery);
		if (poObjectCollImplSP.PointsObject())
		{
			SCP<INAVOObjectCollection> pICollectionSP;
			pICollectionSP.QueryInterface(poObjectCollImplSP);
			*pCollection = pICollectionSP.Detach();
		}
		else
		{
			return S_FALSE;
		}
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
OpenDiscoRecSet(LPCTSTR lpSQLClause, IStream** pADORecordsetStream, navostreaminfo* poNSI)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pADORecordsetStream = NULL;		//in case of exception
		ADODB::_RecordsetPtr poRecordsetPtr = pThis->OpenDiscoRecSet(lpSQLClause);

		if (poRecordsetPtr->State == ADODB::adStateClosed)
		{
			return S_FALSE;
		}

		bool bEmpty = (poRecordsetPtr->BOF || poRecordsetPtr->EOF);

		ADODB::_StreamPtr poStreamPtr;
		poStreamPtr.CreateInstance(_T("ADODB.Stream"));
		poRecordsetPtr->Save(_variant_t((IDispatch*)poStreamPtr, true), ADODB::adPersistXML);
		poRecordsetPtr->Close();

		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(poStreamPtr);

		if (pThis->m_bCompressTrafficToClient)
		{
			poNSI->m_bCompressed = '1';
			poStreamSP = CompressStream(poStreamSP);
		}
		else
		{
			poNSI->m_bCompressed = '0';
		}

		*pADORecordsetStream = poStreamSP.Detach();

		return bEmpty ? S_FALSE : S_OK;
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}

STDMETHODIMP CADOObjServer::XObjectServer::
OpenDiscoRecSet2(LPCTSTR lpSQLClause, IUnknown** pADORecordset)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pADORecordset = NULL;		//in case of exception
		ADODB::_RecordsetPtr poRecordsetPtr = pThis->OpenDiscoRecSet(lpSQLClause);

		SCP<IUnknown> poRecordsetSP;
		poRecordsetSP.QueryInterface(poRecordsetPtr);
		*pADORecordset = poRecordsetSP.Detach();
	}

	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
CreateADOCommand(IUnknown** pADOCommand)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pADOCommand = NULL;		//in case of exception
		ADODB::_CommandPtr poCommandPtr;
		poCommandPtr.CreateInstance("ADODB.Command");
		poCommandPtr->ActiveConnection = pThis->m_poConnectionPtr;
		poCommandPtr->CommandTimeout = 60 * 60;

		SCP<IUnknown> poCommandSP;
		poCommandSP.QueryInterface(poCommandPtr);

		*pADOCommand = poCommandSP.Detach();
	}

	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
CreateADOParameter(IUnknown** pADOParameter)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pADOParameter = NULL;		//in case of exception
		ADODB::_ParameterPtr poParameterPtr;
		poParameterPtr.CreateInstance("ADODB.Parameter");

		SCP<IUnknown> poParameterSP;
		poParameterSP.QueryInterface(poParameterPtr);

		*pADOParameter = poParameterSP.Detach();
	}

	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
Lock_AddItem(long iInx, long iClass, long iTypeid, long iIdObj, long iExtra, long iLockType)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		navolock & rLock = pThis->m_arrLocks[iInx];

		rLock.m_fullid.m_class = iClass;
		rLock.m_fullid.m_typeid = iTypeid;
		rLock.m_fullid.m_idobj = iIdObj;
		rLock.m_fullid.m_extra = iExtra;
		rLock.m_type = (navolocktype)iLockType;
	}

	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::PurgeCache()
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		pThis->purge_cache();
	}

	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}


LPCTSTR ProcedureSuffixOnAction(stdobjactions Action);

STDMETHODIMP CADOObjServer::XObjectServer::
CanDelete(long nTypeId, long IdObj, IDispatch** pADORecordset)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pADORecordset = NULL;
		SCP<CStdObjDef> poStdObjDefSP = pThis->m_poDefinitionManagerSP->GetStdObjDef(nTypeId);
		CString oSQLString = poStdObjDefSP->GetTableName() +
			ProcedureSuffixOnAction(action_candel) + CString(" ") + Long2String(IdObj);
		ADODB::_RecordsetPtr poRecordsetPtr = pThis->OpenDiscoRecSet(oSQLString);

		if (poRecordsetPtr->State == ADODB::adStateClosed)
		{
			return S_OK;
		}
		if (poRecordsetPtr->BOF || poRecordsetPtr->EOF)
		{
			return S_OK;		//yes, you can delete
		}
		SCP<IDispatch> poDispatchSP;
		poDispatchSP.QueryInterface(poRecordsetPtr);
		*pADORecordset = poDispatchSP.Detach();
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_FALSE;	//not, you cannot
}

STDMETHODIMP CADOObjServer::XObjectServer::
SetProp(objsrv_prop nProp, VARIANT vValue)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		CSmartOleVariant oSOV(vValue);
		switch (nProp)
		{
		case objsrv_server:
			pThis->m_oEffectiveServerString = oSOV.GetBStr();
			break;
		case objsrv_database:
			pThis->m_oDBString = oSOV.GetBStr();
			break;
		case objsrv_user:
			pThis->m_oUserString = oSOV.GetBStr();
			break;
		case objsrv_password:
			pThis->m_oPwdString = oSOV.GetBStr();
			break;
		case objsrv_enginetype:
			pThis->m_EngineType = dbenginetype(oSOV.GetLong());
			break;
		case objsrv_mainuid:
			//nie wolno ustawiaæ !!!
		default:
			ASSERT(false);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
GetProp(objsrv_prop nProp, VARIANT* pvValue)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		CSmartOleVariant oSOV;
		switch (nProp)
		{
		case objsrv_server:
			oSOV = pThis->m_oEffectiveServerString;
			break;
		case objsrv_database:
			oSOV = pThis->m_oDBString;
			break;
		case objsrv_user:
			oSOV = pThis->m_oUserString;
			break;
		case objsrv_password:
			oSOV = pThis->m_oPwdString;
			break;
		case objsrv_enginetype:
			oSOV = long(pThis->m_EngineType);
			break;
		case objsrv_mainuid:
			oSOV = theApp.m_oMainUIDString;
			break;
		default:
			ASSERT(false);
		}
		*pvValue = oSOV.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CADOObjServer::XObjectServer::
ExecSQL(LPCTSTR lpSQLCommand, long* pRecordsAffected)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pRecordsAffected = pThis->ExecSQL(lpSQLCommand);
	}
	TOP_ALL_CATCH_DB(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
SetSharedVariable(long nOriginatorCookie, long lVarNr, VARIANT nNewValue)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		CSmartOleVariant oSOV(nNewValue);
		ASSERT(pThis->m_poFDObjectCacheSP.PointsObject());
		pThis->m_poFDObjectCacheSP->SetSharedVar(lVarNr, oSOV);
		if (nOriginatorCookie != 0)
		{
			// m_poNotificationManagerSP nie jest pod³¹czany !!!
			// pThis->m_poNotificationManagerSP->NotifySharedVariableChange(nOriginatorCookie,lVarNr,nNewValue);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
GetSharedVariable(long lVarNr, VARIANT* pvValue)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		CSmartOleVariant oSOV;
		ASSERT(pThis->m_poFDObjectCacheSP.PointsObject());
		bool bVarExists = pThis->m_poFDObjectCacheSP->GetSharedVar(lVarNr, oSOV);
		if (!bVarExists)
		{
			return S_FALSE;
		}
		*pvValue = oSOV.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::GetStream(long IdParent, long IdMapping,
	IStream** pStream, navostreaminfo* poNSI, long* pVersion, long* pStreamId)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pStream = NULL;		//dobre maniery zeruj¹ outpointery
		*pVersion = -1;
		*pStreamId = 0;
		*pStream = pThis->GetFile(IdParent, IdMapping, poNSI, pVersion, pStreamId).Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
CreateExtension(LPCSTR lpExtensionProgId, IDispatch** pExtensionDisp)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		*pExtensionDisp = NULL;

		CLSID oCLSID;
		HRESULT hr = ::CLSIDFromProgID(CBStr(lpExtensionProgId), &oCLSID);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		SCP<IDispatch> poDispatchSP;
		poDispatchSP.CreateInstance(oCLSID, CLSCTX_ALL);
		SCP<IObjectServerExtension> poObjectServerExtSP;
		poObjectServerExtSP.QueryInterface(poDispatchSP);
		hr = poObjectServerExtSP->Init(&pThis->m_xObjectServerExtensionHost);
		if (hr != S_OK)
		{
			return hr;
		}

		*pExtensionDisp = poDispatchSP.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

static CString encode_arch_pwd(LPCSTR lpArchPwd)
{
	CString oEncString;
	int nVal = 1;
	for (LPCSTR lpPtr = lpArchPwd; *lpPtr != '\0'; lpPtr++)
	{
		oEncString += (char)(((*lpPtr) + nVal));
		nVal = -nVal;
	}
	return oEncString;
}

static CString decode_arch_pwd(LPCSTR lpArchPwd)
{
	CString oEncString;
	int nVal = -1;
	for (LPCSTR lpPtr = lpArchPwd; *lpPtr != '\0'; lpPtr++)
	{
		oEncString += (char)(((*lpPtr) + nVal));
		nVal = -nVal;
	}
	return oEncString;
}

const char* _g_lpArchiveMarker = "NAVO2002ARCH";
const char* _g_lpArchiveMarker2008 = "NAVO2008ARCH";

STDMETHODIMP CADOObjServer::XObjectServer::
WriteToArchive(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream* pDestStream)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		SCP<IStream> poStreamSP = NewSCP(pDestStream, true);

	//write header and Archive Password
	{
		CStreamHolder oSH(poStreamSP);
		//write new signature to prevent old code to read new backup
		oSH.WritePascalString(_g_lpArchiveMarker2008);
		oSH.WritePascalString(encode_arch_pwd(lpArchivePwd));

		ASSERT(strcmp(decode_arch_pwd(encode_arch_pwd(lpArchivePwd)), lpArchivePwd) == 0);
	}

	//backup database
	HRESULT hr = pThis->_backup_database(lpSAUser, lpPwd, poStreamSP);
	if (hr != S_OK)
	{
		return hr;
	}

	//backup files (blobs)
	ASSERT(pThis->m_poCachedDataSP.PointsObject());
	CString oPseudoServerString;
	pThis->ComposeCacheName(oPseudoServerString);
	pThis->CheckFileCacheGUID(true, oPseudoServerString);
	return pThis->m_poCachedDataSP->WriteToArchive(oPseudoServerString, poStreamSP.Get());
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServer::
ReadFromArchive(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream* pSrcStream)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServer)

		ALL_TRY
	{
		SCP<IStream> poSrcStreamSP = NewSCP<IStream>(pSrcStream, true);

	//read header and Archive Password
	{
		CStreamHolder oSH(poSrcStreamSP);
		CString oSignatureString = oSH.ReadPascalString();

		//we accept both signatures
		if (oSignatureString != _g_lpArchiveMarker2008 &&
			oSignatureString != _g_lpArchiveMarker)
		{
			return NTE_BAD_SIGNATURE;
		}
		if (strcmp(decode_arch_pwd(oSH.ReadPascalString()), lpArchivePwd) != 0)
		{
			return ERROR_INVALID_PASSWORD;
		}
	}

	pThis->_update_effective_server();

	ASSERT(pThis->m_poCachedDataSP.PointsObject());
	CString oPseudoServerString;
	pThis->ComposeCacheName(oPseudoServerString);
	//restore database 
	HRESULT hr = pThis->_restore_database(lpSAUser, lpPwd, oPseudoServerString, poSrcStreamSP);
	if (hr != S_OK)
	{
		return hr;
	}

	//restore files (blobs)
	//pThis->CheckFileCacheGUID(false,oPseudoServerString);

	hr = pThis->m_poCachedDataSP->ReadFromArchive(oPseudoServerString, poSrcStreamSP);

	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
STDMETHODIMP CADOObjServer::XObjectServerExtensionHost::
GetDBConnection(IUnknown** ppDBConnection)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServerExtensionHost)

		ALL_TRY
	{
		*ppDBConnection = NULL;

		pThis->Login(false);
		SCP<IUnknown> poConnectionUnknownSP;
		poConnectionUnknownSP.QueryInterface(pThis->m_poConnectionPtr);
		*ppDBConnection = poConnectionUnknownSP.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}
//STDMETHODIMP CADOObjServer::XObjectServerExtensionHost::
//GetStoreHub(IDispatch ** ppNX)
//{
//	METHOD_PROLOGUE(CADOObjServer, ObjectServerExtensionHost)
//
//		ALL_TRY
//	{
//		*ppNX = NULL;
//
//		SCP<IDispatch> poDispatchSP = _g_poNAVODB_Global->_get_StoreHub_dispatch();
//
//		*ppNX = poDispatchSP.Detach();
//	}
//	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
//	return S_OK;
//}
STDMETHODIMP CADOObjServer::XObjectServerExtensionHost::
Lock(navolock oNavoLock)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServerExtensionHost)

		ALL_TRY
	{
		ASSERT(pThis->m_poLockManagerSP.PointsObject());

		HRESULT hr = pThis->m_poLockManagerSP->Lock(pThis->m_nLockManCookie, BYTE(true), 1, &oNavoLock);
		if (hr != S_OK && hr != S_FALSE)
		{
			//error
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CADOObjServer::XObjectServerExtensionHost::
UnLock(navolock oNavoLock)
{
	METHOD_PROLOGUE(CADOObjServer, ObjectServerExtensionHost)

		ALL_TRY
	{
		ASSERT(pThis->m_poLockManagerSP.PointsObject());

		HRESULT hr = pThis->m_poLockManagerSP->Lock(pThis->m_nLockManCookie, BYTE(false), 1, &oNavoLock);
		if (hr != S_OK && hr != S_FALSE)
		{
			//error
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

//-----------------------------------------------------------
//-----------------------------------------------------------

STDMETHODIMP CObjectCollectionImpl::XNAVOObjectCollection::Fetch2(fetchdirection FetchDirection,
	long* nCount, long* pDataLength, SAFEARRAY** pSABinData, long nAbsolutePosition)
{
	byte* pBinaryData;
	HRESULT hr = Fetch(FetchDirection, nCount, pDataLength, &pBinaryData, nAbsolutePosition);

	*pSABinData = SafeArrayCreateVector(VT_UI1, 0, *pDataLength);
	void* pSafeArrayData;
	SafeArrayAccessData(*pSABinData, &pSafeArrayData);
	memcpy(pSafeArrayData, pBinaryData, *pDataLength);
	SafeArrayUnaccessData(*pSABinData);
	NdrOleFree(pBinaryData);

	return hr;
}

STDMETHODIMP CObjectCollectionImpl::XNAVOObjectCollection::Fetch(
	fetchdirection	FetchDirection, long* pnCount, long* pDataLength,
	byte** lpBinaryData, long nAbsolutePosition)
{
	METHOD_PROLOGUE(CObjectCollectionImpl, NAVOObjectCollection)

		ALL_TRY
	{
		*pDataLength = 0;
		*lpBinaryData = NULL;
		CFlatData* poFlatData;
		*pnCount = pThis->m_poObjectServer->GetIdentsOnStmt(pThis->m_poRecordsetPtr,
			FetchDirection, *pnCount, &poFlatData, nAbsolutePosition);
		if (*pnCount)
		{
			RPCCopy(poFlatData->GetDataPtr(), poFlatData->GetDataLen(), pDataLength, lpBinaryData);
			delete poFlatData;
		}
	}
	TOP_ALL_CATCH(pThis->m_poObjectServer->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CObjectCollectionImpl::XNAVOObjectCollection::GetCount(
	long* pnCount)
{
	METHOD_PROLOGUE(CObjectCollectionImpl, NAVOObjectCollection)

		ALL_TRY
	{
		*pnCount = -1;
		if (pThis->m_nTotalCount == -1) //unknown yet
		{
			pThis->m_nTotalCount = pThis->m_poRecordsetPtr->GetRecordCount();
		}
		*pnCount = pThis->m_nTotalCount;
	}
	TOP_ALL_CATCH(pThis->m_poObjectServer->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CObjectCollectionImpl::XNAVOObjectCollection::Refresh(long nPositionToKeep, long* pnCount)
{
	METHOD_PROLOGUE(CObjectCollectionImpl, NAVOObjectCollection)

		ALL_TRY
	{
		if (pThis->_requery(nPositionToKeep, pnCount))
		{
			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	TOP_ALL_CATCH(pThis->m_poObjectServer->GetErrorStorage(), DISP_E_EXCEPTION);
}

BEGIN_INTERFACE_MAP(CObjectCollectionImpl, CCmdTargetInterface)
	INTERFACE_PART(CObjectCollectionImpl, IID_INAVOObjectCollection, NAVOObjectCollection)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CObjectCollectionImpl, NAVOObjectCollection)
