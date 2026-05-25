/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CBRManager - backup/restore manager
*/

#if !defined(AFX_BRMANAGER_H__BEF5F192_7500_4714_8756_32BED5B3AA48__INCLUDED_)
#define AFX_BRMANAGER_H__BEF5F192_7500_4714_8756_32BED5B3AA48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BRManager.h : header file
//

/*
	struktura pliku backupu
	naglowek
	{
		dlugosc opisu providera
		opis providera
		{
			dlugosc nazwy
			nazwa
		
			dlugosc opisu
			opis
		
			dlugosc strumienia
			dane strumienia
		}
		end marker
	}
*/

const long BRF_MARKER = 0x31303032;

struct CBRFileHeader
{
	CBRFileHeader() :
		m_marker(BRF_MARKER),
		m_nProvidersCount(0)
	{
	}
	long m_marker;
	long m_nProvidersCount;
};
/////////////////////////////////////////////////////////////////////////////
// CBRManager command target
//---------------------------------------------------
// 
// holder zapewniaj¹cy zamkniêcie transakcji Begin / End
// 
//---------------------------------------------------
class CBackupRestoreInitHolder : public CInterface__
{
public:
	CBackupRestoreInitHolder(SCP<IBackupRestore> & roBRSP,
		SCP<INotificationSink> & rpoNotificationSinkSP,
		SCP<ISupplyInfo> & rpoSupplyInfoSP,bool bBackup,LPCTSTR lpDescription) :
	  m_poBRSP(roBRSP),
		  m_hBeginResult(S_OK)
	  {
		  ASSERT(m_poBRSP.PointsObject());
		  m_hBeginResult = m_poBRSP->Begin(rpoNotificationSinkSP,bBackup,(LPTSTR)lpDescription,rpoSupplyInfoSP);
	  }
	~CBackupRestoreInitHolder()
	{
		if(m_poBRSP.PointsObject())
		{
			VERIFY(m_poBRSP->End() == S_OK);
		}
	}
	HRESULT GetResult() const
	{
		return m_hBeginResult;
	}
	SCP<IBackupRestore> & GetPtr()
	{
		return m_poBRSP;
	}
private:
	HRESULT m_hBeginResult;
	SCP<IBackupRestore> m_poBRSP;
};

const long BRMAN_NOT_INITED = -2;
const long BRMAN_FINISHED	= 99999;

class CBRManager : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CBRManager)

	CBRManager();           // protected constructor used by dynamic creation

public:
	//{{AFX_VIRTUAL(CBRManager)
	//}}AFX_VIRTUAL
	virtual ~CBRManager();

	//{{AFX_MSG(CBRManager)
	//}}AFX_MSG

	BEGIN_INTERFACE_PART(BackupRestore,IBackupRestore)
		STDMETHOD(Begin)(IUnknown * pONSinkUnknown,BYTE bBackup,LPSTR pParameters,ISupplyInfo * pSupplyInfo);
		STDMETHOD(End)();
		STDMETHOD(GetBackupStream)(LPSTR * ppStreamName,
			LPSTR * ppStreamInfo,IStream ** ppDataStream);
		STDMETHOD(SetRestoreStream)(LPSTR  ppStreamName,
			LPSTR  ppStreamInfo,IStream * ppDataStream,__int64 i64Length);
		STDMETHOD(GetStat)(long * pTotalCount,long * pTotalSize);
	END_INTERFACE_PART(BackupRestore)
	BEGIN_INTERFACE_PART(BackupRestoreManager,IBackupRestoreManager)
		STDMETHOD(GetBackupStream)(IStream ** ppDataStream,IStream ** ppInfoStream,
			IUnknown * pONSinkUnknown,IUnknown * pISupplyInfo);
		STDMETHOD(SetRestoreStream)(IStream * pDataStream,IStream * pInfoStream,
			IUnknown * pONSinkUnknown,IUnknown * pISupplyInfo);
		STDMETHOD(NewBrSet)(IDispatch ** ppDispatch);
		STDMETHOD(AddBrSet)(IDispatch * pDispatch);
		STDMETHOD(RemoveAllBrSets)();
		STDMETHOD(_GetNewEnum)(IUnknown ** ppUnknown);
		STDMETHOD(SetProp)(long nProp,VARIANT vValue);
		STDMETHOD(GetProp)(long nProp,VARIANT * pvValue);
	END_INTERFACE_PART(BackupRestoreManager)
	BEGIN_INTERFACE_PART(Stream, IStream)
		STDMETHOD(Read)(void *pData, unsigned long lLength, unsigned long *plBytesRead);
		STDMETHOD(Seek)(LARGE_INTEGER liOffset, unsigned long lOrigin,
			ULARGE_INTEGER * pliNewPointer);
		STDMETHOD(Write)(const void *pData, unsigned long lLength, unsigned long *plBytesWritten);
		STDMETHOD(SetSize)(ULARGE_INTEGER ulSize);
		STDMETHOD(CopyTo)(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten);
		STDMETHOD(Commit)(unsigned long);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(Stat)(STATSTG * pStatStg, unsigned long lFlags);
		STDMETHOD(Clone)(IStream ** ppIStream);
	END_INTERFACE_PART(Stream)

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBRManager)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBRManager)
	afx_msg LPDISPATCH NewBRSetAUTO();
	afx_msg void AddBRSetAUTO(LPDISPATCH);
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	//}}AFX_DISPATCH
	DECLARE_INTERFACE_MAP()
private:
	void _SetProperty(long nProp,const CSmartOleVariant & roSOV);
	void _GetProperty(long nProp,CSmartOleVariant & roSOV);

	HRESULT _PrepareBackup();
	HRESULT _ReadBackup(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT _DoRestore(SCP<IStream> & rpoIStreamSP,SCP<IStream> & rpoInfoStreamSP);

	HRESULT NotifyOnProgress(long nInfoType,long nAdv,long nTotal,LPCTSTR lpMsg)
	{
		return StdNotifyOnProgress(m_poNotificationSinkSP,nInfoType,nAdv,nTotal,lpMsg);
	}
	void ReadDescription(LPCSTR lpDescription);

	CEnumerableArray< SCP<CBRSet>, SCP<CBRSet> & > m_oBRSetArray;
	SCP<INotificationSink>	m_poNotificationSinkSP;
	SCP<ISupplyInfo>		m_poSupplyInfoSP;
	SCP<CStdNotifyOnProgressHolder> m_poStdNotifyOnProgressHolderSP;

	CArray < SCP<CBackupRestoreInitHolder>, SCP<CBackupRestoreInitHolder> & > m_oProvidersArray;
	CBRFileHeader m_oHeader;
	struct CReadingState
	{
		CReadingState()
		{
			Reset();
		}
	
		void Reset()
		{
			m_nCurrentProvider = BRMAN_NOT_INITED;
			m_poCurrentStreamSP = 0;
			m_poInfoStreamSP = 0;
			m_oCurrentStreamNameString = "";
			m_oCurrentStreamInfoString = "";
			m_nCurrentStreamSize = 0;
		}

		long			m_nCurrentProvider;
		SCP<IStream>	m_poCurrentStreamSP;
		SCP<IStream>	m_poInfoStreamSP;
		CString			m_oCurrentStreamNameString;
		CString			m_oCurrentStreamInfoString;
		__int64			m_nCurrentStreamSize;
	};	

	CReadingState m_oReadingState;

	//backup / restore interface state
	enum BackupRestoreState
	{
		brs_none,
		brs_datastream,
		brs_infostream,
		brs_end
	};
	BackupRestoreState	m_eBackupRestoreState;
	SCP<IStream>		m_poBackupRestoreInfoStreamSP;
	SCP<IUnknown>		m_poBackupRestoreONSinkUnknownSP;
	SCP<ISupplyInfo>	m_poBackupRestoreSupplyInfoSP;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRMANAGER_H__BEF5F192_7500_4714_8756_32BED5B3AA48__INCLUDED_)
