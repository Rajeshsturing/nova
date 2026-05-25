/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CBRManager - backup/restore manager
	interfaces
*/
#include "stdafx.h"
#include "resource.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"	//our interface related utils
#include "FileSet.h"
#include "BRManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------
//	IBackupRestore
//----------------------------------------------------------------

STDMETHODIMP CBRManager::XBackupRestore::Begin(
	IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,ISupplyInfo * pSupplyInfo)
{
	METHOD_PROLOGUE(CBRManager, BackupRestore)
	
	ALL_TRY
	{
		pThis->ReadDescription(pParameters);
		pThis->m_eBackupRestoreState = brs_datastream;
		pThis->m_poBackupRestoreONSinkUnknownSP = NewSCP(pONSinkUnknown,true);
		pThis->m_poBackupRestoreSupplyInfoSP = NewSCP(pSupplyInfo,true);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestore::End()
{
	METHOD_PROLOGUE(CBRManager, BackupRestore)
	
	ALL_TRY
	{
		pThis->m_poBackupRestoreONSinkUnknownSP = 0;
		pThis->m_poBackupRestoreSupplyInfoSP = 0;
		pThis->m_poBackupRestoreInfoStreamSP = 0;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestore::
	GetBackupStream(LPSTR * ppStreamName,LPSTR * ppStreamInfo,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CBRManager, BackupRestore)
	
	ALL_TRY
	{
		//dobry zwyczaj zeruj outpointery
		*ppStreamName = NULL;
		*ppStreamInfo = NULL;
		*ppDataStream = NULL;

		if(pThis->m_eBackupRestoreState == brs_datastream)
		{
			HRESULT hr = pThis->m_xBackupRestoreManager.GetBackupStream(ppDataStream,
				&pThis->m_poBackupRestoreInfoStreamSP.GetRawPointer(),
				pThis->m_poBackupRestoreONSinkUnknownSP,
				pThis->m_poBackupRestoreSupplyInfoSP);
			CString oStreamNameString;
			
			oStreamNameString = "CBRManager::XBackupRestore::to_do: stream name";

			*ppStreamName = (LPTSTR) ::NdrOleAllocate(oStreamNameString.GetLength() + 1);
			strcpy((LPTSTR) *ppStreamName,oStreamNameString);
			
			if(hr != S_OK)
			{
				return hr;
			}
			pThis->m_eBackupRestoreState = brs_infostream;
			return S_OK;
		}
		if(pThis->m_eBackupRestoreState == brs_infostream)
		{
			pThis->m_eBackupRestoreState = brs_end;
			*ppDataStream = pThis->m_poBackupRestoreInfoStreamSP.Detach();
			return S_OK;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_FALSE;
}

STDMETHODIMP CBRManager::XBackupRestore::
	SetRestoreStream(LPSTR  ppStreamName,LPSTR  ppStreamInfo,IStream * ppDataStream,__int64 i64Length)
{
	METHOD_PROLOGUE(CBRManager, BackupRestore)
	
	ALL_TRY
	{
		if(pThis->m_eBackupRestoreState == brs_datastream)
		{
			//skopiuj data stream do temp'a 
			ASSERT(pThis->m_poBackupRestoreInfoStreamSP.PointsNull());
			pThis->m_poBackupRestoreInfoStreamSP = CreateTempFileStream();
			ULARGE_INTEGER ulLength;
			ulLength.QuadPart = i64Length;
			HRESULT hr = IStream_CopyTo(ppDataStream,pThis->m_poBackupRestoreInfoStreamSP,ulLength);
			if(hr != S_OK)
			{
				return hr;
			}

			//przewiñ kopiê
			CStreamHolder(pThis->m_poBackupRestoreInfoStreamSP).SeekToBegin();
			pThis->m_eBackupRestoreState = brs_infostream;
		}
		else if(pThis->m_eBackupRestoreState == brs_infostream)
		{
			pThis->m_eBackupRestoreState = brs_end;
			return pThis->m_xBackupRestoreManager.SetRestoreStream(
				pThis->m_poBackupRestoreInfoStreamSP,
				ppDataStream,
				pThis->m_poBackupRestoreONSinkUnknownSP,
				pThis->m_poBackupRestoreSupplyInfoSP);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestore::
	GetStat(long * pTotalCount,long * pTotalSize)
{
	METHOD_PROLOGUE(CBRManager, BackupRestore)
	
	ALL_TRY
	{
		* pTotalCount = -1;
		* pTotalSize = -1;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

//----------------------------------------------------------------
///// IBackupRestoreManager implementation
//----------------------------------------------------------------

STDMETHODIMP CBRManager::XBackupRestoreManager::
	GetBackupStream(IStream ** ppDataStream,IStream ** ppInfoStream,
		IUnknown * pONSinkUnknown,IUnknown * pISupplyInfo)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	HRESULT hr = S_OK;
	ALL_TRY
	{
		if(pThis->m_oBRSetArray.GetSize() == 0)
		{
			return ERROR_EMPTY;
		}
		pThis->m_poNotificationSinkSP.SafeQueryInterface(pONSinkUnknown);
		pThis->m_poSupplyInfoSP.SafeQueryInterface(pISupplyInfo);
		pThis->m_oProvidersArray.RemoveAll();
		pThis->m_oReadingState.Reset();
		pThis->m_oReadingState.m_poInfoStreamSP = CreateTempFileStream();

		SCP<IStream> poOutputStreamSP = NewSCP(&pThis->m_xStream,true);
		* ppDataStream = poOutputStreamSP.Detach();
		SCP<IStream> poOutputInfoStreamSP = pThis->m_oReadingState.m_poInfoStreamSP;
		* ppInfoStream = poOutputInfoStreamSP.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return hr;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	SetRestoreStream(IStream * pDataStream,IStream * pInfoStream,
		IUnknown * pONSinkUnknown,IUnknown * pISupplyInfo)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	HRESULT hr = S_OK;
	ALL_TRY
	{
		pThis->m_poNotificationSinkSP.SafeQueryInterface(pONSinkUnknown);
		pThis->m_poSupplyInfoSP.SafeQueryInterface(pISupplyInfo);
		
		SCP<IStream> poInputStreamSP = NewSCP(pDataStream,true);
		ASSERT(poInputStreamSP);
		SCP<IStream> poInputInfoStreamSP = NewSCP(pInfoStream,true);
		ASSERT(poInputInfoStreamSP);
		
		hr = pThis->_DoRestore(poInputStreamSP,poInputInfoStreamSP);
	}
	ALL_CATCH(const CNavoException & roNavoException)
	{
		pThis->GetErrorStorage() += roNavoException;
		hr = DISP_E_EXCEPTION;
	}
	
	pThis->m_poNotificationSinkSP = 0;
	pThis->m_poSupplyInfoSP = 0;
	return hr;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	NewBrSet(IDispatch ** ppDispatch)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		*ppDispatch = pThis->NewBRSetAUTO();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	AddBrSet(IDispatch * pDispatch)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		pThis->AddBRSetAUTO(pDispatch);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	RemoveAllBrSets()
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		pThis->m_oBRSetArray.RemoveAll();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	_GetNewEnum(IUnknown ** ppUnknown)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		*ppUnknown = pThis->GetNewEnumAUTO();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	SetProp(long nProp,VARIANT vValue)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		CSmartOleVariant oSOV(vValue);
		pThis->_SetProperty(nProp,oSOV);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CBRManager::XBackupRestoreManager::
	GetProp(long nProp,VARIANT * pvValue)
{
	METHOD_PROLOGUE(CBRManager, BackupRestoreManager)
	
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		pThis->_GetProperty(nProp,oSOV);
		*pvValue = oSOV.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


//----------------------------------------------------------------
//			IStream implementatoin
//----------------------------------------------------------------

STDMETHODIMP CBRManager::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		return pThis->_ReadBackup(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Seek(LARGE_INTEGER, unsigned long,ULARGE_INTEGER *)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Write(const void *, unsigned long , unsigned long *)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		return E_FAIL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	SetSize(ULARGE_INTEGER)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Commit(unsigned long)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Revert()
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Stat(STATSTG *, unsigned long)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}


STDMETHODIMP CBRManager::XStream::
	Clone(IStream **)
{
	METHOD_PROLOGUE(CBRManager, Stream)
	
	ALL_TRY
	{
		ASSERT(false);
		return E_NOTIMPL;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}
