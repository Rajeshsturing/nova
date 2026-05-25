/*
	NAVO Enterprise 2001
	common SQL script helper functions
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR ProcedureSuffixOnAction(stdobjactions Action)
{
	switch(Action)
	{
	case action_insert:
		return _T("_insert");
	case action_update:
		return _T("_update");
	case action_delete:
		return _T("_delete");
	case action_get:
		return _T("_select");
	case action_maxid:
		return _T("_maxid");
	case action_candel:
		return _T("_candel");
	default:
		ASSERT(false);
		return _T("");
	}
}

LPCTSTR DelCollectionProcedure()
{
	return _T("navo2001_delcoll");
}

LPCTSTR DelFromCollectionProcedure()
{
	return _T("navo2001_delfromcoll");
}

LPCTSTR MakeOrderCollectionProcedure()
{
	return _T("navo2001_makeordercoll");
}

LPCTSTR MakeSpaceCollectionProcedure()
{
	return _T("navo2001_makespacecoll");
}

LPCTSTR InsertIntoCollectionProcedure()
{
	return _T("navo2001_insertcoll");
}

LPCTSTR OpenCollectionSelect()
{
	return _T("select Collections.IdObj from Collections where Collections.IdCollection=%d and Collections.IdParent=%d order by Collections.lp");
}

LPCTSTR OpenStreamSelect()
{
	return _T("select StreamMap.IdParent from StreamMap where StreamMap.IdMapping=%d and IdStream in (0 %s)");
}

LPCTSTR FindWhereSelect()
{
	return _T("select TOP 3 IdObj from %s where %s");
}

LPCTSTR FindSelect()
{
	return _T("select TOP 3 IdObj from %s");
}

LPCTSTR GetFileCacheGUID()
{
	return _T("navo2001_selectdbid");
}

LPCTSTR InsertFileCacheGUID()
{
	return _T("navo2001_insertdbid");
}

//-------- stream map ------------------------

LPCTSTR DelStreamMapProcedure()
{
	return _T("navo2001_delstrmap");
}

LPCTSTR InsStreamMapProcedure()
{
	return _T("navo2001_insstrmap");
}

LPCTSTR SelStreamMapProcedure()
{
	return _T("navo2001_selstrmap");
}

LPCTSTR UpdStreamMapProcedure()
{
	return _T("navo2001_updstrmap");
}
