/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych
*/

#ifndef _EDIT_NED_H_
#define _EDIT_NED_H_

namespace ned
{

class cned_edit__ : public cned_rect_element_
{
public:
//------ property GET -----------------

	virtual void get_prop_value(CSmartOleVariant & roSOV);
	long get_prop_charwidth() const;
	bool get_prop_valid() const;
	SCP<IDispatch> get_prop_suggestion();

//------ property SET -----------------
	
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
	void set_prop_charwidth(long nCharWidth);
	void set_prop_valid(bool bValid);
	void set_prop_suggestion(SCP<IDispatch> & rpoDispatchSP);

//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- -------------- -------------- --------------
	void paste_from_string(const ng_string & roString);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//-------------- rendering support -------------------
	virtual void render(cned_renderer_ & roRenderer);
//--------------event handlers ---------------------------------------
	virtual void on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult);
	virtual void on_event_mouse_click(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual void on_event_mouse_endclick(const ned_action_mouse & roActionMouse,ned_action_result & roResult);
	virtual eCursorType on_event_set_cursor(const ng_point & roPoint);
	virtual void on_event_focus(const ned_action_focus & roActionFocus,ned_action_result & roResult);
	virtual void on_event_timer(const ned_action_timer & roActionTimer,ned_action_result & roResult);

	virtual void on_event_command(const ned_action_command & roActionCommand,ned_action_result & roResult);
	//---------------------------------------------------------
	void _on_event_mouse_selection(const ned_action_mouse & roActionMouse,ned_action_result & roResult,bool bSelect);
	void _fill_command_list(ned_action_result & roResult);
	//-------------- fine grained manipulations
	void select_to_end();
	void move_caret_to(long nNewCaretPosition,bool bSelectionMode);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
	//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);

	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect /*we wspó³rzêdnych kontenera*/) const;
protected:
	cned_edit__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);
	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);

	void _copy_properties(cned_edit__ * poDestinationEdit);
	//---------------------------------------------------------
	// buffer <-> data convertions
	//---------------------------------------------------------
	virtual bool buffer2variant(CSmartOleVariant & roSOV) const = 0;
	virtual bool variant2buffer(const CSmartOleVariant & roSOV) = 0;

	virtual void get_visible_buffer(ng_string & roString) const;
	//---------------------------------------------------------
	// kbd actions
	//---------------------------------------------------------
	struct cstate;
	bool _dispatch_action(const ned_action_kbd & roActionKBD);
	void _on_successfull_action(const ned_action__ & roAction,const cstate & roOldState,ned_action_result & roResult);

	virtual long _act_move(UINT nVKCode,bool bWithCtrl) = 0;
	virtual bool _act_delete(bool bWithShift) = 0;
	virtual bool _act_backspace(bool bWithShift) = 0;
	virtual bool _act_data(UINT nTranslatedChar) = 0;
	virtual bool _act_paste_from_string(const ng_string & roString) = 0;
	virtual void _act_copy_to_string(ng_string & roString) = 0;
	virtual bool _act_cut_to_string(ng_string & roString) = 0;
	virtual void _after_act_move(long nNewCaretPos,bool bShift);
	virtual void _after_got_focus();

	bool _act_paste();
	bool _act_cut();
	void _act_copy();

	//---------------------------------------------------------
	virtual bool _is_auto_scroll() = 0;
	virtual ng_color _get_text_color(bool bTreeDisabled);

	void _invalidate_internal_paint();
	void _invalidate_caret_paint();
	//---------------------------------------------------------
	// dimension information and calculations
	//---------------------------------------------------------
	ng_xdist _get_frame_px_width() const;
	void _get_back_rect(const ng_point & roCurrentPoint,ng_rect & roBackRect) const;
	void _get_text_rect(const ng_point & roCurrentPoint,ng_rect & roTextRect) const;
	void _get_caret_rect(const ng_point & roCurrentPoint,ng_rect & roCaretRect,const cstate & roState);
	//---------------------------------------------------------
	void _paint_border(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	void _paint_caret(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	//---------------------------------------------------------
	// internal text buffer management
	//---------------------------------------------------------
	struct cstate
	{
		cstate();
		cstate(const cstate & roState);
		ng_string m_oBufferString;	//tekstowy bufor edycyjny

		long	m_nCharScroll;		//pierwszy widoczny znak (s³u¿y do skrolowania)
		long	m_nCharSelFirst;	//pierwszy zaznaczony znak
		long	m_nCharSelLast;		//ostatni zaznaczony
		bool	m_bCaretOn;			//czy 'caret' jest w³¹czony
		long	m_nCharCaret;		//po³o¿enie 'careta'
		ng_xdist m_XLeftCaretLU;	//offset 'caret' od lewej strony textrect
		ng_xdist m_XSelFirstLU;		//offset pocz¹tku selekcji
		ng_xdist m_XSelLastLU;		//offset koñca selekcji
		ng_xdist m_XTextWidthLU;	//szerokoœæ samego tekstu

		void move_caret_to(long nNewCaretPosition,bool bSelectionMode);
		void move_caret_by(long nDelta,bool bSelectionMode);
		void clear_selection();
		
		void insert_char(UINT nChar);	//wstawia do bufora znak na pozycji caret'a. przesuwa caret, kasuje selekcjê jeœli by³a
		void overtype_char(UINT nChar); //nadpisuje znak w buforze na pozycji caret'a. kasuje selekcjê jeœli by³a
		void delete_char();				//kasuje znak w buforze na pozycji kursora

		bool delete_selected_chars();	//usuwa z bufora znaki w selekcji

		long get_caret_pos() const;
		bool is_selection() const;

		void copy_to(cstate & roState) const;
	};

	void _set_new_buffer_text(cstate & roState,const ng_string & roString);

	//---------------------------------------------------------
	void _set_infra_update_pending();
	void _update_infrastructure(ng_dc & roDC,const cstate & roOldState);
	//---------------------------------------------------------
	long _find_char_from_local_point(const ng_point & roLocalPoint,ng_dc & roDC);

	cstate		m_State;			//aktualny 'stan' edita
	long		m_nDeclCharWidth;	//zadeklarowany rozmiar w znakach
	bool		m_bDataValid;		//czy dane s¹ prawid³owe (akceptowalne przez aplikacjê)
	
	bool		m_bInfraUpdPending;	//czy jest potrzeba aktualizacji internal

	SCP<IDispatch>	m_poSuggestionDispatchSP;	//suggestion info object

	static const long INTERNAL_PAINT_RECT_ID;
	static const long CARET_PAINT_RECT_ID;

};

long _act_move_left_word(LPCTSTR lpText,long nPos);
long _act_move_right_word(LPCTSTR lpText,long nPos,long nTextLen);



}

#else
	#error __FILE__ already included
#endif
