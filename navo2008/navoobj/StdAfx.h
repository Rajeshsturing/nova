// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D1F4D644_C1FB_41C2_88ED_8024299D2B87__INCLUDED_)
#define AFX_STDAFX_H__D1F4D644_C1FB_41C2_88ED_8024299D2B87__INCLUDED_

#include "..\include\commonstdafx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"

#ifdef _DEBUG
	#ifdef _NAVODOTNET
		#include <ostream>
		#include <fstream>
		#include <iomanip>

		using namespace std;
	#endif
#endif

#ifdef EOF
#undef EOF
#endif
#import MSADO15_PATH

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D1F4D644_C1FB_41C2_88ED_8024299D2B87__INCLUDED_)
