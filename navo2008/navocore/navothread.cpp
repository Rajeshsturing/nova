/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNavoThread
*/

#include "stdafx.h"
#include "..\include\navothread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNavoThread::CNavoThread(CNavoOleInitHolder::EType eType) :
	m_eOleInitType(eType),
	CWinThread(NavoThreadFunction, this)
{
	if (!CreateThread(CREATE_SUSPENDED, 0, NULL))
	{
		ThrowNavoException1(ERCO_CREATING_THREAD_FAILED, IDPAGE_NOTAVAILABLE,
			GetLastError_To_String(::GetLastError()));
	};
}

unsigned int CNavoThread::NavoThreadFunction(void *pThis)
{
	CNavoThread * pNavoThread = (CNavoThread *)pThis;
	ASSERT(pNavoThread);
	ALL_TRY
	{
		CNavoOleInitHolder oNavoOleInitHolder(pNavoThread->m_eOleInitType);
		if(!oNavoOleInitHolder.IsOK())
		{
			ASSERT(false);
			pNavoThread->GetErrorStorage() += 
				CNavoErrorInfo(ERCO_NAVOTHREAD_OLE_INIT_FAILED,IDPAGE_NOTAVAILABLE,"");
			return 1;
		}
		
		if(CWinVersion().GetVersion() >= CWinVersion::WinNT)
		{
			VERIFY(::SetThreadLocale(GetWorkingLCID()));
		}

		return pNavoThread->Run();
	}
	TOP_ALL_CATCH_(pNavoThread->GetErrorStorage())
	return 0;
}


