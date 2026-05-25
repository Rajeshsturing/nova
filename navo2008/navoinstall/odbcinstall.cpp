/*
	NAVO Enterprise 2001
	Copyright NAVO (c) 2001
	odbc installation support class
*/

#include "stdafx.h"
#include "registry.h"
#include "path.h"
#include "version.h"
#include "odbcinstall.h"
#include <odbcinst.h>

DWORD NAVOSetupFileExIfNewer(LPCTSTR lpSrcFileName,LPCTSTR lpDestFileName,bool & bInUse,bool & rbNewerInstalled);

LPCTSTR pcInstRegKey = "SOFTWARE\\ODBC\\ODBCINST.INI\\"; 
LPCTSTR pcDriversRegKey = "SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Drivers";
LPCTSTR pcTranslatorsRegKey = "SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Translators";

static CODBCDriverDescription DriverDescriptionsArray[5] = 
{
	{ "SQL Server", "sqlsrv32.dll", "sqlsrv32.dll" },
	{ "Sybase SQL Anywhere 5.0", "wod50t.dll", "wod50t.dll" },
	{ "Microsoft Access Driver (*.mdb)", "odbcjt32.dll", "odbcjt32.dll" },
	{ "Microsoft Visual FoxPro Driver", "vfpodbc.dll", "vfpodbc.dll" },
	{ "Microsoft dBase Driver (*.dbf)", "odbcjt32.dll", "oddbse32.dll" },
};

static CODBCTranslatorDescription SQLServerTranslatorDescription = 
{
	"MS Code Page Translator",
	"MSCPXL32.DLL",
};

static CODBCTranslatorDescription SybaseTranslatorDescription = 
{
	"Sybase SQL Anywhere 5.0 Translator",
	"wtr50t.DLL",
};

void CODBCInstaller::InstallDriver(EDBType eDBType)
{
	const CODBCDriverDescription & roDesc = DriverDescriptionsArray[eDBType];
	//windows system
	CString oSysDirString;
	::GetSystemDirectory(oSysDirString.GetBuffer(_MAX_PATH),_MAX_PATH);
	oSysDirString.ReleaseBuffer();
	EnsureEndingBackslash(oSysDirString);

	bool bInUse;
	bool bNewer;
	DWORD dwResult = NAVOSetupFileExIfNewer(GetSrcDir() + roDesc.m_pcDriverFileName,
		oSysDirString + roDesc.m_pcDriverFileName,bInUse,bNewer);
	if(dwResult != ERROR_SUCCESS)
	{
		CString oString;
		oString.Format("instalacja pliku sterownika %s nieudana. kod=%d",oSysDirString + roDesc.m_pcDriverFileName,dwResult);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
	m_bInUse |= bInUse;

	CString oRegKeyString(pcInstRegKey);
	oRegKeyString += roDesc.m_pcName;
	_install_usage_count(oRegKeyString);

	if (&roDesc == &DriverDescriptionsArray[DBTYPE_SQLSERVER])
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"APILevel", "2");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"ConnectFunctions", "YYY");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Driver", oSysDirString + roDesc.m_pcDriverFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Setup", oSysDirString + roDesc.m_pcSetupFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"DriverODBCVer", "02.50");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"SQLLevel", "1");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"FileUsage", "0");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"APILevel", "2");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,pcDriversRegKey,roDesc.m_pcName, "Installed");
	}
	else if (&roDesc == &DriverDescriptionsArray[DBTYPE_MSACCESS])
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"APILevel", "1");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"ConnectFunctions", "YYN");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Driver", oSysDirString + roDesc.m_pcDriverFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Setup", oSysDirString + roDesc.m_pcSetupFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"DriverODBCVer", "02.50");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"SQLLevel", "0");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"FileUsage", "0");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"FileExtns", "*.mdb");
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,pcDriversRegKey,roDesc.m_pcName, "Installed");
	}
	else if (&roDesc == &DriverDescriptionsArray[DBTYPE_SYBASE])
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Driver", oSysDirString + roDesc.m_pcDriverFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Setup", oSysDirString + roDesc.m_pcSetupFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,pcDriversRegKey,roDesc.m_pcName, "Installed");
	}
	else
	{
		ASSERT(false);
	};
};

void CODBCInstaller::UnInstallDriver(EDBType eDBType)
{
	const CODBCDriverDescription & roDesc = DriverDescriptionsArray[eDBType];
	CString oRegKeyString(pcInstRegKey);
	oRegKeyString += roDesc.m_pcName;
	_uninstall_usage_count(oRegKeyString);
};

void CODBCInstaller::InstallTranslator(EDBType eDBType)
{
	const CODBCTranslatorDescription & roDesc = (eDBType == DBTYPE_SQLSERVER) ?  
			SQLServerTranslatorDescription : SybaseTranslatorDescription;

	//windows system
	CString oSysDirString;
	::GetSystemDirectory(oSysDirString.GetBuffer(_MAX_PATH),_MAX_PATH);
	oSysDirString.ReleaseBuffer();
	EnsureEndingBackslash(oSysDirString);

	bool bInUse;
	bool bNewer;
	DWORD dwResult = NAVOSetupFileExIfNewer(GetSrcDir() + roDesc.m_pcFileName,
		oSysDirString + roDesc.m_pcFileName,bInUse,bNewer);
	if(dwResult != ERROR_SUCCESS)
	{
		CString oString;
		oString.Format("instalacja pliku translatora %s nieudana.kod=%d",oSysDirString + roDesc.m_pcFileName,dwResult);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
	m_bInUse |= bInUse;

	CString oRegKeyString(pcInstRegKey);
	oRegKeyString += roDesc.m_pcName;
	_install_usage_count(oRegKeyString);

	if (&roDesc == &SQLServerTranslatorDescription)
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Translator",
			oSysDirString + roDesc.m_pcFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Setup",
			oSysDirString + roDesc.m_pcFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,pcTranslatorsRegKey,roDesc.m_pcName,"Installed");
	}
	if (&roDesc == &SybaseTranslatorDescription)
	{
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Translator",
			oSysDirString + roDesc.m_pcFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,oRegKeyString,"Setup",
			oSysDirString + roDesc.m_pcFileName);
		SafeSetRegistryKeyString(HKEY_LOCAL_MACHINE,pcTranslatorsRegKey,roDesc.m_pcName,"Installed");
	}
	else
	{
		// to do: more Translators
	};
};

void CODBCInstaller::InstallFile(LPCTSTR pcFilePath)
{
	//windows system
	CString oSysDirString;
	::GetSystemDirectory(oSysDirString.GetBuffer(_MAX_PATH),_MAX_PATH);
	oSysDirString.ReleaseBuffer();
	EnsureEndingBackslash(oSysDirString);

	bool bInUse;
	bool bNewer;
	DWORD dwResult = NAVOSetupFileExIfNewer(GetSrcDir() + pcFilePath,
		oSysDirString + pcFilePath,bInUse,bNewer);
	if(dwResult != ERROR_SUCCESS)
	{
		CString oString;
		oString.Format("instalacja pliku %s nieudana, kod =%d",oSysDirString + pcFilePath,dwResult);
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oString);
	}
	m_bInUse |= bInUse;
}

void CODBCInstaller::UnInstallTranslator(EDBType eDBType)
{
	const CODBCTranslatorDescription & roDesc = (eDBType == DBTYPE_SQLSERVER) ?  
			SQLServerTranslatorDescription : SybaseTranslatorDescription;

	CString oRegKeyString(pcInstRegKey);
	oRegKeyString += roDesc.m_pcName;
	_uninstall_usage_count(oRegKeyString);
};

void CODBCInstaller::_install_usage_count(const CString & roRegKeyString)
{
	DWORD dwUsageCount = 0;
	SafeGetRegistryKeyDword(HKEY_LOCAL_MACHINE,roRegKeyString,"UsageCount",dwUsageCount);
	dwUsageCount++;
	SafeSetRegistryKeyDword(HKEY_LOCAL_MACHINE,roRegKeyString,"UsageCount",dwUsageCount);
};

void CODBCInstaller::_uninstall_usage_count(const CString & roRegKeyString)
{
	DWORD dwUsageCount = 0;
	SafeGetRegistryKeyDword(HKEY_LOCAL_MACHINE,roRegKeyString,"UsageCount",dwUsageCount);
	dwUsageCount--;
	SafeSetRegistryKeyDword(HKEY_LOCAL_MACHINE,roRegKeyString,"UsageCount",dwUsageCount);
};


DBTypeDescription DBTypesArray[5] = 
{
	{ DBTYPE_SQLSERVER,	"MSSQL" },
	{ DBTYPE_MSACCESS,	"MSACCESS" },
	{ DBTYPE_SYBASE,	"SYBASE" },
	{ DBTYPE_FOXPRO,	"FOXPRO" },
	{ DBTYPE_DBASE,		"DBASE" },
};

EDBType FindDBTypeIndex(const CString & roDBTypeStr)
{
	for (long lIndex = 0; lIndex < sizeof(DBTypesArray) / sizeof(DBTypeDescription); lIndex++)
	{
		if (!roDBTypeStr.CompareNoCase(DBTypesArray[lIndex].m_DBTypeName))
		{
			return DBTypesArray[lIndex].m_eDBType;
		};
	};
	ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, roDBTypeStr);
};

void PrepareDSNString(CString & rString, _TCHAR * pcText)
{
	lstrcpyn(pcText, rString, 2048);
	while (*pcText)
	{
		if (*pcText == '|')
		{
			*pcText = 0;
		};
		pcText++;
	};
	++pcText;
	*pcText = 0;
};

CString GetODBCErrorMsg()
{
	/*CString oMsgString;
	RETCODE retcode = SQL_SUCCESS;
	WORD indx = 1;
	while(retcode == SQL_SUCCESS)
	{
		DWORD dwErrorCode;
		TCHAR cErrMsg[SQL_MAX_MESSAGE_LENGTH + 1 ] = "\0";
		retcode = ::SQLInstallerError(indx++,&dwErrorCode,cErrMsg,sizeof(cErrMsg),NULL);
		if(retcode == SQL_SUCCESS)
		{
			oMsgString += CString(cErrMsg) + "\r\n";
		}
	}
	return oMsgString;*/
	
	return "";
}

void CODBCInstaller::CreateDSN(EDBType eDBType,bool bSystem,LPCTSTR lpParam)
{
	/*CString oParamString(lpParam);
	_TCHAR acDSD[2048];
	PrepareDSNString(oParamString, acDSD);
	if (!::SQLConfigDataSource(NULL, bSystem ? ODBC_ADD_SYS_DSN : ODBC_ADD_DSN, DriverDescriptionsArray[eDBType].m_pcName, acDSD))
	{
		CString oString;
		oString.Format("SQLConfigDataSource nieudane dla parametrów %s, opis=%s",lpParam, GetODBCErrorMsg());
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,oString);
	};*/
}

void CODBCInstaller::DeleteDSN(EDBType eDBType,bool bSystem,LPCTSTR lpParam)
{
	/*CString oParamString(lpParam);
	_TCHAR acDSD[2048];
	PrepareDSNString(oParamString, acDSD);
	if (!::SQLConfigDataSource(NULL, bSystem ? ODBC_REMOVE_SYS_DSN : ODBC_REMOVE_DSN, DriverDescriptionsArray[eDBType].m_pcName, acDSD))
	{
		CString oString;
		oString.Format("SQLConfigDataSource nieudane dla parametrów %s, opis=%s",lpParam, GetODBCErrorMsg());
		ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,oString);
	};*/
}

