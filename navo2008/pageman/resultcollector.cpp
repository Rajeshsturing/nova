/*
	NAVO Sp. z o.o. (2002)
	
	NAVO Enterprise

	class:
		CResultCollector - zbiera rezultaty wykonania akcji
*/

#include "stdafx.h"
#include "resultcollector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CResultCollector::CResultCollector()
{
	EnableAutomation();
	Reset();
}

CResultCollector::CResultCollector(const CResultCollector & roResultCollector)
{
	EnableAutomation();
	Reset();
	m_bActivePageChanged = roResultCollector.m_bActivePageChanged;
}

CResultCollector::~CResultCollector()
{
	Reset();
}

void CResultCollector::Reset()
{
	m_bActivePageChanged = false;
}

//{{AFX_MSG_MAP(CResultCollector)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CResultCollector, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CResultCollector)
	DISP_FUNCTION(CResultCollector, "ispagechanged", IsPageChangedAUTO, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


BOOL CResultCollector::IsPageChangedAUTO() 
{
	return (m_bActivePageChanged != false);
}
