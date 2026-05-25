// InstallComponentsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "..\include\progressgadget.h"
#include "taskparam.h"
#include "componentinstaller.h"
#include "wizzarddlg.h"
#include "coresetupserv.h"
#include "InstallComponentsDlg.h"
#include ".\installcomponentsdlg.h"

extern CTaskParam _g_oTaskParam;
extern CWindows _g_oWindows;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstallComponentsDlg dialog


CInstallComponentsDlg::CInstallComponentsDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CInstallComponentsDlg::IDD, pParent)
{
	m_bTestPerformed = false;
	//{{AFX_DATA_INIT(CInstallComponentsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInstallComponentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallComponentsDlg)
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BACK, m_btBack);
	DDX_Control(pDX, ID_NEXT, m_btNext);
	DDX_Control(pDX, IDC_nec_wininst, m_btWinInst);
	DDX_Control(pDX, IDC_nec_vbscript, m_btVBS);
	DDX_Control(pDX, IDC_nec_mdac, m_btMDAC);
	DDX_Control(pDX, IDC_nec_dotnet,m_btDotNet);
	DDX_Control(pDX, IDC_nec_engine, m_btEngine);
	DDX_Control(pDX, IDC_nec_dcom, m_btDCOM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstallComponentsDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CInstallComponentsDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallComponentsDlg message handlers
BOOL CInstallComponentsDlg::OnInitDialog() 
{
	CWizzardDlg::OnInitDialog();
	SetButtons();
	return TRUE;
}

void CInstallComponentsDlg::OnNext() 
{
	UpdateData();	
	
	for( eNEComponent eNEC = nec_dcom; eNEC < nec_max; eNEC = eNEComponent( long(eNEC) + 1))
	{
		CButton& roButton = GetButton( eNEC);
		roButton.ShowWindow( SW_SHOW);
		
		if( roButton.IsWindowEnabled())
		{
			if( roButton.GetCheck() == 0)
			{
				_g_oTaskParam._set_need_install_state( eNEC, '1');
			}
			else
			{
				_g_oTaskParam._set_need_install_state( eNEC, '2');
			}
		}
		else
		{
			if( roButton.GetCheck() == 0)
			{
				_g_oTaskParam._set_need_install_state( eNEC, '0');
			}
			else
			{
				_g_oTaskParam._set_need_install_state( eNEC, '3');
			}
		}
	}
	
	EndDialog(ID_NEXT);
}

void CInstallComponentsDlg::OnBack() 
{
	UpdateData();	
	EndDialog(IDC_BACK);
}

void CInstallComponentsDlg::SetButtons()
{
	for( eNEComponent eNEC = nec_dcom; eNEC < nec_max; eNEC = eNEComponent( long(eNEC) + 1))
	{
		CButton& roButton = GetButton( eNEC);
		roButton.ShowWindow( SW_SHOW);
		
		TCHAR cState = _g_oTaskParam._get_need_install_state( eNEC);
		
		switch( cState)
		{
		case '0': //no component installation allowed
			{
				roButton.SetCheck(0);
				roButton.EnableWindow( false);
			}
		break;

		case '1': //component installation allowed but not set
			{
				roButton.SetCheck(0);
				roButton.EnableWindow( true);
			}
		break;

		case '2': //component installation allowed and set
			{
				roButton.SetCheck(1);
				roButton.EnableWindow( true);
			}
		break;

		case '3': //component installation required
			{
				roButton.SetCheck(1);
				roButton.EnableWindow( false);
			}
		break;
		}

		roButton.UpdateWindow();
	}

	m_btNext.EnableWindow();
	m_btCancel.EnableWindow();
	m_btBack.EnableWindow();
	
}

CButton& CInstallComponentsDlg::GetButton(enum eNEComponent eNEC)
{
	switch( eNEC)
	{
	case nec_dcom:
		{
			return m_btDCOM;
		}
	case nec_wininst:
		{
			return m_btWinInst;
		}
	case nec_vbscript:
		{
			return m_btVBS;
		}
	case nec_mdac:	 
		{
			return m_btMDAC;
		}
	case nec_dotnet:
		{
			return m_btDotNet;
		}
	case nec_engine:
		{
			return m_btEngine;
		}
	default:
		{
			//todo-leszek error - not implemented
		}
	}
}

void CInstallComponentsDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
}
