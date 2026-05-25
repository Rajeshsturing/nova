/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoMainFrame - main aplication frame (when UI used, also implemention of
		abstract CUIMainFrame__
*/

#ifndef _NAVOMAINFRAME_H_
#define _NAVOMAINFRAME_H_

class CUserThread;
class CNAVOView__;
class CNavoMainFrame;
class CNAVOToolBarView;
class CRepaintArea;

class CNavoMainFrame : public CWnd
{
public:
	CNavoMainFrame(CUserThread * poUserThread);
	~CNavoMainFrame();
	void Create(LPCTSTR lpCaption);
	void Done();

	void AddRefViewType(long nViewType);
	void ReleaseViewType(long nViewType);
	void OnLayoutChange(CRepaintArea & roRepaintArea,long nSourceViewId);	
	HDC GetViewHDC(long nViewType);

	void OnZoomIn();
	void OnZoomOut();
	void OnSetZoom(const CSize & roNewZoom);
	void update_view_immediate(long nViewType);
	void ScrollToShowRect(const _rect & roRectVisible);

	//quasi interface (CUIMainFrame__) used by CUserThread and related accessors
	//~quasi interface 
	//{{AFX_MSG(CNavoMainFrame)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	
	//poza nawiasami bo ClassWizard ich nie trawi
	afx_msg void OnMenuCommand(UINT nID);
	afx_msg void OnUpdateMenuCommand(CCmdUI* pCmdUI);
	virtual void PostNcDestroy();
	bool _pre_translate_message(MSG & roMsg);

	const CSize & GetZoom() const
	{
		return m_oZoomSize;
	}
	
	void _set_fast_graphics(bool bFast)
	{
		m_bFastGraphics = bFast;
	}

	bool _is_fast_graphics() const
	{
		return m_bFastGraphics;
	}

	//message forwardery
	void raw_OnKeyDown(CNGC & roNGC,UINT nChar, UINT nRepCnt, UINT nFlags);
	void raw_OnMouseClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseEndClick(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnMouseMove(CNGC & roNGC,UINT nFlags, CPoint point,long nSourceView);
	void raw_OnSizeChange(CNGC & roNGC,const CSize & roSize);
	void raw_OnOleControlEvent(CNGC & roNGC,long IdCtrl,AFX_EVENT* pEvent);

	bool raw_OnSetCursor(CPoint point,long nSourceView);

	void OnPrepareDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CRepaintArea & roTotalRA,
		bool bForceRepaint,long nSourceView);
	void raw_OnPerformDraw(CNGC & roNGC,PAINTSTRUCT & rPS,CNAVORegion & roPaintedRgn);

	void raw_OnToolbarDraw(CNGC & roNGC,PAINTSTRUCT & rPS);

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
private:
	void _delete_view();
	void _align_children();

	CBrush	m_oBackgroundBrush;
	CUserThread * m_poUserThread;
	CNAVOView__ * m_poMainView;
	CNAVOToolBarView * m_poToolbarView;

	long m_nVTNAVO_Ref;			//liczba referencji do view typu NAVO
	long m_nVTOLE_Ref;			//liczba referencji do view typu OLE

	CSize m_oZoomSize;
	bool  m_bFastGraphics;
};


#else
	#error __FILE__ already included
#endif
