/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CSingleServerPlaceCacheInfo - single server info
		Indexing Service Support
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "CacheManager.h"
#include "_impinxserv.h"

#ifdef EOF
#undef EOF
#endif
#import MSADO15_PATH 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR _glp_CatalogName = _T("NAVOEnterprise2002");

void CSingleServerPlaceCacheInfo::_setup_indexing_service()
{
	return;
	//do not install when no network is present
	//(MS bug)

	if((::GetSystemMetrics(SM_NETWORK) & 1) == 0)
	{
		return;
	}

	IAdminIndexServer oAdminIS;
	if(!oAdminIS.CreateDispatch(_T("Microsoft.ISAdm")))
	{
		//to_do: service not exists
		return;
	}
	oAdminIS.SetMachineName(GetSystemEnvironmentHLI()->GetStrProp(GVAR_MACHINE));
	
	//stop service
	if(oAdminIS.IsRunning())
	{
		oAdminIS.Stop();
		long nTryCount = 25;	
		while(oAdminIS.IsRunning() && nTryCount--)
		{
			::Sleep(1000);
		}
		if(nTryCount == 0)
		{
			//to_do: error timeout
			return;
		}
	}

	ICatAdm oCatAdm;
	
	TRY
	{
		oCatAdm.AttachDispatch(oAdminIS.GetCatalogByName(_glp_CatalogName));
	}
	CATCH(COleDispatchException,pODE)
	{
		HRESULT hr = pODE->m_scError;
//nie wolno kasowaæ wyj¹tku		pODE->Delete();
		if(HRESULT_CODE(hr) != ERROR_NOT_FOUND)
		{
			return;
		}
	}
	END_CATCH

	if(oCatAdm.m_lpDispatch == NULL)
	{
		oCatAdm.AttachDispatch(oAdminIS.AddCatalog(_glp_CatalogName,m_poCacheManager->_get_root_dir()));
	}
	if(oCatAdm.m_lpDispatch == NULL)
	{
		//to_do: error creating catalog failed
		return;
	}
	TRY
	{
		CSmartOleVariant oSOV;
		IScopeAdm oScopeAdm(oCatAdm.AddScope(m_oStorageDirString,FALSE,oSOV.GetVariantRef(),oSOV.GetVariantRef()));
	}
	CATCH(COleDispatchException,pODE)
	{
		HRESULT hr = pODE->m_scError;
//nie wolno kasowaæ wyj¹tku		pODE->Delete();
		if(HRESULT_CODE(hr) != ERROR_ALREADY_EXISTS)
		{
			//to_do: error scope add failed - reason other than reinstallation
			return;
		}
	}
	END_CATCH
	
	oAdminIS.Start();
}


void CSingleServerPlaceCacheInfo::unsetup_indexing_service()
{
	return;

	IAdminIndexServer oAdminIS;
	if(!oAdminIS.CreateDispatch(_T("Microsoft.ISAdm")))
	{
		//to_do: service not exists
		return;
	}
	oAdminIS.SetMachineName(GetSystemEnvironmentHLI()->GetStrProp(GVAR_MACHINE));
	
	//stop service
	if(oAdminIS.IsRunning())
	{
		oAdminIS.Stop();
		long nTryCount = 25;	
		while(oAdminIS.IsRunning() && nTryCount--)
		{
			::Sleep(1000);
		}
		if(nTryCount == 0)
		{
			//to_do: error timeout
			return;
		}
	}
	
	TRY
	{
		oAdminIS.RemoveCatalog(_glp_CatalogName,TRUE);
	}
	CATCH(COleDispatchException,pODE)
	{
		pODE->Delete();
	}
	END_CATCH
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

class CSimpleIdEnumerator : public CCmdTargetInterface
{
public:
	CSimpleIdEnumerator():
	m_nCurrent(-1)
	{
	}
	void Add(long nFileId)
	{
		m_oFileIdArray.Add(nFileId);
	}
	DECLARE_INTERFACE_MAP();

	BEGIN_INTERFACE_PART(SimpleEnumId,ISimpleEnumId)
		STDMETHOD(Next)(long * pId);
		STDMETHOD(NextFull)(long * pId,LPSTR * plpValue);
	END_INTERFACE_PART(SimpleEnumId)
private:
	CArray<long, long> m_oFileIdArray;
	long m_nCurrent;
};

BEGIN_INTERFACE_MAP(CSimpleIdEnumerator, CCmdTargetInterface)
	INTERFACE_PART(CSimpleIdEnumerator, IID_ISimpleEnumId, SimpleEnumId)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CSimpleIdEnumerator, SimpleEnumId)


STDMETHODIMP CSimpleIdEnumerator::XSimpleEnumId::Next(long * pFileId)
{
	METHOD_PROLOGUE(CSimpleIdEnumerator, SimpleEnumId)
	
	ALL_TRY
	{
		* pFileId = 0;
		 pThis->m_nCurrent++;
		 if(pThis->m_nCurrent <= pThis->m_oFileIdArray.GetUpperBound())
		 {
			 * pFileId = pThis->m_oFileIdArray[pThis->m_nCurrent];
			 return S_OK;
		 }
		 else
		 {
			 return S_FALSE;
		 }
	}
	ALL_CATCH(CNavoException & roException)
	{
		//to_do:
		int TO_DO;				
		return DISP_E_EXCEPTION;
	};
}

STDMETHODIMP CSimpleIdEnumerator::XSimpleEnumId::NextFull(long *,LPSTR *)
{
	return E_NOTIMPL;
}

HRESULT CSingleServerPlaceCacheInfo::fts_query(LPCTSTR lpQuery,ISimpleEnumId ** ppSimpleEnumFileId)
{
	return S_FALSE;

	if(ppSimpleEnumFileId == NULL)
	{
		return E_INVALIDARG;
	}
	*ppSimpleEnumFileId = NULL;
	IAdminIndexServer oAdminIS;
	if(!oAdminIS.CreateDispatch(_T("Microsoft.ISAdm")))
	{
		return S_FALSE;
	}
	oAdminIS.SetMachineName(GetSystemEnvironmentHLI()->GetStrProp(GVAR_MACHINE));
	if(!oAdminIS.IsRunning())
	{
		oAdminIS.Start();
		long nTryCount = 25;	
		while(!oAdminIS.IsRunning() && nTryCount--)
		{
			::Sleep(1000);
		}
		if(nTryCount == 0)
		{
			return CO_E_START_SERVICE_FAILURE;
		}
	}
	IixssoQuery oQuery;
	if(!oQuery.CreateDispatch(_T("IXSSO.Query")))
	{
		return CO_E_CLASS_CREATE_FAILED;
	}
	IixssoUtil oUtils;
	if(!oUtils.CreateDispatch(_T("IXSSO.Util")))
	{
		return CO_E_CLASS_CREATE_FAILED;
	}
	oQuery.SetCatalog(_glp_CatalogName);
	oQuery.SetColumns(_T("filename"));
	oQuery.SetQuery(lpQuery);
	oQuery.SetMaxRecords(500);
	oUtils.AddScopeToQuery(oQuery,m_oStorageDirString,_T("deep"));
	
	ADODB::_RecordsetPtr poRecordsetPtr = oQuery.CreateRecordset("sequential");
	SCP<CSimpleIdEnumerator> poSimpleIdEnumSP = NewSCP(new CSimpleIdEnumerator());
	while(!poRecordsetPtr->EOF)
	{
		_variant_t vIndex = long(0);
		ADODB::FieldPtr poFieldPtr = poRecordsetPtr->Fields->GetItem(vIndex);
		CString oFileNameString(poFieldPtr->GetValue().bstrVal);
		
		long IdFile = _ttol(oFileNameString);
		TRACE("fileid = %d\n", IdFile);
		poSimpleIdEnumSP->Add(IdFile);

		poRecordsetPtr->MoveNext();
	}
	SCP<ISimpleEnumId> poISimpleEnumIdSP;
	poISimpleEnumIdSP.QueryInterface(poSimpleIdEnumSP);
	* ppSimpleEnumFileId = poISimpleEnumIdSP.Detach();
	return S_OK;
}

