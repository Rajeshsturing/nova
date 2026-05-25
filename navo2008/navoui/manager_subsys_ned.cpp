/*
	NAVO Enterprise 2003
	2003-04-12

	navo enhanced display (NED)
		- manager_elementów

	ró¿ne podsystemy
*/

#include "stdafx.h"
#include "arena_manager_ned.h"
#include "style_ned.h"
#include "element_nedaw.h"
#include "commandlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const ng_rect & cned_element_manager::get_screen_arena() const
{
	return m_poArenaManager->get_screen_arena();
}

//---------- time-aware control registration -------------
void cned_element_manager::unregister_for_timer(ned_ident idElement)
{
	for(long iter = 0; iter < m_oTimerRegisteredArray.GetSize(); iter++)
	{
		if(m_oTimerRegisteredArray[iter].m_idElement == idElement)
		{
			m_oTimerRegisteredArray.RemoveAt(iter);
			
			//when removed last - destroy timer
			if(m_oTimerRegisteredArray.GetSize() == 0)
			{
				m_poArenaManager->release_control_timer_ref();
			}
			return;
		}
	}
}

void cned_element_manager::register_for_timer(ned_ident idElement,long nInterval,bool bOnlyWhenOnTop)
{
	ASSERT(nInterval > 0);

	//create timer when registering first
	if(m_oTimerRegisteredArray.GetSize() == 0)
	{
		m_poArenaManager->add_control_timer_ref();
	}
	m_oTimerRegisteredArray.Add(timer_registration(idElement,nInterval,bOnlyWhenOnTop));
}

void cned_element_manager::get_timer_controls(CArray<ned_ident,ned_ident &> & roIdentArray,bool bForTopWindow)
{
	roIdentArray.RemoveAll();

	for(long iter = 0; iter < m_oTimerRegisteredArray.GetSize(); iter++)
	{
		//decrement each registered timer

		m_oTimerRegisteredArray[iter].m_nCountDown--;
		ASSERT(m_oTimerRegisteredArray[iter].m_nCountDown >= 0);
		
		//when threashold reached - add to currently fired controls
		if(m_oTimerRegisteredArray[iter].m_nCountDown == 0)
		{
			if(!m_oTimerRegisteredArray[iter].m_bOnlyWhenOnTop || bForTopWindow)
			{
				roIdentArray.Add(m_oTimerRegisteredArray[iter].m_idElement);
			}
			//restore countdown
			m_oTimerRegisteredArray[iter].m_nCountDown = m_oTimerRegisteredArray[iter].m_nInterval;
		}
	}
}

//------------------------------------------------------------------------------------
// focus management 
//------------------------------------------------------------------------------------
void cned_element_manager::_mark_new_focus_element(ned_ident idNewFocusElement)
{
#ifdef _DEBUG
	{
		if(idNewFocusElement != NEDID_NOTHING)
		{
			ASSERT(can_element_accept_focus(idNewFocusElement));	//poprawne wywo³anie
		}
	}
#endif
	
	m_idFocus = idNewFocusElement;
}

bool cned_element_manager::_consume_focus_change(ned_ident & ridOldFocus)
{
	ridOldFocus = m_idOldFocus;
	bool bChange = (m_idOldFocus != m_idFocus);
	m_idOldFocus = m_idFocus;
	return bChange;
}

//-------------- tooltip and help text manager ----------------------------
void cned_element_manager::set_tooltip_text(ned_ident idElement,const ng_string & roToolTipString)
{
	long nHashedId = _pre_hash(idElement);
	m_oToolTipMap[ nHashedId ] = roToolTipString;
}

void cned_element_manager::get_tooltip_text(ned_ident idElement,ng_string & roToolTipString) const
{
	long nHashedId = _pre_hash(idElement);
	if(!m_oToolTipMap.Lookup(nHashedId,roToolTipString))
	{
		roToolTipString = "";
	}
}

void cned_element_manager::set_help_text(ned_ident idElement,const ng_string & roHelpTextString)
{
	long nHashedId = _pre_hash(idElement);
	m_oHelpTextMap[ nHashedId ] = roHelpTextString;
}

void cned_element_manager::get_help_text(ned_ident idElement,ng_string & roHelpTextString) const
{
	long nHashedId = _pre_hash(idElement);
	if(!m_oHelpTextMap.Lookup(nHashedId,roHelpTextString))
	{
		roHelpTextString = "";
	}
}

//-------------- declared position -------------- -------------- -------------- 
void cned_element_manager::set_decl_position(ned_ident idElement,const ned_position & roPosition)
{
	long nHashedId = _pre_hash(idElement);
	if(roPosition == ned_position())
	{
		m_oDeclPositionMap.RemoveKey(nHashedId);
	}
	else
	{
		m_oDeclPositionMap[ nHashedId ] = roPosition;
	}
}

bool cned_element_manager::get_decl_position(ned_ident idElement,ned_position & roPosition) const
{
	long nHashedId = _pre_hash(idElement);
	return (m_oDeclPositionMap.Lookup(nHashedId,roPosition) != FALSE);
}

//-------------- short key manager -------------- -------------- 
void cned_element_manager::set_shortkey(ned_ident Ident,SCP<cnui_shortkey> & rpoShortKeySP)
{
	long nHashedId = _pre_hash(Ident);
	if(rpoShortKeySP.PointsObject())
	{
		m_oShortKeyMap[ nHashedId ] = rpoShortKeySP;
	}
	else
	{
		VERIFY(m_oShortKeyMap.RemoveKey(nHashedId));
	}
}

SCP<cnui_shortkey> cned_element_manager::get_shortkey(ned_ident Ident)
{
	long nHashedId = _pre_hash(Ident);
	SCP<cnui_shortkey> poShortKeySP;
	m_oShortKeyMap.Lookup(nHashedId,poShortKeySP);
	return poShortKeySP;
}

ned_ident cned_element_manager::lookup_shortkeys(const ned_action_kbd & roActionKBD) const
{
	UINT nUpperKeyCode = UINT(ToUpper(TCHAR(roActionKBD.get_keycode())));
	POSITION pos = m_oShortKeyMap.GetStartPosition();
	while(pos)
	{
		long nHashedId;
		SCP<cnui_shortkey> poShortKeySP;
		m_oShortKeyMap.GetNextAssoc(pos,nHashedId,poShortKeySP);
		ASSERT(poShortKeySP.PointsObject());

		//exact match is required
		if(poShortKeySP->IsAlt()  == roActionKBD.is_ALT()  && 
		   poShortKeySP->IsCtrl() == roActionKBD.is_CTRL() &&
		   poShortKeySP->IsShift()== roActionKBD.is_SHIFT() &&
				(poShortKeySP->GetKey() == nUpperKeyCode || 
				 poShortKeySP->GetKey() == roActionKBD.get_keycode())
			)
		{
			return _post_hash(nHashedId);
		}
	}
	return NEDID_NOTHING;
}

//--------- paint rect management ----------------------
#ifdef _DEVELOPER_EDITION_
bool _debug_bDraw_invalidated_as_red = false;
void cned_element_manager::_debug_draw_invalidated_as_red(bool bDebugDraw)
{
	_debug_bDraw_invalidated_as_red = bDebugDraw;
}
#endif

bool cned_element_manager::invalidate_paint_rect(ned_ident idElement,long nFragment)
{
	ng_rect oRect;
	if(get_paint_rect(idElement,nFragment,oRect))
	{
		switch(nFragment)
		{
		case MAIN_PAINT_RECT_ID:
		case 1:
			{
				cned_element_entry & roEntry = _entry(idElement);
				if(nFragment == MAIN_PAINT_RECT_ID)
				{
					roEntry.m_bPaintRect0 = false;
				}
				else
				{
					roEntry.m_bPaintRect1 = false;
				}
			}
		break;
		default:
			{
				__int64 i64Key = longlong(long(idElement),nFragment);
				VERIFY(m_oPaintRectMap.RemoveKey(i64Key));
			}
		}

		invalidate_paint_rect(oRect);
		return true;
	}
	else
	{
		return false;
	}
}

void cned_element_manager::invalidate_paint_rect(const ng_rect & roAbsoluteRect)
{
	m_poArenaManager->invalidate_paint_rect(roAbsoluteRect);
#ifdef _DEVELOPER_EDITION_
	
	if(_debug_bDraw_invalidated_as_red)
	{
		HWND hWindow = m_poArenaManager->get_os_window();
		ng_dc oDebugDC(::GetDC(hWindow));
		oDebugDC.fill_rect_hg(roAbsoluteRect,Red,Red);
		::ReleaseDC(hWindow,oDebugDC.get_hdc());
	}

#endif
}

//------------------------------------------------------------------------------------
ned_declattrinx cned_element_manager::get_inx_for_declattr(const ned_declattributes & roDeclAttrib)
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_inx_for_declattr(roDeclAttrib);
}

const ned_declattributes & cned_element_manager::get_declattr_on_inx(const ned_declattrinx nAttribInx) const
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_declattr_on_inx(nAttribInx);
}

//------------------------------------------------------------------------------------
SCP<ng_image> cned_element_manager::get_image(const CSmartOleVariant & roImageSourceSOV,SCP<ng_image_request> poRequestSP)
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_image(roImageSourceSOV,poRequestSP);
}

SCP<ng_image> cned_element_manager::get_special_image(eSpecialImage eImage)
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_special_image(eImage);
}
//------------------------------------------------------------------------------------
// miscelanous providers 
//------------------------------------------------------------------------------------


//-------------- style -------------- -------------- -------------- 
SCP<cned_style> cned_element_manager::get_style(long StyleId)
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_style(StyleId);
}

//------------------------------------------------------------------------------------
// miscelanous providers - transfer
//------------------------------------------------------------------------------------
long cned_element_manager::_find_transfer_index(long nHashedId) const
{
	for(long iter = m_oTransferArray.GetUpperBound(); iter >= 0; iter--)
	{
		if(m_oTransferArray[ iter ].m_nHashedId == nHashedId)
		{
			return iter;
		}
	}
	return -1;
}

void cned_element_manager::set_transfer(ned_ident Ident,SCP<nui_transfer> & rpoTransferSP)
{
	long nHashedId = _pre_hash(Ident);
	long nIndex = _find_transfer_index(nHashedId);

	if(rpoTransferSP.PointsObject())
	{
		if(nIndex >= 0)
		{
			m_oTransferArray[ nIndex ].m_poTransferSP = rpoTransferSP;
		}
		else
		{
			m_oTransferArray.Add(nui_transfer_entry(nHashedId,rpoTransferSP));
		}
	}
	else
	{
		if(nIndex >= 0)
		{
			m_oTransferArray.RemoveAt(nIndex);
			if(m_nTransferIterator >= nIndex)
			{
				m_nTransferIterator--;
			}
		}
	}
}

SCP<nui_transfer> cned_element_manager::get_transfer(ned_ident Ident)
{
	SCP<nui_transfer> poTransferSP;

	long nHashedId = _pre_hash(Ident);
	long nIndex = _find_transfer_index(nHashedId);
	if(nIndex >= 0)
	{
		poTransferSP = m_oTransferArray[ nIndex ].m_poTransferSP;
	}
	return poTransferSP;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

HWND cned_element_manager::get_os_window() const
{
	ASSERT(m_poArenaManager);
	return m_poArenaManager->get_os_window();
}

//------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
void cned_element_manager::set_sys_disable(bool bSysDisable)
{
	m_bSysDisabled = bSysDisable;
	
	if(get_focus_element() != NEDID_NOTHING)
	{
		//remove focus from element being effectivelly disabled
		if(is_element_disabled(get_focus_element()))
		{
			m_idFocus = NEDID_NOTHING;
			
			//just to start invalidating process
			invalidate_paint_rect(ng_rect(0,0,0,0));
		}
	}
}

void cned_element_manager::set_layout_invalid_to_all_in_array
	(CArray<cned_element_entry,cned_element_entry & > & roArray)
{
	for(long iter = 0; iter <= roArray.GetUpperBound(); iter++)
	{
		cned_element_entry & roEntry = roArray[iter];
		if(roEntry.m_poElement != NULL)
		{
			roEntry.m_poElement->set_measure_pending();
		}
		else
		{
			roEntry.m_oMiniInfo.set_measure_pending();
		}
	}
}

void cned_element_manager::set_layout_invalid_to_all()
{
	set_layout_invalid_to_all_in_array(m_oFixedIdElementArray);
	set_layout_invalid_to_all_in_array(m_oAutoIdElementArray);
	set_layout_invalid_to_all_in_array(m_oHighIdElementArray);

	_flush_font_cache();
}

//-----------------------------------------------------------------------------------
ned_event_command_list::ned_event_command_list(ned_ident nFiringElement) :
	ned_event_info__(nFiringElement),
	m_poCommandListSP(NewSCP(new CCommandList()))
{
}

SCP<CCommandList> ned_event_command_list::get_command_list()
{
	return m_poCommandListSP;
}

SCP<CCommandList> ned::_retrieve_command_list(ned_event_info__ * poEventInfo)
{
	ASSERT(poEventInfo != NULL);
	ASSERT(poEventInfo->get_type() == eit_command_list);
	ned_event_command_list * poECL = dynamic_cast<ned_event_command_list*>(poEventInfo);
	ASSERT(poECL != NULL);
	return poECL->get_command_list();
}

ng_point & ned::_retrieve_command_list_start_point(ned_event_info__ * poEventInfo)
{
	ASSERT(poEventInfo != NULL);
	ASSERT(poEventInfo->get_type() == eit_command_list);
	ned_event_command_list * poECL = dynamic_cast<ned_event_command_list*>(poEventInfo);
	ASSERT(poECL != NULL);
	return poECL->m_oStartPoint;
}

SCP<CCommandList> ned::_create_or_get_command_list(ned_action_result & roResult,ned_ident idTarget)
{
	//jeœli jeszcze nie ma listy komend - utwórz j¹
	if(roResult.get_info(0).PointsNull())
	{
		SCP<ned_event_command_list> poEventCmdListSP = NewSCP(new ned_event_command_list(idTarget));
		roResult.add_info(poEventCmdListSP);
	}
	
	//teraz zawsze istnieje
	return _retrieve_command_list(roResult.get_info(0));
}

//------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// font provider / manager
//---------------------------------------------------------------------------------------

void cned_element_manager::_flush_font_cache()
{
	for(long iter = 0; iter <= m_oFontArray.GetUpperBound(); iter++)
	{
		m_oFontArray[iter].m_poFontSP = 0;
	}
}

ned_fontinx cned_element_manager::get_inx_for_font_spec(const ned_font_spec & roFontSpec)
{
	ng_string oFontDescString;
	roFontSpec.to_string(oFontDescString);
	ned_fontinx nFontInx;

	if(!m_oFontInxMap.Lookup(oFontDescString,nFontInx))
	{
		nFontInx = ned_fontinx(1 + m_oFontInxMap.GetCount());
		m_oFontInxMap[ oFontDescString ] = nFontInx;
		m_oFontArray.SetAtGrow(long(nFontInx),FontWithDescription(roFontSpec,SCP<ng_font>()));
	}
	return nFontInx;
}

const ned_font_spec & cned_element_manager::get_font_spec_on_inx(const ned_fontinx nFontInx)
{
	ASSERT(long(nFontInx) >= 0 && long(nFontInx) <= m_oFontArray.GetUpperBound());
	return m_oFontArray[ long(nFontInx) ].m_oFontSpec;
}

static const long alRawFontSize[] =
{
	10000 * 4,			//0
	10000 * 6,			//1
	10000 * 7,			//2
	10000 * 8,			//3
	10000 * 9,			//4
	10000 * 10,			//5
	10000 * 11,			//6
	10000 * 12,			//7
	10000 * 14,			//8
	10000 * 16,			//9
	10000 * 18,			//10
	10000 * 20,			//11
	10000 * 22,			//12
	10000 * 24,			//13
	10000 * 26,			//14
	10000 * 28,			//15
	10000 * 32,			//16
	10000 * 36,			//17
	10000 * 40,			//18
	10000 * 48,			//19
	10000 * 60,			//20
	10000 * 72,			//21
	10000 * 144,		//22
};

static long _raw_font_size_from_decl_size(long nSize)
{
	if(nSize < 0 || nSize >= sizeof(alRawFontSize) / sizeof(alRawFontSize[0]))
	{
		ASSERT(false);
#ifdef _DEBUG
		return alRawFontSize[7];			
#else
		return alRawFontSize[3];	//w przypadku b³êdu zwróæ œrodkowy (RELEASE) lub bardzo du¿y (DEBUG)
#endif
	}
	return alRawFontSize[ nSize ];
}

SCP<ng_font> cned_element_manager::get_font_on_inx(const ned_fontinx nFontInx) 
{
	ASSERT(long(nFontInx) >= 0 && long(nFontInx) <= m_oFontArray.GetUpperBound());
	if(m_oFontArray[ long(nFontInx) ].m_poFontSP.PointsNull())
	{
		const ned_font_spec & roFontSpec = m_oFontArray[ long(nFontInx) ].m_oFontSpec;
	
		long nRawSize = (m_oScaling.get_zoom() * _raw_font_size_from_decl_size(roFontSpec.m_nSize) / 100);
		
		ASSERT(!roFontSpec.m_oFontNameString.IsEmpty());

		m_oFontArray[ long(nFontInx) ].m_poFontSP = ng_font::create(roFontSpec.m_oFontNameString,nRawSize,
			roFontSpec.m_bBold,
			roFontSpec.m_bItalic,
			roFontSpec.m_bStrikeThrough,
			roFontSpec.m_bUnderLine,
			roFontSpec.m_sCharSet
			);
	}
	
	ASSERT(m_oFontArray[ long(nFontInx) ].m_poFontSP.PointsObject());
	return m_oFontArray[ long(nFontInx) ].m_poFontSP;
}

//---------------------------------------------------------------------------------------
// ned_font_spec methods
//---------------------------------------------------------------------------------------
void ned_font_spec::to_string(ng_string & roFontSpecString) const
{
	roFontSpecString.Format("%d\t%d\t%d\t%d\t%d\t%d\t%s",
		long(m_bBold),long(m_bItalic),
		long(m_bStrikeThrough),
		long(m_bUnderLine),long(m_nSize),
		long(m_sCharSet),
		m_oFontNameString);
}

void ned_font_spec::from_string(LPCTSTR lpFontSpecString)
{
	CStringArray oStringArray;
	SplitString(ng_string(lpFontSpecString),oStringArray,'\t',true);
	m_bBold				= (oStringArray[0][0] == '1');
	m_bItalic			= (oStringArray[1][0] == '1');
	m_bStrikeThrough	= (oStringArray[2][0] == '1');
	m_bUnderLine		= (oStringArray[3][0] == '1');
	m_nSize				= _ttol(oStringArray[4]);
	m_sCharSet			= SHORT(_ttol(oStringArray[5]));
	m_oFontNameString	= oStringArray[6];
}

//-----------------------------------------------------------------------

struct TransferTypeAndName
{
	LPCTSTR m_lpName;
	eTransferType	m_eType;
};

static TransferTypeAndName _g_TransferNames[] =
{
	{ _T("edit_field"),		ett_edit_field		},
	{ _T("custom"),			ett_custom			},
	{ _T("row_custom"),		ett_row_custom		},
	{ _T("row_edit_field"),	ett_row_edit_field	},
	{ _T("edit_ref"),		ett_edit_ref		},
	{ _T("row_edit_ref"),	ett_row_edit_ref	},
	{ _T("grid_list"),		ett_grid_list		},
	{ _T("row_nr"),			ett_row_number		},
	{ _T("display_text"),	ett_display_text	},
	{ _T("display_ref_text"),ett_display_ref_text},
	{ NULL,					ett_none			}
};

static eTransferType TransferType_from_Name(LPCTSTR lpModeName)
{
	for(TransferTypeAndName * pNAFN = _g_TransferNames; pNAFN->m_lpName; pNAFN++)
	{
		if(_tcsicmp(lpModeName,pNAFN->m_lpName) == 0)
		{
			return pNAFN->m_eType;
		}
	}
	return ett_none;
}

SCP<nui_transfer> create_transfer(const ng_string & roModeString)
{
	SCP<nui_transfer> poTransferSP;
	eTransferType eType = TransferType_from_Name(roModeString);

	switch(eType)
	{
	case ett_none:
		//to_do: zmieniæ string w zasobach
		ThrowNavoException1(ERCO_PARSE_INVALID_MODE,IDPAGE_NOTAVAILABLE,roModeString);
	break;
	case ett_custom:
	case ett_row_custom:
	case ett_row_number:
	case ett_display_text:
		poTransferSP = NewSCP<nui_transfer>(new nui_transfer(eType));
	break;
	case ett_edit_field:
	case ett_grid_list:
	case ett_row_edit_field:
	case ett_display_ref_text:
		poTransferSP = NewSCP<nui_transfer>(new nui_transfer_1(eType));
	break;
	case ett_edit_ref:
	case ett_row_edit_ref:
		poTransferSP = NewSCP<nui_transfer>(new nui_transfer_2(eType));
	break;
	case ett_grid_cursor:
		//ned_to_do:
	default:
		//ned_to_do: zmieniæ string w zasobach
		ThrowNavoException1(ERCO_PARSE_INVALID_MODE,IDPAGE_NOTAVAILABLE,roModeString);
	}
	
	ASSERT(poTransferSP.PointsObject());

	return poTransferSP;
}
