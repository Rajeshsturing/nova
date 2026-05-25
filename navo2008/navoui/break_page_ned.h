/*
	NAVO Enterprise 2003
	2003-04-14

	navo enhanced display (NED)

	ned_breakpage / <ff>

	z³amanie strony

*/

#ifndef _BREAK_PAGE_NED_H_
#define _BREAK_PAGE_NED_H_

namespace ned
{

class cned_break_page : public cned_element
{
	virtual void get_metrics(const ned_measure_param &,cned_metrics &);
	virtual void _invalidate_all_paint() {}
	virtual ened_spr should_paint(const cned_painter_ &,const ng_point &) const;
	void draw_foreground(cned_fore_painter &,const ng_point &){}
	void draw_background(cned_back_painter &,const ng_point &){}
	void post_render(cned_post_render_manager &,const ng_point &){}
	void render(cned_renderer_ & roRenderer);
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
	virtual void get_bounding_rect(long nElementPart,ng_rect & roLocalRect) const;

	//-------- page breaking ---------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
private:
	cned_break_page(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_break_page::cned_break_page(cned_element_manager * poManager,const ned_ident idThis) :
	cned_element(poManager,ned_breakpage,idThis)
{
}

inline ened_spr cned_break_page::should_paint(const cned_painter_ &,const ng_point &) const
{
	return spr_inside;
}

inline void cned_break_page::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	//call allocate just for registration in renderer -
	//renderer can manipulate then this element
	ng_size oDummySize;
	roRenderer.allocate_rect(get_ident(),-1,ng_size(0,0),oDummySize,m_oVectorSize);
}

inline void cned_break_page::get_metrics(const ned_measure_param &,cned_metrics &)
{
	ASSERT(!get_prop_hidden());
	clear_measure_pending();
}

inline bool cned_break_page::is_inside_hit_area(const ng_point &) const
{
	return false;
}

inline bool cned_break_page::quote_distance(eRelativePosition,const ng_rect &,long &)
{
	return false;
}

inline void cned_break_page::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	 roLocalRect = ng_rect();
}

inline void cned_break_page::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	roSplitInfo.update_actual_bottom(oPaintPoint.get_y());
	roSplitInfo.next_y_page();
}

}

#else
	#error __FILE__ already included
#endif
