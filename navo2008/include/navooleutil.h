/*
	NAVO Sp. z o.o. (1999)

	NAVO Enterprise

	OLE helper functions
*/

#ifndef _NAVOOLEUTIL_H_
#define _NAVOOLEUTIL_H_

class CNavoOleInitHolder : public CInterface__
{
public:
	enum EType
	{
		APARTMENT,
		MULTITHREADED,
	};
	CNavoOleInitHolder(EType eType);
	~CNavoOleInitHolder();
	bool IsOK() const
	{
		return m_bShouldFree;
	}
	void SetAbortMode()
	{
		m_bShouldFree = false;
	}
private:
	bool m_bShouldFree;
	EType m_eType;
};

/*
 klasa : CRemoteFreeHolder
 autor : Mariusz
 opis  :
	Destruktor wywoluje NdrOleFree. Jej deklaracje nalezy umiescic mozliwie
	zaraz po deklaracji zmiennej, ktora sie opiekuje. W konstruktorze
	CRemoteFreeHolder zeruje ta zmienna (aby nie zwalniac w destruktorze smieci).
	Zatem konstruktor CRemoteFreeHolder koniecznie musi byc wywolany przed
	wlasciwa fukkcja RPC. Kluczowa jest referencja w konstruktorze.
*/
#ifndef _MINI_CORE_

class CRemoteFreeHolder
{
public:
	template <typename T>
	CRemoteFreeHolder(T * & rpBuffer) :
		m_rpBuffer((void * &)rpBuffer),
		m_bFree(true)
	{
		m_rpBuffer = NULL;
	};
	~CRemoteFreeHolder()
	{
		if (m_rpBuffer && m_bFree)
		{
			::NdrOleFree(m_rpBuffer);
			m_rpBuffer = NULL;
		};
	};
	void Release()
	{
		m_bFree = false;
	};

private:
	void * & m_rpBuffer;
	bool m_bFree;
};

template <class T>
class CRPCLoader_via_Archive
{
public:
	CRPCLoader_via_Archive(T & roT) :
		m_oRemoteFreeHolder(m_pData),
		m_roT(roT)
	{
		// dla trybu [out] parameters
	};
	CRPCLoader_via_Archive(T & roT, long lLength, BYTE * pData) :
		m_roT(roT),
		m_oRemoteFreeHolder(m_pData),
		m_lDataLength(lLength),
		m_pData(pData)
	{
		// dla trybu [in] parameters
		m_oRemoteFreeHolder.Release();
	};
	long * GetLength()
	{
		return &m_lDataLength;
	};
	BYTE ** GetData()
	{
		return &m_pData;
	};
	void Load()
	{
		CMemFile oMemFile;
		oMemFile.Attach(*GetData(), *GetLength());
		oMemFile.SeekToBegin();
		CArchive oArchive(&oMemFile, CArchive::load);
		oArchive >> m_roT;
	};

	CRemoteFreeHolder m_oRemoteFreeHolder;

private:
	T & m_roT;
	long m_lDataLength;
	BYTE * m_pData;
};

template <class T>
class CRPCSaver_via_Archive
{
public:
	CRPCSaver_via_Archive(T & roT) :
		m_oRemoteFreeHolder(m_pData),
		m_roT(roT)
	{
	}
	void Store()
	{
		CMemFile oMemFile;
		{
			CArchive oArchive(&oMemFile, CArchive::store);
			oArchive << m_roT;
		}
		m_lDataLength = (long)oMemFile.GetLength();
		m_pData = (BYTE*) ::NdrOleAllocate(m_lDataLength);
		oMemFile.SeekToBegin();
		oMemFile.Read(m_pData, m_lDataLength);
		m_oRemoteFreeHolder.Release();
	}
	long GetLength() const
	{
		return m_lDataLength;
	};
	BYTE * GetData() const
	{
		return m_pData;
	};
private:
	CRemoteFreeHolder m_oRemoteFreeHolder;
	T & m_roT;
	long m_lDataLength;
	BYTE * m_pData;
};


//---------------------------------
// pojedyñcze funkcje
//---------------------------------

inline void RPCCopy(const void * pSrc, long nSrcLength, long *plDataLength, BYTE ** ppbData)
{
	*plDataLength = nSrcLength;
	*ppbData = (BYTE*) ::NdrOleAllocate(*plDataLength);
	memcpy(*ppbData, pSrc, *plDataLength);
}


inline bool SafeDispatchGetIdOfName(IDispatch * pIDispatch, const OLECHAR *pocName, DISPID & rdispid)
{
	ASSERT(pIDispatch);
	return (pIDispatch->GetIDsOfNames(IID_NULL, &const_cast <OLECHAR * &>(pocName), 1,
		LOCALE_USER_DEFAULT, &rdispid) == S_OK);
}

inline DISPID DispatchGetIdOfName(IDispatch * iDispatch, const OLECHAR * pocName)
{
	ASSERT(iDispatch);
	DISPID id;
	if (!SafeDispatchGetIdOfName(iDispatch, pocName, id))
	{
		USES_CONVERSION;
		LPTSTR ptr2ansi = OLE2T(pocName);
		ThrowNavoException1(ERCO_FUNCTION_NAME_NOT_FOUND, IDPAGE_NOTAVAILABLE, ptr2ansi);
	};
	return id;
};

#ifndef _UNICODE
inline DISPID DispatchGetIdOfName(IDispatch * iDispatch, const CString &roString)
{
	CArray <OLECHAR, OLECHAR> oNameArray;
	oNameArray.SetSize((roString.GetLength() + 1) * sizeof(OLECHAR));
	MultiByteToWideChar(CP_ACP, 0, roString, roString.GetLength() + 1,
		oNameArray.GetData(), oNameArray.GetSize());
	return DispatchGetIdOfName(iDispatch, oNameArray.GetData());
}
#endif

HRESULT DispatchInvoke(IDispatch * pDispatch, const DISPID id, CSmartOleVariant * pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant * poResultSmartOleVariant, EXCEPINFO * poExceptInfo);

//--------------------------------
// wyj¹tkowowo tutaj, ale w errorsupport.h jeszcze nie ma SCP
//--------------------------------
template <class T>
bool GetErrorInfoFromInterface(T & oT, CNavoException & roNavoException)
{
	if (oT == NULL)
	{
		return false;
	}

	SCP<IUnknown> pUnknownSP;
	pUnknownSP.QueryInterface(oT);
	CNavoErrorInfo oNavoErrorInfo;
	bool bAny = false;
	while (ErrorInfoFromInterface(pUnknownSP, oNavoErrorInfo))
	{
		roNavoException += (oNavoErrorInfo);
		bAny = true;
	}
	return bAny;
};


template <class T>
void ThrowFromInterface(T & oT)
{
	if (IsNXMTransport())
	{
		if (oT != NULL)
		{
			SCP<IUnknown> pUnknownSP;
			pUnknownSP.QueryInterface(oT);
			SCP <INavoErrorInfo> poErrorInfoSP;
			if (poErrorInfoSP.SafeQueryInterface(pUnknownSP))
			{
				LPSTR pcErrors = NULL;
				
				if (poErrorInfoSP->RetrieveError2(&pcErrors) == S_OK)
				{
					CString oErrors(pcErrors);
					ThrowNavoException1(ERCO_GENERAL_DETAILS, IDPAGE_NOTAVAILABLE, oErrors);
				}
			};
		}
	}
	else
	{
		CNavoException oNavoException;
		if (GetErrorInfoFromInterface(oT, oNavoException))
		{
			throw oNavoException;
		}
		ThrowNavoException(ERCO_ERRORINFO_NO_INFO_AVAILABLE, IDPAGE_NOTAVAILABLE);
	}
};

template <class T>
HRESULT CreateRemoteInstance(REFCLSID rclsid, LPCTSTR lpServerName, const IID * pIID, SCP<T> & rpoInterfaceSP)
{
	USES_CONVERSION;

	TCHAR cComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD nComputerNameLen = sizeof(cComputerName);
	VERIFY(::GetComputerName(cComputerName, &nComputerNameLen));
	HRESULT hr = S_OK;
	if (!*lpServerName || _tcsicmp(cComputerName, lpServerName) == 0)	//empty server name or same computer
	{
		hr = ::CoCreateInstance(rclsid, NULL, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER, *pIID,
			reinterpret_cast<void**>(&rpoInterfaceSP.GetRawPointer()));
	}
	else	//truly remote server
	{
		COAUTHINFO AuthInfo;
		AuthInfo.dwAuthnSvc = RPC_C_AUTHN_WINNT;
		AuthInfo.dwAuthzSvc = RPC_C_AUTHZ_NONE;
		AuthInfo.pwszServerPrincName = NULL;
		AuthInfo.dwAuthnLevel = DCOM_AUTH_LEVEL;
		AuthInfo.dwImpersonationLevel = RPC_C_IMP_LEVEL_IMPERSONATE;
		AuthInfo.pAuthIdentityData = NULL;
		AuthInfo.dwCapabilities = EOAC_NONE;

		//old mode: AuthInfo.dwAuthnSvc = RPC_C_AUTHN_NONE;//RPC_C_AUTHN_WINNT;

		COSERVERINFO csi;
		memset(&csi, 0, sizeof(COSERVERINFO));
		csi.pAuthInfo = &AuthInfo;
		if (*lpServerName)
		{
			csi.pwszName = T2OLE(lpServerName);
		}
		MULTI_QI mq;
		mq.pIID = pIID;
		mq.pItf = NULL;
		mq.hr = S_OK;
		hr = ::CoCreateInstanceEx(rclsid, NULL, CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, &csi, 1, &mq);
		if (hr == S_OK)
		{
			ASSERT(mq.pItf != NULL);
			rpoInterfaceSP.QueryInterface(mq.pItf);
			mq.pItf->Release();
		}
	}
	return hr;
}

#endif	//not _MINI_CORE_


inline CString StringFromCLSID(const CLSID & rCLSID)
{
	CString AFXAPI AfxStringFromCLSID(REFCLSID rclsid); //from MFC
	return AfxStringFromCLSID(rCLSID);
}


enum eInvokeResult
{
	invoke_ok,
	invoke_true,
	invoke_false,
	invoke_failure,
	invoke_notexists
};

#else
#error __FILE__ already included
#endif
