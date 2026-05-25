/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectList
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
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



CNEO_liststorage::CNEO_liststorage(CNEO_global_cache * poGlobalCache,
		long nCollectionId,long IdParent,long ChildTypeId,bool bParentIsNew,
		CStdObjDef * poParentDefinition) :
	m_CollectionId(nCollectionId),
	m_IdParent(IdParent),
	m_ChildTypeId(ChildTypeId),
	m_poGlobalCache(poGlobalCache),
	m_dwUserRef(0),
	m_eNeedSave(ns_no),
	m_eUserModif(um_no),
	m_bParentMarkDel(false),
	m_bParentIsNew(bParentIsNew),
	m_poParentDefinition(poParentDefinition)
{
	ASSERT(m_IdParent > 0);
	ASSERT(m_CollectionId > 0);
	ASSERT(m_ChildTypeId > 0);
}


CNEO_liststorage::~CNEO_liststorage()
{
}

void CNEO_liststorage::OnFinalRelease()
{
	if(m_poGlobalCache)
	{
		m_poGlobalCache->OnNEO_liststorage_FinalRelease(this);
	}
	else
	{
		delete this;
	}
}

bool CNEO_liststorage::is_element_at(long nInternalIndex)
{
	return (nInternalIndex >= 0) && (nInternalIndex <= m_oItemArray.GetUpperBound());
}

long CNEO_liststorage::get_element_at(long nInternalIndex)
{
	ASSERT(is_element_at(nInternalIndex));
	return m_oItemArray[nInternalIndex].m_IdObj;
}

void CNEO_liststorage::insert_new_element(long nInternalIndex,long nNewIdObj)
{
	m_oItemArray.InsertAt(nInternalIndex,CNEO_listitem(nNewIdObj));

	m_eNeedSave = ns_unknown;
	m_eUserModif = um_unknown;
}

void CNEO_liststorage::delete_element(long nInternalIndex)
{
	m_oItemArray.RemoveAt(nInternalIndex);

	m_eNeedSave = ns_unknown;
	m_eUserModif = um_unknown;
}

void CNEO_liststorage::delete_all_elements()
{
	m_oItemArray.RemoveAll();
	
	m_eNeedSave = ns_unknown;
	m_eUserModif = um_unknown;
}

long CNEO_liststorage::findonid(long nChildIdObj)
{
	for(long iter = 0; iter <= m_oItemArray.GetUpperBound(); iter++)
	{
		if(m_oItemArray[iter].m_IdObj == nChildIdObj)
		{
			return iter;
		}
	}
	return -1;
}

long CNEO_liststorage::find(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	ASSERT(rpoStorageSP->GetType() == GetChildTypeid());

	return findonid(rpoStorageSP->GetThis());
}

void CNEO_liststorage::move_element(long nInternalFrom,long nInternalTo)
{
	ASSERT(nInternalTo != nInternalFrom);	//wywo³anie bez sensu

	long nIdObj = get_element_at(nInternalFrom);
	delete_element(nInternalFrom);
	insert_new_element(nInternalTo,nIdObj);

	m_eNeedSave = ns_unknown;
	m_eUserModif = um_unknown;
}

void CNEO_liststorage::undo_operation(long nOuterIndex,long nChildIdObj)
{
	ASSERT(nOuterIndex != 0);

	if(nOuterIndex > 0)	//undoing insert
	{
		m_oItemArray.RemoveAt(nOuterIndex - 1);
	}
	else	//undoing delete
	{
		ASSERT(-(nOuterIndex-1) >= 0);
		m_oItemArray.InsertAt(-(nOuterIndex-1),CNEO_listitem(nChildIdObj));
	}
}














CNEO_listuser::CNEO_listuser(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_liststorage> & rpoListStorageSP,
							 bool bReadOnlyStorage) :
	m_poTransSP(rpoTransSP),
	m_poListStorageSP(rpoListStorageSP),
	m_bReadOnlyStorage(bReadOnlyStorage)
{
	m_poListStorageSP->AddRef_User();
	EnableAutomation();
}

CNEO_listuser::~CNEO_listuser()
{
	m_poListStorageSP->Release_User();
}

void CNEO_listuser::OnFinalRelease()
{
	ASSERT(m_poTransSP.PointsObject());
	m_poTransSP->OnNEO_listuser_FinalRelease(this);
	delete this;
}

SCP<CNEO_listuser> CNEO_listuser::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetStdObjList = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetStdObjList);
	CNEO_listuser * poStdObjList = dynamic_cast<CNEO_listuser*>(poCmdTargetStdObjList);
	ASSERT(poStdObjList);
	return NewSCP(poStdObjList,true);
}


bool CNEO_listuser::IsElementAt(long nInternalIndex)
{
	ASSERT(_get_storage().PointsObject());
	return _get_storage()->is_element_at(nInternalIndex);
}

SCP<CNEO_user> CNEO_listuser::GetElementAt(long nInternalIndex)
{
	ASSERT(_get_storage().PointsObject());
	ASSERT(_get_trans().PointsObject());
	long nElementIdObj = _get_storage()->get_element_at(nInternalIndex);
	ASSERT(nElementIdObj > 0);
	long nParentTypeId = _get_storage()->GetParentTypeid();
	long nParentIdObj = _get_storage()->GetParentId();

	SCP<CNEO_user> poUserSP = _get_trans()->_get_object(
		_get_storage()->GetChildTypeid(),nElementIdObj,nParentTypeId,nParentIdObj);
	ASSERT(poUserSP.PointsObject());	//musi istnieæ i byæ dostêpny
	ASSERT(poUserSP->_get_storage().PointsObject());
	
	//musi byæ zdefiniowany jako <child>
	ASSERT(poUserSP->_get_storage()->GetDefinition()->IsChild());
	return poUserSP;
}

void CNEO_listuser::_enable_changes()
{
	if(m_bReadOnlyStorage)
	{
		SCP<CNEO_liststorage> poROListStorageSP = m_poListStorageSP;
		m_poListStorageSP = m_poTransSP->_copy_on_write_liststorage(m_poListStorageSP);
		if(poROListStorageSP != m_poListStorageSP)
		{
			m_poListStorageSP->AddRef_User();
			poROListStorageSP->Release_User();
		}
		m_bReadOnlyStorage = false;
		ASSERT(_get_storage());
	}
}

SCP<CNEO_user> CNEO_listuser::add_new_element()
{
	ASSERT(_get_storage());
	return insert_new_element(1+_get_storage()->GetSize());
}

SCP<CNEO_user> CNEO_listuser::insert_new_element(long nOuterIndex)
{
	ASSERT(nOuterIndex > 0);

	_enable_changes();
	ASSERT(_get_storage());
	ASSERT(_get_trans());
	if(_get_storage()->_is_parent_mark_del())
	{
		//to_do: error: nie mo¿na dodawaæ do obiektu zaznaczonego do skasowania
		CString oString = "nie mo¿na dodawaæ do obiektu zaznaczonego do skasowania";
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}

	long nChildTypeId = _get_storage()->GetChildTypeid();
	long nParentTypeId = _get_storage()->GetParentTypeid();
	long nParentIdObj = _get_storage()->GetParentId();
	long nCollectionId = _get_storage()->GetCollectionId();

	CNEO_rollbackholder oRollbackHolder(_get_trans());
		
		//create new child object
		SCP<CNEO_user> poNewUserSP = _get_trans()->_new_object(nChildTypeId,nParentTypeId,nParentIdObj);
		if(poNewUserSP.PointsNull())
		{
			return SCP<CNEO_user>();
		}

		if(!poNewUserSP->_call_before_list_operation(nOuterIndex))
		{
			return SCP<CNEO_user>();
		}
		long nChildIdObj = poNewUserSP->_get_storage()->GetThis();
		//add to storage
		_get_storage()->insert_new_element(nOuterIndex-1,nChildIdObj);
		oRollbackHolder._registerundo_listinsupddel(nCollectionId,nParentIdObj,nOuterIndex,nChildIdObj);

	oRollbackHolder.Success();
	return poNewUserSP;
}

bool CNEO_listuser::delete_element(long nOuterIndex)
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());

	long nChildTypeId = _get_storage()->GetChildTypeid();
	long nChildIdObj = _get_storage()->get_element_at(nOuterIndex-1);
	long nCollectionId = _get_storage()->GetCollectionId();
	long nParentTypeId = _get_storage()->GetParentTypeid();
	long nParentIdObj = _get_storage()->GetParentId();

	ASSERT(nChildIdObj > 0);
	
	SCP<CNEO_user> poUserToBeDelSP = _get_trans()->_get_object(nChildTypeId,nChildIdObj,
		nParentTypeId,nParentIdObj);
	ASSERT(poUserToBeDelSP.PointsObject());	//musi istnieæ i byæ dostêpny

	if(!poUserToBeDelSP->_call_before_list_operation(-nOuterIndex))
	{
		return false;
	}

	_enable_changes();

	CNEO_rollbackholder oRollbackHolder(_get_trans());
		poUserToBeDelSP->set_markdel(true);
		_get_storage()->delete_element(nOuterIndex-1);
		oRollbackHolder._registerundo_listinsupddel(nCollectionId,nParentIdObj,-nOuterIndex,nChildIdObj);

	oRollbackHolder.Success();
	return true;
}

void CNEO_listuser::delete_all_elements()
{
	ASSERT(_get_storage());
	ASSERT(_get_trans());
	_enable_changes();

	CNEO_rollbackholder oRollbackHolder(_get_trans());
	while(IsElementAt(0 /*internal index*/))
	{
		if(!delete_element(1/*outer index */))
		{
			return;
		}
	}
	oRollbackHolder.Success();
}

void CNEO_listuser::set_user_modified(bool bUserModified)
{
	ASSERT(_get_storage());
	_get_storage()->simple_set_user_modified(bUserModified);
}

void CNEO_listuser::_raw_set_markdel(bool bMarkDel)
{
	ASSERT(_get_storage());
	_enable_changes();
	_get_storage()->set_parent_mark_del(bMarkDel);
	for(long iter = 0;IsElementAt(iter);iter++)
	{
		GetElementAt(iter)->set_markdel(bMarkDel);
	}
}

