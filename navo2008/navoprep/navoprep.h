// navoprep.h : main header file for the NAVOPREP DLL
//

#if !defined(AFX_NAVOPREP_H__4D910BA8_57AA_4EC6_98BF_E7AF46D01A6B__INCLUDED_)
#define AFX_NAVOPREP_H__4D910BA8_57AA_4EC6_98BF_E7AF46D01A6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoprepApp
// See navoprep.cpp for the implementation of this class
//

class CNavoprepApp : public CWinApp
{
public:
	CNavoprepApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoprepApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoprepApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOPREP_H__4D910BA8_57AA_4EC6_98BF_E7AF46D01A6B__INCLUDED_)
