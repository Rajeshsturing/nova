/*
	NAVO Enterprise 2008 (c)

	24.07.2002
	
	class:
		cndoc_integrator

	integruje podsystemy, trzyma connection do serwera itd
*/

#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\internal_h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\progressgadget.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoobj\navoobjcoor.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"

#include "common_pageman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_INTERFACE_MAP(cndoc_integrator, CCmdTargetInterface)
	INTERFACE_PART(cndoc_integrator, IID_INotificationSink, NotificationSink)
	INTERFACE_PART(cndoc_integrator, IID_IPingClient, PingClient)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(cndoc_integrator, NotificationSink)  
DELEGATE_UNKNOWN_INTERFACE(cndoc_integrator, PingClient)  

IMPLEMENT_ARRAYENUMERATOR(SCP<cndoc_pagestack>)

LPUNKNOWN cndoc_integrator::get_new_enum_AUTO()
{
	SCP< CArrayEnumerator< SCP<cndoc_pagestack> > > poNewArrayEnumSP = 
		NewSCP(new CArrayEnumerator< SCP<cndoc_pagestack> >(m_oAppStackArray));
	return poNewArrayEnumSP->GetEnumVARIANT().Detach();
}

void cndoc_integrator::_on_user_notify(long nOriginatorCookie,long lEvenCode,VARIANT * pDataVariant)
{
	ALL_TRY
	{
#ifdef _DEBUG
		CDebugTimeMeter oDTM("_on_user_notify");
#endif
		if(V_VT(pDataVariant) == (VT_VARIANT | VT_BYREF))
		{
			VARIANT * pVariant = pDataVariant->pvarVal;
			ASSERT(pVariant);
			_on_user_notify(nOriginatorCookie,lEvenCode,pVariant); //Uwaga! wywo³uje siebie ale ju¿ bez byRef
		}
		else
		{
			SCP<CHyperLinkInfo> poHLISCP = NewSCP(new CHyperLinkInfo());
			poHLISCP->SetNumProp(GVAR_CMD,CMD_INTERNAL_USER_NOTIFY);
			
			poHLISCP->SetNumProp(INTERNALVAR_USER_NOTIF_ORIG,nOriginatorCookie);
			poHLISCP->SetNumProp(INTERNALVAR_USER_NOTIF_EVENT,lEvenCode);
			poHLISCP->SetProp(INTERNALVAR_USER_NOTIF_VALUE,
				reinterpret_cast<const CSmartOleVariant &>(*pDataVariant));
			m_poApplication->post_command(poHLISCP,false);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

