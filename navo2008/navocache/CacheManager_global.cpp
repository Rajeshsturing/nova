/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManager - local cache manager
		global management
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\navolog.h"
#include "CacheManager.h"
#include "srvclassfactory.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCacheManager, CCmdTarget)

LPCTSTR pcCacheSettingsRegKey = _T("\\FileCache");
LPCTSTR pcCacheRootVal= _T("Root");

extern CNavoLog oNavoLog;

CCacheManager::CCacheManager() :
	m_nUniqueIdent(0),
	m_bCompressTrafficToClient(false)
{

	CString oCacheSettingString = GetNAVO2001RootRegistryKeyName() + CString(pcCacheSettingsRegKey);
	LONG nResult = SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE,oCacheSettingString,pcCacheRootVal,m_oRootDirString);
	if(nResult != ERROR_SUCCESS)
	{
		ASSERT(false);
		m_oRootDirString = ".\\";	//w katalogu uruchomienia
	}
	EnsureEndingBackslash(m_oRootDirString);
	_read_global_info();
	_pending_delete();
	EnableAutomation();
}

CCacheManager::~CCacheManager()
{
	//wypisz niewypisane b³êdy
	CNavoExceptionAccessor oNEAH(GetErrorStorage());
	if(oNEAH.ErrorInfoArray().GetSize() > 0)
	{
		oNavoLog << GetErrorStorage().BuildCompleteErrorString();
	}
}

void CCacheManager::Close(bool bOK)
{
	_g_CacheManagerServerClassFactory.OnCloseObject();
}

void CCacheManager::OnFinalRelease()
{
}

void CCacheManager::_get_global_infofile_name(CString & roString)
{
	roString = m_oRootDirString + "global.dat";
}

const long _gc_nGlobalInfoVersion = 2;

void CCacheManager::_read_global_info()
{
	CString oFileNameString;
	_get_global_infofile_name(oFileNameString);

	//musimy tworzyæ katalog aby indexing service siê nie rzuca³
	NavoCreateDirectoryTree(m_oRootDirString);

	//check file existence
	CFileStatus oFileStatus;
	if(!CFile::GetStatus(oFileNameString,oFileStatus))
	{
		//not exists
		//init with defaults
		m_nUniqueIdent = 0;
		return;
	}

	//try open
	CFile oFile;
	if(!oFile.Open(oFileNameString,CFile::modeRead | CFile::shareExclusive))
	{
		CString oString;
		oString.Format("otwarcie pliku %s nieudane",oFileNameString);
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,oString);
	}
	CArchive oArchive(&oFile,CArchive::load);
	long nArchiveVersion = 0;
	oArchive >> nArchiveVersion;
	if(nArchiveVersion != _gc_nGlobalInfoVersion)
	{
		//bad archive version in file %s, found %d, expected: %d
		CString oString;
		oString.Format(IDS_BAD_VERSION,(LPCTSTR) oFileNameString,nArchiveVersion,_gc_nGlobalInfoVersion);
		AfxMessageBox(oString);
		ThrowNavoException3(ERCO_CACHE_BAD_ARCHIVE_VERSION, IDPAGE_NOTAVAILABLE, oFileNameString,nArchiveVersion , _gc_nGlobalInfoVersion);
	}
	oArchive >> m_nUniqueIdent;
	m_oPendingDeleteFileArray.Serialize(oArchive);
}

void CCacheManager::_write_global_info()
{
	CString oFileNameString;
	_get_global_infofile_name(oFileNameString);

	NavoCreateDirectoryTree(m_oRootDirString);

	CFile oFile(oFileNameString,CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	CArchive oArchive(&oFile,CArchive::store);
	
	oArchive << _gc_nGlobalInfoVersion;	//version
	oArchive << m_nUniqueIdent;
	
	m_oPendingDeleteFileArray.Serialize(oArchive);
}

bool CCacheManager::_get_single_server_info(LPCTSTR lpFullServerPath,
			SCP<CSingleServerPlaceCacheInfo> & rpoSSPCISP)
{
	CString oFullServerPathString(lpFullServerPath);
	oFullServerPathString.MakeLower();

	CSimpleLock oSimpleLock(m_oGlobalCS);
	if(!m_oGlobalMap.Lookup(oFullServerPathString,rpoSSPCISP))
	{
		rpoSSPCISP = NewSCP(new CSingleServerPlaceCacheInfo(this,oFullServerPathString));
		long nVersion = rpoSSPCISP->_read_info();
		if(nVersion != -1)
		{
			rpoSSPCISP->upgrade_from_version(nVersion);
			m_oGlobalMap[ oFullServerPathString ] = rpoSSPCISP;
		}
		else
		{
			rpoSSPCISP = 0;
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------------
//  transaction support
//----------------------------------------------------------------------------------
	
void CCacheManager::trans_get_or_create_server_info(LPCTSTR lpFullServerPath,
	SCP<CSingleServerPlaceCacheInfo> & rpoSSPCISP)
{
	//uwaga!
	//lpFullServerPath musi byæ lowercase
	//musi mieæ lock na m_oGlobalCS

	if(!m_oGlobalMap.Lookup(lpFullServerPath,rpoSSPCISP))
	{
		rpoSSPCISP = NewSCP(new CSingleServerPlaceCacheInfo(this,lpFullServerPath));
		long nVersion = rpoSSPCISP->_read_info();
		if(nVersion != -1)
		{
			rpoSSPCISP->upgrade_from_version(nVersion);
			m_oGlobalMap[ lpFullServerPath ] = rpoSSPCISP;
		}
		else
		{
			//read failed - clean
			rpoSSPCISP = 0;
			// create new - empty
			rpoSSPCISP = NewSCP(new CSingleServerPlaceCacheInfo(this,lpFullServerPath));
			rpoSSPCISP->_initialize_first();
			m_oGlobalMap[ lpFullServerPath ] = rpoSSPCISP;
		}
	}

}

	
