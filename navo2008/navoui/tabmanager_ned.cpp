/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabmanager / <tab>
		tabmanager
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "tabitem_ned.h"
#include "tabmanager_header_ned.h"
#include "tabmanager_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_tabmanager::cned_tabmanager(cned_element_manager * poManager,const ned_ident idThis) :
	cned_rect_container_(poManager,ned_tabmanager,idThis),
	m_idHeader(NEDID_NOTHING),
	m_nActiveItemNr(-1)
{
	__construct_header();
}

void cned_tabmanager::__construct_header()
{
	ASSERT(NEDID_NOTHING == m_idHeader);

	//create header - it is 'private' = hidden to control tree
	
	SCP<cned_tabmanager_header_> poTMHeaderSP = 
		scp_cast_ui<cned_tabmanager_header_>(get_manager()->_create_element(ned_tabmanagerheader,NEDID_NOTHING));
	poTMHeaderSP->_set_container(NewSCP<cned_container>(this,true));

	//do-not-link 

	poTMHeaderSP->set_prop_keepline(true);
	
	m_idHeader = poTMHeaderSP->get_ident(); 
}

//-------------- element finders ------------------------
ned_ident cned_tabmanager::find_element_from_point(const ng_point & roPoint)
{
	ASSERT(is_inside_hit_area(roPoint));

	ng_point oInternalPoint(roPoint);
	oInternalPoint.offset(-m_oVectorSize);
	SCP<cned_tabmanager_header_> poTMHeaderSP = _get_header();
	if(poTMHeaderSP->is_inside_hit_area(oInternalPoint))
	{
		return poTMHeaderSP->find_element_from_point(oInternalPoint);
	}
	if(get_prop_active_item_nr() != -1)
	{
		SCP<cned_tabmanager_item> poTMItemSP = get_active_item();
		if(poTMItemSP->is_inside_hit_area(oInternalPoint))
		{
			return poTMItemSP->find_element_from_point(oInternalPoint);
		}
	}
	return get_ident();
}

//--------- drawing ------------------
void cned_tabmanager::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	long nPrevTreeDisCnt;
	roForePainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	SCP<cned_tabmanager_header_> poTMHeaderSP = _get_header();
	if(poTMHeaderSP->should_paint(roForePainter,oPaintPoint))
	{
		poTMHeaderSP->draw_foreground(roForePainter,oPaintPoint);
	}

	if(get_prop_active_item_nr() != -1)
	{
		SCP<cned_tabmanager_item> poTMItemSP = get_active_item();
		if(poTMItemSP->should_paint(roForePainter,oPaintPoint))
		{
			poTMItemSP->draw_foreground(roForePainter,oPaintPoint);
		}
	}

	_draw_std_frame(roForePainter,ng_rect(oPaintPoint,m_oActualSize));

	roForePainter.restore_disabled(nPrevTreeDisCnt);
}

void cned_tabmanager::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	long nPrevTreeDisCnt;
	roBackPainter.mark_disabled(get_prop_disabled(),nPrevTreeDisCnt);

	_draw_std_background(roBackPainter,ng_rect(oPaintPoint,m_oActualSize));

	SCP<cned_tabmanager_header_> poTMHeaderSP = _get_header();
	if(poTMHeaderSP->should_paint(roBackPainter,oPaintPoint))
	{
		poTMHeaderSP->draw_background(roBackPainter,oPaintPoint);
	}

	if(get_prop_active_item_nr() != -1)
	{
		SCP<cned_tabmanager_item> poTMItemSP = get_active_item();
		if(poTMItemSP->should_paint(roBackPainter,oPaintPoint))
		{
			poTMItemSP->draw_background(roBackPainter,oPaintPoint);
		}
	}

	roBackPainter.restore_disabled(nPrevTreeDisCnt);
}

//-------------- attribute functions -------------------------
void cned_tabmanager::set_fixed_properties()
{
	cned_rect_container_::set_fixed_properties();

	set_prop_backcolor(Transparent);
	set_prop_backcolor2(Transparent);
	set_prop_extwidth(NED_MIN_WIDTH);
}

//------------- child management ----------
void cned_tabmanager::remove_children(bool bWhileRemovingItself)
{
	cned_rect_container_::remove_children(bWhileRemovingItself);

	//jeœli jesteœmy usuwani - usuñ tak¿e header
	if(bWhileRemovingItself)
	{
		_get_header()->remove_children(true);
		get_manager()->_remove_element(_get_header_ident());
	}
}

void cned_tabmanager::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	if(rpoChildSP->get_container_ident() == get_ident())
	{
		ASSERT(rpoChildSP->get_type() == ned_tabitem);

		//wyznaczanie pozycji
		long nChildPosition = scan_for_child_pos(rpoChildSP->get_ident());
		ASSERT(nChildPosition >= 0);
		bool bFirstTabItem = (get_child_count() == 1); 

		//notify header
		_get_header()->on_item_inserted(nChildPosition);

		if(bFirstTabItem)
		{
			ASSERT(get_prop_active_item_nr() == -1);
			set_prop_active_item_nr(0);
		}
	}
	cned_rect_container_::on_child_inserted(rpoChildSP);
}

void cned_tabmanager::on_child_removing(ned_ident idChild)
{
	if(get_manager()->get_element_container_ident(idChild) == get_ident())
	{
		if(get_manager()->get_element_type(idChild) == ned_tabitem)
		{
			long nChildPosition = scan_for_child_pos(idChild);
			ASSERT(nChildPosition >= 0);
			
			if(get_prop_active_item_nr() == nChildPosition)	//gdy usuwamy aktywny - przesuñ activeitem
			{
				set_prop_active_item_nr(get_prop_active_item_nr()-1);
			}

			_get_header()->on_item_removed(nChildPosition);
		}
		else
		{
			ASSERT(get_manager()->get_element_type(idChild) == ned_tabmanagerheader);
		}
	}
	cned_rect_container_::on_child_removing(idChild);
}

//-------------- rendering support -------------------
void cned_tabmanager::get_children_metrics(const ned_measure_param & roMParam)
{
	ASSERT(!get_prop_hidden());

	//zmierz osobno header
	cned_metrics oHeaderMetrics;
	_get_header()->get_metrics(roMParam,oHeaderMetrics);
	cned_metrics oActiveItemMetrics;
	if(get_prop_active_item_nr() != -1)
	{
		get_active_item()->get_metrics(roMParam,oActiveItemMetrics);
	}

	//szerokoœæ - max z headera i aktywnego elementu
	//wysokoœæ - suma z headera i aktywnego elementu
	//waga - suma z headera i aktywnego elementu

	m_oMetrics.update(max(oHeaderMetrics.get_minimal_width(),oActiveItemMetrics.get_minimal_width()),
		oHeaderMetrics.get_minimal_height() + oActiveItemMetrics.get_minimal_height(),
		oHeaderMetrics.get_weight() + oActiveItemMetrics.get_weight());
}

void cned_tabmanager::render(cned_renderer_ & roRenderer)
{
	roRenderer.ensure_width(m_oMetrics.get_minimal_width());
	
	const ng_xdist dxActualWidth = _get_std_width_for_rendering(roRenderer);

	cned_column_renderer oColumnRenderer(roRenderer,ng_point(0,0),dxActualWidth);
	
	_get_header()->render(oColumnRenderer);

	if(get_prop_active_item_nr() != -1)
	{
		get_active_item()->render(oColumnRenderer);
	}
	
	ASSERT(dxActualWidth == oColumnRenderer.get_current_width());
	
	ng_size oTMSize(dxActualWidth,_get_std_height_for_rendering(oColumnRenderer.get_current_pos().get_y()));
	roRenderer.allocate_rect(get_ident(),-1,oTMSize,m_oActualSize,m_oVectorSize);
	_validate_last_measured(NEDID_LAST);
}

//--------------event handlers ---------------------------------------
void cned_tabmanager::on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult)
{
	ASSERT(roActionCommand.get_target() == get_ident());
	
	switch(roActionCommand.get_verb())
	{
	case sccv_activate_item:
	{
		ned_ident idFiringStatic = ned_ident(roActionCommand.get_command()->GetProp(PROPC_VARIANT).GetLong());
		long nActiveItemNr = _get_header()->_get_position_of_item_ident(idFiringStatic);
		bool bFirstTime = set_prop_active_item_nr(nActiveItemNr);

		SCP<ned_event_tabitem_activation> poTabItemActivSP = 
			NewSCP(new ned_event_tabitem_activation(get_ident(),nActiveItemNr,bFirstTime));
		roResult.add_info(poTabItemActivSP);
	}
	break;
	}
}

