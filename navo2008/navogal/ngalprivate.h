/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer

	private (implementation) definitions
*/

#ifndef _NGALPRIVATE_H_
#define _NGALPRIVATE_H_

const long MMnaCal = 2540;

/*
	plain_gdi - dzia³a bez korzystania z GDI+ (wymagana obecnoœæ .DLL ze wzglêdu na importy funkcji
	
	gdiplus_normal - korzysta z GDI+, w tym zakresie gdzie jest ono lepsze. Pomija kosztowne 'efekty'
					 mixed mode

	gdiplus_high   - korzysta z GDI+, tworzy najlepsze dostêpne 'efekty'
					 full GDI+ mode
					 NIE JEST W PE£NI ZAIMPLEMENTOWANY	

	w trybie gdiplus_normal
		cngal_context - korzysta zarówno z HDC jaki GDI+
		cngal_image	  - korzysta g³ównie z GDI+
		cngal_region  - korzysta g³ównie z HDC
*/

class cngal_session
{
public:
	cngal_session();
	~cngal_session();
	void init(eNavoGraphicsMode eNGMode);
	void done();
	eNavoGraphicsMode _get_mode() const
	{
		return m_eNGMode;
	}
	long _get_Windows_scaling_factor() const
	{
		//ASSERT(_get_mode() == plain_gdi);
		return m_raw_WindowsScalingFactor;
	}
private:
   GdiplusStartupInput	m_gdiplusStartupInput;
   ULONG_PTR			m_gdiplusToken;
   eNavoGraphicsMode	m_eNGMode;
   long					m_raw_WindowsScalingFactor;
};

extern cngal_session _g_ngal_session;

class CDCAttachHolder;
class CMapModeHolder;

class cngal_context
{
public:
	cngal_context(HDC hDC);
	~cngal_context()
	{
	}
	CSize get_string_size(const CString & roString,SCP<IFont> & rpIFontSP);
	CSize measure_string(LPCTSTR lpString,long nStrLen,long nAreaWidth,SCP<IFont> & rpIFontSP,
		/*out */ long * pMaxChars,/*out*/ int * pArrayOfPartialStrings = NULL);
	void frame_rect(const _rect & roRect,long nFrameWidth,_colordesc framecolor,long nMask);
	void frame_RA(const CRepaintArea & roRepaintArea,long nPixelFrameWidth,_colordesc framecolor);
	void fill_rect_hg(const _rect & roRect,_colordesc fillcolor1,_colordesc fillcolor2);
	void print_text(const _rect & roRect,LPCTSTR lpText,long nCount,_colordesc forecolor,_colordesc backcolor,
		SCP<IFont> & rpIFontSP);
	bool is_visible(const CRepaintArea & roRepaintArea);
	long _getzoom_factor();
	HDC _get_raw_HDC() const
	{
		return m_hDC;
	}
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

	void set_clip_region(const CNAVORegion & roNAVORegion,int nMode);
	void get_clip_region(CNAVORegion & roNAVORegion);

private:
	HDC		m_hDC;
};


class CNAVOGdiPlusImage;
class cngal_image
{
public:
	cngal_image();
	~cngal_image();
	void read_from_file(const CString & roFileNameString);
	void read_from_stream(SCP<IStream> poStreamSP);
	long get_width() const;
	long get_height() const;
	void draw(cngal_context * poContext,const _rect & roDestRect,DWORD dwROP,eImageDrawMode eMode);
	CPalette * get_palette() const;
	CBitmap * clone_bitmap();
private:
	Image * _any_image_ptr() const;
	void _raw_draw_plus(Graphics * poGraphics,Image * poImage,Rect destRect,eImageDrawMode eMode,ImageAttributes * pIA);
	Image * _plus_convert_2_normal();
	Image * _plus_convert_2_disabled();

	Bitmap * _create_image_copy();

	CNAVOGdiPlusImage *	m_pNGPImage;	//implementation in GDI++
	Bitmap *			m_poNormalBitmap;
	Bitmap *			m_poDisabledBitmap;
};

class cngal_region
{
public:
	cngal_region() :
		m_poRegion(NULL),
		m_poRgn(NULL)
	{
	}
	~cngal_region()
	{
		done();
	}
	void from_RA(const CRepaintArea & roRepaintArea);
	void from_rect(const _rect & roRect);
	void combine(cngal_region & roRegion1,cngal_region & roRegion2,int nMode);

	HRGN _get_raw_hrgn() const
	{
		ASSERT(m_poRgn);
		return m_poRgn->operator HRGN();
	}
	Region * _get_raw_region() const
	{
		ASSERT(m_poRegion);
		return m_poRegion;
	}
	bool isinited() const
	{
		return (m_poRegion != NULL || m_poRgn != NULL);
	}
	void initempty()
	{
		done();
		if(_g_ngal_session._get_mode() == gdiplus_high)
		{
			m_poRegion = new Region();
			m_poRegion->MakeEmpty();
		}
		else
		{
			m_poRgn = new CRgn();
			m_poRgn->CreateRectRgn(0,0,0,0);
		}
	}
	void done()
	{
		if(m_poRegion != NULL)
		{
			delete m_poRegion;
			m_poRegion = NULL;
		}
		if(m_poRgn != NULL)
		{
			m_poRgn->DeleteObject();
			delete m_poRgn;
			m_poRgn = NULL;
		}
	}
private:
	Region	* m_poRegion;
	CRgn	* m_poRgn;
};

class CMapModeHolder
{
public:
	CMapModeHolder(CDC & roDC,int nMapMode) :
		m_roDC(roDC),
		m_oViewportExt(roDC.GetViewportExt()),
		m_oViewportOrg(roDC.GetViewportOrg()),
		m_oWindowExt(roDC.GetWindowExt()),
		m_oWindowOrg(roDC.GetWindowOrg())
	{
		m_nPrevMapMode = roDC.SetMapMode(nMapMode);
	}
	~CMapModeHolder()
	{
		m_roDC.SetMapMode(m_nPrevMapMode);
		m_roDC.SetWindowExt(m_oWindowExt);
		m_roDC.SetViewportExt(m_oViewportExt);
		m_roDC.SetWindowOrg(m_oWindowOrg);
		m_roDC.SetViewportOrg(m_oViewportOrg);
	}
	const CPoint & GetViewPortOrg() const
	{
		return m_oViewportOrg;
	}
private:
	CDC &	m_roDC;
	CSize	m_oViewportExt;
	CPoint	m_oViewportOrg;
	CSize	m_oWindowExt;
	CPoint	m_oWindowOrg;
	int		m_nPrevMapMode;
};

// podmiana obiektu (dc.SelectObject) holder
class CGDIHolder
{
public:
	CGDIHolder(CDC & roDC, HGDIOBJ hNewObject):
		m_hDC(roDC)
	{
		m_hOldObject = ::SelectObject(roDC, hNewObject);
		ASSERT(m_hOldObject);
		if(m_hOldObject == hNewObject)	//taki sam to dtor nic nie robi
		{
			m_hOldObject = NULL;
		}
	};
	~CGDIHolder()
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

class CIFontHolder
{
public:
	CIFontHolder(SCP<IFont> & rpIFontSP):
		m_pIFontSP(rpIFontSP)
	{
		ASSERT(rpIFontSP.PointsObject());
		HRESULT hr = m_pIFontSP->get_hFont(&m_hFont);
		if(hr == S_OK)
		{
			hr = m_pIFontSP->AddRefHfont(m_hFont);
			if(hr == S_OK)
			{
				return;
			}
		}
		ThrowNavoException(ERCO_FONTHOLDER_UNABLE_TO_INIT,IDPAGE_NOTAVAILABLE);
		
	}
	~CIFontHolder()
	{
		m_pIFontSP->ReleaseHfont(m_hFont);
	}
	virtual operator HFONT() const
	{
		return m_hFont;
	}
private:
	HFONT		m_hFont;
	SCP<IFont>	m_pIFontSP;
};

class CDCAttachHolder
{
public:
	CDCAttachHolder(HDC hDC)
	{
		m_oDC.Attach(hDC);
	}
	CDC & GetDC()
	{
		return m_oDC;
	}
	~CDCAttachHolder()
	{
		m_oDC.Detach();
	}
private:
	CDC m_oDC;
};

class CGraphicsHolder	//GDI+ Graphics
{
public:
	CGraphicsHolder(HDC hDC) :
		m_poMMH(NULL),
		m_pGraphics(NULL)
	{
		m_oDC.Attach(hDC);
		long nFactor = (m_oDC.GetWindowExt().cy * 100 * _g_ngal_session._get_Windows_scaling_factor()) / MMnaCal;
		ASSERT(nFactor > 0);
		m_poMMH		= new CMapModeHolder(m_oDC,MM_TEXT);
		m_pGraphics	= new Graphics(hDC);
		m_pGraphics->SetPageUnit(UnitMillimeter);
		m_pGraphics->SetPageScale(1.0f / nFactor);

		if(_g_ngal_session._get_mode() == gdiplus_high)
		{
			//high quality settings
			m_pGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
			m_pGraphics->SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
		}
	}
	~CGraphicsHolder()
	{
		delete m_pGraphics;
		delete m_poMMH;
		m_oDC.Detach();
	}
	Graphics & _graphics() 
	{
		ASSERT(m_pGraphics);
		return *m_pGraphics;
	}
	REAL pixel2LU(long nPixels) const
	{
		ASSERT(m_pGraphics);
		return REAL(nPixels) * REAL(MMnaCal) / m_pGraphics->GetDpiX();
	}
private:
	CDC					m_oDC;
	CMapModeHolder  *	m_poMMH;
	CDCAttachHolder *	m_poDCAH;
	Graphics *			m_pGraphics;
};

//------------------------------------------------------------------------------------------
// class inlines
//------------------------------------------------------------------------------------------
void _raw_navo_framerect_dc(CDC & roDC,const _rect & roRect,long nWidth,long nMask);
void _raw_navo_fillrect(CDC & roDC,const _rect & roRect);
void _raw_navo_textout(CDC & roDC,const _rect & roRect,LPCTSTR lpText,long nCount,bool bBackGround);
void _rect2Rect(const _rect & ro_rect,Rect & roRect);
void _rect2RectF(const _rect & ro_rect,RectF & roRectF);
Rect _rect2Rect(const _rect & ro_rect);

inline Color _color2Color(_colordesc color)
{
	return Color(BYTE(BYTE(255) - color._alpha()),color._red(),color._green(),color._blue());
}

inline cngal_context::cngal_context(HDC hDC) :
	m_hDC(hDC)
{
	ASSERT(m_hDC);
}

inline HWND cngal_context::_get_window() const
{
	ASSERT(_g_ngal_session._get_mode() != gdiplus_high);	//w tym trybie nie powinien siê pytaæ (takie jest za³o¿enie)

	ASSERT(m_hDC != NULL);
	return ::WindowFromDC(m_hDC);
}

//converts argument to logical units (like DPtoLP)
inline void cngal_context::toLU(POINT * pDUPoint) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		VERIFY(::DPtoLP(m_hDC, pDUPoint, 1));
	}
}

inline void cngal_context::toLU(RECT * pDURect) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		VERIFY(::DPtoLP(m_hDC, (LPPOINT)pDURect, 2));
	}
}

inline void cngal_context::toLU(SIZE * pDUSize) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		CDCAttachHolder(m_hDC).GetDC().DPtoLP(pDUSize);
	}
}

//converts argument to device units (like LPtoDP)
inline void cngal_context::toDU(POINT * pDUPoint) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		VERIFY(::LPtoDP(m_hDC, pDUPoint, 1));
	}
}

inline void cngal_context::toDU(RECT * pDURect) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		VERIFY(::LPtoDP(m_hDC, (LPPOINT)pDURect, 2));
	}
}

inline void cngal_context::toDU(SIZE * pDUSize) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		CDCAttachHolder(m_hDC).GetDC().LPtoDP(pDUSize);
	}
}

inline void cngal_context::toDU(const CRepaintArea & roLURA,CRepaintArea & roDURA) const
{
	if(_g_ngal_session._get_mode() == gdiplus_high)
	{
		ASSERT(false);
		//to_do: gdiplus_high
	}
	else
	{
		roDURA.Empty();
		CDCAttachHolder oDCAH(m_hDC);
		for(long iter = 0; iter < roLURA.m_oProstArray.GetSize(); iter ++)
		{
			_rect oTmpRect = roLURA.m_oProstArray[iter];
			toDU((LPRECT)&oTmpRect);
			oTmpRect.NormalizeRect();
			roDURA += oTmpRect;
		}
	}
}


//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// misc inlines
//------------------------------------------------------------------------------------------

inline void _rect2Rect(const _rect & ro_rect,Rect & roRect)
{
	roRect.X = ro_rect.left;
	roRect.Y = ro_rect.top;
	roRect.Width = ro_rect.Width();
	roRect.Height = ro_rect.Height();
}

inline void _rect2RectF(const _rect & ro_rect,RectF & roRectF)
{
	roRectF.X = REAL(ro_rect.left);
	roRectF.Y = REAL(ro_rect.top);
	roRectF.Width = REAL(ro_rect.Width());
	roRectF.Height = REAL(ro_rect.Height());
}

inline Rect _rect2Rect(const _rect & ro_rect)
{
	return Rect(ro_rect.left,ro_rect.top,ro_rect.Width(),ro_rect.Height());
}

//----------------------------------------------
//maluje ramkê w prostok¹cie (wspó³rzêdne logiczne LP) o gruboœci nWidth (liczba pixeli
//czyli wspó³rzêdne fizyczne (DP)
//u¿ywa aktualnego pen'a
//----------------------------------------------
inline void _raw_navo_framerect_dc(CDC & roDC,const _rect & roRectDP,long nWidth,long nMask)
{
	ASSERT(_g_ngal_session._get_mode() != gdiplus_high);	//w tym trybie nie powinien wo³aæ (takie jest za³o¿enie)

	POINT aPoints[4];
	aPoints[0].x = roRectDP.left;
	aPoints[0].y = roRectDP.top;
	aPoints[1].y = aPoints[0].y;
	aPoints[1].x = roRectDP.right-1;
	aPoints[2].x = aPoints[1].x;
	aPoints[2].y = roRectDP.bottom-1;
	aPoints[3].y = aPoints[2].y;
	aPoints[3].x = roRectDP.left;

	do
	{
		roDC.MoveTo(aPoints[0]);
		if(nMask & RN_FRAME_TOP)
		{
			roDC.LineTo(aPoints[1]);
		}
		else
		{
			roDC.MoveTo(aPoints[1]);
		}
		if(nMask & RN_FRAME_RIGHT)
		{
			roDC.LineTo(aPoints[2]);
		}
		else
		{
			roDC.MoveTo(aPoints[2]);
		}
		if(nMask & RN_FRAME_BOTTOM)
		{
			aPoints[3].x--;
			roDC.LineTo(aPoints[3]);
			aPoints[3].x++;
		}
		roDC.MoveTo(aPoints[3]);
		if(nMask & RN_FRAME_LEFT)
		{
			aPoints[0].y--;
			roDC.LineTo(aPoints[0]);
			aPoints[0].y++;
		}
		
		if(--nWidth <= 0)
		{
			break;
		}

		aPoints[0].x++;aPoints[0].y++;
		aPoints[1].x--;aPoints[1].y++;
		aPoints[2].x--;aPoints[2].y--;
		aPoints[3].x++;aPoints[3].y--;
	}
	while(true);
}

//----------------------------------------------
//wype³nia prostok¹t (wspó³rzêdne logiczne LP) aktualnym kolorem t³a (bkcolor)
//----------------------------------------------
inline void _raw_navo_fillrect(CDC & roDC,const _rect & roRect)
{
	ASSERT(_g_ngal_session._get_mode() != gdiplus_high);	//w tym trybie nie powinien wo³aæ (takie jest za³o¿enie)
	::ExtTextOut(roDC.m_hDC, 0, 0, ETO_OPAQUE, &roRect, NULL, 0, NULL);
}

//----------------------------------------------
//----------------------------------------------
inline void _raw_navo_textout(CDC & roDC,const _rect & roRect,LPCTSTR lpText,long nCount,bool bBackGround)
{
	ASSERT(_g_ngal_session._get_mode() != gdiplus_high);	//w tym trybie nie powinien wo³aæ (takie jest za³o¿enie)
	roDC.ExtTextOut(roRect.left,roRect.top,ETO_CLIPPED | (bBackGround ? ETO_OPAQUE: 0),&roRect,lpText,nCount,NULL);
}


#else
#error __FILE__ already included
#endif
