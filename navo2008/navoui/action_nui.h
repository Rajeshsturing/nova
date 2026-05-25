/*
	NAVO Enterprise 2008
	21.07.2002


*/

#ifndef _ACTION_NUI_H_
#define _ACTION_NUI_H_



class nui_action_oleevent : public nui_action__
{
public:
	nui_action_oleevent(ng_dc & roDC,long IdCtrl,AFX_EVENT* pEvent) :
		nui_action__(roDC),
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




//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

class nui_event_command : public nui_event_info__
{
public:
	nui_event_command(nui_ident nFiringElement) :
		nui_event_info__(nFiringElement)
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

class nui_event_olecontrol : public nui_event_info__
{
public:
	nui_event_olecontrol(nui_ident nFiringElement,AFX_EVENT * pOleEvent) :
		nui_event_info__(nFiringElement),
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


#else
	#error __FILE__ already included
#endif

