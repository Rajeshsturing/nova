/*
	NAVO Sp. z o.o. (2001)

	NAVO Enterprise

	CDataObjectModificationSet
		- zbiór u¿ywanych CDataObjectów

	CTransaction
	AUTOMATION Part

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
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "cursorcollection.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"
#include "navolock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//{{AFX_MSG_MAP(CNEO_trans)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_trans, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_trans)
	DISP_FUNCTION(CNEO_trans, "getobj", GetObjectAUTO, VT_DISPATCH, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "newobj", GetNewObjectAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(CNEO_trans, "discard", DiscardAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "accept", AcceptAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "isdirty", IsUserModifiedAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "message", AddMessageAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "isvar", IsVarAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CNEO_trans, "usermodif", SetUserModifAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CNEO_trans, "findobjid", FindStdObjAUTO, VT_I4, VTS_I4 VTS_BSTR)
	DISP_PROPERTY_PARAM(CNEO_trans, "var", GetVarAUTO, SetVarAUTO, VT_VARIANT, VTS_I4)
	DISP_FUNCTION(CNEO_trans, "createadors", CreateDiscoRecSetAUTO, VT_DISPATCH, VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "createcursor", CreateObjectCursorAUTO, VT_DISPATCH, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "createrawcursor", CreateRawCursorAUTO, VT_DISPATCH, VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "createftscursor", CreateFTSCursorAUTO, VT_DISPATCH, VTS_I4 VTS_VARIANT VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "saveobjects", SaveAndCommitAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "save", SaveAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "createsubtran", CreateSubTransAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "execsql", ExecSQLAUTO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "vlock", ExclusiveVirtualLockAUTO, VT_BOOL, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "createvlock", CreateVirtualLockAUTO, VT_DISPATCH, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "afc", GetAFC_AUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "isobjselfdirty", IsObjectModified_SimpleAUTO, VT_BOOL, VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "applyvars", ReplaceEnvironmentVarsAUTO, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "get_this", GetRealThisAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "createserverextension", CreateServerExtensionAUTO, VT_DISPATCH, VTS_BSTR)
	DISP_FUNCTION(CNEO_trans, "createnewthreadtran", CreateNewThreadTransAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "activate", ActivateMeAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "getserverproperty", GetServerPropertyAUTO, VT_VARIANT, VTS_I4)
	DISP_FUNCTION(CNEO_trans, "autorollback", SetAutoRollbackAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CNEO_trans, "holdmutex", GetMutexAUTO, VT_DISPATCH, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CNEO_trans, "parsexml", ParseXML_AUTO, VT_EMPTY, VTS_DISPATCH VTS_VARIANT)
	DISP_FUNCTION(CNEO_trans, "nx_", GetNX_AUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "message_sink", MessageSink_AUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CNEO_trans, "createhli", CreateHLIAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNEO_trans, "save2", Save2AUTO, VT_BSTR, VTS_BOOL VTS_BSTR)

#ifdef _DEBUG
	DISP_FUNCTION(CNEO_trans, "debugnr", GetDebugNrAUTO, VT_I4, VTS_NONE)
#endif
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

#ifdef _DEBUG
long CNEO_trans::GetDebugNrAUTO()
{
	return _debug_trans_nr;
}
#endif

LPDISPATCH CNEO_trans::GetObjectAUTO(long TypeId, long IdObj)
{
	ALL_TRY
	{
		if (IdObj <= 0)
		{
			ThrowNavoException1(ERCO_VIRTTRANS_GETOBJ_IDOBJZERO,IDPAGE_NOTAVAILABLE,TypeId);
		}

		if (m_poCoordinator->GetDefinitionManager()->GetStdObjDef(TypeId)->IsChild())
		{
			CString oString;
			oString.Format("Elementy listy nale¿y pobieraæ metod¹ 'get'. Dotyczy typeid=%d,idobj=%d",
				TypeId,IdObj);
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}

		SCP<CNEO_user> poUserSP = _get_object(TypeId,IdObj,0,0);

		if (poUserSP.PointsObject())
		{
			return poUserSP->GetIDispatch(TRUE);
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

LPDISPATCH CNEO_trans::GetNewObjectAUTO(long TypeId)
{
	ALL_TRY
	{
		if (m_poCoordinator->GetDefinitionManager()->GetStdObjDef(TypeId)->IsChild())
		{
			CString oString;
			oString.Format("Elementy listy nale¿y tworzyæ metod¹ 'addnew' lub 'insertnew'. Dotyczy typeid=%d",TypeId);
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		SCP<CNEO_user> poUserSP = _new_object(TypeId,0,0);
		if (poUserSP.PointsObject())
		{
			return poUserSP->GetIDispatch(TRUE);
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

void CNEO_trans::DiscardAUTO()
{
	ALL_TRY
	{
		_clean();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void CNEO_trans::AcceptAUTO()
{
	ALL_TRY
	{
		//neo_todo:		_full_accept(false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_trans::SetUserModifAUTO(BOOL bNewVal)
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

void CNEO_trans::SetAutoRollbackAUTO(BOOL bNewVal)
{
	ALL_TRY
	{
		get_thread()->set_auto_rollback(bNewVal != FALSE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CNEO_trans::IsUserModifiedAUTO()
{
	ALL_TRY
	{
		return is_user_modified() == true;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::CreateSubTransAUTO()
{
	ALL_TRY
	{
		return CreateSubTransaction(true)->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_trans::CreateNewThreadTransAUTO()
{
	ALL_TRY
	{
		return _get_coordinator()->CreateNewThread()->CreateSubTransaction()->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_trans::ActivateMeAUTO()
{
	ALL_TRY
	{
		get_thread()->SetCurrentTransaction(this);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void CNEO_trans::AddMessageAUTO(long nErrorCode, long IdHelpPage, LPCTSTR lpMsg)
{
	ALL_TRY
	{
		AddMessage(CNavoErrorInfo(errorcode(nErrorCode),IdHelpPage,CString(lpMsg)));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

VARIANT CNEO_trans::GetVarAUTO(long Nr)
{
	ALL_TRY
	{
		CSmartOleVariant oSmartOleVariant;
		get_var(Nr,oSmartOleVariant);
		return oSmartOleVariant.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_trans::SetVarAUTO(long Nr, const VARIANT FAR& newValue)
{
	ALL_TRY
	{
		set_var(Nr,reinterpret_cast<const CSmartOleVariant &>(newValue));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CNEO_trans::IsVarAUTO(long nNr)
{
	ALL_TRY
	{
		//zmienne mo¿na przekazywaæ pomiêdzy transakcjami
		return is_var(nNr) != false;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

VARIANT CNEO_trans::GetServerPropertyAUTO(long nNr)
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		m_poCoordinator->GetDBAccess()->GetServerProp(objsrv_prop(nNr),oSOV);
		return oSOV.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CNEO_trans::FindStdObjAUTO(long TypeId, LPCTSTR lpWhere)
{
	ALL_TRY
	{
		return fwd_find_stdobj(TypeId,lpWhere);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::CreateDiscoRecSetAUTO(LPCTSTR lpSQLClause)
{
	ALL_TRY
	{
#ifdef _DEVELOPER_EDITION_
		if (GetDebugOptions().IsTraceAutoCalls())
		{
			CString oString(lpSQLClause);
			while (oString.GetLength() > 400)
			{
				GetDebugger().StoreMsg("DISCO # [%s]\n",oString.Left(400));
				oString = oString.Mid(400);
			}
			GetDebugger().StoreMsg("DISCO # [%s]\n",oString);
		}
#endif

		SCP<IDispatch> poDispatchSP = m_poCoordinator->GetDBAccess()->OpenDiscoRecSet(lpSQLClause);
		if (poDispatchSP.PointsObject())
		{
			return poDispatchSP.Detach();
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

BOOL CNEO_trans::SaveAndCommitAUTO()
{
	ALL_TRY
	{
		if (m_poThreadSP->get_transaction_level() > 0)
		{
			CString oString = _T("w triggerach nie wolno wo³aæ saveobjects");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		return (_save_changes(true, "")[0] == '+');
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_trans::SaveAUTO()
{
	ALL_TRY
	{
		return (_save_changes(false, "")[0] == '+');
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CNEO_trans::Save2AUTO(BOOL bCommit, LPCTSTR lpExtras)
{
	ALL_TRY
	{
		if (lpExtras == NULL)
		{
			lpExtras = "";
		}

		CString strResult = _save_changes(bCommit, lpExtras);

		return strResult.AllocSysString();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::CreateRawCursorAUTO(long TypeId, LPCTSTR lpWhere, LPCTSTR lpOrderBy, LPCTSTR lpJoin)
{
	ALL_TRY
	{
		return CreateRawCursor(TypeId,lpWhere,lpOrderBy,lpJoin)->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CNEO_trans::ReplaceEnvironmentVarsAUTO(LPCTSTR lpString)
{
	ALL_TRY
	{
		CString oString = ReplaceFormalParam(lpString,m_poEnvironmentHLISP.Get());
		return oString.AllocSysString();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_trans::CreateFTSCursorAUTO(long TypeId, const VARIANT FAR& varFieldName, LPCTSTR lpQuery)
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(varFieldName);
		long nOuterFieldNr = -1;
		if (oSOV.Type() == VT_BSTR)
		{
			CBStr oBStr(oSOV.GetBStr());
			oBStr.ToLower();
			nOuterFieldNr = m_poCoordinator->GetDefinitionManager()->GetStdObjDef(TypeId)->GetFieldFromName(oBStr);
		}
		else if (oSOV.Type() == VT_I4)
		{
			nOuterFieldNr = oSOV.GetLong();
		}
		else if (oSOV.Type() == VT_I2)
		{
			nOuterFieldNr = oSOV.GetShort();
		}
		if (nOuterFieldNr == -1)
		{
			CString oString = _T("z³a nazwa pola");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		SCP<CNEO_cursor> poCursorSP = CreateFTSCursor(TypeId,nOuterFieldNr,lpQuery);
		if (poCursorSP.PointsNull())
		{
			return NULL;
		}
		return poCursorSP->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_trans::CreateObjectCursorAUTO(long TypeId, long IdCursor)
{
	ALL_TRY
	{
		return CreateObjectCursor(TypeId,IdCursor)->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long CNEO_trans::ExecSQLAUTO(LPCTSTR lpSQLCommand)
{
	ALL_TRY
	{
		return fwd_ExecSQL(lpSQLCommand);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_trans::ExclusiveVirtualLockAUTO(long nIdent, long nIdent2)
{
	ALL_TRY
	{
		return _exclusive_virtual_lock(LOCKCLASS_OPERATION,nIdent,nIdent2,0) != false;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::CreateVirtualLockAUTO(long nIdent, long nIdent2)
{
	ALL_TRY
	{
		return _create_vlock(LOCKCLASS_OPERATION,nIdent,nIdent2,0)->GetDispatch(true);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::GetAFC_AUTO()
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = _get_coordinator()->_get_AFC_dispatch();
		return poDispatchSP.Detach();	//in effect dispatch will be addrefed
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH CNEO_trans::GetNX_AUTO()
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = _get_coordinator()->_get_NX_dispatch();
		return poDispatchSP.Detach();	//in effect dispatch will be addrefed
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CNEO_trans::IsObjectModified_SimpleAUTO(long TypeId, long IdObj)
{
	ALL_TRY
	{
		//test if in this transaction's workset
		CNEO_storage * poStorage = _search_local_storage_map(TypeId,IdObj);
		if (poStorage == NULL)
		{
			return FALSE;
		}
		//if accessed check changes
		SCP<CNEO_storage> poStorageSP = NewSCP(poStorage,true);
		evaluate_storage(poStorageSP);
		return (poStorageSP->_get_needsave() == ns_yes);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNEO_trans::GetRealThisAUTO()
{
	ALL_TRY
	{
		return GetDispatch(true);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CNEO_trans::CreateServerExtensionAUTO(LPCTSTR lpExtensionProgID)
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = _get_coordinator()->GetDBAccess()->create_server_extension(lpExtensionProgID);
		if (poDispatchSP.PointsObject())
		{
			return poDispatchSP.Detach();
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

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
LPDISPATCH CNEO_trans::GetMutexAUTO(long TypeId, long IdObj, long nExtra)
{
	ALL_TRY
	{
		if (!m_poCoordinator->get_storage_cache()->aquire_mutex(LOCKCLASS_OBJECT,TypeId,IdObj,nExtra))
		{
			return NULL;
		}

		CNEO_mutex_holder_auto * poNewMutexHolder = new CNEO_mutex_holder_auto(this,LOCKCLASS_OBJECT,TypeId,IdObj,nExtra);
		return poNewMutexHolder->GetDispatch(false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_trans::on_mutex_destroyed(long nClass, long nTypeId, long nIdObj, long nExtra)
{
	m_poCoordinator->get_storage_cache()->release_mutex(nClass, nTypeId, nIdObj, nExtra);
}


void ParseXMLAUTO(SCP<IDispatch> poSinkObjectDispatchSP, SCP<IStream> poInputStreamSP);

void CNEO_trans::ParseXML_AUTO(LPDISPATCH pSinkObject, const VARIANT FAR& rvarStream)
{
	ALL_TRY
	{
		CSmartOleVariant oStreamSOV(rvarStream);
		SCP<IDispatch> poSinkObjectDispatchSP = NewSCP(pSinkObject,true);
		ParseXMLAUTO(poSinkObjectDispatchSP,OpenFileStream_Read_On_SOV(oStreamSOV));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNEO_trans::MessageSink_AUTO(LPDISPATCH pSinkObject)
{
	ALL_TRY
	{
		m_poMessageSinkDispatchSP = NewSCP(pSinkObject,true);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
LPDISPATCH CNEO_trans::CreateHLIAUTO()
{
	ALL_TRY
	{
		return NewSCP(new CHyperLinkInfo())->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}