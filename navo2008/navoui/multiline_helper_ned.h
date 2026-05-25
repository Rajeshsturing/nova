/*
	NAVO Enterprise 2003
	2003-04-07

	navo enhanced display (NED)

	helper dla multiline
	
*/

#ifndef _MULTILINE_HELPER_NED_H_
#define _MULTILINE_HELPER_NED_H_

namespace ned
{

class multiline_manager
{
public:
	multiline_manager();

	const long get_line_count() const;
	void reset_line_count(long nLineCount);
	void add(long nFirstChar,long nLastChar,const ng_size & roSize,const ng_size & roVector,ng_xdist dxExtraWidth,long nBreakChars);
	bool get(long nLineNr,long & rnFirstChar,long & rnLastChar,ng_size & roSize,ng_size & roVector,ng_xdist & rdxExtraWidth,long & rnBreakChars) const;
	bool get(long nLineNr,ng_size & roSize,ng_size & roVector) const;
	bool get(long nLineNr,long & rnFirstChar,long & rnLastChar) const;
	void move_by(long nLineNr,const ng_size & roDistanceSize);
private:
	class line_info
	{
	public:
		line_info();
		line_info(long nFirstChar,long nLastChar,const ng_size & roSize,const ng_size & roVector,ng_xdist dxExtraWidth,long nBreakChars);
		const long get_first_char() const;
		const long get_last_char() const;
		const ng_size & get_size() const;
		const ng_size & get_vector() const;
		const ng_xdist get_extra_width() const;
		const long get_breakchar_count() const;
		void move_by(const ng_size & roDistanceSize);
	private:
		long	m_nFirstChar;
		long	m_nLastChar;
		ng_size m_oLineSize;
		ng_size m_oLineVector;
		ng_xdist m_dxExtraWidth;
		long	m_nBreakChars;
	};

	CArray<line_info,const line_info &> m_oLineArray;
};

//-------------------------------------------------------------------------------------------------
// multiline_text_parser -
// parsuje podany tekst na fragmenty:
// W (word) - zwraca pocz¹tek i koniec s³owa (numer znaku w tekscie)
// S (space) - pocz¹tek i koniec to ten znak
// N (newline) - pocz¹tek i koniec to ten znak
// E (end of text = null) - pocz¹tek i koniec to ten znak
//-------------------------------------------------------------------------------------------------

class multiline_text_parser
{
public:
	multiline_text_parser(LPCTSTR lpText,long nStartingChar);
	TCHAR get_next_item(long & rnFirstChar,long & rnLastChar);
private:
	LPCTSTR m_lpText;
	long m_nCurrChar;
};

//-------------------------------------------------------------------------------------------------
//	multiline_measurer -
//	dostarcza informacji o rozmiarach stringa i dowolnego jego podci¹gu
//-------------------------------------------------------------------------------------------------
class multiline_measurer
{
public:
	multiline_measurer(ng_dc & roDC,SCP<ng_font> & rpoFontSP,LPCTSTR lpText,long nCount);
	long _get_part_len(long nFirstChar,long nLastChar) const;
	ng_ydist get_line_height() const;
	LPCTSTR get_text() const;
	long get_count() const;
private:
	LPCTSTR				m_lpText;
	long				m_nCount;
	CArray<int,int>		m_oPartialLengthArray;
	ng_ydist			m_yLineHeight;
};

//--------------------------------------------------------------------
// rendering_line
// helper object which holds info on just rendered line
//--------------------------------------------------------------------
class rendering_line
{
public:
	rendering_line();
	void done();
	void init_new(long nBegin);
	
	void extend(long nNewEnd);
	void shrink();

	bool is_empty() const;
	long get_begin() const;
	long get_end() const;
	long get_breakchar_count() const;

	void add_breakchar();
	void del_breakchar();
private:
	bool _is_valid() const;

	long	m_nBegin;
	long	m_nEnd;
	long	m_nBreakChars;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline multiline_manager::multiline_manager()
{
}

inline void multiline_manager::reset_line_count(long nLineCount)
{
	ASSERT(nLineCount >= 0 && nLineCount <= get_line_count());
	m_oLineArray.SetSize(nLineCount);
}

inline const long multiline_manager::get_line_count() const
{
	return m_oLineArray.GetSize();
}

inline void multiline_manager::add(long nFirstChar,long nLastChar,const ng_size & roSize,
	const ng_size & roVector,ng_xdist dxExtraWidth,long nBreakChars)
{
	m_oLineArray.Add(line_info(nFirstChar,nLastChar,roSize,roVector,dxExtraWidth,nBreakChars));
}

inline bool multiline_manager::get(long nLineNr,long & rnFirstChar,long & rnLastChar,ng_size & roSize,
								   ng_size & roVector,ng_xdist & rdxExtraWidth,long & rnBreakChars) const
{
	if(nLineNr >= m_oLineArray.GetSize())
	{
		return false;
	}
	const line_info & roLineInfo = m_oLineArray[ nLineNr ];
	
	rnFirstChar		= roLineInfo.get_first_char();
	rnLastChar		= roLineInfo.get_last_char();
	roSize			= roLineInfo.get_size();
	roVector		= roLineInfo.get_vector();
	rdxExtraWidth	= roLineInfo.get_extra_width();
	rnBreakChars	= roLineInfo.get_breakchar_count();
	return true;
}

inline bool multiline_manager::get(long nLineNr,ng_size & roSize,ng_size & roVector) const
{
	if(nLineNr >= m_oLineArray.GetSize())
	{
		return false;
	}
	const line_info & roLineInfo = m_oLineArray[ nLineNr ];
	
	roSize			= roLineInfo.get_size();
	roVector		= roLineInfo.get_vector();
	return true;
}

inline bool multiline_manager::get(long nLineNr,long & rnFirstChar,long & rnLastChar) const
{
	if(nLineNr >= m_oLineArray.GetSize())
	{
		return false;
	}
	const line_info & roLineInfo = m_oLineArray[ nLineNr ];

	rnFirstChar		= roLineInfo.get_first_char();
	rnLastChar		= roLineInfo.get_last_char();
	return true;
}

inline void multiline_manager::move_by(long nLineNr,const ng_size & roDistanceSize)
{
	line_info & roLineInfo = m_oLineArray[ nLineNr ];
	roLineInfo.move_by(roDistanceSize);
}

//--------------------------------------------------------------------
// line_info
//--------------------------------------------------------------------
inline multiline_manager::line_info::line_info():
	m_nFirstChar(0),
	m_nLastChar(-1),
	m_dxExtraWidth(0),
	m_nBreakChars(0)
{
}

inline multiline_manager::line_info::line_info(long nFirstChar,long nLastChar,const ng_size & roSize,
	const ng_size & roVector,ng_xdist dxExtraWidth,long nBreakChars) :
	m_nFirstChar(nFirstChar),
	m_nLastChar(nLastChar),
	m_oLineSize(roSize),
	m_oLineVector(roVector),
	m_dxExtraWidth(dxExtraWidth),
	m_nBreakChars(nBreakChars)
{
}

inline const long multiline_manager::line_info::get_first_char() const
{
	return m_nFirstChar;
}

inline const long multiline_manager::line_info::get_last_char() const
{
	return m_nLastChar;
}

inline const ng_size & multiline_manager::line_info::get_size() const
{
	return m_oLineSize;
}

inline const ng_size & multiline_manager::line_info::get_vector() const
{
	return m_oLineVector;
}

inline const ng_xdist multiline_manager::line_info::get_extra_width() const
{
	return m_dxExtraWidth;
}

inline const long multiline_manager::line_info::get_breakchar_count() const
{
	return m_nBreakChars;
}

inline void multiline_manager::line_info::move_by(const ng_size & roDistanceSize)
{
	m_oLineVector = m_oLineVector + roDistanceSize;
}

//-------------------------------------------------------------------------------------------------
// multiline_text_parser -
// parsuje podany tekst na fragmenty:
//-------------------------------------------------------------------------------------------------
inline multiline_text_parser::multiline_text_parser(LPCTSTR lpText,long nStartingChar) :
	m_nCurrChar(nStartingChar),
	m_lpText(lpText)
{
}

inline TCHAR multiline_text_parser::get_next_item(long & rnFirstChar,long & rnLastChar)
{
	ASSERT(m_lpText);
	rnFirstChar = m_nCurrChar;
	TCHAR cFirst = m_lpText[m_nCurrChar];
	switch(cFirst)
	{
	case ' ':
		rnLastChar  = m_nCurrChar++;
	break;
	case MULTILINE_NEWLINE_CHAR:
		rnLastChar  = m_nCurrChar++;
	break;
	case '\0':
		rnLastChar  = m_nCurrChar;
	break;
	default:
		while(m_lpText[m_nCurrChar+1] != ' ' && 
			  m_lpText[m_nCurrChar+1] != MULTILINE_NEWLINE_CHAR && 
			  m_lpText[m_nCurrChar+1] != '\0')
		{
			m_nCurrChar++;
		}
		rnLastChar  = m_nCurrChar++;
	}
	return cFirst;
}
//-------------------------------------------------------------------------------------------------
//	multiline_measurer -
//-------------------------------------------------------------------------------------------------
inline multiline_measurer::multiline_measurer(
	ng_dc & roDC,SCP<ng_font> & rpoFontSP,LPCTSTR lpText,long nCount) :
	m_lpText(lpText),
	m_nCount(nCount)
{

	m_oPartialLengthArray.SetSize(nCount + 1);
	m_yLineHeight = roDC.measure_string(lpText,nCount,MAXLONG,rpoFontSP,NULL,
		m_oPartialLengthArray.GetData()).get_dy();
}

inline ng_ydist multiline_measurer::get_line_height() const
{
	return m_yLineHeight;
}

inline LPCTSTR multiline_measurer::get_text() const
{
	return m_lpText;
}

inline long multiline_measurer::get_count() const
{
	return m_nCount;
}

inline long multiline_measurer::_get_part_len(long nFirstChar,long nLastChar) const
{
	ASSERT(nLastChar >= -1);
	ASSERT(nFirstChar >= 0);
	ASSERT(nLastChar < m_oPartialLengthArray.GetSize());
	ASSERT(nLastChar >= nFirstChar - 1);

	//+1 bo zerowy element wskazuje na szerokoœæ bez tego znaku (czyli 0)
	return m_oPartialLengthArray[nLastChar+1] - m_oPartialLengthArray[nFirstChar];
}

//--------------------------------------------------------------------
// rendering_line
//--------------------------------------------------------------------
inline rendering_line::rendering_line()
{
	done();
}

inline void rendering_line::done()
{
	m_nBegin = -1;
	m_nEnd   = -2;
	m_nBreakChars = 0;
	ASSERT(_is_valid());
}

inline void rendering_line::init_new(long nBegin)
{
	ASSERT(nBegin >= 0);

	m_nBegin = nBegin;
	m_nEnd = nBegin - 1;
	m_nBreakChars = 0;

	ASSERT(_is_valid());
	ASSERT(is_empty());
}
	
inline void rendering_line::extend(long nNewEnd)
{
	ASSERT(_is_valid());
	ASSERT(m_nBegin != -1);		//musi byæ zainicjowana
	ASSERT(nNewEnd > m_nEnd);	//wolno rozszerzaæ
	m_nEnd = nNewEnd;
	ASSERT(_is_valid());
}

inline void rendering_line::shrink()
{
	ASSERT(_is_valid());
	m_nEnd--;
	ASSERT(_is_valid());
}

inline bool rendering_line::is_empty() const
{
	ASSERT(_is_valid());
	return (m_nEnd == m_nBegin - 1);
}

inline long rendering_line::get_begin() const
{
	ASSERT(_is_valid());
	return m_nBegin;
}

inline long rendering_line::get_end() const
{
	ASSERT(_is_valid());
	return m_nEnd;
}

inline long rendering_line::get_breakchar_count() const
{
	return m_nBreakChars;
}

inline void rendering_line::add_breakchar()
{
	m_nBreakChars++;
}

inline void rendering_line::del_breakchar()
{
	m_nBreakChars--;
	ASSERT(m_nBreakChars >= 0);
}

#ifdef _DEBUG
inline bool rendering_line::_is_valid() const
{
	return (m_nEnd >= m_nBegin - 1);
}

#else
inline bool rendering_line::_is_valid() const
{
	return true;
}

#endif

}

#else
	#error __FILE__ already included
#endif

