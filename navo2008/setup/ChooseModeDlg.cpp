// ChooseModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "ChooseModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CChooseModeDlg::CChooseModeDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CChooseModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseModeDlg)
	m_nMode = 0;
	m_strServerName = _T("");
	m_strRootDestPath = _T("");
	//}}AFX_DATA_INIT
}


void CChooseModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseModeDlg)
	DDX_Control(pDX, ID_NEXT, m_btNext);
	DDX_Control(pDX, IDC_SERVERTEXT, m_stServerText);
	DDX_Control(pDX, IDC_SERVERNAME, m_etServerName);
	DDX_Radio(pDX, IDC_SINGLE, m_nMode);
	DDX_Text(pDX, IDC_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_ROOTDESTPATH, m_strRootDestPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseModeDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CChooseModeDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_WORKSTATION, OnWorkstation)
	ON_EN_CHANGE(IDC_SERVERNAME, OnChangeServername)
	ON_BN_CLICKED(IDC_SERVER, OnWorkstation)
	ON_BN_CLICKED(IDC_SINGLE, OnWorkstation)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseModeDlg message handlers

void CChooseModeDlg::OnNext() 
{
	UpdateData();
	EndDialog(ID_NEXT);
}

void CChooseModeDlg::OnBack() 
{
	UpdateData();	
	EndDialog(IDC_BACK);
}

void CChooseModeDlg::OnWorkstation() 
{
	UpdateData();
	if(m_nMode == 2)	//workstation
	{
		m_etServerName.ShowWindow(SW_SHOW);
		m_stServerText.ShowWindow(SW_SHOW);
		m_strServerName.TrimLeft();
		m_strServerName.TrimRight();
		m_btNext.EnableWindow(m_strServerName.GetLength() != 0);
	}
	else
	{
		m_etServerName.ShowWindow(SW_HIDE);
		m_stServerText.ShowWindow(SW_HIDE);
		m_btNext.EnableWindow(TRUE);
	}
}

void CChooseModeDlg::OnChangeServername() 
{
	UpdateData();
	m_strServerName.TrimLeft();
	m_strServerName.TrimRight();
	m_btNext.EnableWindow(m_strServerName.GetLength() != 0);
}

void CChooseModeDlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	static BROWSEINFO bi;
	LPITEMIDLIST lpItemIDList = SHBrowseForFolder( &bi);

	if( lpItemIDList != NULL)
	{
		TCHAR pszPath[ 1000];
		SHGetPathFromIDList( lpItemIDList, pszPath);
		
		CoTaskMemFree( lpItemIDList);

		m_strRootDestPath = pszPath;
		EnsureEndingBackslash( m_strRootDestPath);
		UpdateData( false);
	}
}
