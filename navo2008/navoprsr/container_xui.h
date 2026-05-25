/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_container_parser__
		abstrakcyjna klasa bazowa parserów cned_container*
		
*/

#ifndef _CONTAINER_XUI_H_
#define _CONTAINER_XUI_H_

class cxmlui_container_parser__ : public cxmlui_element_parser__
{
public:
	cxmlui_container_parser__(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	SCP<cned_container> get_container()
	{
		ASSERT(get_uielement().PointsObject());
		return scp_cast_ui<cned_container>(get_uielement());
	}
	void special_set_cointainer(SCP<cned_container> poContainerSP)
	{
		m_poElementSP = NewSCP<cned_element>(poContainerSP.Get(),true);
	}
};

class cxmlui_group_container_parser_ : public cxmlui_container_parser__
{
public:
	cxmlui_group_container_parser_(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
};

class cxmlui_page_parser : public cxmlui_group_container_parser_
{
public:
	cxmlui_page_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_group_container_parser_(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_subpage,nIdent);
		m_poContext->push_page_element((cned_page*)m_poElementSP.Get());
	}
	virtual void end()
	{
		m_poContext->pop_page_element();
		cxmlui_container_parser__::end();
	}
};

class cxmlui_toplevel_parser : public cxmlui_page_parser
{
public:
	cxmlui_toplevel_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_page_parser(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void begin(ned_ident /*nElementIdent*/)
	{
		m_poElementSP = m_poContext->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE);
		m_poContext->push_page_element((cned_page*)m_poElementSP.Get());
	}
};

class cxmlui_table_parser : public cxmlui_container_parser__
{
public:
	cxmlui_table_parser(bool bGrid,cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString),
		m_bGrid(bGrid)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(m_bGrid ? ned_grid : ned_table,nIdent);
	}
	virtual void end();
private:
	bool m_bGrid;
};

class cxmlui_table_section_parser : public cxmlui_container_parser__
{
public:
	cxmlui_table_section_parser(long nParseVar,cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString),
		m_eParseSectionType(ened_tablesection_enum(nParseVar))
	{
		//TRACE("<tsection>\n");
	}
	~cxmlui_table_section_parser()
	{
		//TRACE("</tsection>\n");
	}
	virtual void begin(ned_ident nIdent);
	virtual void attributes(const CMapStringToString & roAttribArray);
private:
	const ened_tablesection_enum m_eParseSectionType;

	//1-thead = ntt_firstheader
	//2-tbody = ntt_body
	//3-tfoot = ntt_lastfotter
};

class cxmlui_table_row_parser : public cxmlui_container_parser__
{
public:
	cxmlui_table_row_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString)
	{
		//TRACE("<tr>");
	}
	~cxmlui_table_row_parser()
	{
		//TRACE("</tr>\n");
	}
	virtual void begin(ned_ident nIdent);
};

class cxmlui_table_cell_parser : public cxmlui_group_container_parser_
{
public:
	cxmlui_table_cell_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_group_container_parser_(poContext,roTagString)
	{
		//TRACE("<td ");
	}
	~cxmlui_table_cell_parser()
	{
		//TRACE("</td>\n");
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_tablecell,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
};

class cxmlui_paragraph_parser : public cxmlui_group_container_parser_
{
public:
	cxmlui_paragraph_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_group_container_parser_(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_paragraph,nIdent);
	}
};

class cxmlui_scroll_parser : public cxmlui_paragraph_parser
{
public:
	cxmlui_scroll_parser(bool bHorizontal,cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_paragraph_parser(poContext,roTagString),
		m_bHorizontal(bHorizontal)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(m_bHorizontal ? ned_hscroll : ned_vscroll,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
private:
	bool m_bHorizontal;
};

class cxmlui_checkbox_radio_parser : public cxmlui_container_parser__
{
public:
	cxmlui_checkbox_radio_parser(bool bRadio,cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString),
		m_bRadio(bRadio)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void begin(ned_ident nIdent)
	{
		create_element(m_bRadio ? ned_radio : ned_checkbox,nIdent);
	}
private:
	bool	m_bRadio;
};

class cxmlui_tabitem_parser : public cxmlui_paragraph_parser
{
public:
	cxmlui_tabitem_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_paragraph_parser(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_tabitem,nIdent);
	}
};

class cxmlui_tabmanager_parser : public cxmlui_container_parser__
{
public:
	cxmlui_tabmanager_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_container_parser__(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);

	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_tabmanager,nIdent);
	}
};

#else
	#error __FILE__ already included
#endif


