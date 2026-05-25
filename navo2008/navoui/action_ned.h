/*
	NAVO Enterprise 2008
	2003-02-22

	navo enhanced display (NED)

	action (events) related informations

*/

#ifndef _ACTION_NED_H_
#define _ACTION_NED_H_

class CCommandList;

namespace ned
{
//----------------------------------------------------------------------------------
//---------------------- input -----------------------------------------------------
//----------------------------------------------------------------------------------

class ned_action__
{
public:
	ng_dc & get_dc() const
	{
		return m_roDC;
	}
protected:
	ned_action__(ng_dc & roDC):
		 m_roDC(roDC)
	{
	}
	ng_dc & m_roDC;
};

class ned_action_paint : public ned_action__
{
public:
	ned_action_paint(ng_dc & roDC) :
		ned_action__(roDC)
	{
	}
};

class ned_action_kbd : public ned_action__
{
public:
	ned_action_kbd(ng_dc & roDC,UINT nChar,UINT nFlags);

	UINT get_keycode() const 
	{ 
		return m_nChar; 
	}
	UINT get_scancode()	const 
	{ 
		return m_nFlags & 0x00FF; 
	}
	bool is_ALT() const		//Lewy Alt
	{
		return m_bIsAlt;
	}
	bool is_CTRL() const		//dowolny Ctrl
	{
		return m_bIsCtrl;
	}
	bool is_SHIFT() const		//dowolny Shift
	{
		return m_bIsShift;
	}
	bool is_normal() const	//¿aden z Ctrl,Alt,Shift nie jest wciœniêty
	{
		return !is_ALT() && !is_CTRL() && !is_SHIFT();
	}
private:
	bool m_bIsAlt;
	bool m_bIsCtrl;
	bool m_bIsShift;
	UINT m_nChar;
	UINT m_nFlags;
};

class ned_action_mouse : public ned_action__
{
public:
	ned_action_mouse(ng_dc & roDC,const ng_point & roMousePosition,UINT nFlags) :
		ned_action__(roDC),
		m_nFlags(nFlags),
		m_oMousePosition(roMousePosition)
	{
	}
	ned_action_mouse(const ned_action_mouse & roActionMouse) :
		ned_action__(roActionMouse.get_dc()),
		m_nFlags(roActionMouse.get_flags()),
		m_oMousePosition(roActionMouse.get_mouse_position())
	{
	}
	const ng_point & get_mouse_position() const
	{
		return m_oMousePosition;
	}
	UINT get_flags() const 
	{ 
		return m_nFlags; 
	}
	bool is_LEFT_click() const
	{
		return (m_nFlags & MK_LBUTTON) != 0;
	}
	bool is_RIGHT_click() const
	{
		return (m_nFlags & MK_RBUTTON) != 0;
	}
	bool is_DOUBLE_click() const
	{
		return (m_nFlags & MK_DBLCLK) != 0;
	}
protected:
	ng_point m_oMousePosition;
	UINT	 m_nFlags;
};

class ned_action_mouse_wheel : public ned_action_mouse
{
public:
	ned_action_mouse_wheel(ng_dc & roDC,const ng_point & roMousePosition,UINT nFlags,long nDelta) :
		ned_action_mouse(roDC,roMousePosition,nFlags),
		m_nDelta(nDelta)
	{
	}
	const long get_delta() const
	{
		return m_nDelta;
	}
private:
	long	m_nDelta;
};

class cned_arena;
class cned_window;
class cned_element_manager;

class ned_action_mouse_drag : public ned_action_mouse
{
public:
	ned_action_mouse_drag(const ned_action_mouse & roActionMouse,
		cned_element_manager * poManager,ned_ident idElementOver) :
		ned_action_mouse(roActionMouse),
		m_poManager(poManager),
		m_idElementOver(idElementOver)
	{
	}
	
	ned_ident get_element() const
	{
		return m_idElementOver;
	}
	cned_element_manager * get_manager() const
	{
		return m_poManager;
	}
private:
	cned_element_manager * m_poManager;
	ned_ident	m_idElementOver;
};

class ned_action_timer : public ned_action__
{
public:
	ned_action_timer(ng_dc & roDC,long IdTimer):
		ned_action__(roDC),
		m_nIdTimer(IdTimer)
	{
	}
	long get_timerid() const
	{
		return m_nIdTimer;
	}
private:
	long	m_nIdTimer;
};

class ned_action_focus : public ned_action__
{
public:
	ned_action_focus(ng_dc & roDC,ned_ident GotFocus,ned_ident LostFocusIdent):
		ned_action__(roDC),
		m_GotFocusIdent(GotFocus),
		m_LostFocusIdent(LostFocusIdent)
	{
	}
	ned_ident get_got_focus_ident() const
	{
		return m_GotFocusIdent;
	}
	ned_ident get_lost_focus_ident() const
	{
		return m_LostFocusIdent;
	}
private:
	ned_ident m_GotFocusIdent;
	ned_ident m_LostFocusIdent;
};

class ned_action_oleevent : public ned_action__
{
public:
	ned_action_oleevent(ng_dc & roDC,long IdCtrl,AFX_EVENT* pEvent) :
		ned_action__(roDC),
		m_IdCtrl(IdCtrl),
		m_pEvent(pEvent)
	{
	}
	long get_idctrl() const
	{
		return m_IdCtrl;
	}
	AFX_EVENT * get_event_data() const
	{
		return m_pEvent;
	}
private:
	long m_IdCtrl;
	AFX_EVENT * m_pEvent;
};


//command 'posted' to control
class ned_action_command : public ned_action__
{
public:
	ned_action_command(ng_dc & roDC,const ned_ident idTargetElement,
		enum eStdControlCommandVerb eVerb,SCP<CHyperLinkInfo> & rpoCommandHLISP) :
		ned_action__(roDC),
		m_idTargetElement(idTargetElement),
		m_eVerb(eVerb),
		m_poCommandHLISP(rpoCommandHLISP)
	{
	}
		
	SCP<CHyperLinkInfo> get_command() const
	{
		return (const_cast<ned_action_command*>(this))->m_poCommandHLISP;
	}
	enum eStdControlCommandVerb	get_verb() const
	{
		return m_eVerb;
	}
	const ned_ident get_target() const
	{
		return m_idTargetElement;
	}
private:
	const ned_ident m_idTargetElement;
	enum eStdControlCommandVerb	m_eVerb;
	SCP<CHyperLinkInfo>	m_poCommandHLISP;
};
//----------------------------------------------------------------------------------
//---------------------- output ----------------------------------------------------
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//abstract info class
//----------------------------------------------------------------------------------
enum eEventInfoType
{
	eit_min_handler = 0,
	eit_newdata		= eit_min_handler,
	eit_getdata		= 1,
	eit_gotfocus	= 2,
	eit_lostfocus	= 3,
	eit_row_oper	= 4,		//row operations
	eit_oleevent	= 5,
	eit_tabitem_activ = 6,
	eit_max_handler = eit_tabitem_activ + 1,
	eit_command_list,
	eit_command,
};

class ned_event_info__ : public CInterface__
{
public:
	ned_event_info__(ned_ident idFiringElement) :
		m_idFiringElement(idFiringElement)
	{}
	const ned_ident get_firing_element() const
	{
		return m_idFiringElement;
	}
	virtual eEventInfoType get_type() const = 0;
private:
	ned_ident	m_idFiringElement;
};


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

class ned_event_command : public ned_event_info__
{
public:
	ned_event_command(ned_ident nFiringElement) :
		ned_event_info__(nFiringElement)
	{
	}
	void set_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
	{
		m_poCommandHLISP = rpoCommandHLISP;
	}
	SCP<CHyperLinkInfo>	get_command()
	{
		return m_poCommandHLISP;
	}
	virtual eEventInfoType get_type() const
	{
		return eit_command;
	}
private:
	SCP<CHyperLinkInfo>	m_poCommandHLISP;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_newdata : public ned_event_info__
{
public:
	ned_event_newdata(ned_ident nFiringElement) :
		ned_event_info__(nFiringElement)
	{
	}
	void set_data(const CSmartOleVariant & roSOV)
	{
		m_oDataSOV = roSOV;
	}
	const CSmartOleVariant & get_data() const
	{
		return m_oDataSOV;
	}
	virtual eEventInfoType get_type() const
	{
		return eit_newdata;
	}
private:
	CSmartOleVariant m_oDataSOV;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_getdata : public ned_event_info__
{
public:
	ned_event_getdata(ned_ident nFiringElement) :
		ned_event_info__(nFiringElement)
	{
	}
	virtual eEventInfoType get_type() const
	{
		return eit_getdata;
	}
private:
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_gotfocus : public ned_event_info__
{
public:
	ned_event_gotfocus(ned_ident nGotFocusElement,ned_ident nLostFocusElement) :
		ned_event_info__(nGotFocusElement),
		m_idLostFocusElement(nLostFocusElement)
	{
	}
	virtual eEventInfoType get_type() const
	{
		return eit_gotfocus;
	}
	ned_ident get_lost_focus_element() const
	{
		return m_idLostFocusElement;
	}
private:
	ned_ident m_idLostFocusElement;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_lostfocus : public ned_event_info__
{
public:
	ned_event_lostfocus(ned_ident nLostFocusElement,ned_ident nGotFocusElement) :
		ned_event_info__(nLostFocusElement),
		m_idGotFocusElement(nGotFocusElement)
	{
	}
	virtual eEventInfoType get_type() const
	{
		return eit_lostfocus;
	}
	ned_ident get_got_focus_element() const
	{
		return m_idGotFocusElement;
	}
private:
	ned_ident m_idGotFocusElement;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_row_operation : public ned_event_info__
{
public:
	enum eOperation
	{
		oper_invalid	= -1,
		oper_insert		= 1,
		oper_delete		= 2,
		oper_delete_all = 3,
		oper_move		= 4,
	};
	ned_event_row_operation(ned_ident nFiringElement) :
		ned_event_info__(nFiringElement),
		m_nDataRowNr(-1),
		m_nSecondDataRowNr(-1),
		m_eOperation(oper_invalid)
	{
	}
	void set_data_row_nr(long nDataRowNr)
	{
		m_nDataRowNr = nDataRowNr;
	}
	long get_data_row_nr() const
	{
		ASSERT(m_nDataRowNr != -1);
		return m_nDataRowNr;
	}
	void set_second_data_row_nr(long nDataRowNr)
	{
		m_nSecondDataRowNr = nDataRowNr;
	}
	long get_second_data_row_nr() const
	{
		ASSERT(m_nSecondDataRowNr != -1);
		return m_nSecondDataRowNr;
	}
	void set_operation(eOperation eOper)
	{
		m_eOperation = eOper;
	}
	eOperation get_operation() const
	{
		ASSERT(m_eOperation != oper_invalid);
		return m_eOperation;
	}
	virtual eEventInfoType get_type() const
	{
		return eit_row_oper;
	}
private:
	long	m_nDataRowNr;
	long	m_nSecondDataRowNr;
	eOperation m_eOperation;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

class ned_event_command_list : public ned_event_info__
{
public:
	ned_event_command_list(ned_ident nFiringElement);
	virtual eEventInfoType get_type() const
	{
		return eit_command_list;
	}
	SCP<CCommandList> get_command_list();

	ng_point m_oStartPoint;
private:
	SCP<CCommandList>	m_poCommandListSP;
};

//----------------------------------------------------------------------------------

class ned_event_olecontrol : public ned_event_info__
{
public:
	ned_event_olecontrol(ned_ident nFiringElement,AFX_EVENT * pOleEvent) :
		ned_event_info__(nFiringElement),
		m_pEvent(pOleEvent)
	{
		ASSERT(m_pEvent);
	}
	virtual eEventInfoType get_type() const
	{
		return eit_oleevent;
	}
	AFX_EVENT * get_event_data() const
	{
		return m_pEvent;
	}
private:
	AFX_EVENT * m_pEvent;
};

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
class ned_event_tabitem_activation : public ned_event_info__
{
public:
	ned_event_tabitem_activation(ned_ident nFiringElement,long nActiveItemNr,bool bFirstTime) :
		ned_event_info__(nFiringElement),
		m_nActiveItemNr(nActiveItemNr),
		m_bFirstTime(bFirstTime)
	{
	}
	virtual eEventInfoType get_type() const
	{
		return eit_tabitem_activ;
	}
	long get_active_item_nr() const
	{
		return m_nActiveItemNr;
	}
	bool get_first_time_flag() const
	{
		return m_bFirstTime;
	}
private:
	long m_nActiveItemNr;
	bool m_bFirstTime;
};
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

class ned_action_result
{
public:
	ned_action_result() :
		m_bProcessed(false)
	{
	}
	void set_processed()
	{
		m_bProcessed = true;
	}
	bool is_processed() const
	{
		return m_bProcessed;
	}
	void add_info(ned_event_info__ * poInfo)
	{
		SCP<ned_event_info__> poInfoSP = NewSCP<ned_event_info__>(poInfo,true);
		m_oInfoArray.Add(poInfoSP);
		set_processed();
	}
	SCP<ned_event_info__> get_info(long Index)
	{
		if(Index <= m_oInfoArray.GetUpperBound())
		{
			return m_oInfoArray[ Index ];
		}
		return SCP<ned_event_info__>();
	}
private:
	CArray< SCP<ned_event_info__>, SCP<ned_event_info__> & > m_oInfoArray;
	bool m_bProcessed;
};

SCP<CCommandList> _retrieve_command_list(ned_event_info__ * poEventInfo);
SCP<CCommandList> _create_or_get_command_list(ned_action_result & roResult,ned_ident idTarget);
ng_point & _retrieve_command_list_start_point(ned_event_info__ * poEventInfo);

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// inlines
//----------------------------------------------------------------------------------

inline ned_action_kbd::ned_action_kbd(ng_dc & roDC,UINT nChar,UINT nFlags) :
	ned_action__(roDC)
{
	m_nChar		= nChar;
	m_nFlags	= nFlags;
	//OS_API_CALL
	m_bIsCtrl	= (::GetKeyState(VK_CONTROL) & 0x80) != 0;
	m_bIsAlt	= (::GetKeyState(VK_MENU) & 0x80)	 != 0;
	m_bIsShift	= (::GetKeyState(VK_SHIFT) & 0x80)   != 0;
}


}

#else
	#error __FILE__ already included
#endif

