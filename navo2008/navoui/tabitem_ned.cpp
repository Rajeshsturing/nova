/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabitem / <tabitem>
		
		element <tab>'a 
*/

#include "stdafx.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "tabitem_ned.h"
#include "tabmanager_header_ned.h"
#include "tabmanager_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------
SCP<cned_tabmanager> cned_tabmanager_item::_get_manager()
{
	return scp_cast_ui<cned_tabmanager>(get_container());
}

//------ property GET -----------------
ng_string cned_tabmanager_item::get_prop_title()
{
	return _get_manager()->get_item_title(get_ident());
}


//------ property SET -----------------
void cned_tabmanager_item::set_prop_title(const ng_string & roTitleString)
{
	_get_manager()->set_item_title(get_ident(),roTitleString);
}

