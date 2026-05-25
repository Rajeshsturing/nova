/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	NAVO Server Class Factory (singleton)
*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\appdb\_impnavobrman.h"
#include "navoserverclassfactory.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNavoLog oNavoLog;

static CString get_dle()
{
	COleDateTime oDT = COleDateTime::GetCurrentTime();
	CString oNowString;
	oNowString.Format(_T("%04d%02d%02d%02d%02d%02d"),
		oDT.GetYear(), oDT.GetMonth(), oDT.GetDay(), oDT.GetHour(), oDT.GetMinute(), oDT.GetSecond());
	return oNowString;
}

static void encode_dle(const CString & roPlainString, CString & roEncodedString)
{
	roEncodedString = CString(' ', 14);
	for (long iter = 0; iter < roPlainString.GetLength(); iter++)
	{
		roEncodedString.SetAt(iter, char(roPlainString.GetAt(iter) + 'a'));
	}
}

static bool decode_dle(const CString & roEncodedString, CString & roPlainString)
{
	if (roEncodedString.IsEmpty())
	{
		return false;
	}
	if (roEncodedString.GetLength() != 14)
	{
		return false;
	}
	roPlainString = CString(' ', 14);
	for (long iter = 0; iter < roEncodedString.GetLength(); iter++)
	{
		roPlainString.SetAt(iter, char(roEncodedString.GetAt(iter) - 'a'));
	}
	return true;	//means: valid
}

/*
	single class factory for whole server and all subsystems
*/

extern CNavoLog oNavoLog;

CNavoServerCF::CNavoServerCF(CNavoLog & roLog, bool bAsService) :
	CNavoClassFactory(m_oErrorStorage, CLSID_NAVO2001Server,
		_T("navo2002.server"), _T(""), true, true),
	m_nClientCount(0),
	m_bWasFailedClients(false),
	m_roLog(roLog)
{
	if (bAsService)
	{
		_set_run_as_service();
	}
	ASSERT(reinterpret_cast<long>(&m_nClientCount) % 4 == 0);	//must be 32-bit aligned
}

void CNavoServerCF::RegisterServer()
{
	//first analyze DLE
	CString oEncodedDLEString;
	CString oDecodedDLEString;
	VERIFY(ERROR_SUCCESS == SafeGetRegistryKeyString(HKEY_CLASSES_ROOT,
		_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"), _T("DLE"), oEncodedDLEString));
	if (!decode_dle(oEncodedDLEString, oDecodedDLEString))
	{
		oDecodedDLEString = "";
	}

	CString oNowString = get_dle();
	if (oNowString > oDecodedDLEString)
	{
		encode_dle(oNowString, oEncodedDLEString);
		SetRegistryKeyString(HKEY_CLASSES_ROOT,
			_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"), _T("DLE"), oEncodedDLEString);
	}

	CNavoClassFactory::RegisterServer();

	SetRegistryKeyString(HKEY_CLASSES_ROOT,
		_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"), _T(""), _T("navo2002.server"));

	/*
	BYTE ucaLaunchPermission[] =
	{
		0x01,0x00,0x04,0x80,0x30,0x00,0x00,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,
		0x00,0x00,0x02,0x00,0x1c,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
		0x01,0x00,0x00,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,0x2e,0x6b,0x49,
		0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,
		0x2e,0x6b,0x49,0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00
	};
	SetRegistryKeyBinary(HKEY_CLASSES_ROOT,
			_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"),_T("LaunchPermission"),
		ucaLaunchPermission,sizeof(ucaLaunchPermission)/sizeof(ucaLaunchPermission[0]));

	BYTE ucaAccessPermission[] =
	{
		0x01,0x00,0x04,0x80,0x30,0x00,0x00,0x00,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,
		0x00,0x00,0x02,0x00,0x1c,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
		0x01,0x00,0x00,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,0x2e,0x6b,0x49,
		0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00,0x01,0x05,0x00,0x00,0x00,0x00,0x00,0x05,0x15,0x00,0x00,0x00,0xa0,0x5f,0x84,0x1f,0x5e,
		0x2e,0x6b,0x49,0xce,0x12,0x03,0x03,0xf4,0x01,0x00,0x00
	};
	SetRegistryKeyBinary(HKEY_CLASSES_ROOT,
		_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"),
		_T("AccessPermission"),
		ucaAccessPermission,sizeof(ucaAccessPermission)/sizeof(ucaAccessPermission[0]));
	*/

	//SetRegistryKeyString(HKEY_CLASSES_ROOT,
	//	_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"),
	//	_T("RunAs"),
	//	//_T("Interactive User"));
	//	_T(""));

	GUID oMainGUID;
	VERIFY(S_OK == ::CoCreateGuid(&oMainGUID));
	CString oGUIDString = StringFromCLSID(oMainGUID);
	SetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(), _T("MainUID"), oGUIDString);
}

void CNavoServerCF::InitModuleName(HINSTANCE hInstance)
{
	TCHAR cBuffer[_MAX_PATH];
	VERIFY(::GetModuleFileName(hInstance, cBuffer, sizeof(cBuffer)) != 0);
	m_oLocalServerPathString = cBuffer;
}

//-------------------------------------------------------------------------------------------

SCP <IUnknown> CNavoServerCF::OnCreateObject()
{
	if (m_roLog.IsHandleValid())
	{
		m_roLog << "new client attempt, count for now=" + Long2String(m_nClientCount);
	}

	SCP<CServerClientObject> poSCOSP = NewSCP(new CServerClientObject());

	SCP<IUnknown> poUnknownSP = poSCOSP->GetUnknownSP();
	ASSERT(poUnknownSP.PointsObject());

	if (::InterlockedIncrement(&m_nClientCount) == 1)
	{
		m_oStartedEvent.SetEvent();
	}
	return poUnknownSP;
}

void CNavoServerCF::OnFinalReleaseObject(CServerClientObject * poSCO)
{
	if (m_roLog.IsHandleValid())
	{
		m_roLog << "releasing client, count for now=" + Long2String(m_nClientCount);
	}
	if (::InterlockedDecrement(&m_nClientCount) == 0)
	{
		m_oFinishedEvent.SetEvent();
	}
}

//-------------------------------------------------------------------------------------------

void CNavoServerCF::WaitForEnd()
{
	DWORD dwTimeOut =
#ifdef _DEBUG
		10000;
#else
		5000;
#endif
	CSingleLock oSingleLock(&m_oFinishedEvent);
	while (!oSingleLock.Lock(dwTimeOut))
	{
		m_oPingServer.__PerformPingTest(oNavoLog);
	}
}

bool CNavoServerCF::Initialize()
{
	oNavoLog << _T("checking system");

	CString oEncodedDLEString;
	CString oDecodedDLEString;
	VERIFY(ERROR_SUCCESS == SafeGetRegistryKeyString(HKEY_CLASSES_ROOT,
		_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"),
		_T("DLE"), oEncodedDLEString));
	if (!decode_dle(oEncodedDLEString, oDecodedDLEString))
	{
		oNavoLog << _T("invalid system time");
		return false;
	}

	CString oNowString = get_dle();
	if (oNowString < oDecodedDLEString)
	{
		oNavoLog << _T("invalid system time");
		return false;
	}

	if (!m_oMRD.Init("Global\\NAVOSERVER"))
	{
		oNavoLog << _T("other instance of NAVOSERVER is running");
		return false;
	}

	oNavoLog << _T("initializing lockmanager");
	m_poLockManagerSP.CreateInstance(CLSID_NAVO2001LockManager, CLSCTX_INPROC_SERVER);

	oNavoLog << _T("initializing notmanager");
	m_poNofiManagerSP.CreateInstance(CLSID_NAVO2001NotificationManager, CLSCTX_INPROC_SERVER);

	oNavoLog << _T("all shared subsystems initialized");
	return true;
}

void CNavoServerCF::Uninitialize()
{
	ASSERT(m_oPingServer.IsEmpty());
	//posprz¹taj ewentualne padaki

	/*
	if(m_bWasFailedClients && m_poLockManagerSP.PointsObject())
	{
		_force_release(m_poLockManagerSP.Get());
	}
	*/
	m_poLockManagerSP = 0;

	if (m_poNofiManagerSP.PointsObject())
	{
		VERIFY(S_OK == m_poNofiManagerSP->Close());
		m_poNofiManagerSP = 0;
	}

	CString oNowString = get_dle();
	CString oEncodedDLEString;
	encode_dle(oNowString, oEncodedDLEString);
	SetRegistryKeyString(HKEY_CLASSES_ROOT,
		_T("AppID\\{188CB16F-82A4-4498-87D0-EBD8D9A00FB8}"), _T("DLE"), oEncodedDLEString);
}

/*
	server representation of connected client
*/

CServerClientObject::CServerClientObject() :
	m_nLockManagerCookie(0),
	m_nNotManCookie(0),
	m_bCallFinalRelease(true)
{
	AfxOleLockApp();
	EnableAutomation();

	if (oNavoLog.IsHandleValid())
	{
		oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":ctor";
	}
}

CServerClientObject::~CServerClientObject()
{
	if (oNavoLog.IsHandleValid())
	{
		oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":dtor1";
	}

	_clean_up(true);

	ASSERT(m_poObjectServerSP.PointsNull());
	ASSERT(m_poAppDBManagerSP.PointsNull());

	//wypisz niewypisane b³êdy
	CNavoExceptionAccessor oNEAH(GetErrorStorage());
	if (oNEAH.ErrorInfoArray().GetSize() > 0)
	{
		oNavoLog << GetErrorStorage().BuildCompleteErrorString();
	}

	AfxOleUnlockApp();

	if (oNavoLog.IsHandleValid())
	{
		oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":dtor2";
	}
}

void CServerClientObject::_clean_up(bool bNormal)
{
	if (oNavoLog.IsHandleValid())
	{
		if (bNormal)
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":entring _clean_up, normal mode";
		}
		else
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":entring _clean_up, KILL mode";
		}
	}

	//clean all subsystems

	/*
		to jest przyk³adowy kod, który zamyka po³¹cznie w trybie "force"

		if(!m_bCleanExit && m_poObjectServerSP.PointsObject())
		{
			m_poObjectServerSP->Close(false);
			_force_release(m_poObjectServerSP.Get());
		}
	*/

	if (m_poObjectServerSP.PointsObject())
	{
		VERIFY(S_OK == m_poObjectServerSP->Close(BYTE(bNormal)));
		m_poObjectServerSP = 0;

		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":ObjectServer cleaned";
		}
	}

	if (m_poAppDBManagerSP.PointsObject())
	{
		VERIFY(S_OK == m_poAppDBManagerSP->Close(BYTE(bNormal)));
		m_poAppDBManagerSP = 0;
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":AppDBManager cleaned";
		}
	}

	if (m_nLockManagerCookie != 0)	//wyczyœæ klienta lockmanagera
	{
		ASSERT(_g_NAVOServerCF.m_poLockManagerSP.PointsObject());
		VERIFY(S_OK == _g_NAVOServerCF.m_poLockManagerSP->UnAdvise(m_nLockManagerCookie));
		m_nLockManagerCookie = 0;

		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":LockManager cleaned";
		}
	}
	if (m_nNotManCookie != 0)
	{
		ASSERT(_g_NAVOServerCF.m_poNofiManagerSP.PointsObject());
		VERIFY(S_OK == _g_NAVOServerCF.m_poNofiManagerSP->UnAdvise(m_nNotManCookie));
		m_nNotManCookie = 0;

		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":NotificationManager cleaned";
		}
	}
	if (m_bCallFinalRelease)
	{
		_g_NAVOServerCF.OnFinalReleaseObject(this);
		m_bCallFinalRelease = false;
	}
	if (oNavoLog.IsHandleValid())
	{
		oNavoLog << Long2String(this->_get_pseudo_cookie()) + ":leaving _clean_up";
	}
}

DELEGATE_UNKNOWN_INTERFACE(CServerClientObject, ServerClient)
DELEGATE_UNKNOWN_INTERFACE(CServerClientObject, PingServer)


BEGIN_INTERFACE_MAP(CServerClientObject, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CServerClientObject, IID_IPingServer, PingServer)
	INTERFACE_PART(CServerClientObject, IID_IServerClient, ServerClient)
END_INTERFACE_MAP()

//----------------------------------------------------------
//		IServerClient implementation
//----------------------------------------------------------

STDMETHODIMP CServerClientObject::XServerClient::
GetService(navoservicetype eNST, IUnknown ** ppUnknown)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(pThis->_get_pseudo_cookie()) + ":GetService:" + Long2String(long(eNST));
		}

		switch (eNST)
		{
		case nst_notman:
		{
			SCP<IUnknown> poIUnknownSP;
			poIUnknownSP.QueryInterface(_g_NAVOServerCF.m_poNofiManagerSP);
			*ppUnknown = poIUnknownSP.Detach();
		}
		break;
		case nst_lockman:
		{
			SCP<IUnknown> poIUnknownSP;
			poIUnknownSP.QueryInterface(_g_NAVOServerCF.m_poLockManagerSP);
			*ppUnknown = poIUnknownSP.Detach();
		}
		break;
		case nst_appdb:
		{
			pThis->m_poAppDBManagerSP.CreateInstance(CLSID_NAVO2001AppDBManager, CLSCTX_INPROC_SERVER);
			SCP<IUnknown> poIUnknownSP;
			poIUnknownSP.QueryInterface(pThis->m_poAppDBManagerSP);
			*ppUnknown = poIUnknownSP.Detach();
		}
		break;
		case nst_brman:
		{
			ASSERT(false); //to_do
		}
		break;
		case nst_objserver:
		{
			pThis->m_poObjectServerSP.CreateInstance(CLSID_NAVO2001_ObjectServer, CLSCTX_INPROC_SERVER);
			SCP<IUnknown> poIUnknownSP;
			poIUnknownSP.QueryInterface(pThis->m_poObjectServerSP);
			*ppUnknown = poIUnknownSP.Detach();
		}
		break;
		default:
			ASSERT(false);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

const TCHAR * _g_pchNAVO2001Engine = _T("System");

STDMETHODIMP CServerClientObject::XServerClient::
GetUpdateVersionIfNewer(long nUpdateType, LPCTSTR lpClientVersion,
	IStream ** ppDataStream, IStream ** ppInfoStream)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		//pobierz œcie¿kê rejestracji serwera
		CString oString;
		LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),
			_T("InstallationRoot"), oString);
		ASSERT(lResult == ERROR_SUCCESS);
		oString += _g_pchNAVO2001Engine;
		EnsureEndingBackslash(oString);

		//sprawdzamy czy serwer pracuje tam gdzie jest zarejestrowany
		int nLastBS = _g_NAVOServerCF.GetLocalServerPath().ReverseFind('\\');
		ASSERT(nLastBS != -1);
		CString oServerDirString = _g_NAVOServerCF.GetLocalServerPath().Left(nLastBS + 1);
		if (oServerDirString.CompareNoCase(oString))
		{
			ThrowNavoException2(ERCO_APPSERV_WORK_DIR_DIFF_REGISTRY, IDPAGE_NOTAVAILABLE, (LPCTSTR)oServerDirString, (LPCTSTR)oString);
		}

		*ppDataStream = NULL;
		*ppInfoStream = NULL;

		int nCompareResult = _tcscmp(lpClientVersion, GetNAVO2001EngineVersion());
		if (nCompareResult > 0)
		{
			return S_FALSE;	//niedobrze - klient ma nowsz¹ wersjê ni¿ serwer
		}
		if (nCompareResult < 0)	//klient ma starsz¹ wersjê ni¿ serwer - przygotuj "backup"
		{
			SCP<IBackupRestoreManager> poBRManSP;
			poBRManSP.CreateInstance(CLSID_NAVO2001BackupRestoreManager, CLSCTX_INPROC);

			LPDISPATCH lpDispatch = NULL;
			HRESULT hr = poBRManSP->NewBrSet(&lpDispatch);
			ASSERT(hr == S_OK); //to_do: error checking
			IBRSet oBrSet(lpDispatch);
			oBrSet.SetType(long(BRSET_FILEGROUP));
			oBrSet.SetRelative(TRUE);
			oBrSet.SetRecurse(TRUE);

			oBrSet.SetPath(oString);
			oBrSet.SetMask(_T("*.exe|*.dll|*.ocx|*.jpg|*.ini|*.gif|*.htt"));
			hr = poBRManSP->AddBrSet(oBrSet);
			ASSERT(hr == S_OK);
			hr = poBRManSP->GetBackupStream(ppDataStream, ppInfoStream, NULL, NULL);
			return hr;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
AdviseLM(LPCSTR pcUserName, LPCSTR pcComputerName, long *pCookie)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(pThis->_get_pseudo_cookie()) + ":AdviseLM:" +
				CString(pcUserName) + "," + CString(pcComputerName);
		}

		ASSERT(_g_NAVOServerCF.m_poLockManagerSP.PointsObject());
		HRESULT hr = _g_NAVOServerCF.m_poLockManagerSP->Advise(pcUserName, pcComputerName, pCookie);
		if (hr == S_OK)
		{
			pThis->m_nLockManagerCookie = *pCookie;
		}
		else
		{
			pThis->m_nLockManagerCookie = 0;
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
UnAdviseLM(long nCookie)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(pThis->_get_pseudo_cookie()) + ":UnAdviseLM:";
		}

		ASSERT(_g_NAVOServerCF.m_poLockManagerSP.PointsObject());
		ASSERT(pThis->m_nLockManagerCookie == nCookie);
		pThis->m_nLockManagerCookie = 0;
		return _g_NAVOServerCF.m_poLockManagerSP->UnAdvise(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
AdviseNM(IUnknown * pONSinkUnknown, LPCSTR pcUserName,
	LPCSTR pcComputerName, notifysinkclass eNSC, long *pCookie)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(pThis->_get_pseudo_cookie()) + ":AdviseNM:" +
				CString(pcUserName) + "," + CString(pcComputerName);
		}

		ASSERT(_g_NAVOServerCF.m_poNofiManagerSP.PointsObject());
		HRESULT hr = _g_NAVOServerCF.m_poNofiManagerSP->Advise(pONSinkUnknown, pcUserName,
			pcComputerName, eNSC, pCookie);
		if (hr == S_OK)
		{
			pThis->m_nNotManCookie = *pCookie;
		}
		else
		{
			pThis->m_nNotManCookie = 0;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
UnAdviseNM(long nCookie)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		if (oNavoLog.IsHandleValid())
		{
			oNavoLog << Long2String(pThis->_get_pseudo_cookie()) + ":UnAdviseNM:";
		}

		ASSERT(_g_NAVOServerCF.m_poNofiManagerSP.PointsObject());
		ASSERT(pThis->m_nNotManCookie == nCookie);
		pThis->m_nNotManCookie = 0;
		return _g_NAVOServerCF.m_poNofiManagerSP->UnAdvise(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
GetRegistryKeyString(long hKeyClass, LPCSTR lpSubKey, LPCSTR lpName, LPSTR * plpValue)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		CString oValueString;
		long lResult = SafeGetRegistryKeyString(HKEY(hKeyClass), lpSubKey, lpName, oValueString);
		if (lResult != ERROR_SUCCESS)
		{
			oValueString = "";
		}
		*plpValue = (LPTSTR) ::NdrOleAllocate(oValueString.GetLength() + 1);
		strcpy((LPTSTR)*plpValue, oValueString);
		return (lResult == ERROR_SUCCESS) ? S_OK : S_FALSE;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
SetRegistryKeyString(long hKeyClass, LPCSTR lpSubKey, LPCSTR lpName, LPCSTR lpValue)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		::SetRegistryKeyString(HKEY(hKeyClass), lpSubKey, lpName, lpValue);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
EnumRegistryKeys(long hKeyClass, LPCSTR lpSubKey, LPSTR * plpValue)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		CString strResult;
		CArray<CString, LPCTSTR> oKeyArray;
		LONG lResult = ::EnumRegistryKeys(HKEY(hKeyClass), lpSubKey, oKeyArray);
		if (lResult == ERROR_SUCCESS)
		{
			for (long iter = 0; iter <= oKeyArray.GetUpperBound(); iter++)
			{
				strResult += oKeyArray[iter] + '\t';
			}
		}
		*plpValue = (LPTSTR) ::NdrOleAllocate(strResult.GetLength() + 1);
		strcpy((LPTSTR)*plpValue, strResult);
		return (lResult == ERROR_SUCCESS) ? S_OK : S_FALSE;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
Close2()
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

	ALL_TRY
	{
		return  S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	
	return S_OK;
}

STDMETHODIMP CServerClientObject::XServerClient::
GetUniqueId(LPSTR * ppUniqueId)
{
	METHOD_PROLOGUE(CServerClientObject, ServerClient)

		ALL_TRY
	{
		CString oUniqueIdString;
		LONG lResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,
			GetSetupRegistryKeyName(), _T("MainUID"), oUniqueIdString);
		*ppUniqueId = (LPTSTR) ::NdrOleAllocate(oUniqueIdString.GetLength() + 1);
		strcpy((LPTSTR)*ppUniqueId, oUniqueIdString);
		return (lResult == ERROR_SUCCESS) ? S_OK : S_FALSE;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

//----------------------------------------------------------
//		ping server implementation
//----------------------------------------------------------

STDMETHODIMP CServerClientObject::XPingServer::Advise(IUnknown * pPingUnknown, long *pCookie)
{
	METHOD_PROLOGUE(CServerClientObject, PingServer)

		ALL_TRY
	{
		long nCookie = reinterpret_cast<long>(pThis);
		_g_NAVOServerCF.m_oPingServer.__Advise(pPingUnknown, nCookie);
		*pCookie = nCookie;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CServerClientObject::XPingServer::UnAdvise(long nCookie)
{
	METHOD_PROLOGUE(CServerClientObject, PingServer)

		ALL_TRY
	{
		ASSERT(nCookie == reinterpret_cast<long>(pThis));
		_g_NAVOServerCF.m_oPingServer.__UnAdvise(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

//----------------------------------------------------------

void CNavoServerPingServer::OnDeadClient(long nCookie)
{
	_g_NAVOServerCF.MarkWasFailedClient();
	CServerClientObject * poSCO = reinterpret_cast<CServerClientObject *>(nCookie);
	ASSERT(poSCO);
	poSCO->_clean_up(false);
}

