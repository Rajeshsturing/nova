/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObject
	miscelanous
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"
#include "min_wrap_ado.h"
#include "navoobjcoor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAnti_recursion_holder
{
public:
	CAnti_recursion_holder(SCP<CNEO_storage> & rpoStorageSP,long nOuterFieldNr):
		m_roFlags(rpoStorageSP->_access_field_status(nOuterFieldNr-1))
	{
		if(m_roFlags.m_bComputing)
		{
			CStdObjDef * poDefinition = rpoStorageSP->GetDefinition();
			ThrowNavoException4(ERCO_STDOBJ_RECURSION_IN_RECALC,IDPAGE_NOTAVAILABLE,
				poDefinition->GetTableName(),
				poDefinition->GetField(nOuterFieldNr)->GetName(),
				rpoStorageSP->GetType(),
				rpoStorageSP->GetThis());
		}
		m_roFlags.m_bComputing = true;
	}
	~CAnti_recursion_holder()
	{
		m_roFlags.m_bComputing = false;
	}
private:
	CNEO_field_status & m_roFlags;
};

bool CNEO_user::_call_recalc(const long nOuterFieldNr,const CSmartOleVariant & roOldValueSOV)
{
	//prevent recursion
	CAnti_recursion_holder oARH(_get_storage(),nOuterFieldNr);

	//prepare call
	// function TABLICA_POLE_change(oldval)

	ASSERT(_get_storage());
	CStdObjDef * poDefinition = _get_storage()->GetDefinition();
	ASSERT(poDefinition);
	ASSERT(poDefinition->GetField(nOuterFieldNr)->IsRecalc());
	CString oFunctionNameString;
	poDefinition->GetRecalcFunctionName(nOuterFieldNr,oFunctionNameString);

#ifdef _DEVELOPER_EDITION_
	CDebuggerCallHolder oDCH;

	if(GetDebugOptions().IsTraceAutoCalls())
	{
		oDCH++.StoreMsg("entering %s(%d)(%s)",oFunctionNameString,_get_storage()->GetThis(),
			Variant2String(roOldValueSOV));
	}
#endif
	
	//setup "this_"
	CInvokeForwarderHolder oThis_InvokeForwarderHolder(
		poDefinition->GetThis_DispatchForwarder(),NewSCP((IDispatch*)&m_xDynaDispatch,true));

	CSmartOleVariant oResultSOV;
	//fire it
	poDefinition->Invoke(CBStr(oFunctionNameString),
		const_cast<CSmartOleVariant*>(&roOldValueSOV),1,&oResultSOV);

	//analyze results
	bool bResult = true;
	if(oResultSOV.Type() == VT_BOOL)
	{
		bResult = oResultSOV.GetBool();
	}
	else
	{
		ThrowNavoException2(ERCO_STDOBJ_RECALC_MUST_RET_BOOL,IDPAGE_NOTAVAILABLE,
			oFunctionNameString,Variant2String(oResultSOV));
	}
#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("leaving %s(%d)=%s",oFunctionNameString,_get_storage()->GetThis(),
			bResult ? "true":"false");
	}
#endif
	return bResult;
}

bool CNEO_user::_call_trigger(long nCommand)
{
	//prepare call
	// function TABLICA_metoda()
	
	ASSERT(_get_storage());
	CStdObjDef * poDefinition = _get_storage()->GetDefinition();
	ASSERT(poDefinition);
	CString oFunctionNameString;
	poDefinition->GetFunctionName(nCommand,oFunctionNameString);
	
#ifdef _DEVELOPER_EDITION_
	CDebuggerCallHolder oDCH;
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		oDCH++.StoreMsg("entering %s(%d)\n",oFunctionNameString,_get_storage()->GetThis());
	}
#endif

	//setup "this_"
	CInvokeForwarderHolder oThis_InvokeForwarderHolder(
		poDefinition->GetThis_DispatchForwarder(),NewSCP((IDispatch*)&m_xDynaDispatch,true));

	CSmartOleVariant oResultSOV;
	//fire it
	poDefinition->Invoke(CBStr(oFunctionNameString),NULL,0,&oResultSOV);
	
	//analyze results
	bool bResult = true;
	if(oResultSOV.Type() == VT_BOOL)
	{
		bResult = oResultSOV.GetBool();
	}
	else
	{
		ThrowNavoException2(ERCO_STDOBJ_TRIGGER_MUST_RET_BOOL,IDPAGE_NOTAVAILABLE,
			oFunctionNameString,Variant2String(oResultSOV));
	}
#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("leaving %s(%d)=%s\n",oFunctionNameString,_get_storage()->GetThis(),bResult ? "true":"false");
	}
#endif
	return bResult;
}

bool CNEO_user::_call_before_list_operation(long nOuterIndex)
{

	ASSERT(nOuterIndex > 0 || nOuterIndex < 0);
	ASSERT(_get_storage());
	CStdObjDef * poDefinition = _get_storage()->GetDefinition();
	ASSERT(poDefinition);

	if(!poDefinition->IsFunctionDefined(CLASS_LISTOP))
	{
		return true;
	}

	//prepare call
	//function TABLICA_listop(index)

	CString oFunctionNameString;
	poDefinition->GetFunctionName(CLASS_LISTOP,oFunctionNameString);
	
#ifdef _DEVELOPER_EDITION_
	CDebuggerCallHolder oDCH;

	if(GetDebugOptions().IsTraceAutoCalls())
	{
		oDCH++.StoreMsg("entering %s(%d)(%d)",oFunctionNameString,_get_storage()->GetThis(),
			nOuterIndex);
	}
#endif

	CInvokeForwarderHolder oThis_InvokeForwarderHolder(
		poDefinition->GetThis_DispatchForwarder(),NewSCP((IDispatch*)&m_xDynaDispatch,true));
	
	CSmartOleVariant oResultSOV;
	CSmartOleVariant oIndexSOV(nOuterIndex);
	poDefinition->Invoke(CBStr(oFunctionNameString),&oIndexSOV,1,&oResultSOV);
	bool bResult = true;
	if(oResultSOV.Type() == VT_BOOL)
	{
		bResult = oResultSOV.GetBool();
	}
	else
	{
		ThrowNavoException2(ERCO_STDOBJ_TRIGGER_MUST_RET_BOOL,IDPAGE_NOTAVAILABLE,
			oFunctionNameString,Variant2String(oResultSOV));
	}
#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("leaving %s(%d)=%s\n",oFunctionNameString,_get_storage()->GetThis(),bResult ? "true":"false");
	}
#endif
	return bResult;
}

CString CNEO_user::get_as_text()
{
	CString strResult;
	ASSERT(_get_storage());
	CStdObjDef * poDefinition = _get_storage()->GetDefinition();
	ASSERT(poDefinition);
	if(poDefinition->IsFunctionDefined(CLASS_AS_TEXT))
	{
		//prepare call
		// function TABLICA_as_text()
		CString oFunctionNameString;
		poDefinition->GetFunctionName(CLASS_AS_TEXT,oFunctionNameString);
		
		CInvokeForwarderHolder oThis_InvokeForwarderHolder(
			poDefinition->GetThis_DispatchForwarder(),NewSCP((IDispatch*)&m_xDynaDispatch,true));

		CSmartOleVariant oResultSOV;
		poDefinition->Invoke(CBStr(oFunctionNameString),NULL,0,&oResultSOV);

		ASSERT(oResultSOV.Type() == VT_BSTR);
		if(oResultSOV.Type() == VT_BSTR)
		{
			strResult = oResultSOV.GetBStr();
		}
	}
	else
	{
		strResult.Format("%s (%d)",poDefinition->GetHumanName(),_get_storage()->GetThis());
	}
	return strResult;
}

SCP<CNEO_user> CNEO_user::_get_parent()
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());
	
	long nParentTypeId = 0;
	long nParentIdObj = 0;
	_get_storage()->_get_parent(nParentTypeId,nParentIdObj);
	
	if(nParentTypeId == 0)
	{
		return SCP<CNEO_user>();
	}
	
	ASSERT(nParentTypeId != 0);
	ASSERT(nParentIdObj != 0);
	
	SCP<CNEO_user> poParentUserSP = _get_trans()->_get_object(nParentTypeId,nParentIdObj,0,0);
	ASSERT(poParentUserSP.PointsObject());	//parenta nie mo¿e nikt usun¹æ jeœli my go mamy (?)
	return poParentUserSP;
}

bool CNEO_user::_exclusive_lock_and_reload()
{
	bool bSuccess = false;
	ASSERT(_get_trans());

	SCP<CNEO_storage> poWriteLockedStorageSP = _get_trans()->_write_lock(m_poStorageSP,bSuccess,this);
	if(bSuccess)
	{
		ASSERT(poWriteLockedStorageSP.PointsObject());
		if(poWriteLockedStorageSP != m_poStorageSP)
		{
			SCP<CNEO_storage> poSwapStorageSP = m_poStorageSP;
			m_poStorageSP = poWriteLockedStorageSP;
			m_poStorageSP->AddRef_User();
			poSwapStorageSP->Release_User();
		}
	}
	ASSERT(_get_storage());
	return bSuccess;
}

void CNEO_user::_exclusive_unlock()
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());
	_get_trans()->_write_unlock(_get_storage());
}


bool CNEO_storage::_test_can_delete(bool bSilent,CNEO_trans * poTrans)
{
	ASSERT(poTrans);
	
	//jeœli zaznaczone przez programistê ¿e zawsze wolno kasowaæ - nie sprawdzaj
	if(GetDefinition()->get_AlwaysCanDel())
	{
		return true;
	}

	SCP<IDispatch> poDiscoRecDispatchSP;
	bool bFreeToDelete = poTrans->fwd_test_can_delete(GetType(),GetThis(),poDiscoRecDispatchSP);
	
	if(bFreeToDelete)
	{
		return true;
	}
	if(!bSilent)
	{
		CString oDescriptionString;
		NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_CANNOT_DEL_OBJ_IS_USED,
			GetDefinition()->GetHumanName());
		
		
		CSmartOleVariant oTypeIdSOV("typeid");
		CSmartOleVariant oIdObjSOV("idobj");
		MWA::_Recordset oDiscoRecordSet(poDiscoRecDispatchSP.Get());
		oDiscoRecordSet.m_bAutoRelease = FALSE;
		CString oDetailsString;
		while(!oDiscoRecordSet.GetEof())
		{
			MWA::Fields oFields(oDiscoRecordSet.GetFields());
			MWA::Field oFieldTypeId(oFields.GetItem(oTypeIdSOV.GetVariantRef()));
			long TypeId = CSmartOleVariant(oFieldTypeId.GetValue()).GetLong();
			MWA::Field oFieldIdObj(oFields.GetItem(oIdObjSOV.GetVariantRef()));
			long IdObj = CSmartOleVariant(oFieldIdObj.GetValue()).GetLong();
			if(!oDetailsString.IsEmpty())
			{
				oDetailsString += ",";
			}
			
			//neo_todo: w przypadku dzieci nale¿y znaleŸæ ParentTypeId,ParentIdObj
			
			CString oString;
			SCP<CStdObjDef> poFoundObjDefSP = poTrans->GetDefinitionManager()->GetStdObjDef(TypeId);
			if(poFoundObjDefSP->IsChild())
			{
				oString.Format("Obiekt '%s'",poFoundObjDefSP->GetHumanName());
			}
			else
			{
				SCP<CNEO_user> poUsingDataObjectSP = poTrans->_get_object(TypeId,IdObj,0,0);
				if(poUsingDataObjectSP.PointsObject())
				{
					oString.Format("Obiekt '%s' (%S)",
						poFoundObjDefSP->GetHumanName(),
						poUsingDataObjectSP->GetAsTextAUTO());
				}
				else
				{
					//neo_todo: string from resources
					oString.Format("Obiekt(%d,%d) w miêdzyczasie usuniêty",TypeId,IdObj);
				}
			}
			oDetailsString += oString;
			oDiscoRecordSet.MoveNext();
		}
		/*
			CNavoErrorInfo oNavoErrorInfo2(ERCO_STDOBJ_CANNOT_DEL_OBJ_IS_USED,
				IDPAGE_NOTAVAILABLE,oDetailsString);
			poTrans->AddMessage(oNavoErrorInfo2);
		*/
		oDescriptionString += oDetailsString;
		CNavoErrorInfo oNavoErrorInfo(ERCO_STDOBJ_CANNOT_DEL_OBJ_IS_USED,
			IDPAGE_NOTAVAILABLE,oDescriptionString);

		poTrans->AddMessage(oNavoErrorInfo);
	}
	return false;
}

bool CNEO_storage::_test_can_save(bool bSilent,CNEO_trans * poTrans)
{
	bool bResult = true;
	
	for(long nField = 1; nField <= m_oFields.GetSize(); nField++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(nField);
		bool bFldResult = m_oFields[ nField - 1 ]._test_can_save(rpoFieldDefSP,this,poTrans,bSilent);
		bResult = bResult && bFldResult;
	}
	
	return bResult;
}















