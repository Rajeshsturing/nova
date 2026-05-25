/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	Locking manager
*/

#if !defined(AFX_LOCKINGMANAGER_H__63B5AEEE_AEAF_4F53_9BF5_79FC3FF7E713__INCLUDED_)
#define AFX_LOCKINGMANAGER_H__63B5AEEE_AEAF_4F53_9BF5_79FC3FF7E713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(_NAVODOTNET) || defined(NAVO2008)
template<> UINT AFXAPI HashKey<const navolockid&>(const navolockid& key);
#endif

class CLockingManager : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CLockingManager)

	CLockingManager();           // protected constructor used by dynamic creation
public:
	//{{AFX_VIRTUAL(CLockingManager)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLockingManager();

	//{{AFX_MSG(CLockingManager)
	//}}AFX_MSG
	BEGIN_INTERFACE_PART(LockManager, ILockManager)
		STDMETHOD(Advise)(LPCSTR pcUserName, LPCSTR pcComputerName, long *pCookie);
	STDMETHOD(UnAdvise)(long nCookie);
	STDMETHOD(Lock)(long nOriginatorCookie, BYTE bLock, long nCount,
		const navolock * pNavoLock);
	STDMETHOD(Lock_AddItem)(long iInx, long iClass, long iTypeid, long iIdObj, long iExtra, long iLockType);
	STDMETHOD(Lock2)(long iOriginatorCookie, boolean bLock, long iCount);
	END_INTERFACE_PART(LockManager)
	BEGIN_INTERFACE_PART(CntResourceManager, ICntResourceManager)
		STDMETHOD(CreateResource)(LPCSTR pcResName, long nMaxUsage);
	STDMETHOD(DeleteResource)(LPCSTR pcResName);
	STDMETHOD(UseResource)(LPCSTR pcResName, long nOriginatorCookie);
	STDMETHOD(ReleaseResource)(LPCSTR pcResName, long nOriginatorCookie);
	STDMETHOD(UseResource2)(LPCSTR pcResName, long nOriginatorCookie, long*hr);
	END_INTERFACE_PART(CntResourceManager)

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLockingManager)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLockingManager)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	class CReadLockOwnerArray : public CArray<long, long &>
	{
	public:
		CReadLockOwnerArray() :
			CArray<long, long &>()
		{
		}
		virtual void operator = (const CReadLockOwnerArray & roRLOwnerArray)
		{
			Copy(roRLOwnerArray);
		}
	};

	CSimpleCriticalSection	m_oCS;
	//{{
	CMap<long, long, SCP<CClientInfo>, SCP<CClientInfo> &> m_oClientInfoMap;	//zarejstrowani klienci
	CMap<navolockid, const navolockid&, long, long&>   m_oWriteLockMap;	//mapa exclusive (write) lockow
	CMap<navolockid, const navolockid&, CReadLockOwnerArray, CReadLockOwnerArray &> m_oReadLockMap;	//mapa shared (read) locków
//}}

//single resource info contains information about current resource users
//and max allowed usage
	class CResourceInfo : public CEnumerableArray_SCP<long, long &>
	{
	public:
		CResourceInfo() :
			m_nMaxUsage(0)
		{
		}
		void _set_max_usage(long nMax)
		{
			m_nMaxUsage = nMax;
		}
		long GetUsage() const
		{
			return GetSize();
		}
		bool AddUsage(long nOriginatorCookie);
		bool ReleaseUsage(long nOriginatorCookie);
	private:
		long	m_nMaxUsage;
	};

	CSimpleCriticalSection	m_oResourceCS;
	//{{
	CMap<CString, LPCTSTR, SCP<CResourceInfo>, SCP<CResourceInfo> &> m_oResourceMap;
	//}}

	//must owe critical section
	SCP<CResourceInfo> _raw_seach_resource(LPCTSTR lpResName);
	/*
		ZASADY:
		1 writelock, wiele readlockow
		ka¿dy lock (read, write) musi mieæ swój unlock
		zrobienie writelock'a nie zak³ada readlock'a
	*/
	void FreeClient(long nCookie);

	//funkcje do u¿ycia w obszarze chronionym (go³e)
	bool raw_CreateReadLock(long nOriginatorCookie, const navolock * pNavoLock, bool bTest);
	void raw_FreeReadLock(long nOriginatorCookie, const navolock * pNavoLock);

	bool raw_CreateWriteLock(long nOriginatorCookie, const navolock * pNavoLock, bool bTest);
	void raw_FreeWriteLock(long nOriginatorCookie, const navolock * pNavoLock);

	bool raw_CleanReadLock_(long nOriginatorCookie, const navolockid * pLockid, CReadLockOwnerArray & roRLOwners);

#ifdef _DEBUG
	void ShowStatistics();
	long m_nRequests;		//liczba wywo³añ funkcji lock
	long m_nSingleLockRequests; //liczba wywo³añ funkcji lock z Count = 1
	long m_nReadLocks;		//liczba za³o¿onych readlockow
	long m_nWriteLocks;		//liczba za³o¿onych writelockow
	long m_nCollisions;		//liczba nieudanych wywo³añ funkcji lock
#endif

	navolock m_arrLocks[100];
};

#if defined(_NAVODOTNET) || defined(NAVO2008)
template<> inline UINT AFXAPI HashKey<const navolockid&>(const navolockid& key)
{
	//hash oparty o IdObj (najwiêksza zmiennoœæ)
	return (DWORD)(key.m_idobj & 0x0000ffff);
}

#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCKINGMANAGER_H__63B5AEEE_AEAF_4F53_9BF5_79FC3FF7E713__INCLUDED_)
