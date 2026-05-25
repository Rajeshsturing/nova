/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_paragraph / <p>

	paragraf - grupa elementów 

*/

#ifndef _PARAGRAPH_NED_H_
#define _PARAGRAPH_NED_H_

namespace ned
{

class cned_paragraph : public cned_group_helper__
{
public:
	//-------------- property get ---------------
	void set_prop_vert_padding(ng_ydist dyVertPadding);
	void set_prop_horiz_padding(ng_xdist dxHorizPadding);

	//-------------- property set ---------------
	ng_ydist get_prop_vert_padding() const;
	ng_xdist get_prop_horiz_padding() const;

	virtual void render(cned_renderer_ & roRenderer);
	virtual void get_children_metrics(const ned_measure_param & roMParam);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
protected:
	cned_paragraph(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	void _copy_properties(cned_paragraph * poDestinationPara);

	ng_xdist	m_dxHorizPadding;
	ng_ydist	m_dyVertPadding;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline cned_paragraph::cned_paragraph(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_group_helper__(poManager,eType,idThis),
	m_dxHorizPadding(0),
	m_dyVertPadding(0)
{
}

inline void cned_paragraph::get_children_metrics(const ned_measure_param & roMParam)
{
	_get_group_metrics(roMParam,m_oMetrics);

	//wylicz metrics elementów
	cned_metrics oGroupMetrics;
	_get_group_metrics(roMParam,oGroupMetrics);

	//powiêksz wynik o ramki
	const ng_xdist xExtension = 2 * (_get_frame_px_width() + get_prop_horiz_padding());
	const ng_ydist yExtension = 2 * (_get_frame_px_width() + get_prop_vert_padding());

	m_oMetrics.update(oGroupMetrics.get_minimal_width() + xExtension,
		oGroupMetrics.get_minimal_height() + yExtension, oGroupMetrics.get_weight());
}

inline void cned_paragraph::render(cned_renderer_ & roRenderer)
{
	//zapewnij miejsce
	roRenderer.ensure_width(m_oMetrics.get_minimal_width());

	const ng_xdist xExtension = _get_frame_px_width() + get_prop_horiz_padding();
	const ng_ydist yExtension = _get_frame_px_width() + get_prop_vert_padding();
	const ng_xdist dxActualWidth = _get_std_width_for_rendering(roRenderer) - xExtension - xExtension;

	cned_transport_renderer oChildTranspRend(roRenderer,ng_point(xExtension,yExtension),dxActualWidth);

	cned_abspos_render_manager oARM;
	
	ng_size oChildSize = _render_group(oChildTranspRend,oARM);

	ng_size oParaSize(dxActualWidth + xExtension + xExtension,oChildSize.get_dy() + yExtension + yExtension);

	ng_size oChildSize2(oParaSize.get_dx() - xExtension - xExtension,oParaSize.get_dy() - yExtension - yExtension);
	ng_size oAbsSize = oARM.render(roRenderer,ng_rect(ng_point(xExtension,yExtension),oChildSize2));
	
	//korekta rozmiaru ze wzglêdu na elementy absolutne
	if(oAbsSize.get_dx() > oChildSize2.get_dx() || oAbsSize.get_dy() > oChildSize2.get_dy())
	{
		ASSERT(oAbsSize.get_dx() >= oChildSize2.get_dx());
		ASSERT(oAbsSize.get_dy() >= oChildSize2.get_dy());

		oParaSize.set_dx(oParaSize.get_dx() + oAbsSize.get_dx() - oChildSize2.get_dx());
		oParaSize.set_dy(oParaSize.get_dy() + oAbsSize.get_dy() - oChildSize2.get_dy());
	}

	//--------------------------
	//uwzglêdniamy wysokoœc zadeklarowan
	ng_ydist yFinalHeight = _get_std_height_for_rendering(oParaSize.get_dy());
	yFinalHeight = max(yFinalHeight,oParaSize.get_dy());
	oParaSize.set_dy(yFinalHeight);
	//---------------------------

	roRenderer.allocate_rect(get_ident(),-1,oParaSize,m_oActualSize,m_oVectorSize);
}

//--------- drawing ------------------
inline void cned_paragraph::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_draw_foreground_children(roForePainter,oPaintPoint);
	_draw_std_frame(roForePainter,ng_rect(oPaintPoint,m_oActualSize));
}

inline void cned_paragraph::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oParaRect(oPaintPoint,m_oActualSize);
	_draw_std_background(roBackPainter,oParaRect);
	_draw_background_children(roBackPainter,oPaintPoint);

	_store_main_paint_rect(oParaRect);
}

inline void cned_paragraph::set_fixed_properties()
{
	cned_group_helper__::set_fixed_properties();

	set_prop_extwidth(NED_MAX_WIDTH);		//domyœlnie paragraf zajmuje ca³¹ szerokoœæ
	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
}

//-------------- property get ---------------
inline void cned_paragraph::set_prop_vert_padding(ng_ydist dyVertPadding)
{
	if(get_prop_vert_padding() == dyVertPadding)
	{
		return;
	}

	m_dyVertPadding = dyVertPadding;

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_paragraph::set_prop_horiz_padding(ng_xdist dxHorizPadding)
{
	if(get_prop_horiz_padding() == dxHorizPadding)
	{
		return;
	}

	m_dxHorizPadding = dxHorizPadding;

	_size_info_dirty();
	_vse_dirty();
}

//-------------- property set ---------------
inline ng_ydist cned_paragraph::get_prop_vert_padding() const
{
	return m_dyVertPadding;
}

inline ng_xdist cned_paragraph::get_prop_horiz_padding() const
{
	return m_dxHorizPadding;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_paragraph::_copy_properties(cned_paragraph * poDestinationPara)
{
	poDestinationPara->m_dxHorizPadding = m_dxHorizPadding;
	poDestinationPara->m_dyVertPadding = m_dyVertPadding;
}

inline void cned_paragraph::fill_clone(cned_element * poDestination)
{
	cned_group_helper__::fill_clone(poDestination);
	cned_paragraph * poDestPara = cast_ui<cned_paragraph>(poDestination);
	
	_copy_properties( poDestPara );
}

//-------- page breaking ---------------------------------

inline void cned_paragraph::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_group_helper__::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_paragraph * poDestPara = cast_ui<cned_paragraph>(poDestination);
	
	_copy_properties( poDestPara );
}


}

#else
	#error __FILE__ already included
#endif
