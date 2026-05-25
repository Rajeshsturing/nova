/*
	NAVO Enterprise 2001
	mail support
*/

#include "stdafx.h"
#include "resource.h"
#include "msmapi32.h"
#include "MailSession.h"
#include "..\include\progressgadget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOINET_Instance;

IMPLEMENT_DYNCREATE(CMailSession, CCmdTarget)

CMailSession::CMailSession():
	m_bFetchValid(false),
	m_bLastUnread(false)
{
	EnableAutomation();
	AfxOleLockApp();
}

CMailSession::~CMailSession()
{
	if(m_oMapiSession)
	{
		m_oMapiSession.SignOff();
	}
	AfxOleUnlockApp();
}


void CMailSession::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMailSession, CCmdTarget)
	//{{AFX_MSG_MAP(CMailSession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMailSession, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CMailSession)
	DISP_FUNCTION(CMailSession, "connect", ConnectAUTO, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CMailSession, "addattachment", AddAttachmentAUTO, VT_EMPTY, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CMailSession, "addrecip", AddRecipmentAUTO, VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CMailSession, "send", SendAUTO, VT_BOOL, VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CMailSession, "download", DownLoadAUTO, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CMailSession, "read", ReadMsgAUTO, VT_BOOL, VTS_I4 VTS_BOOL VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CMailSession, "getattachment", GetAttachmentAUTO, VT_BOOL, VTS_I4 VTS_PVARIANT VTS_PVARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMailSession to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2FBFF224-61A8-4A15-AC63-0A46DADA4FB3}
static const IID IID_IMailSession =
{ 0x2fbff224, 0x61a8, 0x4a15, { 0xac, 0x63, 0xa, 0x46, 0xda, 0xda, 0x4f, 0xb3 } };

BEGIN_INTERFACE_MAP(CMailSession, CCmdTarget)
	INTERFACE_PART(CMailSession, IID_IMailSession, Dispatch)
END_INTERFACE_MAP()

// {188cb173-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CMailSession, "navoinet.Mail", 0x188cb173,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CMailSession message handlers

BOOL CMailSession::ConnectAUTO(LPCTSTR lpUser, LPCTSTR lpPassword) 
{
	ALL_TRY
	{
		if(!m_oMapiSession.CreateDispatch("MSMAPI.MAPISession"))
		{
			return FALSE;
		}
		m_oMapiSession.SetDownLoadMail(FALSE);
		m_oMapiSession.SetLogonUI(TRUE);
		m_oMapiSession.SetUserName(lpUser);
		m_oMapiSession.SetPassword(lpPassword);
		m_oMapiSession.SignOn();
		m_bFetchValid = false;
		m_bLastUnread = false;
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		m_oMapiSession.ReleaseDispatch();
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CMailSession::DownLoadAUTO(LPCTSTR lpUser, LPCTSTR lpPassword) 
{
	ALL_TRY
	{
		if(!m_oMapiSession.CreateDispatch("MSMAPI.MAPISession"))
		{
			return FALSE;
		}
		m_oMapiSession.SetDownLoadMail(TRUE);
		m_oMapiSession.SetLogonUI(TRUE);
		m_oMapiSession.SetUserName(lpUser);
		m_oMapiSession.SetPassword(lpPassword);
		m_oMapiSession.SignOn();
		m_bFetchValid = false;
		m_bLastUnread = false;
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		m_oMapiSession.ReleaseDispatch();
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CMailSession::AddAttachmentAUTO(LPCTSTR lpName, const VARIANT FAR& pStream) 
{
	ALL_TRY
	{
		SCP<IStream> poStreamSP = OpenFileStream_Read_On_SOV(reinterpret_cast<const CSmartOleVariant &>(pStream));
		SCP<CFileRemover> poFileRemoverSP;

		CStreamHolder(poStreamSP).SeekToBegin();
		CString oFileNameString = GenerateUniqueFileName("MA","TMP");	//MA - mail attachment
		ULARGE_INTEGER ulInfinity;
		ulInfinity.QuadPart = MAXLONG;
		HRESULT hr = IStream_CopyTo(poStreamSP,CreateFileStream_Write_On_SOV(
			CSmartOleVariant(oFileNameString),poFileRemoverSP),ulInfinity);
		ASSERT(hr == S_OK);	//to_do: error handling
		m_oAttachmentArray.Add(CAttachment(lpName,oFileNameString,poFileRemoverSP));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CMailSession::AddRecipmentAUTO(LPCTSTR lpAddress, LPCTSTR lpName) 
{
	ALL_TRY
	{
		m_oRecipmentArray.Add(CRecipment(lpAddress,lpName));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CMailSession::SendAUTO(LPCTSTR lpSubject, LPCTSTR lpMsg, long nFormat) 
{
	ALL_TRY
	{
		{
			IMapiMessages oMapiMessages;
			if(!oMapiMessages.CreateDispatch("MSMAPI.MAPIMessages"))
			{
				return FALSE;
			}
			oMapiMessages.SetSessionID(m_oMapiSession.GetSessionID());
			oMapiMessages.Compose();
			oMapiMessages.SetAddressResolveUI(TRUE);
			CString oString(' ',2 + m_oAttachmentArray.GetSize());

			//musimy dodaæ spacje aby by³y pozycje dla za³¹czników
			oString += CString(lpMsg);
			oMapiMessages.SetMsgNoteText(oString);

			oMapiMessages.SetMsgSubject(lpSubject);
			for(long iter = 0; iter <= m_oRecipmentArray.GetUpperBound(); iter++)
			{
				oMapiMessages.SetRecipIndex(iter);
				oMapiMessages.SetRecipAddress(m_oRecipmentArray[iter].m_oAddressString);
				oMapiMessages.SetRecipType(1 /* to: */ );
				oMapiMessages.SetRecipDisplayName(m_oRecipmentArray[iter].m_oNameString);
				oMapiMessages.ResolveName();
			}
			for(long iter = 0; iter <= m_oAttachmentArray.GetUpperBound(); iter++)
			{
				oMapiMessages.SetAttachmentIndex(iter);
				oMapiMessages.SetAttachmentPosition(iter);
				oMapiMessages.SetAttachmentName(m_oAttachmentArray[iter].m_oNameString);
				oMapiMessages.SetAttachmentPathName(m_oAttachmentArray[iter].m_oLocalFileString);
				oMapiMessages.SetAttachmentType(0 /*mapData == file */);
			}
			//to_do: format
#ifdef _NAVODOTNET
			CSmartOleVariant oFalseSOV(COleVariant((long)false,VT_BOOL));
#else
			CSmartOleVariant oFalseSOV(false);
#endif
			oMapiMessages.Send(oFalseSOV.GetVariantRef());
		}
		m_oRecipmentArray.RemoveAll();
		m_oAttachmentArray.RemoveAll();
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CMailSession::ReadMsgAUTO(long nItem, BOOL bUnreadOnly, 
	VARIANT * pVarSenderAddress, 
	VARIANT * pVarSenderName, 
	VARIANT * pVarSubject, 
	VARIANT * pVarMsg, 
	VARIANT * pVarDate, 
	VARIANT * pVarAttachmentCount) 
{
	ALL_TRY
	{
		ASSERT(nItem > 0);
		TRACE1("ENTERING READ MSG %d\n",nItem);
		if(m_oMapiMessages.m_lpDispatch == NULL)
		{
			if(!m_oMapiMessages.CreateDispatch("MSMAPI.MAPIMessages"))
			{
				return FALSE;
			}
			m_bFetchValid = false;
			m_bLastUnread = false;
			m_oMapiMessages.SetSessionID(m_oMapiSession.GetSessionID());
			m_oMapiMessages.SetFetchSorted(TRUE);
		}
		if(!m_bFetchValid || (m_bLastUnread ^ bool(bUnreadOnly != FALSE)))
		{
			m_oMapiMessages.SetFetchUnreadOnly(bUnreadOnly);

			CAfxResourceHandleHolder oARHH(_h_NAVOINET_Instance);
			CString oMsgString;
			oMsgString.LoadString(IDS_FETCHING_INBOX);
			SCP<CPerformingDialogHolder> poPDHSP = NewSCP(new CPerformingDialogHolder(oMsgString));
			
			m_oMapiMessages.Fetch();
			m_bFetchValid = true;
			m_bLastUnread = bool(bUnreadOnly != FALSE);
		}
		long nMsgCount = m_oMapiMessages.GetMsgCount();
		if(nMsgCount <= 0 || nMsgCount <= nItem-1)
		{
			return FALSE;	//no more msg
		}
		m_oMapiMessages.SetMsgIndex(nMsgCount - nItem);
		*pVarSubject = CSmartOleVariant(m_oMapiMessages.GetMsgSubject()).Detach();
		*pVarMsg = CSmartOleVariant(m_oMapiMessages.GetMsgNoteText()).Detach();
		*pVarSenderAddress = CSmartOleVariant(m_oMapiMessages.GetMsgOrigAddress()).Detach();
		*pVarSenderName = CSmartOleVariant(m_oMapiMessages.GetMsgOrigDisplayName()).Detach();
		
		//YYYY/MM/DD HH:MM
		CSmartOleVariant oMsgDateReceivedSOV(m_oMapiMessages.GetMsgDateReceived());
		if(!oMsgDateReceivedSOV.SafeChangeType(VT_DATE))
		{
			oMsgDateReceivedSOV = GetNullDateSOV();
		}
		*pVarDate = oMsgDateReceivedSOV.Detach();
		long nAttachmentCount = m_oMapiMessages.GetAttachmentCount();
		*pVarAttachmentCount =  CSmartOleVariant(nAttachmentCount,VT_I4).Detach();
		//copy attachments
		m_oAttachmentArray.RemoveAll();
		for(long iter = 0; iter < nAttachmentCount; iter++)
		{
			m_oMapiMessages.SetAttachmentIndex(iter);
			AddAttachmentAUTO(m_oMapiMessages.GetAttachmentName(),
				CSmartOleVariant(m_oMapiMessages.GetAttachmentPathName()).GetVariantRef());
		}
		TRACE2("LEAVING READ MSG %d,att # %d\n",nItem,nAttachmentCount);
		return TRUE;	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CMailSession::GetAttachmentAUTO(long nItem, VARIANT FAR* pVarName, VARIANT FAR* pVarStream) 
{
	ALL_TRY
	{
		nItem--;
		if(nItem > m_oAttachmentArray.GetUpperBound())
		{
			return FALSE;
		}
		* pVarName = CSmartOleVariant(m_oAttachmentArray[nItem].m_oNameString).Detach();
		* pVarStream = CSmartOleVariant(m_oAttachmentArray[nItem].m_oLocalFileString).Detach();
		return TRUE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
