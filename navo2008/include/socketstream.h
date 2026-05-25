/*
	NAVO Enterprise 2001

	CSocketStream
		
	Obiekt implementuj¹cy IStream na socketach

*/

#ifndef _SOCKETSTREAM_H_
#define _SOCKETSTREAM_H_


class CSocketStream : public CCmdTargetWithErrorInfo
{
public:
	static SCP<IStream> Get(LPCTSTR lpServer,long nPort,bool bWaitingRead);
	static SCP<IStream> Get(CSmartSocket & roSocket,bool bWaitingRead);

	CSocketStream(LPCTSTR lpServer,long nPort,bool bWaitingRead);
	CSocketStream(CSmartSocket & roSocket,bool bWaitingRead);
	~CSocketStream();
	bool _read_wait(DWORD dwTime);
	SCP<IStream> GetStreamSP()
	{
		SCP<IStream> poIStreamSP;
		poIStreamSP.QueryInterface(this);
		return poIStreamSP;
	}
private:
	//{{AFX_MSG(CSocketStream)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CSocketStream)
	afx_msg void OpenAUTO(LPCTSTR lpServer,long nPort);
	//}}AFX_DISPATCH
	CSocketStream();
	void _init(LPCTSTR lpServer,long nPort,bool bWaitingRead);
	void _init(CSmartSocket & roSocket,bool bWaitingRead);



	BEGIN_INTERFACE_PART(Stream, IStream)
		STDMETHOD(Read)(void *pData, unsigned long lLength, unsigned long *plBytesRead);
		STDMETHOD(Seek)(LARGE_INTEGER liOffset, unsigned long lOrigin,
			ULARGE_INTEGER * pliNewPointer);
		STDMETHOD(Write)(const void *pData, unsigned long lLength, unsigned long *plBytesWritten);
		STDMETHOD(SetSize)(ULARGE_INTEGER ulSize);
		STDMETHOD(CopyTo)(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten);
		STDMETHOD(Commit)(unsigned long);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(Stat)(STATSTG * pStatStg, unsigned long lFlags);
		STDMETHOD(Clone)(IStream ** ppIStream);
	END_INTERFACE_PART(Stream)

	DECLARE_INTERFACE_MAP();
	DECLARE_DISPATCH_MAP()
	DECLARE_OLECREATE(CSocketStream)
	DECLARE_DYNCREATE(CSocketStream)
private:
	HRESULT __Read(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT __Write(const void *pData, unsigned long lLength, unsigned long *plBytesWritten);

	void _set_blocking_mode();

	CSmartSocket m_oSmartSocket;
	CWSAEvent m_oWSAEvent;
	bool	  m_bWaitingRead;
};

#else
#error __FILE__ already included
#endif
