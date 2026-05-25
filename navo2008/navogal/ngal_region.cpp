/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions
	region
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"

void ng_region_impl::from_area(const ng_area & roDUArea)
{
	if(roDUArea.is_empty())
	{
		_initnew();
		ASSERT(m_poRgn);
	}
	else
	{
		empty();
	
		CArray<char,char&> oPointsData;
		CArray<char,char&> oPointCntData;
		oPointsData.SetSize( roDUArea.m_oRectArray.GetSize() * 4 * sizeof(POINT) );
		oPointCntData.SetSize( roDUArea.m_oRectArray.GetSize() * sizeof(INT) );

		POINT * pPoints = (POINT *) oPointsData.GetData();
		INT * pPointCnt = (INT *) oPointCntData.GetData();
		for(int nIndex = 0; nIndex < roDUArea.m_oRectArray.GetSize(); nIndex++ )
		{
			long nIndex4 = nIndex << 2;
			ASSERT(roDUArea.m_oRectArray[ nIndex ].is_normal());
			pPoints[ nIndex4 ].x   = roDUArea.m_oRectArray[ nIndex ].get_left();
			pPoints[ nIndex4++ ].y = roDUArea.m_oRectArray[ nIndex ].get_top();
			
			//+1 because our rects include right and bottom border
			pPoints[ nIndex4 ].x   = roDUArea.m_oRectArray[ nIndex ].get_right() + 1;
			pPoints[ nIndex4++ ].y = roDUArea.m_oRectArray[ nIndex ].get_top();
			
			pPoints[ nIndex4 ].x   = roDUArea.m_oRectArray[ nIndex ].get_right() + 1;
			pPoints[ nIndex4++ ].y = roDUArea.m_oRectArray[ nIndex ].get_bottom() + 1;
			
			pPoints[ nIndex4 ].x   = roDUArea.m_oRectArray[ nIndex ].get_left();
			pPoints[ nIndex4++ ].y = roDUArea.m_oRectArray[ nIndex ].get_bottom() + 1;
			pPointCnt[ nIndex ] = 4;
		}
	
		m_poRgn = new CRgn();
		//OS_API_CALL
		VERIFY(m_poRgn->CreatePolyPolygonRgn(pPoints,pPointCnt,roDUArea.m_oRectArray.GetSize(),WINDING));
	}
}

void ng_region_impl::combine(ng_region_impl & roNAVORegion1,ng_region_impl & roNAVORegion2,int nMode)
{
	_initnew();
	ASSERT(m_poRgn);
	//OS_API_CALL
	m_poRgn->CombineRgn(roNAVORegion1.m_poRgn,roNAVORegion2.m_poRgn,nMode);
}


void ng_region_impl::offset(ng_xdist xOffset,ng_ydist yOffset)
{
	if(m_poRgn != NULL)
	{
		if(xOffset != 0 || yOffset != 0)
		{
			//OS_API_CALL
			VERIFY(ERROR != ::OffsetRgn(get_raw_hrgn(),xOffset,yOffset));
		}
	}
}

void ng_region_impl::from_clip_region(ng_dc_impl & roDCImpl)
{
	_initnew();
	//OS_API_CALL
	VERIFY(::GetClipRgn(roDCImpl.get_hdc(),get_raw_hrgn()) != -1);
	if(roDCImpl.get_x_window_org() != 0  || roDCImpl.get_y_window_org() != 0)	//offset
	{
		offset(roDCImpl.get_x_window_org(),roDCImpl.get_y_window_org());
	}
}

void ng_region_impl::invalidate(HWND hWnd)
{
	//OS_API_CALL
	if(m_poRgn != NULL)
	{
		::InvalidateRgn(hWnd,get_raw_hrgn(),FALSE);
	}
}

//-------------------------------------------------------------------------
// clipping related functions
//-------------------------------------------------------------------------

void ng_dc_impl::set_clip_region(const ng_region_impl & roRegion,int nMode)
{
	HRGN hRgn = roRegion.get_raw_hrgn();
	ng_region_impl oSecondRegion;

	if(get_x_window_org() != 0  || get_y_window_org() != 0)	//offset copy
	{
		oSecondRegion.from_region(roRegion);
		oSecondRegion.offset(-get_x_window_org(),-get_y_window_org());
		hRgn = oSecondRegion.get_raw_hrgn();
	}
	//OS_API_CALL
	VERIFY(ERROR != ::ExtSelectClipRgn(get_hdc(),hRgn,nMode));

#ifdef _DEBUG
	{
		
		HRGN hClipRgn = ::CreateRectRgn(0,0,0,0);
		::GetClipRgn(get_hdc(),hClipRgn);
		RECT oClipRect;
		::GetRgnBox(hClipRgn,&oClipRect);
		::DeleteObject(hClipRgn);
		//TRACE("ClipRegion l=%d,t=%d,r=%d,b=%d\n",oClipRect.left,oClipRect.top,oClipRect.right,oClipRect.bottom);
	}
#endif
}

