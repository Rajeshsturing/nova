/*
	NAVO Enterprise 2020
	setup application

	loose utilities
*/

#include "stdafx.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "coresetupserv.h"

extern CWindows _g_oWindows;

bool CPictureButton::LoadPicture(UINT nResource, CWnd * pParent)
{
	if (!SubclassDlgItem(nResource, pParent))
	{
		return false;
	};

	CString buttonName;
	GetWindowText(buttonName);
	HPALETTE hPalette;
	m_bitmap.Attach(_g_oWindows.LoadResourceBitmap(NULL, buttonName, &hPalette));
	m_palette.Attach(hPalette);
	SizeToContent();

	return true;
};

void CPictureButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	HBITMAP hBitmap = (HBITMAP)m_bitmap, hOldBitmap;
	HDC hMemDC, hdc;
	BITMAP bm;
	VERIFY(m_bitmap.GetObject(sizeof(bm), &bm) == sizeof(bm));
	hdc = lpDIS->hDC;
	hMemDC = CreateCompatibleDC(hdc);
	SelectPalette(hdc, (HPALETTE)m_palette, FALSE);
	RealizePalette(hdc);
	SelectPalette(hMemDC, (HPALETTE)m_palette, FALSE);
	RealizePalette(hMemDC);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	BitBlt(hdc,0,0,bm.bmWidth,bm.bmHeight,hMemDC,0,0,SRCCOPY);
	SelectObject(hMemDC,hOldBitmap);
	DeleteDC(hMemDC);
};
