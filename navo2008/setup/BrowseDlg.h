#if !defined(AFX_BROWSEDLG_H__70645976_AD35_4E5D_B1B4_6F2814C7C7D5__INCLUDED_)
#define AFX_BROWSEDLG_H__70645976_AD35_4E5D_B1B4_6F2814C7C7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowseDlg dialog

class CBrowseDlg : public CDialog
{
// Construction
public:
	bool m_bDownloadAll;
	CString m_strFile;
	CString m_strDir;
	bool m_bDownload;
	CBrowseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBrowseDlg)
	enum { IDD = IDD_BROWSEDLG };
	int		m_nCopyMethod;
	CString	m_edMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBrowseDlg)
	afx_msg void OnLocal();
	afx_msg void OnNavo();
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSEDLG_H__70645976_AD35_4E5D_B1B4_6F2814C7C7D5__INCLUDED_)
