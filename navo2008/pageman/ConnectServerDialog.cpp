// ConnectServerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "resource.h"
#include "ConnectServerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectServerDialog dialog


CConnectServerDialog::CConnectServerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectServerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectServerDialog)
	m_ServerString = _T("");
	m_AppNameString = _T("");
	//}}AFX_DATA_INIT
}


void CConnectServerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectServerDialog)
	DDX_Control(pDX, IDC_COMBO_APPNAME, m_cbAppName);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Text(pDX, IDC_SERVER, m_ServerString);
	DDX_CBString(pDX, IDC_COMBO_APPNAME, m_AppNameString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectServerDialog, CDialog)
	//{{AFX_MSG_MAP(CConnectServerDialog)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_CBN_SELCHANGE(IDC_COMBO_APPNAME, OnSelchangeComboAppname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectServerDialog message handlers

void CConnectServerDialog::OnConnect() 
{
	UpdateData();
	CWaitCursor oWC;
	m_cbAppName.ResetContent();

	SCP<IServerClient> poServerClientSP;
	HRESULT hr = CreateRemoteInstance(CLSID_NAVO2001Server,m_ServerString,&poServerClientSP.GetIID(),poServerClientSP);
	if(hr != S_OK)
	{
		m_btOK.EnableWindow(FALSE);
		AfxMessageBox(_T("Po³¹czenie z serwerem [") + m_ServerString + _T("] nieudane. Wpisz inny serwer.\nKod b³êdu=0x") +
			Long2String(hr,16));
		return;
	}
	LPSTR pString = NULL;
	hr = poServerClientSP->EnumRegistryKeys(long(HKEY_LOCAL_MACHINE),_T("SOFTWARE\\NAVO\\NAVO2002\\Applications"),&pString);
	if(hr != S_OK)
	{
		AfxMessageBox(_T("Pobranie listy aplikacji nieudane.\nKod b³êdu=0x") + Long2String(hr,16));
		return;
	}
	CStringArray oStringArray;
	SplitString(CString(pString),oStringArray,'\t',false);
	::NdrOleFree(pString);
	for(long iter =0; iter <= oStringArray.GetUpperBound(); iter++)
	{
		m_cbAppName.AddString(oStringArray[iter]);
	}
	if(oStringArray.GetSize() > 0)
	{
		m_cbAppName.SetCurSel(0);
		m_btOK.EnableWindow(TRUE);
	}
	m_cbAppName.EnableWindow(TRUE);
}

void CConnectServerDialog::OnSelchangeComboAppname() 
{
	UpdateData();
	
	m_btOK.EnableWindow(TRUE);
}
