/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	notification manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"		//generic error storage
#include "..\include\clientinfo.h"		//client info
#include "..\include\navoclassfactory.h"
#include "..\include\h1000.h"
#include "NotificationManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------------------------------------
// ctor,dtor,macros etc.
//--------------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CNotificationManager, CCmdTarget)

DELEGATE_UNKNOWN_INTERFACE(CNotificationManager, NotificationManager)
DELEGATE_UNKNOWN_INTERFACE(CNotificationManager, NavoErrorInfo)

CNotificationManager::CNotificationManager() :
	m_oExitEvent(FALSE, TRUE),
	m_oNewNotificationEvent(FALSE, TRUE)
{
	memset(m_hSendingThreads, 0, sizeof(m_hSendingThreads));	//set invalid handles
	EnableAutomation();
	AfxOleLockApp();

	_start_working_threads();
}

CNotificationManager::~CNotificationManager()
{
	AfxOleUnlockApp();
}

void CNotificationManager::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

//{{AFX_MSG_MAP(CNotificationManager)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNotificationManager, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNotificationManager)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CNotificationManager, CCmdTargetInterface)
	INTERFACE_PART(CNotificationManager, IID_INavoErrorInfo, NavoErrorInfo)
	INTERFACE_PART(CNotificationManager, IID_INotificationManager, NotificationManager)
END_INTERFACE_MAP()

// {188cb150-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CNotificationManager, "navodb.notmanager", 0x188cb150, 0x82a4, 0x4498, 0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

//--------------------------------------------------------------------------------------
// INotificationManager	interface
//--------------------------------------------------------------------------------------

STDMETHODIMP CNotificationManager::XNotificationManager::
Advise(IUnknown * pONSinkUnknown, LPCSTR pcUserName, LPCSTR pcComputerName,
	notifysinkclass eNSC, long *pCookie)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_advise(pONSinkUnknown, pcUserName, pcComputerName, eNSC, pCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CNotificationManager::XNotificationManager::
UnAdvise(long nCookie)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_unadvise(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}


STDMETHODIMP CNotificationManager::XNotificationManager::
NotifySharedVariableChange(long nOriginatorCookie, long lVarNr, VARIANT nNewValue)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_notify_shared_var_change(nOriginatorCookie, lVarNr, nNewValue);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CNotificationManager::XNotificationManager::
QuerySinks(long *pDataLength, byte ** lpBinaryData)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		CClientInfoArray oClientInfoArray;
		pThis->_fill_rich_client_info(oClientInfoArray);

		//store in binary form
		CRPCSaver_via_Archive< CClientInfoArray > oRPSvA(oClientInfoArray);
		oRPSvA.Store();
		*pDataLength = oRPSvA.GetLength();
		*lpBinaryData = oRPSvA.GetData();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}
STDMETHODIMP CNotificationManager::XNotificationManager::
QuerySinks2(long *pDataLength, SAFEARRAY ** pSA)
{
	long _pDataLength;
	byte * _lpBinaryData;

	HRESULT hr = QuerySinks(&_pDataLength, &_lpBinaryData);

	if (hr == S_OK)
	{
		*pDataLength = _pDataLength;

		*pSA = SafeArrayCreateVector(VT_UI1, 0, _pDataLength);
		void * pSafeArrayData;
		SafeArrayAccessData(*pSA, &pSafeArrayData);
		memcpy(pSafeArrayData, _lpBinaryData, _pDataLength);
		SafeArrayUnaccessData(*pSA);
		NdrOleFree(_lpBinaryData);
	}

	return hr;
}
STDMETHODIMP CNotificationManager::XNotificationManager::
NotifyUser(long nOriginatorCookie, long nDestinatorCookie,
	long lEvenCode, VARIANT * pDataVariant)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_put_notify_user(nOriginatorCookie, nDestinatorCookie, lEvenCode, pDataVariant);
		return S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}

STDMETHODIMP CNotificationManager::XNotificationManager::
NotifyMultipleUsers(long nOriginatorCookie, long nCount,
	const long * pDestinatorCookies, long lEvenCode, VARIANT * pDataVariant)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_put_notify_multiple_users(nOriginatorCookie, nCount, pDestinatorCookies, lEvenCode, pDataVariant);
		return S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}

STDMETHODIMP CNotificationManager::XNotificationManager::
SetProp(long nCookie, long nProp, VARIANT vValue)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_set_client_prop(nCookie, nProp, vValue);
		return S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}


STDMETHODIMP CNotificationManager::XNotificationManager::
GetProp(long nCookie, long nProp, VARIANT * pvValue)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		if (pThis->_get_client_prop(nCookie, nProp, pvValue))
		{
			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}

STDMETHODIMP CNotificationManager::XNotificationManager::
GetProp2(long nCookie, long nProp, VARIANT * pvValue, long * pHR)
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		if (pThis->_get_client_prop(nCookie, nProp, pvValue))
		{
			*pHR = S_OK;
		}
		else
		{
			*pHR = S_FALSE;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CNotificationManager::XNotificationManager::
Close()
{
	METHOD_PROLOGUE(CNotificationManager, NotificationManager)

		ALL_TRY
	{
		pThis->_close();
		return S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}


//==================================================================
// implementation
//==================================================================

// -- register new user ------

void CNotificationManager::_advise(IUnknown * pONSinkUnknown, LPCSTR pcUserName,
	LPCSTR pcComputerName, notifysinkclass eNSC, long *pCookie)
{
	*pCookie = 0;
	SCP<INotificationSink> poNotificationSinkSP;
	poNotificationSinkSP.QueryInterface(pONSinkUnknown);
	SCP<CNMClientInfo> poClientInfoSP =
		NewSCP(new CNMClientInfo(pcUserName, pcComputerName, eNSC, poNotificationSinkSP));

	CSimpleLock oSimpleLock(m_oCookieCS);
	long nCookie = poClientInfoSP->GetCookie();
	m_oMap[nCookie] = poClientInfoSP;
	*pCookie = nCookie;

	//store default properties
	_set_client_prop(nCookie, GVAR_OSUSERNAME, CSmartOleVariant(pcUserName).GetVariantRef());
	_set_client_prop(nCookie, GVAR_MACHINE, CSmartOleVariant(pcComputerName).GetVariantRef());
}

// -- remove user's registration ---

void CNotificationManager::_unadvise(long nCookie)
{
	CSimpleLock oSimpleLock(m_oCookieCS);
	VERIFY(m_oMap.RemoveKey(nCookie));
}


// -- get all users' rich info ------

void CNotificationManager::_fill_rich_client_info(CClientInfoArray & roClientInfoArray)
{
	//fill array from map
	CSimpleLock oSimpleLock(m_oCookieCS);

	long nCounter = m_oMap.GetCount();
	roClientInfoArray.SetSize(nCounter);
	POSITION pos = m_oMap.GetStartPosition();
	while (pos)
	{
		long nCookie;
		SCP<CNMClientInfo> poNMClientInfoSP;
		m_oMap.GetNextAssoc(pos, nCookie, poNMClientInfoSP);
		roClientInfoArray[--nCounter] = *poNMClientInfoSP;
	}
}

// -- get all users' cookies
void CNotificationManager::_fill_cookie_info(CArray<long, long&> & roCookieInfoArray)
{
	//fill array from map
	CSimpleLock oSimpleLock(m_oCookieCS);

	long nCounter = m_oMap.GetCount();
	roCookieInfoArray.SetSize(nCounter);
	POSITION pos = m_oMap.GetStartPosition();
	while (pos)
	{
		long nCookie;
		SCP<CNMClientInfo> poNMClientInfoSP;
		m_oMap.GetNextAssoc(pos, nCookie, poNMClientInfoSP);
		roCookieInfoArray[--nCounter] = nCookie;
	}
}

// -- close sub system, stop all threads

void CNotificationManager::_close()
{
	//info working threads we are exiting
	m_oExitEvent.SetEvent();
	//wait for finish of every thread
	::WaitForMultipleObjects(_MAX_SENDING_THREADS, m_hSendingThreads, TRUE, INFINITE);
}


void CNotificationManager::_set_client_prop(long nCookie, long nProp, const VARIANT & rvValue)
{
	CSimpleLock oSimpleLock(m_oCookieCS);		//sekcja tutaj, aby zapobiec jednoczesnej modyfikacji property przez 2 u¿ytk.
	SCP<CNMClientInfo> poClientInfoSP;
	{
		if (!m_oMap.Lookup(nCookie, poClientInfoSP))
		{
			return;
		}
	}
	poClientInfoSP->_client_properties()->SetProp(nProp, CSmartOleVariant(rvValue));
}

bool CNotificationManager::_get_client_prop(long nCookie, long nProp, VARIANT * pvValue)
{
	CSimpleLock oSimpleLock(m_oCookieCS);		//sekcja tutaj, aby zapobiec jednoczesnej modyfikacji property przez 2 u¿ytk.
	SCP<CNMClientInfo> poClientInfoSP;
	{
		if (!m_oMap.Lookup(nCookie, poClientInfoSP))
		{
			return false;
		}
	}
	CSmartOleVariant oSOV;
	if (!poClientInfoSP->_client_properties()->SafeGetProp(nProp, oSOV))
	{
		return false;
	}
	if (pvValue)
	{
		*pvValue = oSOV.Detach();
	}
	return true;
}

static SCP<CServerNotificationData> _convert_2_SND(long nOriginatorCookie, long nDestinatorCookie,
	long lEvenCode, VARIANT * pDataVariant)
{
	SCP<CServerNotificationData> poSNSP = NewSCP(new CServerNotificationData());
	poSNSP->_originator() = nOriginatorCookie;
	poSNSP->_destinator() = nDestinatorCookie;
	poSNSP->_event() = lEvenCode;
	if (pDataVariant)
	{
		poSNSP->_data() = *pDataVariant;
	}
	return poSNSP;
}

void CNotificationManager::_put_notify_user(long nOriginatorCookie, long nDestinatorCookie, long lEventCode, VARIANT * pDataVariant)
{
	if (nDestinatorCookie == -1)	//means all users
	{
		CArray<long, long&> oCookieArray;
		_fill_cookie_info(oCookieArray);
		_put_notify_multiple_users(nOriginatorCookie, oCookieArray.GetSize(), oCookieArray.GetData(), lEventCode, pDataVariant);
	}
	else
	{
		CList<SCP<CServerNotificationData>, SCP<CServerNotificationData> &> oNewList;
		oNewList.AddTail(_convert_2_SND(nOriginatorCookie, nDestinatorCookie, lEventCode, pDataVariant));
		_add_to_queue(oNewList);
	}
}

void CNotificationManager::_put_notify_multiple_users(long nOriginatorCookie,
	long nCount, const long * pDestinatorCookies,
	long lEventCode, VARIANT * pDataVariant)
{
	if (nCount > 0)
	{
		CList<SCP<CServerNotificationData>, SCP<CServerNotificationData> &> oNewList;
		for (long iter = 0; iter < nCount; iter++)
		{
			oNewList.AddTail(_convert_2_SND(nOriginatorCookie, pDestinatorCookies[iter], lEventCode, pDataVariant));
		}
		_add_to_queue(oNewList);
	}
}

void CNotificationManager::_notify_shared_var_change(long nOriginatorCookie, long lVarNr, const VARIANT & rvNewValue)
{
	return;	//notyfikacje s¹ nieu¿ywane wiêc nie s¹ wysy³ane

	{
		CSimpleLock oSimpleLock(m_oCookieCS);
		POSITION pos = m_oMap.GetStartPosition();
		while (pos)
		{
			long nCookie;
			SCP<CNMClientInfo> poClientInfoSP;
			m_oMap.GetNextAssoc(pos, nCookie, poClientInfoSP);
			if (nOriginatorCookie != nCookie)
			{
				HRESULT hr = poClientInfoSP->GetNotificationSink()->OnSharedVariableChange(lVarNr, rvNewValue);
			}
		}
	}
}

void CNotificationManager::_add_to_queue(CList<SCP<CServerNotificationData>, SCP<CServerNotificationData> &> & roNewList)
{
	CSimpleLock oSimpleLock(m_oNotificationListCS);
	m_oNotificationList.AddTail(&roNewList);
	m_oNewNotificationEvent.SetEvent();
}

SCP<CServerNotificationData> CNotificationManager::_retrieve_from_queue()
{
	SCP<CServerNotificationData> poSNDSP;

	{
		CSimpleLock oSimpleLock(m_oNotificationListCS);
		if (m_oNotificationList.GetCount() != 0)
		{
			poSNDSP = m_oNotificationList.RemoveHead();
			ASSERT(poSNDSP.PointsObject());
		}
		if (m_oNotificationList.IsEmpty())
		{
			VERIFY(m_oNewNotificationEvent.ResetEvent());
		}
	}
	return poSNDSP;
}

void CNotificationManager::_call_destination(SCP<CServerNotificationData> poSNDSP)
{
	ASSERT(poSNDSP.PointsObject());

	SCP<CNMClientInfo> poClientInfoSP;
	{
		CSimpleLock oSimpleLock(m_oCookieCS);
		if (!m_oMap.Lookup(poSNDSP->_destinator(), poClientInfoSP))
		{
			return;
		}
	}

	//jeœli klient odjecha³, albo w³aœnie siê wyrejestrowa³ to rzuci siê kontrolowany wyj¹tek
	ALL_TRY
	{
		ASSERT(poClientInfoSP.PointsObject());
		HRESULT hr = poClientInfoSP->GetNotificationSink()->OnNotifyUser(
			poSNDSP->_originator(),poSNDSP->_event(),&poSNDSP->_data().GetVariantRef());
		if (hr != S_OK)
		{
			TRACE("OnNotifyUser failed with %x\n",hr);
		}
	}
	TOP_ALL_CATCH_(GetErrorStorage());
}