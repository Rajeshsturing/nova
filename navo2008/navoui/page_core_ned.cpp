/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	page element

	core functionality
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cned_page::cned_page(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_group_helper__(poManager,eType,idThis),
	scroll_helper__(poManager,idThis),
	m_idCaption(NEDID_NOTHING),
	m_idHeader(NEDID_NOTHING),
	m_idFooter(NEDID_NOTHING),
	m_ePDM(pdm_normal)
{
	__construct_caption();
	__construct_header();
	__construct_footer();
}

void cned_page::__construct_caption()
{
	//create caption - it is 'private' = hidden to control tree
	
	//frankly speaking current implementation doesn't hide it completely :)
	//we expected cooperation from application programmer
	SCP<cned_page_caption> poPageCaptionSP = 
		scp_cast_ui<cned_page_caption>(get_manager()->_create_element(ned_page_widgets,NEDID_NOTHING));

	poPageCaptionSP->_set_container(NewSCP<cned_container>(this,true));
	m_idCaption = poPageCaptionSP->get_ident();
	
	//do-not-link

	poPageCaptionSP->set_fixed_properties();
	poPageCaptionSP->__construct_elements();
}

void cned_page::__construct_header()
{
	SCP<cned_paragraph> poHeaderSP = 
		scp_cast_ui<cned_paragraph>(get_manager()->_create_element(ned_paragraph,NEDID_NOTHING));
	poHeaderSP->_set_container(NewSCP<cned_container>(this,true));
	m_idHeader = poHeaderSP->get_ident();
	
	//do-not-link

	poHeaderSP->set_fixed_properties();
}

void cned_page::__construct_footer()
{
	SCP<cned_paragraph> poFooterSP = 
		scp_cast_ui<cned_paragraph>(get_manager()->_create_element(ned_paragraph,NEDID_NOTHING));
	poFooterSP->_set_container(NewSCP<cned_container>(this,true));
	m_idFooter = poFooterSP->get_ident();
	
	//do-not-link

	poFooterSP->set_fixed_properties();
}

//-------------- attribute functions -------------------------
void cned_page::set_fixed_properties()
{
	set_prop_backcolor(White);
	set_prop_backcolor2(White);
	set_prop_forecolor(Black);
	set_prop_border_type(NED_BORDER_STYLE_NONE);
	set_prop_ignore_sys_disable(true);
}

void cned_page::remove_children(bool bWhileRemovingItself)
{
	//jeœli jesteœmy usuwani - usuñ tak¿e header
	if(bWhileRemovingItself)
	{
		_get_caption()->remove_children(true);
		get_manager()->_remove_element(_get_caption_ident());
		m_idCaption = NEDID_NOTHING;
		_get_header()->remove_children(true);
		get_manager()->_remove_element(_get_header_ident());
		m_idHeader = NEDID_NOTHING;
		_get_footer()->remove_children(true);
		get_manager()->_remove_element(_get_footer_ident());
		m_idFooter = NEDID_NOTHING;
	}
	cned_group_helper__::remove_children(true);
}

//---------------------------------------------------------------------- 
ned_ident cned_page::find_element_from_point(const ng_point & roPoint)
{
	ASSERT(is_inside_hit_area(roPoint));

	//sprawdzanie caption
	//przelicz na wspó³rzêdne wewnêtrzne
	{
		ng_point oInternalPoint(roPoint);
		oInternalPoint.offset(-m_oVectorSize);
		
		SCP<cned_page_caption> poPageCaptionSP = _get_caption();
		if(poPageCaptionSP->is_inside_hit_area(oInternalPoint))
		{
			return poPageCaptionSP->find_element_from_point(oInternalPoint);
		}

		{
			SCP<cned_paragraph> poHeaderSP = _get_header();
			if(poHeaderSP->is_inside_hit_area(oInternalPoint))
			{
				return poHeaderSP->find_element_from_point(oInternalPoint);
			}
		}

		{
			SCP<cned_paragraph> poFooterSP = _get_footer();
			if(poFooterSP->is_inside_hit_area(oInternalPoint))
			{
				return poFooterSP->find_element_from_point(oInternalPoint);
			}
		}

		//sprawdzenie scroll'a
		if(_scroll_is_inside_hit_area(oInternalPoint))
		{
			return _scroll_find_element_from_point(oInternalPoint);
		}
	}

	//sprawdzanie œrodka
	//uwzglêdnij scroll
	{
		ng_point oInternalPoint(roPoint);
		oInternalPoint.offset(get_scroll_pos());

		return cned_group_helper__::find_element_from_point(oInternalPoint);
	}
}


ned_ident cned_page::find_element_relative(const ng_rect & roRefRect,const ned_ident nIdStart,eRelativePosition eRP,long & rnBestDistance)
{
	//to jest potrzebne poniewaz m_oVectorSize w page jest relatywny do areny !!!
	ng_point oPoint;
	oPoint.offset(m_oVectorSize);
	_arena2local(oPoint);

	//nie odejmujemy m_oVectorSize aby zaraz potem nie dodawaæ, bo cned_container z powrotem odejmuje
	ng_rect oRect(roRefRect);
	oRect.offset(ng_point().distance(oPoint));

	return cned_group_helper__::find_element_relative(oRect,nIdStart,eRP,rnBestDistance);
}


//-------------- property get ---------------
bool cned_page::get_prop_caption() const
{
	return !get_manager()->is_element_hidden(_get_caption_ident());
}

//-------------- property set ---------------
void cned_page::set_prop_caption(bool bCaption)
{
	if(get_prop_caption() == bCaption)
	{
		return;
	}
	_get_caption()->set_prop_hidden(!bCaption);
}

void cned_page::set_prop_display_mode(epage_display_mode ePDM)
{
	if(get_prop_display_mode() == ePDM)
	{
		return;
	}

	if(m_ePDM == pdm_normal)	//was normal -> store info
	{
		m_oNormalModeInfo.m_oVectorSize = m_oVectorSize;
		m_oVectorSize = ng_size();
	}
	else	//was maximized or minimized -> restore info
	{
		m_oVectorSize = m_oNormalModeInfo.m_oVectorSize;
	}

	m_ePDM = ePDM;

	_get_caption()->set_prop_maximized(m_ePDM == pdm_maximized);

	
	//ned_to_do: notyfikacja ca³ego view / sheet o tym ¿e siê zmieni³ tryb

	_size_info_dirty();
	_vse_dirty();
}

//-------------- fill clone -------------- -------------- -------
void cned_page::fill_clone(cned_element * poDestination)
{
	cned_group_helper__::fill_clone(poDestination);
	cned_page * poDestinationPage = cast_ui<cned_page>(poDestination);
	ASSERT(poDestinationPage);

	_get_header()->fill_clone(poDestinationPage->_get_header());
	_get_footer()->fill_clone(poDestinationPage->_get_footer());
}


