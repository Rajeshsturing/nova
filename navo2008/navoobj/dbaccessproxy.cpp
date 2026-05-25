/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	CDBAccessProxy

	implementacja
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\progressgadget.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "resource.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"

#ifdef EOF
#undef EOF
#endif
#import MSADO15_PATH


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOOBJ_Instance;

//-----------------------------------------------------------------------------------
//
// FirstAccessHolder
//
//-----------------------------------------------------------------------------------
class CFirstAccessHolder
{
public:
	CFirstAccessHolder(CDBAccessProxy & roDBAccessProxy) :
		m_roDBAccessProxy(roDBAccessProxy)
	{
		if (m_roDBAccessProxy.m_bFirstDBAccess && m_roDBAccessProxy.m_bShowUI)
		{
			CAfxResourceHandleHolder oARHH(_h_NAVOOBJ_Instance);
			CString oMsgString;
			oMsgString.LoadString(IDS_CONNECTING_TO_DB);
			m_poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));
		}
	}
	~CFirstAccessHolder()
	{
		m_roDBAccessProxy.m_bFirstDBAccess = false;
	}

private:
	SCP<CPerformingDialogHolder> m_poPDHSP;
	CDBAccessProxy & m_roDBAccessProxy;
};

DELEGATE_UNKNOWN_INTERFACE(CDBAccessProxy, PingClient)

BEGIN_INTERFACE_MAP(CDBAccessProxy, CCmdTargetInterface)
	INTERFACE_PART(CDBAccessProxy, IID_IPingClient, PingClient)
END_INTERFACE_MAP()

SCP<CHyperLinkInfo> GetSystemEnvironmentHLI();

void CDBAccessProxy::Init(CDBAP_ConnectionParam & roConnectionParam, SCP<CDefinitionManager> poDefinitionManageSP)
{
	SCP<CHyperLinkInfo> poEnvHLISP = GetSystemEnvironmentHLI();

	m_poGITSP.CreateInstance(CLSID_StdGlobalInterfaceTable, CLSCTX_INPROC_SERVER);

	ASSERT(roConnectionParam.m_poServerClientSP.PointsObject());
	m_poServerClientSP = roConnectionParam.m_poServerClientSP;

	m_poDefinitionManageSP = poDefinitionManageSP;

	SCP<IUnknown> poUnknownSP;
	HRESULT	hr = m_poServerClientSP->GetService(nst_objserver, &poUnknownSP.GetRawPointer());
	if (hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poServerClientSP, oNavoException);
		ContinueThrowNavoException1(oNavoException, ERCO_USERDOC_CANNOT_CREATE_OBJECTSERVER, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}
	m_rpc_poObjectServerSP.QueryInterface(poUnknownSP);
	m_rpc_poObjectServerSP->SetProp(objsrv_database, CSmartOleVariant(roConnectionParam.m_lpDBName).GetVariantRef());
	m_rpc_poObjectServerSP->SetProp(objsrv_user, CSmartOleVariant(roConnectionParam.m_lpUserName).GetVariantRef());
	m_rpc_poObjectServerSP->SetProp(objsrv_password, CSmartOleVariant(roConnectionParam.m_lpPassword).GetVariantRef());
	m_rpc_poObjectServerSP->SetProp(objsrv_enginetype, CSmartOleVariant(roConnectionParam.m_nEngineType).GetVariantRef());
	poUnknownSP = 0;

	hr = m_poServerClientSP->GetService(nst_lockman, &poUnknownSP.GetRawPointer());
	if (hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poServerClientSP, oNavoException);
		ContinueThrowNavoException1(oNavoException, ERCO_USERDOC_CANNOT_CREATE_LOCKMANAGER, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}
	m_rpc_poLockManagerSP.QueryInterface(poUnknownSP);
	ASSERT(m_rpc_poLockManagerSP.PointsObject());

	ASSERT(m_poGITSP.PointsObject());
	VERIFY(S_OK == m_poGITSP->RegisterInterfaceInGlobal(m_rpc_poLockManagerSP.Get(),
		m_rpc_poLockManagerSP.GetIID(), &m_dwLockMan_GIT_Cookie));

	hr = m_poServerClientSP->AdviseLM(poEnvHLISP->GetStrProp(GVAR_OSUSERNAME),
		poEnvHLISP->GetStrProp(GVAR_MACHINE), &m_nLockManager_Cookie);

	if (hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poServerClientSP, oNavoException);
		ContinueThrowNavoException1(oNavoException, ERCO_USERDOC_LOCKMANAGER_ADVISE_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}

	hr = m_rpc_poObjectServerSP->SetCoManagers(
		roConnectionParam.m_lpAppName,
		m_rpc_poLockManagerSP.Get(),
		m_nLockManager_Cookie,
		roConnectionParam.m_bCompressTrafficToClient ? UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT : 0
	);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	m_nServerObject_PingCookie = AdvisePingServer(GetUnknown(), m_poServerClientSP);
	ASSERT(m_nServerObject_PingCookie);
}

void CDBAccessProxy::Done()
{
	if (m_poServerClientSP.PointsObject())
	{
		UnAdvisePingServer(m_poServerClientSP, m_nServerObject_PingCookie);
	}
	if (m_nLockManager_Cookie != 0)
	{
		HRESULT hr = m_poServerClientSP->UnAdviseLM(m_nLockManager_Cookie);
		ASSERT(hr == S_OK);		//to_do: obs³uga b³êdów
	}
	if (m_dwLockMan_GIT_Cookie != 0)
	{
		VERIFY(S_OK == m_poGITSP->RevokeInterfaceFromGlobal(m_dwLockMan_GIT_Cookie));
		m_dwLockMan_GIT_Cookie = 0;
	}
	if (m_rpc_poObjectServerSP.PointsObject())
	{
		HRESULT hr = m_rpc_poObjectServerSP->Close(BYTE(true));
		ASSERT(hr == S_OK);
		m_rpc_poObjectServerSP = 0;
	}
	m_nLockManager_Cookie = 0;
	m_rpc_poLockManagerSP = 0;
	m_poServerClientSP = 0;

#ifdef _DEBUG
	TRACE("--------- DBAccess Proxy stats ----------------\n");
	TRACE("total = %d\n", debug_total_data_read);
	TRACE("max   = %d\n", debug_max_data_read);
	TRACE("-----------------------------------------------\n");
#endif
}

HRESULT CDBAccessProxy::BeginGetObject(long TypeId, long IdObj, long	VersionNoReturn, bool bWriteLock, CFlatData & roFlatData)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());

	long nDataLength = 0;
	BYTE * pBuffer = nullptr;

	// zwolnienie nast¹pi w EndGetObject

	// readlock'ed on server automatically
	HRESULT hr = S_OK;
	long nTimes = 3;
once_again:

	//TRACE("GetObjectIfNewer %d,%d,%d\n",TypeId,IdObj,VersionNoReturn);

	if (IsNXMTransport())
	{
		SAFEARRAY * pSafeArray;
		m_rpc_poObjectServerSP->GetObjectIfNewer2(TypeId, IdObj, VersionNoReturn,
			BYTE(bWriteLock), &nDataLength, &pSafeArray, &hr);

		if (hr == S_OK)
		{
			void * pData;
			SafeArrayAccessData(pSafeArray, &pData);
			pBuffer = new BYTE[nDataLength];
			memcpy(pBuffer, pData, nDataLength);
			SafeArrayUnaccessData(pSafeArray);
			SafeArrayDestroy(pSafeArray);
		}
	}
	else
	{
		hr = m_rpc_poObjectServerSP->GetObjectIfNewer(TypeId, IdObj, VersionNoReturn,
			BYTE(bWriteLock), &nDataLength, &pBuffer);
	}

	if (hr != S_OK && hr != ERROR_LOCK_FAILED && hr != ERROR_EXE_MACHINE_TYPE_MISMATCH)
	{
		ASSERT(nDataLength == 0 && pBuffer == nullptr);
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	if (hr == ERROR_EXE_MACHINE_TYPE_MISMATCH)	//oznacza: nie ma takiego rekordu (nieprawid³owe idobj lub skasowany
	{
		return ERROR_EXE_MACHINE_TYPE_MISMATCH;
	}

	if (hr == ERROR_LOCK_FAILED)
	{
		//lock collision
		ASSERT(nDataLength == 0 && pBuffer == NULL);
		GetErrorInfoFromInterface(m_rpc_poObjectServerSP, m_roErrorStorage);
		--nTimes;

		if (nTimes == 2)
		{
			TRACE("WRITE LOCK FAILED for %d:%d. 1st retry\n", TypeId, IdObj);
#ifdef _DEBUG
			::MessageBeep(-1);
#endif
			::Sleep(250);
		}
		if (nTimes == 1)
		{
			long nDynaDelay = _get_dynamic_second_lock_delay();
			TRACE("WRITE LOCK FAILED for %d:%d. 2nd retry for %d ms\n", TypeId, IdObj, nDynaDelay);
			::Sleep(nDynaDelay);
		}
		if (nTimes == 0)
		{
			_register_lock_failure();
			return hr;
		}
		goto once_again;
	}

	if (bWriteLock)
	{
		_register_lock_success();
	}
	if (nDataLength != 0)
	{
		ASSERT(hr == S_OK);
		roFlatData = CFlatData(nDataLength, pBuffer);
		//newer version delivered
		//TRACE("delivered GetObjectIfNewer %d,%d,%d\n",TypeId,IdObj,VersionNoReturn);

#ifdef _DEBUG
		debug_total_data_read += nDataLength;
		debug_max_data_read = max(nDataLength, debug_max_data_read);
#endif
		return S_OK;
	}
	else
	{
		return S_FALSE;	//no newer version
	}
}

void CDBAccessProxy::EndGetObject(CFlatData & roFlatData)
{
	if (!IsNXMTransport())
	{
		::NdrOleFree(roFlatData.GetDataPtr());
	}
}

void CDBAccessProxy::ReadListCollection(long nCollectionId, long nParentId, CFlatData & roFlatData, long & rnCount)
{
	SCP<INAVOObjectCollection>	pRPC_oObjectCollectionSP = OpenListCollection(nCollectionId, nParentId, &rnCount);
	if (rnCount > 0)
	{
		long nDataLength = 0;
		BYTE * pData = NULL;
		HRESULT hr = S_OK;
		if (IsNXMTransport())
		{
			SAFEARRAY * pSABinData;
			hr = pRPC_oObjectCollectionSP->Fetch2(fdir_abs, &rnCount, &nDataLength, &pSABinData, 0);

			if (hr == S_OK)
			{
				void * _pData;
				SafeArrayAccessData(pSABinData, &_pData);
				pData = new BYTE[nDataLength];
				memcpy(pData, _pData, nDataLength);
				SafeArrayUnaccessData(pSABinData);
				SafeArrayDestroy(pSABinData);
			}
		}
		else
		{
			hr = pRPC_oObjectCollectionSP->Fetch(fdir_abs, &rnCount, &nDataLength, &pData, 0);
		}
		if (hr != S_OK)
		{
			ThrowFromInterface(pRPC_oObjectCollectionSP);
		}

		ASSERT(rnCount > 0);
		ASSERT(nDataLength && pData);

		//wype³nij robocz¹ tablicê
		roFlatData = CFlatData(nDataLength, pData);
	}
}

long CDBAccessProxy::GetUniqueIdent(long TypeId)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	long lNewId;
	HRESULT hr = m_rpc_poObjectServerSP->GetUniqueIdent(TypeId, &lNewId);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	ASSERT(lNewId > 0);
	return lNewId;
}

CString CDBAccessProxy::MakeTransaction(CFlatData & roFlatData,
	long nBlobCount, const transblobinfo * pBlobInfo,
	long nWriteLockCount, const navolock * pNavoLockInfo,
	bool bCommit, LPCTSTR lpExtras)
{
	CString strResult = "+";

	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	long nDataLength = roFlatData.GetDataLen();
	if (nDataLength == 0 && nBlobCount == 0 && !bCommit)
	{
		return strResult;
	}
	HRESULT hr = S_OK;

	if (IsNXMTransport())
	{

		for (int iInx = 0; iInx < nBlobCount; iInx++)
		{
			hr = m_rpc_poObjectServerSP->MakeTransaction_Stream(
				pBlobInfo[iInx].m_pIStream,
				pBlobInfo[iInx].m_IdParent,
				pBlobInfo[iInx].m_IdMapping,
				pBlobInfo[iInx].m_oNSI);

			if (hr != S_OK)
			{
				ThrowFromInterface(m_rpc_poObjectServerSP);
			}
		}

		for (int iInx = 0; iInx < nWriteLockCount; iInx++)
		{
			hr = m_rpc_poObjectServerSP->Lock_AddItem(
				iInx,
				pNavoLockInfo[iInx].m_fullid.m_class,
				pNavoLockInfo[iInx].m_fullid.m_typeid,
				pNavoLockInfo[iInx].m_fullid.m_idobj,
				pNavoLockInfo[iInx].m_fullid.m_extra,
				pNavoLockInfo[iInx].m_type);

			if (hr != S_OK)
			{
				ThrowFromInterface(m_rpc_poObjectServerSP);
			}
		}

		SAFEARRAY * pSABinData = SafeArrayCreateVector(VT_UI1, 0, nDataLength);
		void * _pBinData = 0;

		SafeArrayAccessData(pSABinData, &_pBinData);
		memcpy(_pBinData, roFlatData.GetDataPtr(), nDataLength);
		SafeArrayUnaccessData(pSABinData);

		LPSTR pResult = NULL;

		hr = m_rpc_poObjectServerSP->MakeTransaction2(&pSABinData, nWriteLockCount, BYTE(bCommit), lpExtras, &pResult);

		if (pResult != NULL)
		{
			strResult = CString(pResult);
			::NdrOleFree(pResult);
		}

		SafeArrayDestroy(pSABinData);
	}
	else
	{

		hr = m_rpc_poObjectServerSP->MakeTransaction(nDataLength, roFlatData.GetDataPtr(), nBlobCount,
			const_cast<transblobinfo *>(pBlobInfo), nWriteLockCount, pNavoLockInfo, BYTE(bCommit));
	}
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	return strResult;
}

void CDBAccessProxy::FinishTransaction(bool bSuccess)
{
	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->FinishTransaction(BYTE(bSuccess));
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
}

bool CDBAccessProxy::_lock_items(SCP<ILockManager> & rpoLockManagerSP, navolock * pNavoLockInfo, long nCount,
	bool bLock, bool bSilent)
{
	if (IsNXMTransport())
	{
		for (int iInx = 0; iInx < nCount; iInx++)
		{
			HRESULT hr = rpoLockManagerSP->Lock_AddItem(
				iInx,
				pNavoLockInfo[iInx].m_fullid.m_class,
				pNavoLockInfo[iInx].m_fullid.m_typeid,
				pNavoLockInfo[iInx].m_fullid.m_idobj,
				pNavoLockInfo[iInx].m_fullid.m_extra,
				pNavoLockInfo[iInx].m_type);

			if (hr != S_OK)
			{
				ThrowFromInterface(m_rpc_poObjectServerSP);
			}
		}

		if (nCount > 0)
		{
			HRESULT	hr = rpoLockManagerSP->Lock2(m_nLockManager_Cookie, BYTE(bLock), nCount);

			if (hr != S_OK)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(rpoLockManagerSP, oNavoException);
				if (hr != S_FALSE)
				{
					ContinueThrowNavoException1(oNavoException, ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
				}
				else
				{
					if (!bSilent)
					{
						m_roErrorStorage += oNavoException;
					}
				}
			}

			return (hr == S_OK);
		}

		return true;
	}
	else
	{
		HRESULT hr = rpoLockManagerSP->Lock(m_nLockManager_Cookie, BYTE(bLock), nCount, pNavoLockInfo);

		if (hr != S_OK)
		{
			CNavoException oNavoException;
			GetErrorInfoFromInterface(rpoLockManagerSP, oNavoException);
			if (hr != S_FALSE)
			{
				ContinueThrowNavoException1(oNavoException, ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
			}
			else
			{
				if (!bSilent)
				{
					m_roErrorStorage += oNavoException;
				}
			}
		}

		return (hr == S_OK);
	}
}

long CDBAccessProxy::_get_dynamic_second_lock_delay() const
{
	long nDelay = 500;
	if (m_DynaLockStatShift & 0x03C00000)	//4 poprzednich
	{
		nDelay += 500;
		TRACE("Dynadelay bumped to %d (LIGHT)\n", nDelay);
	}
	if (m_DynaLockStatShift & 0x3C000000)	//4 poprzednich
	{
		nDelay += 500;
		TRACE("Dynadelay bumped to %d (MEDIUM)\n", nDelay);
	}
	if (m_DynaLockStatShift & 0xC0000000)	//najnowsze 2 próby
	{
		nDelay += 1000;
		TRACE("DYNADELAY BUMPED to %d (HEAVY)\n", nDelay);
	}

	nDelay = min(2500, max(500, nDelay));

	ASSERT(nDelay >= 500 && nDelay <= 2500);
	return nDelay;
}

void CDBAccessProxy::_register_lock_success()
{
	m_DynaLockStatShift = m_DynaLockStatShift / 2;
}

void CDBAccessProxy::_register_lock_failure()
{
	m_DynaLockStatShift = m_DynaLockStatShift / 2;
	m_DynaLockStatShift |= 0x80000000;
}

bool CDBAccessProxy::LockItems(navolock * poNLI, long nCount, bool bLock)
{
	SCP<ILockManager> poLockManagerSP;
	ASSERT(m_dwLockMan_GIT_Cookie != 0);
	VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwLockMan_GIT_Cookie,
		poLockManagerSP.GetIID(), reinterpret_cast<void**>(&poLockManagerSP.GetRawPointer())));

	ASSERT(poLockManagerSP.PointsObject());

	ASSERT(nCount > 0);	//avoid unnecessary calls
	ASSERT(poNLI != NULL);	//avoid invalid calls

	long nTimes = 3;
	while (--nTimes)
	{
		if (_lock_items(poLockManagerSP, poNLI, nCount, bLock, nTimes == 1))
		{
			if (bLock)
			{
				_register_lock_success();
			}
			return true;
		}

		ASSERT(bLock);	//tylko lock mo¿e siê nie udaæ, unlock musi siê udaæ
		if (nTimes == 2)
		{
			TRACE("(UN)LOCKITEMS FAILED. 1st retry\n");
#ifdef _DEBUG
			::MessageBeep(-1);
#endif
			::Sleep(250);
		}

		if (nTimes == 1)
		{
			long nDynaDelay = _get_dynamic_second_lock_delay();
			TRACE("(UN)LOCKITEMS FAILED. 2nd retry for %d ms\n", nDynaDelay);
			::Sleep(nDynaDelay);
		}
	}
	if (bLock)
	{
		_register_lock_failure();
	}
	return false;
}

static LPCTSTR lpcEmptyString = "";

SCP<INAVOObjectCollection> CDBAccessProxy::OpenCursor(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause, LPCTSTR lpJoinClause, bool bForwardOnly, long nTop)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	SCP<INAVOObjectCollection> pIObjectCollectionSP;
	HRESULT hr = m_rpc_poObjectServerSP->OpenOnStatement(TypeId,
		(lpWhereClause != NULL) ? lpWhereClause : lpcEmptyString,
		(lpOrderByClause != NULL) ? lpOrderByClause : lpcEmptyString,
		(lpJoinClause != NULL) ? lpJoinClause : lpcEmptyString, BYTE(bForwardOnly), nTop,
		&pIObjectCollectionSP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return pIObjectCollectionSP;
}

SCP<INAVOObjectCollection>	CDBAccessProxy::OpenListCollection(long  CollectionId, long  IdParent, long * pTotalCount)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	SCP<INAVOObjectCollection> pIObjectCollectionSP;
	HRESULT hr = m_rpc_poObjectServerSP->OpenCollection(CollectionId, IdParent, pTotalCount,
		&pIObjectCollectionSP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return pIObjectCollectionSP;
}

SCP<INAVOObjectCollection> CDBAccessProxy::OpenFTSQuery(long IdMapping, LPCSTR lpQuery)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	SCP<INAVOObjectCollection> pIObjectCollectionSP;
	HRESULT hr = m_rpc_poObjectServerSP->OpenFTSQuery(IdMapping, lpQuery, &pIObjectCollectionSP.GetRawPointer());
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return pIObjectCollectionSP;
}

ADODB::_RecordsetPtr CDBAccessProxy::_OpenDiscoRecSet(LPCTSTR lpSQLClause)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	ASSERT(lpSQLClause);
	SCP<IStream> poDiscoRecSetStreamSP;
	navostreaminfo oNSI;
	_init_navostreaminfo(oNSI);
	HRESULT hr = m_rpc_poObjectServerSP->OpenDiscoRecSet(lpSQLClause, &poDiscoRecSetStreamSP.GetRawPointer(), &oNSI);
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	if (poDiscoRecSetStreamSP.PointsNull())
	{
		return NULL;
	}

	ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if (oNSI.m_bCompressed == '1')
	{
		poDiscoRecSetStreamSP = UncompressStream(poDiscoRecSetStreamSP);
		/*
			ADODB.Recordset wykonuje seek przy otwarciu, czyta trochê danych i
			cofa siê do pocz¹tku.
			Poniewa¿ decompressor jest read-only,forward-only
			musimy kopiowaæ wszystko do strumienia tymczasowego i operowaæ na tym strumieniu

			to_do: przyda³by sie obiekt buforuj¹cy strumieñ
		*/

		SCP<IStream> poStreamSP = CreateTempFileStream();
		ULARGE_INTEGER ulInfinity;
		ulInfinity.QuadPart = MAXLONG;
		VERIFY(S_OK == poDiscoRecSetStreamSP->CopyTo(poStreamSP, ulInfinity, NULL, NULL));
		CStreamHolder(poStreamSP).SeekToBegin();
		poDiscoRecSetStreamSP = poStreamSP;
	}

	ADODB::_RecordsetPtr poRecordsetPtr;
	poRecordsetPtr.CreateInstance("ADODB.Recordset");
	poRecordsetPtr->Open(_variant_t((IUnknown*)poDiscoRecSetStreamSP.Get(), true), vtMissing, ADODB::adOpenStatic, ADODB::adLockReadOnly, ADODB::adCmdUnspecified);

	return poRecordsetPtr;
}


SCP<IDispatch> CDBAccessProxy::OpenDiscoRecSet(LPCTSTR lpSQLClause)
{
	ADODB::_RecordsetPtr poRecordsetPtr = _OpenDiscoRecSet(lpSQLClause);

	SCP<IDispatch> poDiscoRecSetDispatchSP;
	poDiscoRecSetDispatchSP.QueryInterface(poRecordsetPtr);
	return poDiscoRecSetDispatchSP;
}

bool CDBAccessProxy::TestCanDelete(long TypeId, long IdObj, SCP<IDispatch> & rpoDiscoRecDispatchSP)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());

	if (IsNXMTransport())
	{
		SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManageSP->GetStdObjDef(TypeId);
		CString oSQLString = poStdObjDefSP->GetTableName() +
			_T("_candel ") + Long2String(IdObj);

		ADODB::_RecordsetPtr poRecordsetPtr = _OpenDiscoRecSet(oSQLString);

		return (poRecordsetPtr == NULL) || (poRecordsetPtr->BOF || poRecordsetPtr->EOF);
	}
	else
	{
		HRESULT hr = m_rpc_poObjectServerSP->CanDelete(TypeId, IdObj,
			&rpoDiscoRecDispatchSP.GetRawPointer());
		if (hr != S_OK && hr != S_FALSE)
		{
			ThrowFromInterface(m_rpc_poObjectServerSP);
		}
		return (hr == S_OK);
	}
}

SCP<IStream> CDBAccessProxy::GetDataBaseFile(long IdParent, long IdMapping, navostreaminfo & roNSI,
	long & rnVersion, long & rnStreamId)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());

	SCP<IStream> poStreamSP;
	HRESULT hr = m_rpc_poObjectServerSP->GetStream(IdParent, IdMapping, &poStreamSP.GetRawPointer(),
		&roNSI, &rnVersion, &rnStreamId);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return poStreamSP;
}

long CDBAccessProxy::FindStdObj(long TypeId, LPCTSTR lpWhereClause)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	long nFoundId;

	HRESULT hr = m_rpc_poObjectServerSP->FindOnField(TypeId, lpWhereClause, &nFoundId);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return nFoundId;
}


long CDBAccessProxy::ExecSQL(LPCTSTR lpSQLCommand)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	long nRecordsAffected = -1;
	HRESULT hr = m_rpc_poObjectServerSP->ExecSQL(lpSQLCommand, &nRecordsAffected);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return nRecordsAffected;
}

void CDBAccessProxy::SetSharedVar(long nVarNr, const CSmartOleVariant & roSOV, long nNotifyOriginatorCookie)
{
	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->SetSharedVariable(nNotifyOriginatorCookie, nVarNr, roSOV.GetVariantRef());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
}

bool CDBAccessProxy::GetSharedVar(long nVarNr, CSmartOleVariant & roSOV)
{
	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->GetSharedVariable(nVarNr, &roSOV.GetVariantRef());
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return (hr == S_OK);
}

void CDBAccessProxy::SetServerProp(objsrv_prop eSrvProp, const CSmartOleVariant & roSOV)
{
	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->SetProp(eSrvProp, roSOV.GetVariantRef());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
}

void CDBAccessProxy::GetServerProp(objsrv_prop eSrvProp, CSmartOleVariant & roSOV)
{
	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->GetProp(eSrvProp, roSOV.GetVariantRef());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
}

void CDBAccessProxy::GetServerRegistryKeyString(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, CString & roDataString)
{
	ASSERT(m_poServerClientSP.PointsObject());
	LPSTR pString = NULL;
	HRESULT hr = m_poServerClientSP->GetRegistryKeyString(long(hKeyClass), lpSubKey, lpName, &pString);
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_poServerClientSP);
	}
	if (hr == S_OK)
	{
		roDataString = CString(pString);
	}
	else
	{
		roDataString = "";
	}
	::NdrOleFree(pString);
}

void CDBAccessProxy::SetServerRegistryKeyString(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, LPCTSTR lpValue)
{
	ASSERT(m_poServerClientSP.PointsObject());
	HRESULT hr = m_poServerClientSP->SetRegistryKeyString(long(hKeyClass), lpSubKey, lpName, lpValue);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_poServerClientSP);
	}
}

//------------------------------------------------------- counted resources ----------
bool CDBAccessProxy::create_counted_resource(LPCTSTR lpResName, long nMaxUsage)
{
	ASSERT(m_rpc_poLockManagerSP.PointsObject());
	SCP<ICntResourceManager> poResourceManagerSP;
	poResourceManagerSP.QueryInterface(m_rpc_poLockManagerSP);
	HRESULT hr = poResourceManagerSP->CreateResource(lpResName, nMaxUsage);
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(poResourceManagerSP);
	}
	return (hr == S_OK);
}

bool CDBAccessProxy::delete_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_rpc_poLockManagerSP.PointsObject());
	SCP<ICntResourceManager> poResourceManagerSP;
	poResourceManagerSP.QueryInterface(m_rpc_poLockManagerSP);
	HRESULT hr = poResourceManagerSP->DeleteResource(lpResName);
	if (hr != S_OK && hr != S_FALSE)
	{
		if (hr == ERROR_RESOURCE_NAME_NOT_FOUND)
		{
			ASSERT(false);		//bad name
		}
		ThrowFromInterface(poResourceManagerSP);
	}
	return (hr == S_OK);
}

long CDBAccessProxy::use_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_rpc_poLockManagerSP.PointsObject());
	SCP<ICntResourceManager> poResourceManagerSP;
	poResourceManagerSP.QueryInterface(m_rpc_poLockManagerSP);

	HRESULT hr = S_OK;

	if (IsNXMTransport())
	{
		poResourceManagerSP->UseResource2(lpResName, m_nLockManager_Cookie, &hr);
	}
	else
	{
		hr = poResourceManagerSP->UseResource(lpResName, m_nLockManager_Cookie);
	}

	switch (hr)
	{
	case S_OK:
		return +1;
	case S_FALSE:
		return 0;
	case ERROR_RESOURCE_NAME_NOT_FOUND:
		return -1;
	default:
		ThrowFromInterface(poResourceManagerSP);
	}
}

long CDBAccessProxy::get_usage_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_rpc_poLockManagerSP.PointsObject());
	SCP<ICntResourceManager> poResourceManagerSP;
	poResourceManagerSP.QueryInterface(m_rpc_poLockManagerSP);

	HRESULT hr = S_OK;

	if (IsNXMTransport())
	{
		poResourceManagerSP->UseResource2(lpResName, 0/*means: test only*/, &hr);
	}
	else
	{
		hr = poResourceManagerSP->UseResource(lpResName, 0/*means: test only*/);
	}

	if (hr == ERROR_RESOURCE_NAME_NOT_FOUND)
	{
		return -1;
	}
	if (hr <= 0)
	{
		return -long(hr);
	}

	ThrowFromInterface(poResourceManagerSP);
}

void CDBAccessProxy::release_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_rpc_poLockManagerSP.PointsObject());
	SCP<ICntResourceManager> poResourceManagerSP;
	poResourceManagerSP.QueryInterface(m_rpc_poLockManagerSP);
	HRESULT hr = poResourceManagerSP->ReleaseResource(lpResName, m_nLockManager_Cookie);
	if (hr != S_OK)
	{
		if (hr == ERROR_RESOURCE_NAME_NOT_FOUND)
		{
			ASSERT(false);		//bad name
		}
		ThrowFromInterface(poResourceManagerSP);
	}
}

SCP<IDispatch> CDBAccessProxy::create_server_extension(LPCTSTR lpExtensionProgID)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	ASSERT(lpExtensionProgID);

	SCP<IDispatch> poExtensionDispatchSP;
	HRESULT hr = m_rpc_poObjectServerSP->CreateExtension(lpExtensionProgID, &poExtensionDispatchSP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}
	return poExtensionDispatchSP;
}

//------------------------------------------------------------------------------------
bool CDBAccessProxy::WriteToArchive(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream * pDestStream)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->WriteToArchive(lpSAUser, lpPwd, lpArchivePwd, pDestStream);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	return true;
}

bool CDBAccessProxy::ReadFromArchive(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, IStream * pSrcStream)
{
	CFirstAccessHolder oFAH(*this);

	ASSERT(m_rpc_poObjectServerSP.PointsObject());
	HRESULT hr = m_rpc_poObjectServerSP->ReadFromArchive(lpSAUser, lpPwd, lpArchivePwd, pSrcStream);
	if (hr != S_OK)
	{
		ThrowFromInterface(m_rpc_poObjectServerSP);
	}

	return true;
}

