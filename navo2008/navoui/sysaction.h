/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	system "actions"
*/

#ifndef _SYSACTION_H_
#define _SYSACTION_H_

enum CUserCmdResult
{
	UCR_NOTPROCESSED,
	UCR_OK,
	UCR_CANCEL,
	UCR_ERROR
};

//----------------------------------------------
//		klasy zwi¹zane z akcjami
//		przechowuj¹ informacje o skutkach akcji
//		oraz ewentualnie niezbêdne do undo
//----------------------------------------------
class CDataUnit;
class CRepaintArea;
class CUIElement;

class CAction__
{
public:
	CAction__(CNGC & roDC) :
	  m_bProcessed(false),
	  m_nResultValid(nothing),
	  m_nFocusElementId(UIEID_NOELEMENT),
	  m_nLostFocusElementId(UIEID_NOELEMENT),
	  m_nChangedSizeElementId(UIEID_NOELEMENT),
	  m_poPerformingUIElement(NULL),
	  m_oRequiredVisibleRect(0,0,0,0),
	  m_roDC(roDC)
	{
	}	

	//--- wype³niane przez UIElement -------------------
	void SetProcessed()									//akcja obs³u¿ona
	{
		m_nResultValid |= processed;
	}
	void SetSizeChanged(long nChangedSizeElementId)		//rozmiar zmieni³ siê
	{
		m_nChangedSizeElementId = nChangedSizeElementId;
		m_nResultValid |= sizechg;
	}
	void SetMakeDataScan()
	{
		m_nResultValid |= makescan;
	}
	void SetCommand(SCP<CHyperLinkInfo> & roHLISP)		//komenda do wykonania
	{
		m_poExecuteHLISP = roHLISP;
		m_nResultValid |= command;
	}
	void SetFocus(long nFocusElementId)					//ustaw fokus na element nFocusElementId
	{
		m_nFocusElementId = nFocusElementId;
		m_nResultValid |= setfocus;
	}
	void LostFocus(long nLostFocusElementId)
	{
		m_nLostFocusElementId = nLostFocusElementId;
		m_nResultValid |= lostfocus;
	}
	void AddData(const CDataUnit & roDataUnit)			//przetwórz dane od kontrolki
	{
		//na razie tylko jedn¹ dan¹. jak chcesz rozszerzyæ to pamiêtaj
		//listê
		m_oDataUnit = roDataUnit;
		m_nResultValid |= newdata;
	}
	CRepaintArea & GetInvalidArea()						//obszar wymagaj¹cy invalidacji
	{
		return m_oRepaintArea;
	}
	void SetPerformingElementHelper(CUIElement * poUIElement)
	{
		m_poPerformingUIElement = poUIElement;
	}
	void SetRequiredVisibleRect(const _rect & roRect)
	{
		m_nResultValid |= reqvis;
		m_oRequiredVisibleRect = roRect;
	}
	//--- OUTPUT - informations
	bool IsProcessed() const
	{
		return (m_nResultValid & processed) != 0;
	}
	bool IsSizeChanged() const
	{
		return (m_nResultValid & sizechg) != 0;
	}
	bool IsCommand() const
	{
		return (m_nResultValid & command) != 0;
	}
	bool IsSetFocus() const
	{
		return (m_nResultValid & setfocus) != 0;
	}
	bool IsLostFocus() const
	{
		return (m_nResultValid & lostfocus) != 0;
	}
	bool IsNewData() const
	{
		return (m_nResultValid & newdata) != 0;
	}
	bool IsMakeDataScan() const
	{
		return (m_nResultValid & makescan) != 0;
	}
	bool IsRequiredVisibleRect() const
	{
		return (m_nResultValid & reqvis) != 0;
	}
	const _rect & GetRequiredVisibleRect() const
	{
		return m_oRequiredVisibleRect;
	}
	long GetFocusElementId() const
	{
		ASSERT(IsSetFocus());
		return m_nFocusElementId;
	}
	long GetLostFocusElementId() const
	{
		ASSERT(IsLostFocus());
		return m_nLostFocusElementId;
	}
	long GetChangedSizeElementId() const
	{
		return m_nChangedSizeElementId;
	}
	SCP<CHyperLinkInfo> & GetCommand()
	{
		ASSERT(IsCommand());
		return m_poExecuteHLISP;
	}
	CDataUnit & GetNewData()		//gdy wiele danych - inna funkcja
	{
		// ASSERT(IsNewData()); - dane z akcji s¹ zwracane w przypadku CActionData
		return m_oDataUnit;
	}
	CUIElement * GetPerformingElementHelper()
	{
		return m_poPerformingUIElement;
	}
	CNGC & GetNGC() const
	{
		return m_roDC;
	}
protected:
	
	////result area ////////////
	enum ResultValid
	{
		nothing	= 0x0000,
		command	= 0x0001,
		resized	= 0x0002,
		setfocus= 0x0004,
		newdata = 0x0008,
		sizechg = 0x0010,
		reqvis	= 0x0020,
		processed=0x0080,
		makescan= 0x0100,
		lostfocus=0x0200
	};
	
	long					m_nFocusElementId;
	long					m_nLostFocusElementId;

	long					m_nResultValid;
	long					m_nChangedSizeElementId;
	CRepaintArea			m_oRepaintArea;
	SCP<CHyperLinkInfo>		m_poExecuteHLISP;
	CDataUnit				m_oDataUnit;
	CUIElement *			m_poPerformingUIElement;//this is pure optimization
	bool					m_bProcessed;
	_rect					m_oRequiredVisibleRect;
	CNGC &					m_roDC;
};

class CActionKBD : public CAction__
{
public:
	CActionKBD(CArchive & roStateArchive,CNGC & roDC,UINT nChar,UINT nFlags,UINT nRepCnt);

	//dane o zdarzeniu podawane do kontrolki
	UINT KeyCode() const 
	{ 
		return m_nChar; 
	}
	UINT ScanCode()	const 
	{ 
		return m_nFlags & 0x00ff; 
	}
	LPARAM MsgLParam() const
	{
		return (LPARAM)(((DWORD)m_nFlags << 16) | (DWORD)m_nRepCnt);
	}
	void SetKeyCode(UINT nKeyCode) 
	{ 
		m_nChar = nKeyCode; 
	}
	bool	IsAlt() const		//Lewy Alt
	{
		return m_bIsAlt;
	}
	bool	IsCtrl() const		//dowolny Ctrl
	{
		return m_bIsCtrl;
	}
	bool	IsShift() const		//dowolny Shift
	{
		return m_bIsShift;
	}
	bool	IsNormal() const	//¿aden z Ctrl,Alt,Shift nie jest wciœniêty
	{
		return !IsAlt() && !IsCtrl() && !IsShift();
	}
	CArchive & Archive()
	{
		return m_roStateArchive;
	}
	//rozpoznaje przynale¿noœæ znaku do grupy
	//zwraca znak na podstawie LOCALE_ u¿ytkownika
	UINT RecognizeCharGroup(UINT nExpectedType,UINT nUnwantedType) const;		
protected:
	UINT	m_nChar;
	UINT	m_nFlags;
	UINT	m_nRepCnt;
	bool	m_bIsCtrl;
	bool	m_bIsAlt;
	bool	m_bIsShift;
	CArchive & m_roStateArchive;
};

#define MK_DBLCLK        0x0040		//dblclick

class CCommandList;
class CActionMouse : public CAction__
{
public:
	CActionMouse(CNGC & roDC,UINT nFlags,CPoint point,CCommandList * poCommandList) : 
		CAction__(roDC),
		m_poCommandList(poCommandList)
	{
		m_nFlags = nFlags;
		m_oPoint = point;
	}

	//dane o zdarzeniu podawane do kontrolki
	const CPoint & Point() const 
	{ 
		return m_oPoint; 
	}
	UINT Flags() const 
	{ 
		return m_nFlags; 
	}
	bool IsLClick() const
	{
		return (m_nFlags & MK_LBUTTON) != 0;
	}
	bool IsRClick() const
	{
		return (m_nFlags & MK_RBUTTON) != 0;
	}
	bool IsDblClick() const
	{
		return (m_nFlags & MK_DBLCLK) != 0;
	}
	CCommandList * GetCommandList() const
	{
		return m_poCommandList;
	}
private:
	CCommandList * m_poCommandList;
	CPoint	m_oPoint;
	UINT	m_nFlags;
};

class CActionData : public CAction__
{
public:
	CActionData(CNGC & roDC,const CDataUnit & roDataUnit) : 
		CAction__(roDC),
		m_nFocusElement(UIEID_NOELEMENT)
	{
		AddData(roDataUnit);
	}
	void SetNewDataConsumed()
	{
		m_nResultValid &= ~newdata;
	}
	void SetFocusElement(long nFocusElement)
	{
		m_nFocusElement = nFocusElement;
	}
	long GetFocusElement() const
	{
		return m_nFocusElement;
	}
private:
	long	m_nFocusElement;
};

const long PAINT_LEVEL_BACKGROUND	=	-1;		//malowanie t³a kontrolki
const long PAINT_LEVEL_FOREGROUND	=	+1;		//malowanie pierwszego planu kontrolki

class CActionPaint : public CAction__
{
public:
	CActionPaint(CNGC & roPaintDC,long nFocusElement,long nMouseOverElement,HWND hViewWindow,
		bool bForceLayout,long nLevel):
		CAction__(roPaintDC),
		m_nFocusElement(nFocusElement),
		m_nMouseOverElement(nMouseOverElement),
		m_hViewWindow(hViewWindow),
		m_eDrawMode(DRAWMODE_FOREGROUND),
		m_hPrinterDevMode(NULL),
		m_bForceLayout(bForceLayout),
		m_nLevel(nLevel)
	{
	}
	long GetLevel() const
	{
		return m_nLevel;
	}
	void SetLevel(long nLevel)
	{
		m_nLevel = nLevel;
	}
	long GetFocusElement() const
	{
		return m_nFocusElement;
	}
	long GetMouseOverElement() const
	{
		return m_nMouseOverElement;
	}
	HWND GetWindow() const
	{
		return m_hViewWindow;
	}
	bool IsForegroundPaint() const
	{
		return m_eDrawMode != DRAWMODE_BACKGROUND;
	}
	bool IsScrollToUpdate() const
	{
		return m_bUpdateScroll;
	}
	eDrawMode GetDrawMode() const
	{
		return m_eDrawMode;
	}
	void SetDrawMode(eDrawMode eDM)
	{
		m_eDrawMode = eDM;
	}
	void SetPaintRect(const _rect & roRect)
	{
		m_oPaintRect = roRect;
	}
	const _rect & GetPaintRect() const
	{
		return m_oPaintRect;
	}
	HANDLE & PrinterDevMode()
	{
		return m_hPrinterDevMode;
	}
	bool IsForceMode() const
	{
		return m_bForceLayout;
	}
	void RemoveFromClipRgn(CRepaintArea & roRepaintArea);
private:
	long		m_nLevel;				//warstwa do malowania. 
	HWND		m_hViewWindow;
	long		m_nFocusElement;
	long		m_nMouseOverElement;
	bool		m_bUpdateScroll;
	eDrawMode	m_eDrawMode;
	_rect		m_oPaintRect;
	HANDLE		m_hPrinterDevMode;
	bool		m_bForceLayout;
};

class CActionMoveFocus : public CAction__
{
public:
	CActionMoveFocus(CNGC & roDC,long IdElementFrom,long IdElementTo) :
		CAction__(roDC),
		m_IdElementFrom(IdElementFrom),
		m_IdElementTo(IdElementTo)
	{
	}
	long GetElementFrom() const
	{
		return m_IdElementFrom;
	}
	long GetElementTo() const
	{
		return m_IdElementTo;
	}
	void SetResolvedElementTo(long IdElemTo)		//podmienia element to na konkretny
	{
		ASSERT(IdElemTo > 0);
		m_IdElementTo = IdElemTo;
	}
private:
	long m_IdElementFrom;
	long m_IdElementTo;
};

class CActionTimeElapsed : public CAction__
{
public:
	CActionTimeElapsed(CNGC & roDC) :
		CAction__(roDC)
	{}
};

class CActionOleEvent : public CAction__
{
public:
	CActionOleEvent(CNGC & roDC,long IdControl,AFX_EVENT * pEvent) :
		CAction__(roDC),
		m_IdControl(IdControl),
		m_pEvent(pEvent)
	{
	}
	long GetIdControl() const
	{
		return m_IdControl;
	}
	AFX_EVENT * GetEventInfo() const
	{
		return m_pEvent;
	}
private:
	long		m_IdControl;
	AFX_EVENT *	m_pEvent;
};

class CActionInit : public CAction__
{
public:
	CActionInit(CNGC & roDC,HWND hParentWnd) :
		CAction__(roDC),
		m_hParentHwnd(hParentWnd)
	{
	}
	HWND GetParentHWND() const
	{
		return m_hParentHwnd;
	}
private:
	HWND		m_hParentHwnd;
};

class CActionCommand : public CAction__
{
public:
	CActionCommand(CNGC & roDC,SCP<CHyperLinkInfoWithResult> poCmdHLISP) :
		CAction__(roDC),
		m_poCommandHyperLinkInfoSP(poCmdHLISP)
	{
	}

	SCP<CHyperLinkInfoWithResult> & GetCommandHLI()
	{
		return m_poCommandHyperLinkInfoSP;
	}
private:
	SCP<CHyperLinkInfoWithResult> m_poCommandHyperLinkInfoSP;
};
//-------------------------------------------------
// informacje o layoucie
//
// s³u¿¹ elementowi do wykonania GetLayoutInfo
// wyniki s¹ zapisywane w CUIElement::m_nMinimalWidth oraz CUIElement::m_nMetric
//-------------------------------------------------

class CLayoutInfo
{
public:
	CLayoutInfo(CNGC & roDC,eDrawMode eDrawMode) :
		m_roDC(roDC),
		m_eDrawMode(eDrawMode)
	{
	}
	CLayoutInfo(const CLayoutInfo & roLayoutInfo) :
		m_roDC(roLayoutInfo.m_roDC),
		m_eDrawMode(roLayoutInfo.m_eDrawMode)
	{
	}
	//callee
	CNGC & GetNGC()
	{
		return m_roDC;
	}
	eDrawMode GetDrawMode() const
	{
		return m_eDrawMode;
	}
private:
	CNGC	&	m_roDC;
	eDrawMode m_eDrawMode;
};

//-------------------------------------------------
// parametry do zrobienia layoutu
//-------------------------------------------------
class CLayoutParam
{
public:
	//caller:
	CLayoutParam(CNGC & roDC,const _rect & roArenaRect,long nRequiredYCoord,
			bool bContinue,eDrawMode eDrawMode) :
		m_roDC(roDC),
		m_oRUSize(-1,-1),
		m_oArenaRect(roArenaRect),
		m_nRequiredYCoordinate(nRequiredYCoord),
		m_bContinue(bContinue),
		m_eDrawMode(eDrawMode)
	{
	}
	//"almost" copy constructor
	CLayoutParam(const CLayoutParam & roLayoutParam,const _rect & roArenaRect) :
		m_roDC(roLayoutParam.m_roDC),
		m_oRUSize(roLayoutParam.m_oRUSize),
		m_oArenaRect(roArenaRect),
		m_nRequiredYCoordinate(roLayoutParam.m_nRequiredYCoordinate),
		m_bContinue(roLayoutParam.m_bContinue),
		m_eDrawMode(roLayoutParam.m_eDrawMode)
	{
	}

	//parameters for callee
	CRepaintArea & GetRepaintArea()
	{
		return m_oRepaintArea;
	}
	CNGC & GetNGC() const
	{
		return m_roDC;
	}
	const _rect & GetArena() const
	{
		return m_oArenaRect;
	}
	long GetRequiredY() const
	{
		return m_nRequiredYCoordinate;
	}
	
	eDrawMode GetDrawMode() const
	{
		return m_eDrawMode;
	}
	bool IsContinue() const
	{
		return m_bContinue;
	}

	//result - setting methods
	//set required or used space
	void SetRUSpace(const CSize & roSize)
	{
		m_oRUSize = roSize;
	}
	//results for caller
	bool IsTooWide() const
	{
		return m_oRUSize.cx > m_oArenaRect.Width();
	}
	bool IsToHigh() const
	{
		return m_oRUSize.cy > m_oArenaRect.Height();
	}
	const CSize & GetRUSpace() const
	{
		return m_oRUSize;
	}
private:
	_rect			m_oArenaRect;				//obszar w którym uk³adamy
	CNGC	&		m_roDC;
	long			m_nRequiredYCoordinate;		//zrób layout conajmniej do tego miejsca
	bool			m_bContinue;				//kontynuacja layoutu
	
	CRepaintArea	m_oRepaintArea;				//obszar do odmalowania w wyniku layoutu
	CSize			m_oRUSize;					//obszar u¿yty/niezbêdny
	eDrawMode		m_eDrawMode;
};

enum eLayoutResult
{
	ltr_none		= 0x00,				//cannot layout even part
	ltr_part		= 0x01,				//part layed out, more parts will be
	ltr_complete	= 0x02,				//task completed
	ltr_semicomplete= 0x03,				//task completed for now (not-necessary part exists)
};


#else
	#error __FILE__ already included
#endif
