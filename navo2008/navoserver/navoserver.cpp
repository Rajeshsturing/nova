/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	NAVO Server EXE
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "navoserverclassfactory.h"
#include "navoserver.h"
#include "..\navodb\NAVODB_Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")


//{{AFX_MSG_MAP(CNAVOServerApp)
//}}AFX_MSG


CNAVOServerApp::CNAVOServerApp()
{
}

CNAVOServerApp theApp;
CNavoLog oNavoLog;
CNavoServerCF _g_NAVOServerCF(oNavoLog,false);

LPCTSTR _g_pcLogFileName = _T("navo2012.server.log.txt");
/////////////////////////////////////////////////////////////////////////////
// CNAVOServerApp initialization

BOOL CNAVOServerApp::InitInstance()
{
	CNavoException oNavoException;
	
	ALL_TRY
	{
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

		oNavoLog << _T("NAVO Enterprise 2023 Server is starting");
		oNavoLog << _T("command line is:") + CString(m_lpCmdLine);

		CParametersSplitter oParameterSplitter(m_lpCmdLine);
		if(oParameterSplitter.GetParameter(_T("regserver")))
		{
			_g_NAVOServerCF.InitModuleName(m_hInstance);
			_g_NAVOServerCF.RegisterServer();
			oNavoLog << _T("registered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter(_T("unregserver")))
		{
			_g_NAVOServerCF.UnRegisterServer();
			oNavoLog << _T("unregistered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter(_T("embedding")))
		{
			oNavoLog << _T("1. NOIH");
			CNavoOleInitHolder oNavoOleInitHolder(CNavoOleInitHolder::MULTITHREADED);
			oNavoLog << _T("2. CIS");

			HRESULT hr = ::CoInitializeSecurity(NULL,-1,NULL,NULL,
				DCOM_AUTH_LEVEL, RPC_C_IMP_LEVEL_IMPERSONATE,NULL,
				EOAC_NONE,
				NULL);
			if(hr != S_OK)
			{
				ThrowNavoException1(ERCO_OBJSERV_UNABLE_TO_INIT_SECURITY,
					IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
			}
			oNavoLog << _T("3. Init");
			_g_NAVOServerCF.InitModuleName(m_hInstance);
			if(_g_NAVOServerCF.Initialize())
			{
				//NAVODB_Global_initialize();

				oNavoLog << _T("4. Register");
				_g_NAVOServerCF.Register();
				oNavoLog << _T("5. Ready for clients");
				_g_NAVOServerCF.WaitForEnd();
				_g_NAVOServerCF.Done();
				oNavoLog << _T("6. Done");
				_g_NAVOServerCF.Revoke();
				oNavoLog << _T("7. Revoked");
				_g_NAVOServerCF.Uninitialize();
				oNavoException += _g_NAVOServerCF.GetErrorStorage();

				//NAVODB_Global_done();
			}
			oNavoLog << _T("8. Cleaned");
			oNavoLog << _T("NAVO Enterprise 2023 Server is stopped");
			return FALSE;
		}
	}
	TOP_ALL_CATCH_(oNavoException)
	oNavoLog << _T("NAVO Enterprise 2023 Server is crashed or bad command line");
	oNavoLog << _T("errors are: ") + oNavoException.BuildCompleteErrorString();
	oNavoLog << _T("----------------------------------------------------------------------");
	return FALSE;
}
