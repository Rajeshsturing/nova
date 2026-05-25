/*
	NAVO Enterprise 2008
	Copyright (c) 2002 NAVO

	NAVOPERIF object supports peripherials (COM etc.)
*/

#if !defined(AFX_COMAUTOOBJECT_H__83C31720_C669_4EB6_AD46_1D63B4EE9524__INCLUDED_)
#define AFX_COMAUTOOBJECT_H__83C31720_C669_4EB6_AD46_1D63B4EE9524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern CNavoLog g_oLog;

class CComAutoObject : public CCmdTarget
{
	DECLARE_DYNCREATE(CComAutoObject)
	CComAutoObject();
public:
	//{{AFX_VIRTUAL(CComAutoObject)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL
protected:
	virtual ~CComAutoObject();
	//{{AFX_MSG(CComAutoObject)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CComAutoObject)
	//{{AFX_DISPATCH(CComAutoObject)
	afx_msg BSTR GetPortAUTO();
	afx_msg void SetPortAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetSpeedAUTO();
	afx_msg void SetSpeedAUTO(long nNewValue);
	afx_msg long GetParityAUTO();
	afx_msg void SetParityAUTO(long nNewValue);
	afx_msg long GetBitsAUTO();
	afx_msg void SetBitsAUTO(long nNewValue);
	afx_msg long GetStopBitsAUTO();
	afx_msg void SetStopBitsAUTO(long nNewValue);
	afx_msg LPDISPATCH GetSinkAUTO();
	afx_msg void SetSinkAUTO(LPDISPATCH newValue);
	afx_msg void WriteAUTO(long nByte);
	afx_msg void WriteStrAUTO(LPCTSTR lpStr);
	afx_msg void FlushAUTO();
	afx_msg long ReadAUTO();
	afx_msg void FillAUTO(long nCount);
	afx_msg long GetErrorAUTO();
	afx_msg void StartAUTO();
	afx_msg void CloseAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	void _flush_write_queue();
	void _fill_read_queue(long nBytes);
	
	void _append_write_queue(BYTE ucByte)
	{
		if(g_oLog.IsHandleValid())
		{
			g_oLog << "wr=" + Long2String((int) ucByte);
		}
		m_oWriteQueue.Add(ucByte);
	}
	bool _retrieve_read_queue(BYTE & rucByte)
	{
		if(m_oReadQueue.GetSize() == 0)
		{
			return false;
		}
		rucByte = m_oReadQueue[0];
		m_oReadQueue.RemoveAt(0);
		
		if(g_oLog.IsHandleValid())
		{
			g_oLog << "rd=" + Long2String((int) rucByte);
		}
		
		return true;
	}
	long _get_read_queue_size() const
	{
		return m_oReadQueue.GetSize();
	}
	void _open_port();
	void _close_port();
	void _start_wait_thread();

	void _on_inputdata_ready(long nBytes);
	
	CArray<BYTE,BYTE> m_oWriteQueue;
	CArray<BYTE,BYTE> m_oReadQueue;

	SCP<IDispatch>	m_poNotificationSinkSP;
	SCP<IStream>	m_poMarshalledNotificationSinkSP;

	HANDLE		m_hComPort;

	//communication settings
	CString		m_oPortString;
	long		m_nSpeed;
	long		m_nParity;
	long		m_nBitsPerByte;
	long		m_nStopBits;

	bool		m_bSignalExitThread;
	HANDLE		m_hWaitThread;
	OVERLAPPED  m_overlapped;
	CEvent		m_oCOMEvent;
	CEvent		m_oExitThreadEvent;

	errorcode	m_eLastError;

	friend UINT AFX_CDECL com_auto_object_waitthread(LPVOID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMAUTOOBJECT_H__83C31720_C669_4EB6_AD46_1D63B4EE9524__INCLUDED_)
