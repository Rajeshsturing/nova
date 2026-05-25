/*
	NAVO Enterprise 2003
	2003-04-25

	navo enhanced display (NED)

	page-breaking classes


*/

#ifndef _PAGE_BREAKER_NED_H_
#define _PAGE_BREAKER_NED_H_

namespace ned
{


class cned_element;

//------------------------------------------------------------------------------
// page_break_params
//------------------------------------------------------------------------------
struct cned_page_break_param
{
	ng_size m_oSheetExtSize;		//'paper sheet' size in external units
	ng_rect m_oSheetExtMargins;		//'paper sheet' margins in external units
	ng_size m_oPrintableSheetPxSize;//'printable paper sheet' size in pixels (less declared device/margins !!)
	ng_size m_oPrintableSheetExtSize;//'printable paper sheet' size in external units
};

//------------------------------------------------------------------------------
// oblicza w rozmiar kartki i marginesów external units, uwgzlêdniaj¹c ograniczenia
// drukarki (urz¹dzenia(
// zwraca tak¿e rozmiar w pixelach
//------------------------------------------------------------------------------
void win32_compute_page_sizes(HDC hdcDevice,
	/*out*/ng_size & roSheetExtSize,/*in-out*/ng_rect & roSheetExtMargins,
	/*out*/ng_size & roSheetPrintablePxSize,
	/*out*/ng_size & roSheetPrintableExtSize);
							  
//------------------------------------------------------------------------------
// virtual base class for page-breaking
//------------------------------------------------------------------------------
class cpb_manager__
{
public:
	virtual void get_areas_for_rect(const ng_rect & roElementRect,ng_rect & roAreaRange) = 0;
	virtual SCP<cned_element> get_clone(long nAreaX,long nAreaY,cned_element * poSrcElement,bool & rbJustCreated) = 0;
	virtual void store_ident_mapping(long nAreaX,long nAreaY,ned_ident idOrig,ned_ident idClone) = 0;

	virtual ng_size get_avail_size(const ng_point & roPoint) = 0;

	virtual void notify_on_cloned_element(ned_ident idOrig,long nAreaX,long nAreaY,SCP<cned_element> poCloneSP) = 0;
};

//---------------------------------------------------------------------
class cpb_split_info_storage
{
public:
	cpb_split_info_storage();
	
	void add_vert_split(ng_ycoord yPosition);
	void add_horiz_split(ng_xcoord xPosition);

	long find_y_area(ng_ycoord yPosition) const;
	ng_ycoord get_y_area_top(long yAreaY) const;

	long find_x_area(ng_xcoord xPosition) const;
	ng_xcoord get_x_area_right(long xAreaX) const;

	//rozmiar (ilosc stron) w ka¿dym wymiarze
	long get_y_count() const;
	long get_x_count() const;
private:
	//--------------
	//m_oVerticalSplitArray <-- pamiêtany jest bottom prostokata (ostatni pixel objety tym obszarem)
	
	CArray<ng_ycoord,ng_ycoord> m_oVerticalSplitArray;
	CArray<ng_xcoord,ng_xcoord> m_oHorizontalSplitArray;
};

//---------------------------------------------------------------------

class cpb_split_info
{
public:
	cpb_split_info(cpb_split_info_storage & roStorage,
		ng_ydist dyParentOffset,ng_ycoord yFirstPartMaxBottom,ng_ydist dyNextPartMaxHeight,
		ng_xdist dxNextPartMaxWidth);
	void next_y_page();

	ng_ycoord get_max_bottom() const;
	ng_ycoord get_actual_bottom() const;
	ng_ydist get_next_part_max_height() const;
	ng_xdist get_next_part_max_width() const;

	void update_actual_bottom(ng_ycoord yNewActualBottom);
	void update_max_right(ng_xcoord xNewMaxRight);

	cpb_split_info_storage & get_storage();

	void propagate(ng_ycoord yActualBottom,ng_ycoord yMaxBottom);
private:
	ng_ycoord m_yActualBottom;
	ng_ycoord m_yMaxBottom;

	ng_xdist m_dxNextPartMaxWidth;
	ng_ydist m_dyNextPartMaxHeight;

	ng_ydist m_dyParentOffset;
	
	cpb_split_info_storage & m_roStorage;
};


struct cpb_on_split_event_param
{
	ng_string			m_oFunctionNameString;
	SCP<cned_element>	m_poClonedElementSP;
	long				m_xAreaX;
	long				m_yAreaY;
	long				m_xCount;
	long				m_yCount;
	void operator =(const cpb_on_split_event_param & roRightParam);
};


class cpb_split_manager
{
public:
	virtual long find_y_area(ng_ycoord yPosition);

	ng_ycoord get_y_area_top(long yAreaY) const;
	ng_xcoord get_x_area_right(long xAreaX) const;

	long find_x_area(ng_xcoord xPosition);
	virtual SCP<cned_element> get_clone(long xAreaX,long yAreaY,ned_ident idElement) = 0;
	virtual void register_clone(long xAreaX,long yAreaY,
		ned_ident idOriginalElement,ned_ident idClonedElement) = 0;

	cpb_split_info_storage & get_storage();

	virtual void add_event_param(const cpb_on_split_event_param & roEventParam) = 0;
protected:
	cpb_split_manager(cpb_split_info_storage & roStorage);

	cpb_split_info_storage & m_roStorage;
};

bool _fire_on_split_event_function(cned_window * poWindow,const cpb_on_split_event_param & roEventParam);

}

#else
	#error __FILE__ already included
#endif
