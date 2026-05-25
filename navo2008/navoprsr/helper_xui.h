/*
	NAVO Enterprise (2002)
	2002-07-13

	helper parsery
		parsery pomocnicze


*/
#ifndef _HELPER_XUI_H_
#define _HELPER_XUI_H_

class cxmlui_script_parser : public cxmlui_parser__
{
public:
	cxmlui_script_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
	virtual void attributes(const CMapStringToString & roAttribArray);
};

class cxmlui_config_parser : public cxmlui_parser__
{
public:
	cxmlui_config_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident /*nElementIdent*/);
private:
};

class cxmlui_typeid_parser : public cxmlui_parser__
{
public:
	cxmlui_typeid_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_securityid_parser : public cxmlui_parser__
{
public:
	cxmlui_securityid_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_fixediid_parser : public cxmlui_parser__
{
public:
	cxmlui_fixediid_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_startpos_parser : public cxmlui_parser__
{
public:
	cxmlui_startpos_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};


class cxmlui_startfocus_parser : public cxmlui_parser__
{
public:
	cxmlui_startfocus_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_title_parser : public cxmlui_parser__
{
public:
	cxmlui_title_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident /*nElementIdent*/);
	virtual void data(LPCTSTR lpData);
};

class cxmlui_page_header_parser : public cxmlui_paragraph_parser
{
public:
	cxmlui_page_header_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_paragraph_parser(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray)
	{
		cxmlui_paragraph_parser::attributes(roAttribArray);
	}
	virtual void begin(ned_ident)
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>
			(m_poContext->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE));
		m_poElementSP = NewSCP<cned_element>(poPageSP->_get_header().Get(),true);
	}
};

class cxmlui_page_body_parser : public cxmlui_group_container_parser_
{
public:
	cxmlui_page_body_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_group_container_parser_(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray)
	{
		//cxmlui_group_container_parser_::attributes(roAttribArray);
	}
	virtual void begin(ned_ident)
	{
		m_poElementSP = m_poContext->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE);
	}
};

class cxmlui_page_footer_parser : public cxmlui_paragraph_parser
{
public:
	cxmlui_page_footer_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_paragraph_parser(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray)
	{
		cxmlui_paragraph_parser::attributes(roAttribArray);
	}
	virtual void begin(ned_ident)
	{
		SCP<cned_page> poPageSP = scp_cast_ui<cned_page>
			(m_poContext->get_window()->get_element_on_ident(NEDID_TOPLEVELPAGE));
		m_poElementSP = NewSCP<cned_element>(poPageSP->_get_footer(),true);
	}
};

class cxmlui_transfer_parser : public cxmlui_parser__
{
public:
	cxmlui_transfer_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString),
			m_Ident(NEDID_NOTHING)
	{
	}
	virtual void begin(ned_ident /*nElementIdent*/);
	virtual void attributes(const CMapStringToString & roAttribArray);

	ned_ident get_element_ident() const
	{
		return m_Ident;
	}
	SCP<nui_transfer> get_transfer()
	{
		return m_poTransferSP;
	}
private:
	ned_ident m_Ident;
	SCP<nui_transfer> m_poTransferSP;
};

class cxmlui_transfer_part_parser : public cxmlui_parser__
{
public:
	cxmlui_transfer_part_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident /*nElementIdent*/);
protected:
	SCP<cxmlui_transfer_parser> m_poTransferParserSP;
};

class cxmlui_field_parser : public cxmlui_transfer_part_parser
{
public:
	cxmlui_field_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_transfer_part_parser(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_searchfield_parser : public cxmlui_transfer_part_parser
{
public:
	cxmlui_searchfield_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_transfer_part_parser(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_cursor_parser : public cxmlui_transfer_part_parser
{
public:
	cxmlui_cursor_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_transfer_part_parser(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_reftypeid_parser : public cxmlui_transfer_part_parser
{
public:
	cxmlui_reftypeid_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_transfer_part_parser(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

//---------- version > 1.3 -------------------------------------
//------------ inplace script code for control event handlers --
class cxmlui_inlplacehandler_parser : public cxmlui_transfer_part_parser
{
public:
	cxmlui_inlplacehandler_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_transfer_part_parser(poContext,roTagString)
	{
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_ondataentered_parser : public cxmlui_inlplacehandler_parser
{
public:
	cxmlui_ondataentered_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_inlplacehandler_parser(poContext,roTagString)
	{
	}
};

class cxmlui_ongetdata_parser : public cxmlui_inlplacehandler_parser
{
public:
	cxmlui_ongetdata_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_inlplacehandler_parser(poContext,roTagString)
	{
	}
};

class cxmlui_ongetfocus_parser : public cxmlui_inlplacehandler_parser
{
public:
	cxmlui_ongetfocus_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_inlplacehandler_parser(poContext,roTagString)
	{
	}
};

class cxmlui_onlostfocus_parser : public cxmlui_inlplacehandler_parser
{
public:
	cxmlui_onlostfocus_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_inlplacehandler_parser(poContext,roTagString)
	{
	}
};

#else
	#error __FILE__ already included
#endif


