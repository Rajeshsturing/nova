// LoginAsUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LoginAsUserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginAsUserDlg dialog


CLoginAsUserDlg::CLoginAsUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginAsUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginAsUserDlg)
	m_oDomainString = _T("");
	m_oPasswordString = _T("");
	m_oUserString = _T("");
	//}}AFX_DATA_INIT
}


void CLoginAsUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginAsUserDlg)
	DDX_Text(pDX, IDC_DOMAIN, m_oDomainString);
	DDX_Text(pDX, IDC_PASSWORD, m_oPasswordString);
	DDX_Text(pDX, IDC_USER, m_oUserString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginAsUserDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginAsUserDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginAsUserDlg message handlers
