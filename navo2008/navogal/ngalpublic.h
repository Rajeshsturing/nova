/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer

	public definitions
*/

#ifndef _NGALPUBLIC_H_
#define _NGALPUBLIC_H_

//private implementation's references
class cngal_session;
class cngal_context;
class cngal_region;
class cngal_image;

//----------------------------
//public part ----------------
//----------------------------
class _colordesc
{
public:
	_colordesc(BYTE red,BYTE green,BYTE blue,BYTE alpha) :
		m_colordesc(RGB(red,green,blue) | ((((DWORD)(BYTE)(alpha))<<24)))
	{
		ASSERT((RGB(red,green,blue) & 0xFF000000) == 0x00000000);	//highest byte must be free

	}
	_colordesc(COLORREF clrref) :
		m_colordesc(clrref)
	{
		ASSERT((clrref & 0xFF000000) == 0x00000000);

	}
	_colordesc(const _colordesc & ro_colordesc) :
		m_colordesc(ro_colordesc.m_colordesc)
	{
	}
	virtual void operator = (const _colordesc & ro_colordesc)
	{
		m_colordesc = ro_colordesc.m_colordesc;
	}
	virtual bool operator == (const _colordesc & ro_colordesc) const
	{
		return (m_colordesc == ro_colordesc.m_colordesc);
	}
	virtual bool operator != (const _colordesc & ro_colordesc) const
	{
		return (m_colordesc != ro_colordesc.m_colordesc);
	}
	BYTE _red() const
	{
		return GetRValue(m_colordesc);
	}
	BYTE _green() const
	{
		return GetGValue(m_colordesc);
	}
	BYTE _blue() const
	{
		return GetBValue(m_colordesc);
	}
	BYTE _alpha() const
	{
		return ((BYTE)((m_colordesc)>>24));
	}
	COLORREF colorref() const
	{
		ASSERT((m_colordesc & 0x00FFFFFF) == RGB(_red(),_green(),_blue()));
		return m_colordesc & 0x00FFFFFF;
	}
	long _get_raw_long() const
	{
		return long(m_colordesc);
	}
	long & _access_raw_long()
	{
		return (long&) m_colordesc;
	}
private:
	DWORD	m_colordesc;
};

const _colordesc TRANSPARENTCOLOR =	_colordesc(255,255,255,255);	//ca≥kowicie przeüroczysty bia≥y
const _colordesc INVALIDCOLOR	  = _colordesc(0,0,0,255);			//"ca≥kowicie przeüroczysty czarny"

class _rect : public tagRECT		//prostokπt, prawie jak CRect tylko lepszy
{
public:
	_rect()
	{
		left = right = top = bottom = 0;
	}
    _rect(long l,long t,long r,long b)
	{
		left = l; right = r; top = t; bottom = b;
	}
	_rect(const _rect & roProst)
	{
		left	=	roProst.left;
		right	=	roProst.right;
		top		=	roProst.top;
		bottom	=	roProst.bottom;
	}
	_rect(const RECT & roRect)
	{
		left	=	roRect.left;
		right	=	roRect.right;
		top		=	roRect.top;
		bottom	=	roRect.bottom;
	}
	_rect(const CPoint & roLUPoint,const CSize & roSize)
	{
		left	= roLUPoint.x;
		top		= roLUPoint.y;
		right	= left + roSize.cx;
		bottom	= top + roSize.cy;
	}
	long Width() const 
	{ 
		return right - left; 
	}
	long Height() const
	{ 
		return bottom - top; 
	}
	CSize Size() const
	{ 
		return CSize(right - left, bottom - top); 
	}
	CPoint TopLeft() const
	{ 
		return CPoint(left,top);
	}
	CPoint BottomRight() const
	{ 
		return CPoint(right,bottom);
	}
	CPoint BottomLeft() const
	{
		return CPoint(left,bottom);
	}
	CPoint CenterPoint() const
	{ 
		return CPoint((left+right)/2, (top+bottom)/2); 
	}
	operator LPRECT() 
	{ 
		return this; 
	}
	operator LPCRECT() const 
	{ 
		return this; 
	}
	virtual bool operator == (const _rect & roRect) const
	{
		return 
			left	== roRect.left  && 
			top		== roRect.top   && 
			right	== roRect.right && 
			bottom	== roRect.bottom;
	}
	virtual bool operator !=(const _rect & roRect) const
	{
		return ! ((*this)==(roRect));
	}
	bool IsRectEmpty() const
	{
		return (right <= left) || (bottom <= top);
	}
	bool PtInRect(POINT point) const
	{
		return (point.x >= left) && (point.x < right) && 
			   (point.y >= top)  && (point.y < bottom);
	}
	void NormalizeRect();
	void OffsetRect(long x, long y)
	{
		left += x;	right += x;	top	+= y; bottom	+= y;
	}
	bool IsNormalized() const
	{
		return (left <= right) && (top <= bottom);
	}
	bool IntersectRect(const _rect & roProst1, const _rect & roProst2);
	void Union(const _rect & roProst);
	void InflateRect(long dx,long dy)
	{
		left  -= dx;
		right += dx;
		top   -= dy;
		bottom+= dy;
	}
	void InflateRect(long dleft,long dtop,long dright,long dbottom)
	{
		left  -= dleft;
		right += dright;
		top   -= dtop;
		bottom+= dbottom;
	}
};

class CRepaintArea : public CInterface__
{
public:
	CRepaintArea(){}

	void operator+=(const CRepaintArea & roRepaintArea);
	void operator+=(const _rect & oRect);

	void Empty()
	{
		m_oProstArray.RemoveAll();
	}
	bool IsEmpty() const
	{
		return m_oProstArray.GetSize() == 0;
	}

	bool IsIntersect(const _rect & roProst) const;
	bool IsInside(const CPoint & oPoint);
	bool Invalidate(HWND hWnd) const;	//DU (device units)
	void GetBoundingRect(_rect & roRect) const;
#ifdef _DEBUG
	void _dump();
#endif 
private:
	CArray<_rect,const _rect&> m_oProstArray;
	friend class cngal_context;
	friend class cngal_region;
};

class CNAVORegion
{
public:
	CNAVORegion();
	~CNAVORegion();
	void from_RA(const CRepaintArea & roRepaintArea);
	void from_rect(const _rect & roRect);
	void combine(CNAVORegion & roNAVORegion1,CNAVORegion & roNAVORegion2,int nMode);
	void empty();
private:
	cngal_region * m_pRegion;

	friend class cngal_context;
};


/*
	graphics session
	(required by some GDI's)
*/

enum eNavoGraphicsMode
{
	plain_gdi,		// = fast and compatible
	gdiplus_normal,	// = GDI+ without special effects
	gdiplus_high	// = GDI+ with high quality effects
};

class CNavoGraphicsSession
{
public:
	CNavoGraphicsSession();
	~CNavoGraphicsSession();
	void Init(eNavoGraphicsMode mode);
	void Done();
};

long _get_raw_scaling_factor();

/*
	CNGC - NAVO Graphics Context (GDI::HDC / GDI+::Graphics like)
*/
const long RN_FRAME_LEFT = 0x0001;
const long RN_FRAME_TOP	 = 0x0002;
const long RN_FRAME_RIGHT= 0x0004;
const long RN_FRAME_BOTTOM=0x0008;
const long RN_FRAME_ALL	 = 0x000F;

const long RN_FRAME_EDGE_FLAT		 = 0x0000;
const long RN_FRAME_EDGE_RAISEDOUTER = 0x0100;
const long RN_FRAME_EDGE_SUNKENOUTER = 0x0200;
const long RN_FRAME_EDGE_RAISEDINNER = 0x0400;
const long RN_FRAME_EDGE_SUNKENINNER = 0x0800;

const long RN_FRAME_EDGE_RAISED = RN_FRAME_EDGE_RAISEDOUTER | RN_FRAME_EDGE_RAISEDINNER;
const long RN_FRAME_EDGE_BUMP	= RN_FRAME_EDGE_RAISEDOUTER | RN_FRAME_EDGE_SUNKENINNER;
const long RN_FRAME_EDGE_ETCHED = RN_FRAME_EDGE_SUNKENOUTER | RN_FRAME_EDGE_RAISEDINNER;
const long RN_FRAME_EDGE_SUNKEN = RN_FRAME_EDGE_SUNKENOUTER | RN_FRAME_EDGE_SUNKENINNER;

class CNGC	
{
public:
	CNGC(HDC hDC);
	~CNGC();
	CSize get_string_size(const CString & roString,SCP<IFont> & rpIFontSP);
	CSize measure_string(LPCTSTR lpString,long nStrLen,long nAreaWidth,SCP<IFont> & rpIFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings = NULL);
	CSize measure_string(const CString & roString,long nAreaWidth,SCP<IFont> & rpIFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings = NULL);

	void frame_rect(const _rect & roRect,long nPixelFrameWidth,_colordesc framecolor,long nMask);
	void frame_RA(const CRepaintArea & roRepaintArea,long nPixelFrameWidth,_colordesc framecolor);

	void fill_rect_hg(const _rect & roRect,_colordesc fillcolor1,_colordesc fillcolor2);	//fills rectangle with color (and optional horizontal gradient)
	void print_text(const _rect & roRect,LPCTSTR lpText,long nCount,_colordesc forecolor,_colordesc backcolor,
		SCP<IFont> & rpIFontSP);
	void print_text(const _rect & roRect,const CString & roString,_colordesc forecolor,_colordesc backcolor,
		SCP<IFont> & rpIFontSP);
	bool is_visible(const CRepaintArea & roRepaintArea);
	long _getzoom_factor();
	
	HDC _get_raw_HDC() const;
	HWND _get_window() const;

	void set_standard_mapping(const CSize & roZoomSize);
	//converts argument to logical units (like DPtoLP)
	void toLU(POINT * pDUPoint) const;
	void toLU(RECT * pDURect) const;
	void toLU(SIZE * pDUSize) const;

	//converts argument to device units (like LPtoDP)
	void toDU(POINT * pDUPoint) const;
	void toDU(RECT * pDURect) const;
	void toDU(SIZE * pDUSize) const;
	void toDU(const CRepaintArea & roLURA,CRepaintArea & roDURA) const;

	//clip region functions
	void set_clip_region(const CNAVORegion & roNAVORegion,int nMode);
	void get_clip_region(CNAVORegion & roNAVORegion);
private:
	cngal_context * m_pContext;

	friend class CNAVOImage;	//for m_pContext
};

enum eImageDrawMode
{
	idm_origsize,
	idm_stretch,
	idm_tile
};

class CNAVOImage : public CInterface__
{
public:
	CNAVOImage();
	~CNAVOImage();

	void read_from_file(const CString & roFileNameString);
	void read_from_stream(SCP<IStream> poStreamSP);
	long get_width() const;
	long get_height() const;
	void draw(CNGC & roNGC,const _rect & roDestRect,DWORD dwROP,eImageDrawMode eMode);
	CPalette * get_palette() const;
	CBitmap * clone_bitmap();
private:
	cngal_image * m_pImage;
};
//-----------------
// INLINES
//-----------------

inline void _rect::NormalizeRect()
{
	long  nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

inline bool _rect::IntersectRect(const _rect & roProst1, const _rect & roProst2)
{
	ASSERT(roProst1.IsNormalized());
	ASSERT(roProst2.IsNormalized());
	left	= max(roProst1.left	 ,roProst2.left		);
	right	= min(roProst1.right ,roProst2.right	);
	top		= max(roProst1.top	 ,roProst2.top		);
	bottom	= min(roProst1.bottom,roProst2.bottom	);
	
	if(Width() > 0 && Height() > 0)
	{
		return true;
	}
	left = right = top = bottom = 0;
	return false;
}

inline void _rect::Union(const _rect & roProst)
{
	ASSERT(IsNormalized());
	ASSERT(roProst.IsNormalized());
	left	= min(left	  ,roProst.left);
	right	= max(right	  ,roProst.right);
	top		= min(top	  ,roProst.top);
	bottom	= max(bottom  ,roProst.bottom);
}

//	 okreúla zawieranie siÍ dwÛch _rect
// 0 nie zawierajπ siÍ
//+1 roProst1 wewnatrz roProst2
//+2 roProst2 wewnπtrz roPros1

inline long RectContaiment(const _rect & roProst1,const _rect & roProst2)
{
	if(roProst1.left >= roProst2.left  && roProst1.top >= roProst2.top &&
	   roProst1.right<=	roProst2.right && roProst1.bottom <= roProst2.bottom)
	{
		return +1;
	}
	if(roProst2.left >= roProst1.left  && roProst2.top >= roProst1.top &&
	   roProst2.right<=	roProst1.right && roProst2.bottom <= roProst1.bottom)
	{
		return +2;
	}
	return 0;
}

//---------------------------------------------------------------------------
// repaint area
//---------------------------------------------------------------------------


inline void CRepaintArea::operator+=(const CRepaintArea & roRepaintArea)
{
	for(int nIndex = 0; nIndex < roRepaintArea.m_oProstArray.GetSize(); nIndex++ )
	{
		(*this) += roRepaintArea.m_oProstArray[ nIndex ];
	}
}

inline bool CRepaintArea::IsIntersect(const _rect & roProst) const		//dawniej IsVisible
{
	_rect oRob;
	for(int nIndex = 0; nIndex < m_oProstArray.GetSize(); nIndex++ )
	{
		if(oRob.IntersectRect(roProst,m_oProstArray[nIndex]))
		{
			return true;
		}
	}
	return false;
}

inline bool CRepaintArea::IsInside(const CPoint & oPoint)
{
	for(int nIndex = 0; nIndex < m_oProstArray.GetSize(); nIndex++ )
	{
		if(m_oProstArray[nIndex].PtInRect(oPoint))
		{
			return true;
		}
	}
	return false;
}

inline void CRepaintArea::operator+=(const _rect & oRect)
{
	if(oRect.IsRectEmpty())
	{
		return;
	}
	for( int nIndex = 0; nIndex < m_oProstArray.GetSize(); nIndex++ )
	{
		switch(RectContaiment(oRect,m_oProstArray[ nIndex ]))
		{
		case 1:		//nowy leøy w starym
			return;		
		case 2:		//stary leøy w nowym - zastπp
			m_oProstArray[ nIndex ] = oRect;
			return;
		}
	}
	m_oProstArray.Add(oRect);
}

inline void CRepaintArea::GetBoundingRect(_rect & roRect) const
{
	if(m_oProstArray.GetSize() == 0)
	{
		roRect = _rect(0,0,0,0);
		return;
	}
	else
	{
		roRect = m_oProstArray[0];
	}
	for( int nIndex = 1; nIndex < m_oProstArray.GetSize(); nIndex++ )
	{
		roRect.Union(m_oProstArray[nIndex]);
	}
}

inline bool CRepaintArea::Invalidate(HWND hWnd) const
{
	if(m_oProstArray.GetSize() == 0)
	{
		return false;
	}
	_rect oClientRect;
	::GetClientRect(hWnd,&oClientRect);
	bool bAnything = false;
	for(int nIndex = 0; nIndex < m_oProstArray.GetSize(); nIndex++ )
	{
		_rect oFinalRect;
		if(oFinalRect.IntersectRect(m_oProstArray[ nIndex ],oClientRect))
		{
			oFinalRect.NormalizeRect();
			VERIFY(::InvalidateRect(hWnd,&oFinalRect,TRUE));
			bAnything = true;
		}
	}
	return bAnything;
}

#ifdef _DEBUG
inline void CRepaintArea::_dump()
{
	if(m_oProstArray.GetSize() == 0)
	{
		TRACE("-- empy repaint area -------------\n");
	}
	else
	{
		TRACE("-- repaint area dump (l,r,t,b) -------------\n");
		for(long iter = 0; iter < m_oProstArray.GetSize(); iter++)
		{
			TRACE("%d=[%d,%d],[%d,%d]\n",iter,m_oProstArray[iter].left,m_oProstArray[iter].right,
				m_oProstArray[iter].top,m_oProstArray[iter].bottom);
		}
		TRACE("-- end repaint area dump ---------\n");
	}
}
#endif 

inline CSize CNGC::measure_string(const CString & roString,long nAreaWidth,SCP<IFont> & rpIFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings)
{
	return measure_string(roString,roString.GetLength(),nAreaWidth,rpIFontSP,
		pMaxChars,pArrayOfPartialStrings);
}

inline void CNGC::print_text(const _rect & roRect,const CString & roString,_colordesc forecolor,_colordesc backcolor,
		SCP<IFont> & rpIFontSP)
{
	print_text(roRect,roString,roString.GetLength(),forecolor,backcolor,rpIFontSP);
}

#else
#error __FILE__ already included
#endif
