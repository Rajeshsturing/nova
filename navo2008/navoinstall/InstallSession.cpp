/*
	NAVO Enterprise 2001
	installation session high-level objects
*/

#include "stdafx.h"
#include "navoinstall.h"
#include "InstallSession.h"
#include "navo_security.h"
#include "path.h"
#include "shllclnt.h"	// external declarations for this file
#include "odbcinstall.h"
#include "..\precursor\commonproc.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD NAVOSetupFileExIfNewer(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse,bool & rbNewerInstalled);
/////////////////////////////////////////////////////////////////////////////
// CInstallSession

IMPLEMENT_DYNCREATE(CInstallSession, CCmdTarget)

CInstallSession::CInstallSession() :
	m_bFileInUse(false),
	m_dwLastError(0)
{
	EnableAutomation();
	AfxOleLockApp();
}

CInstallSession::~CInstallSession()
{
	AfxOleUnlockApp();
}


void CInstallSession::OnFinalRelease()
{
	CCmdTargetInterface::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CInstallSession, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CInstallSession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInstallSession, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CInstallSession)
	DISP_FUNCTION(CInstallSession, "addshortcut", AddShortcutAUTO, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "removeshortcut", RemoveShortcutAUTO, VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "removegroup", RemoveGroupAUTO, VT_EMPTY, VTS_BSTR VTS_BOOL)
	DISP_FUNCTION(CInstallSession, "getlogonobject", GetLogonObject, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CInstallSession, "addodbcdsn", AddODBCDSNAUTO, VT_EMPTY, VTS_BSTR VTS_BOOL VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "removeodbcdsn", RemoveODBCDSNAUTO, VT_EMPTY, VTS_BSTR VTS_BOOL VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "installODBCdriver", InstallODBCDriverAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "uninstallODBCDriver", UninstallODBCDriverAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "setlogname", SetLogNameAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "addlogmsg", AddLogMsgAUTO, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "installfile", InstallFileAUTO, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "anyinuse", AnyInUseAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CInstallSession, "lasterror", GetLastErrorAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CInstallSession, "getmediaurl", GetMediaURLAUTO, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CInstallSession, "getfileversion", GetFileVersionAUTO, VT_BSTR, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {10AACD7F-8EC7-4092-9843-C41E7D42921B}
static const IID IID_IInstallSession =
{ 0x10aacd7f, 0x8ec7, 0x4092, { 0x98, 0x43, 0xc4, 0x1e, 0x7d, 0x42, 0x92, 0x1b } };

BEGIN_INTERFACE_MAP(CInstallSession, CCmdTargetInterface)
	INTERFACE_PART(CInstallSession, IID_IInstallSession, Dispatch)
END_INTERFACE_MAP()

// {188cb175-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CInstallSession, "navoinstall.session", 0x188cb175,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CInstallSession message handlers

void CInstallSession::AddShortcutAUTO(LPCTSTR lpGroupName, LPCTSTR lpProgramPath, LPCTSTR lpArgument, LPCTSTR lpCaption, LPCTSTR lpIconPath, long nIcon, LPCTSTR lpWorkingDir) 
{
	ALL_TRY
	{
		m_oNavoLog << "creating shortcut " + CString(lpCaption) + " in group " + CString(lpGroupName);
		m_oNavoLog << "shortcut arguments: path=" + CString(lpProgramPath) + ",program arguments=" +
			CString(lpArgument) + ",workdir=" + CString(lpWorkingDir);
		
		CShellClient oShellClient;
		oShellClient.CreateProgramItem(lpGroupName,lpProgramPath,lpArgument,lpCaption,lpIconPath, nIcon,lpWorkingDir);
		
		m_oNavoLog << "shortcut created";
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::RemoveShortcutAUTO(LPCTSTR lpGroupName, LPCTSTR lpCaption) 
{
	ALL_TRY
	{
		m_oNavoLog << "removing shortcut " + CString(lpCaption) + " from group " + CString(lpGroupName);
		CShellClient oShellClient;
		oShellClient.RemoveProgramItem(lpGroupName, lpCaption);
		m_oNavoLog << "shortcut removed";
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::RemoveGroupAUTO(LPCTSTR lpGroupName, BOOL bForce) 
{
	ALL_TRY
	{
		m_oNavoLog << "removing group " + CString(lpGroupName);
		CShellClient oShellClient;
		oShellClient.DeleteGroup(lpGroupName,bForce);
		m_oNavoLog << "group removed";
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CLogonAsUserAUTO

IMPLEMENT_DYNCREATE(CLogonAsUserAUTO, CCmdTarget)

CLogonAsUserAUTO::CLogonAsUserAUTO()
{
	EnableAutomation();
	m_pLogonAsUser = new CLogonAsUser();
}

CLogonAsUserAUTO::~CLogonAsUserAUTO()
{
	delete m_pLogonAsUser;
}


BEGIN_MESSAGE_MAP(CLogonAsUserAUTO, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CLogonAsUserAUTO)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLogonAsUserAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CLogonAsUserAUTO)
	DISP_FUNCTION(CLogonAsUserAUTO, "logon", LogonAUTO, VT_BOOL, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ILogonAsUserAUTO to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1C9E8B43-5058-46A5-8210-0B4183F33A5E}
static const IID IID_ILogonAsUserAUTO =
{ 0x1c9e8b43, 0x5058, 0x46a5, { 0x82, 0x10, 0xb, 0x41, 0x83, 0xf3, 0x3a, 0x5e } };

BEGIN_INTERFACE_MAP(CLogonAsUserAUTO, CCmdTargetInterface)
	INTERFACE_PART(CLogonAsUserAUTO, IID_ILogonAsUserAUTO, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogonAsUserAUTO message handlers

BOOL CLogonAsUserAUTO::LogonAUTO(LPCTSTR lpDomain, LPCTSTR lpUser, LPCTSTR lpPassword, BOOL bForever) 
{
	ALL_TRY
	{
		ASSERT(m_pLogonAsUser);
		return m_pLogonAsUser->Logon(lpDomain,lpUser,lpPassword,bForever != FALSE) != false;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CInstallSession::GetLogonObject() 
{
	ALL_TRY
	{
		SCP<CLogonAsUserAUTO> poLAUSP = NewSCP(new CLogonAsUserAUTO());
		return poLAUSP->GetDispatch(false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::AddODBCDSNAUTO(LPCTSTR lpName, BOOL bSystem, LPCTSTR lpDescription) 
{
	ALL_TRY
	{
		//przetestowano dla MSSQL i Sybase
		CODBCInstaller("").CreateDSN(FindDBTypeIndex(CString(lpName)),bSystem != FALSE,lpDescription);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::RemoveODBCDSNAUTO(LPCTSTR lpName, BOOL bSystem, LPCTSTR lpDescription) 
{
	ALL_TRY
	{
		//przetestowano dla MSSQL i Sybase
		CODBCInstaller("").DeleteDSN(FindDBTypeIndex(CString(lpName)),bSystem != FALSE,lpDescription);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::InstallODBCDriverAUTO(LPCTSTR lpName) 
{
	ALL_TRY
	{
		/*
			Uwaga! przetestowano tylko dla Sybase
			Dla MSSQL nie powinno byæ potrzeby (MDAC jest instalowany z definicji)
		*/
		EDBType eDBType = FindDBTypeIndex(CString(lpName));
		switch(eDBType)
		{
		case DBTYPE_SQLSERVER:
			{
				LPCTSTR lpSubDir = "components\\odbc\\mssql\\";
				CString oSrcDirString = GetMediaRootURL(UAM_ALLOWED,"",
					lpSubDir,"sqlsrv32.dll","Sterownik ODBC dla MS SQL Server");
				if(oSrcDirString.IsEmpty())
				{
					ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,"Odszukanie sterownika nieudane");
				}
				oSrcDirString += lpSubDir;

				CODBCInstaller oODBCInstaller(oSrcDirString);
				oODBCInstaller.InstallFile("sqlsrdme.txt");	//	Release Notes
				oODBCInstaller.InstallFile("sqlsodbc.hlp");	//	Help File
				oODBCInstaller.InstallFile("12520437.cpx");	//	Translation Code Page
				oODBCInstaller.InstallFile("12520850.cpx");	//	Translation Code Page
				oODBCInstaller.InstallFile("odbcbcp.dll");	//	SQL Server BCP Library
				oODBCInstaller.InstallFile("windbver.exe");	//	SQL Server Client Configuration Utility
				oODBCInstaller.InstallFile("dbmsshrn.dll");	//	Shared Memory Net-Library	
				oODBCInstaller.InstallFile("dbnmpntw.dll");	//	Named Pipes Net-Library	
				oODBCInstaller.InstallFile("dbmssocn.dll");	//	Sockets Net-Library	
				oODBCInstaller.InstallDriver(eDBType);
				oODBCInstaller.InstallTranslator(eDBType);
			}
		break;
		case DBTYPE_MSACCESS:
			{
				LPCTSTR lpSubDir = "components\\odbc\\access\\";
				CString oSrcDirString = GetMediaRootURL(UAM_ALLOWED,"",lpSubDir,"odbcjt32.dll","Sterownik ODBC dla MS Access");
				if(oSrcDirString.IsEmpty())
				{
					ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,"Odszukanie sterownika nieudane");
				}
				oSrcDirString += lpSubDir;

				CODBCInstaller oODBCInstaller(oSrcDirString);
				oODBCInstaller.InstallDriver(eDBType);
			}
		break;
		case DBTYPE_SYBASE:
			{
				LPCTSTR lpSubDir = "components\\odbc\\sybase\\";
				CString oSrcDirString = GetMediaRootURL(UAM_ALLOWED,"",
					lpSubDir,"wod50t.dll","Sterownik ODBC dla Sybase SQL Anywhere");

				if(oSrcDirString.IsEmpty())
				{
					ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,"Odszukanie sterownika nieudane");
				}
				oSrcDirString += lpSubDir;

				CODBCInstaller oODBCInstaller(oSrcDirString);
				oODBCInstaller.InstallFile("dbl50t.dll");
				oODBCInstaller.InstallFile("dbtl50t.dll");
				oODBCInstaller.InstallFile("rtdsk50.exe");
				oODBCInstaller.InstallFile("wl50ent.dll");
				oODBCInstaller.InstallFile("wodbc.hlp");
				oODBCInstaller.InstallFile("wsqlcalt.dll");
				oODBCInstaller.InstallDriver(eDBType);
				oODBCInstaller.InstallTranslator(eDBType);
			}
		break;
		default:
			ASSERT(false);
		break;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}

}

void CInstallSession::UninstallODBCDriverAUTO(LPCTSTR lpName) 
{
	ALL_TRY
	{
		//to_do: podawanie srcdir
		CString oSrcDirString;
		CODBCInstaller oODBCInstaller(oSrcDirString);
		
		EDBType eDBType = FindDBTypeIndex(CString(lpName));
		switch(eDBType)
		{
		case DBTYPE_SQLSERVER:
			oODBCInstaller.UnInstallDriver(eDBType);
			oODBCInstaller.UnInstallTranslator(eDBType);
		break;
		case DBTYPE_MSACCESS:
			oODBCInstaller.UnInstallDriver(eDBType);
		break;
		case DBTYPE_SYBASE:
			oODBCInstaller.UnInstallDriver(eDBType);
			oODBCInstaller.UnInstallTranslator(eDBType);
		break;
		default:
			ASSERT(false);
			break;
		};
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}

}

void CInstallSession::SetLogNameAUTO(LPCTSTR lpLogFileName) 
{
	ALL_TRY
	{
		TCHAR cWinDrive[ MAX_PATH ] = "C:\\";
		::GetWindowsDirectory(cWinDrive,sizeof(cWinDrive)/sizeof(TCHAR));
		_tcscpy(cWinDrive+3,lpLogFileName);
		m_oNavoLog.Open(cWinDrive);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CInstallSession::AddLogMsgAUTO(LPCTSTR lpMsgText) 
{
	ALL_TRY
	{
		m_oNavoLog << lpMsgText;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CInstallSession::InstallFileAUTO(LPCTSTR lpScr, LPCTSTR lpDest) 
{
	bool bInUse;
	bool bNewer;
	m_oNavoLog << "installing " + CString(lpScr) + " to " + CString(lpDest);
	m_dwLastError = NAVOSetupFileExIfNewer(lpScr,lpDest,bInUse,bNewer);
	m_oNavoLog << "installation result is " + Long2String(long(m_dwLastError));
	m_oNavoLog << "is use status is: " + CString(bInUse ? " in use ": " not in use");
	m_bFileInUse |= bInUse;
	return (m_dwLastError == ERROR_SUCCESS);
}

BOOL CInstallSession::AnyInUseAUTO() 
{
	return m_bFileInUse != false;
}

long CInstallSession::GetLastErrorAUTO() 
{
	return long(m_dwLastError);
}

BSTR CInstallSession::GetMediaURLAUTO(LPCTSTR lpSourceDir, LPCTSTR lpSubDir, LPCTSTR lpKeyFile, LPCTSTR lpComponentName) 
{
	ALL_TRY
	{
		CString strResult = GetMediaRootURL(UAM_ALLOWED,lpSourceDir, lpSubDir, lpKeyFile, lpComponentName);
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CInstallSession::GetFileVersionAUTO(LPCTSTR lpPath) 
{
	ALL_TRY
	{
		CString strResult;
		CVersion oFileVersion;
		if(oFileVersion.Load(lpPath))
		{
			strResult = oFileVersion.GetFileVersion();
		}
		return strResult.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
