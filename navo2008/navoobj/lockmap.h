/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNEO_lockmap
*/

#ifndef _LOCKMAP_H_
#define _LOCKMAP_H_

#ifdef _NAVODOTNET
template<> UINT AFXAPI HashKey<const navolockid&> (const navolockid& key);
#endif

class CNEO_lockmap
{
public:
	CNEO_lockmap();
	~CNEO_lockmap();
	bool _search_write_lock_map(long nClass,long nTypeId,long nIdObj,long nExtra);
	void _add_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra);
	void release_write_lock(long nClass,long nTypeId,long nIdObj,long nExtra);

	void release_all_write_locks();

	CArray<navolock,navolock&> & _access_pending_unlocks()
	{
		return m_oPendingUnlockArray;
	}
private:
	CMap<navolockid,const navolockid&,long,long&>	 m_oWriteLockMap;
	CArray<navolock,navolock&>						 m_oPendingUnlockArray;
};

class CNEO_local_mutex_map
{
public:
	CNEO_local_mutex_map();
	~CNEO_local_mutex_map();

	bool try_acquire_mutex(long nClass,long nTypeId,long nIdObj,long nExtra);
	void release_mutex(long nClass,long nTypeId,long nIdObj,long nExtra);
private:
	CMap<navolockid,const navolockid&,long,long&>	 m_oMutexMap;
};

//---------------------------------------------------------
//---------------------------------------------------------

inline CNEO_local_mutex_map::CNEO_local_mutex_map()
{
}

inline CNEO_local_mutex_map::~CNEO_local_mutex_map()
{
}

inline bool CNEO_local_mutex_map::try_acquire_mutex(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	navolockid oNAVOLockId;
	
	oNAVOLockId.m_class = nClass;
	oNAVOLockId.m_typeid= nTypeId;
	oNAVOLockId.m_idobj = nIdObj;
	oNAVOLockId.m_extra = nExtra;
	long nDummy;
	if(m_oMutexMap.Lookup(oNAVOLockId,nDummy))
	{
		return false;
	}
	m_oMutexMap[ oNAVOLockId ] = true;
	return true;
}

inline void CNEO_local_mutex_map::release_mutex(long nClass,long nTypeId,long nIdObj,long nExtra)
{
	navolockid oNAVOLockId;
	
	oNAVOLockId.m_class = nClass;
	oNAVOLockId.m_typeid= nTypeId;
	oNAVOLockId.m_idobj = nIdObj;
	oNAVOLockId.m_extra = nExtra;
	
	VERIFY(m_oMutexMap.RemoveKey(oNAVOLockId));
}

#if defined(_NAVODOTNET) || defined(NAVO2008)
template<> inline UINT AFXAPI HashKey<const navolockid&> (const navolockid& key)
{
	//hash oparty o IdObj (najwiêksza zmiennoœæ)
	return (DWORD) (key.m_idobj & 0x0000ffff);
}

#endif

#else
	#error __FILE__ already included
#endif
