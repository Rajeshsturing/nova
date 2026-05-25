/*
	NAVO Enterprise 2008
	2002-12-02

	Virtual Storage Engine

	implementation
*/

#ifndef _VSE_IMPLEMENTATION_H_
#define _VSE_IMPLEMENTATION_H_

using namespace navo_vse;

const long VSE_BLOCK_SIZE = 256;

typedef unsigned long vse_block_nr;
typedef unsigned long vse_block_count;

class vse_impl
{
public:
	vse_impl(SCP<IStream>	poStreamStorageSP);
	~vse_impl();

	void _get_item(itemid nItemId,itemsize & rItemSize,itemdataptr & rItemData);
	void _put_item(itemid nItemId,const itemsize & rItemSize,citemdataptr & rItemData);
	bool _exists_item(itemid nItemId);
	void _delete_item(itemid nItemId);
private:
	struct cindex_entry
	{
		vse_block_nr	m_block_nr;
		vse_block_count	m_block_count;
	};
	
	vse_block_nr acquire_blocks(vse_block_count nBlockCount);
	void free_blocks(vse_block_nr nFirstBlockNr,vse_block_count nBlockCount);

	long block_nr_2_offset(vse_block_nr nBlockNr) const;
	vse_block_count _size_2_block_count(itemsize nSize) const;
	itemsize _block_count_2_size(vse_block_count nBlockCount) const;

	bool _entry(itemid ItemId,cindex_entry & roEntry);

	CMap<itemid,itemid,cindex_entry,cindex_entry&>	m_oIndexMap;
	
	CArray<char,char>	m_oBlockAllocArray;	//mapa bitowa alokacji bloków

	SCP<IStream>	m_poStreamStorageSP;

#ifdef _DEBUG
	long _debug_total_blocks;
	long _debug_total_bytes;
#endif
};

inline long vse_impl::block_nr_2_offset(vse_block_nr nBlockNr) const
{
	return (nBlockNr * VSE_BLOCK_SIZE);
}

inline vse_block_count vse_impl::_size_2_block_count(itemsize nSize) const
{
	ASSERT(nSize > 0);
	return 1 + (nSize - 1) / VSE_BLOCK_SIZE;
}

inline itemsize vse_impl::_block_count_2_size(vse_block_count nBlockCount) const
{
	ASSERT(nBlockCount > 0);
	return nBlockCount * VSE_BLOCK_SIZE;
}

inline bool vse_impl::_entry(itemid ItemId,cindex_entry & roEntry)
{
	return (m_oIndexMap.Lookup(ItemId,roEntry) != FALSE);
}


#else
	#error __FILE__ already included
#endif

