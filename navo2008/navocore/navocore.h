// navocore.h : main header file for the NAVOCORE DLL
//

#if !defined(AFX_NAVOCORE_H__02AD5F72_60C4_4E3F_AD44_2F9A47D1604D__INCLUDED_)
#define AFX_NAVOCORE_H__02AD5F72_60C4_4E3F_AD44_2F9A47D1604D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavocoreApp
// See navocore.cpp for the implementation of this class
//

class CNavocoreApp : public CWinApp
{
public:
	CNavocoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavocoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavocoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOCORE_H__02AD5F72_60C4_4E3F_AD44_2F9A47D1604D__INCLUDED_)
