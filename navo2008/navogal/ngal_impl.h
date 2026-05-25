/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions

	last revisited: 09.08.2002
*/

#ifndef _NGAL_IMPL_H_
#define _NGAL_IMPL_H_


class ng_session_impl
{
public:
	ng_session_impl();
	~ng_session_impl();
	void init();
	void done();
private:
   GdiplusStartupInput	m_gdiplusStartupInput;
   ULONG_PTR			m_gdiplusToken;
};

class ng_region_impl;

class ng_dc_impl
{
public:
	ng_dc_impl(HDC hDC) :
		m_xWindowOrg(0),
		m_yWindowOrg(0),
		m_hDC(hDC)
	{
		__setup();
	}

	HDC get_hdc() const
	{
		return m_hDC;
	}
	ng_xcoord get_x_window_org() const
	{
		return m_xWindowOrg;
	}
	ng_ycoord get_y_window_org() const
	{
		return m_yWindowOrg;
	}

	void frame_rect(ng_rect oDURect,long nFrameWidthPx,const ng_color & framecolor,long nMask);
	void frame_area(const ng_area & roDUArea,long nFrameWidthPx,const ng_color & framecolor);
	void fill_rect_hg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const;
	void fill_rect_vg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2) const;
	void print_text(const ng_rect & roDURect,LPCTSTR lpText,long nCount,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP) const;
	void draw_image(const ng_rect & roDURect,const ng_size & roDUScroll,ng_image_impl * poImageImpl,
		ng_image_scaling_mode eScalingMode,ng_image_filter eFilters);
	void draw_image_frame(const ng_rect & roLURect,ng_image_impl * poImageImpl,
		ng_image_scaling_mode eScalingMode,long nFrame);
	void set_clip_region(const ng_region_impl & roRegion,int nMode);
	bool in_clip_region(const ng_area & roArea) const;
	bool in_clip_region(const ng_rect & roRect) const;

	ng_size measure_string(LPCTSTR lpText,long nCount,ng_xdist nXAreaWidth,SCP<ng_font> & rpoNGFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings);
	void patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP) const;
	void bitblt(const ng_point & roDestPoint,const ng_size & roSize,const ng_point & roSrcPoint,DWORD dwROP);

	void reinit()
	{
		__setup();
	}
private:
	void set_x_window_org(ng_xcoord xWinOrg)
	{
		m_xWindowOrg = xWinOrg;
	}
	void set_y_window_org(ng_ycoord yWinOrg)
	{
		m_yWindowOrg = yWinOrg;
	}

	void __fill_rect_hvg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2,bool bVerticalGradient) const;

	long m_xWindowOrg;
	long m_yWindowOrg;

	HDC m_hDC;

	void __setup();

	friend class ng_double_buffer_impl; //for set_*_window_org
};

class ng_Graphics_holder
{
public:
	ng_Graphics_holder(HDC hDC)
	{
		m_poGraphics = new Graphics(hDC);
		m_poGraphics->SetPageUnit(UnitPixel);
		m_poGraphics->SetPageScale(1.0f);
	}
	~ng_Graphics_holder()
	{
		delete m_poGraphics;
	}
	Graphics & getplus()	//odstêpstwo od regu³y ale ma byæ krótkie
	{
		ASSERT(m_poGraphics);
		return *m_poGraphics;
	}
private:
	Graphics *	m_poGraphics;
};

class ng_double_buffer_impl
{
public:
	ng_double_buffer_impl(ng_dc_impl & roDC,const ng_rect & roDURect);
	~ng_double_buffer_impl();

	ng_dc_impl * get_memdc() const
	{
		return m_poMemDCImpl;
	}
	void copy_to(ng_dc_impl & roDestDC,const ng_point & roLeftUpperPoint);
	void copy_from(ng_dc_impl & roSrcDC,const ng_point & roLeftUpperPoint);
private:
	void _init_buffer(const ng_point & roOrgPoint);
	void _clear_buffer();

	ng_dc_impl &	m_roDCImpl;
	ng_dc_impl *	m_poMemDCImpl;
	HBITMAP			m_hBitmap;
	HGDIOBJ			m_hOldBitmap;
	ng_size			m_oDUSize;
};

class ng_ImagePlus : public Image
{
public:
	ng_ImagePlus() :
	  Image()
	{
	}
	static ng_ImagePlus * FromFile(LPCTSTR lpFileName)
	{
		Image * pImage = Image::FromFile(CBStr(lpFileName),FALSE);
		return static_cast<ng_ImagePlus *>(pImage);
	}
	static ng_ImagePlus * FromStream(SCP<IStream> poStreamSP)
	{
		Image * pImage = Image::FromStream(poStreamSP,FALSE);
		return static_cast<ng_ImagePlus *>(pImage);
	}
	static ng_ImagePlus * FromResource(HINSTANCE hInstance,LPCTSTR lpName)
	{
		Image * pBitmap = Bitmap::FromResource(hInstance,CBStr(lpName));
		return static_cast<ng_ImagePlus *>(pBitmap);
	}
	static ng_ImagePlus * FromResource(HINSTANCE hInstance,long nResId)
	{
		Image * pBitmap = Bitmap::FromResource(hInstance,MAKEINTRESOURCEW(nResId));
		return static_cast<ng_ImagePlus *>(pBitmap);
	}
	bool is_valid() const
	{
		return (nativeImage != NULL);
	}
};

class ng_image_impl
{
public:
	ng_image_impl();
	~ng_image_impl();
	void read_from_file(LPCTSTR lpFileName);
	void read_from_stream(SCP<IStream> poStreamSP);
	void read_from_resource(HINSTANCE hInstance,LPCTSTR lpName);
	void read_from_resource(HINSTANCE hInstance,long nResId);
	ng_xdist get_width() const;
	ng_ydist get_height() const;
	long get_frame_count() const;
	Image * get_semitrans();
	Image * get_normal();
	Image * get_disabled();
private:
	Bitmap * _create_image_copy();
	
	Image * _plus_original()
	{
		return m_pImagePlus;
	}
	Bitmap * _plus_convert_2_normal();
	Bitmap * _plus_convert_2_disabled();
	Bitmap * _plus_convert_2_semitrans();

	ng_ImagePlus *	m_pImagePlus;
	
	Image *	m_poNormalCB;
	Image *	m_poDisabledCB;
	Image *	m_poSemiTransCB;
	friend class ng_dc_impl;
};

class ng_region_impl
{
public:
	ng_region_impl();
	~ng_region_impl();
	void from_area(const ng_area & roDUArea);
	void from_rect(const ng_rect & roDURect);
	void from_region(const ng_region_impl & roDURgnImpl);
	void from_clip_region(ng_dc_impl & roDCImpl);
	void combine(ng_region_impl & roNAVORegion1,ng_region_impl & roNAVORegion2,int nMode);
	void offset(ng_xdist xOffset,ng_ydist yOffset);
	void empty();
	void invalidate(HWND hWnd);
	HRGN get_raw_hrgn() const
	{
		ASSERT(m_poRgn);
		return m_poRgn->operator HRGN();
	}
	bool is_empty() const;
private:
	void _initnew();
	CRgn * m_poRgn;
};

class ng_GDIObject_Holder
{
public:
	ng_GDIObject_Holder(HDC hDC, HGDIOBJ hNewObject):
		m_hDC(hDC)
	{
		//OS_API_CALL
		m_hOldObject = ::SelectObject(hDC, hNewObject);
		ASSERT(m_hOldObject);
		if(m_hOldObject == hNewObject)	//taki sam to dtor nic nie robi
		{
			m_hOldObject = NULL;
		}
	};
	~ng_GDIObject_Holder()
	{
		if(m_hOldObject != NULL)
		{
			::SelectObject(m_hDC, m_hOldObject); 
		}
	};

private:
	HGDIOBJ m_hOldObject;
	HDC m_hDC;
};

void rect2PlusRect(const ng_rect & ro_rect,Gdiplus::Rect & roPlusRect);


inline void rect2PlusRect(const ng_rect & ro_rect,Gdiplus::Rect & roPlusRect)
{
	roPlusRect.X = ro_rect.get_left();
	roPlusRect.Y = ro_rect.get_top();
	roPlusRect.Width = ro_rect.get_width();
	roPlusRect.Height = ro_rect.get_height();
}

inline Color ColorPlus(const ng_color & color)
{
	return Color(BYTE(BYTE(255) - color._alpha()),color._red(),color._green(),color._blue());
}

//---------------------------------------------------------------------------------
// region impl
//---------------------------------------------------------------------------------
inline ng_region_impl::ng_region_impl() :
	m_poRgn(NULL)
{
}

inline ng_region_impl::~ng_region_impl()
{
	empty();
}

inline void ng_region_impl::empty()
{
	if(m_poRgn != NULL)
	{
		m_poRgn->DeleteObject();
		delete m_poRgn;
		m_poRgn = NULL;
	}
}

inline bool ng_dc_impl::in_clip_region(const ng_area & roArea) const
{
	for(long iter = 0; iter <= roArea.m_oRectArray.GetUpperBound(); iter++)
	{
		if(in_clip_region(roArea.m_oRectArray[iter]))
		{
			return true;
		}
	}
	return false;
}


inline bool ng_dc_impl::in_clip_region(const ng_rect & roRect) const
{
	//tu jest znowu potrzeba powiêkszania poniewa¿ RectVisible nie uwzglêdnia prawego dolnego rogu
	
	RECT oWinRect = 
	{ 
		roRect.get_left()	- get_x_window_org(),
		roRect.get_top()	- get_y_window_org(),
		roRect.get_right()	- get_x_window_org() + 1,
		roRect.get_bottom() - get_y_window_org() + 1 
	};
	
	//OS_API_CALL
	if(::RectVisible(get_hdc(),&oWinRect))
	{
		return true;
	}
	else
	{
		/*
				jesli nie wierzysz to odkomentuj to poni¿ej:
				skoro prostok¹t nie jest widoczny, to równie¿ jego prawy dolny
				róg nie powinien byæ widoczny, a jest!!
		*/
		
		//ASSERT(!::PtVisible(get_hdc(),oWinRect.right,oWinRect.bottom));
		
		return false;
	}
}

inline void ng_region_impl::from_rect(const ng_rect & roDURect)
{
	empty();
	//MSDN: The region will be exclusive of the bottom and right edges - so include according our convention
	RECT oWinRect = { roDURect.get_left(), roDURect.get_top(), roDURect.get_right() + 1, roDURect.get_bottom() + 1 };
	m_poRgn = new CRgn();
	//OS_API_CALL
	m_poRgn->CreateRectRgnIndirect(&oWinRect);
}

inline void ng_region_impl::from_region(const ng_region_impl & roDURgnImpl)
{
	empty();
	_initnew();
	//OS_API_CALL
	m_poRgn->CombineRgn(roDURgnImpl.m_poRgn,NULL, RGN_COPY); 
}

inline bool ng_region_impl::is_empty() const
{
	if(m_poRgn == NULL)
	{
		return true;
	}
	else
	{
		RECT oDummyRect;
		//OS_API_CALL
		return (m_poRgn->GetRgnBox(&oDummyRect) == NULLREGION);
	}
}

inline void ng_region_impl::_initnew()
{
	if(m_poRgn == NULL)
	{
		m_poRgn = new CRgn();
		//OS_API_CALL
		m_poRgn->CreateRectRgn(0,0,0,0);
	}
}

#else
#error __FILE__ already included
#endif

