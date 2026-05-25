/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObject
*/

#ifndef _DATAOBJECT_H_
#define _DATAOBJECT_H_

#ifdef _DEBUG
inline bool IsPlainVariant(const CSmartOleVariant & roSOV)
{
	VARTYPE vt = roSOV.Type();
	return (vt == VT_I4 || vt == VT_CY || vt == VT_DATE || vt == VT_BSTR);
}

inline bool IsPlainVariant_or_Nothing(const CSmartOleVariant & roSOV)
{
	if(IsPlainVariant(roSOV))
	{
		return true;
	}
	if(roSOV.Type() == VT_DISPATCH)
	{
		return (roSOV.GetDispatch() == NULL);
	}
	return false;
}
#endif

class CStdObjFieldDef;
class CStdObjDef;
class CFlatData;
class CNEO_trans;
class CNEO_global_cache;
class CNEO_user;
class CNEO_storage;

enum eNEO_loadresult
{
	neolr_ok_newer,		//record successfully retrieved (newer version delivered)
	neolr_ok_current,	//record successfully retrieved (version is up-to-date)
	neolr_locked,		//record is locked 
	neolr_not_exists,	//record doesn't exists (bad idobj or deleted)
};

struct CNEO_field_status
{
	bool m_bComputing	: 1;		// inside recalc
	bool m_bBadValue	: 1;		// it was detected, that field has invalid value
	bool m_bAssigned	: 1;		// "by³o przypisanie zmieniaj¹ce wartoœæ"
};

class CNEO_field
{
public:
	CNEO_field()
	{
		m_oFlags.m_bComputing = false;
		m_oFlags.m_bBadValue  = false;
		m_oFlags.m_bAssigned  = false;
	}
	CNEO_field(const CNEO_field & roNEO_field)
	{
		m_oFlags.m_bComputing = false;
		m_oFlags.m_bBadValue  = false;
		m_oFlags.m_bAssigned  = false;

		ASSERT(!roNEO_field.m_oFlags.m_bComputing);
		ASSERT(!roNEO_field.m_oFlags.m_bBadValue);
		ASSERT(!roNEO_field.m_oFlags.m_bAssigned);

		m_oValueSOV = roNEO_field.m_oValueSOV;
	}

	enum eAssignResult
	{
		ar_ok,				//success
		ar_ok_nochange,		//success - void assingment
		ar_long_or_disp,	//must be long or dispatch
		ar_cant_change_type,//cannot change type
		ar_enum_out_range,	//enum value out of range
		ar_string_too_long,	//string too long
		ar_ref_to_bad_type,	//reference to not allowed type
		ar_not_allowed,		//set not allowed
		ar_alien_ptr,		//ptr to 'alien' object
		ar_internal_error,	//internal error
	};
	void clear_bad_value() 
	{
		m_oFlags.m_bBadValue  = false;
	}
	void set_bad_value() 
	{
		m_oFlags.m_bBadValue  = true;
	}
	bool is_bad_value() const
	{
		return m_oFlags.m_bBadValue;
	}
	void set_assigned()
	{
		m_oFlags.m_bAssigned  = true;
	}

	void clear_assigned()
	{
		m_oFlags.m_bAssigned  = false;
	}
	
	bool is_modified(const CNEO_field & roField) const
	{
		if(!m_oFlags.m_bAssigned)
		{
			return false;
		}
		return (m_oValueSOV != roField.m_oValueSOV);
	}

	eAssignResult _assign(SCP<CStdObjFieldDef> & rpoFieldDefSP,
		const CSmartOleVariant & roNewValueSOV,CSmartOleVariant & roOldValueSOV);

	bool _test_can_save(SCP<CStdObjFieldDef> & rpoFieldDefSP,CNEO_storage * poStorage,CNEO_trans * poTrans,bool bSilent);

	void _raw_set_ref_value(long nTypeId,long nIdObj)
	{
		m_oValueSOV.SetPseudoCurrency(nTypeId,nIdObj);
	}
	const CSmartOleVariant & _get_value() const
	{
		return m_oValueSOV;
	}
	CSmartOleVariant & _access_value()	//carefully! special access only (_readbinary)
	{
		return m_oValueSOV;
	}
	CNEO_field_status & _access_status()
	{
		return m_oFlags;
	}
private:
	CNEO_field_status m_oFlags;
	
	CSmartOleVariant	m_oValueSOV;
};

enum eNeedSave
{
	ns_yes,
	ns_no,
	ns_unknown
};

enum eUserModif
{
	um_yes,
	um_no,
	um_unknown
};

class CNEO_storage : public CInterface__
{
public:
	CNEO_storage(CNEO_global_cache * poGlobalCache,long nTypeId,long IdObj,CStdObjDef *	poDefinition);
	~CNEO_storage();

	virtual void OnFinalRelease();
	
	//basic informations
	long GetType() const
	{
		ASSERT(m_nTypeId > 0);
		return m_nTypeId;
	}
	long GetThis() const
	{
		ASSERT(m_nIdObj > 0);
		return m_nIdObj;
	}
	long GetVersion() const
	{
		ASSERT(m_nVersionId >= 0);
		return m_nVersionId;
	}
	CStdObjDef * GetDefinition() const
	{
		ASSERT(m_poDefinition);
		return m_poDefinition;
	}
	bool IsNew() const
	{
		ASSERT(m_eState != debug_state);
		return m_eState == new_data;
	}
	bool IsOld() const
	{
		ASSERT(m_eState != debug_state);
		return m_eState == old_data;
	}
	bool IsDeleted() const
	{
		ASSERT(m_eState != debug_state);
		return m_eState == del_data;
	}

	//two step assingment 
	//first call begin, then finish
	CNEO_field::eAssignResult _begin_set_field(const long nOuterFieldNr,
		const CSmartOleVariant & roNewSOV,CSmartOleVariant & roOldSOV,bool & rbRecalc);
	void _finish_set_field(const long nOuterFieldNr);
	void _explain_set_field_error(CNEO_field::eAssignResult eAR,const long nOuterFieldNr,
		errorcode & rErco,CString & roTableName,CString & roFldName,long & rnTypeId,long & rnIdObj);

	void _get_field(const long nOuterFieldNr,CSmartOleVariant & roSOV,long & rnRelationType);
	void _undo_setfield(long nInternalFldNr,const CSmartOleVariant & roSOV);
	
	void _initnew(CNEO_trans * poTrans);

	void _readbinary(CNEO_trans * poTrans,CFlatData & roFlatData);
	void _writebinary4save(CFlatData & roFlatData);
	void _writebinary4del(CFlatData & roFlatData);

	void _postprocess();

	bool _custom_init(CNEO_user * poUser);

	bool _has_field_bad_value(const long nOuterFieldNr) const;
	void _set_field_bad_value(const long nOuterFieldNr,bool bBad);

	void _init_parent(long nParentTypeId,long nParentIdObj)
	{
		ASSERT(nParentTypeId != 0);
		ASSERT(nParentIdObj != 0);

		ASSERT(long(m_cyParent.Hi) == nParentTypeId || m_cyParent.Hi == 0);
		ASSERT(long(m_cyParent.Lo) == nParentIdObj  || m_cyParent.Lo == 0);
		
		m_cyParent.Hi = nParentTypeId;
		m_cyParent.Lo = nParentIdObj;
	}
	
	void _get_parent(long & rnParentTypeId,long & rnParentIdObj)
	{
		ASSERT(m_cyParent.Hi != 0);
		ASSERT(m_cyParent.Lo != 0);

		rnParentTypeId = m_cyParent.Hi;
		rnParentIdObj = m_cyParent.Lo;
	}

	void _set_mark_del(bool bMarkDel);
	bool _is_mark_del() const
	{
		return m_bMarkDel;
	}

	void simple_set_user_modified(bool bUserModified)
	{
		m_eUserModif = bUserModified ? um_yes : um_no;
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

	void _copy_from(const CNEO_storage & roStorage);

	void _copy_bad_status(const CNEO_storage & roStorage);

	SCP<CNEO_storage> clone();

	eUserModif _get_usermodified() const
	{
#ifdef _DEBUG
		check_modif_flags();
#endif
		return m_eUserModif;
	}
	eNeedSave _get_needsave() const
	{
#ifdef _DEBUG
		check_modif_flags();
#endif
		return m_eNeedSave;
	}

	bool full_is_usermodified(const CNEO_storage & roStorage);
	bool full_is_needsave(const CNEO_storage & roStorage);

	CNEO_field_status & _access_field_status(long nInternalFieldNr)
	{
		return m_oFields[ nInternalFieldNr]._access_status();
	}

	bool _test_can_delete(bool bSilent,CNEO_trans * poTrans);
	bool _test_can_save(bool bSilent,CNEO_trans * poTrans);

	enum DataState
	{
		debug_state,	//debug support
		new_data,		//new object, yet not in db
		old_data,		//existing, already in db
		del_data,		//deleted, not in db, still in memory
	} m_eState;

	void set_prop_recalc_enabled(bool bEnabled);
	bool get_prop_recalc_enabled() const;
private:
#ifdef _DEBUG
	void check_modif_flags() const;
#endif

	const long		 m_nTypeId;			//TypeId
	const long		 m_nIdObj;			//unique identificator = mapped to m_aVars[0]
	long			 m_nVersionId;		//version
	CArray<CNEO_field,CNEO_field &>		m_oFields;

	CStdObjDef *	 m_poDefinition;	//object definition repository
	eNeedSave		 m_eNeedSave;
	eUserModif		 m_eUserModif;
	
	bool			m_bMarkDel;
	bool			m_bConstructed;
	bool			m_bRecalcEnabled;

	long			 m_dwUserRef;
	CY				 m_cyParent;

	CNEO_global_cache * m_poGlobalCache;

#ifdef _DEBUG
	friend class CNEO_trans;
#endif
	friend class CNEO_performer;
};

#ifdef _DEBUG
inline void CNEO_storage::check_modif_flags() const
{
	ASSERT(
		(m_eNeedSave == ns_yes && m_eUserModif == um_yes) ||
		(m_eNeedSave == ns_unknown && m_eUserModif == um_unknown) ||
		(m_eUserModif == um_no)
		);
}
#endif


template<>
AFX_INLINE UINT AFXAPI HashKey(SCP<CNEO_storage> poStorageSP)
{
	return ((UINT)(void*)(DWORD)(void*)(poStorageSP.Get()));
}
//------------ proxy udostêpniane na zewn¹trz ---------------

class CNEO_trans;	

class CNEO_user : public CCmdTargetInterface
{
public:
	CNEO_user(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_storage> & rpoStorageSP,bool bReadOnly);
	~CNEO_user();
	virtual void OnFinalRelease();
	static SCP<CNEO_user> FromIDispatch(LPDISPATCH lpDispatch);

	SCP<CNEO_storage> & _get_storage()
	{
		return m_poStorageSP;
	}
	SCP<CNEO_trans> & _get_trans()
	{
		return m_poTransSP;
	}

	long get_idobj();

	void set_field(long nOuterFieldNr,const CSmartOleVariant & roSOV);
	void get_field(long nOuterFieldNr,CSmartOleVariant & roSOV);
	void get_original_field(long nOuterFieldNr,CSmartOleVariant & roSOV);
	
	bool has_field_bad_value(long nOuterFieldNr) const
	{
		return m_poStorageSP->_has_field_bad_value(nOuterFieldNr);
	}
		
	void set_markdel(bool bMarkDel);
	bool get_markdel();

	bool _call_trigger(long nCommand);
	bool _call_before_list_operation(long nOuterIndex);

	void set_user_modified(bool bUserModified);

	SCP<CNEO_user> _get_parent();
	CString get_as_text();

	//{{AFX_MSG(CNEO_user)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_user)
	afx_msg VARIANT GetFieldAUTO(const VARIANT FAR&varFieldName);
	afx_msg void SetFieldAUTO(const VARIANT FAR&varFieldName, const VARIANT FAR& newValue);
	afx_msg BSTR GetAsTextAUTO();
	afx_msg void SetUserModifAUTO(BOOL bNewVal);
	afx_msg BOOL GetMarkDelAUTO();
	afx_msg void SetMarkDelAUTO(BOOL bNewValue);
	afx_msg BOOL GetIgnoreAUTO();
	afx_msg void SetIgnoreAUTO(BOOL bNewValue);
	afx_msg long GetTypeAUTO();
	afx_msg long GetVersionIdAUTO();
	afx_msg LPDISPATCH GetStdObjDefAUTO();
	afx_msg LPDISPATCH GetParentAUTO();
	afx_msg LPDISPATCH GetRealThisAUTO();
	afx_msg BOOL IsNewAUTO();
	afx_msg BOOL ExclusiveLockAUTO();
	afx_msg void ExclusiveUnlockAUTO();
	afx_msg BOOL CanDelAUTO();
	afx_msg BOOL CanSaveAUTO(BOOL bSilent);
	afx_msg BOOL HasFieldBadValueAUTO(long FieldNr);
	afx_msg BOOL GetRecalcEnabledAUTO();
	afx_msg void SetRecalcEnabledAUTO(BOOL bNewValue);
	afx_msg VARIANT GetOriginalFieldAUTO(const VARIANT FAR&varFieldName);
	afx_msg void SetOriginalFieldAUTO(const VARIANT FAR&varFieldName, const VARIANT FAR& newValue);
	//}}AFX_DISPATCH
	DECLARE_INTERFACE_MAP();
	DECLARE_DISPATCH_MAP()
	BEGIN_INTERFACE_PART(DynaDispatch, IDispatch)
		STDMETHOD(GetTypeInfoCount)(UINT*);
        STDMETHOD(GetTypeInfo)(UINT,LCID,ITypeInfo **);
		STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId);
		STDMETHOD(Invoke)(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError);
	END_INTERFACE_PART(DynaDispatch)
	BEGIN_INTERFACE_PART(NEDataObject,INEDataObject)
		STDMETHOD_(long,get_typeid)();
		STDMETHOD_(long,get_idobj)();
		STDMETHOD_(long,get_i4_field)(long nOuterFieldNr);
		STDMETHOD_(BSTR,get_bstr_field)(long nOuterFieldNr);
		STDMETHOD_(CY,get_cy_field)(long nOuterFieldNr);
		STDMETHOD_(DATE,get_date_field)(long nOuterFieldNr);
		STDMETHOD_(INEDataObject *,get_obj_field)(long nOuterFieldNr);
		STDMETHOD_(INEDataObjectList *,get_list_field)(long nOuterFieldNr);
	END_INTERFACE_PART(NEDataObject)
private:
	long _get_outer_field_nr_from_variant(const CSmartOleVariant & roFieldNameSOV);
	void _enable_changes();
	bool _call_recalc(const long nOuterFieldNr,const CSmartOleVariant & roOldValueSOV);
	bool _exclusive_lock_and_reload();
	void _exclusive_unlock();
	CString Variant2StringWithDataObject(const CSmartOleVariant & roSOV);

	HRESULT _implement_GetIDsOfNames(LPOLESTR*rgszNames,DISPID*rgDispId);
	HRESULT _implement_Invoke(DISPID dispId,WORD wFlags,DISPPARAMS *pDispParams,VARIANT *pVarResult,
		EXCEPINFO * pExceptInfo);

	bool _internal_set_field(long nOuterFieldNr,const CSmartOleVariant & roSOV);

	void _resolve_field(long nOuterFieldNr,CSmartOleVariant & roSOV,long nRelationType,bool bNew);

	SCP<CNEO_trans>		m_poTransSP;
	SCP<CNEO_storage>	m_poStorageSP;
	bool				m_bReadOnlyStorage;
};

inline long CNEO_user::get_idobj()
{
	return _get_storage()->GetThis();
}

//-------------------------------------------------------------------------------------------
inline void CNEO_storage::set_prop_recalc_enabled(bool bEnabled)
{
	m_bRecalcEnabled = bEnabled;
}

inline bool CNEO_storage::get_prop_recalc_enabled() const
{
	return m_bRecalcEnabled;
}

//-------------------------------------------------------------------------------------------

#else
	#error __FILE__ already included
#endif
