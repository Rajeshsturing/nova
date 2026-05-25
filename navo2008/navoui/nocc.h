/*
	
	NAVO Enterprise 2001

	Ole control container and site 

*/

#ifndef _NOCC_H_
#define _NOCC_H_


#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT
#ifdef _NAVODOTNET
#include <afxocc.h>
#else
#include <../MFC/SRC/occimpl.h>
#endif
#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT 

struct AFX_EVENT;

class CNavoOleEventSink
{
public:
	virtual void OnOleControlEvent(long IdCtrl,AFX_EVENT* pEvent) = 0;
};
//-----------------------------------------------------------
// NAVO OLE Control Site
//-----------------------------------------------------------
class CNavoOleControlSite : public COleControlSite
{
public:
	CNavoOleControlSite(COleControlContainer* pCtrlCont) :
	  COleControlSite(pCtrlCont)
	{
	}
	COleDispatchDriver * _dispdriver()
	{ 
		return &m_dispDriver;
	}
	DELEGATE_UNKNOWN_ON_CMDTARGET
};

//-----------------------------------------------------------
// NAVO OLE Control Container
//-----------------------------------------------------------

class CNavoOleControlContainter : public COleControlContainer
{
public:
	CNavoOleControlContainter(CWnd * pWnd) : 
	  COleControlContainer(pWnd)
  {
  }
};

//-----------------------------------------------------------
// NAVO OLE Control Container Manager
//-----------------------------------------------------------

class CNavoOccManager : public COccManager
{
public:
	CNavoOccManager(){}
	virtual ~ CNavoOccManager(){}
	virtual COleControlContainer* CreateContainer(CWnd* pWnd);
	virtual COleControlSite* CreateSite(COleControlContainer* pCtrlCont);
	virtual BOOL OnEvent(CCmdTarget* pCmdTarget, UINT idCtrl, AFX_EVENT* pEvent,
		AFX_CMDHANDLERINFO* pHandlerInfo);
};

CNavoOccManager & GetNavoOccManager();

#else
	#error __FILE__ already included
#endif
