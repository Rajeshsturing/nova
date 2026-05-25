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

void ng_dc_impl::__fill_rect_hvg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2,bool bVerticalGradient) const
{
	if(!_is_fast_graphics() && (roBkColor1 != roBkColor2 || roBkColor1._alpha() != 0))
	{
		ng_Graphics_holder oGH(get_hdc());
		
		//OS_API_CALL
		Gdiplus::Rect oPlusRect;
		ng_rect oDURect = roDURect;
		oDURect.offset(-get_x_window_org(),-get_y_window_org());
		rect2PlusRect(oDURect,oPlusRect);
		Gdiplus::Color oBkColorPlus1 = ColorPlus(roBkColor1);
		if(roBkColor1 != roBkColor2)
		{
			Gdiplus::Color oBkColorPlus2 = ColorPlus(roBkColor2);
			Gdiplus::Point oPT1;
			oPT1.X = oDURect.get_left();
			oPT1.Y = oDURect.get_top();

			Point oPT2;
			if(bVerticalGradient)
			{
				oPT2.X = oDURect.get_left();
				oPT2.Y = oDURect.get_bottom();
			}
			else
			{
				oPT1.X--;
				oPT2.X = oDURect.get_right();
				oPT2.Y = oDURect.get_top();
			}
			LinearGradientBrush oLinearGradientBrush(oPT1,oPT2,oBkColorPlus1,oBkColorPlus2);
			oGH.getplus().FillRectangle(&oLinearGradientBrush,oPlusRect);
		}
		else
		{
			SolidBrush oSolidBrush(oBkColorPlus1);
			oGH.getplus().FillRectangle(&oSolidBrush,oPlusRect);
		}
		return;
	}
	if(roBkColor1 != Transparent)
	{
		//to acommodate right-bottom gap (Win32 OS behaviour) we extend right and bottom dim.
		
		RECT oWinRect = 
		{ 
			roDURect.get_left() - get_x_window_org(), 
			roDURect.get_top() - get_y_window_org(), 
			roDURect.get_right() + 1 - get_x_window_org(), 
			roDURect.get_bottom() + 1 -get_y_window_org()
		};
		
		//OS_API_CALL
		::SetBkColor(get_hdc(),roBkColor1.colorref());
		::ExtTextOut(get_hdc(), 0, 0, ETO_OPAQUE, &oWinRect, NULL, 0, NULL);
	}
}

void ng_dc_impl::fill_rect_hg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const
{
	__fill_rect_hvg(roDURect,roBkColor1,roBkColor2,false);
}

void ng_dc_impl::fill_rect_vg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const
{
	__fill_rect_hvg(roDURect,roBkColor1,roBkColor2,true);
}

class CViewPortExtHolder
{
public:
	CViewPortExtHolder(HDC hDC,long nViewPortExt) :
		m_hDC(hDC)
	{
		VERIFY(::SetViewportExtEx(m_hDC,nViewPortExt,nViewPortExt,&m_oOldViewPortExt));
	}
	~CViewPortExtHolder()
	{
		VERIFY(::SetViewportExtEx(m_hDC,m_oOldViewPortExt.cx,m_oOldViewPortExt.cy,NULL));
	}
private:
	HDC	 m_hDC;
	SIZE m_oOldViewPortExt;
};

void ng_dc_impl::print_text(const ng_rect & roDURect,LPCTSTR lpText,long nCount,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const
{
	//struktura zgodna w Windows
	RECT oWinRect = 
	{ 
			roDURect.get_left() - get_x_window_org(), 
			roDURect.get_top() - get_y_window_org(), 
			roDURect.get_right() + 1 - get_x_window_org(), 
			roDURect.get_bottom() + 1 - get_y_window_org()
	};

	ASSERT(rpoNGFontSP.PointsObject());
	ng_GDIObject_Holder oFontHolder(get_hdc(),rpoNGFontSP->operator HFONT());
	
	::SetTextColor(get_hdc(),forecolor.colorref());

	::ExtTextOut(get_hdc(),oWinRect.left,oWinRect.top,ETO_CLIPPED,&oWinRect,lpText,nCount,NULL);
}


void ng_dc_impl::frame_area(const ng_area & roDUArea,long nFrameWidthPx,const ng_color & framecolor)
{
	ng_area oArea;
	oArea += roDUArea;
	oArea.offset(ng_size(-get_x_window_org(),-get_y_window_org()));

	ng_region_impl oRegion;
	oRegion.from_area(oArea);

	//OS_API_CALL

	CBrush oBrush;
	oBrush.CreateSolidBrush(framecolor.colorref());
	ng_GDIObject_Holder oBrushHolder(get_hdc(),oBrush);

#ifdef _DEBUG
	if(nFrameWidthPx == -3)		//for testing purposes
	{
		VERIFY(::FillRgn(get_hdc(),oRegion.get_raw_hrgn(),oBrush));
		return;
	}
#endif

	VERIFY(::FrameRgn(get_hdc(),oRegion.get_raw_hrgn(),oBrush,nFrameWidthPx,nFrameWidthPx));
}

void ng_dc_impl::patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP) const
{
	CBrush oBrush;
	oBrush.CreateSolidBrush(roColor.colorref());
	ng_GDIObject_Holder oBrushHolder(get_hdc(),oBrush);
	ng_rect oDURect = roDURect;
	
	oDURect.offset(-get_x_window_org(),-get_y_window_org());
	
	VERIFY(::PatBlt(get_hdc(),oDURect.get_left(),oDURect.get_top(),oDURect.get_width(),
		oDURect.get_height(),dwROP));
}

void ng_dc_impl::bitblt(const ng_point & roDestPoint,const ng_size & roSize,const ng_point & roSrcPoint,DWORD dwROP)
{
	VERIFY(::BitBlt(get_hdc(),roDestPoint.get_x(),roDestPoint.get_y(),roSize.get_dx(),roSize.get_dy(),
		get_hdc(),roSrcPoint.get_x(),roSrcPoint.get_y(),dwROP));
}

ng_size ng_dc_impl::measure_string(LPCTSTR lpText,long nCount,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings)
{
	CSize oDUSize(0,0);
	long nReducedLength = min(nCount,8192);	//due Windows 9x limitation

	ASSERT(rpoNGFontSP.PointsObject());
	ng_GDIObject_Holder oFontHolder(get_hdc(),rpoNGFontSP->operator HFONT());

	if(pArrayOfPartialStrings)
	{
		pArrayOfPartialStrings[0] = 0;			//pusty string = zerowa d³ugoœæ
	}
	if(pMaxChars)
	{
		*pMaxChars = 0;
	}
	if(nReducedLength > 0 && lpText[0] != '\0')
	{
		ASSERT(sizeof(int) == sizeof(long));
		ASSERT(nXAreaWidth >= 0);
		//OS_API_CALL
		VERIFY( ::GetTextExtentExPoint(get_hdc(),lpText,nReducedLength,nXAreaWidth,
			(LPINT) pMaxChars, pArrayOfPartialStrings ? (pArrayOfPartialStrings + 1) : NULL, &oDUSize ));
		
		//sztuczna korekta dla kursywy - poszerz j¹ o 1/7 wysokoœci :)

		if(rpoNGFontSP->is_italic())
		{
			oDUSize.cx += LONG(oDUSize.cy / 6);
		}
	}

	return oDUSize;
}
