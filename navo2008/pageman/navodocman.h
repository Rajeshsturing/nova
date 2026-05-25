/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoDocMananager - zarz¹dza stronami i stosami stron (logiczny aspekt zagadnienia)
		CPageContextStack - stos stron
*/


#ifndef _NAVODOCMAN_H_
#define _NAVODOCMAN_H_

class CUserThread;
class CNavoDocMananager;
class CStyleAndFontProvider;
class CPage__;
class CUIPageManager;
class CParseUIThread;
class CPageCacheManagerUser;
struct CMiscProvidersData;
class CNEO_thread;
class CRepaintArea;
enum eMinMaxState;
class CToolbarNavoPage;
class CTransSwitchHolder;

class CPageStack : public CCmdTargetInterface
{
public:
	CPageStack(CNavoDocMananager * poNavoDocManager,SCP<CNEO_thread> & rpoTransactionRootSP);
	~CPageStack();

	void AddPageRef()
	{
		m_nPageRef++;
	}
	void ReleasePageRef()
	{
		m_nPageRef--;
		ASSERT(m_nPageRef >= 0);
		if(m_nPageRef == 0)
		{
			OnFinalPageRelease();
		}
	}

	CPage__ * GetTopPage();
	void PushPage(SCP<CPage__> & rpoPageSP);
	bool PopPage(bool bIgnoreFCloseResult);

	void GoBack(SCP <CHyperLinkInfoWithResult> & roHLISCP);

	SCP<CPage__> CreateAndPreparePage(SCP <CHyperLinkInfo> & rpoOpeningHLISP);

	void GetStackArea(CRepaintArea & roRepaintArea);
	void activate_itself();
	bool is_in_modal_loop() const;
	long _generate_page_iid();
	CPage__ * _get_page_from_iid(long nPageIID);

	SCP<CNEO_trans> GetTransaction();
	SCP<CNEO_trans> CreateSubTransaction();

	CNavoException & GetErrorStorage();

	bool PtInStack(const CPoint & roPoint);

	void on_activate(bool bActivate);
	bool is_command_enabled(long IdCommand);

	//umo¿liwia post komendy przez obiekt z "wnêtrza systemu"
	void fwd_post_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);

	void OnLayoutChange(CRepaintArea & roRepaintArea,bool bUpdateToolbar,long nSourceViewId);
	void GetMiscProviders(CMiscProvidersData & roMPD);
	LPDISPATCH GetDocumentDispatch();
	HDC GetViewHDC(CPage__ * poPage);

	SCP<CPageCacheManagerUser> get_pcmu(long IdFile,SCP<CPropertyProvider__> & rpoHLISP);
	SCP<CParseUIThread> create_parseui_thread(SCP<IStream> & rpoInputStreamSP,
		SCP<CUIPageManager> & rpoOutputPageManagerSP);

	SCP<CTransSwitchHolder> GetTransSwitchHolder(CNEO_trans * poTransaction);

	void process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP,CPage__ * poTargetPage);
	void yield(CPage__ * poPage);
	void update_view_immediate(CPage__ * poPage);

	//message forwardery
	bool OnKeyDown(CActionKBD & roActionKBD);
	void OnMouseClick(CActionMouse & roActionMouse);
	void OnMouseEndClick(CActionMouse & roActionMouse);
	void OnMouseMove(CActionMouse & roActionMouse);
	void OnTimeElapsed(CActionTimeElapsed & roActionTime,UINT nIdTimer);
	void raw_OnSizeChange(CDC & roDC,const CSize & roSize);
	bool raw_OnSetCursor(CPoint point);
	void OnOleControlEvent(CActionOleEvent & roActionOleEvent);

	void raw_OnPrepareDraw(CActionPaint & roActionPaint,bool bActiveStack);
	void raw_OnPerformDraw(CActionPaint & roActionPaint,CNAVORegion & roPaintedRgn,bool bActiveStack);

	void UndoAction(CAction__ & roAction,CArchive & roUndoArchive);

	//{{AFX_MSG(CPageStack)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CPageStack)
	afx_msg void PushPageAUTO(LPDISPATCH page);
	afx_msg void PopPageAUTO();
	afx_msg LPDISPATCH GetTopPageAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	void OnFinalPageRelease();
	void _change_mm_state_to(eMinMaxState eNewMMState);

	CNavoDocMananager *				m_poNavoDocManager;	//uplink
	SCP<CNEO_thread>			m_poTransactionRootSP;
	CEnhancedStack< SCP<CPage__> >	m_oPageStack;
	
	long m_nPageRef;	//licznik referencji ze stron
	bool m_bActive;		//czy jest aktywny
};


class CToolBarPageStack : public CPageStack
{
public:
	CToolBarPageStack(CNavoDocMananager * poNavoDocManager,
		SCP<CNEO_thread> & rpoTransactionRootSP);
};

//specyficzny error storage, notyfikuj¹cy NDM'a
class CNDM_ErrorStorage : public CGenericErrorStorage
{
public:
	CNDM_ErrorStorage(CNavoDocMananager * poNavoDocManager):
		m_poNavoDocManager(poNavoDocManager)
	{}
	virtual void OnNewError();
private:
	CNavoDocMananager * m_poNavoDocManager;
};

class CNavoDocMananager : public CCmdTargetInterface
{
public:
	CNavoDocMananager(CUserThread * poUserThread);
	~CNavoDocMananager();

	//page stack management
	CPageStack * create_new_page_stack();
	void on_page_stack_finished(CPageStack * poPageStack);
	CPageStack * get_active_page_stack();
	void activate_page_stack(CPageStack * poPageStackToBeActive);

	bool is_command_enabled(long IdCommand);
	//inicjowanie
	bool MiscelanousInit(const CString & roServerString,const CString & roAppNameString,
		const CString & roDBNameString,long nDBType);
	void MiscelanousDone();

	long _generate_page_iid()
	{
		return ++m_nPage_IID;
	}

    CNavoException & GetErrorStorage()
	{
		return m_oErrorStorage;
	}
	LPCTSTR GetApplicationName() const
	{
		return m_oAppNameString;
	}
	LPCTSTR GetServerName() const
	{
		return m_oServerString;
	}
	CPage__ * _get_page_from_iid(long nPageIID);

	//umo¿liwia post komendy przez obiekt z "wnêtrza systemu"
	void fwd_post_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);

	void OnLayoutChange(CRepaintArea & roRepaintArea,bool bUpdateToolbar,long nSourceViewId);
	void OnNewError();

	void GetMiscProviders(CMiscProvidersData & roMPD);
	LPDISPATCH GetDocumentDispatch();
	HDC GetViewHDC(CPage__ * poPage);

	void process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	void process_user_notify(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	void yield(CPage__ * poPage);
	void update_view_immediate(CPage__ * poPage);
	void set_exit_loop();
	void on_after_page_push(CPage__ * poPage);
	void on_before_page_pop(CPage__ * poPage);
	
	//use this when changing cross-page stack active transaction
	void SetCurrentGlobalTransaction(CNEO_trans * poTransaction);
	CNEO_trans * GetCurrentGlobalTransaction();

	SCP<CPageCacheManagerUser> get_pcmu(long IdFile,SCP<CPropertyProvider__> & rpoHLISP);
	SCP<CParseUIThread> create_parseui_thread(SCP<IStream> & rpoInputStreamSP,
		SCP<CUIPageManager> & rpoOutputPageManagerSP);

	SCP<CPage__> get_module(long IdFile);
	SCP<CPage__> get_page_on_hli(SCP<CHyperLinkInfo> & rpoHLISP);

	SCP<CToolBarPageStack> get_toolbar_page_stack();
	SCP <CHyperLinkInfo> GetCommonEnvironmentHLI();

	void init_ui();
	void done_ui();
	void allow_show_UI(bool bShowUI);

	void purge_local_caches();

	//message forwardery
	void raw_OnKeyDown(CNGC & roNGC,UINT nChar, UINT nRepCnt, UINT nFlags);
	void raw_OnMouseClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseEndClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseMove(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnSizeChange(CNGC & roNGC,const CSize & roSize);
	bool raw_OnSetCursor(CPoint point,long nSourceView);
	void raw_OnTimeElapsed(CNGC & roNGC,UINT nIdTimer);
	void raw_OnOleControlEvent(CNGC & roNGC,long IdCtrl,AFX_EVENT* pEvent);

	void OnPrepareDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CRepaintArea & roTotalRA,
		bool bForceRepaint,long nSourceView);
	void raw_OnPerformDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CNAVORegion & roPaintedRgn);

	void raw_OnToolbarDraw(CNGC & roNGC,PAINTSTRUCT & rPS);
	void raw_OnToolbarTimeElapsed(CNGC & roNGC,UINT nIdTimer);

	//"wewnêtrzne" metody automation (powinny byæ wo³ane z CUserThreada'
	afx_msg long Font2InxAUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike);
	afx_msg void Inx2FontAUTO(long nInx, VARIANT FAR* pFontName, VARIANT FAR* pFontSize, VARIANT FAR* pBold, VARIANT FAR* pItalic, VARIANT FAR* pStrike);
	afx_msg LPDISPATCH GetDefinitionManagerAUTO();
	afx_msg VARIANT GetRawAppFileAUTO(long IdFile);
	afx_msg LPDISPATCH GetSAFPAUTO();
	afx_msg LPDISPATCH getmoduleAUTO(long IdPage);
	afx_msg LPDISPATCH getpagehliAUTO(const VARIANT FAR& newValue);
	afx_msg void active_stack_push_pageAUTO(LPDISPATCH pPageDispatch);
	afx_msg void active_stack_pop_pageAUTO();
	afx_msg LPDISPATCH active_stack_get_topAUTO();
	afx_msg long GetUserInfoAUTO(long iter, VARIANT FAR* pvarUserName, VARIANT FAR* pvarComputerName);
	afx_msg void NotifyUserAUTO(long nUserCookie, long nEventCode, const VARIANT FAR& varValue);
	afx_msg long GetUserCookieAUTO();
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetUserPropertyAUTO(long nUserCookie,long nProp,const VARIANT FAR& varValue);
	afx_msg BOOL GetUserPropertyAUTO(long nUserCookie,long nProp,VARIANT FAR * pvarValue);

	afx_msg BOOL CreateCountedResourceAUTO(LPCTSTR lpResName, long nMaxUsage);
	afx_msg BOOL DeleteCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg long UseCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg void ReleaseCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg LPDISPATCH GetAFC_AUTO();

	BEGIN_INTERFACE_PART(NotificationSink,INotificationSink)
		STDMETHOD(OnSharedVariableChange)(long lVarNr,VARIANT varNewValue)
		{
			METHOD_PROLOGUE(CNavoDocMananager, NotificationSink)

			pThis->_on_shared_var_change(lVarNr,&varNewValue);
			return S_OK;
		}
		STDMETHOD(OnNotifyUser)(long nOriginatorCookie,long lEvenCode,VARIANT * pDataVariant)
		{
			METHOD_PROLOGUE(CNavoDocMananager, NotificationSink)
			
			pThis->_on_user_notify(nOriginatorCookie,lEvenCode,pDataVariant);
			return S_OK;
		}
		STDMETHOD(OnProgress)(long nInfoType,long lAdvance,long lTotal,LPSTR lpDescription)
		{
			METHOD_PROLOGUE(CNavoDocMananager, NotificationSink)
			return pThis->_on_progress(nInfoType,lAdvance,lTotal,lpDescription) ? 
				S_OK : ERROR_CANCELLED;
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
	/*SCP<CDefinitionManager> GetDefinitionManager()
	{
		return m_poDefinitionManagerSP;
	}*/
	SCP<IAppDBManager> GetAppDBManager()
	{
		return m_poAppDBManagerSP;
	}
	CStyleAndFontProvider * GetStyleAndFontProvider()
	{
		return m_poStyleAndFontProvider;
	}
	SCP<ICachedData> GetCacheManager()
	{
		return m_poCachedDataSP;
	}
	void _init_AFC();
	void _done_AFC();

	void _call_OnExit();

	void ConsumeActionResult(CAction__ & roAction,long nSourceViewId);	

	void _on_user_notify(long nOriginatorCookie,long lEvenCode,VARIANT * pDataVariant);
	void _on_shared_var_change(long lVarNr,VARIANT * pDataVariant);

	bool _on_progress(long nInfoType,long lAdvance,long lTotal,LPCTSTR lpDescription);
	
	void _get_stack_range_area(long nFrom,long nTo,CRepaintArea & roRepaintArea);
	void _pop_all_stacks(bool bForce);

	void update_toolbar();

	CEnumerableArray<SCP<CPageStack>, SCP<CPageStack> & > m_oPageStackArray;

	SCP<CToolBarPageStack>	m_poToolbarPageStackSP;
	/*
		client connections to servers
	*/

	//obiekty lokalne
	SCP<CNavoObjectCoordinator>	m_poNavoObjCoorSP;
	//SCP<CDefinitionManager>		m_poDefinitionManagerSP;
	CStyleAndFontProvider *		m_poStyleAndFontProvider;
	SCP<ICachedData>			m_poCachedDataSP;
	long						m_nCachedData_PingCookie;
	DWORD m_dwCachedData_GIT_Cookie;

	//obiekty zdalne
	SCP<IServerClient>			m_poServerClientSP;
	SCP<IAppDBManager>			m_poAppDBManagerSP;
	DWORD m_dwAppDBManager_GIT_Cookie;

	SCP<INotificationManager>	m_poNotificationManagerSP;
	long						m_nNotification_Cookie;
	
	SCP<IDispatch>				m_poAFCDispatchSP;
	//for marshalling
	SCP<IGlobalInterfaceTable>	m_poGITSP;

	CString						m_oServerString;
	CString						m_oAppNameString;

	CClientInfoArray			m_oCachedClientInfoArray;
	//top-level error storage
	CNDM_ErrorStorage			m_oErrorStorage;
	long						m_nInsideNewError;
	long						m_nPage_IID;
	bool						m_bOnExitCalled;

	CUserThread *				m_poUserThread; //uplink
};

class CTransSwitchHolder :public CInterface__
{
public:
	CTransSwitchHolder(SCP<CNEO_thread> & rpoTransRootSP,CNEO_trans * poNewTrans);
	~CTransSwitchHolder();
private:
	CNEO_trans *		 m_pOldTrans;
	SCP<CNEO_thread>	 m_poTransRootSP;
#ifdef _DEBUG
	CNEO_trans *		 m_pNewTrans;
#endif
};

#else
	#error __FILE__ already included
#endif