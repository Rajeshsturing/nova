/*

	NAVO Enterprise 2008

	2003-04-12


	configurable user preferences

*/

#ifndef _CONFIG_USER_PREF_NDOC_H_
#define _CONFIG_USER_PREF_NDOC_H_

class cndoc_config_user_pref
{
public:
	cndoc_config_user_pref();

	bool	m_bFastGraphics;
	bool	m_bWindowsLook;
	long	m_nZoom;
	CSmartOleVariant m_oStyleSOV;
	bool	m_bAnimateWindows;
	ng_color m_oBackColor;
	ng_color m_oBackColor2;
};


//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cndoc_config_user_pref::cndoc_config_user_pref() :
	m_bFastGraphics(false),
	m_bWindowsLook(false),
	m_nZoom(100),
	m_oStyleSOV(long(IDPAGE_DEFAULTSTYLE),VT_I4),
	m_bAnimateWindows(true),
	m_oBackColor(RGB(0xAB,0xBE,0xE6)),
	m_oBackColor2(RGB(0xAB,0xBE,0xE6))
{
}

#else
	#error __FILE__ already included
#endif

