/////////////////////////////////////////////////////////////////////////////
// VERSION.H		CVersion interface
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

#ifndef _VERSION_H_
#define _VERSION_H_

#ifdef _WIN32
#include "winver.h"		// for VS_FIXEDFILEINFO, various flags
#else
#include "ver.h"		// for VS_FIXEDFILEINFO, various flags
#endif

class CVersion
{

//////////////////////////////////////
// Constructors, destructors, inits
//////////////////////////////////////
public:
	CVersion ();
	virtual ~CVersion ();
	BOOL Load (LPCTSTR lpszPath);

//////////////////////////////////////
// Operators
//////////////////////////////////////
	CString GetFileVersion();

public:
	BOOL operator> (CVersion& rVersion); 	// throws CVersionException
	
	
//////////////////////////////////////
// Accessors
//////////////////////////////////////
public:
	BOOL GetFileVersion (WORD* pwMajorVersion, 
					 	 WORD* pwMinorVersion, 
					 	 WORD* pwThirdVersion = NULL,
					 	 WORD* pwFourthVersion = NULL);
	BOOL GetProductVersion (WORD* pwMajorVersion, 
					 	    WORD* pwMinorVersion, 
					 	    WORD* pwThirdVersion = NULL,
					 	    WORD* pwFourthVersion = NULL);
	BOOL GetFileFlags (DWORD& rdwFlags);
	BOOL GetFileOS (DWORD& rdwOS);
	BOOL GetFileType (DWORD& rdwType);
	BOOL GetFileSubtype (DWORD& rdwType);	

	BOOL GetCompanyName (CString& rCompanyName);
	BOOL GetFileDescription (CString& rFileDescription);
	BOOL GetLegalCopyright (CString& rLegalCopyright);

//////////////////////////////////////
// Implementation
//////////////////////////////////////

protected:
	BOOL GetFixedInformation (VS_FIXEDFILEINFO& rFixedInfo);
	BOOL GetStringInformation (LPCTSTR lpszKey, CString& rValue);

//////////////////////////////////////
// Member Data
//////////////////////////////////////

protected:
	BYTE*		m_pData;
	DWORD		dwHandle;
};

bool IsFileVersionNewer(LPCTSTR pcExistingFile,LPCTSTR pcCandidateFile);

#endif	// !_VERSION_H_

