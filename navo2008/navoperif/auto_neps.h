/*
	NAVO Enterprise 2003
	2003-04-30

	navo enterprise printing support NEPS

	automation shell		
*/

#ifndef _AUTO_NEPS_H_
#define _AUTO_NEPS_H_

//---------------------------------------------------------------------
// main object
//---------------------------------------------------------------------

class CPrintingObjectAUTO : public CCmdTargetInterface
{
public:
	CPrintingObjectAUTO();
	~CPrintingObjectAUTO();
	//{{AFX_DISPATCH(CPrintingObjectAUTO)
	BSTR GetPrintersAUTO();
	BSTR GetDefaultPrinterAUTO();
	LPDISPATCH GetPrintDocConfigAUTO();
	LPDISPATCH GetPrintDocConfigForPrinterAUTO(LPCSTR lpPrinterName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	DECLARE_OLECREATE(CPrintingObjectAUTO)
	DECLARE_DYNCREATE(CPrintingObjectAUTO)
};

//---------------------------------------------------------------------
// printable document configuration
//---------------------------------------------------------------------

class CPrintDocConfigAUTO : public CCmdTargetInterface
{
public:
	CPrintDocConfigAUTO();
	~CPrintDocConfigAUTO();

	static SCP<CPrintDocConfigAUTO> FromIDispatch(LPDISPATCH lpDispatch);

	void init_on_printer_defaults(LPCTSTR lpPrinterName);

	//{{AFX_DISPATCH(CPrintDocConfigAUTO)
	long GetOrientationAUTO();
	void SetOrientationAUTO(long);
	long GetQualityAUTO();
	void SetQualityAUTO(long);
	long GetCopiesAUTO();
	void SetCopiesAUTO(long);
	long GetPaperSizeAUTO();
	void SetPaperSizeAUTO(long);
	long GetLengthAUTO();
	void SetLengthAUTO(long);
	long GetWidthAUTO();
	void SetWidthAUTO(long);
	void LandscapeAUTO();
	void PortraitAUTO();
	BSTR GetAsStringAUTO();
	void SetAsStringAUTO(LPCSTR lpString);
	void QualityHighAUTO();
	void QualityNormalAUTO();
	void QualityDraftAUTO();
	BOOL GetPrintBackgroundAUTO();
	void SetPrintBackgroundAUTO(BOOL bPrint);
	BOOL GetMonoGrayScaleAUTO();
	void SetMonoGrayScaleAUTO(BOOL bMono);
	long GetColoModeAUTO();
	void SetColoModeAUTO(long);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	cneps_printer_config m_oPrinterConfig;
};

#else
	#error __FILE__ already included
#endif

