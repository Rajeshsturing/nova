/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	rendered
*/

#include "stdafx.h"
#include "group_helper_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------------------
// line-renderer uk³ada wszystko w jednej linii - buduje element line
//--------------------------------------------------------------------

cned_line_renderer::cned_line_renderer(cned_renderer_ & roRenderer,cned_element_manager * poManager,
	ened_alignment eHorizAlign,ened_line_alignment eLineAlign,
	const ng_point & roStartingPoint,ng_xdist dxWidth) :
	cned_renderer_(roRenderer),
	m_poManager(poManager),
	m_eHorizAlignment(eHorizAlign),
	m_eLineAlignment(eLineAlign),
	m_oCurrentPoint(roStartingPoint),
	m_dxWidth(dxWidth),
	m_yCurrLineHeight(0)
{
	ASSERT(m_poManager);
	ASSERT(m_dxWidth >= 0);
}

void cned_line_renderer::allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize)
{
	ASSERT(idElement != NEDID_NOTHING);
	//ASSERT(m_dxWidth >= roRequiredSize.get_dx());

	if (m_dxWidth < roRequiredSize.get_dx())
	{
		m_dxWidth = roRequiredSize.get_dx();
	}

	roAllocatedSize = roRequiredSize;
	roVectorSize.set_dx(m_oCurrentPoint.get_x());
	roVectorSize.set_dy(m_oCurrentPoint.get_y());

	m_yCurrLineHeight = max(m_yCurrLineHeight,roAllocatedSize.get_dy());
	m_oCurrentPoint.set_x(m_oCurrentPoint.get_x() + roAllocatedSize.get_dx());
	
	m_dxWidth -= roAllocatedSize.get_dx();
	
	m_oLine.append_element(idElement,nElementPart);

	m_roPostRenderManager.add(idElement);
}

void cned_line_renderer::finish_line()
{
	if((m_eHorizAlignment & eal_horizmask) != eal_left && m_dxWidth > 0)
	{
		ng_size oMoveSize;
		if((m_eHorizAlignment & eal_horizmask) == eal_right)
		{
			oMoveSize.set_dx(m_dxWidth);
		}
		else
		{
			if((m_eHorizAlignment & eal_horizmask) == eal_center)
			{
				oMoveSize.set_dx(m_dxWidth / 2);
			}
		}
		ASSERT(m_poManager != NULL);
		long iter = 0;
		ned_ident idElement;
		long nElementPart;
		while(m_oLine.get_element(iter++,idElement,nElementPart))
		{
			m_poManager->get_element_on_ident(idElement)->move_by(nElementPart,oMoveSize);
		}
	}
	if(m_eLineAlignment != elal_top)
	{
		ASSERT(m_poManager != NULL);
		long iter = 0;
		ned_ident idElement;
		long nElementPart;
		while(m_oLine.get_element(iter++,idElement,nElementPart))
		{
			SCP<cned_element> poElementSP = m_poManager->get_element_on_ident(idElement);
			ng_rect oRect;
			poElementSP->get_bounding_rect(nElementPart,oRect);
			ng_size oMoveSize;
			if(m_eLineAlignment == elal_bottom)
			{
				oMoveSize.set_dy(get_line_height() - oRect.get_height());
			}
			else
			{
				oMoveSize.set_dy((get_line_height() - oRect.get_height())/2);
			}
			poElementSP->move_by(nElementPart,oMoveSize);
		}
	}
}

//--------------------------------------------------------------------
// multi-line-renderer uk³ada wiele linii
//--------------------------------------------------------------------
cned_multi_line_renderer::cned_multi_line_renderer(cned_line_consumer_ * poLineConsumer,
	cned_renderer_ & roRenderer,cned_element_manager * poManager,
	ened_alignment eHorizAlign,ened_line_alignment eLineAlign,
	const ng_point & roStartingPoint,ng_xdist dxWidth) :
	cned_renderer_(roRenderer),
	m_poManager(poManager),
	m_eHorizAlignment(eHorizAlign),
	m_eLineAlignment(eLineAlign),
	m_poLineConsumer(poLineConsumer),
	m_dxWidth(dxWidth),
	m_oCurrentPoint(roStartingPoint),
	m_yStartingY(roStartingPoint.get_y()),
	m_yLastLineHeight(0),
	m_dxMaxLineWidth(0)
{
	ASSERT(m_poManager);
	ASSERT(m_poLineConsumer != NULL);
	ASSERT(m_dxWidth >= 0);

	_start_line();
}

void cned_multi_line_renderer::_start_line()
{
	ASSERT(m_poCurrentLineRendererSP.PointsNull());
	m_poCurrentLineRendererSP = NewSCP(new cned_line_renderer(*this,m_poManager,
		m_eHorizAlignment,m_eLineAlignment,m_oCurrentPoint,m_dxWidth));
}

void cned_multi_line_renderer::_finish_line()
{
	m_poCurrentLineRendererSP->finish_line();

	if(!m_poCurrentLineRendererSP->get_element_line().is_empty())
	{
		//aktualizuj wysokoœæ linii i zapamiêtaj (ale tylko efektywnie coœ zajmujace)
		if(m_poCurrentLineRendererSP->get_line_height() > 0)
		{
			m_yLastLineHeight = m_poCurrentLineRendererSP->get_line_height();
		}
		//ca³a szerokoœæ - to co zosta³o = to co zu¿yte
		ng_xdist dxLineWidth = m_dxWidth - m_poCurrentLineRendererSP->get_current_width();
		m_dxMaxLineWidth = max(m_dxMaxLineWidth,dxLineWidth);

		m_oCurrentPoint.offset(0,m_yLastLineHeight);

		m_poLineConsumer->add_line(m_poCurrentLineRendererSP->get_element_line());
	}

	m_poCurrentLineRendererSP = 0;
}

void cned_multi_line_renderer::ensure_width(const ng_xdist dxWidth)
{
	if(get_current_width() < dxWidth)
	{
		_finish_line();
		_start_line();
	}
	//ASSERT(get_current_width() >= dxWidth);
}

void cned_multi_line_renderer::allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize)
{
	ensure_width(roRequiredSize.get_dx());
	m_poCurrentLineRendererSP->allocate_rect(idElement,nElementPart,roRequiredSize,roAllocatedSize,roVectorSize);
}

//--------------------------------------------------------------------
// column-renderer uk³ada kolejne elementy pod spodem
// szerokoœæ zawsze jest taka sama 
//--------------------------------------------------------------------
cned_column_renderer::cned_column_renderer(cned_renderer_ & roRenderer,const ng_point & roStartingPoint,ng_xdist dxWidth) :
	cned_renderer_(roRenderer),
	m_oCurrentPoint(roStartingPoint),
	mc_dxWidth(dxWidth)
{
	ASSERT(mc_dxWidth >= 0);
}

//--------------------------------------------------------------------
//	absolute position render manager
//  cned_abspos_render_manager
//--------------------------------------------------------------------

ng_size cned_abspos_render_manager::render(cned_renderer_ & roRenderer,const ng_rect & roParentRect)
{
	cned_absolute_renderer oAbsRenderer(roRenderer,roParentRect);

restart_:
	for(long iter = 0; iter <= m_oAbsoluteChildren.GetUpperBound(); iter++)
	{
		if(!m_oAbsoluteChildren[iter].m_poElementSP->abs_render(oAbsRenderer,
			m_oAbsoluteChildren[iter].m_oPosition,m_oAbsoluteChildren[iter].m_oFlowPoint))
		{
			
			//musi byæ zmiana
			ASSERT(roParentRect.get_width() < oAbsRenderer.get_arena_rect().get_width() ||
				roParentRect.get_height() < oAbsRenderer.get_arena_rect().get_height());
			
			//wolno tylko powiêkszaæ
			ASSERT(roParentRect.get_width() <= oAbsRenderer.get_arena_rect().get_width());
			ASSERT(roParentRect.get_height() <= oAbsRenderer.get_arena_rect().get_height());

			goto restart_;
		}
	}
	return oAbsRenderer.get_arena_rect().get_size();
}

//--------------------------------------------------------------------
