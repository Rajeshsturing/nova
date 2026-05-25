/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CUserThread - w¹tek dzia³añ u¿ytkownika - jest odpowiedzialny za jeden cykl dzia³añ u¿ytkownika (task)
*/

#ifndef _USERTHREAD_H_
#define _USERTHREAD_H_

class CNavoDocMananager;
class CCommandExecutor;
class CNavoMainFrame;
class CPage__;
class CRepaintArea;
struct AFX_EVENT;
class _rect;
class CResultCollector;

class CUserThread : public CNavoThread
{
public:
	CUserThread(bool bRunAsObject = true);
	~CUserThread();
	virtual int Run();
	virtual void OnFinalRelease();
	virtual CNavoException & GetErrorStorage();


	bool _is_run_as_object() const
	{
		return m_bRunAsObject;
	}
	bool _is_ui() const
	{
		return m_bUI;
	}
	bool _is_collect_mode() const
	{
		return m_bCollectResults;
	}
	//--------------------------------------------------------------------------
	bool on_first_command(const CString & roServerString,const CString & roAppNameString,
		const CString & roDBNameString,bool bVisible,long nDBType);
	void init_ui(bool bVisible);
	void done_ui();

	void set_collect_results();

	void process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	void yield(CPage__ * poPage);
	void on_after_page_push(CPage__ * poPage);
	void on_before_page_pop(CPage__ * poPage);
	void post_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void set_exit_loop();
	void on_last_stack_finished();
	bool is_command_enabled(long IdCommand);
	void update_view_immediate(CPage__ * poPage);
	void ScrollToShowRect(const _rect & roRectVisible);

	HDC GetViewHDC(CPage__ * poPage);

	void OnMenuCommand(long nMenuNodeId);
	bool IsMenuCommandEnabled(long nMenuNodeId);
	void OnLayoutChange(CRepaintArea & roRepaintArea,long nSourceViewId);	

	void OnZoomIn();
	void OnZoomOut();

	void OnIdleCommandLoop();
	//--------------------------------------------------------------------------
	//message forwardery
	//--------------------------------------------------------------------------

	void raw_OnKeyDown(CNGC & roNGC,UINT nChar, UINT nRepCnt, UINT nFlags);
	void raw_OnMouseClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseEndClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseMove(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnSizeChange(CNGC & roNGC,const CSize & roSize);
	bool raw_OnSetCursor(CPoint point,long nSourceView);
	void raw_OnTimeElapsed(CNGC & roNGC,UINT nIdTimer);
	void raw_OnToolbarTimeElapsed(CNGC & roNGC,UINT nIdTimer);
	void raw_OnOleControlEvent(CNGC & roNGC,long IdCtrl,AFX_EVENT* pEvent);

	void OnPrepareDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CRepaintArea & roTotalRA,bool bForceRepaint,long nSourceView);
	void raw_OnPerformDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CNAVORegion & roPaintedRgn);

	void raw_OnToolbarDraw(CNGC & roNGC,PAINTSTRUCT & rPS);

	bool _pre_translate_message(MSG & roMsg);

	bool WaitForWorkingState()
	{
		if(m_bTryingExit)				//is atomic, isn't it ?
		{
			return false;
		}
		CSingleLock oSLock(&m_oEventWorking,TRUE);
		return true;
	}
	//--------------------------------------------------------------------------
	DECLARE_DYNCREATE(CUserThread)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	DELEGATE_NAVOERRORINFO_ON_GENERICERRORSTORAGE(CUserThread , m_oErrorStorage );
public:	
	//{{AFX_DISPATCH(CUserThread)
	afx_msg LPDISPATCH CreateHLIAUTO();
	afx_msg LPDISPATCH CreateHLIOnStringAUTO(LPCTSTR lpHyperLinkString);
	afx_msg void fwd_PostCommandStringAUTO(LPCTSTR lpHyperLinkString);
	afx_msg void fwd_PostCommandStringIIDAUTO(LPCTSTR lpHyperLinkString,long nPageIID);
	afx_msg long fwd_Font2InxAUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike);
	afx_msg void fwd_Inx2FontAUTO(long nInx, VARIANT FAR* pFontName, VARIANT FAR* pFontSize, VARIANT FAR* pBold, VARIANT FAR* pItalic, VARIANT FAR* pStrike);
	afx_msg LPDISPATCH fwd_GetDefinitionManagerAUTO();
	afx_msg VARIANT fwd_GetRawAppFileAUTO(long IdFile);
	afx_msg LPDISPATCH fwd_GetSAFPAUTO();
	afx_msg LPDISPATCH fwd_getmoduleAUTO(long IdPage);
	afx_msg LPDISPATCH fwd_getpagehliAUTO(const VARIANT FAR& newValue);
	afx_msg void fwd_PushPageAUTO(LPDISPATCH page);
	afx_msg void fwd_PopPageAUTO();
	afx_msg LPDISPATCH fwd_GetTopPageAUTO();
	afx_msg LPDISPATCH CreateStreamObjectAUTO();
	afx_msg LPDISPATCH CreateSystemObjectAUTO();
	afx_msg void SetMenuAUTO(const VARIANT FAR& varStreamOrURL);
	afx_msg long fwd_GetUserInfoAUTO(long iter, VARIANT FAR* pvarUserName, VARIANT FAR* pvarComputerName);
	afx_msg void fwd_NotifyUserAUTO(long nUserCookie, long nEventCode, const VARIANT FAR& varValue);
	afx_msg long fwd_GetUserCookieAUTO();
	afx_msg void fwd_SetUserPropertyAUTO(long nUserCookie,long nProp,const VARIANT FAR& varValue);
	afx_msg BOOL fwd_GetUserPropertyAUTO(long nUserCookie,long nProp,VARIANT FAR * pvarValue);
	afx_msg LPUNKNOWN fwd_GetNewEnumAUTO();
	afx_msg void fwd_SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg LPDISPATCH fwd_GetToolbarAUTO();
	afx_msg void SetTimerAUTO(long nTimerId,const VARIANT FAR& rvarHLI,long nInterval);
	afx_msg BOOL IsCommandEnabledAUTO(long nCmd);
	afx_msg LPDISPATCH CreatePerformingObjectAUTO(LPCTSTR lpText);
	afx_msg void BringWindowToTopAUTO();
	afx_msg LPDISPATCH CreateCmdListAUTO();
	afx_msg LPDISPATCH GetResultCollectorAUTO();

	afx_msg BOOL fwd_CreateCountedResourceAUTO(LPCTSTR lpResName, long nMaxUsage);
	afx_msg BOOL fwd_DeleteCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg long fwd_UseCountedResourceAUTO(LPCTSTR lpResName);
	afx_msg void fwd_ReleaseCountedResourceAUTO(LPCTSTR lpResName);

	afx_msg long fwd_GetZoomAUTO();
	afx_msg void fwd_SetZoomAUTO(long nNewZoom);
	afx_msg void fwd_PurgeLocalCachesAUTO();

	afx_msg LPDISPATCH fwd_GetAFC_AUTO();
	//}}AFX_DISPATCH
	//{{AFX_MSG(CUserThread)
	//}}AFX_MSG
private:
	bool ThreadInit();
	void ThreadGo();
	void ThreadDone();

	void _create_menu_on_xml_file(long IdFile);
	void _create_menu_on_stream(SCP<IStream> & rpoStreamSP);

	CPage__ * get_active_page();

	//----------------------------------------------------------------------
	//------------ collecting results support ------------------------------

	void _reset_collected_results(long nOldPageIID);
	void _set_collected_results(long nCurrPageIID);
	void _mark_active_page_changed();
	SCP<CResultCollector> _wait_for_results();

	//----------------------------------------------------------------------
	void EnterWorkingState()		//thread itself knows its ready
	{
		m_oEventWorking.SetEvent();
	}
	void LeaveWorkingState()
	{
		m_bTryingExit = true;			//is atomic, isn't it ?
		m_oEventWorking.ResetEvent();
		CSingleLock oSLock(&m_oEventFreeToExit,TRUE);
	}
	void MarkFreeToExit()
	{
		ASSERT(m_bAutoDelete);
		m_oEventFreeToExit.SetEvent();
	}



	CCommandExecutor *  m_poCommandExecutor;
	CNavoDocMananager * m_poNavoDocManager;
	CNavoMainFrame * m_poNavoMainFrame;

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
	long						m_nInsideTimeElapsed;

	long m_nExitCode;
	
	bool	m_bRunAsObject;
	bool	m_bCollectResults;
	CEvent	m_oResultsReadyEvent;

	SCP<CResultCollector> m_poResultCollectorSP;
	bool m_bUI;

	CNavoGraphicsSession		m_oNavoGraphicsSession;

	bool	m_bTryingExit;
	CEvent	m_oEventWorking;
	CEvent	m_oEventFreeToExit;
	//tymczasowe error storage, u¿ywane w czasie gdy nie ma jeszcze/juz NDM'a
	CGenericErrorStorage m_oErrorStorage;	
};

#else
	#error __FILE__ already included
#endif