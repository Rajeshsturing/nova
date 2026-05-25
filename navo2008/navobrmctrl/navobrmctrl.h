#if !defined(AFX_NAVOBRMCTRL_H__C8333A14_BB36_470C_9FA6_D3E47D81F849__INCLUDED_)
#define AFX_NAVOBRMCTRL_H__C8333A14_BB36_470C_9FA6_D3E47D81F849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// navobrmctrl.h : main header file for NAVOBRMCTRL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNavobrmctrlApp : See navobrmctrl.cpp for implementation.

class CNavobrmctrlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOBRMCTRL_H__C8333A14_BB36_470C_9FA6_D3E47D81F849__INCLUDED)
