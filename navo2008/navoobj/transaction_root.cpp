/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CTransactionRoot

*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "resource.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
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

#ifdef _DEBUG
long debug_counter = 0;
#endif

CNEO_thread::CNEO_thread(CNavoObjectCoordinator * poCoordinator,
						 CNavoException & roErrorStorage,
						 SCP<CHyperLinkInfo> & rpoInitialEnvHLISP):
	m_poCoordinator(poCoordinator),
	m_roErrorStorage(roErrorStorage),
	m_poCurrentTransaction(NULL),
	m_nPerformingTransLevel(0),
	m_poEnvironmentHLISP(NewSCP(new CHyperLinkInfo())),
	m_bAutoRollBack(true)
{
	(*m_poEnvironmentHLISP) = (*rpoInitialEnvHLISP);

	m_oFiredTriggersMap.InitHashTable( 2111 );
}

CNEO_thread::~CNEO_thread()
{
}

SCP<CNEO_trans> CNEO_thread::CreateSubTransaction()
{
	return NewSCP(new CNEO_trans(m_poCoordinator,m_roErrorStorage,
		true,NULL,NewSCP(this,true),m_poEnvironmentHLISP, SCP<IDispatch>()));
}

void CNEO_thread::SetCurrentTransaction(CNEO_trans * poCurrentTransaction)
{
	//autoswitch to auto sub trans if exists
	//neo_todo: to nie bêdzie potrzebne,
	//jeœli nie bêdziemy dostawaæ nieprawid³owych poleceñ z pageman::CTaskSwitchHoldera
	//który jest z kolei sterowany z CPage__ (pamiêtana jest "g³ówna" transakcja" 
	//a o autosub nic nie wiadomo

	if(poCurrentTransaction != NULL)
	{
		if(poCurrentTransaction->m_poAutoSubTransSP.PointsObject())
		{
			poCurrentTransaction = poCurrentTransaction->m_poAutoSubTransSP.Get();
		}
	}
	m_poCurrentTransaction = poCurrentTransaction;
	m_poCoordinator->SetCurrentTrans(poCurrentTransaction);
}



void CNEO_thread::begin_transaction()
{
	m_nPerformingTransLevel++;
}

void CNEO_thread::end_transaction()
{
	m_nPerformingTransLevel--;
	ASSERT(m_nPerformingTransLevel >= 0);
	if(m_nPerformingTransLevel == 0)
	{
		clean_transaction();
	}
}

eTriggerFiredPhase CNEO_thread::was_trigger_fired(long nTypeId,long nIdObj) const
{
	hyper hyperId = longlong(nTypeId,nIdObj);
	eTriggerFiredPhase eTFP;
	if(m_oFiredTriggersMap.Lookup(hyperId,eTFP))
	{
		ASSERT(eTFP != tfp_notfired);
		return eTFP;
	}
	return tfp_notfired;
}

void CNEO_thread::mark_trigger_firingnow(long nTypeId,long nIdObj)
{
	ASSERT(m_nPerformingTransLevel > 0);

	m_oFiredTriggersMap[ longlong(nTypeId,nIdObj) ] = tfp_firingnow;
}

void CNEO_thread::mark_trigger_fired(long nTypeId,long nIdObj)
{
	ASSERT(m_nPerformingTransLevel > 0);

	m_oFiredTriggersMap[ longlong(nTypeId,nIdObj) ] = tfp_fired;
}

CString CNEO_thread::write2storage(bool bWithCommit, LPCTSTR lpExtras)
{
#ifdef _DEBUG
	CDebugTimeMeter oDTM("CNEO_thread::write2storage");
#endif
	if(!bWithCommit)
	{
		if(m_oBlobData.GetSize() == 0)
		{
			if(m_poFlatDataSP.PointsNull())
			{
				return "+";	//nie ma nic
			}
			if(m_poFlatDataSP->GetDataLen() == 0)
			{
				return "+";	//nie ma nic
			}
		}
	}

	//jeœli jest jakiœ rekord
	//lub
	//jakiœ plik
	//lub
	//nie commited zmiany
	ASSERT(m_poCoordinator->GetDBAccess());
	if(m_poFlatDataSP.PointsNull())
	{
		m_poFlatDataSP = NewSCP(new CFlatData());	//niestety musimy zrobiæ pusty obiekt :(
	}

	CString strResult = m_poCoordinator->GetDBAccess()->MakeTransaction(*m_poFlatDataSP,
		m_oBlobData.GetSize(),m_oBlobData.GetData(),
		0,NULL,
		bWithCommit, lpExtras);

	//wyczyœæ flat/blobdata po zapisie
	m_poFlatDataSP = 0;
	m_oBlobData.RemoveAll();

	return strResult;
}
	
void CNEO_thread::clean_transaction()
{
	m_poFlatDataSP = 0;
	m_oBlobData.RemoveAll();

	m_oFiredTriggersMap.RemoveAll();
}
































