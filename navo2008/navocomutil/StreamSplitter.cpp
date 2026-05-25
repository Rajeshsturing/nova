// StreamSplitter.cpp: implementation of the CStreamSplitter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "StreamSplitter.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStreamSplitterObject::CStreamSplitterObject()
{
	//wo: EnableAutomation();	- zobacz w dokumentacji
	//wo: 	AfxOleLockApp();    - zobacz w dokumentacji
}

CStreamSplitterObject::~CStreamSplitterObject()
{
	//wo: 	AfxOleUnlockApp(); - zobacz w dokumentacji
}
//--------------------------------------------
IMPLEMENT_DYNCREATE(CStreamSplitterObject, CCmdTarget)
// {188cb176-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CStreamSplitterObject, "navocomutil.splitter",0x188cb176,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(CStreamSplitterObject, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CStreamSplitterObject, IID_IStreamSplitter, StreamSplitter)
	INTERFACE_PART(CStreamSplitterObject, IID_IStream, Stream)
	INTERFACE_PART(CStreamSplitterObject, IID_ISupplyInfo, SupplyInfo)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CStreamSplitterObject, StreamSplitter)  
DELEGATE_UNKNOWN_INTERFACE(CStreamSplitterObject, Stream)
DELEGATE_UNKNOWN_INTERFACE(CStreamSplitterObject, SupplyInfo)

STDMETHODIMP CStreamSplitterObject::XStreamSplitter::Join(ISupplyInfo *pSupplyInfo)
{
	METHOD_PROLOGUE(CStreamSplitterObject, StreamSplitter)
/*	
	ALL_TRY
	{
		//wo: ASSERT(pSupplyInfo != NULL); albo lepiej
		//if(pSupplyInfo == NULL)
		//{
		//	return E_POINTER;
		//}

		//wo: m_poSupplyInfoSP = NewSCP(pSupplyInfo,true);


		pThis->m_poInputStreamSP = NewSCP(pStream,true);
		pThis->__Init();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);  */
	return E_NOTIMPL;
}

STDMETHODIMP CStreamSplitterObject::XStreamSplitter::Split(IStream * pInputStream, ISupplyInfo* pSupplyInfo)
{
	METHOD_PROLOGUE(CStreamSplitterObject, StreamSplitter)
/*	
	ALL_TRY
	{
		pThis->m_nFilterType = nType;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}
//------------------------------------
STDMETHODIMP CStreamSplitterObject::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return pThis->__Read(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Seek(LARGE_INTEGER liOffset, unsigned long lOrigin,ULARGE_INTEGER * pliNewPointer)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		//jeœli nie by³o nic czytane i chcemy siê przesunaæ na pocz¹tek to jest to OK
		if(!pThis->m_bWasRead)	
		{
			if(liOffset.QuadPart == 0 && lOrigin == STREAM_SEEK_SET)
			{
				if (pliNewPointer)
				{
					pliNewPointer->QuadPart = 0;
				}
				return S_OK;
			}
		}
		ASSERT(false);
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Write(const void *, unsigned long , unsigned long *)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		ASSERT(false);
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/* ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Revert()
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Stat(STATSTG *, unsigned long)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XStream::
	Clone(IStream **)
{
	METHOD_PROLOGUE(CStreamSplitterObject, Stream)
	
/*	ALL_TRY
	{
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION); */
	return E_NOTIMPL;
}


STDMETHODIMP CStreamSplitterObject::XSupplyInfo ::AskForData (long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer)
{
		METHOD_PROLOGUE(CStreamSplitterObject, SupplyInfo)

		
//		return pThis->Impl_AskForData(nInfoType,lpDescription,varQuestion,pvarAnswer);
	return E_NOTIMPL;
}
