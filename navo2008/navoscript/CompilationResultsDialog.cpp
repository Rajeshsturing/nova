// CompilationResultsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CompilationResultsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompilationResultsDialog dialog


CCompilationResultsDialog::CCompilationResultsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCompilationResultsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompilationResultsDialog)
	m_oResultsString = _T("");
	//}}AFX_DATA_INIT
}


void CCompilationResultsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompilationResultsDialog)
	DDX_Control(pDX, IDC_RESULTSEDIT, m_edResults);
	DDX_Text(pDX, IDC_RESULTSEDIT, m_oResultsString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompilationResultsDialog, CDialog)
	//{{AFX_MSG_MAP(CCompilationResultsDialog)
	ON_BN_CLICKED(IDC_SHOWRESULTS, OnShowresults)
	ON_BN_CLICKED(IDC_SHOWSOURCE, OnShowsource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompilationResultsDialog message handlers

void CCompilationResultsDialog::OnShowresults() 
{
	m_edResults.SetWindowText(m_oResultsString);
}

void CCompilationResultsDialog::OnShowsource() 
{
	m_edResults.SetWindowText(m_oSourceString);
}
