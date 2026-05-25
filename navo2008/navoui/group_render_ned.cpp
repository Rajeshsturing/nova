/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	page element

	group element helper
*/

#include "stdafx.h"
#include "multiline_helper_ned.h"
#include "staticex_ned.h"
#include "group_helper_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-------------- rendering support -------------------
void cned_group_helper__::_get_group_metrics(const ned_measure_param & roMParam,cned_metrics & roGroupMetrics)
{
	ASSERT(!get_prop_hidden());
	ASSERT(is_measure_pending());

	ng_xdist xMinWidth	= 0;		//ca³kowita szerokoœæ minimalna
	ng_xdist xMinCurrentWidth = 0;	//bie¿¹ca szerokoœæ minimalna
	ng_ydist yMinHeight	= 0;		//minimalna wysokoœæ
	long	 nWeight	= 0;		//waga
	
	cned_filter_children oFilter(this,true,roMParam.is_printing());

	while(!oFilter.is_end())
	{
		SCP <cned_element> poElementSP = oFilter.get_element();

		if(get_prop_keepline())		//zliczaj szerokoœæ w jednej linii (poza <br/>)
		{
			cned_metrics oElementMetrics;
			poElementSP->get_metrics(roMParam,oElementMetrics);

			if(poElementSP->get_type() != ned_breakline)
			{
				xMinCurrentWidth += oElementMetrics.get_minimal_width();
			}
			else
			{
				xMinWidth = max(xMinWidth,xMinCurrentWidth);
				xMinCurrentWidth = 0;
			}
			yMinHeight = max(yMinHeight,oElementMetrics.get_minimal_height());
			nWeight += oElementMetrics.get_weight();

			if(yMinHeight > roMParam.get_req_y())
			{
			//ned_to_do: inc_rend	break;	//nie doszliœmy do koñca grupy, a ju¿ wyliczona wysokoœæ jest wiêksza ni¿ ¿¹dana
			}
		}
		else
		{
			poElementSP->get_metrics(roMParam,roGroupMetrics);
			
			if(roGroupMetrics.get_minimal_height() > roMParam.get_req_y())
			{
			//ned_to_do: inc_rend	break;	//nie doszliœmy do koñca grupy, a ju¿ wyliczona wysokoœæ jest wiêksza ni¿ ¿¹dana
			}
		}

		oFilter.move_next();
	}

	if(get_prop_keepline())
	{
		xMinWidth = max(xMinWidth,xMinCurrentWidth);
		roGroupMetrics.update(xMinWidth,yMinHeight,nWeight);
	}
}

//---------------------------------------------------------------------- 
//renderuje dzieci w wielu liniach (free flow renderer)
//---------------------------------------------------------------------- 

ng_size cned_group_helper__::_render_group(cned_transport_renderer & roRenderer,
	cned_abspos_render_manager & roARM)
{
	cned_multi_line_renderer oFreeFlowRenderer(this,roRenderer,get_manager(),
		get_prop_alignment(),m_eLineAlignment,
		roRenderer.get_current_pos(),roRenderer.get_current_width());

	ned_position oAbsPosition;

	cned_filter_children oFilter(this,true,roRenderer.is_printing());
	
	//ned_to_do: pomijanie prawid³owych linii

	while(!oFilter.is_end())
	{
		switch(get_manager()->get_element_type(oFilter.get_ident()))
		{
		case ned_breakline:
			oFilter.get_element()->render(oFreeFlowRenderer);
			oFreeFlowRenderer.newline();
		break;
		case ned_staticex:
		{
			if(get_manager()->get_decl_position(oFilter.get_ident(),oAbsPosition))
			{
				roARM.register_child(oFilter.get_element(),oAbsPosition,oFreeFlowRenderer.get_current_pos());
			}
			else
			{
				SCP<cned_staticex> poStaticExSP = scp_cast_ui<cned_staticex>(oFilter.get_element());
				poStaticExSP->render(oFreeFlowRenderer);
			}
		}
		break;
		default:
			if(get_manager()->get_decl_position(oFilter.get_ident(),oAbsPosition))
			{
				roARM.register_child(oFilter.get_element(),oAbsPosition,oFreeFlowRenderer.get_current_pos());
			}
			else
			{
				oFilter.get_element()->render(oFreeFlowRenderer);
			}
		}
		
		//ned_to_do: if(roRenderer.get_req_y() < oFreeFlowRenderer.get_cur_pos().get_y())
		//{
		//	_update_last_measured(oFilter.get_ident());
		//	break;
		//}

		oFilter.move_next();
	}

	_validate_last_measured(NEDID_LAST);
	return oFreeFlowRenderer.finish_all();
}

