/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManager - local cache manager, data part
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
//	CCacheManager
//--------------------------------------------------------------------------------------


void CCacheManager::_write_all()
{
	CSimpleLock oSimpleLock(m_oGlobalCS);
#ifdef _DEBUG
	CDebugTimeMeter oDTM("_write_all");
#endif

	_write_global_info();

	POSITION pos = m_oGlobalMap.GetStartPosition();
	while(pos)
	{
		CString oDummyString;
		SCP<CSingleServerPlaceCacheInfo> poSSPCISP;
		m_oGlobalMap.GetNextAssoc(pos,oDummyString,poSSPCISP);
		poSSPCISP->_write_info();
	}
}

void CCacheManager::_pending_delete()
{
	CSimpleLock oSimpleLock(m_oPendDelCS);
	for(long iter = 0; iter <= m_oPendingDeleteFileArray.GetUpperBound();)
	{
		if(!NavoDeleteFile(m_oPendingDeleteFileArray[iter]))
		{
			iter++;
		}
		else
		{
			m_oPendingDeleteFileArray.RemoveAt(iter);
		}
	}
}
