/*
	NAVO Enterprise 2003
	2003-04-25

	navo enhanced display (NED)

	window
	
	page breaks
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
#include "element_nedaw.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------
//         page breaking                                  
//--------------------------------------------------------

namespace ned
{

class cpb_window_split_manager : public cpb_split_manager
{
public:
	cpb_window_split_manager(cned_window * poWindow,const cned_page_break_param & roPBP,cpb_split_info_storage & roStorage);
	virtual SCP<cned_element> get_clone(long xAreaX,long yAreaY,ned_ident idElement);
	virtual void register_clone(long xAreaX,long yAreaY,
		ned_ident idOriginalElement,ned_ident idClonedElement);
	virtual void add_event_param(const cpb_on_split_event_param & roEventParam);

	void fire_pending_events();

	class sheet_info : public CInterface__
	{
	public:
		sheet_info(SCP<cned_window_sheet> poWindowSheetSP);

		ned_ident get_mapped_ident(ned_ident idOriginal) const;
		void store_mapped_ident(ned_ident idOriginal,ned_ident idClone);
		SCP<cned_element> get_element_on_ident(const ned_ident idElement);
		SCP<cned_toplevelpage> get_toplevelpage();
	private:
		SCP<cned_window_sheet> m_poWindowSheetSP;
		CMap<ned_ident,ned_ident,ned_ident,ned_ident> m_oIdentMap;
	};

	SCP<sheet_info> get_sheet_info(long xAreaX,long yAreaY);

	void _build_sheet_array(long xCount,long yCount);
	SCP<sheet_info> _create_new_sheet(long xAreaX,long yAreaY);
	void _init_new_sheet(long xAreaX,long yAreaY);

	CArray2DX< SCP<sheet_info>, SCP<sheet_info> & > m_oSheet2DArray;
	CArray<cpb_on_split_event_param,const cpb_on_split_event_param &> m_oPendingEventParamArray;
	
	cned_window * m_poWindow;
	const cned_page_break_param m_oPBP;
};

//-------------------------------------------------------------------
inline void _init_cell(SCP<ned::cpb_window_split_manager::sheet_info> * pObject)
{
	(*pObject) = SCP<cpb_window_split_manager::sheet_info>();
}

inline void _clear_cell(SCP<ned::cpb_window_split_manager::sheet_info> * pObject)
{
	(* pObject) = 0;
}

}

cpb_window_split_manager::sheet_info::sheet_info(SCP<cned_window_sheet> poWindowSheetSP) :
	m_poWindowSheetSP(poWindowSheetSP)
{
	ASSERT(m_poWindowSheetSP.PointsObject());
	m_oIdentMap.InitHashTable(599);
}

inline ned_ident cpb_window_split_manager::sheet_info::get_mapped_ident(ned_ident idOriginal) const
{
	ned_ident idMapped;
	if(!m_oIdentMap.Lookup(idOriginal,idMapped))
	{
		return NEDID_NOTHING;
	}
	return idMapped;
}

inline void cpb_window_split_manager::sheet_info::store_mapped_ident(ned_ident idOriginal,ned_ident idClone)
{
	ASSERT(idOriginal != NEDID_NOTHING);
	ASSERT(idClone != NEDID_NOTHING);
	ASSERT(get_mapped_ident(idOriginal) == NEDID_NOTHING);

	m_oIdentMap[ idOriginal ] = idClone;
}

SCP<cned_element> cpb_window_split_manager::sheet_info::get_element_on_ident(const ned_ident idElement)
{
	return m_poWindowSheetSP->get_element_on_ident(idElement);
}

SCP<cned_toplevelpage> cpb_window_split_manager::sheet_info::get_toplevelpage()
{
	return m_poWindowSheetSP->get_toplevelpage();
}

cpb_window_split_manager::cpb_window_split_manager(cned_window * poWindow,const cned_page_break_param & roPBP,
	cpb_split_info_storage & roStorage) :
	cpb_split_manager(roStorage),
	m_poWindow(poWindow),
	m_oPBP(roPBP)
{
	_build_sheet_array(roStorage.get_x_count(),roStorage.get_y_count());
}

SCP<cpb_window_split_manager::sheet_info> cpb_window_split_manager::_create_new_sheet(long xAreaX,long yAreaY)
{

	SCP<cned_window_sheet> poWindowSheetSP = m_poWindow->_create_sheet();
	m_poWindow->m_poSheetViewSP->add_new_sheet(xAreaX,yAreaY,poWindowSheetSP);

	SCP<sheet_info> poSheetInfoSP = NewSCP(new sheet_info(poWindowSheetSP));

	while(xAreaX >= m_oSheet2DArray.get_col_count())
	{
		m_oSheet2DArray.add_col();
	}
	while(yAreaY >= m_oSheet2DArray.get_row_count())
	{
		m_oSheet2DArray.add_row();
	}
	
	m_oSheet2DArray.set_at(yAreaY,xAreaX,poSheetInfoSP);

	
	poSheetInfoSP->store_mapped_ident(NEDID_TOPLEVELPAGE,NEDID_TOPLEVELPAGE);

	return poSheetInfoSP;
}

void cpb_window_split_manager::_init_new_sheet(long xAreaX,long yAreaY)
{
	SCP<sheet_info> poSheetInfoSP = get_sheet_info(xAreaX,yAreaY);

	m_poWindow->m_poNormalViewSP->get_toplevelpage()->fill_clone_split(
		*this,poSheetInfoSP->get_toplevelpage(),m_oPBP,
		xAreaX,yAreaY,m_oSheet2DArray.get_col_count(),m_oSheet2DArray.get_row_count());
}

void cpb_window_split_manager::_build_sheet_array(long xCount,long yCount)
{
	ASSERT(xCount > 0 && yCount > 0);

	//=== create sheets ===
	{
		for(long xIter = 0; xIter < xCount; xIter++)
		{
			for(long yIter = 0; yIter < yCount; yIter++)
			{
				_create_new_sheet(xIter,yIter);
			}
		}
	}

	//=== fill sheet === 
	{
		for(long xIter = 0; xIter < xCount; xIter++)
		{
			for(long yIter = 0; yIter < yCount; yIter++)
			{
				_init_new_sheet(xIter,yIter);
			}
		}
	}
}

SCP<cpb_window_split_manager::sheet_info> cpb_window_split_manager::get_sheet_info(long xAreaX,long yAreaY)
{
	ASSERT(xAreaX < m_oSheet2DArray.get_col_count() && xAreaX >= 0);
	ASSERT(yAreaY < m_oSheet2DArray.get_row_count() && yAreaY >= 0);

	return m_oSheet2DArray.get_at(yAreaY,xAreaX);
}

SCP<cned_element> cpb_window_split_manager::get_clone(long xAreaX,long yAreaY,ned_ident idElement)
{
	SCP<sheet_info> poSheetInfoSP = get_sheet_info(xAreaX,yAreaY);

	ASSERT(poSheetInfoSP.PointsObject());
	
	ned_ident idClone = poSheetInfoSP->get_mapped_ident(idElement);

	if(idClone != NEDID_NOTHING)
	{
		SCP<cned_element> poClonedElementSP = poSheetInfoSP->get_element_on_ident(idClone);
		ASSERT(poClonedElementSP.PointsObject());
		return poClonedElementSP;
	}
	else
	{
		return SCP<cned_element>();
	}
}

void cpb_window_split_manager::register_clone(
	long xAreaX,long yAreaY,ned_ident idOriginalElement,ned_ident idClonedElement)
{
	SCP<sheet_info> poSheetInfoSP = get_sheet_info(xAreaX,yAreaY);

	ASSERT(poSheetInfoSP.PointsObject());
	ASSERT(poSheetInfoSP->get_mapped_ident(idOriginalElement) == NEDID_NOTHING);

	poSheetInfoSP->store_mapped_ident(idOriginalElement,idClonedElement);
}

void cpb_window_split_manager::add_event_param(const cpb_on_split_event_param & roEventParam)
{
	m_oPendingEventParamArray.Add(roEventParam);

	TRACE("FIRE EVENT %s for %d [%d,%d]\n",roEventParam.m_oFunctionNameString,
		roEventParam.m_poClonedElementSP->get_ident(),roEventParam.m_xAreaX,
		roEventParam.m_yAreaY);
}

void cpb_window_split_manager::fire_pending_events()
{
	for(long iter = 0; iter <= m_oPendingEventParamArray.GetUpperBound(); iter++)
	{
		_fire_on_split_event_function(m_poWindow,m_oPendingEventParamArray[iter]);
	}
}

//==========================================================================
//custom split functions
//==========================================================================
bool ned::_fire_on_split_event_function(cned_window * poWindow,
		const cpb_on_split_event_param & roEventParam)
{
	ASSERT(roEventParam.m_poClonedElementSP.PointsObject());
	CSmartOleVariant oArgumentSOVArray[5];

	ALL_TRY
	{
		//[void] function roFunctionName(byref pClone,byval xAreaX,byval yAreaY,byval xCount,byval yCount)
		
		oArgumentSOVArray[4] = CSmartOleVariant(roEventParam.m_poClonedElementSP.ConstCastObject()->get_my_nedaw()->GetIDispatch(TRUE),false);
		oArgumentSOVArray[3] = CSmartOleVariant(long(1+roEventParam.m_xAreaX),VT_I4);
		oArgumentSOVArray[2] = CSmartOleVariant(long(1+roEventParam.m_yAreaY),VT_I4);
		oArgumentSOVArray[1] = CSmartOleVariant(long(roEventParam.m_xCount),VT_I4);
		oArgumentSOVArray[0] = CSmartOleVariant(long(roEventParam.m_yCount),VT_I4);
		
		eInvokeResult eResult = poWindow->fire_user_command(roEventParam.m_oFunctionNameString,oArgumentSOVArray,5,false);
		return (eResult == invoke_true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
#ifdef _DEVELOPER_EDITION_
		ContinueThrowNavoAutoException(roNavoException);
#endif
	}
}

//=======================================================================
//=======================================================================

void cned_window::do_page_breaks(const cned_page_break_param & roPageBreakParam)
{
	//------------------------------------------------------------------------------
	//note: normal view should be layed out on current DC and params (roPageBreakParam)
	//------------------------------------------------------------------------------

	//reset sheet view to empty one
	m_poSheetViewSP = NewSCP(new cned_sheet_window_view(this));

	cpb_split_info_storage oSplitInfoStorage;
	
	cpb_split_info oSplitInfo(oSplitInfoStorage,0,
		roPageBreakParam.m_oPrintableSheetPxSize.get_dy(),
		roPageBreakParam.m_oPrintableSheetPxSize.get_dy(),
		roPageBreakParam.m_oPrintableSheetPxSize.get_dx());
	
	m_poNormalViewSP->update_split_info(oSplitInfo);

	cpb_window_split_manager oWindowSplitManager(this,roPageBreakParam,oSplitInfoStorage);
	m_poNormalViewSP->make_split(oWindowSplitManager);
	oWindowSplitManager.fire_pending_events();

}

