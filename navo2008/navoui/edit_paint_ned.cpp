/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych

	painting part
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
	bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
	bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
	bbmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmbb
	bbmmttttttttttttttttttttttttttttttttttttttttttttttttttttttmmbb
	bbmmttttttttttttttttttttttttttttttttttttttttttttttttttttttmmbb
	bbmmttttttttttttttttttttttttttttttttttttttttttttttttttttttmmbb
	bbmmttttttttttttttttttttttttttttttttttttttttttttttttttttttmmbb
	bbmmttttttttttttttttttttttttttttttttttttttttttttttttttttttmmbb
	bbmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmbb
	bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
	bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb


	b - border (here widht=2)
	m - margins
	t - text area

	dimensions:
	1. measure text area
	2. always add margins
	3. add border if exists

	-> edit with border is bigger then witout !!
	-> focus is displayed as wider border on margins area (edit size is constant)
*/

const long cned_edit__::INTERNAL_PAINT_RECT_ID = 1;
const long cned_edit__::CARET_PAINT_RECT_ID = 2;

void cned_edit__::_get_caret_rect(const ng_point & roCurrentPoint,ng_rect & roCaretRect,const cstate & roState)
{
	_get_text_rect(roCurrentPoint,roCaretRect);

	roCaretRect.set_left(roCaretRect.get_left() + roState.m_XLeftCaretLU);
	roCaretRect.set_width(get_manager()->__zoomize(1));
	roCaretRect.set_top(roCurrentPoint.get_y() + _get_frame_px_width() + _metrics().edit().get_top_margin());
	roCaretRect.set_bottom(roCurrentPoint.get_y() + m_oActualSize.get_dy() - 1 - _get_frame_px_width() - _metrics().edit().get_bottom_margin());
}


//--------- drawing ------------------
void cned_edit__::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ASSERT(!m_bInfraUpdPending);

	if(!roForePainter.is_printing())
	{
		_paint_border(roForePainter,oPaintPoint);
	
		if(get_prop_focus())
		{
			_paint_caret(roForePainter,oPaintPoint);
		}
	}

	if(m_State.m_oBufferString.GetLength() == 0)	//nie pusty
	{
		return;
	}

	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());

	ng_string oVisibleBufferString;
	get_visible_buffer(oVisibleBufferString);

	LPCTSTR lpTextPtr = oVisibleBufferString;
	
	ng_rect oTextRect;
	
	if(!roForePainter.is_printing())
	{
		_get_text_rect(oPaintPoint,oTextRect);
	}
	else
	{
		oTextRect = ng_rect(oPaintPoint,m_oActualSize);
	}

	//wymaluj tekst
	roForePainter.print_text(oTextRect,lpTextPtr + m_State.m_nCharScroll,
		oVisibleBufferString.GetLength() - m_State.m_nCharScroll,
		_get_text_color(roForePainter.is_effectively_disabled(this)),poFontSP);
	
	//odwróæ selekcje
	if(!roForePainter.is_printing() && !roForePainter.is_effectively_disabled(this))
	{
		if(m_State.m_nCharSelFirst < m_State.m_nCharSelLast)
		{
			oTextRect.set_right(min(oTextRect.get_left() + m_State.m_XSelLastLU,oTextRect.get_right()));
			oTextRect.set_left(oTextRect.get_left() + max(0,m_State.m_XSelFirstLU));
			if(!oTextRect.is_empty())
			{
				roForePainter.patblt(oTextRect,Black/*nie wa¿ne gdy DSTINVERT*/,DSTINVERT);
			}
		}
	}
}

void cned_edit__::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	const cstate oOldState = m_State;
	_update_infrastructure(roBackPainter.get_dc(),oOldState);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oBackRect;
	_get_back_rect(oPaintPoint,oBackRect);

	if(!roBackPainter.is_effectively_disabled(this))
	{
		_draw_std_background(roBackPainter,oBackRect);
	}
	
	_store_main_paint_rect(ng_rect(oPaintPoint,m_oActualSize));
	_store_extra_paint_rect(INTERNAL_PAINT_RECT_ID,oBackRect);
}


void cned_edit__::_paint_border(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
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
		//also invalid field
		if(get_prop_focus() || !get_prop_valid())
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

	ng_rect oFrameRect(roCurrentPoint,m_oActualSize);
	roForePainter.frame_rect(oFrameRect,nFramePxWidth,clrFrameColor,nFrameStyle);
}

void cned_edit__::_paint_caret(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_rect oCaretRect;
	_get_caret_rect(roCurrentPoint,oCaretRect,m_State);

	if(m_State.m_bCaretOn)
	{
		roForePainter.patblt(oCaretRect,Black/*nie wa¿ne gdy DSTINVERT*/,DSTINVERT);

	}
	_store_extra_paint_rect(CARET_PAINT_RECT_ID,oCaretRect);
}

//-------------- rendering support -------------------
void cned_edit__::render(cned_renderer_ & roRenderer)
{
	cned_rect_element_::render(roRenderer);
	
	const cstate oOldState = m_State;
	
	_set_infra_update_pending();

	_update_infrastructure(roRenderer.get_info_dc(),oOldState);
}

void cned_edit__::_update_infrastructure(ng_dc & roDC,const cstate & roOldState)
{
	if(!m_bInfraUpdPending)
	{
		return;
	}

	//wylicz rozmiary znaków
	int aSizes[ 8193 ];
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	
	ng_string oVisibleBufferString;
	get_visible_buffer(oVisibleBufferString);
	
	m_State.m_XTextWidthLU = roDC.measure_string(oVisibleBufferString,LONG_MAX,
		poFontSP,NULL,aSizes).get_dx();

	bool bTextChanged = (m_State.m_oBufferString != roOldState.m_oBufferString);

	//wylicz szerokoœæ prostok¹ta przeznaczonego na teksty (po odjêciu ramek i marginesów)
	//poniewa¿ chodzi nam tylko o szerokoœæ - mo¿emy u¿yæ dowolnego punktu referencyjnego
	ng_rect oTextRect;
	_get_text_rect(ng_point(),oTextRect);
	ng_xdist xTextRectWidth = oTextRect.get_width();

	if(_is_auto_scroll())
	{
		//sprawdŸ czy jest potrzebny scroll
		if(m_State.get_caret_pos() != roOldState.get_caret_pos() || bTextChanged)
		{
			//znormalizuj
			m_State.m_nCharScroll = min(m_State.m_nCharScroll,m_State.m_oBufferString.GetLength());
			
			//ewentualny scroll w lewo
			if(aSizes[m_State.get_caret_pos()] >= aSizes[ m_State.m_nCharScroll ] + xTextRectWidth)
			{
				while(
					(m_State.m_nCharScroll < m_State.m_oBufferString.GetLength()) 
					&&
					(aSizes[m_State.get_caret_pos()] >= aSizes[ m_State.m_nCharScroll ] + 7 * xTextRectWidth  / 8)
					)
				{
					m_State.m_nCharScroll++;
				}
				ASSERT(m_State.m_nCharScroll <= m_State.m_oBufferString.GetLength());
			}
			//ewentualny scroll w prawo
			if(aSizes[ m_State.get_caret_pos() ] <= aSizes[ m_State.m_nCharScroll ])
			{
				while(
					(m_State.m_nCharScroll > 0) 
					&&
					(aSizes[ m_State.get_caret_pos() ] <= aSizes[ m_State.m_nCharScroll ] + 1 * xTextRectWidth  / 8)
					)
				{
					m_State.m_nCharScroll--;
				}
				ASSERT(m_State.m_nCharScroll >= 0);
			}
		}
	}

	//ustaw offset caret'a (LU)
	//uwaga! nie zoomujemy wyniku, poniew¿ u¿yty font uwzglêdnia zoom!!
	m_State.m_XLeftCaretLU = aSizes[ m_State.get_caret_pos() ] - aSizes[ m_State.m_nCharScroll ];
	m_State.m_XSelFirstLU  = aSizes[ m_State.m_nCharSelFirst ] - aSizes[ m_State.m_nCharScroll ];
	m_State.m_XSelLastLU   = aSizes[ m_State.m_nCharSelLast  ] - aSizes[ m_State.m_nCharScroll ];
	m_State.m_XSelLastLU--;	//right side correction


	_invalidate_internal_paint();

	m_bInfraUpdPending = false;
}


void cned_edit__::_invalidate_internal_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),INTERNAL_PAINT_RECT_ID);
}

void cned_edit__::_invalidate_caret_paint()
{
	get_manager()->invalidate_paint_rect(get_ident(),CARET_PAINT_RECT_ID);
}

long cned_edit__::_find_char_from_local_point(const ng_point & roLocalPoint,ng_dc & roDC)
{
	//wylicz rozmiary znaków
	int aSizes[ 8193 ];
	SCP<ng_font> poFontSP = get_manager()->get_font_on_inx(get_prop_fontinx());
	ng_string oVisibleBufferString;
	get_visible_buffer(oVisibleBufferString);
	roDC.measure_string(oVisibleBufferString,LONG_MAX,poFontSP,NULL,aSizes);

	ng_rect oTextRect;
	_get_text_rect(ng_point(),oTextRect);
	ng_xcoord xTest = roLocalPoint.get_x() - oTextRect.get_left() + aSizes[ m_State.m_nCharScroll ];
	for(long iter = 0; iter <= oVisibleBufferString.GetLength(); iter++)
	{
		if(aSizes[ iter ] > xTest)
		{
			return iter;
		}
	}
	return oVisibleBufferString.GetLength();
}
