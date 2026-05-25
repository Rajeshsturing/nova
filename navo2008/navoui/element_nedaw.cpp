/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display automation wrappers (NEDAW)
	
	element definition

*/

#include "stdafx.h"
#include "element_nedaw.h"
#include "static_ned.h"
#include "picture_ned.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"
#include "textedit_ned.h"
#include "curredit_ned.h"
#include "multiline_helper_ned.h"
#include "staticex_ned.h"
#include "scroll_helper_ned.h"
#include "multi_ned.h"
#include "win32_ned.h"
#include "olecontrol_ned.h"
#include "transfer_nedaw.h"

using namespace nedaw;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//--------------------------------------------------------------------------------

SCP<cnedaw_transfer> cnedaw_transfer::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTarget = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTarget);
	cnedaw_transfer * poNEDAWTransfer = static_cast<cnedaw_transfer*>(poCmdTarget);
	ASSERT(poNEDAWTransfer);
	return NewSCP(poNEDAWTransfer,true);
}
cnedaw_transfer::cnedaw_transfer(SCP<nui_transfer> poTransferSP) :
	m_poTransferSP(poTransferSP)
{
	ASSERT(m_poTransferSP.PointsObject());
	EnableAutomation();
}

cnedaw_transfer::~cnedaw_transfer()
{
}

//--------------------------------------------------------------------------------

cnedaw_element::cnedaw_element(SCP<ned::cned_element> poInternalSP) :
	m_poInternalSP(poInternalSP)
{
	ASSERT(m_poInternalSP.PointsObject());
	EnableAutomation();
}

void cnedaw_element::OnFinalRelease()
{
	_get_element()->get_manager()->on_nedaw_final_release(_get_element()->get_ident(),this);
}

SCP<cnedaw_element> cnedaw_element::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTarget = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTarget);
	cnedaw_element * poUIElement = static_cast<cnedaw_element*>(poCmdTarget);
	ASSERT(poUIElement);
	return NewSCP(poUIElement,true);
}

inline ned::cned_element * cnedaw_element::_get_element()
{
	ASSERT(m_poInternalSP.PointsObject());
	return m_poInternalSP.Get();
}

void cnedaw_element::_realize_current_font_bold(bool bNewBold)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_bBold != bNewBold)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_bBold = bNewBold;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_italic(bool bNewItalic)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_bItalic != bNewItalic)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_bItalic = bNewItalic;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_strike(bool bNewStrikeThrough)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_bStrikeThrough != bNewStrikeThrough)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_bStrikeThrough = bNewStrikeThrough;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_under(bool bNewUnderline)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_bUnderLine != bNewUnderline)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_bUnderLine = bNewUnderline;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_size(long nNewSize)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_nSize != nNewSize)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_nSize = nNewSize;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_name(const ng_string & roNewFontNameString)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_oFontNameString.CompareNoCase(roNewFontNameString) != 0)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_oFontNameString = roNewFontNameString;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

void cnedaw_element::_realize_current_font_charset(SHORT sCharSet)
{
	const ned::ned_font_spec & roCurrentFontSpec = _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx());
	if(roCurrentFontSpec.m_sCharSet != sCharSet)
	{
		ned::ned_font_spec oNewFontSpec(roCurrentFontSpec);
		oNewFontSpec.m_sCharSet = sCharSet;
		_get_element()->set_prop_fontinx(_get_element()->get_manager()->get_inx_for_font_spec(oNewFontSpec));
	}
}

//{{AFX_MSG_MAP(cnedaw_element)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(cnedaw_element, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(cnedaw_element)
	DISP_PROPERTY_EX(cnedaw_element, "value", GetValueAUTO, SetValueAUTO, VT_VARIANT)
	DISP_PROPERTY_EX(cnedaw_element, "ident", GetIdentAUTO, SetIdentAUTO, VT_I4)
	DISP_FUNCTION(cnedaw_element, "type", GetTypeAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(cnedaw_element, "parent",  GetContainerAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX(cnedaw_element, "focus", GetFocusAUTO, SetFocusAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "customredirect", GetCustomRedirectAUTO, SetCustomRedirectAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "disable", GetDisableAUTO, SetDisableAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "hide", GetHideAUTO, SetHideAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "backcolor", GetBackcolorAUTO, SetBackcolorAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "backcolor2", GetBackcolor2AUTO, SetBackcolor2AUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "forecolor", GetForecolorAUTO, SetForecolorAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "font", GetFontAUTO, SetFontAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "styleitem", GetStyleItemAUTO, SetStyleItemAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "userprop", GetUserPropAUTO, SetUserPropAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX(cnedaw_element, "bordercolor", GetBorderColorAUTO, SetBorderColorAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "border", GetBorderTypeAUTO, SetBorderTypeAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "borderwidth", GetBorderWidthAUTO, SetBorderWidthAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "align", GetAlignmentAUTO, SetAlignmentAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "width", GetWidthAUTO, SetWidthAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "height", GetHeightAUTO, SetHeightAUTO, VT_I4)
	DISP_FUNCTION(cnedaw_element, "ignoresysdisable", SetIgnoreSysDisableAUTO, VT_EMPTY, VTS_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "readonly", GetReadonlyAUTO, SetReadonlyAUTO, VT_BOOL)
	DISP_FUNCTION(cnedaw_element, "copyto", CopyToAUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_PROPERTY_EX(cnedaw_element, "tip", GetTipAUTO, SetTipAUTO, VT_BSTR)
	DISP_FUNCTION(cnedaw_element, "positionstr", SetPositionAsStringAUTO, VT_EMPTY, VTS_BSTR)
	DISP_PROPERTY_EX(cnedaw_element, "bold", GetFontBoldAUTO, SetFontBoldAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "italic", GetFontItalicAUTO, SetFontItalicAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "strike", GetFontStrikeAUTO, SetFontStrikeAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "underline", GetFontUnderAUTO, SetFontUnderAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_element, "fontsize", GetFontSizeAUTO, SetFontSizeAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "fontname", GetFontNameAUTO, SetFontNameAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_element, "fontcharset", GetFontCharSetAUTO, SetFontCharSetAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_element, "shortkey", GetShortKeyAUTO, SetShortKeyAUTO, VT_BSTR)
	DISP_FUNCTION(cnedaw_element, "prevelement",  GetPrevElementAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_element, "nextelement",  GetNextElementAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX(cnedaw_element, "transfer", GetTransferAUTO, SetTransferAUTO, VT_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL cnedaw_element::GetDisableAUTO() 
{
	ALL_TRY
	{
		return (_get_element()->get_prop_disabled() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cnedaw_element::GetHideAUTO() 
{
	ALL_TRY
	{
		return (_get_element()->get_prop_hidden() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cnedaw_element::GetReadonlyAUTO() 
{
	//ned_to_do:
	return false;
}


long cnedaw_element::GetIdentAUTO() 
{
	return long(_get_element()->get_ident());
}

void cnedaw_element::SetIdentAUTO(long) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_UIELEM_SETPROP_NOT_ALLOWED,IDPAGE_NOTAVAILABLE, PROPC_IDENT, long(_get_element()->get_ident()));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetBackcolorAUTO() 
{
	ALL_TRY
	{
		return _get_element()->get_prop_backcolor().colorref();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetBackcolor2AUTO() 
{
	ALL_TRY
	{
		return _get_element()->get_prop_backcolor2().colorref();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetForecolorAUTO() 
{
	ALL_TRY
	{
		return _get_element()->get_prop_forecolor().colorref();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetBorderColorAUTO()
{
	ALL_TRY
	{
		return(_get_element()->get_prop_border_color().colorref());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetBorderTypeAUTO()
{
	ALL_TRY
	{
		return long(_get_element()->get_prop_border_type());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetBorderWidthAUTO()
{
	ALL_TRY
	{
		return _get_element()->get_prop_border_width();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetFontAUTO() 
{
	ALL_TRY
	{
		return long(_get_element()->get_prop_fontinx());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetAlignmentAUTO()
{
	ALL_TRY
	{
		return long(_get_element()->get_prop_alignment());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetWidthAUTO() 
{
	ALL_TRY
	{
		return _get_element()->get_prop_extwidth();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetHeightAUTO() 
{
	ALL_TRY
	{
		return _get_element()->get_prop_extheight();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetStyleItemAUTO()
{
	const ned::ned_declattributes & roDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
	if(roDeclAttrib.is_declared(NEDA_STYLEITEM))
	{
		return roDeclAttrib.get_styleitemid();
	}
	return STYLE_ITEM_NULL;
}

BOOL cnedaw_element::GetFocusAUTO() 
{
	ALL_TRY
	{
		return (_get_element()->get_prop_focus() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


long cnedaw_element::GetTypeAUTO() 
{
	return long(_get_element()->get_type());
}


VARIANT cnedaw_element::GetValueAUTO() 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		_get_element()->get_prop_value(oSOV);
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


LPDISPATCH cnedaw_element::GetContainerAUTO()
{
	ALL_TRY
	{
		SCP<ned::cned_container> poContainerSP = _get_element()->get_container();
		if(poContainerSP.PointsObject())
		{
			return poContainerSP->get_my_nedaw()->GetDispatch(true);
		}
		else
		{
			//tylko top page mo¿e nie mieæ kontenera
			ASSERT(ned_toplevelpage == _get_element()->get_type());
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_element::GetPrevElementAUTO()
{
	ALL_TRY
	{
		ned_ident idPrevElement = _get_element()->get_prev_element_ident();
		if(idPrevElement != NEDID_NOTHING)
		{
			SCP<ned::cned_element> poPrevElementSP = _get_element()->get_element_on_ident(idPrevElement);
			return poPrevElementSP->get_my_nedaw()->GetDispatch(true);
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

LPDISPATCH cnedaw_element::GetNextElementAUTO()
{
	ALL_TRY
	{
		ned_ident idNextElement = _get_element()->get_next_element_ident();
		if(idNextElement != NEDID_NOTHING)
		{
			SCP<ned::cned_element> poNextElementSP = _get_element()->get_element_on_ident(idNextElement);
			return poNextElementSP->get_my_nedaw()->GetDispatch(true);
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


LPDISPATCH cnedaw_element::GetUserPropAUTO()
{
	ALL_TRY
	{
		if(_get_element()->get_prop_userprop().PointsObject())
		{
			return _get_element()->get_prop_userprop()->GetDispatch(true);
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

LPDISPATCH cnedaw_element::GetTransferAUTO()
{
	ALL_TRY
	{
		SCP<nui_transfer> poTransferSP = 
			_get_element()->get_manager()->get_transfer(_get_element()->get_ident());

		if(poTransferSP.PointsObject())
		{
			SCP<cnedaw_transfer> poNEDAWTransferSP = NewSCP(new cnedaw_transfer(poTransferSP),false);
			return poNEDAWTransferSP->GetDispatch(true);
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


void cnedaw_element::SetPositionAsStringAUTO(LPCTSTR lpPositionString)
{
	ALL_TRY
	{
		ng_string oPosString(lpPositionString);
		oPosString.TrimLeft();
		oPosString.TrimRight();
		if(oPosString.IsEmpty())
		{
			return;
		}
		
		ned_position oPosition;
		oPosition.from_string(oPosString);
		_get_element()->set_decl_position(oPosition);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetCustomRedirectAUTO()
{
	ALL_TRY
	{
		return _get_element()->get_prop_redirect();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::CopyToAUTO(LPDISPATCH pDestElementDispatch)
{
	ALL_TRY
	{
		SCP<cnedaw_element> poDestElementSP = cnedaw_element::FromIDispatch(pDestElementDispatch);
		ASSERT(poDestElementSP.PointsObject());
		ASSERT(poDestElementSP->_get_element() != NULL);

		_get_element()->fill_clone(poDestElementSP->_get_element());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR cnedaw_element::GetTipAUTO()
{
	ALL_TRY
	{
		ng_string oString;
		_get_element()->get_prop_tooltip_text(oString);
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR cnedaw_element::GetShortKeyAUTO()
{
	ALL_TRY
	{
		return _get_element()->get_shortkey()->GetDescription().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cnedaw_element::GetFontBoldAUTO()
{
	ALL_TRY
	{
		return (_get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_bBold != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cnedaw_element::GetFontItalicAUTO()
{
	ALL_TRY
	{
		return (_get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_bItalic != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cnedaw_element::GetFontUnderAUTO()
{
	ALL_TRY
	{
		return (_get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_bUnderLine != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cnedaw_element::GetFontStrikeAUTO()
{
	ALL_TRY
	{
		return (_get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_bStrikeThrough != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetFontSizeAUTO()
{
	ALL_TRY
	{
		return _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_nSize;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_element::GetFontCharSetAUTO()
{
	ALL_TRY
	{
		return long(_get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_sCharSet);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BSTR cnedaw_element::GetFontNameAUTO()
{
	ALL_TRY
	{
		return _get_element()->get_manager()->get_font_spec_on_inx(_get_element()->get_prop_fontinx()).m_oFontNameString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

void cnedaw_element::SetDisableAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		_get_element()->set_prop_disabled(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetHideAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		_get_element()->set_prop_hidden(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetReadonlyAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		//ned_to_do: przenieœæ do cned_edit__ i wy¿szego poziomu
		//kontrolek - ogólnie to nie ma sensu dla cned_element
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetIgnoreSysDisableAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		_get_element()->set_prop_ignore_sys_disable(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetWidthAUTO(long nWidth) 
{
	ALL_TRY
	{
		_get_element()->set_prop_extwidth(ng_xdist(nWidth));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetHeightAUTO(long nHeight) 
{
	ALL_TRY
	{
		_get_element()->set_prop_extheight(ng_ydist(nHeight));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetBackcolorAUTO(long nNewValue)		
{
	ALL_TRY
	{
		ng_color nColor;
		nColor._access_raw_long() = nNewValue;
		_get_element()->set_prop_backcolor(nColor);
		_get_element()->set_prop_backcolor2(nColor);	//ustawiamy tak¿e backcolor2 (tak samo jak w XML)
		
		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_BACKCOLOR))
		{
			if(roOldDeclAttrib.get_backcolor() == nColor)
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_backcolor(nColor);
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetBackcolor2AUTO(long nNewValue) 
{
	ALL_TRY
	{
		ng_color nColor;
		nColor._access_raw_long() = nNewValue;
		_get_element()->set_prop_backcolor2(nColor);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_BACKCOLOR2))
		{
			if(roOldDeclAttrib.get_backcolor2() == nColor)
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_backcolor2(nColor);
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetForecolorAUTO(long nNewValue) 
{
	ALL_TRY
	{
		ng_color nColor;
		nColor._access_raw_long() = nNewValue;
		_get_element()->set_prop_forecolor(nColor);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_FORECOLOR))
		{
			if(roOldDeclAttrib.get_forecolor() == nColor)
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_forecolor(nColor);
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetBorderColorAUTO(long nNewValue)
{
	ALL_TRY
	{
		ng_color nColor;
		nColor._access_raw_long() = nNewValue;
		_get_element()->set_prop_border_color(nColor);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_BORDERCOLOR))
		{
			if(roOldDeclAttrib.get_border_color() == nColor)
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_border_color(nColor);
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetBorderTypeAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_element()->set_prop_border_type(ened_border_style(nNewValue));

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_BORDERSTYLE))
		{
			if(roOldDeclAttrib.get_border_style() == ened_border_style(nNewValue))
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_border_style(ened_border_style(nNewValue));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//DECL_ATTRIB
void cnedaw_element::SetBorderWidthAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_element()->set_prop_border_width(nNewValue);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_BORDERWIDTH))
		{
			if(roOldDeclAttrib.get_border_width() == nNewValue)
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_border_width(nNewValue);
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetFontAUTO(long nFontInx) 
{
	ALL_TRY
	{
		_get_element()->set_prop_fontinx(ned_fontinx(nFontInx));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetAlignmentAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_element()->set_prop_alignment(ened_alignment(nNewValue));

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		if(roOldDeclAttrib.is_declared(NEDA_ALIGNMENT))
		{
			if(roOldDeclAttrib.get_alignment() == ened_alignment(nNewValue))
			{
				return;
			}
		}
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_alignment(ened_alignment(nNewValue));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//DECL_ATTRIB
void cnedaw_element::SetStyleItemAUTO(long StyleItemId)
{
	ALL_TRY
	{
		_get_element()->set_style_item(StyleItemId);

		ASSERT(GetStyleItemAUTO() == StyleItemId);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetFocusAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		if(bNewValue)
		{
			if(_get_element()->get_prop_focus())
			{
				return;
			}
			if(_get_element()->get_manager()->can_element_accept_focus(_get_element()->get_ident()))
			{
				_get_element()->get_manager()->_mark_new_focus_element(_get_element()->get_ident());
			}
		}
		else
		{
			//usuñ focus
			_get_element()->get_manager()->_mark_new_focus_element(NEDID_NOTHING);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void cnedaw_element::SetValueAUTO(const VARIANT FAR& roNewValue) 
{
	ALL_TRY
	{
		_get_element()->set_prop_value(reinterpret_cast<const CSmartOleVariant &>(roNewValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetUserPropAUTO(LPDISPATCH lpDispatch)
{
	ALL_TRY
	{
		_get_element()->set_prop_userprop(CHyperLinkInfo::FromIDispatch(lpDispatch));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetTransferAUTO(LPDISPATCH lpDispatch)
{
	ALL_TRY
	{
		SCP<nui_transfer> poTransferSP;
		
		if(lpDispatch != NULL)
		{
			SCP<cnedaw_transfer> poNEDAWTransferSP = cnedaw_transfer::FromIDispatch(lpDispatch);
			ASSERT(poNEDAWTransferSP.PointsObject());
		
			poTransferSP = poNEDAWTransferSP->_get_transfer();
			ASSERT(poTransferSP.PointsObject());
		}

		_get_element()->get_manager()->set_transfer(_get_element()->get_ident(),poTransferSP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetCustomRedirectAUTO(long nRedirectToElementId)
{
	ALL_TRY
	{
		_get_element()->set_prop_redirect(ned::ned_ident(nRedirectToElementId));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetTipAUTO(LPCTSTR lpszNewValue)
{
	ALL_TRY
	{
		_get_element()->set_prop_tooltip_text(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_element::SetShortKeyAUTO(LPCTSTR lpszNewValue)
{
	ALL_TRY
	{
		_get_element()->set_shortkey(NewSCP(new cnui_shortkey(lpszNewValue)));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontBoldAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		bool bNewBold = (bNewValue != FALSE);
		//realize new font inx if necessary
		_realize_current_font_bold(bNewBold);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTBOLD))
		{
			if(oFontSpec.m_bBold == bNewBold)
			{
				return;
			}
		}
		oFontSpec.m_bBold = bNewBold;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTBOLD));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontItalicAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		bool bNewItalic = (bNewValue != FALSE);
		//realize new font inx if necessary
		_realize_current_font_italic(bNewItalic);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTITALIC))
		{
			if(oFontSpec.m_bItalic == bNewItalic)
			{
				return;
			}
		}
		oFontSpec.m_bItalic = bNewItalic;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTITALIC));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);

	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontStrikeAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		bool bNewStrike = (bNewValue != FALSE);
		//realize new font inx if necessary
		_realize_current_font_strike(bNewStrike);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTSTRIKE))
		{
			if(oFontSpec.m_bStrikeThrough == bNewStrike)
			{
				return;
			}
		}
		oFontSpec.m_bStrikeThrough = bNewStrike;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTSTRIKE));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);

	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontUnderAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		bool bNewUnder = (bNewValue != FALSE);
		//realize new font inx if necessary
		_realize_current_font_under(bNewUnder);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTUNDER))
		{
			if(oFontSpec.m_bUnderLine == bNewUnder)
			{
				return;
			}
		}
		oFontSpec.m_bUnderLine = bNewUnder;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTUNDER));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontSizeAUTO(long nNewValue)
{
	ALL_TRY
	{
		//realize new font inx if necessary
		_realize_current_font_size(nNewValue);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTSIZE))
		{
			if(oFontSpec.m_nSize == nNewValue)
			{
				return;
			}
		}
		oFontSpec.m_nSize = nNewValue;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTSIZE));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontCharSetAUTO(long nNewValue)
{
	ALL_TRY
	{
		//realize new font inx if necessary
		_realize_current_font_charset(SHORT(nNewValue));

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTCHARSET))
		{
			if(oFontSpec.m_sCharSet == SHORT(nNewValue))
			{
				return;
			}
		}
		oFontSpec.m_sCharSet = SHORT(nNewValue);
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTCHARSET));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//DECL_ATTRIB
void cnedaw_element::SetFontNameAUTO(LPCTSTR lpszNewValue)
{
	ALL_TRY
	{
		//realize new font inx if necessary
		_realize_current_font_name(lpszNewValue);

		//update declared attributes
		const ned::ned_declattributes & roOldDeclAttrib = _get_element()->get_manager()->get_declattr_on_inx(_get_element()->get_prop_declattrib_inx());
		ned::ned_attribute_type eFontMask;
		ned::ned_font_spec oFontSpec = roOldDeclAttrib.get_fontspec(eFontMask);
		if(roOldDeclAttrib.is_declared(NEDA_FONTNAME))
		{
			if(oFontSpec.m_oFontNameString.CompareNoCase(lpszNewValue) == 0)
			{
				return;
			}
		}
		oFontSpec.m_oFontNameString = lpszNewValue;
		ned::ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
		oNewDeclAttrib.decl_fontspec(oFontSpec,(ned::ned_attribute_type)(eFontMask | NEDA_FONTNAME));
		_get_element()->set_prop_declattrib(oNewDeclAttrib,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//---------------------------------------------------------------------------
// static 
//---------------------------------------------------------------------------
cnedaw_static::cnedaw_static(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poStatic = static_cast<ned::cned_static*>(poInternalSP.Get());
}

inline ned::cned_static * cnedaw_static::_get_static()
{
	ASSERT(m_poStatic != NULL);
	return m_poStatic;
}

BEGIN_DISPATCH_MAP(cnedaw_static,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_static)
	DISP_PROPERTY_EX(cnedaw_static, "text", GetTextAUTO, SetTextAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_static, "size", GetSizeAUTO, SetSizeAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_static, "href", GetHyperLinkAUTO, SetHyperLinkAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX(cnedaw_static, "hli", GetHyperLinkAUTO, SetHyperLinkAUTO, VT_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


BSTR cnedaw_static::GetTextAUTO() 
{
	ALL_TRY
	{
		return _get_static()->get_prop_text().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_static::SetTextAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		_get_static()->set_prop_text(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_static::GetSizeAUTO() 
{
	ALL_TRY
	{
		return _get_static()->get_prop_charwidth();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_static::SetSizeAUTO(long nNewValue) 
{
	ALL_TRY
	{
		_get_static()->set_prop_charwidth(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_static::GetHyperLinkAUTO()
{
	ALL_TRY
	{
		if(_get_static()->get_prop_hyperlink().PointsObject())
		{
			return _get_static()->get_prop_hyperlink()->GetDispatch(true);
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

void cnedaw_static::SetHyperLinkAUTO(LPDISPATCH pHLIDispatch)
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poHLISP = CHyperLinkInfo::FromIDispatch(pHLIDispatch);
		_get_static()->set_prop_hyperlink(poHLISP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------
// picture
//-----------------------------------------------------------
cnedaw_picture::cnedaw_picture(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poPicture = static_cast<ned::cned_picture*>(poInternalSP.Get());
}

inline ned::cned_picture * cnedaw_picture::_get_picture()
{
	ASSERT(m_poPicture != NULL);
	return m_poPicture;
}

BEGIN_DISPATCH_MAP(cnedaw_picture,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_picture)
	DISP_PROPERTY_EX(cnedaw_picture, "image", GetImageSrcAUTO, SetImageSrcAUTO, VT_VARIANT)
	DISP_PROPERTY_EX(cnedaw_picture, "hli", GetHyperLinkAUTO, SetHyperLinkAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX(cnedaw_picture, "animate", GetAnimateAUTO, SetAnimateAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_picture, "scalingmode", GetScalingModeAUTO, SetScalingModeAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

VARIANT cnedaw_picture::GetImageSrcAUTO()
{
	ALL_TRY
	{
		CSmartOleVariant oVariant(_get_picture()->get_prop_imagesrc());
		return oVariant.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_picture::SetImageSrcAUTO(const VARIANT FAR & newValue)
{
	ALL_TRY
	{
		_get_picture()->set_prop_imagesrc(reinterpret_cast<const CSmartOleVariant &>(newValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_picture::GetHyperLinkAUTO()
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poHLISP = _get_picture()->get_prop_hyperlink();
		if(poHLISP.PointsObject())
		{
			return poHLISP->GetDispatch(true);
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

void cnedaw_picture::SetHyperLinkAUTO(LPDISPATCH pHLIDispatch)
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poHLISP = CHyperLinkInfo::FromIDispatch(pHLIDispatch);
		_get_picture()->set_prop_hyperlink(poHLISP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_picture::SetAnimateAUTO(long nInterval)
{
	ALL_TRY
	{
		_get_picture()->set_prop_animate(nInterval);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_picture::GetAnimateAUTO()
{
	ALL_TRY
	{
		return _get_picture()->get_prop_animate();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_picture::SetScalingModeAUTO(long nScalingMode)
{
	ALL_TRY
	{
		_get_picture()->set_prop_scaling_mode(nScalingMode);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_picture::GetScalingModeAUTO()
{
	ALL_TRY
	{
		return _get_picture()->get_prop_scaling_mode();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------
// edit (base class)
//-----------------------------------------------------------
cnedaw_edit__::cnedaw_edit__(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poEdit = static_cast<ned::cned_edit__*>(poInternalSP.Get());
}

inline ned::cned_edit__ * cnedaw_edit__::_get_edit()
{
	ASSERT(m_poEdit != NULL);
	return m_poEdit;
}

BEGIN_DISPATCH_MAP(cnedaw_edit__,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_edit__)
	DISP_PROPERTY_EX(cnedaw_edit__, "size", GetSizeAUTO, SetSizeAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_edit__, "valid", GetValidAUTO, SetValidAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_edit__, "suggestion", GetSuggestionAUTO, SetSuggestionAUTO, VT_DISPATCH)
	DISP_FUNCTION(cnedaw_edit__, "selecttoend", SelectToEndAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cnedaw_edit__, "movecaretto", MoveCaretToAUTO, VT_EMPTY, VTS_I4 VTS_BOOL)
	
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cnedaw_edit__::GetSizeAUTO() 
{
	ALL_TRY
	{
		return _get_edit()->get_prop_charwidth();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_edit__::SetSizeAUTO(long nNewValue) 
{
	ALL_TRY
	{
		_get_edit()->set_prop_charwidth(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cnedaw_edit__::GetValidAUTO() 
{
	ALL_TRY
	{
		return (_get_edit()->get_prop_valid() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_edit__::SetValidAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		_get_edit()->set_prop_valid(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_edit__::GetSuggestionAUTO()
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = _get_edit()->get_prop_suggestion();
		return poDispatchSP.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_edit__::SetSuggestionAUTO(LPDISPATCH pNewValue)
{
	ALL_TRY
	{
		_get_edit()->set_prop_suggestion(NewSCP(pNewValue,true));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_edit__::SelectToEndAUTO()
{
	ALL_TRY
	{
		_get_edit()->select_to_end();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_edit__::MoveCaretToAUTO(long nNewCarePos,BOOL bWithSel)
{
	ALL_TRY
	{
		_get_edit()->move_caret_to(nNewCarePos,(bWithSel != FALSE));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------
// text edit
//-----------------------------------------------------------
cnedaw_textedit::cnedaw_textedit(SCP<ned::cned_element> poInternalSP) :
	cnedaw_edit__(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTextEdit = static_cast<ned::cned_textedit*>(poInternalSP.Get());
}

inline ned::cned_textedit * cnedaw_textedit::_get_textedit()
{
	ASSERT(m_poTextEdit != NULL);
	return m_poTextEdit;
}

BEGIN_DISPATCH_MAP(cnedaw_textedit,cnedaw_edit__)
	//{{AFX_DISPATCH_MAP(cnedaw_textedit)
	DISP_PROPERTY_EX(cnedaw_textedit, "text", GetTextAUTO, SetTextAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_textedit, "password", GetPasswordAUTO, SetPasswordAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_textedit, "clearonly", GetClearOnlyAUTO, SetClearOnlyAUTO, VT_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL cnedaw_textedit::GetPasswordAUTO() 
{
	ALL_TRY
	{
		return (_get_textedit()->get_prop_password() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_textedit::SetPasswordAUTO(BOOL bPassword) 
{
	ALL_TRY
	{
		_get_textedit()->set_prop_password(bPassword != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cnedaw_textedit::GetClearOnlyAUTO()
{
	ALL_TRY
	{
		return (_get_textedit()->get_prop_clearonly() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_textedit::SetClearOnlyAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		_get_textedit()->set_prop_clearonly(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
//---- for compatibility with version < 1.3 -----------------
//---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

BSTR cnedaw_textedit::GetTextAUTO()
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		_get_textedit()->get_prop_value(oSOV);
		return CString(oSOV.GetBStr()).AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_textedit::SetTextAUTO(LPCTSTR lpszNewValue)
{
	ALL_TRY
	{
		_get_textedit()->set_prop_value(CSmartOleVariant(lpszNewValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------
// currency edit
//-----------------------------------------------------------
cnedaw_curr_edit::cnedaw_curr_edit(SCP<ned::cned_element> poInternalSP) :
	cnedaw_edit__(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poCurrEdit = static_cast<ned::cned_curredit*>(poInternalSP.Get());
}

inline ned::cned_curredit * cnedaw_curr_edit::_get_curr_edit()
{
	ASSERT(m_poCurrEdit != NULL);
	return m_poCurrEdit;
}

BEGIN_DISPATCH_MAP(cnedaw_curr_edit,cnedaw_edit__)
	//{{AFX_DISPATCH_MAP(cnedaw_curr_edit)
	DISP_PROPERTY_EX(cnedaw_curr_edit, "precision", GetPrecisionAUTO, SetPrecisionAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_curr_edit, "unit", GetUnitAUTO, SetUnitAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_curr_edit, "negativecolor", GetNegativecolorAUTO, SetNegativecolorAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cnedaw_curr_edit::GetPrecisionAUTO() 
{
	ALL_TRY
	{
		return _get_curr_edit()->get_prop_precision();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_curr_edit::SetPrecisionAUTO(long nNewValue) 
{
	ALL_TRY
	{
		_get_curr_edit()->set_prop_precision(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR cnedaw_curr_edit::GetUnitAUTO() 
{
	ALL_TRY
	{
		return _get_curr_edit()->get_prop_unit().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_curr_edit::SetUnitAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		_get_curr_edit()->set_prop_unit(ng_string(lpszNewValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_curr_edit::GetNegativecolorAUTO()
{
	ALL_TRY
	{
		return _get_curr_edit()->get_prop_negative_text_color().colorref();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_curr_edit::SetNegativecolorAUTO(long nNewValue)
{
	ALL_TRY
	{
		ng_color oColor;
		oColor._access_raw_long() = nNewValue;
		_get_curr_edit()->set_prop_negative_text_color(oColor);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------
// static ex
//-----------------------------------------------------------
cnedaw_staticex::cnedaw_staticex(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poStaticEx = static_cast<ned::cned_staticex*>(poInternalSP.Get());
}

inline ned::cned_staticex * cnedaw_staticex::_get_static_ex()
{
	ASSERT(m_poStaticEx != NULL);
	return m_poStaticEx;
}

BEGIN_DISPATCH_MAP(cnedaw_staticex,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_staticex)
	DISP_PROPERTY_EX(cnedaw_staticex, "text", GetTextAUTO, SetTextAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_staticex, "size", GetSizeAUTO, SetSizeAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_staticex, "href", GetHyperLinkAUTO, SetHyperLinkAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX(cnedaw_staticex, "hli", GetHyperLinkAUTO, SetHyperLinkAUTO, VT_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BSTR cnedaw_staticex::GetTextAUTO() 
{
	ALL_TRY
	{
		return _get_static_ex()->get_prop_text().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_staticex::SetTextAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		_get_static_ex()->set_prop_text(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_staticex::GetSizeAUTO() 
{
	ALL_TRY
	{
		return _get_static_ex()->get_prop_charwidth();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_staticex::SetSizeAUTO(long nNewValue) 
{
	ALL_TRY
	{
		_get_static_ex()->set_prop_charwidth(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_staticex::GetHyperLinkAUTO()
{
	ALL_TRY
	{
		if(_get_static_ex()->get_prop_hyperlink().PointsObject())
		{
			return _get_static_ex()->get_prop_hyperlink()->GetDispatch(true);
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

void cnedaw_staticex::SetHyperLinkAUTO(LPDISPATCH pHLIDispatch)
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poHLISP = CHyperLinkInfo::FromIDispatch(pHLIDispatch);
		_get_static_ex()->set_prop_hyperlink(poHLISP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------
// multiedit
//-----------------------------------------------------------
cnedaw_multiedit::cnedaw_multiedit(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poMultiEdit = static_cast<ned::cned_multiedit*>(poInternalSP.Get());
}

inline ned::cned_multiedit * cnedaw_multiedit::_get_multi_edit()
{
	ASSERT(m_poMultiEdit != NULL);
	return m_poMultiEdit;
}

BEGIN_DISPATCH_MAP(cnedaw_multiedit,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_multiedit)
	DISP_PROPERTY_EX(cnedaw_multiedit, "valid", GetValidAUTO, SetValidAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_multiedit, "useenter", GetUseEnterAUTO, SetUseEnterAUTO, VT_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL cnedaw_multiedit::GetValidAUTO() 
{
	ALL_TRY
	{
		return (_get_multi_edit()->get_prop_valid() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_multiedit::SetValidAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		_get_multi_edit()->set_prop_valid(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cnedaw_multiedit::GetUseEnterAUTO() 
{
	ALL_TRY
	{
		return (_get_multi_edit()->get_prop_use_enter() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_multiedit::SetUseEnterAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		_get_multi_edit()->set_prop_use_enter(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------
// olecontrol
//-----------------------------------------------------------

cnedaw_olecontrol::cnedaw_olecontrol(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poOleControl = static_cast<ned::cned_olecontrol*>(poInternalSP.Get());
}

inline ned::cned_olecontrol * cnedaw_olecontrol::_get_ole_control()
{
	ASSERT(m_poOleControl != NULL);
	return m_poOleControl;
}

BEGIN_DISPATCH_MAP(cnedaw_olecontrol,cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_olecontrol)
	DISP_FUNCTION(cnedaw_olecontrol, "olecontrol", getolecontrolAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH cnedaw_olecontrol::getolecontrolAUTO()
{
	ALL_TRY
	{
		return _get_ole_control()->get_olecontrol_dispatch().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
BEGIN_INTERFACE_MAP(cnedaw_element, CCmdTargetInterface)
	INTERFACE_PART(cnedaw_element,IID_INUIElement,NUIElement)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(cnedaw_element, NUIElement)


STDMETHODIMP_(long) cnedaw_element::XNUIElement::get_ident()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return pThis->GetIdentAUTO();
}

STDMETHODIMP_(boolean) cnedaw_element::XNUIElement::get_disable()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return (boolean) pThis->GetDisableAUTO();
}


STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_disable(boolean bDisable)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetDisableAUTO((BOOL) bDisable);
}


STDMETHODIMP_(boolean) cnedaw_element::XNUIElement::get_hide()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return (boolean) pThis->GetHideAUTO();
}


STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_hide(boolean bHide)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetHideAUTO((BOOL) bHide);
}


STDMETHODIMP_(long) cnedaw_element::XNUIElement::get_backcolor()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return pThis->GetBackcolorAUTO();
}


STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_backcolor(long nBackColor)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetBackcolorAUTO(nBackColor);
}


STDMETHODIMP_(long) cnedaw_element::XNUIElement::get_backcolor2()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return pThis->GetBackcolor2AUTO();
}


STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_backcolor2(long nBackColor2)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetBackcolor2AUTO(nBackColor2);
}


STDMETHODIMP_(long) cnedaw_element::XNUIElement::get_forecolor()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return pThis->GetForecolorAUTO();
}


STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_forecolor(long nForeColor)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetForecolorAUTO(nForeColor);
}


STDMETHODIMP_(boolean) cnedaw_element::XNUIElement::get_focus()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	return (boolean) pThis->GetFocusAUTO();
}

STDMETHODIMP_(void) cnedaw_element::XNUIElement::set_focus(boolean bFocus)
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	pThis->SetFocusAUTO((BOOL) bFocus);
}

STDMETHODIMP_(INUIContainer *) cnedaw_element::XNUIElement::get_container()
{
	METHOD_PROLOGUE(cnedaw_element,NUIElement)

	LPDISPATCH pDispatch = pThis->GetContainerAUTO();
	//to_do
	return NULL;
}


