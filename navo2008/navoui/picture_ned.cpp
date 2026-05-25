/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_picture		/ <picture>
		kontrolka obrazka
*/

#include "stdafx.h"
#include "picture_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void cned_picture::set_fixed_properties()
{
	cned_rect_element_::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_printable(false);
	set_prop_border_type(NED_BORDER_STYLE_NONE);
}

void cned_picture::set_prop_animate(long nAnimateInterval)
{
	if(get_prop_animate() == nAnimateInterval)
	{
		return;
	}
	if(get_prop_animate() != 0)
	{
		get_manager()->unregister_for_timer(get_ident());
	}
	
	m_nAnimate = nAnimateInterval;

	if(get_prop_animate() != 0)
	{
		get_manager()->register_for_timer(get_ident(),m_nAnimate,false);
	}

	_vse_dirty();
}

//---------------------------------------------------------------------------
ng_size cned_picture::_compute_min_size(const ned_measure_param & roMParam)
{
	_load_picture();
	ASSERT(m_poImageSP.PointsObject());
	
	ng_size oCompleteSize;

	if(m_poImageSP.PointsObject())
	{
		//zak³adamy ¿e obrazek by³ renderowany na 96 dpi - w razie czego mo¿na dorobiæ
		//funkcjê get_horizontal_resolution (GDI+ supportuje to) - gdyby by³ renderowany na coœ innego
		//m_poImageSP->get_width() / 96 dpi * 2540 = external units
		oCompleteSize = ng_size(m_poImageSP->get_width() * 2540 / 96,m_poImageSP->get_height() * 2540 / 96);
	}
	else
	{
		oCompleteSize = ng_size(_metrics().picture().get_default_width(),_metrics().picture().get_default_height());
	}
	//complete size in external units here 
	if(is_normal_width_value(get_prop_extwidth()))
	{
		oCompleteSize.set_dx( get_prop_extwidth() );
	}
	if(is_normal_height_value(get_prop_extheight()))
	{
		oCompleteSize.set_dy( get_prop_extheight() );
	}
	//convert complete size to internal units
	
	oCompleteSize = get_manager()->to_internal(oCompleteSize);

	//add margins
	{
		oCompleteSize.set_dx(oCompleteSize.get_dx() + 
			_metrics().picture().get_left_margin() + _metrics().picture().get_right_margin());
		oCompleteSize.set_dy(oCompleteSize.get_dy() + 
			_metrics().picture().get_top_margin() + _metrics().picture().get_bottom_margin());
	}
	return oCompleteSize;
}

//-------------------------------------------------------------------------------------------
/* 
	'¿adanie obrazka' zg³aszane przez cnui_picture
*/

class cned_picture_image_reguest : public ng_image_request
{
public:
	cned_picture_image_reguest(SCP<cned_picture> poPictureSP):
		m_poPictureSP(poPictureSP)
	{
		ASSERT(poPictureSP.PointsObject());
	}
	virtual void on_image_ready(bool bPositive)
	{
		m_poPictureSP->on_image_ready(bPositive);
	}
private:
	SCP<cned_picture> m_poPictureSP;
};

void cned_picture::on_image_ready(bool bPositive)
{
	//ned_to_do:
}

void cned_picture::_load_picture()
{
	if(m_poImageSP.PointsObject())
	{
		return;
	}

	ALL_TRY
	{
		m_poImageSP = get_manager()->get_image(m_oIdImageSourceSOV,
			NewSCP(new cned_picture_image_reguest(NewSCP(this,true))));
	}
	ALL_CATCH(CNavoException & roException)
	{
		m_poImageSP = get_manager()->get_special_image(esi_missing);

		CString oString = "u¿yto obrazka zastêpczego";
		ContinueThrowNavoException1(roException, ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}

	ASSERT(m_poImageSP.PointsObject());

	if(get_prop_animate() != 0)
	{
		m_nFrameCount = max(1,m_poImageSP->get_frame_count());
	}
}

//--------- drawing ------------------
void cned_picture::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_load_picture();
	
	ng_rect oFrameRect(oPaintPoint,m_oActualSize);

	ng_rect oImageRect;
	_get_image_rect(oPaintPoint,oImageRect,true);

	if(get_prop_animate() != 0 && !_is_fast_graphics())
	{
		ASSERT(m_nFrameCount >= 1);
		if(m_poImageSP.PointsObject())
		{
			roForePainter.get_dc().draw_image_frame(oFrameRect,m_poImageSP,m_eScalingMode,
				m_nCurrentFrame++ % m_nFrameCount);
		}
	}
	else
	{
		bool bMouseOver = (get_manager()->get_mouse_over_element() == get_ident());
		bool bActive = (m_poHyperLinkInfoSP.PointsObject() && !roForePainter.is_effectively_disabled(this));
		
		//OS_API_CALL
		bool bLButtonDown = ((::GetAsyncKeyState(VK_LBUTTON) & 0x8000)  != 0);
		
		if(bActive && bMouseOver && bLButtonDown)
		{
			oImageRect.offset(2,2);
		}
		if(m_poImageSP.PointsObject())
		{
			ng_size oScrollSize; //ned_to_do: scroll
			roForePainter.get_dc().draw_image(oImageRect,oScrollSize,
				m_poImageSP,m_eScalingMode,
				(roForePainter.is_effectively_disabled(this)) ? ngif_disable : ngif_col2tran);
		}
		else
		{
			//ned_to_do: low memory mode ??
		}
		
		if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
		{
			if(bActive) 
			{
				roForePainter.frame_rect(oFrameRect,1,get_prop_border_color(),
					(bMouseOver && bLButtonDown) ? NG_FRAME_EDGE_ROUNDED_XP2 : NG_FRAME_EDGE_ROUNDED_XP);
			}
			else
			{
				if(m_poHyperLinkInfoSP.PointsObject())
				{
					ASSERT(get_prop_disabled());
					roForePainter.frame_rect(oFrameRect,1,ng_color::system(COLOR_GRAYTEXT),
						NG_FRAME_EDGE_ROUNDED_XP);
				}
				else
				{
					_draw_std_frame(roForePainter,oImageRect);
				}
			}
		}
	}
	
	_store_main_paint_rect(oFrameRect);
}

void cned_picture::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_load_picture();

	ng_rect oImageRect;
	_get_image_rect(oPaintPoint,oImageRect,true);
	_draw_std_background(roBackPainter,oImageRect);

}


//--------------event handlers ---------------------------------------
void cned_picture::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(!get_prop_disabled());
	if(get_prop_hyperlink().PointsObject() && roActionMouse.is_LEFT_click())
	{
		_invalidate_all_paint();
		_set_focus_to_me();
		roResult.set_processed();
	}
}

void cned_picture::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	ASSERT(get_prop_hyperlink().PointsObject());
	ASSERT(!get_prop_disabled());

	if((roActionKBD.is_normal() && 
	   (roActionKBD.get_keycode() == VK_RETURN || roActionKBD.get_keycode() == VK_SPACE)) ||
	   (get_manager()->lookup_shortkeys(roActionKBD) == get_ident())
	  )
	{
		SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
		poEventCmdSP->set_command(m_poHyperLinkInfoSP);
		roResult.add_info(poEventCmdSP);
	}
}

void cned_picture::on_event_mouse_over(const ned_action_mouse &,ned_action_result & roResult)
{
	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_all_paint();
		roResult.set_processed();
	}
}

void cned_picture::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(!get_prop_disabled());

	if(roActionMouse.is_LEFT_click())
	{
		if(get_prop_hyperlink().PointsObject())
		{
			SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
			poEventCmdSP->set_command(get_prop_hyperlink());
			roResult.add_info(poEventCmdSP);
				
			_invalidate_all_paint();
		}
	}
	else
	{
		if(roActionMouse.is_RIGHT_click())
		{
			SCP<ned_event_command_list> poEventCmdListSP = NewSCP(new ned_event_command_list(get_ident()));
			roResult.add_info(poEventCmdListSP);
		}
	}
}

void cned_picture::on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult)
{
	ASSERT(get_prop_animate() != 0);

	if(roActionTimer.get_timerid() == ARENA_CONTROL_TIMER_ID)
	{
		_invalidate_all_paint();
		roResult.set_processed();
	}
}

eCursorType cned_picture::on_event_set_cursor(const ng_point &)
{
	return (get_prop_hyperlink().PointsObject() && !get_prop_disabled()) ? ect_hand : ect_default;
}

