/*
	NAVO Sp. z o.o. (2000)
	
	NAVO Enterprise

	class:
		Database access object
*/

#if !defined(AFX_NAVODB_H__358F5802_8B92_43A4_83CF_D20A492639D5__INCLUDED_)
#define AFX_NAVODB_H__358F5802_8B92_43A4_83CF_D20A492639D5__INCLUDED_

class CFDObjectCache;
class CDefinitionManagerProvider;

class CNavodbApp : public CWinApp
{
public:
	CNavodbApp();
	//{{AFX_VIRTUAL(CNavodbApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CNavodbApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	SCP<CFDObjectCache> get_cache_for_cacheuid(LPCTSTR lpObjectCacheUID);

	SCP<CDefinitionManagerProvider> m_poDefinitionManProvSP;
	CString m_oMainUIDString;		//this server unique ID (currently implemented as GUID)
private:
	//object cache
	CSimpleCriticalSection	m_oFDObjCacheMapCS;
	CMap<CString,LPCSTR, SCP<CFDObjectCache> ,SCP<CFDObjectCache> & > m_oFDObjCacheMap;
};


extern CNavodbApp theApp;

#endif // !defined(AFX_NAVODB_H__358F5802_8B92_43A4_83CF_D20A492639D5__INCLUDED_)
