/*

	NAVO Enterprise 2008

	Cross Server Information Manager

*/
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
#include "crossinfoman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNavoLog  oNavoLog;

static const DWORD dwCheckInterval = 1000 * 60 * 1;					//co 1 minutê odbywa siê sprawdzenie
static const DATE dateSessionTimeOut = (1.0 / 24.0 / 60.0) * 5.0;	//5 minut

//----------------- class factory -------------------------------

CCrossInfoCF::CCrossInfoCF() :
	CNavoClassFactory(m_oErrorStorage, CLSID_NAVO2002CrossInfoMan,
		_T("navo2002.crossinfoman"), _T(""),true,true),
	m_oCFCriticalSection(/* 4000 spin count,requires W2K+ */)
{
	_set_run_as_service();
}

void CCrossInfoCF::InitModuleName(HINSTANCE hInstance)
{
	TCHAR cBuffer[ _MAX_PATH ];
	VERIFY(::GetModuleFileName(hInstance,cBuffer,sizeof(cBuffer)) != 0);
	m_oLocalServerPathString = cBuffer;
}

void CCrossInfoCF::RegisterServer()
{
	CNavoClassFactory::RegisterServer();
}

bool CCrossInfoCF::Initialize()
{
	m_poCrossInfoObjectSP = NewSCP(new CCrossInfoObject());
	return true;
}

void CCrossInfoCF::Uninitialize()
{
	m_poCrossInfoObjectSP = 0;
}

SCP <IUnknown> CCrossInfoCF::OnCreateObject()
{
	CSimpleLock oLock(m_oCFCriticalSection);
	ASSERT(m_poCrossInfoObjectSP.PointsObject());
	SCP<IUnknown> poUnknownSP = m_poCrossInfoObjectSP->GetUnknownSP();
	ASSERT(poUnknownSP.PointsObject());
	return poUnknownSP;
}

void CCrossInfoCF::Kill()
{
	CSimpleLock oLock(m_oCFCriticalSection);
	ASSERT(m_poCrossInfoObjectSP.PointsObject());
	m_poCrossInfoObjectSP->on_kill_users();
}

//---------------------------- cross info object ---------------------------
DELEGATE_UNKNOWN_INTERFACE(CCrossInfoObject, CrossInfoManager)  

BEGIN_INTERFACE_MAP(CCrossInfoObject, CCmdTargetInterface)
    INTERFACE_PART(CCrossInfoObject, IID_ICrossInfoManager, CrossInfoManager)
END_INTERFACE_MAP()

STDMETHODIMP CCrossInfoObject::XCrossInfoManager::
	SetProp(long * pnUserCookie,long nProp,VARIANT * pvValue)
{
	METHOD_PROLOGUE(CCrossInfoObject, CrossInfoManager)
	
	ALL_TRY
	{
		pThis->_set_prop(pnUserCookie,nProp,pvValue);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CCrossInfoObject::XCrossInfoManager::
	GetProp(long nUserCookie,long nProp,VARIANT * pvValue)
{
	METHOD_PROLOGUE(CCrossInfoObject, CrossInfoManager)
	
	ALL_TRY
	{
		return pThis->_get_prop(nUserCookie,nProp,pvValue) ? S_OK : S_FALSE;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CCrossInfoObject::XCrossInfoManager::
	DeleteUser(long nUserCookie)
{
	METHOD_PROLOGUE(CCrossInfoObject, CrossInfoManager)
	
	ALL_TRY
	{
		pThis->_delete_user(nUserCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

CCrossInfoObject::CCrossInfoObject():
	m_nUserIdGenerator(1),
	m_oExitEvent(FALSE,TRUE),
	m_hCleaningThread(NULL)
{
	EnableAutomation();
	m_oCrossInfoMap.InitHashTable(783);

	CCrossInfoCleaningThread * poThread = new CCrossInfoCleaningThread(this);

	VERIFY(duplicate_os_handle(poThread->m_hThread,m_hCleaningThread));
	::ResumeThread(m_hCleaningThread);
}

CCrossInfoObject::~CCrossInfoObject()
{
	m_oExitEvent.SetEvent();
	::WaitForSingleObject(m_hCleaningThread,INFINITE);
	::CloseHandle(m_hCleaningThread);
}

bool CCrossInfoObject::_set_prop(long * pnUserCookie,long nProp,VARIANT * pvValue)
{
	SCP<CCrossInfoUser> poCIUSP;

	if(*pnUserCookie)	//existing user
	{
		CSimpleLock oLock(m_oObjCriticalSection);
		if(!m_oCrossInfoMap.Lookup(*pnUserCookie,poCIUSP))
		{
			return false;
		}
	}
	else
	{
		poCIUSP = NewSCP(new CCrossInfoUser());
		
		CSimpleLock oLock(m_oObjCriticalSection);
		*pnUserCookie = ++m_nUserIdGenerator;
		m_oCrossInfoMap[ m_nUserIdGenerator ] = poCIUSP;
	}
	
	ASSERT(poCIUSP.PointsObject());
	poCIUSP->_set_prop(nProp,pvValue);
	
	return true;
}

bool CCrossInfoObject::_get_prop(long nUserCookie,long nProp,VARIANT * pvValue)
{
	SCP<CCrossInfoUser> poCIUSP;
	{
		CSimpleLock oLock(m_oObjCriticalSection);
		if(!m_oCrossInfoMap.Lookup(nUserCookie,poCIUSP))
		{
			return false;
		}
	}
	ASSERT(poCIUSP.PointsObject());
	return poCIUSP->_get_prop(nProp,pvValue);
}

void CCrossInfoObject::_delete_user(long nUserCookie)
{
	CSimpleLock oLock(m_oObjCriticalSection);
	m_oCrossInfoMap.RemoveKey(nUserCookie);
}

void CCrossInfoObject::on_kill_users()
{
	CSimpleLock oLock(m_oObjCriticalSection);
	oNavoLog << _T("killcross request will kill ") + Long2String(m_oCrossInfoMap.GetCount()) + _T(" users ");
	m_oCrossInfoMap.RemoveAll();
}

//------------------------------ user informations ----------------------------------

CCrossInfoUser::CCrossInfoUser()
{
}

CCrossInfoUser::~CCrossInfoUser()
{
}

void CCrossInfoUser::_set_prop(long nProp,VARIANT * pvValue)
{
	CSimpleLock oLock(m_oUserCriticalSection);
	m_oLastAccess = COleDateTime::GetCurrentTime().m_dt;
	SetProp(nProp,*reinterpret_cast<CSmartOleVariant *>(pvValue));
}

bool CCrossInfoUser::_get_prop(long nProp,VARIANT * pvValue)
{
	CSimpleLock oLock(m_oUserCriticalSection);
	m_oLastAccess = COleDateTime::GetCurrentTime().m_dt;
	return SafeGetProp(nProp,*reinterpret_cast<CSmartOleVariant *>(pvValue));
}


//------------------------------ cleaning thread --------------------------------

CCrossInfoCleaningThread::CCrossInfoCleaningThread(CCrossInfoObject * poCrossInfo) :
	CNavoThread(CNavoOleInitHolder::MULTITHREADED),
	m_poCrossInfo(poCrossInfo)
{
	ASSERT(poCrossInfo);
}

CCrossInfoCleaningThread::~CCrossInfoCleaningThread()
{
}

void CCrossInfoCleaningThread::_perform_cleanup()
{
	CSimpleLock oLock(m_poCrossInfo->m_oObjCriticalSection);
	POSITION pos = m_poCrossInfo->m_oCrossInfoMap.GetStartPosition();
	DATE dateNow = COleDateTime::GetCurrentTime().m_dt;
	while(pos)
	{
		long nIdUser;
		SCP<CCrossInfoUser> poUserInfoSP;
		m_poCrossInfo->m_oCrossInfoMap.GetNextAssoc(pos,nIdUser,poUserInfoSP);
		ASSERT(poUserInfoSP.PointsObject());
		if(dateNow - poUserInfoSP->_get_last_access() > dateSessionTimeOut)
		{
			m_poCrossInfo->m_oCrossInfoMap.RemoveKey(nIdUser);
		}
	}
}

int CCrossInfoCleaningThread::Run()
{
	while(true)
	{
		DWORD dwWaitResult = ::WaitForSingleObject(m_poCrossInfo->m_oExitEvent.m_hObject,dwCheckInterval);
		switch(dwWaitResult)
		{
		case WAIT_TIMEOUT:
			//czyszczenie
			_perform_cleanup();
		break;
		case WAIT_OBJECT_0:
			//koniec pracy
			return 0;
		}
	}
	return -1;
}

