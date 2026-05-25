#if !defined(AFX_LOGINASUSERDLG_H__B595C4EB_2FB1_4197_9279_E1CAEDC535D6__INCLUDED_)
#define AFX_LOGINASUSERDLG_H__B595C4EB_2FB1_4197_9279_E1CAEDC535D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginAsUserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginAsUserDlg dialog

class CLoginAsUserDlg : public CDialog
{
// Construction
public:
	CLoginAsUserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginAsUserDlg)
	enum { IDD = IDD_LOGIN };
	CString	m_oDomainString;
	CString	m_oPasswordString;
	CString	m_oUserString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginAsUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginAsUserDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINASUSERDLG_H__B595C4EB_2FB1_4197_9279_E1CAEDC535D6__INCLUDED_)
