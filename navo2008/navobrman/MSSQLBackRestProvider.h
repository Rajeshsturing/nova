/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CMSSQLBackRestProvider- backup/restore provider based for MS SQL 7.0 databases
	(via SQLDMO)
*/

#if !defined(AFX_MSSQLBACKRESTPROVIDER_H__65D90BA5_71C0_4DF6_BED3_9D6BE171C37C__INCLUDED_)
#define AFX_MSSQLBACKRESTPROVIDER_H__65D90BA5_71C0_4DF6_BED3_9D6BE171C37C__INCLUDED_

class CMSSQLBackRestProvider : public CCmdTargetWithErrorInfo
{
public:
	CMSSQLBackRestProvider();           // protected constructor used by dynamic creation
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSSQLBackRestProvider)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMSSQLBackRestProvider();

	// Generated message map functions
	//{{AFX_MSG(CMSSQLBackRestProvider)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	BEGIN_INTERFACE_PART(BackupRestore,IBackupRestore)
		STDMETHOD(Begin)(IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,
			ISupplyInfo * pSupplyInfo);
		STDMETHOD(End)();
		STDMETHOD(GetBackupStream)(LPSTR * ppStreamName,
			LPSTR * ppStreamInfo,IStream ** ppDataStream);
		STDMETHOD(SetRestoreStream)(LPSTR  ppStreamName,
			LPSTR  ppStreamInfo,IStream * ppDataStream,__int64 i64Length);
		STDMETHOD(GetStat)(long * pTotalCount,long * pTotalSize);
	END_INTERFACE_PART(BackupRestore)
	BEGIN_INTERFACE_PART(BackupSink, SQLDMO::BackupSink)
		STDMETHOD (raw_PercentComplete)(BSTR Message,long Percent);
		STDMETHOD (raw_NextMedia)(BSTR Message );
		STDMETHOD (raw_Complete)(BSTR Message );
	END_INTERFACE_PART(BackupSink)
	BEGIN_INTERFACE_PART(RestoreSink, SQLDMO::RestoreSink)
		STDMETHOD (raw_PercentComplete)(BSTR Message,long Percent);
		STDMETHOD (raw_NextMedia)(BSTR Message );
		STDMETHOD (raw_Complete)(BSTR Message );
	END_INTERFACE_PART(RestoreSink)

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMSSQLBackRestProvider)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	void ReadDescription(bool bBackup,LPCSTR lpDescription);

	CFileRemover m_oTmpBackupFR;
	CString m_oSQLServerString;
	CString m_oDBNameString;

	CString m_oUserString;
	CString m_oPasswordString;
	
	CString m_oDescriptionString;
	CString m_oTempBackupFileString;
	bool	m_bConsumed;
	bool	m_bBackup;
	HRESULT m_hResult;
	SCP<ISupplyInfo>			m_poSupplyInfoSP;

	SCP<INotificationSink> m_poNotificationSinkSP;
	DWORD m_dwBackupSinkCookie;
	SQLDMO::_SQLServerPtr	m_poSQLServer;
	SQLDMO::_BackupPtr		m_poBackup;
	SQLDMO::_RestorePtr		m_poRestore;
};


#endif // !defined(AFX_MSSQLBACKRESTPROVIDER_H__65D90BA5_71C0_4DF6_BED3_9D6BE171C37C__INCLUDED_)
