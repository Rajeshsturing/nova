/*
	NAVO Enterprise 2008
	NAVO Server - NT Service version
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\navothread.h"
#include "..\navoserver\navoserverclassfactory.h"
#include "navoservice.h"
#include "crossinfoman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")

#if !defined(_NAVODOTNET) && !defined(NAVO2008)
#ifdef _DEBUG
#pragma comment(lib, "..\\navocore\\debug\\navocore.lib")
#else
#pragma comment(lib, "..\\navocore\\release\\navocore.lib")
#endif
#endif

//{{AFX_MSG_MAP(CNavoserviceApp)
//}}AFX_MSG


CNavoserviceApp::CNavoserviceApp()
{
}


CNavoserviceApp theApp;
CNavoLog  oNavoLog;
CNavoServerCF _g_NAVOServerCF(oNavoLog,true);
CCrossInfoCF _g_CrossInfoCF;

LPCTSTR _g_pcLogFileName = _T("navo2012.service.log.txt");

extern const TCHAR * pcNAVOEnterprise2002ServiceName;

void _Server_Install();
void _Server_UnInstall();
int _Server_StartServiceDispatcher();

BOOL CNavoserviceApp::InitInstance()
{
	CNavoException oNavoException;
	ALL_TRY
	{
		_g_NAVOServerCF._set_service_name(pcNAVOEnterprise2002ServiceName);
		_g_CrossInfoCF._set_service_name(pcNAVOEnterprise2002ServiceName);
	
		CString oLogPathString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),_T("InstallationRoot"),oLogPathString);
		if(!oLogPathString.IsEmpty())
		{
			EnsureEndingBackslash(oLogPathString);
			oLogPathString += _T("System\\");
		}
		else
		{
			oLogPathString = ".\\";
		}
		oLogPathString += _g_pcLogFileName;

		//NavoDeleteFile(oLogPathString);
		oNavoLog.Open(oLogPathString);

		oNavoLog << _T("NAVO Enterprise 2023 Service is starting");
		oNavoLog << _T("command line is:") + CString(m_lpCmdLine);

		oNavoLog << _T("1. NOIH");
		CNavoOleInitHolder oNavoOleInitHolder(CNavoOleInitHolder::MULTITHREADED);
		oNavoLog << _T("2. CIS");
		
		HRESULT hr = ::CoInitializeSecurity(NULL,-1,NULL,NULL,
			DCOM_AUTH_LEVEL,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,
			EOAC_NONE,
			NULL);
		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_OBJSERV_UNABLE_TO_INIT_SECURITY,
				IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
		}
		oNavoLog << _T("3. Init");
		_g_NAVOServerCF.InitModuleName(m_hInstance);
		_g_CrossInfoCF.InitModuleName(m_hInstance);

		CParametersSplitter oParameterSplitter(m_lpCmdLine);
		if(oParameterSplitter.GetParameter(_T("regserver")))
		{
			_g_NAVOServerCF.RegisterServer();
			_g_CrossInfoCF.RegisterServer();
			_Server_Install();
			oNavoLog << _T("registered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter(_T("unregserver")))
		{
			_g_NAVOServerCF.UnRegisterServer();
			_g_CrossInfoCF.UnRegisterServer();
			_Server_UnInstall();
			oNavoLog << _T("unregistered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter(_T("service")))
		{
			_Server_StartServiceDispatcher();
			return FALSE;
		}
	}
	TOP_ALL_CATCH_(oNavoException)
	oNavoLog << _T("NAVO Enterprise 2023 Service is crashed or bad command line");
	oNavoLog << _T("errors are: ") + oNavoException.BuildCompleteErrorString();
	oNavoLog << _T("----------------------------------------------------------------------");
	return FALSE;
}
