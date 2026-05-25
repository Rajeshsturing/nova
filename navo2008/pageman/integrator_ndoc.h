/*
	NAVO Enterprise 2008 (c)

	24.07.2002
	
	class:
		cndoc_integrator

	integruje podsystemy, trzyma connection do serwera itd
*/

#ifndef _INTEGRATOR_NDOC_H_
#define _INTEGRATOR_NDOC_H_

class cndoc_application;
class CNavoObjectCoordinator;
class CNEO_trans;
class CDefinitionManager;
class CPageCacheManagerUser;
class cndoc_pagestack;
class cndoc_page__;
class CClientInfoArray;
class cndoc_config_user_pref;

class cndoc_integrator : public CCmdTargetInterface
{
public:
	cndoc_integrator(cndoc_application * poApplication);
	~cndoc_integrator();
	bool initialize(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void process_first_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	bool process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void finalize_ui();
	void done();

	const CString & get_server_name() const;
	const CString & get_app_name() const;
	const CString & get_full_cache_name() const;
	SCP<CDefinitionManager> get_definition_manager();
	SCP<IDispatch> get_AFC();
	SCP<IDispatch> get_NX();
	SCP<IDispatch> get_NXMNet();
	SCP<cndoc_pagestack> get_toolbar_stack();
	SCP<cndoc_pagestack> get_outlookbar_stack();
	cndoc_application * get_application();
	CNEO_trans * get_current_transaction();

	SCP<cndoc_page__> create_page(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	SCP<cndoc_page__> create_module(long IdFile);

	//--------- page stacks ----------------------------
	SCP<cndoc_pagestack> _get_active_stack();
	bool _is_any_stack() const;
	void on_stack_finished(cndoc_pagestack * poStack);
	void activate_stack(cndoc_pagestack * poStack);

	void pop_active_page();
	//---------------------------------------------------
	void set_main_arena_backcolor(long nColor);

	SCP<CPageCacheManagerUser> get_pcmu(long IdFile,SCP<CPropertyProvider__> & rpoHLISP);
	SCP<IStream> get_raw_app_file(long IdFile);
	SCP <CHyperLinkInfo> GetCommonEnvironmentHLI();

	bool on_action_results(ned_action_result & roActionResults,cned_arena * poSrcArena);
	void on_new_error(SCP<CHyperLinkInfo> & rpoCommandHLISP);
#ifdef PULL_ERROR_MESSAGES
	void on_new_error(const CNavoErrorInfo & roNavoErrorInfo);
#endif

	void update_ui_now();

	void put_control_data_action(long idControl,const CString & roStringData);
	void put_control_cmd_action(long idControl,long nVerb,const CSmartOleVariant & roValueSOV);
	void process_control_data_action();

	void yield();
	void exit_yield();
	bool on_idle();

	void mark_quitting()
	{
		m_bQuitting = true;
	}
	const long generate_page_iid();

	void set_current_style(const CSmartOleVariant & roSOV);
	void apply_settings(const cndoc_config_user_pref & roCUP);
	bool is_UI() const;
	//------------------------------------------------------- counted resources ----------
	bool fwd_create_counted_resource(LPCTSTR lpResName,long nMaxUsage);
	bool fwd_delete_counted_resource(LPCTSTR lpResName);
	long fwd_use_counted_resource(LPCTSTR lpResName);
	long fwd_get_usage_counted_resource(LPCTSTR lpResName);
	void fwd_release_counted_resource(LPCTSTR lpResName);
	//------------------------------------------------------------------------------------
	//------------------------------------------------------- net user functions ---------
	long netuser_getcookie() const;
	long netuser_getinfo(long nIter,VARIANT * pUserName,VARIANT * pComputerName);
	void netuser_notify(long nUserCookie,long nEventCode,const VARIANT & roValue);
	void netuser_setprop(long nUserCookie,long nProp,const VARIANT & roValue);
	bool netuser_getprop(long nUserCookie,long nProp,VARIANT * pValue);
	//------------------------------------------------------------------------------------
	void update_bars();
	bool is_command_enabled(long IdCommand);
	//------------------------------------------------------------------------------------
	long font_desc_to_index(const ned_font_spec & roFontSpec);
	//---------------------------------------------------
	bool backup(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,SCP<IStream> poDestStreamSP);
	bool restore(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,SCP<IStream> poSrcStreamSP);
	//------------------------------------------------------------------------------------
	void _initialize_toolbar();
	void _initialize_outlookbar();
	void _uninitialize_outlookbar();
	void _uninitialize_toolbar();

	bool __on_app_start(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void __on_app_exit();

	bool _pre_translate_message(MSG & roMsg);

	LPUNKNOWN get_new_enum_AUTO();

	BEGIN_INTERFACE_PART(NotificationSink,INotificationSink)
		STDMETHOD(OnSharedVariableChange)(long /*lVarNr*/,VARIANT /*varNewValue*/)
		{
			METHOD_PROLOGUE(cndoc_integrator, NotificationSink)
			ASSERT(false);	//nie u¿ywane
			return S_OK;
		}
		STDMETHOD(OnNotifyUser)(long nOriginatorCookie,long lEvenCode,VARIANT * pDataVariant)
		{
			METHOD_PROLOGUE(cndoc_integrator, NotificationSink)
			
			pThis->_on_user_notify(nOriginatorCookie,lEvenCode,pDataVariant);
			return S_OK;
		}
		STDMETHOD(OnProgress)(long /*nInfoType*/,long /*lAdvance*/,long /*lTotal*/,LPSTR /*lpDescription*/)
		{
			METHOD_PROLOGUE(cndoc_integrator, NotificationSink)
			ASSERT(false);	//nie u¿ywane
			return S_OK;
		}
	END_INTERFACE_PART(NotificationSink)

	BEGIN_INTERFACE_PART(PingClient,IPingClient)		//ping client for navodb
	STDMETHOD(Ping)()
	{
		return S_OK;
	}
	END_INTERFACE_PART(PingClient)
	
	DECLARE_INTERFACE_MAP()
private:
	bool _process_page_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void _process_user_notify_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void _process_arena_click(SCP<CHyperLinkInfo> & rpoCommandHLISP);

	SCP<cndoc_page__> _find_page_on_iid(long nIID);

	long __check_upgrade();

	void _init_AFC(long nEngineType);
	void _done_AFC();

	void _init_NX();
	void _done_NX();

	void _on_user_notify(long nOriginatorCookie,long lEvenCode,VARIANT * pDataVariant);
	void _initialize_standard_ui();

	void _mark_update_views(bool bOnlyMain);
	void _perform_update_views(bool bForce);

	void __check_memory_state();
	//--------- page stacks ----------------------------
	SCP<cndoc_pagestack> _create_new_stack();
	//---------------------------------------------------
	void _store_late_switch_to_trans_for_top_page();
	void _make_late_switch_to_trans();

	CNEO_trans * m_poLateSwitchToTrans;

	void _pop_all_not_modal_pages();
	//toolbar and outlookbar 'stacks'

	cndoc_application * m_poApplication;

	SCP<IDispatch>				m_poAFCDispatchSP;
	SCP<IDispatch>				m_poNXDispatchSP;
	
	SCP<IDispatch>				m_poNXMNetDispatchSP;


	SCP<CNavoObjectCoordinator>	m_poNavoObjCoorSP;
	
	//for marshalling
	SCP<IGlobalInterfaceTable>	m_poGITSP;

	//main server connection
	SCP<IServerClient>			m_poServerClientSP;

	//app provider
	SCP<IAppDBManager>			m_poAppDBManagerSP;
	DWORD m_dwAppDBManager_GIT_Cookie;

	//local cache
	SCP<ICachedData>			m_poCachedDataSP;
	long						m_nCachedData_PingCookie;
	DWORD m_dwCachedData_GIT_Cookie;

	SCP<IPreprocessedDataCache>	m_poPreprocessedDataCacheSP;
	DWORD m_dwPreprocessedDataCache_GIT_Cookie;

	//notifications
	SCP<INotificationManager>	m_poNotificationManagerSP;
	long						m_nNotification_Cookie;

	SCP<CDefinitionManager>		m_poDefinitionManagerSP;

	CString						m_oServerString;
	CString						m_oAppNameString;
	CString						m_oCacheFullNameString;

	//page stacks
	SCP<cndoc_pagestack>		m_poToolbarStackSP;
	SCP<cndoc_pagestack>		m_poOutlookBarStackSP;
	CEnumerableArray< SCP<cndoc_pagestack>, SCP<cndoc_pagestack> & > m_oAppStackArray;
	CClientInfoArray			m_oCachedNetUserInfoArray;

	//arenas
	SCP<cned_arena_integrator>  m_poArenaIntegratorSP;
	SCP<cned_arena>				m_poToolbarArenaSP;
	SCP<cned_arena>				m_poOutlookBarArenaSP;
	SCP<cned_arena>				m_poMainArenaSP;
	long						m_nPage_IID;
	bool						m_bUI;
	bool						m_bQuitting;
	CNavoLog					m_oLog;
	DWORD						m_dwLastUpdateMainView;
	DWORD						m_dwLastUpdateOtherView;

	//put control data - cached values
	CArray< SCP<CHyperLinkInfo>, SCP<CHyperLinkInfo> &>	m_oPCVHyperLinkArray;

	friend class cndoc_control_command_processor;
};

inline const CString & cndoc_integrator::get_server_name() const
{
	//ASSERT(!m_oServerString.IsEmpty());
	return m_oServerString;
}

inline const CString & cndoc_integrator::get_app_name() const
{
	ASSERT(!m_oAppNameString.IsEmpty());
	return m_oAppNameString;
}

inline const CString & cndoc_integrator::get_full_cache_name() const
{
	ASSERT(!m_oCacheFullNameString.IsEmpty());
	return m_oCacheFullNameString;
}


inline SCP<IDispatch> cndoc_integrator::get_AFC()
{
	return m_poAFCDispatchSP;
}

inline SCP<IDispatch> cndoc_integrator::get_NX()
{
	return m_poNXDispatchSP;
}
inline SCP<IDispatch> cndoc_integrator::get_NXMNet()
{
	return m_poNXMNetDispatchSP;
}
inline cndoc_application * cndoc_integrator::get_application()
{
	return m_poApplication;
}

inline SCP<cndoc_pagestack> cndoc_integrator::get_toolbar_stack()
{
	return m_poToolbarStackSP;
}

inline SCP<cndoc_pagestack> cndoc_integrator::get_outlookbar_stack()
{
	return m_poOutlookBarStackSP;
}

inline bool cndoc_integrator::_is_any_stack() const
{
	return (m_oAppStackArray.GetSize() != 0);
}


inline const long cndoc_integrator::generate_page_iid()
{
	return ++m_nPage_IID;
}

inline bool cndoc_integrator::is_UI() const
{
	return m_bUI;
}

inline void cndoc_integrator::set_main_arena_backcolor(long nColor)
{
	if(m_poMainArenaSP.PointsObject())
	{
		m_poMainArenaSP->set_prop_backcolor(ng_color(COLORREF(nColor)));
		m_poMainArenaSP->set_prop_backcolor2(ng_color(COLORREF(nColor)));
	}
}

#else
	#error __FILE__ already included
#endif
