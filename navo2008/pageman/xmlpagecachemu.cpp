/*
	NAVO Sp. z o.o. (2001)
	NAVO Enterprise
	class:
		CXMLPageCacheManagerUser - CacheManageUser dla stron XML (preprocessor i strip_white_space)
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\navoscript\CacheManagerUser.h"
#include "xmlpagecachemu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _PREPROCESS_ON_SERVER_
SCP<IStream> CPageCacheManagerUser::GetFinalStream()
{
	ASSERT(m_poEnvironmentHLISP.PointsObject());
	SCP<IStream> poStreamSP;
	
#ifdef _PREPROCESS_ON_SERVER_
	
	navostreaminfo oNSI;
	CString oEnvString;
	m_poEnvironmentHLISP->get_canonical_string(oEnvString);
	
	TRACE("env=[%s]\n",oEnvString);

	HRESULT hr = m_poAppDBManagerSP->GetFinalStream(m_IdFile,(LPCSTR)oEnvString,&poStreamSP.GetRawPointer(),&oNSI);
	if(hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poPreprocessorSP,oNavoException);
		ContinueThrowNavoException2(oNavoException,ERCO_PAGECACHE_PREPROCESS_FAILED,IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
	}
	ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if(oNSI.m_bCompressed == '1')
	{
		poStreamSP = UncompressStream(poStreamSP);
	}
#else
	ASSERT(m_poPreprocessorSP.PointsNull());

	SCP<IStreamProvider> poStreamProviderSP;
	poStreamProviderSP.QueryInterface(m_poAppDBManagerSP);
	
	m_poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor,CLSCTX_INPROC);
		
	VERIFY(S_OK == m_poPreprocessorSP->Init(m_poEnvironmentHLISP->GetIDispatch(FALSE),poStreamProviderSP,m_poPDC_SP));
	HRESULT hr = m_poPreprocessorSP->PreprocessFile(m_IdFile,BYTE(false));
	if(hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_poPreprocessorSP,oNavoException);
		ContinueThrowNavoException2(oNavoException,ERCO_PAGECACHE_PREPROCESS_FAILED,IDPAGE_NOTAVAILABLE, m_IdFile,SCODE_To_String(hr));
	}
	poStreamSP.QueryInterface(m_poPreprocessorSP);
#endif

	return poStreamSP;
}
