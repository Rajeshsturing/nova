/*
	NAVO Sp. z o.o. (2002)
	24.07.2002

	NAVO Enterprise

	class:
		cndoc_page__ - abstrakcyjna "strona" bazowa
*/

#ifndef _PAGE_NDOC_H_
#define _PAGE_NDOC_H_

class cndoc_integrator;
class cndoc_pagestack;
class nui_action_result;

class cndoc_page__ : public CCmdTargetInterface
{
public:
	cndoc_page__(cndoc_pagestack * poPageStack,cndoc_integrator * poIntegrator,SCP <CHyperLinkInfo> & rpoOpeningHLISP,
		SCP<CNEO_trans> & rpoTransactionSP);
	~cndoc_page__();
	
	const long get_iid() const
	{
		return m_nIID;
	}

	virtual bool process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP);
	virtual bool prepare() = 0;

	virtual void update(){}

	virtual bool on_idle(bool /*bForeground*/)	{ return false;	}

	bool is_in_modal_loop() const
	{
		return (m_nInModal != 0);
	}
	virtual bool is_command_enabled(long /*IdCommand*/)
	{
		return false;
	}
	cndoc_pagestack * get_stack() const
	{
		ASSERT(m_poPageStack != NULL);
		return m_poPageStack;
	}
	SCP<CNEO_trans> get_transaction();

	virtual bool on_action_results(ned_action_result & roActionResults);
	
	virtual long print(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
		SCP<IDispatch> poPrintInfoSinkSP) = 0;
	virtual void printpreview(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig) = 0;
	virtual long print_direct(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
		SCP<IStream> poStreamSP) = 0;
	virtual void normalview() = 0;
	virtual bool isprintpreview() = 0;

	//{{AFX_DISPATCH(cndoc_page__)
	afx_msg void ActivateAUTO();
	afx_msg long GetResultAUTO();
	afx_msg void SetResultAUTO(long nNewValue);
	afx_msg long DoModalAUTO();
	afx_msg long DoModalNewAUTO();
	afx_msg long PrintAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig,LPDISPATCH pPrintInfoSinkDispatch);
	afx_msg long PrintDirectAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig,const VARIANT FAR& roVariant);
	afx_msg void PrintPreviewAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig);
	afx_msg void NormalViewAUTO();
	afx_msg BOOL IsPrintPreviewAUTO();
	afx_msg void GoBackAUTO();
	afx_msg BOOL IsCommandEnabledAUTO(long nCmd);
	afx_msg LPDISPATCH GetRealThisAUTO();
	afx_msg LPDISPATCH GetOpeningHLICloneAUTO();
	afx_msg long GetPageIIDAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	CNavoException & GetErrorStorage();
	cndoc_integrator * get_integrator()
	{
		return m_poIntegrator;
	}

	long _do_modal(bool bAutoPop);

	SCP <CHyperLinkInfo> m_poOpeningHLISP;
	SCP<CNEO_trans>		 m_poTransactionSP;
	long m_nIID;
private:
	long m_nModalResult;
	long m_nInModal;
	cndoc_integrator * m_poIntegrator;
	cndoc_pagestack * m_poPageStack;
};

class cndoc_transaction_switch_holder
{
public:
	cndoc_transaction_switch_holder(CNEO_trans * poCurrentTrans,CNEO_trans * poNewTrans);
	~cndoc_transaction_switch_holder();
private:
	CNEO_trans	*		m_poOldTransaction;
};



#else
	#error __FILE__ already included
#endif

