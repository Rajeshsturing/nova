/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	01.08.2002

	manager handlerów zdarzeñ 
*/


#ifndef _EVENT_HANDLER_NDOC_H_
#define _EVENT_HANDLER_NDOC_H_

class cndoc_event_manager;
class nui_transfer;
class ned::ned_event_info__;
class ned::cned_window;
class ned::cned_element;
enum ned::eEventInfoType;
class CNEO_trans;
class CNEO_user;
class ned::ned_event_command_list;
class CCommandList;

struct cndoc_event_param
{
	cndoc_event_param();

	cndoc_event_manager * m_poEventManager;
	nui_transfer *		  m_poTransfer;
	ned_event_info__ *	  m_poEventInfo;
	cned_window *         m_poWindow;
	CNEO_trans *		  m_poTransaction;
	SCP<CNEO_user>		  m_poObjectSP;
};

enum eTransferResult
{
	tr_ok,
	tr_failed,
	tr_void
};


typedef eTransferResult (* pfEventHandler)(cndoc_event_param &);


class cndoc_event_manager : public CInterface__
{
public:
	cndoc_event_manager();
	~cndoc_event_manager();

	eTransferResult invoke(cndoc_event_param & roEventParam);

	void mark_failed_handler(ned_ident Ident,eEventInfoType);
	bool is_handler_failed(ned_ident Ident,eEventInfoType) const;

	void build_custom_cmd_list(ned_event_command_list * poEventCmdList,cned_window * poWindow);
private:
	static pfEventHandler _g_aHandlers[ ett_max ][eit_max_handler];

	CMap<hyper,hyper,bool,bool>		m_oFailedHandlerMap;
};

SCP<ned::cned_element> get_firing_element(cndoc_event_param & roEventParam);
void set_valid_state(SCP<ned::cned_element> & rpoElementSP,bool bValid);

ned_ident supply_grid_info(SCP<ned::cned_element> & rpoElementSP,long & rnRowNr);

ned_ident supply_grid_info2(SCP<ned::cned_element> & rpoElementSP,long & rnRowNr,
				SCP<nui_transfer_1> & rpoGridTransferSP);

void invoke_build_cmd_list(cndoc_event_manager * poEventManager,cned_window * poWindow,
						   ned::cned_element * poElement,CCommandList * poCommandList);

#else
	#error __FILE__ already included
#endif
