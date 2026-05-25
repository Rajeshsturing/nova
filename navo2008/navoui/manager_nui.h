/*
	NAVO Enterprise 2008
	15.04.2002
	
	cnui_element_manager
		- manager_elementów


	- dostarcza elementy / swapuje unswapuje elementy
	- dostarcza ró¿ne providery (style, picture itd.)

*/


#ifndef _MANAGER_NUI_H_
#define _MANAGER_NUI_H_

class cnui_element_manager : public CInterface__
{
	void on_compact_memory();
	bool is_low_memory_mode() const;

	//element "mini info"
	bool is_element_tabstop(const nui_ident Ident) const;

	//funkcja pomocnicza - z³o¿enie istabstop, isdisabled i ishidden tree - w celu przyœpieszenia
	bool can_element_accept_focus(const nui_ident Ident) const;

	bool is_active() const
	{
		return m_bIsActive;
	}
	void set_active_flag(bool bActive)
	{
		m_bIsActive = bActive;
	}
	bool _was_element_with_script_support() const;


	void __destroy_element(cnui_element * poElement);

private:
	void _add_new_element(SCP<cnui_element> poNewElementSP);
	

	static void on_compact_memory_in_array(CArray<cnui_element_entry,cnui_element_entry & > & roArray);
	bool	m_bQuitting;
	bool	m_bWasElementWithStdScriptSupport;
	bool	m_bIsActive;
	

	friend class cnui_arena_manager;
};



inline void cnui_element_manager::enter_dragging(const nui_drag_info & roDragInfo)
{
	m_oDragInfo = roDragInfo;
}

inline void cnui_element_manager::exit_dragging()
{
	m_oDragInfo = nui_drag_info();
}

inline nui_drag_info & cnui_element_manager::get_drag_info()
{
	return m_oDragInfo;
}



inline bool cnui_element_manager::is_element_tabstop(const nui_ident Ident) const
{
	return get_miniinfo_on_ident(Ident).is_tabstop();
}


inline bool cnui_element_manager::_was_element_with_script_support() const
{
	return m_bWasElementWithStdScriptSupport;
}



#else
	#error __FILE__ already included
#endif
 