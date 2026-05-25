/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	miscelanous utilities

*/
#ifndef _MISCUTIL_H_
#define _MISCUTIL_H_

inline hyper longlong(long hi,long lo)
{
	hyper retval;
	((LARGE_INTEGER*)&retval)->LowPart = lo;
	((LARGE_INTEGER*)&retval)->HighPart = hi;
	return retval;
}

inline long lohyper(hyper val)
{
	return (long)((LARGE_INTEGER*)&val)->LowPart;
}

inline long hihyper(hyper val)
{
	return ((LARGE_INTEGER*)&val)->HighPart;
}

class CThreeIdent
{
public:
	CThreeIdent(long id1 = 0,long id2 = -1, long id3 = -1) :
		m_id1(id1),
		m_id2(id2),
		m_id3(id3)
	{
	}
	CThreeIdent(const CThreeIdent & roItemMoniker)
	{
		operator = (roItemMoniker);
	};
	virtual bool operator == (const CThreeIdent * pCtrlItemMoniker) const
	{
		ASSERT(pCtrlItemMoniker);
		return  (m_id1 == pCtrlItemMoniker->m_id1) &&
				(m_id2 == pCtrlItemMoniker->m_id2) &&
				(m_id3 == pCtrlItemMoniker->m_id3);
	}
	virtual void operator = (const CThreeIdent & roCtrlItemMoniker)
	{
		m_id1	= roCtrlItemMoniker.m_id1;
		m_id2	= roCtrlItemMoniker.m_id2;
		m_id3	= roCtrlItemMoniker.m_id3;
	}
	virtual bool operator == (const CThreeIdent & roCtrlItemMoniker) const
	{
		return (*this) == (&roCtrlItemMoniker);
	};
	long & GetId1()
	{
		return m_id1;
	}
	long & GetId2()
	{
		return m_id2;
	}
	long & GetId3()
	{
		return m_id3;
	}
	long GetId1() const
	{
		return m_id1;
	}
	long GetId2() const
	{
		return m_id2;
	}
	long GetId3() const
	{
		return m_id3;
	}
	long Hash() const
	{
		return (m_id1 << 4) + (m_id2 << 8) + (m_id3 << 12);
	};
protected:
	long m_id1;
	long m_id2;
	long m_id3;
};

template <>
inline UINT AFXAPI HashKey(CThreeIdent & roTIM)
{
	return HashKey <long> (const_cast<CThreeIdent &>(roTIM).Hash());
};

class CFourIdent : public CThreeIdent
{
public:
	CFourIdent(long id1 = 0,long id2 = -1, long id3 = -1, long id4 = -1) :
		CThreeIdent(id1,id2,id3),
		m_id4(id4)
	{
	}
	CFourIdent(const CFourIdent & roItemMoniker) :
		CThreeIdent(roItemMoniker),
		m_id4(roItemMoniker.m_id4)
	{
	};
	virtual bool operator == (const CFourIdent * pCtrlItemMoniker) const
	{
		ASSERT(pCtrlItemMoniker);
		return  CThreeIdent::operator ==(pCtrlItemMoniker) &&
			(m_id4 == pCtrlItemMoniker->m_id4);
	}
	virtual void operator = (const CFourIdent & roCtrlItemMoniker)
	{
		CThreeIdent::operator =(roCtrlItemMoniker);
		m_id4	= roCtrlItemMoniker.m_id4;
	}
	virtual bool operator == (const CFourIdent & roCtrlItemMoniker) const
	{
		return (*this) == (&roCtrlItemMoniker);
	};
	long & GetId4()
	{
		return m_id4;
	}
protected:
	long m_id4;
};

template <>
inline UINT AFXAPI HashKey(CFourIdent & roFIM)
{
	return HashKey <long> (const_cast<CFourIdent &>(roFIM).Hash());
};

//--------------------------------------------------------------------------
//	international settings support
//--------------------------------------------------------------------------
LCID GetWorkingLCID();
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//szyfruje i deszyfruje bufor
void DecodeBuffer(void * pBuffer, long lSize);
void EncodeBuffer(void * pBuffer, long lSize);


//character information functions
inline bool IsAlpha(TCHAR c)
{
	return isalpha((TBYTE)c) != 0;
}

inline bool IsAlphaNum(TCHAR c)
{
	return isalnum((TBYTE)c) != 0 || (c == '_');
}

inline bool IsSpace(TCHAR c)
{
	return isspace((TBYTE)c) != 0;
}

inline bool IsWhite(TCHAR cCharacter)
{
	return cCharacter == ' ' || cCharacter == '\t';
};

const TBYTE NON_BREAKING_SPACE = 160;

inline bool IsBreakingSpace(TCHAR c)
{
	return IsSpace(c) && (TBYTE)c != NON_BREAKING_SPACE;
}

inline bool IsDigit(TCHAR c)
{
	return isdigit((TBYTE)c) != 0;
}

inline bool IsUpper(TCHAR c)
{
	return isupper((TBYTE)c) != 0;
}

inline bool IsLower(TCHAR c)
{
	return islower((TBYTE)c) != 0;
}

inline TCHAR ToUpper(TCHAR c)
{
	return TCHAR(toupper((TBYTE)c));
}

inline TCHAR ToLower(TCHAR c)
{
	return TCHAR(tolower((TBYTE)c));
}

//dzia³a jak strstr ale case-insensitive
const TCHAR * FindSubStrNoCase(const TCHAR * pcSource, const TCHAR * pcDest); 

inline CString Long2String(long lValue, int nRadix = 10) // converts long to CString
{
	TCHAR cBuffer[ 36 ];
	return _ltot( lValue, cBuffer, nRadix );
}

inline bool String2Long(LPCTSTR pcString, long & lValue)
{
	TCHAR *pcErrorPointer;
	lValue = _tcstol(pcString, &pcErrorPointer, 10);
	bool bResult = *pcErrorPointer == '\0';
	if (!bResult)
	{
		lValue = 0;
	};
	return bResult;
};

//dzieli OleDateTime na kawa³ki
void OleDate2Parts(const COleDateTime & roOleDateTime,
				   int & nYear,int & nMonth,int & nDay,
				   int & nHour,int & nMin,int & nSecond);

//zamienia string na tablicê stringów, kryterium podzia³u jest cSeparator 
//Domyslnie separatorem sa dowolne odstepy (wg IsSpace)
//bAddEmptyItems - okreœla czy dodawaæ puste stringi
// 
CStringArray & SplitString(const CString &roString,CStringArray &roArray, TCHAR cSeparator = '\0',bool bAddEmptyItems = false);

// jw. ale separatorem sa odstepy rozdzielajace, tzn. te, dla ktorych 
// IsBreakingSpace(c) zwraca true
CStringArray & SplitStringBreakingSpaces(const CString &roString,CStringArray &roArray, bool bAddEmptyItems = false);

//zamienia zwyk³y string na UTF-8 string (uzywany w Internecie)
void StringToUTF8(LPCSTR lpString,CString & roResultString);

inline bool IsWhiteSpaceOnly(LPCTSTR lpText)
{
	while(*lpText)
	{
		if(!IsBreakingSpace(*lpText))
		{
			return false;
		}
		lpText++;	//macro safe
	}
	return true;
}

CString EscapeString(const CString & roString);
//-------------------- CBstr ------------------
//
//obudowa na BSTR
//
//---------------------------------------------

class CBStr
{
public:
	enum EAllocType
	{
		COALLOC,
		SYSALLOC,
	};
	CBStr(EAllocType eAllocType = SYSALLOC):
		m_eAllocType(eAllocType),
		m_pwcString(NULL)
	{
	};
	CBStr(const CBStr & roBStr)
	{
		*this = roBStr;
	};
	CBStr(LPCWSTR pBStr, EAllocType eAllocType = SYSALLOC):
		m_pwcString(NULL),
		m_eAllocType(eAllocType)
	{
		operator = (pBStr);
	};
	CBStr(const char *pcText, EAllocType eAllocType = SYSALLOC):
		m_eAllocType(eAllocType)
	{
		ASSERT(pcText);
		long lLength = strlen(pcText);
		Alloc((lLength + 1) * 2);
		MultiByteToWideChar(CP_ACP, 0, pcText, lLength + 1,
			m_pwcString, (lLength + 1) * 2 / sizeof(OLECHAR));
	};
	CBStr(const char *pcText, long lLength, EAllocType eAllocType = SYSALLOC):
		m_eAllocType(eAllocType)
	{
		ASSERT(pcText);
		Alloc((lLength + 1) * 2);
		MultiByteToWideChar(CP_ACP, 0, pcText, lLength + 1,
			m_pwcString, (lLength + 1) * 2 / sizeof(OLECHAR));
	};
	CBStr(const CString & roString, EAllocType eAllocType = SYSALLOC):
		m_eAllocType(eAllocType)
	{
#ifdef _UNICODE
		operator = (LPCWSTR(roString));
#else
		Alloc((roString.GetLength() + 1) * 2);
		MultiByteToWideChar(CP_ACP, 0, roString, roString.GetLength() + 1,
			m_pwcString, (roString.GetLength() + 1) * 2 / sizeof(OLECHAR));
#endif
	};
	~CBStr()
	{
		Free();
	};
	operator LPCWSTR () const
	{
		ASSERT(m_pwcString);
		return m_pwcString;
	};
	CBStr & operator = (const CBStr & roBStr)
	{
		return operator = ((LPCWSTR)roBStr);
	};
	CBStr & operator = (LPCWSTR pwcString)
	{
		Free();
		m_pwcString = ::SysAllocString(pwcString);
		if (!m_pwcString)
		{
			ThrowNavoException(ERCO_NOT_ENOUGH_MEMORY_IN_BSTR, IDPAGE_NOTAVAILABLE);
		};
		return *this;
	};
	BSTR & GetRawPointer()
	{
		ASSERT(m_pwcString == NULL);
		return m_pwcString;
	};
	bool PointsString()
	{
		return m_pwcString != NULL;
	};
	bool PointsNull()
	{
		return m_pwcString == NULL;
	};
	bool CompareNoCase(LPCWSTR pwcString) const
	{
		return _wcsicmp(m_pwcString, pwcString) == 0;
	};
	bool operator == (LPCWSTR pwcString) const
	{
		return wcscmp(m_pwcString, pwcString) == 0;
	};
	bool operator != (LPCWSTR pwcString) const
	{
		return wcscmp(m_pwcString, pwcString) != 0;
	};
	void ToUpper()
	{
		ASSERT(PointsString());
		_wcsupr(m_pwcString);
	};
	void ToLower()
	{
		ASSERT(PointsString());
		_wcslwr(m_pwcString);
	};
	void Free()
	{
		if (m_pwcString)
		{
			m_eAllocType == SYSALLOC ? ::SysFreeString(m_pwcString) : ::CoTaskMemFree(m_pwcString);
		};
	};
	void Attach(BSTR & pBStr, EAllocType eAllocType = SYSALLOC)
	{
		ASSERT(!m_pwcString);
		m_eAllocType = eAllocType;
		m_pwcString = pBStr;
		pBStr = NULL;
	};
	BSTR Detach()
	{
		BSTR pwcString = m_pwcString;
		m_pwcString = NULL;
		return pwcString;
	};
private:
	void Alloc(long lSize)
	{
		m_pwcString = m_eAllocType == SYSALLOC ? ::SysAllocStringByteLen(NULL, lSize) : (BSTR)::CoTaskMemAlloc(lSize);
		if (!m_pwcString)
		{
			ThrowNavoException(ERCO_NOT_ENOUGH_MEMORY_IN_BSTR, IDPAGE_NOTAVAILABLE);
		};
	};

	BSTR m_pwcString;
	EAllocType m_eAllocType;
};

//-------------------- CICSBStr ---------------
//
//case-insensitive CBStr
//
//---------------------------------------------

class CICSBStr: public CBStr
{
public:
	CICSBStr()
	{
	};
	CICSBStr(const CICSBStr & roBStr):
		CBStr(roBStr)
	{
	};
	CICSBStr(LPCWSTR pBStr):
		CBStr(pBStr)
	{
	};
	CICSBStr(LPCSTR pcStr):
		CBStr(pcStr)
	{
	};
	bool operator == (LPCWSTR pwcStr) const
	{
		return CompareNoCase(pwcStr);
	};
	CICSBStr & operator = (LPCWSTR pwcStr)
	{
		CBStr::operator = (pwcStr);
		return *this;
	};
};

//-------------- CICSBStrArgKey ---------------
//
//case-insensitive CBStr (argkey do mapy)
//
//---------------------------------------------

class CICSBStrArgKey
{
public:
	CICSBStrArgKey(const CICSBStr & roBStr):
		m_pcStr(roBStr.operator LPCWSTR())
	{
	};
	CICSBStrArgKey(const CBStr & roBStr):
		m_pcStr(roBStr.operator LPCWSTR())
	{
	};
	CICSBStrArgKey(LPCWSTR pcStr):
		m_pcStr(pcStr)
	{
	};
	CICSBStrArgKey(const CICSBStrArgKey & roArgKey):
		m_pcStr(roArgKey.m_pcStr)
	{
	};
	operator LPCWSTR () const
	{
		return m_pcStr;
	};

private:
	LPCWSTR m_pcStr;
	friend UINT AFXAPI HashKey(CICSBStrArgKey);
};


//------------- CArrayWriter ------------------
//
//samorosn¹ca tablica
//
//UWAGA! mo¿e nie dzia³aæ dla bardziej skomplikowanych typów (memcpy)
//---------------------------------------------

template <class T>
class CArrayWriter
{
public:
	CArrayWriter(CArray <T, T &> & roArray):
		m_roArray(roArray)
	{
		Reset();
		ASSERT(m_poT);
		ASSERT(m_lCounter == 0);
	};
	CArrayWriter & operator << (T oT)
	{
		if (m_lCounter == m_roArray.GetSize())
		{
			m_roArray.SetSize(m_roArray.GetSize() * 2);
			m_poT = &m_roArray[m_lCounter];
		};
		*m_poT++ = oT;
		m_lCounter++;
		return *this;
	};
	CArrayWriter & Write(const T * poT, long lLength)
	{
		ASSERT(lLength >= 0);
		if (m_lCounter + lLength >= m_roArray.GetSize())
		{
			long lNewSize = m_roArray.GetSize() * 2;
			if (lNewSize < m_lCounter + lLength)
			{
				lNewSize = m_lCounter + lLength;
			};
			m_roArray.SetSize(lNewSize);
			m_poT = &m_roArray[m_lCounter];
		};
		//TO_DO: memcpy jest podejrzane, gdy <T> nie jest prosty (?)
		memcpy(m_poT, poT, sizeof(T) * lLength);
		m_lCounter += lLength;
		m_poT += lLength;
		return *this;
	};
	void Reset()
	{
		m_roArray.SetSize(1024);
		m_lCounter = 0;
		m_poT = &m_roArray[m_lCounter];
	}
	const long CharactersWritten() const
	{
		ASSERT(m_lCounter >= 0);
		return m_lCounter;
	};

private:
	CArray <T, T &> & m_roArray;
	T * m_poT;
	long m_lCounter;
};

//------------- CEnhancedStack ------------------
//
//Stos z mozliwoscia dostepu do dowolnego elementu
//
//---------------------------------------------

template <class T>
class CEnhancedStack: protected CList <T, T &>
{
public:
	void Push(T & oT)
	{
		CList <T, T &> :: AddHead(oT);
	};
	T Pop ()
	{
		return RemoveHead();
	};
	bool IsEmpty() const
	{
		return CList <T, T &>::IsEmpty() != FALSE;
	};
	POSITION GetTopPosition() const
	{
		return GetHeadPosition();
	};
	POSITION GetBottomPosition() const
	{
		return GetTailPosition();
	};
	T & MoveDown(POSITION & oPosition)
	{
		return GetNext(oPosition);
	};
	const T & MoveDown(POSITION & oPosition) const
	{
		return GetNext(oPosition);
	};
	T & MoveUp(POSITION & oPosition)
	{
		return GetPrev(oPosition);
	};
	const T & MoveUp(POSITION & oPosition) const
	{
		return GetPrev(oPosition);
	};
	T & GetTop()
	{
		return GetHead();
	};
	const T & GetTop() const
	{
		return GetHead();
	};
	T & GetBottom()
	{
		return GetTail();
	};
	const T & GetBottom() const
	{
		return GetTail();
	};
	T & GetAt(POSITION oPosition)
	{
		return CList <T, T &>::GetAt(oPosition);
	};
	const T & GetAt(POSITION oPosition) const
	{
		return CList <T, T &> :: GetAt(oPosition);
	};
	void RemoveAt(POSITION oPosition)
	{
		ASSERT(oPosition);
		CList <T, T &> :: RemoveAt(oPosition);
	};
	void RemoveAtAndMoveDown(POSITION & oPosition)
	{
		ASSERT(oPosition);
		POSITION TempPos = oPosition;
		MoveDown(oPosition);
		RemoveAt(TempPos);
	};
	void RemoveAtAndMoveUp(POSITION & oPosition)
	{
		ASSERT(oPosition);
		POSITION TempPos = oPosition;
		MoveUp(oPosition);
		RemoveAt(TempPos);
	};
	long GetCount() const
	{
		return CList <T, T &> :: GetCount();
	}
};

//------------- CPushStackHolder  ------------------
//
// Holder na operacje na stosie
//
//---------------------------------------------

template <class T>
class CPushStackHolder : public CInterface__
{
public:
	CPushStackHolder(CEnhancedStack <T> & roStack, T & roT):
		m_roStack(roStack)
	{
		m_roStack.Push(roT);
	};
	~CPushStackHolder()
	{
		m_roStack.Pop();
	};
private:
	CEnhancedStack <T> & m_roStack;
};

//------------- CFastList --------------------------
//
// uporz¹dkowana lista unikalnych elementów 
// z szybk¹ mo¿liwoœci¹ sprawdzenia czy ju¿ istnieje
//
//--------------------------------------------------

template <class T>
class CFastList
{
public:
	CFastList()
	{
	};
	void _init_hash_table(UINT nSize)
	{
		m_oMap.InitHashTable(nSize);
	}
	void Add(T & oT)
	{
		ASSERT(!Exists(oT));
		m_oMap[ oT ] = m_oList.AddTail( oT );
	};
	void InsertAfter(T & roT,T & roAfterT)
	{
		POSITION pos;
		VERIFY( m_oMap.Lookup(roAfterT,pos) );
		m_oMap[ roT ] = m_oList.InsertAfter(pos, roT );
	}
	void Remove(T & oT)
	{
		POSITION pos;
		VERIFY( m_oMap.Lookup(oT,pos) );
		VERIFY(m_oMap.RemoveKey( oT ));
		m_oList.RemoveAt( pos );
	}
	bool Exists(T & oT) const
	{
		POSITION dummy;
		return m_oMap.Lookup(oT, dummy) != FALSE;
	};
	
	POSITION GetFirstPosition() const
	{
		return m_oList.GetHeadPosition();
	};
	POSITION GetLastPosition() const
	{
		return m_oList.GetTailPosition();
	};
	
	const T & GetNext(POSITION & roPosition) const
	{
		ASSERT(roPosition != NULL);
		return m_oList.GetNext(roPosition);
	};
	T & GetAt(POSITION oPosition)
	{
		return m_oList.GetAt(oPosition);
	}
	POSITION GetPositionOf(T & oT) const
	{
		POSITION oPosition;
		VERIFY(m_oMap.Lookup(oT,oPosition));
		return oPosition;
	}
	
	const T * SafeGetAt(const T &  roT) const
	{
		POSITION oPosition;
		if (!m_oMap.Lookup(roT, oPosition))
		{
			return NULL;
		};
		return &m_oList.GetAt(oPosition);
	}

	T * SafeGetAt(const T &  roT)
	{
		POSITION oPosition;
		if (!m_oMap.Lookup(roT, oPosition))
		{
			return NULL;
		};
		return &m_oList.GetAt(oPosition);
	}
	
	T & GetNext(POSITION & roPosition)
	{
		ASSERT(roPosition != NULL);
		return m_oList.GetNext(roPosition);
	};
	const T & GetPrev(POSITION & roPosition) const
	{
		ASSERT(roPosition != NULL);
		return m_oList.GetPrev(roPosition);
	};
	T & GetPrev(POSITION & roPosition)
	{
		ASSERT(roPosition != NULL);
		return m_oList.GetPrev(roPosition);
	};

	void RemoveAll()
	{
		m_oMap.RemoveAll();
		m_oList.RemoveAll();
	}
	long GetCount() const
	{
		ASSERT(m_oList.GetCount() == m_oMap.GetCount());
		return m_oList.GetCount();
	}
private:

	CList <T, T &> m_oList;
	CMap <T,T, POSITION, POSITION&> m_oMap;
};

//------------- CIndexedList -----------------------
//
// uporz¹dkowana lista z szybkim dostêpem (random)
// poprzez index (na mapie)
//
// prosta implementacja indeksu w sensie bazy danych
//--------------------------------------------------

template <class T, class TD>
class CTTD
{
public:
	CTTD()
	{
	};
	CTTD(T & oT, TD & oTD):
		m_oT(oT),
		m_oTD(oTD)
	{
	};
	CTTD & operator = (CTTD & roTTD)
	{
		m_oT = roTTD.m_oT;
		m_oTD = roTTD.m_oTD;
		return *this;
	};

	T m_oT;
	TD m_oTD;
};

template <class T, class ARGT, class TD>
class CIndexedList
{
public:
	CIndexedList()
	{
	};
	void _init_hash_table(UINT nSize)
	{
		m_oMap.InitHashTable(nSize);
	}
	void Add(T & oT, TD oTD)
	{
		ASSERT(!Exists(oT));

		CTTD <T, TD> oCTTD(oT, oTD);
		m_oMap[oT] = m_oList.AddTail(oCTTD);
#ifdef _DEBUG
		TestItself();
#endif
	};
	void InsertAfter(T & oT, TD oTD,T & oAfterT)
	{
		POSITION oPosition;
		VERIFY(m_oMap.Lookup(oAfterT,oPosition));
		CTTD <T, TD> oCTTD(oT, oTD);
		m_oMap[oT] = m_oList.InsertAfter(oPosition,oCTTD);
#ifdef _DEBUG
		TestItself();
#endif
	}
	void Remove(T & oT)
	{
		ASSERT(Exists(oT));
		m_oList.RemoveAt(m_oMap[oT]);
		VERIFY(m_oMap.RemoveKey(oT));
#ifdef _DEBUG
		TestItself();
#endif
	};
	void RemoveAtPosition(POSITION pos)
	{
		VERIFY(m_oMap.RemoveKey(m_oList.GetAt(pos).m_oT));
		m_oList.RemoveAt(pos);
#ifdef _DEBUG
		TestItself();
#endif
	}
	bool Exists(ARGT oT) const
	{
		POSITION oPosition;
		return m_oMap.Lookup(oT, oPosition) != FALSE;
	};
	POSITION GetFirstPosition() const
	{
		return m_oList.GetHeadPosition();
	};
	POSITION GetLastPosition() const
	{
		return m_oList.GetTailPosition();
	};
	POSITION GetPositionOf(T & oT) const
	{
		POSITION oPosition;
		VERIFY(m_oMap.Lookup(oT,oPosition));
		return oPosition;
	}
	POSITION SafeGetPositionOf(T & oT) const
	{
		POSITION oPosition;
		if(!m_oMap.Lookup(oT,oPosition))
		{
			return NULL;
		}
		return oPosition;
	}
	const TD & GetNext(POSITION & roPosition, T & roT) const
	{
		ASSERT(roPosition != NULL);
		const CTTD <T, TD> & rCTTD = m_oList.GetNext(roPosition);
		roT = rCTTD.m_oT;
		return rCTTD.m_oTD;
	};
	const TD & GetPrev(POSITION & roPosition, T & roT) const
	{
		ASSERT(roPosition != NULL);
		const CTTD <T, TD> & rCTTD = m_oList.GetPrev(roPosition);
		roT = rCTTD.m_oT;
		return rCTTD.m_oTD;
	};
	const TD & GetAt(ARGT oT) const
	{
		POSITION oPosition;
		VERIFY(m_oMap.Lookup(oT, oPosition));
#ifdef _DEBUG
		TestItself();
#endif
		return m_oList.GetAt(oPosition).m_oTD;
	};
	TD & GetAtPosition(POSITION oPosition)
	{
		return m_oList.GetAt(oPosition).m_oTD;
	}
	TD & GetAt(ARGT oT)
	{
		POSITION oPosition;
		VERIFY(m_oMap.Lookup(oT, oPosition));
#ifdef _DEBUG
		TestItself();
#endif
		return m_oList.GetAt(oPosition).m_oTD;
	};
	const TD * SafeGetAt(ARGT oT) const
	{
		POSITION oPosition;
		if (!m_oMap.Lookup(oT, oPosition))
		{
			return NULL;
		};
		return &m_oList.GetAt(oPosition).m_oTD;
	};
	TD * SafeGetAt(ARGT oT)
	{
		POSITION oPosition;
		if (!m_oMap.Lookup(oT, oPosition))
		{
			return NULL;
		};
		return &m_oList.GetAt(oPosition).m_oTD;
	};
	TD & GetNext(POSITION & roPosition, T & roT)
	{
#ifdef _DEBUG
		TestItself();
#endif
		ASSERT(roPosition != NULL);
		CTTD <T, TD> & rCTTD = m_oList.GetNext(roPosition);
		roT = rCTTD.m_oT;
		return rCTTD.m_oTD;
	};
	TD & GetPrev(POSITION & roPosition, T & roT)
	{
		ASSERT(roPosition != NULL);
		CTTD <T, TD> & rCTTD = m_oList.GetPrev(roPosition);
		roT = rCTTD.m_oT;
		return rCTTD.m_oTD;
	};
	void RemoveAll()
	{
		m_oList.RemoveAll();
		m_oMap.RemoveAll();
	};

	long GetCount() const
	{
		ASSERT(m_oList.GetCount() == m_oMap.GetCount());
		return m_oList.GetCount();
	}
	CList <CTTD <T, TD>, CTTD <T, TD> &> m_oList;
	CMap <T, ARGT, POSITION, POSITION &> m_oMap;

#ifdef _DEBUG
	void TestItself() const
	{
		ASSERT(m_oList.GetCount() == m_oMap.GetCount());
	/*	
		POSITION pos = m_oMap.GetStartPosition();
		while(pos)
		{
			T key;
			POSITION value;
			m_oMap.GetNextAssoc(pos,key,value);
			ASSERT(m_oList.GetAt(value).m_oT == key);
		}
	*/
	}
#endif
};

//------------- CArrayOfSCP  ------------------
//
//  Tablica SCP bêd¹ca sama SCP
//
//---------------------------------------------
template<class T>
class CArrayOfSCP : public CArray<SCP<T>, SCP<T> &>, public CInterface__
{
public:
	CArrayOfSCP()	{}
	~CArrayOfSCP()	{}
};

//---------CIncDecHolder-----------
//	holder zliczaj¹cy np. u¿ycia, rekursjê
//	dzia³a na dowolnej klasie implementuj¹cej operator ++ i -- oraz operator long()
//---------------------------------

template<typename T>
class CIncDecHolder
{
public:
	CIncDecHolder(T & roCounter) :
	  m_roCounter(roCounter)
	{
		m_roCounter++;
	}
	~CIncDecHolder()
	{
		m_roCounter--;
		ASSERT(m_roCounter >= 0);
	}
private:
	T & m_roCounter;
};

//---------------------------------
//INLINES
//---------------------------------

inline void DecodeBuffer(void * pBuffer, long lSize)
{
	for (long lIndex = 0; lIndex < lSize; lIndex++)
	{
		((unsigned char *)pBuffer)[lIndex] = (unsigned char)~(((unsigned char *)pBuffer)[lIndex]);
	};
};

inline void EncodeBuffer(void * pBuffer, long lSize)
{
	DecodeBuffer(pBuffer, lSize);
};

inline const TCHAR * FindSubStrNoCase(const TCHAR * pcSource, const TCHAR * pcPattern)
{
	CString oSourceString(pcSource);
	CString oPaternString(pcPattern);
	oSourceString.MakeLower();
	oPaternString.MakeLower();
	int nPosition = oSourceString.Find(oPaternString);
	if(nPosition == -1)
	{
		return NULL;
	}
	return pcSource + nPosition;
}

template<class TYPE, class ARG_TYPE>
inline void SortAsc(CArray<TYPE,ARG_TYPE> & roArray)
{
	bool bChange;
	do
	{
		bChange = false;
		for(long iter = 0; iter < roArray.GetUpperBound(); iter++)
		{
			if(roArray[iter] > roArray[iter+1])
			{
				bChange = true;
				TYPE tmp = roArray[iter];
				roArray[iter] = roArray[iter+1];
				roArray[iter+1] = tmp;
			}
		}
	}
	while(bChange);
}

template<class TYPE, class ARG_TYPE>
inline void SortDesc(CArray<TYPE,ARG_TYPE> & roArray)
{
	bool bChange;
	do
	{
		bChange = false;
		for(long iter = 0; iter < roArray.GetUpperBound(); iter++)
		{
			if(roArray[iter] < roArray[iter+1])
			{
				bChange = true;
				TYPE tmp = roArray[iter];
				roArray[iter] = roArray[iter+1];
				roArray[iter+1] = tmp;
			}
		}
	}
	while(bChange);
}

//------------------------------------
// holder na AfxGet/SetResourceHandle
//------------------------------------

class CAfxResourceHandleHolder
{
public:
	CAfxResourceHandleHolder(HINSTANCE hNewResourceHandler) :
	  m_hInstance(::AfxGetResourceHandle())
	{
		::AfxSetResourceHandle(hNewResourceHandler);
	}
	~CAfxResourceHandleHolder()
	{
		::AfxSetResourceHandle(m_hInstance);
	}
private:
	HINSTANCE m_hInstance;
};

#ifdef _DEBUG
class CDebugTimeMeter
{
public:
	CDebugTimeMeter(LPCTSTR lpMsgStr,long nLowerThreshold = 0) :
		m_oMessageString(lpMsgStr),
		m_nStartTime((long)::GetTickCount()),		//OS_API_CALL
		m_nLowerThreshold(nLowerThreshold)
	{
	}
	~CDebugTimeMeter()
	{
		//OS_API_CALL
		long nTimeElapsed = long(::GetTickCount()-m_nStartTime);
		if(nTimeElapsed >= m_nLowerThreshold)
		{
			TRACE2("%s,time=%d\n",m_oMessageString,nTimeElapsed);
		}
	}
private:
	long m_nStartTime;
	long m_nLowerThreshold;
	CString m_oMessageString;
};

#endif

#ifndef _MINI_CORE_

template <class T>
class CEnumerableCollection
{
public:
	CEnumerableCollection(){}
	virtual bool IsElementAt(long nPosition) = 0;
	virtual T GetElementAt(long nPosition) = 0;
};

template <class T,class ARGT>
class CEnumerableArray : public CArray<T, ARGT>, public CEnumerableCollection<T>
{
public:
	virtual bool IsElementAt(long nPosition)
	{
		return (GetUpperBound() >= nPosition) && (nPosition >= 0);
	}
	virtual T GetElementAt(long nPosition) 
	{
		return ElementAt(nPosition);
	}
};

template <class T,class ARGT>
class CEnumerableArray_SCP : public CEnumerableArray<T, ARGT>, public CInterface__
{
public:
};

template <class T>
class CArrayEnumeratorBase__ : public CCmdTargetInterface
{
public:
	CArrayEnumeratorBase__(CEnumerableCollection<T> & roEnumerableCollection) :
		m_roEnumerableCollection(roEnumerableCollection),
		m_lPosition(0)
	{
		EnableAutomation();
	}
	CArrayEnumeratorBase__(const CArrayEnumeratorBase__ & roArrayEnumerator) :
		m_roEnumerableCollection(roArrayEnumerator.m_roEnumerableCollection),
		m_lPosition(roArrayEnumerator.m_lPosition)
	{
		EnableAutomation();
	}
	bool Next(long lElements, CSmartOleVariant * pVariants, long *plElementsFetched)
	{
		if (plElementsFetched)
		{
			*plElementsFetched = 0;
		};
		long lIndex, lLP;
		for (lIndex = 0, lLP = GetPosition(); lIndex < lElements; lIndex++, lLP++)
		{
			if(!m_roEnumerableCollection.IsElementAt(lLP))
			{
				break;
			}
			T oElement = m_roEnumerableCollection.GetElementAt( lLP );
			ConvertItem(*pVariants,oElement);
		};
		if (plElementsFetched)
		{
			*plElementsFetched = lIndex;
		};
		m_lPosition = lLP;
		return lIndex == lElements;
	};
	bool Skip(ULONG lValue)
	{
		if(m_roEnumerableCollection.IsElementAt(GetPosition() + lValue))
		{
			m_lPosition += lValue;
			return true;
		};
		return false;
	};
	void Reset()
	{
		m_lPosition = 0;
	};
	SCP < CArrayEnumeratorBase__<T> > Clone()
	{
		return NewSCP(new CArrayEnumeratorBase__<T>(*this));
	};
	SCP <IEnumVARIANT> GetEnumVARIANT()
	{
		return NewSCP(&m_xEnumVariant, true);
	};
	long GetPosition() const
	{
		return m_lPosition;
	};
	virtual void ConvertItem(CSmartOleVariant & /*roSOV*/, T & /*roElement*/)
	{
	};
	//{{AFX_DISPATCH(CArrayEnumeratorBase__<T>)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(EnumVariant, IEnumVARIANT)
		HRESULT STDMETHODCALLTYPE Next(ULONG celt,VARIANT *rgVar,ULONG *pCeltFetched)
		{
			METHOD_PROLOGUE(CArrayEnumeratorBase__<T>, EnumVariant);
			ALL_TRY
			{
				for (ULONG lIndex = 0; lIndex < celt; lIndex++)
				{
					::VariantInit(&rgVar[lIndex]);
				};
				return pThis->Next((long)celt, (CSmartOleVariant *)((void *)rgVar), (long *)pCeltFetched) ? S_OK : S_FALSE;
			}
			ALL_CATCH(CNavoException & /*to_do: roException */)
			{
				for (ULONG lIndex = 0; lIndex < celt; lIndex++)
				{
					::VariantClear(&rgVar[lIndex]);
				};
				//to_do:
				return DISP_E_EXCEPTION;
			};
		};
		HRESULT STDMETHODCALLTYPE Skip(
			/* [in] */ ULONG celt)
		{
			METHOD_PROLOGUE(CArrayEnumeratorBase__<T>, EnumVariant);
			ALL_TRY
			{
				return pThis->Skip(celt) ? S_OK : S_FALSE;
			}
			ALL_CATCH(CNavoException & /*to_do: roException*/)
			{
				//to_do:
				return DISP_E_EXCEPTION;
			};
		};
		HRESULT STDMETHODCALLTYPE Reset( void)
		{
			METHOD_PROLOGUE(CArrayEnumeratorBase__<T>, EnumVariant);
			pThis->Reset();
			return S_OK;
		};
		HRESULT STDMETHODCALLTYPE Clone(
			/* [out] */ IEnumVARIANT __RPC_FAR *__RPC_FAR *ppEnum)
		{
			METHOD_PROLOGUE(CArrayEnumeratorBase__<T>, EnumVariant);
			ALL_TRY
			{
				*ppEnum = pThis->Clone()->GetEnumVARIANT().Detach();
			}
			ALL_CATCH(CNavoException & /*to_do: roException */)
			{
				//to_do:
				return DISP_E_EXCEPTION;
			};
			return S_OK;
		};
	END_INTERFACE_PART(EnumVariant)
private:
	CEnumerableCollection<T> & m_roEnumerableCollection;
	long m_lPosition;
};

#define IMPLEMENT_ARRAYENUMERATOR(_T_) \
	BEGIN_INTERFACE_MAP(CArrayEnumeratorBase__< _T_ >, CCmdTarget) \
		INTERFACE_PART(CArrayEnumeratorBase__< _T_ >, IID_IEnumVARIANT, EnumVariant) \
	END_INTERFACE_MAP() \
	DELEGATE_UNKNOWN_INTERFACE(CArrayEnumeratorBase__< _T_ >, EnumVariant)  \
	BEGIN_DISPATCH_MAP(CArrayEnumeratorBase__< _T_ >, CCmdTarget) \
	END_DISPATCH_MAP()


template <class T>
class CArrayEnumerator : public CArrayEnumeratorBase__<T>
{
public:
	CArrayEnumerator(CEnumerableCollection<T> & roEnumerableCollection) :
	  CArrayEnumeratorBase__<T>(roEnumerableCollection)
	{
	}
	CArrayEnumerator(const CArrayEnumerator & roArrayEnumerator) :
		CArrayEnumeratorBase__<T>(roArrayEnumerator)
	{
	}
	virtual void ConvertItem(CSmartOleVariant & roSOV, T & roElement)
	{
		SCP<IDispatch> poDispatchSP;
		poDispatchSP.QueryInterface(roElement);
		roSOV = CSmartOleVariant(poDispatchSP);
	}
};


template <class T>
class CArrayEnumeratorWithArray : public CArrayEnumerator< T >
{
public:
	CArrayEnumeratorWithArray(long nSize = 0);
	void SetAt(long iter,T & rT);
private:
	CEnumerableArray< T, T & > m_oEmbeddedArray;
};

template <class T>
inline CArrayEnumeratorWithArray<T>::CArrayEnumeratorWithArray(long nSize) :
	CArrayEnumerator< T >(m_oEmbeddedArray)
{
	m_oEmbeddedArray.SetSize(nSize);
}

template <class T>
inline void CArrayEnumeratorWithArray<T>::SetAt(long iter,T & rT)
{
	m_oEmbeddedArray[ iter ] = rT;
}

#endif //_MINI_CORE_

//-------- CParametersSplitter ----------------
//
//klasa do czytania commandline
// czyta argumenty -param1 value1 -param2 "value 2"
// gdzie param1, param2, ... mog¹ myæ stringami w przeciwieñstwie do poprzedniej wersji 
// gdzie by³y to chary
//
//---------------------------------------------

class CParametersSplitter
{
public:
	CParametersSplitter(const TCHAR *pcParameters)
	{
		Do(pcParameters);
	};
	bool GetParameter(LPCTSTR pcType, CString & roString) const
	{
		return m_oParametersMap.Lookup(pcType, roString) != FALSE;
	};
	bool GetParameter(LPCTSTR pcType) const
	{
		CString oString;
		return m_oParametersMap.Lookup(pcType, oString) != FALSE;
	};

private:
	void Do(const TCHAR * pcParameters);
	CMap <CString, LPCTSTR, CString, CString &> m_oParametersMap;	
};

bool ParsePropertyName(const TCHAR * pcSource, 
					   long & rlPropNumber, 
					   VARTYPE & rnPropType, 
					   const TCHAR * & pcStart, 
					   const TCHAR * & rpcTerminator);

//------------------------------
// Base64
//------------------------------
class Base64Coder;
class CBase64CoDec
{
public:
	CBase64CoDec(LPCVOID pBinary,long nBinLen);
	CBase64CoDec(LPCTSTR lpBase64);
	LPCTSTR Encoded() const;
	LPCVOID Decoded(DWORD & rnLen) const;
	~CBase64CoDec();
private:
	Base64Coder * m_poImplementation;
};

//------------------------------
//	CTagSplitter
//	CTagSplittingResult
//
//	klasy dziel¹ string na pary nazwa=wartoœæ
//	i mówi¹ co "przysz³o"
// 
//------------------------------

#define MAX_ASSOCIATE_ARGUMENTS 99

class CTagSplitter;

class CTagSplittingResult
{
public:
	CTagSplittingResult ()
	{
		memset (acResults, 0, sizeof (acResults));
	};
	bool operator [] (long lIndex) const
	{
		ASSERT (lIndex < MAX_ASSOCIATE_ARGUMENTS);
		return (acResults [lIndex / 8] & 1 << lIndex % 8) != 0;
	};
#ifdef _DEBUG
	void Dump()
	{
		for(long lIndex = 0; lIndex < MAX_ASSOCIATE_ARGUMENTS; lIndex++)
		{
			TRACE1("%c", operator [] (lIndex) ? '1' : '0');
		};
		TRACE(_T("\n"));
	};
#endif
private:
	void ResultOk (long lIndex)
	{
		ASSERT (lIndex < MAX_ASSOCIATE_ARGUMENTS);
		acResults [lIndex / 8] |= 1 << lIndex % 8;
	};

	TBYTE acResults [MAX_ASSOCIATE_ARGUMENTS / 8 + MAX_ASSOCIATE_ARGUMENTS % 8];
	friend CTagSplitter;
};

class CTagSplitter
{
public:
	CTagSplitter(LPCTSTR lpStr) :
		m_pCurrPtr(lpStr)
	{
	}

	bool NextItem(CString & szName,CString & szVal,bool bNameUpperCase = true, bool bValUpperCase = false);
	void Associate(CTagSplittingResult & oTagSplittingResult, const TCHAR * pcFormat, ...);	
private:
	LPCTSTR m_pCurrPtr;
};


#define MK_DBLCLK        0x0040		//dblclick

const CSmartOleVariant & GetNullDateSOV();
const CSmartOleVariant & GetNullTimeSOV();
//--------------------------------------------------------------------------
//	international settings support
//--------------------------------------------------------------------------
inline LCID GetWorkingLCID()
{
	return MAKELCID(MAKELANGID(LANG_POLISH,SUBLANG_NEUTRAL),SORT_DEFAULT);
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
LPCTSTR GetSetupAppName();
LPCTSTR GetNAVO2001RootRegistryKeyName();
LPCTSTR GetApplicationsRegistryKeyName();
LPCTSTR GetSetupRegistryKeyName();
LPCTSTR GetDatabaseRegistryKeyName();
LPCTSTR GetSupportRegistryKeyName();
bool IsSetupAppName(LPCTSTR lpAppName);
bool IsSlowConnection_Registry();

bool IsNXMTransport();
void SetNXMTransport(bool bDotNet);

LPCTSTR GetNAVO2001EngineVersion();

/*
	input:
		* pDestLen - rozmiar pDestBuffer
	output:
		* pDestLen - iloœæ danych w pDestBuffer
*/

void packbuffer(BYTE * pDestBuffer,unsigned long * pDestLen,const BYTE * pSrcBuffer,unsigned long nSrcLen);
void unpackbuffer(BYTE * pDestBuffer,unsigned long * pDestLen,const BYTE * pSrcBuffer,unsigned long nSrcLen);


#else
	#error __FILE__ already included
#endif
