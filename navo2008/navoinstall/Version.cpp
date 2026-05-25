/////////////////////////////////////////////////////////////////////////////
// VERSION.CPP		CVersion implementation
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


//////////////////////////////////////
// Includes
//////////////////////////////////////

#include "stdafx.h"		// included by all compilands
#include "version.h"	// external declarations for this file
#include "winver.h"

//////////////////////////////////////
// Constructors, destructors, inits
//////////////////////////////////////

CVersion::CVersion ()
{
	m_pData = NULL;
}

CVersion::~CVersion ()
{
	if (m_pData != NULL)
	{
		delete [] m_pData;
	}
}
			


BOOL CVersion::Load (LPCTSTR lpszPath)	// throws CMemoryException
{
	DWORD		dwHandle;
	DWORD		dwSize;
	BOOL		bSuccess;
	dwSize = ::GetFileVersionInfoSize ((LPTSTR) lpszPath,
									   &dwHandle);
	if (dwSize == 0)
		return FALSE;
		
	m_pData = new BYTE [dwSize + 1];	
	bSuccess = ::GetFileVersionInfo ((LPTSTR) lpszPath, dwHandle, dwSize, m_pData);
	return bSuccess;
}


//////////////////////////////////////
// Get State
//////////////////////////////////////

BOOL CVersion::GetFileVersion (WORD* pwMajorVersion, 
					 	 	   WORD* pwMinorVersion, 
					 	 	   WORD* pwThirdVersion /*= NULL*/,
					 	 	   WORD* pwFourthVersion /*= NULL*/)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		*pwMajorVersion = HIWORD (FixedInfo.dwFileVersionMS);
		*pwMinorVersion = LOWORD (FixedInfo.dwFileVersionMS);
		if (pwThirdVersion != NULL)
		{
			*pwThirdVersion = HIWORD (FixedInfo.dwFileVersionLS);
		}
		if (pwFourthVersion)
		{
			*pwFourthVersion = LOWORD (FixedInfo.dwFileVersionLS);
		}
		return TRUE;
	}
	return FALSE;		
}					 	 


BOOL CVersion::GetProductVersion (WORD* pwMajorVersion, 
					 	 	      WORD* pwMinorVersion, 
					 	 	      WORD* pwThirdVersion /*= NULL*/,
					 	 	      WORD* pwFourthVersion /*= NULL*/)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		*pwMajorVersion = HIWORD (FixedInfo.dwProductVersionMS);
		*pwMinorVersion = LOWORD (FixedInfo.dwProductVersionMS);
		if (pwThirdVersion != NULL)
		{
			*pwThirdVersion = HIWORD (FixedInfo.dwProductVersionLS);
		}
		if (pwFourthVersion)
		{
			*pwFourthVersion = LOWORD (FixedInfo.dwProductVersionLS);
		}
		return TRUE;
	}
	return FALSE;		
}					 	 


BOOL CVersion::GetFileFlags (DWORD& rdwFlags)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		rdwFlags = FixedInfo.dwFileFlags;
		return TRUE;
	}
	else
		return FALSE;	
}


BOOL CVersion::GetFileOS (DWORD& rdwOS)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		rdwOS = FixedInfo.dwFileOS;
		return TRUE;
	}
	else
		return FALSE;	
}


BOOL CVersion::GetFileType (DWORD& rdwType)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		rdwType = FixedInfo.dwFileType;
		return TRUE;
	}
	else
		return FALSE;	
}


BOOL CVersion::GetFileSubtype (DWORD& rdwType)
{
	VS_FIXEDFILEINFO	FixedInfo;
	
	if (GetFixedInformation	(FixedInfo))
	{
		rdwType = FixedInfo.dwFileSubtype;
		return TRUE;
	}
	else
		return FALSE;	
}


BOOL CVersion::GetCompanyName (CString& rCompanyName)
{
	return GetStringInformation (_T("CompanyName"), rCompanyName);
}

BOOL CVersion::GetFileDescription (CString& rFileDescription)
{
	return GetStringInformation (_T("FileDescription"), rFileDescription);
}

BOOL CVersion::GetLegalCopyright (CString& rLegalCopyright)
{
	return GetStringInformation (_T("LegalCopyright"), rLegalCopyright);
}


//////////////////////////////////////
// Implementation
//////////////////////////////////////


BOOL CVersion::GetFixedInformation (VS_FIXEDFILEINFO& rFixedInfo)
{
	BOOL bSuccess = FALSE;
	UINT nLength;
	VS_FIXEDFILEINFO*	pFixedInfo; //

	ASSERT (m_pData != NULL);
	
	if (m_pData != NULL)
	{
		bSuccess = ::VerQueryValue (m_pData, _T("\\"),(void **) &pFixedInfo, &nLength);
	}
		
	if (bSuccess)
	{
		memcpy (&rFixedInfo, pFixedInfo, sizeof (VS_FIXEDFILEINFO));
	}
	return bSuccess;							
}

BOOL CVersion::GetStringInformation (LPCTSTR lpszKey, CString& rValue)
{
	BOOL		bSuccess;
	DWORD*		pdwTranslation;
	UINT		nLength;
	CString	Key;
	LPCTSTR		lpszValue;
	
	ASSERT (m_pData != NULL);	
	if (m_pData == NULL)
		return FALSE;
		
	bSuccess =	::VerQueryValue(m_pData, _T("\\VarFileInfo\\Translation"), 
								(void**) &pdwTranslation, &nLength);
	if (!bSuccess)
		return FALSE;

	Key.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
				 LOWORD (*pdwTranslation), HIWORD (*pdwTranslation),
				 lpszKey);
	_TCHAR	szKey [400];	// VerQueryValue erroneously takes a non-const string
	strcpy (szKey, Key);
	bSuccess = ::VerQueryValue (m_pData, szKey, (void**) &lpszValue, &nLength);

	if (!bSuccess)
		return FALSE;
		
	rValue = lpszValue;
	return TRUE;
}


BOOL CVersion::operator> (CVersion& rVersion)	// throws CVersionException
{
	WORD		nThis1, nThis2, nThis3, nThis4;
	WORD		nVersion1, nVersion2, nVersion3, nVersion4;
	
	
	GetFileVersion (&nThis1, &nThis2, &nThis3, &nThis4);
	rVersion.GetFileVersion (&nVersion1, &nVersion2, &nVersion3, &nVersion4);
	
	if (nThis1 > nVersion1)
		return TRUE;
	else if (nThis1 < nVersion1)
		return FALSE;

	if (nThis2 > nVersion2)
		return TRUE;
	else if (nThis2 < nVersion2)
		return FALSE;

	if (nThis3 > nVersion3)
		return TRUE;
	else if (nThis3 < nVersion3)
		return FALSE;

	if (nThis4 > nVersion4)
		return TRUE;
	else	
		return FALSE;
}

	
CString CVersion::GetFileVersion()
{
	WORD w1 = 0,w2 = 0,w3 = 0,w4 = 0;
	CString oString("0.0.0.0");

	if(GetFileVersion(&w1,&w2,&w3,&w4))
	{
		oString.Format("%d.%d.%d.%d",w1,w2,w3,w4);
	}
	return oString;
}

bool IsFileVersionNewer(LPCTSTR pcExistingFile,LPCTSTR pcCandidateFile)
{
	CVersion	ExistingVersion;
	CVersion	ThisVersion;
	BOOL		bExistingVersion;
	BOOL		bThisVersion;
	
	bExistingVersion = ExistingVersion.Load(pcExistingFile);
	bThisVersion = ThisVersion.Load (pcCandidateFile);
	if (bExistingVersion && !bThisVersion)
	{
		return false;
	}
	else if (bThisVersion && !bExistingVersion)
	{
		return true;
	}	
	else if (bThisVersion && bExistingVersion)
	{
		return ThisVersion > ExistingVersion != FALSE;
	}
	else
	{
		CFileStatus oExistingFileStatus;
		CFileStatus oCandidateFileStatus;
		if(!CFile::GetStatus(pcExistingFile,oExistingFileStatus))
		{
			return true;
		}
		VERIFY(CFile::GetStatus(pcCandidateFile,oCandidateFileStatus));
		return (oCandidateFileStatus.m_ctime > oExistingFileStatus.m_ctime) != FALSE;
	}		
}
