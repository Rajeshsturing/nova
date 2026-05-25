/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	page caption element

*/

#ifndef _PAGE_CAPTION_NED_H_
#define _PAGE_CAPTION_NED_H_

#ifndef COLOR_GRADIENTACTIVECAPTION
#define COLOR_GRADIENTACTIVECAPTION     27
#endif

namespace ned
{

class cned_static;
class cned_picture;

class cned_page_caption : public cned_paragraph
{
public:
	void __construct_elements();
	//-------------- property get ---------------
	void get_prop_title(ng_string & roTitleString) const;
	bool get_prop_active() const;
	bool get_prop_maximized() const;
	//-------------- property set ---------------
	void set_prop_title(const ng_string & roTitleString);
	void set_prop_active(bool bActive);
	void set_prop_maximized(bool bMaximized);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

//--------------event handlers ---------------------------------------
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
//-------------- event forwarders -------------- -------------- -------
	virtual void process_event_mouse_click(ned_path_to_element & roCallStack,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	//---- paint invalidating --------
	void invalidate_caption_paint();

	SCP<cned_picture> _get_close_pic() const;
private:
	cned_page_caption(cned_element_manager * poManager,const ned_ident idThis);
	void _update_internal_properties();

	SCP<cned_static> _get_title() const;
	SCP<cned_picture> _get_maximize_pic() const;

	ned_ident m_idTitleStatic;
	ned_ident m_idCloseBoxPic;
	ned_ident m_idMaximizePic;
	bool	  m_bActive;
	bool	  m_bMaximized;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_page_caption::cned_page_caption(cned_element_manager * poManager,const ned_ident idThis) :
	cned_paragraph(poManager,ned_page_widgets,idThis),
	m_idTitleStatic(NEDID_NOTHING),
	m_idCloseBoxPic(NEDID_NOTHING),
	m_idMaximizePic(NEDID_NOTHING),
	m_bActive(true),
	m_bMaximized(false)
{
}

inline void cned_page_caption::set_fixed_properties()
{
	cned_paragraph::set_fixed_properties();

	set_prop_backcolor(ng_color::system(COLOR_ACTIVECAPTION));
	set_prop_backcolor2( ng_color::system(COLOR_GRADIENTACTIVECAPTION));
	set_prop_vert_padding(0);
	set_prop_horiz_padding(2);
	set_prop_keepline(true);
	set_prop_ignore_sys_disable(true);
}

inline void cned_page_caption::invalidate_caption_paint()
{
	_invalidate_all_paint();
}

//-------------- property get ---------------
inline bool cned_page_caption::get_prop_active() const
{
	return m_bActive;
}

inline bool cned_page_caption::get_prop_maximized() const
{
	return m_bMaximized;
}

//-------------- property set ---------------
inline void cned_page_caption::set_prop_active(bool bActive)
{
	if(get_prop_active() == bActive)
	{
		return;
	}

	m_bActive = bActive;
	
	_update_internal_properties();
}

inline void cned_page_caption::set_prop_maximized(bool bMaximized)
{
	if(get_prop_maximized() == bMaximized)
	{
		return;
	}

	m_bMaximized = bMaximized;
	
	_update_internal_properties();
}

}

#else
	#error __FILE__ already included
#endif
