/*
	NAVO Enterprise 2003
	2003-04-30

	navo enterprise printing support NEPS

	automation shell		
*/


#include "stdafx.h"
#include "core_neps.h"
#include "auto_neps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------
// main object
//---------------------------------------------------------------------

CPrintingObjectAUTO::CPrintingObjectAUTO()
{
	EnableAutomation();
	AfxOleLockApp();
}

CPrintingObjectAUTO::~CPrintingObjectAUTO()
{
	AfxOleUnlockApp();
}

BEGIN_DISPATCH_MAP(CPrintingObjectAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CPrintingObjectAUTO)
	DISP_FUNCTION(CPrintingObjectAUTO, "printers", GetPrintersAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CPrintingObjectAUTO, "defaultprinter", GetDefaultPrinterAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CPrintingObjectAUTO, "docconfig", GetPrintDocConfigAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CPrintingObjectAUTO, "printerdocconfig", GetPrintDocConfigForPrinterAUTO, VT_DISPATCH, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_DYNCREATE(CPrintingObjectAUTO, CCmdTargetInterface)

// {188cb18f-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CPrintingObjectAUTO, "navoperif.printing",0x188cb18f,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)


BSTR CPrintingObjectAUTO::GetPrintersAUTO()
{
	ALL_TRY
	{
		CString oJoinedString;
		CArray<CString,CString> oPrinterNamesArray;
		if(win32_get_printers_names(oPrinterNamesArray))
		{
			for(long iter = 0; iter < oPrinterNamesArray.GetSize(); iter++)
			{
				if(iter != 0)
				{
					oJoinedString += '\t';
				}
				oJoinedString += oPrinterNamesArray[iter];
			}
		}
		return oJoinedString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BSTR CPrintingObjectAUTO::GetDefaultPrinterAUTO()
{
	ALL_TRY
	{
		CString oString;
		win32_get_default_printer_name(oString);
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CPrintingObjectAUTO::GetPrintDocConfigAUTO()
{
	ALL_TRY
	{
		SCP<CPrintDocConfigAUTO> poPDCSP = NewSCP(new CPrintDocConfigAUTO());
		return poPDCSP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CPrintingObjectAUTO::GetPrintDocConfigForPrinterAUTO(LPCSTR lpPrinterName)
{
	ALL_TRY
	{
		SCP<CPrintDocConfigAUTO> poPDCSP = NewSCP(new CPrintDocConfigAUTO());
		poPDCSP->init_on_printer_defaults(lpPrinterName);
		return poPDCSP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//---------------------------------------------------------------------
// printable document configuration
//---------------------------------------------------------------------
CPrintDocConfigAUTO::CPrintDocConfigAUTO()
{
	EnableAutomation();
	AfxOleLockApp();
}

CPrintDocConfigAUTO::~CPrintDocConfigAUTO()
{
	AfxOleUnlockApp();
}

SCP<CPrintDocConfigAUTO> CPrintDocConfigAUTO::FromIDispatch(LPDISPATCH lpDispatch)
{
	if(lpDispatch == NULL)	//VB nothing
	{
		return SCP<CPrintDocConfigAUTO>();
	}
	else
	{
		CCmdTarget * poCmdTargetPDC = CCmdTarget::FromIDispatch(lpDispatch);
		ASSERT(poCmdTargetPDC);
		CPrintDocConfigAUTO * poPDC = dynamic_cast<CPrintDocConfigAUTO *>(poCmdTargetPDC);
		ASSERT(poPDC);
		return NewSCP(poPDC,true);
	}
}

BEGIN_DISPATCH_MAP(CPrintDocConfigAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CPrintDocConfigAUTO)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "orientation", GetOrientationAUTO, SetOrientationAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "quality", GetQualityAUTO, SetQualityAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "copies", GetCopiesAUTO, SetCopiesAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "paperformat", GetPaperSizeAUTO, SetPaperSizeAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "length", GetLengthAUTO, SetLengthAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "width", GetWidthAUTO, SetWidthAUTO, VT_I4, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "printbackground", GetPrintBackgroundAUTO, SetPrintBackgroundAUTO, VT_BOOL, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "monograyscale", GetMonoGrayScaleAUTO, SetMonoGrayScaleAUTO, VT_BOOL, VTS_NONE)
	DISP_PROPERTY_PARAM(CPrintDocConfigAUTO, "colormode", GetColoModeAUTO, SetColoModeAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "portrait", PortraitAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "landscape", LandscapeAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "high", QualityHighAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "normal", QualityNormalAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "draft", QualityDraftAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CPrintingObjectAUTO, "tostring", GetAsStringAUTO, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CPrintDocConfigAUTO, "fromstring", SetAsStringAUTO, VT_EMPTY, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long CPrintDocConfigAUTO::GetOrientationAUTO()
{
	ALL_TRY
	{
		return long(m_oPrinterConfig.get_orientation());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetOrientationAUTO(long nOrientation)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_orientation(cneps_printer_config::eOrientation(nOrientation));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::LandscapeAUTO()
{
	ALL_TRY
	{
		m_oPrinterConfig.landscape();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::PortraitAUTO()
{
	ALL_TRY
	{
		m_oPrinterConfig.portrait();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long CPrintDocConfigAUTO::GetQualityAUTO()
{
	ALL_TRY
	{
		return long(m_oPrinterConfig.get_quality());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetQualityAUTO(long nQuality)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_quality(cneps_printer_config::eQuality(nQuality));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long CPrintDocConfigAUTO::GetCopiesAUTO()
{
	ALL_TRY
	{
		return m_oPrinterConfig.get_copies();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetCopiesAUTO(long nCopies)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_copies(nCopies);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long CPrintDocConfigAUTO::GetPaperSizeAUTO()
{
	ALL_TRY
	{
		return m_oPrinterConfig.get_paper_size();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetPaperSizeAUTO(long nPaperSizeEnum)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_paper_size(nPaperSizeEnum);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


long CPrintDocConfigAUTO::GetLengthAUTO()
{
	ALL_TRY
	{
		return m_oPrinterConfig.get_extlength();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetLengthAUTO(long nExtLength)
{
	ALL_TRY
	{
		m_oPrinterConfig.sheet_dimensions(m_oPrinterConfig.get_extwidth(),nExtLength);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CPrintDocConfigAUTO::GetWidthAUTO()
{
	ALL_TRY
	{
		return m_oPrinterConfig.get_extwidth();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetWidthAUTO(long nExtWidth)
{
	ALL_TRY
	{
		m_oPrinterConfig.sheet_dimensions(nExtWidth,m_oPrinterConfig.get_extlength());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


BSTR CPrintDocConfigAUTO::GetAsStringAUTO()
{
	ALL_TRY
	{
		CString oString;
		m_oPrinterConfig.get_as_string(oString);
		return oString.AllocSysString();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetAsStringAUTO(LPCSTR lpString)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_from_string(lpString);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::QualityHighAUTO()
{
	ALL_TRY
	{
		m_oPrinterConfig.high();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::QualityNormalAUTO()
{
	ALL_TRY
	{
		m_oPrinterConfig.normal();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::QualityDraftAUTO()
{
	ALL_TRY
	{
		m_oPrinterConfig.draft();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CPrintDocConfigAUTO::GetPrintBackgroundAUTO()
{
	ALL_TRY
	{
		return (m_oPrinterConfig.get_print_background() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetPrintBackgroundAUTO(BOOL bPrintBackground)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_print_background(bPrintBackground != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CPrintDocConfigAUTO::GetMonoGrayScaleAUTO()
{
	ALL_TRY
	{
		return (m_oPrinterConfig.get_mono_grayscale() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetMonoGrayScaleAUTO(BOOL bGrayScale)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_mono_grayscale(bGrayScale != FALSE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CPrintDocConfigAUTO::GetColoModeAUTO()
{
	ALL_TRY
	{
		return long(m_oPrinterConfig.get_color_mode());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::SetColoModeAUTO(long eCM)
{
	ALL_TRY
	{
		m_oPrinterConfig.set_color_mode(cneps_printer_config::eColorMode(eCM));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CPrintDocConfigAUTO::init_on_printer_defaults(LPCTSTR lpPrinterName)
{
	HGLOBAL hDevNames = HGLOBAL(NULL);
	HGLOBAL hDevMode = HGLOBAL(NULL);
	
	if(win32_get_printer_dev_xxx(lpPrinterName,hDevNames,hDevMode))
	{
		win32_init_on_devmode(hDevMode,m_oPrinterConfig);
	}

	::GlobalFree(hDevNames);
	::GlobalFree(hDevMode);
}
