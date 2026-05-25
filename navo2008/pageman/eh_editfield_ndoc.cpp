/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	01.08.2002

	handlerów 'edit_field
*/


#include "stdafx.h"
#include "eh_common_inc_ndoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



eTransferResult eh_editfield_de(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ned_ident nIdent = roEventParam.m_poEventInfo->get_firing_element();

	if(roEventParam.m_poEventManager->is_handler_failed(nIdent,eit_newdata))
	{
		return tr_failed;
	}

	ALL_TRY
	{
		ASSERT(roEventParam.m_poObjectSP.PointsObject());
		ASSERT(dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo));
		ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
		
		roEventParam.m_poObjectSP->set_field(
			dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field(),
			dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data());
	}
	ALL_CATCH(CNavoException & roException)
	{
		//to tylko z³a wartoœæ
		if(SearchExceptionForErrorCode(roException,ERCO_STDOBJ_INVALID_VALUE_FOR_FIELD))
		{
			return tr_failed;
		}
		//nie mo¿na dostaæ write lock'a
		if(SearchExceptionForErrorCode(roException,ERCO_STDOBJ_CANNOT_GET_WRITE_LOCK))
		{
			return tr_failed;
		}
		roEventParam.m_poEventManager->mark_failed_handler(nIdent,eit_newdata);
		ContinueThrowNavoException2(roException, ERCO_EXCHLOG_FUN_FAILED_DATAENTERED, IDPAGE_NOTAVAILABLE, 
			_T("built-in edit_field"),nIdent);
	}
	return tr_ok;
}

eTransferResult eh_editfield_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	long nFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
	CSmartOleVariant oSOV;
	roEventParam.m_poObjectSP->get_field(nFieldNr,oSOV);
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	poElementSP->set_prop_value(oSOV);
	set_valid_state(poElementSP,!roEventParam.m_poObjectSP->has_field_bad_value(nFieldNr));
	return tr_ok;
}

eTransferResult eh_disp_text_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_display_text);

	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	CString oTextString = roEventParam.m_poObjectSP->get_as_text();
	CSmartOleVariant oSOV(oTextString);
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	poElementSP->set_prop_value(oSOV);
	return tr_ok;
}

//--------------------------------------------------------------------
eTransferResult eh_row_edfld_de(cndoc_event_param & roEventParam)
{
	//ned_to_do: try/catche dla failed handlerów

	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_newdata);
	ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
	ASSERT(roEventParam.m_poObjectSP.PointsObject());

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	SCP<CNEO_user> poNEOChildSP;
	{
		long nDataRowNr = 0;
		SCP<nui_transfer_1> poGridTransferSP;
		supply_grid_info2(poElementSP,nDataRowNr,poGridTransferSP);
		long nListFieldNr = poGridTransferSP->get_field();
		
		CSmartOleVariant oListSOV;
		roEventParam.m_poObjectSP->get_field(nListFieldNr,oListSOV);
		SCP<CNEO_listuser> poNEOListSP = CNEO_listuser::FromIDispatch(oListSOV.GetDispatch());
		if(poNEOListSP->IsElementAt(nDataRowNr))
		{
			poNEOChildSP = poNEOListSP->GetElementAt(nDataRowNr);
		}
		else
		{
			poNEOChildSP = poNEOListSP->add_new_element();
			if(poNEOChildSP.PointsNull())
			{
				return tr_failed;	//nie mo¿na by³o dodaæ elementu do listy (bo coœ siê nie zgodzi³o)
			}
			ASSERT(poNEOListSP->IsElementAt(nDataRowNr));	//edycja mo¿e siê odbywaæ tylko w ostatnim + 1 wierszu !
		}
	}
	ASSERT(poNEOChildSP.PointsObject());
	
	poNEOChildSP->set_field(
			dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field(),
			dynamic_cast<ned_event_newdata*>(roEventParam.m_poEventInfo)->get_data());

	return tr_ok;
}

eTransferResult eh_row_edfld_gd(cndoc_event_param & roEventParam)
{
	//ned_to_do: try/catche dla failed handlerów

	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
	ASSERT(roEventParam.m_poObjectSP.PointsObject());

	bool bValid;

	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	{
		long nDataRowNr = 0;
		SCP<nui_transfer_1> poGridTransferSP;
		supply_grid_info2(poElementSP,nDataRowNr,poGridTransferSP);
		
		long nListFieldNr = poGridTransferSP->get_field();
		CSmartOleVariant oListSOV;
		roEventParam.m_poObjectSP->get_field(nListFieldNr,oListSOV);
		
		SCP<CNEO_listuser> poNEOListSP = CNEO_listuser::FromIDispatch(oListSOV.GetDispatch());
	
		if(poNEOListSP->IsElementAt(nDataRowNr))
		{
			CSmartOleVariant oValueSOV;
			SCP<CNEO_user> poNEOChildSP = poNEOListSP->GetElementAt(nDataRowNr);
			ASSERT(poNEOChildSP.PointsObject());

			long nChildFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
			poNEOChildSP->get_field(nChildFieldNr,oValueSOV);
			bValid = !poNEOChildSP->has_field_bad_value(nChildFieldNr);
			poElementSP->set_prop_value(oValueSOV);
		}
		else
		{
			//"pusty wiersz" grid'a, ale ¿aden inny
			ASSERT(nDataRowNr == poNEOListSP->GetCountAUTO());	

			//do kontrolki wstawiamy wartoœci ze wzorca
			SCP<cned_element> poPatternSP = roEventParam.m_poWindow->get_element_on_ident(poElementSP->get_prop_redirect());
			ASSERT(poPatternSP.PointsObject());
			poPatternSP->fill_clone(poElementSP);
			bValid = true;
		}
	}

	set_valid_state(poElementSP,bValid);
	return tr_ok;
}

