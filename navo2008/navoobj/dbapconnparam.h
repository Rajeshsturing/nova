/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDBAP_ConnectionParam

	parametry pol¹czenia do Objectservera
*/

#ifndef _DBAPCONNPARAM_H_
#define _DBAPCONNPARAM_H_

struct CDBAP_ConnectionParam
{
	CDBAP_ConnectionParam():
		m_nEngineType(long(dbet_ms_sql70)),
		m_bCompressTrafficToClient(false)
	{
	}
	
	SCP<IServerClient>	m_poServerClientSP;		//server client connection

	LPCTSTR m_lpServerName;		//remote computer name
	LPCTSTR m_lpDBName;			//db name
	LPCTSTR m_lpUserName;		//user name
	LPCTSTR m_lpPassword;		//password
	LPCTSTR m_lpAppName;		//application Name
	long	m_nEngineType;		//db engine type
	bool	m_bCompressTrafficToClient;
};

#else
	#error __FILE__ already included
#endif
