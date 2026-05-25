/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	OS related utility functions
*/

#ifndef _OSUTIL_H_
#define _OSUTIL_H_

__declspec(noreturn) inline void ThrowRegException(long lCode, LPCTSTR pcKeyName)
{
	ThrowNavoException3(ERCO_INTERNAL_REGEXCEPTION, IDPAGE_NOTAVAILABLE, 
		pcKeyName ? _T(" "): _T(""), pcKeyName ? pcKeyName : _T(""), GetLastError_To_String(lCode));
};


LONG SafeGetRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,CString & roDataString); //reads single string from registry
LONG SafeSetRegistryKeyString(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,LPCTSTR lpValue);		  //writes single string to registry
LONG SafeGetRegistryKeyDword(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,DWORD & rdwData); //reads single dword from registry
LONG SafeSetRegistryKeyDword(HKEY hKeyClass,LPCTSTR lpSubKey,LPCTSTR lpName,DWORD dwData);		  //writes single dword to registry
LONG SafeGetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, CArray <char, char &> & roArray);
LONG SafeSetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, LPCVOID pValue, long lSize);
LONG SafeDeleteRegistryValue(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName);
LONG SafeDeleteRegistryKey(HKEY hKeyClass, LPCTSTR lpSubKey);

#ifndef _MINI_CORE_
DWORD RecursiveDeleteRegistryKey(HKEY hKeyClass, LPCTSTR lpSubKey);
#endif

LONG EnumRegistryKeys(HKEY hKeyClass, LPCTSTR lpSubKey,CArray<CString,LPCTSTR> & roResultArray);

inline void GetRegistryKeyString(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, CString & roDataString)
{
	long lResult = SafeGetRegistryKeyString(hKeyClass, lpSubKey, lpName, roDataString);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, CString(lpSubKey) + '\\' + lpName);
	};
};

inline void SetRegistryKeyString(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, LPCTSTR lpValue)
{
	long lResult = SafeSetRegistryKeyString(hKeyClass, lpSubKey, lpName, lpValue);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, CString(lpSubKey) + '\\' + lpName);
	};
};

inline void GetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, CArray <char, char &> & roArray)
{
	long lResult = SafeGetRegistryKeyBinary(hKeyClass, lpSubKey, lpName, roArray);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, CString(lpSubKey) + '\\' + lpName);
	};
};

inline void SetRegistryKeyBinary(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName, LPCVOID pValue, long lSize)
{
	long lResult = SafeSetRegistryKeyBinary(hKeyClass, lpSubKey, lpName, pValue, lSize);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, CString(lpSubKey) + '\\' + lpName);
	};
};

inline void DeleteRegistryValue(HKEY hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpName)
{
	long lResult = SafeDeleteRegistryValue(hKeyClass, lpSubKey, lpName);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, CString(lpSubKey) + '\\' + lpName);
	};
};

inline void DeleteRegistryKey(HKEY hKeyClass, LPCTSTR lpSubKey)
{
	long lResult = SafeDeleteRegistryKey(hKeyClass, lpSubKey);
	if (lResult != ERROR_SUCCESS)
	{
		ThrowRegException(lResult, lpSubKey);
	};
};

//-----------CDLLHolder--------------------
//
//³aduje i zwalnia bibliotekê DLL
// 
//-----------------------------------------

class CDLLHolder : public CInterface__
{
public:
	CDLLHolder(LPCTSTR pcDLLName):
		m_oModuleNameString(pcDLLName),
		m_hInstance(::LoadLibrary(pcDLLName))
	{
		if (!m_hInstance)
		{
			DWORD dwErrorCode = ::GetLastError();
			ThrowNavoException2(ERCO_INTERNAL_DLLLOADFAILED, IDPAGE_NOTAVAILABLE,
				pcDLLName, GetLastError_To_String(dwErrorCode));
		};
	};
	~CDLLHolder()
	{
		::FreeLibrary(GetInstance());
	};
	template <class T>
	DWORD SafeGetProcAddress(T & t, LPCSTR pcFunctionName) const
	{
		if ((t = (T)::GetProcAddress(GetInstance(), pcFunctionName)) == (T)NULL)
		{
			return ::GetLastError();
		};
		return ERROR_SUCCESS;
	};
	template <class T>
	void GetProcAddress(T & t, LPCSTR pcFunctionName) const
	{
		if ((t = (T)::GetProcAddress(GetInstance(), pcFunctionName)) == (T)NULL)
		{
			ThrowNavoException2(ERCO_INTERNAL_LOADFUNCTIONFAILED, IDPAGE_NOTAVAILABLE, pcFunctionName, m_oModuleNameString);
		};
	};

private:
	HINSTANCE GetInstance() const
	{
		ASSERT(m_hInstance);
		return m_hInstance;
	};

	CString m_oModuleNameString;
	HINSTANCE m_hInstance;
};

//-----------------------------------------
//rejestruje i wyrejestrowuje
//COM-object zawarty w podanym .DLLu
//-----------------------------------------

HRESULT RegisterDLL(LPCTSTR pcFileName);
HRESULT UnregisterDLL(LPCTSTR pcFileName);

//-----------CRegisterDLLHolder-----------------
//
// holder na rejestracjê
// COM-objectów zawartych w podanym .DLLu
//
//-----------------------------------------

class CRegisterDLLHolder
{
public:
	CRegisterDLLHolder(LPCTSTR pcFileName):
		m_oFileNameString(pcFileName)
	{
		ASSERT(!m_oFileNameString.IsEmpty());

#ifdef _DEBUG
		{
			CFileStatus oFileStatus;
			ASSERT(CFile::GetStatus(m_oFileNameString, oFileStatus));
		}
#endif
		HRESULT hr = ::RegisterDLL(pcFileName);
		if(hr != S_OK)
		{
			ThrowNavoException2(ERCO_INTERNAL_REGISTERMODULEFAILED, IDPAGE_NOTAVAILABLE, pcFileName, SCODE_To_String(hr));
		};
	};
	~CRegisterDLLHolder()
	{
		try
		{
			if(!m_oFileNameString.IsEmpty())	//is detached or not
			{
				HRESULT hr = ::UnregisterDLL(m_oFileNameString);
				if(hr != S_OK)
				{
					ThrowNavoException2(ERCO_INTERNAL_UNREGISTERMODULEFAILED, IDPAGE_NOTAVAILABLE, m_oFileNameString, 
						SCODE_To_String(hr));
				}
			};
		}
		catch(...)
		{
			//TO_DO:
			ASSERT(false);
		};
	};
	void Detach()
	{
		m_oFileNameString.Empty();
	};

private:
	CString m_oFileNameString;
};

class CMemoryMappedFileHolder
{
public:
	CMemoryMappedFileHolder(LPCTSTR lpName,long nSize) :
		m_hFileMapping(NULL),
		m_pBaseAddr(NULL),
		m_bExisted(false),
		m_oEvent(FALSE,FALSE,lpName)
	{
		TCHAR cFMName[ _MAX_PATH ];
		_tcscpy(cFMName,lpName);
		_tcscat(cFMName,_T("_FM"));
		m_hFileMapping = ::CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,nSize,cFMName);
		if(m_hFileMapping == NULL)
		{
			return;
		}
		m_bExisted = (::GetLastError() == ERROR_ALREADY_EXISTS);
		m_pBaseAddr = ::MapViewOfFile(m_hFileMapping,FILE_MAP_WRITE | FILE_MAP_READ,0,0,nSize);
		if(m_pBaseAddr)
		{
			*((TCHAR*)m_pBaseAddr) = '\0';	//initially empty string
		}
	}
	~CMemoryMappedFileHolder()
	{
		if(m_pBaseAddr)
		{
			VERIFY(::UnmapViewOfFile(m_pBaseAddr));
		}
		if(m_hFileMapping != NULL)
		{
			VERIFY(::CloseHandle(m_hFileMapping));
		}
	}
	bool IsOK() const
	{
		return (m_pBaseAddr != NULL) && (m_hFileMapping != NULL);
	}
	bool Existed() const
	{
		return m_bExisted;
	}
	void Signal()
	{
		m_oEvent.SetEvent();
	}
	HANDLE GetEventHandle() const
	{
		return m_oEvent.m_hObject;
	}
	LPVOID GetPtr() const
	{
		return m_pBaseAddr;
	}
private:
	bool m_bExisted;
	HANDLE m_hFileMapping;
	LPVOID m_pBaseAddr;
	CEvent m_oEvent;
};

class CWinVersion
{
public:
	CWinVersion();
	enum WinVersion
	{ 
		Win95,
		Win98,
		WinNT,
		Win2K,
		WinXP
	};
	WinVersion GetVersion() const
	{
		return m_iVersion;
	}
private:
	WinVersion m_iVersion;
};

class CMultipleRunDetector
{
public:
	CMultipleRunDetector():
		m_hHandle(NULL)
	{
	};
	bool Init(LPCTSTR pcMutexName)
	{
		long lCount = 10; // czekamy maksymalnie 10 sekund
		while (lCount)
		{
			m_hHandle = ::CreateMutex(NULL, TRUE, pcMutexName);
			if (!m_hHandle)
			{
				ThrowNavoException2(ERCO_MUTEX_CREATION_FAILED, IDPAGE_NOTAVAILABLE,
					pcMutexName, GetLastError_To_String(::GetLastError()));
			}
			else
			{
				if (::GetLastError() == ERROR_ALREADY_EXISTS)
				{
					Revoke();
					lCount--;
					Sleep(1000);
				}
				else
				{
					return true;
				};
			};
		};
		return false;
	};
	~CMultipleRunDetector()
	{
		Revoke();
	};
	void Revoke()
	{
		if (m_hHandle)
		{
			::CloseHandle(m_hHandle);
			m_hHandle = NULL;
		};
	};

private:
	HANDLE m_hHandle;
};

//-------------------------------------- 
//	"smart" execute process
//--------------------------------------

errorcode ExecuteProcess(
	LPCTSTR pcProcessPath,			//full .exe path
	LPCTSTR pcProcessDirectory,		//working directory
	LPCTSTR pcArguments,			//arguments
	long lShowCommand,				//show command
	long & lExitCode,				//process exit code
	bool bExitAfterLaunch);			//true - don't wait for process completition


bool is_memory_low();				//returns information about memory low state

inline bool duplicate_os_handle(HANDLE hSrcHandle,HANDLE & rhTargetHandle)
{
	return (::DuplicateHandle(::GetCurrentProcess(),hSrcHandle,
		::GetCurrentProcess(),&rhTargetHandle,0,FALSE,DUPLICATE_SAME_ACCESS) != FALSE);
}

#else
	#error __FILE__ already included
#endif
