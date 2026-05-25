// WelcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "WelcomeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CWelcomeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcomeDlg)
	m_nChoice = 0;
	//}}AFX_DATA_INIT
}


void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDlg)
	DDX_Radio(pDX, IDC_AUTOMATIC, m_nChoice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CWelcomeDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_AUTOMATIC, OnAutomatic)
	ON_BN_CLICKED(IDC_MANUAL, OnManual)
	ON_BN_CLICKED(IDC_UNINSTALL, OnUninstall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg message handlers
void CWelcomeDlg::OnNext() 
{
	EndDialog(ID_NEXT);
}

void CWelcomeDlg::OnAutomatic() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CWelcomeDlg::OnManual() 
{
	// TODO: Add your control notification handler code here
	UpdateData();	
}

void CWelcomeDlg::OnUninstall() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
}
