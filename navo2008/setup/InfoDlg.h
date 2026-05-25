#if !defined(AFX_INFODLG_H__FC2A05BF_22BE_42FF_B5FE_48A31D7DD2AC__INCLUDED_)
#define AFX_INFODLG_H__FC2A05BF_22BE_42FF_B5FE_48A31D7DD2AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog

class CInfoDlg : public CWizzardDlg
{
// Construction
public:
	CInfoDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_oAppNameString;
	CString m_oModeString;
	CString m_oDestPathString;
// Dialog Data
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFODLG };
	CStatic	m_stDestPathStatic;
	CStatic	m_stMode;
	CStatic	m_stApplication;
	CButton	m_btNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__FC2A05BF_22BE_42FF_B5FE_48A31D7DD2AC__INCLUDED_)
