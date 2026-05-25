/*
	NAVO Enterprise 2003
	2003-04-15

	navo enhanced display (NED)

	ned_olecontrol 
	cned_olecontrol - wrapper dla ActiveX

	
*/

#ifndef _OLECONTROL_NED_H_
#define _OLECONTROL_NED_H_

namespace ned
{

class cned_olecontrol_window;

class cned_olecontrol : public cned_win32__
{
public:
	~cned_olecontrol();

	//------ integration support -----------
	SCP<IDispatch> get_olecontrol_dispatch();
	SCP<ITypeInfo> get_olecontrol_event_typeinfo();
	
	//returns event name for dispid (used to call custom handlers)
	bool get_olecontrol_event_name(DISPID dispid,ng_string & roEventNameString);

	//------ property GET -----------------
	const CLSID & get_prop_clsid() const;
	//------ property SET -----------------
	void set_prop_clsid(const CLSID & roCLSID);

	//-------------------------------------------------
	bool is_initialized() const;

	virtual HWND get_embedded_hwnd() const;
//-------------- fill clone -------------- -------------- -------
	virtual void fill_clone(cned_element * poDestination);
protected:
	cned_olecontrol(cned_element_manager * poManager,const ened_element_type eType,const ned_ident idThis);

	virtual void _init_control();
	virtual void _reset_control();

	CLSID	m_oCLSID;

	SCP<IDispatch>			 m_poControlDispatchSP;
	SCP<ITypeInfo>			 m_poEventTypeInfoSP;
	cned_olecontrol_window * m_poControlWindow;

	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

inline void cned_olecontrol::set_prop_clsid(const CLSID & roCLSID)
{
	if(get_prop_clsid() == roCLSID)
	{
		return;
	}

	m_oCLSID = roCLSID;
	_reset_control();
	
	_vse_dirty();
}

inline const CLSID & cned_olecontrol::get_prop_clsid() const
{
	return m_oCLSID;
}

inline bool cned_olecontrol::is_initialized() const
{
	return (m_poControlWindow != NULL);
}

//-------------- fill clone -------------- -------------- -------
inline void cned_olecontrol::fill_clone(cned_element * poDestination)
{
	cned_win32__::fill_clone(poDestination);
	cned_olecontrol * poDestOleCtrl = cast_ui<cned_olecontrol>(poDestination);
	
	poDestOleCtrl->set_prop_clsid(get_prop_clsid());
}

}

#else
	#error __FILE__ already included
#endif
