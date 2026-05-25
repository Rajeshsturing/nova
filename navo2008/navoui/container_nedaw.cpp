/*
	NAVO Enterprise 2003
	2003-03-30

	navo enhanced display automation wrappers (NEDAW)
	
	nedaw container definition

*/

#include "stdafx.h"
#include "element_nedaw.h"
#include "picture_ned.h"
#include "container_nedaw.h"
#include "optionbutton_ned.h"
#include "group_helper_ned.h"
#include "scroll_helper_ned.h"
#include "table_ned.h"
#include "tablesection_ned.h"
#include "grid_ned.h"
#include "table_bodysection_ned.h"
#include "tablerow_ned.h"
#include "pattern_tablerow_ned.h"
#include "grid_bodysection_ned.h"
#include "tablecell_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "page_ned.h"
#include "tabitem_ned.h"
#include "tabmanager_header_ned.h"
#include "tabmanager_ned.h"
#include "scrollbar_ned.h"


using namespace nedaw;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//---------------------------------------------------------------------------
// container 
//---------------------------------------------------------------------------
cnedaw_container::cnedaw_container(SCP<ned::cned_element> poInternalSP) :
	cnedaw_element(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poContainer = static_cast<ned::cned_container*>(poInternalSP.Get());
}

inline ned::cned_container * cnedaw_container::_get_container()
{
	ASSERT(m_poContainer != NULL);
	return m_poContainer;
}

BEGIN_DISPATCH_MAP(cnedaw_container, cnedaw_element)
	//{{AFX_DISPATCH_MAP(cnedaw_container)
	DISP_FUNCTION(cnedaw_container, "addnew", AddNewAUTO, VT_DISPATCH, VTS_I4 VTS_I4)
	DISP_FUNCTION(cnedaw_container, "insertnew", InsertNewAUTO, VT_DISPATCH, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(cnedaw_container, "removeall", RemoveAllAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cnedaw_container, "remove", RemoveAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_PROPERTY_EX_ID(cnedaw_container, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	DISP_FUNCTION(cnedaw_container, "applyattributes", ApplyAttributesAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(cnedaw_container, "element", GetElementAUTO, VT_DISPATCH, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

void cnedaw_container::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","uicontainer");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


LPDISPATCH cnedaw_container::AddNewAUTO(long nElementType,long IdentNew) 
{
	return InsertNewAUTO(nElementType,NEDID_LAST,IdentNew);
}

LPDISPATCH cnedaw_container::InsertNewAUTO(long nElementType, long IdentAfter,long IdentNew) 
{
	ALL_TRY
	{
		SCP <cned_element> poElementSP = _get_container()->insert_new_element(ened_element_type(nElementType),ned_ident(IdentNew),ned_ident(IdentAfter));
		poElementSP->apply_attributes(_get_container()->get_current_attributes());
		return poElementSP->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


void cnedaw_container::RemoveAllAUTO() 
{
	ALL_TRY
	{
		_get_container()->remove_children(false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_container::RemoveAUTO(const VARIANT FAR& rvarElement)
{
	ALL_TRY
	{
		const CSmartOleVariant & roValueSOV = reinterpret_cast<const CSmartOleVariant &>(rvarElement);
		switch(roValueSOV.Type())
		{
		case VT_I4:
		{
			ned_ident Ident = ned_ident(roValueSOV.GetLong());
			_get_container()->remove_element(Ident);
		}
		break;
		case VT_I2:			//wyj¹tkowo aby nie byæ upierdliwym dla programisty
		{
			ned_ident Ident = ned_ident(roValueSOV.GetShort());
			_get_container()->remove_element(Ident);
		}
		break;
		case VT_DISPATCH:
		{
			SCP<cnedaw_element> poNedawElementSP = cnedaw_element::FromIDispatch(roValueSOV.GetDispatch());
			ASSERT(poNedawElementSP.PointsObject());
			_get_container()->remove_element(poNedawElementSP->_get_element()->get_ident());
		}
		break;
		case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
		{
			VARIANT * pVariant = roValueSOV.GetVariantRef().pvarVal;
			ASSERT(pVariant);
			RemoveAUTO(*pVariant);	//Uwaga! wywo³uje siebie ale ju¿ bez byRef
		}
		break;
		default:
			ASSERT(false);
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_container::ApplyAttributesAUTO()
{
	ALL_TRY
	{
		SCP<cned_container> poParentContainerSP = _get_container()->get_container();
		_get_container()->apply_attributes(poParentContainerSP.PointsObject() ? 
			poParentContainerSP->get_current_attributes() : _get_container()->get_current_attributes());
		_get_container()->_size_info_dirty();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_container::GetElementAUTO(long nOuterPos)
{
	ALL_TRY
	{
		ned_ident idChild = _get_container()->get_child_ident_on_pos(nOuterPos-1);
		if(idChild != NEDID_NOTHING)
		{
			return _get_container()->get_nedaw(idChild)->GetDispatch(true);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//---------------------------------------------------------------------------------------
// enumerator
//---------------------------------------------------------------------------------------

class cnedaw_container_enumerator : public CCmdTargetInterface
{
public:
	cnedaw_container_enumerator(SCP<cned_container> & rpoContainerSP) :
		m_poContainerSP(rpoContainerSP),
		m_oFilterChildren(rpoContainerSP,false,false)
	{
		EnableAutomation();
	}
	cnedaw_container_enumerator(const cnedaw_container_enumerator & roSecond) :
		m_poContainerSP(const_cast<cnedaw_container_enumerator &>(roSecond).m_poContainerSP),
		m_oFilterChildren(roSecond.m_poContainerSP,false,false)
	{
		EnableAutomation();
	}
	bool Next(long lElements, CSmartOleVariant * pVariants, long *plElementsFetched)
	{
		if (plElementsFetched)
		{
			*plElementsFetched = 0;
		};
		long iter = 0; 
		for (iter = 0; iter < lElements; iter++)
		{
			if(m_oFilterChildren.is_end())
			{
				break;
			}
			SCP<cned_element> poElementSP = m_oFilterChildren.get_element();
			ASSERT(poElementSP.PointsObject());
			SCP<IDispatch> poDispatchSP = poElementSP->get_my_nedaw()->GetDispatchSP();
			*pVariants = CSmartOleVariant(poDispatchSP);
			m_oFilterChildren.move_next();
		}
		if (plElementsFetched)
		{
			*plElementsFetched = iter;
		};
		return (iter == lElements);
	};
	bool Skip(ULONG lValue)
	{
		while(lValue-- > 0)
		{
			if(m_oFilterChildren.is_end())
			{
				return false;
			}
			m_oFilterChildren.move_next();
		}
		return true;
	};
	void Reset()
	{
		m_oFilterChildren.restart_at(m_poContainerSP->get_first_child_ident());
	};
	SCP < cnedaw_container_enumerator > Clone()
	{
		return NewSCP(new cnedaw_container_enumerator (*this));
	};
	SCP <IEnumVARIANT> GetEnumVARIANT()
	{
		return NewSCP(&m_xEnumVariant, true);
	};
	//{{AFX_DISPATCH(cnedaw_container_enumerator )
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(EnumVariant, IEnumVARIANT)
		HRESULT STDMETHODCALLTYPE Next(ULONG celt,VARIANT *rgVar,ULONG *pCeltFetched)
		{
			METHOD_PROLOGUE(cnedaw_container_enumerator , EnumVariant);
			ALL_TRY
			{
				for (ULONG lIndex = 0; lIndex < celt; lIndex++)
				{
					::VariantInit(&rgVar[lIndex]);
				};
				return pThis->Next((long)celt, (CSmartOleVariant *)((void *)rgVar), (long *)pCeltFetched) ? S_OK : S_FALSE;
			}
			ALL_CATCH(CNavoException & /*to_do: roException */)
			{
				for (ULONG lIndex = 0; lIndex < celt; lIndex++)
				{
					::VariantClear(&rgVar[lIndex]);
				};
				//ned_to_do:
				return DISP_E_EXCEPTION;
			};
		};
		HRESULT STDMETHODCALLTYPE Skip(ULONG celt)
		{
			METHOD_PROLOGUE(cnedaw_container_enumerator , EnumVariant);
			ALL_TRY
			{
				return pThis->Skip(celt) ? S_OK : S_FALSE;
			}
			ALL_CATCH(CNavoException & /*to_do: roException*/)
			{
				//ned_to_do:
				return DISP_E_EXCEPTION;
			};
		};
		HRESULT STDMETHODCALLTYPE Reset(void)
		{
			METHOD_PROLOGUE(cnedaw_container_enumerator, EnumVariant);
			pThis->Reset();
			return S_OK;
		};
		HRESULT STDMETHODCALLTYPE Clone(IEnumVARIANT ** ppEnum)
		{
			METHOD_PROLOGUE(cnedaw_container_enumerator, EnumVariant);
		
			ALL_TRY
			{
				*ppEnum = pThis->Clone()->GetEnumVARIANT().Detach();
			}
			ALL_CATCH(CNavoException & /*to_do: roException */)
			{
				//ned_to_do:
				return DISP_E_EXCEPTION;
			};
			return S_OK;
		};
	END_INTERFACE_PART(EnumVariant)
private:
	SCP<cned_container> m_poContainerSP;
	cned_filter_children m_oFilterChildren;
};

BEGIN_INTERFACE_MAP(cnedaw_container_enumerator, CCmdTarget)
	INTERFACE_PART(cnedaw_container_enumerator, IID_IEnumVARIANT, EnumVariant)
END_INTERFACE_MAP()
	
DELEGATE_UNKNOWN_INTERFACE(cnedaw_container_enumerator, EnumVariant)
	BEGIN_DISPATCH_MAP(cnedaw_container_enumerator, CCmdTarget)
END_DISPATCH_MAP()



LPUNKNOWN cnedaw_container::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP<cnedaw_container_enumerator> poContainerEnumSP = 
			NewSCP(new cnedaw_container_enumerator(NewSCP(_get_container(),true)));
		return poContainerEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

//-----------------------------------------------------------------
// group container
//-----------------------------------------------------------------
cnedaw_group_container::cnedaw_group_container(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poGroupHelper = static_cast<ned::cned_group_helper__*>(poInternalSP.Get());
}

inline ned::cned_group_helper__ * cnedaw_group_container::_get_group_helper()
{
	ASSERT(m_poGroupHelper != NULL);
	return m_poGroupHelper;
}

BEGIN_DISPATCH_MAP(cnedaw_group_container, cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_group_container)
	DISP_PROPERTY_EX(cnedaw_group_container, "keepline", GetForceSingleLineAUTO, SetForceSingleLineAUTO, VT_BOOL)
	DISP_PROPERTY_EX(cnedaw_group_container, "linealign", GetLineAlignmentAUTO, SetLineAlignmentAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BOOL cnedaw_group_container::GetForceSingleLineAUTO()
{
	ALL_TRY
	{
		return _get_group_helper()->get_prop_keepline();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_group_container::SetForceSingleLineAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		_get_group_helper()->set_prop_keepline(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_group_container::GetLineAlignmentAUTO()
{
	ALL_TRY
	{
		return long(_get_group_helper()->get_prop_line_alignment());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_group_container::SetLineAlignmentAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_group_helper()->set_prop_line_alignment(ened_line_alignment(nNewValue));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------------
// paragraph
//-----------------------------------------------------------------
cnedaw_paragraph::cnedaw_paragraph(SCP<ned::cned_element> poInternalSP) :
	cnedaw_group_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poParagraph = static_cast<ned::cned_paragraph*>(poInternalSP.Get());
}

inline ned::cned_paragraph * cnedaw_paragraph::_get_paragraph()
{
	ASSERT(m_poParagraph != NULL);
	return m_poParagraph;
}

BEGIN_DISPATCH_MAP(cnedaw_paragraph, cnedaw_group_container)
	//{{AFX_DISPATCH_MAP(cnedaw_paragraph)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//-----------------------------------------------------------------
// table cell
//-----------------------------------------------------------------
cnedaw_table_cell::cnedaw_table_cell(SCP<ned::cned_element> poInternalSP) :
	cnedaw_group_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTableCell = static_cast<ned::cned_tablecell*>(poInternalSP.Get());
}

inline ned::cned_tablecell * cnedaw_table_cell::_get_table_cell()
{
	ASSERT(m_poTableCell != NULL);
	return m_poTableCell;
}

BEGIN_DISPATCH_MAP(cnedaw_table_cell, cnedaw_group_container)
	//{{AFX_DISPATCH_MAP(cnedaw_table_cell)
	DISP_PROPERTY_EX(cnedaw_table_cell, "colspan", GetColSpanAUTO, SetColSpanAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_table_cell, "rowspan", GetRowSpanAUTO, SetRowSpanAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cnedaw_table_cell::GetColSpanAUTO()
{
	ALL_TRY
	{
		return _get_table_cell()->get_prop_colspan();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_table_cell::SetColSpanAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_table_cell()->set_prop_colspan(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_table_cell::GetRowSpanAUTO()
{
	ALL_TRY
	{
		return _get_table_cell()->get_prop_rowspan();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_table_cell::SetRowSpanAUTO(long nNewValue)
{
	ALL_TRY
	{
		_get_table_cell()->set_prop_rowspan(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// page
//-----------------------------------------------------------------
cnedaw_page::cnedaw_page(SCP<ned::cned_element> poInternalSP) :
	cnedaw_group_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poPage = static_cast<ned::cned_page*>(poInternalSP.Get());
}

inline ned::cned_page * cnedaw_page::_get_page()
{
	ASSERT(m_poPage != NULL);
	return m_poPage;
}

BEGIN_DISPATCH_MAP(cnedaw_page, cnedaw_group_container)
	//{{AFX_DISPATCH_MAP(cnedaw_page)
	DISP_PROPERTY_EX(cnedaw_page, "title", GetTitleAUTO, SetTitleAUTO, VT_BSTR)
	DISP_PROPERTY_EX(cnedaw_page, "caption", GetCaptionAUTO, SetCaptionAUTO, VT_BOOL)
	DISP_FUNCTION(cnedaw_page, "widgets", GetWidgetsAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_page, "header", GetHeaderAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_page, "footer", GetFooterAUTO, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX(cnedaw_page, "displaymode", GetDisplayModeAUTO, SetDisplayModeAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH cnedaw_page::GetWidgetsAUTO()
{
	ALL_TRY
	{
		return _get_page()->_get_caption()->get_my_nedaw()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_page::GetHeaderAUTO()
{
	ALL_TRY
	{
		return _get_page()->_get_header()->get_my_nedaw()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_page::GetFooterAUTO()
{
	ALL_TRY
	{
		return _get_page()->_get_footer()->get_my_nedaw()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

BSTR cnedaw_page::GetTitleAUTO() 
{
	ALL_TRY
	{
		ng_string oTitleString;
		_get_page()->get_prop_title(oTitleString);
		return oTitleString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_page::SetTitleAUTO(LPCTSTR lpszNewTitle) 
{
	ALL_TRY
	{
		_get_page()->set_prop_title(lpszNewTitle);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


BOOL cnedaw_page::GetCaptionAUTO()
{
	ALL_TRY
	{
		return (_get_page()->get_prop_caption() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_page::SetCaptionAUTO(BOOL bNewValue)
{
	ALL_TRY
	{
		_get_page()->set_prop_caption(bNewValue != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_page::GetDisplayModeAUTO()
{
	ALL_TRY
	{
		return (long) _get_page()->get_prop_display_mode();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_page::SetDisplayModeAUTO(long nNewMode)
{
	ALL_TRY
	{
		_get_page()->set_prop_display_mode((epage_display_mode)nNewMode);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// option button
//-----------------------------------------------------------------
cnedaw_option_button_::cnedaw_option_button_(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poOptionButton = static_cast<ned::cned_option_button_*>(poInternalSP.Get());
}

inline ned::cned_option_button_ * cnedaw_option_button_::_get_option_button()
{
	ASSERT(m_poOptionButton != NULL);
	return m_poOptionButton;
}

BEGIN_DISPATCH_MAP(cnedaw_option_button_, cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_option_button_)
	DISP_PROPERTY_EX(cnedaw_option_button_, "colspan", GetColSpanAUTO, SetColSpanAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cnedaw_option_button_::GetColSpanAUTO() 
{
	ALL_TRY
	{
		return _get_option_button()->get_prop_colspan();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_option_button_::SetColSpanAUTO(long nNewValue) 
{
	ALL_TRY
	{
		_get_option_button()->set_prop_colspan(nNewValue);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// table
//-----------------------------------------------------------------
cnedaw_table::cnedaw_table(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTable = static_cast<ned::cned_table*>(poInternalSP.Get());
}

inline ned::cned_table * cnedaw_table::_get_table()
{
	ASSERT(m_poTable != NULL);
	return m_poTable;
}

BEGIN_DISPATCH_MAP(cnedaw_table, 	cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_table)
	DISP_FUNCTION(cnedaw_table, "header", GetFirstHeaderSectionAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_table, "nextheader", GetNextHeaderSectionAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_table, "body", GetBodySectionAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_table, "footer", GetLastFooterSectionAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(cnedaw_table, "prevfooter", GetPrevFooterSectionAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH cnedaw_table::GetBodySectionAUTO()
{
	ALL_TRY
	{
		_get_table()->create_all_missing_sections();

		return _get_table()->get_section(ned_tse_body)->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_table::GetFirstHeaderSectionAUTO()
{
	ALL_TRY
	{
		_get_table()->create_all_missing_sections();

		return _get_table()->get_section(ned_tse_first_header)->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_table::GetLastFooterSectionAUTO()
{
	ALL_TRY
	{
		_get_table()->create_all_missing_sections();

		return _get_table()->get_section(ned_tse_last_footer)->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_table::GetNextHeaderSectionAUTO()
{
	ALL_TRY
	{
		if(_get_table()->_get_next_header_ident() == NEDID_NOTHING)
		{
			_get_table()->create_next_header(NEDID_NOTHING);
		}

		return _get_table()->get_next_header()->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_table::GetPrevFooterSectionAUTO()
{
	ALL_TRY
	{
		if(_get_table()->_get_prev_footer_ident() == NEDID_NOTHING)
		{
			_get_table()->create_prev_footer(NEDID_NOTHING);
		}

		return _get_table()->get_prev_footer()->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// grid
//-----------------------------------------------------------------

cnedaw_grid::cnedaw_grid(SCP<ned::cned_element> poInternalSP) :
	cnedaw_table(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poGrid = static_cast<ned::cned_grid*>(poInternalSP.Get());
}

inline ned::cned_grid * cnedaw_grid::_get_grid()
{
	ASSERT(m_poGrid != NULL);
	return m_poGrid;
}

BEGIN_DISPATCH_MAP(cnedaw_grid,cnedaw_table)
	//{{AFX_DISPATCH_MAP(cnedaw_grid)
	DISP_FUNCTION(cnedaw_grid, "pattern", GetPatternSectionAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH cnedaw_grid::GetPatternSectionAUTO()
{
	ALL_TRY
	{
		_get_grid()->create_all_missing_sections();

		return _get_grid()->get_pattern_section()->get_my_nedaw()->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// tabmanager
//-----------------------------------------------------------------
cnedaw_tabmanager::cnedaw_tabmanager(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTabManager = static_cast<ned::cned_tabmanager*>(poInternalSP.Get());
}

inline ned::cned_tabmanager * cnedaw_tabmanager::_get_tabmanager()
{
	ASSERT(m_poTabManager != NULL);
	return m_poTabManager;
}

BEGIN_DISPATCH_MAP(cnedaw_tabmanager, cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_tabmanager)
	DISP_PROPERTY_EX(cnedaw_tabmanager, "activeitem", GetActiveItemAUTO, SetActiveItemAUTO, VT_I4)
	DISP_PROPERTY_EX(cnedaw_tabmanager, "tabsinrow", GetTabsInRowAUTO, SetTabsInRowAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cnedaw_tabmanager::GetActiveItemAUTO()
{
	ALL_TRY
	{
		return 1 + _get_tabmanager()->get_prop_active_item_nr();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_tabmanager::SetActiveItemAUTO(long nItem)
{
	ALL_TRY
	{
		_get_tabmanager()->set_prop_active_item_nr(nItem - 1);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_tabmanager::GetTabsInRowAUTO()
{
	ALL_TRY
	{
		return _get_tabmanager()->get_prop_tabs_in_row();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_tabmanager::SetTabsInRowAUTO(long nCount)
{
	ALL_TRY
	{
		_get_tabmanager()->set_prop_tabs_in_row(nCount);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------------
// tabmanager_item
//-----------------------------------------------------------------
cnedaw_tabmanager_item::cnedaw_tabmanager_item(SCP<ned::cned_element> poInternalSP) :
	cnedaw_paragraph(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTabManagerItem = static_cast<ned::cned_tabmanager_item*>(poInternalSP.Get());
}

inline ned::cned_tabmanager_item * cnedaw_tabmanager_item::_get_tabmanager_item()
{
	ASSERT(m_poTabManagerItem != NULL);
	return m_poTabManagerItem;
}


BEGIN_DISPATCH_MAP(cnedaw_tabmanager_item, cnedaw_paragraph)
	//{{AFX_DISPATCH_MAP(cnedaw_tabmanager_item)
	DISP_PROPERTY_EX(cnedaw_tabmanager_item, "title", GetTitleAUTO, SetTitleAUTO, VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BSTR cnedaw_tabmanager_item::GetTitleAUTO() 
{
	ALL_TRY
	{
		return _get_tabmanager_item()->get_prop_title().AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_tabmanager_item::SetTitleAUTO(LPCTSTR lpszNewTitle) 
{
	ALL_TRY
	{
		_get_tabmanager_item()->set_prop_title(lpszNewTitle);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------
// table section
//-----------------------------------------------------------------
cnedaw_table_section::cnedaw_table_section(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poSection = static_cast<ned::cned_tablesection*>(poInternalSP.Get());
}

inline ned::cned_tablesection * cnedaw_table_section::_get_section()
{
	ASSERT(m_poSection != NULL);
	return m_poSection;
}

BEGIN_DISPATCH_MAP(cnedaw_table_section,cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_table_section)
	DISP_FUNCTION(cnedaw_table_section, "row", GetRowAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(cnedaw_table_section, "count", GetRowCountAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(cnedaw_table_section, "insertnewrow", InsertNewRowAUTO, VT_DISPATCH, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPDISPATCH cnedaw_table_section::GetRowAUTO(long nExternalRowNr)
{
	ALL_TRY
	{
		long nInternalRowNr = nExternalRowNr - 1;
		if(nInternalRowNr < 0 || nInternalRowNr >= _get_section()->get_child_count())
		{
			ThrowNavoException3(ERCO_UITABLE_BAD_ROW_NR,IDPAGE_NOTAVAILABLE,_get_section()->get_ident(),
				nExternalRowNr,"row");
		}
		return _get_section()->get_row(nInternalRowNr)->get_my_nedaw()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_table_section::GetRowCountAUTO()
{
	ALL_TRY
	{
		return _get_section()->get_child_count();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH cnedaw_table_section::InsertNewRowAUTO(long nExternalRowNr)
{
	ALL_TRY
	{
		long nInternalRowNr = nExternalRowNr - 1;
		if(nInternalRowNr < 0 || nInternalRowNr > _get_section()->get_child_count())
		{
			ThrowNavoException3(ERCO_UITABLE_BAD_ROW_NR,IDPAGE_NOTAVAILABLE,_get_section()->get_ident(),
				nExternalRowNr,"insertnewrow");
		}
		ned_ident idAfter = NEDID_NOTHING;
		if(nInternalRowNr >= _get_section()->get_child_count())
		{
			idAfter = NEDID_LAST;
		}
		else
		{
			if(nInternalRowNr > 0)
			{
				idAfter = _get_section()->get_row_ident(nInternalRowNr-1);
			}
			else
			{
				idAfter = NEDID_NOTHING;
			}
		}
		return InsertNewAUTO(_get_section()->get_new_row_type(),idAfter,NEDID_NOTHING);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------------
// grid body section
//-----------------------------------------------------------------
cnedaw_gridbody_section::cnedaw_gridbody_section(SCP<ned::cned_element> poInternalSP) :
	cnedaw_table_section(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poGridBodySection = static_cast<ned::cned_grid_bodysection*>(poInternalSP.Get());
}

inline ned::cned_grid_bodysection * cnedaw_gridbody_section::_get_gridbody_section()
{
	ASSERT(m_poGridBodySection != NULL);
	return m_poGridBodySection;
}

BEGIN_DISPATCH_MAP(cnedaw_gridbody_section,cnedaw_table_section)
	//{{AFX_DISPATCH_MAP(cnedaw_gridbody_section)
	DISP_PROPERTY_EX(cnedaw_gridbody_section, "datarowcount", GetDataRowCountAUTO, SetDataRowCountAUTO, VT_I4)
	DISP_FUNCTION(cnedaw_gridbody_section, "dr2tr", DataRowNr2TableRowNrAUTO, VT_I4, VTS_I4)
	DISP_FUNCTION(cnedaw_gridbody_section, "tr2dr", TableRowNr2DataRowNrAUTO, VT_I4, VTS_I4)
	DISP_PROPERTY_EX(cnedaw_gridbody_section, "firstvisible", GetFirstVisibleAUTO, SetFirstVisibleAUTO, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


void cnedaw_gridbody_section::SetDataRowCountAUTO(long nNewRowCount)
{
	ALL_TRY
	{
		_get_gridbody_section()->set_prop_total_datarows(nNewRowCount);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_gridbody_section::GetDataRowCountAUTO()
{
	ALL_TRY
	{
		return _get_gridbody_section()->get_prop_total_datarows();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_gridbody_section::DataRowNr2TableRowNrAUTO(long nExtDataRowNr)
{
	ALL_TRY
	{
		return _get_gridbody_section()->table_row_nr_from_datarow_nr(nExtDataRowNr - 1) + 1;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_gridbody_section::TableRowNr2DataRowNrAUTO(long nExtTableRowNr)
{
	ALL_TRY
	{
		return _get_gridbody_section()->datarow_nr_from_table_row_nr(nExtTableRowNr - 1) + 1;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cnedaw_gridbody_section::SetFirstVisibleAUTO(long iFirstVisibleDataRow)
{
	ALL_TRY
	{
		_get_gridbody_section()->set_prop_first_visible_datarow(iFirstVisibleDataRow);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long cnedaw_gridbody_section::GetFirstVisibleAUTO()
{
	ALL_TRY
	{
		return _get_gridbody_section()->get_prop_first_visible_datarow();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}


//-----------------------------------------------------------------
// tablerow
//-----------------------------------------------------------------
cnedaw_tablerow::cnedaw_tablerow(SCP<ned::cned_element> poInternalSP) :
	cnedaw_container(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poTableRow = static_cast<ned::cned_tablerow*>(poInternalSP.Get());
}

inline ned::cned_tablerow * cnedaw_tablerow::_get_table_row()
{
	ASSERT(m_poTableRow != NULL);
	return m_poTableRow;
}

BEGIN_DISPATCH_MAP(cnedaw_tablerow,cnedaw_container)
	//{{AFX_DISPATCH_MAP(cnedaw_tablerow)
	DISP_FUNCTION(cnedaw_tablerow, "insertnewcell", InsertNewCellAUTO, VT_DISPATCH, VTS_I4)
	DISP_FUNCTION(cnedaw_tablerow, "count", GetCellCountAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(cnedaw_tablerow, "cell", GetCellAUTO, VT_DISPATCH, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPDISPATCH cnedaw_tablerow::InsertNewCellAUTO(long nExternalElementNr)
{
	ALL_TRY
	{
		long nInternalNr = nExternalElementNr - 1;
		if(nInternalNr < 0 || nInternalNr > _get_table_row()->get_child_count())
		{
			ThrowNavoException3(ERCO_UITABLE_BAD_COL_NR,IDPAGE_NOTAVAILABLE,
				_get_table_row()->get_ident(),nExternalElementNr,"insertnewcell");
		}
		
		ned_ident idAfter = NEDID_NOTHING;
		if(nInternalNr >= _get_table_row()->get_child_count())
		{
			idAfter = NEDID_LAST;
		}
		else
		{
			if(nInternalNr > 0)
			{
				idAfter = _get_table_row()->get_child_ident_on_pos(nInternalNr-1);
			}
			else
			{
				idAfter = NEDID_NOTHING;
			}
		}
		return InsertNewAUTO(ned_tablecell,idAfter,NEDID_NOTHING);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cnedaw_tablerow::GetCellAUTO(long nExternalElementNr)
{
	ALL_TRY
	{
		ned_ident idCell = _get_table_row()->get_child_ident_on_pos(nExternalElementNr-1);
		if(idCell != NEDID_NOTHING)
		{
			return _get_table_row()->get_element_on_ident(idCell)->get_my_nedaw()->GetDispatch(true);
		}
		else
		{
			return NULL;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cnedaw_tablerow::GetCellCountAUTO()
{
	ALL_TRY
	{
		return _get_table_row()->get_child_count();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//-----------------------------------------------------------------
// scrollbar
//-----------------------------------------------------------------
cnedaw_scrollbar::cnedaw_scrollbar(SCP<ned::cned_element> poInternalSP) :
	cnedaw_paragraph(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poScrollBar = static_cast<ned::cned_scrollbar__*>(poInternalSP.Get());
}

inline ned::cned_scrollbar__ * cnedaw_scrollbar::_get_scrollbar()
{
	ASSERT(m_poScrollBar != NULL);
	return m_poScrollBar;
}

BEGIN_DISPATCH_MAP(cnedaw_scrollbar, cnedaw_paragraph)
	//{{AFX_DISPATCH_MAP(cnedaw_scrollbar)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//-----------------------------------------------------------------
// page_caption
//-----------------------------------------------------------------
cnedaw_pagecaption::cnedaw_pagecaption(SCP<ned::cned_element> poInternalSP) :
	cnedaw_paragraph(poInternalSP)
{
	ASSERT(poInternalSP.PointsObject());
	
	m_poPageCaption = static_cast<ned::cned_page_caption*>(poInternalSP.Get());
}

inline ned::cned_page_caption * cnedaw_pagecaption::_get_page_caption()
{
	ASSERT(m_poPageCaption != NULL);
	return m_poPageCaption;
}

BEGIN_DISPATCH_MAP(cnedaw_pagecaption, cnedaw_paragraph)
	//{{AFX_DISPATCH_MAP(cnedaw_pagecaption)
	DISP_FUNCTION(cnedaw_pagecaption, "closepicture", GetClosePicAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

LPDISPATCH cnedaw_pagecaption::GetClosePicAUTO()
{
	ALL_TRY
	{
		return _get_page_caption()->_get_close_pic()->get_my_nedaw()->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
