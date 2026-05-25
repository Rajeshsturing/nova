/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Precompiled data manager
*/
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "prepobj.h"
#include "precompileddata.h"

CPreprocessedDataCacheImpl::CPreprocessedDataCacheImpl()
{
}

CPreprocessedDataCacheImpl::~CPreprocessedDataCacheImpl()
{
}

void CPreprocessedDataCacheImpl::Add(long nFileId, SCP<IStream> poStreamSP)
{
	CSimpleLock oSimpleLock(m_oMapAccessCS);
	m_oPrecompiledMap[ nFileId ] = poStreamSP;
}

SCP<IStream> CPreprocessedDataCacheImpl::Get(long nFileId) const
{
	SCP<IStream> poStreamSP;
	CSimpleLock oSimpleLock(m_oMapAccessCS);
	m_oPrecompiledMap.Lookup(nFileId,poStreamSP);
	
	return poStreamSP;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
void CPrecompiledData::read(SCP<IStream> poReadStreamSP)
{
	m_oNamesArray.RemoveAll();
	m_oValuesArray.RemoveAll();

	CStreamHolder oSH(poReadStreamSP);
	oSH.SeekToBegin();
	
	long nCount = 0;
	oSH.Read(&nCount,sizeof(nCount));
	m_oNamesArray.SetSize(nCount);
	m_oValuesArray.SetSize(nCount);
	m_oTypeArray.SetSize(nCount);

	while(nCount --)
	{
		m_oNamesArray[nCount] = oSH.ReadPascalString();
		m_oValuesArray[nCount] = oSH.ReadPascalString();
		
		TCHAR cType;
		oSH.Read(&cType,sizeof(TCHAR));
		m_oTypeArray[nCount] = cType;
	}
}

void CPrecompiledData::write(SCP<IStream> poWriteStreamSP)
{
	CStreamHolder oSH(poWriteStreamSP);
	
	long nCount = m_oNamesArray.GetSize();
	oSH.Write(&nCount,sizeof(nCount));

	while(nCount --)
	{
		oSH.WritePascalString(m_oNamesArray[nCount]);
		oSH.WritePascalString(m_oValuesArray[nCount]);
		oSH.Write(&m_oTypeArray[nCount],sizeof(TCHAR));
	}
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

IMPLEMENT_DYNCREATE(CPreprocessedDataCache, CCmdTarget)

CPreprocessedDataCache::CPreprocessedDataCache():
	m_poImplementationSP(NewSCP(new CPreprocessedDataCacheImpl()))
{
	EnableAutomation();
	AfxOleLockApp();
}

CPreprocessedDataCache::~CPreprocessedDataCache()
{
	m_poImplementationSP = 0;
	AfxOleUnlockApp();
}


BEGIN_INTERFACE_MAP(CPreprocessedDataCache, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CPreprocessedDataCache, IID_IPreprocessedDataCache, PreprocessedDataCache)
END_INTERFACE_MAP()

// {188cb189-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CPreprocessedDataCache, "navoprep.datacache", 0x188cb189,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

DELEGATE_UNKNOWN_INTERFACE(CPreprocessedDataCache, PreprocessedDataCache)


STDMETHODIMP CPreprocessedDataCache::XPreprocessedDataCache::
	GetData(long IdFile,IStream ** ppDataStream)
{
	METHOD_PROLOGUE(CPreprocessedDataCache, PreprocessedDataCache)
	
	ALL_TRY
	{
		* ppDataStream = NULL;	//zeroing out pointers, keeps OLE healthy

		SCP<IStream> poStreamSP = pThis->m_poImplementationSP->Get(IdFile);
		
		if(poStreamSP.PointsNull())
		{
			return S_FALSE;
		}
		else
		{
			* ppDataStream = poStreamSP.Detach();
			return S_OK;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}


STDMETHODIMP CPreprocessedDataCache::XPreprocessedDataCache::
	PutData(long IdFile,IStream * pDataStream)
{
	METHOD_PROLOGUE(CPreprocessedDataCache, PreprocessedDataCache)
	
	ALL_TRY
	{
		pThis->m_poImplementationSP->Add(IdFile,NewSCP(pDataStream,true));
		return S_OK;
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
}




