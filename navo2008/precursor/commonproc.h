/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	repair/installation common procedures
*/

#ifndef _COMMONPROC_H_
#define _COMMONPROC_H_


CString AskUserForFolder(LPCTSTR lpTitle);

//--------------- return root path or root URL to media source ------------------
//--------------- containing required components --------------------------------
enum UserAskMode
{
	UAM_FORBIDDEN,
	UAM_ALLOWED,
	UAM_REQUIRED
};

CString GetMediaRootURL(UserAskMode eUAM,LPCTSTR lpSourceDir,LPCTSTR lpSubDir,LPCTSTR lpKeyFile,LPCTSTR lpComponentHumanName);

HRESULT TestCreateInstance(const CLSID & rClassId);

//--------- like CopyFile but with ability to effective copy "in-use" files --------
DWORD NAVOSetupFileEx(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse);

errorcode RegUnregComponent(bool bUIAllowed,LPCTSTR lpPathName,bool bRegister);

class CSimpleOleInitHolder
{
public:
	CSimpleOleInitHolder()
	{
		HRESULT hResult = ::OleInitialize(NULL);
		m_bShouldFree = (hResult == S_OK || hResult == S_FALSE);
	}
	~CSimpleOleInitHolder()
	{
		if(m_bShouldFree)
		{
			::OleUninitialize();
		}
	}
private:
	bool m_bShouldFree;
};

errorcode GetInprocServer(const CLSID & roCLSID,CString & roString);
errorcode GetInprocServer(LPCTSTR lpProgId,CString & roString);
errorcode GetLocalServer(const CLSID & roCLSID,CString & roString);
errorcode GetLocalServer(LPCTSTR lpProgId,CString & roString);

//in syscheck.cpp
errorcode CheckCOMObject(const CLSID & rCLSID,errorcode CodeOnFail);
errorcode CheckCOMObject(LPCTSTR lpProgId,errorcode CodeOnFail);



#else
	#error __FILE__ already included
#endif
