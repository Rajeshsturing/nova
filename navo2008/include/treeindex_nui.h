/*
	NAVO Enterprise 2003
	2003-03-09

	treearray
		-specjalizowane drzewo dla nui
*/

#ifndef _TREEINDEX_NUI_H_
#define _TREEINDEX_NUI_H_

namespace treearray
{

#ifdef _DEBUG
const long LEAF_BLOCK_SIZE = 16;
const long NODE_BLOCK_SIZE = 16;
#else
const long LEAF_BLOCK_SIZE = 16;
const long NODE_BLOCK_SIZE = 16;
#endif

template<class VALUE>
	class cleaf_block;

//cleaf stores leaf information - VALUE and hierarchy uplink
template<class VALUE>
class cleaf : public CInterface__
{
public:
	cleaf(cleaf_block<VALUE> * poParent,const VALUE & roValue);
	~cleaf();

	const VALUE & get_value() const;
	SCP< cleaf_block<VALUE> > get_parent();

	void update_parent(cleaf_block<VALUE> * poNewParent);

#ifdef _DEBUG
	virtual void print_leaf(long nIndent);
#endif

private:
	VALUE	m_oValue;
	cleaf_block<VALUE> * m_poParent;
};

template<class VALUE>
	class cnode_block;

//cnode_or_leaf_block is base class for blocks (node block or leaf one)

template<class VALUE>
class cnode_or_leaf_block : public CInterface__
{
public:
	cnode_or_leaf_block(cnode_block<VALUE> * poParent);
	~cnode_or_leaf_block();

	virtual const long get_total_count() const = 0;
	virtual SCP< cleaf<VALUE> > lookup_entry(long  & rnIndex) = 0;

	SCP< cnode_block<VALUE> > get_parent();
	void update_parent(cnode_block<VALUE> * poNewParent);

#ifdef _DEBUG
	virtual void print(long nIndent) = 0;
#endif

protected:
	cnode_block<VALUE> * m_poParent;
};

//cleaf_block - leaf block

template<class VALUE>
class cleaf_block : public cnode_or_leaf_block<VALUE>
{
public:
	cleaf_block(cnode_block<VALUE> * poParent);
	~cleaf_block();

	virtual const long get_total_count() const;
	virtual SCP< cleaf<VALUE> > lookup_entry(long & rnIndex);

	SCP< cleaf<VALUE> > insert_at(long nIndex,const VALUE & roValue);
	void remove_at(long nIndex);
	void move_upper_half(cleaf_block<VALUE> * poDestLeafBlock);
	virtual void on_block_split(cleaf_block<VALUE> * poDestLeafBlock,
		SCP< cleaf<VALUE> > & rpoMoveLeafSP);

	long _lookup_position(cleaf<VALUE> * poLeaf);

#ifdef _DEBUG
	virtual void print(long nIndent);
#endif

protected:
	virtual SCP<cleaf<VALUE> > __create_leaf(const VALUE & roValue);

	CArray<SCP< cleaf<VALUE> >,SCP< cleaf<VALUE> > & > m_oLeafArray;
};

//block wêz³ów
template<class VALUE>
class cnode_block : public cnode_or_leaf_block<VALUE>
{
public:
	cnode_block(cnode_block<VALUE> * poParent);
	~cnode_block();

	virtual const long get_total_count() const;
	virtual SCP<cleaf<VALUE> > lookup_entry(long & rnIndex);

	void update_total_count(long nByCnt);
	const long get_entry_count() const;
	
	void insert_after(SCP<cnode_or_leaf_block<VALUE> > & rpoBlockOfInsertSP,SCP<cnode_or_leaf_block<VALUE> > & rpoNewBlockSP);
	void remove_by_ptr(SCP<cnode_or_leaf_block<VALUE> > & rpoBlockToRemoveSP);

	void move_upper_half(cnode_block * poDestNodeBlock);
	virtual void on_block_split(cnode_block<VALUE> * poDestLeafBlock,
		SCP<cnode_or_leaf_block<VALUE> > & rpoMoveBlockSP);
	virtual void on_root_promote(SCP<cnode_or_leaf_block<VALUE> > & rpoOldRootSP);

	long _lookup_position(SCP<cnode_or_leaf_block<VALUE> > & rpoSearchedBlockSP,long * pCountTotals);

#ifdef _DEBUG
	virtual void print(long nIndent);
#endif

	CArray< SCP< cnode_or_leaf_block<VALUE> >, SCP< cnode_or_leaf_block<VALUE> > > m_oBlockArray;
private:
	long m_nTotalChildCount;
};


template<class VALUE>
class ctree_array
{
public:
	ctree_array();
	~ctree_array();

	const long get_count() const;

	virtual SCP< cleaf<VALUE> > insert_at(long nIndex,const VALUE & roValue);
	virtual SCP< cleaf<VALUE> > remove_at(long nIndex);
	virtual void remove_all();

	const VALUE & get_at(long nIndex);
	const VALUE * safe_get_at(long nIndex);

#ifdef _DEBUG
	void print();
#endif

protected:
	virtual void _remove_leaf(SCP<cleaf<VALUE> > poLeafSP,long nIndex);
	void __real_remove_leaf(SCP<cleaf<VALUE> > poLeafSP,long nIndex);

	SCP<cleaf<VALUE> > _lookup_entry(long & rnIndex);
	long _lookup_position(cleaf<VALUE> * poLeaf);

	virtual SCP<cleaf_block<VALUE> > __create_leaf_block(cnode_block<VALUE> * poParent);
	virtual SCP<cnode_block<VALUE> > __create_node_block(cnode_block<VALUE> * poParent);

	SCP<cnode_block<VALUE> >	m_poRootSP;
};

template<class VALUE,class VALUE_ARG>
class cindexed_tree_array : public ctree_array<VALUE>
{
public:
	cindexed_tree_array(UINT nHashTableSize = 599);
	~cindexed_tree_array();

	long get_position(const VALUE & roValue);

	virtual SCP< cleaf<VALUE> > insert_at(long nIndex,const VALUE & roValue);
	virtual SCP< cleaf<VALUE> > remove_at(long nIndex);

	void remove_element(const VALUE & roValue);

	virtual void remove_all();
protected:
	CMap< VALUE, VALUE_ARG, SCP< cleaf<VALUE> >, SCP< cleaf<VALUE> > & > m_oIndexMap;
};

//-------------------------------------------------------------------------------- 
//---------------------- cleaf --------------------------------------------------- 
//-------------------------------------------------------------------------------- 
template<class VALUE>
inline cleaf<VALUE>::cleaf(cleaf_block<VALUE> * poParent,const VALUE & roValue) :
	m_poParent(poParent),
	m_oValue(roValue)
{
}

template<class VALUE>
inline cleaf<VALUE>::~cleaf()
{
}

template<class VALUE>
inline const VALUE & cleaf<VALUE>::get_value() const
{
	return m_oValue;
}

template<class VALUE>
inline SCP< cleaf_block<VALUE> > cleaf<VALUE>::get_parent()
{
	return NewSCP(m_poParent,true);
}

template<class VALUE>
inline void cleaf<VALUE>::update_parent(cleaf_block<VALUE> * poNewParent)
{
	m_poParent = poNewParent;
}

#ifdef _DEBUG
template<class VALUE>
inline void cleaf<VALUE>::print_leaf(long nIndent)
{
	CString oTabString('\t',nIndent);
	//note: you may need modify it depending on VALUE type
	TRACE("%s<leaf>%s</leaf>\n",oTabString,m_oValue);
}
#endif

//-------------------------------------------------------------------------------- 
//---------------------- cnode_or_leaf_block ------------------------------------- 
//-------------------------------------------------------------------------------- 
template<class VALUE>
inline cnode_or_leaf_block<VALUE>::cnode_or_leaf_block(cnode_block<VALUE> * poParent) :
	m_poParent(poParent)
{
}

template<class VALUE>
inline cnode_or_leaf_block<VALUE>::~cnode_or_leaf_block()
{
}

template<class VALUE>
inline SCP<cnode_block<VALUE> > cnode_or_leaf_block<VALUE>::get_parent()
{
	return NewSCP(m_poParent,true);
}

template<class VALUE>
inline void cnode_or_leaf_block<VALUE>::update_parent(cnode_block<VALUE> * poNewParent)
{
	m_poParent = poNewParent;
}

//-------------------------------------------------------------------------------- 
//---------------------- cleaf_block ---------------------------------------------
//--------------------------------------------------------------------------------
template<class VALUE>
inline cleaf_block<VALUE>::cleaf_block(cnode_block<VALUE> * poParent) :
	cnode_or_leaf_block<VALUE>(poParent)
{
}

template<class VALUE>
inline cleaf_block<VALUE>::~cleaf_block()
{
}

template<class VALUE>
inline const long cleaf_block<VALUE>::get_total_count() const
{
	return m_oLeafArray.GetSize();
}

template<class VALUE>
inline SCP<cleaf<VALUE> > cleaf_block<VALUE>::lookup_entry(long & rnIndex)
{
	ASSERT(rnIndex >= 0);
	ASSERT(rnIndex < get_total_count() );
	
	return m_oLeafArray[ rnIndex ];
}

template<class VALUE>
inline long cleaf_block<VALUE>::_lookup_position(cleaf<VALUE>  * poLeaf)
{
	ASSERT(poLeaf != NULL);
	ASSERT(poLeaf->get_parent().Get() == this);

	for(long iter = 0; iter < get_total_count(); iter++)
	{
		if(m_oLeafArray[ iter ].Get() == poLeaf)
		{
			return iter;
		}
	}
	ASSERT(false);
	return -1;
}

template<class VALUE>
SCP< cleaf<VALUE> > cleaf_block<VALUE>::insert_at(long nIndex,const VALUE & roValue)
{
	ASSERT(get_total_count() <= LEAF_BLOCK_SIZE);

	SCP<cleaf<VALUE> > poNewLeafSP = __create_leaf(roValue);
	m_oLeafArray.InsertAt(nIndex,poNewLeafSP);
	
	m_poParent->update_total_count(+1);

	return poNewLeafSP;
}
		
template<class VALUE>
inline void cleaf_block<VALUE>::remove_at(long nIndex)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < get_total_count() );
	
	m_oLeafArray.RemoveAt(nIndex);
	m_poParent->update_total_count(-1);
}

template<class VALUE>
inline void cleaf_block<VALUE>::move_upper_half(cleaf_block * poDestLeafBlock)
{
	ASSERT(poDestLeafBlock != NULL);
	ASSERT(poDestLeafBlock->m_poParent == m_poParent);	//same parent
	ASSERT(poDestLeafBlock->get_total_count() == 0);	//must be empty
	
	long nStartIndex = get_total_count() / 2;
	
	ASSERT(nStartIndex > 0);							//bad LEAF_BLOCK_SIZE value ? bad call ?

	for(long iter = nStartIndex; iter < get_total_count(); iter ++)
	{
		poDestLeafBlock->m_oLeafArray.Add(m_oLeafArray[iter]);
		
		on_block_split(poDestLeafBlock,m_oLeafArray[iter]);

		m_oLeafArray[iter]->update_parent(poDestLeafBlock);
	}
	m_oLeafArray.SetSize(nStartIndex);
}

template<class VALUE>
inline void cleaf_block<VALUE>::on_block_split(cleaf_block<VALUE> *,SCP< cleaf<VALUE> > &)
{
}

#ifdef _DEBUG
template<class VALUE>
inline void cleaf_block<VALUE>::print(long nIndent)
{
	CString oTabString('\t',nIndent);
	++nIndent;
	TRACE("%s<leaf_block total='%d'>\n",oTabString,get_total_count());
	for(long iter = 0; iter < get_total_count(); iter ++)
	{
		m_oLeafArray[iter]->print_leaf(nIndent);
		ASSERT(m_oLeafArray[iter]->get_parent().Get() == this);
	}
	TRACE("%s</leaf_block>\n",oTabString);
}
#endif


template<class VALUE>
inline SCP<cleaf<VALUE> > cleaf_block<VALUE>::__create_leaf(const VALUE & roValue)
{
	return NewSCP(new cleaf<VALUE>(this,roValue));
}

//-------------------------------------------------------------------------------- 
//----------------------- node block ---------------------------------------------
//-------------------------------------------------------------------------------- 
template<class VALUE>
inline cnode_block<VALUE>::cnode_block(cnode_block<VALUE> * poParent) :
	cnode_or_leaf_block<VALUE>(poParent),
	m_nTotalChildCount(0)
{
}

template<class VALUE>
inline cnode_block<VALUE>::~cnode_block()
{
}

template<class VALUE>
inline const long cnode_block<VALUE>::get_total_count() const
{
	return m_nTotalChildCount;
}

template<class VALUE>
inline const long cnode_block<VALUE>::get_entry_count() const
{
	return m_oBlockArray.GetSize();
}

template<class VALUE>
inline void cnode_block<VALUE>::update_total_count(long nByCnt)
{
	m_nTotalChildCount += nByCnt;
	
	ASSERT(m_nTotalChildCount >= 0);

	if(m_poParent)
	{
		m_poParent->update_total_count(nByCnt);
	}
}

template<class VALUE>
inline SCP<cleaf<VALUE> > cnode_block<VALUE>::lookup_entry(long  & rnIndex)
{
	ASSERT(rnIndex >= 0);
	ASSERT(rnIndex < get_total_count() );

	for(long iter = 0; iter < m_oBlockArray.GetSize(); iter++)
	{
		if(m_oBlockArray[iter]->get_total_count() > rnIndex)
		{
			return m_oBlockArray[iter]->lookup_entry(rnIndex);
		}
		rnIndex -= m_oBlockArray[iter]->get_total_count();
	}
	
	ASSERT(false);
	
	rnIndex = -1;
	return SCP<cleaf<VALUE> > ();
}

template<class VALUE>
inline long cnode_block<VALUE>::_lookup_position(SCP<cnode_or_leaf_block<VALUE> > & rpoSearchedBlockSP,
												 long * pCountTotals)
{
	for(long iter = 0; iter < get_entry_count(); iter ++)
	{
		if(m_oBlockArray[iter].Get() == rpoSearchedBlockSP)
		{
			return iter;
		}
		if(pCountTotals != NULL)
		{
			(*pCountTotals) += m_oBlockArray[iter]->get_total_count();
		}
	}
	
	ASSERT(false);
	return -1;
}

template<class VALUE>
inline void cnode_block<VALUE>::insert_after(SCP<cnode_or_leaf_block<VALUE> > & rpoBlockOfInsertSP,
											 SCP<cnode_or_leaf_block<VALUE> > & rpoNewBlockSP)
{
	ASSERT(get_entry_count() <= NODE_BLOCK_SIZE);
	ASSERT(rpoNewBlockSP.PointsObject());
	ASSERT(rpoNewBlockSP->get_parent().operator == (this));

	long nInsertPosition = -1;
	
	if(rpoBlockOfInsertSP.PointsNull())
	{
		nInsertPosition = 0;
	}
	else
	{
		nInsertPosition = 1 + _lookup_position(rpoBlockOfInsertSP,NULL);
		ASSERT(nInsertPosition > 0);
	}
	
	ASSERT(nInsertPosition >= 0);
	m_oBlockArray.InsertAt(nInsertPosition,rpoNewBlockSP);
}

template<class VALUE>
inline void cnode_block<VALUE>::remove_by_ptr(SCP<cnode_or_leaf_block<VALUE> > & rpoBlockToRemoveSP)
{
	ASSERT(rpoBlockToRemoveSP.PointsObject());
	ASSERT(rpoBlockToRemoveSP->get_parent().Get() == this);
	ASSERT(rpoBlockToRemoveSP->get_total_count() == 0);

	for(long iter = 0; iter < get_entry_count(); iter ++)
	{
		if(m_oBlockArray[iter].Get() == rpoBlockToRemoveSP)
		{
			m_oBlockArray.RemoveAt(iter);
			return;
		}
	}

	ASSERT(false);		//invalid remove request
}

template<class VALUE>
inline void cnode_block<VALUE>::move_upper_half(cnode_block<VALUE> * poDestNodeBlock)
{
	ASSERT(poDestNodeBlock != NULL);
	ASSERT(poDestNodeBlock->m_poParent == m_poParent);	//same parent
	ASSERT(poDestNodeBlock->get_total_count() == 0);	//must be empty
	
	long nStartIndex = get_entry_count() / 2;
	ASSERT(nStartIndex > 0);							//bad NODE_BLOCK_SIZE value ? bad call ?

	long nMovedTotalCount = 0;
	for(long iter = nStartIndex; iter < get_entry_count(); iter ++)
	{
		SCP<cnode_or_leaf_block<VALUE> > poMovedBlockSP = m_oBlockArray[iter];
		poDestNodeBlock->m_oBlockArray.Add(poMovedBlockSP);

		on_block_split(poDestNodeBlock,poMovedBlockSP);

		poMovedBlockSP->update_parent(poDestNodeBlock);
		nMovedTotalCount += poMovedBlockSP->get_total_count();
	}
	
	poDestNodeBlock->update_total_count(nMovedTotalCount);
	update_total_count(-nMovedTotalCount);
	
	m_oBlockArray.SetSize(nStartIndex);
}

template<class VALUE>
inline void cnode_block<VALUE>::on_block_split(cnode_block<VALUE> *,SCP<cnode_or_leaf_block<VALUE> > &)
{
}

template<class VALUE>
inline void cnode_block<VALUE>::on_root_promote(SCP<cnode_or_leaf_block<VALUE> > &)
{
}

#ifdef _DEBUG
template<class VALUE>
inline void cnode_block<VALUE>::print(long nIndent)
{
	CString oTabString('\t',nIndent);
	++nIndent;
	TRACE("%s<node_block items='%d' total='%d'>\n",oTabString,get_entry_count(),get_total_count());
	for(long iter = 0; iter < get_entry_count(); iter ++)
	{
		m_oBlockArray[iter]->print(nIndent);
		ASSERT(m_oBlockArray[iter]->get_parent().Get() == this);
	}
	TRACE("%s</node_block>\n",oTabString);
}
#endif

//-------------------------------------------------------------------------------- 
//----------------------------- ctree_array ----------------------------------
//-------------------------------------------------------------------------------- 

template<class VALUE>
inline ctree_array<VALUE>::ctree_array()
{
}

template<class VALUE>
inline ctree_array<VALUE>::~ctree_array()
{
}

template<class VALUE>
inline SCP<cleaf<VALUE> > ctree_array<VALUE>::_lookup_entry(long & rnIndex)
{

#ifdef _DEBUG
	ASSERT(rnIndex >= 0);
	ASSERT(rnIndex < get_count());
	long nOrigIndex = rnIndex;
#endif

	if(m_poRootSP.PointsObject())
	{
		if(m_poRootSP->get_total_count() > rnIndex)
		{
			SCP<cleaf<VALUE> > poLeafSP = m_poRootSP->lookup_entry(rnIndex);

#ifdef _DEBUG
			//test integrity
			ASSERT(_lookup_position(poLeafSP) == nOrigIndex);
#endif

			return poLeafSP;
		}
	}

	rnIndex = -1;
	return SCP<cleaf<VALUE> > ();
}

template<class VALUE>
inline long ctree_array<VALUE>::_lookup_position(cleaf<VALUE> * poLeaf)
{
	ASSERT(poLeaf != NULL);
	SCP<cleaf_block<VALUE> > poLeafBlockSP = poLeaf->get_parent();

	ASSERT(poLeafBlockSP.PointsObject());
	long nPosition = poLeafBlockSP->_lookup_position(poLeaf);

	SCP<cnode_or_leaf_block<VALUE> > poChildBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poLeafBlockSP,true);
	SCP<cnode_block<VALUE> > poParentBlockSP = poLeafBlockSP->get_parent();

	while(poParentBlockSP.PointsObject())
	{
		poParentBlockSP->_lookup_position(poChildBlockSP,&nPosition);
		poChildBlockSP = poParentBlockSP;
		poParentBlockSP = poChildBlockSP->get_parent();
	}
	return nPosition;
}

template<class VALUE>
void ctree_array<VALUE>::_remove_leaf(SCP<cleaf<VALUE> > poLeafSP,long nIndex)
{
	__real_remove_leaf(poLeafSP,nIndex);
}

template<class VALUE>
void ctree_array<VALUE>::__real_remove_leaf(SCP<cleaf<VALUE> > poLeafSP,long nIndex)
{
	SCP<cleaf_block<VALUE> > poLeafBlockSP = poLeafSP->get_parent();
	poLeafBlockSP->remove_at(nIndex);
	if(poLeafBlockSP->get_total_count() == 0)	//empty
	{
		SCP<cnode_block<VALUE> > poParentNodeBlockSP = poLeafBlockSP->get_parent();
		SCP<cnode_or_leaf_block<VALUE> > poChildBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poLeafBlockSP,true);
		poParentNodeBlockSP->remove_by_ptr(poChildBlockSP);

		while(poParentNodeBlockSP->get_total_count() == 0)
		{
			poChildBlockSP = poParentNodeBlockSP;
			poParentNodeBlockSP = poChildBlockSP->get_parent();
			if(poParentNodeBlockSP.PointsNull())
			{
				m_poRootSP = 0;
				return;
			}
			poParentNodeBlockSP->remove_by_ptr(poChildBlockSP);
		}
	}
}

template<class VALUE>
SCP< cleaf<VALUE> > ctree_array<VALUE>::insert_at(long nIndex,const VALUE & roValue)
{
	//here nIndex is valid between [0.. get_count()]

	SCP< cleaf<VALUE> > poNewLeafSP;
	SCP< cleaf<VALUE> > poLeafSP;

	long nTotalCount = get_count();
	
	if(nIndex > nTotalCount)
	{
		//to_do: ERCO_
		throw "invalid index while inserting";
	}

	long nIndexCorrection = 0;
	
	if(nIndex == nTotalCount)	//special case - index entry 'one above'
	{
		if(nTotalCount != 0)
		{
			nIndex--;
			nIndexCorrection++;
			poLeafSP = _lookup_entry(nIndex);
		}
	}
	else
	{
		poLeafSP = _lookup_entry(nIndex);
	}

	if(poLeafSP.PointsObject())
	{
		SCP<cleaf_block<VALUE> > poLeafBlockSP = poLeafSP->get_parent();
		
		poNewLeafSP = poLeafBlockSP->insert_at(nIndex+nIndexCorrection,roValue);

		if(poLeafBlockSP->get_total_count() > LEAF_BLOCK_SIZE)
		{
			//make leaf block split - create new leaf block
			SCP<cnode_block<VALUE> > poParentNodeBlockSP = poLeafBlockSP->get_parent();
			SCP<cleaf_block<VALUE> > poNewLeafBlockSP = __create_leaf_block(poParentNodeBlockSP);

			//move some leafs from poLeafBlock to poNewLeafBlockSP
			poLeafBlockSP->move_upper_half(poNewLeafBlockSP);

			SCP<cnode_or_leaf_block<VALUE> > poOldBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poLeafBlockSP,true);
			SCP<cnode_or_leaf_block<VALUE> > poNewBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poNewLeafBlockSP,true);
			poParentNodeBlockSP->insert_after(poOldBlockSP,poNewBlockSP);

			//propagate split
			while(poParentNodeBlockSP->get_entry_count() > NODE_BLOCK_SIZE)
			{
				poOldBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poParentNodeBlockSP,true);
				poParentNodeBlockSP = poOldBlockSP->get_parent();
				
				if(poParentNodeBlockSP.PointsNull())
				{
					//replace root'a
					ASSERT(poOldBlockSP.Get() == m_poRootSP.Get());
					m_poRootSP = __create_node_block(NULL);
					
					//insert old root as 1-st child in new root's block
					poOldBlockSP->update_parent(m_poRootSP);
					m_poRootSP->update_total_count(poOldBlockSP->get_total_count());
					m_poRootSP->on_root_promote(poOldBlockSP);
					m_poRootSP->insert_after(SCP<cnode_or_leaf_block<VALUE> >(),poOldBlockSP);
					poParentNodeBlockSP = m_poRootSP;
				}
				
				//create new node block
				SCP<cnode_block<VALUE> > poNodeBlockSP = __create_node_block(poParentNodeBlockSP);
				poNewBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poNodeBlockSP,true);

				//move some nodes from poOldBlock to poNewBlock
				cnode_block<VALUE> * poSrcNodeBlock = (cnode_block<VALUE> *)(poOldBlockSP.Get());
				poSrcNodeBlock->move_upper_half(poNodeBlockSP);
				poParentNodeBlockSP->insert_after(poOldBlockSP,poNewBlockSP);
			}
		}
	}
	else
	{
		ASSERT(m_poRootSP.PointsNull());

		m_poRootSP = __create_node_block(NULL);
		SCP<cleaf_block<VALUE> > poLeafBlockSP = __create_leaf_block(m_poRootSP);
		poNewLeafSP = poLeafBlockSP->insert_at(0,roValue);

		SCP<cnode_or_leaf_block<VALUE> > poBlockSP = NewSCP<cnode_or_leaf_block<VALUE> >(poLeafBlockSP,true);
		m_poRootSP->insert_after(SCP<cnode_or_leaf_block<VALUE> >(),poBlockSP);
	}

	ASSERT(poNewLeafSP.PointsObject());
	return poNewLeafSP;
}


template<class VALUE>
inline SCP< cleaf<VALUE> > ctree_array<VALUE>::remove_at(long nIndex)
{
	//here nIndex is valid between [0.. get_count()-1]

	SCP<cleaf<VALUE> > poLeafSP = _lookup_entry(nIndex);

	if(poLeafSP.PointsObject())
	{
		_remove_leaf(poLeafSP,nIndex);
	}
	else
	{
		ASSERT(false);
		//to_do: ERCO_
		throw "invalid index specified while removing";
	}

	return poLeafSP;
}

template<class VALUE>
inline void ctree_array<VALUE>::remove_all()
{
	m_poRootSP = 0;
}

template<class VALUE>
inline const VALUE * ctree_array<VALUE>::safe_get_at(long nIndex)
{
	//here nIndex is valid between [0.. get_count() - 1]

	SCP<cleaf<VALUE> > poLeafSP = _lookup_entry(nIndex);
	if(poLeafSP.PointsObject())
	{
		return &poLeafSP->get_value();
	}
	else
	{
		return NULL;
	}
}

template<class VALUE>
inline const VALUE & ctree_array<VALUE>::get_at(long nIndex)
{
	const VALUE * pKey = safe_get_at(nIndex);
	if(pKey != NULL)
	{
		return *pKey;
	}
	else
	{
		ASSERT(false);
		//to_do: ERCO_
		throw "invalid index specified while getting";
	}
}

template<class VALUE>
inline const long ctree_array<VALUE>::get_count() const
{
	if(m_poRootSP.PointsObject())
	{
		return m_poRootSP->get_total_count();
	}
	else
	{
		return 0;
	}
}

#ifdef _DEBUG
template<class VALUE>
inline void ctree_array<VALUE>::print()
{
	TRACE("<?xml version=\"1.0\" encoding=\"windows-1250\" ?>\n");
	TRACE("<tree>\n");
	if(m_poRootSP.PointsObject())
	{
		m_poRootSP->print(1);
		ASSERT(m_poRootSP->get_parent() == NULL);
	}
	TRACE("</tree>\n\n");
}
#endif


template<class VALUE>
inline SCP<cleaf_block<VALUE> > ctree_array<VALUE>::__create_leaf_block(cnode_block<VALUE> * poParent)
{
	return NewSCP(new cleaf_block<VALUE>(poParent));
}

template<class VALUE>
inline SCP<cnode_block<VALUE> > ctree_array<VALUE>::__create_node_block(cnode_block<VALUE> * poParent)
{
	return NewSCP(new cnode_block<VALUE>(poParent));
}

//-------------------------------------------------------------------------------- 
//----------------------------- cindexed_tree_array ------------------------------
//-------------------------------------------------------------------------------- 
template<class VALUE,class VALUE_ARG>
inline cindexed_tree_array<VALUE,VALUE_ARG>::cindexed_tree_array(UINT nHashTableSize)
{
	m_oIndexMap.InitHashTable(nHashTableSize);
}

template<class VALUE,class VALUE_ARG>
inline cindexed_tree_array<VALUE,VALUE_ARG>::~cindexed_tree_array()
{
}

template<class VALUE,class VALUE_ARG>
inline void cindexed_tree_array<VALUE,VALUE_ARG>::remove_all()
{
	m_oIndexMap.RemoveAll();
	ctree_array<VALUE>::remove_all();
}

template<class VALUE,class VALUE_ARG>
inline SCP< cleaf<VALUE> > cindexed_tree_array<VALUE,VALUE_ARG>::insert_at(long nIndex,const VALUE & roValue)
{
	SCP< cleaf<VALUE> > poNewLeafSP = ctree_array<VALUE>::insert_at(nIndex,roValue);

	m_oIndexMap[ roValue ] = poNewLeafSP;
	return poNewLeafSP;
}

template<class VALUE,class VALUE_ARG>
inline SCP< cleaf<VALUE> > cindexed_tree_array<VALUE,VALUE_ARG>::remove_at(long nIndex)
{
	SCP< cleaf<VALUE> > poDeletedLeafSP = ctree_array<VALUE>::remove_at(nIndex);

	VERIFY(m_oIndexMap.RemoveKey(poDeletedLeafSP->get_value()));

	return poDeletedLeafSP;
}

template<class VALUE,class VALUE_ARG>
inline void cindexed_tree_array<VALUE,VALUE_ARG>::remove_element(const VALUE & roValue)
{
	SCP< cleaf<VALUE> > poLeafSP;
	if(!m_oIndexMap.Lookup(roValue,poLeafSP))
	{
		//to_do: ERCO_
		throw "invalid value while removing";
	}
	VERIFY(m_oIndexMap.RemoveKey(roValue));
	
	ASSERT(poLeafSP.PointsObject());
	long nIndex = poLeafSP->get_parent()->_lookup_position(poLeafSP);
	_remove_leaf(poLeafSP,nIndex);
}

template<class VALUE,class VALUE_ARG>
inline long cindexed_tree_array<VALUE,VALUE_ARG>::get_position(const VALUE & roValue)
{
	SCP< cleaf<VALUE> > poLeafSP;
	if(!m_oIndexMap.Lookup(roValue,poLeafSP))
	{
		return -1;
	}
	return _lookup_position(poLeafSP);
}

}		//end of namespace treearray

#else
	#error __FILE__ already included
#endif
