/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
	CHyperLinkInfo
	
	  "kolekcja property"
*/


#ifndef ___VARIABLE_ENVIRONMENT_H___
#define ___VARIABLE_ENVIRONMENT_H___

class CNAVOArchiveWriter;
class CNAVOArchiveReader;

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class CMapEx: public CMap <KEY, ARG_KEY, VALUE, ARG_VALUE>
{
public:
	CMapEx()
	{
	};
	~CMapEx()
	{
	};
	bool Exists(ARG_KEY key) const
	{
		return Find(key) != NULL;
	};
	VALUE * Find(ARG_KEY key)
	{
		UINT nHash;
#if defined(_NAVODOTNET) || defined(NAVO2008)
		UINT nHashBucket;
		CAssoc* pAssoc = GetAssocAt(key, nHashBucket,nHash);
#else
		CAssoc* pAssoc = GetAssocAt(key, nHash);
#endif
		if (pAssoc == NULL)
		{
			return NULL;
		};
		return &pAssoc->value;
	};
	const VALUE * Find(ARG_KEY key) const
	{
		UINT nHash;
#if defined(_NAVODOTNET) || defined(NAVO2008)
		UINT nHashBucket;
		const CAssoc * pAssoc = GetAssocAt(key, nHashBucket, nHash);
#else
		const CAssoc * pAssoc = GetAssocAt(key, nHash);
#endif
		if (pAssoc == NULL)
		{
			return NULL;
		};
		return &pAssoc->value;
	};
#if 0 && (defined(_NAVODOTNET) || defined(NAVO2008))
	const VALUE & GetNextAssoc(POSITION & rNextPosition, KEY & rKey) const
	{
		ASSERT_VALID(this);
		ASSERT(m_pHashTable != NULL);  // never call on empty map

		const CAssoc* pAssocRet = (const CAssoc *)rNextPosition;
		ASSERT(pAssocRet != NULL);

		if (pAssocRet == (const CAssoc *) BEFORE_START_POSITION)
		{
			// find the first association
			for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
				if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
					break;
			ASSERT(pAssocRet != NULL);  // must find something
		}

		// find next association
		ASSERT(AfxIsValidAddress(pAssocRet, sizeof(CAssoc)));
		const CAssoc* pAssocNext;
		if ((pAssocNext = pAssocRet->pNext) == NULL)
		{
			// go to next bucket
			for (UINT nBucket = pAssocRet->nHashValue + 1;
			  nBucket < m_nHashTableSize; nBucket++)
				if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
					break;
		}

		rNextPosition = (POSITION) pAssocNext;

		// fill in return data
		rKey = pAssocRet->key;
		return pAssocRet->value;
	};
#endif
};

class CPropertyProvider__ : public CCmdTargetInterface
{
public:
	virtual bool SafeGetProp(long lNumber, CSmartOleVariant & rSOV) const = 0;
	static SCP<CPropertyProvider__> FromIDispatch(LPDISPATCH lpDispatch);
	virtual void get_canonical_string(CString & roDestString) const = 0;
};

class CHyperLinkInfo : public CPropertyProvider__
{
	class CSingleVariableEnvironment
	{
		CMapEx <long, long, CVariable, CVariable &> m_map;
		const CVariable * Find(long name) const
		{
			return m_map.Find(name);
		}
		CVariable * Find(long name)
		{
			return m_map.Find(name);
		}
		CSingleVariableEnvironment() {}
		void Set(const CVariable & rNew)
		{
			m_map[rNew.GetName()] = rNew;
		}
		
		bool Del(long name)				//deletes named variable
		{
			if (!Find(name))
			{
				return false;
			};
			// todo: it can be optimized
			m_map.RemoveKey(name);
			return true;
		}
		
		const CVariable * Get(long name) const		//get value
		{
			return Find(name);
		}
		const CVariable & GetVariable(long name,bool & rbOK) const		//get value
		{
			const CVariable * pVariable = Find(name);
			rbOK = (pVariable != NULL);
			return *pVariable;
		}
		bool Exists(long name) const		//test of existence
		{
			return m_map.Exists(name);
		}
		void Push(const CSingleVariableEnvironment & rNewVars) //add, return frame pointer
		{
			POSITION pos = rNewVars.m_map.GetStartPosition();
			while (pos)
			{
				long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
				CVariable oVariable;
				rNewVars.m_map.GetNextAssoc(pos,lName,oVariable);
				m_map[lName] = oVariable;
#else
				const CVariable & rVar = rNewVars.m_map.GetNextAssoc(pos, lName);
				m_map[lName] = rVar;
#endif
			};
		}
		
		bool SafeGet(long lName, CSmartOleVariant & rSOV) const
		{
			const CVariable * pVar = Find(lName);
			if (!pVar)
			{
				return false;
			};
			rSOV = pVar->GetVal();
			return true;
		};
		
		virtual CSingleVariableEnvironment & operator = (const CSingleVariableEnvironment & rRight)
		{
			m_map.RemoveAll();
			POSITION pos = rRight.m_map.GetStartPosition();
			while (pos)
			{
				long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
				CVariable oVariable;
				rRight.m_map.GetNextAssoc(pos,lName,oVariable);
				m_map[lName] = oVariable;
#else
				const CVariable & rVar = rRight.m_map.GetNextAssoc(pos, lName);
				m_map[lName] = rVar;
#endif
			};
			return *this;
		}
		void operator += (const CSingleVariableEnvironment & rRight)
		{
			POSITION pos = rRight.m_map.GetStartPosition();
			while (pos)
			{
				long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
				CVariable oVariable;
				rRight.m_map.GetNextAssoc(pos,lName,oVariable);
				m_map[lName] = oVariable;
#else
				const CVariable & rVar = rRight.m_map.GetNextAssoc(pos, lName);
				m_map[lName] = rVar;
#endif
			};
		}

		virtual void Serialize(CArchive & roArchive)
		{
			if (roArchive.IsStoring())
			{
				operator << (roArchive);
			}
			else
			{
				operator >> (roArchive);
			};
		};
		bool operator == (const CSingleVariableEnvironment & roEnv) const
		{
			if (m_map.GetCount() != roEnv.m_map.GetCount())
			{
				return false;
			};
			POSITION pos = m_map.GetStartPosition();
			while (pos)
			{
				long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
				CVariable oVariable;
				m_map.GetNextAssoc(pos, lName,oVariable);
				const CVariable *poEnvVar = roEnv.m_map.Find(lName);
				if (!poEnvVar)
				{
					return false;
				};
				if (oVariable != *poEnvVar)
				{
					return false;
				};
#else
				const CVariable &roVar = m_map.GetNextAssoc(pos, lName);
				const CVariable *poEnvVar = roEnv.m_map.Find(lName);
				if (!poEnvVar)
				{
					return false;
				};
				if (roVar != *poEnvVar)
				{
					return false;
				};
#endif
			};
			return true;
		};
		bool operator != (const CSingleVariableEnvironment & roEnv) const
		{
			return !(operator == (roEnv));
		};
		void RemoveAll()
		{
			m_map.RemoveAll();
		};
	public:
		CArchive & AFXAPI operator << (CArchive & roArchive) const
		{
			POSITION pos = m_map.GetStartPosition();
			roArchive << (long)m_map.GetCount();
			while (pos)
			{
				long lName;
#if (defined(_NAVODOTNET) || defined(NAVO2008))
				CVariable oVariable;
				m_map.GetNextAssoc(pos, lName,oVariable);
				roArchive << oVariable;
#else
				roArchive << m_map.GetNextAssoc(pos, lName);
#endif
			};
			return roArchive;
		}
		CArchive & AFXAPI operator >> (CArchive & roArchive)
		{
			long lCount;
			roArchive >> lCount;
			for (long lIndex = 0; lIndex < lCount; lIndex++)
			{
				CVariable oVar;
				roArchive >> oVar;
				m_map[oVar.GetName()] = oVar;
			};
			return roArchive;
		}
		friend class CHyperLinkInfo;
		friend class CTransaction;	//special access to members
		friend class CNEO_trans;
	} m_props;
public:
	CHyperLinkInfo();
	CHyperLinkInfo(const CHyperLinkInfo & roHLI);

	bool operator == (const CHyperLinkInfo & roHLI) const
	{
		return m_props == roHLI.m_props;
	};
	bool operator != (const CHyperLinkInfo & roHLI) const
	{
		return m_props != roHLI.m_props;
	};
	void RemoveAll()
	{
		GetVars().RemoveAll();
	};
	CHyperLinkInfo & operator = (const CHyperLinkInfo & roHLI)
	{
		GetVars() = roHLI.GetVars();
		return *this;
	};
	void operator += (const CHyperLinkInfo & roHLI)
	{
		GetVars() += roHLI.GetVars();
	}
	virtual void _store(CNAVOArchiveWriter & roWriter);
	virtual void _load(CNAVOArchiveReader & roReader);
	
	DECLARE_DYNCREATE(CHyperLinkInfo)
		
	bool PropertyExists(long lPropertyNumber) const
	{
		return m_props.Exists(lPropertyNumber);
	}
	virtual bool SafeGetProp(long lNumber, CSmartOleVariant & rSOV) const
	{
		return m_props.SafeGet(lNumber, rSOV);
	};
	bool DeleteProp(long nProp)
	{
		return m_props.Del(nProp);
	}
	void SetNumProp(long nProp,long Value);
	void SetStrProp(long nProp,const CString & Value);
	void SetProp(long nProp,const CSmartOleVariant & roValueSOV);
	
	long GetNumProp(long nProp) const;
	LPCWSTR GetBStrProp(long nProp) const;
	CString GetStrProp(long nProp) const;
	const CSmartOleVariant & GetProp(long nProp) const;
	
	bool SafeGetNumProp(long nProp,long & nValue) const;
	bool SafeGetStrProp(long nProp,CString & roValueString) const;
	
	const CSingleVariableEnvironment & GetVars() const { return m_props; }
	CSingleVariableEnvironment & GetVars() { return m_props; }
	
	//some most popular commands 
	virtual void get_canonical_string(CString & roDestString) const;

	CString WriteToString(bool bSafeForMarshallingOnly = false) const;
	CString WriteToXMLString() const;
	
	virtual void Serialize(CArchive & roArchive)
	{
		m_props.Serialize(roArchive);
	}
	friend CArchive & AFXAPI operator << (CArchive & oArchive, const CHyperLinkInfo & roHLI);
	friend CArchive & AFXAPI operator >> (CArchive & oArchive, CHyperLinkInfo & roHLI);

	static SCP<CHyperLinkInfo> FromIDispatch(LPDISPATCH lpDispatch);
	
//{{AFX_MSG(CHyperLinkInfo)
//}}AFX_MSG
//{{AFX_DISPATCH(CHyperLinkInfo)
	afx_msg BOOL ExistsAUTO(long Name);
	afx_msg BSTR GetAsStringAUTO();
	afx_msg VARIANT GetPropAUTO(long Name);
	afx_msg void SetPropAUTO(long Name, const VARIANT FAR& newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	friend class CTransaction;	//special access to members
	friend class CNEO_trans;
};

SCP<CHyperLinkInfo> ReadHLIFromString(const CString & roString,
	SCP<CHyperLinkInfo> poHLISP = SCP<CHyperLinkInfo>());

class CNamedHyperLinkInfo : public CHyperLinkInfo
{
public:
	CNamedHyperLinkInfo()
	{
	}
	CNamedHyperLinkInfo(const CString & roString,const CHyperLinkInfo & roHLI) :
		CHyperLinkInfo(roHLI),
		m_oNameString(roString)
	{
	}
	virtual void operator =(const CNamedHyperLinkInfo & roNHLI)
	{
		CHyperLinkInfo::operator =(roNHLI);
		m_oNameString = roNHLI.m_oNameString;
	}
	const CString & GetName() const
	{
		return m_oNameString;
	}
	void SetName(LPCTSTR lpName)
	{
		m_oNameString = lpName;
	}
private:
	CString m_oNameString;
};

class CHyperLinkInfoWithResult : public CHyperLinkInfo
{
public:
	CHyperLinkInfoWithResult() :
		m_bResultExpected(false)
	{
	}
	CHyperLinkInfoWithResult(bool bResultExpected,const CHyperLinkInfo & roHLI) :
		CHyperLinkInfo(roHLI),
		m_bResultExpected(bResultExpected)
	{
	}
	virtual void operator =(const CHyperLinkInfoWithResult & roNHLI)
	{
		CHyperLinkInfo::operator =(roNHLI);
		m_bResultExpected = roNHLI.m_bResultExpected;
	}
	bool IsResultExpected() const
	{
		return m_bResultExpected;
	}
	void SetResultExpected(bool bResultExpected)
	{
		m_bResultExpected = bResultExpected;
	}
private:
	bool	m_bResultExpected;
};

//inlines 

inline CArchive & AFXAPI operator << (CArchive & oArchive, const CHyperLinkInfo & roHLI)
{
	return roHLI.GetVars().operator <<(oArchive);
};

inline CArchive & AFXAPI operator >> (CArchive & oArchive, CHyperLinkInfo & roHLI)
{
	return roHLI.GetVars().operator >>(oArchive);
};

inline void CHyperLinkInfo::SetNumProp(long nProp,long Value)
{
	m_props.Set(CVariable(nProp,CSmartOleVariant(Value)));
}

inline void CHyperLinkInfo::SetStrProp(long nProp,const CString & Value)
{
	m_props.Set(CVariable(nProp,CSmartOleVariant((LPCTSTR)Value)));
}

inline void CHyperLinkInfo::SetProp(long nProp,const CSmartOleVariant & roValueSOV)
{
	m_props.Set(CVariable(nProp,roValueSOV));
}

inline long CHyperLinkInfo::GetNumProp(long nProp) const
{
	return GetProp(nProp).GetLong();
}

inline const CSmartOleVariant & CHyperLinkInfo::GetProp(long nProp) const
{
	bool bOK;
	const CSmartOleVariant & roSOV = m_props.GetVariable(nProp,bOK).GetVal();
	if(!bOK)
	{
		ThrowNavoException2(ERCO_SVENV_VARIABLEDOESNOTEXISTS,
			IDPAGE_NOTAVAILABLE, nProp,(LPCTSTR)WriteToString());
	}
	return roSOV;
}

inline LPCWSTR CHyperLinkInfo::GetBStrProp(long nProp) const
{
	return GetProp(nProp).GetBStr();
}

inline CString CHyperLinkInfo::GetStrProp(long nProp) const
{
	return CString(GetProp(nProp).GetBStr());
}

inline bool CHyperLinkInfo::SafeGetNumProp(long nProp,long & nValue) const
{
	CSmartOleVariant oSOV;
	if(!SafeGetProp(nProp,oSOV))
	{
		return false;
	}
	nValue = oSOV.GetLong();
	return true;
}

inline bool CHyperLinkInfo::SafeGetStrProp(long nProp,CString & roValueString) const
{
	CSmartOleVariant oSOV;
	if(!SafeGetProp(nProp,oSOV))
	{
		return false;
	}
	roValueString = oSOV.GetBStr();
	return true;
}

inline void CHyperLinkInfo::get_canonical_string(CString & roDestString) const
{
	roDestString = WriteToString(true);
}

SCP<CHyperLinkInfo> GetSystemEnvironmentHLI();

CString ReplaceFormalParam(LPCTSTR lpInput,CHyperLinkInfo * poHLI);
	
#else
	#error File already included
#endif
