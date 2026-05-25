/*
	NAVO Sp. z o.o. (2002)
	25.07.2002

	NAVO Enterprise

	class:
		cndoc_pagestack - stos stron
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\internal_h1000.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\navothread.h"		//navo thread
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navogal\ngal_iface.h"		//graphics

#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "..\navoui\oleeventsink_ndoc.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"
#include "..\navoobj\cursorcollection.h"
#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"
#include "navoview_impl_ndoc.h"
#include "cview_ndoc.h"

#include "common_pageman.h"

#include "navopage_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cndoc_pagestack::cndoc_pagestack(cndoc_integrator * poIntegrator,SCP<cned_arena> poArenaSP) :
	m_poIntegrator(poIntegrator),
	m_poArenaSP(poArenaSP),
	m_dwPageRef(0)
{
	ASSERT(m_poArenaSP.PointsObject());
	EnableAutomation();
}

cndoc_pagestack::~cndoc_pagestack()
{
	ASSERT(m_dwPageRef == 0);
}


void cndoc_pagestack::on_page_detach()
{
	m_dwPageRef--;
	if(m_dwPageRef == 0)
	{
		ASSERT(is_empty());
		//gdy nic go nie trzyma i jest pusty
		get_integrator()->on_stack_finished(this);
	}
}

void cndoc_pagestack::on_activate(bool bActivated)
{
	ASSERT(!is_empty() || !bActivated);
	ASSERT(m_dwPageRef > 0);

	if(bActivated)
	{
		POSITION pos = m_oPageStack.GetBottomPosition();
		while(pos)
		{
			SCP<cndoc_page__> poPageSP = m_oPageStack.GetAt(pos);
			cndoc_navopage * poNAVOPage = dynamic_cast<cndoc_navopage *>(poPageSP.Get());
			if(poNAVOPage != NULL)
			{
				ASSERT(poNAVOPage->get_window().PointsObject());
				m_poArenaSP->move_window_to_top(poNAVOPage->get_window());
			}
			m_oPageStack.MoveUp(pos);
		}
		on_minimize(false);
	}
}

void cndoc_pagestack::on_minimize(bool bMinimize)
{
	POSITION pos = m_oPageStack.GetBottomPosition();
	while(pos)
	{
		SCP<cndoc_page__> poPageSP = m_oPageStack.GetAt(pos);
		cndoc_navopage * poNAVOPage = dynamic_cast<cndoc_navopage *>(poPageSP.Get());
		if(poNAVOPage != NULL)
		{
			ASSERT(poNAVOPage->get_window().PointsObject());
			//ned_to_do: poNAVOPage->get_window()->set_prop_minimized(bMinimize);
		}
		m_oPageStack.MoveUp(pos);
	}
}

void cndoc_pagestack::attach_view(SCP<cndoc_view__> poViewSP)
{
	m_poViewSP = poViewSP;
}

void cndoc_pagestack::update_view()
{
	if(!is_empty())
	{
		get_top_page()->update();
	}
	//when connected to view, update layout
	if(m_poViewSP.PointsObject())
	{
		m_poViewSP->update();
	}
}

void cndoc_pagestack::assign_thread(SCP<CNEO_thread> poThreadSP)
{
	ASSERT(m_poTransactionTheadSP.PointsNull());
	m_poTransactionTheadSP = poThreadSP;
}

SCP<CNEO_thread> cndoc_pagestack::get_thread()
{
	return m_poTransactionTheadSP;
}

void cndoc_pagestack::push(SCP<cndoc_page__> poPageSP)
{
	//add page to stack
	ASSERT(poPageSP.PointsObject());
	ASSERT(poPageSP->get_stack() == this);

	m_oPageStack.Push(poPageSP);
	
	//add page's window to arena stack
	cndoc_navopage * poNavoPage = dynamic_cast<cndoc_navopage *>(poPageSP.Get());
	if(poNavoPage != NULL)
	{
		m_poArenaSP->add_window_to_stack(poNavoPage->get_window(),NULL);
	}
}

void cndoc_pagestack::pop()
{
	ASSERT(!is_empty());
	SCP<cndoc_page__> poPageSP = m_oPageStack.GetTop();

	m_oPageStack.Pop();
	cndoc_navopage * poNavoPage = dynamic_cast<cndoc_navopage *>(poPageSP.Get());
	if(poNavoPage != NULL)
	{
		m_poArenaSP->remove_window_from_stack(poNavoPage->get_window());
	}
}

SCP<cndoc_page__> cndoc_pagestack::get_top_page()
{
	ASSERT(!is_empty());
	return m_oPageStack.GetTop();
}

SCP<cndoc_page__> cndoc_pagestack::find_page_on_iid(long nIID)
{
	POSITION pos = m_oPageStack.GetTopPosition();
	while(pos)
	{
		if(m_oPageStack.GetAt(pos)->get_iid() == nIID)
		{
			return m_oPageStack.GetAt(pos);
		}
		m_oPageStack.MoveDown(pos);
	}
	return SCP<cndoc_page__>();
}

bool cndoc_pagestack::on_action_results(ned_action_result & roActionResults)
{
	if(!is_empty())
	{
		return get_top_page()->on_action_results(roActionResults);
	}
	return false;
}

bool cndoc_pagestack::process_command(SCP<cndoc_page__> poTargetPageSP,SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	ASSERT(poTargetPageSP.PointsObject());
	ASSERT(poTargetPageSP->get_stack() == this);
	ASSERT(rpoCommandHLISP.PointsObject());

	on_minimize(false);

	if(poTargetPageSP->process_command(rpoCommandHLISP))
	{
		return true;
	}

	long nCommand = 0;
	if(!rpoCommandHLISP->SafeGetNumProp(GVAR_CMD,nCommand))
	{
		return false;
	}

	//w wersji developerskiej zrób layout strony

	switch(nCommand)
	{
	case CMD_GOBACK:
	case CMD_INTERNAL_GOBACK:
		process_command_goback(rpoCommandHLISP);
		return true;
	case CMD_INTERNAL_MINIMIZE:
		on_minimize(true);
		return true;
	default:
		return false;
	}
}

void cndoc_pagestack::process_command_goback(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	ASSERT(get_top_page().PointsObject());

	if(rpoCommandHLISP.PointsObject())
	{
		if(rpoCommandHLISP->PropertyExists(GVAR_MODALRES))
		{
			get_top_page()->SetResultAUTO(rpoCommandHLISP->GetNumProp(GVAR_MODALRES));
		}
	}
	if(get_top_page()->is_in_modal_loop())
	{
		get_integrator()->exit_yield();
	}
	else
	{
		pop();
	}
}

bool cndoc_pagestack::on_idle(bool bForeground)
{
	ASSERT(!is_empty());

	bool bResult = false;
	
	POSITION pos = m_oPageStack.GetBottomPosition();
	while(pos)
	{
		if(m_oPageStack.GetAt(pos).Get() != m_oPageStack.GetTop().Get())
		{
			bResult = bResult | m_oPageStack.GetAt(pos)->on_idle(false);
		}
		m_oPageStack.MoveUp(pos);
	}

	return bResult | m_oPageStack.GetTop()->on_idle(bForeground);
}

//----------------------------------------------------------------------------------------
// automation
//----------------------------------------------------------------------------------------

//{{AFX_MSG_MAP(cndoc_pagestack)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(cndoc_pagestack, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(cndoc_pagestack)
	DISP_FUNCTION(cndoc_pagestack, "pushpage", PushPageAUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(cndoc_pagestack, "poppage", PopPageAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_pagestack, "gettoppage", GetTopPageAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

void cndoc_pagestack::PushPageAUTO(LPDISPATCH lpPageDispatch)
{
	ALL_TRY
	{
		SCP<cndoc_navopage> poNavoPageSP = cndoc_navopage::FromIDispatch(lpPageDispatch);
		if(poNavoPageSP.PointsNull())
		{
			//to_do: error 
			ASSERT(false);
			CString oString("stack::pushpage z³y wskaŸnik lub przekazany przez page_");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		if(poNavoPageSP->get_stack() != this)
		{
			//to_do: error 
			ASSERT(false);
			CString oString("strona z innego stosu");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}

		push(NewSCP<cndoc_page__>(poNavoPageSP.Get(),true));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_pagestack::PopPageAUTO()
{
	ALL_TRY
	{
		pop();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_pagestack::GetTopPageAUTO()
{
	ALL_TRY
	{
		if(is_empty())
		{
			return NULL;
		}

		SCP<cndoc_page__> poPageSP = get_top_page();
		ASSERT(poPageSP.PointsObject());
		return poPageSP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

