/*
	NAVO Enterprise 2008
	NAVO Server - NT Service version
	Copyright NAVO
	
	nt service support
*/

#include "stdafx.h"
#include <winsvc.h>
#include "..\include\navothread.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\navoserver\navoserverclassfactory.h"
#include "crossinfoman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNavoLog  oNavoLog;

enum EServiceErrorCode
{
	ESEC_OK = 0,
	ESEC_CREATE_SERVICE_FAILED = 1,
	ESEC_OPEN_SCM_FAILED = 2,
	ESEC_STOP_SERVICE_FAILED = 3,
	ESEC_DELETE_SERVICE_FAILED = 4,
	ESEC_OPEN_SERVICE_FAILED = 5,
	ESEC_START_DISPATCHER_FAILED = 6,
	ESEC_START_SERVICE_FAILED = 7,
	ESEC_QUERY_SERVICE_FAILED = 8,
	ESEC_CHANGE_SERVICE_CONFIG_FAILED = 9,
	ESEC_ACCESS_DENIED = 10,
};

EServiceErrorCode InstallService(const char *pcServicePath, const char *pcServiceName,
	const char *pcServiceDisplayName)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;
	EServiceErrorCode eResult = ESEC_OK;

	schSCManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!schSCManager)
	{
		DWORD dwErrorCode = GetLastError();
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			eResult = ESEC_ACCESS_DENIED;
			goto _exit;
		};
		eResult = ESEC_OPEN_SCM_FAILED;
		goto _exit;
	};
	schService = ::CreateService(
		schSCManager,               // SCManager database
		pcServiceName,					 // name of service
		pcServiceDisplayName,		 // name to display
		SERVICE_ALL_ACCESS,         // desired access
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,  // service type
		SERVICE_DEMAND_START,       // start type
		SERVICE_ERROR_NORMAL,       // error control type
		pcServicePath,              // service's binary
		NULL,                       // no load ordering group
		NULL,                       // no tag identifier
		TEXT(""),			          // dependencies
		NULL,                       // LocalSystem account
		NULL);                      // no password
	if (!schService)
	{
		eResult = ESEC_CREATE_SERVICE_FAILED;
		goto _exitManager;
	};
	::CloseServiceHandle(schService);
_exitManager:
	::CloseServiceHandle(schSCManager);
_exit:
	return eResult;
}

EServiceErrorCode UninstallService(const char *pcServiceName)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;
	SERVICE_STATUS ssStatus;
	EServiceErrorCode eResult = ESEC_OK;

	schSCManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!schSCManager)
	{
		DWORD dwErrorCode = GetLastError();
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			eResult = ESEC_ACCESS_DENIED;
			goto _exit;
		};
		eResult = ESEC_OPEN_SCM_FAILED;
		goto _exit;
	};
	schService = ::OpenService(schSCManager, pcServiceName, SERVICE_ALL_ACCESS);
	if (!schService)
	{
		eResult = ESEC_OPEN_SERVICE_FAILED;
		goto _exitManager;
	};
	// try to stop the service
	if ( ::ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )
	{
		Sleep( 1000 );
		while( ::QueryServiceStatus( schService, &ssStatus ) )
		{
			if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
			{
				Sleep( 1000 );
			}
			else
			{
				break;
			};
		}
		if ( ssStatus.dwCurrentState != SERVICE_STOPPED )
		{
			eResult = ESEC_STOP_SERVICE_FAILED;
			goto _exitService;
		};
	}
	// now remove the service
	if(!DeleteService(schService))
	{
		eResult = ESEC_DELETE_SERVICE_FAILED;
		goto _exitService;
	};
_exitService:
	::CloseServiceHandle(schService);
_exitManager:
	::CloseServiceHandle(schSCManager);
_exit:
	return eResult;
}
//--------------- global service informations ----------------------------------- 
void WINAPI _Server_ServiceMain(DWORD cArg, LPTSTR *rgszArg);
void WINAPI _Server_ServiceHandler(DWORD dwControl);

const TCHAR * pcNAVOEnterprise2002ServiceName = _T("NAVOEnterprise2012");
const TCHAR * pcNAVOEnterprise2002ServiceDesc = _T("NAVO Enterprise 2023 Service");
const SERVICE_TABLE_ENTRY _g_ste[2] =
{
	{ (TCHAR*)pcNAVOEnterprise2002ServiceName, _Server_ServiceMain },
	{ NULL, NULL } 
};

SERVICE_STATUS _Server_ServiceStatus;
SERVICE_STATUS_HANDLE _Server_ServiceStatusHandle = (SERVICE_STATUS_HANDLE)NULL;


//------------------------------------------------------------------------------

HINSTANCE GetNAVOCORE_InstanceHandle();

enum eServerState
{
	SERSTA_STOPPED = 0,
	SERSTA_RUNNING = 1
};

eServerState _g_ServerState = SERSTA_STOPPED;

CEvent _g_oExitEvent;

void WINAPI _Server_ServiceMain(DWORD cArg, LPTSTR *rgszArg)
{
	UNREFERENCED_PARAMETER(cArg);
	UNREFERENCED_PARAMETER(rgszArg);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	AfxSetResourceHandle(GetNAVOCORE_InstanceHandle());
    
	_Server_ServiceStatus.dwServiceType        = SERVICE_WIN32_OWN_PROCESS;
    _Server_ServiceStatus.dwCurrentState       = SERVICE_START_PENDING;
    _Server_ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    _Server_ServiceStatus.dwWin32ExitCode      = 0;
    _Server_ServiceStatus.dwServiceSpecificExitCode = 0;
    _Server_ServiceStatus.dwCheckPoint         = 0;
    _Server_ServiceStatus.dwWaitHint           = 0;
	_Server_ServiceStatusHandle = ::RegisterServiceCtrlHandler(pcNAVOEnterprise2002ServiceName,
		_Server_ServiceHandler);
	if(!_Server_ServiceStatusHandle)
	{
		return;
	}
	::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
	//start server
	if(_g_ServerState == SERSTA_STOPPED)
	{
		if(_g_NAVOServerCF.Initialize() && _g_CrossInfoCF.Initialize())
		{
			oNavoLog << _T("4. Register");
			_g_NAVOServerCF.Register();
			_g_CrossInfoCF.Register();
			oNavoLog << _T("5. Ready for clients");
			_g_ServerState = SERSTA_RUNNING;
		}
	}
	if(_g_ServerState == SERSTA_RUNNING)
	{
		_Server_ServiceStatus.dwCurrentState       = SERVICE_RUNNING;
		_Server_ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP;
		::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
	}
	CSyncObject * pEvents[] =
	{
		&_g_oExitEvent,
		&_g_NAVOServerCF._get_started_event()
	};
	CMultiLock oMLock(pEvents,2);
	while(true)
	{
		//teraz wolno zatrzymaæ
		_Server_ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP;
		::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
		
		DWORD dwWaitRes = oMLock.Lock(INFINITE,FALSE);
		if(dwWaitRes == WAIT_OBJECT_0)	// - exit exent
		{
			break;
		}
		else
		{
			//teraz nie bo s¹ u¿ytkownicy
			_Server_ServiceStatus.dwControlsAccepted   = 0;
			::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
			
			ASSERT(dwWaitRes == WAIT_OBJECT_0 + 1);		//started event
			_g_NAVOServerCF.WaitForEnd();
		}
	}
}


void WINAPI _Server_ServiceHandler(DWORD dwCtrlCode)
{
	bool bForceStop = false;
	switch(dwCtrlCode)
	{
	case SERVICE_CONTROL_SHUTDOWN:
		bForceStop = true;
	case SERVICE_CONTROL_STOP:
		if(_g_ServerState == SERSTA_RUNNING)
		{
			long nRunningClients = _g_NAVOServerCF._get_current_client_count();
			if(nRunningClients == 0 || bForceStop)
			{
				_Server_ServiceStatus.dwControlsAccepted   = 0;
				_Server_ServiceStatus.dwCurrentState       = SERVICE_STOP_PENDING;
				::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
				oNavoLog << _T("5. Beginning stop sequence");
				_g_CrossInfoCF.Done();
				_g_NAVOServerCF.Done();
				oNavoLog << _T("6. Done");
				_g_CrossInfoCF.Revoke();
				_g_NAVOServerCF.Revoke();
				oNavoLog << _T("7. Revoked");
				_g_CrossInfoCF.Uninitialize();
				_g_NAVOServerCF.Uninitialize();
				oNavoLog << _T("errors are: ") + _g_NAVOServerCF.GetErrorStorage().BuildCompleteErrorString();
				oNavoLog << _T("8. Cleaned");
				oNavoLog << _T("NAVO Enterprise 2023 Service is stopped");
				_Server_ServiceStatus.dwCurrentState       = SERVICE_STOPPED;
				_g_ServerState = SERSTA_STOPPED;
			}
			else
			{
				//nie powinno byæ mo¿liwe - zg³aszamy b³¹d
				_Server_ServiceStatus.dwWin32ExitCode = ERROR_SERVICE_CANNOT_ACCEPT_CTRL;
				_Server_ServiceStatus.dwCheckPoint++;
				::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
				_Server_ServiceStatus.dwWin32ExitCode = 0;
			}
		}
		if(_g_ServerState == SERSTA_STOPPED)
		{
			VERIFY(_g_NAVOServerCF._get_finished_event().SetEvent());
			_g_oExitEvent.SetEvent();
		}
	break;
	case SERVICE_CONTROL_INTERROGATE:
	break;
	}
	::SetServiceStatus(_Server_ServiceStatusHandle,&_Server_ServiceStatus);
}

int _Server_StartServiceDispatcher()
{
	return ::StartServiceCtrlDispatcher(_g_ste) ? 0 : ::GetLastError();
}

void _Server_Install()
{
	char cBuffer[ _MAX_PATH ];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(),cBuffer,sizeof(cBuffer)) != 0);
	CString oString(cBuffer);
	oString += _T(" /service");
	InstallService(oString,pcNAVOEnterprise2002ServiceName,pcNAVOEnterprise2002ServiceDesc);
}

void _Server_UnInstall()
{
	UninstallService(pcNAVOEnterprise2002ServiceName);
}
