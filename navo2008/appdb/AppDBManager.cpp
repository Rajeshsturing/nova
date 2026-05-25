/*
	NAVO Sp. z o.o. (2000)

	NAVO Enterprise

	class:
		CAppDBManager - APPLICATION database manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\filerange.h"		//file range definitions
#include "..\include\InterfaceUtil.h"	//
#include "AppDBManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDBManager

IMPLEMENT_DYNCREATE(CAppDBManager, CCmdTarget)
// {188cb157-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CAppDBManager, "navoappdb.appdbmanager", 0x188cb157, 0x82a4, 0x4498, 0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

CAppDBManager::CAppDBManager() :
	m_bUserMode(false),
	m_bFileInfoDirty(false),
	m_nAppVersion(APPVERSION_INTERNAL_ERROR),
	m_bDisableFastModifDate(false),
	m_bCompressTrafficToClient(false)
{
	EnableAutomation();
	AfxOleLockApp();

	CString oDisableFastMDString;
	SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSupportRegistryKeyName(), _T("DisableFastModDate"), oDisableFastMDString);
	oDisableFastMDString.MakeUpper();
	if (oDisableFastMDString == "Y")
	{
		m_bDisableFastModifDate = true;
	}

	m_oRootDirString = "";
}

CAppDBManager::~CAppDBManager()
{
	Close(true);
	AfxOleUnlockApp();
}

BEGIN_DISPATCH_MAP(CAppDBManager, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAppDBManager)
	DISP_PROPERTY_EX(CAppDBManager, "mode", getmodeAUTO, setmodeAUTO, VT_I4)
	DISP_FUNCTION(CAppDBManager, "init", initAUTO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CAppDBManager, "upload", uploadAUTO, VT_I4, VTS_I4 VTS_UNKNOWN VTS_BSTR)
	DISP_FUNCTION(CAppDBManager, "delete", deleteAUTO, VT_I4, VTS_I4)
	DISP_FUNCTION(CAppDBManager, "create", createAUTO, VT_I4, VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CAppDBManager, "drop", dropAUTO, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CAppDBManager, "pack", packAUTO, VT_I4, VTS_VARIANT VTS_VARIANT VTS_BSTR)
	DISP_FUNCTION(CAppDBManager, "unpack", unpackAUTO, VT_I4, VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CAppDBManager, "compiledataobj", CompileDataObjAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_MESSAGE_MAP(CAppDBManager, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CAppDBManager)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppDBManager message handlers
static const IID IID_IAppDBManagerDisp =
{
  0x4bc847ae, 0x5f8c, 0x4db2, { 0x9c, 0x93, 0xa8, 0xfb, 0x56, 0xac, 0xff, 0x79 }
};

BEGIN_INTERFACE_MAP(CAppDBManager, CCmdTargetInterface)
	INTERFACE_PART(CAppDBManager, IID_INavoErrorInfo, NavoErrorInfo)
	INTERFACE_PART(CAppDBManager, IID_IAppDBManagerDisp, Dispatch)
	INTERFACE_PART(CAppDBManager, IID_IStreamProvider, StreamProvider)
	INTERFACE_PART(CAppDBManager, IID_IAppDBManager, AppDBManager)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CAppDBManager, StreamProvider)
DELEGATE_UNKNOWN_INTERFACE(CAppDBManager, AppDBManager)
DELEGATE_UNKNOWN_INTERFACE(CAppDBManager, NavoErrorInfo)


STDMETHODIMP CAppDBManager::XAppDBManager::SetAltStreamProvider(IStreamProvider * pStreamProvider)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

		ALL_TRY
	{
		pThis->m_poStreamProviderSP = NewSCP(pStreamProvider, true);
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}

STDMETHODIMP CAppDBManager::XStreamProvider::Get(long IdFile, IStream **pStream, navostreaminfo * poNSI)
{
	METHOD_PROLOGUE(CAppDBManager, StreamProvider)

		ALL_TRY
	{
		_init_navostreaminfo(*poNSI);
		*pStream = NULL;		//a jak bêdzie wyj¹tek...
		SCP<IStream> poStreamSP = pThis->GetFile(IdFile);
		if (pThis->m_bCompressTrafficToClient)
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
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);
	return S_OK;
}

void CAppDBManager::GenerateFileName(long IdFile, CString & roFileNameString)
{
	//IDPAGE_FILEINFO is exception !
	ASSERT(IdFile != IDPAGE_FILEINFO);

	ASSERT(GetRootDir());
	if (*GetRootDir() == '\0')
	{
		ThrowNavoException(ERCO_APPDB_NOT_INITED, IDPAGE_NOTAVAILABLE);
	}

	LPCTSTR lpSubDir = NULL;

	if (FileIdIsHeader(IdFile))
	{
		lpSubDir = GetHeadersSubDir();
	}
	else if (FileIdIsDataObjLib(IdFile))
	{
		lpSubDir = GetDataObjLibSubDir();
	}
	else if (FileIdIsUtil(IdFile))
	{
		lpSubDir = GetUtilPageSubDir();
	}
	else if (FileIdIsForm(IdFile))
	{
		lpSubDir = GetFormPageSubDir();
	}
	else if (FileIdIsPicture(IdFile))
	{
		lpSubDir = GetPicturePageSubDir();
	}
	else if (FileIdIsDataObj(IdFile))
	{
		lpSubDir = GetDataObjSubDir();
	}
	else if (FileIdIsMenu(IdFile))
	{
		lpSubDir = GetMenuPageSubDir();
	}
	else if (FileIdIsRaport(IdFile))
	{
		lpSubDir = GetRaportPageSubDir();
	}
	else if (FileIdIsHelp(IdFile))
	{
		lpSubDir = GetHelpPageSubDir();
	}
	else if (FileIdIsStyle(IdFile))
	{
		lpSubDir = GetStylePageSubDir();
	}
	else if (FileIdIsExtras(IdFile))
	{
		lpSubDir = GetExtrasSubDir();
	}

	if (lpSubDir == NULL)
	{
		ThrowNavoException1(ERCO_APPDB_INVALIDFILEID, IDPAGE_NOTAVAILABLE, IdFile);
	}

	SCP<CAppDBFileInfo> poFileInfoSP;
	if (!m_oFileInfoMap.Lookup(IdFile, poFileInfoSP))
	{
		ThrowNavoException1(ERCO_APPDB_NO_VARDEP_INFO, IDPAGE_NOTAVAILABLE, IdFile);
	}

	roFileNameString.Format(_T("%s%s\\%s"), GetRootDir(), lpSubDir, poFileInfoSP->get_file_name());
	//	TRACE2("AppDB:Filename for %d is %s\n",IdFile,roFileNameString);
}

SCP <IStream> CAppDBManager::GetFile(long lFileId)
{
	if (lFileId == IDPAGE_INSTALLED_APPS)
	{
		return GetInstallAppClientPage();
	}
	else
	{
		CString oFileNameString;
		ALL_TRY
		{
			if (m_poStreamProviderSP.PointsObject())
			{
				SCP<IStream> poInitialStreamSP;

				navostreaminfo oNSI;
				_init_navostreaminfo(oNSI);
				HRESULT hr = m_poStreamProviderSP->Get(lFileId, &poInitialStreamSP.GetRawPointer(), &oNSI);

				if (hr == S_OK && poInitialStreamSP.PointsObject())
				{
					return poInitialStreamSP;
				}
			}

			__LoadPersistentData();
			GenerateFileName(lFileId,oFileNameString);
			bool bDecode = m_bUserMode && (!FileIdIsExtras(lFileId));
		
			return OpenFileStream_Read(oFileNameString,bDecode);
		}
		ALL_CATCH(CNavoException & roNavoException)
		{
			ContinueThrowNavoException2(roNavoException,
				ERCO_APPDB_UNBL_TO_OPEN_APPFILE, IDPAGE_NOTAVAILABLE, lFileId, oFileNameString);
		};
	}
}

long CAppDBManager::initAUTO(LPCTSTR lpAppName)
{
	ALL_TRY
	{
		Init(lpAppName);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::uploadAUTO(long FileId, LPUNKNOWN pStream, LPCTSTR pExt)
{
	ALL_TRY
	{
		SCP<IStream> pStreamSP;
		pStreamSP.QueryInterface(pStream);
		Upload(FileId,pStreamSP.Get(),pExt);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::deleteAUTO(long FileId)
{
	ALL_TRY
	{
		Delete(FileId);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::createAUTO(LPCTSTR lpAppName, LPCTSTR lpRootDir, long nVersion)
{
	ALL_TRY
	{
		CreateStructures(lpAppName,lpRootDir,nVersion);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::dropAUTO(LPCTSTR lpAppName)
{
	ALL_TRY
	{
		DropApp(lpAppName);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::packAUTO(const VARIANT FAR & varDestination, const VARIANT FAR& varDestinationInfo, LPCTSTR lpDescription)
{
	ALL_TRY
	{
		Pack(varDestination,varDestinationInfo,lpDescription);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::unpackAUTO(const VARIANT FAR & varSource, const VARIANT FAR & varSourceInfo)
{
	ALL_TRY
	{
		Unpack(varSource,varSourceInfo);
		return ERCO_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CAppDBManager::getmodeAUTO()
{
	ALL_TRY
	{
		return GetMode();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CAppDBManager::setmodeAUTO(long nNewValue)
{
	ALL_TRY
	{
		ChangeMode(nNewValue);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


void CAppDBManager::CompileDataObjAUTO()
{
	ALL_TRY
	{
		__CommitStdObjDef();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

class CSimpleStreamEnumerator : public CCmdTargetInterface
{
public:
	CSimpleStreamEnumerator(LPCTSTR lpDirectory, LPCTSTR lpMask)
	{
		Fill(lpDirectory, lpMask);
	}
	DECLARE_INTERFACE_MAP();

	BEGIN_INTERFACE_PART(SimpleEnumId, ISimpleEnumId)
		STDMETHOD(Next)(long * pId);
	STDMETHOD(NextFull)(long * pId, LPSTR * plpValue);
	END_INTERFACE_PART(SimpleEnumId)
private:
	void Fill(LPCTSTR lpDir, LPCTSTR lpMask);

	CArray<long, long> m_oFileIdArray;
	CArray<CString, LPCTSTR> m_oFileNameArray;
	long m_nCurrent;
};

BEGIN_INTERFACE_MAP(CSimpleStreamEnumerator, CCmdTargetInterface)
	INTERFACE_PART(CSimpleStreamEnumerator, IID_ISimpleEnumId, SimpleEnumId)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CSimpleStreamEnumerator, SimpleEnumId)


STDMETHODIMP CSimpleStreamEnumerator::XSimpleEnumId::Next(long * pFileId)
{
	METHOD_PROLOGUE(CSimpleStreamEnumerator, SimpleEnumId)

		ALL_TRY
	{
		*pFileId = 0;
		pThis->m_nCurrent++;
		if (pThis->m_nCurrent <= pThis->m_oFileIdArray.GetUpperBound())
		{
			*pFileId = pThis->m_oFileIdArray[pThis->m_nCurrent];
			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	ALL_CATCH(CNavoException & roException)
	{
		//to_do:
		return DISP_E_EXCEPTION;
	};
}

STDMETHODIMP CSimpleStreamEnumerator::XSimpleEnumId::NextFull(long * pFileId, LPSTR * plpValue)
{
	METHOD_PROLOGUE(CSimpleStreamEnumerator, SimpleEnumId)

		ALL_TRY
	{

		*pFileId = 0;
		*plpValue = NULL;
		pThis->m_nCurrent++;
		if (pThis->m_nCurrent <= pThis->m_oFileIdArray.GetUpperBound())
		{
			*pFileId = pThis->m_oFileIdArray[pThis->m_nCurrent];
			*plpValue = (LPTSTR) ::NdrOleAllocate(pThis->m_oFileNameArray[pThis->m_nCurrent].GetLength() + 1);
			strcpy((LPTSTR)*plpValue, pThis->m_oFileNameArray[pThis->m_nCurrent]);

			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	ALL_CATCH(CNavoException & roException)
	{
		//to_do:
		return DISP_E_EXCEPTION;
	};
}

void CSimpleStreamEnumerator::Fill(LPCTSTR lpDir, LPCTSTR lpMask)
{
	CFileFind oFileFind;
	CString strWildcard(lpDir);
	EnsureEndingBackslash(strWildcard);
	strWildcard += CString(lpMask);

	BOOL bWorking = oFileFind.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = oFileFind.FindNextFile();
		if (oFileFind.IsDots() || oFileFind.IsDirectory())
		{
			continue;
		}
		else
		{
			long FileId = _ttol(LPCTSTR(oFileFind.GetFileName()) + 1);
			ASSERT(FileId);		//maska powinna pomin¹æ nieprawid³owe pliki
			m_oFileIdArray.Add(FileId);
			m_oFileNameArray.Add(oFileFind.GetFileName());
		}
	}
	oFileFind.Close();
	m_nCurrent = -1;
}

STDMETHODIMP CAppDBManager::XAppDBManager::EnumFileGroup(LPCTSTR lpGroupName,
	ISimpleEnumId ** ppSimpleEnumFileId)
{
	METHOD_PROLOGUE(CAppDBManager, AppDBManager)

		ALL_TRY
	{
		//we assume that group name is identical to directory name
		CString oMaskString;
		if (!CString(lpGroupName).CompareNoCase(pThis->GetHeadersSubDir()))
		{
			oMaskString = "h*.h";
		}
		else if (!CString(lpGroupName).CompareNoCase(pThis->GetDataObjLibSubDir()))
		{
			oMaskString = "l*.nxb";
		}
		else if (!CString(lpGroupName).CompareNoCase(pThis->GetPicturePageSubDir()))
		{
			oMaskString = "p*.pic";
		}
		else if (!CString(lpGroupName).CompareNoCase(pThis->GetExtrasSubDir()))
		{
			oMaskString = "e*.dat";
		}
		else
		{
			oMaskString = "*.xml";
		}
		SCP<CSimpleStreamEnumerator> poSSESP =
			NewSCP(new CSimpleStreamEnumerator(pThis->GetRootDir() + CString(lpGroupName), oMaskString));
		SCP<ISimpleEnumId> poSimpleEnumStreamSP;
		poSimpleEnumStreamSP.QueryInterface(poSSESP);
		*ppSimpleEnumFileId = poSimpleEnumStreamSP.Detach();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
LPCTSTR CAppDBManager::GetHeadersSubDir()
{
	return _T("header");
}

LPCTSTR CAppDBManager::GetDataObjSubDir()
{
	return _T("dataobj");
}

LPCTSTR CAppDBManager::GetDataObjLibSubDir()
{
	return _T("library");
}

LPCTSTR CAppDBManager::GetFormPageSubDir()
{
	return _T("form");
}

LPCTSTR CAppDBManager::GetUtilPageSubDir()
{
	return _T("util");
}

LPCTSTR CAppDBManager::GetMenuPageSubDir()
{
	return _T("menu");
}

LPCTSTR CAppDBManager::GetExtrasSubDir()
{
	return _T("extras");
}

LPCTSTR CAppDBManager::GetRaportPageSubDir()
{
	return _T("raport");
}

LPCTSTR CAppDBManager::GetHelpPageSubDir()
{
	return _T("help");
}

LPCTSTR CAppDBManager::GetStylePageSubDir()
{
	return _T("style");
}

LPCTSTR CAppDBManager::GetPicturePageSubDir()
{
	return _T("picture");
}

const long APPDB_ARCHIVE_VERSION = 2;

void CAppDBManager::__WriteToArchive(CArchive & roArchive)
{
	roArchive << APPDB_ARCHIVE_VERSION;
	roArchive << (long)m_nAppVersion;
	roArchive << (BYTE)m_bUserMode;
	roArchive << (long)m_oFileInfoMap.GetCount();
	POSITION pos = m_oFileInfoMap.GetStartPosition();
	while (pos)
	{
		long IdFile;
		SCP<CAppDBFileInfo> poAppDBFileInfoSP;
		m_oFileInfoMap.GetNextAssoc(pos, IdFile, poAppDBFileInfoSP);
		roArchive << IdFile;
		poAppDBFileInfoSP->__WriteToArchive(roArchive);
	}
}

void CAppDBManager::__ReadFromArchive(CArchive & roArchive)
{
	long nVersion;
	roArchive >> nVersion;
	if (nVersion != APPDB_ARCHIVE_VERSION)
	{
		ThrowNavoException2(ERCO_APPDB_FILEINFO_BAD_VERSION, IDPAGE_NOTAVAILABLE,
			nVersion, APPDB_ARCHIVE_VERSION);
	}
	long nAppVersion;
	roArchive >> (long)nAppVersion;

	//niezgodnoœæ pomiêdzy registry a plikiem !!!
	//ignorujemy dla aplikacji SETUP

	if (m_nAppVersion != nAppVersion &&
		m_nAppVersion != APPVERSION_SETUP)
	{
		ThrowNavoException2(ERCO_APPDB_FILEINFO_VERSION_MISMATCH, IDPAGE_NOTAVAILABLE,
			nAppVersion, m_nAppVersion);
	}
	m_nAppVersion = nAppVersion;

	BYTE ucUserMode;
	roArchive >> ucUserMode;
	m_bUserMode = (ucUserMode != '\0');
	long nCount;
	roArchive >> nCount;
	while (nCount--)
	{
		long IdFile;
		roArchive >> IdFile;
		SCP<CAppDBFileInfo> poAppDBFileInfoSP = NewSCP(new CAppDBFileInfo());
		poAppDBFileInfoSP->__ReadFromArchive(roArchive);
		m_oFileInfoMap[IdFile] = poAppDBFileInfoSP;
	}
}

void CAppDBManager::__LoadPersistentData()
{
	if (__IsPersistentDataLoaded())
	{
		return;		//already read
	}
	CString oFileNameString = GetRootDir() + CString(GetDataObjLibSubDir()) + "\\L6.NXB";
	CFile oFile;
	if (!oFile.Open(oFileNameString, CFile::modeRead | CFile::shareDenyWrite))
	{
		ThrowNavoException2(ERCO_APPDB_UNBL_TO_OPEN_FILEINFO, IDPAGE_NOTAVAILABLE,
			(LPCTSTR)oFileNameString, GetLastError_To_String(::GetLastError()));
	}
	CArchive oArchive(&oFile, CArchive::load);
	__ReadFromArchive(oArchive);
}

void CAppDBManager::__SavePersistentData()
{
	if (!m_bFileInfoDirty)
	{
		return;
	}
	CString oFileNameString = GetRootDir() + CString(GetDataObjLibSubDir()) + "\\L6.NXB";
	CFile oFile(oFileNameString, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	CArchive oArchive(&oFile, CArchive::store);
	__WriteToArchive(oArchive);
	m_bFileInfoDirty = false;
}

//---------------------------------------------------------------------------------------
SCP<IStream> CAppDBManager::get_final_stream(long idFile, SCP<IDispatch> poEnvDispatchSP)
{
	SCP<IStreamProvider> poStreamProviderSP;
	poStreamProviderSP.QueryInterface(&m_xStreamProvider);

	ASSERT(poEnvDispatchSP.PointsObject());

	SCP<IStream> poStreamSP;

	SCP<IPreprocessor> poPreprocessorSP;
	poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor, CLSCTX_INPROC);

	VERIFY(S_OK == poPreprocessorSP->Init(poEnvDispatchSP.Get(), poStreamProviderSP, NULL));
	HRESULT hr = poPreprocessorSP->PreprocessFile(idFile, BYTE(false));
	if (hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(poPreprocessorSP, oNavoException);
		ContinueThrowNavoException2(oNavoException, ERCO_PAGECACHE_PREPROCESS_FAILED, IDPAGE_NOTAVAILABLE, idFile, SCODE_To_String(hr));
	}
	poStreamSP.QueryInterface(poPreprocessorSP);

	return poStreamSP;
}
