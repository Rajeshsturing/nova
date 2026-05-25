/*
	NAVO Ltd. (after flood)
	Copyright NAVO 1997 
	CFileSystemCollection

	now in NAVO Enterprise 2001
*/
#include "stdafx.h"
#include "filesyscol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CFileSysServer
{
	CMap<CString,LPCTSTR,long,long> m_mapStringIndex;
	CMap<long,long,CString,LPCTSTR> m_mapLongIndex;

public:
	CFileSysServer() {}
	~CFileSysServer() { Done(); }
	void Done();
	long AddOrUpdateItem(LPCTSTR lpItemCode);
	bool Get(long Ident,CString & szNetRes);
};

CFileSysServer _g_FileSysServer;

CFileSysServer & NavoAppGetFSServer()
{
	return _g_FileSysServer;
}

bool CFileSysCollection::NetResFromString(NETRESOURCE & netres,LPCTSTR lpNetResAsString)
{
	netres.dwDisplayType= _ttol(lpNetResAsString);
	lpNetResAsString	= _tcschr(lpNetResAsString,'\t') + 1;

	netres.dwType		= _ttol(lpNetResAsString);
	lpNetResAsString	= _tcschr(lpNetResAsString,'\t') + 1;

	netres.dwScope		= _ttol(lpNetResAsString);
	lpNetResAsString	= _tcschr(lpNetResAsString,'\t') + 1;

	netres.dwUsage		= _ttol(lpNetResAsString);
	lpNetResAsString	= _tcschr(lpNetResAsString,'\t') + 1;

	LPCTSTR ptr = _tcschr(lpNetResAsString,'\t');
	long nLen = ptr - lpNetResAsString;
	netres.lpLocalName = new TCHAR[ nLen + 1 ];
	_tcsncpy(netres.lpLocalName,lpNetResAsString,nLen);
	netres.lpLocalName[ nLen ] = '\0';
	lpNetResAsString = ptr + 1;
	
	ptr = _tcschr(lpNetResAsString,'\t');
	nLen = ptr - lpNetResAsString;
	netres.lpRemoteName = new TCHAR[ nLen + 1 ];
	_tcsncpy(netres.lpRemoteName,lpNetResAsString,nLen);
	netres.lpRemoteName[ nLen ] = '\0';
	lpNetResAsString = ptr + 1;

	ptr = _tcschr(lpNetResAsString,'\t');
	nLen = ptr - lpNetResAsString;
	netres.lpComment = new TCHAR [ nLen + 1 ];
	_tcsncpy(netres.lpComment,lpNetResAsString,nLen);
	netres.lpComment[ nLen ] = '\0';
	lpNetResAsString = ptr + 1;

	netres.lpProvider = new TCHAR[ _tcslen(lpNetResAsString) + 1 ];
	_tcscpy(netres.lpProvider,lpNetResAsString);

	return true;
}

bool CFileSysCollection::StringFromNetRes(CString & szString,const NETRESOURCE & netres)
{
	szString = 
		Long2String(netres.dwDisplayType) + _T("\t") + 
		Long2String(netres.dwScope)		+ _T("\t") + 
		Long2String(netres.dwType)		+ _T("\t") + 
		Long2String(netres.dwUsage)		+ _T("\t") + 
		CString(netres.lpLocalName)		+ _T("\t") + 
		CString(netres.lpRemoteName)	+ _T("\t") + 
		CString(netres.lpComment)		+ _T("\t") + 
		CString(netres.lpProvider);
	return true;
}

bool CFileSysCollection::InternalOpenNet(LPCTSTR lpOpenString)
{
	HANDLE hNetEnum;
	NETRESOURCE netres0;
	if(lpOpenString != NULL)
	{
		VERIFY(NetResFromString(netres0,lpOpenString ));
	}
	
	
	DWORD dwScope = (m_bAll && (lpOpenString == NULL)) ? RESOURCE_GLOBALNET : RESOURCE_CONTEXT;
	NETRESOURCE * pNetRes = ((lpOpenString == NULL) || !m_bAll)? NULL : &netres0;

	DWORD lRes = ::WNetOpenEnum(dwScope ,RESOURCETYPE_ANY,
		(RESOURCEUSAGE_CONNECTABLE | RESOURCEUSAGE_CONTAINER),pNetRes,&hNetEnum);
	if(lRes != NO_ERROR)
		return false;
	
	while(1)
	{
		NETRESOURCE netres[ 20 ];
		DWORD lCount = 20;
		DWORD lBufSize = sizeof(netres);
		
		DWORD lRes = ::WNetEnumResource(hNetEnum,&lCount,(LPVOID)&netres,&lBufSize);
		if(lRes == NO_ERROR || lRes == ERROR_MORE_DATA)
			for(DWORD iter = 0; iter < lCount; iter++)
			{
				long Ident;
				CString szItem;
				if(netres[iter].dwUsage & RESOURCEUSAGE_CONTAINER)
					VERIFY(StringFromNetRes(szItem,netres[iter]));
				else
					szItem = "S"+CString(netres[iter].lpRemoteName);
				
				TRACE1("netopen=%s\n",szItem);

				Ident = NavoAppGetFSServer().AddOrUpdateItem(szItem);
				m_Idents.Add(Ident);
			}
		else
			break;
	}
	::WNetCloseEnum(hNetEnum);
	m_bOpened = true;
	return true;
}

bool CFileSysCollection::InternalOpenDir(LPCTSTR lpOpenString)
{
	ASSERT(lpOpenString);

	CFileFind ff;
	CString szOpenStr = CString(lpOpenString).Mid(1) + _T("\\*.*");
	if(!ff.FindFile( szOpenStr ))
	{
		return false;
	}
	while(ff.FindNextFile())
	{
		if(!ff.IsDots())
		{
			CString szItem = ff.IsDirectory() ? _T("D") : _T("F");
			szItem += ff.GetFilePath();
			m_Idents.Add( NavoAppGetFSServer().AddOrUpdateItem(szItem) );
		}
	}
	if(!ff.IsDots())
	{
		CString szItem = ff.IsDirectory() ? _T("D") : _T("F");
		szItem += ff.GetFilePath();
		m_Idents.Add( NavoAppGetFSServer().AddOrUpdateItem(szItem) );
	}
	ff.Close();
	m_bOpened = true;
	return true;
}

bool CFileSysCollection::InternalOpen(LPCTSTR lpOpenString)
{
	if(lpOpenString == NULL || IsDigit(*lpOpenString))
	{
		return InternalOpenNet(lpOpenString);
	}
	return InternalOpenDir(lpOpenString);
}

bool CFileSysCollection::Open(long StartingIdent)
{
	CString szNetResAsString;
	if(StartingIdent != 0)
	{
		VERIFY(NavoAppGetFSServer().Get(StartingIdent,szNetResAsString));
		return InternalOpen(szNetResAsString);
	}
	return InternalOpen(NULL);
}

bool CFileSysCollection::Open(LPCTSTR lpDir)
{
	return InternalOpen(lpDir);
}

void CFileSysCollection::GetInParts(long & Ident,CString & oItemName,TCHAR & cType,
	NETRESOURCE * pInfo)
{
	CString oString;
	NavoAppGetFSServer().Get(m_Idents[m_nPos],oString);
	ASSERT(oString.GetLength() > 0 );

	Ident = m_Idents[m_nPos];
	oItemName = oString.Mid(1);
	cType = oString[0];
	
	if(pInfo)
	{
		NetResFromString( *pInfo, oString );
	}
}


/*
	"file system server"
*/

void CFileSysServer::Done()
{
	m_mapStringIndex.RemoveAll();
	m_mapLongIndex.RemoveAll();
}

long CFileSysServer::AddOrUpdateItem(LPCTSTR lpItemCode)
{
	long Ident;
	if(!m_mapStringIndex.Lookup(lpItemCode,Ident))
	{
		Ident = m_mapStringIndex.GetCount() + 1;
		m_mapStringIndex.SetAt(lpItemCode,Ident);
		m_mapLongIndex.SetAt(Ident,lpItemCode);
	}
	return Ident;
}

bool CFileSysServer::Get(long Ident,CString & szNetRes)
{
	return m_mapLongIndex.Lookup(Ident,szNetRes) != FALSE;
}

