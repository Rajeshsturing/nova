/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Internal debugger and tracing system support
*/

#ifndef _IDTSS_H_
#define _IDTSS_H_


class CDebugOptions
{
public:
	CDebugOptions();
	bool IsTraceAutoCalls() const
	{
		return m_bAutoCalls;
	}
	void SetTraceAutoCalls(bool bOn)
	{
		m_bAutoCalls = bOn;
	}
	bool IsTraceExceptions() const
	{
		return m_bExceptions;
	}
	void SetTraceExceptions(bool bOn)
	{
		m_bExceptions = bOn;
	}
	bool IsTraceEventsNoGetData() const
	{
		return m_bEventsNoGetData;
	}
	void SetTraceEventsNoGetData(bool bOn)
	{
		m_bEventsNoGetData = bOn;
	}
	bool IsTraceEventsGetData() const
	{
		return m_bEventsGetData;
	}
	void SetTraceEventsGetData(bool bOn)
	{
		m_bEventsGetData = bOn;
	}
private:
	bool m_bAutoCalls;
	bool m_bExceptions;
	bool m_bEventsNoGetData;
	bool m_bEventsGetData;
};

CDebugOptions & GetDebugOptions();

class CDebuggerImpl;
class CDebugger
{
public:
	CDebugger();
	~CDebugger();
	
	//used from engine
	void StoreMsg(LPCTSTR lpMsgOrFormat,...);
	void IncDecIndent(long nByCount);
	void AddManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown);
	void RemoveManageableObject(LPCTSTR lpObjectName,IUnknown * poObjectUnknown);
private:
	CDebuggerImpl *		m_poImplementation;
};

CDebugger & GetDebugger();


class CDebuggerCallHolder
{
public:
	CDebuggerCallHolder() :
	  m_nIndentInc(0)
	{
	}
	virtual CDebugger &  operator ++(int)
	{
		m_nIndentInc++;
		GetDebugger().IncDecIndent(+1);
		return GetDebugger();
	}
	virtual CDebugger &  operator --(int)
	{
		m_nIndentInc--;
		GetDebugger().IncDecIndent(-1);
		return GetDebugger();
	}
	~CDebuggerCallHolder()
	{
		GetDebugger().IncDecIndent(-m_nIndentInc);
	}
private:
	long m_nIndentInc;
};

#else
	#error __FILE__ already included
#endif

