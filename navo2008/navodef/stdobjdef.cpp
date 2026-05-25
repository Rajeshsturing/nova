/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	StdObj definitions
	
	to_do: doprowadziæ do mo¿liwoœci generowania XML/binary korzystaj¹c tylko
		   z Automation
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "stdobjdef.h"
#include "DefinitionManager.h"

#ifdef _DEBUG
	#ifdef _NAVODOTNET
		//-- nothing here -- 
	#else
		#if defined(NAVO2008)
			//-- nothing here
		#else
			#include <fstream.h>
			#include <iomanip.h>
		#endif
	#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString SQLTypeName(long Type,dbenginetype eEngineType);
//-----------------------------------------------------------
//------------------ stdobjfielddef -------------------------
//-----------------------------------------------------------

CStdObjFieldDef::CStdObjFieldDef():
   m_nRelationType (RELT_EMBED),
   m_bReadOnly (false),
   m_bVirtual (FALSE),
   m_nSQLType (0),
   m_bRefOptional(false),
   m_bNonEmpty(false),
   m_bUnique(false),
   m_bRecalc(false),
   m_bHiddenFld(false),
   m_bComputed(false)
{
	ASSERT(m_Default.Type() == VT_EMPTY);
	EnableAutomation();
};

void CStdObjFieldDef::WriteToArchive(CArchive & roArchive)
{
	roArchive	<< m_szNameString	<< m_oHumanNameString	<< m_nSQLType		<< m_nRelationType;

	if(m_Default.Type() == VT_DISPATCH)
	{
		roArchive	<< (BYTE) 'o';			//object, m_Default must be null
	}
	else
	{
		roArchive	<< (BYTE) 'p';			//plain
		roArchive	<< 	m_Default;
	}

	roArchive	<< (BYTE)m_bRecalc
				<< (BYTE)m_bReadOnly<< (BYTE)m_bVirtual
				<< (BYTE)m_bRefOptional << (BYTE)m_bNonEmpty << (BYTE)m_bUnique 
				<< (BYTE) m_bHiddenFld << (BYTE)m_bComputed;
	m_oWildRefTypeIdArray.Serialize(roArchive);
	m_oEnumValuesArray.Serialize(roArchive);
}

void CStdObjFieldDef::ReadFromArchive(CArchive & roArchive)
{
	roArchive	>> m_szNameString	>> m_oHumanNameString	>> m_nSQLType		>> m_nRelationType;
	
	BYTE ucDefaultClass;
	roArchive	>> ucDefaultClass;
	if(ucDefaultClass == (BYTE) 'o')			//object, m_Default must be null
	{
		m_Default = CSmartOleVariant(LPDISPATCH(NULL),false);
	}
	else
	{
		ASSERT(ucDefaultClass == (BYTE) 'p');	//plain
		roArchive	>> m_Default		;
	}
	BYTE ucRecalc;
	roArchive >> ucRecalc;
	m_bRecalc = (ucRecalc != '\0');

	BYTE ucReadOnly;
	BYTE ucVirtual;
	BYTE ucRefOptional;
	BYTE ucNonEmpty;
	BYTE ucUnique;
	BYTE ucComputed;
	BYTE ucHidden;

	roArchive >> ucReadOnly >> ucVirtual >> ucRefOptional >> ucNonEmpty >> ucUnique 
		>> ucHidden >> ucComputed;
	m_bReadOnly		= (ucReadOnly		!= '\0');
	m_bVirtual		= (ucVirtual		!= '\0');
	m_bRefOptional	= (ucRefOptional	!= '\0');
	m_bNonEmpty		= (ucNonEmpty		!= '\0');
	m_bUnique		= (ucUnique			!= '\0');
	m_bHiddenFld	= (ucHidden			!= '\0');
	m_bComputed		= (ucComputed		!= '\0');

	m_oWildRefTypeIdArray.Serialize(roArchive);
	m_oEnumValuesArray.Serialize(roArchive);
}


//=======================================================================================
//						a u t o m a t i o n   p a r t
//=======================================================================================
//{{AFX_MSG_MAP(CStdObjFieldDef)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CStdObjFieldDef, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CStdObjFieldDef)
	DISP_PROPERTY_EX(CStdObjFieldDef, "name", GetNameAUTO, SetNameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CStdObjFieldDef, "type", GetTypeAUTO, SetTypeAUTO, VT_I4)
	DISP_PROPERTY_EX(CStdObjFieldDef, "sqltype", GetSQLTypeAUTO, SetSQLTypeAUTO, VT_I4)
	DISP_PROPERTY_EX(CStdObjFieldDef, "sqltypename", GetSQLTypeNameAUTO, SetSQLTypeNameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CStdObjFieldDef, "humanname", GetHumannameAUTO, SetHumannameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CStdObjFieldDef, "reftypeid", GetReftypeidAUTO, SetReftypeidAUTO, VT_I4)
	DISP_PROPERTY_EX(CStdObjFieldDef, "isunique", GetIsUniqueAUTO, SetIsUniqueAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "isnonempty", GetIsNonEmptyAUTO, SetIsNonEmptyAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "ispersist", GetIsPersistentAUTO, SetIsPersistentAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "isrefopt", GetIsRefOptAUTO, SetIsRefOptAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "iscomputed", GetIsComputedAUTO, SetIsComputedAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "hidden", GetIsHiddenAUTO, SetIsHiddenAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjFieldDef, "isvirtual", GetIsVirtualAUTO, SetIsVirtualAUTO, VT_BOOL)
	DISP_FUNCTION(CStdObjFieldDef, "wildreftypeid",GetWildRefTypeIdAUTO,VT_I4, VTS_I4)
	DISP_FUNCTION(CStdObjFieldDef, "enumvalue",GetEnumValueAUTO,VT_BSTR, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BSTR CStdObjFieldDef::GetNameAUTO() 
{
	ALL_TRY
	{
		return GetName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjFieldDef::SetNameAUTO(LPCTSTR) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"name","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CStdObjFieldDef::GetTypeAUTO() 
{
	return GetRelationType();
}

void CStdObjFieldDef::SetTypeAUTO(long) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"type","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CStdObjFieldDef::GetSQLTypeAUTO() 
{
	return GetSQLType();
}

void CStdObjFieldDef::SetSQLTypeAUTO(long) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"sqltype","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CStdObjFieldDef::GetSQLTypeNameAUTO() 
{
	ALL_TRY
	{
		return SQLTypeName(GetSQLType(),dbet_ms_sql70).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjFieldDef::SetSQLTypeNameAUTO(LPCTSTR) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"sqltypename","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CStdObjFieldDef::GetHumannameAUTO() 
{
	ALL_TRY
	{
		return GetHumanName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjFieldDef::SetHumannameAUTO(LPCTSTR /*lpszNewValue*/) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"humanname","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CStdObjFieldDef::GetReftypeidAUTO() 
{
	ALL_TRY
	{
		if(GetRelationType() != RELT_REF 
			&& GetRelationType() != RELT_LIST
			&& GetRelationType() != RELT_WILDREF)
		{
			ThrowNavoException1(ERCO_SOFD_REFTYPE_NA_FOR_THIS_FIELD,IDPAGE_NOTAVAILABLE,(LPCTSTR)GetName());
		}
		return GetReferenceTypeId();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjFieldDef::SetReftypeidAUTO(long /*nNewValue*/) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"reftypeid","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CStdObjFieldDef::GetIsUniqueAUTO()
{
	return IsUnique() != false;
}

void CStdObjFieldDef::SetIsUniqueAUTO(BOOL /*bNewValue*/)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"isunique","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CStdObjFieldDef::GetIsNonEmptyAUTO()
{
	return IsNonEmpty() != false;
}

void CStdObjFieldDef::SetIsNonEmptyAUTO(BOOL /*bNewValue*/)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"isnonempty","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CStdObjFieldDef::GetIsPersistentAUTO()
{
	return IsPersistent() != false;
}

void CStdObjFieldDef::SetIsPersistentAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"ispersist","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjFieldDef::GetIsComputedAUTO()
{
	return IsComputed() != false;
}

void CStdObjFieldDef::SetIsComputedAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"iscomputed","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjFieldDef::GetIsVirtualAUTO()
{
	return IsVirtual() != false;
}

void CStdObjFieldDef::SetIsVirtualAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"isvirtual","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjFieldDef::GetIsHiddenAUTO()
{
	return is_hidden() != false;
}

void CStdObjFieldDef::SetIsHiddenAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"hidden","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjFieldDef::GetIsRefOptAUTO()
{
	return IsRefOptional() != false;
}

void CStdObjFieldDef::SetIsRefOptAUTO(BOOL /*bNewValue*/)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"isrefopt","stdobjfielddef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CStdObjFieldDef::GetWildRefTypeIdAUTO(long nInx)
{
	ALL_TRY
	{
		return GetWildRefTypeId(nInx);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CStdObjFieldDef::GetEnumValueAUTO(long nInx)
{
	ALL_TRY
	{
		return CString(GetEnumValue(nInx)).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//=======================================================================================
void CStdObjFieldDef::PostProcess()
{
	VARTYPE vartype = VT_EMPTY;
	
	bool bIsNull = false;
	if(m_Default.Type() == VT_BSTR)	//jeœli jest podana to musi byæ to string
	{
		bIsNull = (_wcsicmp(m_Default.GetBStr(),L"null") == 0);
	}
	else
	{
		ASSERT(m_Default.Type() == VT_EMPTY);
	}
	switch(m_nRelationType)
	{
	case RELT_EMBED:
		switch(m_nSQLType)
		{
		case SQLT_SMALL:
			vartype = VT_I2;
		break;
		case SQLT_INT:
			vartype = VT_I4;
		break;
		case SQLT_TIME:
			vartype = VT_I4;
			if(bIsNull)
			{
				m_Default = GetNullTimeSOV();
			}
		break;
		case SQLT_DATE:
			vartype = VT_DATE;
			if(bIsNull)
			{
				m_Default = GetNullDateSOV();
			}
		break;
		case SQLT_IMAGE:
			vartype = VT_UI1 | VT_ARRAY;
			m_Default.CreateOneDimArray(VT_UI1,1);
		break;
		case SQLT_MONEY:
		case SQLT_QUANTITY:
			vartype = VT_CY;
		break;
		case SQLT_OBJECT:
			vartype = VT_DISPATCH;
			if(!IsVirtual())
			{
				CString oString("SQLObject must be virtual");
				ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
			}
		break;
		default:
			if(m_nSQLType >= SQLT_CHAR0 && m_nSQLType < SQLT_SMALL)
			{
				vartype = VT_BSTR;
			}
			else
			{
				ThrowNavoException1(ERCO_SOFD_INVALID_SQLTYPE,IDPAGE_NOTAVAILABLE,m_nSQLType);
			}
		}
	break;
	case RELT_REF:
		m_nSQLType = SQLT_INT;
		vartype = VT_CY;		//hi=typeid, lo=idobj

		if(IsVirtual())
		{
			CString oString("<ref> must not be virtual");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
	break;
	case RELT_WILDREF:
		m_nSQLType = SQLT_INT;
		vartype = VT_CY;		//hi=typeid, lo=idobj
		
		if(GetWildRefTypeId(1) == 0)	//at least two types for <wildref>
		{
			ThrowNavoException1(ERCO_SOFD_WILDREF_TO_LESS_TYPEIDS,IDPAGE_NOTAVAILABLE,m_szNameString);
		}
		
		if(IsVirtual())
		{
			CString oString("<wildref> must not be virtual");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
	break;
	case RELT_ENUM:
		if(!m_bRefOptional)	//jeœli nie jest podane <optional/> to jest wymagane
		{
			SetNonEmpty();
		}
		if(GetEnumCount() == 0)
		{
			ThrowNavoException1(ERCO_SOFD_ENUM_TO_LESS_ITEMS,IDPAGE_NOTAVAILABLE,m_szNameString);
		}
		m_nSQLType = SQLT_INT;
		vartype = VT_I4;
	break;
	case RELT_FILE:
	case RELT_LIST:
		m_nSQLType = SQLT_IGNORE;
		vartype = VT_I4;

		if(IsVirtual())
		{
			CString oString("<list> nor <file> must not be virtual");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
	break;
	}
	if(IsVirtual())
	{
		m_nSQLType = SQLT_IGNORE;
	}


	if(VT_DISPATCH == vartype)
	{
		m_Default = CSmartOleVariant(LPDISPATCH(NULL),false);
	}
	else
	{
		m_Default.ChangeType(vartype);
	}
	ASSERT(m_Default.Type() != VT_EMPTY);
	
	if(m_oHumanNameString.IsEmpty())
	{
		m_oHumanNameString = m_szNameString;
	}
}



//-----------------------------------------------------------
//------------------ stdobjdef ------------------------------
//-----------------------------------------------------------
CStdObjDef::CStdObjDef(CNavoException & roErrorStorage) :
	CScriptUser(10000 /* bezpieczna wartoœæ mapowania DISPID, szukaj tak¿e FIRST_FIELD_DISPID */),		
	m_bVolatile(false),
	m_bChild(false),
	m_bCacheOnServer(true),
	m_bCacheOnClient(true),
	m_bHidden(false),
	m_bHasAnyList(false),
	m_bHasAnyFile(false),
	m_bAlwaysCanDel(false),
	m_nTypeId(0),
	m_nParentTypeId(0),
	m_poDefinitionManager(NULL),
	m_roErrorStorage(roErrorStorage)
{
	EnableAutomation();
	for(long iter=CLASS_CTOR;iter<CLASS_STDCOMMANDS_COUNT;iter++)
	{
		m_bStdCommandsArray[iter] = false;
	}
	//for use in stdobj methods. actual pointer will be supplied
	//by CStdObj::XPropDispatch::Invoke
	AddNamedItem(NewSCP(new CNamedItemInfo(_T("this_"),&GetThis_DispatchForwarder(),NULL)));
	AddNamedItem(NewSCP(new CNamedItemInfo(_T("trans_"),&GetTransaction_DispatchForwarder(),NULL)));
}

void CStdObjDef::__attach(CDefinitionManager * poDefinitionManager,long nTypeId)
{
	m_poDefinitionManager = poDefinitionManager;
	m_nTypeId = nTypeId;
	ASSERT(m_poDefinitionManager);
	AddNamedItem(NewSCP(new CNamedItemInfo(_T("stdobjdef_"),m_poDefinitionManager->GetDispatch(false),NULL)));
	
	if(m_poDefinitionManager->GetDOC_Dispatch().PointsObject())
	{
		AddNamedItem(NewSCP(new CNamedItemInfo(_T("doc_"),m_poDefinitionManager->GetDOC_Dispatch().Get(),NULL)));
	}
	if(m_poDefinitionManager->GetNX_Dispatch().PointsObject())
	{
		AddNamedItem(NewSCP(new CNamedItemInfo(_T("nx_"),m_poDefinitionManager->GetNX_Dispatch().Get(),NULL)));
	}
}

void CStdObjDef::WriteToArchive(CArchive & roArchive)
{
	roArchive << m_nParentTypeId << m_oTableNameString	<< m_oHumanNameString << (BYTE) m_bVolatile
		<< (BYTE) m_bChild << (BYTE) m_bCacheOnServer << (BYTE) m_bCacheOnClient 
		<< (BYTE) m_bHidden 
		<< (BYTE) m_bHasAnyList << (BYTE) m_bHasAnyFile << (BYTE) m_bAlwaysCanDel
		<< m_oClassScriptString << m_aFields.GetSize();

	long iter=0;
	for(iter=0; iter <= m_aFields.GetUpperBound(); iter++)
	{
		m_aFields[iter]->WriteToArchive(roArchive);
	}
	for(iter=CLASS_CTOR;iter<CLASS_STDCOMMANDS_COUNT;iter++)
	{
		roArchive << (BYTE) m_bStdCommandsArray[iter];
	}
	roArchive << m_oCursorMap.GetCount();
	POSITION pos = m_oCursorMap.GetStartPosition();
	while(pos)
	{
		long nDummy;
		SCP<CCursorDef> poCursorDefSP;
		m_oCursorMap.GetNextAssoc(pos,nDummy,poCursorDefSP);
		poCursorDefSP->WriteToArchive(roArchive);
	}
}

void CStdObjDef::ReadFromArchive(CArchive & roArchive)
{
	roArchive >> m_nParentTypeId >> m_oTableNameString	>> m_oHumanNameString;
	
	BYTE ucVolatile;
	
	roArchive >> ucVolatile;
	m_bVolatile	= (ucVolatile != '\0');

	BYTE ucChild;
	BYTE ucCacheOnServer;
	BYTE ucCacheOnClient;
	BYTE ucHidden;
	BYTE ucHasAnyList;
	BYTE ucHasAnyFile;
	BYTE ucAlwaysCanDel;

	roArchive >> ucChild >> ucCacheOnServer >> ucCacheOnClient >> ucHidden;
	roArchive >> ucHasAnyList >> ucHasAnyFile >> ucAlwaysCanDel;
	m_bChild = (ucChild != '\0');
	m_bCacheOnServer  = (ucCacheOnServer != '\0');
	m_bCacheOnClient = (ucCacheOnClient != '\0');
	m_bHidden = (ucHidden != '\0');
	m_bHasAnyList = (ucHasAnyList != '\0');
	m_bHasAnyFile = (ucHasAnyFile != '\0');
	m_bAlwaysCanDel = (ucAlwaysCanDel != '\0');
			
	roArchive >> m_oClassScriptString;

	ScanScriptForProcedures(m_oClassScriptString,m_oFunctionsArray,m_oTableNameString);

	long nFieldCount;
	roArchive >> nFieldCount;

	m_aFields.SetSize(nFieldCount);
	long iter = 0;
	for(iter = 0; iter < nFieldCount; iter++)
	{
		SCP<CStdObjFieldDef> poStdObjFieldDefSP = NewSCP(new CStdObjFieldDef());
		poStdObjFieldDefSP->ReadFromArchive(roArchive);
		m_aFields[ iter ] = poStdObjFieldDefSP;
		CString oFieldNameString = poStdObjFieldDefSP->GetName();
		oFieldNameString.MakeLower();
		m_oFieldNamesMap[ CICSBStr(oFieldNameString) ] = iter;
	}
	for(iter=CLASS_CTOR;iter<CLASS_STDCOMMANDS_COUNT;iter++)
	{
		BYTE ucCmd;
		roArchive >> ucCmd;
		m_bStdCommandsArray[iter] = (ucCmd != '\0');
	}
	long nCursorCount;
	roArchive >> nCursorCount;
	while(nCursorCount--)
	{
		SCP<CCursorDef> poCursorDefSP = NewSCP(new CCursorDef());
		poCursorDefSP->ReadFromArchive(roArchive);
		AddCursorDef(poCursorDefSP);
	}
}

void CStdObjDef::GetRecalcFunctionName(long nFieldNr,CString & roString)
{
	ASSERT(nFieldNr >= 0 && nFieldNr <= m_aFields.GetUpperBound());
	roString = m_oTableNameString + "_" + m_aFields[nFieldNr]->GetName() + CString("_change");
	roString.MakeLower();
}

static LPCTSTR pcClassMethods[] = 
{
	_T("_initnew"),
	_T("_befins"),
	_T("_befupd"),
	_T("_befdel"),
	_T("_aftins"),
	_T("_aftupd"),
	_T("_aftdel"),
	_T("_reinit"),
	_T("_as_text"),
	_T("_listop"),
	NULL
};

void CStdObjDef::GetFunctionName(long nCommand,CString & roString)
{
	roString = m_oTableNameString + CString(pcClassMethods[nCommand]);
	roString.MakeLower();
}

static long FindFunctionName(CFunctionInfoArray & roFunctionArray,const CString & roNameString)
{
	for(long iter=0;iter<=roFunctionArray.GetUpperBound();iter++)
	{
		if(roFunctionArray[iter].m_oNameString.CompareNoCase(roNameString) == 0)
		{
			return iter;
		}
	}
	return -1;
}

void CStdObjDef::SearchClassFunctions()
{
	ScanScriptForProcedures(m_oClassScriptString,m_oFunctionsArray,m_oTableNameString);

	//2. search for matching class functions
	
	CString oPatternString;
	for(long iter=CLASS_CTOR;iter<CLASS_STDCOMMANDS_COUNT;iter++)
	{
		GetFunctionName(iter,oPatternString);
		long nPos = FindFunctionName(m_oFunctionsArray,oPatternString);
		m_bStdCommandsArray[iter] = (nPos != -1);
	}

	//3. search matching field names
	for(long nField=0;nField <= m_aFields.GetUpperBound(); nField++)
	{
		CString oFunctionNameString;
		GetRecalcFunctionName(nField,oFunctionNameString);
		for(long iter=0;iter<=m_oFunctionsArray.GetUpperBound();iter++)
		{
			if(m_oFunctionsArray[iter].m_oNameString.CompareNoCase(oFunctionNameString) == 0)
			{
				m_aFields[nField]->MarkRecalc();
				m_oFunctionsArray[ iter ].m_dispid = nField;
				break;
			}
		}
	}
}

CCursorDef::CCursorDef() :
	m_Ident(0),
	m_bForwardOnly(false)
{
	EnableAutomation();
}

void CCursorDef::WriteToArchive(CArchive & roArchive)
{
	roArchive << m_Ident << (BYTE) m_bForwardOnly << m_oHumanNameString <<
		m_oWhereString << m_oJoinString << m_oOrderByString << m_oSPNameString << m_oSPBodyString;
}

void CCursorDef::ReadFromArchive(CArchive & roArchive)
{
	roArchive >> m_Ident;
	BYTE cFO;
	roArchive >> cFO;
	m_bForwardOnly = (cFO != '\0');
	roArchive >> m_oHumanNameString >>
		m_oWhereString >> m_oJoinString >> m_oOrderByString >> m_oSPNameString >> m_oSPBodyString;
}

//=======================================================================================
//						a u t o m a t i o n   p a r t
//=======================================================================================
//{{AFX_MSG_MAP(CStdObjDef)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CStdObjDef, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CStdObjDef)
	DISP_PROPERTY_EX(CStdObjDef, "humanname", GetHumanameAUTO, SetHumanameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CStdObjDef, "tablename", GetTablenameAUTO, SetTablenameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CStdObjDef, "ispersist", GetIsPersistentAUTO, SetIsPersistentAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjDef, "typeid", GetTypeidAUTO, SetTypeidAUTO, VT_I4)
	DISP_PROPERTY_EX(CStdObjDef, "child", GetChildAUTO, SetChildAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjDef, "hidden", GetHiddenAUTO, SetHiddenAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CStdObjDef, "parenttypeid", GetParentTypeidAUTO, SetParentTypeidAUTO, VT_I4)
	DISP_FUNCTION(CStdObjDef, "getfieldcount", GetFieldCountAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CStdObjDef, "getfieldindex", GetFieldIndexAUTO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CStdObjDef, "field", GetFieldAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CStdObjDef, "cursor", GetCursorDefAUTO, VT_DISPATCH, VTS_I4)
	DISP_PROPERTY_EX_ID(CStdObjDef, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	DISP_FUNCTION(CStdObjDef, "scriptcode", GetScriptCodeAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CStdObjDef, "generatesqlpart", GenerateMSSQLScriptAUTO, VT_BSTR, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_ARRAYENUMERATOR(SCP<CStdObjFieldDef>)

LPUNKNOWN CStdObjDef::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CArrayEnumerator< SCP<CStdObjFieldDef> > > poNewArrayEnumSP = NewSCP(new CArrayEnumerator< SCP<CStdObjFieldDef> >(m_aFields));
		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

void CStdObjDef::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


BSTR CStdObjDef::GetHumanameAUTO() 
{
	ALL_TRY
	{
		return GetHumanName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjDef::SetHumanameAUTO(LPCTSTR /*lpszNewValue*/) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"humanname","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CStdObjDef::GetScriptCodeAUTO()
{
	ALL_TRY
	{
		return CString(GetScriptCode()).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CStdObjDef::GenerateMSSQLScriptAUTO(long nPartId)
{
	ALL_TRY
	{
		CString oString;
		generate_mssql_script(oString,nPartId);
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


BSTR CStdObjDef::GetTablenameAUTO() 
{
	ALL_TRY
	{
		return GetTableName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStdObjDef::SetTablenameAUTO(LPCTSTR /*lpszNewValue*/) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"tablename","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CStdObjDef::GetFieldCountAUTO() 
{
	ALL_TRY
	{
		return GetFieldCount();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CStdObjDef::GetFieldIndexAUTO(LPCTSTR lpName) 
{
	ALL_TRY
	{
		CString oFieldNameString(lpName);
		oFieldNameString.MakeLower();
		return GetFieldFromName(CBStr(oFieldNameString));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjDef::GetIsPersistentAUTO()
{
	return IsVolatile() == false;
}

void CStdObjDef::SetIsPersistentAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"ispersist","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjDef::GetChildAUTO()
{
	return IsChild() != false;
}

void CStdObjDef::SetChildAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"child","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CStdObjDef::GetHiddenAUTO()
{
	return IsHidden() != false;
}

void CStdObjDef::SetHiddenAUTO(BOOL)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"hidden","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


long CStdObjDef::GetTypeidAUTO()
{
	return m_nTypeId;
}

void CStdObjDef::SetTypeidAUTO(long /*nNewValue*/)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"typeid","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


long CStdObjDef::GetParentTypeidAUTO()
{
	ASSERT(IsChild());
	return m_nParentTypeId;
}

void CStdObjDef::SetParentTypeidAUTO(long /*nNewValue*/)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"typeid","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CStdObjDef::GetFieldAUTO(long nFldInx) 
{
	ALL_TRY
	{
		return GetField(nFldInx)->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CStdObjDef::GetCursorDefAUTO(long idCursor)
{
	ALL_TRY
	{
		return GetCursorDef(idCursor)->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//=======================================================================================
//=======================================================================================
//{{AFX_MSG_MAP(CCursorDef)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CCursorDef, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CCursorDef)
	DISP_PROPERTY_EX(CCursorDef, "ident",		GetIdentAUTO, SetIdentAUTO, VT_I4)
	DISP_PROPERTY_EX(CCursorDef, "humanname",	GetHumannameAUTO, SetHumannameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "where",		GetWhereAUTO, SetWhereAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "join",		GetJoinAUTO, SetJoinAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "orderby",		GetOrderByAUTO, SetOrderByAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "spname",		GetSPNameAUTO, SetSPNameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "spbody",		GetSPBodyAUTO, SetSPBodyAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CCursorDef, "forwardonly", GetIsForwardOnlyAUTO, SetIsForwardOnlyAUTO, VT_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BSTR CCursorDef::GetHumannameAUTO() 
{
	ALL_TRY
	{
		return GetHumanName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetHumannameAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetHumanName(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CCursorDef::GetWhereAUTO() 
{
	ALL_TRY
	{
		return GetWhere().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetWhereAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetWhere(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CCursorDef::GetJoinAUTO() 
{
	ALL_TRY
	{
		return GetJoin().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetJoinAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetJoin(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
BSTR CCursorDef::GetOrderByAUTO() 
{
	ALL_TRY
	{
		return GetOrderBy().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetOrderByAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetOrderBy(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
BSTR CCursorDef::GetSPNameAUTO() 
{
	ALL_TRY
	{
		return GetSPName().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetSPNameAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetSPName(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
BSTR CCursorDef::GetSPBodyAUTO() 
{
	ALL_TRY
	{
		return GetSPBody().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCursorDef::SetSPBodyAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetSPBody(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CCursorDef::GetIsForwardOnlyAUTO()
{
	return IsForwardOnly() != false;
}

void CCursorDef::SetIsForwardOnlyAUTO(BOOL bFO)
{
	ALL_TRY
	{
		SetForwardOnly(bFO != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CCursorDef::GetIdentAUTO() 
{
	return GetIdent();
}

void CCursorDef::SetIdentAUTO(long Ident) 
{
	ALL_TRY
	{
		SetIdent(Ident);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


//=======================================================================================
//=======================================================================================

void CStdObjDef::SetScriptCode(LPCTSTR lpScriptCode)
{
	m_oClassScriptString = CString("Option Explicit\r\n") + lpScriptCode;
	SearchClassFunctions();
}

void CStdObjDef::GetDocumentName(CString & roDocNameString)
{
	roDocNameString = "definicja " + m_oTableNameString;
}

SCP<CStdObjFieldDef> & CStdObjDef::GetField(long nFieldNr)
{
	if(nFieldNr < 0 || nFieldNr > m_aFields.GetUpperBound())
	{
		ThrowNavoException2(ERCO_SOD_GETFIELD_FAILED,IDPAGE_NOTAVAILABLE,m_oTableNameString,nFieldNr);
	}
	return m_aFields[ nFieldNr ];
}

long CStdObjDef::GetFieldFromName(LPCWSTR lpFieldName)
{
	long nFieldNr;
	if(m_oFieldNamesMap.Lookup(lpFieldName,nFieldNr))
	{
		return nFieldNr;
	}
	return -1;
}

SCP<CStdObjFieldDef> CStdObjDef::NewField()
{
	return NewSCP(new CStdObjFieldDef());
}

void CStdObjDef::AddField(SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP)
{
	rpoStdObjFieldDefSP->PostProcess();
	m_aFields.Add(rpoStdObjFieldDefSP);
	CString oFieldNameString = rpoStdObjFieldDefSP->GetName();
	oFieldNameString.MakeLower();
	m_oFieldNamesMap[ CICSBStr(oFieldNameString) ] = m_aFields.GetUpperBound();
	
	switch(rpoStdObjFieldDefSP->GetRelationType())
	{
	case RELT_LIST:
	{
		m_bHasAnyList = true;
	}
	break;
	case RELT_FILE:
	{
		m_bHasAnyFile = true;
	}
	break;
	}
}

void CStdObjDef::AddCursorDef(SCP<CCursorDef> & rpoCursorDefSP)
{
	m_oCursorMap[ rpoCursorDefSP->GetIdent() ] = rpoCursorDefSP;
}

void CStdObjDef::RemoveCursorDef(long Ident)
{
	VERIFY(m_oCursorMap.RemoveKey(Ident));
}

SCP<CCursorDef> CStdObjDef::GetCursorDef(long Ident)
{
	SCP<CCursorDef> poCursorDefSP;
	if(!m_oCursorMap.Lookup(Ident,poCursorDefSP))
	{
		ThrowNavoException2(ERCO_SOD_GETCURSOR_FAILED,IDPAGE_NOTAVAILABLE,(LPCTSTR)m_oTableNameString,Ident);
	}
	return poCursorDefSP;
}

//////////////---
//----------- dumpers

#ifdef _DEBUG
#if !defined(NAVO2008)
void CStdObjFieldDef::Dump(ostream & out)
{
	out << "\t\tname="		<< m_szNameString << endl;
	out << "\t\thumanname=" << m_oHumanNameString << endl;
	out << "\t\tsqltype="	<< m_nSQLType << endl;
	out << "\t\tvartype="	<< long(m_Default.Type()) << endl;
	out << "\t\tfieldtype=" << m_nRelationType << endl;
	out << "\t\tdefault="	<< Variant2String(m_Default) << endl;
	if(m_bRecalc)
	{
		out << "\t\trecalc" << endl;
	}
	if(m_bReadOnly)
	{
		out << "\t\treadonly" << endl;
	}
	if(m_bVirtual)
	{
		out << "\t\tvirtual" << endl;
	}
	if(m_bRefOptional)
	{
		out << "\t\trefopt" << endl;
	}
	if(m_bNonEmpty)
	{
		out << "\t\tnonempty" << endl;
	}
	if(m_bUnique)
	{
		out << "\t\tunique" << endl;
	}
	for(long iter = 0; iter <= m_oWildRefTypeIdArray.GetUpperBound(); iter++)
	{
		out << "\t\ttypeid[" << iter <<	"]=" << m_oWildRefTypeIdArray[iter] << endl;
	}
	for(iter = 0; iter <= m_oEnumValuesArray.GetUpperBound(); iter++)
	{
		out << "\t\tenum[" << iter <<	"]=" << m_oEnumValuesArray[iter] << endl;
	}
}

void CStdObjDef::Dump(ostream & out)
{
	out << "\ttable=" << m_oTableNameString << endl;
	out << "\thumanname=" << m_oHumanNameString << endl;

	for(long iter=CLASS_CTOR;iter<CLASS_STDCOMMANDS_COUNT;iter++)
	{
		if(m_bStdCommandsArray[iter])
		{
			out << "\t" << pcClassMethods[iter]  << endl;
		}
	}
	
	if(m_bVolatile)
	{
		out << "\tvolatile" << endl;
	}
	out << "\tscript{" << endl << m_oClassScriptString << endl << "}";
	out << "\t-----fields ------" << endl;
	for(iter = 0; iter < m_aFields.GetSize(); iter++)
	{
		out << "\tfield #" << iter << endl;
		m_aFields[iter]->Dump(out);
	}
	out << "\t----end of fields ------" << endl;
}
#endif
#endif


