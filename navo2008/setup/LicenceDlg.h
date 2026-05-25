#if !defined(AFX_LICENCEDLG_H__9073EB5A_F1D6_4506_8C7E_4E6DFC211348__INCLUDED_)
#define AFX_LICENCEDLG_H__9073EB5A_F1D6_4506_8C7E_4E6DFC211348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog

class CLicenceDlg : public CWizzardDlg
{
// Construction
public:
	CLicenceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicenceDlg)
	enum { IDD = IDD_LICENCEDLG };
	CString	m_strLicenceTxt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENCEDLG_H__9073EB5A_F1D6_4506_8C7E_4E6DFC211348__INCLUDED_)
