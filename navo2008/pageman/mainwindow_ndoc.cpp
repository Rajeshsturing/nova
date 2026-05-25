/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_mainwindow
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"
#include "application_ndoc.h"

extern HINSTANCE _h_PAGEMAN_Instance;

//------------------------------------------------------------------------
//------------------------------------------------------------------------

class cndoc_shelltray
{
public:
	cndoc_shelltray(HWND hWnd);
	~cndoc_shelltray();

	void set_state(eShellTrayState eNewState);
	void set_tip(const ng_string & roTipString);

	eShellTrayState get_state()
	{
		return m_eState;
	}
private:
	static long _icon_from_state(eShellTrayState State);

	NOTIFYICONDATA m_notifyicondata;
	HWND m_hWnd;
	eShellTrayState m_eState;
};

//------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(cndoc_mainwindow, CWnd)
	//{{AFX_MSG_MAP(cndoc_mainwindow)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_USER + 1214,OnShellIconNotify)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(MENU_CMD_INTERNAL_OFFSET,MENU_CMD_INTERNAL_OFFSET+1000,OnMenuCommand)
	ON_UPDATE_COMMAND_UI_RANGE(MENU_CMD_INTERNAL_OFFSET,MENU_CMD_INTERNAL_OFFSET+1000,OnUpdateMenuCommand)
END_MESSAGE_MAP()

cndoc_mainwindow * cndoc_mainwindow::create_main_window(cndoc_application * poApplication,LPCTSTR lpCaption,bool bVisible)
{
	cndoc_mainwindow * poMainWindow = new cndoc_mainwindow(poApplication);
	poMainWindow->create(lpCaption);
	if(bVisible)
	{
		//OS_API_CALL
		poMainWindow->ShowWindow(SW_SHOWMAXIMIZED);
		::SetWindowPos(poMainWindow->m_hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		poMainWindow->UpdateWindow();
	}
	else
	{
#ifdef _DEBUG
		poMainWindow->ShowWindow(SW_SHOWMINIMIZED);
#else
		poMainWindow->ShowWindow(SW_HIDE);
#endif
	}
	return poMainWindow;
}

cndoc_mainwindow::cndoc_mainwindow(cndoc_application * poApplication):
	m_poApplication(poApplication),
	m_poShellTray(NULL),
	m_bShellTrayFlash(false)
{
	memset(m_oViews,0,sizeof(m_oViews));
}

cndoc_mainwindow::~cndoc_mainwindow()
{
	delete m_poShellTray;
}

void cndoc_mainwindow::create(LPCTSTR lpCaption)
{
	VERIFY(CWnd::CreateEx(0,NULL,lpCaption,(WS_MAXIMIZE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN),
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL, 
		::LoadMenu(_h_PAGEMAN_Instance,MAKEINTRESOURCE(IDR_EMPTYMENU))
		));
}

BOOL cndoc_mainwindow::PreCreateWindow(CREATESTRUCT& cs)
{
	m_oBackgroundBrush.CreateSolidBrush(RGB(0xAB,0xBE,0xE6));
	//OS_API_CALL
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,
		HCURSOR(0),(HBRUSH)m_oBackgroundBrush,::LoadIcon(_h_PAGEMAN_Instance,MAKEINTRESOURCE(IDI_MAIN)));
	return CWnd::PreCreateWindow(cs);
}

void cndoc_mainwindow::done()
{
	if(m_oViews[ vt_main ] != NULL)
	{
		cndoc_view__ * poView = m_oViews[ vt_main ];
		m_oViews[ vt_main ] = NULL;
		poView->DestroyWindow();
	}
#ifdef _DEBUG
	for(long iter = 0; iter < sizeof(m_oViews) / sizeof(m_oViews[0]); iter++)
	{
		ASSERT(m_oViews[ iter ] == NULL);
	}
#endif
	
	delete m_poShellTray;
	m_poShellTray = NULL;

	CWnd::DestroyWindow();
}

void cndoc_mainwindow::PostNcDestroy()
{
	delete this;
}

void cndoc_mainwindow::on_view_final_release(cndoc_view__ * poView)
{
	for(eViewType eVT = vt_min; eVT < vt_max; eVT = eViewType(eVT+1))
	{
		if(m_oViews[ eVT ] == poView)
		{
			if(eVT != vt_main)
			{
				m_oViews[ eVT ] = NULL;
				poView->DestroyWindow();
				_align_children();
			}
			return;
		}
	}
	ASSERT(false); 
}

SCP<cndoc_view__> cndoc_mainwindow::get_create_view(eViewType eVT,SCP<cned_arena> poArenaSP)
{
	if(m_oViews[ eVT ] != NULL)
	{
		return NewSCP(m_oViews[ eVT ],true);
	}
	else
	{
		SCP<cndoc_view__> poViewSP = NewSCP(new cndoc_navoview(eVT,this,poArenaSP));
		poViewSP->create();
		m_oViews[ eVT ] = poViewSP;
		_align_children();

		poViewSP->ShowWindow(SW_SHOW);
		
		return poViewSP;
	}
}

void cndoc_mainwindow::_align_children()
{
	CRect oClientRect;
	GetClientRect(&oClientRect);
	CRect oToobarRect = oClientRect;
	oToobarRect.bottom = oToobarRect.top + 42;
	CRect oOutlookBarRect = oClientRect;
	
	if(m_oViews[ vt_toolbar ] != NULL)
	{
		oOutlookBarRect.top = oToobarRect.bottom + 1;
	}
	else
	{
		oOutlookBarRect.top = oClientRect.top;
	}

	oOutlookBarRect.right = oOutlookBarRect.left + 50;

	CRect oMainRect = oClientRect;

	if(m_oViews[ vt_toolbar ] != NULL)
	{
		oMainRect.top = oToobarRect.bottom + 1;
	}
	else
	{
		oMainRect.top = oClientRect.top;
	}
	if(m_oViews[ vt_outlookbar ] != NULL)
	{
		oMainRect.left = oOutlookBarRect.right + 1;
	}
	else
	{
		oMainRect.left = oClientRect.left;
	}

	if(m_oViews[ vt_toolbar ] != NULL)
	{
		m_oViews[ vt_toolbar ]->MoveWindow(&oToobarRect,TRUE);
	}
	if(m_oViews[ vt_outlookbar ] != NULL)
	{
		m_oViews[ vt_outlookbar ]->MoveWindow(&oOutlookBarRect,TRUE);
	}
	if(m_oViews[ vt_main ] != NULL)
	{
		m_oViews[ vt_main ]->MoveWindow(&oMainRect,TRUE);
		m_oViews[ vt_main ]->SetFocus();
	}
}

bool cndoc_mainwindow::on_idle()
{
	bool bResult = false;
	for(eViewType eVT = vt_min; eVT < vt_max; eVT = eViewType(eVT+1))
	{
		if(m_oViews[ eVT ] != NULL)
		{
			bool bViewResult = m_oViews[ eVT ]->on_idle();
			bResult = bResult || bViewResult;
		}
	}
	return bResult;
}

void cndoc_mainwindow::OnClose() 
{
	if(::AfxMessageBox("Czy zamkn¹æ program ?", MB_ICONQUESTION | MB_YESNO) != IDYES)
	{
		return;
	}
	//komenda wyœwietlaj¹ca okno z zapytaniem
	//true - bêdzie robi³ post CMD_QUIT
	//false - nic
	m_poApplication->quit();
}

int cndoc_mainwindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	::SetTimer(m_hWnd,APPLICATION_TIMER_ID,500,NULL);
	
	return 0;
}

void cndoc_mainwindow::OnSize(UINT nType, int cx, int cy) 
{
	if(nType == SIZE_MINIMIZED)
	{
		//suspend();
	}
	else
	{
		CWnd::OnSize(nType, cx, cy);
		_align_children();
	}
}

void cndoc_mainwindow::OnSetFocus(CWnd* /*pOldWnd*/) 
{
	if(m_oViews[ vt_main ] != NULL)
	{
		m_oViews[ vt_main ]->SetFocus();
	}
}

void cndoc_mainwindow::OnTimer(UINT nIDEvent) 
{
	ASSERT(APPLICATION_TIMER_ID == nIDEvent);

	{
		ASSERT(m_poApplication);
		m_poApplication->on_programmable_timer_event();
		
		if(m_bShellTrayFlash)
		{
			switch(get_shell_tray_state())
			{
			case st_new_message_1:
				set_shell_tray_state(st_new_message_2);
			break;
			case st_new_message_2:
				set_shell_tray_state(st_new_message_1);
			break;
			}
		}
	}
}

void cndoc_mainwindow::OnMenuCommand(UINT nID)
{
	ASSERT(m_poApplication);
	m_poApplication->post_menu_command(ndoc_menuid(nID - MENU_CMD_INTERNAL_OFFSET));
}

void cndoc_mainwindow::OnUpdateMenuCommand(CCmdUI* pCmdUI)
{
	ASSERT(m_poApplication);
	pCmdUI->Enable(m_poApplication->is_menu_command_enabled(pCmdUI->m_nID - MENU_CMD_INTERNAL_OFFSET));
}

bool cndoc_mainwindow::on_action_results(ned_action_result & roActionResults,cned_arena * poSrcArena)
{
	ASSERT(m_poApplication);
	
	if(roActionResults.is_processed())
	{
		return m_poApplication->on_action_results(roActionResults,poSrcArena);
	}
	return false;
}


void cndoc_mainwindow::OnDestroy() 
{
	::KillTimer(m_hWnd,APPLICATION_TIMER_ID);
	CWnd::OnDestroy();
}

void cndoc_mainwindow::suspend()
{
	//OS_API_CALL
	ShowWindow(SW_HIDE);

	show_shell_tray(true);
	set_shell_tray_flash(false);
	set_shell_tray_state(st_idle);
}

LRESULT cndoc_mainwindow::OnShellIconNotify(WPARAM wParam, LPARAM lParam)
{
	UINT nMsg = (UINT) lParam;
	if(nMsg == WM_RBUTTONDOWN || nMsg == WM_LBUTTONDBLCLK)
	{
		set_shell_tray_flash(false);
		show_shell_tray(false);
		
		//OS_API_CALL
		SetForegroundWindow();
		ShowWindow(SW_RESTORE);
		BringWindowToTop();
	}
	return 0;
}

void cndoc_mainwindow::show_shell_tray(bool bShow)
{
	if(bShow)
	{
		if(m_poShellTray != NULL)
		{
			return;
		}
		else
		{
			m_poShellTray = new cndoc_shelltray(m_hWnd);
		}
	}
	else
	{
		if(m_poShellTray == NULL)
		{
			return;
		}
		else
		{
			delete m_poShellTray;
			m_poShellTray = NULL;
		}
	}
}

void cndoc_mainwindow::set_shell_tray_state(eShellTrayState eNewState)
{
	if(m_poShellTray != NULL)
	{
		m_poShellTray->set_state(eNewState);
	}
}

void cndoc_mainwindow::set_shell_tray_tip(const ng_string & roTipString)
{
	if(m_poShellTray != NULL)
	{
		m_poShellTray->set_tip(roTipString);
	}
}

eShellTrayState cndoc_mainwindow::get_shell_tray_state()
{
	if(m_poShellTray != NULL)
	{
		return m_poShellTray->get_state();
	}
	else
	{
		return st_idle;
	}
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

long cndoc_shelltray::_icon_from_state(eShellTrayState State)
{
	switch(State)
	{
	case st_idle:
		return IDI_MAIN;
	case st_new_message_1:
		return IDI_ST_NEW_MSG_1;
	case st_new_message_2:
		return IDI_ST_NEW_MSG_2;
	default:
		ASSERT(false);
		return 0;
	}
}

cndoc_shelltray::cndoc_shelltray(HWND hWnd) :
	m_eState(st_idle),
	m_hWnd(hWnd)
{
	memset(&m_notifyicondata,0,sizeof(m_notifyicondata));
	m_notifyicondata.cbSize = sizeof(m_notifyicondata);
	m_notifyicondata.hWnd = m_hWnd;
	m_notifyicondata.uID = 1;
	m_notifyicondata.uCallbackMessage = WM_USER + 1214;
	m_notifyicondata.hIcon = ::LoadIcon(_h_PAGEMAN_Instance,MAKEINTRESOURCE(_icon_from_state(m_eState)));
	m_notifyicondata.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	
	_tcscpy(m_notifyicondata.szTip,_T("NAVO Enterprise 2023"));
	Shell_NotifyIcon(NIM_ADD,&m_notifyicondata);
}

cndoc_shelltray::~cndoc_shelltray()
{
	//delete shell tray icon
	m_notifyicondata.hWnd = m_hWnd;
	m_notifyicondata.uID = 1;
	m_notifyicondata.uFlags = 0;
	Shell_NotifyIcon(NIM_DELETE,&m_notifyicondata);
}

void cndoc_shelltray::set_state(eShellTrayState eNewState)
{
	if(m_eState == eNewState)
	{
		return;
	}
	m_eState = eNewState;
	m_notifyicondata.hIcon = ::LoadIcon(_h_PAGEMAN_Instance,MAKEINTRESOURCE(_icon_from_state(m_eState)));
	m_notifyicondata.uFlags = NIF_ICON | NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY,&m_notifyicondata);
}

void cndoc_shelltray::set_tip(const ng_string & roTipString)
{
	_tcscpy(m_notifyicondata.szTip,roTipString.Left(sizeof(m_notifyicondata.szTip)/sizeof(m_notifyicondata.szTip[0]) - 1));
	m_notifyicondata.uFlags = NIF_ICON | NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY,&m_notifyicondata);
}
