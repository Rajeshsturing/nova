/*
	NAVO Enterprise 2008
	28.08.2002
	
	multiline_
	abstrakcyjna klasa obs³uguj¹ca tekst z podzia³em na linie
*/

#ifndef _MULTILINE_NUI_H_
#define _MULTILINE_NUI_H_

const TCHAR NEWLINE_CHAR = '\x0D';

//zamienia sekwencjê CR + LF na pojedyñczy znak Newline
void normalize_string_newlines(const ng_string & roInputString,ng_string & roOutputString);
void unnormalize_string_newlines(const ng_string & roInputString,ng_string & roOutputString);

class multiline_
{
protected:
	multiline_();

	const ng_string & _get_prop_text() const
	{
		return m_oTextString;
	}

	void _get_area(ng_area & roArea) const;
	void _set_prop_text(const ng_string & roText);
	void _on_insert_char(TCHAR cChar,long nPosition);
	void _on_insert_string(const ng_string & roString,long nPosition);
	void _on_delete_char(long nPosition);
	void _on_delete_string(long nPosition,long nCount);
	void _reflow(cnui_element * poElement,cnui_renderer__ & roRenderer,SCP<ng_font> & rpoFontSP,ng_area & roUpdateArea);
	void _measure(cnui_measure_info & roInfo,cnui_measures & roMeasures,SCP<ng_font> & rpoFontSP);

	void _paint(cnui_painter & roPainter,SCP<ng_font> & rpoFontSP,const ng_color & roForeColor);

	void _move_by(const ng_size & roSize);

	void copy_to(const multiline_ & roMultiLine);
protected:
	class cline
	{
	public:
		cline();
		cline(long nFirstChar,long nLastChar,const ng_rect & roLineRect,long nWhiteChars,long nExtraSpace);
		
		long get_first_char() const
		{
			return m_nFirstChar;
		}
		long get_last_char() const
		{
			return m_nLastChar;
		}
		const ng_rect & get_rect() const
		{
			return m_oLineRect;
		}
		void move_by(const ng_size & roSize)
		{
			m_oLineRect.offset(roSize);
		}
	private:
		long	m_nFirstChar;		//pierwszy znak linii
		long	m_nLastChar;		//ostatni znak linii
		ng_rect	m_oLineRect;		//prostok¹t zajmowany przez liniê
		long	m_nWhiteChars;		//liczba spacji w linii (pocz¹tkowe,œrodkowe,koñcowe)
		long	m_nExtraSpace;		//justfication info
	};

	long _linenr_for_pos(long nPos);

	ng_string	m_oTextString;
	ng_ydist	m_yLineHeight;

	CArray<cline,cline&>	m_oLineArray;
	long		m_nInvalidChar;			//first char attected by change.  == MAXLONG  - when all valid

	friend class multiline_reflow_helper;
};


inline multiline_::cline::cline():
	m_nFirstChar(-1),
	m_nLastChar(-1),
	m_nWhiteChars(0),
	m_nExtraSpace(0)
{
}

inline multiline_::cline::cline(long nFirstChar,long nLastChar,const ng_rect & roLineRect,long nWhiteChars,long nExtraSpace):
	m_nFirstChar(nFirstChar),
	m_nLastChar(nLastChar),
	m_oLineRect(roLineRect),
	m_nWhiteChars(nWhiteChars),
	m_nExtraSpace(nExtraSpace)
{
}

#else
	#error __FILE__ already included
#endif
