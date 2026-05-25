/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions

	frame function
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"

const long NG_FRAME_LINE_MASK = 0x000F0000;

/*
	maluje prostok¹tn¹ ramkê o szerokoœci okreœlonej nWidthPx iloœci pixeli
	mo¿e malowaæ dowolny segment ramki (left,top,right,bottom) niezale¿nie - nMask
*/

static void _raw_navo_framerect_dc(HDC hDC,const ng_rect & roDURect,long nWidthPx,long nMask)
{
	ASSERT(nMask != 0);
	nMask &= (~(DWORD)NG_FRAME_LINE_MASK);

	CArray<POINT,POINT> oPointArray;
	oPointArray.SetSize(nWidthPx * 5);
	CArray<DWORD,DWORD> oCountsArray;
	oCountsArray.SetSize(nWidthPx * 2);
	long nPtCnt = 0;
	long nSegCnt = 0;
	
	POINT aStartPoints[4];
	aStartPoints[0].x = roDURect.get_left();		//left upper
	aStartPoints[0].y = roDURect.get_top();
	aStartPoints[1].y = aStartPoints[0].y;			//right upper
	aStartPoints[1].x = roDURect.get_right();
	aStartPoints[2].x = aStartPoints[1].x;			//right bottom
	aStartPoints[2].y = roDURect.get_bottom();
	aStartPoints[3].y = aStartPoints[2].y;			//left bottom
	aStartPoints[3].x = roDURect.get_left();
	
	POINT aEndPoints[4];
	memcpy(aEndPoints,aStartPoints,sizeof(aEndPoints));
	aEndPoints[0].y--;
	aEndPoints[1].x++;
	aEndPoints[2].y++;
	aEndPoints[3].x--;

	//IMPORTANT: all segments painted clockwise !!

	for(long iter=0; iter < nWidthPx; iter++)
	{
		switch(nMask)
		{
		case  NG_FRAME_LEFT:
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aEndPoints[0];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case  NG_FRAME_TOP:
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aEndPoints[1];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_TOP):
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aEndPoints[1];
			oCountsArray[ nSegCnt++ ] = 3;
		break;
		case  NG_FRAME_RIGHT:
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aEndPoints[2];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_RIGHT):
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aEndPoints[0];
			oCountsArray[ nSegCnt++ ] = 2;
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aEndPoints[2];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_TOP  | NG_FRAME_RIGHT):
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aEndPoints[2];
			oCountsArray[ nSegCnt++ ] = 3;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_TOP | NG_FRAME_RIGHT):
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aEndPoints[2];
			oCountsArray[ nSegCnt++ ] = 4;
		break;
		case NG_FRAME_BOTTOM:
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aEndPoints[3];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aEndPoints[0];
			oCountsArray[ nSegCnt++ ] = 3;
		break;
		case (NG_FRAME_TOP | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aEndPoints[1];
			oCountsArray[ nSegCnt++ ] = 2;
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aEndPoints[3];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_TOP | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aEndPoints[1];
			oCountsArray[ nSegCnt++ ] = 3;
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aEndPoints[3];
			oCountsArray[ nSegCnt++ ] = 2;
		break;
		case (NG_FRAME_RIGHT | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aEndPoints[3];
			oCountsArray[ nSegCnt++ ] = 3;
		break;
		case (NG_FRAME_LEFT | NG_FRAME_RIGHT | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aEndPoints[0];
			oCountsArray[ nSegCnt++ ] = 4;
		break;
		case (NG_FRAME_TOP | NG_FRAME_RIGHT | NG_FRAME_BOTTOM):
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aEndPoints[3];
			oCountsArray[ nSegCnt++ ] = 4;
		break;
		case NG_FRAME_ALL:
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oPointArray[ nPtCnt++ ] = aStartPoints[1];
			oPointArray[ nPtCnt++ ] = aStartPoints[2];
			oPointArray[ nPtCnt++ ] = aStartPoints[3];
			oPointArray[ nPtCnt++ ] = aStartPoints[0];
			oCountsArray[ nSegCnt++ ] = 5;
		break;
		default:
			ASSERT(false);
		}

		aStartPoints[0].x++;aStartPoints[0].y++;
		aStartPoints[1].x--;aStartPoints[1].y++;
		aStartPoints[2].x--;aStartPoints[2].y--;
		aStartPoints[3].x++;aStartPoints[3].y--;
	
		aEndPoints[0].x++;aEndPoints[0].y++;
		aEndPoints[1].x--;aEndPoints[1].y++;
		aEndPoints[2].x--;aEndPoints[2].y--;
		aEndPoints[3].x++;aEndPoints[3].y--;
	}
	//OS_API_CALL
	::PolyPolyline(hDC,oPointArray.GetData(),oCountsArray.GetData(),nSegCnt);
}


//maluje zaokr¹glon¹ ramkê dla prost¹k¹ta (2 kroki zaokr¹glenia)
static void __raw_navo_rounded_framerect_2step(HDC hDC,const ng_rect & roRect,const ng_color & framecolor)
{
	CPen oFramePen(PS_SOLID,0,framecolor.colorref());
	
	ng_GDIObject_Holder oPenHolder(hDC,oFramePen);

	POINT oFramePoints[12];

	oFramePoints[0].x = roRect.get_left() + 1;
	oFramePoints[0].y = roRect.get_top();
	oFramePoints[1].x = roRect.get_right() - 1;
	oFramePoints[1].y = oFramePoints[0].y;
	oFramePoints[2].x = oFramePoints[1].x;
	oFramePoints[2].y = oFramePoints[1].y + 1;
	oFramePoints[3].x = oFramePoints[2].x + 1;
	oFramePoints[3].y = oFramePoints[2].y;
	oFramePoints[4].x = oFramePoints[3].x;
	oFramePoints[4].y = roRect.get_bottom() - 1;
	oFramePoints[5].x = oFramePoints[4].x - 1;
	oFramePoints[5].y = oFramePoints[4].y;
	oFramePoints[6].x = oFramePoints[5].x;
	oFramePoints[6].y = oFramePoints[5].y + 1;
	oFramePoints[7].x = roRect.get_left() + 1;
	oFramePoints[7].y = oFramePoints[6].y;
	oFramePoints[8].x = oFramePoints[7].x;
	oFramePoints[8].y = oFramePoints[7].y - 1;
	oFramePoints[9].x = oFramePoints[8].x - 1;
	oFramePoints[9].y = oFramePoints[8].y;
	oFramePoints[10].x =oFramePoints[9].x;
	oFramePoints[10].y = roRect.get_top() + 1;
	oFramePoints[11].x =oFramePoints[10].x + 1;
	oFramePoints[11].y = oFramePoints[10].y;
	VERIFY(::Polyline(hDC,oFramePoints,12));
}

//maluje zaokr¹glon¹ ramkê dla prost¹k¹ta (3 kroki zaokr¹glenia)
static void __raw_navo_rounded_framerect_3step(HDC hDC,const ng_rect & roRect,const ng_color & framecolor)
{
	CPen oFramePen(PS_SOLID,0,framecolor.colorref());
	
	ng_GDIObject_Holder oPenHolder(hDC,oFramePen);

	POINT oFramePoints[8];
	DWORD anCounts[4] = { 2, 2, 2, 2 };
	oFramePoints[0].x = roRect.get_right() - 3;
	oFramePoints[0].y = roRect.get_top();
	oFramePoints[1].x = roRect.get_left()  + 2;
	oFramePoints[1].y = oFramePoints[0].y;

	oFramePoints[2].x = roRect.get_left();
	oFramePoints[2].y = roRect.get_top() + 3;
	oFramePoints[3].x = oFramePoints[2].x;
	oFramePoints[3].y = roRect.get_bottom() - 2;
	
	oFramePoints[4].x = roRect.get_left()  + 3;
	oFramePoints[4].y = roRect.get_bottom();
	oFramePoints[5].x = roRect.get_right() - 2;
	oFramePoints[5].y = oFramePoints[4].y;
	
	oFramePoints[6].x = roRect.get_right();
	oFramePoints[6].y = roRect.get_bottom() - 3;
	oFramePoints[7].x = oFramePoints[6].x;
	oFramePoints[7].y = roRect.get_top() + 2;
	
	VERIFY(::PolyPolyline(hDC,oFramePoints,anCounts,4));
	//left upper corner
	long nX = roRect.get_left() + 2;
	long nY = roRect.get_top() + 1;
	::SetPixel(hDC,nX,nY,framecolor.colorref());
	::SetPixel(hDC,--nX,nY,framecolor.colorref());
	::SetPixel(hDC,nX,++nY,framecolor.colorref());
	//left bottom
	nY = roRect.get_bottom() - 2;
	::SetPixel(hDC,nX,nY,framecolor.colorref());
	::SetPixel(hDC,nX,++nY,framecolor.colorref());
	::SetPixel(hDC,++nX,nY,framecolor.colorref());
	//right bottom
	nX = roRect.get_right() - 2;
	::SetPixel(hDC,nX,nY,framecolor.colorref());
	::SetPixel(hDC,++nX,nY,framecolor.colorref());
	::SetPixel(hDC,nX,--nY,framecolor.colorref());
	//right upper
	nY = roRect.get_top() + 2;
	::SetPixel(hDC,nX,nY,framecolor.colorref());
	::SetPixel(hDC,nX,--nY,framecolor.colorref());
	::SetPixel(hDC,--nX,nY,framecolor.colorref());
}

//maluje obramowanie dla przycisku w stylu XP
static void _raw_navo_xpframerect_dc(HDC hDC,const ng_rect & roRect,const ng_color & framecolor,long nMask)
{
	bool bPressed = ((nMask & NG_FRAME_EDGE_ROUNDED_XP2) != 0);


	//------- frame rect -------------------
	{
		ng_rect oRect(roRect);
		oRect.inflate(-1,-1,-1,-1);
		__raw_navo_rounded_framerect_2step(hDC,oRect,framecolor);
	}
	ng_Graphics_holder oGH(hDC);
	//--------- very highlited elements -----------------------
	{
		Gdiplus::Pen oVeryHighPen(ColorPlus(ng_color(255,255,255,64)),1);
		//upper inside
		ng_ycoord nTop = roRect.get_top() + 2 + (bPressed ? 1 : 0);
		oGH.getplus().DrawLine(&oVeryHighPen,roRect.get_left() + 2,
			nTop,roRect.get_right() - 2,nTop);
		//left inside
		ng_xcoord nLeft = roRect.get_left() + 2 + (bPressed ? 1 : 0);
		oGH.getplus().DrawLine(&oVeryHighPen,nLeft,roRect.get_top() + 2,
			nLeft,roRect.get_bottom() - 2);

		//outer right and bottom
		Gdiplus::Point oVHPoints[5];
		oVHPoints[0].X = roRect.get_right();
		oVHPoints[0].Y = roRect.get_top() + 3;
		oVHPoints[1].X = oVHPoints[0].X;
		oVHPoints[1].Y = roRect.get_bottom() - 1;
		oVHPoints[2].X = oVHPoints[1].X - 1;
		oVHPoints[2].Y = oVHPoints[1].Y;
		oVHPoints[3].X = oVHPoints[2].X;
		oVHPoints[3].Y = oVHPoints[2].Y + 1;
		oVHPoints[4].X = roRect.get_left() + 3;
		oVHPoints[4].Y = oVHPoints[3].Y;
		oGH.getplus().DrawLines(&oVeryHighPen,oVHPoints,5);
	}
	//--------- highlited elements -----------------------
	{
		Gdiplus::Pen oHighPen(ColorPlus(ng_color(255,255,255,128)),1);
		//upper inside 2
		oGH.getplus().DrawLine(&oHighPen,roRect.get_left() + 2,roRect.get_top() + 3,
			roRect.get_right() - 2,roRect.get_top() + 3);
	}
	//---------- darkened elements -----------------------
	{
		Gdiplus::Pen oDarkPen(ColorPlus(ng_color(128,128,128,192)),1);
		//right inside 2
		ng_xcoord nRight = roRect.get_right() - 3 + (bPressed ? 1 : 0);
		oGH.getplus().DrawLine(&oDarkPen,nRight,roRect.get_top() + 3,
			nRight,roRect.get_bottom() - 3);
		//bottom inide 2 
		ng_ycoord nBottom = roRect.get_bottom() - 3 + (bPressed ? 1 : 0);
		oGH.getplus().DrawLine(&oDarkPen,roRect.get_left() + 3,nBottom,
			roRect.get_right() - 3,nBottom);
		
		Gdiplus::Point oDarkPoints[6];
		oDarkPoints[0].X = roRect.get_right() - 3;
		oDarkPoints[0].Y = roRect.get_top();
		oDarkPoints[1].X = roRect.get_left() + 2;
		oDarkPoints[1].Y = oDarkPoints[0].Y;
		oDarkPoints[2].X = oDarkPoints[1].X;
		oDarkPoints[2].Y = oDarkPoints[1].Y + 2;
		oDarkPoints[3].X = oDarkPoints[2].X - 2;
		oDarkPoints[3].Y = oDarkPoints[2].Y + 1;
		oDarkPoints[4].X = oDarkPoints[3].X;
		oDarkPoints[4].Y = roRect.get_bottom() - 3;
		oDarkPoints[5].X = oDarkPoints[4].X + 1;
		oDarkPoints[5].Y = oDarkPoints[4].Y;
		oGH.getplus().DrawLines(&oDarkPen,oDarkPoints,6);
	}
	//---------- very darkened elements -----------------------
	{
		Gdiplus::Pen oVeryDarkPen(ColorPlus(ng_color(128,128,128,64)),1);
		if(bPressed)
		{
			//upper inside
			oGH.getplus().DrawLine(&oVeryDarkPen,roRect.get_left() + 2,roRect.get_top() + 2,
				roRect.get_right() - 2,roRect.get_top() + 2);
			//left inside
			oGH.getplus().DrawLine(&oVeryDarkPen,roRect.get_left() + 2,roRect.get_top() + 2,
				roRect.get_left() + 2,roRect.get_bottom() - 2);
		}
		else
		{
			//right inside
			oGH.getplus().DrawLine(&oVeryDarkPen,roRect.get_right() - 2,roRect.get_top() + 2,
				roRect.get_right() - 2,roRect.get_bottom() - 2);
			//bottom inside
			oGH.getplus().DrawLine(&oVeryDarkPen,roRect.get_left() + 3,roRect.get_bottom() - 2,
				roRect.get_right() - 2,roRect.get_bottom() - 2);
		}
	}
}

static void _raw_navo_edge_framerect_dc(HDC hDC,ng_rect & roDURect,long nFrameWidthPx,const ng_color & framecolor,long nMask)
{
	ASSERT(framecolor.is_opaque());
	
	long nFramePartPx = nFrameWidthPx/2;
	ng_color clrFace = ng_color::system(COLOR_BTNHIGHLIGHT);
	ng_color clrShadow = ng_color::system(COLOR_BTNSHADOW);
	
	//OS_API_CALL
	CPen oPenFace1(PS_SOLID,0,clrFace.colorref());
	CPen oPenShadow1(PS_SOLID,0,clrShadow.colorref());
	CPen oPenFace2(PS_SOLID,0,framecolor.colorref());
	CPen oPenShadow2(PS_SOLID,0,Black.colorref());
	//draw outer
	if(nMask & (NG_FRAME_EDGE_RAISEDOUTER | NG_FRAME_EDGE_SUNKENOUTER))
	{
		//left and top
		if(nMask & (NG_FRAME_LEFT | NG_FRAME_TOP))
		{
			ng_GDIObject_Holder oPenHolder(hDC,
				(nMask & NG_FRAME_EDGE_RAISEDOUTER) ? oPenFace1 : oPenShadow1);
			_raw_navo_framerect_dc(hDC,roDURect,nFramePartPx,
				nMask & (NG_FRAME_LEFT | NG_FRAME_TOP));
		}
		//right and bottom
		if(nMask & (NG_FRAME_RIGHT | NG_FRAME_BOTTOM))
		{
			ng_GDIObject_Holder oPenHolder(hDC,
				(nMask & NG_FRAME_EDGE_RAISEDOUTER) ? oPenShadow2 : oPenFace1);
			_raw_navo_framerect_dc(hDC,roDURect,nFramePartPx,
				nMask & (NG_FRAME_RIGHT | NG_FRAME_BOTTOM));
		}
	}
	
	nFrameWidthPx -= nFramePartPx;
	roDURect.inflate(-nFramePartPx,-nFramePartPx);
	//draw inner
	if(nMask & (NG_FRAME_EDGE_RAISEDINNER | NG_FRAME_EDGE_SUNKENINNER))
	{
		//left and top
		if(nMask & (NG_FRAME_LEFT | NG_FRAME_TOP))
		{
			ng_GDIObject_Holder oPenHolder(hDC,
				(nMask & NG_FRAME_EDGE_RAISEDINNER) ? oPenFace2: oPenShadow2);
			_raw_navo_framerect_dc(hDC,roDURect,nFramePartPx,
				nMask & (NG_FRAME_LEFT | NG_FRAME_TOP));
		}
		//right and bottom
		if(nMask & (NG_FRAME_RIGHT | NG_FRAME_BOTTOM))
		{
			ng_GDIObject_Holder oPenHolder(hDC,
				(nMask & NG_FRAME_EDGE_RAISEDINNER) ? oPenShadow1 : oPenFace2);
			_raw_navo_framerect_dc(hDC,roDURect,nFramePartPx,
				nMask & (NG_FRAME_RIGHT | NG_FRAME_BOTTOM));
		}
	}
}

const long NG_FRAME_EDGE_ANY		 
		= NG_FRAME_EDGE_RAISEDOUTER | NG_FRAME_EDGE_SUNKENOUTER |
		  NG_FRAME_EDGE_RAISEDINNER | NG_FRAME_EDGE_SUNKENINNER;

void ng_dc_impl::frame_rect(ng_rect oDURect,long nFrameWidthPx,const ng_color & framecolor,long nMask)
{
	oDURect.offset(-get_x_window_org(),-get_y_window_org());

	if(nMask == 0)
	{
		return;
	}

	if(nMask & NG_FRAME_EDGE_ANY)		//raised / sunken
	{
		_raw_navo_edge_framerect_dc(get_hdc(),oDURect,nFrameWidthPx,framecolor,nMask);
	}
	else
	{
		if(nMask & NG_FRAME_EDGE_ROUNDED_FLAT)		//raised / sunken
		{
			__raw_navo_rounded_framerect_3step(get_hdc(),oDURect,framecolor);
		}
		else
		{
			if(nMask & (NG_FRAME_EDGE_ROUNDED_XP | NG_FRAME_EDGE_ROUNDED_XP2))	//zaokr¹glona ramka w stylu XP
			{
				_raw_navo_xpframerect_dc(get_hdc(),oDURect,framecolor,nMask);
			}
			else	//p³aska krawêdŸ, brak alphy
			{
				if(framecolor != Transparent)
				{
					CPen oPen((nMask & NG_FRAME_LINE_MASK) >> 16,0,framecolor.colorref());
					ng_GDIObject_Holder oPenHolder(get_hdc(),oPen);
					_raw_navo_framerect_dc(get_hdc(),oDURect,nFrameWidthPx,nMask);
				}
			}
		}
	}
}

