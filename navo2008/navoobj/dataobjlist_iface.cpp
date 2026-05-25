/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectList
	interace and automation part
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//{{AFX_MSG_MAP(CNEO_listuser)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_listuser, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_listuser)
	DISP_FUNCTION(CNEO_listuser, "get", GetAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "exists", ExistsAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "count", GetCountAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CNEO_listuser, "addnew", AddNewAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_listuser, "insertnew", InsertNewAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "delete", DeleteAUTO, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "deleteall", DeleteAllAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CNEO_listuser, "find", FindAUTO, VT_I4, VTS_DISPATCH)
	DISP_FUNCTION(CNEO_listuser, "findonid", FindOnIdAUTO, VT_I4, VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "move", MoveAUTO, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_listuser, "usermodif", SetUserModifAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CNEO_listuser, "collectionid", GetCollectionIDAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CNEO_listuser, "getidobj", GetIdObjAUTO, VT_I4, VTS_I4)
	DISP_PROPERTY_EX_ID(CNEO_listuser, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPCTSTR lpDataObjListObjectName = "dataobjlist";

IMPLEMENT_ARRAYENUMERATOR(SCP<CNEO_user>)

LPUNKNOWN CNEO_listuser::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CArrayEnumerator< SCP<CNEO_user> > > poNewArrayEnumSP = 
			NewSCP(new CArrayEnumerator< SCP<CNEO_user> >(*this));
		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

void CNEO_listuser::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)",lpDataObjListObjectName);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_listuser::GetAUTO(long nOuterIndex) 
{
	ALL_TRY
	{
		ASSERT(nOuterIndex > 0);
		return GetElementAt(nOuterIndex - 1)->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		long iParentTypeId = _get_storage()->GetParentTypeid();
		long iParentIdObj = _get_storage()->GetParentId();

		CString oString;
		oString.Format("parent type=%d,parent idobj=%d,lp=%d",
			iParentTypeId,iParentIdObj,nOuterIndex);
		ContinueThrowNavoException1(roNavoException,ERCO_TODO,IDPAGE_NOTAVAILABLE,oString );
	};
}

long CNEO_listuser::GetIdObjAUTO(long nOuterIndex)
{
	ALL_TRY
	{
		ASSERT(nOuterIndex > 0);
		ASSERT(_get_storage().PointsObject());
		ASSERT(_get_trans().PointsObject());
		long nElementIdObj = _get_storage()->get_element_at(nOuterIndex - 1);
		ASSERT(nElementIdObj > 0);
		return nElementIdObj;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CNEO_listuser::ExistsAUTO(long nOuterIndex) 
{
	ALL_TRY
	{
		if(nOuterIndex <= 0)		//wiadomo ¿e nie ma
		{
			return FALSE;
		}
		return IsElementAt(nOuterIndex - 1);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_listuser::AddNewAUTO() 
{
	ALL_TRY
	{
		SCP<CNEO_user> poUserSP = add_new_element();
		if(poUserSP.PointsObject())
		{
			return poUserSP->GetDispatch(true);
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

LPDISPATCH CNEO_listuser::InsertNewAUTO(long nOuterIndex) 
{
	ALL_TRY
	{
		SCP<CNEO_user> poUserSP = insert_new_element(nOuterIndex);
		if(poUserSP.PointsObject())
		{
			return poUserSP->GetDispatch(true);
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

void CNEO_listuser::DeleteAUTO(long nOuterIndex) 
{
	ALL_TRY
	{
		delete_element(nOuterIndex);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_listuser::DeleteAllAUTO() 
{
	ALL_TRY
	{
		delete_all_elements();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CNEO_listuser::FindAUTO(LPDISPATCH poUserDispatch) 
{
	ALL_TRY
	{
		SCP<CNEO_user> poUserSP = CNEO_user::FromIDispatch(poUserDispatch);
		ASSERT(poUserSP.PointsObject());
		
		//0 - nieznaleziono >0 - znaleziono
		return _get_storage()->find(poUserSP->_get_storage()) + 1;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CNEO_listuser::FindOnIdAUTO(long nIdChildIdObj)
{
	ALL_TRY
	{
		//0 - nieznaleziono >0 - znaleziono
		return _get_storage()->findonid(nIdChildIdObj) + 1;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_listuser::MoveAUTO(long nOuterFromIndex,long nOuterToIndex)
{
	ALL_TRY
	{
		ASSERT(ExistsAUTO(nOuterFromIndex));
		ASSERT(ExistsAUTO(nOuterToIndex));
		_get_storage()->move_element(nOuterFromIndex-1,nOuterToIndex-1);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_listuser::SetUserModifAUTO(BOOL bNewVal)
{
	ALL_TRY
	{
		set_user_modified(bNewVal != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNEO_listuser::GetCountAUTO()
{
	ALL_TRY
	{
		return _get_storage()->GetSize();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNEO_listuser::GetCollectionIDAUTO()
{
	ALL_TRY
	{
		return _get_storage()->GetCollectionId();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
