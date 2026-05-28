/*
	NAVO Sp. z o.o. (2002)
		
	NAVO Enterprise

	class:
		cndoc_navopage - strona typu NAVO

	05.08.2002
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navothread.h"		//navo thread
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\CacheManagerUser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\cursorcollection.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"

#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\element_nedaw.h"

using namespace ned;

#include "common_pageman.h"

#include "navopage_ndoc.h"
#include "xmlpagecachemu.h"
#include "event_handler_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void _cocoon_navopage_auto_diag(const CString& roMessage)
{
	try
	{
		CFile oFile;
		if (!oFile.Open(_T("C:\\app\\navo-native-diagnostics.log"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			return;
		}

		oFile.SeekToEnd();
		CString oLine;
		CTime oNow = CTime::GetCurrentTime();
		oLine.Format(_T("%s [navopage_auto] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

static CString _cocoon_navopage_auto_format_params(DISPPARAMS* pDispParams)
{
	if (pDispParams == NULL)
	{
		return _T("args=null");
	}

	CString oText;
	oText.Format(_T("argc=%u"), pDispParams->cArgs);
	for (UINT iter = 0; iter < pDispParams->cArgs && pDispParams->rgvarg != NULL; iter++)
	{
		CString oArg;
		oArg.Format(_T(" arg%u_vt=0x%04x"), iter, pDispParams->rgvarg[iter].vt);
		oText += oArg;
	}
	return oText;
}

//-----------------------------------------------------------------------------
//{{AFX_MSG_MAP(cndoc_navopage)
//}}AFX_MSG_MAP

#ifdef DISP_FUNCTION
#undef DISP_FUNCTION
#define DISP_FUNCTION(a1,a2,a3,a4,a5)	"Nie wolno u¿ywaæ w tej klasie"
#endif

#ifdef DISP_PROPERTY_EX
#undef DISP_PROPERTY_EX
#define DISP_PROPERTY_EX(a1,a2,a3,a4,a5)	"Nie wolno u¿ywaæ w tej klasie"
#endif


BEGIN_DISPATCH_MAP(cndoc_navopage, cndoc_page__)
	//{{AFX_DISPATCH_MAP(cndoc_navopage)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "cursoriter",100, GetCursorIteratorAUTO, SetCursorIteratorAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "root", 101,GetRootAUTO, SetRootAUTO, VT_DISPATCH)
	DISP_PROPERTY_PARAM_ID(cndoc_navopage, "cmdenabled", 102, GetCmdEnabledAUTO, SetCmdEnabledAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(cndoc_navopage, "ctrl", 103, GetUIElementAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION_ID(cndoc_navopage, "roottypeid", 104, GetPageRootTypeIdAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_navopage, "topelement", 105, GetUIPageManagerAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_navopage, "trygetctrl", 106, SafeGetUIElementAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION_ID(cndoc_navopage, "updateview", 107,UpdateViewAUTO, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "enableedit", 108, GetEnableEditAUTO, SetEnableEditAUTO, VT_BOOL)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "secidread", 109, GetSecurityId_Read_AUTO, SetSecurityId_Read_AUTO, VT_I4)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "secidins",  110, GetSecurityId_Insert_AUTO, SetSecurityId_Insert_AUTO, VT_I4)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "secidupd",  111, GetSecurityId_Update_AUTO, SetSecurityId_Update_AUTO, VT_I4)
	DISP_PROPERTY_EX_ID(cndoc_navopage, "seciddel",  112, GetSecurityId_Delete_AUTO, SetSecurityId_Delete_AUTO, VT_I4)
	DISP_FUNCTION_ID(cndoc_navopage, "rootidobj", 113, GetPageRootIdObjAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_navopage, "addxml", 114, AddXMLAUTO, VT_EMPTY, VTS_I4 VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPDISPATCH cndoc_navopage::GetRootAUTO() 
{
	ALL_TRY
	{
		if(m_poRootStdObjSP.PointsObject())
		{
			return m_poRootStdObjSP->GetDispatch(true);
		}
		return NULL;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetRootAUTO(LPDISPATCH lpDispatch) 
{
	ALL_TRY
	{
		SCP<CNEO_user> poStdObjSP = CNEO_user::FromIDispatch(lpDispatch);
		if(poStdObjSP != m_poRootStdObjSP)
		{
			if(poStdObjSP.PointsObject())
			{
#ifdef _DEVELOPER_EDITION_
				if(poStdObjSP->_get_trans().Get() != m_poTransactionSP.Get())
				{
					CString oString;
					oString.Format(
						"próbujesz podstawiæ pod root_ obiekt z innej transakcji (# %d). w³aœciwa (# %d)",
						poStdObjSP->_get_trans()->_debug_trans_nr,
						m_poTransactionSP->_debug_trans_nr);
					ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
				}
#endif
			}
			m_poRootStdObjSP = poStdObjSP;
			if(poStdObjSP.PointsObject())
			{
				SetEnableEditAUTO(m_poRootStdObjSP->_get_storage()->IsNew());
				m_nRootStdObj_IdObj = m_poRootStdObjSP->_get_storage()->GetThis();
			}
			else
			{
				m_nRootStdObj_IdObj = 0;
			}
			m_bNeedFullDataScan = true;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_navopage::GetUIPageManagerAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poWindowSP.PointsObject());
		SCP<cned_element> poTopPageSP = m_poWindowSP->get_element_on_ident(NEDID_TOPLEVELPAGE);
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

LPDISPATCH cndoc_navopage::GetCursorIteratorAUTO() 
{
	ALL_TRY
	{
		if(m_poCursorsCollectionIteratorSP.PointsNull())
		{
			return NULL;
		}
		else
		{
			return m_poCursorsCollectionIteratorSP->GetDispatch(true);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetCursorIteratorAUTO(LPDISPATCH lpCursorCollectionIterDispatch) 
{
	ALL_TRY
	{
		if(lpCursorCollectionIterDispatch == NULL)
		{
			m_poCursorsCollectionIteratorSP = 0;
		}
		else
		{
			SCP<CNEO_cursorIterator> poCCISP = CNEO_cursorIterator::FromIDispatch(lpCursorCollectionIterDispatch);
			ASSERT(poCCISP.PointsObject());
#ifdef _DEVELOPER_EDITION_
			if(poCCISP->debug_get_transaction_ptr() != m_poTransactionSP.Get())
			{
				CString oString;
				oString.Format(	
				"próbujesz podstawiæ pod page_.cursoriter kursor z innej transakcji (# %d). w³aœciwa (# %d)",
					poCCISP->debug_get_transaction_ptr()->_debug_trans_nr,
					m_poTransactionSP->_debug_trans_nr);
					ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
			}
#endif			
			m_poCursorsCollectionIteratorSP = poCCISP;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cndoc_navopage::GetUIElementAUTO(long Ident) 
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

LPDISPATCH cndoc_navopage::SafeGetUIElementAUTO(long Ident)
{
	ALL_TRY
	{
		SCP<cned_element> poElementSP = m_poWindowSP->get_element_on_ident(ned_ident(Ident));
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

long cndoc_navopage::GetPageRootTypeIdAUTO()
{
	ALL_TRY
	{
		long IdCommand = m_poOpeningHLISP->GetNumProp(GVAR_CMD);
		if(IdCommand == CMD_OPEN_RECORD_PAGE)
		{
			return m_poWindowSP->get_prop_root_typeid();
		}
		else
		{
			return 0;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cndoc_navopage::GetPageRootIdObjAUTO()
{
	ALL_TRY
	{
		return m_nRootStdObj_IdObj;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cndoc_navopage::GetSecurityId_Read_AUTO()
{
	ALL_TRY
	{
		return m_poWindowSP->get_prop_secid_read();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cndoc_navopage::GetSecurityId_Insert_AUTO()
{
	ALL_TRY
	{
		return m_poWindowSP->get_prop_secid_insert();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cndoc_navopage::GetSecurityId_Update_AUTO()
{
	ALL_TRY
	{
		return m_poWindowSP->get_prop_secid_update();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cndoc_navopage::GetSecurityId_Delete_AUTO()
{
	ALL_TRY
	{
		return m_poWindowSP->get_prop_secid_delete();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

void cndoc_navopage::SetSecurityId_Read_AUTO(long idsecRead)
{
	ALL_TRY
	{
		m_poWindowSP->set_prop_secid_read(idsecRead);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetSecurityId_Insert_AUTO(long idsecInsert)
{
	ALL_TRY
	{
		m_poWindowSP->set_prop_secid_insert(idsecInsert);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetSecurityId_Update_AUTO(long idsecUpdate)
{
	ALL_TRY
	{
		m_poWindowSP->set_prop_secid_update(idsecUpdate);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetSecurityId_Delete_AUTO(long idsecDelete)
{
	ALL_TRY
	{
		m_poWindowSP->set_prop_secid_delete(idsecDelete);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

void cndoc_navopage::UpdateViewAUTO() 
{
	ALL_TRY
	{
		cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(),get_transaction());
		get_integrator()->update_ui_now();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cndoc_navopage::GetCmdEnabledAUTO(long nCmd) 
{
	ALL_TRY
	{
		return is_command_enabled(nCmd) != false;	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetCmdEnabledAUTO(long nCmd, BOOL bNewValue) 
{
	ALL_TRY
	{
		m_poWindowSP->set_prop_button_visible(nCmd,bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL cndoc_navopage::GetEnableEditAUTO() 
{
	ALL_TRY
	{
		ASSERT(m_poWindowSP.PointsObject());
		return (m_poWindowSP->is_sys_disable() == false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_navopage::SetEnableEditAUTO(BOOL bNewValue) 
{
	ALL_TRY
	{
		ASSERT(m_poWindowSP.PointsObject());
		if(GetEnableEditAUTO() != bNewValue)
		{
			m_poWindowSP->set_sys_disable(bNewValue == FALSE);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void read_part_xml(SCP<IStream> poStreamSP,SCP<cned_window> pWindowSP,
			  SCP<CDefinitionManager> poDefinitionManagerSP,SCP<cned_container> poContainerSP);

void cndoc_navopage::AddXMLAUTO(long idContainer,const VARIANT FAR & rvarXML)
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
		
		SCP<cned_element> poElementSP = m_poWindowSP->get_element_on_ident(ned_ident(idContainer));
		ASSERT(poElementSP.PointsObject());
		SCP<cned_container> poContainerSP = scp_cast_ui<cned_container>(poElementSP.Get());
		ASSERT(poContainerSP.PointsObject());

		read_part_xml(poXMLStreamSP,m_poWindowSP,get_integrator()->get_definition_manager(),
			poContainerSP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
//-----------------------------------------------------------------------------

BEGIN_INTERFACE_MAP(cndoc_navopage, CCmdTargetInterface)
	INTERFACE_PART(cndoc_navopage, IID_IDispatch, DynaDispatch)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(cndoc_navopage, DynaDispatch)  

STDMETHODIMP cndoc_navopage::XDynaDispatch::GetTypeInfoCount(UINT* pCount)
{
	METHOD_PROLOGUE(cndoc_navopage, DynaDispatch)

	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfoCount(pCount);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP cndoc_navopage::XDynaDispatch::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo ** ppTInfo)
{
	METHOD_PROLOGUE(cndoc_navopage, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfo(iTInfo,lcid,ppTInfo);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

const long PAGE_DISPID_OFFSET = 300;

STDMETHODIMP cndoc_navopage::XDynaDispatch::
	GetIDsOfNames(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId)
{
	METHOD_PROLOGUE(cndoc_navopage, DynaDispatch)

	ALL_TRY
	{
		CString oName;
		if (rgszNames != NULL && cNames > 0 && rgszNames[0] != NULL)
		{
			oName = rgszNames[0];
		}

		HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);
		CString oPath(_T("native"));
		if(hr == DISP_E_UNKNOWNNAME)
		{
			oPath = _T("window");
			hr = pThis->m_poWindowSP->Window_GetIDsOfNames(rgszNames,cNames,rgDispId);
			if(hr == S_OK)
			{
				*rgDispId += PAGE_DISPID_OFFSET;
			}
		}
		else
		{
			ASSERT(*rgDispId < PAGE_DISPID_OFFSET);
		}

		CString oDiag;
		oDiag.Format(_T("GetIDsOfNames name=%s path=%s hr=0x%08lx dispid=%ld cNames=%u window_null=%d"),
			(LPCTSTR)oName, (LPCTSTR)oPath, hr,
			(rgDispId != NULL && cNames > 0) ? *rgDispId : -1, cNames,
			pThis->m_poWindowSP.PointsNull() ? 1 : 0);
		_cocoon_navopage_auto_diag(oDiag);
		return hr;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP cndoc_navopage::XDynaDispatch::
	Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError)
{
	METHOD_PROLOGUE(cndoc_navopage, DynaDispatch)
	
	ALL_TRY
	{
		if(dispId == DISPID_VALUE)
		{
			_cocoon_navopage_auto_diag(_T("Invoke DISPID_VALUE member not found"));
			return DISP_E_MEMBERNOTFOUND;
		}
		if(dispId < PAGE_DISPID_OFFSET)
		{
			CString oBeginDiag;
			oBeginDiag.Format(_T("Invoke native begin dispid=%ld wFlags=0x%04x %s"),
				dispId, wFlags, (LPCTSTR)_cocoon_navopage_auto_format_params(pDispParams));
			_cocoon_navopage_auto_diag(oBeginDiag);

			HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->
					Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
			CString oDiag;
			oDiag.Format(_T("Invoke native end dispid=%ld hr=0x%08lx result_vt=0x%04x"),
				dispId, hr, (pVarResult != NULL) ? pVarResult->vt : VT_EMPTY);
			_cocoon_navopage_auto_diag(oDiag);
			ASSERT(hr != DISP_E_MEMBERNOTFOUND);
			return hr;
		}
		else
		{
			CInvokeForwarderHolder oPage_InvokeForwarderHolder(pThis->_get_page_disp_fwdr(),
				NewSCP((IDispatch*)&pThis->m_xDynaDispatch,true));
			
			cndoc_transaction_switch_holder oSwitchToMeHolder(pThis->get_integrator()->get_current_transaction(),pThis->get_transaction());

			CString oBeginDiag;
			oBeginDiag.Format(_T("Invoke window begin dispid=%ld script_dispid=%ld wFlags=0x%04x %s"),
				dispId, dispId-PAGE_DISPID_OFFSET, wFlags,
				(LPCTSTR)_cocoon_navopage_auto_format_params(pDispParams));
			_cocoon_navopage_auto_diag(oBeginDiag);

			HRESULT hr = pThis->m_poWindowSP->Window_Invoke(dispId-PAGE_DISPID_OFFSET,riid,lCid,
				wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);

			CString oSource;
			CString oDescription;
			SCODE scode = 0;
			WORD wCode = 0;
			if (pExceptInfo != NULL)
			{
				if (pExceptInfo->bstrSource != NULL)
				{
					oSource = pExceptInfo->bstrSource;
				}
				if (pExceptInfo->bstrDescription != NULL)
				{
					oDescription = pExceptInfo->bstrDescription;
				}
				scode = pExceptInfo->scode;
				wCode = pExceptInfo->wCode;
			}

			CString oDiag;
			oDiag.Format(_T("Invoke window end dispid=%ld script_dispid=%ld hr=0x%08lx result_vt=0x%04x wCode=%u scode=0x%08lx source=%s desc=%s"),
				dispId, dispId-PAGE_DISPID_OFFSET, hr,
				(pVarResult != NULL) ? pVarResult->vt : VT_EMPTY,
				wCode, scode, (LPCTSTR)oSource, (LPCTSTR)oDescription);
			_cocoon_navopage_auto_diag(oDiag);
			return hr;
		}
	}
	TOP_ALL_CATCH_AUTOMATION(pThis->GetErrorStorage(),pExceptInfo);
}

