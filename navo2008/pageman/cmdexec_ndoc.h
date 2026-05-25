/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_commandexecutor
*/

#ifndef _COMMAND_EXEC_NDOC_H_
#define _COMMAND_EXEC_NDOC_H_

class cndoc_application;

class cndoc_commandexecutor : public CInterface__
{
public:
	cndoc_commandexecutor(cndoc_application * poApplication);
	~cndoc_commandexecutor();
	void mark_quitting();

	void yield();
	void exit_yield();


	void wait_command(long nCommandNumber);		//out of thread
	void wait_idle();							//out of thread
	long post_command(SCP<CHyperLinkInfo> & rpoCommandHLISP,bool bWaitable);

	void _message_loop();
	void _on_new_command();
private:
	bool _on_idle();
	bool _pre_translate_message(MSG & roMsg);
	SCP <CHyperLinkInfo> _retrieve_posted_command();
	void _process_command(SCP <CHyperLinkInfo> & roHLISCP);

	CSimpleCriticalSection m_oPostedCommandCS;
	//{{
		CList <SCP <CHyperLinkInfo>, SCP <CHyperLinkInfo> &> m_oPostedCommandList;
	//}}
	CEvent	m_oEventExitLoop;
	CEvent	m_oEventNewCmd;
	CEvent	m_oEventCommandProcessed;
	CEvent	m_oEventGoingIdle;
	long	m_nCommandCounter;
	CArray<long,long>	m_oProcessedWaitableCommands;
	bool	m_bQuitting;
	cndoc_application * m_poApplication;
};

inline void cndoc_commandexecutor::exit_yield()
{
	m_oEventExitLoop.SetEvent();
}

#else
	#error __FILE__ already included
#endif
