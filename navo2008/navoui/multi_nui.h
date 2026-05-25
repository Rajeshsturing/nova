/*
	NAVO Enterprise 2008
	15.04.2002
	
	cnui_multiedit
		wieloliniowy edytor tekstu

*/

#ifndef _MULTI_NUI_H_
#define _MULTI_NUI_H_


class cnui_multiedit : public cnui_rect_element_, public multiline_
{
public:
	virtual void on_event_keydown(const nui_action_kbd & roActionKBD,nui_action_result & roResult);

	virtual void paint(cnui_painter & roPainter);

	virtual ng_ycoord render(cnui_renderer__ & roRenderer);

	ng_string get_prop_text() const;

	bool get_prop_valid() const
	{
		return m_bDataValid;
	}
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	
	void set_prop_use_enter(bool bUseEnter);
	bool get_prop_use_enter() const;

	void set_prop_text(const ng_string & roTextString);
	void set_prop_valid(bool bValid);
	virtual void set_prop_value(const CSmartOleVariant & roSOV);

	virtual void  copy_to(SCP<cnui_element> & poDestElementSP);

private:
	void _get_caret_rect(ng_rect & roRect);

	void _paint_border(cnui_painter & roPainter);
	void _paint_caret(cnui_painter & roPainter);

	void __on_successfull_action(const ng_string & roString,nui_action_result & roResult);

	ng_point get_char_point(long nChar,ng_dc & roDC,SCP<ng_font> & rpoFontSP);

	struct cstate
	{
		cstate();
		cstate(const cstate & roState);
		long	m_nCharSelFirst;	//pierwszy zaznaczony znak
		long	m_nCharSelLast;		//ostatni zaznaczony
		bool	m_bCaretOn;			//czy 'caret' jest w³¹czony
		long	m_nCharCaret;		//po³o¿enie 'careta' (w buforze)
		ng_point m_oTLCaret;		//lewy-górny róg caret'a
		ng_point m_oTLSelFirst;		//lewy-górny róg pocz¹tku selekcji
		ng_point m_oTLSelLast;		//lewy-górny róg koñca selekcji
		
		long get_caret_pos() const;
		void move_caret_to(long nNewCaretPosition,bool bSelectionMode);
		void move_caret_by(long nDelta,bool bSelectionMode);
	};

	cnui_multiedit(cnui_element_manager * poManager,const nui_ident nIdent);
	bool _dispatch_action(const nui_action_kbd & roActionKBD);

	cstate		m_State;
	bool		m_bDataValid;		//czy dane s¹ prawid³owe (akceptowalne przez aplikacjê)
	bool		m_bUseEnter;		//dzia³anie klawisza ENTER - true oznacza now¹ liniê, false - utratê focusa

	friend class cnui_element_manager;
};

inline cnui_multiedit::cstate::cstate():
	m_nCharSelFirst(0),
	m_nCharSelLast(0),
	m_bCaretOn(true),
	m_nCharCaret(0),
	m_oTLCaret(0),
	m_oTLSelFirst(0),
	m_oTLSelLast(0)
{
}

inline cnui_multiedit::cstate::cstate(const cnui_multiedit::cstate & roState) :
	m_nCharSelFirst(roState.m_nCharSelFirst),
	m_nCharSelLast(roState.m_nCharSelLast),
	m_bCaretOn(roState.m_bCaretOn),
	m_nCharCaret(roState.m_nCharCaret),
	m_oTLCaret(roState.m_oTLCaret),
	m_oTLSelFirst(roState.m_oTLSelFirst),
	m_oTLSelLast(roState.m_oTLSelLast)
{
}

inline long cnui_multiedit::cstate::get_caret_pos() const
{
	return m_nCharCaret;
}

inline void cnui_multiedit::cstate::move_caret_by(long nDelta,bool bSelectionMode)
{
	move_caret_to(get_caret_pos() + nDelta,bSelectionMode);
}

inline void cnui_multiedit::set_prop_use_enter(bool bUseEnter)
{
	m_bUseEnter = bUseEnter;
}

inline bool cnui_multiedit::get_prop_use_enter() const
{
	return m_bUseEnter;
}

#else
	#error __FILE__ already included
#endif

