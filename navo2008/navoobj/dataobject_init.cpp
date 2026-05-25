/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObject
	initialization 
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobjcache.h"
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


CNEO_storage::CNEO_storage(CNEO_global_cache * poGlobalCache,
		long nTypeId,long nIdObj,CStdObjDef * poDefinition) :
	m_poGlobalCache(poGlobalCache),
	m_nTypeId(nTypeId),
	m_nIdObj(nIdObj),
	m_nVersionId(-1),
	m_poDefinition(poDefinition),
	m_eState(debug_state),
	m_dwUserRef(0),
	m_eNeedSave(ns_no),
	m_eUserModif(um_no),
	m_bMarkDel(false),
	m_bConstructed(false),
	m_bRecalcEnabled(true)
{
	m_cyParent.int64 = __int64(0);

	ASSERT(m_nTypeId > 0);
	ASSERT(m_nIdObj > 0);
	ASSERT(m_poDefinition);
	ASSERT(m_poDefinition->GetFieldCount() >= 2);

	m_oFields.SetSize(m_poDefinition->GetFieldCount()-1);
}

CNEO_storage::~CNEO_storage()
{
}

void CNEO_storage::OnFinalRelease()
{
	if(m_poGlobalCache)
	{
		m_poGlobalCache->OnNEO_storage_FinalRelease(this);
	}
	else
	{
		delete this;
	}
}

void CNEO_storage::_initnew(CNEO_trans * poTrans)
{
	ASSERT(m_oFields.GetSize() == GetDefinition()->GetFieldCount()-1);

	for(long iter = 1; iter <= m_oFields.GetSize(); iter++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(iter);
		long nRelationType = rpoFieldDefSP->GetRelationType();
		
		bool bDateToday = false;
		if(nRelationType == RELT_EMBED)
		{
			if(rpoFieldDefSP->GetSQLType() == SQLT_DATE)
			{
				ASSERT(rpoFieldDefSP->GetDefaultValue().Type() == VT_DATE);
				if(rpoFieldDefSP->GetDefaultValue().GetDate() == DATE(0.0))	//no default value
				{
					bDateToday = true;
				}
			}
		}
		if(bDateToday)
		{
			ASSERT(poTrans != NULL);
			poTrans->get_var(GVAR_TODAY,m_oFields[iter-1]._access_value());
		}
		else
		{
			m_oFields[iter-1]._access_value() = rpoFieldDefSP->GetDefaultValue();
		}
		
		ASSERT(IsPlainVariant_or_Nothing(m_oFields[iter-1]._get_value()));
	}
	
	m_nVersionId = 0;		//nowy ma zawsze wersjê 0
	m_eState = new_data;
	m_eNeedSave = ns_yes;
	m_eUserModif = um_yes;
}

void CNEO_storage::_postprocess()
{
	if(_is_mark_del())
	{
		if(IsOld())
		{
			m_eState = del_data;
		}
		else
		{
			ASSERT(IsNew());
		}
	}
	else
	{

		if(IsNew())
		{
			m_eState = old_data;
		}
		
		//clear assigned flag
		for(long iter = 0; iter <= m_oFields.GetUpperBound(); iter++)
		{
			m_oFields[ iter ].clear_assigned();
			m_oFields[ iter ].clear_bad_value();
		}

		m_nVersionId++;
	}
	m_eNeedSave = ns_no;
	m_eUserModif = um_no;
	m_bMarkDel = false;

	TRACE("postprocessed storage: %s[%d]\n",GetDefinition()->GetTableName(),GetThis());
}

bool CNEO_storage::_custom_init(CNEO_user * poUser)
{
	m_bConstructed = false;

	ASSERT(poUser);

	//inicjowanie musi siê odbywaæ na this !!
	ASSERT(poUser->_get_storage().Get() == this);

	bool bOK = true;

	if(IsNew())
	{
		if(GetDefinition()->IsFunctionDefined(CLASS_CTOR))
		{
			bOK = poUser->_call_trigger(CLASS_CTOR);
		}
	}
	else
	{
		if(GetDefinition()->IsFunctionDefined(CLASS_REGENER))
		{
			bOK = poUser->_call_trigger(CLASS_REGENER);
		}
	}

	m_bConstructed = true;
	return bOK;
}

void CNEO_storage::_readbinary(CNEO_trans * poTrans,CFlatData & roFlatData)
{
	PBYTE pMem = roFlatData.GetDataPtr();
	CFlatData::CFDHeader oFDHeader(pMem);
	
	//z cache'a lub nie
	ASSERT(GetDefinition());
	ASSERT( oFDHeader.Action() == action_get || oFDHeader.Action() == action_insert || oFDHeader.Action() == action_update);
	ASSERT( oFDHeader.TypeId() == m_nTypeId );
	ASSERT( oFDHeader.IdObj()  == m_nIdObj );
	ASSERT( oFDHeader.VersionId() >= 1);
	
	pMem += CFlatData::CFDHeader::Size();
	long nFieldCount = GetDefinition()->GetFieldCount();
	ASSERT(m_oFields.GetSize() == nFieldCount-1);
	for(long iter = 1; iter < nFieldCount; iter++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(iter);
		long nSQLType = rpoFieldDefSP->GetSQLType();
		long nRelationType = rpoFieldDefSP->GetRelationType();
		if(nSQLType != SQLT_IGNORE)
		{
			pMem += Binary2VariantHelper(nSQLType,m_oFields[iter-1]._access_value(),pMem);
			if(nRelationType == RELT_REF || nRelationType == RELT_WILDREF)
			{
				long nIdObj;
				long nTypeId;
				ASSERT(m_oFields[iter-1]._get_value().Type() == VT_I4);
				nIdObj = m_oFields[iter-1]._get_value().GetLong();
				if(nRelationType == RELT_REF)
				{
					nTypeId = rpoFieldDefSP->GetReferenceTypeId();
				}
				else
				{
					CSmartOleVariant oTypeIdSOV;
					pMem += Binary2VariantHelper(SQLT_INT,oTypeIdSOV,pMem);
					nTypeId = oTypeIdSOV.GetLong();
				}
				m_oFields[iter-1]._raw_set_ref_value(nTypeId,nIdObj);
			}
			ASSERT(IsPlainVariant(m_oFields[iter-1]._get_value()));
		}
		else
		{
			//virtual or other non-persistent
			bool bDateToday = false;
			if(nRelationType == RELT_EMBED)
			{
				if(nSQLType == SQLT_DATE)
				{
					ASSERT(rpoFieldDefSP->GetDefaultValue().Type() == VT_DATE);
					if(rpoFieldDefSP->GetDefaultValue().GetDate() == DATE(0.0))	//no default value
					{
						bDateToday = true;
					}
				}
			}

			if(bDateToday)
			{
				ASSERT(poTrans != NULL);
				poTrans->get_var(GVAR_TODAY,m_oFields[iter-1]._access_value());
			}
			else
			{
				m_oFields[iter-1]._access_value() = rpoFieldDefSP->GetDefaultValue();
			}
	
			ASSERT(IsPlainVariant_or_Nothing(m_oFields[iter-1]._get_value()));
		}

	}
	ASSERT(pMem == roFlatData.GetDataPtr() + roFlatData.GetDataLen());
	m_nVersionId = oFDHeader.VersionId();
	m_eState = old_data;
	m_eNeedSave = ns_no;
	m_eUserModif = um_no;
}

void CNEO_storage::_writebinary4save(CFlatData & roFlatData)
{
	long nDataSize = CFlatData::CFDHeader::Size();
	for(long nField = 1; nField <= m_oFields.GetSize(); nField++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(nField);
		long nSQLType = rpoFieldDefSP->GetSQLType();
		long nRelationType = rpoFieldDefSP->GetRelationType();
		if(nSQLType != SQLT_IGNORE)
		{
			ASSERT(IsPlainVariant(m_oFields[nField-1]._get_value()));
			switch(nRelationType)
			{
			case RELT_EMBED:
				nDataSize += Variant2BinaryHelper(nSQLType,m_oFields[nField-1]._get_value());
			break;
			case RELT_ENUM:
				nDataSize += sizeof(long);
			break;
			case RELT_WILDREF:
				nDataSize += sizeof(long);
			//no break
			case RELT_REF:
				nDataSize += sizeof(long);
			break;
			case RELT_FILE:
			case RELT_LIST:		//impossible
			default:
				ASSERT(false);	//unknown type
			}
		}
	}
	PBYTE pNewMem = roFlatData.GrowBy(nDataSize);
	CFlatData::CFDHeader oFDHeader(pNewMem);
	oFDHeader.Length() = nDataSize;
	oFDHeader.Action() = IsNew() ? action_insert : action_update;
	oFDHeader.TypeId() = GetType();
	oFDHeader.IdObj()  = GetThis();
	oFDHeader.VersionId() = GetVersion();
	pNewMem += CFlatData::CFDHeader::Size();

	for(long nField = 1; nField <= m_oFields.GetSize(); nField++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(nField);
		long nSQLType = rpoFieldDefSP->GetSQLType();
		long nRelationType = rpoFieldDefSP->GetRelationType();
		if(nSQLType != SQLT_IGNORE)
		{
			ASSERT(IsPlainVariant(m_oFields[nField-1]._get_value()));

			switch(nRelationType)
			{
			case RELT_EMBED:
				pNewMem += Variant2BinaryHelper(nSQLType,m_oFields[nField-1]._get_value(),pNewMem);
			break;
			case RELT_ENUM:
				*(long *)pNewMem = m_oFields[nField-1]._get_value().GetLong(); 
				pNewMem += sizeof(long);
			break;
			case RELT_REF:
			case RELT_WILDREF:
			{
				CY tmpCY = m_oFields[nField-1]._get_value().GetCurrency();
				*(long *)pNewMem = tmpCY.Lo; 
				pNewMem += sizeof(long);
				if(nRelationType == RELT_WILDREF)
				{
					*(long *)pNewMem = tmpCY.Hi;
					pNewMem += sizeof(long);
				}
			}
			break;
			case RELT_FILE:
			case RELT_LIST:		//impossible
			default:
				ASSERT(false);	//unknown type
			}
		}
	}

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		CDebuggerCallHolder oDCH;
		oDCH++.StoreMsg("DB:%s %s[%d:%d]\n",(IsNew() ? "INS": "UPD"),GetDefinition()->GetTableName(),GetType(),GetThis());
	}
#endif

}

void CNEO_storage::_writebinary4del(CFlatData & roFlatData)
{
	long nDataSize = CFlatData::CFDHeader::Size();
	PBYTE pNewMem = roFlatData.GrowBy(nDataSize);
	CFlatData::CFDHeader oFDHeader(pNewMem);
	oFDHeader.Length() = nDataSize;
	oFDHeader.Action() = action_delete;
	oFDHeader.TypeId() = GetType();
	oFDHeader.IdObj()  = GetThis();
	oFDHeader.VersionId() = GetVersion();

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		CDebuggerCallHolder oDCH;
		oDCH++.StoreMsg("DB:DEL %s[%d:%d]\n",GetDefinition()->GetTableName(),GetType(),GetThis());
	}
#endif

}

SCP<CNEO_storage> CNEO_storage::clone()
{
	//construct copy
	SCP<CNEO_storage> poNewStorageSP = NewSCP(new CNEO_storage(NULL,m_nTypeId,m_nIdObj,m_poDefinition));
	
	//copy data
	poNewStorageSP->_copy_from(*this);
	poNewStorageSP->m_bMarkDel = m_bMarkDel;

	return poNewStorageSP;
}

void CNEO_storage::_copy_from(const CNEO_storage & roStorage)
{
	ASSERT(m_nTypeId == roStorage.m_nTypeId);
	ASSERT(m_nIdObj == roStorage.m_nIdObj);
	
	m_nVersionId = roStorage.m_nVersionId;
	m_cyParent = roStorage.m_cyParent;
	m_eState = roStorage.m_eState;
	m_oFields.Copy(roStorage.m_oFields);

	m_eNeedSave = roStorage.m_eNeedSave;
	m_eUserModif = roStorage.m_eUserModif;
	m_bConstructed = roStorage.m_bConstructed;
	m_bRecalcEnabled = roStorage.m_bRecalcEnabled;
}

void CNEO_storage::_copy_bad_status(const CNEO_storage & roStorage)
{
	ASSERT(m_nTypeId == roStorage.m_nTypeId);
	ASSERT(m_nIdObj == roStorage.m_nIdObj);

	for(long nInnerFieldNr = 0; nInnerFieldNr <= m_oFields.GetUpperBound(); nInnerFieldNr++)
	{
		
		if(roStorage.m_oFields[nInnerFieldNr].is_bad_value())
		{
			m_oFields[ nInnerFieldNr ].set_bad_value();
		}
		else
		{
			m_oFields[ nInnerFieldNr ].clear_bad_value();
		}
	}
}

bool CNEO_storage::full_is_usermodified(const CNEO_storage & roStorage)
{
	ASSERT(m_eUserModif == um_unknown || m_eNeedSave == ns_unknown);
	if(full_is_needsave(roStorage))
	{
		m_eUserModif = um_yes;
#ifdef _DEBUG
		check_modif_flags();
#endif
		return true;
	}
	else
	{
		m_eUserModif = um_no;
#ifdef _DEBUG
		check_modif_flags();
#endif
		return false;
	}
}

bool CNEO_storage::full_is_needsave(const CNEO_storage & roStorage)
{
	ASSERT(m_nTypeId == roStorage.m_nTypeId);
	ASSERT(m_nIdObj == roStorage.m_nIdObj);

	ASSERT(m_eNeedSave == ns_unknown);
	if(m_bMarkDel)
	{
		if(m_eState == old_data)
		{
			m_eNeedSave = ns_yes;
			return true;
		}
		else
		{
			ASSERT(m_eState == new_data);
			m_eNeedSave = ns_no;
			return false;
		}
	}
	for(long iter = 0; iter <= m_oFields.GetUpperBound(); iter++)
	{
		SCP<CStdObjFieldDef> & rpoFieldDefSP = GetDefinition()->GetField(iter + 1);
		if(!rpoFieldDefSP->IsVirtual())
		{
			if(m_oFields[iter].is_modified(roStorage.m_oFields[iter]))
			{
				m_eNeedSave = ns_yes;
				return true;
			}
		}
	}
	if(m_eState == new_data)
	{
		m_eNeedSave = ns_yes;
		/*
			zaznaczamy ¿e trzeba zapisywaæ (ns_yes), ale zwracamy 'false'
			do full_is_usermodified jeœli jedynym powodem widzenia zmian z poziomu u¿ytkownika
			mia³oby byæ samo stworzenie nowego obiektu
		*/
		return false;	
	}
	m_eNeedSave = ns_no;
	return false;
}

void CNEO_storage::_set_mark_del(bool bMarkDel)
{
	m_bMarkDel = bMarkDel;
	if(!bMarkDel)
	{
		m_eNeedSave = ns_unknown;
		m_eUserModif = um_unknown;
	}
	else
	{
		if(bMarkDel)
		{
			if(m_eState == old_data)
			{
				m_eNeedSave = ns_yes;
				m_eUserModif = um_yes;
			}
			else
			{
				ASSERT(m_eState == new_data);
				m_eNeedSave = ns_no;
				m_eUserModif = um_no;
			}
		}
	}
#ifdef _DEBUG
	check_modif_flags();
#endif
}

//----------------------------------------------------------- 
//------------ proxy udostêpniane na zewn¹trz ---------------
//----------------------------------------------------------- 

CNEO_user::CNEO_user(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_storage> & rpoStorageSP,bool bReadOnly) :
	m_poTransSP(rpoTransSP),
	m_poStorageSP(rpoStorageSP),
	m_bReadOnlyStorage(bReadOnly)
{
	EnableAutomation();

	ASSERT(rpoTransSP.PointsObject());
	ASSERT(rpoStorageSP.PointsObject());
	m_poStorageSP->AddRef_User();
	m_poStorageSP->GetDefinition()->SetTransaction_DDR(m_poTransSP->GetTransaction_DDR());

//	TRACE("USER ctor %s[%d]\n",m_poStorageSP->GetDefinition()->GetTableName(),m_poStorageSP->GetThis());
}

CNEO_user::~CNEO_user()
{
//	TRACE("user DTOR %s[%d]\n",m_poStorageSP->GetDefinition()->GetTableName(),m_poStorageSP->GetThis());
	m_poStorageSP->Release_User();
}

void CNEO_user::OnFinalRelease()
{
	ASSERT(m_poTransSP.PointsObject());
	m_poTransSP->OnNEO_user_FinalRelease(this);		//notify transaction we are disappering
	delete this;
}

SCP<CNEO_user> CNEO_user::FromIDispatch(LPDISPATCH lpDispatch)
{
	if(lpDispatch == NULL)
	{
		return SCP<CNEO_user>();
	}
	else
	{
		CNEO_user::XDynaDispatch oTestDispatch;
		if(*(DWORD*)lpDispatch != *(DWORD*)&oTestDispatch)
		{
			ASSERT(false); //who calls that way ?
			return SCP<CNEO_user>();
		}
		
		CNEO_user * poUserObj = (CNEO_user *)
			((BYTE*)lpDispatch - offsetof(CNEO_user, m_xDynaDispatch));
		ASSERT(poUserObj);
		return NewSCP(poUserObj,true);
	}
}

void CNEO_user::set_user_modified(bool bUserModified)
{
	ASSERT(_get_storage());
	_get_storage()->simple_set_user_modified(bUserModified);
}




