// LockingManager.cpp : implementation file
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"	//lockinfo hash
#include "..\include\clientinfo.h"		//client info
#include "..\include\navoclassfactory.h"
#include "LockingManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLockingManager

IMPLEMENT_DYNCREATE(CLockingManager, CCmdTargetInterface)

DELEGATE_UNKNOWN_INTERFACE(CLockingManager, CntResourceManager)
DELEGATE_UNKNOWN_INTERFACE(CLockingManager, LockManager)
DELEGATE_UNKNOWN_INTERFACE(CLockingManager, NavoErrorInfo)

CLockingManager::CLockingManager()
{
	EnableAutomation();
	AfxOleLockApp();

#ifdef _DEBUG
	m_nRequests = 0;
	m_nSingleLockRequests = 0;
	m_nReadLocks = 0;
	m_nWriteLocks = 0;
	m_nCollisions = 0;
#endif
}

CLockingManager::~CLockingManager()
{
#ifdef _DEBUG
	ShowStatistics();
#endif
	AfxOleUnlockApp();
}


void CLockingManager::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CLockingManager, CCmdTargetWithErrorInfo)
	//{{AFX_MSG_MAP(CLockingManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLockingManager, CCmdTargetWithErrorInfo)
	//{{AFX_DISPATCH_MAP(CLockingManager)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CLockingManager, CCmdTargetInterface)
	INTERFACE_PART(CLockingManager, IID_INavoErrorInfo, NavoErrorInfo)
	INTERFACE_PART(CLockingManager, IID_ILockManager, LockManager)
	INTERFACE_PART(CLockingManager, IID_ICntResourceManager, CntResourceManager)
END_INTERFACE_MAP()

// {188cb153-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CLockingManager, "navodb.lockmanager", 0x188cb153, 0x82a4, 0x4498, 0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CLockingManager message handlers

STDMETHODIMP CLockingManager::XLockManager::
Advise(LPCSTR pcUserName, LPCSTR pcComputerName, long *pCookie)
{
	METHOD_PROLOGUE(CLockingManager, LockManager)

		ALL_TRY
	{
#ifdef _UNICODE
#pragma message( "Unicode todo" )
		ASSERT(false);
#else
		*pCookie = 0;
		SCP<CClientInfo> poClientInfoSP = NewSCP(new CClientInfo(pcUserName, pcComputerName));
		*pCookie = reinterpret_cast<long>(poClientInfoSP.Get());
		CSimpleLock oSlock(pThis->m_oCS);
		pThis->m_oClientInfoMap[*pCookie] = poClientInfoSP;
#endif
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XLockManager::
UnAdvise(long nCookie)
{
	METHOD_PROLOGUE(CLockingManager, LockManager)

		ALL_TRY
	{
		pThis->FreeClient(nCookie);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XLockManager::
Lock(long nOriginatorCookie, BYTE bLock, long nCount, const navolock * pNavoLock)
{
	METHOD_PROLOGUE(CLockingManager, LockManager)

		ALL_TRY
	{
		/*
			mo¿liwa optymalizacja, gdyby locki stanowi³y w¹skie gard³o:
			zamiast jednego oSlocka i jednej mapy na wszystkie obiekty,
			mo¿na stosowaæ n map (np. 16) i hashowaæ dostêp do nich na bazie np.
			IdObj % 16 - w ten sposób 16 w¹tków bêdzie mog³o prawie jednoczeœnie pracowaæ
			(z regu³y nCount = 1)
		*/
		CSimpleLock oSlock(pThis->m_oCS);

#ifdef _DEBUG
		pThis->m_nRequests++;
		if (nCount == 1)
		{
			pThis->m_nSingleLockRequests++;
		}

		{
			for (long i = 0; i < nCount; i++)
			{
				ASSERT(pNavoLock[i].m_fullid.m_class == LOCKCLASS_OBJECT ||
					pNavoLock[i].m_fullid.m_class == LOCKCLASS_OPERATION);
			}
		}
#endif

		if (bLock)
		{
			//first check (or lock immediatelly when single item is locked)
			for (long iter = 0; iter < nCount; iter++)
			{
				if (pNavoLock[iter].m_type & nlt_exlock)
				{
					if (!pThis->raw_CreateWriteLock(nOriginatorCookie, pNavoLock + iter, nCount != 1))
					{
						goto in_use;
					}
				}
				if (pNavoLock[iter].m_type & nlt_shlock)
				{
					ASSERT(false);	//dobre, ale na razie nie u¿ywane
					if (!pThis->raw_CreateReadLock(nOriginatorCookie, pNavoLock + iter, nCount != 1))
					{
						goto in_use;
					}
				}
			}
			if (nCount != 1)
			{
				//then lock
				for (long iter = 0; iter < nCount; iter++)
				{
					if (pNavoLock[iter].m_type & nlt_exlock)
					{
						VERIFY(pThis->raw_CreateWriteLock(nOriginatorCookie, pNavoLock + iter, false));
					}
					if (pNavoLock[iter].m_type & nlt_shlock)
					{
						ASSERT(false);	//dobre, ale nie u¿ywane
						VERIFY(pThis->raw_CreateReadLock(nOriginatorCookie, pNavoLock + iter, false));
					}
				}
			}
			return S_OK;
		in_use:
			{
				//create hume readable information
				CString oDescriptionString;
				NavoFormatErrorMsg(oDescriptionString, ERCO_LOCK_IMPOSS_BECAUSE_OTHERS);

				pThis->GetErrorStorage() +=
					CNavoErrorInfo(ERCO_LOCK_IMPOSS_BECAUSE_OTHERS, IDPAGE_NOTAVAILABLE,
						oDescriptionString);
			}

#ifdef _DEBUG
			pThis->m_nCollisions++;
#endif

			return S_FALSE;
		}
		else
		{
			for (long iter = 0; iter < nCount; iter++)
			{
				if (pNavoLock[iter].m_type & nlt_exlock)
				{
					pThis->raw_FreeWriteLock(nOriginatorCookie, pNavoLock + iter);
				}
				if (pNavoLock[iter].m_type & nlt_shlock)
				{
					ASSERT(false);	//dobre, ale nie u¿ywane
					pThis->raw_FreeReadLock(nOriginatorCookie, pNavoLock + iter);
				}
			}
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XLockManager::Lock_AddItem(long iInx, long iClass, long iTypeid, long iIdObj, long iExtra, long iLockType)
{
	METHOD_PROLOGUE(CLockingManager, LockManager)

		ALL_TRY
	{
		navolock & rLock = pThis->m_arrLocks[iInx];

		rLock.m_fullid.m_class = iClass;
		rLock.m_fullid.m_typeid = iTypeid;
		rLock.m_fullid.m_idobj = iIdObj;
		rLock.m_fullid.m_extra = iExtra;
		rLock.m_type = (navolocktype)iLockType;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CLockingManager::XLockManager::Lock2(long iOriginatorCookie, boolean bLock, long iCount)
{
	METHOD_PROLOGUE(CLockingManager, LockManager)

		ALL_TRY
	{
		return Lock(iOriginatorCookie, bLock, iCount, pThis->m_arrLocks);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
}

///////////////////////////////////////////////////////////////////////////////////
//		create lock
///////////////////////////////////////////////////////////////////////////////////

bool CLockingManager::raw_CreateWriteLock(long nOriginatorCookie, const navolock * pNavoLock, bool bTest)
{
	ASSERT(pNavoLock);
	ASSERT(pNavoLock->m_type & nlt_exlock);

#ifdef _DEBUG
	m_nWriteLocks++;
#endif

	CReadLockOwnerArray oRLOwnerArray;

	//czy s¹ readlocki
	if (m_oReadLockMap.Lookup(pNavoLock->m_fullid, oRLOwnerArray))
	{
		ASSERT(oRLOwnerArray.GetSize() >= 1);
		if (oRLOwnerArray.GetSize() == 1)		//tylko jeden - mo¿e to my
		{
			if (oRLOwnerArray[0] != nOriginatorCookie)
			{
				return false;	//ktoœ inny
			}
		}
		else
		{
			return false;			//wiêcej ni¿ jeden - nie mo¿na zrobiæ write locka
		}
	}
	else
	{
		ASSERT(oRLOwnerArray.GetSize() == 0);
	}

	long nLockOwner = 0;
	if (m_oWriteLockMap.Lookup(pNavoLock->m_fullid, nLockOwner))
	{
		if (nLockOwner == nOriginatorCookie)
		{
			//b³¹d wewnêtrzny klienta: ju¿ posiada writelock
			SCP<CClientInfo> poClientInfoSP;
			VERIFY(m_oClientInfoMap.Lookup(nOriginatorCookie, poClientInfoSP));

			ThrowNavoException4(ERCO_LOCK_ALREADY_HAS_WRITE_LOCK, IDPAGE_NOTAVAILABLE,
				pNavoLock->m_fullid.m_class,
				pNavoLock->m_fullid.m_typeid,
				pNavoLock->m_fullid.m_idobj,
				CString(poClientInfoSP->GetUserName()));
		}
		else
		{
			return false;		//ma to ktoœ inny
		}
	}
	if (!bTest)
	{
		m_oWriteLockMap[pNavoLock->m_fullid] = nOriginatorCookie;

		TRACE(_T("EX-LOCK:%d,%d,%d for %d\n"),
			pNavoLock->m_fullid.m_class,
			pNavoLock->m_fullid.m_typeid,
			pNavoLock->m_fullid.m_idobj,
			nOriginatorCookie);
	}
	return true;
}

bool CLockingManager::raw_CreateReadLock(long nOriginatorCookie, const navolock * pNavoLock, bool bTest)
{
	ASSERT(pNavoLock);
	ASSERT(pNavoLock->m_type & nlt_shlock);
	ASSERT(!(pNavoLock->m_type & nlt_exlock));

#ifdef _DEBUG
	m_nReadLocks++;
#endif

	long nLockOwner = 0;
	if (m_oWriteLockMap.Lookup(pNavoLock->m_fullid, nLockOwner))
	{
		//ktoœ inny ma ju¿ writelock
		if (nLockOwner != nOriginatorCookie)
		{
			return false;
		}
	}

	CReadLockOwnerArray oRLOwnerArray;
	if (m_oReadLockMap.Lookup(pNavoLock->m_fullid, oRLOwnerArray))
	{
		for (long iter = 0; iter <= oRLOwnerArray.GetUpperBound(); iter++)
		{
			if (oRLOwnerArray[iter] == nOriginatorCookie)
			{
				//b³¹d wewnêtrzny klienta: ju¿ posiada readlock
				SCP<CClientInfo> poClientInfoSP;
				VERIFY(m_oClientInfoMap.Lookup(nOriginatorCookie, poClientInfoSP));

				ThrowNavoException4(ERCO_LOCK_ALREADY_HAS_READ_LOCK, IDPAGE_NOTAVAILABLE,
					pNavoLock->m_fullid.m_class,
					pNavoLock->m_fullid.m_typeid,
					pNavoLock->m_fullid.m_idobj,
					CString(poClientInfoSP->GetUserName()));
			}
		}
	}
	else
	{
		ASSERT(oRLOwnerArray.GetSize() == 0);
	}
	if (!bTest)
	{
		oRLOwnerArray.Add(nOriginatorCookie);
		m_oReadLockMap.SetAt(pNavoLock->m_fullid, oRLOwnerArray);

		TRACE(_T("SH-LOCK:%d,%d,%d for %d of (%d)\n"),
			pNavoLock->m_fullid.m_class,
			pNavoLock->m_fullid.m_typeid,
			pNavoLock->m_fullid.m_idobj,
			nOriginatorCookie, oRLOwnerArray.GetSize());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//		free lock (unlock)
//////////////////////////////////////////////////////////////////////////////////////////////

bool CLockingManager::raw_CleanReadLock_(long nOriginatorCookie, const navolockid * pLockid,
	CReadLockOwnerArray & roRLOwners)
{
	ASSERT(pLockid);
	bool bHadLock = false;
	for (long iter = 0; iter <= roRLOwners.GetUpperBound(); iter++)
	{
		if (roRLOwners[iter] == nOriginatorCookie)
		{
			roRLOwners.RemoveAt(iter);
			bHadLock = true;
			break;
		}
	}
	if (!bHadLock)
	{
		return false;	//error: nie posiada readlock lub czyszczenie po kliencie
	}

	if (roRLOwners.GetSize() == 0)
	{
		VERIFY(m_oReadLockMap.RemoveKey(*pLockid));	//usuñ w ogóle
	}
	else
	{
		m_oReadLockMap.SetAt(*pLockid, roRLOwners);	//zast¹p zmniejszon¹ list¹ klientów
	}

	TRACE(_T("SH-UNLOCK:%d,%d,%d for %d of (%d)\n"),
		pLockid->m_class,
		pLockid->m_typeid,
		pLockid->m_idobj,
		nOriginatorCookie, roRLOwners.GetSize());
	return true;
}

void CLockingManager::raw_FreeWriteLock(long nOriginatorCookie, const navolock * pNavoLock)
{
	ASSERT(pNavoLock->m_type & nlt_exlock);

	long nLockOwner = 0;
	if (!m_oWriteLockMap.Lookup(pNavoLock->m_fullid, nLockOwner))
	{
		//b³¹d: nie posiada writelock
		SCP<CClientInfo> poClientInfoSP;
		VERIFY(m_oClientInfoMap.Lookup(nOriginatorCookie, poClientInfoSP));

		ThrowNavoException4(ERCO_LOCK_NO_WRITE_LOCK_TO_FREE, IDPAGE_NOTAVAILABLE,
			pNavoLock->m_fullid.m_class,
			pNavoLock->m_fullid.m_typeid,
			pNavoLock->m_fullid.m_idobj,
			CString(poClientInfoSP->GetUserName()));
	}
	VERIFY(m_oWriteLockMap.RemoveKey(pNavoLock->m_fullid));

	TRACE(_T("EX-UNLOCK:%d,%d,%d for %d\n"),
		pNavoLock->m_fullid.m_class,
		pNavoLock->m_fullid.m_typeid,
		pNavoLock->m_fullid.m_idobj,
		nOriginatorCookie);
}


void CLockingManager::raw_FreeReadLock(long nOriginatorCookie, const navolock * pNavoLock)
{
	ASSERT(pNavoLock);
	ASSERT(pNavoLock->m_type & nlt_shlock);
	ASSERT(!(pNavoLock->m_type & nlt_exlock));

	CReadLockOwnerArray oRLOwners;
	if (m_oReadLockMap.Lookup(pNavoLock->m_fullid, oRLOwners))
	{
		if (raw_CleanReadLock_(nOriginatorCookie, &pNavoLock->m_fullid, oRLOwners))
		{
			return;	//posz³o g³adko
		}
	}

	//b³¹d: nie posiada readlock
	SCP<CClientInfo> poClientInfoSP;
	VERIFY(m_oClientInfoMap.Lookup(nOriginatorCookie, poClientInfoSP));

	ThrowNavoException4(ERCO_LOCK_NO_READ_LOCK_TO_FREE, IDPAGE_NOTAVAILABLE,
		pNavoLock->m_fullid.m_class,
		pNavoLock->m_fullid.m_typeid,
		pNavoLock->m_fullid.m_idobj,
		CString(poClientInfoSP->GetUserName()));
}

void CLockingManager::FreeClient(long nCookie)
{
	TRACE1("FREE-CLIENT UNLOCK for %d\n", nCookie);

	CSimpleLock oSlock(m_oCS);


#ifdef _DEBUG
	SCP<CClientInfo> poClientInfoSP;
	ASSERT(m_oClientInfoMap.Lookup(nCookie, poClientInfoSP));
	poClientInfoSP = 0;
#endif

	VERIFY(m_oClientInfoMap.RemoveKey(nCookie));
	POSITION pos = m_oWriteLockMap.GetStartPosition();
	while (pos)
	{
		navolockid oDummy;
		long nLockOwner;
		m_oWriteLockMap.GetNextAssoc(pos, oDummy, nLockOwner);
		if (nLockOwner == nCookie)
		{
			VERIFY(m_oWriteLockMap.RemoveKey(oDummy));
		}
	}
	pos = m_oReadLockMap.GetStartPosition();
	while (pos)
	{
		navolock oDummy;
		CReadLockOwnerArray oRLOwnerArray;
		m_oReadLockMap.GetNextAssoc(pos, oDummy.m_fullid, oRLOwnerArray);
		raw_CleanReadLock_(nCookie, &oDummy.m_fullid, oRLOwnerArray);	//ignoruj rezultat
	}
	TRACE1("FREE-CLIENT UNLOCK complete\n", nCookie);

	TRACE1("FREE-CLIENT RELEASE RESOURCES for %d\n", nCookie);

	CSimpleLock oSlock2(m_oResourceCS);
	pos = m_oResourceMap.GetStartPosition();
	while (pos)
	{
		CString oResName;
		SCP<CResourceInfo> poResourceSP;
		m_oResourceMap.GetNextAssoc(pos, oResName, poResourceSP);
		while (poResourceSP->ReleaseUsage(nCookie))
		{
			;
		}
	}
	TRACE1("FREE-CLIENT RELEASE RESOURCES complete %d\n", nCookie);
}


//------------------------------------------------------------------------------------------------
//	IResourceManager implementation
//
//------------------------------------------------------------------------------------------------
STDMETHODIMP CLockingManager::XCntResourceManager::
CreateResource(LPCSTR pcResName, long nMaxUsage)
{
	METHOD_PROLOGUE(CLockingManager, CntResourceManager)

		ALL_TRY
	{
		CSimpleLock oSlock(pThis->m_oResourceCS);
		SCP<CResourceInfo> poResourceInfoSP = pThis->_raw_seach_resource(pcResName);
		if (poResourceInfoSP.PointsObject())
		{
			return S_FALSE;
		}
		poResourceInfoSP = NewSCP(new CResourceInfo());
		poResourceInfoSP->_set_max_usage(nMaxUsage);
		pThis->m_oResourceMap[pcResName] = poResourceInfoSP;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XCntResourceManager::
DeleteResource(LPCSTR pcResName)
{
	METHOD_PROLOGUE(CLockingManager, CntResourceManager)

		ALL_TRY
	{
		CSimpleLock oSlock(pThis->m_oResourceCS);
		SCP<CResourceInfo> poResourceInfoSP = pThis->_raw_seach_resource(pcResName);
		if (poResourceInfoSP.PointsNull())
		{
			return ERROR_RESOURCE_NAME_NOT_FOUND;
		}
		if (poResourceInfoSP->GetUsage() != 0)
		{
			return S_FALSE;		//in use
		}
		VERIFY(pThis->m_oResourceMap.RemoveKey(pcResName));
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XCntResourceManager::
UseResource(LPCSTR pcResName, long nOriginatorCookie)
{
	METHOD_PROLOGUE(CLockingManager, CntResourceManager)

		ALL_TRY
	{
		CSimpleLock oSlock(pThis->m_oResourceCS);
		SCP<CResourceInfo> poResourceInfoSP = pThis->_raw_seach_resource(pcResName);
		if (poResourceInfoSP.PointsNull())
		{
			return  ERROR_RESOURCE_NAME_NOT_FOUND;
		}
		if (nOriginatorCookie == 0)
		{
			return HRESULT(-poResourceInfoSP->GetUsage());
		}
		if (poResourceInfoSP->AddUsage(nOriginatorCookie))
		{
			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CLockingManager::XCntResourceManager::
UseResource2(LPCSTR pcResName, long nOriginatorCookie, long * hr)
{
	*hr = UseResource(pcResName, nOriginatorCookie);

	return S_OK;
}


STDMETHODIMP CLockingManager::XCntResourceManager::
ReleaseResource(LPCSTR pcResName, long nOriginatorCookie)
{
	METHOD_PROLOGUE(CLockingManager, CntResourceManager)

		ALL_TRY
	{
		CSimpleLock oSlock(pThis->m_oResourceCS);
		SCP<CResourceInfo> poResourceInfoSP = pThis->_raw_seach_resource(pcResName);
		if (poResourceInfoSP.PointsNull())
		{
			return  ERROR_RESOURCE_NAME_NOT_FOUND;
		}
		VERIFY(poResourceInfoSP->ReleaseUsage(nOriginatorCookie));
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

bool CLockingManager::CResourceInfo::AddUsage(long nOriginatorCookie)
{
	if (GetSize() >= m_nMaxUsage)
	{
		return false;
	}
	Add(nOriginatorCookie);
	return true;
}

bool CLockingManager::CResourceInfo::ReleaseUsage(long nOriginatorCookie)
{
	for (long iter = 0; iter < GetSize(); iter++)
	{
		if (GetAt(iter) == nOriginatorCookie)
		{
			RemoveAt(iter);
			return true;
		}
	}
	return false;
}


SCP<CLockingManager::CResourceInfo> CLockingManager::_raw_seach_resource(LPCTSTR lpResName)
{
	SCP<CResourceInfo> poResourceSP;

	if (m_oResourceMap.Lookup(lpResName, poResourceSP))
	{
		return poResourceSP;
	}
	else
	{
		return SCP<CResourceInfo>();
	}
}















#ifdef _DEBUG
void CLockingManager::ShowStatistics()
{
	TRACE0("------Lock Manager statistic----------\n");
	TRACE1("Total requests: %d \n", m_nRequests);
	TRACE1("1-item requests: %d \n", m_nSingleLockRequests);
	TRACE1("1-item ratio %d%%\n", ((m_nRequests == 0) ? 0 : (100 * m_nSingleLockRequests) / m_nRequests));
	TRACE1("Collisions %d\n", m_nCollisions);
	TRACE1("Collisions ratio %d%%\n", ((m_nRequests == 0) ? 0 : (100 * m_nCollisions) / m_nRequests));
	TRACE1("Read locks created: %d \n", m_nReadLocks);
	TRACE1("Write locks created: %d\n", m_nWriteLocks);
}
#endif