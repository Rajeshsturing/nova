/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDataObjectFile
*/

#ifndef _DATAOBJECTFILE_H_
#define _DATAOBJECTFILE_H_

class CNEO_filestorage : public CStreamAutoObject
{
public:
	CNEO_filestorage(CNEO_global_cache * poGlobalCache,
		long nParentTypeId,long nParentIdObj,long nOuterFieldNr,bool bParentIsNew);
	~CNEO_filestorage();
	virtual void OnFinalRelease();
	
	long GetParentId() const
	{
		return m_IdParent;
	}
	long GetParentTypeid() const
	{
		return m_ParentTypeId;
	}
	long GetOuterFieldNr() const
	{
		return m_nOuterFieldNr;
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
	bool full_is_usermodified();
	bool full_is_needsave();
	CString _get_ext()
	{
		return CString(m_oNSI.m_cExt);
	}
	void _set_ext(LPCTSTR lpszNewValue)
	{
		memset(m_oNSI.m_cExt,0,sizeof(m_oNSI.m_cExt));
		_tcsncpy((TCHAR*)m_oNSI.m_cExt,lpszNewValue,sizeof(m_oNSI.m_cExt)-1);
	}
	void _set_stream_info(const navostreaminfo & roNSI);
	virtual void OnStreamAttachDetach();
	virtual void OnFirstWrite();
	void _postprocess();
	void _copy_from(const CNEO_filestorage & roFileStorage);
	SCP<CNEO_filestorage> clone();

	void _writebinary(CArray<transblobinfo,transblobinfo &> & roBlobData);
private:

	long m_IdParent;
	long m_ParentTypeId;
	long m_nOuterFieldNr;

	eNeedSave		 m_eNeedSave;
	eUserModif		 m_eUserModif;
	bool			 m_bParentMarkDel;
	bool			 m_bParentIsNew;
	
	bool			 m_bStreamModified;
	long			 m_dwUserRef;

	navostreaminfo m_oNSI;
	CNEO_global_cache * m_poGlobalCache;

	friend class CNEO_global_cache;
};

inline long _compose_filemapping_id(long nParentTypeId,long nOuterFieldNr)
{
	ASSERT(nParentTypeId != 0);
	ASSERT(nOuterFieldNr != 0);
	return nParentTypeId  * 1000 + nOuterFieldNr;
}

inline hyper _compose_filestorage_key(CNEO_filestorage * poFileStorage)
{
	return longlong(
		_compose_filemapping_id(poFileStorage->GetParentTypeid(),poFileStorage->GetOuterFieldNr()),
		poFileStorage->GetParentId());
}

template<>
AFX_INLINE UINT AFXAPI HashKey(SCP<CNEO_filestorage> poFileStorageSP)
{
	return ((UINT)(void*)(DWORD)(void*)(poFileStorageSP.Get()));
}



class CNEO_fileuser  : public CCmdTargetInterface
{
public:
	CNEO_fileuser(SCP<CNEO_trans> & rpoTransSP,SCP<CNEO_filestorage> & rpoFileStorageSP,bool bReadOnly);
	~CNEO_fileuser();
	static SCP<CNEO_fileuser> FromIDispatch(LPDISPATCH lpDispatch);
	virtual void OnFinalRelease();
	
	SCP<CNEO_filestorage> & _get_storage()
	{
		return m_poFileStorageSP;
	}
	SCP<CNEO_trans> & _get_trans()
	{
		return m_poTransSP;
	}
	void _raw_set_markdel(bool bMarkDel);

	//{{AFX_MSG(CNEO_fileuser)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CNEO_fileuser)
	afx_msg BSTR GetExtAUTO();
	afx_msg void SetExtAUTO(LPCTSTR lpszNewValue);
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
	BEGIN_INTERFACE_PART(Stream, IStream)
		STDMETHOD(Read)(void *pData, unsigned long lLength, unsigned long *plBytesRead);
		STDMETHOD(Seek)(LARGE_INTEGER liOffset, unsigned long lOrigin,
			ULARGE_INTEGER * pliNewPointer);
		STDMETHOD(Write)(const void *pData, unsigned long lLength, unsigned long *plBytesWritten);
		STDMETHOD(SetSize)(ULARGE_INTEGER ulSize);
		STDMETHOD(CopyTo)(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten);
		STDMETHOD(Commit)(unsigned long);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(Stat)(STATSTG * pStatStg, unsigned long lFlags);
		STDMETHOD(Clone)(IStream ** ppIStream);
	END_INTERFACE_PART(Stream)
private:
	void _enable_changes();

	SCP<CNEO_trans>			m_poTransSP;
	SCP<CNEO_filestorage>	m_poFileStorageSP;
	bool					m_bReadOnlyStorage;
};










#else
	#error __FILE__ already included
#endif
