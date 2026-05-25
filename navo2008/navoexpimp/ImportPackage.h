/*
	NAVO Enterprise 2001
	ImportPackage
*/
#if !defined(AFX_IMPORTPACKAGE_H__D2E01423_9B99_4B79_B014_AC40C0EF46AB__INCLUDED_)
#define AFX_IMPORTPACKAGE_H__D2E01423_9B99_4B79_B014_AC40C0EF46AB__INCLUDED_

class CImportMessage;
class CImportObject;

class CImportSinkInfo
{
public:
	CImportSinkInfo() :
		m_dispidMsgBegin(0),
		m_dispidMsgEnd(0),
		m_dispidObject(0)
	{
	}
	void Init(SCP<IDispatch> & rpoEventSinkDispatchSP);
	SCP<IDispatch> GetEventSinkDispatch()
	{
		return m_poEventSinkDispatchSP;
	}
	void OnMessageBegin(SCP<CImportMessage> & rpoImportMessageSP,bool & rbBreak);
	void OnMessageEnd(SCP<CImportMessage> & rpoImportMessageSP,bool & rbBreak);
	void OnObject(SCP<CImportObject> & rpoImportObjectSP,bool & rbBreak);
private:
	void _Invoke(DISPID dispid,const CSmartOleVariant & roSOV,bool & rbBreak);
	SCP<IDispatch>	m_poEventSinkDispatchSP;
	DISPID			m_dispidMsgBegin;
	DISPID			m_dispidMsgEnd;
	DISPID			m_dispidObject;
};

class CImportPackage : public CCmdTarget
{
	DECLARE_DYNCREATE(CImportPackage)

	CImportPackage();           // protected constructor used by dynamic creation
public:
	//{{AFX_VIRTUAL(CImportPackage)
	//}}AFX_VIRTUAL
protected:
	virtual ~CImportPackage();

	//{{AFX_MSG(CImportPackage)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CImportPackage)

	//{{AFX_DISPATCH(CImportPackage)
	afx_msg LPDISPATCH GetSinkAUTO();
	afx_msg void SetSinkAUTO(LPDISPATCH newValue);
	afx_msg void SetInputStreamAUTO(const VARIANT FAR& pStream);
	afx_msg long GoAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CImportSinkInfo m_oImportSinkInfo;
	SCP<IStream>	m_poInputStreamSP;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTPACKAGE_H__D2E01423_9B99_4B79_B014_AC40C0EF46AB__INCLUDED_)
