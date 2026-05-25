/*
	NAVO Enterprise 2008 (c)

	24.07.2002
	
	class:
		cndoc_integrator

	integruje podsystemy, trzyma connection do serwera itd
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\internal_h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\progressgadget.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"
#include "..\navoobj\cursorcollection.h"

#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\group_helper_ned.h"
#include "..\navoui\paragraph_ned.h"
#include "..\navoui\page_caption_ned.h"
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\page_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"

#include "common_pageman.h"

#include "navopage_ndoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cndoc_integrator::_initialize_toolbar()
{
	//create arena
	if(m_poToolbarArenaSP.PointsNull())
	{
		m_poToolbarArenaSP = m_poArenaIntegratorSP->create_arena();
		m_poToolbarArenaSP->set_providers(get_full_cache_name(),m_poGITSP,m_dwAppDBManager_GIT_Cookie,m_dwCachedData_GIT_Cookie);
	}
	
	if(m_poToolbarStackSP.PointsObject())
	{
		return;
	}
	//create stack
	m_poToolbarStackSP = NewSCP(new cndoc_pagestack(this,m_poToolbarArenaSP));

	//prepare command
	SCP<CHyperLinkInfo> poOpeningHLISP = NewSCP(new CHyperLinkInfo());
	poOpeningHLISP->SetNumProp(GVAR_CMD,CMD_OPEN_STATIC_PAGE);
	poOpeningHLISP->SetNumProp(GVAR_DESTPAGE,IDPAGE_TOOLBAR);

	//create page
	SCP<cndoc_navopage> poToolPageSP = NewSCP<cndoc_navopage>(new cndoc_navopage(m_poToolbarStackSP,
		this,poOpeningHLISP,SCP<CNEO_trans>(),m_poToolbarArenaSP->create_window()));
	VERIFY(poToolPageSP->prepare());


	//force size (and ignore supplied in XML)
	SCP<cned_element> poTopPageElementSP = poToolPageSP->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE);
	poTopPageElementSP->set_prop_extwidth(NED_MAX_WIDTH);
	poTopPageElementSP->set_prop_extheight(NED_MAX_HEIGHT);
	cast_ui<cned_page>(poTopPageElementSP.Get())->set_prop_extmargins(ng_rect(0,0,0,0));
	cast_ui<cned_page>(poTopPageElementSP.Get())->set_prop_display_mode(pdm_maximized);

	//create view
	ASSERT(m_poApplication->get_main_window());
	SCP<cndoc_view__> poToolbarViewSP = m_poApplication->get_main_window()->get_create_view(vt_toolbar,m_poToolbarArenaSP);
	ASSERT(poToolbarViewSP.PointsObject());
	//attach
	m_poToolbarStackSP->attach_view(poToolbarViewSP);
	
	//push page on stack - which in turn updates view
	ASSERT(poToolPageSP->get_stack() == m_poToolbarStackSP.Get());
	m_poToolbarStackSP->push(NewSCP<cndoc_page__>(poToolPageSP.Get(),true));
	m_poToolbarStackSP->update_view();
}

void cndoc_integrator::_initialize_outlookbar()
{
	if(m_poOutlookBarArenaSP.PointsNull())
	{
		//create arena
		m_poOutlookBarArenaSP = m_poArenaIntegratorSP->create_arena();
		m_poOutlookBarArenaSP->set_providers(get_full_cache_name(),m_poGITSP,m_dwAppDBManager_GIT_Cookie,m_dwCachedData_GIT_Cookie);			
	}
	if(m_poOutlookBarStackSP.PointsObject())
	{
		return;
	}
	//create stack
	m_poOutlookBarStackSP = NewSCP(new cndoc_pagestack(this,m_poOutlookBarArenaSP));

	//prepare command
	SCP<CHyperLinkInfo> poOpeningHLISP = NewSCP(new CHyperLinkInfo());
	poOpeningHLISP->SetNumProp(GVAR_CMD,CMD_OPEN_STATIC_PAGE);
	poOpeningHLISP->SetNumProp(GVAR_DESTPAGE,IDPAGE_APPTREE);

	SCP<cndoc_navopage> poOutlookBarPageSP = NewSCP<cndoc_navopage>(new cndoc_navopage(m_poOutlookBarStackSP,
		this,poOpeningHLISP,SCP<CNEO_trans>(),m_poOutlookBarArenaSP->create_window()));
	VERIFY(poOutlookBarPageSP->prepare());

	//force size (and ignore supplied in XML)

	SCP<cned_element> poTopPageElementSP = poOutlookBarPageSP->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE);
	poTopPageElementSP->set_prop_extwidth(NED_MAX_WIDTH);
	poTopPageElementSP->set_prop_extheight(NED_MAX_HEIGHT);
	cast_ui<cned_page>(poTopPageElementSP.Get())->set_prop_extmargins(ng_rect(0,0,0,0));
	cast_ui<cned_page>(poTopPageElementSP.Get())->set_prop_display_mode(pdm_maximized);

	//create view
	ASSERT(m_poApplication->get_main_window());
	SCP<cndoc_view__> poOutlookbarViewSP = m_poApplication->get_main_window()->get_create_view(vt_outlookbar,m_poOutlookBarArenaSP);
	ASSERT(poOutlookbarViewSP.PointsObject());
	//attach
	m_poOutlookBarStackSP->attach_view(poOutlookbarViewSP);
	
	//push page on stack - which in turn updates view
	ASSERT(poOutlookBarPageSP->get_stack() == m_poOutlookBarStackSP.Get());
	m_poOutlookBarStackSP->push(NewSCP<cndoc_page__>(poOutlookBarPageSP.Get(),true));
	m_poOutlookBarStackSP->update_view();
}

void cndoc_integrator::_initialize_standard_ui()
{
// jeœli silnik ma sam pocz¹tkowo pokazywaæ toolbar i outlookbar
// to nale¿y odkomentowaæ poni¿sze linie

//	_initialize_toolbar();
//	_initialize_outlookbar();
}

void cndoc_integrator::finalize_ui()
{
	_pop_all_not_modal_pages();
	//ASSERT(!_is_any_stack());	//all MUST be non modal at this moment

	//clean 'build-in' user interface
	_uninitialize_outlookbar();
	_uninitialize_toolbar();
}

void cndoc_integrator::_uninitialize_outlookbar()
{
	if(m_poOutlookBarStackSP.PointsObject())
	{
		if(!m_poOutlookBarStackSP->is_empty())
		{
			m_poOutlookBarStackSP->pop();
		}
	}
}

void cndoc_integrator::_uninitialize_toolbar()
{
	if(m_poToolbarStackSP.PointsObject())
	{
		if(!m_poToolbarStackSP->is_empty())
		{
			m_poToolbarStackSP->pop();
		}
	}
}

void cndoc_integrator::process_first_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	//get UI value
	rpoCommandHLISP->SetNumProp(GVAR_NEWTHREAD,1);	//supply new thread flag for first cmd
	process_command(rpoCommandHLISP);

}

/*
	g³ówny procesor komend
*/

bool cndoc_integrator::process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	bool bProcessed = false;

	ALL_TRY
	{
		ASSERT(rpoCommandHLISP.PointsObject());

		long nCommand = 0;

		if(rpoCommandHLISP->SafeGetNumProp(GVAR_CMD,nCommand))
		{
			switch(nCommand)
			{
			case CMD_QUIT:
				{
					m_poApplication->quit();
					bProcessed = true;
				}
			break;
			case CMD_OPEN_STATIC_PAGE:
			case CMD_OPEN_RECORD_PAGE:
			case CMD_OPEN_OLEDOC_PAGE:
			case CMD_OPEN_WIZARD_PAGE:
			{
				SCP<cndoc_page__> poPageSP = create_page(rpoCommandHLISP);
				if(poPageSP.PointsObject())
				{
					ASSERT(_get_active_stack().PointsObject());
					//raczej nie powinien siê zmieniæ - chcemy wiedzieæ jakby co
					ASSERT(_get_active_stack().Get() == poPageSP->get_stack());
					ASSERT(poPageSP->get_stack() != NULL);
					//ale i tak rób push na stos przypisany do strony
					poPageSP->get_stack()->push(poPageSP);
				}
				bProcessed = true;
			}
			break;
			case CMD_OPEN_MODULE_PAGE:
				ASSERT(false);	//who calls it
				;
			case CMD_SUSPEND:
			{
				get_application()->get_main_window()->suspend();
				bProcessed = true;
			}
			break;
			case CMD_INTERNAL_USER_NOTIFY:
			{
				_process_user_notify_command(rpoCommandHLISP);
				bProcessed = true;
			}
			break;
			case CMD_INTERNAL_ARENA_CLICK:
			{
				_process_arena_click(rpoCommandHLISP);
				bProcessed = true;
			}
			break;
			case CMD_INTERNAL_APPLYCTRLDATA:
			{
				process_control_data_action();
				bProcessed = true;
			}
			break;
			case CMD_INTERNAL_NEW_ERROR:
			{
				on_new_error(rpoCommandHLISP);
			}
			break;
			default:
				bProcessed = _process_page_command(rpoCommandHLISP);
			}
		}
		else
		{
			bProcessed = _process_page_command(rpoCommandHLISP);
		}
	
		_make_late_switch_to_trans();
		
		if(m_bQuitting)
		{
			//wyczyœæ co siê da i wyjdŸ
			_pop_all_not_modal_pages();
		}
		else
		{
			if(bProcessed)
			{
				_mark_update_views(false);
			}
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		m_poApplication->GetErrorStorage() += roNavoException;
		//to_do: ??
	}
	return bProcessed;
}

/*
	procesor komend przeznaczonych dla stron i stosów stron
*/
bool cndoc_integrator::_process_page_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	SCP<cndoc_page__> poTargetPageSP;
	long nTargetIID;
	if(rpoCommandHLISP->SafeGetNumProp(GVAR_PAGE_IID,nTargetIID))
	{
		if(ACTIVE_PAGE_IID != nTargetIID)
		{
			poTargetPageSP = _find_page_on_iid(nTargetIID);
			if(poTargetPageSP.PointsNull())
			{
				ASSERT(false);		//nie ma takiej strony - b³¹d programisty aplikacji
				return false;		//ingoruj komendê
			}
		}
	}
	if(poTargetPageSP.PointsNull())		//target -> strona aktywna
	{
		ASSERT(_is_any_stack());		//nie ma ¿adnego stacka - b³¹d programisty aplikacji
		if(!_is_any_stack())
		{
			return false;				//ignoruj
		}

		ASSERT(!_get_active_stack()->is_empty());	//aktywny stack jest pusty - b³¹d programisty aplikacji
		if(_get_active_stack()->is_empty())
		{
			return false;			//ignoruj
		}
		poTargetPageSP = _get_active_stack()->get_top_page();
	}
	ASSERT(poTargetPageSP.PointsObject());
	ASSERT(poTargetPageSP->get_stack() != NULL);
	
	return poTargetPageSP->get_stack()->process_command(poTargetPageSP,rpoCommandHLISP);
}


SCP<cndoc_pagestack> cndoc_integrator::_get_active_stack()
{
	ASSERT(_is_any_stack());
	return m_oAppStackArray[ m_oAppStackArray.GetUpperBound() ];
}

SCP<cndoc_pagestack> cndoc_integrator::_create_new_stack()
{
	ASSERT(m_poMainArenaSP.PointsObject());
	//utwórz nowy page stack
	SCP<cndoc_pagestack> poPageStackSP = NewSCP(new cndoc_pagestack(this,m_poMainArenaSP));
	m_oAppStackArray.Add(poPageStackSP);
	
	//jeli jest UI to pod³¹cz stack do g³ównego view
	if(m_bUI)
	{
		SCP<cndoc_view__> poMainViewSP = m_poApplication->get_main_window()->get_create_view(vt_main,m_poMainArenaSP);
		ASSERT(poMainViewSP.PointsObject());
		poPageStackSP->attach_view(poMainViewSP);
	}
	ASSERT(_get_active_stack() == poPageStackSP);
	return poPageStackSP;
}

void cndoc_integrator::on_stack_finished(cndoc_pagestack * poStack)
{
	for(long iter = 0; iter <= m_oAppStackArray.GetUpperBound(); iter++)
	{
		if(m_oAppStackArray[iter].Get() == poStack)
		{
			m_oAppStackArray.RemoveAt(iter);
			_store_late_switch_to_trans_for_top_page();
			return;
		}
	}
	
	if(m_poToolbarStackSP.Get() == poStack)
	{
		m_poToolbarStackSP = 0;
	}
	if(m_poOutlookBarStackSP.Get() == poStack)
	{
		m_poOutlookBarStackSP = 0;
	}
}

void cndoc_integrator::activate_stack(cndoc_pagestack * poStack)
{
	if(poStack == _get_active_stack().Get())
	{
		return;
	}
	
	_get_active_stack()->on_activate(false);

	for(long iter = 0; iter <= m_oAppStackArray.GetUpperBound(); iter++)
	{
		if(m_oAppStackArray[iter].Get() == poStack)
		{
			SCP<cndoc_pagestack> poHoldPageStackSP = m_oAppStackArray[iter];
			m_oAppStackArray.RemoveAt(iter);
			m_oAppStackArray.Add(poHoldPageStackSP);
			break;
		}
	}

	ASSERT(poStack == _get_active_stack().Get());

	_get_active_stack()->on_activate(true);

	_store_late_switch_to_trans_for_top_page();
}

void cndoc_integrator::_store_late_switch_to_trans_for_top_page()
{
	if(_is_any_stack())
	{
		ASSERT(_get_active_stack().PointsObject());
		ASSERT(!_get_active_stack()->is_empty());
		m_poLateSwitchToTrans = _get_active_stack()->get_thread()->GetCurrentTransaction();
	}
	else
	{
		m_poLateSwitchToTrans = NULL;
	}
}

void cndoc_integrator::_make_late_switch_to_trans()
{
	if(m_poLateSwitchToTrans != NULL)
	{
		m_poNavoObjCoorSP->SetCurrentTrans(m_poLateSwitchToTrans);
		m_poLateSwitchToTrans = NULL;
	}
}

SCP<cndoc_page__> cndoc_integrator::create_page(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	long nCommand = rpoCommandHLISP->GetNumProp(GVAR_CMD);

	SCP<CNEO_trans> poPageTransSP;
	SCP<cndoc_pagestack> poPageStackSP;

	bool bNewThread = rpoCommandHLISP->PropertyExists(GVAR_NEWTHREAD);
	
	/*
		utwórz nowy 'w¹tek' - stos stron oraz transaction thread
	*/
	if(!_is_any_stack() && !bNewThread)
	{

#ifdef _DEVELOPER_EDITION_
		AfxMessageBox("Komenda nie zawiera GVAR_NEWTHREAD a nie ma ¿adnego aktywnego stosu.\n"
			"GVAR_NEWTHREAD zostanie emulowane, ale za karê musisz nacisn¹æ OK");
#endif

		bNewThread = true;	//auto supply 
	}

	if(bNewThread)
	{
		poPageStackSP = _create_new_stack();
		SCP<CNEO_thread> poNewThreadSP = m_poNavoObjCoorSP->CreateNewThread();
		poPageStackSP->assign_thread(poNewThreadSP);
		//ASSERT(nCommand != CMD_OPEN_WIZARD_PAGE && nCommand != CMD_OPEN_MODULE_PAGE);
		poPageTransSP = poNewThreadSP->CreateSubTransaction();
		ASSERT(poPageTransSP.PointsObject());
	}
	else
	{
		//u¿yj aktywnego stosu
		poPageStackSP = _get_active_stack();
	}

	ASSERT(m_poMainArenaSP.PointsObject());
	ASSERT(poPageStackSP.PointsObject());

	//tworzenie strony
	SCP<cndoc_page__> poPageSP;
	switch(nCommand)
	{
	case CMD_OPEN_WIZARD_PAGE:
	case CMD_OPEN_MODULE_PAGE:
		
		//ASSERT(poPageTransSP.PointsNull());
		ASSERT(get_current_transaction());
		
		//u¿yj aktywnej transakcji
		poPageTransSP = NewSCP(get_current_transaction(),true);
		
		ASSERT(poPageTransSP.PointsObject());
		
		poPageSP = NewSCP<cndoc_page__>(new cndoc_navopage(poPageStackSP,this,rpoCommandHLISP,
			poPageTransSP,m_poMainArenaSP->create_window()));

	break;
	case CMD_OPEN_STATIC_PAGE:
	case CMD_OPEN_RECORD_PAGE:
		ASSERT(get_current_transaction());
		
		//utwórz podtransakcjê
		if(poPageTransSP.PointsNull())	//mo¿e nie byæ gdy jest "new thread"
		{
			poPageTransSP = get_current_transaction()->CreateSubTransaction(true);
		}
		ASSERT(poPageTransSP.PointsObject());
		
		poPageTransSP->ApplyEnvironment(rpoCommandHLISP);
		poPageSP = NewSCP<cndoc_page__>(new cndoc_navopage(poPageStackSP,this,rpoCommandHLISP,
			poPageTransSP,m_poMainArenaSP->create_window()));
	break;
	case CMD_OPEN_OLEDOC_PAGE:
		ASSERT(false);	//to_do
	break;
	default:
		ASSERT(false);
	}
	ASSERT(poPageSP.PointsObject());
	
	if(!poPageSP->prepare())
	{
		return SCP<cndoc_page__>();
	}
	else
	{
		//touch update - any non-zero value
		//must be low to be recognized as 'enough old'
		
		m_dwLastUpdateMainView = 1;

		return poPageSP;
	}
}

CNEO_trans * cndoc_integrator::get_current_transaction()
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->GetCurrentTrans();
}

SCP<cndoc_page__> cndoc_integrator::create_module(long IdFile)
{
	SCP<CHyperLinkInfo> poOpeningHLISP = NewSCP(new CHyperLinkInfo());
	poOpeningHLISP->SetNumProp(GVAR_CMD,CMD_OPEN_WIZARD_PAGE);
	poOpeningHLISP->SetNumProp(GVAR_DESTPAGE,IdFile);
	return create_page(poOpeningHLISP);
}

bool cndoc_integrator::on_action_results(ned_action_result & roActionResults,cned_arena * poSrcArena)
{
	ASSERT(roActionResults.is_processed());
	if(poSrcArena == m_poMainArenaSP.Get())
	{
		if(_is_any_stack())
		{
			if(_get_active_stack()->on_action_results(roActionResults))
			{
				_mark_update_views(true);
				return true;
			}
		}
	}
	else
	{
		if(poSrcArena == m_poOutlookBarArenaSP.Get())
		{
			if(m_poOutlookBarStackSP.PointsObject())
			{
				if(m_poOutlookBarStackSP->on_action_results(roActionResults))
				{
					return true;
				}
			}
		}
		else
		{
			if(poSrcArena == m_poToolbarArenaSP.Get())
			{
				if(m_poToolbarStackSP.PointsObject())
				{
					if(m_poToolbarStackSP->on_action_results(roActionResults))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool cndoc_integrator::is_command_enabled(long IdCommand)
{
	if(IdCommand == CMD_ZOOMIN || IdCommand == CMD_ZOOMOUT)
	{
		//to_do: sprawdziæ czy nie jesteœmy na granicy najwiêkszego/najmniejszego zoom'a
		return true;
	}
	if(_is_any_stack())
	{
		if(!_get_active_stack()->is_empty())
		{
			return _get_active_stack()->get_top_page()->is_command_enabled(IdCommand);
		}
	}
	return false;
}

#ifdef PULL_ERROR_MESSAGES

void cndoc_integrator::on_new_error(const CNavoErrorInfo & roNavoErrorInfo)
{
	if(m_oLog.IsHandleValid())
	{
		CString oLogString;
		oLogString.Format("[%d]\t%s",roNavoErrorInfo.GetErroCode(),
				roNavoErrorInfo.GetErrorString());
		m_oLog << oLogString;
	}
}

#endif

void cndoc_integrator::on_new_error(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	ASSERT(rpoCommandHLISP.PointsObject());

	if(m_oLog.IsHandleValid())
	{
		CString oLogString;
		oLogString.Format("[%d]\t%s",rpoCommandHLISP->GetNumProp(INTERNALVAR_NEWERROR_ERRORCODE),
			rpoCommandHLISP->GetStrProp(INTERNALVAR_NEWERROR_ERRORSTR));
		m_oLog << oLogString;
	}

	if(m_poMainArenaSP.PointsNull())	//jeszcze/ju¿ nie ma systemu okien
	{
		return;
	}
	if(m_poNavoObjCoorSP.PointsNull())	//nie ma jeszcze/ju¿ object coordinatora
	{
		return;
	}

	cndoc_transaction_switch_holder oSwitchToMeHolder(get_current_transaction(),get_current_transaction());

	SCP<cndoc_page__> poMessagePageSP = _find_page_on_iid(4);
	if(poMessagePageSP.PointsNull())
	{
		SCP <CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
		poHLISP->SetNumProp(GVAR_CMD,CMD_OPEN_STATIC_PAGE);
		poHLISP->SetNumProp(GVAR_DESTPAGE,IDPAGE_ERRORLOG);
		poHLISP->SetNumProp(GVAR_NEWTHREAD,1);
		poMessagePageSP = create_page(poHLISP);
		ASSERT(poMessagePageSP.PointsObject());
		
		//raczej nie powinien siê zmieniæ - chcemy wiedzieæ jakby co
		ASSERT(_get_active_stack().Get() == poMessagePageSP->get_stack());

		ASSERT(poMessagePageSP->get_stack() != NULL);
		//ale i tak rób push na stos przypisany do strony
		poMessagePageSP->get_stack()->push(poMessagePageSP);
	}
	cndoc_navopage * poMessagePage = dynamic_cast<cndoc_navopage *>(poMessagePageSP.Get());
	ASSERT(poMessagePage != NULL);
	
	rpoCommandHLISP->SetStrProp(GVAR_FUNCTIONHLI,"on_new_error");
	poMessagePage->process_command(rpoCommandHLISP);
	_mark_update_views(false);
}

void cndoc_integrator::_mark_update_views(bool bOnlyMain)
{
	if(m_dwLastUpdateMainView == 0)
	{
		m_dwLastUpdateMainView = ::GetTickCount();
	}
	
	if(!bOnlyMain)
	{
		if(m_dwLastUpdateOtherView == 0)
		{
			m_dwLastUpdateOtherView = ::GetTickCount();
		}
	}
}

static DWORD dwMainViewDelay =  350;
static DWORD dwOtherViewDelay = 750;

static DWORD _equalize_delay(DWORD dwDelay,DWORD dwMin,DWORD dwMax,DWORD dwLastTime)
{
	//wyliczanie œredniej wa¿onej (3 x ostatni czas) = 20% oraz  historia 4 ostatnich)

	DWORD dwResult = (dwDelay * 4 + (3 * dwLastTime)) / 5;
	dwResult = min(max(dwResult,dwMin),dwMax);
	return dwResult;
}

void cndoc_integrator::_perform_update_views(bool bForce)
{
	ALL_TRY
	{
		if(bForce || 
			(
			(m_dwLastUpdateMainView != 0) 
			&& 
			(m_dwLastUpdateMainView + dwMainViewDelay < ::GetTickCount())
			)
			)
		{
			TRACE("UPDATE MAIN\n");
			DWORD dwStartUpdate = ::GetTickCount();
			if(_is_any_stack())
			{
				_get_active_stack()->update_view();
			}
			else
			{
				ASSERT(m_poMainArenaSP.PointsObject());
				
				if(m_bUI)
				{
					get_application()->get_main_window()->get_create_view(vt_main,m_poMainArenaSP)->update();
				}
			}
			//not marked for update
			m_dwLastUpdateMainView = 0;
			dwMainViewDelay = _equalize_delay(dwMainViewDelay,5,150,::GetTickCount() - dwStartUpdate);
			
			TRACE("main delay=%d\n",dwMainViewDelay);
		}
		
		if(bForce ||
			(
			(m_dwLastUpdateOtherView != 0) 
			&&
			(m_dwLastUpdateOtherView + dwOtherViewDelay < ::GetTickCount())
			)
			)
		{
			TRACE("UPDATE BARS\n");
			
			update_bars();
			
			//not marked for update
			m_dwLastUpdateOtherView = 0;
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		m_poApplication->GetErrorStorage() += roNavoException;
	}
}

void cndoc_integrator::update_bars()
{
	if(m_poToolbarStackSP.PointsObject())
	{
		if(!m_poToolbarStackSP->is_empty())
		{
			CSmartOleVariant oActivePageSOV(LPDISPATCH(NULL),false);

			SCP<cndoc_page__> poToolbarPageSP = m_poToolbarStackSP->get_top_page();
			ASSERT(poToolbarPageSP.PointsObject());
			cndoc_navopage * poToolbarPage = dynamic_cast<cndoc_navopage *>(poToolbarPageSP.Get());
			ASSERT(poToolbarPage != NULL);
			
			if(_is_any_stack())
			{
				if(!_get_active_stack()->is_empty())
				{
					SCP<cndoc_page__> poActivePageSP = _get_active_stack()->get_top_page();
					ASSERT(poActivePageSP.PointsObject());
				
					oActivePageSOV = CSmartOleVariant(poActivePageSP->GetDispatch(true),false);
				}
			}

			//setup "page_"
			CInvokeForwarderHolder oPage_InvokeForwarderHolder(poToolbarPage->_get_page_disp_fwdr(),
				NewSCP((IDispatch*)&poToolbarPage->m_xDynaDispatch,true));

			poToolbarPage->get_window()->fire_user_command("update_toolbar",&oActivePageSOV,1,true);
			m_poToolbarStackSP->update_view();
		}
	}
	if(m_poOutlookBarStackSP.PointsObject())
	{
		m_poOutlookBarStackSP->update_view();
	}
}

void cndoc_integrator::_process_user_notify_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	SCP<cndoc_page__> poModuleSP = create_module(IDPAGE_SYSFUNCTIONLIB);
	SCP<IDispatch> pIPageDispatchSP = NewSCP(poModuleSP->GetDispatch(true),false);

	if(pIPageDispatchSP.PointsObject())
	{
		//function user_notification(nOrigCookie,nEventCode,varData)

		CSmartOleVariant oParamSOV[3];
		oParamSOV[2] = CSmartOleVariant(rpoCommandHLISP->GetNumProp(INTERNALVAR_USER_NOTIF_ORIG));
		oParamSOV[1] = CSmartOleVariant(rpoCommandHLISP->GetNumProp(INTERNALVAR_USER_NOTIF_EVENT));
		oParamSOV[0] = rpoCommandHLISP->GetProp(INTERNALVAR_USER_NOTIF_VALUE);
		DispatchInvoke(pIPageDispatchSP,
			DispatchGetIdOfName(pIPageDispatchSP,CString(_T("user_notification"))),
			oParamSOV,3,NULL,NULL);
	}
}

void cndoc_integrator::_process_arena_click(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	SCP<cndoc_page__> poModuleSP = create_module(IDPAGE_SYSFUNCTIONLIB);
	SCP<IDispatch> pIPageDispatchSP = NewSCP(poModuleSP->GetDispatch(true),false);

	if(pIPageDispatchSP.PointsObject())
	{
		//function arena_left_click(byval nButtonCode)

		CSmartOleVariant oParamSOV[1];
		oParamSOV[0] = rpoCommandHLISP->GetProp(INTERNALVAR_ARENA_CLICK_BUTTON);
		DispatchInvoke(pIPageDispatchSP,
			DispatchGetIdOfName(pIPageDispatchSP,CString(_T("arena_left_click"))),
			oParamSOV,1,NULL,NULL);
	}
}

void cndoc_integrator::put_control_data_action(long idControl,const CString & roStringData)
{
	SCP<CHyperLinkInfo> poCommandHLISP = NewSCP(new CHyperLinkInfo());
	poCommandHLISP->SetNumProp(PROPC_IDENT,idControl);
	poCommandHLISP->SetNumProp(GVAR_CONTROL_VERB_INTERNAL,long(sccv_paste_data));
	poCommandHLISP->SetStrProp(PROPC_VARIANT,roStringData);

	m_oPCVHyperLinkArray.Add(poCommandHLISP);
}

void cndoc_integrator::put_control_cmd_action(long idControl,long nVerb,const CSmartOleVariant & roValueSOV)
{
	SCP<CHyperLinkInfo> poCommandHLISP = NewSCP(new CHyperLinkInfo());
	poCommandHLISP->SetNumProp(PROPC_IDENT,idControl);
	poCommandHLISP->SetNumProp(GVAR_CONTROL_VERB_INTERNAL,nVerb);
	poCommandHLISP->SetProp(PROPC_VARIANT,roValueSOV);

	m_oPCVHyperLinkArray.Add(poCommandHLISP);
}

void cndoc_integrator::process_control_data_action()
{
	ASSERT(m_poMainArenaSP.PointsObject());

	cndoc_control_command_processor oCCP(get_application());

	for(long iter = 0; iter <= m_oPCVHyperLinkArray.GetUpperBound(); iter++)
	{
		oCCP.process(m_oPCVHyperLinkArray[iter]);
		//to_do: rezultat gdy dane nie zosta³y zaakceptowane
	}

	m_oPCVHyperLinkArray.RemoveAll();

}

void cndoc_integrator::pop_active_page()
{
	ASSERT(_is_any_stack());
	ASSERT(!_get_active_stack()->is_empty());
	_get_active_stack()->pop();
	_make_late_switch_to_trans();
}

