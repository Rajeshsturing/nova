/*
	NAVO Sp. z o.o. (2000)
	
	NAVO Enterprise

	class:
		CAppDBManager - APPLICATION database manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\stdobjdefparser.h"
#include "..\navodef\DefinitionManager.h"
#include "AppDBManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void __CopyVarDepFromPrepToFileInfo(long IdFile,SCP<IPreprocessor> & rpoPreprocessorSP,
	SCP<CAppDBFileInfo> & rpoFileInfoSP);

void CAppDBManager::__CommitStdObjDef()
{
	ASSERT(__IsPersistentDataLoaded());

	SCP<ISimpleEnumId> poSimpleEnumStreamSP;

	HRESULT hr = m_xAppDBManager.EnumFileGroup(_T("dataobj"),&poSimpleEnumStreamSP.GetRawPointer());
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_APPDB_ENUM_DATAOBJ, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
	}
	
	SCP<IPreprocessor> poPreprocessorSP;
	poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor,CLSCTX_INPROC);
	SCP<IStreamProvider> poStreamProviderSP = NewSCP(&m_xStreamProvider,true);
	SCP<CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
	SCP<CDefinitionManager> poDefinitionManagerSP = NewSCP(new CDefinitionManager());

	VERIFY(S_OK == poPreprocessorSP->Init(poHLISP->GetIDispatch(FALSE),poStreamProviderSP,NULL));

	while(hr == S_OK)
	{
		long IdFile;
		hr = poSimpleEnumStreamSP->Next(&IdFile);
		if(hr != S_OK)
		{
			break;
		}
		HRESULT hr = poPreprocessorSP->PreprocessFile(IdFile,BYTE(false));
		if(hr != S_OK)
		{
			ThrowNavoException2(ERCO_APPDB_PREP_FAILED, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String(hr));
		}
		
		SCP<IStream> pOutputStreamSP;
		pOutputStreamSP.QueryInterface(poPreprocessorSP);
		
		SCP<INavoErrorInfo> poNavoErrorInfoSP;
		if(!ParseStdObjDefinition(pOutputStreamSP,poDefinitionManagerSP,poNavoErrorInfoSP))
		{
			CNavoException oNavoException;
			GetErrorInfoFromInterface(poNavoErrorInfoSP,oNavoException);
			ContinueThrowNavoException1(oNavoException,
				ERCO_APPDB_ERROR_IN_STDOBJDEF,IDPAGE_NOTAVAILABLE,IdFile);
		}
		
		//get info: var dependencies
		SCP<CAppDBFileInfo> poFileInfoSP;
		if(!m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
		{
			ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
		}
		__CopyVarDepFromPrepToFileInfo(IdFile,poPreprocessorSP,poFileInfoSP);

		poPreprocessorSP->Close();
		TRACE1("processed %d \n",IdFile);
	}
	poDefinitionManagerSP->CommitStdObjDef();
	CString oFileNameString;
	GenerateFileName(IDPAGE_CLASSDEF,oFileNameString);
	
	poDefinitionManagerSP->SaveTo(CreateFileStream_Write(oFileNameString).Get());
	TRACE0("finished creating stdobjdef\n");
}

