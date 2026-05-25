// ComAutoObject.cpp : implementation file
//

#include "stdafx.h"
#include "navoperif.h"
#include "ComAutoObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CNavoLog g_oLog;

/////////////////////////////////////////////////////////////////////////////
// CComAutoObject

IMPLEMENT_DYNCREATE(CComAutoObject, CCmdTarget)

CComAutoObject::CComAutoObject():
	m_nSpeed(9600),
	m_nParity(0),
	m_nBitsPerByte(8),
	m_nStopBits(0),
	m_hComPort(NULL),
	m_hWaitThread(NULL),
	m_eLastError(ERCO_OK)
{
	m_oPortString = _T("COM1");

	EnableAutomation();
	AfxOleLockApp();
	m_overlapped.hEvent = m_oCOMEvent.m_hObject;

//	g_oLog.Open("C:\\navoperif_log.txt");

}

CComAutoObject::~CComAutoObject()
{
	_close_port();
	AfxOleUnlockApp();
}

void CComAutoObject::OnFinalRelease()
{
	_close_port();
	CCmdTarget::OnFinalRelease();
}

void CComAutoObject::_close_port()
{
	if(m_hComPort == NULL)
	{
		return;
	}
	m_poNotificationSinkSP = 0;
	m_oExitThreadEvent.SetEvent();
	VERIFY(::CloseHandle(m_hComPort));
	m_hComPort = NULL;
	if(m_hWaitThread != NULL)
	{
		::WaitForSingleObject(m_hWaitThread,INFINITE);
	}	

	if(g_oLog.IsHandleValid())
	{
		g_oLog << "port closed";
	}
}

void CComAutoObject::_open_port()
{
	if(m_hComPort != NULL)
	{
		return;
	}
	m_hComPort = ::CreateFile(m_oPortString,GENERIC_READ|GENERIC_WRITE,0,
		NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);
	if(m_hComPort == INVALID_HANDLE_VALUE)
	{
		m_eLastError = ERCO_PERIF_COM_CANT_OPEN_PORT;
		DWORD dwLastError = ::GetLastError();
		ThrowNavoException2(ERCO_PERIF_COM_CANT_OPEN_PORT, IDPAGE_NOTAVAILABLE,
			m_oPortString,SCODE_To_String(dwLastError));
	}
	DCB oDCB;
	VERIFY(::GetCommState(m_hComPort,&oDCB));
	oDCB.BaudRate = DWORD(m_nSpeed);
	oDCB.ByteSize = BYTE(m_nBitsPerByte);
	oDCB.Parity   = BYTE(m_nParity);	/* 0-4=None,Odd,Even,Mark,Space    */
	oDCB.StopBits = BYTE(m_nStopBits);	/* 0,1,2 = 1, 1.5, 2               */
	oDCB.fAbortOnError = TRUE;
	if(!::SetCommState(m_hComPort,&oDCB))
	{
		DWORD dwLastError = ::GetLastError();
		m_eLastError = ERCO_PERIF_COM_CANT_INIT_PORT;
		ThrowNavoException2(ERCO_PERIF_COM_CANT_INIT_PORT, IDPAGE_NOTAVAILABLE,
			m_oPortString,SCODE_To_String(dwLastError));
	}
	COMMTIMEOUTS commtimeouts;
	memset(&commtimeouts,0,sizeof(commtimeouts));
	commtimeouts.ReadIntervalTimeout = MAXDWORD;	
	commtimeouts.ReadTotalTimeoutMultiplier= MAXDWORD;
	commtimeouts.ReadTotalTimeoutConstant = 1000;	//1 s

	if(!::SetCommTimeouts(m_hComPort,&commtimeouts))
	{
		m_eLastError = ERCO_PERIF_COM_CANT_SET_TIMEOUTS;
		DWORD dwLastError = ::GetLastError();
		ThrowNavoException2(ERCO_PERIF_COM_CANT_SET_TIMEOUTS, IDPAGE_NOTAVAILABLE,
			m_oPortString,SCODE_To_String(dwLastError));
	};
	
	if(g_oLog.IsHandleValid())
	{
		g_oLog << "port " + m_oPortString + " opened";
	}

//	VERIFY(::EscapeCommFunction(m_hComPort, SETDTR));
}

void CComAutoObject::_flush_write_queue()
{
	_open_port();
	ASSERT(m_hComPort != NULL);
	if(m_oWriteQueue.GetSize() == 0)
	{
		return;
	}
	DWORD dwBytesWritten = 0;
	m_overlapped.Offset = 0;
	m_overlapped.OffsetHigh = 0;
	
	if(!::WriteFile(m_hComPort,m_oWriteQueue.GetData(),DWORD(m_oWriteQueue.GetSize()),&dwBytesWritten,&m_overlapped))
	{
		DWORD dwLastError = ::GetLastError();
		if(ERROR_IO_PENDING != dwLastError && ERROR_SOME_NOT_MAPPED!= dwLastError)
		{
			m_eLastError = ERCO_PERIF_COM_WRITE_FAILED;
			ThrowNavoException1(ERCO_PERIF_COM_WRITE_FAILED, IDPAGE_NOTAVAILABLE,SCODE_To_String(dwLastError));
		}
		DWORD dwDummy;
		while(!::GetOverlappedResult(m_hComPort,&m_overlapped,&dwDummy,TRUE))
		{
			DWORD dwLastError = ::GetLastError();
		    if(dwLastError != ERROR_IO_INCOMPLETE && ERROR_SOME_NOT_MAPPED!= dwLastError)
			{
				m_eLastError = ERCO_PERIF_COM_WRITE_FAILED2;
				ThrowNavoException1(ERCO_PERIF_COM_WRITE_FAILED2, IDPAGE_NOTAVAILABLE,SCODE_To_String(dwLastError));
			}
		}
	}
	m_oWriteQueue.RemoveAll();
}

void CComAutoObject::_fill_read_queue(long nBytes)
{
	ASSERT(nBytes > 0);
	long nOldSize = _get_read_queue_size();
	m_oReadQueue.SetSize(nOldSize + nBytes);
	_open_port();

	//read 
	ASSERT(m_hComPort != NULL);
	DWORD dwBytesRead = 0;
	m_overlapped.Offset = 0;
	m_overlapped.OffsetHigh = 0;
	if(!::ReadFile(m_hComPort,m_oReadQueue.GetData() + nOldSize,DWORD(nBytes),&dwBytesRead,&m_overlapped))
	{
		DWORD dwLastError = ::GetLastError();
		if(ERROR_IO_PENDING != dwLastError && ERROR_SOME_NOT_MAPPED!= dwLastError)
		{
			m_eLastError = ERCO_PERIF_COM_READ_FAILED;
			ThrowNavoException1(ERCO_PERIF_COM_READ_FAILED, IDPAGE_NOTAVAILABLE,SCODE_To_String(dwLastError));
		}
		DWORD dwDummy;
		while(!::GetOverlappedResult(m_hComPort,&m_overlapped,&dwDummy,TRUE))
		{
			DWORD dwLastError = ::GetLastError();
		    if(dwLastError != ERROR_IO_INCOMPLETE && ERROR_SOME_NOT_MAPPED!= dwLastError)
			{
				m_eLastError = ERCO_PERIF_COM_READ_FAILED2;
				ThrowNavoException1(ERCO_PERIF_COM_READ_FAILED2, IDPAGE_NOTAVAILABLE,SCODE_To_String(dwLastError));
			}
		}
	}
}

UINT AFX_CDECL com_auto_object_waitthread(LPVOID lpThreadParameter)
{
	CNavoOleInitHolder oNavoOleInitHolder(CNavoOleInitHolder::MULTITHREADED);
	ASSERT(lpThreadParameter);
	CComAutoObject * poComAutoObject = reinterpret_cast<CComAutoObject *>(lpThreadParameter);
	poComAutoObject->m_poNotificationSinkSP.UnMarshal(poComAutoObject->m_poMarshalledNotificationSinkSP);
	poComAutoObject->m_poMarshalledNotificationSinkSP = 0;
	if(!::SetCommMask(poComAutoObject->m_hComPort,EV_RXCHAR))
	{
		return 1;
	}
	while(true)
	{
		DWORD dwEventMask = 0;
		if(!::WaitCommEvent(poComAutoObject->m_hComPort,&dwEventMask,&poComAutoObject->m_overlapped))
		{
			DWORD dwLastError = ::GetLastError();
			if(ERROR_IO_PENDING != dwLastError)
			{
				return 2;
			}
			HANDLE aHandles[] =
			{
				poComAutoObject->m_oExitThreadEvent.m_hObject,
				poComAutoObject->m_oCOMEvent.m_hObject
			};
			DWORD dwRes = ::WaitForMultipleObjects(2,aHandles,FALSE,INFINITE);
			switch(dwRes)
			{
			case WAIT_OBJECT_0:
				poComAutoObject->m_poNotificationSinkSP = 0;
				return 0;	//exit thread event
			case WAIT_OBJECT_0+1:
			break;			//data event
			default:
				return 3;	//error event
			}
		}
		if((dwEventMask & EV_RXCHAR) == EV_RXCHAR)
		{
			//notify - some data ready
			COMSTAT comstat;
			DWORD dwErrors;
			if(!::ClearCommError(poComAutoObject->m_hComPort,&dwErrors,&comstat))
			{
				return 3;
			}
			long nBytesReady = long(comstat.cbInQue);
			if(nBytesReady != 0)
			{
				poComAutoObject->_on_inputdata_ready(nBytesReady);
			}
		}
	}
	return 0;
}

void CComAutoObject::_start_wait_thread()
{
	if(m_hWaitThread == NULL)
	{
		if(m_poMarshalledNotificationSinkSP.PointsObject())

		{
			CWinThread * poThread = AfxBeginThread(com_auto_object_waitthread,(LPVOID)this);
			if(poThread != NULL)
			{
				m_hWaitThread = poThread->m_hThread;
			}
		}
	}
}

//out of main thread call
void CComAutoObject::_on_inputdata_ready(long nBytes)
{
	if(m_poNotificationSinkSP.PointsObject())
	{
		DISPID dispid = DispatchGetIdOfName(m_poNotificationSinkSP,L"dataready");
		EXCEPINFO ei;
		CSmartOleVariant oDataLenSOV(nBytes);
		HRESULT hResult = DispatchInvoke(m_poNotificationSinkSP, dispid,&oDataLenSOV,1,NULL,&ei);
		if (hResult != S_OK)
		{
			m_eLastError = ERCO_PERIF_COM_INVOKE_FAILED;
			ThrowNavoException1(ERCO_PERIF_COM_INVOKE_FAILED, IDPAGE_NOTAVAILABLE,SCODE_To_String(hResult));
		}
	}
}

BEGIN_MESSAGE_MAP(CComAutoObject, CCmdTarget)
	//{{AFX_MSG_MAP(CComAutoObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComAutoObject, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CComAutoObject)
	DISP_PROPERTY_EX(CComAutoObject, "port", GetPortAUTO, SetPortAUTO, VT_BSTR)
	DISP_PROPERTY_EX(CComAutoObject, "speed", GetSpeedAUTO, SetSpeedAUTO, VT_I4)
	DISP_PROPERTY_EX(CComAutoObject, "parity", GetParityAUTO, SetParityAUTO, VT_I4)
	DISP_PROPERTY_EX(CComAutoObject, "bits", GetBitsAUTO, SetBitsAUTO, VT_I4)
	DISP_PROPERTY_EX(CComAutoObject, "stopbits", GetStopBitsAUTO, SetStopBitsAUTO, VT_I4)
	DISP_PROPERTY_EX(CComAutoObject, "sink", GetSinkAUTO, SetSinkAUTO, VT_DISPATCH)
	DISP_FUNCTION(CComAutoObject, "write", WriteAUTO, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CComAutoObject, "writestr", WriteStrAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CComAutoObject, "flush", FlushAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CComAutoObject, "read", ReadAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CComAutoObject, "fill", FillAUTO, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CComAutoObject, "error", GetErrorAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CComAutoObject, "start", StartAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CComAutoObject, "close", CloseAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IComAutoObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {75121426-AF72-432B-8CC8-B530F6BB2D37}
static const IID IID_IComAutoObject =
{ 0x75121426, 0xaf72, 0x432b, { 0x8c, 0xc8, 0xb5, 0x30, 0xf6, 0xbb, 0x2d, 0x37 } };

BEGIN_INTERFACE_MAP(CComAutoObject, CCmdTarget)
	INTERFACE_PART(CComAutoObject, IID_IComAutoObject, Dispatch)
END_INTERFACE_MAP()

// {188cb17e-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CComAutoObject, "navoperif.comobject", 0x188cb17e,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CComAutoObject message handlers

BSTR CComAutoObject::GetPortAUTO() 
{
	return m_oPortString.AllocSysString();
}

void CComAutoObject::SetPortAUTO(LPCTSTR lpszNewValue) 
{
	m_oPortString = lpszNewValue;
}

long CComAutoObject::GetSpeedAUTO() 
{
	return m_nSpeed;
}

void CComAutoObject::SetSpeedAUTO(long nNewValue) 
{
	m_nSpeed = nNewValue;
}

long CComAutoObject::GetParityAUTO() 
{
	return m_nParity;
}

void CComAutoObject::SetParityAUTO(long nNewValue) 
{
	m_nParity = nNewValue;
}

long CComAutoObject::GetBitsAUTO() 
{
	return m_nBitsPerByte;
}

void CComAutoObject::SetBitsAUTO(long nNewValue) 
{
	m_nBitsPerByte = nNewValue;
}

long CComAutoObject::GetStopBitsAUTO() 
{
	return m_nStopBits;
}

void CComAutoObject::SetStopBitsAUTO(long nNewValue) 
{
	m_nStopBits = nNewValue;
}

void CComAutoObject::WriteAUTO(long nByte) 
{
	ALL_TRY
	{
		if(nByte > 255 || nByte < 0)
		{
			m_eLastError = ERCO_PERIF_COM_WRITE_INV_VALUE;
			ThrowNavoException1(ERCO_PERIF_COM_WRITE_INV_VALUE, IDPAGE_NOTAVAILABLE,nByte);
		}
		_append_write_queue(BYTE(nByte));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CComAutoObject::WriteStrAUTO(LPCTSTR lpString) 
{
	ALL_TRY
	{
		if(lpString == NULL)
		{
			m_eLastError = ERCO_PERIF_COM_WRITESTR_INV_PARAM;
			ThrowNavoException(ERCO_PERIF_COM_WRITESTR_INV_PARAM, IDPAGE_NOTAVAILABLE);
		}
		while(*lpString)
		{
			_append_write_queue(BYTE(*lpString));
			lpString++;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CComAutoObject::FlushAUTO() 
{
	ALL_TRY
	{
		_flush_write_queue();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CComAutoObject::ReadAUTO() 
{
	ALL_TRY
	{
		BYTE ucByte = '\0';
		if(!_retrieve_read_queue(ucByte))
		{
			_fill_read_queue(1);
			VERIFY(_retrieve_read_queue(ucByte));
		}
		return (long)(unsigned long)ucByte;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CComAutoObject::FillAUTO(long nCount) 
{
	ALL_TRY
	{
		long nAvailableBytes = _get_read_queue_size();
		if(nAvailableBytes < nCount)
		{
			_fill_read_queue(nCount - nAvailableBytes);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CComAutoObject::GetErrorAUTO() 
{
	return long(m_eLastError);
}

LPDISPATCH CComAutoObject::GetSinkAUTO() 
{
	return m_poNotificationSinkSP.Get();
}

void CComAutoObject::SetSinkAUTO(LPDISPATCH pSinkDisp) 
{
	ALL_TRY
	{
		if(pSinkDisp != NULL)
		{
			m_poNotificationSinkSP = NewSCP(pSinkDisp,true);
			m_poMarshalledNotificationSinkSP = m_poNotificationSinkSP.Marshal();
		}
		m_poNotificationSinkSP = 0;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CComAutoObject::StartAUTO() 
{
	ALL_TRY
	{
		_open_port();
		_start_wait_thread();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CComAutoObject::CloseAUTO() 
{
	ALL_TRY
	{
		_close_port();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
