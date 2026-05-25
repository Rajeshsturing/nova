/*
	NAVO Enterprise 2001
	web transfer object
*/

#include "stdafx.h"
#include "resource.h"
#include <afxinet.h>
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\include\progressgadget.h"
#include "WebTransfer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOINET_Instance;


class CHttpFileCloseHolder
{
public:
	CHttpFileCloseHolder(CHttpFile * poHttpFile) :
		m_poHttpFile(poHttpFile)
	{
	}
	~CHttpFileCloseHolder()
	{
		if(m_poHttpFile)
		{
			m_poHttpFile->Close();
			delete m_poHttpFile;
		}
	}
private:
	CHttpFile * m_poHttpFile;
};

/////////////////////////////////////////////////////////////////////////////
// CWebTransfer

IMPLEMENT_DYNCREATE(CWebTransfer, CCmdTargetInterface)

CWebTransfer::CWebTransfer() :
	m_dwLastError(0),
	m_pConnection(NULL),
	m_bWeEstablishedConnection(false),
	m_bSilent(false)
{
	EnableAutomation();
	
	AfxOleLockApp();
}

CWebTransfer::~CWebTransfer()
{
	if(m_bWeEstablishedConnection)
	{
		CAfxResourceHandleHolder oARHH(_h_NAVOINET_Instance);
		if(AfxMessageBox(IDS_WANT_HANGUP,MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			::InternetAutodialHangup(0);
		}
	}
	if(m_pConnection)
	{
		m_pConnection->Close();
		delete m_pConnection;
	}
	AfxOleUnlockApp();
}


void CWebTransfer::OnFinalRelease()
{
	CCmdTargetWithErrorInfo::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CWebTransfer, CCmdTargetWithErrorInfo)
	//{{AFX_MSG_MAP(CWebTransfer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWebTransfer, CCmdTargetWithErrorInfo)
	//{{AFX_DISPATCH_MAP(CWebTransfer)
	DISP_FUNCTION(CWebTransfer, "connect", ConnectAUTO, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL)
	DISP_FUNCTION(CWebTransfer, "get", GetAUTO, VT_VARIANT, VTS_BSTR)
	DISP_FUNCTION(CWebTransfer, "post", PostAUTO, VT_VARIANT, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CWebTransfer, "lasterror", GetLastErrorAUTO, VT_I4, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// {3405CBE6-BCB5-48AA-B0FB-061B67A9D143}
static const IID IID_IWebTransfer =
{ 0x3405cbe6, 0xbcb5, 0x48aa, { 0xb0, 0xfb, 0x6, 0x1b, 0x67, 0xa9, 0xd1, 0x43 } };

BEGIN_INTERFACE_MAP(CWebTransfer, CCmdTargetWithErrorInfo)
	INTERFACE_PART(CWebTransfer, IID_IWebTransfer, Dispatch)
END_INTERFACE_MAP()

// {188cb174-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CWebTransfer, "navoinet.webtransfer", 0x188cb174,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CWebTransfer message handlers

long CWebTransfer::ConnectAUTO(LPCTSTR lpServer, LPCTSTR lpUser, LPCTSTR lpPassword, BOOL bSilent) 
{
	ALL_TRY
	{
		DWORD dwFlags;
		if(!::InternetGetConnectedState(&dwFlags,0))
		{
#if defined(_NAVODOTNET) || defined(NAVO2008)
			if(!::InternetAutodial(INTERNET_AUTODIAL_FORCE_ONLINE,::GetActiveWindow()))
#else
			if(!::InternetAutodial(INTERNET_AUTODIAL_FORCE_ONLINE,(DWORD)::GetActiveWindow()))
#endif
			{
				m_dwLastError = (DWORD) -1;
				return m_dwLastError;
			}
			m_bWeEstablishedConnection = true;
		}
		/*
		if(::InternetAttemptConnect(0) != ERROR_SUCCESS)
		{
			m_dwLastError = (DWORD) -1;
			return m_dwLastError;
		}
		*/
		SCP<CPerformingDialogHolder> poPDHSP;
		if(m_oServerString != lpServer)
		{
			if(m_pConnection)
			{
				m_pConnection->Close();
			}
			if(!bSilent)
			{
				CAfxResourceHandleHolder oARHH(_h_NAVOINET_Instance);
				CString oMsgString;
				oMsgString.Format(IDS_CONNECTING_TO_WWW_SERVER,lpServer);
				poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));
			}
			TRACE3("Connecting (%s,%s,%s)\n",lpServer,lpUser,lpPassword);
			m_pConnection = m_oInternetSession.GetHttpConnection(lpServer,INTERNET_INVALID_PORT_NUMBER,
				lpUser,lpPassword);
			if(!InternetCheckConnection(lpServer,0,0))
			{
				m_pConnection->Close();
				m_dwLastError = ::GetLastError();
				return m_dwLastError;
			}
			m_oServerString = lpServer;
		}
		m_bSilent = (bSilent != FALSE);
		return 0;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

VARIANT CWebTransfer::GetAUTO(LPCTSTR lpServerPath) 
{
	ALL_TRY
	{
		SCP<CPerformingDialogHolder> poPDHSP;
		if(!m_bSilent)
		{
			CAfxResourceHandleHolder oARHH(_h_NAVOINET_Instance);
			CString oMsgString;
			oMsgString.LoadString(IDS_DOWNLOADING_FROM_WWW);
			poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));
		}
		CSmartOleVariant oSOV;
		ASSERT(m_pConnection);
		TRACE1("GET (%s)\n",lpServerPath);
		CHttpFile * pHttpFile = m_pConnection->OpenRequest("GET",lpServerPath,NULL,1,NULL,NULL,
			 INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_CACHE_WRITE);
		CHttpFileCloseHolder oHFCH(pHttpFile);
		if(pHttpFile == NULL)
		{
			m_dwLastError = ::GetLastError();
		}
		else
		{
_retry:
			try
			{
				VERIFY(pHttpFile->SendRequestEx(0,HSR_SYNC));
				VERIFY(pHttpFile->EndRequest());
				CString oServerResponseString;
				VERIFY(pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF,oServerResponseString));
				TRACE1("response = %s\n",oServerResponseString);
				VERIFY(pHttpFile->QueryInfoStatusCode(m_dwLastError));
				if(m_dwLastError >= 200 && m_dwLastError <= 202)	//well known success codes
				{
					SCP<IStream> poResultStreamSP = CreateTempFileStream();
					while(pHttpFile->GetLength())	//actually number of unread bytes !!!!
					{
						ReadStreamFromFile(pHttpFile,poResultStreamSP);
					}
					CStreamHolder oSH(poResultStreamSP);
					oSH.SeekToBegin();
					oSOV = CSmartOleVariant(poResultStreamSP);
				}
			}
			catch(CInternetException * pException)
			{
				if(pException->m_dwError == ERROR_INTERNET_FORCE_RETRY)
				{
					goto _retry;
				}
				CString oString;
				pException->GetErrorMessage(oString.GetBuffer(512),512);
				oString.ReleaseBuffer();
				pException->Delete();
				ThrowNavoException1(ERCO_INET_UPLOAD_ERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)oString);
			}
		}
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

VARIANT CWebTransfer::PostAUTO(LPCTSTR lpServerPath, const VARIANT FAR& pInputStream) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		ASSERT(m_pConnection);
		TRACE1("POST (%s)\n",lpServerPath);
		CHttpFile * pHttpFile = m_pConnection->OpenRequest("POST",lpServerPath,NULL,1,NULL,
			NULL,INTERNET_FLAG_NO_CACHE_WRITE );
		CHttpFileCloseHolder oHFCH(pHttpFile);
		if(pHttpFile == NULL)
		{
			m_dwLastError = ::GetLastError();
		}
		else
		{
			CSmartOleVariant oInputSOV(pInputStream);
			SCP<IStream> poInputStreamSP = OpenFileStream_Read_On_SOV(oInputSOV);
			ASSERT(poInputStreamSP.PointsObject());
			long nStreamLength = GetStreamSize(poInputStreamSP);
_retry:
			try
			{
				VERIFY(pHttpFile->SendRequestEx(nStreamLength));
				HRESULT hr = SaveStreamToFile(poInputStreamSP, pHttpFile);
				ASSERT(hr == S_OK);
				VERIFY(pHttpFile->EndRequest());
				CString oServerResponseString;
				VERIFY(pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF,oServerResponseString));
				TRACE1("response = %s\n",oServerResponseString);
				VERIFY(pHttpFile->QueryInfoStatusCode(m_dwLastError));
				if(m_dwLastError >= 200 && m_dwLastError <= 202)	//well known success codes
				{
					SCP<IStream> poResultStreamSP = CreateTempFileStream();
					ReadStreamFromFile(pHttpFile,poResultStreamSP);
					CStreamHolder oSH(poResultStreamSP);
					oSH.SeekToBegin();
					oSOV = CSmartOleVariant(poResultStreamSP);
				}
			}
			catch(CInternetException * pException)
			{
				if(pException->m_dwError == ERROR_INTERNET_FORCE_RETRY)
				{
					pException->Delete();
					goto _retry;
				}
				CString oString;
				pException->GetErrorMessage(oString.GetBuffer(512),512);
				oString.ReleaseBuffer();
				pException->Delete();
				ThrowNavoException1(ERCO_INET_UPLOAD_ERROR,IDPAGE_NOTAVAILABLE,(LPCTSTR)oString);
			}
		}
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CWebTransfer::GetLastErrorAUTO() 
{
	ALL_TRY
	{
		return m_dwLastError;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
