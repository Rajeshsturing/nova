/*
	NAVO 2002 Project (2002)

	SETUP application

	core setup services
*/


#include "stdafx.h"
#include <winsvc.h>
#include "..\navoinstall\version.h"	// external declarations for this file
#include "resource.h"
#include "setup.h"
#include "coresetupserv.h"
#include "taskparam.h"
#include "componentinstaller.h"
#include "BrowseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _DEBUG
//http://www.navo.com.pl/NAVO Enterprise 2020/
//http://main.navo.com.pl/eb/
const TCHAR const * pcWWWRoot = _T ("http://www.navo.com.pl/eb/");
#else
const TCHAR const * pcWWWRoot = _T ("http://leszek/NAVO Enterprise 2020/");
#endif

extern CTaskParam _g_oTaskParam;
extern CNavoLog _g_oNavoLog;
extern CWindows _g_oWindows;

HRESULT download_url_2_file (LPCTSTR lpURL, LPCTSTR lpFile, bool bUI);

CWindows::CWindows ()
{
}

CWindows::~CWindows ()
{
}

void CWindows::_init_zero()
{
	TCHAR cWinDir[ MAX_PATH ] = _T ("C:\\");
	::GetWindowsDirectory (cWinDir, sizeof (cWinDir)/sizeof (TCHAR));
	m_oWinDirString = cWinDir;
	int nPos = m_oWinDirString.Find ('\\');
	if (nPos == -1)
	{
		m_oWinDriveString = _T (".\\");
	}
	else
	{
		m_oWinDriveString = CString (cWinDir, nPos);
	}
	EnsureEndingBackslash (m_oWinDirString);
	m_oWinSys32DirString = m_oWinDirString + _T ("SYSTEM32\\");
}

bool CWindows::_init ()
{
	ALL_TRY
	{
		{
			LONG lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProgramFilesDir", m_oProgramFilesDirString);

			while(lResult == ERROR_ACCESS_DENIED)
			{
				_g_oNavoLog << "not enough rights to retieve SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ProgramFilesDir";
				return false;

				//if (!_logon_as_admin ())
				//{
				//	_g_oNavoLog << "not enough rights to retieve SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ProgramFilesDir";
				//	return false;
				//}

				//lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProgramFilesDir", m_oProgramFilesDirString);
			}

			if (lResult != ERROR_SUCCESS)
			{
				_g_oNavoLog << "can not retieve SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ProgramFilesDir";
				return false;
			}

			EnsureEndingBackslash (m_oProgramFilesDirString);
		}

		return true;
	}
	ALL_CATCH (CNavoException & roException)
	{
		AfxMessageBox (roException.BuildCompleteErrorString ());
		return false;
	}
}

bool CWindows::_check ()
{
	if (m_oWinVersion.GetVersion () == CWinVersion::Win95)
	{
		_g_oNavoLog << ("Found Win95. User informed about required Windows version. Exiting.");
		AfxMessageBox (IDS_WIN98_OR_ABOVE_REQUIRED, MB_OK | MB_ICONSTOP);
		return false;
	}
	//HKEY_LOCAL_MACHINE\Software\Microsoft\Internet Explorer - "Version" 
	//4.72.3612.1713   IE 4.01 SP2
	CString oIEVersionString;
	if (SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Internet Explorer", "Version", oIEVersionString))
	{
		_g_oNavoLog << ("Cannot read IE version (may be not installed)");
		return false;
	}

	_g_oNavoLog << ("IE version is " + oIEVersionString);

	if (oIEVersionString < "4.72.3612.1713")
	{
		AfxMessageBox (IDS_IE401SP2_OR_ABOVE_REQUIRED, MB_OK | MB_ICONSTOP);
		_g_oNavoLog << ("User informed about required IE version. Exiting.");
		return false;
	}

	return true;
}

bool CWindows::_logon_as_admin ()
{
	return CLogonAsUser ().Logon (true, ::GetActiveWindow ());
}

bool CWindows::is_valid_location (const CString & roPath)
{
	CFile oFileToTest;
	if (oFileToTest.Open (roPath, CFile::modeRead))
	{
		oFileToTest.Close ();
		return true;
	}
	return false;
}

CString CWindows::FindFirstCDROMDrive ()
{
	for (char cDrive = 'C'; cDrive <= 'Z'; cDrive++)
	{
		CString oString;
		oString.Format ("%c:\\", cDrive);
		if (::GetDriveType (oString) == DRIVE_CDROM)
		{
			return oString;
		}
	}
	return "";
}

setuperror CWindows::_provide_source_file_path (CString & roLocation, LPCTSTR lpSubDir, LPCTSTR lpKeyFile, LPCTSTR lpComponentHumanName)
{
	CString oFileName (lpKeyFile);
	CString oRelativePath (lpSubDir);
	EnsureEndingBackslash (oRelativePath);
	oRelativePath += oFileName;

	TRACE (oRelativePath + "\n");
	CString oRootDir = _g_oTaskParam._get_root_source ();
	EnsureEndingBackslash (oRootDir);

	//sprawdŸ root-source
	if (is_valid_location (oRootDir + oRelativePath))
	{
		roLocation = oRootDir + oRelativePath;
		return stpe_ok;
	}


	//sprawdŸ lokalizacjê z ostatniej instalacji
	oRootDir.Empty ();
	
	LONG lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName (), "MediaSource", oRootDir);

	while(lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "can not check last installation source";
		return stpe_not_enough_rights;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not clear pending flag";
		//	return stpe_not_enough_rights;
		//}

		//lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName (), "MediaSource", oRootDir);
	}
	
	if (!oRootDir.IsEmpty ())
	{
		EnsureEndingBackslash (oRootDir);

		if (is_valid_location (oRootDir + oRelativePath))
		{
			_g_oTaskParam._set_root_source (oRootDir);
			roLocation = oRootDir + oRelativePath;
			return stpe_ok;
		}
	}

	//check cdrom
	oRootDir = FindFirstCDROMDrive ();

	if (!oRootDir.IsEmpty ())
	{
		EnsureEndingBackslash (oRootDir);

		if (is_valid_location (oRootDir + oRelativePath))
		{
			roLocation = oRootDir + oRelativePath;
			return stpe_ok;
		}
	}

	CString oUserDir = _g_oTaskParam._get_user_pointed_dir ();

	if (!oUserDir.IsEmpty ())
	{
		EnsureEndingBackslash (oUserDir);

		if (is_valid_location (oUserDir + oFileName))
		{
			roLocation = oUserDir + oFileName;
			return stpe_ok;
		}
	}

	//download if allowed

	CBrowseDlg oBrowse;

	bool bDownload = _g_oTaskParam._is_internet_download ();

	while (!bDownload && !is_valid_location(roLocation))
	{
		CBrowseDlg oBrowse;
		oBrowse.m_strFile = oFileName;
		oBrowse.m_edMessage = "Instalator nie mo¿e odnaleŸæ pliku " + oFileName;

		if ( oBrowse.DoModal () == IDOK)
		{

			if (oBrowse.m_bDownload)
			{
				bDownload = oBrowse.m_bDownload;
			}
			else
			{
				roLocation = oBrowse.m_strDir + oFileName;
				_g_oTaskParam._set_user_pointed_dir(oBrowse.m_strDir);
			}
		}
		else
		{
			return stpe_user_break;
		}

		_g_oTaskParam._set_internet_download( oBrowse.m_bDownloadAll);
	}

	oRelativePath.MakeLower ();
	CString oUniqueFilePath; 

	if (!m_oDownloadedFilesMap.Lookup (oRelativePath, oUniqueFilePath))
	{
		oRootDir = pcWWWRoot;

		CString oExt;

		int dotPos = oFileName.ReverseFind('.');

		if (dotPos >= 0)
		{
			oExt = oFileName.Mid (dotPos + 1);
		}
		else
		{
			oExt.Empty ();
		}
		
		oUniqueFilePath = GenerateUniqueFileName ("NS", oExt);

		CSimpleOleInitHolder oSimpleOleInitHolder;

		HRESULT hr = download_url_2_file (oRootDir + oRelativePath, oUniqueFilePath, true);
		//setuperror err = _g_oWindows.DownloadFile(oRootDir + oRelativePath, oUniqueFilePath);
		//if( err != stpe_ok)
		//{
		//	return err;
		//}
		if (hr == E_ABORT)
		{
			return stpe_user_break;
		}

		if (hr != S_OK)
		{
			return stpe_download_failed;
		}
		
		m_oDownloadedFilesMap [oRelativePath] = oUniqueFilePath;
	}

	ASSERT (is_valid_location (oUniqueFilePath));

	roLocation = oUniqueFilePath;
	return stpe_ok;
}

bool CWindows::_test_need_install (eNEComponent eNEC)
{
	switch (eNEC)
	{
	case nec_dcom:
	{
		return false;
	/*	if (m_oWinVersion.GetVersion () == CWinVersion::Win98)
		{
			return CDCOMInstaller ()._need_install ();
		}
		else
		{
			return false;
		}*/
	}
	case nec_vbscript:
	{
		return false;
	//	return CVBSInstaller()._need_install();
	}
	case nec_engine:
	{
		return CNE2002Installer ()._need_install ();
	}
	case nec_wininst:
	{
		return false;
	//	return CWinInstInstaller ()._need_install ();
	}
	case nec_dotnet:
	{
		return CDotNetInstaller()._need_install();
	}
	default:
		return CComponentInstaller (eNEC)._need_install ();
	}
}

setuperror CWindows::_install_component (eNEComponent eNEC)
{
	switch (eNEC)
	{
	case nec_dcom:
	{
		return CDCOMInstaller ()._install ();
	}
	case nec_vbscript:
	{
		return CVBSInstaller()._install();
	}
	case nec_engine:
	{
		return CNE2002Installer ()._install ();
	}
	case nec_wininst:
	{
		return CWinInstInstaller ()._install ();
	}
	case nec_dotnet:
	{
		return CDotNetInstaller()._install();
	}
	default:
		return CComponentInstaller (eNEC)._install ();
	}
}



setuperror CWindows::CheckCOMObject (const CLSID & rCLSID, setuperror CodeOnFail)
{
	ALL_TRY
	{
		CSimpleOleInitHolder oSimpleOleInitHolder;
		SCP<IUnknown> poTestSP;
		poTestSP.CreateInstance (rCLSID, CLSCTX_ALL);
	}
	ALL_CATCH (CNavoException & roNavoException)
	{
		_g_oNavoLog << ("check com object threw " + roNavoException.BuildCompleteErrorString ());
		return CodeOnFail;
	}
	return stpe_ok;
}

setuperror CWindows::CheckCOMObject (LPCTSTR lpProgId, setuperror CodeOnFail)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString ( (LPOLESTR) (LPCWSTR)CBStr (lpProgId), &oCLSID);
	if (hr != S_OK)
	{
		return CodeOnFail;
	}
	return CheckCOMObject (oCLSID, CodeOnFail);
}

setuperror CWindows::GetInprocServer (const CLSID & roCLSID, CString & roString)
{
	LONG lResult = SafeGetRegistryKeyString (HKEY_CLASSES_ROOT, "CLSID\\" + StringFromCLSID (roCLSID) + "\\InprocServer32", NULL, roString);

	if(lResult == ERROR_ACCESS_DENIED)
	{
		return stpe_not_enough_rights;
	}

	if (lResult != ERROR_SUCCESS)
	{
		return stpe_syschk_bad_clsid;
	}

	return stpe_ok;
}

setuperror CWindows::GetInprocServer (LPCTSTR lpProgId, CString & roString)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString ( (LPOLESTR) (LPCWSTR)CBStr (lpProgId), &oCLSID);
	if (hr != S_OK)
	{
		return stpe_syschk_bad_progid;
	}
	return GetInprocServer (oCLSID, roString);
}

setuperror CWindows::GetLocalServer (const CLSID & roCLSID, CString & roString)
{
	LONG lResult = SafeGetRegistryKeyString (HKEY_CLASSES_ROOT, "CLSID\\" + StringFromCLSID (roCLSID) + "\\LocalServer32", NULL, roString);
	
	if (lResult == ERROR_ACCESS_DENIED)
	{
		return stpe_not_enough_rights;
	}

	if (lResult != ERROR_SUCCESS)
	{
		return stpe_syschk_bad_clsid;
	}

	return stpe_ok;
}

setuperror CWindows::GetLocalServer (LPCTSTR lpProgId, CString & roString)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString ( (LPOLESTR) (LPCWSTR)CBStr (lpProgId), &oCLSID);
	if (hr != S_OK)
	{
		return stpe_syschk_bad_progid;
	}
	return GetLocalServer (oCLSID, roString);
}

HPALETTE CWindows::CreateDIBPalette (LPBITMAPINFO lpbmi, LPINT lpiNumColors)
{
	LPBITMAPINFOHEADER lpbi;
	LPLOGPALETTE lpPal;
	HANDLE hLogPal;
	HPALETTE hPal = NULL;
	int i;

	lpbi = (LPBITMAPINFOHEADER)lpbmi;
	if (lpbi->biBitCount <= 8)
	{
		*lpiNumColors = (1 << lpbi->biBitCount);
	}
	else
	{
		*lpiNumColors = 0;  // No palette needed for 24 BPP DIB
	};
	if (lpbi->biClrUsed > 0)
	{
		*lpiNumColors = lpbi->biClrUsed;  // Use biClrUsed
	}
	if (*lpiNumColors)
	{
		hLogPal = GlobalAlloc (GHND, sizeof (LOGPALETTE) + sizeof (PALETTEENTRY) * (*lpiNumColors));
		lpPal = (LPLOGPALETTE) GlobalLock (hLogPal);
		lpPal->palVersion = 0x300;
		lpPal->palNumEntries = (unsigned short) *lpiNumColors;
		for (i = 0;  i < *lpiNumColors;  i++)
		{
			lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
			lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
			lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
			lpPal->palPalEntry[i].peFlags = 0;
		}
		hPal = CreatePalette (lpPal);
		GlobalUnlock (hLogPal);
		GlobalFree (hLogPal);
	}
	return hPal;
};

HBITMAP CWindows::LoadResourceBitmap (HINSTANCE hInstance, LPCTSTR lpString, HPALETTE FAR* lphPalette)
{
	HGLOBAL hGlobal;
	HBITMAP hBitmapFinal = NULL;
	LPBITMAPINFOHEADER  lpbi;
	HDC hdc;
	int iNumColors;
	HRSRC hRsrc = FindResource (hInstance, lpString, RT_BITMAP);
	if (hRsrc)
	{
		hGlobal = LoadResource (hInstance, hRsrc);
		lpbi = (LPBITMAPINFOHEADER)LockResource (hGlobal);

		hdc = GetDC (NULL);
		*lphPalette =  CreateDIBPalette ( (LPBITMAPINFO)lpbi, &iNumColors);
		if (*lphPalette)
		{
			SelectPalette (hdc, *lphPalette, FALSE);
			RealizePalette (hdc);
		}

		hBitmapFinal = CreateDIBitmap (hdc, (LPBITMAPINFOHEADER)lpbi, (LONG)CBM_INIT, (LPSTR)lpbi + lpbi->biSize + iNumColors * sizeof (RGBQUAD), (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
		ReleaseDC (NULL, hdc);
		UnlockResource (hGlobal);
		FreeResource (hGlobal);
	}
	return hBitmapFinal;
} 

setuperror CWindows::UnregComponent (bool bUIAllowed, LPCTSTR lpPathName)
{
	while (1)
	{
		HRESULT hResult = UnregisterDLL (lpPathName);

		if (hResult == S_OK)
		{
			return stpe_ok;
		}

		if (hResult == REGDB_E_WRITEREGDB && bUIAllowed) //not enough rights
		{
			return stpe_not_enough_rights;
			
			//if (_g_oWindows._logon_as_admin ())
			//{
			//	continue;
			//}
		}

		return stpe_not_enough_rights;
	}
}

setuperror CWindows::RegComponent (bool bUIAllowed, LPCTSTR lpPathName)
{
	while (1)
	{
		HRESULT hResult = RegisterDLL (lpPathName);

		if (hResult == S_OK || hResult == SELFREG_E_TYPELIB)
		{
			return stpe_ok;
		}

		if (hResult == REGDB_E_WRITEREGDB && bUIAllowed) //not enough rights
		{
			return stpe_not_enough_rights;

			//if (_g_oWindows._logon_as_admin ())
			//{
			//	continue;
			//}
		}

		return stpe_not_enough_rights;
	}
}

setuperror CWindows::RegDotNetComponent(bool /*bUIAllowed*/,LPCTSTR lpNXManToolPath,LPCTSTR lpPathName)
{
	long nExitCode;
	CString oNxManToolString = lpNXManToolPath;
	EnsureEndingBackslash(oNxManToolString);
	CString oSafePathName = lpPathName;
//	oSafePathName.Replace("\"","\"\"");
	oSafePathName = "\"" + oSafePathName + "\"";
	errorcode eErrorCode = ExecuteProcess(oNxManToolString + "navo2012.net.manager.exe", oNxManToolString, 
		" -regasm " + oSafePathName, SW_HIDE, nExitCode, false);

	if(eErrorCode != ERCO_OK)
	{
		return stpe_dotnetregister_failed;
	}
	else
	{
		return stpe_ok;
	}
}

long NAVOGetDiskFreeSpace(LPCTSTR lpDir)
{
	CString oTestString(lpDir);
	int nPos = oTestString.Find('\\');
	ASSERT(nPos != -1);
	oTestString = oTestString.Left(nPos + 1);
	CDLLHolder oDLLHolder("KERNEL32.DLL");
	BOOL (WINAPI * pGetDiskFreeSpaceExA)(LPCSTR,PULARGE_INTEGER,PULARGE_INTEGER,PULARGE_INTEGER) = NULL;
	oDLLHolder.GetProcAddress(pGetDiskFreeSpaceExA,"GetDiskFreeSpaceExA");
	ULARGE_INTEGER ulFreeBytesAvail;
	ULARGE_INTEGER ulTotalNumberOfBytes;
	ULARGE_INTEGER ulTotalNumberOfFreeBytes;
	if(pGetDiskFreeSpaceExA((LPCTSTR)oTestString,&ulFreeBytesAvail,&ulTotalNumberOfBytes,&ulTotalNumberOfFreeBytes))
	{
		return long(ulTotalNumberOfFreeBytes.QuadPart / ULONGLONG(1024 * 1024));
	}
	DWORD dwLastError = ::GetLastError();
	ASSERT(false);
	return -1;	//error
}

DWORD NAVOSetupFileEx (LPCTSTR lpSrcFileName, LPCTSTR lpDestFileName, bool & bInUse)
{
	bInUse = false;

try_copy:
	if (::CopyFile (lpSrcFileName, lpDestFileName, FALSE))
	{
		return ERROR_SUCCESS;
	}

	DWORD dwLastError = ::GetLastError ();

	if (dwLastError == ERROR_ACCESS_DENIED)
	{
		CFileStatus oFileStatus;
		CFile::GetStatus (lpDestFileName, oFileStatus);
		oFileStatus.m_attribute = (BYTE) (oFileStatus.m_attribute & ~CFile::readOnly);

		try
		{
			CFile::SetStatus (lpDestFileName, oFileStatus);
		}
		catch (CFileException * poFE)
		{
			if (poFE->m_cause == CFileException::sharingViolation || poFE->m_cause == CFileException::accessDenied)
			{
				dwLastError = ERROR_SHARING_VIOLATION;
				goto sharing_viola;
			}
			return dwLastError;
		}

		goto try_copy;
	};

sharing_viola:
	if (dwLastError == ERROR_SHARING_VIOLATION)
	{
		CWinVersion oWinVersion;

		if (oWinVersion.GetVersion () == CWinVersion::WinNT || 
		   oWinVersion.GetVersion () == CWinVersion::Win2K ||
		   oWinVersion.GetVersion () == CWinVersion::WinXP)
		{
			CString oTmpDestFile (lpDestFileName);
			oTmpDestFile += ".pending";
			if (::CopyFile (lpSrcFileName, oTmpDestFile, FALSE))
			{
				CDLLHolder oDLLHolder ("KERNEL32.DLL");
				BOOL (WINAPI * pMoveFileExA) (LPCSTR, LPCSTR, DWORD) = NULL;
				oDLLHolder.GetProcAddress (pMoveFileExA, "MoveFileExA");
				if (pMoveFileExA (oTmpDestFile, lpDestFileName, MOVEFILE_REPLACE_EXISTING | MOVEFILE_DELAY_UNTIL_REBOOT))
				{
					bInUse = true;
					return ERROR_SUCCESS;
				}
			}
			return ::GetLastError ();
		}
		else
		{
			::WritePrivateProfileString
				 (
				"RENAME", 
				ShortFileNameFromLongName (lpDestFileName), 
				ShortFileNameFromLongName (lpSrcFileName), 
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

DWORD NAVOSetupFileExIfNewer (LPCTSTR lpSrcFileName, LPCTSTR lpDestFileName, bool & bInUse, bool & rbNewerInstalled)
{
	rbNewerInstalled = IsFileVersionNewer (lpDestFileName, lpSrcFileName);
	if (!rbNewerInstalled)
	{
		bInUse = false;
		return ERROR_SUCCESS;
	}
	return NAVOSetupFileEx (lpSrcFileName, lpDestFileName, bInUse);
}

//-----------------------------------------------------------------------------
// implementation
//-----------------------------------------------------------------------------
SC_HANDLE virtual_OpenSCManager (LPCTSTR lpMachineName, LPCTSTR lpDataBaseName, DWORD dwDesiredAccess)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	SC_HANDLE (WINAPI *pFunction) (LPCTSTR, LPCTSTR, DWORD);
	oDLLHolder.GetProcAddress (pFunction, _T ("OpenSCManagerA") );
	return pFunction (lpMachineName, lpDataBaseName, dwDesiredAccess);
}

BOOL virtual_CloseServiceHandle (SC_HANDLE hHandle)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	BOOL (WINAPI *pFunction) (SC_HANDLE);
	oDLLHolder.GetProcAddress (pFunction, _T ("CloseServiceHandle") );
	return pFunction (hHandle);
}

SC_HANDLE virtual_OpenService (SC_HANDLE hSCManager, LPCTSTR lpServiceName, DWORD dwDesiredAccess)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	SC_HANDLE (WINAPI *pFunction) (SC_HANDLE, LPCTSTR, DWORD);
	oDLLHolder.GetProcAddress (pFunction, _T ("OpenServiceA") );
	return pFunction (hSCManager, lpServiceName, dwDesiredAccess);
}

BOOL virtual_StartService (SC_HANDLE hService, DWORD dwNumServiceArgs, LPCTSTR* lpServiceArgVectors)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	BOOL (WINAPI *pFunction) (SC_HANDLE, DWORD, LPCTSTR*);
	oDLLHolder.GetProcAddress (pFunction, _T ("StartServiceA") );
	return pFunction (hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL virtual_ControlService (SC_HANDLE hService, DWORD dwControl, LPSERVICE_STATUS lpServiceStatus)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	BOOL (WINAPI *pFunction) (SC_HANDLE, DWORD, LPSERVICE_STATUS);
	oDLLHolder.GetProcAddress (pFunction, _T ("ControlService") );
	return pFunction (hService, dwControl, lpServiceStatus);
}

BOOL virtual_QueryServiceStatus (SC_HANDLE hService, LPSERVICE_STATUS lpServiceStatus)
{
	ASSERT (_g_oWindows._get_version () >= CWinVersion::WinNT);
	CDLLHolder oDLLHolder (_T ("ADVAPI32.DLL"));
	BOOL (WINAPI *pFunction) (SC_HANDLE, LPSERVICE_STATUS);
	oDLLHolder.GetProcAddress (pFunction, _T ("QueryServiceStatus") );
	return pFunction (hService, lpServiceStatus);
}

//-----------------------------------------------------------------------------

setuperror CVirtualNTServiceManager::start ()
{
	if (_g_oWindows._get_version () < CWinVersion::WinNT)
	{
		return stpe_ok;
	}
	SC_HANDLE hSCM = virtual_OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
	{
		DWORD dwErrorCode = GetLastError ();
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			return stpe_not_enough_rights;
		};
	}
	SC_HANDLE hService = virtual_OpenService (hSCM, m_oServiceNameString, SERVICE_ALL_ACCESS);
	if (!hService)
	{
		virtual_CloseServiceHandle (hSCM);
		return stpe_openservice_failed;
	}
	BOOL bResult = virtual_StartService (hService, 0, NULL);

	virtual_CloseServiceHandle (hService);
	virtual_CloseServiceHandle (hSCM);
	
	return bResult ? stpe_ok : stpe_startservice_failed;
}

setuperror CVirtualNTServiceManager::stop ()
{
	if (_g_oWindows._get_version () < CWinVersion::WinNT)
	{
		return stpe_ok;
	}
	SC_HANDLE hSCM = virtual_OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
	{
		DWORD dwErrorCode = GetLastError ();
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			return stpe_not_enough_rights;
		};
	}
	SC_HANDLE hService = virtual_OpenService (hSCM, m_oServiceNameString, SERVICE_ALL_ACCESS);
	if (!hService)
	{
		virtual_CloseServiceHandle (hSCM);
		return stpe_openservice_failed;
	}
	SERVICE_STATUS ss;
	BOOL bResult = virtual_ControlService (hService, SERVICE_CONTROL_STOP, &ss);

	virtual_CloseServiceHandle (hService);
	virtual_CloseServiceHandle (hSCM);
	
	return bResult ? stpe_ok : stpe_stopservice_failed;
}

setuperror CVirtualNTServiceManager::is_running (bool & rbRunning)
{
	rbRunning = false;
	if (_g_oWindows._get_version () < CWinVersion::WinNT)
	{
		return stpe_ok;
	}
	SC_HANDLE hSCM = virtual_OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCM)
	{
		DWORD dwErrorCode = GetLastError ();
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			return stpe_not_enough_rights;
		};
	}
	SC_HANDLE hService = virtual_OpenService (hSCM, m_oServiceNameString, SERVICE_ALL_ACCESS);
	if (!hService)
	{
		virtual_CloseServiceHandle (hSCM);
		return stpe_openservice_failed;
	}
	SERVICE_STATUS ss;
	memset (&ss, 0, sizeof (ss));
	BOOL bResult = virtual_QueryServiceStatus (hService, &ss);
	if (bResult)
	{
		if (ss.dwCurrentState == SERVICE_RUNNING)
		{
			bResult = virtual_ControlService (hService, SERVICE_CONTROL_INTERROGATE, &ss);
			if (bResult)
			{
				rbRunning = (ss.dwCurrentState == SERVICE_RUNNING);
			}
		}
	}

	virtual_CloseServiceHandle (hService);
	virtual_CloseServiceHandle (hSCM);
	
	return bResult ? stpe_ok : stpe_getstateservice_fail;
}


bool CWindows::_shutdown()
{
   HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 
 
   // Get a token for this process. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
   // Get the LUID for the shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get the shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
      return FALSE; 
 
   // Shut down the system and force all applications to close. 
 
   if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)) 
      return FALSE; 

   return TRUE;
}

