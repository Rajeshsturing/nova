/*
	NAVO Enterprise 2008
	15.07.2002
	
	cnui_window
		- "okno"
*/

#ifndef _NUI_WINDOW_H_
#define _NUI_WINDOW_H_

#ifdef nigdy_nie_definiuj_bo_stare_i_nie_uzywane

const long STD_COMMAND_COUNT = 24;

class cnui_window : public CCmdTargetInterface, public CScriptUser
{
public:
	cnui_window(cnui_arena * poArena,SCP<cnui_element_manager> poElementManagerSP);
	~cnui_window();

	bool is_inside_hit_area(const ng_point & roPoint) const;

	void on_event_olecontrol(const nui_action_oleevent & roActionOleEvent,nui_action_result & roResult);
	void on_event_size_changed();
	void on_event_on_top(bool bTopmost);

	void on_compact_memory();

	//------------------- property get --------------
	bool get_prop_is_stdcmd(long IdCmd) const;
	bool get_prop_button_visible(long IdCmd) const;
	bool get_prop_minimized() const;
	//------------------- property set --------------
	void set_prop_script(const ng_string & roScriptCodeString);
	void set_prop_is_stdcmd(long IdCmd,bool bDefine);
	void set_prop_button_visible(long IdCmd,bool bShow);
	void set_prop_minimized(bool bMinimized);

	virtual void OnFinalRelease();
	
	void mark_repaint_all();
	//--------- scripting support -------------------------------
	//for CScriptUser

	virtual void GetDocumentName(ng_string & roDocNameString);
	//-----------------------------------------------------------
	void setup_defaults(long IdPageTypeCmd,bool bWithCursor);
	void init_transaction_ddr(CDispatchDynamicResolver * pDDR);
private:
	SCP<cnui_toplevelpage> __get_toplevelpage() const;

	void _process_event_keydown(const nui_ident TargetIdent,const nui_action_kbd & roActionKBD,nui_action_result & roResult);
	void _process_event_mouse_click(const nui_ident TargetIdent,const nui_action_mouse & roActionMouse,nui_action_result & roResult);
	void _process_event_mouse_endclick(const nui_ident TargetIdent,const nui_action_mouse & roActionMouse,nui_action_result & roResult);
	void _process_event_mouse_over(const nui_ident TargetIdent,const nui_action_mouse & roActionMouse,nui_action_result & roResult);
	void _process_event_olecontrol(const nui_ident TargetIdent,const nui_action_oleevent & roActionOleEvent,nui_action_result & roResult);

	eCursorType _process_event_set_cursor(const nui_ident TargetIdent,const ng_point & roPoint);

	void _on_after_event(const nui_action__ & roAction,nui_action_result & roResult);



	void _build_in_on_event_keydown(const nui_action_kbd & roActionKBD,nui_action_result & roResult);

	nui_ident __find_next_focusable_element(nui_ident idStarting);

	nui_ident _find_mouse_target_element(ng_point oPoint);

	void add_layers(cnui_layerstack & roLayerStack) const;

	static LPCTSTR _get_std_command_name(long nCommandId);

	long			 m_nRootTypeId;
	long			 m_nFixedPageIID;
	bool			 m_bMinimized;
	CDynamicDispatchForwarer m_oTransaction_DispatchForwarder;

	bool m_abIsStdCmdDefined[ STD_COMMAND_COUNT ];
	bool m_abShowButton[ STD_COMMAND_COUNT ];
	long		m_nUpdateRecursion;

	friend class cnui_arena;
};


inline bool cnui_window::get_prop_is_stdcmd(long IdCmd) const
{
	if(IdCmd < CMD_STANDARDFIRST || IdCmd > CMD_STANDARDLAST)
	{
		return false;
	}
	return m_abIsStdCmdDefined[IdCmd-CMD_STANDARDFIRST];
}

inline bool cnui_window::get_prop_button_visible(long IdCmd) const
{
	ASSERT(IdCmd >= CMD_STANDARDFIRST && IdCmd <= CMD_STANDARDLAST);
	return m_abShowButton[IdCmd-CMD_STANDARDFIRST];
}

inline bool cnui_window::get_prop_minimized() const
{
	return m_bMinimized;
}

#endif

#else
	#error __FILE__ already included
#endif
