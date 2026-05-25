// navodef.h : main header file for the NAVODEF DLL
//

#if !defined(AFX_NAVODEF_H__E81699CE_89FF_4467_AAEA_4C9073F9E93C__INCLUDED_)
#define AFX_NAVODEF_H__E81699CE_89FF_4467_AAEA_4C9073F9E93C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavodefApp
// See navodef.cpp for the implementation of this class
//

class CNavodefApp : public CWinApp
{
public:
	CNavodefApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavodefApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavodefApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVODEF_H__E81699CE_89FF_4467_AAEA_4C9073F9E93C__INCLUDED_)
