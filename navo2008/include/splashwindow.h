/*

	NAVO Enterprise 2001 (c)
	splash window
*/

#ifndef _SPLASHWINDOW_H_
#define _SPLASHWINDOW_H_

class ng_image;

class CSplashWindow : public CWnd, public CInterface__
{
public:
	CSplashWindow(LPCTSTR lpSplashFileName);
	~CSplashWindow();

	//{{AFX_MSG(CSplashWindow)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL Create(CWnd* pParentWnd = NULL);
	SCP<ng_image>	m_poSafeImageSP;
	CString			m_oSplashFileNameString;
};

#else
	#error __FILE__ already included
#endif
