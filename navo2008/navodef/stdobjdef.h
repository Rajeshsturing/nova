/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	StdObj definitions
*/

#ifndef _STDOBJDEF_H_
#define _STDOBJDEF_H_

#ifdef _DEBUG
	#ifdef _NAVODOTNET
		//-- nothing here -- 
	#else
		class ostream;
	#endif
#endif

//Relation TYPES
//
//	M U S T   M A T C H   H1000.H DEFINITION !!!!
//
//------------------------------------------------------------

/*
	opis pojedyñczego pola CStdObj
*/

class CStdObjFieldDef: public CCmdTargetInterface
{
public:
	CStdObjFieldDef();

	bool IsPersistent() const
	{
		return m_nSQLType != SQLT_IGNORE;
	};
	bool IsReadOnly () const
	{
		return m_bReadOnly != false;
	};
	void SetVirtual()
	{
		m_bVirtual = true;
	}
	bool IsVirtual() const
	{
		return m_bVirtual != false;
	};
	bool IsRefOptional() const
	{
		ASSERT(m_nRelationType == RELT_REF || m_nRelationType == RELT_WILDREF
			|| m_nRelationType == RELT_ENUM);
		return m_bRefOptional;
	};
	void SetRefOptional()
	{
		m_bRefOptional = true;
	}
	const CSmartOleVariant & GetDefaultValue() const
	{
		return m_Default;
	}
	void SetDefaultValue(const CSmartOleVariant & roDefaultSOV)
	{
		m_Default = roDefaultSOV;
	}
	void SetName(LPCTSTR lpName)
	{
		m_szNameString = lpName;
	}
	const CString & GetName() const
	{
		return m_szNameString;
	}
	
	void SetHumanName(LPCTSTR lpHumanName)
	{
		m_oHumanNameString = lpHumanName;
	}
	const CString & GetHumanName() const
	{
		return m_oHumanNameString;
	}

	void SetSQLType(long nSQLType)
	{
		m_nSQLType = nSQLType;
	}
	//zwraca kod typu pola w tabeli SQL (SQLT_IGNORE - pole nie ma odpowiednika w tabeli)
	long GetSQLType() const
	{
		return m_nSQLType;
	}

	void SetRelationType(long nRelationType)
	{
		m_nRelationType = nRelationType;
	}
	//zwraca rodzaj pola (<embedded>,<ref>,<list>,<file>,<wildref>)
	long GetRelationType() const
	{
		return m_nRelationType;
	}
	void SetReferenceTypeId(long nRefTypeId)
	{
		ASSERT(m_oWildRefTypeIdArray.GetSize() == 0);	//set only once
		m_oWildRefTypeIdArray.SetAtGrow(0,nRefTypeId);
	}
	//zwraca typ referencji w przypadku pola <ref> lub typ dziecka dla <list>
	long GetReferenceTypeId() const
	{
		ASSERT(m_oWildRefTypeIdArray.GetSize() > 0);
		return m_oWildRefTypeIdArray[0];
	}
	
	void AddWildRefTypeId(long nTypeId)
	{
		ASSERT(m_nRelationType == RELT_WILDREF);
		m_oWildRefTypeIdArray.Add(nTypeId);
	}
	//returns 0 when no more typeids
	long GetWildRefTypeId(long nInx)
	{
		ASSERT(m_nRelationType == RELT_WILDREF);
		if(nInx >= 0 && nInx <= m_oWildRefTypeIdArray.GetUpperBound())
		{
			return m_oWildRefTypeIdArray[ nInx ];
		}
		return 0;
	}
	bool IsWildRefTypeIdAllowed(long TypeId)
	{
		ASSERT(m_nRelationType == RELT_WILDREF);
		for(long iter = 0; iter <= m_oWildRefTypeIdArray.GetUpperBound(); iter++)
		{
			if(m_oWildRefTypeIdArray[ iter ] == TypeId)
			{
				return true;
			}
		}
		return false;
	}

	void AddEnumValue(LPCTSTR lpEnumValue)
	{
		m_oEnumValuesArray.Add(lpEnumValue);
	}
	LPCTSTR GetEnumValue(long nInx)
	{
		ASSERT(m_nRelationType == RELT_ENUM);
		if(nInx >= 0 && nInx <= m_oEnumValuesArray.GetUpperBound())
		{
			return m_oEnumValuesArray[ nInx ];
		}
		return NULL;
	}
	long GetEnumCount() const
	{
		return m_oEnumValuesArray.GetSize();
	}

	void SetUnique()
	{
		m_bUnique = true;
	}
	bool IsUnique() const
	{
		return m_bUnique != false;
	}
	bool is_hidden() const
	{
		return m_bHiddenFld;
	}
	void set_hidden()
	{
		m_bHiddenFld = true;
	}
	void SetNonEmpty()
	{
		m_bNonEmpty = true;
	}
	bool IsNonEmpty() const
	{
		return m_bNonEmpty != false;
	}
	bool IsRecalc() const
	{
		return m_bRecalc;
	}
	void MarkRecalc()
	{
		m_bRecalc = true;
	}
	bool IsComputed() const
	{
		return m_bComputed;
	}
	void MarkComputed()
	{
		m_bComputed = true;
	}
	void PostProcess();

	void WriteToArchive(CArchive & roArchive);
	void ReadFromArchive(CArchive & roArchive);

#ifdef _DEBUG
	void Dump(ostream & rostream);
#endif
	//{{AFX_MSG(CStdObjFieldDef)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CStdObjFieldDef)
	afx_msg BSTR GetNameAUTO();
	afx_msg void SetNameAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetTypeAUTO();
	afx_msg void SetTypeAUTO(long nNewValue);
	afx_msg long GetSQLTypeAUTO();
	afx_msg void SetSQLTypeAUTO(long nNewValue);
	afx_msg BSTR GetSQLTypeNameAUTO();
	afx_msg void SetSQLTypeNameAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetHumannameAUTO();
	afx_msg void SetHumannameAUTO(LPCTSTR lpszNewValue);
	afx_msg long GetReftypeidAUTO();
	afx_msg void SetReftypeidAUTO(long nNewValue);
	afx_msg BOOL GetIsUniqueAUTO();
	afx_msg void SetIsUniqueAUTO(BOOL bNewValue);
	afx_msg BOOL GetIsNonEmptyAUTO();
	afx_msg void SetIsNonEmptyAUTO(BOOL bNewValue);
	afx_msg BOOL GetIsPersistentAUTO();
	afx_msg void SetIsPersistentAUTO(BOOL bNewValue);
	afx_msg BOOL GetIsRefOptAUTO();
	afx_msg void SetIsRefOptAUTO(BOOL bNewValue);
	afx_msg long GetWildRefTypeIdAUTO(long nInx);
	afx_msg BSTR GetEnumValueAUTO(long nInx);
	afx_msg BOOL GetIsComputedAUTO();
	afx_msg void SetIsComputedAUTO(BOOL bNewValue);
	afx_msg BOOL GetIsHiddenAUTO();
	afx_msg void SetIsHiddenAUTO(BOOL bNewValue);
	afx_msg BOOL GetIsVirtualAUTO();
	afx_msg void SetIsVirtualAUTO(BOOL bNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:
	//db field description

	CString	m_szNameString;
	CString	m_oHumanNameString;
	long	m_nSQLType;
	long	m_nRelationType;

	CSmartOleVariant m_Default;	//initialized to default value (from XML) or to variant default
	
	bool	m_bRecalc;
	

	//wildref description
	CArray<long,long> m_oWildRefTypeIdArray;
	CArray<CString,LPCTSTR> m_oEnumValuesArray;

	//attributes
	bool		m_bReadOnly;		
	bool		m_bVirtual;
	bool		m_bRefOptional;
	bool		m_bComputed;

	//standard conditions
	bool		m_bNonEmpty;
	bool		m_bUnique;
	bool		m_bHiddenFld;


	friend class CDefinitionManager;
};

typedef CEnumerableArray< SCP<CStdObjFieldDef>, SCP<CStdObjFieldDef> &> CStdObjFieldDefArray;

class CCursorDef: public CCmdTargetInterface
{
public:
	CCursorDef();

	long GetIdent() const
	{
		ASSERT(m_Ident != 0);
		return m_Ident;
	}
	void SetIdent(long Ident)
	{
		ASSERT(Ident != 0);
		m_Ident = Ident;
	}
	void SetHumanName(LPCTSTR lpHumanName)
	{
		m_oHumanNameString = lpHumanName;
	}
	const CString & GetHumanName() const
	{
		return m_oHumanNameString;
	}

	void SetWhere(LPCTSTR lpWhere)
	{
		m_oWhereString = lpWhere;
	}
	const CString & GetWhere() const
	{
		return m_oWhereString;
	}
	void SetJoin(LPCTSTR lpJoin)
	{
		m_oJoinString = lpJoin;
	}
	const CString & GetJoin() const
	{
		return m_oJoinString;
	}
	void SetOrderBy(LPCTSTR lpOrderBy)
	{
		m_oOrderByString = lpOrderBy;
	}
	const CString & GetOrderBy() const
	{
		return m_oOrderByString;
	}
	void SetSPName(LPCTSTR lpSPName)
	{
		m_oSPNameString = lpSPName;
	}
	const CString & GetSPName() const
	{
		return m_oSPNameString;
	}
	void SetSPBody(LPCTSTR lpSPBody)
	{
		m_oSPBodyString = lpSPBody;
	}
	const CString & GetSPBody() const
	{
		return m_oSPBodyString;
	}
	bool IsForwardOnly() const
	{
		return m_bForwardOnly;
	}
	void SetForwardOnly(bool bFO)
	{
		m_bForwardOnly = bFO;
	}

	void WriteToArchive(CArchive & roArchive);
	void ReadFromArchive(CArchive & roArchive);
	//{{AFX_MSG(CCursorDef)
	afx_msg long GetIdentAUTO();
	afx_msg void SetIdentAUTO(long nNewValue);
	afx_msg BSTR GetHumannameAUTO();
	afx_msg void SetHumannameAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetWhereAUTO();
	afx_msg void SetWhereAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetJoinAUTO();
	afx_msg void SetJoinAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetOrderByAUTO();
	afx_msg void SetOrderByAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetSPNameAUTO();
	afx_msg void SetSPNameAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetSPBodyAUTO();
	afx_msg void SetSPBodyAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetIsForwardOnlyAUTO();
	afx_msg void SetIsForwardOnlyAUTO(BOOL bNewValue);
	//}}AFX_MSG
	//{{AFX_DISPATCH(CCursorDef)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	long		m_Ident;
	bool		m_bForwardOnly;
	CString		m_oHumanNameString;
	CString		m_oWhereString;
	CString		m_oJoinString;
	CString		m_oOrderByString;
	CString		m_oSPNameString;
	CString		m_oSPBodyString;
};

// identyfikatory metod standardowych
// kolejnoœæ taka sama jak w stdobjdef.cpp / pcClassMethods

const long CLASS_STDCOMMANDS_COUNT = 10;

const long CLASS_INVALID_FUNCTION = -1;	//invalid function number

const long CLASS_CTOR	= 0;			//constructor (for new objects)
const long CLASS_BITRIG	= 1;			//Before Insert Trigger
const long CLASS_BUTRIG	= 2;			//		 Update
const long CLASS_BDTRIG	= 3;			//		 Delete
const long CLASS_AITRIG	= 4;			//After
const long CLASS_AUTRIG	= 5;			//		 Update
const long CLASS_ADTRIG	= 6;			//		 Delete
const long CLASS_REGENER= 7;			//"regenerator" (for old objects)
const long CLASS_AS_TEXT= 8;			//default text representation
const long CLASS_LISTOP = 9;			//list operation

/*
	opis ca³ej klasy (typu) obiektu CStdObj
*/

class CDispatchForwarder;
class CDefinitionManager;

class CStdObjDef: public CCmdTargetInterface, public CScriptUser
{
public:
	CStdObjDef(CNavoException & roErrorStorage);
	~CStdObjDef()
	{
		QuasiDtor();
	}
	void QuasiDtor()
	{
		POSITION pos = m_oCursorMap.GetStartPosition();
		while(pos)
		{
			SCP<CCursorDef> poCursorDefSP;
			long nValue;
			m_oCursorMap.GetNextAssoc(pos,nValue,poCursorDefSP);
			poCursorDefSP = 0;
		}
		m_oCursorMap.RemoveAll();
		m_oFieldNamesMap.RemoveAll();

		CScriptUser::QuasiDtor();
	}
	void Validate();
#ifdef _DEBUG
	void Dump(ostream & rostream);
#endif
	//properties
	virtual LPCTSTR GetScriptCode()
	{
		return m_oClassScriptString;
	}
	virtual LPCTSTR GetScriptNXID()
	{
		CString strNXID("dataobject." + m_oTableNameString);
		
		//disable for now
		strNXID = "";

		return strNXID;
	}
	void SetScriptCode(LPCTSTR lpScriptCode);
	
	const CString & GetTableName() const
	{
		return m_oTableNameString;
	}
	void SetTableName(LPCTSTR lpTableName)
	{
		m_oTableNameString = lpTableName;
	}
	const CString & GetHumanName() const
	{
		if(m_oHumanNameString.IsEmpty())
		{
			return m_oTableNameString;
		}
		else
		{
			return m_oHumanNameString;
		}
	}
	void SetHumanName(LPCTSTR lpHumanName)
	{
		m_oHumanNameString = lpHumanName;
	}
	void SetVolatile()
	{
		m_bVolatile = true;
	}
	
	bool IsVolatile() const
	{
		return m_bVolatile;
	}
	void SetChild()
	{
		m_bChild = true;
	}
	bool IsChild() const
	{
		return m_bChild;
	}
	void SetHidden()
	{
		m_bHidden = true;
	}
	bool IsHidden() const
	{
		return m_bHidden;
	}
	bool IsCacheOnServer() const
	{
		return m_bCacheOnServer;
	}
	bool IsCacheOnClient() const
	{
		return m_bCacheOnClient;
	}
	void SetDontCacheOnServer()
	{
		m_bCacheOnServer = false;
	}
	void SetDontCacheOnClient()
	{
		m_bCacheOnClient = false;
	}
	bool HasAnyList() const
	{
		return m_bHasAnyList;
	}
	bool HasAnyFile() const
	{
		return m_bHasAnyFile;
	}
	void set_AlwaysCanDel()
	{
		m_bAlwaysCanDel = true;
	}
	bool get_AlwaysCanDel() const
	{
		return m_bAlwaysCanDel;
	}
	//serialization
	void WriteToArchive(CArchive & roArchive);
	void ReadFromArchive(CArchive & roArchive);
	virtual void GetDocumentName(CString & roDocNameString);

	//field manipulations
	SCP<CStdObjFieldDef> & GetField(long nFieldNr);
	SCP<CStdObjFieldDef> NewField();
	long GetFieldFromName(LPCWSTR lpFieldName);
	void AddField(SCP<CStdObjFieldDef> & rpoStdObjFieldDefSP);
	long GetFieldCount() const
	{
		return m_aFields.GetSize();
	}
	//function manipulations
	bool IsFunctionDefined(long nCommand) const
	{
		return m_bStdCommandsArray[ nCommand ];
	}
	void GetFunctionName(long nCommand,CString & roString);
	void GetRecalcFunctionName(long nFieldNr,CString & roString);

	//dispatch forwarders
	CDispatchForwarder & GetThis_DispatchForwarder()
	{
		return m_oThis_DispatchForwarder;
	}
	CDynamicDispatchForwarer & GetTransaction_DispatchForwarder()
	{
		return m_oTransaction_DispatchForwarder;
	}
	
	void SetTransaction_DDR(CDispatchDynamicResolver * pDDR)
	{
		m_oTransaction_DispatchForwarder.SetDispatchDynamicResolver(pDDR);
	}

	void AddCursorDef(SCP<CCursorDef> & rpoCursorDefSP);
	void RemoveCursorDef(long Ident);
	SCP<CCursorDef> GetCursorDef(long Ident);

	CNavoException & GetErrorStorage()
	{
		return m_roErrorStorage;
	}

	//{{AFX_MSG(CStdObjDef)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CStdObjDef)
	afx_msg BSTR GetHumanameAUTO();
	afx_msg void SetHumanameAUTO(LPCTSTR lpszNewValue);
	afx_msg BSTR GetTablenameAUTO();
	afx_msg void SetTablenameAUTO(LPCTSTR lpszNewValue);
	afx_msg BOOL GetIsPersistentAUTO();
	afx_msg void SetIsPersistentAUTO(BOOL bNewValue);
	afx_msg BOOL GetChildAUTO();
	afx_msg void SetChildAUTO(BOOL bNewValue);
	afx_msg BOOL GetHiddenAUTO();
	afx_msg void SetHiddenAUTO(BOOL bNewValue);
	afx_msg long GetTypeidAUTO();
	afx_msg void SetTypeidAUTO(long nNewValue);
	afx_msg long GetParentTypeidAUTO();
	afx_msg void SetParentTypeidAUTO(long nNewValue);
	afx_msg long GetFieldCountAUTO();
	afx_msg long GetFieldIndexAUTO(LPCTSTR lpName);
	afx_msg LPDISPATCH GetFieldAUTO(long nFldInx);
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg BSTR GetScriptCodeAUTO();
	afx_msg LPDISPATCH GetCursorDefAUTO(long idCursor);

	afx_msg BSTR GenerateMSSQLScriptAUTO(long nPart);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(PropDispatch, IDispatch)
		STDMETHOD(GetTypeInfoCount)(UINT*);
        STDMETHOD(GetTypeInfo)(UINT,LCID,ITypeInfo **);
		STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR*rgszNames,UINT cNames,LCID lCid,DISPID*rgDispId);
		STDMETHOD(Invoke)(DISPID dispId,REFIID riid,LCID lCid,WORD wFlags,DISPPARAMS *pDispParams,
            VARIANT *pVarResult,EXCEPINFO * pExceptInfo,UINT * puArgError);
	END_INTERFACE_PART(PropDispatch)

private:
	void __attach(CDefinitionManager * poDefinitionManager,long nTypeId);
	void SearchClassFunctions();

	void generate_mssql_script(CString & roString,long nPart);
	
	long	m_nTypeId;
	long	m_nParentTypeId;
	CString m_oTableNameString;
	CString m_oHumanNameString;

	//object level standard methods
	bool	m_bStdCommandsArray[CLASS_STDCOMMANDS_COUNT];	

	bool	m_bVolatile;

	bool	m_bChild;
	bool	m_bCacheOnServer;
	bool	m_bCacheOnClient;
	bool	m_bHidden;
	bool	m_bHasAnyList;
	bool	m_bHasAnyFile;
	bool	m_bAlwaysCanDel;		//don't check delete posibility with _candel

	CString m_oClassScriptString;

	CStdObjFieldDefArray m_aFields;
	
	//mapa pól  nazwa -> nr pola (dla celów dispid - ale pamiêtany jest nr pola nie dispid !!)
	CMap<CICSBStr,LPCWSTR,long,long &> m_oFieldNamesMap;
	
	CDispatchForwarder m_oThis_DispatchForwarder;
	CDynamicDispatchForwarer m_oTransaction_DispatchForwarder;

	CMap<long,long,SCP<CCursorDef>,SCP<CCursorDef> &> m_oCursorMap;
	CNavoException & m_roErrorStorage;


	CDefinitionManager * m_poDefinitionManager;	//uplink
	friend class CDefinitionManager;
};

#else
	#error __FILE__ included
#endif
