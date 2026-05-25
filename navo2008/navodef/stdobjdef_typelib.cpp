/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	StdObj definitions
	
	IDispatch implenetation
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "stdobjdef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------

BEGIN_INTERFACE_MAP(CStdObjDef, CCmdTargetInterface)
	INTERFACE_PART(CStdObjDef, IID_IDispatch, PropDispatch)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CStdObjDef, PropDispatch)  

STDMETHODIMP CStdObjDef::XPropDispatch::GetTypeInfoCount(UINT* pCount)
{
	METHOD_PROLOGUE(CStdObjDef, PropDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfoCount(pCount);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CStdObjDef::XPropDispatch::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo ** ppTInfo)
{
	METHOD_PROLOGUE(CStdObjDef, PropDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfo(iTInfo,lcid,ppTInfo);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CStdObjDef::XPropDispatch::
	GetIDsOfNames(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId)
{
	METHOD_PROLOGUE(CStdObjDef, PropDispatch)
	
	ALL_TRY
	{
		HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);
		if(hr == DISP_E_UNKNOWNNAME)
		{
			hr = pThis->__GetIDsOfNames(rgszNames,cNames,rgDispId);
			return hr;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CStdObjDef::XPropDispatch::
	Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError)
{
	METHOD_PROLOGUE(CStdObjDef, PropDispatch)
	
	ALL_TRY
	{
		if(dispId == DISPID_VALUE)
		{
			return DISP_E_MEMBERNOTFOUND;
		}

		HRESULT hr = ((IDispatch*)&pThis->m_xDispatch)->
				Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
		if(hr != DISP_E_MEMBERNOTFOUND)
		{
			return hr;
		}
		else
		{
			return pThis->__Invoke(dispId,riid,lCid,wFlags,pDispParams,pVarResult,pExceptInfo,puArgError);
		}
	}
	TOP_ALL_CATCH_AUTOMATION(pThis->GetErrorStorage(),pExceptInfo);
}
