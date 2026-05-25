/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Clipboard / Drag Drop Support (core classes)
*/
#include "StdAfx.h"
#include "..\include\clipboardsupport.h"

CNavoOleDataSource::cfCodeAndName CNavoOleDataSource::_gm_CodesAndNames[] = 
{
	{ 0, _T("HTML Format") },				//NCF_HTML
	{ 0, _T("Rich Text Format") },			//NCF_RTF
	{ 0, _T("NAVO Enterprise Format") },	//NCF_NAVO2001
	{ CF_TEXT, _T("Text Format") }			//NCF_TEXT == CF_TEXT
};


void CNavoOleDataSource::CacheMemoryStreamData(CLIPFORMAT cfFormat,SCP<IStream> & rpoStreamSP)
{
	STGMEDIUM	stgMedium;
	FORMATETC	formatEtc;
	HGLOBAL hGlobal = (HGLOBAL)NULL;
	HRESULT hr = ::GetHGlobalFromStream(rpoStreamSP.Get(),&hGlobal);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_NAVOOLEDATASRC_BADSTREAM,IDPAGE_NOTAVAILABLE,
			SCODE_To_String(hr));
	}
	ASSERT(hGlobal != (HGLOBAL)NULL);
	memset(&stgMedium,0,sizeof(stgMedium));

	stgMedium.tymed		= TYMED_HGLOBAL;
	stgMedium.hGlobal	= hGlobal;
	
	formatEtc.cfFormat	= cfFormat;
	formatEtc.ptd		= NULL;
	formatEtc.dwAspect  = DVASPECT_CONTENT;
	formatEtc.lindex	= -1;
	formatEtc.tymed		= TYMED_HGLOBAL;
	
	CacheData(cfFormat,&stgMedium,&formatEtc);
	rpoStreamSP.Detach();
}

UINT CNavoOleDataSource::GetClipBoardFormat(navoCF eNAVOCF)
{
	if(_gm_CodesAndNames[ eNAVOCF ].m_code == 0)
	{
		_gm_CodesAndNames[ eNAVOCF].m_code = ::RegisterClipboardFormat(_gm_CodesAndNames[ eNAVOCF ].m_lpName);
		if(_gm_CodesAndNames[ eNAVOCF].m_code == 0)
		{
			ThrowNavoException1(ERCO_NAVOOLEDATASRC_CANTREGFORMAT,IDPAGE_NOTAVAILABLE,
				GetLastError_To_String(::GetLastError()));
		}
	}
	ASSERT(0 != _gm_CodesAndNames[ eNAVOCF].m_code);
	return _gm_CodesAndNames[ eNAVOCF].m_code;
}

