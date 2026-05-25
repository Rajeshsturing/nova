/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display automation wrappers (NEDAW)
	
	nedaw element definition

*/

#ifndef _ELEMENT_NEDAW_H_
#define _ELEMENT_NEDAW_H_

#include "..\navopx\navopx.h"

namespace ned
{
	class cned_element;
	class cned_static;
	class cned_picture;
	class cned_edit__;
	class cned_textedit;
	class cned_curredit;
	class cned_staticex;
	class cned_multiedit;
	class cned_olecontrol;
}

namespace nedaw
{

class cnedaw_element : public CCmdTargetInterface
{
public:
	cnedaw_element(SCP<ned::cned_element> poInternalSP);

	static SCP<cnedaw_element> FromIDispatch(LPDISPATCH lpDispatch);
	ned::cned_element * _get_element();
	//{{AFX_DISPATCH(cnedaw_element)
	afx_msg long GetIdentAUTO();
	afx_msg void SetIdentAUTO(long nNewValue);
	afx_msg BOOL GetDisableAUTO();
	afx_msg void SetDisableAUTO(BOOL bNewValue);
	afx_msg BOOL GetHideAUTO();
	afx_msg void SetHideAUTO(BOOL bNewValue);
	afx_msg BOOL GetReadonlyAUTO();
	afx_msg void SetReadonlyAUTO(BOOL bNewValue);
	afx_msg long GetBackcolorAUTO();
	afx_msg void SetBackcolorAUTO(long nNewValue);
	afx_msg long GetBackcolor2AUTO();
	afx_msg void SetBackcolor2AUTO(long nNewValue);
	afx_msg long GetForecolorAUTO();
	afx_msg void SetForecolorAUTO(long nNewValue);
	afx_msg BOOL GetFocusAUTO();
	afx_msg void SetFocusAUTO(BOOL bNewValue);
	afx_msg long GetFontAUTO();
	afx_msg void SetFontAUTO(long nNewValue);
	afx_msg long GetStyleItemAUTO();
	afx_msg void SetStyleItemAUTO(long nNewValue);
	afx_msg LPDISPATCH GetUserPropAUTO();
	afx_msg void SetUserPropAUTO(LPDISPATCH newValue);
	afx_msg long GetBorderColorAUTO();
	afx_msg void SetBorderColorAUTO(long nNewValue);
	afx_msg long GetBorderTypeAUTO();
	afx_msg void SetBorderTypeAUTO(long nNewValue);
	afx_msg long GetBorderWidthAUTO();
	afx_msg void SetBorderWidthAUTO(long nNewValue);
	afx_msg long GetWidthAUTO();
	afx_msg void SetWidthAUTO(long nNewValue);
	afx_msg long GetHeightAUTO();
	afx_msg void SetHeightAUTO(long nNewValue);
	afx_msg long GetTypeAUTO();
	afx_msg LPDISPATCH GetContainerAUTO();
	afx_msg VARIANT GetValueAUTO();
	afx_msg void SetValueAUTO(const VARIANT FAR& newValue);
	afx_msg void SetIgnoreSysDisableAUTO(BOOL bNewValue);
	afx_msg void SetCustomRedirectAUTO(long nRedirectToElementId);
	afx_msg long GetCustomRedirectAUTO();
	afx_msg void CopyToAUTO(LPDISPATCH pDestElementDispatch);
	afx_msg BSTR GetTipAUTO();
	afx_msg void SetTipAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetFontBoldAUTO();
	afx_msg void SetFontBoldAUTO(BOOL bNewValue);
	afx_msg BOOL GetFontItalicAUTO();
	afx_msg void SetFontItalicAUTO(BOOL bNewValue);
	afx_msg BOOL GetFontStrikeAUTO();
	afx_msg void SetFontStrikeAUTO(BOOL bNewValue);
	afx_msg BOOL GetFontUnderAUTO();
	afx_msg void SetFontUnderAUTO(BOOL bNewValue);
	afx_msg long GetFontSizeAUTO();
	afx_msg void SetFontSizeAUTO(long nNewValue);
	afx_msg BSTR GetFontNameAUTO();
	afx_msg void SetFontNameAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetFontCharSetAUTO();
	afx_msg void SetFontCharSetAUTO(long nNewValue);
	afx_msg long GetAlignmentAUTO();
	afx_msg void SetAlignmentAUTO(long nNewValue);
	afx_msg void SetPositionAsStringAUTO(LPCTSTR lpPositionString);
	afx_msg BSTR GetShortKeyAUTO();
	afx_msg void SetShortKeyAUTO(LPCTSTR lpszNewValue);
	afx_msg LPDISPATCH GetPrevElementAUTO();
	afx_msg LPDISPATCH GetNextElementAUTO();
	afx_msg LPDISPATCH GetTransferAUTO();
	afx_msg void SetTransferAUTO(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(NUIElement,INUIElement)
		STDMETHOD_(long,get_ident)();
		STDMETHOD_(boolean,get_disable)();
		STDMETHOD_(void,set_disable)(boolean bDisable);
		STDMETHOD_(boolean,get_hide)();
		STDMETHOD_(void,set_hide)(boolean bHide);
		STDMETHOD_(long,get_backcolor)();
		STDMETHOD_(void,set_backcolor)(long nBackColor);
		STDMETHOD_(long,get_backcolor2)();
		STDMETHOD_(void,set_backcolor2)(long nBackColor2);
		STDMETHOD_(long,get_forecolor)();
		STDMETHOD_(void,set_forecolor)(long nForeColor);
		STDMETHOD_(boolean,get_focus)();
		STDMETHOD_(void,set_focus)(boolean bFocus);
		STDMETHOD_(INUIContainer * ,get_container)();
	END_INTERFACE_PART(NUIElement)
private:
	void _realize_current_font_bold(bool bBold);
	void _realize_current_font_italic(bool bItalic);
	void _realize_current_font_strike(bool bStrikeThrough);
	void _realize_current_font_under(bool bUnderline);
	void _realize_current_font_size(long nSize);
	void _realize_current_font_name(const ng_string & roFontName);
	void _realize_current_font_charset(SHORT sCharSet);


	virtual void OnFinalRelease();

	SCP<ned::cned_element> m_poInternalSP;
};

//-----------------------------------------------------------
// static
//-----------------------------------------------------------

class cnedaw_static : public cnedaw_element
{
public:
	cnedaw_static(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_static)
	afx_msg BSTR GetTextAUTO();
	afx_msg void SetTextAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetSizeAUTO();
	afx_msg void SetSizeAUTO(long nNewValue);
	afx_msg LPDISPATCH GetHyperLinkAUTO();
	afx_msg void SetHyperLinkAUTO(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_static * _get_static();
	
	ned::cned_static * m_poStatic;
};

//-----------------------------------------------------------
// picture
//-----------------------------------------------------------

class cnedaw_picture : public cnedaw_element
{
public:
	cnedaw_picture(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_picture)
	afx_msg VARIANT GetImageSrcAUTO();
	afx_msg void SetImageSrcAUTO(const VARIANT FAR & newValue);
	afx_msg LPDISPATCH GetHyperLinkAUTO();
	afx_msg void SetHyperLinkAUTO(LPDISPATCH newValue);
	afx_msg void SetAnimateAUTO(long nInterval);
	afx_msg long GetAnimateAUTO();
	afx_msg long GetScalingModeAUTO();
	afx_msg void SetScalingModeAUTO(long nScalingMode);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_picture * _get_picture();
	
	ned::cned_picture * m_poPicture;
};

//-----------------------------------------------------------
// edit (base class)
//-----------------------------------------------------------
class cnedaw_edit__ : public cnedaw_element
{
public:
	cnedaw_edit__(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_edit__)
	afx_msg long GetSizeAUTO();
	afx_msg void SetSizeAUTO(long nNewValue);
	afx_msg BOOL GetValidAUTO();
	afx_msg void SetValidAUTO(BOOL bNewValue);
	afx_msg LPDISPATCH GetSuggestionAUTO();
	afx_msg void SetSuggestionAUTO(LPDISPATCH newValue);
	afx_msg void SelectToEndAUTO();
	afx_msg void MoveCaretToAUTO(long nNewCarePos,BOOL bWithSel);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_edit__ * _get_edit();
	
	ned::cned_edit__ * m_poEdit;
};

//-----------------------------------------------------------
// text edit
//-----------------------------------------------------------
class cnedaw_textedit : public cnedaw_edit__
{
public:
	cnedaw_textedit(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_textedit)
	afx_msg BSTR GetTextAUTO();
	afx_msg void SetTextAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetPasswordAUTO();
	afx_msg void SetPasswordAUTO(BOOL bNewValue);
	afx_msg BOOL GetClearOnlyAUTO();
	afx_msg void SetClearOnlyAUTO(BOOL bNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_textedit * _get_textedit();
	
	ned::cned_textedit * m_poTextEdit;
};
//-----------------------------------------------------------
// currency edit
//-----------------------------------------------------------
class cnedaw_curr_edit : public cnedaw_edit__
{
public:
	cnedaw_curr_edit(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_curr_edit)
	afx_msg long GetPrecisionAUTO();
	afx_msg void SetPrecisionAUTO(long nNewValue);
	afx_msg BSTR GetUnitAUTO();
	afx_msg void SetUnitAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetNegativecolorAUTO();
	afx_msg void SetNegativecolorAUTO(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_curredit * _get_curr_edit();
	
	ned::cned_curredit * m_poCurrEdit;
};


//-----------------------------------------------------------
// static ex
//-----------------------------------------------------------
class cnedaw_staticex : public cnedaw_element
{
public:
	cnedaw_staticex(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_staticex)
	afx_msg BSTR GetTextAUTO();
	afx_msg void SetTextAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetSizeAUTO();
	afx_msg void SetSizeAUTO(long nNewValue);
	afx_msg LPDISPATCH GetHyperLinkAUTO();
	afx_msg void SetHyperLinkAUTO(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_staticex * _get_static_ex();
	
	ned::cned_staticex * m_poStaticEx;
};

//-----------------------------------------------------------
// multiedit
//-----------------------------------------------------------
class cnedaw_multiedit : public cnedaw_element
{
public:
	cnedaw_multiedit(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_multiedit)
	afx_msg BOOL GetValidAUTO();
	afx_msg void SetValidAUTO(BOOL bNewValue);
	afx_msg BOOL GetUseEnterAUTO();
	afx_msg void SetUseEnterAUTO(BOOL bNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_multiedit * _get_multi_edit();
	
	ned::cned_multiedit * m_poMultiEdit;
};

//-----------------------------------------------------------
// olecontrol
//-----------------------------------------------------------
class cnedaw_olecontrol : public cnedaw_element
{
public:
	cnedaw_olecontrol(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_olecontrol)
	afx_msg LPDISPATCH getolecontrolAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

protected:
	ned::cned_olecontrol * _get_ole_control();
	
	ned::cned_olecontrol * m_poOleControl;
};

}


#else
	#error __FILE__ already included
#endif
