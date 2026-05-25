// ===========================================================================
//
// NAVO Enterprise 2001
//
// Error support
//
// error support utils
//
// ===========================================================================

#ifndef _ERRORSUPPORT_H_
#define _ERRORSUPPORT_H_

struct IErrorInfo;
/// basic error information unit
class CNavoErrorInfo
{
public:
	CNavoErrorInfo() :
		m_erco(ERCO_NOTAVAILABLE),
		m_idHelp(IDPAGE_NOTAVAILABLE)
	{
	}
	CNavoErrorInfo(const CNavoErrorInfo & roNavoErrorInfo) :
		m_erco(roNavoErrorInfo.m_erco),
		m_idHelp(roNavoErrorInfo.m_idHelp),
		m_oErrorDescriptionString(roNavoErrorInfo.m_oErrorDescriptionString)
	{
	}
	CNavoErrorInfo(errorcode erco,long idHelp,const CString & roDescription) :
		m_erco(erco),
		m_idHelp(idHelp),
		m_oErrorDescriptionString(roDescription)
	{
	}
	virtual void operator = (const CNavoErrorInfo & roNavoErrorInfo)
	{
		m_erco = roNavoErrorInfo.m_erco;
		m_idHelp = roNavoErrorInfo.m_idHelp;
		m_oErrorDescriptionString = roNavoErrorInfo.m_oErrorDescriptionString;
	}
	errorcode GetErroCode() const
	{
		return m_erco;
	}
	long GetHelpId() const
	{
		return m_idHelp;
	}
	LPCTSTR GetErrorString() const
	{
		return m_oErrorDescriptionString;
	}
	CString BuildErrorString() const;
	friend CArchive & AFXAPI operator << (CArchive & oArchive,const CNavoErrorInfo & roNavoErrorInfo);
	friend CArchive & AFXAPI operator >> (CArchive & oArchive, CNavoErrorInfo & roNavoErrorInfo);
private:
	errorcode m_erco;
	long	  m_idHelp;
	CString	  m_oErrorDescriptionString;
};

inline CArchive & AFXAPI operator << (CArchive & oArchive,const CNavoErrorInfo & roErrorInfo)
{
	oArchive << (long) roErrorInfo.m_erco << roErrorInfo.m_idHelp << roErrorInfo.m_oErrorDescriptionString;
	return oArchive;
}

inline CArchive & AFXAPI operator >> (CArchive & oArchive, CNavoErrorInfo & roErrorInfo)
{
	oArchive >> (long&) roErrorInfo.m_erco >> roErrorInfo.m_idHelp >> roErrorInfo.m_oErrorDescriptionString;
	return oArchive;
}

class CNavoException
{
public:
	CNavoException()
	{
	}
	CNavoException(const CNavoErrorInfo & roNavoErrorInfo)
	{
		m_oNEIArray.Add(roNavoErrorInfo);
	}
	CNavoException(const CNavoException & roNavoException)
	{
		(*this) = roNavoException;
	}

	virtual void operator +=(const CNavoException & roNavoException)
	{
		CSingleLock oSingleLock(&m_oCriticalSection,TRUE);
		m_oNEIArray.Append(roNavoException.m_oNEIArray);
		OnNewError();
	}
	virtual void operator +=(const CNavoErrorInfo & roNavoErrorInfo)
	{
		CSingleLock oSingleLock(&m_oCriticalSection,TRUE);
		m_oNEIArray.Add(roNavoErrorInfo);
		OnNewError();
	}

	CString BuildCompleteErrorString() const;
protected:
	CNavoException(const CNavoException & roNavoException,const CNavoErrorInfo & roNavoErrorInfo)
	{
		(*this) = roNavoException;
		m_oNEIArray.Add(roNavoErrorInfo);
	}
	virtual void operator = (const CNavoException & roNavoException)
	{
		CSingleLock oSingleLock(&m_oCriticalSection,TRUE);
		m_oNEIArray.RemoveAll();
		(*this) += roNavoException;
	}
	virtual void OnNewError() {}
	CArray<CNavoErrorInfo,const CNavoErrorInfo &> m_oNEIArray;
	CCriticalSection	m_oCriticalSection;

	friend class CNavoExceptionAccessor;
};

class CNavoExceptionAccessor
{
public:
	CNavoExceptionAccessor(CNavoException & roNavoException) :
	  m_roNavoException(roNavoException),
	  m_oSingleLock(&roNavoException.m_oCriticalSection,TRUE)
	{
	}
	~CNavoExceptionAccessor()
	{
	}
	CArray<CNavoErrorInfo,const CNavoErrorInfo &> & ErrorInfoArray()
	{
		return m_roNavoException.m_oNEIArray;
	}
private:
	CNavoException & m_roNavoException;
	CSingleLock		 m_oSingleLock;
};

inline bool SearchExceptionForErrorCode(CNavoException & roNavoException,errorcode eErco)
{
	CNavoExceptionAccessor oNEA(roNavoException);
	for(long iter = 0; iter <= oNEA.ErrorInfoArray().GetUpperBound(); iter++)
	{
		if(oNEA.ErrorInfoArray()[iter].GetErroCode() == eErco)
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------
// rzucanie wyj¹tków CNavoException
//-------------------------------------
__declspec(noreturn) void ThrowNavoExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	errorcode erco,
	long idHelp,
	...);

__declspec(noreturn) void ContinueThrowNavoExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	CNavoException & roException,
	errorcode erco,
	long idHelp,
	...);

__declspec(noreturn) void ThrowNavoAutomationExceptionInternal(
	LPCTSTR pcFileName,
	long lLine,
	errorcode erco,
	long lHelpPageId,
	...);

__declspec(noreturn) void ThrowNavoAutomationExceptionFromInfoInternal(
	LPCTSTR pcFileName,
	long lLine,
	const CNavoException & roNavoException);

__declspec(noreturn) void ThrowFromErrorInfo(HRESULT hResult, IErrorInfo * iErrorInfo);

#define ThrowNavoException(ErrorCode, lHelpId)							ThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId))
#define ThrowNavoException1(ErrorCode, lHelpId, a1)					ThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1))
#define ThrowNavoException2(ErrorCode, lHelpId, a1, a2)				ThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2))
#define ThrowNavoException3(ErrorCode, lHelpId, a1, a2, a3)			ThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2), (a3))
#define ThrowNavoException4(ErrorCode, lHelpId, a1, a2, a3, a4)	ThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2), (a3), (a4))

#define ContinueThrowNavoException(Exception, ErrorCode, lHelpId)						ContinueThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (Exception), (ErrorCode), (lHelpId))
#define ContinueThrowNavoException1(Exception, ErrorCode, lHelpId, a1)					ContinueThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (Exception), (ErrorCode), (lHelpId), (a1))
#define ContinueThrowNavoException2(Exception, ErrorCode, lHelpId, a1, a2)			ContinueThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (Exception), (ErrorCode), (lHelpId), (a1), (a2))
#define ContinueThrowNavoException3(Exception, ErrorCode, lHelpId, a1, a2, a3)		ContinueThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (Exception), (ErrorCode), (lHelpId), (a1), (a2), (a3))
#define ContinueThrowNavoException4(Exception, ErrorCode, lHelpId, a1, a2, a3, a4)	ContinueThrowNavoExceptionInternal(_T(__FILE__), __LINE__, (Exception), (ErrorCode), (lHelpId), (a1), (a2), (a3), (a4))

#define ThrowNavoAutoException(ErrorCode, lHelpId)							ThrowNavoAutomationExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId))
#define ThrowNavoAutoException1(ErrorCode, lHelpId, a1)					ThrowNavoAutomationExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1))
#define ThrowNavoAutoException2(ErrorCode, lHelpId, a1, a2)				ThrowNavoAutomationExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2))
#define ThrowNavoAutoException3(ErrorCode, lHelpId, a1, a2, a3)			ThrowNavoAutomationExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2), (a3))
#define ThrowNavoAutoException4(ErrorCode, lHelpId, a1, a2, a3, a4)	ThrowNavoAutomationExceptionInternal(_T(__FILE__), __LINE__, (ErrorCode), (lHelpId), (a1), (a2), (a3), (a4))

#define ContinueThrowNavoAutoException(ErrorInfo) ThrowNavoAutomationExceptionFromInfoInternal(_T(__FILE__), __LINE__,(ErrorInfo))

bool ErrorInfoFromInterface(IUnknown * pUnknown, CNavoErrorInfo & roNavoErrorInfo);

CString GetLastError_To_String(DWORD dwErrorCode);
CString SCODE_To_String(SCODE sc);

void NavoFormatErrorMsg(CString & roMsgString,errorcode lErrorCode,...);

void _fill_excepinfo(EXCEPINFO * pExcepInfo,const CNavoException & roNavoException);
//-------------------------------------------------
//	try przekszta³caj¹cy wszystko na CNavoException
//-------------------------------------------------

#define ALL_TRY\
	try\
	{\
		try

#define ALL_CATCH(__e__)\
		catch(_com_error e)\
		{\
			ThrowFromErrorInfo(e.Error(), e.ErrorInfo());\
		}\
		catch(CException * e)\
		{\
			ASSERT(e);\
			TCHAR cErrorMsg[ 512 ]; \
			e->GetErrorMessage(cErrorMsg,sizeof(cErrorMsg)); \
			e->Delete();\
			ThrowNavoException1(ERCO_MFC_EXCEPTION, IDPAGE_NOTAVAILABLE,cErrorMsg);\
		}\
		catch(CNavoException &)\
		{\
			throw;\
		}\
		catch(...)\
		{\
			ThrowNavoException1(ERCO_GENERAL, IDPAGE_NOTAVAILABLE, NULL);\
		}\
	}\
	catch(__e__)

#define TOP_ALL_CATCH(__a__, _to_return_) \
	ALL_CATCH(const CNavoException & roNavoException)\
	{\
		(__a__) += (roNavoException);\
		return (_to_return_);\
	};

#define TOP_ALL_CATCH_(__a__) \
	ALL_CATCH(const CNavoException & roNavoException)\
	{\
		(__a__) += (roNavoException);\
	};

#define TOP_ALL_CATCH_AUTOMATION(__a__, _pExceptInfo_) \
	ALL_CATCH(const CNavoException & roNavoException)\
	{\
		_fill_excepinfo((_pExceptInfo_),roNavoException);	\
		(__a__) += (roNavoException);\
		return (DISP_E_EXCEPTION);\
	};

#else
	#error this _T(__FILE__) was included
#endif
