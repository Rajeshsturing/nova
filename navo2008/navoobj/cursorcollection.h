/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNEO_cursor implementation
*/

#ifndef _CURSORCOLLECTION_H_
#define _CURSORCOLLECTION_H_

class CNEO_cursorIterator;
class CNEO_user;

class CNEO_cursor : public CCmdTargetInterface, CEnumerableCollection< SCP<CNEO_user> >
{
public:
	CNEO_cursor(CNEO_trans * poTransaction,
		long TypeId,LPCTSTR lpWhereClause,LPCTSTR lpOrderByClause,LPCTSTR lpJoinClause);

	CNEO_cursor(CNEO_trans * poTransaction,long TypeId,SCP<INAVOObjectCollection> poObjectCollectionSP);
	
	virtual ~CNEO_cursor();
	virtual void OnFinalRelease();

	virtual bool IsElementAt(long nPosition)
	{
		SCP<CNEO_user> poStdObjSP;
		return SafeGet(nPosition,poStdObjSP,false);
	}
	virtual SCP<CNEO_user> GetElementAt(long nPosition)
	{
		SCP<CNEO_user> poStdObjSP;
		VERIFY(SafeGet(nPosition,poStdObjSP,true));
		return poStdObjSP;
	}
	void SetForwardOnly(bool bForwardOnly)
	{
		ASSERT(m_pRPC_oObjectCollectionSP.PointsNull());
		m_bForwarOnly = bForwardOnly;
	}
	bool GetForwardOnly() const
	{
		return m_bForwarOnly;
	}
	void SetTop(long nTop)
	{
		m_nTop = nTop;
	}
	long GetTop() const
	{
		return m_nTop;
	}
	
	bool Refresh(long nPositionToKeep);

	long GetTotalCount();

	SCP<CNEO_cursorIterator> CreateIterator();

	static SCP<CNEO_cursor> FromIDispatch(LPDISPATCH lpDispatch);

#ifdef _DEVELOPER_EDITION_
	CNEO_trans * debug_get_transaction_ptr()
	{
		return m_poTransactionSP.Get();
	}
#endif 
	//{{AFX_MSG(CNEO_cursor)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_cursor)
	afx_msg BOOL GetForwardonlyAUTO();
	afx_msg void SetForwardonlyAUTO(BOOL bNewValue);
	afx_msg long GetTopAUTO();
	afx_msg void SetTopAUTO(long nTop);
	afx_msg LPDISPATCH GetAUTO(long Index);
	afx_msg BOOL ExistsAUTO(long Index);
	afx_msg LPDISPATCH CreateIteratorAUTO();
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg long GetTotalCountAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	bool SafeGet(long nIndex,SCP<CNEO_user> & rpoStdObjSP,bool bReturnObject);	//zwraca obiekt jeœli istnieje
	void __ReadFromDB(long nAbsPos);

	long					m_nPageOffset;
	long					m_nTotalCount;
	CArray<long,long &>		m_oIdents;
	bool					m_bForwarOnly;
	long					m_nTop;
	SCP<INAVOObjectCollection>	m_pRPC_oObjectCollectionSP;
	SCP<CNEO_trans>		m_poTransactionSP;
	
	//cursor parameters
	long					m_nTypeId;
	CString					m_oWhereClauseString;
	CString					m_oOrderByClauseString;
	CString					m_oJoinClauseString;
}; 

#else
	#error __FILE__ already included
#endif


/////////////////////////////////////////////////////////////////////////////
// CNEO_cursorIterator command target
/////////////////////////////////////////////////////////////////////////////

class CNEO_cursorIterator : public CCmdTargetInterface
{
	CNEO_cursorIterator(SCP<CNEO_cursor> & rpoManagedCursorCollectionSP);
public:
#ifdef _DEVELOPER_EDITION_
	CNEO_trans * debug_get_transaction_ptr()
	{
		return m_poManagedCursorCollectionSP->debug_get_transaction_ptr();
	}
#endif 
	//{{AFX_VIRTUAL(CNEO_cursorIterator)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	static SCP<CNEO_cursorIterator> FromIDispatch(LPDISPATCH lpDispatch);
protected:
	virtual ~CNEO_cursorIterator();
	//{{AFX_MSG(CNEO_cursorIterator)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CNEO_cursorIterator)
	afx_msg BOOL GoFirstAUTO();
	afx_msg BOOL GoLastAUTO();
	afx_msg BOOL GoNextAUTO();
	afx_msg BOOL GoPrevAUTO();
	afx_msg BOOL GoTo(long nRecordNumber);
	afx_msg LPDISPATCH GetAUTO();
	afx_msg BOOL RefreshAUTO();
	afx_msg BOOL IsEmptyAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	friend class CNEO_cursor;
private:
	long					m_nRecordNr;
	SCP<CNEO_cursor>	m_poManagedCursorCollectionSP;
};

/////////////////////////////////////////////////////////////////////////////
inline SCP<CNEO_cursorIterator> CNEO_cursorIterator::FromIDispatch(LPDISPATCH lpDispatch)
{
	CCmdTarget * poCmdTargetCCI = CCmdTarget::FromIDispatch(lpDispatch);
	ASSERT(poCmdTargetCCI);
	CNEO_cursorIterator * poCursorCollectionIter = dynamic_cast<CNEO_cursorIterator*>(poCmdTargetCCI);
	ASSERT(poCursorCollectionIter);
	return NewSCP(poCursorCollectionIter,true);
}
