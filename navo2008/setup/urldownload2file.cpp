/*
	NAVO 2002 Project (2002)

	SETUP application

	download url to file
*/


#include "stdafx.h"
#include "..\include\progressgadget.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CDownloadBindStatusCallback : public CCmdTargetInterface
{
public:

	BEGIN_INTERFACE_PART(BindStatusCallback,IBindStatusCallback)
		STDMETHOD(OnStartBinding)(DWORD ,IBinding *)
		{
			return S_OK;
		}

		STDMETHOD(GetPriority)(LONG *)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnLowResource)(DWORD)
		{
			return S_OK;
		}
		STDMETHOD(OnProgress)(ULONG ulProgress,ULONG ulProgressMax,ULONG ulStatusCode,LPCWSTR /*szStatusText*/)
		{
			METHOD_PROLOGUE(CDownloadBindStatusCallback, BindStatusCallback)

			switch(ulStatusCode)
			{
			case BINDSTATUS_BEGINDOWNLOADDATA:
				pThis->m_poProgressInfoSP = NewSCP(new CProgressInfo(100,true,pThis->m_oTitleString,
					CWnd::GetActiveWindow() ));
				::SetCursor(::LoadCursor(NULL,IDC_ARROW));
			break;
			case BINDSTATUS_DOWNLOADINGDATA:
				pThis->m_poProgressInfoSP->SetElapsed(ulProgress*100/ulProgressMax);
				if(pThis->m_poProgressInfoSP->IsBroken())
				{
					return E_ABORT;
				}
			break;
			case BINDSTATUS_ENDDOWNLOADDATA:
				pThis->m_poProgressInfoSP = 0;
			break;
			}
			return S_OK;
		}
		STDMETHOD(OnStopBinding)(HRESULT,LPCWSTR)
		{
			return S_OK;
		}
		STDMETHOD(GetBindInfo)(DWORD *grfBINDF,BINDINFO *)
		{
			*grfBINDF = BINDF_GETNEWESTVERSION | BINDF_PRAGMA_NO_CACHE;
			return S_OK;
		}
		STDMETHOD(OnDataAvailable)(DWORD ,DWORD ,FORMATETC *,STGMEDIUM *)
		{
			return S_OK;
		}
		STDMETHOD(OnObjectAvailable)(REFIID ,IUnknown*)
		{
			return S_OK;
		}
	END_INTERFACE_PART(BindStatusCallback)
	DECLARE_INTERFACE_MAP()
public:
	SCP<CProgressInfo> m_poProgressInfoSP;
	CString m_oTitleString;
};

DELEGATE_UNKNOWN_INTERFACE(CDownloadBindStatusCallback, BindStatusCallback)  

BEGIN_INTERFACE_MAP(CDownloadBindStatusCallback, CCmdTargetInterface)
    INTERFACE_PART(CDownloadBindStatusCallback, IID_IBindStatusCallback, BindStatusCallback)
END_INTERFACE_MAP()

/*  
  LPUNKNOWN pCaller,  // Caller's controlling IUnknown
  LPCWSTR szURL,      // Pointer to URL to be downloaded
  LPCTSTR szFileName, // Pointer to file name
  DWORD dwResv,       // Reserved for future use
  LPBINDSTATUSCALLBACK lpfnCB
*/                    

static HRESULT STDAPICALLTYPE virtual_URLDownloadToFile(LPUNKNOWN p1,LPCSTR p2,LPCSTR p3,DWORD p4,LPBINDSTATUSCALLBACK p5)
{
	CDLLHolder oDLLHolder(_T("URLMON.DLL"));
	HRESULT (STDAPICALLTYPE *pFunction)(LPUNKNOWN,LPCSTR,LPCSTR,DWORD,LPBINDSTATUSCALLBACK);
	if(oDLLHolder.SafeGetProcAddress(pFunction, _T("URLDownloadToFileA") ) != ERROR_SUCCESS)
	{
		return E_NOTIMPL;
	}
	return pFunction(p1,p2,p3,p4,p5);
}

HRESULT download_url_2_file(LPCTSTR lpURL,LPCTSTR lpFile,bool bUI)
{ 
	SCP<CDownloadBindStatusCallback> poDBSCSP = NewSCP(new CDownloadBindStatusCallback());
	poDBSCSP->m_oTitleString = _T("Trwa pobieranie z ") + CString(lpURL);
	SCP<IBindStatusCallback> pIBindStatusCallbackSP;
	pIBindStatusCallbackSP.QueryInterface(poDBSCSP);
	
	return virtual_URLDownloadToFile(NULL,lpURL,lpFile,0,bUI ? pIBindStatusCallbackSP.Get() : NULL);
}
/*
  LPUNKNOWN pCaller,  // Caller's controlling IUnknown
  LPCWSTR szURL,      // Pointer to URL to be downloaded
  LPTSTR szFileName,  // Pointer to name of cached file
  DWORD dwBufLen,     // Size of szFileName
  DWORD dwResv,       // Reserved for future use
  LPBINDSTATUSCALLBACK lpfnCB
*/
                      
static HRESULT STDAPICALLTYPE virtual_URLDownloadToCacheFile(LPUNKNOWN p1, LPCSTR p2, LPSTR p3, DWORD p4, DWORD p5, LPBINDSTATUSCALLBACK p6)
{
	CDLLHolder oDLLHolder(_T("URLMON.DLL"));
	HRESULT (STDAPICALLTYPE *pFunction)(LPUNKNOWN,LPCSTR,LPSTR,DWORD,DWORD,LPBINDSTATUSCALLBACK);

	if(oDLLHolder.SafeGetProcAddress(pFunction, _T("URLDownloadToCacheFileA") ) != ERROR_SUCCESS)
	{
		return E_NOTIMPL;
	}

	return pFunction(p1,p2,p3,p4,p5,p6);
}

HRESULT download_url_2_cache_file(LPCTSTR lpURL, LPTSTR lpFile,bool bUI)
{ 
	SCP<CDownloadBindStatusCallback> poDBSCSP = NewSCP(new CDownloadBindStatusCallback());
	poDBSCSP->m_oTitleString = _T("Trwa pobieranie z ") + CString(lpURL);
	SCP<IBindStatusCallback> pIBindStatusCallbackSP;
	pIBindStatusCallbackSP.QueryInterface(poDBSCSP);
	
	return virtual_URLDownloadToCacheFile(NULL, lpURL, lpFile, MAX_PATH, 0, bUI ? pIBindStatusCallbackSP.Get() : NULL);
}