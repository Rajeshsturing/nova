/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		Preprocessor object
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\symbnameres.h"
#include "prepobj.h"
#include "preprocessor.h"
#include "precompileddata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreprocessorObj

IMPLEMENT_DYNCREATE(CPreprocessorObj, CCmdTarget)

CPreprocessorObj::CPreprocessorObj()
{
	EnableAutomation();
	AfxOleLockApp();
}

CPreprocessorObj::~CPreprocessorObj()
{
	AfxOleUnlockApp();
}

void CPreprocessorObj::OnFinalRelease()
{
	CCmdTargetWithErrorInfo::OnFinalRelease();
}

BEGIN_INTERFACE_MAP(CPreprocessorObj, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CPreprocessorObj, IID_INavoErrorInfo, NavoErrorInfo)
	INTERFACE_PART(CPreprocessorObj, IID_IPreprocessor, Preprocessor)
	INTERFACE_PART(CPreprocessorObj, IID_IStream, Stream)
END_INTERFACE_MAP()

// {188cb166-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CPreprocessorObj, "navoprep.preprocessor", 0x188cb166,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

DELEGATE_UNKNOWN_INTERFACE(CPreprocessorObj, Stream)
DELEGATE_UNKNOWN_INTERFACE(CPreprocessorObj, Preprocessor)
DELEGATE_UNKNOWN_INTERFACE(CPreprocessorObj, NavoErrorInfo)  

#ifdef _DEBUG
DWORD _debug_last_prepr_init_time = 0;
#endif

STDMETHODIMP CPreprocessorObj::XPreprocessor::Init(IDispatch * pEnvironmentDisp,
	IStreamProvider * pStreamProvider,IPreprocessedDataCache * pDataCache)
{
	METHOD_PROLOGUE(CPreprocessorObj, Preprocessor)
	
	ALL_TRY
	{
#ifdef _DEBUG
		_debug_last_prepr_init_time = ::GetTickCount();
#endif

		if(pThis->m_poPreprocessorSP.PointsObject())
		{
			ASSERT(false);		//po to aby programista, który nie sprawdza rezultatu wiedzia³
			return ERROR_INVALID_STATE;
		}
		pThis->m_poEnvironmentSP = CPropertyProvider__::FromIDispatch(pEnvironmentDisp);
		pThis->m_poStreamProviderSP = NewSCP(pStreamProvider,true);
		pThis->m_poPreprocessedDataCacheSP = NewSCP(pDataCache,true);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CPreprocessorObj::XPreprocessor::PreprocessFile(long IdFile,BYTE bParseMode)
{
	METHOD_PROLOGUE(CPreprocessorObj, Preprocessor)
	
	ALL_TRY
	{
		if(pThis->m_poPreprocessorSP.PointsObject())
		{
			ASSERT(false);		//po to aby programista, który nie sprawdza rezultatu wiedzia³
			return ERROR_INVALID_STATE;
		}
		if(!pThis->m_poStreamProviderSP.PointsObject())
		{
			ASSERT(false);		//po to aby programista, który nie sprawdza rezultatu wiedzia³
			return ERROR_INVALID_STATE;
		}
		if(!pThis->m_poEnvironmentSP.PointsObject())
		{
			ASSERT(false);		//po to aby programista, który nie sprawdza rezultatu wiedzia³
			return ERROR_INVALID_STATE;
		}

		pThis->m_poPreprocessorSP = NewSCP(new CPreprocesor(IdFile,
				pThis->m_poStreamProviderSP,pThis->m_poEnvironmentSP,
				pThis->m_poPreprocessedDataCacheSP,bParseMode != '\0'));
		pThis->m_nReadPos	= 0;
		pThis->m_nWritePos	= 0;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CPreprocessorObj::XPreprocessor::GetVarDependencies(long * pnVarCntr,long ** ppVarNr)
{
	METHOD_PROLOGUE(CPreprocessorObj, Preprocessor)
	
	ALL_TRY
	{
		if(pThis->m_poPreprocessorSP.PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		*pnVarCntr = pThis->m_poPreprocessorSP->GetVarDependecyCount();
		*ppVarNr = (long*) ::NdrOleAllocate(*pnVarCntr * sizeof(long));
		pThis->m_poPreprocessorSP->GetVarDependencies(*ppVarNr);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CPreprocessorObj::XPreprocessor::GetIncludeDependencies(long * pnVarCntr,long ** ppVarNr)
{
	METHOD_PROLOGUE(CPreprocessorObj, Preprocessor)
	
	ALL_TRY
	{
		if(pThis->m_poPreprocessorSP.PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		*pnVarCntr = pThis->m_poPreprocessorSP->GetIncludeDependecyCount();
		*ppVarNr = (long*) ::NdrOleAllocate(*pnVarCntr * sizeof(long));
		pThis->m_poPreprocessorSP->GetIncludeDependencies(*ppVarNr);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CPreprocessorObj::XPreprocessor::Close()
{
	METHOD_PROLOGUE(CPreprocessorObj, Preprocessor)
	
	ALL_TRY
	{
		pThis->m_poPreprocessorSP = 0;
#ifdef _DEBUG
//		TRACE1("preprocessing time %d\n",::GetTickCount() - _debug_last_prepr_init_time);
#endif
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CPreprocessorObj::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poPreprocessorSP.PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		if(plBytesRead)
		{
			*plBytesRead = 0;
		}
		TCHAR * pcData = (TCHAR*) pData;
		//copy already read data
		ASSERT(pThis->m_nWritePos >= pThis->m_nReadPos);
		unsigned long nActualDataLen = min(lLength,pThis->m_nWritePos - pThis->m_nReadPos);
		if(nActualDataLen > 0)
		{
			memcpy(pcData,pThis->m_oOutputBuffer + pThis->m_nReadPos,nActualDataLen);
//			TRACE1("%s",CString(pcData,nActualDataLen));
			pcData += nActualDataLen;
			lLength -= nActualDataLen;
			pThis->m_nReadPos += nActualDataLen;
			if(plBytesRead)
			{
				*plBytesRead += nActualDataLen;
			}
		}
		CArray<TCHAR,TCHAR&> oOutputBufferArray;
		oOutputBufferArray.SetSize(1024);
		while(lLength > 0)
		{
			ASSERT(pThis->m_nWritePos == pThis->m_nReadPos);	//przeczyta³ wszystko
			//pull enough data
			CArrayWriter<TCHAR> oOutputWriter(oOutputBufferArray);
			bool bEOF = !pThis->m_poPreprocessorSP->DoChunk(oOutputWriter);

			//copy direct to output
			nActualDataLen = min((unsigned long)oOutputWriter.CharactersWritten(),lLength);
			if(nActualDataLen > 0)
			{
				memcpy(pcData,oOutputBufferArray.GetData(),nActualDataLen);
				pcData += nActualDataLen;
				lLength -= nActualDataLen;
				if(plBytesRead)
				{
					*plBytesRead += nActualDataLen;
				}
			}
			//copy rest to buffer for later
			pThis->m_nWritePos = oOutputWriter.CharactersWritten() - nActualDataLen;
			if(pThis->m_nWritePos > 0)
			{
				if(pThis->m_nWritePos > PREP_OUTPUT_BUFFER_SIZE)
				{
					ThrowNavoException(ERCO_PREP_LINE_TOO_LONG,IDPAGE_NOTAVAILABLE);
				}
				memcpy(pThis->m_oOutputBuffer,oOutputBufferArray.GetData() + nActualDataLen,pThis->m_nWritePos);
			}
			pThis->m_nReadPos = 0;
			if(bEOF)
			{
				break;
			}
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CPreprocessorObj::XStream::
	Seek(LARGE_INTEGER, unsigned long,ULARGE_INTEGER *)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	Write(const void *, unsigned long , unsigned long *)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	Revert()
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	Stat(STATSTG *, unsigned long)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessorObj::XStream::
	Clone(IStream **)
{
	METHOD_PROLOGUE(CPreprocessorObj, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


