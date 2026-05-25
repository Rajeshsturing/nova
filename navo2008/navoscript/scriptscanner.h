/*
	NAVO Enterprise (2001)
	
	Script Code Scanner

	scans script for function (sub) names and marks which is sub (function)
*/

#ifndef _SCRIPT_SCANNER_H_
#define _SCRIPT_SCANNER_H_

const DISPID DISPID_NONE = -1;

struct CFunctionInfo
{
	CFunctionInfo():
		m_bFunction(false),
		m_dispid(DISPID_NONE)
	{
	}
	CFunctionInfo(const CString & roString,bool bFunction):
		m_oNameString(roString),
		m_bFunction(bFunction),
		m_dispid(DISPID_NONE)
	{
	}
	CFunctionInfo(const CFunctionInfo & roFunctionInfo) :
		m_oNameString(roFunctionInfo.m_oNameString),
		m_bFunction(roFunctionInfo.m_bFunction),
		m_dispid(roFunctionInfo.m_dispid)
	{
	}
	virtual void operator = (const CFunctionInfo & roFunctionInfo)
	{
		m_oNameString	= roFunctionInfo.m_oNameString;
		m_bFunction		= roFunctionInfo.m_bFunction;
		m_dispid		= roFunctionInfo.m_dispid;
	}
	CString m_oNameString;
	bool	m_bFunction;	//false == Sub
	DISPID	m_dispid;
};

typedef CArray<CFunctionInfo,CFunctionInfo&> CFunctionInfoArray;

void ScanScriptForProcedures(LPCTSTR lpScriptCode, CFunctionInfoArray & roFunctionInfoArray,
							 LPCTSTR lpRequiredPrefix = NULL);

#else
	#error __FILE__ already included
#endif
