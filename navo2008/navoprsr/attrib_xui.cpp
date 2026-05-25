/*
	NAVO Enterprise (2002)
	2002-07-13

	translator atrybutów		
*/


#include "stdafx.h"
#include "..\navogal\ngal_iface.h"
#include "..\navoui\common_ned_inc.h"		//common includes

using namespace ned;

#include "attrib_xui.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR * pcAttribIdent						= _T("name");
static const TCHAR * pcAttribFore				= _T("forecolor");
static const TCHAR * pcAttribBack				= _T("backcolor");
static const TCHAR * pcAttribBack2				= _T("backcolor2");
static const TCHAR * pcAttribFontName			= _T("font");
static const TCHAR * pcAttribFontBold			= _T("bold");
static const TCHAR * pcAttribFontItalic			= _T("italic");
static const TCHAR * pcAttribFontStrike			= _T("strike");
static const TCHAR * pcAttribFontUnderline		= _T("underline");
static const TCHAR * pcAttribFontSize			= _T("fontsize");
static const TCHAR * pcAttribFontCharSet		= _T("fontcharset");
static const TCHAR * pcAttribPrint				= _T("print");
static const TCHAR * pcAttribAlign				= _T("align");
static const TCHAR * pcAttribVAlign				= _T("valign");
static const TCHAR * pcAttribStyle				= _T("style");
static const TCHAR * pcAttribImage				= _T("image");
static const TCHAR * pcAttribHREF				= _T("href");

static const TCHAR * pcAttribBorderStyle		= _T("border");
static const TCHAR * pcAttribBorderWidth		= _T("borderwidth");
static const TCHAR * pcAttribBorderColor		= _T("bordercolor");
static const TCHAR * pcAttribSKey				= _T("skey");
static const TCHAR * pcAttribAbsPos				= _T("position");
static const TCHAR * pcAttribMargins			= _T("margins");

static const TCHAR * pcTokenTrue				= _T("true");

static const TCHAR * pcAlignLeft				= _T("left");
static const TCHAR * pcAlignRight				= _T("right");
static const TCHAR * pcAlignCenter				= _T("center");
static const TCHAR * pcAlignJust				= _T("justify");

const TCHAR * pcAlignTop				= _T("top");
const TCHAR * pcAlignBottom				= _T("bottom");
const TCHAR * pcAlignVCenter			= _T("vcenter");

static const TCHAR * pcWidthAuto				= _T("auto");
static const TCHAR * pcWidthMin					= _T("min");
static const TCHAR * pcWidthMax					= _T("max");


struct CSysColors
{
	int			m_nSysInx;
	LPCTSTR		m_pszName;
};

static CSysColors _g_syscolor[] =
{
	{	COLOR_ACTIVECAPTION,	"win.activecaption"	},	
	{	COLOR_MENU,				"win.menu"			},	
	{	COLOR_WINDOWTEXT,		"win.windowtext"	},	
	{	COLOR_WINDOW,			"win.window"		},	
	{	COLOR_HIGHLIGHT,		"win.highlight"		},
	{	COLOR_HIGHLIGHTTEXT,	"win.highlighttext" },
	{	COLOR_BTNFACE,			"win.btnface"		},
	{	COLOR_BTNSHADOW,		"win.btnshadow"		},
	{	COLOR_BTNHIGHLIGHT,		"win.btnhighlight"	},
};

struct CPredefColors
{
	CPredefColors(COLORREF clr,LPCTSTR lpName) :
		m_color(clr),
		m_pszName(lpName)
	{
	}
	CPredefColors(ng_color ngcolor,LPCTSTR lpName) :
		m_color(ngcolor),
		m_pszName(lpName)
	{
	}
	ng_color	m_color;
	LPCTSTR		m_pszName;
};

static CPredefColors _g_stdcolors[] =
{
	 CPredefColors(White, _T("WHITE")	),	//bia³y
	 CPredefColors(Black, _T("BLACK")	),	//czarny
	 CPredefColors(Red, _T("RED")	),	//czerwony
	 CPredefColors(RGB(0x00,0x80,0x00), _T("GREEN")	),	//zielony	
	 CPredefColors(RGB(0x00,0x00,0xff), _T("BLUE")	),	//niebieski	
	 CPredefColors(RGB(0x00,0xff,0xff), _T("AQUA")	),	//b³êkit
	 CPredefColors(RGB(0xff,0x00,0xff), _T("FUCHSIA")),	//fiolet
	 CPredefColors(RGB(0xff,0xff,0x00), _T("YELLOW")	),	//¿ó³ty
	 CPredefColors(RGB(0x00,0x80,0x80), _T("TEAL")	),
	 CPredefColors(RGB(0xC0,0xC0,0xC0), _T("SILVER")	),
	 CPredefColors(RGB(0x80,0x80,0x80), _T("GRAY")	),
	 CPredefColors(RGB(0x00,0xFF,0x00), _T("LIME")	),
	 CPredefColors(RGB(0x80,0x00,0x00), _T("MAROON")	),
	 CPredefColors(RGB(0x00,0x00,0x80), _T("NAVY")	),
	 CPredefColors(RGB(0x00,0x80,0x08), _T("OLIVE")	),
	 CPredefColors(RGB(0x80,0x00,0x80), _T("PURPLE")	),
	 CPredefColors(RGB(0x80,0x00,0x00), _T("BROWN")	),
	 CPredefColors(Transparent,			_T("TRANSPARENT") ),
};

//string to color conversion

static void string2color(const ng_string & roString,ng_color & rColor)
{
	if(roString.GetLength() < 3)
	{
		ASSERT(false);		//z³y kolor
		rColor = Invalid;
		return;
	}
	TCHAR cFirst = roString[0];

	if(cFirst == '#' || isdigit(cFirst))
	{
		goto HEXDIGIT;
	}
	
	cFirst = TCHAR(ToUpper(cFirst));
	if(cFirst == 'A' || cFirst == 'B' || cFirst == 'F')
	{
		//moze liczba moze nazwa koloru
		if(toupper(roString[1]) <= 'F')
		{
			goto HEXDIGIT;
		}
	}
	long i;

	for(i=0; i < sizeof(_g_stdcolors) / sizeof(_g_stdcolors[0]); i++)
	{
		const CPredefColors * pColors = _g_stdcolors + i;
		if(!roString.CompareNoCase(pColors->m_pszName))
		{
			rColor = pColors->m_color;
			return;
		}
	}
	for(i=0; i < sizeof(_g_syscolor) / sizeof(_g_syscolor[0]); i++)
	{
		const CSysColors * pSysColor = _g_syscolor + i;
		if(!roString.CompareNoCase(pSysColor->m_pszName))
		{
			rColor = ng_color::system(pSysColor->m_nSysInx);
			return;
		}
	}
	ASSERT(false);		//z³y kolor
	rColor = Invalid;
	return;
HEXDIGIT:
	COLORREF color = _tcstoul((LPCTSTR)roString+1,NULL,16);
	rColor = ng_color(GetBValue(color),GetGValue(color),GetRValue(color),BYTE(color >> 24));
}

//translate atribute to color value

bool translate_attrib_color(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,ng_color & rColor)
{
	ng_string oValueString;
	if(!roAttributes.Lookup(pcAttribName,oValueString))
	{
		return false;
	}
	string2color(oValueString,rColor);
	return true;
}

//translate atribute to boolean value

bool translate_attrib_boolean(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,bool & rnValue)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribName,oValueString))
	{
		if(oValueString.CompareNoCase(pcTokenTrue) == 0 || oValueString == "1")
		{
			rnValue = true;
		}
		else
		{
			rnValue = false;
		}
		return true;
	}
	return false;
}

bool translate_attrib_long(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,long & rnValue)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribName,oValueString))
	{
		rnValue = _ttol(oValueString);
		return true;
	}
	return false;
}

//translate atribute to element identifier

bool translate_attrib_ident(const CMapStringToString & roAttributes,ned_ident & rnIdent)
{
	ng_string oString;
	if(!roAttributes.Lookup(pcAttribIdent,oString))
	{
		return false;
	}

	if(oString.IsEmpty())
	{
		ThrowNavoException1(ERCO_PARSE_BAD_ELEMENT_IDENT,IDPAGE_NOTAVAILABLE,"");
	}
	LPCTSTR lpString = oString;
	if(!IsDigit(*lpString) && *lpString != '-' && *lpString != '+')	
	{
		lpString++;
	}
	rnIdent = (ned_ident) _ttol(lpString);
	if(rnIdent == 0)
	{
		ThrowNavoException1(ERCO_PARSE_BAD_ELEMENT_IDENT,IDPAGE_NOTAVAILABLE,oString);
	}
	return true;
}

//translate atribute to alignment

bool translate_attrib_alignment(const CMapStringToString & roAttributes,ened_alignment & reAlign)
{
	ng_string oValueString;
	reAlign = ened_alignment(0);
	bool bResult = false;
	if(roAttributes.Lookup(pcAttribAlign,oValueString))
	{
		bResult = true;
		if(oValueString == pcAlignLeft)
		{
			reAlign = ened_alignment(reAlign | eal_left);
		}
		else if(oValueString == pcAlignRight)
		{
			reAlign = ened_alignment(reAlign | eal_right);
		}
		else if(oValueString == pcAlignCenter)
		{
			reAlign = ened_alignment(reAlign | eal_center);
		}
		else if(oValueString == pcAlignJust)
		{
			reAlign = ened_alignment(reAlign | eal_justify);
		}
	}
	if(roAttributes.Lookup(pcAttribVAlign,oValueString))
	{
		bResult = true;
		if(oValueString == pcAlignTop)
		{
			reAlign = ened_alignment(reAlign | eal_top);
		}
		else if(oValueString == pcAlignBottom)
		{
			reAlign = ened_alignment(reAlign | eal_bottom);
		}
		else if(oValueString == pcAlignVCenter)
		{
			reAlign = ened_alignment(reAlign | eal_vcenter);
		}
	}
	return bResult;
}

//translate atribute set to font description

bool translate_attrib_font(const CMapStringToString & roAttributes,ned_font_spec & roFontSpec,ned_attribute_type & roMask)
{
	//zero validity mask
	roMask = ned_attribute_type(0);

	bool bBold;
	if(translate_attrib_boolean(roAttributes,pcAttribFontBold,bBold))
	{
		roFontSpec.m_bBold = bBold;
		roMask = ned_attribute_type(roMask | NEDA_FONTBOLD);
	}
	bool bItalic;
	if(translate_attrib_boolean(roAttributes,pcAttribFontItalic,bItalic))
	{
		roFontSpec.m_bItalic = bItalic;
		roMask = ned_attribute_type(roMask | NEDA_FONTITALIC);
	}
	bool bStrike;
	if(translate_attrib_boolean(roAttributes,pcAttribFontStrike,bStrike))
	{
		roFontSpec.m_bStrikeThrough = bStrike;
		roMask = ned_attribute_type(roMask | NEDA_FONTSTRIKE);
	}
	bool bUnderLine;
	if(translate_attrib_boolean(roAttributes,pcAttribFontUnderline,bUnderLine))
	{
		roFontSpec.m_bUnderLine = bUnderLine;
		roMask = ned_attribute_type(roMask | NEDA_FONTUNDER);
	}

	if(translate_attrib_long(roAttributes,pcAttribFontSize,roFontSpec.m_nSize))
	{
		roMask = ned_attribute_type(roMask | NEDA_FONTSIZE);
	}

	long nCharSet = 0;
	if(translate_attrib_long(roAttributes,pcAttribFontCharSet,nCharSet))
	{
		roMask = ned_attribute_type(roMask | NEDA_FONTCHARSET);
		roFontSpec.m_sCharSet = SHORT(nCharSet);
	}
	
	if(roAttributes.Lookup(pcAttribFontName,roFontSpec.m_oFontNameString))
	{
		roMask = ned_attribute_type(roMask | NEDA_FONTNAME);
	}
	return (roMask != ned_attribute_type(0));
}

bool translate_attrib_style(const CMapStringToString & roAttributes,long & rnStyle,long & rnStyleItem)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribStyle,oValueString))
	{
		int nPos = oValueString.Find(':');
		if(nPos != -1)
		{
			ASSERT(nPos > 0);
			rnStyle = _ttol(oValueString.Left(nPos));
			if(rnStyle == 0)	//nie jest to liczba - Ÿle napisany style=''
			{
				ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,"");
			}
		}
		else
		{
			rnStyle = STYLE_ID_CURRENT;
		}
		rnStyleItem = _ttol(oValueString.Mid(nPos+1));
		if(rnStyleItem == 0)	//nie jest to liczba - Ÿle napisany style=''
		{
#ifdef _DEVELOPER_EDITION_
			CString oString;
			oString.Format("Z³y style= (%s)",oValueString.Mid(nPos+1));
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
#else
			rnStyleItem = STYLE_ITEM_NULL;
#endif
		}
		return true;
	}
	return false;
}

bool translate_attrib_image(const CMapStringToString & roAttributes,CSmartOleVariant & roSOV)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribImage,oValueString))
	{
		long nIdImageList = _ttol(oValueString);
		if(nIdImageList != 0)
		{
			roSOV = CSmartOleVariant(long(nIdImageList),VT_I4);
		}
		else
		{
			roSOV = oValueString;
		}
		return true;
	}
	return false;
}

bool translate_attrib_dimension(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,long & rnDimension)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribName,oValueString))
	{
		rnDimension = _ttol(oValueString);
		if(rnDimension == 0)
		{
			ASSERT(oValueString.GetLength() > 2);
			oValueString.MakeLower();
			if(oValueString == pcWidthAuto)
			{
				rnDimension = NED_AUTO_WIDTH;
			}
			else if(oValueString == pcWidthMin)
			{
				rnDimension = NED_MIN_WIDTH;
			}
			else if(oValueString == pcWidthMax)
			{
				rnDimension = NED_MAX_WIDTH;
			}
		}
		return true;
	}
	return false;
}

bool translate_attrib_href(const CMapStringToString & roAttributes,SCP<CHyperLinkInfo> & rpoHLISP)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribHREF,oValueString))
	{
		rpoHLISP = ReadHLIFromString(oValueString);
		return true;
	}
	return false;
}

bool translate_attrib_shortkey(const CMapStringToString & roAttributes,SCP<cnui_shortkey> & poShortKeySP)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribSKey,oValueString))
	{
		poShortKeySP = NewSCP(new cnui_shortkey(oValueString));
		return true;
	}
	return false;
}

bool translate_attrib_margins(const CMapStringToString & roAttributes,ng_rect & rcMargins)
{
	ng_string oValueString;
	if(roAttributes.Lookup(pcAttribMargins,oValueString))
	{
		//margins=left,top,right,bottom
		long nLeft,nTop,nRight,nBottom;
		if(sscanf(oValueString,"%d,%d,%d,%d",&nLeft,&nTop,&nRight,&nBottom) != 4)
		{
			ASSERT(false);	//nieprawid³owo sformatowane marginesy - throw
			return false;
		}
		rcMargins.set_left(ng_xcoord(nLeft));
		rcMargins.set_top(ng_ycoord(nTop));
		rcMargins.set_right(ng_xcoord(nRight));
		rcMargins.set_bottom(ng_ycoord(nBottom));
		return true;
	}
	return false;
}

bool translate_absolute_position(const CMapStringToString & roAttributes,ned_position & roPosition)
{
	//recognized format:
	//{[L|R][nnn|*],{[T|B][nnn|*]}

	ng_string oValueString;
	if(!roAttributes.Lookup(pcAttribAbsPos,oValueString))
	{
		return false;
	}

	oValueString.TrimLeft();
	oValueString.TrimRight();
	if(oValueString.IsEmpty())
	{
		return false;
	}

	roPosition.from_string(oValueString);
	return true;
}

void translate_common_attrib(ned_declattributes & roDeclAttributes,const CMapStringToString & roAttributes)
{
	//colors

	ng_color nBackColor(0,0,0,0),nBackColor2(0,0,0,0),nForeColor(0,0,0,0);
	if(translate_attrib_color(roAttributes,pcAttribFore,nForeColor))
	{
		roDeclAttributes.decl_forecolor(nForeColor);
	}
	if(translate_attrib_color(roAttributes,pcAttribBack,nBackColor))
	{
		roDeclAttributes.decl_backcolor(nBackColor);
		//auto supply second, to avoid gradient
		roDeclAttributes.decl_backcolor2(nBackColor);
	}
	if(translate_attrib_color(roAttributes,pcAttribBack2,nBackColor2))
	{
		roDeclAttributes.decl_backcolor2(nBackColor2);
	}

	//font
	ned_attribute_type eMask;
	ned_font_spec oFontSpec;
	if(translate_attrib_font(roAttributes,oFontSpec,eMask))
	{
		roDeclAttributes.decl_fontspec(oFontSpec,eMask);
	}

	ened_alignment eAlignment;
	if(translate_attrib_alignment(roAttributes,eAlignment))
	{
		roDeclAttributes.decl_alignment(eAlignment);
	}
	bool bPrintable = false;
	if(translate_attrib_boolean(roAttributes,pcAttribPrint,bPrintable))
	{
		roDeclAttributes.decl_printable(bPrintable);
	}
	long nStyle,nStyleItem;
	if(translate_attrib_style(roAttributes,nStyle,nStyleItem))
	{
		if(nStyle != STYLE_ID_CURRENT)
		{
			roDeclAttributes.decl_styleid(nStyle);
		}
		roDeclAttributes.decl_styleitemid(nStyleItem);
	}
	long nBorderStyle;
	if(translate_attrib_long(roAttributes,pcAttribBorderStyle,nBorderStyle))
	{
		roDeclAttributes.decl_border_style(ened_border_style(nBorderStyle));
	}
	ng_color nBorderColor;
	if(translate_attrib_color(roAttributes,pcAttribBorderColor,nBorderColor))
	{
		roDeclAttributes.decl_border_color(nBorderColor);
	}
	long nBorderWidth;
	if(translate_attrib_long(roAttributes,pcAttribBorderWidth,nBorderWidth))
	{
		roDeclAttributes.decl_border_width(nBorderWidth);
	}
}

void trim_data_string(LPCTSTR lpDataString,ng_string & roOutputString)
{
	roOutputString = lpDataString;
	roOutputString.TrimLeft();
	roOutputString.TrimRight();
}

void normalize_data_string(LPCTSTR lpDataString,ng_string & roOutputString)
{
	roOutputString = lpDataString;
	roOutputString.TrimLeft();
	roOutputString.TrimRight();
	roOutputString.Replace("\x0A",NULL);
	roOutputString.Replace("\x0D",NULL);
	roOutputString.Replace("\x09",NULL);
}
