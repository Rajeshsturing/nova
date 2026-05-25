/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	ned_static / <t>

	jednoliniowy tekst / hyperlink

*/

#include "stdafx.h"
#include "static_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long cned_static::TEXT_PAINT_RECT_ID = 1;

//--------------------------------------------------------
//--------------------------------------------------------
void cned_static::set_fixed_properties()
{
	cned_rect_element_::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_border_type(NED_BORDER_STYLE_NONE);
}

//------- creates string for dimension tests -------------
//
// when declared size is bigger than actual one
// function synteses string from declared size 
//
//--------------------------------------------------------

void cned_static::_create_test_string(ng_string & roTestString) const
{
	ASSERT(m_nDeclCharWidth >= 0);
	if(m_nDeclCharWidth > 0 && m_oTextString.GetLength() < m_nDeclCharWidth)
	{
		//rozmiar zadeklarowany wiêkszy ni¿ rzeczywisty - symuluj:
		//symulowany string sk³ada siê z 7-znakowych "s³ów", tak aby
		//procedura podzia³u na s³owa (word break) mia³a szansê podzieliæ
		// i nie walczy³a z niespotykanym przypadkiem bardzo d³ugiego s³owa
		//7-znaków wybrano abritralnie

		LPSTR ptr = roTestString.GetBuffer(m_nDeclCharWidth);
		long nCnt = m_nDeclCharWidth;
		while(nCnt > 7)
		{
			memcpy(ptr,"777777 ",7);
			ptr += 7;
			nCnt -= 7;
		}
		_tcsncpy(ptr,"777777 ",nCnt);
		ptr[nCnt] = '\0';
		roTestString.ReleaseBuffer();
	}
	else
	{
		roTestString = m_oTextString;
	}
	if(roTestString.IsEmpty())	//at least one char
	{
		roTestString = "7";
	}
}

//--------------------------------------------------------
ng_size cned_static::_compute_min_size(const ned_measure_param & roMParam)
{
	ng_string oTestString;
	_create_test_string(oTestString);

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	ng_size oCompleteSize = roMParam.get_info_dc().measure_string(oTestString,MAXLONG,poFontSP,NULL);
	
	//podana szerokoœæ (width) ma wy¿szy priorytet ni¿ size

	if(is_normal_width_value(get_prop_extwidth()))
	{
		oCompleteSize.set_dx(get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx());
	}
	if(is_normal_height_value(get_prop_extheight()))
	{
		oCompleteSize.set_dy(get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy());
	}

	//compute real text size (based on real chars. not declararion)
	m_xTextWidth = roMParam.get_info_dc().measure_string(m_oTextString,MAXLONG,poFontSP,NULL).get_dx();
	
	if(get_prop_border_type() == NED_BORDER_STYLE_TABITEM_HEADER_UP || 
	   get_prop_border_type() == NED_BORDER_STYLE_TABITEM_HEADER_DOWN)
	{
		oCompleteSize.set_dx(oCompleteSize.get_dx() + 2 * _metrics().text().get_horiz_tabheader_margin());
		oCompleteSize.set_dy(oCompleteSize.get_dy() + 2 * _metrics().text().get_vert_tabheader_margin());
	}
	

	return oCompleteSize;
}

//--------------------------------------------------------
//--------- drawing ------------------
//--------------------------------------------------------
ned_fontinx get_underlined_font(cned_element_manager * poManager,const ned_fontinx inxNormalFont)
{
	ASSERT(poManager != NULL);
	ned_font_spec oUnderlinedFont = poManager->get_font_spec_on_inx(inxNormalFont);
	oUnderlinedFont.m_bUnderLine = true;
	return poManager->get_inx_for_font_spec(oUnderlinedFont);
}

ned_fontinx get_bolded_font(cned_element_manager * poManager,const ned_fontinx inxInputFont,bool bBolded)
{
	ASSERT(poManager != NULL);
	ned_font_spec oBoldedFont = poManager->get_font_spec_on_inx(inxInputFont);
	oBoldedFont.m_bBold = bBolded;
	return poManager->get_inx_for_font_spec(oBoldedFont);
}

void cned_static::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	bool bMouseOver = (get_manager()->get_mouse_over_element() == get_ident());
	bool bActive = (m_poHyperLinkInfoSP.PointsObject() && !roForePainter.is_effectively_disabled(this));
	bool bFocused = get_prop_focus();

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(((bMouseOver ||bFocused) && bActive) ? 
		get_underlined_font(get_manager(),get_prop_fontinx()) : get_prop_fontinx());

	ng_color oForeColor = get_prop_forecolor();
	if(roForePainter.is_effectively_disabled(this))
	{
		if(!_metrics().is_high_contrast())
		{
			oForeColor = ng_color::system(COLOR_GRAYTEXT);
		}
	}
	else
	{
		if(bMouseOver && bActive)
		{
			oForeColor = _metrics().text().get_highlight_color();
		}
	}

	ng_rect oTextRect(oPaintPoint,m_oActualSize);

	if(get_prop_border_type() == NED_BORDER_STYLE_TABITEM_HEADER_UP || 
	   get_prop_border_type() == NED_BORDER_STYLE_TABITEM_HEADER_DOWN)
	{
		oTextRect.inflate(
			- _metrics().text().get_horiz_tabheader_margin(),
			- _metrics().text().get_vert_tabheader_margin(),
			- _metrics().text().get_horiz_tabheader_margin(),
			- _metrics().text().get_vert_tabheader_margin());
	}
	ASSERT(m_xTextWidth >= 0);

	ng_xdist xTextOffset = 0;

	//dynamicznie wyliczamy po³o¿enie tekstu
	switch(eal_horizmask & get_prop_alignment())
	{
	case eal_left:
	case eal_justify:		//ned_to_do: justification not supported
		xTextOffset = 0;
	break;
	case eal_right:
		xTextOffset = max(0,m_oActualSize.get_dx() - m_xTextWidth);
	break;
	case eal_center:
		xTextOffset = max(0,(m_oActualSize.get_dx() - m_xTextWidth)/2);
	break;
	default:
		ASSERT(false);
	}

	oTextRect.inflate(-xTextOffset,0,0,0);

	roForePainter.print_text(oTextRect,m_oTextString,oForeColor,poFontSP);
	
	_draw_std_frame(roForePainter,ng_rect(oPaintPoint,m_oActualSize));

	_store_extra_paint_rect(TEXT_PAINT_RECT_ID,oTextRect);
}

void cned_static::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oBackRect(oPaintPoint,m_oActualSize);
	oBackRect.inflate(-1,-1);
	_draw_std_background(roBackPainter,oBackRect);

	_store_main_paint_rect(ng_rect(oPaintPoint,m_oActualSize));
}


void cned_static::_invalidate_text_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),TEXT_PAINT_RECT_ID);
}

//--------------------------------------------------------------------
//--------------event handlers ---------------------------------------
//--------------------------------------------------------------------

void cned_static::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	ASSERT(get_prop_hyperlink().PointsObject());
	ASSERT(!get_prop_disabled());

	if((roActionKBD.is_normal() && 
	   (roActionKBD.get_keycode() == VK_RETURN || roActionKBD.get_keycode() == VK_SPACE)) ||
	   (get_manager()->lookup_shortkeys(roActionKBD) == get_ident())
	  )
	{
		SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
		poEventCmdSP->set_command(get_prop_hyperlink());
		roResult.add_info(poEventCmdSP);
	}
}

void cned_static::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(!get_prop_disabled());

	if(get_prop_hyperlink().PointsObject() && roActionMouse.is_LEFT_click())
	{
		_set_focus_to_me();
		roResult.set_processed();
	}
}


void cned_static::on_event_mouse_over(const ned_action_mouse &,ned_action_result & roResult)
{
	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_text_paint();
		roResult.set_processed();
	}
}

void cned_static::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(!get_prop_disabled());

	if(roActionMouse.is_LEFT_click())
	{
		if(get_prop_hyperlink().PointsObject())
		{
			SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(get_ident()));
			poEventCmdSP->set_command(get_prop_hyperlink());
			roResult.add_info(poEventCmdSP);
				
			_invalidate_text_paint();
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

void cned_static::on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult)
{
#ifdef _DEBUG
	//gdy dostaje focus to musi mieæ do tego prawo
	if(get_ident() == roActionFocus.get_got_focus_ident())
	{
		ASSERT(get_prop_hyperlink().PointsObject() && !get_prop_disabled());
	}
#endif

	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_text_paint();
	}
}
