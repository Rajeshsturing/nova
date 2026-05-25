/*
	NAVO 2002 Project (2002)

	SETUP application

	System core ?setup? services
*/


#ifndef _CORE_NESETUP_SERVICES_H_
#define _CORE_NESETUP_SERVICES_H_
enum eNEComponent;


class CWindows
{
public:
	CWindows();
	~CWindows();
	void _init_zero();
	bool _init();

	const CString & _get_dir() const
	{
		return m_oWinDirString;
	}
	const CString & _get_system32_dir() const
	{
		return m_oWinSys32DirString;
	}
	const CString & _get_drive()
	{
		return m_oWinDriveString;
	}
	const CString & _get_program_files_dir() const
	{
		return m_oProgramFilesDirString;
	}

	CWinVersion::WinVersion _get_version() const
	{
		return m_oWinVersion.GetVersion();
	}

	bool _logon_as_admin();
	bool _check();
	bool _test_need_install(eNEComponent eNEC);
	bool is_valid_location (const CString & roPath);
	bool _shutdown();

	CString FindFirstCDROMDrive ();

	setuperror _install_component(eNEComponent eNEC);
	setuperror _provide_source_file_path(CString & roString,LPCTSTR lpSubDir,LPCTSTR lpKeyFile,LPCTSTR lpComponentHumanName);
	setuperror CheckCOMObject(const CLSID & rCLSID,setuperror CodeOnFail);
	setuperror CheckCOMObject(LPCTSTR lpProgId,setuperror CodeOnFail);
	setuperror GetInprocServer(const CLSID & roCLSID,CString & roString);
	setuperror GetInprocServer(LPCTSTR lpProgId,CString & roString);
	setuperror GetLocalServer(const CLSID & roCLSID,CString & roString);
	setuperror GetLocalServer(LPCTSTR lpProgId,CString & roString);
	setuperror RegComponent(bool bUIAllowed,LPCTSTR lpPathName);
	setuperror UnregComponent(bool bUIAllowed,LPCTSTR lpPathName);
	setuperror RegDotNetComponent(bool bUIAllowed,LPCTSTR lpNXManToolPath,LPCTSTR lpPathName);

	HPALETTE CreateDIBPalette (LPBITMAPINFO lpbmi, LPINT lpiNumColors);
	HBITMAP LoadResourceBitmap(HINSTANCE hInstance, LPCTSTR lpString, HPALETTE FAR* lphPalette);

private:
	//valid after init
	CString	 m_oWinDirString;
	CString	 m_oWinDriveString;
	CString  m_oWinSys32DirString;
	CString	 m_oProgramFilesDirString;
	CWinVersion m_oWinVersion;
	
	CMapStringToString m_oDownloadedFilesMap;
};

class CSimpleOleInitHolder
{
public:
	CSimpleOleInitHolder()
	{
		HRESULT hResult = ::OleInitialize(NULL);
		m_bShouldFree = (hResult == S_OK || hResult == S_FALSE);
	}
	~CSimpleOleInitHolder()
	{
		if(m_bShouldFree)
		{
			::OleUninitialize();
		}
	}
private:
	bool m_bShouldFree;
};

//setuperror CheckCOMObject(const CLSID & rCLSID,setuperror CodeOnFail);
//setuperror CheckCOMObject(LPCTSTR lpProgId,setuperror CodeOnFail);
//setuperror GetLocalServer(LPCTSTR lpProgId,CString & roString);
//setuperror GetLocalServer(const CLSID & roCLSID,CString & roString);
//setuperror GetInprocServer(LPCTSTR lpProgId,CString & roString);
//setuperror GetInprocServer(const CLSID & roCLSID,CString & roString);

inline CString StringFromCLSID(const CLSID & rCLSID)
{
	CString AFXAPI AfxStringFromCLSID(REFCLSID rclsid); //from MFC
	return AfxStringFromCLSID(rCLSID);
}

DWORD NAVOSetupFileEx(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse);

class CVirtualNTServiceManager
{
public:
	CVirtualNTServiceManager(LPCTSTR lpServiceName) :
	  m_oServiceNameString(lpServiceName)
	{
	}
	setuperror start();
	setuperror stop();
	setuperror is_running(bool & bRunning);
private:
	CString m_oServiceNameString;
};

#else
	#error __FILE__ already included
#endif



