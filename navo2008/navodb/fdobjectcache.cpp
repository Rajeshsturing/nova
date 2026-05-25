/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Object Cache
*/

#include "stdafx.h"
#include "navodb.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\navodef\stdobjdef.h"
#include "..\include\flatdata.h"	//flat data transport
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\DefinitionManager.h"
#include "ADOObjServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CFDObjectCache::Flush()
{
	CSimpleLock oSL(m_oCS);
	m_oObjectCacheMap.RemoveAll();
}

bool CFDObjectCache::Get(long TypeId,long IdObj,SCP<CFlatData> & rpoFlatDataSP)
{
	if(_is_disabled())	//cache disabled
	{
		return false;
	}

#ifdef _DEBUG
		m_nCacheRequests++;
#endif
	__int64 lKey = longlong(TypeId,IdObj);

	CSimpleLock oSL(m_oCS);
	SCP<CFlatData> * prpoFlatDataSP = m_oObjectCacheMap.SafeGetAt(lKey);
	if(prpoFlatDataSP)
	{
		rpoFlatDataSP = *prpoFlatDataSP;
#ifdef _DEBUG
		m_nCacheHits++;
#endif
		return true;
	}
	else
	{
		return false;
	}
}

void CFDObjectCache::Set(long TypeId,long IdObj,SCP<CFlatData> & rpoFlatDataSP)
{
	if(_is_disabled())	//cache disabled
	{
		return;
	}

#ifdef _DEBUG
	m_nCacheUpdates++;	//duty
#endif
	__int64 lKey = longlong(TypeId,IdObj);
	{
		//WARNING! You have to own critical section
		while(DWORD(m_oObjectCacheMap.GetCount()) > m_dwMaxCacheSize)
		{
			m_oObjectCacheMap.RemoveAtPosition(m_oObjectCacheMap.GetFirstPosition());
		}
		SCP<CFlatData> * ppoFlatDataSP = m_oObjectCacheMap.SafeGetAt(lKey);
		if(ppoFlatDataSP)
		{
			* ppoFlatDataSP = rpoFlatDataSP;
		}
		else
		{
			m_oObjectCacheMap.Add(lKey,rpoFlatDataSP);
		}
#ifdef _DEBUG
		m_nMaxRunningObjects = max(m_nMaxRunningObjects,m_oObjectCacheMap.GetCount());
#endif
	}
}
	
void CFDObjectCache::Remove(long TypeId,long IdObj)
{
	if(_is_disabled())	//cache disabled
	{
		return;
	}

#ifdef _DEBUG
	m_nCacheUpdates++;	//duty
#endif
	__int64 lKey = longlong(TypeId,IdObj);
	{
		//WARNING! You have to own critical section
		if(m_oObjectCacheMap.Exists( lKey ))
		{
			m_oObjectCacheMap.Remove( lKey );
		}
	}
}

void CFDObjectCache::purge()
{
	m_oObjectCacheMap.RemoveAll();
}

bool CFDObjectCache::GetMaxIdObj(long TypeId,long & nMaxIdObj)
{
	//WARNING! You have to own critical section
	return m_oUniqueIdMap.Lookup(TypeId,nMaxIdObj) != FALSE;
}

void CFDObjectCache::SetMaxIdObj(long TypeId,long nMaxIdObj)
{
	//WARNING! You have to own critical section
	m_oUniqueIdMap[ TypeId ] = nMaxIdObj;
}

void CFDObjectCache::SetSharedVar(long nVarNr,const CSmartOleVariant & roSOV)
{
	CSimpleLock oSLock(m_oSharedVarCS);
	m_poSharedVarHLISP->SetProp(nVarNr,roSOV);
}

bool CFDObjectCache::GetSharedVar(long nVarNr,CSmartOleVariant & roSOV)
{
	switch(nVarNr)
	{
	case GVAR_SYSTIME:
		_get_system_time(roSOV);
	return true;
	case GVAR_SYSDATE:
		_get_system_date(roSOV);
	return true;
	default:
		{
			CSimpleLock oSLock(m_oSharedVarCS);
			return m_poSharedVarHLISP->SafeGetProp(nVarNr,roSOV);
		}
	}
}

void CFDObjectCache::_get_system_time(CSmartOleVariant & roSOV)
{
	int nYear,nMonth,nDay,nHour,nMin,nSecond;
	OleDate2Parts(COleDateTime::GetCurrentTime(),nYear,nMonth,nDay,nHour,nMin,nSecond);
	roSOV.ChangeType(VT_I4);
	roSOV.SetLong(nHour*100+nMin);
}

void CFDObjectCache::_get_system_date(CSmartOleVariant & roSOV)
{
	int nYear,nMonth,nDay,nHour,nMin,nSecond;
	OleDate2Parts(COleDateTime::GetCurrentTime(),nYear,nMonth,nDay,nHour,nMin,nSecond);
	COleDateTime oDateOnly;
	oDateOnly.SetDate(nYear,nMonth,nDay);
	roSOV.ChangeType(VT_DATE);
	roSOV.SetDate(oDateOnly);
}

#ifdef _DEBUG

void CFDObjectCache::ShowStatistics()
{
	TRACE0("------Server Object Cache statistic----------\n");
	TRACE1("Total requests: %d \n",m_nCacheRequests);
	TRACE1("Cache hits: %d \n",m_nCacheHits);
	TRACE1("Cache updates: %d \n",m_nCacheUpdates);
	TRACE1("Cache hit ratio %%: %d \n",(m_nCacheRequests==0) ? 0 : ((100*m_nCacheHits)/m_nCacheRequests));
	TRACE1("Cache upd ratio %%: %d \n",(m_nCacheRequests==0) ? 0 : ((100*m_nCacheUpdates)/m_nCacheRequests));
	TRACE1("Max running obj: %d \n",m_nMaxRunningObjects);
}

#endif

SCP<CDefinitionManager> CDefinitionManagerProvider::_load_definition(LPCTSTR lpAppName)
{
	SCP<CDefinitionManager> poDefinitionManagerSP;
	//1.create appdbmanager for this application
	SCP<IAppDBManager> poAppDBManagerSP;
	poAppDBManagerSP.CreateInstance(CLSID_NAVO2001AppDBManager,CLSCTX_INPROC_SERVER);
	HRESULT hr = poAppDBManagerSP->Init(lpAppName);
	if(hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(poAppDBManagerSP,oNavoException);
		ContinueThrowNavoException2(oNavoException,ERCO_TODO,
			IDPAGE_NOTAVAILABLE,lpAppName,SCODE_To_String(hr));
	}
	//2.
	SCP<IStreamProvider> poStreamProviderSP;
	poStreamProviderSP.QueryInterface(poAppDBManagerSP);
	SCP<IStream> poClassDefinitionStreamSP;
	navostreaminfo oNSI;
	_init_navostreaminfo(oNSI);
	hr = poStreamProviderSP->Get(IDPAGE_CLASSDEF,&poClassDefinitionStreamSP.GetRawPointer(),&oNSI);
	if(hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(poAppDBManagerSP,oNavoException);
		ContinueThrowNavoException2(oNavoException,ERCO_TODO,
			IDPAGE_NOTAVAILABLE,lpAppName,SCODE_To_String(hr));
	}
	ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if(oNSI.m_bCompressed == '1')
	{
		poClassDefinitionStreamSP = UncompressStream(poClassDefinitionStreamSP);
	}

	poDefinitionManagerSP = NewSCP(new CDefinitionManager());
	poDefinitionManagerSP->InitializeFrom(poClassDefinitionStreamSP);
	return poDefinitionManagerSP;
}

SCP<CDefinitionManager> CDefinitionManagerProvider::_get_definition(LPCTSTR lpAppName)
{
	CSimpleLock oSL(m_oCS);
	SCP<CDefinitionManager> poDefinitionManagerSP;
	if(!m_oDMMap.Lookup(lpAppName,poDefinitionManagerSP))
	{
		//need to load
		poDefinitionManagerSP = _load_definition(lpAppName);
		ASSERT(poDefinitionManagerSP.PointsObject());
		m_oDMMap[ lpAppName ] = poDefinitionManagerSP;
	}
	ASSERT(poDefinitionManagerSP.PointsObject());
	return poDefinitionManagerSP;
}

//-------------------------------------------------------------------------------------
// tracks db writes
//-------------------------------------------------------------------------------------
void CFDObjectCache::track_write(long nUserDynamicCookie,const CFlatData & roFlatData)
{
	ASSERT(is_tracking_writes());

	CSimpleLock oSLock(m_oTrackWritesCS);
	if(m_poTrackWritesStreamSP.PointsNull())
	{
		m_poTrackWritesStreamSP = OpenFileStream("nedb-changes-log.bin",true,
			GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_DELETE,OPEN_ALWAYS);
		CStreamHolder oSH(m_poTrackWritesStreamSP);
		oSH.SeekToEnd();
		LPCTSTR lpFormatMarker = "\x01NEDBDBL1\x01";
		oSH.WritePascalString(lpFormatMarker);
	}
	CStreamHolder oSH(m_poTrackWritesStreamSP);
	oSH.Write(&nUserDynamicCookie,sizeof(nUserDynamicCookie));
	oSH.Write(roFlatData.GetDataPtr(),roFlatData.GetDataLen());
}
