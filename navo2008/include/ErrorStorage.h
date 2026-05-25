// ===========================================================================
//
// NAVO Enterprise 2001
//
// Error support
//
// error support utils
//
// ===========================================================================


#ifndef _ERRORSTORAGE_H_
#define _ERRORSTORAGE_H_

class CGenericErrorStorage : public CNavoException
{
public:
	CGenericErrorStorage()
	{
	}
	~CGenericErrorStorage()
	{
		ASSERT(m_oNEIArray.GetSize() == 0);
	}
	HRESULT RetrieveError(long *pDataLength, byte ** lpBinaryData);
	HRESULT RetrieveError2(LPSTR * ppcErrors);
};

#define DELEGATE_NAVOERRORINFO_ON_GENERICERRORSTORAGE( _outerclass_, __member_ ) \
	BEGIN_INTERFACE_PART(NavoErrorInfo,INavoErrorInfo) \
		STDMETHOD(RetrieveError)(long *pDataLength,byte ** lpBinaryData) \
		{ \
			METHOD_PROLOGUE(_outerclass_, NavoErrorInfo) \
			return pThis->__member_.RetrieveError(pDataLength,lpBinaryData); \
		} \
		STDMETHOD(RetrieveError2)(LPSTR * ppcErrors) \
		{ \
			METHOD_PROLOGUE(_outerclass_, NavoErrorInfo) \
			return pThis->__member_.RetrieveError2(ppcErrors); \
		} \
	END_INTERFACE_PART(NavoErrorInfo)
	
class CCmdTargetWithErrorInfo : public CCmdTargetInterface
{
public:
	CCmdTargetWithErrorInfo() : 
	  CCmdTargetInterface()
	{
	}

#undef NAVO_CLASS_DECL
#ifdef THIS_IS_NAVOCORE
#define NAVO_CLASS_DECL _declspec(dllexport)
#else
#define NAVO_CLASS_DECL _declspec(dllimport)
#endif
#undef  AFX_DATA
#define AFX_DATA NAVO_CLASS_DECL

	DECLARE_INTERFACE_MAP();

	DELEGATE_NAVOERRORINFO_ON_GENERICERRORSTORAGE(CCmdTargetWithErrorInfo , m_oErrorStorage);

public:
    virtual CNavoException & GetErrorStorage()
	{
		return m_oErrorStorage;
	}
protected:
	CGenericErrorStorage m_oErrorStorage;
};

#undef  AFX_DATA
#define AFX_DATA

#else
	#error this __FILE__ was included
#endif
