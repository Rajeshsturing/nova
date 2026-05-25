/*
	NAVO Sp. z o.o. (2002)
	
	NAVO Enterprise

	class CNEO_rollbacklog and related classes

	transactional log


*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
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


CNEO_rollbacklog::CNEO_rollbacklog(CNEO_trans & roTrans) :
	m_nLevel(0),
	m_bOverallSuccess(true),
	m_roTrans(roTrans)
{
}

CNEO_rollbacklog::~CNEO_rollbacklog()
{
	ASSERT(m_nLevel == 0);
}

bool CNEO_rollbacklog::_begin_operation()
{
	if(m_nLevel++ == 0)
	{
		m_bOverallSuccess = true;
		return true;		//this call started overall sequence
	}
	return false;
}

void CNEO_rollbacklog::_finish_operation(bool bSuccess)
{
	m_nLevel--;
	ASSERT(m_nLevel >= 0);
	m_bOverallSuccess = m_bOverallSuccess && bSuccess;
	if(m_nLevel == 0)
	{
		ASSERT(m_bOverallSuccess == bSuccess);
		if(!m_bOverallSuccess)
		{
			_perform_undo();
		}
		_clean();
	}
}

void CNEO_rollbacklog::_registerundo(SCP<CNEO_undoitem__> & rpoUndoItemSP)
{
	m_oUndoItemArray.Add(rpoUndoItemSP);
}

void CNEO_rollbacklog::_clean()
{
	m_oUndoItemArray.RemoveAll();
}

void CNEO_rollbacklog::_perform_undo()
{
	bool bAnyWriteLock = false;

	for(long iter = m_oUndoItemArray.GetUpperBound(); iter >= 0; iter--)
	{
		switch(m_oUndoItemArray[iter]->_get_type())
		{
		case CNEO_undoitem__::it_fldchange:
		{
			CNEO_undofieldchange * poUndoFC = dynamic_cast<CNEO_undofieldchange *>(m_oUndoItemArray[iter].Get());
			ASSERT(poUndoFC);
			
			CNEO_storage * poStorage = m_roTrans._search_local_storage_map(poUndoFC->m_nTypeId,poUndoFC->m_nIdObj);
			ASSERT(poStorage);
			poStorage->_undo_setfield(poUndoFC->m_nFldNr,poUndoFC->m_oValueSOV);
		}
		break;
		case CNEO_undoitem__::it_newobject:
		{
			CNEO_undonewobject * poUndoNO = dynamic_cast<CNEO_undonewobject *>(m_oUndoItemArray[iter].Get());
			ASSERT(poUndoNO);
			m_roTrans._remove_from_local_storage_map(poUndoNO->m_nTypeId,poUndoNO->m_nIdObj);
		}
		break;
		case CNEO_undoitem__::it_markdel:
		{
			CNEO_undomarkdel * poUndoMD = dynamic_cast<CNEO_undomarkdel *>(m_oUndoItemArray[iter].Get());
			ASSERT(poUndoMD);
			CNEO_storage * poStorage = m_roTrans._search_local_storage_map(poUndoMD->m_nTypeId,poUndoMD->m_nIdObj);
			ASSERT(poStorage);
			poStorage->_set_mark_del(poUndoMD->m_bOldState);
		}
		break;
		case CNEO_undoitem__::it_listoper:
		{
			CNEO_undolistoper * poUndoLO = dynamic_cast<CNEO_undolistoper *>(m_oUndoItemArray[iter].Get());
			ASSERT(poUndoLO);
			CNEO_liststorage * poListStorage = 
				m_roTrans._search_local_liststorage_map(poUndoLO->m_nCollectionId,poUndoLO->m_nIdParent);
			ASSERT(poListStorage);
			poListStorage->undo_operation(poUndoLO->m_nOuterIndex,poUndoLO->m_nIdChild);
		}
		break;
		case CNEO_undoitem__::it_writelock:
		{
			CNEO_undowritelock * poUndoWL =  dynamic_cast<CNEO_undowritelock *>(m_oUndoItemArray[iter].Get());
			ASSERT(poUndoWL);
			m_roTrans.release_write_lock(poUndoWL->m_nClass,poUndoWL->m_nTypeId,poUndoWL->m_nIdObj,poUndoWL->m_nExtra);
			bAnyWriteLock = true;
		}
		break;
		default:
			ASSERT(false);
		}
	}
	if(bAnyWriteLock)
	{
		m_roTrans.flush_pending_unlocks();
	}
}
