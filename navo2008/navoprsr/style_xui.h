/*
	NAVO Enterprise (2002)
	2002-09-01

	cxmlui_style_parser - SAX handler dla styli
		
*/

#ifndef _STYLE_XUI_H_
#define _STYLE_XUI_H_

class cxmlui_style_parser : public CSAXHandler__
{
public:
	cxmlui_style_parser(SCP<cned_style> poStyleSP);
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

private:
	SCP<cned_style> m_poStyleSP;
};

#else
	#error __FILE__ already included
#endif

