/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	element definition
	some helpers

*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------------------

SCP<cned_page> cned_element::get_page() const
{
	//dla tych nie ma co siê pytaæ
	ASSERT(get_type() != ned_subpage && get_type() != ned_toplevelpage);

	SCP<cned_container> poContainerSP = get_container();
	ASSERT(poContainerSP.PointsObject());	//przynajmniej 1 musi byæ
	while(poContainerSP.PointsObject())
	{
		if(poContainerSP->get_type() == ned_subpage || poContainerSP->get_type() == ned_toplevelpage)
		{
			return scp_cast_ui<cned_page>(poContainerSP.Get());
		}
		poContainerSP = poContainerSP->get_container();
	}
	ASSERT(false);
	return SCP<cned_page>();
}

SCP<cned_toplevelpage> cned_element::get_toplevelpage() const
{
	return scp_cast_ui<cned_toplevelpage>(get_element_on_ident(NEDID_TOPLEVELPAGE));
}

/*
	zaczyna poszukiwania od bezpoœredniego ojca elementu a potem roszerza wœród kontenerów w górê
	- jest du¿a szansa ¿e znajdzie szybko dobry wynik i resztê bêdzie móg³ przeskoczyæ
*/

#ifdef _DEBUG
long _debug_quoting_counter = 0;
#endif

ned_ident cned_element::search_tree_for_nearest_element(eRelativePosition eRP)
{
#ifdef _DEBUG
	_debug_quoting_counter = 0;
#endif

	ned_ident idBest = NEDID_NOTHING;
	ned_ident idStart = get_ident();
	long nBestDistance = MAXLONG;

	//compute element's bounding rect
	ng_rect oMyRect;
	get_bounding_rect(-1,oMyRect);

	SCP<cned_container> poContainerSP = get_container();
	
	while(poContainerSP.PointsObject())
	{
		//zamieniamy na wspó³rzêdne nadrzêdnego kontenera
		oMyRect.offset(poContainerSP->m_oVectorSize);

		ned_ident idFound = poContainerSP->find_element_relative(oMyRect,idStart,eRP,nBestDistance);
		if(idFound != NEDID_NOTHING)
		{
			idBest = idFound;
		}
		idStart = poContainerSP->get_ident();		//informacja, aby tego ju¿ nie analizowaæ
		poContainerSP = poContainerSP->get_container();
	}

	ASSERT(idBest != idStart);
#ifdef _DEBUG
	TRACE("FER: total quoted = %d\n",_debug_quoting_counter);
#endif
	return idBest;
}

//----------------------------------------------------------------------------------------------
const long RELPOS_SCALING_FACTOR = 100;
const long RELPOS_MISLINE_PENALTY = 10;

bool ned::_quote_rect_distance(eRelativePosition eRP,const ng_rect & roRefRect,const ng_rect & roTestRect,long & rnDistance)
{
	long nDistance = MAXLONG;
	
	switch(eRP)
	{
	case rp_above:
	{
		ng_ydist yDist = RELPOS_SCALING_FACTOR * (roRefRect.get_top() - roTestRect.get_bottom());
		if(yDist > 0)
		{
			if(roRefRect.get_left() <= roTestRect.get_right() && roTestRect.get_left() <= roRefRect.get_right())
			{
				yDist += labs(roRefRect.get_center_x() - roTestRect.get_center_x()) * RELPOS_MISLINE_PENALTY;
				nDistance = yDist;
			}
		}
	}
	break;
	case rp_below:
	{
		ng_ydist yDist = RELPOS_SCALING_FACTOR * (roTestRect.get_top() - roRefRect.get_bottom());
		if(yDist > 0)
		{
			if(roRefRect.get_left() <= roTestRect.get_right() && roTestRect.get_left() <= roRefRect.get_right())
			{
				yDist += labs(roRefRect.get_center_x() - roTestRect.get_center_x()) * RELPOS_MISLINE_PENALTY;
				nDistance = yDist;
			}
		}
	}
	break;
	case rp_leftside:
	{
		ng_xdist xDist = RELPOS_SCALING_FACTOR * (roRefRect.get_left() - roTestRect.get_right());
		if(xDist > 0)
		{
			if(roRefRect.get_top() <= roTestRect.get_bottom() && roTestRect.get_top() <= roRefRect.get_bottom())
			{
				xDist += labs(roRefRect.get_center_y() - roTestRect.get_center_y()) * RELPOS_MISLINE_PENALTY;
				nDistance = xDist;
			}
		}
	}
	break;
	case rp_righside:
	{
		ng_xdist xDist = RELPOS_SCALING_FACTOR * (roTestRect.get_left() - roRefRect.get_right());
		if(xDist > 0)
		{
			if(roRefRect.get_top() <= roTestRect.get_bottom() && roTestRect.get_top() <= roRefRect.get_bottom())
			{
				xDist += labs(roRefRect.get_center_y() - roTestRect.get_center_y()) * RELPOS_MISLINE_PENALTY;
				nDistance = xDist;
			}
		}
	}
	break;
	default:
		ASSERT(false);
	}
	
	if(nDistance < rnDistance)
	{
		rnDistance = nDistance;
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------------------------
void draw_drag_rect(const ng_rect & roRect,ng_dc & roDC)
{
	ng_rect oInteriorRect(roRect);
	oInteriorRect.inflate(-2,-2);
	ng_region oRegion(oInteriorRect);
	roDC.set_clip_region(oRegion,RGN_DIFF);
	roDC.patblt(roRect,RGB(192,192,192),PATINVERT);
	roDC.set_clip_region(oRegion,RGN_OR);
}

void animate_rect(const animate_rect_effect & roARE,ng_dc & roDC)
{
	ASSERT(roARE.m_nSteps > 1);
	ASSERT(roARE.m_nStepDelay > 0);

	long nSteps = roARE.m_nSteps;

	ng_xdist dxSizeChange = (roARE.m_oEndingRect.get_width() - roARE.m_oStartingRect.get_width()) / nSteps;
	ng_ydist dySizeChange = (roARE.m_oEndingRect.get_height() - roARE.m_oStartingRect.get_height()) / nSteps;
	ng_xdist dxPosChange = (roARE.m_oEndingRect.get_left() - roARE.m_oStartingRect.get_left()) / nSteps;
	ng_ydist dyPosChange = (roARE.m_oEndingRect.get_top() - roARE.m_oStartingRect.get_top()) / nSteps;

	ng_rect oRect = roARE.m_oStartingRect;

	draw_drag_rect(oRect,roDC);

	while(nSteps--)
	{
		//OS_API_CALL
		::Sleep(roARE.m_nStepDelay);
	
		//remove initial rect
		draw_drag_rect(oRect,roDC);		
		
		//compute new rect
		oRect.offset(dxPosChange,dyPosChange);
		oRect.set_width(oRect.get_width() + dxSizeChange);
		oRect.set_height(oRect.get_height() + dySizeChange);

		//paint new rect
		draw_drag_rect(oRect,roDC);
	}
	
	//remove final rect
	draw_drag_rect(oRect,roDC);
}

//--------------------------------------------------------------------------
// perform raw (bitblit) but smart scroll
//--------------------------------------------------------------------------

void ned::_perform_scroll(perform_scroll_param & roPSP)
{
	roPSP.m_oArenaSrcRect.intersect_with(roPSP.m_oArenaCompleteRect);

	if(roPSP.m_oDistance.get_dy() > 0)
	{
		roPSP.m_oArenaSrcRect.set_top(roPSP.m_oArenaSrcRect.get_top() + roPSP.m_oDistance.get_dy());
		roPSP.m_oArenaInvalidRectY = roPSP.m_oArenaSrcRect;
		roPSP.m_oArenaInvalidRectY.set_top(roPSP.m_oArenaSrcRect.get_bottom() - roPSP.m_oDistance.get_dy() + 1);
	}
	else
	{
		roPSP.m_oArenaSrcRect.set_bottom(roPSP.m_oArenaSrcRect.get_bottom() + roPSP.m_oDistance.get_dy());
		roPSP.m_oArenaInvalidRectY = roPSP.m_oArenaSrcRect;
		roPSP.m_oArenaInvalidRectY.set_bottom(roPSP.m_oArenaSrcRect.get_top() - roPSP.m_oDistance.get_dy() + 1);
	}
	
	if(roPSP.m_oDistance.get_dx() > 0)
	{
		roPSP.m_oArenaSrcRect.set_left(roPSP.m_oArenaSrcRect.get_left() + roPSP.m_oDistance.get_dx());
		roPSP.m_oArenaInvalidRectX = roPSP.m_oArenaSrcRect;
		roPSP.m_oArenaInvalidRectX.set_left(roPSP.m_oArenaSrcRect.get_right() - roPSP.m_oDistance.get_dx() + 1);
	}
	else
	{
		roPSP.m_oArenaSrcRect.set_right(roPSP.m_oArenaSrcRect.get_right() + roPSP.m_oDistance.get_dx());
		roPSP.m_oArenaInvalidRectX = roPSP.m_oArenaSrcRect;
		roPSP.m_oArenaInvalidRectX.set_right(roPSP.m_oArenaSrcRect.get_left() - roPSP.m_oDistance.get_dx() + 1);
	}

	ng_rect oDestRect(roPSP.m_oArenaSrcRect);
	oDestRect.offset(-roPSP.m_oDistance);

	if(roPSP.m_oArenaSrcRect.is_normal())
	{
		ASSERT(oDestRect.is_normal());
		ASSERT(rect_containment(roPSP.m_oArenaSrcRect,roPSP.m_oArenaCompleteRect) == 1);

		ng_region oSaveRgn;
		oSaveRgn.from_clip_region(*roPSP.m_poDC);
		ng_region oRegion(oDestRect);
//		roPSP.m_poDC->set_clip_region(oRegion,RGN_COPY);
		roPSP.m_poDC->bitblt(oDestRect.get_topleft(),oDestRect.get_size(),roPSP.m_oArenaSrcRect.get_topleft(),SRCCOPY);
		roPSP.m_poDC->set_clip_region(oSaveRgn,RGN_COPY);
	}
}
