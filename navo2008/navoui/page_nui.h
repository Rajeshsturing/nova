/*
	NAVO Enterprise 2008
	15.04.2002
	
	cnui_page
		strona (subpage lub toplevelpage)
*/


#ifndef _PAGE_NUI_H_
#define _PAGE_NUI_H_

#ifdef nigdy_nie_definiuj_bo_stare_i_nie_uzywane

struct cnui_page_rendering_info;
class cnui_render_info__;
class cnui_printing_info;


class cnui_page : public cnui_group_container, public cnui_layer__, public scrollable__
{
public:
//XPART
	void set_position_on_arena(const ng_size & roArenaPosition);
	const ng_size & get_position_on_arena() const;
//~XPART

	virtual ng_ycoord render(cnui_renderer__ & roRenderer);

	virtual void get_area(ng_area & roElementLUArea) const;
	virtual void get_back_areas(ng_area & roBackLUArea) const;
	virtual void get_child_rect(ng_rect & roRect) const;


	virtual void layer_paint(cnui_painter & roPainter);

	virtual void get_layer_area(ng_area & roArea) const;
	//-------------------------------------------------------- 
	virtual void on_event_mouse_wheel(const nui_action_mouse_wheel & roActionMouseWheel,nui_action_result & roResult);
	virtual void process_event_keydown(nui_action_call_stack & roCallStack,const nui_action_kbd & roActionKBD,nui_action_result & roResult);
	virtual void process_event_mouse_wheel(nui_action_call_stack & roCallStack,const nui_action_mouse_wheel & roActionMouseWheel,nui_action_result & roResult);
	virtual void process_event_focus(nui_action_call_stack & roCallStack,const nui_action_focus & roActionFocus,nui_action_result & roResult);

	virtual void on_compact_memory();

	virtual void get_scrollable_rect(ng_rect & roRect);

protected:
	cnui_page(cnui_element_manager * poManager,const enui_type eType,const nui_ident nIdent);
	
	void _get_back_rect(const ng_point & roCurrentPoint,ng_rect & roBodyRect) const;
	void _get_title_rect(const ng_point & roCurrentPoint,ng_rect & roTitleRect) const;
	void _get_body_rect(const ng_point & roCurrentPoint,ng_rect & roInteriorRect) const;
	void _get_shadows_rects(const ng_point & roCurrentPoint,ng_rect & roRightShadowRect,ng_rect & roBottomShadowRect) const;

	void _paint_shadows(cnui_painter & roPainter,const ng_point & roCurrentPoint);
	
	void _draw_back_image(cnui_back_painter & roBackPainter,const ng_rect & roBodyRect);

	void __fill_rendering_info(cnui_render_info__ & roRender,cnui_page_rendering_info & roInfo);

//XPART
	ng_size _get_top_left_margin() const;
	ng_size _get_right_bottom_margin() const;
	bool _is_inside_body_area(const ng_point & roPoint) const;	//roPoint we wspó³rzêdnych strony (zewnêtrznych do body)

	ng_xdist			m_xLastRenderWidth;
};


class cnui_layerstack;


#endif


#else
	#error __FILE__ already included
#endif
