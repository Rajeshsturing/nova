/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		Preprocessor object
*/

#ifndef _PREPOBJ_H_
#define _PREPOBJ_H_

class CPreprocesor;

const unsigned long PREP_OUTPUT_BUFFER_SIZE = 65536;

class CPreprocessorObj : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CPreprocessorObj)

	CPreprocessorObj();           // protected constructor used by dynamic creation
	virtual ~CPreprocessorObj();

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreprocessorObj)
virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

	BEGIN_INTERFACE_PART(Preprocessor,IPreprocessor)
		STDMETHOD(Init)(IDispatch * pEnvironmentDisp,IStreamProvider * pStreamProvider,IPreprocessedDataCache * pDataCache);
		STDMETHOD(PreprocessFile)(long IdFile,BYTE bParseMode);
		STDMETHOD(GetVarDependencies)(long * pnVarCntr,long ** ppVarNr);
		STDMETHOD(GetIncludeDependencies)(long * pnFileCntr,long ** ppIdFile);
		STDMETHOD(Close)();
	END_INTERFACE_PART(Preprocessor)
	
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
protected:
	//{{AFX_MSG(CPreprocessorObj)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CPreprocessorObj)
	//}}AFX_DISPATCH
	DECLARE_OLECREATE(CPreprocessorObj)
	DECLARE_INTERFACE_MAP()
private:
	SCP<CPreprocesor>		m_poPreprocessorSP;
	SCP<IStreamProvider>	m_poStreamProviderSP;
	SCP<CPropertyProvider__>		m_poEnvironmentSP;
	SCP<IPreprocessedDataCache> m_poPreprocessedDataCacheSP;
	TCHAR					m_oOutputBuffer[PREP_OUTPUT_BUFFER_SIZE];
	unsigned long			m_nReadPos;		//pozycja do odczytu
	unsigned long			m_nWritePos;	//pozycja do zapisu
};

class CPreprocessedDataCacheImpl;
class CPreprocessedDataCache : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CPreprocessedDataCache)

	CPreprocessedDataCache();           // protected constructor used by dynamic creation
	virtual ~CPreprocessedDataCache();
public:
	BEGIN_INTERFACE_PART(PreprocessedDataCache, IPreprocessedDataCache)
		STDMETHOD(GetData)(long IdFile,IStream ** ppDataStream);
		STDMETHOD(PutData)(long IdFile,IStream * pDataStream);
	END_INTERFACE_PART(PreprocessedDataCache)

	DECLARE_OLECREATE(CPreprocessedDataCache)
	DECLARE_INTERFACE_MAP()

private:
	SCP<CPreprocessedDataCacheImpl>	m_poImplementationSP;
};

#else
	#error __FILE__ already included
#endif
