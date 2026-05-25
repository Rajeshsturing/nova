#pragma once

// navobrmctrl2008.h : main header file for navobrmctrl2008.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// Cnavobrmctrl2008App : See navobrmctrl2008.cpp for implementation.

class Cnavobrmctrl2008App : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

