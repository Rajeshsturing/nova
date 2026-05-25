// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BFC90461_B3BE_4793_BD50_D1C2D9CAC5B0__INCLUDED_)
#define AFX_STDAFX_H__BFC90461_B3BE_4793_BD50_D1C2D9CAC5B0__INCLUDED_

#include "..\include\commonstdafx.h"

#ifdef EOF
#undef EOF
#import "..\lib\sqldmo.rll" rename("GetUserName","__GetUserName")
#endif

#pragma warning(disable:4786)		//identifier was truncated to '255' 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BFC90461_B3BE_4793_BD50_D1C2D9CAC5B0__INCLUDED_)
