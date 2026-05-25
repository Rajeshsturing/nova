/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CSmartSocket

	small but smart socket wrapper
*/

#ifndef _SMARTSOCKET2_H_
#define _SMARTSOCKET2_H_

void _navo_init_sockets();

class CSmartSocket
{
public:
	CSmartSocket(SOCKET hSocket = INVALID_SOCKET) :
		m_hSocket(hSocket)
	{
	}
	CSmartSocket(CSmartSocket & roSmartSocket) :
		m_hSocket(roSmartSocket.m_hSocket)
	{
		roSmartSocket.m_hSocket = INVALID_SOCKET;
	}
	~CSmartSocket()
	{
		if(m_hSocket != INVALID_SOCKET)
		{
			::closesocket(GetHandle());
		}
	}
	virtual void operator = (CSmartSocket & roSmartSocket)
	{
		m_hSocket = roSmartSocket.m_hSocket;
		roSmartSocket.m_hSocket = INVALID_SOCKET;
	}
	void Open()
	{
		_navo_init_sockets();
		m_hSocket = ::socket(AF_INET,SOCK_STREAM,0);
		if(GetHandle() == INVALID_SOCKET)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
		BOOL bNoDelay = TRUE;
		VERIFY(SOCKET_ERROR !=::setsockopt(m_hSocket,IPPROTO_TCP,TCP_NODELAY,(LPCSTR)&bNoDelay,sizeof(BOOL)));
		VERIFY(SOCKET_ERROR !=::setsockopt(m_hSocket,SOL_SOCKET,SO_KEEPALIVE,(LPCSTR)&bNoDelay,sizeof(BOOL)));
	}
	void BindToPort(u_short nPort)
	{
		SOCKADDR_IN sockAddr;
		memset(&sockAddr,0,sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		sockAddr.sin_port = htons(nPort);
		int nResult = ::bind(GetHandle(),reinterpret_cast<sockaddr *>(&sockAddr),sizeof(sockAddr));
		ASSERT(INVALID_SOCKET != 0);	//nic siê nie zmieni³o w deklaracjach
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	}
	void Connect(LPCTSTR lpServer,u_short nPort)
	{

		SOCKADDR_IN sockAddr;
		memset(&sockAddr,0,sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(nPort);
		sockAddr.sin_addr.s_addr = inet_addr(lpServer);
		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			hostent * pHost = gethostbyname(lpServer);
			if (pHost == NULL)
			{
				ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,CString("gethostbyname failed for ")+ CString(lpServer));
			}
			memcpy(&sockAddr.sin_addr, pHost->h_addr_list[0],pHost->h_length);
		}
		int nResult = ::connect(GetHandle(),reinterpret_cast<sockaddr *>(&sockAddr),sizeof(sockAddr));
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	}
	void Listen()
	{
		int nResult = ::listen(GetHandle(),5);
		ASSERT(INVALID_SOCKET != 0);	//nic siê nie zmieni³o w deklaracjach
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	}
	CSmartSocket Accept()
	{
		return CSmartSocket(::accept(GetHandle(),NULL,NULL));
	}
	long NoWaitRead(char * pBuffer,long nBufferLen)
	{
		long nResult = ::recv(GetHandle(),pBuffer,nBufferLen,0);
		if(nResult == SOCKET_ERROR)
		{
			long nLastError = ::WSAGetLastError();
			if(nLastError == WSAEWOULDBLOCK)
			{
				return 0;
			}
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)Long2String(nLastError));
		}
		return nResult;
	}
		
	long Read(char * pBuffer,long nBufferLen)
	{
		long nResult = ::recv(GetHandle(),pBuffer,nBufferLen,0);
		if(nResult == SOCKET_ERROR)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
		return nResult;
	}
	long Write(const char * pBuffer,long nBufferLen)
	{
		long nResult = ::send(GetHandle(),pBuffer,nBufferLen,0);
		if(nResult == SOCKET_ERROR)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
		return nResult;
	}
	const SOCKET & GetHandle() const
	{
		ASSERT(m_hSocket != INVALID_SOCKET);
		return m_hSocket;
	}
	SOCKET & GetHandle()
	{
		ASSERT(m_hSocket != INVALID_SOCKET);
		return m_hSocket;
	}
	static CString WSAGetLastErrorToString();
private:
	SOCKET	m_hSocket;
};

class CWSAEvent
{
public:
	CWSAEvent(): 
		m_hEvent(WSA_INVALID_EVENT)
	{
	}
	void Create()
	{
		ASSERT(m_hEvent == WSA_INVALID_EVENT);
		m_hEvent = ::WSACreateEvent();
		if(m_hEvent == WSA_INVALID_EVENT)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	};
	void Close()
	{
		if (m_hEvent != WSA_INVALID_EVENT)
		{
			::WSACloseEvent(GetHandle());
			m_hEvent = WSA_INVALID_EVENT;
		}
	}
	~CWSAEvent()
	{
		Close();
	};
	bool IsSignalled(unsigned long ulTime = 0) const
	{
		return ::WSAWaitForMultipleEvents(1, &GetHandle(), FALSE, ulTime, FALSE) == WSA_WAIT_EVENT_0;
	};
	unsigned long WaitForSingleObject(unsigned long ulTime = 0) const
	{
		return ::WSAWaitForMultipleEvents(1, &GetHandle(), FALSE, ulTime, FALSE);
	};
	void EnumNetworkEvents(SOCKET hSocket, LPWSANETWORKEVENTS pNetworkEvents) const 
	{
		int nResult = ::WSAEnumNetworkEvents(hSocket, GetHandle(), pNetworkEvents);
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	};
	WSAEVENT & GetHandle() const
	{
		ASSERT(m_hEvent != WSA_INVALID_EVENT);
		return (WSAEVENT &)m_hEvent;
	};

private:

	WSAEVENT m_hEvent;
};


class CStartupCleanupHolder : public CInterface__
{
public:
	CStartupCleanupHolder(WORD hiVersion,WORD loVersion);
	~CStartupCleanupHolder();
	long Result() const
	{
		return m_nResult;
	}
private:
	long m_nResult;
	bool m_bClean;
};

#else
	#error __FILE__ already included
#endif
