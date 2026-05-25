/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	01.08.2002

	handlerów 'custom
*/


#include "stdafx.h"
#include <afxpriv2.h>
#include "eh_common_inc_ndoc.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\win32_ned.h"
#include "..\navoui\olecontrol_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static LPCTSTR cEventHandlerSuffix[] = 
{
	{ "_ondataentered"	},		//eit_newdata
	{ "_ongetdata"		},		//eit_getdata
	{ "_ongotfocus"		},		//eit_gotfocus
	{ "_onlostfocus"	},		//eit_lostfocus
	{ ""				},		//placeholder for eit_row_oper
	{ ""				},		//placeholder for eit_oleevent
	{ "_ontabitemactivate"},	//eit_tabitem_activ
	{ ""				},		//placeholder for eit_max_handler
	{ "_oncmdlist"		},		//eit_command_list
};

static void create_event_handler_name(CString & roString,ned_ident nIdent,eEventInfoType eType)
{
	roString.Format("c%d%s",nIdent,cEventHandlerSuffix[ eType ] );
}

eTransferResult eh_custom_de(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom ||
		   roEventParam.m_poTransfer->get_type() == ett_row_custom);
	
	SCP<ned::cned_element> poElementSP = get_firing_element(roEventParam);

	bool bRow = (roEventParam.m_poTransfer->get_type() == ett_row_custom);
	
	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_newdata))
	{
		return tr_failed;
	}

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_newdata);

	ASSERT(dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo));

	CSmartOleVariant oArgumentSOVArray[3];

	if(bRow)
	{
		long nDataRowNr = 0;
		VERIFY(NEDID_NOTHING != supply_grid_info(poElementSP,nDataRowNr));

		nDataRowNr++;		//external numbering

		//[bool] function c123_ondataentered(ctrl,row,value)
		oArgumentSOVArray[2] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[1] = nDataRowNr;
		oArgumentSOVArray[0] = dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data();
	}
	else
	{
		//[bool] function c123_ondataentered(ctrl,value)
		oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[0] = dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data();
	}

	
	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,
			bRow ? 3 : 2,true) == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_newdata);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}

eTransferResult eh_custom_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom ||
		   roEventParam.m_poTransfer->get_type() == ett_row_custom);

	SCP<ned::cned_element> poElementSP = get_firing_element(roEventParam);

	bool bRow = (roEventParam.m_poTransfer->get_type() == ett_row_custom);

	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_newdata))
	{
		return tr_failed;
	}

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_getdata);

	CSmartOleVariant oArgumentSOVArray[2];

	if(bRow)
	{
		long nDataRowNr = 0;
		VERIFY(NEDID_NOTHING != supply_grid_info(poElementSP,nDataRowNr));
		
		nDataRowNr++;		//external numbering

		//[void] function c123_ongetdata(ctrl,row)
		oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[0] = nDataRowNr;
	}
	else
	{
		//[void] function c123_ongetdata(ctrl)
		oArgumentSOVArray[0] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	}

	
	ALL_TRY
	{
		roEventParam.m_poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,
			bRow ? 2 : 1,true);
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_newdata);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}

eTransferResult eh_custom_gf(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_gotfocus);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom ||
		   roEventParam.m_poTransfer->get_type() == ett_row_custom);

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	bool bRow = (roEventParam.m_poTransfer->get_type() == ett_row_custom);
	
	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_gotfocus))
	{
		return tr_failed;
	}

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_gotfocus);
	
	CSmartOleVariant oArgumentSOVArray[3];
	ASSERT(dynamic_cast<ned_event_gotfocus*>(roEventParam.m_poEventInfo));

	if(bRow)
	{
		long nDataRowNr = 0;
		VERIFY(NEDID_NOTHING != supply_grid_info(poElementSP,nDataRowNr));
		
		nDataRowNr++;		//external numbering

		//[void] function c123_ongotfocus(ctrl,row,nLostFocusId)
		oArgumentSOVArray[2] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[1] = nDataRowNr;
		oArgumentSOVArray[0] = CSmartOleVariant(dynamic_cast<ned_event_gotfocus*>(roEventParam.m_poEventInfo)->get_lost_focus_element(),VT_I4);
	}
	else
	{
		//[void] function c123_ongotfocus(ctrl,nLostFocusId)
		oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[0] = CSmartOleVariant(dynamic_cast<ned_event_gotfocus*>(roEventParam.m_poEventInfo)->get_lost_focus_element(),VT_I4);
	}

	
	ALL_TRY
	{
		eInvokeResult eIR = roEventParam.m_poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,bRow ? 3 : 2,false);
		if(eIR == invoke_notexists)
		{
			return tr_void;
		}
		return (eIR == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_gotfocus);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}

eTransferResult eh_custom_lf(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_lostfocus);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom ||
		   roEventParam.m_poTransfer->get_type() == ett_row_custom);

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	bool bRow = (roEventParam.m_poTransfer->get_type() == ett_row_custom);
	
	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_lostfocus))
	{
		return tr_failed;
	}

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_lostfocus);

	CSmartOleVariant oArgumentSOVArray[3];
	ASSERT(dynamic_cast<ned_event_lostfocus*>(roEventParam.m_poEventInfo));

	if(bRow)
	{
		long nDataRowNr = 0;
		VERIFY(NEDID_NOTHING != supply_grid_info(poElementSP,nDataRowNr));
		
		nDataRowNr++;		//external numbering

		//[void] function c123_onlostfocus(ctrl,row,nGotFocusId)
		oArgumentSOVArray[2] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[1] = nDataRowNr;
		oArgumentSOVArray[0] = CSmartOleVariant(dynamic_cast<ned_event_lostfocus*>(roEventParam.m_poEventInfo)->get_got_focus_element(),VT_I4);
	}
	else
	{
		//[void] function c123_onlostfocus(ctrl,nGotFocusId)
		oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[0] = CSmartOleVariant(dynamic_cast<ned_event_lostfocus*>(roEventParam.m_poEventInfo)->get_got_focus_element(),VT_I4);
	}


	ALL_TRY
	{
		eInvokeResult eIR = roEventParam.m_poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,
			bRow ? 3 : 2,false);
		if(eIR == invoke_notexists)
		{
			return tr_void;
		}
		return (eIR == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_lostfocus);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}


eTransferResult eh_custom_ro(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom);
	ned_event_row_operation * poEventRO = dynamic_cast<ned_event_row_operation *>(roEventParam.m_poEventInfo);
	ASSERT(poEventRO);
	
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	ASSERT(poElementSP->get_type() == ned_grid);

	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}

	//special version of create event name
	CString oFunNameFormatString;
	switch(poEventRO->get_operation())
	{
	case ned_event_row_operation::oper_insert:
	{
		oFunNameFormatString = _T("c%d_oninsertrow");
	}
	break;
	case ned_event_row_operation::oper_delete:
	{
		oFunNameFormatString = _T("c%d_ondeleterow");
	}
	break;
	case ned_event_row_operation::oper_delete_all:
	{
		oFunNameFormatString = _T("c%d_ondeleteallrows");
	}
	break;
	default: 
		ASSERT(false);
	}
	CString oFunctionNameString;
	oFunctionNameString.Format(oFunNameFormatString,nResolvedIdent);

	CSmartOleVariant oArgumentSOVArray[2];
	//[void] function c123_oninsert/deleterow(pGrid,nDataRowNr)
	oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[0] = CSmartOleVariant(1+poEventRO->get_data_row_nr(),VT_I4);

	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,
			2,true) == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_row_oper);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}

void invoke_build_cmd_list(cndoc_event_manager * poEventManager,cned_window * poWindow,cned_element * poElement,CCommandList * poCommandList)
{
	ASSERT(poEventManager);
	ASSERT(poWindow);
	ASSERT(poElement);
	ASSERT(poCommandList);

	if(poElement->get_prop_disabled())
	{
		return;
	}

	ned_ident nResolvedIdent = poElement->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElement->get_ident();
	}
	if(poEventManager->is_handler_failed(nResolvedIdent,eit_command_list))
	{
		return;
	}
	
	long nDataRowNr = 0;
	ned_ident idGrid = supply_grid_info(NewSCP(poElement,true),nDataRowNr);

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_command_list);
	CSmartOleVariant oArgumentSOVArray[3];


	if(idGrid != NEDID_NOTHING)	//under grid
	{
		nDataRowNr++;		//external numbering
		//[void] function c123_oncmdlist(pCtrl,row,pCmdList)
		oArgumentSOVArray[2] = CSmartOleVariant(poElement->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[1] = nDataRowNr;
		oArgumentSOVArray[0] = CSmartOleVariant(poCommandList->GetIDispatch(TRUE),false);
	}
	else
	{
		//[void] function c123_oncmdlist(pCtrl,pCmdList)
		oArgumentSOVArray[1] = CSmartOleVariant(poElement->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[0] = CSmartOleVariant(poCommandList->GetIDispatch(TRUE),false);
	}


	ALL_TRY
	{
		poWindow->fire_user_command(oFunctionNameString,oArgumentSOVArray,
			(idGrid != NEDID_NOTHING) ? 3 : 2,false);
	}
	ALL_CATCH(CNavoException & roException)
	{
		poEventManager->mark_failed_handler(nResolvedIdent,eit_command_list);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_RIGHTCLICK, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
}

eTransferResult eh_custom_oe(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_oleevent);
	ASSERT(dynamic_cast<ned_event_olecontrol *>(roEventParam.m_poEventInfo));

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_oleevent))
	{
		return tr_failed;
	}

	ASSERT(ned_olecontrol == poElementSP->get_type());
	cned_olecontrol * poOleControlWrapper = cast_ui<cned_olecontrol>(poElementSP.Get());
	ASSERT(poOleControlWrapper != NULL);

	ned_event_olecontrol * poEventOleControl = dynamic_cast<ned_event_olecontrol *>(roEventParam.m_poEventInfo);
	AFX_EVENT * pAfxEvent = poEventOleControl->get_event_data();

	ng_string oEventNameString;
	if(!poOleControlWrapper->get_olecontrol_event_name(pAfxEvent->m_dispid,oEventNameString))
	{
		TRACE1("unknown event %d\n",pAfxEvent->m_dispid);
		return tr_void;
	}

	//construct handler name
	ng_string oFunctionNameString;
	oFunctionNameString.Format("c%d_%s",nResolvedIdent,oEventNameString);

	ALL_TRY
	{
		eInvokeResult eIR = roEventParam.m_poWindow->fire_user_command(oFunctionNameString,
			reinterpret_cast<CSmartOleVariant *>(
			((pAfxEvent->m_pDispParams != NULL) ? pAfxEvent->m_pDispParams->rgvarg : NULL)
			),
			((pAfxEvent->m_pDispParams != NULL) ? pAfxEvent->m_pDispParams->cArgs : 0),false);
		if(eIR == invoke_notexists)
		{
			return tr_void;
		}
		return (eIR == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_oleevent);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;
}

eTransferResult eh_custom_tabia(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_tabitem_activ);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_custom);

	SCP<ned::cned_element> poElementSP = get_firing_element(roEventParam);

	ned_ident nResolvedIdent = poElementSP->get_prop_redirect();
	if(nResolvedIdent == NEDID_NOTHING)
	{
		nResolvedIdent = poElementSP->get_ident();
	}
	
	if(roEventParam.m_poEventManager->is_handler_failed(nResolvedIdent,eit_tabitem_activ))
	{
		return tr_failed;
	}

	CString oFunctionNameString;
	create_event_handler_name(oFunctionNameString,nResolvedIdent,eit_tabitem_activ);

	ASSERT(dynamic_cast<ned_event_tabitem_activation*>(roEventParam.m_poEventInfo));
	ned_event_tabitem_activation * pEventInfo = dynamic_cast<ned_event_tabitem_activation*>(roEventParam.m_poEventInfo);

	CSmartOleVariant oArgumentSOVArray[3];

	//[bool] function c123_ontabitemactivate(ctrl,nActiveItem,bool bFirstTime)
	oArgumentSOVArray[2] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[1] = (long) (pEventInfo->get_active_item_nr() + 1);	//external numbering
#ifdef _NAVODOTNET
	oArgumentSOVArray[0] = CSmartOleVariant(COleVariant ((long)(bool) pEventInfo->get_first_time_flag(), VT_BOOL));
#else
	oArgumentSOVArray[0] = CSmartOleVariant((bool) pEventInfo->get_first_time_flag());
#endif
	

	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(oFunctionNameString,
			oArgumentSOVArray,3,true) == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		roEventParam.m_poEventManager->mark_failed_handler(nResolvedIdent,eit_tabitem_activ);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			oFunctionNameString,nResolvedIdent);
	}
	return tr_void;

}

