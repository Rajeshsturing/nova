/*
	NAVO Sp. z o.o. (2002)
	05.08.2002

	NAVO Enterprise

	class:
		cndoc_page__ - abstrakcyjna "strona" bazowa
		czêœæ AUTOMATION
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\include\internal_h1000.h"
#include "..\include\navothread.h"		//navo thread
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\navogal\ngal_iface.h"		//graphics

#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "common_pageman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//{{AFX_MSG_MAP(cndoc_page__)
//}}AFX_MSG_MAP

#ifdef DISP_FUNCTION
#undef DISP_FUNCTION
#define DISP_FUNCTION(a1,a2,a3,a4,a5)	"Nie wolno u¿ywaæ w tej klasie"
#endif

#ifdef DISP_PROPERTY_EX
#undef DISP_PROPERTY_EX
#define DISP_PROPERTY_EX(a1,a2,a3,a4,a5)	"Nie wolno u¿ywaæ w tej klasie"
#endif


BEGIN_DISPATCH_MAP(cndoc_page__, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(cndoc_page__)
	DISP_PROPERTY_EX_ID(cndoc_page__, "result", 200, GetResultAUTO, SetResultAUTO, VT_I4)
	DISP_FUNCTION_ID(cndoc_page__, "domodalauto", 201,  DoModalAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "domodal", 202, DoModalNewAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "print", 204, PrintAUTO, VT_I4, VTS_BSTR VTS_BSTR VTS_DISPATCH)
	DISP_FUNCTION_ID(cndoc_page__, "activate",205, ActivateAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "goback",206, GoBackAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "iscmdenabled",207, IsCommandEnabledAUTO, VT_BOOL, VTS_I4)
	DISP_FUNCTION_ID(cndoc_page__, "get_this", 208, GetRealThisAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "iid", 209, GetPageIIDAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "printpreview", 210, PrintPreviewAUTO,  VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(cndoc_page__, "normalview", 211, NormalViewAUTO,  VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "isprintpreview", 212, IsPrintPreviewAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "getopeninghliclone", 213, GetOpeningHLICloneAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION_ID(cndoc_page__, "printdirect", 214, PrintDirectAUTO, VT_I4, VTS_BSTR VTS_BSTR VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

long cndoc_page__::DoModalAUTO()
{
	ALL_TRY
	{
		return _do_modal(true);	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_page__::DoModalNewAUTO()
{
	ALL_TRY
	{
		return _do_modal(false);	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_page__::GetResultAUTO()
{
	ALL_TRY
	{
		return m_nModalResult;	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_page__::SetResultAUTO(long nNewValue)
{
	ALL_TRY
	{
		m_nModalResult = nNewValue;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_page__::PrintAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig,LPDISPATCH pPrintInfoSinkDispatch) 
{
	ALL_TRY
	{
		neps::cneps_printer_config oPrinterConfig;

		if(lpPrinterConfig != NULL)
		{
			if(*lpPrinterConfig != '\0')
			{
				oPrinterConfig.set_from_string(lpPrinterConfig);
			}
		}
		SCP<IDispatch> poSinkDispatchSP;
		if(pPrintInfoSinkDispatch != NULL)
		{
			poSinkDispatchSP.Attach(pPrintInfoSinkDispatch,true);
		}
		return print(lpPrinterName,oPrinterConfig,poSinkDispatchSP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_page__::PrintDirectAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig,const VARIANT FAR& roVariant)
{
	ALL_TRY
	{
		neps::cneps_printer_config oPrinterConfig;

		if(lpPrinterConfig != NULL)
		{
			if(*lpPrinterConfig != '\0')
			{
				oPrinterConfig.set_from_string(lpPrinterConfig);
			}
		}

		CSmartOleVariant oInputSOV(roVariant);
		
		SCP<IStream> poStreamSP = OpenFileStream_Read_On_SOV(oInputSOV);

		return print_direct(lpPrinterName,oPrinterConfig,poStreamSP);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void cndoc_page__::PrintPreviewAUTO(LPCSTR lpPrinterName,LPCSTR lpPrinterConfig)
{
	ALL_TRY
	{
		neps::cneps_printer_config oPrinterConfig;

		if(lpPrinterConfig != NULL)
		{
			if(*lpPrinterConfig != '\0')
			{
				oPrinterConfig.set_from_string(lpPrinterConfig);
			}
		}
		
		printpreview(lpPrinterName,oPrinterConfig);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_page__::NormalViewAUTO()
{
	ALL_TRY
	{
		normalview();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


BOOL cndoc_page__::IsPrintPreviewAUTO()
{
	ALL_TRY
	{
		return (isprintpreview() != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void cndoc_page__::ActivateAUTO() 
{
	ALL_TRY
	{
		get_integrator()->activate_stack(get_stack());
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


void cndoc_page__::GoBackAUTO()
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poHLISCP = NewSCP(new CHyperLinkInfo());
		poHLISCP->SetNumProp(GVAR_CMD,CMD_INTERNAL_GOBACK);
		poHLISCP->SetNumProp(GVAR_PAGE_IID,get_iid());

		get_integrator()->get_application()->post_command(poHLISCP,false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL cndoc_page__::IsCommandEnabledAUTO(long nCmd)
{
	ALL_TRY
	{
		return is_command_enabled(nCmd) != false;	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


LPDISPATCH cndoc_page__::GetRealThisAUTO() 
{
	ALL_TRY
	{
		return GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long cndoc_page__::GetPageIIDAUTO()
{
	ALL_TRY
	{
		return get_iid();	
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH cndoc_page__::GetOpeningHLICloneAUTO()
{
	ALL_TRY
	{
		SCP<CHyperLinkInfo> poCloneHLISP = NewSCP(new CHyperLinkInfo(*m_poOpeningHLISP));
		return poCloneHLISP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}