/*
	NAVO Enterprise 2003
	2003-03-28

	navo enhanced display (NED)

	ned_button / <button>

	przycisk
*/

#include "stdafx.h"
#include "static_ned.h"
#include "button_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void cned_button::_create_test_string(ng_string & roTestString) const
{
	if(m_nDeclCharWidth > 0 && m_oTextString.GetLength() < m_nDeclCharWidth)
	{
		//wg deklarowanego rozmiaru
		roTestString = ng_string('7', m_nDeclCharWidth + 6);
	}
	else
	{
		roTestString = "777" + m_oTextString + "777";
	}
	ASSERT(!roTestString.IsEmpty());
}

ng_size cned_button::_compute_min_size(const ned_measure_param & roMParam)
{
	//compute complete size
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	ng_string oTestString;
	_create_test_string(oTestString);
	ng_size oCompleteSize = roMParam.get_info_dc().measure_string(oTestString,MAXLONG,poFontSP,NULL);
	oCompleteSize.set_dx(oCompleteSize.get_dx() + _metrics().button().get_left_margin() 
		+ _metrics().button().get_right_margin());
	oCompleteSize.set_dy(oCompleteSize.get_dy() + _metrics().button().get_top_margin()
		+ _metrics().button().get_bottom_margin());
	
	
	return oCompleteSize;
}

ned_fontinx get_bolded_font(cned_element_manager * poManager,const ned_fontinx inxInputFont,bool bBolded);

void cned_button::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oTextRect;
	_get_text_rect(oPaintPoint,oTextRect);

	_store_extra_paint_rect(cned_static::TEXT_PAINT_RECT_ID,oTextRect);

	bool bActive = (m_poHyperLinkInfoSP.PointsObject() && !roForePainter.is_effectively_disabled(this));
	bool bMouseOver = (get_manager()->get_mouse_over_element() == get_ident());
	bool bLButtonDown = ((::GetAsyncKeyState(VK_LBUTTON) & 0x8000)  != 0);
	bool bFocused = get_prop_focus();
	
	if(bActive && bMouseOver && bLButtonDown)
	{
		oTextRect.offset(2,2);
	}

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(bFocused ? 
		get_bolded_font(get_manager(),get_prop_fontinx(),true) : get_prop_fontinx());
	
	//compute real text size - it can differs for focused and not focused button
	ng_xdist dxTextWidth = roForePainter.get_dc().measure_string(m_oTextString,MAXLONG,poFontSP,NULL).get_dx();

	ASSERT(dxTextWidth >= 0);
	ng_xdist xTextOffset = max(0,(m_oActualSize.get_dx() - dxTextWidth) / 2);

	ASSERT(xTextOffset >= 0);
	oTextRect.offset(xTextOffset,0);

	ng_color oForeColor = get_prop_forecolor();
	if(roForePainter.is_effectively_disabled(this))
	{
		oForeColor = ng_color::system(COLOR_GRAYTEXT);
	}
	else
	{
		if(bActive && bMouseOver)
		{
			oForeColor = _metrics().text().get_highlight_color();
		}
	}

	roForePainter.print_text(oTextRect,m_oTextString,oForeColor,poFontSP);
	
	ng_rect oFrameRect(oPaintPoint,m_oActualSize);

	if(bActive)
	{
		roForePainter.frame_rect(oFrameRect,3,get_prop_border_color(),
			(bMouseOver && bLButtonDown) ? NG_FRAME_EDGE_ROUNDED_XP2 : NG_FRAME_EDGE_ROUNDED_XP);
	}
	else
	{
		roForePainter.frame_rect(oFrameRect,3,ng_color::system(COLOR_GRAYTEXT),
			NG_FRAME_EDGE_ROUNDED_XP);
	}

}

void cned_button::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oTextRect;
	_get_text_rect(oPaintPoint,oTextRect);

	if(!roBackPainter.get_paint_param().paint_background())
	{
		return;
	}
	
	if(get_prop_backcolor() != Transparent && get_prop_backcolor2() != Transparent)
	{
		roBackPainter.fill_rect_vg(oTextRect,get_prop_backcolor(),get_prop_backcolor2());
	}

	_store_main_paint_rect(ng_rect(oPaintPoint,m_oActualSize));
}

//--------------------------------------------------------------------
//--------------event handlers ---------------------------------------
//--------------------------------------------------------------------
void cned_button::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_all_paint();
		roResult.set_processed();
	}
}

void cned_button::on_event_mouse_click(const ned_action_mouse &,ned_action_result & roResult)
{
	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_all_paint();
		roResult.set_processed();
	}
}
