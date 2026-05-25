/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	01.08.2002

	manager handlerów zdarzeñ 
*/

#include "stdafx.h"
#include "..\include\treeindex_nui.h"
#include "eh_common_inc_ndoc.h"
#include "event_handler_impl_ndoc.h"
#include "..\navoui\edit_ned.h"
#include "..\navoui\edit_ned_inl.h"
#include "..\navoui\multiline_helper_ned.h"
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\multi_ned.h"
#include "..\navoui\group_helper_ned.h"
#include "..\navoui\table_ned.h"
#include "..\navoui\tablesection_ned.h"
#include "..\navoui\grid_ned.h"
#include "..\navoui\table_bodysection_ned.h"
#include "..\navoui\tablerow_ned.h"
#include "..\navoui\pattern_tablerow_ned.h"
#include "..\navoui\grid_bodysection_ned.h"
#include "..\navoui\tablecell_ned.h"
#include "..\navoui\commandlist.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

eTransferResult eh_void(cndoc_event_param &)	//void handler
{
	return tr_void;
}

eTransferResult eh_ok(cndoc_event_param &)	//ok handler
{
	return tr_ok;
}

cndoc_event_param::cndoc_event_param() :
	m_poEventManager(NULL),
	m_poTransfer(NULL),
	m_poEventInfo(NULL),
	m_poWindow(NULL),
	m_poTransaction(NULL)
{
}

#ifdef _CUSTOM_HANDLER_ONLY_
pfEventHandler cndoc_event_manager::_g_aHandlers[ett_max][eit_max_handler] =
{
					/* data entered */		/*getdata*/			/* gotfocus */		/* lostfocus */		/*row_oper*/			/*oleevent*/	  /*tabitem_activ*/
/*ett_custom*/		{ { eh_custom_de	},{ eh_custom_gd	} ,{ eh_custom_gf	} ,{ eh_custom_lf	} ,{ NULL				},	{ eh_custom_oe	},{ NULL			}},	
};
#else
pfEventHandler cndoc_event_manager::_g_aHandlers[ett_max][eit_max_handler] =
{
					/* data entered */		/*getdata*/			/* gotfocus */		/* lostfocus */		/*row_oper*/			/*oleevent*/	  /*tabitem_activ*/
/*ett_none*/		{ { NULL			},{ NULL			} ,{ NULL			} ,{ NULL			} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_custom*/		{ { eh_custom_de	},{ eh_custom_gd	} ,{ eh_custom_gf	} ,{ eh_custom_lf	} ,{ eh_custom_ro		},	{ eh_custom_oe	},{ eh_custom_tabia	}},	
/*ett_edit_field*/	{ { eh_editfield_de	},{ eh_editfield_gd	} ,{ eh_void		} ,{ eh_void		} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_grid_list*/	{ { eh_ok			},{ eh_grid_list_gd	} ,{ NULL			} ,{ NULL			} ,{ eh_grid_list_ro	},	{ NULL			},{ NULL			}},		
/*ett_grid_cursor*/	{ { NULL			},{ NULL			} ,{ NULL			} ,{ NULL			} ,{ NULL				},	{ NULL			},{ NULL			}},		
/*ett_edit_ref*/	{ { eh_editref_de	},{ eh_editref_gd	} ,{ eh_void		} ,{ eh_editref_lf	} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_row_custom*/	{ { eh_custom_de	},{ eh_custom_gd	} ,{ eh_custom_gf	} ,{ eh_custom_lf	} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_row_edit_fld*/{ { eh_row_edfld_de	},{ eh_row_edfld_gd	} ,{ eh_void		} ,{ eh_void		} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_row_edit_ref*/{ { eh_row_edref_de	},{ eh_row_edref_gd	} ,{ eh_void		} ,{ eh_editref_lf	} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_row_number*/	{ { NULL			},{ eh_row_number_gd} ,{ eh_void		} ,{ eh_void		} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_display_text*/{ { NULL			},{ eh_disp_text_gd } ,{ eh_void		} ,{ eh_void		} ,{ NULL				},	{ NULL			},{ NULL			}},	
/*ett_display_ref_text*/{ { eh_disp_ref_text_de	},{ eh_disp_ref_text_gd } ,{ eh_void} ,{ eh_void	} ,{ NULL				},	{ NULL			},{ NULL			}},	
};
#endif

cndoc_event_manager::cndoc_event_manager()
{
}

cndoc_event_manager::~cndoc_event_manager()
{
}

eTransferResult cndoc_event_manager::invoke(cndoc_event_param & roEventParam)
{
	roEventParam.m_poEventManager  = this;
	
	ASSERT(roEventParam.m_poTransfer != NULL);
	ASSERT(roEventParam.m_poEventInfo != NULL);

#ifdef _CUSTOM_HANDLER_ONLY_
	pfEventHandler pfHandler = _g_aHandlers[ 0 ][ roEventParam.m_poEventInfo->get_type() ];
#else
	pfEventHandler pfHandler = _g_aHandlers[ roEventParam.m_poTransfer->get_type()]
		[ roEventParam.m_poEventInfo->get_type() ];
#endif

	ASSERT(pfHandler != NULL);
	
	eTransferResult eResult = pfHandler(roEventParam);

	return eResult;
}

void cndoc_event_manager::mark_failed_handler(ned_ident Ident,eEventInfoType eEIT)
{
	m_oFailedHandlerMap[ longlong(long(Ident),long(eEIT)) ] = true;
}

bool cndoc_event_manager::is_handler_failed(ned_ident Ident,eEventInfoType eEIT) const
{
	bool bDummy;
	return m_oFailedHandlerMap.Lookup(longlong(long(Ident),long(eEIT)),bDummy) != FALSE;
}


void cndoc_event_manager::build_custom_cmd_list(ned_event_command_list * poEventCmdList,
												cned_window * poWindow)
{
	ASSERT(poEventCmdList);
	ASSERT(poWindow);
	SCP<cned_element> poElementSP = poWindow->get_element_on_ident(poEventCmdList->get_firing_element());
	ASSERT(poElementSP.PointsObject());

	ASSERT(poElementSP.PointsObject());
	
	invoke_build_cmd_list(this,poWindow,poElementSP,poEventCmdList->get_command_list());

	SCP<cned_container> poContainerSP = poElementSP->get_container();
	while(poContainerSP.PointsObject())
	{
		invoke_build_cmd_list(this,poWindow,poContainerSP,poEventCmdList->get_command_list());
		poContainerSP = poContainerSP->get_container();
	}
}

//----------------------------------------------------------------
//-------- helpers for handlers ----------------------------------
//----------------------------------------------------------------

SCP<cned_element> get_firing_element(cndoc_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poWindow != NULL);
	ASSERT(roEventParam.m_poEventInfo != NULL);
	SCP<cned_element> poElementSP = 
		roEventParam.m_poWindow->get_element_on_ident(
			roEventParam.m_poEventInfo->get_firing_element()
		);
	ASSERT(poElementSP.PointsObject());
	return poElementSP;
}

void set_valid_state(SCP<cned_element> & rpoElementSP,bool bValid)
{
	ASSERT(rpoElementSP.PointsObject());

	switch(rpoElementSP->get_type())
	{
	case ned_textedit:
	case ned_date:
	case ned_currency:
	case ned_timeed:
		{
			scp_cast_ui<cned_edit__>(rpoElementSP)->set_prop_valid(bValid);
		}
	break;
	case ned_multiline:
		{
			scp_cast_ui<cned_multiedit>(rpoElementSP)->set_prop_valid(bValid);
		}
	break;
	default:
		;	//do nothing
	}
}

ned_ident supply_grid_info(SCP<cned_element> & rpoElementSP,long & rnDataRowNr)
{
	ASSERT(rpoElementSP.PointsObject());

	//uwtórz sciezke do elementu
	ned_path_to_element oPathToElement(rpoElementSP);

	//znajdŸ grid'a (zak³adamy ¿e nie ma zagnie¿dzania)
	if(oPathToElement.is_empty())
	{
		return NEDID_NOTHING;
	}
	while(oPathToElement.top()->get_type() != ned_grid)
	{
		oPathToElement.pop();
		if(oPathToElement.is_empty())
		{
			return NEDID_NOTHING;	//not in grid
		}
	}
	
	ned_ident idGrid = oPathToElement.pop()->get_ident();

	if(oPathToElement.is_empty())	//rpoElementSP musi byæ sekcja
	{
		ASSERT(cast_ui<cned_tablesection>(rpoElementSP.Get()) != NULL);
		return NEDID_NOTHING;
	}

	//pomiñ sekcjê
	SCP<cned_grid_bodysection> poGridBodySectionSP = scp_cast_ui<cned_grid_bodysection>(oPathToElement.pop());

	//znajdŸ wiersz
	SCP<cned_tablerow> poTableRowSP = scp_cast_ui<cned_tablerow>(oPathToElement.is_empty() ? rpoElementSP : oPathToElement.top());
	ASSERT(poTableRowSP.PointsObject());
	ASSERT(poTableRowSP->get_type() == ned_tablerow);
	
	//fill results
	rnDataRowNr = 
		poGridBodySectionSP->datarow_nr_from_table_row_nr(
			poGridBodySectionSP->get_row_nr(poTableRowSP->get_ident()));
	
	return idGrid;
}

ned_ident supply_grid_info2(SCP<cned_element> & rpoElementSP,long & rnDataRowNr,
				SCP<nui_transfer_1> & rpoGridTransferSP)
{
	ned_ident idGrid = supply_grid_info(rpoElementSP,rnDataRowNr);
	ASSERT(NEDID_NOTHING != idGrid);

	rpoGridTransferSP = NewSCP<nui_transfer_1>(
		dynamic_cast<nui_transfer_1*>(rpoElementSP->get_manager()->get_transfer(idGrid).Get()),true);
	ASSERT(rpoGridTransferSP.PointsObject());

	return idGrid;
}

//----------------------------------------------------------------
