/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	01.08.2002

	deklaracje handlerów zdarzeñ 
*/


#ifndef _EVENT_HANDLER_IMPL_NDOC_H_
#define _EVENT_HANDLER_IMPL_NDOC_H_

//data entered = eit_newdata
eTransferResult eh_custom_de(cndoc_event_param & roEventParam);
eTransferResult eh_editfield_de(cndoc_event_param & roEventParam);
eTransferResult eh_editref_de(cndoc_event_param & roEventParam);
eTransferResult eh_row_edfld_de(cndoc_event_param & roEventParam);
eTransferResult eh_row_edref_de(cndoc_event_param & roEventParam);
eTransferResult eh_disp_ref_text_de(cndoc_event_param & roEventParam);

//get data = eit_getdata
eTransferResult eh_custom_gd(cndoc_event_param & roEventParam);
eTransferResult eh_editfield_gd(cndoc_event_param & roEventParam);
eTransferResult eh_editref_gd(cndoc_event_param & roEventParam);
eTransferResult eh_row_edfld_gd(cndoc_event_param & roEventParam);
eTransferResult eh_row_edref_gd(cndoc_event_param & roEventParam);
eTransferResult eh_row_number_gd(cndoc_event_param & roEventParam);
eTransferResult eh_grid_list_gd(cndoc_event_param & roEventParam);
eTransferResult eh_disp_text_gd(cndoc_event_param & roEventParam);
eTransferResult eh_disp_ref_text_gd(cndoc_event_param & roEventParam);

//got focus = eit_gotfocus
eTransferResult eh_custom_gf(cndoc_event_param & roEventParam);

//lost focus = eit_lostfocus
eTransferResult eh_custom_lf(cndoc_event_param & roEventParam);
eTransferResult eh_editref_lf(cndoc_event_param & roEventParam);

//row operations = eit_row_oper
eTransferResult eh_custom_ro(cndoc_event_param & roEventParam);
eTransferResult eh_grid_list_ro(cndoc_event_param & roEventParam);

//ole event = eit_oleevent
eTransferResult eh_custom_oe(cndoc_event_param & roEventParam);

eTransferResult eh_custom_tabia(cndoc_event_param & roEventParam);

#else
	#error __FILE__ already included
#endif
