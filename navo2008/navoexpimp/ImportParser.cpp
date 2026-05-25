/*
	NAVO Enterprise 2001
	Import SAX Parser
*/

#include "stdafx.h"
#include "..\include\h1000.h"
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

static const TCHAR * pcTokenPackage	= _T("neipckg");
static const TCHAR * pcTokenMessage	= _T("neimsg");
static const TCHAR * pcTokenObject	= _T("neio");
static const TCHAR * pcTokenTypeId	= _T("typeid");
static const TCHAR * pcTokenIdObj	= _T("idobj");
static const TCHAR * pcAttribVT		= _T("vt");

void CImportSAXHandler::OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes)
{
	CString oElementString(lpElement);
	oElementString.MakeLower();

	switch(m_eState)
	{
	case is_none:
		if(oElementString == pcTokenPackage)
		{
			m_eState = is_msg;
			return;
		}
	break;
	case is_msg:
		if(oElementString == pcTokenMessage)
		{
			ASSERT(m_poCurrentMsgSP.PointsNull());
			m_poCurrentMsgSP = NewSCP(new CImportMessage());
			m_eState = is_obj;
			return;
		}
	break;
	case is_obj:
		if(oElementString == pcTokenObject)
		{
			ASSERT(m_poCurrentMsgSP.PointsObject());
			ASSERT(m_poCurrentObjectSP.PointsNull());
			m_poCurrentObjectSP = NewSCP(new CImportObject(m_poCurrentMsgSP.Get()));
			m_eState = is_field;
			return;
		}
	break;
	case is_field:
	{
		m_oFieldValueString.Empty();
		m_poBigFieldStreamSP = 0;
		m_bFieldConsumed = false;
		ASSERT(oElementString.GetLength() > 0);
		switch(oElementString[0])
		{
		case 't':		//typeid
			m_eFieldVariant = fv_typeid;
		break;
		case 'i':		//idobj
			m_eFieldVariant = fv_idobj;
		break;
		case 'f':		//f.....
		{
			m_eFieldVariant = fv_regular;
			m_oFieldNameString = ((LPCTSTR)oElementString)+1;
			
			CString oVTString;
			if(roAttributes.Lookup(pcAttribVT,oVTString))
			{
				m_vtFieldType = VARTYPE(_ttol(oVTString));
			}
			else
			{
				m_vtFieldType = VT_BSTR;
			}
			if(m_vtFieldType == VT_STREAM)
			{
				m_poBigFieldStreamSP = CreateTempFileStream();
			}
			ASSERT(m_vtFieldType != VT_EMPTY);
		}
		break;
		default:
			ASSERT(false);
		}
		return;
	}
	break;
	default: 
		ASSERT(false);
	}
	ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE,IDPAGE_NOTAVAILABLE,oElementString);
}

void CImportSAXHandler::OnEndElement(LPCTSTR lpElement)
{
	CString oElementString(lpElement);
	oElementString.MakeLower();
	
	switch(m_eState)
	{
	case is_none:
	return;
	case is_msg:
	{
		if(oElementString == pcTokenPackage)
		{
			m_eState = is_none;
			//invoke on msg end
			bool bBreak = false;
			m_roImportSinkInfo.OnMessageEnd(m_poCurrentMsgSP,bBreak);
			if(bBreak)
			{
				SetAbort();
			}
			m_poCurrentMsgSP = 0;
			return;
		}
	}
	break;
	case is_obj:
	{
		if(oElementString == pcTokenMessage)
		{
			m_eState = is_msg;
			return;
		}
		if(oElementString == pcTokenObject)
		{
			return;
		}
	}
	break;
	case is_field:
	{
		if(oElementString == pcTokenObject)
		{
			m_eState = is_obj;
			m_eFieldVariant = fv_none;

			//jeœli w³aœnie skoñczyliœmy wczytywaæ header rozpocznij msg
			if(m_poCurrentObjectSP->GetTypeidAUTO() == TYPEID_EXPIMPMSGHEADER)
			{
				ASSERT(m_poCurrentObjectSP->GetIdobjAUTO() == 1);
				m_poCurrentMsgSP->SetHeader(m_poCurrentObjectSP);
				//invoke on msg begin
				bool bBreak = false;
				m_roImportSinkInfo.OnMessageBegin(m_poCurrentMsgSP,bBreak);
				if(bBreak)
				{
					SetAbort();
				}
			}
			else	//normalny obiekt
			{
				//invoke onobject
				bool bBreak = false;
				
				m_roImportSinkInfo.OnObject(m_poCurrentObjectSP,bBreak);
				if(bBreak)
				{
					SetAbort();
				}
			}
			m_poCurrentObjectSP = 0;
		}
		else
		{
			ASSERT(m_poCurrentObjectSP.PointsObject());
			m_bFieldConsumed = true;
			switch(m_eFieldVariant)
			{
			case fv_typeid:
				m_poCurrentObjectSP->SetTypeId(_ttol(m_oFieldValueString));
			return;
			case fv_idobj:
				m_poCurrentObjectSP->SetIdObj(_ttol(m_oFieldValueString));
			return;
			case fv_regular:
			{
				ASSERT(m_vtFieldType != VT_EMPTY);
				if(m_vtFieldType == VT_BSTR)
				{
					ASSERT(m_poBigFieldStreamSP.PointsNull());
					//white space preserved !
					m_poCurrentObjectSP->SetField(m_oFieldNameString,CSmartOleVariant(m_oFieldValueString));
				}
				else if(m_vtFieldType == VT_STREAM)	//musi supportowaæ IStream
				{
					ASSERT(m_poBigFieldStreamSP.PointsObject());
					ASSERT(m_oFieldValueString.IsEmpty());
					SCP<IStream> poDecodedStreamAUTOSP = CreateTempFileStream();
					{
						CStreamHolder(m_poBigFieldStreamSP).SeekToBegin();
					}

					//odkoduj strumieñ
					ULARGE_INTEGER ulInfinity;
					ulInfinity.QuadPart = MAXLONG;
					HRESULT hr = IStream_CopyTo(UncompressStream(Base64DecodeStream(m_poBigFieldStreamSP)),poDecodedStreamAUTOSP,ulInfinity);
					ASSERT(hr == S_OK);	//to_do: error handling
					m_poBigFieldStreamSP = 0;
					CStreamHolder(poDecodedStreamAUTOSP).SeekToBegin();
					m_poCurrentObjectSP->SetField(m_oFieldNameString,CSmartOleVariant(poDecodedStreamAUTOSP));
				}
				else
				{
					//dla tych typów nie exportujemy wartoœci 0
					//wiêc musimy j¹ tu odtworzyæ
					switch(m_vtFieldType)
					{
					case VT_CY:
					case VT_I4:
					case VT_DATE:
						if(m_oFieldValueString.IsEmpty())
						{
							m_oFieldValueString = "0";
						}
					}
					ASSERT(m_poBigFieldStreamSP.PointsNull());
					CSmartOleVariant oSOV(m_oFieldValueString);
					oSOV.ChangeType(m_vtFieldType);
					m_poCurrentObjectSP->SetField(m_oFieldNameString,oSOV);
				}
			}
			return;
			}
		}
		return;
	}
	break;
	default:
		ASSERT(false);
	}
	ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE,IDPAGE_NOTAVAILABLE,oElementString);
}

bool CImportSAXHandler::IsDataDirect() const
{
	return true;
}

void CImportSAXHandler::OnDataValue(LPCTSTR lpwcData,long nLength)
{
	CString oString(lpwcData,nLength);
	if(m_eState == is_field)
	{
		if(!m_bFieldConsumed)		//ignoruj spacje pomiêdzy polami tj. </fpole1> spacje <fpole2 vt....
		{
			if(m_vtFieldType != VT_STREAM)
			{
				m_oFieldValueString += oString;	//zapamiêtaj na przysz³oœæ
			}
			else
			{
				ASSERT(m_poBigFieldStreamSP.PointsObject());
				CStreamHolder(m_poBigFieldStreamSP).WriteString(oString);
			}
		}
		return;
	}
	else
	{
		oString.TrimLeft();
		oString.TrimRight();
		if(oString.IsEmpty())
		{
			return;
		}
	}
	ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE,IDPAGE_NOTAVAILABLE,oString);
}

void CImportSAXHandler::OnDataValue(LPCTSTR /*lpValue*/)
{
	ASSERT(false); //shouldn't be called
}

