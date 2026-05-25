// pageman.h : main header file for the PAGEMAN DLL
//

#if !defined(AFX_PAGEMAN_H__9E850C77_825E_4267_BD1D_08CE3386D1B0__INCLUDED_)
#define AFX_PAGEMAN_H__9E850C77_825E_4267_BD1D_08CE3386D1B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPagemanApp
// See pageman.cpp for the implementation of this class
//

class CPagemanApp : public CWinApp
{
public:
	CPagemanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagemanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPagemanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMAN_H__9E850C77_825E_4267_BD1D_08CE3386D1B0__INCLUDED_)
