/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	26.01.2003

	class:
		cndoc_navoview_stock_container
		
		container for cndoc_navoview_impl
*/

#ifndef _STOCK_CONTAINER_NDOC_H_
#define _STOCK_CONTAINER_NDOC_H_

class cndoc_event_manager;
class ned::cned_window;

class cndoc_navoview_stock_container : public CCmdTargetInterface
{
public:
	cndoc_navoview_stock_container(CNavoException & roErrorStorage);
	~cndoc_navoview_stock_container();
	void set_window(SCP<ned::cned_window> poWindowSP);

	bool on_action_results(ned::ned_action_result & roActionResults);
	//{{AFX_DISPATCH(cndoc_navoview_stock_container)
	afx_msg void UpdateViewAUTO();
	afx_msg LPDISPATCH GetUIElementAUTO(long Ident);
	afx_msg LPDISPATCH SafeGetUIElementAUTO(long Ident);
	afx_msg long GetPageRootTypeIdAUTO();
	afx_msg long GetPageRootIdObjAUTO();
	afx_msg LPDISPATCH GetUIPageManagerAUTO();
	afx_msg void AddXMLAUTO(long idContainer,const VARIANT FAR & rvarXML);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(DynaDispatch, IDispatch)
		STDMETHOD(GetTypeInfoCount)(UINT*);
        STDMETHOD(GetTypeInfo)(UINT,LCID,ITypeInfo **);
		STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId);
		STDMETHOD(Invoke)(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError);
	END_INTERFACE_PART(DynaDispatch)
protected:
	CNavoException & _error_storage()
	{
		return m_roErrorStorage;
	}
	CDispatchForwarder & _get_page_disp_fwdr()
	{
		return m_oPage_DispatchForwarder;
	}
	SCP<ned::cned_window> _get_window();

	SCP<cndoc_event_manager>	m_poEventManagerSP;
	CDispatchForwarder			m_oPage_DispatchForwarder;
	CNavoException &			m_roErrorStorage;
	SCP<ned::cned_window>			m_poWindowSP;
};

#else
	#error __FILE__ already included
#endif

