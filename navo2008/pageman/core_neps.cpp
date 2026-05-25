/*
	NAVO Enterprise 2003
	2003-04-30

	navo enterprise printing support NEPS
		
*/

#include "stdafx.h"
#include <winspool.h>
#include "core_neps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------
// returns a DEVMODE and DEVNAMES for the printer name specified

// dirty code from Q166129
//----------------------------------------------------------------

bool neps_win32::win32_get_printer_dev_xxx(LPCTSTR lpPrinterName,HGLOBAL & rhDevNames,HGLOBAL & rhDevMode)
{
    // Open printer
    HANDLE hPrinter;
    if (!::OpenPrinter(const_cast<LPSTR>(lpPrinterName), &hPrinter, NULL))
	{
		return false;
	}

    // obtain PRINTER_INFO_2 structure and close printer
    DWORD dwBytesReturned, dwBytesNeeded;
    ::GetPrinter(hPrinter, 2/*level=2*/, NULL, 0, &dwBytesNeeded);
    PRINTER_INFO_2* pPrinterInfo2 = reinterpret_cast<PRINTER_INFO_2*>(::GlobalAlloc(GPTR,dwBytesNeeded));

    if (::GetPrinter(hPrinter, 2, (LPBYTE)pPrinterInfo2, dwBytesNeeded,&dwBytesReturned) == 0) 
	{
		::GlobalFree(pPrinterInfo2);
		::ClosePrinter(hPrinter);
       return false;
    }
	::ClosePrinter(hPrinter);

    // Allocate a global handle for DEVMODE
    HGLOBAL hDevMode = ::GlobalAlloc(GHND, sizeof(*pPrinterInfo2->pDevMode) + pPrinterInfo2->pDevMode->dmDriverExtra);
    ASSERT(hDevMode);
    
	DEVMODE* pDevMode = reinterpret_cast<DEVMODE*>(::GlobalLock(hDevMode));
    ASSERT(pDevMode);

    // copy DEVMODE data from PRINTER_INFO_2::pDevMode
    memcpy(pDevMode, pPrinterInfo2->pDevMode, sizeof(*pPrinterInfo2->pDevMode) + pPrinterInfo2->pDevMode->dmDriverExtra);
    ::GlobalUnlock(hDevMode);

    // Compute size of DEVNAMES structure from PRINTER_INFO_2's data
    DWORD drvNameLen = lstrlen(pPrinterInfo2->pDriverName)+1;  // driver name
    DWORD ptrNameLen = lstrlen(pPrinterInfo2->pPrinterName)+1; // printer name
    DWORD porNameLen = lstrlen(pPrinterInfo2->pPortName)+1;    // port name

    // Allocate a global handle big enough to hold DEVNAMES.
    HGLOBAL hDevNames = ::GlobalAlloc(GHND, sizeof(DEVNAMES) + (drvNameLen + ptrNameLen + porNameLen)*sizeof(TCHAR));
    ASSERT(hDevNames);

    DEVNAMES* pDevNames = reinterpret_cast<DEVNAMES*>(::GlobalLock(hDevNames));
    ASSERT(pDevNames);

    // Copy the DEVNAMES information from PRINTER_INFO_2
    // tcOffset = TCHAR Offset into structure
    int tcOffset = sizeof(DEVNAMES)/sizeof(TCHAR);
    ASSERT(sizeof(DEVNAMES) == tcOffset*sizeof(TCHAR));

    pDevNames->wDriverOffset = WORD(tcOffset);
    memcpy((LPTSTR)pDevNames + tcOffset, pPrinterInfo2->pDriverName,drvNameLen*sizeof(TCHAR));
    tcOffset += drvNameLen;

    pDevNames->wDeviceOffset = WORD(tcOffset);
    memcpy((LPTSTR)pDevNames + tcOffset, pPrinterInfo2->pPrinterName,ptrNameLen*sizeof(TCHAR));
    tcOffset += ptrNameLen;

    pDevNames->wOutputOffset = WORD(tcOffset);
    memcpy((LPTSTR)pDevNames + tcOffset, pPrinterInfo2->pPortName,porNameLen*sizeof(TCHAR));
    pDevNames->wDefault = 0;

    ::GlobalUnlock(hDevNames);
    ::GlobalFree(pPrinterInfo2);   // free PRINTER_INFO_2

    // set the new hDevMode and hDevNames
    rhDevMode = hDevMode;
    rhDevNames = hDevNames;
    return true;
}

//----------------------------------------------------------------
//get all available printer names
//----------------------------------------------------------------

bool neps_win32::win32_get_printers_names(CArray<CString,CString> & roNameArray)
{
	const DWORD dwInfoLevel = 1;
	DWORD dwBytesNeeded = 0;
	DWORD dwEntries = 0;
	
	//query for required size
	if(!::EnumPrinters(PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_LOCAL, NULL,dwInfoLevel,NULL,0,
		&dwBytesNeeded,&dwEntries))
	{
		CArray<BYTE,BYTE> oBuffer;
		oBuffer.SetSize(dwBytesNeeded);
		//get real data
		if(!::EnumPrinters(PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_LOCAL, NULL,dwInfoLevel,
			oBuffer.GetData(),dwBytesNeeded,&dwBytesNeeded,&dwEntries))
		{
			return false;
		}
		ASSERT(dwBytesNeeded <= DWORD(oBuffer.GetSize()));
		ASSERT(dwInfoLevel == 1);	//

		PRINTER_INFO_1 * pPrinterInfo1 = reinterpret_cast<PRINTER_INFO_1 *>(oBuffer.GetData());

		for(DWORD dwIter = 0; dwIter < dwEntries; dwIter++)
		{
			roNameArray.Add(CString(pPrinterInfo1[dwIter].pName));
		}
	}
	return true;
}

static BOOL WINAPI virtual_GetDefaultPrinter_W2K(LPTSTR p1,LPDWORD p2)
{
	CDLLHolder oDLLHolder(_T("WINSPOOL.DRV"));
	BOOL (WINAPI *pFunction)(LPTSTR,LPDWORD);

	if(oDLLHolder.SafeGetProcAddress(pFunction, _T("GetDefaultPrinterA") ) != ERROR_SUCCESS)
	{
		return false;
	}

	return pFunction(p1,p2);
}

//----------------------------------------------------------------
//get default printer name
//
// dirty code from Q246772
//----------------------------------------------------------------

bool neps_win32::win32_get_default_printer_name(CString & roNameString)
{
	CWinVersion oWindowsVersion;
	 
	// If Windows 95 or 98, use EnumPrinters...
	if(oWindowsVersion.GetVersion() == CWinVersion::Win95 || oWindowsVersion.GetVersion() == CWinVersion::Win98)
	{
		DWORD dwBytesNeeded = 0;
		DWORD dwBytesReturned = 0;

		// The first EnumPrinters() tells you how big our buffer should
		// be in order to hold ALL of PRINTER_INFO_2. Note that this will
		// usually return FALSE. This only means that the buffer (the 4th
		// parameter) was not filled in. You don't want it filled in here...
		::EnumPrinters(PRINTER_ENUM_DEFAULT,NULL,2/*level*/,NULL,0,&dwBytesNeeded,&dwBytesReturned);
		if(dwBytesNeeded == 0)
		{
			return false; //no default printer ?
		}

		CArray<BYTE,BYTE> oBuffer;
		oBuffer.SetSize(dwBytesNeeded);
		if(!::EnumPrinters(PRINTER_ENUM_DEFAULT,NULL,2/*level*/,oBuffer.GetData(),dwBytesNeeded,&dwBytesNeeded,&dwBytesReturned))
		{
			return false;
		}
		PRINTER_INFO_2 * pPrinterInfo2 = reinterpret_cast<PRINTER_INFO_2 *>(oBuffer.GetData());
		roNameString = pPrinterInfo2->pPrinterName;
		return true;		
	}
	else
	{
		if(oWindowsVersion.GetVersion() == CWinVersion::WinNT)	//NT4.0
		{
			const DWORD dwBufferSize = 512;
			char cIniString[ dwBufferSize ];
			  // Retrieve the default string from Win.ini (the registry).
			  // String will be in form "printername,drivername,portname".
			if (::GetProfileString("windows", "device", ",,,", cIniString, dwBufferSize) <= 0)
			{
				return false;
			}
				
			// Printer name precedes first "," character...
			strtok(cIniString, ",");
			roNameString = cIniString;
			return true;
		}
		else
		{
			if(oWindowsVersion.GetVersion() == CWinVersion::Win2K || oWindowsVersion.GetVersion() == CWinVersion::WinXP)
			{
				const DWORD dwPrnNameLen = 512;
				DWORD dwPrinterNameLen = dwPrnNameLen;
				char cPrinterName[ dwPrnNameLen ];
				if(!virtual_GetDefaultPrinter_W2K(cPrinterName,&dwPrinterNameLen))
				{
					return false;
				}
				roNameString = cPrinterName;
				return true;
			}
		}
	}
	ASSERT(false);	//unknown Win Version
	return false;
}

//----------------------------------------------------------------
// create printer DC on hDevNames and hDevMode
//----------------------------------------------------------------
HDC neps_win32::win32_create_printer_dc(HGLOBAL hDevNames,HGLOBAL hDevMode)
{
	ASSERT(hDevNames != NULL);

	LPDEVNAMES lpDevNames = reinterpret_cast<LPDEVNAMES>(::GlobalLock(hDevNames));
	LPDEVMODE  lpDevMode = (hDevMode != NULL) ? reinterpret_cast<LPDEVMODE>(::GlobalLock(hDevMode)) : NULL;

	if (lpDevNames == NULL)
	{
		return HDC(NULL);
	}

	HDC hDC = ::CreateDC((LPCTSTR)lpDevNames + lpDevNames->wDriverOffset,
					  (LPCTSTR)lpDevNames + lpDevNames->wDeviceOffset,
					  (LPCTSTR)lpDevNames + lpDevNames->wOutputOffset,
					  lpDevMode);

	::GlobalUnlock(hDevNames);
	if (hDevMode != NULL)
	{
		::GlobalUnlock(hDevMode);
	}

	return hDC;
}

//----------------------------------------------------------------
// provide hDevMode according specified settings
//
// dirty code from Q167345
//----------------------------------------------------------------
bool neps_win32::win32_configure_devmode(LPCTSTR lpPrinterName,HWND hParentWindow,const neps::cneps_printer_config & roPrinterConfig,HGLOBAL & rhFinalDevMode)
{
	// Open printer
    HANDLE hPrinter;
    if (!::OpenPrinter(const_cast<LPSTR>(lpPrinterName), &hPrinter, NULL))
	{
		return false;
	}

	// Step 1: Allocate a buffer of the correct size.
	DWORD dwBytesNeeded = ::DocumentProperties(hParentWindow,hPrinter,const_cast<LPSTR>(lpPrinterName),NULL,NULL,0);

    // Allocate a global handle for DEVMODE
    HGLOBAL hDevMode = ::GlobalAlloc(GHND, dwBytesNeeded);
    ASSERT(hDevMode);
    
	DEVMODE* pDevMode = reinterpret_cast<DEVMODE*>(::GlobalLock(hDevMode));
    ASSERT(pDevMode);

   // Step 2: Get the default DevMode for the printer and modify it for our needs.
	DWORD dwResult = ::DocumentProperties(hParentWindow,hPrinter,const_cast<LPSTR>(lpPrinterName),pDevMode,NULL,DM_OUT_BUFFER);
	
	if(dwResult != IDOK)
	{
		::GlobalUnlock(hDevMode);
		::GlobalFree(hDevMode);
		::ClosePrinter(hPrinter);
		return false;
	}

   
   /* Make changes to the DevMode which are supported. */ 
	if(pDevMode->dmFields & DM_ORIENTATION)
	{
		switch(roPrinterConfig.get_orientation())
		{
		case neps::cneps_printer_config::orient_portrait:
		   pDevMode->dmOrientation = DMORIENT_PORTRAIT;
		break;
		case neps::cneps_printer_config::orient_landscape:
		   pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
		break;
		}
	}
	
	if(pDevMode->dmFields & DM_PAPERSIZE)
	{
		if(roPrinterConfig.get_paper_size() != -1)
		{
			pDevMode->dmPaperSize = short(roPrinterConfig.get_paper_size());
		}
	}
	
	if(roPrinterConfig.get_paper_size() == DMPAPER_USER)
	{
		pDevMode->dmFields |= DM_PAPERLENGTH;
		pDevMode->dmFields |= DM_PAPERWIDTH;
		pDevMode->dmPaperLength = short(roPrinterConfig.get_extlength() / 10);
		pDevMode->dmPaperWidth  = short(roPrinterConfig.get_extwidth() / 10);
	}

	if(pDevMode->dmFields & DM_COPIES)
	{
		pDevMode->dmCopies = short(roPrinterConfig.get_copies());
	}

	if(pDevMode->dmFields & DM_PRINTQUALITY)
	{
		switch(roPrinterConfig.get_quality())
		{
		case neps::cneps_printer_config::quality_high:
			pDevMode->dmPrintQuality = DMRES_HIGH;
		break;
		case neps::cneps_printer_config::quality_medium:
			pDevMode->dmPrintQuality = DMRES_MEDIUM;
		break;
		case neps::cneps_printer_config::quality_low:
			pDevMode->dmPrintQuality = DMRES_LOW;
		break;
		case neps::cneps_printer_config::quality_draft:
			pDevMode->dmPrintQuality = DMRES_DRAFT;
		break;
		}
	}

	if(pDevMode->dmFields & DM_COLOR)
	{
		switch(roPrinterConfig.get_color_mode())
		{
		case neps::cneps_printer_config::colormode_color:
			pDevMode->dmColor = DMCOLOR_COLOR;
		break;
		case neps::cneps_printer_config::colormode_mono:
			pDevMode->dmColor = DMCOLOR_MONOCHROME;
		break;
		}
	}

	/*
		Step 3:  Merge the new settings with the old. This gives the driver a chance to update any private
		portions of the DevMode structure.
    */ 

    dwResult = ::DocumentProperties(hParentWindow,hPrinter,const_cast<LPSTR>(lpPrinterName),pDevMode,pDevMode,DM_IN_BUFFER | DM_OUT_BUFFER);
	
	if(dwResult != IDOK)
	{
		::GlobalUnlock(hDevMode);
		::GlobalFree(hDevMode);
		::ClosePrinter(hPrinter);
		return false;
	}

 	::ClosePrinter(hPrinter);
	::GlobalUnlock(hDevMode);
	rhFinalDevMode = hDevMode;

   return true;
}

//----------------------------------------------------------------
//fill cneps_printer_config on DEVMODE
//----------------------------------------------------------------
void neps_win32::win32_init_on_devmode(HGLOBAL hDevMode,neps::cneps_printer_config & roConfig)
{
	DEVMODE* pDevMode = reinterpret_cast<DEVMODE*>(::GlobalLock(hDevMode));
    ASSERT(pDevMode);
	
	if(pDevMode->dmFields & DM_ORIENTATION)
	{
		if(pDevMode->dmOrientation == DMORIENT_PORTRAIT)
		{
			roConfig.portrait();
		}
		else
		{
			if(pDevMode->dmOrientation == DMORIENT_LANDSCAPE)
			{
				roConfig.landscape();
			}
		}
	}

	if(pDevMode->dmFields & DM_PAPERSIZE)
	{
		roConfig.set_paper_size(pDevMode->dmPaperSize);
	}

	if(roConfig.get_paper_size() == DMPAPER_USER)
	{
		roConfig.sheet_dimensions(pDevMode->dmPaperWidth * 10,pDevMode->dmPaperLength * 10);
	}

	if(pDevMode->dmFields & DM_COPIES)
	{
		roConfig.set_copies(pDevMode->dmCopies);
	}

	if(pDevMode->dmFields & DM_PRINTQUALITY)
	{
		switch(pDevMode->dmPrintQuality)
		{
		case DMRES_HIGH:
			roConfig.high();
		break;
		case DMRES_MEDIUM:
			roConfig.set_quality(neps::cneps_printer_config::quality_medium);
		break;
		case DMRES_LOW:
			roConfig.set_quality(neps::cneps_printer_config::quality_low);
		break;
		case DMRES_DRAFT:
			roConfig.draft();
		break;
		default:
			if(pDevMode->dmPrintQuality > 0)
			{
				if(pDevMode->dmPrintQuality <= 150)
				{
					roConfig.draft();
				}
				else
				{
					if(pDevMode->dmPrintQuality <= 300)
					{
						roConfig.set_quality(neps::cneps_printer_config::quality_medium);
					}
					else
					{
						roConfig.high();
					}
				}
			}
		}
	}

	if(pDevMode->dmFields & DM_COLOR)
	{
		if(pDevMode->dmColor == DMCOLOR_COLOR)
		{
			roConfig.set_color_mode(neps::cneps_printer_config::colormode_color);
		}
		else
		{
			if(pDevMode->dmColor == DMCOLOR_MONOCHROME)
			{
				roConfig.set_color_mode(neps::cneps_printer_config::colormode_mono);
			}
		}
	}

	::GlobalUnlock(hDevMode);
}

//----------------------------------------------
//cneps_printer_config
//----------------------------------------------

void cneps_printer_config::get_as_string(CString & roResultString)
{
	roResultString.Format("1\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%c\t%c\t",long(m_eOrientation),
		long(m_DMPaperSize),long(m_nExtLength),long(m_nExtWidth),long(m_nCopies),
		long(m_eQuality),long(m_eColorMode),(m_bPrintBackground ? '1' : '0'),
		(m_bMonoGrayScale ? '1' : '0'));
}

void cneps_printer_config::set_from_string(LPCTSTR lpString)
{
	CStringArray oStringArray;
	SplitString(CString(lpString),oStringArray,'\t',true);

	ASSERT(oStringArray.GetSize() == 10);
	ASSERT(oStringArray[0][0] == '1');	//only suppored format

	m_eOrientation = eOrientation(_ttol(oStringArray[1]));
	m_DMPaperSize = _ttol(oStringArray[2]);
	m_nExtLength = _ttol(oStringArray[3]);
	m_nExtWidth = _ttol(oStringArray[4]);
	m_nCopies = _ttol(oStringArray[5]);
	m_eQuality = eQuality(_ttol(oStringArray[6]));
	m_eColorMode = eColorMode(_ttol(oStringArray[7]));
	m_bPrintBackground = (oStringArray[8][0] == '1');
	m_bMonoGrayScale = (oStringArray[9][0] == '1');
}


