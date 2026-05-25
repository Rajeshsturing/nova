/*
	NAVO Enterprise 2001
	Copyright NAVO (c) 2001
	odbc installation support class
*/

#ifndef _ODBCINSTALL_H_
#define _ODBCINSTALL_H_

enum EDBType
{
	DBTYPE_SQLSERVER = 0,
	DBTYPE_SYBASE = 1,
	DBTYPE_MSACCESS = 2,
	DBTYPE_FOXPRO = 3,
	DBTYPE_DBASE = 4,
};

struct DBTypeDescription
{
	EDBType m_eDBType;
	LPCTSTR m_DBTypeName;
};

struct CODBCDriverDescription
{
	LPCTSTR m_pcName;
	LPCTSTR m_pcDriverFileName;
	LPCTSTR m_pcSetupFileName;
	LPCTSTR m_pcDSN;
};

struct CODBCTranslatorDescription
{
	LPCTSTR m_pcName;
	LPCTSTR m_pcFileName;
};


class CODBCInstaller
{
public:
	CODBCInstaller(LPCTSTR pcSrcDirectory):
		m_oSrcDirString(pcSrcDirectory),
		m_bInUse(false)
	{
		EnsureEndingBackslash(m_oSrcDirString);
	};
	void UnInstallDriver(EDBType eDBType);
	void InstallDriver(EDBType eDBType);
	void UnInstallTranslator(EDBType eDBType);
	void InstallTranslator(EDBType eDBType);
	void InstallFile(LPCTSTR pcFilePath);
	void CreateDSN(EDBType eDBType,bool bSystem,LPCTSTR lpParam);
	void DeleteDSN(EDBType eDBType,bool bSystem,LPCTSTR lpParam);
private:
	void _install_usage_count(const CString & roRegKeyString);
	void _uninstall_usage_count(const CString & roRegKeyString);

	const CString & GetSrcDir() const
	{
		return m_oSrcDirString;
	};
	CString m_oSrcDirString;
	bool	m_bInUse;
};

EDBType FindDBTypeIndex(const CString & oDBTypeStr);

#else
	#error __FILE__ already included
#endif
