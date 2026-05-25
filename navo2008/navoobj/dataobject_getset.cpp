/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObject
	get - set part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CNEO_field::eAssignResult CNEO_field::_assign(SCP<CStdObjFieldDef> & rpoFieldDefSP,
	const CSmartOleVariant & roNewValueSOV,CSmartOleVariant & roOldValueSOV)
{
	ASSERT(rpoFieldDefSP.PointsObject());
	
	if(m_oValueSOV == roNewValueSOV)	//no change - exit
	{
		return ar_ok_nochange;
	}

	//store old value
	roOldValueSOV = m_oValueSOV;		//most assignements will succeed
	
	//analyze field relation
	long nRelType = rpoFieldDefSP->GetRelationType();

	switch(nRelType)
	{
	case RELT_EMBED:
	{
		if(m_oValueSOV.Type() != roNewValueSOV.Type())
		{
			return ar_cant_change_type;
		}
		else
		{
			long nSQLType = rpoFieldDefSP->GetSQLType();
			if(nSQLType == SQLT_MONEY)
			{
				ASSERT(roNewValueSOV.Type() == VT_CY);
				CY curRaw = roNewValueSOV.GetCurrency();

				//zaokr¹glenie do dwóch znaków po precinku
				//-- {{ round_currency_2
				long nDroppedPart = long(curRaw.int64 % __int64(100));
				if(nDroppedPart != 0)
				{
					curRaw.int64 = (curRaw.int64 / __int64(100)) * __int64(100);
					if(nDroppedPart > 49)
					{
						curRaw.int64 += __int64(100);
					}
					else
					{
						if(nDroppedPart < -49)
						{
							curRaw.int64 -= __int64(100);
						}
					}
				}
				//-- }}

				if(m_oValueSOV.GetCurrency().int64 == curRaw.int64)
				{
					return ar_ok_nochange;
				}
				else
				{
					m_oValueSOV = COleCurrency(curRaw);
					return ar_ok;
				}
			}
			else
			{
				if(nSQLType  < SQLT_SMALL)		//test for string length
				{
					DWORD nMaxChars = (nSQLType < SQLT_VARCHAR0) ? CHARLEN(nSQLType) : VARCHARLEN(nSQLType);
					ASSERT(roNewValueSOV.Type() == VT_BSTR);
					if(nMaxChars < wcslen(roNewValueSOV.GetBStr()))
					{
						return ar_string_too_long;
					}
				}
				m_oValueSOV = roNewValueSOV;
			}
			return ar_ok;
		}
	}
	break;
	case RELT_ENUM:
	{
		if(m_oValueSOV.Type() != roNewValueSOV.Type())
		{
			return ar_cant_change_type;
		}
		else
		{
			ASSERT(roNewValueSOV.Type() == VT_I4);
			long nValue = roNewValueSOV.GetLong();
			if(nValue < 0 || nValue > rpoFieldDefSP->GetEnumCount())
			{
				return ar_enum_out_range;
			}
			else
			{
				m_oValueSOV = roNewValueSOV;
				return ar_ok;
			}
		}
	}
	break;
	case RELT_REF:
	case RELT_WILDREF:
	{
		bool bFullPointer = (roNewValueSOV.Type() == VT_DISPATCH);
		if(bFullPointer)
		{
			bFullPointer = (roNewValueSOV.GetDispatch() != NULL);
		}
		if(bFullPointer)
		{
			SCP<CNEO_user> poUserSP = CNEO_user::FromIDispatch(roNewValueSOV.GetDispatch());
			if(poUserSP.PointsNull())
			{
				return ar_alien_ptr;
			}
			long nRefTypeId = poUserSP->_get_storage()->GetType();
			
			if(nRelType == RELT_WILDREF)	//check
			{
				if(!rpoFieldDefSP->IsWildRefTypeIdAllowed(nRefTypeId))
				{
					return ar_ref_to_bad_type;
				}
			}
			else
			{
				if(nRefTypeId != rpoFieldDefSP->GetReferenceTypeId())		//musi zgadzaæ siê z deklaracj¹
				{
					return ar_ref_to_bad_type;
				}
			}
			if(m_oValueSOV.GetCurrency().Hi == nRefTypeId && 
				long(m_oValueSOV.GetCurrency().Lo) == poUserSP->_get_storage()->GetThis())
			{
				return ar_ok_nochange;
			}
			else
			{
				_raw_set_ref_value(nRefTypeId,poUserSP->_get_storage()->GetThis());
				return ar_ok;
			}
		}
		else	//wyzerowanie
		{
			//test poprawnoœci intencji (dozwolone 0 (long lub short))
			if(roNewValueSOV.Type() != VT_DISPATCH)
			{
				VARTYPE vt = roNewValueSOV.Type();
				if(vt != VT_I4 && vt != VT_I2)
				{
					return ar_long_or_disp;
				}
				if((vt == VT_I4 && roNewValueSOV.GetLong()  != 0) || 
				   (vt == VT_I2 && roNewValueSOV.GetShort() != 0))
				{
					return ar_long_or_disp;
				}
			}
			else
			{
				ASSERT(roNewValueSOV.GetDispatch() == NULL);	//nic innego byæ nie mo¿e
			}
			ASSERT(m_oValueSOV.Type() == VT_CY);
			if(m_oValueSOV.GetCurrency().Lo == 0)	//jest ju¿ 0
			{
				return ar_ok_nochange;
			}
			else
			{
				m_oValueSOV = rpoFieldDefSP->GetDefaultValue();
				return ar_ok;
			}
		}
	}
	break;
	case RELT_FILE:	//internal use only
	{
		ASSERT(roNewValueSOV.Type() == VT_I4);
		m_oValueSOV = roNewValueSOV;
		return ar_ok;
	}
	break;
	case RELT_LIST:
		return ar_not_allowed;
	default:
		ASSERT(false);
	}

	return ar_internal_error;
}

bool CNEO_field::_test_can_save(SCP<CStdObjFieldDef> & rpoFieldDefSP,CNEO_storage * poStorage,CNEO_trans * poTrans,bool bSilent)
{
	ASSERT(rpoFieldDefSP.PointsObject());
	ASSERT(poTrans);
	ASSERT(poStorage);

	long nRelationType = rpoFieldDefSP->GetRelationType();
	switch(nRelationType)
	{
	case RELT_EMBED:
	case RELT_ENUM:
	{
		if(rpoFieldDefSP->IsNonEmpty() || rpoFieldDefSP->IsUnique())
		{
			long nSQLType = rpoFieldDefSP->GetSQLType();
			bool bOK = true;

			switch(nSQLType)
			{
			case SQLT_DATE:
			{
				ASSERT(m_oValueSOV.Type() == VT_DATE);
				bOK = (GetNullDateSOV() != m_oValueSOV);
			}
			break;
			case SQLT_INT:
			{
				bOK = (m_oValueSOV.GetLong() != 0);
			}
			break;
			case SQLT_TIME:
			{
				bOK = (m_oValueSOV != GetNullTimeSOV());
			}
			break;
			case SQLT_MONEY:
			case SQLT_QUANTITY:
			{
				ASSERT(m_oValueSOV.Type() == VT_CY);
				bOK = (m_oValueSOV.GetCurrency().int64 != __int64(0));
			}
			break;
			default:
				if(nSQLType < SQLT_SMALL) //char or varchar
				{
					ASSERT(m_oValueSOV.Type() == VT_BSTR);
					CString oTestString(m_oValueSOV.GetBStr());
					oTestString.TrimRight();
					bOK = !oTestString.IsEmpty();
				}
			}

			if(!bOK)
			{
				if(!bSilent)
				{
					CString oDescriptionString;
					NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_FIELD_MUST_BE_NONEMPTY,
						rpoFieldDefSP->GetHumanName(),
						poStorage->GetDefinition()->GetHumanName()
						/*,poStorage->GetType(),poStorage->GetThis()*/);
					CNavoErrorInfo oNavoErrorInfo(ERCO_STDOBJ_FIELD_MUST_BE_NONEMPTY,
						IDPAGE_NOTAVAILABLE,oDescriptionString);
					poTrans->AddMessage(oNavoErrorInfo);
				}
				//ustaw flagê "jest Ÿle"
				set_bad_value();
				return false;
			}
		}
		if(rpoFieldDefSP->IsUnique())
		{
			CString oWhereString;
			const TCHAR * lpFormatString = _T("%s.%s='%s'");
			long nSQLType = rpoFieldDefSP->GetSQLType();
			if(nSQLType == SQLT_INT)
			{
				lpFormatString = _T("%s.%s=%s");
			}
			
			ASSERT(lpFormatString != NULL);

			oWhereString.Format(lpFormatString,
				poStorage->GetDefinition()->GetTableName(),
				rpoFieldDefSP->GetName(),
				Variant2SQLString(m_oValueSOV));
			
			long IdObj = poTrans->FindStdObjAUTO(poStorage->GetType(),oWhereString);

			if(IdObj > 0 && IdObj != poStorage->GetThis())
			{
				if(!bSilent)
				{
					CString oDescriptionString;
					NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_FIELD_MUST_UNIQUE,
						rpoFieldDefSP->GetHumanName(),
						poStorage->GetDefinition()->GetHumanName()
						/*,poStorage->GetType(),poStorage->GetThis()*/);
					CNavoErrorInfo oNavoErrorInfo(ERCO_STDOBJ_FIELD_MUST_UNIQUE,
						IDPAGE_NOTAVAILABLE,oDescriptionString);
					poTrans->AddMessage(oNavoErrorInfo);
				}
				//ustaw flagê "jest Ÿle"
				set_bad_value();
				return false;
			}
		}
		return true;
	}
	break;
	case RELT_REF:
	case RELT_WILDREF:
	{
		ASSERT(m_oValueSOV.Type() == VT_CY);
		bool bIsNull = (m_oValueSOV.GetCurrency().Lo == 0);

		if(bIsNull)
		{	
			if(!rpoFieldDefSP->IsRefOptional())
			{
				if(!bSilent)
				{
					CString oDescriptionString;
					NavoFormatErrorMsg(oDescriptionString,ERCO_STDOBJ_REF_IS_REQUIRED,
						rpoFieldDefSP->GetHumanName(),
						poStorage->GetDefinition()->GetHumanName()
						/*,poStorage->GetType(),poStorage->GetThis()*/);
					CNavoErrorInfo oNavoErrorInfo(ERCO_STDOBJ_REF_IS_REQUIRED,
						IDPAGE_NOTAVAILABLE,oDescriptionString);
					poTrans->AddMessage(oNavoErrorInfo);
				}
				//ustaw flagê "jest Ÿle"
				set_bad_value();
				return false;
			}
		}
		return true;
	}
	break;
	
	}
	return true;
}

CNEO_field::eAssignResult CNEO_storage::_begin_set_field(const long nOuterFieldNr,const CSmartOleVariant & roNewValueSOV,
							  CSmartOleVariant & roOldValueSOV,bool & rbRecalc)
{
	if(nOuterFieldNr < 1 || nOuterFieldNr > m_oFields.GetUpperBound() + 1)
	{
		ThrowNavoException4(ERCO_STDOBJ_INVALID_FIELD_NR,IDPAGE_NOTAVAILABLE,
			GetType(),GetThis(),nOuterFieldNr,GetDefinition()->GetTableName());
	}
	long nInnerFieldNr = nOuterFieldNr - 1;
	
	ASSERT(nInnerFieldNr >= 0 && nInnerFieldNr <= m_oFields.GetUpperBound());

	SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(nOuterFieldNr);
	CNEO_field::eAssignResult eAR = m_oFields[nInnerFieldNr]._assign(rpoFieldDefSP,roNewValueSOV,roOldValueSOV);
	
	if(eAR == CNEO_field::ar_ok && m_bConstructed && get_prop_recalc_enabled())
	{
		rbRecalc = rpoFieldDefSP->IsRecalc();
	}
	else
	{
		rbRecalc = false;
	}
	
	ASSERT(IsPlainVariant(m_oFields[nInnerFieldNr]._get_value())
		|| rpoFieldDefSP->IsVirtual());	//przed rekalkiem jest plain lub polem virtualnym
	
	return eAR;
}

void CNEO_storage::_finish_set_field(const long nOuterFieldNr)
{
	long nInnerFieldNr = nOuterFieldNr - 1;
	//skasuj flagê "jest Ÿle"
	m_oFields[nInnerFieldNr].clear_bad_value();
	bool bVirtualField = GetDefinition()->GetField(nOuterFieldNr)->IsVirtual();

	if(!bVirtualField)
	{
		//ustaw flagê "by³o przypisanie zmieniaj¹ce wartoœæ" (dla pola)
		m_oFields[nInnerFieldNr].set_assigned();
		//i dla obiektu
		m_eNeedSave = ns_unknown;
		m_eUserModif = um_unknown;
	}
	
	ASSERT(IsPlainVariant(m_oFields[nInnerFieldNr]._get_value()) || bVirtualField);	//na koñcu te¿ jest plain lub polem virtualnym
}

void CNEO_storage::_explain_set_field_error(CNEO_field::eAssignResult eAR,const long nOuterFieldNr,
	errorcode & reErco,CString & roTableName,CString & roFldName,long & rnTypeId,long & rnIdObj)
{
	//error - generate message
	roTableName = GetDefinition()->GetHumanName();
	roFldName = GetDefinition()->GetField(nOuterFieldNr)->GetHumanName();
	rnTypeId = GetType();
	rnIdObj = GetThis();

	switch(eAR)
	{
	case CNEO_field::ar_long_or_disp:	//must be long or dispatch
		reErco = ERCO_STDOBJ_REF_MUST_BE_DISP_OR_LONG;
	break;
	case CNEO_field::ar_cant_change_type://cannot change type
		reErco = ERCO_STDOBJ_CANNOT_CHANGE_FIELD_TYPE;
	break;
	case CNEO_field::ar_enum_out_range:	//enum value out of range
		reErco = ERCO_STDOBJ_EXCEED_ENUM_VALUE;
	break;
	case CNEO_field::ar_string_too_long:	//string too long
		reErco = ERCO_STDOBJ_EXCEED_FIELD_MAXLEN;
	break;
	case CNEO_field::ar_ref_to_bad_type:	//reference to not allowed type
		reErco = ERCO_STDOBJ_REF_TO_ANOTHER_TYPE;
	break;
	case CNEO_field::ar_not_allowed:		//set not allowed
		reErco = ERCO_STDOBJ_SET_NOT_ALLOWED;
	break;
	case CNEO_field::ar_alien_ptr:		//ptr to 'alien' object
		reErco = ERCO_TODO;
	break;
	default:
		reErco = ERCO_NOTAVAILABLE;
	}
}

void CNEO_storage::_get_field(const long nOuterFieldNr,CSmartOleVariant & roSOV,long & rnRelationType)
{
	if(nOuterFieldNr < 0 || nOuterFieldNr > m_oFields.GetUpperBound() + 1)
	{
		ThrowNavoException4(ERCO_STDOBJ_INVALID_FIELD_NR,IDPAGE_NOTAVAILABLE,
			GetType(),GetThis(),nOuterFieldNr,GetDefinition()->GetTableName());
	}
	if(nOuterFieldNr == 0)
	{
		roSOV = CSmartOleVariant(GetThis(),VT_I4);
		rnRelationType = RELT_EMBED;
		return;
	}

	long nInnerFieldNr = nOuterFieldNr - 1;
	ASSERT(nInnerFieldNr >= 0 && nInnerFieldNr <= m_oFields.GetUpperBound());

	SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(nOuterFieldNr);
	rnRelationType = rpoFieldDefSP->GetRelationType();
	roSOV = m_oFields[nInnerFieldNr]._get_value();
}

void CNEO_storage::_undo_setfield(long nInternalFldNr,const CSmartOleVariant & roSOV)
{
	m_oFields[ nInternalFldNr ]._access_value() = roSOV;
}

bool CNEO_storage::_has_field_bad_value(const long nOuterFieldNr) const
{
	if(nOuterFieldNr < 1 || nOuterFieldNr > m_oFields.GetUpperBound() + 1)
	{
		ThrowNavoException4(ERCO_STDOBJ_INVALID_FIELD_NR,IDPAGE_NOTAVAILABLE,
			GetType(),GetThis(),nOuterFieldNr,GetDefinition()->GetTableName());
	}
	long nInnerFieldNr = nOuterFieldNr - 1;
	
	return m_oFields[nInnerFieldNr].is_bad_value();
}

void CNEO_storage::_set_field_bad_value(const long nOuterFieldNr,bool bBad)
{
	if(nOuterFieldNr < 1 || nOuterFieldNr > m_oFields.GetUpperBound() + 1)
	{
		ThrowNavoException4(ERCO_STDOBJ_INVALID_FIELD_NR,IDPAGE_NOTAVAILABLE,
			GetType(),GetThis(),nOuterFieldNr,GetDefinition()->GetTableName());
	}
	long nInnerFieldNr = nOuterFieldNr - 1;
	
	if(bBad)
	{
		m_oFields[ nInnerFieldNr ].set_bad_value();
	}
	else
	{
		m_oFields[ nInnerFieldNr ].clear_bad_value();
	}
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------




void CNEO_user::_resolve_field(long nOuterFieldNr,CSmartOleVariant & roSOV,long nRelationType,bool bNew)
{
	ASSERT(_get_trans());
	ASSERT(_get_storage());

	switch(nRelationType)
	{
	case RELT_EMBED:
	case RELT_ENUM:
	break;
	case RELT_REF:
	case RELT_WILDREF:
		ASSERT(roSOV.Type() == VT_CY);
		{
			CY cyTypeIdObj = roSOV.GetCurrency();
			if(cyTypeIdObj.Lo != 0)
			{
				//info: _get_object dostaje ostatnie parametry 0,0 poniewa¿ nie
				//ma referencji do dzieci (mog¹ byæ do ojców)

				ASSERT(cyTypeIdObj.Hi != 0);
				SCP<CNEO_user> poUserSP = _get_trans()->
					_get_object(cyTypeIdObj.Hi,cyTypeIdObj.Lo,0,0);
				if(poUserSP.PointsObject())
				{
					roSOV = CSmartOleVariant(poUserSP->GetDispatch(true),FALSE);
				}
				else
				{
					//rekord niedostêpny lub usuniêty
					//VB nothing
					roSOV = CSmartOleVariant(LPDISPATCH(NULL),false);
				}
			}
			else
			{
				//VB nothing
				roSOV = CSmartOleVariant(LPDISPATCH(NULL),false);
			}
		}
		ASSERT(roSOV.Type() == VT_DISPATCH);
	break;
	case RELT_LIST:
	{
		ASSERT(roSOV.Type() == VT_I4);
		ASSERT(roSOV.GetLong() == 0);
		{
			long nCollectionId = _compose_collection_id(_get_storage()->GetType(),nOuterFieldNr);
			long nParentIdObj = _get_storage()->GetThis();
			SCP<CNEO_listuser> poListUserSP;
			if(bNew)
			{
				poListUserSP = _get_trans()->_get_list(nCollectionId,nParentIdObj,_get_storage()->IsNew());
			}
			else
			{
				poListUserSP = _get_trans()->_get_old_list(nCollectionId,nParentIdObj);
			}
#ifdef _DEBUG
			if(bNew)
			{
				ASSERT(poListUserSP.PointsObject());
			}
#endif
			if(poListUserSP.PointsObject())
			{
				roSOV = CSmartOleVariant(poListUserSP->GetDispatch(true),FALSE);
			}
			else
			{
				roSOV = CSmartOleVariant(LPDISPATCH(NULL),FALSE);
			}
		}
		ASSERT(roSOV.Type() == VT_DISPATCH);
	}
	break;
	case RELT_FILE:
		ASSERT(roSOV.Type() == VT_I4);
		{
			long nParentTypeId = _get_storage()->GetType();
			long nParentIdObj= _get_storage()->GetThis();
			SCP<CNEO_fileuser> poFileUserSP = 
				_get_trans()->_get_file(nParentTypeId,nParentIdObj,nOuterFieldNr,_get_storage()->IsNew());
			roSOV = CSmartOleVariant(poFileUserSP->GetDispatch(true),FALSE);
		}
		ASSERT(roSOV.Type() == VT_DISPATCH);
	break;
	default:
		ASSERT(false);
	}
}

void CNEO_user::_enable_changes()
{
	if(m_bReadOnlyStorage)
	{
		SCP<CNEO_storage> poROStorageSP = m_poStorageSP;
		m_poStorageSP = m_poTransSP->_copy_on_write_storage(m_poStorageSP);
		if(poROStorageSP != m_poStorageSP)
		{
			m_poStorageSP->AddRef_User();
			poROStorageSP->Release_User();
		}
		m_bReadOnlyStorage = false;
		ASSERT(_get_storage());
	}
}

bool CNEO_user::_internal_set_field(long nOuterFieldNr,const CSmartOleVariant & roSOV)
{
	ASSERT(_get_storage());

	//switch from RO storage to our 'writable' copy if necessary
	_enable_changes();

#ifdef _DEVELOPER_EDITION_ENABLE_TRIGGER_EXCEPTION
	if(_get_trans()->_get_coordinator()->GetCurrentTrans() != _get_trans().Get())
	{
		CString oString;
		oString.Format("obiekt %s[%d] jest z transakcji # %d i nie wolno do niego przypisywaæ w tej (# %d)",
			(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
			_get_storage()->GetThis(),
			_get_trans()->_debug_trans_nr,
			_get_trans()->_get_coordinator()->GetCurrentTrans()->_debug_trans_nr
			);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}

	if(_get_trans()->fwd_was_trigger_fired(_get_storage()->GetType(),_get_storage()->GetThis()) == tfp_fired)
	{
		CString oString;
		oString.Format("dla obiektu %s[%d] by³ ju¿ wo³any trigger w tej transakcji",
			(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
			_get_storage()->GetThis());
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
#endif

	//begin assignment
	CSmartOleVariant oOldValueSOV;
	bool bCallRecalc;
	CNEO_field::eAssignResult eAR = _get_storage()->_begin_set_field(nOuterFieldNr,roSOV,oOldValueSOV,bCallRecalc);

#ifdef _DEVELOPER_EDITION_ENABLE_TRIGGER_EXCEPTION
	CDebuggerCallHolder oDCH;
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		oDCH++.StoreMsg("let %s[%d].%s=%s (oldval=%s)",
			(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
			_get_storage()->GetThis(),
			(LPCTSTR)_get_storage()->GetDefinition()->GetField(nOuterFieldNr)->GetName(),
			Variant2StringWithDataObject(roSOV),
			Variant2StringWithDataObject(oOldValueSOV));
	}
#endif

	if(eAR == CNEO_field::ar_ok_nochange)
	{
		return true;
	}

	if(eAR == CNEO_field::ar_ok)
	{
		/*
			undo rejestrujemy gdy nie wiemy czy siê przypisanie powiedzie siê ostatecznie.
			mo¿e to byæ ze wzglêdu, ¿e jesteœmy wewn¹trz recalc'a, triggera itd.
			lub w³aœnie zaczynamy recalc
		*/
		
		CNEO_rollbackholder oRollbackHolder(_get_trans());
		if(bCallRecalc || !oRollbackHolder._is_toplevel())
		{
			oRollbackHolder._registerundo_objectfieldchange(_get_storage()->GetType(),_get_storage()->GetThis(),
				nOuterFieldNr - 1,oOldValueSOV);
			
			if(bCallRecalc)
			{
				_resolve_field(nOuterFieldNr,oOldValueSOV,
					_get_storage()->GetDefinition()->GetField(nOuterFieldNr)->GetRelationType(),true);
				if(!_call_recalc(nOuterFieldNr,oOldValueSOV))
				{
					return false;	//holder przywróci star¹ wartoœæ pola
				}
			}
		}
		oRollbackHolder.Success();
		_get_storage()->_finish_set_field(nOuterFieldNr);
		return true;
	}
	
	//generate error message
	{
		errorcode eErco;
		CString oTableName;
		CString oFldName;
		long nTypeId;
		long nIdObj;
		_get_storage()->_explain_set_field_error(eAR,nOuterFieldNr,
			eErco,oTableName,oFldName,nTypeId,nIdObj);

		CString oDescriptionString;
		CString oValueString;
		Variant2Display(roSOV,oValueString);
		if(oValueString.GetLength() > 255)
		{
			oValueString = oValueString.Left(255) + "...";
		}
		
		NavoFormatErrorMsg(oDescriptionString,eErco,oFldName,oTableName,oValueString/*,nTypeId,nIdObj*/);
		CNavoErrorInfo oNavoErrorInfo(eErco,IDPAGE_NOTAVAILABLE,oDescriptionString);
		_get_trans()->AddMessage(oNavoErrorInfo);
	}
	return false;
}

void CNEO_user::set_field(long nOuterFieldNr,const CSmartOleVariant & roSOV)
{
	if(!_internal_set_field(nOuterFieldNr,roSOV))
	{
		ThrowNavoException3(ERCO_STDOBJ_INVALID_VALUE_FOR_FIELD,IDPAGE_NOTAVAILABLE,
			(LPCTSTR)_get_storage()->GetDefinition()->GetField(nOuterFieldNr)->GetName(),
			(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
			(LPCTSTR) Variant2String(roSOV));
	}
}

void CNEO_user::get_field(long nOuterFieldNr,CSmartOleVariant & roSOV)
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());

#ifdef _DEVELOPER_EDITION_
	if(_get_trans()->_get_coordinator()->GetCurrentTrans() != _get_trans().Get())
	{
		CString oString;
		oString.Format("obiekt %s[%d] jest z transakcji # %d i nie wolno z niego czytaæ w tej (# %d)",
			(LPCTSTR)_get_storage()->GetDefinition()->GetTableName(),
			_get_storage()->GetThis(),
			_get_trans()->_debug_trans_nr,
			_get_trans()->_get_coordinator()->GetCurrentTrans()->_debug_trans_nr
			);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
#endif

	long nRelationType;
	_get_storage()->_get_field(nOuterFieldNr,roSOV,nRelationType);
	
	ASSERT(IsPlainVariant(roSOV)|| _get_storage()->GetDefinition()->GetField(nOuterFieldNr)->IsVirtual());
	
	_resolve_field(nOuterFieldNr,roSOV,nRelationType,true);
}


void CNEO_user::get_original_field(long nOuterFieldNr,CSmartOleVariant & roSOV)
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());

	SCP<CNEO_storage> poRefStorageSP = _get_trans()->_search_reference_storage_map(
		_get_storage()->GetType(),_get_storage()->GetThis());
	long nRelationType;
	if(poRefStorageSP.PointsNull())
	{
		//jeœli nie by³o zmian zwróæ aktualn¹ wersjê
		ASSERT(m_bReadOnlyStorage);
		_get_storage()->_get_field(nOuterFieldNr,roSOV,nRelationType);
	}
	else
	{
		poRefStorageSP->_get_field(nOuterFieldNr,roSOV,nRelationType);
	}
	
	ASSERT(IsPlainVariant(roSOV) || _get_storage()->GetDefinition()->GetField(nOuterFieldNr)->IsVirtual());

	_resolve_field(nOuterFieldNr,roSOV,nRelationType,false);
}

void CNEO_user::set_markdel(bool bMarkDel)
{

	bool bOldMarkDel = get_markdel(); 
	if(!(bMarkDel ^ bOldMarkDel))
	{
		return;
	}
	//real change

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("MARKDEL for %s(%d)\n",
			_get_storage()->GetDefinition()->GetTableName(),_get_storage()->GetThis());
	}
#endif

	//switch from RO storage to our 'writable' copy if necessary
	_enable_changes();

	CNEO_rollbackholder oRollbackHolder(_get_trans());
	_get_storage()->_set_mark_del(bMarkDel);
	
	if(!oRollbackHolder._is_toplevel())
	{
		oRollbackHolder._registerundo_markdelobject(_get_storage()->GetType(),_get_storage()->GetThis(),bOldMarkDel);
	}
	//for each list contained in this object
	CStdObjDef * poDefinition = _get_storage()->GetDefinition();
	if(poDefinition->HasAnyList() || poDefinition->HasAnyFile())
	{
		CStdObjDef * poDefinition = _get_storage()->GetDefinition();
		for(long iter = 1; iter < poDefinition->GetFieldCount(); iter++)
		{
			long nRelationType = poDefinition->GetField(iter)->GetRelationType();
			if(nRelationType == RELT_LIST)
			{
				long nCollectionId = _compose_collection_id(_get_storage()->GetType(),iter);
				long nParentIdObj = _get_storage()->GetThis();
				SCP<CNEO_listuser> poListUserSP = _get_trans()->_get_list(nCollectionId,nParentIdObj,_get_storage()->IsNew());
				ASSERT(poListUserSP.PointsObject());
				poListUserSP->_raw_set_markdel(bMarkDel);
			}
			else if(nRelationType == RELT_FILE)
			{
				long nParentTypeId = _get_storage()->GetType();
				long nParentIdObj = _get_storage()->GetThis();
				SCP<CNEO_fileuser> poFileUserSP = _get_trans()->_get_file(nParentTypeId,nParentIdObj,iter,_get_storage()->IsNew());
				ASSERT(poFileUserSP.PointsObject());
				poFileUserSP->_raw_set_markdel(bMarkDel);
			}

		}
	}
	oRollbackHolder.Success();
}

bool CNEO_user::get_markdel()
{
	ASSERT(_get_storage());
	return _get_storage()->_is_mark_del();
}








