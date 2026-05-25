#if !defined(AFX_WELCOMEDLG_H__DEC842CD_3D37_4EED_9F2B_4E633244B925__INCLUDED_)
#define AFX_WELCOMEDLG_H__DEC842CD_3D37_4EED_9F2B_4E633244B925__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog

class CWelcomeDlg : public CWizzardDlg
{
// Construction
public:
	CWelcomeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcomeDlg)
	enum { IDD = IDD_WELCOMEDLG };
	int		m_nChoice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDlg)
	afx_msg void OnNext();
	afx_msg void OnAutomatic();
	afx_msg void OnManual();
	afx_msg void OnUninstall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEDLG_H__DEC842CD_3D37_4EED_9F2B_4E633244B925__INCLUDED_)
