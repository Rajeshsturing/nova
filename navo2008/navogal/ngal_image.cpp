/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions
	image 
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"


//-- this function must be before DEBUG_NEW due different allocation mechanism and syntax in GDI+

static Bitmap * new_Bitmap_32bpp(long nWidth,long nHeight)
{
	return new Bitmap(nWidth,nHeight,PixelFormat32bppARGB);
}


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//------------------------------------------------------ image -----------------------

ng_image_impl::ng_image_impl() :
	m_poNormalCB(NULL),
	m_poDisabledCB(NULL),
	m_poSemiTransCB(NULL),
	m_pImagePlus(NULL)
{
//	TRACE("ctor ng_image_impl %x\n",long(this));
}

ng_image_impl::~ng_image_impl()
{

	delete m_poSemiTransCB;
	delete m_poNormalCB;
	delete m_poDisabledCB;
	delete m_pImagePlus;

//	TRACE("dtor ng_image_impl %x\n",long(this));
}

void ng_image_impl::read_from_file(LPCTSTR lpFileName)
{
	m_pImagePlus = ng_ImagePlus::FromFile(lpFileName);
	if(m_pImagePlus != NULL)
	{
		if(m_pImagePlus->is_valid())
		{
			return;
		}
		m_pImagePlus = NULL;
	}
	ThrowNavoException1(ERCO_IMAGE_NOT_AVAILABLE,IDPAGE_NOTAVAILABLE,lpFileName);
}

void ng_image_impl::read_from_stream(SCP<IStream> poStreamSP)
{
	m_pImagePlus = ng_ImagePlus::FromStream(poStreamSP);
	if(m_pImagePlus != NULL)
	{
		if(m_pImagePlus->is_valid())
		{
			return;
		}
		m_pImagePlus = NULL;
	}
	ThrowNavoException1(ERCO_IMAGE_NOT_AVAILABLE,IDPAGE_NOTAVAILABLE,"<stream>");
}

void ng_image_impl::read_from_resource(HINSTANCE hInstance,LPCTSTR lpName)
{
	m_pImagePlus = ng_ImagePlus::FromResource(hInstance,lpName);
	if(m_pImagePlus != NULL)
	{
		if(m_pImagePlus->is_valid())
		{
			return;
		}
		m_pImagePlus = NULL;
	}
	ThrowNavoException1(ERCO_IMAGE_NOT_AVAILABLE,IDPAGE_NOTAVAILABLE,lpName);
}

void ng_image_impl::read_from_resource(HINSTANCE hInstance,long nResId)
{
	m_pImagePlus = ng_ImagePlus::FromResource(hInstance,nResId);
	if(m_pImagePlus != NULL)
	{
		if(m_pImagePlus->is_valid())
		{
			return;
		}
		m_pImagePlus = NULL;
	}
	ThrowNavoException1(ERCO_IMAGE_NOT_AVAILABLE,IDPAGE_NOTAVAILABLE,Long2String(nResId));
}

ng_xdist ng_image_impl::get_width() const
{
	ASSERT(m_pImagePlus);
	return (ng_xdist) m_pImagePlus->GetWidth();
}

ng_ydist ng_image_impl::get_height() const
{
	ASSERT(m_pImagePlus);
	return (ng_ydist) m_pImagePlus->GetHeight();
}
	
long ng_image_impl::get_frame_count() const
{
	ASSERT(m_pImagePlus);
	return (long) m_pImagePlus->GetFrameCount(&FrameDimensionTime);
}

Bitmap * ng_image_impl::_create_image_copy()
{
	ASSERT(m_pImagePlus);
	//create bitmap for copy
	Bitmap * poBitmap = new_Bitmap_32bpp(m_pImagePlus->GetWidth(),m_pImagePlus->GetHeight());
	ASSERT(poBitmap);
	Graphics oBitmapGraphics(poBitmap);	
	Rect oRectPlus(0,0,m_pImagePlus->GetWidth(),m_pImagePlus->GetHeight());
	//make copy
	oBitmapGraphics.DrawImage(m_pImagePlus,oRectPlus);
	return poBitmap;
}

class ng_bitmap_filter
{
public:
	ng_bitmap_filter(Bitmap * poBitmap) :
		m_pBitmap(poBitmap)
	{
		ASSERT(poBitmap);
		Rect oRect(0,0,poBitmap->GetWidth(),poBitmap->GetHeight());
		VERIFY(Ok==poBitmap->LockBits(&oRect,ImageLockModeWrite,PixelFormat32bppARGB,&m_oBitmapData));
	}
	~ng_bitmap_filter()
	{
		VERIFY(Ok==m_pBitmap->UnlockBits(&m_oBitmapData));
	}
	void _make_standard();
	void _make_disabled();
	void _make_semitransparent();
private:
	Bitmap * m_pBitmap;
	BitmapData m_oBitmapData;
};

const UINT _n_TransparentColor = 0xFFFF00FF;

void ng_bitmap_filter::_make_standard()
{
	UINT* pixels = (UINT*)m_oBitmapData.Scan0;
	for(UINT row = 0; row < m_oBitmapData.Height; ++row)
	{
		for(UINT col = 0; col < m_oBitmapData.Width; ++col)
		{
			UINT *pPixel = pixels + row * m_oBitmapData.Stride / sizeof(UINT) + col;
			if(*pPixel == _n_TransparentColor)		//zamieniamy nasz umowny kolor na full alphê
			{
				*pPixel = 0;
			}
		}
	}
}

void ng_bitmap_filter::_make_semitransparent()
{
	UINT* pixels = (UINT*)m_oBitmapData.Scan0;
	for(UINT row = 0; row < m_oBitmapData.Height; ++row)
	{
		for(UINT col = 0; col < m_oBitmapData.Width; ++col)
		{
			UINT *pPixel = pixels + row * m_oBitmapData.Stride / sizeof(UINT) + col;
			*pPixel = (*pPixel & 0x00FFFFFF) | 0xC0000000;
		}
	}
}

void ng_bitmap_filter::_make_disabled()
{
	UINT* pixels = (UINT*)m_oBitmapData.Scan0;
	for(UINT row = 0; row < m_oBitmapData.Height; ++row)
	{
		for(UINT col = 0; col < m_oBitmapData.Width; ++col)
		{
			UINT *pPixel = pixels + row * m_oBitmapData.Stride / sizeof(UINT) + col;
			if(*pPixel == _n_TransparentColor)		//zamieniamy nasz umowny kolor na full alphê
			{
				*pPixel = 0;
			}
			else
			{
				//filtr wyszarzaj¹cy 
				DWORD dwIntensity = ((BYTE(*pPixel & 0x000000FF) + BYTE((*pPixel & 0x0000FF00) >> 8) + BYTE((*pPixel & 0x00FF0000) >> 16)) / 3);
				BYTE byIntensity = BYTE(dwIntensity);
				*pPixel = (*pPixel & 0x7F000000) + byIntensity + (UINT(byIntensity) << 8) + (UINT(byIntensity) << 16);
				/*
				//filtr os³abiaj¹cy kolor 
					*pPixel = 
				((((*pPixel & 0x000000FF) >> 1) | ((*pPixel & 0x000000FF) >> 2)) & 0x000000FF) |	//0.75 B
				((((*pPixel & 0x0000FF00) >> 1) | ((*pPixel & 0x0000FF00) >> 2)) & 0x0000FF00) |	//0.75 G
				((((*pPixel & 0x00FF0000) >> 1) | ((*pPixel & 0x00FF0000) >> 2)) & 0x00FF0000) |	//0.75 R
				 (((*pPixel & 0xFF000000) >> 1) & 0xFF000000);										//1.00 alpha
				 */
			}
		}
	}
}

Bitmap * ng_image_impl::_plus_convert_2_normal()
{
	Bitmap * poNormalBitmap = _create_image_copy();
	ASSERT(poNormalBitmap);
	ng_bitmap_filter oFilter(poNormalBitmap);
	oFilter._make_standard();

	ASSERT(poNormalBitmap);
	return poNormalBitmap;
}

Bitmap * ng_image_impl::_plus_convert_2_disabled()
{
	Bitmap * poDisabledBitmap = _create_image_copy();
	ASSERT(poDisabledBitmap );
	ng_bitmap_filter oFilter(poDisabledBitmap);
	oFilter._make_disabled();

	ASSERT(poDisabledBitmap );
	return poDisabledBitmap ;
}

Bitmap * ng_image_impl::_plus_convert_2_semitrans()
{
	Bitmap * poSemiTransBitmap = _create_image_copy();
	ASSERT(poSemiTransBitmap);
	ng_bitmap_filter oFilter(poSemiTransBitmap);
	oFilter._make_semitransparent();

	ASSERT(poSemiTransBitmap);
	return poSemiTransBitmap;
}

Image * ng_image_impl::get_semitrans()
{
	if(m_poSemiTransCB != NULL)
	{
		return m_poSemiTransCB;
	}
	m_poSemiTransCB = _plus_convert_2_semitrans();
	return m_poSemiTransCB;
}

Image * ng_image_impl::get_normal()
{
	if(m_poNormalCB != NULL)
	{
		return m_poNormalCB;
	}
	m_poNormalCB = _plus_convert_2_normal();
	return m_poNormalCB;
}

Image * ng_image_impl::get_disabled()
{
	if(m_poDisabledCB != NULL)
	{
		return m_poDisabledCB;
	}
	m_poDisabledCB = _plus_convert_2_disabled();
	return m_poDisabledCB;
}

//------------ dc impl ----------------------------------------------------------
void ng_dc_impl::draw_image(const ng_rect & roDURect,const ng_size & roDUScroll,ng_image_impl * poImageImpl,
	ng_image_scaling_mode eScalingMode,ng_image_filter eFilters)
{
	//select image variant
	ASSERT(poImageImpl);
	Image * poImage2Draw = NULL;
	switch(eFilters)
	{
	case ngif_none:
		poImage2Draw = poImageImpl->_plus_original();
	break;
	case ngif_col2tran:
		poImage2Draw = poImageImpl->get_normal();
	break;
	case ngif_disable:
		poImage2Draw = poImageImpl->get_disabled();
	break;
	case ngif_semitrans:
		poImage2Draw = poImageImpl->get_semitrans();
	break;
	default:
		ASSERT(false);
	}
	ASSERT(poImage2Draw);

	//compute destination rectangle
	ng_rect oDURect(roDURect);
	oDURect.offset(-get_x_window_org(),-get_y_window_org());

	UINT nHeight;
	UINT nWidth;
	switch(eScalingMode)
	{
	case ngis_original:
	{
		nWidth = poImage2Draw->GetWidth();
		nHeight = poImage2Draw->GetHeight();
		oDURect.set_width(nWidth);
		oDURect.set_height(nHeight);
	}
	break;
	case ngis_clip:
	{
		nWidth = min(UINT(oDURect.get_width()),poImage2Draw->GetWidth());
		nHeight = min(UINT(oDURect.get_height()),poImage2Draw->GetHeight());
	}
	break;
	case ngis_stretch:
		nWidth = poImage2Draw->GetWidth();
		nHeight = poImage2Draw->GetHeight();
	break;
	default:
		ASSERT(false);
		return;	//nic nie malujemy
	}

	Gdiplus::Rect oPlusRect;
	rect2PlusRect(oDURect,oPlusRect);

	//draw
	ng_Graphics_holder oGH(get_hdc());
	oGH.getplus().DrawImage(poImage2Draw,oPlusRect,roDUScroll.get_dx(),roDUScroll.get_dy(),
		nWidth,nHeight,UnitPixel,NULL);
	ASSERT(oGH.getplus().GetLastStatus() == Ok);
}

void ng_dc_impl::draw_image_frame(const ng_rect & roDURect,ng_image_impl * poImageImpl,
	ng_image_scaling_mode eScalingMode,long nFrame)
{
	//select image frame
	ASSERT(poImageImpl);
	Image * poImage2Draw = poImageImpl->_plus_original();
	ASSERT(poImage2Draw != NULL);
	poImage2Draw->SelectActiveFrame(&FrameDimensionTime,UINT(nFrame));

	//compute destination rectangle
	ng_rect oDURect(roDURect);
	oDURect.offset(-get_x_window_org(),-get_y_window_org());

	switch(eScalingMode)
	{
	case ngis_original:
	{
		ng_size oDUSize = ng_size(poImage2Draw->GetWidth(),poImage2Draw->GetHeight());
		oDURect = ng_rect(oDURect.get_topleft(),oDUSize);
	}
	break;
	case ngis_stretch:
	break;
	default:
		ASSERT(false);
	}

	Gdiplus::Rect oPlusRect;
	rect2PlusRect(oDURect,oPlusRect);

	//draw
	ng_Graphics_holder oGH(get_hdc());
	oGH.getplus().DrawImage(poImage2Draw,oPlusRect,
		0,0,poImage2Draw->GetWidth(),poImage2Draw->GetHeight(),UnitPixel,NULL);
	ASSERT(oGH.getplus().GetLastStatus() == Ok);
}

