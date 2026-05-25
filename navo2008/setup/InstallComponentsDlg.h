#if !defined(AFX_INSTALLCOMPONENTSDLG_H__50485BA5_5811_4187_A456_C5FCF2BD2EAA__INCLUDED_)
#define AFX_INSTALLCOMPONENTSDLG_H__50485BA5_5811_4187_A456_C5FCF2BD2EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstallComponentsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstallComponentsDlg dialog
enum eNEComponent;

class CInstallComponentsDlg : public CWizzardDlg
{
// Construction
public:
	CInstallComponentsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInstallComponentsDlg)
	enum { IDD = IDD_INSTALLCOMPDLG };
	CButton	m_btCancel;
	CButton	m_btBack;
	CButton	m_btNext;
	CButton	m_btWinInst;
	CButton	m_btVBS;
	CButton	m_btXML;
	CButton	m_btMDAC;
	CButton m_btDotNet;
	CButton	m_btEngine;
	CButton	m_btDCOM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallComponentsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void SetButtons();
	CButton& GetButton( enum eNEComponent eNEC);
// Implementation
protected:
	bool m_bTestPerformed;

	// Generated message map functions
	//{{AFX_MSG(CInstallComponentsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLCOMPONENTSDLG_H__50485BA5_5811_4187_A456_C5FCF2BD2EAA__INCLUDED_)
