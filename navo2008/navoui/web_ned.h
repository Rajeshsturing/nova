/*
	NAVO Enterprise 2003
	2003-04-17

	navo enhanced display (NED)

	ned_htmlwindow
	cned_web - wrapper dla IE

	
*/

#ifndef _WEB_NED_H_
#define _WEB_NED_H_

struct IWebBrowser2;

namespace ned
{

class cned_web : public cned_olecontrol
{
public:
	//------ property GET -----------------
	const CSmartOleVariant & get_prop_url() const;
	virtual void get_prop_value(CSmartOleVariant & roSOV);
	//------ property SET -----------------
	void set_prop_url(const CSmartOleVariant & roSOV);
	virtual void set_prop_value(const CSmartOleVariant & roSOV);
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
private:
	cned_web(cned_element_manager * poManager,const ned_ident idThis);

	virtual void _init_control();

	void __navigateto();

	SCP<IWebBrowser2>	m_poBrowserAppSP;
	CSmartOleVariant	m_oURLSOV;
	
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_web::cned_web(cned_element_manager * poManager,const ned_ident idThis) :
	cned_olecontrol(poManager,ned_htmlwindow,idThis)
{
	set_prop_clsid(CLSID_WebBrowser);
}

//------ property GET -----------------
inline const CSmartOleVariant & cned_web::get_prop_url() const
{
	return m_oURLSOV;
}

inline void cned_web::get_prop_value(CSmartOleVariant & roSOV)
{
	roSOV = get_prop_url();
}

//------ property SET -----------------
inline void cned_web::set_prop_url(const CSmartOleVariant & roSOV)
{
	if(get_prop_url() == roSOV)
	{
		return;
	}
	
	m_oURLSOV = roSOV;
	__navigateto();

	_vse_dirty();
}

inline void cned_web::set_prop_value(const CSmartOleVariant & roSOV)
{
	set_prop_url(roSOV);
}


//-------------- fill clone -------------- -------------- -------
inline void cned_web::fill_clone(cned_element * poDestination)
{
	cned_olecontrol::fill_clone(poDestination);
	cned_web * poWebDest = cast_ui<cned_web>(poDestination);
	poWebDest->m_oURLSOV = m_oURLSOV;
}

}

#else
	#error __FILE__ already included
#endif
