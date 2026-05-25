/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	CDataObjectModificationSet
		- zbiór u¿ywanych CDataObjectów

	CTransaction

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
#include "cursorcollection.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"
#include "lockmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
extern long debug_counter;
#endif

CNEO_trans::CNEO_trans(CNavoObjectCoordinator * poCoordinator, CNavoException & roErrorStorage,
	bool bStandardMode, CNEO_trans * poPreviousTrans, SCP<CNEO_thread> & rpoThreadSP, SCP<CHyperLinkInfo> & rpoInitialEnvHLISP,
	SCP<IDispatch> poMessageSinkDispatchSP) :
	m_poCoordinator(poCoordinator),
	m_roErrorStorage(roErrorStorage),
	m_poThreadSP(rpoThreadSP),
	m_poEnvironmentHLISP(NewSCP(new CHyperLinkInfo())),
	m_poPrevTransaction(poPreviousTrans),
	m_poLocalLockMap(new CNEO_lockmap()),
	m_dwVLockRefs(0),
	m_eTransState(trst_commited),
	m_bStandardMode(bStandardMode),
	m_poMessageSinkDispatchSP(poMessageSinkDispatchSP)
#ifdef _DEVELOPER_EDITION_
	, _debug_trans_nr(++poCoordinator->m_debug_trans_nr_gener)
#endif
{
	if (m_bStandardMode && m_poPrevTransaction)		//reczne referencje
	{
		m_poPrevTransaction->AddRef();
	}

	EnableAutomation();
	(*m_poEnvironmentHLISP) = (*rpoInitialEnvHLISP);


	//create rollback log
	m_poRollbackLogSP = NewSCP(new CNEO_rollbacklog(*this));
	m_poThreadSP->SetCurrentTransaction(this);

#ifdef _DEVELOPER_EDITION_
	if (!m_bStandardMode)
	{
		if (GetDebugOptions().IsTraceAutoCalls())
		{
			GetDebugger().StoreMsg("AUTOTRANS # %d started\n", _debug_trans_nr);
		}
	}
	else
	{
		if (GetDebugOptions().IsTraceAutoCalls())
		{
			GetDebugger().StoreMsg("TRANSACTION # %d started\n", _debug_trans_nr);
		}
	}
#endif

	m_oNEO_userMap.InitHashTable(2111);
	m_oNEO_listuserMap.InitHashTable(211);

	m_oLocalStorageMap._init_hash_table(2111);
	m_oLocalListStorageMap._init_hash_table(211);

	m_oReferenceStorageMap.InitHashTable(2111);
	m_oReferenceListStorageMap.InitHashTable(211);

	m_dispid_message_sink = DISPID_NONE;
}


CNEO_trans::~CNEO_trans()
{
	/*
		jeœli jest niezapisana transakcja, a nie jest to
		wewn¹trz aktywnie wykonywanej subtransakcji -
		wtedy wykonaj rollback
	*/
	//neo_todo
	if (m_poPrevTransaction)
	{
		if (m_poPrevTransaction->m_poAutoSubTransSP.Get() == this)
		{
			ASSERT(m_poPrevTransaction->m_poAutoSubTransSP->m_dwRef == 0);
			m_poPrevTransaction->m_poAutoSubTransSP.Detach();
		}
	}

	if ((m_eTransState != trst_commited) && m_poThreadSP->get_transaction_level() == 0)
	{
		if (m_poThreadSP->is_auto_rollback())
		{
			_rollback();
		}
	}

#ifdef _DEBUG
	if (is_user_modified())
	{
		//AfxMessageBox("Destrukcja niezapisanej i niewyczyszczonej transakcji!");
	}
#endif
	_clean();
	m_poRollbackLogSP = 0;


	delete m_poLocalLockMap;
	m_poThreadSP->SetCurrentTransaction(m_poPrevTransaction);

#ifdef _DEBUG
	if (m_dwVLockRefs != 0)		//nie wszystkie VLocki zosta³y zwolnione
	{
		ASSERT(false);
		ASSERT(false);
		GetDebugger().StoreMsg("Warning! Nie zwolni³eœ jeszcze %d VLocków", m_dwVLockRefs);
	}
	ASSERT(m_oNEO_userMap.IsEmpty());
	ASSERT(m_oNEO_listuserMap.IsEmpty());
	ASSERT(m_oNEO_fileuserMap.IsEmpty());

	ASSERT(m_oReferenceStorageMap.IsEmpty());
	ASSERT(m_oReferenceListStorageMap.IsEmpty());

	ASSERT(m_oVirtLockArray.GetSize() == 0);

	ASSERT(m_oLocalStorageMap.GetCount() == 0);
	ASSERT(m_oLocalListStorageMap.GetCount() == 0);
	ASSERT(m_oLocalFileStorageMap.GetCount() == 0);

#endif

#ifdef _DEVELOPER_EDITION_
	if (!m_bStandardMode)
	{
		if (GetDebugOptions().IsTraceAutoCalls())
		{
			GetDebugger().StoreMsg("AUTOTRANS # %d deleted\n", _debug_trans_nr);
		}
	}
	else
	{
		if (GetDebugOptions().IsTraceAutoCalls())
		{
			GetDebugger().StoreMsg("TRANSACTION # %d deleted\n", _debug_trans_nr);
		}
	}
#endif

	if (m_bStandardMode && m_poPrevTransaction)		//reczne referencje
	{
		m_poPrevTransaction->Release();
	}
}

SCP<CNEO_trans> CNEO_trans::CreateSubTransaction(bool bStandard)
{
	return NewSCP(new CNEO_trans(m_poCoordinator, m_roErrorStorage,
		bStandard, this, m_poThreadSP, m_poEnvironmentHLISP, m_poMessageSinkDispatchSP));
}


CDispatchDynamicResolver * CNEO_trans::GetTransaction_DDR()
{
	return m_poCoordinator->GetTransaction_DDR();
}

void CNEO_trans::ApplyEnvironment(SCP<CHyperLinkInfo> & rpoHLISP)
{
	ASSERT(rpoHLISP.PointsObject());
	const CHyperLinkInfo * poHLI = rpoHLISP.ConstCastObject();
	POSITION pos = poHLI->m_props.m_map.GetStartPosition();
	while (pos)
	{
		long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
		CVariable rVar;
		poHLI->m_props.m_map.GetNextAssoc(pos, lName, rVar);
#else
		const CVariable & rVar = poHLI->m_props.m_map.GetNextAssoc(pos, lName);
#endif
		if (rVar.GetVal().Type() != VT_DISPATCH)
		{
			set_var(lName, rVar.GetVal());
		}
		else
		{
			TRACE1("environment var %d has DISPATCH type and will be not copied\n", lName);
		}
	}
}

void CNEO_trans::_clean()
{
	/*
		ze wzglêdu, ¿e thread::SetCurrentTransaction automatycznie podmienia
		bie¿¹c¹ transakcjê, musimy zrobiæ trick
		- najpierw zerujemy m_poAutoSubTransSP
		- potem robimy rêczny release, jeœli jest na czym
	*/

	CNEO_trans * poAutoSubTrans = m_poAutoSubTransSP.Detach();
	ASSERT(m_poAutoSubTransSP.PointsNull());
	if (poAutoSubTrans != NULL)
	{
		poAutoSubTrans->Release();
	}

	/*koniec tricku */


	purge_maps();
	release_write_locks();
}

//-------- kopiuje z bie¿¹cej transakcji do poDestTrans
//-------- wszystkie zmienione obiekty oraz referencestorage, w takim
//-------- stanie jakim s¹ - w przybli¿eniu kopiuje transakcjê

void CNEO_trans::_copy_workset(CNEO_trans * poDestTrans, bool bChangedOnly)
{
	ASSERT(poDestTrans);

	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);

		ASSERT(poStorageSP->_get_needsave() != ns_unknown);	//caller has to evaluate first !

		if (!bChangedOnly || poStorageSP->_get_needsave() == ns_yes)
		{
			long nTypeId = poStorageSP->GetType();
			long nIdObj = poStorageSP->GetThis();
			CNEO_storage * poDestStorage = poDestTrans->_search_local_storage_map(nTypeId, nIdObj);
			if (poDestStorage != NULL)
			{
				poDestStorage->_copy_from(*poStorageSP);		//replace contents
			}
			else
			{
				poDestTrans->_add_to_local_storage_map(poStorageSP->clone());	//add clone
			}

			SCP<CNEO_storage> poSrcRefStorageSP = _search_reference_storage_map(nTypeId, nIdObj);
			ASSERT(poSrcRefStorageSP.PointsObject());

			SCP<CNEO_storage> poDestRefStorageSP = poDestTrans->_search_reference_storage_map(nTypeId, nIdObj);
			if (poDestRefStorageSP.PointsObject())
			{
				poDestRefStorageSP->_copy_from(*poSrcRefStorageSP);
			}
			else
			{
				poDestTrans->_add_to_reference_storage_map(poSrcRefStorageSP->clone());
			}
		}
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);

		ASSERT(poListStorageSP->_get_needsave() != ns_unknown);

		if (!bChangedOnly || poListStorageSP->_get_needsave() == ns_yes)
		{
			long nCollectionID = poListStorageSP->GetCollectionId();
			long nParentId = poListStorageSP->GetParentId();

			CNEO_liststorage * poDestListStorage = poDestTrans->_search_local_liststorage_map(nCollectionID, nParentId);
			if (poDestListStorage != NULL)
			{
				poDestListStorage->_copy_from(*poListStorageSP);
			}
			else
			{
				poDestTrans->_add_to_local_liststorage_map(poListStorageSP->clone());
			}

			SCP<CNEO_liststorage> poSrcRefListStorageSP = _search_reference_liststorage_map(nCollectionID, nParentId);
			ASSERT(poSrcRefListStorageSP.PointsObject());

			SCP<CNEO_liststorage> poDestRefListStorageSP = poDestTrans->_search_reference_liststorage_map(nCollectionID, nParentId);

			if (poDestRefListStorageSP.PointsObject())
			{
				poDestRefListStorageSP->_copy_from(*poListStorageSP);
			}
			else
			{
				poDestTrans->_add_to_reference_liststorage_map(poSrcRefListStorageSP->clone());
			}
		}
	}

	pos = m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_filestorage> poFileStorageSP = m_oLocalFileStorageMap.GetNext(pos, hyperId);

		ASSERT(poFileStorageSP->_get_needsave() != ns_unknown);

		if (!bChangedOnly || poFileStorageSP->_get_needsave() == ns_yes)
		{
			CNEO_filestorage * poDestFileStorage = poDestTrans->_search_local_filestorage_map(
				poFileStorageSP->GetParentTypeid(),
				poFileStorageSP->GetParentId(),
				poFileStorageSP->GetOuterFieldNr());

			if (poDestFileStorage != NULL)
			{
				poDestFileStorage->_copy_from(*poFileStorageSP);
			}
			else
			{
				poDestTrans->_add_to_local_filestorage_map(poFileStorageSP->clone());
			}
		}
	}
}

/*
SEPTBUG
void CNEO_trans::_update_reference_storage()
{
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while(pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos,hyperId);

		ASSERT(poStorageSP->_get_needsave() != ns_unknown);	//caller has to evaluate first !
		SCP<CNEO_storage> poPrevRefStorageSP = _search_reference_storage_map(poStorageSP->GetType(),poStorageSP->GetThis());
		ASSERT(poPrevRefStorageSP.PointsObject());
		poPrevRefStorageSP->_copy_from(*poStorageSP);
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while(pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos,hyperId);
		ASSERT(poListStorageSP->_get_needsave() != ns_unknown);
		SCP<CNEO_liststorage> poPrevRefListStorageSP = _search_reference_liststorage_map(poListStorageSP->GetCollectionId(),poListStorageSP->GetParentId());
		ASSERT(poPrevRefListStorageSP.PointsObject());
		poPrevRefListStorageSP->_copy_from(*poListStorageSP);
	}

	//nie ma file reference..
}
*/


void CNEO_trans::_propagate_workset()
{
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);

		ASSERT(poStorageSP->_get_needsave() != ns_unknown);	//caller has to evaluate first !
		_propagate_storage_change(poStorageSP);
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);
		ASSERT(poListStorageSP->_get_needsave() != ns_unknown);
		_propagate_liststorage_change(poListStorageSP);
	}

	pos = m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_filestorage> poFileStorageSP = m_oLocalFileStorageMap.GetNext(pos, hyperId);

		ASSERT(poFileStorageSP->_get_needsave() != ns_unknown);
		_propagate_filestorage_change(poFileStorageSP);
	}
}

bool CNEO_trans::is_user_modified()
{
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);
		switch (poStorageSP->_get_usermodified())
		{
		case um_yes:
			return true;
		case um_no:
			break;
		case um_unknown:
		{
			//full compare
			SCP<CNEO_storage> poRefStorageSP;
			VERIFY(m_oReferenceStorageMap.Lookup(hyperId, poRefStorageSP));
			if (poStorageSP->full_is_usermodified(*poRefStorageSP))
			{
				return true;
			}
		}
		break;
		default:
			ASSERT(false);
		}
		ASSERT(poStorageSP->_get_usermodified() != um_unknown);
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);
		switch (poListStorageSP->_get_usermodified())
		{
		case um_yes:
			return true;
		case um_no:
			break;
		case um_unknown:
		{
			SCP<CNEO_liststorage> poRefListStorageSP;
			VERIFY(m_oReferenceListStorageMap.Lookup(hyperId, poRefListStorageSP));
			if (poListStorageSP->full_is_usermodified(*poRefListStorageSP))
			{
				return true;
			}
		}
		break;
		default:
			ASSERT(false);
		}
		ASSERT(poListStorageSP->_get_usermodified() != um_unknown);
	}
	pos = m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_filestorage> poFileStorageSP = m_oLocalFileStorageMap.GetNext(pos, hyperId);
		switch (poFileStorageSP->_get_usermodified())
		{
		case um_yes:
			return true;
		case um_no:
			break;
		case um_unknown:
		{
			if (poFileStorageSP->full_is_usermodified())
			{
				return true;
			}
		}
		break;
		default:
			ASSERT(false);
		}
	}
	return false;
}

//czyœci localne mapy z nieu¿ywanych storage /list storage
void CNEO_trans::purge_maps()
{
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);
		if (!poStorageSP->InExternalUse())
		{
			m_oLocalStorageMap.RemoveAtPosition(oldpos);
			VERIFY(m_oReferenceStorageMap.RemoveKey(hyperId));
			poStorageSP = 0;
		}
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);
		if (!poListStorageSP->InExternalUse())
		{
			m_oLocalListStorageMap.RemoveAtPosition(oldpos);
			VERIFY(m_oReferenceListStorageMap.RemoveKey(hyperId));
			poListStorageSP = 0;
		}
	}

	pos = m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_filestorage> poFileStorageSP = m_oLocalFileStorageMap.GetNext(pos, hyperId);
		if (!poFileStorageSP->InExternalUse())
		{
			m_oLocalFileStorageMap.RemoveAtPosition(oldpos);
			poFileStorageSP = 0;
		}
	}
}

void CNEO_trans::release_write_locks()
{
	m_oVirtLockArray.RemoveAll();
	m_poLocalLockMap->release_all_write_locks();
	flush_pending_unlocks();
}

void CNEO_trans::_propagate_storage_change(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	//propagate to every previous transaction
	CNEO_trans * poPrevTrans = m_poPrevTransaction;
	while (poPrevTrans)
	{
		CNEO_storage * poStorage = poPrevTrans->_search_local_storage_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
		if (poStorage != NULL)
		{
			if (rpoStorageSP->IsDeleted() && !poStorage->InExternalUse())
			{
				poPrevTrans->_remove_from_local_storage_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
				VERIFY(poPrevTrans->m_oReferenceStorageMap.RemoveKey(
					longlong(rpoStorageSP->GetType(), rpoStorageSP->GetThis())));
			}
			else
			{
				poStorage->_copy_from(*rpoStorageSP);
				SCP<CNEO_storage> poPrevRefStorageSP = poPrevTrans->_search_reference_storage_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
				ASSERT(poPrevRefStorageSP.PointsObject());
				poPrevRefStorageSP->_copy_from(*rpoStorageSP);
			}
		}
		poPrevTrans = poPrevTrans->m_poPrevTransaction;
	}

	//propagate to global cache
	CNEO_storage * poStorage = m_poCoordinator->get_storage_cache()->_search_RLU_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
	if (poStorage != NULL)
	{
		if (rpoStorageSP->IsDeleted() && !poStorage->InExternalUse())
		{
			m_poCoordinator->get_storage_cache()->_remove_from_RLU_map(poStorage);
			delete poStorage;
		}
		else
		{
			poStorage->_copy_from(*rpoStorageSP);
		}
	}
}

void CNEO_trans::_propagate_liststorage_change(SCP<CNEO_liststorage> & rpoListStorageSP)
{
	ASSERT(rpoListStorageSP.PointsObject());
	CNEO_trans * poPrevTrans = m_poPrevTransaction;
	while (poPrevTrans)
	{
		CNEO_liststorage * poListStorage = poPrevTrans->_search_local_liststorage_map(rpoListStorageSP->GetCollectionId(), rpoListStorageSP->GetParentId());
		if (poListStorage != NULL)
		{
			poListStorage->_copy_from(*rpoListStorageSP);
			SCP<CNEO_liststorage> poPrevRefListStorageSP = poPrevTrans->_search_reference_liststorage_map(rpoListStorageSP->GetCollectionId(), rpoListStorageSP->GetParentId());
			ASSERT(poPrevRefListStorageSP.PointsObject());
			poPrevRefListStorageSP->_copy_from(*rpoListStorageSP);
		}
		poPrevTrans = poPrevTrans->m_poPrevTransaction;
	}

	CNEO_liststorage * poListStorage = m_poCoordinator->get_storage_cache()->_search_list_map(rpoListStorageSP->GetCollectionId(), rpoListStorageSP->GetParentId());
	if (poListStorage != NULL)
	{
		poListStorage->_copy_from(*rpoListStorageSP);
	}
}

void CNEO_trans::_propagate_filestorage_change(SCP<CNEO_filestorage> & rpoFileStorageSP)
{
	ASSERT(rpoFileStorageSP.PointsObject());
	CNEO_trans * poPrevTrans = m_poPrevTransaction;
	while (poPrevTrans)
	{
		CNEO_filestorage * poFileStorage = poPrevTrans->_search_local_filestorage_map(
			rpoFileStorageSP->GetParentTypeid(),
			rpoFileStorageSP->GetParentId(),
			rpoFileStorageSP->GetOuterFieldNr());

		if (poFileStorage != NULL)
		{
			poFileStorage->_copy_from(*rpoFileStorageSP);
		}
		poPrevTrans = poPrevTrans->m_poPrevTransaction;
	}

	CNEO_filestorage * poFileStorage = m_poCoordinator->get_storage_cache()->_search_file_map(
		rpoFileStorageSP->GetParentTypeid(),
		rpoFileStorageSP->GetParentId(),
		rpoFileStorageSP->GetOuterFieldNr());
	if (poFileStorage != NULL)
	{
		poFileStorage->_copy_from(*rpoFileStorageSP);
	}
}

void CNEO_trans::_propagate_commited(eTransState TransState)
{
	m_eTransState = TransState;

	for (
		CNEO_trans * poPrevTrans = m_poPrevTransaction;
		poPrevTrans != NULL;
		poPrevTrans = poPrevTrans->m_poPrevTransaction)
	{
		//neo_todo: analiza
		poPrevTrans->m_eTransState = TransState;
	}
}

void CNEO_trans::evaluate_and_purge_not_needsave_maps(bool bPurge)
{

	TRACE("---------- starting tr:eval --------------------\n");
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);

		evaluate_storage(poStorageSP);

		ASSERT(poStorageSP->_get_needsave() != ns_unknown);

		bool bRemove = (poStorageSP->_get_needsave() == ns_no);

		if (!poStorageSP->InExternalUse() && bPurge)
		{
			if (bRemove)
			{
				m_oLocalStorageMap.RemoveAtPosition(oldpos);
				VERIFY(m_oReferenceStorageMap.RemoveKey(hyperId));
				poStorageSP = 0;
			}
		}
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);

		evaluate_list_storage(poListStorageSP);

		ASSERT(poListStorageSP->_get_needsave() != ns_unknown);

		bool bRemove = (poListStorageSP->_get_needsave() == ns_no);

		if (!poListStorageSP->InExternalUse() && bPurge)
		{
			if (bRemove)
			{
				m_oLocalListStorageMap.RemoveAtPosition(oldpos);
				VERIFY(m_oReferenceListStorageMap.RemoveKey(hyperId));
				poListStorageSP = 0;
			}
		}
	}

	pos = m_oLocalFileStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		POSITION oldpos = pos;
		SCP<CNEO_filestorage> poFileStorageSP = m_oLocalFileStorageMap.GetNext(pos, hyperId);

		evaluate_file_storage(poFileStorageSP);

		ASSERT(poFileStorageSP->_get_needsave() != ns_unknown);

		bool bRemove = (poFileStorageSP->_get_needsave() == ns_no);

		if (!poFileStorageSP->InExternalUse() && bPurge)
		{
			if (bRemove)
			{
				m_oLocalFileStorageMap.RemoveAtPosition(oldpos);
				poFileStorageSP = 0;
			}
		}
	}

	TRACE("---------- completed tr:eval --------------------\n");
}

void CNEO_trans::evaluate_storage(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());

	switch (rpoStorageSP->_get_needsave())
	{
	case ns_yes:
		TRACE("tr:eval: %s[%d] said YES\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
		break;
	case ns_no:
		TRACE("tr:eval: %s[%d] said NO\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
		break;
	case ns_unknown:
	{
		TRACE("tr:eval: %s[%d] said UNK will be eval\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
		//full compare
		SCP<CNEO_storage> poRefStorageSP = _search_reference_storage_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
		ASSERT(poRefStorageSP.PointsObject());
		rpoStorageSP->full_is_usermodified(*poRefStorageSP);	//wo³ane aby wyliczyæ
		if (rpoStorageSP->_get_needsave() == ns_yes)
		{
			TRACE("tr:eval: %s[%d] evaluated to YES\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
		}
		else
		{
			TRACE("tr:eval: %s[%d] evaluated to NO\n", rpoStorageSP->GetDefinition()->GetTableName(), rpoStorageSP->GetThis());
		}
	}
	break;
	default:
		ASSERT(false);
	}
	ASSERT(rpoStorageSP->_get_needsave() != ns_unknown);
}

void CNEO_trans::evaluate_list_storage(SCP<CNEO_liststorage> & rpoListStorageSP)
{
	ASSERT(rpoListStorageSP.PointsObject());
	switch (rpoListStorageSP->_get_needsave())
	{
	case ns_yes:
		TRACE("tr:eval:list [%d:%d]=%d said YES\n",
			rpoListStorageSP->GetParentTypeid(),
			rpoListStorageSP->GetParentId(),
			rpoListStorageSP->GetCollectionId());
		break;
	case ns_no:
		TRACE("tr:eval:list [%d:%d]=%d said NO\n",
			rpoListStorageSP->GetParentTypeid(),
			rpoListStorageSP->GetParentId(),
			rpoListStorageSP->GetCollectionId());
		break;
	case ns_unknown:
	{
		TRACE("tr:eval:list [%d:%d]=%d said UNK, will eval\n",
			rpoListStorageSP->GetParentTypeid(),
			rpoListStorageSP->GetParentId(),
			rpoListStorageSP->GetCollectionId());
		//full compare
		SCP<CNEO_liststorage> poRefListStorageSP = _search_reference_liststorage_map(
			rpoListStorageSP->GetCollectionId(),
			rpoListStorageSP->GetParentId());
		ASSERT(poRefListStorageSP.PointsObject());

		rpoListStorageSP->full_is_usermodified(*poRefListStorageSP);
		if (rpoListStorageSP->_get_needsave() == ns_yes)
		{
			TRACE("tr:eval:list [%d:%d]=%d evaluated to YES\n",
				rpoListStorageSP->GetParentTypeid(),
				rpoListStorageSP->GetParentId(),
				rpoListStorageSP->GetCollectionId());
		}
		else
		{
			TRACE("tr:eval:list [%d:%d]=%d evaluated to YES\n",
				rpoListStorageSP->GetParentTypeid(),
				rpoListStorageSP->GetParentId(),
				rpoListStorageSP->GetCollectionId());
		}
	}
	break;
	default:
		ASSERT(false);
	}
	ASSERT(rpoListStorageSP->_get_needsave() != ns_unknown);
}

void CNEO_trans::evaluate_file_storage(SCP<CNEO_filestorage> & rpoFileStorageSP)
{
	switch (rpoFileStorageSP->_get_needsave())
	{
	case ns_yes:
		break;
	case ns_no:
		break;
	case ns_unknown:
	{
		//full compare
		rpoFileStorageSP->full_is_usermodified();
	}
	break;
	default:
		ASSERT(false);
	}
	ASSERT(rpoFileStorageSP->_get_needsave() != ns_unknown);
}

void CNEO_trans::set_user_modified(bool bUserModified)
{
	POSITION pos = m_oLocalStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_storage> poStorageSP = m_oLocalStorageMap.GetNext(pos, hyperId);
		poStorageSP->simple_set_user_modified(bUserModified);
	}

	pos = m_oLocalListStorageMap.GetFirstPosition();
	while (pos != NULL)
	{
		hyper hyperId;
		SCP<CNEO_liststorage> poListStorageSP = m_oLocalListStorageMap.GetNext(pos, hyperId);
		poListStorageSP->simple_set_user_modified(bUserModified);
	}

	//test jest pe³ny tylko w przypadku bUserModified=false 

	ASSERT(is_user_modified() == bUserModified);
}

bool CNEO_trans::_is_inside_change_sequence() const
{
	ASSERT(m_poRollbackLogSP.PointsObject());
	return m_poRollbackLogSP->_is_inside_change_sequence();
}

void CNEO_trans::OnNEO_user_FinalRelease(CNEO_user * poUser)
{
	ASSERT(poUser);
	SCP<CNEO_storage> & rpoStorageSP = poUser->_get_storage();
	VERIFY(m_oNEO_userMap.RemoveKey(longlong(rpoStorageSP->GetType(), rpoStorageSP->GetThis())));
}

void CNEO_trans::OnNEO_listuser_FinalRelease(CNEO_listuser * poListUser)
{
	ASSERT(poListUser);
	SCP<CNEO_liststorage> & rpoListStorageSP = poListUser->_get_storage();
	VERIFY(m_oNEO_listuserMap.RemoveKey(longlong(rpoListStorageSP->GetCollectionId(),
		rpoListStorageSP->GetParentId())));
}

void CNEO_trans::OnNEO_fileuser_FinalRelease(CNEO_fileuser * poFileUser)
{
	ASSERT(poFileUser);
	SCP<CNEO_filestorage> & rpoFileStorageSP = poFileUser->_get_storage();
	ASSERT(rpoFileStorageSP.PointsObject());
	VERIFY(m_oNEO_fileuserMap.RemoveKey(_compose_filestorage_key(rpoFileStorageSP)));
}

void CNEO_trans::OnNEO_cursor_FinalRelease(CNEO_cursor * /*poCursor*/)
{
	//jeœli bêdzie zarz¹dzanie kursorami
}

void CNEO_trans::_add_to_user_map(CNEO_user * poUser)
{
	ASSERT(poUser);
	SCP<CNEO_storage> & rpoStorageSP = poUser->_get_storage();

	ASSERT(NULL == _search_user_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis()));

	m_oNEO_userMap[longlong(rpoStorageSP->GetType(), rpoStorageSP->GetThis())] = poUser;
}

CNEO_user * CNEO_trans::_search_user_map(long TypeId, long IdObj)
{
	CNEO_user * poTest;
	if (m_oNEO_userMap.Lookup(longlong(TypeId, IdObj), poTest))
	{
		return poTest;
	}
	else
	{
		return NULL;
	}
}

SCP<CNEO_user> CNEO_trans::_new_object(long TypeId, long nParentTypeId, long nParentIdObj)
{

	ASSERT((nParentTypeId != 0 && nParentIdObj != 0) || (nParentTypeId == 0 && nParentIdObj == 0));

	SCP<CNEO_storage> poBaseStorageSP = m_poCoordinator->get_storage_cache()->new_object(TypeId);

#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("NEWOBJ %s(%d) created\n",
			poBaseStorageSP->GetDefinition()->GetTableName(), poBaseStorageSP->GetThis());
	}
#endif

	//utwórz nasz¹ w³asn¹ kopiê
	SCP<CNEO_storage> poStorageSP = poBaseStorageSP->clone();
	poStorageSP->_initnew(this);

	_add_to_local_storage_map(poStorageSP);

	/*
		rollback holder jest potrzebny gdy:
		- jesteœmy wewn¹trz triggera (_is_inside_change_seq...)
		lub
		- custom_init (_initnew / _reinit) mo¿e siê nie udaæ -
	*/

	CNEO_rollbackholder oRollbackHolder(NewSCP(this, true));
	oRollbackHolder._registerundo_newobjectcreate(TypeId, poStorageSP->GetThis());

	if (nParentTypeId != 0)
	{
		poStorageSP->_init_parent(nParentTypeId, nParentIdObj);
	}

	SCP<CNEO_user> poUserSP = NewSCP(new CNEO_user(NewSCP(this, true), poStorageSP, false));
	_add_to_user_map(poUserSP);
	bool bInitResult = poStorageSP->_custom_init(poUserSP.Get());

#ifdef _DEBUG
	ASSERT(poStorageSP->m_bConstructed);
#endif

	if (!bInitResult)
	{
		return SCP<CNEO_user>();
	}

	oRollbackHolder.Success();
	_add_to_reference_storage_map(poStorageSP->clone());

	//copy back 'initial' state
	poBaseStorageSP->_copy_from(*poStorageSP);
	return poUserSP;
}

SCP<CNEO_user> CNEO_trans::_get_object(long TypeId, long IdObj, long nParentTypeId, long nParentIdObj)
{
	ASSERT((nParentTypeId != 0 && nParentIdObj != 0) || (nParentTypeId == 0 && nParentIdObj == 0));

	CNEO_user * poUser = _search_user_map(TypeId, IdObj);
	if (poUser != NULL)	//found object in external use
	{
		return NewSCP(poUser, true);
	}
	bool bForceLoad = false;
	if (nParentTypeId != 0)
	{
		bForceLoad = _is_write_lock(LOCKCLASS_OBJECT, nParentTypeId, nParentIdObj, 0);
	}
	//object is not externally used now - look for storage and create neo_user
	eProvStorRes ePSR;
	SCP<CNEO_storage> poBaseStorageSP = _provide_storage(TypeId, IdObj, bForceLoad, ePSR);
	if (poBaseStorageSP.PointsNull())
	{
		return SCP<CNEO_user>();
	}

	SCP<CNEO_storage> poStorageSP;
	if (ePSR == psr_cacheinit || ePSR == psr_cachenoinit)
	{
		//utwórz nasz¹ w³asn¹ kopiê
		poStorageSP = poBaseStorageSP->clone();
		_add_to_local_storage_map(poStorageSP);
	}
	else
	{
		poStorageSP = poBaseStorageSP;
	}

	ASSERT(poStorageSP.PointsObject());

	if (nParentTypeId != 0)
	{
		poStorageSP->_init_parent(nParentTypeId, nParentIdObj);
	}

	SCP<CNEO_user> poUserSP = NewSCP(new CNEO_user(NewSCP(this, true), poStorageSP, (ePSR == psr_prevtrans)));
	_add_to_user_map(poUserSP);
	if (ePSR == psr_cacheinit)
	{
		CNEO_rollbackholder oRollbackHolder(NewSCP(this, true));
		bool bInitResult = poStorageSP->_custom_init(poUserSP.Get());
		if (!bInitResult)
		{
			return SCP<CNEO_user>();
		}
		oRollbackHolder.Success();
	}
	if (ePSR == psr_cacheinit || ePSR == psr_cachenoinit)
	{
		_add_to_reference_storage_map(poStorageSP->clone());

		//copy back 'initial' state
		poBaseStorageSP->_copy_from(*poStorageSP);
	}

#ifdef _DEBUG
	ASSERT(poStorageSP->m_bConstructed);
#endif
	return poUserSP;
}

SCP<CNEO_user> CNEO_trans::_get_user_for_ready_storage(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	CNEO_user * poUser = _search_user_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis());
	if (poUser != NULL)	//found object in external use
	{
		return NewSCP(poUser, true);
	}
	SCP<CNEO_user> poUserSP = NewSCP(new CNEO_user(NewSCP(this, true), rpoStorageSP, false));
	_add_to_user_map(poUserSP);
	return poUserSP;
}

CNEO_listuser * CNEO_trans::_search_listuser_map(long CollectionId, long ParentId)
{
	CNEO_listuser * poTestListUser;
	if (m_oNEO_listuserMap.Lookup(longlong(CollectionId, ParentId), poTestListUser))
	{
		return poTestListUser;
	}
	else
	{
		return NULL;
	}
}


SCP<CNEO_listuser> CNEO_trans::_get_list(long nCollectionId, long IdParent, bool bForNewParent)
{
	CNEO_listuser * poListUser = _search_listuser_map(nCollectionId, IdParent);
	if (poListUser != NULL)
	{
		return NewSCP(poListUser, true);
	}

	SCP<CNEO_listuser> poListUserSP;
	//list not externally used now - look for storage
	bool bLocalCopy;	//== !bReadOnly
	SCP<CNEO_liststorage> poListStorageSP = _provide_liststorage(nCollectionId, IdParent, bForNewParent, bLocalCopy);
	if (poListStorageSP.PointsObject())
	{
		poListUserSP = NewSCP(new CNEO_listuser(NewSCP(this, true), poListStorageSP, !bLocalCopy));
	}
	_add_to_listuser_map(poListUserSP);
	return poListUserSP;
}

SCP<CNEO_listuser> CNEO_trans::_get_old_list(long nCollectionId, long nIdParent)
{
	SCP<CNEO_liststorage> poOldListStorageSP = _search_reference_liststorage_map(nCollectionId, nIdParent);
	if (poOldListStorageSP.PointsObject())
	{
		SCP<CNEO_listuser> poOldListUserSP = NewSCP(new CNEO_listuser(NewSCP(this, true), poOldListStorageSP, true));
		ASSERT(poOldListUserSP.PointsObject());	//must exist
		return poOldListUserSP;
	}
	else
	{
		return SCP<CNEO_listuser>();
	}
}

SCP<CNEO_fileuser> CNEO_trans::_get_file(long nParentTypeId, long nParentIdObj, long nOuterFieldNr, bool bForNewParent)
{
	CNEO_fileuser * poFileUser = _search_fileuser_map(nParentTypeId, nParentIdObj, nOuterFieldNr);
	if (poFileUser != NULL)
	{
		return NewSCP(poFileUser, true);
	}

	//provide_filestorage
	SCP<CNEO_filestorage> poFileStorageSP;
	CNEO_filestorage * poFileStorage = _search_local_filestorage_map(nParentTypeId, nParentIdObj, nOuterFieldNr);
	if (poFileStorage != NULL)
	{
		poFileStorageSP = NewSCP(poFileStorage, true);
	}
	else
	{
		if (bForNewParent)
		{
			poFileStorageSP = m_poCoordinator->get_storage_cache()->new_file(nParentTypeId, nParentIdObj, nOuterFieldNr, bForNewParent);
		}
		else
		{
			m_poCoordinator->get_storage_cache()->load_file(nParentTypeId, nParentIdObj, nOuterFieldNr, bForNewParent, poFileStorageSP);
		}

		poFileStorageSP = poFileStorageSP->clone();
		_add_to_local_filestorage_map(poFileStorageSP);
	}


	SCP<CNEO_fileuser> poFileUserSP =
		NewSCP(new CNEO_fileuser(NewSCP(this, true), poFileStorageSP, true));
	_add_to_fileuser_map(poFileUserSP);
	return poFileUserSP;
}


SCP<CNEO_storage> CNEO_trans::_copy_on_write_storage(SCP<CNEO_storage> & rpoROStorageSP)
{
	ASSERT(rpoROStorageSP.PointsObject());

	//if loaded by us - it is 'writable' by definition
	if (_search_local_storage_map(rpoROStorageSP->GetType(), rpoROStorageSP->GetThis()))
	{
		return rpoROStorageSP;
	}
	//not our copy - need to clone
	SCP<CNEO_storage> poCloneStorageSP = rpoROStorageSP->clone();
	ASSERT(poCloneStorageSP.PointsObject());
	//add to our map
	_add_to_local_storage_map(poCloneStorageSP);
	_add_to_reference_storage_map(poCloneStorageSP->clone());

	ASSERT(NULL != _search_local_storage_map(poCloneStorageSP->GetType(), poCloneStorageSP->GetThis()));

	return poCloneStorageSP;
}

SCP<CNEO_liststorage> CNEO_trans::_copy_on_write_liststorage(SCP<CNEO_liststorage> & rpoROListStorageSP)
{
	ASSERT(rpoROListStorageSP.PointsObject());
	//if loaded by us - it is 'writable' by definition
	if (_search_local_liststorage_map(rpoROListStorageSP->GetCollectionId(), rpoROListStorageSP->GetParentId()))
	{
		return rpoROListStorageSP;
	}
	//not our copy - need to clone
	SCP<CNEO_liststorage> poCloneListStorageSP = rpoROListStorageSP->clone();
	_add_to_local_liststorage_map(poCloneListStorageSP);
	_add_to_reference_liststorage_map(poCloneListStorageSP->clone());

	ASSERT(NULL != _search_local_liststorage_map(
		poCloneListStorageSP->GetCollectionId(), poCloneListStorageSP->GetParentId()));
	return poCloneListStorageSP;
}

bool CNEO_trans::_is_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	return m_poLocalLockMap->_search_write_lock_map(nClass, nTypeId, nIdObj, nExtra);
}

class ckeep_storage_holder
{
public:
	ckeep_storage_holder(CNEO_user * poUser, SCP<CNEO_storage> & rpoWorkStorageSP) :
		m_poUser(poUser)
	{
		ASSERT(m_poUser != NULL);

		m_poOriginalStorageSP = m_poUser->_get_storage();
		m_poUser->_get_storage() = rpoWorkStorageSP;
	}

	~ckeep_storage_holder()
	{
		m_poUser->_get_storage() = m_poOriginalStorageSP;
	}
private:
	SCP<CNEO_storage> m_poOriginalStorageSP;
	CNEO_user * m_poUser;
};

SCP<CNEO_storage> CNEO_trans::_write_lock(SCP<CNEO_storage> & rpoStorageSP, bool & rbSuccess, CNEO_user * poUser)
{
	ASSERT(rpoStorageSP.PointsObject());
	ASSERT(poUser);
	ASSERT(rpoStorageSP->IsOld());	//nie ma sensu lockowaæ nowych obiektów!!
	ASSERT(!rpoStorageSP->GetDefinition()->IsChild());	//nie wolno lockowaæ dzieci

	const long nTypeId = rpoStorageSP->GetType();
	const long nIdObj = rpoStorageSP->GetThis();

	if (_is_write_lock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0))
	{
		rbSuccess = true;
		return rpoStorageSP;
	}
	//nie ma trzeba prosiæ i to œwie¿¹ kopiê
	SCP<CNEO_storage> poBaseStorageSP;
	bool bNeedInit = false;
	eNEO_loadresult eLR = m_poCoordinator->get_storage_cache()->load_object(this, nTypeId, nIdObj, true, poBaseStorageSP, bNeedInit);
	if (eLR != neolr_ok_newer && eLR != neolr_ok_current)
	{
		ASSERT(poBaseStorageSP.PointsNull());
		return SCP<CNEO_storage>();
	}

	rbSuccess = true;

	//store in local writelock table
	{
		CNEO_rollbackholder oRollbackHolder(NewSCP(this, true));

		m_poLocalLockMap->_add_write_lock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0);

		oRollbackHolder._registerundo_writelock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0);
		oRollbackHolder.Success();
	}

	if (_search_local_storage_map(nTypeId, nIdObj))
	{
		_remove_from_local_storage_map(nTypeId, nIdObj);
	}
	//utwórz nasz¹ w³asn¹ kopiê
	SCP<CNEO_storage> poStorageSP = poBaseStorageSP->clone();
	_add_to_local_storage_map(poStorageSP);
	if (bNeedInit)
	{
		CNEO_rollbackholder oRollbackHolder(NewSCP(this, true));
		//PATCH: 2004-04-02
		//custom init mog³o siê odbywaæ na innym storage ni¿ poStorageSP
		//pola wirtualne by³y inicjowane w innym storage co powodowa³o 'gubienie'
		//wartoœci tych pól po exlock
		{
			ckeep_storage_holder oKeepStorageHolder(poUser, poStorageSP);
			bool bInitResult = poStorageSP->_custom_init(poUser);

			if (!bInitResult)
			{
				return SCP<CNEO_storage>();
			}
		}
		oRollbackHolder.Success();
	}
	_add__or_replace_reference_storage_map(poStorageSP->clone());

	//przetwarzanie konswekwencji
	CStdObjDef * poDefinition = poStorageSP->GetDefinition();
	if (poDefinition->HasAnyList() || poDefinition->HasAnyFile())
	{
		_purge_children_and_lists_of_locked_parent(poStorageSP);
	}
#ifdef _DEBUG
	ASSERT(poStorageSP->m_bConstructed);
#endif

	//copy back 'initial' state
	poBaseStorageSP->_copy_from(*poStorageSP);

	return poStorageSP;
}

void CNEO_trans::_write_unlock(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());

	const long nTypeId = rpoStorageSP->GetType();
	const long nIdObj = rpoStorageSP->GetThis();

	if (_is_write_lock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0))
	{
		m_poCoordinator->get_storage_cache()->release_write_lock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0);
		m_poCoordinator->get_storage_cache()->flush_pending_unlocks();

		m_poLocalLockMap->release_write_lock(LOCKCLASS_OBJECT, nTypeId, nIdObj, 0);
		m_poLocalLockMap->_access_pending_unlocks().RemoveAll();
	}
}

bool CNEO_trans::aquire_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	if (!m_poCoordinator->get_storage_cache()->aquire_write_lock(nClass, nTypeId, nIdObj, nExtra))
	{
		return false;
	}
	m_poLocalLockMap->_add_write_lock(nClass, nTypeId, nIdObj, nExtra);
	return true;
}

void CNEO_trans::release_write_lock(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	ASSERT(_is_write_lock(nClass, nTypeId, nIdObj, nExtra));
	m_poLocalLockMap->release_write_lock(nClass, nTypeId, nIdObj, nExtra);
}

void CNEO_trans::flush_pending_unlocks()
{
	for (long iter = 0; iter < m_poLocalLockMap->_access_pending_unlocks().GetSize(); iter++)
	{
		navolock & roNavoLock = m_poLocalLockMap->_access_pending_unlocks()[iter];
		m_poCoordinator->get_storage_cache()->
			release_write_lock(roNavoLock.m_fullid.m_class, roNavoLock.m_fullid.m_typeid,
				roNavoLock.m_fullid.m_idobj, roNavoLock.m_fullid.m_extra);
	}
	m_poCoordinator->get_storage_cache()->flush_pending_unlocks();
	m_poLocalLockMap->_access_pending_unlocks().RemoveAll();
}


void CNEO_trans::_purge_children_and_lists_of_locked_parent(SCP<CNEO_storage> & rpoStorageSP)
{
	//1. usuñ z local_storage wszystkie dzieci jaki wczytaliœmy, to samo z reference storage
	//2. usuñ z local_list_storage wszystkie listy tego ojca (spis elementów)
	CStdObjDef * poDefinition = rpoStorageSP->GetDefinition();
	for (long iter = 1; iter < poDefinition->GetFieldCount(); iter++)
	{
		long nRelationType = poDefinition->GetField(iter)->GetRelationType();
		if (nRelationType == RELT_LIST)
		{
			long nCollectionId = _compose_collection_id(rpoStorageSP->GetType(), iter);
			long nParentIdObj = rpoStorageSP->GetThis();
			CNEO_liststorage * poListStorage = _search_local_liststorage_map(nCollectionId, nParentIdObj);
			if (poListStorage != NULL)
			{
				long nChildTypeId = poListStorage->GetChildTypeid();
				for (long iter2 = 0; poListStorage->is_element_at(iter2); iter2++)
				{
					long nChildIdObj = poListStorage->get_element_at(iter2);
					if (_search_local_storage_map(nChildTypeId, nChildIdObj))
					{
						_remove_from_local_storage_map(nChildTypeId, nChildIdObj);
						VERIFY(m_oReferenceStorageMap.RemoveKey(longlong(nChildTypeId, nChildIdObj)));
					}
				}
				_remove_from_local_liststorage_map(nCollectionId, nParentIdObj);
				VERIFY(m_oReferenceListStorageMap.RemoveKey(longlong(nCollectionId, nParentIdObj)));
			}
		}
		else if (nRelationType == RELT_FILE)	//usuñ z local storage wszystkie "pliki"
		{
			CNEO_filestorage * poFileStorage = _search_local_filestorage_map(
				rpoStorageSP->GetType(), rpoStorageSP->GetThis(), iter);
			if (poFileStorage != NULL)
			{
				_remove_from_local_filestorage_map(NewSCP(poFileStorage, true));
			}
		}
	}
}

SCP<CNEO_storage> CNEO_trans::_provide_storage(long TypeId, long IdObj, bool bForceLoad, eProvStorRes & rePSR)
{
#ifdef _DEBUG
	m_poCoordinator->m_nProvideStorageCalls++;
#endif
	//1. look in our working set
	CNEO_storage * poStorage = _search_local_storage_map(TypeId, IdObj);
	if (poStorage != NULL)
	{

#ifdef _DEBUG
		{
			SCP<CNEO_storage> poTestStorageSP;
			ASSERT(m_oReferenceStorageMap.Lookup(longlong(TypeId, IdObj), poTestStorageSP));
		}
#endif

		rePSR = psr_local;
		return NewSCP(poStorage, true);
	}

	if (!bForceLoad)
	{
		//2. get from previous trans chain (if any)
		CNEO_trans * poPrevTrans = m_poPrevTransaction;
		while (poPrevTrans)
		{
			poStorage = poPrevTrans->_search_local_storage_map(TypeId, IdObj);
			if (poStorage != NULL)
			{
				break;
			}
			poPrevTrans = poPrevTrans->m_poPrevTransaction;
		}

		if (poStorage != NULL)
		{
			rePSR = psr_prevtrans;
			SCP<CNEO_storage> poStorageSP = NewSCP(poStorage, true);
			return poStorageSP;
		}
	}

#ifdef _DEBUG
	m_poCoordinator->m_nLoadObjectCalls++;
#endif

	//3. load from global_cache -> DB
	SCP<CNEO_storage> poBaseStorageSP;
	bool bNeedInit = false;
	eNEO_loadresult eLR = m_poCoordinator->get_storage_cache()->load_object(this, TypeId, IdObj, false, poBaseStorageSP, bNeedInit);
	if (eLR != neolr_ok_newer && eLR != neolr_ok_current)
	{
		ASSERT(poBaseStorageSP.PointsNull());
		return SCP<CNEO_storage>();
	}
	rePSR = bNeedInit ? psr_cacheinit : psr_cachenoinit;
	return poBaseStorageSP;
}

SCP<CNEO_liststorage> CNEO_trans::_provide_liststorage(long nCollectionId, long nIdParent, bool bForNewParent, bool & rbLocalCopy)
{
	//1. look in our working set
	CNEO_liststorage * poListStorage = _search_local_liststorage_map(nCollectionId, nIdParent);
	if (poListStorage != NULL)
	{
#ifdef _DEBUG
		{
			SCP<CNEO_liststorage> poTestListStorageSP;
			ASSERT(m_oReferenceListStorageMap.Lookup(longlong(nCollectionId, nIdParent),
				poTestListStorageSP));
		}
#endif
		rbLocalCopy = true;
		return NewSCP(poListStorage, true);
	}
	//2. get from previous trans chain (if any)
	CNEO_trans * poPrevTrans = m_poPrevTransaction;
	while (poPrevTrans)
	{
		poListStorage = poPrevTrans->_search_local_liststorage_map(nCollectionId, nIdParent);
		if (poListStorage != NULL)
		{
			break;
		}
		poPrevTrans = poPrevTrans->m_poPrevTransaction;
	}
	if (poListStorage != NULL)
	{
		rbLocalCopy = false;
		return NewSCP(poListStorage, true);
	}
	//3. load from global_cache -> DB
	SCP<CNEO_liststorage> poListStorageSP;
	if (bForNewParent)
	{
		poListStorageSP = m_poCoordinator->get_storage_cache()->new_list(nCollectionId, nIdParent, bForNewParent);
	}
	else
	{
		m_poCoordinator->get_storage_cache()->load_list(nCollectionId, nIdParent, bForNewParent, poListStorageSP);
	}
	poListStorageSP = poListStorageSP->clone();
	_add_to_local_liststorage_map(poListStorageSP);
	_add_to_reference_liststorage_map(poListStorageSP->clone());
	rbLocalCopy = true;
	return poListStorageSP;
}

//--------------------- manages local storage copies ----------------
CNEO_storage * CNEO_trans::_search_local_storage_map(long TypeId, long IdObj)
{
	SCP<CNEO_storage> * ppoStorageSP = m_oLocalStorageMap.SafeGetAt(longlong(TypeId, IdObj));
	if (ppoStorageSP != NULL)
	{
		return ppoStorageSP->Get();
	}
	else
	{
		return NULL;
	}
}

void CNEO_trans::_add_to_listuser_map(CNEO_listuser * poListUser)
{
	ASSERT(poListUser);
	SCP<CNEO_liststorage> & rpoListStorageSP = poListUser->_get_storage();

	ASSERT(NULL == _search_listuser_map(rpoListStorageSP->GetCollectionId(), rpoListStorageSP->GetParentId()));

	hyper hyperListId = longlong(rpoListStorageSP->GetCollectionId(), rpoListStorageSP->GetParentId());
	m_oNEO_listuserMap[hyperListId] = poListUser;
}


void CNEO_trans::_add_to_fileuser_map(CNEO_fileuser * poFileUser)
{
	ASSERT(poFileUser);
	SCP<CNEO_filestorage> & rpoFileStorageSP = poFileUser->_get_storage();
	ASSERT(_search_fileuser_map(rpoFileStorageSP->GetParentTypeid(),
		rpoFileStorageSP->GetParentId(), rpoFileStorageSP->GetOuterFieldNr()) == NULL);
	m_oNEO_fileuserMap[_compose_filestorage_key(rpoFileStorageSP)] = poFileUser;

}

CNEO_fileuser * CNEO_trans::_search_fileuser_map(long nParentTypeId, long nParentIdObj, long nOuterFieldNr)
{
	CNEO_fileuser * poFileUser = NULL;
	if (m_oNEO_fileuserMap.Lookup(longlong(_compose_filemapping_id(nParentTypeId, nOuterFieldNr), nParentIdObj), poFileUser))
	{
		return poFileUser;
	}
	else
	{
		return NULL;
	}
}

void CNEO_trans::_add_to_local_storage_map(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	long nTypeId = rpoStorageSP->GetType();
	long nIdObj = rpoStorageSP->GetThis();

	hyper hyperId = longlong(nTypeId, nIdObj);
	m_oLocalStorageMap.Add(hyperId, rpoStorageSP);
}

void CNEO_trans::_remove_from_local_storage_map(long TypeId, long IdObj)
{
	hyper hyperId = longlong(TypeId, IdObj);
	m_oLocalStorageMap.Remove(hyperId);
}

SCP<CNEO_storage> CNEO_trans::_search_reference_storage_map(long TypeId, long IdObj)
{
	SCP<CNEO_storage> poStorageSP;
	if (m_oReferenceStorageMap.Lookup(longlong(TypeId, IdObj), poStorageSP))
	{
		return poStorageSP;
	}
	return SCP<CNEO_storage>();
}

void CNEO_trans::_add_to_reference_storage_map(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	ASSERT(_search_reference_storage_map(rpoStorageSP->GetType(), rpoStorageSP->GetThis()).PointsNull());

	_add__or_replace_reference_storage_map(rpoStorageSP);
}


void CNEO_trans::_add__or_replace_reference_storage_map(SCP<CNEO_storage> & rpoStorageSP)
{
	ASSERT(rpoStorageSP.PointsObject());
	long nTypeId = rpoStorageSP->GetType();
	long nIdObj = rpoStorageSP->GetThis();

	m_oReferenceStorageMap[longlong(nTypeId, nIdObj)] = rpoStorageSP;
}

SCP<CNEO_liststorage> CNEO_trans::_search_reference_liststorage_map(long nCollectionId, long nIdParent)
{
	SCP<CNEO_liststorage> poListStorageSP;
	if (m_oReferenceListStorageMap.Lookup(longlong(nCollectionId, nIdParent), poListStorageSP))
	{
		return poListStorageSP;
	}
	else
	{
		return SCP<CNEO_liststorage>();
	}
}

void CNEO_trans::_add_to_reference_liststorage_map(SCP<CNEO_liststorage> & rpoListStorageSP)
{
	ASSERT(rpoListStorageSP.PointsObject());
	long nCollectionId = rpoListStorageSP->GetCollectionId();
	long nParentId = rpoListStorageSP->GetParentId();

	hyper hyperId = longlong(nCollectionId, nParentId);

	ASSERT(_search_reference_liststorage_map(nCollectionId, nParentId).PointsNull());
	m_oReferenceListStorageMap[hyperId] = rpoListStorageSP;
}


//---------- manages local liststorage copies ------------------------
CNEO_liststorage * CNEO_trans::_search_local_liststorage_map(long nCollectionId, long nIdParent)
{
	SCP<CNEO_liststorage> * ppoListStorageSP =
		m_oLocalListStorageMap.SafeGetAt(longlong(nCollectionId, nIdParent));
	if (ppoListStorageSP != NULL)
	{
		return ppoListStorageSP->Get();
	}
	else
	{
		return NULL;
	}
}

void CNEO_trans::_add_to_local_liststorage_map(SCP<CNEO_liststorage> & rpoListStorageSP)
{
	ASSERT(rpoListStorageSP.PointsObject());
	long nCollectionId = rpoListStorageSP->GetCollectionId();
	long nParentId = rpoListStorageSP->GetParentId();

	hyper hyperId = longlong(nCollectionId, nParentId);
	m_oLocalListStorageMap.Add(hyperId, rpoListStorageSP);
}

void CNEO_trans::_remove_from_local_liststorage_map(long nCollectionId, long nIdParent)
{
	hyper hyperId = longlong(nCollectionId, nIdParent);
	m_oLocalListStorageMap.Remove(hyperId);
}


CNEO_filestorage * CNEO_trans::_search_local_filestorage_map(long nParentTypeId, long nParentIdObj, long nOuterFieldNr)
{
	SCP<CNEO_filestorage> * ppoFileStorageSP = m_oLocalFileStorageMap.SafeGetAt(longlong(_compose_filemapping_id(nParentTypeId, nOuterFieldNr), nParentIdObj));
	if (ppoFileStorageSP != NULL)
	{
		return ppoFileStorageSP->Get();
	}
	else
	{
		return NULL;
	}
}

void CNEO_trans::_add_to_local_filestorage_map(SCP<CNEO_filestorage> & rpoFileStorageSP)
{
	ASSERT(rpoFileStorageSP.PointsObject());
	ASSERT(_search_local_filestorage_map(rpoFileStorageSP->GetParentTypeid(),
		rpoFileStorageSP->GetParentId(), rpoFileStorageSP->GetOuterFieldNr()) == NULL);

	hyper hyperId = _compose_filestorage_key(rpoFileStorageSP);
	m_oLocalFileStorageMap.Add(hyperId, rpoFileStorageSP);
}

void CNEO_trans::_remove_from_local_filestorage_map(SCP<CNEO_filestorage> & rpoFileStorageSP)
{
	ASSERT(rpoFileStorageSP.PointsObject());
	hyper hyperId = _compose_filestorage_key(rpoFileStorageSP);
	m_oLocalFileStorageMap.Remove(hyperId);
}


//--------------------- variables -----------------------------------

void CNEO_trans::set_var(long nVarNr, const CSmartOleVariant & croSOV)
{
	//nie wolno podstawiaæ obiektów (IDispatch) do zmiennych
	ASSERT(croSOV.Type() != VT_DISPATCH);

	m_poEnvironmentHLISP->SetProp(nVarNr, croSOV);
	if (nVarNr >= SHARED_VAR_FIRST && nVarNr <= SHARED_VAR_LAST)
	{
		m_poCoordinator->GetDBAccess()->SetSharedVar(nVarNr, croSOV, 0 /* to_do: originator cookie */);
	}
	else
	{
		if ((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER))
		{
			m_poCoordinator->SetCommonVar(nVarNr, croSOV);
		}
	}
}

bool CNEO_trans::SafeGetProp(long nVarNr, CSmartOleVariant & roSOV) const
{
	//GVAR_TODAY,GVAR_SYSDATE - shared variable server
	//SHARED_VAR_FIRST ... SHARED_VAR_LAST

	if (nVarNr == GVAR_SYSTIME || nVarNr == GVAR_SYSDATE ||
		(nVarNr >= SHARED_VAR_FIRST && nVarNr <= SHARED_VAR_LAST))
	{
		VERIFY(m_poCoordinator->GetDBAccess()->GetSharedVar(nVarNr, roSOV));
		return true;
	}
	else
	{
		if ((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER))
		{
			m_poCoordinator->GetCommonVar(nVarNr, roSOV);
			return true;
		}
		else
		{
			return m_poEnvironmentHLISP->SafeGetProp(nVarNr, roSOV);
		}
	}
}

void CNEO_trans::get_var(long nVarNr, CSmartOleVariant & roSOV)
{
	if (!SafeGetProp(nVarNr, roSOV))
	{
		ThrowNavoException1(ERCO_VIRTTRANS_NO_VARIABLE, IDPAGE_NOTAVAILABLE, nVarNr);
	}
}

bool CNEO_trans::is_var(long nVarNr)
{
	//zmienne mo¿na przekazywaæ pomiêdzy transakcjami

	if (nVarNr == GVAR_SYSTIME || nVarNr == GVAR_SYSDATE ||
		(nVarNr >= SHARED_VAR_FIRST && nVarNr <= SHARED_VAR_LAST))
	{
		CSmartOleVariant oSOV;
		return m_poCoordinator->GetDBAccess()->GetSharedVar(nVarNr, oSOV);
	}
	else
	{
		if ((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER))
		{
			return m_poCoordinator->IsCommonVar(nVarNr);
		}
		else
		{
			return m_poEnvironmentHLISP->PropertyExists(nVarNr);
		}
	}
}

void CNEO_trans::get_canonical_string(CString & roDestString) const
{
	CHyperLinkInfo oTmpHLI(*m_poEnvironmentHLISP);
	oTmpHLI += (*m_poCoordinator->GetCommonEnvironmentHLI());
	oTmpHLI.get_canonical_string(roDestString);
}

long CNEO_trans::fwd_find_stdobj(long TypeId, LPCTSTR lpWhereClause)
{
	long idObj = m_poCoordinator->GetDBAccess()->FindStdObj(TypeId, lpWhereClause);

#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("FIND [%s] WHERE [%s] returned %d\n",
			GetDefinitionManager()->GetStdObjDef(TypeId)->GetTableName(),
			(lpWhereClause == NULL) ? "" : lpWhereClause,
			idObj
		);
	}
#endif

	return idObj;
}

SCP<INAVOObjectCollection> CNEO_trans::fwd_open_cursor(long TypeId, LPCTSTR lpWhereClause, LPCTSTR lpOrderByClause, LPCTSTR lpJoinClause, bool bForwardOnly, long nTop)
{
#ifdef _DEVELOPER_EDITION_
	if (GetDebugOptions().IsTraceAutoCalls())
	{
		GetDebugger().StoreMsg("CURSOR [%s] JOIN [%s] WHERE [%s] ORDER BY [%s]\n",
			GetDefinitionManager()->GetStdObjDef(TypeId)->GetTableName(),
			(lpJoinClause == NULL) ? "" : lpJoinClause,
			(lpWhereClause == NULL) ? "" : lpWhereClause,
			(lpOrderByClause == NULL) ? "" : lpOrderByClause
		);
	}
#endif

	return m_poCoordinator->GetDBAccess()->OpenCursor(TypeId, lpWhereClause, lpOrderByClause, lpJoinClause, bForwardOnly, nTop);
}

bool CNEO_trans::fwd_test_can_delete(long TypeId, long IdObj, SCP<IDispatch> & rpoDiscoRecDispatchSP)
{
	return m_poCoordinator->GetDBAccess()->TestCanDelete(TypeId, IdObj, rpoDiscoRecDispatchSP);
}


SCP<CNEO_cursor> CNEO_trans::CreateRawCursor(long TypeId, LPCTSTR lpWhere, LPCTSTR lpOrderBy, LPCTSTR lpJoin)
{
	return NewSCP(new CNEO_cursor(this, TypeId, lpWhere, lpOrderBy, lpJoin));
}

SCP<CNEO_cursor> CNEO_trans::CreateFTSCursor(long TypeId, long nOuterFieldNr, LPCTSTR lpQuery)
{
	SCP<INAVOObjectCollection> poObjectCollectionSP =
		m_poCoordinator->GetDBAccess()->OpenFTSQuery(_compose_filemapping_id(TypeId, nOuterFieldNr), lpQuery);
	if (poObjectCollectionSP.PointsNull())
	{
		return SCP<CNEO_cursor>();
	}
	return NewSCP(new CNEO_cursor(this, TypeId, poObjectCollectionSP));
}

SCP<CNEO_cursor> CNEO_trans::CreateObjectCursor(long TypeId, long IdCursor)
{
	SCP<CCursorDef> poCursorDefSP = m_poCoordinator->GetDefinitionManager()->GetStdObjDef(TypeId)->GetCursorDef(IdCursor);
	ASSERT(poCursorDefSP.PointsObject());
	CString oWhereString = ReplaceFormalParam(poCursorDefSP->GetWhere(), m_poEnvironmentHLISP.Get());
	CString oOrderByString = ReplaceFormalParam(poCursorDefSP->GetOrderBy(), m_poEnvironmentHLISP.Get());
	CString oJoinString = ReplaceFormalParam(poCursorDefSP->GetJoin(), m_poEnvironmentHLISP.Get());

	return CreateRawCursor(TypeId, oWhereString, oOrderByString, oJoinString);
}

long CNEO_trans::fwd_ExecSQL(LPCTSTR lpSQLCommand)
{
	return m_poCoordinator->GetDBAccess()->ExecSQL(lpSQLCommand);
}

bool CNEO_trans::_exclusive_virtual_lock(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	SCP<CNEO_vlock> poVLockSP = _create_vlock(nClass, nTypeId, nIdObj, nExtra);
	if (poVLockSP->_lock())
	{
		poVLockSP->_set_no_flush();
		m_oVirtLockArray.Add(poVLockSP);
		return true;
	}
	return false;
}

SCP<CNEO_vlock> CNEO_trans::_create_vlock(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	return NewSCP(new CNEO_vlock(NewSCP(this, true), nClass, nTypeId, nIdObj, nExtra));
}

CDefinitionManager * CNEO_trans::GetDefinitionManager()
{
	return m_poCoordinator->GetDefinitionManager();
}

SCP<CNEO_trans> CNEO_trans::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetCC = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetCC);
	CNEO_trans * poTrans = dynamic_cast<CNEO_trans*>(poCmdTargetCC);
	ASSERT(poTrans);
	return NewSCP(poTrans, true);
}

void CNEO_trans::_add_message_external_sink(CNavoErrorInfo & roErrorInfo)
{
	if (m_dispid_message_sink == DISPID_NONE)
	{
		if (!SafeDispatchGetIdOfName(m_poMessageSinkDispatchSP.Get(), L"on_message", m_dispid_message_sink))
		{
			return;
		}
	}

	CSmartOleVariant oArgumentSOVArray[2];
	oArgumentSOVArray[0] = roErrorInfo.GetErrorString();
	oArgumentSOVArray[1] = (long)roErrorInfo.GetErroCode();

	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poMessageSinkDispatchSP, m_dispid_message_sink, oArgumentSOVArray, 2, NULL, &ei);
}


