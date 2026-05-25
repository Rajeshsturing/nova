/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCommandExecutor - wykonawca komend, mo¿e byæ wo³any z ró¿nych w¹tków
*/

#ifndef _COMMANDEXECUTOR_H_
#define _COMMANDEXECUTOR_H_

class CUserThread;
class CTreeXMLDataProvider;

class CCommandExecutor
{
public:
	CCommandExecutor(CUserThread * poUserThread);
	void PostHLICommand(SCP <CHyperLinkInfoWithResult> & roHLISCP);

	void Run();
	void OnMenuCommand(long nMenuNodeId);
	bool IsMenuCommandEnabled(long nMenuNodeId);
	void create_menu_on_stream(SCP<IStream> & rpoStreamSP,HMENU hTopMenu);
	
	void set_exit_loop()
	{
		_set_exit_loop();
	}
	void _message_loop();
	void _process_command(SCP <CHyperLinkInfoWithResult> & roHLISCP);
private:
	void _on_new_command();
	SCP <CHyperLinkInfoWithResult> _retrieve_posted_command();
	void _add_to_processed_command(SCP <CHyperLinkInfoWithResult> & rpoHLISP);
	void _wait_for_result(SCP <CHyperLinkInfoWithResult> & roHLISCP);

	void _set_exit_loop();

	bool _pre_translate_message(MSG & roMsg);

	CSimpleCriticalSection m_oPostedCommandCS;
	//{{
	CList <SCP <CHyperLinkInfoWithResult>, SCP <CHyperLinkInfoWithResult> &> m_oPostedCommandList;
	CList <SCP <CHyperLinkInfoWithResult>, SCP <CHyperLinkInfoWithResult> &> m_oProcessedCommandList;
	CEvent	m_oCommandReadyEvent;
	//}}
	DWORD	m_hBaseThreadId;
	CEvent	m_oEventExitLoop;
	CEvent	m_oEventNewCmd;
	bool	m_bFirstCmd;

	SCP<CTreeXMLDataProvider>	m_poMenuCommandTXDPSP;

	CUserThread * m_poUserThread; //uplink
};

#else
	#error __FILE__ already included
#endif
