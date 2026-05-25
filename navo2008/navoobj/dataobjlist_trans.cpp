/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectList
	transaction support and read/write operations
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "dbapconnparam.h"
#include "dbaccessproxy.h"
#include "dataobject.h"
#include "dataobjlist.h"
#include "dataobjectfile.h"
#include "transrollback.h"
#include "transaction.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void __ReadIdArrayFromFlatData(CFlatData & roFlatData,CArray< long, long &> & roIdentArray)
{
	ASSERT(roFlatData.GetDataPtr());

	PBYTE pMem = roFlatData.GetDataPtr();
	CFlatData::CFDHeader oFDHeader(pMem);
	ASSERT( oFDHeader.Action() == action_lists );
	ASSERT( oFDHeader.TypeId() == TYPEID_COLLECTIONS );
	ASSERT( long(CFlatData::CFDHeader::Size() + sizeof(long) + 
		oFDHeader.IdObj() * sizeof(long)) == oFDHeader.Length());
	ASSERT(oFDHeader.IdObj() > 0 );
	roIdentArray.SetSize(oFDHeader.IdObj());

	pMem += CFlatData::CFDHeader::Size();
	ASSERT(*reinterpret_cast<stdobjlistoperations*>(pMem) == listop_getid);
	
	pMem += sizeof(long);
	memcpy(roIdentArray.GetData(), pMem, oFDHeader.IdObj() * sizeof(long));
}

void CNEO_liststorage::_readbinary(CFlatData & roFlatData)
{
	CArray< long, long &> oIdentArray;
	__ReadIdArrayFromFlatData(roFlatData,oIdentArray);
	long nPersistentSize = oIdentArray.GetSize();
	
	m_oItemArray.SetSize(nPersistentSize);
	for(long iter = 0; iter < nPersistentSize; iter++)
	{
		m_oItemArray[ iter ].m_IdObj = oIdentArray[ iter ];
	}
}

void CNEO_liststorage::_writebinary4save(CFlatData & roFlatData)
{
	ASSERT(!m_bParentMarkDel);
	//LIST_COMPLETE_WRITE
	//obliczanie dlugosci
	long nDataSize = CFlatData::CFDHeader::Size() + sizeof(long);		//for WhatToDo
	long nIdentsByteSize = m_oItemArray.GetSize() * sizeof(long);
	
	//ilosc elementów w ogole + rozmiar danych
	nDataSize +=  sizeof(long) + nIdentsByteSize;

	PBYTE pNewMem = roFlatData.GrowBy(nDataSize);
	CFlatData::CFDHeader oFDHeader(pNewMem);
	oFDHeader.Length() = nDataSize;
	oFDHeader.Action() = action_lists;
	oFDHeader.TypeId() = GetCollectionId();
	oFDHeader.IdObj()  = GetParentId();
	pNewMem += CFlatData::CFDHeader::Size();
	*(long*)pNewMem = (long) listop_save2;
	pNewMem += sizeof(long);
	
	*(long*)pNewMem = (long)m_oItemArray.GetSize(); 
	pNewMem += sizeof(long);

	for(long iter = 0; iter < m_oItemArray.GetSize(); iter++)
	{
		*(long*)pNewMem = m_oItemArray[iter].m_IdObj;
		pNewMem += sizeof(long);
	}

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		CDebuggerCallHolder oDCH;
		oDCH++.StoreMsg("DB:LSAVE [%d:%d]=%d,cnt=%d\n",GetParentTypeid(),GetParentId(),GetCollectionId(),m_oItemArray.GetSize());
	}
#endif
}

void CNEO_liststorage::_writebinary4del(CFlatData & roFlatData)
{
	ASSERT(m_bParentMarkDel);
	//obliczanie dlugosci
	long nDataSize = CFlatData::CFDHeader::Size() + sizeof(long);		//for WhatToDo

	PBYTE pNewMem = roFlatData.GrowBy(nDataSize);
	CFlatData::CFDHeader oFDHeader(pNewMem);
	oFDHeader.Length() = nDataSize;
	oFDHeader.Action() = action_lists;
	oFDHeader.TypeId() = GetCollectionId();
	oFDHeader.IdObj()  = GetParentId();
	pNewMem += CFlatData::CFDHeader::Size();
	*(long*)pNewMem = (long) listop_delcollection;
	pNewMem += sizeof(long);

#ifdef _DEVELOPER_EDITION_
	if(GetDebugOptions().IsTraceAutoCalls())
	{
		CDebuggerCallHolder oDCH;
		oDCH++.StoreMsg("DB:LDEL [%d:%d]=%d\n",GetParentTypeid(),GetParentId(),GetCollectionId());
	}
#endif
}


SCP<CNEO_liststorage> CNEO_liststorage::clone()
{
	ASSERT(m_poParentDefinition != NULL);

	SCP<CNEO_liststorage> poListStorageSP = NewSCP(new CNEO_liststorage(
		NULL,m_CollectionId,m_IdParent,m_ChildTypeId,m_bParentIsNew,m_poParentDefinition));
	
	poListStorageSP->_copy_from(*this);
	poListStorageSP->m_bParentMarkDel = m_bParentMarkDel;
	return poListStorageSP;
}

void CNEO_liststorage::_copy_from(const CNEO_liststorage & roListStorage)
{
	ASSERT(m_CollectionId == roListStorage.m_CollectionId);
	ASSERT(m_IdParent == roListStorage.m_IdParent);
	ASSERT(m_ChildTypeId == roListStorage.m_ChildTypeId);
	ASSERT(m_poParentDefinition == roListStorage.m_poParentDefinition);

	m_oItemArray.Copy(roListStorage.m_oItemArray);

	m_eNeedSave = roListStorage.m_eNeedSave;
	m_eUserModif = roListStorage.m_eUserModif;
}

bool CNEO_liststorage::full_is_usermodified(const CNEO_liststorage & roListStorage)
{
	ASSERT(m_eUserModif == um_unknown);
	if(full_is_needsave(roListStorage))
	{
		m_eUserModif = um_yes;
		return true;
	}
	else
	{
		m_eUserModif = um_no;
		return false;
	}
}

bool CNEO_liststorage::full_is_needsave(const CNEO_liststorage & roListStorage)
{
	ASSERT(m_CollectionId == roListStorage.m_CollectionId);
	ASSERT(m_IdParent == roListStorage.m_IdParent);
	ASSERT(m_ChildTypeId == roListStorage.m_ChildTypeId);
	
	ASSERT(m_eNeedSave == ns_unknown);
	if(m_bParentMarkDel)
	{
		if(m_bParentIsNew)
		{
			m_eNeedSave = ns_no;
			return false;
		}
		else
		{
			m_eNeedSave = ns_yes;
			return true;
		}
	}
	if(m_oItemArray.GetSize() != roListStorage.m_oItemArray.GetSize())
	{
		m_eNeedSave = ns_yes;
		return true;
	}
	for(long iter = 0; iter < m_oItemArray.GetSize(); iter++)
	{
		if(m_oItemArray[iter].m_IdObj != roListStorage.m_oItemArray[iter].m_IdObj)
		{
			m_eNeedSave = ns_yes;
			return true;
		}
	}
	m_eNeedSave = ns_no;
	return false;
}

void CNEO_liststorage::_postprocess()
{
	m_eNeedSave = ns_no;
	m_eUserModif = um_no;
	m_bParentMarkDel = false;
	m_bParentIsNew = false;

	TRACE("postprocessed liststorage: [%d:%d]=%d\n",GetParentTypeid(),GetParentId(),GetCollectionId());
}
















