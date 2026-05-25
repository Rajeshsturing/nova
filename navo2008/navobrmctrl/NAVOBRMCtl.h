#if !defined(AFX_NAVOBRMCTL_H__F250AF1A_DCC6_44A1_9381_6F89C47C5F09__INCLUDED_)
#define AFX_NAVOBRMCTL_H__F250AF1A_DCC6_44A1_9381_6F89C47C5F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// NAVOBRMCtl.h : Declaration of the CNAVOBRMCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMCtrl : See NAVOBRMCtl.cpp for implementation.

class CNAVOBRMCtrl : public COleControl
{
	DECLARE_DYNCREATE(CNAVOBRMCtrl)

// Constructor
public:
	CNAVOBRMCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNAVOBRMCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CNAVOBRMCtrl();

	DECLARE_OLECREATE_EX(CNAVOBRMCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CNAVOBRMCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CNAVOBRMCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CNAVOBRMCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CNAVOBRMCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CNAVOBRMCtrl)
	BOOL m_bCompress;
	afx_msg void OnCompressChanged();
	long m_nSplitSize;
	afx_msg void OnSplitsizeChanged();
	afx_msg VARIANT GetDataStreamAUTO();
	afx_msg void SetDataStreamAUTO(const VARIANT FAR& newValue);
	afx_msg VARIANT GetInfoStreamAUTO();
	afx_msg void SetInfoStreamAUTO(const VARIANT FAR& newValue);
	afx_msg LPDISPATCH GetSinkAUTO();
	afx_msg void SetSinkAUTO(LPDISPATCH newValue);
	afx_msg BSTR GetDescriptionAUTO();
	afx_msg void SetDescriptionAUTO(LPCTSTR lpszNewValue);
	afx_msg long RestoreAUTO();
	afx_msg LPDISPATCH NewBRSetAUTO();
	afx_msg long BackupAUTO();
	afx_msg void AddBRSetAUTO(LPDISPATCH pBRSet);
	afx_msg long ReadHeaderAUTO();
	afx_msg BSTR GetProfileAUTO(LPCTSTR lpServerName, long nProfile);
	afx_msg void SetProfileAUTO(LPCTSTR lpServerName, long nProfile, LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	BEGIN_INTERFACE_PART(NotificationSink,INotificationSink)
		STDMETHOD(OnSharedVariableChange)(long,VARIANT)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnNotifyUser)(long,long,VARIANT *)
		{
			return E_NOTIMPL;
		}
		STDMETHOD(OnProgress)(long nInfoType,long lAdvance,long lTotal,LPSTR lpDescription);
	END_INTERFACE_PART(NotificationSink)
	DECLARE_INTERFACE_MAP()

	afx_msg void AboutBox();
	virtual BOOL IsInvokeAllowed(DISPID)
	{
		return TRUE;
	}

// Event maps
	//{{AFX_EVENT(CNAVOBRMCtrl)
	void FireProgress(long nInfoType, long nAdvance, long nTotal, LPCTSTR lpDescription, BOOL FAR* pCancel)
		{FireEvent(eventidProgress,EVENT_PARAM(VTS_I4  VTS_I4  VTS_I4  VTS_BSTR  VTS_PBOOL), nInfoType, nAdvance, nTotal, lpDescription, pCancel);}
	void FireAskForData(long nInfoType, LPCTSTR lpDescription, const VARIANT FAR& varQuestion, VARIANT FAR* pVarAnswer)
		{FireEvent(eventidAskForData,EVENT_PARAM(VTS_I4  VTS_BSTR  VTS_VARIANT  VTS_PVARIANT), nInfoType, lpDescription, &varQuestion, pVarAnswer);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	HRESULT Impl_AskForData(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer);

	enum {
	//{{AFX_DISP_ID(CNAVOBRMCtrl)
	dispidCompress = 1L,
	dispidDatastream = 3L,
	dispidInfostream = 4L,
	dispidSplitsize = 2L,
	dispidSink = 5L,
	dispidDescription = 6L,
	dispidRestore = 7L,
	dispidProfile = 12L,
	dispidNewbrset = 8L,
	dispidBackup = 9L,
	dispidAddbrset = 10L,
	dispidReadheader = 11L,
	eventidProgress = 1L,
	eventidAskForData = 2L,
	//}}AFX_DISP_ID
	};
private:
	CString			m_oDescriptionString;
	SCP<IBackupRestoreManager> m_poLocalBRMSP;
	CSmartOleVariant m_oDataStreamSOV;
	CSmartOleVariant m_oInfoStreamSOV;
	SCP<CScriptSupplyInfo>	m_poSSI_SinkSP;
	SCP<IDispatch>			m_poSupplyInfoDispatchSP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVOBRMCTL_H__F250AF1A_DCC6_44A1_9381_6F89C47C5F09__INCLUDED)
