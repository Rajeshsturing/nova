/*
	NAVO Enterprise (2002)
	2002-07-13

	cxmlui_*_parser
		parsery ró¿nych ned_elementów (prostych)


*/
#ifndef _ELEMENT_XUI_H_
#define _ELEMENT_XUI_H_

class cxmlui_static_parser : public cxmlui_element_parser__
{
public:
	cxmlui_static_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_static,nIdent);
	}
	virtual void data(LPCTSTR lpData);
	virtual void attributes(const CMapStringToString & roAttribArray);
};

class cxmlui_staticex_parser : public cxmlui_element_parser__
{
public:
	cxmlui_staticex_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_staticex,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void data(LPCTSTR lpData);
};

class cxmlui_extern_parser : public cxmlui_element_parser__
{
public:
	cxmlui_extern_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_extern,nIdent);
	}
	virtual void data(LPCTSTR lpData)
	{
		scp_cast_ui<cned_extern>(get_uielement())->set_prop_data(lpData);
	}
};

class cxmlui_picture_parser : public cxmlui_element_parser__
{
public:
	cxmlui_picture_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_picture,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void data(LPCTSTR lpData);
};

class cxmlui_breakline_parser : public cxmlui_element_parser__
{
public:
	cxmlui_breakline_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_breakline,nIdent);
	}
};

class cxmlui_breakpage_parser : public cxmlui_element_parser__
{
public:
	cxmlui_breakpage_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_breakpage,nIdent);
	}
};

class cxmlui_button_parser : public cxmlui_static_parser
{
public:
	cxmlui_button_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_static_parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_button,nIdent);
	}
};

class cxmlui_edit__parser : public cxmlui_element_parser__
{
public:
	cxmlui_edit__parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
	virtual void data(LPCTSTR lpData);
};

class cxmlui_textedit_parser : public cxmlui_edit__parser
{
public:
	cxmlui_textedit_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_edit__parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_textedit,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
};

class cxmlui_currency_edit_parser : public cxmlui_edit__parser
{
public:
	cxmlui_currency_edit_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_edit__parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_currency,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
};


class cxmlui_date_edit_parser : public cxmlui_edit__parser
{
public:
	cxmlui_date_edit_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_edit__parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_date,nIdent);
	}
};

class cxmlui_time_edit_parser : public cxmlui_edit__parser
{
public:
	cxmlui_time_edit_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_edit__parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_timeed,nIdent);
	}
};

class cxmlui_int_edit_parser : public cxmlui_edit__parser
{
public:
	cxmlui_int_edit_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_edit__parser(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_intedit,nIdent);
	}
};

class cxmlui_multi_rich_edit_parser : public cxmlui_element_parser__
{
public:
	cxmlui_multi_rich_edit_parser(bool bRTF,cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString),
		m_bRTF(bRTF)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(m_bRTF ? ned_richedit : ned_multiline,nIdent);
	}
	virtual void data(LPCTSTR lpData);
	virtual void attributes(const CMapStringToString & roAttribArray);
private:
	bool	m_bRTF;
};

class cxmlui_web_parser : public cxmlui_element_parser__
{
public:
	cxmlui_web_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_htmlwindow,nIdent);
	}
	virtual void data(LPCTSTR lpData);
};

class cxmlui_olecontrol_parser : public cxmlui_element_parser__
{
public:
	cxmlui_olecontrol_parser(cxmlui_main_parser * poContext,const ng_string & roTagString) :
		cxmlui_element_parser__(poContext,roTagString)
	{
	}
	virtual void begin(ned_ident nIdent)
	{
		create_element(ned_olecontrol,nIdent);
	}
	virtual void attributes(const CMapStringToString & roAttribArray);
};

#else
	#error __FILE__ already included
#endif


