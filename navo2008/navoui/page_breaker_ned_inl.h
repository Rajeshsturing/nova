/*
	NAVO Enterprise 2003
	2003-10-02

	navo enhanced display (NED)

	page-breaking classes


*/

#ifndef _PAGE_BREAKER_NED_INL_H_
#define _PAGE_BREAKER_NED_INL_H_

namespace ned
{

inline cpb_split_info_storage::cpb_split_info_storage()
{
}

inline void cpb_split_info_storage::add_vert_split(ng_ycoord yPosition)
{
	m_oVerticalSplitArray.Add(yPosition);
}

inline void cpb_split_info_storage::add_horiz_split(ng_xcoord xPosition)
{
	m_oHorizontalSplitArray.Add(xPosition);
}

inline long cpb_split_info_storage::find_y_area(ng_ycoord yPosition) const
{
	ASSERT(yPosition >= 0);
	long iter = 0; 
	for(iter = 0; iter <= m_oVerticalSplitArray.GetUpperBound(); iter++)
	{
		if(m_oVerticalSplitArray[iter] > yPosition)
		{
			break;
		}
	}
	return iter;
}

inline ng_ycoord cpb_split_info_storage::get_y_area_top(long yAreaY) const
{
	ASSERT(yAreaY >=0 && yAreaY <= m_oVerticalSplitArray.GetUpperBound() + 1);

	if(yAreaY == 0)
	{
		return 0;
	}
	else
	{
		return m_oVerticalSplitArray[ yAreaY - 1] + 1;
	}
}

inline long cpb_split_info_storage::find_x_area(ng_xcoord xPosition) const
{
	ASSERT(xPosition >= 0);
	long iter = 0; 
	for(iter = 0; iter <= m_oHorizontalSplitArray.GetUpperBound(); iter++)
	{
		if(m_oHorizontalSplitArray[iter] > xPosition)
		{
			break;
		}
	}
	return iter;
}

inline ng_xcoord cpb_split_info_storage::get_x_area_right(long xAreaX) const
{
	ASSERT(xAreaX >= 0 && xAreaX <= m_oHorizontalSplitArray.GetUpperBound() + 1);
	if(xAreaX <= m_oHorizontalSplitArray.GetUpperBound())
	{
		return m_oHorizontalSplitArray[ xAreaX ];
	}
	else
	{
		return NED_MAX_WIDTH;
	}
}


inline long cpb_split_info_storage::get_y_count() const
{
	return m_oVerticalSplitArray.GetSize() + 1;
}

inline long cpb_split_info_storage::get_x_count() const
{
	return m_oHorizontalSplitArray.GetSize() + 1;
}

//---------------------------------------------------------------------
inline cpb_split_info::cpb_split_info(cpb_split_info_storage & roStorage,
	ng_ydist dyParentOffset,ng_ycoord yFirstPartMaxBottom,
	ng_ydist dyNextPartMaxHeight,ng_xdist dxNextPartMaxWidth) :
	m_dyParentOffset(dyParentOffset),
	m_yActualBottom(yFirstPartMaxBottom),
	m_yMaxBottom(yFirstPartMaxBottom),
	m_dxNextPartMaxWidth(dxNextPartMaxWidth),
	m_dyNextPartMaxHeight(dyNextPartMaxHeight),
	m_roStorage(roStorage)
{
}

inline void cpb_split_info::next_y_page()
{
	//=====store computed size=========
	m_roStorage.add_vert_split(m_dyParentOffset + m_yActualBottom);

	TRACE(">>>>>> PAGE SPLIT %d / %d <<<<<< \n", m_dyParentOffset + m_yActualBottom,m_dyParentOffset + m_yMaxBottom);

	m_yMaxBottom = m_yActualBottom + m_dyNextPartMaxHeight;
	m_yActualBottom = m_yMaxBottom;
}

inline ng_ycoord cpb_split_info::get_max_bottom() const
{
	return m_yMaxBottom;
}

inline ng_ycoord cpb_split_info::get_actual_bottom() const
{
	return m_yActualBottom;
}

inline ng_ydist cpb_split_info::get_next_part_max_height() const
{
	return m_dyNextPartMaxHeight;
}

inline ng_xdist cpb_split_info::get_next_part_max_width() const
{
	return m_dxNextPartMaxWidth;
}

inline cpb_split_info_storage & cpb_split_info::get_storage()
{
	return m_roStorage;
}

inline void cpb_split_info::update_actual_bottom(ng_ycoord yNewActualBottom)
{
	ASSERT(yNewActualBottom < m_yActualBottom);
	m_yActualBottom = yNewActualBottom;
}

inline void cpb_split_info::update_max_right(ng_xcoord xNewMaxRight)
{
	while(get_storage().get_x_count() * m_dxNextPartMaxWidth < xNewMaxRight)
	{
		get_storage().add_horiz_split(get_storage().get_x_count() * m_dxNextPartMaxWidth);
	}
}

inline void cpb_split_info::propagate(ng_ycoord yActualBottom,ng_ycoord yMaxBottom)
{
	ASSERT(yActualBottom >= m_yActualBottom);
	m_yActualBottom = yActualBottom;

	ASSERT(yMaxBottom >= m_yMaxBottom);
	m_yMaxBottom = yMaxBottom;
}

//------------------------------------------------------------------------
inline cpb_split_manager::cpb_split_manager(cpb_split_info_storage & roStorage) :
	m_roStorage(roStorage)
{
}

inline long cpb_split_manager::find_y_area(ng_ycoord yPosition)
{
	return m_roStorage.find_y_area(yPosition);
}

inline ng_ycoord cpb_split_manager::get_y_area_top(long yAreaY) const
{
	return m_roStorage.get_y_area_top(yAreaY);
}

inline ng_xcoord cpb_split_manager::get_x_area_right(long xAreaX) const
{
	return m_roStorage.get_x_area_right(xAreaX);
}

inline long cpb_split_manager::find_x_area(ng_xcoord xPosition)
{
	return m_roStorage.find_x_area(xPosition);
}

inline cpb_split_info_storage & cpb_split_manager::get_storage()
{
	return m_roStorage;
}


inline void cpb_on_split_event_param::operator =(const cpb_on_split_event_param & roRightParam)
{
	m_oFunctionNameString = roRightParam.m_oFunctionNameString;
	m_poClonedElementSP = NewSCP<cned_element>(roRightParam.m_poClonedElementSP.ConstCastObject(),true);
	
	m_xAreaX = roRightParam.m_xAreaX;
	m_yAreaY = roRightParam.m_yAreaY;
	m_xCount = roRightParam.m_xCount;
	m_yCount = roRightParam.m_yCount;
}

}

#else
	#error __FILE__ already included
#endif
