/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_grid / <grid>
		tabelka edycyjna
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "scroll_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "grid_ned.h"
#include "table_bodysection_ned.h"
#include "tablerow_ned.h"
#include "pattern_tablerow_ned.h"
#include "grid_bodysection_ned.h"
#include "tablecell_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------
SCP<cned_element> cned_grid::create_section(ened_tablesection_enum eSection,const ned_ident idSection)
{
	if(eSection == ned_tse_body)
	{
		ASSERT(_get_section_ident(ned_tse_body) == NEDID_NOTHING);	//call only once
		ASSERT(m_idPatternSection == NEDID_NOTHING);				//call only once
		
		_create_missing_sections(eSection);

		//now create requested section
		SCP<cned_element> poSectionSP =  
			_internal_create_section(ned_spreadbodysection,ned_tse_body,idSection);

		//przy okazji tworzymy sekcjê 'pattern'
		//ale nie notyfikujemy o powstaniu takiej sekcji
		//patrz implementacja _internal_create_section
		m_idPatternSection = _internal_create_section(ned_spreadpatternsection,ned_tse_pattern,NEDID_NOTHING)->get_ident();

		return poSectionSP;
	}
	else
	{
		return cned_table::create_section(eSection,idSection);
	}
}

void cned_grid::_measure_columns(const ned_measure_param & roMParam,ng_ydist & ryMinTableHeight)
{
	cned_table::_measure_columns(roMParam,ryMinTableHeight);
	//to jest trochê Ÿle, poniewa¿ cned_table::_measure_columns zamyka ju¿ pewne rzeczy i 
	//mierzenie pattern-section nie ma wp³ywu ale w praktyce to nie ma znaczenia
	if(get_pattern_section_ident() != NEDID_NOTHING)	//only if already exists
	{
		SCP<cned_tablesection> poPatterSectionSP = get_pattern_section();
		poPatterSectionSP->init_measure_columns();
		
		for(long nColNr = 0; nColNr < get_col_count(); nColNr++)
		{
			ng_ydist yMinColHeight = 0;
			poPatterSectionSP->measure_column(roMParam,nColNr,yMinColHeight);
		
			if(nColNr == get_col_count() - 1) //przy ostatniej zaznacz ¿e sekcja zosta³a zmierzona
			{
				poPatterSectionSP->clear_measure_pending();
			}
			ryMinTableHeight = max(ryMinTableHeight,yMinColHeight);
		}
		poPatterSectionSP->finish_measure_columns();
	}
}

//--------------------------------------------------------------------
//--------------event handlers ---------------------------------------
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// command
// obs³uga tutaj a nie w sekcji bo grid ma transfer a nie sekcja
//--------------------------------------------------------------------

void cned_grid::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(roActionCommand.get_target() == get_ident());

	bool bSuccess = false;
	SCP<ned_event_row_operation> poEventRowOpSP = NewSCP(new ned_event_row_operation(get_ident()));
	
	switch(roActionCommand.get_verb())
	{
	case sccv_insert_row:
	{
		poEventRowOpSP->set_data_row_nr(roActionCommand.get_command()->GetNumProp(PROPC_ROW));
		poEventRowOpSP->set_operation(ned_event_row_operation::oper_insert);
		bSuccess = true;
	}
	break;
	case sccv_delete_row:
	{
		poEventRowOpSP->set_data_row_nr(roActionCommand.get_command()->GetNumProp(PROPC_ROW));
		poEventRowOpSP->set_operation(ned_event_row_operation::oper_delete);
		bSuccess = true;
	}
	break;
	case sccv_delete_all:
	{
		if (::AfxMessageBox("Czy usun¹æ wszystkie pozycje ?", MB_ICONQUESTION | MB_YESNO) != IDYES)
		{
			return;
		}

		poEventRowOpSP->set_operation(ned_event_row_operation::oper_delete_all);
		bSuccess = true;
	}
	break;
	}
	
	if(bSuccess)
	{
		roResult.add_info(poEventRowOpSP);
	}
}

