/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	OS related utility functions
*/

#include "stdafx.h"

#ifndef _MINI_CORE_
#include <shlwapi.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _MINI_CORE_
#pragma comment(lib,"Shlwapi.lib")
#endif

LONG SafeGetRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,CString & roDataString)
{
	HKEY hKey;
	LONG lResult= ::RegOpenKeyEx(hKeyClass, lpSubKey, 0, KEY_READ,&hKey);
	if (lResult != ERROR_SUCCESS) 
	{
		return lResult;
	}

	DWORD cbData = 512;
	DWORD dwType = REG_SZ;
	lResult = ::RegQueryValueEx(hKey, lpName, NULL,&dwType, NULL,&cbData);
	BYTE * pBuffer = (LPBYTE) roDataString.GetBuffer(cbData);
	lResult = ::RegQueryValueEx(hKey, lpName, NULL,&dwType, pBuffer,&cbData);
	::RegCloseKey(hKey);
	roDataString.ReleaseBuffer();
	
	//if expandable - expand
	if(dwType == REG_EXPAND_SZ)
	{
		TCHAR cNothing[2];
		cbData = ExpandEnvironmentStrings((LPCTSTR)roDataString,cNothing,1) + 1;
		CString oString;
		ExpandEnvironmentStrings((LPCTSTR)roDataString,oString.GetBuffer(cbData),cbData);
		oString.ReleaseBuffer();
		roDataString = oString;
	}
	return lResult;
}

LONG SafeSetRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,LPCTSTR lpValue)
{
	HKEY hkGlobal  = NULL;
	DWORD dwDisposition;
	LONG lResult= ::RegCreateKeyEx(hKeyClass, lpSubKey, 0,_T(""), REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hkGlobal, &dwDisposition);
	if (lResult != ERROR_SUCCESS)
	{
		return lResult;
	}
	ASSERT (dwDisposition == REG_CREATED_NEW_KEY || dwDisposition == REG_OPENED_EXISTING_KEY);
	if(lpValue == NULL)		//no value = just create entry
	{
		lpValue = _T("");
	}
	lResult= ::RegSetValueEx(hkGlobal, lpName, 0, REG_SZ,
		(CONST BYTE*)lpValue, _tcslen(lpValue) +1);
	::RegCloseKey(hkGlobal);
	return lResult;
}

LONG SafeGetRegistryKeyDword(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,DWORD & rdwData)
{
	HKEY hKey;
	LONG lResult= ::RegOpenKeyEx(hKeyClass, lpSubKey, 0, KEY_READ,&hKey);
	if (lResult != ERROR_SUCCESS) 
	{
		return lResult;
	}

	DWORD cbData = sizeof(DWORD);
	DWORD dwType = REG_DWORD;
	lResult = ::RegQueryValueEx(hKey, lpName, NULL, &dwType, (LPBYTE)&rdwData, &cbData);
	::RegCloseKey(hKey);
	return lResult;
}

LONG SafeSetRegistryKeyDword(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,DWORD dwData)
{
	HKEY hkGlobal  = NULL;
	DWORD dwDisposition;
	LONG lResult= ::RegCreateKeyEx(hKeyClass, lpSubKey, 0,_T(""), REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hkGlobal, &dwDisposition);
	if (lResult != ERROR_SUCCESS)
	{
		return lResult;
	}
	ASSERT (dwDisposition == REG_CREATED_NEW_KEY || dwDisposition == REG_OPENED_EXISTING_KEY);
	lResult= ::RegSetValueEx(hkGlobal, lpName, 0, REG_DWORD,(CONST BYTE*)&dwData, sizeof(DWORD));
	::RegCloseKey(hkGlobal);
	return lResult;
}


LONG EnumRegistryKeys(HKEY hKeyClass, LPCTSTR lpSubKey,CArray<CString,LPCTSTR> & roResultArray)
{
	HKEY hKey;
	LONG lResult = ::RegOpenKeyEx(hKeyClass, lpSubKey, 0, KEY_READ,&hKey);
	DWORD Index = 0;
	if (lResult != ERROR_SUCCESS) 
	{
		goto _exit;
	}
	do
	{
		TCHAR cKeyName[2048];
		DWORD nBufferLen = sizeof(cKeyName);
		FILETIME dummy;
		lResult = ::RegEnumKeyEx(hKey,Index,cKeyName,&nBufferLen,NULL,NULL,NULL,&dummy);
		if(lResult != ERROR_SUCCESS)
		{
			break;
		}
		cKeyName[nBufferLen] = '\0';
		roResultArray.Add(cKeyName);
		Index++;
	}
	while(true);
	::RegCloseKey(hKey);
_exit:
	return (lResult == ERROR_NO_MORE_ITEMS) ? ERROR_SUCCESS : lResult;
}

LONG SafeGetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, CArray <char, char &> & roArray)
{
	HKEY hKey;
	LONG lResult = ::RegOpenKeyEx(hKeyClass, lpSubKey, 0, KEY_READ,&hKey);
	DWORD cbData = 0;
	DWORD dwType = REG_BINARY;
	if (lResult != ERROR_SUCCESS) 
	{
		goto _exit;
	}
	lResult = ::RegQueryValueEx(hKey, lpName, NULL, &dwType, NULL, &cbData);
	if (lResult != ERROR_SUCCESS)
	{
		goto _exit1;
	};
	roArray.SetSize(cbData);
	lResult = ::RegQueryValueEx(hKey, lpName, NULL, &dwType, (BYTE *)roArray.GetData(), &cbData);
_exit1:
	::RegCloseKey(hKey);
_exit:
	return lResult;
}

LONG SafeSetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, LPCVOID pValue, long lSize)
{
	HKEY hkGlobal  = NULL;
	DWORD dwDisposition;
	LONG lResult = ::RegCreateKeyEx(hKeyClass, lpSubKey, 0, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkGlobal, &dwDisposition);
	if (lResult != ERROR_SUCCESS)
	{
		goto _exit;
	}
	ASSERT (dwDisposition == REG_CREATED_NEW_KEY || dwDisposition == REG_OPENED_EXISTING_KEY);
	lResult = ::RegSetValueEx(hkGlobal, lpName, 0, REG_BINARY, (CONST BYTE*)pValue, lSize);
	::RegCloseKey(hkGlobal);
_exit:
	return lResult;
}

LONG SafeDeleteRegistryValue(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName)
{
	HKEY hKey;
	LONG lResult = ::RegOpenKeyEx(hKeyClass, lpSubKey, 0, KEY_ALL_ACCESS,&hKey);
	if (lResult != ERROR_SUCCESS) 
	{
		goto _exit;
	}
	lResult = ::RegDeleteValue (hKey, lpName);
	if (lResult != ERROR_SUCCESS)
	{
		goto _exit1;
	};
_exit1:
	::RegCloseKey(hKey);
_exit:
	return lResult;
}

LONG SafeDeleteRegistryKey(HKEY hKeyClass, LPCTSTR lpSubKey)
{
	return ::RegDeleteKey(hKeyClass, lpSubKey);
}

#ifndef _MINI_CORE_
DWORD RecursiveDeleteRegistryKey(HKEY hKeyClass, LPCTSTR lpSubKey)
{
	return ::SHDeleteKey(hKeyClass, lpSubKey);
}
#endif

CWinVersion::CWinVersion()
{
	OSVERSIONINFO ovi;
	ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	VERIFY(::GetVersionEx(&ovi));
	m_iVersion = WinNT;
	if( VER_PLATFORM_WIN32_WINDOWS == ovi.dwPlatformId )
	{
		bool bW98 = ((ovi.dwMajorVersion > 4) ||
			((ovi.dwMajorVersion == 4) && (ovi.dwMinorVersion > 0)));
		m_iVersion = bW98 ? Win98 : Win95;
	}
	else if(VER_PLATFORM_WIN32_NT== ovi.dwPlatformId )
	{
		m_iVersion = (ovi.dwMajorVersion > 4) ? Win2K : WinNT;
	}
}


HRESULT RegisterDLL(LPCTSTR pcFileName)
{
	LPCTSTR pcLastBS = _tcsrchr(pcFileName,'\\');
	CString oString(pcFileName,(pcLastBS ? pcLastBS - pcFileName + 1 : _tcslen(pcFileName)));
	CDirectoryChangeHolder oDCH(oString);

	CDLLHolder oLMH(pcFileName);
	HRESULT (__stdcall *pFunction)();
	oLMH.GetProcAddress(pFunction, "DllRegisterServer");
	return pFunction();
}

HRESULT UnregisterDLL(LPCTSTR pcFileName)
{
	LPCTSTR pcLastBS = _tcsrchr(pcFileName,'\\');
	CString oString(pcFileName,(pcLastBS ? pcLastBS - pcFileName + 1 : _tcslen(pcFileName)));
	CDirectoryChangeHolder oDCH(oString);

	CDLLHolder oLMH(pcFileName);
	HRESULT (__stdcall * pFunction)();
	oLMH.GetProcAddress(pFunction, "DllUnregisterServer");

	return pFunction();
}

//-------------------------------------- 
//	"smart" execute process
//--------------------------------------

class CCloseHandleHolder
{
public:
	CCloseHandleHolder(HANDLE hHandle):
		m_hHandle(hHandle)
	{
	};
	~CCloseHandleHolder()
	{
		if (m_hHandle != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(m_hHandle);
		};
	};
	HANDLE m_hHandle;
};

errorcode ExecuteProcess(
	LPCTSTR pcProcessPath,
	LPCTSTR pcProcessDirectory,
	LPCTSTR pcArguments,
	long lShowCommand,
	long & lExitCode,
	bool bExitAfterLaunch)
{
	bool bReboot = false;
	CString oCmdLineString = CString('\"') + pcProcessPath + '\"' + CString(" ") + pcArguments;
	ASSERT(pcProcessPath);
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	::ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	StartupInfo.wShowWindow = (WORD)lShowCommand;
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.cb = sizeof (STARTUPINFO);
	TCHAR acCmdLine[_MAX_PATH];
	_tcsncpy(acCmdLine, oCmdLineString, sizeof(acCmdLine))[sizeof(acCmdLine) / sizeof(TCHAR) - sizeof(TCHAR)] = 0;
	
	SECURITY_ATTRIBUTES SecurityAttributes;
	SecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecurityAttributes.bInheritHandle = true;
	SecurityAttributes.lpSecurityDescriptor = NULL;

	if (!::CreateProcess(
		NULL,					// pointer to name of executable module	
		acCmdLine,				// pointer to command line string
		&SecurityAttributes,	// process security attributes
		&SecurityAttributes,	// thread security attributes
		TRUE,					// handle inheritance flag
		NORMAL_PRIORITY_CLASS,	// creation flags
		NULL,					// pointer to new environment block
		pcProcessDirectory,		// pointer to current directory name
		&StartupInfo,			// pointer to STARTUPINFO
		&ProcessInfo))			// pointer to PROCESS_INFORMATION
	{
		DWORD dwErrorCode = ::GetLastError();
		_RPT2(_CRT_ASSERT, "Unable to execute process %s. Error = %d", acCmdLine, dwErrorCode);

		if (dwErrorCode == ERROR_DIRECTORY || ERROR_PATH_NOT_FOUND || dwErrorCode == ERROR_FILE_NOT_FOUND)
		{
			return ERCO_UNABLE_TO_OPEN_FILE;
		};

		return ERCO_CREATEPROCESSFAILED;
	};

	CCloseHandleHolder oProcessCloseHandleHolder(ProcessInfo.hProcess);
	CCloseHandleHolder oThreadCloseHandleHolder(ProcessInfo.hThread);

	if (bExitAfterLaunch)
	{
		bReboot = true;
	}
	else
	{
		while (true)
		{
			DWORD dwResult = ::MsgWaitForMultipleObjects(1, &ProcessInfo.hProcess, FALSE, INFINITE, QS_ALLINPUT);

			if (dwResult == WAIT_OBJECT_0 + 1)
			{
				MSG oMsg;
				while (::PeekMessage(&oMsg, 0, 0, 0, PM_REMOVE))
				{
					if (oMsg.message == WM_QUIT)
					{
						bReboot = true;
						break;
					};
					if (oMsg.message == WM_ENDSESSION ||
						oMsg.message == WM_CLOSE)
					{
						bReboot = true;
					};
					::TranslateMessage(&oMsg);
					::DispatchMessage(&oMsg);
					if (bReboot)
					{
						break;
					};
				};
			}
			else
			{
				ASSERT(dwResult == WAIT_OBJECT_0);
				break;
			};

			if (bReboot)
			{
				break;
			};
		};
	};

	if (!bReboot)
	{
		if (!::GetExitCodeProcess(ProcessInfo.hProcess, (LPDWORD)&lExitCode))
		{
			lExitCode = -1;
		};
	}
	else
	{
		lExitCode = 0;
	};

	return bReboot ? ERCO_SYSCHK_NEEDREBOOT : ERCO_OK;
};

bool is_memory_low()
{
	//OS_API_CALL
	MEMORYSTATUS oMemoryStatus;
	::GlobalMemoryStatus(&oMemoryStatus);
	return (oMemoryStatus.dwMemoryLoad >= 95);
}
