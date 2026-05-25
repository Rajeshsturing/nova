/*
	NAVO Enterprise 2003
	2003-04-07

	navo enhanced display (NED)

	ned_staticex		/ <text>
		kontrolka tekstu wieloliniowego
*/

#include "stdafx.h"
#include "multiline_helper_ned.h"
#include "staticex_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_staticex::cned_staticex(cned_element_manager * poManager,const ned_ident idThis) :
	cned_element(poManager,ned_staticex,idThis),
	m_nDeclCharWidth(0)
{
}

//--------------------------------------------------------
void cned_staticex::set_fixed_properties()
{
	cned_element::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_border_type(NED_BORDER_STYLE_NONE);
}


//-------------- rendering support -------------------
inline void cned_staticex::_prepare_internal_text(ng_string & roInternalTextString) const
{
	text2internaltext(m_oTextString,roInternalTextString);
}

void get_multiline_min_size(ng_dc & roDC,SCP<ng_font> & rpoFontSP,
	LPCTSTR lpText,long nCount,cned_metrics & roMetrics);

void cned_staticex::get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics)
{
	ASSERT(!get_prop_hidden());

	if(is_measure_pending())
	{
		m_oMetrics.reset();
		ng_string oInternalString;
		_prepare_internal_text(oInternalString);
		SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
		get_multiline_min_size(roMParam.get_info_dc(),poFontSP,oInternalString,oInternalString.GetLength(),m_oMetrics);
		
		//increase size up to declared character count
		if(get_prop_charwidth() != 0)
		{
			ng_string oTestString('7',get_prop_charwidth());
			ng_size oCompleteSize = roMParam.get_info_dc().measure_string(oTestString,MAXLONG,poFontSP,NULL);
			m_oMetrics.update(oCompleteSize.get_dx(),oCompleteSize.get_dy(),0);
		}

		clear_measure_pending();
	}
	roMetrics.update(m_oMetrics);
}


void cned_staticex::render(cned_multi_line_renderer & roMLRenderer)
{
	long nFirstChar;
	long nLastChar;
	bool bHardBreak = true;
	
	//ned_to_do: renderowaæ tylko gdy zmieni³ siê text lub szerokoœæ lub po³o¿enie
	//czêœciowo to mo¿e zapewniæ flaga 'infra-update-pending'
	//a czesciowo pamietanie polozenia i ostatniej szerokosci renderowania

	ng_string oInternalString;
	_prepare_internal_text(oInternalString);

	multiline_text_parser oTextParser(oInternalString,0);

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	multiline_measurer oTextMeasurer(roMLRenderer.get_info_dc(),poFontSP,oInternalString,oInternalString.GetLength());

	rendering_line oRendLine;
	oRendLine.init_new(0);
	m_oMLM.reset_line_count(0);

	while(true)
	{
		switch(oTextParser.get_next_item(nFirstChar,nLastChar))
		{
		case '\0':
			_render_finish_line(roMLRenderer,oRendLine,oTextMeasurer,false,oInternalString);
		return;
		case MULTILINE_NEWLINE_CHAR:
			_render_finish_line(roMLRenderer,oRendLine,oTextMeasurer,true,oInternalString);
			bHardBreak = true;
			oRendLine.init_new(nLastChar+1);
		break;
		case ' ':
			if(!bHardBreak && oRendLine.is_empty())
			{
				oRendLine.init_new(nLastChar+1); //pomiñ pocz¹tkowe spacje dla soft-break
			}
			else
			{
				if(oTextMeasurer._get_part_len(oRendLine.get_begin(),nLastChar) <= roMLRenderer.get_current_width())
				{
					oRendLine.extend(nLastChar);
					oRendLine.add_breakchar();
				}
				else
				{
					_render_finish_line(roMLRenderer,oRendLine,oTextMeasurer,true,oInternalString);
					bHardBreak = false;
					oRendLine.init_new(nLastChar+1);
				}
			}
		break;
		default:
			if(oTextMeasurer._get_part_len(oRendLine.get_begin(),nLastChar) <= roMLRenderer.get_current_width())
			{
				oRendLine.extend(nLastChar);
			}
			else
			{
				ASSERT(oRendLine.get_end() <= nFirstChar);	//wolno nam pomin¹æ odstêp
				_render_finish_line(roMLRenderer,oRendLine,oTextMeasurer,true,oInternalString);
				bHardBreak = false;
				oRendLine.init_new(nFirstChar);
				oRendLine.extend(nLastChar);
			}
		}
	}
}

void cned_staticex::_render_finish_line(cned_multi_line_renderer & roMLRenderer,
	rendering_line & roRendLine,multiline_measurer & roMeasurer,bool bWithNewline,
	const ng_string & roInternalString)
{
	//obetnij koñcowe spacje
	while(!roRendLine.is_empty() && roInternalString.GetAt( roRendLine.get_end() ) == ' ')
	{
		roRendLine.shrink();
		roRendLine.del_breakchar();
	}

	if(!roRendLine.is_empty() || bWithNewline)
	{
		ng_size oLineSize;
		oLineSize.set_dy(roMeasurer.get_line_height());
		oLineSize.set_dx(roMeasurer._get_part_len(roRendLine.get_begin(),roRendLine.get_end()));

		ng_size oVectorSize;
		ng_xdist dxExtraWidth = 0;
		
		if(eal_justify == get_prop_alignment() && bWithNewline)
		{
			dxExtraWidth = roMLRenderer.get_current_width() - oLineSize.get_dx();
			oLineSize.set_dx(roMLRenderer.get_current_width());
		}

		roMLRenderer.allocate_rect(get_ident(),m_oMLM.get_line_count(),oLineSize,oLineSize,oVectorSize);
		ASSERT(dxExtraWidth >= 0);

		m_oMLM.add(roRendLine.get_begin(),roRendLine.get_end(),oLineSize,
			oVectorSize,dxExtraWidth,roRendLine.get_breakchar_count());

#ifdef _DEBUG0
		{
			CString oLineFragmentString = roInternalString.Mid(roRendLine.get_begin(),
				roRendLine.get_end() - roRendLine.get_begin() + 1);

			TRACE("v=(%d,%d)[%s]\n",oVectorSize.get_dx(),oVectorSize.get_dy(),oLineFragmentString);
			
		}
#endif

	}

	if(bWithNewline)
	{
		roMLRenderer.newline();
	}
	
	roRendLine.done();
}


void cned_staticex::post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	long iter = 0;
	ng_size oLineSize;
	ng_size oLineVector;
	
	while(m_oMLM.get(iter,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);
		ng_rect oNewLineRect(oLinePoint,oLineSize);
		ng_rect oOldLineRect;
	
		get_manager()->get_paint_rect(get_ident(),iter,oOldLineRect);

		if(oOldLineRect != oNewLineRect)
		{
			get_manager()->invalidate_paint_rect(get_ident(),iter);
			get_manager()->invalidate_paint_rect(oNewLineRect);
		}
	
		iter++;
	}
	
}

//--------- drawing ------------------
ned_fontinx get_underlined_font(cned_element_manager * poManager,const ned_fontinx inxNormalFont);

void cned_staticex::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	//get context information
	bool bMouseOver = (get_manager()->get_mouse_over_element() == get_ident());
	bool bActive = (m_poHyperLinkInfoSP.PointsObject() && !roForePainter.is_effectively_disabled(this));
	bool bFocused = get_prop_focus();

	//prepare font
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(((bMouseOver || bFocused) && bActive) ? 
			get_underlined_font(get_manager(),get_prop_fontinx()) : get_prop_fontinx());

	//prepare fore color
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

	ng_string oInternalString;
	_prepare_internal_text(oInternalString);
	//prepare iterator 

	long iter = 0;
	long nFirstChar;
	long nLastChar;
	ng_size oLineSize;
	ng_size oLineVector;
	ng_xdist dxExtraWidth;
	long nBreakChars;
	
	while(m_oMLM.get(iter,nFirstChar,nLastChar,oLineSize,oLineVector,dxExtraWidth,nBreakChars))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);

		if(eal_justify == get_prop_alignment())
		{
			//OS_API_CALL

			//Win98 bug workaround
			if(dxExtraWidth != 0 && nBreakChars == 0)
			{
				nBreakChars = 1;
			}
			::SetTextJustification(roForePainter.get_dc().get_hdc(),dxExtraWidth,nBreakChars);
		}
		
		ng_rect oLineRect(oLinePoint,oLineSize);
		roForePainter.print_text(oLineRect,
			LPCTSTR(oInternalString) + nFirstChar,nLastChar - nFirstChar + 1,
			oForeColor,poFontSP);
		
		_store_extra_paint_rect(iter,oLineRect);
		
		iter++;
	}

	if(eal_justify == get_prop_alignment())
	{
		//OS_API_CALL
		::SetTextJustification(roForePainter.get_dc().get_hdc(),0,0);
	}
}

void cned_staticex::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	//early detect void call
	if(!roBackPainter.get_paint_param().paint_background())
	{
		return;
	}
	if(get_prop_backcolor() == Transparent || get_prop_backcolor2() == Transparent)
	{
		return;
	}


	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	//prepare iterator 
	long iter = 0;
	ng_size oLineSize;
	ng_size oLineVector;
	
	while(m_oMLM.get(iter,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);
		
		roBackPainter.fill_rect_hg(ng_rect(oLinePoint,oLineSize),
			get_prop_backcolor(),get_prop_backcolor2());
		
		iter++;
	}
}

ened_spr cned_staticex::should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const
{
	if(m_oMLM.get_line_count() == 0)
	{
		return spr_other;
	}

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	//prepare iterator 
	ng_size oLineSize;
	ng_size oLineVector;

	//czy pierwsza nie jest poni¿ej
	if(m_oMLM.get(0,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);
		if(oPaintPoint.get_y() > roPainter.paint_bottom())
		{
			return spr_below;
		}
	}

	//czy ostatnia nie jest powy¿ej
	if(m_oMLM.get(m_oMLM.get_line_count()-1,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);

		if(ng_rect(oLinePoint,oLineSize).get_bottom() < roPainter.paint_top())
		{
			return spr_above;
		}
	}

	long iter = 0;

	while(m_oMLM.get(iter,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oPaintPoint);
		oLinePoint.offset(oLineVector);
		
		if(roPainter.in_clip_region(ng_rect(oLinePoint,oLineSize)))
		{
			return spr_inside;
		}

		iter++;
	}

	return spr_other;
}

bool cned_staticex::is_inside_hit_area(const ng_point & roPoint) const
{
	ng_point oTestPoint;
	oTestPoint.offset(m_oVectorSize);
	
	long iter = 0;
	ng_size oLineSize;
	ng_size oLineVector;
	
	while(m_oMLM.get(iter,oLineSize,oLineVector))
	{
		ng_point oLinePoint(oTestPoint);
		oLinePoint.offset(oLineVector);
	
		if(ng_rect(oLinePoint,oLineSize).is_inside(roPoint))
		{
			return true;
		}
				
		iter++;
	}
	
	return false;
}

bool cned_staticex::quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance)
{
	ng_rect oInternalRefRect(roRefRect);
	oInternalRefRect.offset(-m_oVectorSize);
	long iter = 0;
	ng_size oLineSize;
	ng_size oLineVector;
	bool bFound = false;
	while(m_oMLM.get(iter,oLineSize,oLineVector))
	{
		bool bFoundInLine = _quote_rect_distance(eRP,oInternalRefRect,
			ng_rect(ng_point().offset(oLineVector),oLineSize),rnDistance);
		
		bFound = bFound || bFoundInLine;
		iter++;
	}
	
	return bFound;
}

void cned_staticex::get_bounding_rect(long nElementPart,ng_rect & roLocalRect) const
{
	ng_point oInternalPoint;
	oInternalPoint.offset(m_oVectorSize);

	ng_rect oRect;
	ng_size oLineSize;
	ng_size oLineVector;

	if(nElementPart == -1)
	{
		long iter = 0;
		
		while(m_oMLM.get(iter,oLineSize,oLineVector))
		{
			ng_rect oLineRect(oInternalPoint,oLineSize);
			oLineRect.offset(oLineVector);
			
			oRect.union_with(oLineRect);
			iter++;
		}
		roLocalRect = oRect;
	}
	else
	{
		if(m_oMLM.get(nElementPart,oLineSize,oLineVector))
		{
			roLocalRect = ng_rect(oInternalPoint,oLineSize).offset(oLineVector);
		}
		else
		{
			roLocalRect = ng_rect();
		}
	}
}

void cned_staticex::_invalidate_all_paint()
{
	long iter = 0;
	while(get_manager()->invalidate_paint_rect(get_ident(),iter))
	{
		iter++;
	}
}

//-------- page breaking ---------------------------------
void cned_staticex::do_breaks(cpb_manager__ & roPBManager,const ng_point & roCurrentPoint)
{
	ng_rect oElementRect;
	get_bounding_rect(-1,oElementRect);
	oElementRect.offset(roCurrentPoint.distance(ng_point()));

	ng_rect oAreasRect;
	roPBManager.get_areas_for_rect(oElementRect,oAreasRect);
	bool bDummyJustCreated;	
	//not splitted - simple case
	if(oAreasRect.get_bottom() == oAreasRect.get_top() && oAreasRect.get_left() == oAreasRect.get_right())
	{
		SCP<cned_element> poClonedStaticElementSP = roPBManager.get_clone(oAreasRect.get_left(),oAreasRect.get_top(),this,bDummyJustCreated);
		cned_staticex * poClonedStatic = cast_ui<cned_staticex>(poClonedStaticElementSP);
		poClonedStatic->m_oTextString = m_oTextString;
	}
	else
	{
		ng_point oPaintPoint(roCurrentPoint);
		oPaintPoint.offset(m_oVectorSize);
	
		ng_string oInternalString;
		_prepare_internal_text(oInternalString);


		//prepare iterator 
		long iter = 0;
		long nFirstChar;
		long nLastChar;
		long nLastClonedChar = -1;
		ng_size oLineSize;
		ng_size oLineVector;
		ng_xdist dxExtraWidth;
		long nBreakChars;
		
		while(m_oMLM.get(iter,nFirstChar,nLastChar,oLineSize,oLineVector,dxExtraWidth,nBreakChars))
		{
			ng_point oLinePoint(oPaintPoint);
			oLinePoint.offset(oLineVector);
			ng_rect oLineRect(oLinePoint,oLineSize);
			
			ng_rect oAreasRect;
			roPBManager.get_areas_for_rect(oLineRect,oAreasRect);
			SCP<cned_element> poClonedStaticElementSP = roPBManager.get_clone(oAreasRect.get_right(),oAreasRect.get_bottom(),this,bDummyJustCreated);
			cned_staticex * poClonedStatic = cast_ui<cned_staticex>(poClonedStaticElementSP);

			nFirstChar = 1 + nLastClonedChar;

			ASSERT(nFirstChar >= 0);
			ASSERT(nFirstChar <= nLastChar);
			ng_string oPartString(LPCTSTR(oInternalString) + nFirstChar,nLastChar - nFirstChar + 1);
			poClonedStatic->m_oTextString += oPartString;
			
			iter++;
			nLastClonedChar = nLastChar;
			ASSERT(nLastClonedChar >= 0);
		}
	}
}

//--------------event handlers ---------------------------------------
void cned_staticex::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
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

void cned_staticex::on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(get_prop_hyperlink().PointsObject() && !get_prop_disabled())
	{
		_invalidate_all_paint();
		roResult.set_processed();
	}
}

void cned_staticex::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	ASSERT(!get_prop_disabled());

	if(get_prop_hyperlink().PointsObject() && roActionMouse.is_LEFT_click())
	{
		_set_focus_to_me();
		roResult.set_processed();
	}
}

void cned_staticex::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
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

void cned_staticex::on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult)
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
		_invalidate_all_paint();
	}
}

void cned_staticex::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	//to-do: 
	//problemem jest to ¿e static-ex mo¿e rozciagac sie na wiele stron w dó³
	//potrzeba jest rozbudowy cpb_split_info o mechanizm 'wracania'
}

void cned_staticex::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager)
{
	ng_rect oElementRect;
	get_bounding_rect(-1,oElementRect);
	oElementRect.offset(roCurrentPoint.distance(ng_point()));

	long xAreaLeft = roSplitManager.find_x_area(oElementRect.get_left());
	long xAreaRight = roSplitManager.find_x_area(oElementRect.get_right());
	long yAreaTop = roSplitManager.find_y_area(oElementRect.get_top());
	long yAreaBottom = roSplitManager.find_y_area(oElementRect.get_bottom());

	//not splitted - simple case
	if(xAreaLeft == xAreaRight && yAreaTop == yAreaBottom)
	{
		SCP<cned_element> poClonedStaticElementSP = _make_clone_split(roSplitManager,xAreaLeft,yAreaTop);
		cned_staticex * poClonedStatic = cast_ui<cned_staticex>(poClonedStaticElementSP);
		poClonedStatic->m_oTextString = m_oTextString;
	}
	else
	{
		ng_point oPaintPoint(roCurrentPoint);
		oPaintPoint.offset(m_oVectorSize);
	
		ng_string oInternalString;
		_prepare_internal_text(oInternalString);

		//prepare iterator 
		long iter = 0;
		long nFirstChar;
		long nLastChar;
		long nLastClonedChar = -1;
		ng_size oLineSize;
		ng_size oLineVector;
		ng_xdist dxExtraWidth;
		long nBreakChars;
		
		while(m_oMLM.get(iter,nFirstChar,nLastChar,oLineSize,oLineVector,dxExtraWidth,nBreakChars))
		{
			ng_point oLinePoint(oPaintPoint);
			oLinePoint.offset(oLineVector);
			ng_rect oLineRect(oLinePoint,oLineSize);
			
			long xLineAreaRight = roSplitManager.find_x_area(oLinePoint.get_x());
			long yLineAreaBottom = roSplitManager.find_y_area(oLinePoint.get_y());

			SCP<cned_element> poClonedStaticElementSP = _make_clone_split(roSplitManager,xLineAreaRight,yLineAreaBottom);
			cned_staticex * poClonedStatic = cast_ui<cned_staticex>(poClonedStaticElementSP);

			nFirstChar = 1 + nLastClonedChar;

			ASSERT(nFirstChar >= 0);
			ASSERT(nFirstChar <= nLastChar);
			ng_string oPartString(LPCTSTR(oInternalString) + nFirstChar,nLastChar - nFirstChar + 1);
			poClonedStatic->m_oTextString += oPartString;
			
			iter++;
			nLastClonedChar = nLastChar;
			ASSERT(nLastClonedChar >= 0);
		}
	}
}

void cned_staticex::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_element::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_staticex * poDestSE = cast_ui<cned_staticex>(poDestination);

	//do not copy m_oTextString  - make-split is responsible for it
	poDestSE->m_nDeclCharWidth = m_nDeclCharWidth;

	//do not copy hyperlink
}

