/*
	NAVO Enterprise 2008
	15.07.2002

	CArray2D

		tablica 2d
*/

#ifndef _ARRAY2D_H_
#define _ARRAY2D_H_

#ifdef _ARRAY2D_DIRECT_ON_MEMORY_ALREADY_WORKING_
/*

	define this only when you correct 2D implementation working
	directly on memory
	now there are problems at least with insert_col_at - 
	and type=SCP - object are created and destroyed uneven number times
	which leads to errors

*/

template<class T>
void _init_cell(T * pObject)
{
	memset(pObject,0,sizeof(T));
}

template<class T>
void _clear_cell(T * pObject)
{
	memset(pObject,0,sizeof(T));
}


template<class T,class ARGT>
class CArray2D
{
public:
	CArray2D() :
		m_nRows(0),
		m_nCols(0),
		m_pData(NULL),
		m_nAllocSize(0)
	{
	}
	~CArray2D()
	{
		make_empty();
	}
	long get_row_count() const
	{
		return m_nRows;
	}
	long get_col_count() const
	{
		return m_nCols;
	}
	void add_row();
	void insert_row_at(long nRow);
	void delete_row(long nRow);
	
	void add_col();
	void insert_col_at(long nCol);
	void delete_col(long nCol);

	void init_size(long nRows,long nCols);	//allowed only for use with empty array

	const T & get_at(long nRow,long nCol) const;
	T & get_at(long nRow,long nCol);
	void set_at(long nRow,long nCol,ARGT newElement);

	void make_empty();
protected:
	long _offset(long nRow,long nCol) const
	{
		return (nRow * m_nCols) + nCol;
	}
	long _offset_modif(long nRow,long nCol,long nColums) const
	{
		return (nRow * nColums) + nCol;
	}
	long	m_nRows;
	long	m_nCols;
	T *		m_pData;
	long	m_nAllocSize;
};

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::add_row()
{
	insert_row_at(get_row_count());
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::add_col()
{
	insert_col_at(get_col_count());
}

template<class T,class ARGT>
__forceinline const T & CArray2D<T,ARGT>::get_at(long nRow,long nCol) const
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	ASSERT(_offset(nRow,nCol) >= 0);
	ASSERT(_offset(nRow,nCol) < m_nRows * m_nCols);
	ASSERT(m_pData);
	return m_pData[ _offset(nRow,nCol) ];
}

template<class T,class ARGT>
__forceinline T & CArray2D<T,ARGT>::get_at(long nRow,long nCol)
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	ASSERT(_offset(nRow,nCol) >= 0);
	ASSERT(_offset(nRow,nCol) < m_nRows * m_nCols);
	ASSERT(m_pData);
	return m_pData[ _offset(nRow,nCol) ];
}

template<class T,class ARGT>
__forceinline void CArray2D<T,ARGT>::set_at(long nRow,long nCol,ARGT newElement)
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	ASSERT(_offset(nRow,nCol) >= 0);
	ASSERT(_offset(nRow,nCol) < m_nRows * m_nCols);
	ASSERT(m_pData);
	m_pData[ _offset(nRow,nCol) ] = newElement;
}

static inline long _compute_alloc(long nSize)
{
	return (nSize > 1024) ? (nSize + (nSize / 4)) : (nSize + (nSize / 2));
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::insert_row_at(long nRow)
{
	long nNewSize = (m_nRows + 1) * m_nCols;

	if(nNewSize > m_nAllocSize)
	{
		//need alloc
		m_nAllocSize = _compute_alloc(nNewSize);
		T *	pDestData = (T*) new char[ sizeof(T) * m_nAllocSize ];
		memset(pDestData,0,sizeof(T) * m_nAllocSize);
		//copy rows before insert
		memcpy(&pDestData[ _offset(0,0) ],&m_pData[ _offset(0,0) ],sizeof(T) * m_nCols * nRow);

		//init gap
		for(long iC = 0; iC < m_nCols; iC++)
		{
			_init_cell<T>(&pDestData[ _offset(nRow,iC) ]);
		}
		//copy the rest
		memcpy(&pDestData[ _offset(nRow + 1,0) ],&m_pData[ _offset(nRow,0) ],
			sizeof(T) * m_nCols * (m_nRows - nRow));
		delete [] (BYTE*)m_pData; //avoid calling T dtors
		m_pData = pDestData;
	}
	else
	{
		for(long iR = m_nRows; iR >= nRow + 1; iR--)
		{
			memcpy(&m_pData[ _offset(iR,0) ],&m_pData[ _offset(iR-1,0) ],sizeof(T) * m_nCols);
		}
		//reinit 'slot'
		for(long iC = 0; iC < m_nCols; iC++)
		{
			_init_cell<T>(&m_pData[ _offset(nRow,iC) ]);
		}
	}
	m_nRows++;
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::insert_col_at(long nCol)
{
	long nNewSize = m_nRows * (m_nCols + 1);
	if(nNewSize > m_nAllocSize)
	{
		//need alloc
		m_nAllocSize = _compute_alloc(nNewSize);
		T *	pDestData = (T*) new char[ sizeof(T) * m_nAllocSize ];
		memset(pDestData,0,sizeof(T) * m_nAllocSize);
		//copy cols before insert
		for(long iR = 0; iR < m_nRows; iR++)
		{
			for(long iC = 0; iC < nCol; iC++)
			{
				memcpy(&pDestData[ _offset_modif(iR,iC,m_nCols+1) ],&m_pData[ _offset(iR,iC) ],sizeof(T));
			}
		}
		//init gap
		for(iR = 0; iR < m_nRows; iR++)
		{
			_init_cell<T>(&pDestData[ _offset_modif(iR,nCol,m_nCols+1) ]);
		}
		//copy the rest
		for(iR = 0; iR < m_nRows; iR++)
		{
			for(long iC = nCol + 1; iC <= m_nCols; iC++)
			{
				memcpy(&pDestData[ _offset_modif(iR,iC,m_nCols+1) ],&m_pData[ _offset(iR,iC-1) ],sizeof(T));
			}
		}
		delete [] (BYTE*) m_pData;	//avoid calling T dtors
		m_pData = pDestData;
	}
	else
	{
		for(long iR = m_nRows - 1; iR >= 0; iR--)
		{
			//copy after part
			for(long iC = m_nCols; iC >= nCol + 1; iC--)
			{
				memcpy(&m_pData[ _offset_modif(iR,iC,m_nCols+1) ],&m_pData[ _offset(iR,iC-1) ],sizeof(T));
			}

			//copy before part
			for(iC = nCol-1; iC >= 0; iC--)
			{
				memcpy(&m_pData[ _offset_modif(iR,iC,m_nCols+1) ],&m_pData[ _offset(iR,iC) ],sizeof(T));
			}
		}
		//reinit 'slot'
		for(iR = 0; iR < m_nRows; iR++)
		{
			_init_cell<T>(&m_pData[ _offset_modif(iR,nCol,m_nCols+1) ]);
		}
	}
	
	m_nCols++;
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::delete_row(long nRow)
{
	m_nRows--;
	//copy rows above deleted
	for(long iR = nRow; iR < m_nRows; iR++)
	{
		memcpy(&m_pData[ _offset(iR,0) ],&m_pData[ _offset(iR+1,0) ],sizeof(T) * m_nCols);
	}
	//clean objects 'slot'
	for(long iC = 0; iC < m_nCols; iC++)
	{
		_clear_cell<T>(&m_pData[ _offset(m_nRows,iC) ]);
	}
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::delete_col(long nCol)
{
	ASSERT(false);	//dokoñczyæ i sprawdziæ

	m_nCols--;
	for(long iR = 0; iR < m_nRows; iR++)
	{
		for(long iC = 0; iC < nCol; iC++)
		{
			memcpy(&m_pData[ _offset(iR,iC) ],&m_pData[ _offset_modif(iR,iC,m_nCols+1) ],sizeof(T));
		}
		_clear_cell<T>(&m_pData[ _offset(iR,nCol) ]);
	}
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::init_size(long nRows,long nCols)
{
	ASSERT(m_pData == NULL);
	ASSERT(m_nRows == 0 && m_nCols == 0);
	ASSERT(nRows >= 0);
	ASSERT(nCols >= 0);

	m_nRows = nRows;
	m_nCols = nCols;
	m_nAllocSize = _compute_alloc(nRows * nCols);

	if(m_nAllocSize > 0)
	{
		//alloc raw memory
		m_pData = (T*) new char[ sizeof(T) * m_nAllocSize ];
		//zero
		memset(m_pData,0,sizeof(T) * m_nAllocSize);
		//init with default T ctor
		for(long iter = 0; iter < m_nRows * m_nCols; iter++)
		{
			_init_cell<T>(&m_pData[iter]);
		}
	}
}

template<class T,class ARGT>
inline void CArray2D<T,ARGT>::make_empty()
{
	for(long iter = 0; iter < m_nRows * m_nCols; iter++)
	{
		_clear_cell<T>(&m_pData[iter]);
	}
	delete [] (BYTE*) m_pData;
	
	m_nRows = 0;
	m_nCols = 0;
	m_pData = NULL;
	m_nAllocSize = 0;
}

#endif	_ARRAY2D_DIRECT_ON_MEMORY_ALREADY_WORKING_

//-------------------------------------------------------------------------------
template<class T,class ARGT>
class CArrayInterface__ : public CArray<T,ARGT>, public CInterface__
{
public:
	CArrayInterface__()
	{
	}
	~CArrayInterface__()
	{
	}
};

template<class T,class ARGT>
class CArray2DX
{
public:
	CArray2DX() :
		m_nRows(0),
		m_nCols(0)
	{
	}
	~CArray2DX()
	{
	}
	long get_row_count() const
	{
		ASSERT(m_oStorage.GetSize() == m_nRows);
		return m_nRows;
	}
	long get_col_count() const
	{
#ifdef _DEBUG
		if(get_row_count())
		{
			ASSERT(m_oStorage[0]->GetSize() == m_nCols);
		}
#endif
		return m_nCols;
	}
	void add_row();
	void insert_row_at(long nRow);
	void delete_row(long nRow);
	
	void add_col();
	void insert_col_at(long nCol);
	void delete_col(long nCol);

	const T & get_at(long nRow,long nCol) const;
	T & get_at(long nRow,long nCol);
	void set_at(long nRow,long nCol,ARGT newElement);

protected:
	long	m_nRows;
	long	m_nCols;
	CArrayOfSCP < CArrayInterface__<T,ARGT> > m_oStorage;
};

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::add_row()
{
	insert_row_at(get_row_count());
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::add_col()
{
	insert_col_at(get_col_count());
}

template<class T,class ARGT>
inline const T & CArray2DX<T,ARGT>::get_at(long nRow,long nCol) const
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	return (*m_oStorage[ nRow ])[nCol];
}

template<class T,class ARGT>
inline T & CArray2DX<T,ARGT>::get_at(long nRow,long nCol)
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	return (*m_oStorage[ nRow ])[nCol];
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::set_at(long nRow,long nCol,ARGT newElement)
{
	ASSERT(nRow >= 0 && nRow < get_row_count());
	ASSERT(nCol >= 0 && nCol < get_col_count());
	(*m_oStorage[ nRow ])[nCol] = newElement;
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::insert_row_at(long nRow)
{
	SCP< CArrayInterface__<T,ARGT> > poNewArraySP = NewSCP(new CArrayInterface__<T,ARGT>());
	poNewArraySP->SetSize( get_col_count() );
	m_oStorage.InsertAt(nRow,poNewArraySP);
	m_nRows++;
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::insert_col_at(long nCol)
{
	for(long iter = 0; iter < get_row_count(); iter ++)
	{
		m_oStorage[ iter ]->InsertAt(nCol, T() );
	}

	m_nCols++;
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::delete_row(long nRow)
{
	m_nRows--;
	m_oStorage.RemoveAt(nRow);
}

template<class T,class ARGT>
inline void CArray2DX<T,ARGT>::delete_col(long nCol)
{
	m_nCols--;
	
	for(long iter = 0; iter < get_row_count(); iter ++)
	{
		m_oStorage[ iter ]->RemoveAt(nCol);
	}
}


#else
	#error __FILE__ already included
#endif
