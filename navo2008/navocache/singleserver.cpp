/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CSingleServerPlaceCacheInfo - single server info
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\navoclassfactory.h"
#include "..\include\InterfaceUtil.h"
#include "CacheManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//warning! don't change it without reason !
//change also global archive version id !

const long _gn_SubDirCount = 100;	

//use 1000 for huge number of files. Warning! You have to rebuild cache info and
//move files to new dirs when changes this value
//zmieñ te¿ prefiks w _get_subdir_for_ivi aby ³atwiej rozpoznawaæ rodzaj podkartotek

static void normalize_path(LPCTSTR lpFullServerPath,CString & roNormalizedString)
{
	normalize_name_4_path(lpFullServerPath,roNormalizedString);
}

CSingleServerPlaceCacheInfo::CSingleServerPlaceCacheInfo(CCacheManager * poCacheManager,
		LPCTSTR lpFullServerPath) :
	m_poCacheManager(poCacheManager),
	m_oFullServerPathString(lpFullServerPath),
	m_nGenerator(1),
	m_bDirty(false),
	m_bBlobDataBase(false)
{
	ASSERT(poCacheManager);

	m_bBlobDataBase = (m_oFullServerPathString.Find(_T("<database>:")) == 0);

	CString oNormalizedPathString;
	normalize_path(m_oFullServerPathString,oNormalizedPathString);
	m_oStorageDirString = m_poCacheManager->_get_root_dir() + oNormalizedPathString;
	EnsureEndingBackslash(m_oStorageDirString);
}

void CSingleServerPlaceCacheInfo::_initialize_first()
{
	ASSERT(m_oGUIDString.IsEmpty());
	GUID oTmpGUID;
	VERIFY(S_OK == ::CoCreateGuid(&oTmpGUID));
	m_oGUIDString = StringFromCLSID(oTmpGUID);
	ASSERT(!m_oGUIDString.IsEmpty());

	if(is_blob_database())
	{

		CString oDirPathString;
		_get_storage_dir(oDirPathString);
		NavoCreateDirectoryTree(oDirPathString);

		_setup_indexing_service();
	}
}

void CSingleServerPlaceCacheInfo::_get_infofile_name(CString & roInfoFileString)
{
	_get_storage_dir(roInfoFileString);
	roInfoFileString += "info.dat";
}

long CSingleServerPlaceCacheInfo::_read_info()
{
	ASSERT(m_poCacheManager);

	CString oFileNameString;
	_get_infofile_name(oFileNameString);

	CFile oFile;
	if(!oFile.Open(oFileNameString,CFile::modeRead | CFile::shareExclusive))
	{
		return -1;
	}
	CArchive oArchive(&oFile,CArchive::load);
	long nVersion = _read_from_archive(oArchive,oFileNameString);
	m_bDirty = false;
	return nVersion;
}

void CSingleServerPlaceCacheInfo::_write_info()
{
	CSimpleLock oSimpleLock(m_oItemInfoCS);
	if(!is_dirty())
	{
		return;
	}

	CString oFileNameString;
	_get_storage_dir(oFileNameString);
	NavoCreateDirectoryTree(oFileNameString);

	_get_infofile_name(oFileNameString);
	
	CFile oFile(oFileNameString,CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate);
	CArchive oArchive(&oFile,CArchive::store);
	_write_to_archive(oArchive);
	m_bDirty = false;
}

const long CACHE_ARCHIVE_VERSION_RELEASE_MARCH_2002 = 3;
const long CACHE_ARCHIVE_VERSION = 4;

long CSingleServerPlaceCacheInfo::_read_from_archive(CArchive & roArchive,LPCTSTR lpFileName)
{
	long nArchiveVersion;
	roArchive >> nArchiveVersion;
	if(nArchiveVersion < CACHE_ARCHIVE_VERSION_RELEASE_MARCH_2002)
	{
		ThrowNavoException3(ERCO_CACHE_BAD_SINGLE_ARCHIVE_VERSION, IDPAGE_NOTAVAILABLE, 
			lpFileName,nArchiveVersion,CACHE_ARCHIVE_VERSION);
	}
	ASSERT(m_oGUIDString.IsEmpty());
	roArchive >> m_oGUIDString;
	long nCount;
	roArchive >> m_nGenerator >> nCount;
	while(nCount--)
	{
		long IdFile;
		roArchive >> IdFile;
		SCP<CItemVariantInfo> poFileVariantsInfoSP = NewSCP( new CItemVariantInfo(this));
		poFileVariantsInfoSP->read_from_archive(roArchive);
		m_oItemVariantInfoMap[ IdFile ] = poFileVariantsInfoSP;
	}
	return nArchiveVersion;
}

void CSingleServerPlaceCacheInfo::_write_to_archive(CArchive & roArchive)
{
	roArchive << CACHE_ARCHIVE_VERSION << m_oGUIDString << m_nGenerator << m_oItemVariantInfoMap.GetCount();

	POSITION pos = m_oItemVariantInfoMap.GetStartPosition();
	while(pos)
	{
		long IdFile;
		SCP<CItemVariantInfo> poFileVariantsInfoSP;
		m_oItemVariantInfoMap.GetNextAssoc(pos,IdFile,poFileVariantsInfoSP);
		roArchive << IdFile;
		poFileVariantsInfoSP->write_to_archive(roArchive);
	}
}

void CSingleServerPlaceCacheInfo::write_to_backup_archive(SCP<IStream> poOutStreamSP)
{
	CStreamHolder oSH(poOutStreamSP);

	{
		oSH.WritePascalString(m_oGUIDString);
		oSH.Write(&m_nGenerator,sizeof(m_nGenerator));
		long nCount = m_oItemVariantInfoMap.GetCount();
		oSH.Write(&nCount,sizeof(nCount));

		POSITION pos = m_oItemVariantInfoMap.GetStartPosition();
		while(pos)
		{
			long IdFile;
			SCP<CItemVariantInfo> poFileVariantsInfoSP;
			m_oItemVariantInfoMap.GetNextAssoc(pos,IdFile,poFileVariantsInfoSP);
			oSH.Write(&IdFile,sizeof(IdFile));
			poFileVariantsInfoSP->write_to_backup_archive(poOutStreamSP);
		}
	}
}

void CSingleServerPlaceCacheInfo::load_from_backup_archive(SCP<IStream> poInStreamSP)
{
	CStreamHolder oSH(poInStreamSP);

	m_oGUIDString = oSH.ReadPascalString();
	oSH.Read(&m_nGenerator,sizeof(m_nGenerator));
	long nCount;
	oSH.Read(&nCount,sizeof(nCount));

	while(nCount--)
	{
		long IdFile;
		oSH.Read(&IdFile,sizeof(IdFile));
		SCP<CItemVariantInfo> poFileVariantsInfoSP = NewSCP( new CItemVariantInfo(this));
		poFileVariantsInfoSP->load_from_backup_archive(poInStreamSP);
		m_oItemVariantInfoMap[ IdFile ] = poFileVariantsInfoSP;
	}
	
	set_dirty();
}

void CSingleServerPlaceCacheInfo::_get_subdir_for_ivi(long IdFile,CString & roSubDir)
{
	CString oString;
	//A - prefiks dla _gn_SubDirCount = 100, dla innych u¿yj innego
	roSubDir = "A"+Long2String(_gn_SubDirCount + (IdFile % _gn_SubDirCount)).Mid(1) + "\\";
}

bool CSingleServerPlaceCacheInfo::get_info(long IdFile,SCP<CItemVariantInfo> & rpoFileVariantsInfoSP)
{
	CSimpleLock oSimpleLock(m_oItemInfoCS);
	if(!m_oItemVariantInfoMap.Lookup(IdFile,rpoFileVariantsInfoSP))
	{
		return false;
	}
	return true;
}

void CSingleServerPlaceCacheInfo::get_item_full_path(const CItemVariantInfo * poIVI,const CCacheInfoItem * poCII,CString & roFullPathString) const
{
	ASSERT(poIVI);
	ASSERT(poCII);
	
	CString oFileNameString;
	_get_storage_dir(roFullPathString);
	roFullPathString += poIVI->get_sub_dir();
	roFullPathString += poCII->get_file_name();

	CItemVariantInfo::supply_extension(roFullPathString,is_blob_database(),poIVI->_get_stream_info());
}

void CSingleServerPlaceCacheInfo::create_item_full_path(long IdFile,CString & roPathString,CString & roFileNameString)
{
	CString oRootDirString,oSubDirString,oFileNameString;
	_get_storage_dir(oRootDirString);
	_get_subdir_for_ivi(IdFile,oSubDirString);
	
	{
		CSimpleLock oSimpleLock(m_oItemInfoCS);
		oFileNameString = Long2String(++m_nGenerator);
	}
	roFileNameString = Long2String(IdFile) + "_" + oFileNameString;
	roPathString = oRootDirString + oSubDirString;
}

void CSingleServerPlaceCacheInfo::upgrade_from_version(long nVersion)
{
	if(CACHE_ARCHIVE_VERSION == nVersion)
	{
		return;
	}
	if(CACHE_ARCHIVE_VERSION_RELEASE_MARCH_2002 == nVersion)
	{
		if(is_blob_database())
		{
			//decode all files
			_decode_all(true);
			_setup_indexing_service();
		}
	}
	set_dirty();
	_write_info();
}

/*
	function decodes all single server files and updates CacheInfoItem
	bUseOldExtensions - when called on upgrade - uses .cache extension for old file
*/

void CSingleServerPlaceCacheInfo::_decode_all(bool bUseOldExtensions)
{
	CSimpleLock oSimpleLock(m_oItemInfoCS);
	CSimpleLock oSimpleLock2(_get_atom_cs());

	POSITION pos = m_oItemVariantInfoMap.GetStartPosition();
	while(pos)
	{
		long IdFile;
		SCP<CItemVariantInfo> poFileVariantsInfoSP;
		m_oItemVariantInfoMap.GetNextAssoc(pos,IdFile,poFileVariantsInfoSP);
		long iter = 0;
		SCP<CCacheInfoItem> poCIISP = poFileVariantsInfoSP->get_item(iter++);
		while(poCIISP.PointsObject())
		{
			CString oItemFullPathString;
			poCIISP->get_full_path(oItemFullPathString);
			if(bUseOldExtensions)
			{
				//substitue new extension (e.a. .unk, .pic) with old one (always .cache)
				long nPos = oItemFullPathString.ReverseFind('.');
				ASSERT(nPos != -1);
				oItemFullPathString = oItemFullPathString.Left(nPos) + CCacheInfoItem::get_suffix();
			}
			//now decode file
			CFileStatus oFileStatus;
			if(!CFile::GetStatus(oItemFullPathString,oFileStatus))
			{
				//file %d stored as %s does not exists
				ThrowNavoException2(ERCO_CACHE_GET_FILE_FAILED, IDPAGE_NOTAVAILABLE, IdFile, oItemFullPathString);
			}

			//generate new name
			CString oPathString;
			CString oFileNameString;
			create_item_full_path(IdFile,oPathString,oFileNameString);
			poCIISP->_set_file_name(oFileNameString);

			//open encoded
			SCP<IStream> poEncodedStreamSP = OpenFileStream_Read(oItemFullPathString,true);
			
			//create decoded
			CString oTmpFileNameString = oPathString + oFileNameString;
			CItemVariantInfo::supply_extension(oTmpFileNameString,is_blob_database(),
				poFileVariantsInfoSP->_get_stream_info());

			SCP<IStream> poDecodedStreamSP = CreateFileStream_Write(oTmpFileNameString,false);
			
			//copy with decoding
			ULARGE_INTEGER ulInfinity;
			ulInfinity.QuadPart = MAXLONG;
			HRESULT hr = IStream_CopyTo(poEncodedStreamSP,poDecodedStreamSP,ulInfinity);
			if(hr != S_OK)
			{
				ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
			}
			poEncodedStreamSP = 0;
			if(!NavoDeleteFile(oItemFullPathString))
			{
				m_poCacheManager->Add2PendingDelete(oItemFullPathString);
			}
			poCIISP = poFileVariantsInfoSP->get_item(iter++);
		}
	}
}

//----------------------------------------------------------------------------------
//  transaction support
//----------------------------------------------------------------------------------

void CSingleServerPlaceCacheInfo::trans_get_or_create_info(long IdFile,SCP<CItemVariantInfo> & rpoFileVariantsInfoSP)
{
	//uwaga! musi mieæ lock na m_oItemInfoCS

	if(!m_oItemVariantInfoMap.Lookup(IdFile,rpoFileVariantsInfoSP))
	{
		rpoFileVariantsInfoSP = NewSCP(new CItemVariantInfo(this));
		m_oItemVariantInfoMap[ IdFile ] = rpoFileVariantsInfoSP;
		CString oSubDirString;
		_get_subdir_for_ivi(IdFile,oSubDirString);
		rpoFileVariantsInfoSP->_set_sub_dir(oSubDirString);
		set_dirty();
	}
}

void CSingleServerPlaceCacheInfo::trans_remove(long IdFile)
{
	//uwaga! musi mieæ lock na m_oItemInfoCS
	VERIFY(m_oItemVariantInfoMap.RemoveKey(IdFile));
	set_dirty();
}

