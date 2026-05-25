// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C19CE6C7_2B10_45C7_937C_99EEDD8A6446__INCLUDED_)
#define AFX_STDAFX_H__C19CE6C7_2B10_45C7_937C_99EEDD8A6446__INCLUDED_

//#define _WIN32_WINNT 0x0400
 
#include "..\include\commonstdafx.h"
#include "..\include\array2d.h"

#include <afxcmn.h>
#include <afxhtml.h>
#include <afxrich.h>

#ifdef _DEBUG
	#ifdef _NAVODOTNET
		#include <ostream>
		#include <fstream>
		#include <iomanip>

		using namespace std;
	#endif
#endif
//#define _NDOC_

#define MENU_CMD_INTERNAL_OFFSET	1000
#define ACTIVE_PAGE_IID				  -1


#define VIEW_TYPE_DONTCARE			   0
#define VIEW_TYPE_NAVO				   1
#define VIEW_TYPE_OLEDOC			   2
#define VIEW_TYPE_TOOLBAR			   3
#define VIEW_TYPE_MESSAGE			   4

#define  BLINKINGTIMERID	1
#define DATAREFRESHTIMERID	2

#define BLINKINGINTERVAL    500		//powienien dzieliæ 1000 bez reszty
#define APPLICATION_TIMER_ID	1000


typedef long ndoc_menuid;

#define PULL_ERROR_MESSAGES		//tryb pobierania, zamiast automatycznego wyœwietlania


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C19CE6C7_2B10_45C7_937C_99EEDD8A6446__INCLUDED_)
