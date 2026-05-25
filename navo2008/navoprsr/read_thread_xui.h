/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_reader_thread
		w¹tek wczytuj¹cy	
		
*/

#ifndef _READ_THREAD_XUI_H_
#define _READ_THREAD_XUI_H_

class cxmlui_main_parser;

class cxmlui_reader_thread : public CNavoThread, public CSAXHandlerController__
{
public:
	static SCP<cxmlui_reader_thread> create(SCP<cned_window> pWindowSP,
			  SCP<CDefinitionManager> poDefinitionManagerSP,
			  SCP<IStream> poStreamSP,long nInitialChunkSize);

	bool is_error() const;
	void abort();
	void complete();

	bool wait_chunk_complete();
	void next_chunk(long nChunkSize);
	virtual void on_chunk_completed(CSAXHandler__ * poSAXHandler);
private:
	cxmlui_reader_thread(SCP<cned_window> pWindowSP,
			  SCP<CDefinitionManager> poDefinitionManagerSP,SCP<IStream> poStreamSP,long nInitialChunkSize);
	~cxmlui_reader_thread();
	void _clean();
	virtual int Run();
	virtual CNavoException & GetErrorStorage();

	SCP<cned_window>		m_pWindowSP;
	SCP<CDefinitionManager> m_poDefinitionManagerSP;
	SCP<IStream>			m_poStreamSP;
	long					m_nInitialChunkSize;

	CNavoException			m_oErrorStorage;	
	
	cxmlui_main_parser *	m_poParser;		//ten pointer jest po to, aby nie ci¹gn¹æ definicji xmlui_main_parser po projekcie

	enum eState
	{
		state_none,
		state_running,
		state_abort,
		state_completed,
		state_error
	};

	eState m_eState;
	CEvent m_oWorkReadyEvent;
	CEvent m_oWorkContinueEvent;
};

inline bool cxmlui_reader_thread::is_error() const
{
	return (m_eState == state_error);
}

#else
	#error __FILE__ already included
#endif

