// ChooseAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Afxcmn.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "ChooseAppDlg.h"
#include "taskparam.h"
#include "coresetupserv.h"
#include "componentinstaller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define C_COLUMNS 2 
 
extern const TCHAR const * pcWWWRoot;
extern CTaskParam _g_oTaskParam;
extern CNavoLog _g_oNavoLog;

CChooseAppDlg::CChooseAppDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CChooseAppDlg::IDD, pParent)
{
	m_nSelInx = -1;
	//{{AFX_DATA_INIT(CChooseAppDlg)
	//}}AFX_DATA_INIT
}


void CChooseAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseAppDlg)
	DDX_Control(pDX, IDC_APPLIST, m_lcAppList);
	DDX_Control(pDX, ID_NEXT, m_btNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseAppDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CChooseAppDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_LOCALCHOOSE, OnLocalchoose)
	ON_BN_CLICKED(IDC_INETCHOOSE, OnInetchoose)
	ON_NOTIFY(LVN_INSERTITEM, IDC_APPLIST, OnInsertitemApplist)
	ON_NOTIFY(NM_CLICK, IDC_APPLIST, OnClickApplist)
	ON_NOTIFY(NM_DBLCLK, IDC_APPLIST, OnDblclkApplist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CChooseAppDlg::GetCurrentSelection()
{
	int nReturn = -1;
	for( int nItem = 0; nItem < m_lcAppList.GetItemCount(); nItem ++)
	{
		if( (LVIS_FOCUSED | LVIS_SELECTED) & m_lcAppList.GetItemState( nItem, LVIS_FOCUSED | LVIS_SELECTED))
		{
			nReturn = nItem;
		}
	}

	return nReturn;
}

void CChooseAppDlg::OnNext() 
{
	UpdateData();

	m_nSelInx = GetCurrentSelection();

	if(m_nSelInx >= 0)
	{
		EndDialog(ID_NEXT);
	}
}

void CChooseAppDlg::OnBack() 
{
	EndDialog(IDC_BACK);
}

BOOL CChooseAppDlg::OnInitDialog() 
{
	CWizzardDlg::OnInitDialog();
	m_lcAppList.InsertColumn(0, _T("Aplikacja"),LVCFMT_LEFT,120, 0);
	m_lcAppList.InsertColumn(1, _T("Lokalizacja"),LVCFMT_LEFT,190, 1);

	for(long iter = 0; iter <= m_oAppInfoArray.GetUpperBound(); iter += 2)
	{
		AddApplication( m_oAppInfoArray[iter], m_oAppInfoArray[iter + 1]);
	}

	if(m_oAppInfoArray.GetUpperBound() >= 0)
	{
		m_btNext.EnableWindow();	
	}
	return TRUE;
}

extern const TCHAR * _g_pchPackAppPL;

LPSTR DupString(LPSTR lpsz) 
{ 
    int cb = lstrlen(lpsz) + 1; 
    LPSTR lpszNew = (LPSTR) LocalAlloc(LMEM_FIXED, cb); 

    if (lpszNew != NULL) 
        CopyMemory(lpszNew, lpsz, cb); 
    return lpszNew; 
} 

void CChooseAppDlg::OnLocalchoose() 
{
	CString oFilterString = _g_pchPackAppPL + CString(_T(" (*.npx)|*.npx||"));
	CFileDialog oFD(TRUE,"*.npx",NULL,0,oFilterString,this);

	if(oFD.DoModal() != IDOK)
	{
		return;
	}
	
	CString oLocation = oFD.GetPathName();
	int nPos = oLocation.ReverseFind('\\');
	int nPos2 = oLocation.ReverseFind('.');
	CString oAppName = oLocation.Mid(nPos+1,nPos2-nPos-1);

	m_oAppInfoArray.Add(oAppName);
	m_oAppInfoArray.Add(oLocation);

    AddApplication( oAppName, oLocation);
}

HRESULT download_url_2_cache_file(LPCTSTR lpURL,LPTSTR lpFile,bool bUI);

void CChooseAppDlg::OnInetchoose() 
{
	CString oSrcFilePath( pcWWWRoot);
	oSrcFilePath += "packapp\\Applications.lst";

	CString oUniqueFilePath(" ", MAX_PATH);

	CSimpleOleInitHolder oSimpleOleInitHolder;
	_g_oNavoLog << "downloading application list: " + oSrcFilePath;

	HRESULT hr = download_url_2_cache_file( oSrcFilePath, oUniqueFilePath.GetBuffer(0), true);

	_g_oNavoLog << "as: " + oUniqueFilePath;

	if( hr == E_ABORT)
	{
		_g_oNavoLog << "user break" ;
		return;
	}

	if( hr != S_OK)
	{
		_g_oNavoLog << "download failed - download_url_2_cache_file returned error code :" <<  Long2String(hr);

		AfxMessageBox(IDS_stpe_ok + long(stpe_download_failed),MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	CStdioFile oFile;
	oFile.Open( oUniqueFilePath, CFile::modeRead);
	CString oAppName;

	CString oLocation( pcWWWRoot);
	oLocation += "packapp\\";

	while( oFile.ReadString( oAppName))
	{
		if( !oAppName.IsEmpty())
		{	
			m_oAppInfoArray.Add(oAppName);
			m_oAppInfoArray.Add(oLocation+ oAppName + ".npx");
			AddApplication( oAppName, oLocation + oAppName + ".npx");
		}
	}
}

void CChooseAppDlg::AddApplication( const CString &oAppName, const CString &oLocation)
{
    LVITEM pItem[1];

    pItem->mask = LVIF_TEXT | LVIF_STATE;
 	pItem->iItem = m_lcAppList.GetItemCount();
	pItem->state = LVIS_FOCUSED | LVIS_SELECTED;
	pItem->stateMask = LVIS_FOCUSED | LVIS_SELECTED;
    pItem->iSubItem = 0; 
    pItem->pszText = strdup(oAppName);
 
	int nItem = m_lcAppList.InsertItem( pItem);
    pItem->mask = LVIF_TEXT | LVIF_STATE;
 	pItem->iItem = nItem; 
	pItem->state = 0;
	pItem->stateMask = 0;
    pItem->iSubItem = 1; 
    pItem->pszText = strdup(oLocation);
	m_lcAppList.SetItem( pItem);
}

void CChooseAppDlg::OnInsertitemApplist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if( GetCurrentSelection() >= 0)
	{
		m_btNext.EnableWindow(true);
	}

	*pResult = 0;
}

void CChooseAppDlg::OnClickApplist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if( GetCurrentSelection() >= 0)
	{
		m_btNext.EnableWindow(true);
	}

	
	*pResult = 0;
}

void CChooseAppDlg::OnDblclkApplist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_nSelInx = GetCurrentSelection();

	if(m_nSelInx >= 0)
	{
		EndDialog(ID_NEXT);
	}
	
	*pResult = 0;
}
