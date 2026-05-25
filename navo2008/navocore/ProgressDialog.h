/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	uniweralny progress (implementacja)
	tego nie wo³aj bezpoœrednio
*/


#if !defined(AFX_PROGRESSDIALOG_H__C46B41C8_242D_4A62_A04D_61B10440B526__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__C46B41C8_242D_4A62_A04D_61B10440B526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog

class CProgressDialog : public CDialog
{
// Construction
public:
	CProgressDialog(bool bCanBreak,CWnd* pParent = NULL);   // standard constructor
	bool IsBroken() const;

	void SetRange(long nTotal)
	{
		m_oProgressCtrl.SetRange32(0,nTotal);
		m_oProgressCtrl.SetStep(1);
	}
	void StepIt()
	{
		m_oProgressCtrl.StepIt();
	}
	void SetElapsed(long nElapsed)
	{
		m_oProgressCtrl.SetPos(nElapsed);
	}

	void SetMonitorString( LPCTSTR lpMonitorString)
	{
		m_oMonitorString = lpMonitorString;
		UpdateData(FALSE);
	}

	void SetQueryEndSessionString(LPCTSTR lpQESString)
	{
		m_oQueryEndSessionString = lpQESString;
	}
	
	void Create(long nTotal,LPCTSTR lpTitle = NULL,CWnd * pParentWnd = NULL);
// Dialog Data
	//{{AFX_DATA(CProgressDialog)
	enum { IDD = IDD_DIALOGPROGRESS };
	CProgressCtrl	m_oProgressCtrl;
	CString	m_oMonitorString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDialog)
	virtual void OnCancel();
	afx_msg BOOL OnQueryEndSession();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_bCanBreak;
	bool m_bBroken;
	CString m_oQueryEndSessionString;
};

class CPerformingDialog : public CDialog
{
// Construction
public:
	CPerformingDialog(CWnd* pParent = NULL);   // standard constructor
	~CPerformingDialog();
// Dialog Data
	//{{AFX_DATA(CPerformingDialog)
	enum { IDD = IDD_PERFORMING };
	CStatic	m_Text;
	CAnimateCtrl m_animation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerformingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPerformingDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	HCURSOR	m_hPreviousCursor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__C46B41C8_242D_4A62_A04D_61B10440B526__INCLUDED_)
