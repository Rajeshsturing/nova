/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	ClientInfo - describes manager's client (object which 
	has logged in user and resides on computer);
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\clientinfo.h"


HRESULT QueryNotificationManagerClients(SCP<INotificationManager> & rpoNotificationManageSP,
				   CClientInfoArray & roClientInfoArray)
{

	ASSERT(rpoNotificationManageSP.PointsObject());
	CRPCLoader_via_Archive< CClientInfoArray > oRPCLoader(roClientInfoArray);

	if (IsNXMTransport())
	{
		long pLength;
		SAFEARRAY * pData = NULL;
		
		HRESULT hr = rpoNotificationManageSP->QuerySinks2(&pLength, &pData);

		if (hr == S_OK)
		{
			void * pBinData;
			SafeArrayAccessData(pData, &pBinData);
			(*oRPCLoader.GetLength()) = pLength;
			(*oRPCLoader.GetData()) = (BYTE*)pBinData;
			oRPCLoader.Load();
			SafeArrayUnaccessData(pData);
			SafeArrayDestroy(pData);
			oRPCLoader.m_oRemoteFreeHolder.Release();
		}

		return hr;
	}
	else
	{
		HRESULT hr = rpoNotificationManageSP->QuerySinks(oRPCLoader.GetLength(), oRPCLoader.GetData());

		if (hr == S_OK)
		{
			oRPCLoader.Load();
		}

		return hr;
	}
}

