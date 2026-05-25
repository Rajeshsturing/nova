/*
	NAVO Enterprise 2001

	COld_NAVOOleDocView - view presenting ole document
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "navooledocview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
IMPLEMENT_DYNCREATE(COld_NAVOOleDocView,COld_NAVOView__);


BEGIN_MESSAGE_MAP(COld_NAVOOleDocView,COld_NAVOView__)
	//{{AFX_MSG_MAP(COld_NAVOOleDocView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COld_NAVOOleDocView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   COld_NAVOView__::OnDestroy();
   if(GetDocument())
   {
	   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	   {
		  pActiveItem->Deactivate();
		  ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	   }
   }
}

void COld_NAVOOleDocView::OnSetFocus(CWnd* pOldWnd)
{
	if(GetDocument())
	{
		COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
		if (pActiveItem != NULL &&
			pActiveItem->GetItemState() == COleClientItem::activeUIState)
		{
			// need to set focus to this item if it is in the same view
			CWnd* pWnd = pActiveItem->GetInPlaceWindow();
			if (pWnd != NULL)
			{
				pWnd->SetFocus();   // don't call the base class
				return;
			}
		}
	}
	COld_NAVOView__::OnSetFocus(pOldWnd);
}

void COld_NAVOOleDocView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	if(GetDocument())
	{
		COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
		if (pActiveItem != NULL)
		{
			pActiveItem->Close();
		}
		ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}
}

void COld_NAVOOleDocView::OnSize(UINT nType, int cx, int cy)
{
	if(GetDocument())
	{
		COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
		if (pActiveItem != NULL)
		{
			pActiveItem->SetItemRects();
		}
	}
}

*/