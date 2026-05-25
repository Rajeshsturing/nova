/*
NAVO Enterprise 2008 (c)

24.07.2002

class:
cndoc_integrator

integruje podsystemy, trzyma connection do serwera itd
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\progressgadget.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\splashwindow.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoscript\CacheManagerUser.h"
#include "..\navoobj\dbapconnparam.h"
#include "..\navoobj\navoobjcoor.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\oleeventsink_ndoc.h"
using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"

#include "common_pageman.h"

#include "xmlpagecachemu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR _g_cFakePassword[] = _T("kasparow");
static TCHAR _g_cCodedPwd[] = _T("             ");

extern HINSTANCE _h_PAGEMAN_Instance;
void CopyEngineFiles(SCP<IStream> & rpoDataStreamSP, SCP<IStream> & rpoInfoStreamSP);

cndoc_integrator::cndoc_integrator(cndoc_application * poApplication) :
	m_poApplication(poApplication),
	m_dwCachedData_GIT_Cookie(0),
	m_dwAppDBManager_GIT_Cookie(0),
	m_dwPreprocessedDataCache_GIT_Cookie(0),
	m_nNotification_Cookie(0),
	m_nCachedData_PingCookie(0),
	m_bUI(false),
	m_bQuitting(false),
	m_nPage_IID(100000 /*wartoœæ dla stron z automatycznym iid - powy¿ej dozwolonego numeru strony */),
	m_poLateSwitchToTrans(NULL),
	m_dwLastUpdateMainView(0),
	m_dwLastUpdateOtherView(0)
{
	EnableAutomation();
}

cndoc_integrator::~cndoc_integrator()
{
}

class COccManager;

bool cndoc_integrator::initialize(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	//check OS version
	CWinVersion oWV;
	if (oWV.GetVersion() == CWinVersion::Win95)
	{
		ThrowNavoException(ERCO_SYSCHK_WIN98_OR_ABOVE_REQ, IDPAGE_NOTAVAILABLE);
	}

	SCP<CSplashWindow> poSplashWindowSP;

	{
		long nUserInterface = 1;
		rpoCommandHLISP->SafeGetNumProp(GVAR_UISTYLE, nUserInterface);
		//ju¿ w tym miejscu ustawiamy czy wolno pokazywaæ UI
		//jak coœ siê wywali, a wolno -> poka¿¹ siê komunikaty
		m_bUI = (nUserInterface != 0);
	}

	//both must exist
	m_oAppNameString = rpoCommandHLISP->GetStrProp(GVAR_APPLICATION);
	m_oServerString = rpoCommandHLISP->GetStrProp(GVAR_DBSERVER);

	//open log
	{
		//LANGUAGE: PL
		CString oLogNameString;
		oLogNameString.Format("%s-komunikaty", m_oAppNameString);

		CString oNormalizedString;
		normalize_name_4_path(oLogNameString, oNormalizedString);
		m_oLog.Open(oNormalizedString + ".txt");
		m_oLog << "Komenda startowa: " + rpoCommandHLISP->WriteToString();

		m_oLog << "Oryginalny katalog roboczy: " + NavoGetCurrentDir();
	}

	CString strInstallationRoot;
	SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), _T("InstallationRoot"), strInstallationRoot);
	EnsureEndingBackslash(strInstallationRoot);
	CString strWorkingDir = strInstallationRoot + _T("System");
	
	//NavoSetCurrentDir(strWorkingDir);
	
	m_oLog << "Aktualny katalog roboczy: " + NavoGetCurrentDir();

	if (is_UI())
	{
		//find splash image location
		CString oExtrasDirString = strInstallationRoot + _T("Applications\\") + m_oAppNameString + _T("\\Extras\\splash.jpg");
		poSplashWindowSP = NewSCP(new CSplashWindow(oExtrasDirString));
	}


	//get DB name or supply default if missing
	CString oDBNameString;
	if (!rpoCommandHLISP->SafeGetStrProp(GVAR_DBNAME, oDBNameString))
	{
		oDBNameString = "navo2002";
		rpoCommandHLISP->SetStrProp(GVAR_DBNAME, oDBNameString);
	}
	long nEngineType;
	if (!rpoCommandHLISP->SafeGetNumProp(GVAR_DBTYPE, nEngineType))
	{
		nEngineType = long(dbet_ms_sql70);
	}

	CString strTransport;
	if (!rpoCommandHLISP->SafeGetStrProp(GVAR_NET_TRANSPORT, strTransport))
	{
		strTransport = "dcom";
	}
	
	if (strTransport.MakeLower() == "nxm")
	{
		SetNXMTransport(true);
	}

	SCP<CPerformingDialogHolder> poPDHSP;

	//show 'wait' dialog
	if (is_UI())
	{
		CString oMsgString;
		{
			CAfxResourceHandleHolder oARHH(_h_PAGEMAN_Instance);
			oMsgString.Format(IDS_CONNECTING_TO_SERVER, get_server_name());
		}
		poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));
	}

	//------------------------------------- connect to server ---------------------------------
	HRESULT hr = S_OK;

	if (IsNXMTransport())
	{
		CLSID clsid;
		hr = CLSIDFromString(CBStr("{188CB16F-2012-4498-87D0-EBD8D9A00FB8}"), &clsid);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_CANNOT_CREATE_NXM_CLIENT, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		SCP<IServerClientFactory> poSCFSP;
		hr = CreateRemoteInstance(clsid, "", &poSCFSP.GetIID(), poSCFSP);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_CANNOT_CREATE_NXM_CLIENT, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}

		hr = poSCFSP->GetServerClient(get_server_name(), oDBNameString, &m_poServerClientSP.GetRawPointer());
		
		if (hr == S_OK)
		{
			m_poNXMNetDispatchSP.QueryInterface(m_poServerClientSP);
		}
		else
		{
			ThrowFromInterface(poSCFSP);
		}
	}
	else
	{
		hr = CreateRemoteInstance(CLSID_NAVO2001Server, get_server_name(), &m_poServerClientSP.GetIID(), m_poServerClientSP);
	}

	if (hr != S_OK)
	{
		ThrowNavoException2(ERCO_USERDOC_CANNOT_CREATE_SERVERCLIENT, IDPAGE_NOTAVAILABLE, get_server_name(), SCODE_To_String(hr));
	}

	ASSERT(m_poServerClientSP.PointsObject());
	long nCURes = __check_upgrade();
	if (nCURes != 1)
	{
		m_poApplication->set_exit_code(nCURes);
		return false;
	}

	//access GIT
	m_poGITSP.CreateInstance(CLSID_StdGlobalInterfaceTable, CLSCTX_INPROC_SERVER);

	{
		CString oServerUIDString;
		LPSTR lpServerUID;
		CRemoteFreeHolder oRFHName(lpServerUID);
		if (m_poServerClientSP->GetUniqueId(&lpServerUID) == S_OK)
		{
			oServerUIDString = lpServerUID;
			m_oCacheFullNameString.Format("%s:%s", oServerUIDString, get_app_name());
		}
		else
		{
#ifdef _DEBUG
			AfxMessageBox("Zarejestruj server z opcj¹ /regserver !");
#endif
			m_oCacheFullNameString.Format("%s:%s", get_server_name(), get_app_name());
		}
	}

	SCP<IUnknown> poUnknownSP;

	//------------------------------------- inicjowanie appdb managera -----------------------------
	hr = m_poServerClientSP->GetService(nst_appdb, &poUnknownSP.GetRawPointer());
	m_poAppDBManagerSP.QueryInterface(poUnknownSP);
	poUnknownSP = 0;
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_USERDOC_CANNOT_CREATE_APPDB, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}

	bool bSlowConnection = IsSlowConnection_Registry();

	hr = m_poAppDBManagerSP->Init(get_app_name());
	if (hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poAppDBManagerSP, oNavoException);
		ContinueThrowNavoException2(oNavoException, ERCO_USERDOC_CANNOT_INIT_APPDB,
			IDPAGE_NOTAVAILABLE, get_app_name(), SCODE_To_String(hr));
	}
	if (bSlowConnection)
	{
		VERIFY(S_OK == m_poAppDBManagerSP->SetOptions(UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT));
	}

	//------------------------------------- inicjowanie lokalnego cachea plików -----------------------------
	bool bEnableFileCache = true;
	{
		CString oDisableFileCacheString;
		SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(),
			"DisableFileCache", oDisableFileCacheString);
		bEnableFileCache = (oDisableFileCacheString != "Y");
	}

	//fill GIT
	ASSERT(m_poGITSP.PointsObject());
	VERIFY(S_OK == m_poGITSP->RegisterInterfaceInGlobal(m_poAppDBManagerSP.Get(), m_poAppDBManagerSP.GetIID(),
		&m_dwAppDBManager_GIT_Cookie));

	if (bEnableFileCache && !IsSetupAppName(get_app_name()))
	{
		//file cache is always local
		m_poCachedDataSP.CreateInstance(CLSID_NAVO2001_CacheServer, CLSCTX_ALL);
		m_nCachedData_PingCookie = AdvisePingServer(GetUnknown(), m_poCachedDataSP);
		ASSERT(m_nCachedData_PingCookie);
		VERIFY(S_OK == m_poGITSP->RegisterInterfaceInGlobal(m_poCachedDataSP.Get(), m_poCachedDataSP.GetIID(),
			&m_dwCachedData_GIT_Cookie));
	}

	m_poPreprocessedDataCacheSP.CreateInstance(CLSID_NAVO2002PreprocessedDataCache, CLSCTX_ALL);
	VERIFY(S_OK == m_poGITSP->RegisterInterfaceInGlobal(m_poPreprocessedDataCacheSP.Get(), m_poPreprocessedDataCacheSP.GetIID(),
		&m_dwPreprocessedDataCache_GIT_Cookie));

	//------------------------------------- inicjowanie areny  -----------------------------
	COccManager * get_occmaganer();
	AfxEnableControlContainer(get_occmaganer());

	//always create arena as windows holder (which in turn is page/module holder)
	m_poArenaIntegratorSP = NewSCP(new cned_arena_integrator());
	m_poMainArenaSP = m_poArenaIntegratorSP->create_arena();
	m_poMainArenaSP->set_providers(get_full_cache_name(), m_poGITSP, m_dwAppDBManager_GIT_Cookie, m_dwCachedData_GIT_Cookie);

	if (is_UI())
	{
		_initialize_standard_ui();
	}
	//------------------------------------- inicjowanie stdobj-definition managera -----------------------------
	//uwaga na kolejnosc - poszczegolne elementy musza byc inicjowane 
	//w precyzyjnie dobranej kolejnosci
	_init_NX();

	{

		m_poDefinitionManagerSP = NewSCP(new CDefinitionManager());
		SCP<IDispatch> poUserThreadSP = NewSCP(m_poApplication->GetIDispatch(TRUE), false);
		m_poDefinitionManagerSP->SetDOC_Dispatch(poUserThreadSP);
		SCP<IStream> poClassDefinitionStreamSP;

		//spróbuj z cache'a
		SCP<CCacheManagerUser> poCacheManUserSP =
			NewSCP(new CCacheManagerUser(get_full_cache_name(), m_poCachedDataSP, m_poAppDBManagerSP,
				NewSCP<CPropertyProvider__>(new CHyperLinkInfo()), IDPAGE_CLASSDEF));

		CCacheUserHolder oCUH(poCacheManUserSP);
		SCP<IDispatch> poNXDispatchSP = get_NX();
		m_poDefinitionManagerSP->SetNX_Dispatch(poNXDispatchSP);
		m_poDefinitionManagerSP->InitializeFrom(oCUH.get_stream().Get());
		oCUH.OK();
	}

	//------------------------------------- connect to object coordinator / transaction provider
	{

		CDBAP_ConnectionParam oConnectionParam;
		oConnectionParam.m_poServerClientSP = m_poServerClientSP;
		oConnectionParam.m_lpDBName = oDBNameString;
		if (_g_cCodedPwd[0] == ' ')
		{
			_g_cCodedPwd[4] = '0';
			_g_cCodedPwd[3] = TCHAR('0' + 1);
			_g_cCodedPwd[8] = '3';
			_g_cCodedPwd[5] = 'x';
			_g_cCodedPwd[7] = TCHAR('U' + 'a' - 'A');
			_g_cCodedPwd[0] = 'y';
			_g_cCodedPwd[1] = '7';
			_g_cCodedPwd[6] = 'r';
			_g_cCodedPwd[9] = '\0';
			_g_cCodedPwd[2] = '4';
		}
		oConnectionParam.m_lpPassword = _T("abc@123.123");
		oConnectionParam.m_lpPassword = _g_cCodedPwd;
		oConnectionParam.m_lpUserName = "navo2002user";
		oConnectionParam.m_lpServerName = get_server_name();
		oConnectionParam.m_lpAppName = get_app_name();
		oConnectionParam.m_nEngineType = nEngineType;
		oConnectionParam.m_bCompressTrafficToClient = bSlowConnection;

		m_poNavoObjCoorSP = NewSCP(new CNavoObjectCoordinator(m_poApplication->GetErrorStorage()));

		m_poNavoObjCoorSP->Connect(oConnectionParam, m_poDefinitionManagerSP);
		m_poNavoObjCoorSP->SetShowUI(is_UI());
	}

	//------------------------------------- inicjowanie notify-manager'a -----------------------------
	{
		SCP<IUnknown> poUnknownSP;
		SCP<CHyperLinkInfo> poEnvHLISP = GetSystemEnvironmentHLI();
		HRESULT hr = m_poServerClientSP->GetService(nst_notman, &poUnknownSP.GetRawPointer());
		m_poNotificationManagerSP.QueryInterface(poUnknownSP);
		poUnknownSP = 0;
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_USERDOC_CANNOT_CREATE_NOTIFMANAGER, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		ASSERT(m_poNotificationManagerSP.PointsObject());
		SCP<INotificationSink> poThisNotificationSinkSP;
		poThisNotificationSinkSP.QueryInterface(GetUnknown());
		hr = m_poServerClientSP->AdviseNM(poThisNotificationSinkSP.Get(),
			poEnvHLISP->GetStrProp(GVAR_OSUSERNAME), poEnvHLISP->GetStrProp(GVAR_MACHINE),
			nsc_document, &m_nNotification_Cookie);

		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_USERDOC_NOTIFMANAGER_ADVISE_FAILED, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
	}

	//init AFC
	_init_AFC(nEngineType);

	m_poNavoObjCoorSP->_set_NX_dispatch(m_poNXDispatchSP);
	return true;
}

void cndoc_integrator::done()
{
	//destroy arenas
	m_poMainArenaSP = 0;
	m_poOutlookBarArenaSP = 0;
	m_poToolbarArenaSP = 0;

	//and finally arena-integrator
	m_poArenaIntegratorSP = 0;

	//finalize_ui should already called
	ASSERT(m_poToolbarStackSP.PointsNull());

	if (!m_poNXMNetDispatchSP.PointsNull())
	{
		m_poNXMNetDispatchSP = 0;
	}

	_done_NX();
	_done_AFC();

	if (m_poNavoObjCoorSP.PointsObject())
	{
		m_poNavoObjCoorSP->Disconnect();
		m_poNavoObjCoorSP = 0;
	}
	//clean GIT
	if (m_poGITSP.PointsObject())
	{
		if (m_dwCachedData_GIT_Cookie != 0)
		{
			VERIFY(S_OK == m_poGITSP->RevokeInterfaceFromGlobal(m_dwCachedData_GIT_Cookie));
			m_dwCachedData_GIT_Cookie = 0;
		}
		if (m_dwAppDBManager_GIT_Cookie != 0)
		{
			VERIFY(S_OK == m_poGITSP->RevokeInterfaceFromGlobal(m_dwAppDBManager_GIT_Cookie));
			m_dwAppDBManager_GIT_Cookie = 0;
		}
		if (m_dwPreprocessedDataCache_GIT_Cookie != 0)
		{
			VERIFY(S_OK == m_poGITSP->RevokeInterfaceFromGlobal(m_dwPreprocessedDataCache_GIT_Cookie));
			m_dwPreprocessedDataCache_GIT_Cookie = 0;
		}
		m_poGITSP = 0;
	}
	//clean local cache
	if (m_poCachedDataSP.PointsObject())
	{
		UnAdvisePingServer(m_poCachedDataSP, m_nCachedData_PingCookie);
		VERIFY(S_OK == m_poCachedDataSP->Close(BYTE(true)));
		m_poCachedDataSP = 0;
	}
	m_nCachedData_PingCookie = 0;

	//clean notification manager'a
	if (m_poNotificationManagerSP.PointsObject())
	{
		HRESULT hr = m_poServerClientSP->UnAdviseNM(m_nNotification_Cookie);
		m_poNotificationManagerSP = 0;
		ASSERT(hr == S_OK);		//to_do: obs³uga b³êdów
	}
	m_nNotification_Cookie = 0;

	if (m_poDefinitionManagerSP.PointsObject())
	{
		m_poDefinitionManagerSP->QuasiDtor();
	}
	m_poDefinitionManagerSP = 0;

	m_poAppDBManagerSP = 0;

	m_poPreprocessedDataCacheSP = 0;
	
	if (IsNXMTransport())
	{
		m_poServerClientSP->Close2();
	}

	m_poServerClientSP = 0;

	m_oLog.Close();
}



void cndoc_integrator::_init_AFC(long nEngineType)
{
	ASSERT(m_poAFCDispatchSP.PointsNull());
	ASSERT(m_poApplication != NULL);

	CLSID oCLSID;
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(_T("navoafc.afc")), &oCLSID);
	if (hr != S_OK)
	{
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poAFCDispatchSP.CreateInstance(oCLSID, CLSCTX_INPROC_SERVER);

	//register doc_ object
	DISPID dispid = DispatchGetIdOfName(m_poAFCDispatchSP, L"initdoc_");
	EXCEPINFO ei;

	CSmartOleVariant oArgumentSOVArray[2];
	oArgumentSOVArray[1] = CSmartOleVariant(m_poApplication->GetIDispatch(TRUE), false);
	oArgumentSOVArray[0] = CSmartOleVariant(nEngineType, VT_I4);

	HRESULT hResult = DispatchInvoke(m_poAFCDispatchSP, dispid, oArgumentSOVArray, 2, NULL, &ei);

	if (hResult != S_OK)
	{
		//to_do
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poNavoObjCoorSP->_set_AFC_dispatch(m_poAFCDispatchSP);
}

void cndoc_integrator::_done_AFC()
{
	if (m_poAFCDispatchSP.PointsNull())
	{
		return;
	}
	//deregister doc_ object
	DISPID dispid = DispatchGetIdOfName(m_poAFCDispatchSP, L"donedoc_");
	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poAFCDispatchSP, dispid, NULL, 0, NULL, &ei);
	if (hResult != S_OK)
	{
		//to_do
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}

	m_poAFCDispatchSP = 0;
	if (m_poNavoObjCoorSP.PointsObject())
	{
		m_poNavoObjCoorSP->_set_AFC_dispatch(m_poAFCDispatchSP);
	}
}

void cndoc_integrator::_init_NX()
{
	ASSERT(m_poNXDispatchSP.PointsNull());
	ASSERT(m_poApplication != NULL);

	CLSID oCLSID;
	HRESULT hr = CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(_T("nxhub.hub")), &oCLSID);
	if (hr != S_OK)
	{
		ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
	}
	m_poNXDispatchSP.CreateInstance(oCLSID, CLSCTX_INPROC_SERVER);

}

void cndoc_integrator::_done_NX()
{
	if (m_poNXDispatchSP.PointsNull())
	{
		return;
	}

	m_poNXDispatchSP = 0;

	if (m_poNavoObjCoorSP.PointsObject())
	{
		m_poNavoObjCoorSP->_set_NX_dispatch(m_poNXDispatchSP);
	}
}

long cndoc_integrator::__check_upgrade()
{
	return 1;	//means OK
	//ASSERT(m_poServerClientSP.PointsObject());
	////-------------------------------------  perform upgrade if neccessary
	//SCP<IStream> poDataStreamSP;
	//SCP<IStream> poInfoStreamSP;
	//HRESULT hr = m_poServerClientSP->GetUpdateVersionIfNewer(0/*engine*/, GetNAVO2001EngineVersion(),
	//	&poDataStreamSP.GetRawPointer(), &poInfoStreamSP.GetRawPointer());
	//switch (hr)
	//{
	//case S_OK:
	//	if (poDataStreamSP.PointsObject())	//newer version !!!
	//	{
	//		CAfxResourceHandleHolder oARHH(_h_PAGEMAN_Instance);
	//		if (AfxMessageBox(IDS_SERVER_IS_NEWER_DOWNLOAD, MB_ICONQUESTION | MB_YESNO) != IDYES)
	//		{
	//			return 0;	//means: exit
	//		}
	//		ASSERT(poInfoStreamSP.PointsObject());
	//		CopyEngineFiles(poDataStreamSP, poInfoStreamSP);
	//		//new version ready for update
	//		return -4;		//means: run setup /checkcore
	//	}
	//	break;
	//case S_FALSE:
	//	break;
	//	//ThrowNavoException1(ERCO_CLIENT_ENGINE_VERSION_NEWER,IDPAGE_NOTAVAILABLE,m_oServerString);
	//default:
	//{
	//	CNavoException oNavoException;
	//	GetErrorInfoFromInterface(m_poServerClientSP, oNavoException);
	//	ContinueThrowNavoException1(oNavoException, ERCO_UPDATE_ENGINE_VERSION_FAILED, IDPAGE_NOTAVAILABLE, m_oServerString);
	//}
	//}

	//return 1;	//means OK
}

SCP<CPageCacheManagerUser> cndoc_integrator::get_pcmu(long IdFile, SCP<CPropertyProvider__> & rpoHLISP)
{
	ASSERT(rpoHLISP.PointsObject());

	//acquire pointers from GIT
	ASSERT(m_poGITSP.PointsObject());
	SCP<ICachedData> poCachedDataSP;
	if (m_dwCachedData_GIT_Cookie != 0)	//cache may be disabled
	{
		VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwCachedData_GIT_Cookie,
			poCachedDataSP.GetIID(),
			reinterpret_cast<void**>(&poCachedDataSP.GetRawPointer())));
	}

	ASSERT(m_dwAppDBManager_GIT_Cookie != 0);
	SCP<IAppDBManager>	poAppDBManagerSP;
	VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwAppDBManager_GIT_Cookie,
		poAppDBManagerSP.GetIID(),
		reinterpret_cast<void**>(&poAppDBManagerSP.GetRawPointer())));

	ASSERT(m_dwPreprocessedDataCache_GIT_Cookie != 0);
	SCP<IPreprocessedDataCache>	poPreprocessedDataCacheSP;
	VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwPreprocessedDataCache_GIT_Cookie,
		poPreprocessedDataCacheSP.GetIID(),
		reinterpret_cast<void**>(&poPreprocessedDataCacheSP.GetRawPointer())));


	SCP<CPageCacheManagerUser> poPageCacheManagerUserSP =
		NewSCP(new CPageCacheManagerUser(m_poApplication->GetErrorStorage(),
			get_full_cache_name(), poCachedDataSP, poAppDBManagerSP, poPreprocessedDataCacheSP,
			rpoHLISP, IdFile));

	return poPageCacheManagerUserSP;
}

SCP<IStream> cndoc_integrator::get_raw_app_file(long IdFile)
{
	ASSERT(m_dwAppDBManager_GIT_Cookie != 0);
	SCP<IAppDBManager>	poAppDBManagerSP;
	VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwAppDBManager_GIT_Cookie,
		poAppDBManagerSP.GetIID(),
		reinterpret_cast<void**>(&poAppDBManagerSP.GetRawPointer())));

	SCP<IStreamProvider> poStreamProviderSP;
	poStreamProviderSP.QueryInterface(poAppDBManagerSP);

	SCP<IStream> poStreamSP;
	navostreaminfo oNSI;
	_init_navostreaminfo(oNSI);
	HRESULT hr = poStreamProviderSP->Get(IdFile, &poStreamSP.GetRawPointer(), &oNSI);
	if (hr != S_OK)
	{
		ThrowFromInterface(poStreamProviderSP);
	}
	ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if (oNSI.m_bCompressed == '1')
	{
		poStreamSP = UncompressStream(poStreamSP);
	}
	return poStreamSP;
}


void cndoc_integrator::yield()
{
	_mark_update_views(false);
	m_poApplication->yield();
}

void cndoc_integrator::exit_yield()
{
	m_poApplication->exit_yield();
}

void cndoc_integrator::update_ui_now()
{
	_perform_update_views(true);
	m_poApplication->update_ui_now();
}

void cndoc_integrator::_pop_all_not_modal_pages()
{
restart:
	for (long iter = 0; iter <= m_oAppStackArray.GetUpperBound(); iter++)
	{
		if (!m_oAppStackArray[iter]->is_empty())
		{
			if (!m_oAppStackArray[iter]->get_top_page()->is_in_modal_loop())
			{
				m_oAppStackArray[iter]->pop();
				goto restart;
			}
		}
	}
}

SCP<cndoc_page__> cndoc_integrator::_find_page_on_iid(long nIID)
{
	//start with active stack
	for (long iter = m_oAppStackArray.GetUpperBound(); iter >= 0; iter--)
	{
		SCP<cndoc_page__> poPageSP = m_oAppStackArray[iter]->find_page_on_iid(nIID);
		if (poPageSP.PointsObject())
		{
			return poPageSP;
		}
	}
	if (m_poOutlookBarStackSP.PointsObject())
	{
		SCP<cndoc_page__> poPageSP = m_poOutlookBarStackSP->find_page_on_iid(nIID);
		if (poPageSP.PointsObject())
		{
			return poPageSP;
		}
	}
	if (m_poToolbarStackSP.PointsObject())
	{
		SCP<cndoc_page__> poPageSP = m_poToolbarStackSP->find_page_on_iid(nIID);
		if (poPageSP.PointsObject())
		{
			return poPageSP;
		}
	}
	return SCP<cndoc_page__>();
}

bool cndoc_integrator::on_idle()
{
	_perform_update_views(false);

	//	__check_memory_state();

	return false;

	if (!_is_any_stack())
	{
		return false;
	}

	//active stack = last in array
	bool bResult = false;

	for (long iter = 0; iter < m_oAppStackArray.GetUpperBound(); iter++)
	{
		bResult = bResult | m_oAppStackArray[iter]->on_idle(false);
	}

	return bResult | _get_active_stack()->on_idle(true);
}

static SCP<CHyperLinkInfo> _get_appglobalmodule_hli()
{
	SCP<CHyperLinkInfo> poCmdHLISP = NewSCP(new CHyperLinkInfo());
	poCmdHLISP->SetNumProp(GVAR_NEWTHREAD, 1);
	poCmdHLISP->SetNumProp(GVAR_CMD, CMD_OPEN_RECORD_PAGE);
	poCmdHLISP->SetNumProp(GVAR_DESTPAGE, IDPAGE_APPGLOBALMODULE);

	return poCmdHLISP;
}

static void _cocoon_native_diag(const CString & roMessage)
{
	try
	{
		CFile oFile;
		if (!oFile.Open(_T("C:\\app\\navo-native-diagnostics.log"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			return;
		}

		oFile.SeekToEnd();
		CString oLine;
		CTime oNow = CTime::GetCurrentTime();
		oLine.Format(_T("%s [integrator_ndoc] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

static bool _is_cocoon_login_start_page(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	long nStartPage = 0;
	if (!rpoCommandHLISP->SafeGetNumProp(GVAR_DESTPAGE, nStartPage))
	{
		return false;
	}

	return nStartPage >= 72000 && nStartPage <= 72008;
}

bool cndoc_integrator::__on_app_start(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	_cocoon_native_diag(CString(_T("__on_app_start begin input=")) + rpoCommandHLISP->WriteToString());

	SCP<CHyperLinkInfo> poCmdHLISP = NewSCP(new CHyperLinkInfo());
	//copy command line
	(*poCmdHLISP) = (*rpoCommandHLISP);
	//apply our vars
	(*poCmdHLISP) += (*_get_appglobalmodule_hli());
	_cocoon_native_diag(CString(_T("__on_app_start appglobal_hli=")) + poCmdHLISP->WriteToString());
	//use it to start
	SCP<cndoc_page__> poModuleSP = create_page(poCmdHLISP);
	_cocoon_native_diag(CString(_T("__on_app_start create_page object=")) + (poModuleSP.PointsObject() ? _T("yes") : _T("no")));
	if (poModuleSP.PointsObject())
	{
		SCP<IDispatch> poModuleDispatchSP = poModuleSP->GetDispatchSP();
		CSmartOleVariant oArgumentSOV(rpoCommandHLISP->GetIDispatch(TRUE), false);
		CSmartOleVariant oAnswerSOV;
		DISPID dispidAppOnStart = DISPID_UNKNOWN;
		CBStr oAppOnStartName(_T("app_onstart"));

		if (!SafeDispatchGetIdOfName(poModuleDispatchSP, oAppOnStartName, dispidAppOnStart))
		{
			_cocoon_native_diag(_T("__on_app_start app_onstart missing from appglobal dispatch"));

			if (_is_cocoon_login_start_page(rpoCommandHLISP))
			{
				_cocoon_native_diag(_T("__on_app_start tolerated missing app_onstart for startup page"));
				return true;
			}

			DispatchGetIdOfName(poModuleDispatchSP, oAppOnStartName);
		}

		_cocoon_native_diag(_T("__on_app_start invoking app_onstart"));
		DispatchInvoke(poModuleDispatchSP,
			dispidAppOnStart,
			&oArgumentSOV, 1, &oAnswerSOV, NULL);

		if (oAnswerSOV.Type() == VT_BOOL)
		{
			_cocoon_native_diag(CString(_T("__on_app_start result=")) + (oAnswerSOV.GetBool() ? _T("true") : _T("false")));
			return oAnswerSOV.GetBool();
		}
		_cocoon_native_diag(_T("__on_app_start result was not VT_BOOL"));
	}
	_cocoon_native_diag(_T("__on_app_start default true"));
	return true;
}

void cndoc_integrator::__on_app_exit()
{
	_cocoon_native_diag(_T("__on_app_exit begin"));

	SCP<cndoc_page__> poModuleSP = create_page(_get_appglobalmodule_hli());
	if (poModuleSP.PointsObject())
	{
		SCP<IDispatch> poModuleDispatchSP = poModuleSP->GetDispatchSP();
		DISPID dispidAppOnExit = DISPID_UNKNOWN;
		CBStr oAppOnExitName(_T("app_onexit"));
		if (!SafeDispatchGetIdOfName(poModuleDispatchSP, oAppOnExitName, dispidAppOnExit))
		{
			_cocoon_native_diag(_T("__on_app_exit app_onexit missing from appglobal dispatch"));
			return;
		}

		DispatchInvoke(poModuleDispatchSP,
			dispidAppOnExit,
			NULL, 0, NULL, NULL);
	}
	_cocoon_native_diag(_T("__on_app_exit end"));
}

