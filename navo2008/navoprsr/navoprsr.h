// navoprsr.h : main header file for the NAVOPRSR DLL
//

#if !defined(AFX_NAVOPRSR_H__979BC6A3_9DB8_49E9_BF69_8D660D65077B__INCLUDED_)
#define AFX_NAVOPRSR_H__979BC6A3_9DB8_49E9_BF69_8D660D65077B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoprsrApp
// See navoprsr.cpp for the implementation of this class
//

class CNavoprsrApp : public CWinApp
{
public:
	CNavoprsrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoprsrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoprsrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOPRSR_H__979BC6A3_9DB8_49E9_BF69_8D660D65077B__INCLUDED_)
