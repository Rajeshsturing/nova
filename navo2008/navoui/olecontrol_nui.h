/*
	NAVO Enterprise 2008
	26.08.2002
	
	cnui_olecontrol_wrapper
		klasa dla ActiveX control

*/

#ifndef _OLECONTROL_NUI_H_
#define _OLECONTROL_NUI_H_

//---------------------------------------------------------------------
// ogólna klasa do obs³ugi kontrolek ActiveX
//---------------------------------------------------------------------
class cnui_olecontrol_window;
struct IWebBrowser2;

class cnui_olecontrol_wrapper : public cnui_win32__
{
public:
	~cnui_olecontrol_wrapper();

	
	virtual void on_event_olecontrol(const nui_action_oleevent & roActionOleEvent,nui_action_result & roResult);
	virtual void paint(cnui_painter & roPainter);
	virtual ng_ycoord render(cnui_renderer__ & roRenderer);
	//{{AFX_DISPATCH(cnui_olecontrol_wrapper)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
protected:
	virtual HWND get_embedded_hwnd() const;
	virtual void _init_control();
	void _hide_control();

	cnui_olecontrol_wrapper(cnui_element_manager * poManager,const enui_type eType,const nui_ident nIdent);

	cnui_olecontrol_window * m_poWindow;
	CLSID					 m_oCLSID;
	SCP<IDispatch>			 m_poControlDispatchSP;
	SCP<ITypeInfo>			 m_poEventTypeInfoSP;
	CMap<DISPID,DISPID,ng_string,LPCTSTR> m_oEventNameMap;
	bool					 m_bInitialized;

	friend class cnui_element_manager;
};




#else
	#error __FILE__ already included
#endif

