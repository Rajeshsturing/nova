/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CSmartSocket

	small but smart socket wrapper
*/

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CStartupCleanupHolder::CStartupCleanupHolder(WORD hiVersion,WORD loVersion) :
	m_nResult(0),
	m_bClean(false)
{
	WSADATA wsaData;
	m_nResult = ::WSAStartup(MAKEWORD(hiVersion,loVersion),&wsaData);
	if(m_nResult == 0)
	{
		m_bClean = true;

		if(LOBYTE(wsaData.wVersion) != loVersion ||
		   HIBYTE(wsaData.wVersion) != hiVersion) 
		{
			m_nResult = WSAVERNOTSUPPORTED;
		}
	}
}

CStartupCleanupHolder::~CStartupCleanupHolder()
{
	if(m_bClean)
	{
		::WSACleanup();
	}
}

CString CSmartSocket::WSAGetLastErrorToString()
{
	long nResult = ::WSAGetLastError();
	switch(nResult)
	{
	case WSAECONNABORTED:
		return "po³¹czenie przerwane na tym komputerze";
	case WSAECONNRESET:
		return "po³¹czenie przerwane na zdalnym komputerze";
	case WSAEADDRINUSE:
		return "port w u¿yciu przez inn¹ aplikacjê";
	default:
		return Long2String(nResult);
	}
}
