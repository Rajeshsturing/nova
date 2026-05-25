/*
	NAVO Enterprise 2008
	2002-12-02

	Virtual Storage Engine

	interface
*/

#ifndef _VSE_INTERFACE_H_
#define _VSE_INTERFACE_H_


class vse_impl;

namespace navo_vse
{
	typedef unsigned long	itemsize;		//rozmiar elementu
	typedef void *			itemdataptr;	//wskaünik na dane elementu
	typedef const void *	citemdataptr;	//const wskaünik na dane elementu
	typedef long			itemid;			//identyfikator elementu
	
	class vse_interface
	{
	public:
		vse_interface(SCP<IStream> poStorageStreamSP);
		~vse_interface();

		void _get_item(itemid nItemId,itemsize & rItemSize,itemdataptr & rItemData);
		void _put_item(itemid nItemId,const itemsize & rItemSize,citemdataptr & rItemData);
		bool _exists_item(itemid nItemId);
		void _delete_item(itemid nItemId);
	private:
		vse_impl * m_poImplementation;
	};

	class vse_exception
	{
	public:
		enum eCode
		{
			vseerr_item_not_found_get,
			vseerr_item_not_found_delete,
			vseerr_read_failed,
		};

		vse_exception(eCode code,itemid nItemId) :
			m_eCode(code),
			m_ItemId(nItemId)
		{
		}
		eCode _code() const
		{
			return m_eCode;
		}
	private:
		eCode	m_eCode;
		itemid	m_ItemId;
	};
};

#else
	#error __FILE__ already included
#endif
