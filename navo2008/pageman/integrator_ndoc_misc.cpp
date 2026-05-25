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
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\progressgadget.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\splashwindow.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navoscript\CacheManagerUser.h"
#include "..\navoobj\dbapconnparam.h"
#include "..\navoobj\navoobjcoor.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"

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

#include "xmlpagecachemu.h"
#include "configuserpref.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SCP<CDefinitionManager> cndoc_integrator::get_definition_manager()
{
	return m_poDefinitionManagerSP;
}


SCP <CHyperLinkInfo> cndoc_integrator::GetCommonEnvironmentHLI()
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->GetCommonEnvironmentHLI();
}

//------------------------------------------------------- counted resources ----------
bool cndoc_integrator::fwd_create_counted_resource(LPCTSTR lpResName, long nMaxUsage)
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->fwd_create_counted_resource(lpResName, nMaxUsage);
}

bool cndoc_integrator::fwd_delete_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->fwd_delete_counted_resource(lpResName);
}

long cndoc_integrator::fwd_use_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->fwd_use_counted_resource(lpResName);
}

long cndoc_integrator::fwd_get_usage_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	return m_poNavoObjCoorSP->fwd_get_usage_counted_resource(lpResName);
}

void cndoc_integrator::fwd_release_counted_resource(LPCTSTR lpResName)
{
	ASSERT(m_poNavoObjCoorSP.PointsObject());
	m_poNavoObjCoorSP->fwd_release_counted_resource(lpResName);
}


//------------------------------------------------------------------------------------
// netuser_*
//------------------------------------------------------------------------------------
long cndoc_integrator::netuser_getinfo(long nIter, VARIANT * pUserName, VARIANT * pComputerName)
{
	ASSERT(nIter >= 0);		//warn app programmer
	ASSERT(m_poNotificationManagerSP.PointsObject());
	if (nIter == 0)		//value 0 means ->reload cache
	{
		m_oCachedNetUserInfoArray.RemoveAll();
		HRESULT hr = QueryNotificationManagerClients(m_poNotificationManagerSP, m_oCachedNetUserInfoArray);
		if (hr != S_OK)
		{
			ThrowFromInterface(m_poNotificationManagerSP);
		}
	}
	if (nIter > m_oCachedNetUserInfoArray.GetUpperBound() || nIter < 0)
	{
		return 0;
	}
	CSmartOleVariant oCompNameSOV(m_oCachedNetUserInfoArray[nIter].GetComputerName());
	CSmartOleVariant oUserNameSOV(m_oCachedNetUserInfoArray[nIter].GetUserName());
	*pUserName = oCompNameSOV.Detach();
	*pComputerName = oUserNameSOV.Detach();
	return m_oCachedNetUserInfoArray[nIter].GetCookie();
}

void cndoc_integrator::netuser_notify(long nUserCookie, long nEventCode, const VARIANT & roValue)
{
	if (V_VT(&roValue) & VT_BYREF)
	{
		VARIANT * pVariant = roValue.pvarVal;
		ASSERT(pVariant);
		netuser_notify(nUserCookie, nEventCode, *pVariant);
		return;
	}
	ASSERT(m_poNotificationManagerSP.PointsObject());
	HRESULT hr = m_poNotificationManagerSP->NotifyUser(m_nNotification_Cookie, nUserCookie, nEventCode, const_cast<LPVARIANT>(&roValue));
	if (hr != S_OK && hr != S_FALSE)
	{
		ThrowFromInterface(m_poNotificationManagerSP);
	}
}

void cndoc_integrator::netuser_setprop(long nUserCookie, long nProp, const VARIANT & roValue)
{
	if (V_VT(&roValue) & VT_BYREF)
	{
		VARIANT * pVariant = roValue.pvarVal;
		ASSERT(pVariant);
		netuser_setprop(nUserCookie, nProp, *pVariant);
		return;
	}
	ASSERT(m_poNotificationManagerSP.PointsObject());
	VERIFY(S_OK == m_poNotificationManagerSP->SetProp(nUserCookie, nProp, roValue));
}

bool cndoc_integrator::netuser_getprop(long nUserCookie, long nProp, VARIANT * pValue)
{
	ASSERT(m_poNotificationManagerSP.PointsObject());
	
	HRESULT hr = S_OK;
	
	if (IsNXMTransport())
	{
		m_poNotificationManagerSP->GetProp2(nUserCookie, nProp, pValue, &hr);
	}
	else
	{
		hr = m_poNotificationManagerSP->GetProp(nUserCookie, nProp, pValue);
		if (hr != S_OK && hr != S_FALSE)
		{
			ThrowFromInterface(m_poNotificationManagerSP);
		}
	}

	return (hr == S_OK);
}

long cndoc_integrator::netuser_getcookie() const
{
	return m_nNotification_Cookie;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

long cndoc_integrator::font_desc_to_index(const ned_font_spec & roFontSpec)
{
	if (m_poMainArenaSP.PointsObject())
	{
		ASSERT(false);
		//ned_to_do: 
		return -1;
	}

	//to_do: error: arena must exists at this moment
	ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
}

void cndoc_integrator::set_current_style(const CSmartOleVariant & roSOV)
{
	if (m_poMainArenaSP.PointsObject())
	{
		m_poMainArenaSP->set_current_style(roSOV);
		return;
	}

	//to_do: error: arena must exists at this moment
	ThrowNavoException(ERCO_TODO, IDPAGE_NOTAVAILABLE);
}

void cndoc_integrator::apply_settings(const cndoc_config_user_pref & roCUP)
{
	if (roCUP.m_bFastGraphics != _is_fast_graphics())
	{
		_set_fast_graphics(roCUP.m_bFastGraphics);
	}
	if (roCUP.m_bWindowsLook != ned::_metrics().is_windows_look())
	{
		_metrics().set_windows_look(roCUP.m_bWindowsLook);
	}
	if (m_poMainArenaSP.PointsObject())
	{
		if (roCUP.m_bAnimateWindows != m_poMainArenaSP->get_prop_animate_windows())
		{
			m_poMainArenaSP->set_prop_animate_windows(roCUP.m_bAnimateWindows);
		}
	}
}

void cndoc_integrator::__check_memory_state()
{
	//first compact
	if (is_memory_low())
	{
		if (m_poMainArenaSP.PointsObject())
		{
			//ned_to_do: m_poMainArenaSP->on_compact_memory();
		}
		if (m_poOutlookBarArenaSP.PointsObject())
		{
			//ned_to_do: m_poOutlookBarArenaSP->on_compact_memory();
		}
		if (m_poToolbarArenaSP.PointsObject())
		{
			//ned_to_do: m_poToolbarArenaSP->on_compact_memory();
		}
	}

	//set memory state when still low
	bool bLowMem = is_memory_low();

	if (m_poMainArenaSP.PointsObject())
	{
		//ned_to_do: m_poMainArenaSP->set_low_memory_mode(bLowMem);
	}
	if (m_poOutlookBarArenaSP.PointsObject())
	{
		//ned_to_do: m_poOutlookBarArenaSP->set_low_memory_mode(bLowMem);
	}
	if (m_poToolbarArenaSP.PointsObject())
	{
		//ned_to_do: m_poToolbarArenaSP->set_low_memory_mode(bLowMem);
	}
}

bool cndoc_integrator::_pre_translate_message(MSG & roMsg)
{
	if (m_poMainArenaSP.PointsObject())
	{
		return m_poMainArenaSP->_pre_translate_message(roMsg);
	}
	return false;
}

bool cndoc_integrator::backup(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, SCP<IStream> poDestStreamSP)
{
	return m_poNavoObjCoorSP->WriteToArchive(lpSAUser, lpPwd, lpArchivePwd, poDestStreamSP);
}

bool cndoc_integrator::restore(LPCSTR lpSAUser, LPCSTR lpPwd, LPCSTR lpArchivePwd, SCP<IStream> poSrcStreamSP)
{
	return m_poNavoObjCoorSP->ReadFromArchive(lpSAUser, lpPwd, lpArchivePwd, poSrcStreamSP);
}

