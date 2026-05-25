/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	uniweralny progress (implementacja)
	tego nie wo³aj bezpoœrednio
*/


#include "stdafx.h"
#include <afxcmn.h>
#include "..\include\progressgadget.h"
#include "resource.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOCORE_Instance;
/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog


CProgressDialog::CProgressDialog(bool bCanBreak,CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent),
	m_bCanBreak(bCanBreak),
	m_bBroken(false)
{
	//{{AFX_DATA_INIT(CProgressDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_oMonitorString = _T("");
	//}}AFX_DATA_INIT
}


void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDialog)
	DDX_Control(pDX, IDC_PROGRESS1, m_oProgressCtrl);
	DDX_Text(pDX, IDC_MONITOR, m_oMonitorString);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
	//{{AFX_MSG_MAP(CProgressDialog)
	ON_WM_QUERYENDSESSION()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CProgressDialog::OnCancel() 
{
	m_bBroken = true;
}

bool CProgressDialog::IsBroken() const
{
	MSG msg;
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return m_bBroken;
}

void CProgressDialog::Create(long nTotal,LPCTSTR lpTitle,CWnd * pParentWnd)
{
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	CDialog::Create(CProgressDialog::IDD,(pParentWnd == NULL) ? CWnd::GetActiveWindow() : pParentWnd);
	SetRange(nTotal);
	CenterWindow();
	if(!m_bCanBreak)
	{
		ASSERT(GetDlgItem(IDCANCEL));
		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	}
	ShowWindow(SW_SHOW);
	UpdateWindow();
	if(lpTitle)
	{
		SetWindowText(lpTitle);
	}
}

//========================================
// calling shell
//========================================
BEGIN_DISPATCH_MAP(CProgressInfo, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CProgressInfo)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

CProgressInfo::CProgressInfo(long nTotal,bool bCanBreak,LPCTSTR lpTitle,CWnd * pParentWnd):
	m_hProgressParent(NULL)
{
	EnableAutomation();
	m_poProgressDialog = new CProgressDialog(bCanBreak,pParentWnd);
	m_poProgressDialog->Create(nTotal,lpTitle,pParentWnd);
	if(pParentWnd)
	{
		m_hProgressParent = pParentWnd->m_hWnd;
		pParentWnd->EnableWindow(FALSE);
	}
}

CProgressInfo::~CProgressInfo()
{
	if(m_hProgressParent != NULL)
	{
		CWnd * pWnd = CWnd::FromHandle(m_hProgressParent);
		pWnd->EnableWindow(TRUE);
		pWnd->SetFocus();
	}
	delete m_poProgressDialog;
}

bool CProgressInfo::IsBroken() const
{
	ASSERT(m_poProgressDialog);
	return m_poProgressDialog->IsBroken();
}

void CProgressInfo::StepIt()
{
	ASSERT(m_poProgressDialog);
	m_poProgressDialog->StepIt();
}

void CProgressInfo::SetElapsed(long nElapsed)
{
	ASSERT(m_poProgressDialog);
	m_poProgressDialog->SetElapsed(nElapsed);
}

void CProgressInfo::SetRange(long nTotal)
{
	ASSERT(m_poProgressDialog);
	m_poProgressDialog->SetRange(nTotal);
}

void CProgressInfo::SetMonitorString( LPCTSTR lpMonitorString)
{
	ASSERT(m_poProgressDialog);
	m_poProgressDialog->SetMonitorString(lpMonitorString);
}

void CProgressInfo::SetQueryEndSessionString(LPCTSTR lpQESString)
{
	ASSERT(m_poProgressDialog);
	m_poProgressDialog->SetQueryEndSessionString(lpQESString);
}

/////////////////////////////////////////////////////////////////////////////
// CPerformingDialog message handlers
BEGIN_DISPATCH_MAP(CPerformingDialogHolder, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CPerformingDialogHolder)
	DISP_PROPERTY_EX(CPerformingDialogHolder, "text", GetTextAUTO, SetTextAUTO, VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_MESSAGE_MAP(CPerformingDialogHolder, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CPerformingDialogHolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPerformingDialogHolder::CPerformingDialogHolder(LPCTSTR pcText, HWND hWnd):
	m_bDisableParentWindow(false),
	m_pWnd(NULL)
{
	EnableAutomation();
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	CWnd * pWnd = CWnd::FromHandle(hWnd);
	m_poDialog = new CPerformingDialog();
	m_poDialog->Create(m_poDialog->IDD, pWnd);
	m_poDialog->m_Text.SetWindowText(pcText);
};

CPerformingDialogHolder::CPerformingDialogHolder(LPCTSTR pcText, CWnd * pWnd, bool bDisableParent):
	m_bDisableParentWindow(bDisableParent),
	m_pWnd(pWnd)
{
	EnableAutomation();
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	if (!m_pWnd)
	{
		m_bDisableParentWindow = false;
	};
	m_poDialog = new CPerformingDialog();
	m_poDialog->Create(m_poDialog->IDD, pWnd);
	m_poDialog->m_Text.SetWindowText(pcText);
	if (m_bDisableParentWindow)
	{
		ASSERT(pWnd);
		pWnd->EnableWindow(FALSE);
	};
};

CPerformingDialogHolder::~CPerformingDialogHolder()
{
	m_poDialog->DestroyWindow();
	delete m_poDialog;
	if (m_bDisableParentWindow)
	{
		m_pWnd->EnableWindow(TRUE);
		m_pWnd->SetFocus();
	};
};

void CPerformingDialogHolder::SetText(LPCTSTR lpNewText)
{
	CString oOldTextString;
	m_poDialog->m_Text.GetWindowText(oOldTextString);
	if(oOldTextString != lpNewText)
	{
		m_poDialog->m_Text.SetWindowText(lpNewText);
		m_poDialog->m_Text.UpdateWindow();
	}
}

BSTR CPerformingDialogHolder::GetTextAUTO() 
{
	ALL_TRY
	{
		CString strResult;
		ASSERT(m_poDialog);
		m_poDialog->m_Text.GetWindowText(strResult);
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPerformingDialogHolder::SetTextAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetText(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

/////////////////////////////////////////////////////////////////////////////
// CPerformingDialog dialog


CPerformingDialog::CPerformingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPerformingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPerformingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPerformingDialog::~CPerformingDialog()
{
	::SetCursor(m_hPreviousCursor);
}

void CPerformingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerformingDialog)
	DDX_Control(pDX, IDC_PERFORMING_TEXT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerformingDialog, CDialog)
	//{{AFX_MSG_MAP(CPerformingDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPerformingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(!::IsWindow(m_animation.m_hWnd))
	{
		m_animation.Create(WS_CHILD | WS_VISIBLE | ACS_CENTER | ACS_TRANSPARENT,CRect(10,35,410,80),this,IDR_AVIPERFORMING);
	}
	CAfxResourceHandleHolder oARHH(_h_NAVOCORE_Instance);
	Animate_OpenEx(m_animation.m_hWnd,_h_NAVOCORE_Instance,MAKEINTRESOURCE(IDR_AVIPERFORMING_RES));
	m_animation.Play(0,(UINT)-1,(UINT)-1);
	m_hPreviousCursor = ::SetCursor(::LoadCursor(NULL,IDC_WAIT));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CProgressDialog::OnQueryEndSession() 
{
	if (!CDialog::OnQueryEndSession())
	{
		return FALSE;
	}
	
	if(m_oQueryEndSessionString.GetLength() != 0)
	{
		AfxMessageBox(m_oQueryEndSessionString,MB_OK | MB_ICONINFORMATION);
	}
	
	return TRUE;
}
