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
#include "..\include\filerange.h"		//file range definitions
#include "_impnavobrman.h"
#include "AppDBManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------------
//-------------------------------- Interface ----------------------------------------
//-----------------------------------------------------------------------------------

STDMETHODIMP CAppDBManager::XAppDBManager::Init(LPCTSTR lpAppName)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->Init(lpAppName);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::Close(BYTE bOK)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->Close(bOK != '\0');
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::SetOptions(long nOptions)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		if(nOptions & UNIOPTIONS_COMPRESS_TRAFFIC_TO_CLIENT)
		{
			pThis->m_bCompressTrafficToClient = true;
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::Upload(long IdFile,IStream * pStream,LPCTSTR pcExtension)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->Upload(IdFile,pStream,pcExtension);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::Delete(long IdFile)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->Delete(IdFile);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::CreateApp(LPCTSTR lpAppName,LPCTSTR lpRootDirectory,long nKey)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->CreateStructures(lpAppName,lpRootDirectory,nKey);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::DropApp(LPCTSTR lpAppName)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	
	ALL_TRY
	{
		pThis->DropApp(lpAppName);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);
	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::Pack(VARIANT varDestNameOrStream,VARIANT varDestNameOrStreamInfo)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

	ALL_TRY
	{
		//to_do: umo¿liwiæ podawanie description z tego interface
		pThis->Pack(varDestNameOrStream,varDestNameOrStreamInfo,"");
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::Unpack(VARIANT varSrcNameOrStream,VARIANT varSrcNameOrStreamInfo)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

	ALL_TRY
	{
		pThis->Unpack(varSrcNameOrStream,varSrcNameOrStreamInfo);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::
	GetItemInfo2(long nInfoType,long IdFile, DATE * pModifDate,long * pnVarCntr, SAFEARRAY ** ppSAVarNr)
{
	long * ppVarNr;
	HRESULT hr = GetItemInfo(nInfoType, IdFile, pModifDate, pnVarCntr, &ppVarNr);
	
	if(hr == S_OK)
	{	
		*ppSAVarNr = SafeArrayCreateVector(VT_I4, 0, *pnVarCntr);
		void * pSafeArrayData;
		SafeArrayAccessData(*ppSAVarNr, &pSafeArrayData);
		memcpy(pSafeArrayData, ppVarNr, *pnVarCntr * sizeof(long));
		SafeArrayUnaccessData(*ppSAVarNr);
		NdrOleFree(ppVarNr);
	}
	return hr;
}

STDMETHODIMP CAppDBManager::XAppDBManager::
	GetItemInfo(long nInfoType,long IdFile,DATE * pModifDate,long * pnVarCntr,long ** ppVarNr)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

	ALL_TRY
	{
		*pnVarCntr = 0;
		*ppVarNr = NULL;

		if(nInfoType & APPDBMAN_ITEMINFO_VARDEP)
		{
			*pnVarCntr = pThis->GetVarDependencyCount(IdFile);
			*ppVarNr = (long*) ::NdrOleAllocate(*pnVarCntr * sizeof(long));
			pThis->GetVarDependencies(IdFile,*ppVarNr);
		}
		if((nInfoType & APPDBMAN_ITEMINFO_MODIFDATE) || 
		   (nInfoType & APPDBMAN_ITEMINFO_MODIFDATE_NO_DEP))
		{
			*pModifDate = pThis->GetModificationDate(IdFile,
				(nInfoType & APPDBMAN_ITEMINFO_MODIFDATE) == APPDBMAN_ITEMINFO_MODIFDATE);
		}
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::ChangeMode(long nNewMode)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

	ALL_TRY
	{
		pThis->ChangeMode(nNewMode);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::GetMode(long * pnMode)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

	ALL_TRY
	{
		*pnMode = pThis->GetMode();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XAppDBManager::GetFinalStream(long idFile,
	LPCSTR pcEnvironentStr,IStream ** pStream,navostreaminfo * poNSI)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poEnvHLISP = ReadHLIFromString(CString(pcEnvironentStr),SCP<CHyperLinkInfo>() );
		SCP<IDispatch> poEnvDispatchSP = poEnvHLISP->GetDispatchSP();

		_init_navostreaminfo(*poNSI);
		*pStream = NULL;		//a jak bêdzie wyj¹tek...
		SCP<IStream> poStreamSP = pThis->get_final_stream(idFile,poEnvDispatchSP);
		if(pThis->m_bCompressTrafficToClient)
		{
			poNSI->m_bCompressed = '1';
			poStreamSP = CompressStream(poStreamSP);
		}
		else
		{
			poNSI->m_bCompressed = '0';
		}
		*pStream = poStreamSP.Detach();

	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(),DISP_E_EXCEPTION);

	return S_OK;
}

//-----------------------------------------------------------------------------------
//-------------------------------- Implementation -----------------------------------
//-----------------------------------------------------------------------------------

LPCTSTR pcAppDBRootVal= _T("Root");
LPCTSTR pcAppDBVersionVal= _T("Version");

void CAppDBManager::_InitOnAppName(LPCTSTR lpAppName,CString & roRootDir,long & rnVersion)
{
	if(IsSetupAppName(lpAppName))
	{
		roRootDir = lpAppName + _tcslen(GetSetupAppName())+1;	//+1 for ':' sign
		rnVersion = APPVERSION_SETUP;
	}
	else
	{
		CString oString(GetApplicationsRegistryKeyName());
		CString oAppNameString(lpAppName);
		oString += "\\" + oAppNameString;
		LONG nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oString,pcAppDBRootVal,roRootDir);
		if(nResult != ERROR_SUCCESS)
		{
			roRootDir = ".\\";
		}
		else
		{
			CString oVersionString;
			nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oString,pcAppDBVersionVal,oVersionString);
			if(nResult != ERROR_SUCCESS)
			{
				rnVersion = APPVERSION_REGISTRY_ERROR;
			}
			else
			{
				rnVersion = _ttol(oVersionString);
				ASSERT(rnVersion > 0);
			}
		}
	}
}

void CAppDBManager::Init(LPCTSTR lpAppName)
{
	_InitOnAppName(lpAppName,m_oRootDirString,m_nAppVersion);
	EnsureEndingBackslash(m_oRootDirString);
	if(m_oRootDirString == ".\\")
	{
		ThrowNavoException1(ERCO_APPDB_MISSING_IN_REGISTRY,IDPAGE_NOTAVAILABLE,lpAppName);
	}
	__LoadPersistentData();		//when application is created, always exists fileinfo
}

void CAppDBManager::Close(bool bOK)
{
	__SavePersistentData();
}

void CAppDBManager::Upload(long IdFile,IStream * pStream,LPCTSTR pcExtension)
{
	if(IsUserMode())
	{
		ThrowNavoException1(ERCO_APPDB_FORBIDDENINUSERMODE, IDPAGE_NOTAVAILABLE, "UPLOAD");
	}
	//save
	{
		__LoadPersistentData();
		ASSERT(__IsPersistentDataLoaded());

		CString oString;
		GenerateFileName(IdFile,oString);
		CStreamHolder oSH(NewSCP(pStream,true));
		oSH.SeekToBegin();
		SaveStreamToFile(oSH.GetStream(),oString,false);
		m_oFileInfoMap[ IdFile ] = NewSCP(new CAppDBFileInfo());
		m_bFileInfoDirty = true;
	}
	//in programmers mode do immediate processing
	if(!IsUserMode())
	{
		__PreprocessFile(IdFile);
	}
}

void CAppDBManager::Delete(long IdFile)
{
	if(IsUserMode())
	{
		ThrowNavoException1(ERCO_APPDB_FORBIDDENINUSERMODE, IDPAGE_NOTAVAILABLE, "DELETE");
	}
	//to_do
	ASSERT(false);
	__LoadPersistentData();
	ASSERT(__IsPersistentDataLoaded());
	
	m_oFileInfoMap.RemoveKey(IdFile);
	m_bFileInfoDirty = true;
}

void CAppDBManager::CreateStructures(LPCTSTR lpAppName,LPCTSTR lpRootDir,long nVersion)
{
	CString oString(GetApplicationsRegistryKeyName());
	CString oAppNameString(lpAppName);
	oString += "\\" + oAppNameString;
	m_oRootDirString = lpRootDir;
	EnsureEndingBackslash(m_oRootDirString);
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oString,pcAppDBRootVal,lpRootDir);
	SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oString,pcAppDBVersionVal,Long2String(nVersion));

	NavoCreateDirectoryTree(lpRootDir);
	CString oRootString(lpRootDir);
	EnsureEndingBackslash(oRootString);

	NavoCreateDirectory(oRootString + GetHeadersSubDir());
	NavoCreateDirectory(oRootString + GetDataObjSubDir());
	NavoCreateDirectory(oRootString + GetDataObjLibSubDir());
	NavoCreateDirectory(oRootString + GetFormPageSubDir());
	NavoCreateDirectory(oRootString + GetMenuPageSubDir());
	NavoCreateDirectory(oRootString + GetRaportPageSubDir());
	NavoCreateDirectory(oRootString + GetUtilPageSubDir());
	NavoCreateDirectory(oRootString + GetStylePageSubDir());
	NavoCreateDirectory(oRootString + GetPicturePageSubDir());
	NavoCreateDirectory(oRootString + GetHelpPageSubDir());
	NavoCreateDirectory(oRootString + GetExtrasSubDir());
	
#ifdef  _DEVELOPER_EDITION_
	__ScanFileGroup(GetHeadersSubDir());
	__ScanFileGroup(GetDataObjSubDir());
	__ScanFileGroup(GetDataObjLibSubDir());
	__ScanFileGroup(GetFormPageSubDir());
	__ScanFileGroup(GetMenuPageSubDir());
	__ScanFileGroup(GetRaportPageSubDir());
	__ScanFileGroup(GetUtilPageSubDir());
	__ScanFileGroup(GetStylePageSubDir());
	__ScanFileGroup(GetPicturePageSubDir());
	__ScanFileGroup(GetHelpPageSubDir());
	__ScanFileGroup(GetExtrasSubDir());

	//--- for new structures add artifically
	{
		SCP<CAppDBFileInfo> poFileInfoSP = NewSCP( new CAppDBFileInfo());
		poFileInfoSP->set_file_name("L6.NXB");
		m_oFileInfoMap[ IDPAGE_FILEINFO ] = poFileInfoSP;
	}
	{
		SCP<CAppDBFileInfo> poFileInfoSP = NewSCP( new CAppDBFileInfo());
		poFileInfoSP->set_file_name("L10.NXB");
		m_oFileInfoMap[ IDPAGE_CLASSDEF ] = poFileInfoSP;
	}
#endif

	m_bFileInfoDirty = true;	//force save
	m_nAppVersion = nVersion;
	__SavePersistentData();
}

void CAppDBManager::DropApp(LPCTSTR lpAppName)
{
	_InitOnAppName(lpAppName,m_oRootDirString,m_nAppVersion);
	
	if(m_nAppVersion > 0)	//tylko gdy jest prawid³owa !!
	{
		EnsureEndingBackslash(m_oRootDirString);
		NavoRemoveDirectoryTree(m_oRootDirString);

		CString oString(GetApplicationsRegistryKeyName());
		EnsureEndingBackslash(oString);
		oString += lpAppName;
		VERIFY(RecursiveDeleteRegistryKey(HKEY_LOCAL_MACHINE,oString)==ERROR_SUCCESS);
	}
}


void CAppDBManager::Pack(const VARIANT FAR&  varDestination,const VARIANT FAR& varDestinationInfo,LPCTSTR lpDescription)
{
	ASSERT(GetRootDir());
	if(*GetRootDir() == '\0')
	{
		ThrowNavoException(ERCO_APPDB_NOT_INITED, IDPAGE_NOTAVAILABLE);
	}
	_DNAVOBRM oNAVOBRMCtrl;
	oNAVOBRMCtrl.CreateDispatch(_T("NAVOBRMCTRL.NAVOBRMCtrl.1"));
	//all together
	{
		IBRSet oBrSet(oNAVOBRMCtrl.newbrset());
		oBrSet.SetType(long(BRSET_FILEGROUP));
		oBrSet.SetRelative(TRUE);
		oBrSet.SetRecurse(TRUE);
		oBrSet.SetPath(GetRootDir());
		oBrSet.SetMask(_T("*.xml|*.h|*.nxb|*.pic|*.dat"));
		oNAVOBRMCtrl.addbrset(oBrSet);
	}

	oNAVOBRMCtrl.SetDatastream(varDestination);
	oNAVOBRMCtrl.SetInfostream(varDestinationInfo);
	oNAVOBRMCtrl.SetCompress(TRUE);
	oNAVOBRMCtrl.SetDescription(lpDescription);
	oNAVOBRMCtrl.backup();
}

long CAppDBManager::GetVarDependencyCount(long IdFile)
{
	__LoadPersistentData();
	ASSERT(__IsPersistentDataLoaded());
	
	SCP<CAppDBFileInfo> poFileInfoSP;

	if(!m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
	{
		ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
	}
	ASSERT(poFileInfoSP.PointsObject());
	return poFileInfoSP->GetDependVars().GetSize();
}

void CAppDBManager::GetVarDependencies(long IdFile,long * pDependencies)
{
	__LoadPersistentData();
	ASSERT(__IsPersistentDataLoaded());

	SCP<CAppDBFileInfo> poFileInfoSP;

	if(!m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
	{
		ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
	}
	ASSERT(poFileInfoSP.PointsObject());
	memcpy(pDependencies,poFileInfoSP->GetDependVars().GetData(),
		poFileInfoSP->GetDependVars().GetSize() * sizeof(long));
}

DATE CAppDBManager::GetModificationDate(long IdFile,bool bIncludeDependencies)
{
	CString oFileNameString;
	ALL_TRY
	{
		__LoadPersistentData();
		//to_do: ingored bIncludeDependencies
		SCP<CAppDBFileInfo> poFileInfoSP;

		if(!m_bDisableFastModifDate)
		{
			if(m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
			{
				if(poFileInfoSP->_get_modification_date() != GetNullDateSOV().GetDate())
				{
					return poFileInfoSP->_get_modification_date();
				}
			}
		}

		GenerateFileName(IdFile,oFileNameString);
		CFileStatus oFileStatus;
		CFile::GetStatus(oFileNameString,oFileStatus);
		SYSTEMTIME oSysTime;
		VERIFY(oFileStatus.m_mtime.GetAsSystemTime(oSysTime));
		COleDateTime oODT(oSysTime);
		if(poFileInfoSP.PointsObject())
		{
			poFileInfoSP->_set_modification_date(oODT);
		}
		return oODT;
		
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoException2(roNavoException,
			ERCO_APPDB_UNBL_TO_OPEN_APPFILE,IDPAGE_NOTAVAILABLE,IdFile,oFileNameString);
	};
}

void CAppDBManager::ChangeMode(long nNewMode)
{
	__LoadPersistentData();
	if(GetMode() == nNewMode)
	{
		return;
	}
	//switching to user mode
	if((nNewMode & APPDBMAN_MODE_USER) && !IsUserMode())
	{
		__CommitAppDB();
		ASSERT(m_bUserMode);
	}
	//switching to programmer mode
	if(!(nNewMode & APPDBMAN_MODE_USER) && IsUserMode())
	{
		m_bUserMode = false;
		__EncodeAppDB();
		m_bFileInfoDirty = true;
		__SavePersistentData();
	}
}

long CAppDBManager::GetMode() const
{
	long nMode = 0;
	if(IsUserMode())
	{
		nMode |= APPDBMAN_MODE_USER;
	}
	else
	{
		nMode |= APPDBMAN_MODE_PROGRAMMER;
	}
	return nMode;
}

void CAppDBFileInfo::SetDependVars(long nCount,long * pDependVars)
{
	m_oDependVarArray.SetSize(nCount);
	memcpy(m_oDependVarArray.GetData(),pDependVars,nCount * sizeof(long));
}

void CAppDBFileInfo::__WriteToArchive(CArchive & roArchive)
{
	roArchive << m_oFileNameString;
	m_oDependVarArray.Serialize(roArchive);
}

void CAppDBFileInfo::__ReadFromArchive(CArchive & roArchive)
{
	roArchive >> m_oFileNameString;
	m_oDependVarArray.Serialize(roArchive);
}

//---------------------------------------------------------------------------------------
//
//	helper do preprocessingu
//
//---------------------------------------------------------------------------------------

//zupe³ny helper - wykorzystywany w __PreprocessSingleFile
// oraz w  __CommitStdObjDef - po to aby nie preprocesowac "dataobj" 2 x
void __CopyVarDepFromPrepToFileInfo(long IdFile,SCP<IPreprocessor> & rpoPreprocessorSP,
	SCP<CAppDBFileInfo> & rpoFileInfoSP)
{
	long nVarCount = -1;
	long * pVarArray;
	CRemoteFreeHolder oRFH(pVarArray);
	HRESULT hr = rpoPreprocessorSP->GetVarDependencies(&nVarCount,&pVarArray);
	if(hr != S_OK)
	{
		ThrowNavoException2(ERCO_APPDB_PREP_VARDEP_FAILED, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String(hr));
	}
	ASSERT(nVarCount >= 0);
	TRACE2("FILE %d IS DEPENEDENT ON %d VARS\n",IdFile,nVarCount);
	rpoFileInfoSP->SetDependVars(nVarCount,pVarArray);
}

static void __PreprocessSingleFile(long IdFile,SCP<IPreprocessor> & rpoPreprocessorSP,
	SCP<CAppDBFileInfo> & rpoFileInfoSP)
{
	HRESULT hr = rpoPreprocessorSP->PreprocessFile(IdFile,BYTE(true));
	if(hr != S_OK)
	{
		ThrowNavoException2(ERCO_APPDB_PREP_FAILED, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String(hr));
	}
	SCP<IStream> pOutputStreamSP;
	pOutputStreamSP.QueryInterface(rpoPreprocessorSP);
	
	//pull all text to "null" destination, to make sure all was preprocessed
	ULARGE_INTEGER ulInfinity;
	ulInfinity.QuadPart = MAXLONG;
	hr = IStream_CopyTo(pOutputStreamSP,NULL,ulInfinity);
	if(hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(rpoPreprocessorSP,oNavoException);
		ContinueThrowNavoException2(oNavoException,ERCO_APPDB_PREP_FAILED2, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String(hr));
	}
	//get info: var dependencies
	__CopyVarDepFromPrepToFileInfo(IdFile,rpoPreprocessorSP,rpoFileInfoSP);
	VERIFY(rpoPreprocessorSP->Close() == S_OK);
}
	
void CAppDBManager::__PreprocessFile(long IdFile)
{
	ASSERT(__IsPersistentDataLoaded());

	SCP<CAppDBFileInfo> poFileInfoSP;

	if(!m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
	{
		ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
	}
	SCP<CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
	SCP<IStreamProvider> poStreamProviderSP = NewSCP(&m_xStreamProvider,true);
	SCP<IPreprocessor> poPreprocessorSP;
	poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor,CLSCTX_INPROC);
	VERIFY(S_OK == poPreprocessorSP->Init(poHLISP->GetIDispatch(FALSE),poStreamProviderSP,NULL));
	__PreprocessSingleFile(IdFile,poPreprocessorSP,poFileInfoSP);

}

void CAppDBManager::__PreprocessFileGroup(LPCTSTR lpFileGroupName)
{
	ASSERT(__IsPersistentDataLoaded());

	SCP<IPreprocessor> poPreprocessorSP;
	poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor,CLSCTX_INPROC);
	SCP<CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
	SCP<IStreamProvider> poStreamProviderSP = NewSCP(&m_xStreamProvider,true);
	VERIFY(S_OK == poPreprocessorSP->Init(poHLISP->GetIDispatch(FALSE),poStreamProviderSP,NULL));
	
	SCP<ISimpleEnumId> poSimpleEnumStreamSP;
	HRESULT hr = m_xAppDBManager.EnumFileGroup(lpFileGroupName,&poSimpleEnumStreamSP.GetRawPointer());
	
	while(hr == S_OK)
	{
		long IdFile;
		hr = poSimpleEnumStreamSP->Next(&IdFile);
		if(hr != S_OK)
		{
			break;
		}
		SCP<CAppDBFileInfo> poFileInfoSP;

		if(!m_oFileInfoMap.Lookup(IdFile,poFileInfoSP))
		{
			ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
		}
		__PreprocessSingleFile(IdFile,poPreprocessorSP,poFileInfoSP);
	}
}

void CAppDBManager::__EncodeFileGroup(LPCTSTR lpFileGroupName)
{
	SCP<ISimpleEnumId> poSimpleEnumStreamSP;
	HRESULT hr = m_xAppDBManager.EnumFileGroup(lpFileGroupName,&poSimpleEnumStreamSP.GetRawPointer());
	while(hr == S_OK)
	{
		long IdFile;
		hr = poSimpleEnumStreamSP->Next(&IdFile);
		if(hr != S_OK)
		{
			break;
		}
		if(IdFile == IDPAGE_FILEINFO)	//pomiñ kodowanie definicji aplikacji (jak gdyby samego siebie)
		{
			continue;
		}
		CString oString;
		GenerateFileName(IdFile,oString);
		SCP<IStream> poTempStreamSP = CreateTempFileStream();
		ULARGE_INTEGER ulInfinity;
		ulInfinity.QuadPart = MAXLONG;
		hr = IStream_CopyTo(OpenFileStream_Read(oString,false),poTempStreamSP,ulInfinity);
		ASSERT(hr==S_OK);
		CStreamHolder(poTempStreamSP).SeekToBegin();
		hr = IStream_CopyTo(poTempStreamSP,CreateFileStream_Write(oString,true),ulInfinity);
		ASSERT(hr==S_OK);
	}
}

void CAppDBManager::__ScanFileGroup(LPCTSTR lpFileGroupName)
{
	SCP<ISimpleEnumId> poSimpleEnumStreamSP;
	HRESULT hr = m_xAppDBManager.EnumFileGroup(lpFileGroupName,&poSimpleEnumStreamSP.GetRawPointer());
	
	while(hr == S_OK)
	{
		LPSTR pcFileNameString = NULL;
		long IdFile;
		hr = poSimpleEnumStreamSP->NextFull(&IdFile,&pcFileNameString);
		if(hr != S_OK)
		{
			break;
		}
		CString oFileName(pcFileNameString);

		SCP<CAppDBFileInfo> poFileInfoSP = NewSCP( new CAppDBFileInfo());
		poFileInfoSP->set_file_name(oFileName);

		SCP<CAppDBFileInfo> poTestFileInfoSP;
		if(m_oFileInfoMap.Lookup(IdFile,poTestFileInfoSP))
		{
			CString oInfoString;
			oInfoString.Format("Plik o id=%d ju¿ istnieje. Nazwa = %s",
				IdFile,(LPCTSTR) oFileName);
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oInfoString);
		}

		m_oFileInfoMap[ IdFile ] = poFileInfoSP;
		
		::NdrOleFree(pcFileNameString);
	}
}

void CAppDBManager::__CommitAppDB()
{
	__LoadPersistentData();
	{
#ifdef _DEBUG
		CDebugTimeMeter oDTM(_T("appdb commit"));
#endif
		//prepare var depenedencies info for all files
		__PreprocessFileGroup(GetFormPageSubDir());
		__PreprocessFileGroup(GetMenuPageSubDir());
		__PreprocessFileGroup(GetRaportPageSubDir());
		__PreprocessFileGroup(GetUtilPageSubDir());
		__PreprocessFileGroup(GetHelpPageSubDir());
		//don't preprocess Extras !!
		__CommitStdObjDef();
	}

	__EncodeAppDB();

	m_bFileInfoDirty = true;
	m_bUserMode = true;

	__SavePersistentData();
}

void CAppDBManager::__EncodeAppDB()
{
	__EncodeFileGroup(GetFormPageSubDir());
	__EncodeFileGroup(GetMenuPageSubDir());
	__EncodeFileGroup(GetRaportPageSubDir());
	__EncodeFileGroup(GetUtilPageSubDir());
	__EncodeFileGroup(GetHelpPageSubDir());
	__EncodeFileGroup(GetDataObjSubDir());
	__EncodeFileGroup(GetHeadersSubDir());
	__EncodeFileGroup(GetStylePageSubDir());
	__EncodeFileGroup(GetPicturePageSubDir());
	__EncodeFileGroup(GetDataObjLibSubDir());
	//don't encode Extras
}

class CADMUnpackSupplyInfo : public CSupplyInfo__
{
public:
	CADMUnpackSupplyInfo(LPCTSTR lpRootDirString) :
		CSupplyInfo__(),
		m_oRootDirString(lpRootDirString)
	{
	}
	virtual HRESULT Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer)
	{
		ASSERT(nInfoType == ERCO_ASK_FOR_RELATIVE_PATH);
		* pvarAnswer = CSmartOleVariant(m_oRootDirString).Detach();
		return S_OK;
	}
private:
	CString m_oRootDirString;
};

void CAppDBManager::Unpack(const VARIANT FAR& varSource,const VARIANT FAR& varSourceInfo)
{
	ASSERT(GetRootDir());
	if(*GetRootDir() == '\0')
	{
		ThrowNavoException(ERCO_APPDB_NOT_INITED, IDPAGE_NOTAVAILABLE);
	}

	CADMUnpackSupplyInfo oADMUSI(GetRootDir());
	{
		_DNAVOBRM oNAVOBRMCtrl;
		oNAVOBRMCtrl.CreateDispatch(_T("NAVOBRMCTRL.NAVOBRMCtrl.1"));
		DWORD dwCookie;
		
		const IID BASED_CODE IID_DNAVOBRMEvents =
		{ 0xc4f4646c, 0xc8a9, 0x4227, { 0x90, 0xce, 0x6f, 0x73, 0xdf, 0x46, 0x3a, 0x28 } };
		
		AfxConnectionAdvise(oNAVOBRMCtrl,IID_DNAVOBRMEvents,oADMUSI.GetUnknown(),TRUE,&dwCookie);
		oNAVOBRMCtrl.SetDatastream(varSource);
		oNAVOBRMCtrl.SetInfostream(varSourceInfo);
		oNAVOBRMCtrl.SetRootDir(GetRootDir());
		oNAVOBRMCtrl.restore();
		AfxConnectionUnadvise(oNAVOBRMCtrl,IID_DNAVOBRMEvents,oADMUSI.GetUnknown(),TRUE,dwCookie);
	}

	//reinit structures
	m_oFileInfoMap.RemoveAll();
	m_nAppVersion = APPVERSION_SETUP;
	__LoadPersistentData();
	//to_do: update version in registry
	//na razie
	m_bFileInfoDirty = true;
}


//--------------------- "ASP" pages ====================================
//
//---------------------- zwraca stronê pozwalaj¹c¹ zainstalowaæ (wyrzuciæ) skróty ---
//do aplikacji na serwerze

SCP <IStream> CAppDBManager::GetInstallAppClientPage()
{
	SCP <IStream> poStreamSP = CreateTempFileStream();
	CStreamHolder oSH(poStreamSP);
	CString oString(GetApplicationsRegistryKeyName());
	CArray<CString,LPCTSTR> oAppArray;
	LONG lResult = EnumRegistryKeys(HKEY_LOCAL_MACHINE,oString,oAppArray);
	oSH.WriteString(
		_T("<?xml version=\"1.0\" encoding=\"windows-1250\" ?><tree>")
		);
	for(long iter = 0; iter <= oAppArray.GetUpperBound(); iter++)
	{
		oSH.WriteString(_T("<node><label>") + oAppArray[iter] + _T("</label></node>"));
	}
	oSH.WriteString(
		_T("</tree>")
		);
	oSH.SeekToBegin();
	return poStreamSP;
}
