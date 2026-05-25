// navoexpimp.h : main header file for the NAVOEXPIMP DLL
//

#if !defined(AFX_NAVOEXPIMP_H__D199EDCE_101C_4BC0_B56E_B71E68EA0E59__INCLUDED_)
#define AFX_NAVOEXPIMP_H__D199EDCE_101C_4BC0_B56E_B71E68EA0E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoexpimpApp
// See navoexpimp.cpp for the implementation of this class
//

class CNavoexpimpApp : public CWinApp
{
public:
	CNavoexpimpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoexpimpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoexpimpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOEXPIMP_H__D199EDCE_101C_4BC0_B56E_B71E68EA0E59__INCLUDED_)
