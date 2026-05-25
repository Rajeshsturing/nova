/*
	NAVO Enterprise 2020
	setup application

	'task param' - set of configuration options used to perform setup task
*/


#ifndef _TASK_PARAM_H_
#define _TASK_PARAM_H_

enum eOperationMode
{
	om_install			= 1,		//install components, engine and application
	om_uninstall		= 2,		//uninstall engine
	om_monitor_process	= 3,		//monitor process
	om_checkengine		= 4,		//check / reinstal engine only - fully automated
	om_error			= 5			//bad parameters
};


enum eInstallVariant
{
	iv_unknown		= 0,
	iv_single		= 1,	//single user installation (both client+server
	iv_server		= 2,	//server only installation
	iv_client		= 3,	//client only installation
};

////==================================================================================================
enum eWizardStep
{
	ws_welcome		= 0,
	ws_licence		= 1,
	ws_choosemode	= 2,
	ws_choosecomp	= 3,
	ws_chooseapp	= 4,
	ws_info			= 5,
	ws_max			= 6
};

enum eNEComponent
{
	nec_dcom	 = 0,	//dcom
	nec_wininst	 = 1,	//windows installer
	nec_vbscript = 2,	//vbscript
	nec_mdac	 = 3,	//mdac
	nec_dotnet   = 4,	//.NET
	nec_engine	 = 5,	//navo enterpise engine
	nec_max		 = 6,
};

class CTaskParam
{
public:
	CTaskParam(){}
	setuperror _init_with_defaults();
	setuperror _read_from_cmd_line(LPTSTR lpCmdLine);
	setuperror _read_from_registry();
	setuperror _write_to_registry();
	
	void _clear_registry();

	eOperationMode _get_operation_mode() const
	{
		return m_eOperMode;
	}

	void _set_root_dest(const CString & roString)
	{
		m_oRootDestPathString = roString;
		EnsureEndingBackslash(m_oRootDestPathString);
	}

	void _set_user_pointed_dir(const CString & roString)
	{
		m_oUserPoitedDir = roString;
		EnsureEndingBackslash (m_oUserPoitedDir);
	}

	const CString & _get_root_dest() const
	{
		return m_oRootDestPathString;
	}

	const CString & _get_user_pointed_dir() const
	{
		return m_oUserPoitedDir;
	}

	const CString & _get_app_name() const
	{
		return m_oAppNameString;
	}

	const CString & _get_app_location() const
	{
		return m_oAppURLString;
	}

	void _set_app_name(const CString & roAppName)
	{
		m_oAppNameString = roAppName;
	}

	void _set_app_location(const CString & roAppLocation)
	{
		m_oAppURLString = roAppLocation;
	}

	const CString & _get_exit_cmd() const
	{
		return m_oExitCmdString;
	}

	void _set_exit_cmd(const CString & roExitCmd)
	{
		m_oExitCmdString = roExitCmd;
	}

	const CString & _get_server_name() const
	{
		return m_oServerNameString;
	}

	void _set_server_name(const CString & roServerName)
	{
		m_oServerNameString = roServerName;
	}

	eWizardStep _get_current_step() const
	{
		return m_eStep;
	}

	void _set_current_step(eWizardStep eWS)
	{
		m_eStep = eWS;
	}

	bool _is_automode() const
	{
		return m_bAutomaticMode;
	}

	void _set_automode(bool bAuto)
	{
		m_bAutomaticMode = bAuto;
	}

	void _set_internet_download (bool bDownload)
	{
		m_bInternetDownload = bDownload;
	}

	void _set_oper_mode( eOperationMode eOperMode)
	{
		m_eOperMode = eOperMode;
	}

	eOperationMode _get_oper_mode() const
	{
		return m_eOperMode;
	}

	bool _is_internet_download() const
	{
		return m_bInternetDownload;
	}

	TCHAR _get_need_install_state(eNEComponent eNEC) const
	{
		return m_oNeedInstallString[eNEC];
	}

	void _set_need_install_state(eNEComponent eNEC,TCHAR cState)
	{
		ASSERT(cState >= '0' || cState <= '3');
		m_oNeedInstallString.SetAt(eNEC,cState);
	}

	eInstallVariant _get_install_variant() const
	{
		return m_eInstallVariant;
	}

	void _set_install_variant(eInstallVariant eIV)
	{
		m_eInstallVariant = eIV;
	}
	const CString & _get_root_source() const
	{
		return m_oRootSourceMediaString;
	}

	void _set_root_source(const CString & roString)
	{
		m_oRootSourceMediaString = roString;
	}

private:
	eOperationMode	m_eOperMode;
	eInstallVariant m_eInstallVariant;

	CString m_oRootDestPathString;	//root destination path
	CString m_oServerNameString;	//server to use (iv_client)
	CString m_oAppNameString;		//application to install
	CString m_oAppURLString;		//application location
	CString m_oExitCmdString;
	CString m_oRootSourceMediaString;
	CString m_oUserPoitedDir;
	bool	m_bAutomaticMode;
	bool	m_bInternetDownload;

	eWizardStep m_eStep;
	CString m_oNeedInstallString;
	static const TCHAR * _pcRestartValueName;

	friend class CWindows;
	friend class CWizzardContext;
};

#else
	#error __FILE__ already included
#endif
