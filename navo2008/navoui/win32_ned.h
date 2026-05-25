/*
	NAVO Enterprise 2003
	2003-04-15

	navo enhanced display (NED)

	cned_win32__ - klasa bazowa dla kontrolek Win32

	
*/

#ifndef _WIN32_NED_H_
#define _WIN32_NED_H_

namespace ned
{

class cned_win32__ : public cned_rect_element_
{
public:
	void arena_move_by(const ng_size & roDistanceSize);

	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
	virtual void render(cned_renderer_ & roRenderer);

	virtual void _init_control() = 0;
	virtual void _reset_control() = 0;
	virtual HWND get_embedded_hwnd() const = 0;
protected:
	cned_win32__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);
	virtual ~cned_win32__();
	virtual ng_size _compute_min_size(const ned_measure_param & roMParam);
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline cned_win32__::cned_win32__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_element_(poManager,eType,idThis)
{
}

inline cned_win32__::~cned_win32__()
{
}

inline ng_size cned_win32__::_compute_min_size(const ned_measure_param & roMParam)
{
	ng_xdist xWidth = 0;
	ng_ydist yHeight = 0;
	if(is_normal_width_value(get_prop_extwidth()))
	{
		xWidth = get_manager()->to_internal(ng_size(get_prop_extwidth(),0)).get_dx();
	}
	else
	{
		xWidth = _metrics()._win32().get_default_width();
	}
	if(is_normal_height_value(get_prop_extheight()))
	{
		yHeight = get_manager()->to_internal(ng_size(0,get_prop_extheight())).get_dy();
	}
	else
	{
		yHeight = _metrics()._win32().get_default_height();
	}

	return ng_size(xWidth,yHeight);
}

inline void cned_win32__::render(cned_renderer_ & roRenderer)
{
	cned_rect_element_::render(roRenderer);
	_init_control();
	HWND hWindow = get_embedded_hwnd();
	if(hWindow != HWND(NULL))
	{
		ng_point oPoint;
		_local2screen(oPoint);
		ng_rect oRect(oPoint,m_oActualSize);
	
		//OS_API_CALL
		::MoveWindow(get_embedded_hwnd(),oRect.get_left(),oRect.get_top(),
			oRect.get_width(),oRect.get_height(),TRUE);
	}
}

inline void cned_win32__::draw_foreground(cned_fore_painter &,const ng_point &)
{
}

inline void cned_win32__::draw_background(cned_back_painter & roBackPainter,const ng_point &  roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_init_control();
	HWND hWindow = get_embedded_hwnd();
	if(hWindow != HWND(NULL))
	{
		//OS_API_CALL
		::InvalidateRect(hWindow,NULL,FALSE);
		::SendMessage(hWindow,WM_PRINTCLIENT,WPARAM(roBackPainter.get_dc().get_hdc()),LPARAM(PRF_CLIENT));
	}

	_store_main_paint_rect(ng_rect(oPaintPoint,m_oActualSize));
}

inline void cned_win32__::arena_move_by(const ng_size & roDistanceSize)
{
	HWND hWindow = get_embedded_hwnd();
	if(hWindow != HWND(NULL))
	{
		//OS_API_CALL
		RECT oWndRect;
		::GetWindowRect(hWindow,&oWndRect);
		POINT oWndPoint = { oWndRect.left, oWndRect.top } ;
		::ScreenToClient(get_manager()->get_os_window(),&oWndPoint);
		oWndPoint.x += roDistanceSize.get_dx();
		oWndPoint.y += roDistanceSize.get_dy();
		::SetWindowPos(hWindow,HWND(NULL),oWndPoint.x,oWndPoint.y,0,0,SWP_NOZORDER | SWP_NOSIZE);
	}
}

}

#else
	#error __FILE__ already included
#endif
