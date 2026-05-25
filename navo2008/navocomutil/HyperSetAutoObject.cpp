/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CHyperSetAutoObject implementuje zbiory par liczb long (x,y) dostêpne
		przez automation
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "HyperSetAutoObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHyperSetAutoObject, CCmdTargetInterface)

CHyperSetAutoObject::CHyperSetAutoObject()
{
	EnableAutomation();
	AfxOleLockApp();
	m_oItemMap.InitHashTable(193);
}

CHyperSetAutoObject::~CHyperSetAutoObject()
{
	AfxOleUnlockApp();
}


void CHyperSetAutoObject::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

SCP<CHyperSetAutoObject> CHyperSetAutoObject::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetHyperSet = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetHyperSet);
	CHyperSetAutoObject * poHyperSet = dynamic_cast<CHyperSetAutoObject*>(poCmdTargetHyperSet);
	ASSERT(poHyperSet);
	return NewSCP(poHyperSet,true);
}


BEGIN_MESSAGE_MAP(CHyperSetAutoObject, CCmdTarget)
	//{{AFX_MSG_MAP(CHyperSetAutoObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CHyperSetAutoObject, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CHyperSetAutoObject)
	DISP_FUNCTION(CHyperSetAutoObject, "exists", ExistsAUTO, VT_BOOL, VTS_I4 VTS_I4)
	DISP_FUNCTION(CHyperSetAutoObject, "add", AddAUTO, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CHyperSetAutoObject, "remove", RemoveAuto, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CHyperSetAutoObject, "or", OrAUTO, VT_DISPATCH, VTS_DISPATCH)
	DISP_FUNCTION(CHyperSetAutoObject, "and", AndAUTO, VT_DISPATCH, VTS_DISPATCH)
	DISP_FUNCTION(CHyperSetAutoObject, "minus", MinusAUTO, VT_DISPATCH, VTS_DISPATCH)
	DISP_FUNCTION(CHyperSetAutoObject, "isempty", IsEmptyAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CHyperSetAutoObject, "empty", EmptyAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CHyperSetAutoObject, "extract", ExtractAUTO, VT_EMPTY, VTS_CY VTS_PVARIANT VTS_PVARIANT)
	DISP_PROPERTY_EX_ID(CHyperSetAutoObject, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {B054FA3E-3DEA-4A2F-A5E7-FDE46F024580}
static const IID IID_IHyperSetAutoObject =
{ 0xb054fa3e, 0x3dea, 0x4a2f, { 0xa5, 0xe7, 0xfd, 0xe4, 0x6f, 0x2, 0x45, 0x80 } };

BEGIN_INTERFACE_MAP(CHyperSetAutoObject, CCmdTarget)
	INTERFACE_PART(CHyperSetAutoObject, IID_IHyperSetAutoObject, Dispatch)
END_INTERFACE_MAP()

// {188cb170-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CHyperSetAutoObject, "navocomutil.hyperset", 0x188cb170,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
void CHyperSetAutoObject::__raw_copy(const CHyperSetAutoObject & roHSAO)
{
	POSITION pos = roHSAO.m_oItemMap.GetStartPosition();
	while(pos)
	{
		mapkey h1;
		mapvalue mv1;
		roHSAO.m_oItemMap.GetNextAssoc(pos, h1, mv1);
		m_oItemMap[ h1 ] = mv1;
	}
}
	
void CHyperSetAutoObject::__copy(const CHyperSetAutoObject & roHSAO)
{
	m_oItemMap.RemoveAll();
	m_oItemMap.InitHashTable(roHSAO.m_oItemMap.GetHashTableSize());
	__raw_copy(roHSAO);
}

void CHyperSetAutoObject::__and(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2)
{
	m_oItemMap.RemoveAll();
	POSITION pos = roHSAO1.m_oItemMap.GetStartPosition();
	while(pos)
	{
		mapkey h1;
		mapvalue mv1,mv2;
		roHSAO1.m_oItemMap.GetNextAssoc(pos, h1, mv1);
		if(roHSAO2.m_oItemMap.Lookup(h1,mv2))
		{
			m_oItemMap[ h1 ] = mv1;
		}
	}
}

void CHyperSetAutoObject::__or(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2)
{
	__copy(roHSAO1);
	__raw_copy(roHSAO2);
}

void CHyperSetAutoObject::__minus(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2)
{
	m_oItemMap.RemoveAll();
	POSITION pos = roHSAO1.m_oItemMap.GetStartPosition();
	while(pos)
	{
		mapkey h1;
		mapvalue mv1,mv2;
		roHSAO1.m_oItemMap.GetNextAssoc(pos, h1, mv1);
		if(!roHSAO2.m_oItemMap.Lookup(h1,mv2))
		{
			m_oItemMap[ h1 ] = mv1;
		}
	}
}

void CHyperSetAutoObject::__add(long TypeId,long IdObj)
{
	m_oItemMap[ longlong(TypeId,IdObj) ] = true;
}

void CHyperSetAutoObject::__remove(long TypeId,long IdObj)
{
	m_oItemMap.RemoveKey( longlong(TypeId,IdObj) );
}

void CHyperSetAutoObject::__empty()
{
	m_oItemMap.RemoveAll();
}

bool CHyperSetAutoObject::__exists(long TypeId,long IdObj) const
{
	mapvalue mv1;
	return m_oItemMap.Lookup(longlong(TypeId,IdObj),mv1) != FALSE;
}

bool CHyperSetAutoObject::__isempty() const
{
	return m_oItemMap.IsEmpty() != FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//      AUTOMATION
/////////////////////////////////////////////////////////////////////////////

BOOL CHyperSetAutoObject::ExistsAUTO(long TypeId,long IdObj) 
{
	ALL_TRY
	{
		return __exists(TypeId,IdObj) != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CHyperSetAutoObject::AddAUTO(long TypeId,long IdObj) 
{
	ALL_TRY
	{
		__add(TypeId,IdObj);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CHyperSetAutoObject::RemoveAuto(long TypeId,long IdObj) 
{
	ALL_TRY
	{
		__remove(TypeId,IdObj);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CHyperSetAutoObject::OrAUTO(LPDISPATCH lpHyperSetDispatch) 
{
	ALL_TRY
	{
		SCP<CHyperSetAutoObject> poHSAOSP = CHyperSetAutoObject::FromIDispatch(lpHyperSetDispatch);
		ASSERT(poHSAOSP.PointsObject());
		SCP<CHyperSetAutoObject> poResultHSAOSP = NewSCP(new CHyperSetAutoObject());
		poResultHSAOSP->__or(*this,*poHSAOSP);
		return poResultHSAOSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CHyperSetAutoObject::AndAUTO(LPDISPATCH lpHyperSetDispatch) 
{
	ALL_TRY
	{
		SCP<CHyperSetAutoObject> poHSAOSP = CHyperSetAutoObject::FromIDispatch(lpHyperSetDispatch);
		ASSERT(poHSAOSP.PointsObject());
		SCP<CHyperSetAutoObject> poResultHSAOSP = NewSCP(new CHyperSetAutoObject());
		poResultHSAOSP->__and(*this,*poHSAOSP);
		return poResultHSAOSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CHyperSetAutoObject::MinusAUTO(LPDISPATCH lpHyperSetDispatch) 
{
	ALL_TRY
	{
		SCP<CHyperSetAutoObject> poHSAOSP = CHyperSetAutoObject::FromIDispatch(lpHyperSetDispatch);
		ASSERT(poHSAOSP.PointsObject());
		SCP<CHyperSetAutoObject> poResultHSAOSP = NewSCP(new CHyperSetAutoObject());
		poResultHSAOSP->__minus(*this,*poHSAOSP);
		return poResultHSAOSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CHyperSetAutoObject::IsEmptyAUTO() 
{
	ALL_TRY
	{
		return __isempty() != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CHyperSetAutoObject::EmptyAUTO() 
{
	ALL_TRY
	{
		__empty();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

class CHyperArrayEnumerator : public CArrayEnumeratorBase__<mapkey>
{
public:
	CHyperArrayEnumerator(long nSize = 0) :
		CArrayEnumeratorBase__<mapkey>(m_oItemArray)
	{
		m_oItemArray.SetSize(nSize);
	}
	void SetAt(long nInx,mapkey mapkeyVal)
	{
		m_oItemArray[ nInx ] = mapkeyVal;
	}
	virtual void ConvertItem(CSmartOleVariant & roSOV, mapkey & roElement)
	{
		roSOV.SetPseudoCurrency(hihyper(roElement),lohyper(roElement));
	}
private:
	CEnumerableArray<mapkey,mapkey &>	m_oItemArray;
};

IMPLEMENT_ARRAYENUMERATOR( mapkey )

LPUNKNOWN CHyperSetAutoObject::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CHyperArrayEnumerator > poNewArrayEnumSP = 
			NewSCP(new CHyperArrayEnumerator( m_oItemMap.GetCount() ));
		POSITION pos = m_oItemMap.GetStartPosition();
		long iter = 0;
		while(pos)
		{
			mapkey h1;
			mapvalue mv1;
			m_oItemMap.GetNextAssoc(pos, h1, mv1);
			poNewArrayEnumSP->SetAt(iter,h1);
			iter++;
		}
		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

void CHyperSetAutoObject::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","hyperset");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CHyperSetAutoObject::ExtractAUTO(CURRENCY cyHyperValue, VARIANT FAR* pnHiPart, VARIANT FAR* pnLoPart) 
{
	*pnHiPart = CSmartOleVariant(long(cyHyperValue.Hi),VT_I4).Detach();
	*pnLoPart = CSmartOleVariant(long(cyHyperValue.Lo),VT_I4).Detach();
}
