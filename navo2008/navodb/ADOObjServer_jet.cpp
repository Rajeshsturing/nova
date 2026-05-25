/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Object Server (on ADO) 
	Jet specific part
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CADOObjServer::_login_msjet()
{
	ASSERT(m_EngineType == dbet_ms_jet35);

	m_poConnectionPtr->Provider = _T("Microsoft.Jet.OLEDB.4.0");
	m_poConnectionPtr->Attributes = ADODB::adXactCommitRetaining + ADODB::adXactAbortRetaining;
	
	//tworzenie œcie¿ki na podstawie registry
	CString oDBPathString;
	SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetDatabaseRegistryKeyName(),_T("DBPath"),oDBPathString);
	if(oDBPathString.IsEmpty())
	{
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),_T("InstallationRoot"),oDBPathString);
		ASSERT(!oDBPathString.IsEmpty());
		EnsureEndingBackslash(oDBPathString);
		oDBPathString += _T("Database\\");
	}
	EnsureEndingBackslash(oDBPathString);
	CString oDBNameString = m_oDBString;
	int nPos = oDBNameString.Find('.');
	if(nPos == -1)
	{
		oDBNameString += ".mdb";
	}
	oDBPathString += oDBNameString;

	CString oDSNDBString = _T("Data Source=") + oDBPathString;

	//to_do: user and password
	m_poConnectionPtr->Open(_bstr_t(oDSNDBString),_bstr_t(""),_bstr_t(""),-1);
	
//not supported	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET CURSOR_CLOSE_ON_COMMIT OFF"),true);
//not supported	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET DATEFORMAT DMY"),true);
//not supported	CADOCommand(m_poConnectionPtr).ExecDirect(_T("SET XACT_ABORT OFF"),true);
	
	m_poConnectionPtr->BeginTrans();
}

//-------------------------------------------------------------------------
const TCHAR * _pcInsertValuesKwd = _T("INSERT INTO %s VALUES(?,?%s)");

static void _get_sql_insert_msjet(SCP<CStdObjDef> & rpoStdObjDefSP,CString & roString)
{
	ASSERT(rpoStdObjDefSP.PointsObject());
	long nCount = rpoStdObjDefSP->GetFieldCount();
	//to_do: odejmij pola virtualne
	CString oString('?',nCount+nCount-2);
	for(long iter = 0; iter < nCount-1; iter++)
	{
		oString.SetAt(iter+iter,',');
	}
	roString.Format(_pcInsertValuesKwd,rpoStdObjDefSP->GetTableName(),oString);
}

const TCHAR * _pcUpdateKwd	= _T("UPDATE %s SET VersionId=?%s WHERE %s.IdObj=%d");

static void _get_sql_update_msjet(SCP<CStdObjDef> & rpoStdObjDefSP,long IdObj,CString & roString)
{
	ASSERT(rpoStdObjDefSP.PointsObject());

	CString oString;
	long nCount = rpoStdObjDefSP->GetFieldCount();
	for(long iter = 1; iter < nCount; iter++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = rpoStdObjDefSP->GetField(iter);
		if(rpoFieldDefSP->IsPersistent())
		{
			CString oFldString;
			oFldString.Format(",%s.%s=?",rpoStdObjDefSP->GetTableName(),rpoFieldDefSP->GetName());
			oString += oFldString;
		}
	}
	roString.Format(_pcUpdateKwd,rpoStdObjDefSP->GetTableName(),oString,rpoStdObjDefSP->GetTableName(),IdObj);
}

const TCHAR * _pcDeleteKwd = _T("DELETE FROM %s WHERE %s.IdObj=%d");

static void _get_sql_delete_msjet(SCP<CStdObjDef> & rpoStdObjDefSP,long IdObj,CString & roString)
{
	ASSERT(rpoStdObjDefSP.PointsObject());

	roString.Format(_pcDeleteKwd,rpoStdObjDefSP->GetTableName(),rpoStdObjDefSP->GetTableName(),IdObj);
}

const TCHAR * _pcSelectKwd	= _T("SELECT %s.VersionId%s FROM %s WHERE %s.IdObj=%d");

static void _get_sql_select_msjet(SCP<CStdObjDef> & rpoStdObjDefSP,long IdObj,CString & roString)
{
	ASSERT(rpoStdObjDefSP.PointsObject());

	CString oString;
	long nCount = rpoStdObjDefSP->GetFieldCount();
	for(long iter = 1; iter < nCount; iter++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = rpoStdObjDefSP->GetField(iter);
		long nSQLType = rpoFieldDefSP->GetSQLType();
		long nRelationType = rpoFieldDefSP->GetRelationType();
		if(nSQLType != SQLT_IGNORE)
		{
			CString oFldString;
			oFldString.Format(",%s.%s",rpoStdObjDefSP->GetTableName(),rpoFieldDefSP->GetName());
			oString += oFldString;

			if(nRelationType == RELT_WILDREF)
			{
				CString oFldString;
				oFldString.Format(",%s.%s_wrt",rpoStdObjDefSP->GetTableName(),rpoFieldDefSP->GetName());
				oString += oFldString;
			}
		}
	}
	roString.Format(_pcSelectKwd,rpoStdObjDefSP->GetTableName(),oString,rpoStdObjDefSP->GetTableName(),rpoStdObjDefSP->GetTableName(),IdObj);
}

const TCHAR * _pcSelectMaxIdKwd	= _T("SELECT max(%s.IdObj) FROM %s");

static void _get_sql_select_maxid_msjet(SCP<CStdObjDef> & rpoStdObjDefSP,CString & roString)
{
	roString.Format(_pcSelectMaxIdKwd,rpoStdObjDefSP->GetTableName(),rpoStdObjDefSP->GetTableName());
}


class CADORecordsetAccessor
{
public:
	CADORecordsetAccessor(ADODB::_RecordsetPtr poRecordsetPtr) :
		m_poRecordsetPtr(poRecordsetPtr)
	{
		_build_values();
	}
	void _build_values()
	{
		ADODB::FieldsPtr poFieldsPtr = m_poRecordsetPtr->Fields;
		m_oFieldValues.SetSize(poFieldsPtr->GetCount());
		for(long iter = 0; iter < m_oFieldValues.GetSize(); iter++)
		{
			m_oFieldValues[iter] = poFieldsPtr->GetItem(_variant_t(iter))->Value;
		}
	}
	const CSmartOleVariant & operator [](long nIndex) const
	{
		return m_oFieldValues[nIndex];
	}
private:
	ADODB::_RecordsetPtr m_poRecordsetPtr;
	CArray<CSmartOleVariant,CSmartOleVariant &> m_oFieldValues;
};

bool CADOObjServer::_get_object_msjet(long TypeId,long IdObj,CFlatData ** ppoFlatData,
	long & rnLength,SCP<CStdObjDef>  & rpoStdObjDefSP)
{
	ASSERT(m_EngineType == dbet_ms_jet35);

	CADOCommand oCommand(m_poConnectionPtr);
	long nFields = rpoStdObjDefSP->GetFieldCount();
	//execute
	CString oCmdString;
	_get_sql_select_msjet(rpoStdObjDefSP,IdObj,oCmdString);

	TRACE("%s\n",oCmdString);
	//nie ma rekordu...
	ADODB::_RecordsetPtr poRecordsetPtr = oCommand.ExecDirect(oCmdString,false);
	if(poRecordsetPtr->BOF || poRecordsetPtr->EOF)
	{
		return false;
	}
	
	CADORecordsetAccessor oARA(poRecordsetPtr);

	//store results
	*ppoFlatData = new CFlatData(rnLength,new BYTE[ rnLength ],true);
	
	{	//uwaga na realokacje!
		CFlatData::CFDHeader oHeader((*ppoFlatData)->GetDataPtr());
		oHeader.Action() = action_get;
		oHeader.TypeId() = TypeId;
		oHeader.IdObj() = IdObj;
		oHeader.VersionId() = oARA[0].GetLong();
	}

	long nFldIter = 1;	//0-for version
	for(long iter = 1; iter < nFields; iter++)
	{
		SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = rpoStdObjDefSP->GetField(iter);
		long nSQLType = rpoStdObjFieldDefSP->GetSQLType();
		long nRelationType = rpoStdObjFieldDefSP->GetRelationType();
		if(nSQLType != SQLT_IGNORE)
		{
			long nFieldSize = Variant2BinaryHelper(nSQLType,oARA[nFldIter]);
			Variant2BinaryHelper(nSQLType,oARA[nFldIter++],(*ppoFlatData)->GrowBy(nFieldSize));
			rnLength += nFieldSize;
			if(nRelationType == RELT_WILDREF)
			{
				ASSERT(Variant2BinaryHelper(SQLT_INT,oARA[nFldIter]) == sizeof(long));
				Variant2BinaryHelper(SQLT_INT,oARA[nFldIter++],(*ppoFlatData)->GrowBy(sizeof(long)));
				rnLength += sizeof(long);
			}
		}
	}
	return true;
}

void CADOObjServer::_get_max_idobj_msjet(long TypeId,long & rnMaxIdObj)
{
	ASSERT(m_EngineType == dbet_ms_jet35);

	CADOCommand oCommand(m_poConnectionPtr);
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);

	//execute
	CString oCmdString;
	_get_sql_select_maxid_msjet(poStdObjDefSP,oCmdString);
	TRACE("%s\n",oCmdString);

	CADORecordsetAccessor oARA(oCommand.ExecDirect(oCmdString,false));
	if(oARA[0].Type() == VT_NULL)
	{
		//nie ma ¿adnego rekordu...
		rnMaxIdObj = 0;
	}
	else
	{
		rnMaxIdObj = oARA[0].GetLong();
	}
}

const TCHAR * _pcDelCollKwd	= _T("DELETE from Collections where IdParent=%d AND IdCollection=%d");

static const TCHAR * _get_sql_delcoll_msjet()
{
	return _pcDelCollKwd;
}

const TCHAR * _pcInsCollKwd = _T("INSERT into Collections(IdParent,IdCollection,LP,IdObj) values(?,?,?,?)");

static const TCHAR * _get_sql_inscoll_msjet()
{
	return _pcInsCollKwd;
}

void CADOObjServer::_execute_list_stat_msjet(const CFlatData & roFlatData,long TypeId,long IdParent)
{
	ASSERT(m_EngineType == dbet_ms_jet35);

	PBYTE pData = roFlatData.GetDataPtr() + CFlatData::CFDHeader::Size();
	stdobjlistoperations eWhatToDo = static_cast<stdobjlistoperations>(*(long*)pData);
	pData += sizeof(long);
	
	switch(eWhatToDo)
	{
	case listop_delcollection:
	{
		CADOCommand oCommand(m_poConnectionPtr);
		TRACE("%s\n",_get_sql_delcoll_msjet());
		
		oCommand.AddInParam(SQLT_INT,(LPVOID)&IdParent);
		oCommand.AddInParam(SQLT_INT,(LPVOID)&TypeId);
		oCommand.ExecDirect(_get_sql_delcoll_msjet(),true);
	}
	break;
	case listop_save2:
	{
		//1. usuniêcie wszystkich elementów
		{
			CADOCommand oCommand(m_poConnectionPtr);
			TRACE("%s\n",_get_sql_delcoll_msjet());
			
			oCommand.AddInParam(SQLT_INT,(LPVOID)&IdParent);
			oCommand.AddInParam(SQLT_INT,(LPVOID)&TypeId);
			oCommand.ExecDirect(_get_sql_delcoll_msjet(),true);
		}
		//2. wstawienie wszystkich elementów
		long   nTotalItems	= *(LPLONG) pData; pData += sizeof(long);
		if(nTotalItems > 0)
		{
			LPLONG pItemsIdObjs =  (LPLONG) pData;
			for(long iter=0; iter < nTotalItems; iter++)
			{
				CADOCommand oCommand(m_poConnectionPtr);
				TRACE("%s\n",_get_sql_inscoll_msjet());
				oCommand.AddInParam(SQLT_INT,(LPVOID)&IdParent);
				oCommand.AddInParam(SQLT_INT,(LPVOID)&TypeId);

				long nInx = iter + 1;
				oCommand.AddInParam(SQLT_INT,(LPVOID)&nInx);
				oCommand.AddInParam(SQLT_INT,(LPVOID)&pItemsIdObjs[iter]);
				oCommand.ExecDirect(_get_sql_inscoll_msjet(),true);
			}
		}
	}
	break;
	default:
		ASSERT(false);
	}
}

void CADOObjServer::_execute_simple_stat_msjet(const CFlatData & roFlatData,stdobjactions Action,long TypeId)
{
	ASSERT(m_EngineType == dbet_ms_jet35);

	ASSERT(Action == action_insert || Action == action_update || Action == action_delete);
	SCP<CStdObjDef> poStdObjDefSP = m_poDefinitionManagerSP->GetStdObjDef(TypeId);
	CADOCommand oCommand(m_poConnectionPtr);

	long nFields = poStdObjDefSP->GetFieldCount();
	PBYTE pData = roFlatData.GetDataPtr() + CFlatData::CFDHeader::Size();
	CFlatData::CFDHeader oFlatDataHeader(roFlatData);
	//binding params
	switch(Action)
	{
	case action_update:
	case action_insert:
	{
		oCommand.AddInParam(SQLT_INT,(LPVOID)&oFlatDataHeader.IdObj());
		oFlatDataHeader.VersionId()++;
		oCommand.AddInParam(SQLT_INT,(LPVOID)&oFlatDataHeader.VersionId());
		for(long iter = 1; iter < nFields; iter++)
		{
			SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP = poStdObjDefSP->GetField(iter);
			long nSQLType = rpoStdObjFieldDefSP->GetSQLType();
			long nRelationType = rpoStdObjFieldDefSP->GetRelationType();
			if(nSQLType != SQLT_IGNORE)
			{
				pData += oCommand.AddInParam(nSQLType,pData);
				if(nRelationType == RELT_WILDREF)
				{
					pData += oCommand.AddInParam(SQLT_INT,pData);
				}
			}
		}
	}
	break;
	case action_delete:
		oCommand.AddInParam(SQLT_INT,(LPVOID)&oFlatDataHeader.IdObj());
	break;
	default:
		ASSERT(false);
	}

	CString oCmdString;
	switch(Action)
	{
	case action_insert:
		_get_sql_insert_msjet(poStdObjDefSP,oCmdString);
	break;
	case action_update:
		_get_sql_update_msjet(poStdObjDefSP,oFlatDataHeader.IdObj(),oCmdString);
	break;
	case action_delete:
		_get_sql_delete_msjet(poStdObjDefSP,oFlatDataHeader.IdObj(),oCmdString);
	break;
	default:
		ASSERT(false);
	}

	TRACE("%s\n",oCmdString);
	oCommand.ExecDirect(oCmdString,true);
}

