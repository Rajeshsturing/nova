/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_mainwindow
*/

#ifndef _MAINWINDOW_NDOC_H_
#define _MAINWINDOW_NDOC_H_

class cndoc_application;
class cndoc_view__;

enum eViewType
{
	vt_min			= 0,
	vt_toolbar		= 1,
	vt_main			= 2,
	vt_outlookbar	= 3,
	vt_max			= 4,
};

class cndoc_shelltray;

enum eShellTrayState
{
	st_idle = 0,
	st_new_message_1,
	st_new_message_2,
};

class cndoc_mainwindow : public CWnd, public cndoc_navoview_impl_container_
{
public:
	static cndoc_mainwindow * create_main_window(cndoc_application * poApplication,LPCTSTR lpCaption,bool bVisible);

	cndoc_mainwindow(cndoc_application * poApplication);
	~cndoc_mainwindow();
	void create(LPCTSTR lpCaption);
	void done();

	void suspend();

	void show_shell_tray(bool bShow);
	void set_shell_tray_state(eShellTrayState eNewState);
	void set_shell_tray_tip(const ng_string & roTipString);
	eShellTrayState get_shell_tray_state();

	void set_shell_tray_flash(bool bFlash);

	void on_view_final_release(cndoc_view__ * poView);

	SCP<cndoc_view__> get_create_view(eViewType eVT,SCP<cned_arena> poArenaSP);
	cndoc_application * get_application();

	virtual bool is_visible() const;
	virtual bool on_action_results(ned::ned_action_result & roActionResults,cned_arena * poSrcArena);

	bool on_idle();

	//{{AFX_MSG(cndoc_mainwindow)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnShellIconNotify(WPARAM, LPARAM);
	//}}AFX_MSG
	
	afx_msg void OnMenuCommand(UINT nID);
	afx_msg void OnUpdateMenuCommand(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();

private:
	void _align_children();

	cndoc_application * m_poApplication;
	
	cndoc_view__ * m_oViews[ vt_max ];
	cndoc_shelltray * m_poShellTray;
	bool m_bShellTrayFlash;

	CBrush	m_oBackgroundBrush;
};

inline cndoc_application * cndoc_mainwindow::get_application()
{
	ASSERT(m_poApplication != NULL);
	return m_poApplication;
}

inline bool cndoc_mainwindow::is_visible() const
{
	return (IsWindowVisible() != FALSE);
}

inline void cndoc_mainwindow::set_shell_tray_flash(bool bFlash)
{
	m_bShellTrayFlash = bFlash;
}

#else
	#error __FILE__ already included
#endif

