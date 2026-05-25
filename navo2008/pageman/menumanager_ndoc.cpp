/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		cndoc_menumanager
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "..\navoobj\treedataprov.h"
#include "menumanager_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void cndoc_menumanager::create_menu_on_stream(SCP<IStream> & rpoStreamSP,HMENU hTopMenu)
{
	ASSERT(hTopMenu != NULL);
	ASSERT(rpoStreamSP.PointsObject());
	set_menu_changed_flag(true);

	m_poMenuCommandTXDPSP = NewSCP<CTreeXMLDataProvider>(new CTreeXMLDataProvider(rpoStreamSP));
	//destroy old
	{
		for(long iter = 0; iter < ::GetMenuItemCount(hTopMenu); iter++)
		{
			HMENU hSubMenu = ::GetSubMenu(hTopMenu,iter);
			if(hSubMenu != HMENU(NULL))
			{
				VERIFY(::DestroyMenu(hSubMenu));
			}
		}
		while(::GetMenuItemCount(hTopMenu) > 0)
		{
			VERIFY(::RemoveMenu(hTopMenu,0,MF_BYPOSITION));
		}
	}

	//create new
	CArray<long,long> oItems;
	m_poMenuCommandTXDPSP->GetChildren(0,oItems);
	for(long iter = 0 ; iter <= oItems.GetUpperBound(); iter++)
	{
		__create_sub_menu(oItems[iter],iter,hTopMenu);
	}
}

void cndoc_menumanager::__create_sub_menu(long nNode,long nPos,HMENU hParentMenu)
{
	ASSERT(m_poMenuCommandTXDPSP.PointsObject());
	
	if(!m_poMenuCommandTXDPSP->Add2Menu(nNode))
	{
		return;
	}

	CArray<long,long> oItems;
	m_poMenuCommandTXDPSP->GetChildren(nNode,oItems);
	MENUITEMINFO mii; 
	mii.cbSize = sizeof(mii);
	SCP<CHyperLinkInfo> poHLISP = m_poMenuCommandTXDPSP->GetNode(nNode);
	CString oString = poHLISP->GetStrProp(PROPC_LABEL);
	if(oString.IsEmpty())
	{
		mii.fType = MFT_SEPARATOR;
	}
	else
	{
		mii.fType = MFT_STRING; 
	}
	mii.dwTypeData = (LPTSTR)(LPCTSTR)oString; 
	mii.cch = oString.GetLength();
	if(oItems.GetSize() > 0)
	{
		HMENU hPopupMenu = ::CreatePopupMenu();
		mii.hSubMenu = hPopupMenu; 
		mii.fMask = MIIM_SUBMENU | MIIM_TYPE; 
		::InsertMenuItem(hParentMenu,nPos, TRUE, &mii); 

		for(long iter = 0 ; iter <= oItems.GetUpperBound(); iter++)
		{
			__create_sub_menu(oItems[iter],iter,hPopupMenu);
		}
	}
	else
	{
		mii.fMask = MIIM_TYPE | MIIM_ID;
		mii.wID = nNode + MENU_CMD_INTERNAL_OFFSET;
		::InsertMenuItem(hParentMenu,nPos, TRUE, &mii); 
	}
}

SCP<CHyperLinkInfo> cndoc_menumanager::get_command(ndoc_menuid nMenuId)
{
	return m_poMenuCommandTXDPSP->GetNode(long(nMenuId));
}


SCP<IDispatch> cndoc_menumanager::get_automation_object()
{
	ASSERT(m_poMenuCommandTXDPSP.PointsObject());
	return m_poMenuCommandTXDPSP->get_automation_object();
}
