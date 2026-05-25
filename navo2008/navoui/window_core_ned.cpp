/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	window
	
	core functionality
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "arena_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------
// construction and destruction
//----------------------------------------------------------------------
cned_window::cned_window(cned_arena * poArena) :
	CScriptUser(0),
	m_poArena(poArena),
	m_nPage_IID(0),
	m_nRootTypeId(0),
	m_bExistsSuggestionTransfer(false),
	m_eWIP(wip_default),
	m_idInitialFocus(NEDID_NOTHING),
	m_eActiveView(wv_normal),
	m_idsecRead(0),
	m_idsecInsert(0),
	m_idsecUpdate(0),
	m_idsecDelete(0)
{
	EnableAutomation();

	ASSERT(m_poArena);
	
	ASSERT(CMD_STANDARDLAST - CMD_STANDARDFIRST + 1 == STD_COMMAND_COUNT);

	m_strScriptNXID = "";

	for(long iter=0;iter<STD_COMMAND_COUNT;iter++)
	{
		m_abIsStdCmdDefined[iter] = false;
		m_abShowButton[iter] = false;
	}
	AddNamedItem(NewSCP(new CNamedItemInfo(_T("trans_"),&m_oTransaction_DispatchForwarder,NULL)));

	m_poNormalViewSP = NewSCP(new cned_normal_window_view(this,_create_sheet()));
	m_poSheetViewSP = NewSCP(new cned_sheet_window_view(this));

}

cned_window::~cned_window()
{
}

void cned_window::OnFinalRelease()
{
	m_poSheetViewSP = 0;
	m_poNormalViewSP = 0;

	ASSERT(m_poArena);
	m_poArena->on_window_final_release(this);
}

void cned_window::init_transaction_ddr(CDispatchDynamicResolver * poDDR)
{
	m_oTransaction_DispatchForwarder.SetDispatchDynamicResolver(poDDR);
}

//---------------- internal sheet management ----------------


SCP<cned_window_sheet> cned_window::_create_sheet()
{
	SCP<cned_element_manager> poElementManagerSP = m_poArena->_create_element_manager();
	SCP<cned_toplevelpage> poTopPageSP = 
		scp_cast_ui<cned_toplevelpage>(poElementManagerSP->_create_element(ned_toplevelpage,NEDID_TOPLEVELPAGE));

	return NewSCP(new cned_window_sheet(m_poArena,this,poElementManagerSP,poTopPageSP));
}

SCP<cned_toplevelpage> cned_window::get_toplevelpage() const
{
	ASSERT(_get_active_view() != NULL);
	return _get_active_view()->get_toplevelpage();
}

void cned_window::get_prop_official_title(ng_string & roString) const
{
	m_poNormalViewSP->get_prop_official_title(roString);
}

//-----------------------------------------------------------------
void cned_window::_realize_initial_position(const ng_rect & roCompleteArena)
{
	//ned_to_do: to nie jest eleganckie rozwi¹zanie,
	//gdy¿ ignoruje fakt istnienia view, a po nimi sheet
	//
	//Ÿle zadzia³a gdy pierwszy update wykona siê w trybie sheetview

	if(m_eWIP == wip_done)
	{
		return;
	}

	ASSERT(m_eActiveView == wv_normal);

	ng_size oTopPageSize = get_toplevelpage()->get_actual_size();

	if(is_maximal_width_value(get_toplevelpage()->get_prop_extwidth()))
	{
		m_eWIP = wip_top_left;		//overwrite inconsistent settings
	}

	ng_point oTopLeftPoint;	//ctor is safe and smart
	
	switch(m_eWIP)
	{
	case wip_center:
		oTopLeftPoint = roCompleteArena.get_centerpoint();
		oTopLeftPoint.offset(ng_size(-oTopPageSize.get_dx()/2,-oTopPageSize.get_dy()/2));
		break;
	case wip_bottom_left:
		oTopLeftPoint.set_y(roCompleteArena.get_height() - oTopPageSize.get_dy());
		break;
	case wip_top_right:
		oTopLeftPoint.set_x(roCompleteArena.get_width() - oTopPageSize.get_dx());
		break;
	case wip_top_left:
		break;
	case wip_default:
		oTopLeftPoint = m_poArena->get_default_window_position(this);
		break;
	default:
		ASSERT(false);
	}
	
	get_toplevelpage()->move_to(oTopLeftPoint.distance(ng_point()));

	ng_rect oTopPageRect;
	get_toplevelpage()->get_page_rect(oTopPageRect);
	
	//invalidujemy bezpoœrednio prostok¹t
	//bo strona mo¿e jeszcze nie byæ namalowana (a nawet nie powinna !)

	invalidate_paint_rect(oTopPageRect);

	m_eWIP = wip_done;

	_prepare_special_paint(wse_expand);
}


void cned_window::invalidate_paint_rect(const ng_rect & roAbsoluteRect)
{
	m_poArena->internal_invalidate_paint_rect(roAbsoluteRect);
}



//------------------------------ zoom helper ------------------------------

static const long _g_ZoomTable[] =
{
	33,
	50,
	66,
	73,		//73%
	81,
	90,
	100,	//x1
	111,
	123,
	137,
	152,
};

long get_next_zoom_in(const long nZoom)
{
	for(long iter = sizeof(_g_ZoomTable) / sizeof(_g_ZoomTable[0]) - 2; iter >= 0; iter--)
	{
		if(nZoom >= _g_ZoomTable[iter])
		{
			if(_g_ZoomTable[iter + 1] != 0)	//terminator
			{
				return _g_ZoomTable[iter + 1];
			}
		}
	}
	return nZoom;
}

long get_next_zoom_out(const long nZoom)
{
	for(long iter = 0; iter < sizeof(_g_ZoomTable) / sizeof(_g_ZoomTable[0]); iter++)
	{
		if(nZoom <= _g_ZoomTable[iter])
		{
			if(iter > 0 )
			{
				return _g_ZoomTable[iter - 1];
			}
		}
	}
	return nZoom;
}
