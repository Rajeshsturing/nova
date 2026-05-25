/*
	NAVO Enterprise (2001)

	Script Engine Host User
*/

#ifndef _SCRIPTUSER_H_
#define _SCRIPTUSER_H_

//------------------------------------------------
//--------- informacje o "named item" dla skryptu
//------------------------------------------------

class CNamedItemInfo : public CInterface__
{
public:
	CNamedItemInfo(
		LPCTSTR lpNameString,
		IDispatch* poItemDispatch,
		ITypeInfo* poItemTypeInfo) :
		m_oNameBStr(lpNameString),
		m_poItemDispatch(poItemDispatch),
		m_poItemTypeInfo(poItemTypeInfo)
	{
	}
	IDispatch* Dispatch()
	{
		return m_poItemDispatch;
	}
	ITypeInfo* TypeInfo()
	{
		return m_poItemTypeInfo;
	}
	const CBStr& GetName() const
	{
		return m_oNameBStr;
	}
private:
	CBStr			m_oNameBStr;
	IDispatch* m_poItemDispatch;
	ITypeInfo* m_poItemTypeInfo;
};

class CScriptHostImpl;

//----------------------------------------------------------------------------------------
//------------ obudowa script engine pozwalaj¹ca nie zabieraæ za sob¹ wszystkich #includów
//----------------------------------------------------------------------------------------

class CScriptHost : public CInterface__
{
public:
	CScriptHost(bool bVB = true);
	~CScriptHost();
	void AddNamedItem(SCP<CNamedItemInfo>& rpoNamedItemSP);
	void Init(LPCOLESTR pScriptCode, LPCTSTR pDocumentName);
	void InitWithNXID(LPCTSTR lpNXID);

	void Invoke(DISPID id, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);
	void Invoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);
	eInvokeResult SafeInvoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);

	DISPID GetDISPID(const OLECHAR* pocName);
private:
	CScriptHostImpl* m_poImplementation;
	friend class CScriptUser;
};

//------------------------------------------------------------------------------------
//------------ klasa bazowa do obiektów skryptowalnych (posiadaj¹cych w³asne skrypty)
//
// z niej nale¿y dziedziczyæ obiekty, które zawieraj¹ w³asne skrypty
// klasa pochodna musi dostarczyæ treœæ skryptu (GetScriptCode), dodaæ ewentualnie
// named items (AddNamedItem)
//
// mo¿na potem u¿ywaæ albo jako "forward" implementacji IDispatch (__GetIDsOfNames,__Invoke)
// albo samemu wo³aæ metody skryptu (Invoke)
//
//------------------------------------------------------------------------------------

class CScriptUser
{
public:
	CScriptUser(long nTranslateBy_DISPID) :
		m_nTranslateBy_DISPID(nTranslateBy_DISPID),
		m_bCompiled(false)
	{
	}
	~CScriptUser()
	{
		QuasiDtor();
	}

	//wysokopoziomowa funkcja wywo³ania metody przez nazwê
	void Invoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);

	eInvokeResult SafeInvoke(const OLECHAR* pocName, CSmartOleVariant* pArgumentsSmartOleVariant, const long lSize, CSmartOleVariant* poResultSmartOleVariant = NULL);

	//klasa pochodna dostarcza kod skryptu:
	virtual LPCTSTR GetScriptCode() = 0;

	virtual LPCTSTR GetScriptNXID() = 0;

	//klasa pochodna dostarcza nazwê dokumentu
	virtual void GetDocumentName(CString& roDocNameString) = 0;


	//
	void AddNamedItem(SCP<CNamedItemInfo>& rpoNamedItemSP)
	{
		ASSERT(!m_bCompiled);
		m_oNIIArray.Add(rpoNamedItemSP);
	}

	//niskopoziomowe funkcje implementuj¹ce "IDispatch"
	HRESULT __GetIDsOfNames(LPOLESTR* rgszNames, UINT cNames, DISPID* rgDispId);
	HRESULT __Invoke(DISPID dispId, REFIID riid, LCID lCid, WORD wFlags, DISPPARAMS* pDispParams,
		VARIANT* pVarResult, EXCEPINFO* pExceptInfo, UINT* puArgError);
protected:
	DISPID GetDISPID(const OLECHAR* pcFunctionName);


	void QuasiDtor()
	{
		m_oNIIArray.RemoveAll();
		m_poScriptHostSP = 0;
	}
	void _InitScript();
	void _PushNamedItems();
	void _Compile();

	SCP<CScriptHost>	m_poScriptHostSP;		//implementacja hosta script engine
	CFunctionInfoArray	m_oFunctionsArray;		//tablica funkcji i procedur wykrytych w skrypcie

	long				m_nTranslateBy_DISPID;	//mapowanie DISPID o sta³y offset
	CArray<SCP<CNamedItemInfo>, SCP<CNamedItemInfo>&>	m_oNIIArray;
	bool				m_bCompiled;

};

class CSimpleScriptUser : public CScriptUser
{
public:
	CSimpleScriptUser(long nTranslateBy_DISPID) :
		CScriptUser(nTranslateBy_DISPID)
	{
	}
	virtual LPCTSTR GetScriptCode()
	{
		return m_oScriptCodeStorage;
	}

	virtual LPCTSTR GetScriptNXID()
	{
		return "";
	}

	virtual void GetDocumentName(CString& roDocNameString)
	{
		roDocNameString = m_oScriptNameString;
	};
	CString& _access_script_storage()		//used for script storage manipulation
	{
		return m_oScriptCodeStorage;
	}
	CString& _access_script_name()
	{
		return m_oScriptNameString;
	}
protected:
	CString m_oScriptCodeStorage;
	CString m_oScriptNameString;
};

#else
#error __FILE__ already included
#endif
