/*
	NAVO Enterprise 2003
	2003-03-30

	navo enhanced display automation wrappers (NEDAW)
	
	nedaw container definition

*/

#ifndef _CONTAINER_NEDAW_H_
#define _CONTAINER_NEDAW_H_

namespace ned
{
	class cned_container;
	class cned_group_helper__;
	class cned_tablecell;
	class cned_page;
	class cned_option_button_;
	class cned_table;
	class cned_grid;
	class cned_tabmanager;
	class cned_tabmanager_item;
	class cned_tablesection;
	class cned_grid_bodysection;
	class cned_tablerow;
	class cned_scrollbar__;
	class cned_paragraph;
	class cned_page_caption;
}

namespace nedaw
{

class cnedaw_container : public cnedaw_element
{
public:
	cnedaw_container(SCP<ned::cned_element> poInternalSP);
	//{{AFX_DISPATCH(cnedaw_container)
	afx_msg LPDISPATCH AddNewAUTO(long Type,long Ident);
	afx_msg LPDISPATCH InsertNewAUTO(long Type, long IdentAfter,long Ident);
	afx_msg void RemoveAllAUTO();
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg void RemoveAUTO(const VARIANT FAR& rvarElement);
	afx_msg void ApplyAttributesAUTO();
	afx_msg LPDISPATCH GetElementAUTO(long nOuterPos);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_container * _get_container();
	
	ned::cned_container * m_poContainer;
};

//-----------------------------------------------------------------
// group container
//-----------------------------------------------------------------
class cnedaw_group_container : public cnedaw_container
{
public:
	cnedaw_group_container(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_group_container)
	afx_msg BOOL GetForceSingleLineAUTO();
	afx_msg void SetForceSingleLineAUTO(BOOL bNewValue);
	afx_msg long GetLineAlignmentAUTO();
	afx_msg void SetLineAlignmentAUTO(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_group_helper__ * _get_group_helper();
	
	ned::cned_group_helper__ * m_poGroupHelper;
};

//-----------------------------------------------------------------
// table cell
//-----------------------------------------------------------------
class cnedaw_table_cell : public cnedaw_group_container
{
public:
	cnedaw_table_cell(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_table_cell)
	afx_msg long GetColSpanAUTO();
	afx_msg void SetColSpanAUTO(long nNewValue);
	afx_msg long GetRowSpanAUTO();
	afx_msg void SetRowSpanAUTO(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_tablecell * _get_table_cell();
	
	ned::cned_tablecell * m_poTableCell;
};

//-----------------------------------------------------------------
// page
//-----------------------------------------------------------------
class cnedaw_page : public cnedaw_group_container
{
public:
	cnedaw_page(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_page)
	afx_msg BSTR GetTitleAUTO();
	afx_msg void SetTitleAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetCaptionAUTO();
	afx_msg void SetCaptionAUTO(BOOL bNewValue);
	afx_msg long GetDisplayModeAUTO();
	afx_msg void SetDisplayModeAUTO(long nValue);
	afx_msg LPDISPATCH GetWidgetsAUTO();
	afx_msg LPDISPATCH GetHeaderAUTO();
	afx_msg LPDISPATCH GetFooterAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_page * _get_page();
	
	ned::cned_page * m_poPage;
};

//-----------------------------------------------------------------
// cnedaw_option_button_
//-----------------------------------------------------------------
class cnedaw_option_button_ : public cnedaw_container
{
public:
	cnedaw_option_button_(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_option_button_)
	afx_msg long GetColSpanAUTO();
	afx_msg void SetColSpanAUTO(long nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_option_button_ * _get_option_button();
	
	ned::cned_option_button_ * m_poOptionButton;
};

//-----------------------------------------------------------------
// table
//-----------------------------------------------------------------
class cnedaw_table : public cnedaw_container
{
public:
	cnedaw_table(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_table)
	afx_msg LPDISPATCH GetFirstHeaderSectionAUTO();
	afx_msg LPDISPATCH GetNextHeaderSectionAUTO();
	afx_msg LPDISPATCH GetBodySectionAUTO();
	afx_msg LPDISPATCH GetPrevFooterSectionAUTO();
	afx_msg LPDISPATCH GetLastFooterSectionAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_table * _get_table();
	
	ned::cned_table * m_poTable;
};

//-----------------------------------------------------------------
// grid
//-----------------------------------------------------------------
class cnedaw_grid : public cnedaw_table
{
public:
	cnedaw_grid(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_grid)
	afx_msg LPDISPATCH GetPatternSectionAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_grid * _get_grid();
	
	ned::cned_grid * m_poGrid;
};

//-----------------------------------------------------------------
// tabmanager
//-----------------------------------------------------------------
class cnedaw_tabmanager : public cnedaw_container
{
public:
	cnedaw_tabmanager(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_tabmanager)
	afx_msg long GetActiveItemAUTO();
	afx_msg void SetActiveItemAUTO(long nItem);
	afx_msg long GetTabsInRowAUTO();
	afx_msg void SetTabsInRowAUTO(long nCount);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_tabmanager * _get_tabmanager();
	
	ned::cned_tabmanager * m_poTabManager;
};

//-----------------------------------------------------------------
// paragraph
//-----------------------------------------------------------------
class cnedaw_paragraph : public cnedaw_group_container
{
public:
	cnedaw_paragraph(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_paragraph)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_paragraph * _get_paragraph();
	
	ned::cned_paragraph * m_poParagraph;
};

//-----------------------------------------------------------------
// tabmanager_item
//-----------------------------------------------------------------
class cnedaw_tabmanager_item : public cnedaw_paragraph
{
public:
	cnedaw_tabmanager_item(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_tabmanager_item)
	afx_msg BSTR GetTitleAUTO();
	afx_msg void SetTitleAUTO(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_tabmanager_item * _get_tabmanager_item();
	
	ned::cned_tabmanager_item * m_poTabManagerItem;
};

//-----------------------------------------------------------------
// table section
//-----------------------------------------------------------------
class cnedaw_table_section : public cnedaw_container
{
public:
	cnedaw_table_section(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_table_section)
	afx_msg LPDISPATCH InsertNewRowAUTO(long nRow);
	afx_msg long GetRowCountAUTO();
	afx_msg LPDISPATCH GetRowAUTO(long nRow);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_tablesection * _get_section();
	
	ned::cned_tablesection * m_poSection;
};

//-----------------------------------------------------------------
// grid body section
//-----------------------------------------------------------------
class cnedaw_gridbody_section : public cnedaw_table_section
{
public:
	cnedaw_gridbody_section(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_gridbody_section)
	afx_msg long GetDataRowCountAUTO();
	afx_msg void SetDataRowCountAUTO(long nNewRowCount);
	afx_msg long DataRowNr2TableRowNrAUTO(long nExtDataRowNr);
	afx_msg long TableRowNr2DataRowNrAUTO(long nExtTableRowNr);
	afx_msg long GetFirstVisibleAUTO();
	afx_msg void SetFirstVisibleAUTO(long iFirstVisibleDataRow);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_grid_bodysection * _get_gridbody_section();
	
	ned::cned_grid_bodysection * m_poGridBodySection;
};

//-----------------------------------------------------------------
// tablerow
//-----------------------------------------------------------------
class cnedaw_tablerow : public cnedaw_container
{
public:
	cnedaw_tablerow(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_tablerow)
	afx_msg LPDISPATCH InsertNewCellAUTO(long nCol);
	afx_msg long GetCellCountAUTO();
	afx_msg LPDISPATCH GetCellAUTO(long nCol);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_tablerow * _get_table_row();
	
	ned::cned_tablerow * m_poTableRow;
};

//-----------------------------------------------------------------
// scrollbar
//-----------------------------------------------------------------
class cnedaw_scrollbar : public cnedaw_paragraph
{
public:
	cnedaw_scrollbar(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_scrollbar)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_scrollbar__ * _get_scrollbar();
	
	ned::cned_scrollbar__ * m_poScrollBar;
};

//-----------------------------------------------------------------
// page_caption
//-----------------------------------------------------------------
class cnedaw_pagecaption : public cnedaw_paragraph
{
public:
	cnedaw_pagecaption(SCP<ned::cned_element> poInternalSP);

	//{{AFX_DISPATCH(cnedaw_pagecaption)
	afx_msg LPDISPATCH GetClosePicAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	ned::cned_page_caption * _get_page_caption();
	
	ned::cned_page_caption * m_poPageCaption;
};


}


#else
	#error __FILE__ already included
#endif

