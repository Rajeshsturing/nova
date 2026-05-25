/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	element definition

	inline part
*/

#ifndef _ELEMENT_NED_INL_H_
#define _ELEMENT_NED_INL_H_


namespace ned
{
//---------- rendering helpers ----------------
inline ng_xdist cned_element::_get_std_width_for_rendering(const cned_renderer_ & roRenderer) const
{
	ng_xdist dxWidth = 0;

	if(is_maximal_width_value(get_prop_extwidth()))
	{
		dxWidth = roRenderer.get_current_width();
	}
	else
	{
		if(is_normal_width_value(get_prop_extwidth()))
		{
			dxWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
		}
	}
	
	//min, auto - fall in these case as 'min'
	dxWidth = max(dxWidth,m_oMetrics.get_minimal_width());
	return dxWidth;
}

inline ng_ydist cned_element::_get_std_height_for_rendering(ng_ydist dyHeightForAuto) const
{
	if(is_normal_height_value(get_prop_extheight()))
	{
		ng_ydist dyHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
		return dyHeight;
	}
	else
	{
		return dyHeightForAuto;
	}
}


inline ned_element_mini_info & cned_element::_mini_info()
{
	return m_oMiniInfo;
}

inline const ned_element_mini_info & cned_element::_mini_info() const
{
	return m_oMiniInfo;
}

inline cned_element_manager * cned_element::get_manager() 
{
	ASSERT(m_poManager != NULL);
	return m_poManager;
}

inline const cned_element_manager * cned_element::get_manager() const
{
	ASSERT(m_poManager != NULL);
	return m_poManager;
}

inline const ned_ident cned_element::get_ident() const
{
	return m_idThis;
}

inline const ened_element_type cned_element::get_type() const
{
	return _mini_info().get_type();
}

inline const ned_ident cned_element::get_container_ident() const
{
	ASSERT(_mini_info().get_container_ident() != NEDID_NOTHING);
	
	return _mini_info().get_container_ident();
}

inline const ned_ident cned_element::get_next_element_ident() const
{
	return _mini_info().get_next_element_ident();
}

inline const ned_ident cned_element::get_prev_element_ident() const
{
	return _mini_info().get_prev_element_ident();
}

inline void cned_element::_vse_clean()
{
	m_bVSE_Dirty = false;
}

inline bool cned_element::_is_vse_dirty() const
{
	return m_bVSE_Dirty;
}

inline SCP<cned_container> cned_element::get_container() const
{
	if(m_poContainerSP.PointsNull())
	{
		_resolve_container();
	}
	return (const_cast<cned_element*>(this))->m_poContainerSP;
}

inline void cned_element::__internal_cleanup()
{
	m_poContainerSP = 0;
}

inline void cned_element::_on_remove_element()
{
	_invalidate_all_paint();
	__internal_cleanup();
}

//-------------- rendering support -------------------
inline bool cned_element::is_measure_pending() const
{
	return _mini_info().is_measure_pending();
}

#ifdef _DEVELOPER_EDITION_
extern bool _debug_bDrawResized_as_red;
#endif

inline void cned_element::set_measure_pending()
{
//	TRACE("bad [%d] of type %d\n",get_ident(),long(get_type()));
	_mini_info().set_measure_pending();

#ifdef _DEVELOPER_EDITION_
	if(_debug_bDrawResized_as_red)
	{
		get_manager()->_debug_draw_invalidated_as_red(true);
		_invalidate_all_paint();
		get_manager()->_debug_draw_invalidated_as_red(false);
	}
#endif

}

inline void cned_element::clear_measure_pending()
{
	_mini_info().clear_measure_pending();
}

inline void cned_element::move_by(long /*nElementPart*/,const ng_size & roDistanceSize)
{
	m_oVectorSize = m_oVectorSize + roDistanceSize;
}

//------ property GET -----------------

inline bool cned_element::get_prop_tabstop() const
{
	return _mini_info().is_tabstop();
}

inline bool cned_element::get_prop_hidden() const
{
	return _mini_info().is_hidden();
}

inline bool cned_element::get_prop_ignore_sys_disable() const
{
	return _mini_info().is_internal_ignore_sys_dis();
}

inline bool cned_element::get_prop_printable() const
{
	return _mini_info().is_printable();
}

inline ng_xdist cned_element::get_prop_extwidth() const
{
	return m_oCurrAttrib.get_extwidth();
}

inline ng_ydist cned_element::get_prop_extheight() const
{
	return m_oCurrAttrib.get_extheight();
}

inline ng_color cned_element::get_prop_forecolor() const
{
	return m_oCurrAttrib.get_forecolor();
}

inline ng_color cned_element::get_prop_backcolor() const
{
	return m_oCurrAttrib.get_backcolor();
}

inline ng_color cned_element::get_prop_backcolor2() const
{
	return m_oCurrAttrib.get_backcolor2();
}

inline ned_fontinx cned_element::get_prop_fontinx() const
{
	return m_oCurrAttrib.get_fontinx();
}

inline ned_declattrinx cned_element::get_prop_declattrib_inx() const
{
	return m_inxDeclAttrib;
}

inline ened_border_style cned_element::get_prop_border_type() const
{
	return m_oCurrAttrib.get_border().m_eBorderStyle;
}

inline long cned_element::get_prop_border_width() const
{
	return m_oCurrAttrib.get_border().m_nBorderPxWidth;
}

inline ng_color cned_element::get_prop_border_color() const
{
	return m_oCurrAttrib.get_border().m_clrBorderColor;
}

inline ened_alignment cned_element::get_prop_alignment() const
{
	return m_oCurrAttrib.get_alignment();
}

inline SCP<CHyperLinkInfo> cned_element::get_prop_userprop()
{
	return m_poUserPropertiesSP;
}

inline ned_ident cned_element::get_prop_redirect() const
{
	return m_idRedirectEvents;
}

inline bool cned_element::get_prop_split_allowed() const
{
	return _mini_info().is_split_allowed();
}

//------ property SET -----------------
inline void cned_element::set_prop_redirect(ned_ident idRedirect)
{
	if(get_prop_redirect() == idRedirect)
	{
		return;
	}
	
	m_idRedirectEvents = idRedirect;
	_vse_dirty();
}

inline void cned_element::set_prop_fontinx(ned_fontinx nFontInx)
{
	if(get_prop_fontinx() == nFontInx)
	{
		return;
	}
	m_oCurrAttrib.set_fontinx(nFontInx);

	_size_info_dirty();
	_vse_dirty();
}


inline void cned_element::set_prop_forecolor(ng_color nForeColor)
{
	if(get_prop_forecolor() == nForeColor)
	{
		return;
	}
	m_oCurrAttrib.set_forecolor(nForeColor);

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_element::set_prop_backcolor(ng_color nBackColor)
{
	if(get_prop_backcolor() == nBackColor)
	{
		return;
	}
	m_oCurrAttrib.set_backcolor(nBackColor);

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_element::set_prop_backcolor2(ng_color nBackColor2)
{
	if(get_prop_backcolor2() == nBackColor2)
	{
		return;
	}
	m_oCurrAttrib.set_backcolor2(nBackColor2);

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_element::set_prop_border_type(ened_border_style eStyle)
{
	if(get_prop_border_type() == eStyle)
	{
		return;
	}
	m_oCurrAttrib.get_border().m_eBorderStyle = eStyle;

	_invalidate_all_paint();
	_vse_dirty();
}


inline void cned_element::set_prop_border_width(long nPxWidth)
{
	if(get_prop_border_width() == nPxWidth)
	{
		return;
	}
	m_oCurrAttrib.get_border().m_nBorderPxWidth = nPxWidth;
	
	_size_info_dirty();
	_vse_dirty();
}

inline void cned_element::set_prop_border_color(ng_color nColor)
{
	if(get_prop_border_color() == nColor)
	{
		return;
	}
	m_oCurrAttrib.get_border().m_clrBorderColor = nColor;

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_element::set_prop_tabstop(bool bTabStop)
{
	_mini_info().set_tabstop(bTabStop);
	_vse_dirty();
}

inline void cned_element::set_prop_split_allowed(bool bSplit)
{
	_mini_info().set_split_allowed(bSplit);
	_vse_dirty();
}

inline void cned_element::set_prop_ignore_sys_disable(bool bIgnoreSysDis)
{
	if(get_prop_ignore_sys_disable() == bIgnoreSysDis)
	{
		return;
	}
	_mini_info().set_internal_ignore_sys_dis(bIgnoreSysDis);

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_element::set_prop_extwidth(ng_xdist xWidth)
{
	if(get_prop_extwidth() == xWidth)
	{
		return;
	}
	m_oCurrAttrib.set_extwidth(xWidth);

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_element::set_prop_extheight(ng_ydist yHeight)
{
	if(get_prop_extheight() == yHeight)
	{
		return;
	}
	m_oCurrAttrib.set_extheight(yHeight);

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_element::set_prop_alignment(ened_alignment eAlignment)
{
	if(get_prop_alignment() == eAlignment)
	{
		return;
	}
	m_oCurrAttrib.set_aligment(eAlignment);

	_size_info_dirty();
	_vse_dirty();
}

inline void cned_element::set_prop_printable(bool bPrintable)
{
	if(get_prop_printable() == bPrintable)
	{
		return;
	}
	_mini_info().set_printable(bPrintable);
	
	_vse_dirty();
}

inline void cned_element::set_prop_userprop(SCP<CHyperLinkInfo> & rpoUserPropHLISP)
{
	if(get_prop_userprop().Get() == rpoUserPropHLISP.Get())
	{
		return;
	}
	m_poUserPropertiesSP = rpoUserPropHLISP;

	_vse_dirty();
}

inline void cned_element::set_fixed_properties() 
{
	//noop
}

inline void cned_element::get_opaque_background_area(const ng_point &,ng_area &) const
{
	//noop
}

inline const ned_currattributes & cned_element::get_current_attributes() const
{
	return m_oCurrAttrib;
}

inline void cned_element::draw_foreground(cned_fore_painter &,const ng_point &)
{
	ASSERT(false);
}

inline void cned_element::draw_background(cned_back_painter &,const ng_point &)
{
	ASSERT(false);
}

inline void cned_element::render(cned_renderer_ & /*roRenderer*/)
{
	ASSERT(false);
}

inline bool cned_element::abs_render(cned_absolute_renderer & /*roAbsRenderer*/,
	const ned_position & /*roPosition*/,const ng_point & /*roFlowPoint*/)
{
	ASSERT(false);
	return true;
}

inline void cned_element::post_render(cned_post_render_manager & /*roPostRender*/,const ng_point & /*roCurrentPoint*/)
{
	ASSERT(false);
}

inline bool cned_element::is_inside_hit_area(const ng_point &) const
{
	ASSERT(false);
	return false;
}

//--------------event handlers ---------------------------------------
inline void cned_element::on_event_keydown(const ned_action_kbd &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_mouse_click(const ned_action_mouse &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_mouse_endclick(const ned_action_mouse &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_mouse_over(const ned_action_mouse &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_mouse_wheel(const ned_action_mouse_wheel &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_focus(const ned_action_focus &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_timer(const ned_action_timer &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_olecontrol(const ned_action_oleevent &,ned_action_result &)
{
	//noop
}

inline void cned_element::on_event_command(const ned_action_command &,ned_action_result &)
{
	//noop
}

inline eCursorType cned_element::on_event_set_cursor(const ng_point &)
{
	return ect_default;
}

//--------------- persistency -----------------------------------
inline void cned_element::save(cned_storage_writer & roWriter)
{
	roWriter << m_oVectorSize << m_inxDeclAttrib << m_poUserPropertiesSP << m_idRedirectEvents
		<< m_oMetrics << m_oCurrAttrib;
}

inline void cned_element::load(cned_storage_reader & roReader)
{
	roReader >> m_oVectorSize >> m_inxDeclAttrib >> m_poUserPropertiesSP >> m_idRedirectEvents
		>> m_oMetrics >> m_oCurrAttrib;
}

//-------- page breaking ---------------------------------
inline void cned_element::do_breaks(cpb_manager__ &,const ng_point &)
{
	ASSERT(false);
}

inline void cned_element::update_split_info(const ng_point &,cpb_split_info &)
{
	ASSERT(false);
}

inline void cned_element::make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	//umieszczamy siê na podstawie top-left
	long xAreaX = roSplitManager.find_x_area(oPaintPoint.get_x());
	long yAreaY = roSplitManager.find_y_area(oPaintPoint.get_y());

	_make_clone_split(roSplitManager,xAreaX,yAreaY);
}

inline void cned_element::fill_clone_split(cpb_split_manager & /*roSplitManager*/,long /*xAreaX*/,long /*yAreaY*/,cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	
	ned_position oPosition;
	if(get_decl_position(oPosition))
	{
		//todo: przesuniêcie pozycji wzglêdem pocz¹tku kartki..
		poDestination->set_decl_position(oPosition);
	}
}


inline SCP<cned_element> cned_element::_make_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY)
{
	SCP<cned_element> poClonedElementSP = roSplitManager.get_clone(xAreaX,yAreaY,get_ident());
	if(poClonedElementSP.PointsNull())
	{
		SCP<cned_element> poClonedContainerElementSP = roSplitManager.get_clone(xAreaX,yAreaY,get_container_ident());
		//todo: patch: teraz gdy nie ma kontenera (pomimo ¿e powinien byæ), to wymuszamy sklonowanie go
		if(poClonedContainerElementSP.PointsNull())
		{
			poClonedContainerElementSP = get_container()->_make_clone_split(roSplitManager,xAreaX,yAreaY);
		}
		ASSERT(poClonedContainerElementSP.PointsObject());

		SCP<cned_container> poClonedContainerSP = scp_cast_ui<cned_container>(poClonedContainerElementSP);
		ASSERT(poClonedContainerSP.PointsObject());

		poClonedElementSP = poClonedContainerSP->insert_new_element(get_type(),NEDID_NOTHING,NEDID_LAST);
		
		roSplitManager.register_clone(xAreaX,yAreaY,get_ident(),poClonedElementSP->get_ident());

		fill_clone_split(roSplitManager,xAreaX,yAreaY,poClonedElementSP);
	}
	
	ASSERT(poClonedElementSP.PointsObject());

	return poClonedElementSP;
}


inline void cned_element::fill_clone_for_breaks(cpb_manager__ &,long ,long ,cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	
	ned_position oPosition;
	if(get_decl_position(oPosition))
	{
		poDestination->set_decl_position(oPosition);
	}
}

inline bool cned_element::is_visually_empty() const
{
	return false;
}

//--------------------------------------------------------------------------
inline void cned_element::_arena2local(ng_point & roPoint) const
{
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->_arena2local(roPoint);
	}

	roPoint.offset(-m_oVectorSize);
}

inline void cned_element::_local2arena(ng_point & roPoint) const
{
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->_local2arena(roPoint);
	}

	roPoint.offset(m_oVectorSize);
}

inline void cned_element::_local2arena(ng_rect & roRect) const
{
	ng_point oTopLeftPoint = roRect.get_topleft();
	_local2arena(oTopLeftPoint);
	roRect = ng_rect(oTopLeftPoint,roRect.get_size());
}

inline void cned_element::_screen2local(ng_point & roPoint) const
{
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->_screen2local(roPoint);
	}

	roPoint.offset(-m_oVectorSize);
}

inline void cned_element::_local2screen(ng_point & roPoint) const
{
	SCP<cned_container> poContainerSP = get_container();
	if(poContainerSP.PointsObject())
	{
		poContainerSP->_local2screen(roPoint);
	}

	roPoint.offset(m_oVectorSize);
}

//--------------------------------------------------------------------------
//		cned_rect_element_
//--------------------------------------------------------------------------
inline cned_rect_element_::cned_rect_element_(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_element(poManager,eType,idThis)
{
}

inline void cned_rect_element_::get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics)
{
	ASSERT(!get_prop_hidden());
	if(is_measure_pending())
	{
		m_oMetrics.reset();
		ng_size oMinSize = _compute_min_size(roMParam);
		
		if(is_normal_width_value(get_prop_extwidth()))
		{
			ng_xdist dxWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
			if(dxWidth > oMinSize.get_dx())
			{
				oMinSize.set_dx(dxWidth);
			}
		}

		m_oMetrics.update(oMinSize.get_dx(),oMinSize.get_dy(),oMinSize.get_dx());
		clear_measure_pending();
	}
	roMetrics.update(m_oMetrics);
}

inline void cned_rect_element_::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	ASSERT(!get_prop_hidden());

	roRenderer.ensure_width(m_oMetrics.get_minimal_width());
	ng_size oRequestedSize(_get_std_width_for_rendering(roRenderer),
		_get_std_height_for_rendering(m_oMetrics.get_minimal_height()));
	roRenderer.allocate_rect(get_ident(),-1,oRequestedSize,m_oActualSize,m_oVectorSize);
}

inline bool cned_rect_element_::abs_render(
	cned_absolute_renderer & roAbsRenderer,const ned_position & roPosition,const ng_point & roFlowPoint)
{

	//ned_to_do: na razie: tylko minimalna szerokoœæ i wysokoœc:
	m_oActualSize = ng_size(m_oMetrics.get_minimal_width(),m_oMetrics.get_minimal_height());

	_compute_vector_from_position(get_manager(),roPosition,roAbsRenderer.get_arena_rect(),roFlowPoint,
		m_oActualSize,m_oVectorSize);

	//sprawdzamy czy wyliczony rozmiar mieœci siê w dostêpnym
	//jeœli nie to zg³aszamy potrzebê
	ng_rect oRect(ng_point().offset(m_oVectorSize),m_oActualSize);
	
	bool bResult = true;
	if(oRect.get_right() > roAbsRenderer.get_arena_rect().get_right())
	{
		roAbsRenderer.get_arena_rect().set_right(oRect.get_right());
		bResult = false;
	}

	if(oRect.get_bottom() > roAbsRenderer.get_arena_rect().get_bottom())
	{
		roAbsRenderer.get_arena_rect().set_bottom(oRect.get_bottom());
		bResult = false;
	}

	return bResult;
}

inline ened_spr cned_rect_element_::should_paint(const cned_painter_ & roPainter,const ng_point & roCurrentPoint) const
{
	ng_rect oTestRect(ng_point(roCurrentPoint).offset(m_oVectorSize),m_oActualSize);
	if(oTestRect.get_top() > roPainter.paint_bottom())
	{
		return spr_below;
	}
	else
	{
		if(oTestRect.get_bottom() < roPainter.paint_top())
		{
			return spr_above;
		}
		else
		{
			return roPainter.in_clip_region(oTestRect) ? spr_inside : spr_other;
		}
	}
}

inline void cned_rect_element_::get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const
{
	if(_is_fast_graphics() || get_prop_backcolor().is_opaque())	//jeœli nieprze¿roczysty to ca³y obszar
	{
		ng_point oPaintPoint(roCurrentPoint);
		oPaintPoint.offset(m_oVectorSize);
		roArea += ng_rect(oPaintPoint,m_oActualSize);
	}
}

inline bool cned_rect_element_::is_inside_hit_area(const ng_point & roPoint) const
{
	ng_rect oMyRect;
	cned_rect_element_::get_bounding_rect(-1,oMyRect);
	return oMyRect.is_inside(roPoint);
}

inline bool cned_rect_element_::quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance)
{
	ng_rect oMyRect;
	cned_rect_element_::get_bounding_rect(-1,oMyRect);
	return _quote_rect_distance(eRP,roRefRect,oMyRect,rnDistance);
}

inline void cned_rect_element_::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	roLocalRect = ng_rect(ng_point().offset(m_oVectorSize),m_oActualSize);
}

//--------------- persistency -----------------------------------
inline void cned_rect_element_::save(cned_storage_writer & roWriter)
{
	cned_element::save(roWriter);
	roWriter << m_oActualSize;
}

inline void cned_rect_element_::load(cned_storage_reader & roReader)
{
	cned_element::load(roReader);
	roReader >> m_oActualSize;
}


inline void cned_rect_element_::set_fixed_properties()
{
	cned_element::set_fixed_properties();
	set_prop_split_allowed(false);
}

//----------------------------------------------------------------------------------------------
inline void _compute_vector_from_position(cned_element_manager * poManager,const ned_position & roPosition,
	const ng_rect & roArenaRect,const ng_point & roFlowPoint,const ng_size & roSize,ng_size & roVector)
{
	ASSERT(poManager != NULL);

	if(roPosition.is_left())
	{
		roVector.set_dx(roArenaRect.get_left() +
			poManager->to_internal(ng_size(roPosition.get_left(),0)).get_dx());
	}
	else
	{
		if(roPosition.is_right())
		{
			roVector.set_dx(1 + roArenaRect.get_right() - roSize.get_dx() - 
				poManager->to_internal(ng_size(roPosition.get_right(),0)).get_dx());
		}
		else
		{
			roVector.set_dx(roFlowPoint.get_x());
		}
	}

	if(roPosition.is_top())
	{
		roVector.set_dy(roArenaRect.get_top() + 
			poManager->to_internal(ng_size(0,roPosition.get_top())).get_dy());
	}
	else
	{
		if(roPosition.is_bottom())
		{
			roVector.set_dy(1 + roArenaRect.get_bottom() - roSize.get_dy() - 
				poManager->to_internal(ng_size(0,roPosition.get_bottom())).get_dy());
		}
		else
		{
			roVector.set_dy(roFlowPoint.get_y());
		}
	}
}

//--------------------------------------------------------------------------
//zamienia tekst na postaæ wewnêtrzn¹ (tab <-> spacje, x0d <-> nic
//zwraca true jeœli dokona³ jakiœ zmian
inline bool text2internaltext(const ng_string & roExternalText,ng_string & roInternalText)
{
	roInternalText = roExternalText;
	
	bool bChanged1 = (roInternalText.Replace("\x0D",NULL) != 0);
	bool bChanged2 = (roInternalText.Replace("\x09","    ") != 0);

	return (bChanged1 || bChanged2);
}


inline bool internaltext2text(const ng_string & roInternalText,ng_string & roExternalText)
{
	roExternalText = roInternalText;
	bool bChanged1 = (roExternalText.Replace("\0x0A","\0x0D\x0A") != 0);
	bool bChanged2 = (roExternalText.Replace("    ","\x09") != 0);

	return (bChanged1 || bChanged2);
}


}

#else
	#error __FILE__ already included
#endif
