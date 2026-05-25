/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CScriptBackRestProvider- backup/restore provider based on scripts
*/

#if !defined(AFX_SCRIPTBACKRESTPROVIDER_H__0A0C88F5_CA76_4EA0_968B_3C1E0691B9E5__INCLUDED_)
#define AFX_SCRIPTBACKRESTPROVIDER_H__0A0C88F5_CA76_4EA0_968B_3C1E0691B9E5__INCLUDED_


class CScriptBackRestProvider : public CCmdTargetWithErrorInfo
{
public:
	CScriptBackRestProvider();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptBackRestProvider)
	//}}AFX_VIRTUAL

	BEGIN_INTERFACE_PART(BackupRestore,IBackupRestore)
		STDMETHOD(Begin)(IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,
			ISupplyInfo *pSupplyInfo);
		STDMETHOD(End)();
		STDMETHOD(GetBackupStream)(LPSTR * ppStreamName,
			LPSTR * ppStreamInfo,IStream ** ppDataStream);
		STDMETHOD(SetRestoreStream)(LPSTR  ppStreamName,
			LPSTR  ppStreamInfo,IStream * ppDataStream,__int64 i64Length);
		STDMETHOD(GetStat)(long * pTotalCount,long * pTotalSize);
	END_INTERFACE_PART(BackupRestore)

	DECLARE_INTERFACE_MAP();
protected:
	virtual ~CScriptBackRestProvider();

	// Generated message map functions
	//{{AFX_MSG(CScriptBackRestProvider)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CScriptBackRestProvider)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTBACKRESTPROVIDER_H__0A0C88F5_CA76_4EA0_968B_3C1E0691B9E5__INCLUDED_)
