/*
	NAVO Sp. z o.o. (2000)
	
	NAVO Enterprise

	class:
		CAppdbApp - APPLICATION database manager
*/

#if !defined(AFX_APPDB_H__B85DA525_D393_4336_8082_009F57D103E0__INCLUDED_)
#define AFX_APPDB_H__B85DA525_D393_4336_8082_009F57D103E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppdbApp
// See appdb.cpp for the implementation of this class
//

class CAppdbApp : public CWinApp
{
public:
	CAppdbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppdbApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAppdbApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPDB_H__B85DA525_D393_4336_8082_009F57D103E0__INCLUDED_)
