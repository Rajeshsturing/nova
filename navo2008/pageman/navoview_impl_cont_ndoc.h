/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	26.01.2003

	class:
		cndoc_navoview_impl_container_ 
		
		container for cndoc_navoview_impl
*/


#ifndef _NAVOVIEW_IMPL_CONT_NDOC_H_
#define _NAVOVIEW_IMPL_CONT_NDOC_H_

class ned::ned_action_result;
class ned::cned_arena;
class cndoc_navoview_impl_container_
{
public:
	virtual bool is_visible() const = 0;
	virtual bool on_action_results(ned::ned_action_result & roActionResults,ned::cned_arena * poSrcArena) = 0;
};

#else
	#error __FILE__ already included
#endif


