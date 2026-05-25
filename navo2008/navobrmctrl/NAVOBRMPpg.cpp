// NAVOBRMPpg.cpp : Implementation of the CNAVOBRMPropPage property page class.

#include "stdafx.h"
#include "navobrmctrl.h"
#include "NAVOBRMPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CNAVOBRMPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CNAVOBRMPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CNAVOBRMPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNAVOBRMPropPage, "NAVOBRMCTRL.NAVOBRMPropPage.1",
	0x9cec22d2, 0x5313, 0x45df, 0xa6, 0xa9, 0x98, 0x95, 0x1c, 0x5c, 0x50, 0xb0)


/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMPropPage::CNAVOBRMPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CNAVOBRMPropPage

BOOL CNAVOBRMPropPage::CNAVOBRMPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_NAVOBRM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMPropPage::CNAVOBRMPropPage - Constructor

CNAVOBRMPropPage::CNAVOBRMPropPage() :
	COlePropertyPage(IDD, IDS_NAVOBRM_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CNAVOBRMPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMPropPage::DoDataExchange - Moves data between page and properties

void CNAVOBRMPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CNAVOBRMPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMPropPage message handlers
