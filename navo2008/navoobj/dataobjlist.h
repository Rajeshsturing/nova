/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectList
*/

#ifndef _DATAOBJLIST_H_
#define _DATAOBJLIST_H_

long _extract_parent_typeid(long IdCollection);

class CNEO_liststorage : public CInterface__
{
public:
	CNEO_liststorage(CNEO_global_cache * poGlobalCache,long nCollectionId,long IdParent,
		long ChildTypeId,bool bParentIsNew,CStdObjDef *	poDefinition);
	~CNEO_liststorage();
	virtual void OnFinalRelease();

	
	long GetCollectionId() const
	{
		return m_CollectionId;
	}
	long GetParentId() const
	{
		return m_IdParent;
	}
	long GetParentTypeid() const
	{
		return _extract_parent_typeid(m_CollectionId);
	}
	long GetChildTypeid() const
	{
		return m_ChildTypeId;
	}

	long GetSize() const
	{
		return m_oItemArray.GetSize();
	}
	void AddRef_User()
	{
		m_dwUserRef++;
	}
	void Release_User()
	{
		--m_dwUserRef;
	}
	bool InExternalUse() const
	{
		return (m_dwUserRef != 0);
	}
	
	eUserModif _get_usermodified() const
	{
		return m_eUserModif;
	}
	eNeedSave _get_needsave() const
	{
		return m_eNeedSave;
	}
	
	void simple_set_user_modified(bool bUserModified)
	{
		m_eUserModif = bUserModified ? um_yes : um_no;
	}
	void set_parent_mark_del(bool bParentMarkDel)
	{
		m_bParentMarkDel = bParentMarkDel;
		m_eNeedSave = ns_unknown;
		m_eUserModif = um_unknown;
	}
	bool _is_parent_mark_del() const
	{
		return m_bParentMarkDel;
	}
	bool full_is_usermodified(const CNEO_liststorage & roListStorage);
	bool full_is_needsave(const CNEO_liststorage & roListStorage);

	void _readbinary(CFlatData & roFlatData);
	void _writebinary4save(CFlatData & roFlatData);
	void _writebinary4del(CFlatData & roFlatData);

	bool is_element_at(long nInternalIndex);
	long get_element_at(long nInternalIndex);
	void insert_new_element(long nInternalIndex,long nNewIdObj);
	void delete_element(long nInternalIndex);
	void delete_all_elements();
	long find(SCP<CNEO_storage> & rpoStorageSP);
	long findonid(long nChildIdObj);
	void move_element(long nFrom,long nTo);

	void _copy_from(const CNEO_liststorage & roListStorage);
	void _postprocess();

	SCP<CNEO_liststorage> clone();

	void undo_operation(long nInternalIndex,long nChildIdObj);

	CStdObjDef * get_parent_definition() const;
private:
	
	struct CNEO_listitem
	{
		CNEO_listitem() :
			m_IdObj(0)
		{
		}
		CNEO_listitem(const CNEO_listitem & roLI)
		{
			m_IdObj = roLI.m_IdObj;
		}
		CNEO_listitem(long IdObj) :
			m_IdObj(IdObj)
		{
		}
		
		long m_IdObj;		//idobj dziecka
	};

	CArray<CNEO_listitem,CNEO_listitem&>		m_oItemArray;
	
	long m_CollectionId;
	long m_IdParent;
	long m_ChildTypeId;

	CStdObjDef *	 m_poParentDefinition;	//parent object definition repository
	eNeedSave		 m_eNeedSave;
	eUserModif		 m_eUserModif;

	bool			 m_bParentMarkDel;
	bool			 m_bParentIsNew;

	long			 m_dwUserRef;
	CNEO_global_cache * m_poGlobalCache;
};


template<>
AFX_INLINE UINT AFXAPI HashKey(SCP<CNEO_liststorage> poListStorageSP)
{
	return ((UINT)(void*)(DWORD)(void*)(poListStorageSP.Get()));
}











class CNEO_user;
class CNEO_listuser : public CCmdTargetInterface, CEnumerableCollection< SCP<CNEO_user> >
{
public:
	CNEO_listuser(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_liststorage> & rpoListStorageSP,bool bReadOnlyStorage);
	~CNEO_listuser();

	static SCP<CNEO_listuser> FromIDispatch(LPDISPATCH lpDispatch);
	virtual void OnFinalRelease();

	SCP<CNEO_liststorage> & _get_storage()
	{
		return m_poListStorageSP;
	}
	SCP<CNEO_trans> & _get_trans()
	{
		return m_poTransSP;
	}

	virtual bool IsElementAt(long nInternalIndex);
	virtual SCP<CNEO_user> GetElementAt(long nInternalIndex);

	SCP<CNEO_user> add_new_element();
	SCP<CNEO_user> insert_new_element(long nOuterIndex);
	bool delete_element(long nOuterIndex);
	void delete_all_elements();

	void set_user_modified(bool bUserModified);
	void _raw_set_markdel(bool bMarkDel);

	//{{AFX_MSG(CNEO_listuser)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_listuser)
	afx_msg LPDISPATCH GetAUTO(long nOuterIndex);
	afx_msg BOOL ExistsAUTO(long nOuterIndex);
	afx_msg LPDISPATCH AddNewAUTO();
	afx_msg LPDISPATCH InsertNewAUTO(long nOuterIndex);
	afx_msg void DeleteAUTO(long nOuterIndex);
	afx_msg void DeleteAllAUTO();
	afx_msg long FindAUTO(LPDISPATCH pObj);
	afx_msg long FindOnIdAUTO(long nIdChildIdObj);
	afx_msg void MoveAUTO(long nFrom,long nTo);
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg void SetUserModifAUTO(BOOL bNewVal);
	afx_msg long GetCountAUTO();
	afx_msg long GetCollectionIDAUTO();
	afx_msg long GetIdObjAUTO(long nOuterIndex);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:
	void _enable_changes();

	SCP<CNEO_trans>			m_poTransSP;
	SCP<CNEO_liststorage>	m_poListStorageSP;
	bool					m_bReadOnlyStorage;
};


inline CStdObjDef * CNEO_liststorage::get_parent_definition() const
{
	return m_poParentDefinition;
}




inline long _extract_parent_typeid(long IdCollection)
{
	ASSERT(IdCollection != 0);
	ASSERT(IdCollection / 1000 != 0);
	return (IdCollection / 1000);
}

inline long _extract_parent_field(long IdCollection)
{
	ASSERT(IdCollection != 0);
	ASSERT(IdCollection % 1000 != 0);
	return IdCollection % 1000;
}

inline long _compose_collection_id(long nParentTypeId,long nFieldId)
{
	ASSERT(nParentTypeId != 0);
	ASSERT(nFieldId != 0);
	return nParentTypeId  * 1000 + nFieldId;
}

#else
	#error __FILE__ already included
#endif
