/*
	NAVO Enterprise 2003
	2003-04-17

	navo enhanced display (NED)

	ned_htmlwindow
	cned_web - wrapper dla IE

	
*/

#include "stdafx.h"
#include "win32_ned.h"
#include "olecontrol_ned.h"
#include "web_ned.h"


void cned_web::__navigateto()
{
	if(m_poBrowserAppSP.PointsObject())
	{
		m_poBrowserAppSP->Navigate2(&m_oURLSOV.GetVariantRef(),
			&CSmartOleVariant((long)0,VT_I4).GetVariantRef(),
			&CSmartOleVariant("").GetVariantRef(),
			&CSmartOleVariant().GetVariantRef(),
			&CSmartOleVariant("").GetVariantRef());
	}
}
