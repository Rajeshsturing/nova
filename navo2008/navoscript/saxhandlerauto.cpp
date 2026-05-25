/*
	NAVO Enterprise 2008

	SAXHandlerAUTO

	gateway SAXHandler to VBS based SAX interpreters
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\saxhandler.h"	//generic error storage
#include "saxhandlerauto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const OLECHAR * lpctStart	= L"OnElementStart";
const OLECHAR * lpctData	= L"OnData";
const OLECHAR * lpctEnd		= L"OnElementEnd";

CSAXHandlerAUTO::CSAXHandlerAUTO(SCP<IDispatch> poSinkObjectDispatchSP) :
	CSAXHandler__(NULL),
	m_poSinkObjectDispatchSP(poSinkObjectDispatchSP),
	m_dispid_start(DISPID(0)),
	m_dispid_data(DISPID(0)),
	m_dispid_end(DISPID(0))
{
	ASSERT(m_poSinkObjectDispatchSP.PointsObject());

	m_dispid_start = DispatchGetIdOfName(m_poSinkObjectDispatchSP.Get(),lpctStart);
	m_dispid_data	 = DispatchGetIdOfName(m_poSinkObjectDispatchSP.Get(),lpctData);
	m_dispid_end	 = DispatchGetIdOfName(m_poSinkObjectDispatchSP.Get(),lpctEnd);

	if(m_dispid_start == 0 || m_dispid_data == 0 || m_dispid_end == 0)
	{
		ThrowNavoException(ERCO_TODO,IDPAGE_NOTAVAILABLE);
	}
}

CSAXHandlerAUTO::~CSAXHandlerAUTO()
{
}

void CSAXHandlerAUTO::OnDataValue(LPCTSTR,long)
{
	ASSERT(false);
}

class CMapStringToStringAUTO : public CCmdTargetInterface
{
public:
	CMapStringToStringAUTO(const CMapStringToString & roAttributes) :
		m_pAttributes(&roAttributes),
		m_pOwnedAttributesCopy(NULL)
	{
		EnableAutomation();
	}
	CMapStringToStringAUTO(const CMapStringToStringAUTO & roMSTMA) :
		m_pOwnedAttributesCopy(new CMapStringToString())
	{
		EnableAutomation();

		m_pAttributes = m_pOwnedAttributesCopy;
		POSITION pos = roMSTMA.m_pAttributes->GetStartPosition();
		while(pos)
		{
			CString oKeyString;
			CString oValueString;
			roMSTMA.m_pAttributes->GetNextAssoc(pos,oKeyString,oValueString);
			m_pOwnedAttributesCopy->SetAt(oKeyString,oValueString);
		}
	}
	~CMapStringToStringAUTO()
	{
		delete m_pOwnedAttributesCopy;
	}

	//{{AFX_MSG(CMapStringToStringAUTO)
	//}}AFX_MSG
	DECLARE_DISPATCH_MAP()
	//{{AFX_DISPATCH(CMapStringToStringAUTO)
	afx_msg BOOL ExistsAUTO(LPCTSTR lpKeyName);
	afx_msg BSTR GetAUTO(LPCTSTR lpKeyName);
	afx_msg BSTR GetAsStringAUTO();
	afx_msg LPDISPATCH GetCloneAUTO();
	//}}AFX_DISPATCH
private:
	CMapStringToString * m_pOwnedAttributesCopy;
	const CMapStringToString * m_pAttributes;
};

//{{AFX_MSG_MAP(CMapStringToStringAUTO)
//}}AFX_MSG_MAP
BEGIN_DISPATCH_MAP(CMapStringToStringAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CMapStringToStringAUTO)
	DISP_FUNCTION(CMapStringToStringAUTO, "exists", ExistsAUTO, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CMapStringToStringAUTO, "get", GetAUTO, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CMapStringToStringAUTO, "getstring", GetAsStringAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CMapStringToStringAUTO, "clone", GetCloneAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL CMapStringToStringAUTO::ExistsAUTO(LPCTSTR lpKeyName)
{
	ALL_TRY
	{
		CString oDummyString;
		return m_pAttributes->Lookup(lpKeyName,oDummyString);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CMapStringToStringAUTO::GetAUTO(LPCTSTR lpKeyName)
{
	ALL_TRY
	{
		CString oString;
		m_pAttributes->Lookup(lpKeyName,oString);
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CMapStringToStringAUTO::GetCloneAUTO()
{
	ALL_TRY
	{
		CMapStringToStringAUTO * poMSTMA = new CMapStringToStringAUTO(*this);
		return poMSTMA->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR CMapStringToStringAUTO::GetAsStringAUTO()
{
	ALL_TRY
	{
		CString oString;
		POSITION pos = m_pAttributes->GetStartPosition();
		while(pos)
		{
			CString oKeyString;
			CString oValueString;
			m_pAttributes->GetNextAssoc(pos,oKeyString,oValueString);

			TCHAR cQuoteChar = (oValueString.Find('\'') != -1) ? '\"' : '\'';
			CString oAttribString;
			oAttribString.Format("%s=%c%s%c ",oKeyString,cQuoteChar,oValueString,cQuoteChar);
			oString += oAttribString;
		}
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CSAXHandlerAUTO::OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes)
{
	//function OnElementStart(byval strTag,byref pAttributes)
	CSmartOleVariant oArgumentSOVArray[2];
	oArgumentSOVArray[1] = CSmartOleVariant(lpElement);
	SCP<CMapStringToStringAUTO> poAttribAutoSP = NewSCP(new CMapStringToStringAUTO(roAttributes));
	oArgumentSOVArray[0] = CSmartOleVariant(poAttribAutoSP->GetDispatch(true),false);

	_invoke(m_dispid_start,oArgumentSOVArray,2);
}

void CSAXHandlerAUTO::OnEndElement(LPCTSTR lpElement)
{
	//[bool] function OnElementEnd(byval strTag)

	CSmartOleVariant oTagSOV(lpElement);
	_invoke(m_dispid_end,&oTagSOV,1);
}

void CSAXHandlerAUTO::OnDataValue(LPCTSTR lpValue)
{
	//[bool] function OnData(byval strValue)

	CSmartOleVariant oDataSOV(lpValue);
	_invoke(m_dispid_data,&oDataSOV,1);
}

void CSAXHandlerAUTO::_invoke(DISPID dispid,CSmartOleVariant * pArguments,long nArgCount)
{
#ifdef _NAVODOTNET
	CSmartOleVariant oResultSOV(COleVariant ((long)true, VT_BOOL));
#else
	CSmartOleVariant oResultSOV(true);
#endif

	EXCEPINFO ei;
	HRESULT hResult = DispatchInvoke(m_poSinkObjectDispatchSP, dispid,pArguments,nArgCount,&oResultSOV,&ei);
	if (hResult != S_OK)
	{
		ThrowNavoException2(ERCO_SCRIPT_INVOKE_FAILED,IDPAGE_NOTAVAILABLE,(LPCTSTR)
			(CString(ei.bstrSource) + " " + CString(ei.bstrDescription)),
			SCODE_To_String(hResult));
	};
	if(oResultSOV.Type() == VT_BOOL)
	{
		if(!oResultSOV.GetBool())
		{
			SetAbort();
		}
	}
}

void ParseXMLAUTO(SCP<IDispatch> poSinkObjectDispatchSP,SCP<IStream> poInputStreamSP)
{

	SCP<INavoErrorInfo> poNavoErrorInfoSP;
	if(!ParseXML(NewSCP<CSAXHandler__>(new CSAXHandlerAUTO(poSinkObjectDispatchSP)),
		poInputStreamSP,poNavoErrorInfoSP))
	{
		ThrowFromInterface(poNavoErrorInfoSP);
	}
}