/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNEO_cursor implementation
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\InterfaceUtil.h"
#include "..\include\progressgadget.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "cursorcollection.h"
#include "transrollback.h"
#include "transaction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOOBJ_Instance;

CNEO_cursor::CNEO_cursor(CNEO_trans * poTransaction,
	long TypeId,LPCTSTR lpWhereClause,LPCTSTR lpOrderByClause,LPCTSTR lpJoinClause) :
	m_poTransactionSP(NewSCP(poTransaction,true)),
	m_nTypeId(TypeId),
	m_oWhereClauseString(lpWhereClause ? lpWhereClause : ""),
	m_oOrderByClauseString(lpOrderByClause ? lpOrderByClause : ""),
	m_oJoinClauseString(lpJoinClause ? lpJoinClause : ""),
	m_nPageOffset(0),
	m_bForwarOnly(true),
	m_nTotalCount(-1),
	m_nTop(0)
{
	EnableAutomation();
}

CNEO_cursor::CNEO_cursor(CNEO_trans * poTransaction,long TypeId,SCP<INAVOObjectCollection> poObjectCollectionSP) :
	m_poTransactionSP(NewSCP(poTransaction,true)),
	m_pRPC_oObjectCollectionSP(poObjectCollectionSP),
	m_nTypeId(TypeId),
	m_nPageOffset(0),
	m_bForwarOnly(true),
	m_nTotalCount(-1),
	m_nTop(0)
{
	EnableAutomation();
}

CNEO_cursor::~CNEO_cursor()
{
}

void CNEO_cursor::OnFinalRelease()
{
	delete this;
}

void __ReadIdArrayFromFlatData(CFlatData & roFlatData,CArray< long, long &> & roIdentArray);

void CNEO_cursor::__ReadFromDB(long nAbsPos)
{
	if(m_pRPC_oObjectCollectionSP.PointsNull())
	{
		ASSERT(m_poTransactionSP.PointsObject());
		m_pRPC_oObjectCollectionSP = m_poTransactionSP->fwd_open_cursor(m_nTypeId,
			m_oWhereClauseString,m_oOrderByClauseString,m_oJoinClauseString,m_bForwarOnly,m_nTop);
	}
	long nPageSize = 
#ifdef _DEBUG
		5
#else
		100
#endif
		;

	fetchdirection eFetchDir = fdir_abs;

	if(m_bForwarOnly)
	{
		if(m_nPageOffset > nAbsPos)
		{
			ThrowNavoException2(ERCO_CURCOL_FORWARONLY,IDPAGE_NOTAVAILABLE,nAbsPos+1,m_nPageOffset);
		}
		//
		nPageSize = max(1 + nAbsPos - m_nPageOffset,nPageSize);
		nAbsPos = m_nPageOffset + m_oIdents.GetSize();
		eFetchDir = fdir_next;
		ASSERT(nPageSize < 10000);		//coœ za du¿o na raz....
	}

	long nDataLength = 0;
	BYTE * pData = NULL;
	CRemoteFreeHolder oFreeHolder(pData);
	
	HRESULT hr = S_OK;

	if(IsNXMTransport())
	{
		SAFEARRAY * pSABinData;
		hr = m_pRPC_oObjectCollectionSP->Fetch2(eFetchDir, &nPageSize, &nDataLength, &pSABinData, nAbsPos);
	
		if(hr == S_OK)
		{
			void * _pData;
			SafeArrayAccessData(pSABinData, &_pData);
			pData = new BYTE[nDataLength];
			memcpy(pData, _pData, nDataLength);
			SafeArrayUnaccessData(pSABinData);
			SafeArrayDestroy(pSABinData);
		}
	}
	else
	{
		hr = m_pRPC_oObjectCollectionSP->Fetch(eFetchDir,&nPageSize,&nDataLength,&pData,nAbsPos);
	}

	if(hr != S_OK)
	{
		ThrowFromInterface(m_pRPC_oObjectCollectionSP);
	}
	
	if(nPageSize > 0)
	{
		m_oIdents.RemoveAll();
		ASSERT(nDataLength && pData);
			CFlatData oFlatData(nDataLength,pData);
		__ReadIdArrayFromFlatData( oFlatData, m_oIdents );
		ASSERT(m_oIdents.GetSize() == nPageSize);
		m_nPageOffset = nAbsPos;
	}
	
	if(IsNXMTransport())
	{
		oFreeHolder.Release();
	}
}

bool CNEO_cursor::Refresh(long nPositionToKeep)
{
	if(m_pRPC_oObjectCollectionSP.PointsNull())
	{
		return true;
	}
	HRESULT hr = m_pRPC_oObjectCollectionSP->Refresh(nPositionToKeep,&m_nTotalCount);
	if(hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_pRPC_oObjectCollectionSP);
	}
	return (hr == S_OK);
}

long CNEO_cursor::GetTotalCount()
{
	if(m_nTotalCount == -1)
	{
		if(m_pRPC_oObjectCollectionSP.PointsNull())
		{
			ASSERT(m_poTransactionSP.PointsObject());
			m_pRPC_oObjectCollectionSP = m_poTransactionSP->fwd_open_cursor(m_nTypeId,
				m_oWhereClauseString,m_oOrderByClauseString,m_oJoinClauseString,m_bForwarOnly,m_nTop);
		}
		CAfxResourceHandleHolder oARHH(_h_NAVOOBJ_Instance);
		CString oMsgString;
		oMsgString.LoadString(IDS_COMPUTINGTOTALCOUNT);
		SCP<CPerformingDialogHolder> poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));

		HRESULT hr = m_pRPC_oObjectCollectionSP->GetCount(&m_nTotalCount);
		if(hr != S_OK)
		{
			ThrowFromInterface(m_pRPC_oObjectCollectionSP);
		}
		ASSERT(m_nTotalCount != -1);
	}
	return m_nTotalCount;
}

bool CNEO_cursor::SafeGet(long nIndex,SCP<CNEO_user> & rpoStdObjSP,bool bReturnObject)
{
	if(m_nTotalCount != -1)
	{
		if(nIndex >= m_nTotalCount)
		{
			return false;
		}
	}
	if(m_nPageOffset > nIndex || nIndex >= m_nPageOffset + m_oIdents.GetSize())
	{
		__ReadFromDB(nIndex);
		if(m_nPageOffset > nIndex || nIndex >= m_nPageOffset + m_oIdents.GetSize())
		{
			return false;
		}
	}
	
	ASSERT(m_oIdents[nIndex - m_nPageOffset] != 0);
	if(bReturnObject)
	{
		//info: _get_object dostaje ostatnie parametry 0,0 poniewa¿ 
		//narazie nie pozwalamy na kursory po dzieciach - musz¹ byæ po ojcach
		//jak ktoœ chce siê iterowaæ po dzieciach to ma listê
		rpoStdObjSP = m_poTransactionSP->_get_object(m_nTypeId,m_oIdents[ nIndex - m_nPageOffset],0,0);
	}
	return true;
}

SCP<CNEO_cursor> CNEO_cursor::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetCC = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetCC);
	CNEO_cursor * poCursorCollection = dynamic_cast<CNEO_cursor*>(poCmdTargetCC);
	ASSERT(poCursorCollection);
	return NewSCP(poCursorCollection,true);
}

SCP<CNEO_cursorIterator> CNEO_cursor::CreateIterator()
{
	return NewSCP(new CNEO_cursorIterator(NewSCP(this,true)));
}

//{{AFX_MSG_MAP(CNEO_cursor)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_cursor, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_cursor)
	DISP_PROPERTY_EX(CNEO_cursor, "forwardonly", GetForwardonlyAUTO, SetForwardonlyAUTO, VT_BOOL)
	DISP_PROPERTY_EX(CNEO_cursor, "top", GetTopAUTO, SetTopAUTO, VT_I4)
	DISP_FUNCTION(CNEO_cursor, "get", GetAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CNEO_cursor, "exists", ExistsAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CNEO_cursor, "createiterator", CreateIteratorAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX_ID(CNEO_cursor, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	DISP_FUNCTION(CNEO_cursor, "count", GetTotalCountAUTO, VT_I4, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPUNKNOWN CNEO_cursor::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CArrayEnumerator< SCP<CNEO_user> > > poNewArrayEnumSP = NewSCP(new CArrayEnumerator< SCP<CNEO_user> >(*this));
		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

void CNEO_cursor::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","cursor");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_cursor::GetAUTO(long Index) 
{
	ALL_TRY
	{
		ASSERT(Index > 0);
		SCP<CNEO_user> poStdObjSP;
		if(!SafeGet(Index-1,poStdObjSP,true))
		{
			ThrowNavoException1(ERCO_CURCOL_GET_BAD_INDEX,IDPAGE_NOTAVAILABLE,Index);
		}
		if(poStdObjSP.PointsObject())
		{
			return poStdObjSP->GetDispatch(true);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CNEO_cursor::ExistsAUTO(long Index) 
{
	ALL_TRY
	{
		if(Index <= 0)		//wiadomo ¿e nie ma
		{
			return FALSE;
		}

		SCP<CNEO_user> poStdObjSP;
		return SafeGet(Index-1,poStdObjSP,false) != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CNEO_cursor::GetForwardonlyAUTO() 
{
	return GetForwardOnly() != false;
}

void CNEO_cursor::SetForwardonlyAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		if(m_pRPC_oObjectCollectionSP.PointsObject())
		{
			ThrowNavoException(ERCO_CURCOL_TO_LATE_CHANGED_FORWARONLY,IDPAGE_NOTAVAILABLE);
		}
		SetForwardOnly(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNEO_cursor::GetTopAUTO()
{
	return GetTop();
}

long CNEO_cursor::GetTotalCountAUTO()
{
	ALL_TRY
	{
		return GetTotalCount();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_cursor::SetTopAUTO(long nTop)
{
	ALL_TRY
	{
		if(m_pRPC_oObjectCollectionSP.PointsObject())
		{
			ThrowNavoException(ERCO_CURCOL_TO_LATE_SET_TOP,IDPAGE_NOTAVAILABLE);
		}
		SetTop(nTop);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH CNEO_cursor::CreateIteratorAUTO() 
{
	ALL_TRY
	{
		return CreateIterator()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNEO_cursorIterator
/////////////////////////////////////////////////////////////////////////////

CNEO_cursorIterator::CNEO_cursorIterator(SCP<CNEO_cursor> & rpoManagedCursorCollectionSP) :
	m_poManagedCursorCollectionSP(rpoManagedCursorCollectionSP),
	m_nRecordNr(0 /*BOF*/)
{
	EnableAutomation();
}

CNEO_cursorIterator::~CNEO_cursorIterator()
{
}

void CNEO_cursorIterator::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}


//{{AFX_MSG_MAP(CNEO_cursorIterator)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_cursorIterator, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_cursorIterator)
	DISP_FUNCTION(CNEO_cursorIterator, "gofirst", GoFirstAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "golast", GoLastAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "gonext", GoNextAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "goprev", GoPrevAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "goto", GoTo, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CNEO_cursorIterator, "get", GetAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "refresh", RefreshAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_cursorIterator, "isempty", IsEmptyAUTO, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ICursorCollectionIterator to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9900F9B6-28C4-46F2-98E4-C582F7259C30}
static const IID IID_ICursorCollectionIterator =
{ 0x9900f9b6, 0x28c4, 0x46f2, { 0x98, 0xe4, 0xc5, 0x82, 0xf7, 0x25, 0x9c, 0x30 } };

BEGIN_INTERFACE_MAP(CNEO_cursorIterator, CCmdTarget)
	INTERFACE_PART(CNEO_cursorIterator, IID_ICursorCollectionIterator, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNEO_cursorIterator message handlers

BOOL CNEO_cursorIterator::GoFirstAUTO() 
{
	ALL_TRY
	{
		ASSERT(!m_poManagedCursorCollectionSP->GetForwardOnly());
		if(m_poManagedCursorCollectionSP->ExistsAUTO(1))
		{
			m_nRecordNr = 1;
			return TRUE;
		}
		return FALSE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::GoLastAUTO() 
{
	ALL_TRY
	{
		ASSERT(!m_poManagedCursorCollectionSP->GetForwardOnly());
		RefreshAUTO();
		m_nRecordNr = m_poManagedCursorCollectionSP->GetTotalCount();
		ASSERT(m_nRecordNr >= 0);
		return m_nRecordNr > 0;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::GoNextAUTO() 
{
	ALL_TRY
	{
		ASSERT(!m_poManagedCursorCollectionSP->GetForwardOnly());
		if(m_poManagedCursorCollectionSP->ExistsAUTO(m_nRecordNr+1))
		{
			m_nRecordNr++;
			return TRUE;
		}
		return FALSE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::GoPrevAUTO() 
{
	ALL_TRY
	{
		ASSERT(!m_poManagedCursorCollectionSP->GetForwardOnly());
		if(m_poManagedCursorCollectionSP->ExistsAUTO(m_nRecordNr-1))
		{
			m_nRecordNr--;
			return TRUE;
		}
		return FALSE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::GoTo(long nRecordNumber) 
{
	ALL_TRY
	{
		ASSERT(!m_poManagedCursorCollectionSP->GetForwardOnly());
		if(m_poManagedCursorCollectionSP->ExistsAUTO(nRecordNumber))
		{
			m_nRecordNr = nRecordNumber;
			return TRUE;
		}
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH CNEO_cursorIterator::GetAUTO() 
{
	ALL_TRY
	{
		ASSERT(m_nRecordNr != 0);	//Go* operation reguired first
		return m_poManagedCursorCollectionSP->GetAUTO(m_nRecordNr);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::RefreshAUTO() 
{
	ALL_TRY
	{
		return (m_poManagedCursorCollectionSP->Refresh(m_nRecordNr) != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_cursorIterator::IsEmptyAUTO()
{
	ALL_TRY
	{
		return (m_poManagedCursorCollectionSP->ExistsAUTO(1) == FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
