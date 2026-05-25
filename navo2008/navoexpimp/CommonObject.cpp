/*
	NAVO Enterprise 2001
	Common Export/Import base Object
*/

#include "stdafx.h"
#include "CommonObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CCommonObject,CCmdTargetInterface)
	//{{AFX_MSG_MAP(CCommonObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCommonObject,CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CCommonObject)
	DISP_PROPERTY_EX(CCommonObject, "typeid", GetTypeidAUTO, SetTypeidAUTO, VT_I4)
	DISP_PROPERTY_EX(CCommonObject, "idobj", GetIdobjAUTO, SetIdobjAUTO, VT_I4)
	DISP_PROPERTY_PARAM(CCommonObject, "field", GetFieldAUTO, SetFieldAUTO, VT_VARIANT, VTS_BSTR)
	DISP_FUNCTION(CCommonObject, "isfield", IsFieldAUTO, VT_BOOL, VTS_BSTR)
	DISP_DEFVALUE(CCommonObject, "field")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CCommonObject,CCmdTargetInterface)
END_INTERFACE_MAP()


bool CCommonObject::IsField(LPCTSTR lpFieldName)
{
	CString oString(lpFieldName);
	oString.MakeLower();
	CSmartOleVariant oSOV;
	if(m_oFieldMap.Lookup(oString,oSOV))
	{
		return true;
	}
	return false;
}

void CCommonObject::SetField(LPCTSTR lpFieldName,const CSmartOleVariant & roSOV)
{
	CString oString(lpFieldName);
	oString.MakeLower();
	m_oFieldMap[ oString ] = roSOV;
}

void CCommonObject::GetField(LPCTSTR lpFieldName,CSmartOleVariant & roSOV)
{
	CString oString(lpFieldName);
	oString.MakeLower();
	if(!m_oFieldMap.Lookup(oString,roSOV))
	{
		ThrowNavoException3(ERCO_EXPIMP_FIELD_NOT_EXISTS,IDPAGE_NOTAVAILABLE,
			m_nTypeId,m_nIdObj,oString);
	}
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

VARIANT CCommonObject::GetFieldAUTO(LPCTSTR lpName) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV;
		GetField(lpName,oSOV);
		return oSOV.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CCommonObject::SetFieldAUTO(LPCTSTR lpName, const VARIANT FAR& newValue) 
{
	ALL_TRY
	{
		CSmartOleVariant oSOV(newValue);
		if(oSOV.Type() == VT_EMPTY)
		{
			ThrowNavoException3(ERCO_EXPIMP_FIELD_BAD_VALUE,IDPAGE_NOTAVAILABLE,
				m_nTypeId,m_nIdObj,lpName);
		}
		SetField(lpName,oSOV);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BOOL CCommonObject::IsFieldAUTO(LPCTSTR lpName)
{
	ALL_TRY
	{
		return (IsField(lpName) != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CCommonObject::GetTypeidAUTO() 
{
	return m_nTypeId;
}

void CCommonObject::SetTypeidAUTO(long) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"typeid","export/import");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CCommonObject::GetIdobjAUTO() 
{
	return m_nIdObj;
}

void CCommonObject::SetIdobjAUTO(long) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"idobj","export/import");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CCommonObject::Write(ExportImportFormat eif,SCP<IStream> & rpoOutputStreamSP)
{
	if(eif == eif_xml)
	{
		CStreamHolder oSH(rpoOutputStreamSP);
		oSH.WriteString("\t\t<neio>\r\n");
		CString oString;
		oString.Format("\t\t\t<typeid>%d</typeid>\r\n\t\t\t<idobj>%d</idobj>\r\n",m_nTypeId,m_nIdObj);
		oSH.WriteString(oString);
		POSITION pos = m_oFieldMap.GetStartPosition();
		while(pos)
		{
			CString oFieldNameString;
			CSmartOleVariant oSOV;
			m_oFieldMap.GetNextAssoc(pos, oFieldNameString, oSOV);
			long nFieldType = long(oSOV.Type());
			switch(nFieldType)
			{
			case VT_BSTR:
			{
				CString oValueString = Variant2String(oSOV);
				if(oValueString.IsEmpty())
				{
					oString.Format("\t\t\t<f%s vt='%d' />\r\n",oFieldNameString,VT_BSTR);
				}
				else
				{
					oString.Format("\t\t\t<f%s vt='%d'><![CDATA[%s]]></f%s>\r\n",oFieldNameString,VT_BSTR,Variant2String(oSOV),oFieldNameString);
				}
				oSH.WriteString(oString);
			}
			break;
			case VT_CY:
			case VT_I4:
			case VT_DATE:
			{
				CString oValueString = Variant2String(oSOV);
				if(oValueString == "0")
				{
					oString.Format("\t\t\t<f%s vt='%d' />\r\n",oFieldNameString,nFieldType);
				}
				else
				{
					oString.Format("\t\t\t<f%s vt='%d'>%s</f%s>\r\n",oFieldNameString,nFieldType,Variant2String(oSOV),oFieldNameString);
				}
				oSH.WriteString(oString);
			}
			break;
			case VT_DISPATCH:	//musi supportowaæ IStream
			{
				SCP<IStream> poIStreamSP;
				poIStreamSP.QueryInterface(oSOV.GetDispatch());
				oString.Format("\t\t\t<f%s vt='%d'><![CDATA[",oFieldNameString,VT_STREAM);
				oSH.WriteString(oString);
				CStreamHolder(poIStreamSP).SeekToBegin();
				
				ULARGE_INTEGER ulInfinity;
				ulInfinity.QuadPart = MAXLONG;
				HRESULT hr = IStream_CopyTo(Base64EncodeStream(CompressStream(poIStreamSP)),oSH.GetStream(),ulInfinity);
				ASSERT(hr == S_OK);	//to_do: error handling

				oString.Format("]]></f%s>\r\n",oFieldNameString);
				oSH.WriteString(oString);
			}
			break;
			default:
				ASSERT(false);
			}
		}
		oSH.WriteString("\t\t</neio>\r\n");
	}
	else
	{
		ASSERT(false);	//to_do
	}
}
