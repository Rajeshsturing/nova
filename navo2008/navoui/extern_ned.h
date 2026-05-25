/*
	NAVO Enterprise 2003
	2003-04-15

	navo enhanced display (NED)

	ned_extern / <extern>

	element 'extern'

*/

#ifndef _EXTERN_NED_H_
#define _EXTERN_NED_H_

namespace ned
{

class cned_extern : public cned_element
{
public:
//------ property GET -----------------
	const ng_string & get_prop_data() const;
	virtual void get_prop_value(CSmartOleVariant & roSOV);
//------ property SET -----------------
	void set_prop_data(LPCTSTR lpDataString);
	virtual void set_prop_hidden(bool bHidden);
	virtual void set_prop_value(const CSmartOleVariant & roSOV);

//------------ formalizmy ----------------------
	virtual void get_metrics(const ned_measure_param &,cned_metrics &);
	virtual bool is_inside_hit_area(const ng_point & roPoint) const;
	virtual bool quote_distance(eRelativePosition eRP,const ng_rect & roRefRect,long & rnDistance);
	virtual void get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const;
	virtual ened_spr should_paint(const cned_painter_ &,const ng_point &) const;
	virtual void draw_foreground(cned_fore_painter &,const ng_point &){}
	virtual void draw_background(cned_back_painter &,const ng_point &){}
	virtual void post_render(cned_post_render_manager &,const ng_point &){}
	virtual void render(cned_renderer_ & roRenderer);
	virtual void _invalidate_all_paint() {}
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
private:
	cned_extern(cned_element_manager * poManager,const ned_ident idThis);

	ng_string	m_oDataString;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_extern::cned_extern(cned_element_manager * poManager,const ned_ident idThis) :
	cned_element(poManager,ned_extern,idThis)
{
	//wyj¹tkowo w ten sposób, poniewa¿ w konstruktorze
	//nie ma jeszcze powi¹zañ
	//a chcemy zapewniæ, ¿e element extern jest zawsze ukryty

	_mini_info().set_hidden(true);
}

//------ property GET -----------------
inline const ng_string & cned_extern::get_prop_data() const
{
	return m_oDataString;
}

inline void cned_extern::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = m_oDataString;
}

//------ property SET -----------------
inline void cned_extern::set_prop_hidden(bool /*bHidden*/)
{
	cned_element::set_prop_hidden(true);
}

inline void cned_extern::set_prop_data(LPCTSTR lpDataString)
{
	m_oDataString = lpDataString;
}

inline void cned_extern::set_prop_value(const CSmartOleVariant & roSOV)
{
	m_oDataString = roSOV.GetBStr();
}

//------------ formalizmy ----------------------
inline void cned_extern::get_metrics(const ned_measure_param &,cned_metrics &)
{
	ASSERT(!get_prop_hidden());
	clear_measure_pending();
}

inline bool cned_extern::is_inside_hit_area(const ng_point &) const
{
	return false;
}

inline bool cned_extern::quote_distance(eRelativePosition,const ng_rect &,long &)
{
	return false;
}

inline void cned_extern::get_bounding_rect(long /*nElementPart*/,ng_rect & roLocalRect) const
{
	roLocalRect = ng_rect();
}

inline ened_spr cned_extern::should_paint(const cned_painter_ &,const ng_point &) const
{
	return spr_inside;
}

inline void cned_extern::render(cned_renderer_ & roRenderer)
{
	ASSERT(!is_measure_pending());
	//call allocate just for registration in renderer -
	//renderer can manipulate then this element
	ng_size oDummySize;
	roRenderer.allocate_rect(get_ident(),-1,ng_size(0,0),oDummySize,m_oVectorSize);
}

//-------------- fill clone -------------- -------------- -------
inline void cned_extern::fill_clone(cned_element * poDestination)
{
	cned_element::fill_clone(poDestination);
	
	cned_extern * poExternDest = cast_ui<cned_extern>(poDestination);
	poExternDest->m_oDataString = m_oDataString;
}


}


#else
	#error __FILE__ already included
#endif
