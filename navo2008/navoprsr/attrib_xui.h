/*
	NAVO Enterprise (2002)
	2002-07-13

	translator atrybutów		
*/

#ifndef _ATTRIB_XUI_H_
#define _ATTRIB_XUI_H_

class cnui_shortkey;

bool translate_attrib_ident(const CMapStringToString & roAttributes,ned_ident & rnIdent);

void translate_common_attrib(ned_declattributes & roDeclAttributes,const CMapStringToString & roAttributes);

bool translate_attrib_long(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,long & rnValue);
bool translate_attrib_boolean(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,bool & rnValue);
bool translate_attrib_color(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,ng_color & rColor);
bool translate_attrib_image(const CMapStringToString & roAttributes,CSmartOleVariant & roSOV);
bool translate_attrib_dimension(const CMapStringToString & roAttributes,const TCHAR * pcAttribName,long & rnDimension);
bool translate_attrib_href(const CMapStringToString & roAttributes,SCP<CHyperLinkInfo> & rpoHLISP);
bool translate_attrib_shortkey(const CMapStringToString & roAttributes,SCP<cnui_shortkey> & poShortKeySP);
bool translate_absolute_position(const CMapStringToString & roAttributes,ned_position & roPosition);
bool translate_attrib_margins(const CMapStringToString & roAttributes,ng_rect & rcMargins);

//obcina spacje
void trim_data_string(LPCTSTR lpDataString,ng_string & roOutputString);
//obcina spacje, likwiduje newlines
void normalize_data_string(LPCTSTR lpDataString,ng_string & roOutputString);

#else
	#error __FILE__ already included
#endif

