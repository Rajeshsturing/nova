/*
	NAVO Enterprise 2020
	setup application

	'task param' - set of configuration options used to perform setup task
*/

#include "stdafx.h"
#include "taskparam.h"
#include "coresetupserv.h"
#include "setup.h"

extern const TCHAR * _g_pchNAVO2001Root;
extern CNavoLog _g_oNavoLog;
extern CWindows _g_oWindows;
extern CSetupApp _g_setupApp;

setuperror CTaskParam::_init_with_defaults()
{
	m_eOperMode			= om_install;
	m_eInstallVariant	= iv_single;
	m_eStep				= ws_welcome;
	m_bAutomaticMode	= true;
	m_bInternetDownload = false;

	//todo-leszek m_oNeedInstallString = _T("xxxxxx");
	m_oNeedInstallString = _T("xxxxxx");
	ASSERT(m_oNeedInstallString.GetLength() == nec_max);
	m_oRootSourceMediaString = _g_setupApp._get_program_dir();
	EnsureEndingBackslash(m_oRootSourceMediaString);

	LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot", m_oRootDestPathString);

	while(lResult == ERROR_ACCESS_DENIED)
	{
		return stpe_not_enough_rights;

		//if(!_g_oWindows._logon_as_admin())
		//{
		//	return stpe_not_enough_rights;
		//}
		
		//lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), "InstallationRoot", m_oRootDestPathString);
	}

	if (lResult != ERROR_SUCCESS)
	{
		m_oRootDestPathString = _g_oWindows._get_program_files_dir();
		m_oRootDestPathString += _g_pchNAVO2001Root;
	}
	
	EnsureEndingBackslash(m_oRootDestPathString);

	return stpe_ok;
}

const TCHAR * CTaskParam::_pcRestartValueName = _T("Restart");

setuperror CTaskParam::_read_from_registry()
{
	CString oString;
	if(SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,GetSetupRegistryKeyName(),_pcRestartValueName,oString))
	{
		return stpe_cant_read_param;
	}
	CStringArray oStringArray;
	SplitString(oString,oStringArray, '|',true);
	if(oStringArray.GetSize() != 11)			//see _write_to_registry
	{
		return stpe_param_corrupted;
	}

	//decode param
	m_eOperMode				= eOperationMode(_ttol(oStringArray[0]));
	m_eInstallVariant		= eInstallVariant(_ttol(oStringArray[1]));
	m_oRootDestPathString	= oStringArray[2];
	m_oServerNameString		= oStringArray[3];
	m_oAppNameString		= oStringArray[4];
	m_eStep					= eWizardStep(_ttol(oStringArray[5]));
	m_oExitCmdString		= oStringArray[6];
	m_oRootSourceMediaString= oStringArray[7];
	m_bAutomaticMode		= (oStringArray[8] == "1");
	//m_oNeedInstallString	- after every restart information is gathered again
	
	ASSERT(m_oNeedInstallString.GetLength() == nec_max);
	m_oAppURLString			= oStringArray[9];
	m_bInternetDownload		= (oStringArray[10] == "1");
	return stpe_ok;
}

setuperror CTaskParam::_write_to_registry()
{
	CString oString;

	oString.Format(
			_T("%d|%d|%s|%s|%s|%d|%s|%s|%s|%s|%s"),
			long(m_eOperMode),
			long(m_eInstallVariant),
			m_oRootDestPathString,
			m_oServerNameString,
			m_oAppNameString,
			long(m_eStep),
			m_oExitCmdString,
			m_oRootSourceMediaString,
			m_bAutomaticMode ? "1" : "0",
			m_oAppURLString,
			m_bInternetDownload ? "1" : "0"
	);

	if(SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,GetSetupRegistryKeyName(),_pcRestartValueName,oString))
	{
		return stpe_cant_write_param;
	}

	return stpe_ok;
}

void CTaskParam::_clear_registry()
{
	SafeDeleteRegistryValue(HKEY_LOCAL_MACHINE,GetSetupRegistryKeyName(),_pcRestartValueName);
}

setuperror CTaskParam::_read_from_cmd_line(LPTSTR lpCmdLine)
{
	CString oCmdLineString(lpCmdLine);

	if(oCmdLineString == "")
	{
		return stpe_ok;
	}
	CParametersSplitter oParameterSplitter(lpCmdLine);
	
	oParameterSplitter.GetParameter("s",m_oExitCmdString);
	
	CString oModeString;
	if(oParameterSplitter.GetParameter(_T("monitor")))
	{
		m_eOperMode = om_monitor_process;
		//to_do:
		return stpe_ok;
	}
	else if(oParameterSplitter.GetParameter(_T("checkcore")))
	{
		m_eOperMode = om_checkengine;
		return stpe_ok;
	}
	else if(oParameterSplitter.GetParameter(_T("restart")))
	{
		setuperror stpError = _read_from_registry();
		return stpError;
	}
	else if(oParameterSplitter.GetParameter(_T("install"),oModeString))
	{
		m_eOperMode = om_install;
		if(oParameterSplitter.GetParameter(_T("src"),m_oRootSourceMediaString))
		{
			EnsureEndingBackslash(m_oRootSourceMediaString);
		}
		if(oParameterSplitter.GetParameter(_T("dest"),m_oRootDestPathString))
		{
			EnsureEndingBackslash(m_oRootDestPathString);
		}
		CString oTempAppNameString;
		CString oAppNameString;
		if(oParameterSplitter.GetParameter(_T("app"),oTempAppNameString))
		{
			oAppNameString = oTempAppNameString;
			long nPos2 = oAppNameString.ReverseFind('.');
			if(nPos2 == oAppNameString.GetLength() - 4)
			{
				long nPos1 = oAppNameString.ReverseFind('\\');
				ASSERT(nPos1 >= 0);
				ASSERT(nPos1 < nPos2);
				oAppNameString = oAppNameString.Mid(nPos1+1,nPos2-nPos1-1);
			}
		}
		if(!oAppNameString.IsEmpty())
		{
			m_oAppNameString = oAppNameString;
			m_oAppURLString = oTempAppNameString;
		}
		if(oModeString.CompareNoCase(_T("single")) == 0)
		{
			m_eInstallVariant = iv_single;
		}
		else if(oModeString.CompareNoCase(_T("client")) == 0)
		{
			m_eInstallVariant = iv_client;
		}
		else if(oModeString.CompareNoCase(_T("server")) == 0)
		{
			m_eInstallVariant = iv_server;
		}
		return stpe_ok;
	}
	else if(oParameterSplitter.GetParameter(_T("uninstall")))
	{
		m_eOperMode = om_uninstall;
		return stpe_ok;
	}
	return stpe_bad_cmd_line;
}
