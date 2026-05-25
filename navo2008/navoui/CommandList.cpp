// CommandList.cpp : implementation file
//

#include "stdafx.h"
#include "navoui.h"
#include "CommandList.h"
#include "..\include\internal_h1000.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef ACTIVE_PAGE_IID
#define ACTIVE_PAGE_IID				  -1
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandList

CCommandList::CCommandList()
{
	EnableAutomation();
}

CCommandList::~CCommandList()
{
}

void CCommandList::AddCommand(LPCTSTR lpText,SCP<CHyperLinkInfo> poHLISP)
{
	ASSERT(poHLISP.PointsObject());
	if(!poHLISP->PropertyExists(GVAR_PAGE_IID))
	{
		//zak³adamy ¿e komendy s¹ lokalne w stosunku do strony i ACTIVE_PAGE_IID jest OK
		poHLISP->SetNumProp(GVAR_PAGE_IID,ACTIVE_PAGE_IID);
	}
	m_oCommandArray.Add(CCommandItem(CCommandItem::CIT_ITEM,lpText,poHLISP));
}

void CCommandList::AddSeparator()
{
	if(m_oCommandArray.GetSize() > 0)
	{
		if(m_oCommandArray[m_oCommandArray.GetUpperBound()].m_eCIT != CCommandItem::CIT_SEPARATOR)
		{
			m_oCommandArray.Add(CCommandItem(CCommandItem::CIT_SEPARATOR));
		}
	}
}

void CCommandList::AddSubMenu(LPCTSTR lpText)
{
	m_oCommandArray.Add(CCommandItem(CCommandItem::CIT_SUBMENU,lpText));
}

void CCommandList::EndSubMenu()
{
	m_oCommandArray.Add(CCommandItem(CCommandItem::CIT_ENDSUB));
}

SCP<CHyperLinkInfo> CCommandList::Show(CPoint PtScreenPos,HWND hWnd)
{
	::ClientToScreen(hWnd,&PtScreenPos);
	HMENU hPopupMenu = ::CreatePopupMenu();
	CArray<HMENU,HMENU & > oMenuArray;
	oMenuArray.Add(hPopupMenu);
	for(long iter = 0; iter <= m_oCommandArray.GetUpperBound(); iter++)
	{
		switch(m_oCommandArray[iter].m_eCIT)
		{
		case CCommandItem::CIT_ITEM:
			VERIFY(::AppendMenu(oMenuArray[oMenuArray.GetUpperBound()],MF_STRING,iter+1,m_oCommandArray[iter].m_oTextString));
		break;
		case CCommandItem::CIT_SEPARATOR:
			VERIFY(::AppendMenu(oMenuArray[oMenuArray.GetUpperBound()],MF_SEPARATOR|MF_STRING,iter+1,NULL));
		break;
		case CCommandItem::CIT_SUBMENU:
		{
			HMENU hPopupMenu = ::CreatePopupMenu();
			VERIFY(::AppendMenu(oMenuArray[oMenuArray.GetUpperBound()],MF_POPUP|MF_STRING,(UINT_PTR)hPopupMenu,
				m_oCommandArray[iter].m_oTextString));
			oMenuArray.Add(hPopupMenu);
		}
		break;
		case CCommandItem::CIT_ENDSUB:
			oMenuArray.RemoveAt(oMenuArray.GetUpperBound());
		break;
		default:
			ASSERT(false);
		}
	}

	int nResult = ::TrackPopupMenu(hPopupMenu,TPM_NONOTIFY| TPM_RETURNCMD,PtScreenPos.x,PtScreenPos.y,0,hWnd,NULL);
	if(nResult != 0)
	{
		return m_oCommandArray[nResult-1].m_poHLISP;
	}
	return SCP<CHyperLinkInfo> ();
}

//{{AFX_MSG_MAP(CCommandList)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CCommandList, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCommandList)
	DISP_FUNCTION(CCommandList, "addcommand", AddCommandAUTO, VT_EMPTY, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CCommandList, "addseparator", AddSeparatorAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CCommandList, "addsubmenu", AddSubMenuAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CCommandList, "endsubmenu", EndSubMenuAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CCommandList, "isempty", IsEmptyAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CCommandList, "get", GetCommandAUTO, VT_BOOL, VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICommandList to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {03F057AA-6F43-4EA6-AA2C-E3A596D65044}
static const IID IID_ICommandList =
{ 0x3f057aa, 0x6f43, 0x4ea6, { 0xaa, 0x2c, 0xe3, 0xa5, 0x96, 0xd6, 0x50, 0x44 } };

BEGIN_INTERFACE_MAP(CCommandList, CCmdTarget)
	INTERFACE_PART(CCommandList, IID_ICommandList, Dispatch)
END_INTERFACE_MAP()


void CCommandList::AddCommandAUTO(LPCTSTR lpText, const VARIANT FAR& poHLI) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(poHLI);
		SCP<CHyperLinkInfo> poCommandHLISP;
		switch(oSOV.Type())
		{
		case VT_BSTR:
			poCommandHLISP = ReadHLIFromString(CString(oSOV.GetBStr()));
		break;
		case VT_DISPATCH:
			poCommandHLISP = CHyperLinkInfo::FromIDispatch(oSOV.GetDispatch());
		break;
		case (VT_VARIANT | VT_BYREF):
		{
			VARIANT * pVariant = oSOV.GetVariantRef().pvarVal;
			ASSERT(pVariant);
			AddCommandAUTO(lpText,*pVariant);	//wo³amy siebie, ale ju¿ bef VT_BYREF
			return;
		}
		default:
			ASSERT(false);
		}
		ASSERT(poCommandHLISP.PointsObject());
		AddCommand(lpText,poCommandHLISP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void CCommandList::AddSeparatorAUTO() 
{
	ALL_TRY
	{
		AddSeparator();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCommandList::AddSubMenuAUTO(LPCTSTR lpText) 
{
	ALL_TRY
	{
		AddSubMenu(lpText);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCommandList::EndSubMenuAUTO() 
{
	ALL_TRY
	{
		EndSubMenu();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CCommandList::IsEmptyAUTO() 
{
	ALL_TRY
	{
		return IsEmpty() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CCommandList::GetCommandAUTO(long nItem, VARIANT * lpType, VARIANT * lpText, VARIANT * lpHLI)
{
	ALL_TRY
	{
		nItem--;
		if(nItem < 0 || nItem > m_oCommandArray.GetUpperBound())
		{
			return FALSE;
		}
		*lpType = CSmartOleVariant(long(m_oCommandArray[nItem].m_eCIT)).Detach();
		*lpText = CSmartOleVariant(m_oCommandArray[nItem].m_oTextString).Detach();
		if(m_oCommandArray[nItem].m_poHLISP.PointsObject())
		{
			*lpHLI  = CSmartOleVariant(m_oCommandArray[nItem].m_poHLISP->GetDispatch(true),false).Detach();
		}
		else
		{
			*lpHLI = CSmartOleVariant((IDispatch*)NULL,false).Detach();
		}
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

