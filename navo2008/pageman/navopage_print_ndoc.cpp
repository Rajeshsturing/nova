/*
	NAVO Sp. z o.o. (2003)
		
	NAVO Enterprise

	class:
		cndoc_navopage - strona typu NAVO
		printing support

	2003-05-02
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\navothread.h"		//navo thread
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"
#include "..\navoobj\cursorcollection.h"

#include "common_pageman.h"
#include "navopage_ndoc.h"

#include "navoview_impl_cont_ndoc.h"
#include "mainwindow_ndoc.h"


static HDC _prepare_printer_hdc(LPCTSTR lpPrinterName,HWND hParentWindow,neps::cneps_printer_config & roPrinterConfig)
{
	//nie podano drukarki - pytamy siê u¿ytkownika
	if(_tcsicmp(lpPrinterName, _T("ASK")) == 0  || *lpPrinterName == '\0')
	{
		//OS_API_CALL
		CPrintDialog oPrintDialog(FALSE);

		//u¿ytkownik zrezygnowa³
		if(oPrintDialog.DoModal() != IDOK)
		{
			return HDC(NULL);
		}
	
		return oPrintDialog.GetPrinterDC();
	}

	//podano nazwê - weryfikujemy
	ng_string oPrinterNameString;

	if(_tcsicmp(lpPrinterName,_T("DEFAULT")) == 0)
	{
		if(!neps_win32::win32_get_default_printer_name(oPrinterNameString))
		{
			return HDC(NULL);
		}
	}
	else
	{
		oPrinterNameString = lpPrinterName;
	}

	CArray<CString,CString> oPrinterNamesArray;
	if(!neps_win32::win32_get_printers_names(oPrinterNamesArray))
	{
		return HDC(NULL);
	}
	
	//sprawdzamy czy podana nazwa jest dostêpna
	long nFound = -1;
	for(long iter = 0; iter <= oPrinterNamesArray.GetUpperBound(); iter++)
	{
		if(_tcsicmp(oPrinterNameString,oPrinterNamesArray[iter]) == 0)
		{
			nFound = iter;
			break;
		}
	}
	if(nFound == -1)
	{
		return HDC(NULL);
	}
	
	HGLOBAL hDevNames = HGLOBAL(NULL);
	HGLOBAL hDevMode = HGLOBAL(NULL);
	if(!neps_win32::win32_get_printer_dev_xxx(oPrinterNameString,hDevNames,hDevMode))
	{
		return HDC(NULL);
	}

	::GlobalFree(hDevMode);
	hDevMode = HGLOBAL(NULL); //reset

	HDC hdcPrinter = HDC(NULL);
	
	if(neps_win32::win32_configure_devmode(oPrinterNameString,hParentWindow,roPrinterConfig,hDevMode))
	{
		hdcPrinter = neps_win32::win32_create_printer_dc(hDevNames,hDevMode);
		neps_win32::win32_init_on_devmode(hDevMode,roPrinterConfig);
	}

	::GlobalFree(hDevNames);
	::GlobalFree(hDevMode);

	return hdcPrinter;
}

bool cndoc_navopage::_preprare_printing_info(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
	HDC & rhdcPrinter,cned_paint_param & roPaintParam)
{
	//---------- acquire printer HDC --------------------
	HWND hParentWindow = HWND(NULL);
	if(get_integrator()->get_application()->get_main_window() != NULL)
	{
		hParentWindow = get_integrator()->get_application()->get_main_window()->m_hWnd;
	}

	neps::cneps_printer_config oPrinterConfig(roPrinterConfig);
	rhdcPrinter = _prepare_printer_hdc(lpPrinterName,hParentWindow,oPrinterConfig);
	if(rhdcPrinter == HDC(NULL))
	{
		return false;
	}

	roPaintParam.set_paint_background(oPrinterConfig.get_print_background());

	if(oPrinterConfig.get_color_mode() == neps::cneps_printer_config::colormode_mono)
	{
		roPaintParam.set_color_translation(
			oPrinterConfig.get_mono_grayscale() ? ct_grayscale : ct_blackwhite);
	}
	return true;
}

long cndoc_navopage::print(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig,
						   SCP<IDispatch> poPrintInfoSinkSP)
{
	cned_paint_param oPrintingPaintParam;
	HDC hdcPrinter;
	
	if(!_preprare_printing_info(lpPrinterName,roPrinterConfig,hdcPrinter,oPrintingPaintParam))
	{
		return -1;
	}

	ng_dc oPrinterDC(hdcPrinter);
	oPrintingPaintParam.set_paint_mode(pm_printer);

	ned_action_paint oPrintAction(oPrinterDC);
	ned_action_result oActionResult;

	//--- perform printing ---------------
	long nResult = m_poWindowSP->print(oPrintAction,oActionResult,
		oPrintingPaintParam,poPrintInfoSinkSP);

	::DeleteDC(hdcPrinter);
	return nResult;
}

void cndoc_navopage::printpreview(LPCTSTR lpPrinterName,const neps::cneps_printer_config & roPrinterConfig)
{
	if(isprintpreview())		//ned_to_do: teraz prze³¹cza na zmianê - powinno byæ to regulowane poziom wy¿ej
	{
		normalview();
	}
	else
	{
		cned_paint_param oPrintingPaintParam;
		HDC hdcPrinter;
		
		if(!_preprare_printing_info(lpPrinterName,roPrinterConfig,hdcPrinter,oPrintingPaintParam))
		{
			return;
		}
	
		ng_dc oPrinterDC(hdcPrinter);
		oPrintingPaintParam.set_paint_mode(pm_printpreview);
		ned_action_paint oPrintAction(oPrinterDC);
		ned_action_result oActionResult;

		//--- prepare print preview ---
		m_poWindowSP->print_preview(oPrintAction,oActionResult,oPrintingPaintParam);

		::DeleteDC(hdcPrinter);
	}
}

long cndoc_navopage::print_direct(LPCTSTR lpPrinterName,
	const neps::cneps_printer_config & roPrinterConfig,SCP<IStream> poStreamSP)
{
	cned_paint_param oPrintingPaintParam;
	HDC hdcPrinter;
	
	if(!_preprare_printing_info(lpPrinterName,roPrinterConfig,hdcPrinter,oPrintingPaintParam))
	{
		return -1;
	}

	ng_dc oPrinterDC(hdcPrinter);
	oPrintingPaintParam.set_paint_mode(pm_printer);

	ned_action_paint oPrintAction(oPrinterDC);
	ned_action_result oActionResult;

	CStreamHolder oSH(poStreamSP);
	long iCopies = roPrinterConfig.get_copies();
	
	const long BUFFER_SIZE = 16 * 1024;
	long iSizeRead;

	char cBuffer[BUFFER_SIZE + sizeof(WORD)];

	DOCINFO documentinfo;
	memset(&documentinfo, 0, sizeof(DOCINFO));
	
	documentinfo.cbSize = sizeof(DOCINFO);
	documentinfo.lpszDocName = "Wydruk bezpoœredni";
	
	::StartDoc(hdcPrinter,&documentinfo);
	if(iCopies == 0)
	{
		iCopies = 1;
	}

	while(iCopies-- > 0)
	{
		::StartPage(hdcPrinter);
		oSH.SeekToBegin();

      do
      {
		 iSizeRead = oSH.Read(cBuffer+sizeof(WORD), BUFFER_SIZE);
         *(WORD*)cBuffer = (WORD)iSizeRead;
         VERIFY( ::Escape(hdcPrinter,PASSTHROUGH,NULL,cBuffer,NULL) == (int) iSizeRead);
      }
      while ( iSizeRead == BUFFER_SIZE );
	  ::EndPage(hdcPrinter);
	}

	::EndDoc(hdcPrinter);
	::DeleteDC(hdcPrinter);
	return 0;
}

void cndoc_navopage::normalview()
{
	m_poWindowSP->normal_view();
}

bool cndoc_navopage::isprintpreview()
{
	if(m_poWindowSP.PointsObject())
	{
		return (m_poWindowSP->get_active_view_type() == wv_sheet);
	}
	return false;
}

