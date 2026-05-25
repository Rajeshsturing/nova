/*
	NAVO Enterprise 2003
	2003-04-01

	navo enhanced display (NED)

	ned_breakline / <br>

	z³amanie linii

*/

#ifndef _BREAK_LINE_NED_H_
#define _BREAK_LINE_NED_H_

namespace ned
{

class cned_break_line : public cned_element
{
	virtual void get_metrics(const ned_measure_param &,cned_metrics &);
	virtual void _invalidate_all_paint() {}
	virtual ened_spr should_paint(const cned_painter_ &,const ng_point &) const;
	virtual void draw_foreground(cned_fore_painter &,const ng_point &){}
	virtual void draw_background(cned_back_painter &,const ng_point &){}
	virtual void post_render(cned_post_render_manager &,const ng_point &){}
	virtual void render(cned_renderer_ & roRenderer);
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const;

	//-------- page breaking ---------------------------------
	virtual void update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo);
private:
	cned_break_line(cned_element_manager * poManager,const ned_ident idThis);

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_break_line::cned_break_line(cned_element_manager * poManager,const ned_ident idThis) :
	cned_element(poManager,ned_breakline,idThis)
{
}

inline ened_spr cned_break_line::should_paint(const cned_painter_ &,const ng_point &) const
{
	return spr_inside;
}

inline void cned_break_line::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	//call allocate just for registration in renderer -
	//renderer can manipulate then this element
	ng_size oDummySize;
	roRenderer.allocate_rect(get_ident(),-1,ng_size(0,0),oDummySize,m_oVectorSize);
}

inline void cned_break_line::get_metrics(const ned_measure_param &,cned_metrics &)
{
	ASSERT(!get_prop_hidden());
	clear_measure_pending();
}

inline bool cned_break_line::is_inside_hit_area(const ng_point &) const
{
	return false;
}

inline bool cned_break_line::quote_distance(eRelativePosition,const ng_rect &,long &)
{
	return false;
}

inline void cned_break_line::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	 roLocalRect = ng_rect();
}

//-------- page breaking ---------------------------------
inline void cned_break_line::update_split_info(const ng_point & roCurrentPoint,cpb_split_info & roSplitInfo)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	if(oPaintPoint.get_y() > roSplitInfo.get_max_bottom())
	{
		//next page -> finish current
		roSplitInfo.next_y_page();
	}
}


}

#else
	#error __FILE__ already included
#endif
