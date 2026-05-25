/*
	NAVO Enterprise 2003
	2003-08-01

	navo RTF pre-parser

	dzieli strumieñ RTF na fragmenty
*/

#ifndef _RTF_PREPARSER_H_
#define _RTF_PREPARSER_H_

/*
//--------- virtual RTF token sink

class crtf_token_sink__ 
{
public:
	crtf_token_sink__(){}
	virtual void on_token(LPCTSTR lpToken) = 0;
	virtual void on_token_number(LPCTSTR lpToken,long nValue) = 0;
	virtual void on_text(char cChar) = 0;
	virtual void on_hex_byte(BYTE cByte) = 0;
	virtual void enter() = 0;
	virtual void leave() = 0;
};

class cpreparser
{
public:
	cpreparser(crtf_token_sink__ & roSink,SCP<IStream> poInputStreamSP);
	void go();
private:
	void _translate_token(CStreamBuffer & roStreamBuffer);

	SCP<IStream>	m_poInputStreamSP;
	crtf_token_sink__ & m_roSink;
	bool			m_bBinary;
};

//-------------- inlines -------------
inline cpreparser::cpreparser(crtf_token_sink__ & roSink,SCP<IStream> poInputStreamSP) :
	m_roSink(roSink),
	m_poInputStreamSP(poInputStreamSP),
	m_bBinary(false)
{
}

*/
#else
	#error File already included
#endif
