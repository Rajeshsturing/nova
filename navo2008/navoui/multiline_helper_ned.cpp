/*
	NAVO Enterprise 2003
	2003-03-27

	navo enhanced display (NED)

	multi part text renderer

*/

#include "stdafx.h"
#include "multiline_helper_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//-------------------------------------------------------------------------------------------------
//	multiline_measure_helper -
//	parsuje tekst i wyznacza rozmiar najmniejszego s³owa
//-------------------------------------------------------------------------------------------------

class multiline_measure_helper
{
public:
	multiline_measure_helper(multiline_measurer & roMeasurer);
	void measure(ng_xdist & rxMinWidth,long & rnWeight);
private:
	multiline_measurer & m_roMeasurer;
};

multiline_measure_helper::multiline_measure_helper(multiline_measurer & roMeasurer) :
	m_roMeasurer(roMeasurer)
{
}

void multiline_measure_helper::measure(ng_xdist & rxMinWidth,long & rnWeight)
{
	rxMinWidth = 0;
	rnWeight = m_roMeasurer._get_part_len(0,m_roMeasurer.get_count()-1);

	long nFirstChar;
	long nLastChar;

	multiline_text_parser oParser(m_roMeasurer.get_text(),0);

	while(true)
	{
		switch(oParser.get_next_item(nFirstChar,nLastChar))
		{
		case '\0':
			//finished !
		return;
		case MULTILINE_NEWLINE_CHAR:
		case ' ':
			//ignore
		break;
		default:
			{
				ng_xdist xWordLen = m_roMeasurer._get_part_len(nFirstChar,nLastChar);
				rxMinWidth = max(rxMinWidth,xWordLen);
			}
		}
	}
				
}

void get_multiline_min_size(ng_dc & roDC,SCP<ng_font> & rpoFontSP,LPCTSTR lpText,long nCount,
							   cned_metrics & roMetrics)
{
	ng_xdist dxMinWidth;
	long	 nWeight;

	multiline_measurer oMeasurer(roDC,rpoFontSP,lpText,nCount);
	multiline_measure_helper oMeasureHelper(oMeasurer);
	oMeasureHelper.measure(dxMinWidth,nWeight);

	roMetrics.update(dxMinWidth,oMeasurer.get_line_height(),nWeight);
}

//-------------------------------------------------------------------------------------------------
