/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	Application object and system real entry
*/

#include "stdafx.h"
#include <locale.h>
#include <Wininet.h>
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navothread.h"		//navo thread
#include "..\include\dataunit.h"
#include "..\include\clientinfo.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoobj\dbapconnparam.h"
#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "commandexecutor.h"		
#include "ConnectServerDialog.h"

#include "..\navogal\ngal_iface.h"		//graphics
#include "application_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CleanupScriptEngineEtc();

//-------------------------
// singleton object
//-------------------------

class CApplicationServer
{
public:
	CApplicationServer() :
		m_idInstanceGener(1000)
	{
	}
	void SetLaunchInfoAndParseCmdLine(HINSTANCE hInstance, LPCTSTR lpCmdLine, int nCmdShow)
	{
		m_hLaunchInstance = hInstance;
		m_oLaunchCmdLineString = lpCmdLine;
		m_nCmdShow = nCmdShow;
	}
	int Work();
	void MiscelanousDone();
	void CreateDocumentFromCommandLine(LPCTSTR lpCmdLine);
private:
	CSimpleCriticalSection		m_oThreadsCS;
	CArray<HANDLE, HANDLE>		m_oThreadHandleArray;
	CArray<long, long>			m_oAppObjPtrArray;	//cndoc_application *
	CArray<long, long>			m_oInstanceIdArray; //instance idents

	HINSTANCE					m_hLaunchInstance;
	CString						m_oLaunchCmdLineString;
	int							m_nCmdShow;
	long						m_idInstanceGener;
};

const TCHAR const* pMMFOICmdLineName = "NAVOEnt_OI_CmdLine";

errorcode QuickCheckSystem(long nLevel);

int CApplicationServer::Work()
{
	CNavoException oNavoException;
	ALL_TRY
	{
		char* pActualLocale = ::setlocale(LC_ALL,"polish");
		VERIFY(pActualLocale != NULL);

		//create shared memory and detect other instance
		CMemoryMappedFileHolder oOtherInstanceCmdLineMMH(pMMFOICmdLineName,1024);
		if (!oOtherInstanceCmdLineMMH.IsOK())
		{
			ThrowNavoException(ERCO_APPSERV_MMF_FAILED,IDPAGE_NOTAVAILABLE);
		}
		if (oOtherInstanceCmdLineMMH.Existed())
		{

#ifndef _DEVELOPER_EDITION_
			if (AfxMessageBox(IDS_STARTANOTHERSESSION,MB_ICONQUESTION | MB_YESNO) != IDYES)
			{
				return 0;
			}
#endif
			_tcscpy((TCHAR*)oOtherInstanceCmdLineMMH.GetPtr(),m_oLaunchCmdLineString);
			oOtherInstanceCmdLineMMH.Signal();
			return 0;
		}
		//we are only instance
		CleanNavoTemporaryFiles();	//can exists from previous run

		//initialized by navo.exe process
		
		//CNavoOleInitHolder oNavoOleInitHolder(CNavoOleInitHolder::MULTITHREADED);
		//if (!oNavoOleInitHolder.IsOK())
		//{
		//	ThrowNavoException(ERCO_APPSERV_OLE_INIT_FAILED, IDPAGE_NOTAVAILABLE);
		//}
		//HRESULT hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL,
		//	DCOM_AUTH_LEVEL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL,
		//	EOAC_NONE,
		//	NULL);
		//if (hr != S_OK)
		//{
		//	ThrowNavoException1(ERCO_APPSERV_UNABLE_TO_INIT_SECURITY,
		//		IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		//}

		errorcode eErco = QuickCheckSystem(0);
		if (eErco != ERCO_OK)
		{
			ThrowNavoException(eErco,IDPAGE_NOTAVAILABLE);
		}

		HANDLE hDupHandle;
		VERIFY(duplicate_os_handle(oOtherInstanceCmdLineMMH.GetEventHandle(),hDupHandle));

		m_oThreadHandleArray.Add(hDupHandle);
		m_oAppObjPtrArray.Add(0);
		m_oInstanceIdArray.Add(0);

		CreateDocumentFromCommandLine(m_oLaunchCmdLineString);
		while (true)
		{
			if (m_oThreadHandleArray.GetSize() == 1)
			{
				MiscelanousDone();
				return 0;
			}
			DWORD dwResult = ::WaitForMultipleObjects(m_oThreadHandleArray.GetSize(),
				m_oThreadHandleArray.GetData(),FALSE,INFINITE);
			if (dwResult == WAIT_OBJECT_0)	//other instance signal
			{
				CreateDocumentFromCommandLine((TCHAR*)oOtherInstanceCmdLineMMH.GetPtr());
			}
			else if (dwResult >= WAIT_OBJECT_0 + 1 && dwResult <= WAIT_OBJECT_0 + m_oThreadHandleArray.GetSize())
			{
				CSimpleLock oSimpleLock(m_oThreadsCS);

				DWORD dwThreadExitCode = 0;
				if (::GetExitCodeThread(m_oThreadHandleArray[dwResult - WAIT_OBJECT_0],&dwThreadExitCode))
				{
					ASSERT(dwThreadExitCode != STILL_ACTIVE);
					if (dwThreadExitCode != 0)
					{
						MiscelanousDone();
						return dwThreadExitCode;
					}
				}
				else
				{
#ifdef _DEBUG
					DWORD dwLastError = ::GetLastError();
#endif
				}

				::CloseHandle(m_oThreadHandleArray[dwResult - WAIT_OBJECT_0]);

				m_oThreadHandleArray.RemoveAt(dwResult - WAIT_OBJECT_0);
				m_oAppObjPtrArray.RemoveAt(dwResult - WAIT_OBJECT_0);
				m_oInstanceIdArray.RemoveAt(dwResult - WAIT_OBJECT_0);
			}
		}
	}
		TOP_ALL_CATCH_(oNavoException)
		return -3;
}

void CApplicationServer::MiscelanousDone()
{
	CleanupScriptEngineEtc();
}

static bool DecodeURLString(const CString& roURLString, CString& roString)
{
	DWORD nBufferLength = (DWORD)roURLString.GetLength() * 2;
	BOOL bResult = ::InternetCanonicalizeUrl(roURLString, roString.GetBuffer(nBufferLength),
		&nBufferLength, ICU_DECODE | ICU_NO_ENCODE);
	roString.ReleaseBuffer();
	return (bResult != FALSE);
}

void CApplicationServer::CreateDocumentFromCommandLine(LPCTSTR lpCmdLine)
{
	//AfxMessageBox(lpCmdLine);

	//to_do: analyse lpCmdLine
	//uwaga! precursor rezerwuje dla siebie
	//-src
	//-dest
	//-checkcore
	//-server
	//-app

	CParametersSplitter oParameterSplitter(lpCmdLine);
	CString oInitialCommandString;
	if (oParameterSplitter.GetParameter("i", oInitialCommandString))
	{
		CString oDecodedString;
		if (!DecodeURLString(oInitialCommandString, oDecodedString))
		{
			goto bad_command;
		}
		oInitialCommandString = oDecodedString;
		goto run_command;
	}
	if (oParameterSplitter.GetParameter("s", oInitialCommandString))
	{
	run_command:
		//utwórz najpierw komunikaty
		oInitialCommandString += " vn5040=-1";
		try
		{
			SCP<CHyperLinkInfo> poInitialCmdHLISP = ReadHLIFromString(oInitialCommandString);
			long idInstance = 0;
			poInitialCmdHLISP->SafeGetNumProp(GVAR_SPAWNNEWDOC, idInstance);
			SCP<cndoc_application> poAppThreadSP;
			{
				CSimpleLock oSimpleLock(m_oThreadsCS);
				if (idInstance != 0)
				{
					for (long iter = 0; iter <= m_oInstanceIdArray.GetUpperBound(); iter++)
					{
						if (m_oInstanceIdArray[iter] == idInstance)
						{
							poAppThreadSP = NewSCP<cndoc_application>(
								reinterpret_cast<cndoc_application*>(m_oAppObjPtrArray[iter]), true);
							break;
						}
					}
				}

				if (poAppThreadSP.PointsNull())
				{
					if (idInstance == 0)
					{
						idInstance = m_idInstanceGener++;
					}
					poAppThreadSP = cndoc_application::create_application_thread(idInstance);
					HANDLE hDupHandle;
					VERIFY(duplicate_os_handle(poAppThreadSP->m_hThread, hDupHandle));
					m_oThreadHandleArray.Add(hDupHandle);
					m_oAppObjPtrArray.Add(reinterpret_cast<long>(poAppThreadSP.Get()));
					m_oInstanceIdArray.Add(idInstance);
				}
			}

			if (poInitialCmdHLISP->PropertyExists(GVAR_SPAWNNEWDOC))
			{
				poInitialCmdHLISP->DeleteProp(GVAR_SPAWNNEWDOC);
			}

			if (poAppThreadSP.PointsObject())
			{
				poAppThreadSP->post_command(poInitialCmdHLISP, false);
				poAppThreadSP->BringWindowToTopAUTO();
			}
			return;
		}
		catch (...)
		{
		}
		goto bad_command;
	}
	else
	{
		//missing parameters - fire connection dialog
		CConnectServerDialog oConnectDialog;
		if (oConnectDialog.DoModal() != IDOK)
		{
			return;
		}
		//compose command line
		oConnectDialog.m_ServerString.TrimLeft();
		oConnectDialog.m_ServerString.TrimRight();
		if (oConnectDialog.m_ServerString.IsEmpty())
		{
			oInitialCommandString.Format("vn1001=1030 vn1002=70000 vs8003='%s'",
				(LPCTSTR)oConnectDialog.m_AppNameString);
		}
		else
		{
			oInitialCommandString.Format("vn1001=1030 vn1002=70000 vs8003='%s' vs1012='%s'",
				(LPCTSTR)oConnectDialog.m_AppNameString, (LPCTSTR)oConnectDialog.m_ServerString);
		}
		goto run_command;
	}
bad_command:
	AfxMessageBox(IDS_BAD_CMD_LINE, MB_OK | MB_ICONINFORMATION);
}


CApplicationServer _g_NAVO2001AppServer;

void CreateUserDocumentFromCommandLine(LPCTSTR lpCmdLine)
{
	CMemoryMappedFileHolder oOtherInstanceCmdLineMMH(pMMFOICmdLineName, 1024);
	ASSERT(oOtherInstanceCmdLineMMH.Existed());
	_tcscpy((TCHAR*)oOtherInstanceCmdLineMMH.GetPtr(), lpCmdLine);
	oOtherInstanceCmdLineMMH.Signal();
}

int RunNAVOApplication(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	_g_NAVO2001AppServer.SetLaunchInfoAndParseCmdLine(hInstance, lpCmdLine, nCmdShow);
	return _g_NAVO2001AppServer.Work();
}