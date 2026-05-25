/*
	NAVO Enterprise 2008

	MIMEDecoder
	various specialized mime decoders
*/

#ifndef _MIMEDECODER_H_
#define _MIMEDECODER_H_

//----------------------------------------------------------
//-- performs no operation except copying to msgpart  ------
//----------------------------------------------------------

class CDumbDecoder : public CMIMEDecoder__
{
public:
	CDumbDecoder(SCP<cnavopop3_msg_part> poMsgPartSP,CStreamLineReader & roSLR,LPCTSTR lpTerminator);
	virtual enavopop3_error _decode()
	{
		TRACE("*************************** DUMB BODY ***************************** \n");
		return _common_loop();
	}
	virtual enavopop3_error _uncommon(const CString & roLastLineString)
	{
		TRACE("DUMB:%s\n",roLastLineString);
		return ene_OK;
	};
};

//----------------------------------------------------------
//-- decodes text/plain -----------------------------------
//----------------------------------------------------------

class CPlainTextDecoder : public CMIMEDecoder__
{
public:
	CPlainTextDecoder(SCP<cnavopop3_msg_part> poMsgPartSP,CStreamLineReader & roSLR,LPCTSTR lpTerminator);
	virtual enavopop3_error _decode();
	virtual enavopop3_error _uncommon(const CString & roLastLineString);
protected:
	SCP<IStream> m_poBodyStreamSP;
};

class CMultiPartDecoder : public CMIMEDecoder__
{
public:
	CMultiPartDecoder(SCP<cnavopop3_msg_part> poMsgPartSP,CStreamLineReader & roSLR,LPCTSTR lpTerminator);
	virtual enavopop3_error _decode();
	virtual enavopop3_error _uncommon(const CString & roLastLineString);
protected:
	enavopop3_error _retrieve_boundary();
	CString m_oBoundaryString;
	bool	m_bEndReached;
};


#else
	#error __FILE__ already included
#endif
