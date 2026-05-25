/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	Object Server (on ADO)
	MS SQL specific part
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

//wstaw œcie¿kê do miejsca gdzie jest zainstalowany SQL Server i ta biblioteka
#import "..\lib\sqldmo.rll"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR ProcedureSuffixOnAction(stdobjactions Action);

LPCTSTR DelCollectionProcedure();
LPCTSTR MakeOrderCollectionProcedure();
LPCTSTR MakeSpaceCollectionProcedure();
LPCTSTR DelFromCollectionProcedure();
LPCTSTR InsertIntoCollectionProcedure();

static void ensure_start_sql_server(const CString & roServerNameString,
	const CString & roUserNameString, const CString & roPwdString)
{
	return;

	try
	{
		SQLDMO::_SQLServerPtr	poSQLServer;
		poSQLServer.CreateInstance("sqldmo.sqlserver");

		poSQLServer->Start(TRUE, _bstr_t(roServerNameString),
			_bstr_t(roUserNameString), _bstr_t(roPwdString));
	}
	catch (_com_error e)
	{
		if (HRESULT_CODE(e.Error()) == ERROR_SERVICE_ALREADY_RUNNING)
		{
			return;	//that's OK
		}
		if (HRESULT_CODE(e.Error()) == ERROR_ACCESS_DENIED)
		{
			return;	//give up
		}

		throw;
	}
}

bool _is_TransactionMode2020();

void CADOObjServer::_login_mssql()
{
	ASSERT(m_EngineType == dbet_ms_sql70 || m_EngineType == dbet_ms_sql2000);
	m_poConnectionPtr->Provider = _T("SQLOLEDB");

	if (!_is_TransactionMode2020())
	{
		m_poConnectionPtr->Attributes = ADODB::adXactCommitRetaining + ADODB::adXactAbortRetaining;
	}

	m_poConnectionPtr->CommandTimeout = 60 * 60;
	CString oDSNDBString;

	_update_effective_server();

	ASSERT(!m_oEffectiveServerString.IsEmpty());

	oDSNDBString = _T("Server=") + m_oEffectiveServerString + _T(";DATABASE=") + m_oDBString;

	ensure_start_sql_server(m_oEffectiveServerString, m_oUserString, m_oPwdString);

	m_poConnectionPtr->Open(_bstr_t(oDSNDBString), _bstr_t(m_oUserString), _bstr_t(m_oPwdString), -1);
	m_poConnectionPtr->CommandTimeout = 60 * 60;

	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET CURSOR_CLOSE_ON_COMMIT OFF"), true);
	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET DATEFORMAT DMY"), true);
	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET XACT_ABORT OFF"), true);
	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET ANSI_PADDING OFF"), true);

	if (_is_TransactionMode2020())
	{
		CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET IMPLICIT_TRANSACTIONS OFF"), true);
	}

	if (!_is_TransactionMode2020())
	{
		m_poConnectionPtr->BeginTrans();
	}
}


bool CADOObjServer::_get_object_mssql(long TypeId, long IdObj, CFlatData ** ppoFlatData, long & rnLength,
	SCP<CStdObjDef>  & rpoStdObjDefSP)
{
	CADOCommand oCommand(m_poConnectionPtr);
	long nFields = rpoStdObjDefSP->GetFieldCount();

	oCommand.AddReturnValueParam(SQLT_INT);

	oCommand.AddInParam(SQLT_INT, (LPVOID)&IdObj);
	oCommand.AddOutParam(SQLT_INT);	//0=versionid

	for (long iter = 1; iter < nFields; iter++)
	{
		SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = rpoStdObjDefSP->GetField(iter);
		long nSQLType = rpoStdObjFieldDefSP->GetSQLType();
		long nRelationType = rpoStdObjFieldDefSP->GetRelationType();
		if (nSQLType != SQLT_IGNORE)
		{
			//outparam
			oCommand.AddOutParam(nSQLType);
			if (nRelationType == RELT_WILDREF)
			{
				//outparam
				oCommand.AddOutParam(SQLT_INT);
			}
		}
	}
	//execute
	oCommand.ExecProc(rpoStdObjDefSP->GetTableName() + ProcedureSuffixOnAction(action_get), false);
	ASSERT(oCommand.GetReturnValue().Type() == VT_I4);
	if (oCommand.GetReturnValue().GetLong() != 1)
	{
		return false;	//pobranie rekordu nieudane
	}
	//store results
	*ppoFlatData = new CFlatData(rnLength, new BYTE[rnLength], true);

	{	//uwaga na realokacje!
		CFlatData::CFDHeader oHeader((*ppoFlatData)->GetDataPtr());
		oHeader.Action() = action_get;
		oHeader.TypeId() = TypeId;
		oHeader.IdObj() = IdObj;
		oHeader.VersionId() = oCommand.GetOutParam(0).GetLong();
	}

	long nFldIter = 1;	//0-for version
	for (long iter = 1; iter < nFields; iter++)
	{
		SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = rpoStdObjDefSP->GetField(iter);
		long nSQLType = rpoStdObjFieldDefSP->GetSQLType();
		long nRelationType = rpoStdObjFieldDefSP->GetRelationType();
		if (nSQLType != SQLT_IGNORE)
		{
			long nFieldSize = Variant2BinaryHelper(nSQLType, oCommand.GetOutParam(nFldIter));
			Variant2BinaryHelper(nSQLType, oCommand.GetOutParam(nFldIter++),
				(*ppoFlatData)->GrowBy(nFieldSize));
			rnLength += nFieldSize;
			if (nRelationType == RELT_WILDREF)
			{
				ASSERT(Variant2BinaryHelper(SQLT_INT, oCommand.GetOutParam(nFldIter)) == sizeof(long));
				Variant2BinaryHelper(SQLT_INT, oCommand.GetOutParam(nFldIter++),
					(*ppoFlatData)->GrowBy(sizeof(long)));
				rnLength += sizeof(long);
			}
		}
	}
	return true;
}

void CADOObjServer::_execute_simple_stat_mssql(const CFlatData & roFlatData, stdobjactions Action, long TypeId)
{
	ASSERT(m_EngineType == dbet_ms_sql70 || m_EngineType == dbet_ms_sql2000);

	ASSERT(Action == action_insert || Action == action_update || Action == action_delete);
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddReturnValueParam(SQLT_INT);
	long nFields = poStdObjDefSP->GetFieldCount();
	PBYTE pData = roFlatData.GetDataPtr() + CFlatData::CFDHeader::Size();
	CFlatData::CFDHeader oFlatDataHeader(roFlatData);
	//binding params
	switch (Action)
	{
	case action_update:
	case action_insert:
	{
		oCommand.AddInParam(SQLT_INT, (LPVOID)&oFlatDataHeader.IdObj());
		oFlatDataHeader.VersionId()++;
		oCommand.AddInParam(SQLT_INT, (LPVOID)&oFlatDataHeader.VersionId());
		for (long iter = 1; iter < nFields; iter++)
		{
			SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = poStdObjDefSP->GetField(iter);
			long nSQLType = rpoStdObjFieldDefSP->GetSQLType();
			long nRelationType = rpoStdObjFieldDefSP->GetRelationType();
			if (nSQLType != SQLT_IGNORE)
			{
				pData += oCommand.AddInParam(nSQLType, pData);
				if (nRelationType == RELT_WILDREF)
				{
					pData += oCommand.AddInParam(SQLT_INT, pData);
				}
			}
		}
	}
	break;
	case action_delete:
		oCommand.AddInParam(SQLT_INT, (LPVOID)&oFlatDataHeader.IdObj());
		break;
	default:
		ASSERT(false);
	}

	oCommand.ExecProc(poStdObjDefSP->GetTableName() + ProcedureSuffixOnAction(Action), true);
	ASSERT(oCommand.GetReturnValue().Type() == VT_I4);
	if (oCommand.GetReturnValue().GetLong() != 1)
	{
		CString oString;
		oString.Format("procedura %s zmieni³a %d rekordów dla idobj=%d",
			poStdObjDefSP->GetTableName() + ProcedureSuffixOnAction(Action),
			oCommand.GetReturnValue().GetLong(), oFlatDataHeader.IdObj());
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
}

void CADOObjServer::_get_max_idobj_mssql(long TypeId, long & rnMaxIdObj)
{
	ASSERT(m_EngineType == dbet_ms_sql70 || m_EngineType == dbet_ms_sql2000);

	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);

	CADOCommand oCommand(m_poConnectionPtr);
	oCommand.AddOutParam(SQLT_INT);
	oCommand.ExecProc(poStdObjDefSP->GetTableName() + ProcedureSuffixOnAction(action_maxid), false);
	if (oCommand.GetOutParam(0).Type() == VT_NULL)
	{
		rnMaxIdObj = 0;
	}
	else
	{
		rnMaxIdObj = oCommand.GetOutParam(0).GetLong();
	}
}

void CADOObjServer::_execute_list_stat_mssql(const CFlatData & roFlatData, long TypeId, long IdParent)
{
	ASSERT(m_EngineType == dbet_ms_sql70 || m_EngineType == dbet_ms_sql2000);

	PBYTE pData = roFlatData.GetDataPtr() + CFlatData::CFDHeader::Size();
	stdobjlistoperations eWhatToDo = static_cast<stdobjlistoperations>(*(long*)pData);
	pData += sizeof(long);

	switch (eWhatToDo)
	{
	case listop_delcollection:
	{
		CADOCommand oCommand(m_poConnectionPtr);
		oCommand.AddInParam(SQLT_INT, (LPVOID)&IdParent);
		oCommand.AddInParam(SQLT_INT, (LPVOID)&TypeId);
		oCommand.ExecProc(DelCollectionProcedure(), true);
	}
	break;
	case listop_save:
	{
		ASSERT(false);
		//to jest dobry i sprawdzony kod ale nie powienien byæ
		//przez nic wo³any, poniewa¿ zmieni³a siê implementacja list
		// i one teraz wo³j¹ listop_save2
		//ten kod nie obs³uguje operacji move na liœcie
		//i jest wolniejszy przy d³ugich listach
		//(ale potencjalnie szybszy przy krótkich)

		long   nTotalNewItems = *(LPLONG)pData; pData += sizeof(long);
		long   nItemsToInsert = *(LPLONG)pData; pData += sizeof(long);
		LPLONG pItemsToInsertInx = (LPLONG)pData; pData += nTotalNewItems * sizeof(long);
		LPLONG pItemsToInsertObj = (LPLONG)pData; pData += nTotalNewItems * sizeof(long);
		long   nItemsToDelete = *(LPLONG)pData; pData += sizeof(long);
		LPLONG pItemsToDelete = (LPLONG)pData;

		long   nItemsToAdd = nTotalNewItems - nItemsToInsert;
		ASSERT(nTotalNewItems >= 0);
		ASSERT(nItemsToAdd >= 0);
		ASSERT(nItemsToInsert >= 0);
		ASSERT(nItemsToDelete >= 0);

		// 1. usuwanie elementow do usuniecia
		if (nItemsToDelete > 0)
		{
			CADOCommand oCommand(m_poConnectionPtr);
			oCommand.Prepare(DelFromCollectionProcedure());

			COleSafeArray oSafeArray;
			CSmartOleVariant oIdParentSOV(IdParent, VT_I4);
			CSmartOleVariant oTypeIdSOV(TypeId, VT_I4);
			oSafeArray.CreateOneDim(VT_VARIANT, 3);
			for (long iter = 0; iter < nItemsToDelete; iter++)
			{
				long nInx = 0;
				oSafeArray.PutElement(&nInx, &oIdParentSOV); nInx++;
				oSafeArray.PutElement(&nInx, &oTypeIdSOV);	nInx++;
				CSmartOleVariant oSOV(pItemsToDelete[iter], VT_I4);
				oSafeArray.PutElement(&nInx, &oSOV);
				oCommand.ExecProc(true, &oSafeArray);
			}
		}
		// 2. wstawianie nowych (inserted + added)
		if (nTotalNewItems > 0)
		{
			if (nItemsToInsert > 0)
			{
				//2.1. miejsce na nowe (inserted)
				long nMultiplyFactor = nItemsToInsert + 1;
				CADOCommand oCommand(m_poConnectionPtr);
				oCommand.AddInParam(SQLT_INT, (LPVOID)&nMultiplyFactor);
				oCommand.AddInParam(SQLT_INT, (LPVOID)&IdParent);
				oCommand.AddInParam(SQLT_INT, (LPVOID)&TypeId);
				oCommand.ExecProc(MakeSpaceCollectionProcedure(), true);
			}
			//2.2. wstawianie
			{
				CADOCommand oCommand(m_poConnectionPtr);
				oCommand.Prepare(InsertIntoCollectionProcedure());

				COleSafeArray oSafeArray;
				CSmartOleVariant oIdParentSOV(IdParent, VT_I4);
				CSmartOleVariant oTypeIdSOV(TypeId, VT_I4);
				CSmartOleVariant oInsertInx(long(0), VT_I4);
				CSmartOleVariant oInsertObj(long(0), VT_I4);
				oSafeArray.CreateOneDim(VT_VARIANT, 4);
				long nInx = 0;
				oSafeArray.PutElement(&nInx, &oIdParentSOV); nInx++;
				oSafeArray.PutElement(&nInx, &oTypeIdSOV);	nInx++;
				long nI2 = 2;
				long nI3 = 3;
				for (long iter = 0; iter < nTotalNewItems; iter++)
				{
					V_I4(&oInsertInx.GetVariantRef()) = pItemsToInsertInx[iter];
					V_I4(&oInsertObj.GetVariantRef()) = pItemsToInsertObj[iter];

					oSafeArray.PutElement(&nI2, &oInsertInx.GetVariantRef());
					oSafeArray.PutElement(&nI3, &oInsertObj.GetVariantRef());
					oCommand.ExecProc(true, &oSafeArray);
				}
			}
		}
		//3. porz¹dkowanie kolekcji
		if (nItemsToDelete > 0 || nTotalNewItems > 0)
		{
			CADOCommand oCommand(m_poConnectionPtr);
			oCommand.AddInParam(SQLT_INT, (LPVOID)&IdParent);
			oCommand.AddInParam(SQLT_INT, (LPVOID)&TypeId);
			oCommand.ExecProc(MakeOrderCollectionProcedure(), true);
		}
	}
	break;
	case listop_save2:
	{
		//1. usuniêcie wszystkich elementów
		{
			CADOCommand oCommand(m_poConnectionPtr);
			oCommand.AddInParam(SQLT_INT, (LPVOID)&IdParent);
			oCommand.AddInParam(SQLT_INT, (LPVOID)&TypeId);
			oCommand.ExecProc(DelCollectionProcedure(), true);
		}
		//2. wstawienie wszystkich elementów
		long   nTotalItems = *(LPLONG)pData; pData += sizeof(long);
		if (nTotalItems > 0)
		{
			LPLONG pItemsIdObjs = (LPLONG)pData;
			CADOCommand oCommand(m_poConnectionPtr);
			oCommand.Prepare(InsertIntoCollectionProcedure());

			COleSafeArray oSafeArray;
			CSmartOleVariant oIdParentSOV(IdParent, VT_I4);
			CSmartOleVariant oTypeIdSOV(TypeId, VT_I4);
			CSmartOleVariant oInsertInx(long(0), VT_I4);
			CSmartOleVariant oInsertObj(long(0), VT_I4);
			oSafeArray.CreateOneDim(VT_VARIANT, 4);
			long nInx = 0;
			oSafeArray.PutElement(&nInx, &oIdParentSOV); nInx++;
			oSafeArray.PutElement(&nInx, &oTypeIdSOV);	nInx++;
			long nI2 = 2;
			long nI3 = 3;
			for (long iter = 0; iter < nTotalItems; iter++)
			{
				V_I4(&oInsertInx.GetVariantRef()) = iter + 1;
				V_I4(&oInsertObj.GetVariantRef()) = pItemsIdObjs[iter];

				oSafeArray.PutElement(&nI2, &oInsertInx.GetVariantRef());
				oSafeArray.PutElement(&nI3, &oInsertObj.GetVariantRef());
				oCommand.ExecProc(true, &oSafeArray);
			}
		}
	}
	break;
	default:
		ASSERT(false);
	}
}

