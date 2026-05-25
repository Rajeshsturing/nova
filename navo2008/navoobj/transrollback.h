/*
	NAVO Sp. z o.o. (2002)
	
	NAVO Enterprise

	class CNEO_rollbacklog and related classes

	transactional log


*/

#ifndef _TRANS_ROLLBACK_H_
#define _TRANS_ROLLBACK_H_

//------------------------------------------------------------------------------------
// rollback log
//------------------------------------------------------------------------------------
class CNEO_trans;

class CNEO_undoitem__ : public CInterface__			//base class for every undo item type
{
public:
	enum eItemType
	{
		it_fldchange,			//zmieniono wartoœæ pola
		it_newobject,			//utworzono nowy obiekt
		it_markdel,				//zmieniono status 'mark del'
		it_listoper,			//zmieniono strukturê listy
		it_writelock,			//uzyskano write lock
	};
	eItemType _get_type() const
	{
		return m_eType;
	}
protected:
	CNEO_undoitem__(eItemType eType):
		m_eType(eType)
	{
	}
private:
	eItemType m_eType;
};

class CNEO_undofieldchange : public CNEO_undoitem__
{
public:
	CNEO_undofieldchange(long nTypeId,long nIdObj,long nFldNr,
		const CSmartOleVariant & roOldValueSOV):
		CNEO_undoitem__(it_fldchange),
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj),
		m_nFldNr(nFldNr),
		m_oValueSOV(roOldValueSOV)
	{
	}
private:
	long m_nTypeId;
	long m_nIdObj;
	long m_nFldNr;
	CSmartOleVariant m_oValueSOV;

	friend class CNEO_rollbacklog;
};

class CNEO_undonewobject : public CNEO_undoitem__
{
public:
	CNEO_undonewobject(long nTypeId,long nIdObj) :
		CNEO_undoitem__(it_newobject),
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj)
	{
	}
private:
	long m_nTypeId;
	long m_nIdObj;

	friend class CNEO_rollbacklog;
};

class CNEO_undomarkdel : public CNEO_undoitem__
{
public:
	CNEO_undomarkdel(long nTypeId,long nIdObj,bool bOldState) :
		CNEO_undoitem__(it_markdel),
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj),
		m_bOldState(bOldState)
	{
	}
private:
	long m_nTypeId;
	long m_nIdObj;
	bool m_bOldState;

	friend class CNEO_rollbacklog;
};

class CNEO_undolistoper : public CNEO_undoitem__
{
public:
	CNEO_undolistoper(long nCollectionId,long IdParent,long nOuterIndex,long nIdChild) :
		CNEO_undoitem__(it_listoper),
		m_nCollectionId(nCollectionId),
		m_nIdParent(IdParent),
		m_nOuterIndex(nOuterIndex),
		m_nIdChild(nIdChild)
	{
	}
private:
	long m_nCollectionId;
	long m_nIdParent;
	long m_nOuterIndex;
	long m_nIdChild;

	friend class CNEO_rollbacklog;
};

class CNEO_undowritelock : public CNEO_undoitem__
{
public:
	CNEO_undowritelock(long nClass,long nTypeId,long nIdObj,long nExtra) :
		CNEO_undoitem__(it_writelock),
		m_nClass(nClass),
		m_nTypeId(nTypeId),
		m_nIdObj(nIdObj),
		m_nExtra(nExtra)
	{
	}
private:
	long m_nClass;
	long m_nTypeId;
	long m_nIdObj;
	long m_nExtra;

	friend class CNEO_rollbacklog;
};

class CNEO_rollbacklog : public CInterface__
{
public:
	CNEO_rollbacklog(CNEO_trans & roTrans);
	~CNEO_rollbacklog();
	bool _is_inside_change_sequence() const
	{
		return (m_nLevel != 0);
	}
private:	//for CNEO_rollbackholder
	friend class CNEO_rollbackholder;
	
	bool _begin_operation();				//open next level
	void _finish_operation(bool bSuccess);	//close level and commit/rollback
	void _registerundo(SCP<CNEO_undoitem__> & rpoUndoItemSP);
private:
	void _perform_undo();
	void _clean();



	CNEO_trans & m_roTrans;
	long		 m_nLevel;			//how many sub-operations started and not finished yet (recalc etc.)
	bool		 m_bOverallSuccess;	//all sub-operations successed
	CArray< SCP<CNEO_undoitem__>, SCP<CNEO_undoitem__> & > m_oUndoItemArray;
};



#else
	#error __FILE__ already included
#endif

