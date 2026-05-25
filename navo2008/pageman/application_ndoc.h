/*
	NAVO Enterprise 2008 (c)

	24.07.2002

	class:
		cndoc_application

		g³ówny obiekt (wewnêtrzny)
		odpowiadaj¹cy za pojedyñcz¹ sesjê

		cndoc_application integruje podsystemy
			- po³¹czenie z baz¹ danych (navoobj)
			- cache lokalny
			- okno OS (mainframe + client windows)
			
		ob³s³uguje komendy pochodz¹ce z messages i Automation (z wnêtrza aplikacji -
			ten sam thread, oraz z zewn¹trz - osobny thread, czekaj¹cy na wyniki)

		usage:
			1. create_application_thread()
			2. use by post_command or calling methods
			3. call quit(true/false) to stop thread

		NOTE: only way to stop thread is calling quit!!
*/

#ifndef _APPLICATION_NDOC_H_
#define _APPLICATION_NDOC_H_

class ng_session;
class cndoc_commandexecutor;
class cndoc_mainwindow;
class cndoc_integrator;
class cndoc_menumanager;
class cndoc_application;

namespace ned
{
	class ned_action_result;
	class cned_arena;
}

//specyficzny error storage, notyfikuj¹cy cndoc_application
class cndoc_application_ErrorStorage : public CGenericErrorStorage
{
public:
	cndoc_application_ErrorStorage():
		m_poApplication(NULL)
	{
	}
	void set_application(cndoc_application * poApplication)
	{
		m_poApplication = poApplication;
		if(m_poApplication != NULL)
		{
			OnNewError();
		}
	}
	virtual void OnNewError();
private:
	cndoc_application * m_poApplication;
};

class cndoc_application : public CNavoThread
{
public:
	static SCP<cndoc_application> create_application_thread(long idInstance);

	cndoc_application(bool bAsyncMode,long idInstance);
	~cndoc_application();
	void done();
	
	const long get_instance_id();

	virtual void OnFinalRelease();
	virtual int Run();
	virtual CNavoException & GetErrorStorage();

	void quit();
	long post_command(SCP<CHyperLinkInfo> poCommandHLISP,bool bWaitable);	//may be out of thread
	long post_command(LPCTSTR lpHLIString);
	void wait_command(long nCommandNumber);

	bool on_idle();

	void yield();
	void exit_yield();

	void update_ui_now();

	void wait_idle();

	void post_menu_command(ndoc_menuid nMenuId);
	bool is_menu_command_enabled(ndoc_menuid nMenuId);

	bool is_command_enabled(long IdCommand);
	cndoc_mainwindow * get_main_window();

	bool on_action_results(ned::ned_action_result & roActionResults,ned::cned_arena * poSrcArena);
	void on_programmable_timer_event();
	void on_new_error();

	bool is_async_mode() const;
	bool is_notify_idle() const;
	void set_notify_idle();

	bool is_UI() const;

	void set_exit_code(int nExitCode);

	bool _pre_translate_message(MSG & roMsg);

	//{{AFX_DISPATCH(cndoc_application)
	afx_msg LPDISPATCH CreateHLIAUTO();
	afx_msg LPDISPATCH CreateHLIOnStringAUTO(LPCTSTR lpHyperLinkString);
	afx_msg void fwd_PostCommandStringAUTO(LPCTSTR lpHyperLinkString);
	afx_msg void fwd_CallCommandStringAUTO(LPCTSTR lpHyperLinkString);
	afx_msg void fwd_PostCommandStringIIDAUTO(LPCTSTR lpHyperLinkString,long nPageIID);
	afx_msg long fwd_Font2InxAUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike);
	afx_msg long fwd_Font2Inx_v2_AUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike, BOOL bUnderLine,long nCharSet);
	afx_msg LPDISPATCH fwd_GetDefinitionManagerAUTO();
	afx_msg VARIANT fwd_GetRawAppFileAUTO(long IdFile);
	afx_msg LPDISPATCH fwd_getmoduleAUTO(long IdPage);
	afx_msg LPDISPATCH fwd_getpagehliAUTO(const VARIANT FAR& newValue);
	afx_msg void fwd_PushPageAUTO(LPDISPATCH page);
	afx_msg void fwd_PopPageAUTO();
	afx_msg LPDISPATCH fwd_GetTopPageAUTO();
	afx_msg LPDISPATCH CreateStreamObjectAUTO();
	afx_msg LPDISPATCH CreateSystemObjectAUTO();
	afx_msg void SetMenuAUTO(const VARIANT FAR& varStreamOrURL);
	afx_msg LPDISPATCH GetCurrentMenuTreeAUTO();
	afx_msg long fwd_GetUserInfoAUTO(long iter, VARIANT FAR* pvarUserName, VARIANT FAR* pvarComputerName);
	afx_msg void fwd_NotifyUserAUTO(long nUserCookie, long nEventCode, const VARIANT FAR& varValue);
	afx_msg long fwd_GetUserCookieAUTO();
	afx_msg void fwd_SetUserPropertyAUTO(long nUserCookie,long nProp,const VARIANT FAR& varValue);
	afx_msg BOOL fwd_GetUserPropertyAUTO(long nUserCookie,long nProp,VARIANT FAR * pvarValue);
	afx_msg LPUNKNOWN fwd_GetNewEnumAUTO();
	afx_msg void fwd_SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg LPDISPATCH fwd_GetToolbarAUTO();
	afx_msg LPDISPATCH fwd_GetOutlookbarAUTO();
	afx_msg void SetTimerAUTO(long nTimerId,const VARIANT FAR& rvarHLI,long nInterval);
	afx_msg BOOL IsCommandEnabledAUTO(long nCmd);
	afx_msg LPDISPATCH CreatePerformingObjectAUTO(LPCTSTR lpText);
	afx_msg void BringWindowToTopAUTO();
	afx_msg void SetShellTrayStateAUTO(long nState,BOOL bFlash,LPCTSTR lpTip);

	afx_msg BOOL fwd_CreateCountedResourceAUTO(LPCTSTR lpResName, long nMaxUsage);
	afx_msg BOOL fwd_DeleteCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg long fwd_UseCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg long fwd_GetUsageCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg void fwd_ReleaseCountedResourceAUTO(LPCTSTR lpResName);

	afx_msg long fwd_GetZoomAUTO();
	afx_msg void fwd_SetZoomAUTO(long nNewZoom);
	afx_msg void fwd_PurgeLocalCachesAUTO();

	afx_msg LPDISPATCH fwd_GetAFC_AUTO();

	afx_msg void fwd_ShowHideOutlookBarAUTO(BOOL bShow);
	afx_msg void fwd_ShowHideToolBarAUTO(BOOL bShow);

	afx_msg void fwd_PutControlDataAUTO(long idControl,LPCTSTR lpDataString);
	afx_msg void fwd_PutControlCommandAUTO(long idControl,long nVerb,const VARIANT FAR& varValue);
	afx_msg void ApplyControlDataAUTO();
	afx_msg void WaitIdleAUTO();

	afx_msg BOOL fwd_GetMenuChangedFlagAUTO();
	afx_msg void fwd_SetMenuChangedFlagAUTO(BOOL bChanged);
	afx_msg void fwd_SetCurrentStyleAUTO(const VARIANT FAR& rvarStyle);

	afx_msg void ParseXML_AUTO(LPDISPATCH pSinkObject,const VARIANT FAR& rvarStream);
#ifdef PULL_ERROR_MESSAGES
	afx_msg long GetNewMessageFlagAUTO();
	afx_msg BOOL GetNewMessageAUTO(VARIANT FAR * pvaridMsg, VARIANT FAR* pvaridHelp, VARIANT FAR* pvarDescription);
	afx_msg void ClearNewMessageFlagAUTO();
#endif

	afx_msg BOOL fwd_BackupAUTO(LPCTSTR lpSAUser,LPCTSTR lpPwd,LPCTSTR lpArchivePwd,const VARIANT FAR& rvarStream);
	afx_msg BOOL fwd_RestoreAUTO(LPCTSTR lpSAUser,LPCTSTR lpPwd,LPCTSTR lpArchivePwd,const VARIANT FAR& rvarStream);

	afx_msg LPDISPATCH fwd_GetNX_AUTO();
	afx_msg LPDISPATCH fwd_GetNXMNet_AUTO();
	
	afx_msg void fwd_SetArenaBackColorAUTO(long nArenaBackColor);
	afx_msg	void MessageSink_AUTO(LPDISPATCH pSinkObject);

	//}}AFX_DISPATCH
	//{{AFX_MSG(cndoc_application)
	//}}AFX_MSG
	DECLARE_DISPATCH_MAP()
private:
	bool __init();
	void __go();
	void __done(bool bOK);

	void _initialize_ui(bool bVisible,const CString & roAppNameString,const CString & roServerNameString);
	void _finalize_ui();

	void _process_first_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void _process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);

	void _create_menu_on_xml_file(long IdFile);
	void _create_menu_on_stream(SCP<IStream> & rpoStreamSP);
	SCP<IDispatch> _get_current_menu_tree_automation_object();
	bool _get_menu_changed_flag() const;
	void _set_menu_changed_flag(bool bChanged);

	long __fwd_PostCommandString(LPCTSTR lpHyperLinkString,bool bWaitable);

	struct CProgrammableTimer : public CInterface__
	{
		CProgrammableTimer() :
			m_nTimerInterval(0),
			m_nTimerCountDown(0)
		{
		}
		long m_nTimerInterval;
		long m_nTimerCountDown;
		SCP<CHyperLinkInfo>	m_poHLISP;
	};
	CMap<long,long,SCP<CProgrammableTimer>,SCP<CProgrammableTimer> & > m_oTimerMap;

	CEvent	m_oEventWorking;
	CEvent	m_oEventFreeToExit;
	cndoc_application_ErrorStorage m_oAppErrorStorage;
	
	bool	m_bAsyncMode;
	bool	m_bNotifyIdle;
	
	SCP<cndoc_commandexecutor>	m_poCommandExecutorSP;
	SCP<cndoc_menumanager>		m_poMenuManagerSP;
	SCP<cndoc_integrator>		m_poIntegratorSP;
	cndoc_mainwindow *			m_poMainWindow;
	int							m_nExitCode;
	ng_session m_oGraphicSession;
	bool						m_bCallAppExit;
	long						m_idInstance;

#ifdef PULL_ERROR_MESSAGES
	long m_nNewErrorMessageLevel;
#endif

	void _add_message_external_sink(CNavoErrorInfo & roErrorInfo);

	SCP<IDispatch>				m_poMessageSinkDispatchSP;
	DISPID						m_dispid_message_sink;

	friend class cndoc_commandexecutor;
	friend class cndoc_control_command_processor;
};

class CDCGetReleaseHolder;
class ng_dc;
class cndoc_view__;

class cndoc_control_command_processor
{
public:
	cndoc_control_command_processor(cndoc_application * poApplication);
	~cndoc_control_command_processor();
	void process(SCP<CHyperLinkInfo> & rpoCommandSP);
private:
	cndoc_application * m_poApplication;
	cndoc_view__ * m_poView;
	CDCGetReleaseHolder * m_poDCHolder;
	ng_dc * m_poDC;
	bool	m_bUpdateView;
};

inline cndoc_mainwindow * cndoc_application::get_main_window()
{
	return m_poMainWindow;
}

inline bool cndoc_application::is_async_mode() const
{
	return m_bAsyncMode;
}

inline bool cndoc_application::is_notify_idle() const
{
	return m_bNotifyIdle;
}

inline void cndoc_application::set_notify_idle()
{
	m_bNotifyIdle = true;
}

inline void cndoc_application::done()
{
	__done(true);
}

inline void cndoc_application::set_exit_code(int nExitCode)
{
	m_nExitCode = nExitCode;
}

inline const long cndoc_application::get_instance_id()
{
	return m_idInstance;
}


#else
	#error __FILE__ already included
#endif