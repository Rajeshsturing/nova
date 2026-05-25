/*
	NAVO Enterprise 2008 (c)

	26.07.2002
	
	class:
		cndoc_external_client

		obudowa dla dostêpu do navo2002.client z zewn¹trz
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navogal\ngal_iface.h"		//graphics
#include "application_ndoc.h"
#include "external_client_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(cndoc_external_client, CCmdTarget)

cndoc_external_client::cndoc_external_client() :
	m_bAsyncMode(false),
	m_poApplication(NULL)
{
	EnableAutomation();
	AfxOleLockApp();
}

void CleanupScriptEngineEtc();	//destroy debugger etc.

cndoc_external_client::~cndoc_external_client()
{
	ALL_TRY
	{
		if(m_poApplication != NULL)
		{
			if(m_bAsyncMode)
			{
				m_poApplication->quit();
			}
			else
			{
				m_poApplication->done();
				m_poApplication->ExternalRelease();
			}
			m_poApplication = NULL;
		}
	}
	ALL_CATCH(CNavoException & /*roNavoException*/)
	{
	}

	CleanupScriptEngineEtc();
	AfxOleSetUserCtrl(FALSE);
	AfxOleUnlockApp();
}

BEGIN_DISPATCH_MAP(cndoc_external_client, CCmdTarget)
	//{{AFX_DISPATCH_MAP(cndoc_external_client)
	DISP_FUNCTION(cndoc_external_client, "document", GetUserThreadAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_external_client, "login", LoginAUTO, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(cndoc_external_client, "setasyncmode", SetAsyncModeAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


// {188cb167-82a4-4498-87d0-ebd8d9a00fb8 }
IMPLEMENT_OLECREATE(cndoc_external_client, "navo2002.client",0x188cb167,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)


LPDISPATCH cndoc_external_client::GetUserThreadAUTO() 
{
	ALL_TRY
	{
		if(m_poApplication == NULL)
		{
			if(m_bAsyncMode)
			{
				m_poApplication = cndoc_application::create_application_thread(
					reinterpret_cast<long>(this)).Get();
				/*
					reference counting is not performed
					quit method is used to singal thread to stop
				*/
				m_poApplication->set_notify_idle();
			}
			else
			{
				m_poApplication = new cndoc_application(false,reinterpret_cast<long>(this));
			}
		}
		return m_poApplication->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cndoc_external_client::LoginAUTO(LPCTSTR lpUser, LPCTSTR lpPwd) 
{
	//to_do: validate
	return TRUE;
}

void cndoc_external_client::SetAsyncModeAUTO() 
{
	ASSERT(m_poApplication == NULL);
	m_bAsyncMode = true;
}
