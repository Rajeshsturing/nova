/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Quick system check functions
*/

#include "StdAfx.h"
#include "..\navopx\navopx.h"
#include "..\precursor\commonproc.h"


const long _NAVO_COINIT_MULTITHREADED      = 0x0;

errorcode CheckDCOM()
{
	CDLLHolder oDLLHolder("OLE32.DLL");
	HRESULT (STDAPICALLTYPE * pCoInitializeEx)(LPVOID,DWORD) = NULL;
	if(oDLLHolder.SafeGetProcAddress(pCoInitializeEx,"CoInitializeEx") != ERROR_SUCCESS)
	{
		return ERCO_SYSCHK_DCOM_NOT_INSTALLED;
	}

	HRESULT hResult = pCoInitializeEx(NULL,_NAVO_COINIT_MULTITHREADED);
	if(hResult != S_OK && hResult != S_FALSE)
	{
		return ERCO_SYSCHK_DCOM_NOT_WORKING;
	}
	::CoUninitialize();

	CString oString;
	LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\OLE", "EnableDCOM",oString);
	if(lResult == ERROR_ACCESS_DENIED)
	{
		return ERCO_NOT_ENOUGH_RIGHTS;
	}
	if(!(lResult == ERROR_FILE_NOT_FOUND || lResult != ERROR_SUCCESS))
	{
		if(!(oString.IsEmpty() || (oString[0] != 'y' && oString[0] != 'Y')))
		{
			return ERCO_OK;
		}
		else
		{
			return ERCO_SYSCHK_DCOM_NOT_TURNED_ON;
		}
	}
	else
	{
		return ERCO_SYSCHK_DCOM_NOT_INSTALLED;
	}
}

errorcode QuickCheckSystem(long nLevel)
{
	errorcode eErco = CheckDCOM();
	if(eErco != ERCO_OK)
	{
		return eErco;
	}
	
	//w tym miejscu powinno dzia³aæ ju¿ OLE/DCOM

	CSimpleOleInitHolder oSimpleOleInitHolder;
	eErco = CheckCOMObject(CLSID_VBSCRIPT,ERCO_SYSCHK_VBSCRIPT_CR_FAILED);
	if(eErco != ERCO_OK)
	{
		return eErco;
	}
	eErco = CheckCOMObject("navocomutil.system",ERCO_SYSCHK_ENGINE_PART_NOT_INV);
	if(eErco != ERCO_OK)
	{
		return eErco;
	}
	if(nLevel != 1)
	{
		return eErco;
	}
	///LEVEL 1 checks
	///
	///

	if(nLevel != 2)
	{
		return eErco;
	}
	
	//LEVEL 2 checks
	//
	//
	
	return eErco;
}

errorcode CheckCOMObject(const CLSID & rCLSID,errorcode CodeOnFail)
{
	ALL_TRY
	{
		CSimpleOleInitHolder oSimpleOleInitHolder;
		SCP<IUnknown> poTestSP;
		poTestSP.CreateInstance(rCLSID,CLSCTX_ALL);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		return CodeOnFail;
	}
	return ERCO_OK;
}

errorcode CheckCOMObject(LPCTSTR lpProgId,errorcode CodeOnFail)
{
	CLSID oCLSID;
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(lpProgId),&oCLSID);
	if(hr != S_OK)
	{
		return CodeOnFail;
	}
	return CheckCOMObject(oCLSID,CodeOnFail);
}

/*
	return disk free space in MB rounded down
*/
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
