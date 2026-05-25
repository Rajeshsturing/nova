/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheInfoItem - single item information
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "CacheManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//--------------------------------------------------------------------------------------
//	CCacheInfoItem
//--------------------------------------------------------------------------------------

LPCTSTR CCacheInfoItem::get_suffix()
{
	return _T(".cache");
}

void CCacheInfoItem::write_to_archive(CArchive & roArchive)
{
	roArchive << m_oFileNameString;
	m_oDescriptorArray.Serialize(roArchive);
}

void CCacheInfoItem::read_from_archive(CArchive & roArchive)
{
	roArchive >> m_oFileNameString;
	m_oDescriptorArray.Serialize(roArchive);
}

void CCacheInfoItem::get_full_path(CString & roFullPathString) const
{
	ASSERT(m_poIVI);
	m_poIVI->get_item_full_path(this,roFullPathString);
}

void CCacheInfoItem::write_to_backup_archive(SCP<IStream> poOutStreamSP)
{
	CStreamHolder oSH(poOutStreamSP);

	{
		oSH.WritePascalString(m_oFileNameString);

		long nSize = m_oDescriptorArray.GetSize();

		oSH.Write(&nSize,sizeof(nSize));
		if(nSize != 0)
		{
			oSH.Write(m_oDescriptorArray.GetData(),nSize);
		}

		CString oItemFileNameString;
		get_full_path(oItemFileNameString);

		SCP<IStream> poFileStreamSP = OpenFileStream_Read(oItemFileNameString);
		ASSERT(poFileStreamSP.PointsObject());

		long nStreamLength = GetStreamSize(poFileStreamSP);
		oSH.Write(&nStreamLength,sizeof(nStreamLength));

		ULARGE_INTEGER ulStreamLength;
		ulStreamLength.QuadPart = ULONGLONG(nStreamLength);
		HRESULT hr = IStream_CopyTo(poFileStreamSP,poOutStreamSP,ulStreamLength);

		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_CACHE_BACKUP_WRITE_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
		}
	}
}

void CCacheInfoItem::load_from_backup_archive(SCP<IStream> poInStreamSP)
{
	CStreamHolder oSH(poInStreamSP);

	m_oFileNameString = oSH.ReadPascalString();

	long nSize;
	oSH.Read(&nSize,sizeof(nSize));
	m_oDescriptorArray.SetSize(nSize);
	if(nSize != 0)
	{
		oSH.Read(m_oDescriptorArray.GetData(),nSize);
	}


	CString oItemFileNameString;
	get_full_path(oItemFileNameString);

	CString oPathString = oItemFileNameString.Left(oItemFileNameString.ReverseFind('\\'));
	NavoCreateDirectoryTree(oPathString);

	long nStreamLength;
	oSH.Read(&nStreamLength,sizeof(nStreamLength));
	
	SCP<IStream> poFileStreamSP = CreateFileStream_Write(oItemFileNameString);
	
	ULARGE_INTEGER ulStreamLength;
	ulStreamLength.QuadPart = ULONGLONG(nStreamLength);
	HRESULT hr = IStream_CopyTo(poInStreamSP,poFileStreamSP,ulStreamLength);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_CACHE_RESTORE_READ_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
	}
}


