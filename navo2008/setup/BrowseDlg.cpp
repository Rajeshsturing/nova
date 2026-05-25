// BrowseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "setup.h"
#include "BrowseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowseDlg dialog


CBrowseDlg::CBrowseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowseDlg)
	m_nCopyMethod = 0;
	m_edMessage = _T("");
	//}}AFX_DATA_INIT
}


void CBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowseDlg)
	DDX_Radio(pDX, IDC_LOCAL, m_nCopyMethod);
	DDX_Text(pDX, IDC_EDIT1, m_edMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowseDlg, CDialog)
	//{{AFX_MSG_MAP(CBrowseDlg)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseDlg message handlers

BOOL CBrowseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bDownload = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CBrowseDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	switch (m_nCopyMethod)
	{
	case 0:
		{
			CString oFilterString = "Wszystkie pliki" + CString(_T(" (*.*)|*.*||"));
			CFileDialog oFileDialog(TRUE,"*.*",NULL,0,oFilterString,this);

			if (oFileDialog.DoModal () == IDOK)
			{
				CString oPath = oFileDialog.GetPathName ();
				int nPos = oPath.ReverseFind ('\\');

				m_strDir = oPath.Mid (0, nPos + 1);
				m_bDownload = false;
				m_bDownloadAll = false;
				EndDialog (IDOK);
			}	
		} 
		break;

	case 1:
		{
			m_bDownload = true;
			m_bDownloadAll = false;
			EndDialog (IDOK);
		}
		break;

	case 2:
		{
			m_bDownload = true;
			m_bDownloadAll = true;
			EndDialog (IDOK);
		}
		break;
	}

}
