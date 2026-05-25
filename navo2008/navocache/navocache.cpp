/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Cache Server EXE
*/

#include "stdafx.h"
#include <locale.h>
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\navolog.h"
#include "navocache.h"
#include "srvclassfactory.h"
#include "CacheManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "rpcrt4.lib")
/////////////////////////////////////////////////////////////////////////////
// CNavoCacheApp

BEGIN_MESSAGE_MAP(CNavoCacheApp, CWinApp)
	//{{AFX_MSG_MAP(CNavoCacheApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavoCacheApp construction

CNavoCacheApp::CNavoCacheApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNavoCacheApp object

CNavoCacheApp theApp;
CNavoLog oNavoLog;

/////////////////////////////////////////////////////////////////////////////
// CNavoCacheApp initialization
extern LPCTSTR pcCacheSettingsRegKey;
extern LPCTSTR pcCacheRootVal;

LPCTSTR _g_pcLogFileName = _T("navo2012.cache.log.txt");

BOOL CNavoCacheApp::InitInstance()
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

		NavoDeleteFile(oLogPathString);
		oNavoLog.Open(oLogPathString);
		oNavoLog << _T("NAVO Enterprise 2023 Cache is starting");
		oNavoLog << _T("command line is:") + CString(m_lpCmdLine);

		char * pActualLocale = ::setlocale(LC_ALL,"polish");
		VERIFY(pActualLocale != NULL);
		CParametersSplitter oParameterSplitter(m_lpCmdLine);
		if(oParameterSplitter.GetParameter("regserver"))
		{
			CString oCacheRootString;
			if(!oParameterSplitter.GetParameter("root",oCacheRootString))
			{
				AfxMessageBox(IDS_MISSINGROOT,MB_OK | MB_ICONEXCLAMATION);
				oNavoLog << _T("missing /root param");
				return FALSE;
			}
			try
			{
				NavoCreateDirectoryTree(oCacheRootString);
				CString oCacheSettingString = GetNAVO2001RootRegistryKeyName() + CString(pcCacheSettingsRegKey);
				SetRegistryKeyString(HKEY_LOCAL_MACHINE,oCacheSettingString,pcCacheRootVal,oCacheRootString);
			}
			catch(CNavoException & roNavoException)
			{
				AfxMessageBox(roNavoException.BuildCompleteErrorString(),MB_OK | MB_ICONEXCLAMATION);
				oNavoLog << _T("creating directory tree failed");
				return FALSE;
			}
			
			_g_CacheManagerServerClassFactory.InitModuleName(m_hInstance);
			_g_CacheManagerServerClassFactory.RegisterServer();
			oNavoLog << _T("registered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter("unregserver"))
		{
			CNavoOleInitHolder oNOIH(CNavoOleInitHolder::MULTITHREADED);
			CSingleServerPlaceCacheInfo::unsetup_indexing_service();
			_g_CacheManagerServerClassFactory.UnRegisterServer();
			oNavoLog << _T("unregistered OK");
			return FALSE;
		}
		if(oParameterSplitter.GetParameter("embedding"))
		{
			oNavoLog << _T("1. NOIH");
			m_poNOIHSP = NewSCP(new CNavoOleInitHolder(CNavoOleInitHolder::MULTITHREADED));
			oNavoLog << _T("2. CIS");
			HRESULT hr = ::CoInitializeSecurity(NULL,-1,NULL,NULL,
				DCOM_AUTH_LEVEL,RPC_C_IMP_LEVEL_IMPERSONATE,NULL,
				EOAC_NONE,
				NULL);

			if(hr != S_OK)
			{
				ThrowNavoException1(ERCO_CACHE_UNABLE_TO_INIT_SECURITY,
					IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
			}
			_g_CacheManagerServerClassFactory.Register();
			oNavoLog << _T("3. CF reg OK");
			_g_CacheManagerServerClassFactory.WaitForEnd();
			oNavoLog << _T("4. finished OK");
			_g_CacheManagerServerClassFactory.Revoke();
			oNavoLog << _T("5. revoke OK");
			_g_CacheManagerServerClassFactory.Uninitialize();
			m_poNOIHSP = 0;
			oNavoLog << _T("6. Cleaned");
			oNavoLog << _T("NAVO Enterprise 2023 Cache is stopped");
			oNavoLog << _T("errors are: ") + _g_CacheManagerServerClassFactory.m_oErrorStorage.BuildCompleteErrorString();
			return FALSE;
		}
	}
	TOP_ALL_CATCH_(oNavoException)
	
	oNavoLog << _T("NAVO Enterprise 2023 Cache is crashed or bad command line");
	oNavoLog << _T("errors are: ") + oNavoException.BuildCompleteErrorString();
	oNavoLog << _T("----------------------------------------------------------------------");

	return FALSE;
}
