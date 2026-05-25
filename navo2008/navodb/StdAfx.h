// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3A33CF12_A7C8_4809_99E6_440FE1423430__INCLUDED_)
#define AFX_STDAFX_H__3A33CF12_A7C8_4809_99E6_440FE1423430__INCLUDED_

#include "..\include\commonstdafx.h"
#include "..\include\navolog.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\navothread.h"

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

#endif // !defined(AFX_STDAFX_H__3A33CF12_A7C8_4809_99E6_440FE1423430__INCLUDED_)
