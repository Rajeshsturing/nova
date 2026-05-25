/////////////////////////////////////////////////////////////////////////////
// REGISTRY.H	Interfaces for CRegistryKey, CRegistryString, etc.
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

#ifdef _WIN32			// this file available for _WIN32 only

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

//////////////////////////////////////
// Includes, forwards
//////////////////////////////////////

#include <winreg.h>		// for REGSAM, etc., declarations.

/////////////////////////////////////////////////////////////////////////////
// CRegistryKey Interface
/////////////////////////////////////////////////////////////////////////////

class CRegistryKey: public CObject
{
//////////////////////////////////////
// Constructors, destructors, inits
//////////////////////////////////////

public:
	CRegistryKey ();
	virtual ~CRegistryKey();

//////////////////////////////////////
// Get state
//////////////////////////////////////

public:
	LONG GetLastError () const { return m_nLastError; }

//////////////////////////////////////
// Key-related Operations
//////////////////////////////////////

public:
	BOOL OpenKey (HKEY hKey,
				  LPCTSTR lpszSubKey = NULL,
				  REGSAM samDesired = KEY_ALL_ACCESS);
	BOOL CreateKey(HKEY hKey,
				   LPCTSTR lpszSubKey = NULL,
				   LPCTSTR lpszClass = NULL,
				   REGSAM samDesired = KEY_ALL_ACCESS,
				   LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
	BOOL DeleteKey(HKEY hKey,
				   LPCTSTR lpszSubKey = NULL);
	BOOL CloseKey();
	BOOL GetNextSubKey (CString& rSubKey,
						CString& rClass);

	//////////////////////////////////////
	// Value-related operations
	//////////////////////////////////////

	BOOL DeleteValue (LPCTSTR lpszValueName = NULL);

	//// GetValue

	// string versions
	BOOL GetValue (CString& rText);
	BOOL GetValue (LPCTSTR lpszValueName, CString& rText);

	// DWORD versions
	BOOL GetValue (LPCTSTR lpszValueName, DWORD& rdwValue);
	BOOL GetValue (DWORD& rdwValue);

	/// SetValue

	// string versions
	BOOL SetValue (LPCTSTR lpszValue);
	BOOL SetValue (LPCTSTR lpszValueName, LPCTSTR lpszValue);

	// dword values
	BOOL SetValue (DWORD dwValue);
	BOOL SetValue (LPCTSTR lpszValueName, DWORD dwValue);

#if (FALSE)
	BOOL SetValue (LPBYTE pbyData, DWORD cbLength);
	BOOL SetValue (LPCTSTR lpszValueName, LPBYTE pbyData, DWORD cbLength);
#endif

#ifdef _DEBUG
public:
	static void UnitTest();
#endif

protected:
	HKEY	m_hKey;
	LONG	m_nLastError;
	int		m_nSubKey;		// used for enumering subkeys
};



/////////////////////////////////////////////////////////////////////////////
// CRegistryString Interface
/////////////////////////////////////////////////////////////////////////////

class CRegistryString: public CRegistryKey
{
public:
	CRegistryString (HKEY hKey,
					 LPCTSTR lpszSubKey = NULL,
					 LPCTSTR lpszValueName = NULL,
					 LPCTSTR lpszDefaultValue = NULL,
					 BOOL bAutoLoad = TRUE,
					 BOOL bAutoSave = TRUE);
	~CRegistryString();

public:
	operator LPCTSTR () const;
	CRegistryString& operator = (LPCTSTR lpszValue);

public:
	BOOL Load(LPCTSTR lpszDefaultValue = NULL);
	BOOL Save();

public:
	BOOL IsEmpty () const { return m_Value.IsEmpty(); }

protected:
	HKEY		m_hBaseKey;
	CString		m_SubKey;
	CString		m_ValueName;

	CString		m_Value;
	BOOL		m_bModified;
	BOOL		m_bAutoSave;
};




#define DECLARE_STRING_REGISTRY(lpszClassName, hKey, lpszSubKey, lpszValueName, lpszDefaultValue)\
class lpszClassName: public CRegistryString\
{\
public:\
	lpszClassName(): CRegistryString (hKey, lpszSubKey, lpszValueName, lpszDefaultValue) {}\
	operator LPCTSTR () { return m_Value; }\
	lpszClassName& operator = (LPCTSTR lpszValue) { m_Value = lpszValue; m_bModified = TRUE; return *this; }\
};


/////////////////////////////////////////////////////////////////////////////
// CRegistryDWORD Interface
/////////////////////////////////////////////////////////////////////////////

class CRegistryDWORD: public CRegistryKey
{
public:
	CRegistryDWORD (HKEY hKey,
					 LPCTSTR lpszSubKey = NULL,
					 LPCTSTR lpszValueName = NULL,
					 DWORD dwDefaultValue = 0,
					 BOOL bAutoLoad = TRUE,
					 BOOL bAutoSave = TRUE);
	~CRegistryDWORD();

public:
	operator DWORD () const;
	CRegistryDWORD& operator = (DWORD dwValue);
	DWORD operator+= (DWORD dwIncrement) { m_dwValue += dwIncrement; m_bModified = TRUE; return m_dwValue; }
	DWORD operator-= (DWORD dwIncrement) { m_dwValue -= dwIncrement; m_bModified = TRUE; return m_dwValue; }
	// you cannot overload operators ++ or --; these would be naturals

public:
	BOOL Load(DWORD dwDefaultValue = 0);
	BOOL Save();

protected:
	HKEY		m_hBaseKey;
	CString		m_SubKey;
	CString		m_ValueName;

	DWORD		m_dwValue;
	BOOL		m_bModified;
	BOOL		m_bAutoSave;
};


#define DECLARE_DWORD_REGISTRY(lpszClassName, hKey, lpszSubKey, lpszValueName, dwDefaultValue)\
class lpszClassName: public CRegistryDWORD\
{\
public:\
	lpszClassName(): CRegistryDWORD (hKey, lpszSubKey, lpszValueName, dwDefaultValue) {}\
	operator DWORD () { return m_dwValue; }\
	lpszClassName& operator = (DWORD dwValue) { m_dwValue = dwValue; m_bModified = TRUE; return *this; }\
};


#endif	// !_REGISTRY_H_
#endif	// _WIN32

