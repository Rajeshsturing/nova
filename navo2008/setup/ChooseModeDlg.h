#if !defined(AFX_CHOOSEMODEDLG_H__87DFA161_76EA_4194_95C2_9F4815CDCEEC__INCLUDED_)
#define AFX_CHOOSEMODEDLG_H__87DFA161_76EA_4194_95C2_9F4815CDCEEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseModeDlg dialog

class CChooseModeDlg : public CWizzardDlg
{
// Construction
public:
	CChooseModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseModeDlg)
	enum { IDD = IDD_CHOOSEMODEDLG };
	CButton	m_btNext;
	CStatic	m_stServerText;
	CEdit	m_etServerName;
	int		m_nMode;
	CString	m_strServerName;
	CString	m_strRootDestPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseModeDlg)
	afx_msg void OnNext();
	afx_msg void OnBack();
	afx_msg void OnWorkstation();
	afx_msg void OnChangeServername();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEMODEDLG_H__87DFA161_76EA_4194_95C2_9F4815CDCEEC__INCLUDED_)
