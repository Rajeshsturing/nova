/*
	NAVO Enterprise 2001
	Export Message
*/

#if !defined(AFX_EXPORTMESSAGE_H__A6A9CB2E_D1BC_461D_A271_D50DBF13CD8B__INCLUDED_)
#define AFX_EXPORTMESSAGE_H__A6A9CB2E_D1BC_461D_A271_D50DBF13CD8B__INCLUDED_

class CExportMessage : public CCmdTargetInterface
{
public:
	CExportMessage(ExportImportFormat eif,SCP<IStream> & rpoOutputStreamSP);
	//{{AFX_VIRTUAL(CExportMessage)
	//}}AFX_VIRTUAL

	void OnSaveObject(CExportObject * poExportObject);
private:
	virtual ~CExportMessage();

	//{{AFX_MSG(CExportMessage)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CExportMessage)
	afx_msg LPDISPATCH GetHeaderAUTO();
	afx_msg void SetHeaderAUTO(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetNewObjAUTO(long nType, long nIdObj);
	afx_msg BOOL WasObjAUTO(long nType, long nIdObj);
	afx_msg void SaveAUTO();
	afx_msg LPDISPATCH CloneToImportMessageAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	SCP<CExportObject> GetNewObj(long nType, long nIdObj);

	void InitHeader();
	bool WasObject(long nType, long nIdObj);

	void WriteMsgHeader();
	void WriteMsgFooter();
private:
	ExportImportFormat	m_eif;
	SCP<IStream>		m_poOutputStreamSP;
	CMap<hyper,hyper,bool,bool>		m_oObjectMap;	//bool - false - not saved yet;
	SCP<CExportObject>	m_poHeaderExportObjectSP;
	bool				m_bSaved;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTMESSAGE_H__A6A9CB2E_D1BC_461D_A271_D50DBF13CD8B__INCLUDED_)
