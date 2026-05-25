/*
	NAVO Enterprise 2003
	2003-04-30

	navo enterprise printing support NEPS
		
*/

#ifndef _CORE_NEPS_H_
#define _CORE_NEPS_H_

namespace neps				//neps - OS independent part
{
	class cneps_printer_config
	{
	public:
		enum eOrientation
		{
			orient_default = 0,		//use printer default settings
			orient_portrait,
			orient_landscape
		};

		enum eQuality
		{
			quality_default = 0,
			quality_high,
			quality_medium,
			quality_low,
			quality_draft,
		};
		enum eColorMode
		{
			colormode_default = 0,
			colormode_color,
			colormode_mono
		};

		cneps_printer_config();
		cneps_printer_config(const cneps_printer_config & roPrinterConfig);

		//--------------------------------------------------------------------
		// get
		//--------------------------------------------------------------------
		eOrientation get_orientation() const;
		eQuality get_quality() const;

		long get_paper_size() const;

		long get_extlength() const;
		long get_extwidth() const;
		long get_copies() const;

		bool get_print_background() const;
		bool get_mono_grayscale() const;

		eColorMode get_color_mode() const;

		void get_as_string(CString & roResultString);
		//--------------------------------------------------------------------
		// put
		//
		// commonly used subset
		//--------------------------------------------------------------------
		void landscape();
		void portrait();
		void draft();
		void normal();
		void high();
		void set_orientation(eOrientation eOrient);
		void set_quality(eQuality eQty);
		void set_copies(long nCopies);
		void set_paper_size(long nPaperSizeEnum);

		void sheet_dimensions(long nExtWidth,long nExtHeight);
		void set_color_mode(eColorMode eCM);
		
		void set_print_background(bool bPrint);
		void set_mono_grayscale(bool bGrayScale);

		void set_from_string(LPCTSTR lpString);

	private:
		eOrientation m_eOrientation;
		long		 m_DMPaperSize;		// -1 - default, DMPAPER_USER - user defined
		long		 m_nExtLength;		// in navo external units 1cm = 1000
		long		 m_nExtWidth;		// in navo external units 1cm = 1000
		long		 m_nCopies;			// numer of copies if supported
		eQuality	 m_eQuality;
		eColorMode	 m_eColorMode;
		bool		 m_bPrintBackground;
		bool		 m_bMonoGrayScale;
	};
};

namespace neps_win32		//neps - Win32 dependent part
{

//----------------------------------------------------------------
//get all available printer names
//----------------------------------------------------------------
bool win32_get_printers_names(CArray<CString,CString> & roNameArray);

//----------------------------------------------------------------
//get default printer name
//----------------------------------------------------------------
bool win32_get_default_printer_name(CString & roNameString);

//----------------------------------------------------------------
// returns a DEVMODE and DEVNAMES for the printer name specified
// caller have to ::globalfree HGLOBALs
//----------------------------------------------------------------
bool win32_get_printer_dev_xxx(LPCTSTR lpPrinterName,HGLOBAL & rhDevNames,HGLOBAL & rhDevMode);

//----------------------------------------------------------------
// create printer DC on hDevNames and hDevMode
//----------------------------------------------------------------
HDC win32_create_printer_dc(HGLOBAL hDevNames,HGLOBAL hDevMode);

//----------------------------------------------------------------
// provide hDevMode according specified settings
// caller have to ::globalfree HGLOBAL
//----------------------------------------------------------------
bool win32_configure_devmode(LPCTSTR lpPrinterName,HWND hParentWindow,const neps::cneps_printer_config & roConfig,HGLOBAL & rhDevMode);

//----------------------------------------------------------------
//fill cneps_printer_config on DEVMODE
//----------------------------------------------------------------
void win32_init_on_devmode(HGLOBAL hDevMode,neps::cneps_printer_config & roConfig);

}

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
namespace neps				//neps - OS independent part
{
	
inline cneps_printer_config::cneps_printer_config() :
	m_eOrientation(orient_default),
	m_DMPaperSize(-1/*use default*/),
	m_nExtLength(0),
	m_nExtWidth(0),
	m_nCopies(1),
	m_eQuality(quality_default),
	m_eColorMode(colormode_default),
	m_bPrintBackground(false),
	m_bMonoGrayScale(false)
{
}
		
inline cneps_printer_config::cneps_printer_config(const cneps_printer_config & roPrinterConfig) :
	m_eOrientation(roPrinterConfig.m_eOrientation),
	m_DMPaperSize(roPrinterConfig.m_DMPaperSize),
	m_nExtLength(roPrinterConfig.m_nExtLength),
	m_nExtWidth(roPrinterConfig.m_nExtWidth),
	m_nCopies(roPrinterConfig.m_nCopies),
	m_eQuality(roPrinterConfig.m_eQuality),
	m_eColorMode(roPrinterConfig.m_eColorMode),
	m_bPrintBackground(roPrinterConfig.m_bPrintBackground),
	m_bMonoGrayScale(roPrinterConfig.m_bMonoGrayScale)
{
}
//--------------------------------------------------------------------
// get
//--------------------------------------------------------------------
inline cneps_printer_config::eOrientation cneps_printer_config::get_orientation() const
{
	return m_eOrientation;
}

inline long cneps_printer_config::get_paper_size() const
{
	return m_DMPaperSize;
}

inline long cneps_printer_config::get_extlength() const
{
	return m_nExtLength;
}

inline long cneps_printer_config::get_extwidth() const
{
	return m_nExtWidth;
}

inline long cneps_printer_config::get_copies() const
{
	return m_nCopies;
}

inline cneps_printer_config::eQuality cneps_printer_config::get_quality() const
{
	return m_eQuality;
}

inline cneps_printer_config::eColorMode cneps_printer_config::get_color_mode() const
{
	return m_eColorMode;
}

inline bool cneps_printer_config::get_print_background() const
{
	return m_bPrintBackground;
}

inline bool cneps_printer_config::get_mono_grayscale() const
{
	return m_bMonoGrayScale;
}

//--------------------------------------------------------------------
// put
//--------------------------------------------------------------------
inline void cneps_printer_config::set_orientation(eOrientation eOrient)
{
	m_eOrientation = eOrient;
}

inline void cneps_printer_config::set_quality(eQuality eQty)
{
	m_eQuality = eQty;
}

inline void cneps_printer_config::set_copies(long nCopies)
{
	m_nCopies = nCopies;
}

inline void cneps_printer_config::set_paper_size(long nPaperSizeEnum)
{
	m_DMPaperSize = nPaperSizeEnum;
}

inline void cneps_printer_config::landscape()
{
	set_orientation(orient_landscape);
}

inline void cneps_printer_config::portrait()
{
	set_orientation(orient_portrait);
}

inline void cneps_printer_config::draft()
{
	set_quality(quality_draft);
}

inline void cneps_printer_config::high()
{
	set_quality(quality_high);
}

inline void cneps_printer_config::normal()
{
	set_quality(quality_medium);
}

inline void cneps_printer_config::sheet_dimensions(long nExtWidth,long nExtHeight)
{
	m_DMPaperSize = DMPAPER_USER;
	m_nExtLength = nExtHeight;
	m_nExtWidth = nExtWidth;
}

inline void cneps_printer_config::set_color_mode(eColorMode eCM)
{
	m_eColorMode = eCM;
}

inline void cneps_printer_config::set_print_background(bool bPrint)
{
	m_bPrintBackground = bPrint;
}

inline void cneps_printer_config::set_mono_grayscale(bool bGrayScale)
{
	m_bMonoGrayScale = bGrayScale;
}

}

using namespace neps;
using namespace neps_win32;

#else
	#error __FILE__ already included
#endif

