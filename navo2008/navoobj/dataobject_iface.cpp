/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObject
	interface part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\navodef\stdobjdef.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long FIRST_FIELD_DISPID = 1000;

BEGIN_INTERFACE_MAP(CNEO_user, CCmdTargetInterface)
	INTERFACE_PART(CNEO_user, IID_IDispatch, DynaDispatch)
	INTERFACE_PART(CNEO_user,IID_INEDataObject,NEDataObject)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CNEO_user, DynaDispatch)  
DELEGATE_UNKNOWN_INTERFACE(CNEO_user, NEDataObject)  

//{{AFX_MSG_MAP(CNEO_user)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_user, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_user)
	DISP_FUNCTION_ID(CNEO_user, "isnew", 1, IsNewAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "text", 2, GetAsTextAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "type", 3,GetTypeAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM_ID(CNEO_user, "field", 4, GetFieldAUTO, SetFieldAUTO, VT_VARIANT, VTS_VARIANT)
	DISP_FUNCTION_ID(CNEO_user, "parent", 5, GetParentAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX_ID(CNEO_user, "markdel", 6, GetMarkDelAUTO, SetMarkDelAUTO, VT_BOOL)
	DISP_PROPERTY_EX_ID(CNEO_user, "ignore", 7, GetIgnoreAUTO, SetIgnoreAUTO, VT_BOOL)
	DISP_FUNCTION_ID(CNEO_user, "versionid", 8, GetVersionIdAUTO, VT_I4, VTS_NONE)	
	DISP_FUNCTION_ID(CNEO_user, "getobjdef", 9, GetStdObjDefAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "usermodif", 10, SetUserModifAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(CNEO_user, "get_this", 11, GetRealThisAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "exlock", 12, ExclusiveLockAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "exunlock", 13, ExclusiveUnlockAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "candel", 14, CanDelAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CNEO_user, "isbad_field", 15, HasFieldBadValueAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(CNEO_user, "cansave", 16, CanSaveAUTO, VT_BOOL, VTS_BOOL)
	DISP_PROPERTY_EX_ID(CNEO_user, "recalcenabled", 17, GetRecalcEnabledAUTO, SetRecalcEnabledAUTO, VT_BOOL)
	DISP_PROPERTY_PARAM_ID(CNEO_user, "oldfield", 19, GetOriginalFieldAUTO, SetOriginalFieldAUTO, VT_VARIANT, VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

STDMETHODIMP CNEO_user::XDynaDispatch::GetTypeInfoCount(UINT* pCount)
{
	METHOD_PROLOGUE(CNEO_user, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfoCount(pCount);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_user::XDynaDispatch::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo ** ppTInfo)
{
	METHOD_PROLOGUE(CNEO_user, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfo(iTInfo,lcid,ppTInfo);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_user::XDynaDispatch::
	GetIDsOfNames(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId)
{
	METHOD_PROLOGUE(CNEO_user, DynaDispatch)
	
	ALL_TRY
	{
		for (UINT nIndex = 1; nIndex < cNames; nIndex++)
		{
			rgDispId[nIndex] = DISPID_UNKNOWN;
		}
		//1. check field names
		HRESULT hr = pThis->_implement_GetIDsOfNames(rgszNames,rgDispId);
		if(hr == S_OK)
		{
			return S_OK;
		}
		
		//2. check dispatch map
		hr = ((IDispatch*)&pThis->m_xDispatch)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);

		//3. check object class script
		if(hr == DISP_E_UNKNOWNNAME)
		{
			hr = pThis->_get_storage()->GetDefinition()->__GetIDsOfNames(rgszNames,cNames,rgDispId);
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_user::XDynaDispatch::
	Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError)
{
	METHOD_PROLOGUE(CNEO_user, DynaDispatch)

	ALL_TRY
	{
		//0. reject known bad values
		if(dispId == DISPID_VALUE)
		{
			return DISP_E_MEMBERNOTFOUND;
		}

		//1. try invoke field method/property
		HRESULT hr = pThis->_implement_Invoke(dispId,wFlags,pDispParams,pVarResult,pExceptInfo);
		if(hr != DISP_E_MEMBERNOTFOUND)
		{
			return hr;
		}
	
		//2. try invoke dispatch map
		hr = ((IDispatch*)&pThis->m_xDispatch)->
			Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
		
		//3. invoke script method
		if(hr == DISP_E_MEMBERNOTFOUND)
		{
			CInvokeForwarderHolder oThis_InvokeForwarderHolder(
				pThis->_get_storage()->GetDefinition()->GetThis_DispatchForwarder(),
				NewSCP((IDispatch*)&pThis->m_xDynaDispatch,true));
			hr = pThis->_get_storage()->GetDefinition()->__Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
		}
		return hr;
	}
	TOP_ALL_CATCH_AUTOMATION(pThis->_get_trans()->GetErrorStorage(),pExceptInfo);
	return S_OK;
}


//------------------------------------------- --------------------------------
HRESULT CNEO_user::_implement_GetIDsOfNames(LPOLESTR*rgszNames,DISPID*rgDispId)
{
	ASSERT(_get_storage());

	CBStr oBStr(rgszNames[0]);
	oBStr.ToLower();
	LPCWSTR lpFieldName = oBStr;
	bool bIsBad = (wcsnicmp(oBStr,L"isbad_",6)==0);	//pytanie o status
	bool bIsOld = false;
	if(bIsBad)
	{
		lpFieldName = lpFieldName + 6;	//length("isbad_")
	}
	else
	{
		bIsOld = (wcsnicmp(oBStr,L"old_",4)==0);	//pytanie o wartoœæ oryginaln¹
		if(bIsOld)
		{
			lpFieldName = lpFieldName + 4;	//length("old_")
		}
	}
	rgDispId[0] = _get_storage()->GetDefinition()->GetFieldFromName(lpFieldName);
	if(rgDispId[0] != -1)
	{
		rgDispId[0] += FIRST_FIELD_DISPID;
		if(bIsBad)
		{
			rgDispId[0] += FIRST_FIELD_DISPID;
		}
		else if(bIsOld)
		{
			rgDispId[0] += FIRST_FIELD_DISPID + FIRST_FIELD_DISPID;
		}
		return S_OK;
	}
	
	return DISP_E_UNKNOWNNAME;
}

HRESULT CNEO_user::_implement_Invoke(DISPID dispId,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,
		EXCEPINFO * pExceptInfo)
{
	ASSERT(_get_storage());
	long nFieldCount = _get_storage()->GetDefinition()->GetFieldCount();
	if(dispId >= FIRST_FIELD_DISPID && dispId < FIRST_FIELD_DISPID + nFieldCount)
	{
		//get
		if((wFlags & DISPATCH_METHOD) || (wFlags & DISPATCH_PROPERTYGET))
		{
			get_field(dispId-FIRST_FIELD_DISPID,reinterpret_cast<CSmartOleVariant&>(*pVarResult));
			return S_OK;
		}
		//set
		if(wFlags == DISPATCH_PROPERTYPUT || wFlags == DISPATCH_PROPERTYPUTREF)
		{
			bool bResult = _internal_set_field(dispId-FIRST_FIELD_DISPID,
				reinterpret_cast<const CSmartOleVariant&>(pDispParams->rgvarg[0]));
			if(!bResult)
			{
				//build error info
				if(pExceptInfo)
				{
					CString oDescriptionString;
					NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_INVALID_VALUE_FOR_FIELD,
						(LPCTSTR)_get_storage()->GetDefinition()->GetField(dispId-FIRST_FIELD_DISPID)->GetName(),
						(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
						(LPCTSTR) Variant2String(CSmartOleVariant(pDispParams->rgvarg[0]))
						);
					
					pExceptInfo->wCode = (WORD) ERCO_STDOBJ_INVALID_VALUE_FOR_FIELD;
					pExceptInfo->bstrDescription = oDescriptionString.AllocSysString();
					pExceptInfo->scode = DISP_E_EXCEPTION;
				}
				return DISP_E_EXCEPTION;
			}
			return S_OK;
		}
		ASSERT(false);	//dziwne
		return DISP_E_BADPARAMCOUNT;
	}
	else if(dispId >= FIRST_FIELD_DISPID+FIRST_FIELD_DISPID && dispId < FIRST_FIELD_DISPID+FIRST_FIELD_DISPID + nFieldCount)
	{
		//get
		if((wFlags & DISPATCH_METHOD) || (wFlags & DISPATCH_PROPERTYGET))
		{
			V_VT(pVarResult) = VT_BOOL;
			V_BOOL(pVarResult) = _get_storage()->_has_field_bad_value(dispId-FIRST_FIELD_DISPID-FIRST_FIELD_DISPID) != false;
			return S_OK;
		}
		//set
		if(wFlags == DISPATCH_PROPERTYPUT || wFlags == DISPATCH_PROPERTYPUTREF)
		{
			ASSERT(V_VT(&pDispParams->rgvarg[0]) == VT_BOOL);
			_get_storage()->_set_field_bad_value(
				dispId-FIRST_FIELD_DISPID-FIRST_FIELD_DISPID,
				V_BOOL(&pDispParams->rgvarg[0]) != FALSE);
			return S_OK;
		}
		
		ASSERT(false);	//dziwne
		return DISP_E_BADPARAMCOUNT;
	}
	else if(dispId >= 3*FIRST_FIELD_DISPID && dispId < 3*FIRST_FIELD_DISPID + nFieldCount)
	{
		if((wFlags & DISPATCH_METHOD) || (wFlags & DISPATCH_PROPERTYGET))
		{
			get_original_field(dispId-3*FIRST_FIELD_DISPID,reinterpret_cast<CSmartOleVariant&>(*pVarResult));
			return S_OK;
		}
		//build error info
		if(pExceptInfo)
		{
			CString oDescriptionString;
			NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_CANNOT_SET_OLDVAL,
				(LPCTSTR)_get_storage()->GetDefinition()->GetField(dispId-3*FIRST_FIELD_DISPID)->GetName(),
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
				_get_storage()->GetThis()
				);
			
			pExceptInfo->wCode = (WORD) ERCO_STDOBJ_CANNOT_SET_OLDVAL;
			pExceptInfo->bstrDescription = oDescriptionString.AllocSysString();
			pExceptInfo->scode = DISP_E_EXCEPTION;
		}
		return DISP_E_EXCEPTION;
	}
	
	return DISP_E_MEMBERNOTFOUND;
}

//------------------------------------------- --------------------------------
long CNEO_user::_get_outer_field_nr_from_variant(const CSmartOleVariant & roFieldNameSOV)
{
	switch(roFieldNameSOV.Type())
	{
	case VT_I4:
		return roFieldNameSOV.GetLong();
	break;
	case (VT_I4 | VT_BYREF):
	{
		return roFieldNameSOV.GetVariantRef().lVal;
	}
		break;
	case VT_I2:
		return roFieldNameSOV.GetShort();
	break;
	case VT_BSTR:
	{
		CBStr oBStr(roFieldNameSOV.GetBStr());
		oBStr.ToLower();
		return _get_storage()->GetDefinition()->GetFieldFromName(oBStr);
	}
	break;
	case (VT_BSTR | VT_BYREF):
	{
		CBStr oBStr(*roFieldNameSOV.GetVariantRef().pbstrVal);
		oBStr.ToLower();
		return _get_storage()->GetDefinition()->GetFieldFromName(oBStr);
	}
	break;
	case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
	{
		VARIANT * pVariant = roFieldNameSOV.GetVariantRef().pvarVal;
		ASSERT(pVariant);
		return _get_outer_field_nr_from_variant(*pVariant);	//Uwaga! wywo³uje siebie ale ju¿ bez byRef
	}
	break;
	default:
		ASSERT(false);
		return 0;
	}
}

void CNEO_user::SetFieldAUTO(const VARIANT FAR& varFieldName, const VARIANT FAR& newValueVariant) 
{
	ALL_TRY
	{
		set_field(
			_get_outer_field_nr_from_variant(reinterpret_cast<const CSmartOleVariant &>(varFieldName)),
				reinterpret_cast<const CSmartOleVariant &>(newValueVariant));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

VARIANT CNEO_user::GetFieldAUTO(const VARIANT FAR& varFieldName) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		
		get_field(
			_get_outer_field_nr_from_variant(
				reinterpret_cast<const CSmartOleVariant &>(varFieldName)),oSOV);

		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

VARIANT CNEO_user::GetOriginalFieldAUTO(const VARIANT FAR& varFieldName) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		
		get_original_field(
			_get_outer_field_nr_from_variant(
				reinterpret_cast<const CSmartOleVariant &>(varFieldName)),oSOV);

		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::SetOriginalFieldAUTO(const VARIANT FAR& , const VARIANT FAR& ) 
{
	ALL_TRY
	{
		ThrowNavoException(ERCO_TODO,IDPAGE_NOTAVAILABLE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_user::HasFieldBadValueAUTO(long FieldNr)
{
	ALL_TRY
	{
		return has_field_bad_value(FieldNr);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CNEO_user::GetAsTextAUTO() 
{
	ALL_TRY
	{
		return get_as_text().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::SetUserModifAUTO(BOOL bNewVal)
{
	ALL_TRY
	{
		set_user_modified(bNewVal != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CNEO_user::GetMarkDelAUTO() 
{
	ALL_TRY
	{
		if(_get_storage()->IsNew())
		{
			ThrowNavoException2(ERCO_STDOBJ_CANNOT_DEL_NEWOBJ,IDPAGE_NOTAVAILABLE,
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
		}
		
		return get_markdel() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::SetMarkDelAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		if(_get_storage()->IsNew())
		{
			ThrowNavoException2(ERCO_STDOBJ_CANNOT_DEL_NEWOBJ,IDPAGE_NOTAVAILABLE,
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
		}
		if(_get_storage()->GetDefinition()->IsChild())
		{
			CString oString;
			oString.Format("dla obiektów <child> nie mo¿na u¿ywaæ metod markdel/ignore - dotyczy %s[%d]",
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		set_markdel(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_user::GetIgnoreAUTO() 
{
	ALL_TRY
	{
		if(!_get_storage()->IsNew())
		{
			ThrowNavoException2(ERCO_STDOBJ_CANNOT_IGNORE_OLD,IDPAGE_NOTAVAILABLE,
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
				_get_storage()->GetThis());
		}
		return get_markdel() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::SetIgnoreAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		if(!_get_storage()->IsNew())
		{
			ThrowNavoException2(ERCO_STDOBJ_CANNOT_IGNORE_OLD,IDPAGE_NOTAVAILABLE,
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
		}
		if(_get_storage()->GetDefinition()->IsChild())
		{
			CString oString;
			oString.Format("dla obiektów <child> nie mo¿na u¿ywaæ metod markdel/ignore - dotyczy %s[%d]",
				(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		set_markdel(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//--------------------------------------------------------------------------------

BOOL CNEO_user::GetRecalcEnabledAUTO()
{
	ALL_TRY
	{
		return (_get_storage()->get_prop_recalc_enabled() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::SetRecalcEnabledAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		_get_storage()->set_prop_recalc_enabled((bNewValue != FALSE));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


LPDISPATCH CNEO_user::GetStdObjDefAUTO() 
{
	ALL_TRY
	{
		return _get_storage()->GetDefinition()->GetIDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNEO_user::GetTypeAUTO() 
{
	ALL_TRY
	{
		return _get_storage()->GetType();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNEO_user::GetVersionIdAUTO()
{
	ALL_TRY
	{
		return _get_storage()->GetVersion();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_user::GetParentAUTO() 
{
	ALL_TRY
	{
		SCP<CNEO_user> poParentUserSP = _get_parent();
		if(poParentUserSP.PointsObject())
		{
			return poParentUserSP->GetIDispatch(TRUE);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH CNEO_user::GetRealThisAUTO() 
{
	ALL_TRY
	{
		return GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_user::IsNewAUTO() 
{
	ALL_TRY
	{
		ASSERT(_get_storage());
		return _get_storage()->IsNew() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_user::ExclusiveLockAUTO() 
{
	ALL_TRY
	{
		return _exclusive_lock_and_reload();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_user::ExclusiveUnlockAUTO() 
{
	ALL_TRY
	{
		_exclusive_unlock();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CNEO_user::CanDelAUTO() 
{
	ALL_TRY
	{
		ASSERT(_get_storage());
		ASSERT(_get_trans());
		return _get_storage()->_test_can_delete(true,_get_trans()) != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_user::CanSaveAUTO(BOOL bSilent) 
{
	ALL_TRY
	{
		ASSERT(_get_storage());
		ASSERT(_get_trans());
		return _get_storage()->_test_can_save((bSilent != FALSE),_get_trans()) != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

CString CNEO_user::Variant2StringWithDataObject(const CSmartOleVariant & roSOV)
{
	if(roSOV.Type() == VT_DISPATCH)
	{
		if(roSOV.GetDispatch() != NULL)
		{
			SCP<CNEO_user> poDataObjectSP = CNEO_user::FromIDispatch(roSOV.GetDispatch());
			if(poDataObjectSP.PointsObject())
			{
				CString oString;
				oString.Format(" [dataobj] %s(%d)",
					poDataObjectSP->_get_storage()->GetDefinition()->GetTableName(),
					poDataObjectSP->_get_storage()->GetThis());
				return oString;
			}
		}
	}
	return Variant2String(roSOV);
}


// ------ IID_INEDataObject-----------------

STDMETHODIMP_(long) CNEO_user::XNEDataObject::get_i4_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	CSmartOleVariant oSOV;
	pThis->get_field(nOuterFieldNr,oSOV);
	return oSOV.GetLong();
}


STDMETHODIMP_(BSTR) CNEO_user::XNEDataObject::get_bstr_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	CSmartOleVariant oSOV;
	pThis->get_field(nOuterFieldNr,oSOV);
	return CString(oSOV.GetBStr()).AllocSysString();
}

STDMETHODIMP_(long) CNEO_user::XNEDataObject::get_typeid()
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	return pThis->GetTypeAUTO();
}

STDMETHODIMP_(long) CNEO_user::XNEDataObject::get_idobj()
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	return pThis->get_idobj();
}

STDMETHODIMP_(CY) CNEO_user::XNEDataObject::get_cy_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	CSmartOleVariant oSOV;
	pThis->get_field(nOuterFieldNr,oSOV);
	return oSOV.GetCurrency();
}

STDMETHODIMP_(DATE) CNEO_user::XNEDataObject::get_date_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	CSmartOleVariant oSOV;
	pThis->get_field(nOuterFieldNr,oSOV);
	return oSOV.GetDate();
}

STDMETHODIMP_(INEDataObject*) CNEO_user::XNEDataObject::get_obj_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	CSmartOleVariant oSOV;
	pThis->get_field(nOuterFieldNr,oSOV);
	
	SCP<CNEO_user> poUserSP = CNEO_user::FromIDispatch(oSOV.GetDispatch());
	SCP<INEDataObject> poNEDOSP;
	poNEDOSP.QueryInterface(poUserSP);
	return poNEDOSP.Detach();
}

STDMETHODIMP_(INEDataObjectList*) CNEO_user::XNEDataObject::get_list_field(long nOuterFieldNr)
{
	METHOD_PROLOGUE(CNEO_user,NEDataObject)

	return NULL;
}

