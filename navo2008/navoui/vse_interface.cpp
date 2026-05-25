/*
	NAVO Enterprise 2008
	2002-12-02

	Virtual Storage Engine

	interface
*/

#include "stdafx.h"
#include "vse_implementation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



vse_interface::vse_interface(SCP<IStream> poStorageStreamSP) :
	m_poImplementation(new vse_impl(poStorageStreamSP))
{
}

vse_interface::~vse_interface()
{
	delete m_poImplementation;
}


void vse_interface::_get_item(itemid nItemId,itemsize & rItemSize,itemdataptr & rItemData)
{
	m_poImplementation->_get_item(nItemId,rItemSize,rItemData);
}

void vse_interface::_put_item(itemid nItemId,const itemsize & rItemSize,citemdataptr & rItemData)
{
	m_poImplementation->_put_item(nItemId,rItemSize,rItemData);
}

bool vse_interface::_exists_item(itemid nItemId)
{
	return m_poImplementation->_exists_item(nItemId);
}

void vse_interface::_delete_item(itemid nItemId)
{
	m_poImplementation->_delete_item(nItemId);
}

