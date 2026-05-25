/*
	NAVO Enterprise 2008
	27.06.2002
	
	cnui_group_container
		abstrakcyjna grupa elementów,
		uk³adana wg flow np. paragraph, tablecell itd.
		maj¹ca wspólne cechy i t³o
*/


#ifndef _GROUP_NUI_H_
#define _GROUP_NUI_H_

/*
	dynamic group of elements making single 'line'
*/

cnui_element_manager;

enum enui_line_alignment
{
	elal_top	= 0x00,
	elal_bottom	= 0x01,
	elal_vcenter= 0x02,
};

//XPART
class cnui_element_line
{
public:
	cnui_element_line();
	
	void add_first_item(nui_ident idElement,long nFragmentId);
	void add_next_item(nui_ident idElement,long nFragmentId);
	nui_ident get_last_item() const;
//~XPART

	void get_area(ng_area & roArea,cnui_element_manager * poManager) const;
	bool get_render_info(cnui_element_manager * poManager,ng_ycoord & ryMinRender,ng_ycoord & ryTop) const;

	void align_and_move_by(enui_line_alignment eLineAlignment,const ng_rect & roLineRect,
		const ng_size & roSize,cnui_element_manager * poManager);
private:
	//------- first element in line (ident + fragment)
	nui_ident	m_idFirst;
	long		m_nFirstFragmentId;
	//------- last element in line (ident + fragment)
	nui_ident	m_idLast;
	long		m_nLastFragmentId;
};


class cnui_group_container : public cnui_rect_container_
{
public: 
	
	virtual bool save(cnui_storage_write & roStorageWrite);
	virtual void load(cnui_storage_read & roStorageRead);

//XPART
	virtual bool measure_children(cnui_measure_info & roInfo);
//------ property GET -----------------
//------ property SET -----------------
//------ ~ property  -----------------

protected:
	cnui_group_container(cnui_element_manager * poManager,const enui_type eType,const nui_ident nIdent);
//~XPART


//XPART
	bool				m_bKeepLine;		//uk³adaj wszystko w jednej linii (poza <br>)
	enui_line_alignment m_eLineAlignment;	//wyrównanie wewn¹trz lini
//~XPART
	
	//to_do: czy to jest potrzebne ?
	ng_size				m_oGroupSize;		//rozmiar zajmowany przez dzieci (nie jest to rozmiar kontenera
	
	//each array element represents single "line"
	CArray<cnui_element_line,cnui_element_line &> m_oLineArray;

	friend class cnui_ff_line_renderer;
};

//------------------------------------------------------------------ 
//---------------------- inlines -----------------------------------
//------------------------------------------------------------------

//XPART
inline cnui_element_line::cnui_element_line() :
	m_idFirst(NUI_IDENT_NOTHING),
	m_nFirstFragmentId(0),
	m_idLast(NUI_IDENT_NOTHING),
	m_nLastFragmentId(0)
{
}

inline void cnui_element_line::add_first_item(nui_ident idElement,long nFragmentId)
{
	ASSERT(m_idFirst == NUI_IDENT_NOTHING);

	m_idFirst			= idElement;
	m_idLast			= idElement;
	m_nFirstFragmentId	= nFragmentId;
	m_nLastFragmentId	= nFragmentId;
}

inline void cnui_element_line::add_next_item(nui_ident idElement,long nFragmentId)
{
	ASSERT(m_idLast != NUI_IDENT_NOTHING);
	
	m_idLast			= idElement;
	m_nLastFragmentId	= nFragmentId;
}

inline nui_ident cnui_element_line::get_last_item() const
{
	return m_idLast;
}
	
//~XPART

#else
	#error __FILE__ already included
#endif
