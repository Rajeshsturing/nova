/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNAVOLockObject
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNEO_vlock::CNEO_vlock(CNEO_trans * poTrans,long nClass,long nTypeId,long nIdObj,long nExtra):
		m_poTrans(poTrans),
		m_nClass(nClass),
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj),
		m_nExtra(nExtra),
		m_bOwnsLock(false),
		m_bFlush(true)
{
	ASSERT(poTrans != NULL);
	EnableAutomation();
	
	m_poTrans->AddRef_VLock();
}

CNEO_vlock::~CNEO_vlock()
{
	_unlock();
	
	m_poTrans->Release_VLock();
}

bool CNEO_vlock::_lock()
{
	if(!m_bOwnsLock)
	{
		m_bOwnsLock = m_poTrans->aquire_write_lock(m_nClass,m_nTypeId,m_nIdObj,m_nExtra);
	}
	return m_bOwnsLock;
}

void CNEO_vlock::_unlock()
{
	if(m_bOwnsLock)
	{
		m_poTrans->release_write_lock(m_nClass,m_nTypeId,m_nIdObj,m_nExtra);
		if(m_bFlush)
		{
			m_poTrans->flush_pending_unlocks();
		}
	}
	m_bOwnsLock = false;
}

//{{AFX_MSG_MAP(CNEO_vlock)
//}}AFX_MSG_MAP
BEGIN_DISPATCH_MAP(CNEO_vlock, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_vlock)
	DISP_FUNCTION(CNEO_vlock, "lock", LockAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_vlock, "unlock", UnlockAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL CNEO_vlock::LockAUTO() 
{
	ALL_TRY
	{
		return _lock() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_vlock::UnlockAUTO() 
{
	ALL_TRY
	{
		_unlock();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//----------------------------------------------------------
//{{AFX_MSG_MAP(CNEO_mutex_holder_auto)
//}}AFX_MSG_MAP
BEGIN_DISPATCH_MAP(CNEO_mutex_holder_auto, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_mutex_holder_auto)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

CNEO_mutex_holder_auto::CNEO_mutex_holder_auto(CNEO_trans * poTrans,long nClass,long nTypeId,long nIdObj,long nExtra) :
	m_poTrans(poTrans),
	m_nClass(nClass),
	m_nTypeId(nTypeId),
	m_nIdObj(nIdObj),
	m_nExtra(nExtra)
{
	ASSERT(poTrans != NULL);
	EnableAutomation();
	m_poTrans->AddRef();
	TRACE("mutex created (%d,%d,%d,%d)\n",m_nClass,m_nTypeId,m_nIdObj,m_nExtra);
}

CNEO_mutex_holder_auto::~CNEO_mutex_holder_auto()
{
	TRACE("mutex destroyed (%d,%d,%d,%d)\n",m_nClass,m_nTypeId,m_nIdObj,m_nExtra);
	m_poTrans->on_mutex_destroyed(m_nClass,m_nTypeId,m_nIdObj,m_nExtra);
	m_poTrans->Release();
}


