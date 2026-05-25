
/*
	intermediate include for event handler functions
	eh_*_ndoc
*/

#ifndef _EH_COMMON_INC_NDOC_H_
#define _EH_COMMON_INC_NDOC_H_

#include "..\navopx\navopx.h"
#include "..\include\H1000.h"
#include "..\include\H1001.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\flatdata.h"		//flat data structure
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navogal\ngal_iface.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"
#include "..\navoui\element_nedaw.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"

using namespace ned;

#include "event_handler_ndoc.h"


#else
	#error __FILE__ already included
#endif
