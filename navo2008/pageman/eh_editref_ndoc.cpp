/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	29.08.2002

	handler podpowiedzi (edit_ref)
*/


#include "stdafx.h"
#include "eh_common_inc_ndoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


eTransferResult eh_editref_de(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_edit_ref);
	
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	ASSERT(dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo));

	CSmartOleVariant oArgumentSOVArray[7];

	nui_transfer_2 * poTransfer2 = dynamic_cast<nui_transfer_2 *>(roEventParam.m_poTransfer);
	ASSERT(poTransfer2 != NULL);

	//[bool] function std_rs_dataentered_n(byref pCtrl,byval strEntered,byval nRefField,byval nRefTypeId,byval nMatchField,byval idCursor,byref pCustomizer)
	
	oArgumentSOVArray[6] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[5] = dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data();
	oArgumentSOVArray[4] = poTransfer2->get_field();
	oArgumentSOVArray[3] = poTransfer2->get_reftypeid();
	oArgumentSOVArray[2] = poTransfer2->get_reffield();
	oArgumentSOVArray[1] = poTransfer2->get_cursor();
	oArgumentSOVArray[0] = CSmartOleVariant(LPDISPATCH(NULL),false);
	
	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(_T("std_rs_dataentered_n"),
			oArgumentSOVArray,7,true) == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("std_rs_dataentered_n"),poElementSP->get_ident());
	}

	return tr_void;
}

eTransferResult eh_editref_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_edit_ref);

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	CSmartOleVariant oArgumentSOVArray[3];

	nui_transfer_2 * poTransfer2 = dynamic_cast<nui_transfer_2 *>(roEventParam.m_poTransfer);
	ASSERT(poTransfer2 != NULL);

	//[void] function std_rs_getdata_n(byref pCtrl,byval nRefField,byval nMatchField)
	oArgumentSOVArray[2] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[1] = poTransfer2->get_field();
	oArgumentSOVArray[0] = poTransfer2->get_reffield();

	ALL_TRY
	{
		roEventParam.m_poWindow->fire_user_command(_T("std_rs_getdata_n"),
			oArgumentSOVArray,3,true);
	}
	ALL_CATCH(CNavoException & roException)
	{
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("std_rs_getdata_n"),poElementSP->get_ident());
	}
	return tr_ok;
}

eTransferResult eh_editref_lf(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_lostfocus);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_edit_ref || 
		   roEventParam.m_poTransfer->get_type() == ett_row_edit_ref);

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	CSmartOleVariant oArgumentSOVArray[2];
	ASSERT(dynamic_cast<ned_event_lostfocus*>(roEventParam.m_poEventInfo));

	//[void] function std_rs_lostfocus(byref pCtrl,byval idGotFocus)
	oArgumentSOVArray[1] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[0] = CSmartOleVariant(dynamic_cast<ned_event_lostfocus*>(roEventParam.m_poEventInfo)->get_got_focus_element(),VT_I4);

	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(_T("std_rs_lostfocus"),
			oArgumentSOVArray,2,false) == invoke_notexists) ? tr_void: tr_ok;
	}
	ALL_CATCH(CNavoException & roException)
	{
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("std_rs_lostfocus"),poElementSP->get_ident());
	}
	return tr_void;
}

//---------------------------------------------------------
//---------------------------------------------------------

eTransferResult eh_row_edref_de(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_row_edit_ref);
	
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	ASSERT(dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo));

	CSmartOleVariant oArgumentSOVArray[9];

	nui_transfer_2 * poTransfer2 = dynamic_cast<nui_transfer_2 *>(roEventParam.m_poTransfer);
	ASSERT(poTransfer2 != NULL);

	long nDataRowNr = 0;
	SCP<nui_transfer_1> poGridTransferSP;
	supply_grid_info2(poElementSP,nDataRowNr,poGridTransferSP);

	//[bool] function std_lrs_dataentered_n(byref pCtrl,byval strEntered,byval nListField,byval nRow,byval nRefField,byval nRefTypeId,byval nMatchField,byval idCursor,byref pCustomizer)
	
	oArgumentSOVArray[8] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	oArgumentSOVArray[7] = dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data();

	oArgumentSOVArray[6] = poGridTransferSP->get_field();
	oArgumentSOVArray[5] = CSmartOleVariant(long(1+nDataRowNr),VT_I4);

	oArgumentSOVArray[4] = poTransfer2->get_field();
	oArgumentSOVArray[3] = poTransfer2->get_reftypeid();
	oArgumentSOVArray[2] = poTransfer2->get_reffield();
	oArgumentSOVArray[1] = poTransfer2->get_cursor();
	oArgumentSOVArray[0] = CSmartOleVariant(LPDISPATCH(NULL),false);
	
	ALL_TRY
	{
		return (roEventParam.m_poWindow->fire_user_command(_T("std_lrs_dataentered_n"),
			oArgumentSOVArray,9,true) == invoke_true) ? tr_ok : tr_failed;
	}
	ALL_CATCH(CNavoException & roException)
	{
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("std_lrs_dataentered_n"),poElementSP->get_ident());
	}

	return tr_void;
}

eTransferResult eh_row_edref_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_row_edit_ref);

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	CSmartOleVariant oArgumentSOVArray[5];

	nui_transfer_2 * poTransfer2 = dynamic_cast<nui_transfer_2 *>(roEventParam.m_poTransfer);
	ASSERT(poTransfer2 != NULL);

	long nDataRowNr = 0;
	SCP<nui_transfer_1> poGridTransferSP;
	supply_grid_info2(poElementSP,nDataRowNr,poGridTransferSP);

	//[void] function std_lrs_getdata_n(byref pCtrl,byval nListField,byval nRow,byval nRefField,byval nMatchField)
	oArgumentSOVArray[4] = CSmartOleVariant(poElementSP->get_my_nedaw()->GetIDispatch(TRUE),false);
	
	oArgumentSOVArray[3] = poGridTransferSP->get_field();
	oArgumentSOVArray[2] = CSmartOleVariant(long(1+nDataRowNr),VT_I4);

	oArgumentSOVArray[1] = poTransfer2->get_field();
	oArgumentSOVArray[0] = poTransfer2->get_reffield();

	ALL_TRY
	{
		roEventParam.m_poWindow->fire_user_command(_T("std_lrs_getdata_n"),oArgumentSOVArray,5,true);
	}
	ALL_CATCH(CNavoException & roException)
	{
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("std_lrs_getdata_n"),poElementSP->get_ident());
	}

	return tr_ok;
}

//---------------------------------------------------------
//---------------------------------------------------------

eTransferResult eh_disp_ref_text_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_display_ref_text);
	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	long nFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
	CSmartOleVariant oRefSOV;
	roEventParam.m_poObjectSP->get_field(nFieldNr,oRefSOV);
	SCP<CNEO_user> poNEORefSP = CNEO_user::FromIDispatch(oRefSOV.GetDispatch());
	CString oTextString = "";
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	if(poNEORefSP.PointsObject())
	{
		oTextString = poNEORefSP->get_as_text();
	}
	else
	{
		poElementSP->get_prop_tooltip_text(oTextString);
	}
	CSmartOleVariant oSOV(oTextString);
	poElementSP->set_prop_value(oSOV);
	return tr_ok;
}


eTransferResult eh_disp_ref_text_de(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_display_ref_text);
	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	ASSERT(dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo));
	
	const CSmartOleVariant & roEnteredSOV = dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data();
	if(wcscmp(roEnteredSOV.GetBStr(),L"") == 0)
	{
		long nFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
		roEventParam.m_poObjectSP->set_field(nFieldNr,CSmartOleVariant(LPDISPATCH(NULL),false));
	}
	return tr_ok;
}
