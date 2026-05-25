/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManagerUser
*/


#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\flatdata.h"	//flat data transport
#include "..\include\InterfaceUtil.h"
#include "CacheManagerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
class CCMUStatistics
{
public:
	CCMUStatistics() :
		m_nRequests(0),
		m_nHits(0)

	{
	}
	~CCMUStatistics()
	{
		TRACE0("------ cmu stats ------------\n");
		TRACE1("requests = %d\n",m_nRequests);
		TRACE1("hits = %d\n",m_nHits);
		TRACE1("hit ratio (%%) = %d\n",(m_nRequests == 0) ? 0 : (100*m_nHits)/m_nRequests);
		TRACE0("------ --------- ------------\n");
	}
	void _request()
	{
		m_nRequests++;
	}
	void _hit()
	{
		m_nHits++;
	}
private:
	long m_nRequests;
	long m_nHits;
};

CCMUStatistics _debug_cmustat;
#endif

//----------------------------------------------------------------------------------------
// IStream
//----------------------------------------------------------------------------------------
BEGIN_INTERFACE_MAP(CCacheUser__, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CCacheUser__, IID_IStream, Stream)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CCacheUser__, Stream)

STDMETHODIMP CCacheUser__::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poOutputStreamSP.PointsNull())
		{
			pThis->m_poOutputStreamSP = pThis->Init();
		}
		HRESULT hr = pThis->m_poOutputStreamSP->Read(pData, lLength, plBytesRead);
		if(hr == S_OK)
		{
			if(!pThis->m_bDeliveredFromCache && pThis->m_poMirrorStreamSP.PointsObject())
			{
				unsigned long lBytesWritten;
				hr = pThis->m_poMirrorStreamSP->Write(pData, *plBytesRead, &lBytesWritten);
				ASSERT(*plBytesRead  == lBytesWritten || hr != S_OK);
			}
			return hr;
		}
		else
		{
			SCP<INavoErrorInfo> poNavoErrorInfoSP;
			if(poNavoErrorInfoSP.SafeQueryInterface(pThis->m_poOutputStreamSP))
			{
				ThrowFromInterface(poNavoErrorInfoSP);
			}
			else
			{
				return hr;
			}
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}


STDMETHODIMP CCacheUser__::XStream::
	Seek(LARGE_INTEGER ulMove, unsigned long dwOrigin,ULARGE_INTEGER * pulParam3)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
/*		LARGE_INTEGER ulZero;
		ulZero.QuadPart = 0;
		
		//jeœli jeszcze nie czytaliœmy i chcemy przewin¹æ siê na pocz¹tek - it is OK
		if(pThis->m_poOutputStreamSP.PointsNull() && 
			dwOrigin == STREAM_SEEK_SET && 
			ulMove.QuadPart == ulZero.QuadPart)
		{
			return S_OK;
		}
		ASSERT(false);
		return E_FAIL;
*/
		if(pThis->m_poOutputStreamSP.PointsNull())
		{
			pThis->m_poOutputStreamSP = pThis->Init();
		}
		return pThis->m_poOutputStreamSP->Seek(ulMove,dwOrigin,pulParam3);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	Write(const void *, unsigned long , unsigned long *)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	Revert()
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	Stat(STATSTG * pParam1, unsigned long ulParam2)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poOutputStreamSP.PointsNull())
		{
			pThis->m_poOutputStreamSP = pThis->Init();
		}
		return pThis->m_poOutputStreamSP->Stat(pParam1,ulParam2);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CCacheUser__::XStream::
	Clone(IStream ** ppIStream)
{
	METHOD_PROLOGUE(CCacheUser__, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poOutputStreamSP.PointsNull())
		{
			pThis->m_poOutputStreamSP = pThis->Init();
		}
		
		return pThis->m_poOutputStreamSP->Clone(ppIStream);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

//----------------------------------------------------------------------------------------
// implementation
//----------------------------------------------------------------------------------------
SCP<IStream> CCacheUser__::GetCacheStreamForStore()
{
	SCP<IStream> poCachedStreamSP;
	if(_get_cache().PointsNull())	//caching not enabled
	{
		return SCP<IStream>();
	}

	navostreaminfo oNSI;
	_init_navostreaminfo(oNSI);
	HRESULT hr = _get_cache()->StoreItem(m_IdFile,m_oFullPathServerString,m_oDescriptorArray.GetSize(),
		m_oDescriptorArray.GetData(),0,&oNSI,&poCachedStreamSP.GetRawPointer());
	if(hr != S_OK)
	{
		ThrowNavoException2(ERCO_CACHEMAN_STOREITEM_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
	}
	return poCachedStreamSP;
}
	
SCP<IStream> CCacheUser__::Init()
{
	SCP<IStream> poStreamSP;
	
	OnInit();

#ifdef _DEBUG
	_debug_cmustat._request();
#endif
	if(_get_cache().PointsNull())	//no caching available -> just provide preprocessed stream
	{
		return GetFinalStream();
	}
	else
	{
		PrepareDescriptor();
		//get cache info

		navostreaminfo oNSI;
		_init_navostreaminfo(oNSI);
		HRESULT hr = _get_cache()->GetItem(m_IdFile,m_oFullPathServerString,m_oDescriptorArray.GetSize(),
			m_oDescriptorArray.GetData(),&poStreamSP.GetRawPointer(),&oNSI);
		
		ASSERT(oNSI.m_bCompressed == '0');	//lokalny cache nie kompresuje

		switch(hr)
		{
		case S_OK:
		{
#ifdef _DEBUG
			_debug_cmustat._hit();
#endif
			m_bDeliveredFromCache = true;
			ASSERT(poStreamSP.PointsObject());
			return poStreamSP;
		}
		break;
		case S_FALSE:		//not in cache
		{
			ASSERT(poStreamSP.PointsNull());
			return GetFinalStream();
		}
		break;
		case DISP_E_EXCEPTION:
		{
			ASSERT(poStreamSP.PointsNull());
			CNavoException oNavoException;
			GetErrorInfoFromInterface(_get_cache(),oNavoException);
			ContinueThrowNavoException2(oNavoException,ERCO_CACHEMAN_GETITEM_FAILED,IDPAGE_NOTAVAILABLE, m_IdFile, SCODE_To_String(hr));
		}
		break;
		default:
		{
			ASSERT(poStreamSP.PointsNull());
			ThrowNavoException2(ERCO_CACHEMAN_GETITEM_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
		}
		}
	}
	ASSERT(false);
}

SCP<IStream> CCacheUser__::_begin_get_stream_and_auto_cache(long & rnTransaction)
{
	rnTransaction = 0;
	SCP<IStream> poStreamSP;
	poStreamSP.QueryInterface(this);

	if(!IsFromCache())
	{
		if(_get_cache().PointsObject())
		{
			HRESULT hr = _get_cache()->BeginTransaction(&rnTransaction);
			if(hr != S_OK)
			{
				ThrowNavoException2(ERCO_CACHEMAN_STOREITEM_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
			}
			SCP<IStream> poCachedStreamSP;
			navostreaminfo oNSI;
			_init_navostreaminfo(oNSI);
			_get_cache()->StoreItem(m_IdFile,m_oFullPathServerString,m_oDescriptorArray.GetSize(),
				m_oDescriptorArray.GetData(),rnTransaction,&oNSI,&poCachedStreamSP.GetRawPointer());
			if(hr != S_OK)
			{
				ThrowNavoException2(ERCO_CACHEMAN_STOREITEM_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
			}
			if(poCachedStreamSP.PointsObject())
			{
				ULARGE_INTEGER ulInfinity;
				ulInfinity.QuadPart = MAXLONG;
				HRESULT hr = poStreamSP->CopyTo(poCachedStreamSP,ulInfinity,NULL,NULL);
				if(hr != S_OK)
				{
					ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
				}
				//rewind cached
				CStreamHolder(poCachedStreamSP).SeekToBegin();
				//and return cached - work will be on it
				poStreamSP = poCachedStreamSP;
			}
		}
	}
	return poStreamSP;
}

void CCacheUser__::_end_get_stream_and_auto_cache(long nTransaction,bool bOK)
{
	if(nTransaction != 0)
	{
		if(_get_cache().PointsObject())
		{
			HRESULT hr = _get_cache()->FinishTransaction(nTransaction,BYTE(bOK));
			if(hr != S_OK)
			{
				ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
			}
		}
	}
}


///----------------------------------------------------------------------------------------------
///----------------------------------------------------------------------------------------------

static long specialVT2SQLType(VARTYPE vt)
{
	switch(vt)
	{
	case VT_BSTR:
		return SQLT_CHAR0;
	case VT_I4:
		return SQLT_INT;
	case VT_I2:
		return SQLT_SMALL;
	case VT_CY:
		return SQLT_MONEY;
	case VT_DATE:
		return SQLT_DATE;
	default:

#ifdef _DEVELOPER_EDITION_
		{
			AfxMessageBox("Nieprawid³owy typ zmiennej przy budowaniu deskryptora pliku");
		}
#endif
		ASSERT(false);
		return SQLT_IGNORE;
	}
}


static void BuildDescriptor(DATE dtModDate,long nVarCount,long * pnVars,
	SCP<CPropertyProvider__> & rpoEnvironmentSP,CArray<BYTE,BYTE> & roDescriptorArray)
{
	//first pass - find length
	long nLength = sizeof(DATE);
	long iter = 0; 
	for(iter = 0; iter < nVarCount; iter ++)
	{
		CSmartOleVariant oSOV;
		if(rpoEnvironmentSP->SafeGetProp(pnVars[iter],oSOV))
		{
			ASSERT(specialVT2SQLType(oSOV.Type())!=SQLT_IGNORE);
			nLength += Variant2BinaryHelper(specialVT2SQLType(oSOV.Type()),oSOV);
		}
	}
	//second pass - put data
	roDescriptorArray.SetSize(nLength);
	PBYTE pcData = roDescriptorArray.GetData();
	for(iter = 0; iter < nVarCount; iter ++)
	{
		CSmartOleVariant oSOV;
		if(rpoEnvironmentSP->SafeGetProp(pnVars[iter],oSOV))
		{
			long nItemLength = Variant2BinaryHelper(specialVT2SQLType(oSOV.Type()),oSOV,pcData);
			pcData += nItemLength;
		}
	}
	*((DATE *)pcData) = dtModDate;
}

/////////////////////////////////////////////////////////////////////////////
// CCacheManagerUser
/////////////////////////////////////////////////////////////////////////////

CCacheManagerUser::CCacheManagerUser(
		LPCTSTR lpFullPathServer,
		SCP<ICachedData> & rpoCachedDataSP,
		SCP<IAppDBManager> & rpoAppDBManagerSP,
		SCP<CPropertyProvider__> & rpoEnvironmentHLISP,
		long IdFile) :
		CCacheUser__(rpoCachedDataSP,lpFullPathServer,IdFile),
		m_poCachedDataSP(rpoCachedDataSP),
		m_poAppDBManagerSP(rpoAppDBManagerSP),
		m_poEnvironmentHLISP(rpoEnvironmentHLISP)
{
	ASSERT(rpoAppDBManagerSP.PointsObject());
	ASSERT(m_poEnvironmentHLISP.PointsObject());	//without it caching wont occur (empty property set is OK).

	if(rpoCachedDataSP.PointsObject())
	{
		m_poMarshalled_CachedDataSP = rpoCachedDataSP.Marshal();
	}
	if(rpoAppDBManagerSP.PointsObject())
	{
		m_poMarshalled_AppDBManagerSP = rpoAppDBManagerSP.Marshal();
	}
	EnableAutomation();
}

CCacheManagerUser::~CCacheManagerUser()
{
}

SCP<IStream> CCacheManagerUser::GetFinalStream()
{
	SCP<IStreamProvider> poStreamProviderSP;
	poStreamProviderSP.QueryInterface(m_poAppDBManagerSP);
	SCP<IStream> poStreamSP;

	navostreaminfo oNSI;
	_init_navostreaminfo(oNSI);
	HRESULT hr = poStreamProviderSP->Get(m_IdFile,&poStreamSP.GetRawPointer(),&oNSI);
	if(hr != S_OK)
	{
		ThrowNavoException2(ERCO_CACHEMAN_GET_FILE_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
	}
	ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if(oNSI.m_bCompressed == '1')
	{
		poStreamSP = UncompressStream(poStreamSP);
	}
	return poStreamSP;
}

void CCacheManagerUser::OnInit()
{
	//always unmarshal due problems on NT4.0 
	{
		SCP<IAppDBManager>	poAppDBManagerSP = m_poAppDBManagerSP;	//keep object alive
		m_poAppDBManagerSP = 0;
		m_poAppDBManagerSP.UnMarshal(m_poMarshalled_AppDBManagerSP);
	}
	//always unmarshal due some other problems when a cache provider was marshalled.
	//When file cache is disabled there is no cached-data stream; attempting to
	//unmarshal a null stream fails with E_INVALIDARG before the real error is visible.
	if (m_poMarshalled_CachedDataSP.PointsObject())
	{
		SCP<ICachedData> poCachedDataSP = m_poCachedDataSP;	//to keep object alive
		m_poCachedDataSP = 0;
		m_poCachedDataSP.UnMarshal(m_poMarshalled_CachedDataSP);
	}
	else
	{
		m_poCachedDataSP = 0;
	}
}

void CCacheManagerUser::PrepareDescriptor()
{
	//get variable dependencies
	DATE dtModifDate;
	long nVarCount = 0;

	SAFEARRAY * pSAVars = NULL;
	long * pnVars = NULL;

	HRESULT hr = S_OK;

	CRemoteFreeHolder oRFHName(pnVars);

	if(IsNXMTransport())
	{
		hr = m_poAppDBManagerSP->GetItemInfo2(APPDBMAN_ITEMINFO_VARDEP | APPDBMAN_ITEMINFO_MODIFDATE,
			m_IdFile, &dtModifDate, &nVarCount, &pSAVars);
	}
	else
	{
		hr = m_poAppDBManagerSP->GetItemInfo(APPDBMAN_ITEMINFO_VARDEP | APPDBMAN_ITEMINFO_MODIFDATE,
			m_IdFile, &dtModifDate, &nVarCount, &pnVars);
	}
	if(hr != S_OK)
	{
		ThrowNavoException2(ERCO_CACHEMAN_GETVARDEP_FAILED, IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
	}
	
	//build descriptor, empty array is <null> descriptor
	if(m_poEnvironmentHLISP.PointsObject())
	{
		if(IsNXMTransport())
		{
			void * pData;
			SafeArrayAccessData(pSAVars, &pData);
			BuildDescriptor(dtModifDate, nVarCount,(long*)pData, m_poEnvironmentHLISP, m_oDescriptorArray);
			SafeArrayUnaccessData(pSAVars);
		}
		else
		{
			BuildDescriptor(dtModifDate, nVarCount, pnVars, m_poEnvironmentHLISP, m_oDescriptorArray);
		}
	}
	
	if(IsNXMTransport())
	{
		oRFHName.Release();
		SafeArrayDestroy(pSAVars);
	}
}


