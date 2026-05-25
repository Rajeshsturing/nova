// navobrman.h : main header file for the NAVOBRMAN DLL
//

#if !defined(AFX_NAVOBRMAN_H__36E5D9C8_E940_4B81_BBB3_B2FD9DD81A1B__INCLUDED_)
#define AFX_NAVOBRMAN_H__36E5D9C8_E940_4B81_BBB3_B2FD9DD81A1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavobrmanApp
// See navobrman.cpp for the implementation of this class
//

class CNavobrmanApp : public CWinApp
{
public:
	CNavobrmanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavobrmanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavobrmanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOBRMAN_H__36E5D9C8_E940_4B81_BBB3_B2FD9DD81A1B__INCLUDED_)
