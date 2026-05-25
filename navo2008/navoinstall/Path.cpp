/////////////////////////////////////////////////////////////////////////////
// PATH.CPP		CPath class
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
	Class Overview
	
	The class CPath is used to represent pathnames, that is the name and 
	location of a file. CPaths are used when you want to refer to a file
	as a whole, or to the location of a file, as opposed to CFile, which is 
	used when you want to change the contents of the file.

    Important Methods
    
    The methods below represent some of CPath's most useful functionality:
    
    GetDrive, GetDirectory, GetNameExtension, etc.		Get parts of a path
    SetDrive, SetNameExtension, SetExtension, etc.		Set parts of a path
    CreateDirectory										Like md
    RemoveDirectory										Like rd
    Current Directory									Like cd
    ChangeDirectory										Like cd 'this'


	Class Implementation
	
	The data representation for CPath consists of two data members. The 
	first, m_Path, is a CString. This allows for easy operators to and 
	from strings. Using a string to represent the path allows for fully 
	qualified as well as relative paths. The class is fundamentally built 
	on the C runtime functions _splitpath and _makepath.
	
	Class Notes
	
	This clas should suppport long filenames when compiled with a version
	of C++ runtime designed for them (e.g. Windows 95). It does not support
	UNC's as of yet (UNCs are of the form \\<server>\dir\dir\name.ext.
*/    

    
//////////////////////////////////////
// Includes
//////////////////////////////////////


#include "stdafx.h"		// included by all compilands
#include "path.h"		// external declarations for this file

#ifdef _WINDOWS
//#include "drvtype.h"	// for DriveType()
//#include "xstring.h"	// for sprintf
#endif

#include <sys\stat.h>    // for _stat, used in GetSize, DOS version of Exists
#include <direct.h>     // for _getcwd
#include <stdlib.h>     // for _splitpath
#include <stdio.h>		// for remove
#include <io.h>			// for access routines

//////////////////////////////////////
// Constants, Defines
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


const _TCHAR WILD_ONE             = '?';
const _TCHAR WILD_ANY             = '*';
LPCTSTR const WILD_SET      = _T("?*");
const _TCHAR DRIVE_DELIMITER      = ':';
const _TCHAR DIRECTORY_DELIMITER  = '\\';
const _TCHAR EXTENSION_DELIMITER  = '.';


//////////////////////////////////////
// External Functions
//////////////////////////////////////

inline DWORD ClearFlags (DWORD dwSource, DWORD dwFlags)
{
	return dwSource & ~dwFlags;
}

inline DWORD RetainFlags (DWORD dwSource, DWORD dwFlags)
{
	return dwSource & dwFlags;
}


inline BOOL IsFlagSet (DWORD dwSource, DWORD dwFlag)
{
	return (dwSource & dwFlag) != 0;
}


inline DWORD SetFlags (DWORD dwSource, DWORD dwFlags)
{
	return dwSource | dwFlags;
}


//////////////////////////////////////
// CString helper functions
//////////////////////////////////////


void SetLength (CString& Text, int nLength)
/*
	Effect:		Set the length of Text to nLength. Like putting a '\0' at the 
				nLength spot.
*/	
{
	Text.GetBufferSetLength (nLength);
	Text.ReleaseBuffer ();
}	


void StripLeadingChar (CString& rText, _TCHAR chLeading)
{
	int		nLength = rText.GetLength ();
	
	if (nLength == 0)
		return;

	if (rText[0] == chLeading)
		rText = rText.Right (nLength - 1);
}


void StripLeadingBackslash (CString& Directory)
{
	int		nLength = Directory.GetLength ();
	
	if (nLength <= 1)
		return;

	if (Directory[0] == DIRECTORY_DELIMITER)
		Directory = Directory.Right (nLength - 1);
}
		
	
void StripTrailingChar (CString& rText, _TCHAR chTrailing)
/*
	Effect:		If the character chTrailing is the last charactor of
				 of rText, remove it.
*/				
{
	int	nLength = rText.GetLength ();
	
	if (nLength == 0)
		return;
	
	if (rText[nLength - 1] == chTrailing)
		SetLength (rText, nLength - 1);	
}


void StripTrailingBackslash (CString& rDirectory)
/*
	Effect:		If the backslash is the last character of
				rDirectory, remove it, unless that is the 
				whole directory.
*/				
{
	int	nLength = rDirectory.GetLength ();
	
	// if Directory is of the form '\', don't do it.
	if (nLength <= 1)
		return;
		
	if (rDirectory[nLength - 1] == DIRECTORY_DELIMITER)
		SetLength (rDirectory, nLength - 1);	
}


void EnsureTrailingBackslash (CString& Directory)
/*
	Effect:		Add a backslash to the end of Directory if there is
				not already one there.
*/				
{
	int	nLength = Directory.GetLength ();

	if (Directory.IsEmpty() || Directory[nLength - 1] != DIRECTORY_DELIMITER)
		Directory = Directory + DIRECTORY_DELIMITER;
}
	

void EnsureLeadingBackslash (CString& Directory)
/*
	Effect:		Add a backslash to the beginning of Directory if there
				is not already one there.
*/				
{
	if (Directory.IsEmpty() || Directory[0] != DIRECTORY_DELIMITER)
		Directory = DIRECTORY_DELIMITER + Directory;
}

inline void CPath::Init ()
/*
	Effect:		Helper function for the various CPath constructors. 
				Initializes the data members and establishes various
				class invariants.
*/
{
	m_dwFindFileAttributes = 0;
#ifdef _WIN32
	m_hFindFile = NULL;
#else
	m_pFindFileInfo = NULL;
#endif
}


inline void CPath::Exit ()
{
#ifdef _WIN32
	if (m_hFindFile != NULL)
		FindClose (m_hFindFile);
#else
	if (m_pFindFileInfo != NULL)
		delete m_pFindFileInfo;
#endif
}


CPath::CPath ()
{
	Init ();
}


CPath::CPath (CPath& rPath)
{
	Init ();
	m_Path = rPath.m_Path;
}

	
CPath::CPath (LPCTSTR lpszPath)
{
	Init ();
    m_Path = lpszPath;
}

    
CPath::CPath (SpecialDirectoryEnum eInitialDir)
/*
	Effect:		Create a CPath which points to one of the "special" predefined
				subdirectories.

	Note:		If you have static CPaths in your program, you cannot use these
				predefined paths because Windows support may not be enabled yet.
*/				
{
	Init ();
    switch (eInitialDir)
    {		 
        case CURRENT_DIRECTORY:
            CurrentDirectory ();
            break;

#ifdef _WINDOWS            
        case WINDOWS_DIRECTORY:
            WindowsDirectory ();
            break;
            
        case SYSTEM_DIRECTORY:
            SystemDirectory ();
            break;
                        
        case MODULE_DIRECTORY:
            ModuleDirectory ();
            break;

		case TEMP_DIRECTORY:
			TempDirectory ();
			break;
#endif	// _WINDOWS
            
        default:
            // Only constants we know about.
            ASSERT (FALSE);
    }   // switch
}


CPath::~CPath ()
{
	Exit ();
}


/////////////////////////////////////////////////////////////////////////////
// Operators
/////////////////////////////////////////////////////////////////////////////

BOOL CPath::operator == (CPath& rPath) const
{
	CString		FullyQualified1, FullyQualified2;
	
	GetFullyQualified (FullyQualified1);
	rPath.GetFullyQualified (FullyQualified2);
	
	return (FullyQualified1.CompareNoCase (FullyQualified2) == 0);
}


CPath& CPath::operator= (const CPath& rPath)
{                   
	if (this == &rPath)
		return *this;
		
    m_Path = rPath.m_Path;
    return *this;
}



CPath& CPath::operator= (LPCTSTR lpszPath)
{
    m_Path = lpszPath;
    return *this;
}


CPath::operator LPCTSTR() const	//is this OK to change the name RGC
{
    return (LPCTSTR) m_Path;
}



/////////////////////////////////////////////////////////////////////////////
// Get Components
/////////////////////////////////////////////////////////////////////////////


void CPath::GetComponents (CString* pDrive, 
                       	   CString* pDirectory, 
                       	   CString* pName, 
                           CString* pExtension) const
/*
	Effect:		Return the individual components of this path. For any given argument,
				you can pass NULL if you are not interested in that component.

	Note:		THIS METHOD DIFFERS FROM THE DOS FUNCTION _splitpath:
	
				Returns the drive component without a colon, e.g. "c"

				Returns the directory component with a leading backslash, but no trailing 
				backslash, e.g. "\dir\subdir\".

				Returns name compleletely without delimiters, e.g "letter".
				
				Returns extension completely without delimiters, e.g. "doc".
				
	Note:		Do not rely on pNames being <= 8 characters, extensions being <= 3 characters,
				or drives being 1 character.
*/							
{
	_splitpath (m_Path, 
                pDrive ? pDrive->GetBuffer (_MAX_DRIVE + 1) : NULL,
                pDirectory ? pDirectory->GetBuffer (_MAX_DIR + 1) : NULL,
                pName ? pName->GetBuffer (_MAX_FNAME + 1) : NULL,
                pExtension ? pExtension->GetBuffer (_MAX_EXT + 1) : NULL);
                
    if (pDrive)
        pDrive->ReleaseBuffer ();            
    if (pDirectory)
        pDirectory->ReleaseBuffer ();            
    if (pName)
        pName->ReleaseBuffer ();            
    if (pExtension)
        pExtension->ReleaseBuffer (); 


	// DOS's _splitpath returns "d:", we return "d"
	if (pDrive)
		StripTrailingChar (*pDrive, DRIVE_DELIMITER);
	// DOS's _splitpath returns "\dir\subdir\", we return "\dir\subdir"	
	if (pDirectory)
		StripTrailingBackslash (*pDirectory);
	// DOS's _splitpath returns ".ext", we return "ext"	
	if (pExtension)
		StripLeadingChar (*pExtension, EXTENSION_DELIMITER);		
}

                       
void CPath::GetDrive (CString& rDrive) const
{
	GetComponents (&rDrive, NULL, NULL, NULL);
}


void CPath::GetDriveDirectory (CString& roDriveDirectoryString) const
{
    CString     oDriveString;
    CString     oDirectoryString;

	GetComponents (&oDriveString, &oDirectoryString);
	if (!oDriveString.IsEmpty())
	{
		roDriveDirectoryString = oDriveString + DRIVE_DELIMITER + oDirectoryString;
	}
	else
	{
		roDriveDirectoryString = oDirectoryString;
	}
}


void CPath::GetDirectory (CString& rDirectory) const
{
    GetComponents (NULL, &rDirectory, NULL, NULL);
}    


void CPath::GetNameExtension (CString& rNameExtension) const
{
    CString     Name;
    CString     Extension;

	GetComponents (NULL, NULL, &Name, &Extension);
    rNameExtension = Name;
    if (!Extension.IsEmpty ())
    	rNameExtension += EXTENSION_DELIMITER + Extension;
}


void CPath::GetName (CString& rName) const
{
    GetComponents (NULL, NULL, &rName, NULL);
}


void CPath::GetExtension (CString& rExtension) const
{
    GetComponents (NULL, NULL, NULL, &rExtension);
}   


void CPath::GetFullyQualified (CString& rFullyQualified) const
{
	_fullpath (rFullyQualified.GetBuffer (_MAX_PATH), m_Path, _MAX_PATH + 1);
    rFullyQualified.ReleaseBuffer ();
}

/////////////////////////////////////////////////////////////////////////////
// Get other state
/////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
BOOL CPath::IsValid () const
/*
   Effect:        Determine whether lpszFileName is valid. A filename
                  is valid if it contains only legal characters, doesn't
                  have repeated contiguous subdirectory delimiters, has at 
                  most one drive delimiter, has at most one extension 
                  delimiter, and all components fit within maximum sizes.

                  This routine does *not* determine if a file exists, or
                  even if it could exist relative to the user's directory
                  hierarchy.  Its tests are for lexical correctness only.

   See Also:      CPath::Exists.
*/
   {  // FileNameValid                      
#ifdef _WIN32	
   SECURITY_ATTRIBUTES sa;

    HANDLE fHandle = CreateFile(
				    m_Path,	// pointer to name of the file 
					0,	// access (read-write) mode 
					0,	// share mode 
					&sa,	// pointer to security descriptor 
					OPEN_EXISTING,	// how to create 
					FILE_ATTRIBUTE_NORMAL,	// file attributes 
					NULL 	// handle to file with attributes to copy  
					);
	BOOL bSuccess = (fHandle != INVALID_HANDLE_VALUE);

	if (bSuccess)
		CloseHandle(fHandle);
	
	return bSuccess;
#else
   OFSTRUCT       of ;
   return (OpenFile (m_Path, &of, OF_PARSE) != HFILE_ERROR) ;
#endif
   }  // FileNameValid
#endif

    
BOOL CPath::IsWild () const
{
    return (m_Path.FindOneOf (WILD_SET) != -1);
}


/////////////////////////////////////////////////////////////////////////////
// Set Components
/////////////////////////////////////////////////////////////////////////////


void CPath::SetComponents (LPCTSTR lpszDrive, LPCTSTR lpszDirectory,
						   LPCTSTR lpszName, LPCTSTR lpszExtension)
{
	_makepath (m_Path.GetBuffer (_MAX_PATH), 
			   lpszDrive, lpszDirectory,
			   lpszName, lpszExtension);
	m_Path.ReleaseBuffer ();

}

						   
void CPath::SetDrive (_TCHAR chDrive)
{
	CString		Drive = chDrive;
	CString		Directory;
	CString		Name;
	CString		Extension;
	
	GetComponents (NULL, &Directory, &Name, &Extension);
	SetComponents (Drive, Directory, Name, Extension);
}


void CPath::SetDirectory (LPCTSTR lpszDirectory, BOOL bEnsureAbsolute /*= FALSE*/)

{
	CString		Drive;	
	CString		Directory = lpszDirectory;
	CString		Name;
	CString		Extension;
	
	EnsureLeadingBackslash (Directory);
	EnsureTrailingBackslash (Directory);		

	GetComponents (&Drive, NULL, &Name, &Extension);
	SetComponents (Drive, Directory, Name, Extension);
}    


void CPath::SetDriveDirectory (LPCTSTR lpszDriveDirectory)
{
	CString		DriveDirectory = lpszDriveDirectory;
	CString		Name;
	CString		Extension;
	
	EnsureTrailingBackslash (DriveDirectory);
	
	GetComponents (NULL, NULL, &Name, &Extension);
	SetComponents (NULL, DriveDirectory, Name, Extension);
}    


void CPath::SetName (LPCTSTR lpszName)
{
	CString		Drive;
	CString		Directory;
	CString		Extension;
	
	GetComponents (&Drive, &Directory, NULL, &Extension);
	SetComponents (Drive, Directory, lpszName, Extension);
}

    
void CPath::SetExtension (LPCTSTR lpszExtension)
{
	CString		Drive;
	CString		Directory;
	CString		Name;
	
	GetComponents (&Drive, &Directory, &Name, NULL);
	SetComponents (Drive, Directory, Name, lpszExtension);
}


void CPath::SetNameExtension (LPCTSTR lpszNameExtension)
{
	CString		Drive;
	CString		Directory;

	GetComponents (&Drive, &Directory, NULL, NULL);
	SetComponents (Drive, Directory, lpszNameExtension, NULL);	
}    


void CPath::AppendDirectory (LPCTSTR lpszSubDirectory)
{                                               
	CString		Drive;
	CString		Directory;
	CString		SubDirectory = lpszSubDirectory;
	CString		Name;
	CString		Extension;
	
	if (SubDirectory.IsEmpty ())
		return;

	// strip out any preceeding backslash		
	StripLeadingBackslash (SubDirectory);
	EnsureTrailingBackslash (SubDirectory);

	GetComponents (&Drive, &Directory, &Name, &Extension);
	EnsureTrailingBackslash (Directory);
	SetComponents (Drive, Directory + SubDirectory, Name, Extension);
}


void CPath::UpDirectory (CString* pLastDirectory /*= NULL*/)
{
	CString		Directory;
	int			nDelimiter;

	GetDirectory (Directory);	
	StripTrailingBackslash (Directory);
	if(Directory.IsEmpty())
		return;
	
	nDelimiter = Directory.ReverseFind (DIRECTORY_DELIMITER);
	
	if (pLastDirectory != NULL)
	{
		*pLastDirectory = Directory.Mid (nDelimiter);
		StripLeadingBackslash (*pLastDirectory);
	}
		
	if (nDelimiter >= 0)
		Directory = Directory.Left (nDelimiter);
		
	SetDirectory (Directory);
}

		
/////////////////////////////////////////////////////////////////////////////
// Set Whole Path
/////////////////////////////////////////////////////////////////////////////

void CPath::Empty ()
{
	m_Path.Empty ();
}

	
void CPath::CurrentDirectory ()
/*
	Effect:		Set this path to the current working directory.
	
	Note:		To maintain class invariant, don't just set the representation
				to what we get from _getcwd. Go through the fundamental operations
				of Empty and SetDriveDirectory instead. This effectively gets that
				backslash at the end of the representation string.
*/	
{
	CString		DriveDirectory;
	
	_getcwd (DriveDirectory.GetBuffer (_MAX_PATH), _MAX_PATH);
	DriveDirectory.ReleaseBuffer ();
	
	Empty ();
	SetDriveDirectory (DriveDirectory);
}


#ifdef _WINDOWS
void CPath::WindowsDirectory ()
{
	CString		DriveDirectory;
	
    GetWindowsDirectory (DriveDirectory.GetBuffer (_MAX_PATH), _MAX_PATH);
    DriveDirectory.ReleaseBuffer ();
    
    Empty ();
    SetDriveDirectory (DriveDirectory);
}
#endif	// _WINDOWS


#ifdef _WINDOWS
void CPath::SystemDirectory ()
{
	CString		DriveDirectory;
	
    GetSystemDirectory (DriveDirectory.GetBuffer (_MAX_PATH), _MAX_PATH);
    DriveDirectory.ReleaseBuffer ();
    
    Empty ();
    SetDriveDirectory (DriveDirectory);
}
#endif	// _WINDOWS


#ifdef _WINDOWS
void CPath::ModulePath ()
{
    GetModuleFileName (AfxGetInstanceHandle(),
                       m_Path.GetBuffer (_MAX_PATH), _MAX_PATH);
    m_Path.ReleaseBuffer ();                   
}
#endif	// _WINDOWS


#ifdef _WINDOWS
void CPath::ModuleDirectory ()
/*
	Effect:		Set this path to the drive and directory of the currently 
				executing process.
*/				
{
	ModulePath ();
	SetNameExtension (_T(""));
}
#endif


#ifdef _WINDOWS
void CPath::TempDirectory ()
/*
	Effect:		Set this CPath to the drive and directory most appropriate
				for temporary files. 
				
				
	Note:		Currently, if the current environment has an
				entry for the TEMP environment variable, the directory will
				be set to that. If not, the directory will be the Windows
				System directory. The caller of this method, however, should
				not rely on this convention.
				
	Internals:	Use GetTempFileName to create a full temporary pathname. Then
				retain just the drive and directory.
*/				
{
#ifdef _WIN32
	::GetTempPath (_MAX_PATH, m_Path.GetBuffer(_MAX_PATH));
#else
	::GetTempFileName (0,
					   "temp",
					   0,
					   m_Path.GetBuffer (_MAX_PATH));
#endif
	m_Path.ReleaseBuffer ();
	SetNameExtension (_T(""));	
}						 
#endif	// _WINDOWS
        

#ifdef _WINDOWS
void CPath::LocalProfile (LPCTSTR lpszName, LPCTSTR lpszExtension /*= NULL*/)
/*
    Effect:     Local profiles are private INI files but located in the same 
                directory as the executable. These are used for less volatile
                settings than those found in the applications main private INI
                file, which would be in the Windows directory.
                
                Sets the value of this path to <drive>:\<directory>\<name>.ini
                where name is from lpszName and drive and directory are from the
                currently executing module's path.

    Arguments:  lpszName    The name component of the path.
    
    See Also:   PrivateProfile, LocalProfile (UINT).
*/              
{
	ModuleDirectory ();
    
    if (lpszExtension == NULL)
        lpszExtension = INI_EXTENSION;

	SetName (lpszName);
	SetExtension (lpszExtension);	        
}
#endif	// _WINDOWS

            
#ifdef _WINDOWS
void CPath::LocalProfile (UINT nNameResourceID, UINT nExtensionResourceID /*= 0*/)
/*
    Effect:     Like the above LocalProfile, but with the name supplied by a resource
                string identified by nResourceID.
                
    See Also:   LocalProfile (LPCTSTR).          
*/              
{
    CString     Name;
    CString     Extension;

    if (nExtensionResourceID)
        Extension.LoadString (nExtensionResourceID);
    else
        Extension = INI_EXTENSION;
                
    if (Name.LoadString (nNameResourceID))
        LocalProfile (Name, Extension);
}
#endif	// _WINDOWS


#ifdef _WINDOWS
void CPath::PrivateProfile ()
{
    CPath   WindowsDirectory (WINDOWS_DIRECTORY);
    
	ModulePath ();
	SetDriveDirectory (WindowsDirectory);
	SetExtension (INI_EXTENSION);
}
#endif	// _WINDOWS

void CPath::MakeRoot  ()
/*
	Effect:		Turn this path from "x:\directory\subdirectory\name.ext"
				to just "x:\".
*/
{   
	SetDirectory (_T(""));
	SetNameExtension (_T(""));
}

/////////////////////////////////////////////////////////////////////////////
// File Operations
/////////////////////////////////////////////////////////////////////////////


BOOL CPath::Delete (BOOL bEvenIfReadOnly)
{
	//REMOVE will not actually remove read only files
	//so we might want to set the readonly property
	//off

	if (bEvenIfReadOnly)
	{
		if( (_access(m_Path, _S_IWRITE )) != -1 ) //does the file have write access
		{
			if(_chmod( m_Path, _S_IWRITE ) == -1 )
				TRACE(_T("ERROR - CPath::Delete was unable to delete file"));
		}
	}
	return !remove ((LPCTSTR) *this);
}	


BOOL CPath::Rename (LPCTSTR lpszNewPath)
{
	return !rename ((LPCTSTR) *this, lpszNewPath);
}	


/////////////////////////////////////////////////////////////////////////////
// Directory Information
/////////////////////////////////////////////////////////////////////////////


BOOL CPath::DirectoryExists () const
/*
	Win32 Effect:		To determine if the directory exists, we need to
						create a test path with a wildcard (*.*) extension
						and see if FindFirstFile returns anything.  We don't
						use CPath::FindFirst() because that routine parses out
						'.' and '..', which fails for empty directories.
*/
{
#ifdef _WIN32
	CPath		TestPath = *this;

	TestPath.SetNameExtension (WILD_NAME_EXTENSION);	//create test path	
	
	WIN32_FIND_DATA		FindData;
	BOOL				bGotFile;
	HANDLE hFindFile = FindFirstFile (TestPath, &FindData);	//find anything in the path
	bGotFile = (hFindFile != INVALID_HANDLE_VALUE);

	if (m_hFindFile != NULL)	//make sure to close the file
		FindClose (m_hFindFile);

	return bGotFile;
#else
	_find_t		FindFileInfo;
	CString		Path = m_Path;
	
	StripTrailingBackslash (Path);
	
    if (_dos_findfirst (Path, _A_SUBDIR, &FindFileInfo) != 0)
    	return FALSE;
    	
	return (IsFlagSet (FindFileInfo.attrib, _A_SUBDIR));
#endif
}                                                     
	
BOOL CPath::IsDirectoryEmpty () const
{
	CPath	FileSpec = *this;
	
	FileSpec.SetNameExtension (WILD_NAME_EXTENSION);
	return (!FileSpec.FindFirst ());
}

	
/////////////////////////////////////////////////////////////////////////////
// Drive Information
/////////////////////////////////////////////////////////////////////////////


#ifdef _WINDOWS
BOOL CPath::IsRemovableDrive () const
{
	return (GetDriveType () == DRIVE_REMOVABLE);
}
#endif


#ifdef _WINDOWS
BOOL CPath::IsNetworkDrive () const
{
	return (GetDriveType () == DRIVE_REMOTE);
}
#endif

#ifdef _WINDOWS
BOOL CPath::IsCDRomDrive () const
{
	return (GetDriveType () == DRIVE_CDROM);
}
#endif


#ifdef _WINDOWS
BOOL CPath::IsRAMDrive () const
{
	return (GetDriveType () == DRIVE_RAMDISK);
}
#endif // _WINDOWS


LONG CPath::DriveFreeSpaceBytes () const
{
	DWORD		nSectorsPerCluster;
	DWORD		nBytesPerSector;
	DWORD		nFreeClusters;
	DWORD		nClusters;

	if (!GetDiskFreeSpace (&nSectorsPerCluster, &nBytesPerSector,
					 	   &nFreeClusters, &nClusters))
		return 0;
	else		
		return nFreeClusters * nSectorsPerCluster * nBytesPerSector;
}


LONG CPath::DriveTotalSpaceBytes () const
{
	DWORD		nSectorsPerCluster;
	DWORD		nBytesPerSector;
	DWORD		nFreeClusters;
	DWORD		nClusters;

	if (!GetDiskFreeSpace (&nSectorsPerCluster, &nBytesPerSector,
					 	   &nFreeClusters, &nClusters))
		return 0;
	else		
		return nClusters * nSectorsPerCluster * nBytesPerSector;
}


LONG CPath::GetDriveClusterSize () const
{
	DWORD		nSectorsPerCluster;
	DWORD		nBytesPerSector;
	DWORD		nFreeClusters;
	DWORD		nClusters;

	if (!GetDiskFreeSpace (&nSectorsPerCluster, &nBytesPerSector,
					 	   &nFreeClusters, &nClusters))
		return 0;
	else		
		return nSectorsPerCluster * nBytesPerSector;
}

/////////////////////////////////////////////////////////////////////////////
// Find First / Find Next
/////////////////////////////////////////////////////////////////////////////

BOOL AttributesMatch (DWORD dwTargetAttributes, DWORD dwFileAttributes)
{
	if (dwTargetAttributes == _A_NORMAL)
	{
		return (!IsFlagSet (_A_SUBDIR, dwFileAttributes));
	}
	else
	{
		return (IsFlagSet (dwTargetAttributes, dwFileAttributes) &&
				(IsFlagSet (_A_SUBDIR, dwTargetAttributes) == 
				 IsFlagSet (_A_SUBDIR, dwFileAttributes)));
	}
}


BOOL CPath::FindFirst (DWORD dwAttributes /*= _A_NORMAL*/)
/*
	Effect:		Find the first file that meets this path and the specified
				attributes.

  	Arguments:	dwAttributes
	
				These constants specify the current attributes 
				of the file or directory specified by the function.
				The attributes are represented by the following 
				manifest constants:

				_A_ARCH		Archive. Set whenever the file is 
							changed, and cleared by the BACKUP 
							command.
				_A_HIDDEN   Hidden file. Not normally seen with 
							the DIR command, unless the /AH option 
							is used. Returns information about normal 
							files as well as files with this attribute.
				_A_NORMAL   Normal. File can be read or written to 
							without restriction.
				_A_RDONLY   Read-only. File cannot be opened for writing, 
							and a file with the same name cannot be created. 
				_A_SUBDIR   Subdirectory.
				_A_SYSTEM   System file. Not normally seen with the DIR 
							command, unless the /AS option is used.

				Multiple constants can be combined with the OR operator (|).

	Note:		These attributes do not follow a simple additive logic.
				Note that _A_NORMAL is 0x00, so it effectively cannot be
				removed from the attribute set. You will therefore always
				get normal files, and may also get Archive, Hidden, etc.,
				if you specify those attributes.

	See Also:	FindNextFile, FindFirstSubdirectory.

*/
{
	m_dwFindFileAttributes = dwAttributes;
	BOOL				bGotFile;
	BOOL				bWantSubdirectory = IsFlagSet (_A_SUBDIR, dwAttributes);

	//////////////////////////////////////
	// i. find first candidate file
	//////////////////////////////////////

#ifdef _WIN32
	WIN32_FIND_DATA		FindData;
	m_hFindFile = FindFirstFile (m_Path, &FindData);
	
	bGotFile = (m_hFindFile != INVALID_HANDLE_VALUE);
#else 
	if (m_pFindFileInfo != NULL)
		delete m_pFindFileInfo;
    m_pFindFileInfo = new find_t;
    
   bGotFile =  (_dos_findfirst (m_Path, 
   								(unsigned) dwAttributes, 
   								m_pFindFileInfo) == 0);
#endif
	while (bGotFile)
	{
		//////////////////////////////////////
		// ii. compare candidate to attributes
		//////////////////////////////////////
#if _WIN32
		if (!AttributesMatch (m_dwFindFileAttributes, 
							  FindData.dwFileAttributes))
			goto GetAnother;

		if (bWantSubdirectory && (FindData.cFileName[0] == '.'))
			goto GetAnother;
#else
		if (!AttributesMatch (m_dwFindFileAttributes,
							  m_pFindFileInfo->attrib))
			goto GetAnother;				  

		if (bWantSubdirectory && (m_pFindFileInfo->name[0] == '.'))
			goto GetAnother;
#endif

		//////////////////////////////////////
		// iii. found match; prepare result
		//////////////////////////////////////

		if (IsFlagSet (_A_SUBDIR, m_dwFindFileAttributes))
   		   	StripTrailingBackslash (m_Path);
#if _WIN32   		   	
		SetNameExtension (FindData.cFileName);
#else		
        SetNameExtension (m_pFindFileInfo->name);
#endif        
	    if (IsFlagSet (_A_SUBDIR, dwAttributes))
    	   	EnsureTrailingBackslash (m_Path);
		return TRUE;
	
		//////////////////////////////////////
		// iv. not found match; get another
		//////////////////////////////////////
	GetAnother:
#if _WIN32
		bGotFile = FindNextFile (m_hFindFile, &FindData);
#else		
    	bGotFile = (_dos_findnext (m_pFindFileInfo) == 0);
#endif    
	}	// while
	
	return FALSE;
}


BOOL CPath::FindNext ()
{
#ifdef _WIN32
	WIN32_FIND_DATA		FindData;

	ASSERT (m_hFindFile != NULL);
	while (FindNextFile (m_hFindFile, &FindData) != FALSE)
#else	
	ASSERT (m_pFindFileInfo != NULL);
	while (_dos_findnext (m_pFindFileInfo) == 0)
#endif	
	{
#ifdef _WIN32
		if (AttributesMatch (m_dwFindFileAttributes, 
							 FindData.dwFileAttributes))
#else							 
		if (AttributesMatch (m_dwFindFileAttributes, 
							 m_pFindFileInfo->attrib))
#endif							 
		{
	        if (IsFlagSet (_A_SUBDIR, m_dwFindFileAttributes))
			{
				UpDirectory ();
#ifdef _WIN32				
				AppendDirectory (FindData.cFileName);
#else				
				AppendDirectory (m_pFindFileInfo->name);
#endif				
			}
			else
#ifdef _WIN32				
				SetNameExtension (FindData.cFileName);
#else				
				SetNameExtension (m_pFindFileInfo->name);
#endif				
//	        if (IsFlagSet (_A_SUBDIR, m_dwFindFileAttributes))
//    	    	EnsureTrailingBackslash (m_Path);
			return TRUE;
		}
//		bGotFile = FindNextFile (m_hFindFile, &FindData);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// File information
/////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
BOOL CPath::Exists () const
{
	
#ifdef _WIN32
	WIN32_FIND_DATA FindData;
	HANDLE SearchHandle = FindFirstFile(m_Path,&FindData);
	BOOL bSuccess = (SearchHandle != INVALID_HANDLE_VALUE);
	FindClose(SearchHandle);
	return bSuccess;
#else
    OFSTRUCT    of;    
    return (OpenFile (m_Path, &of, OF_EXIST) != HFILE_ERROR);
#endif
}
#else
BOOL CPath::Exists () const
{
	struct _stat	s;
    int				result;
    
    result = _stat (m_Path, &s);
    return (result == 0);
}
#endif    


LONG CPath::GetSize () const
{
	struct _stat	s;
    int				result;
	result = _stat (m_Path, &s);

    if (result == 0)
    	return (s.st_size);
    else
    	return 0;	
}

				
CTime CPath::GetTime () const
{
	struct _stat	s;
    int				result;

	result = _stat (m_Path, &s);

    if (result == 0)
    	return (s.st_mtime);
    else
    	return 0;	
}


/////////////////////////////////////////////////////////////////////////////
// Directory Operations
/////////////////////////////////////////////////////////////////////////////

BOOL CPath::ChangeDirectory ()
{
	CString	DriveDirectory;
	GetDriveDirectory (DriveDirectory);
	return (_chdir (DriveDirectory) == 0);
}


BOOL CPath::RemoveDirectory ()
{
	CString		DriveDirectory;
	
	GetDriveDirectory (DriveDirectory);
	BOOL bSuccess = (_rmdir (DriveDirectory) ==  0);
	return bSuccess;
}

	
BOOL CPath::CreateDirectory (BOOL bCreateIntermediates /*= TRUE*/)
{
	CString		PathText (m_Path);
	BOOL		bSuccess;
		
	StripTrailingBackslash (PathText);
	bSuccess = (_mkdir (PathText) ==  0);
	if (!bSuccess)
		bSuccess = ChangeDirectory ();
		
	if (!bSuccess && bCreateIntermediates)
	{
		int	nDelimiter = PathText.ReverseFind (DIRECTORY_DELIMITER);
		if (nDelimiter == -1)
			return FALSE;

		SetLength (PathText, nDelimiter);
		CPath	SubPath = PathText;
		
		if (SubPath.CreateDirectory ())
			return CreateDirectory (FALSE);
		else 
			return FALSE;
	}
	return bSuccess;
}			


void CPath::CreateDirectoryExcept (BOOL bCreateIntermediates /*= TRUE*/)
{                          
	BOOL		bSuccess = CreateDirectory (bCreateIntermediates);
	
	if (!bSuccess)
		CFileException::ThrowErrno (errno);
}				


/////////////////////////////////////////////////////////////////////////////
// Implementation
/////////////////////////////////////////////////////////////////////////////

BOOL CPath::GetDiskFreeSpace (LPDWORD lpSectorsPerCluster,
							  LPDWORD lpBytesPerSector,
							  LPDWORD lpFreeClusters,
							  LPDWORD lpClusters) const
{
#ifdef _WIN32
	CPath	RootPath = *this;

	RootPath.MakeRoot ();
	return ::GetDiskFreeSpace (RootPath, 
							   lpSectorsPerCluster,
							   lpBytesPerSector,
							   lpFreeClusters,
							   lpClusters);
#else
	CString		Drive;
    _diskfree_t	diskfree;
	
	GetDrive (Drive);
    Drive.MakeLower ();
    
    if (Drive.IsEmpty ())
        return FALSE;
    else
    {
    	// default is 0, drive A: is 1, etc.
    	if (_dos_getdiskfree (Drive[0] - 'a' + 1, &diskfree))
    		return FALSE;

		*lpSectorsPerCluster = diskfree.sectors_per_cluster;
		*lpBytesPerSector = diskfree.bytes_per_sector;
		*lpFreeClusters = diskfree.avail_clusters;
		*lpClusters = diskfree.total_clusters;

		return TRUE;
	}
#endif
}


#ifdef _WINDOWS
UINT CPath::GetDriveType () const
/*
	Effect:		Return the type of the drive this path points to.
				In particular, return one of the following:
				
				0		Drive type cannot be determined
				1		Root directory does not exist
				DRIVE_REMOVABLE		Drive can be removed (e.g. floppy)
				DRIVE_FIXED			Drive cannot be removed (e.g. hard disk)
				DRIVE_REMOTE		Network drive
				DRIVE_CDROM			CD-Rom drive
				DRIVE_RAMDISK		RAM drive

	Internals:	This method exists primarily to give an OS-independent way
				of accessing the drive type, which is done differently in
				win 16 and 32. In 32, ::GetDriveType has the full function,
				in 16, it is supplemented by DriveType (drvtype.cpp).
*/
{
	CPath	RootPath = *this;

	RootPath.MakeRoot ();
	return ::GetDriveType(RootPath);	//unsure of what to do RGC
	return 0;
}
#endif 	// _WINDOWS
