/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	Smart COM pointer
	(with OLE-way reference counting)
*/


#ifndef ___SMARTCOMPOINTER_H___
#define ___SMARTCOMPOINTER_H___

template <class T>
void AddRefSCP(T * poT)
{
	poT->AddRef();
};

template <class T>
void ReleaseSCP(T * poT)
{
	poT->Release();
};

template <typename T>
class SCP
{
public:
	SCP(const CLSID & rClassId, DWORD dwContext):
		m_pObject(NULL)
	{
		CreateInstance(rClassId, dwContext);
	};
	template <typename T_> SCP(SCP <T_> & T_SCP):
		m_pObject(T_SCP.Get())
	{
		if (PointsObject ())
		{
			AddRefSCP(Get());
		}
	};
	SCP():
		m_pObject(NULL)
	{
	};
	SCP(SCP <T> & TSCP):
		m_pObject (TSCP.Get())
	{
		if (PointsObject ())
		{
			AddRefSCP(Get());
		}
	};
	~SCP()
	{
		DeleteObject ();
	};

	bool PointsObject () const
	{
		return m_pObject != (T *) NULL;
	};
	bool PointsNull () const
	{
		return m_pObject == (T *) NULL;
	};
	const T * Get () const
	{
		return m_pObject;
	};
	T * Get ()
	{
		return m_pObject;
	};
	const T * SafeGet () const
	{
		ASSERT (m_pObject != (T *) NULL);
		return m_pObject;
	};
	T * SafeGet ()
	{
		ASSERT (m_pObject != (T *) NULL);
		return m_pObject;
	};
	T * ConstCastObject() const // Use this extremely carefully
	{
		return const_cast <T *> (Get());
	};
	bool operator == (const SCP <T> & TSCP) const
	{
		return m_pObject == TSCP.m_pObject;
	};
	bool operator != (const SCP <T> & TSCP) const
	{
		return m_pObject != TSCP.m_pObject;
	};
	bool operator == (const T * pT) const
	{
		return m_pObject == pT;
	};
	bool operator != (const T * pT) const
	{
		return m_pObject != pT;
	};
#ifdef _DEBUG
	bool operator == (int null) const
#else
	bool operator == (int) const
#endif
	{
		ASSERT (null == NULL);
		return PointsNull();
	};
#ifdef _DEBUG
	bool operator != (int null) const
#else
	bool operator != (int) const
#endif
	{
		ASSERT (null == NULL);
		return PointsObject();
	};
	bool operator ! () const
	{
		return PointsNull ();
	};

	operator const T * () const;
	operator T * ();
	/*
		to jest niebezpieczny operator w po³¹czeniu z CSmartOleVariant np.
		const SCP<IStream> pIStreamSP;
		CSmartOleVariant(pIStreamSP) nie u¿ywa CSmartOleVariant(SCP<IStream> &) lecze
		CSmartOleVariant(bool)
	
	operator bool () const 
	{
		return PointsObject ();
	};
	*/
	const T * operator -> () const
	{
		return SafeGet();
	};
	T * operator -> ()
	{
		return SafeGet();
	};

	const T & operator * () const
	{
		return *SafeGet();
	};
	T & operator * ()
	{
		return *SafeGet ();
	};
	template<typename T_> void QueryInterface(T_ pT_)
	{
		DeleteObject();
		ASSERT(pT_ != NULL);
		HRESULT hResult = pT_->QueryInterface(GetIID(), reinterpret_cast<void**>(reinterpret_cast<void**>(&m_pObject)));
		if (hResult == S_OK)
		{
			return;
		};
		if (hResult == E_NOINTERFACE)
		{
			ThrowNavoException(ERCO_OBJ_DOESNT_IMPLEMENT_INTERFACE,IDPAGE_NOTAVAILABLE);
		};
		ThrowNavoException1(ERCO_QUERY_INTERFACE_FAILED, IDPAGE_NOTAVAILABLE, 
							SCODE_To_String(hResult));
	}
	template<typename T_> bool SafeQueryInterface(T_ pT_)
	{
		DeleteObject();
		
		if(pT_ == NULL)		//zachowanie takie jakby nie mia³ interface
		{
			return false;
		}

		HRESULT hResult = pT_->QueryInterface(GetIID(), reinterpret_cast<void**>(reinterpret_cast<void**>(&m_pObject)));
		if (hResult == S_OK)
		{
			return true;
		};
		if (hResult == E_NOINTERFACE)
		{
			return false;
		};
		ThrowNavoException1(ERCO_QUERY_INTERFACE_FAILED, IDPAGE_NOTAVAILABLE, 
			SCODE_To_String(hResult));
	}
	static const IID & GetIID()
	{
		return __uuidof(T);
	};
	void DeleteObject ()
	{
		if (PointsObject ())
		{
			ReleaseSCP(Get());
			m_pObject = (T *) NULL;
		};
	};
	void CreateInstance(const CLSID & rClassId, DWORD dwContext)
	{
		DeleteObject();
		IUnknown *pUnknown;
		SCODE sc = ::CoCreateInstance(rClassId, NULL, dwContext, __uuidof(IUnknown), 
		   reinterpret_cast<void**>(&pUnknown));
		
		if (S_OK != sc)
		{
			ThrowNavoException2(ERCO_SCP_CREATEINSTANCE_FAIL,IDPAGE_NOTAVAILABLE,
				StringFromCLSID(rClassId),SCODE_To_String(sc));
		};
		sc = ::OleRun(pUnknown);
		if (S_OK != sc)
		{
			pUnknown->Release();
			ThrowNavoException2(ERCO_SCP_CREATEINSTANCE_FAIL2,IDPAGE_NOTAVAILABLE,
				StringFromCLSID(rClassId),SCODE_To_String(sc));
		};
		sc = pUnknown->QueryInterface(GetIID(), reinterpret_cast<void**>(&m_pObject));
		pUnknown->Release();
		if (S_OK != sc)
		{
			ThrowNavoException2(ERCO_SCP_CREATEINSTANCE_FAIL3,IDPAGE_NOTAVAILABLE,
				StringFromCLSID(rClassId),SCODE_To_String(sc));
		};
	};
#ifdef _DEBUG
	SCP & operator = (int null)
#else
	SCP & operator = (int)
#endif
	{
		ASSERT (null == NULL);
		DeleteObject();
		return *this;
	};
	template<typename T_> SCP & operator = (T_ & pT)
	{
		SetObject (pT.Get());
		return *this;
	};
	template<typename T_> SCP & operator = (const T_ & pT)
	{
		SetObject (const_cast<T*>(pT.Get()));
		return *this;
	};
	SCP & operator = (SCP <T> & pT)
	{
		SetObject (pT.Get());
		return *this;
	};
	int GetObjectSize () const
	{
		return sizeof (T);
	};
	T *Detach()
	{
		T * const pT = m_pObject;
		m_pObject = (T *) NULL;
		return pT;
	};
	T * & GetRawPointer()
	{
		ASSERT (PointsNull());
		return m_pObject; // Bedzie mozna podac go do QueryInterface, ale musi byc pusty
	};
	void Attach(T * pT, bool bAddRef = false)
	{
		DeleteObject ();
		m_pObject = pT;
		if (bAddRef && PointsObject ())
		{
			AddRefSCP(Get());
		}
	};
	SCP<T> GetSCP() const
	{
		SCP<T> oSCP;
		oSCP.m_pObject = m_pObject;
		if (oSCP.PointsObject())
		{
			oSCP.m_pObject->AddRef();
		}
		return oSCP;
	};
	SCP <IStream> Marshal();
	void UnMarshal(SCP <IStream> &);

private:
#ifdef _NAVODOTNET
	void SetObject(const T * pT)
	{
		SetObject(const_cast<T*>(pT));
	}
#endif
	void SetObject(T * pT)
	{
		if(m_pObject == pT)
		{
			return;
		}
		DeleteObject ();
		m_pObject = pT;
		if (PointsObject ())
		{
			AddRefSCP(Get());
		};
	};

	T * m_pObject;
};

//-----------------------------
// templates
//-----------------------------

template <typename T>
SCP <T> NewSCP(T *pT, bool bAddRef = false)
{
	SCP <T> oTSCP;
	oTSCP.Attach(pT, bAddRef);
	return oTSCP;
};

template<class T>
inline SCP <T> :: operator const T * () const
{
	return Get();
}

template<class T>
inline SCP <T> :: operator T * ()
{
	return Get();
}

template <class T>
SCP <IStream> SCP <T> :: Marshal()
{
	SCP <IStream> iStreamSCP;
	HRESULT hr = ::CoMarshalInterThreadInterfaceInStream(GetIID(), (LPUNKNOWN)SafeGet(),
		&iStreamSCP.GetRawPointer());
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_UNABLE_TO_MARSHAL_ITNERF_TO_STREAM, IDPAGE_NOTAVAILABLE,
			SCODE_To_String(hr));
	}
	return iStreamSCP;
};

template <class T>
void SCP <T> :: UnMarshal(SCP <IStream> & riStreamSCP)
{
	ASSERT(PointsNull());
	HRESULT hr = ::CoGetInterfaceAndReleaseStream(riStreamSCP.Detach(), GetIID(),
		(void **)&GetRawPointer());
	if (hr != S_OK)
	{
		ThrowNavoException1(ERCO_UNABLE_TO_MARSHAL_ITERF_FROM_STREAM, IDPAGE_NOTAVAILABLE,
			SCODE_To_String(hr));
	}
};

#else
	#error __FILE__ "Already included"
#endif
