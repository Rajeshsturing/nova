/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Internal debugger and tracing system support
*/

#include "StdAfx.h"
#include "navo debugger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///global object supporting debug and tracing functionality

CDebugOptions	_g_DebugOptions;
CDebugger		_g_Debugger;

CDebugOptions::CDebugOptions() :
	m_bAutoCalls(true),
	m_bExceptions(false),
	m_bEventsNoGetData(false),
	m_bEventsGetData(false)
{
}


CDebugOptions & GetDebugOptions()
{
	return _g_DebugOptions;
}

CDebugger & GetDebugger()
{
	return _g_Debugger;
}

class CDebuggerImpl : public CCmdTargetInterface
{
	//{{AFX_MSG(CDebuggerImpl)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CDebuggerImpl)
	afx_msg LPDISPATCH GetObjectAUTO(LPCTSTR lpObjectName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
public:

	CDebuggerImpl();
	~CDebuggerImpl();
	void StoreMsg(LPCTSTR lpMsg);
	void IncDecIndent(long nByCount)
	{
		m_nIndent += nByCount;
		if(m_nIndent < 0)
		{
			m_nIndent = 0;
		}
	}
	long GetIndent() const
	{
		return m_nIndent;
	}
	void AddManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown);
	void RemoveManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown);
private:
	void __InitSink();

	struct CManageables
	{
		CManageables() :
			m_poObjectUnknown(NULL)
		{
		}
		CManageables(const CManageables & roManageables) :
			m_oObjectNameString(roManageables.m_oObjectNameString),
			m_poObjectUnknown(roManageables.m_poObjectUnknown)
		{
		}
		CString m_oObjectNameString;
		IUnknown * m_poObjectUnknown;
	};
	
	CArray<CManageables,CManageables &> m_oManageableObjectArray;

	_DebugMainSink	m_oDebugMainSink;
	long	m_nIndent;
	SCP<IStream>	m_poLogStreamSP;
};

/////////////////////////////////////////////////////////////////////////////////////
//			CDebugger - published class
/////////////////////////////////////////////////////////////////////////////////////

CDebugger::CDebugger() :
	m_poImplementation(new CDebuggerImpl())
{

}

CDebugger::~CDebugger()
{
	delete m_poImplementation;
}

void CDebugger::StoreMsg(LPCTSTR lpMsgOrFormat,...)
{
	ASSERT(m_poImplementation);

	va_list argList;
	va_start(argList, lpMsgOrFormat);
	CString oMsgString;
	oMsgString.FormatV(lpMsgOrFormat,argList);
	va_end(argList);
	if(m_poImplementation->GetIndent() > 0)
	{
		CString oString(' ',4*m_poImplementation->GetIndent());
		oMsgString = oString + oMsgString;
	}
	m_poImplementation->StoreMsg(oMsgString);
}

void CDebugger::IncDecIndent(long nByCount)
{
	ASSERT(m_poImplementation);
	m_poImplementation->IncDecIndent(nByCount);
}

void CDebugger::AddManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown)
{
	ASSERT(m_poImplementation);
	m_poImplementation->AddManageableObject(lpObjectName,poObjectUnknown);
}

void CDebugger::RemoveManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown)
{
	ASSERT(m_poImplementation);
	m_poImplementation->RemoveManageableObject(lpObjectName,poObjectUnknown);
}

/////////////////////////////////////////////////////////////////////////////////////
//			CDebuggerImpl - implementation class
/////////////////////////////////////////////////////////////////////////////////////
CDebuggerImpl::CDebuggerImpl() :
	m_nIndent(0)
{
	EnableAutomation();

#ifdef _DEBUG
	NavoCreateDirectoryTree("C:\\NAVO2001\\EXE\\DEBUG\\");
	CString oFileNameString;
	oFileNameString.Format("C:\\NAVO2001\\EXE\\DEBUG\\debugger_%d.txt",::GetCurrentProcessId());
	
	m_poLogStreamSP = CreateFileStream_Write(oFileNameString);
#endif

}

DWORD _g_FirstDebuggingThreadId = 0;

CDebuggerImpl::~CDebuggerImpl()
{
	if(_g_FirstDebuggingThreadId == ::GetCurrentThreadId())
	{
		m_oDebugMainSink.ReleaseDispatch();
	}
}


void CDebuggerImpl::__InitSink()
{
#ifdef _NAVODOTNET
	//to_do: uruchomic
	return;
#endif
	if(m_oDebugMainSink.m_lpDispatch == NULL)
	{
		_g_FirstDebuggingThreadId =  ::GetCurrentThreadId();
		m_oDebugMainSink.CreateDispatch(_T("NAVODebug.DebugMainSink"));
		m_oDebugMainSink.m_bAutoRelease = FALSE;
		CSmartOleVariant oSOV(GetDispatchSP());
		m_oDebugMainSink.registersink(&oSOV.GetVariantRef());
	}
}

void CDebuggerImpl::StoreMsg(LPCTSTR lpMsg)
{
	CString oString(lpMsg);
	CString strLeft500 = oString.Left(500);
	strLeft500.Replace("%","%%");
	TRACE(strLeft500);
	
	__InitSink();
	if(_g_FirstDebuggingThreadId == ::GetCurrentThreadId())
	{
#ifdef _NAVODOTNET
	//to_do: uruchomic
	return;
#endif
		m_oDebugMainSink.message(CSmartOleVariant(oString).Detach());
	}

#ifdef _DEBUG
	CStreamHolder oSH(m_poLogStreamSP);
	oSH.WriteString(lpMsg);
#endif

}

void CDebuggerImpl::AddManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown)
{
	CManageables oManageable;
	oManageable.m_oObjectNameString = lpObjectName;
	oManageable.m_poObjectUnknown = poObjectUnknown;
	m_oManageableObjectArray.Add(oManageable);
}

void CDebuggerImpl::RemoveManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown)
{
	for(long iter = 0; iter <= m_oManageableObjectArray.GetUpperBound(); iter++)
	{
		if(_tcscmp(lpObjectName,m_oManageableObjectArray[iter].m_oObjectNameString) == 0)
		{
			m_oManageableObjectArray.RemoveAt(iter);
			return;
		}
	}
}

//{{AFX_MSG_MAP(CDebuggerImpl)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CDebuggerImpl, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CDebuggerImpl)
	DISP_FUNCTION(CDebuggerImpl, "getobject", GetObjectAUTO, VT_DISPATCH, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH CDebuggerImpl::GetObjectAUTO(LPCTSTR lpObjectName) 
{
	ALL_TRY
	{
		for(long iter = 0; iter <= m_oManageableObjectArray.GetUpperBound(); iter++)
		{
			if(_tcscmp(lpObjectName,m_oManageableObjectArray[iter].m_oObjectNameString) == 0)
			{
				SCP<IDispatch> poDispatchSP;
				poDispatchSP.QueryInterface(m_oManageableObjectArray[iter].m_poObjectUnknown);
				return poDispatchSP.Detach();
			}
		}
		return NULL;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
