/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
		- deklarowane atrybuty elementu
*/


#ifndef _ATTRIBUTES_NED_H_
#define _ATTRIBUTES_NED_H_

namespace ned
{
//----------------------------------------------------------------------------------------------

enum ned_attribute_type : long
{
	NEDA_NONE		= 0x0000000000000000,
	NEDA_FORECOLOR	= 0x0000000000000001,
	NEDA_BACKCOLOR	= 0x0000000000000002,
	NEDA_BACKCOLOR2 = 0x0000000000000004,
	
	NEDA_FONTNAME   = 0x0000000000000008,		
	NEDA_FONTSIZE   = 0x0000000000000010,		
	NEDA_FONTBOLD   = 0x0000000000000020,		
	NEDA_FONTITALIC = 0x0000000000000040,		
	NEDA_FONTSTRIKE = 0x0000000000000080,		
	NEDA_FONTUNDER  = 0x0000000000000100,		

	NEDA_ALIGNMENT  = 0x0000000000000200,
	NEDA_PRINTABLE	= 0x0000000000000400,

	NEDA_STYLE		= 0x0000000000000800,
	NEDA_STYLEITEM	= 0x0000000000001000,

	NEDA_BORDERSTYLE= 0x0000000000002000,
	NEDA_BORDERCOLOR= 0x0000000000004000,
	NEDA_BORDERWIDTH= 0x0000000000008000,
	
	NEDA_FONTCHARSET= 0x0000000000010000,

	NEDA_FONT_ALL	= NEDA_FONTNAME | NEDA_FONTSIZE | NEDA_FONTBOLD | NEDA_FONTITALIC |
					  NEDA_FONTSTRIKE | NEDA_FONTUNDER | NEDA_FONTCHARSET,
	
	NEDA_ALL		= 0xFFFFFFFFFFFFFFFF,
};

//----------------------------------------------------------------------------------------------

enum ened_border_style
{
	NED_BORDER_STYLE_NONE	= 0,
	NED_BORDER_STYLE_SOLID	= 1,
	NED_BORDER_STYLE_ETCHED	= 2,
	NED_BORDER_STYLE_SUNKEN	= 3,
	NED_BORDER_STYLE_BUMP	= 4,
	NED_BORDER_STYLE_RAISED = 5,
	NED_BORDER_STYLE_ROUNDED= 6,
	NED_BORDER_STYLE_ROUNDED_XP_UP		= 7,
	NED_BORDER_STYLE_ROUNDED_XP_DOWN	= 8,
	NED_BORDER_STYLE_TABITEM_HEADER_UP	= 9,
	NED_BORDER_STYLE_TABITEM_HEADER_DOWN= 10,
};

//----------------------------------------------------------------------------------------------

struct ned_border
{
	ned_border() :
		m_eBorderStyle(NED_BORDER_STYLE_NONE),
		m_nBorderPxWidth(1),
		m_clrBorderColor(0,0,0,0)
	{
	}
	void operator = (const ned_border & roBorder);
	
	ng_color get_color() const
	{
		return m_clrBorderColor;
	}
	ened_border_style get_style() const
	{
		return m_eBorderStyle;
	}
	long get_px_width() const
	{
		return m_nBorderPxWidth;
	}

	ened_border_style	m_eBorderStyle;
	long				m_nBorderPxWidth;
	ng_color			m_clrBorderColor;
};

//----------------------------------------------------------------------------------------------

const long STYLE_ID_CURRENT		= 0;
const long STYLE_ITEM_NULL		= -1;

//atrybuty deklarowane

class ned_declattributes
{
public:
	ned_declattributes();
	ned_declattributes(const ned_declattributes & roDeclAttrib);
	void operator = (const ned_declattributes & roDeclAttrib);

	void decl_forecolor(const ng_color & roForeColor);
	void decl_backcolor(const ng_color & roBackColor);
	void decl_backcolor2(const ng_color & roBackColor2);
	void decl_fontspec(const ned_font_spec & roFontSpec,ned_attribute_type eValidMask);

	void decl_alignment(ened_alignment eAlignment);
	void decl_printable(bool bPrintable);
	void decl_styleid(long nStyle);
	void decl_styleitemid(long nStyleItemId);

	void decl_border_style(ened_border_style eBorderStyle);
	void decl_border_color(const ng_color & roBorderColor);
	void decl_border_width(long nPxWidth);
	
	bool is_declared(ned_attribute_type eAttrib) const;

	ng_color get_forecolor() const;
	ng_color get_backcolor() const;
	ng_color get_backcolor2() const;
	const ned_font_spec & get_fontspec(ned_attribute_type & roValidMask) const;
	ened_alignment get_alignment() const;
	bool get_printable() const;
	long get_styleid() const;
	long get_styleitemid() const;
	
	ened_border_style get_border_style() const;
	ng_color get_border_color() const;
	long get_border_width() const;

	void build_string_descriptor(ng_string & roDescriptorString) const;
protected:
	ng_color				m_nForeColor;
	ng_color				m_nBackColor;
	ng_color				m_nBackColor2;
	ned_font_spec			m_oFontSpec;

	ened_alignment			m_eAlignment;
	bool					m_bPrintable;

	long					m_nStyleId;
	long					m_nStyleItemId;

	ned_border				m_oBorder;

	ned_attribute_type		m_oDeclaredMask;
};

//----------------------------------------------------------------------------------------------
class cned_element_manager;

class ned_position
{
public:
	ned_position();
	void operator = (const ned_position & roPosition);
	bool operator ==(const ned_position & roPosition) const;
	
	bool is_left() const
	{
		return ((m_eFlags & epf_horizmask) == epf_left);
	}
	bool is_right() const
	{
		return ((m_eFlags & epf_horizmask) == epf_right);
	}
	bool is_top() const
	{
		return ((m_eFlags & epf_vertmask) == epf_top);
	}
	bool is_bottom() const
	{
		return ((m_eFlags & epf_vertmask) == epf_bottom);
	}
	ng_xdist get_left() const
	{
		ASSERT(is_left());
		return m_nExtLeftRight;
	}
	ng_xdist get_right() const
	{
		ASSERT(is_right());
		return m_nExtLeftRight;
	}
	ng_ydist get_top() const
	{
		ASSERT(is_top());
		return m_nExtTopBottom;
	}
	ng_ydist get_bottom() const
	{
		ASSERT(is_bottom());
		return m_nExtTopBottom;
	}
	void set_top(ng_ydist dyTop)
	{
		m_eFlags = eFlags(m_eFlags | epf_abs | epf_top);
		m_nExtTopBottom = dyTop;
	}
	void set_left(ng_xdist dxLeft)
	{
		m_eFlags = eFlags(m_eFlags | epf_abs | epf_left);
		m_nExtLeftRight = dxLeft;
	}
	void set_right(ng_xdist dxRight)
	{
		m_eFlags = eFlags(m_eFlags | epf_abs | epf_right);
		m_nExtLeftRight = dxRight;
	}
	void set_bottom(ng_ydist dyBottom)
	{
		m_eFlags = eFlags(m_eFlags | epf_abs | epf_bottom);
		m_nExtTopBottom = dyBottom;
	}
	void from_string(LPCTSTR pcString);
private:
	enum eFlags
	{
		epf_auto = 0x00,		//automatic - follow flow
		epf_abs	 = 0x01,		//absolute - offset to parent's rectangle
		epf_modemask = (epf_auto | epf_abs),

		epf_left = 0x02,
		epf_right= 0x04,
		epf_horizmask = (epf_left | epf_right),
		
		epf_top  = 0x08,
		epf_bottom=0x10,
		epf_vertmask = (epf_top | epf_bottom)
	};

	ng_xdist m_nExtLeftRight;	//'declared' left/right in external units
	ng_ydist m_nExtTopBottom;	//'declared' top/bottom in external units
	eFlags	 m_eFlags;
};

//----------------------------------------------------------------------------------------------
class cned_storage_writer;
class cned_storage_reader;

//atrybuty bie¿¹ce	(u¿ywane w powi¹zaniu z ned_element_mini_info)
class ned_currattributes
{
public:
	ned_currattributes() :
		m_nFontIndex(NED_DEFAULT_FONT_INX),
		m_nForeColor(Black),
#ifdef _DEBUG
		m_nBackColor(Red),			//red to see it easy
#else
		m_nBackColor(Black),		//black
#endif
		m_nBackColor2(Black),
		m_nExtWidth(NED_AUTO_WIDTH),
		m_nExtHeight(NED_AUTO_HEIGHT),
		m_eAlignment(eal_left)
	{
	}
	ned_fontinx get_fontinx() const
	{
		return m_nFontIndex;
	}
	ng_color get_forecolor() const
	{
		return m_nForeColor;
	}
	ng_color get_backcolor() const
	{
		return m_nBackColor;
	}
	ng_color get_backcolor2() const
	{
		return m_nBackColor2;
	}
	void set_forecolor(ng_color nForeColor)
	{
		m_nForeColor = nForeColor;
	}
	void set_backcolor(ng_color nBackColor)
	{
		m_nBackColor = nBackColor;
	}
	void set_backcolor2(ng_color nBackColor2)
	{
		m_nBackColor2 = nBackColor2;
	}
	void set_fontinx(ned_fontinx nFontIndex)
	{
		m_nFontIndex = nFontIndex;
	}
	const ned_border & get_border() const
	{
		return m_oBorder;
	}
	ned_border & get_border()
	{
		return m_oBorder;
	}
	void set_extwidth(ng_xdist nExtWidth)
	{
		m_nExtWidth = nExtWidth;
	}
	void set_extheight(ng_ydist nExtHeight)
	{
		m_nExtHeight = nExtHeight;
	}
	ng_xdist get_extwidth() const
	{
		return m_nExtWidth;
	}
	ng_ydist get_extheight() const
	{
		return m_nExtHeight;
	}
	ened_alignment get_alignment() const
	{
		return m_eAlignment;
	}
	void set_aligment(ened_alignment eAlignment)
	{
		m_eAlignment = eAlignment;
	}

	void operator = (const ned_currattributes & roCurrAttrib);
	void inherit_from(const ned_declattributes & roDeclAttributes);
	void inherit_from_parent(const ned_currattributes & roCurrAttrib);
	
private:
	ng_color				m_nForeColor;
	ng_color				m_nBackColor;
	ng_color				m_nBackColor2;
	ned_fontinx				m_nFontIndex;
	ned_border				m_oBorder;		//most elements has all border elements uniform
	ng_xdist				m_nExtWidth;	//'declared' width in external units
	ng_ydist				m_nExtHeight;	//'declared' height in external units
	ened_alignment			m_eAlignment;


	friend cned_storage_writer & operator << (cned_storage_writer &,const ned_currattributes &);
	friend cned_storage_reader & operator >> (cned_storage_reader &,ned_currattributes &);
};


//--------------------------------------------------------------------------------------
//
// definicja elementu stylu (zarz¹dzana przez cned_style)
//
//--------------------------------------------------------------------------------------

class cned_styleitem : public CInterface__, public ned_declattributes
{
public:
	cned_styleitem(){}
};
 
//------------------- inlines ----------------------------------------------------------
inline ned_position::ned_position() :
	m_nExtLeftRight(0),
	m_nExtTopBottom(0),
	m_eFlags(epf_auto)
{
}

inline void ned_position::operator = (const ned_position & roPosition)
{
	m_nExtLeftRight	= roPosition.m_nExtLeftRight;
	m_nExtTopBottom	= roPosition.m_nExtTopBottom;
	m_eFlags		= roPosition.m_eFlags;
}

inline bool ned_position::operator ==(const ned_position & roPosition) const
{
	return 
	(m_nExtLeftRight	== roPosition.m_nExtLeftRight) &&
	(m_nExtTopBottom	== roPosition.m_nExtTopBottom) &&
	(m_eFlags			== roPosition.m_eFlags);
}
//--------------------------------------------------------------------------------------

inline void ned_border::operator = (const ned_border & roBorder)
{
	m_eBorderStyle		= roBorder.m_eBorderStyle;
	m_nBorderPxWidth	= roBorder.m_nBorderPxWidth;
	m_clrBorderColor	= roBorder.m_clrBorderColor;
}

//--------------------------------------------------------------------------------------

inline void ned_currattributes::inherit_from_parent(const ned_currattributes & roCurrAttrib)
{
	m_nForeColor	= roCurrAttrib.m_nForeColor;
	m_nBackColor	= roCurrAttrib.m_nBackColor;
	m_nBackColor2	= roCurrAttrib.m_nBackColor2;
	m_nFontIndex	= roCurrAttrib.m_nFontIndex;
	m_oBorder		= roCurrAttrib.m_oBorder;
	m_eAlignment	= roCurrAttrib.m_eAlignment;
}

inline void ned_currattributes::operator = (const ned_currattributes & roCurrAttrib)
{
	inherit_from_parent(roCurrAttrib);
	m_nExtWidth		= roCurrAttrib.m_nExtWidth;
	m_nExtHeight	= roCurrAttrib.m_nExtHeight;
}

//--------------------------------------------------------------------------------------

inline ned_declattributes::ned_declattributes() :
	m_oDeclaredMask(ned_attribute_type(0)),
	m_nForeColor(Black),
#ifdef _DEBUG
	m_nBackColor(Red),			//red to see it easy
#else
	m_nBackColor(Black),		//black
#endif
	m_nBackColor2(Black),
	m_eAlignment(ened_alignment(0)),
	m_bPrintable(true),
	m_nStyleId(STYLE_ID_CURRENT),
	m_nStyleItemId(STYLE_ITEM_NULL)
{
}

inline ned_declattributes::ned_declattributes(const ned_declattributes & roDeclAttrib)
{
	(*this) = roDeclAttrib;
}

inline void ned_declattributes::operator = (const ned_declattributes & roDeclAttrib)
{
	m_nForeColor		= roDeclAttrib.m_nForeColor;
	m_nBackColor		= roDeclAttrib.m_nBackColor;
	m_nBackColor2		= roDeclAttrib.m_nBackColor2;
	m_oFontSpec			= roDeclAttrib.m_oFontSpec;

	m_eAlignment		= roDeclAttrib.m_eAlignment;
	m_bPrintable		= roDeclAttrib.m_bPrintable;

	m_nStyleId			= roDeclAttrib.m_nStyleId;
	m_nStyleItemId		= roDeclAttrib.m_nStyleItemId;

	m_oBorder			= roDeclAttrib.m_oBorder;

	m_oDeclaredMask = roDeclAttrib.m_oDeclaredMask;
}

inline bool ned_declattributes::is_declared(ned_attribute_type eAttrib) const
{
	return ((m_oDeclaredMask & eAttrib) != 0);
}

inline void ned_declattributes::decl_forecolor(const ng_color & roForeColor)
{
	m_nForeColor = roForeColor;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_FORECOLOR);
}

inline void ned_declattributes::decl_backcolor(const ng_color & roBackColor)
{
	m_nBackColor = roBackColor;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_BACKCOLOR);
}

inline void ned_declattributes::decl_backcolor2(const ng_color & roBackColor2)
{
	m_nBackColor2 = roBackColor2;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_BACKCOLOR2);
}

inline void ned_declattributes::decl_fontspec(const ned_font_spec & roFontSpec,ned_attribute_type eValidMask)
{
	m_oFontSpec = roFontSpec;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | eValidMask);
}

inline void ned_declattributes::decl_alignment(ened_alignment eAlignment)
{
	m_eAlignment = eAlignment;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_ALIGNMENT);
}

inline void ned_declattributes::decl_printable(bool bPrintable)
{
	m_bPrintable = bPrintable;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_PRINTABLE);
}

inline void ned_declattributes::decl_styleid(long nStyle)
{
	m_nStyleId = nStyle;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_STYLE);
}

inline void ned_declattributes::decl_styleitemid(long nStyleItemId)
{
	m_nStyleItemId = nStyleItemId;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_STYLEITEM);
}

inline void ned_declattributes::decl_border_style(ened_border_style eBorderStyle)
{
	m_oBorder.m_eBorderStyle = eBorderStyle;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_BORDERSTYLE);
}

inline void ned_declattributes::decl_border_color(const ng_color & roBorderColor)
{
	m_oBorder.m_clrBorderColor = roBorderColor;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_BORDERCOLOR);
}

inline void ned_declattributes::decl_border_width(long nPxWidth)
{
	m_oBorder.m_nBorderPxWidth = nPxWidth;
	m_oDeclaredMask = ned_attribute_type(m_oDeclaredMask | NEDA_BORDERWIDTH);
}

inline ng_color ned_declattributes::get_forecolor() const
{
	ASSERT(is_declared(NEDA_FORECOLOR));
	return m_nForeColor;
}

inline ng_color ned_declattributes::get_backcolor() const
{
	ASSERT(is_declared(NEDA_BACKCOLOR));
	return m_nBackColor;
}

inline ng_color ned_declattributes::get_backcolor2() const
{
	ASSERT(is_declared(NEDA_BACKCOLOR2));
	return m_nBackColor2;
}

inline const ned_font_spec & ned_declattributes::get_fontspec(ned_attribute_type & roValidMask) const
{
	roValidMask = ned_attribute_type(m_oDeclaredMask & (NEDA_FONT_ALL));
	return m_oFontSpec;
}

inline ened_alignment ned_declattributes::get_alignment() const
{
	ASSERT(is_declared(NEDA_ALIGNMENT));
	return m_eAlignment;
}

inline bool ned_declattributes::get_printable() const
{
	ASSERT(is_declared(NEDA_PRINTABLE));
	return m_bPrintable;
}

inline long ned_declattributes::get_styleid() const
{
	ASSERT(is_declared(NEDA_STYLE));
	return m_nStyleId;
}

inline long ned_declattributes::get_styleitemid() const
{
	ASSERT(is_declared(NEDA_STYLEITEM));
	return m_nStyleItemId;
}

inline ened_border_style ned_declattributes::get_border_style() const
{
	ASSERT(is_declared(NEDA_BORDERSTYLE));
	return m_oBorder.get_style();
}

inline ng_color ned_declattributes::get_border_color() const
{
	ASSERT(is_declared(NEDA_BORDERCOLOR));
	return m_oBorder.get_color();
}

inline long ned_declattributes::get_border_width() const
{
	ASSERT(is_declared(NEDA_BORDERWIDTH));
	return m_oBorder.get_px_width();
}


//----------------------------------------------------------------------------------------------

inline long border_style_to_frame_mask(ened_border_style eStyle,long nEdgeMask)
{
	switch(eStyle)
	{
	case NED_BORDER_STYLE_NONE:
		return NG_FRAME_EDGE_FLAT;
	case NED_BORDER_STYLE_SOLID:
		return NG_FRAME_EDGE_FLAT | nEdgeMask;
	case NED_BORDER_STYLE_ETCHED:
		return NG_FRAME_EDGE_ETCHED | nEdgeMask;
	case NED_BORDER_STYLE_SUNKEN:
		return NG_FRAME_EDGE_SUNKEN | nEdgeMask;
	case NED_BORDER_STYLE_BUMP:
		return NG_FRAME_EDGE_BUMP | nEdgeMask;
	case NED_BORDER_STYLE_RAISED:
		return NG_FRAME_EDGE_RAISED | nEdgeMask;
	case NED_BORDER_STYLE_ROUNDED:
		return NG_FRAME_EDGE_ROUNDED_FLAT | nEdgeMask;
	case NED_BORDER_STYLE_ROUNDED_XP_UP:
		return NG_FRAME_EDGE_ROUNDED_XP | nEdgeMask;
	case NED_BORDER_STYLE_ROUNDED_XP_DOWN:
		return NG_FRAME_EDGE_ROUNDED_XP2 | nEdgeMask;
	case NED_BORDER_STYLE_TABITEM_HEADER_UP:
		return NG_FRAME_EDGE_RAISEDOUTER | NG_FRAME_LEFT | NG_FRAME_TOP | NG_FRAME_RIGHT;
	case NED_BORDER_STYLE_TABITEM_HEADER_DOWN:
		return NG_FRAME_EDGE_SUNKENOUTER | NG_FRAME_ALL;
	default:
		return NG_FRAME_EDGE_FLAT;
	}
}

inline void ned_position::from_string(LPCTSTR pcString)
{
	//recognized format:
	//{[L|R][nnn|*],{[T|B][nnn|*]}

	//parse first part (horizontal coordinate)
	bool bLeft = true;
	if(ToUpper(*pcString) == 'R')	//right
	{
		bLeft = false;
		pcString++;
	}
	else
	{
		if(ToUpper(*pcString) == 'L')	//left - default
		{
			pcString++;
		}
	}
	if(*pcString != '*')
	{
		LPTSTR pcEnd;
		long dX= _tcstol(pcString,&pcEnd,10);
		if(bLeft)
		{
			set_left(dX);
		}
		else
		{
			set_right(dX);
		}
		pcString = pcEnd;
	}
	else
	{
		pcString++;
	}

	if(*pcString != ',')
	{
		ASSERT(false);		//syntax error
		return;	
	}
	pcString++;

	//parse second part (vertical coordinate)
	bool bTop = true;
	if(ToUpper(*pcString) == 'B')	//bottom
	{
		bTop = false;
		pcString++;
	}
	else
	{
		if(ToUpper(*pcString) == 'T')	//top
		{
			pcString++;
		}
	}

	if(*pcString != '*')
	{
		LPTSTR pcEnd;
		long dY= _tcstol(pcString,&pcEnd,10);
		if(bTop)
		{
			set_top(dY);
		}
		else
		{
			set_bottom(dY);
		}
	}
}


}

#else
	#error __FILE__ already included
#endif

