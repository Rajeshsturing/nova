/*
	NAVO Enterprise 2020
	setup application

	component installer (except NE2002 engine)
*/

#include "stdafx.h"
#include "..\navoinstall\version.h"	// external declarations for this file
#include "coresetupserv.h"
#include "taskparam.h"
#include "componentinstaller.h"
#include "setup.h"

extern CNavoLog _g_oNavoLog;
extern CWindows _g_oWindows;
extern CSetupApp _g_setupApp;


struct CComponentInfo
{
	LPCTSTR m_lpHumanName;
	LPCTSTR m_lpSubDir;
	LPCTSTR m_lpKeyFile;
	LPCTSTR m_lpExecProcessCmd;
	const CLSID	* m_poCLSID;
	LPCTSTR m_lpReqVersion;
};

//ORDER MUST BE SAME AS IN enum eNEComponent !!!

struct __declspec(uuid("00000507-0000-0010-8000-00AA006D2EA4")) IADOCommand26;
extern "C" const GUID __declspec(selectany) CLSID_VBSCRIPT =
{ 0xb54f3741,0x5b07,0x11cf,{0xa4,0xb0,0x0,0xaa,0x0,0x4a,0x55,0xe8} };
extern "C" const GUID __declspec(selectany) CLSID_SAXXMLReader =
{ 0x079aa557,0x4a18,0x424a,{0x8e,0xee,0xe3,0x9f,0x0a,0x8d,0x41,0xb9} };

static CComponentInfo _g_component_info[] =
{
	{ "Distributed COM",				"components\\dcom98",	"dcom98.exe"	  ,"/q"	,&__uuidof(NULL)			,NULL				},
	{ "Windows Installer",				"components\\msinst",	NULL			  ,"/q"	,&__uuidof(NULL)			,NULL				},
	{ "Visual Basic 5.6",				"components\\vbs55",	"scr56pl98.exe"	  ,"/q"	,&CLSID_VBSCRIPT			,_T("5.6.0.8515")	},	//5.6 
	{ "Microsoft Data Access",			"components\\mdac",		"mdac_typ_po.exe" ,"/Q"	,&__uuidof(IADOCommand26)	,_T("2.60.6526.0")	},
	{ "Microsoft .NET Framework 1.1",	"components\\dotnet",	"msdotnet1_1pl.exe","/q"  , &__uuidof(NULL)			,NULL				},
	{ "Platforma "
		"NAVO Enterprise 2020",	"components\\navo2012",	"navo2012.exe"	  ,""	,&__uuidof(NULL)			,NULL				}
};

LPCTSTR CComponentInstaller::_human_name() const
{
	return _g_component_info[m_eComponentType].m_lpHumanName;
}

LPCTSTR CComponentInstaller::_key_file_name() const
{
	return _g_component_info[m_eComponentType].m_lpKeyFile;
}

LPCTSTR CComponentInstaller::_subdir_name() const
{
	return _g_component_info[m_eComponentType].m_lpSubDir;
}

const CLSID * CComponentInstaller::_checked_clsid() const
{
	return _g_component_info[m_eComponentType].m_poCLSID;
}

LPCTSTR CComponentInstaller::_required_version() const
{
	return _g_component_info[m_eComponentType].m_lpReqVersion;
}

setuperror CComponentInstaller::_install()
{
	_g_oNavoLog << "installing " + CString(_human_name());

	CString oPathString;
	setuperror eErco = _g_oWindows._provide_source_file_path(oPathString, _subdir_name(), _key_file_name(), _human_name());

	if (eErco != stpe_ok)
	{
		return eErco;
	}

	long nExitCode = 0;

	errorcode eErrorCode = ExecuteProcess(oPathString, ".\\",
		_g_component_info[m_eComponentType].m_lpExecProcessCmd, SW_SHOW, nExitCode, false);

	if (eErrorCode == ERCO_UNABLE_TO_OPEN_FILE)
	{
		_g_oNavoLog << ("unable to open file " + oPathString);
		return stpe_unable_2_open_file;
	}
	if (eErrorCode == ERCO_OK)
	{
		_g_oNavoLog << ("installed " + CString(_human_name()));
		return stpe_ok;
	}
	else
	{
		_g_oNavoLog << ("installed " + CString(_human_name()) + ", RESTART required");
		return stpe_restart_required;
	}
}

setuperror CComponentInstaller::_uninstall()
{
	//not supported yet
	return stpe_ok;
}

bool CComponentInstaller::_need_install()
{
	ASSERT(_checked_clsid());
	ASSERT(_required_version());

	_g_oNavoLog << ("checking " + CString(_human_name()));
	setuperror eErco = _g_oWindows.CheckCOMObject(*_checked_clsid(), stpe_comobj_check_fail);
	_g_oNavoLog << (CString(_human_name()) + " checked, result is: " + Long2String(long(eErco)));

	if (eErco != stpe_ok)
	{
		return true;
	}
	else	//check version
	{
		CString oCOMInprocString;
		eErco = _g_oWindows.GetInprocServer(*_checked_clsid(), oCOMInprocString);

		if (eErco == stpe_not_enough_rights)
		{
			_g_oNavoLog << "current user has not enough rights for checks";
			return true;

			//if(!_g_oWindows._logon_as_admin())
			//{
			//	_g_oNavoLog << "current user has not enough rights for checks";
			//	return true;
			//}
		}

		if (eErco != stpe_ok)
		{
			return true;
		}
		else
		{
			CVersion oVersion;
			if (!oVersion.Load(oCOMInprocString))
			{
				return true;
			}
			else
			{
				CString oLogString = "module " + oCOMInprocString + " has version " +
					oVersion.GetFileVersion() + " and therefore will be ";

				bool bNeedInstall = (oVersion.GetFileVersion() < _required_version());
				if (bNeedInstall)
				{
					oLogString += "INSTALLED";
				}
				else
				{
					oLogString += "not installed";
				}
				_g_oNavoLog << oLogString;
				return bNeedInstall;
			}
		}
	}
}

///-------- DCOM installer			----------------
const long _NAVO_COINIT_MULTITHREADED = 0x0;

bool CDCOMInstaller::_need_install()
{
	_g_oNavoLog << ("checking " + CString(_human_name()));

	CDLLHolder oDLLHolder("OLE32.DLL");
	HRESULT(STDAPICALLTYPE * pCoInitializeEx)(LPVOID, DWORD) = NULL;

	if (oDLLHolder.SafeGetProcAddress(pCoInitializeEx, "CoInitializeEx") != ERROR_SUCCESS)
	{
		_g_oNavoLog << ("dcom not installed at all");
		return true;
	}

	HRESULT hResult = pCoInitializeEx(NULL, _NAVO_COINIT_MULTITHREADED);
	if (hResult != S_OK && hResult != S_FALSE)
	{
		_g_oNavoLog << ("dcom installed but is not working properly");
		return true;
	}
	::CoUninitialize();

	CString oString;
	LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\OLE", "EnableDCOM", oString);

	while (lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "current user has not enough rights for checks";
		return true;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "current user has not enough rights for checks";
		//	return true;
		//}

		//lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\OLE", "EnableDCOM",oString);
	}

	if (!(lResult == ERROR_FILE_NOT_FOUND || lResult != ERROR_SUCCESS))
	{
		if (!(oString.IsEmpty() || (oString[0] != 'y' && oString[0] != 'Y')))
		{
			_g_oNavoLog << ("DCOM is OK");
			return false;
		}
		else
		{
			_g_oNavoLog << ("DCOM is turned OFF");
			return true;
		}
	}
	else
	{
		_g_oNavoLog << ("incomplete DCOM installation");
		return true;
	}
}

///-------- Windows Installer installer			----------------
const TCHAR * _g_pchMSInstKeyFile9x = "InstMsi9x.exe";
const TCHAR * _g_pchMSInstKeyFileNT = "InstMsint.exe";

LPCTSTR CWinInstInstaller::_key_file_name() const
{
	return (_g_oWindows._get_version() == CWinVersion::Win98) ?
		_g_pchMSInstKeyFile9x : _g_pchMSInstKeyFileNT;
}

class Installer : public COleDispatchDriver
{
public:
	Installer() {}		// Calls COleDispatchDriver default constructor
	Installer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Installer(const Installer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	CString GetVersion();
};

CString Installer::GetVersion()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


bool CWinInstInstaller::_need_install()
{
	_g_oNavoLog << ("checking " + CString(_human_name()));
	setuperror eErco = _g_oWindows.CheckCOMObject(_T("WindowsInstaller.Installer"), stpe_comobj_check_fail);
	_g_oNavoLog << (CString(_human_name()) + " checked, result is: " + Long2String(long(eErco)));
	if (eErco != stpe_ok)
	{
		return true;
	}

	ALL_TRY
	{

		CSimpleOleInitHolder oSimpleOleInitHolder;
		CLSID oCLSID;
		HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr("WindowsInstaller.Installer"),&oCLSID);
		ASSERT(hr == S_OK);
		SCP<IUnknown> poWinInstSP;
		poWinInstSP.CreateInstance(oCLSID,CLSCTX_ALL);
		SCP<IDispatch> poWinInstDispSP;
		poWinInstDispSP.QueryInterface(poWinInstSP);
		Installer oInstaller(poWinInstDispSP.Detach());
		_g_oNavoLog << ("found Windows Installer version " + oInstaller.GetVersion());
		if (oInstaller.GetVersion() > "1.0999999")	//means 1.1 is OK
		{
			return false;
		}
		return true;	//means need install
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		_g_oNavoLog << ("check threw exception " + roNavoException.BuildCompleteErrorString());
		return true;
	}
	return false;
}

//---------------------- CVBSInstaller-------------------------
LPCTSTR CVBSInstaller::_key_file_name() const
{
	if (_g_oWindows._get_version() <= CWinVersion::Win98)
	{
		return _T("scr56pl98.exe");
	}
	else
	{
		return _T("scr56plnt.exe");
	}
}

//---------------------- CDotNetInstaller-------------------------
bool CDotNetInstaller::_need_install()
{
	return false;
	HKEY hKey;
	LONG lResult = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\.NETFramework\\v4.5", 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		return true;
	}
	
	::RegCloseKey(hKey);
	return false;
}

LPCTSTR CDotNetInstaller::_key_file_name() const
{
	return _T("msdotnet1_1pl.exe");
}



