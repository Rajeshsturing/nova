#if !defined(AFX_COMPILATIONRESULTSDIALOG_H__37C4A746_284E_4A25_B384_D14C5F8BE6F6__INCLUDED_)
#define AFX_COMPILATIONRESULTSDIALOG_H__37C4A746_284E_4A25_B384_D14C5F8BE6F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CompilationResultsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompilationResultsDialog dialog

class CCompilationResultsDialog : public CDialog
{
// Construction
public:
	CCompilationResultsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompilationResultsDialog)
	enum { IDD = IDD_COMPILATIONRESULTSDIALOG };
	CEdit	m_edResults;
	CString	m_oResultsString;
	CString m_oSourceString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompilationResultsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompilationResultsDialog)
	afx_msg void OnShowresults();
	afx_msg void OnShowsource();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPILATIONRESULTSDIALOG_H__37C4A746_284E_4A25_B384_D14C5F8BE6F6__INCLUDED_)
