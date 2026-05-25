/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
	CSystemAutoObject
		obiekt udostêpnia funkcje OS
*/

#include "stdafx.h"
#include <mmsystem.h>
#include "..\include\h1000.h"
#include "SystemAutoObject.h"
#include "specialfolders.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "winmm.lib")

static long CSIDL_from_NSF(eNAVOSpecFolder eNSF)
{
	switch(eNSF)
	{
	case nsf_desktop:
		return CSIDL_DESKTOP;
	case nsf_mydocuments:
		return CSIDL_PERSONAL;
	case nsf_favorites:
		return CSIDL_FAVORITES;
	default:
		ASSERT(false);
		return -1;
	}
}

CString _get_special_folder_path(eNAVOSpecFolder eNSF)
{
	long nIdFolder = CSIDL_from_NSF(eNSF);
	if(nIdFolder == -1)
	{
		return "";
	}
	SCP<IMalloc> poShellMallocSP;
	VERIFY(::SHGetMalloc(&poShellMallocSP.GetRawPointer()) == S_OK);
	ASSERT(poShellMallocSP.PointsObject());
	LPITEMIDLIST pIDL = NULL;
	HRESULT hr = ::SHGetSpecialFolderLocation(::GetActiveWindow(),nIdFolder,&pIDL);
	TCHAR cPath[ MAX_PATH + 1 ];
	cPath[0] = '\0';
	if(hr == S_OK)
	{
		VERIFY(::SHGetPathFromIDList(pIDL,cPath));
		poShellMallocSP->Free(pIDL);
	}
	return CString(cPath);
}

CSystemAutoObject::CSystemAutoObject()
{
	EnableAutomation();
	AfxOleLockApp();
}

CSystemAutoObject::~CSystemAutoObject()
{
	AfxOleUnlockApp();
}



BEGIN_MESSAGE_MAP(CSystemAutoObject, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CSystemAutoObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSystemAutoObject, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CSystemAutoObject)
	DISP_FUNCTION(CSystemAutoObject, "windir", GetWindowsDirectoryAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CSystemAutoObject, "sysdir", GetSystemDirectoryAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CSystemAutoObject, "getregistrykeys", GetRegistryKeysAUTO, VT_BSTR, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "createtempstream", CreateTempStreamAUTO, VT_VARIANT, VTS_NONE)
	DISP_FUNCTION(CSystemAutoObject, "registerdll", RegisterDLL, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "unregisterdll", UnregisterDLL, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "execute", ExecuteProcessAUTO, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL)
	DISP_FUNCTION(CSystemAutoObject, "utf8", StringToUTF8, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "delregistrykey", DeleteRegistryKeyAUTO, VT_EMPTY, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "osid", GetOSIdAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CSystemAutoObject, "specialfolder", GetSpecialFolderAUTO, VT_BSTR, VTS_I4)
	DISP_FUNCTION(CSystemAutoObject, "createtempfilename", CreateTempfileNameAUTO, VT_BSTR, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "shellopen", ShellOpenAUTO, VT_BOOL, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "shellprint", ShellPrintAUTO, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CSystemAutoObject, "sleep", SleepAUTO, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CSystemAutoObject, "setfilemtime", SetFileModifiedTimeAUTO, VT_BOOL, VTS_BSTR VTS_DATE)
	DISP_FUNCTION(CSystemAutoObject, "sound", PlaySoundAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CSystemAutoObject, "activex", 700,CreateObjectAUTO, VT_DISPATCH, VTS_BSTR)
	DISP_PROPERTY_PARAM(CSystemAutoObject, "registry", GetRegistryAUTO, SetRegistryAUTO, VT_BSTR, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_PROPERTY_PARAM(CSystemAutoObject, "privateprofile", GetPrivateProfileAUTO, SetPrivateProfileAUTO, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISystemAutoObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

static const IID IID_ISystemAutoObject =
{ 0xf2e76961, 0x8494, 0x40d4, { 0xa2, 0xfc, 0xf7, 0x6f, 0xcc, 0x79, 0xb5, 0xd7 } };

IMPLEMENT_DYNCREATE(CSystemAutoObject, CCmdTargetInterface)

// {188cb15d-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CSystemAutoObject, "navocomutil.system",0x188cb15d,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(CSystemAutoObject, CCmdTargetInterface)
	INTERFACE_PART(CSystemAutoObject, IID_ISystemAutoObject, Dispatch)
END_INTERFACE_MAP()

static HKEY NAVOLong2HKEY(long navolong)
{
	switch(navolong)
	{
	case hKey_ClassesRoot :
		return HKEY_CLASSES_ROOT;
	case hKey_CurrentUser :
		return HKEY_USERS;
	case hKey_LocalMachine:
		return HKEY_LOCAL_MACHINE;
	case hKey_Users:
		return HKEY_CURRENT_USER;
	default:
		ASSERT(false);
		//to_do: throw
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CSystemAutoObject message handlers

BSTR CSystemAutoObject::GetRegistryAUTO(long hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpValueName) 
{
	ALL_TRY
	{
		CString oValueString;
		long lResult = SafeGetRegistryKeyString(NAVOLong2HKEY(hKeyClass), lpSubKey, lpValueName, oValueString);
		if (lResult != ERROR_SUCCESS)
		{
			oValueString = "";
		}
		return oValueString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CSystemAutoObject::SetRegistryAUTO(long hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		SetRegistryKeyString(NAVOLong2HKEY(hKeyClass), lpSubKey, lpValueName, lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CSystemAutoObject::GetWindowsDirectoryAUTO() 
{
	ALL_TRY
	{
		CString strResult;
		::GetWindowsDirectory(strResult.GetBuffer(_MAX_PATH),_MAX_PATH);
		strResult.ReleaseBuffer();
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CSystemAutoObject::GetSystemDirectoryAUTO() 
{
	ALL_TRY
	{
		CString strResult;
		::GetSystemDirectory(strResult.GetBuffer(_MAX_PATH),_MAX_PATH);
		strResult.ReleaseBuffer();
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CSystemAutoObject::GetPrivateProfileAUTO(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpIniFile) 
{
	ALL_TRY
	{
		CString strResult;
		::GetPrivateProfileString(lpSection,lpKey,"",strResult.GetBuffer(2048),2048,lpIniFile);
		strResult.ReleaseBuffer();
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CSystemAutoObject::SetPrivateProfileAUTO(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpIniFile, LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		::WritePrivateProfileString(lpSection,lpKey,lpszNewValue,lpIniFile);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CSystemAutoObject::GetRegistryKeysAUTO(long hKeyClass, LPCTSTR lpSubKey) 
{
	CString strResult;
	CArray<CString,LPCTSTR> oKeyArray;
	EnumRegistryKeys(NAVOLong2HKEY(hKeyClass),lpSubKey,oKeyArray);
	for(long iter = 0; iter <= oKeyArray.GetUpperBound(); iter++)
	{
		strResult += oKeyArray[iter] + '\t';
	}
	return strResult.AllocSysString();
}

VARIANT CSystemAutoObject::CreateTempStreamAUTO() 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(CreateTempFileStream());
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CSystemAutoObject::RegisterDLL(LPCTSTR lpFilePath) 
{
	ALL_TRY
	{
		return (long)::RegisterDLL(lpFilePath);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CSystemAutoObject::UnregisterDLL(LPCTSTR lpFilePath) 
{
	ALL_TRY
	{
		return (long)::UnregisterDLL(lpFilePath);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CSystemAutoObject::ShellOpenAUTO(LPCTSTR pcFile, LPCTSTR pcWorkDir, LPCTSTR pcParams)
{
	ALL_TRY
	{
		if ((int)::ShellExecute(NULL, "open", pcFile, pcParams, pcWorkDir, SW_SHOWNORMAL)<=32)
		{
			return FALSE;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
		return FALSE;
	}

	return TRUE;
} 
BOOL CSystemAutoObject::ShellPrintAUTO(LPCTSTR pcFile)
{
	ALL_TRY
	{
		if ((int)::ShellExecute(NULL, "print", pcFile, NULL, NULL, SW_SHOWNORMAL)<=32)
		{
			return FALSE;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
		return FALSE;
	}

	return TRUE;
} 

long CSystemAutoObject::ExecuteProcessAUTO(LPCTSTR pcProcessPath, LPCTSTR pcWorkDir, LPCTSTR pcArguments, BOOL bShow, BOOL bWait) 
{
	ALL_TRY
	{
		long nExitCode = 0;
		errorcode eErco = ExecuteProcess(pcProcessPath,pcWorkDir,pcArguments,
			bShow ? SW_SHOW : SW_HIDE,nExitCode,bWait ? false : true);
		if(eErco == ERCO_OK)
		{
			return nExitCode;
		}
		else
		{
			return (long)eErco;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}


	return 0;
}

BSTR CSystemAutoObject::StringToUTF8(LPCTSTR lpString) 
{
	CString strResult;
	::StringToUTF8(lpString,strResult);
	return strResult.AllocSysString();
}

void CSystemAutoObject::DeleteRegistryKeyAUTO(long hKeyClass, LPCTSTR lpSubKey) 
{
	ALL_TRY
	{
		RecursiveDeleteRegistryKey(NAVOLong2HKEY(hKeyClass), lpSubKey);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CSystemAutoObject::GetOSIdAUTO()
{
	ALL_TRY
	{
		CWinVersion osVersion;
		return osVersion.GetVersion();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CSystemAutoObject::GetSpecialFolderAUTO(long nType) 
{
	ALL_TRY
	{
		return _get_special_folder_path(eNAVOSpecFolder(nType)).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CSystemAutoObject::CreateTempfileNameAUTO(LPCTSTR pcPrefix, LPCTSTR pcExtension) 
{
	ALL_TRY
	{
		return GenerateUniqueFileName(pcPrefix,pcExtension).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CSystemAutoObject::SleepAUTO(long lTime) 
{
	::Sleep(DWORD(lTime));
}

BOOL CSystemAutoObject::SetFileModifiedTimeAUTO(LPCTSTR lpFile, DATE nNewDate) 
{
	ALL_TRY
	{
		CFileStatus oFileStatus;
		CFile::GetStatus(lpFile,oFileStatus);
		COleDateTime oNewODT(nNewDate);
		if(GetNullDateSOV() != CSmartOleVariant(oNewODT))
		{
			SYSTEMTIME oSysTime;
			VERIFY(oNewODT.GetAsSystemTime(oSysTime));
			oFileStatus.m_mtime = CTime(oSysTime);
		}
		else
		{
			oFileStatus.m_mtime = CTime::GetCurrentTime();
		}
		CFile::SetStatus(lpFile,oFileStatus);
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CSystemAutoObject::PlaySoundAUTO(LPCTSTR lpFile) 
{
	ALL_TRY
	{
		::PlaySound(lpFile,NULL,SND_FILENAME|SND_ASYNC);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CSystemAutoObject::CreateObjectAUTO(LPCTSTR lpProgId)
{
	ALL_TRY
	{
		CLSID oCLSID;
		HRESULT hr = ::CLSIDFromProgID(CBStr(lpProgId),&oCLSID);
		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
		}
		SCP<IDispatch> poDispatchSP;
		poDispatchSP.CreateInstance(oCLSID,CLSCTX_ALL);
		return poDispatchSP.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
