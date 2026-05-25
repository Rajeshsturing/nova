/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabitem / <tabitem>
		
		element <tab>'a 
*/


#ifndef _TABITEM_NED_H_
#define _TABITEM_NED_H_

namespace ned
{
class cned_tabmanager;

class cned_tabmanager_item : public cned_paragraph
{
public:
	//------ property GET -----------------
	ng_string get_prop_title();
	//------ property SET -----------------
	void set_prop_title(const ng_string & roTitleString);
//--------- drawing ------------------
	virtual void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint);

	bool get_already_activated() const;

	void on_activate(bool bActivate);
private:
	cned_tabmanager_item(cned_element_manager * poManager,const ned_ident idThis);
	
	//----------------------------------
	SCP<cned_tabmanager> _get_manager();
	bool	m_bAlreadyActivated;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_tabmanager_item::cned_tabmanager_item(cned_element_manager * poManager,const ned_ident idThis) :
	cned_paragraph(poManager,ned_tabitem,idThis),
	m_bAlreadyActivated(false)
{
}

inline bool cned_tabmanager_item::get_already_activated() const
{
	return m_bAlreadyActivated;
}


inline void cned_tabmanager_item::on_activate(bool bActivate)
{
	if(bActivate)
	{
		m_bAlreadyActivated = true;
	}
	set_prop_hidden(!bActivate);
}

//--------- drawing ------------------
//
//specjalizowane malowanie ramki dla tabitem'a - 
//nie malujemy górnej krawêdzi
//
inline void cned_tabmanager_item::draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	_draw_foreground_children(roForePainter,oPaintPoint);

	if(get_prop_border_type() != NED_BORDER_STYLE_NONE)
	{
		long nFramePxWidth = get_manager()->__zoomize(get_prop_border_width());
		if(nFramePxWidth > 0)
		{
			roForePainter.frame_rect(ng_rect(oPaintPoint,m_oActualSize),nFramePxWidth,
				get_prop_border_color(),border_style_to_frame_mask(get_prop_border_type(),
				NG_FRAME_LEFT | NG_FRAME_RIGHT | NG_FRAME_BOTTOM));
		}
	}
}


}


#else
	#error __FILE__ already included
#endif
