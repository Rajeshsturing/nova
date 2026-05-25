/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	OLE helper functions
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\navolog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#undef AFX_DATA
#ifdef THIS_IS_NAVOCORE
	#define AFX_DATA _declspec(dllexport)
#else
	#define AFX_DATA _declspec(dllimport)
#endif
IMPLEMENT_DYNCREATE(CCmdTargetInterface,CCmdTarget);
#undef AFX_DATA
#define AFX_DATA

CNavoOleInitHolder::CNavoOleInitHolder(CNavoOleInitHolder::EType eType):
	m_eType(eType)
{
	HRESULT hResult = S_OK;
	switch(eType)
	{
	case APARTMENT:
		hResult = ::OleInitialize(NULL);
	break;
	case MULTITHREADED:
		hResult = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	break;
	default:
		ASSERT(false);
	};
	m_bShouldFree = (hResult == S_OK || hResult == S_FALSE);
#ifdef _DEBUG
	ASSERT(m_bShouldFree);	//bêdziemy wiedzieæ ¿e Ÿle posz³o
	if(!m_bShouldFree)
	{
		CString oMsgString;
		oMsgString.Format("OLE init failed with code %d",hResult);
		AfxMessageBox(oMsgString);
	}
#endif
}

CNavoOleInitHolder::~CNavoOleInitHolder() 
{
	if(m_bShouldFree)
	{
		switch(m_eType)
		{
		case APARTMENT:
			::OleUninitialize();
		break;
		case MULTITHREADED:
			::CoUninitialize();
		break;
		default:
			ASSERT(false);
		};
	}
}

struct CScriptArgumentShadow
{
	CSmartOleVariant m_oSmartOleVariant;
	VARTYPE			 m_nVarType;
};

HRESULT DispatchInvoke(IDispatch * iDispatch, const DISPID id, CSmartOleVariant * pArgumentsSmartOleVariant,	const long lSize, CSmartOleVariant *poResultSmartOleVariant, EXCEPINFO * poExceptInfo)
{
	long lIndex;
	DISPPARAMS DispParams;
	EXCEPINFO ei;
	if (!poExceptInfo)
	{
		poExceptInfo = &ei;
	};
	bool bAreReferences = false;
	DispParams.rgvarg = CSmartOleVariantPToCOleVariantP(pArgumentsSmartOleVariant);
	DispParams.rgdispidNamedArgs = NULL;
	DispParams.cArgs = lSize;
	DispParams.cNamedArgs = 0;
	CArray <CScriptArgumentShadow, CScriptArgumentShadow &> oShadowArgumentsArray;
	oShadowArgumentsArray.SetSize(lSize);
	for (lIndex = 0; lIndex < lSize; lIndex++)
	{
		if (pArgumentsSmartOleVariant[lIndex].Type() & VT_NAVOBYREF)
		{
			bAreReferences = true;
			pArgumentsSmartOleVariant[lIndex].ClearNavoRef();
			oShadowArgumentsArray[lIndex].m_nVarType = pArgumentsSmartOleVariant[lIndex].Type();
			oShadowArgumentsArray[lIndex].m_oSmartOleVariant = pArgumentsSmartOleVariant[lIndex];
			pArgumentsSmartOleVariant[lIndex].SetRef(oShadowArgumentsArray[lIndex].m_oSmartOleVariant);
		};
	};
	HRESULT hResult = iDispatch->
		Invoke(id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &DispParams, 
		CSmartOleVariantPToCOleVariantP(poResultSmartOleVariant), poExceptInfo, NULL);
	if(hResult == S_OK)
	{
		if (bAreReferences)
		{
			for (lIndex = 0; lIndex < lSize; lIndex++)
			{
				if (pArgumentsSmartOleVariant[lIndex].Type() == (VT_VARIANT | VT_BYREF))
				{
					CSmartOleVariant & roSourceVariant = oShadowArgumentsArray[lIndex].m_oSmartOleVariant,
						& roDestinationVariant = pArgumentsSmartOleVariant[lIndex];
					VARTYPE nDestinationVarType = oShadowArgumentsArray[lIndex].m_nVarType;
					/*
					Typ wyniku nie jest okreslony
					lub musi sie zgadzac
					*/
					if (nDestinationVarType == VT_EMPTY ||
						nDestinationVarType == roSourceVariant.Type())
					{
						roDestinationVariant = roSourceVariant; 
					}
					else
					{
						// sprobujemy konwertowac
						switch(nDestinationVarType)
						{
						case VT_I4:
							if (roSourceVariant.Type() == VT_I2)
							{
								roDestinationVariant.Set(roSourceVariant, VT_I4);
							};
							break;
						};
					};
					if (roDestinationVariant.Type() == (VT_VARIANT | VT_BYREF))
					{
						ThrowNavoException(ERCO_FUN_CHANGED_REF_ARGS_TYPE, IDPAGE_NOTAVAILABLE);
					};
				};
			};
		};
	}
	else if (!poExceptInfo)
	{
		CString ErrorDescriptionString(ei.bstrDescription);
		ThrowNavoException2(ERCO_INVOKE_FAILED, IDPAGE_NOTAVAILABLE, ei.wCode, ErrorDescriptionString);
	};
	return hResult;
}

BEGIN_INTERFACE_MAP(CSupplyInfo__, CCmdTargetInterface)
    INTERFACE_PART(CSupplyInfo__, IID_ISupplyInfo, SupplyInfo)
    INTERFACE_PART(CSupplyInfo__, IID_IDispatch, Dispatch)
END_INTERFACE_MAP()

BEGIN_DISPATCH_MAP(CSupplyInfo__, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CSupplyInfo__)
	DISP_FUNCTION_ID(CSupplyInfo__, "AskForData", 2,AskForDataAUTO, VT_EMPTY, VTS_I4 VTS_BSTR VTS_VARIANT VTS_PVARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

DELEGATE_UNKNOWN_INTERFACE(CSupplyInfo__, SupplyInfo)

const OLECHAR * lpctAskForData = L"AskForData";
const OLECHAR * lpctOnProgress = L"OnProgress";

HRESULT CScriptSupplyInfo::Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer)
{
	ASSERT(m_poDispatchSP);
	if(m_dispidAskForData == 0)
	{
		m_dispidAskForData = DispatchGetIdOfName(m_poDispatchSP.Get(),lpctAskForData);
	}
	ASSERT(m_dispidAskForData);

	CSmartOleVariant oArgumentSOVArray[4];
	oArgumentSOVArray[3] = CSmartOleVariant(nInfoType);
	oArgumentSOVArray[2] = CSmartOleVariant(lpDescription);
	oArgumentSOVArray[1] = CSmartOleVariant(varQuestion);
	oArgumentSOVArray[0] = CSmartOleVariant(*pvarAnswer);
	oArgumentSOVArray[0].SetNavoRef();

	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poDispatchSP, m_dispidAskForData,
		(CSmartOleVariant*)&oArgumentSOVArray,4,NULL,&ei);
	if (hResult != S_OK)
	{
		ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED,IDPAGE_NOTAVAILABLE,(LPCTSTR)
			(CString(ei.bstrSource) + " " + CString(ei.bstrDescription)),
			SCODE_To_String(hResult));
	};
	//copy result
	*pvarAnswer = oArgumentSOVArray[0].Detach();
	return hResult;
}

HRESULT CScriptSupplyInfo::Impl_OnProgress(long nInfoType,long lAdvance,long lTotal,LPSTR lpDescription)
{
	ASSERT(m_poDispatchSP);
	if(m_dispidOnProgress == 0)
	{
		m_dispidOnProgress = DispatchGetIdOfName(m_poDispatchSP.Get(),lpctOnProgress);
	}
	ASSERT(m_dispidOnProgress);

	CSmartOleVariant oArgumentSOVArray[4];
	oArgumentSOVArray[3] = CSmartOleVariant(nInfoType);
	oArgumentSOVArray[2] = CSmartOleVariant(lAdvance);
	oArgumentSOVArray[1] = CSmartOleVariant(lTotal);
	oArgumentSOVArray[0] = CSmartOleVariant(lpDescription);
	CSmartOleVariant oResultSOV;
	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poDispatchSP, m_dispidOnProgress,
		(CSmartOleVariant*)&oArgumentSOVArray,4,&oResultSOV,&ei);
	if (hResult != S_OK)
	{
		ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED,IDPAGE_NOTAVAILABLE,(LPCTSTR)
			(CString(ei.bstrSource) + " " + CString(ei.bstrDescription)),
			SCODE_To_String(hResult));
	};
	if(oResultSOV.Type() == VT_BOOL)
	{
		if(!oResultSOV.GetBool())
		{
			return ERROR_CANCELLED;
		}
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------
// implementation from interfaceutil.h
//-------------------------------------------------------------------------------------

HRESULT StdNotifyOnProgress(SCP<INotificationSink> & rpoNotificationSinkSP,
							long nInfoType,long nAdv,long nTotal,LPCTSTR lpMsg)
{
	HRESULT hr = S_OK;
	if(rpoNotificationSinkSP.PointsObject())
	{
		hr = rpoNotificationSinkSP->OnProgress(nInfoType,nAdv,nTotal,(LPTSTR)lpMsg);
		
		MSG msg;
		while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	return hr;
}

HRESULT IStream_CopyTo_WithNotify(SCP<INotificationSink> & rpoNotificationSinkSP,
	SCP<IStream> & rpoSrcStreamSP,SCP<IStream> & rpoDestStreamSP,LPCTSTR lpStreamName,
	__int64 i64StreamSize)
{
	CString oStreamName(lpStreamName);
	CString oInformationString;

	const long nCopyPartSize = 0x00040000; //256KB
	ULARGE_INTEGER ulPart;
	
	//write stream data, in part to allow abort
	for(__int64 i64SizeCopied = 0; i64SizeCopied < i64StreamSize; i64SizeCopied += nCopyPartSize)
	{
		ulPart.QuadPart = min(nCopyPartSize,i64StreamSize-i64SizeCopied);	
		ULARGE_INTEGER ulBytesRead;
		ULARGE_INTEGER ulBytesWritten;
		ulBytesRead.QuadPart = 0;
		ulBytesWritten.QuadPart = 0;

		HRESULT hr = rpoSrcStreamSP->CopyTo(rpoDestStreamSP,ulPart,&ulBytesRead,&ulBytesWritten);
		if(hr != S_OK)
		{
			return hr;
		}
		if(ulBytesWritten.QuadPart == 0 || ulBytesRead.QuadPart == 0)
		{
			return S_OK;
		}
		if(i64StreamSize > nCopyPartSize)	//wyœwieltaj tylko dla du¿ych
		{
			//LANGUAGE:PL
			oInformationString.Format(_T("Kopiowanie pliku %s"),oStreamName);
			if(StdNotifyOnProgress(rpoNotificationSinkSP,NOTF_COPYING_FILE,
				long(i64SizeCopied),long(i64StreamSize),oInformationString) != S_OK)
			{
				return ERROR_CANCELLED;
			}
		}
	}
	return S_OK;
}

/*
	podstawowa implementacja ping-servera
*/

CPingServerImpl::~CPingServerImpl()
{
	CSimpleLock oSimpleLock(m_oCookieCS);
	ASSERT(m_oMap.GetCount() == 0);
}

void CPingServerImpl::__Advise(IUnknown * pPingUnknown,long nCookie)
{
	SCP<IPingClient> poPingClientSP;
	poPingClientSP.QueryInterface(pPingUnknown);
	{
		CSimpleLock oSimpleLock(m_oCookieCS);
#ifdef _DEBUG
		{
			SCP<IPingClient> poTestSP;
			ASSERT(!m_oMap.Lookup(nCookie,poTestSP));
		}
#endif
		m_oMap[ nCookie ] = poPingClientSP;
	}
}
void CPingServerImpl::__UnAdvise(long nCookie)
{
	CSimpleLock oSimpleLock(m_oCookieCS);
	VERIFY(m_oMap.RemoveKey(nCookie));
}

void CPingServerImpl::__PerformPingTest(CNavoLog & roLog)
{
	CSimpleLock oSimpleLock(m_oCookieCS);
	POSITION pos = m_oMap.GetStartPosition();
	while(pos)
	{
		
		long nCookie;
		SCP<IPingClient> poPingClientSP;
		m_oMap.GetNextAssoc(pos,nCookie,poPingClientSP);
		bool bClientAlive = false;
		DWORD dwStartTime = ::GetTickCount();

		try
		{
			/*
			if(roLog.IsHandleValid())
			{
				CString oString;
				oString.Format("> pinging cookie=%d",nCookie);
				roLog << oString;
			}
			*/

			ASSERT(poPingClientSP.PointsObject());
			HRESULT hr = poPingClientSP->Ping();
			if(hr == S_OK)
			{
				bClientAlive = true;
				
				if(roLog.IsHandleValid())
				{
					DWORD dwEndTime = ::GetTickCount();
					if(dwEndTime - dwStartTime > 500)
					{
						CString oString;
						oString.Format("! long ping cookie=%d,OK,time=%d",nCookie,(dwEndTime - dwStartTime));
						roLog << oString;
					}
				}
			}
			else
			{
				if(roLog.IsHandleValid())
				{
					DWORD dwEndTime = ::GetTickCount();
					CString oString;
					oString.Format("< pinging cookie=%d,ERROR,time=%d",nCookie,(dwEndTime - dwStartTime));
					roLog << oString;
				}

				VERIFY(m_oMap.RemoveKey(nCookie));
				_force_release(poPingClientSP.Detach());
				pos = m_oMap.GetStartPosition();	//restart iteration
			}
		}
		catch(...)
		{
			if(roLog.IsHandleValid())
			{
				CString oString;
				oString.Format("< pinging cookie=%d,THREW,time=%d",nCookie,(::GetTickCount() - dwStartTime));
				roLog << oString;
			}
		}
		if(!bClientAlive)
		{
			try
			{
				if(roLog.IsHandleValid())
				{
					CString oString;
					oString.Format("killing dead client, cookie=%d,",nCookie);
					roLog << oString;
				}

				OnDeadClient(nCookie);

				if(roLog.IsHandleValid())
				{
					CString oString;
					oString.Format("dead client killed, cookie=%d,",nCookie);
					roLog << oString;
				}
			
			}
			catch(...)
			{
				if(roLog.IsHandleValid())
				{
					CString oString;
					oString.Format("killing THREW, cookie=%d,",nCookie);
					roLog << oString;
				}
			}
		}
	}
}
