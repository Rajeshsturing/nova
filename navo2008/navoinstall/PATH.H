/////////////////////////////////////////////////////////////////////////////
// PATH.H		CPath interface
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


#ifndef _PATH_H_
#define _PATH_H_

//////////////////////////////////////
// Includes, Forwards
//////////////////////////////////////

#include <dos.h>	// for default DOS attribute _A_NORMAL.

//////////////////////////////////////
// Constants, Defines
//////////////////////////////////////

#ifdef _WIN32
LPCTSTR const DLL_EXTENSION = _T("dll");
LPCTSTR const INI_EXTENSION = _T("ini");
LPCTSTR const EXE_EXTENSION = _T("exe");
LPCTSTR const WILD_NAME_EXTENSION = _T("*.*");
#else
const char * const DLL_EXTENSION = _T("dll");
const char * const INI_EXTENSION = _T("ini");
const char * const EXE_EXTENSION = _T("exe");
const char * const WILD_NAME_EXTENSION = _T("*.*");
#endif

#ifndef IWBASECLASS
// Some implementations allow the InstallWizard class library to be built
// as a DLL. In these cases, IWBASECLASS is defined to implement MFC 
// extension DLL class sharing. If it isn't defined, define it to nothing
#define IWBASECLASS /* nothing */
#endif

//////////////////////////////////////
// Real components lengths
//////////////////////////////////////

// These constants can be used to limit user-interface elements to the
// appropriate sizes. These constants are smaller that the similar ones
// in STDLIB.H, which are used for the sizes required in splitpath.
// These constants do *not* take into account room for a trailing zero.

const int MaxFilePathLength			= _MAX_PATH;
const int MaxFileNameLength			= 8;
const int MaxFileExtensionLength	= 3;


class IWBASECLASS CPath
{
public:
	enum SpecialDirectoryEnum
	{
		CURRENT_DIRECTORY,
		WINDOWS_DIRECTORY,
		SYSTEM_DIRECTORY,
		MODULE_DIRECTORY,
		TEMP_DIRECTORY
	};
		
//////////////////////////////////////
// Constructors/Destructors/Inits
//////////////////////////////////////

public:    
    CPath ();
    CPath (CPath& rPath);
    CPath (LPCTSTR lpszPath);
    CPath (SpecialDirectoryEnum eInitialDir);
    ~CPath ();

	inline void Init ();
	inline void Exit ();

//////////////////////////////////////
// Operators
//////////////////////////////////////

    CPath& operator= (const CPath& rPath);
    CPath& operator= (LPCTSTR lpszPath);
    operator LPCTSTR() const;
	operator CString& () { return m_Path; }
	BOOL operator == (CPath& rPath) const;
    
//////////////////////////////////////
// Get Components
//////////////////////////////////////

    void GetDrive (CString& rDrive) const;
    void GetDriveDirectory (CString& rDriveDirectory) const;
    void GetDirectory (CString& rDirectory) const;
    void GetName (CString& rName) const;
    void GetNameExtension (CString& rNameExtension) const;
    void GetExtension (CString& rExtension) const;
    
	void GetComponents (CString* pDrive = NULL, 
						CString* pDirectory = NULL, 
						CString* pName = NULL, 
						CString* pExtension = NULL) const;
    void GetFullyQualified (CString& rFullyQualified) const;    


//////////////////////////////////////
// Get Other State
//////////////////////////////////////

	BOOL IsEmpty () const { return m_Path.IsEmpty (); }
    BOOL IsValid () const;
    BOOL IsWild () const;
    

//////////////////////////////////////
// SetComponents
//////////////////////////////////////

    void SetDrive (_TCHAR chDrive);
    void SetDriveDirectory (LPCTSTR lpszDriveDirectory);
    void SetDirectory (LPCTSTR lpszDirectory, BOOL bEnsureAbsolute = FALSE);
    void SetName (LPCTSTR lpszName);
    void SetNameExtension (LPCTSTR lpszNameExtension);
    void SetExtension (LPCTSTR lpszExtension);

	void AppendDirectory (LPCTSTR lpszSubDirectory);
	void UpDirectory (CString* pLastDirectory = NULL);

	void SetComponents (LPCTSTR lpszDrive, LPCTSTR lpszDirectory,
					    LPCTSTR lpszName, LPCTSTR lpszExtension);
					    
					    
//////////////////////////////////////
// Set whole path
//////////////////////////////////////

    void CurrentDirectory ();
    void WindowsDirectory ();
    void SystemDirectory ();
    void ModuleDirectory ();
	void TempDirectory ();

    void PrivateProfile ();
    void LocalProfile (UINT nNameResourceID, UINT nExtensionResourceID = 0);
    void LocalProfile (LPCTSTR lpszName, LPCTSTR lpszExtension = NULL);

    void MakeRoot ();

	void ModulePath ();
	void Empty ();
		        
//////////////////////////////////////
// Drive Information 
//////////////////////////////////////

    BOOL IsRemovableDrive () const;
    BOOL IsCDRomDrive () const;
    BOOL IsNetworkDrive () const;
    BOOL IsRAMDrive () const;

    LONG DriveTotalSpaceBytes () const;
    LONG DriveFreeSpaceBytes () const;
    LONG GetDriveClusterSize () const;

//////////////////////////////////////
// Directory information
//////////////////////////////////////

    BOOL DirectoryExists () const;
    BOOL IsDirectoryEmpty () const;

//////////////////////////////////////
// File Information
//////////////////////////////////////

    BOOL Exists () const;
    LONG GetSize () const; 
    CTime GetTime () const;

//////////////////////////////////////
// Directory operations
//////////////////////////////////////

    BOOL CreateDirectory (BOOL bCreateIntermediates = TRUE);
    void CreateDirectoryExcept (BOOL bCreateIntermediates = TRUE);	// throws CFileException
	BOOL RemoveDirectory ();
    BOOL ChangeDirectory ();
	    
//////////////////////////////////////
// File operations
//////////////////////////////////////

	BOOL Delete (BOOL bEvenIfReadOnly = TRUE);
	BOOL Rename (LPCTSTR lpszNewPath);	

//////////////////////////////////////
// FindFirst/FindNext
//////////////////////////////////////

    BOOL FindFirst (DWORD dwAttributes = _A_NORMAL);
    BOOL FindNext ();

//////////////////////////////////////
// Implementation
//////////////////////////////////////

#ifdef _WINDOWS
	UINT GetDriveType () const;
#endif	
	BOOL GetDiskFreeSpace (LPDWORD lpSectorsPerCluster,
						   LPDWORD lpBytesPerSector,
						   LPDWORD lpFreeClusters,
						   LPDWORD lpClusters) const;


//////////////////////////////////////
// Data members
//////////////////////////////////////

protected:
    CString         m_Path;    
	DWORD			m_dwFindFileAttributes;
#ifdef _WIN32
	HANDLE			m_hFindFile;
#else
    find_t*  		m_pFindFileInfo;
#endif
};	// class CPath



inline CArchive& operator<< (CArchive& rArchive, const CPath& rPath) \
	{ rArchive << (CString&) rPath; return rArchive; }
inline CArchive& operator>> (CArchive& rArchive, CPath& rPath) \
	{ rArchive >> (CString&) rPath; return rArchive; }

#endif // !_PATH_H_
