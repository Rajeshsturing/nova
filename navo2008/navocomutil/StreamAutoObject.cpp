/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
	CStreamAutoObject
		obiekt implementuje IStream manipulowalny przed automation
*/


#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "StreamAutoObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStreamAutoObject

CStreamAutoObject::CStreamAutoObject() :
	m_eLastOperation(LAOP_UNKNOWN)
{
	AfxOleLockApp();
	EnableAutomation();
}

CStreamAutoObject::CStreamAutoObject(CStreamAutoObject & roStreamAutoObject) :
	m_poXMLStreamSP(roStreamAutoObject.m_poXMLStreamSP),
	m_eLastOperation(roStreamAutoObject.m_eLastOperation),
	m_bFirstWrite(true)
{
	AfxOleLockApp();
	EnableAutomation();
}

CStreamAutoObject::~CStreamAutoObject()
{
	AfxOleUnlockApp();
}

SCP<CStreamAutoObject> CStreamAutoObject::FromIDispatch(LPDISPATCH lpDispatch)
{
	if(lpDispatch == NULL)	//VB nothing
	{
		return SCP<CStreamAutoObject>();
	}
	else
	{
		CCmdTarget * poCmdTargetSAO = CCmdTarget::FromIDispatch(lpDispatch);
		ASSERT(poCmdTargetSAO);
		CStreamAutoObject * poSAO = dynamic_cast<CStreamAutoObject *>(poCmdTargetSAO);
		ASSERT(poSAO);
		return NewSCP(poSAO,true);
	}
}

void CStreamAutoObject::_rewind_to_begin()
{
	if(m_poXMLStreamSP.PointsObject())
	{
		CStreamHolder oSH(m_poXMLStreamSP);
		oSH.SeekToBegin();
		m_eLastOperation = LAOP_UNKNOWN;
	}
}

void CStreamAutoObject::_rewind_to_end()
{
	if(m_poXMLStreamSP.PointsObject())
	{
		CStreamHolder oSH(m_poXMLStreamSP);
		oSH.SeekToEnd();
		m_eLastOperation = LAOP_UNKNOWN;
	}
}

BEGIN_MESSAGE_MAP(CStreamAutoObject, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CStreamAutoObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CStreamAutoObject, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CStreamAutoObject)
	DISP_FUNCTION_ID(CStreamAutoObject, "save", 100,SaveAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CStreamAutoObject, "attach", 101, AttachAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION_ID(CStreamAutoObject, "write", 102, WriteAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CStreamAutoObject, "read", 103, ReadAUTO, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CStreamAutoObject, "getstream", 104, GetStreamAUTO, VT_VARIANT, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "isempty", 105, IsEmptyAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "empty", 106, EmptyAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "getstring", 107, GetAsStringAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "getlength", 108, GetCurrentLengthAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "copyto", 109, CopyToAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION_ID(CStreamAutoObject, "savecoded", 110,SaveCodedAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CStreamAutoObject, "attachcoded", 111, AttachCodedAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION_ID(CStreamAutoObject, "rewind", 112, RewindAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "attachtemp", 113, AttachTempAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CStreamAutoObject, "seektoend", 114, SeekToEndAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IStreamAutoObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9CB41DDF-7098-4E5B-978A-4C05220726DF}
static const IID IID_IStreamAutoObject =
{ 0x9cb41ddf, 0x7098, 0x4e5b, { 0x97, 0x8a, 0x4c, 0x5, 0x22, 0x7, 0x26, 0xdf } };

IMPLEMENT_DYNCREATE(CStreamAutoObject, CCmdTargetInterface)
// {188cb16e-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CStreamAutoObject, "navocomutil.streamobj",0x188cb16e,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(CStreamAutoObject, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CStreamAutoObject, IID_IStreamAutoObject, Dispatch)
	INTERFACE_PART(CStreamAutoObject, IID_IStream, Stream)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CStreamAutoObject, Stream)

/////////////////////////////////////////////////////////////////////////////
// CStreamAutoObject message handlers

VARIANT CStreamAutoObject::GetStreamAUTO() 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(m_poXMLStreamSP);
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::_save_to_url(LPCTSTR lpURL,bool bCoded)
{
	if(m_poXMLStreamSP.PointsObject())
	{
		CStreamHolder(m_poXMLStreamSP).SeekToBegin();
		SaveStreamToFile(m_poXMLStreamSP,lpURL,bCoded);
		m_eLastOperation = LAOP_UNKNOWN;
	}
	else
	{
		ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
	}
}

void CStreamAutoObject::SaveCodedAUTO(LPCTSTR lpURL)
{
	ALL_TRY
	{
		_save_to_url(lpURL,true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStreamAutoObject::SaveAUTO(LPCTSTR lpURL) 
{
	ALL_TRY
	{
		_save_to_url(lpURL,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CStreamAutoObject::AttachCodedAUTO(const VARIANT FAR& varStreamOrURL)
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(varStreamOrURL);
		switch(oSOV.Type())
		{
		case VT_BSTR:
		{
			CString oURLString(oSOV.GetBStr());
			Attach(OpenFileStream_Read(oURLString,true));
			OnStreamAttachDetach();
		}
		break;
		case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
			{
				VARIANT * pVariant = oSOV.GetVariantRef().pvarVal;
				ASSERT(pVariant);
				AttachCodedAUTO(*pVariant);	//Uwaga! wywo³uje siebie ale ju¿ bez byRef
			}
		break;
		default:
			ASSERT(false);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::AttachAUTO(const VARIANT FAR& varStreamOrURL) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(varStreamOrURL);
		switch(oSOV.Type())
		{
		case VT_BSTR:
		{
			CString oURLString(oSOV.GetBStr());
			if(0 == _tcsnicmp(oURLString,_T("url:"),4))			//4=="url:"
			{
				Attach(OpenURLStream(LPCTSTR(oURLString)+4));
			}
			else
			{
				Attach(OpenFileStream(oURLString,false,
					GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,OPEN_ALWAYS));
			}
			OnStreamAttachDetach();
		}
		break;
		case VT_DISPATCH:
		{
			SCP<IStream> poInputStreamSP;
			poInputStreamSP.QueryInterface(oSOV.GetDispatch());
			Attach(poInputStreamSP);
			OnStreamAttachDetach();
		}
		break;
		case VT_UNKNOWN:
		{
			Attach(oSOV.GetStream());
			OnStreamAttachDetach();
		}
		break;
		case (VT_ARRAY | VT_UI1) :
		{
			Attach(CreateStreamInMemory());
			COleSafeArray oSafeArray;
			oSafeArray.Attach(oSOV.GetVariantRef());
			CSafeArrayAccessHolder<TCHAR> oSAAH(oSafeArray);
			WriteAUTO(oSAAH.GetData());
			OnStreamAttachDetach();
		}
		break;
		case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
			{
				VARIANT * pVariant = oSOV.GetVariantRef().pvarVal;
				ASSERT(pVariant);
				AttachAUTO(*pVariant);	//Uwaga! wywo³uje siebie ale ju¿ bez byRef
			}
			break;
		default:
			ASSERT(false);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::CopyToAUTO(const VARIANT FAR& varStreamOrURL)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;
		SCP<IStream> poDestStreamSP = CreateFileStream_Write_On_SOV(
			reinterpret_cast<const CSmartOleVariant&>(varStreamOrURL),poFileRemoverSP);
		if(m_poXMLStreamSP.PointsObject() && poDestStreamSP.PointsObject())
		{
			CStreamHolder(m_poXMLStreamSP).SeekToBegin();
			ULARGE_INTEGER ulInfinity;
			ulInfinity.QuadPart = MAXLONG;
			HRESULT hr = IStream_CopyTo(m_poXMLStreamSP.Get(),poDestStreamSP.Get(),ulInfinity);
			ASSERT(hr == S_OK);
			if(poFileRemoverSP.PointsObject())
			{
				poFileRemoverSP->DontRemove();
			}
			m_eLastOperation = LAOP_WRITE;
		}
		else
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::WriteAUTO(LPCTSTR strData) 
{
	ALL_TRY
	{
		if(m_bFirstWrite)
		{
			OnFirstWrite();
			m_bFirstWrite = false;
		}
		if(m_poXMLStreamSP.PointsObject())
		{
			CStreamHolder oSH(m_poXMLStreamSP);
			if(m_eLastOperation != LAOP_WRITE)
			{
				oSH.SeekToEnd();
				m_eLastOperation = LAOP_WRITE;
			}
			oSH.WriteString(strData);
		}
		else
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL CStreamAutoObject::IsEmptyAUTO() 
{
	if(m_poXMLStreamSP.PointsNull())
	{
		return TRUE;
	}
	return (GetStreamSize(m_poXMLStreamSP.Get()) == 0);
}

void CStreamAutoObject::EmptyAUTO() 
{
	ALL_TRY
	{
		m_poXMLStreamSP = 0;
		OnStreamAttachDetach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CStreamAutoObject::GetAsStringAUTO() 
{
	CString strResult;
	if(m_poXMLStreamSP.PointsObject())
	{
		long nStreamSize = GetStreamSize(m_poXMLStreamSP);
		_rewind_to_begin();
		CStreamHolder oSH(m_poXMLStreamSP);
		oSH.Read(strResult.GetBuffer(nStreamSize),nStreamSize);
		strResult.ReleaseBuffer(nStreamSize);
	}
	return strResult.AllocSysString();
}

BSTR CStreamAutoObject::ReadAUTO(long nBytes)
{
	CString strResult;
	if(m_poXMLStreamSP.PointsObject())
	{
		strResult.ReleaseBuffer(CStreamHolder(m_poXMLStreamSP).Read(strResult.GetBuffer(nBytes),nBytes));
	}
	return strResult.AllocSysString();
}

long CStreamAutoObject::GetCurrentLengthAUTO()
{
	if(m_poXMLStreamSP.PointsObject())
	{
		CStreamHolder oSH(m_poXMLStreamSP);
		return oSH.Seek(0,STREAM_SEEK_CUR);
	}
	else
	{
		return 0;
	}
}

void CStreamAutoObject::RewindAUTO()
{
	ALL_TRY
	{
		_rewind_to_begin();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::SeekToEndAUTO()
{
	ALL_TRY
	{
		_rewind_to_end();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CStreamAutoObject::AttachTempAUTO()
{
	ALL_TRY
	{
		Attach(CreateTempFileStream());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
//------------------------------------------------------------------------------------
//		IStream
//------------------------------------------------------------------------------------

STDMETHODIMP CStreamAutoObject::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		pThis->m_eLastOperation = LAOP_READ;
		return pThis->m_poXMLStreamSP->Read(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Seek(LARGE_INTEGER ulParam1, unsigned long lParam2,ULARGE_INTEGER * pulParam3)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		pThis->m_eLastOperation = LAOP_UNKNOWN;
		return pThis->m_poXMLStreamSP->Seek(ulParam1,lParam2,pulParam3);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Write(const void * pData, unsigned long lLength, unsigned long * plBytesWritten)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_bFirstWrite)
		{
			pThis->OnFirstWrite();
			pThis->m_bFirstWrite = false;
		}
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		pThis->m_eLastOperation = LAOP_WRITE;

		return pThis->m_poXMLStreamSP->Write(pData,lLength,plBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	SetSize(ULARGE_INTEGER ulSize)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(ulSize.QuadPart == __int64(0))
		{
			pThis->OnStreamAttachDetach();
		}
		if(pThis->m_bFirstWrite)
		{
			pThis->OnFirstWrite();
			pThis->m_bFirstWrite = false;
		}
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		pThis->m_eLastOperation = LAOP_UNKNOWN;
		return pThis->m_poXMLStreamSP->SetSize(ulSize);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		pThis->m_eLastOperation = LAOP_UNKNOWN;	//przesuwa seek ptr
		return pThis->m_poXMLStreamSP->CopyTo(pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Commit(unsigned long lParam1)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->Commit(lParam1);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Revert()
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->Revert();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	LockRegion(ULARGE_INTEGER ulParam1, ULARGE_INTEGER ulParam2, unsigned long lParam3)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->LockRegion(ulParam1,ulParam2,lParam3);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	UnlockRegion(ULARGE_INTEGER ulParam1, ULARGE_INTEGER ulParam2, unsigned long lParam3)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->UnlockRegion(ulParam1,ulParam2,lParam3);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Stat(STATSTG * pStatStg, unsigned long nOptions)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->Stat(pStatStg,nOptions);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamAutoObject::XStream::
	Clone(IStream ** ppStream)
{
	METHOD_PROLOGUE(CStreamAutoObject, Stream)
	
	ALL_TRY
	{
		if(pThis->m_poXMLStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_STRM_OBJ_NO_STREAM, IDPAGE_NOTAVAILABLE);
		}
		return pThis->m_poXMLStreamSP->Clone(ppStream);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//				Stream filter object
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CStreamFilterObject, CCmdTarget)
// {188cb16a-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CStreamFilterObject, "navocomutil.streamfilter",0x188cb16a,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(CStreamFilterObject, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CStreamFilterObject, IID_IStreamFilter, StreamFilter)
	INTERFACE_PART(CStreamFilterObject, IID_IStream, Stream)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CStreamFilterObject, StreamFilter)  
DELEGATE_UNKNOWN_INTERFACE(CStreamFilterObject, Stream)

STDMETHODIMP CStreamFilterObject::XStreamFilter::AttachInput(IStream *pStream)
{
	METHOD_PROLOGUE(CStreamFilterObject, StreamFilter)
	
	ALL_TRY
	{
		pThis->m_poInputStreamSP = NewSCP(pStream,true);
		pThis->__Init();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CStreamFilterObject::XStreamFilter::SetParam(long nType)
{
	METHOD_PROLOGUE(CStreamFilterObject, StreamFilter)
	
	ALL_TRY
	{
		pThis->m_nFilterType = nType;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

STDMETHODIMP CStreamFilterObject::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		return pThis->__Read(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	Seek(LARGE_INTEGER liOffset, unsigned long lOrigin,ULARGE_INTEGER * pliNewPointer)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
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
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CStreamFilterObject::XStream::
	Write(const void *, unsigned long , unsigned long *)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	Revert()
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CStreamFilterObject::XStream::
	Stat(STATSTG * pParam1, unsigned long ulParam2)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(pThis->m_poInputStreamSP.PointsObject());
		return pThis->m_poInputStreamSP->Stat(pParam1,ulParam2);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CStreamFilterObject::XStream::
	Clone(IStream **)
{
	METHOD_PROLOGUE(CStreamFilterObject, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}

void CStreamFilterObject::__Init()
{
	m_bInsideHeader = true;
	m_nDataLen = 0;
	m_nFirstUnread = 0;
	m_bWasRead = false;
#ifdef _DEBUG
	_debug_m_nTotalUncompressedBytesRead = 0;
	_debug_m_nTotalCompressedBytesRead = 0;
#endif
}

HRESULT CStreamFilterObject::__Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	ASSERT(m_poInputStreamSP.PointsObject());
	m_bWasRead = true;
	switch(m_nFilterType)
	{
	case SFT_STRIP_STARTING_WHITESPACE:
	{
		return __read_strip_starting_whitespace(pData,lLength,plBytesRead);
	}
	break;
	case SFT_COMPRESS:
	{
		return __read_compress(pData,lLength,plBytesRead);
	}
	break;
	case SFT_UNCOMPRESS:
	{
		return __read_uncompress(pData,lLength,plBytesRead);
	}
	break;
	case SFT_BASE64ENCODE:
	{
		return __read_base64encode(pData,lLength,plBytesRead);
	}
	break;
	case SFT_BASE64DECODE:
	{
		return __read_base64decode(pData,lLength,plBytesRead);
	}
	break;
	default:
		ASSERT(false);
	}
	return E_INVALIDARG;
}


HRESULT CStreamFilterObject::__read_strip_starting_whitespace(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	BYTE * pcData = (BYTE *) pData;
	unsigned long lBytesRead = 0;
	while(m_bInsideHeader)
	{
		CArray<char,char> oBufferArray;
		oBufferArray.SetSize(lLength);
		HRESULT hr = m_poInputStreamSP->Read(oBufferArray.GetData(),lLength,&lBytesRead);
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			if(hr == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_poInputStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,
					ERCO_STRM_FLTR_SSW_READ_FAIL,IDPAGE_NOTAVAILABLE);
			}
			return hr;
		}
		unsigned long iter = 0; 
		while((iter < lBytesRead) && 
			(IsSpace(oBufferArray[iter]) || IsWhite(oBufferArray[iter])))
		{
			iter++;
		}
		m_bInsideHeader = (iter == lBytesRead - 1);
		if(!m_bInsideHeader)	//skopiuj koñcówkê
		{
			ASSERT(lBytesRead > iter);
			memcpy(pcData,oBufferArray.GetData()+iter,lBytesRead - iter);
			pcData += lBytesRead - iter;
			lLength -= lBytesRead - iter;
			lBytesRead -= iter;

		}
	}

	//po prostu kopiuj
	unsigned long lBytesRead2 = 0;
	HRESULT hr = m_poInputStreamSP->Read(pcData,lLength,&lBytesRead2);
	* plBytesRead = lBytesRead + lBytesRead2;
	return hr;
}

HRESULT CStreamFilterObject::__read_compress(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	unsigned long lBytesRead = 0;
	BYTE * pcData = (BYTE *) pData;
	while(lLength > m_nDataLen - m_nFirstUnread)
	{
		//read buffer contents
		unsigned long nChunkSize = m_nDataLen - m_nFirstUnread;
		if(nChunkSize != 0)
		{
			memcpy(pcData,m_oBuffer+m_nFirstUnread,nChunkSize);
			pcData += nChunkSize;
			lLength -= nChunkSize;
			m_nFirstUnread = m_nDataLen;
			lBytesRead += nChunkSize;
		}
		//fill buffer from source
		BYTE oSrcBuffer[ COMPRESSION_WINDOW_SIZE ];
		unsigned long nInputDataRead = 0;
		HRESULT hr = m_poInputStreamSP->Read(oSrcBuffer,COMPRESSION_WINDOW_SIZE,&nInputDataRead);
		ASSERT(nInputDataRead <= COMPRESSION_WINDOW_SIZE);
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			if(hr == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_poInputStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,ERCO_STRM_FLTR_COMPRESS_READ_FAIL,IDPAGE_NOTAVAILABLE);
			}
			return hr;
		}
		if(nInputDataRead == 0)		//no more data in input
		{
			lLength = 0;
			break;
		}
		m_nFirstUnread = 0;
		//compress buffer
		m_nDataLen = TOTAL_COMPRESSION_BUFFER_SIZE - sizeof(unsigned long);
		packbuffer(m_oBuffer + sizeof(unsigned long),&m_nDataLen,oSrcBuffer,nInputDataRead);
#ifdef _DEBUG
		if(m_nDataLen > COMPRESSION_WINDOW_SIZE)
		{
			TRACE1("pack: negative compression %d\n",m_nDataLen-COMPRESSION_WINDOW_SIZE);
		}
#endif
		*(unsigned long*)m_oBuffer = m_nDataLen;
		m_nDataLen += sizeof(unsigned long);
	}
	if(lLength != 0)
	{
		memcpy(pcData,m_oBuffer+m_nFirstUnread,lLength);
		m_nFirstUnread += lLength;
		lBytesRead += lLength;
	}
	ASSERT(m_nFirstUnread <= m_nDataLen);
	* plBytesRead = lBytesRead;
	return S_OK;
}

HRESULT CStreamFilterObject::__read_uncompress(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	unsigned long lBytesRead = 0;
	BYTE * pcData = (BYTE *) pData;
	while(lLength > m_nDataLen - m_nFirstUnread)
	{
		//read buffer contents
		unsigned long nChunkSize = m_nDataLen - m_nFirstUnread;
		if(nChunkSize != 0)
		{
			memcpy(pcData,m_oBuffer+m_nFirstUnread,nChunkSize);
			pcData += nChunkSize;
			lLength -= nChunkSize;
			m_nFirstUnread = m_nDataLen;
			lBytesRead += nChunkSize;
		}
		//fill buffer from source
		BYTE oSrcBuffer[ TOTAL_COMPRESSION_BUFFER_SIZE ];	//for case of "negative" compression
		unsigned long nInputDataRead = 0;
		unsigned long nPacketSize = 0;
			//read part length
		HRESULT hr = m_poInputStreamSP->Read((void*) &nPacketSize,sizeof(unsigned long),&nInputDataRead);
#ifdef _DEBUG
		_debug_m_nTotalCompressedBytesRead += sizeof(unsigned long);
#endif
		ASSERT(nInputDataRead <= sizeof(unsigned long));
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			if(hr == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_poInputStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,ERCO_STRM_FLTR_UNCOMPRESS_READ_FAIL,IDPAGE_NOTAVAILABLE);
			}
			return hr;
		}
		if(nInputDataRead == 0)		//no more data in input
		{
			lLength = 0;
			break;
		}
			//read data
		
		ASSERT(nPacketSize <= TOTAL_COMPRESSION_BUFFER_SIZE);
		hr = m_poInputStreamSP->Read(oSrcBuffer,nPacketSize,&nInputDataRead);
#ifdef _DEBUG
		_debug_m_nTotalCompressedBytesRead += nPacketSize;
#endif
		ASSERT(nInputDataRead == nPacketSize);	//musi siê udaæ
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			return hr;
		}

		m_nFirstUnread = 0;
		//compress buffer
		m_nDataLen = TOTAL_COMPRESSION_BUFFER_SIZE;
#ifdef _DEBUG
		if(nPacketSize > COMPRESSION_WINDOW_SIZE)
		{
			TRACE1("unpack: negative compression %d\n",nPacketSize-COMPRESSION_WINDOW_SIZE);
		}
#endif
		unpackbuffer(m_oBuffer,&m_nDataLen,oSrcBuffer,nInputDataRead);
	}
	if(lLength != 0)
	{
		memcpy(pcData,m_oBuffer+m_nFirstUnread,lLength);
		m_nFirstUnread += lLength;
		lBytesRead += lLength;
	}
	ASSERT(m_nFirstUnread <= m_nDataLen);
	* plBytesRead = lBytesRead;
#ifdef _DEBUG
	_debug_m_nTotalUncompressedBytesRead += lBytesRead;
#endif
	return S_OK;
}

/*
	zgodnie ze specyfikacj¹ Base64, ka¿da linia powinna mieæ max 76 znaków po zakodowaniu + \r\n
	linia krótsza (ostatnia) powinna mieæ padding znakami =

	masze kodowanie koduje jedn¹ liniê, zatem:
	76 / 4 bajty(zakodowane) * 3 bajty (binarne) = 57 i tyle znaków czytamy za jednym zamachem - 1 
	(na przeczytan¹ d³ugoœæ, która te¿ idzie do zakodowania). struktura bufora:
	byte = d³ugoœæ
	0-56 binary do zakodowania
*/

HRESULT CStreamFilterObject::__read_base64encode(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	unsigned long lBytesRead = 0;
	BYTE * pcData = (BYTE *) pData;
	while(lLength > m_nDataLen - m_nFirstUnread)
	{
		//read buffer contents
		unsigned long nChunkSize = m_nDataLen - m_nFirstUnread;
		if(nChunkSize != 0)
		{
			memcpy(pcData,m_oBuffer+m_nFirstUnread,nChunkSize);
			pcData += nChunkSize;
			lLength -= nChunkSize;
			m_nFirstUnread = m_nDataLen;
			lBytesRead += nChunkSize;
		}
		//fill buffer from source
		/*
		
		*/
		BYTE oSrcBuffer[ COMPRESSION_WINDOW_SIZE ];
		unsigned long nInputDataRead = 0;
		HRESULT hr = m_poInputStreamSP->Read(oSrcBuffer+1,56,&nInputDataRead);
		ASSERT(nInputDataRead <= COMPRESSION_WINDOW_SIZE);
		ASSERT(nInputDataRead <= 56);
		oSrcBuffer[0] = char(nInputDataRead);
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			if(hr == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_poInputStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,ERCO_STRM_FLTR_BASE64EN_READ_FAIL,IDPAGE_NOTAVAILABLE);
			}
			return hr;
		}
		if(nInputDataRead == 0)		//no more data in input
		{
			lLength = 0;
			break;
		}
		m_nFirstUnread = 0;
		//encode buffer
		CBase64CoDec oB64CD(oSrcBuffer,nInputDataRead+1);
		strcpy((char*)m_oBuffer,oB64CD.Encoded());
		m_nDataLen = strlen((char*)m_oBuffer);
		m_oBuffer[m_nDataLen++] = '\n';
		m_oBuffer[m_nDataLen] = '\0';
		ASSERT(m_nDataLen <= 77);
	}
	if(lLength != 0)
	{
		memcpy(pcData,m_oBuffer+m_nFirstUnread,lLength);
		m_nFirstUnread += lLength;
		lBytesRead += lLength;
	}
	ASSERT(m_nFirstUnread <= m_nDataLen);
	* plBytesRead = lBytesRead;
	return S_OK;
}

HRESULT CStreamFilterObject::__read_base64decode(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	unsigned long lBytesRead = 0;
	BYTE * pcData = (BYTE *) pData;
	while(lLength > m_nDataLen - m_nFirstUnread)
	{
		//read buffer contents
		unsigned long nChunkSize = m_nDataLen - m_nFirstUnread;
		if(nChunkSize != 0)
		{
			memcpy(pcData,m_oBuffer+m_nFirstUnread,nChunkSize);
			pcData += nChunkSize;
			lLength -= nChunkSize;
			m_nFirstUnread = m_nDataLen;
			lBytesRead += nChunkSize;
		}
		//fill buffer from source
		/*
		
		*/
		BYTE oSrcBuffer[ COMPRESSION_WINDOW_SIZE ];
		unsigned long nInputDataRead = 0;
		HRESULT hr = m_poInputStreamSP->Read(oSrcBuffer,77,&nInputDataRead);
		ASSERT(nInputDataRead <= COMPRESSION_WINDOW_SIZE);
		if(hr != S_OK)
		{
			* plBytesRead = lBytesRead;
			if(hr == DISP_E_EXCEPTION)
			{
				CNavoException oNavoException;
				GetErrorInfoFromInterface(m_poInputStreamSP,oNavoException);
				ContinueThrowNavoException(oNavoException,ERCO_STRM_FLTR_BASE64DE_READ_FAIL,IDPAGE_NOTAVAILABLE);
			}
			return hr;
		}
		if(nInputDataRead == 0)		//no more data in input
		{
			lLength = 0;
			break;
		}
		m_nFirstUnread = 0;
		//encode buffer
		oSrcBuffer[nInputDataRead] = '\0';
		CBase64CoDec oB64CD((const char*)oSrcBuffer);
		LPCVOID pEncodedBuffer = oB64CD.Decoded(m_nDataLen);
		ASSERT(m_nDataLen <= 57);
		DWORD nTrueLen = ((const char*)pEncodedBuffer)[0];
		ASSERT(nTrueLen <= m_nDataLen);
		m_nDataLen = nTrueLen;
		memcpy(m_oBuffer,((const char*)pEncodedBuffer)+1,m_nDataLen);
	}
	if(lLength != 0)
	{
		memcpy(pcData,m_oBuffer+m_nFirstUnread,lLength);
		m_nFirstUnread += lLength;
		lBytesRead += lLength;
	}
	ASSERT(m_nFirstUnread <= m_nDataLen);
	* plBytesRead = lBytesRead;
	return S_OK;
}
