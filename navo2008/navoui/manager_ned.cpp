/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
		- manager_elementów

	- dostarcza elementy / swapuje unswapuje elementy
	- dostarcza ró¿ne providery (style, picture itd.)
*/

#include "stdafx.h"
#include "arena_manager_ned.h"
#include "style_ned.h"
#include "element_nedaw.h"
#include "commandlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
	ARmania - explanation

	cned_element can exist but be not used (!interface_has_references()) - in this situation its m_poManager member is NULL,
	and element doesn't references manager.
	while used element _reincarnates_ and AddRefs manager to keep it alive.
	while element is finally released it releases managar to and has m_poManager member zeroed.

	this behaviour is necessery, because element can have external references from script, so it must 
	keep manager working.
*/
//---------------------------------------------------------------------------------------
//-------------------------------- construction - destruction ---------------------------
//---------------------------------------------------------------------------------------

cned_element_manager::cned_element_manager(cned_arena_manager * poArenaManager) :
	m_nAutoIdent(FIRST_AUTOIDENT),
	m_bSysDisabled(false),
	m_idFocus(NEDID_NOTHING),
	m_idOldFocus(NEDID_NOTHING),
	m_idMouseOver(NEDID_NOTHING),
	m_poArenaManager(poArenaManager),
	m_bQuitting(false),
	m_nTransferIterator(-1),
	m_poVSE(NULL),
	m_bWasElementWithStdScriptSupport(false),
	m_bSwappingEnabled(false),
	m_bModifiedFlag(true),
	m_nFormFeedCount(0)
{
#ifdef _DEBUG
	_debug_m_nTotalRequests = 0;
	_debug_m_nMaxRequests = 0;
#endif

	//initialize interlnal GrowBy
	m_oFixedIdElementArray.SetSize(0,512);
	m_oAutoIdElementArray.SetSize(0,4096);
	m_oHighIdElementArray.SetSize(0,4096);

	m_oNEDAWMap.InitHashTable(97);
	m_oPaintRectMap.InitHashTable(2003);

	//-------- init for default font ----------------
	ned_font_spec oDefaultFontSpec;
	oDefaultFontSpec.make_normal();
	oDefaultFontSpec.m_nSize			= 3;
	oDefaultFontSpec.m_oFontNameString	= _T("Segoe UI Light");

	ng_string oFontDescString;
	oDefaultFontSpec.to_string(oFontDescString);

	m_oFontInxMap[ oFontDescString ] = NED_DEFAULT_FONT_INX;
	m_oFontArray.SetAtGrow(long(NED_DEFAULT_FONT_INX),FontWithDescription(oDefaultFontSpec,SCP<ng_font>()));

}

cned_element_manager::~cned_element_manager()
{
	_clean_all();

	if(m_oTimerRegisteredArray.GetSize() != 0)	//coœ siê nie wyrejestrowa³o
	{
		m_poArenaManager->release_control_timer_ref();
	}

#ifdef _DEBUG
	TRACE("--------------- font cache stats ----------------------\r\n");
	TRACE("font count %d\r\n",m_oFontArray.GetSize());
	TRACE("-------------------------------------------------------\r\n");
#endif

	delete m_poVSE;
}

void cned_element_manager::_clean_all()
{
	m_bQuitting = true;

	//internal_cleanup dla wszystkich elementów
	_clean_array(m_oFixedIdElementArray);
	_clean_array(m_oAutoIdElementArray);
	_clean_array(m_oHighIdElementArray);

	//wyczyszczenie mapy i delete
	_clean_array2(m_oFixedIdElementArray);
	_clean_array2(m_oAutoIdElementArray);
	_clean_array2(m_oHighIdElementArray);

	m_bQuitting = false;
}

//------------ swapping settings ---------------------------
void cned_element_manager::enable_swapping(bool bEnable)
{
	m_bSwappingEnabled = bEnable;

	if(m_bSwappingEnabled && (m_poVSE == NULL))
	{
#ifdef _DEBUG
		{
			CString oString;
			oString.Format("c:\\navo2001\\exe\\Debug\\System\\swap_%x.bin",long(this));
			
			m_poVSE = new navo_vse::vse_interface(
				OpenFileStream(oString,false,GENERIC_READ|GENERIC_WRITE,0,CREATE_ALWAYS));
		}
#else
		m_poVSE = new navo_vse::vse_interface(CreateTempFileStream());
#endif
	}
}

void cned_element_manager::_clean_array(CArray<cned_element_entry,cned_element_entry & > & roArray)
{
	for(long iter = 0; iter <= roArray.GetUpperBound(); iter++)
	{
		cned_element_entry & roEntry = roArray[iter];
		if(roEntry.m_poElement != NULL)
		{
			roEntry.m_poElement->__internal_cleanup();
		}
	}
}

void cned_element_manager::_clean_array2(CArray<cned_element_entry,cned_element_entry & > & roArray)
{
	for(long iter = 0; iter <= roArray.GetUpperBound(); iter++)
	{
		cned_element_entry & roEntry = roArray[iter];
		if(roEntry.m_poElement != NULL)
		{
			if(!roEntry.m_poElement->interface_has_references())
			{
				delete roEntry.m_poElement;
				roEntry.m_poElement = NULL;
			}
		}
	}
}

//---------------------------------------------------------------------------------------
// element management
//---------------------------------------------------------------------------------------
inline static bool is_swapable(ened_element_type eType)
{
	switch(eType)
	{
	case ned_static:
	case ned_tablecell:
		return true;
	default:
		return false;
	}
}

void cned_element_manager::on_element_finalrelease(cned_element * poElement)
{
	ASSERT(poElement);
	ASSERT(poElement->get_ident() != NEDID_NOTHING);

	ASSERT(!poElement->interface_has_references());

	poElement->m_poManager = NULL;

	if(!m_bQuitting)
	{
		cned_element_entry & roEntry = _entry(poElement->get_ident());

		ASSERT(roEntry.m_poElement == poElement);
		
		//update mini info
		ned_element_mini_info & roMiniInfo = roEntry.m_oMiniInfo;
		roMiniInfo = poElement->m_oMiniInfo;

		if(roMiniInfo.is_deletenow())
		{
			__destroy_element(poElement);
		}
		else
		{
			if(is_swapping_enabled())
			{
				//nie swapuje 'widocznych'
				if(!(roEntry.m_bPaintRect0 || roEntry.m_bPaintRect1))
				{
					ned_ident idElement = poElement->get_ident();
					if(is_swapable(poElement->get_type()))
					{
						if(poElement->_is_vse_dirty())
						{
							//ned_todo:
							//first put in queue of "ready to swap"
							//and swap only if queue grows to much

							//if qualifies to swapping
							//swap to storage
							cned_storage_writer oStorageWriter;
							poElement->save(oStorageWriter);
							{
								const void * pData = oStorageWriter._data();
								const long nSize = oStorageWriter._size();
								m_poVSE->_put_item(idElement,nSize,pData);
								poElement->_vse_clean();
							}
						}
						
#ifdef _DEBUG
						{
							navo_vse::itemsize nSize;
							navo_vse::itemdataptr pData;
							m_poVSE->_get_item(idElement,nSize,pData);
							delete pData;
						}
#endif
						
						//delete - already SWAPped - now or previousely
						poElement->__internal_cleanup();
						delete poElement;
						roEntry.m_poElement = NULL;
					}
				}
			}
		}
	}
	else
	{
		//TRACE("EQFR %d\n",poElement->get_ident());
	}

	//ARmania - see comments at start

	Release();
}

SCP<cned_element> cned_element_manager::__reincarnate_element(cned_element * poElement) const
{
	//ARmania - see comments at start
	ASSERT(poElement != NULL);
	if(poElement->m_poManager == NULL)
	{
		ASSERT(!poElement->interface_has_references());
		poElement->m_poManager = const_cast<cned_element_manager*>(this);
		const_cast<cned_element_manager*>(this)->AddRef();
	}
	return NewSCP(poElement,true);
}

SCP<cned_element> cned_element_manager::get_element_on_ident(const ned_ident Ident) const
{
	const cned_element_entry * poEntry = _safe_entry(Ident);
	if(poEntry == NULL)
	{
		return SCP<cned_element>();	//po prostu nie ma
	}
	
	const ned_element_mini_info & roMiniInfo = (poEntry->m_poElement == NULL) ? poEntry->m_oMiniInfo : poEntry->m_poElement->_mini_info();

	ASSERT(roMiniInfo.get_type() != ned_none);

	if(roMiniInfo.is_deletenow())
	{
#ifdef _DEVELOPER_EDITION_
		AfxMessageBox(
		"Próbujesz pobraæ element zaznaczony do skasowania o id=" + Long2String(Ident) + 
		". Najczêœciej jest to zwi¹zane z przechowywaniem referencji do elementu w zmiennej globalnej"
		);
#endif
		return SCP<cned_element>();	//zaznaczony do skasowania - raportuj ¿e nie ma
	}

	if(poEntry->m_poElement == NULL)	//is SWAPped - reload from storage
	{
		//ned_todo: may be in queue - check it fist
		//then try reload from swap
		ASSERT(m_poVSE != NULL);
		SCP<cned_element> poElementSP = const_cast<cned_element_manager*>(this)->__construct_element(poEntry->m_oMiniInfo.get_type(),Ident);
		navo_vse::itemsize nSize;
		navo_vse::itemdataptr pData;
		m_poVSE->_get_item(Ident,nSize,pData);
			
			//restore element from disk
			cned_storage_reader oStorageRead((const char *)pData);
			poElementSP->load(oStorageRead);
			poElementSP->_vse_clean();
			poElementSP->m_oMiniInfo = poEntry->m_oMiniInfo;
		
		delete pData;

		const_cast<cned_element_entry*>(poEntry)->m_poElement = poElementSP.Get();
		const_cast<cned_element_manager*>(this)->AddRef();
		return poElementSP;
	}
	
	return __reincarnate_element(poEntry->m_poElement);
}

void cned_element_manager::_add_new_element(SCP<cned_element> poNewElementSP)
{
	ASSERT(poNewElementSP.PointsObject());
	ASSERT(poNewElementSP->m_poManager == this);

	long nMappedId = _map_ident(poNewElementSP->get_ident());

	CArray<cned_element_entry,cned_element_entry & > & roArray = _array(poNewElementSP->get_ident());
	
	if(nMappedId <= roArray.GetUpperBound())
	{
		//wykrywanie duplikatów w _create_element zawiod³o ?
		ASSERT(roArray[ nMappedId ].m_oMiniInfo.get_type() == ned_none);
	}
	else
	{
		roArray.SetSize(1 + nMappedId);
	}

	ASSERT(nMappedId <= roArray.GetUpperBound());

	roArray[ nMappedId ].m_poElement = poNewElementSP.Get();
	roArray[ nMappedId ].m_oMiniInfo = poNewElementSP->m_oMiniInfo;

	//ARmania - see comments at start
	AddRef();
}

void cned_element_manager::_remove_element(const ned_ident Ident)
{
	cned_element_entry & roEntry = _entry(Ident);

	//zdejmij focus i inne takie z elementu który jest usuwany
	if(m_idFocus == Ident)
	{
		m_idFocus = NEDID_NOTHING;
	}
	if(m_idOldFocus == Ident)
	{
		m_idOldFocus = NEDID_NOTHING;
	}
	if(m_idMouseOver == Ident)
	{
		m_idMouseOver = NEDID_NOTHING;
	}

	//zaznacz ¿e ma siê usun¹æ przy pierwszej okazji (final release)
	if(roEntry.m_poElement != NULL)
	{
		{
			SCP<cned_element> poElementSP = __reincarnate_element(roEntry.m_poElement);

			poElementSP->_on_remove_element();
			/*
				jeœli element jest nieu¿ywany poza nami to set_delete_now
				spowoduje ¿e w on_final_release zostanie wywo³ane __destroy_element
			*/
			poElementSP->_mini_info().set_delete_now();
		}
	}
	else
	{
		roEntry.m_oMiniInfo.set_delete_now();
	}
}

void cned_element_manager::__destroy_element(cned_element * poElement)
{
	ASSERT(poElement != NULL);
	ASSERT(!poElement->interface_has_references());
	ASSERT(poElement->_mini_info().is_deletenow());

	long nHashedId = _pre_hash(poElement->get_ident());
	
	set_transfer(poElement->get_ident(),SCP<nui_transfer>());

	m_oShortKeyMap.RemoveKey(nHashedId);	//remove shortkey if exists
	m_oToolTipMap.RemoveKey(nHashedId);
	m_oHelpTextMap.RemoveKey(nHashedId);
	m_oDeclPositionMap.RemoveKey(nHashedId);

	//remove from timer registrations
	for(long iter = 0; iter < m_oTimerRegisteredArray.GetSize(); iter++)
	{
		if(m_oTimerRegisteredArray[iter].m_idElement == poElement->get_ident())
		{
			m_oTimerRegisteredArray.RemoveAt(iter);
			break;
		}
	}
	if(poElement->get_type() == ned_breakpage)
	{
		m_nFormFeedCount--;
		ASSERT(m_nFormFeedCount >=0);
	}
	cned_element_entry & roEntry = _entry(poElement->get_ident());
	roEntry.m_oMiniInfo._set_type(ned_none);
	roEntry.m_poElement = NULL;

	ASSERT(get_focus_element() != poElement->get_ident());
	//TRACE("NUI ELEMENT %d DELETED\n",poElement->get_ident());
	delete poElement;
}

ned_ident cned_element_manager::_generate_ident()
{
	return ++m_nAutoIdent;
}


SCP<cned_element> cned_element_manager::_create_element(ened_element_type eType,const ned_ident idNewElement)
{
	//check range
	if(idNewElement >= FIRST_AUTOIDENT && idNewElement < FIRST_HIGHIDENT)
	{
		CString oString;
		oString.Format("Identyfikator %d zastrze¿onego zakresu\n",idNewElement);
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,oString);
	}
	
	//generate new ident when needed
	ned_ident nNewIdent = (idNewElement == NEDID_NOTHING) ? _generate_ident() : idNewElement;
	ASSERT(nNewIdent != NEDID_NOTHING);

#ifdef _DEVELOPER_EDITION_

	//check for duplicates
	{
		long nMappedId = _map_ident(nNewIdent);
		CArray<cned_element_entry,cned_element_entry & > & roArray = _array(nNewIdent);
		if(nMappedId <= roArray.GetUpperBound())
		{
			if(roArray[ nMappedId ].m_oMiniInfo.get_type() != ned_none)
			{
				CString oString = "Ta strona zawiera ju¿ element o id=" + Long2String(nNewIdent);
				
				ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
			}
		}
	}

#endif

	//create element
	SCP<cned_element> poElementSP = __construct_element(eType,nNewIdent);

	//add to storage
	_add_new_element(poElementSP);

	return poElementSP;
}


//------- nedaw element support -----------------
SCP<nedaw::cnedaw_element> construct_nedaw(SCP<ned::cned_element> poElementSP);

SCP<nedaw::cnedaw_element> cned_element_manager::get_nedaw(ned_ident idElement)
{
	long nHashedId = _pre_hash(idElement);
	nedaw::cnedaw_element * pNEDAWElement = NULL;
	if(m_oNEDAWMap.Lookup(nHashedId,pNEDAWElement))
	{
		return NewSCP(pNEDAWElement,true);
	}
	
	SCP<nedaw::cnedaw_element> pNEDAWElementSP = construct_nedaw(get_element_on_ident(idElement));

	ASSERT(pNEDAWElementSP.PointsObject());
	m_oNEDAWMap[ nHashedId ] = pNEDAWElementSP.Get();
	return pNEDAWElementSP;
}

void cned_element_manager::on_nedaw_final_release(ned_ident idElement,nedaw::cnedaw_element * poElement)
{
	long nHashedId = _pre_hash(idElement);
	VERIFY(m_oNEDAWMap.RemoveKey(nHashedId));
	delete poElement;
}

//----------- transfer iterator ------------------------
bool cned_element_manager::next_transfer_iterator(ned_ident & ridElement,SCP<nui_transfer> & rpoTransferSP)
{
	m_nTransferIterator++;
	while(m_nTransferIterator <= m_oTransferArray.GetUpperBound())
	{
		ned_ident nIdent = _post_hash(m_oTransferArray[m_nTransferIterator].m_nHashedId);
		if(!is_element_in_hidden_tree(nIdent))
		{
			ridElement = nIdent;
			rpoTransferSP = m_oTransferArray[m_nTransferIterator].m_poTransferSP;
			return true;
		}
		m_nTransferIterator++;
	}
	return false;
}


