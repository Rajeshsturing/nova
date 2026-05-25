/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CItemVariantInfo - item information
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
//	CItemVariantInfo
//--------------------------------------------------------------------------------------
void CItemVariantInfo::write_to_archive(CArchive & roArchive)
{
	roArchive << m_oSubDirString << m_oNSI << m_oVariantsArray.GetSize();
	for(long iter = 0; iter < m_oVariantsArray.GetSize(); iter++)
	{
		m_oVariantsArray[iter]->write_to_archive(roArchive);
	}
}

void CItemVariantInfo::read_from_archive(CArchive & roArchive)
{
	long nSize;
	roArchive >> m_oSubDirString  >> m_oNSI >> nSize;
	m_oVariantsArray.SetSize(nSize);
	for(long iter = 0; iter < nSize; iter++)
	{
		SCP<CCacheInfoItem> poCacheInfoItemSP = NewSCP(new CCacheInfoItem(this));
		m_oVariantsArray[iter] = poCacheInfoItemSP;
		poCacheInfoItemSP->read_from_archive(roArchive);
	}
}

long CItemVariantInfo::_find(long DescriptorLength,BYTE * pcDescriptor)
{
	for(long iter = 0; iter <= m_oVariantsArray.GetUpperBound(); iter++)
	{
		if(m_oVariantsArray[iter]->compare(DescriptorLength,pcDescriptor))
		{
			return iter;
		}
	}
	return -1;
}

bool CItemVariantInfo::get_info(long DescriptorLength,BYTE * pcDescriptor,SCP<CCacheInfoItem> & rpoCacheItemInfoSP)
{
	ASSERT(m_poSSI);
	CSimpleLock oSimpleLock(m_poSSI->_get_atom_cs());
	long Index = _find(DescriptorLength,pcDescriptor);
	if(Index != -1)
	{
		rpoCacheItemInfoSP = m_oVariantsArray[Index];
		return true;
	}
	else
	{
		return false;
	}
}

void CItemVariantInfo::get_item_full_path(const CCacheInfoItem * poCII,CString & roFullPathString) const
{
	ASSERT(m_poSSI);
	m_poSSI->get_item_full_path(this,poCII,roFullPathString);
}

SCP<CCacheInfoItem> CItemVariantInfo::get_item(long nIndex)
{
	if(nIndex <= m_oVariantsArray.GetUpperBound() && nIndex >= 0)
	{
		return m_oVariantsArray[ nIndex ];
	}
	return SCP<CCacheInfoItem>();
}

void CItemVariantInfo::supply_extension(CString & roPathString,bool bBlobDB,const navostreaminfo & roNSI)
{
	if(bBlobDB)
	{
		if(roNSI.m_cExt[0] != '\0')
		{
			roPathString += "." + CString(roNSI.m_cExt);
		}
		else
		{
			roPathString += ".unk";
		}
	}
	else
	{
		roPathString += CCacheInfoItem::get_suffix();
	}
}

//----------------------------------------------------------------------------------
//transaction support
//----------------------------------------------------------------------------------

bool CItemVariantInfo::trans_get_or_create_info(long DescriptorLength,BYTE * pcDescriptor,SCP<CCacheInfoItem> & rpoCacheItemInfoSP)
{
	ASSERT(m_poSSI);
	ASSERT(rpoCacheItemInfoSP.PointsNull());
	
	CSimpleLock oSimpleLock(m_poSSI->_get_atom_cs());

	long Index = _find(DescriptorLength,pcDescriptor);
	
	if(Index != -1)
	{
		rpoCacheItemInfoSP = m_oVariantsArray[Index];
	}
	else
	{
		SCP<CCacheInfoItem> poCIISP = NewSCP(new CCacheInfoItem(this));
		poCIISP->set_descriptor(DescriptorLength,pcDescriptor);
		m_oVariantsArray.Add(poCIISP);
		rpoCacheItemInfoSP = poCIISP;
		m_poSSI->set_dirty(this);
	}
	
	ASSERT(rpoCacheItemInfoSP.PointsObject());
	return (Index != -1);
}

bool CItemVariantInfo::trans_remove(long DescriptorLength,BYTE * pcDescriptor)
{
	ASSERT(m_poSSI);
	CSimpleLock oSimpleLock(m_poSSI->_get_atom_cs());

	long Index = _find(DescriptorLength,pcDescriptor);
	if(Index != -1)
	{
		m_oVariantsArray.RemoveAt(Index);
		return true;
	}
	return false;
}

void CItemVariantInfo::write_to_backup_archive(SCP<IStream> poOutStreamSP)
{
	CStreamHolder oSH(poOutStreamSP);

	{
		oSH.WritePascalString(m_oSubDirString);
		oSH.Write(&m_oNSI,sizeof(m_oNSI));
		long nCount = m_oVariantsArray.GetSize();
		oSH.Write(&nCount,sizeof(nCount));

		for(long iter = 0; iter < nCount; iter++)
		{
			m_oVariantsArray[iter]->write_to_backup_archive(poOutStreamSP);
		}
	}
}

void CItemVariantInfo::load_from_backup_archive(SCP<IStream> poInStreamSP)
{
	CStreamHolder oSH(poInStreamSP);

	m_oSubDirString = oSH.ReadPascalString();
	oSH.Read(&m_oNSI,sizeof(m_oNSI));
	long nCount;
	oSH.Read(&nCount,sizeof(nCount));

	m_oVariantsArray.SetSize(nCount);
	for(long iter = 0; iter < nCount; iter++)
	{
		SCP<CCacheInfoItem> poCacheInfoItemSP = NewSCP(new CCacheInfoItem(this));
		m_oVariantsArray[iter] = poCacheInfoItemSP;
		poCacheInfoItemSP->load_from_backup_archive(poInStreamSP);
	}
}

