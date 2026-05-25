/*
	NAVO Enterprise 2008 (c)

	26.07.2002
	
	class:
		cndoc_external_client

		obudowa dla dostêpu do navo2002.client z zewn¹trz
*/

#ifndef _EXTERNAL_CLIENT_NDOC_H_
#define _EXTERNAL_CLIENT_NDOC_H_

class cndoc_application;

class cndoc_external_client : public CCmdTarget
{
public:
	cndoc_external_client();
	~cndoc_external_client();

	DECLARE_DYNCREATE(cndoc_external_client)

	DECLARE_OLECREATE(cndoc_external_client)

	//{{AFX_DISPATCH(cndoc_external_client)
	afx_msg LPDISPATCH GetUserThreadAUTO();
	afx_msg BOOL LoginAUTO(LPCTSTR lpUser, LPCTSTR lpPwd);
	afx_msg void SetAsyncModeAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	cndoc_application * m_poApplication;
	bool	m_bAsyncMode;
};

#else
	#error __FILE__ already included
#endif
