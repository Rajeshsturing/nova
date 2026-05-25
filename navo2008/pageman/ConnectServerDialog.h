#if !defined(AFX_CONNECTSERVERDIALOG_H__BFA5E082_FF8E_48F5_B57A_733DC4741A67__INCLUDED_)
#define AFX_CONNECTSERVERDIALOG_H__BFA5E082_FF8E_48F5_B57A_733DC4741A67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectServerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectServerDialog dialog

class CConnectServerDialog : public CDialog
{
// Construction
public:
	CConnectServerDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectServerDialog)
	enum { IDD = IDD_CONNECTDIALOG };
	CComboBox	m_cbAppName;
	CButton	m_btOK;
	CString	m_ServerString;
	CString	m_AppNameString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectServerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectServerDialog)
	afx_msg void OnConnect();
	afx_msg void OnSelchangeComboAppname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTSERVERDIALOG_H__BFA5E082_FF8E_48F5_B57A_733DC4741A67__INCLUDED_)
