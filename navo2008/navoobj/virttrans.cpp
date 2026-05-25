/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	class:
		CVirtualTransaction

*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\progressgadget.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "resource.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"

#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CNEO_performer
{
public:
	CNEO_performer()
	{
	}

	CString make(SCP<CNEO_trans> poTransSP, bool bWithCommit, LPCTSTR lpExtras);
private:
	//tworzy AutoSub i wype³nia with modified work set
	SCP<CNEO_trans> _prepare_worktrans(SCP<CNEO_trans> & rpoTransSP);

	bool _fire_triggers(SCP<CNEO_trans> & rpoTransSP);
	bool _perform_tests(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoFailedStorageSP);
	void _create_final_list(SCP<CNEO_trans> & rpoWorkTransSP);
	void _writebinary_4_save(CNEO_thread * poThread);
	void _after_save(eTransState eTransState, SCP<CNEO_trans> & rpoTransSP, SCP<CNEO_storage> & rpoFailedStorageSP);

	//----------- trigger helpers ------------------------------------- 
	//analizuje jaki trigger ma byæ odpalony
	long _get_trigger_id(SCP<CNEO_storage> & rpoStorageSP);

	//odpala trigger jeœli jest
	bool _fire_single_trigger(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoStorageSP);

	//sprawdza czy trigger nie by³ odpalony
	eTriggerFiredPhase _was_trigger_fired(SCP<CNEO_trans> & rpoWorkTransSP, long nTypeId, long nIdObj)
	{
		ASSERT(rpoWorkTransSP.PointsObject());
		return rpoWorkTransSP->fwd_was_trigger_fired(nTypeId, nIdObj);
	}
	//zaznacza ¿e trigger jest w³aœnie odpalany
	void _mark_trigger_firingnow(SCP<CNEO_trans> & rpoWorkTransSP, long nTypeId, long nIdObj)
	{
		ASSERT(rpoWorkTransSP.PointsObject());
		rpoWorkTransSP->m_poThreadSP->mark_trigger_firingnow(nTypeId, nIdObj);
	}
	//zaznacza ¿e trigger by³ odpalony i zakoñczy³o siê ju¿ to
	void _mark_trigger_fired(SCP<CNEO_trans> & rpoWorkTransSP, long nTypeId, long nIdObj)
	{
		ASSERT(rpoWorkTransSP.PointsObject());
		rpoWorkTransSP->m_poThreadSP->mark_trigger_fired(nTypeId, nIdObj);
	}
	//---------- final binary storage helpers -------------------------------

	void add_storage_2_final_list(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoStorageSP);

	void _post_process();	//aktualizuje wewnêtrzny stan obiektów (ale nie wartoœci pól)

	//SEPTBUG
	void _update_references(SCP<CNEO_trans> & rpoWorkTransSP);	//aktualizuje wartoœci obiektów 'refrence' (tylko w work transakcji)


	CFastList< SCP<CNEO_storage> >			m_oFinalStorageList;
	CFastList< SCP<CNEO_liststorage> >		m_oFinalListStorageList;
	CFastList< SCP<CNEO_filestorage> >		m_oFinalFileStorageList;

	CEnhancedStack< SCP<CNEO_storage> >		m_oAdd2FinalListStack;
};




CString CNEO_performer::make(SCP<CNEO_trans> poTransSP, bool bWithCommit, LPCTSTR lpExtras)
{
	CString strResult = "-";

	//utwórz AS jeœli nie ma i nie jest to poTransSP
	SCP<CNEO_trans> poWorkTransSP = _prepare_worktrans(poTransSP);
	SCP<CNEO_storage> poTestFailedStorageSP;

	try
	{
		eTransState TransState = trst_uncom_fail;
		if (_fire_triggers(poWorkTransSP))
		{
			if (_perform_tests(poWorkTransSP, poTestFailedStorageSP))
			{
				_create_final_list(poWorkTransSP);
				_writebinary_4_save(poWorkTransSP->m_poThreadSP.Get());

				strResult = poWorkTransSP->m_poThreadSP->write2storage(bWithCommit, lpExtras);
				TransState = bWithCommit ? trst_commited : trst_uncom_ok;
			}
		}
		_after_save(TransState, poWorkTransSP, poTestFailedStorageSP);
		
		return strResult;
	}
	catch (...)
	{
		_after_save(trst_uncom_fail, poWorkTransSP, poTestFailedStorageSP);
		throw;
	}
}

class CNEO_trans_begend_holder
{
public:
	CNEO_trans_begend_holder(CNEO_trans & roTrans) :
		m_roTrans(roTrans)
	{
		roTrans.m_poThreadSP->begin_transaction();
	}
	~CNEO_trans_begend_holder()
	{
		m_roTrans.m_poThreadSP->end_transaction();
	}
private:
	CNEO_trans & m_roTrans;
};

CString CNEO_trans::_save_changes(bool bWithCommit, LPCTSTR lpExtras)
{
	CNEO_trans_begend_holder oTBEHolder(*this);

#ifdef _DEBUG
	CDebugTimeMeter oDTM("CNEO_trans::_save_changes");

#ifdef _DEVELOPER_EDITION_
	CDebuggerCallHolder oDCH;
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		oDCH++.StoreMsg(bWithCommit ?
			"SAVEOBJECTS # %d started (level=%d)\n" : "SAVE # %d started (level=%d)\n",
			_debug_trans_nr,
			m_poThreadSP->get_transaction_level());
	}
#endif

#endif

	CNEO_performer oPerformer;
	CString strResult = oPerformer.make(NewSCP(this, true), bWithCommit, lpExtras);

#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("TRANSACTION # %d finished (level=%d), with %s\n",
			_debug_trans_nr,
			m_poThreadSP->get_transaction_level(),
			(strResult != "-") ? "SUCCESS" : "FAILURE");
	}
#endif

	if (bWithCommit || (strResult[0] != '+'))
	{
		get_thread()->set_auto_rollback(true);
	}

	return strResult;
}

void CNEO_trans::_rollback()
{
#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("ROLLBACK\n");
	}
#endif
	m_poCoordinator->GetDBAccess()->FinishTransaction(false);
	_propagate_commited(trst_commited);
}

bool CNEO_trans::_commit()
{
#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("standalone COMMIT\n");
	}
#endif
	m_poCoordinator->GetDBAccess()->FinishTransaction(true);
	_propagate_commited(trst_commited);
	return true;
}

//-------------------------------------------------------------------------------------------------
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
//
//
//
//
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
//-------------------------------------------------------------------------------------------------

SCP<CNEO_trans> CNEO_performer::_prepare_worktrans(SCP<CNEO_trans> & rpoTransSP)
{
	SCP<CNEO_trans> poWorkTransSP;

	ASSERT(rpoTransSP.PointsObject());
	if (rpoTransSP->m_bStandardMode)
	{
		if (rpoTransSP->m_poAutoSubTransSP.PointsNull())
		{
			rpoTransSP->m_poAutoSubTransSP = rpoTransSP->CreateSubTransaction(false);
			//w³aœnie za³o¿yliœmy AutoSub
			//skopiuj workset z transakcji g³ównej
			rpoTransSP->evaluate_and_purge_not_needsave_maps(true);
			rpoTransSP->_copy_workset(rpoTransSP->m_poAutoSubTransSP, true);
		}
		else
		{
			ASSERT(false);		//ktoœ nas nieprawid³owo wywo³a³ z g³ównej transakcji mimo ¿e by³a sub.
		}
		ASSERT(rpoTransSP->m_poAutoSubTransSP.PointsObject());
		poWorkTransSP = rpoTransSP->m_poAutoSubTransSP;
	}
	else
	{
		poWorkTransSP = rpoTransSP;
	}

	ASSERT(poWorkTransSP.PointsObject());
	ASSERT(!poWorkTransSP->m_bStandardMode);
	return poWorkTransSP;
}

long CNEO_performer::_get_trigger_id(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	//wyznacz jaki trigger ma byæ wo³any
	long nTriggerId = CLASS_INVALID_FUNCTION;
	if (rpoStorageSP->_is_mark_del())
	{
		if (rpoStorageSP->GetDefinition()->IsFunctionDefined(CLASS_BDTRIG))
		{
			nTriggerId = CLASS_BDTRIG;
		}
	}
	else
	{
		if (rpoStorageSP->IsNew())
		{
			if (rpoStorageSP->GetDefinition()->IsFunctionDefined(CLASS_BITRIG))
			{
				nTriggerId = CLASS_BITRIG;
			}
		}
		else
		{
			if (rpoStorageSP->GetDefinition()->IsFunctionDefined(CLASS_BUTRIG))
			{
				nTriggerId = CLASS_BUTRIG;
			}
		}
	}

	//jeœli ¿aden to OK
	return nTriggerId;
}

bool CNEO_performer::_fire_single_trigger(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	ASSERT(rpoWorkTransSP.PointsObject());
	ASSERT(!rpoWorkTransSP->m_bStandardMode);
	ASSERT(_was_trigger_fired(rpoWorkTransSP, rpoStorageSP->GetType(), rpoStorageSP->GetThis()) == tfp_notfired);

	long nTriggerId = _get_trigger_id(rpoStorageSP);
	if (CLASS_INVALID_FUNCTION == nTriggerId)
	{
		return true;		//brak triggera - done
	}

	//fully qualify object
	long nTypeId = rpoStorageSP->GetType();
	long nIdObj = rpoStorageSP->GetThis();
	long nParentTypeId = 0;
	long nParentId = 0;
	if (rpoStorageSP->GetDefinition()->IsChild())
	{
		rpoStorageSP->_get_parent(nParentTypeId, nParentId);
	}

	//create user
	SCP<CNEO_user> poUserSP = rpoWorkTransSP->_get_object(nTypeId, nIdObj, nParentTypeId, nParentId);
	ASSERT(poUserSP.PointsObject());
	ASSERT(poUserSP->_get_storage());

	_mark_trigger_firingnow(rpoWorkTransSP, nTypeId, nIdObj);
	bool bResult = poUserSP->_call_trigger(nTriggerId);
	_mark_trigger_fired(rpoWorkTransSP, nTypeId, nIdObj);
	return bResult;
}

bool CNEO_performer::_fire_triggers(SCP<CNEO_trans> & rpoTransSP)
{
	ASSERT(rpoTransSP.PointsObject());
	ASSERT(!rpoTransSP->m_bStandardMode);

	long nInitialCount = rpoTransSP->m_oLocalStorageMap.GetCount();
again:
	POSITION pos = rpoTransSP->m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = rpoTransSP->m_oLocalStorageMap.GetNext(pos, hyperId);

		rpoTransSP->evaluate_storage(poStorageSP);
		ASSERT(poStorageSP->_get_needsave() != ns_unknown);

		if (poStorageSP->_get_needsave() == ns_yes)
		{
			ASSERT(hihyper(hyperId) == poStorageSP->GetType());
			ASSERT(lohyper(hyperId) == poStorageSP->GetThis());

			if (_was_trigger_fired(rpoTransSP, hihyper(hyperId), lohyper(hyperId)) == tfp_notfired)
			{
				//jeœli jest zmienione dziecko, to ono powoduje wywo³anie triggera ojca
				if (poStorageSP->GetDefinition()->IsChild())
				{
					long nParentTypeId = 0;
					long nParentId = 0;
					poStorageSP->_get_parent(nParentTypeId, nParentId);

					//neo_todo: byæ mo¿e trigger powinien byæ wo³any na koñcu, po wszystkich dzieciach...
					//kolejnoœæ triggerów to problem...
					if (_was_trigger_fired(rpoTransSP, nParentTypeId, nParentId) == tfp_notfired)
					{
						//assume no grand children
						SCP<CNEO_user> poParentUserSP = rpoTransSP->_get_object(nParentTypeId, nParentId, 0, 0);
						if (!_fire_single_trigger(rpoTransSP, poParentUserSP->_get_storage()))
						{
							return false;
						}
					}
				}
				if (!_fire_single_trigger(rpoTransSP, poStorageSP))
				{
					return false;
				}
			}
			else
			{
				TRACE("SKIPPED already fired/firing trigger for %s[%d]\n",
					poStorageSP->GetDefinition()->GetTableName(), poStorageSP->GetThis());
			}
		}
	}
	if (rpoTransSP->m_oLocalStorageMap.GetCount() != nInitialCount)
	{
		ASSERT(rpoTransSP->m_oLocalStorageMap.GetCount() > nInitialCount);
		nInitialCount = rpoTransSP->m_oLocalStorageMap.GetCount();
		goto again;
	}

	TRACE("---------- end object triggers --------------------\n");

	TRACE("---------- list escalated triggers --------------------\n");
	pos = rpoTransSP->m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = rpoTransSP->m_oLocalListStorageMap.GetNext(pos, hyperId);
		rpoTransSP->evaluate_list_storage(poListStorageSP);
		ASSERT(poListStorageSP->_get_needsave() != ns_unknown);
		if (poListStorageSP->_get_needsave() == ns_yes)
		{
			long nParentTypeId = poListStorageSP->GetParentTypeid();
			long nParentId = poListStorageSP->GetParentId();
			if (_was_trigger_fired(rpoTransSP, nParentTypeId, nParentId) == tfp_notfired)
			{
				//assume no grand children
				SCP<CNEO_user> poParentUserSP = rpoTransSP->_get_object(nParentTypeId, nParentId, 0, 0);
				if (!_fire_single_trigger(rpoTransSP, poParentUserSP->_get_storage()))
				{
					return false;
				}
			}
		}
	}
	TRACE("---------- end list escalated triggers --------------------\n");

	return true;
}


bool CNEO_performer::_perform_tests(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoFailedStorageSP)
{
	ASSERT(rpoWorkTransSP.PointsObject());
	ASSERT(!rpoWorkTransSP->m_bStandardMode);

	POSITION pos = rpoWorkTransSP->m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = rpoWorkTransSP->m_oLocalStorageMap.GetNext(pos, hyperId);
		rpoWorkTransSP->evaluate_storage(poStorageSP);

		ASSERT(poStorageSP->_get_needsave() != ns_unknown);

		if (poStorageSP->_get_needsave() == ns_yes)
		{
			if (poStorageSP->_is_mark_del())
			{
				if (!poStorageSP->_test_can_delete(false, rpoWorkTransSP))
				{
					TRACE("test/candel failed %s[%d]\n",
						poStorageSP->GetDefinition()->GetTableName(), poStorageSP->GetThis());
					return false;
				}
			}
			else
			{
				if (!poStorageSP->_test_can_save(false, rpoWorkTransSP))
				{
					TRACE("test/cansave failed %s[%d]\n",
						poStorageSP->GetDefinition()->GetTableName(), poStorageSP->GetThis());
					rpoFailedStorageSP = poStorageSP;
					return false;
				}
			}
		}
	}

	TRACE("---------- end of build in tests --------------------\n");
	return true;
}


void CNEO_performer::add_storage_2_final_list(SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoWorkTransSP.PointsObject());
	ASSERT(!rpoWorkTransSP->m_bStandardMode);

	if (rpoStorageSP->_get_needsave() != ns_yes)
	{
		ASSERT(rpoStorageSP->_get_needsave() == ns_no);	//must be evaluated
		return;
	}
	if (m_oFinalStorageList.Exists(rpoStorageSP))
	{
		return;
	}

	//now analyzed stack
	POSITION pos = m_oAdd2FinalListStack.GetTopPosition();
	while (pos)
	{
		if (m_oAdd2FinalListStack.MoveDown(pos).Get() == rpoStorageSP.Get())
		{
			return;
		}
	}

	CPushStackHolder< SCP<CNEO_storage> > oNowAnalyzedHolder(m_oAdd2FinalListStack, rpoStorageSP);

	//analyze references
	for (long nField = 1; nField <= rpoStorageSP->m_oFields.GetSize(); nField++)
	{
		long nRelationType = rpoStorageSP->GetDefinition()->GetField(nField)->GetRelationType();
		if (nRelationType == RELT_WILDREF || nRelationType == RELT_REF)
		{
			ASSERT(rpoStorageSP->m_oFields[nField - 1]._get_value().Type() == VT_CY);
			CY cyTypeIdObj = rpoStorageSP->m_oFields[nField - 1]._get_value().GetCurrency();
			if (cyTypeIdObj.Lo != 0)		//referencja jest niepusta
			{
				CNEO_storage * poStorage = rpoWorkTransSP->_search_local_storage_map(cyTypeIdObj.Hi, cyTypeIdObj.Lo);
				if (poStorage != NULL)
				{
					add_storage_2_final_list(rpoWorkTransSP, NewSCP(poStorage, true));
				}
			}
		}
	}
	//add
	m_oFinalStorageList.Add(rpoStorageSP);
	TRACE("FINAL:added %s[%d]\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
}

void CNEO_performer::_create_final_list(SCP<CNEO_trans> & rpoWorkTransSP)
{
	ASSERT(rpoWorkTransSP.PointsObject());
	ASSERT(!rpoWorkTransSP->m_bStandardMode);

	TRACE("---------- creating final list --------------------\n");

	POSITION pos = rpoWorkTransSP->m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		add_storage_2_final_list(rpoWorkTransSP, rpoWorkTransSP->m_oLocalStorageMap.GetNext(pos, hyperId));
	}
	pos = rpoWorkTransSP->m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperListId;
		SCP<CNEO_liststorage> poListStorageSP = rpoWorkTransSP->m_oLocalListStorageMap.GetNext(pos, hyperListId);
		if (poListStorageSP->_get_needsave() == ns_yes)
		{
			m_oFinalListStorageList.Add(poListStorageSP);
			TRACE("tr:final:list added [%d:%d]=%d,cnt=%d\n",
				poListStorageSP->GetParentTypeid(),
				poListStorageSP->GetParentId(),
				poListStorageSP->GetCollectionId(),
				poListStorageSP->GetSize());
		}
		else
		{
			ASSERT(poListStorageSP->_get_needsave() == ns_no);	//must be fully evaluated
		}
	}
	pos = rpoWorkTransSP->m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperFileID;
		SCP<CNEO_filestorage> poFileStorageSP = rpoWorkTransSP->m_oLocalFileStorageMap.GetNext(pos, hyperFileID);
		if (poFileStorageSP->_get_needsave() == ns_yes)
		{
			m_oFinalFileStorageList.Add(poFileStorageSP);
			TRACE("tr:final:file added [%d:%d:%d]\n",
				poFileStorageSP->GetParentTypeid(),
				poFileStorageSP->GetParentId(),
				poFileStorageSP->GetOuterFieldNr());
		}
	}
	TRACE("---------- created final list --------------------\n");
}

void CNEO_performer::_writebinary_4_save(CNEO_thread * poThread)
{
	ASSERT(poThread != NULL);

	POSITION pos = m_oFinalStorageList.GetFirstPosition();

	while (pos)
	{
		SCP<CNEO_storage> poStorageSP = m_oFinalStorageList.GetNext(pos);

		ASSERT(poStorageSP.PointsObject());
		ASSERT(poStorageSP->_get_needsave() == ns_yes);

		if (!poStorageSP->GetDefinition()->IsVolatile())
		{
			if (poStorageSP->_is_mark_del())
			{
				poStorageSP->_writebinary4del(poThread->flatdata());
			}
			else
			{
				poStorageSP->_writebinary4save(poThread->flatdata());
			}
		}
	}

	pos = m_oFinalListStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_liststorage> poListStorageSP = m_oFinalListStorageList.GetNext(pos);

		ASSERT(poListStorageSP.PointsObject());
		ASSERT(poListStorageSP->_get_needsave() == ns_yes);

		if (!poListStorageSP->get_parent_definition()->IsVolatile())
		{
			if (poListStorageSP->_is_parent_mark_del())
			{
				poListStorageSP->_writebinary4del(poThread->flatdata());
			}
			else
			{
				poListStorageSP->_writebinary4save(poThread->flatdata());
			}
		}
	}
	pos = m_oFinalFileStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_filestorage> poFileStorageSP = m_oFinalFileStorageList.GetNext(pos);

		ASSERT(poFileStorageSP.PointsObject());
		ASSERT(poFileStorageSP->_get_needsave() == ns_yes);

		poFileStorageSP->_writebinary(poThread->blobdata());
	}
}

void CNEO_performer::_post_process()
{
	POSITION pos = m_oFinalStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_storage> poStorageSP = m_oFinalStorageList.GetNext(pos);
		ASSERT(poStorageSP.PointsObject());
		ASSERT(poStorageSP->_get_needsave() == ns_yes);
		poStorageSP->_postprocess();
	}

	pos = m_oFinalListStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_liststorage> poListStorageSP = m_oFinalListStorageList.GetNext(pos);
		ASSERT(poListStorageSP.PointsObject());
		ASSERT(poListStorageSP->_get_needsave() == ns_yes);
		poListStorageSP->_postprocess();
	}

	pos = m_oFinalFileStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_filestorage> poFileStorageSP = m_oFinalFileStorageList.GetNext(pos);
		ASSERT(poFileStorageSP.PointsObject());
		ASSERT(poFileStorageSP->_get_needsave() == ns_yes);
		poFileStorageSP->_postprocess();
	}
}

//SEPTBUG
//aktualizuje wartoœci obiektów 'refrence' (tylko w work transakcji)
void CNEO_performer::_update_references(SCP<CNEO_trans> & rpoWorkTransSP)
{
	POSITION pos = m_oFinalStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_storage> poStorageSP = m_oFinalStorageList.GetNext(pos);
		ASSERT(poStorageSP.PointsObject());
		ASSERT(poStorageSP->_get_needsave() == ns_no);

		SCP<CNEO_storage> poPrevRefStorageSP = rpoWorkTransSP->_search_reference_storage_map(poStorageSP->GetType(), poStorageSP->GetThis());
		ASSERT(poPrevRefStorageSP.PointsObject());
		poPrevRefStorageSP->_copy_from(*poStorageSP);
	}

	pos = m_oFinalListStorageList.GetFirstPosition();
	while (pos)
	{
		SCP<CNEO_liststorage> poListStorageSP = m_oFinalListStorageList.GetNext(pos);
		ASSERT(poListStorageSP.PointsObject());
		ASSERT(poListStorageSP->_get_needsave() == ns_no);

		SCP<CNEO_liststorage> poPrevRefListStorageSP = rpoWorkTransSP->_search_reference_liststorage_map(poListStorageSP->GetCollectionId(), poListStorageSP->GetParentId());
		ASSERT(poPrevRefListStorageSP.PointsObject());
		poPrevRefListStorageSP->_copy_from(*poListStorageSP);
	}

	//nie ma file reference..
}

void CNEO_performer::_after_save(eTransState TransState, SCP<CNEO_trans> & rpoWorkTransSP, SCP<CNEO_storage> & rpoFailedStorageSP)
{
	ASSERT(rpoWorkTransSP.PointsObject());
	ASSERT(!rpoWorkTransSP->m_bStandardMode);

	//jeœli siê uda³o to wykonaj post_process
	if (TransState == trst_commited || TransState == trst_uncom_ok)
	{
		_post_process();
		//teraz bedziemy przerzucaæ
		if (TransState == trst_commited)
		{
			ASSERT(rpoWorkTransSP->m_poPrevTransaction);
			ASSERT(rpoWorkTransSP->m_poPrevTransaction->m_bStandardMode);
			ASSERT(rpoWorkTransSP->m_poThreadSP->get_transaction_level() == 1);

			//skopiuj wszystkie jakie mamy (zebraliœmy), a¿ do cache'a
			rpoWorkTransSP->_propagate_workset();
		}
		else
		{
			if (rpoWorkTransSP->m_poThreadSP->get_transaction_level() > 1)
			{
				CNEO_trans * poMainTrans = rpoWorkTransSP->m_poPrevTransaction;
				ASSERT(poMainTrans);
				ASSERT(poMainTrans->m_bStandardMode);
				while (true)
				{
					if (poMainTrans->m_poPrevTransaction == NULL)
					{
						break;
					}
					if (poMainTrans->m_poPrevTransaction->m_bStandardMode)
					{
						break;
					}
					rpoWorkTransSP->_copy_workset(poMainTrans->m_poPrevTransaction, false);
					poMainTrans = poMainTrans->m_poPrevTransaction->m_poPrevTransaction;
					if (poMainTrans == NULL)
					{
						break;
					}
					ASSERT(poMainTrans->m_bStandardMode);
				}
			}

			//SEPTBUG : else
			{
				//SEPTBUG : zaktualizuj reference na podstawie zmienionych
				_update_references(rpoWorkTransSP);
			}
		}
	}

	if (TransState == trst_commited || TransState == trst_uncom_fail)
	{
		ASSERT(rpoWorkTransSP->m_poPrevTransaction);
		ASSERT(rpoWorkTransSP->m_poPrevTransaction->m_bStandardMode);
		ASSERT(rpoWorkTransSP->m_poPrevTransaction->m_poAutoSubTransSP.Get() == rpoWorkTransSP.Get());
		if (TransState == trst_uncom_fail)
		{
			rpoWorkTransSP->_rollback();
			if (rpoFailedStorageSP.PointsObject())
			{
				/* kopiowanie z³ego statusu */
				CNEO_storage * poOrigFailedStorage =
					rpoWorkTransSP->m_poPrevTransaction->_search_local_storage_map(
						rpoFailedStorageSP->GetType(), rpoFailedStorageSP->GetThis());
				if (poOrigFailedStorage != NULL)
				{
					poOrigFailedStorage->_copy_bad_status(*rpoFailedStorageSP);
				}
			}
			//wyczyœæ autosub (czyli nas) jeœli error
			rpoWorkTransSP->m_poPrevTransaction->m_poAutoSubTransSP = 0;
		}
		else
		{
			//jeœli commited clean
			rpoWorkTransSP->m_poPrevTransaction->_clean();
		}
	}
	rpoWorkTransSP->_propagate_commited(TransState);
}

