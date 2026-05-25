/*
	NAVO Enterprise 2003
	2003-08-01

	navo RTF pre-parser

	dzieli strumieñ RTF na fragmenty
*/

#include "stdafx.h"
#include "rtf_preparser.h"

/*
void cpreparser::go()
{
	CStreamBuffer oStreamBufer(m_poInputStreamSP);

	while(true)
	{
		char cChar = oStreamBufer._get_char();
		switch(cChar)
		{
		case '\0':
			return;
		case '{':
			m_roSink.enter();
		break;
		case '}':
			m_roSink.leave();
		break;
		case 0x0d:
		case 0x0a:
			//noop
		break;
		case '\\':
			_translate_token(oStreamBufer);
		break;
		default:
			if(m_bBinary)
			{
			}
			else
			{
				m_roSink.on_text(cChar);
			}
		}
	}
}

#define c2h(_b_)	(((_b_) > '9') ? (((_b_) - 'a') + 10) : ((_b_) - '0'))

void cpreparser::_translate_token(CStreamBuffer & roStreamBuffer)
{
	char cChar = roStreamBuffer._get_char();
	if(!IsAlpha(cChar))
	{
		if(cChar == '\'')
		{
			char cB1 = ToLower(roStreamBuffer._get_char());
			char cB2 = ToLower(roStreamBuffer._get_char());
			m_roSink.on_hex_byte((BYTE)( c2h(cB1) * 16 + c2h(cB2) ));
			return;
		}
		else
		{
			char c2Bytes[2] = "\0";
			c2Bytes[0] = cChar;
			m_roSink.on_token(c2Bytes);
			return;
		}
	}

	CString oTokenString(cChar);
	while(true)
	{
		cChar = roStreamBuffer._get_char();
		if(!IsAlpha(cChar))
		{
			break;
		}
		oTokenString += cChar;
	}
	CString oValueString;

	if(IsDigit(cChar) || cChar == '-')
	{
		oValueString = cChar;
		cChar = roStreamBuffer._get_char();
		while(IsDigit(cChar))
		{
			oValueString += cChar;
			cChar = roStreamBuffer._get_char();
		}
		m_roSink.on_token_number(oTokenString,_ttol(oValueString));
	}
	else
	{
		m_roSink.on_token(oTokenString);
	}
	if(cChar != ' ')
	{
		roStreamBuffer._unget_char();
	}
}


//----------------------------------------------------------------------------------------
//	crtf_asp_token_sink
//----------------------------------------------------------------------------------------
class crtf_asp_token_sink : public crtf_token_sink__
{
public:
	crtf_asp_token_sink(SCP<IStream> poOutputStreamSP);

	virtual void on_token(LPCTSTR lpToken);
	virtual void on_token_number(LPCTSTR lpToken,long nValue);
	virtual void on_text(char cChar);
	virtual void on_hex_byte(BYTE cByte);
	virtual void enter();
	virtual void leave();
private:

	void _put(char cChar);
	void _puts(LPCTSTR lpStr);
	enum eLastText
	{
		elt_open,		// opening "<"
		elt_perc,		// closing "%"
		elt_other,		//other
	};

	eLastText		m_eLastText;
	bool			m_bModeVB;

	SCP<IStream>	m_poOutputStreamSP;
	CStreamHolder	m_oOSH;

};

inline void crtf_asp_token_sink::_put(char cChar)
{
	m_oOSH.Write(&cChar,sizeof(cChar)); 
}

inline void crtf_asp_token_sink::_puts(LPCTSTR lpStr)
{
	m_oOSH.WriteString(lpStr);
}

crtf_asp_token_sink::crtf_asp_token_sink(SCP<IStream> poOutputStreamSP) :
	m_poOutputStreamSP(poOutputStreamSP),
	m_oOSH(poOutputStreamSP),
	m_eLastText(elt_other),
	m_bModeVB(false)
{
}

void crtf_asp_token_sink::on_hex_byte(BYTE cByte)
{
	_put('\\');
	_put('\'');
	
	char cHex[4] = { '\0', '\0','\0','\0' };
	ltoa(256+long(cByte),cHex,16);
	_puts(cHex+1);
}

void crtf_asp_token_sink::on_token(LPCTSTR lpToken)
{
	if(!m_bModeVB)
	{
		_put('\\');
		_puts(lpToken);
	}
}

void crtf_asp_token_sink::on_token_number(LPCTSTR lpToken,long nValue)
{
	if(!m_bModeVB)
	{
		_put('\\');
		_puts(lpToken);
		_puts(Long2String(nValue));
	}
}

void crtf_asp_token_sink::on_text(char cChar)
{
	if(cChar == '<')
	{
		m_eLastText = elt_open;
	}
	else
	{
		if(cChar == '%')
		{
			if(m_eLastText == elt_open)
			{
				//start of ASP
				m_bModeVB = true;
			}
			m_eLastText = elt_perc;
		}
		else
		{
			if(cChar == '>')
			{
				if(m_eLastText == elt_perc)
				{
					//end of ASP
					m_bModeVB = false;
				}
			}
			m_eLastText = elt_other;
		}
	}

	_put(cChar);
}

void crtf_asp_token_sink::enter()
{
	if(!m_bModeVB)
	{
		_put('{');
	}
}

void crtf_asp_token_sink::leave()
{
	if(!m_bModeVB)
	{
		_put('}');
	}
}


static void test()
{
	
	SCP<IStream> poInputStreamSP = OpenFileStream_Read_On_SOV(CSmartOleVariant("c:\\temp\\a.rtf"));

	SCP<CFileRemover> poFileRemoverSP;
	SCP<IStream> poOutputStreamSP = CreateFileStream_Write_On_SOV(CSmartOleVariant("c:\\temp\\b.rtf"),poFileRemoverSP);
	if(poFileRemoverSP.PointsObject())
	{
		poFileRemoverSP->DontRemove();
	}

	crtf_asp_token_sink oSink(poOutputStreamSP);
	cpreparser oPreParser(oSink,poInputStreamSP);
	oPreParser.go();
}

*/
