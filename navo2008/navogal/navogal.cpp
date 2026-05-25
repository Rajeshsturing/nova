/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer
*/

#include "stdafx.h"
#include "navogal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"..\\..\\lib\\gdiplus\\gdiplus.lib")

BEGIN_MESSAGE_MAP(CNavogalApp, CWinApp)
	//{{AFX_MSG_MAP(CNavogalApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNavogalApp::CNavogalApp()
{
}


CNavogalApp theApp;
