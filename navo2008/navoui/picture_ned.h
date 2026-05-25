/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_picture		/ <picture>
		kontrolka obrazka
*/

#ifndef _PICTURE_NED_H_
#define _PICTURE_NED_H_

namespace ned
{

class cned_picture : public cned_rect_element_
{
public:
//------ property GET -----------------
	const CSmartOleVariant & get_prop_imagesrc() const;
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	SCP<CHyperLinkInfo> & get_prop_hyperlink();
	long get_prop_animate() const;
	long get_prop_scaling_mode() const;
//------ property SET -----------------
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_imagesrc(const CSmartOleVariant & roImageSrcSOV);
	void set_prop_hyperlink(SCP<CHyperLinkInfo> poHyperLinkInfoSP);
	void set_prop_animate(long nAnimateInterval);
	void set_prop_scaling_mode(long nScalingMode);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();	//ustawia nie-dziedziczone property

//-------------- rendering support -------------------
	virtual void render(cned_renderer_ & roRenderer);
//-------------- attribute functions -------------------------
	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);
//--------------
	void on_image_ready(bool bPositive);	//notification positive or negative
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
private:
	cned_picture(cned_element_manager * poManager,const ned_ident idThis);
	void _load_picture();
//--------------
	void _get_image_rect(const ng_point & roCurrentPoint,ng_rect & roRect,bool bPrinting);
	void _copy_properties(cned_picture * poDestPicture);

	SCP<ng_image>		m_poImageSP;
	SCP<CHyperLinkInfo> m_poHyperLinkInfoSP;
	CSmartOleVariant	m_oIdImageSourceSOV;
	long				m_nFrameCount;
	long				m_nCurrentFrame;
	long				m_nAnimate;
	ng_image_scaling_mode m_eScalingMode;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_picture::cned_picture(cned_element_manager * poManager,const ned_ident idThis) :
	cned_rect_element_(poManager,ned_picture,idThis),
	m_nFrameCount(1),
	m_nCurrentFrame(0),
	m_nAnimate(0),
	m_eScalingMode(ngis_clip)
{
}

//------ property GET -----------------
inline const CSmartOleVariant & cned_picture::get_prop_imagesrc() const
{
	return m_oIdImageSourceSOV;
}

inline SCP<CHyperLinkInfo> & cned_picture::get_prop_hyperlink() 
{
	return m_poHyperLinkInfoSP;
}

inline long cned_picture::get_prop_animate() const
{
	return m_nAnimate;
}

inline void cned_picture::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = get_prop_imagesrc();
}

inline long cned_picture::get_prop_scaling_mode() const
{
	return long(m_eScalingMode);
}

//------ property SET -----------------
inline void cned_picture::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_imagesrc(roSOV);
}

inline void cned_picture::set_prop_imagesrc(const CSmartOleVariant & roImageSrcSOV)
{
	if(roImageSrcSOV == m_oIdImageSourceSOV)
	{
		return;
	}
	m_poImageSP = 0; //reset image
	m_oIdImageSourceSOV = roImageSrcSOV;

	if(is_normal_width_value(get_prop_extwidth()) && is_normal_height_value(get_prop_extheight()))
	{
		_invalidate_all_paint();	//niezbêdne gdy¿ rozmiar nie ulega zmianie i postrender tego nie wykryje
	}
	else
	{
		_size_info_dirty();			//mo¿e zmieniæ siê rozmiar
	}
	_vse_dirty();
}

inline void cned_picture::set_prop_hyperlink(SCP<CHyperLinkInfo> poHyperLinkInfoSP)
{
	if(poHyperLinkInfoSP.Get() == m_poHyperLinkInfoSP.Get())
	{
		return;
	}
	
	//notifikuj tylko gdy pojawi³ siê / znikn¹³ hyperlink - treœæ nie ma znaczenia
	//dla rozmiaru i wygl¹du

	bool bNotify = (m_poHyperLinkInfoSP.PointsObject() != poHyperLinkInfoSP.PointsObject());
	m_poHyperLinkInfoSP = poHyperLinkInfoSP;

	if(bNotify)
	{
		_invalidate_all_paint();
	}

	_vse_dirty();
}

inline void cned_picture::set_prop_scaling_mode(long nScalingMode)
{
	if(get_prop_scaling_mode() == nScalingMode)
	{
		return;
	}
	
	m_eScalingMode = ng_image_scaling_mode(nScalingMode);

	_invalidate_all_paint();
	_vse_dirty();
}

//--------------------------------------------------------------------
inline void cned_picture::_get_image_rect(const ng_point & roCurrentPoint,ng_rect & roRect,bool bWithMargins)
{
	roRect = ng_rect(roCurrentPoint,m_oActualSize);

	if(bWithMargins)
	{
		roRect.inflate(
			-_metrics().picture().get_left_margin(),
			-_metrics().picture().get_top_margin(),
			-_metrics().picture().get_right_margin(),
			-_metrics().picture().get_bottom_margin());
	}
}

//-------------- fill clone -------------- -------------- -------
inline void cned_picture::_copy_properties(cned_picture * poDestPicture)
{
	poDestPicture->m_oIdImageSourceSOV = m_oIdImageSourceSOV;
	poDestPicture->set_prop_animate(get_prop_animate());
	poDestPicture->m_eScalingMode = m_eScalingMode;

	if(m_poHyperLinkInfoSP.PointsObject())
	{
		poDestPicture->m_poHyperLinkInfoSP = NewSCP(new CHyperLinkInfo(*m_poHyperLinkInfoSP));
	}
}


inline void cned_picture::fill_clone(cned_element * poDestination)
{
	cned_rect_element_::fill_clone(poDestination);
	cned_picture * poDestPic = cast_ui<cned_picture>(poDestination);
	_copy_properties(poDestPic);
}

inline void cned_picture::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_rect_element_::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_picture * poDestPic = cast_ui<cned_picture>(poDestination);
	_copy_properties(poDestPic);
}

//-------------- rendering support -------------------
inline void cned_picture::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	ASSERT(!get_prop_hidden());

	roRenderer.ensure_width(m_oMetrics.get_minimal_width());
	ng_size oRequestedSize(m_oMetrics.get_minimal_width(),m_oMetrics.get_minimal_height());
	roRenderer.allocate_rect(get_ident(),-1,oRequestedSize,m_oActualSize,m_oVectorSize);
}


}

#else
	#error __FILE__ already included
#endif

