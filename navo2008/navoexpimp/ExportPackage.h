/*
	NAVO Enterprise 2001
	ExportPackage
*/

#if !defined(AFX_EXPORTPACKAGE_H__19D50961_4676_47CE_8E18_10D75824ECA2__INCLUDED_)
#define AFX_EXPORTPACKAGE_H__19D50961_4676_47CE_8E18_10D75824ECA2__INCLUDED_

class CExportPackage : public CCmdTarget
{
	DECLARE_DYNCREATE(CExportPackage)

	CExportPackage();           // protected constructor used by dynamic creation
public:
	//{{AFX_VIRTUAL(CExportPackage)
	//}}AFX_VIRTUAL

protected:
	virtual ~CExportPackage();

	//{{AFX_MSG(CExportPackage)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CExportPackage)

	//{{AFX_DISPATCH(CExportPackage)
	afx_msg LPDISPATCH NewMsgAUTO();
	afx_msg void SetOutputStreamAUTO(const VARIANT FAR& ostream);
	afx_msg void SaveAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	void WritePackageHeader();
	void WritePackageFooter();
private:
	ExportImportFormat	m_eif;
	SCP<IStream>		m_poOutputStreamSP;
	SCP<CFileRemover>	m_poFileRemoverSP;
	bool				m_bSaved;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTPACKAGE_H__19D50961_4676_47CE_8E18_10D75824ECA2__INCLUDED_)
