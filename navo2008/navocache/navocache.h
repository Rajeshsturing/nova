/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Cache Server EXE
*/

#if !defined(AFX_NAVOCACHE_H__E85118C5_AAA1_4BF1_945C_F5C31805966C__INCLUDED_)
#define AFX_NAVOCACHE_H__E85118C5_AAA1_4BF1_945C_F5C31805966C__INCLUDED_


class CNavoCacheApp : public CWinApp
{
public:
	CNavoCacheApp();

	//{{AFX_VIRTUAL(CNavoCacheApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNavoCacheApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SCP<CNavoOleInitHolder> m_poNOIHSP;
};

#endif // !defined(AFX_NAVOCACHE_H__E85118C5_AAA1_4BF1_945C_F5C31805966C__INCLUDED_)
