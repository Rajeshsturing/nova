/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoToolbar - toolbar by NAVO
		CNAVOStatusBar
*/

#ifndef _NAVOTOOLBAR_H_
#define _NAVOTOOLBAR_H_
/*
extern HINSTANCE _h_PAGEMAN_Instance;

class CNAVOToolbar : public CCJToolBar
{
public:
	CNAVOToolbar() :
		m_nId(0)
	{
	}
	~CNAVOToolbar()
	{
	}
	virtual void OnFinalRelease()
	{
		delete this;
	}
	bool Create(CCJMDIFrameWnd * pParent,long Id)
	{
		if(!CreateEx(pParent, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
		{
			return false;
		}
		SetBarStyle(GetBarStyle() & ~CBRS_HIDE_INPLACE);
		EnableDocking(CBRS_ALIGN_ANY);
		pParent->DockControlBar(this);
		CAfxResourceHandleHolder oRHH(_h_PAGEMAN_Instance);
		LoadToolBar(Id);
		m_nId = Id;
		return true;
	}
	long GetId()
	{
		return m_nId;
	}
	DELEGATE_UNKNOWN_ON_CMDTARGET
private:
	long m_nId;
};


class CNAVOStatusBar : public CStatusBar
{
public:
	CNAVOStatusBar() :
	  m_bBroken(false)
	{}
	void BeginProgress(long nTotal,bool bCanBreak,LPCTSTR lpTitle = NULL);
	void EndProgress();
	bool IsBrokenProgress() const;
	void SetElapsedProgress(long nElapsed);

	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CNAVOStatusBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
private:
	CProgressCtrl	m_oProgressCtrl;
	CButton			m_oBreakButton;
	bool			m_bBroken;
};
*/

#else
	#error __FILE__ already included
#endif
