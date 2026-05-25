/////////////////////////////////////////////////////////////////////////////
// REGISTRY.CPP		Implementation for CRegistryKey, CRegistryString, etc.
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

  This file declares several classes designed to make it easier to work with
  the registry. There is a full win32 API for working with the registry, but
  using this API involves a fair amount of repetitive code and error checking.
  These classes are an attempt to encapsulate the common registry tasks.

  The base class is called CRegistryKey. This is a relatively-straightforward
  C++ "wrapper" around the registry API. The primary object data for 
  CRegistryKey is an HKEY for the open registry key. Using CRegistryKey is 
  much like using the API, but with these advantages:

	- automatic closing of open hkeys at destruction
	- use of overloading and optional arguments simplifies interface
	- use of CStrings simplifies returning of string values
	- when loading a value, ensuring that the proper data type was found
	- ensuring that CString returns are properly sized.

  Derived from CRegistryKey are CRegistryString, CRegistryDWord, etc.,
  designed for working with particular data types stored in the registry.
  These classes present a different view of the registry, letting you
  think of these classes as "persistent" data. For example, CRegistryStrings
  are constructed with arguments for the key, subkey and value name, and 
  automatically load the value in the registry. CRegistryString has an 
  operator (LPCTSTR), so you can use a CRegistryString anywhere you'd
  use the value of a string or CString. CRegistry also has an operator =
  which takes a (LPCTSTR), so you can set the registry value simply
  by setting a CRegistryString value. When the CRegistryString object is
  destroyed, any modified values are saved to the registry.

  This file is defined for _WIN32 only.
*/

//////////////////////////////////////
// Includes, forwards
//////////////////////////////////////

#include "stdafx.h"		// included by all compilands

#ifdef _WIN32

#include "registry.h"	// external declarations for this file
#include <limits.h>		// for _UI16_MAX


/////////////////////////////////////////////////////////////////////////////
// CRegistryKey
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////
// Constructors, Destructors, Inits
//////////////////////////////////////

CRegistryKey::CRegistryKey()
/*
	Effect:		Constructor for CRegistryKey. Zero out all data members.
				Most important is m_hKey; the value of NULL is used to
				indicate that this CRegistryKey has not been opened.
*/
{
	m_nLastError = ERROR_SUCCESS;
	m_hKey = NULL;
	m_nSubKey = 0;
}


// virtual
CRegistryKey::~CRegistryKey()
/*
	Effect:		Destructor for CRegistryKey. If this key is still open,
				close it.
*/
{
	if (m_hKey != NULL)
		CloseKey();
}


//////////////////////////////////////
// Key-related operations
//////////////////////////////////////

BOOL CRegistryKey::OpenKey (HKEY hKey,
							LPCTSTR lpszSubKey /*= NULL*/,
						    REGSAM samDesired /*= KEY_ALL_ACCESS*/)
{
	// Check arguments
	ASSERT_VALID (this);
	ASSERT (hKey != NULL);

	// If you get this assertion, then you've called OpenKey or
	// CreateKey with this CRegistryKey without an intervening
	// CloseKey call.
	ASSERT (m_hKey == NULL);

	m_nLastError = ::RegOpenKeyEx (hKey,		// base key
								   lpszSubKey,	// optional subkey
								   0,			// reserved
								   samDesired,	// security requested
								   &m_hKey);
	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::CreateKey (HKEY hKey,
 							  LPCTSTR lpszSubKey /*= NULL*/,
							  LPCTSTR lpszClass /*= NULL*/,
							  REGSAM samDesired /*= KEY_ALL_ACCESS*/,
							  LPSECURITY_ATTRIBUTES lpSecurityAttributes /*= NULL*/)
{
	// Check arguments
	ASSERT_VALID (this);
	ASSERT (hKey != NULL);

	// If you get this assertion, then you've called OpenKey or
	// CreateKey with this CRegistryKey without an intervening
	// CloseKey call.
	ASSERT (m_hKey == NULL);

	unsigned long	nCreatedKey;
	m_nLastError = ::RegCreateKeyEx (hKey,			// base key
									lpszSubKey,		// optional subkey
									0,				// reserved
									(LPTSTR) lpszClass,
									0,				// options
									samDesired,
									NULL,
									&m_hKey,
									&nCreatedKey);
	return (m_nLastError == ERROR_SUCCESS);
}



BOOL CRegistryKey::DeleteKey (HKEY hKey,
							  LPCTSTR lpszSubKey /*= NULL*/)
{
	m_nLastError = ::RegDeleteKey (hKey, lpszSubKey);
	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::CloseKey ()
{
	if (m_hKey == NULL)
		return TRUE;

	m_nLastError = ::RegCloseKey (m_hKey);
	m_hKey = NULL;
	return (m_nLastError == ERROR_SUCCESS);
}

BOOL CRegistryKey::GetNextSubKey (CString& rSubKey,
								  CString& rClass)
{
	ASSERT (m_hKey != NULL);

	for (DWORD dwStringLength = 256; 
		 dwStringLength < _UI16_MAX; 
		 dwStringLength <<= 2)
	{
		DWORD		dwKeyLength = dwStringLength;
		DWORD		dwClassLength = dwStringLength;
		FILETIME	ftime;

		m_nLastError = ::RegEnumKeyEx (m_hKey,
									   m_nSubKey,
									   rSubKey.GetBuffer (dwStringLength),
									   &dwKeyLength,
									   0,				// reserved
									   rClass.GetBuffer (dwStringLength),
									   &dwClassLength,
									   &ftime);

		rSubKey.ReleaseBuffer(dwKeyLength);
		rClass.ReleaseBuffer(dwClassLength);

		if ((m_nLastError != ERROR_SUCCESS) &&
			(m_nLastError != ERROR_NO_MORE_ITEMS))
			break;

		if ((dwKeyLength <= dwStringLength) &&
			(dwClassLength <= dwStringLength))
			break;
	}	// for

	m_nSubKey++;	// increment for next time
	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::DeleteValue (LPCTSTR lpszValueName /*= NULL*/)
{
	ASSERT (m_hKey != NULL);
	m_nLastError = ::RegDeleteValue (m_hKey, lpszValueName);
	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::GetValue (CString& rText)
{
	return GetValue (NULL, rText);
}


BOOL CRegistryKey::GetValue (LPCTSTR lpszValueName, CString& rText)
{
	DWORD		dwType;
	DWORD		cbData;

	ASSERT (m_hKey != NULL);
	m_nLastError = ::RegQueryValueEx (m_hKey,
								lpszValueName,
								0,
								&dwType,
								NULL,
								&cbData);
	if (m_nLastError != ERROR_SUCCESS)
		return FALSE;

	if (dwType != REG_SZ)
	{
		m_nLastError = ERROR_INVALID_DATATYPE;
		return FALSE;
	}

	m_nLastError = ::RegQueryValueEx (m_hKey,
								lpszValueName,
								0,
								&dwType,
								(LPBYTE) &(*(rText.GetBuffer (cbData))),
								&cbData);
	rText.ReleaseBuffer ();

	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::SetValue (LPCTSTR lpszValue)
{
	return SetValue (NULL, lpszValue);
}


BOOL CRegistryKey::SetValue (LPCTSTR lpszValueName,
							  LPCTSTR lpszValue)
{
	CString Value = lpszValue;
	ASSERT (m_hKey != NULL);
	m_nLastError = ::RegSetValueEx (m_hKey,
							lpszValueName,
							0,				// reserved
							REG_SZ,
							(CONST BYTE* ) &(*lpszValue),
							(Value.GetLength() + 1)*sizeof(_TCHAR));
	return (m_nLastError == ERROR_SUCCESS); 	
}


BOOL CRegistryKey::GetValue (DWORD& rdwValue)
{
	return GetValue (NULL, rdwValue);
}


BOOL CRegistryKey::GetValue (LPCTSTR lpszValueName, DWORD& rdwValue)
{
	DWORD		dwType;
	DWORD		cbData = sizeof (DWORD);
	DWORD		dwValue;

	ASSERT (m_hKey != NULL);
	m_nLastError = ::RegQueryValueEx (m_hKey,
								lpszValueName,
								0,
								&dwType,
								(LPBYTE) &dwValue,
								&cbData);
	if (m_nLastError != ERROR_SUCCESS)
		return FALSE;

	if (dwType != REG_DWORD)
	{
		m_nLastError = ERROR_INVALID_DATATYPE;
		return FALSE;
	}

	rdwValue = dwValue;
	return (m_nLastError == ERROR_SUCCESS);
}


BOOL CRegistryKey::SetValue (DWORD dwValue)
{
	return SetValue (NULL, dwValue);
}


BOOL CRegistryKey::SetValue (LPCTSTR lpszValueName,
							 DWORD dwValue)
{
	ASSERT (m_hKey != NULL);
	m_nLastError = ::RegSetValueEx (m_hKey,
							lpszValueName,
							0,				// reserved
							REG_DWORD,
							(CONST BYTE*) &dwValue,
							sizeof (DWORD));
	return (m_nLastError == ERROR_SUCCESS); 
}


#ifdef _DEBUG
// static
LPCTSTR const szTestSubKey			 = _T("Software\\Microsoft\\Test");
LPCTSTR const szTestStringValueName = _T("String Value Name");
LPCTSTR const szTestStringValue	 = _T("String Value");
DECLARE_STRING_REGISTRY (CTest, HKEY_CURRENT_USER,
						 szTestSubKey,
						 szTestStringValueName,
						 _T("Default"));

void CRegistryKey::UnitTest()
{
	CRegistryKey	Key;
	CRegistryKey	SameKeyAsTest;
	CString			Value;

	ASSERT (Key.CreateKey (HKEY_CURRENT_USER,
						   szTestSubKey));
	ASSERT (Key.SetValue (szTestStringValueName,
						  szTestStringValue));
	ASSERT (Key.GetValue (szTestStringValueName,
						  Value));
	ASSERT (Value == szTestStringValue);
	ASSERT (Key.CloseKey ());
	ASSERT (Key.DeleteKey (HKEY_CURRENT_USER,
						   szTestSubKey));
	ASSERT (!Key.OpenKey (HKEY_CURRENT_USER,
						  szTestSubKey));

	{
		CTest			Test;
		CString			TestValue = Test;
		ASSERT (TestValue == "Default");
		Test = _T("New Value");
		
		ASSERT (!SameKeyAsTest.OpenKey (HKEY_CURRENT_USER,
									szTestSubKey));
	}

	CString			TestValue2;
	ASSERT (SameKeyAsTest.OpenKey (HKEY_CURRENT_USER,
									szTestSubKey));
	ASSERT (SameKeyAsTest.GetValue (szTestStringValueName,
									TestValue2));
	ASSERT (TestValue2 == _T("New Value"));
}
#endif


/////////////////////////////////////////////////////////////////////////////
// CRegistryString
/////////////////////////////////////////////////////////////////////////////


CRegistryString::CRegistryString (HKEY hKey,
								  LPCTSTR lpszSubKey /*= NULL*/,
								  LPCTSTR lpszValueName /*= NULL*/,
								  LPCTSTR lpszDefaultValue /*= NULL*/,
								  BOOL bAutoLoad /*= TRUE*/,
								  BOOL bAutoSave /*= TRUE*/)
{
	m_hBaseKey = hKey;
	m_SubKey = lpszSubKey;
	m_ValueName = lpszValueName;

	m_bAutoSave = bAutoSave;
	m_bModified = FALSE;

	if (bAutoLoad)
		Load (lpszDefaultValue);
}


CRegistryString::~CRegistryString ()
{
	if (m_bModified && m_bAutoSave)
		Save ();
}


BOOL CRegistryString::Load (LPCTSTR lpszDefaultValue /*= NULL*/)
{
	ASSERT (m_hKey == NULL);

	m_Value = lpszDefaultValue;
	if (OpenKey (m_hBaseKey, m_SubKey))
	{
		return GetValue (m_ValueName, m_Value);
	}
	else
	{
		return FALSE;
	}
}


CRegistryString::operator LPCTSTR () const
{
	return m_Value;
}


CRegistryString& CRegistryString::operator= (LPCTSTR lpszValue)
{
	m_Value = lpszValue;
	m_bModified = TRUE;
	return *this;
}


BOOL CRegistryString::Save ()
{
	if (m_hKey == NULL)
	{
		if (!CreateKey (m_hBaseKey,
						m_SubKey))
				return FALSE;
	}

	if (SetValue (m_ValueName, m_Value))
	{
		m_bModified = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRegistryDWORD
/////////////////////////////////////////////////////////////////////////////


CRegistryDWORD::CRegistryDWORD (HKEY hKey,
							    LPCTSTR lpszSubKey /*= NULL*/,
							    LPCTSTR lpszValueName /*= NULL*/,
								DWORD dwDefaultValue /*= NULL*/,
								  BOOL bAutoLoad /*= TRUE*/,
								  BOOL bAutoSave /*= TRUE*/)
{
	m_hBaseKey = hKey;
	m_SubKey = lpszSubKey;
	m_ValueName = lpszValueName;

	m_bAutoSave = bAutoSave;
	m_bModified = FALSE;

	if (bAutoLoad)
		Load (dwDefaultValue);
}


CRegistryDWORD::~CRegistryDWORD ()
{
	if (m_bModified && m_bAutoSave)
		Save ();
}


BOOL CRegistryDWORD::Load (DWORD dwDefaultValue /*= NULL*/)
{
	ASSERT (m_hKey == NULL);

	m_dwValue = dwDefaultValue;
	if (OpenKey (m_hBaseKey, m_SubKey))
	{
		return GetValue (m_ValueName, m_dwValue);
	}
	else
	{
		return FALSE;
	}
}


CRegistryDWORD::operator DWORD () const
{
	return m_dwValue;
}


CRegistryDWORD& CRegistryDWORD::operator= (DWORD dwValue)
{
	m_dwValue = dwValue;
	m_bModified = TRUE;
	return *this;
}


BOOL CRegistryDWORD::Save ()
{
	if (m_hKey == NULL)
	{
		if (!CreateKey (m_hBaseKey,
						m_SubKey))
				return FALSE;
	}

	if (SetValue (m_ValueName, m_dwValue))
	{
		m_bModified = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


#endif	// _WIN32
