/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectFile
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobjcache.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"
#include "navoobjcoor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CNEO_filestorage::CNEO_filestorage(CNEO_global_cache * poGlobalCache,
		long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew) : 
	m_poGlobalCache(poGlobalCache),
	m_ParentTypeId(nParentTypeId),
	m_IdParent(nParentIdObj),
	m_nOuterFieldNr(nOuterFieldNr),
	m_dwUserRef(0),
	m_eNeedSave(ns_no),
	m_eUserModif(um_no),
	m_bStreamModified(false),
	m_bParentMarkDel(false),
	m_bParentIsNew(bParentIsNew)
{
	_init_navostreaminfo(m_oNSI);
}

CNEO_filestorage::~CNEO_filestorage()
{
}

void CNEO_filestorage::OnFinalRelease()
{
	if(m_poGlobalCache)
	{
		m_poGlobalCache->OnNEO_filestorage_FinalRelease(this);
	}
	else
	{
		delete this;
	}
}

void CNEO_filestorage::_set_stream_info(const navostreaminfo & roNSI)
{
	_copy_navostreaminfo(roNSI,m_oNSI);
}

void CNEO_filestorage::_copy_from(const CNEO_filestorage & roFileStorage)
{
	ASSERT(m_ParentTypeId	== roFileStorage.m_ParentTypeId);
	ASSERT(m_IdParent		== roFileStorage.m_IdParent);
	ASSERT(m_nOuterFieldNr	== roFileStorage.m_nOuterFieldNr);

	m_eNeedSave		= roFileStorage.m_eNeedSave;
	m_eUserModif	= roFileStorage.m_eUserModif;
	m_bStreamModified = roFileStorage.m_bStreamModified;
	Attach(const_cast<CNEO_filestorage&>(roFileStorage).m_poXMLStreamSP);
	_copy_navostreaminfo(roFileStorage.m_oNSI,m_oNSI);
}

void CNEO_filestorage::OnFirstWrite()
{
	if(!m_bStreamModified)
	{
		/*
			SCP<IStream> poCopyStreamSP = CreateTempFileStream();
			ULARGE_INTEGER ulInfinity;
			ulInfinity.QuadPart = MAXLONG;
			CStreamHolder(m_poXMLStreamSP).SeekToBegin();
			HRESULT hr = m_poXMLStreamSP->CopyTo(poCopyStreamSP,ulInfinity,NULL,NULL);
			ASSERT(hr == S_OK);
			CStreamHolder(poCopyStreamSP).SeekToBegin();
			Attach(poCopyStreamSP);
		*/
		m_bStreamModified = true;
		m_eNeedSave = ns_yes;
		m_eUserModif = um_yes;
	}
}

void CNEO_filestorage::OnStreamAttachDetach()
{
	m_bStreamModified = true;
	m_eNeedSave = ns_yes;
	m_eUserModif = um_yes;
}

bool CNEO_filestorage::full_is_usermodified()
{
	ASSERT(m_eUserModif == um_unknown);
	if(full_is_needsave())
	{
		m_eUserModif = um_yes;
		return true;
	}
	else
	{
		m_eUserModif = um_no;
		return false;
	}
}

bool CNEO_filestorage::full_is_needsave()
{
	ASSERT(m_eNeedSave == ns_unknown);
	if(m_bParentMarkDel)
	{
		if(m_bParentIsNew)
		{
			m_eNeedSave = ns_no;
			return false;
		}
		else
		{
			m_eNeedSave = ns_yes;
			return true;
		}
	}
	if(m_bStreamModified)
	{
		m_eNeedSave = ns_yes;
		return true;
	}
	m_eNeedSave = ns_no;
	return false;
}

void CNEO_filestorage::_postprocess()
{
	m_eNeedSave = ns_no;
	m_eUserModif = um_no;
	m_bParentMarkDel = false;
	m_bStreamModified = false;
	m_bParentIsNew = false;
}

SCP<CNEO_filestorage> CNEO_filestorage::clone()
{
	SCP<CNEO_filestorage> poFileStorageSP = 
		NewSCP(new CNEO_filestorage(NULL,GetParentTypeid(),GetParentId(),GetOuterFieldNr(),m_bParentIsNew));

	poFileStorageSP->_copy_from(*this);
	poFileStorageSP->m_bParentMarkDel = m_bParentMarkDel;
	return poFileStorageSP;
}

void CNEO_filestorage::_writebinary(CArray<transblobinfo,transblobinfo &> & roBlobData)
{
	if(m_bParentIsNew)
	{
		if(m_bParentMarkDel || IsEmptyAUTO())
		{
			return;	//ignore
		}
	}
	else
	{
		if(m_bParentMarkDel || IsEmptyAUTO())
		{
			//delete
			transblobinfo oTBI;
			_copy_navostreaminfo(m_oNSI,oTBI.m_oNSI);
			oTBI.m_IdParent = GetParentId();
			oTBI.m_IdMapping= _compose_filemapping_id(GetParentTypeid(),GetOuterFieldNr());
			oTBI.m_pIStream = NULL;
			roBlobData.Add(oTBI);

#ifdef _DEVELOPER_EDITION_
			if(GetDebugOptions().IsTraceAutoCalls())
			{
				CDebuggerCallHolder oDCH;
				oDCH++.StoreMsg("DB:FILEDEL [%d:%d]=%d\n",GetParentTypeid(),GetParentId(),
					_compose_filemapping_id(GetParentTypeid(),GetOuterFieldNr()));
			}
#endif
			return;
		}
	}
	{
		//write
		transblobinfo oTBI;
		_copy_navostreaminfo(m_oNSI,oTBI.m_oNSI);
		oTBI.m_IdParent = GetParentId();
		oTBI.m_IdMapping= _compose_filemapping_id(GetParentTypeid(),GetOuterFieldNr());
		oTBI.m_pIStream = GetStream().Get();
		roBlobData.Add(oTBI);
	}

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		CDebuggerCallHolder oDCH;
		oDCH++.StoreMsg("DB:FILESAVE [%d:%d]=%d\n",GetParentTypeid(),GetParentId(),
			_compose_filemapping_id(GetParentTypeid(),GetOuterFieldNr()));
	}
#endif
}






CNEO_fileuser::CNEO_fileuser(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_filestorage> & rpoFileStorageSP,bool bReadOnly) :
	m_poTransSP(rpoTransSP),
	m_poFileStorageSP(rpoFileStorageSP),
	m_bReadOnlyStorage(bReadOnly)
{
	EnableAutomation();
	m_poFileStorageSP->AddRef_User();
}

CNEO_fileuser::~CNEO_fileuser()
{
	m_poFileStorageSP->Release_User();
}

SCP<CNEO_fileuser> CNEO_fileuser::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetFileUser = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetFileUser);
	CNEO_fileuser * poFileUser = dynamic_cast<CNEO_fileuser*>(poCmdTargetFileUser);
	ASSERT(poFileUser);
	return NewSCP(poFileUser,true);
}

void CNEO_fileuser::OnFinalRelease()
{
	ASSERT(m_poTransSP.PointsObject());
	m_poTransSP->OnNEO_fileuser_FinalRelease(this);
	delete this;
}

void CNEO_fileuser::_raw_set_markdel(bool bMarkDel)
{
	ASSERT(_get_storage());
	_get_storage()->set_parent_mark_del(bMarkDel);
}

void CNEO_fileuser::_enable_changes()
{
}


BEGIN_INTERFACE_MAP(CNEO_fileuser, CCmdTargetInterface)
	INTERFACE_PART(CNEO_fileuser, IID_IDispatch, DynaDispatch)
	INTERFACE_PART(CNEO_fileuser, IID_IStream, Stream)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CNEO_fileuser, DynaDispatch)  
DELEGATE_UNKNOWN_INTERFACE(CNEO_fileuser, Stream)

//------------------------------------------------------------------------------------
//		IDispatch
//------------------------------------------------------------------------------------

STDMETHODIMP CNEO_fileuser::XDynaDispatch::GetTypeInfoCount(UINT* pCount)
{
	METHOD_PROLOGUE(CNEO_fileuser, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfoCount(pCount);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_fileuser::XDynaDispatch::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo ** ppTInfo)
{
	METHOD_PROLOGUE(CNEO_fileuser, DynaDispatch)
	
	ALL_TRY
	{
		return ((IDispatch*)&pThis->m_xDispatch)->GetTypeInfo(iTInfo,lcid,ppTInfo);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_fileuser::XDynaDispatch::
	GetIDsOfNames(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId)
{
	METHOD_PROLOGUE(CNEO_fileuser, DynaDispatch)
	
	ALL_TRY
	{
		HRESULT hr = pThis->_get_storage()->GetIDispatch(FALSE)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);
		if(hr == DISP_E_UNKNOWNNAME)
		{
			hr = ((IDispatch*)&pThis->m_xDispatch)->GetIDsOfNames(riid,rgszNames,cNames,lCid,rgDispId);
		}
		return hr;
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

STDMETHODIMP CNEO_fileuser::XDynaDispatch::
	Invoke(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError)
{
	METHOD_PROLOGUE(CNEO_fileuser, DynaDispatch)

	ALL_TRY
	{
		HRESULT hr = pThis->_get_storage()->GetIDispatch(FALSE)->Invoke(dispId,riid,lCid,wFlags,pDispParams,
				pVarResult,pExceptInfo,puArgError);
		if(hr == DISP_E_MEMBERNOTFOUND)
		{
			hr = ((IDispatch*)&pThis->m_xDispatch)->Invoke(dispId,riid,lCid,wFlags,pDispParams,
				pVarResult,pExceptInfo,puArgError);
		}
		return hr;
	}
	TOP_ALL_CATCH_AUTOMATION(pThis->_get_trans()->GetErrorStorage(),pExceptInfo);
	return S_OK;
}


//------------------------------------------------------------------------------------
//		IStream
//------------------------------------------------------------------------------------

STDMETHODIMP CNEO_fileuser::XStream::
	Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Read(pData,lLength,plBytesRead);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Seek(LARGE_INTEGER ulParam1, unsigned long lParam2,ULARGE_INTEGER * pulParam3)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Seek(ulParam1,lParam2,pulParam3);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Write(const void * pData, unsigned long lLength, unsigned long * plBytesWritten)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Write(pData,lLength,plBytesWritten);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	SetSize(ULARGE_INTEGER ulSize)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->SetSize(ulSize);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
		ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->CopyTo(pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Commit(unsigned long lParam1)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Commit(lParam1);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Revert()
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Revert();
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	LockRegion(ULARGE_INTEGER ulParam1, ULARGE_INTEGER ulParam2, unsigned long lParam3)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->LockRegion(ulParam1,ulParam2,lParam3);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	UnlockRegion(ULARGE_INTEGER ulParam1, ULARGE_INTEGER ulParam2, unsigned long lParam3)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)

	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->UnlockRegion(ulParam1,ulParam2,lParam3);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Stat(STATSTG * pStatStg, unsigned long nOptions)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Stat(pStatStg,nOptions);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CNEO_fileuser::XStream::
	Clone(IStream ** ppStream)
{
	METHOD_PROLOGUE(CNEO_fileuser, Stream)
	
	ALL_TRY
	{
		if(pThis->_get_storage().PointsNull())
		{
			return ERROR_INVALID_STATE;
		}
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(pThis->_get_storage());
		return poStreamSP->Clone(ppStream);
	}
	TOP_ALL_CATCH(pThis->_get_trans()->GetErrorStorage(),DISP_E_EXCEPTION);
}

//{{AFX_MSG_MAP(CNEO_fileuser)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CNEO_fileuser,CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CNEO_fileuser)
	DISP_PROPERTY_EX_ID(CNEO_fileuser, "ext", 200, GetExtAUTO, SetExtAUTO, VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


BSTR CNEO_fileuser::GetExtAUTO() 
{
	ALL_TRY
	{
		ASSERT(_get_storage().PointsObject());
		return _get_storage()->_get_ext().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CNEO_fileuser::SetExtAUTO(LPCTSTR lpszNewValue) 
{
	ALL_TRY
	{
		ASSERT(_get_storage().PointsObject());
		_enable_changes();
		_get_storage()->_set_ext(lpszNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}









	
