/*
	NAVO Enterprise 2020
	setup application

	component installer
*/

#ifndef _COMPONENT_INSTALLER_H_
#define _COMPONENT_INSTALLER_H_

class CComponentInstaller
{
public:
	virtual bool _need_install();
	virtual setuperror _install();
	virtual setuperror _uninstall();

	LPCTSTR _human_name() const;

	eNEComponent _type() const
	{
		return m_eComponentType;
	}
	CComponentInstaller(eNEComponent eComponentType) :
		m_eComponentType(eComponentType)
	{
	}
protected:
	virtual LPCTSTR _key_file_name() const;
	LPCTSTR _subdir_name() const;
	const CLSID * _checked_clsid() const;
	LPCTSTR _required_version() const;

	eNEComponent m_eComponentType;
};

class CWinInstInstaller : public CComponentInstaller
{
public:
	CWinInstInstaller() : CComponentInstaller(nec_wininst)
	{
	}
	virtual bool _need_install();
	virtual LPCTSTR _key_file_name() const;
};

class CProgressInfo;
enum eDestType;

class CFileInfo
{
public:
	eDestType m_eDT;
	LPCTSTR m_poName;
	LPCTSTR m_poVersion;
	long	m_nRegisterMethod;
	LPCTSTR m_poArguments;
	bool	m_bCopy;
	bool    m_bDownload;
};

class CNE2002Installer : public CComponentInstaller
{
public:
	CNE2002Installer() : CComponentInstaller(nec_engine)
	{
	}
	virtual bool _need_install();
	virtual setuperror _install();
	virtual setuperror _uninstall();

	setuperror _create_dirs( CProgressInfo& roProgressInfo);
	setuperror _update_registry( CProgressInfo& roProgressInfo);
	setuperror _download_files( CProgressInfo& roProgressInfo);
	setuperror _verify_files( CProgressInfo& roProgressInfo);
	setuperror _copy_files( CProgressInfo& roProgressInfo);
	setuperror _unregister_files( CProgressInfo& roProgressInfo);
	setuperror _register_files (CProgressInfo& roProgressInfo);
	setuperror FindSourcePath (CString & roReturnPath, CFileInfo & roFileInfo);
	setuperror UserFindSourcePath (CString & roReturnPath, CFileInfo & roFileInfo);

	setuperror _register_uninstall_info();
	bool IsVersionValid (const CString & roFilePath, const CString & roVersion);


private:
	CString m_oUserDir;
	CMapStringToString m_oFilesMap;
};

class CDCOMInstaller : public CComponentInstaller
{
public:
	CDCOMInstaller() : CComponentInstaller(nec_dcom)
	{
	}
	virtual bool _need_install();
};

class CVBSInstaller : public CComponentInstaller
{
public:
	CVBSInstaller() : CComponentInstaller(nec_vbscript)
	{
	};
	virtual LPCTSTR _key_file_name() const;
};

class CDotNetInstaller : public CComponentInstaller
{
public:
	CDotNetInstaller() : CComponentInstaller(nec_dotnet)
	{
	};
	virtual bool _need_install();
	virtual LPCTSTR _key_file_name() const;
};

#else
	#error __FILE__ already included
#endif
