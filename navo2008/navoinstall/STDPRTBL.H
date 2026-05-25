/////////////////////////////////////////////////////////////////////////////
// STDPRTBL.H	Standard portability declarations
//
// This file is part of the Microsoft InstallWizard library.
// Copyright (C) 1994-1996 Microsoft Corporation. All rights reserved.
//
// This source code is only intended as a supplement to the Microsoft 
// InstallWizard Class Library Reference and related electronic documentation 
// provided with the library. See these sources for detailed information 
// regarding the InstallWizard product.
/////////////////////////////////////////////////////////////////////////////

// This file is part of InstallWizard's Install Class Library. It's use is
// governed by your license agreement. Please see the file license.doc for
// more information.

/*
	File Overview:

	This file contains declarations for making it easier to write MFC code
	that can be compiled for both the 16 and 32 bit compilers. Also it help
	to port to UNICODE.

	This file is included in stdafx.h, so does not need to be included 
	explicitly.

	Also of use in writing 16/32 code is the file intsize.h, which contains 
	memory-model- and compiler-independent signed and unsigned integer types.
*/

#ifndef _STDPRTBL_
	#define _STDPRTBL_

#ifndef LPDWORD
typedef DWORD FAR *LPDWORD;
#endif
#ifndef LPBYTE
typedef BYTE FAR *LPBYTE;
#endif



#ifdef _WIN32

#define DELETE_EXCEPTION(pException) 	(pException)->Delete ()

#else

#define DELETE_EXCEPTION(pException)	delete (pException)

#endif

/////////////////////////////////////
//	Portability Macros for UNICODE
/////////////////////////////////////

#ifdef _UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
	#include "winnls.h"
#endif

//// this is to help note that any LPCSTRs in the the code
//// could be intentially left for ANSI interface to system
//// calls.

//// string macros
#ifdef _UNICODE
	#define STRLEN	wcslen
	#define STRCPY wcscpy
	#define STRNCPY wcsncpy
	#define STRCMP wcscmp
	#define STRICMP _wcsicmp
	#define STRNCMP wcsncmp
	#define STRNICMP _wcsnicmp		
	#define _ITOA _itow
	#define LTOA	_ltow
	#define ATOI	_wtoi
	#define ATOL	_wtol
	#define SPRINTF	swprintf
	#define	VSPRINTF vswprintf
	#define STRDUP _wcsdup
	#define STRTOK wcstok
	#define STRCHR wcschr
#else
	#define STRLEN strlen
	#define STRCPY strcpy
	#define STRNCPY strncpy
	#define STRCMP strcmp
	#define STRICMP stricmp
	#define STRNCMP strncmp
	#define STRNICMP strnicmp	
	#define _ITOA _itoa
	#define LTOA _ltoa
	#define ATOI atoi
	#define ATOL atol
	#define SPRINTF sprintf
	#define VSPRINTF vsprintf	
	#define STRDUP strdup
	#define STRTOK strtok
	#define STRCHR strchr
#endif

//// file macros
#ifdef _UNICODE
	#define _SPLITPATH _wsplitpath
	#define _FULLPATH _wfullpath
	#define _MAKEPATH _wmakepath
	#define _GETCWD _wgetcwd
	#define REMOVE	_wremove
	#define _ACCESS	_waccess
	#define _CHMOD _wchmod
	#define RENAME	_wrename
	#define _STAT	_wstat
	#define _MKDIR	_wmkdir
	#define _CHDIR	_wchdir
	#define _RMDIR _wrmdir
#else
	#define _SPLITPATH _splitpath
	#define _FULLPATH _fullpath
	#define _MAKEPATH _makepath
	#define _GETCWD	_getcwd
	#define REMOVE remove
	#define _ACCESS _access
	#define _CHMOD _chmod
	#define RENAME rename
	#define _STAT _stat
	#define _MKDIR	_mkdir	
	#define _CHDIR _chdir
	#define _RMDIR _rmdir
#endif


//////////////////////////////////////////////////////////////
//	Unicode string conversion routines
//////////////////////////////////////////////////////////////
inline LPTSTR AllocUnicodeFromANSI(const char* lpcAString)
{
#ifdef _UNICODE

	int	nLen = MultiByteToWideChar(CP_ACP,	//determine new string length
									0, 
									lpcAString, 
									strlen(lpcAString), 
									NULL, 
									0);

	if (nLen == 0)	//verify length is not zero
		return NULL;

	LPTSTR 	lpWString = new _TCHAR[nLen+1];	//allocate string
      

    nLen = MultiByteToWideChar(CP_ACP,	//perform the conversion
								0, 
								lpcAString, 
								strlen(lpcAString), 
								lpWString, 
								nLen);

	if (nLen == 0)	//assure that call succeeded
		ASSERT(FALSE);	

	lpWString[nLen] = '\0';	//assure null terminated

	return lpWString;	//return allocated string
#else
	return (char*)lpcAString;	//return the ANSI string if not in Unicode
#endif
}

inline LPSTR AllocANSIFromUnicode(LPCTSTR lpcWString)
{
	#ifdef _UNICODE

	int	nLen = WideCharToMultiByte(CP_ACP,	//determine new string length
									0, 
									lpcWString, 
									wcslen(lpcWString), 
									NULL, 
									0,
									NULL,
									NULL);

	if (nLen == 0)	//verify length is not zero
		return NULL;

	LPSTR 	lpAString = new char[nLen+1];	//allocate string
      

    nLen = WideCharToMultiByte(CP_ACP,	//perform the conversion
								0, 
								lpcWString, 
								wcslen(lpcWString), 
								lpAString, 
								nLen,
								NULL,
								NULL);

	if (nLen == 0)	//assure that call succeeded
		ASSERT(FALSE);	

	lpAString[nLen] = '\0';	//assure null terminated

	return lpAString;	//return allocated string
#else
	return (LPTSTR)lpcWString;	//return the ANSI string
#endif
}

inline void FreeUnicode(LPTSTR lpWString)
{
#ifdef _UNICODE
	delete [] lpWString;	//delete only in Unicode
#endif
}

inline void FreeANSI(LPSTR lpAString)
{
#ifdef _UNICODE
	delete [] lpAString;	//delete only in Unicode
#endif
}

#endif	//_STDPRTBL_