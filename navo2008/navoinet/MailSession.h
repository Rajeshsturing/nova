/*
	NAVO Enterprise 2001
	mail support
*/

#if !defined(AFX_MAILSESSION_H__C65893A1_8DE0_450A_B700_5B8D448B5BF6__INCLUDED_)
#define AFX_MAILSESSION_H__C65893A1_8DE0_450A_B700_5B8D448B5BF6__INCLUDED_


/////////////////////////////////////////////////////////////////////////////
// CMailSession command target

class CMailSession : public CCmdTarget
{
	DECLARE_DYNCREATE(CMailSession)

	CMailSession();           // protected constructor used by dynamic creation
public:
	//{{AFX_VIRTUAL(CMailSession)
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL
protected:
	virtual ~CMailSession();
	//{{AFX_MSG(CMailSession)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMailSession)

	//{{AFX_DISPATCH(CMailSession)
	afx_msg BOOL ConnectAUTO(LPCTSTR lpUser, LPCTSTR lpPassword);
	afx_msg void AddAttachmentAUTO(LPCTSTR lpName, const VARIANT FAR& pStream);
	afx_msg void AddRecipmentAUTO(LPCTSTR lpAddress, LPCTSTR lpName);
	afx_msg BOOL SendAUTO(LPCTSTR lpSubject, LPCTSTR lpMsg, long nFormat);
	afx_msg BOOL DownLoadAUTO(LPCTSTR lpUser, LPCTSTR lpPassword);
	afx_msg BOOL ReadMsgAUTO(long nItem, BOOL bUnreadOnly, VARIANT * lpSenderAddress, VARIANT * lpSenderName, VARIANT * lpSubject, VARIANT * lpMsg, VARIANT * dtDate, VARIANT * pnAttachmentCount);
	afx_msg BOOL GetAttachmentAUTO(long nItem, VARIANT FAR* pVarName, VARIANT FAR* pVarStream);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	IMapiSession m_oMapiSession;
	IMapiMessages m_oMapiMessages;
	bool		  m_bFetchValid;
	bool		  m_bLastUnread;

	struct CAttachment
	{
		CAttachment()
		{
		}
		CAttachment(LPCTSTR lpName,LPCTSTR lpLocalFile,SCP<CFileRemover> & rpoFileRemoverSP) :
			m_oNameString(lpName),
			m_oLocalFileString(lpLocalFile),
			m_poFileRemoverSP(rpoFileRemoverSP)
		{
		}
		CAttachment(const CAttachment & roAttachment) :
			m_oNameString(roAttachment.m_oNameString),
			m_oLocalFileString(roAttachment.m_oLocalFileString),
			m_poFileRemoverSP(NewSCP(roAttachment.m_poFileRemoverSP.ConstCastObject(),true))
		{
		}
		CString m_oNameString;
		CString m_oLocalFileString;
		SCP<CFileRemover> m_poFileRemoverSP;
	};
	struct CRecipment
	{
		CRecipment(){}
		CRecipment(LPCTSTR lpAddress,LPCTSTR lpName):
			m_oAddressString(lpAddress),
			m_oNameString(lpName)
		{
		}
		
		CRecipment(const CRecipment & roRecipment) :
			m_oAddressString(roRecipment.m_oAddressString),
			m_oNameString(roRecipment.m_oNameString)
		{
		}
		CString m_oAddressString;
		CString m_oNameString;
	};

	CArray<CAttachment,CAttachment&> m_oAttachmentArray;
	CArray<CRecipment,CRecipment&> m_oRecipmentArray;
};


#endif // !defined(AFX_MAILSESSION_H__C65893A1_8DE0_450A_B700_5B8D448B5BF6__INCLUDED_)
