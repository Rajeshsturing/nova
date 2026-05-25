/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CBRSet - backup/restore item description (file group, database,etc.)
*/

#if !defined(AFX_FILESET_H__7932684D_1AE9_45D5_811D_88333A9326A2__INCLUDED_)
#define AFX_FILESET_H__7932684D_1AE9_45D5_811D_88333A9326A2__INCLUDED_

class CBRSet : public CCmdTargetInterface
{
	DECLARE_DYNCREATE(CBRSet)


public:
	CBRSet();           // protected constructor used by dynamic creation
	virtual ~CBRSet();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBRSet)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	BRSetType GetType() const
	{
		return m_BRSetType;
	}
	bool IsRecurse() const
	{
		return m_bResurse;
	}
	bool IsRelative() const
	{
		return m_bRelative;
	}
	const CString & GetServer() const
	{
		return m_oServerString;
	}
	const CString & GetDatabase() const
	{
		return m_oDBString;
	}
	const CString & GetUser() const
	{
		return m_oUserString;
	}
	const CString & GetPassword() const
	{
		return m_oPasswordString;
	}
	const CString & GetMask() const
	{
		return m_oMaskString;
	}
	const CString & GetRemoteServer() const
	{
		return m_oRemoteServerString;
	}

	const CString & GetPath() const
	{
		return m_oPathString;
	}
	const CString & GetName() const
	{
		return m_oNameString;
	}

	CEnumerableArray< SCP<CBRSet>, SCP<CBRSet> & > & GetSubSetArray()
	{
		return m_oBRSetArray;
	}

	CString GetDescription() const;
	bool SetDescription(LPCTSTR lpDescription);
protected:

	// Generated message map functions
	//{{AFX_MSG(CBRSet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBRSet)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBRSet)
	afx_msg long GetTypeAUTO();
	afx_msg void SetTypeAUTO(long nNewValue);
	afx_msg BSTR GetMaskAUTO();
	afx_msg void SetMaskAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetResurseAUTO();
	afx_msg void SetResurseAUTO(BOOL bNewValue);
	afx_msg BSTR GetServerAUTO();
	afx_msg void SetServerAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetDatabaseAUTO();
	afx_msg void SetDatabaseAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetUserAUTO();
	afx_msg void SetUserAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetPasswordAUTO();
	afx_msg void SetPasswordAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetRemoteserverAUTO();
	afx_msg void SetRemoteserverAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetRelativeAUTO();
	afx_msg void SetRelativeAUTO(BOOL bNewValue);
	afx_msg BSTR GetPathAUTO();
	afx_msg void SetPathAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetNameAUTO();
	afx_msg void SetNameAUTO(LPCTSTR lpszNewValue);
	afx_msg void AddBRSetAUTO(LPDISPATCH lpBRSetDispatch);
	afx_msg void ReadAUTO(LPCTSTR lpDescription);
	afx_msg BSTR WriteAUTO();
	afx_msg LPDISPATCH GetBRSetAUTO(long nIter);
	afx_msg void DeleteBRSetAUTO(long nIter);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	LPCTSTR __ReadDescription(LPCTSTR lpDescription);

	BRSetType	m_BRSetType;
	CString		m_oMaskString;	//maska *.xml;*.doc
	CString		m_oPathString;	// c:\program files\navo enterprise\ 
	bool		m_bResurse;
	bool		m_bRelative;
	
	CString		m_oNameString;		//brset name
	CString		m_oServerString;
	CString		m_oDBString;

	CString		m_oUserString;
	CString		m_oPasswordString;

	CString		m_oRemoteServerString;

	CEnumerableArray< SCP<CBRSet>, SCP<CBRSet> & > m_oBRSetArray;
};

//obiekt implementuj¹cy IBackupRestore dla plików
//
//mo¿liwa optymalizacja:
//teraz tworzy listê wszystkich plików na wstêpie, a potem je kolejno zwraca
//móg³by to robiæ iteracyjnie.

class CFileSetBackRestProvider : public CCmdTargetWithErrorInfo
{
public:
	CFileSetBackRestProvider() :
		m_bRelative(false),
		m_bResurse(false)
	{
	}
	void ReadDescription(LPCSTR lpDescription)
	{
		CBRSet oBRSet;
		VERIFY(oBRSet.SetDescription(lpDescription));
		ASSERT(oBRSet.GetType() == BRSET_FILEGROUP);

		SplitString(oBRSet.GetMask(),m_oMaskStringArray,'|');

		m_oPathString = oBRSet.GetPath();
 		m_bResurse = oBRSet.IsRecurse();
		m_bRelative= oBRSet.IsRelative();
	}

	BEGIN_INTERFACE_PART(BackupRestore,IBackupRestore)
		STDMETHOD(Begin)(IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,ISupplyInfo * pSupplyInfo);
		STDMETHOD(End)();
		STDMETHOD(GetBackupStream)(LPSTR * ppStreamName,
			LPSTR * ppStreamInfo,IStream ** ppDataStream);
		STDMETHOD(SetRestoreStream)(LPSTR  ppStreamName,
			LPSTR  ppStreamInfo,IStream * ppDataStream,__int64 i64Length);
		STDMETHOD(GetStat)(long * pTotalCount,long * pTotalSize);
	END_INTERFACE_PART(BackupRestore)

	DECLARE_INTERFACE_MAP();
private:
	bool PopulateFileList(LPCTSTR lpDir,SCP<INotificationSink> & rpoNotificationSinkSP);

	CArray<CString,LPCTSTR>		m_oFileArray;
	long						m_nCurrentPos;
	long						m_nTotalSize;
	CString						m_oPathString; //œcie¿ka tj. c:\navo2001
	CStringArray				m_oMaskStringArray; //maski tj. *.xml
	bool						m_bResurse;
	bool						m_bRelative;
	bool						m_bBackup;
	SCP<ISupplyInfo>			m_poSupplyInfoSP;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESET_H__7932684D_1AE9_45D5_811D_88333A9326A2__INCLUDED_)
