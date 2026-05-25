/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	element definition

*/

#include "stdafx.h"
#include "element_nedaw.h"
#include "style_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEVELOPER_EDITION_
bool ned::_debug_bDrawResized_as_red = false;
#endif

//------------------- construction, destruction -------------------------

cned_element::cned_element(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	m_poManager(poManager),
	m_idThis(idThis),
	m_idRedirectEvents(NEDID_NOTHING),
	m_inxDeclAttrib(NED_DECLATTR_ALL_DEFAULT),
	m_bVSE_Dirty(true)
{
	ASSERT(m_idThis != NEDID_NOTHING);
	ASSERT(poManager);

	_mini_info()._set_type(eType);
}

cned_element::~cned_element()
{
}

void cned_element::OnFinalRelease()
{
	ASSERT(get_manager());
	get_manager()->on_element_finalrelease(this);
}

void cned_element::_set_container(SCP<cned_container> & rpoContainerSP)
{
	m_poContainerSP = rpoContainerSP;

	ned_ident idContainer = m_poContainerSP.PointsObject() ? rpoContainerSP->get_ident() : NEDID_NOTHING;
	_mini_info().set_container_ident(idContainer);
}

void cned_element::_resolve_container() const
{
	ASSERT(m_poContainerSP.PointsNull());
	ASSERT(get_manager());

	ned_ident idContainer = _mini_info().get_container_ident();
	if(idContainer == NEDID_NOTHING)
	{
		return;
	}
	
	(const_cast<cned_element*>(this))->m_poContainerSP = 
		scp_cast_ui<cned_container>(get_element_on_ident(idContainer));
}

//----------------------------------------------------------------------------------
void cned_element::_vse_dirty()
{
	m_bVSE_Dirty = true;
	get_manager()->set_modified_flag();
}

//----------------------------------------------------------------------------------
//------ property GET --------------------------------------------------------------

void cned_element::get_prop_help_text(ng_string & roText) const
{
	get_manager()->get_help_text(get_ident(),roText);
}

void cned_element::get_prop_tooltip_text(ng_string & roText) const
{
	get_manager()->get_tooltip_text(get_ident(),roText);
}

bool cned_element::get_prop_disabled() const
{
	return _mini_info().is_internal_disabled() ||
		(get_manager()->is_sys_disable() && !_mini_info().is_internal_ignore_sys_dis());
}

bool cned_element::get_prop_focus() const
{
	return (get_manager()->get_focus_element() == get_ident());
}

void cned_element::get_prop_value(CSmartOleVariant & /*roSOV*/)
{
	ThrowNavoException2(ERCO_UIELEM_GETPROP_NOT_EXISTS, IDPAGE_NOTAVAILABLE, PROPC_VARIANT, long(get_ident()));
}

//------ property SET -----------------
void cned_element::set_prop_hidden(bool bWillBeHidden)
{
	if(get_prop_hidden() == bWillBeHidden)
	{
		return;
	}
	
	_mini_info().set_hidden(bWillBeHidden);

	
	if(bWillBeHidden)	//ukrywamy
	{
		_invalidate_all_paint();
	}

	if(!is_measure_pending() || !bWillBeHidden)	//jeœli prawid³owy OR by³ ukryty (a bêdzie widoczny)
	{
		set_measure_pending();	//zaznacz ¿e z³y

		SCP<cned_container> poContainerSP = get_container();
		if(poContainerSP.PointsObject())
		{
			poContainerSP->on_child_size_info_dirty(get_ident());
		}
	}

	ASSERT(is_measure_pending());
	_vse_dirty();
}

void cned_element::set_prop_disabled(bool bDisabled)
{
	if(_mini_info().is_internal_disabled() == bDisabled)
	{
		return;
	}

	_mini_info().set_internal_disabled(bDisabled);
	
	if(get_prop_focus() && get_prop_disabled())
	{
		//skoro jesteœmy disabled - usuñ focus z nas
		get_manager()->_mark_new_focus_element(NEDID_NOTHING);
	}

	_invalidate_all_paint();
	_vse_dirty();
}

void cned_element::set_prop_declattrib(const ned_declattributes & roDeclAttributes,bool bSizeDirty)
{
	ned_declattrinx nDeclAttrInx = roDeclAttributes.is_declared(NEDA_ALL) ? 
		get_manager()->get_inx_for_declattr(roDeclAttributes) : NED_DECLATTR_ALL_DEFAULT;
	
	if(m_inxDeclAttrib == nDeclAttrInx)
	{
		return;
	}
	m_inxDeclAttrib = nDeclAttrInx;
	
	if(bSizeDirty)
	{
		_size_info_dirty();
	}
	_vse_dirty();
}

void cned_element::set_prop_tooltip_text(const ng_string & roToolTipText)
{
	get_manager()->set_tooltip_text(get_ident(),roToolTipText);
	_vse_dirty();
}

void cned_element::set_prop_help_text(const ng_string & roHelpText)
{
	get_manager()->set_help_text(get_ident(),roHelpText);
	_vse_dirty();
}

void cned_element::set_prop_value(const CSmartOleVariant & /*roSOV*/)
{
	ThrowNavoException2(ERCO_UIELEM_SETPROP_NOT_ALLOWED,IDPAGE_NOTAVAILABLE, PROPC_VARIANT, long(get_ident()));
}

//-------------- short key support -------------- -------------- 
void cned_element::set_shortkey(SCP<cnui_shortkey> & rpoShortKeySP)
{
	get_manager()->set_shortkey(get_ident(),rpoShortKeySP);
}

SCP<cnui_shortkey> cned_element::get_shortkey()
{
	return get_manager()->get_shortkey(get_ident());
}

//----------------------------------------------------------------------------------
void cned_element::_set_focus_to_me()
{
	ASSERT(!get_prop_hidden());
	ASSERT(!get_prop_disabled());

	if(get_prop_focus())
	{
		return;
	}

	if(get_manager()->can_element_accept_focus(get_ident()))
	{
		get_manager()->_mark_new_focus_element(get_ident());
	}
}

//----------------------------------------------------------------------------------
//-------------- attribute functions -------------------------
//----------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------


static bool apply_font_spec(ned_font_spec & roDestFontSpec,const ned_font_spec & roSrcFontSpec,
							ned_attribute_type eValidMask)
{
	ASSERT(eValidMask & NEDA_FONT_ALL);
	bool bAnyChange = false;

	if(eValidMask & NEDA_FONTNAME)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_oFontNameString != roSrcFontSpec.m_oFontNameString);
		roDestFontSpec.m_oFontNameString = roSrcFontSpec.m_oFontNameString;
	}
	if(eValidMask & NEDA_FONTSIZE)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_nSize != roSrcFontSpec.m_nSize);
		roDestFontSpec.m_nSize = roSrcFontSpec.m_nSize;
	}
	if(eValidMask & NEDA_FONTBOLD)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_bBold != roSrcFontSpec.m_bBold);
		roDestFontSpec.m_bBold = roSrcFontSpec.m_bBold;
	}
	if(eValidMask & NEDA_FONTITALIC)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_bItalic != roSrcFontSpec.m_bItalic);
		roDestFontSpec.m_bItalic = roSrcFontSpec.m_bItalic;
	}
	if(eValidMask & NEDA_FONTSTRIKE)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_bStrikeThrough != roSrcFontSpec.m_bStrikeThrough);
		roDestFontSpec.m_bStrikeThrough = roSrcFontSpec.m_bStrikeThrough;
	}
	if(eValidMask & NEDA_FONTUNDER)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_bUnderLine != roSrcFontSpec.m_bUnderLine);
		roDestFontSpec.m_bUnderLine = roSrcFontSpec.m_bUnderLine;
	}
	if(eValidMask & NEDA_FONTCHARSET)
	{
		bAnyChange = bAnyChange | (roDestFontSpec.m_sCharSet != roSrcFontSpec.m_sCharSet);
		roDestFontSpec.m_sCharSet = roSrcFontSpec.m_sCharSet;
	}
	
	return bAnyChange;
}

/*
	kolejnoœæ ustawiania atrybutów (od najni¿szego priorytetu do najwy¿szego):
	1. dziedziczenie z parenta
	2. atrybut fixed (predefiniowane przez kontrolkê)
	3. jeœli jest styl to ze stylu
	4. zadeklarowane specyficznie dla kontrolki
*/

void cned_element::apply_attributes(const ned_currattributes & roCurrAttrib)
{
	//1. dziedziczenie z parenta
	m_oCurrAttrib.inherit_from_parent(roCurrAttrib);

	//2. ustawianie wbudowanych
	set_fixed_properties();

	const ned_declattributes & roDeclAttrib = get_manager()->get_declattr_on_inx(get_prop_declattrib_inx());
	
	//fonty id¹ równolegle
	ned_font_spec oFontSpec(get_manager()->get_font_spec_on_inx(get_prop_fontinx()));
	bool bStyleFontChange = false;
	bool bDeclFontChange = false;

	//3. w pierwszej kolejnoœcu style = template
	if(roDeclAttrib.is_declared(NEDA_STYLEITEM))
	{
		//dziedziczenie ze stylu
		//u¿yj konkretnego stylu lub weŸ bie¿¹cy
		long StyleId = roDeclAttrib.is_declared(NEDA_STYLE) ? roDeclAttrib.get_styleid() : STYLE_ID_CURRENT;
		long StyleItemId = roDeclAttrib.get_styleitemid();
		ASSERT(STYLE_ITEM_NULL != StyleItemId);
		cned_styleitem * poStyleItem = get_manager()->get_style(StyleId)->get_item(StyleItemId);
		if(poStyleItem != NULL)
		{
			if(poStyleItem->is_declared(NEDA_ALL))
			{
				m_oCurrAttrib.inherit_from(*poStyleItem);
				
				ned_attribute_type eStyleFontMask;
				const ned_font_spec & roStyleFontSpec = poStyleItem->get_fontspec(eStyleFontMask);
				if(eStyleFontMask != NEDA_NONE)
				{
					bStyleFontChange = apply_font_spec(oFontSpec,roStyleFontSpec,eStyleFontMask);
				}
				if(poStyleItem->is_declared(NEDA_PRINTABLE))
				{
					set_prop_printable(poStyleItem->get_printable());
				}
			}
		}
	}

	//4. potem atrybuty zadeklarowane specyficznie dla elementu
	if(roDeclAttrib.is_declared((ned_attribute_type)(NEDA_ALL & (~NEDA_STYLEITEM))))
	{
		m_oCurrAttrib.inherit_from(roDeclAttrib);

		ned_attribute_type eDeclFontMask;
		const ned_font_spec & roDeclFontSpec = roDeclAttrib.get_fontspec(eDeclFontMask);
		if(eDeclFontMask != NEDA_NONE)
		{
			bDeclFontChange = apply_font_spec(oFontSpec,roDeclFontSpec,eDeclFontMask);
		}
		if(roDeclAttrib.is_declared(NEDA_PRINTABLE))
		{
			set_prop_printable(roDeclAttrib.get_printable());
		}
	}

	if(bDeclFontChange || bStyleFontChange)
	{
		set_prop_fontinx(get_manager()->get_inx_for_font_spec(oFontSpec));
	}

	ASSERT(get_manager()->get_inx_for_font_spec(oFontSpec) == get_prop_fontinx());
}

void ned_currattributes::inherit_from(const ned_declattributes & roDeclAttributes)
{
	ASSERT(roDeclAttributes.is_declared((ned_attribute_type)(NEDA_ALL & (~NEDA_STYLEITEM))));

	if(roDeclAttributes.is_declared(NEDA_FORECOLOR))
	{
		m_nForeColor = roDeclAttributes.get_forecolor();
	}
	if(roDeclAttributes.is_declared(NEDA_BACKCOLOR))
	{
		m_nBackColor = roDeclAttributes.get_backcolor();
	}
	if(roDeclAttributes.is_declared(NEDA_BACKCOLOR2))
	{
		m_nBackColor2 = roDeclAttributes.get_backcolor2();
	}
	if(roDeclAttributes.is_declared(NEDA_BORDERSTYLE))
	{
		m_oBorder.m_eBorderStyle = roDeclAttributes.get_border_style();
	}
	if(roDeclAttributes.is_declared(NEDA_BORDERCOLOR))
	{
		m_oBorder.m_clrBorderColor = roDeclAttributes.get_border_color();
	}
	if(roDeclAttributes.is_declared(NEDA_BORDERWIDTH))
	{
		m_oBorder.m_nBorderPxWidth = roDeclAttributes.get_border_width();
	}
	if(roDeclAttributes.is_declared(NEDA_ALIGNMENT))
	{
		m_eAlignment = roDeclAttributes.get_alignment();
	}
}

void cned_element::set_style_item(long StyleItemId)
{
	//update declared attributes

	const ned_declattributes & roOldDeclAttrib = get_manager()->get_declattr_on_inx(get_prop_declattrib_inx());
	if(roOldDeclAttrib.is_declared(NEDA_STYLEITEM))
	{
		if(roOldDeclAttrib.get_styleitemid() == StyleItemId)
		{
			return;
		}
	}

	ned_declattributes oNewDeclAttrib(roOldDeclAttrib);
	oNewDeclAttrib.decl_styleitemid(StyleItemId);
	set_prop_declattrib(oNewDeclAttrib,true);
	SCP<cned_container> poContainerSP = get_container();
	cned_element::apply_attributes(poContainerSP.PointsObject() ? 
		poContainerSP->get_current_attributes() : get_current_attributes());
	_size_info_dirty();
}

void cned_element::set_decl_position(const ned_position & roPosition)
{
	get_manager()->set_decl_position(get_ident(),roPosition);
}

bool cned_element::get_decl_position(ned_position & roPosition) const
{
	return get_manager()->get_decl_position(get_ident(),roPosition);
}

//--------------------------------------------------------------------------------------
SCP<CHyperLinkInfo> ned::init_control_command_hli(ned_ident idDestElement,eStdControlCommandVerb eVerb)
{
	ASSERT(idDestElement != NEDID_NOTHING);
	SCP<CHyperLinkInfo> poVerbHLISP = NewSCP(new CHyperLinkInfo());
	poVerbHLISP->SetNumProp(GVAR_CMD,CMD_CONTROL);
	poVerbHLISP->SetNumProp(PROPC_IDENT,long(idDestElement));
	poVerbHLISP->SetNumProp(GVAR_CONTROL_VERB_INTERNAL,long(eVerb));
	return poVerbHLISP;
}

//--------------------------------------------------------------------------------------
//---------- drawing helpers ----------------
//--------------------------------------------------------------------------------------
void cned_element::_draw_std_frame(cned_fore_painter & roForePainter,const ng_rect & roFrameRect)
{
	if(get_prop_border_type() != NED_BORDER_STYLE_NONE)
	{
		long nFramePxWidth = get_manager()->__zoomize(get_prop_border_width());
		if(nFramePxWidth > 0)
		{
			roForePainter.frame_rect(roFrameRect,nFramePxWidth,
				get_prop_border_color(),border_style_to_frame_mask(get_prop_border_type(),NG_FRAME_ALL));
		}
	}
}

void cned_element::_draw_std_background(cned_back_painter & roBackPainter,const ng_rect & roBackRect)
{
	if(!roBackPainter.get_paint_param().paint_background())
	{
		return;
	}
	if(get_prop_backcolor() != Transparent && get_prop_backcolor2() != Transparent)
	{
		roBackPainter.fill_rect_hg(roBackRect,get_prop_backcolor(),get_prop_backcolor2());
	}
}


void cned_element::_store_main_paint_rect(const ng_rect & roRect)
{
	get_manager()->store_paint_rect(get_ident(),MAIN_PAINT_RECT_ID,roRect);
}

void cned_element::_store_extra_paint_rect(long nExtraId,const ng_rect & roRect)
{
	get_manager()->store_paint_rect(get_ident(),nExtraId,roRect);
}

bool cned_element::_get_main_paint_rect(ng_rect & roRect)
{
	return get_manager()->get_paint_rect(get_ident(),MAIN_PAINT_RECT_ID,roRect);
}

bool cned_element::_get_extra_paint_rect(long nExtraId,ng_rect & roRect)
{
	return get_manager()->get_paint_rect(get_ident(),nExtraId,roRect);
}

//--------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void cned_element::_size_info_dirty()
{
	if(!is_measure_pending())	//tylko jeœli prawid³owy
	{
		set_measure_pending();	//zaznacz ¿e z³y

		if(!get_prop_hidden())	//tylko jeœli jest widoczny
		{
			SCP<cned_container> poContainerSP = get_container();
			if(poContainerSP.PointsObject())
			{
				poContainerSP->on_child_size_info_dirty(get_ident());
			}
		}
	}

	ASSERT(is_measure_pending());
}
//--------------------------------------------------------------------------

void cned_element::fill_clone(cned_element * poDestination)
{
	ASSERT(poDestination != NULL);
	ASSERT(poDestination->get_type() == get_type()
		|| (poDestination->get_type() == ned_tablerow && get_type() == ned_patterntablerow));
	
	poDestination->m_idRedirectEvents = m_idRedirectEvents;
	
	//to jest bezpieczne w ramach tej samej areny (managery stron mog¹ byæ ró¿ne)
	poDestination->m_oCurrAttrib = m_oCurrAttrib;
	
	//patch dla m_nFontIndex; przy ró¿nych managerach
	if(poDestination->get_manager() != get_manager())
	{
		const ned_font_spec & roFontSpec = get_manager()->get_font_spec_on_inx(get_prop_fontinx());
		const ned_fontinx nFontInx = poDestination->get_manager()->get_inx_for_font_spec(roFontSpec);
		poDestination->m_oCurrAttrib.set_fontinx(nFontInx);
	}

	if(m_poUserPropertiesSP.PointsObject())
	{
		poDestination->m_poUserPropertiesSP = NewSCP(new CHyperLinkInfo(*m_poUserPropertiesSP));
	}

	//to jest bezpieczne w ramach tej samej areny (managery stron mog¹ byæ ró¿ne)
	poDestination->m_inxDeclAttrib = m_inxDeclAttrib;

	_mini_info().fill_clone(poDestination->_mini_info());

	SCP<nui_transfer> poTransferSP = get_manager()->get_transfer(get_ident());
	if(poTransferSP.PointsObject())
	{
		poDestination->get_manager()->set_transfer(poDestination->get_ident(),poTransferSP);
	}
	//copy tooltip
	ng_string oTipString;
	get_prop_tooltip_text(oTipString);
	if(!oTipString.IsEmpty())
	{
		poDestination->set_prop_tooltip_text(oTipString);
	}

//  ned_to_do: 
//  info: patrz na u¿ycia
//  przy tworzeniu nowych i tak bêdzie dirty
//  przy kopiowaniu starych raczej nie ma takiej potrzeby
//  ewentualnie mo¿na dodaæ nowy parametr (zaznaczaj / nie zaznaczaj dirty)

//	poDestination->_size_info_dirty();

	poDestination->_vse_dirty();
}

//--------------------------------------------------------------------------------------
// rect_element
//--------------------------------------------------------------------------------------

void cned_rect_element_::_invalidate_all_paint()
{	
	get_manager()->invalidate_paint_rect(get_ident(),MAIN_PAINT_RECT_ID);
}

void cned_rect_element_::post_render(cned_post_render_manager & roPostRender,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oNewRect(oPaintPoint,m_oActualSize);
	ng_rect oOldRect;

	_get_main_paint_rect(oOldRect);
	
	if(oOldRect != oNewRect)
	{
		cned_rect_element_::_invalidate_all_paint();
		get_manager()->invalidate_paint_rect(oNewRect);
	}
}


//--------------------------------------------------------
void cned_rect_element_::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);
	ng_rect oElementRect(oPaintPoint,m_oActualSize);

	if(oElementRect.get_top() > roSplitInfo.get_max_bottom())
	{
		//next page -> finish current
		roSplitInfo.next_y_page();
	}
	else
	{
		//jesli wystaje -> zostanie przeniesiony na nast.strone
		//cofnij actual bottom

		if(oElementRect.get_bottom() > roSplitInfo.get_max_bottom())
		{
			if(oElementRect.get_top() < roSplitInfo.get_actual_bottom())
			{
				roSplitInfo.update_actual_bottom(oElementRect.get_top());
			}
		}
	}
	
	roSplitInfo.update_max_right(oElementRect.get_right());
}

//--------------------------------------------------------------------------------------
// automation 
//--------------------------------------------------------------------------------------
SCP<nedaw::cnedaw_element> cned_element::get_my_nedaw()
{
	return get_nedaw(get_ident());
}

SCP<nedaw::cnedaw_element> cned_element::get_nedaw(ned_ident idElement)
{
	return get_manager()->get_nedaw(idElement);
}

//--------------------------------------------------------------------------------------
bool cned_painter_::is_effectively_disabled(const cned_element * poElement) const
{
	ASSERT(poElement != NULL);
	const ned_element_mini_info & roMiniInfo = poElement->_mini_info();
	if(roMiniInfo.is_internal_disabled())
	{
		return true;
	}

	if(!roMiniInfo.is_internal_ignore_sys_dis())
	{
		if(m_nTreeDisableCount != 0)
		{
			return true;
		}

		if(poElement->get_manager()->is_sys_disable())
		{
			return true;
		}
	}
	
	return false;
}
