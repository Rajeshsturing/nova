/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
	CStreamAutoObject
		obiekt implementuje IStream manipulowalny przed automation
*/

#if !defined(AFX_STREAMAUTOOBJECT_H__4F4EE3DA_4B16_4A1A_BD29_CB713AEF93B3__INCLUDED_)
#define AFX_STREAMAUTOOBJECT_H__4F4EE3DA_4B16_4A1A_BD29_CB713AEF93B3__INCLUDED_

class CStreamAutoObject : public CCmdTargetWithErrorInfo
{
public:
	CStreamAutoObject();
	CStreamAutoObject(CStreamAutoObject & roStreamAutoObject);
	//{{AFX_VIRTUAL(CStreamAutoObject)
	//}}AFX_VIRTUAL

	void Attach(SCP<IStream> & rpoStreamSP)
	{
		m_poXMLStreamSP = rpoStreamSP;
		m_eLastOperation = LAOP_UNKNOWN;
		m_bFirstWrite = true;
		/*
			Attention! 
			Consider OnStreamAttachDetach notification call in code calling this method.
		*/
	}
	static SCP<CStreamAutoObject> FromIDispatch(LPDISPATCH lpDispatch);
	virtual void OnStreamAttachDetach() {}

protected:
	SCP<IStream> GetStream()
	{
		return m_poXMLStreamSP;
	}
	virtual ~CStreamAutoObject();

	virtual void OnFirstWrite() {}

	//{{AFX_MSG(CStreamAutoObject)
	//}}AFX_MSG
	DECLARE_DYNCREATE(CStreamAutoObject)
	DECLARE_OLECREATE(CStreamAutoObject)

	DECLARE_MESSAGE_MAP()
public:
	//{{AFX_DISPATCH(CStreamAutoObject)
	afx_msg void SaveAUTO(LPCTSTR URL);
	afx_msg void SaveCodedAUTO(LPCTSTR URL);
	afx_msg void AttachAUTO(const VARIANT FAR& varStreamOrURL);
	afx_msg void AttachCodedAUTO(const VARIANT FAR& varStreamOrURL);
	afx_msg void WriteAUTO(LPCTSTR strData);
	afx_msg BSTR ReadAUTO(long nBytes);
	afx_msg VARIANT GetStreamAUTO();
	afx_msg BOOL IsEmptyAUTO();
	afx_msg void EmptyAUTO();
	afx_msg BSTR GetAsStringAUTO();
	afx_msg long GetCurrentLengthAUTO();
	afx_msg void CopyToAUTO(const VARIANT FAR& varStreamOrURL);
	afx_msg void RewindAUTO();
	afx_msg void SeekToEndAUTO();
	afx_msg void AttachTempAUTO();
	//}}AFX_DISPATCH
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


#undef NAVO_CLASS_DECL
#ifdef THIS_IS_NAVOCOMUTIL
#define NAVO_CLASS_DECL _declspec(dllexport)
#else
#define NAVO_CLASS_DECL _declspec(dllimport)
#endif
#undef  AFX_DATA
#define AFX_DATA NAVO_CLASS_DECL

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#undef  AFX_DATA
#define AFX_DATA

protected:
	void _save_to_url(LPCTSTR URL,bool bCoded);

	void _rewind_to_begin();
	void _rewind_to_end();

	enum eLastOperation
	{
		LAOP_UNKNOWN,			//stan nieznany
		LAOP_WRITE,				//ostatnio pisano
		LAOP_READ				//ostatnio czytano
	} m_eLastOperation;

	SCP<IStream> m_poXMLStreamSP;
	bool m_bFirstWrite;
	
};

const long COMPRESSION_WINDOW_SIZE = 4096;
const long TOTAL_COMPRESSION_BUFFER_SIZE = COMPRESSION_WINDOW_SIZE + COMPRESSION_WINDOW_SIZE / 100 + 20  + sizeof(unsigned long);

class CStreamFilterObject : public CCmdTargetWithErrorInfo
{
public:
	CStreamFilterObject() :
		m_nFilterType(SFT_INVALID)
	{
		AfxOleLockApp();
		__Init();
	}
	~CStreamFilterObject()
	{
		AfxOleUnlockApp();

#ifdef _DEBUG

/*
		TRACE("-------- StreamFilterObject --------\n");
		TRACE("total uncompress %d\n",_debug_m_nTotalUncompressedBytesRead);
		TRACE("total compress %d\n",_debug_m_nTotalCompressedBytesRead);
		if(_debug_m_nTotalUncompressedBytesRead != 0)
		{
			TRACE("compress ratio %d %%\n",
				(100*_debug_m_nTotalCompressedBytesRead) /
				_debug_m_nTotalUncompressedBytesRead);
		}
		TRACE("------------------------------------\n");
*/

#endif

	}
private:
	DECLARE_DYNCREATE(CStreamFilterObject)
	DECLARE_OLECREATE(CStreamFilterObject)

	BEGIN_INTERFACE_PART(StreamFilter,IStreamFilter)
		STDMETHOD(AttachInput)(IStream * pInputStream);
		STDMETHOD(SetParam)(long nType);
	END_INTERFACE_PART(StreamFilter)

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

	DECLARE_INTERFACE_MAP();
private:
	void __Init();
	HRESULT __Read(void *pData, unsigned long lLength, unsigned long *plBytesRead);

	HRESULT __read_strip_starting_whitespace(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT __read_compress(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT __read_uncompress(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT __read_base64encode(void *pData, unsigned long lLength, unsigned long *plBytesRead);
	HRESULT __read_base64decode(void *pData, unsigned long lLength, unsigned long *plBytesRead);


	SCP<IStream>	m_poInputStreamSP;
	long			m_nFilterType;
	
	//state for SFT_STRIP_STARTING_WHITESPACE
	bool			m_bInsideHeader;		

	//state for SFT_COMPRESS,SFT_UNCOMPRESS,SFT_BASE64ENCODE,SFT_BASE64DECODE
					//rozmiar bufora wymagany przez algorytm kompresji / dekompresji
	BYTE			m_oBuffer[ TOTAL_COMPRESSION_BUFFER_SIZE ];
	unsigned long	m_nDataLen;		//iloœæ wa¿nych danych w buforze
	unsigned long	m_nFirstUnread;	//pierwszy nieprzeczytany znak w buforze (na zewn¹trz)

	bool			m_bWasRead;
#ifdef _DEBUG
	long			_debug_m_nTotalUncompressedBytesRead;
	long			_debug_m_nTotalCompressedBytesRead;
#endif
};

#else
	#error File already included
#endif
