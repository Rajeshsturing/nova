/*
	NAVO Enterprise 2003
	2003-04-06

	navo enhanced display (NED)

	ned_tabmanagerheader / header <tab>
		tabmanager-header
		wewnêtrzny kontener w tab-manager

	tabmanager-header zawiera elementy static poprzedzielane breakline
	tak aby utworzyæ kilka rz¹dków
*/

#ifndef _TABMANAGER_HEADER_NED_H_
#define _TABMANAGER_HEADER_NED_H_

namespace ned
{
class cned_tabmanager;

class cned_tabmanager_header_ : public cned_paragraph
{
public:
	//--- notifications from tab-manager ----
	void on_item_inserted(long nTabNr);
	void on_item_removed(long nTabNr);
	void on_item_activate(long nTabNr,bool bActivate);

	const ng_string & get_item_title(long nTabNr);
	void set_item_title(long nTabNr,const ng_string & roTitleString);
	//------------------------------------------------------
	long _get_position_of_item_ident(ned_ident idItem) const;		
	//pozycja elementu o ident
	//w przypadku wielowierszowych - mo¿e nie byæ pozycj¹ dziecka

	long get_prop_tabs_in_row() const;
	void set_prop_tabs_in_row(long nTabsInRow);
private:
	cned_tabmanager_header_(cned_element_manager * poManager,ned_ident idThis);

	long child_position_2_tab_nr(long nChildPosition) const;
	long tab_nr_2_child_position(long nTabNr) const;
	//----------------------- helpers ---------------------------------------------
	void _insert_title_item(ned_ident idAfter);

	long m_nTabsInRow;
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_tabmanager_header_::cned_tabmanager_header_(cned_element_manager * poManager,ned_ident idThis) :
	cned_paragraph(poManager,ned_tabmanagerheader,idThis),
	m_nTabsInRow(4)
{
}

//------------------------------------------------------
inline long cned_tabmanager_header_::_get_position_of_item_ident(ned_ident idItem) const
{
	return child_position_2_tab_nr(scan_for_child_pos(idItem));
}

inline long cned_tabmanager_header_::get_prop_tabs_in_row() const
{
	return m_nTabsInRow;
}

inline void cned_tabmanager_header_::set_prop_tabs_in_row(long nTabsInRow)
{
	ASSERT(nTabsInRow > 0);
	if(nTabsInRow <= 0)
	{
#ifdef _DEVELOPER_EDITION_
		{
			CString oInfoString = "tabs-in-row musi byæ dodatnie";
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oInfoString );
		}
#endif	
		return;
	}

	if(get_prop_tabs_in_row() == nTabsInRow)
	{
		return;
	}
	
	if(get_child_count() != 0)
	{
#ifdef _DEVELOPER_EDITION_
		{
			CString oInfoString = "bie¿¹ca implementacja pozwala na zmianê tabs-in-row "
				" tylko przy pustym headerze";
			ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,oInfoString );
		}
#endif	
		return;
	}

	m_nTabsInRow = nTabsInRow;
}

inline long cned_tabmanager_header_::child_position_2_tab_nr(long nChildPosition) const
{
	return nChildPosition - (nChildPosition / (get_prop_tabs_in_row() + 1));
}

inline long cned_tabmanager_header_::tab_nr_2_child_position(long nTabNr) const
{
	return nTabNr + (long)((nTabNr / get_prop_tabs_in_row()));
}

}

#else
	#error __FILE__ already included
#endif
