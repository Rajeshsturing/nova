/*
	NAVO Enterprise (2001)
	
	Basic XML SAX parser
*/

#if !defined(AFX_SAXPARSER__H__5E4BCE0A_FDB4_430E_95A8_4ACB0BB62D2F__INCLUDED_)
#define AFX_SAXPARSER__H__5E4BCE0A_FDB4_430E_95A8_4ACB0BB62D2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum eXMLError
{
	xe_ok,
	xe_unexpected,
	xe_ident_too_long,
	xe_expected_less,
	xe_expected_ident,
	xe_expected_greater,
	xe_expected_equal,
	xe_expected_slash,
	xe_expected_quote,
	xe_value_too_long,
	xe_cdata_more_data,
	xe_mismatched_tags,
	xe_value_more_data,
	xe_expected_cdata_start,
	xe_data_multipletimes,
	xe_aborted,
};

class CXMLParser;

class CXMLParserImpl
{
public:
	CXMLParserImpl(CXMLParser & roParser,CStreamBuffer & roTokenizer,SCP<CSAXHandler__> poOutputSP);
	~CXMLParserImpl();
	eXMLError _parse();
	eXMLError _skip_directives();
private:
	bool _skip_comment();
	bool _skip_white();
	eXMLError _get_ident(CArray<TCHAR,TCHAR&> & roIdentArray);
	eXMLError _get_value_in_quotes(CArray<TCHAR,TCHAR&> & roValueArray);
	eXMLError _get_cdata(bool bBegin,CArray<TCHAR,TCHAR&> & roValueArray);
	eXMLError _get_value_until_tag(CArray<TCHAR,TCHAR&> & roValueArray);

	TCHAR _translate_entity();
	CString _get_attr_as_string();

	CStreamBuffer & m_roStreamBuffer;
	SCP<CSAXHandler__> m_poOutputSP;
	CXMLParser &	m_roParser;

	CArray<TCHAR,TCHAR&> m_oElementNameArray;

	CMapStringToString m_oAttributesMap;

	struct CEntityTranslaction
	{
		LPCTSTR m_lpEntity;
		TCHAR	m_cTranslated;
	};
	static CEntityTranslaction _g_entityarray[];

	friend class CXMLParser;
	enum ePhase
	{
		xp_bef_op,				//before opening tag
		xp_in_op,				//inside opening tag
		xp_in_cont,				//inside content
		xp_in_cl,				//inside closing tag
	};
	ePhase m_ePhase;
};

class CXMLParser : public CCmdTargetWithErrorInfo
{
public:
	CXMLParser();
	eXMLError _go(SCP<CSAXHandler__> & rpoSAXHandler,SCP<IStream> & rpoInputStreamSP);
	void _inc_line_nr()
	{
		++m_nLineNr;
	}
	void _push(CXMLParserImpl * poParserImpl)
	{
		m_oParserStack.Push(poParserImpl);
	}
	void _pop()
	{
		m_oParserStack.Pop();
	}
	void _make_error_snapshot(eXMLError eXE,CStreamBuffer & roStreamBuffer);
private:
	CEnhancedStack<CXMLParserImpl *>	m_oParserStack;
	long	m_nLineNr;
};


#endif // !defined(AFX_SAXPARSER__H__5E4BCE0A_FDB4_430E_95A8_4ACB0BB62D2F__INCLUDED_)
