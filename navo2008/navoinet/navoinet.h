// navoinet.h : main header file for the NAVOINET DLL
//

#if !defined(AFX_NAVOINET_H__1B12854B_C9E9_4B50_8D73_C0EC222A5340__INCLUDED_)
#define AFX_NAVOINET_H__1B12854B_C9E9_4B50_8D73_C0EC222A5340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavoinetApp
// See navoinet.cpp for the implementation of this class
//

class CNavoinetApp : public CWinApp
{
public:
	void InitSockets();

	CNavoinetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavoinetApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoinetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	SCP<CStartupCleanupHolder> m_poSCHSP;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOINET_H__1B12854B_C9E9_4B50_8D73_C0EC222A5340__INCLUDED_)
