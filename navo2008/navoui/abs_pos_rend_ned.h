/*
	NAVO Enterprise 2003
	2003-04-14

	navo enhanced display (NED)

	absolute position render manager

	pomocniczy renderer dla elementów z pozycj¹

*/

#ifndef _ABS_POS_REND_NED_H_
#define _ABS_POS_REND_NED_H_

namespace ned
{

class cned_abspos_render_manager
{
public:
	cned_abspos_render_manager();
	void register_child(SCP<cned_element> poElementSP,const ned_position & roPosition,const ng_point & roFlowPoint);
	ng_size render(cned_renderer_ & roRenderer,const ng_rect & roParentRect);
private:
	struct abs_child_info
	{
		abs_child_info();
		abs_child_info(SCP<cned_element> & rpoElementSP,const ned_position & roPosition,
			const ng_point & roFlowPoint);
		void operator = (abs_child_info & roAbsInfo);

		SCP<cned_element> m_poElementSP;
		ned_position	  m_oPosition;
		ng_point		  m_oFlowPoint;
	};
	CArray<abs_child_info,abs_child_info &> m_oAbsoluteChildren;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_abspos_render_manager::abs_child_info::abs_child_info()
{
}

inline cned_abspos_render_manager::abs_child_info::abs_child_info(
	SCP<cned_element> & rpoElementSP,const ned_position & roPosition,const ng_point & roFlowPoint) :
	m_poElementSP(rpoElementSP),
	m_oPosition(roPosition),
	m_oFlowPoint(roFlowPoint)
{
}

inline void cned_abspos_render_manager::abs_child_info::operator = (abs_child_info & roAbsInfo)
{
	m_poElementSP	= roAbsInfo.m_poElementSP;
	m_oPosition		= roAbsInfo.m_oPosition;
	m_oFlowPoint	= roAbsInfo.m_oFlowPoint;
}

inline cned_abspos_render_manager::cned_abspos_render_manager()
{
}

inline void cned_abspos_render_manager::register_child(SCP<cned_element> poElementSP,const ned_position & roPosition,const ng_point & roFlowPoint)
{
	m_oAbsoluteChildren.Add(abs_child_info(poElementSP,roPosition,roFlowPoint));
}

}

#else
	#error __FILE__ already included
#endif
