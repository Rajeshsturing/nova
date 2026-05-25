/*
	NAVO Enterprise 2003
	2003-03-24

	navo enhanced display (NED)

	ned_tablecell / <td>
		komórka tabelki
*/

#ifndef _TABLECELL_NED_H_
#define _TABLECELL_NED_H_

namespace ned
{
class cned_tablerow;
class cned_tablesection;
class cned_table;

class cned_tablecell : public cned_group_helper__
{
public:
//--------- drawing ------------------
	void draw_foreground(cned_fore_painter & roForePainter,const ng_point & roCurrentPoint,
		const long nAllocRowNr,const long nColNr);
	virtual void draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint);
//-------------- attribute functions -------------------------
	virtual void set_fixed_properties();
//------ property GET -----------------
	long get_prop_colspan() const;
	long get_prop_rowspan() const;
//------ property SET -----------------
	void set_prop_colspan(long nColSpan);
	void set_prop_rowspan(long nRowSpan);
	virtual void set_prop_hidden(bool bHidden);
//-------------- rendering support -------------------
	ng_ydist render(cned_transport_renderer & roTransportRenderer,long nAllocRowNr,long nColNr);
	const cned_metrics & get_metrics(const ned_measure_param & roMParam,ng_xdist & rxMinInternalCellWidth);
	virtual void get_children_metrics(const ned_measure_param & roMParam);

	void render_increase_height(ng_ydist dyDeltaEqualizer);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);

	//-------- page breaking ---------------------------------
	virtual void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager);
	void make_split(const ng_point & roCurrentPoint,cpb_split_manager & roSplitManager,long nAllocRowNr,long nColNr);
	//--------------- persistency -----------------------------------
	virtual void save(cned_storage_writer & roWriter);
	virtual void load(cned_storage_reader & roReader);
protected:
	cned_tablecell(cned_element_manager * poManager,const ned_ident nIdent);

	//----- structure helpers -----------
	SCP<cned_tablerow> _get_row() const;
	SCP<cned_tablesection> _get_section() const;
	SCP<cned_table> _get_table() const;
private:

	long	m_nColSpan;
	long	m_nRowSpan;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_tablecell::cned_tablecell(cned_element_manager * poManager,const ned_ident idThis) :
	cned_group_helper__(poManager,ned_tablecell,idThis),
	m_nRowSpan(1),
	m_nColSpan(1)
{
}

//------ property GET -----------------
inline long cned_tablecell::get_prop_colspan() const
{
	return m_nColSpan;
}

inline long cned_tablecell::get_prop_rowspan() const
{
	return m_nRowSpan;
}

//--------------------------------------------------------------------
//----- structure helpers -----------
inline SCP<cned_tablerow> cned_tablecell::_get_row() const
{
	return scp_cast_ui<cned_tablerow>(get_container());
}

inline SCP<cned_tablesection> cned_tablecell::_get_section() const
{
	return scp_cast_ui<cned_tablesection>(get_container()->get_container());
}

inline SCP<cned_table> cned_tablecell::_get_table() const
{
	return scp_cast_ui<cned_table>(get_container()->get_container()->get_container());
}

//---------------------------------------------------------------------------------
inline void cned_tablecell::render_increase_height(ng_ydist dyDeltaRowEqualizer)
{
	ASSERT(dyDeltaRowEqualizer > 0);
	m_oActualSize.set_dy(m_oActualSize.get_dy() + dyDeltaRowEqualizer);
}

//--------- drawing ------------------
inline void cned_tablecell::draw_background(cned_back_painter & roBackPainter,const ng_point & roCurrentPoint)
{
	ng_point oPaintPoint(roCurrentPoint);
	oPaintPoint.offset(m_oVectorSize);

	ng_rect oCellRect(oPaintPoint,m_oActualSize);
	
	_draw_std_background(roBackPainter,oCellRect);
	_draw_background_children(roBackPainter,oPaintPoint);
	
	_store_main_paint_rect(oCellRect);
}

//-------------- fill clone -------------- -------------- -------
inline void cned_tablecell::fill_clone(cned_element * poDestination)
{
	cned_group_helper__::fill_clone(poDestination);
	cned_tablecell * poDestTableCell = cast_ui<cned_tablecell>(poDestination);
	//don't copy raw members - use set_prop
	poDestTableCell->set_prop_colspan(get_prop_colspan());
	poDestTableCell->set_prop_rowspan(get_prop_rowspan());
}

//-------- page breaking ---------------------------------
inline void cned_tablecell::make_split(const ng_point &,cpb_split_manager &)
{
	ASSERT(false);	//specialized version should be called intead
}

//--------------- persistency -----------------------------------
inline void cned_tablecell::save(cned_storage_writer & roWriter)
{
	cned_group_helper__::save(roWriter);
	roWriter << m_nColSpan << m_nRowSpan;
}

inline void cned_tablecell::load(cned_storage_reader & roReader)
{
	cned_group_helper__::load(roReader);
	roReader >> m_nColSpan >> m_nRowSpan;
}

}

#else
	#error __FILE__ already included
#endif
