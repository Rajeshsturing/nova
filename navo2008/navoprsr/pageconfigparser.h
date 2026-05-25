/*
	NAVO Enterprise (2001)
	UI Page Config Parser
*/

#ifndef _PAGECONFIGPARSER_H_
#define _PAGECONFIGPARSER_H_

enum PageConfigToken
{
	pctnone,
	pctbuttons,
	pctbutton,
	pctscript,
	pcttypeid,
	pctstyle,
	pcttitle,
	pctstartpos,
	pctstartfocus,
	pctsecurityid_read,
	pctsecurityid_insert,
	pctsecurityid_update,
	pctsecurityid_delete,
};

class CPageConfigParser : public CInterface__
{
public:
	CPageConfigParser(CParseContext * poParseContext,SCP<CUIPageManager> & rpoPageManagerSP) :
		m_poParseContext(poParseContext),
		m_eCurrentToken(pctnone),
		m_poPageManagerSP(rpoPageManagerSP)
	{
	}
	~CPageConfigParser();
	void OnStartElement(const CString & roElementString,const CMapStringToString & roAttributes);
	void OnEndElement(const CString & roElementString);
	void OnDataValue(LPCTSTR lpValue);
private:
	PageConfigToken		m_eCurrentToken;
	SCP<CUIPageManager>	m_poPageManagerSP;
	CParseContext *		m_poParseContext;
};

#else
	#error __FILE__ already included
#endif