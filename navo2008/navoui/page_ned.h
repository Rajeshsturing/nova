/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	page element

*/

#ifndef _PAGE_NED_H_
#define _PAGE_NED_H_

namespace ned
{

enum epage_display_mode
{
	pdm_minimized,
	pdm_normal,
	pdm_maximized
};

class cned_page : public cned_group_helper__, public scroll_helper__
{
public:
	//-------------- property get ---------------
	const ng_rect & get_prop_extmargins() const;
	const CSmartOleVariant & get_prop_imagesrc() const;
	bool get_prop_caption() const;
	void get_prop_title(ng_string & roTitleString) const;
	epage_display_mode get_prop_display_mode() const;
	//-------------- property set ---------------
	void set_prop_extmargins(const ng_rect & roMarginsRect);
	void set_prop_imagesrc(const CSmartOleVariant & roImageSrcSOV);
	void set_prop_caption(bool bCaption);
	void set_prop_title(const ng_string & roTitle);
	void set_prop_display_mode(epage_display_mode ePDM);
	//------- paint support --------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	void prepare_paint_region(ng_region & roCommonRgn,const ng_point & roCurrentPoint);
	void paint(cned_painter_ & roPainter,const ng_point & roCurrentPoint);

//-------------- rendering support -------------------
	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics);
	virtual void render(cned_renderer_ & roRenderer);
	
	virtual void post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint);

	//-------------- element finders ------------------------
	virtual ned_ident find_element_from_point(const ng_point & roPoint);
	virtual ned_ident find_element_relative(const ng_rect & roRefRect,const ned_ident nIdStart,eRelativePosition eRP,long & rnBestDistance);

	virtual void remove_children(bool bWhileRemovingItself);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);

	//---- paint invalidating --------
	virtual void _invalidate_all_paint();

	SCP<cned_page_caption> _get_caption() const;
	SCP<cned_paragraph> _get_header() const;
	SCP<cned_paragraph> _get_footer() const;


	//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
	virtual void _screen2local(ng_point & roPoint) const;
	virtual void _local2screen(ng_point & roPoint) const;

	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);

protected:
	cned_page(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	void __construct_caption();
	void __construct_header();
	void __construct_footer();

	void _paint_shadows(cned_painter_ & roPainter,const ng_point & roCurrentPoint);
	void _paint_border(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _paint_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);

	void _paint_caption_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _paint_caption_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);

	//-------------- dimension helpers -------------------
	void _get_shadows_rects(const ng_point & roCurrentPoint,ng_rect & roRightShadowRect,ng_rect & roBottomShadowRect) const;
	void _get_child_rect(const ng_point & roCurrentPoint,ng_rect & roChildRect) const;
	bool _is_max_width_in_effect() const;
	bool _is_max_height_in_effect() const;

	//-------------- rendering helpers -------------------
	void _measure_body_min_width(const ned_measure_param & roMParam,
		ng_xdist & rdxMinWidth,ng_xdist & rdxMinWidthNoMargins);

	//-------------- 
	ned_ident _get_caption_ident() const;
	ned_ident _get_header_ident() const;
	ned_ident _get_footer_ident() const;
	//-------------- 

	ng_region	m_oWorkRgn;

	//------------ page specific attributes ----------------------------------
	CSmartOleVariant	m_oIdImageSourceSOV;
	SCP<ng_image>		m_poBackgroundImageSP;
	ng_rect				m_oExtPageMargins;
	epage_display_mode	m_ePDM;
	
	struct cnormalmode_info
	{
		ng_size m_oVectorSize;
	};

	cnormalmode_info	m_oNormalModeInfo;
	ng_rect				m_oChildRect;		//relative to page (internal cooordinates)
	ng_size				m_oFullVirtualSize; //full page size (virtual cause includes scrolledout area)

	ned_ident			m_idCaption;
	ned_ident			m_idHeader;
	ned_ident			m_idFooter;

	friend class cned_element_manager;

	static const long SHADOW1_PAINT_RECT_ID;
	static const long SHADOW2_PAINT_RECT_ID;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline void cned_page::get_metrics(const ned_measure_param & /*roMParam*/,cned_metrics & /*roMetrics*/)
{
	/*
		poniewa¿ strona zawsze le¿y w swojej warstwie (layer) to nie wp³ywa
		na metrics swojego kontenera

		strona jest measureowana na pocz¹tku renderowania
	*/
}

inline ned_ident cned_page::_get_caption_ident() const
{
	ASSERT(m_idCaption != NEDID_NOTHING);
	return m_idCaption;
}

inline ned_ident cned_page::_get_header_ident() const
{
	ASSERT(m_idHeader != NEDID_NOTHING);
	return m_idHeader;
}

inline ned_ident cned_page::_get_footer_ident() const
{
	ASSERT(m_idFooter != NEDID_NOTHING);
	return m_idFooter;
}

inline SCP<cned_page_caption> cned_page::_get_caption() const
{
	return scp_cast_ui<cned_page_caption>(get_element_on_ident(_get_caption_ident()));
}

inline SCP<cned_paragraph> cned_page::_get_header() const
{
	return scp_cast_ui<cned_paragraph>(get_element_on_ident(_get_header_ident()));
}

inline SCP<cned_paragraph> cned_page::_get_footer() const
{
	return scp_cast_ui<cned_paragraph>(get_element_on_ident(_get_footer_ident()));
}

inline void cned_page::post_render(cned_post_render_manager & roPostRender,const ng_point & /*roCurrentPoint*/)
{
	//m_oVectorSize - we wspó³rzêdnych areny a nie parenta !
	//dlatego ignorujemy roCurrentPoint
	if(roPostRender.test_element_remove(_get_caption_ident()))
	{
		ng_point oPagePoint;
		oPagePoint.offset(m_oVectorSize);
		_get_caption()->post_render(roPostRender,oPagePoint);
	}
	
	cned_group_helper__::post_render(roPostRender,ng_point());
}

//-------------- property get ---------------
inline const ng_rect & cned_page::get_prop_extmargins() const
{
	return m_oExtPageMargins;
}

inline const CSmartOleVariant & cned_page::get_prop_imagesrc() const
{
	return m_oIdImageSourceSOV;
}

inline void cned_page::get_prop_title(ng_string & roTitleString) const
{
	_get_caption()->get_prop_title(roTitleString);
}

inline epage_display_mode cned_page::get_prop_display_mode() const
{
	return m_ePDM;
}

//-------------- property set ---------------
inline void cned_page::set_prop_extmargins(const ng_rect & roMarginsRect)
{
	if(roMarginsRect == get_prop_extmargins())
	{
		return;
	}

	m_oExtPageMargins = roMarginsRect;

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_page::set_prop_imagesrc(const CSmartOleVariant & roImageSrcSOV)
{
	if(roImageSrcSOV == get_prop_imagesrc())
	{
		return;
	}
	m_oIdImageSourceSOV = roImageSrcSOV;
	m_poBackgroundImageSP = 0; //reset image

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_page::set_prop_title(const ng_string & roTitleString)
{
	_get_caption()->set_prop_title(roTitleString);
}

//--------------------------------------------------------
inline bool cned_page::_is_max_width_in_effect() const
{
	return
		(get_prop_display_mode() == pdm_maximized) || 
		((get_prop_display_mode() == pdm_normal) && is_maximal_width_value(get_prop_extwidth()));
}

inline bool cned_page::_is_max_height_in_effect() const
{
	return
		(get_prop_display_mode() == pdm_maximized) || 
		((get_prop_display_mode() == pdm_normal) && is_maximal_height_value(get_prop_extheight()));
}

//-------- page breaking ---------------------------------
inline void cned_page::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_group_helper__::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_page * poDestPage = cast_ui<cned_page>(poDestination);
	poDestPage->set_prop_imagesrc(get_prop_imagesrc());
}

inline void cned_page::_get_child_rect(const ng_point & roCurrentPoint,ng_rect & roChildRect) const
{
	roChildRect = m_oChildRect;
	roChildRect.offset(roCurrentPoint.distance(ng_point()));
}

//-----t³umaczenie wspó³rzêdnych (uwzglêdnia scroll)-----
inline void cned_page::_screen2local(ng_point & roPoint) const
{
	cned_group_helper__::_screen2local(roPoint);
	roPoint.offset(get_scroll_pos());
}

inline void cned_page::_local2screen(ng_point & roPoint) const
{
	cned_group_helper__::_local2screen(roPoint);
	roPoint.offset(-get_scroll_pos());
}

inline bool cned_page::quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance)
{
	//to jest potrzebne poniewaz m_oVectorSize w page jest relatywny do areny !!!
	ng_point oPoint;
	oPoint.offset(m_oVectorSize);
	_arena2local(oPoint);
	oPoint.offset(m_oVectorSize);	//teraz oPoint jest we wspó³rzêdnych kontenera

	return _quote_rect_distance(eRP,roRefRect,ng_rect(oPoint,m_oActualSize),rnDistance);
}

}

#else
	#error __FILE__ already included
#endif
