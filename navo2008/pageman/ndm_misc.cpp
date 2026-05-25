/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	navo document manager utility functions 		
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//------------------------------------------------------------------------------------
// copy engine function
//------------------------------------------------------------------------------------

class CCopyEngineSupplyInfo : public CSupplyInfo__
{
public:
	CCopyEngineSupplyInfo(LPCTSTR lpDestDirString) :
		CSupplyInfo__(),
		m_oDestDirString(lpDestDirString)
	{
	}
	virtual HRESULT Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer)
	{
		ASSERT(nInfoType == ERCO_ASK_FOR_RELATIVE_PATH);
		* pvarAnswer = CSmartOleVariant(m_oDestDirString).Detach();
		return S_OK;
	}
private:
	CString m_oDestDirString;
};

const TCHAR * GetUpdateSubDir();

const TCHAR * _g_pchNAVO2001Components		= "\\components\\navo2002\\";
const TCHAR * _g_pchNAVO2001Engine			= "System\\";
const TCHAR * _g_pchNAVO2001SetupEXE		= "setup.exe";

void CopyEngineFiles(SCP<IStream> & rpoDataStreamSP,SCP<IStream> & rpoInfoStreamSP)
{
	//create restore instance
	SCP<IBackupRestoreManager> poBRMSP;
	poBRMSP.CreateInstance(CLSID_NAVO2001BackupRestoreManager,CLSCTX_INPROC);

	//get destination path
	CString oStringRoot,oStringSystem,oStringUpdate;
	LONG lResult =  SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),"InstallationRoot",oStringRoot);
	ASSERT(lResult == ERROR_SUCCESS);
	oStringUpdate = oStringRoot + GetUpdateSubDir() + CString(_g_pchNAVO2001Components);
	EnsureEndingBackslash(oStringUpdate);
	NavoCreateDirectoryTree(oStringUpdate);
	oStringSystem = oStringRoot + _g_pchNAVO2001Engine;
	EnsureEndingBackslash(oStringSystem);
	CCopyEngineSupplyInfo oCESI(oStringUpdate);

	SCP<IStream> poTempDataStreamSP = CreateTempFileStream();
	SCP<IStream> poTempInfoStreamSP = CreateTempFileStream();
	ULARGE_INTEGER ulInfinity;
	ulInfinity.QuadPart = MAXLONG;
	HRESULT hr = IStream_CopyTo(rpoDataStreamSP,poTempDataStreamSP,ulInfinity);
	if(hr == S_OK)
	{
		hr = IStream_CopyTo(rpoInfoStreamSP,poTempInfoStreamSP,ulInfinity);
		if(hr == S_OK)
		{
			CStreamHolder(poTempDataStreamSP).SeekToBegin();
			CStreamHolder(poTempInfoStreamSP).SeekToBegin();
			//do restore
			hr = poBRMSP->SetRestoreStream(poTempDataStreamSP,poTempInfoStreamSP,NULL,oCESI.GetUnknown());
			if(hr == S_OK)
			{
				//copy setup.exe to %navoroot%\system dir
				VERIFY(::CopyFile(oStringUpdate + _g_pchNAVO2001SetupEXE,oStringSystem+ _g_pchNAVO2001SetupEXE, FALSE));
				oStringUpdate = oStringRoot + GetUpdateSubDir();
				EnsureEndingBackslash(oStringUpdate);
				lResult =  SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),"MediaSource",oStringUpdate);
				ASSERT(lResult == ERROR_SUCCESS);
				//set MediaSource
				return;
			}
		}
	}
	//to_do: delete copied files

	CNavoException oNavoException;
	GetErrorInfoFromInterface(poBRMSP,oNavoException);
	ContinueThrowNavoException(oNavoException,ERCO_COPY_ENGINE_FILES_FAILED,IDPAGE_NOTAVAILABLE);
}