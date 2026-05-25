// CNAVOBRMPpg.cpp : Implementation of the CCNAVOBRMPropPage property page class.

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "navobrmctrl2008.h"
#include "CNAVOBRMPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCNAVOBRMPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CCNAVOBRMPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCNAVOBRMPropPage, "NAVOBRMCTRL.NAVOBRMPropPage.1",
	0xa3f1011c, 0x1c15, 0x408a, 0x95, 0xd5, 0x54, 0xcd, 0xeb, 0x7e, 0x9d, 0xd8)



// CCNAVOBRMPropPage::CCNAVOBRMPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCNAVOBRMPropPage

BOOL CCNAVOBRMPropPage::CCNAVOBRMPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_NAVOBRMCTRL2008_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCNAVOBRMPropPage::CCNAVOBRMPropPage - Constructor

CCNAVOBRMPropPage::CCNAVOBRMPropPage() :
	COlePropertyPage(IDD, IDS_NAVOBRMCTRL2008_PPG_CAPTION)
{
}



// CCNAVOBRMPropPage::DoDataExchange - Moves data between page and properties

void CCNAVOBRMPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCNAVOBRMPropPage message handlers
