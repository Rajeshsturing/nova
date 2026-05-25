/*
	NAVO Enterprise 2020
	setup application
*/

#if !defined(AFX_SETUP_H__9FAFF628_6AA8_40A3_BA2C_4F5418EFEFF1__INCLUDED_)
#define AFX_SETUP_H__9FAFF628_6AA8_40A3_BA2C_4F5418EFEFF1__INCLUDED_

class CSetupApp : public CWinApp
{
public:
	CSetupApp();
	//{{AFX_VIRTUAL(CSetupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSetupApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	const CString & _get_program_fullpath() const
	{
		return m_oThisProgramFullPathString;
	}
	const CString & _get_program_dir() const
	{
		return m_oThisProgramDirString;
	}

	setuperror _install_components();
	setuperror _install_application();

	setuperror _prepare_restart_info();
	void _clean_restart_info();

private:
	CString	 m_oThisProgramFullPathString;
	CString	 m_oThisProgramDirString;
	const TCHAR * m_pcRunOnceName;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP_H__9FAFF628_6AA8_40A3_BA2C_4F5418EFEFF1__INCLUDED_)
