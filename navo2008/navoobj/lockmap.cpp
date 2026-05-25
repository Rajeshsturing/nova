/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNEO_lockmap
*/


#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "lockmap.h"

CNEO_lockmap::CNEO_lockmap()
{
	m_oWriteLockMap.InitHashTable( 2111 );
}

CNEO_lockmap::~CNEO_lockmap()
{
}

bool CNEO_lockmap::_search_write_lock_map(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	navolockid oNLID;
	oNLID.m_class	= nClass;
	oNLID.m_typeid	= nTypeId; 
	oNLID.m_idobj	= nIdObj;
	oNLID.m_extra	= nExtra;

	long dwRef = 0;
	if(m_oWriteLockMap.Lookup(oNLID,dwRef))
	{
		ASSERT(dwRef > 0);
		return true;
	}
	else
	{
		return false;
	}
}

void CNEO_lockmap::_add_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	navolockid oNLID;
	oNLID.m_class	= nClass;
	oNLID.m_typeid	= nTypeId; 
	oNLID.m_idobj	= nIdObj;
	oNLID.m_extra	= nExtra;
	long dwRef = 0;
	if(m_oWriteLockMap.Lookup(oNLID,dwRef))
	{
		ASSERT(dwRef > 0);
	}
	dwRef++;
	m_oWriteLockMap[ oNLID ] = dwRef;
	TRACE("WLM:add: %d,%d=%d\n",nTypeId,nIdObj,dwRef);
}

void CNEO_lockmap::release_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	navolock oNavoLock;
	oNavoLock.m_fullid.m_class	= nClass;
	oNavoLock.m_fullid.m_typeid	= nTypeId; 
	oNavoLock.m_fullid.m_idobj	= nIdObj;
	oNavoLock.m_fullid.m_extra	= nExtra;

	long dwRef = 0;
	VERIFY(m_oWriteLockMap.Lookup(oNavoLock.m_fullid,dwRef));
	ASSERT(dwRef > 0);

	dwRef--;
	
	if(dwRef == 0)
	{
		VERIFY(m_oWriteLockMap.RemoveKey(oNavoLock.m_fullid));
		oNavoLock.m_type = nlt_exlock;
		m_oPendingUnlockArray.Add(oNavoLock);
	}
	else
	{
		m_oWriteLockMap[ oNavoLock.m_fullid ] = dwRef;
	}
	TRACE("WLM:release: %d,%d=%d\n",nTypeId,nIdObj,dwRef);
}

void CNEO_lockmap::release_all_write_locks()
{
	
	POSITION pos = m_oWriteLockMap.GetStartPosition();
	while(pos)
	{
		navolock oNavoLock;
		long dwRef = 0;
		m_oWriteLockMap.GetNextAssoc(pos,oNavoLock.m_fullid,dwRef);
		ASSERT(dwRef > 0);
		while(dwRef--)
		{
			m_oPendingUnlockArray.Add(oNavoLock);
		}
	}
	m_oWriteLockMap.RemoveAll();
}
