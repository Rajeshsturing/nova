/*
	NAVO Enterprise 2003
	2003-05-02

	navo enhanced display (NED)

	window
	
	printing
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\progressgadget.h"
#include "arena_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"
#include "print_sink_info_ned.h"
#include "static_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long STANDARD_SCREEN_DPI = 96;

long cned_sheet_window_view::print(ned_action_paint & roActionPaint,ned_action_result & roResult,const cned_paint_param & roPaintParam,SCP<IDispatch> poPrintInfoSinkSP)
{
	cned_paint_param oStorePaintParam = m_oPaintParam;

	long nStoreCSX = m_nCurrentSheetX;
	long nStoreCSY = m_nCurrentSheetY;

	long nPrintingResult = 0;

	HDC hdcPrinter = roActionPaint.get_dc().get_hdc();
	//OS_API_CALL
	const long nPrintZoom = ::GetDeviceCaps(hdcPrinter,LOGPIXELSY)*100/STANDARD_SCREEN_DPI;
	const long xDeviceTotalWidthPx = ::GetDeviceCaps(hdcPrinter,PHYSICALWIDTH);
	const long yDeviceTotalHeightPx = ::GetDeviceCaps(hdcPrinter,PHYSICALHEIGHT);
	const long xDeviceLeftMarginPx = ::GetDeviceCaps(hdcPrinter,PHYSICALOFFSETX);
	const long yDeviceTopMarginPx = ::GetDeviceCaps(hdcPrinter,PHYSICALOFFSETY);

	DOCINFO documentinfo;
	memset(&documentinfo, 0, sizeof(DOCINFO));
	documentinfo.cbSize = sizeof(DOCINFO);

	ng_rect oPageRect(ng_point(),ng_size(xDeviceTotalWidthPx,yDeviceTotalHeightPx));
	
	ng_string oOfficialTitleString;
	m_poWindow->get_prop_official_title(oOfficialTitleString);
	documentinfo.lpszDocName = oOfficialTitleString;

	SCP<CPerformingDialogHolder> poPDHSP;
	long nPageCounter = 0;
	const long nTotalPages = m_oSheet2DArray.get_col_count() * m_oSheet2DArray.get_row_count();

	get_current_sheet()->invalidate_sheet();

	cned_print_sink_info_wrapper oPSIW(poPrintInfoSinkSP);

	if(oPSIW.is_sink())
	{
		if(!oPSIW.on_start_printing_document(oOfficialTitleString,m_oSheet2DArray.get_col_count(),m_oSheet2DArray.get_row_count()))
		{
			goto finish_printing;
		}
	}
	else
	{
		CString oString;
		//LANGUAGE:PL
		oString = "Rozpoczêto drukowanie " + oOfficialTitleString;
		poPDHSP	= NewSCP(new CPerformingDialogHolder(oString));
	}

	//OS_API_CALL
	::StartDoc(hdcPrinter,&documentinfo);
	
	{
		for(long nY = 0; nY < m_oSheet2DArray.get_row_count(); nY++)
		{
			for(long nX = 0; nX < m_oSheet2DArray.get_col_count(); nX++)
			{
				nPageCounter++;
				bool bPrintThisPage = true;
				
				//symuluje przewijanie - powoduje invalidate
				set_current_sheet_coord(nX,nY);

				if(oPSIW.is_sink())
				{
					switch(oPSIW.on_start_printing_page(nX,nY))
					{
					case PSIW_PRINT:
							; //noop
					break;
					case PSIW_SKIP:
						bPrintThisPage = false;
					break;
					case PSIW_CANCEL:
						goto abort_printing;
					default:
						goto abort_printing;
					}
				}
				else
				{
					CString oString;
					//LANGUAGE:PL
					oString.Format("Trwa drukowanie strony %d z %d",nPageCounter,nTotalPages);
					poPDHSP->SetText(oString);
				}
			
				if(bPrintThisPage)
				{
					::StartPage(hdcPrinter);
					{
						m_oPaintParam = roPaintParam;
						//probably necessary for Win9x
						roActionPaint.get_dc().reinit();

						//store orignal zoom and print with printing zoom
						long nStoreZoom = get_sheet(nX,nY)->get_zoom();
						get_sheet(nX,nY)->set_zoom(nPrintZoom);
						
						//-----------------------------------------------------
						SCP<cned_toplevelpage> poTopLevelPageSP = get_sheet(nX,nY)->get_toplevelpage();
						
						
						//update layout
						get_sheet(nX,nY)->update_layout(roActionPaint,roResult,oPageRect,roPaintParam,MAXLONG);
						
						/* 
						info:
						drukowanie odbywa siê z przesuniêciem, tak ¿e punkt 0,0 nie l¹duje na rogu
						kartki papieru, ale PHYSICALOFFSETX/PHYSICALOFFSETY pixeli od niej
						poniewa¿ chcemy osi¹gn¹æ fizyczna zgodnosc z papierem tzn.
						punkt o wspó³rzêdnych 1cm wzglêdem toppage bêdzie drukowany 1cm od brzegu papieru
						*/
						
						{
							ng_size oStoreArenaPositionSize = poTopLevelPageSP->get_arena_position();
							poTopLevelPageSP->move_to(ng_size(-xDeviceLeftMarginPx,-yDeviceTopMarginPx));
							{
								
								ng_region oRegion(oPageRect);
								poTopLevelPageSP->prepare_paint_region(oRegion);
								cned_painter_ oSheetPainter(roActionPaint.get_dc(),oPageRect);
								oSheetPainter.set_paint_param(roPaintParam);
								poTopLevelPageSP->paint(oSheetPainter);
							}
							poTopLevelPageSP->move_to(oStoreArenaPositionSize);
						}
						
						//restore original values
						get_sheet(nX,nY)->set_zoom(nStoreZoom);
					}
					::EndPage(hdcPrinter);
				}

				oPSIW.on_end_printing_page();
			}
		}
	}
	
	::EndDoc(hdcPrinter);
	goto finish_printing;

abort_printing:
	::AbortDoc(hdcPrinter);

finish_printing:

	oPSIW.on_end_printing_document();

	poPDHSP	= 0;
	
	//restore paint param
	m_oPaintParam = oStorePaintParam;
	m_nCurrentSheetX = nStoreCSX;
	m_nCurrentSheetY = nStoreCSY;
	
	return nPrintingResult;
}

long cned_window::print(ned_action_paint & roActionPaint,ned_action_result & roResult,
						const cned_paint_param & roPaintParam,SCP<IDispatch> poPrintInfoSinkSP)
{
	bool bWasSheetView = (m_eActiveView == wv_sheet);
	if(!bWasSheetView)
	{
		//generate print preview
		print_preview(roActionPaint,roResult,roPaintParam);
	}

	long nResult = m_poSheetViewSP->print(roActionPaint,roResult,roPaintParam,poPrintInfoSinkSP);

	if(!bWasSheetView)
	{
		//switch back to normal view
		normal_view();
	}

	return nResult;
}

void cned_window::print_preview(ned_action_paint & roActionPaint,ned_action_result & roResult,const cned_paint_param & roPaintParam)
{
	if(m_eActiveView == wv_normal)
	{
		//LANGUAGE:PL
		SCP<CPerformingDialogHolder> poPDHSP = 
			NewSCP(new CPerformingDialogHolder("Trwa podzia³ na strony..."));

		cned_page_break_param oPageBreakParam;
		ng_rect oDeclaredMarginsRect = m_poNormalViewSP->get_toplevelpage()->get_prop_extmargins();
		
		ng_xdist xDeclaredWidth = m_poNormalViewSP->get_toplevelpage()->get_prop_extwidth();
		ng_ydist yDeclaredHeight = m_poNormalViewSP->get_toplevelpage()->get_prop_extheight();

		oPageBreakParam.m_oSheetExtMargins = oDeclaredMarginsRect;

		//okreœlamy oPageBreakParam na podstawie parametrów z DC printera
		win32_compute_page_sizes(roActionPaint.get_dc().get_hdc(),
			oPageBreakParam.m_oSheetExtSize,oPageBreakParam.m_oSheetExtMargins,
			oPageBreakParam.m_oPrintableSheetPxSize,
			oPageBreakParam.m_oPrintableSheetExtSize);

		SCP<cned_toplevelpage> poNormalTopPageSP = m_poNormalViewSP->get_toplevelpage();
		bool bNeedSimulateFooter = (poNormalTopPageSP->_get_footer()->get_child_count() == 0);
		if(bNeedSimulateFooter)
		{
			SCP<cned_static> poStaticSP = scp_cast_ui<cned_static>(
				poNormalTopPageSP->_get_footer()->insert_new_element(ned_static,NEDID_NOTHING,NEDID_LAST));
			poStaticSP->set_fixed_properties();
			poStaticSP->set_prop_text("Stymulacja:_)");
		}

		poNormalTopPageSP->set_prop_extmargins(ng_rect(0,0,0,0));
		poNormalTopPageSP->set_prop_extwidth(
				oPageBreakParam.m_oPrintableSheetExtSize.get_dx());

		{
			//wymuszamy renderowanie ca³ego normalnego view z DC printera i rozmiarem strony 
			//(przede wszystkim chodzi o szerokoœæ) ustawionym  na rozmiar drukowalnego obszaru papieru
			//marginesy ustawiamy na 0,0,0,0
			//w ten sposób po u³o¿eniu mamy spójny obszar do "pociêcia" na prostok¹ty
			//które zmieszcz¹ siê w na drukowalnym obszarze papieru
			
			//przy renderowaniu ustaw zoom na proporcjê DPI drukarki do DPI ekranu (=STANDARD_SCREEN_DPI)
			//tryb renderowania = printer

			const long nPrintZoom = ::GetDeviceCaps(roActionPaint.get_dc().get_hdc(),LOGPIXELSY)*100/STANDARD_SCREEN_DPI;
			m_poNormalViewSP->set_zoom(nPrintZoom);

			
			//staraj siê renderowaæ na drukowalnym obszarze
			ng_rect oCompleteArena(ng_point(),
				ng_size(oPageBreakParam.m_oPrintableSheetPxSize.get_dx(),MAXLONG));
		
			cned_paint_param oFullPagePaintParam(roPaintParam);
			oFullPagePaintParam.set_paint_mode(pm_printer);
			
			m_poNormalViewSP->update_layout(roActionPaint,roResult,oCompleteArena,oFullPagePaintParam,MAXLONG);
		}

		//-------------------------------------
		//przywróæ oryginalne ustawienia
		//-------------------------------------

		poNormalTopPageSP->set_prop_extwidth(xDeclaredWidth);
		poNormalTopPageSP->set_prop_extheight(yDeclaredHeight);
		poNormalTopPageSP->set_prop_extmargins(oDeclaredMarginsRect);
		if(bNeedSimulateFooter)
		{
			poNormalTopPageSP->_get_footer()->remove_children(false);
		}
		//-------------------------------------
		//na podstawie renderingu powy¿ej robimy podzia³ na kartki
		//-------------------------------------

		do_page_breaks(oPageBreakParam);
	
		//prze³¹czamy siê do trybu podzia³u na strony 
		m_poSheetViewSP->set_current_sheet_coord(0,0);

		//ned_to_do: roboczo - trzeba bêdzie pamiêtaæ wiêcej info
		//tak aby zasymulowaæ / wytworzyæ printer dc !

		m_poSheetViewSP->m_oPaintParam = roPaintParam;
		m_poSheetViewSP->m_oPaintParam.set_paint_mode(pm_printpreview);

		m_eActiveView = wv_sheet;
	}
}

void cned_window::normal_view()
{
	if(get_active_view_type() == wv_sheet)
	{
		//switch back
		m_eActiveView = wv_normal;
		m_poSheetViewSP->invalidate_view();
		
		//this will free memory
		m_poSheetViewSP = NewSCP(new cned_sheet_window_view(this));
		m_poNormalViewSP->set_zoom(100);
	}
}

//---------------------------------- helper function ------------------------------------------------

void ned::win32_compute_page_sizes(HDC hdcDevice,/*out*/ng_size & roSheetExtSize,
	/*in-out*/ng_rect & roSheetExtMargins,/*out*/ng_size & roSheetPrintablePxSize,
	/*out*/ng_size & roSheetPrintableExtSize)
{
	//OS_API_CALL
	//wszystko w pixelach
	const long xDeviceLeftMarginPx = ::GetDeviceCaps(hdcDevice,PHYSICALOFFSETX);
	const long yDeviceTopMarginPx = ::GetDeviceCaps(hdcDevice,PHYSICALOFFSETY);

	long xDeviceTotalWidthPx = ::GetDeviceCaps(hdcDevice,PHYSICALWIDTH);
	long yDeviceTotalHeightPx = ::GetDeviceCaps(hdcDevice,PHYSICALHEIGHT);

	const long xDevicePrintableWidth = ::GetDeviceCaps(hdcDevice,HORZRES);
	const long yDevicePrintableHeight = ::GetDeviceCaps(hdcDevice,VERTRES);

	if(xDeviceTotalWidthPx == 0)
	{
		xDeviceTotalWidthPx = xDevicePrintableWidth;
	}
	if(yDeviceTotalHeightPx == 0)
	{
		yDeviceTotalHeightPx = yDevicePrintableHeight;
	}
	
	const long xDeviceRigthMarginPx = xDeviceTotalWidthPx - xDevicePrintableWidth - xDeviceLeftMarginPx;
	const long yDeviceBottomMarginPx = yDeviceTotalHeightPx - yDevicePrintableHeight - yDeviceTopMarginPx;

	ASSERT(xDeviceRigthMarginPx >= 0);
	ASSERT(yDeviceBottomMarginPx >= 0);

	const long xDeviceDPIX = ::GetDeviceCaps(hdcDevice,LOGPIXELSX);
	const long yDeviceDPIY = ::GetDeviceCaps(hdcDevice,LOGPIXELSY);
	
	ASSERT(xDeviceDPIX != 0);
	ASSERT(yDeviceDPIY != 0);

	//przeliczamy marginesy urz¹dzenia z pixeli na external units
	const long xExtLeftMargin	= xDeviceLeftMarginPx * 2540 / xDeviceDPIX;
	const long yExtTopMargin	= yDeviceTopMarginPx * 2540 / yDeviceDPIY;
	const long xExtRightMargin	= xDeviceRigthMarginPx * 2540 / xDeviceDPIX;
	const long xExtBottomMargin	= yDeviceBottomMarginPx * 2540 / yDeviceDPIY;

	//ustalamy marginesy z podanych i z dozwolonych przez urz¹dzenie
	roSheetExtMargins.set_left(max(roSheetExtMargins.get_left(),xExtLeftMargin));
	roSheetExtMargins.set_top(max(roSheetExtMargins.get_top(),yExtTopMargin));
	roSheetExtMargins.set_right(max(roSheetExtMargins.get_right(),xExtRightMargin));
	roSheetExtMargins.set_bottom(max(roSheetExtMargins.get_bottom(),xExtBottomMargin));

	//ustalamy rozmiar fizyczny kartki w external units
	roSheetExtSize.set_dx(xDeviceTotalWidthPx * 2540 / xDeviceDPIX);
	roSheetExtSize.set_dy(yDeviceTotalHeightPx * 2540 / yDeviceDPIY);

#ifdef _DEBUG
	{
		ng_xdist dxPrintablePx = roSheetExtSize.get_dx() - roSheetExtMargins.get_left() - roSheetExtMargins.get_right();
		ng_ydist dyPrintablePx = roSheetExtSize.get_dy() - roSheetExtMargins.get_top() - roSheetExtMargins.get_bottom();
	}
#endif

	//ustalamy rozmiar drukowalny w pixelach
	//odejmujemy ustalone marginesy !!
	const long xDeviceEffectiveMarginsX = (roSheetExtMargins.get_left() + roSheetExtMargins.get_right()) * xDeviceDPIX / 2540;
	const long yDeviceEffectiveMarginsY = (roSheetExtMargins.get_top() + roSheetExtMargins.get_bottom()) * yDeviceDPIY / 2540;

	roSheetPrintablePxSize.set_dx(xDeviceTotalWidthPx - xDeviceEffectiveMarginsX);
	roSheetPrintablePxSize.set_dy(yDeviceTotalHeightPx - yDeviceEffectiveMarginsY);

	ASSERT(roSheetPrintablePxSize.get_dx() <= xDevicePrintableWidth);
	ASSERT(roSheetPrintablePxSize.get_dy() <= yDevicePrintableHeight);

	roSheetPrintableExtSize.set_dx(roSheetPrintablePxSize.get_dx() * 2540 / xDeviceDPIX);
	roSheetPrintableExtSize.set_dy(roSheetPrintablePxSize.get_dy() * 2540 / yDeviceDPIY);
}

