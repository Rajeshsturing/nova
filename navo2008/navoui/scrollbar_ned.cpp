/*
	NAVO Enterprise 2003
	2003-04-22

	navo enhanced display (NED)


	ned_hscroll / <scrollbar>
	ned_vscroll

	kontrolka scrollbar

	cned_scrollbar__ - wspólna klasa bazowa
*/

#include "stdafx.h"
#include "picture_ned.h"
#include "group_helper_ned.h"
#include "scrollbar_ned.h"
#include "scroll_helper_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cned_scrollbar__::_construct_children()
{
	//call it only once
	ASSERT(NEDID_NOTHING == get_first_child_ident());
	ASSERT(NEDID_NOTHING == get_last_child_ident());

	//top left picture
	{
		SCP<cned_picture> poTopLeftPicSP = 
			scp_cast_ui<cned_picture>(get_manager()->_create_element(ned_picture,NEDID_NOTHING));

		poTopLeftPicSP->_set_container(NewSCP<cned_container>(this,true));

		_link_element(poTopLeftPicSP->get_ident(),NEDID_LAST);

		poTopLeftPicSP->set_prop_imagesrc(CSmartOleVariant(
			-long((get_type() == ned_vscroll) ? esi_verts_upper : esi_horizs_left),VT_I4));
		poTopLeftPicSP->set_fixed_properties();

		poTopLeftPicSP->set_prop_ignore_sys_disable(true);
		poTopLeftPicSP->set_prop_printable(true);
		ned_position oMPosition;

		//ned_to_do: przenieœæ te sta³e do metrics
		
		if(get_type() == ned_vscroll)
		{
			oMPosition.set_top(2540/92*0);	//2540 units/inch * 92dpi * 1 px
		}
		else
		{
			oMPosition.set_left(2540/92*0);	//2540 units/inch * 92dpi * 1 px
		}
		
		poTopLeftPicSP->set_decl_position(oMPosition);

		SCP<CHyperLinkInfo> poHyperLinkSP = init_control_command_hli(get_ident(),sccv_scr_dummy);
		poTopLeftPicSP->set_prop_hyperlink(poHyperLinkSP);
		//LANGUAGE:PL
		poTopLeftPicSP->set_prop_tooltip_text(
			(get_type() == ned_vscroll) ? _T("W górê") : _T("W lewo") );
	}

	//bottom right picture
	{
		SCP<cned_picture> poBottomRightPicSP = 
			scp_cast_ui<cned_picture>(get_manager()->_create_element(ned_picture,NEDID_NOTHING));

		poBottomRightPicSP->_set_container(NewSCP<cned_container>(this,true));

		_link_element(poBottomRightPicSP->get_ident(),NEDID_LAST);

		poBottomRightPicSP->set_prop_imagesrc(CSmartOleVariant(
			-long((get_type() == ned_vscroll) ? esi_verts_lower : esi_horizs_right),VT_I4));
		poBottomRightPicSP->set_fixed_properties();

		poBottomRightPicSP->set_prop_ignore_sys_disable(true);
		poBottomRightPicSP->set_prop_printable(true);
		ned_position oMPosition;

		//ned_to_do: przenieœæ te sta³e do metrics
		if(get_type() == ned_vscroll)
		{
			oMPosition.set_bottom(2540/92*0);	//2540 units/inch * 92dpi * 1 px
		}
		else
		{
			oMPosition.set_right(2540/92*0);	//2540 units/inch * 92dpi * 1 px
		}
		
		poBottomRightPicSP->set_decl_position(oMPosition);

		SCP<CHyperLinkInfo> poHyperLinkSP = init_control_command_hli(get_ident(),sccv_scr_dummy);
		poBottomRightPicSP->set_prop_hyperlink(poHyperLinkSP);
		//LANGUAGE:PL
		poBottomRightPicSP->set_prop_tooltip_text(
			(get_type() == ned_vscroll) ? _T("W dó³") : _T("W prawo") );
	}
}

//--------------------- helpers -----------------------------------------
bool cned_scrollbar__::_compute_position_on_local_point(const ng_point & roLocalPoint)
{
	ng_rect oThumbRect;
	_get_thumb_rect(ng_point(),oThumbRect);
	
	if(oThumbRect.is_inside(roLocalPoint))	//klikniêcie na suwak
	{
		return true;
	}

	//klikniêcie na woln¹ przestrzeñ - wyznaczamy z propocji
	ng_rect oSlidingRect;
	_get_sliding_rect(ng_point(),oSlidingRect);

	//click point
	long nClickPos = (get_type() == ned_vscroll) ? 
		(roLocalPoint.get_y() - oSlidingRect.get_top()) : 
		(roLocalPoint.get_x() - oSlidingRect.get_left());

	long nTotalArea = (get_type() == ned_vscroll) ? oSlidingRect.get_height() : oSlidingRect.get_width();
	ASSERT(nTotalArea > 0);
	long nMoveRange = get_prop_total_range() - get_prop_page_range() - 1;

	set_prop_position((nClickPos + (nTotalArea/nMoveRange/2) )* nMoveRange / nTotalArea);

	return false;
}

void cned_scrollbar__::_compute_position_on_thumb_target(long nThumbTarget)
{
	long nPosition = get_prop_position();
	long nMoveRange = get_prop_total_range() - get_prop_page_range() - 1;

	long nTT;
	long nDummy;
	_compute_thumb_info(ng_point(),nPosition,nTT,nDummy);

	while((nTT < nThumbTarget) && (nPosition < nMoveRange))
	{
		nPosition++;
		_compute_thumb_info(ng_point(),nPosition,nTT,nDummy);
	}
	while((nTT > nThumbTarget) && (nPosition > 0))
	{
		nPosition--;
		_compute_thumb_info(ng_point(),nPosition,nTT,nDummy);
	}
	set_prop_position(nPosition);
}

//--------------event handlers ---------------------------------------

//-------------------------------------------------------------------------------------------------
// command
//-------------------------------------------------------------------------------------------------
void cned_scrollbar__::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(roActionCommand.get_target() == get_ident());
	//ned_to_do:
	roResult.set_processed();
}

void cned_scrollbar__::_on_action_result(long nOldPosition,ned_action_result & roResult)
{
	if(nOldPosition != get_prop_position())
	{
		if(is_mode_embedded())
		{
			SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_container_ident()));
			SCP<CHyperLinkInfo> poScrollCmdHLISP = init_control_command_hli(get_container_ident(),sccv_scroll_to);
			poScrollCmdHLISP->SetNumProp( (get_type() == ned_vscroll) ? PROPC_YPOSITION : PROPC_XPOSITION,get_prop_position());
			poEventCmdSP->set_command(poScrollCmdHLISP);
			roResult.add_info(poEventCmdSP);
		}
		else
		{

			SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
			poEventDataSP->set_data(CSmartOleVariant(get_prop_position(),VT_I4)); 
			roResult.add_info(poEventDataSP);
		}
	}
	else
	{
		roResult.set_processed();
	}
}
//-------------------------------------------------------------------------------------------------
// mouse click
//-------------------------------------------------------------------------------------------------

void cned_scrollbar__::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_LEFT_click() && !get_prop_disabled())
	{
		long nOldPosition = get_prop_position();
		ng_point oPoint(roActionMouse.get_mouse_position());
		if(is_mode_embedded())
		{
			SCP<cned_container> poContainerSP = get_container();
			scroll_helper__ * poScrollHelper = dynamic_cast<scroll_helper__ *>(poContainerSP.Get());
			poScrollHelper->_scroll_screen2local(oPoint);
			oPoint.offset(-m_oVectorSize);
		}
		else
		{
			_screen2local(oPoint);
		}

		if(_compute_position_on_local_point(oPoint))
		{
			get_manager()->store_drag_info(NewSCP(new cned_drag_info_scrollbar(roActionMouse.get_mouse_position(),NewSCP(this,true))));
		}

		_on_action_result(nOldPosition,roResult);
	}
}

//-------------------------------------------------------------------------------------------------
// timer
//-------------------------------------------------------------------------------------------------
const long AUTO_SCROLL_FACTOR = 100;
const long AUTO_SCROLL_SPEED_UP_FACTOR = 33;	//*= 1.03
const long AUTO_SCROLL_INITIAL_SPEED = 100;		//1.0 % ca³oœci (total range / 100)
		
//s³u¿y do przyœpieszania przesuwania - factor - co ile tickow przyspieszac

void cned_scrollbar__::on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	if(roActionTimer.get_timerid() == ARENA_CONTROL_TIMER_ID)
	{
		long nOldPosition = get_prop_position();
		set_prop_position(get_prop_position() + m_nAutoScrollIncrement / AUTO_SCROLL_FACTOR);
		
		m_nAutoScrollIncrement += m_nAutoScrollIncrement / AUTO_SCROLL_SPEED_UP_FACTOR;

		if(nOldPosition == get_prop_position())
		{
			//wyrejestruj siê w timerze
			get_manager()->unregister_for_timer(get_ident());
			m_nAutoScrollIncrement = 0;
		}

		_on_action_result(nOldPosition,roResult);
	}
}


//-------------------------------------------------------------------------------------------------
// forwarders
//-------------------------------------------------------------------------------------------------

void cned_scrollbar__::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(roCallStack.is_empty());
	ASSERT(roCallStack.target()->get_ident() == get_first_child_ident() ||
		roCallStack.target()->get_ident() == get_last_child_ident());

	ned_action_result oDummyResult;
	roCallStack.target()->on_event_mouse_click(roActionMouse,oDummyResult);
	long nOldPosition = get_prop_position();
	
	const long nInitialScrollSpeed = max(1,(get_prop_total_range() / AUTO_SCROLL_INITIAL_SPEED));

	if(roCallStack.target()->get_ident() == get_first_child_ident())
	{
		set_prop_position(get_prop_position() - nInitialScrollSpeed);
		m_nAutoScrollIncrement = -(nInitialScrollSpeed) * AUTO_SCROLL_FACTOR;
	}
	else
	{
		if(roCallStack.target()->get_ident() == get_last_child_ident())
		{
			set_prop_position(get_prop_position() + nInitialScrollSpeed);
			m_nAutoScrollIncrement = +(nInitialScrollSpeed) * AUTO_SCROLL_FACTOR;
		}
		else
		{
			ASSERT(false);
		}
	}

	_on_action_result(nOldPosition,roResult);

	//zarejestruj siê aby otrzymywaæ timer-notyfikacje (auto scroll)
	get_manager()->register_for_timer(get_ident(),1,true);
}

void cned_scrollbar__::process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(roCallStack.is_empty());
	ASSERT(roCallStack.target()->get_ident() == get_first_child_ident() ||
		roCallStack.target()->get_ident() == get_last_child_ident());

	ned_action_result oDummyResult;
	roCallStack.target()->on_event_mouse_click(roActionMouse,oDummyResult);

	roResult.set_processed();

	//wyrejestruj siê w timerze
	get_manager()->unregister_for_timer(get_ident());
	m_nAutoScrollIncrement = 0;
}


//--------- drawing ------------------

//ned_to_do: sta³a przenieœæ do metrics
const long ARROW_IMAGE_DIMENSION = 18;
const long MIN_THUMB_DIMENSION = 12;

void cned_scrollbar__::_get_sliding_rect(const ng_point & roPoint,ng_rect & roSlidingRect) const
{
	roSlidingRect = ng_rect(roPoint,m_oActualSize);

	if(get_type() == ned_vscroll)
	{
		roSlidingRect.set_top(roSlidingRect.get_top() + ARROW_IMAGE_DIMENSION);
		roSlidingRect.set_bottom(roSlidingRect.get_bottom() - ARROW_IMAGE_DIMENSION);
	}
	else
	{
		roSlidingRect.set_left(roSlidingRect.get_left() + ARROW_IMAGE_DIMENSION);
		roSlidingRect.set_right(roSlidingRect.get_right() - ARROW_IMAGE_DIMENSION);
	}
}

void cned_scrollbar__::_compute_thumb_info(const ng_point & roPoint,long nPosition,long & rnThumbTarget,long & rnThumbSize) const
{
	ng_rect oSlidingRect;
	_get_sliding_rect(roPoint,oSlidingRect);
		
	//ca³kowity obszar do przesuwania
	long nTotalArea = (get_type() == ned_vscroll) ? oSlidingRect.get_height() : oSlidingRect.get_width();

	//w stosunku do rozmiaru ca³oœci (get_prop_total_range())
	ASSERT(get_prop_total_range() > 0);
	ASSERT(get_prop_page_range() > 0);
	
	rnThumbSize = (nTotalArea * get_prop_page_range()) / get_prop_total_range(); //rozmiar suwaka
	rnThumbSize = min(nTotalArea,max(rnThumbSize, MIN_THUMB_DIMENSION));		 //najmniejszy rozmiar suwaka
	long nMoveArea = nTotalArea - rnThumbSize;		//obszar do przesuwania (uwzglêdnia rozmiar suwaka)
	ASSERT(nMoveArea >= 0);
	
	ASSERT(get_prop_total_range() >= get_prop_page_range());
	long nMoveRange = get_prop_total_range() - get_prop_page_range() - 1;
	ASSERT(nPosition <= nMoveRange);
	
	long nOffset = (nMoveRange == 0) ? 0 : (nMoveArea * nPosition) / (nMoveRange);

	if(get_type() == ned_vscroll)
	{
		rnThumbTarget = oSlidingRect.get_top() + nOffset;
	}
	else
	{
		rnThumbTarget = oSlidingRect.get_left() + nOffset;
	}
}

void cned_scrollbar__::_get_thumb_rect(const ng_point & roPoint,ng_rect & roThumbRect) const
{
	ng_rect oSlidingRect;
	_get_sliding_rect(roPoint,oSlidingRect);
		
	long nThumbTarget;
	long nThumbSize;

	_compute_thumb_info(roPoint,get_prop_position(),nThumbTarget,nThumbSize);

	if(get_type() == ned_vscroll)
	{
		roThumbRect.set_left(oSlidingRect.get_left());
		roThumbRect.set_right(oSlidingRect.get_right());
		roThumbRect.set_top(nThumbTarget);
		roThumbRect.set_height(nThumbSize);
	}
	else
	{
		roThumbRect.set_top(oSlidingRect.get_top());
		roThumbRect.set_bottom(oSlidingRect.get_bottom());
		roThumbRect.set_left(nThumbTarget);
		roThumbRect.set_width(nThumbSize);
	}
}

void cned_scrollbar__::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_draw_foreground_children(roForePainter,oPaintPoint);
	_draw_std_frame(roForePainter,ng_rect(oPaintPoint,m_oActualSize));

	//ned_to_do: uporz¹dkowaæ to
//	roForePainter.frame_rect(ng_rect(oPaintPoint,m_oActualSize),2,ng_color::system(COLOR_SCROLLBAR),NG_FRAME_EDGE_SUNKENOUTER | NG_FRAME_ALL);

	ng_rect oThumbRect;
	_get_thumb_rect(oPaintPoint,oThumbRect);
	roForePainter.frame_rect(oThumbRect,2,ng_color::system(COLOR_BTNSHADOW),NG_FRAME_EDGE_ROUNDED_XP | NG_FRAME_ALL);

}

void cned_scrollbar__::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oSBRect(oPaintPoint,m_oActualSize);
	_draw_std_background(roBackPainter,oSBRect);
	_draw_background_children(roBackPainter,oPaintPoint);

	//ned_to_do: uporz¹dkowaæ to
	ng_rect oThumbRect;
	_get_thumb_rect(oPaintPoint,oThumbRect);
	oThumbRect.inflate(-2,-2);

	//backcolor='#FFFFFF' backcolor2='#ABBEE6'

	if(get_type() == ned_vscroll)
	{
		roBackPainter.get_dc().fill_rect_hg(oThumbRect,ng_color(0xff,0xff,0xff,0),ng_color(0xab,0xbe,0xe6,0));
	}
	else
	{
		roBackPainter.get_dc().fill_rect_vg(oThumbRect,ng_color(0xff,0xff,0xff,0),ng_color(0xab,0xbe,0xe6,0));
	}

	_store_main_paint_rect(oSBRect);
}

//-------------- rendering support -------------------
void cned_scrollbar__::render(cned_renderer_ & roRenderer)
{
	//zapewnij miejsce
	roRenderer.ensure_width(m_oMetrics.get_minimal_width());

	cned_abspos_render_manager oARM;
	ned_position oAbsPosition;
	
	VERIFY(get_manager()->get_decl_position(get_first_child_ident(),oAbsPosition));
	oARM.register_child(get_element_on_ident(get_first_child_ident()),oAbsPosition,ng_point());

	VERIFY(get_manager()->get_decl_position(get_last_child_ident(),oAbsPosition));
	oARM.register_child(get_element_on_ident(get_last_child_ident()),oAbsPosition,ng_point());

	ng_size oSize = _prepare_size_while_rendering(roRenderer);
	
	ng_size oAbsSize = oARM.render(roRenderer,ng_rect(ng_point(),oSize));

	roRenderer.allocate_rect(get_ident(),-1,oSize,m_oActualSize,m_oVectorSize);
}

//--------------------------------------------------------------------
// horizontal
//--------------------------------------------------------------------

//-------------- rendering support -------------------
void cned_horiz_scrollbar::get_children_metrics(const ned_measure_param & roMParam)
{
	cned_metrics oPictureMetrics;
	get_element_on_ident(get_first_child_ident())->get_metrics(roMParam,oPictureMetrics);
	get_element_on_ident(get_last_child_ident())->get_metrics(roMParam,oPictureMetrics);

	

	m_oMetrics.update(
		oPictureMetrics.get_minimal_width() * 2 + MIN_THUMB_DIMENSION,
		oPictureMetrics.get_minimal_height(),oPictureMetrics.get_weight());
}

ng_size cned_horiz_scrollbar::_prepare_size_while_rendering(cned_renderer_ & roRenderer)
{
	return ng_size(_get_std_width_for_rendering(roRenderer),
		m_oMetrics.get_minimal_height());
}

//--------------------------------------------------------------------
// vertical
//--------------------------------------------------------------------
//-------------- rendering support -------------------
void cned_vert_scrollbar::get_children_metrics(const ned_measure_param & roMParam)
{
	cned_metrics oPictureMetrics;
	get_element_on_ident(get_first_child_ident())->get_metrics(roMParam,oPictureMetrics);
	get_element_on_ident(get_last_child_ident())->get_metrics(roMParam,oPictureMetrics);

	m_oMetrics.update(oPictureMetrics.get_minimal_width(),
		oPictureMetrics.get_minimal_height() * 2 + MIN_THUMB_DIMENSION,oPictureMetrics.get_weight());
}

ng_size cned_vert_scrollbar::_prepare_size_while_rendering(cned_renderer_ & roRenderer)
{
	ng_ydist dyHeight = 100;	//sta³a do metrics (na wszelki wypadek)
	if(is_normal_height_value(get_prop_extheight()))
	{
		dyHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
	}
	else
	{
		ASSERT(false);
#ifdef _DEVELOPER_EDITION_
		AfxMessageBox("Attribute height is required for <vscroll>!");
#endif
	}

	return ng_size(m_oMetrics.get_minimal_width(),dyHeight);
}

//--------------------------------------------------------------------
// dragging support
//--------------------------------------------------------------------
cned_drag_info_scrollbar::cned_drag_info_scrollbar(const ng_point & roStartingArenaPoint,
	SCP<cned_scrollbar__> poScrollBarSP) :
	cned_drag_info__(roStartingArenaPoint),
		m_poScrollbarSP(poScrollBarSP)
{
	ASSERT(m_poScrollbarSP.PointsObject());

	m_nInitialOffset = m_poScrollbarSP->_get_current_thumb_target();
}

bool cned_drag_info_scrollbar::on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	long nOldPosition = m_poScrollbarSP->get_prop_position();

	ng_size oSize = roActionMouseDrag.get_mouse_position().distance(m_oStartingPoint);
	long nTargetThumb = m_nInitialOffset;
	if(m_poScrollbarSP->get_type() == ned_vscroll)
	{
		nTargetThumb += oSize.get_dy();
	}
	else
	{
		nTargetThumb += oSize.get_dx();
	}

	m_poScrollbarSP->_compute_position_on_thumb_target(nTargetThumb);
	m_poScrollbarSP->_on_action_result(nOldPosition,roResult);

	return true;
}

bool cned_drag_info_scrollbar::on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult)
{
	//ned_to_do
	return true;
}


