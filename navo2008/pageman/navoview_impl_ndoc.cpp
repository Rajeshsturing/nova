/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	26.01.2003

	class:
		cndoc_navoview_impl
	
		implements ned_arena-based window
*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navothread.h"		//navo thread
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "navoview_impl_cont_ndoc.h"
#include "navoview_impl_ndoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cndoc_navoview_impl::cndoc_navoview_impl(cndoc_navoview_impl_container_ * poContainer) :
	m_poContainer(poContainer),
	m_nLastClickFlags(0),
	m_bInsideShortcutMenu(false),
	m_hWindow(NULL)
{
	ASSERT(m_poContainer != NULL);
}

void cndoc_navoview_impl::set_arena(SCP<cned_arena> poArenaSP)
{
	m_poArenaSP = poArenaSP;
	
	if(m_hWindow != HWND(NULL))
	{
		if(m_poArenaSP.PointsObject())
		{
			m_poArenaSP->attach_os_window(m_hWindow);
		}
	}
}

void cndoc_navoview_impl::attach_window(HWND hWindow)
{
	if(hWindow != m_hWindow)
	{
		m_hWindow = hWindow;
		if(m_poArenaSP.PointsObject())
		{
			m_poArenaSP->attach_os_window(m_hWindow);
		}
	}
}

cndoc_navoview_impl::~cndoc_navoview_impl()
{
}

//---------------------- events -------------------------
void cndoc_navoview_impl::on_paint_event(const ng_rect & roUpdateRect)
{
	ALL_TRY
	{
		m_poArenaSP->external_invalidate_paint(roUpdateRect);
		_do_paint();
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_left_button_down_event(UINT nFlags,ng_point oPoint)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		m_nLastClickFlags = nFlags;
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_mouse oMouseAction(oDC,oPoint,nFlags);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_mouse_click(oMouseAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_left_button_up_event(UINT /*nFlags*/,ng_point oPoint)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_mouse oMouseAction(oDC,oPoint,m_nLastClickFlags);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_mouse_endclick(oMouseAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
		
		//special processing for right click
		//actually on_action_results fills command list with custom items
		//code below displays menu and posts on_action_results again (with choosen command)
		if(oMouseAction.is_RIGHT_click())
		{
			if(oResult.get_info(0).PointsObject())
			{
				if(oResult.get_info(0)->get_type() == eit_command_list)
				{
					_retrieve_command_list_start_point(oResult.get_info(0)) = oPoint;
				}
			}
			_process_shortcutmenu(oResult);
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::_process_shortcutmenu(ned::ned_action_result & roResult)
{
	if(roResult.get_info(0).PointsObject())
	{
		if(roResult.get_info(0)->get_type() == eit_command_list)
		{
			SCP<CCommandList> poCommandListSP = _retrieve_command_list(roResult.get_info(0));
			if(!poCommandListSP->IsEmpty())
			{
				m_bInsideShortcutMenu = true;	//powoduje zmianê kursora na arrow
				
				ng_point oPoint = _retrieve_command_list_start_point(roResult.get_info(0));
				SCP<CHyperLinkInfo> poCommandHLISP = poCommandListSP->Show(CPoint(oPoint.get_x(),oPoint.get_y()),m_hWindow);
				
				m_bInsideShortcutMenu = false;

				if(poCommandHLISP.PointsObject())
				{
					ned::ned_action_result oCommandResult;
					SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(NEDID_NOTHING));
					poEventCmdSP->set_command(poCommandHLISP);
					oCommandResult.add_info(poEventCmdSP);
					m_poContainer->on_action_results(oCommandResult,m_poArenaSP.Get());
				}
			}
		}
	}
}

void cndoc_navoview_impl::on_left_button_dbl_click_event(UINT nFlags,ng_point oPoint)
{
	ALL_TRY
	{
		on_left_button_down_event(nFlags | MK_DBLCLK, oPoint);
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_mouse_move_event(UINT nFlags,ng_point oPoint)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_mouse oMouseAction(oDC,oPoint,nFlags);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_mouse_over(oMouseAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_mouse_wheel_event(UINT nFlags,long zDelta,ng_point oPoint)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_mouse_wheel oMouseWheelAction(oDC,oPoint,nFlags,zDelta);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_mouse_wheel(oMouseWheelAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_right_button_down_event(UINT nFlags,ng_point oPoint)
{
	m_nLastClickFlags = nFlags;
	on_left_button_down_event(nFlags,oPoint);
}

void cndoc_navoview_impl::on_right_button_up_event(UINT nFlags,ng_point oPoint)
{
	on_left_button_up_event(nFlags,oPoint);
}

bool cndoc_navoview_impl::on_key_down_event(UINT nChar, UINT /*nRepCnt*/, UINT nFlags)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_kbd oKeyAction(oDC,nChar,nFlags);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_keydown(oKeyAction,oResult);
		

		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
		_process_shortcutmenu(oResult);
		
		return oResult.is_processed();
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
		return false;
	}
}

void cndoc_navoview_impl::on_olecontrol_event(long IdCtrl,AFX_EVENT* pEvent)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_oleevent oOleEventAction(oDC,IdCtrl,pEvent);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_olecontrol(oOleEventAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_size_changed_event()
{
	ALL_TRY
	{
		if(m_poArenaSP.PointsObject())
		{
			CDCGetReleaseHolder oGRH(m_hWindow);
			ng_dc oDC(oGRH.get_hdc());
					
			ASSERT(m_poArenaSP.PointsObject());

			ng_rect oNewRect;
			_get_client_rect(oNewRect);
			m_poArenaSP->on_event_size_changed(oDC,oNewRect);
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

bool cndoc_navoview_impl::on_set_cursor_event()
{
	ALL_TRY
	{
		if(m_bInsideShortcutMenu)
		{
			::SetCursor(::LoadCursor(NULL,IDC_ARROW));
			return true;
		}
		else
		{
			ASSERT(m_poArenaSP.PointsObject());
			return m_poArenaSP->on_event_set_cursor();
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
		return false;
	}
}

void cndoc_navoview_impl::on_time_elapsed_event(UINT idTimer)
{
	ALL_TRY
	{
		ASSERT(m_poContainer);
		
		CDCGetReleaseHolder oGRH(m_hWindow);
		ng_dc oDC(oGRH.get_hdc());

		ned_action_timer oTimerAction(oDC,idTimer);
		ned::ned_action_result oResult;
		m_poArenaSP->on_event_timer(oTimerAction,oResult);
		
		m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::update_view()
{
	//do paint
	_do_paint();
}

#ifdef _DEBUG
long debug_paint_recursion = 0;
#endif

void cndoc_navoview_impl::_do_paint()
{
#ifdef _DEBUG
		if(debug_paint_recursion)
		{
			return;
		}
		CIncDecHolder<long> oDebugPainRec(debug_paint_recursion);
#endif
		
	ALL_TRY
	{
		ASSERT(m_poContainer);
		ASSERT(m_poArenaSP.PointsObject());
		
		if(!m_poContainer->is_visible())
		{
			return;
		}
		{
			CDCGetReleaseHolder oGRH(m_hWindow);
			ng_dc oDC(oGRH.get_hdc());
			
			ned_action_paint oActionPaint(oDC);
			ned::ned_action_result oResult;

			//to wymusza aktualizacjê (rendering) stron
			m_poArenaSP->on_event_paint(oActionPaint,oResult);
			m_poContainer->on_action_results(oResult,m_poArenaSP.Get());
		}
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}

void cndoc_navoview_impl::on_idle_event()
{
	ALL_TRY
	{
		//do paint
		_do_paint();
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		_error_storage() += roNavoException;
	}
}
