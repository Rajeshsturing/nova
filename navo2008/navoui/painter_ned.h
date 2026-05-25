/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	painter classes

*/

#ifndef _PAINTER_NED_H_
#define _PAINTER_NED_H_

namespace ned
{
class cned_element;

enum ened_spr		//should paint result
{
	spr_above,		//above paint area
	spr_inside,		//inside paint area
	spr_other,		//other position i.e. to the right
	spr_below		//below paint area
};

//-------------------------------------------------------------------------
// 'bazowy' kontekst malowania
//-------------------------------------------------------------------------
class cned_painter_
{
public:
	bool is_printing() const;		//hardcopy painting
	ng_dc & get_dc() const;
	bool in_clip_region(const ng_area & roArea) const;
	bool in_clip_region(const ng_rect & roRect) const;
	ng_ycoord paint_top() const;
	ng_ycoord paint_bottom() const;
	ng_xcoord paint_left() const;
	ng_xcoord paint_right() const;
	const ng_rect & paint_rect() const;

	cned_painter_(ng_dc & roDeviceDC,const ng_rect & roPaintRect);
	const cned_paint_param & get_paint_param() const;
	void set_paint_param(const cned_paint_param & roPaintParam);
	void mark_disabled(bool bDisabled,long & rnPrevCount);
	void restore_disabled(long nCount);
	bool is_effectively_disabled(const cned_element * poElement) const;

protected:
	cned_painter_(const cned_painter_ & roPainter);

	cned_paint_param	m_oPaintParam;
private:
	ng_dc & m_roDeviceDC;			//output DC
	ng_rect m_oPaintRect;
	long	m_nTreeDisableCount;			//czy jest w poddrzewie zadisableowanym
};

//-------------------------------------------------------------------------
// malowanie foreground
//-------------------------------------------------------------------------
class cned_fore_painter : public cned_painter_
{
public:
	void frame_rect(const ng_rect & roDURect,long nFrameWidthPx,const ng_color & framecolor,long nMask);
	void print_text(const ng_rect & roDURect,LPCTSTR lpText,long nCount,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP);
	void print_text(const ng_rect & roDURect,const ng_string & roString,const ng_color & forecolor,SCP<ng_font> & rpoNGFontSP);
	void patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP);
private:
	cned_fore_painter(const cned_painter_ & roPainter);

	friend class cned_page;
};

//-------------------------------------------------------------------------
// malowanie background
//-------------------------------------------------------------------------
class cned_back_painter : public cned_painter_
{
public:
	void fill_rect_hg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2);
	void fill_rect_vg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2);
private:
	cned_back_painter(const cned_painter_ & roPainter);

	friend class cned_page;
};

//--------------------------------------------------------------------
// scroll clipper
//--------------------------------------------------------------------
class cned_scroll_clipper
{
public:
	cned_scroll_clipper(const cned_painter_ & roPainter,const ng_rect & roScrollRect);
	~cned_scroll_clipper();
private:
	ng_dc &			m_roDC;
	ng_region		m_oSaveRegion;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_painter_::cned_painter_(ng_dc & roDeviceDC,const ng_rect & roPaintRect) :
	m_roDeviceDC(roDeviceDC),
	m_oPaintRect(roPaintRect),
	m_nTreeDisableCount(0)
{
}

inline cned_painter_::cned_painter_(const cned_painter_ & roPainter) :
	m_roDeviceDC(roPainter.get_dc()),
	m_oPaintParam(roPainter.m_oPaintParam),
	m_oPaintRect(roPainter.m_oPaintRect),
	m_nTreeDisableCount(roPainter.m_nTreeDisableCount)
{
}

inline ng_dc & cned_painter_::get_dc() const
{
	return m_roDeviceDC;
}

inline bool cned_painter_::is_printing() const
{
	return m_oPaintParam.is_printing();
}

inline bool cned_painter_::in_clip_region(const ng_area & roArea) const
{
	return get_dc().in_clip_region(roArea);
}

inline bool cned_painter_::in_clip_region(const ng_rect & roRect) const
{
	return get_dc().in_clip_region(roRect);
}

inline ng_ycoord cned_painter_::paint_top() const
{
	return paint_rect().get_top();
}

inline ng_ycoord cned_painter_::paint_bottom() const
{
	return paint_rect().get_bottom();
}

inline ng_xcoord cned_painter_::paint_left() const
{
	return paint_rect().get_left();
}

inline ng_xcoord cned_painter_::paint_right() const
{
	return paint_rect().get_right();
}

inline const ng_rect & cned_painter_::paint_rect() const
{
	return m_oPaintRect;
}

inline const cned_paint_param & cned_painter_::get_paint_param() const
{
	return m_oPaintParam;
}

inline void cned_painter_::set_paint_param(const cned_paint_param & roPaintParam)
{
	m_oPaintParam = roPaintParam;
}

inline void cned_painter_::mark_disabled(bool bDisabled,long & rnPrevCount)
{
	rnPrevCount = m_nTreeDisableCount;
	if(bDisabled)
	{
		m_nTreeDisableCount++;
	}
}

inline void cned_painter_::restore_disabled(long nCount)
{
	m_nTreeDisableCount = nCount;
}


//-------------------------------------------------------------------------
// malowanie foreground
//-------------------------------------------------------------------------
inline cned_fore_painter::cned_fore_painter(const cned_painter_ & roPainter) :
	cned_painter_(roPainter)
{
}

inline void cned_fore_painter::frame_rect(const ng_rect & roDURect,long nFrameWidthPx,const ng_color & roFrameColor,long nMask)
{
	get_dc().frame_rect(roDURect,nFrameWidthPx,
		roFrameColor.translate(m_oPaintParam.get_color_translation()),nMask);
}

inline void cned_fore_painter::print_text(const ng_rect & roDURect,LPCTSTR lpText,long nCount,const ng_color & roForeColor,SCP<ng_font> & rpoNGFontSP)
{
	get_dc().print_text(roDURect,lpText,nCount,
		roForeColor.translate(m_oPaintParam.get_color_translation()),rpoNGFontSP);
}

inline void cned_fore_painter::print_text(const ng_rect & roDURect,const ng_string & roString,const ng_color & roForeColor,SCP<ng_font> & rpoNGFontSP)
{
	get_dc().print_text(roDURect,roString,
		roForeColor.translate(m_oPaintParam.get_color_translation()),rpoNGFontSP);
}

inline void cned_fore_painter::patblt(const ng_rect & roDURect,const ng_color & roColor,DWORD dwROP)
{
	get_dc().patblt(roDURect,roColor.translate(m_oPaintParam.get_color_translation()),dwROP);
}

//-------------------------------------------------------------------------
// malowanie background
//-------------------------------------------------------------------------
inline cned_back_painter::cned_back_painter(const cned_painter_ & roPainter) :
	cned_painter_(roPainter)
{
}

inline void cned_back_painter::fill_rect_hg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2)
{
	get_dc().fill_rect_hg(roDURect,
		roBkColor1.translate(m_oPaintParam.get_color_translation()),
		roBkColor2.translate(m_oPaintParam.get_color_translation()));
}

inline void cned_back_painter::fill_rect_vg(const ng_rect & roDURect,const ng_color & roBkColor1,const ng_color & roBkColor2)
{
	get_dc().fill_rect_vg(roDURect,
		roBkColor1.translate(m_oPaintParam.get_color_translation()),
		roBkColor2.translate(m_oPaintParam.get_color_translation()));
}

//--------------------------------------------------------------------
// scroll clipper
//--------------------------------------------------------------------
inline cned_scroll_clipper::cned_scroll_clipper(const cned_painter_ & roPainter,
	const ng_rect & roScrollRect) :
	m_roDC(roPainter.get_dc())
{
	m_oSaveRegion.from_clip_region(m_roDC);
	ng_rect oReducedRect(roScrollRect);
	oReducedRect.intersect_with(roPainter.paint_rect());
	ng_region oRegion(oReducedRect);
	m_roDC.set_clip_region(oRegion,RGN_AND);
}

inline cned_scroll_clipper::~cned_scroll_clipper()
{
	m_roDC.set_clip_region(m_oSaveRegion,RGN_COPY);
}


}


#else
	#error __FILE__ already included
#endif
