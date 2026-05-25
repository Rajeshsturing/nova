/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)


	- wspólny manager dla wszystkich elementów
	(rodzaj implementacji dla cnui_arena)

*/

#ifndef _ARENA_MANAGER_NED_H_
#define _ARENA_MANAGER_NED_H_

namespace ned
{

class cned_element_manager;
class cned_style;
class cned_stylemanager;

class cned_arena_manager : public CInterface__
{
public:
	cned_arena_manager();
	~cned_arena_manager();

	void set_providers(const ng_string & roFullCachePathString,SCP<IGlobalInterfaceTable> poGITSP,
		DWORD dwAppDBManager_GIT_Cookie,DWORD dwCachedData_GIT_Cookie);
	
	SCP<cned_element_manager> create_element_manager();

	SCP<ng_image> get_image(const CSmartOleVariant & roImageSourceSOV,SCP<ng_image_request> poRequestSP);
	SCP<ng_image> get_special_image(eSpecialImage eImage);

	//declared attributes provider
	ned_declattrinx get_inx_for_declattr(const ned_declattributes & roDeclAttrib);
	const ned_declattributes & get_declattr_on_inx(const ned_declattrinx nAttribInx) const;

	//style
	SCP<cned_style> get_style(long StyleId);

	//ustawia nowy styl i mówi czy siê zmieni³
	bool set_current_style(const CSmartOleVariant & roStyleSOV);


	void set_arena(const ng_rect & roArenaRect)
	{
		m_oArenaRect = roArenaRect;
	}
	void attach_os_window(HWND hWnd)
	{
		m_hWnd = hWnd;
	}
	HWND get_os_window() const
	{
		return m_hWnd;
	}
	const ng_rect & get_screen_arena() const
	{
		return m_oArenaRect;
	}
	void invalidate_paint_rect(const ng_rect & roAbsoluteRect);
	const ng_area & get_invalid_paint_area() const;
	void clear_paint_area();

	void add_control_timer_ref();
	void release_control_timer_ref();
private:
	SCP<ng_image> _load_image(const CSmartOleVariant & roImageSourceSOV);
	SCP<ng_image> _load_image_via_cache(long nIdImage);

#ifdef _DEBUG
	long _debug_picture_requests;
	long _debug_picture_hits;
#endif

	CSimpleCriticalSection	m_oPictureMapCS;
	//{{
		CMap<ng_string,LPCTSTR,SCP<ng_image>,SCP<ng_image> >	m_oPictureMap;
	//}}

	//{{
		CMap<ng_string,LPCTSTR,ned_declattrinx,ned_declattrinx>	m_oDeclAttribMap;
		CArray<ned_declattributes,const ned_declattributes&>	m_oDeclAttribArray;
	//}}

	SCP<ng_image>		m_aSpecialImages[ esi_max ];

	SCP<cned_stylemanager> m_poStyleManagerSP;
	SCP<cned_style>		   m_poCurrentStyleSP;
	//data providers
	SCP<IGlobalInterfaceTable> m_poGITSP;
	DWORD m_dwAppDBManager_GIT_Cookie;
	DWORD m_dwCachedData_GIT_Cookie;
	ng_string			m_oFullServerPathString;

	ng_rect				m_oArenaRect;
	ng_area				m_oInvalidPaintArea;
	long				m_nArenaControlTimerRef;
	
	HWND				m_hWnd;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline const ned_declattributes & cned_arena_manager::get_declattr_on_inx(const ned_declattrinx nAttribInx) const
{
	ASSERT(nAttribInx >= 0 && nAttribInx <= m_oDeclAttribArray.GetUpperBound());
	return m_oDeclAttribArray[ long(nAttribInx) ];
}

inline void cned_arena_manager::invalidate_paint_rect(const ng_rect & roAbsoluteRect)
{
#ifdef _DEBUG
	CDebugTimeMeter oDTM("cned_arena_manager::invalidate_paint_rect",2);
#endif

	if(!roAbsoluteRect.is_empty())
	{
		ng_rect oRestrictedRect(roAbsoluteRect);
		oRestrictedRect.intersect_with(get_screen_arena());
		
		m_oInvalidPaintArea += oRestrictedRect;
		
		//jak jest za du¿o kawa³ków to po prostu zaznacz ca³¹ arenê
		if(m_oInvalidPaintArea.get_count() > 400 /*threashold */)
		{
			m_oInvalidPaintArea.empty();
			m_oInvalidPaintArea += get_screen_arena();
		}
	}
}

inline const ng_area & cned_arena_manager::get_invalid_paint_area() const
{
	return m_oInvalidPaintArea;
}

inline void cned_arena_manager::clear_paint_area()
{
	m_oInvalidPaintArea.empty();
}

}

#else
	#error __FILE__ already included
#endif
