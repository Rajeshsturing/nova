/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	26.01.2003

	class:
		cndoc_navoview_stock_container
		
		container for cndoc_navoview_impl
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\element_nedaw.h"
#include "..\navoobj\dataobject.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "navoview_impl_cont_ndoc.h"

using namespace ned;

#include "event_handler_ndoc.h"
#include "stockcontainer_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cndoc_navoview_stock_container::cndoc_navoview_stock_container(CNavoException & roErrorStorage):
	m_roErrorStorage(roErrorStorage)
{
	EnableAutomation();
	m_poEventManagerSP = NewSCP(new cndoc_event_manager());
}

cndoc_navoview_stock_container::~cndoc_navoview_stock_container()
{
	m_poEventManagerSP = 0;
}

SCP<cned_window> cndoc_navoview_stock_container::_get_window()
{
	return m_poWindowSP;
}

void cndoc_navoview_stock_container::set_window(SCP<cned_window> poWindowSP)
{
	if(poWindowSP.Get() != m_poWindowSP.Get())
	{
		m_poWindowSP = poWindowSP;
		if(m_poWindowSP.PointsObject())
		{
			m_poWindowSP->AddNamedItem(NewSCP(new CNamedItemInfo(_T("page_"),
				&_get_page_disp_fwdr(),NULL)));
		}
	}
}

bool cndoc_navoview_stock_container::on_action_results(ned::ned_action_result & roActionResults)
{
	ASSERT(_get_window().PointsObject());

	CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
			NewSCP((IDispatch*)&m_xDynaDispatch,true));

	long Index = 0;
	while(roActionResults.get_info(Index).PointsObject())
	{
		if(roActionResults.get_info(Index)->get_type() >= eit_min_handler && roActionResults.get_info(Index)->get_type() < eit_max_handler)
		{
			const ned_ident FiringIdent = roActionResults.get_info(Index)->get_firing_element();
			SCP<nui_transfer> poTransferSP = _get_window()->get_transfer(FiringIdent);
			if(poTransferSP.PointsObject())
			{
				cndoc_event_param oEventParam;
				oEventParam.m_poEventInfo = roActionResults.get_info(Index);
				oEventParam.m_poTransfer = poTransferSP;
				oEventParam.m_poWindow = _get_window().Get();
				
				eTransferResult eTR = m_poEventManagerSP->invoke(oEventParam);
				if(eTR == tr_failed)
				{
					//to_do: odkrêcamy akcjê....
					ASSERT(false);
				}
				else
				{
					if(eTR == tr_ok)
					{
					}
				}
			}
		}
		else
		{
			switch(roActionResults.get_info(Index)->get_type())
			{
			case eit_command_list:
			{
				ned_event_command_list * poEventCmdList = dynamic_cast<ned_event_command_list*>(roActionResults.get_info(Index).Get());
				m_poEventManagerSP->build_custom_cmd_list(poEventCmdList,_get_window());
			}
			break;
			case eit_command:
			{
				ned_event_command * poEventCommand = dynamic_cast<ned_event_command *>(roActionResults.get_info(Index).Get());

				ASSERT(poEventCommand != NULL);
				ASSERT(poEventCommand->get_command().PointsObject());
				//invoke functions
				{
					CString oFunctionNameString;
					if(poEventCommand->get_command()->SafeGetStrProp(GVAR_FUNCTION,oFunctionNameString))
					{
					_get_window()->fire_user_command(oFunctionNameString,NULL,0,true);
					}
					if(poEventCommand->get_command()->SafeGetStrProp(GVAR_FUNCTIONHLI,oFunctionNameString))
					{
						CSmartOleVariant oSOV(poEventCommand->get_command()->GetDispatchSP());
						_get_window()->fire_user_command(oFunctionNameString,&oSOV,1,true);
					}
				}
			}
			break;
			}
		}
		
		Index++;
	}
	return true;
}

//-----------------------------------------------------------------------------
//{{AFX_MSG_MAP(cndoc_navopage)
//}}AFX_MSG_MAP


BEGIN_DISPATCH_MAP(cndoc_navoview_stock_container, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(cndoc_navoview_stock_container)
	DISP_FUNCTION_ID(cndoc_navoview_stock_container, "ctrl", 103, GetUIElementAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION_ID(cndoc_navoview_stock_container, "topelement", 105, GetUIPageManagerAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_navoview_stock_container, "trygetctrl", 106, SafeGetUIElementAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION_ID(cndoc_navoview_stock_container, "updateview", 107,UpdateViewAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_navoview_stock_container, "addxml", 114, AddXMLAUTO, VT_EMPTY, VTS_I4 VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPDISPATCH cndoc_navoview_stock_container::GetUIPageManagerAUTO()
{
	ALL_TRY
	{
		ASSERT(_get_window().PointsObject());
		SCP<cned_element> poTopPageSP = _get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE);
		if(poTopPageSP.PointsObject())
		{
			return poTopPageSP->get_my_nedaw()->GetIDispatch(TRUE);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_navoview_stock_container::GetUIElementAUTO(long Ident) 
{
	ALL_TRY
	{
		LPDISPATCH lpDispatch = SafeGetUIElementAUTO(Ident);
		if(lpDispatch != NULL)
		{
			return lpDispatch;
		}

		//to_do: error: no such element
		CString oString;
		oString.Format("no such element [%d]",Ident);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_navoview_stock_container::SafeGetUIElementAUTO(long Ident)
{
	ALL_TRY
	{
		ASSERT(_get_window().PointsObject());
		SCP<cned_element> poElementSP = _get_window()->get_element_on_ident(ned_ident(Ident));
		if(poElementSP.PointsObject())
		{
			return poElementSP->get_my_nedaw()->GetIDispatch(TRUE);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navoview_stock_container::UpdateViewAUTO() 
{
	ALL_TRY
	{
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


class CDefinitionManager;

void read_part_xml(SCP<IStream> poStreamSP,SCP<cned_window> pWindowSP,
			  SCP<CDefinitionManager> poDefinitionManagerSP,SCP<cned_container> poContainerSP);

void cndoc_navoview_stock_container::AddXMLAUTO(long idContainer,const VARIANT FAR & rvarXML)
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(rvarXML);
		SCP<IStream> poXMLStreamSP;
		
		if(oSOV.Type() == VT_BSTR)
		{
			//copy variant to stream
			poXMLStreamSP = CreateStreamInMemory();
			CStreamHolder oSH(poXMLStreamSP);
			CString oString(oSOV.GetBStr());
			oSH.WriteString(oString);
			oSH.SeekToBegin();
		}
		else
		{
			poXMLStreamSP = OpenFileStream_Read_On_SOV(oSOV);
		}
		ASSERT(poXMLStreamSP.PointsObject());
		ASSERT(_get_window().PointsObject());
		
		SCP<cned_element> poElementSP = _get_window()->get_element_on_ident(ned_ident(idContainer));
		ASSERT(poElementSP.PointsObject());
		SCP<cned_container> poContainerSP = scp_cast_ui<cned_container>(poElementSP.Get());
		ASSERT(poContainerSP.PointsObject());

		read_part_xml(poXMLStreamSP,_get_window(),SCP<CDefinitionManager>(),poContainerSP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
//-----------------------------------------------------------------------------

BEGIN_INTERFACE_MAP(cndoc_navoview_stock_container, CCmdTargetInterface)
	INTERFACE_PART(cndoc_navoview_stock_container, IID_IDispatch, DynaDispatch)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(cndoc_navoview_stock_container, DynaDispatch)  

STDMETHODIMP cndoc_navoview_stock_container::XDynaDispatch::GetTypeInfoCount(UINT* pCount)
{
	METHOD_PROLOGUE(cndoc_navoview_stock_container, DynaDispatch)

	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfoCount(pCount);
	}
	TOP_ALL_CATCH(pThis->_error_storage(),DISP_E_EXCEPTION);
}

STDMETHODIMP cndoc_navoview_stock_container::XDynaDispatch::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo ** ppTInfo)
{
	METHOD_PROLOGUE(cndoc_navoview_stock_container, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfo(iTInfo,lcid,ppTInfo);
	}
	TOP_ALL_CATCH(pThis->_error_storage(),DISP_E_EXCEPTION);
}

const long FIRST_SCRIPT_DISPID = 1000;

STDMETHODIMP cndoc_navoview_stock_container::XDynaDispatch::
	GetIDsOfNames(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId)
{
	METHOD_PROLOGUE(cndoc_navoview_stock_container, DynaDispatch)

	ALL_TRY
	{
		HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);
		if(hr == DISP_E_UNKNOWNNAME)
		{
			hr = pThis->_get_window()->Window_GetIDsOfNames(rgszNames,cNames,rgDispId);
			if(hr == S_OK)
			{
				*rgDispId += FIRST_SCRIPT_DISPID;
			}
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->_error_storage(),DISP_E_EXCEPTION);
}

STDMETHODIMP cndoc_navoview_stock_container::XDynaDispatch::
	Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError)
{
	METHOD_PROLOGUE(cndoc_navoview_stock_container, DynaDispatch)
	
	ALL_TRY
	{
		if(dispId == DISPID_VALUE)
		{
			return DISP_E_MEMBERNOTFOUND;
		}
		if(dispId < FIRST_SCRIPT_DISPID)
		{
			HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->
					Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
			ASSERT(hr != DISP_E_MEMBERNOTFOUND);
			return hr;
		}
		else
		{
			CInvokeForwarderHolder oPage_InvokeForwarderHolder(pThis->_get_page_disp_fwdr(),
				NewSCP((IDispatch*)&pThis->m_xDynaDispatch,true));
			
			return pThis->_get_window()->Window_Invoke(dispId-FIRST_SCRIPT_DISPID,riid,lCid,
				wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
		}
	}
	TOP_ALL_CATCH_AUTOMATION(pThis->_error_storage(),pExceptInfo);
}

