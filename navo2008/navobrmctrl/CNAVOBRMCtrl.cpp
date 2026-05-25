// CNAVOBRMCtrl.cpp : Implementation of the CNAVOBRMCtrl ActiveX Control class.

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "navobrmctrl2008.h"
#include "CNAVOBRMCtrl.h"
#include "CNAVOBRMPpg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CNAVOBRMCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CNAVOBRMCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(CNAVOBRMCtrl, COleControl)
	INTERFACE_PART(CNAVOBRMCtrl, IID_INotificationSink, NotificationSink)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CNAVOBRMCtrl, NotificationSink)
// Dispatch map

BEGIN_DISPATCH_MAP(CNAVOBRMCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CNAVOBRMCtrl)
	DISP_PROPERTY_NOTIFY(CNAVOBRMCtrl, "compress", m_bCompress, OnCompressChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CNAVOBRMCtrl, "splitsize", m_nSplitSize, OnSplitsizeChanged, VT_I4)
	DISP_PROPERTY_EX(CNAVOBRMCtrl, "datastream", GetDataStreamAUTO, SetDataStreamAUTO, VT_VARIANT)
	DISP_PROPERTY_EX(CNAVOBRMCtrl, "infostream", GetInfoStreamAUTO, SetInfoStreamAUTO, VT_VARIANT)
	DISP_PROPERTY_EX(CNAVOBRMCtrl, "sink", GetSinkAUTO, SetSinkAUTO, VT_DISPATCH)
	DISP_PROPERTY_EX(CNAVOBRMCtrl, "description", GetDescriptionAUTO, SetDescriptionAUTO, VT_BSTR)
	DISP_FUNCTION(CNAVOBRMCtrl, "restore", RestoreAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CNAVOBRMCtrl, "newbrset", NewBRSetAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CNAVOBRMCtrl, "backup", BackupAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CNAVOBRMCtrl, "addbrset", AddBRSetAUTO, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION(CNAVOBRMCtrl, "readheader", ReadHeaderAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CNAVOBRMCtrl, "profile", GetProfileAUTO, SetProfileAUTO, VT_BSTR, VTS_BSTR VTS_I4)
	DISP_PROPERTY_EX_ID(CNAVOBRMCtrl, "rootdir", 32, GetRootDirAUTO, SetRootDirAUTO, VT_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CNAVOBRMCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CNAVOBRMCtrl, COleControl)
	//{{AFX_EVENT_MAP(CNAVOBRMCtrl)
	EVENT_CUSTOM("Progress", FireProgress, VTS_I4  VTS_I4  VTS_I4  VTS_BSTR  VTS_PBOOL)
	EVENT_CUSTOM("AskForData", FireAskForData, VTS_I4  VTS_BSTR  VTS_VARIANT  VTS_PVARIANT)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CNAVOBRMCtrl, 1)
	PROPPAGEID(CCNAVOBRMPropPage::guid)
END_PROPPAGEIDS(CNAVOBRMCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNAVOBRMCtrl, "NAVOBRMCTRL.NAVOBRMCtrl.1",
	0xb4222b0f, 0xed29, 0x4ecc, 0x9b, 0x57, 0x99, 0x5a, 0x5e, 0x22, 0x25, 0x40)



	// Type library ID and version

	IMPLEMENT_OLETYPELIB(CNAVOBRMCtrl, _tlid, _wVerMajor, _wVerMinor)



	// Interface IDs

	const IID IID_Dnavobrmctrl2008 = { 0x624555E0, 0x29AA, 0x4BDE, { 0xB0, 0xA3, 0x5E, 0x5F, 0x13, 0x90, 0xED, 0x28 } };
const IID IID_Dnavobrmctrl2008Events =
{ 0x69E3EFCF, 0xA739, 0x4879, { 0xA9, 0x99, 0xC, 0x70, 0xE5, 0x50, 0xE2, 0x3A } };


// Control type information

static const DWORD _dwnavobrmctrl2008OleMisc =
OLEMISC_INVISIBLEATRUNTIME |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CNAVOBRMCtrl, IDS_NAVOBRMCTRL2008, _dwnavobrmctrl2008OleMisc)



// CNAVOBRMCtrl::CNAVOBRMCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CNAVOBRMCtrl

BOOL CNAVOBRMCtrl::CNAVOBRMCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_NAVOBRMCTRL2008,
			IDB_NAVOBRMCTRL2008,
			afxRegApartmentThreading,
			_dwnavobrmctrl2008OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMCtrl::CNAVOBRMCtrl - Constructor

CNAVOBRMCtrl::CNAVOBRMCtrl() :
	m_bCompress(FALSE),
	m_nSplitSize(0)		//no splitting
{
	InitializeIIDs(&IID_Dnavobrmctrl2008, &IID_Dnavobrmctrl2008Events);
	m_poLocalBRMSP.CreateInstance(CLSID_NAVO2001BackupRestoreManager, CLSCTX_ALL);
}



/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMCtrl::~CNAVOBRMCtrl - Destructor

CNAVOBRMCtrl::~CNAVOBRMCtrl()
{
}

void CNAVOBRMCtrl::OnDraw(CDC*, const CRect&, const CRect&)
{
	//empty
}

void CNAVOBRMCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


// CNAVOBRMCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CNAVOBRMCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control can activate without creating a window.
	// TODO: when writing the control's message handlers, avoid using
	//		the m_hWnd member variable without first checking that its
	//		value is non-NULL.
	dwFlags |= windowlessActivate;
	return dwFlags;
}



// CNAVOBRMCtrl::OnResetState - Reset control to default state

void CNAVOBRMCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CNAVOBRMCtrl::AboutBox - Display an "About" box to the user

void CNAVOBRMCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_NAVOBRMCTRL2008);
	dlgAbout.DoModal();
}



// CNAVOBRMCtrl message handlers

/////////////////////////////////////////////////////////////////////////////
// CNAVOBRMCtrl message handlers


BSTR CNAVOBRMCtrl::GetProfileAUTO(LPCTSTR lpServerName, long nProfile)
{
	ALL_TRY
	{
		CString strResult;
		SCP<IBackupRestoreManager> poBRMSP;
		if (!*lpServerName)
		{
			poBRMSP = m_poLocalBRMSP;
		}
		else
		{
			CreateRemoteInstance(CLSID_NAVO2001BackupRestoreManager,lpServerName,
						&poBRMSP.GetIID(),poBRMSP);
		}
		if (poBRMSP.PointsObject())
		{
			VARIANT oVariant;
			if (poBRMSP->GetProp(nProfile,&oVariant) == S_OK)
			{
				strResult = CSmartOleVariant(oVariant).GetBStr();
			}
		}
		return strResult.AllocSysString();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNAVOBRMCtrl::SetProfileAUTO(LPCTSTR lpServerName, long nProfile, LPCTSTR lpszNewValue)
{
	ALL_TRY
	{
		SCP<IBackupRestoreManager> poBRMSP;
		if (!*lpServerName)
		{
			poBRMSP = m_poLocalBRMSP;
		}
		else
		{
			CreateRemoteInstance(CLSID_NAVO2001BackupRestoreManager,lpServerName,
						&poBRMSP.GetIID(),poBRMSP);
		}
		if (poBRMSP.PointsObject())
		{
			CSmartOleVariant oSOV(lpszNewValue);
			HRESULT hr = poBRMSP->SetProp(nProfile,oSOV.GetVariantRef());
			ASSERT(hr == S_OK);
		}
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CNAVOBRMCtrl::NewBRSetAUTO()
{
	ALL_TRY
	{
		LPDISPATCH lpDispatch = NULL;
		HRESULT hr = m_poLocalBRMSP->NewBrSet(&lpDispatch);
		if (hr == S_OK)
		{
			ASSERT(lpDispatch);
			return lpDispatch;
		}
		return NULL;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

class CNAVOBRMSupplyInfo : public CSupplyInfo__
{
public:
	CNAVOBRMSupplyInfo(CNAVOBRMCtrl * poNAVOBRMCtrl) :
		CSupplyInfo__(),
		m_poNAVOBRMCtrl(poNAVOBRMCtrl)
	{
	}
	virtual HRESULT Impl_AskForData(long nInfoType, LPCTSTR lpDescription, VARIANT varQuestion, VARIANT * pvarAnswer)
	{
		return m_poNAVOBRMCtrl->Impl_AskForData(nInfoType, lpDescription, varQuestion, pvarAnswer);
	}
private:
	CNAVOBRMCtrl * m_poNAVOBRMCtrl;
};

#pragma pack(push)
#pragma pack(1)
struct CNAVOBackupHeader
{
	CNAVOBackupHeader()
	{
		m_aMarker[0] = 'N';
		m_aMarker[1] = 'B';
		m_aMarker[2] = 'H';
		m_aMarker[3] = '2';
		m_nSplitSize = 0;	//no splitting
		m_cCompressed = '0';
		m_nDescriptionLength = 0;
		ASSERT(is_valid_marker());
	}
	bool is_valid_marker() const
	{
		return (m_aMarker[0] == 'N' &&
			m_aMarker[1] == 'B' &&
			m_aMarker[2] == 'H' &&
			m_aMarker[3] == '2');
	}

	char m_aMarker[4];
	long m_nSplitSize;
	long m_nDescriptionLength;
	char m_cCompressed;
};

#pragma pack(pop)

long CNAVOBRMCtrl::BackupAUTO()
{
	ALL_TRY
	{
		SCP<CFileRemover> poDestFileRemoverSP;
		SCP<CFileRemover> poInfoFileRemoverSP;

		SCP<IStream> poDestinationStreamSP =
			CreateFileStream_Write_On_SOV(m_oDataStreamSOV,poDestFileRemoverSP);
		SCP<IStream> poInfoDestinationStreamSP =
			CreateFileStream_Write_On_SOV(m_oInfoStreamSOV,poInfoFileRemoverSP);

		ASSERT(poDestinationStreamSP.PointsObject());
		ASSERT(poInfoDestinationStreamSP.PointsObject());

		SCP<IStream> poBackupDataStreamSP;
		SCP<IStream> poBackupInfoStreamSP;
		CNAVOBRMSupplyInfo oBRMSupplyInfo(this);
		HRESULT hr = m_poLocalBRMSP->GetBackupStream(&poBackupDataStreamSP.GetRawPointer(),
			&poBackupInfoStreamSP.GetRawPointer(),&m_xNotificationSink,oBRMSupplyInfo.GetISupplyInfo());

		if (hr == S_OK)
		{
			CNAVOBackupHeader oNBH;
			oNBH.m_cCompressed = m_bCompress ? '1' : '0';
			oNBH.m_nSplitSize = m_nSplitSize;
			oNBH.m_nDescriptionLength = m_oDescriptionString.GetLength();

			CStreamHolder oInfoSH(poBackupInfoStreamSP);
			oInfoSH.Write(&oNBH,sizeof(oNBH));
			oInfoSH.Write((void*)(LPCTSTR)m_oDescriptionString,m_oDescriptionString.GetLength());

			ULARGE_INTEGER ulInfinity;
			ulInfinity.QuadPart = MAXLONG;
			SCP<IStream> poInterMediateStreamSP = m_bCompress ? CompressStream(poBackupDataStreamSP) : poBackupDataStreamSP;
			hr = IStream_CopyTo(poInterMediateStreamSP,poDestinationStreamSP,ulInfinity);
			if (hr != S_OK)
			{
				if (hr != ERROR_CANCELLED)
				{
					CNavoException oNavoException;
					GetErrorInfoFromInterface(poInterMediateStreamSP,oNavoException);
					GetErrorInfoFromInterface(poDestinationStreamSP,oNavoException);
					ContinueThrowNavoException(oNavoException,ERCO_BRMANCTRL_COPYING_FAILED,IDPAGE_NOTAVAILABLE);
				}
			}

			//dopiero w tym momencie poBackupInfoStreamSP ma ustalon¹ d³ugoœæ
			ASSERT(m_nSplitSize == 0);	//for now no splitting

			if (hr == S_OK)
			{
				hr = IStream_CopyTo(poBackupInfoStreamSP,poInfoDestinationStreamSP,ulInfinity);
			}

			if (hr == S_OK)
			{
				poDestFileRemoverSP->DontRemove();
				poInfoFileRemoverSP->DontRemove();
			}
			ASSERT(hr == S_OK); //just for control
		}
		return hr;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNAVOBRMCtrl::RestoreAUTO()
{
	ALL_TRY
	{
		SCP<IStream> poSrcStreamSP = OpenFileStream_Read_On_SOV(m_oDataStreamSOV);
		SCP<IStream> poSrcInfoStreamSP = OpenFileStream_Read_On_SOV(m_oInfoStreamSOV);
		ASSERT(poSrcStreamSP.PointsObject());
		ASSERT(poSrcInfoStreamSP.PointsObject());
		CStreamHolder oInfoSH(poSrcInfoStreamSP);

		CNAVOBackupHeader oNBH;
		oInfoSH.Read(&oNBH,sizeof(oNBH));
		if (!oNBH.is_valid_marker())
		{
			return ERROR_BAD_FORMAT;
		}
		m_bCompress = (oNBH.m_cCompressed == '1');

		//read description
		if (oNBH.m_nDescriptionLength != 0)
		{
			LPSTR ptr = m_oDescriptionString.GetBuffer(oNBH.m_nDescriptionLength);
			oInfoSH.Read(ptr,oNBH.m_nDescriptionLength);
			m_oDescriptionString.ReleaseBuffer(oNBH.m_nDescriptionLength);
		}

		CNAVOBRMSupplyInfo oBRMSupplyInfo(this);
		HRESULT hr = m_poLocalBRMSP->SetRestoreStream(
			m_bCompress ? UncompressStream(poSrcStreamSP).Get() : poSrcStreamSP.Get(),
			poSrcInfoStreamSP.Get(),&m_xNotificationSink,oBRMSupplyInfo.GetISupplyInfo());
		if (hr != S_OK)
		{
			CNavoException oNavoException;
			GetErrorInfoFromInterface(m_poLocalBRMSP,oNavoException);
			BOOL bDummyCancel;
			FireProgress(231,0,0,oNavoException.BuildCompleteErrorString(),&bDummyCancel);
		}
		return hr;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CNAVOBRMCtrl::ReadHeaderAUTO()
{
	ALL_TRY
	{
		SCP<IStream> poSrcInfoStreamSP = OpenFileStream_Read_On_SOV(m_oInfoStreamSOV);
		ASSERT(poSrcInfoStreamSP.PointsObject());
		CStreamHolder oInfoSH(poSrcInfoStreamSP);

		CNAVOBackupHeader oNBH;
		oInfoSH.Read(&oNBH,sizeof(oNBH));
		if (!oNBH.is_valid_marker())
		{
			return ERROR_BAD_FORMAT;
		}
		m_bCompress = (oNBH.m_cCompressed == '1');

		//read description
		if (oNBH.m_nDescriptionLength != 0)
		{
			LPSTR ptr = m_oDescriptionString.GetBuffer(oNBH.m_nDescriptionLength);
			oInfoSH.Read(ptr,oNBH.m_nDescriptionLength);
			m_oDescriptionString.ReleaseBuffer(oNBH.m_nDescriptionLength);
		}
		return S_OK;
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CNAVOBRMCtrl::AddBRSetAUTO(LPDISPATCH pBRSetDispatch)
{
	ALL_TRY
	{
		HRESULT hr = m_poLocalBRMSP->AddBrSet(pBRSetDispatch);
		ASSERT(hr == S_OK);
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

HRESULT CNAVOBRMCtrl::Impl_AskForData(long nInfoType, LPCTSTR lpDescription, VARIANT varQuestion, VARIANT * pvarAnswer)
{
	if (ERCO_ASK_FOR_RELATIVE_PATH == nInfoType)
	{
		*pvarAnswer = CSmartOleVariant(m_oRootDirString).Detach();
		return S_OK;
	}

	if (m_poSSI_SinkSP.PointsObject())
	{
		return m_poSSI_SinkSP->Impl_AskForData(nInfoType, lpDescription, varQuestion, pvarAnswer);
	}
	else
	{
		FireAskForData(nInfoType, lpDescription, varQuestion, pvarAnswer);
	}
	return S_OK;
}

HRESULT CNAVOBRMCtrl::XNotificationSink::OnProgress(long nInfoType, long lAdvance, long lTotal, LPSTR lpDescription)
{
	METHOD_PROLOGUE(CNAVOBRMCtrl, NotificationSink)

		if (pThis->m_poSSI_SinkSP.PointsObject())
		{
			return pThis->m_poSSI_SinkSP->Impl_OnProgress(nInfoType, lAdvance, lTotal, lpDescription);
		}
		else
		{
			BOOL bCancel = FALSE;
			pThis->FireProgress(nInfoType, lAdvance, lTotal, lpDescription, &bCancel);
			return bCancel ? ERROR_CANCELLED : S_OK;
		}
}

void CNAVOBRMCtrl::OnCompressChanged()
{
	//empty
}

VARIANT CNAVOBRMCtrl::GetDataStreamAUTO()
{
	return m_oDataStreamSOV.GetVariantRef();
}

void CNAVOBRMCtrl::SetDataStreamAUTO(const VARIANT FAR& newValue)
{
	m_oDataStreamSOV = newValue;
}

VARIANT CNAVOBRMCtrl::GetInfoStreamAUTO()
{
	return m_oInfoStreamSOV.GetVariantRef();
}

void CNAVOBRMCtrl::SetInfoStreamAUTO(const VARIANT FAR& newValue)
{
	m_oInfoStreamSOV = newValue;
}

void CNAVOBRMCtrl::OnSplitsizeChanged()
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

LPDISPATCH CNAVOBRMCtrl::GetSinkAUTO()
{
	SCP<IDispatch> pIDispatchSP = m_poSupplyInfoDispatchSP;
	return pIDispatchSP.Detach();
}

void CNAVOBRMCtrl::SetSinkAUTO(LPDISPATCH pDispatch)
{
	ALL_TRY
	{
		m_poSupplyInfoDispatchSP = NewSCP(pDispatch,true);
		if (m_poSupplyInfoDispatchSP.PointsObject())
		{
			m_poSSI_SinkSP = NewSCP(new CScriptSupplyInfo(m_poSupplyInfoDispatchSP));
		}
		else
		{
			m_poSSI_SinkSP = 0;
		}

		SetModifiedFlag();
	}
		ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CNAVOBRMCtrl::GetDescriptionAUTO()
{
	return m_oDescriptionString.AllocSysString();
}

void CNAVOBRMCtrl::SetDescriptionAUTO(LPCTSTR lpszNewValue)
{
	m_oDescriptionString = lpszNewValue;
	SetModifiedFlag();
}

BSTR CNAVOBRMCtrl::GetRootDirAUTO()
{
	return m_oRootDirString.AllocSysString();
}

void CNAVOBRMCtrl::SetRootDirAUTO(LPCTSTR lpszNewValue)
{
	m_oRootDirString = lpszNewValue;
}

