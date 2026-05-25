/*
	NAVO Enterprise 2001
	ImportPackage
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"
#include "CommonObject.h"
#include "ImportObject.h"
#include "ImportMessage.h"
#include "ImportPackage.h"
#include "ImportParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportPackage

IMPLEMENT_DYNCREATE(CImportPackage, CCmdTarget)

CImportPackage::CImportPackage()
{
	EnableAutomation();
	AfxOleLockApp();
}

CImportPackage::~CImportPackage()
{
	AfxOleUnlockApp();
}

BEGIN_MESSAGE_MAP(CImportPackage, CCmdTarget)
	//{{AFX_MSG_MAP(CImportPackage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImportPackage, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CImportPackage)
	DISP_PROPERTY_EX(CImportPackage, "sink", GetSinkAUTO, SetSinkAUTO, VT_DISPATCH)
	DISP_FUNCTION(CImportPackage, "istream", SetInputStreamAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CImportPackage, "go", GoAUTO, VT_I4, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IImportPackage to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {5227E73E-485B-4E5D-B328-0009BED9AB9C}
static const IID IID_IImportPackage =
{ 0x5227e73e, 0x485b, 0x4e5d, { 0xb3, 0x28, 0x0, 0x9, 0xbe, 0xd9, 0xab, 0x9c } };

BEGIN_INTERFACE_MAP(CImportPackage, CCmdTarget)
	INTERFACE_PART(CImportPackage, IID_IImportPackage, Dispatch)
END_INTERFACE_MAP()

// {188cb172-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CImportPackage, "navoexpimp.ImportPackage", 0x188cb172,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

const OLECHAR * lpctMsgBegin = L"OnMessageBegin";
const OLECHAR * lpctMsgEnd	 = L"OnMessageEnd";
const OLECHAR * lpctObject	 = L"OnObject";

void CImportSinkInfo::Init(SCP<IDispatch> & rpoEventSinkDispatchSP)
{
	ASSERT(rpoEventSinkDispatchSP.PointsObject());
	m_poEventSinkDispatchSP = rpoEventSinkDispatchSP;
	
	m_dispidMsgBegin = DispatchGetIdOfName(m_poEventSinkDispatchSP.Get(),lpctMsgBegin);
	m_dispidMsgEnd	 = DispatchGetIdOfName(m_poEventSinkDispatchSP.Get(),lpctMsgEnd);
	m_dispidObject	 = DispatchGetIdOfName(m_poEventSinkDispatchSP.Get(),lpctObject);

	if(m_dispidMsgBegin == 0 || m_dispidMsgEnd == 0 || m_dispidObject == 0)
	{
		ThrowNavoException(ERCO_EXPIMP_SINK_NO_METHODS,IDPAGE_NOTAVAILABLE);
	}
}

void CImportSinkInfo::OnMessageBegin(SCP<CImportMessage> & rpoImportMessageSP,bool & rbBreak)
{
	_Invoke(m_dispidMsgBegin,CSmartOleVariant(rpoImportMessageSP->GetIDispatch(TRUE),false),rbBreak);
}

void CImportSinkInfo::OnMessageEnd(SCP<CImportMessage> & rpoImportMessageSP,bool & rbBreak)
{
	_Invoke(m_dispidMsgEnd,CSmartOleVariant(rpoImportMessageSP->GetIDispatch(TRUE),false),rbBreak);
}

void CImportSinkInfo::OnObject(SCP<CImportObject> & rpoImportObjectSP,bool & rbBreak)
{
	_Invoke(m_dispidObject,CSmartOleVariant(rpoImportObjectSP->GetIDispatch(TRUE),false),rbBreak);
}

void CImportSinkInfo::_Invoke(DISPID dispid,const CSmartOleVariant & roSOV,bool & rbBreak)
{
	//function ala(byref obiekt,byref bBreak)
	CSmartOleVariant oArgumentSOVArray[2];
	oArgumentSOVArray[1] = roSOV;
#ifdef _NAVODOTNET
	oArgumentSOVArray[0] = CSmartOleVariant(COleVariant ((long)(bool) false, VT_BOOL));
#else
	oArgumentSOVArray[0] = CSmartOleVariant(false);
#endif
	
	oArgumentSOVArray[0].SetNavoRef();		//wo³amy przez byref

	ASSERT(m_poEventSinkDispatchSP);
	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poEventSinkDispatchSP, dispid,(CSmartOleVariant*)&oArgumentSOVArray,2,NULL,&ei);
	if (hResult != S_OK)
	{
		ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED,IDPAGE_NOTAVAILABLE,(LPCTSTR)
			(CString(ei.bstrSource) + " " + CString(ei.bstrDescription)),
			SCODE_To_String(hResult));
	};
	rbBreak = oArgumentSOVArray[0].GetBool();
}

LPDISPATCH CImportPackage::GetSinkAUTO() 
{
	ALL_TRY
	{
		return m_oImportSinkInfo.GetEventSinkDispatch().Get();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CImportPackage::SetSinkAUTO(LPDISPATCH pEventSinkDispatch) 
{
	ALL_TRY
	{
		m_oImportSinkInfo.Init(NewSCP(pEventSinkDispatch,true));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CImportPackage::SetInputStreamAUTO(const VARIANT FAR& varIStream) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(varIStream);
		
		m_poInputStreamSP = OpenFileStream_Read_On_SOV(oSOV);
		ASSERT(m_poInputStreamSP.PointsObject());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CImportPackage::GoAUTO() 
{
	ALL_TRY
	{
		//musi byæ podany stream
		if(m_poInputStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_MUST_SET_STREAM_FIRST,IDPAGE_NOTAVAILABLE);
		}
		SCP<INavoErrorInfo> poNavoErrorInfoSP;
		CStreamHolder(m_poInputStreamSP).SeekToBegin();
		if(!ParseXML(NewSCP<CSAXHandler__>(new CImportSAXHandler(m_oImportSinkInfo)),m_poInputStreamSP,poNavoErrorInfoSP))
		{
			//to_do:
			return -1;
		}
		return 0;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//-----------------------------------------------------------------------------------
