/*
	NAVO Enterprise 2001
	Import SAX Parser
*/

#ifndef _IMPORT_PARSER_H_
#define _IMPORT_PARSER_H_

///------------------------------------------------------------------
/// import sax handler
///------------------------------------------------------------------

class CImportSAXHandler : public CSAXHandler__
{
public:
	CImportSAXHandler(CImportSinkInfo & roImportSinkInfo) :
		CSAXHandler__(NULL),
		m_roImportSinkInfo(roImportSinkInfo),
		m_eState(is_none),
		m_eFieldVariant(fv_none),
		m_vtFieldType(VT_EMPTY),
		m_bFieldConsumed(false)
	{
	}
	virtual void OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes);
	virtual void OnEndElement(LPCTSTR lpElement);
	virtual bool IsDataDirect() const;
	virtual void OnDataValue(LPCTSTR lpElement,long nLength);
	virtual void OnDataValue(LPCTSTR lpValue);
private:
	enum State
	{
		is_none,	//expecting neipckg (package)
		is_msg,		//expecting neimsg (message)
		is_obj,		//expecting neio (object
		is_field,	//expecting field or typeid or idobj
	};
	enum FieldVariant
	{
		fv_none,
		fv_typeid,
		fv_idobj,
		fv_regular
	};

	State		 m_eState;
	FieldVariant m_eFieldVariant;
	CString		 m_oFieldNameString;
	VARTYPE		 m_vtFieldType;
	CString		 m_oFieldValueString;
	SCP<IStream> m_poBigFieldStreamSP;
	CImportSinkInfo & m_roImportSinkInfo;
	bool		 m_bFieldConsumed;
	
	SCP<CImportMessage> m_poCurrentMsgSP;
	SCP<CImportObject>	m_poCurrentObjectSP;
};



#else
	#error __FILE__ already included
#endif
