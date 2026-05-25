/*
	NAVO Enterprise 2003
	2003-03-27

	navo enhanced display (NED)

	page element

	rendering related functionality
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "scrollbar_ned.h"
#include "page_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const ng_xdist STARTING_AUTO_PAGE_WIDTH  = 10000;


/*
	1. zadeklarowane rozmiary s³u¿¹ od okreœlenia szerokoœci strony. jeœli szerokoœc
	   zadeklarowana jest mniejsza ni¿ minimalna dopuszczalna, to jest brana wiêksza z nich.

	2. rezerwowany jest obszar na tytu³, marginesy i ramkê (jeœli wystêpuj¹)

	3. na wynikowym punkcie top-left oraz szerokoœci, przy za³o¿onej nieskoñczonej 
		wysokoœci robiony jest layout

	4. w zale¿noœci o zadeklarowanych rozmiarów oraz wyników ustalany jest rozmiar prostok¹ta
	   strony (po uwzglêdnieniu marginesów)

	5. jeœli wyniki wysz³y wiêksze ni¿ rozmiar strony w poprzednim punkcie to pojawia siê scroll


	BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
	BCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCB
	BMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIMMB
	BMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMB
	BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

	B order
	C aption
	M argin
	I nterior
*/

/*
	oblicz minimaln¹ szerokoœæ body
	uwzglêdnia:
		minimaln¹ szerokoœæ dzieci
		minimaln¹ szerokoœæ caption jeœli jest
		zadeklarowane rozmiary width='max'/'min'/'auto'/liczba
*/

void cned_page::_measure_body_min_width(const ned_measure_param & roMParam,
										ng_xdist & rdxMinWidth,ng_xdist & rdxMinWidthNoMargins)
{
	ng_xdist dxLeftMargin = get_manager()->to_internal(ng_size(get_prop_extmargins().get_left(),0)).get_dx();
	ng_xdist dxRightMargin = get_manager()->to_internal(ng_size(get_prop_extmargins().get_right(),0)).get_dx();

	if(is_measure_pending())
	{
		m_oMetrics.reset();
		//zmierz caption
		cned_metrics oCaptionMetrics;
		
		//zmierz caption jeœli jest widoczny
		if(get_prop_caption() && (roMParam.get_paint_mode() != pm_printer))
		{
			_get_caption()->get_metrics(roMParam,oCaptionMetrics);
		}
		
		//zmierz 'body' - dzieci
		cned_metrics oGroupMetrics;

		if(!_get_header()->get_prop_hidden())
		{
			_get_header()->get_metrics(roMParam,oGroupMetrics);
		}

		if(!_get_footer()->get_prop_hidden())
		{
			_get_footer()->get_metrics(roMParam,oGroupMetrics);
		}

		{
			ned_measure_param oChildMParam(roMParam);
			oChildMParam.update_req_y(get_scroll_pos().get_dy());
			_get_group_metrics(oChildMParam,oGroupMetrics);
		}

		
		//szerokoœæ body + marignesy
		rdxMinWidth = oGroupMetrics.get_minimal_width() + dxLeftMargin + dxRightMargin;
		//weŸ max z tego i caption
		rdxMinWidth = max(rdxMinWidth,oCaptionMetrics.get_minimal_width());
		
		//porównaj z wartoœciami zadeklarowanymi
		ng_xdist dxDeclWidth = rdxMinWidth;
		
		if(_is_max_width_in_effect())
		{
			dxDeclWidth = roMParam.get_complete_arena().get_width();
		}
		else
		{
			if(is_auto_width_value(get_prop_extwidth()))
			{
				dxDeclWidth = get_manager()->to_internal(ng_size(STARTING_AUTO_PAGE_WIDTH,0)).get_dx();
			}
			else
			{
				if(is_normal_width_value(get_prop_extwidth()))
				{
					dxDeclWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
				}
				else
				{
					//'min' - use computed rdxMinWidth
				}
			}
		}
		
		//ensure that declared width is not to narrow
		rdxMinWidth = max(rdxMinWidth,dxDeclWidth);
		m_oMetrics.update(rdxMinWidth,0,0);

		ASSERT(rdxMinWidth >= oGroupMetrics.get_minimal_width());
		ASSERT(rdxMinWidth >= oCaptionMetrics.get_minimal_width());

		clear_measure_pending();
	}
	else
	{
		rdxMinWidth = m_oMetrics.get_minimal_width();
	}

	//odejmij marginesy - zostaje samo body
	rdxMinWidthNoMargins = rdxMinWidth - dxLeftMargin - dxRightMargin;

	ASSERT(rdxMinWidth >= rdxMinWidthNoMargins);
}

//-------------- dimension helpers -------------------

void cned_page::_get_shadows_rects(const ng_point & roCurrentPoint,ng_rect & roRightShadowRect,ng_rect & roBottomShadowRect) const
{
	ng_rect oRect(roCurrentPoint,m_oActualSize);

	roRightShadowRect = 
		ng_rect(
			oRect.get_right() + 1,
			oRect.get_top() + _metrics().page().get_shadow_height(),
			oRect.get_right() + 1 + _metrics().page().get_shadow_width(),
			oRect.get_bottom()
		);
	roBottomShadowRect = 
		ng_rect(
			oRect.get_left() + _metrics().page().get_shadow_width(),
			oRect.get_bottom() + 1,
			oRect.get_right()  + 1 + _metrics().page().get_shadow_width(),
			oRect.get_bottom() + _metrics().page().get_shadow_height()
		);
}

//------------------------------------------------------------------------------------

void cned_page::render(cned_renderer_ & roRenderer)
{
	ASSERT(is_measure_pending() || get_type() == ned_subpage);

	//---------------------------------
	//1. compute minimal width and measure all necessary elements (children,caption)
	ned_measure_param oMParam(roRenderer.get_info_dc(),roRenderer.get_paint_mode(),roRenderer.get_req_y(),
		roRenderer.get_complete_arena());
	ng_xdist dxMinWidth;
	ng_xdist dxMinWidthNoMargins;
	_measure_body_min_width(oMParam,dxMinWidth,dxMinWidthNoMargins);

	ng_xdist dxLeftMargin	= get_manager()->to_internal(ng_size(get_prop_extmargins().get_left(),0)).get_dx();
	ng_ydist dyTopMargin	= get_manager()->to_internal(ng_size(0,get_prop_extmargins().get_top())).get_dy();
	ng_ydist dyBottomMargin = get_manager()->to_internal(ng_size(0,get_prop_extmargins().get_bottom())).get_dy();
	ng_xdist dxRightMargin = get_manager()->to_internal(ng_size(get_prop_extmargins().get_right(),0)).get_dx();
	
	ng_ydist dyTopBorder    = 0;
	ng_xdist dxLeftBorder	= 0;
	ng_ydist dyBottomBorder = 0;
	ng_xdist dxRightBorder	= 0;

	//wylicz efektywne ramki i marginesy
	if(roRenderer.get_paint_mode() != pm_printer)
	{
		if(!_is_max_width_in_effect())
		{
			dxLeftBorder = _metrics().page().get_border_width();
			dxRightBorder= _metrics().page().get_border_width();
		}
		else
		{
			dyTopMargin = 0;		//reduce margin
		}
		if(!_is_max_height_in_effect())
		{
			dyTopBorder = _metrics().page().get_border_height();
			dyBottomBorder = _metrics().page().get_border_height();
		}
	}
	
	const ng_point oCaptionTopLeftPoint(dxLeftBorder,dyTopBorder);
	ng_point oCurrentPoint(oCaptionTopLeftPoint);

	//---------------------------------
	//2. render caption
	if(get_prop_caption() && !roRenderer.is_printing())
	{
		//+1 do dxMinWidth to zwyk³a ³ata bo coœ siê Ÿle malowa³o :)

		cned_column_renderer oCaptionRenderer(roRenderer,oCurrentPoint,dxMinWidth+1);
		_get_caption()->render(oCaptionRenderer);
		
		oCurrentPoint.set_y(oCaptionRenderer.get_current_pos().get_y());
	}

	//przygotuj po³o¿enie dla dzieci - uwzglêdnij marginesy
	oCurrentPoint.offset(dxLeftMargin,dyTopMargin);
	
	//---------------------------------
	//3.0 render header
	//---------------------------------
	if(!_get_header()->get_prop_hidden())
	{
		cned_column_renderer oHeaderRenderer(roRenderer,oCurrentPoint,dxMinWidthNoMargins);
		_get_header()->render(oHeaderRenderer);
		
		oCurrentPoint.set_y(oHeaderRenderer.get_current_pos().get_y());
	}
	//---------------------------------
	//3.2 render footer
	ng_ydist dyFooterHeight = 0;
	ng_ycoord yFooterTop = oCurrentPoint.get_y();
	
	if(!_get_footer()->get_prop_hidden())
	{
		cned_column_renderer oFooterRenderer(roRenderer,oCurrentPoint,dxMinWidthNoMargins);
		_get_footer()->render(oFooterRenderer);
		
		dyFooterHeight = oFooterRenderer.get_current_pos().get_y() - yFooterTop;
	}

	//---------------------------------
	//3.1 render children
	const ng_point oChildTopLeftPoint(oCurrentPoint);

	cned_abspos_render_manager oARM;

	cned_transport_renderer oChildTranRend(roRenderer,oCurrentPoint,dxMinWidthNoMargins);
	oChildTranRend.update_req_y(get_scroll_pos().get_dy());

	ng_size oFullVirtualChildSize = _render_group(oChildTranRend,oARM);

	ASSERT(oFullVirtualChildSize.get_dx() <= dxMinWidthNoMargins);

	//3. render absolute children
	{
		ng_rect oChildRect = ng_rect(oCurrentPoint,ng_size(dxMinWidthNoMargins,oFullVirtualChildSize.get_dy()));
		ng_size oAbsSize = oARM.render(roRenderer,oChildRect);
		
		//korekta rozmiaru ze wzglêdu na elementy absolutne
		if(oAbsSize.get_dx() > dxMinWidthNoMargins || oAbsSize.get_dy() > oFullVirtualChildSize.get_dy())
		{
			ASSERT(oAbsSize.get_dx() >= dxMinWidthNoMargins);
			ASSERT(oAbsSize.get_dy() >= oFullVirtualChildSize.get_dy());
			
			dxMinWidth += oAbsSize.get_dx() - dxMinWidthNoMargins;
			oFullVirtualChildSize = oAbsSize;
		}
	}

	//---------------------------------
	//4. renderowanie gotowe - analiza wyników
	//---------------------------------
	
	//4.1. jeœli jest podana wysokoœæ (wysokoœæ = top.marg + fullchildsize + bottom.marg)
	//to j¹ uwzglêdniamy 
	//dyPageHeight != rozmiar kontrolki <page>, ale u¿yteczny rozmiar strony, w tym marginesy
	ng_ydist dyPageHeight = _get_std_height_for_rendering(dyTopMargin + oFullVirtualChildSize.get_dy() + dyBottomMargin);

#ifdef _DEBUG
	{
		if(is_auto_height_value(get_prop_extheight()))
		{
			//nie powinno siê nic zmieniæ dla automatycznej wysokoœci
			ASSERT(dyPageHeight - dyTopMargin - dyBottomMargin == oFullVirtualChildSize.get_dy());
		}
	}
#endif

	//4.2 wyliczanie rozmiaru zewnêtrznego
	m_oActualSize = ng_size(dxMinWidth,oChildTopLeftPoint.get_y() + dyPageHeight - dyTopMargin + dyFooterHeight);

	//dodaj border - lewy i górny ju¿ jest, zatem prawy i dolny
	if(roRenderer.get_paint_mode() != pm_printer)
	{
		if(!_is_max_width_in_effect())
		{
			m_oActualSize.set_dx(m_oActualSize.get_dx() + dxLeftBorder + dxRightBorder);
		}
		if(!_is_max_height_in_effect())
		{
			m_oActualSize.set_dy(m_oActualSize.get_dy() + dyBottomBorder);
		}
	}

	m_oFullVirtualSize = m_oActualSize;
	
	//zadeklarowane height max
	if(_is_max_height_in_effect())
	{
		m_oActualSize.set_dy(roRenderer.get_complete_arena().get_height());
		m_oFullVirtualSize.set_dy(m_oActualSize.get_dy());
	}
	else
	{
		//normalne lub auto -> tylko aby mieœci³o siê na arenie
		m_oActualSize.set_dy(min(m_oActualSize.get_dy(),roRenderer.get_complete_arena().get_height()));
	}
	
	if(_is_max_width_in_effect())
	{
		m_oActualSize.set_dx(roRenderer.get_complete_arena().get_width());
		m_oFullVirtualSize.set_dx(m_oActualSize.get_dx());
	}
	else
	{
		m_oActualSize.set_dx(min(m_oActualSize.get_dx(),roRenderer.get_complete_arena().get_width()));
	}


	//4.3. ustalenie realnego prostok¹ta 'dzieci'
	{
		ng_size oChildSize(m_oActualSize.get_dx() - dxLeftMargin - dxRightMargin,
			m_oActualSize.get_dy() - oChildTopLeftPoint.get_y() - dyBottomMargin - dyFooterHeight);
		if(!_is_max_height_in_effect())
		{
			oChildSize.set_dy(oChildSize.get_dy() - dyBottomBorder);
		}
		if(!_is_max_width_in_effect())
		{
			oChildSize.set_dx(oChildSize.get_dx() - dxLeftBorder - dxRightBorder);
		}
		m_oChildRect = ng_rect(oChildTopLeftPoint,oChildSize);
	}
	
	if(roRenderer.get_paint_mode() != pm_printer)
	{
		//pokazywanie - ukrywanie scrolla
		if((oFullVirtualChildSize.get_dy() > m_oChildRect.get_height()) &&
		  !is_maximal_height_value(get_prop_extheight()))
		{

			long nPageRange = m_oChildRect.get_height();
			long nTotalRange = oFullVirtualChildSize.get_dy();
			const ng_xdist DXSPACE_LEFT_OF_VSCROLL = 4;
			ng_point oScrollLeftTop(m_oChildRect.get_right() + DXSPACE_LEFT_OF_VSCROLL,m_oChildRect.get_top());
			ng_xdist dxScrollWidth = show_vertical_bar(roRenderer,
				oScrollLeftTop,m_oChildRect.get_height(),nTotalRange,nPageRange);
			
			ng_xdist dxHorizAdvance = max(dxScrollWidth + DXSPACE_LEFT_OF_VSCROLL,dxRightMargin) - dxRightMargin;

			m_oActualSize.set_dx(m_oActualSize.get_dx() + dxHorizAdvance);
			m_oFullVirtualSize.set_dx(m_oFullVirtualSize.get_dx() + dxHorizAdvance);

			//jeœli wychodzi poza - musimy skorygowaæ po³o¿enie scrolla, rozmiar i childrect
			ng_xdist dxHorizOverflow = m_oActualSize.get_dx() - roRenderer.get_complete_arena().get_width();
			if(dxHorizOverflow > 0)
			{
				m_oActualSize.set_dx(m_oActualSize.get_dx() - dxHorizOverflow);
				_get_vert_bar()->move_by(-1,ng_size(-dxHorizOverflow,0));
				m_oChildRect.set_width(m_oChildRect.get_width() - dxHorizOverflow);
			}
		}
		else
		{
			hide_vertical_bar();
		}

		if((oFullVirtualChildSize.get_dx() > m_oChildRect.get_width()) &&
			!is_maximal_height_value(get_prop_extheight()))
		{
			long nPageRange = m_oChildRect.get_width();
			long nTotalRange = oFullVirtualChildSize.get_dx();
			ng_point oScrollLeftTop(m_oChildRect.get_left(),m_oActualSize.get_dy());
			
			ng_ydist dyScrollHeight = show_horizontal_bar(roRenderer,
				oScrollLeftTop,m_oChildRect.get_width(),nTotalRange,nPageRange);

			m_oActualSize.set_dy(m_oActualSize.get_dy() + dyScrollHeight + dyBottomBorder);
			m_oFullVirtualSize.set_dy(m_oFullVirtualSize.get_dy() + dyScrollHeight + dyBottomBorder);

			ng_ydist dyVertOverflow = m_oActualSize.get_dy() - roRenderer.get_complete_arena().get_height();
			if(dyVertOverflow > 0)
			{
				m_oActualSize.set_dy(m_oActualSize.get_dy() - dyVertOverflow);
				_get_horiz_bar()->move_by(-1,ng_size(0,-dyVertOverflow));

			// m_oChildRect nie pomniejszamy - ten obszar nie ma marginesów w sobie
			// scrolle wchoda teraz na obszar marginesów
			//
			// m_oChildRect.set_height(m_oChildRect.get_height() - dyVertOverflow);
			}
		}
		else
		{
			hide_horizontal_bar();
		}

		
		if(_is_vert_bar())
		{
			//---------------------------------
			//rerender caption cause width changed (vert bar is just shown)
			//---------------------------------
			if(get_prop_caption())
			{
				ng_xdist dxCaptionWidth = m_oActualSize.get_dx();
				if(!_is_max_width_in_effect())
				{
					//-1 = ta sama ³ata co przy pierwotnym renderowaniu caption'a
					dxCaptionWidth -= dxLeftBorder + dxRightBorder - 1;
				}
			
				cned_column_renderer oCaptionRenderer(roRenderer,oCaptionTopLeftPoint,dxCaptionWidth);
				_get_caption()->render(oCaptionRenderer);
			}

		}
	}

	if(!_get_footer()->get_prop_hidden())
	{
		//move footer to appropiate position
		 _get_footer()->move_by(-1,ng_size(0,
			m_oActualSize.get_dy() - dyFooterHeight - dyBottomMargin - yFooterTop));
	}

	//ned_to_do: to jest jakieœ nie³adne :(
	//dla subpage ustal ich vector we wspó³rzednych areny
	if(get_type() == ned_subpage)
	{
		ng_point oPoint = roRenderer.get_current_pos();
		m_oVectorSize = ng_size();
		//specjalna wersja local2arens, która zatrzymuje siê na subpage
		//gdy¿ ta subpage ma ju¿ wspó³rzêdne areny
		SCP<cned_container> poContainerSP = get_container();
		while(poContainerSP.PointsObject())
		{
			oPoint.offset(poContainerSP->m_oVectorSize);
			if(poContainerSP->get_type() == ned_subpage)
			{
				break;
			}
			poContainerSP = poContainerSP->get_container();
		}
		m_oVectorSize = oPoint.distance(ng_point());
	}

	roRenderer.__add_to_post_renderer(get_ident());

	ASSERT(m_oFullVirtualSize.get_dx() >= m_oActualSize.get_dx());
	ASSERT(m_oFullVirtualSize.get_dy() >= m_oActualSize.get_dy());
}

