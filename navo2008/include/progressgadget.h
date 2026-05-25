/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	uniweralny progress (do u¿ycia w aplikacji)
*/

#ifndef _PROGRESS_GADGET_H_
#define _PROGRESS_GADGET_H_

class CProgressDialog;

class CProgressInfo: public CCmdTargetInterface
{
public:
	CProgressInfo(long nTotal,bool bCanBreak,LPCTSTR lpTitle = NULL,CWnd * pParentWnd = NULL);
	~CProgressInfo();
	bool IsBroken() const;
	void StepIt();
	void SetElapsed(long nElapsed);
	void SetRange(long nTotal);
	void SetMonitorString( LPCTSTR lpMonitorString);
	void SetQueryEndSessionString(LPCTSTR lpQESString);
	//{{AFX_DISPATCH(CProgressInfo)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	CProgressDialog * m_poProgressDialog;
	HWND	m_hProgressParent;
};

class CPerformingDialog;
class CPerformingDialogHolder: public CCmdTargetInterface
{
public:
	CPerformingDialogHolder(LPCTSTR pcText, HWND hWnd = NULL);
	CPerformingDialogHolder(LPCTSTR pcText, CWnd * pWnd, bool bDisableParent = true);
	~CPerformingDialogHolder();
	void SetText(LPCTSTR lpNewText);
	//{{AFX_DISPATCH(CPerformingDialogHolder)
	afx_msg BSTR GetTextAUTO();
	afx_msg void SetTextAUTO(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	//{{AFX_MSG(CPerformingDialogHolder)
	//}}AFX_MSG
public:
	CPerformingDialog * m_poDialog;
	bool m_bDisableParentWindow;
	CWnd * m_pWnd;
};

#else
	#error __FILE__ already included
#endif
