/*
	NAVO Enterprise 2008
	2003-04-03

	cned_tablesection
		sekcja tabelki
		core part
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "scroll_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "table_bodysection_ned.h"
#include "tablerow_ned.h"
#include "tablecell_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cned_table_bodysection::cned_table_bodysection(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_tablesection(poManager,eType,idThis),
	scroll_helper__(poManager,idThis)
{
}

//-------------- element finders ------------------------
ned_ident cned_table_bodysection::find_element_from_point(const ng_point & roPoint)
{
	//uwzglêdnij scroll
	ng_point oInternalPoint(roPoint);
	oInternalPoint.offset(get_scroll_pos());

	return cned_tablesection::find_element_from_point(oInternalPoint);
}

//--------- drawing ------------------
void cned_table_bodysection::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oSectionRect(oPaintPoint,m_oActualSize);

	cned_scroll_clipper oScrollClipper(roForePainter,oSectionRect);

	ng_point oChildrenPoint(roCurrentPoint);

	if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		oChildrenPoint.offset(-get_scroll_pos());
	}
	cned_tablesection::draw_foreground(roForePainter,oChildrenPoint);
}

void cned_table_bodysection::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oSectionRect(oPaintPoint,m_oActualSize);

	cned_scroll_clipper oScrollClipper(roBackPainter,oSectionRect);
		
	ng_point oChildrenPoint(roCurrentPoint);
	if(roBackPainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		oChildrenPoint.offset(-get_scroll_pos());
	}
	cned_tablesection::draw_background(roBackPainter,oChildrenPoint);
}

//-------------- rendering support -------------------
void cned_table_bodysection::get_children_metrics(const ned_measure_param & roMParam)
{
	ned_measure_param oChildMParam(roMParam);
	//ned_to_do: scroll
	cned_tablesection::get_children_metrics(oChildMParam);
}

void cned_table_bodysection::render(cned_renderer_ & roRenderer)
{
	//ned_to_do: scroll
	//ned_to_do: childrenderer

	cned_tablesection::render(roRenderer);
}

ng_ydist cned_table_bodysection::_correct_rendered_section_height(cned_renderer_ & roRenderer,ng_ydist yHeight)
{
	if(is_normal_height_value(get_prop_extheight()))
	{
		ng_ydist dyHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
		if(dyHeight < yHeight)
		{
			//ned_to_do: na razie to roboczo
			show_vertical_bar(roRenderer,ng_point(roRenderer.get_current_width(),0),yHeight,yHeight,dyHeight);
		}
		else
		{
			hide_vertical_bar();
		}
		return dyHeight;
	}
	else
	{
		return cned_tablesection::_correct_rendered_section_height(roRenderer,yHeight);
	}
}

//--------------------------------------------------------------------
//wheel
//--------------------------------------------------------------------

void cned_table_bodysection::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	ng_point oCurrentPoint;
	_local2screen(oCurrentPoint);
	
	oCurrentPoint.offset(get_scroll_pos()); //korekta - pomijamy nasze w³asne przescrolowanie

	ng_rect oScrollableRect(oCurrentPoint,m_oActualSize);

	_scroll_event_wheel(roActionMouseWheel,roResult,oScrollableRect);
}

void cned_table_bodysection::process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	cned_tablesection::process_event_mouse_wheel(roCallStack,roActionMouseWheel,roResult);
	
	if(!roResult.is_processed())
	{
		on_event_mouse_wheel(roActionMouseWheel,roResult);
	}
}



