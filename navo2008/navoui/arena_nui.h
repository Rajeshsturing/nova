/*
	NAVO Enterprise 2008
	15.07.2002
	
	cnui_arena
		- ca³e srodowisko graficzne
*/

#ifndef _ARENA_NUI_H_
#define _ARENA_NUI_H_

class cnui_arena : public CInterface__
{
	void on_event_size_changed(ng_dc & roDC,const ng_rect & roArenaRect);
	void on_event_olecontrol(const nui_action_oleevent & roActionOleEvent,nui_action_result & roResult);

	void on_compact_memory();
	void set_low_memory_mode(bool bLowMem);
private:
	void _on_after_event(SCP<cnui_window> & rpoWindowSP,const nui_action__ & roAction,nui_action_result & roResult);

	void _paint(ng_dc & roDC,const ng_rect & roPaintRect);
};


#else
	#error __FILE__ already included
#endif
