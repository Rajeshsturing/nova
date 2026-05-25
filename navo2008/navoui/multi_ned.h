/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_multiline		/ <multiline>
		kontrolka edycji tekstów wieloliniowych
*/

#ifndef _MULTIEDIT_NED_H_
#define _MULTIEDIT_NED_H_

namespace ned
{
class multiline_measurer;

class cned_multiedit : public cned_rect_container_, public scroll_helper__
{
public:
	//------ property GET -----------------
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	ng_string get_prop_text() const;
	virtual void get_prop_tooltip_text(ng_string & roText) const;
	bool get_prop_use_enter() const;
	bool get_prop_valid() const;
	//------ property SET -----------------
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_text(const ng_string & roTextString);
	void set_prop_use_enter(bool bUseEnter);
	void set_prop_valid(bool bValid);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();

	virtual ned_ident find_element_from_point(const ng_point & roPoint);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);

	virtual void get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const;
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);
	virtual void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);
	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);

	void _fill_command_list(ned_action_result & roResult);

//-------------- rendering support -------------------
	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);
	virtual void render(cned_renderer_ & roRenderer);
	virtual void get_metrics(const ned_measure_param & roMParam,cned_metrics & roMetrics);
private:
	cned_multiedit(cned_element_manager * poManager,const ned_ident idThis);

	void _render_finish_line(rendering_line & roRendLine,const multiline_measurer & roMeasurer,
		bool bWithNewline,const ng_string & roInternalString);
	//--------- drawing helpers ------------------
	void _draw_internals(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _invalidate_internal_paint();
	void _invalidate_caret_paint();

	void _draw_caret(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _draw_frame(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);

	ng_color _get_text_color(bool bTreeDisabled);
	//---------------------------------------------------------
	// dimension information and calculations
	//---------------------------------------------------------
	ng_xdist _get_frame_px_width() const;
	void _get_back_rect(const ng_point & roCurrentPoint,ng_rect & roBackRect) const;
	void _get_text_rect(const ng_point & roCurrentPoint,ng_rect & roRect) const;
	void _get_caret_rect(const ng_point & roCurrentPoint,ng_rect & roRect) const;

	long _get_char_pos_for_line_and_dx(const ng_xdist dxOffset,long nLine,ng_dc & roDC);
	//---------------------------------------------------------
	// kbd actions
	//---------------------------------------------------------
	bool _dispatch_action(const ned_action_kbd & roActionKBD);
	class cstate;
	void _on_successfull_action(const ned_action__ & roAction,const cstate & roOldState,ned_action_result & roResult);

	bool _act_data(UINT nTranslatedChar);
	long _act_move(UINT nVKCode,bool bWithCtrl,ng_dc & roDC);
	bool _act_delete(bool bWithShift);
	bool _act_backspace(bool bWithShift);

	bool _act_paste();
	bool _act_cut();
	void _act_copy();

	bool _act_paste_from_string(const ng_string & roString);
	void _act_copy_to_string(ng_string & roString);
	bool _act_cut_to_string(ng_string & roString);
	//---------------------------------------------------------
	void _set_infra_update_pending();
	void _update_infrastructure(ng_dc & roDC,const cstate & roOldState,bool bWhileRendering);
	bool _layout_lines(const multiline_measurer & roTextMeasurer);
	long _get_line_for_char_pos(long nCharPos) const;

	void _get_dx_and_line_for_char_pos(long nCharPos,const multiline_measurer & roMeasurer,ng_xdist & rdxOffset,long & rnLine) const;

	ng_ydist _get_actual_text_height() const;
	//---------------------------------------------------------
	//--------- buffer manipulation --------------
	class cstate
	{
	public:
		cstate();
		cstate(const cstate & roState);

		long get_caret_pos() const;
		long get_start_of_selection() const;
		long get_end_of_selection() const;

		long get_buffer_size() const;
		void move_caret_to(long nNewCaretPosition,bool bSelectionMode);
		void move_caret_by(long nDelta,bool bSelectionMode);
		void clear_selection();
		bool delete_selected_chars();	//usuwa z bufora znaki w selekcji
		bool is_selection() const;

		const ng_string & get_buffer() const;
		//--- only allowed buffer manipulation --- 
		void __delete_from_buffer(long nPosition,long nCount);
		void __insert_to_buffer(long nPosition,TCHAR cChar);
		void __insert_to_buffer(long nPosition,const ng_string & roString);
		void __set_buffer(const ng_string & roString);

		long get_invalid_char() const;
		void validate_up_to_char(long nPosition);
		void copy_to(cstate & roState) const;

		ng_xdist	m_dxCaretPos;	//offset 'caret' od linii
		long		m_nCaretLine;	//linia w której jest caret
		ng_xdist	m_dxSelFirstPos;//offset pocz¹tku selekcji (w linii)
		long		m_nSelFirstLine;//linia w której zaczyna siê selekcja
		ng_xdist	m_dxSelLastPos;	//offset koñca selekcji	(w linii)
		long		m_nSelLastLine; //linia w której koñczy siê selekcja
		ng_ydist	m_dyLineHeight;	//wysokoœæ linii

		bool		m_bCaretOn;			//czy 'caret' jest w³¹czony
	private:
		ng_string m_oBufferString;	//tekstowy bufor edycyjny
		long	m_nCharSelFirst;	//pierwszy zaznaczony znak
		long	m_nCharSelLast;		//ostatni zaznaczony
		long	m_nCharCaret;		//po³o¿enie 'careta' (w buforze)
		long	m_nInvalidChar;		//pierwszy znak wymagaj¹cy layoutu linii
	};

	cstate		m_State;
	multiline_manager	m_oMLM;					//multi line manager

	bool		m_bDataValid;		//czy dane s¹ prawid³owe (akceptowalne przez aplikacjê)
	bool		m_bUseEnter;		//dzia³anie klawisza ENTER - true oznacza now¹ liniê, false - utratê focusa

	bool		m_bInfraUpdPending;	//czy jest potrzeba aktualizacji internal

	friend class cned_element_manager;

	static const long INTERNAL_PAINT_RECT_ID;
	static const long CARET_PAINT_RECT_ID;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_multiedit::cstate::cstate():
	m_nCharSelFirst(0),
	m_nCharSelLast(0),
	m_bCaretOn(true),
	m_nCharCaret(0),
	m_dxCaretPos(0),
	m_nCaretLine(0),
	m_dxSelFirstPos(0),
	m_nSelFirstLine(0),
	m_dxSelLastPos(0),
	m_nSelLastLine(0),
	m_dyLineHeight(0),
	m_nInvalidChar(MAXLONG)
{
}

inline cned_multiedit::cstate::cstate(const cned_multiedit::cstate & roState) :
	m_nCharSelFirst(roState.m_nCharSelFirst),
	m_nCharSelLast(roState.m_nCharSelLast),
	m_bCaretOn(roState.m_bCaretOn),
	m_nCharCaret(roState.m_nCharCaret),
	m_dxCaretPos(roState.m_dxCaretPos),
	m_nCaretLine(roState.m_nCaretLine),
	m_dxSelFirstPos(roState.m_dxSelFirstPos),
	m_nSelFirstLine(roState.m_nSelFirstLine),
	m_dxSelLastPos(roState.m_dxSelLastPos),
	m_nSelLastLine(roState.m_nSelLastLine),
	m_dyLineHeight(roState.m_dyLineHeight),
	m_nInvalidChar(roState.m_nInvalidChar),
	m_oBufferString(roState.m_oBufferString)
{
}

inline void cned_multiedit::cstate::copy_to(cstate & roState) const
{
	roState.m_nCharSelFirst	= m_nCharSelFirst;
	roState.m_nCharSelLast	= m_nCharSelLast;
	roState.m_bCaretOn		= m_bCaretOn;
	roState.m_nCharCaret	= m_nCharCaret;
	roState.m_nInvalidChar	= 0;
	roState.m_oBufferString = m_oBufferString;
}

//--------------------------------------------------------------------
//--- only allowed buffer manipulation --- 
//--------------------------------------------------------------------
inline void cned_multiedit::cstate::__delete_from_buffer(long nPosition,long nCount)
{
	m_oBufferString.Delete(nPosition,nCount);
	m_nInvalidChar = min(m_nInvalidChar,nPosition);
}

inline void cned_multiedit::cstate::__insert_to_buffer(long nPosition,TCHAR cChar)
{
	m_oBufferString.Insert(nPosition,cChar);
	m_nInvalidChar = min(m_nInvalidChar,nPosition);
}

inline void cned_multiedit::cstate::__insert_to_buffer(long nPosition,const ng_string & roString)
{
	m_oBufferString.Insert(nPosition,roString);
	m_nInvalidChar = min(m_nInvalidChar,nPosition);
}

inline void cned_multiedit::cstate::__set_buffer(const ng_string & roString)
{
	m_oBufferString = roString;
	m_nInvalidChar = 0;
}

inline long cned_multiedit::cstate::get_buffer_size() const
{
	return m_oBufferString.GetLength();
}

inline const ng_string & cned_multiedit::cstate::get_buffer() const
{
	return m_oBufferString;
}

//--------------------------------------------------------------------
inline long cned_multiedit::cstate::get_invalid_char() const
{
	return m_nInvalidChar; 
}

inline void cned_multiedit::cstate::validate_up_to_char(long nPosition)
{
	ASSERT(m_nInvalidChar <= nPosition);
	m_nInvalidChar = nPosition;
}

//--------------------------------------------------------------------
// caret manipulation
//--------------------------------------------------------------------
inline long cned_multiedit::cstate::get_caret_pos() const
{
	return m_nCharCaret;
}

inline long cned_multiedit::cstate::get_start_of_selection() const
{
	return m_nCharSelFirst;
}

inline long cned_multiedit::cstate::get_end_of_selection() const
{
	return m_nCharSelLast;
}

inline bool cned_multiedit::cstate::is_selection() const
{
	ASSERT(get_start_of_selection() <= get_end_of_selection());
	ASSERT(get_start_of_selection() >= 0);
	return get_start_of_selection() != get_end_of_selection();
}

inline void cned_multiedit::cstate::move_caret_by(long nDelta,bool bSelectionMode)
{
	move_caret_to(get_caret_pos() + nDelta,bSelectionMode);
}

inline void cned_multiedit::cstate::move_caret_to(long nNewCaretPosition,bool bSelectionMode)
{
	ASSERT(nNewCaretPosition >= 0 && nNewCaretPosition <= get_buffer_size());
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
		
inline void cned_multiedit::cstate::clear_selection()
{
	m_nCharSelFirst = get_caret_pos();
	m_nCharSelLast = get_caret_pos();
}

inline bool cned_multiedit::cstate::delete_selected_chars()
{
	if(is_selection())
	{
		long nStartingPos = m_nCharSelFirst;
		long nCount = m_nCharSelLast - m_nCharSelFirst;
		__delete_from_buffer(nStartingPos,nCount);
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

//------ property GET -----------------
inline bool cned_multiedit::get_prop_use_enter() const
{
	return m_bUseEnter;
}

inline bool cned_multiedit::get_prop_valid() const
{
	return m_bDataValid;
}

inline void cned_multiedit::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = get_prop_text();
}

inline ng_string cned_multiedit::get_prop_text() const
{
	return m_State.get_buffer();
}

//------ property SET -----------------

inline void cned_multiedit::set_prop_use_enter(bool bUseEnter)
{
	m_bUseEnter = bUseEnter;
}

inline void cned_multiedit::set_prop_valid(bool bValid)
{
	if(get_prop_valid() == bValid)
	{
		return;
	}
	m_bDataValid = bValid;

	_invalidate_all_paint();
	_vse_dirty();
}

inline void cned_multiedit::set_prop_value(const CSmartOleVariant & roSOV)
{
	ng_string oString(roSOV.GetBStr());
	set_prop_text(oString);

	_vse_dirty();
}

inline void cned_multiedit::set_prop_text(const ng_string & roTextString)
{
	if(m_State.get_buffer() == roTextString)
	{
		return;
	}

	m_State.__set_buffer(roTextString);
	m_State.move_caret_to(0,false);

	_set_infra_update_pending();
	
	_invalidate_all_paint();
	_vse_dirty();
}

//---------------------------------------------------------
// dimension information and calculations
//---------------------------------------------------------
inline ng_xdist cned_multiedit::_get_frame_px_width() const
{
	if(_metrics().is_windows_look())
	{
		return get_manager()->__zoomize(2);	//NG_FRAME_EDGE_SUNKEN is double
	}
	else
	{
		if(get_prop_border_type() != NED_BORDER_STYLE_NONE)
		{
			return get_manager()->__zoomize(get_prop_border_width());
		}
		else
		{
			return 0;
		}
	}
}

inline void cned_multiedit::_get_back_rect(const ng_point & roCurrentPoint,ng_rect & roBackRect) const
{
	roBackRect = ng_rect(roCurrentPoint,m_oActualSize);
	roBackRect.inflate(-_get_frame_px_width(),- _get_frame_px_width());
}

inline void cned_multiedit::_get_text_rect(const ng_point & roCurrentPoint,ng_rect & roRect) const
{
	_get_back_rect(roCurrentPoint,roRect);
	roRect.inflate(-_metrics().edit().get_left_margin(),-_metrics().edit().get_top_margin(),
			-_metrics().edit().get_right_margin(),-_metrics().edit().get_bottom_margin());
}

inline void cned_multiedit::_get_caret_rect(const ng_point & roCurrentPoint,ng_rect & roRect) const
{
	ng_point oCaretPoint(roCurrentPoint);

	oCaretPoint.offset(m_State.m_dxCaretPos,_get_frame_px_width() + _metrics().edit().get_top_margin() + 
		m_State.m_nCaretLine * m_State.m_dyLineHeight);
	
	roRect = ng_rect(oCaretPoint,ng_size(1,m_State.m_dyLineHeight));
}
//---------------------------------------------------------
inline void cned_multiedit::_set_infra_update_pending()
{
	m_bInfraUpdPending = true;
}

//------------------------------------------------------------------------------------
inline ng_color cned_multiedit::_get_text_color(bool bTreeDisabled)
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

inline void cned_multiedit::get_opaque_background_area(const ng_point & roCurrentPoint,ng_area & roArea) const
{
	if(_is_fast_graphics() || get_prop_backcolor().is_opaque())	//jeœli nieprze¿roczysty to ca³y obszar
	{
		ng_point oPaintPoint(roCurrentPoint);
		oPaintPoint.offset(m_oVectorSize);
		roArea += ng_rect(oPaintPoint,m_oActualSize);
	}
}
}

#else
	#error __FILE__ already included
#endif

