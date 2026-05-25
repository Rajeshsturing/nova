/*
	NAVO Enterprise 2008
	2003-02-22
	
	ned_metrics

	klasa grupuj¹ca informacje o wymiarowaniu, opcjach wyœwietlania itd.
*/

#ifndef _METRICS_NED_H_
#define _METRICS_NED_H_

namespace ned
{

enum ened_border_style;

class ned_metrics
{
public:
	ned_metrics();

	//--------- display variants (styles) ---------------------
	void set_windows_look(bool bWL)
	{
		m_bWindowsLook = bWL;
	}
	
	bool is_windows_look() const
	{
		return m_bWindowsLook;
	}


	bool is_high_contrast() const; ///high contrast for enhanced visual experience
	
	//--------- various elements' dimensions and settings ------------------
	class _arena
	{
	public:
		_arena(){}
	
		ng_color get_backcolor() const
		{
			return ng_color(RGB(0xAB,0xBE,0xE6));
		}
		ng_color get_backcolor2() const
		{
			return ng_color(RGB(0xAB,0xBE,0xE6));
		}
		ng_xdist get_default_pos_x_increment() const
		{
			return 20;
		}
		ng_ydist get_default_pos_y_increment() const
		{
			return 20;
		}
	};


	//static
	class _text
	{
	public:
		_text(ned_metrics & rometrics);
		ng_color get_highlight_color() const
		{
			return ng_color(0,0,255,0);
		}
		ng_color get_highlight_frame_color() const
		{
			return ng_color(0,0,238,0);
		}
		ng_xdist get_horiz_tabheader_margin() const
		{
			return 2;
		}
		ng_ydist get_vert_tabheader_margin() const
		{
			return 2;
		}
	protected:
		ned_metrics & m_rometrics;
	};
	class _button : public _text
	{
	public:
		_button(ned_metrics & rometrics);
		ng_xdist get_left_margin() const
		{
			return 3;
		}
		ng_xdist get_right_margin() const
		{
			return 3;
		}
		ng_ydist get_top_margin() const
		{
			return 3;
		}
		ng_ydist get_bottom_margin() const
		{
			return 3;
		}
		ng_color get_border_color() const
		{
			return ng_color(0,0,160,0);
		}
	};
	class _picture
	{
	public:
		_picture(ned_metrics & rometrics);
		ng_xdist get_default_width() const
		{
			return 16 * 2540 / 96; //16 = arbitrarty pixel size; 2540 - ext unit / inch; 96 - assumed picture resolution (dpi)
		}
		ng_ydist get_default_height() const
		{
			return 16 * 2540 / 96;
		}
		ng_xdist get_left_margin() const
		{
			return 3;
		}
		ng_xdist get_right_margin() const
		{
			return 3;
		}
		ng_ydist get_top_margin() const
		{
			return 3;
		}
		ng_ydist get_bottom_margin() const
		{
			return 3;
		}
	private:
		ned_metrics & m_rometrics;
	};
	//edit (common)
	class _edit
	{
	public:
		_edit(ned_metrics & rometrics);

		ng_xdist get_left_margin() const
		{
			return 2;
		}
		ng_xdist get_right_margin() const
		{
			return 2;
		}
		ng_ydist get_top_margin() const
		{
			return 1;
		}
		ng_ydist get_bottom_margin() const
		{
			return 1;
		}
		ng_color get_forecolor() const
		{
			return Black;
		}
		ng_color get_backcolor() const
		{
			return White;
		}
		ng_color get_invalid_data_color() const
		{
			return m_clrInvalidData;
		}
		ened_border_style get_border_type() const;
	protected:
		const ng_color  m_clrInvalidData;
		ned_metrics & m_rometrics;
	};
	//date edit
	class _dateedit : public _edit
	{
	public:
		_dateedit(ned_metrics & rometrics);

		LPCTSTR get_format() const
		{
			return m_cDateFormat;
		}
		long get_format_len() const
		{
			return m_nDateFormatLen;
		}
		TCHAR get_separator() const
		{
			return m_cDateSep;
		}
		LPCTSTR get_null_text() const
		{
			//ta dziwna sta³a znakowa aby kompilator nie wzi¹³ tego za trigraph
			return "????" "-??" "-??";
		}
	private:
		TCHAR	m_cDateFormat[100];
		long	m_nDateFormatLen;
		TCHAR	m_cDateSep;
	};
	//time edit
	class _timeedit : public _edit
	{
	public:
		_timeedit(ned_metrics & rometrics);
		long get_format_len() const
		{
			return m_nTimeFormatLen;
		}
		const TCHAR get_separator() const
		{
			return m_cTimeSep;
		}
		LPCTSTR get_null_text() const
		{
			return "??:??";
		}
	private:
		long	m_nTimeFormatLen;
		TCHAR	m_cTimeSep;
	};
	class _currency
	{
	public:
		_currency();

		TCHAR get_decimal_separator() const
		{
			return m_cDecimalSeparator;
		}
		TCHAR get_thousand_separator() const
		{
			return m_cThousandSeparator;
		}
	private:
		TCHAR	  m_cDecimalSeparator;
		TCHAR	  m_cThousandSeparator;
	};
	//option button (checkbox / radio)
	class _optionbtn
	{
	public:
		_optionbtn(ned_metrics & rometrics) :
			m_rometrics(rometrics)
		{
		}
		ng_xdist get_img2item_distance() const	//odleg³oœæ miêdzy obrazkiem a itemem
		{
			return 2;
		}
		ng_xdist get_col_distance() const		//odleg³oœæ miêdzy kolumnami
		{
			return 6;
		}
		ng_ydist get_row_distance() const
		{
			return 2;
		}

		ng_xdist get_left_margin(ened_border_style eStyle) const
		{
			return (NED_BORDER_STYLE_NONE == eStyle) ? 2 : 5;
		}
		ng_xdist get_right_margin(ened_border_style eStyle) const
		{
			return (NED_BORDER_STYLE_NONE == eStyle) ? 2 : 6;
		}
		ng_ydist get_top_margin(ened_border_style eStyle) const
		{
			return (NED_BORDER_STYLE_NONE == eStyle) ? 2 : 5;
		}
		ng_ydist get_bottom_margin(ened_border_style eStyle) const
		{
			return (NED_BORDER_STYLE_NONE == eStyle) ? 2 : 4;
		}
		ng_xdist get_image_width() const
		{
			return 14;
		}
		ng_ydist get_image_height() const
		{
			return 14;
		}
	protected:
		ned_metrics & m_rometrics;
	};
	//table cell
	class _tablecell
	{
	public:
		_tablecell(ned_metrics & rometrics) :
			m_rometrics(rometrics)
		{
		}
		//table cell
		ng_xdist get_padding_width() const
		{
			return 1;
		}
		ng_ydist get_padding_height() const
		{
			return 1;
		}
	protected:
		ned_metrics & m_rometrics;
	};
	
	//win32 controls
	class _win32_
	{
	public:
		_win32_(ned_metrics & rometrics) :
			m_rometrics(rometrics)
		{
		}
		ng_xdist get_default_width() const
		{
			return 50;	
		}
		ng_ydist get_default_height() const
		{
			return 50;
		}
	protected:
		ned_metrics & m_rometrics;
	};

	//multiline edit
	class _multiedit
	{
	public:
		_multiedit(ned_metrics & rometrics) :
			m_rometrics(rometrics)
		{
		}
		ng_xdist get_default_width() const
		{
			return 300;	
		}
		ng_ydist get_default_height() const
		{
			return 100;
		}
	protected:
		ned_metrics & m_rometrics;
	};

	class _page
	{
	public:
		_page(ned_metrics & rometrics) :
			m_rometrics(rometrics)
		{
		}
		ng_xdist get_shadow_width() const
		{
			return 8;	
		}
		ng_ydist get_shadow_height() const
		{
			return 8;
		}
		ng_color get_shadow_color() const
		{
			return ng_color(144,144,144,160);
		}
		ng_xdist get_iconic_width() const
		{
			return 64;	
		}
		ng_ydist get_iconic_height() const
		{
			return 20;	
		}
		ng_xdist get_border_width() const
		{
			return 2;
		}
		ng_ydist get_border_height() const
		{
			return 2;
		}

	protected:
		ned_metrics & m_rometrics;
	};
	
	//page 

	//tool tip
	ng_color get_tooltip_backcolor() const
	{
		return ng_color(255,255,232,0);
	}
	//general drag
	const ng_size & get_void_drag_size() const
	{
		return m_oVoidDragSize;
	}
	const _text & text() const
	{
		return m_text;
	}
	const _button & button() const
	{
		return m_button;
	}
	const _picture & picture() const
	{
		return m_picture;
	}
	const _edit	& edit() const
	{
		return m_edit;
	}
	const _dateedit & dateedit() const
	{
		return m_dateedit;
	}
	const _timeedit & timeedit() const
	{
		return m_timeedit;
	}
	const _currency	& currency() const
	{
		return m_currency;
	}
	const _optionbtn & optionbtn() const
	{
		return m_optionbtn;
	}
	const _tablecell & tablecell() const
	{
		return m_tablecell;
	}
	const _win32_ & _win32() const
	{
		return m_win32_;
	}
	const _multiedit & multiedit() const
	{
		return m_multitedit;
	}
	const _page & page() const
	{
		return m_page;
	}

	const _arena & arena() const
	{
		return m_arena;
	}

	//convertions


private:
	bool	m_bWindowsLook;			//wizualizacja podobna do Windows
	bool    m_bHighContrast;

	ng_size	  m_oVoidDragSize;

	_arena		m_arena;
	_text		m_text;
	_button		m_button;
	_picture	m_picture;
	_edit		m_edit;
	_dateedit	m_dateedit;
	_timeedit	m_timeedit;
	_currency	m_currency;
	_optionbtn  m_optionbtn;
	_tablecell	m_tablecell;
	_win32_		m_win32_;
	_multiedit	m_multitedit;
	_page		m_page;

	friend class _page;
};

ned_metrics & _metrics();

inline bool ned_metrics::is_high_contrast() const
{
	return m_bHighContrast;
}

}

#else
	#error __FILE__ already included
#endif
