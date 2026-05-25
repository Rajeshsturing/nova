/*
	NAVO Enterprise (2002)
	2002-09-01

	cxmlui_style_parser - SAX handler dla styli
		
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"
#include "..\navogal\ngal_iface.h"
#include "..\navoui\common_ned_inc.h"		//common includes
using namespace ned;

#include "attrib_xui.h"
#include "style_xui.h"


#include "..\navoui\style_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern const TCHAR * pcAttribIdent;
static const TCHAR * pcAttribAuthor				= _T("author");

cxmlui_style_parser::cxmlui_style_parser(SCP<cned_style> poStyleSP) :
	CSAXHandler__(NULL),
	m_poStyleSP(poStyleSP)
{
	ASSERT(m_poStyleSP.PointsObject());
}

void cxmlui_style_parser::OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttribArray)
{
	ng_string oElementString(lpElement);
	oElementString.MakeLower();
	ASSERT(!oElementString.IsEmpty());
	switch(oElementString[0])
	{		
	case 's':	//<style
		{
			ng_string oString;
			if(!roAttribArray.Lookup(pcAttribIdent,oString))
			{
				//error: style name is required
				ThrowNavoException(ERCO_TODO,IDPAGE_NOTAVAILABLE);
			}
			m_poStyleSP->set_prop_name(oString);
			if(roAttribArray.Lookup(pcAttribAuthor,oString))
			{
				m_poStyleSP->set_prop_author(oString);
			}
		}
	return;
	case 'i':
		{
			ASSERT(!roAttribArray.IsEmpty());
			ned_ident nIdent = NEDID_NOTHING;
			translate_attrib_ident(roAttribArray,nIdent);
			if(nIdent == NEDID_NOTHING)
			{
				//error: invalid style item name
				ThrowNavoException(ERCO_TODO,IDPAGE_NOTAVAILABLE);
			}
			SCP<cned_styleitem> poStyleItemSP = NewSCP(new cned_styleitem());
			translate_common_attrib(*poStyleItemSP,roAttribArray);
			m_poStyleSP->add_item(long(nIdent),poStyleItemSP);
		}
	return;
	}
	ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE,IDPAGE_NOTAVAILABLE,oElementString);
}

void cxmlui_style_parser::OnEndElement(LPCTSTR /*lpElement*/)
{
}

void cxmlui_style_parser::OnDataValue(LPCTSTR /*lpValue*/)
{
}



bool read_style_xml(SCP<IStream> poStreamSP,SCP<cned_style> poStyleSP)
{
	SCP<INavoErrorInfo> poNavoErrorInfoSP;
		if(!ParseXML(NewSCP<CSAXHandler__>(new cxmlui_style_parser(poStyleSP)),
			poStreamSP,poNavoErrorInfoSP))
		{
			//to_do: zg³osiæ error
			ASSERT(false);
			return false;
		}
	return true;
}


