/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	visual utilities
*/

#ifndef _VIEWUTIL_H_
#define _VIEWUTIL_H_

//predefiniowane rozmiary
const long TOTAL_PAGE_WIDTH  = 21000;
const long TOTAL_PAGE_HEIGHT = 29700;

const long PAGE_MARGIN_CX	 = 1250;
const long PAGE_MARGIN_CY	 = 1250;

const long PAGE_MARGIN_LEFT  = 1250;
const long PAGE_MARGIN_RIGHT = TOTAL_PAGE_WIDTH - 1250;
const long PAGE_MARGIN_TOP	 = 1250;
const long PAGE_MARGIN_BOTTOM= TOTAL_PAGE_HEIGHT - 1250;

// specjalne wartoœci Ident dla UIElementów
const long UIEID_NOELEMENT		= -1;
const long UIEID_BACKGROUND		= -2;
const long UIEID_STARTFOCUS		= -3;
const long UIEID_FIRSTINVALID	= -4;
const long UIEID_FOCUSELEMENT	= -5;
const long UIEID_LASTELEMENT	= -6;

//elementy okreœlone relatywnie
const long UIEID_REL_RIGHT		= -6;
const long UIEID_REL_LEFT		= -7;
const long UIEID_REL_ABOVE		= -8;
const long UIEID_REL_BELOW		= -9;
const long UIEID_REL_NEXT		= -10;
const long UIEID_REL_PREV		= -11;
const long UIEID_REL_NEXT_NOHLI = -12;

const long UIEID_TOP_PAGEMAN	= -20;

const long MCID_ARROW			= 0;
const long MCID_HAND			= 1;
const long MCID_BEAM			= 3;

#define TA_JUSTIFY		1024



enum eMinMaxState
{
	MMS_MINIMIZED	= 1,
	MMS_RESTORED	= 2,
	MMS_MAXIMIZED	= 3
};

//----------------------
// klasy pomocnicze
//----------------------

// SaveDC/RestoreDC hldr

class CSaveDC_Holder
{
public:
	CSaveDC_Holder(CDC * poDC) :
	  m_poDC(poDC)
	{
		ASSERT(m_poDC);
		m_poDC->SaveDC();
	}
	~CSaveDC_Holder()
	{
		m_poDC->RestoreDC(-1);
	}
private:
	CDC * m_poDC;
};



class CDevModeAccessHolder
{
public:
	CDevModeAccessHolder(HANDLE hDevMode) :
		m_hDevMode(hDevMode)
	{
		m_lpDevMode = reinterpret_cast<DEVMODE*>(::GlobalLock(hDevMode));
	}
	~CDevModeAccessHolder()
	{
		::GlobalUnlock(m_hDevMode);
	}
	LPDEVMODE PtrDevMode()
	{
		return m_lpDevMode;
	}
private:
	LPDEVMODE m_lpDevMode;
	HANDLE	  m_hDevMode;
};


void _add_rect_simple_diff(CRepaintArea & roRepaintArea,const _rect & roRect1,const _rect & roRect2);

/*
	konwencja nazewnictwa:
	_raw_navo_		- szybkie funkcje, ale wymagaj¹ aby œrodowisko by³o specjalnie ustawione
	_navo_			- funkcje samodzielne, nie wymagaj¹ ¿adnych dodatkowych ustawieñ

	Uwaga! zak³adamy, ¿e DC jest odpowiednio zamapowane
*/
//------------------ prymitywy graficzne --------------------




//----------------------------------------------
// zwraca aktualnie ustawiony zoom (100 = x1, 25 = x4 , 200 = x 1/2)
//----------------------------------------------
inline long _navo_getzoom(CDC & roDC);


//------------------CRysunekBitmap--------------
//
//	Klasa maluj¹ca bitmapê lub dwie
//
//----------------------------------------------

class CRysunekBitmap : public CInterface__
{
public:
	CRysunekBitmap( HBITMAP hOnBlackBitamp, 
					HBITMAP hOnWhiteBitmap = (HBITMAP) NULL);
	virtual ~CRysunekBitmap()
	{}
	virtual void Draw(CDC* poDC,_rect oRect,bool bVertCenter,bool bHorizCenter);
	CSize GetSizeOnDC(CDC* poDC) const;
	CSize GetDPSize() const
	{ 
		return m_oDPSize; 
	}
protected:
	CSize m_oDPSize;
	CBitmap m_aoBitmap[ 2 ];
	enum
	{ 
		eOnBlack0 = 0, 
		eOnWhite1 = 1 
	};
};

//------specjalizowane klasy do malowania konkretnych rzeczy-----
class CRysunekFocus
{
public:
	CRysunekFocus()
	{
	}
	~CRysunekFocus()
	{
	}
	void Draw(CDC* poDC,_rect oRect);
private:
	SCP<CRysunekBitmap> m_poRysunekBmpSP;
};

extern CRysunekFocus _g_oRysunekFocus;

//----------CNavoVirtKey----------------
//
//	definicje skrótów klawiszowych 
//
//--------------------------------------

class CNavoVirtKey
{
public:
	CNavoVirtKey() :
		m_nKey(0),
		m_nFlags(0),
		m_bEmpty(true)
	{}
	CNavoVirtKey(const CString &oKeyDescription)
	{
		*this = oKeyDescription;
	}
	CNavoVirtKey(UINT nKey, UINT nFlags) :
		m_nKey(nKey),
		m_nFlags(nFlags),
		m_bEmpty(false)
	{}

	enum
	{
		ALT_FLAG	= 0x01,
		CTRL_FLAG	= 0x02,
		SHIFT_FLAG	= 0x04
	};

	CNavoVirtKey &operator=(const CString &oKeyDescription);
	CNavoVirtKey &operator=(const CNavoVirtKey &roSecond);
	CString AddUserDescription(const CString &oText) const;
	CString GetDescription() const;
	static CString GetKeyName(UINT nKeyCode);
	CString GetKeyName() const
	{
		ASSERT(!m_bEmpty);
		return GetKeyName(m_nKey);
	}
	bool IsEmpty() const
	{
		return m_bEmpty;
	}
	void MakeEmpty()
	{
		m_bEmpty = true;
	}
	UINT GetKey() const
	{
		ASSERT(!IsEmpty());
		return m_nKey;
	}
	bool IsAlt() const
	{
		return (GetFlags() & ALT_FLAG) != 0;
	}
	bool IsCtrl() const
	{
		return (GetFlags() & CTRL_FLAG) != 0;
	}
	bool IsShift() const
	{
		return (GetFlags() & SHIFT_FLAG) != 0;
	}
	UINT GetFlags() const 
	{
		ASSERT(!IsEmpty());
		return m_nFlags;
	}
	static bool IsAllowedKey(UINT nKeyCode)
	{
		return !GetKeyName(nKeyCode).IsEmpty();
	}
	CNavoVirtKey( LPARAM lParam )
	{
		m_bEmpty = ( 0 == lParam );
		m_nKey	= LOWORD( lParam );
		m_nFlags= HIWORD( lParam );
	}
	operator LPARAM() { return m_bEmpty ? MAKELPARAM( 0, 0 ) : MAKELPARAM( m_nKey, m_nFlags ); };
private:

	UINT m_nKey;
	UINT m_nFlags;
	bool m_bEmpty;
};

enum eDrawMode
{
	DRAWMODE_FOREGROUND,
	DRAWMODE_BACKGROUND,
	DRAWMODE_PRINT,
};

//----------------------------------
// luŸne funkcje pomocnicze
//----------------------------------


//zamienia region z jednostek logicznych na device
void TransferRgnLPtoDP(HDC hDC,const CRgn & oLP_Rgn,CRgn& oPixelRgn);


//zwraca handle cursora myszki na podstawie kodu MCID_ (patrz wy¿ej)
HCURSOR GetCursorHandleOnMCId(long nMCId);



inline CNavoVirtKey & CNavoVirtKey::operator=(const CNavoVirtKey & roSecond)
{
	m_nKey		= roSecond.m_nKey;
	m_nFlags	= roSecond.m_nFlags;
	m_bEmpty	= roSecond.m_bEmpty;
	return *this;
}


#else
	#error __FILE__ already included
#endif
