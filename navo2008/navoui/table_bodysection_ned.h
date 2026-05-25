/*
	NAVO Enterprise 2003
	2003-04-01

	navo enhanced display (NED)

	ned_tablebodysection / <tbody> 
		sekcja body tabelki
*/

#ifndef _TABLE_BODY_SECTION_NED_H_
#define _TABLE_BODY_SECTION_NED_H_

namespace ned
{

class cned_table_bodysection : public cned_tablesection, public scroll_helper__
{
public:
	cned_table_bodysection(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);
	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	//-------------- rendering support -------------------
	virtual void get_children_metrics(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);
//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);
//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult);

	virtual ng_ydist _correct_rendered_section_height(cned_renderer_ & roRenderer,ng_ydist yHeight);
	//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
	virtual void _screen2local(ng_point & roPoint) const;
	virtual void _local2screen(ng_point & roPoint) const;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
inline void cned_table_bodysection::_screen2local(ng_point & roPoint) const
{
	cned_tablesection::_screen2local(roPoint);
	roPoint.offset(get_scroll_pos());
}

inline void cned_table_bodysection::_local2screen(ng_point & roPoint) const
{
	cned_tablesection::_local2screen(roPoint);
	roPoint.offset(-get_scroll_pos());
}


}

#else
	#error __FILE__ already included
#endif
