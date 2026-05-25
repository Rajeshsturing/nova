/*
	NAVO Enterprise 2001

	CSocketStream
		
	Obiekt implementuj¹cy IStream na socketach

*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\socketstream.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------------------
//	IStream interface
//------------------------------------------------------------------------------------

STDMETHODIMP CSocketStream::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		return pThis->__Read(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	Seek(LARGE_INTEGER liOffset, unsigned long /*lOrigin*/,ULARGE_INTEGER * pliNewPointer)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		if(liOffset.QuadPart == 0)
		{
			if(pliNewPointer)
			{
				pliNewPointer->QuadPart = 0;
			}
			return S_OK;
		}
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CSocketStream::XStream::
	Write(const void * pData, unsigned long lLength, unsigned long * plBytesWritten)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		return pThis->__Write(pData,lLength,plBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	Revert()
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CSocketStream::XStream::
	Stat(STATSTG *, unsigned long)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CSocketStream::XStream::
	Clone(IStream **)
{
	METHOD_PROLOGUE(CSocketStream, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

//------------------------------------------------------------------------------------
//	implementation
//------------------------------------------------------------------------------------

//{{AFX_MSG_MAP(CSocketStream)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CSocketStream, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CSocketStream)
	DISP_FUNCTION(CSocketStream, "open", OpenAUTO, VT_EMPTY, VTS_BSTR VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {90B41DDF-7098-4E5B-978A-4C05220726DF}
static const IID IID_ISocketStream =
{ 0x90b41ddf, 0x7098, 0x4e5b, { 0x97, 0x8a, 0x4c, 0x5, 0x22, 0x7, 0x26, 0xdf } };


BEGIN_INTERFACE_MAP(CSocketStream, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CSocketStream, IID_IStream, Stream)
	INTERFACE_PART(CSocketStream, IID_ISocketStream, Dispatch)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CSocketStream, Stream)

IMPLEMENT_DYNCREATE(CSocketStream, CCmdTargetInterface)
// {188cb178-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CSocketStream, "navoinet.socket",0x188cb178,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

CSocketStream::CSocketStream(LPCTSTR lpServer,long nPort,bool bWaitingRead) 
{
	EnableAutomation();
	AfxOleLockApp();
	
	_init(lpServer,nPort,bWaitingRead);
}

CSocketStream::CSocketStream() :
	m_bWaitingRead(false)
{
	EnableAutomation();
	AfxOleLockApp();
}

CSocketStream::~CSocketStream()
{
	AfxOleUnlockApp();
}

void CSocketStream::_init(LPCTSTR lpServer,long nPort,bool bWaitingRead)
{
	m_oSmartSocket.Open();
	m_oSmartSocket.Connect(lpServer,(u_short) nPort);
	m_bWaitingRead = bWaitingRead;
	if(!m_bWaitingRead)
	{
		//change mode to non-blocking (default is blocking)
		m_oWSAEvent.Create();
		int nResult = ::WSAEventSelect(m_oSmartSocket.GetHandle(),m_oWSAEvent.GetHandle(),FD_READ | FD_WRITE | FD_CLOSE);
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
	}
}

bool CSocketStream::_read_wait(DWORD dwTime)
{
	while(true)
	{
		bool bWaitOK = (WSA_WAIT_EVENT_0 == m_oWSAEvent.WaitForSingleObject(dwTime));
		if(!bWaitOK)
		{
			return false;	//not event -> return fail
		}
		//our event
		WSANETWORKEVENTS wsaNetworkEvents;
		m_oWSAEvent.EnumNetworkEvents(m_oSmartSocket.GetHandle(),&wsaNetworkEvents);
		if(wsaNetworkEvents.lNetworkEvents & FD_READ)
		{
			//exactly read and no error
			if(wsaNetworkEvents.iErrorCode[FD_READ_BIT] == 0)
			{
				return true;			
			}
			//to_do:
			ASSERT(false);	//error occured
		}
		//continue wait
		/*
		to_do: maybe not necessary
		int nResult = ::WSAEventSelect(m_oSmartSocket.GetHandle(),m_oWSAEvent.GetHandle(),FD_READ | FD_WRITE | FD_CLOSE);
		if(nResult != 0)
		{
			ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
		}
		*/
	}
}

void CSocketStream::_set_blocking_mode()
{
	int nResult = ::WSAEventSelect(m_oSmartSocket.GetHandle(),m_oWSAEvent.GetHandle(),0);
	if(nResult != 0)
	{
		ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
	}
	DWORD dwZero = 0;
	DWORD dwOutLen = 0;
	nResult = ::WSAIoctl(m_oSmartSocket.GetHandle(),FIONBIO,(LPVOID)&dwZero,sizeof(dwZero),(LPVOID)&dwZero,sizeof(dwZero),&dwOutLen,NULL,NULL);
	if(nResult != 0)
	{
		ThrowNavoException1(ERCO_SOCKET_WSAERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)CSmartSocket::WSAGetLastErrorToString());
	}
}

HRESULT CSocketStream::__Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	long nBytesRead = 0;
	if(m_bWaitingRead)
	{
		//restore blocking mode
		_set_blocking_mode();

		nBytesRead = m_oSmartSocket.Read((LPTSTR) pData,(long)lLength);
	}
	else
	{
		nBytesRead = m_oSmartSocket.NoWaitRead((LPTSTR) pData,(long)lLength);
	}
	if(plBytesRead)
	{
		*plBytesRead = (unsigned long) nBytesRead;
	}
	return S_OK;
}

HRESULT CSocketStream::__Write(const void *pData, unsigned long lLength, unsigned long *plBytesWritten)
{
	long nBytesWritten = m_oSmartSocket.Write((LPCTSTR) pData,(long)lLength);
	if(plBytesWritten)
	{
		*plBytesWritten = nBytesWritten;
	}
	return S_OK;
}

SCP<IStream> CSocketStream::Get(LPCTSTR lpServer,long nPort,bool bWaitingRead)
{
	return NewSCP(new CSocketStream(lpServer,nPort,bWaitingRead))->GetStreamSP();
}

SCP<IStream> OpenSocketStream(LPCTSTR lpServer,long nPort,bool bWaitingRead)
{
	return CSocketStream::Get(lpServer,nPort,bWaitingRead);
}


void CSocketStream::OpenAUTO(LPCTSTR lpServer,long nPort)
{
	ALL_TRY
	{
		_init(lpServer,nPort,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
