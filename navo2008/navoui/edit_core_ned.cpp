/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych

	core part
*/

#include "stdafx.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-------------- attribute functions -------------------------
void cned_edit__::set_fixed_properties()
{
	cned_rect_element_::set_fixed_properties();

	set_prop_forecolor(_metrics().edit().get_forecolor());
	set_prop_backcolor(_metrics().edit().get_backcolor());
	set_prop_backcolor2(_metrics().edit().get_backcolor());
	set_prop_border_type(_metrics().edit().get_border_type());
	set_prop_border_color(_metrics().edit().get_forecolor());
}

//---------------------------------------------------------
// dimension information and calculations
//---------------------------------------------------------

ng_size cned_edit__::_compute_min_size(const ned_measure_param & roMParam)
{
	ng_string oTestString('7',get_prop_charwidth());
	
	ng_size oTextSize = roMParam.get_info_dc().measure_string(oTestString,MAXLONG,
		get_manager()->get_font_on_inx(get_prop_fontinx()),NULL);
	
	ng_size oCompleteSize;
	if(roMParam.is_printing())
	{
		oCompleteSize = oTextSize;
	}
	else
	{
		oCompleteSize.set_dx(oTextSize.get_dx() + 2 * _get_frame_px_width() + 
			_metrics().edit().get_left_margin() + _metrics().edit().get_right_margin());
		oCompleteSize.set_dy(oTextSize.get_dy() + 2 * _get_frame_px_width() + 
			_metrics().edit().get_top_margin() + _metrics().edit().get_bottom_margin());
	}
	return oCompleteSize;
}

ng_xdist cned_edit__::_get_frame_px_width() const
{
	if(_metrics().is_windows_look())
	{
		return get_manager()->__zoomize(2);	//NG_FRAME_EDGE_SUNKEN is double
	}
	else
	{
		if(get_prop_border_type() != NED_BORDER_STYLE_NONE)
		{
			return get_manager()->__zoomize(get_prop_border_width());
		}
		else
		{
			return 0;
		}
	}
}


//---------------------------------------------------------

void cned_edit__::set_prop_value(const CSmartOleVariant & roSOV)
{
	CSmartOleVariant oOldSOV;
	get_prop_value(oOldSOV);
	
	if(roSOV == oOldSOV)
	{
		return;
	}

	if(variant2buffer(roSOV))
	{
		_set_infra_update_pending();
		//poniewa¿ samo zaznaczenie infra_update nie powoduje odmalowania
		//mo¿emy czekaæ w nieskoñczonoœæ - musimy wywo³aæ ma³y update

		_invalidate_internal_paint();		
		
		_vse_dirty();
	}
	else
	{
		//ned_to_do:: co wtedy
		//ned_to_do: update i wykrywanie czy siê zmieni³o...
	}
}
