/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
	CSystemAutoObject
		obiekt udostêpnia funkcje OS
*/

#if !defined(AFX_SYSTEMAUTOOBJECT_H__301EBC20_7A2B_46FE_92CD_B894E493425B__INCLUDED_)
#define AFX_SYSTEMAUTOOBJECT_H__301EBC20_7A2B_46FE_92CD_B894E493425B__INCLUDED_

class CSystemAutoObject : public CCmdTargetInterface
{
public:
	CSystemAutoObject();
	//{{AFX_VIRTUAL(CSystemAutoObject)
public:
	//}}AFX_VIRTUAL

protected:
	virtual ~CSystemAutoObject();
	//{{AFX_MSG(CSystemAutoObject)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CSystemAutoObject)
	afx_msg BSTR GetWindowsDirectoryAUTO();
	afx_msg BSTR GetSystemDirectoryAUTO();
	afx_msg BSTR GetRegistryKeysAUTO(long hKeyClass, LPCTSTR lpSubKey);
	afx_msg VARIANT CreateTempStreamAUTO();
	afx_msg long RegisterDLL(LPCTSTR lpFilePath);
	afx_msg long UnregisterDLL(LPCTSTR lpFilePath);
	afx_msg long ExecuteProcessAUTO(LPCTSTR pcProcessPath, LPCTSTR pcWorkDir, LPCTSTR pcArguments, BOOL bShow, BOOL bWait);
	afx_msg BSTR StringToUTF8(LPCTSTR lpString);
	afx_msg void DeleteRegistryKeyAUTO(long hKeyClass, LPCTSTR lpSubKey);
	afx_msg long GetOSIdAUTO();
	afx_msg BSTR GetSpecialFolderAUTO(long nType);
	afx_msg BSTR CreateTempfileNameAUTO(LPCTSTR pcPrefix, LPCTSTR pcExtension);
	afx_msg BOOL ShellOpenAUTO(LPCTSTR pcFile, LPCTSTR pcWorkDir, LPCTSTR pcParams);
	afx_msg BOOL ShellPrintAUTO(LPCTSTR pcFile);
	afx_msg void SleepAUTO(long lTime);
	afx_msg BOOL SetFileModifiedTimeAUTO(LPCTSTR lpFile, DATE nNewDate);
	afx_msg void PlaySoundAUTO(LPCTSTR lpFile);
	afx_msg BSTR GetRegistryAUTO(long hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpValueName);
	afx_msg void SetRegistryAUTO(long hKeyClass, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpszNewValue);
	afx_msg BSTR GetPrivateProfileAUTO(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpIniFile);
	afx_msg void SetPrivateProfileAUTO(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpIniFile, LPCTSTR lpszNewValue);
	afx_msg LPDISPATCH CreateObjectAUTO(LPCTSTR lpProgId);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	DECLARE_OLECREATE(CSystemAutoObject)
	DECLARE_DYNCREATE(CSystemAutoObject)
};


#else
	#error File already included
#endif
