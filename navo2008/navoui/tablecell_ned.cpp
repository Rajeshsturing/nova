/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_tablecell
		komórka tabelki
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "tablerow_ned.h"
#include "tablecell_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void cned_tablecell::set_fixed_properties()
{
	cned_group_helper__::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
}

void cned_tablecell::set_prop_colspan(long nColSpan)
{
	if(nColSpan < 1)
	{
#ifdef _DEVELOPER_EDITION_
		CString oString;
		oString.Format("colspan musi byæ >= 1 a podano %d. Idctrl=%d",nColSpan,get_ident());
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
#else
		nColSpan = 1;
#endif
	}
	if(m_nColSpan == nColSpan)
	{
		return;
	}
	m_nColSpan = nColSpan;
	
	_size_info_dirty();
	_vse_dirty();
	_get_row()->on_cell_colspan_change();
}

void cned_tablecell::set_prop_rowspan(long nRowSpan)
{
	if(nRowSpan < 1)
	{
#ifdef _DEVELOPER_EDITION_
		CString oString;
		oString.Format("rolspan musi byæ >= 1 a podano %d. Idctrl=%d",nRowSpan,get_ident());
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
#else
		nRowSpan = 1;
#endif
	}
	if(m_nRowSpan == nRowSpan)
	{
		return;
	}
	m_nRowSpan = nRowSpan;

	_size_info_dirty();
	_vse_dirty();
	_get_row()->on_cell_rowspan_change();
}

void cned_tablecell::set_prop_hidden(bool bHidden)
{
	if(get_prop_hidden() == bHidden)
	{
		return;
	}
	cned_group_helper__::set_prop_hidden(bHidden);
	_get_row()->on_cell_show_hide();
}

//-----------------------------------------------------------------------------------
//-------------- rendering support -------------------
//--------------------------------------------------------------------
void cned_tablecell::get_children_metrics(const ned_measure_param & roMParam)
{
	//wylicz metrics elementów
	cned_metrics oGroupMetrics;
	_get_group_metrics(roMParam,oGroupMetrics);

	//powiêksz wynik o ramki
	ng_xdist xExtension = 2 * _get_frame_px_width();
	ng_ydist yExtension = 2 * _get_frame_px_width();

	//powiêksz wynik o padding (ale nie dla grida)
	if(_get_table()->get_type() != ned_grid)
	{
		xExtension += get_manager()->__zoomize(2 * _metrics().tablecell().get_padding_width());
		yExtension += get_manager()->__zoomize(2 * _metrics().tablecell().get_padding_height());
	}

	m_oMetrics.update(oGroupMetrics.get_minimal_width() + xExtension,
		oGroupMetrics.get_minimal_height() + yExtension, oGroupMetrics.get_weight());
}

const cned_metrics & cned_tablecell::get_metrics(const ned_measure_param & roMParam,
	 ng_xdist & rxMinInternalCellWidth)
{
	ASSERT(!get_prop_hidden());

	if(is_measure_pending())
	{
		m_oMetrics.reset();
		get_children_metrics(roMParam);
		
		if(is_normal_width_value(get_prop_extwidth()))
		{
			ng_xdist dxWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
			if(dxWidth > m_oMetrics.get_minimal_width())
			{
				m_oMetrics.update(dxWidth,m_oMetrics.get_minimal_height(),m_oMetrics.get_weight());
			}
		}

		clear_measure_pending();
	}

	//zarezewuj przestrzeñ na ramki
	rxMinInternalCellWidth = m_oMetrics.get_minimal_width() - 2 * _get_frame_px_width();
	
	return m_oMetrics;
}

ng_ydist cned_tablecell::render(cned_transport_renderer & roTransportRenderer,long nAllocRowNr,long nColNr)
{
	ASSERT(!get_prop_hidden());

	//musi prawid³owo wywo³any
	/*ASSERT(roTransportRenderer.get_current_width() >= 
			m_oMetrics.get_minimal_width() - 2 * _get_frame_px_width());*/

	//okreœl obszar wewnêtrzny dla kontolek
	//(musimy zarezerwowaæ obszar na padding)
	//pobierz wspóln¹ przestrzeñ dla ramek
	ng_rect oSpaceRect;
	_get_section()->get_cell_common_border_space(this,nAllocRowNr,nColNr,oSpaceRect);
	
	long nFramePxWidth = _get_frame_px_width();
	ng_xdist dxLeft		= nFramePxWidth - oSpaceRect.get_left();
	ng_xdist dxRight	= nFramePxWidth - oSpaceRect.get_right();
	ng_ydist dyTop		= nFramePxWidth - oSpaceRect.get_top();
	ng_ydist dyBottom	= nFramePxWidth - oSpaceRect.get_bottom();

	ASSERT(dxLeft >= 0);
	ASSERT(dxRight >= 0);
	ASSERT(dyTop >= 0);
	ASSERT(dyBottom >= 0);
	
	if(_get_table()->get_type() != ned_grid)
	{
		ng_xdist dxZoomedWidth = get_manager()->__zoomize(_metrics().tablecell().get_padding_width());
		dxLeft   += dxZoomedWidth;
		dxRight  += dxZoomedWidth;

		ng_ydist dyZoomedHeight = get_manager()->__zoomize(_metrics().tablecell().get_padding_height());
		dyTop    += dyZoomedHeight;
		dyBottom += dyZoomedHeight;
	}
	
	ng_xdist xWidth = roTransportRenderer.get_current_width() - dxLeft - dxRight;
	
	//utwórz renderer na pomniejszonym obszarze
	cned_transport_renderer oChildTranspRend(roTransportRenderer,ng_point(dxLeft,dyTop),xWidth);

	cned_abspos_render_manager oARM;

	ng_size oChildSize = _render_group(oChildTranspRend,oARM);

	ASSERT(oChildSize.get_dx() <= roTransportRenderer.get_current_width());
	
	//wspó³rzêdne wzglêdem wnêtrza
	ng_size oAbsSize = oARM.render(roTransportRenderer,ng_rect(ng_point(dxLeft,dyTop),
		ng_size(xWidth,oChildSize.get_dy())));
	
	//korekta rozmiaru ze wzglêdu na elementy absolutne
	//ale ignorujemy zmianê szerokoœci - musi pasowaæ !
	ASSERT(oAbsSize.get_dx() <= xWidth);

	if(oAbsSize.get_dy() > oChildSize.get_dy())
	{
		oChildSize.set_dy(oAbsSize.get_dy());
	}

	//zapamiêtaj rozmiar - do u¿ytej wysokoœci dodaj padding + kawa³ek ramek. Szerokoœc jest fixed !

	m_oActualSize = ng_size(roTransportRenderer.get_current_width(),
		oChildSize.get_dy() + dyTop + dyBottom);

	m_oVectorSize = roTransportRenderer.get_current_pos().distance(ng_point());


//	TRACE("cell=%d,vector=(%d,%d),size=(%d,%d)\n",get_ident(),m_oVectorSize.get_dx(),
//		m_oVectorSize.get_dy(),m_oActualSize.get_dx(),m_oActualSize.get_dy());

	roTransportRenderer.__add_to_post_renderer(get_ident());

	return m_oActualSize.get_dy();
}

//--------- drawing ------------------
void cned_tablecell::draw_foreground(cned_fore_painter & roForePainter,
	const ng_point & roCurrentPoint,const long nAllocRowNr,const long nColNr)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_draw_foreground_children(roForePainter,oPaintPoint);

	long nFramePxWidth = _get_frame_px_width();
	
	if(get_prop_border_type() != NED_BORDER_STYLE_NONE && nFramePxWidth != 0)
	{
		ng_rect oFrameRect(oPaintPoint,m_oActualSize);

		//pobierz wspóln¹ przestrzeñ dla ramek
		ng_rect oSpaceRect;
		_get_section()->get_cell_common_border_space(this,nAllocRowNr,nColNr,oSpaceRect);

		oFrameRect.inflate(oSpaceRect.get_left(),oSpaceRect.get_top(),
			oSpaceRect.get_right(),oSpaceRect.get_bottom());

		_draw_std_frame(roForePainter,oFrameRect);
	}
}

//-------- page breaking ---------------------------------
void cned_tablecell::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager,
	long nAllocRowNr,long nColNr)
{
	SCP<cned_table> poTableSP = _get_table();

	cned_table::column & roTabColLeft = poTableSP->get_column(nColNr);
	cned_table::column & roTabColRight = poTableSP->get_column(nColNr + get_prop_colspan() - 1);
	long xAreaLeft = roTabColLeft.get_split_area_left();
	long xAreaRight = roTabColRight.get_split_area_right();

	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oElementRect(oPaintPoint,m_oActualSize);

#ifdef _DEBUG
	{
		long _debug_xAreaLeft = roSplitManager.find_x_area(oElementRect.get_left());
		long _debug_xAreaRight = roSplitManager.find_x_area(oElementRect.get_right());

		ASSERT(_debug_xAreaLeft == xAreaLeft);
		ASSERT(_debug_xAreaRight == xAreaRight);
	}
#endif

	long yAreaTop = roSplitManager.find_y_area(oElementRect.get_top());
	long yAreaBottom = roSplitManager.find_y_area(oElementRect.get_bottom());

	for(long yArea = yAreaTop; yArea <= yAreaBottom; yArea++)
	{
		for(long xArea = xAreaLeft; xArea <= xAreaRight; xArea++)
		{
			SCP<cned_element> poClonedTableCellSP = _make_clone_split(roSplitManager,xArea,yArea);
			cned_tablecell * poClonedCell = cast_ui<cned_tablecell>(poClonedTableCellSP);
			
			//ustawianie colspan - komórka nie dzieli siê w poziomie -> kopiujemy col-span
			//oraz ustawiamy szerokoœæ na wyliczon¹
			if(xAreaLeft == xAreaRight)
			{
				poClonedCell->set_prop_colspan(get_prop_colspan());

				//ma³a ³atka:
				//jest gdzieœ problem z okreœlaniem min. szerokoœci dla colspan > 1
				//min. szerokoœæ jaka pozostaje po odjêciu poprzednich kolumn jest za du¿a
				//prawdopodobnie s¹ to skumulowane b³êdy zaokr¹glên, bo b³¹d nie roœnie ale skacze
				//dlatego na razie nie podajemy szerokoœci dla colspan > 1
				
				if(get_prop_colspan() == 1)
				{
					poClonedCell->set_prop_extwidth(get_manager()->to_external(m_oActualSize).get_dx());
				}
			}
			else
			{
				long nNewColSpan = 0;
				for(long nIterCol = nColNr; nIterCol < nColNr + get_prop_colspan(); nIterCol++)
				{
					cned_table::column & roTabCol = poTableSP->get_column(nIterCol);
					
					if(roTabCol.get_split_area_left() <= xArea && roTabCol.get_split_area_right() >= xArea)
					{
						nNewColSpan++;
					}
				}
				
				ASSERT(nNewColSpan>=1 && nNewColSpan <= get_prop_colspan());
				
				poClonedCell->set_prop_colspan(nNewColSpan);
			}
			
			if(yAreaTop == yAreaBottom)
			{
				poClonedCell->set_prop_rowspan(get_prop_rowspan());
			}
		}
	}
	_make_children_split(oPaintPoint,roSplitManager);
}
