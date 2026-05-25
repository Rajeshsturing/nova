/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	window

*/

#ifndef _WINDOW_NED_H_
#define _WINDOW_NED_H_

namespace ned
{
class cned_arena;
class cned_toplevelpage;

const long STD_COMMAND_COUNT = 24;

enum ened_window_initial_pos
{
	wip_default,
	wip_center,
	wip_bottom_left,
	wip_top_right,
	wip_top_left,
	wip_done,		//initial position realized
};

enum ened_window_special_effect
{
	wse_none,
	wse_expand,
	wse_collapse,
	wse_migrate_to_corner,
	wse_migrate_to_center
};

//----------------------------------------------------------------------
// single window sheet
//----------------------------------------------------------------------
class cned_window;

class cned_window_sheet : public CInterface__
{
public:
	cned_window_sheet(cned_arena * poArena,cned_window * poWindow,SCP<cned_element_manager> poElementManagerSP,SCP<cned_toplevelpage> poTopLevelPageSP);
	~cned_window_sheet();

	SCP<cned_element> get_element_on_ident(const ned_ident idElement) const;
	SCP<cned_toplevelpage> get_toplevelpage() const;

	void update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord);

	long get_zoom() const;
	void set_zoom(long nZoom);

	void update_split_info(cpb_split_info & roSplitInfo);
	void make_split(cpb_split_manager & roSplitManager);


	bool is_inside_hit_area(const ng_point & roPoint) const;
	//----- painting, rendering --------------------------------
	void _prepare_paint_region(ng_region & roRegion);
	void paint(cned_painter_ & roArenaPainter);
	
	void invalidate_sheet();
	void get_sheet_rect(ng_rect & roSheetRect);

	void on_window_on_top(bool bTopMost);
	
	void on_being_current_sheet(bool bCurrent);
	//--------- event handlers ---------------------------------
	eCursorType on_event_set_cursor(const ng_point & roPoint);
	void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult);

	void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult);

	//------ property GET -----------------
	void get_prop_title(ng_string & roTitleString) const;

	void set_layout_invalid_to_all();
	void apply_attributes(const ned_currattributes & roCurrAttrib);
private:
	cned_toplevelpage *  get_page();
	cned_element_manager * get_manager();

	const cned_toplevelpage *  get_page() const;
	const cned_element_manager * get_manager() const;
	void _prepare_tooltip();

	//-------------------- event helpers ----------------------------------------
	ned_ident _find_mouse_target_element(const ng_point & roArenaPoint);

	void _make_focus_change(ng_dc & roDC,ned_action_result & roResult);
	void _process_event_keydown(const ned_ident TargetIdent,const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	void _process_event_focus(const ned_ident TargetIdent,const ned_action_focus & roFocusAction,ned_action_result & roResult);
	void _process_event_timer(const ned_ident idTarget,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	void _process_event_mouse_over(const ned_ident idTarget,const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void _realize_initial_focus();

	SCP<cned_toplevelpage>		m_poTopLevelPageSP;
	SCP<cned_element_manager>	m_poElementManagerSP;	//element storage service

#define ned_to_do_FRIEND			//odkomentuj aby zobaczyæ jakie elementy s¹ 'nadu¿ywane'

#ifdef ned_to_do_FRIEND
	friend class cned_normal_window_view;
	friend class cned_sheet_window_view;
#endif
	cned_arena * m_poArena;
	cned_window * m_poWindow;
};

//----------------------------------------------------------------------
// cned_window_view__
//----------------------------------------------------------------------
class cned_window;

class cned_window_view__ : public CInterface__
{
public:
	virtual SCP<cned_element> get_element_on_ident(const ned_ident idElement) const = 0;
	virtual SCP<cned_toplevelpage> get_toplevelpage() const = 0 ;

	virtual bool is_inside_hit_area(const ng_point & roPoint) const = 0;
	//----- painting, rendering --------------------------------
	virtual void _prepare_paint_region(ng_region & roRegion) = 0;
	virtual void paint(cned_painter_ & roArenaPainter) = 0;

	virtual void update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord) = 0;

	virtual long get_zoom() const = 0;
	virtual void set_zoom(long nZoom) = 0;

	virtual void invalidate_view() = 0;

	virtual void on_window_on_top(bool bTopMost) = 0;
	//------- transfer support --------
	virtual void set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP) = 0;
	virtual SCP<nui_transfer> get_transfer(ned_ident Ident) = 0;
	virtual void start_transfer_iterator() = 0;
	virtual bool next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP) = 0;

	//-------------- sys disable ---------------
	virtual void set_sys_disable(bool bSysDisable) = 0;
	virtual bool is_sys_disable() const = 0;

	//-------------- modified flag --------------
	virtual void set_modified_flag(bool bModified) = 0;
	virtual bool get_modified_flag() const = 0;

	//--------- event handlers ---------------------------------
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint) = 0;
	virtual void on_event_size_changed(bool bWidthChange) = 0;
	virtual void on_event_style_changed() = 0;
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult) = 0;
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult) = 0;
	virtual void on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult) = 0;
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult) = 0;
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult) = 0;
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult) = 0;
	virtual void on_event_zoom_in() = 0;
	virtual void on_event_zoom_out() = 0;
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult) = 0;

	virtual void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult) = 0;

	cned_paint_param m_oPaintParam;
protected:
	cned_window_view__(cned_window * poWindow);

	cned_window * m_poWindow;
};

//----------------------------------------------------------------------
// cned_normal_window_view 
// normal view
//----------------------------------------------------------------------
class cned_normal_window_view : public cned_window_view__
{
public:
	cned_normal_window_view(cned_window * poWindow,SCP<cned_window_sheet> poSheetSP);

	virtual SCP<cned_element> get_element_on_ident(const ned_ident idElement) const;
	virtual SCP<cned_toplevelpage> get_toplevelpage() const;

	void set_layout_invalid_to_all();
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;

	//------- transfer support --------
	virtual void set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP);
	virtual SCP<nui_transfer> get_transfer(ned_ident Ident);
	virtual void start_transfer_iterator();
	virtual bool next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP);

	//----- painting, rendering --------------------------------
	virtual void _prepare_paint_region(ng_region & roRegion);
	virtual void paint(cned_painter_ & roArenaPainter);

	virtual void update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord);
	
	void update_split_info(cpb_split_info & roSplitInfo);
	void make_split(cpb_split_manager & roSplitManager);


	virtual long get_zoom() const;
	virtual void set_zoom(long nZoom);
	virtual void invalidate_view();

	virtual void on_window_on_top(bool bTopMost);
	//-------------- sys disable ---------------
	virtual void set_sys_disable(bool bSysDisable);
	virtual bool is_sys_disable() const;

	//-------------- modified flag --------------
	virtual void set_modified_flag(bool bModified);
	virtual bool get_modified_flag() const;
	//--------- event handlers ---------------------------------
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_size_changed(bool bWidthChange);
	virtual void on_event_style_changed();
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual void on_event_zoom_in();
	virtual void on_event_zoom_out();
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult);

	virtual void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult);

	//------ property GET -----------------
	void get_prop_official_title(ng_string & roString) const;
private:
	SCP<cned_window_sheet>		m_poSheetSP;
};

//----------------------------------------------------------------------
// cned_sheet_window_view
// page break (print preview) view
//----------------------------------------------------------------------
class cned_sheet_window_view : public cned_window_view__
{
public:
	cned_sheet_window_view(cned_window * poWindow);

	virtual SCP<cned_element> get_element_on_ident(const ned_ident idElement) const;
	virtual SCP<cned_toplevelpage> get_toplevelpage() const;

	void add_new_sheet(long nX,long nY,SCP<cned_window_sheet> poSheetSP);
	void set_layout_invalid_to_all();

	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	//------- transfer support --------
	virtual void set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP);
	virtual SCP<nui_transfer> get_transfer(ned_ident Ident);
	virtual void start_transfer_iterator();
	virtual bool next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP);

	//----- painting, rendering --------------------------------
	virtual void _prepare_paint_region(ng_region & roRegion);

	virtual void paint(cned_painter_ & roArenaPainter);
	
	virtual void update_layout(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompletArenaRect,const cned_paint_param & roPaintParam,
		ng_ycoord yReqYcoord);

	virtual long get_zoom() const;
	virtual void set_zoom(long nZoom);
	virtual void invalidate_view();

	virtual void on_window_on_top(bool bTopMost);
	//-------------- sys disable ---------------
	virtual void set_sys_disable(bool bSysDisable);
	virtual bool is_sys_disable() const;

	//-------------- modified flag --------------
	virtual void set_modified_flag(bool bModified);
	virtual bool get_modified_flag() const;
	//--------- event handlers ---------------------------------
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_size_changed(bool bWidthChange);
	virtual void on_event_style_changed();
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	virtual void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	virtual void on_event_zoom_in();
	virtual void on_event_zoom_out();
	virtual void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult);

	virtual void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult);

	long print(ned_action_paint & roActionPaint,ned_action_result & roResult,const cned_paint_param & roPaintParam,SCP<IDispatch> poPrintInfoSinkSP);

	void get_current_sheet_coord(long & rnX,long & rnY) const;
	void set_current_sheet_coord(long nX,long nY);
private:
	SCP<cned_window_sheet> get_sheet(long nX,long nY) const;
	SCP<cned_window_sheet> get_current_sheet() const;

	CArray2DX< SCP<cned_window_sheet>, SCP<cned_window_sheet> & > m_oSheet2DArray;
		
	long	m_nCurrentSheetX;
	long	m_nCurrentSheetY;
	long	m_nZoom;
};

enum ewindow_view
{
	wv_normal,
	wv_sheet
};

class cned_window : public CCmdTargetInterface, public CScriptUser
{
public:
	cned_window(cned_arena * poArena);
	~cned_window();

	SCP<cned_element> get_element_on_ident(const ned_ident idElement) const;
	SCP<cned_toplevelpage> get_toplevelpage() const;

	//--------- event handlers ---------------------------------
	void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);

	void on_event_size_changed(bool bWidthChange);
	eCursorType on_event_set_cursor(const ng_point & roPoint);

	void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_over(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	void on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result & roResult);
	void on_event_timer(bool bTopWindow,const ned_action_timer & roActionTimer,ned_action_result & roResult);
	void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);

	void on_event_style_changed();
	void on_event_zoom_in();
	void on_event_zoom_out();

	//----- window live cycle events ---------------
	void on_window_initial_update();		//called when put on stack
	void on_window_final_update();			//called when removed from stack
	void on_window_on_top(bool bTopmost,cned_window * poSecondWindow);	//called when put/removed from top of stack

	//----- painting, rendering --------------------------------
	void _update_layout_for_display(const ned_action__ & roAction,ned_action_result & roResult,
		const ng_rect & roCompleteArena);
	void _prepare_paint_region(ng_region & roRegion);
	void _paint(cned_painter_ & roPainter);

	long print(ned_action_paint & roActionPaint,ned_action_result & roResult,const cned_paint_param & roPaintParam,SCP<IDispatch> poPrintInfoSinkSP);
	void print_preview(ned_action_paint & roActionPaint,ned_action_result & roResult,const cned_paint_param & roPaintParam);
	void normal_view();
	ewindow_view get_active_view_type() const;

	bool is_inside_hit_area(const ng_point & roPoint) const;
	
	void invalidate_paint_rect(const ng_rect & roAbsoluteRect);
	//------- transfer support --------
	void set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP);
	SCP<nui_transfer> get_transfer(ned_ident Ident);
	void start_transfer_iterator();
	bool next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP);

	//-------- page breaking ---------------------------------
	void do_page_breaks(const cned_page_break_param & roPageBreakParam);
	//-------------- sys disable ---------------
	void set_sys_disable(bool bSysDisable);
	bool is_sys_disable() const;

	//-------------- modified flag --------------
	void set_modified_flag(bool bModified);
	bool get_modified_flag() const;
	//------ property GET -----------------
	bool get_prop_is_stdcmd(long IdCmd) const;
	bool get_prop_button_visible(long IdCmd) const;
	long get_prop_iid() const;
	long get_prop_root_typeid() const;
	
	long get_prop_secid_read() const;
	long get_prop_secid_insert() const;
	long get_prop_secid_update() const;
	long get_prop_secid_delete() const;

	ned_ident get_prop_initial_focus() const;
	
	void get_prop_official_title(ng_string & roString) const;
//------ property SET -----------------
	void set_prop_is_stdcmd(long IdCmd,bool bDefine);
	void set_prop_button_visible(long IdCmd,bool bShow);
	void set_prop_script(const ng_string & roScriptCodeString);
	void set_prop_script_nxid(const ng_string& roScriptNXID);
	void set_prop_iid(long nPage_IID);
	void set_prop_root_typeid(long nRootTypeId);

	void set_prop_secid_read(long idsecRead);
	void set_prop_secid_insert(long idsecInsert);
	void set_prop_secid_update(long idsecUpdate);
	void set_prop_secid_delete(long idsecDelete);

	void set_prop_initial_position(ened_window_initial_pos eWIP);
	void set_prop_initial_focus(ned_ident nInitialFocus);

	long get_zoom() const;
	void set_zoom(long nZoom);
	void on_zoom_out();
	void on_zoom_in();
	//--------- scripting support -------------------------------
	virtual LPCTSTR GetScriptCode();
	virtual LPCTSTR GetScriptNXID();
	virtual void GetDocumentName(ng_string & roDocNameString);
	void init_transaction_ddr(CDispatchDynamicResolver * pDDR);
	void setup_defaults(long IdPageTypeCmd,bool bWithCursor);

	eInvokeResult invoke_method(const OLECHAR *pocName, CSmartOleVariant * pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant *poResultSmartOleVariant,bool bThrowIfNotExists);

	eInvokeResult fire_user_command(LPCTSTR lpFunctionName,CSmartOleVariant * pArgumentsSmartOleVariant,long lSize,bool bMustExists);
	eInvokeResult fire_std_command(long nCommandId,CSmartOleVariant * pArgumentsSmartOleVariant,long lSize);

	//dla integracji IDispatch'a
	HRESULT Window_GetIDsOfNames(LPOLESTR * rgszNames,UINT cNames,DISPID * rgDispId);
	HRESULT Window_Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError);

	//{{AFX_DISPATCH(cned_window)
	afx_msg VARIANT GetStartingfocusAUTO();
	afx_msg void SetStartingfocusAUTO(const VARIANT FAR& newValue);
	afx_msg LPDISPATCH GetFocusElementAUTO();
	afx_msg BOOL GetModifiedFlagAUTO();
	afx_msg void SetModifiedFlagAUTO(BOOL bModified);
	afx_msg LPDISPATCH CreateTransferAUTO(LPCTSTR lpTransferMode);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	virtual void OnFinalRelease();

	//-------------------- event helpers ----------------------------------------
	void _on_after_event(const ned_action__ & roAction,ned_action_result & roResult);
	void _build_in_on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);

	void _realize_initial_position(const ng_rect & roCompleteArena);

	void _prepare_special_paint(ened_window_special_effect eWSE);


	//--------------- command helpers --------------------
	static SCP<ned_event_command> _prepare_command(long nCmd);

	//---------------- internal mode and sheet management ----------------
	SCP<cned_window_sheet> _create_sheet();

	ewindow_view m_eActiveView;
	cned_window_view__ * _get_active_view() const;
	
	SCP<cned_normal_window_view>	m_poNormalViewSP;
	SCP<cned_sheet_window_view>		m_poSheetViewSP;	
	
	//--- up / down links -------------------------
	cned_arena * m_poArena;								//uplink

	//--- scripting support
	ng_string	m_oScriptCodeString;
	ng_string	m_strScriptNXID;
	bool m_abIsStdCmdDefined[ STD_COMMAND_COUNT ];
	bool m_abShowButton[ STD_COMMAND_COUNT ];

	long m_nPage_IID;			//iid strony - albo podany z XML, albo wygenerowany przez cndoc_page
	long m_nRootTypeId;
	CDynamicDispatchForwarer m_oTransaction_DispatchForwarder;
	bool m_bExistsSuggestionTransfer;

	ened_window_initial_pos		m_eWIP;		//pocz¹tkowa pozycja okna
	ned_ident					m_idInitialFocus;

	//----- to w³aœciwie powinno byæ w cndoc_navopage ---
	//-- ale tu jest wygodniej umieœciæ --------

	long						m_idsecRead;
	long						m_idsecInsert;
	long						m_idsecUpdate;
	long						m_idsecDelete;

	friend class cned_window_pb_manager;
	friend class cpb_window_split_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//--- scripting support
//--------------------------------------------------------------------
inline LPCTSTR cned_window::GetScriptCode()
{
	return m_oScriptCodeString;
}

inline LPCTSTR cned_window::GetScriptNXID()
{
	return m_strScriptNXID;
}

//------ property GET -----------------
inline bool cned_window::get_prop_is_stdcmd(long IdCmd) const
{
	if(IdCmd < CMD_STANDARDFIRST || IdCmd > CMD_STANDARDLAST)
	{
		return false;
	}
	return m_abIsStdCmdDefined[IdCmd-CMD_STANDARDFIRST];
}

inline bool cned_window::get_prop_button_visible(long IdCmd) const
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	return m_abShowButton[IdCmd-CMD_STANDARDFIRST];
}

inline long cned_window::get_prop_iid() const
{
	return m_nPage_IID;
}

inline long cned_window::get_prop_root_typeid() const
{
	return m_nRootTypeId;
}

inline long cned_window::get_prop_secid_read() const
{
	if(m_idsecRead != 0)
	{
		return m_idsecRead;
	}
	if(get_prop_root_typeid() != 0)
	{
		return get_prop_root_typeid() * 10 + STDR_READ;
	}
	return 0;
}

inline long cned_window::get_prop_secid_insert() const
{
	if(m_idsecInsert != 0)
	{
		return m_idsecInsert;
	}
	if(get_prop_root_typeid() != 0)
	{
		return get_prop_root_typeid() * 10 + STDR_INSERT;
	}
	return 0;
}

inline long cned_window::get_prop_secid_update() const
{
	if(m_idsecUpdate != 0)
	{
		return m_idsecUpdate;
	}
	if(get_prop_root_typeid() != 0)
	{
		return get_prop_root_typeid() * 10 + STDR_UPDATE;
	}
	return 0;
}

inline long cned_window::get_prop_secid_delete() const
{
	if(m_idsecDelete != 0)
	{
		return m_idsecDelete;
	}
	if(get_prop_root_typeid() != 0)
	{
		return get_prop_root_typeid() * 10 + STDR_DELETE;
	}
	return 0;
}

inline ned_ident cned_window::get_prop_initial_focus() const
{
	return m_idInitialFocus;
}

//------ property SET -----------------

inline void cned_window::set_prop_is_stdcmd(long IdCmd,bool bDefine)
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	m_abIsStdCmdDefined[IdCmd-CMD_STANDARDFIRST] = bDefine;
}

inline void cned_window::set_prop_button_visible(long IdCmd,bool bShow)
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	m_abShowButton[IdCmd-CMD_STANDARDFIRST] = bShow;
}

inline void cned_window::set_prop_iid(long nPage_IID)
{
	ASSERT(get_prop_iid() == 0);	//mo¿na zmieniæ tylko 1-raz
	ASSERT(nPage_IID != 0);

	m_nPage_IID = nPage_IID;
}

inline void cned_window::set_prop_root_typeid(long nRootTypeId)
{
	ASSERT(get_prop_root_typeid() == 0);	//mo¿na zmieniæ tylko 1-raz
	ASSERT(nRootTypeId != 0);
	m_nRootTypeId = nRootTypeId;
}

inline void cned_window::set_prop_secid_read(long idsecRead)
{
	m_idsecRead = idsecRead;
}

inline void cned_window::set_prop_secid_insert(long idsecInsert)
{
	m_idsecInsert = idsecInsert;
}

inline void cned_window::set_prop_secid_update(long idsecUpdate)
{
	m_idsecUpdate = idsecUpdate;
}

inline void cned_window::set_prop_secid_delete(long idsecDelete)
{
	m_idsecDelete = idsecDelete;
}

inline void cned_window::set_prop_initial_position(ened_window_initial_pos eWIP)
{
	m_eWIP = eWIP;
}

inline void cned_window::set_prop_initial_focus(ned_ident idInitialFocus)
{
	m_idInitialFocus = idInitialFocus;
}

//---------------- internal mode and sheet management ----------------
inline ewindow_view cned_window::get_active_view_type() const
{
	return m_eActiveView;
}

inline cned_window_view__ * cned_window::_get_active_view() const
{
	switch(m_eActiveView)
	{
	case wv_normal:
		ASSERT(m_poNormalViewSP.PointsObject());
		return m_poNormalViewSP.ConstCastObject();
	case wv_sheet:
		ASSERT(m_poSheetViewSP.PointsObject());
		return m_poSheetViewSP.ConstCastObject();
	default:
		ASSERT(false);
		return NULL;
	}
}

inline SCP<cned_element> cned_window::get_element_on_ident(const ned_ident idElement) const
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->get_element_on_ident(idElement);
}


//--------------- transfer support --------------------------------------------------------
inline void cned_window::set_transfer(ned_ident idElement,SCP<nui_transfer> & rpoTransferSP)
{
	ASSERT(_get_active_view() != NULL);

	_get_active_view()->set_transfer(idElement,rpoTransferSP);

	if(rpoTransferSP.PointsObject())
	{
		if(rpoTransferSP->get_type() == ett_edit_ref || rpoTransferSP->get_type() == ett_row_edit_ref)
		{
			m_bExistsSuggestionTransfer = true;
		}
	}
}

inline SCP<nui_transfer> cned_window::get_transfer(ned_ident idElement)
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->get_transfer(idElement);
}

inline void cned_window::start_transfer_iterator()
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->start_transfer_iterator();
}

inline bool cned_window::next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP)
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->next_transfer_iterator(ridElement,rpoTransferSP);
}

//-------------- sys disable ---------------
inline void cned_window::set_sys_disable(bool bSysDisable)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->set_sys_disable(bSysDisable);
}

inline bool cned_window::is_sys_disable() const
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->is_sys_disable();
}

inline long cned_window::get_zoom() const
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->get_zoom();
}

inline void cned_window::set_zoom(long nZoom)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->set_zoom(nZoom);
}

//-------------- modified flag --------------
inline void cned_window::set_modified_flag(bool bModified)
{
	ASSERT(_get_active_view() != NULL);
	_get_active_view()->set_modified_flag(bModified);
}

inline bool cned_window::get_modified_flag() const
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->get_modified_flag();
}

//-------------------------------------------------------------------
//cned_window_view__
//-------------------------------------------------------------------
inline cned_window_view__::cned_window_view__(cned_window * poWindow) :
	m_poWindow(poWindow)
{
}

//-------------------------------------------------------------------
//	cned_sheet_window_view 
//-------------------------------------------------------------------
inline void cned_sheet_window_view::get_current_sheet_coord(long & rnX,long & rnY) const
{
	rnX = m_nCurrentSheetX;
	rnY = m_nCurrentSheetY;
}

//-------------------------------------------------------------------
inline void _init_cell(SCP<ned::cned_window_sheet> * pObject)
{
	(*pObject) = SCP<ned::cned_window_sheet>();
}

inline void _clear_cell(SCP<ned::cned_window_sheet> * pObject)
{
	(* pObject) = 0;
}

}

#else
	#error __FILE__ already included
#endif
