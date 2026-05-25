// navoinstall.h : main header file for the NAVOINSTALL DLL
//

#if !defined(AFX_NAVOINSTALL_H__F91383AF_1D46_4841_A77A_799C79288B7D__INCLUDED_)
#define AFX_NAVOINSTALL_H__F91383AF_1D46_4841_A77A_799C79288B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoinstallApp
// See navoinstall.cpp for the implementation of this class
//
#if !defined(NAVO2008)

class CNavoinstallApp : public CWinApp
{
public:
	CNavoinstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoinstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoinstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOINSTALL_H__F91383AF_1D46_4841_A77A_799C79288B7D__INCLUDED_)
