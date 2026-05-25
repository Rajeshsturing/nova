/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_*_parser
		parsery ró¿nych ned_elementów (prostych)


*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"
#include "..\include\errorstorage.h"		//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navogal\ngal_iface.h"

#include "..\navoui\common_ned_inc.h"		//common includes
#include "..\navoui\extern_ned.h"
#include "..\navoui\static_ned.h"			
#include "..\navoui\multiline_helper_ned.h"
#include "..\navoui\staticex_ned.h"			
#include "..\navoui\edit_ned.h"			
#include "..\navoui\edit_ned_inl.h"
#include "..\navoui\textedit_ned.h"			
#include "..\navoui\intedit_ned.h"			
#include "..\navoui\curredit_ned.h"			
#include "..\navoui\scroll_helper_ned.h"
#include "..\navoui\multi_ned.h"			
#include "..\navoui\picture_ned.h"
#include "..\navoui\win32_ned.h"
#include "..\navoui\olecontrol_ned.h"
#include "..\navoui\web_ned.h"
#include "..\navoui\group_helper_ned.h"
#include "..\navoui\paragraph_ned.h"
#include "..\navoui\page_caption_ned.h"
#include "..\navoui\page_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "base_xui.h"
#include "element_xui.h"
#include "attrib_xui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR * pcAttribCharCount		= _T("size");
static const TCHAR * pcAttribAnimate		= _T("animate");
static const TCHAR * pcAttribPrec			= _T("precision");
static const TCHAR * pcAttribUnit			= _T("unit");
static const TCHAR * pcAttribNegativeColor	= _T("negativecolor");
static const TCHAR * pcTokenProgId			= _T("progid");
static const TCHAR * pcTokenCLSID			= _T("clsid");
static const TCHAR * pcAttribPassword		= _T("password");
static const TCHAR * pcAttribClearOnly		= _T("clearonly");
static const TCHAR * pcAttribUseEnter		= _T("useenter");
static const TCHAR * pcAttribScalingMode	= _T("scalingmode");

void cxmlui_static_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);
	long nCharCount;
	SCP<cned_static> poStaticSP = scp_cast_ui<cned_static>(get_uielement());
	if(translate_attrib_long(roAttribArray,pcAttribCharCount,nCharCount))
	{
		poStaticSP->set_prop_charwidth(nCharCount);
	}
	SCP<CHyperLinkInfo> poCommandHLISP;
	if(translate_attrib_href(roAttribArray,poCommandHLISP))
	{
		poStaticSP->set_prop_hyperlink(poCommandHLISP);
	}
}

void cxmlui_static_parser::data(LPCTSTR lpData)
{
	ng_string oTextString;
	normalize_data_string(lpData,oTextString);
	scp_cast_ui<cned_static>(get_uielement())->set_prop_text(oTextString);
}

void cxmlui_staticex_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);
	long nCharCount;
	SCP<cned_staticex> poStaticExSP = scp_cast_ui<cned_staticex>(get_uielement());
	if(translate_attrib_long(roAttribArray,pcAttribCharCount,nCharCount))
	{
		poStaticExSP->set_prop_charwidth(nCharCount);
	}
	SCP<CHyperLinkInfo> poCommandHLISP;
	if(translate_attrib_href(roAttribArray,poCommandHLISP))
	{
		poStaticExSP->set_prop_hyperlink(poCommandHLISP);
	}
}

void cxmlui_staticex_parser::data(LPCTSTR lpData)
{
	ng_string oTextString;
	trim_data_string(lpData,oTextString);

	scp_cast_ui<cned_staticex>(get_uielement())->set_prop_text(oTextString);
}

void cxmlui_edit__parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);
	long nCharCount;
	if(translate_attrib_long(roAttribArray,pcAttribCharCount,nCharCount))
	{
		scp_cast_ui<cned_edit__>(get_uielement())->set_prop_charwidth(nCharCount);
	}
}

void cxmlui_edit__parser::data(LPCTSTR lpData)
{
	ng_string oTextString;
	trim_data_string(lpData,oTextString);
	scp_cast_ui<cned_edit__>(get_uielement())->paste_from_string(oTextString);
}


void cxmlui_textedit_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_edit__parser::attributes(roAttribArray);
	bool bPassword;
	if(translate_attrib_boolean(roAttribArray,pcAttribPassword,bPassword))
	{
		scp_cast_ui<cned_textedit>(get_uielement())->set_prop_password(bPassword);
	}
	bool bClearOnly;
	if(translate_attrib_boolean(roAttribArray,pcAttribClearOnly,bClearOnly))
	{
		scp_cast_ui<cned_textedit>(get_uielement())->set_prop_clearonly(bClearOnly);
	}
}

void cxmlui_currency_edit_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_edit__parser::attributes(roAttribArray);
	
	SCP<cned_curredit> poCurrencyEditSP = scp_cast_ui<cned_curredit>(get_uielement());
	long nPrecision;
	if(translate_attrib_long(roAttribArray,pcAttribPrec,nPrecision))
	{
		poCurrencyEditSP->set_prop_precision(nPrecision);
	}
	
	ng_string oUnitString;
	if(roAttribArray.Lookup(pcAttribUnit,oUnitString))
	{
		poCurrencyEditSP->set_prop_unit(oUnitString);
	}

	ng_color oNegativeColor;
	if(translate_attrib_color(roAttribArray,pcAttribNegativeColor,oNegativeColor))
	{
		poCurrencyEditSP->set_prop_negative_text_color(oNegativeColor);
	}
}

void cxmlui_picture_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);
	CSmartOleVariant oSOV;
	SCP<cned_picture> poPictureSP = scp_cast_ui<cned_picture>(get_uielement());
	if(translate_attrib_image(roAttribArray,oSOV))
	{
		poPictureSP->set_prop_imagesrc(oSOV);
	}
	long nAnimateInterval;
	if(translate_attrib_long(roAttribArray,pcAttribAnimate,nAnimateInterval))
	{
		poPictureSP->set_prop_animate(nAnimateInterval);
	}
	long nScalingMode;
	if(translate_attrib_long(roAttribArray,pcAttribScalingMode,nScalingMode))
	{
		ASSERT(nScalingMode == 1 || nScalingMode == 2);
		poPictureSP->set_prop_scaling_mode(nScalingMode);
	}
	SCP<CHyperLinkInfo> poCommandHLISP;
	if(translate_attrib_href(roAttribArray,poCommandHLISP))
	{
		poPictureSP->set_prop_hyperlink(poCommandHLISP);
	}
}

void cxmlui_picture_parser::data(LPCTSTR lpData)
{
	ng_string oTextString;
	normalize_data_string(lpData,oTextString);
	scp_cast_ui<cned_picture>(get_uielement())->set_prop_tooltip_text(oTextString);
}


void cxmlui_web_parser::data(LPCTSTR lpData)
{
	ng_string oURLString;
	normalize_data_string(lpData,oURLString);
	scp_cast_ui<cned_web>(get_uielement())->set_prop_url(CSmartOleVariant(oURLString));
}


void cxmlui_olecontrol_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);

	if(!roAttribArray.IsEmpty())
	{
		SCP<cned_olecontrol> poOleControlSP = scp_cast_ui<cned_olecontrol>(get_uielement());
		ng_string oProgIdString;
		CLSID oCLSID;
		if(roAttribArray.Lookup(pcTokenProgId,oProgIdString))
		{
			//OS_API_CALL
			HRESULT hr = ::CLSIDFromProgID(CBStr(oProgIdString),&oCLSID);
			if(hr == S_OK)
			{
				poOleControlSP->set_prop_clsid(oCLSID);
			}
		}
		else
		{
			if(roAttribArray.Lookup(pcTokenCLSID,oProgIdString))
			{
				//OS_API_CALL
				HRESULT hr = ::CLSIDFromString((LPOLESTR)(LPCWSTR)CBStr(oProgIdString),&oCLSID);
				if(hr == S_OK)
				{
					poOleControlSP->set_prop_clsid(oCLSID);
				}
			}
		}
	}
}

void cxmlui_multi_rich_edit_parser::data(LPCTSTR lpData)
{
	ng_string oTextString;
	trim_data_string(lpData,oTextString);
	scp_cast_ui<cned_multiedit>(get_uielement())->set_prop_text(oTextString);
}

void cxmlui_multi_rich_edit_parser::attributes(const CMapStringToString & roAttribArray)
{
	cxmlui_element_parser__::attributes(roAttribArray);
	
	if(!roAttribArray.IsEmpty())
	{
		bool bUseEnter;
		if(translate_attrib_boolean(roAttribArray,pcAttribUseEnter,bUseEnter))
		{
			scp_cast_ui<cned_multiedit>(get_uielement())->set_prop_use_enter(bUseEnter);
		}
	}
}
