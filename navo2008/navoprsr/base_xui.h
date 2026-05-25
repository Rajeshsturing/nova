/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_parser__
		abstrakcyjna klasa bazowa parserów cned_*
	
	cxmlui_main_parser - SAX handler
		
*/

#ifndef _BASE_XUI_H_
#define _BASE_XUI_H_

class cxmlui_main_parser;

class cxmlui_parser__ : public CInterface__
{
public:
	cxmlui_parser__(cxmlui_main_parser * poContext,const ng_string & roTagString):
		m_poContext(poContext),
		m_oTagString(roTagString)
	{
	}
	
	virtual void begin(ned_ident /*nElementIdent*/){};
	virtual void attributes(const CMapStringToString & /* roAttribArray */){};
	virtual void end(){}
	virtual void data(LPCTSTR /*lpData*/){};

	LPCTSTR get_tag() const
	{
		return m_oTagString;
	}
protected:
	ng_string			m_oTagString;
	cxmlui_main_parser * m_poContext;
};

class cxmlui_element_parser__ : public cxmlui_parser__
{
public:
	cxmlui_element_parser__(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	SCP<cned_element> get_uielement()
	{
		return m_poElementSP;
	}
	void create_element(ened_element_type eType,ned_ident nIdent)
	{
		m_poElementSP = get_current_container()->insert_new_element(eType,nIdent,NEDID_LAST);
	}
	SCP<cned_container> get_current_container();
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void data(LPCTSTR lpData);
protected:
	SCP<cned_element>	m_poElementSP;
};

class cxmlui_main_parser : public CSAXHandler__
{
public:
	cxmlui_main_parser(CSAXHandlerController__ * poSAXController,SCP<cned_window> & rpoWindowSP,SCP<CDefinitionManager> poDefinitionManagerSP) :
		CSAXHandler__(poSAXController),
		m_poWindowSP(rpoWindowSP),
		m_poDefinitionManagerSP(poDefinitionManagerSP),
		m_nElementPendingCounter(MAXLONG),
		m_nElementReadCounter(0)
	{
	}
	~cxmlui_main_parser();

	//for reading XML code part
	void start_with_container(SCP<cned_container> poContainerSP);
	void end_with_container();

	void set_chunk_size(long nChunk);

	virtual void OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes);
	virtual void OnEndElement(LPCTSTR lpElement);
	virtual bool IsDataDirect() const
	{
		return false;
	}
	virtual void OnDataValue(LPCTSTR,long)
	{
		ASSERT(false);
	}
	virtual void OnDataValue(LPCTSTR lpValue);

	SCP<cxmlui_parser__> get_current_parser();
	SCP<cxmlui_parser__> create_parser(const ng_string & roElementString);
	SCP<cned_window> get_window()
	{
		return m_poWindowSP;
	}
	SCP<CDefinitionManager> get_definition_manager()
	{
		return m_poDefinitionManagerSP;
	}
	long get_current_typeid() const;
	void push_typeid(long nTypeId);
	void pop_typeid();
	void push_page_element(cned_page * poPageElement);
	void pop_page_element();
	void set_current_page_title(const ng_string & roTitleString);
	cned_page * get_current_page_element();

	long resolve_field(LPCTSTR lpData,long nTypeId);
	void add_to_script(LPCTSTR lpScriptPart)
	{
		m_oScriptCodeString += lpScriptPart;
	}
	void set_script_nxid(LPCTSTR lpNXID)
	{
		m_strScriptNXID = lpNXID;
	}
private:
	static ened_element_type _lookup_element_type(LPCTSTR lpTag,long & rnVariant);

	CEnhancedStack< SCP<cxmlui_parser__> > m_oParserStack;
	CEnhancedStack< long >				   m_oTypeIdStack;
	CEnhancedStack< cned_page * >          m_oPageStack;

	SCP<cned_window>	m_poWindowSP;
	SCP<CDefinitionManager> m_poDefinitionManagerSP;
	ng_string			m_oScriptCodeString;
	ng_string			m_strScriptNXID;
	long				m_nElementPendingCounter;
	long				m_nElementReadCounter;
	ng_string			m_oCurrentPageTitleString;
};

inline void cxmlui_main_parser::set_chunk_size(long nChunk)
{
	ASSERT(nChunk > 0);
	m_nElementPendingCounter = nChunk;
}

#else
	#error __FILE__ already included
#endif

