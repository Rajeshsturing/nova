/*
	NAVO Enterprise 2008 (c)

	24.07.2002

	class:
		cndoc_application

		g³ówny obiekt (wewnêtrzny)
		odpowiadaj¹cy za pojedyñcz¹ sesjê
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\internal_h1000.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoobj\treedataprov.h"
#include "..\navoscript\CacheManagerUser.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "common_pageman.h"

#include "cmdexec_ndoc.h"
#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"
#include "menumanager_ndoc.h"
#include "xmlpagecachemu.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cndoc_application::cndoc_application(bool bAsyncMode, long idInstance) :
	CNavoThread(CNavoOleInitHolder::APARTMENT),
	m_oEventWorking(FALSE, TRUE),
	m_oEventFreeToExit(FALSE, TRUE),
	m_poMainWindow(NULL),
	m_bAsyncMode(bAsyncMode),
	m_bNotifyIdle(false),
	m_bCallAppExit(false),
	m_idInstance(idInstance),
	m_nExitCode(0)
#ifdef PULL_ERROR_MESSAGES
	, m_nNewErrorMessageLevel(0)
#endif
{
	EnableAutomation();

	if (!m_bAsyncMode)
	{
		__init();
	}
#ifdef _DEBUG
	{
		int nOldFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		//		nOldFlags |= _CRTDBG_CHECK_ALWAYS_DF;
		_CrtSetDbgFlag(nOldFlags);
	}
#endif

	m_dispid_message_sink = DISPID_NONE;
}

cndoc_application::~cndoc_application()
{
}

SCP<cndoc_application> cndoc_application::create_application_thread(long idInstance)
{
	ASSERT(idInstance != 0);
	SCP<cndoc_application> poAppThreadSP = NewSCP(new cndoc_application(true, idInstance));
	CEvent & roEventWorking = poAppThreadSP->m_oEventWorking;
	poAppThreadSP->ResumeThread();

	CSingleLock oSLock(&roEventWorking, TRUE);
	return poAppThreadSP;
}

void cndoc_application::OnFinalRelease()
{
	ASSERT(m_bAutoDelete);
	//do nothing - will delete on OS thread exit (cause CWinThread.m_bAutoDelete)
	if (!m_bAsyncMode)
	{
		__done(true);
		delete this;
	}
}

int cndoc_application::Run()
{
	set_exit_code(0);
	ALL_TRY
	{
		if (__init())
		{
			__go();
			__done(true);
		}
		else
		{
			__done(false);
			set_exit_code(-1);
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		m_oAppErrorStorage.set_application(NULL);
		GetErrorStorage() += roNavoException;

		CString strMessage(roNavoException.BuildCompleteErrorString());

		if (strMessage.Find("CORE.E019") >= 0)
		{
			::ShellExecute(NULL, "open", "https://www.nxm.com.pl/", NULL, NULL, SW_SHOWNORMAL);
		}
		else
		{
			AfxMessageBox(strMessage);
		}

		__done(false);
		set_exit_code(-1);
	}

	return m_nExitCode;
}

CNavoException & cndoc_application::GetErrorStorage()
{
	return m_oAppErrorStorage;
}

void cndoc_application::yield()
{
	ASSERT(m_poCommandExecutorSP.PointsObject());
	m_poCommandExecutorSP->yield();
}

void cndoc_application::exit_yield()
{
	ASSERT(m_poCommandExecutorSP.PointsObject());
	m_poCommandExecutorSP->exit_yield();
}

void cndoc_application::update_ui_now()
{
	ASSERT(m_poCommandExecutorSP.PointsObject());

	m_poCommandExecutorSP->_message_loop();
	m_poCommandExecutorSP->_on_new_command();
	if (m_poMainWindow != NULL)
	{
		m_poMainWindow->on_idle();
	}
	m_poCommandExecutorSP->_message_loop();
}

void cndoc_application::quit()	//may be out of thread
{
	m_oTimerMap.RemoveAll();//wy³¹cz timery

	ASSERT(m_poCommandExecutorSP.PointsObject());
	ASSERT(m_poIntegratorSP.PointsObject());

	//zaznacz ¿e wychodzimy
	m_poCommandExecutorSP->mark_quitting();
	m_poIntegratorSP->mark_quitting();

	//wyrzuæ go z bie¿¹cej pêtli
	m_poCommandExecutorSP->exit_yield();

	//zaznacz ¿e teraz mo¿na ju¿ robiæ __done()
	m_oEventFreeToExit.SetEvent();
}

//---------- initialization --------------------
bool cndoc_application::__init()
{
	m_oGraphicSession.init();
	m_poIntegratorSP = NewSCP(new cndoc_integrator(this));
	m_poCommandExecutorSP = NewSCP(new cndoc_commandexecutor(this));
	m_poMenuManagerSP = NewSCP(new cndoc_menumanager());

	m_oEventWorking.SetEvent();
	m_oAppErrorStorage.set_application(this);
	return true;
}

//---------- main loop -------------------------
void cndoc_application::__go()
{
	yield();
}

//---------- cleanup ----------------------------

void cndoc_application::__done(bool bOK)
{
	bool bUI = is_UI();

	if (m_poIntegratorSP.PointsObject() && bOK && m_bCallAppExit)
	{
		m_poIntegratorSP->__on_app_exit();
	}
	m_oAppErrorStorage.set_application(NULL);
	m_oEventWorking.ResetEvent();
	_finalize_ui();

	//zaczekaj a¿ Ci zezwol¹ kasowaæ podsystemy - chyba ¿e siê wali
	if (bOK && m_bAsyncMode)
	{
		CSingleLock oSLock(&m_oEventFreeToExit, TRUE);
	}

	m_poCommandExecutorSP = 0;
	m_poMenuManagerSP = 0;

	if (m_poIntegratorSP.PointsObject())
	{
		m_poIntegratorSP->done();
		m_poIntegratorSP = 0;
	}
	m_oGraphicSession.done();

	//wypisz niewypisane b³êdy
	CNavoExceptionAccessor oNEAH(m_oAppErrorStorage);
	if (oNEAH.ErrorInfoArray().GetSize() > 0)
	{
		//to_do: wypisz b³êdy w lepszy sposób
		if (bUI)
		{
			AfxMessageBox(m_oAppErrorStorage.BuildCompleteErrorString());
		}
		oNEAH.ErrorInfoArray().RemoveAll();
	}
}


long cndoc_application::post_command(LPCTSTR lpHLIString)
{
	return post_command(ReadHLIFromString(lpHLIString), false);
}

long cndoc_application::post_command(SCP<CHyperLinkInfo> poCommandHLISP, bool bWaitable)
{
	ASSERT(m_poCommandExecutorSP.PointsObject());
	return m_poCommandExecutorSP->post_command(poCommandHLISP, bWaitable);
}

void cndoc_application::wait_command(long nCommandNumber)
{
	ASSERT(m_poCommandExecutorSP.PointsObject());
	m_poCommandExecutorSP->wait_command(nCommandNumber);
}

void cndoc_application::wait_idle()
{
	ASSERT(m_poCommandExecutorSP.PointsObject());
	m_poCommandExecutorSP->wait_idle();
}

void cndoc_application::_initialize_ui(bool bVisible, const CString & roAppNameString, const CString & roServerNameString)
{
	if (m_poMainWindow == NULL)
	{
		CString oCaptionString, oAppTitleString;
		oAppTitleString.LoadString(AFX_IDS_APP_TITLE);
		oCaptionString.Format(IDS_APPFROMSERVER, oAppTitleString, GetNAVO2001EngineVersion(),
			roAppNameString, roServerNameString);
#ifdef _DEVELOPER_EDITION_
		oCaptionString += " Developer Edition - !!NOT REDISTRIBUTABLE!!";
#endif
		m_poMainWindow = cndoc_mainwindow::create_main_window(this, oCaptionString, bVisible);
		ASSERT(m_poMainWindow != NULL);
	}
}

void cndoc_application::_finalize_ui()
{
	if (m_poIntegratorSP.PointsObject())
	{
		m_poIntegratorSP->finalize_ui();
	}
	if (m_poMainWindow != NULL)
	{
		m_poMainWindow->done();
		m_poMainWindow = NULL;
	}
}

void cndoc_application::_process_first_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	//1. get basic connection information
	//-------------------------------------

	//to_do: when missing display connect dialog

	//get Application name
	CString oAppNameString = rpoCommandHLISP->GetStrProp(GVAR_APPLICATION);
	//get or compose server name
	CString oServerString;
	if (!rpoCommandHLISP->SafeGetStrProp(GVAR_DBSERVER, oServerString))
	{
		SCP<CHyperLinkInfo> poEnvHLISP = GetSystemEnvironmentHLI();
		rpoCommandHLISP->SetStrProp(GVAR_DBSERVER, poEnvHLISP->GetStrProp(GVAR_MACHINE));
		oServerString = poEnvHLISP->GetStrProp(GVAR_MACHINE);
	}

	//get UI value
	long nUserInterface = 1;
	rpoCommandHLISP->SafeGetNumProp(GVAR_UISTYLE, nUserInterface);

	//2. display main window and splash
	//-------------------------------------

	_initialize_ui((nUserInterface != 0), oAppNameString, oServerString);


	//3. start connecting to servers
	//-------------------------------------
	if (!m_poIntegratorSP->initialize(rpoCommandHLISP))
	{
		quit();
		return;
	}
	//4. set application menu
	_create_menu_on_xml_file(IDPAGE_MENU);

	if (!m_poIntegratorSP->__on_app_start(rpoCommandHLISP))
	{
		quit();
		return;
	}

	m_bCallAppExit = true;

	m_poIntegratorSP->process_first_command(rpoCommandHLISP);

}

void cndoc_application::_process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	ASSERT(m_poIntegratorSP.PointsObject());
	m_poIntegratorSP->process_command(rpoCommandHLISP);
}

bool cndoc_application::on_idle()
{
	bool bResult = false;
	if (m_poIntegratorSP.PointsObject())
	{
		bool bIntResult = m_poIntegratorSP->on_idle();
		bResult = bResult || bIntResult;
	}
	if (m_poMainWindow != NULL)
	{
		bool bMainWindowResult = m_poMainWindow->on_idle();
		bResult = bResult || bMainWindowResult;
	}
	return bResult;
}

bool cndoc_application::is_command_enabled(long IdCommand)
{
	//zawsze wolno otwieraæ
	ASSERT(IdCommand != CMD_OPEN_MODULE_PAGE);
	if (IdCommand >= CMD_OPEN_STATIC_PAGE && IdCommand <= CMD_OPEN_WIZARD_PAGE)
	{
		return true;
	}

	//zawsze mo¿na wyjœæ
	if (IdCommand == CMD_QUIT)
	{
		return true;
	}

	if (m_poIntegratorSP.PointsObject())
	{
		return m_poIntegratorSP->is_command_enabled(IdCommand);
	}
	return false;
}





void cndoc_application::_create_menu_on_xml_file(long IdFile)
{
	ASSERT(m_poIntegratorSP.PointsObject());

	SCP<CPageCacheManagerUser> poPCMUSP = m_poIntegratorSP->get_pcmu(IdFile,
		NewSCP<CPropertyProvider__>(m_poIntegratorSP->GetCommonEnvironmentHLI().Get(), true));

	CCacheUserHolder oCUH(poPCMUSP);
	_create_menu_on_stream(oCUH.get_stream());
	oCUH.OK();
}

void cndoc_application::_create_menu_on_stream(SCP<IStream> & rpoStreamSP)
{
	ASSERT(m_poMainWindow);
	//OS_API_CALL
	HMENU hTopMenu = ::GetMenu(m_poMainWindow->m_hWnd);
	ASSERT(hTopMenu != HMENU(NULL));
	ASSERT(m_poMenuManagerSP.PointsObject());
	m_poMenuManagerSP->create_menu_on_stream(rpoStreamSP, hTopMenu);
	m_poMainWindow->DrawMenuBar();
}

SCP<IDispatch> cndoc_application::_get_current_menu_tree_automation_object()
{
	if (m_poMenuManagerSP.PointsObject())
	{
		return m_poMenuManagerSP->get_automation_object();
	}
	else
	{
		return SCP<IDispatch>();
	}
}

bool cndoc_application::_get_menu_changed_flag() const
{
	ASSERT(m_poMenuManagerSP.PointsObject());
	return m_poMenuManagerSP->get_menu_changed_flag();
}

void cndoc_application::_set_menu_changed_flag(bool bChanged)
{
	ASSERT(m_poMenuManagerSP.PointsObject());
	m_poMenuManagerSP->set_menu_changed_flag(bChanged);
}

void cndoc_application::post_menu_command(ndoc_menuid nMenuId)
{
	ASSERT(m_poMenuManagerSP.PointsObject());
	ASSERT(m_poMenuManagerSP->get_command(nMenuId).PointsObject());

	post_command(m_poMenuManagerSP->get_command(nMenuId), false);
}

bool cndoc_application::is_menu_command_enabled(ndoc_menuid nMenuId)
{
	ASSERT(m_poMenuManagerSP.PointsObject());
	ASSERT(m_poMenuManagerSP->get_command(nMenuId).PointsObject());
	long IdCommand = m_poMenuManagerSP->get_command(nMenuId)->GetNumProp(GVAR_CMD);
	return is_command_enabled(IdCommand);
}

bool cndoc_application::on_action_results(ned_action_result & roActionResults, cned_arena * poSrcArena)
{
	ASSERT(roActionResults.is_processed());
	ASSERT(m_poIntegratorSP.PointsObject());

	bool bResult = m_poIntegratorSP->on_action_results(roActionResults, poSrcArena);

	for (long Index = 0; roActionResults.get_info(Index).PointsObject(); Index++)
	{
		//jeœli komenda
		if (roActionResults.get_info(Index)->get_type() == eit_command)
		{
			ned_event_command * poEventCommand = dynamic_cast<ned_event_command *>(roActionResults.get_info(Index).Get());
			ASSERT(poEventCommand != NULL);
			ASSERT(poEventCommand->get_command().PointsObject());

			//uzupe³nij komendê o id kontrolki generujacej komendê
			poEventCommand->get_command()->SetNumProp(PROPC_CONTROL, poEventCommand->get_firing_element());

			//komendy typu CMD_CONTROL nie s¹ postowane, lecz przetwarzane specjalnie
			if (poEventCommand->get_command()->PropertyExists(GVAR_CMD))
			{
				if (poEventCommand->get_command()->GetNumProp(GVAR_CMD) == CMD_CONTROL)
				{
					cndoc_control_command_processor oCCP(this);
					oCCP.process(poEventCommand->get_command());
					continue;
				}
			}
			post_command(poEventCommand->get_command(), false);
		}
	}
	return bResult;
}

#define ENGINE_ERROR_FIRST		1001
#define APP_WARNING_FIRST		4000
#define APP_WARNING_LAST		4999

void cndoc_application::on_new_error()
{
	CNavoExceptionAccessor oNEA(GetErrorStorage());
#ifdef PULL_ERROR_MESSAGES
	if (oNEA.ErrorInfoArray().GetUpperBound() >= 0)
	{
		CNavoErrorInfo & roNavoErrorInfo = oNEA.ErrorInfoArray()[oNEA.ErrorInfoArray().GetUpperBound()];

		if (roNavoErrorInfo.GetErroCode() > ENGINE_ERROR_FIRST &&
			roNavoErrorInfo.GetErroCode() < APP_WARNING_FIRST)
		{
			m_nNewErrorMessageLevel = 2;
		}
		else
		{
			m_nNewErrorMessageLevel = max(m_nNewErrorMessageLevel, 1);
		}
		if (m_poIntegratorSP.PointsObject())
		{
			m_poIntegratorSP->on_new_error(roNavoErrorInfo);
		}
		while (oNEA.ErrorInfoArray().GetSize() > 50)
		{
			oNEA.ErrorInfoArray().RemoveAt(0);
		}

		if (m_poMessageSinkDispatchSP.PointsObject())
		{
			_add_message_external_sink(roNavoErrorInfo);
		}
	}
#else
	for (long iter = oNEA.ErrorInfoArray().GetUpperBound(); iter >= 0; iter--)
	{
		CNavoErrorInfo & roNavoErrorInfo = oNEA.ErrorInfoArray()[iter];

		SCP <CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
		poHLISP->SetNumProp(GVAR_CMD, CMD_INTERNAL_NEW_ERROR);

		poHLISP->SetNumProp(INTERNALVAR_NEWERROR_ERRORCODE, roNavoErrorInfo.GetErroCode());
		poHLISP->SetNumProp(INTERNALVAR_NEWERROR_HELPID, roNavoErrorInfo.GetHelpId());
		poHLISP->SetStrProp(INTERNALVAR_NEWERROR_ERRORSTR, roNavoErrorInfo.GetErrorString());
		post_command(poHLISP, false);
	}
	oNEA.ErrorInfoArray().RemoveAll();
#endif
}

bool cndoc_application::is_UI() const
{
	if (m_poIntegratorSP.PointsObject())
	{
		return m_poIntegratorSP->is_UI();
	}
	return false;
}

///----------------------------------------------------------
bool cndoc_application::_pre_translate_message(MSG & roMsg)
{
	if (m_poIntegratorSP.PointsObject())
	{
		return m_poIntegratorSP->_pre_translate_message(roMsg);
	}
	return false;
}

void cndoc_application::on_programmable_timer_event()
{
	POSITION pos = m_oTimerMap.GetStartPosition();
	while (pos)
	{
		long nTimerId;
		SCP<CProgrammableTimer> poProgTimerSP;
		m_oTimerMap.GetNextAssoc(pos, nTimerId, poProgTimerSP);
		poProgTimerSP->m_nTimerCountDown--;
		ASSERT(poProgTimerSP->m_nTimerCountDown >= 0);
		if (poProgTimerSP->m_nTimerCountDown == 0)
		{
			ASSERT(poProgTimerSP->m_poHLISP.PointsObject());
			post_command(poProgTimerSP->m_poHLISP, false);
			poProgTimerSP->m_nTimerCountDown = poProgTimerSP->m_nTimerInterval;
		}
	}
}

cndoc_control_command_processor::cndoc_control_command_processor(cndoc_application * poApplication) :
	m_poApplication(poApplication),
	m_poDCHolder(NULL),
	m_poDC(NULL),
	m_poView(NULL),
	m_bUpdateView(false)
{
	ASSERT(m_poApplication);
	if (m_poApplication->is_UI())
	{
		m_poView = m_poApplication->get_main_window()->get_create_view(vt_main, m_poApplication->m_poIntegratorSP->m_poMainArenaSP);
		m_poDCHolder = new CDCGetReleaseHolder(m_poView->m_hWnd);
	}
	else
	{
		//OS_API_CALL
		m_poDCHolder = new CDCGetReleaseHolder(::GetDesktopWindow());
	}
	m_poDC = new ng_dc(m_poDCHolder->get_hdc());
}

cndoc_control_command_processor::~cndoc_control_command_processor()
{
	if (m_poView != NULL && m_bUpdateView)
	{
		m_poView->update();
	}
	delete m_poDC;
	delete m_poDCHolder;
}

void cndoc_control_command_processor::process(SCP<CHyperLinkInfo> & rpoCommandSP)
{
	ASSERT(m_poApplication);
	ASSERT(m_poDC);
	ned_action_command oCtrlCmdAction(*m_poDC, ned_ident(rpoCommandSP->GetNumProp(PROPC_IDENT)),
		eStdControlCommandVerb(rpoCommandSP->GetNumProp(GVAR_CONTROL_VERB_INTERNAL)), rpoCommandSP);
	ned_action_result oResult;
	m_poApplication->m_poIntegratorSP->m_poMainArenaSP->on_event_command(oCtrlCmdAction, oResult);

	if (oResult.is_processed())
	{
		m_poApplication->on_action_results(oResult, m_poApplication->m_poIntegratorSP->m_poMainArenaSP.Get());
		m_bUpdateView = true;
	}
}

///----------------------------------------------------------
///----------- application error storage --------------------
///----------------------------------------------------------

void cndoc_application_ErrorStorage::OnNewError()
{
	if (m_poApplication != NULL)
	{
		m_poApplication->on_new_error();
	}
}

void cndoc_application::_add_message_external_sink(CNavoErrorInfo & roErrorInfo)
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

