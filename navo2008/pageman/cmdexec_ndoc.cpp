/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		cndoc_commandexecutor
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "..\navopx\navopx.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navogal\ngal_iface.h"		//graphics
#include "cmdexec_ndoc.h"
#include "application_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const long GVAR_INTERNAL_COMMAND_NUMBER   = 20021106;
static const long GVAR_INTERNAL_COMMAND_WAITABLE = 20021118;

cndoc_commandexecutor::cndoc_commandexecutor(cndoc_application * poApplication) :
	m_poApplication(poApplication),
	m_oEventCommandProcessed(FALSE,FALSE),
	m_oEventGoingIdle(FALSE,TRUE),
	m_nCommandCounter(0),
	m_bQuitting(false)
{
	ASSERT(m_poApplication != NULL);
}

cndoc_commandexecutor::~cndoc_commandexecutor()
{
}

void cndoc_commandexecutor::_message_loop()
{
	//OS_API_CALL
	MSG msg;
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if(!_pre_translate_message(msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

void cndoc_commandexecutor::mark_quitting()
{
	m_bQuitting = true;
	//set events
	m_oEventExitLoop.SetEvent();
	m_oEventCommandProcessed.SetEvent();
	m_oEventGoingIdle.SetEvent();
}

void cndoc_commandexecutor::yield()
{
	//big loop
	_message_loop();
	while(true)
	{
		//if in quitting mode - return immediatelly
		if(m_bQuitting)
		{
			return;
		}

		DWORD dwWaitTime = _on_idle() ? 0 : INFINITE;

		
		if(m_poApplication->is_async_mode() && m_poApplication->is_notify_idle())
		{
	#ifdef _DEBUG
			::Sleep(0);		//see Q173260
	#endif
			TRACE("+GOING IDLE (%d)\n",::GetTickCount());
			m_oEventGoingIdle.SetEvent();
		}

		const DWORD nCountOfObjects = 2;
		HANDLE oWaitObjects[nCountOfObjects] = 
		{
			m_oEventExitLoop.m_hObject,
			m_oEventNewCmd.m_hObject
		};

		DWORD dwResult = ::MsgWaitForMultipleObjects(nCountOfObjects,
			oWaitObjects,FALSE,dwWaitTime,QS_ALLINPUT);
		
		if(dwResult == WAIT_OBJECT_0)					//event exit
		{
			return;
		}
		
		if(dwResult == WAIT_TIMEOUT)					//timeout
		{
			ASSERT(false); //INFITE reached ?  on_idle was true ?
		}

		if((dwResult == WAIT_OBJECT_0 + nCountOfObjects) ||		//msg
		   (dwResult == WAIT_OBJECT_0 + 1))						//event command
		{
			_message_loop();
			_on_new_command();

			//sprawdŸ czy jest zapalone 'wyjœcie'
			//poniewa¿ messages maj¹ wy¿szy priorytet,
			//eventy mog¹ byæ zapalone, ale w dwResult zg³aszany jest WAIT_OBJECT_0 + nCountOfObjects 
			//(message)

			if(::WaitForSingleObject(m_oEventExitLoop.m_hObject,0) == WAIT_OBJECT_0)
			{
				return;
			}
		}
	}
}

bool cndoc_commandexecutor::_on_idle()
{
	ASSERT(m_poApplication);
	return m_poApplication->on_idle();
}

//--------------------------------------------------------------
// command processing
//--------------------------------------------------------------
SCP<CHyperLinkInfo> cndoc_commandexecutor::_retrieve_posted_command()
{
	CSimpleLock oLock(m_oPostedCommandCS);
	if (m_oPostedCommandList.IsEmpty())
	{
		return SCP <CHyperLinkInfo> ();
	}
	return m_oPostedCommandList.RemoveHead();
}

void cndoc_commandexecutor::_on_new_command()
{
	for(SCP <CHyperLinkInfo> poHLISP = _retrieve_posted_command();
		poHLISP.PointsObject(); 
		poHLISP = _retrieve_posted_command())
	{
		_process_command(poHLISP);

		ASSERT(m_poApplication->is_async_mode());

		//notify,that command is processed

		if(poHLISP->PropertyExists(GVAR_INTERNAL_COMMAND_WAITABLE))
		{
			long nLastProcessedCommand = poHLISP->GetNumProp(GVAR_INTERNAL_COMMAND_NUMBER);
			{
				CSimpleLock oLock(m_oPostedCommandCS);
				m_oProcessedWaitableCommands.Add(nLastProcessedCommand);

				//oznacza to albo du¿e zagnie¿d¿enie komend
				//albo ktoœ nie odbiera
				//limit (10) mo¿e byæ dowolny, ale warto wiedzieæ
				ASSERT(m_oProcessedWaitableCommands.GetSize() < 10);
			}
#ifdef _DEBUG
			::Sleep(0);		//see Q173260
#endif
			m_oEventCommandProcessed.PulseEvent();
		}
	}
}

void CreateUserDocumentFromCommandLine(LPCTSTR lpCmdLine);

void cndoc_commandexecutor::_process_command(SCP <CHyperLinkInfo> & rpoHLISP)
{
	TRACE("PROCESSING %s\n",rpoHLISP->WriteToString());

	ASSERT(rpoHLISP.PointsObject());
	ASSERT(m_poApplication);

	//sprawdŸ poprawnoœæ komendy
	if(!rpoHLISP->PropertyExists(GVAR_CMD) && 
	   !rpoHLISP->PropertyExists(GVAR_FUNCTION) &&
	   !rpoHLISP->PropertyExists(GVAR_FUNCTIONHLI))
	{
#ifdef _DEVELOPER_EDITION_
		CString oDescriptionString;
		NavoFormatErrorMsg(oDescriptionString,ERCO_USERDOC_MISSING_GVAR_CMD,rpoHLISP->WriteToString());
		AfxMessageBox(oDescriptionString);
#endif
		return;	//just ignore this command
	}
	//jeœli otwarcie nowego dokumentu - wykonaj i wyjdŸ
	if(rpoHLISP->PropertyExists(GVAR_SPAWNNEWDOC))
	{
		if(rpoHLISP->GetNumProp(GVAR_SPAWNNEWDOC) != 0)
		{
			SCP<CHyperLinkInfo> poCopyHLISP = NewSCP(new CHyperLinkInfo(*rpoHLISP));
			poCopyHLISP->DeleteProp(GVAR_PAGE_IID);

			CString oString = poCopyHLISP->WriteToString();
			oString.Replace("\"","\'");
			CreateUserDocumentFromCommandLine(CString("-s \"") + oString + CString("\""));
		}
		return;
	}
	if(rpoHLISP->GetNumProp(GVAR_INTERNAL_COMMAND_NUMBER) == 0)
	{
		m_poApplication->_process_first_command(rpoHLISP);
	}
	else
	{
		m_poApplication->_process_command(rpoHLISP);
	}

	TRACE("PROCESSED %s\n",rpoHLISP->WriteToString());
}

//--------------------------------------------------------------
// command posting
//--------------------------------------------------------------

long cndoc_commandexecutor::post_command(SCP<CHyperLinkInfo> & rpoCommandHLISP,bool bWaitable)
{
	CSimpleLock oLock(m_oPostedCommandCS);
	long nCmdNumber = m_nCommandCounter++;
	rpoCommandHLISP->SetNumProp(GVAR_INTERNAL_COMMAND_NUMBER,nCmdNumber);
	
	if(bWaitable)
	{
		rpoCommandHLISP->SetNumProp(GVAR_INTERNAL_COMMAND_WAITABLE,1);
	}

	if(m_poApplication->is_async_mode())
	{
		m_oPostedCommandList.AddTail(rpoCommandHLISP);

		if(m_poApplication->is_notify_idle())
		{
#ifdef _DEBUG
			TRACE("POSTED: %s\n",(LPCSTR)rpoCommandHLISP->WriteToString());
			::Sleep(0);		//see Q173260
#endif
			TRACE("-GOING IDLE (%d)\n",::GetTickCount());
			m_oEventGoingIdle.ResetEvent();
		}
		m_oEventNewCmd.SetEvent();
	}
	else
	{
		_process_command(rpoCommandHLISP);
	}
	return nCmdNumber;
}

void cndoc_commandexecutor::wait_command(long nCommandNumber)
{
	if(m_poApplication->is_async_mode())
	{
		while(true)
		{
			CSingleLock oSLock(&m_oEventCommandProcessed,TRUE);
			if(m_bQuitting)
			{
				return;
			}
			CSimpleLock oLock(m_oPostedCommandCS);
			
			for(long iter = 0; iter <= m_oProcessedWaitableCommands.GetUpperBound(); iter++)
			{
				if(m_oProcessedWaitableCommands[iter] == nCommandNumber)
				{
					//found -> remove and return
					m_oProcessedWaitableCommands.RemoveAt(iter);
					return;
				}
			}
		}
	}
	else
	{
		return;
	}
}

void cndoc_commandexecutor::wait_idle()
{
	ASSERT(m_poApplication->is_notify_idle());

	TRACE("WAIT IDLE START\n");

	CSingleLock oSLock(&m_oEventGoingIdle,TRUE);
	
	TRACE("WAIT IDLE DONE\n");

	if(m_bQuitting)
	{
		return;
	}
}

bool cndoc_commandexecutor::_pre_translate_message(MSG & roMsg)
{
	return m_poApplication->_pre_translate_message(roMsg);
}
