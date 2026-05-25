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
#include "adocommand.h"
#include "NAVODB_Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _VERSION_WITHOUT_COMMAND_TIMEOUT_

extern CNavoLog g_oLog;

//in this mode transaction is started only on demand (reads may be performed outside transaction)
//when false, old mode is used (transaction is started at connect and auto-restarted after commit)

bool _is_TransactionMode2020() { return true; }

CADOObjServer::CADOObjServer() :
	m_bInTransaction(false),
	m_EngineType(dbet_ms_sql70),
	m_nCachedData_PingCookie(0),
	m_nNotifyManCookie(0),
	m_nLockManCookie(0),
	m_bCompressTrafficToClient(false),
	m_oNOIH(CNavoOleInitHolder::MULTITHREADED)
{
	EnableAutomation();
	AfxOleLockApp();
}

CADOObjServer::~CADOObjServer()
{
	_clean_up();
	AfxOleUnlockApp();
}

void CADOObjServer::_clean_up()
{
	if (m_poCurrentTHSP.PointsObject())
	{
		m_poCurrentTHSP->SetRollback();
	}
	m_poCurrentTHSP = 0;
	if (m_poCachedDataSP.PointsObject())
	{
		UnAdvisePingServer(m_poCachedDataSP, m_nCachedData_PingCookie);
		VERIFY(S_OK == m_poCachedDataSP->Close(BYTE(true)));
		m_poCachedDataSP = 0;
	}
	m_poDefinitionManagerSP = 0;
	m_poNotificationManagerSP = 0;
	m_poLockManagerSP = 0;
	m_nLockManCookie = 0;
	m_nNotifyManCookie = 0;
	Logoff();
	m_poFDObjectCacheSP = 0;
}

BEGIN_MESSAGE_MAP(CADOObjServer, CCmdTargetWithErrorInfo)
	//{{AFX_MSG_MAP(CADOObjServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




void CADOObjServer::_update_effective_server()
{
	//-------------------------------------------------
	//this allows to redirect calls to next tier server
	//-------------------------------------------------

	if (m_oEffectiveServerString.IsEmpty())
	{
		CString oSQLServerString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetDatabaseRegistryKeyName(), _T("Server"), oSQLServerString);
		if (oSQLServerString.IsEmpty())
		{
			TCHAR cComputerName[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD nComputerNameLen = sizeof(cComputerName);
			VERIFY(::GetComputerName(cComputerName, &nComputerNameLen));
			oSQLServerString = CString(cComputerName) + _T("\\NAVO2002");
		}
		m_oEffectiveServerString = oSQLServerString;
	}

	ASSERT(!m_oEffectiveServerString.IsEmpty());
}
//----------------------------------------------
//
//	Error information functions
//
//----------------------------------------------

//----------------------------------------------
//----------------------------------------------
void CADOObjServer::Login(bool bForRestore)
{
	if (g_oLog.IsHandleValid())
	{
		g_oLog << "entering CADOObjServer::Login";
	}

	if (m_poConnectionPtr)
	{
		if (g_oLog.IsHandleValid())
		{
			g_oLog << "CADOObjServer::Login => m_poConnectionPtr exists";
		}
		return;
	}

	m_poConnectionPtr.CreateInstance(_T("ADODB.Connection"));

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "CADOObjServer::Login => ADODB.Connection instance created";
	}

	//-------------------------------------------------

	switch (m_EngineType)
	{
	case dbet_ms_jet35:
		_login_msjet();
		break;
	case dbet_ms_sql70:
	case dbet_ms_sql2000:
		_login_mssql();
		break;
	default:
		ASSERT(false);
	}

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "inside CADOObjServer::Login";
	}

	m_poFDObjectCacheSP = theApp.get_cache_for_cacheuid(m_oEffectiveServerString + ";" + m_oDBString);

	if (!bForRestore)
	{
		_sync_cache_stream_counter();
	}

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "done CADOObjServer::Login";
	}
}

void CADOObjServer::Logoff()
{
	m_poConnectionPtr = 0;
}

void CADOObjServer::_begin_transaction()
{
	Login(false);

	if (_is_TransactionMode2020())
	{
		m_poConnectionPtr->BeginTrans();
	}

	ASSERT(!m_bInTransaction);
	m_bInTransaction = true;
}

void CADOObjServer::_end_transaction(bool bCommit, long nFileTransactionId)
{
	ASSERT(m_bInTransaction);
	HRESULT hr = S_OK;
	if (bCommit)
	{
		if (nFileTransactionId != 0)
		{
			hr = CommitFiles(nFileTransactionId);
		}
		if (hr == S_OK)
		{
			hr = m_poConnectionPtr->CommitTrans();
		}
	}
	else
	{
		if (nFileTransactionId != 0)
		{
			hr = RollbackFiles(nFileTransactionId);
		}
		//in every situation, rollback transaction
		hr = m_poConnectionPtr->RollbackTrans();
	}
	if (hr != S_OK)
	{
		//try rollback database anyway !!!
		m_poConnectionPtr->RollbackTrans();

		ThrowNavoException1(ERCO_OBJSERV_COMMIT_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}
	m_bInTransaction = false;
}

void CADOObjServer::MakeTransaction(long nDataLength, byte * lpBinaryData,
	long nBlobInfoCount, transblobinfo * pBlobInfo,
	long nWriteLockCount, const navolock * pNavoLock, bool bCommit)
{
	try
	{
		ASSERT(nDataLength != 0 || nBlobInfoCount != 0 || bCommit);	//po co wo³ane gdy nie ma nic do robienia

#ifdef _DEBUG
		CDebugTimeMeter oDTM(_T("MakeTransaction="));
#endif

		//otwórz TransactionHolder, jeœli jest taka potrzeba
		if ((nDataLength != 0) || (nBlobInfoCount != 0))
		{
			if (m_poCurrentTHSP.PointsNull())
			{
				m_poCurrentTHSP = NewSCP(new CTransactionHolder(*this));
			}
			ASSERT(m_poCurrentTHSP.PointsObject());
		}

		//przetwórz pliki (jeœli s¹)
		if (nBlobInfoCount != 0)
		{
			ASSERT(m_poCurrentTHSP.PointsObject());
			for (long iter = 0; iter < nBlobInfoCount; iter++)
			{
				if (pBlobInfo[iter].m_pIStream != NULL)
				{
					StoreFile(pBlobInfo[iter].m_IdParent, pBlobInfo[iter].m_IdMapping, NewSCP<IStream>(pBlobInfo[iter].m_pIStream, true),
						&pBlobInfo[iter].m_oNSI);
				}
				else
				{
					RemoveFile(pBlobInfo[iter].m_IdParent, pBlobInfo[iter].m_IdMapping);
				}
			}
		}
		//przetwórz rekordy (jeœli s¹)
		if (nDataLength != 0)
		{
			ASSERT(m_poCurrentTHSP.PointsObject());

			CFlatData oFlatData(nDataLength, lpBinaryData);
			{
				CFlatDataIterator oFlatDataIterator(oFlatData);
				while (1)
				{
					CFlatData oRecordFlatData;
					bool bMore = oFlatDataIterator.GetNext(oRecordFlatData);
					CFlatData::CFDHeader oFDHeader(oRecordFlatData);
					ExecuteStatement(oRecordFlatData);
					if (!bMore)
					{
						break;
					}
				}
			}
		}

		if (m_poCurrentTHSP.PointsObject())
		{
			//
			//ASSERT(nDataLength != 0 || nBlobInfoCount != 0);
			//

			//zaznacz ¿e siê uda³o
			m_poCurrentTHSP->SetCommit();
		}
		else
		{
			ASSERT(nDataLength == 0 && nBlobInfoCount == 0);
		}

		//update GLOB_CACHE (tylko dla bCommit, bo inaczej trzeba bêdzie odkrêcaæ, a
		//poza tym jest szansa, ¿e to bêdzie du¿a transakcja i zaraz wyflushuje z cache'a
		//a poza tym nie powinno to byæ widoczne dla innych gdy¿ nie jest skomitowane).

		if (nDataLength != 0)
		{
			CFlatData oFlatData(nDataLength, lpBinaryData);
			CFlatDataIterator oFlatDataIterator(oFlatData);
			ASSERT(m_poFDObjectCacheSP.PointsObject());
			CSimpleLock oSimpleLock(m_poFDObjectCacheSP->CriticalSection());

			while (1)
			{
				CFlatData oRecordFlatData;
				bool bMore = oFlatDataIterator.GetNext(oRecordFlatData);
				CFlatData::CFDHeader oFDHeader(oRecordFlatData);
				stdobjactions Action = (stdobjactions)oFDHeader.Action();

				//pomijamy pozosta³e akcje
				if (Action == action_insert || Action == action_update || Action == action_delete)
				{
					//w trybie commit wsadzaj inserty i updaty
					if (bCommit && (Action == action_insert || Action == action_update))
					{
						SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(oFDHeader.TypeId());
						ASSERT(poStdObjDefSP);
						if (!poStdObjDefSP->IsVolatile() && poStdObjDefSP->IsCacheOnServer())
						{
							SCP<CFlatData> poFlatDataSP = NewSCP(new CFlatData());
							memcpy(poFlatDataSP->GrowBy(oRecordFlatData.GetDataLen()),
								oRecordFlatData.GetDataPtr(), oRecordFlatData.GetDataLen());
							ASSERT(m_poFDObjectCacheSP.PointsObject());
							m_poFDObjectCacheSP->Set(oFDHeader.TypeId(), oFDHeader.IdObj(), poFlatDataSP);
						}
					}
					else if (!bCommit || (Action == action_delete))
						//jeœli nie jest tryb commit to wywal z cache, aby inni nie dostawali starych informacji
					{
						ASSERT(m_poFDObjectCacheSP.PointsObject());
						m_poFDObjectCacheSP->Remove(oFDHeader.TypeId(), oFDHeader.IdObj());
					}
					else
					{
						ASSERT(false);	//nie ma innych przypadków
					}
				}

				if (!bMore)
				{
					break;
				}
			}
		}
		if (nDataLength != 0)
		{
			ASSERT(m_poFDObjectCacheSP.PointsObject());
			if (m_poFDObjectCacheSP->is_tracking_writes())
			{
				CFlatData oFlatData(nDataLength, lpBinaryData);
				long nUserDynamicCookie = reinterpret_cast<long>(this);
				m_poFDObjectCacheSP->track_write(nUserDynamicCookie, oFlatData);
			}
		}
		if (bCommit)	//jak commit to commituj
		{
			if (m_poCurrentTHSP.PointsObject())
			{
				//ASSERT(nDataLength != 0 || nBlobInfoCount != 0);
				m_poCurrentTHSP = 0;
			}
			else
			{
				ASSERT(nDataLength == 0 && nBlobInfoCount == 0);
			}
			ASSERT(m_poCurrentTHSP.PointsNull());
		}
		if (nWriteLockCount != 0)
		{
			HRESULT hr = m_poLockManagerSP->Lock(m_nLockManCookie, BYTE(false), nWriteLockCount, pNavoLock);
			ASSERT(hr == S_OK);	//unlock musi siê udaæ
		}
	}
	catch (...)
	{
		//definitywnie rollback
		FinishTransaction(false);
		throw;
	}
}

void CADOObjServer::FinishTransaction(bool bSuccess)
{
	if (m_poCurrentTHSP.PointsObject())
	{
		if (bSuccess)
		{
			m_poCurrentTHSP->SetCommit();
		}
		else
		{
			m_poCurrentTHSP->SetRollback();
		}
	}
	m_poCurrentTHSP = 0;	//to zamyka transakcjê w tê czy inn¹ stronê
}

void CADOObjServer::purge_cache()
{
	ASSERT(m_poFDObjectCacheSP.PointsObject());
	CSimpleLock oSimpleLock(m_poFDObjectCacheSP->CriticalSection());

	m_poFDObjectCacheSP->purge();
}

void CADOObjServer::ExecuteStatement(const CFlatData & roFlatData)
{
	Login(false);

	ASSERT(m_bInTransaction);

	CFlatData::CFDHeader oFDHeader(roFlatData);
	stdobjactions Action = (stdobjactions)oFDHeader.Action();
	long TypeId = oFDHeader.TypeId();
	switch (Action)
	{
	case action_insert:
	case action_update:
	case action_delete:
		ExecuteSimpleStatement(roFlatData, Action, TypeId);
		break;
	case action_lists:
	{
		long IdObj = oFDHeader.IdObj();
		ExecuteListStatement(roFlatData, TypeId, IdObj);
	}
	break;
	default:
		ASSERT(false);
	}
}

void CADOObjServer::ExecuteSimpleStatement(const CFlatData & roFlatData, stdobjactions Action, long TypeId)
{
	switch (m_EngineType)
	{
	case dbet_ms_jet35:
		_execute_simple_stat_msjet(roFlatData, Action, TypeId);
		break;
	case dbet_ms_sql70:
	case dbet_ms_sql2000:
		_execute_simple_stat_mssql(roFlatData, Action, TypeId);
		break;
	default:
		ASSERT(false);
	}
}

void CADOObjServer::ExecuteListStatement(const CFlatData & roFlatData, long TypeId, long IdParent)
{
#ifdef _DEBUG
	CDebugTimeMeter oDTM(_T("ExecuteListStatement="));
#endif
	switch (m_EngineType)
	{
	case dbet_ms_jet35:
		_execute_list_stat_msjet(roFlatData, TypeId, IdParent);
		break;
	case dbet_ms_sql70:
	case dbet_ms_sql2000:
		_execute_list_stat_mssql(roFlatData, TypeId, IdParent);
		break;
	default:
		ASSERT(false);
	}
}

LPCTSTR DelStreamMapProcedure();
LPCTSTR InsStreamMapProcedure();
LPCTSTR SelStreamMapProcedure();
LPCTSTR UpdStreamMapProcedure();

void CADOObjServer::ExecInsStreamMap(long nIdStream, long nIdParent, long nIdMapping)
{
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdParent);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdMapping);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdStream);
	oCommand.ExecProc(InsStreamMapProcedure(), true);
}

void CADOObjServer::ExecDelStreamMap(long nIdParent, long nIdMapping)
{
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdParent);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdMapping);
	oCommand.ExecProc(DelStreamMapProcedure(), true);
}

long CADOObjServer::ExecSelStreamMap(long nIdParent, long nIdMapping, long & rnVersion)
{
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddReturnValueParam(SQLT_INT);

	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdParent);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdMapping);
	oCommand.AddOutParam(SQLT_INT);	//0=idstream
	oCommand.AddOutParam(SQLT_INT);	//1=version
	oCommand.ExecProc(SelStreamMapProcedure(), false);
	ASSERT(oCommand.GetReturnValue().Type() == VT_I4);
	if (oCommand.GetReturnValue().GetLong() != 1)
	{
		return 0;	//nie ma takiego streammappingu - to jest ok
	}
	long nIdStream = oCommand.GetOutParam(0).GetLong();
	rnVersion = oCommand.GetOutParam(1).GetLong();
	ASSERT(nIdStream != 0);
	return nIdStream;
}

void CADOObjServer::ExecUpdStreamMap(long nIdParent, long nIdMapping, long nVersion)
{
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdParent);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nIdMapping);
	oCommand.AddInParam(SQLT_INT, (LPVOID)&nVersion);
	oCommand.ExecProc(UpdStreamMapProcedure(), true);
}


void CADOObjServer::_sync_cache_stream_counter()
{
	if (_is_TransactionMode2020())
	{
		m_poConnectionPtr->BeginTrans();
	}

	long iMaxIdInStreamMap = 0;
	CADOCommand oCommand(m_poConnectionPtr);
	ADODB::_RecordsetPtr poRecordsetPtr = oCommand.ExecDirect("select isnull(max(IdStream),0) from StreamMap", false);
	if (!poRecordsetPtr->EOF)
	{
		_variant_t vIndex = long(0);
		ADODB::FieldPtr poFieldPtr = poRecordsetPtr->Fields->GetItem(vIndex);
		iMaxIdInStreamMap = poFieldPtr->GetValue().lVal;
		ASSERT(iMaxIdInStreamMap >= 0);
	}
	long iIdStream = iMaxIdInStreamMap - 1;
	GetMaxIdObj(TYPEID_FILE, iIdStream);
	ASSERT(iIdStream >= iMaxIdInStreamMap);

	m_poConnectionPtr->CommitTrans();
}

bool CADOObjServer::_Move(ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection, long nAbsPos)
{
	//move to
	switch (nFetchDirection)
	{
	case fdir_first:
		if (rpoRecordsetPtr->BOF)	//nie ma rekordów
		{
			return false;
		}
		rpoRecordsetPtr->MoveFirst();
		break;
	case fdir_next:
		if (rpoRecordsetPtr->BOF || rpoRecordsetPtr->EOF)
		{
			return false;
		}
		//noop
		break;
	case fdir_prev:
		if (rpoRecordsetPtr->BOF)
		{
			return false;
		}
		ASSERT(false);	//to_do: zaimplementowaæ
		break;
	case fdir_last:
		if (rpoRecordsetPtr->EOF)
		{
			return false;
		}
		rpoRecordsetPtr->MoveLast();
		break;
	case fdir_abs:
		try
		{
			rpoRecordsetPtr->Move(nAbsPos, _variant_t(long(ADODB::adBookmarkFirst), VT_I4));
		}
		catch (_com_error e)
		{
			HRESULT hr = e.Error();
			if ((hr & 0xffff) == ADODB::adErrNoCurrentRecord)
			{
				return false;
			}
			throw;	//throw any other errors
		}
		break;
	default:
		ASSERT(false);
	}

	if (rpoRecordsetPtr->EOF || rpoRecordsetPtr->BOF)
	{
		return false;
	}
	else
	{
		return true;
	}
}

long CADOObjServer::GetObjectsOnStmt(
	ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection,
	long TypeId, long IdObj, long nCount,
	CFlatData ** ppoFlatData, long nAbsPos)
{
	ASSERT(false);		//nieu¿ywane ?
	ASSERT(nCount == 1 && nFetchDirection == fdir_next);	//podobno tylko tak jest to wo³ane 
	//jeœli tak to mo¿liwe jest zrobienie optymalizacji

	*ppoFlatData = NULL;
	if (!_Move(rpoRecordsetPtr, nFetchDirection, nAbsPos))
	{
		return 0;
	}
	_variant_t vArrayRecors = rpoRecordsetPtr->GetRows(nCount);
	long nRecordsUB = 0;
	HRESULT hr = ::SafeArrayGetUBound(vArrayRecors.parray, 2, &nRecordsUB);
	ASSERT(hr == S_OK);
	if (nRecordsUB < 0)
	{
		return 0;
	}
#ifdef _DEBUG
	{
		long nFieldsUB = 0;
		HRESULT hr = ::SafeArrayGetUBound(vArrayRecors.parray, 1, &nFieldsUB);
		ASSERT(hr == S_OK);
	}
#endif
	//something read, now process it
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	long nFields = poStdObjDefSP->GetFieldCount();

	//retrieve field definition
	long nDataSize = (nRecordsUB + 1) * CFlatData::CFDHeader::Size();
	*ppoFlatData = new CFlatData(nDataSize, new BYTE[nDataSize], true);

	CArray<long, long&> oFieldTypesArray;
	CArray<long, long&> oFieldRelationsArray;
	oFieldTypesArray.SetSize(nFields);
	oFieldRelationsArray.SetSize(nFields);
	oFieldTypesArray[0] = (IdObj == 0) ? SQLT_INT : SQLT_IGNORE;		//for IdObj
	for (long nField = 1; nField < nFields; nField++)
	{
		SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = poStdObjDefSP->GetField(nField);
		oFieldTypesArray[nField] = rpoStdObjFieldDefSP->GetSQLType();
		oFieldRelationsArray[nField] = rpoStdObjFieldDefSP->GetRelationType();
	}
	//read results
	long rgIndices[2];
	_variant_t vResult;
	for (long iter = 0; iter <= nRecordsUB; iter++)
	{
		long nLength = 0;
		rgIndices[1] = iter;
		long nPersField;
		{
			CFlatData::CFDHeader oHeader((*ppoFlatData)->GetDataPtr());
			oHeader.Action() = action_get;
			oHeader.TypeId() = TypeId;
		}
		nLength += CFlatData::CFDHeader::Size();
		//read IdObj if necessary
		if (IdObj == 0)
		{
			rgIndices[0] = 0;
			hr = ::SafeArrayGetElement(vArrayRecors.parray, rgIndices, &vResult);
			CFlatData::CFDHeader((*ppoFlatData)->GetDataPtr()).IdObj() = (long)vResult;
			nPersField = 1;
		}
		else
		{
			ASSERT(oFieldTypesArray[0] == SQLT_IGNORE);
			ASSERT(nCount == 1);
			CFlatData::CFDHeader((*ppoFlatData)->GetDataPtr()).IdObj() = IdObj;
			nPersField = 0;
		}
		//read version
		{
			rgIndices[0] = nPersField;
			hr = ::SafeArrayGetElement(vArrayRecors.parray, rgIndices, &vResult);
			CFlatData::CFDHeader((*ppoFlatData)->GetDataPtr()).VersionId() = (long)vResult;
			nPersField++;
		}
		//to_do: optymalniej
		//to_do: dwie pêtle, najpierw zliczanie rozmiaru potem zamiana pól
		//uniknie siê realokacji po ka¿dym polu
		for (long nField = 1; nField < nFields; nField++)
		{
			if (oFieldTypesArray[nField] != SQLT_IGNORE)
			{
				rgIndices[0] = nPersField;
				hr = ::SafeArrayGetElement(vArrayRecors.parray, rgIndices, &vResult);
				nPersField++;

				//wildref is special case
				long nFieldSize = Variant2BinaryHelper(oFieldTypesArray[nField], vResult);
				Variant2BinaryHelper(oFieldTypesArray[nField], vResult, (*ppoFlatData)->GrowBy(nFieldSize));
				nLength += nFieldSize;
				if (oFieldRelationsArray[nField] == RELT_WILDREF)
				{
					rgIndices[0] = nPersField;
					hr = ::SafeArrayGetElement(vArrayRecors.parray, rgIndices, &vResult);
					nPersField++;
					long nFieldSize = Variant2BinaryHelper(SQLT_INT, vResult);
					Variant2BinaryHelper(SQLT_INT, vResult, (*ppoFlatData)->GrowBy(nFieldSize));
					nLength += nFieldSize;
				}
			}
		}
		CFlatData::CFDHeader((*ppoFlatData)->GetDataPtr()).Length() = nLength;
	}

	//update GLOB_CACHE
	{
		CFlatDataIterator oFlatDataIterator(**ppoFlatData);
		ASSERT(m_poFDObjectCacheSP.PointsObject());
		CSimpleLock oSimpleLock(m_poFDObjectCacheSP->CriticalSection());

		while (1)
		{
			CFlatData oRecordFlatData;
			bool bMore = oFlatDataIterator.GetNext(oRecordFlatData);
			CFlatData::CFDHeader oFDHeader(oRecordFlatData);
			SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(oFDHeader.TypeId());
			ASSERT(poStdObjDefSP);
			if (!poStdObjDefSP->IsVolatile() && poStdObjDefSP->IsCacheOnServer())
			{
				SCP<CFlatData> poFlatDataSP = NewSCP(new CFlatData());
				memcpy(poFlatDataSP->GrowBy(oRecordFlatData.GetDataLen()),
					oRecordFlatData.GetDataPtr(), oRecordFlatData.GetDataLen());
				ASSERT(m_poFDObjectCacheSP.PointsObject());
				m_poFDObjectCacheSP->Set(oFDHeader.TypeId(), oFDHeader.IdObj(), poFlatDataSP);
			}
			if (!bMore)
			{
				break;
			}
		}
	}
	return 1 + nRecordsUB;
}

long CADOObjServer::GetIdentsOnStmt(ADODB::_RecordsetPtr & rpoRecordsetPtr, fetchdirection nFetchDirection,
	long nCount, CFlatData ** ppoFlatData, long nAbsPos)
{
	*ppoFlatData = NULL;
	if (!_Move(rpoRecordsetPtr, nFetchDirection, nAbsPos))
	{
		return 0;
	}
	_variant_t vArrayRecors = rpoRecordsetPtr->GetRows(nCount);
	long nRecordsUB = 0;
	HRESULT hr = ::SafeArrayGetUBound(vArrayRecors.parray, 2, &nRecordsUB);
	ASSERT(hr == S_OK);
	if (nRecordsUB < 0)
	{
		return 0;
	}
	long nDataSize = CFlatData::CFDHeader::Size() + sizeof(long) +
		(nRecordsUB + 1) * sizeof(long);
	*ppoFlatData = new CFlatData(nDataSize, new BYTE[nDataSize], true);
	CFlatData::CFDHeader oHeader(**ppoFlatData);
	oHeader.Action() = action_lists;
	oHeader.TypeId() = TYPEID_COLLECTIONS;
	oHeader.IdObj() = nRecordsUB + 1;
	oHeader.Length() = nDataSize;

	PBYTE pMem = (*ppoFlatData)->GetDataPtr() + CFlatData::CFDHeader::Size();
	*reinterpret_cast<stdobjlistoperations*>(pMem) = listop_getid;
	pMem += sizeof(long);
	//read results
	long rgIndices[2];
	rgIndices[0] = 0;

	_variant_t vResult;
	for (long iter = 0; iter <= nRecordsUB; iter++)
	{
		rgIndices[1] = iter;
		hr = ::SafeArrayGetElement(vArrayRecors.parray, rgIndices, &vResult);
#ifdef _DEBUG
		ASSERT(Variant2BinaryHelper(SQLT_INT, vResult) == sizeof(long));
#endif
		Variant2BinaryHelper(SQLT_INT, vResult, pMem);
		pMem += sizeof(long);
	}
	return 1 + nRecordsUB;
}

bool CADOObjServer::GetObject(long TypeId, long IdObj, CFlatData ** ppoFlatData)
{
	ASSERT(IdObj != 0);
	*ppoFlatData = NULL;
	//_crtDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF;

	Login(false);

	long nLength = CFlatData::CFDHeader::Size();
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);

	bool bResult = false;
	switch (m_EngineType)
	{
	case dbet_ms_jet35:
		bResult = _get_object_msjet(TypeId, IdObj, ppoFlatData, nLength, poStdObjDefSP);
		break;
	case dbet_ms_sql70:
	case dbet_ms_sql2000:
		bResult = _get_object_mssql(TypeId, IdObj, ppoFlatData, nLength, poStdObjDefSP);
		break;
	default:
		ASSERT(false);
	}
	if (!bResult)
	{
		return false;
	}

	CFlatData::CFDHeader((*ppoFlatData)->GetDataPtr()).Length() = nLength;

	//update GLOB_CACHE
	if (!poStdObjDefSP->IsVolatile() && poStdObjDefSP->IsCacheOnServer())
	{
		ASSERT(m_poFDObjectCacheSP.PointsObject());
		CSimpleLock oSimpleLock(m_poFDObjectCacheSP->CriticalSection());

		ASSERT((*ppoFlatData)->GetDataLen() == nLength);
		SCP<CFlatData> poFlatDataSP = NewSCP(new CFlatData());
		memcpy(poFlatDataSP->GrowBy(nLength), (*ppoFlatData)->GetDataPtr(), nLength);
		m_poFDObjectCacheSP->Set(TypeId, IdObj, poFlatDataSP);
	}
	return true;
}

/*
	stara wersja do wykorzystania z _selectrs
bool CADOObjServer::GetObject(long TypeId,long IdObj,CFlatData ** poFlatData)
{
	Login();
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddInParam(SQLT_INT,(LPVOID)&IdObj);
	ADODB::_RecordsetPtr poRecordSetPtr = oCommand.ExecProc(
		poStdObjDefSP->GetTableName() + ProcedureSuffixOnAction(action_get),false);
	if(GetObjectsOnStmt(poRecordSetPtr,fdir_next,TypeId,IdObj,1,poFlatData) == 0)
	{
		return false;
	}
#ifdef _DEBUG
	{
		CFlatData::CFDHeader oHeader((*poFlatData)->GetDataPtr());
		ASSERT(oHeader.IdObj() == IdObj);	//czy wczytalismy to co chcielismy ?
	}
#endif
	return true;
}
*/


void CADOObjServer::GetMaxIdObj(long TypeId, long & nMaxIdObj)
{
	//pseudo type FILE is special case
	if (TypeId == TYPEID_FILE)
	{
		HRESULT hr = m_poCachedDataSP->GetUniqueIdent(&nMaxIdObj);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_OBJSERV_GETUIQID_FILE, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
	}
	else
	{
		Login(false);
		ASSERT(m_poFDObjectCacheSP.PointsObject());
		CSimpleLock oSimpleLock(m_poFDObjectCacheSP->CriticalSection());
		if (!m_poFDObjectCacheSP->GetMaxIdObj(TypeId, nMaxIdObj))
		{
			SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);

			//dla obiektów <virtual> rozpoczynamy od 1
			if (poStdObjDefSP->IsVolatile())
			{
				nMaxIdObj = 0;
			}
			else
			{
				//not found in map
				Login(false);
				switch (m_EngineType)
				{
				case dbet_ms_jet35:
					_get_max_idobj_msjet(TypeId, nMaxIdObj);
					break;
				case dbet_ms_sql70:
				case dbet_ms_sql2000:
					_get_max_idobj_mssql(TypeId, nMaxIdObj);
					break;
				default:
					ASSERT(false);
				}
			}
		}
		m_poFDObjectCacheSP->SetMaxIdObj(TypeId, ++nMaxIdObj);
	}
}


ADODB::_RecordsetPtr CADOObjServer::OpenDiscoRecSet(LPCTSTR lpSQLClause)
{
	Login(false);

#ifdef _VERSION_WITHOUT_COMMAND_TIMEOUT_
	ADODB::_RecordsetPtr poRecordsetPtr;
	poRecordsetPtr.CreateInstance("ADODB.Recordset");
	poRecordsetPtr->CursorLocation = ADODB::adUseClient;
	poRecordsetPtr->Open(_bstr_t(lpSQLClause), m_poConnectionPtr.GetInterfacePtr(),
		ADODB::adOpenForwardOnly,
		ADODB::adLockReadOnly,
		ADODB::adCmdUnspecified);
#else
	--
		--problem polega na tym, ze nie mozna zmieniac ActiveConnection gdy recordset
		-- ma za zrodlo Command - prawdopodobnie nie mozna zrobic disconnected
		--

		CADOCommand oCommand(m_poConnectionPtr);
	oCommand.set_cmdtxt(lpSQLClause);
	oCommand.set_timeout(300);

	ADODB::_RecordsetPtr poRecordsetPtr;
	poRecordsetPtr.CreateInstance("ADODB.Recordset");
	poRecordsetPtr->CursorLocation = ADODB::adUseClient;
	poRecordsetPtr->Open(oCommand.get_command_ptr(), vtMissing,
		ADODB::adOpenForwardOnly,
		ADODB::adLockReadOnly,
		ADODB::adCmdUnspecified);
#endif

	//make disconnected
	poRecordsetPtr->PutRefActiveConnection(NULL);
	return poRecordsetPtr;
}

LPCTSTR FindWhereSelect();
LPCTSTR FindSelect();

void CADOObjServer::Find(long TypeId, LPCTSTR lpWhereClause, long & rFoundId)
{
	if (g_oLog.IsHandleValid())
	{
		g_oLog << "entering  CADOObjServer::Find " + CString(lpWhereClause);
	}

	Login(false);
	CADOCommand oCommand(m_poConnectionPtr);
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	CString oSQLString;
	if (lpWhereClause != NULL && !IsWhiteSpaceOnly(lpWhereClause))
	{
		oSQLString.Format(FindWhereSelect(), poStdObjDefSP->GetTableName(), lpWhereClause);
	}
	else
	{
		oSQLString.Format(FindSelect(), poStdObjDefSP->GetTableName());
	}

	ADODB::_RecordsetPtr poRecordsetPtr = oCommand.ExecDirect(oSQLString, false);
	if (poRecordsetPtr->BOF || poRecordsetPtr->EOF)
	{
		if (g_oLog.IsHandleValid())
		{
			g_oLog << "no results  CADOObjServer::Find " + CString(lpWhereClause);
		}

		rFoundId = 0;
		return;
	}
	//at least one exists
	_variant_t vIndex = long(0);
	ADODB::FieldPtr poFieldPtr = poRecordsetPtr->Fields->GetItem(vIndex);
	rFoundId = poFieldPtr->GetValue().lVal;
	//test czy wiêcej ni¿ jeden
	poRecordsetPtr->MoveNext();
	if (!poRecordsetPtr->EOF)
	{
		rFoundId = -1;
	}

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "exiting CADOObjServer::Find " + CString(lpWhereClause);
	}
}

bool CADOObjServer::LockSingleObject(long TypeId, long IdObj, bool bReadLock, bool bLock)
{
	ASSERT(m_poLockManagerSP.PointsObject());

	navolock oNLI;
	oNLI.m_type = bReadLock ? nlt_shlock : nlt_exlock;
	oNLI.m_fullid.m_class = LOCKCLASS_OBJECT;
	oNLI.m_fullid.m_typeid = TypeId;
	oNLI.m_fullid.m_idobj = IdObj;
	oNLI.m_fullid.m_extra = 0;

	HRESULT hr = m_poLockManagerSP->Lock(m_nLockManCookie, BYTE(bLock), 1, &oNLI);
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowNavoException3(ERCO_OBJSERV_SINGLE_LOCK_FAILED, IDPAGE_NOTAVAILABLE, TypeId, IdObj, SCODE_To_String(hr));
	}
	if (hr == S_OK)
	{
		return true;
	}
	CNavoException oNavoException;
	GetErrorInfoFromInterface(m_poLockManagerSP, oNavoException);
	GetErrorStorage() += oNavoException;
	return false;
}


long CADOObjServer::ExecSQL(LPCTSTR lpSQLCommand)
{
	Login(false);
	CADOCommand oADOCommand(m_poConnectionPtr);
	oADOCommand.set_timeout(3000);
	oADOCommand.ExecDirect(lpSQLCommand, true);
	return oADOCommand.GetRecordsAffected();
}

void CADOObjServer::OnObjectCollection_FinalRelease(CObjectCollectionImpl * /*poCursor*/)
{
	//current implementation makes nothing
}

//-----------------------------------------------------------
//		<file> related operations
//-----------------------------------------------------------
void CADOObjServer::ComposeCacheName(CString & roString)
{
	ASSERT(!m_oEffectiveServerString.IsEmpty());
	roString = "<database>:" + m_oEffectiveServerString + ":" + m_oDBString;
}

LPCTSTR InsertFileCacheGUID();
LPCTSTR GetFileCacheGUID();

void CADOObjServer::CheckFileCacheGUID(bool bMustExistInDB, const CString & roPseudoServerString)
{
	if (roPseudoServerString == m_oComposedCacheNameString)
	{
		return;
	}
	//pobierz guid z cache'a
	ASSERT(m_poCachedDataSP.PointsObject());
	GUID oTmpGUID;
	HRESULT hr = m_poCachedDataSP->GetCacheInfoGUID(roPseudoServerString, &oTmpGUID);
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowNavoException2(ERCO_OBJSERV_GET_CACHE_GUID_FAILED, IDPAGE_NOTAVAILABLE,
			(LPCTSTR)roPseudoServerString, SCODE_To_String(hr));
	}
	if (hr == S_FALSE)
	{
		ASSERT(false);	//jeszcze nie ma takiego cache info - z³e wywo³anie w CADOObjServer
		if (bMustExistInDB)
		{
			ThrowNavoException(ERCO_OBJSERV_CACHE_MISSING_IN_CACHE, IDPAGE_NOTAVAILABLE);
		}
		return;
	}
	CString oTmpGUIDString = StringFromCLSID(oTmpGUID);
	//pobierz guid z DB
	CString oDBGUIDString = "";
	{
		CADOCommand oCommand(m_poConnectionPtr);
		oCommand.AddInParam(SQLT_VARCHAR(512), (LPVOID)(LPCTSTR)roPseudoServerString);
		oCommand.AddOutParam(SQLT_VARCHAR(512));
		oCommand.ExecProc(GetFileCacheGUID(), false);
		ASSERT(oCommand.GetOutParam(0).Type() == VT_NULL || oCommand.GetOutParam(0).Type() == VT_BSTR);
		if (oCommand.GetOutParam(0).Type() == VT_BSTR)
		{
			oDBGUIDString = oCommand.GetOutParam(0).GetBStr();
			oDBGUIDString.TrimRight();
		}
		else if (bMustExistInDB)
		{
			ThrowNavoException(ERCO_OBJSERV_CACHE_GUID_MISSING_INDB, IDPAGE_NOTAVAILABLE);
		}
	}

	if (!oDBGUIDString.IsEmpty())	//jeœli jest musi siê zgadzaæ
	{
		if (oDBGUIDString == oTmpGUIDString)
		{
			m_oComposedCacheNameString = roPseudoServerString;
			return;
		}

		ThrowNavoException(ERCO_OBJSERV_CACHE_GUID_MISMATCH, IDPAGE_NOTAVAILABLE);
	}

	//insert DB with guid
	ASSERT(!bMustExistInDB);
	oDBGUIDString = oTmpGUIDString;
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddInParam(SQLT_VARCHAR(512), (LPVOID)(LPCTSTR)roPseudoServerString);
	oCommand.AddInParam(SQLT_VARCHAR(512), (LPVOID)(LPCTSTR)oDBGUIDString);
	oCommand.ExecProc(InsertFileCacheGUID(), true);
	m_oComposedCacheNameString = roPseudoServerString;
}

SCP <IStream> CADOObjServer::GetFile(long IdParent, long IdMapping, navostreaminfo * poNSI,
	long *pVersion, long * pStreamId)
{
	*pStreamId = ExecSelStreamMap(IdParent, IdMapping, *pVersion);
	if (*pStreamId == 0)
	{
		return SCP <IStream>();
	}
	ASSERT(m_poCachedDataSP.PointsObject());

	CString oPseudoServerString;
	ComposeCacheName(oPseudoServerString);
	CheckFileCacheGUID(true, oPseudoServerString);

	SCP<IStream> poStreamSP;
	HRESULT hr = m_poCachedDataSP->GetItem(*pStreamId, oPseudoServerString, 0, NULL, &poStreamSP.GetRawPointer(), poNSI);
	if (hr == S_OK)
	{
		return poStreamSP;
	}
	ThrowNavoException2(ERCO_OBJSERV_GETFILE_FAILED, IDPAGE_NOTAVAILABLE, *pStreamId, SCODE_To_String(hr));
}

void CADOObjServer::StoreFile(long IdParent, long IdMapping, SCP<IStream> & rpoStreamSP, navostreaminfo * poNSI)
{
	long nVersion = -1;
	long nIdStream = ExecSelStreamMap(IdParent, IdMapping, nVersion);
	if (nIdStream == 0)
	{
		GetMaxIdObj(TYPEID_FILE, nIdStream);
		ASSERT(nIdStream != 0);
		ExecInsStreamMap(nIdStream, IdParent, IdMapping);
	}
	else
	{
		ASSERT(nVersion >= 1);
		nVersion++;
		ExecUpdStreamMap(IdParent, IdMapping, nVersion);
	}
	ASSERT(nIdStream != 0);
	ASSERT(m_poCachedDataSP.PointsObject());
	ASSERT(m_poCurrentTHSP.PointsObject());
	long nFileTransactionId = m_poCurrentTHSP->GetFileTransactionId();
	if (nFileTransactionId == 0)
	{
		HRESULT hr = m_poCachedDataSP->BeginTransaction(&nFileTransactionId);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_OBJSERV_BEGIN_FILE_TRANS_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		m_poCurrentTHSP->SetFileTransactionId(nFileTransactionId);
	}
	ASSERT(nFileTransactionId != 0);

	CString oPseudoServerString;
	ComposeCacheName(oPseudoServerString);

	SCP<IStream> poCachedStreamSP;
	HRESULT hr = m_poCachedDataSP->StoreItem(nIdStream, oPseudoServerString, 0, NULL, nFileTransactionId,
		poNSI, &poCachedStreamSP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowNavoException2(ERCO_OBJSERV_STOREFILE_FAILED, IDPAGE_NOTAVAILABLE, nIdStream, SCODE_To_String(hr));
	}
	ULARGE_INTEGER ulInfinity;
	ulInfinity.QuadPart = MAXLONG;
	CStreamHolder(rpoStreamSP).SeekToBegin();
	hr = rpoStreamSP->CopyTo(poCachedStreamSP, ulInfinity, NULL, NULL);
	if (hr != S_OK)
	{
		ThrowNavoException2(ERCO_OBJSERV_STOREFILE_FAILED2, IDPAGE_NOTAVAILABLE, nIdStream, SCODE_To_String(hr));
	}
	CheckFileCacheGUID(false, oPseudoServerString);
}

void CADOObjServer::RemoveFile(long IdParent, long IdMapping)
{
	long nVersion;
	long nIdStream = ExecSelStreamMap(IdParent, IdMapping, nVersion);
	if (nIdStream != 0)
	{
		ASSERT(nIdStream != 0);
		ExecDelStreamMap(IdParent, IdMapping);

		ASSERT(m_poCachedDataSP.PointsObject());
		ASSERT(m_poCurrentTHSP.PointsObject());
		long nFileTransactionId = m_poCurrentTHSP->GetFileTransactionId();
		if (nFileTransactionId == 0)
		{
			HRESULT hr = m_poCachedDataSP->BeginTransaction(&nFileTransactionId);
			if (hr != S_OK)
			{
				ThrowNavoException1(ERCO_OBJSERV_BEGIN_FILE_TRANS_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
			}
			m_poCurrentTHSP->SetFileTransactionId(nFileTransactionId);
		}
		ASSERT(nFileTransactionId != 0);

		CString oPseudoServerString;
		ComposeCacheName(oPseudoServerString);
		CheckFileCacheGUID(true, oPseudoServerString);

		HRESULT hr = m_poCachedDataSP->RemoveItem(nIdStream, oPseudoServerString, 0, NULL, nFileTransactionId);
		if (hr != S_OK)
		{
			ThrowNavoException2(ERCO_OBJSERV_DELETEFILE_FAILED, IDPAGE_NOTAVAILABLE, nIdStream, SCODE_To_String(hr));
		}
	}
}

HRESULT CADOObjServer::CommitFiles(long nFileTransactionId)
{
	ASSERT(m_poCachedDataSP.PointsObject());
	ASSERT(m_poCurrentTHSP.PointsObject());
	ASSERT(nFileTransactionId != 0);

	return m_poCachedDataSP->FinishTransaction(nFileTransactionId, BYTE(true));
}

HRESULT CADOObjServer::RollbackFiles(long nFileTransactionId)
{
	ASSERT(m_poCachedDataSP.PointsObject());
	ASSERT(m_poCurrentTHSP.PointsObject());
	ASSERT(nFileTransactionId != 0);

	return m_poCachedDataSP->FinishTransaction(nFileTransactionId, BYTE(false));
}

SCP<CObjectCollectionImpl> CADOObjServer::MakeFTSQuery(long IdMapping, LPCSTR lpQuery)
{
	ASSERT(m_poCachedDataSP.PointsObject());
	SCP<ISimpleEnumId> poSimpleEnumIdSP;

	CString oPseudoServerString;
	ComposeCacheName(oPseudoServerString);

	HRESULT hr = m_poCachedDataSP->FTSQuery(oPseudoServerString, lpQuery,
		&poSimpleEnumIdSP.GetRawPointer());

	if (hr != S_OK)
	{
		return SCP<CObjectCollectionImpl>();
	}
	SCP<CObjectCollectionImpl> poObjectCollectionImplSP = NewSCP(new CObjectCollectionImpl(this));
	poObjectCollectionImplSP->OpenOnFTSQueryResults(IdMapping, poSimpleEnumIdSP);

	return poObjectCollectionImplSP;
}

//-----------------------------------------------------------
//
//		object collection
//
//-----------------------------------------------------------
LPCTSTR OpenCollectionSelect();

void CObjectCollectionImpl::OnFinalRelease()
{
	ASSERT(m_poObjectServer);
	m_poObjectServer->OnObjectCollection_FinalRelease(this);
	delete this;
}

bool CObjectCollectionImpl::_requery(long nPositionToKeep, long * pnCount)
{
	ASSERT(m_poRecordsetPtr != NULL);
	ASSERT(m_poObjectServer);

	bool bResult = m_poObjectServer->_Move(m_poRecordsetPtr, fdir_abs, nPositionToKeep);
	_variant_t vBookmark;
	if (bResult)
	{
		if (!m_poRecordsetPtr->BOF && !m_poRecordsetPtr->EOF)
		{
			vBookmark = m_poRecordsetPtr->Bookmark;
		}
	}
	m_poRecordsetPtr->Requery(ADODB::adCmdText);
	if (bResult)
	{
		if (V_VT(&vBookmark) != VT_EMPTY)
		{
			try
			{
				m_poRecordsetPtr->Bookmark = vBookmark;
			}
			catch (_com_error e)
			{
				HRESULT hr = e.Error();
				if (hr != 0x80040E0E)	//Invalid bookmark
				{
					throw;	//throw any other errors
				}
				//ignore invalid bookmark
			}
		}
	}

	m_nTotalCount = m_poRecordsetPtr->GetRecordCount();
	if (pnCount != NULL)
	{
		*pnCount = m_nTotalCount;
	}
	return bResult;
}

void CObjectCollectionImpl::OpenCollection(long CollectionId, long  IdParent, long * pTotalCount)
{
	m_poObjectServer->Login(false);
	m_poRecordsetPtr.CreateInstance("ADODB.Recordset");
	m_poRecordsetPtr->CursorLocation = ADODB::adUseClient;
	CString oCommandString;
	oCommandString.Format(OpenCollectionSelect(), CollectionId, IdParent);
	m_poRecordsetPtr->Open(_bstr_t(oCommandString),
		m_poObjectServer->m_poConnectionPtr.GetInterfacePtr(),
		ADODB::adOpenStatic,
		ADODB::adLockReadOnly,
		ADODB::adCmdText);
	m_poRecordsetPtr->PutRefActiveConnection(NULL);

	if (pTotalCount)
	{
		*pTotalCount = m_poRecordsetPtr->GetRecordCount();
		ASSERT(*pTotalCount != -1);	//database must have this capability
	}
}

void CObjectCollectionImpl::OpenOnStatement(long TypeId,
	LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause, LPCTSTR lpJoinClause, bool bForwardOnly, long nTop)
{
	//prepare command text
	CString oCommandString;
	SCP<CStdObjDef> poStdObjDefSP = m_poObjectServer->m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	CString oTopString;
	if (nTop != 0)
	{
		oTopString.Format(_T("top %d"), nTop);
	}
	oCommandString.Format(_T("select %s %s.IdObj from %s"), oTopString, poStdObjDefSP->GetTableName(), poStdObjDefSP->GetTableName());
	if (lpJoinClause != NULL && _tcslen(lpJoinClause))
	{
		oCommandString += _T(" join ") + CString(lpJoinClause);
	}
	if (lpWhereClause != NULL && _tcslen(lpWhereClause))
	{
		oCommandString += _T(" where ") + CString(lpWhereClause);
	}
	if (lpOrderByClause != NULL && _tcslen(lpOrderByClause))
	{
		oCommandString += _T(" order by ") + CString(lpOrderByClause);
	}

	//login and init
	m_poObjectServer->Login(false);
	m_poRecordsetPtr.CreateInstance(_T("ADODB.Recordset"));

	if (bForwardOnly)
	{
		//open in fast forward only mode, disconnected recordset
		m_poRecordsetPtr->CursorLocation = ADODB::adUseClient;
		m_poRecordsetPtr->CacheSize = 1;
		m_poRecordsetPtr->Open(_bstr_t(oCommandString),
			m_poObjectServer->m_poConnectionPtr.GetInterfacePtr(),
			ADODB::adOpenForwardOnly,
			ADODB::adLockReadOnly,
			ADODB::adCmdText);
		m_poRecordsetPtr->PutRefActiveConnection(NULL);
	}
	else
	{
		//open in browseable mode / updatable etc.
		m_poRecordsetPtr->CursorLocation = ADODB::adUseClient;
		m_poRecordsetPtr->PutActiveConnection(_variant_t(m_poObjectServer->m_poConnectionPtr, true));
		//		m_poRecordsetPtr->Properties->Item["Preserve on Commit"]->Value = true;
		//		m_poRecordsetPtr->Properties->Item["Preserve on Abort"]->Value = true;
		m_poRecordsetPtr->Properties->Item["Remove Deleted Rows"]->Value = true;
		m_poRecordsetPtr->CacheSize = 1;
		m_poRecordsetPtr->Open(_bstr_t(oCommandString),
			vtMissing,
			ADODB::adOpenStatic,
			ADODB::adLockOptimistic,
			ADODB::adCmdText);
	}
}

LPCTSTR OpenStreamSelect();

void CObjectCollectionImpl::OpenOnFTSQueryResults(long IdMapping, SCP<ISimpleEnumId> poSimpleEnumIdSP)
{
	ASSERT(poSimpleEnumIdSP.PointsObject());

	m_poObjectServer->Login(false);
	m_poRecordsetPtr.CreateInstance("ADODB.Recordset");
	m_poRecordsetPtr->CursorLocation = ADODB::adUseClient;

	CString oIdStreamListString;
	while (true)
	{
		long IdFile;
		HRESULT hr = poSimpleEnumIdSP->Next(&IdFile);
		if (hr != S_OK)
		{
			break;
		}
		oIdStreamListString += "," + Long2String(IdFile);
	}

	CString oCommandString;
	oCommandString.Format(OpenStreamSelect(), IdMapping, oIdStreamListString);
	m_poRecordsetPtr->Open(_bstr_t(oCommandString),
		m_poObjectServer->m_poConnectionPtr.GetInterfacePtr(),
		ADODB::adOpenStatic,
		ADODB::adLockReadOnly,
		ADODB::adCmdText);
	m_poRecordsetPtr->PutRefActiveConnection(NULL);
}

//-----------------------------------------------------------
//-----------------------------------------------------------

//-------------------------------------------------------------------------


void CADOObjServer::_get_ADO_errors(CNavoException & roErrorStorage)
{
	if (m_poConnectionPtr)
	{
		long nErrorCount = m_poConnectionPtr->Errors->Count;
		for (long iter = 0; iter < nErrorCount; iter++)
		{
			ADODB::ErrorPtr poErrorPtr = m_poConnectionPtr->Errors->GetItem(_variant_t(long(iter)));
			if (poErrorPtr)
			{
				_bstr_t bstrDescription = poErrorPtr->Description;
				_bstr_t bstrSource = poErrorPtr->Source;
				long nNumber = poErrorPtr->Number;
				long nNative = poErrorPtr->NativeError;
				CString oErrorMsgString;
				oErrorMsgString.Format("%s [%d][%d] %s", (LPCTSTR)bstrDescription, nNumber, nNative,
					(LPCTSTR)bstrSource);
				roErrorStorage += CNavoErrorInfo(ERCO_ADO_ERROR, IDPAGE_NOTAVAILABLE, oErrorMsgString);
			}
		}
	}
}

HRESULT CADOObjServer::_backup_database(LPCSTR lpSAUser, LPCSTR lpPwd, SCP<IStream> poArchiveStreamSP)
{
	//------------ logoff -----
	Logoff();
	CString oDBString = m_oDBString;
	CString oUserString = m_oUserString;
	CString oPwdString = m_oPwdString;

	m_oDBString = "master";
	m_oUserString = lpSAUser;
	m_oPwdString = lpPwd;
	Login(true);

	//------------ create backup to file -----
	CADOCommand oCommand(m_poConnectionPtr);
	CString oFileNameString = GenerateUniqueFileName(_T("BK"), _T("TMP"));
	CFileRemover oFileRemover(oFileNameString);
	CString oSQLString = "backup database " + oDBString + " to disk='" + oFileNameString + "'";
	oCommand.set_timeout(1000);
	oCommand.ExecDirect(oSQLString, true);

	//--- copy database backup to destination backup stream ------
	SCP<IStream> poDBStreamSP = OpenFileStream_Read(oFileNameString);
	__int64 iStreamSize = get_stream_size64(poDBStreamSP);

	//write header: length
	//for compatibility write (long)0 as marker of new format
	{
		CStreamHolder oSH(poArchiveStreamSP);
		long lZero = 0L;
		oSH.Write(&lZero, sizeof(lZero));
		oSH.Write(&iStreamSize, sizeof(iStreamSize));
	}

	ULARGE_INTEGER ulInfinity;
	ulInfinity.QuadPart = MAXLONGLONG;

	//poDBStreamSP = CompressStream(poDBStreamSP);

	HRESULT hr = IStream_CopyTo(poDBStreamSP, poArchiveStreamSP, ulInfinity);
	if (hr != S_OK)
	{
		return hr;
	}

	//--- restore login ---
	Logoff();
	m_oDBString = oDBString;
	m_oUserString = oUserString;
	m_oPwdString = oPwdString;
	Login(false);

	return S_OK;
}

LPCSTR _glp_mssql_after_restore_script =
"use master\r\n"
"\r\n"
"set implicit_transactions off\r\n"
"\r\n"
"if exists (select * from sysusers where name = N'navo2002user' and uid < 16382)\r\n"
"	exec sp_revokedbaccess N'navo2002user'\r\n"
"\r\n"
"exec sp_grantdbaccess N'navo2002user', N'navo2002user'\r\n"
"\r\n"
"exec n2001_makegrants 'navo2002user'\r\n"
"\r\n"
"checkpoint\r\n"
"\r\n"
"use %s\r\n"
"\r\n"
"if exists (select * from sysusers where name = N'navo2002user' and uid < 16382)\r\n"
"	exec sp_revokedbaccess N'navo2002user'\r\n"
"\r\n"
"exec sp_grantdbaccess N'navo2002user', N'navo2002user'\r\n"
"\r\n"
"exec sp_addsrvrolemember 'navo2002user','dbcreator'\r\n"
"\r\n"
"exec sp_addrolemember 'db_owner','navo2002user'\r\n"
"\r\n"
"exec n2001_makegrants 'navo2002user'\r\n"
"\r\n"
"set implicit_transactions on\r\n"
"\r\n"
;

LPCSTR _glp_mssql_update_fcdbid =
""
"set implicit_transactions off\r\n"
"\r\n"
"use %s\r\n"
"\r\n"
"update FCDBId set strDBID='%s'\r\n"
"\r\n"
"set implicit_transactions on\r\n"
"\r\n"
;

HRESULT CADOObjServer::_restore_database(LPCSTR lpSAUser, LPCSTR lpPwd,
	const CString & roPseudoServerString, SCP<IStream> poArchiveStreamSP)
{
	//copy database backup part from archive stream to temporary file
	__int64 iStreamSize = 0;
	{
		long lTestSize;
		CStreamHolder oSH(poArchiveStreamSP);
		oSH.Read(&lTestSize, sizeof(lTestSize));
		if (lTestSize != 0)
		{
			iStreamSize = lTestSize;
		}
		else
		{
			oSH.Read(&iStreamSize, sizeof(iStreamSize));
		}
	}

	CString oFileNameString = GenerateUniqueFileName(_T("BK"), _T("TMP"));
	CFileRemover oFileRemover(oFileNameString);

	{
		SCP<IStream> poTempStreamSP = CreateFileStream_Write(oFileNameString);
		ULARGE_INTEGER ulLength;
		ulLength.QuadPart = iStreamSize;
		//poArchiveStreamSP = UncompressStream(poArchiveStreamSP);
		HRESULT hr = IStream_CopyTo(poArchiveStreamSP, poTempStreamSP, ulLength);
		if (hr != S_OK)
		{
			return hr;
		}
	}

	Logoff();
	CString oDBString = m_oDBString;
	CString oUserString = m_oUserString;
	CString oPwdString = m_oPwdString;

	m_oDBString = "master";
	m_oUserString = lpSAUser;
	m_oPwdString = lpPwd;
	Login(true);

	//perform database restore
	CString oRestoreSQLString = "restore database " + oDBString + " from disk='" + oFileNameString + "' with ";
	CString oRootString;
	SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot", oRootString);
	EnsureEndingBackslash(oRootString);
	oRootString += "Database\\";
	//	dim strInstRoot: strInstRoot = sysobj.registry(hKey_LocalMachine,"SOFTWARE\NAVO\NAVO2002\Setup",)

	{
		CADOCommand oRestoreFileListCmd(m_poConnectionPtr);
		ADODB::_RecordsetPtr poRecordsetPtr = oRestoreFileListCmd.ExecDirect(
			"restore filelistonly from disk='" + oFileNameString + "'", false);

		while (!poRecordsetPtr->EOF)
		{
			//at least one exists
			_variant_t vIndex = long(0);
			CString oLogicalNameString = poRecordsetPtr->Fields->GetItem(vIndex)->GetValue().bstrVal;
			vIndex = long(1);
			CString oPhisycalNameString = poRecordsetPtr->Fields->GetItem(vIndex)->GetValue().bstrVal;
			int nBSPos = oPhisycalNameString.ReverseFind('\\');
			oPhisycalNameString = oPhisycalNameString.Mid(nBSPos + 1, oPhisycalNameString.GetLength() - nBSPos - 1);

			CString oFileNameString = oRootString + oPhisycalNameString;
			oRestoreSQLString += " move '" + oLogicalNameString + "' to '" + oFileNameString + "',";

			poRecordsetPtr->MoveNext();
		}
	}
	oRestoreSQLString = oRestoreSQLString + " replace";
	{
		CADOCommand oRestoreCommand(m_poConnectionPtr);
		oRestoreCommand.set_timeout(1000);
		CString oSQLString = oRestoreSQLString;
		oRestoreCommand.ExecDirect(oSQLString, true);
	}

	//apply login and grants
	{
		CADOCommand oLoginAndGrantsCommand(m_poConnectionPtr);
		CString oSQLString;
		oSQLString.Format(_glp_mssql_after_restore_script, oDBString);
		oLoginAndGrantsCommand.ExecDirect(oSQLString, true);
	}

	//update fcdbid
	{
		CADOCommand oUpdateFCDBIDCommand(m_poConnectionPtr);
		CString oSQLString;
		oSQLString.Format(_glp_mssql_update_fcdbid, oDBString, roPseudoServerString);

		oUpdateFCDBIDCommand.ExecDirect(oSQLString, true);
	}


	Logoff();
	m_oDBString = oDBString;
	m_oUserString = oUserString;
	m_oPwdString = oPwdString;
	Login(false);
	m_poFDObjectCacheSP->Flush();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//NAVODB_Global * _g_poNAVODB_Global;
//
//void NAVODB_Global_initialize()
//{
//	_g_poNAVODB_Global = new NAVODB_Global();
//	_g_poNAVODB_Global->_init_Store_Hub();
//}
//
//void NAVODB_Global_done()
//{
//	_g_poNAVODB_Global->_done_Store_Hub();
//	delete _g_poNAVODB_Global;
//	_g_poNAVODB_Global = NULL;
//}
//
//NAVODB_Global::NAVODB_Global()
//{
//
//}
//
//void NAVODB_Global::_init_Store_Hub()
//{
//	ASSERT(m_poStoreHubSP.PointsNull());
//
//	CLSID oCLSID;
//	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(_T("nxm.biz.store.store_manager_hub")), &oCLSID);
//	if (hr != S_OK)
//	{
//		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
//	}
//	m_poStoreHubSP.CreateInstance(oCLSID, CLSCTX_INPROC_SERVER);
//}
//
//void NAVODB_Global::_done_Store_Hub()
//{
//	if (m_poStoreHubSP.PointsNull())
//	{
//		return;
//	}
//
//	m_poStoreHubSP = 0;
//}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
