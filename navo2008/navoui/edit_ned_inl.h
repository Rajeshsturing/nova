/*
	NAVO Enterprise 2003
	2003-08-20

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych

	inline part
*/

#ifndef _EDIT_NED_INL_H_
#define _EDIT_NED_INL_H_

namespace ned
{

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline cned_edit__::cned_edit__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_element_(poManager,eType,idThis),
	m_nDeclCharWidth(1),
	m_bDataValid(true),
	m_bInfraUpdPending(true)
{
	set_prop_tabstop(true);
}


inline cned_edit__::cstate::cstate() :
	m_nCharScroll(0),
	m_nCharSelFirst(0),
	m_nCharSelLast(0),
	m_bCaretOn(true),
	m_nCharCaret(0),
	m_XLeftCaretLU(0),
	m_XSelFirstLU(0),
	m_XSelLastLU(0),
	m_XTextWidthLU(0)
{
}

inline long cned_edit__::cstate::get_caret_pos() const
{
	return m_nCharCaret;
}

inline bool cned_edit__::cstate::is_selection() const
{
	ASSERT(m_nCharSelFirst <= m_nCharSelLast);
	ASSERT(m_nCharSelFirst >= 0);
	return m_nCharSelFirst != m_nCharSelLast;
}

inline void cned_edit__::cstate::clear_selection()
{
	m_nCharSelFirst = get_caret_pos();
	m_nCharSelLast = get_caret_pos();
}

inline void cned_edit__::cstate::move_caret_by(long nDelta,bool bSelectionMode)
{
	move_caret_to(get_caret_pos() + nDelta,bSelectionMode);
}
		
inline void cned_edit__::cstate::copy_to(cned_edit__::cstate & roState) const
{
	roState.m_oBufferString		= m_oBufferString;
	roState.m_nCharScroll		= m_nCharScroll;
	roState.m_nCharSelFirst		= m_nCharSelFirst;
	roState.m_nCharSelLast		= m_nCharSelLast;
	roState.m_bCaretOn			= m_bCaretOn;
	roState.m_nCharCaret		= m_nCharCaret;
}

inline cned_edit__::cstate::cstate(const cned_edit__::cstate & roState) :
	m_oBufferString(roState.m_oBufferString),
	m_nCharScroll(roState.m_nCharScroll),
	m_nCharSelFirst(roState.m_nCharSelFirst),
	m_nCharSelLast(roState.m_nCharSelLast),
	m_bCaretOn(roState.m_bCaretOn),
	m_nCharCaret(roState.m_nCharCaret),
	m_XLeftCaretLU(roState.m_XLeftCaretLU),
	m_XSelFirstLU(roState.m_XSelFirstLU),
	m_XSelLastLU(roState.m_XSelLastLU),
	m_XTextWidthLU(roState.m_XTextWidthLU)
{
}

//----------------------------------------------------------------
//	buffer and caret management
//----------------------------------------------------------------
inline void cned_edit__::cstate::move_caret_to(long nNewCaretPosition,bool bSelectionMode)
{
	ASSERT(nNewCaretPosition >= 0 && nNewCaretPosition <= m_oBufferString.GetLength());
	bool bWasSelection = is_selection();
	long nOldCaretPosition = get_caret_pos();
	
	m_nCharCaret = nNewCaretPosition;
	
	if(bSelectionMode)
	{
		if(bWasSelection)		//rozszerz lub zwêŸ selekcjê zgodnie z ruchem kursora
		{
			if(m_nCharSelFirst == nOldCaretPosition)
			{
				m_nCharSelFirst = get_caret_pos();
			}
			else if(m_nCharSelLast == nOldCaretPosition)
			{
				m_nCharSelLast = get_caret_pos();
			}
			if(m_nCharSelFirst > m_nCharSelLast)	//swap selection
			{
				long nTmp = m_nCharSelFirst;
				m_nCharSelFirst = m_nCharSelLast;
				m_nCharSelLast = nTmp;
			}
		}
		else
		{
			if(get_caret_pos() > nOldCaretPosition)
			{
				ASSERT(m_nCharSelFirst == nOldCaretPosition);
				m_nCharSelLast = get_caret_pos();
			}
			else
			{
				ASSERT(m_nCharSelLast == nOldCaretPosition);
				m_nCharSelFirst = get_caret_pos();
			}
		}
	}
	else
	{
		clear_selection(); //poci¹gnij za sob¹ selekcjê
	}
	ASSERT(m_nCharSelFirst == m_nCharCaret || m_nCharSelLast == m_nCharCaret);
	ASSERT(m_nCharSelFirst <= m_nCharSelLast);
}


inline void cned_edit__::cstate::insert_char(UINT nChar)
{
	delete_selected_chars();

	ASSERT(get_caret_pos() >= 0);			//jeœli piszemy tu musimy mieæ ustawiony kursor
	long nCaretPos = get_caret_pos();
	if(nCaretPos == m_oBufferString.GetLength())
	{
		m_oBufferString += TCHAR(nChar);
	}
	else
	{
		m_oBufferString.Insert(nCaretPos,TCHAR(nChar));
	}
	move_caret_by(+1,false);
}

inline void cned_edit__::cstate::delete_char()
{
	ASSERT(get_caret_pos() >= 0);			//jeœli piszemy tu musimy mieæ ustawiony kursor
	if(get_caret_pos() < m_oBufferString.GetLength())
	{
		m_oBufferString.Delete(get_caret_pos(),1);
	}
}

inline void cned_edit__::cstate::overtype_char(UINT nChar)
{
	ASSERT(get_caret_pos() >= 0);			//jeœli piszemy tu musimy mieæ ustawiony kursor
	ASSERT(get_caret_pos() < m_oBufferString.GetLength());
	m_oBufferString.SetAt(get_caret_pos(),TCHAR(nChar));
}

inline bool cned_edit__::cstate::delete_selected_chars()
{
	if(is_selection())
	{
		long nStartingPos = m_nCharSelFirst;
		long nCount = m_nCharSelLast - m_nCharSelFirst;
		m_oBufferString.Delete(nStartingPos,nCount);
		if(get_caret_pos() > nStartingPos)
		{
			move_caret_by(-nCount,false);
		}
		clear_selection();
		return true;
	}
	else
	{
		return false;
	}
}


inline void cned_edit__::_set_new_buffer_text(cstate & roState,const ng_string & roString)
{
	roState.m_oBufferString = roString;
	if(roState.get_caret_pos() > roState.m_oBufferString.GetLength())
	{
		roState.move_caret_to(roState.m_oBufferString.GetLength(),false);
	}
}

inline void cned_edit__::_after_act_move(long nNewCaretPos,bool bShift)
{
	m_State.move_caret_to(nNewCaretPos,bShift);
}

inline void cned_edit__::select_to_end()
{
	long nCaretPos = m_State.get_caret_pos();
	m_State.move_caret_to(m_State.m_oBufferString.GetLength(),false);
	m_State.move_caret_to(nCaretPos,true);
}

inline void cned_edit__::move_caret_to(long nNewCaretPosition,bool bSelectionMode)
{
	m_State.move_caret_to(nNewCaretPosition,bSelectionMode);
}

//------ property GET -----------------
inline SCP<IDispatch> cned_edit__::get_prop_suggestion()
{
	return m_poSuggestionDispatchSP;
}

inline long cned_edit__::get_prop_charwidth() const
{
	return m_nDeclCharWidth;
}

inline bool cned_edit__::get_prop_valid() const
{
	return m_bDataValid;
}

inline void cned_edit__::get_prop_value(CSmartOleVariant & roSOV)
{
	if(!buffer2variant(roSOV))
	{
		//ned_to_do:: co zwracaæ ??
	}
}

//------ property SET -----------------

inline void cned_edit__::set_prop_suggestion(SCP<IDispatch> & rpoDispatchSP)
{
	m_poSuggestionDispatchSP = rpoDispatchSP;
}

inline void cned_edit__::set_prop_charwidth(long nCharWidth)
{
	ASSERT(nCharWidth >= 1);
	if(get_prop_charwidth() == nCharWidth)
	{
		return;
	}
	m_nDeclCharWidth = nCharWidth;

	_size_info_dirty();
	_vse_dirty();

}

inline void cned_edit__::set_prop_valid(bool bValid)
{
	if(get_prop_valid() == bValid)
	{
		return;
	}
	m_bDataValid = bValid;

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_edit__::paste_from_string(const ng_string & roString)
{
	_act_paste_from_string(roString);
}

//------------------------------------------------------------------------------------
inline ng_color cned_edit__::_get_text_color(bool bTreeDisabled)
{
	if(_metrics().is_high_contrast())
	{
		return get_prop_forecolor();
	}
	else
	{
		return (get_prop_disabled() || bTreeDisabled) ? 
			ng_color::system(COLOR_GRAYTEXT) : get_prop_forecolor();
	}
}

//--------------event handlers ---------------------------------------
inline eCursorType cned_edit__::on_event_set_cursor(const ng_point &)
{
	if(!get_prop_disabled())
	{
		return ect_ibeam;
	}
	return ect_default;
}

//---------------------------------------------------------
inline void cned_edit__::_set_infra_update_pending()
{
	m_bInfraUpdPending = true;
}

//-------------- fill clone -------------- -------------- -------
inline void cned_edit__::_copy_properties(cned_edit__ * poDestinationEdit)
{
	poDestinationEdit->m_bDataValid = m_bDataValid;
	poDestinationEdit->m_nDeclCharWidth = m_nDeclCharWidth;
	m_State.copy_to(poDestinationEdit->m_State);
	poDestinationEdit->_set_infra_update_pending();

	//dontcopy m_poSuggestionDispatchSP
}

inline void cned_edit__::fill_clone(cned_element * poDestination)
{
	cned_rect_element_::fill_clone(poDestination);
	cned_edit__ * poDestEdit = cast_ui<cned_edit__>(poDestination);
	_copy_properties(poDestEdit);
}

//-------- page breaking ---------------------------------
inline void cned_edit__::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_rect_element_::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_edit__ * poDestEdit = cast_ui<cned_edit__>(poDestination);
	_copy_properties(poDestEdit);
}

inline void cned_edit__::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	_get_text_rect(ng_point().offset(m_oVectorSize),roLocalRect);
	//ned_to_do: zastanowiæ siê czy to coœ pomaga ?
	roLocalRect.set_width(m_State.m_XTextWidthLU);
}

//---------------------------------------------------------
// dimension information and calculations
//---------------------------------------------------------

inline void cned_edit__::_get_back_rect(const ng_point & roCurrentPoint,ng_rect & roBackRect) const
{
	roBackRect = ng_rect(roCurrentPoint,m_oActualSize);
	roBackRect.inflate(-_get_frame_px_width(),-_get_frame_px_width());
}

inline void cned_edit__::_get_text_rect(const ng_point & roCurrentPoint,ng_rect & roTextRect) const
{
	_get_back_rect(roCurrentPoint,roTextRect);

	roTextRect.inflate(-_metrics().edit().get_left_margin(),-_metrics().edit().get_top_margin(),
		-_metrics().edit().get_right_margin(),-_metrics().edit().get_bottom_margin());

	if(eal_right == get_prop_alignment())
	{
		ng_xdist xOffset = max(0,roTextRect.get_width() - m_State.m_XTextWidthLU);
		roTextRect.set_left(roTextRect.get_left() + xOffset);
	}
}

inline void cned_edit__::get_visible_buffer(ng_string & roString) const
{
	roString = m_State.m_oBufferString;
}

//------------------------------------------------------------------------------------
// helpers
//------------------------------------------------------------------------------------

inline long _act_move_left_word(LPCTSTR lpText,long nPos)
{
	//pomiñ spacje ale nie newline
	while(nPos > 0 && IsSpace(lpText[nPos-1])  && (lpText[nPos-1] != MULTILINE_NEWLINE_CHAR))
	{
		nPos--;
	}
	if(nPos > 0)
	{
		if(lpText[nPos-1] == MULTILINE_NEWLINE_CHAR)
		{
			return --nPos;
		}
	}
	//pomiñ s³owo
	while(nPos > 0 && !IsSpace(lpText[nPos-1]))
	{
		nPos--;
	}
	return nPos;
}

inline long _act_move_right_word(LPCTSTR lpText,long nPos,long nTextLen)
{
	//pomiñ spacje ale nie newline
	while(nPos < nTextLen && IsSpace(lpText[nPos]) && (lpText[nPos] != MULTILINE_NEWLINE_CHAR))
	{
		nPos++;
	}
	if(nPos < nTextLen)
	{
		if(lpText[nPos] == MULTILINE_NEWLINE_CHAR)
		{
			return ++nPos;
		}
	}
	//pomiñ s³owo
	while(nPos < nTextLen && !IsSpace(lpText[nPos]))
	{
		nPos++;
	}
	//pomiñ spacje ale nie newline
	while(nPos < nTextLen && IsSpace(lpText[nPos]) && (lpText[nPos] != MULTILINE_NEWLINE_CHAR))
	{
		nPos++;
	}
	return nPos;
}


}

#else
	#error __FILE__ already included
#endif
