// navocore2008.h : main header file for the navocore2008 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cnavocore2008App
// See navocore2008.cpp for the implementation of this class
//

class Cnavocore2008App : public CWinApp
{
public:
	Cnavocore2008App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
