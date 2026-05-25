/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool _g_b_FastGraphics = false;

bool _is_fast_graphics()
{
	return _g_b_FastGraphics;
}

void _set_fast_graphics(bool bFast)
{
	_g_b_FastGraphics = bFast;
}

//-------------- forwarders from interface ------------------------------------
ng_session::ng_session()
{
	m_poSessionImpl = new ng_session_impl();
}

ng_session::~ng_session()
{
	delete m_poSessionImpl;
}

void ng_session::init()
{
	ASSERT(m_poSessionImpl);
	m_poSessionImpl->init();
}

void ng_session::done()
{
	ASSERT(m_poSessionImpl);
	m_poSessionImpl->done();
}

ng_ic::ng_ic(HDC hDC)
{
	m_poDCImpl = new ng_dc_impl(hDC);
}

ng_ic::ng_ic() :
	m_poDCImpl(NULL)
{
}

ng_ic::~ng_ic()
{
	delete m_poDCImpl;
}

void ng_ic::attach(ng_dc_impl * poDCImpl)
{
	ASSERT(m_poDCImpl == NULL);
	m_poDCImpl = poDCImpl;
}

void ng_ic::detach()
{
	ASSERT(m_poDCImpl != NULL);
	m_poDCImpl = NULL;
}

void ng_ic::reinit()
{
	ASSERT(m_poDCImpl);
	m_poDCImpl->reinit();
}

ng_size ng_ic::measure_string(LPCTSTR lpText,long nCount,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings)
{
	ASSERT(m_poDCImpl);
	return m_poDCImpl->measure_string(lpText,nCount,nXAreaWidth,rpoNGFontSP,pMaxChars,pArrayOfPartialStrings);
}

HDC ng_ic::get_hdc() const
{
	ASSERT(m_poDCImpl);
	return m_poDCImpl->get_hdc();
}

//-------------------------------------------------------

ng_dc::ng_dc(HDC hDC) :
	ng_ic(hDC)
{
}

ng_dc::ng_dc() :
	ng_ic()
{
}

ng_dc::~ng_dc()
{
}

void ng_dc::fill_rect_hg(const ng_rect & roLURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const
{
	if(roBkColor1 == Transparent && roBkColor2 == Transparent)
	{
		return;
	}
#ifdef _DEBUG
	(const_cast<ng_dc*>(this))->m_nFillRectCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->fill_rect_hg(roLURect,roBkColor1,roBkColor2);
}

void ng_dc::fill_rect_vg(const ng_rect & roLURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const
{
	if(roBkColor1 == Transparent && roBkColor2 == Transparent)
	{
		return;
	}
#ifdef _DEBUG
	(const_cast<ng_dc*>(this))->m_nFillRectCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->fill_rect_vg(roLURect,roBkColor1,roBkColor2);
}

void ng_dc::frame_rect(const ng_rect & roLURect,long nFrameWidthPx,const ng_color & framecolor,long nMask)
{
#ifdef _DEBUG
	m_nFrameRectCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->frame_rect(roLURect,nFrameWidthPx,framecolor,nMask);
}

void ng_dc::frame_area(const ng_area & roLUArea,long nFrameWidthPx,const ng_color & framecolor)
{
#ifdef _DEBUG
	m_nFrameAreaCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->frame_area(roLUArea,nFrameWidthPx,framecolor);
}

void ng_dc::patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP)
{
#ifdef _DEBUG
	m_nPatBltCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->patblt(roDURect,roColor,dwROP);
}

void ng_dc::bitblt(const ng_point & roDestPoint,const ng_size & roSize,const ng_point & roSrcPoint,DWORD dwROP)
{
#ifdef _DEBUG
	m_nBitBltCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->bitblt(roDestPoint,roSize,roSrcPoint,dwROP);
}

void ng_dc::print_text(const ng_rect & roLURect,LPCTSTR lpText,long nCount,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const
{
#ifdef _DEBUG
	(const_cast<ng_dc*>(this))->m_nPrintTextCalls++;
#endif
	ASSERT(m_poDCImpl);
	if(nCount > 0)
	{
		m_poDCImpl->print_text(roLURect,lpText,nCount,forecolor,rpoNGFontSP);
	}
}

void ng_dc::draw_image(const ng_rect & roLURect,const ng_size & roDUScroll,SCP<ng_image> poImageSP,
		ng_image_scaling_mode eScalingMode,ng_image_filter eFilters)
{
#ifdef _DEBUG
	m_nDrawImageCalls++;
#endif
	ASSERT(poImageSP.PointsObject());
	ASSERT(m_poDCImpl);
	m_poDCImpl->draw_image(roLURect,roDUScroll,poImageSP->m_poImageImpl,eScalingMode,eFilters);
}

void ng_dc::draw_image_frame(const ng_rect & roLURect,SCP<ng_image> poImageSP,ng_image_scaling_mode eScalingMode,long nFrame)
{
#ifdef _DEBUG
	m_nDrawImageCalls++;
#endif
	ASSERT(poImageSP.PointsObject());
	ASSERT(m_poDCImpl);
	m_poDCImpl->draw_image_frame(roLURect,poImageSP->m_poImageImpl,eScalingMode,nFrame);
}

void ng_dc::set_clip_region(const ng_region & roRegion,int nMode)
{
#ifdef _DEBUG
	m_nSetClipRegionCalls++;
#endif
	ASSERT(m_poDCImpl);
	m_poDCImpl->set_clip_region(*roRegion.m_poRegionImpl,nMode);
}

bool ng_dc::in_clip_region(const ng_area & roArea) const
{
#ifdef _DEBUG
	(const_cast<ng_dc*>(this))->m_nInClipRegionCalls++;
#endif
	ASSERT(m_poDCImpl);
	return m_poDCImpl->in_clip_region(roArea);
}

bool ng_dc::in_clip_region(const ng_rect & roRect) const
{
#ifdef _DEBUG
	(const_cast<ng_dc*>(this))->m_nInClipRegionCalls++;
#endif
	ASSERT(m_poDCImpl);
	return m_poDCImpl->in_clip_region(roRect);
}

ng_double_buffer::ng_double_buffer(ng_dc & roDC,const ng_rect & roLURect)
{
	m_poDBImpl = new ng_double_buffer_impl(*roDC.m_poDCImpl,roLURect);
	m_oDC.attach(m_poDBImpl->get_memdc());
}

ng_double_buffer::~ng_double_buffer()
{
	m_oDC.detach();
	delete m_poDBImpl;
}

void ng_double_buffer::copy_from(ng_dc & roSrcDC,const ng_point & roLeftUpperPoint)
{
	ASSERT(m_poDBImpl);
	m_poDBImpl->copy_from(*roSrcDC.m_poDCImpl,roLeftUpperPoint);
}

void ng_double_buffer::copy_to(ng_dc & roDestDC,const ng_point & roLeftUpperPoint)
{
	ASSERT(m_poDBImpl);
	m_poDBImpl->copy_to(*roDestDC.m_poDCImpl,roLeftUpperPoint);
}

ng_region::ng_region()
{
	m_poRegionImpl = new ng_region_impl();
}

ng_region::ng_region(const ng_rect & roRect)
{
	m_poRegionImpl = new ng_region_impl();
	from_rect(roRect);
}

ng_region::~ng_region()
{
	delete m_poRegionImpl;
}

void ng_region::from_area(const ng_area & roDUArea)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->from_area(roDUArea);
}

void ng_region::from_rect(const ng_rect & roDURect)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->from_rect(roDURect);
}

void ng_region::invalidate(HWND hWnd)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->invalidate(hWnd);
}

void ng_region::from_region(const ng_region & roDURgn)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->from_region(*roDURgn.m_poRegionImpl);
}

bool ng_region::is_empty() const
{
	ASSERT(m_poRegionImpl);
	return m_poRegionImpl->is_empty();
}

void ng_region::combine(ng_region & roNAVORegion1,ng_region & roNAVORegion2,int nMode)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->combine(*roNAVORegion1.m_poRegionImpl,*roNAVORegion2.m_poRegionImpl,nMode);
}

void ng_region::empty()
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->empty();
}

void ng_region::offset(ng_xdist xOffset,ng_ydist yOffset)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->offset(xOffset,yOffset);
}

void ng_region::from_clip_region(ng_ic & roDC)
{
	ASSERT(m_poRegionImpl);
	m_poRegionImpl->from_clip_region(*roDC.m_poDCImpl);
}

//----------------------------------------------------------------
SCP<ng_image> ng_image::from_file(LPCTSTR lpFileName)
{
	SCP<ng_image> poImageSP = NewSCP(new ng_image());
	poImageSP->read_from_file(lpFileName);
	return poImageSP;
}

SCP<ng_image> ng_image::from_stream(SCP<IStream> poStreamSP)
{
	SCP<ng_image> poImageSP = NewSCP(new ng_image());
	poImageSP->read_from_stream(poStreamSP);
	return poImageSP;
}

SCP<ng_image> ng_image::from_resource(HINSTANCE hInstance,LPCTSTR lpName)
{
	SCP<ng_image> poImageSP = NewSCP(new ng_image());
	poImageSP->read_from_resource(hInstance,lpName);
	return poImageSP;
}

SCP<ng_image> ng_image::from_resource(HINSTANCE hInstance,long nResId)
{
	SCP<ng_image> poImageSP = NewSCP(new ng_image());
	poImageSP->read_from_resource(hInstance,nResId);
	return poImageSP;
}


ng_image::ng_image()
{
	m_poImageImpl = new ng_image_impl();
}

ng_image::~ng_image()
{
	delete m_poImageImpl;
}

void ng_image::read_from_file(LPCTSTR lpFileName)
{
	ASSERT(m_poImageImpl);
	m_poImageImpl->read_from_file(lpFileName);
}

void ng_image::read_from_stream(SCP<IStream> poStreamSP)
{
	ASSERT(m_poImageImpl);
	m_poImageImpl->read_from_stream(poStreamSP);
}

void ng_image::read_from_resource(HINSTANCE hInstance,LPCTSTR lpName)
{
	ASSERT(m_poImageImpl);
	m_poImageImpl->read_from_resource(hInstance,lpName);
}

void ng_image::read_from_resource(HINSTANCE hInstance,long nResId)
{
	ASSERT(m_poImageImpl);
	m_poImageImpl->read_from_resource(hInstance,nResId);
}


ng_xdist ng_image::get_width() const
{
	ASSERT(m_poImageImpl);
	return m_poImageImpl->get_width();
}

ng_ydist ng_image::get_height() const
{
	ASSERT(m_poImageImpl);
	return m_poImageImpl->get_height();
}

long ng_image::get_frame_count() const
{
	ASSERT(m_poImageImpl);
	return m_poImageImpl->get_frame_count();
}
//----------------------------------------------------------------

ng_session_impl::ng_session_impl():
	m_gdiplusToken(NULL)
{
}

ng_session_impl::~ng_session_impl()
{
	done();
}

void ng_session_impl::init()
{
	VERIFY(GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL) == Ok);
}

void ng_session_impl::done()
{
	if(m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
}

void ng_dc_impl::__setup()
{
	ASSERT(get_hdc() != HDC(NULL));
	
	::SetMapMode(get_hdc(),MM_ISOTROPIC);
	VERIFY(::SetWindowExtEx(get_hdc(),100,100,NULL));
	VERIFY(::SetViewportExtEx(get_hdc(),100,100,NULL));
	VERIFY(::SetWindowOrgEx(get_hdc(),0,0,NULL));
	VERIFY(::SetViewportOrgEx(get_hdc(),0,0,NULL));
	::SetBkMode(get_hdc(),TRANSPARENT);

}



