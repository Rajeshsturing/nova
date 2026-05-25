/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions
	font
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SCP<ng_font> ng_font::create(LPCTSTR lpFontName,long nRawSize,bool bBold,bool bItalic,bool bStrikeThrough,bool bUnderline,SHORT sCharSet)
{
	CBStr oFontNameBStr(lpFontName);
	FONTDESC fd;
	memset( &fd, 0, sizeof(FONTDESC));
	fd.cbSizeofstruct = sizeof(FONTDESC);
	fd.lpstrName = (LPOLESTR)(LPCWSTR)oFontNameBStr;
	fd.cySize.Hi = 0;
	fd.cySize.Lo = nRawSize;
	ASSERT(fd.cySize.Lo > 0);
	
	fd.sWeight = (SHORT)(bBold ? FW_BOLD : FW_NORMAL);
	fd.fItalic = (BYTE)bItalic;
	fd.fStrikethrough = (BYTE) bStrikeThrough;
	fd.fUnderline = (BYTE) bUnderline;
	fd.sCharset = sCharSet;
	SCP<IFont> iFontSCP;
	//OS_API_CALL
	HRESULT hr = ::OleCreateFontIndirect(&fd, IID_IFont, (void **)&iFontSCP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowNavoException(ERCO_STYLEPROV_CANNOT_CREATE_FONT, IDPAGE_NOTAVAILABLE);
	}
	return NewSCP(new ng_font(iFontSCP,bItalic));
}
