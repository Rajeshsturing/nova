/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNAVOView__ - bazowe view dla wszystkich odmian stron
		
		CNAVOPageView - view dla CNavoPage

*/

#ifndef _NAVOVIEW__H_
#define _NAVOVIEW__H_

class CNavoMainFrame;
class CNAVOView__ : public CWnd, public CNavoOleEventSink
{
public:
	CNAVOView__(CNavoMainFrame * poNavoMainFrame);
	virtual ~CNAVOView__();
	virtual void Create() = 0;

	virtual void PostNcDestroy();

	CNGC & get_client_NGC()
	{
		ASSERT(m_poClientNGC);
		return *m_poClientNGC;
	}
	void PrepareDC(CNGC & roNGC);

	void OnZoom();
	void ScrollToShowRect(const _rect & roRectVisible);

	virtual void OnOleControlEvent(long IdCtrl,AFX_EVENT* pEvent);

	void OnLayoutChange(CRepaintArea & roRepaintArea);	
	//{{AFX_MSG(CNAVOView__)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual long GetViewType() const = 0;

	void _on_vscroll(UINT nSBCode, UINT nPos);
	void _on_hscroll(UINT nSBCode, UINT nPos);

	CSize _scroll_to(CPoint oNewPosPoint,CPoint oOldPosPoint);

	CSize _update_scroll_range(CSize oUsedSize);
	CPoint	_get_scroll_bar_position() const;
	CPoint	_get_scroll_thumb_position() const;
	void _set_scroll_bar_position(CPoint point);

	CNavoMainFrame * m_poNavoMainFrame;
	CNGC * m_poClientNGC;
private:
	void InvalidatePendingRA();

	long m_nInsidePaint;
	CRepaintArea m_oPendingInvalidateRA;
	bool m_bPendingForceLayout;
	UINT m_nLastClickFlags;
};


class CNAVOPageView : public CNAVOView__
{
public:
	CNAVOPageView(CNavoMainFrame * poNavoMainFrame);
	virtual void Create();
	//{{AFX_MSG(CNAVOPageView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	virtual long GetViewType() const
	{
		return VIEW_TYPE_NAVO;
	}
private:
};

class CNAVOToolBarView : public CNAVOPageView
{
public:
	CNAVOToolBarView(CNavoMainFrame * poNavoMainFrame);
	virtual void Create();
	virtual long GetViewType() const
	{
		return VIEW_TYPE_TOOLBAR;
	}
	//{{AFX_MSG(CNAVOToolBarView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CNAVOOleDocView : public CNAVOView__
{
public:
	CNAVOOleDocView(CNavoMainFrame * poNavoMainFrame);
	virtual long GetViewType() const
	{
		return VIEW_TYPE_OLEDOC;
	}
	//{{AFX_MSG(CNAVOOleDocView)
	//}}AFX_MSG
private:
};

#else
	#error __FILE__ already included
#endif
