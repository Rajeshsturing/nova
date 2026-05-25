/*
	NAVO Enterprise 2008

	SAXHandlerAUTO

	gateway SAXHandler to VBS based SAX interpreters
*/

#ifndef _SAX_HANDLER_AUTO_H_
#define _SAX_HANDLER_AUTO_H_

class CSAXHandlerAUTO : public CSAXHandler__
{
public:
	CSAXHandlerAUTO(SCP<IDispatch> poSinkObjectDispatchSP);
	~CSAXHandlerAUTO();
	virtual void OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes);
	virtual void OnEndElement(LPCTSTR lpElement);
	virtual bool IsDataDirect() const
	{
		return false;
	}
	virtual void OnDataValue(LPCTSTR lpValue,long nLength);
	virtual void OnDataValue(LPCTSTR lpValue);
private:
	SCP<IDispatch>	m_poSinkObjectDispatchSP;
	
	void _invoke(DISPID dispid,CSmartOleVariant * pArguments,long nArgCount);

	DISPID m_dispid_start;
	DISPID m_dispid_data;
	DISPID m_dispid_end;
};

#else
	#error __FILE__ already included
#endif
