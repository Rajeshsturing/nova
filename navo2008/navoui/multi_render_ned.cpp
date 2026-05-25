/*
	NAVO Enterprise 2003
	2003-04-07

	navo enhanced display (NED)

	ned_multiedit		/ <multiline>
		kontrolka edycji tekstów wieloliniowych

		render part
*/

#include "stdafx.h"
#include "multiline_helper_ned.h"
#include "scroll_helper_ned.h"
#include "multi_ned.h"
#include "scrollbar_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long cned_multiedit::INTERNAL_PAINT_RECT_ID = 1;
const long cned_multiedit::CARET_PAINT_RECT_ID = 2;

//-------------- rendering support -------------------
ng_size cned_multiedit::_compute_min_size(const ned_measure_param &)
{
	ng_xdist xWidth = 0;
	ng_ydist yHeight = 0;
	if(is_normal_width_value(get_prop_extwidth()))
	{
		xWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
	}
	else
	{
		xWidth = _metrics().multiedit().get_default_width();
	}
	if(is_normal_height_value(get_prop_extheight()))
	{
		yHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
	}
	else
	{
		yHeight = _metrics().multiedit().get_default_height();
	}
	
	return ng_size(xWidth,yHeight);
}

void cned_multiedit::get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics)
{
	ASSERT(!get_prop_hidden());
	if(is_measure_pending())
	{
		m_oMetrics.reset();
		ng_size oMinSize = _compute_min_size(roMParam);
		
		if(is_normal_width_value(get_prop_extwidth()))
		{
			ng_xdist dxWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
			if(dxWidth > oMinSize.get_dx())
			{
				oMinSize.set_dx(dxWidth);
			}
		}

		m_oMetrics.update(oMinSize.get_dx(),oMinSize.get_dy(),oMinSize.get_dx());
		clear_measure_pending();
	}
	roMetrics.update(m_oMetrics);
}

void cned_multiedit::_get_dx_and_line_for_char_pos(long nCharPos,const multiline_measurer & roTextMeasurer,
	ng_xdist & rdxOffset,long & rnLine) const
{
	rnLine = _get_line_for_char_pos(nCharPos);
	ASSERT((rnLine >= 0 && rnLine < m_oMLM.get_line_count()) || 
		   (rnLine == 0 && m_oMLM.get_line_count() == 0));

	long nFirstChar = 0;
	long nLastChar = -1;
	if(rnLine < m_oMLM.get_line_count())
	{
		VERIFY(m_oMLM.get(rnLine,nFirstChar,nLastChar));
	}

	rdxOffset = _get_frame_px_width() + _metrics().edit().get_left_margin() +
		roTextMeasurer._get_part_len(nFirstChar,nCharPos - 1);
}

long cned_multiedit::_get_char_pos_for_line_and_dx(const ng_xdist dxOffset,long nLine,ng_dc & roDC)
{
	//dxOffset - relative to multiedit area - includes border and margin
	ng_xdist dxInternalOffset =  dxOffset - _get_frame_px_width() - _metrics().edit().get_left_margin();
	if(nLine < 0)
	{
		return 0;
	}
	if(nLine >= m_oMLM.get_line_count())
	{
		return m_State.get_buffer_size();
	}

	ASSERT(nLine >= 0 && nLine < m_oMLM.get_line_count());

	long nFirstChar = 0;
	long nLastChar = -1;
	VERIFY(m_oMLM.get(nLine,nFirstChar,nLastChar));

	//prepare font
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	long nMaxChars;
	roDC.measure_string(LPCTSTR(m_State.get_buffer()) + nFirstChar,nLastChar - nFirstChar + 1,
		dxInternalOffset,poFontSP,&nMaxChars,NULL);
	
	return min(m_State.get_buffer_size(),nFirstChar + nMaxChars);
}


ng_ydist cned_multiedit::_get_actual_text_height() const
{
	if(m_oMLM.get_line_count() > 0)
	{
		ng_size oLineSize;
		ng_size oVectorSize;
		m_oMLM.get(m_oMLM.get_line_count() - 1,oLineSize,oVectorSize);

		return (oVectorSize + oLineSize).get_dy();
	}
	return 0;
}

//-----------------------------------------------------------------------------------------

void cned_multiedit::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	ASSERT(!get_prop_hidden());

	roRenderer.ensure_width(m_oMetrics.get_minimal_width());
	ng_size oRequestedSize(_get_std_width_for_rendering(roRenderer),
		_get_std_height_for_rendering(m_oMetrics.get_minimal_height()));
	roRenderer.allocate_rect(get_ident(),-1,oRequestedSize,m_oActualSize,m_oVectorSize);

	const cstate oOldState = m_State;
	_update_infrastructure(roRenderer.get_info_dc(),oOldState,true);

	//----------------------------------
	//ned_to_do: dokoñczyæ .............
	//----------------------------------

#ifdef _DEVELOPER_EDITION_

	ng_ydist yTotalSize = _get_actual_text_height();
	if(yTotalSize > m_oActualSize.get_dy())
	{
		ng_rect oTextRect;
		_get_text_rect(ng_point(),oTextRect);

		ng_xdist dxScrollWidth = show_vertical_bar(roRenderer,
			oTextRect.get_topright(),oTextRect.get_height(),yTotalSize,m_oActualSize.get_dy());
		
		_get_vert_bar()->move_by(-1,ng_size(- dxScrollWidth + 
			_metrics().edit().get_right_margin() + 1,1));
	}
	else
	{
		hide_vertical_bar();
	}

#endif
}

void cned_multiedit::_update_infrastructure(ng_dc & roDC,const cstate & roOldState,bool bWhileRendering)
{
	if(!m_bInfraUpdPending)
	{
		return;
	}

	//ned_to_do:

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	//przygotuj measurer
	LPCTSTR lpBuffer2Measure = m_State.get_buffer_size() ? m_State.get_buffer() : "7";
	const long nBuffet2MeasureLen = m_State.get_buffer_size() ? m_State.get_buffer_size() : 1;
	multiline_measurer oTextMeasurer(roDC,poFontSP,lpBuffer2Measure,nBuffet2MeasureLen);
	m_State.m_dyLineHeight = oTextMeasurer.get_line_height();

	bool bLayoutChanged = _layout_lines(oTextMeasurer);
	bool bSelChanged = false;

	if(bLayoutChanged || m_State.get_caret_pos() != roOldState.get_caret_pos())
	{
		_get_dx_and_line_for_char_pos(m_State.get_caret_pos(),oTextMeasurer,m_State.m_dxCaretPos,m_State.m_nCaretLine);
		_invalidate_caret_paint();
	}
	if(bLayoutChanged || m_State.get_start_of_selection() != roOldState.get_start_of_selection())
	{
		_get_dx_and_line_for_char_pos(m_State.get_start_of_selection(),oTextMeasurer,m_State.m_dxSelFirstPos,m_State.m_nSelFirstLine);
		//ned_to_do: jeœli by³a zmiana po³o¿enia kursora to 
		//automatycznie nastêpuje zmiana po³o¿enia selekcji
		//zatem ten warunek odœwie¿ania nie ma sensu -> generuje nadmiarowe odœwie¿enia ca³oœci
		bSelChanged = true;
	}

	if(bLayoutChanged || m_State.get_end_of_selection()  != roOldState.get_end_of_selection())
	{
		_get_dx_and_line_for_char_pos(m_State.get_end_of_selection(),oTextMeasurer,m_State.m_dxSelLastPos,m_State.m_nSelLastLine);
		m_State.m_dxSelLastPos--;	//correction for right side range
		bSelChanged = true;
	}

	if(bLayoutChanged || bSelChanged)
	{
		_invalidate_internal_paint();
	}

#ifdef _DEVELOPER_EDITION_
	if(!bWhileRendering)
	{
		//potrzebny a nie ma lub jest a nie potrzebny
		if((_get_actual_text_height() > m_oActualSize.get_dy()) != _is_vert_bar())
		{
			_size_info_dirty();
		}
	}
#endif

	m_bInfraUpdPending = false;
}

bool cned_multiedit::_layout_lines(const multiline_measurer & roTextMeasurer)
{
	//jeœli wszystko OK - wychodzimy
	if(m_State.get_invalid_char() == MAXLONG)
	{
		return false;
	}

	ASSERT(m_State.get_invalid_char() <= m_State.get_buffer().GetLength());

	//szukamy linii zawieraj¹cej 'punkt zmiany'
	long nFirstChar = 0;
	long nLastChar = -1;

	if(m_oMLM.get_line_count() > 0)
	{
		m_oMLM.get(m_oMLM.get_line_count() - 1,nFirstChar,nLastChar);	//we¿ ostatni¹ liniê

		long nLineNr = 0;

		if(m_State.get_invalid_char() > nLastChar)		//zmiana poza u³o¿onym zakresem
		{
			nLineNr = m_oMLM.get_line_count() - 1;
		}
		else
		{
			while(m_oMLM.get(nLineNr,nFirstChar,nLastChar))
			{
				if(nLastChar >= m_State.get_invalid_char())
				{
					break;
				}
				nLineNr++;
			}
			
			ASSERT(nLastChar >= m_State.get_invalid_char());
		
			// musimy siê cofn¹æ do poprzedniej linii - np. podzia³ s³owa, 
			//które przed podzia³em nie zmieœci³o by siê w poprzedniej, a teraz siê zmieœci

			if(nLineNr > 0)	
			{
				nLineNr--;
				m_oMLM.get(nLineNr,nFirstChar,nLastChar);	//we¿ ostateczny pocz¹tek
			}

			ASSERT(nFirstChar <= m_State.get_invalid_char());	//teraz musi byæ 
		}
		ASSERT(nLineNr >= 0);
		//wyrzuæ zbêdne linie
		m_oMLM.reset_line_count(nLineNr);
	}

	ASSERT(nFirstChar >= 0 && nFirstChar <= m_State.get_buffer().GetLength());

	//przygotuj parser
	multiline_text_parser oTextParser(m_State.get_buffer(),nFirstChar);

	bool bHardBreak = true;
	rendering_line oRendLine;
	oRendLine.init_new(nFirstChar);

	const ng_xdist dxInternalWidth = m_oActualSize.get_dx() - 
		_metrics().edit().get_left_margin() - _metrics().edit().get_right_margin();	//ned_to_do: frames ?
	
	while(true)
	{
		switch(oTextParser.get_next_item(nFirstChar,nLastChar))
		{
		case '\0':
			_render_finish_line(oRendLine,roTextMeasurer,true,m_State.get_buffer());
			m_State.validate_up_to_char(MAXLONG);
			TRACE("------------------------------\n");
		return true;
		case MULTILINE_NEWLINE_CHAR:
			_render_finish_line(oRendLine,roTextMeasurer,true,m_State.get_buffer());
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
				if(roTextMeasurer._get_part_len(oRendLine.get_begin(),nLastChar) <= dxInternalWidth)
				{
					oRendLine.extend(nLastChar);
					oRendLine.add_breakchar();
				}
				else
				{
					_render_finish_line(oRendLine,roTextMeasurer,true,m_State.get_buffer());
					bHardBreak = false;
					oRendLine.init_new(nLastChar+1);
				}
			}
		break;
		default:
			if(roTextMeasurer._get_part_len(oRendLine.get_begin(),nLastChar) <= dxInternalWidth)
			{
				oRendLine.extend(nLastChar);
			}
			else
			{
				//ned_to_do: try extend by one-char - this is necessary for words wider then multiedit (dxInternalWidth)
				ASSERT(oRendLine.get_end() <= nFirstChar);	//wolno nam pomin¹æ odstêp
				_render_finish_line(oRendLine,roTextMeasurer,true,m_State.get_buffer());
				bHardBreak = false;
				oRendLine.init_new(nFirstChar);
				oRendLine.extend(nLastChar);
			}
		}
	}

}

void cned_multiedit::_render_finish_line(rendering_line & roRendLine,const multiline_measurer & roMeasurer,
		bool bWithNewline,const ng_string & roInternalString)
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

		ng_rect oInternalRect;
		_get_text_rect(ng_point(),oInternalRect);
		ng_size oVectorSize(oInternalRect.get_left(),oInternalRect.get_top() + 
			m_oMLM.get_line_count() * roMeasurer.get_line_height());

		m_oMLM.add(roRendLine.get_begin(),roRendLine.get_end(),oLineSize,oVectorSize,0,0);

#ifdef _DEBUG
		{
			CString oLineFragmentString = roInternalString.Mid(roRendLine.get_begin(),
				roRendLine.get_end() - roRendLine.get_begin() + 1);

			TRACE("v=(%d,%d)[%s][%d:%d]\n",oVectorSize.get_dx(),oVectorSize.get_dy(),
				oLineFragmentString,roRendLine.get_begin(),roRendLine.get_end());
			
		}
#endif

	}
	
	roRendLine.done();
}


void cned_multiedit::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	{	
		ng_rect oChildRect;
		_get_text_rect(oPaintPoint,oChildRect);
		cned_scroll_clipper oScrollClipper(roForePainter,oChildRect);
		
		ng_point oChildrenPoint(oPaintPoint);
		if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
		{
			oChildrenPoint.offset(-get_scroll_pos());
		}
		
		_draw_internals(roForePainter,oChildrenPoint);
	}

	
	if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		_scroll_draw_foreground(roForePainter,roCurrentPoint);
	}

	_draw_frame(roForePainter,oPaintPoint);
}

void cned_multiedit::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	const cstate oOldState = m_State;
	_update_infrastructure(roBackPainter.get_dc(),oOldState,false);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oBackRect;
	_get_back_rect(oPaintPoint,oBackRect);

	if(!roBackPainter.is_effectively_disabled(this))
	{
		_draw_std_background(roBackPainter,oBackRect);
	}

	if(roBackPainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		_scroll_draw_background(roBackPainter,roCurrentPoint);
	}
	_store_main_paint_rect(ng_rect(oPaintPoint,m_oActualSize));
	
	//reuse back-rect for text-rect
	_get_text_rect(oPaintPoint,oBackRect);
	_store_extra_paint_rect(INTERNAL_PAINT_RECT_ID,oBackRect);
}

//--------- drawing helpers ------------------
void cned_multiedit::_draw_caret(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_rect oCaretRect;
	_get_caret_rect(roCurrentPoint,oCaretRect);
	if(m_State.m_bCaretOn)
	{
		roForePainter.patblt(oCaretRect,Black/*nie wa¿ne gdy DSTINVERT*/,DSTINVERT);

	}
	_store_extra_paint_rect(CARET_PAINT_RECT_ID,oCaretRect);
}

void cned_multiedit::_draw_frame(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	long nFrameStyle;
	ng_color clrFrameColor;
	long nFramePxWidth = _get_frame_px_width();
	
	if(_metrics().is_windows_look())
	{
		nFrameStyle = NG_FRAME_ALL|NG_FRAME_EDGE_SUNKEN;
		clrFrameColor = get_container()->get_prop_backcolor();
	}
	else
	{
		//focused element has wider border
		if(get_prop_focus())
		{
			nFramePxWidth++;
		}
		if(!get_prop_valid())
		{
			nFrameStyle = NG_FRAME_ALL | NG_FRAME_EDGE_FLAT;
		}
		else
		{
			nFrameStyle = border_style_to_frame_mask(get_prop_border_type(),NG_FRAME_ALL);
		}
		clrFrameColor = get_prop_valid() ? get_prop_border_color() : 
			_metrics().edit().get_invalid_data_color();
	}

	roForePainter.get_dc().frame_rect(ng_rect(roCurrentPoint,m_oActualSize),nFramePxWidth,clrFrameColor,nFrameStyle);
}

void cned_multiedit::_draw_internals(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	//draw caret
	if(get_prop_focus())
	{
		_draw_caret(roForePainter,roCurrentPoint);
	}

	//prepare font
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());

	//prepare fore color
	ng_color oForeColor = _get_text_color(roForePainter.is_effectively_disabled(this));

	//prepare iterator 
	long nLineNr = 0;
	long nFirstChar;
	long nLastChar;
	ng_size oLineSize;
	ng_size oLineVector;
	ng_xdist dxExtraWidth;
	long nBreakChars;
	
	while(m_oMLM.get(nLineNr,nFirstChar,nLastChar,oLineSize,oLineVector,dxExtraWidth,nBreakChars))
	{
		ng_point oLinePoint(roCurrentPoint);
		oLinePoint.offset(oLineVector);
		
		roForePainter.print_text(ng_rect(oLinePoint,oLineSize),
			LPCTSTR(m_State.get_buffer()) + nFirstChar,nLastChar - nFirstChar + 1,
			oForeColor,poFontSP);

		if(!roForePainter.is_printing() && !roForePainter.is_effectively_disabled(this))
		{
			//draw selection if in range
			if(nLineNr >= m_State.m_nSelFirstLine && nLineNr <= m_State.m_nSelLastLine)
			{
				ng_rect oSelRect(oLinePoint,oLineSize);
				if(nLineNr == m_State.m_nSelFirstLine)
				{
					oSelRect.set_left(roCurrentPoint.get_x() + m_State.m_dxSelFirstPos);
				}
				if(nLineNr == m_State.m_nSelLastLine)
				{
					oSelRect.set_right(roCurrentPoint.get_x() + m_State.m_dxSelLastPos);
				}
				if(!oSelRect.is_empty())
				{
					roForePainter.patblt(oSelRect,Black/*nie wa¿ne gdy DSTINVERT*/,DSTINVERT);
				}
			}
		}

		nLineNr++;
	}
}

void cned_multiedit::_invalidate_internal_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),INTERNAL_PAINT_RECT_ID);
}

void cned_multiedit::_invalidate_caret_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),CARET_PAINT_RECT_ID);
}

void cned_multiedit::fill_clone(cned_element * poDestination)
{
	cned_rect_container_::fill_clone(poDestination);
	cned_multiedit * poMEDest = cast_ui<cned_multiedit>(poDestination);

	poMEDest->m_bDataValid = m_bDataValid;
	poMEDest->m_bUseEnter = m_bUseEnter;
	m_State.copy_to(poMEDest->m_State);
	poMEDest->_set_infra_update_pending();
}


