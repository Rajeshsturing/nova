/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_view__
		base view (just for integration)
*/

#ifndef _VIEW_NDOC_H_
#define _VIEW_NDOC_H_

class cndoc_mainwindow;

class cndoc_view__ : public CWnd, public CInterface__
{
public:
	cndoc_view__(eViewType eVT,cndoc_mainwindow * poMainWindow);
public:
	//{{AFX_VIRTUAL(cndoc_view__)
	//}}AFX_VIRTUAL
public:
	virtual ~cndoc_view__();
	virtual void OnFinalRelease();
	virtual void PostNcDestroy();

	virtual void create() = 0;
	virtual void update() = 0;
	virtual void on_timer_event(UINT nIDEvent) = 0;
	virtual bool on_idle() = 0;
protected:
	CNavoException & GetErrorStorage();
	//{{AFX_MSG(cndoc_view__)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	cndoc_mainwindow * m_poMainWindow;
	eViewType m_eVT;
};

/////////////////////////////////////////////////////////////////////////////
class cndoc_navoview : public cndoc_view__,public cndoc_navoview_impl
{
public:
	cndoc_navoview(eViewType eVT,cndoc_mainwindow * poMainWindow,SCP<cned_arena> poArenaSP);
	//{{AFX_VIRTUAL(cndoc_navoview)
	//}}AFX_VIRTUAL
	virtual CNavoException & _error_storage();
	virtual void _get_client_rect(ng_rect & roClientRect);
public:
	virtual ~cndoc_navoview();
	virtual void create();
	virtual void update();
	virtual void on_timer_event(UINT nIDEvent);
	virtual bool on_idle();
protected:
	//{{AFX_MSG(cndoc_navoview)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CNavoException & cndoc_navoview::_error_storage()
{
	return GetErrorStorage();
}


#else
	#error __FILE__ already included
#endif

