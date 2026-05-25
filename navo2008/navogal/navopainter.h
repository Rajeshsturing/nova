/*
	NAVO Enterprise 2008
	15.04.2002
	
	CNAVOPainter
*/

#ifndef _NAVO_PAINTER_H_
#define _NAVO_PAINTER_H_

class cngal_painter;

class CNAVOPainter
{
public:
	CNAVOPainter(CNGC & roNGC,const CRepaintArea & roRepaintArea);
	~CNAVOPainter();

	void frame_rect(const _rect & roLURect,long nFramePxWidth,_colordesc framecolor,long nMask);
	void fill_rect_hg(const _rect & roLURect,_colordesc fillcolor1,_colordesc fillcolor2);
	void print_text(const _rect & roLURect,LPCTSTR lpText,long nCount,_colordesc forecolor,_colordesc backcolor,
		SCP<IFont> & rpIFontSP);
private:
	cngal_painter * m_poPainter;
};

#else
	#error __FILE__ already included
#endif
