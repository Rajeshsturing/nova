/*
	NAVO Enterprise 2003
	2003-05-16

	navo ASPator

	t³umaczy strumieñ w formacie "ASP" na skrypt VB, z mo¿liwoœci¹ wykonania
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"		//script user
#include "navoaspator.h"
#include "StreamAutoObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR * _g_pcResponseObjectName = _T("so");
const TCHAR * _g_pcResponseWriteName = _T("so.write \"");
const long _g_nResponseWriteLen = 10;	//len(_g_pcResponseWriteName)
const TCHAR * _g_pcResponseCloseName = _T("\"\x0d\x0a");
const long _g_nResponseCloseLen = 3;	//len("\"\x0d\x0a")
//---------------------------------------------------------------------------------------

caspator_comobject::caspator_comobject() :
	CSimpleScriptUser(0),
	m_bPreprocess(false)
{
	AfxOleLockApp();
	EnableAutomation();
}


caspator_comobject::~caspator_comobject()
{
	AfxOleUnlockApp();
}


//{{AFX_MSG_MAP(caspator_comobject)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(caspator_comobject, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(caspator_comobject)
	DISP_FUNCTION(caspator_comobject, "init", InitAUTO, VT_EMPTY, VTS_VARIANT VTS_VARIANT VTS_DISPATCH VTS_BOOL)
	DISP_FUNCTION(caspator_comobject, "addsymbol", AddNameAUTO, VT_EMPTY, VTS_BSTR VTS_DISPATCH)
	DISP_FUNCTION(caspator_comobject, "include", AddIncludeAUTO, VT_EMPTY, VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(caspator_comobject, "go", GoAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(caspator_comobject, "godirect", GoDirectAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


IMPLEMENT_DYNCREATE(caspator_comobject, CCmdTargetInterface)
// {188cb190-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(caspator_comobject, "navocomutil.aspator",0x188cb190,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(caspator_comobject, CCmdTargetWithErrorInfo)
END_INTERFACE_MAP()

void caspator_comobject::InitAUTO(const VARIANT FAR& varInputStreamOrURL,
		const VARIANT FAR& varOutputStreamOrURL,LPDISPATCH pEnvironent,BOOL bPreprocess)
{
	ALL_TRY
	{
		CSmartOleVariant oInputSOV(varInputStreamOrURL);
		m_poInputStreamSP = OpenFileStream_Read_On_SOV(oInputSOV);

		CSmartOleVariant oOutputSOV(varOutputStreamOrURL);
		m_poOutputStreamSP = CreateFileStream_Write_On_SOV(oOutputSOV,m_poFileRemoverSP);
		m_poPropertyProvSP = NewSCP(pEnvironent,true);
		if(m_poPropertyProvSP.PointsNull())
		{
			SCP<CHyperLinkInfo> poHLISP = NewSCP(new CHyperLinkInfo());
			m_poPropertyProvSP = poHLISP->GetDispatchSP();
		}
		m_bPreprocess = (bPreprocess != FALSE);

	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void caspator_comobject::AddNameAUTO(LPCTSTR pcName,LPDISPATCH pObject)
{
	ALL_TRY
	{
		SCP<IDispatch> poDispatchSP = NewSCP(pObject,true);
		m_oSymbolDispatchArray.Add(poDispatchSP);
		AddNamedItem(NewSCP(new CNamedItemInfo(pcName,poDispatchSP.Get(),NULL)));
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void caspator_comobject::AddIncludeAUTO(long idInclude,const VARIANT FAR& varIncludeStreamOrURL)
{
	ALL_TRY
	{
		CSmartOleVariant oIncludeSOV(varIncludeStreamOrURL);
		m_oIncludeMap[ idInclude ] = OpenFileStream_Read_On_SOV(oIncludeSOV);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void caspator_comobject::GoAUTO()
{
	ALL_TRY
	{
		//addname "response"
		SCP<CStreamAutoObject> poStreamAUTOSP = NewSCP(new CStreamAutoObject());
		poStreamAUTOSP->Attach(m_poOutputStreamSP);
		AddNameAUTO(_g_pcResponseObjectName,poStreamAUTOSP->GetIDispatch(FALSE));

		CArray<TCHAR,TCHAR &> oResultString;
		CArrayWriter<TCHAR> oResultArrayWriter(oResultString);
		//write start
		CString oVBString = "Option Explicit\n";
		oResultArrayWriter.Write(oVBString,oVBString.GetLength());

		_translate_to_script_code(_get_final_input_stream(),oResultArrayWriter);

		_access_script_storage() = CString((LPCTSTR)oResultString.GetData(),oResultArrayWriter.CharactersWritten());
		
		TRACE("%s",(LPCTSTR)_access_script_storage());

		SafeInvoke(CBStr("nonexiting"),NULL,0,NULL);

		if(m_poFileRemoverSP.PointsObject())
		{
			m_poFileRemoverSP->DontRemove();
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//just copies input (preprocessed) to desired output
void caspator_comobject::GoDirectAUTO()
{
	ALL_TRY
	{
		ULARGE_INTEGER ulInfinity;
		ulInfinity.QuadPart = MAXLONG;
		HRESULT hr = IStream_CopyTo(_get_final_input_stream(),m_poOutputStreamSP,ulInfinity);
		ASSERT(hr==S_OK);

		if(m_poFileRemoverSP.PointsObject())
		{
			m_poFileRemoverSP->DontRemove();
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//---------------------------------------------------------------------------------------
// dummy stream provider - provides single file
//---------------------------------------------------------------------------------------

class cdummy_streamprovider : public IStreamProvider
{
public:
	cdummy_streamprovider(caspator_comobject * poAspator) :
		m_lRefCount(1),		
		m_poAspator(poAspator)
	{
	}
	~cdummy_streamprovider()
	{
	}
	virtual unsigned long STDMETHODCALLTYPE AddRef()
	{ 
		ASSERT(m_lRefCount >= 0);
		return ::InterlockedIncrement(&m_lRefCount);
	}
	virtual unsigned long STDMETHODCALLTYPE Release()
	{
		::InterlockedDecrement(&m_lRefCount);
		ASSERT(m_lRefCount >= 0);
		
		if(m_lRefCount == 0)
		{
			delete this;
			return 0;
		}
		else
		{
			return m_lRefCount;
		}
	}
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject)
	{
		*ppvObject = NULL;
		if(riid == IID_IStreamProvider || riid == IID_IUnknown)
		{
			AddRef();
			*ppvObject = reinterpret_cast<void*>(this);
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	virtual HRESULT STDMETHODCALLTYPE Get(long IdFile,IStream **ppStream,navostreaminfo * poNSI)
	{

		_init_navostreaminfo(*poNSI);
		poNSI->m_bCompressed = '0';
		*ppStream = NULL;		//a jak bêdzie wyj¹tek...
		SCP<IStream> poStreamSP;
		if (IdFile == 9999999)
		{
			poStreamSP = m_poAspator->m_poInputStreamSP;
		}
		else
		{
			VERIFY(m_poAspator->m_oIncludeMap.Lookup(IdFile,poStreamSP));
		}
		*ppStream = poStreamSP.Detach();
		return S_OK;
	}
private:
	long m_lRefCount;
	caspator_comobject * m_poAspator;
};

//---------------------------------------------------------------------------------------
// implementation
//---------------------------------------------------------------------------------------

SCP<IStream> caspator_comobject::_get_final_input_stream()
{
	if(m_bPreprocess)
	{
		ASSERT(m_poPropertyProvSP.PointsObject());
		SCP<IStreamProvider> poStreamProviderSP = NewSCP(new cdummy_streamprovider(this));
		SCP<IPreprocessor> poPreprocessorSP;
		poPreprocessorSP.CreateInstance(CLSID_NAVO2001Preprocessor,CLSCTX_INPROC);
		VERIFY(S_OK == poPreprocessorSP->Init(m_poPropertyProvSP.Get(),poStreamProviderSP,NULL));
		HRESULT hr = poPreprocessorSP->PreprocessFile(9999999,BYTE(false));
		if(hr != S_OK)
		{
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}
		SCP<IStream> pOutputStreamSP;
		pOutputStreamSP.QueryInterface(poPreprocessorSP);
		return pOutputStreamSP;
	}
	else
	{
		return m_poInputStreamSP;
	}
}

inline void open_txtline(CArrayWriter<TCHAR> & roResultString)
{
	roResultString.Write(_g_pcResponseWriteName,_g_nResponseWriteLen);
}

inline void close_txtline(CArrayWriter<TCHAR> & roResultString)
{
	roResultString.Write(_g_pcResponseCloseName,_g_nResponseCloseLen);
}

void caspator_comobject::_translate_to_script_code(SCP<IStream> poInputStreamSP,CArrayWriter<TCHAR> & roResultString)
{
	bool bModeVB = false;
	bool bTxtLineOpen = false;

	CStreamBuffer oStreamBufer(poInputStreamSP);
	
	while(true)
	{
		char cChar = oStreamBufer._get_char();
		if(cChar == '\0')
		{
			break;
		}

		if(bModeVB)
		{
			if(cChar == '%')	//wykrywanie sygnatury koñca %>
			{
				char cSecondChar = oStreamBufer._get_char();
				if(cSecondChar == '>')
				{
					bModeVB = false;
					roResultString << '\x0d' << '\x0a';
					continue;
				}
				roResultString << '%' << cSecondChar;
			}
			else
			{
				roResultString << cChar;
			}
		}
		else
		{
			if(cChar == '<')	//wykrywanie sygnatury pocz¹tku <% 
			{
				char cSecondChar = oStreamBufer._get_char();
				if(cSecondChar == '%')
				{
					if(bTxtLineOpen)
					{
						close_txtline(roResultString);
						bTxtLineOpen = false;
					}

					bModeVB = true;
					continue;
				}
				else
				{
					oStreamBufer._unget_char();
				}
			}

			if(cChar == '\x0d')
			{
				if(bTxtLineOpen)
				{
					close_txtline(roResultString);
					roResultString.Write("so.write vbCrLf\n",16);
					bTxtLineOpen = false;
				}
			}
			else
			{
				if(cChar == '\x0a')
				{
					//noop
				}
				else
				{
					if(!bTxtLineOpen)
					{
						open_txtline(roResultString);
						bTxtLineOpen = true;
					}
					if(cChar == '\"')
					{
						roResultString << '\"' << '\"';
					}
					else
					{
						roResultString << cChar;
					}
				}
			}
		}
	}

	if(bTxtLineOpen)
	{
		ASSERT(!bModeVB);
		close_txtline(roResultString);
	}
}

