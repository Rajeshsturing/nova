/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	public (interface) definitions
*/

#ifndef _NGAL_IFACE_H_
#define _NGAL_IFACE_H_

//forward declarations
class ng_dc_impl;
class ng_region_impl;
class ng_session_impl;
class ng_double_buffer_impl;
class ng_image_impl;
class ng_size;
//-------------------------------------------------------------------------
//basic typedefs
//
//you can change it to anything (short,int64 etc)
//-------------------------------------------------------------------------

typedef long	ng_xcoord;			//horizontal coordinate
typedef long	ng_ycoord;			//vertical coordinate
typedef long	ng_xdist;			//horizontal distance
typedef long	ng_ydist;			//vertical distance
typedef CString ng_string;			//string

//-------------------------------------------------------------------------
// primitve structures
//-------------------------------------------------------------------------

class ng_point
{
public:
	ng_point() :
		m_x(0),
		m_y(0)
	{
	}
	ng_point(ng_xcoord x,ng_ycoord y) :
		m_x(x),
		m_y(y)
	{
	}
	ng_point(const ng_point & roPt) :
		m_x(roPt.m_x),
		m_y(roPt.m_y)
	{
	}
	ng_point(const CPoint & roWinPoint) :
		m_x(roWinPoint.x),
		m_y(roWinPoint.y)
	{
	}
	void operator = (const ng_point & roPt)
	{
		m_x = roPt.m_x;
		m_y	= roPt.m_y;
	}
	bool operator == (const ng_point & roPt) const
	{
		return (m_x == roPt.m_x) && (m_y == roPt.m_y);
	}
	bool operator != (const ng_point & roPt) const
	{
		return !(operator ==(roPt));
	}
	ng_xcoord get_x() const
	{
		return m_x;
	}
	void set_x(ng_xcoord x)
	{
		m_x = x;
	}
	ng_ycoord get_y() const
	{
		return m_y;
	}
	void set_y(ng_ycoord y)
	{
		m_y = y;
	}
	ng_point & offset(const ng_size & roSize);
	ng_point & offset(ng_xdist xdx,ng_ydist ydy);
	ng_size distance(const ng_point & roPt) const;
private:
	ng_xcoord	m_x;
	ng_ycoord	m_y;
};

class ng_size
{
public:
	ng_size() :
		m_dx(0),
		m_dy(0)
	{
	}
	ng_size(ng_xdist dx,ng_ydist dy) :
		m_dx(dx),
		m_dy(dy)
	{
	}
	ng_size(const ng_size & roSize) :
		m_dx(roSize.m_dx),
		m_dy(roSize.m_dy)
	{
	}
	ng_size(const CSize & roWinSize):
		m_dx(roWinSize.cx),
		m_dy(roWinSize.cy)
	{
	}
	void operator = (const ng_size & roSize)
	{
		m_dx = roSize.m_dx;
		m_dy = roSize.m_dy;
	}
	ng_size operator - () const
	{
		return ng_size(-get_dx(),-get_dy());
	}
	ng_size operator - (const ng_size & roSize) const
	{
		return ng_size(get_dx()-roSize.get_dx(),get_dy()-roSize.get_dy());
	}
	ng_size operator + (const ng_size & roSize) const
	{
		return ng_size(get_dx()+roSize.get_dx(),get_dy()+roSize.get_dy());
	}
	bool operator == (const ng_size & roSize) const
	{
		return (m_dx == roSize.m_dx) && (m_dy == roSize.m_dy);
	}
	bool operator != (const ng_size & roSize) const
	{
		return !((*this) == roSize);
	}
	ng_xdist get_dx() const
	{
		return m_dx;
	}
	void set_dx(ng_xdist dx)
	{
		m_dx = dx;
	}
	ng_ydist get_dy() const
	{
		return m_dy;
	}
	void set_dy(ng_ydist dy)
	{
		m_dy = dy;
	}
private:
	ng_xdist	m_dx;
	ng_ydist	m_dy;
};

class ng_rect
{
public:
	ng_rect() :
		m_xleft(0),
		m_ytop(0),
		m_xright(-1),
		m_ybottom(-1)
	{
	}
	ng_rect(ng_xcoord xleft,ng_ycoord ytop,ng_xcoord xright,ng_ycoord ybottom):
		m_xleft(xleft),
		m_ytop(ytop),
		m_xright(xright),
		m_ybottom(ybottom)
	{
	}
	ng_rect(const ng_rect & roRect) :
		m_xleft(roRect.m_xleft),
		m_ytop(roRect.m_ytop),
		m_xright(roRect.m_xright),
		m_ybottom(roRect.m_ybottom)
	{
	}
	ng_rect(const ng_point & roPoint,const ng_size & roSize):
		m_xleft(roPoint.get_x()),
		m_ytop(roPoint.get_y()),
		m_xright(roPoint.get_x() + roSize.get_dx() - 1),
		m_ybottom(roPoint.get_y() + roSize.get_dy() - 1)
	{
	}
	ng_xdist get_width() const
	{
		return (m_xright - m_xleft + 1);
	}
	ng_ydist get_height() const
	{
		return (m_ybottom - m_ytop + 1);
	}
	ng_size get_size() const
	{
		return ng_size(get_width(),get_height());
	}
	ng_point get_topleft() const
	{
		return ng_point(m_xleft,m_ytop);
	}
	ng_point get_topright() const
	{
		return ng_point(m_xright,m_ytop);
	}
	ng_point get_bottomleft() const
	{
		return ng_point(m_xleft,m_ybottom);
	}
	ng_point get_bottomright() const
	{
		return ng_point(m_xright,m_ybottom);
	}
	ng_xcoord get_center_x() const
	{
		return ng_xcoord((m_xleft+m_xright)/2);
	}
	ng_ycoord get_center_y() const
	{
		return ng_xcoord((m_ytop+m_ybottom)/2);
	}
	ng_point get_centerpoint() const
	{
		return ng_point(get_center_x(),get_center_y()); 
	}
	bool operator ==(const ng_rect & roRect) const
	{
		return	m_xleft  == roRect.m_xleft  && m_ytop    == roRect.m_ytop &&
				m_xright == roRect.m_xright && m_ybottom == roRect.m_ybottom;
	}
	bool operator !=(const ng_rect & roRect) const
	{
		return	m_xleft  != roRect.m_xleft  || m_ytop    != roRect.m_ytop ||
				m_xright != roRect.m_xright || m_ybottom != roRect.m_ybottom;
	}
	void operator = (const ng_rect & roRect)
	{
		m_xleft		= roRect.m_xleft;
		m_ytop		= roRect.m_ytop;
		m_xright	= roRect.m_xright;
		m_ybottom	= roRect.m_ybottom;
	}
	ng_rect & offset(ng_xdist dx, ng_ydist dy)
	{
		m_xleft		+= dx;	
		m_xright	+= dx;	
		m_ytop		+= dy;
		m_ybottom	+= dy;
	
		return (*this);
	}
	ng_rect & offset(const ng_size & roSize)
	{
		m_xleft		+= roSize.get_dx();
		m_xright	+= roSize.get_dx();
		m_ytop		+= roSize.get_dy();
		m_ybottom	+= roSize.get_dy();

		return (*this);
	}
	void inflate(ng_xdist dx,ng_ydist dy)
	{
		m_xleft		-= dx;
		m_xright	+= dx;
		m_ytop		-= dy;
		m_ybottom	+= dy;
	}
	void inflate(ng_xdist dleft,ng_ydist dtop,ng_xdist dright,ng_ydist dbottom)
	{
		m_xleft		-= dleft;
		m_xright	+= dright;
		m_ytop		-= dtop;
		m_ybottom	+= dbottom;
	}
	bool is_normal() const
	{
		return (get_width() >= 0) && (get_height() >= 0);
	}
	bool is_inside(const ng_point & roPoint) const
	{
		return (roPoint.get_x() >= m_xleft) && (roPoint.get_x() <= m_xright) && 
			   (roPoint.get_y() >= m_ytop)  && (roPoint.get_y() <= m_ybottom);
	}
	bool is_intersect(const ng_rect & roRect) const
	{
		ASSERT(is_normal());
		ASSERT(roRect.is_normal());

		if(max(m_xleft,roRect.get_left()) > min(m_xright,roRect.get_right()))
		{
			return false;
		}
		return (max(m_ytop,roRect.get_top()) <= min(m_ybottom,roRect.get_bottom()));
	}
	bool is_empty() const
	{
		return (m_xright < m_xleft) || (m_ybottom < m_ytop);
	}
	ng_xcoord get_left() const
	{
		return m_xleft;
	}
	ng_xcoord get_right() const
	{
		return m_xright;
	}
	void set_left(ng_xcoord xleft)
	{
		m_xleft = xleft;
	}
	void set_right(ng_xcoord xright)
	{
		m_xright = xright;
	}
	ng_ycoord get_top() const
	{
		return m_ytop;
	}
	ng_ycoord get_bottom() const
	{
		return m_ybottom;
	}
	void set_top(ng_ycoord ytop)
	{
		m_ytop = ytop;
	}
	void set_bottom(ng_ycoord ybottom)
	{
		m_ybottom = ybottom;
	}
	void set_width(ng_xdist xWidth)
	{
		m_xright = m_xleft + xWidth - 1;
		ASSERT(get_width() == xWidth);
	}
	void set_height(ng_ydist yHeight)
	{
		m_ybottom = m_ytop + yHeight - 1;
		ASSERT(get_height() == yHeight);
	}
	void set_size(const ng_size & roSize)
	{
		set_width(roSize.get_dx());
		set_height(roSize.get_dy());
	}
	void normalize();
	void union_with(const ng_rect & roProst);
	bool merge_adjacent(const ng_rect & roProst);
	void intersect_with(const ng_rect & roInRect);
private:
	ng_xcoord	m_xleft;
	ng_ycoord	m_ytop;
	ng_xcoord	m_xright;
	ng_ycoord	m_ybottom;
};


class ng_area
{
public:
	ng_area(){}
	ng_area(const ng_rect & roRect)
	{
		(*this) += roRect;
	}
	bool is_empty() const
	{
		return m_oRectArray.GetSize() == 0;
	}
	bool is_inside(const ng_point & roPoint) const;
	bool is_intersect(const ng_rect & roRect) const;

	void operator += (const ng_rect & roRect);
	void operator +=(const ng_area & roArea);
	void get_bounding_rect(ng_rect & roRect) const;
	void offset(const ng_size & roSize);
	void intersect_with(const ng_rect & roInRect,ng_area & roOutputArea) const;
	void empty()
	{
		m_oRectArray.RemoveAll();
	}
	long get_count() const
	{
		return m_oRectArray.GetSize();
	}
private:
	CArray<ng_rect,const ng_rect &> m_oRectArray;

	friend class ng_dc_impl;
	friend class ng_region_impl;
};

//	 okreœla zawieranie siê dwóch ng_rect
// 0 nie zawieraj¹ siê
//+1 roProst1 wewnatrz roProst2
//+2 roProst2 wewn¹trz roPros1

long rect_containment(const ng_rect & roProst1,const ng_rect & roProst2);

//-------------------------------------------------------------------------
//	"full color"
//-------------------------------------------------------------------------
enum eColorTranslation
{
	ct_none,		//identity operation
	ct_blackwhite,	//maps all to black-white
	ct_grayscale,	//maps all colors to grayscale
};

class ng_color
{
public:
	ng_color() :
#if defined(_NAVODOTNET) || defined(NAVO2008)
		m_color(((DWORD)(BYTE)(255))<<24)
#else
		//to_do: this is error in new compiler, but compiles in older one!
		m_color(0,0,0,255)	//init with Invalid
#endif
	{
	}
	ng_color(BYTE red,BYTE green,BYTE blue,BYTE alpha) :
		m_color(RGB(red,green,blue) | ((((DWORD)(BYTE)(alpha))<<24)))
	{
		ASSERT((RGB(red,green,blue) & 0xFF000000) == 0x00000000);	//highest byte must be free

	}
	ng_color(COLORREF clrref) :
		m_color(clrref)
	{
		ASSERT((clrref & 0xFF000000) == 0x00000000);
	}
	ng_color(const ng_color & rong_color) :
		m_color(rong_color.m_color)
	{
	}
	void operator = (const ng_color & rong_color)
	{
		m_color = rong_color.m_color;
	}
	bool operator == (const ng_color & rong_color) const
	{
		return (m_color == rong_color.m_color);
	}
	bool operator != (const ng_color & rong_color) const
	{
		return (m_color != rong_color.m_color);
	}
	BYTE _red() const
	{
		ASSERT(_is_valid());
		return GetRValue(m_color);
	}
	BYTE _green() const
	{
		ASSERT(_is_valid());
		return GetGValue(m_color);
	}
	BYTE _blue() const
	{
		ASSERT(_is_valid());
		return GetBValue(m_color);
	}
	BYTE _alpha() const
	{
		ASSERT(_is_valid());
		return ((BYTE)((m_color)>>24));
	}
	COLORREF colorref() const
	{
		ASSERT(_is_valid());
		ASSERT((m_color & 0x00FFFFFF) == RGB(_red(),_green(),_blue()));
		return m_color & 0x00FFFFFF;
	}
	bool is_opaque() const
	{
		ASSERT(_is_valid());
		return (_alpha() == 0);
	}
	long _get_raw_long() const
	{
		return long(m_color);
	}
	long & _access_raw_long()
	{
		return (long&) m_color;
	}
	static ng_color system(int nSystemColorIndex)
	{
		//OS_API_CALL
		return ng_color(::GetSysColor(nSystemColorIndex));
	}
	ng_color translate(const eColorTranslation eCT) const;
	bool _is_valid() const;
private:
	DWORD	m_color;
};

const ng_color Transparent	= ng_color(255,255,255,255);	//completly transparent white - interpreted as transparent glass
const ng_color Invalid		= ng_color(0,0,0,255);			//completly transparent black - invalid value for color
const ng_color Black		= ng_color(0,0,0,0);			//opaque black = normal black
const ng_color White		= ng_color(255,255,255,0);		//opaque white
const ng_color Red			= ng_color(255,0,0,0);			//opaque red

inline bool ng_color::_is_valid() const
{
	return (*this) != Invalid;
}

inline ng_color ng_color::translate(const eColorTranslation eCT) const
{
	//--- transparent is immutable --
	if(*this == Transparent)
	{
		return *this;
	}

	switch(eCT)
	{
	case ct_none:
		return *this;
	case ct_blackwhite:
		return ((_red() + _green() + _blue()) > 3 * 0x80) ? White : Black;
	case ct_grayscale:
		{
			const long nIntensity = ((_red() + _green() + _blue()) / 3);
			return ng_color(RGB(nIntensity,nIntensity,nIntensity));
		}
	default:
		ASSERT(false);
		return *this;
	}
}

//-------------------------------------------------------------------------
//	fonts
//-------------------------------------------------------------------------
class ng_font : public CInterface__
{
public:
	static SCP<ng_font> create(LPCTSTR lpFontName,long nRawSize,bool bBold,bool bItalic,bool bStrikeThrough,bool bUnderline,SHORT sCharSet);
	operator HFONT() const
	{
		return m_hFont;
	}
	bool is_italic() const
	{
		return m_bItalic;
	}
private:
	ng_font(SCP<IFont> & rpoFontSP,bool bItalic);
	~ng_font();

	HFONT	   m_hFont;
	SCP<IFont> m_poFontSP;
	bool       m_bItalic;
};
//-------------------------------------------------------------------------
//	regions
//-------------------------------------------------------------------------
class ng_ic;

class ng_region
{
public:
	ng_region();
	ng_region(const ng_rect & roDURect);

	~ng_region();
	void from_area(const ng_area & roDUArea);	//inflates !!!
	void from_rect(const ng_rect & roDURect);
	void from_region(const ng_region & roDURgn);
	void from_clip_region(ng_ic & roDC);
	void combine(ng_region & roNAVORegion1,ng_region & roNAVORegion2,int nMode);
	void offset(ng_xdist xOffset,ng_ydist yOffset);
	void empty();
	bool is_empty() const;
	void invalidate(HWND hWnd);
private:
	ng_region_impl * m_poRegionImpl;
	friend class ng_dc;
};

//-------------------------------------------------------------------------
//	images
//-------------------------------------------------------------------------
class ng_image : public CInterface__
{
public:
	static SCP<ng_image> from_file(LPCTSTR lpFileName);
	static SCP<ng_image> from_stream(SCP<IStream> poStreamSP);
	static SCP<ng_image> from_resource(HINSTANCE hInstance,LPCTSTR lpName);
	static SCP<ng_image> from_resource(HINSTANCE hInstance,long nResId);

	~ng_image();
	ng_xdist get_width() const;
	ng_ydist get_height() const;
	long get_frame_count() const;
private:
	ng_image();
	void read_from_file(LPCTSTR lpFileName);
	void read_from_stream(SCP<IStream> poStreamSP);
	void read_from_resource(HINSTANCE hInstance,LPCTSTR lpName);
	void read_from_resource(HINSTANCE hInstance,long nResId);

	ng_image_impl * m_poImageImpl;

	friend class ng_dc;
};

/* 
	'¿adanie obrazka'
*/
class ng_image_request : public CInterface__
{
public:
	ng_image_request(){}
	virtual void on_image_ready(bool bPositive) = 0;	//notification positive or negative
};
//-------------------------------------------------------------------------
//	display (device) related clases
//-------------------------------------------------------------------------

class ng_ic		//information context
{
public:
	ng_ic(HDC hDC);
	~ng_ic();

	ng_size measure_string(LPCTSTR lpText,long nCount,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings = NULL);
	ng_size measure_string(const ng_string & roString,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings = NULL);

	HDC get_hdc() const;

	long get_color_depth() const;
	void reinit();
protected:
	ng_ic();
	void attach(ng_dc_impl * poDCImpl);
	void detach();
	ng_dc_impl * m_poDCImpl;

	friend class ng_double_buffer;
	friend class ng_region;
};

const long NG_FRAME_LEFT = 0x00000001;
const long NG_FRAME_TOP	 = 0x00000002;
const long NG_FRAME_RIGHT= 0x00000004;
const long NG_FRAME_BOTTOM=0x00000008;
const long NG_FRAME_ALL	 = 0x0000000F;

const long NG_FRAME_EDGE_FLAT		 = 0x00000000;
const long NG_FRAME_EDGE_RAISEDOUTER = 0x00000100;
const long NG_FRAME_EDGE_SUNKENOUTER = 0x00000200;
const long NG_FRAME_EDGE_RAISEDINNER = 0x00000400;
const long NG_FRAME_EDGE_SUNKENINNER = 0x00000800;
const long NG_FRAME_EDGE_ROUNDED_XP	 = 0x00001000;		//button frame
const long NG_FRAME_EDGE_ROUNDED_XP2 = 0x00002000;		//pressed button frame
const long NG_FRAME_EDGE_ROUNDED_FLAT= 0x00004000;		//flat rounder frame

const long NG_FRAME_EDGE_RAISED = NG_FRAME_EDGE_RAISEDOUTER | NG_FRAME_EDGE_RAISEDINNER;
const long NG_FRAME_EDGE_BUMP	= NG_FRAME_EDGE_RAISEDOUTER | NG_FRAME_EDGE_SUNKENINNER;
const long NG_FRAME_EDGE_ETCHED = NG_FRAME_EDGE_SUNKENOUTER | NG_FRAME_EDGE_RAISEDINNER;
const long NG_FRAME_EDGE_SUNKEN = NG_FRAME_EDGE_SUNKENOUTER | NG_FRAME_EDGE_SUNKENINNER;

const long NG_FRAME_LINE_SOLID		 = (PS_SOLID << 16) + 0x00000000;
const long NG_FRAME_LINE_DASH		 = (PS_DASH << 16)  + NG_FRAME_LINE_SOLID;
const long NG_FRAME_LINE_DOT		 = (PS_DOT  << 16)  + NG_FRAME_LINE_SOLID;

enum ng_image_scaling_mode
{
	ngis_original,
	ngis_stretch,
	ngis_clip,
};

enum ng_image_filter
{
	ngif_none,		//no filter
	ngif_col2tran,	//replace color with transparency
	ngif_disable,	//"disabled look"
	ngif_semitrans,	//make image with 50% alpha
};

class ng_dc : public ng_ic		//display context
{
public:
	ng_dc(HDC hDC);
	~ng_dc();

	//drawing primitives
	void frame_rect(const ng_rect & roDURect,long nFrameWidthPx,const ng_color & framecolor,long nMask);
	void frame_area(const ng_area & roDUArea,long nFrameWidthPx,const ng_color & framecolor);

	void fill_rect_hg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const;
	void fill_rect_vg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const;
	void print_text(const ng_rect & roDURect,LPCTSTR lpText,long nCount,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const;
	void print_text(const ng_rect & roDURect,const ng_string & roString,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const;
	void draw_image(const ng_rect & roDURect,const ng_size & roDUScroll,SCP<ng_image> poImageSP,
		ng_image_scaling_mode eScalingMode,ng_image_filter eFilters);
	void draw_image_frame(const ng_rect & roDURect,SCP<ng_image> poImageSP,ng_image_scaling_mode eScalingMode,long nFrame);
	void patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP);
	void bitblt(const ng_point & roDestPoint,const ng_size & roSize,const ng_point & roSrcPoint,DWORD dwROP);

	//clipping
	void set_clip_region(const ng_region & roRegion,int nMode);
	bool in_clip_region(const ng_area & roArea) const;
	bool in_clip_region(const ng_rect & roRect) const;

private:
	ng_dc();

	friend class ng_double_buffer;

#ifdef _DEBUG
	void _reset_stats();
	
	long	m_nFrameRectCalls;
	long	m_nFrameAreaCalls;
	long	m_nFillRectCalls;
	long	m_nPrintTextCalls;
	long	m_nDrawImageCalls;
	long	m_nPatBltCalls;
	long	m_nBitBltCalls;
	long	m_nSetClipRegionCalls;
	long	m_nInClipRegionCalls;

	friend class ng_dc_statistics;
#endif
};

#ifdef _DEBUG
class ng_dc_statistics
{
public:
	ng_dc_statistics(ng_dc & roDC,const ng_rect & roPaintRect) :
		m_roDC(roDC),
		m_oPaintRect(roPaintRect)
	{
		m_roDC._reset_stats();
	}
	~ng_dc_statistics();
private:
	ng_rect m_oPaintRect;
	ng_dc & m_roDC;
};
#endif

class ng_double_buffer
{
public:
	ng_double_buffer(ng_dc & roDC,const ng_rect & roDURect);
	~ng_double_buffer();
	ng_dc & get_dc()
	{
		return m_oDC;
	}
	void copy_from(ng_dc & roSrcDC,const ng_point & roLeftUpperPoint);
	void copy_to(ng_dc & roDestDC,const ng_point & roLeftUpperPoint);
private:
	ng_double_buffer_impl * m_poDBImpl;
	ng_dc	m_oDC;
};

class ng_session
{
public:
	ng_session();
	~ng_session();
	void init();
	void done();
private:
	ng_session_impl * m_poSessionImpl;
};

//prze³¹czanie trybu grafiki na 'szybk¹'
bool _is_fast_graphics();
void _set_fast_graphics(bool bFast);


class CDCGetReleaseHolder
{
public:
	CDCGetReleaseHolder(HWND hWnd) :
		m_hWnd(hWnd)
	{
		ASSERT(m_hWnd != HWND(NULL));
		m_hDC = ::GetDC(m_hWnd);
	};
	~CDCGetReleaseHolder()
	{
		::ReleaseDC(m_hWnd,m_hDC);
	}
	HDC get_hdc() const
	{
		return m_hDC;
	}
private:
	HWND m_hWnd;
	HDC	 m_hDC;
};

//------------------------------------------------------------------------------------
//---------------------------------------- scaling helper ----------------------------
//------------------------------------------------------------------------------------

static inline __int64 __int64_div_round(__int64 nN,__int64 nD)
{
	ASSERT(nD != 0);
	return (nN + (nD / 2)) / nD;
}

class ng_scaling
{
public:
	ng_scaling() :
		m_xWindowExt(2540),
		m_yWindowExt(2540),
		m_xViewportExt(96),
		m_yViewportExt(96),
		m_nZoom(100)
	{
	}
	
	//--------- zamiana z external na internal (internal to nie DU) -------------------
	ng_xcoord x_to_du(ng_xcoord xLU) const
	{
		ASSERT(m_xWindowExt != 0);
		return ng_xcoord(__int64_div_round(__int64(xLU) * __int64(m_nZoom) *__int64(m_xViewportExt),100 * __int64(m_xWindowExt)));
	}
	ng_ycoord y_to_du(ng_ycoord yLU) const
	{
		ASSERT(m_yWindowExt != 0);
		return ng_ycoord(__int64_div_round(__int64(yLU) * __int64(m_nZoom) * __int64(m_yViewportExt),100 * __int64(m_yWindowExt)));
	}
	ng_xdist dx_to_du(ng_xdist dxLU) const
	{
		ASSERT(m_xWindowExt != 0);
		return ng_xdist(__int64_div_round(__int64(dxLU) * __int64(m_nZoom) * __int64(m_xViewportExt),100 * __int64(m_xWindowExt)));
	}
	ng_ydist dy_to_du(ng_ydist dyLU) const
	{
		ASSERT(m_yWindowExt != 0);
		return ng_ydist(__int64_div_round(__int64(dyLU) * __int64(m_nZoom) * __int64(m_yViewportExt),100 * __int64(m_yWindowExt)));
	}

	//--------- zamiana z internal na external -------------------
	ng_xcoord du_to_x(ng_xcoord xLU) const
	{
		ASSERT(m_xWindowExt != 0);
		return ng_xcoord(__int64_div_round(__int64(xLU) * 100 * __int64(m_xWindowExt),__int64(m_nZoom) *__int64(m_xViewportExt)));
	}
	ng_ycoord du_to_y(ng_ycoord yLU) const
	{
		ASSERT(m_yWindowExt != 0);
		return ng_ycoord(__int64_div_round(__int64(yLU) * 100 * __int64(m_yWindowExt),__int64(m_nZoom) * __int64(m_yViewportExt)));
	}
	ng_xdist du_to_dx(ng_xdist dxLU) const
	{
		ASSERT(m_xWindowExt != 0);
		return ng_xdist(__int64_div_round(__int64(dxLU) * 100 * __int64(m_xWindowExt),__int64(m_nZoom) * __int64(m_xViewportExt)));
	}
	ng_ydist du_to_dy(ng_ydist dyLU) const
	{
		ASSERT(m_yWindowExt != 0);
		return ng_ydist(__int64_div_round(__int64(dyLU) * 100 * __int64(m_yWindowExt),__int64(m_nZoom) * __int64(m_yViewportExt)));
	}

	//------------ zamiana iloœci pixeli na external (bez uwzglêdniania zooma) ------------------
	// do automatycznego definiowania rozmiarów obiektów
	//
	long __zoomize(long nNotZoomedValue) const
	{
		return long(nNotZoomedValue * m_nZoom / 100);
	}
	void set_zoom(long nZoom)
	{
		m_nZoom = nZoom;
	}
	long get_zoom() const
	{
		return m_nZoom;
	}
private:
	long	m_nZoom;
	const long	m_xWindowExt;
	const long	m_yWindowExt;
	long	m_xViewportExt;
	long	m_yViewportExt;
};

//-------------------------- inlines -------------------------------------------
#ifdef _DEBUG
inline void ng_dc::_reset_stats()
{
	m_nFrameRectCalls = 0;
	m_nFrameAreaCalls = 0;
	m_nFillRectCalls = 0;
	m_nPrintTextCalls = 0;
	m_nDrawImageCalls = 0;
	m_nPatBltCalls = 0;
	m_nBitBltCalls = 0;
	m_nSetClipRegionCalls = 0;
	m_nInClipRegionCalls = 0;
}

inline ng_dc_statistics::~ng_dc_statistics()
{
	TRACE("-------- PAINT STATISTICS ------------\n");
	TRACE("rect left,top=(%d,%d), size=(%d,%d)\n",
		m_oPaintRect.get_left(),m_oPaintRect.get_top(),
		m_oPaintRect.get_width(),m_oPaintRect.get_height());
	if(m_roDC.m_nFrameRectCalls != 0)
	{
		TRACE("framed rects %d\n",m_roDC.m_nFrameRectCalls);
	}
	if(m_roDC.m_nFrameAreaCalls != 0)
	{
		TRACE("framed areas %d\n",m_roDC.m_nFrameAreaCalls);
	}
	if(m_roDC.m_nFillRectCalls != 0)
	{
		TRACE("filled rects %d\n",m_roDC.m_nFillRectCalls);
	}
	if(m_roDC.m_nPrintTextCalls != 0)
	{
		TRACE("printed texts %d\n",m_roDC.m_nPrintTextCalls);
	}
	if(m_roDC.m_nDrawImageCalls != 0)
	{
		TRACE("drawn images %d\n",m_roDC.m_nDrawImageCalls);
	}
	if(m_roDC.m_nPatBltCalls != 0)
	{
		TRACE("pattern blits %d\n",m_roDC.m_nPatBltCalls);
	}
	if(m_roDC.m_nBitBltCalls != 0)
	{
		TRACE("bit blits %d\n",m_roDC.m_nBitBltCalls);
	}
	if(m_roDC.m_nSetClipRegionCalls != 0)
	{
		TRACE("clips set %d\n",m_roDC.m_nSetClipRegionCalls);
	}
	if(m_roDC.m_nInClipRegionCalls != 0)
	{
		TRACE("in clip tests %d\n",m_roDC.m_nInClipRegionCalls);
	}
	TRACE("--------------------------------------\n");
}
#endif

inline ng_point & ng_point::offset(const ng_size & roSize)
{
	m_x += roSize.get_dx();
	m_y += roSize.get_dy();
	
	return (*this);
}

inline ng_point & ng_point::offset(ng_xdist xdx,ng_ydist ydy)
{
	m_x += xdx;
	m_y += ydy;

	return (*this);
}

inline ng_size ng_point::distance(const ng_point & roPt) const
{
	return ng_size(get_x() - roPt.get_x(),get_y() - roPt.get_y());
}

inline void ng_dc::print_text(const ng_rect & roLURect,const ng_string & roString,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const
{
	print_text(roLURect,roString,roString.GetLength(),forecolor,rpoNGFontSP);
}

inline ng_size ng_ic::measure_string(const ng_string & roString,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings)
{
	return measure_string(roString,roString.GetLength(),nXAreaWidth,rpoNGFontSP,pMaxChars,pArrayOfPartialStrings);
}

inline long ng_ic::get_color_depth() const
{
	//OS_API_CALL
	return ::GetDeviceCaps(get_hdc(), PLANES) * ::GetDeviceCaps(get_hdc(), BITSPIXEL); 
}

inline ng_font::ng_font(SCP<IFont> & rpoFontSP,bool bItalic) :
	m_poFontSP(rpoFontSP),
	m_bItalic(bItalic)
{
	ASSERT(rpoFontSP.PointsObject());
	//OS_API_CALL
	HRESULT hr = rpoFontSP->get_hFont(&m_hFont);
	if(hr == S_OK)
	{
		hr = rpoFontSP->AddRefHfont(m_hFont);
		if(hr == S_OK)
		{
			return;
		}
	}
	ThrowNavoException(ERCO_FONTHOLDER_UNABLE_TO_INIT,IDPAGE_NOTAVAILABLE);
}

inline ng_font::~ng_font()
{
	//OS_API_CALL
	VERIFY(S_OK == m_poFontSP->ReleaseHfont(m_hFont));
}

inline void ng_rect::normalize()
{
	if (m_xleft > m_xright)
	{
		ng_xcoord xTemp = m_xleft;
		m_xleft = m_xright;
		m_xright = xTemp;
	}
	if (m_ytop > m_ybottom)
	{
		ng_ycoord yTemp = m_ytop;
		m_ytop = m_ybottom;
		m_ybottom = yTemp;
	}
	ASSERT(is_normal());
}

inline void ng_rect::union_with(const ng_rect & roProst)
{
	ASSERT(is_normal());
	ASSERT(roProst.is_normal());

	if(!roProst.is_empty())		//unia z pustym nic nie zmienia
	{
		if(is_empty())
		{
			(*this) = roProst;	//jeœli my jesteœmy puœci ->zast¹p
		}
		else	//oba niepuste ->unionuj
		{
			m_xleft	 = min(m_xleft,		roProst.m_xleft);
			m_xright = max(m_xright,	roProst.m_xright);
			m_ytop	 = min(m_ytop  ,	roProst.m_ytop);
			m_ybottom= max(m_ybottom,	roProst.m_ybottom);
		}
	}
}

inline void ng_rect::intersect_with(const ng_rect & roInRect)
{
	ASSERT(is_normal());
	ASSERT(roInRect.is_normal());
	m_xleft	 = max(m_xleft,		roInRect.m_xleft);
	m_xright = min(m_xright,	roInRect.m_xright);
	m_ytop	 = max(m_ytop  ,	roInRect.m_ytop);
	m_ybottom= min(m_ybottom,	roInRect.m_ybottom);

	if(get_width() < 0)
	{
		set_width(0);
	}
	if(get_height() < 0)
	{
		set_height(0);
	}

	ASSERT(is_normal());
}

inline bool ng_rect::merge_adjacent(const ng_rect & roProst)
{
	//test: one below second
	if(get_left() == roProst.get_left() && get_right() == roProst.get_right())
	{
		if(get_bottom() + 1 == roProst.get_top())
		{
			set_bottom(roProst.get_bottom());
			return true;
		}
		else
		{
			if(roProst.get_bottom() + 1 == get_top())
			{
				set_top(roProst.get_top());
				return true;
			}
		}
	}
	//test: one right second
	if(get_top() == roProst.get_top() && get_bottom() == roProst.get_bottom())
	{
		if(get_right() + 1 == roProst.get_left())
		{
			set_right(roProst.get_right());
			return true;
		}
		else
		{
			if(roProst.get_right() + 1 == get_left())
			{
				set_left(roProst.get_left());
				return true;
			}
		}
	}
	return false;
}

inline void ng_area::operator+=(const ng_rect & roRect)
{
	if(roRect.is_empty())
	{
		return;
	}
	
	ASSERT(roRect.get_bottom() < 10000000 && roRect.get_top() < 10000000);

	for(long nIndex = 0; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		switch(rect_containment(roRect,m_oRectArray[ nIndex ]))
		{
		case 1:		//nowy le¿y w starym
			return;		
		case 2:		//stary le¿y w nowym - zast¹p
			m_oRectArray[ nIndex ] = roRect;
			return;
		}
	}
	m_oRectArray.Add(roRect);
}

inline void ng_area::operator+=(const ng_area & roArea)
{
	for(int nIndex = 0; nIndex < roArea.m_oRectArray.GetSize(); nIndex++ )
	{
		(*this) += roArea.m_oRectArray[ nIndex ];
	}
}

inline void ng_area::intersect_with(const ng_rect & roInRect,ng_area & roOutputArea) const
{
	for(int nIndex = 0; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		ng_rect oRect = m_oRectArray[ nIndex ];
		oRect.intersect_with(roInRect);
		if(!oRect.is_empty())
		{
			roOutputArea += oRect;
		}
	}
}

inline void ng_area::get_bounding_rect(ng_rect & roRect) const
{
	if(m_oRectArray.GetSize() == 0)
	{
		roRect = ng_rect();
		return;
	}
	else
	{
		roRect = m_oRectArray[0];
	}
	for( int nIndex = 1; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		roRect.union_with(m_oRectArray[nIndex]);
	}
}

inline bool ng_area::is_inside(const ng_point & roPoint) const
{
	for(int nIndex = 0; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		if(m_oRectArray[nIndex].is_inside(roPoint))
		{
			return true;
		}
	}
	return false;
}

inline bool ng_area::is_intersect(const ng_rect & roRect) const
{
	for(int nIndex = 0; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		if(m_oRectArray[nIndex].is_intersect(roRect))
		{
			return true;
		}
	}
	return false;
}

inline void ng_area::offset(const ng_size & roSize)
{
	if(roSize == ng_size(0,0))
	{
		return;
	}
	for(int nIndex = 0; nIndex < m_oRectArray.GetSize(); nIndex++ )
	{
		m_oRectArray[nIndex].offset(roSize);
	}
}

inline long rect_containment(const ng_rect & roProst1,const ng_rect & roProst2)
{
	if(roProst1.get_left() >= roProst2.get_left()  && roProst1.get_top() >= roProst2.get_top()  &&
	   roProst1.get_right() <=	roProst2.get_right() && roProst1.get_bottom() <= roProst2.get_bottom())
	{
		return +1;
	}
	if(roProst2.get_left() >= roProst1.get_left() && roProst2.get_top() >= roProst1.get_top()  &&
	   roProst2.get_right() <=	roProst1.get_right() && roProst2.get_bottom() <= roProst1.get_bottom())
	{
		return +2;
	}
	return 0;
}

#else
#error __FILE__ already included
#endif

