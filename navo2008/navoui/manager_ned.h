/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
		- manager_elementów

	- dostarcza elementy / swapuje unswapuje elementy
	- dostarcza ró¿ne providery (style, picture itd.)
*/


#ifndef _MANAGER_NED_H_
#define _MANAGER_NED_H_

namespace ned
{

class cned_element;
class cned_arena_manager;
class ned_action_kbd;
class ned_action_mouse;
class cned_style;

const long FIRST_AUTOIDENT = 10000;
const long FIRST_HIGHIDENT = 10000000;

class navo_vse::vse_interface;
class nedaw::cnedaw_element;

//--------------------------------------------------------------------------
// drag info base class 
//--------------------------------------------------------------------------

class cned_drag_info__ : public CInterface__
{
public:
	cned_drag_info__(const ng_point & roStartingArenaPoint);

	//return true when event processed, false when normal processing should occur
	virtual bool on_drag_over_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult) = 0;
	virtual bool on_end_drag_event(const ned_action_mouse_drag & roActionMouseDrag,ned_action_result & roResult) = 0;
protected:
	ng_point  m_oStartingPoint;
};


//--------------------------------------------------------------------------
// single sheet (element set) manager
//--------------------------------------------------------------------------
class cned_element_manager : public CInterface__
{
public:
	//element creation / destruction
	SCP<cned_element> get_element_on_ident(const ned_ident Ident) const;
	void on_element_finalrelease(cned_element * poElement);
	
	SCP<cned_element> _create_element(ened_element_type eType,const ned_ident Ident);
	void _remove_element(const ned_ident Ident);

	SCP<nedaw::cnedaw_element> get_nedaw(ned_ident idElement);
	void on_nedaw_final_release(ned_ident idElement,nedaw::cnedaw_element *);

	//------------------------------------------------------------------------
	HWND get_os_window() const;

	//------- element relations -----------------
	const ened_element_type get_element_type(const ned_ident Ident) const;
	const ned_ident get_element_container_ident(const ned_ident Ident) const;

	ned_ident get_prev_element(ned_ident Ident) const;
	ned_ident get_next_element(ned_ident Ident) const;
	void set_prev_element(ned_ident Ident,ned_ident idPrev);
	void set_next_element(ned_ident Ident,ned_ident idNext);

	//------------ element informations -----------------------
	bool is_element_hidden(const ned_ident Ident) const;
	bool is_element_in_hidden_tree(ned_ident Ident) const;
	bool is_element_in_disabled_tree(ned_ident Ident) const;
	bool is_element_disabled(const ned_ident Ident) const;
	bool is_element_tabstop(const ned_ident Ident) const;
	bool is_element_printable(const ned_ident Ident) const;
	bool is_element_measure_pending(const ned_ident Ident) const;

	bool can_element_accept_focus(const ned_ident Ident) const;
	//------------ swapping settings ---------------------------
	void enable_swapping(bool bEnable);
	bool is_swapping_enabled() const;
	//------- global informations ------------------------------
	bool is_sys_disable() const;

	void set_sys_disable(bool bSysDisable);
	void set_layout_invalid_to_all();
	//-------------- transfer manager ----------------------------
	void set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP);
	SCP<nui_transfer> get_transfer(ned_ident Ident);

	//-------------- font provider ------------------------------------------
	ned_fontinx get_inx_for_font_spec(const ned_font_spec & roFontSpec);
	const ned_font_spec & get_font_spec_on_inx(const ned_fontinx nFontInx);
	SCP<ng_font> get_font_on_inx(const ned_fontinx nFontInx);

	//-------------- declared attributes provider ----------------------------
	ned_declattrinx get_inx_for_declattr(const ned_declattributes & roDeclAttrib);
	const ned_declattributes & get_declattr_on_inx(const ned_declattrinx nAttribInx) const;
	
	//-------------- images -------------------------------------------------
	SCP<ng_image> get_image(const CSmartOleVariant & roImageSourceSOV,SCP<ng_image_request> poRequestSP);
	SCP<ng_image> get_special_image(eSpecialImage eImage);

	//-------------- tooltip and help text manager ----------------------------
	void set_tooltip_text(ned_ident idElement,const ng_string & roToolTipString);
	void get_tooltip_text(ned_ident idElement,ng_string & roToolTipString) const;

	void set_help_text(ned_ident idElement,const ng_string & roHelpTextString);
	void get_help_text(ned_ident idElement,ng_string & roHelpTextString) const;

	//-------------- short key manager -------------- -------------- 
	void set_shortkey(ned_ident Ident,SCP<cnui_shortkey> & rpoShortKeySP);
	SCP<cnui_shortkey> get_shortkey(ned_ident Ident);
	ned_ident lookup_shortkeys(const ned_action_kbd & roActionKBD) const;

	//-------------- declared position -------------- -------------- -------------- 
	void set_decl_position(ned_ident idElement,const ned_position & roPosition);
	bool get_decl_position(ned_ident idElement,ned_position & roPosition) const;

	//-------------- style -------------- -------------- -------------- 
	SCP<cned_style> get_style(long StyleId);

	//----- focus management ------------------------
	ned_ident get_focus_element() const;
	ned_ident get_mouse_over_element() const;
	void update_mouse_over_element(ned_ident idMouseOver);

	void _mark_new_focus_element(ned_ident idNewFocusElement);
	bool _consume_focus_change(ned_ident & ridOldFocus);

	//------ dragging support ------------------------
	void store_drag_info(SCP<cned_drag_info__> poDragInfoSP);
	void clean_drag_info();
	bool is_dragging() const;
	SCP<cned_drag_info__> get_drag_info();
	
	//--------- paint rect management ----------------------
	void store_paint_rect(ned_ident idElement,long nFragment,const ng_rect & roRect);
	bool get_paint_rect(ned_ident idElement,long nFragment,ng_rect & roRect);
	bool invalidate_paint_rect(ned_ident idElement,long nFragment);
	void invalidate_paint_rect(const ng_rect & roAbsoluteRect);

	//----------- transfer iterator ------------------------
	void start_transfer_iterator();
	bool next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP);

	//---------- time-aware control registration -------------
	void unregister_for_timer(ned_ident idElement);
	void register_for_timer(ned_ident idElement,long nInterval,bool bOnlyWhenOnTop);
	
	void get_timer_controls(CArray<ned_ident,ned_ident &> & roIdentArray,bool bForTopWindow);

	//---------- convertions and zoom -----------------------------
	//converts external units to internal one (including DC and zoom)
	ng_point to_internal(const ng_point & roExtPoint) const;
	ng_size	to_internal(const ng_size & roExtSize) const;

	//converts internal units to external one (including DC and zoom)
	ng_point to_external(const ng_point & roExtPoint) const;
	ng_size	to_external(const ng_size & roExtSize) const;

	long __zoomize(long nNotZoomedValue) const;

	long get_zoom() const;
	void set_zoom(long nZoom);

	const ng_rect & get_screen_arena() const;

	long get_form_feed_count() const;
	//--------------------------------------------------
	bool is_modified_flag() const;
	void set_modified_flag();
	void clear_modified_flag();
	//--------------------------------------------------
#ifdef _DEVELOPER_EDITION_
	void _debug_draw_invalidated_as_red(bool bDebugDraw);
#endif
public:	/*almost "private" */
	void _clean_all();

private: /* public for friends only */
	cned_element_manager(cned_arena_manager * poArenaManager);
	~cned_element_manager();


	void __destroy_element(cned_element * poElement);

	//element information
	ned_element_mini_info & _get_miniinfo_on_ident(const ned_ident Ident) const;

	long _map_ident(ned_ident idElement) const;
	long _pre_hash(ned_ident Ident) const
	{
		return long(DWORD(Ident) << 4);
	}
	ned_ident _post_hash(long nHashedId) const
	{
		return ned_ident(DWORD(nHashedId) >> 4);
	}
	ned_ident _generate_ident();

	void _add_new_element(SCP<cned_element> poNewElementSP);
	
	SCP<cned_element> __construct_element(ened_element_type eType,const ned_ident Ident);
	SCP<cned_element> __reincarnate_element(cned_element * poElement) const;
	long _find_transfer_index(long nHashedId) const;

	
	void _flush_font_cache();

	struct cned_element_entry
	{
		cned_element_entry();

		cned_element *			m_poElement;
		ned_element_mini_info	m_oMiniInfo;
		ng_rect					m_oPaintRect0;
		ng_rect					m_oPaintRect1;
		bool					m_bPaintRect0 : 1;
		bool					m_bPaintRect1 : 1;
	};

	//main storage for elements
	CArray<cned_element_entry,cned_element_entry & > m_oFixedIdElementArray;
	CArray<cned_element_entry,cned_element_entry & > m_oAutoIdElementArray;
	CArray<cned_element_entry,cned_element_entry & > m_oHighIdElementArray;

	
	//_array accessor
	CArray<cned_element_entry,cned_element_entry & > & _array(ned_ident idElement);
	const CArray<cned_element_entry,cned_element_entry & > & _array(ned_ident idElement) const;
	
	//_entry accessor
	cned_element_entry & _entry(ned_ident idElement);
	const cned_element_entry & _entry(ned_ident idElement) const;
	
	const cned_element_entry * _safe_entry(ned_ident idElement) const;

	static void _clean_array(CArray<cned_element_entry,cned_element_entry & > & roArray);
	static void _clean_array2(CArray<cned_element_entry,cned_element_entry & > & roArray);
	static void set_layout_invalid_to_all_in_array(CArray<cned_element_entry,cned_element_entry & > & roArray);

#ifdef _DEBUG
	long _debug_m_nTotalRequests;
	long _debug_m_nMaxRequests;
#endif	

	long	m_nAutoIdent;
	bool	m_bSysDisabled;		//global "sys disable flag"
	bool	m_bModifiedFlag;	//"modified" flag - means: it was any modification since last reset
	
	ned_ident m_idFocus;
	ned_ident m_idOldFocus;
	ned_ident m_idMouseOver;
	SCP<cned_drag_info__> m_poDragInfoSP;

	cned_arena_manager * m_poArenaManager;		//uplink

	//transfer
	struct nui_transfer_entry
	{
		nui_transfer_entry();
		nui_transfer_entry(long nHashedId,SCP<nui_transfer> & rpoTransferSP);

		long m_nHashedId;
		SCP<nui_transfer> m_poTransferSP;
	};
	
	CArray<nui_transfer_entry, nui_transfer_entry & > m_oTransferArray;
	long m_nTransferIterator;

	struct FontWithDescription
	{
		SCP<ng_font>	m_poFontSP;
		ned_font_spec	m_oFontSpec;
		
		FontWithDescription(){}
		FontWithDescription(const ned_font_spec & roFontSpec,SCP<ng_font> poFontSP) :
			m_poFontSP(poFontSP),
			m_oFontSpec(roFontSpec)
		{
		}
	};

	//{{
		CMap<ng_string,LPCTSTR,ned_fontinx,ned_fontinx>		m_oFontInxMap;
		CArray<FontWithDescription, FontWithDescription & >	m_oFontArray;
	//}}

	//timer registrations
	CArray<timer_registration,const timer_registration & > m_oTimerRegisteredArray;

	//shortkeys
	CMap<long,long, SCP<cnui_shortkey>, SCP<cnui_shortkey> & > m_oShortKeyMap;
	
	CMap<long,long, ng_string, ng_string & > m_oToolTipMap;
	CMap<long,long, ng_string, ng_string & > m_oHelpTextMap;
	
	CMap<long,long, ned_position, ned_position & > m_oDeclPositionMap;

	//------- nedaw element support -----------------
	CMap<long,long, nedaw::cnedaw_element *, nedaw::cnedaw_element * > m_oNEDAWMap;
	
	CMap<__int64,__int64,ng_rect,ng_rect & > m_oPaintRectMap;

	bool	m_bQuitting;
	bool	m_bWasElementWithStdScriptSupport;
	bool	m_bSwappingEnabled;
	long	m_nFormFeedCount;
	ng_scaling m_oScaling;
	
	navo_vse::vse_interface * m_poVSE;

	friend class cned_arena_manager;
	friend class cned_window; //for _add_new_element
};

//------------------ inlines --------------------------------------
inline cned_element_manager::cned_element_entry::cned_element_entry():
	m_poElement(NULL),
	m_bPaintRect0(false),
	m_bPaintRect1(false)
{
}

inline cned_element_manager::nui_transfer_entry::nui_transfer_entry():
	m_nHashedId(0)
{
}

inline cned_element_manager::nui_transfer_entry::nui_transfer_entry(long nHashedId,SCP<nui_transfer> & rpoTransferSP):
	m_nHashedId(nHashedId),
	m_poTransferSP(rpoTransferSP)
{
}

inline long cned_element_manager::_map_ident(ned_ident idElement) const
{
	ASSERT(idElement > 0 && idElement < FIRST_HIGHIDENT + 1000000);	//albo b³¹d albo bardzo du¿a strona - warto wiedzieæ

	return (idElement < FIRST_AUTOIDENT) ? 
				idElement : 
				((idElement >= FIRST_HIGHIDENT) ? 
					idElement - FIRST_HIGHIDENT : 
					idElement - FIRST_AUTOIDENT);
}

inline CArray<cned_element_manager::cned_element_entry,cned_element_manager::cned_element_entry & > & cned_element_manager::_array(ned_ident idElement)
{
	ASSERT(idElement > 0 && idElement < FIRST_HIGHIDENT + 1000000);	//albo b³¹d albo bardzo du¿a strona - warto wiedzieæ
	return (idElement < FIRST_AUTOIDENT) ? 
				m_oFixedIdElementArray : 
				((idElement >= FIRST_HIGHIDENT) ? 
					m_oHighIdElementArray :	
					m_oAutoIdElementArray);
}

inline const CArray<cned_element_manager::cned_element_entry,cned_element_manager::cned_element_entry & > & cned_element_manager::_array(ned_ident idElement) const
{
	ASSERT(idElement > 0 && idElement < FIRST_HIGHIDENT + 1000000);	//albo b³¹d albo bardzo du¿a strona - warto wiedzieæ
	return (idElement < FIRST_AUTOIDENT) ? 
				m_oFixedIdElementArray : 
				((idElement >= FIRST_HIGHIDENT) ? 
					m_oHighIdElementArray :	
					m_oAutoIdElementArray);
}

inline cned_element_manager::cned_element_entry & cned_element_manager::_entry(ned_ident idElement)
{
	return _array(idElement)[ _map_ident(idElement) ];
}

inline const cned_element_manager::cned_element_entry & cned_element_manager::_entry(ned_ident idElement) const
{
	return _array(idElement)[ _map_ident(idElement) ];
}

inline const cned_element_manager::cned_element_entry * cned_element_manager::_safe_entry(ned_ident idElement) const
{
	if(idElement > 0)
	{
		const CArray<cned_element_entry,cned_element_entry & > & roArray = _array(idElement);
		long nMappedId = _map_ident(idElement);
		ASSERT(nMappedId >= 0);
		if(nMappedId <= roArray.GetUpperBound())
		{
			if(roArray[nMappedId].m_oMiniInfo.get_type() != ned_none)
			{
				return &roArray[nMappedId];
			}
		}
	}
	return NULL;
}

inline ned_element_mini_info & cned_element_manager::_get_miniinfo_on_ident(const ned_ident Ident) const
{
	const cned_element_entry & roEntry = _entry(Ident);
	
	if(roEntry.m_poElement != NULL)
	{
		return roEntry.m_poElement->_mini_info();
	}
	else
	{
		return const_cast<ned_element_mini_info &>(roEntry.m_oMiniInfo);
	}
}

inline ned_ident cned_element_manager::get_prev_element(ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).get_prev_element_ident();
}

inline ned_ident cned_element_manager::get_next_element(ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).get_next_element_ident();
}

inline void cned_element_manager::set_prev_element(ned_ident Ident,ned_ident idPrev)
{
	_get_miniinfo_on_ident(Ident).set_prev_element_ident(idPrev);
}

inline void cned_element_manager::set_next_element(ned_ident Ident,ned_ident idNext)
{
	_get_miniinfo_on_ident(Ident).set_next_element_ident(idNext);
}

inline bool cned_element_manager::is_element_disabled(const ned_ident Ident) const
{
	ned_element_mini_info & roMiniInfo = _get_miniinfo_on_ident(Ident);
	
	return roMiniInfo.is_internal_disabled() ||
		(is_sys_disable() && !roMiniInfo.is_internal_ignore_sys_dis());
}

inline bool cned_element_manager::is_element_hidden(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).is_hidden();
}

inline bool cned_element_manager::is_element_printable(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).is_printable();
}

inline bool cned_element_manager::is_element_measure_pending(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).is_measure_pending();
}

inline bool cned_element_manager::is_element_tabstop(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).is_tabstop();
}

inline const ened_element_type cned_element_manager::get_element_type(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).get_type();
}

inline const ned_ident cned_element_manager::get_element_container_ident(const ned_ident Ident) const
{
	return _get_miniinfo_on_ident(Ident).get_container_ident();
}


inline bool cned_element_manager::is_element_in_hidden_tree(ned_ident Ident) const
{
	ASSERT(Ident != NEDID_NOTHING);

	while(Ident != NEDID_NOTHING)
	{
		ned_element_mini_info & roMiniInfo = _get_miniinfo_on_ident(Ident);
		if(roMiniInfo.is_hidden())
		{
			return true;
		}
		Ident = roMiniInfo.get_container_ident();
	}
	return false;
}

inline bool cned_element_manager::is_element_in_disabled_tree(ned_ident Ident) const
{
	ASSERT(Ident != NEDID_NOTHING);

	while(Ident != NEDID_NOTHING)
	{
		ned_element_mini_info & roMiniInfo = _get_miniinfo_on_ident(Ident);
		if(roMiniInfo.is_internal_disabled())
		{
			return true;
		}
		Ident = roMiniInfo.get_container_ident();
	}
	return false;
}

inline bool cned_element_manager::is_sys_disable() const
{
	return m_bSysDisabled;
}

inline ned_ident cned_element_manager::get_focus_element() const
{
	return m_idFocus;
}

inline ned_ident cned_element_manager::get_mouse_over_element() const
{
	return m_idMouseOver;
}

inline void cned_element_manager::update_mouse_over_element(ned_ident idMouseOver)
{
	m_idMouseOver = idMouseOver;
}

inline bool cned_element_manager::can_element_accept_focus(const ned_ident Ident) const
{
	ned_element_mini_info & roMiniInfo = _get_miniinfo_on_ident(Ident);

	if(roMiniInfo.is_internal_disabled() ||
		(is_sys_disable() && !roMiniInfo.is_internal_ignore_sys_dis()))
	{
		return false;
	}
	if(roMiniInfo.is_hidden())
	{
		return false;
	}
	if(NEDID_NOTHING == roMiniInfo.get_container_ident())
	{
		return false;
	}
	//ned_to_do: prawdopodobnie is_element_in_hidden_tree nie jest tu
	//potrzebne - sprawdziæ wywo³ania can-element-accept
	
	//ned_to_do: byæ mo¿e te¿ wszystkie wywo³ania can-element-accept
	//s¹ robione w kontekœcie, ¿e zwraca true - jeœli tak, to pozostawiæ tylko w
	//wersji _DEBUG (jako ASSERT)

	return !is_element_in_hidden_tree(roMiniInfo.get_container_ident()) &&
		!is_element_in_disabled_tree(roMiniInfo.get_container_ident());
}

//--------- paint rect management ----------------------
inline void cned_element_manager::store_paint_rect(ned_ident idElement,long nFragment,const ng_rect & roRect)
{
	switch(nFragment)
	{
	case MAIN_PAINT_RECT_ID:
	case 1:
	{
		cned_element_entry & roEntry = _entry(idElement);

		if(nFragment == MAIN_PAINT_RECT_ID)
		{
			roEntry.m_oPaintRect0 = roRect;
			roEntry.m_bPaintRect0 = true;
		}
		else
		{
			roEntry.m_oPaintRect1 = roRect;
			roEntry.m_bPaintRect1 = true;
		}
	}
	break;
	default:
		m_oPaintRectMap[ longlong(long(idElement),nFragment) ] = roRect;
	}
}

inline bool cned_element_manager::get_paint_rect(ned_ident idElement,long nFragment,ng_rect & roRect)
{
	switch(nFragment)
	{
	case MAIN_PAINT_RECT_ID:
	case 1:
	{
		cned_element_entry & roEntry = _entry(idElement);

		if(nFragment == MAIN_PAINT_RECT_ID)
		{
			if(roEntry.m_bPaintRect0)
			{
				roRect = roEntry.m_oPaintRect0;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if(roEntry.m_bPaintRect1)
			{
				roRect = roEntry.m_oPaintRect1;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	break;
	default:
		__int64 i64Key = longlong(long(idElement),nFragment);
		return (m_oPaintRectMap.Lookup(i64Key,roRect) != FALSE);
	}
}

//----------- transfer iterator ------------------------
inline void cned_element_manager::start_transfer_iterator()
{
	m_nTransferIterator = -1;
}

//------------ swapping settings ---------------------------
inline bool cned_element_manager::is_swapping_enabled() const
{
	return m_bSwappingEnabled;
}

//------ dragging support ------------------------

inline bool _is_in_void_drag_area(const ng_point & roPoint1,const ng_point & roPoint2)
{
	ng_xdist xDist = (ng_xdist) labs(roPoint1.get_x() - roPoint2.get_x());
	ng_ydist yDist = (ng_ydist) labs(roPoint1.get_y() - roPoint2.get_y());
	
	ASSERT(xDist >= 0 && yDist >= 0);

	return (xDist <= _metrics().get_void_drag_size().get_dx() && 
		    yDist <= _metrics().get_void_drag_size().get_dy());
}


inline void cned_element_manager::store_drag_info(SCP<cned_drag_info__> poDragInfoSP)
{
	ASSERT(m_poDragInfoSP.PointsNull());
	m_poDragInfoSP = poDragInfoSP;
}

inline void cned_element_manager::clean_drag_info()
{
	m_poDragInfoSP = 0;
}

inline bool cned_element_manager::is_dragging() const
{
	return m_poDragInfoSP.PointsObject();
}

inline SCP<cned_drag_info__> cned_element_manager::get_drag_info()
{
	ASSERT(is_dragging());
	return m_poDragInfoSP;
}

inline long cned_element_manager::get_form_feed_count() const
{
	return m_nFormFeedCount;
}

//--------------------------------------------------
//--------------------------------------------------
inline bool cned_element_manager::is_modified_flag() const
{
	return m_bModifiedFlag;
}

inline void cned_element_manager::set_modified_flag()
{
	m_bModifiedFlag = true;
}

inline void cned_element_manager::clear_modified_flag()
{
	m_bModifiedFlag = false;
}

//------------------------ -----------------------------
//------------------------ inlines ----------------------------------------
//------------------------ -----------------------------

inline ng_point cned_element_manager::to_internal(const ng_point & roExtPoint) const
{
	return ng_point(m_oScaling.x_to_du(roExtPoint.get_x()),m_oScaling.y_to_du(roExtPoint.get_y()));
}

inline ng_size	cned_element_manager::to_internal(const ng_size & roExtSize) const
{
	return ng_size(m_oScaling.dx_to_du(roExtSize.get_dx()),m_oScaling.dy_to_du(roExtSize.get_dy()));
}

inline ng_point cned_element_manager::to_external(const ng_point & roExtPoint) const
{
	return ng_point(m_oScaling.du_to_x(roExtPoint.get_x()),m_oScaling.du_to_y(roExtPoint.get_y()));
}

inline ng_size	cned_element_manager::to_external(const ng_size & roExtSize) const
{
	return ng_size(m_oScaling.du_to_dx(roExtSize.get_dx()),m_oScaling.du_to_dy(roExtSize.get_dy()));
}

inline long cned_element_manager::__zoomize(long nNotZoomedValue) const
{
	return m_oScaling.__zoomize(nNotZoomedValue);
}

inline long cned_element_manager::get_zoom() const
{
	return m_oScaling.get_zoom();
}

inline void cned_element_manager::set_zoom(long nZoom)
{
	if(get_zoom() == nZoom)
	{
		return;
	}
	m_oScaling.set_zoom(nZoom);
	set_layout_invalid_to_all();
}

//------------------- cned_element -------------------------------

inline SCP<cned_element> cned_element::get_element_on_ident(ned_ident idElement) const
{
	SCP<cned_element> poElementSP = get_manager()->get_element_on_ident(idElement);
	ASSERT(poElementSP.PointsObject());
	return poElementSP;
}

//------------------- cned_drag_info__ -------------------------------
inline cned_drag_info__::cned_drag_info__(const ng_point & roStartingArenaPoint) :
	m_oStartingPoint(roStartingArenaPoint)
{
}



}

#else
	#error __FILE__ already included
#endif
 