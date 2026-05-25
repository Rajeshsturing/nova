/*
	NAVO Enterprise 2020
	setup application

	NE2002 engine installer
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navoinstall\version.h"	// external declarations for this file
#include "..\include\progressgadget.h"
#include "coresetupserv.h"
#include "taskparam.h"
#include "componentinstaller.h"
#include "browsedlg.h"

const TCHAR * _g_pchNAVO2001Root				= "NAVO Enterprise 2002\\";
const TCHAR * _g_pchNAVO2001Engine				= "System\\";
const TCHAR * _g_pchNAVO2001Applications		= "Applications\\";
const TCHAR * _g_pchNAVO2001Temporary			= "TempFiles\\";
const TCHAR * _g_pchNAVO2001Archive				= "Archive\\";
const TCHAR * _g_pchNAVO2001Database			= "Database\\";

const TCHAR * _g_pchEngineUninstall = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\NAVO Enterprise 2020");
const TCHAR * _g_pchEngineComponentHuman = _T("Sk³adnik Platformy NAVO Enterprise 2020");

extern const TCHAR const * pcWWWRoot;
extern CTaskParam _g_oTaskParam;
extern CNavoLog _g_oNavoLog;
extern CWindows _g_oWindows;

enum eDestType
{
	dest_winsys32,			//windows\system32
	dest_navo2008,			//navo enterprise system dir
	dest_navoroot,			//navo enterprsie root dir
};


const long REGMET_DLL = 1;		//register with REGSVR32
const long REGMET_EXE = 2;		//register launching target .EXE
const long REGMET_NO  = 3;		//no registration
const long REGMET_DOTNET = 4;	//register with NXManTool2008

#if defined(NAVO2008)
CFileInfo _g_cEngineFiles [] =
{	
	{ dest_navo2008, "Interop.ADODB.dll","2.8.0.0", REGMET_DOTNET, "", false, false},
	//---------------------------
	//NX.NET dlls
	//{ dest_navo2001, "Interop.NE2002Iface.dll","0.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.navoafc.dll","1.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.VBA.dll","6.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.Scripting.dll","1.0.0.0", REGMET_NO, "", false, false},
	//---------------------------
	{ dest_navo2008, "navo2012.net.core.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.glue.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.raport.builder.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.ui.builder.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.appdb.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.raport.engine.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.business.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.devices.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2008, "navo2012.net.hub.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	//---------------------------
	{ dest_navo2008, "navo2012.net.manager.exe",GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	//---------------------------
#ifdef _INSTALL_DEBUG_ENGINE
    { dest_navo2008, "mfc90d.dll",	"9.0.21022.8", REGMET_NO, "", false, false},
	{ dest_navo2008, "msvcr90d.dll",	"9.0.21022.8", REGMET_NO, "", false, false},
#else
//	{ dest_navo2008, "mfc90.dll",	"9.0.21022.8", REGMET_NO, "", false, false},
//	{ dest_navo2008, "msvcr90.dll",	"9.0.21022.8", REGMET_NO, "", false, false},
#endif

	{ dest_winsys32, "msvbvm60.dll","6.0.89.64" , REGMET_NO, "", false, false},
	{ dest_navo2008, "navoafc.dll",	    "1.2.0.1050", REGMET_DLL, "", false, false },

	{ dest_navo2008, "gdiplus.dll",		"5.1.3097.0", REGMET_NO,  "", false, false},
	{ dest_navo2008, "navo2012.proxy.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.core.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.comutils.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.definitions.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.objects.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.preprocessor.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.scripting.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.ui.engine.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.ui.parser.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.exportimport.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.gal.dll",		GetNAVO2001EngineVersion(), REGMET_NO,  "", false, false},
	{ dest_navo2008, "navo2012.server.gm.dll",	GetNAVO2001EngineVersion(), REGMET_NO,  "", false, false},
	{ dest_navo2008, "navo2012.backrest.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.brctrl.ocx",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.internet.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.peripherials.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.pagemanager.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.cache.exe",	GetNAVO2001EngineVersion(), REGMET_EXE, "/regserver /root \"%sFileCache\"", false, false},
	{ dest_navo2008, "navo2012.exe",	GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
//	{ dest_navo2008, "navoservice2008.exe",	GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	{ dest_navo2008, "navo2012.setup.exe",		GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	{ dest_navo2008, "splash.jpg",		NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "navologo.gif",	NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "desktop.ini",		NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "folder.htt",		NULL, REGMET_NO, "", false, false},


	//server ?
	{ dest_navo2008, "navo2012.appdb.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, "navo2012.server.exe",	GetNAVO2001EngineVersion(), REGMET_EXE, "/regserver", false, false},
	{ dest_navo2008, "navo2012.database.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2008, NULL, NULL, 0, NULL, false, false},
};

#else
CFileInfo _g_cEngineFiles [] =
{
	//system MFC
#ifdef _NAVODOTNET
	{ dest_navo2001, "mfc71.dll",	"7.10.3077.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "msvcp71.dll",	"7.10.3077.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "msvcr71.dll",	"7.10.3052.4", REGMET_NO, "", false, false},
	{ dest_navo2001, "msvcrt.dll",	"7.0.2600.1106", REGMET_NO, "", false, false},
	
	{ dest_navo2001, "adodb.dll","7.10.3077.0", REGMET_DOTNET, "", false, false},
	//---------------------------
	//NX.NET dlls
	//{ dest_navo2001, "Interop.NE2002Iface.dll","0.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.navoafc.dll","1.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.VBA.dll","6.0.0.0", REGMET_NO, "", false, false},
	//{ dest_navo2001, "Interop.Scripting.dll","1.0.0.0", REGMET_NO, "", false, false},
	//---------------------------
	{ dest_navo2001, "nxappcore.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nx2ne2002.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxraport.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxuibuilder.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxapprepos.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxrapexec.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxbusiness.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxdevices.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	{ dest_navo2001, "nxhub.dll",GetNAVO2001EngineVersion(), REGMET_DOTNET, "", false, false},
	//---------------------------
	{ dest_navo2001, "nxmantool.exe",GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	//---------------------------
#else
#ifdef _INSTALL_DEBUG_ENGINE
	{ dest_navo2001, "msvcrtd.dll",	"6.0.8797.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "msvcirtd.dll","6.0.8168.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "mfc42d.dll",	"6.0.8665.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "mfco42d.dll",	"6.0.8665.0", REGMET_NO, "", false, false},
#else
	{ dest_navo2001, "msvcrt.dll",	"6.1.8637.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "msvcirt.dll",	"6.1.8637.0", REGMET_NO, "", false, false},
	{ dest_navo2001, "mfc42.dll",	"6.0.8665.0", REGMET_NO, "", false, false},
#endif
#endif
	{ dest_winsys32, "msvbvm60.dll","6.0.89.64" , REGMET_NO, "", false, false},

	{ dest_navo2001, "gdiplus.dll",		"5.1.3097.0", REGMET_NO,  "", false, false},
	{ dest_navo2001, "navopx.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navocore.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navocomutil.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navodef.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoobj.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoprep.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoscript.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoui.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoprsr.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoinstall.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoexpimp.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navogal.dll",		GetNAVO2001EngineVersion(), REGMET_NO,  "", false, false},
	{ dest_navo2001, "navobrman.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navobrmctrl.ocx",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navodocman.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoinet.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoperif.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoafc.dll",	    "1.2.0.1048", REGMET_DLL, "", false, false},
	{ dest_navo2001, "navocache.exe",	GetNAVO2001EngineVersion(), REGMET_EXE, "/regserver /root \"%sFileCache\"", false, false},
	{ dest_navo2001, "navo2002.exe",	GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	{ dest_navo2001, "setup.exe",		GetNAVO2001EngineVersion(), REGMET_NO, "", false, false},
	{ dest_navo2001, "splash.jpg",		NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "navologo.gif",	NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "desktop.ini",		NULL, REGMET_NO, "", false, false},
	{ dest_navoroot, "folder.htt",		NULL, REGMET_NO, "", false, false},


	//server ?
	{ dest_navo2001, "navoappdb.dll",	GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, "navoserver.exe",	GetNAVO2001EngineVersion(), REGMET_EXE, "/regserver", false, false},
	{ dest_navo2001, "navodb.dll",		GetNAVO2001EngineVersion(), REGMET_DLL, "", false, false},
	{ dest_navo2001, NULL, NULL, 0, NULL, false, false},
};
#endif

bool CNE2002Installer::_need_install()
{
	bool bInstallNAVO2001 = false;
	_g_oNavoLog << "checking " + CString( _human_name());

	long iter = 0;

	while( _g_cEngineFiles[iter].m_poName != NULL)
	{
		CFileInfo & roFileInfo = _g_cEngineFiles[iter];
		roFileInfo.m_bCopy = false;

		_g_oNavoLog << ("checking engine file: " + CString(roFileInfo.m_poName));
		CString oFileDestString;

		switch( _g_cEngineFiles[iter].m_eDT)
		{
			case dest_winsys32:
			{
				oFileDestString = _g_oWindows._get_system32_dir() + roFileInfo.m_poName;
			}	
			break;

			case dest_navo2008:
			{
				oFileDestString = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Engine + roFileInfo.m_poName;
			}	
			break;

			case dest_navoroot:
			{
				oFileDestString = _g_oTaskParam._get_root_dest() + roFileInfo.m_poName;
			}	
			break;	

			default:
			{
				ASSERT(false);
			}
		}

		_g_oNavoLog << ("compare is performed against:" + oFileDestString);

		if( !IsVersionValid( oFileDestString, roFileInfo.m_poVersion))
		{
			bInstallNAVO2001 = true;
			roFileInfo.m_bCopy = true;
		}

	

		if(roFileInfo.m_bCopy)
		{
			_g_oNavoLog << ("engine file: " + CString(roFileInfo.m_poName) + " will be copied");
		}
		else
		{
			_g_oNavoLog << ("engine file: " + CString(roFileInfo.m_poName) + " is OK");
		}

		iter++;
	}

	CString oInstallRootString;
	LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot", oInstallRootString);

	while (lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not clear pending flag";
		return stpe_not_enough_rights;
		
		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not clear pending flag";
		//	return stpe_not_enough_rights;
		//}

		//lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "RegPending","N");
	}

	if( oInstallRootString != _g_oTaskParam._get_root_dest())
	{
		bInstallNAVO2001 = true;
	}

	_g_oNavoLog << "checked " + CString(_human_name());

	return bInstallNAVO2001;
}

HRESULT download_url_2_file (LPCTSTR lpURL, LPCTSTR lpFile, bool bUI);

setuperror CNE2002Installer::_download_files(  CProgressInfo& roProgressInfo)
{
	long iter = 0;

	_g_oNavoLog << "start downloading engine files";

	while( _g_cEngineFiles[iter].m_poName != NULL)
	{
		CFileInfo & roFileInfo = _g_cEngineFiles[iter];

		if( roFileInfo.m_bDownload)
		{
			CString oRootDir( pcWWWRoot);
			CString oFileName( roFileInfo.m_poName);
			CString oRelativePath( _subdir_name());
			EnsureEndingBackslash(oRelativePath);
			oRelativePath += oFileName;
			CString oSrcFilePath;

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
			
			CString oUniqueFilePath = GenerateUniqueFileName ("NS", oExt);

			CSimpleOleInitHolder oSimpleOleInitHolder;
			_g_oNavoLog << "downloading file: " + oRootDir + oRelativePath;
			_g_oNavoLog << "as:" + oUniqueFilePath;


			HRESULT hr = download_url_2_file (oRootDir + oRelativePath, oUniqueFilePath, true);
			//setuperror err = _g_oWindows.DownloadFile(oRootDir + oRelativePath, oUniqueFilePath);
			//if( err != stpe_ok)
			//{
			//	return err;
			//}
			if(hr == E_ABORT)
			{
				_g_oNavoLog << "user break";
				return stpe_user_break;
			}

			if (hr != S_OK)
			{
				_g_oNavoLog << "download failed";
				return stpe_download_failed;
			}
			
			m_oFilesMap[oRelativePath] = oUniqueFilePath;
		}

		iter ++;
	}


	_g_oNavoLog << ("engine source files downloaded");
	return stpe_ok;
}

setuperror CNE2002Installer::_verify_files( CProgressInfo& roProgressInfo)
{
	long iter = 0;


	while( _g_cEngineFiles[iter].m_poName != NULL)
	{
		CFileInfo & roFileInfo = _g_cEngineFiles[iter];

		if( roFileInfo.m_bCopy)
		{
			CString oSrcFilePath;

			setuperror eErco = FindSourcePath (oSrcFilePath, roFileInfo);

			while (!IsVersionValid (oSrcFilePath, roFileInfo.m_poVersion) &&
				   !roFileInfo.m_bDownload)
			{
				eErco = UserFindSourcePath( oSrcFilePath, roFileInfo);

				if (eErco != stpe_ok)
				{
					return eErco;
				}
			} 
		}

		iter++;
	}


	_g_oNavoLog << ("engine source files verified successfully");
	return stpe_ok;
}


setuperror CNE2002Installer::FindSourcePath (CString & roReturnPath, CFileInfo & roFileInfo)
{
	CString oFileName( roFileInfo.m_poName);
	CString oRelativePath (_subdir_name());
	EnsureEndingBackslash (oRelativePath);
	oRelativePath += oFileName;

	CString oRootDir = _g_oTaskParam._get_root_source ();
	EnsureEndingBackslash (oRootDir);

	oRelativePath.MakeLower();
	if( m_oFilesMap.Lookup( oRelativePath, roReturnPath))
	{
		return stpe_ok;
	}

	//sprawdŸ root-source
	
	if (IsVersionValid (oRootDir + oRelativePath, roFileInfo.m_poVersion))
	{
		roReturnPath = oRootDir + oRelativePath;
		return stpe_ok;
	}


	//sprawdŸ lokalizacjê z ostatniej instalacji
	oRootDir.Empty ();
	
	LONG lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName (), "MediaSource", oRootDir);
	
	while(lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - can not check last installation source";
		return stpe_not_enough_rights;

		//if( !_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - can not check last installation source";
		//	return stpe_not_enough_rights;
		//}

		//lResult = SafeGetRegistryKeyString (HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName (), "MediaSource", oRootDir);
	}
	
	if (!oRootDir.IsEmpty ())
	{
		EnsureEndingBackslash (oRootDir);

		if (IsVersionValid (oRootDir + oRelativePath, roFileInfo.m_poVersion))
		{
			_g_oTaskParam._set_root_source (oRootDir);
			roReturnPath = oRootDir + oRelativePath;
			return stpe_ok;
		}
	}

	//check cdrom
	oRootDir = _g_oWindows.FindFirstCDROMDrive ();

	if (!oRootDir.IsEmpty ())
	{
		EnsureEndingBackslash (oRootDir);

		if (IsVersionValid (oRootDir + oRelativePath, roFileInfo.m_poVersion))
		{
			roReturnPath = oRootDir + oRelativePath;
			return stpe_ok;
		}
	}

	if (!m_oUserDir.IsEmpty ())
	{
		EnsureEndingBackslash (m_oUserDir);

		if (IsVersionValid (m_oUserDir + oFileName, roFileInfo.m_poVersion))
		{
			roReturnPath = m_oUserDir + oFileName;
			return stpe_ok;
		}
	}
}

setuperror CNE2002Installer::UserFindSourcePath (CString & roReturnPath, CFileInfo & roFileInfo)
{
	CString oFileName( roFileInfo.m_poName);
	CString oRelativePath (_subdir_name());
	EnsureEndingBackslash (oRelativePath);
	oRelativePath += oFileName;

	roFileInfo.m_bDownload = _g_oTaskParam._is_internet_download ();

	if( roFileInfo.m_bDownload)
	{
		_g_oNavoLog << CString("marking file for download: ") + roFileInfo.m_poName;
		return stpe_ok;
	}
	
	CBrowseDlg oBrowse;
	oBrowse.m_strFile = oFileName;
	oBrowse.m_edMessage = "Instalator nie mo¿e odnaleŸæ pliku " + oFileName;

	if ( oBrowse.DoModal () == IDOK)
	{

		if (oBrowse.m_bDownload)
		{
			roFileInfo.m_bDownload = oBrowse.m_bDownload;	
			_g_oNavoLog << CString("marking file for download: ") + roFileInfo.m_poName;
		}
		else
		{
			m_oUserDir = oBrowse.m_strDir;
			roReturnPath = oBrowse.m_strDir + oFileName;
			_g_oNavoLog << "user pointed file: " +  roReturnPath;
			m_oFilesMap[oRelativePath] = roReturnPath;
		}

		_g_oTaskParam._set_internet_download( oBrowse.m_bDownloadAll);
	}
	else
	{
		return stpe_user_break;
	}

	return stpe_ok;
}



bool CNE2002Installer::IsVersionValid(const CString & roFilePath, const CString & roVersion)
{
	bool bVersionOK = _g_oWindows.is_valid_location( roFilePath); 
	_g_oNavoLog << "location: " + roFilePath + " is " + (bVersionOK ? "" : "not ") + "valid";

	if (roVersion != "") 
	{
		if( bVersionOK)
		{
			CVersion oFileVersion;

			bVersionOK = oFileVersion.Load (roFilePath) != FALSE;
			_g_oNavoLog << "file version load : " + roFilePath + " is " + (bVersionOK ? "" : "not ") + "valid";

			if (bVersionOK)
			{
				_g_oNavoLog << "found file version  : " + oFileVersion.GetFileVersion() + ", expected: " + roVersion;
		
				bVersionOK = oFileVersion.GetFileVersion() >= roVersion;
			}
		}
	}

	return bVersionOK;
}

setuperror CNE2002Installer::_create_dirs (CProgressInfo& roProgressInfo)
{
	CString oDestNAVO2001String = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Engine;
	EnsureEndingBackslash(oDestNAVO2001String);

	_g_oNavoLog << ("creating directory (and subs):" + oDestNAVO2001String);

	CString oMsgString;oMsgString.LoadString(IDS_CREATING_DIR);
	roProgressInfo.SetMonitorString( oMsgString + _g_oTaskParam._get_root_dest());
	NavoCreateDirectoryTree(_g_oTaskParam._get_root_dest());
	VERIFY(::SetFileAttributes(_g_oTaskParam._get_root_dest(),FILE_ATTRIBUTE_READONLY));

	roProgressInfo.SetMonitorString( oMsgString + _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Temporary);
	NavoCreateDirectoryTree(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Temporary);
	VERIFY(::SetFileAttributes(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Temporary,FILE_ATTRIBUTE_READONLY));
	
	roProgressInfo.SetMonitorString( oMsgString + oDestNAVO2001String);
	NavoCreateDirectoryTree(oDestNAVO2001String);
	VERIFY(::SetFileAttributes(oDestNAVO2001String,FILE_ATTRIBUTE_READONLY));
	
	if(_g_oTaskParam._get_install_variant() != iv_client)
	{
		roProgressInfo.SetMonitorString( oMsgString + _g_pchNAVO2001Archive);
		NavoCreateDirectoryTree(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Archive);
		VERIFY(::SetFileAttributes(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Archive,FILE_ATTRIBUTE_READONLY));

		roProgressInfo.SetMonitorString( oMsgString + _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Database);
		NavoCreateDirectoryTree(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Database);
		VERIFY(::SetFileAttributes(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Database,FILE_ATTRIBUTE_READONLY));
	}

	_g_oNavoLog << ("directories created");
	return stpe_ok;
}

setuperror CNE2002Installer::_update_registry( CProgressInfo& roProgressInfo)
{
	_g_oNavoLog << "updating registry entries";
	_g_oNavoLog << GetSetupRegistryKeyName();

	CString oMsgString;oMsgString.LoadString(IDS_UPDATING_REGISTRY);
	roProgressInfo.SetMonitorString( oMsgString + GetSetupRegistryKeyName());

	if( SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot",_g_oTaskParam._get_root_dest()))
	{
		return stpe_not_enough_rights;
		
		//if(!_g_oWindows._logon_as_admin())
		//{	
		//	return stpe_not_enough_rights;
		//}
		//else
		//{
		//	if( SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot",_g_oTaskParam._get_root_dest()))
		//	{
		//		return stpe_registry_write_fail;
		//	}
		//}
	}

	_g_oNavoLog << ("registry entries updated");
	return stpe_ok;
}

setuperror CNE2002Installer::_copy_files( CProgressInfo& roProgressInfo)
{
	CString oDestNAVO2001String = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Engine;
	EnsureEndingBackslash(oDestNAVO2001String);
	bool bAnyInUse = false;
	//copy files
	long iter = 0;


	while(_g_cEngineFiles[iter].m_poName != NULL)
	{
		if(_g_cEngineFiles[iter].m_bCopy)
		{
			CFileInfo & roFileInfo = _g_cEngineFiles[iter];
			bool bInUse;
			DWORD dwResult = ERROR_SUCCESS;

			CString oFullPathString;
			setuperror eErco = FindSourcePath( oFullPathString,roFileInfo);

			if(eErco != stpe_ok)
			{
				return eErco;
			}

			CString oFileDestString;
			if(roFileInfo.m_eDT == dest_winsys32)
			{
				oFileDestString = _g_oWindows._get_system32_dir() + roFileInfo.m_poName;
			}
			else if(roFileInfo.m_eDT == dest_navo2008)
			{
				oFileDestString = oDestNAVO2001String + roFileInfo.m_poName;
			}
			else if(_g_cEngineFiles[iter].m_eDT == dest_navoroot)
			{
				oFileDestString = _g_oTaskParam._get_root_dest() + roFileInfo.m_poName;
			}
			else
			{
				ASSERT(false);
			}

			_g_oNavoLog << ("copying engine file from " + oFullPathString + " to " +
				oFileDestString);
			CString oMsgString;oMsgString.LoadString(IDS_COPYING_FILE);
			roProgressInfo.SetMonitorString( oMsgString + oFileDestString);

			WIN32_FIND_DATA wfdFindFileData;
			HANDLE hFind;

			hFind = ::FindFirstFile( oFullPathString, &wfdFindFileData);

			if (hFind != INVALID_HANDLE_VALUE) 
			{
				::FindClose( hFind);

				if( wfdFindFileData.nFileSizeLow > 0)
				{
					dwResult = NAVOSetupFileEx( oFullPathString, oFileDestString, bInUse);
				}
				else
				{
					_g_oNavoLog << "copying failed. File size incorrect; file: " + oFullPathString + "; size: " + Long2String((long)wfdFindFileData.nFileSizeLow);
					return stpe_file_size_incorrect;
				}
			} 
			else
			{
				dwResult = ::GetLastError();
			}

			while(dwResult == ERROR_ACCESS_DENIED)
			{
				return stpe_not_enough_rights;

				//if(!_g_oWindows._logon_as_admin())
				//{
				//	return stpe_not_enough_rights;
				//}

				//dwResult = NAVOSetupFileEx( oFullPathString, oFileDestString, bInUse);
			}


			if(dwResult == ERROR_SUCCESS)
			{
				if(bInUse)
				{
					_g_oNavoLog << ("engine file " + oFileDestString + " was in use!");
					bAnyInUse = true;
				}
			}
			else
			{
				_g_oNavoLog << ( "copying failed. Windows error code=" + Long2String((long)dwResult));
				return stpe_file_copy_failed;
			}

			_g_oNavoLog << ("engine file " + oFullPathString + " copied");
		}
		iter++;
	}

	if(bAnyInUse)
	{
		_g_oNavoLog << ("setting registry pending flag");
		

		LONG lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), 
			"RegPending", "Y");


		while (lResult == ERROR_ACCESS_DENIED)
		{
			_g_oNavoLog << "not enough rights - could not write pending flag";
			return stpe_not_enough_rights;

			//if(!_g_oWindows._logon_as_admin())
			//{
			//	_g_oNavoLog << "not enough rights - could not write pending flag";
			//	return stpe_not_enough_rights;
			//}

			//lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), 
			//	"RegPending", "Y");
		}

		if(lResult == ERROR_SUCCESS)
		{
			_g_oNavoLog << "pending flag set - restart required";
			return stpe_restart_required;
		}

		_g_oNavoLog << "unknown error writing HKEY_LOCAL_MACHINE\\" << GetSetupRegistryKeyName() << "RegPending";
		_g_oNavoLog << "error code: " << Long2String(lResult);
		return stpe_internal_error;
	}

	_g_oNavoLog << ("engine files copied successfully");
	return stpe_ok;
}

setuperror CNE2002Installer::_register_files(  CProgressInfo& roProgressInfo)
{
	setuperror eErco = stpe_ok;
	_g_oNavoLog << ("registering engine components");
	//now register at location pointed by _g_oTaskParam._get_root_dest()

	long iter = 0;

	while(_g_cEngineFiles[iter].m_poName != NULL)
	{
		switch(_g_cEngineFiles[iter].m_nRegisterMethod)
		{
		case REGMET_DLL:
			try
			{
				CString oFileNameString = _g_oTaskParam._get_root_dest() + CString(_g_pchNAVO2001Engine) + _g_cEngineFiles[iter].m_poName;

				_g_oNavoLog << "registering DLL: " + oFileNameString;
				CString oMsgString;oMsgString.LoadString(IDS_REGISTERING_FILE);
				roProgressInfo.SetMonitorString( oMsgString + oFileNameString);

				eErco = _g_oWindows.RegComponent(true,oFileNameString);

				_g_oNavoLog << ("DLL registered. result is " + Long2String(long(eErco)));
				
				if(eErco != stpe_ok)
				{
					return eErco;
				}
			}
			catch(...)
			{
				_g_oNavoLog << ("DLL register failed ");
				return stpe_register_failed;
			}
		break;

		case REGMET_EXE:
		{
			CString oFilePathString = _g_oTaskParam._get_root_dest() + CString(_g_pchNAVO2001Engine);
			CString oFileNameString = oFilePathString + _g_cEngineFiles[iter].m_poName;

			CString oExpandedArgumentsString;
			//very simple expander - expands single %s to destdir
			oExpandedArgumentsString.Format( _g_cEngineFiles[iter].m_poArguments, _g_oTaskParam._get_root_dest());

			_g_oNavoLog << "registering EXE: " + oFileNameString + CString("with arguments ") + oExpandedArgumentsString;
			CString oMsgString;oMsgString.LoadString(IDS_REGISTERING_FILE);
			roProgressInfo.SetMonitorString( oMsgString + oFileNameString + oExpandedArgumentsString);

			long nExitCode;
			errorcode eErrorCode = ExecuteProcess( oFileNameString,oFilePathString,	oExpandedArgumentsString, SW_SHOW, nExitCode, false);
			_g_oNavoLog << ("EXE registered. result is" + Long2String(long(eErco)));

			if(eErrorCode != ERCO_OK)
			{
				return stpe_restart_required;
			}
		}
		break;
		case REGMET_DOTNET:
		{
			try
			{
				CString oFileNameString = _g_oTaskParam._get_root_dest() + CString(_g_pchNAVO2001Engine) + _g_cEngineFiles[iter].m_poName;

				_g_oNavoLog << "registering .net DLL: " + oFileNameString;
				CString oMsgString;oMsgString.LoadString(IDS_REGISTERING_FILE);
				roProgressInfo.SetMonitorString( oMsgString + oFileNameString);

				eErco = _g_oWindows.RegDotNetComponent(true,_g_oTaskParam._get_root_dest() + CString(_g_pchNAVO2001Engine),oFileNameString);

				_g_oNavoLog << (".net DLL registered. result is " + Long2String(long(eErco)));
				
				if(eErco != stpe_ok)
				{
					return eErco;
				}
			}
			catch(...)
			{
				_g_oNavoLog << (".net DLL register failed ");
				return stpe_dotnetregister_failed;
			}
		}
		break;
		case REGMET_NO:
		break;

		default:
			ASSERT(false);
		}
		iter++;
	}
	_g_oNavoLog << ("engine components registered");

	_g_oNavoLog << ("clearing registry pending flag");
	LONG lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "RegPending","N");

	while (lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not clear pending flag";
		return stpe_not_enough_rights;
		
		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not clear pending flag";
		//	return stpe_not_enough_rights;
		//}

		//lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "RegPending","N");
	}

	if(lResult != ERROR_SUCCESS)
	{
		_g_oNavoLog << "unknown error writing HKEY_LOCAL_MACHINE\\" << GetSetupRegistryKeyName() << "RegPending";
		_g_oNavoLog << "error code: " << Long2String(lResult);
		return stpe_internal_error;
	}

	_g_oNavoLog << ("engine components registered");

	return eErco;
}

const TCHAR * _g_pchNE2ServiceName = _T("NAVOEnterprise2002");

setuperror CNE2002Installer::_install()
{
	CString oTitleString;
	oTitleString.LoadString(IDS_PROGRESSTITLE2);
	CProgressInfo oProgressInfo(4,false,oTitleString);
	_g_oNavoLog << ("installing engine");

	CVirtualNTServiceManager oVNTSM(_g_pchNE2ServiceName);
	oVNTSM.stop();
	//verify files

	setuperror eErrorCode = _register_uninstall_info();
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}

	eErrorCode = _update_registry( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}

	eErrorCode = _create_dirs( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}

	eErrorCode = _verify_files( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}

	eErrorCode = _download_files( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}

	oProgressInfo.StepIt();
	eErrorCode = _copy_files( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}
	oProgressInfo.StepIt();
	eErrorCode = _register_files( oProgressInfo);
	if(eErrorCode != stpe_ok)
	{
		return eErrorCode;
	}
	oProgressInfo.StepIt();

	_g_oNavoLog << ("engine installed");
	oProgressInfo.StepIt();
	return stpe_ok;
}

const TCHAR * _g_pchNE2Name		 = _T("Platforma NAVO Enterprise 2020");
const TCHAR * _g_pchPackAppEng	 = _T("NAVO Enterprise 2020 Packed App");
const TCHAR * _g_pchPackAppPL	 = _T("Spakowana aplikacja NAVO Enterprise 2020");

setuperror CNE2002Installer::_register_uninstall_info()
{
	_g_oNavoLog << "registering uninstall information";
	CString oDestEngineDirString = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Engine;

	LONG lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"DisplayName",_g_pchNE2Name);

	while (lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not register uninstall information";
		return stpe_not_enough_rights;
		
		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not clear pending flag";
		//	return stpe_not_enough_rights;
		//}

		//lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "RegPending","N");
	}

	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"UninstallString",
		oDestEngineDirString + "setup.exe /uninstall");
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"HelpLink",
		"http://www.navo.com.pl/NAVO Enterprise 2020/default.htm");
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"HelpTelephone",
		"(0 71) 785 46 71");
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"Publisher",
		"NAVO Spó³ka z o.o.");
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"URLInfoAbout",
		"http://www.navo.com.pl/");
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall,"URLUpdateInfo",
		"http://www.navo.com.pl/NAVO Enterprise 2020/update.htm");

	SafeSetRegistryKeyString(HKEY_CLASSES_ROOT,".npx","",_g_pchPackAppEng);
	SafeSetRegistryKeyString(HKEY_CLASSES_ROOT,_g_pchPackAppEng,"",
		_g_pchPackAppPL);

	SafeSetRegistryKeyString(HKEY_CLASSES_ROOT,"NAVO Enterprise 2020 Packed App\\shell\\Zainstaluj\\command","",
		oDestEngineDirString + "setup.exe /app \"%1\"");
	SafeSetRegistryKeyString(HKEY_CLASSES_ROOT,"NAVO Enterprise 2020 Packed App\\DefaultIcon","",
		oDestEngineDirString + "setup.exe,1");


	_g_oNavoLog << ("uninstall information registered");

	return stpe_ok;
}


extern CFileInfo _g_cEngineFiles [];

CString PrepareDelBatch(const CString & roNE2K2SystemDirString)
{
	//delne2k2.bat
	//:Repeat
	//del "C:\Win95ADG\SETUP.EXE"
	//if exist "SETUP.EXE" goto Repeat
	//rmdir "C:\Win95ADG"
	//del "\delne2k2.bat"

	CString oBatchPathString(_g_oWindows._get_dir());
	EnsureEndingBackslash(oBatchPathString);
	oBatchPathString += "delne2k2.bat";
	CNavoLog oBatchNL(true);
	oBatchNL.Open(oBatchPathString);
	oBatchNL << ":Repeat\r\ndel \"" + roNE2K2SystemDirString + "setup.exe\"\r\n";
	oBatchNL << "if exist \"" + roNE2K2SystemDirString + "setup.exe\" goto Repeat\r\n";
	oBatchNL << "rmdir " + roNE2K2SystemDirString + "\r\n";
	oBatchNL << "del delne2k2.bat\r\n";
	return oBatchPathString;
}

setuperror CNE2002Installer::_uninstall()
{	
	CString oTitleString;
	oTitleString.LoadString(IDS_PROGRESSTITLE2);
	CProgressInfo oProgressInfo(35,false,oTitleString);
	_g_oNavoLog << ("uninstalling engine");

	setuperror eErco = stpe_ok;
	//leave dcom, vbscript etc.
	//uninstall just engine

	//to_do:
	//find instalation root
	//1. unregister engine
	CString oInstallRootString;
	//spróbuj z ostatniej 

	LONG lResult =  SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),"InstallationRoot",oInstallRootString);

	// remove registry entries
//	oProgressInfo.SetMonitorString( CString("deleting: HKEY_LOCAL_MACHINE\\") + _g_pchEngineUninstall);
	lResult = SafeDeleteRegistryKey(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall);

	while (lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not clear delete HKEY_LOCAL_MACHINE\\" << _g_pchEngineUninstall;
		return stpe_not_enough_rights;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not clear delete HKEY_LOCAL_MACHINE\\" << _g_pchEngineUninstall;
		//	return stpe_not_enough_rights;
		//}

		//lResult = lResult = SafeDeleteRegistryKey(HKEY_LOCAL_MACHINE,_g_pchEngineUninstall);
	}
	
	if(lResult != ERROR_SUCCESS)
	{
		if(lResult != ERROR_FILE_NOT_FOUND)
		{
			_g_oNavoLog << "unknown error deleting HKEY_LOCAL_MACHINE\\" << _g_pchEngineUninstall;
			_g_oNavoLog << "error code: " << Long2String(lResult);
			return stpe_internal_error;
		}
	}
			
	EnsureEndingBackslash( oInstallRootString);
	oInstallRootString += _g_pchNAVO2001Engine;
	EnsureEndingBackslash( oInstallRootString);

	long iter = 0;
	while(_g_cEngineFiles[iter].m_poName != NULL)
	{
		WIN32_FIND_DATA wfdFindFileData;
		HANDLE hFind;
		CString oMsgString;oMsgString.LoadString(IDS_DELETING_FILE);
		oProgressInfo.SetMonitorString( oMsgString + oInstallRootString + _g_cEngineFiles[iter].m_poName);

		hFind = ::FindFirstFile( oInstallRootString + _g_cEngineFiles[iter].m_poName, &wfdFindFileData);

		if (hFind != INVALID_HANDLE_VALUE) 
		{
			::FindClose( hFind);

			switch(_g_cEngineFiles[iter].m_nRegisterMethod)
			{
				case REGMET_DLL:
				{
					_g_oNavoLog << "unregistering DLL: " + oInstallRootString + _g_cEngineFiles[iter].m_poName;

					try
					{
						eErco = _g_oWindows.UnregComponent( true, oInstallRootString + _g_cEngineFiles[iter].m_poName);
						_g_oNavoLog << "DLL unregistered. result is " + Long2String(long(eErco));
					}
					catch(...)
					{
						_g_oNavoLog << "DLL unregister failed (it may be already uninstalled)";
					}
				}
				break;

				case REGMET_EXE:
				{
					{
						try
						{
							long nExitCode;
							_g_oNavoLog << ("unregistering EXE: " + oInstallRootString + _g_cEngineFiles[iter].m_poName);
							errorcode eErrorCode = ExecuteProcess(oInstallRootString + _g_cEngineFiles[iter].m_poName,oInstallRootString,
								"/unregserver",SW_SHOW,nExitCode,false);
							//to_do: analiza kodu b³êdu
							_g_oNavoLog << ("EXE unregistered. result is" + Long2String(long(eErrorCode)));
						}
						catch(...)
						{
							_g_oNavoLog << ("EXE unregister failed (it may be already uninstalled)");
						}
					}
				}
				break;

				case REGMET_NO:
				break;
			
				default:
				{
					ASSERT(false);
				}
			}
		}

		iter++;
		oProgressInfo.StepIt();
	}
	// remove engine files
	CString oMsgString;oMsgString.LoadString(IDS_DELETING_FILE);
	oProgressInfo.SetMonitorString( oMsgString + oInstallRootString);
	NavoRemoveDirectoryTree(oInstallRootString);
	oProgressInfo.StepIt();

	oProgressInfo.StepIt();
	// remove directories
	CString oDelBatchString = PrepareDelBatch(oInstallRootString);
	long nExitCode;
	oProgressInfo.SetMonitorString( oMsgString + CString("setup.exe"));
	ExecuteProcess( oDelBatchString,NULL,"",SW_HIDE,nExitCode,true);	
	oProgressInfo.StepIt();
	return stpe_ok;
}
