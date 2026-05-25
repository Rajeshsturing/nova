/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCOMUserThreadHolder - holder CUserThreada dla com'a
*/

#ifndef _COMUSERTHREADHOLDER_H_
#define _COMUSERTHREADHOLDER_H_


class CCOMUserThreadHolder : public CCmdTarget
{
	DECLARE_DYNCREATE(CCOMUserThreadHolder)
	CCOMUserThreadHolder();           // protected constructor used by dynamic creation
public:
	//{{AFX_VIRTUAL(CCOMUserThreadHolder)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL
protected:
	virtual ~CCOMUserThreadHolder();

	//{{AFX_MSG(CCOMUserThreadHolder)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CCOMUserThreadHolder)

	//{{AFX_DISPATCH(CCOMUserThreadHolder)
	afx_msg LPDISPATCH GetUserThreadAUTO();
	afx_msg BOOL LoginAUTO(LPCTSTR lpUser, LPCTSTR lpPwd);
	afx_msg void SetAsyncModeAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	SCP<CUserThread>	m_poUserThreadSP;
	bool	m_bAsyncMode;
};


#else
	#error __FILE__ already included
#endif
