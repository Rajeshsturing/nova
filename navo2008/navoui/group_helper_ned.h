/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	group element helper

*/

#ifndef _GROUP_HELPER_NED_H_
#define _GROUP_HELPER_NED_H_

namespace ned
{

class cned_group_helper__ : public cned_rect_container_, public cned_line_consumer_
{
public:
//------ property GET -----------------

	bool get_prop_keepline() const;
	ened_line_alignment get_prop_line_alignment() const;

//------ property SET -----------------

	void set_prop_keepline(bool bKeepLine);
	void set_prop_line_alignment(ened_line_alignment eLineAlignment);

//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//--------------
	ng_xdist _get_frame_px_width() const;
//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);
protected:
	cned_group_helper__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

//-------------- rendering support -------------------
	void _get_group_metrics(const ned_measure_param & roMParam,cned_metrics & roGroupMetrics);
	ng_size _render_group(cned_transport_renderer & roRenderer,cned_abspos_render_manager & roARM);		//renderuje dzieci

	void _copy_properties(cned_group_helper__ * poGroupHelper);
//-------- page breaking ---------------------------------
	virtual void fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination);
private:
	//-------------- rendering support -------------------
	virtual void add_line(const cned_element_line & roLine);


	bool				m_bKeepLine;		//uk³adaj wszystko w jednej linii (poza <br>)
	ened_line_alignment m_eLineAlignment;	//wyrównanie wewn¹trz lini
	
	//-------------- rendering support -------------------
	//rendered lines
	CArray<cned_element_line,const cned_element_line&> m_oLineArray;

	friend class cned_multi_line_renderer;	//for add_line
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
inline cned_group_helper__::cned_group_helper__(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis) :
	cned_rect_container_(poManager,eType,idThis),
	m_bKeepLine(false),
	m_eLineAlignment(elal_top)
{
}

//------ property GET -----------------

inline bool cned_group_helper__::get_prop_keepline() const
{
	return m_bKeepLine;
}

inline ened_line_alignment cned_group_helper__::get_prop_line_alignment() const
{
	return m_eLineAlignment;
}

inline void cned_group_helper__::set_prop_keepline(bool bKeepLine)
{
	if(get_prop_keepline() == bKeepLine)
	{
		return;
	}
	m_bKeepLine = bKeepLine;
	
	_size_info_dirty();
	_vse_dirty();
}

inline void cned_group_helper__::set_prop_line_alignment(ened_line_alignment eLineAlignment)
{
	if(get_prop_line_alignment() == eLineAlignment)
	{
		return;
	}
	m_eLineAlignment = eLineAlignment;

	_size_info_dirty();
	_vse_dirty();
}

//--------------------------------------------------------------------
//-------------- rendering support -------------------
//--------------------------------------------------------------------
inline void cned_group_helper__::add_line(const cned_element_line & roLine)
{
	m_oLineArray.Add(roLine);
}

inline ng_xdist cned_group_helper__::_get_frame_px_width() const
{
	if(_metrics().is_windows_look())
	{
		return get_manager()->__zoomize(1);	
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

//-------------- fill clone -------------- -------------- -------
inline void cned_group_helper__::_copy_properties(cned_group_helper__ * poDestGroupHelper)
{
	poDestGroupHelper->m_bKeepLine = m_bKeepLine;
	poDestGroupHelper->m_eLineAlignment = m_eLineAlignment;
}

inline void cned_group_helper__::fill_clone(cned_element * poDestination)
{
	cned_rect_container_::fill_clone(poDestination);
	cned_group_helper__ * poDestGroupHelper = cast_ui<cned_group_helper__>(poDestination);
	_copy_properties(poDestGroupHelper);
}

//-------- page breaking ---------------------------------
inline void cned_group_helper__::fill_clone_split(cpb_split_manager & roSplitManager,long xAreaX,long yAreaY,cned_element * poDestination)
{
	cned_rect_container_::fill_clone_split(roSplitManager,xAreaX,yAreaY,poDestination);
	cned_group_helper__ * poDestGroupHelper = cast_ui<cned_group_helper__>(poDestination);
	_copy_properties(poDestGroupHelper);
}

//--------------- persistency -----------------------------------
inline void cned_group_helper__::save(cned_storage_writer & roWriter)
{
	cned_rect_container_::save(roWriter);
	roWriter << m_bKeepLine << long(m_eLineAlignment);

	//ned_to_do: << m_olinearray
}

inline void cned_group_helper__::load(cned_storage_reader & roReader)
{
	cned_rect_container_::load(roReader);
	ASSERT(sizeof(m_eLineAlignment) == sizeof(long));

	roReader >> m_bKeepLine >> (long &) m_eLineAlignment;

	//ned_to_do: << m_olinearray
}

}

#else
	#error __FILE__ already included
#endif
