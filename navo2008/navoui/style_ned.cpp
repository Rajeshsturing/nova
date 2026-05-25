/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
	
	cned_style
		- definicja stylu
*/


#include "stdafx.h"
#include "style_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


cned_style::cned_style() :
	m_oStyleAuthorString(_T("NAVO"))
{
}

cned_styleitem	* cned_style::get_item(long ItemIdent)
{
	SCP<cned_styleitem> poStyleItemSP;
	if(m_oItemMap.Lookup(ItemIdent,poStyleItemSP))
	{
		ASSERT(poStyleItemSP.PointsObject());
		return poStyleItemSP.Get();
	}
	else
	{
		return NULL;
	}
}


void cned_style::add_item(long ItemIdent,SCP<cned_styleitem> poStyleItemSP)
{
	ASSERT(get_item(ItemIdent) == NULL);

	m_oItemMap[ ItemIdent ] = poStyleItemSP;
}


