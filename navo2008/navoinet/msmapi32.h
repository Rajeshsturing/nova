// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IMapiSession wrapper class

class IMapiSession : public COleDispatchDriver
{
public:
	IMapiSession() {}		// Calls COleDispatchDriver default constructor
	IMapiSession(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMapiSession(const IMapiSession& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetDownLoadMail();
	void SetDownLoadMail(BOOL bNewValue);
	BOOL GetLogonUI();
	void SetLogonUI(BOOL bNewValue);
	BOOL GetNewSession();
	void SetNewSession(BOOL bNewValue);
	short GetAction();
	void SetAction(short nNewValue);
	long GetSessionID();
	void SetSessionID(long nNewValue);
	CString GetPassword();
	void SetPassword(LPCTSTR lpszNewValue);
	CString GetUserName_();
	void SetUserName(LPCTSTR lpszNewValue);
	void SignOn();
	void SignOff();
};
/////////////////////////////////////////////////////////////////////////////
// MAPISessionEvents wrapper class

class MAPISessionEvents : public COleDispatchDriver
{
public:
	MAPISessionEvents() {}		// Calls COleDispatchDriver default constructor
	MAPISessionEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MAPISessionEvents(const MAPISessionEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// IMapiMessages wrapper class

class IMapiMessages : public COleDispatchDriver
{
public:
	IMapiMessages() {}		// Calls COleDispatchDriver default constructor
	IMapiMessages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMapiMessages(const IMapiMessages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetAddressCaption();
	void SetAddressCaption(LPCTSTR lpszNewValue);
	short GetAddressEditFieldCount();
	void SetAddressEditFieldCount(short nNewValue);
	CString GetAddressLabel();
	void SetAddressLabel(LPCTSTR lpszNewValue);
	BOOL GetAddressModifiable();
	void SetAddressModifiable(BOOL bNewValue);
	BOOL GetAddressResolveUI();
	void SetAddressResolveUI(BOOL bNewValue);
	long GetAttachmentCount();
	void SetAttachmentCount(long nNewValue);
	long GetAttachmentIndex();
	void SetAttachmentIndex(long nNewValue);
	CString GetAttachmentName();
	void SetAttachmentName(LPCTSTR lpszNewValue);
	CString GetAttachmentPathName();
	void SetAttachmentPathName(LPCTSTR lpszNewValue);
	long GetAttachmentPosition();
	void SetAttachmentPosition(long nNewValue);
	short GetAttachmentType();
	void SetAttachmentType(short nNewValue);
	CString GetFetchMsgType();
	void SetFetchMsgType(LPCTSTR lpszNewValue);
	BOOL GetFetchSorted();
	void SetFetchSorted(BOOL bNewValue);
	BOOL GetFetchUnreadOnly();
	void SetFetchUnreadOnly(BOOL bNewValue);
	CString GetMsgConversationID();
	void SetMsgConversationID(LPCTSTR lpszNewValue);
	long GetMsgCount();
	void SetMsgCount(long nNewValue);
	CString GetMsgDateReceived();
	void SetMsgDateReceived(LPCTSTR lpszNewValue);
	CString GetMsgID();
	void SetMsgID(LPCTSTR lpszNewValue);
	long GetMsgIndex();
	void SetMsgIndex(long nNewValue);
	CString GetMsgNoteText();
	void SetMsgNoteText(LPCTSTR lpszNewValue);
	CString GetMsgOrigAddress();
	void SetMsgOrigAddress(LPCTSTR lpszNewValue);
	CString GetMsgOrigDisplayName();
	void SetMsgOrigDisplayName(LPCTSTR lpszNewValue);
	BOOL GetMsgRead();
	void SetMsgRead(BOOL bNewValue);
	BOOL GetMsgReceiptRequested();
	void SetMsgReceiptRequested(BOOL bNewValue);
	BOOL GetMsgSent();
	void SetMsgSent(BOOL bNewValue);
	CString GetRecipAddress();
	void SetRecipAddress(LPCTSTR lpszNewValue);
	long GetRecipCount();
	void SetRecipCount(long nNewValue);
	CString GetRecipDisplayName();
	void SetRecipDisplayName(LPCTSTR lpszNewValue);
	long GetRecipIndex();
	void SetRecipIndex(long nNewValue);
	short GetRecipType();
	void SetRecipType(short nNewValue);
	long GetSessionID();
	void SetSessionID(long nNewValue);
	CString GetMsgSubject();
	void SetMsgSubject(LPCTSTR lpszNewValue);
	CString GetMsgType();
	void SetMsgType(LPCTSTR lpszNewValue);
	short GetAction();
	void SetAction(short nNewValue);
	void Compose();
	void Copy();
	void Delete(const VARIANT& vObj);
	void Fetch();
	void Forward();
	void Reply();
	void ReplyAll();
	void ResolveName();
	void Save();
	void Show(const VARIANT& vDetails);
	void Send(const VARIANT& vDialog);
};
/////////////////////////////////////////////////////////////////////////////
// MAPIMessagesEvents wrapper class

class MAPIMessagesEvents : public COleDispatchDriver
{
public:
	MAPIMessagesEvents() {}		// Calls COleDispatchDriver default constructor
	MAPIMessagesEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MAPIMessagesEvents(const MAPIMessagesEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
