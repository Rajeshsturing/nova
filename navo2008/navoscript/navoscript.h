// navoscript.h : main header file for the NAVOSCRIPT DLL
//

#if !defined(AFX_NAVOSCRIPT_H__1ECE11DA_063F_4A6A_9069_31B701BEBD0D__INCLUDED_)
#define AFX_NAVOSCRIPT_H__1ECE11DA_063F_4A6A_9069_31B701BEBD0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoscriptApp
// See navoscript.cpp for the implementation of this class
//

class CNavoscriptApp : public CWinApp
{
public:
	CNavoscriptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoscriptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoscriptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOSCRIPT_H__1ECE11DA_063F_4A6A_9069_31B701BEBD0D__INCLUDED_)
