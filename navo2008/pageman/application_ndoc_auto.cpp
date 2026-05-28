/*
	NAVO Enterprise 2008 (c)

	24.07.2002

	class:
		cndoc_application

		g³ówny obiekt (wewnêtrzny)
		odpowiadaj¹cy za pojedyñcz¹ sesjê

		AUTOMATION PART
*/

#include "stdafx.h"
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
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\streamautoobject.h"
#include "..\navocomutil\SystemAutoObject.h"
#include "..\include\scriptuser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\cursorcollection.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\commandlist.h"
#include "..\navoui\oleeventsink_ndoc.h"

using namespace ned;

#include "common_pageman.h"

#include "navopage_ndoc.h"
#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"

static void _cocoon_application_diag(const CString& roMessage)
{
	try
	{
		CFile oFile;
		if (!oFile.Open(_T("C:\\app\\navo-native-diagnostics.log"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			return;
		}

		oFile.SeekToEnd();
		CString oLine;
		CTime oNow = CTime::GetCurrentTime();
		oLine.Format(_T("%s [application_ndoc] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

BEGIN_DISPATCH_MAP(cndoc_application, CNavoThread)
	//{{AFX_DISPATCH_MAP(cndoc_application)
	DISP_FUNCTION(cndoc_application, "afc", fwd_GetAFC_AUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getmodule", fwd_getmoduleAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(cndoc_application, "postcommand", fwd_PostCommandStringAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "postcommandiid", fwd_PostCommandStringIIDAUTO, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION(cndoc_application, "createstreamobj", CreateStreamObjectAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_application, "system", 700, CreateSystemObjectAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "createhlistr", CreateHLIOnStringAUTO, VT_DISPATCH, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "createhli", CreateHLIAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getpagehli", fwd_getpagehliAUTO, VT_DISPATCH, VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "callcommand", fwd_CallCommandStringAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "putctrldata", fwd_PutControlDataAUTO, VT_EMPTY, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "putctrlcmd", fwd_PutControlCommandAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "applyctrldata", ApplyControlDataAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "waitidle", WaitIdleAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "font2inx", fwd_Font2InxAUTO, VT_I4, VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL)
	DISP_FUNCTION(cndoc_application, "font2inx2", fwd_Font2Inx_v2_AUTO, VT_I4, VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4)
	DISP_FUNCTION(cndoc_application, "setmenu", SetMenuAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "stdobjdef", fwd_GetDefinitionManagerAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_application, "getappfile", 701, fwd_GetRawAppFileAUTO, VT_VARIANT, VTS_I4)
	DISP_FUNCTION(cndoc_application, "pushpage", fwd_PushPageAUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(cndoc_application, "poppage", fwd_PopPageAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "gettoppage", fwd_GetTopPageAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getusers", fwd_GetUserInfoAUTO, VT_I4, VTS_I4 VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(cndoc_application, "notifyuser", fwd_NotifyUserAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "getmycookie", fwd_GetUserCookieAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getuserprop", fwd_GetUserPropertyAUTO, VT_BOOL, VTS_I4 VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(cndoc_application, "setuserprop", fwd_SetUserPropertyAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "timer", SetTimerAUTO, VT_EMPTY, VTS_I4 VTS_VARIANT VTS_I4)
	DISP_PROPERTY_EX_ID(cndoc_application, "_NewEnum", DISPID_NEWENUM, fwd_GetNewEnumAUTO, fwd_SetNewEnumAUTO, VT_UNKNOWN)
	DISP_FUNCTION(cndoc_application, "gettoolbar", fwd_GetToolbarAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getoutlookbar", fwd_GetOutlookbarAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "iscmdenabled", IsCommandEnabledAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION(cndoc_application, "performing", CreatePerformingObjectAUTO, VT_DISPATCH, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "bringtotop", BringWindowToTopAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "updateshelltray", SetShellTrayStateAUTO, VT_EMPTY, VTS_I4 VTS_BOOL VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "purgelocalcache", fwd_PurgeLocalCachesAUTO, VT_EMPTY, VTS_NONE)

	DISP_FUNCTION(cndoc_application, "createres", fwd_CreateCountedResourceAUTO, VT_BOOL, VTS_BSTR VTS_I4)
	DISP_FUNCTION(cndoc_application, "deleteres", fwd_DeleteCountedResourceAUTO, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "useres", fwd_UseCountedResourceAUTO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(cndoc_application, "releaseres", fwd_ReleaseCountedResourceAUTO, VT_EMPTY, VTS_BSTR)
	DISP_PROPERTY_EX(cndoc_application, "zoom", fwd_GetZoomAUTO, fwd_SetZoomAUTO, VT_I4)
	DISP_FUNCTION(cndoc_application, "showoutlookbar", fwd_ShowHideOutlookBarAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(cndoc_application, "showtoolbar", fwd_ShowHideToolBarAUTO, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(cndoc_application, "getmenuobj", GetCurrentMenuTreeAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX(cndoc_application, "menuchanged", fwd_GetMenuChangedFlagAUTO, fwd_SetMenuChangedFlagAUTO, VT_BOOL)
	DISP_FUNCTION(cndoc_application, "style", fwd_SetCurrentStyleAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "parsexml", ParseXML_AUTO, VT_EMPTY, VTS_DISPATCH VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "getusageres", fwd_GetUsageCountedResourceAUTO, VT_I4, VTS_BSTR)

#ifdef PULL_ERROR_MESSAGES
	DISP_FUNCTION(cndoc_application, "isnewmessage", GetNewMessageFlagAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "clearnewmessage", ClearNewMessageFlagAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "getnewmessage", GetNewMessageAUTO, VT_BOOL, VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT)
#endif

	DISP_FUNCTION(cndoc_application, "backup", fwd_BackupAUTO, VT_BOOL, VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "restore", fwd_RestoreAUTO, VT_BOOL, VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(cndoc_application, "nx_", fwd_GetNX_AUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "arenabackcolor", fwd_SetArenaBackColorAUTO, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(cndoc_application, "nxm_net_", fwd_GetNXMNet_AUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cndoc_application, "message_sink", MessageSink_AUTO, VT_EMPTY, VTS_DISPATCH)

	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//-------------------------------------------------------------
//forwardery
//-------------------------------------------------------------
long cndoc_application::__fwd_PostCommandString(LPCTSTR lpHyperLinkString, bool bWaitable)
{
	SCP<CHyperLinkInfo> poHyperLinkSP = ReadHLIFromString(lpHyperLinkString);
	if (poHyperLinkSP.PointsObject())
	{
		if (!poHyperLinkSP->PropertyExists(GVAR_PAGE_IID))
		{
			ASSERT(m_poIntegratorSP.PointsObject());

			if (m_poIntegratorSP->_is_any_stack())
			{
				SCP<cndoc_pagestack> poPageStackSP = m_poIntegratorSP->_get_active_stack();
				if (!poPageStackSP->is_empty())
				{
					poHyperLinkSP->SetNumProp(GVAR_PAGE_IID,
						poPageStackSP->get_top_page()->get_iid());
				}
			}
		}
		return post_command(poHyperLinkSP, bWaitable);
	}
	else
	{
		ASSERT(false);	//niepoprawna komenda. throw ?
		return -1;
	}
}

void cndoc_application::fwd_PostCommandStringAUTO(LPCTSTR lpHyperLinkString)
{
	ALL_TRY
	{
		__fwd_PostCommandString(lpHyperLinkString,false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_CallCommandStringAUTO(LPCTSTR lpHyperLinkString)
{
	ALL_TRY
	{
		long nCommandNumber = __fwd_PostCommandString(lpHyperLinkString,true);
		wait_command(nCommandNumber);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_PostCommandStringIIDAUTO(LPCTSTR lpHyperLinkString, long nPageIID)
{
	ALL_TRY
	{
		ASSERT(nPageIID);
		SCP<CHyperLinkInfo> poHyperLinkSP = ReadHLIFromString(lpHyperLinkString);
		if (poHyperLinkSP.PointsObject())
		{
			poHyperLinkSP->SetNumProp(GVAR_PAGE_IID,nPageIID);
			post_command(poHyperLinkSP,false);
		}
		else
		{
			ASSERT(false);	//niepoprawna komenda. throw ?
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_Font2InxAUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike)
{
	ALL_TRY
	{
		return fwd_Font2Inx_v2_AUTO(lpFontName,nFontSize,bBold,bItalic,bStrike,FALSE,EASTEUROPE_CHARSET);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long cndoc_application::fwd_Font2Inx_v2_AUTO(LPCTSTR lpFontName, long nFontSize, BOOL bBold, BOOL bItalic, BOOL bStrike, BOOL bUnderLine, long nCharSet)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());

		ned_font_spec oFontSpec;
		oFontSpec.make_normal();
		oFontSpec.m_oFontNameString = lpFontName;
		oFontSpec.m_nSize = nFontSize;
		oFontSpec.m_bBold = (bBold != FALSE);
		oFontSpec.m_bItalic = (bItalic != FALSE);
		oFontSpec.m_bStrikeThrough = (bStrike != FALSE);
		oFontSpec.m_bUnderLine = (bUnderLine != FALSE);
		oFontSpec.m_sCharSet = SHORT(nCharSet);

		return m_poIntegratorSP->font_desc_to_index(oFontSpec);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_GetDefinitionManagerAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		ASSERT(m_poIntegratorSP->get_definition_manager().PointsObject());
		return m_poIntegratorSP->get_definition_manager()->GetDispatch(true);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

VARIANT cndoc_application::fwd_GetRawAppFileAUTO(long IdFile)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<IStream> poRawStreamSP = m_poIntegratorSP->get_raw_app_file(IdFile);
		CSmartOleVariant oSOV(poRawStreamSP);
		return oSOV.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


LPDISPATCH cndoc_application::fwd_getmoduleAUTO(long IdPage)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		{
			CString oDiag;
			oDiag.Format(_T("fwd_getmodule begin page=%ld"), IdPage);
			_cocoon_application_diag(oDiag);
		}

		SCP<cndoc_page__> poModuleSP = m_poIntegratorSP->create_module(IdPage);
		if (poModuleSP.PointsObject())
		{
			LPDISPATCH lpStaticDispatch = poModuleSP->GetDispatch(false);
			LPDISPATCH lpDispatch = poModuleSP->GetDynamicDispatch(true);
			CString oDiag;
			oDiag.Format(_T("fwd_getmodule page=%ld page_ptr=0x%08lx static_dispatch=0x%08lx return_dispatch=0x%08lx iid=%ld"),
				IdPage, (long)poModuleSP.Get(), (long)lpStaticDispatch, (long)lpDispatch, poModuleSP->get_iid());
			_cocoon_application_diag(oDiag);

			if (lpDispatch != NULL)
			{
				try
				{
					LPOLESTR pNames[3];
					pNames[0] = L"navo_client_init";
					pNames[1] = L"navo_client_get_trans";
					pNames[2] = L"get_this";
					for (long iter = 0; iter < 3; iter++)
					{
						DISPID dispid = DISPID_UNKNOWN;
						HRESULT hr = lpDispatch->GetIDsOfNames(IID_NULL, &pNames[iter], 1, LOCALE_SYSTEM_DEFAULT, &dispid);
						CString oProbeDiag;
						oProbeDiag.Format(_T("fwd_getmodule probe page=%ld name=%s hr=0x%08lx dispid=%ld"),
							IdPage, CString(pNames[iter]), hr, dispid);
						_cocoon_application_diag(oProbeDiag);
					}
				}
				catch (...)
				{
					CString oProbeDiag;
					oProbeDiag.Format(_T("fwd_getmodule probe page=%ld threw native exception"), IdPage);
					_cocoon_application_diag(oProbeDiag);
				}
			}
			return lpDispatch;
		}
		else
		{
			CString oDiag;
			oDiag.Format(_T("fwd_getmodule page=%ld create_module returned null"), IdPage);
			_cocoon_application_diag(oDiag);
			return NULL;
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_getpagehliAUTO(const VARIANT FAR& roVariant)
{
	ALL_TRY
	{
		//"rozpakuj" Variant do hyperlink'a
		CSmartOleVariant oSOV(roVariant);
		SCP<CHyperLinkInfo> poOpeningHLISP;
		switch (oSOV.Type())
		{
		case VT_BSTR:
			poOpeningHLISP = ReadHLIFromString(CString(oSOV.GetBStr()));
		break;
		case VT_DISPATCH:
			poOpeningHLISP = CHyperLinkInfo::FromIDispatch(oSOV.GetDispatch());
		break;
		case (VT_VARIANT | VT_BYREF):
		{
			VARIANT * pVariant = oSOV.GetVariantRef().pvarVal;
			ASSERT(pVariant);
			return fwd_getpagehliAUTO(*pVariant);	//wo³amy siebie, ale ju¿ bef VT_BYREF
		}
		break;
		default:
			ASSERT(false);
		}

		//utwórz stronê
		ASSERT(poOpeningHLISP.PointsObject());
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<cndoc_page__> poPageSP = m_poIntegratorSP->create_page(poOpeningHLISP);
		if (poPageSP.PointsObject())
		{
			return poPageSP->GetDispatch(true);
		}
		else
		{
			return NULL;
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_PushPageAUTO(LPDISPATCH pPageDispatch)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<cndoc_navopage> poNavoPageSP = cndoc_navopage::FromIDispatch(pPageDispatch);
		if (poNavoPageSP.PointsNull())
		{
			//to_do: error: page object required
			ASSERT(false);
			CString oString("push: z³y wskaŸnik lub przekazany przez page_");
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
		}
		ASSERT(m_poIntegratorSP->_is_any_stack());
		ASSERT(poNavoPageSP->get_stack() != NULL);
		//wrzucaj zawsze na stos przypisany stronie
		poNavoPageSP->get_stack()->push(NewSCP<cndoc_page__>(poNavoPageSP.Get(),true));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_PopPageAUTO()
{
	ALL_TRY
	{
		m_poIntegratorSP->pop_active_page();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_GetTopPageAUTO()
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			if (m_poIntegratorSP->_is_any_stack())
			{
				ASSERT(!m_poIntegratorSP->_get_active_stack()->is_empty());
				return m_poIntegratorSP->_get_active_stack()->get_top_page()->GetDispatch(true);
			}
		}
		return NULL;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


LPDISPATCH cndoc_application::fwd_GetAFC_AUTO()
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<IDispatch> poAFCDispatchSP = m_poIntegratorSP->get_AFC();
		return poAFCDispatchSP.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_GetNX_AUTO()
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<IDispatch> poNXDispatchSP = m_poIntegratorSP->get_NX();
		return poNXDispatchSP.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
LPDISPATCH cndoc_application::fwd_GetNXMNet_AUTO()
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		SCP<IDispatch> poNXMNetDispatchSP = m_poIntegratorSP->get_NXMNet();
		return poNXMNetDispatchSP.Detach();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
void cndoc_application::fwd_SetArenaBackColorAUTO(long nArenaBackColor)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		m_poIntegratorSP->set_main_arena_backcolor(nArenaBackColor);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_GetUserInfoAUTO(long iter, VARIANT FAR* pvarUserName, VARIANT FAR* pvarComputerName)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return m_poIntegratorSP->netuser_getinfo(iter,pvarUserName,pvarComputerName);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_NotifyUserAUTO(long nUserCookie, long nEventCode, const VARIANT FAR& varValue)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		m_poIntegratorSP->netuser_notify(nUserCookie,nEventCode,varValue);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_GetUserCookieAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return m_poIntegratorSP->netuser_getcookie();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_SetUserPropertyAUTO(long nUserCookie, long nProp, const VARIANT FAR& varValue)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		m_poIntegratorSP->netuser_setprop(nUserCookie,nProp,varValue);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL cndoc_application::fwd_GetUserPropertyAUTO(long nUserCookie, long nProp, VARIANT FAR * pvarValue)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return m_poIntegratorSP->netuser_getprop(nUserCookie,nProp,pvarValue);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL cndoc_application::fwd_CreateCountedResourceAUTO(LPCTSTR lpResName, long nMaxUsage)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return (m_poIntegratorSP->fwd_create_counted_resource(lpResName,nMaxUsage) != false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL cndoc_application::fwd_DeleteCountedResourceAUTO(LPCTSTR lpResName)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return (m_poIntegratorSP->fwd_delete_counted_resource(lpResName) != false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_UseCountedResourceAUTO(LPCTSTR lpResName)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return m_poIntegratorSP->fwd_use_counted_resource(lpResName);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_GetUsageCountedResourceAUTO(LPCTSTR lpResName)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		return m_poIntegratorSP->fwd_get_usage_counted_resource(lpResName);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_ReleaseCountedResourceAUTO(LPCTSTR lpResName)
{
	ALL_TRY
	{
		ASSERT(m_poIntegratorSP.PointsObject());
		m_poIntegratorSP->fwd_release_counted_resource(lpResName);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL cndoc_application::IsCommandEnabledAUTO(long nCmd)
{
	ALL_TRY
	{
		return is_command_enabled(nCmd) != false;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_application::CreateStreamObjectAUTO()
{
	ALL_TRY
	{
		SCP<CStreamAutoObject> poStreamAutoObjectSP = NewSCP(new CStreamAutoObject());
		poStreamAutoObjectSP->Attach(CreateTempFileStream());
		return poStreamAutoObjectSP->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void cndoc_application::BringWindowToTopAUTO()
{
	ALL_TRY
	{
		if (get_main_window() != NULL)
		{
			//Uwaga! W Win32 nie uzywamy BringWindowToTop() 
			//tylko SetForegroundWindow
			get_main_window()->SetForegroundWindow();
			if (get_main_window()->IsIconic())
			{
				get_main_window()->ShowWindow(SW_RESTORE);
			}
			get_main_window()->BringWindowToTop();
			get_main_window()->UpdateWindow();
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::SetShellTrayStateAUTO(long nState, BOOL bFlash, LPCTSTR lpTip)
{
	ALL_TRY
	{
		if (get_main_window() != NULL)
		{
			get_main_window()->set_shell_tray_state(eShellTrayState(nState));
			get_main_window()->set_shell_tray_flash(bFlash != FALSE);
			get_main_window()->set_shell_tray_tip(ng_string(lpTip));
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_application::CreateSystemObjectAUTO()
{
	ALL_TRY
	{
		return NewSCP(new CSystemAutoObject())->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::SetMenuAUTO(const VARIANT FAR& varMenu)
{
	ALL_TRY
	{
		ASSERT(m_poMainWindow);

		CSmartOleVariant oMenuSOV(varMenu);
		switch (oMenuSOV.Type())
		{
		case VT_I4:
			_create_menu_on_xml_file(oMenuSOV.GetLong());
		break;
		case VT_BSTR:
		case VT_UNKNOWN:
		case VT_DISPATCH:
		{
			SCP<IStream> poInputStreamSP = OpenFileStream_Read_On_SOV(oMenuSOV);
			{
				CStreamHolder(poInputStreamSP).SeekToBegin();
			}
			_create_menu_on_stream(poInputStreamSP);
		}
		break;
		default:
			ASSERT(false);
		}
		m_poMainWindow->DrawMenuBar();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_application::GetCurrentMenuTreeAUTO()
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = _get_current_menu_tree_automation_object();
		if (poDispatchSP.PointsObject())
		{
			return poDispatchSP.Detach();
		}
		else
		{
			return NULL;
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cndoc_application::fwd_GetMenuChangedFlagAUTO()
{
	ALL_TRY
	{
		return (_get_menu_changed_flag() != false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_SetMenuChangedFlagAUTO(BOOL bChanged)
{
	ALL_TRY
	{
		_set_menu_changed_flag(bChanged != FALSE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH cndoc_application::CreateHLIAUTO()
{
	ALL_TRY
	{
		return NewSCP(new CHyperLinkInfo())->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::CreateHLIOnStringAUTO(LPCTSTR lpHyperLinkString)
{
	ALL_TRY
	{
		return ReadHLIFromString(CString(lpHyperLinkString))->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


void cndoc_application::SetTimerAUTO(long nTimerId, const VARIANT FAR& rvarHLI, long nInterval)
{
	ALL_TRY
	{
		ASSERT(BLINKINGINTERVAL != 0);

		if (nInterval == 0)	//remove timer
		{
			m_oTimerMap.RemoveKey(nTimerId);
		}
		else	//setup timer
		{
			SCP<CProgrammableTimer> poProgTimerSP = NewSCP(new CProgrammableTimer());
			poProgTimerSP->m_nTimerInterval = (nInterval * 1000) / BLINKINGINTERVAL;
			poProgTimerSP->m_nTimerCountDown = poProgTimerSP->m_nTimerInterval;
			CSmartOleVariant oSOV(rvarHLI);
			poProgTimerSP->m_poHLISP = ReadHLIFromString(CString(oSOV.GetBStr()));
			m_oTimerMap[nTimerId] = poProgTimerSP;
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPUNKNOWN cndoc_application::fwd_GetNewEnumAUTO()
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			return m_poIntegratorSP->get_new_enum_AUTO();
		}
		ASSERT(false);
		return NULL;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
};

void cndoc_application::fwd_SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","document");
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_application::fwd_GetZoomAUTO()
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			//ned_to_do: return m_poMainWindow->get_zoom();
			return 100;
		}
		else
		{
			return 100;
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_SetZoomAUTO(long nNewZoom)
{
	ALL_TRY
	{
		if (m_poMainWindow != NULL)
		{
			//ned_to_do:	m_poMainWindow->set_zoom(nNewZoom);
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_GetToolbarAUTO()
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			if (m_poIntegratorSP->get_toolbar_stack().PointsObject())
			{
				return m_poIntegratorSP->get_toolbar_stack()->get_top_page()->GetDispatch(true);
			}
		}
		return NULL;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_application::fwd_GetOutlookbarAUTO()
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			if (m_poIntegratorSP->get_outlookbar_stack().PointsObject())
			{
				return m_poIntegratorSP->get_outlookbar_stack()->get_top_page()->GetDispatch(true);
			}
		}
		return NULL;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::fwd_ShowHideOutlookBarAUTO(BOOL bShow)
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			if (bShow)
			{
				m_poIntegratorSP->_initialize_outlookbar();
			}
			else
			{
				m_poIntegratorSP->_uninitialize_outlookbar();
			}
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_ShowHideToolBarAUTO(BOOL bShow)
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			if (bShow)
			{
				m_poIntegratorSP->_initialize_toolbar();
			}
			else
			{
				m_poIntegratorSP->_uninitialize_toolbar();
			}
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_application::CreatePerformingObjectAUTO(LPCTSTR lpText)
{
	ALL_TRY
	{
		return NewSCP(new CPerformingDialogHolder(lpText))->GetIDispatch(TRUE);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_PurgeLocalCachesAUTO()
{
	ALL_TRY
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,GetSupportRegistryKeyName(),
			_T("PurgeLocalCache"),_T("Y"));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_PutControlDataAUTO(long idControl, LPCTSTR lpDataString)
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			m_poIntegratorSP->put_control_data_action(idControl,lpDataString);
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_PutControlCommandAUTO(long idControl, long nVerb, const VARIANT FAR& roVarValue)
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(roVarValue);
		if (oSOV.Type() == (VT_VARIANT | VT_BYREF))
		{
			fwd_PutControlCommandAUTO(idControl,nVerb,*oSOV.GetVariantRef().pvarVal);
		}
		else
		{
			if (m_poIntegratorSP.PointsObject())
			{
				m_poIntegratorSP->put_control_cmd_action(idControl,nVerb,roVarValue);
			}
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::ApplyControlDataAUTO()
{
	ALL_TRY
	{
		ASSERT(CMD_INTERNAL_APPLYCTRLDATA == 9007);
		__fwd_PostCommandString("vn1001=9007",false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_application::WaitIdleAUTO()
{
	ALL_TRY
	{
		wait_idle();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_application::fwd_SetCurrentStyleAUTO(const VARIANT FAR& rvarStyle)
{
	ALL_TRY
	{
		if (m_poIntegratorSP.PointsObject())
		{
			m_poIntegratorSP->set_current_style(reinterpret_cast<const CSmartOleVariant &>(rvarStyle));
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void ParseXMLAUTO(SCP<IDispatch> poSinkObjectDispatchSP, SCP<IStream> poInputStreamSP);

void cndoc_application::ParseXML_AUTO(LPDISPATCH pSinkObject, const VARIANT FAR& rvarStream)
{
	ALL_TRY
	{
		CSmartOleVariant oStreamSOV(rvarStream);
		SCP<IDispatch> poSinkObjectDispatchSP = NewSCP(pSinkObject,true);
		ParseXMLAUTO(poSinkObjectDispatchSP,OpenFileStream_Read_On_SOV(oStreamSOV));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cndoc_application::fwd_BackupAUTO(LPCTSTR lpSAUser, LPCTSTR lpPwd, LPCTSTR lpArchivePwd, const VARIANT FAR& rvarStream)
{
	ALL_TRY
	{
		CSmartOleVariant oStreamSOV(rvarStream);
		SCP<CFileRemover> poFileRemoverSP;
		bool bResult = m_poIntegratorSP->backup(lpSAUser,lpPwd,lpArchivePwd,CreateFileStream_Write_On_SOV(oStreamSOV,poFileRemoverSP));
		if (poFileRemoverSP.PointsObject() && bResult)
		{
			poFileRemoverSP->DontRemove();
		}
		return (bResult != false);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cndoc_application::fwd_RestoreAUTO(LPCTSTR lpSAUser, LPCTSTR lpPwd, LPCTSTR lpArchivePwd, const VARIANT FAR& rvarStream)
{
	ALL_TRY
	{
		CSmartOleVariant oStreamSOV(rvarStream);
		return m_poIntegratorSP->restore(lpSAUser,lpPwd,lpArchivePwd,OpenFileStream_Read_On_SOV(oStreamSOV));
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

#ifdef PULL_ERROR_MESSAGES
long cndoc_application::GetNewMessageFlagAUTO()
{
	return m_nNewErrorMessageLevel;
}

void cndoc_application::ClearNewMessageFlagAUTO()
{
	m_nNewErrorMessageLevel = 0;
}

BOOL cndoc_application::GetNewMessageAUTO(VARIANT FAR * pvaridMsg, VARIANT FAR* pvaridHelp, VARIANT FAR* pvarDescription)
{
	ALL_TRY
	{
		CNavoExceptionAccessor oNEA(GetErrorStorage());
		if (oNEA.ErrorInfoArray().GetSize() > 0)
		{
			CSmartOleVariant oErrorCodeSOV((long)oNEA.ErrorInfoArray()[0].GetErroCode(),VT_I4);
			CSmartOleVariant oHelpIdSOV((long)oNEA.ErrorInfoArray()[0].GetHelpId(),VT_I4);
			CSmartOleVariant oErrorStringSOV(oNEA.ErrorInfoArray()[0].GetErrorString());

			*pvaridMsg = oErrorCodeSOV.Detach();
			*pvaridHelp = oHelpIdSOV.Detach();
			*pvarDescription = oErrorStringSOV.Detach();

			oNEA.ErrorInfoArray().RemoveAt(0);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

#endif

void cndoc_application::MessageSink_AUTO(LPDISPATCH pSinkObject)
{
	ALL_TRY
	{
		m_poMessageSinkDispatchSP = NewSCP(pSinkObject,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}