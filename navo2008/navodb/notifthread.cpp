/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	notification manager
	notification thread
*/

/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	notification manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"		//generic error storage
#include "..\include\clientinfo.h"		//client info
#include "..\include\navoclassfactory.h"
#include "NotificationManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CNotificationManager::_start_working_threads()
{
	//create all threads
	for(long iter = 0; iter < _MAX_SENDING_THREADS; iter++)
	{
		CNotificationThread * poThread = new CNotificationThread(this);
		m_hSendingThreads[iter] = poThread->m_hThread;
	}
	for(long iter = 0; iter < _MAX_SENDING_THREADS; iter++)
	{
		::ResumeThread(m_hSendingThreads[iter]);
	}
}

CNotificationThread::CNotificationThread(CNotificationManager * poNotMan) :
	CNavoThread(CNavoOleInitHolder::MULTITHREADED),
	m_poNotMan(poNotMan)
{
	ASSERT(m_poNotMan);
	TRACE("THREAD %d,%d started\n",long((void*)this),long(m_hThread));
}

CNotificationThread::~CNotificationThread()
{
	TRACE("THREAD %d finished\n",long((void*)this));
}

int CNotificationThread::Run()
{
	ASSERT(m_poNotMan);

	HANDLE hEvents[2] = 
	{
		m_poNotMan->m_oExitEvent.m_hObject,
		m_poNotMan->m_oNewNotificationEvent.m_hObject
	};
	
	while(true)
	{
		DWORD dwWaitResult = ::WaitForMultipleObjects(2,hEvents,FALSE,INFINITE);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
			return 0;		//exit event
		}
		if(dwWaitResult == WAIT_OBJECT_0 + 1)	//something to do
		{
			SCP<CServerNotificationData> poSNDSP = m_poNotMan->_retrieve_from_queue();
			if(poSNDSP.PointsObject())
			{
				m_poNotMan->_call_destination(poSNDSP);
			}
			continue;
		}
		if(dwWaitResult == WAIT_FAILED)
		{
			TRACE("bad wait result %d, exiting\n",long(::GetLastError()));
			return -1;
		}
	}
}

