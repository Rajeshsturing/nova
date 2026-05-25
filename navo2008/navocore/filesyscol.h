/*
	NAVO Ltd. (after flood)
	Copyright NAVO 1997 
	CFileSystemCollection
	
	now in NAVO Enterprise 2001
*/


#ifndef _FILESYSCOL_H_
#define _FILESYSCOL_H_

/*
	uzyj parametru bAll = true i wtedy powoli uzyskasz obraz:
		Cala siec
			Windows Network
				Domeny
					Komputery

	albo bAll = false i dostaniecz
		Cala siec
		Komputery
*/


class CFileSysCollection
{
public:
	CFileSysCollection(bool bAll = false)
	{
		m_bOpened = FALSE;
		m_nPos = -1;
		m_bAll = bAll;
	}

	~CFileSysCollection()
	{
		Close();
	}

	//rozpocznij iteracjê
	virtual bool GoFirst()
	{
		m_nPos = 0;
		return (m_Idents.GetUpperBound() >= 0);
	}
	//przejdŸ do nastêpnego
	virtual bool GoNext()
	{
		if(m_nPos >= m_Idents.GetUpperBound())
			return false;
		m_nPos++;
		return true;
	}

	//we¿ dane bie¿¹cego rekordu
	void GetInParts(long & Ident,CString & oItemName,TCHAR & cType,NETRESOURCE * pInfo = NULL);

	bool Open(long StartingIdent = 0);			//for network browsing
	bool Open(LPCTSTR lpDir);					//for directory browsing
	void Close()
	{
		if(!m_bOpened) return;
		m_Idents.RemoveAll();
		m_bOpened = false;
	}
private:
	CDWordArray		m_Idents;
	long			m_nPos;
	bool			m_bAll;
	CFileFind		m_ff;
	enum Type
	{
		netcursor,
		dircursor
	};
	Type			m_Type;
	bool			m_bOpened;
	

	bool InternalOpenNet(LPCTSTR lpOpenStr);	
	bool InternalOpenDir(LPCTSTR lpOpenStr);	
	bool InternalOpen(LPCTSTR lpOpenStr);	

	static bool NetResFromString(NETRESOURCE & netres,LPCTSTR lpNetResAsString);
	static bool StringFromNetRes(CString & szString,const NETRESOURCE & netres);
};


#else
	#error __FILE__ already included
#endif
