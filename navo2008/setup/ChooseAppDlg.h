#if !defined(AFX_CHOOSEAPPDLG_H__0246B652_5AF2_412E_B346_C44F2C3A0606__INCLUDED_)
#define AFX_CHOOSEAPPDLG_H__0246B652_5AF2_412E_B346_C44F2C3A0606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseAppDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseAppDlg dialog

class CChooseAppDlg : public CWizzardDlg
{
// Construction
public:
	CChooseAppDlg(CWnd* pParent = NULL);   // standard constructor
	
	CArray<CString,LPCTSTR>	m_oAppInfoArray;		//odd index - name, even - location
	long	m_nSelInx;
// Dialog Data
	//{{AFX_DATA(CChooseAppDlg)
	enum { IDD = IDD_CHOOSEAPPDLG };
	CListCtrl	m_lcAppList;
	CButton	m_btNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseAppDlg)
	afx_msg void OnNext();
	afx_msg void OnBack();
	virtual BOOL OnInitDialog();
	afx_msg void OnLocalchoose();
	afx_msg void OnInetchoose();
	afx_msg void OnInsertitemApplist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickApplist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkApplist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddApplication( const CString & oAppName, const CString & oLocation);
	int  GetCurrentSelection();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEAPPDLG_H__0246B652_5AF2_412E_B346_C44F2C3A0606__INCLUDED_)
