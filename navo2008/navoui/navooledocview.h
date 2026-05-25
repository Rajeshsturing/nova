/*
	NAVO Enterprise 2001

	COld_NAVOOleDocView - view presenting ole document
*/

#ifndef _NAVOOLEDOCVIEW_H_
#define _NAVOOLEDOCVIEW_H_
/*
class COld_NAVOOleDocView : public COld_NAVOView__
{
public:
	COleDocument * GetDocument()
	{
		return dynamic_cast<COleDocument *>(m_pDocument);
	}
	void SetDocument(COleDocument * poOleDocument)
	{
		m_pDocument = poOleDocument;
	}

#undef NAVO_CLASS_DECL
#ifdef THIS_IS_NAVOUI
#define NAVO_CLASS_DECL _declspec(dllexport)
#else
#define NAVO_CLASS_DECL _declspec(dllimport)
#endif
#undef  AFX_DATA
#define AFX_DATA NAVO_CLASS_DECL

	DECLARE_DYNCREATE(COld_NAVOOleDocView);

	COld_NAVOOleDocView(){}
	DECLARE_MESSAGE_MAP()
	
	//{{AFX_VIRTUAL(COld_NAVOOleDocView)
	virtual void OnDraw(CDC*){}
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(COld_NAVOOleDocView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelEditCntr();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

#undef  AFX_DATA
#define AFX_DATA
};
*/

#else
	#error __FILE__ already included
#endif
