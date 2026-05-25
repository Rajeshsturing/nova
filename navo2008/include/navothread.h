/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoThread

	CWinThread but with CoOleInitialize and SCP<> able
*/

#ifndef _NAVOTHREAD_H_
#define _NAVOTHREAD_H_


class CNavoThread: public CWinThread
{
public:
	CNavoThread(CNavoOleInitHolder::EType eType);
	~CNavoThread(){}
	DELEGATE_UNKNOWN_ON_CMDTARGET
	
	virtual int Run() = 0;
	virtual CNavoException & GetErrorStorage() = 0;
protected:

	CNavoOleInitHolder::EType m_eOleInitType;
	static unsigned int NavoThreadFunction(void *pThis);
};


#else
	#error __FILE__ already included
#endif
