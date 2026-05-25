// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _DebugMainSink wrapper class

class _DebugMainSink : public COleDispatchDriver
{
public:
	_DebugMainSink() {}		// Calls COleDispatchDriver default constructor
	_DebugMainSink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DebugMainSink(const _DebugMainSink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetBPause(BOOL bNewValue);
	BOOL GetBPause();
	void message(const VARIANT& pcMsg);
	void registersink(VARIANT* pSink);
	LPDISPATCH GetSink();
};
