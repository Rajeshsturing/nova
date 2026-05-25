/*
NAVO Sp. z o.o. (2001)

NAVO Enterprise

Application ENVELOPE
*/


#include "stdafx.h"
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif



int RunNAVOApplication(HINSTANCE hInstance,LPSTR lpCmdLine,int nCmdShow);
typedef int(*fpRNA)(HINSTANCE,LPSTR,int);

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE /*hPrevInstance*/,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
#ifdef _DEBUG
#define DUMPDIR "ne2001"
	::CreateDirectory("c:\\temp", NULL);
	::CreateDirectory("c:\\temp\\dump", NULL);
	::CreateDirectory("c:\\temp\\dump\\" DUMPDIR, NULL);
	::_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	::_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW | _CRTDBG_MODE_DEBUG);
	::_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	::_CrtSetReportFile(_CRT_WARN, ::CreateFile("c:\\temp\\dump\\" DUMPDIR "\\trace.dbg", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
	::_CrtSetReportFile(_CRT_ASSERT, ::CreateFile("c:\\temp\\dump\\" DUMPDIR "\\assert.dbg", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
	::_CrtSetReportFile(_CRT_ERROR, ::CreateFile("c:\\temp\\dump\\" DUMPDIR "\\error.dbg", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
#undef DUMPDIR
#endif

	HINSTANCE hCLINAVLib = NULL;

	try
	{	
		::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
		_set_abort_behavior( 0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);

		hCLINAVLib = ::LoadLibrary("navo2012.pagemanager.dll");
		if(hCLINAVLib != (HINSTANCE) NULL)
		{
			fpRNA pRNA = (fpRNA) ::GetProcAddress(hCLINAVLib,"?RunNAVOApplication@@YAHPAUHINSTANCE__@@PADH@Z");
			if(pRNA != NULL)
			{
				int nResult =  pRNA(hInstance,lpCmdLine,nCmdShow);
				if(nResult == -4)
				{
					goto run_setup;
				}
				if(nResult == -3)
				{
					goto ask_run_setup;
				}

				::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS);
				::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
				::FreeLibrary(hInstance);

				Sleep(15000);

				return nResult;
			}
		}

ask_run_setup:
		//repair or install
		if(::MessageBox(::GetActiveWindow(),
			"Uruchomienie aplikacji nieudane.\nCzy uruchomiæ program naprawczy/instalacyjny ?",
			"NAVO Enterprise 2023",
			MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return -3;
		}
run_setup:
		{
			PROCESS_INFORMATION ProcessInfo;
			STARTUPINFO StartupInfo;
			::ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
			StartupInfo.wShowWindow = (WORD)SW_SHOW;
			StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
			StartupInfo.cb = sizeof (STARTUPINFO);
			TCHAR acCmdLine[_MAX_PATH+_MAX_PATH];
			strcpy(acCmdLine,"setup.exe /checkcore ");
			strcat(acCmdLine,lpCmdLine);

			if (!::CreateProcess(
				NULL,
				acCmdLine,
				NULL,
				NULL,
				TRUE, 
				NORMAL_PRIORITY_CLASS,
				NULL,
				".\\",
				&StartupInfo,
				&ProcessInfo))
			{
				::MessageBox(::GetActiveWindow(),"Uruchomienie programu naprawczego nieudane","NAVO Enterprise 2020",
					MB_OK | MB_ICONEXCLAMATION);
				return -5;
			}
			return -6;
		}
	}
	catch(...)
	{
		return -2;
	}
	return 0;
}



