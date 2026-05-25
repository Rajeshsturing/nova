/*
	NAVO Enterprise 2001
	web transfer object
*/

#if !defined(AFX_WEBTRANSFER_H__A0C7DEA2_151E_4FAC_AB3F_CE0D9F3E87C3__INCLUDED_)
#define AFX_WEBTRANSFER_H__A0C7DEA2_151E_4FAC_AB3F_CE0D9F3E87C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CWebTransfer command target

class CWebTransfer : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CWebTransfer)

	CWebTransfer();           // protected constructor used by dynamic creation

public:
	//{{AFX_VIRTUAL(CWebTransfer)
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

protected:
	virtual ~CWebTransfer();

	//{{AFX_MSG(CWebTransfer)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CWebTransfer)

	//{{AFX_DISPATCH(CWebTransfer)
	afx_msg long ConnectAUTO(LPCTSTR lpServer, LPCTSTR lpUser, LPCTSTR lpPassword, BOOL bSilent);
	afx_msg VARIANT GetAUTO(LPCTSTR lpServerPath);
	afx_msg VARIANT PostAUTO(LPCTSTR lpServerPath, const VARIANT FAR& pInputStream);
	afx_msg long GetLastErrorAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CString				m_oServerString;

	CInternetSession	m_oInternetSession;
	CHttpConnection *	m_pConnection;
	DWORD				m_dwLastError;
	bool				m_bWeEstablishedConnection;
	bool				m_bSilent;
};


#endif // !defined(AFX_WEBTRANSFER_H__A0C7DEA2_151E_4FAC_AB3F_CE0D9F3E87C3__INCLUDED_)
