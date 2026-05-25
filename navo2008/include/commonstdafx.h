/*
	NAVO Sp. z o.o. (2001 - 2015)
	
	NAVO Enterprise

	commonstdafx.h

	include at begin of every stdafx.h

*/


#define _DEVELOPER_EDITION_
//#define _BETA_EDITION_

#define DCOM_AUTH_LEVEL	RPC_C_AUTHN_LEVEL_CALL


#if defined(_DEVELOPER_EDITION_) && defined(_BETA_EDITION_)
	#error define either BETA or DEVELOPER but no both same time
#endif
#if defined(_DEBUG) && !defined(_DEVELOPER_EDITION_)
	#error define _DEVELOPER_EDITION_ for DEBUG builds
#endif


#pragma warning(disable:4786)	//identifier was truncated to '255' characters in the debug information
#pragma warning(error:4800) //niejawna konwersja SCP<IDispatch> do boolean -> nieprawid³owy kod

//note: it must be explicit values, since here nothing is included yet
#define _WIN32_WINNT 0x0600
#define _WIN32_IE 0x0700

#define _CRT_SECURE_NO_WARNINGS

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define MSADO15_PATH "C:\Program Files\Common Files\System\ado\msado15.dll" 

#ifndef NAVO2008
#include "C:\navo2001\include\basetsd.2001.h"
#else
#include <basetsd.h>
#endif
//#include <typeinfo.h>		// for RTTI (i.e. dynamic_cast)
#include <afxwin.h>         // MFC core and standard components
#include <comdef.h>			// c++ compiler extras
#include <afxtempl.h>		// MFC templates
#include <afxdisp.h>		// for OleVariant
#include <afxmt.h>			// MFC multithread support
#include <afxctl.h>			// For Event Map things
#include <afxole.h>
#include <afxdocob.h>
#include <atlconv.h>


#pragma warning(disable:4355)	//'this' : used in base member initializer list
#pragma warning(disable:4239)	//nonstandard extension used : 'token' : conversion from 'type' to 'type'
#pragma warning(disable:4711)	//function 'function' selected for inline expansion
#pragma warning(error:4150)		//deletion of pointer to incomplete type 'type'; no destructor called


//NAVO standard
#ifndef NAVO2008
#ifndef _NAVODOTNET
#ifndef _ARRAY_BY_NAVO_
#error Uzyj AFXTEMPL.H zmodyfikowanego w NAVO 
#endif

#ifndef _LIST_BY_NAVO_
#error Uzyj AFXTEMPL.H zmodyfikowanego w NAVO 
#endif
#endif
#endif

#include "stderrorcode.h"		//standard error codes
#include "errorsupport.h"		//error support utils
#include "scp.h"				// famous smart-com-pointers
#include "sov.h"				// smart OLE VARIANT
#include "interfacesupport.h"	//interface related helpers

#include "mtutil.h"			// multithread primitives
#include "miscutil.h"		// miscelanous utility
#include "osutil.h"			// OS related utility
#include "fileutil.h"		// file related utility
#include "navooleutil.h"	// OLE related utils

#include "hyperlink.h"		// CHyperLink class


#include "idtss.h"
#include "navosqltconst.h"

#include "fileutil_inl.h"		// file related utility (inlines)

//#define UD_APARTMENT
