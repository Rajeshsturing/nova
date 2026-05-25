/*
	NAVO Enterprise 2003
	2003-03-26

	navo enhanced display (NED)

	ned_option_button_		
		klasa bazowa dla radio i checkbox'a
*/

#include "stdafx.h"
#include "multiline_helper_ned.h"
#include "staticex_ned.h"
#include "optionbutton_ned.h"
#include "scroll_helper_ned.h"
#include "checkbox_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------ specjalizowany filtr dla option button'a ----------------------------
// (uwzglêdnia stan selekcji dla trybu 'print' -------------------------------------

class cned_option_filter_children : public cned_filter_children__<cned_element>
{
public:
	cned_option_filter_children(cned_option_button_ * poOptionButton,bool bPrinting);
	virtual void restart_at(ned_ident idElement);
	void move_next();
	long get_col_nr() const;
	long get_element_nr() const;
private:
	virtual void _find_next_valid();
	cned_option_button_ * m_poOptionButton;
	long m_nCurrCol;
	long m_nElementNr;		//kolejny numer elementu (bez filtrowania)
};

cned_option_filter_children::cned_option_filter_children(cned_option_button_ * poOptionButton,bool bPrinting) :
	cned_filter_children__<cned_element>(poOptionButton,true,bPrinting),
	m_poOptionButton(poOptionButton),
	m_nCurrCol(0),	
	m_nElementNr(0)
{
	//called once again to use derived version of _find_next_valid
	restart_at(poOptionButton->get_first_child_ident());
}

void cned_option_filter_children::_find_next_valid()
{
	while(m_idCurrent != NEDID_NOTHING)
	{
		if(cned_filter_children__<cned_element>::_qualify(m_idCurrent))
		{
			//bPrinting == m_bSkipNonPrintable
			//m_bSkipNonPrintable ma tutaj dodatkowe znaczenie - pomiñ niezaznaczone

			if(!m_bSkipNonPrintable)
			{
				return;
			}
			else
			{
				if(m_poOptionButton->get_prop_checked(get_element_nr()))
				{
					return;
				}
			}
		}
		m_nElementNr++;
		m_idCurrent = m_poManager->get_next_element(m_idCurrent);
	}
}

inline void cned_option_filter_children::restart_at(ned_ident idElement)
{
	cned_filter_children__<cned_element>::restart_at(idElement);
	m_nCurrCol = 0;
}

inline void cned_option_filter_children::move_next()
{
	m_nElementNr++;
	cned_filter_children__<cned_element>::move_next();
	m_nCurrCol = ++m_nCurrCol % m_poOptionButton->get_prop_colspan();
}

inline long cned_option_filter_children::get_col_nr() const
{
	return m_nCurrCol;
}

inline long cned_option_filter_children::get_element_nr() const
{
	return m_nElementNr;
}

//----------------------------------------------------------------------------------
/*
	<-left margin-><-image-><-image2item space-><-item-><-between col space-><-image-><-image2item space-><-item-><-right margin->
*/

void cned_option_button_::get_children_metrics(const ned_measure_param & roMParam)
{
	ASSERT(!get_prop_hidden());

	const ng_xdist dxImageWidth	 = _metrics().optionbtn().get_image_width();
	const ng_xdist dxI2IDistance = _metrics().optionbtn().get_img2item_distance();
	const ng_xdist dxColDistance = _metrics().optionbtn().get_col_distance();

	long nCol = 0;
	
	//reset old values
	long nWeight = 0;
	for(nCol = 0; nCol < get_prop_colspan(); nCol++)
	{
		m_oColArray[nCol].reset();
	}

	
	cned_option_filter_children oFilterChildren(this,roMParam.is_printing());

	while(!oFilterChildren.is_end())
	{
		cned_metrics oMetrics;
		oFilterChildren.get_element()->get_metrics(roMParam,oMetrics);

		m_oColArray[ oFilterChildren.get_col_nr() ].update_min_width(oMetrics.get_minimal_width());
		m_oColArray[ oFilterChildren.get_col_nr() ].update_min_height(oMetrics.get_minimal_height());

		nWeight += oMetrics.get_weight();
			
		oFilterChildren.move_next();
	}
	
	//wylicz podsumowanie
	ng_xdist xMinWidth = 0;
	ng_ydist yMinHeight = 0;
	for(nCol = 0; nCol < get_prop_colspan(); nCol++)
	{
		xMinWidth += m_oColArray[nCol].get_min_width() +
			(roMParam.is_printing() ? 0 : (dxI2IDistance + dxImageWidth));
		
		if(nCol != 0 && !roMParam.is_printing())
		{
			xMinWidth += dxColDistance;
		}
		
		yMinHeight = max(yMinHeight,m_oColArray[nCol].get_min_height());
	}
	
	xMinWidth += _metrics().optionbtn().get_left_margin(get_prop_border_type()) + _metrics().optionbtn().get_right_margin(get_prop_border_type());

	m_oMetrics.update(xMinWidth,yMinHeight,nWeight);
}

void cned_option_button_::_compute_final_col_widths(ng_xdist dxAvailInternalWidth,bool bPrinting)
{
	const ng_xdist dxImageWidth	 = bPrinting ? 0 : _metrics().optionbtn().get_image_width();
	const ng_xdist dxI2IDistance = bPrinting ? 0 : _metrics().optionbtn().get_img2item_distance();
	const ng_xdist dxColDistance = bPrinting ? 0 : _metrics().optionbtn().get_col_distance();

	ng_xdist dxMinSumWidth = 0;
	for(long nCol = 0; nCol < get_prop_colspan(); nCol++)
	{
		dxMinSumWidth += m_oColArray[nCol].get_min_width() + dxI2IDistance + dxImageWidth;
		
		if(nCol != 0)
		{
			dxMinSumWidth += dxColDistance;
		}
	}
	ASSERT(dxMinSumWidth <= dxAvailInternalWidth);
	
	ng_xdist dxFreeSpace = dxAvailInternalWidth - dxMinSumWidth;
	ASSERT(get_prop_colspan() > 0);
	ng_xdist dxFreeSpace4Col = dxFreeSpace / get_prop_colspan();
	ASSERT(dxFreeSpace4Col >= 0);

	//dodajemy po równo
	for(int nCol = 0; nCol < get_prop_colspan() - 1; nCol++)
	{
		m_oColArray[nCol].set_col_width(m_oColArray[nCol].get_min_width() + dxFreeSpace4Col);
		dxFreeSpace -= dxFreeSpace4Col;
	}
	
	//ostatnia dostaje tak¿e 'resztke'	
	ASSERT(dxFreeSpace >= 0);
	m_oColArray[get_prop_colspan()-1].set_col_width(m_oColArray[get_prop_colspan()-1].get_min_width() + dxFreeSpace);

}

void cned_option_button_::render(cned_renderer_ & roRenderer)
{
	const ng_xdist dxImageWidth	 = _metrics().optionbtn().get_image_width();
	const ng_xdist dxI2IDistance = _metrics().optionbtn().get_img2item_distance();
	const ng_xdist dxColDistance = _metrics().optionbtn().get_col_distance();
	const ng_ydist dyRowDistance = _metrics().optionbtn().get_row_distance();

	//zapewnij miejsce
	roRenderer.ensure_width(m_oMetrics.get_minimal_width());
	
	//ustal szerokoœæ (wewnêtrzn¹, przeznaczon¹ na dzieci)
	const ng_xdist dxActualWidth = _get_std_width_for_rendering(roRenderer);
	
	const ng_xdist dxInternalWidth = dxActualWidth - 
		_metrics().optionbtn().get_left_margin(get_prop_border_type()) - _metrics().optionbtn().get_right_margin(get_prop_border_type());
	
	//ned_to_do: to nie zawsze dzia³a (przynajmniej gdy jest w komórce grida
	//wtedy resetuje siê do samych obrazków przy ponownym renderowaniu
	if(true || dxActualWidth != m_oActualSize.get_dx() || _get_last_measured() != NEDID_LAST)
	{
		_compute_final_col_widths(dxInternalWidth,roRenderer.is_printing());

		m_oRowHeightArray.RemoveAll();
		
		cned_option_filter_children oFilterChildren(this,roRenderer.is_printing());

		const ng_xcoord xStartingX = roRenderer.is_printing() ? 0 : _metrics().optionbtn().get_left_margin(get_prop_border_type());
		const ng_ycoord yStartingY = roRenderer.is_printing() ? 0 : _metrics().optionbtn().get_top_margin(get_prop_border_type());
		ng_xcoord xCurrentX = xStartingX;
		ng_ycoord yCurrentY = yStartingY;
		ng_ycoord yRowHeight = 0;

		while(!oFilterChildren.is_end())
		{
			cned_multi_line_renderer oMultiLineRenderer(this,roRenderer,get_manager(),
				get_prop_alignment(),elal_top,
				ng_point(xCurrentX,yCurrentY),dxImageWidth + dxI2IDistance + m_oColArray[ oFilterChildren.get_col_nr() ].get_col_width());
			
			if(!roRenderer.is_printing())
			{
				ng_size oImgSpaceSize(dxImageWidth + dxI2IDistance,_metrics().optionbtn().get_image_height());
				ng_size oDummyVectorSize;
				oMultiLineRenderer.allocate_rect(NEDID_PLACEHOLDER,-1,oImgSpaceSize,oImgSpaceSize,oDummyVectorSize);
				
				ASSERT(oDummyVectorSize.get_dx() == xCurrentX && oDummyVectorSize.get_dy() == yCurrentY);
			}
			
			if(get_manager()->get_element_type(oFilterChildren.get_ident()) == ned_staticex)
			{
				SCP<cned_staticex> poStaticExSP = scp_cast_ui<cned_staticex>(oFilterChildren.get_element());
				poStaticExSP->render(oMultiLineRenderer);
			}
			else
			{
				oFilterChildren.get_element()->render(oMultiLineRenderer);
			}

			ng_ydist yElementHeight = oMultiLineRenderer.finish_all().get_dy();
			yRowHeight = max(yRowHeight,yElementHeight);
			xCurrentX += dxImageWidth + dxI2IDistance + 
				m_oColArray[oFilterChildren.get_col_nr()].get_col_width() + dxColDistance;

			oFilterChildren.move_next();
			
			if(oFilterChildren.get_col_nr() == 0)
			{
				yCurrentY += yRowHeight;

				if(!oFilterChildren.is_end())
				{
					yCurrentY += dyRowDistance;
				}

				m_oRowHeightArray.Add(yRowHeight);
				yRowHeight = 0;
				xCurrentX = xStartingX;
			}
		}

		if(oFilterChildren.get_col_nr() != 0)	//zakoñcz ostatni (niepe³ny wiersz)
		{
			yCurrentY += yRowHeight;
			
			m_oRowHeightArray.Add(yRowHeight);
		}

		ng_ydist yHeight = yCurrentY + (roRenderer.is_printing() ? 0 : _metrics().optionbtn().get_bottom_margin(get_prop_border_type()));
		ng_size oOptionButtonSize(dxActualWidth,_get_std_height_for_rendering(yHeight));
		ng_size oForAllocSize;
		_on_finish_rendering(roRenderer,oOptionButtonSize,oForAllocSize);
		roRenderer.allocate_rect(get_ident(),-1,oForAllocSize,m_oActualSize,m_oVectorSize);
	}
	else
	{
		roRenderer.allocate_rect(get_ident(),-1,m_oActualSize,m_oActualSize,m_oVectorSize);
	}

	_validate_last_measured(NEDID_LAST);
}

void cned_option_button_::add_line(const cned_element_line & roLine)
{
}

//--------- drawing ------------------
void cned_option_button_::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	long nPrevTreeDisCnt;
	roForePainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	cned_option_filter_children oFilterChildren(this,roForePainter.is_printing());
	long nRenderedElementNr = 0;

	while(!oFilterChildren.is_end())
	{
		oFilterChildren.get_element()->draw_foreground(roForePainter,oPaintPoint);
		
		if(!roForePainter.is_printing())
		{
			ng_rect oImageRect;
			_get_image_rect(nRenderedElementNr,oPaintPoint,oImageRect);

			SCP<ng_image> poImageSP = get_manager()->get_special_image(_get_image_for_item(oFilterChildren.get_element_nr()));
			
			roForePainter.get_dc().draw_image(oImageRect,ng_size(),poImageSP,ngis_original,
				get_manager()->is_element_disabled(oFilterChildren.get_ident()) ? ngif_disable : ngif_col2tran);

			_store_extra_paint_rect(1 + oFilterChildren.get_element_nr(),oImageRect);
		}

		oFilterChildren.move_next();
		nRenderedElementNr++;
	}

	_draw_std_frame(roForePainter,ng_rect(oPaintPoint,m_oActualSize));
	roForePainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_option_button_::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	long nPrevTreeDisCnt;
	roBackPainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	
	ng_rect oBackRect(oPaintPoint,m_oActualSize);
	_draw_std_background(roBackPainter,oBackRect);

	cned_option_filter_children oFilterChildren(this,roBackPainter.is_printing());

	while(!oFilterChildren.is_end())
	{
		oFilterChildren.get_element()->draw_background(roBackPainter,oPaintPoint);
		oFilterChildren.move_next();
	}

	_store_main_paint_rect(oBackRect);

	roBackPainter.restore_disabled(nPrevTreeDisCnt);
}

//-------------- drawing helpers ---------------------
void cned_option_button_::_get_image_rect(long nItemNr,const ng_point & roCurrPoint,ng_rect & roImageRect) const
{
	long nImageCol = nItemNr % get_prop_colspan();
	long nImageRow = nItemNr / get_prop_colspan();

	const ng_xdist dxImageWidth	 = _metrics().optionbtn().get_image_width();
	const ng_xdist dxI2IDistance = _metrics().optionbtn().get_img2item_distance();
	const ng_xdist dxColDistance = _metrics().optionbtn().get_col_distance();
	const ng_ydist dyRowDistance = _metrics().optionbtn().get_row_distance();

	//ustal rozmiar
	roImageRect.set_left(roCurrPoint.get_x() + _metrics().optionbtn().get_left_margin(get_prop_border_type()));
	roImageRect.set_top(roCurrPoint.get_y() + _metrics().optionbtn().get_top_margin(get_prop_border_type()));
	roImageRect.set_width(dxImageWidth);
	roImageRect.set_height(_metrics().optionbtn().get_image_height());

	ng_xdist dxLeft = 0;
	//przesuñ w prawo 
	for(long nCol = 0; nCol < nImageCol; nCol++)
	{
		dxLeft += dxImageWidth + dxI2IDistance + m_oColArray[nCol].get_col_width() + dxColDistance;
	}
	roImageRect.offset(dxLeft,0);

	//przesuñ w dó³
	ng_ydist dyTop = 0;
	for(long nRow = 0; nRow < nImageRow; nRow++)
	{
		dyTop += m_oRowHeightArray[nRow] + dyRowDistance;
	}
	roImageRect.offset(0,dyTop);
}

//----------------------------------------------------------------------------------
void cned_option_button_::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();
	set_prop_border_type(NED_BORDER_STYLE_ROUNDED);
	set_prop_border_width(1);
}


//------------------ 
//
// szuka elementu na podstawie punktu (analizowany jest obrazek)
// zwraca numer elementu (liczone wsrod wszystkich dzieci oraz ident
//
//------------------ 

bool cned_option_button_::_find_image_from_point(const ng_point & roLocalPoint,long & rnElementNr,ned_ident & ridElement)
{
	ASSERT(!is_measure_pending());

	cned_option_filter_children oFilterChildren(this,false);
	long nRenderedElementNr = 0;

	while(!oFilterChildren.is_end())
	{
		ng_rect oImageRect;
		_get_image_rect(nRenderedElementNr,ng_point(),oImageRect);

		if(oImageRect.is_inside(roLocalPoint))
		{
			rnElementNr = oFilterChildren.get_element_nr();
			ridElement = oFilterChildren.get_ident();
			return true;
		}
			
		oFilterChildren.move_next();
		nRenderedElementNr++;
	}

	rnElementNr = -1;
	ridElement = NEDID_NOTHING;
	return false;
}


//--------------event handlers ---------------------------------------
void cned_option_button_::on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_LEFT_click() && !get_prop_disabled())
	{
		ng_point oPoint(roActionMouse.get_mouse_position());
		_screen2local(oPoint);
		long nElementNr;
		ned_ident idElement;
		if(_find_image_from_point(oPoint,nElementNr,idElement))
		{
			if(_on_internal_focus_change(nElementNr,idElement))
			{
				roResult.set_processed();
			}
		}
	}

	//ale nie przejmujemy focusa!
}

void cned_option_button_::on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	if(roActionMouse.is_LEFT_click() && !get_prop_disabled())
	{
		ng_point oPoint(roActionMouse.get_mouse_position());
		_screen2local(oPoint);
		long nElementNr;
		ned_ident idElement;
		if(_find_image_from_point(oPoint,nElementNr,idElement))
		{
			if(m_nInternalFocusInx == nElementNr)
			{
				if(_on_item_selected(nElementNr,idElement))
				{
					SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
					CSmartOleVariant oSOV;
					get_prop_value(oSOV);
					poEventDataSP->set_data(oSOV); 
					roResult.add_info(poEventDataSP);
				}
			}
		}
	}
}

void cned_option_button_::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	long nColSpan = get_prop_colspan();
	ASSERT(nColSpan > 0);
	nColSpan = max(1,nColSpan);

	long nCol = m_nInternalFocusInx % nColSpan;
	long nNewInternalFocus = m_nInternalFocusInx;

	switch(roActionKBD.get_keycode())
	{
	case VK_UP:
		if(nNewInternalFocus - nColSpan >= 0)
		{
			nNewInternalFocus -= nColSpan;
		}
	break;
	case VK_DOWN:
		if(nNewInternalFocus + nColSpan < get_child_count())
		{
			nNewInternalFocus += nColSpan;
		}
	break;
	case VK_LEFT:
		if(nCol > 0)
		{
			nNewInternalFocus --;
		}
	break;
	case VK_RIGHT:
		if(nCol < nColSpan - 1)
		{
			nNewInternalFocus ++;
		}
	break;
	}
	//normalize
	nNewInternalFocus = min(nNewInternalFocus,get_child_count() - 1);
	nNewInternalFocus = max(0,nNewInternalFocus);
	
	if(nNewInternalFocus != m_nInternalFocusInx)
	{
		ned_ident idElement = get_child_ident_on_pos(nNewInternalFocus);
		ASSERT(idElement != NEDID_NOTHING);
		_event_set_selection_to(idElement,nNewInternalFocus,roResult,false);
	}

	//sekwencja przejœcia dalej
	if(!roResult.is_processed())
	{
		switch(roActionKBD.get_keycode())
		{
		case VK_TAB:
		case VK_RETURN:
			{
				ned_ident idNext = find_element_next_prev(NEDID_NOTHING,!roActionKBD.is_SHIFT());
				if(idNext != NEDID_NOTHING)
				{
					//przestaw focus 
					get_manager()->_mark_new_focus_element(idNext);
					roResult.set_processed();
				}
			}
		break;
		default:
			;	//not processed
		}
	}
}

void cned_option_button_::process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_rect_container_::process_event_mouse_click(roCallStack,roActionMouse,roResult);
	
	if(!roResult.is_processed())
	{
		roResult.set_processed();
	}
}

void cned_option_button_::process_event_mouse_endclick(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult)
{
	cned_rect_container_::process_event_mouse_endclick(roCallStack,roActionMouse,roResult);
	
	if(roActionMouse.is_LEFT_click())
	{
		ned_ident idElement = roCallStack.target()->get_ident();
		SCP<cned_container> poContainerSP = roCallStack.target()->get_container();
		while(poContainerSP.Get() != this)
		{
			idElement = poContainerSP->get_ident();
			poContainerSP = poContainerSP->get_container();
		}
		
		long nPosition = scan_for_child_pos(idElement);
		_event_set_selection_to(idElement,nPosition,roResult,true);
	}
}

void cned_option_button_::on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult)
{
	if(m_nInternalFocusInx != -1)
	{
		_invalidate_image_rect(m_nInternalFocusInx);
	}
}

void cned_option_button_::_event_set_selection_to(ned_ident idElement,long nElementNr,ned_action_result & roResult,bool bChildClick)
{
	if(_on_internal_focus_change(nElementNr,idElement))
	{
		if(bChildClick || get_type() == ned_radio)
		{
			if(_on_item_selected(nElementNr,idElement))
			{
				SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
				CSmartOleVariant oSOV;
				get_prop_value(oSOV);
				poEventDataSP->set_data(oSOV); 
				roResult.add_info(poEventDataSP);
			}
		}
		else
		{
			roResult.set_processed();
		}
	}
}

//--------------------------------------------------------------------
// check box
//--------------------------------------------------------------------

//--------- drawing ------------------
void cned_checkbox::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oChkBoxRect(oPaintPoint,m_oActualSize);

	cned_scroll_clipper oScrollClipper(roForePainter,oChkBoxRect);

	ng_point oChildrenPoint(roCurrentPoint);
	if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		oChildrenPoint.offset(-get_scroll_pos());
	}
	cned_option_button_::draw_foreground(roForePainter,oChildrenPoint);
}

void cned_checkbox::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oChkBoxRect(oPaintPoint,m_oActualSize);

	cned_scroll_clipper oScrollClipper(roBackPainter,oChkBoxRect);
		
	ng_point oChildrenPoint(roCurrentPoint);
	if(roBackPainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		oChildrenPoint.offset(-get_scroll_pos());
	}
	cned_option_button_::draw_background(roBackPainter,oChildrenPoint);
}

//--------------event handlers ---------------------------------------
void cned_checkbox::on_event_mouse_wheel(const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	ng_point oCurrentPoint;
	_local2screen(oCurrentPoint);
	oCurrentPoint.offset(get_scroll_pos()); //korekta - pomijamy nasze w³asne przescrolowanie
	ng_rect oScrollableRect(oCurrentPoint,m_oActualSize);

	_scroll_event_wheel(roActionMouseWheel,roResult,oScrollableRect);
}

void cned_checkbox::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	if(roActionKBD.get_keycode() == VK_SPACE)
	{
		ned_ident idElement = get_child_ident_on_pos(m_nInternalFocusInx);
		if(_on_item_selected(m_nInternalFocusInx,idElement))
		{
			SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
			CSmartOleVariant oSOV;
			get_prop_value(oSOV);
			poEventDataSP->set_data(oSOV); 
			roResult.add_info(poEventDataSP);
		}
	}
	else
	{
		cned_option_button_::on_event_keydown(roActionKBD,roResult);
	}
}

//-------------- event forwarders -------------- -------------- -------
void cned_checkbox::process_event_mouse_wheel(ned_path_to_element & roCallStack,const ned_action_mouse_wheel & roActionMouseWheel,ned_action_result & roResult)
{
	cned_option_button_::process_event_mouse_wheel(roCallStack,roActionMouseWheel,roResult);
	
	if(!roResult.is_processed())
	{
		on_event_mouse_wheel(roActionMouseWheel,roResult);
	}
}

//-------------- element finders ------------------------
ned_ident cned_checkbox::find_element_from_point(const ng_point & roPoint)
{
	//uwzglêdnij scroll
	ng_point oInternalPoint(roPoint);
	oInternalPoint.offset(get_scroll_pos());

	return cned_option_button_::find_element_from_point(oInternalPoint);
}

void cned_checkbox::_on_finish_rendering(cned_renderer_ & roRenderer,const ng_size & roFullSize,
		ng_size & roForAllocSize)
{
	if(is_normal_height_value(get_prop_extheight()))
	{
		ng_ydist dyHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
		if(dyHeight < roFullSize.get_dy())
		{
			roForAllocSize = ng_size(roFullSize.get_dx(), dyHeight);
			//ned_to_do: na razie to roboczo
			show_vertical_bar(roRenderer,ng_point(roFullSize.get_dx(),0),dyHeight,roFullSize.get_dy(),dyHeight);
		}
		else
		{
			hide_vertical_bar();
			roForAllocSize = roFullSize;
		}
	}
	else
	{
		cned_option_button_::_on_finish_rendering(roRenderer,roFullSize,roForAllocSize);
	}
}
