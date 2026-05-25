/*
	NAVO Enterprise 2008
	2002-12-02

	Virtual Storage Engine

	implementation
*/

#include "stdafx.h"
#include "vse_implementation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


vse_impl::vse_impl(SCP<IStream>	poStreamStorageSP):
	m_poStreamStorageSP(poStreamStorageSP)
{
	ASSERT(poStreamStorageSP.PointsObject());

	m_oBlockAllocArray.Add('\0');

#ifdef _DEBUG
	_debug_total_blocks = 0;
	_debug_total_bytes = 0;
#endif
}

vse_impl::~vse_impl()
{
#ifdef _DEBUG
	TRACE("---------------VSE Stats---------------\n");
	TRACE("total bytes stored %d\n",_debug_total_bytes);
	TRACE("total blocks stored %d\n",_debug_total_blocks);
	
	long nFillRatio = 0;
	if(_debug_total_blocks != 0)
	{
		nFillRatio = 100 * _debug_total_bytes / _debug_total_blocks / VSE_BLOCK_SIZE;
	}

	TRACE("fill ratio %d\n",nFillRatio);
	TRACE("---------------------------------------\n");
#endif
}

void vse_impl::_get_item(itemid nItemId,itemsize & rItemSize,itemdataptr & rItemData)
{
	cindex_entry oEntry;
	if(!_entry(nItemId,oEntry))
	{
		throw navo_vse::vse_exception(navo_vse::vse_exception::vseerr_item_not_found_get,nItemId);
	}
	CStreamHolder oSH(m_poStreamStorageSP);
	oSH.Seek(block_nr_2_offset(oEntry.m_block_nr),STREAM_SEEK_SET);
	if(oSH.Read(&rItemSize,sizeof(rItemSize)) != sizeof(rItemSize))
	{
		throw navo_vse::vse_exception(navo_vse::vse_exception::vseerr_read_failed,nItemId);
	}
	ASSERT(rItemSize <= _block_count_2_size(oEntry.m_block_count));
	rItemData = new char[ rItemSize ];
	if(oSH.Read(rItemData,rItemSize) != rItemSize)
	{
		throw navo_vse::vse_exception(navo_vse::vse_exception::vseerr_read_failed,nItemId);
	}
}

void vse_impl::_put_item(itemid nItemId,const itemsize & rItemSize,citemdataptr & rItemData)
{
	cindex_entry oEntry;

#ifdef _DEBUG
	_debug_total_blocks += _size_2_block_count(sizeof(rItemSize) + rItemSize);
	_debug_total_bytes += sizeof(rItemSize) + rItemSize;
#endif

	if(_entry(nItemId,oEntry))
	{
		//update "in-place"
		if(_size_2_block_count(sizeof(rItemSize) + rItemSize) == oEntry.m_block_count)
		{
			//write
			CStreamHolder oSH(m_poStreamStorageSP);
			oSH.Seek(block_nr_2_offset(oEntry.m_block_nr),STREAM_SEEK_SET);
			oSH.Write(&rItemSize,sizeof(rItemSize));
			oSH.Write(rItemData,rItemSize);
			return;
		}
		else
		{
			//free blocks
			free_blocks(oEntry.m_block_nr,oEntry.m_block_count);
		}
	}

	//acquire blocks
	oEntry.m_block_count = _size_2_block_count(sizeof(rItemSize) + rItemSize);
	oEntry.m_block_nr = acquire_blocks(oEntry.m_block_count);
	//write
	CStreamHolder oSH(m_poStreamStorageSP);
	oSH.Seek(block_nr_2_offset(oEntry.m_block_nr),STREAM_SEEK_SET);
	oSH.Write(&rItemSize,sizeof(rItemSize));
	oSH.Write(rItemData,rItemSize);
	//update index
	m_oIndexMap[ nItemId ] = oEntry;
}

bool vse_impl::_exists_item(itemid nItemId)
{
	cindex_entry oDummyEntry;
	return _entry(nItemId,oDummyEntry);
}

void vse_impl::_delete_item(itemid nItemId)
{
	cindex_entry oEntry;
	if(!_entry(nItemId,oEntry))
	{
		throw navo_vse::vse_exception(navo_vse::vse_exception::vseerr_item_not_found_delete,nItemId);
	}
	
	free_blocks(oEntry.m_block_nr,oEntry.m_block_count);
}

vse_block_nr vse_impl::acquire_blocks(vse_block_count nBlockCount)
{
	ASSERT(nBlockCount > 0);
	ASSERT(m_oBlockAllocArray.GetUpperBound() >= 0);
	ASSERT(m_oBlockAllocArray[m_oBlockAllocArray.GetUpperBound()] == '\0');

	CString oFreeBlockString('0',nBlockCount);
	char * pFoundBlockPtr = strstr(m_oBlockAllocArray.GetData(),oFreeBlockString);
	
	if(pFoundBlockPtr != NULL)
	{
		vse_block_nr nBlockNr = (pFoundBlockPtr - m_oBlockAllocArray.GetData());
		memset(pFoundBlockPtr,'1',nBlockCount);

		ASSERT(m_oBlockAllocArray[m_oBlockAllocArray.GetUpperBound()] == '\0');

		return nBlockNr;
	}
	
	//no free space - expand and alloc
	vse_block_nr nBlockNr = m_oBlockAllocArray.GetSize() - 1;
	m_oBlockAllocArray.InsertAt(nBlockNr,'1',nBlockCount);

	ASSERT(m_oBlockAllocArray.GetUpperBound() >= 0);
	ASSERT(m_oBlockAllocArray[m_oBlockAllocArray.GetUpperBound()] == '\0');

	return nBlockNr;
}

void vse_impl::free_blocks(vse_block_nr nFirstBlockNr,vse_block_count nBlockCount)
{
	memset(m_oBlockAllocArray.GetData() + nFirstBlockNr,'0',nBlockCount);

	ASSERT(m_oBlockAllocArray.GetUpperBound() >= 0);
	ASSERT(m_oBlockAllocArray[m_oBlockAllocArray.GetUpperBound()] == '\0');
}


