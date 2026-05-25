/*
	NAVO Enterprise 2020
	setup application
*/

#if !defined(AFX_STDAFX_H__9B445B96_79DA_4737_B296_2222DB60A3E7__INCLUDED_)
#define AFX_STDAFX_H__9B445B96_79DA_4737_B296_2222DB60A3E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//note: it must be explicit values, since here nothing is included yet
#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0603

#define _CRT_SECURE_NO_WARNINGS


#pragma warning(disable:4239)

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>		// for OleVariant
#include <afxmt.h>			// MFC multithread support
#include <comdef.h>			// c++ compiler extras
#include <objidl.h>			

#ifdef _NAVODOTNET
	#include <afxtempl.h>
#else
	#include "..\include\afxtempl.h"		// MFC templates
#endif

#include "..\include\stderrorcode.h"		//standard error codes
#include "..\include\errorsupport.h"		//error support utils
#include "..\include\scp.h"				// famous smart-com-pointers
#include "..\include\sov.h"				// smart OLE VARIANT
#include "..\include\interfacesupport.h"//interface related helpers
#include "..\include\miscutil.h"		// miscelanous utility
#include "..\include\mtutil.h"		// miscelanous utility
#include "..\include\osutil.h"			//OS related utilities
#include "..\include\fileutil.h"		//file related utilities
#include "..\include\navolog.h"
#include "setuperrors.h"
#include "security.h"

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_STDAFX_H__9B445B96_79DA_4737_B296_2222DB60A3E7__INCLUDED_)
