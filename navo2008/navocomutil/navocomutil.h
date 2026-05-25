// navocomutil.h : main header file for the NAVOCOMUTIL DLL
//

#if !defined(AFX_NAVOCOMUTIL_H__2CB9F632_B0AE_4412_9A1F_8724694817D8__INCLUDED_)
#define AFX_NAVOCOMUTIL_H__2CB9F632_B0AE_4412_9A1F_8724694817D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavocomutilApp
// See navocomutil.cpp for the implementation of this class
//

class CNavocomutilApp : public CWinApp
{
public:
	CNavocomutilApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavocomutilApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavocomutilApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOCOMUTIL_H__2CB9F632_B0AE_4412_9A1F_8724694817D8__INCLUDED_)
