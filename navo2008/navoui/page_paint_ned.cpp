/*
	NAVO Enterprise 2003
	2003-03-27

	navo enhanced display (NED)

	page element

	paint related functionality
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long cned_page::SHADOW1_PAINT_RECT_ID = 1;
const long cned_page::SHADOW2_PAINT_RECT_ID = 2;

//------- paint support --------------------
void cned_page::prepare_paint_region(ng_region & roCommonRgn,const ng_point & roCurrentPoint)
{
	//1. zapamiêtaj region jeszcze bez nas - w tym obszarze wolno nam malowaæ
	m_oWorkRgn.from_region(roCommonRgn);

	//2. pomniejsz wspólny region o obszar odmalowywany ostatecznie przez nas
	//(np. jeœli jesteœmy (pó³) przezroczyœci, to nie jest to ostateczne odmalowanie)

	if(!roCommonRgn.is_empty())		//jeœli jest ju¿ pusty to nic nie robimy dalej
	{
		ng_area oOpaqueBackArea;
		get_opaque_background_area(roCurrentPoint,oOpaqueBackArea);
		
		if(!oOpaqueBackArea.is_empty())
		{
			ng_region oExcludeRgn;
			oExcludeRgn.from_area(oOpaqueBackArea);
			
			roCommonRgn.combine(roCommonRgn,oExcludeRgn,RGN_DIFF);
		}
	}
}

void cned_page::paint(cned_painter_ & roPainter,const ng_point & roCurrentPoint)
{
	if(m_oWorkRgn.is_empty())
	{
		return;
	}

	ng_point oPagePoint(roCurrentPoint);
	oPagePoint.offset(m_oVectorSize);

	//zastosuj zapamiêtany region
	roPainter.get_dc().set_clip_region(m_oWorkRgn,RGN_COPY);


	//maluj t³o
	cned_back_painter oBackPainter(roPainter);
	
	//w trybie podgl¹du zawsze z t³em
	cned_paint_param oBackgroundPP = roPainter.get_paint_param();
	if(roPainter.get_paint_param().get_paint_mode() == pm_printpreview)
	{
		oBackgroundPP.set_paint_background(true);
	}
	oBackPainter.set_paint_param(oBackgroundPP);

	draw_background(oBackPainter,oPagePoint);

	//zastosuj ponownie zapamiêtany region
	roPainter.get_dc().set_clip_region(m_oWorkRgn,RGN_COPY);
	//maluj foreground

	cned_fore_painter oForePainter(roPainter);
	draw_foreground(oForePainter,oPagePoint);

	//maluj cienie - to siê dzieje po namalowaniu foreground
	
	if(!_metrics().is_windows_look() && !_is_fast_graphics())
	{
		if(roPainter.get_paint_param().get_paint_mode() != pm_printer)
		{
			_paint_shadows(roPainter,oPagePoint);
		}
	}

	m_oWorkRgn.empty();
}

void cned_page::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	_paint_caption_foreground(roForePainter,roCurrentPoint);

	long nPrevTreeDisCnt;
	roForePainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	{
		SCP<cned_paragraph> poHeaderSP = _get_header();
		if(poHeaderSP->should_paint(roForePainter,roCurrentPoint) == spr_inside)
		{
			poHeaderSP->draw_foreground(roForePainter,roCurrentPoint);
		}
	}

	{	
		ng_rect oChildRect;
		_get_child_rect(roCurrentPoint,oChildRect);
		cned_scroll_clipper oScrollClipper(roForePainter,oChildRect);
		
		ng_point oChildrenPoint(roCurrentPoint);
		if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
		{
			oChildrenPoint.offset(-get_scroll_pos());
		}
		
		_draw_foreground_children(roForePainter,oChildrenPoint);
	}

	{
		SCP<cned_paragraph> poFooterSP = _get_footer();
		if(poFooterSP->should_paint(roForePainter,roCurrentPoint) == spr_inside)
		{
			poFooterSP->draw_foreground(roForePainter,roCurrentPoint);
		}
	}

	roForePainter.restore_disabled(nPrevTreeDisCnt);

	if(roForePainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		_scroll_draw_foreground(roForePainter,roCurrentPoint);
		_paint_border(roForePainter,roCurrentPoint);
	}
}

void cned_page::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	_paint_background(roBackPainter,roCurrentPoint);

	if(roBackPainter.get_paint_param().get_paint_mode() != pm_printpreview)
	{
		_paint_caption_background(roBackPainter,roCurrentPoint);
	}

	long nPrevTreeDisCnt;
	roBackPainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	{
		SCP<cned_paragraph> poHeaderSP = _get_header();
		if(poHeaderSP->should_paint(roBackPainter,roCurrentPoint) == spr_inside)
		{
			poHeaderSP->draw_background(roBackPainter,roCurrentPoint);
		}
	}

	{	
		ng_rect oChildRect;
		_get_child_rect(roCurrentPoint,oChildRect);
		cned_scroll_clipper oScrollClipper(roBackPainter,oChildRect);
		
		ng_point oChildrenPoint(roCurrentPoint);
		if(roBackPainter.get_paint_param().get_paint_mode() != pm_printer)
		{
			oChildrenPoint.offset(-get_scroll_pos());
		}
		
		_draw_background_children(roBackPainter,oChildrenPoint);
	}

	{
		SCP<cned_paragraph> poFooterSP = _get_footer();
		if(poFooterSP->should_paint(roBackPainter,roCurrentPoint) == spr_inside)
		{
			poFooterSP->draw_background(roBackPainter,roCurrentPoint);
		}
	}
	
	roBackPainter.restore_disabled(nPrevTreeDisCnt);

	if(roBackPainter.get_paint_param().get_paint_mode() != pm_printer)
	{
		_scroll_draw_background(roBackPainter,roCurrentPoint);
	}

	_store_main_paint_rect(ng_rect(roCurrentPoint,m_oActualSize));
}

//--------------------------------------------------------------------------------------
// caption painting
//--------------------------------------------------------------------------------------

void cned_page::_paint_caption_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	if(!get_prop_caption())
	{
		return;
	}

	if(roForePainter.get_paint_param().get_paint_mode() == pm_printer)
	{
		return;
	}
	if(roForePainter.get_paint_param().get_paint_mode() == pm_printpreview)
	{
		return;
	}

	SCP<cned_page_caption> poCaptionSP = _get_caption();
	if(poCaptionSP->should_paint(roForePainter,roCurrentPoint) == spr_inside)
	{
		poCaptionSP->draw_foreground(roForePainter,roCurrentPoint);
	}
}

void cned_page::_paint_caption_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	if(!get_prop_caption())
	{
		return;
	}
	if(roBackPainter.get_paint_param().get_paint_mode() == pm_printer)
	{
		return;
	}

	//caption has artifically constructed paint parameters
	//in print-preview mode
	cned_paint_param oSavePP = roBackPainter.get_paint_param();
	
	if(roBackPainter.get_paint_param().get_paint_mode() == pm_printpreview)
	{
		cned_paint_param oCaptionPP = oSavePP;
		oCaptionPP.set_color_translation(ct_none);
		oCaptionPP.set_paint_background(true);
		roBackPainter.set_paint_param(oCaptionPP);
	}

	SCP<cned_page_caption> poCaptionSP = _get_caption();
	if(poCaptionSP->should_paint(roBackPainter,roCurrentPoint) == spr_inside)
	{
		poCaptionSP->draw_background(roBackPainter,roCurrentPoint);
	}

	roBackPainter.set_paint_param(oSavePP);
}

//---- paint invalidating --------
void cned_page::_invalidate_all_paint()
{
	if(m_idCaption != NEDID_NOTHING)	//bo mo¿e byæ JU¯ usuniêty
	{
		_get_caption()->invalidate_caption_paint();
	}
	cned_group_helper__::_invalidate_all_paint();
	get_manager()->invalidate_paint_rect(get_ident(),SHADOW1_PAINT_RECT_ID);
	get_manager()->invalidate_paint_rect(get_ident(),SHADOW2_PAINT_RECT_ID);
}

void cned_page::_paint_shadows(cned_painter_ & roPainter,const ng_point & roCurrentPoint)
{
	bool bRightShadow = !_is_max_width_in_effect();
	bool bBottomShadow = !_is_max_height_in_effect();
	
	if(!bRightShadow && !bBottomShadow)
	{
		return;
	}

	//construct area
	ng_rect oRightShadowRect;
	ng_rect oBottomShadowRect;
	_get_shadows_rects(roCurrentPoint,oRightShadowRect,oBottomShadowRect);
		
	ng_area oShadowAreaDU;
	if(bRightShadow)
	{
		oShadowAreaDU += oRightShadowRect;
	}
	if(bBottomShadow)
	{
		oShadowAreaDU += oBottomShadowRect;
	}

	//translate area
	ng_size oFinalScrollSize; //ned_to_do: = __get_efective_scroll_stack(false);
	oShadowAreaDU.offset(oFinalScrollSize);

	ng_region oShadowRegion;
	oShadowRegion.from_area(oShadowAreaDU);

	ng_region oClipRegion;
	oClipRegion.from_clip_region(roPainter.get_dc());

	oShadowRegion.combine(oShadowRegion,oClipRegion,RGN_AND);
	
	//offset shadow region back
	oShadowRegion.offset(-oFinalScrollSize.get_dx(),-oFinalScrollSize.get_dy());
	//set clip
	roPainter.get_dc().set_clip_region(oShadowRegion,RGN_OR);

	//ned_to_do: gradient cienia
	//problem jest z obszarem 'rogu' który powinien byæ rozjaniany, 
	//a obecna implementacja zaciemiania - byæ mo¿e rozwi¹zaniem bêdzie gradient diagonalny ?
	ng_color oShadowColor = _metrics().page().get_shadow_color();

	if(bRightShadow)
	{
		roPainter.get_dc().fill_rect_hg(oRightShadowRect,oShadowColor,oShadowColor);
		_store_extra_paint_rect(SHADOW1_PAINT_RECT_ID,oRightShadowRect);
	}
	if(bBottomShadow)
	{
		roPainter.get_dc().fill_rect_vg(oBottomShadowRect,oShadowColor,oShadowColor);
		_store_extra_paint_rect(SHADOW2_PAINT_RECT_ID,oBottomShadowRect);
	}

}

void cned_page::_paint_border(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_rect oBorderRect(roCurrentPoint,m_oActualSize);

	if(roForePainter.in_clip_region(oBorderRect))
	{
		bool bMaxWidth = _is_max_width_in_effect();
		bool bMaxHeight = _is_max_height_in_effect();

		const long nFrameElements = (bMaxWidth ? 0 : (NG_FRAME_LEFT | NG_FRAME_RIGHT)) | 
			(bMaxHeight ? 0 : (NG_FRAME_TOP | NG_FRAME_BOTTOM));
		
		roForePainter.frame_rect(oBorderRect,_metrics().page().get_border_width(),
			ng_color::system(COLOR_ACTIVEBORDER),nFrameElements | NG_FRAME_EDGE_RAISED);
	}
}

//---------------------------------- wsparcie dla obrazka t³a ---------------------------------------

class cned_page_image_reguest : public ng_image_request
{
public:
	cned_page_image_reguest(SCP<cned_page> poPageSP):
		m_poPageSP(poPageSP)
	{
		ASSERT(poPageSP.PointsObject());
	}
	virtual void on_image_ready(bool bPositive)
	{
		//ned_to_do:.. notify
	}
private:
	SCP<cned_page> m_poPageSP;
};

void cned_page::_paint_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_rect oBackRect(roCurrentPoint,m_oActualSize);

	_draw_std_background(roBackPainter,oBackRect);

	if(m_oIdImageSourceSOV.Type() != VT_EMPTY)
	{
		if(m_poBackgroundImageSP.PointsNull())
		{
			m_poBackgroundImageSP = get_manager()->get_image(m_oIdImageSourceSOV,
				NewSCP(new cned_page_image_reguest(NewSCP(this,true))));
		}
	}
	if(m_poBackgroundImageSP.PointsObject())
	{
		ng_rect oChildRect;
		_get_child_rect(roCurrentPoint,oChildRect);
		ng_size oScrollSize;
		
		//ned_to_do: roboczo na razie - jest b³êdny wymiar rysunku (za ma³a wysokoœc)

		if(_is_vert_bar())
		{
			oChildRect.set_height(get_scroll_total_range().get_dy());
			oScrollSize.set_dy(get_scroll_pos().get_dy());
		}
		roBackPainter.get_dc().draw_image(oChildRect,
			oScrollSize,m_poBackgroundImageSP,ngis_stretch,ngif_col2tran);
	}

	if(roBackPainter.get_paint_param().get_paint_mode() == pm_printpreview)
	{
		//w trybie podgl¹du zawsze pokazuj marginesy
		cned_paint_param oSavePP = roBackPainter.get_paint_param();
		cned_paint_param oMarginsPP = oSavePP;
		oMarginsPP.set_color_translation(ct_none);
		oMarginsPP.set_paint_background(true);
		roBackPainter.set_paint_param(oMarginsPP);

		ng_color oMarginColor(234,234,234,0);

		ng_xdist dxLeftMargin	= get_manager()->to_internal(ng_size(get_prop_extmargins().get_left(),0)).get_dx();
		ng_ydist dyTopMargin	= get_manager()->to_internal(ng_size(0,get_prop_extmargins().get_top())).get_dy();
		ng_xdist dxRightMargin  = get_manager()->to_internal(ng_size(get_prop_extmargins().get_right(),0)).get_dx();
		ng_ydist dyBottomMargin = get_manager()->to_internal(ng_size(0,get_prop_extmargins().get_bottom())).get_dy();

		ng_rect oMarginRect(roCurrentPoint,m_oActualSize);
		oMarginRect.set_width(dxLeftMargin);
		roBackPainter.fill_rect_hg(oMarginRect,oMarginColor,oMarginColor);
		
		oMarginRect = ng_rect(roCurrentPoint,m_oActualSize);
		oMarginRect.set_left(oMarginRect.get_right() - dxRightMargin);
		roBackPainter.fill_rect_hg(oMarginRect,oMarginColor,oMarginColor);
		
		oMarginRect = ng_rect(roCurrentPoint,m_oActualSize);
		oMarginRect.set_height(dyTopMargin);
		roBackPainter.fill_rect_hg(oMarginRect,oMarginColor,oMarginColor);

		oMarginRect = ng_rect(roCurrentPoint,m_oFullVirtualSize);
		
		if(_is_vert_bar())
		{
			oMarginRect.offset(-get_scroll_pos());
		}

		oMarginRect.set_top(oMarginRect.get_bottom() - dyBottomMargin);
	
		roBackPainter.fill_rect_hg(oMarginRect,oMarginColor,oMarginColor);

		roBackPainter.set_paint_param(oSavePP);
	}
}

