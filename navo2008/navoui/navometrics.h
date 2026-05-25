/*
	NAVO Sp. z o.o. (2002)
	
	NAVO Enterprise

	graphical metrics

	"nvmetr_" for NAVO metrics
*/

#ifndef _NAVO_METRICS_H_
#define _NAVO_METRICS_H_

#define STANDARD_SPACE_96		53			//2 pixele na 96 dpi

long _get_raw_scaling_factor();

inline long nvmetr_focus_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 200 / _get_raw_scaling_factor();
}

inline long nvmetr_optbut_upperspace()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return STANDARD_SPACE_96 / _get_raw_scaling_factor();
}

inline long nvmetr_optbut_buttextspace()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 100 / _get_raw_scaling_factor();
}

inline long nvmetr_optbut_leftspace()
{
	return nvmetr_optbut_buttextspace();
}

inline long nvmetr_optbut_rightspace()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 200 / _get_raw_scaling_factor();
}

inline long nvmetr_optbut_lowerspace()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return STANDARD_SPACE_96 / _get_raw_scaling_factor();
}

inline long nvmetr_sysradio_size()
{
	return 13; //pixels
}

inline long nvmetr_shadow_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 159 / _get_raw_scaling_factor();
}

inline long nvmetr_shadow_height()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 200 / _get_raw_scaling_factor();
}

inline long nvmetr_default_winelement_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 5000 / _get_raw_scaling_factor();
}

inline long nvmetr_default_winelement_height()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 5000 / _get_raw_scaling_factor();
}

inline long nvmetr_default_richedit_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 5000 / _get_raw_scaling_factor();
}

inline long nvmetr_default_richedit_height()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 3000 / _get_raw_scaling_factor();
}

inline long nvmetr_default_oledoc_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 15000 / _get_raw_scaling_factor();
}

inline long nvmetr_default_oledoc_height()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 15000 / _get_raw_scaling_factor();
}


inline long nvmetr_table_cell_margin_width()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return STANDARD_SPACE_96 / _get_raw_scaling_factor();
}

inline long nvmetr_spread_cell_margin_width()
{
	extern long _g_raw_SpreadCellMarginWidth;
	return _g_raw_SpreadCellMarginWidth;
}

void nvmetr_adjust_spread_cell_margin_width(CNGC & roNGC);


inline long nvmetr_default_noimage_size()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 1000 / _get_raw_scaling_factor();
}

inline long nvmetr_nicefontscale()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 8000 / _get_raw_scaling_factor();
}

inline long nvmetr_convert_dimension(long nExternalDimension)
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return nExternalDimension / _get_raw_scaling_factor();
}

inline long nvmetr_unconvert_dimension(long nInternalDimension)
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return nInternalDimension * _get_raw_scaling_factor();
}

//for use outside of this .DLL
long nvmetr_convert_dimension_ext(long nExternalDimension);

inline long nvmetr_void_mouse_area()
{
	ASSERT(_get_raw_scaling_factor() != 0);
	return 200 / _get_raw_scaling_factor();
}

#else
	#error __FILE__ already included
#endif
