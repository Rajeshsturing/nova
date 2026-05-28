/*
	NAVO Sp. z o.o. (2002)
		
	NAVO Enterprise

	class:
		cndoc_navopage - strona typu NAVO

	24.07.2002
*/

#ifndef _NAVO_PAGE_NDOC_H_
#define _NAVO_PAGE_NDOC_H_

class ned::cned_window;
class cndoc_event_manager;
class cxmlui_reader_thread;

class cndoc_navopage : public cndoc_page__ 
{
public:
	cndoc_navopage(cndoc_pagestack * poPageStack,cndoc_integrator * poIntegrator,SCP <CHyperLinkInfo> & rpoOpeningHLISP,
		SCP<CNEO_trans> & rpoTransactionSP,SCP<cned_window> poWindowSP);
	~cndoc_navopage();
	virtual void OnFinalRelease();
	virtual bool process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	virtual bool prepare();

	static SCP<cndoc_navopage> FromIDispatch(LPDISPATCH lpDispatch);

	virtual bool on_action_results(ned_action_result & roActionResults);
	virtual void update();

	virtual bool is_command_enabled(long IdCommand);
	virtual bool on_idle(bool bForeground);

	SCP<cned_window> get_window()
	{
		return m_poWindowSP;
	}

	LPDISPATCH GetDynamicDispatch(bool bAddRef = false)
	{
		LPDISPATCH lpDispatch = (IDispatch*)&m_xDynaDispatch;
		if (bAddRef && lpDispatch != NULL)
		{
			lpDispatch->AddRef();
		}
		return lpDispatch;
	}
	
	virtual long print(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
		SCP<IDispatch> poPrintInfoSinkSP);
	virtual void printpreview(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig);
	virtual long print_direct(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
		SCP<IStream> poStreamSP);
	virtual void normalview();
	virtual bool isprintpreview();

	//{{AFX_DISPATCH(cndoc_navopage)
	afx_msg BOOL GetEnableEditAUTO();
	afx_msg void SetEnableEditAUTO(BOOL bNewValue);
	afx_msg BOOL GetCmdEnabledAUTO(long nCmd);
	afx_msg void SetCmdEnabledAUTO(long nCmd, BOOL bNewValue);
	afx_msg LPDISPATCH GetCursorIteratorAUTO();
	afx_msg void SetCursorIteratorAUTO(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetRootAUTO();
	afx_msg void SetRootAUTO(LPDISPATCH newValue);
	afx_msg void UpdateViewAUTO();
	afx_msg LPDISPATCH GetUIElementAUTO(long Ident);
	afx_msg LPDISPATCH SafeGetUIElementAUTO(long Ident);
	afx_msg long GetPageRootTypeIdAUTO();
	afx_msg long GetPageRootIdObjAUTO();
	afx_msg LPDISPATCH GetUIPageManagerAUTO();
	afx_msg long GetSecurityId_Read_AUTO();
	afx_msg long GetSecurityId_Insert_AUTO();
	afx_msg long GetSecurityId_Update_AUTO();
	afx_msg long GetSecurityId_Delete_AUTO();

	afx_msg void SetSecurityId_Read_AUTO(long);
	afx_msg void SetSecurityId_Insert_AUTO(long);
	afx_msg void SetSecurityId_Update_AUTO(long);
	afx_msg void SetSecurityId_Delete_AUTO(long);
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
private:
	void _init_dataobject_etc();
	void _make_full_data_scan();

	bool unprepare();

	void _process_command_copy(SCP <CHyperLinkInfo> & roHLISCP);
	void _process_command_paste(SCP <CHyperLinkInfo> & roHLISCP);

	void _process_command_paste_format(COleDataObject & oOleDataObject, navoCF eFormat, long idPage);
	bool _is_data_in_clipboard();

	bool _preprare_printing_info(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
		HDC & hdcPrinter,cned_paint_param & roPaintParam);

	void _read_chunk();

	CDispatchForwarder & _get_page_disp_fwdr()
	{
		return m_oPage_DispatchForwarder;
	}

	CDispatchForwarder			m_oPage_DispatchForwarder;
	SCP<cned_window>			m_poWindowSP;
	SCP<cndoc_event_manager>	m_poEventManagerSP;
	SCP<CNEO_user>				m_poRootStdObjSP;
	long						m_nRootStdObj_IdObj;		//samo idobj po to, aby by³o dostêpne z dowolnej transakcji
	SCP<CNEO_cursorIterator>	m_poCursorsCollectionIteratorSP;
	bool						m_bNeedFullDataScan;
	bool						m_bCallUnprepare;
	long						m_nUnprepageLevel;
	cxmlui_reader_thread *		m_poReadingThread;
	long						m_nReadingChunkSize;
	DWORD						m_dwLastReadChunkTime;

	friend class cndoc_integrator;
};

#else
	#error __FILE__ already included
#endif

