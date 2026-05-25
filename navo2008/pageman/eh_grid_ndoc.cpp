/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	29.08.2002

	handler grid'a
*/


#include "stdafx.h"
#include "..\include\treeindex_nui.h"
#include "eh_common_inc_ndoc.h"
#include "..\navoui\group_helper_ned.h"
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\table_ned.h"
#include "..\navoui\tablesection_ned.h"
#include "..\navoui\grid_ned.h"
#include "..\navoui\table_bodysection_ned.h"
#include "..\navoui\tablerow_ned.h"
#include "..\navoui\pattern_tablerow_ned.h"
#include "..\navoui\grid_bodysection_ned.h"
#include "..\navoui\tablecell_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


eTransferResult eh_row_number_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(roEventParam.m_poTransfer->get_type() == ett_row_number);
	
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);

	long nDataRowNr = 0;
	VERIFY(NEDID_NOTHING != supply_grid_info(poElementSP,nDataRowNr));

	poElementSP->set_prop_value(CSmartOleVariant(Long2String(nDataRowNr+1)));
	return tr_ok;
}

eTransferResult eh_grid_list_gd(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_getdata);
	ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	long nFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
	
	CSmartOleVariant oListSOV;
	roEventParam.m_poObjectSP->get_field(nFieldNr,oListSOV);
	SCP<CNEO_listuser> poNEOListSP = CNEO_listuser::FromIDispatch(oListSOV.GetDispatch());
	
	//odszukaj sekcjê body grid'a
	SCP<cned_element> poElementSP = get_firing_element(roEventParam);
	cned_grid * poGrid = cast_ui<cned_grid>(poElementSP);
	ASSERT(poGrid);
	SCP<cned_tablesection> poTableSectionSP = poGrid->get_section(ned_tse_body);
	cned_grid_bodysection * poGridBodySection = cast_ui<cned_grid_bodysection>(poTableSectionSP);
	ASSERT(poGridBodySection);
	//podaj liczbê wierszy danych
	poGridBodySection->set_prop_total_datarows(poNEOListSP->GetCountAUTO());
	return tr_ok;
}

eTransferResult eh_grid_list_ro(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poEventInfo->get_type() == eit_row_oper);

	ASSERT(dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer));
	ASSERT(roEventParam.m_poObjectSP.PointsObject());
	long nFieldNr = dynamic_cast<nui_transfer_1*>(roEventParam.m_poTransfer)->get_field();
	
	CSmartOleVariant oListSOV;
	roEventParam.m_poObjectSP->get_field(nFieldNr,oListSOV);
	SCP<CNEO_listuser> poNEOListSP = CNEO_listuser::FromIDispatch(oListSOV.GetDispatch());

	ned_event_row_operation * poEventRO = dynamic_cast<ned_event_row_operation *>(roEventParam.m_poEventInfo);
	ASSERT(poEventRO);
	switch(poEventRO->get_operation())
	{
	case ned_event_row_operation::oper_insert:
	{
		poNEOListSP->insert_new_element(1+poEventRO->get_data_row_nr());
	}
	return tr_ok;
	case ned_event_row_operation::oper_delete:
	{
		poNEOListSP->delete_element(1+poEventRO->get_data_row_nr());
	}
	return tr_ok;
	case ned_event_row_operation::oper_delete_all:
	{
		poNEOListSP->delete_all_elements();
	}
	return tr_ok;
	case ned_event_row_operation::oper_move:
	{
		if(poNEOListSP->ExistsAUTO(poEventRO->get_second_data_row_nr()))
		{
			poNEOListSP->MoveAUTO(poEventRO->get_data_row_nr(),poEventRO->get_second_data_row_nr());
			return tr_ok;
		}
	}
	break;
	}
	return tr_void;
}

