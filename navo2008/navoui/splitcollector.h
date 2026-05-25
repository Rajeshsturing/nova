/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CUISplitCollector - kollektor info o preferowanych miejscach splita
*/

#ifndef _SPLIT_COLLECTOR_H_
#define _SPLIT_COLLECTOR_H_

class CUISplitCollector
{
public:
	CUISplitCollector(){}
	void add_vsplit(long nXCoord,long nItemCount)
	{
		long nCount = 0;
		if(m_VSplitMap.Lookup(nXCoord,nCount))
		{
			nItemCount += nCount;
		}
		m_VSplitMap.SetAt(nXCoord,nItemCount);
	}
	void add_hsplit(long nYCoord,long nItemCount)
	{
		long nCount = 0;
		if(m_HSplitMap.Lookup(nYCoord,nCount))
		{
			nItemCount += nCount;
		}
		m_HSplitMap.SetAt(nYCoord,nItemCount);
	}

	void vsplit_2_array(CArray<hyper,hyper> & roVSplitArray)
	{
		roVSplitArray.SetSize(m_VSplitMap.GetCount());
		POSITION pos = m_VSplitMap.GetStartPosition();
		long iter = 0;
		while(pos)
		{
			long nXCoord;
			long nCount;
			m_VSplitMap.GetNextAssoc(pos,nXCoord,nCount);
			roVSplitArray[ iter ++ ] = longlong(nXCoord,nCount);
		}
	}

	void hsplit_2_array(CArray<hyper,hyper> & roHSplitArray)
	{
		roHSplitArray.SetSize(m_HSplitMap.GetCount());
		POSITION pos = m_HSplitMap.GetStartPosition();
		long iter = 0;
		while(pos)
		{
			long nYCoord;
			long nCount;
			m_HSplitMap.GetNextAssoc(pos,nYCoord,nCount);
			roHSplitArray[ iter ++ ] = longlong(nYCoord,nCount);
		}
	}
private:
	CMap<long,long,long,long> m_VSplitMap;
	CMap<long,long,long,long> m_HSplitMap;
};

#else
	#error __FILE__ already included
#endif
