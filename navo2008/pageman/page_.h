/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CPage__ - abstrakcyjna "strona" bazowa
*/

#ifndef _PAGE__H_
#define _PAGE__H_

class CPageStack;
class CAction__;
class CActionPaint;
class CActionMouse;
class CActionKBD;
class CActionTimeElapsed;
class CActionOleEvent;
class CRepaintArea;
class CTransaction;

class CPage__ : public CCmdTargetInterface
{
public:
	CPage__(CPageStack * poPageStack,SCP <CHyperLinkInfo> & rpoOpeningHLISP);
	~CPage__();
	virtual long _get_page_iid() const
	{
		return m_nPage_IID;
	}
	CPageStack * _get_page_stack() const
	{
		return m_poPageStack;
	}
	virtual bool Prepare() = 0;					//inicjuje przygotowanie do pracy
	virtual bool UnPrepare(bool bForce) = 0;
	virtual bool process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP);
	virtual long Print() = 0;

	virtual long GetViewType() = 0;

	virtual	void GetPageRect(_rect & roPageRect) = 0;
	virtual	void GetPageCompleteArea(CRepaintArea & roRepaintArea) = 0;
	virtual void OnActivate(bool bActive) = 0;

	virtual void OnChangeMMState(eMinMaxState eNewMMState) = 0;
	//message forwardery
	virtual bool OnKeyDown(CActionKBD & roActionKBD) = 0;
	virtual void OnMouseClick(CActionMouse & roActionMouse) = 0;
	virtual void OnMouseEndClick(CActionMouse & roActionMouse) = 0;
	virtual void OnMouseMove(CActionMouse & roActionMouse) = 0;
	virtual void OnTimeElapsed(CActionTimeElapsed & roActionTime,UINT nIdTimer) = 0;
	virtual void raw_OnSizeChange(CDC & roDC,const CSize & roSize) = 0;
	virtual bool raw_OnSetCursor(CPoint point) = 0;
	virtual void OnOleControlEvent(CActionOleEvent & roActionOleEvent) = 0;
	
	virtual void UndoAction(CAction__ & roAction,CArchive & roUndoArchive) = 0;

	virtual void raw_OnPrepareDraw(CActionPaint & roActionPaint) = 0;
	virtual void raw_OnPerformDraw(CActionPaint & roActionPaint,CNAVORegion & roPaintedRgn) = 0;

	virtual bool IsCommandEnabled(long /*IdCommand*/)
	{
		return false;
	}

	CNavoException & GetErrorStorage();
	
	SCP<CNEO_trans> & GetTransaction()
	{
		return m_poTransactionSP;
	}

	bool is_in_modal_loop() const
	{
		return (m_nInModal != 0);
	}
	//{{AFX_MSG(CPage__)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CPage__)
	afx_msg void ActivateAUTO();
	afx_msg long GetResultAUTO();
	afx_msg void SetResultAUTO(long nNewValue);
	afx_msg long DoModalAUTO();
	afx_msg long DoModalNewAUTO();
	afx_msg long PrintAUTO();
	afx_msg void GoBackAUTO();
	afx_msg BOOL IsCommandEnabledAUTO(long nCmd);
	afx_msg LPDISPATCH GetRealThisAUTO();
	afx_msg long GetPageIIDAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	long _do_modal(bool bAutoPop);

	long					m_nModalResult;
	long					m_nInModal;
	const long				m_nPage_IID;
	CPageStack *			m_poPageStack;	//uplink
	SCP <CHyperLinkInfo>	m_poOpeningHLISP;
	SCP<CNEO_trans>		m_poTransactionSP;

#ifdef _DEBUG
	friend class CPageStack;
#endif
};

#else
	#error __FILE__ already included
#endif