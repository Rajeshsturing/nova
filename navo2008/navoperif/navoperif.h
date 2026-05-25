/*
	NAVO Enterprise 2008
	Copyright (c) 2002 NAVO

	NAVOPERIF object supports peripherials (COM etc.)
*/

#if !defined(AFX_NAVOPERIF_H__928E82B9_CFCD_4E4C_B2C5_70495E004A28__INCLUDED_)
#define AFX_NAVOPERIF_H__928E82B9_CFCD_4E4C_B2C5_70495E004A28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNavoperifApp : public CWinApp
{
public:
	CNavoperifApp();
	//{{AFX_VIRTUAL(CNavoperifApp)
	//}}AFX_VIRTUAL
public:
	virtual BOOL InitInstance();
	//{{AFX_MSG(CNavoperifApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOPERIF_H__928E82B9_CFCD_4E4C_B2C5_70495E004A28__INCLUDED_)
