/*
	NAVO Enterprise 2020
	setup application
*/

#include "stdafx.h"
#include "..\include\progressgadget.h"
#include "resource.h"
#include "coresetupserv.h"
#include "taskparam.h"
#include "componentinstaller.h"
#include "wizzardCtx.h"
#include "setup.h"
#include "..\navopx\navopx.h"


extern "C" const GUID __declspec(selectany) CLSID_NAVO2001AppDBManager =
	{0x188cb157,0x82a4,0x4498,{0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8}};

extern const TCHAR * _g_pchNAVO2001Applications;
extern const TCHAR * _g_pchNAVO2001Temporary;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupApp

BEGIN_MESSAGE_MAP(CSetupApp, CWinApp)
	//{{AFX_MSG_MAP(CSetupApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupApp construction

CSetupApp::CSetupApp()
: m_pcRunOnceName( _T("NAVO Enterprise 2020 Setup"))
{
}


CWindows _g_oWindows;	//core system services
CNavoLog _g_oNavoLog;   //istallation log
CTaskParam _g_oTaskParam;

CSetupApp _g_setupApp;
HINSTANCE _h_NAVOCORE_Instance = HINSTANCE(NULL);

extern const TCHAR * _g_pchNAVO2001Engine;
const TCHAR const * pcLogName = _T("NAVO Enterprise 2020.setup.log.txt");
long NAVOGetDiskFreeSpace(LPCTSTR lpDir);

BOOL CSetupApp::InitInstance()
{
	const TCHAR const * pMMFOICmdLineName ="NAVOEnt_OI_CmdLine";

	_h_NAVOCORE_Instance = m_hInstance;
	m_pszAppName = _tcsdup(_T("Instalacja Platformy NAVO Enterprise 2020"));
	
	_g_oWindows._init_zero();

	//open log - MUST be available
	{
		CString oLogNameString = _g_oWindows._get_drive();
		EnsureEndingBackslash(oLogNameString);
		oLogNameString += pcLogName;
		_g_oNavoLog.Open(oLogNameString);
	}
	_g_oNavoLog << CString("command line is: ") + m_lpCmdLine;

	if(!_g_oWindows._init())		//init subsystems
	{
		return FALSE;
	}
	if(!_g_oWindows._check())	//check OS and MUST BE prerequisites (IE 4.x +)
	{
		return FALSE;
	}

	setuperror eStpErr = stpe_ok;

	{
		TCHAR cThisProgramName[ _MAX_PATH ];
		VERIFY(::GetModuleFileName(_g_setupApp.m_hInstance,cThisProgramName,sizeof(cThisProgramName)) != 0);
		m_oThisProgramFullPathString = cThisProgramName;

		int nPos = m_oThisProgramFullPathString.ReverseFind('\\');
		ASSERT(nPos != -1);
		m_oThisProgramDirString = m_oThisProgramFullPathString.Left(nPos+1);

		eStpErr = _g_oTaskParam._init_with_defaults();
	}

	CMemoryMappedFileHolder oOtherInstanceCmdLineMMH(pMMFOICmdLineName,1024);

	if(eStpErr != stpe_ok)
	{
		goto bad_exit;
	}

	eStpErr = _g_oTaskParam._read_from_cmd_line(m_lpCmdLine);
	if(eStpErr != stpe_ok)
	{
		goto bad_exit;
	}

	if(oOtherInstanceCmdLineMMH.Existed())
	{
		_g_oNavoLog << "other NAVO2002 applications found. Exiting";

		if( _g_oTaskParam._get_operation_mode() != om_monitor_process)	
		{
			AfxMessageBox(IDS_NAVOAPP_ALREADY_RUNNING,MB_OK | MB_ICONINFORMATION);
			return FALSE;
		}
		else
		{
			_g_oNavoLog << "Monitor mode. Ignoring NAVO2002 applications and continue";
		}
	}

	if( _g_oTaskParam._get_operation_mode() != om_checkengine)
	{
		_clean_restart_info();
	}

	if( _g_oTaskParam._get_operation_mode() == om_monitor_process)
	{
		CString oMonitorProcessString;

		if(SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorProcess",oMonitorProcessString))
		{
			_g_oNavoLog << "missing MonitorProcess registry key";
			eStpErr = stpe_bad_monitor_command;
			goto bad_exit;
		}

		CString oMonitorDirString;
		if(SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorDir",oMonitorDirString))
		{
			_g_oNavoLog << "missing MonitorDir registry key";
			eStpErr = stpe_bad_monitor_command;
			goto bad_exit;
		}

		CString oMonitorArgsString;
		if(SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorArgs",oMonitorArgsString))
		{
			_g_oNavoLog << "missing MonitorArgs registry key";
			eStpErr = stpe_bad_monitor_command;
			goto bad_exit;
		}

		_g_oNavoLog << "monitoring process" + oMonitorProcessString + ",path=" + oMonitorDirString +
			",args=" + oMonitorArgsString;
		long lExitCode = 0;

		if( ERCO_OK != ExecuteProcess(oMonitorProcessString, oMonitorDirString, oMonitorArgsString, SW_SHOW, lExitCode, false))
		{
			eStpErr = stpe_monitor_failed;
		}

		if( lExitCode != 0)
		{
			eStpErr = stpe_monitor_failed;
		}

		SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorProcess");
		SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorDir");
		SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\NAVO\\NAVO2002\\Setup","MonitorArgs");
		_g_oNavoLog << "monitoring process finished with exitcode=" + Long2String(lExitCode);

	} 
	else
	{
		if( _g_oTaskParam._get_operation_mode() != om_checkengine)
		{
			eStpErr = CWizzardContext()._run();
			
			if(eStpErr != stpe_finished)
			{
				ASSERT( eStpErr != stpe_ok);
				goto bad_exit;
			}
		}

		switch(_g_oTaskParam._get_operation_mode())
		{
			case om_install:
			{
				_g_oNavoLog << "effective destination is: " << _g_oTaskParam._get_root_dest();
				{
					_g_oNavoLog << "checking free space on destination dir";
					long nFreeMB = NAVOGetDiskFreeSpace(_g_oTaskParam._get_root_dest());
					long nReqMB;
					
					switch( _g_oTaskParam._get_install_variant())
					{
						case iv_server:
						case iv_single: 
							nReqMB = 100;
							break;

						case iv_client:
							nReqMB = 50;
							break;
					}

					if( nFreeMB < nReqMB)
					{
						eStpErr = stpe_not_enough_disk_spc;
						goto bad_exit;
					}

					_g_oNavoLog << "successfully tested free space. It is "  + Long2String(nFreeMB) + " MB";
				}


				eStpErr =_install_components();

				if(eStpErr != stpe_ok)
				{
					goto bad_exit;
				}


				eStpErr = _install_application();

				if(eStpErr != stpe_ok)
				{
					goto bad_exit;
				}
			}
			break;

			case om_uninstall:
			{
				if( AfxMessageBox(IDS_OK_TO_UNINSTALL,MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
				{
					//AfxMessageBox(IDS_stpe_ok + long(eStpErr),MB_OK | MB_ICONEXCLAMATION);

					eStpErr = CNE2002Installer()._uninstall();

					if(eStpErr != stpe_ok)
					{
						goto bad_exit;
					}
				}
			}
			break;
			case om_checkengine:
			{
				_g_oNavoLog << "starting checkcore mode";
				CNE2002Installer oNE2K2Installer;
				oNE2K2Installer._need_install();		//mark what need to be copied
				eStpErr = oNE2K2Installer._install();
				_g_oNavoLog << "checkcore mode finished";
			}
			break;

			case om_error:

			default:
			{
				ASSERT(false);
				goto bad_exit;
			}
		}
	}

	if(!_g_oTaskParam._get_exit_cmd().IsEmpty())
	{
		CString oExitCmdString = "-s \"" + _g_oTaskParam._get_exit_cmd() + "\"";
		long nDummy;
		_g_oNavoLog << ("restarting navo2012.exe with arguments: " + oExitCmdString);
		CString oDestPathString = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Engine;
		EnsureEndingBackslash(oDestPathString);
		ExecuteProcess(oDestPathString + "navo2012.exe", oDestPathString, oExitCmdString, 
			SW_SHOW, nDummy, true);
	}

	return FALSE;
bad_exit:

	if( eStpErr == stpe_restart_required)
	{
		if(AfxMessageBox(IDS_stpe_ok + long(eStpErr),MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			//to_do: dla NT/2K trzeba dodaæ the SE_SHUTDOWN_NAME (patrz Remarks w ExitWindowsEx)
			if(!_g_oWindows._shutdown())
			{
				AfxMessageBox(IDS_stpe_ok + long(stpe_not_enough_rights),MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}
	else
	{
		AfxMessageBox(IDS_stpe_ok + long(eStpErr),MB_OK | MB_ICONEXCLAMATION);
	}

	return FALSE;
}

setuperror CSetupApp::_install_components()
{
	setuperror eStpErr =  _g_setupApp._prepare_restart_info();
	{
		if(eStpErr != stpe_ok)
		{
			return eStpErr;
		}

		for( eNEComponent iter = nec_dcom; iter < nec_max; iter = eNEComponent( long(iter) + 1))
		{
			if( _g_oTaskParam._get_need_install_state(iter) >= '2')	//yes
			{
				eStpErr = _g_oWindows._install_component(iter);

				if( eStpErr != stpe_ok)
				{
					if( eStpErr == stpe_user_break)
					{
						_g_setupApp._clean_restart_info();
					}

					return eStpErr;
				}
			}
		}
	}
	_g_setupApp._clean_restart_info();

	return stpe_ok;
}

const long nAppVersion	= 1;
HRESULT download_url_2_file(LPCTSTR lpURL,LPCTSTR lpFile,bool bUI);

setuperror CSetupApp::_install_application()
{
	CString roAppName( _g_oTaskParam._get_app_name());
	CString roAppLocation( _g_oTaskParam._get_app_location());

	roAppLocation.MakeLower();

	if( roAppLocation.Mid(0, 5) == "http:")
	{
		NavoCreateDirectoryTree(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Temporary);
		VERIFY(::SetFileAttributes(_g_oTaskParam._get_root_dest() + _g_pchNAVO2001Temporary,FILE_ATTRIBUTE_READONLY));

		CString oNpiLocation( roAppLocation);
		oNpiLocation.Replace( ".npx", ".npi");
		CString oUniqueFilePath = GenerateUniqueFileName ("NS", "npi");

		CSimpleOleInitHolder oSimpleOleInitHolder;

		_g_oNavoLog << "downloading file: " + oNpiLocation;
		_g_oNavoLog << "as: " + oUniqueFilePath;

		HRESULT hr = download_url_2_file( oNpiLocation, oUniqueFilePath, true);

		if( hr == E_ABORT)
		{
			_g_oNavoLog << "user break";
			return stpe_user_break;
		}

		if( hr != S_OK)
		{
			_g_oNavoLog << "download failed";
			return stpe_download_failed;
		}

		oUniqueFilePath.Replace(".npi", ".npx");

		_g_oNavoLog << "downloading file: " + roAppLocation;
		_g_oNavoLog << "as: " + oUniqueFilePath;

		hr = download_url_2_file( roAppLocation, oUniqueFilePath, true);

		if( hr == E_ABORT)
		{
			_g_oNavoLog << "user break";
			return stpe_user_break;
		}

		if( hr != S_OK)
		{
			_g_oNavoLog << "download failed";
			return stpe_download_failed;
		}

		roAppLocation = oUniqueFilePath;
	}



	CString oTitleString;
	oTitleString.Format(IDS_PROGRESSTITLE3,roAppName);
	CProgressInfo oProgressInfo(5,false,oTitleString);

	CString oRegKeyName(GetApplicationsRegistryKeyName());
	oRegKeyName += "\\" + CString(roAppName);
	
	CString oAppRootDirString;

	LONG nResult = SafeGetRegistryKeyString( HKEY_LOCAL_MACHINE,oRegKeyName,"Root",oAppRootDirString);

	if( nResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not read HKEY_LOCAL_MACHINE\\" << oRegKeyName << "\\Root";
		
		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not read HKEY_LOCAL_MACHINE\\" << oRegKeyName << "\\Root";
		//}

		//nResult = SafeGetRegistryKeyString( HKEY_LOCAL_MACHINE,oRegKeyName,"Root",oAppRootDirString);
	}

	if(oAppRootDirString.IsEmpty())
	{
		oAppRootDirString = _g_oTaskParam._get_root_dest() + _g_pchNAVO2001Applications;
		EnsureEndingBackslash(oAppRootDirString);
		oAppRootDirString += roAppName;
		_g_oNavoLog << ("constructed application path as: " + oAppRootDirString);
	}
	else
	{
		_g_oNavoLog << ("existing application path (on registry) is: " + oAppRootDirString);
	}

	CString oVersionString;
	nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyName,"Version",oVersionString);

	while( nResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "not enough rights - could not read HKEY_LOCAL_MACHINE\\" << oRegKeyName << "\\Version";
		return stpe_not_enough_rights;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "not enough rights - could not read HKEY_LOCAL_MACHINE\\" << oRegKeyName << "\\Version";
		//	return stpe_not_enough_rights;
		//}

		//nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyName,"Version",oVersionString);
	}

	if(_ttol(oVersionString) < nAppVersion)
	{
		//todo-leszek: handle incorrect version
	}

	CString oMsgString;oMsgString.LoadString(IDS_TESTING_APPDBMAN);
	oProgressInfo.SetMonitorString( oMsgString );
	_g_oNavoLog << "testing AppDBMan COM Object";
	{
		setuperror eErco = _g_oWindows.CheckCOMObject(CLSID_NAVO2001AppDBManager,stpe_comobj_check_fail);

		if(eErco != stpe_ok)
		{
			return eErco;
		}
	}

	CSimpleOleInitHolder oSimpleOleInitHolder;
	SCP<IAppDBManager>	poAppDBManagerSP;

//	oProgressInfo.SetMonitorString( CString("firing: AppDBMan"));
	_g_oNavoLog << ("firing AppDBMan...");
	{
		poAppDBManagerSP.CreateInstance(CLSID_NAVO2001AppDBManager,CLSCTX_ALL);

		if( poAppDBManagerSP.PointsNull())
		{
			return stpe_appdbman_create_fail;
		}
	}
	oProgressInfo.StepIt();


	_g_oNavoLog << ("AppDBMan OK. Installing application " + roAppName);
	{
		ASSERT(!oAppRootDirString.IsEmpty());
	}

	//create
	//init
	//unpack

	HRESULT hr;

	oMsgString.LoadString(IDS_CREATING_APP);
	oProgressInfo.SetMonitorString( oMsgString +  roAppName);
	_g_oNavoLog << ("Creating App...");
	{
		hr = poAppDBManagerSP->CreateApp(roAppName,oAppRootDirString,nAppVersion);
	
		if(hr != S_OK)
		{
			return stpe_appdb_create_fail;
		}
	}
	oProgressInfo.StepIt();

//	oProgressInfo.SetMonitorString( CString("initializing: ") + roAppName);
	_g_oNavoLog << ("App OK. Initing App..."); 
	{
		hr = poAppDBManagerSP->Init(roAppName);

		if(hr != S_OK)
		{
			return stpe_appdb_init_fail;
		}
	}
	oProgressInfo.StepIt();

	
	oMsgString.LoadString(IDS_UNPACKING_APP);
	oProgressInfo.SetMonitorString( oMsgString + roAppName);
	_g_oNavoLog << "App inited OK. Unpacking...";
	{
		//œcie¿ka Ÿród³owa do .npx, npi
		CString oNPXPathString = roAppLocation;
		int nPos = 	roAppLocation.ReverseFind('.');
		CString oNPIPathString = oNPXPathString.Left(nPos+1) + _T("npi");
		CSmartOleVariant oNPXSOV(oNPXPathString),oNPISOV(oNPIPathString);

		hr = poAppDBManagerSP->Unpack(oNPXSOV.GetVariantRef(), oNPISOV.GetVariantRef());

		if(hr != S_OK)
		{
			return stpe_appdb_unpack_fail;
		}
	}
	oProgressInfo.StepIt();

	_g_oNavoLog << "App unpacked OK.";
	_g_oNavoLog << "application " + roAppName + " installed";

	if(_g_oTaskParam._get_install_variant() != iv_client)
	{
		_g_oTaskParam._set_exit_cmd("vn1001=1030 vn1002=72002 vs8003='" + 
			_g_oTaskParam._get_app_name() + "'");
	}
	else
	{
		_g_oTaskParam._set_exit_cmd("vn1001=1030 vn1002=72000 vs8003='" + 
			_g_oTaskParam._get_app_name() + "' vs1012='" + 
			_g_oTaskParam._get_server_name()  + "'");
	}
	
	return stpe_ok;
}

setuperror CSetupApp::_prepare_restart_info()
{
	CString oRunOnceString = m_oThisProgramFullPathString + _T(" /restart");
	_g_oNavoLog << ("Storing RunOnce key: " + oRunOnceString);
	
	LONG lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",m_pcRunOnceName,oRunOnceString);

	while(lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << ("failed to write RunOnce command to registry. Manual restart required");
		return stpe_not_enough_rights;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << ("failed to write RunOnce command to registry. Manual restart required");
		//	return stpe_not_enough_rights;
		//}
		
		//lResult = SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,
		//	"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",m_pcRunOnceName,oRunOnceString);
	}

	if(lResult != ERROR_SUCCESS)
	{
		_g_oNavoLog << "unknown error writing HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce" << m_pcRunOnceName;
		_g_oNavoLog << "error code: " << Long2String(lResult);
		return stpe_internal_error;
	}


	return _g_oTaskParam._write_to_registry();
}

void CSetupApp::_clean_restart_info()
{
	LONG lResult = SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
		m_pcRunOnceName);

	while(lResult == ERROR_ACCESS_DENIED)
	{
		_g_oNavoLog << "failed to clean restart info";
		return;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	_g_oNavoLog << "failed to clean restart info";
		//	return;
		//}

		//lResult = SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
		//	m_pcRunOnceName);
	}

	if(lResult != ERROR_SUCCESS)
	{
		_g_oNavoLog << "failed to clean restart info";
		return;
	}

	_g_oTaskParam._clear_registry();
}



//copied from \navocore\navooleutil.cpp

IMPLEMENT_DYNCREATE(CCmdTargetInterface,CCmdTarget);
