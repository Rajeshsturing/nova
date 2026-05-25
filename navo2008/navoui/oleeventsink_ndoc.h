/*
	NAVO Enterprise 2008
	26.08.2002
	
	cndoc_olecontrol_event_sink__
		sink dla eventów z ActiveX control

*/

#ifndef _NDOC_OLECONTROL_EVENT_SINK_H_
#define _NDOC_OLECONTROL_EVENT_SINK_H_

class cndoc_olecontrol_event_sink__
{
public:
	virtual void on_olecontrol_event(long IdCtrl,AFX_EVENT* pEvent) = 0;
};

#else
	#error __FILE__ already included
#endif
