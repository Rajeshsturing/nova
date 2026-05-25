/*
NAVO Sp. z o.o. (2001)

NAVO Enterprise 2001

Smart &	Enhanced version of VARIANT
*/



#ifndef ___SMARTOLEVARIANT_H___
#define ___SMARTOLEVARIANT_H___

#define VT_NAVOBYREF 0x0040 // Uwaga: to samo co VT_MFCBYREF, trzeba przypilnowac, zeby nie weszlo w kolizje

#define LANG_ID_FOR_CONVERTIONS			1033	

class CSmartOleVariant: private COleVariant
{
public:
	CSmartOleVariant()
	{
	};
	~CSmartOleVariant ()
	{
		ClearNavoRef();
	};
#ifndef _UNICODE
	CSmartOleVariant(LPCWSTR pwcString)
	{
		ASSERT(pwcString);
		AfxVariantInit(this);
		V_VT(this) = VT_BSTR;
		V_BSTR(this) = ::SysAllocString(pwcString);
		if (V_BSTR(this) == NULL) 
		{
			ThrowNoMemory();
		};
	};
#endif
	CSmartOleVariant(const LPDISPATCH pDispatch, bool bAddRef)
	{
		SetDispatch (pDispatch);
		if (bAddRef)
		{
			pDispatch->AddRef();
		};
	};
	CSmartOleVariant (const SCP <IDispatch> & rpoIDispatchSP)
	{
		ASSERT(rpoIDispatchSP.PointsObject());
		IDispatch * pDispatch = rpoIDispatchSP.ConstCastObject();
		SetDispatch (pDispatch);
		pDispatch->AddRef();
	};
	CSmartOleVariant (CCmdTarget *pCmdTarget, bool bAddRef)
	{
		SetDispatch (pCmdTarget->GetIDispatch(bAddRef));
	};
	CSmartOleVariant (CCmdTarget &rCmdTarget, bool bAddRef)
	{
		SetDispatch (rCmdTarget.GetIDispatch(bAddRef));
	};
	CSmartOleVariant(SCP<IStream> & rpoIStreamSP)
	{
		ASSERT(rpoIStreamSP.PointsObject());
		SetStream(rpoIStreamSP);
		rpoIStreamSP->AddRef();
	}
	CSmartOleVariant(IStream * pIStream)
	{
		ASSERT(pIStream);
		SetStream(pIStream);
		pIStream->AddRef();
	}
	CSmartOleVariant(const VARIANT& varSrc): COleVariant (varSrc)
	{
	};
	CSmartOleVariant(LPCVARIANT pSrc): COleVariant (pSrc)
	{
	};
	CSmartOleVariant(const COleVariant &varSrc): COleVariant (varSrc)
	{
	};
	CSmartOleVariant(const CSmartOleVariant & roSOV)
	{
		(*this) = roSOV;
	};
	CSmartOleVariant(LPCTSTR lpszSrc): COleVariant (lpszSrc)
	{
	};
	CSmartOleVariant(LPCTSTR lpszSrc, VARTYPE vtSrc): COleVariant (lpszSrc, (VARTYPE)(vtSrc & (VARTYPE)~VT_NAVOBYREF))
	{
		if (vtSrc & (VARTYPE)VT_NAVOBYREF)
		{
			SetNavoRef();
		};
	};
	CSmartOleVariant(CString& strSrc): COleVariant (strSrc)
	{
	};
	CSmartOleVariant(BYTE nSrc): COleVariant (nSrc)
	{
	};
	CSmartOleVariant(short nSrc, VARTYPE vtSrc = VT_I2): COleVariant (nSrc, vtSrc)
	{
		AfxVariantInit(this);
		V_VT(this) = vtSrc;
		V_I2(this) = nSrc;
	};
	CSmartOleVariant(long lSrc, VARTYPE vtSrc = VT_I4)
	{
		AfxVariantInit(this);
		V_VT(this) = vtSrc;
		V_I4(this) = lSrc;
	};
	CSmartOleVariant(void *pSrc, VARTYPE vtSrc)
	{
		AfxVariantInit(this);
		V_VT(this) = (VARTYPE)(vtSrc | (VARTYPE)VT_BYREF);
		V_BYREF(this) = pSrc;
	};
#ifndef _NAVODOTNET
	CSmartOleVariant(bool bValue): COleVariant ((long)bValue, VT_BOOL)
	{
	};
#endif
	CSmartOleVariant(const COleCurrency& curSrc): COleVariant (curSrc)
	{
	};
	CSmartOleVariant(float fltSrc): COleVariant (fltSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
	};
	CSmartOleVariant(double dblSrc): COleVariant (dblSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
	};
	CSmartOleVariant(const COleDateTime& timeSrc): COleVariant (timeSrc)
	{
	};
	CSmartOleVariant(const CByteArray& arrSrc): COleVariant (arrSrc)
	{
	};
	CSmartOleVariant(const CLongBinary& lbSrc): COleVariant (lbSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
	};
	CSmartOleVariant(const VARIANT & roVariant, VARTYPE oType)
	{
		Set(roVariant, oType);
	};
	CSmartOleVariant& operator=(const VARIANT& varSrc)
	{
		COleVariant :: operator = (varSrc); return *this;
	};
	CSmartOleVariant& operator=(LPCVARIANT pSrc)
	{
		COleVariant :: operator = (pSrc); return *this;
	};
	CSmartOleVariant& operator=(const CSmartOleVariant& varSrc)
	{
		VARTYPE vtSrc = V_VT(&varSrc);

		ASSERT(vtSrc >= VT_EMPTY);	//valid value
		ASSERT(vt >= VT_EMPTY);	//valid value

		if((vtSrc <= VT_DATE || vtSrc == VT_BOOL) && 
			(vt <= VT_DATE || vt == VT_BOOL))	//"plain" types
		{
			ASSERT(sizeof(cyVal) >= sizeof(lVal));
			ASSERT(sizeof(cyVal) >= sizeof(dblVal));
			ASSERT(sizeof(cyVal) >= sizeof(date));
			cyVal = varSrc.cyVal;
			vt = vtSrc;
			return *this;
		}
		COleVariant::operator = (varSrc); return *this;
	}
	CSmartOleVariant& operator=(const COleVariant& varSrc)
	{
		COleVariant :: operator = (varSrc); return *this;
	};
	CSmartOleVariant& operator=(const LPCTSTR lpszSrc)
	{
		COleVariant :: operator = (lpszSrc); return *this;
	};
	CSmartOleVariant& operator=(const CString& strSrc)
	{
		COleVariant :: operator = (strSrc); return *this;
	};
	CSmartOleVariant& operator=(BYTE nSrc)
	{
		COleVariant :: operator = (nSrc); return *this;
	};
	CSmartOleVariant& operator=(short nSrc)
	{
		COleVariant :: operator = (nSrc); return *this;
	};
	CSmartOleVariant& operator=(long lSrc)
	{
		COleVariant :: operator = (lSrc); return *this;
	};
	CSmartOleVariant& operator=(const COleCurrency& curSrc)
	{
		COleVariant :: operator = (curSrc); return *this;
	};
	CSmartOleVariant& operator=(float fltSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
		COleVariant :: operator = (fltSrc); return *this;
	};
	CSmartOleVariant& operator=(double dblSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
		COleVariant :: operator = (dblSrc); return *this;
	};
	CSmartOleVariant& operator=(const COleDateTime& dateSrc)
	{
		COleVariant :: operator = (dateSrc); return *this;
	};
	CSmartOleVariant& operator=(const CByteArray& arrSrc)
	{
		COleVariant :: operator = (arrSrc); return *this;
	};
	CSmartOleVariant& operator=(const CLongBinary& lbSrc)
	{
		//nie przewidujemy uzywania tego typu
		ASSERT(false);
		COleVariant :: operator = (lbSrc); return *this;
	};
	bool operator == (const CSmartOleVariant & roVariant) const
	{
		return COleVariant::operator == (roVariant.GetVariantRef()) != FALSE;
	};
	bool operator == (const COleVariant & roVariant) const
	{
		return COleVariant::operator == (roVariant) != FALSE;
	};
	bool operator == (const VARIANT & roVariant) const
	{
		return COleVariant::operator == (roVariant) != FALSE;
	};
	bool operator != (const CSmartOleVariant & roVariant) const
	{
		return COleVariant::operator == (roVariant.GetVariantRef()) == FALSE;
	};
	bool operator != (const COleVariant & roVariant) const
	{
		return COleVariant::operator == (roVariant) == FALSE;
	};
	bool operator != (const VARIANT & roVariant) const
	{
		return COleVariant::operator == (roVariant) == FALSE;
	};
	void SetNavoRef()
	{
		V_VT(this) |= VT_NAVOBYREF;
	};
	void ClearNavoRef()
	{
		V_VT(this) &= ~VT_NAVOBYREF;
	};
	void SetRef(CSmartOleVariant & roVariant)
	{
		Clear();
		V_VT(this) = VT_VARIANT | VT_BYREF;
		V_BYREF(this) = &roVariant;
	};
	void Clear()
	{
		COleVariant::Clear();
	};

	void SetPseudoCurrency(long Hi,long Lo)	//this is unnormalized currency (VARIANT is used just as storage)
	{
		Clear();
		V_VT(this) = VT_CY;
		V_CY(this).Hi = Hi;
		V_CY(this).Lo = Lo;
	}
	CSmartOleVariant & Set(const CSmartOleVariant & roVariant, VARTYPE oType)
	{
		return Set(roVariant.GetVariantRef(), oType);
	};
	CSmartOleVariant & Set(const VARIANT & roVariant, VARTYPE oType)
	{
		if(V_VT(&roVariant) == VT_DATE && oType == VT_BSTR)
		{
			*this = COleDateTime(roVariant).Format(_T("%Y/%m/%d"));
			return * this;
		}
		
		{
			HRESULT hResult = ::VariantChangeTypeEx(this, 
				const_cast <VARIANTARG FAR *>(&roVariant), LANG_ID_FOR_CONVERTIONS, VARIANT_NOUSEROVERRIDE, oType);
			/*
			VariantChangeType konwertuje wg podanego LCID, chyba ze podane LCID jest takie jak
			aktualnie wybrane przez uzytkownika, wtedy bierze ustawienia podane przez
			uzytkownika, co moze byc niezgodne z wewnetrznym standardem (US English).
			Poniewa¿ nie przewidujemy klientów w RPA (nie ma tam ju¿ bia³ych) takie ustawienia powinno
			dzia³aæ
			Zmiana:
			Dodano VARIANT_NOUSEROVERRIDE, co powoduje, ¿e powinno dzia³aæ nawet
			przy ustawieniach ENGLISH,DEFAULT
			*/
			if (hResult != S_OK)
			{
				ThrowCannotChangeType(oType);
			};
		}
		return *this;
	};
	bool SafeChangeType(VARTYPE oType)
	{
		if(Type() == VT_DATE && oType == VT_BSTR)
		{
			ALL_TRY
			{
				*this = COleDateTime(*this).Format(_T("%Y/%m/%d"));
			}
			ALL_CATCH(CNavoException &)
			{
				return false;
			};
		}
		else
		{
			HRESULT hResult = ::VariantChangeTypeEx(this, this, MAKELCID(LANG_ID_FOR_CONVERTIONS, SORT_DEFAULT), 
				VARIANT_NOUSEROVERRIDE, oType);
			/*
			VariantChangeType konwertuje wg podanego LCID, chyba ze podane LCID jest takie jak
			aktualnie wybrane przez uzytkownika, wtedy bierze ustawienia podane przez
			uzytkownika, co moze byc niezgodne z wewnetrznym standardem (US English).
			Poniewa¿ nie przewidujemy klientów w RPA (nie ma tam ju¿ bia³ych) 
			takie ustawienia powinno dzia³aæ
			Zmiana:
			Dodano VARIANT_NOUSEROVERRIDE, co powoduje, ¿e powinno dzia³aæ nawet
			przy ustawieniach ENGLISH,DEFAULT
			*/
			return hResult == S_OK;
		}
		return true;
	};
	CSmartOleVariant & ChangeType(VARTYPE oType)
	{
		return Set(*this, oType);
	};

	CCmdTarget *FromIDispatch () const
	{
		if (Type() != VT_DISPATCH)
		{
			ThrowUnexpectedVariantType(VT_DISPATCH);
		};
		return CCmdTarget :: FromIDispatch (V_DISPATCH (this));
	};
	void EnsureType(VARTYPE nVarType) const
	{
		if (Type() != nVarType)
		{
			ThrowUnexpectedVariantType(nVarType);
		};
	};
	VARTYPE Type() const
	{
		return V_VT(this);
	}
	const bool GetBool() const
	{
		EnsureType(VT_BOOL);
		return V_BOOL(this) != 0;
	};
	void SetBool(bool bValue)
	{
		EnsureType(VT_BOOL);
		V_BOOL(this) = bValue;
	};
	const long GetLong() const
	{
		EnsureType(VT_I4);
		return V_I4(this);
	};
	void SetLong(long lValue)
	{
		EnsureType(VT_I4);
		V_I4(this) = lValue;
	};
	CY GetCurrency() const
	{
		EnsureType(VT_CY);
		return V_CY(this);
	};
	void SetCurrency(CY oValue)
	{
		EnsureType(VT_CY);
		V_CY(this) = oValue;
	};
	DATE GetDate() const
	{
		EnsureType(VT_DATE);
		return V_DATE(this);
	};
	void SetDate(DATE oValue)
	{
		EnsureType(VT_DATE);
		V_DATE(this) = oValue;
	};
	short GetShort() const
	{
		EnsureType(VT_I2);
		return V_I2(this);
	};
	void SetShort(short nValue)
	{
		EnsureType(VT_I2);
		V_I2(this) = nValue;
	};
	const long * GetLongRef() const
	{
		EnsureType(VT_I4 | VT_BYREF);
		return V_I4REF(this);
	};
	void SetLongRef(long *plValue)
	{
		EnsureType(VT_I4 | VT_BYREF);
		V_I4REF(this) = plValue;
	};
	LPCWSTR GetBStr() const
	{
		EnsureType(VT_BSTR);
		return V_BSTR(this);
	};
	SCP<IStream> GetStream() const
	{
		EnsureType(VT_UNKNOWN);
		SCP<IStream> poStreamSP;
		poStreamSP.QueryInterface(const_cast<IUnknown*>(V_UNKNOWN(this)));
		return poStreamSP;
	}
	void SetBStr(BSTR pbstrText)
	{
		EnsureType(VT_BSTR);
		V_BSTR(this) = pbstrText;
	};
	void SetCurrency(long Hi,long Lo)
	{
		EnsureType(VT_CY);
		*this = COleCurrency(Hi,Lo);
	}
	// helper for creating 1-dimension arrays
	void CreateOneDimArray(VARTYPE vtElement, long nElementCount)
	{
		Clear();

		vt = (VARTYPE)(VT_ARRAY | vtElement);
		SAFEARRAYBOUND bounds[1];
		bounds[0].cElements = nElementCount;
		bounds[0].lLbound = 0;
		parray = ::SafeArrayCreate(vtElement, 1, bounds);
		if (parray == NULL)
		{
			ThrowNoMemory();
		};
	};

	// Caution: for very advanced users only

	// returns not adrefed IDispatch *
	LPDISPATCH GetDispatch() const
	{
		EnsureType(VT_DISPATCH);
		return V_DISPATCH(this);
	};
	// returns adrefed copy (not auto releasing)
	VARIANT Detach()
	{
		return COleVariant::Detach();
	};
	void Attach(VARIANT & rSrcVariant)
	{
		COleVariant::Attach(rSrcVariant);
	};
	// returns COleVariant, unsafe operation will be allowed
	const COleVariant & GetVariantRef() const
	{
		return *this;
	};
	// returns COleVariant, unsafe operation will be allowed
	COleVariant & GetVariantRef()
	{
		return *this;
	};
	// end of advanced users
private:
	void SetDispatch (LPDISPATCH pDispatch)
	{
		AfxVariantInit(this);
		V_VT(this) = VT_DISPATCH;
		V_DISPATCH(this) = pDispatch;
	};
	void SetStream(IStream * pIStream)
	{
		AfxVariantInit(this);
		V_VT(this) = VT_UNKNOWN;
		V_UNKNOWN(this) = pIStream;
	}
	__declspec(noreturn) void ThrowNoMemory();
	__declspec(noreturn) void ThrowCannotChangeType(VARTYPE NewType);
	__declspec(noreturn) void ThrowUnexpectedVariantType(VARTYPE lNewType) const;

	// converts SmartOleVariant * to COleVariant *
	friend COleVariant * CSmartOleVariantPToCOleVariantP(CSmartOleVariant * pSOV);
	friend const COleVariant * CSmartOleVariantPToCOleVariantP(const CSmartOleVariant * pSOV);
};

inline COleVariant * CSmartOleVariantPToCOleVariantP(CSmartOleVariant * pSOV)
{
	return pSOV;
};

inline const COleVariant * CSmartOleVariantPToCOleVariantP(const CSmartOleVariant * pSOV)
{
	return pSOV;
};

inline CArchive& AFXAPI operator << (CArchive& ar, const CSmartOleVariant & roSOV)
{
	return ar << roSOV.GetVariantRef();
};

inline CArchive& AFXAPI operator >> (CArchive& ar, CSmartOleVariant & roSOV)
{
	return ar >> roSOV.GetVariantRef();
};

template <class T>
class CSafeArrayAccessHolder
{
public:
	CSafeArrayAccessHolder(COleSafeArray & roSafeArray) :
		m_roSafeArray(roSafeArray)
	{
		roSafeArray.AccessData(&m_pData);
	};
	~CSafeArrayAccessHolder()
	{
		m_roSafeArray.UnaccessData();
	};
	T * GetData()
	{
		return (T *)m_pData;
	};
	const T * GetData() const
	{
		return (const T *)m_pData;
	};

private:
	COleSafeArray & m_roSafeArray;
	void * m_pData;
};

class CVariable
{
	CSmartOleVariant	m_val;
	long				m_name;
public:
	CVariable() 
	{ 
		m_name = 0; 
	}
	CVariable(long name, const CSmartOleVariant & rVal) 
	{ 
		m_name = name;
		m_val = rVal;
	}
	CVariable(const CVariable & roVariable)
	{
		m_name = roVariable.m_name;
		m_val  = roVariable.m_val;
	}
	~CVariable()
	{
		;
	}
	bool operator == (const CVariable & roVariable) const
	{
		return m_name == roVariable.m_name && m_val == roVariable.m_val;
	};
	bool operator != (const CVariable & roVariable) const
	{
		return m_name != roVariable.m_name || m_val != roVariable.m_val;
	};
	virtual CVariable & operator = (const CVariable & roVariable)
	{
		m_name = roVariable.m_name;
		m_val  = roVariable.m_val;
		return *this;
	}
	const CSmartOleVariant & GetVal() const 
	{ 
		return m_val; 
	}
	long GetName() const
	{
		return m_name;
	};
	void SetVal (const CSmartOleVariant &rSmartOleVariant)
	{
		m_val = rSmartOleVariant;
	};
	friend CArchive & operator << (CArchive & roArchive, const CVariable & roVariable)
	{
		return roArchive << roVariable.m_name << roVariable.m_val;
	};
	friend CArchive & operator >> (CArchive & roArchive, CVariable & roVariable)
	{
		return roArchive >> roVariable.m_name >> roVariable.m_val;
	};
};

inline CString Variant2String(const CSmartOleVariant & roSOV)
{
	if(roSOV.Type() == VT_DISPATCH)
	{
		return "(object)";
	}
	else
	{
		CSmartOleVariant tmpSOV(roSOV);
		return tmpSOV.ChangeType(VT_BSTR).GetBStr();
	}
}

bool Variant2Display(const CSmartOleVariant& roSOV,CString& oDisplayString,void * lpFormat=NULL);
CString Variant2SQLString(const CSmartOleVariant & roSOV);

#else
#error __FILE__ already included
#endif