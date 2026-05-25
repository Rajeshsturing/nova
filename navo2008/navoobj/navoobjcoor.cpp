/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNavoObjectCoordinator

	"global" object which manages all client dataobject activity
*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobjcache.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNavoObjectCoordinator::CNavoObjectCoordinator(CNavoException & roErrorStorage) :
	m_roErrorStorage(roErrorStorage),
	m_poDBAccessProxy(new CDBAccessProxy(roErrorStorage)),
	//-----------------------------------------------newcode----------------------
	m_poCurrentTrans(NULL),
	m_bShowUI(false),
	m_poCommonEnvironmentHLISP(GetSystemEnvironmentHLI())
{
#ifdef _DEBUG
	m_nProvideStorageCalls = 0;
	m_nLoadObjectCalls = 0;
#endif
#ifdef _DEVELOPER_EDITION_
	m_debug_trans_nr_gener = 0;
#endif

	COleDateTime oTodayODT(COleDateTime::GetCurrentTime());
	{
		int nYear,nMonth,nDay,nHour,nMin,nSecond;
		OleDate2Parts(oTodayODT,nYear,nMonth,nDay,nHour,nMin,nSecond);
		oTodayODT.SetDate(nYear,nMonth,nDay);
	}
	m_poCommonEnvironmentHLISP->SetProp(GVAR_TODAY,oTodayODT);
}

CNavoObjectCoordinator::~CNavoObjectCoordinator()
{
#ifdef _DEBUG
	TRACE("--------------- provide_storage stats ------------------\n");
	TRACE("provide storage calls %d\n",m_nProvideStorageCalls);
	TRACE("load objects calls %d\n",m_nLoadObjectCalls);
	TRACE("load objects ratio %d%%\n",
		(m_nProvideStorageCalls == 0) ? 0 :
		(100*m_nLoadObjectCalls / m_nProvideStorageCalls));
	TRACE("--------------------------------------------------------\n");
#endif
	Disconnect();
	delete m_poDBAccessProxy;
}

void CNavoObjectCoordinator::SetShowUI(bool bShowUI)
{
	m_bShowUI = bShowUI;
	m_poDBAccessProxy->SetShowUI(bShowUI);
}

void CNavoObjectCoordinator::Connect(CDBAP_ConnectionParam & roConnectionParam,
									 SCP<CDefinitionManager> & rpoDefinitionManageSP)
{
	ASSERT(rpoDefinitionManageSP.PointsObject());
	m_poDefinitionManageSP = rpoDefinitionManageSP;
	m_poDBAccessProxy->Init(roConnectionParam, rpoDefinitionManageSP);
	m_poCommonEnvironmentHLISP->SetStrProp(GVAR_DBSERVER,roConnectionParam.m_lpServerName);
	m_poCommonEnvironmentHLISP->SetNumProp(GVAR_DBTYPE,roConnectionParam.m_nEngineType);
	m_poStorageCacheSP = NewSCP( new CNEO_global_cache(m_poDBAccessProxy,m_poDefinitionManageSP.Get()));
}

void CNavoObjectCoordinator::Disconnect()
{
	if(m_poStorageCacheSP.PointsObject())
	{
		m_poStorageCacheSP->done();
	}

	m_poStorageCacheSP = 0;

	m_poDBAccessProxy->Done();
	m_poDefinitionManageSP = 0;
}

void CNavoObjectCoordinator::PurgeLocalBlobCache()
{
	if(m_poStorageCacheSP.PointsObject())
	{
		m_poStorageCacheSP->purge_local_blob_cache();
	}
}

CNEO_global_cache * CNavoObjectCoordinator::get_storage_cache()
{
	return m_poStorageCacheSP;
}

SCP<CNEO_thread> CNavoObjectCoordinator::CreateNewThread()
{
	SCP<CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo);
	(*poHLISP) = (*m_poCommonEnvironmentHLISP);

	return NewSCP(new CNEO_thread(this,m_roErrorStorage,poHLISP));
}

void CNavoObjectCoordinator::SetCurrentTrans(CNEO_trans * poTrans)
{
#ifdef _DEBUG
	{
		long nOldTrans = 0;
		if(m_poCurrentTrans != NULL)
		{
			nOldTrans = m_poCurrentTrans->_debug_trans_nr;
		}
		
		long nNewTrans = 0;
		if(poTrans != NULL)
		{
			nNewTrans = poTrans->_debug_trans_nr;
		}
		if(nNewTrans != nOldTrans)
		{
			TRACE("TRANSSWITCH %d => %d\n",nOldTrans,nNewTrans);
		}
	}
#endif

	m_poCurrentTrans = poTrans;
}

	
SCP<IDispatch> CNavoObjectCoordinator::CCurrentTransactionDDR::GetDynamicDispatchSP()
{
	CNavoObjectCoordinator * pThis = ((CNavoObjectCoordinator*)((BYTE*)this - offsetof(CNavoObjectCoordinator, m_oCurrentTransDDR)));
	if(pThis->GetCurrentTrans())
	{
		return pThis->GetCurrentTrans()->GetDispatchSP();
	}
	else
	{
		return SCP<IDispatch>();
	}
}

SCP<CDefinitionManager> CNavoObjectCoordinator::GetDefinitionManager()
{
	return m_poDefinitionManageSP;
}


void CNavoObjectCoordinator::SetCommonVar(long nVarNr,const CSmartOleVariant & croSOV)
{
	ASSERT((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER));
	ASSERT(m_poCommonEnvironmentHLISP.PointsObject());
	m_poCommonEnvironmentHLISP->SetProp(nVarNr,croSOV);
}

void CNavoObjectCoordinator::GetCommonVar(long nVarNr,CSmartOleVariant & roSOV)
{
	ASSERT((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER));
	ASSERT(m_poCommonEnvironmentHLISP.PointsObject());
	
	if(!m_poCommonEnvironmentHLISP->SafeGetProp(nVarNr,roSOV))
	{
		ThrowNavoException1(ERCO_OBJCOOR_NO_VARIABLE,IDPAGE_NOTAVAILABLE, nVarNr);
	}
}

bool CNavoObjectCoordinator::IsCommonVar(long nVarNr)
{
	ASSERT((nVarNr >= COMMON_VAR_FIRST && nVarNr <= COMMON_VAR_LAST) || (nVarNr == GVAR_TODAY || nVarNr == GVAR_DBSERVER));
	ASSERT(m_poCommonEnvironmentHLISP.PointsObject());
	
	return m_poCommonEnvironmentHLISP->PropertyExists(nVarNr);
}


bool CNavoObjectCoordinator::fwd_create_counted_resource(LPCTSTR lpResName,long nMaxUsage)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->create_counted_resource(lpResName,nMaxUsage);
}

bool CNavoObjectCoordinator::fwd_delete_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->delete_counted_resource(lpResName);
}

long CNavoObjectCoordinator::fwd_use_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->use_counted_resource(lpResName);
}

long CNavoObjectCoordinator::fwd_get_usage_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->get_usage_counted_resource(lpResName);
}

void CNavoObjectCoordinator::fwd_release_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poDBAccessProxy);
	m_poDBAccessProxy->release_counted_resource(lpResName);
}

bool CNavoObjectCoordinator::WriteToArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pDestStream)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->WriteToArchive(lpSAUser,lpPwd,lpArchivePwd,pDestStream);
}

bool CNavoObjectCoordinator::ReadFromArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pSrcStream)
{
	ASSERT(m_poDBAccessProxy);
	return m_poDBAccessProxy->ReadFromArchive(lpSAUser,lpPwd,lpArchivePwd,pSrcStream);
}


