/*
	NAVO Enterprise 2001
	Base view class

	All real views will be derived from it
*/

#include "stdafx.h"

/*

BOOL COld_NAVOView__::PreTranslateMessage(MSG* pMsg)
{
	if(::IsWindow(m_oToolTipCtrl.m_hWnd) && pMsg->hwnd == m_hWnd)
	{
		switch(pMsg->message)
		{
			
		case WM_LBUTTONDOWN:    
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:    
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:    
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			m_oToolTipCtrl.RelayEvent(pMsg);
			break;
		}
	}
	return CView::PreTranslateMessage(pMsg);
}



BEGIN_MESSAGE_MAP(COld_NAVOView__, CView)
	//{{AFX_MSG_MAP(COld_NAVOView__)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT,0,0xFFFF,OnToolTipNotify)
   	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

  

BOOL COld_NAVOView__::OnSetCursor(CWnd*, UINT, UINT) 
{
	ALL_TRY
	{
		if(IsViewSite())
		{
			CClientDC oClientDC(this);
			OnPrepareDC(&oClientDC,NULL);
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			oClientDC.DPtoLP(&point);
			if(!::IsWindow(m_oToolTipCtrl.m_hWnd))
			{
				VERIFY(m_oToolTipCtrl.Create(this,TTS_ALWAYSTIP));
				VERIFY(m_oToolTipCtrl.AddTool(this));
				m_oToolTipCtrl.SetMaxTipWidth(200);
				m_oToolTipCtrl.SetDelayTime(200);
				m_oToolTipCtrl.SendMessage(TTM_SETDELAYTIME, TTDT_INITIAL, 200);
				m_oToolTipCtrl.Activate(TRUE);
			}

			CString oTTString;
			BOOL bResult = GetViewSite()->OnSetCursor(point,oTTString,m_oLastElemRect);
			if(m_oToolTipString != oTTString)
			{
				m_oToolTipString = oTTString;
				m_oToolTipCtrl.Update();
				oClientDC.LPtoDP(&m_oLastElemRect);
			}
			return bResult;
		}
		return FALSE;
	}
	TOP_ALL_CATCH(GetErrorStorage(),TRUE)
}


#ifndef SW_SMOOTHSCROLL
#define SW_SMOOTHSCROLL     0x0010  /* Use smooth scrolling 
#endif

BOOL COld_NAVOView__::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR * pNMHDR = reinterpret_cast<NMHDR *>(lParam);
	ASSERT(pNMHDR);
	
	switch(pNMHDR->code)
	{
	case NM_CLICK:
	{
		//-- NMCLICK * pNMCLICK = reinterpret_cast<NMCLICK *>(pNMHDR);
		DWORD pos = GetMessagePos();
		CPoint pt(LOWORD(pos), HIWORD(pos));
		ScreenToClient(&pt);
		OnLButtonDown(0,pt);
	}
	return TRUE;
	case NM_DBLCLK:
	{
		//-- NMCLICK * pNMCLICK = reinterpret_cast<NMCLICK *>(pNMHDR);
		DWORD pos = GetMessagePos();
		CPoint pt(LOWORD(pos), HIWORD(pos));
		ScreenToClient(&pt);
		OnLButtonDblClk(0,pt);
	}
	return TRUE;
	case NM_KEYDOWN:
	{
		NMKEY * pNMKEY = reinterpret_cast<NMKEY *>(pNMHDR);
		OnKeyDown(pNMKEY->nVKey,0,pNMKEY->uFlags);
	}
	return TRUE;
	case TVN_KEYDOWN:
	{
		NMTVKEYDOWN * pNMKEY = reinterpret_cast<NMTVKEYDOWN *>(pNMHDR);
		OnKeyDown(pNMKEY->wVKey,0,pNMKEY->flags);
	}
	return TRUE;
	}
	return FALSE;
}

BOOL COld_NAVOView__::OnToolTipNotify(UINT id, NMHDR *pNMHDR,LRESULT * pResult)
{
	TOOLTIPTEXT * pToolTipText = reinterpret_cast<TOOLTIPTEXT *>(pNMHDR);
	pToolTipText->uFlags = 0;
	pToolTipText->hinst = (HINSTANCE) NULL;
    pToolTipText->lpszText = (LPTSTR)(LPCTSTR)m_oToolTipString;
	return TRUE;
}

*/
