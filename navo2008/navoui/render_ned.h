/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	rendering classes

*/

#ifndef _RENDER_NED_H_
#define _RENDER_NED_H_

namespace ned
{

class cned_element;
class cned_group_helper__;
class cned_element_manager;

//---------------------------------------------------------------------- 
// 'linia' elementów
//
// ned_to_do: optymalizacja - nie przechowywaæ wszystkich elementów, tylko
// np. pocz¹tek i koniec - problem jednak polega na tym, ¿e nie wiemy
// ile fragmentów ma dany element - zatem nie wiemy jak iterowaæ siê po fragmentach
//---------------------------------------------------------------------- 
class cned_element_line
{
public:
	cned_element_line();
	void append_element(ned_ident idElement,long nElementPart);
	bool get_element(long nIndex,ned_ident & ridElement,long & rnElementPart);
	bool is_empty() const;
	void operator = (const cned_element_line & roElementLine);
private:
	CArray<long,long>	m_oInfoArray;	//packed array in form [idElement,nElementPart]
};

class cned_line_consumer_
{
public:
	virtual void add_line(const cned_element_line & roLine) = 0;
};
//--------- base class for rendering parameters ------------

class ned_render_param__
{
public:
	ng_dc & get_info_dc() const;	//information DC for measurement
	ng_ycoord get_req_y() const;	//required y coordinate
	bool is_printing() const;		//hardcopy rendering
	ePaintMode get_paint_mode() const;
	const ng_rect & get_complete_arena() const;
	void update_req_y(ng_ydist dyOffset);
protected:
	ned_render_param__(ng_dc & roInfoDC,ePaintMode ePM,ng_ycoord yRequiredYCoord,
		const ng_rect & roCompleteArenaRect);
	ned_render_param__(const ned_render_param__ & roRenderParam);
private:
	ng_ycoord			m_yRequiredYCoord;
	ng_dc &				m_roInfoDC;
	const ePaintMode	m_ePaintMode;
	const ng_rect		m_oCompleteArenaRect;
};

//--------- measurement parameters --------------------------

class ned_measure_param : public ned_render_param__
{
public:
	ned_measure_param(ng_dc & roInfoDC,ePaintMode ePM,
		ng_ycoord yRequiredYCoord,const ng_rect & roCompleteArenaRect);
	ned_measure_param(const ned_measure_param & roMeasParam);
};

//--------------------------------------------------------------------
// cned_post_render_manager
//
// post rendering pass
//--------------------------------------------------------------------
class cned_post_render_manager
{
public:
	cned_post_render_manager(bool bPrinting);
	void add(ned_ident idElement);
	bool test_element_remove(ned_ident idElement);
	bool is_any() const;
	bool is_printing() const;
#ifdef _DEBUG
	void dump();
#endif
private:
	bool m_bPrinting;
	CMap<ned_ident,ned_ident,bool,bool>	m_oRenderedElementMap;
};

//--------------------------------------------------------------------
// abstract rendering class which defines rendering interface
//--------------------------------------------------------------------
class cned_renderer_ : public ned_render_param__
{
public:
	//called by element to ensure space availability
	virtual void ensure_width(const ng_xdist xWidth) = 0;
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		/*[out]*/ ng_size & roAllocatedSize,/*[out]*/ ng_size & roVectorSize) = 0;
	
	//returns currently available width (may change after alloc_rect or prepare)
	virtual const ng_xdist get_current_width() const = 0;
	//returns current top left (may change after alloc_rect or prepare)
	virtual const ng_point get_current_pos() const = 0;

	void __add_to_post_renderer(ned_ident idElement);
protected:
	cned_renderer_(cned_renderer_ & roRenderer);
	
	cned_post_render_manager & m_roPostRenderManager;
private:
	cned_renderer_(ng_dc & roInfoDC,ng_ycoord yRequiredYCoord,ePaintMode ePM,
		const ng_rect & roCompleteArenaRect,cned_post_render_manager & roPostRenderManager);

	friend class cned_transport_renderer;
};

//--------------------------------------------------------------------
// transport-renderer s³u¿y tylko do 'transportu' informacji
// nie nale¿y wo³aæ allocate-rect
//--------------------------------------------------------------------
class cned_transport_renderer : public cned_renderer_
{
public:
	cned_transport_renderer(cned_renderer_ & roRenderer,const ng_point & roStartingPoint,ng_xdist dxWidth);

	virtual void ensure_width(const ng_xdist xWidth);
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize);
	virtual const ng_xdist get_current_width() const;
	virtual const ng_point get_current_pos() const;
protected:
	cned_transport_renderer(ng_dc & roInfoDC,ng_ycoord yRequiredYCoord,ePaintMode ePM,
		const ng_rect & roCompleteArenaRect,cned_post_render_manager & roPostRenderManager);
private:
	const ng_point m_oStartingPoint;
	const ng_xdist m_dxWidth;
};


//--------------------------------------------------------------------
// just to clarify design
//--------------------------------------------------------------------

class cned_top_transport_renderer : public cned_transport_renderer
{
public:
	cned_top_transport_renderer(ng_dc & roInfoDC,ng_ycoord yRequiredYCoord,ePaintMode ePM,
		const ng_rect & roCompleteArenaRect,cned_post_render_manager & roPostRenderManager);
};
//--------------------------------------------------------------------
// line-renderer uk³ada wszystko w jednej linii - buduje element line
//--------------------------------------------------------------------

class cned_line_renderer : public cned_renderer_, public CInterface__
{
public:
	cned_line_renderer(cned_renderer_ & roRenderer,cned_element_manager * poManager,
		ened_alignment eHorizAlign,ened_line_alignment eLineAlign,
		const ng_point & roStartingPoint,ng_xdist dxWidth);

	virtual void ensure_width(const ng_xdist xWidth);
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize);
	virtual const ng_xdist get_current_width() const;
	virtual const ng_point get_current_pos() const;

	void finish_line();
	const cned_element_line & get_element_line() const;
	ng_ydist get_line_height() const;
private:
	//-------------- parameters ---------------------
	ng_xdist m_dxWidth;
	cned_element_line m_oLine;
	
	//------------------ 'running' values -----------
	ng_point m_oCurrentPoint;
	ng_ydist m_yCurrLineHeight;	//max wysokoœæ elementów w bie¿¹cej linii
	ened_alignment		   m_eHorizAlignment;
	ened_line_alignment	   m_eLineAlignment;
	cned_element_manager * m_poManager;
};

//--------------------------------------------------------------------
// multi-line-renderer uk³ada wiele linii
//--------------------------------------------------------------------

class cned_multi_line_renderer : public cned_renderer_
{
public:
	cned_multi_line_renderer(cned_line_consumer_ * poLineConsumer,
		cned_renderer_ & roRenderer,cned_element_manager * poManager,
		ened_alignment eHorizAlign,ened_line_alignment eLineAlign,
		const ng_point & roStartingPoint,ng_xdist dxWidth);

	virtual void ensure_width(const ng_xdist xWidth);
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize);
	virtual const ng_xdist get_current_width() const;
	virtual const ng_point get_current_pos() const;

	void newline();
	ng_size finish_all();
private:
	void _start_line();
	void _finish_line();

	//-------------- parameters ---------------------
	const ng_ycoord m_yStartingY;
	const ng_xdist m_dxWidth;
	cned_line_consumer_ *	m_poLineConsumer;
	
	//------------------ 'running' values -----------
	ng_ydist	m_yLastLineHeight;	//dla pustych linii'
	ng_xcoord	m_dxMaxLineWidth;	//max szerokoœæ z wszystkich linii
	ng_point	m_oCurrentPoint;
	SCP<cned_line_renderer> m_poCurrentLineRendererSP;
	ened_alignment		   m_eHorizAlignment;
	ened_line_alignment	   m_eLineAlignment;
	cned_element_manager * m_poManager;
};

//--------------------------------------------------------------------
// column-renderer uk³ada kolejne elementy pod spodem
// szerokoœæ zawsze jest taka sama 
//--------------------------------------------------------------------
class cned_column_renderer : public cned_renderer_
{
public:
	cned_column_renderer(cned_renderer_ & roRenderer,const ng_point & roStartingPoint,ng_xdist dxWidth);

	virtual void ensure_width(const ng_xdist xWidth);
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize);
	virtual const ng_xdist get_current_width() const;
	virtual const ng_point get_current_pos() const;
private:
	ng_point m_oCurrentPoint;
	const ng_xdist mc_dxWidth;
};

//--------------------------------------------------------------------
// quite different renderer for
// absolute - positioned elements
//--------------------------------------------------------------------
class cned_absolute_renderer : public cned_renderer_
{
public:
	cned_absolute_renderer(cned_renderer_ & roRenderer,const ng_rect & roArenaRect);
	virtual void ensure_width(const ng_xdist xWidth);
	virtual void allocate_rect(ned_ident idElement,long nElementPart,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize);
	virtual const ng_xdist get_current_width() const;
	virtual const ng_point get_current_pos() const;
	ng_rect & get_arena_rect();
private:
	ng_rect m_oArenaRect;
};

//--------------------------------------------------------------------
// INLINE SECTION
//---------------------------------------------------------------------- 
// cned_element_line
//---------------------------------------------------------------------- 
inline void cned_renderer_::__add_to_post_renderer(ned_ident idElement)
{
	m_roPostRenderManager.add(idElement);
}

inline cned_element_line::cned_element_line()
{
	ASSERT(is_empty());
}

inline void cned_element_line::append_element(ned_ident idElement,long nElementPart)
{
	m_oInfoArray.Add(idElement);
	m_oInfoArray.Add(nElementPart);
}

inline bool cned_element_line::get_element(long nIndex,ned_ident & ridElement,long & rnElementPart)
{
	nIndex = nIndex + nIndex;
	if(m_oInfoArray.GetUpperBound() >= nIndex)
	{
		ridElement = m_oInfoArray[ nIndex++ ];
		rnElementPart = m_oInfoArray[ nIndex ];
		return true;
	}
	else
	{
		return false;
	}
}

inline bool cned_element_line::is_empty() const
{
	return (m_oInfoArray.GetSize() == 0);
}

inline void cned_element_line::operator = (const cned_element_line & roElementLine)
{
	m_oInfoArray.Copy(roElementLine.m_oInfoArray);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

inline ned_render_param__::ned_render_param__(
	ng_dc & roInfoDC,ePaintMode ePM,ng_ycoord yRequiredYCoord,const ng_rect & roCompleteArenaRect) :
	m_roInfoDC(roInfoDC),
	m_yRequiredYCoord(yRequiredYCoord),
	m_ePaintMode(ePM),
	m_oCompleteArenaRect(roCompleteArenaRect)
{
}

inline ned_render_param__::ned_render_param__(const ned_render_param__ & roRenderParam) :
	m_roInfoDC(roRenderParam.m_roInfoDC),
	m_yRequiredYCoord(roRenderParam.m_yRequiredYCoord),
	m_ePaintMode(roRenderParam.m_ePaintMode),
	m_oCompleteArenaRect(roRenderParam.m_oCompleteArenaRect)
{
}

inline ng_dc & ned_render_param__::get_info_dc() const
{
	return m_roInfoDC;
}

inline ng_ycoord ned_render_param__::get_req_y() const
{
	return m_yRequiredYCoord;
}

inline ePaintMode ned_render_param__::get_paint_mode() const
{
	return m_ePaintMode;
}

inline bool ned_render_param__::is_printing() const
{
	return (m_ePaintMode == pm_printpreview) || (m_ePaintMode == pm_printer);
}

inline const ng_rect & ned_render_param__::get_complete_arena() const
{
	return m_oCompleteArenaRect;
}

inline void ned_render_param__::update_req_y(ng_ydist dyOffset)
{
	m_yRequiredYCoord += dyOffset;
}

//--------------------------------------------------------------------
inline ned_measure_param::ned_measure_param(
	ng_dc & roInfoDC,ePaintMode ePM,ng_ycoord yRequiredYCoord,const ng_rect & roCompleteArenaRect) :
	ned_render_param__(roInfoDC,ePM,yRequiredYCoord,roCompleteArenaRect)
{
}

inline ned_measure_param::ned_measure_param(const ned_measure_param & roMeasParam) :
	ned_render_param__(roMeasParam)
{
}

//--------------------------------------------------------------------
inline cned_renderer_::cned_renderer_(cned_renderer_ & roRenderer) :
	ned_render_param__(roRenderer.get_info_dc(),roRenderer.get_paint_mode(),
		roRenderer.get_req_y(),roRenderer.get_complete_arena()),
	m_roPostRenderManager(roRenderer.m_roPostRenderManager)
{
}

inline cned_renderer_::cned_renderer_(ng_dc & roInfoDC,ng_ycoord yRequiredYCoord,ePaintMode ePM,
	const ng_rect & roCompleteArenaRect,cned_post_render_manager & roPostRenderManager) :
	ned_render_param__(roInfoDC,ePM,yRequiredYCoord,roCompleteArenaRect),
	m_roPostRenderManager(roPostRenderManager)
{
}

//--------------------------------------------------------------------
	//public ctor
inline cned_transport_renderer::cned_transport_renderer(cned_renderer_ & roRenderer,const ng_point & roStartingPoint,ng_xdist dxWidth) :
	cned_renderer_(roRenderer),
	m_oStartingPoint(roStartingPoint),
	m_dxWidth(dxWidth)
{
	ASSERT(m_dxWidth >= 0);
}

	//protected ctor
inline cned_transport_renderer::cned_transport_renderer(ng_dc & roInfoDC,
	ng_ycoord yRequiredYCoord,ePaintMode ePM,const ng_rect & roCompleteArenaRect,
	cned_post_render_manager & roPostRenderManager) :
	cned_renderer_(roInfoDC,yRequiredYCoord,ePM,roCompleteArenaRect,roPostRenderManager),
	m_dxWidth(roCompleteArenaRect.get_width())
{
	ASSERT(m_dxWidth >= 0);
}

inline void cned_transport_renderer::ensure_width(const ng_xdist)
{
	ASSERT(false);		//disallowed to call - formalizm only
}

inline void cned_transport_renderer::allocate_rect(ned_ident,long,const ng_size &,
		ng_size &,ng_size &)
{
	ASSERT(false);		//disallowed to call - formalizm only
}

inline const ng_xdist cned_transport_renderer::get_current_width() const
{
	return m_dxWidth;
}

inline const ng_point cned_transport_renderer::get_current_pos() const
{
	return m_oStartingPoint;
}

//--------------------------------------------------------------------
inline cned_top_transport_renderer::cned_top_transport_renderer(ng_dc & roInfoDC,
	ng_ycoord yRequiredYCoord,ePaintMode ePM,const ng_rect & roCompleteArenaRect,
	cned_post_render_manager & roPostRenderManager) :
	cned_transport_renderer(roInfoDC,yRequiredYCoord,ePM,roCompleteArenaRect,roPostRenderManager)
{
}

//--------------------------------------------------------------------
// line renderer
//--------------------------------------------------------------------
inline void cned_line_renderer::ensure_width(const ng_xdist xWidth)
{
	UNUSED(xWidth);
	ASSERT(m_dxWidth >= xWidth);
}

inline const ng_xdist cned_line_renderer::get_current_width() const
{
	return m_dxWidth;
}

inline const ng_point cned_line_renderer::get_current_pos() const
{
	return m_oCurrentPoint;
}

inline const cned_element_line & cned_line_renderer::get_element_line() const
{
	return m_oLine;
}

inline ng_ydist cned_line_renderer::get_line_height() const
{
	return m_yCurrLineHeight;
}

//--------------------------------------------------------------------
// multi-line-renderer uk³ada wiele linii
//--------------------------------------------------------------------
inline const ng_xdist cned_multi_line_renderer::get_current_width() const
{
	ASSERT(m_poCurrentLineRendererSP.PointsObject());
	return m_poCurrentLineRendererSP->get_current_width();
}

inline const ng_point cned_multi_line_renderer::get_current_pos() const
{
	ASSERT(m_poCurrentLineRendererSP.PointsObject());
	return m_poCurrentLineRendererSP->get_current_pos();
}

inline ng_size cned_multi_line_renderer::finish_all()
{
	_finish_line();
	
	return ng_size(m_dxMaxLineWidth,m_oCurrentPoint.get_y() - m_yStartingY);
}

inline void cned_multi_line_renderer::newline()
{
	_finish_line();
	_start_line();
}

//--------------------------------------------------------------------
// column-renderer uk³ada kolejne elementy pod spodem
// szerokoœæ zawsze jest taka sama 
//--------------------------------------------------------------------
inline void cned_column_renderer::ensure_width(const ng_xdist xWidth)
{
	UNUSED(xWidth);
	ASSERT(mc_dxWidth >= xWidth);
}

inline void cned_column_renderer::allocate_rect(ned_ident idElement,long,const ng_size & roRequiredSize,
	ng_size & roAllocatedSize,ng_size & roVectorSize)
{
	UNUSED_ALWAYS(idElement);
	ASSERT(mc_dxWidth >= roRequiredSize.get_dx());

	roAllocatedSize.set_dx(mc_dxWidth);
	roAllocatedSize.set_dy(roRequiredSize.get_dy());

	roVectorSize.set_dx(m_oCurrentPoint.get_x());
	roVectorSize.set_dy(m_oCurrentPoint.get_y());

	m_oCurrentPoint.set_y(m_oCurrentPoint.get_y() + roRequiredSize.get_dy());

	m_roPostRenderManager.add(idElement);
}

inline const ng_xdist cned_column_renderer::get_current_width() const
{
	return mc_dxWidth;
}

inline const ng_point cned_column_renderer::get_current_pos() const
{
	return m_oCurrentPoint;
}

//--------------------------------------------------------------------
// cned_absolute_renderer
//--------------------------------------------------------------------
inline cned_absolute_renderer::cned_absolute_renderer(cned_renderer_ & roRenderer,const ng_rect & roArenaRect) :
	cned_renderer_(roRenderer),
	m_oArenaRect(roArenaRect)
{
}

inline ng_rect & cned_absolute_renderer::get_arena_rect()
{
	return m_oArenaRect;
}

inline void cned_absolute_renderer::ensure_width(const ng_xdist xWidth)
{
	UNUSED(xWidth);
	ASSERT(xWidth <= get_current_width());
}

inline void cned_absolute_renderer::allocate_rect(ned_ident /*idElement*/,long /*nElementPart*/,const ng_size & roRequiredSize,
		ng_size & roAllocatedSize,ng_size & roVectorSize)
{
	roAllocatedSize = roRequiredSize;
	roVectorSize = ng_size();
}

inline const ng_xdist cned_absolute_renderer::get_current_width() const
{
	return m_oArenaRect.get_width();
}

inline const ng_point cned_absolute_renderer::get_current_pos() const
{
	return m_oArenaRect.get_topleft();
}


//--------------------------------------------------------------------
// post rendering pass
//--------------------------------------------------------------------
inline cned_post_render_manager::cned_post_render_manager(bool bPrinting):
	m_bPrinting(bPrinting)
{
	m_oRenderedElementMap.InitHashTable(599);
}

inline void cned_post_render_manager::add(ned_ident idElement)
{
	if(NEDID_PLACEHOLDER != idElement)
	{
		m_oRenderedElementMap[ idElement ] = true;
	}
}

inline bool cned_post_render_manager::test_element_remove(ned_ident idElement)
{
	return (m_oRenderedElementMap.RemoveKey(idElement) != FALSE);
}

inline bool cned_post_render_manager::is_any() const
{
	return (m_oRenderedElementMap.GetCount() != 0);
}

inline bool cned_post_render_manager::is_printing() const
{
	return m_bPrinting;
}

#ifdef _DEBUG
inline void cned_post_render_manager::dump()
{
	return;

	TRACE("--- post renderer dump ---------\n");

	POSITION pos = m_oRenderedElementMap.GetStartPosition();
	while(pos)
	{
		ned_ident idElement;
		bool bDummy;
		m_oRenderedElementMap.GetNextAssoc(pos,idElement,bDummy);
		TRACE("%d\n",idElement);
	}
	
	TRACE("----------------------------------\n");
}

#endif

}

#else
	#error __FILE__ already included
#endif
