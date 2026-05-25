// saxparser_.cpp : implementation file
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\saxhandler.h"	//generic error storage


#include "saxparser_.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CXMLParserImpl::CXMLParserImpl(CXMLParser & roParser,CStreamBuffer & roTokenizer,SCP<CSAXHandler__> poOutputSP) :
	m_roStreamBuffer(roTokenizer),
	m_poOutputSP(poOutputSP),
	m_roParser(roParser),
	m_ePhase(xp_bef_op)
{
	ASSERT(m_poOutputSP.PointsObject());
	m_roParser._push(this);
}

CXMLParserImpl::~CXMLParserImpl()
{
	m_roParser._pop();
}
	
eXMLError CXMLParserImpl::_parse()
{
	while(_skip_comment() || _skip_white())
	{
		;
	}
	TCHAR cChar = m_roStreamBuffer._get_char();
	if(cChar == '\0')
	{
		return xe_ok;
	}

	if(cChar != '<')
	{
		m_roParser._make_error_snapshot(xe_expected_less,m_roStreamBuffer);
		return xe_expected_less;
	}
	m_ePhase = xp_in_op;
	//parse tag identifier
	eXMLError eXE = _get_ident(m_oElementNameArray);
	if(eXE != xe_ok)
	{
		m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
		return eXE;
	}
	//get attributes
	bool bEndOfTag = false;
	while(!bEndOfTag)
	{
		_skip_white();
		TCHAR cChar = m_roStreamBuffer._get_char();
		switch(cChar)
		{
		case '/':		//end of tag
		{
			if(m_roStreamBuffer._get_char() != '>')
			{
				m_roParser._make_error_snapshot(xe_expected_greater,m_roStreamBuffer);
				return xe_expected_greater;
			}
			//notify bot
			m_poOutputSP->OnStartElement(m_oElementNameArray.GetData(),m_oAttributesMap);
			//notify eot
			m_poOutputSP->OnEndElement(m_oElementNameArray.GetData());
			if(m_poOutputSP->GetContinuationState() == SAXHC_Abort)
			{
				return xe_aborted;
			}
			return xe_ok;
		}
		case '>':
		{
			//notify bot
			m_poOutputSP->OnStartElement(m_oElementNameArray.GetData(),m_oAttributesMap);
			bEndOfTag = true;
			break;
		}
		default:
			m_roStreamBuffer._unget_char();
		}
		if(!bEndOfTag)
		{
			CArray<TCHAR,TCHAR&> oAttrNameArray;
			eXMLError eXE = _get_ident(oAttrNameArray);
			if(eXE != xe_ok)
			{
				m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
				return eXE;
			}
			_skip_white();
			if(m_roStreamBuffer._get_char() != '=')
			{
				m_roParser._make_error_snapshot(xe_expected_equal,m_roStreamBuffer);
				return xe_expected_equal;
			}
			_skip_white();
			CArray<TCHAR,TCHAR&> oValueArray;
			eXE = _get_value_in_quotes(oValueArray);
			if(eXE != xe_ok)
			{
				m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
				return eXE;
			}
			_tcslwr(oAttrNameArray.GetData());
			m_oAttributesMap[ oAttrNameArray.GetData() ] = oValueArray.GetData();
		}
	}
	
	m_ePhase = xp_in_cont;
	
	bool bWasDataOrCDATA = false;

	while(true)
	{
		while(_skip_comment() || _skip_white())
		{
			;
		}
		if(m_roStreamBuffer._get_char() != '<')	//value
		{
			if(bWasDataOrCDATA)
			{
				m_roParser._make_error_snapshot(xe_data_multipletimes,m_roStreamBuffer);
				return xe_data_multipletimes;
			}

			m_roStreamBuffer._unget_char();
			//get value
			CArray<TCHAR,TCHAR&> oValueArray;
			eXMLError eXE = _get_value_until_tag(oValueArray); 
			while(eXE == xe_value_more_data)
			{
				//notify
				ASSERT(m_poOutputSP->IsDataDirect());
				m_poOutputSP->OnDataValue(oValueArray.GetData(),oValueArray.GetSize());
				eXE = _get_value_until_tag(oValueArray); 
			}
			if(eXE != xe_ok)
			{
				m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
				return eXE;
			}
			//notify last time
			if(oValueArray.GetSize())
			{
				if(m_poOutputSP->IsDataDirect())
				{
					m_poOutputSP->OnDataValue(oValueArray.GetData(),oValueArray.GetSize());
				}
				else
				{
					m_poOutputSP->OnDataValue(oValueArray.GetData());
				}
			}
			bWasDataOrCDATA = true;
		}
		else
		{
			switch(m_roStreamBuffer._get_char())
			{
			case '!':		//must be cdata
				{
					if(bWasDataOrCDATA)
					{
						m_roParser._make_error_snapshot(xe_data_multipletimes,m_roStreamBuffer);
						return xe_data_multipletimes;
					}

					CArray<TCHAR,TCHAR&> oValueArray;
					eXMLError eXE = _get_cdata(true,oValueArray); 
					while(eXE == xe_cdata_more_data)
					{
						//notify
						ASSERT(m_poOutputSP->IsDataDirect());
						m_poOutputSP->OnDataValue(oValueArray.GetData(),oValueArray.GetSize());
						eXE = _get_cdata(false,oValueArray);
					}
					if(eXE != xe_ok)
					{
						m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
						return eXE;
					}
					//notify last time
					if(oValueArray.GetSize())
					{
						if(m_poOutputSP->IsDataDirect())
						{
							m_poOutputSP->OnDataValue(oValueArray.GetData(),oValueArray.GetSize());
						}
						else
						{
							m_poOutputSP->OnDataValue(oValueArray.GetData());
						}
					}
					bWasDataOrCDATA = true;
				}
				break;
			case '/':		//end tag
				{
					m_ePhase = xp_in_cl;
					CString oTestElementString;
					CArray<TCHAR,TCHAR&> oTestElementNameArray;
					eXE = _get_ident(oTestElementNameArray);
					if(eXE != xe_ok)
					{
						m_roParser._make_error_snapshot(eXE,m_roStreamBuffer);
						return eXE;
					}

					if(_tcscmp(oTestElementNameArray.GetData(),m_oElementNameArray.GetData()))
					{
						m_roParser._make_error_snapshot(xe_mismatched_tags,m_roStreamBuffer);
						return xe_mismatched_tags;
					}
					m_poOutputSP->OnEndElement(m_oElementNameArray.GetData());
					if(m_poOutputSP->GetContinuationState() == SAXHC_Abort)
					{
						return xe_aborted;
					}
					if(m_roStreamBuffer._get_char() != '>')
					{
						m_roParser._make_error_snapshot(xe_expected_greater,m_roStreamBuffer);
						return xe_expected_greater;
					}
					return xe_ok;
				}
				break;
			default:	//subtag
				{
					m_roStreamBuffer._unget_char();
					m_roStreamBuffer._unget_char();
					CXMLParserImpl oParser(m_roParser,m_roStreamBuffer,m_poOutputSP);
					eXMLError eXE = oParser._parse();
					if(eXE != xe_ok)
					{
						return eXE;
					}
				}
			}
		}
	}
}


eXMLError CXMLParserImpl::_skip_directives()
{
	TCHAR cChar = m_roStreamBuffer._get_char();
	while(true)
	{
		if(cChar == '\0')
		{
			return xe_ok;
		}
		else
		{
			if(cChar == '<')
			{
				if(m_roStreamBuffer._get_char() != '?')		//for <?xml
				{
					m_roStreamBuffer._unget_char();
					m_roStreamBuffer._unget_char();
					return xe_ok;
				}
			}
			else
			{
				if(cChar == '?')
				{
					if(m_roStreamBuffer._get_char() == '>')
					{
						return xe_ok;
					}
				}
			}
		}
		cChar = m_roStreamBuffer._get_char();
	}
}

//true - comment skipped
//false - not a comment
bool CXMLParserImpl::_skip_comment()
{
	if(m_roStreamBuffer._get_char() == '<')
	{
		if(m_roStreamBuffer._get_char() == '!')
		{
			if(m_roStreamBuffer._get_char() == '-')
			{
				if(m_roStreamBuffer._get_char() == '-')
				{
					//it was comment begin - now skip contents
					TCHAR cChar = m_roStreamBuffer._get_char();
					while(cChar != '\0')
					{
						if(cChar == '-')
						{
							if(m_roStreamBuffer._get_char() == '-')
							{
								if(m_roStreamBuffer._get_char() == '>')
								{
									break;
								}
							}
						}
						if(cChar == '\n')
						{
							m_roParser._inc_line_nr();
						}
						cChar = m_roStreamBuffer._get_char();
					}
					return true;
				}
				m_roStreamBuffer._unget_char();
			}
			m_roStreamBuffer._unget_char();
		}
		m_roStreamBuffer._unget_char();
	}
	m_roStreamBuffer._unget_char();
	return false;
}

bool CXMLParserImpl::_skip_white()
{
	TCHAR cChar = m_roStreamBuffer._get_char();
	if(!IsSpace(cChar))
	{
		m_roStreamBuffer._unget_char();
		return false;
	}
	//at least one space
	cChar = m_roStreamBuffer._get_char();
	while(IsSpace(cChar))
	{
		if(cChar == '\n')
		{
			m_roParser._inc_line_nr();
		}
		cChar = m_roStreamBuffer._get_char();
	}
	m_roStreamBuffer._unget_char();
	return true;
}

eXMLError CXMLParserImpl::_get_ident(CArray<TCHAR,TCHAR&> & roIdentArray)
{
	CArrayWriter<TCHAR>  oArrayWriter(roIdentArray);
	while(true)
	{
		TCHAR cChar = m_roStreamBuffer._get_char();
		if(!IsAlphaNum(cChar))
		{
			m_roStreamBuffer._unget_char();
			break;
		}
		oArrayWriter << cChar;
	}
	roIdentArray.SetSize( oArrayWriter.CharactersWritten() + 1 );
	roIdentArray[ oArrayWriter.CharactersWritten() ] = '\0';
	if(oArrayWriter.CharactersWritten() == 0)
	{
		return xe_expected_ident;
	}
	return xe_ok;
}

eXMLError CXMLParserImpl::_get_value_in_quotes(CArray<TCHAR,TCHAR&> & roValueArray)
{
	CArrayWriter<TCHAR>  oArrayWriter(roValueArray);
	TCHAR cQuoteChar = m_roStreamBuffer._get_char();
	if(cQuoteChar != '\'' && cQuoteChar != '\"')
	{
		return xe_expected_quote;
	}
	while(true)
	{
		TCHAR cChar = m_roStreamBuffer._get_char();
		if(cChar == cQuoteChar || cChar == '\0')
		{
			m_roStreamBuffer._unget_char();
			break;
		}
		if(cChar == '&')	//found entity start
		{
			cChar = _translate_entity();
		}
		oArrayWriter << cChar;
	}
	roValueArray.SetSize( oArrayWriter.CharactersWritten() + 1 );
	roValueArray[ oArrayWriter.CharactersWritten() ] = '\0';
	if(m_roStreamBuffer._get_char() != cQuoteChar)
	{
		return xe_expected_quote;
	}
	return xe_ok;
}

const long MAX_PART_LEN = 1020;

eXMLError CXMLParserImpl::_get_cdata(bool bBegin,CArray<TCHAR,TCHAR&> & roValueArray)
{
	if(bBegin)
	{
		TCHAR cCDATA[7];
		for(long iter = 0; iter < 7; iter++)
		{
			cCDATA[iter] = m_roStreamBuffer._get_char();
		}
		if(memcmp(cCDATA,_T("[CDATA["),sizeof(cCDATA)))
		{
			return xe_expected_cdata_start;
		}
	}
	CArrayWriter<TCHAR> oArrayWriter(roValueArray);
	long nMaxChars = m_poOutputSP->IsDataDirect() ? MAX_PART_LEN : MAXLONG;
	long iter = 0;
	for(iter = 0; iter < nMaxChars; iter++)
	{
		TCHAR cChar = m_roStreamBuffer._get_char();
		if(cChar == '\0')
		{
			break;
		}
		if(cChar == ']')
		{
			if(m_roStreamBuffer._get_char() == ']')
			{
				if(m_roStreamBuffer._get_char() == '>')
				{
					break;
				}
				m_roStreamBuffer._unget_char();
			}
			m_roStreamBuffer._unget_char();
		}
		if(cChar == '\n')
		{
			m_roParser._inc_line_nr();
		}
		if(cChar != '\r')	//skip carriage return
		{
			oArrayWriter << cChar;
		}
	}
	if(m_poOutputSP->IsDataDirect())
	{
		//NOT null terminated
		roValueArray.SetSize(oArrayWriter.CharactersWritten());
	}
	else
	{
		roValueArray.SetSize( oArrayWriter.CharactersWritten() + 1 );
		roValueArray[ oArrayWriter.CharactersWritten() ] = '\0';
	}
	if (iter >= nMaxChars)
	{
		return xe_cdata_more_data;
	}
	return xe_ok;
}


 CXMLParserImpl::CEntityTranslaction CXMLParserImpl::_g_entityarray[] =
{
	{ _T("gt;"),		'>' },
	{ _T("lt;"),		'<' },
	{ _T("amp;"),		'&' },
	{ _T("apos;"),		'\'' },
	{ _T("quot;"),		'\"' },
	{ _T("nbsp;"),		'\xA0' },
	{ _T("nl;"),		'\x0D' },
	{ NULL, '\0' }
};

TCHAR CXMLParserImpl::_translate_entity()
{
	//translate char

	//read entity
	CArray<TCHAR,TCHAR&> oEntityArray;
	CArrayWriter<TCHAR> oArrayWriter(oEntityArray);
	TCHAR cChar;
	do
	{
		cChar = m_roStreamBuffer._get_char();
		oArrayWriter << cChar;
	}
	while(cChar != ';' && cChar != '\0');
	oEntityArray.SetSize(oArrayWriter.CharactersWritten()+1);
	oEntityArray[ oArrayWriter.CharactersWritten() ] = '\0';
	for(CEntityTranslaction * pET = _g_entityarray; pET->m_lpEntity != NULL; pET++)
	{
		if(_tcscmp(pET->m_lpEntity,oEntityArray.GetData()) == 0)
		{
			return pET->m_cTranslated;
		}
	}
	ASSERT(false);	//unknown entity
	return '\0';
}

	
eXMLError CXMLParserImpl::_get_value_until_tag(CArray<TCHAR,TCHAR&> & roValueArray)
{
	CArrayWriter<TCHAR> oArrayWriter(roValueArray);
	long nMaxChars = m_poOutputSP->IsDataDirect() ? MAX_PART_LEN : MAXLONG;
	long iter = 0; 
	for(iter = 0; iter < nMaxChars; iter++)
	{
		TCHAR cChar = m_roStreamBuffer._get_char();
		if(cChar == '<' || cChar == '\0')
		{
			m_roStreamBuffer._unget_char();
			break;
		}
		if(cChar == '&')	//found entity start
		{
			cChar = _translate_entity();
		}
		oArrayWriter << cChar;
	}
	if(m_poOutputSP->IsDataDirect())
	{
		//NOT null terminated
		roValueArray.SetSize(oArrayWriter.CharactersWritten());
	}
	else
	{
		roValueArray.SetSize( oArrayWriter.CharactersWritten() + 1 );
		roValueArray[ oArrayWriter.CharactersWritten() ] = '\0';
	}
	if (iter >= nMaxChars)
	{
		return xe_value_more_data;
	}
	return xe_ok;
}

CString CXMLParserImpl::_get_attr_as_string()
{
	CString oString;
	POSITION pos = m_oAttributesMap.GetStartPosition();
	while(pos)
	{
		CString oAttrNameString;
		CString oAttrValueString;
		m_oAttributesMap.GetNextAssoc(pos,oAttrNameString,oAttrValueString);
		CString oString1;
		oString1.Format("%s='%s' ",oAttrNameString,oAttrValueString);
		oString += oString1;
	}
	return oString;
}

//----------------------------- top level class ------------------------------------

CXMLParser::CXMLParser() :
	m_nLineNr(0)
{
}

eXMLError CXMLParser::_go(SCP<CSAXHandler__> & rpoSAXHandler,SCP<IStream> & rpoInputStreamSP)
{
	CStreamBuffer oStreamBuffer(rpoInputStreamSP);
	CXMLParserImpl oParser(*this,oStreamBuffer,rpoSAXHandler);
	eXMLError eXE = oParser._skip_directives();
	if(eXE == xe_ok)
	{
		eXE = oParser._parse();
	}
	return eXE;
}

void CXMLParser::_make_error_snapshot(eXMLError eXE,CStreamBuffer & roStreamBuffer)
{
	CString oBufferString;
	long nCount = 256;
	while(nCount--)
	{
		TCHAR cChar = roStreamBuffer._get_char();
		oBufferString += cChar;
		if(cChar == '\0')
		{
			break;
		}
	}
	CString oString;

	POSITION pos = m_oParserStack.GetBottomPosition();
	while(pos)
	{
		CXMLParserImpl * poPI = m_oParserStack.MoveUp(pos);
		CString oString1;
		oString1.Format("(%d)<%s %s>\t",poPI->m_ePhase,
			(LPCTSTR)poPI->m_oElementNameArray.GetData(),
			poPI->_get_attr_as_string());
		oString += oString1;
	}
	oString += "(" + oBufferString + ")";
	CString oMsgString;
	NavoFormatErrorMsg(oMsgString,ERCO_PARSE_SYNTAX_ERROR_WITHINFO,oString,m_nLineNr,long(eXE));
	GetErrorStorage() += CNavoErrorInfo(ERCO_PARSE_SYNTAX_ERROR_WITHINFO,IDPAGE_NOTAVAILABLE,oMsgString);
}

bool ParseXML(SCP<CSAXHandler__> & rpoSAXHandler,SCP<IStream> & rpoInputStreamSP,
			  SCP<INavoErrorInfo> & rpoNavoErrorInfoSP)
{
	SCP<CXMLParser> poXMLParserSP = NewSCP(new CXMLParser());
	if(poXMLParserSP->_go(rpoSAXHandler,rpoInputStreamSP) != xe_ok)
	{
		rpoNavoErrorInfoSP.QueryInterface(poXMLParserSP);
		return false;
	}
	return  true;
}

