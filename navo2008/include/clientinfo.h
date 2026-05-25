/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	ClientInfo - describes manager's client (object which 
	has logged in user and resides on computer);
*/

#ifndef _CLIENTINFO
#define _CLIENTINFO

class CClientInfo : public CInterface__
{
public:
	CClientInfo(LPCTSTR lpUserName = _T(""),LPCTSTR lpComputerName = _T("")) :
		m_oUserNameString(lpUserName),
		m_oComputerNameString(lpComputerName),
		m_poClientPropertyHLISP(NewSCP(new CHyperLinkInfo())),
		m_nCookie(__InitCookie())
	{
	}
	LPCTSTR GetUserName() const
	{
		return m_oUserNameString;
	}
	LPCTSTR GetComputerName() const
	{
		return m_oComputerNameString;
	}
	long GetCookie() const
	{
		return m_nCookie;
	}
	SCP<CHyperLinkInfo> & _client_properties()
	{
		return m_poClientPropertyHLISP;
	}
	friend CArchive & AFXAPI operator << (CArchive & oArchive,const CClientInfo & roClientInfo);
	friend CArchive & AFXAPI operator >> (CArchive & oArchive, CClientInfo & roClientInfo);
protected:
	long __InitCookie() const
	{
		return reinterpret_cast<long>(this);
	}
	long	m_nCookie;
	CString m_oUserNameString;
	CString m_oComputerNameString;
	SCP<CHyperLinkInfo>		m_poClientPropertyHLISP;
};

class CClientInfoArray : public CArray<CClientInfo,CClientInfo&>
{
public:
	CClientInfoArray()
	{
	}
	friend CArchive & AFXAPI operator << (CArchive & oArchive,const CClientInfoArray & roClientInfoArray);
	friend CArchive & AFXAPI operator >> (CArchive & oArchive, CClientInfoArray & roClientInfoArray);
};

HRESULT QueryNotificationManagerClients(SCP<INotificationManager> & rpoNotificationManageSP,
				   CClientInfoArray & roClientInfoArray);

//--------------------------------- inlinez ---------------------------------------------

inline CArchive & AFXAPI operator << (CArchive & oArchive,const CClientInfo & roClientInfo)
{
	oArchive  << roClientInfo.GetCookie()
			  << CString(roClientInfo.GetComputerName())
			  << CString(roClientInfo.GetUserName())
			  << *roClientInfo.m_poClientPropertyHLISP;
	return oArchive;
}

inline CArchive & AFXAPI operator >> (CArchive & oArchive, CClientInfo & roClientInfo)
{
	oArchive >> roClientInfo.m_nCookie 
			 >> roClientInfo.m_oComputerNameString 
			 >>	roClientInfo.m_oUserNameString 
			 >> *roClientInfo.m_poClientPropertyHLISP;
	return oArchive;
}

inline CArchive & AFXAPI operator << (CArchive & oArchive,CClientInfoArray & roClientInfoArray)
{
	roClientInfoArray.Serialize(oArchive);
	return oArchive;
}

inline CArchive & AFXAPI operator >> (CArchive & oArchive, CClientInfoArray & roClientInfoArray)
{
	roClientInfoArray.Serialize(oArchive);
	return oArchive;
}

template<>
inline void AFXAPI SerializeElements<CClientInfo>(CArchive& ar, CClientInfo* pElements, int nCount)
{
	if (ar.IsStoring())
	{
		for (; nCount--; ++pElements)
			ar << *pElements;
	}
	else
	{
		for (; nCount--; ++pElements)
			ar >> *pElements;
	}
}


#else
	#error __FILE__ already included
#endif
