/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	class:
	CHyperLinkInfo
	
	  "kolekcja property"
*/

#include "StdAfx.h"
#include "..\include\h1000.h"
#include "..\include\navoarchive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHyperLinkInfo::CHyperLinkInfo()
{
	EnableAutomation();
}

CHyperLinkInfo::CHyperLinkInfo(const CHyperLinkInfo & roHLI)
{
	EnableAutomation();
	operator = (roHLI);
};


SCP<CHyperLinkInfo> CHyperLinkInfo::FromIDispatch(LPDISPATCH lpDispatch)
{
	if(lpDispatch == NULL)	//VB nothing
	{
		return SCP<CHyperLinkInfo>();
	}
	else
	{
		CCmdTarget * poCmdTargetHLI = CCmdTarget::FromIDispatch(lpDispatch);
		ASSERT(poCmdTargetHLI);
		CHyperLinkInfo * poHLI = dynamic_cast<CHyperLinkInfo *>(poCmdTargetHLI);
		ASSERT(poHLI);
		return NewSCP(poHLI,true);
	}
}

SCP<CPropertyProvider__> CPropertyProvider__::FromIDispatch(LPDISPATCH lpDispatch)
{
	if(lpDispatch == NULL)	//VB nothing
	{
		return SCP<CPropertyProvider__>();
	}
	else
	{
		CCmdTarget * poCmdTargetHLI = CCmdTarget::FromIDispatch(lpDispatch);
		ASSERT(poCmdTargetHLI);
		CPropertyProvider__ * poHLI = dynamic_cast<CPropertyProvider__ *>(poCmdTargetHLI);
		ASSERT(poHLI);
		return NewSCP(poHLI,true);
	}
}


//{{AFX_MSG_MAP(CHyperLinkInfo)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CHyperLinkInfo, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CHyperLinkInfo)
	DISP_FUNCTION(CHyperLinkInfo, "exists", ExistsAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CHyperLinkInfo, "getstring", GetAsStringAUTO, VT_BSTR, VTS_NONE)
	DISP_PROPERTY_PARAM(CHyperLinkInfo, "prop", GetPropAUTO, SetPropAUTO, VT_VARIANT, VTS_I4)
	DISP_DEFVALUE(CHyperLinkInfo, "prop")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_DYNCREATE(CHyperLinkInfo,CCmdTarget);


VARIANT CHyperLinkInfo::GetPropAUTO(long Name) 
{
	ALL_TRY
	{
		CSmartOleVariant oVariant;
		if (!SafeGetProp(Name, oVariant))
		{
			ThrowNavoException1(ERCO_HYPERLINK_GETVAR_NOTEXISTS,IDPAGE_NOTAVAILABLE, Name);
		};
		return oVariant.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CHyperLinkInfo::SetPropAUTO(long Name, const VARIANT FAR & newValue) 
{
	ALL_TRY
	{
		SetProp(Name, CSmartOleVariant(newValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CHyperLinkInfo::ExistsAUTO(long Nr) 
{
	ALL_TRY
	{
		return (PropertyExists(Nr) == true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

CString CHyperLinkInfo::WriteToString(bool bSafeForMarshallingOnly) const
{

	CString oString;
	bool bWasVariable = false;
	POSITION pos = m_props.m_map.GetStartPosition();
	while (pos)
	{
		long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
		CVariable roVariable;
		m_props.m_map.GetNextAssoc(pos, lName,roVariable);
#else
		const CVariable & roVariable = m_props.m_map.GetNextAssoc(pos, lName);
#endif
		CSmartOleVariant oVariant = roVariable.GetVal();
		VARTYPE vt = oVariant.Type();
		char cType;
		switch(vt)
		{
		case VT_BSTR:
			cType = 's';
			break;
		case VT_I2:
		case VT_I4:
			oVariant.ChangeType(VT_BSTR);
			cType = 'n';
			break;
		case VT_DATE:
			oVariant.ChangeType(VT_BSTR);
			cType = 'd';
			break;
		case VT_CY:
			oVariant.ChangeType(VT_BSTR);
			cType = 'c';
			break;
		default:
			{
				CString oTmpStr;
				oTmpStr.Format(_T("v%d(type=%d)"), roVariable.GetName(), vt);
				if(bWasVariable)
				{
					oString += ' ';
				}
				
				bWasVariable = true;

				if(bSafeForMarshallingOnly)
				{
#ifdef _DEVELOPER_EDITION_
					CString oMsgString("unsafe variable=" + oTmpStr);
					ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE,oMsgString);
#else
					//ignore !
#endif
				}
				else
				{
					oString += oTmpStr;
				}

			}
			continue;
		};
		CString oTmpStr;
		CString strVariant(oVariant.GetVariantRef());
		oTmpStr.Format(_T("v%c%d=\"%s\""), cType, roVariable.GetName(), strVariant);
		if (bWasVariable)
		{
			oString += ' ';
		};
		oString += oTmpStr;
		bWasVariable = true;
	}
	return oString;
};


CString CHyperLinkInfo::WriteToXMLString() const
{
	CString oString = "<hyperlink>\n";
	POSITION pos = m_props.m_map.GetStartPosition();
	while (pos)
	{
		long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
		CVariable roVariable;
		m_props.m_map.GetNextAssoc(pos, lName, roVariable);
#else
		const CVariable & roVariable = m_props.m_map.GetNextAssoc(pos, lName);
#endif
		CSmartOleVariant oVariant = roVariable.GetVal();
		VARTYPE vt = oVariant.Type();
		char cType;
		switch(vt)
		{
		case VT_BSTR:
			cType = 's';
			break;
		case VT_I4:
			oVariant.ChangeType(VT_BSTR);
			cType = 'n';
			break;
		case VT_DATE:
			oVariant.ChangeType(VT_BSTR);
			cType = 'd';
			break;
		case VT_CY:
			oVariant.ChangeType(VT_BSTR);
			cType = 'c';
			break;
		default:
			{
				CString oTmpStr;
				oTmpStr.Format(_T("<v%d>(object)</v%d>\n"), roVariable.GetName(), roVariable.GetName());
				oString += oTmpStr;
			}
			continue;
		};
		CString oTmpStr;
		oTmpStr.Format(_T("<v%c%d>%S</v%c%d>\n"),cType,roVariable.GetName(),oVariant.GetBStr(),cType,roVariable.GetName());
		oString += oTmpStr;
	}
	return oString + _T("</hyperlink>\n");
}

void CHyperLinkInfo::_store(CNAVOArchiveWriter & roWriter)
{
	roWriter << long(m_props.m_map.GetCount());
	POSITION pos = m_props.m_map.GetStartPosition();
	while (pos)
	{
		long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
		CVariable roVariable;
		m_props.m_map.GetNextAssoc(pos, lName,roVariable);
#else
		const CVariable & roVariable = m_props.m_map.GetNextAssoc(pos, lName);
#endif
		CSmartOleVariant oVariant = roVariable.GetVal();
		VARTYPE vt = oVariant.Type();

		roWriter << lName << long(vt);
		switch(vt)
		{
		case VT_BSTR:
			roWriter << CString(oVariant.GetBStr());
			break;
		case VT_I4:
			roWriter << oVariant.GetLong();
			break;
		case VT_DATE:
			roWriter << oVariant.GetDate();
			break;
		case VT_CY:
			roWriter << oVariant.GetCurrency();
			break;
		default:
			{
				ASSERT(false);
			}
			continue;
		};
	}
}

void CHyperLinkInfo::_load(CNAVOArchiveReader & roReader)
{
	long nCount;
	roReader >> nCount;
	while(nCount--)
	{
		long lName;
		roReader >> lName;
		long nType;
		roReader >> nType;
		VARTYPE vt = (VARTYPE) nType;
		CSmartOleVariant oVariantSOV;
		switch(vt)
		{
		case VT_BSTR:
		{
			CString oString;
			roReader >> oString;
			oVariantSOV = oString;
		}
		break;
		case VT_I4:
		{
			long nLong;
			roReader >> nLong;
			oVariantSOV = nLong;
		}
		break;
		case VT_DATE:
		{
			DATE dtDate;
			roReader >> dtDate;
			oVariantSOV = dtDate;
		}
		break;
		case VT_CY:
		{
			CY cy;
			roReader >> cy;
			oVariantSOV = cy;
		}
		break;
		default:
			{
				ASSERT(false);
			}
		}
		SetProp(lName,oVariantSOV);
	}
}

SCP<CHyperLinkInfo> ReadHLIFromString(const CString & roString,SCP<CHyperLinkInfo> poHLISP)
{
	SCP<CHyperLinkInfo> oHyperLinkInfoSP;
	if(poHLISP.PointsObject())
	{
		oHyperLinkInfoSP = poHLISP;
	}
	else
	{
		oHyperLinkInfoSP = NewSCP(new CHyperLinkInfo);
	}
	CString oNameString;
	CString oValueString;
	CTagSplitter oTagSplitter(roString);

	while (oTagSplitter.NextItem(oNameString, oValueString))
	{
		long lPropertyNumber;
		VARTYPE nVarType;
		const TCHAR * pcStart, * pcEnd;
		if (ParsePropertyName(oNameString, lPropertyNumber, nVarType, pcStart, pcEnd))
		{
			if (oHyperLinkInfoSP->PropertyExists(lPropertyNumber))
			{
				ThrowNavoException(ERCO_READHLI_PROP_ALREADY_DEFINED, IDPAGE_NOTAVAILABLE);
			};
			CSmartOleVariant oVariant(oValueString);
			ALL_TRY
			{
				oVariant.ChangeType(nVarType);
			}
			ALL_CATCH(CNavoException & roException)
			{
				ContinueThrowNavoException2(roException, ERCO_READHLI_PROP_VAL_DOESNT_AGREE_WITH_TYPE, IDPAGE_NOTAVAILABLE, oValueString,oNameString);
			};
			oHyperLinkInfoSP->SetProp(lPropertyNumber, oVariant);
		}
		else
		{
#ifdef _DEBUG
			{
				CString oInfoString;
				oInfoString.Format(_T("ReadHLIFromString ma problem z %s w %s"),roString,oNameString);
				AfxMessageBox(oInfoString);
			}
#endif
			ThrowNavoException1(ERCO_READHLI_VARIABLE_EXPECTED, IDPAGE_NOTAVAILABLE, oNameString);
		};
	};
	return oHyperLinkInfoSP;
};


#ifndef UNLEN
#define UNLEN       256                 // Maximum user name length
#endif

SCP<CHyperLinkInfo> GetSystemEnvironmentHLI()
{

	SCP<CHyperLinkInfo> poInitialEnvironmentHLISP = NewSCP(new CHyperLinkInfo);
	
	{
		TCHAR cComputerName[ MAX_COMPUTERNAME_LENGTH + 1 ];
		DWORD nComputerNameLen = sizeof( cComputerName );
		VERIFY(::GetComputerName(cComputerName, &nComputerNameLen ));
		poInitialEnvironmentHLISP->SetStrProp(GVAR_MACHINE,cComputerName);
	}
	poInitialEnvironmentHLISP->SetStrProp(GVAR_NAVO2001VERSION,GetNAVO2001EngineVersion());
	{
		TCHAR cComputerUserName[ UNLEN + 1 ];
		DWORD nComputerUserNameLen = sizeof( cComputerUserName );
		VERIFY( ::GetUserName( cComputerUserName,&nComputerUserNameLen) );
		poInitialEnvironmentHLISP->SetStrProp(GVAR_OSUSERNAME,cComputerUserName );
	}
	return poInitialEnvironmentHLISP;
}

CString ReplaceFormalParam(LPCTSTR lpInput,CHyperLinkInfo * poHLI)
{
	CArray<TCHAR,TCHAR&> oOutputBufferArray;
	oOutputBufferArray.SetSize(1024);
	CArrayWriter<TCHAR> oOutputWriter(oOutputBufferArray);
	while(*lpInput)
	{
		if(*lpInput == 'v' || *lpInput == 'V')
		{
			long lPropertyNumber;
			VARTYPE nVarType;
			const TCHAR * pcStart, * pcEnd;
			if(ParsePropertyName(lpInput, lPropertyNumber, nVarType, pcStart, pcEnd))
			{
				CSmartOleVariant oSOV = poHLI->GetProp(lPropertyNumber);
				CString oString = oSOV.ChangeType(VT_BSTR).GetBStr();
				oOutputWriter.Write(oString,oString.GetLength());
				lpInput = pcEnd;
				continue;
			}
		}
		oOutputWriter << *lpInput++;
	}
	return CString(oOutputBufferArray.GetData(),oOutputWriter.CharactersWritten());
}


BSTR CHyperLinkInfo::GetAsStringAUTO() 
{
	ALL_TRY
	{
		return WriteToString().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
