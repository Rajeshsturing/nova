/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	repair/installation common procedures
*/

#include "stdafx.h"
#include "..\navoinstall\resource.h"
#include <shlobj.h>
#include "commonproc.h"
#include "..\navoinstall\navo_security.h"
#include "..\navoinstall\version.h"


CString AskUserForFolder(LPCTSTR lpTitle)
{
	CSimpleOleInitHolder oSimpleOleInitHolder;

	SCP<IMalloc> pIMallocSP;
	if(::SHGetMalloc(&pIMallocSP.GetRawPointer()) != S_OK)
	{
		ASSERT(false);
		return "";
	}
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	
	TCHAR szDisplayName[MAX_PATH];
	szDisplayName[0] = '\0';
	
	bi.hwndOwner = ::GetActiveWindow();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = lpTitle;
	bi.ulFlags = BIF_RETURNONLYFSDIRS  ;
	bi.lParam = NULL;
	bi.iImage = 0;
	
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);
	if(pidl != NULL)
	{
		BOOL bRes = ::SHGetPathFromIDList(pidl,szDisplayName);
		pIMallocSP->Free((LPVOID) pidl);
		return bRes ? CString(szDisplayName) : "";
	}
	return "";
}

static CString TestLocationForSourceMedia(LPCTSTR lpLocation,LPCTSTR lpSubDir,LPCTSTR lpKeyFile)
{
	CFile oFileToTest;
	CString oFullPathString = CString(lpLocation); 
	EnsureEndingBackslash(oFullPathString);

	oFullPathString += CString(lpSubDir);
	EnsureEndingBackslash(oFullPathString);
	oFullPathString += lpKeyFile;
	if(oFileToTest.Open(oFullPathString,CFile::modeRead))
	{
		oFileToTest.Close();
		return CString(lpLocation);	//found in subdir
	}
	return "";
}

CString FindFirstCDROMDrive()
{
	for(char cDrive = 'C'; cDrive <= 'Z'; cDrive++)
	{
		CString oString;
		oString.Format("%c:\\",cDrive);
		if(::GetDriveType(oString) == DRIVE_CDROM)
		{
			return oString;
		}
	}
	return "";
}

CString GetMediaRootURL(UserAskMode eUAM,LPCTSTR lpSourceDir,LPCTSTR lpSubDir,LPCTSTR lpKeyFile,
						LPCTSTR lpComponentHumanName)
{
	CString oString;
	LONG lResult = ERROR_SUCCESS;

	if(eUAM != UAM_REQUIRED)
	{
		if(*lpSourceDir)	//podano Ÿród³o - próbuj u¿yæ
		{
			return TestLocationForSourceMedia(lpSourceDir,lpSubDir,lpKeyFile);
		}
		
		//check current directory
		CString oCurDirString = NavoGetCurrentDir();
		CString oTestString = TestLocationForSourceMedia(oCurDirString,lpSubDir,lpKeyFile);
		if(!oTestString.IsEmpty())
		{
			return oTestString;
		}

restart:	
		//nie ma Ÿród³a - sprawdŸ ostatnie Ÿród³o na podstawie registry
		lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "MediaSource",oString);
		if(lResult == ERROR_ACCESS_DENIED)
		{
			CLogonAsUser oLogonAsUser;
			if(oLogonAsUser.Logon(true,::GetActiveWindow()))
			{
				goto restart;
			}
			else
			{
				return "";
			}
		}
		
		//check last registry entry
		if(!oString.IsEmpty())
		{
			CString oTestString = TestLocationForSourceMedia(oString,lpSubDir,lpKeyFile);
			if(!oTestString.IsEmpty())
			{
				return oTestString;
			}
		}
		
		
		//check cdrom if exists
		oString = FindFirstCDROMDrive();
		if(!oString.IsEmpty())
		{
			CString oTestString = TestLocationForSourceMedia(oString,lpSubDir,lpKeyFile);
			if(!oTestString.IsEmpty())
			{
				return oTestString;
			}
		}
	}
	//ask user if it is allowed
	if(eUAM == UAM_FORBIDDEN)
	{
		return "";
	}

	while(1)
	{
		//ask user for folder
		CString oTitleString;
		oTitleString.Format(IDS_BROWSEFORSOURCEMEDIA,lpComponentHumanName,lpKeyFile);
		oString = AskUserForFolder(oTitleString);
		if(oString.IsEmpty())
		{
			return "";
		}
		//check signature
		CString oTestString = TestLocationForSourceMedia(oString,"",lpKeyFile);

		if(!oTestString.IsEmpty())
		{
			EnsureEndingBackslash(oString);
			CString oSubDirString(lpSubDir);
			EnsureEndingBackslash(oSubDirString);
			return oString.Left(oString.GetLength() - oSubDirString.GetLength());
		}
		oTitleString.Format(IDS_CANNTFINDSRCATLOCATION,lpComponentHumanName);
		if(AfxMessageBox(oTitleString,MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return "";
		}
	}
}



DWORD NAVOSetupFileEx(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse)
{
	bInUse = false;
try_copy:
	if(::CopyFile(lpSrcFileName,lpDestFileName,FALSE))
	{
		return ERROR_SUCCESS;
	}
	DWORD dwLastError = ::GetLastError();
	if (dwLastError == ERROR_ACCESS_DENIED)
	{
		CFileStatus oFileStatus;
		CFile::GetStatus(lpDestFileName, oFileStatus);
		oFileStatus.m_attribute = (BYTE)(oFileStatus.m_attribute & ~CFile::readOnly);
		try
		{
			CFile::SetStatus(lpDestFileName, oFileStatus);
		}
		catch(CFileException * poFE)
		{
			if(poFE->m_cause == CFileException::sharingViolation || poFE->m_cause == CFileException::accessDenied)
			{
				dwLastError = ERROR_SHARING_VIOLATION;
				goto sharing_viola;
			}
			return dwLastError;
		}
		goto try_copy;
	};
sharing_viola:
	if(dwLastError == ERROR_SHARING_VIOLATION)
	{
		CWinVersion oWinVersion;
		if(oWinVersion.GetVersion() == CWinVersion::WinNT || 
		   oWinVersion.GetVersion() == CWinVersion::Win2K ||
		   oWinVersion.GetVersion() == CWinVersion::WinXP)
		{
			CString oTmpDestFile(lpDestFileName);
			oTmpDestFile += ".pending";
			if(::CopyFile(lpSrcFileName,oTmpDestFile,FALSE))
			{
				CDLLHolder oDLLHolder("KERNEL32.DLL");
				BOOL (WINAPI * pMoveFileExA)(LPCSTR,LPCSTR,DWORD) = NULL;
				oDLLHolder.GetProcAddress(pMoveFileExA,"MoveFileExA");
				if(pMoveFileExA(oTmpDestFile,lpDestFileName,MOVEFILE_REPLACE_EXISTING | MOVEFILE_DELAY_UNTIL_REBOOT))
				{
					bInUse = true;
					return ERROR_SUCCESS;
				}
			}
			return ::GetLastError();
		}
		else
		{
			::WritePrivateProfileString
				(
				"RENAME",
				ShortFileNameFromLongName(lpDestFileName),
				ShortFileNameFromLongName(lpSrcFileName),
				"WININIT.INI"
				);
			bInUse = true;
			return ERROR_SUCCESS;
		}
	}
	else
	{
		return dwLastError;
	}
}

DWORD NAVOSetupFileExIfNewer(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse,bool & rbNewerInstalled)
{
	rbNewerInstalled = IsFileVersionNewer(lpDestFileName,lpSrcFileName);
	if(!rbNewerInstalled)
	{
		bInUse = false;
		return ERROR_SUCCESS;
	}
	return NAVOSetupFileEx(lpSrcFileName,lpDestFileName,bInUse);
}

errorcode RegUnregComponent(bool bUIAllowed,LPCTSTR lpPathName,bool bRegister)
{
	while(1)
	{
		HRESULT hResult = bRegister ? RegisterDLL(lpPathName) : UnregisterDLL(lpPathName);
		if(hResult == S_OK)
		{
			return ERCO_OK;
		}
		if(hResult == REGDB_E_WRITEREGDB && bUIAllowed) //not enough rights
		{
			CLogonAsUser oLogonAsUser;
			if(oLogonAsUser.Logon(true,::GetActiveWindow()))
			{
				continue;
			}
		}
		return ERCO_NOT_ENOUGH_RIGHTS;
	}
}


errorcode GetInprocServer(const CLSID & roCLSID,CString & roString)
{
	LONG lResult = SafeGetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\" + StringFromCLSID(roCLSID) + "\\InprocServer32", NULL, roString);
	if (lResult == ERROR_SUCCESS)
	{
		return ERCO_OK;
	}
	if(lResult == ERROR_ACCESS_DENIED)
	{
		return ERCO_NOT_ENOUGH_RIGHTS;
	}
	return ERCO_SYSCHK_BAD_CLSID;
}

errorcode GetInprocServer(LPCTSTR lpProgId,CString & roString)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(lpProgId),&oCLSID);
	if(hr != S_OK)
	{
		return ERCO_SYSCHK_BAD_PROGID;
	}
	return GetInprocServer(oCLSID,roString);
}

errorcode GetLocalServer(const CLSID & roCLSID,CString & roString)
{
	LONG lResult = SafeGetRegistryKeyString(HKEY_CLASSES_ROOT, "CLSID\\" + StringFromCLSID(roCLSID) + "\\LocalServer32", NULL, roString);
	if (lResult == ERROR_SUCCESS)
	{
		return ERCO_OK;
	}
	if(lResult == ERROR_ACCESS_DENIED)
	{
		return ERCO_NOT_ENOUGH_RIGHTS;
	}
	return ERCO_SYSCHK_BAD_CLSID;
}

errorcode GetLocalServer(LPCTSTR lpProgId,CString & roString)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(lpProgId),&oCLSID);
	if(hr != S_OK)
	{
		return ERCO_SYSCHK_BAD_PROGID;
	}
	return GetLocalServer(oCLSID,roString);
}

