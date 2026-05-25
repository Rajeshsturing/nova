/*
	NAVO Enterprise 2001
	installation session high-level objects
*/
#if !defined(AFX_INSTALLSESSION_H__76886994_1119_401A_8483_40318B7589E5__INCLUDED_)
#define AFX_INSTALLSESSION_H__76886994_1119_401A_8483_40318B7589E5__INCLUDED_

class CInstallSession : public CCmdTargetInterface
{
	DECLARE_DYNCREATE(CInstallSession)

	CInstallSession();           // protected constructor used by dynamic creation

public:
	//{{AFX_VIRTUAL(CInstallSession)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

protected:
	virtual ~CInstallSession();

	//{{AFX_MSG(CInstallSession)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CInstallSession)

	//{{AFX_DISPATCH(CInstallSession)
	afx_msg void AddShortcutAUTO(LPCTSTR lpGroupName, LPCTSTR lpProgramPath, LPCTSTR lpArgument, LPCTSTR lpCaption, LPCTSTR lpIconPath, long nIcon, LPCTSTR lpWorkingDir);
	afx_msg void RemoveShortcutAUTO(LPCTSTR lpGroupName, LPCTSTR lpCaption);
	afx_msg void RemoveGroupAUTO(LPCTSTR lpGroupName, BOOL bForce);
	afx_msg LPDISPATCH GetLogonObject();
	afx_msg void AddODBCDSNAUTO(LPCTSTR lpName, BOOL bSystem, LPCTSTR lpDescription);
	afx_msg void RemoveODBCDSNAUTO(LPCTSTR lpName, BOOL bSystem, LPCTSTR lpDescription);
	afx_msg void InstallODBCDriverAUTO(LPCTSTR lpName);
	afx_msg void UninstallODBCDriverAUTO(LPCTSTR lpName);
	afx_msg void SetLogNameAUTO(LPCTSTR lpLogFileName);
	afx_msg void AddLogMsgAUTO(LPCTSTR lpMsgText);
	afx_msg BOOL InstallFileAUTO(LPCTSTR lpScr, LPCTSTR lpDest);
	afx_msg BOOL AnyInUseAUTO();
	afx_msg long GetLastErrorAUTO();
	afx_msg BSTR GetMediaURLAUTO(LPCTSTR lpSourceDir, LPCTSTR lpSubDir, LPCTSTR lpKeyFile, LPCTSTR lpComponentName);
	afx_msg BSTR GetFileVersionAUTO(LPCTSTR lpPath);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CNavoLog m_oNavoLog;
	//last install file state
	bool	 m_bFileInUse;
	DWORD	 m_dwLastError;
};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CLogonAsUserAUTO command target
class CLogonAsUser;
class CLogonAsUserAUTO : public CCmdTargetInterface
{
	DECLARE_DYNCREATE(CLogonAsUserAUTO)

	CLogonAsUserAUTO();           
public:
	virtual ~CLogonAsUserAUTO();
	//{{AFX_VIRTUAL(CLogonAsUserAUTO)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CLogonAsUserAUTO)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CLogonAsUserAUTO)
	afx_msg BOOL LogonAUTO(LPCTSTR lpDomain, LPCTSTR lpUser, LPCTSTR lpPassword, BOOL bForever);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CLogonAsUser * m_pLogonAsUser;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLSESSION_H__76886994_1119_401A_8483_40318B7589E5__INCLUDED_)
