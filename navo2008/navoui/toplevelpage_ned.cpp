/*
	NAVO Enterprise 2003
	2003-03-22

	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	top level page element
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "static_ned.h"
#include "win32_ned.h"
#include "CommandList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_toplevelpage::cned_toplevelpage(cned_element_manager * poManager) :
	cned_page(poManager,ned_toplevelpage,NEDID_TOPLEVELPAGE)
{
}

//--------------------------------------------------------
void cned_toplevelpage::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	ASSERT(rpoChildSP.PointsObject());

	switch(rpoChildSP->get_type())
	{
	case ned_subpage:
		_subpage_add(rpoChildSP->get_ident());
	break;
	case ned_olecontrol:
	case ned_htmlwindow:
		_win32ctrl_add(rpoChildSP->get_ident());
	break;
	}
	
	cned_page::on_child_inserted(rpoChildSP);
}

void cned_toplevelpage::on_child_removing(ned_ident idChild)
{
	cned_page::on_child_removing(idChild);

	switch(get_manager()->get_element_type(idChild))
	{
	case ned_subpage:
		_subpage_remove(idChild);
	break;
	case ned_olecontrol:
	case ned_htmlwindow:
		_win32ctrl_remove(idChild);
	break;
	}
}

//--------------------------------------------------------
//------------------ subpage management ------------------
//--------------------------------------------------------

void cned_toplevelpage::_subpage_add(ned_ident idSubPage)
{
	m_oSubPageArray.Add(idSubPage);
}

void cned_toplevelpage::_subpage_remove(ned_ident idSubPage)
{
	for(long iter = 0; iter < m_oSubPageArray.GetSize(); iter++)
	{
		if(m_oSubPageArray[ iter ] == idSubPage)
		{
			m_oSubPageArray.RemoveAt(iter);
			return;
		}
	}
	ASSERT(false);	//usuwanie nieznanej subpage ?
}

void cned_toplevelpage::_subpage_move_by(const ng_size & roDistance)
{
	for(long iter = 0; iter < m_oSubPageArray.GetSize(); iter++)
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(get_element_on_ident(m_oSubPageArray[iter]));
		poPageSP->move_by(-1,roDistance);
	}
}

//--------------------------------------------------------
//------------------ win32 ctrls management ------------------
//--------------------------------------------------------
void cned_toplevelpage::_win32ctrl_add(ned_ident idWin32Ctrl)
{
	m_oWin32Array.Add(idWin32Ctrl);
}

void cned_toplevelpage::_win32ctrl_remove(ned_ident idWin32Ctrl)
{
	for(long iter = 0; iter < m_oWin32Array.GetSize(); iter++)
	{
		if(m_oWin32Array[ iter ] == idWin32Ctrl)
		{
			m_oWin32Array.RemoveAt(iter);
			return;
		}
	}
	ASSERT(false);	//usuwanie nieznanej ctrl ?
}

void cned_toplevelpage::_win32ctrl_move_by(const ng_size & roDistanceSize)
{
	for(long iter = 0; iter < m_oWin32Array.GetSize(); iter++)
	{
		SCP<cned_win32__> poWin32CtrlSP = scp_cast_ui<cned_win32__>(get_element_on_ident(m_oWin32Array[iter]));
		poWin32CtrlSP->arena_move_by(roDistanceSize);
	}
}

//------- paint support --------------------
void cned_toplevelpage::prepare_paint_region(ng_region & roCommonRgn)
{
	ng_point oPageTopLeft;

	//ned_to_do: co z koordynatami subpage -
	//one s¹ wyznaczane w stosunku do ich kontenera, którym nie musi byæ
	//top-page
	
	//najpierw podstrony (one s¹ zawsze przed stron¹)
	for(long iter = m_oSubPageArray.GetUpperBound(); iter >= 0; iter--)
	{
		scp_cast_ui<cned_page>(get_element_on_ident(m_oSubPageArray[ iter ]))->prepare_paint_region(roCommonRgn,oPageTopLeft);
	}
	//potem strona g³ówna
	cned_page::prepare_paint_region(roCommonRgn,oPageTopLeft);
}


void cned_toplevelpage::paint(cned_painter_ & roPainter)
{
	ng_point oPageTopLeft;

	//najpierw strona g³ówna (pod spodem)
	cned_page::paint(roPainter,oPageTopLeft);

	//potem podstrony (one s¹ zawsze przed stron¹)
	for(long iter = m_oSubPageArray.GetUpperBound(); iter >= 0; iter--)
	{
		scp_cast_ui<cned_page>(get_element_on_ident(m_oSubPageArray[ iter ]))->paint(roPainter,oPageTopLeft);
	}
}

//-------------- element finders ------------------------
ned_ident cned_toplevelpage::find_element_from_point(const ng_point & roPoint)
{
	ASSERT(is_inside_hit_area(roPoint));

	//ned_to_do: co z koordynatami subpage -
	//one s¹ wyznaczane w stosunku do ich kontenera, którym nie musi byæ
	//top-page

	for(long iter = 0; iter < m_oSubPageArray.GetSize(); iter++)
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>(get_element_on_ident(m_oSubPageArray[ iter ]));
		if(poPageSP->is_inside_hit_area(roPoint))
		{
			return poPageSP->find_element_from_point(roPoint);
		}
	}
	return cned_page::find_element_from_point(roPoint);
}

//--------------
bool cned_toplevelpage::is_inside_hit_area(const ng_point & roPoint) const
{
	for(long iter = 0; iter < m_oSubPageArray.GetSize(); iter++)
	{
		if(get_element_on_ident(m_oSubPageArray[ iter ])->is_inside_hit_area(roPoint))
		{
			return true;
		}
	}
	return cned_page::is_inside_hit_area(roPoint);
}

void cned_toplevelpage::_invalidate_all_paint()
{
	for(long iter = 0; iter < m_oSubPageArray.GetSize(); iter++)
	{
		get_element_on_ident(m_oSubPageArray[ iter ])->_invalidate_all_paint();
	}
	cned_page::_invalidate_all_paint();
}

//called when put/removed from top of stack

void cned_toplevelpage::on_window_on_top(bool bTopMost)
{
	if(get_prop_caption())
	{
		_get_caption()->set_prop_active(bTopMost);
	}
}

//--------------event handlers ---------------------------------------

//--------------------------------------------------------------------
//command
//--------------------------------------------------------------------
void cned_toplevelpage::_get_scrollable_rect_for_scroll(ng_rect & roRect)
{
	ng_point oCurrentPoint;
	_local2screen(oCurrentPoint);
	oCurrentPoint.offset(get_scroll_pos()); //korekta l2s - ned_to_do
	_get_child_rect(oCurrentPoint,roRect);
}

void cned_toplevelpage::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(roActionCommand.get_target() == get_ident());
	
	switch(roActionCommand.get_verb())
	{
	case sccv_maximize:
	{
		set_prop_display_mode(pdm_maximized);
		roResult.set_processed();
	}
	break;
	case sccv_restore:
	{
		set_prop_display_mode(pdm_normal);
		roResult.set_processed();
	}
	break;
	case sccv_scroll_to:
	{
		ng_rect oScrollableRect;
		_get_scrollable_rect_for_scroll(oScrollableRect);
		_scroll_event_command(roActionCommand,roResult,oScrollableRect);
	}
	break;
	}
}

//--------------------------------------------------------------------
//click
//--------------------------------------------------------------------

void cned_toplevelpage::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(get_prop_display_mode() == pdm_normal)
	{
		get_manager()->store_drag_info(NewSCP(new cned_drag_info_toplevelpage(roActionMouse.get_mouse_position())));
	}
	roResult.set_processed();
}

//--------------------------------------------------------------------
//wheel
//--------------------------------------------------------------------

void cned_toplevelpage::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	ng_rect oScrollableRect;
	_get_scrollable_rect_for_scroll(oScrollableRect);
	_scroll_event_wheel(roActionMouseWheel,roResult,oScrollableRect);
}

//--------------------------------------------------------------------
//key down
//--------------------------------------------------------------------

void cned_toplevelpage::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	switch(roActionKBD.get_keycode())
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_PRIOR:
	case VK_NEXT:
		{
			ng_rect oScrollableRect;
			_get_scrollable_rect_for_scroll(oScrollableRect);
			_scroll_event_kbd(roActionKBD,roResult,oScrollableRect);
		}
	}
}

void cned_toplevelpage::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_page::process_event_mouse_click(roCallStack,roActionMouse,roResult);
	
	if(!roResult.is_processed() && roActionMouse.is_LEFT_click())
	{
		if(get_prop_display_mode() == pdm_normal)
		{
			get_manager()->store_drag_info(NewSCP(new cned_drag_info_toplevelpage(roActionMouse.get_mouse_position())));
		}
		roResult.set_processed();
	}
}

void cned_toplevelpage::process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	cned_page::process_event_mouse_wheel(roCallStack,roActionMouseWheel,roResult);
	
	if(!roResult.is_processed())
	{
		on_event_mouse_wheel(roActionMouseWheel,roResult);
	}
}

void cned_toplevelpage::process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_page::process_event_mouse_endclick(roCallStack,roActionMouse,roResult);
	if(roActionMouse.is_RIGHT_click())
	{
		SCP<CCommandList> poCmdListSP = _create_or_get_command_list(roResult,get_ident());
		ASSERT(poCmdListSP.PointsObject());

		//jesli coœ by³o - dodaj separator
		if(!poCmdListSP->IsEmpty())
		{
			poCmdListSP->AddSeparator();
		}
		
		{
			//komenda 'powiêksz'
			SCP<CHyperLinkInfo> poZoomInHLISP = NewSCP(new CHyperLinkInfo());
			poZoomInHLISP->SetNumProp(GVAR_CMD,CMD_ZOOMIN);
			//LANGUAGE:PL
			poCmdListSP->AddCommand(_T("P&owiêksz (+)"),poZoomInHLISP);
		}

		{
			//komenda 'pomniejsz'
			SCP<CHyperLinkInfo> poZoomOutHLISP = NewSCP(new CHyperLinkInfo());
			poZoomOutHLISP->SetNumProp(GVAR_CMD,CMD_ZOOMOUT);
			//LANGUAGE:PL
			poCmdListSP->AddCommand(_T("Po&mniejsz (-)"),poZoomOutHLISP);
		}
	}
}

//-------- page breaking ---------------------------------
void cned_toplevelpage::fill_clone_split(cpb_split_manager & roSplitManager,SCP<cned_toplevelpage> poDestPageSP,
	const cned_page_break_param & roPBP,long xAreaX,long yAreaY,long xCount,long yCount)
{
	cned_element::fill_clone(poDestPageSP);
	cned_group_helper__::_copy_properties(poDestPageSP);

	poDestPageSP->set_prop_imagesrc(get_prop_imagesrc());

	poDestPageSP->set_prop_extmargins(roPBP.m_oSheetExtMargins);
	poDestPageSP->set_prop_extwidth(roPBP.m_oSheetExtSize.get_dx());
	poDestPageSP->set_prop_extheight(roPBP.m_oSheetExtSize.get_dy());

	//ned_to_do: na razie tu jest to zafixowane
	//ustawienia jak dla print previev
	poDestPageSP->set_prop_backcolor(White);
	poDestPageSP->set_prop_backcolor2(White);

	//----- tytu³
	ng_string oTitleString;
	get_prop_title(oTitleString);

	//LANGUAGE:PL
	ng_string oDestTitleString;
	if(xCount == 1)
	{
		oDestTitleString.Format("%s - strona %d z %d",LPCTSTR(oTitleString), yAreaY + 1, yCount);
	}
	else
	{
		oDestTitleString.Format("%s - strona %d-%d z (%dx%d)",LPCTSTR(oTitleString), 
			yAreaY + 1, xAreaX + 1, yCount,xCount);
	}

	poDestPageSP->set_prop_title(oDestTitleString);
	poDestPageSP->set_prop_caption(false);

	//klonujemy - potem custom mo¿e poprawiæ
	_get_header()->fill_clone(poDestPageSP->_get_header());

	//klonujemy - potem custom mo¿e poprawiæ
	//pusty footer -> wype³niamy staticiem Strona X z Y
	if(!_get_footer()->get_prop_hidden() && _get_footer()->get_child_count() == 0)
	{
		SCP<cned_static> poStaticSP = scp_cast_ui<cned_static>(
			poDestPageSP->_get_footer()->insert_new_element(ned_static,NEDID_NOTHING,NEDID_LAST));
		poStaticSP->set_fixed_properties();
		poStaticSP->set_prop_text(oDestTitleString);
	}
	else
	{
		_get_footer()->fill_clone(poDestPageSP->_get_footer());
	}

	cpb_on_split_event_param oOnPageSplitEventParam;
		oOnPageSplitEventParam.m_oFunctionNameString = "on_page_split";
		oOnPageSplitEventParam.m_poClonedElementSP = poDestPageSP;
		oOnPageSplitEventParam.m_xAreaX = xAreaX;
		oOnPageSplitEventParam.m_yAreaY = yAreaY;
		oOnPageSplitEventParam.m_xCount = xCount;
		oOnPageSplitEventParam.m_yCount = yCount;
	roSplitManager.add_event_param(oOnPageSplitEventParam);
}


void cned_toplevelpage::update_split_info(const ng_point &,cpb_split_info & roSplitInfo)
{
	ng_ydist dyHeaderHeight = _get_header()->get_actual_size().get_dy();
	ng_ydist dyFooterHeight = _get_footer()->get_actual_size().get_dy();

	//redukujemy dostêpn¹ wysokoœæ o rozmiary headera i footera strony
	const ng_ydist yNextPartMaxHeight = 
		roSplitInfo.get_next_part_max_height() - dyHeaderHeight - dyFooterHeight;

	ng_ycoord yFirstParMaxBottom = 
		roSplitInfo.get_actual_bottom() - dyHeaderHeight - dyFooterHeight;

	cpb_split_info oPageSplitInfo(roSplitInfo.get_storage(),
		0,yFirstParMaxBottom,yNextPartMaxHeight,
		roSplitInfo.get_next_part_max_width());

	//odejmujemy obszar zajêty przez header, aby dzieci siê uk³ada³y od pocz¹tku obszaru
	ng_point oPaintPoint(0,-dyHeaderHeight);
	
	_update_children_split_info(oPaintPoint,oPageSplitInfo);
}

void cned_toplevelpage::make_split(const ng_point & ,cpb_split_manager & roSplitManager)
{
	ng_ydist dyHeaderHeight = _get_header()->get_actual_size().get_dy();
	
	//odejmujemy obszar zajêty przez header, aby dzieci siê uk³ada³y od pocz¹tku obszaru
	ng_point oPaintPoint(0,-dyHeaderHeight);

	_make_children_split(oPaintPoint,roSplitManager);
}

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------

cned_drag_info_toplevelpage::cned_drag_info_toplevelpage(const ng_point & roStartingArenaPoint) :
	cned_drag_info__(roStartingArenaPoint),
	m_oLastPoint(roStartingArenaPoint)
{
}

void draw_drag_rect(const ng_rect & roRect,ng_dc & roDC);

bool cned_drag_info_toplevelpage::on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	SCP<cned_toplevelpage> poTopPageSP = scp_cast_ui<cned_toplevelpage>(roActionMouseDrag.get_manager()->get_element_on_ident(NEDID_TOPLEVELPAGE));

	ng_rect oTopPageRect;
	poTopPageSP->get_page_rect(oTopPageRect);
	
	ng_rect oOldRect(oTopPageRect);
	oOldRect.offset(m_oLastPoint.distance(m_oStartingPoint));
	ng_rect oNewRect(oTopPageRect);
	oNewRect.offset(roActionMouseDrag.get_mouse_position().distance(m_oStartingPoint));
	
	if(!(oNewRect == oOldRect))
	{
		draw_drag_rect(oOldRect,roActionMouseDrag.get_dc());
		draw_drag_rect(oNewRect,roActionMouseDrag.get_dc());
	}
	
	m_oLastPoint = roActionMouseDrag.get_mouse_position();

	return true;
}

bool cned_drag_info_toplevelpage::on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	SCP<cned_toplevelpage> poTopPageSP = scp_cast_ui<cned_toplevelpage>(roActionMouseDrag.get_manager()->get_element_on_ident(NEDID_TOPLEVELPAGE));

	ng_rect oTopPageRect;
	poTopPageSP->get_page_rect(oTopPageRect);

	if(!(m_oStartingPoint == m_oLastPoint))
	{
		ng_rect oOldRect(oTopPageRect);
		oOldRect.offset(m_oLastPoint.distance(m_oStartingPoint));
		draw_drag_rect(oOldRect,roActionMouseDrag.get_dc());
	}

	if(!_is_in_void_drag_area(m_oStartingPoint,roActionMouseDrag.get_mouse_position()))
	{
		//ned_to_do: notyfikacja ca³ego view / sheet o tym ¿e siê przesuwa

		//move page to new position
		poTopPageSP->move_to(poTopPageSP->get_arena_position() + 
			roActionMouseDrag.get_mouse_position().distance(m_oStartingPoint));
		
		//invalidujemy stary obszar
		poTopPageSP->invalidate_page();
		
		//oraz nowy obszar
		poTopPageSP->get_page_rect(oTopPageRect);
		roActionMouseDrag.get_manager()->invalidate_paint_rect(oTopPageRect);
	}
	return true;
}



