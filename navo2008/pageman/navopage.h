/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoPage - "strona" typu NAVO
*/

#ifndef _NAVOPAGE_H_
#define _NAVOPAGE_H_

class CUIPageManager;
class CUIEventManager;
class CNEO_user;
class CNEO_cursorIterator;

class CNavoPage : public CPage__ , public CUIPageManagerController
{
public:
	CNavoPage(CPageStack * poPageStack,SCP <CHyperLinkInfo> & rpoOpeningHLISP);
	~CNavoPage();

	virtual bool Prepare();						//inicjuje przygotowanie do pracy
	virtual bool UnPrepare(bool bForce);
	virtual bool process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	virtual long Print();
	virtual long GetViewType();

	virtual	void GetPageRect(_rect & roPageRect);
	virtual	void GetPageCompleteArea(CRepaintArea & roRepaintArea);
	virtual void OnActivate(bool bActive);
	//-------------------- CUIPageManagerController methods --------------------
	virtual bool RequestDataSetEvent(CDataUnit & roDataUnit);
	virtual void GetMiscProviders(CMiscProvidersData & roMPD);
	virtual void OnLayoutChangePending();

	static SCP<CNavoPage> FromIDispatch(LPDISPATCH lpDispatch);

	virtual void OnChangeMMState(eMinMaxState eNewMMState);
	//message forwardery
	virtual bool OnKeyDown(CActionKBD & roActionKBD);
	virtual void OnMouseClick(CActionMouse & roActionMouse);
	virtual void OnMouseEndClick(CActionMouse & roActionMouse);
	virtual void OnMouseMove(CActionMouse & roActionMouse);
	virtual void OnTimeElapsed(CActionTimeElapsed & roActionTime,UINT nIdTimer);
	virtual void raw_OnSizeChange(CDC & roDC,const CSize & roSize);
	virtual bool raw_OnSetCursor(CPoint point);
	virtual void OnOleControlEvent(CActionOleEvent & roActionOleEvent);

	virtual bool IsCommandEnabled(long IdCommand);
	virtual void UndoAction(CAction__ & roAction,CArchive & roUndoArchive);

	void raw_OnPrepareDraw(CActionPaint & roActionPaint);
	void raw_OnPerformDraw(CActionPaint & roActionPaint,CNAVORegion & roPaintedRgn);

	//{{AFX_MSG(CNavoPage)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CNavoPage)
	afx_msg BOOL GetEnableEditAUTO();
	afx_msg void SetEnableEditAUTO(BOOL bNewValue);
	afx_msg BOOL GetCmdEnabledAUTO(long nCmd);
	afx_msg void SetCmdEnabledAUTO(long nCmd, BOOL bNewValue);
	afx_msg LPDISPATCH GetCursorIteratorAUTO();
	afx_msg void SetCursorIteratorAUTO(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetRootAUTO();
	afx_msg void SetRootAUTO(LPDISPATCH newValue);
	afx_msg void UpdateViewAUTO();
	afx_msg LPDISPATCH GetUIElementAUTO(long Ident);
	afx_msg LPDISPATCH SafeGetUIElementAUTO(long Ident);
	afx_msg long GetPageRootTypeIdAUTO();
	afx_msg long GetPageRootIdObjAUTO();
	afx_msg LPDISPATCH GetUIPageManagerAUTO();
	afx_msg long GetSecurityId_Read_AUTO();
	afx_msg long GetSecurityId_Insert_AUTO();
	afx_msg long GetSecurityId_Update_AUTO();
	afx_msg long GetSecurityId_Delete_AUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(PropDispatch, IDispatch)
		STDMETHOD(GetTypeInfoCount)(UINT*);
        STDMETHOD(GetTypeInfo)(UINT,LCID,ITypeInfo **);
		STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId);
		STDMETHOD(Invoke)(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError);
	END_INTERFACE_PART(PropDispatch)
protected:
	void _init_dataobject_etc();

	void _make_full_dataeventscan(CAction__ & roAction);
	bool ConsumeActionResult(CAction__ & roAction);	

	void _process_command_copy(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	void _process_command_paste(SCP <CHyperLinkInfoWithResult> & roHLISCP,CAction__ & roAction);
	void _process_command_savepage(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	bool _is_data_in_clipboard();

	void _set_enable_edit(bool bEnable);
	bool _get_enable_edit() const;

	CDispatchForwarder & _get_page_disp_fwdr()
	{
		return m_oPage_DispatchForwarder;
	}

	CDispatchForwarder			m_oPage_DispatchForwarder;
	SCP<CUIPageManager>			m_poPageManagerSP;
	CUIEventManager *			m_poEventManager;
	SCP<CNEO_user>				m_poRootStdObjSP;
	long						m_nRootIdObj;
	SCP<CNEO_cursorIterator> m_poCursorsCollectionIteratorSP;
	bool						m_bPendingLayoutChange;

#ifdef _DEBUG
	long debug_inside_process_command;
#endif

private:
	bool	m_bFirstLayout;		//czy jest to pierwsze uk³adanie strony (powoduje
								//pozycjonowanie okna
	bool	m_bEnableEdit;
};

class CToolbarNavoPage : public CNavoPage
{
public:
	CToolbarNavoPage(CPageStack * poPageStack,SCP <CHyperLinkInfo> & rpoOpeningHLISP);
	virtual bool Prepare();						//inicjuje przygotowanie do pracy
	virtual long GetViewType();
	virtual long _get_page_iid() const;
};

class CMessageNavoPage : public CNavoPage
{
public:
	CMessageNavoPage(CPageStack * poPageStack,SCP <CHyperLinkInfo> & rpoOpeningHLISP);
	virtual long GetViewType();
};

#else
	#error __FILE__ already included
#endif
