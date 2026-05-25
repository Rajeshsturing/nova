/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Preprocessor
*/

#ifndef _NAVOPREPROCESSOR_H_
#define _NAVOPREPROCESSOR_H_

class CPrecompiledData;
interface IStreamProvider;

class CPreprocesor : public CInterface__, public CSymbolicNameResolver
{
public:
	CPreprocesor(long IdFile, SCP<IStreamProvider> & rpoStreamProviderSP,
		SCP<CPropertyProvider__> & rpoHyperLinkSP,
		SCP<IPreprocessedDataCache> & rpoPDMSP,bool bParseMode);
	~CPreprocesor();
	
	//przetwórz kawa³ek, false - koniec
	bool DoChunk(CArrayWriter<TCHAR> & roOutputWriter);
	long GetVarDependecyCount() const
	{
		return m_oDependencyMap.GetCount();
	}
	long GetIncludeDependecyCount() const
	{
		return m_oIncludeMap.GetCount();
	}
	void GetVarDependencies(long * pDependencies);
	void GetIncludeDependencies(long * pDependencies);

	bool GetSymbolValue(LPCTSTR lpSymbol,CSmartOleVariant & roValueSOV);
	bool is_symbol_defined(LPCTSTR lpSymbol);
private:
	void FormatMacro(const TCHAR* &pcNameString, CString &oValueString);
	void ExtractParams( const TCHAR* &pcSource, TCHAR* &pcWord, const TCHAR* pcParamStartArr[], const TCHAR* pcParamEndArr[]);

	//rozpoznaje s³owa kluczowe
	long DetectKeyword(const TCHAR *  pcText,TCHAR * & pcCursor);
	
	//rozpoznaje czy linia ma #dyrektywy czy nie i odpowiednio steruje przep³ywem
	bool ParseLine(LPCTSTR pcInputLine,CArrayWriter<TCHAR> & roOutputWriter);
	
	//t³umaczy liniê ! uwaga mo¿e zmieniæ pcInputLine !!!
	bool TranslateLine(LPCTSTR pcInputLine,CArrayWriter<TCHAR> & roOutputWriter);
	bool TranslateMacro( LPCTSTR pcInputLine, CArrayWriter<TCHAR> &roOutputWriter, const TCHAR* pcParamStartArr[], const TCHAR* pcParamEndArr[]);
	
	void ReadIdentifier( TCHAR* &pcName, TCHAR* &pcCursor);
	void AddDefinition(LPCTSTR pcName, LPCTSTR pcValue);
	void AddMacro( LPCTSTR pcName, LPCTSTR pcValue);
	void RemoveDefinition(LPCTSTR pcName);

	bool GetDefinition(LPCTSTR pcName,CString & roValueString)
	{
		return m_oDefinedItemsMap.Lookup(pcName,roValueString) != FALSE;
	}

	enum GetVarVal
	{
		gvv_notvariable,
		gvv_varnotdef,
		gvv_vardef
	};

	GetVarVal GetVariableValue(LPCTSTR pcName,CSmartOleVariant & roSOV);

	void AddVarDependency(long nVarNr)
	{
		m_oDependencyMap[ nVarNr ] = nVarNr;
	}
	void AddIncludeDependency(long IdFile)
	{
		m_oIncludeMap[ IdFile ] = IdFile;
	}
	CString GetErrorContextText();

	//wczytuje kolejne linie (znak kontynuacji \) dla #define i #macro 
	void _read_continuation_lines(CString & roValueString);

	//dyrektywy
	void _Kwd_Define(TCHAR * pcCursor);
	bool _Kwd_Macro( TCHAR * pcCursor);
	bool _Kwd_Ifdef(bool bDef,TCHAR * pcCursor);
	bool _Kwd_If(TCHAR * pcCursor);
	void _Kwd_Else(TCHAR * pcCursor);
	void _Kwd_Endif(TCHAR * pcCursor);
	void _Kwd_Undef(TCHAR * pcCursor);
	void _Kwd_Include(TCHAR * pcCursor);
	void _Kwd_Pure();

	class CPrepFileData
	{
	public:
		CPrepFileData();
		CPrepFileData(const CPrepFileData & roPrepFileData)
		{
			(*this) = (roPrepFileData);
		}
		CPrepFileData(long IdFile,SCP<IStream> & rpoIStreamSP);
		virtual void operator = (const CPrepFileData & roPrepFileData);
		
		long			m_IdFile;
		long			m_nLineNr;
		CBufferToFile	m_oBufferToFile;
		SCP<CPrecompiledData>	m_poPDSP;
	};
	
	CMapStringToString				m_oDefinedItemsMap;
	CEnhancedStack<CPrepFileData>	m_oPrepFileDataStack;
	CEnhancedStack<bool>			m_oConditionStack;
	long							m_nPassedConditionsCount;
	SCP<IStreamProvider>			m_poStreamProviderSP;
	SCP<CPropertyProvider__>		m_poEnvironmentHLISP;
	SCP<IPreprocessedDataCache>		m_poPreprocessedDataCacheSP;
	CMap<long, long,long,long>		m_oDependencyMap;
	CMap<long, long,long,long>		m_oIncludeMap;
	long							m_lDefinedWordsMinLength;
	bool							m_bStrict;				//strict keyword recognision
	bool							m_bParseMode;
	bool							m_bStillPure;
	long							m_macroCount;
	int								m_recurLevel;
#ifdef _DEBUG
	long m_lRejectedWords, m_lComparedWords, m_lMatchedWords, m_lKeywordsTest, m_lTotalRead, m_lTotalWritten;
#endif
};

#else
	#error __FILE__ already included
#endif
