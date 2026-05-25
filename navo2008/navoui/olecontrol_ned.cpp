/*
	NAVO Enterprise 2003
	2003-04-01

	navo enhanced display (NED)

	ned_olecontrol
		wrapper dla ActiveX
*/

#include "stdafx.h"
#include <afxpriv2.h>

#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT
#if defined(_NAVODOTNET) || defined(NAVO2008)
#include <afxocc.h>
#else
#include <../MFC/SRC/occimpl.h>
#endif
#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT 

#include "oleeventsink_ndoc.h"
#include "win32_ned.h"
#include "olecontrol_ned.h"
#include "web_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//--------------------------------------------------------------------------------
//helper classes for ole control
//--------------------------------------------------------------------------------

class cned_olecontrol_site : public COleControlSite
{
public:
	cned_olecontrol_site(COleControlContainer* pCtrlCont) :
		COleControlSite(pCtrlCont)
	{
	}
	COleDispatchDriver & _getdriver()
	{
		return m_dispDriver;
	}
};

//-----------------------------------------------------------
// NAVO OLE Control Container Manager
//-----------------------------------------------------------

class cnui_occmanager : public COccManager
{
public:
	cnui_occmanager(){}
	~cnui_occmanager(){}
	virtual BOOL OnEvent(CCmdTarget* pCmdTarget, UINT idCtrl, AFX_EVENT* pEvent,
		AFX_CMDHANDLERINFO* pHandlerInfo);
};

static cnui_occmanager _g_nui_occmanager;

COccManager * get_occmaganer()
{
	return & _g_nui_occmanager;
}

BOOL cnui_occmanager::OnEvent(CCmdTarget* pCmdTarget, UINT idCtrl, AFX_EVENT* pEvent,
		AFX_CMDHANDLERINFO* /*pHandlerInfo*/)
{
	ASSERT(pCmdTarget);
	cndoc_olecontrol_event_sink__ * poOleControlEventSink = dynamic_cast<cndoc_olecontrol_event_sink__ *>(pCmdTarget);
	ASSERT(poOleControlEventSink);
	poOleControlEventSink->on_olecontrol_event(idCtrl,pEvent);
	return TRUE;
}

//--------------------------------------------------------------------------------
// okno (Win320 pomocnicze
//--------------------------------------------------------------------------------
namespace ned
{

class cned_olecontrol_window : public CWnd
{
public:
	cned_olecontrol_window(ned_ident idOleControl,cned_element_manager * poElementManager) :
		m_idOleControl(idOleControl),
		m_poElementManager(poElementManager)
	{
		ASSERT(poElementManager);
		ASSERT(NEDID_NOTHING != m_idOleControl);
	}
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);

	cned_olecontrol_site * GetControlSite()
	{
		return reinterpret_cast<cned_olecontrol_site*>(m_pCtrlSite);
	}
private:
	ned_ident m_idOleControl;
	cned_element_manager * m_poElementManager;
};

}

BOOL cned_olecontrol_window::OnCmdMsg(UINT nID, int nCode, void* pExtra,AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (nCode == CN_EVENT)
	{
		ASSERT(m_poElementManager);
		/*
		
		  ned_to_do:

			if(!m_poElementManager->is_active())
			{
				return TRUE;
			}

		*/

		//tylko gdy jest aktywne
		SCP<cned_element> poElementSP = m_poElementManager->get_element_on_ident(m_idOleControl);
		cned_olecontrol * poOleControlWrapper = cast_ui<cned_olecontrol>(poElementSP.Get());
		ASSERT(poOleControlWrapper != NULL);
		if(!poOleControlWrapper->is_initialized())
		{
			return TRUE;
		}

		return FALSE;
	}

	return CWnd::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

//--------------------------------------------------------------------
// cned_olecontrol
//--------------------------------------------------------------------

cned_olecontrol::cned_olecontrol(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_win32__(poManager,eType,idThis),
	m_oCLSID(CLSID_NULL),
	m_poControlWindow(NULL)
{
}

cned_olecontrol::~cned_olecontrol()
{
	_reset_control();
}

void cned_olecontrol::_reset_control()
{
	m_poControlDispatchSP = 0;
	m_poEventTypeInfoSP = 0;

	if(m_poControlWindow != NULL)
	{
		m_poControlWindow->DestroyWindow();
		delete m_poControlWindow;
		m_poControlWindow = NULL;
	}
}

void cned_olecontrol::_init_control()
{
	if(m_poControlWindow != NULL)
	{
		//cause error in IE4 and above
		::ShowWindow(m_poControlWindow->m_hWnd,SW_SHOW);
		return;
	}
	
	if(IsEqualGUID(m_oCLSID,CLSID_NULL))
	{
		return;
	}
	RECT oWinRect = { 10000,10000,10010,10010 };
	
	m_poControlWindow = new cned_olecontrol_window(get_ident(),get_manager());

	if(!m_poControlWindow->CreateControl(get_prop_clsid(),"",WS_VISIBLE | WS_CHILD, oWinRect, 
		CWnd::FromHandle(get_manager()->get_os_window()),get_ident()))
	{
		delete m_poControlWindow;
		m_poControlWindow = NULL;
	}
}

HWND cned_olecontrol::get_embedded_hwnd() const
{
	if(m_poControlWindow != NULL)
	{
		return m_poControlWindow->m_hWnd;
	}
	return HWND(NULL);
}

//------ ------ integration support ----------- ------ ------ ------ 

SCP<IDispatch> cned_olecontrol::get_olecontrol_dispatch()
{
	if(m_poControlDispatchSP.PointsNull())
	{
		_init_control();
		if(m_poControlDispatchSP.PointsNull())
		{
			if(m_poControlWindow != NULL)
			{
				ASSERT(m_poControlWindow->GetControlSite());
				ASSERT(m_poControlWindow->GetControlSite()->m_pObject);
				
				//zdobywanie m_poControlDispatchSP
				if(m_poControlWindow->GetControlSite()->_getdriver().m_lpDispatch == NULL)
				{
					SCP<IDispatch> pIDispatchSP;
					pIDispatchSP.QueryInterface(m_poControlWindow->GetControlSite()->m_pObject);
					
					//to mi³y gest w stosunku do COleControlSite'a
					m_poControlWindow->GetControlSite()->_getdriver().AttachDispatch(pIDispatchSP.Get(),FALSE);
					m_poControlDispatchSP = pIDispatchSP;
				}
				else
				{
					m_poControlDispatchSP =  NewSCP<IDispatch>(m_poControlWindow->GetControlSite()->_getdriver().m_lpDispatch,true);
				}
				
				//zdobywanie control typeinfo
				if(m_poControlDispatchSP.PointsObject())
				{
					IID iidEvent;
					if(m_poControlWindow->GetControlSite()->GetEventIID(&iidEvent))
					{
						SCP<ITypeInfo> poTypeInfoSP;
						HRESULT hr = m_poControlDispatchSP->GetTypeInfo(0,0,&poTypeInfoSP.GetRawPointer());
						if(hr == S_OK)
						{
							ASSERT(poTypeInfoSP.PointsObject());
							SCP<ITypeLib> poTypeLibSP;
						
							hr = poTypeInfoSP->GetContainingTypeLib(&poTypeLibSP.GetRawPointer(),NULL);
							if(hr == S_OK)
							{
								ASSERT(poTypeLibSP.PointsObject());
								hr = poTypeLibSP->GetTypeInfoOfGuid(iidEvent,
									&m_poEventTypeInfoSP.GetRawPointer());
								
								if(hr == S_OK)
								{
									ASSERT(m_poEventTypeInfoSP.PointsObject());
								}
							}
						}
					}
				}
			}
		}
	}
	return m_poControlDispatchSP;
}

SCP<ITypeInfo> cned_olecontrol::get_olecontrol_event_typeinfo()
{
	SCP<IDispatch> poDispatchSP = get_olecontrol_dispatch();	//force initialization
	
	return m_poEventTypeInfoSP;	//return whatever it is
}

struct olecontrol_stock_event_name
{
	DISPID m_dispid;
	LPCTSTR m_pcName;
};

static olecontrol_stock_event_name _g_ole_ctrl_stock_events[] =
{
	{ DISPID_MOUSEMOVE, _T("MouseMove")		},
	{ DISPID_CLICK,		_T("Click")			},
	{ DISPID_KEYDOWN,	_T("KeyDown")		},
	{ DISPID_MOUSEDOWN, _T("MouseDown")		},
	{ 0, NULL },
};

bool cned_olecontrol::get_olecontrol_event_name(DISPID dispid,ng_string & roEventNameString)
{
	//first look for stock events
	ng_string oFunctionNameString;
	for(olecontrol_stock_event_name * pSE = _g_ole_ctrl_stock_events;pSE->m_pcName != NULL; pSE++)
	{
		if(pSE->m_dispid == dispid)
		{
			roEventNameString = pSE->m_pcName;
			return true;
		}
	}

	//then look for custom events
	SCP<ITypeInfo> poTypeInfoSP = get_olecontrol_event_typeinfo();
	if(poTypeInfoSP.PointsObject())
	{
		CBStr oFunctionNameBstr;
		unsigned int nNamesCount;
		HRESULT hr = poTypeInfoSP->GetNames(dispid,&oFunctionNameBstr.GetRawPointer(),1,&nNamesCount);
		if(hr == S_OK)
		{
			roEventNameString = oFunctionNameBstr;
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------

void cned_web::_init_control()
{
	cned_olecontrol::_init_control();
	if(is_initialized())
	{
		m_poBrowserAppSP.QueryInterface(m_poControlWindow->GetControlUnknown());
		__navigateto();
	}
}
