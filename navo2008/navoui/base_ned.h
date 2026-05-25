/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	basic definitions

*/

#ifndef _BASE_NED_H_
#define _BASE_NED_H_

namespace ned
{
//--------------------------------------------------------------------
// typ kontrolki
//--------------------------------------------------------------------

enum ened_element_type
{
	ned_none			= -1,
	ned_static			= CTRL_TYPE_STATIC,
	ned_button			= CTRL_TYPE_BUTTON,
	ned_textedit		= CTRL_TYPE_EDIT,
	ned_multiline		= CTRL_TYPE_MULTILINE,
	ned_date			= CTRL_TYPE_DATE,
	ned_currency		= CTRL_TYPE_CURRENCY,
	ned_radio			= CTRL_TYPE_RADIO,
	ned_checkbox		= CTRL_TYPE_CHECKBOX,
	ned_timeed			= CTRL_TYPE_TIME,
	
	ned_paragraph		= CTRL_TYPE_PARAGRAPH,
	ned_breakline		= CTRL_TYPE_BREAKLINE,
	ned_breakpage		= CTRL_TYPE_BREAKPAGE,
	ned_richedit		= CTRL_TYPE_RICHEDIT,
	ned_htmlwindow		= CTRL_TYPE_WEB,
	ned_olecontrol		= CTRL_TYPE_OLECONTROL,
	ned_picture			= CTRL_TYPE_PICTURE,
	ned_extern			= CTRL_TYPE_EXTERN,

	ned_subpage			= CTRL_TYPE_PAGEMAN,

	ned_tablecell		= CTRL_TYPE_TABLECELL,
	ned_tablerow		= CTRL_TYPE_TABLEROW,
	ned_tablesection	= 23,		//nie maj¹ zewnêtrznych sta³ych
	ned_table			= CTRL_TYPE_TABLE,
	ned_grid			= CTRL_TYPE_GRID,
	ned_staticex		= CTRL_TYPE_STATICEX,
	ned_patterntablerow   = 27,	//nie maj¹ zewnêtrznych sta³ych
	ned_spreadbodysection = 28,	//nie maj¹ zewnêtrznych sta³ych
	ned_documentobject	= CTRL_TYPE_DOCUMENTOBJECT,
	ned_toplevelpage	= CTRL_TYPE_TOPLEVELPAGE,
	ned_tabmanager		= CTRL_TYPE_TABMANAGER,
	ned_tabitem			= CTRL_TYPE_TABITEM,
	ned_hscroll			= CTRL_TYPE_HSCROLL,
	ned_vscroll			= CTRL_TYPE_VSCROLL,
	ned_intedit			= CTRL_TYPE_INTEDIT,
	ned_spreadpatternsection = 36,	//nie ma zewnêtrznej sta³ej
	ned_page_widgets	= 37,		//nie ma zewnêtrznej sta³ej
	ned_tablebodysection= 38,		//nie ma zewnêtrznej sta³ej
	ned_tabmanagerheader = 39,		//nie ma zewnêtrznej sta³ej
};

const long ARENA_TOOLTIP_TIMER_ID	= 7001;
const long ARENA_CONTROL_TIMER_ID	= 7002;
//--------------------------------------------------------------------
// typy identyfikatorów
//--------------------------------------------------------------------
typedef long	ned_ident;			//identyfikator elementu
typedef long	ned_declattrinx;	//index attrybutów deklaracji
typedef long	ned_fontinx;		//font index

//--------------------------------------------------------------------
// predefiniowane sta³e
//--------------------------------------------------------------------
const ned_ident			NEDID_NOTHING		= ned_ident(-1);			//nothing
const ned_ident			NEDID_LAST			= ned_ident(-2);			//last element
const ned_ident			NEDID_PLACEHOLDER	= ned_ident(-3);			//placeholder
const ned_ident			NEDID_TOPLEVELPAGE	= ned_ident(9997);
const ned_declattrinx	NED_DECLATTR_ALL_DEFAULT= ned_declattrinx(0);
const ned_fontinx		NED_DEFAULT_FONT_INX	= ned_fontinx(0);

const ng_xdist			NED_AUTO_WIDTH		= ng_xdist(LONG_MAX);
const ng_xdist			NED_MIN_WIDTH		= ng_xdist(LONG_MAX-1);
const ng_xdist			NED_MAX_WIDTH		= ng_xdist(LONG_MAX-2);

const ng_ydist			NED_AUTO_HEIGHT		= ng_ydist(NED_AUTO_WIDTH);
const ng_ydist			NED_MIN_HEIGHT		= ng_ydist(NED_MIN_WIDTH);
const ng_ydist			NED_MAX_HEIGHT		= ng_ydist(NED_MAX_WIDTH);

const TCHAR MULTILINE_NEWLINE_CHAR = '\x0A';

const long MAIN_PAINT_RECT_ID = 0;

//--------------------------------------------------------------------
// mini-info - informacja podstawowa, szybko dostêpne bez pobierania elementu
// (nawet gdy jest swappped)
//--------------------------------------------------------------------
class ned_element_mini_info
{
public:
	ned_element_mini_info();

	ened_element_type get_type() const;
	//--------------- structure informations --------------
	const ned_ident get_container_ident() const;
	const ned_ident get_next_element_ident() const;
	const ned_ident get_prev_element_ident() const;
	//--------------- get bit flags -----------------------

	bool is_hidden() const;
	bool is_tabstop() const;
	bool is_internal_disabled() const;
	bool is_internal_ignore_sys_dis() const;
	bool is_printable() const;
	bool is_deletenow() const;
	bool is_measure_pending() const;
	bool is_split_allowed() const;

	//--------------- set bit flags -----------------------
	void set_hidden(bool bHidden);
	void set_tabstop(bool bTabStop);
	void set_internal_disabled(bool bDisabled);
	void set_internal_ignore_sys_dis(bool bIgnore);
	void set_printable(bool bPrintable);
	void set_delete_now();
	void set_split_allowed(bool bSplit);
	
	void set_measure_pending();
	void clear_measure_pending();

	//--------------- set structure informations --------------
	void set_next_element_ident(ned_ident idNext);
	void set_prev_element_ident(ned_ident idPrev);
	void set_container_ident(ned_ident nContainerIdent);

	//---------------- special --------------------------------
	void _set_type(const ened_element_type eType);
	void fill_clone(ned_element_mini_info & roMiniInfo) const;
private:
	ned_ident			m_idContainer;			//container id
	ned_ident			m_idNext;				//next sibling id
	ned_ident			m_idPrev;				//prev sibling id
	ened_element_type	m_eType;				//element type;
	
	union uBitsByte
	{
		struct sBits
		{
			bool	m_bHidden			: 1;		//hidden flag
			bool	m_bTabStop			: 1;		//tabstop flag
			bool	m_bDeleteNow		: 1;		//marked for deletion
			bool	m_bInternalDisabled	: 1;		//element is disabled (internal flag)

			bool	m_bInternalISD		: 1;		//ignore sys disable (internal flag)
			bool	m_bNotPrintable		: 1;		//printable flag
			bool	m_bNotMeasurePending: 1;		//measure done flag
			bool	m_bDontSplit		: 1;		//dont split between pages
		};
		sBits	m_Bits; 
		BYTE	m_Byte;
	};

	uBitsByte	m_BitsByte;
};

//--------------------------------------------------------------------
// ró¿ne enumeracje
//--------------------------------------------------------------------

//--- sk³adniki ramki ---------

enum ened_border_element
{
	ebe_left	= 0,
	ebe_top		= 1,
	ebe_right	= 2,
	ebe_bottom	= 3
};

//--- mo¿liwe alignmenty (wyrównania) ------------

enum ened_alignment
{
	eal_left	= 0x00,
	eal_right	= 0x01,
	eal_center	= 0x02,
	eal_justify	= 0x03,
	eal_horizmask = (eal_left | eal_right | eal_center | eal_justify),

	eal_top		= 0x00,
	eal_bottom	= 0x08,
	eal_vcenter	= 0x10,

	eal_vertmask = (eal_top | eal_bottom | eal_vcenter)
};

//--- mo¿liwe alignmenty w linii (wyrównania elementów tworz¹cych liniê) ------------

enum ened_line_alignment
{
	elal_top	= 0x00,
	elal_bottom	= 0x01,
	elal_vcenter= 0x02,
};

//--- typ kursora myszki ------------------------

enum eCursorType
{
	ect_default,
	ect_hand,
	ect_ibeam,
	ect_drag,
};

//--- wbudowane, predefiniowane obrazki ---------

enum eSpecialImage
{
	esi_check_ns_nf = 0,			//checkbox not selected, not focused
	esi_check_se_nf = 1,			//checkbox selected,not focused
	esi_radio_ns_nf = 2,			//radio not selected, not focused
	esi_radio_se_nf = 3,			//radio selected,not focused

	esi_check_ns_fo = 4,			//checkbox not selected, focused
	esi_check_se_fo = 5,			//checkbox selected,focused
	esi_radio_ns_fo = 6,			//radio not selected, focused
	esi_radio_se_fo = 7,			//radio selected, focused

	esi_verts_upper = 8,			//vertical scrollbar, upper arrow
	esi_verts_lower = 9,			//vertical scrollbar, lower arrow
	esi_horizs_left =10,			//horizontal scrollbar, left arrow
	esi_horizs_right=11,			//horizontal scrollbar, right arrow

	esi_close_up	=12,			//close button
	esi_minimize	=13,			//minimize button
	esi_maximize	=14,			//maximize button
	esi_missing		=15,
	esi_max = esi_missing + 1,
};

//------------------------------------------------
// polecenia obs³ugiwane przez ró¿ne kontrolki
// nie wszystkie obs³uguj¹ wszystko
//------------------------------------------------
//	
//	DO NOT CHANGE ORDINAL NUMBERS - USED IN APPLICATION
//	
//	
//------------------------------------------------

enum eStdControlCommandVerb
{
	sccv_none		= 0,
	sccv_put_value	= 1,	//PROPC_VARIANT = data value (variant)
	sccv_copy		= 2,
	sccv_paste		= 3,
	sccv_paste_data = 4,	//PROPC_VARIANT = data value (string)
	sccv_insert_row	= 5,	//PROPC_ROW = internal data row nr
	sccv_delete_row	= 6,	//PROPC_ROW = internal data row nr
	sccv_delete_all	= 7,	//delete all rows
	sccv_activate_item = 8,	//(tabmanager) PROPC_VARIANT - title static ident (long)
	sccv_minimize	= 9,	//(page) - minimize
	sccv_restore	= 10,	//(page) - restore
	sccv_maximize	= 11,	//(page) - maximize
	sccv_scr_dummy	= 12,	//dummy command - used by scrollbar
	sccv_scroll_to	= 13,	//scroll to position	PROPC_XPOSITION or PROPC_YPOSITION or both
};

//----------------------------------------------------------------------------------------------
// opis fontu
//----------------------------------------------------------------------------------------------

struct ned_font_spec
{
	ned_font_spec();
	ned_font_spec(const ned_font_spec & roFontSpec);
	void operator = (const ned_font_spec & roFontSpec);
	void make_normal();

	//converts to / from string
	void to_string(ng_string & roFontSpecString) const;
	void from_string(LPCTSTR lpFontSpecString);

	ng_string	m_oFontNameString;
	long		m_nSize;
	bool		m_bBold;
	bool		m_bItalic;
	bool		m_bStrikeThrough;
	bool		m_bUnderLine;
	SHORT		m_sCharSet;
};

//----------------------------------------------------------------------------------------------
// metrics
//
// klasa s³u¿aca do przechowywania metryk elementu
// minimalna szerokosc
// minimalna wysokosc
// "waga" elementu
//----------------------------------------------------------------------------------------------
class cned_storage_writer;
class cned_storage_reader;

class cned_metrics
{
public:
	cned_metrics();
	cned_metrics(const cned_metrics & roMetrics);
	
	void update(ng_xdist xMinWidth,ng_ydist yMinHeight,long nWeight);
	void update(const cned_metrics & roMetrics);

	ng_xdist get_minimal_width() const;
	ng_ydist get_minimal_height() const;
	long get_weight() const;

	void reset();
private:
	ng_xdist	m_xMinWidth;		//minimalna szerokoœæ elementu
	ng_ydist	m_yMinHeight;		//minimalna wysokoœæ elementu
	long		m_nWeight;			//"waga" elementu

	friend cned_storage_writer & operator << (cned_storage_writer & roWriter,const cned_metrics & roMetrics);
	friend cned_storage_reader & operator >> (cned_storage_reader & roReader,cned_metrics & roMetrics);
};

//--------------------------------------------------------------------
// used for control timer registration
//--------------------------------------------------------------------

struct timer_registration
{
	timer_registration();
	timer_registration(ned_ident idElement,long nInterval,bool bOnlyWhenOnTop);
	timer_registration(const timer_registration & roTimerRegistr);
	void operator = (const timer_registration & roTimerRegistr);
	bool operator == (const timer_registration & roTimerRegistr) const;

	ned_ident	m_idElement;
	long		m_nInterval;
	long		m_nCountDown;
	bool		m_bOnlyWhenOnTop;
};

//-------------------------------------------------------------------------
//	parametry malowania
//	cned_paint_param
//-------------------------------------------------------------------------
enum ePaintMode
{
	pm_screen,
	pm_printpreview,
	pm_printer
};

class cned_paint_param
{
public:
	cned_paint_param();
	cned_paint_param(const cned_paint_param & roPaintParam);
	void operator = (const cned_paint_param & roPaintParam);

	//-- get info ---------
	bool paint_background() const;
	bool is_printing() const;			//printing or print preview (fixed result)
	ePaintMode get_paint_mode() const;
	eColorTranslation get_color_translation() const;

	//-- set info ------------
	void set_paint_background(bool bPaint);
	void set_paint_mode(ePaintMode ePM);
	void set_color_translation(eColorTranslation eCT);
private:
	ePaintMode	m_ePaintMode;
	bool	m_bPaintBackground;
	eColorTranslation m_eColorTranslation;
};

//--------------------------------------------------------------------
// describes effect of animated rect
//--------------------------------------------------------------------
struct animate_rect_effect
{
	animate_rect_effect();
	animate_rect_effect(const animate_rect_effect & roARE);
	void operator = (const animate_rect_effect & roARE);

	ng_rect m_oStartingRect;
	ng_rect m_oEndingRect;
	long	m_nSteps;
	long	m_nStepDelay;
};

//--------------------------------------------------------------------
bool is_container(ened_element_type eType);

inline bool is_normal_width_value(ng_xdist xWidth);
inline bool is_normal_height_value(ng_ydist yHeight);

inline bool is_maximal_width_value(ng_xdist xWidth);
inline bool is_maximal_height_value(ng_ydist yHeight);

inline bool is_minimal_width_value(ng_xdist xWidth);
inline bool is_minimal_height_value(ng_ydist yHeight);

inline bool is_auto_width_value(ng_xdist xWidth);
inline bool is_auto_height_value(ng_ydist yHeight);

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline ned_element_mini_info::ned_element_mini_info() :
	m_eType(ned_none),
	m_idContainer(NEDID_NOTHING),
	m_idNext(NEDID_NOTHING),
	m_idPrev(NEDID_NOTHING)
{
	m_BitsByte.m_Byte = BYTE('\0');
	
	ASSERT(!is_hidden());
	ASSERT(!is_internal_disabled());
	ASSERT(!is_internal_ignore_sys_dis());
	ASSERT(is_printable());
	ASSERT(!is_deletenow());
	ASSERT(is_measure_pending());
}

inline ened_element_type ned_element_mini_info::get_type() const
{
	return m_eType;
}

//--------------- structure informations --------------
inline const ned_ident ned_element_mini_info::get_container_ident() const
{
	return m_idContainer; 
}

inline const ned_ident ned_element_mini_info::get_next_element_ident() const
{
	return m_idNext;
}

inline const ned_ident ned_element_mini_info::get_prev_element_ident() const
{
	return m_idPrev;
}

//--------------- get bit flags -----------------------
inline bool ned_element_mini_info::is_hidden() const
{
	return m_BitsByte.m_Bits.m_bHidden;
}

inline bool ned_element_mini_info::is_tabstop() const
{
	return m_BitsByte.m_Bits.m_bTabStop;
}

inline bool ned_element_mini_info::is_internal_disabled() const
{
	return m_BitsByte.m_Bits.m_bInternalDisabled;
}

inline bool ned_element_mini_info::is_internal_ignore_sys_dis() const
{
	return m_BitsByte.m_Bits.m_bInternalISD;
}

inline bool ned_element_mini_info::is_printable() const
{
	return !m_BitsByte.m_Bits.m_bNotPrintable;
}

inline bool ned_element_mini_info::is_deletenow() const
{
	return m_BitsByte.m_Bits.m_bDeleteNow;
}

inline bool ned_element_mini_info::is_measure_pending() const
{
	return !m_BitsByte.m_Bits.m_bNotMeasurePending;
}

inline bool ned_element_mini_info::is_split_allowed() const
{
	return !m_BitsByte.m_Bits.m_bDontSplit;
}

//--------------- set bit flags -----------------------
inline void ned_element_mini_info::set_hidden(bool bHidden)
{
	m_BitsByte.m_Bits.m_bHidden = bHidden;
}

inline void ned_element_mini_info::set_tabstop(bool bTabStop)
{
	m_BitsByte.m_Bits.m_bTabStop = bTabStop;
}

inline void ned_element_mini_info::set_internal_disabled(bool bDisabled)
{
	m_BitsByte.m_Bits.m_bInternalDisabled = bDisabled;
}

inline void ned_element_mini_info::set_internal_ignore_sys_dis(bool bIgnore)
{
	m_BitsByte.m_Bits.m_bInternalISD = bIgnore;
}

inline void ned_element_mini_info::set_printable(bool bPrintable)
{
	m_BitsByte.m_Bits.m_bNotPrintable = !bPrintable;
}

inline void ned_element_mini_info::set_delete_now()
{
	m_BitsByte.m_Bits.m_bDeleteNow = true;
}

inline void ned_element_mini_info::set_measure_pending()
{
	m_BitsByte.m_Bits.m_bNotMeasurePending = false;
}

inline void ned_element_mini_info::clear_measure_pending()
{
	m_BitsByte.m_Bits.m_bNotMeasurePending = true;
}

inline void ned_element_mini_info::set_split_allowed(bool bSplit)
{
	m_BitsByte.m_Bits.m_bDontSplit = !bSplit;
}

//--------------- set structure informations --------------
inline void ned_element_mini_info::set_next_element_ident(ned_ident idNext)
{
	m_idNext = idNext;
}

inline void ned_element_mini_info::set_prev_element_ident(ned_ident idPrev)
{
	m_idPrev = idPrev;
}

inline void ned_element_mini_info::set_container_ident(ned_ident idContainer)
{
	//wolno nadawaæ albo kasowaæ, ale nie zmieniaæ
	ASSERT(
		(m_idContainer == NEDID_NOTHING && idContainer != NEDID_NOTHING) ||
		(m_idContainer != NEDID_NOTHING && idContainer == NEDID_NOTHING)
		);
	m_idContainer = idContainer;
}


//---------------- special --------------------------------
inline void ned_element_mini_info::_set_type(const ened_element_type eType)
{
	m_eType = eType;
}

inline void ned_element_mini_info::fill_clone(ned_element_mini_info & roMiniInfo) const
{
	roMiniInfo.m_BitsByte.m_Bits.m_bHidden				= m_BitsByte.m_Bits.m_bHidden;
	roMiniInfo.m_BitsByte.m_Bits.m_bInternalDisabled	= m_BitsByte.m_Bits.m_bInternalDisabled;
	roMiniInfo.m_BitsByte.m_Bits.m_bInternalISD			= m_BitsByte.m_Bits.m_bInternalISD;
	roMiniInfo.m_BitsByte.m_Bits.m_bNotPrintable		= m_BitsByte.m_Bits.m_bNotPrintable;
}

//----------------------------------------------------------------------------------------------
// opis fontu
//----------------------------------------------------------------------------------------------
inline ned_font_spec::ned_font_spec() 
	/*
		takie dziwne inicjowanie, 
		aby wykryæ b³êdy braku inicjowania 
		(pochy³y przekreœlony font rzuca siê w oczy)
	*/
#ifdef _DEBUG				
	:
	m_nSize(5),
	m_bBold(false),
	m_bItalic(true),				
	m_bStrikeThrough(true),
	m_bUnderLine(false)
#endif
{
}

inline ned_font_spec::ned_font_spec(const ned_font_spec & roFontSpec)
{
	(*this) = roFontSpec;
}

inline void ned_font_spec::make_normal()
{
	m_bBold = false;
	m_bItalic = false;
	m_bUnderLine = false;
	m_bStrikeThrough = false;
	m_sCharSet	= EASTEUROPE_CHARSET;
}

inline void ned_font_spec::operator = (const ned_font_spec & roFontSpec)
{
	m_oFontNameString		= roFontSpec.m_oFontNameString;
	m_nSize					= roFontSpec.m_nSize;
	m_bBold					= roFontSpec.m_bBold;
	m_bItalic				= roFontSpec.m_bItalic;
	m_bStrikeThrough		= roFontSpec.m_bStrikeThrough;
	m_bUnderLine			= roFontSpec.m_bUnderLine;
	m_sCharSet				= roFontSpec.m_sCharSet;
}

//----------------------------------------------------------------------------------------------
// metrics
//----------------------------------------------------------------------------------------------

inline cned_metrics::cned_metrics() :
	m_xMinWidth(0),
	m_yMinHeight(0),
	m_nWeight(0)
{
}

inline cned_metrics::cned_metrics(const cned_metrics & roMetrics) :
	m_xMinWidth(roMetrics.m_xMinWidth),
	m_yMinHeight(roMetrics.m_yMinHeight),
	m_nWeight(roMetrics.m_nWeight)
{
}
	
inline void cned_metrics::update(ng_xdist xMinWidth,ng_ydist yMinHeight,long nWeight)
{
	ASSERT(xMinWidth >= 0);
	ASSERT(yMinHeight >= 0);
	ASSERT(nWeight >= 0);

	m_xMinWidth = max(m_xMinWidth,xMinWidth);
	m_yMinHeight = max(m_yMinHeight,yMinHeight);
	m_nWeight += nWeight;
}

inline void cned_metrics::update(const cned_metrics & roMetrics)
{
	m_xMinWidth = max(m_xMinWidth,roMetrics.m_xMinWidth);
	m_yMinHeight = max(m_yMinHeight,roMetrics.m_yMinHeight);
	m_nWeight += roMetrics.m_nWeight;
}

inline ng_xdist cned_metrics::get_minimal_width() const
{
	return m_xMinWidth;
}

inline ng_ydist cned_metrics::get_minimal_height() const
{
	return m_yMinHeight;
}

inline long cned_metrics::get_weight() const
{
	return m_nWeight;
}
	
inline void cned_metrics::reset()
{
	m_xMinWidth = 0;
	m_yMinHeight = 0;
	m_nWeight = 0;
}

//----------------------------------------------------------------------------------------------
//	timer_registration
//----------------------------------------------------------------------------------------------
inline timer_registration::timer_registration() :
	m_idElement(NEDID_NOTHING),
	m_nInterval(0),
	m_nCountDown(0),
	m_bOnlyWhenOnTop(false)
{
};

inline timer_registration::timer_registration(ned_ident idElement,long nInterval,bool bOnlyWhenOnTop) :
	m_idElement(idElement),
	m_nInterval(nInterval),
	m_nCountDown(nInterval),
	m_bOnlyWhenOnTop(bOnlyWhenOnTop)
{
}

inline timer_registration::timer_registration(const timer_registration & roTimerRegistr) :
	m_idElement(roTimerRegistr.m_idElement),
	m_nInterval(roTimerRegistr.m_nInterval),
	m_nCountDown(roTimerRegistr.m_nCountDown),
	m_bOnlyWhenOnTop(roTimerRegistr.m_bOnlyWhenOnTop)
{
}

inline void timer_registration::operator = (const timer_registration & roTimerRegistr)
{
	m_idElement = roTimerRegistr.m_idElement;
	m_nInterval = roTimerRegistr.m_nInterval;
	m_nCountDown = roTimerRegistr.m_nCountDown;
	m_bOnlyWhenOnTop = roTimerRegistr.m_bOnlyWhenOnTop;
}

inline bool timer_registration::operator == (const timer_registration & roTimerRegistr) const
{
	return 
		(m_idElement == roTimerRegistr.m_idElement) && 
		(m_nInterval == roTimerRegistr.m_nInterval) &&
		(m_nCountDown == roTimerRegistr.m_nCountDown) &&
		(m_bOnlyWhenOnTop == roTimerRegistr.m_bOnlyWhenOnTop);
}

//----------------------------------------------------------------------------------------------
//	animate_rect_effect
//----------------------------------------------------------------------------------------------
inline animate_rect_effect::animate_rect_effect() :
	m_nSteps(5),
	m_nStepDelay(15)
{
}

inline animate_rect_effect::animate_rect_effect(const animate_rect_effect & roARE) :
	m_oStartingRect(roARE.m_oStartingRect),
	m_oEndingRect(roARE.m_oEndingRect),
	m_nSteps(roARE.m_nSteps),
	m_nStepDelay(roARE.m_nStepDelay)
{
}

inline void animate_rect_effect::operator = (const animate_rect_effect & roARE)
{
	m_oStartingRect	= roARE.m_oStartingRect;
	m_oEndingRect	= roARE.m_oEndingRect;
	m_nSteps		= roARE.m_nSteps;
	m_nStepDelay	= roARE.m_nStepDelay;
}

//-------------------------------------------------------------------------
// cned_paint_param
//-------------------------------------------------------------------------
inline cned_paint_param::cned_paint_param() :
	m_ePaintMode(pm_screen),
	m_bPaintBackground(true),
	m_eColorTranslation(ct_none)
{
}

inline cned_paint_param::cned_paint_param(const cned_paint_param & roPaintParam) :
	m_ePaintMode(roPaintParam.m_ePaintMode),
	m_bPaintBackground(roPaintParam.m_bPaintBackground),
	m_eColorTranslation(roPaintParam.m_eColorTranslation)
{
}

inline void cned_paint_param::operator = (const cned_paint_param & roPaintParam)
{
	m_ePaintMode = roPaintParam.m_ePaintMode;
	m_bPaintBackground = roPaintParam.m_bPaintBackground;
	m_eColorTranslation = roPaintParam.m_eColorTranslation;
}

inline bool cned_paint_param::paint_background() const
{
	return m_bPaintBackground;
}

inline ePaintMode cned_paint_param::get_paint_mode() const
{
	return m_ePaintMode;
}

inline bool cned_paint_param::is_printing() const
{
	return (m_ePaintMode == pm_printpreview) || (m_ePaintMode == pm_printer);
}

inline eColorTranslation cned_paint_param::get_color_translation() const
{
	return m_eColorTranslation;
}

inline void cned_paint_param::set_paint_background(bool bPaint)
{
	m_bPaintBackground = bPaint;
}

inline void cned_paint_param::set_paint_mode(ePaintMode ePM)
{
	m_ePaintMode = ePM;
}

inline void cned_paint_param::set_color_translation(eColorTranslation eCT)
{
	m_eColorTranslation = eCT;
}


//----------------------------------------------------------------------------------------------
inline bool is_container(ened_element_type eType)
{
	switch(eType)
	{
	case ned_static:
	case ned_button:
	case ned_textedit:
	case ned_date:
	case ned_currency:
	case ned_intedit:
	case ned_timeed:
	case ned_breakline:
	case ned_breakpage:
	case ned_richedit:
	case ned_htmlwindow:
	case ned_olecontrol:
	case ned_picture:
	case ned_staticex:
	case ned_documentobject:
	case ned_extern:
		return false;
	default:
		return true;
	}
}

inline bool is_normal_width_value(ng_xdist xWidth)
{
	return (xWidth < NED_MAX_WIDTH);
}

inline bool is_normal_height_value(ng_ydist yHeight)
{
	return (yHeight < NED_MAX_HEIGHT);
}

inline bool is_maximal_width_value(ng_xdist xWidth)
{
	return (xWidth == NED_MAX_WIDTH);
}

inline bool is_maximal_height_value(ng_ydist yHeight)
{
	return (yHeight == NED_MAX_HEIGHT);
}

inline bool is_minimal_width_value(ng_xdist xWidth)
{
	return (xWidth == NED_MIN_WIDTH);
}

inline bool is_minimal_height_value(ng_ydist yHeight)
{
	return (yHeight == NED_MIN_HEIGHT);
}

inline bool is_auto_width_value(ng_xdist xWidth)
{
	return (xWidth == NED_AUTO_WIDTH);
}

inline bool is_auto_height_value(ng_ydist yHeight)
{
	return (yHeight == NED_AUTO_HEIGHT);
}


}

#ifdef _DEBUG
#define SHIFT_PAUSE \
	{ while(!(::GetAsyncKeyState(VK_SHIFT) & 0x0001))	::Sleep(100); }
#else
#define SHIFT_PAUSE		;
#endif

#else
	#error __FILE__ already included
#endif
