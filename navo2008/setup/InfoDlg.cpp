// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_DESTPATHSTATIC, m_stDestPathStatic);
	DDX_Control(pDX, IDC_MODESTATIC, m_stMode);
	DDX_Control(pDX, IDC_APPSTATIC, m_stApplication);
	DDX_Control(pDX, ID_NEXT, m_btNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers
BOOL CInfoDlg::OnInitDialog() 
{
	CWizzardDlg::OnInitDialog();
	m_stApplication.SetWindowText(m_oAppNameString);
	m_stMode.SetWindowText(m_oModeString);
	m_stDestPathStatic.SetWindowText(m_oDestPathString);
	return TRUE;
}

void CInfoDlg::OnNext() 
{
	EndDialog(ID_NEXT);
}

void CInfoDlg::OnBack() 
{
	EndDialog(IDC_BACK);
}
