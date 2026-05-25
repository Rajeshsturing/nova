/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CUIAttributes - klasa bazowa atrybutów CUIElementu
*/

#ifndef _UIATTRIBUTES_H_
#define _UIATTRIBUTES_H_

class CStyleAndFontProvider;

enum EUIAttributeType
{
	UIA_POSITIONABSX = 0x00000002,		//position='nnnn,?'
	UIA_POSITIONABSY = 0x00000004,		//position='?,nnnn'
	UIA_DECLWIDTH	 = 0x00000008,		//width='nnnn'
	UIA_DECLHEIGHT	 = 0x00000010,		//height='nnnn'
	
	UIA_FORECOLOR	 = 0x00000020,		//forecolor='cccc'
	UIA_BACKCOLOR	 = 0x00000040,		//backcolor='cccc'
	
	UIA_FONTNAME	 = 0x00000080,		//font='name'	
	UIA_FONTSIZE	 = 0x00000100,		//fontsize='nnnn'
	UIA_FONTBOLD	 = 0x00000200,		//bold=true/false
	UIA_FONTITALIC	 = 0x00000400,		//italic='true/false'
	UIA_FONTSTRIKE	 = 0x00000800,		//strikethrough='true/false'
	
	UIA_ALIGNMENT	 = 0x00001000,		//align='left/right/center/justify'
	
	UIA_LBORDERTYPE	 = 0x00002000,		//lborder='nnnn'
	UIA_LBORDERWIDTH = 0x00004000,		//lborderwidth='nnnn'
	UIA_LBORDERCOLOR = 0x00008000,		//lbordercolor='cccc'

	UIA_RBORDERTYPE	 = 0x00010000,		//rborder='nnnn'
	UIA_RBORDERWIDTH = 0x00020000,		//rborderwidth='nnnn'
	UIA_RBORDERCOLOR = 0x00040000,		//rbordercolor='cccc'

	UIA_TBORDERTYPE	 = 0x00080000,		//tborder='nnnn'
	UIA_TBORDERWIDTH = 0x00100000,		//tborderwidth='nnnn'
	UIA_TBORDERCOLOR = 0x00200000,		//tbordercolor='cccc'

	UIA_BBORDERTYPE	 = 0x00400000,		//bborder='nnnn'
	UIA_BBORDERWIDTH = 0x00800000,		//bborderwidth='nnnn'
	UIA_BBORDERCOLOR = 0x01000000,		//bbordercolor='cccc'

	UIA_HIDDEN		 = 0x02000000,		//hide='true/false'
	UIA_RONLYDISABLED= 0x04000000,		//readonly='true/false' disabled='true/false'

	UIA_STYLEITEM	 = 0x08000000,		//style='nnnn'
	UIA_STYLE		 = 0x10000000,		//style='nnnn:mmmmm'
	UIA_PRINTABLE	 = 0x20000000,		//print='true/false'
	UIA_IMAGEID		 = 0x40000000,		//image='nnnn'
};

enum EUIAttributeType2
{
	UIA_BACKCOLOR2	 = 0x00000002,		//second backcolor used in gradient fill
};

enum ElementActivityMode
{
	normal		= 0x00,
	readonly	= 0x01,
	disabled	= 0x02,

	ignoresysdisable = 0x08,
};

const long BORDERSTYLE_NONE		= 0;
const long BORDERSTYLE_SOLID	= 1;
const long BORDERSTYLE_ETCHED	= 2;
const long BORDERSTYLE_SUNKEN	= 3;
const long BORDERSTYLE_BUMP		= 4;
const long BORDERSTYLE_RAISED	= 5;

struct BorderStyle
{
	BorderStyle() :
		//to_do: inicjowanie ma byæ zgodne z typami ramki które zostan¹ dopiero wymyœlone
		m_nBorderType(BORDERSTYLE_NONE),
		m_nBorderWidth(1),
		m_nBorderColor(RGB(0,0,0))
	{
	}
	BorderStyle(const BorderStyle & roBorderStyle) :
		m_nBorderType(roBorderStyle.m_nBorderType),
		m_nBorderWidth(roBorderStyle.m_nBorderWidth),
		m_nBorderColor(roBorderStyle.m_nBorderColor)
	{
	}
	
	virtual void operator = (const BorderStyle & roBorderStyle)
	{
		m_nBorderType	= roBorderStyle.m_nBorderType;
		m_nBorderWidth	= roBorderStyle.m_nBorderWidth;
		m_nBorderColor	= roBorderStyle.m_nBorderColor;
	}

	long			m_nBorderType;
	long			m_nBorderWidth;
	_colordesc		m_nBorderColor;
};

enum eBorderElement
{
	be_left		= 0,
	be_top		= 1,
	be_right	= 2,
	be_bottom	= 3
};

const long CURRENT_STYLE		=  0;
const long INVALID_STYLEITEM	= -1;
const long INVALID_FONTINX		= -1;
const long INVALID_POSABS		= -2;
const long INVALID_DIMENSION	= -2;
const long AUTOMATIC_DIMENSION	= LONG_MAX;
const long MINIMAL_DIMENSION	= LONG_MAX-1;
const long MAXIMAL_DIMENSION	= LONG_MAX-2;
const long INAVLID_IMAGEID		= -1;


inline bool IsSpecialDimension(long nDimension) 
{
	return (nDimension >= MAXIMAL_DIMENSION);
}

inline long NormalizeDimension(long nDimension)
{
	if(IsSpecialDimension(nDimension))
	{
		return 0;
	}
	return nDimension;
}

class CUIAttributes
{
public:
	CUIAttributes();
	CUIAttributes(const CUIAttributes & roUIAttributes);
	virtual void operator = (const CUIAttributes & roUIAttributes);
	void Inherit(const CUIAttributes & roUIAttributes,CStyleAndFontProvider * poSAFP);	//inherits attributes, clears mask

	bool IsAttributeDecl(EUIAttributeType eUIATTest) const
	{
		return (eUIATTest & m_oDeclMask) != 0;
	}
	bool IsAttributeDecl2(EUIAttributeType2 eUIATTest) const
	{
		return (eUIATTest & m_oDeclMask2) != 0;
	}
	bool IsHidden() const
	{
		return m_bHidden;
	}
	bool IsDisabled() const
	{
		return (m_nActMode & disabled) != 0;
	}
	bool IsReadOnly() const
	{
		return (m_nActMode & readonly) != 0;
	}
	bool IsIgnoreSysDisable() const
	{
		return (m_nActMode & ignoresysdisable) != 0;
	}

	bool IsPrintable() const
	{
		return m_bPrintable;
	}

	long GetPositionAbsX() const
	{
		ASSERT(m_oDeclMask & UIA_POSITIONABSX);
		return m_nPosAbsX;
	}
	long GetPositionAbsY() const
	{
		ASSERT(m_oDeclMask & UIA_POSITIONABSY);
		return m_nPosAbsY;
	}
	long GetDeclWidth() const
	{
		ASSERT(m_oDeclMask & UIA_DECLWIDTH);
		return m_nDeclWidth;
	}
	long GetDeclHeight() const
	{
		ASSERT(m_oDeclMask & UIA_DECLHEIGHT);
		return m_nDeclHeight;
	}

	long GetBorderType(eBorderElement eborderelement) const
	{
		return m_aBorderStyle[ eborderelement ].m_nBorderType;
	}
	
	long GetBorderWidth(eBorderElement eborderelement) const
	{
		return m_aBorderStyle[ eborderelement ].m_nBorderWidth;
	}
	_colordesc GetBorderColor(eBorderElement eborderelement) const
	{
		return m_aBorderStyle[ eborderelement ].m_nBorderColor;
	}

	long GetStyleItemId() const
	{
		ASSERT(m_oDeclMask & UIA_STYLEITEM);
		ASSERT(m_nStyleItemId != INVALID_STYLEITEM);
		return m_nStyleItemId;
	}
	long GetStyleId() const
	{
		ASSERT(m_oDeclMask & UIA_STYLE);
		return m_nStyleId;
	}
	long GetFontInx() const
	{
		ASSERT(m_nFontInx != INVALID_FONTINX);
		return m_nFontInx;
	}
	_colordesc GetForeColor() const
	{
		ASSERT(m_nForeColor != INVALIDCOLOR);
		ASSERT(m_oDeclMask & UIA_FORECOLOR);
		return m_nForeColor;
	}
	_colordesc GetBackColor() const
	{
		ASSERT(m_nBackColor != INVALIDCOLOR);
		ASSERT(m_oDeclMask & UIA_BACKCOLOR);
		return m_nBackColor;
	}
	_colordesc GetBackColor2() const
	{
		ASSERT(m_nBackColor2 != INVALIDCOLOR);
		ASSERT(m_oDeclMask2 & UIA_BACKCOLOR2);
		return m_nBackColor2;
	}
	long GetAlignment() const
	{
		ASSERT(m_oDeclMask & UIA_ALIGNMENT);
		return m_nAlignment;
	}
	long GetImageId() const
	{
		ASSERT(m_oDeclMask & UIA_IMAGEID);
		return m_nImageId;
	}

	void SetFontInx(long nFontInx)
	{
		m_nFontInx = nFontInx;
	}

	//declare attribute, also runtime settings
	void DeclareAttribute(EUIAttributeType eUIAttribute)
	{
		m_oDeclMask = EUIAttributeType(m_oDeclMask | eUIAttribute);
	}

	void DeclarePosAbsX(long nPosAbsX)
	{
		m_nPosAbsX = nPosAbsX;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_POSITIONABSX);
	}
	void DeclarePosAbsY(long nPosAbsY)
	{
		m_nPosAbsY = nPosAbsY;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_POSITIONABSY);
	}
	void DeclareWidth(long nWidth)
	{
		m_nDeclWidth = nWidth;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_DECLWIDTH);
	}
	void DeclareHeight(long nHeight)
	{
		m_nDeclHeight = nHeight;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_DECLHEIGHT);
	}
	void DeclareHide(bool bHide)
	{
		m_bHidden = bHide;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_HIDDEN);
	}
	void DeclarePrintable(bool bPrintable)
	{
		m_bPrintable = bPrintable;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_PRINTABLE);
	}
	void DeclareReadOnly(bool bReadOnly)
	{
		if(bReadOnly)
		{
			m_nActMode |= readonly;
		}
		else
		{
			m_nActMode &= ~readonly;
		}
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RONLYDISABLED);
	}
	void DeclareIgnoreSysDisable(bool bIgnore)
	{
		if(bIgnore)
		{
			m_nActMode |= ignoresysdisable;
		}
		else
		{
			m_nActMode &= ~ignoresysdisable;
		}
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RONLYDISABLED);
	}
	void DeclareDisabled(bool bDisabled)
	{
		if(bDisabled)
		{
			m_nActMode |= disabled;
		}
		else
		{
			m_nActMode &= ~disabled;
		}
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RONLYDISABLED);
	}
	void DeclareForeColor(_colordesc nForeColor)
	{
		m_nForeColor = nForeColor;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_FORECOLOR);
	}
	void DeclareBackColor(_colordesc nBackColor)
	{
		m_nBackColor = nBackColor;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_BACKCOLOR);
	}
	void DeclareBackColor2(_colordesc nBackColor2)
	{
		m_nBackColor2 = nBackColor2;
		m_oDeclMask2 = EUIAttributeType2(m_oDeclMask2 | UIA_BACKCOLOR2);
	}
	void DeclareStyleItemId(long nStyleItemId)
	{
		m_nStyleItemId = nStyleItemId;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_STYLEITEM);
	}
	void DeclareStyleId(long nStyleId)
	{
		m_nStyleId = nStyleId;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_STYLE);
	}
	void DeclareAlignment(long nAlignment)
	{
		m_nAlignment = nAlignment;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_ALIGNMENT);
	}
	void DeclareImageId(long nImageId)
	{
		m_nImageId = nImageId;
		m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_IMAGEID);
	}
	void DeclareBorderType(eBorderElement eborderelement,long nBorderType)
	{
		switch(eborderelement)
		{
		case be_left:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_LBORDERTYPE);
		break;
		case be_top:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_TBORDERTYPE);
		break;
		case be_right:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RBORDERTYPE);
		break;
		case be_bottom:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_BBORDERTYPE);
		break;
		default:
			ASSERT(false);
		}
		m_aBorderStyle[ eborderelement ].m_nBorderType = nBorderType;
	}
	void DeclareBorderWidth(eBorderElement eborderelement,long nBorderWidth)
	{
		switch(eborderelement)
		{
		case be_left:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_LBORDERWIDTH);
		break;
		case be_top:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_TBORDERWIDTH);
		break;
		case be_right:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RBORDERWIDTH);
		break;
		case be_bottom:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_BBORDERWIDTH);
		break;
		default:
			ASSERT(false);
		}
		m_aBorderStyle[ eborderelement ].m_nBorderWidth = nBorderWidth;
	}
	void DeclareBorderColor(eBorderElement eborderelement,_colordesc colorref)
	{
		switch(eborderelement)
		{
		case be_left:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_LBORDERCOLOR);
		break;
		case be_top:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_TBORDERCOLOR);
		break;
		case be_right:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_RBORDERCOLOR);
		break;
		case be_bottom:
			m_oDeclMask = EUIAttributeType(m_oDeclMask | UIA_BBORDERCOLOR);
		break;
		default:
			ASSERT(false);
		}
		m_aBorderStyle[ eborderelement ].m_nBorderColor = colorref;
	}

private:
	long				m_nPosAbsX;
	long				m_nPosAbsY;
	long				m_nDeclWidth;
	long				m_nDeclHeight;

	_colordesc			m_nForeColor;
	_colordesc			m_nBackColor;
	_colordesc			m_nBackColor2;

	long				m_nFontInx;

	long				m_nAlignment;

	BorderStyle			m_aBorderStyle[4];

	bool				m_bHidden;
	long				m_nActMode;
	bool				m_bPrintable;
	long				m_nImageId;
	
	//
	//to pole ma podwójne znaczenie,
	//w UIAttributes oznacza, czy podano attrybut style='idstyle'
	//w CStyleItem oznacza id tego w³aœnie item'a (logiczny odpowiednik "this")
	//
	//
	long				m_nStyleId;
	long				m_nStyleItemId;
	
	EUIAttributeType	m_oDeclMask;
	EUIAttributeType2	m_oDeclMask2;
};

#else
	#error __FILE__ already included
#endif
