/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    security.h

Abstract:

    Functions to handle communication with the security package

Revision History:

--*/

//-------------------------------------------------
//	this is NOT RECURSIVE (when you are 
//  logged as someone else, you cannot logon once more)
//-------------------------------------------------

class CLogonAsUser
{
public:
	CLogonAsUser() :
		m_bRevert(false)
	{
	}
	bool Logon(bool bForever,HWND hWndParent = (HWND) NULL);
	bool Logon(LPCTSTR lpDomain,LPCTSTR lpUser,LPCTSTR lpPwd,bool bForever);
	~CLogonAsUser();
private:
	bool m_bRevert;
};