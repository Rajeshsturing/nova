/*
	NAVO Sp. z o.o. (2002)
	24.07.2002

	NAVO Enterprise

	class:
		cndoc_page__ - abstrakcyjna "strona" bazowa
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navothread.h"		//navo thread
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navogal\ngal_iface.h"		//graphics

#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"

#include "common_pageman.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cndoc_page__::cndoc_page__(
	cndoc_pagestack * poPageStack,
	cndoc_integrator * poIntegrator,SCP <CHyperLinkInfo> & rpoOpeningHLISP,
		SCP<CNEO_trans> & rpoTransactionSP) :
	m_poPageStack(poPageStack),
	m_poIntegrator(poIntegrator),
	m_poOpeningHLISP(rpoOpeningHLISP),
	m_poTransactionSP(rpoTransactionSP),
	m_nIID(poIntegrator->generate_page_iid()),
	m_nInModal(0),
	m_nModalResult(0)
{
	ASSERT(m_poPageStack);
	ASSERT(m_poIntegrator);
	ASSERT(m_poOpeningHLISP.PointsObject());
	EnableAutomation();
	m_poPageStack->on_page_attach();
}

cndoc_page__::~cndoc_page__()
{
	ASSERT(m_poPageStack != NULL);
	m_poTransactionSP = 0;		
	
	// transaction = 0 this must be before on_page_detach
	// cause on_page_detach can call on_stack_finished
	// which have to switch transaction
	// but transaction dtor also can switch

	m_poPageStack->on_page_detach();
}

SCP<CNEO_trans> cndoc_page__::get_transaction()
{
	return m_poTransactionSP;
}

CNavoException & cndoc_page__::GetErrorStorage()
{
	ASSERT(m_poIntegrator != NULL);
	return m_poIntegrator->get_application()->GetErrorStorage();
}

bool cndoc_page__::on_action_results(ned_action_result & roActionResults)
{
	ASSERT(roActionResults.is_processed());
	long Index = 0;
	while(roActionResults.get_info(Index).PointsObject())
	{
		//do komendy dodaj PAGE_IID jeœli nie ma
		if(roActionResults.get_info(Index)->get_type() == eit_command)
		{
			ned_event_command * poEventCommand = dynamic_cast<ned_event_command *>(roActionResults.get_info(Index).Get());

			ASSERT(poEventCommand != NULL);
			ASSERT(poEventCommand->get_command().PointsObject());

			if(!poEventCommand->get_command()->PropertyExists(GVAR_PAGE_IID))
			{
				poEventCommand->get_command()->SetNumProp(GVAR_PAGE_IID,get_iid());
			}
		}

		Index++;
	}
	return false;
}

long cndoc_page__::_do_modal(bool bAutoPop)
{
	cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(),get_transaction());

	m_nModalResult = 0;

	if(bAutoPop)
	{
		ASSERT(get_stack() != NULL);
		ASSERT(get_integrator()->_is_any_stack());
		ASSERT(get_integrator()->_get_active_stack().Get() == get_stack());

		//jeœli nie jest na wierzchu - zrób push
		bool bPush = get_stack()->is_empty();
		if(!bPush)
		{
			bPush = (get_stack()->get_top_page().Get() != this);
		}
		if(bPush)
		{
			get_stack()->push(NewSCP(this,true));
		}
	}
again_:
	{
		CIncDecHolder<long> oInsideModalHolder(m_nInModal);
		get_integrator()->yield();
	}
	if(bAutoPop)
	{
		ASSERT(get_stack() != NULL);
		ASSERT(get_integrator()->_is_any_stack());
		ASSERT(get_integrator()->_get_active_stack().Get() == get_stack());
		/*
			to_do: sprawdzaæ czy strona zgadza siê aby zrobiæ jej pop (fclose musi zwróciæ true)
			if(!canpop())
			{
				goto again_;
			}
		*/
		get_stack()->pop();
	}
	return m_nModalResult;
}

bool cndoc_page__::process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	long nCommand;
	if(rpoCommandHLISP->SafeGetNumProp(GVAR_CMD,nCommand))
	{
		if(nCommand == CMD_INTERNAL_ACTIVATE)
		{
			ActivateAUTO();
			return true;
		}
	}
	return false;
}


//-------------------------------------------------------------------------------------
//
//	transaction switch holder
//
//-------------------------------------------------------------------------------------

cndoc_transaction_switch_holder::cndoc_transaction_switch_holder(CNEO_trans * poCurrentTrans,CNEO_trans * poNewTrans):
	m_poOldTransaction(poCurrentTrans)
{
	if(poNewTrans != NULL)
	{
		poNewTrans->get_thread()->SetCurrentTransaction(poNewTrans);
	}
}

cndoc_transaction_switch_holder::~cndoc_transaction_switch_holder()
{
	if(m_poOldTransaction != NULL)
	{
		m_poOldTransaction->get_thread()->SetCurrentTransaction(m_poOldTransaction);
	}
}

