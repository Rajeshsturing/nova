/*
	NAVO Sp. z o.o. ( 2001)
	
	NAVO Enterprise

	Preprocessor
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\symbnameres.h"
#include "..\include\expresseval.h"
#include "..\include\filerange.h"

// leszek void _cdecl _init_navostreaminfo( navostreaminfo&);
#include "..\include\interfaceutil.h"
#include "preprocessor.h"
#include "precompileddata.h"

//#define PREP_CORRECTION_1

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_LINE_LENGTH		2048
#define MAX_RECUR_DEPTH		20
#define MAX_PARAM_COUNT     64

#define MACRO_MARKER		'\xff'
#define MACRO_PARAM_MARKER_BYTE0	'\1'
#define MACRO_PARAM_MARKER_BYTE3	'\0'

static void _build_file_included_define(long idFile,CString & roString)
{
	roString.Format(_T("INCLUDED_%d"),idFile);
}

CPreprocesor::CPrepFileData::CPrepFileData( long IdFile, SCP<IStream> &rpoIStreamSP) :
	m_IdFile( IdFile), 
	m_oBufferToFile( rpoIStreamSP), 
	m_nLineNr( 0)
{
}
	
CPreprocesor::CPrepFileData::CPrepFileData() :
	m_IdFile( 0), 
	m_oBufferToFile(), 
	m_nLineNr( 0)
{
}

void CPreprocesor::CPrepFileData::operator = ( const CPrepFileData &roPrepFileData)
{
	m_IdFile		= roPrepFileData.m_IdFile;
	m_oBufferToFile = roPrepFileData.m_oBufferToFile;
	m_nLineNr		= roPrepFileData.m_nLineNr;
	m_poPDSP		= const_cast<CPrepFileData & >( roPrepFileData).m_poPDSP;
}

CPreprocesor::CPreprocesor(long IdFile,SCP<IStreamProvider> & rpoStreamProviderSP, 
	SCP<CPropertyProvider__> & rpoHyperLinkSP,SCP<IPreprocessedDataCache> & rpoPDMSP, bool bParseMode):
	m_poStreamProviderSP( rpoStreamProviderSP), 
	m_poEnvironmentHLISP( rpoHyperLinkSP), 
	m_lDefinedWordsMinLength( 9999), 
	m_nPassedConditionsCount( 0), 
	m_bStrict( false), 
	m_bParseMode( bParseMode), 
	m_poPreprocessedDataCacheSP( rpoPDMSP), 
	m_bStillPure( true), 
	m_recurLevel( 0),
	m_macroCount( 0)
{
	ASSERT( m_poStreamProviderSP.PointsObject());

	SCP<IStream> poInitialStreamSP;
	navostreaminfo oNSI;
	_init_navostreaminfo( oNSI);
	HRESULT hr = m_poStreamProviderSP->Get( IdFile, &poInitialStreamSP.GetRawPointer(), &oNSI);
	if( hr != S_OK)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface( m_poStreamProviderSP, oNavoException);
		ContinueThrowNavoException2( oNavoException, ERCO_PREP_UNABLE_TO_OPEN_INPUTFILE, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String( hr));
	}
	ASSERT( oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
	if( oNSI.m_bCompressed == '1')
	{
		poInitialStreamSP = UncompressStream( poInitialStreamSP);
	}
	m_oDefinedItemsMap.InitHashTable( 503);
	m_oDependencyMap.InitHashTable( 31);
	m_oPrepFileDataStack.Push( CPrepFileData( IdFile, poInitialStreamSP));
	
	//#define INCLUDED_file
	{
		CString oIncludedString;
		_build_file_included_define(IdFile,oIncludedString);
		TRACE("%s\n",oIncludedString);
		AddDefinition(oIncludedString, _T( ""));
	}

#ifdef _DEBUG
	//TRACE2( "preprocessing %d in %s mode\n", IdFile, bParseMode ? "parse-only" : "real");

	m_lRejectedWords = 0;
	m_lComparedWords = 0;
	m_lMatchedWords  = 0;
	m_lKeywordsTest  = 0;

	m_lTotalRead	 = 0;
	m_lTotalWritten	 = 0;

	AddDefinition( _T( "_DEBUG"), _T( ""));
#else
	AddDefinition( _T( "NDEBUG"), _T( ""));
#endif
	AddDefinition( _T( "THIS_FILE"), Long2String( IdFile));
	AddDefinition( _T( "__FILE__"), Long2String( IdFile)); // ANSI C macro

}


CPreprocesor::~CPreprocesor()
{
#ifdef _DEBUG
		CString oStr;
		oStr.Format( 
			_T( "Status parsowania:\n")
			_T( "Najkrotszy define: %d\n")
			_T( "Liczba odrzuconych wstepnie: %d\n")
			_T( "Liczba porownanych: %d\n")
			_T( "Liczba pasujacych: %d\n")
			_T( "Liczba keywordtestów %d\n")
			_T( "Liczba zdefiniowanych elem %d\n")
			_T( "Odczyt %d\n")
			_T( "Zapis %d\n") 
			_T( "Bilans odczyt - zapis: %d\n"), 
			m_lDefinedWordsMinLength, m_lRejectedWords, 
			m_lComparedWords, m_lMatchedWords, 
			m_lKeywordsTest, 
			m_oDefinedItemsMap.GetCount(),
			m_lTotalRead,
			m_lTotalWritten,
			m_lTotalRead - m_lTotalWritten);
			TRACE( oStr);
#endif
}

//--------- zwraca opis aktualnego kontekstu parsowania
//---------
//przydatne podczas wyœwietlania b³êdów

CString CPreprocesor::GetErrorContextText()
{
	//disallow recursive includes
	CString oString;
	POSITION pos = m_oPrepFileDataStack.GetTopPosition();

	while( pos)
	{
		CPrepFileData &roPrepFileData = m_oPrepFileDataStack.MoveDown( pos);
		CString oStringPart;
		oStringPart.Format( _T( "file=%d, line=%d\n"), roPrepFileData.m_IdFile, roPrepFileData.m_nLineNr);
		oString += oStringPart;
	}

	return oString;
}

bool CPreprocesor::DoChunk( CArrayWriter<TCHAR> &roOutputWriter)
{
	while( !m_oPrepFileDataStack.IsEmpty())
	{
		CArray <TCHAR, TCHAR &> oInputLineArray;
		oInputLineArray.SetSize( MAX_LINE_LENGTH);

#ifdef _DEBUG
		long bytesRead;
		if( (bytesRead = m_oPrepFileDataStack.GetTop().m_oBufferToFile.ReadLine( oInputLineArray, false)) != -1)
#else
		if( m_oPrepFileDataStack.GetTop().m_oBufferToFile.ReadLine( oInputLineArray, false) != -1)
#endif
		{
   			m_oPrepFileDataStack.GetTop().m_nLineNr++;
			ParseLine( oInputLineArray.GetData(), roOutputWriter);
#ifdef _DEBUG
			m_lTotalWritten += roOutputWriter.CharactersWritten();
			m_lTotalRead += bytesRead;
#endif
			return true;
		}
		else
		{
			CPrepFileData oPFD = m_oPrepFileDataStack.Pop();
			if(m_poPreprocessedDataCacheSP.PointsObject())
			{
				if( m_bStillPure)
				{
					if( oPFD.m_poPDSP.PointsObject())
					{
						SCP<IStream> poStreamSP = CreateStreamInMemory();
						oPFD.m_poPDSP->write(poStreamSP);
						VERIFY(S_OK == m_poPreprocessedDataCacheSP->PutData(oPFD.m_IdFile,poStreamSP));
						TRACE("PRECOMP: stored data for file %d\n",oPFD.m_IdFile);
					}
				}
			}
		}
	}

	return false;
}

#define KEYWORD_NOTHING		( -1)
#define KEYWORD_DEFINE		1
#define KEYWORD_IFDEF		2
#define KEYWORD_IF			4
#define KEYWORD_ELSE		8
#define KEYWORD_ENDIF		16
#define KEYWORD_UNDEF		32
#define KEYWORD_INCLUDE		64
#define KEYWORD_IFNDEF		128
#define KEYWORD_COMMENT		256
#define KEYWORD_PURE		512
#define KEYWORD_MACRO       1024

//-------------------------------------------------------
//		handcoded function !!
//
//
//		#define
//-------------------------------------------------------
//
long CPreprocesor::DetectKeyword( const TCHAR * pcText, TCHAR * & pcCursor)
{
#ifdef _DEBUG
	m_lKeywordsTest++;
#endif
	ASSERT( *pcText == '#');
	pcCursor = const_cast<TCHAR*>(pcText);

	switch( *++pcText)
	{
	case 'c':		//#comment
	{
		pcCursor += 8;

		if( m_bStrict)
		{
			return _tcsncmp( pcText, _T( "comment"), 7) ? KEYWORD_NOTHING: KEYWORD_COMMENT;
		}
		else
		{
			return KEYWORD_COMMENT;
		}
	}

	case 'd':		//#define
	{
		pcCursor += 7;

		if( m_bStrict)
		{
			return _tcsncmp( pcText, _T( "define"), 6) ? KEYWORD_NOTHING: KEYWORD_DEFINE;
		}
		else
		{
			return KEYWORD_DEFINE;
		}
	}

	case 'm' :      //#macro
	{	
		pcCursor += 6;

		if( m_bStrict)
		{
			return _tcsncmp( pcText, _T( "macro"), 5) ? KEYWORD_NOTHING: KEYWORD_MACRO;
		}
		else
		{
			return KEYWORD_MACRO;
		}
	}

	case 'e':		//#else, #endif

		switch( *++pcText)
		{
		case 'l':
		{
			pcCursor += 5;
			if( m_bStrict)
			{
				return _tcsncmp( pcText, _T( "lse"), 3) ? KEYWORD_NOTHING: KEYWORD_ELSE;
			}
			else
			{
				return KEYWORD_ELSE;
			}
		}

		case 'n':
		{
			pcCursor += 6;
			if( m_bStrict)
			{
				return _tcsncmp( pcText, _T( "ndif"), 4) ? KEYWORD_NOTHING: KEYWORD_ENDIF;
			}
			else
			{
				return KEYWORD_ENDIF;
			}
		}

		default:
			return KEYWORD_NOTHING;
		}

	case 'i':		//#ifdef, #if, #include, #ifndef

		switch( *++pcText)
		{
		case 'f':	//#ifdef, #if, #ifndef

			switch( *++pcText)
			{
			case 'd':
				pcCursor += 6;

				if( m_bStrict)
				{
					return _tcsncmp( pcText, _T( "def"), 3) ? KEYWORD_NOTHING: KEYWORD_IFDEF;
				}
				else
				{
					return KEYWORD_IFDEF;
				}

			case 'n':
				pcCursor += 7;

				if( m_bStrict)
				{
					return _tcsncmp( pcText, _T( "ndef"), 4) ? KEYWORD_NOTHING: KEYWORD_IFNDEF;
				}
				else
				{
					return KEYWORD_IFNDEF;
				}

			default:		//#if or nothing
				pcCursor += 3;
				return IsWhite( *pcText) ? KEYWORD_IF : KEYWORD_NOTHING;
			}

		case 'n':
		{
			pcCursor += 8;

			if( m_bStrict)
			{
				return _tcsncmp( pcText, _T( "nclude"), 6) ? KEYWORD_NOTHING: KEYWORD_INCLUDE;
			}
			else
			{
				return KEYWORD_INCLUDE;
			}
		}
		default:
			return KEYWORD_NOTHING;
		}

	case 'p':		//#pure
	{
		pcCursor += 5;

		if( m_bStrict)
		{
			return _tcsncmp( pcText, _T( "pure"), 4) ? KEYWORD_NOTHING: KEYWORD_PURE;
		}
		else
		{
			return KEYWORD_PURE;
		}
	}

	case 'u':		//#undef
	{
		pcCursor += 6;

		if( m_bStrict)
		{
			return _tcsncmp( pcText, _T( "undef"), 5) ? KEYWORD_NOTHING: KEYWORD_UNDEF;
		}
		else
		{
			return KEYWORD_UNDEF;
		}
	}

	default:
		return KEYWORD_NOTHING;
	}
}

//helpers
static inline void SkipWhiteCharacters( TCHAR* &pcText)
{
	while( IsWhite( *pcText))
	{
		pcText++;
	}
}


static inline bool SkipIdentifierCharacters(  TCHAR* &pcText)
{
	 TCHAR* pcFirst = pcText;

	while( IsAlphaNum( *pcText) )
	{
		pcText++;
	}

	return pcFirst != pcText;
}


static inline void SetNullAndMoveNext( TCHAR* &pcCursor)
{
	if( !*pcCursor)
	{
		return;
	}

	*pcCursor++ = '\0';
}


static inline bool EnsureEndOfLine( TCHAR* pcText)
{
	SkipWhiteCharacters( pcText);
	return ( *pcText == '\0');
}

void CPreprocesor::ReadIdentifier(  TCHAR* &pcName,  TCHAR* &pcCursor)
{
	SkipWhiteCharacters( pcCursor);

	if( !*pcCursor)
	{
		ThrowNavoException2( ERCO_PREP_UNEXPECTED_EOL, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}

	pcName = pcCursor;

	if( !SkipIdentifierCharacters( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_INVALID_IDENTIFIER, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}
}

void CPreprocesor::AddDefinition( LPCTSTR pcName, LPCTSTR pcValue)
{
	if( !m_bParseMode)
	{
		CString oString;
		if(GetDefinition(pcName,oString))
		{
			ThrowNavoException4( ERCO_PREP_ALREADY_DEFINED, IDPAGE_NOTAVAILABLE, pcName, oString, pcValue, GetErrorContextText());
		}
	}
	//resolve transitive definitions ( "#define A B" and "#define B C" results in "#define A C")
	//

	CArray<TCHAR, TCHAR&> oOutputBufferArray;
	oOutputBufferArray.SetSize( 1024);
	CArrayWriter<TCHAR> oOutputWriter( oOutputBufferArray);
	TranslateLine( pcValue, oOutputWriter);

	m_oDefinedItemsMap[ pcName ] = CString( oOutputBufferArray.GetData(), oOutputWriter.CharactersWritten());

	long nDefLen = _tcslen( pcName);
	m_lDefinedWordsMinLength = min( m_lDefinedWordsMinLength, nDefLen);
}

void CPreprocesor::AddMacro( LPCTSTR pcName, LPCTSTR pcValue)
{
	if( !m_bParseMode)
	{
		CString oString;
		if( m_oDefinedItemsMap.Lookup( pcName, oString))
		{
			ThrowNavoException4( ERCO_PREP_ALREADY_DEFINED, IDPAGE_NOTAVAILABLE, pcName, oString, pcValue, GetErrorContextText());
		}
	}

	m_macroCount ++;
	m_oDefinedItemsMap[ pcName ] = CString( pcValue);

	long nDefLen = _tcslen( pcName);
	m_lDefinedWordsMinLength = min( m_lDefinedWordsMinLength, nDefLen);
}

void CPreprocesor::RemoveDefinition( LPCTSTR pcName)
{
	CString oString;

	if( !m_oDefinedItemsMap.Lookup( pcName, oString))
	{
		ThrowNavoException2( ERCO_PREP_UNDEF_NOT_DEFINED, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}

	VERIFY( m_oDefinedItemsMap.RemoveKey( pcName));
}

CPreprocesor::GetVarVal CPreprocesor::GetVariableValue( LPCTSTR pcName, CSmartOleVariant &roSOV)
{
	VARTYPE varType;
	const TCHAR* pcDummy1;
	const TCHAR* pcDummy2;
	long nVarNr;

	if( !ParsePropertyName( pcName, nVarNr, varType, pcDummy1, pcDummy2))
	{
		return gvv_notvariable;
	}

	AddVarDependency( nVarNr);
	return m_poEnvironmentHLISP->SafeGetProp( nVarNr, roSOV) ? gvv_vardef : gvv_varnotdef;
}

//--------------------------------------------------------------------------------
//sprawdza czy lpSymbol jest zdefiniowany
//--------------------------------------------------------------------------------

bool CPreprocesor::is_symbol_defined(LPCTSTR lpSymbol)
{
	CString oValueString;

	//sprawdzamy czy by³o #define lpSymbol coœtam
	if(!GetDefinition(lpSymbol,oValueString))
	{
		//mo¿e lpSymbol jest nazw¹ zmiennej (w postaci v[s|n|d]nnnn)
		CSmartOleVariant oDummySOV;
		GetVarVal eGVV = GetVariableValue(lpSymbol,oDummySOV);
		return (eGVV == gvv_vardef);
	}
	else
	{
		//by³o zdefiniowane jako #define lpSymbol
		if(oValueString.IsEmpty())
		{
			return true;
		}

		//by³o zdefiniowane jako #define lpSymbol coœtam
		//jeœli coœtam jest jest nazw¹ zmiennej (w postaci v[s|n|d]nnnn)
		//to sprawdzamy czy ta zmienna jest zdefiniowana
		CSmartOleVariant oDummySOV;
		GetVarVal eGVV = GetVariableValue(oValueString,oDummySOV);

		return (eGVV != gvv_varnotdef);
	}
}

//--------------------------------------------------------------------------------
//zwraca wartoœæ lpSymbol jeœli jest zdefiniowany
//--------------------------------------------------------------------------------

bool CPreprocesor::GetSymbolValue( LPCTSTR lpSymbol, CSmartOleVariant &roValueSOV)
{
	CString oValueString;
	bool bDefined;


	if( !GetDefinition( lpSymbol, oValueString))
	{
		GetVarVal eGVV = GetVariableValue( lpSymbol, roValueSOV);
		bDefined = ( eGVV == gvv_vardef);
	}
	else
	{
		if( oValueString.IsEmpty())
		{
			return true;
		}

		GetVarVal eGVV = GetVariableValue( oValueString, roValueSOV);

		if( eGVV == gvv_notvariable)
		{
			//konwersja do przypuszczalnego typu
			CTokenizer oTokenizer( oValueString);
			CToken oToken;
			VERIFY( oTokenizer.GetToken( oToken));
			//ASSERT( oToken.GetType() == et_value);
			roValueSOV = oToken.GetValue();
		}

		bDefined = ( eGVV != gvv_varnotdef);
	}
	return bDefined;
}

void CPreprocesor::GetVarDependencies( long* pDependencies)
{
	POSITION pos = m_oDependencyMap.GetStartPosition();
	while( pos)
	{
		long nDummy;
		long nVarNr;
		m_oDependencyMap.GetNextAssoc( pos, nDummy, nVarNr);
		*pDependencies = nVarNr;
		pDependencies++;
	}
}

void CPreprocesor::GetIncludeDependencies( long* pDependencies)
{
	POSITION pos = m_oIncludeMap.GetStartPosition();
	while( pos)
	{
		long nDummy;
		long IdFile;
		m_oIncludeMap.GetNextAssoc( pos, nDummy, IdFile);
		*pDependencies = IdFile;
		pDependencies++;
	}
}

//---------------------------------------------------
//-------- directives' implementation ---------------
//
//
//	albo jest to #define ALA coœtam
//	albo odwo³anie do zmiennej œrodowiskowej ( vxnnnnn)
//
//
//---------------------------------------------------
void CPreprocesor::_read_continuation_lines(CString & roValueString)
{
	if(!roValueString.IsEmpty())
	{
		if(roValueString[roValueString.GetLength()-1] == '\\')
		{
			do
			{
				roValueString.SetAt(roValueString.GetLength()-1,'\n');	//zast¹p backslash znakiem nowej linii
				CArray <TCHAR, TCHAR &> oInputLineArray;
				oInputLineArray.SetSize( MAX_LINE_LENGTH);
				long nLineLen = m_oPrepFileDataStack.GetTop().m_oBufferToFile.ReadLine(oInputLineArray,false);
				CString oString(oInputLineArray.GetData(),nLineLen);
				oString.TrimRight();
				if(oString.IsEmpty())
				{
					break;
				}
				roValueString += oString;
				if(oString[oString.GetLength()-1] != '\\')
				{
					break;
				}
			}
			while(true);
		}
	}
}

void CPreprocesor::_Kwd_Define( TCHAR* pcCursor)
{
	 TCHAR * pcName;
	ReadIdentifier(pcName, pcCursor);
	SetNullAndMoveNext(pcCursor);

	if( *pcName == '(')
	{
		ThrowNavoException2( ERCO_TODO, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}

	SkipWhiteCharacters(pcCursor);
	CString	oValueString(pcCursor);
	oValueString.TrimRight();
	_read_continuation_lines(oValueString);

	if( m_bStillPure)
	{
		if(m_poPreprocessedDataCacheSP.PointsObject())
		{
			if( m_oPrepFileDataStack.GetTop().m_poPDSP.PointsNull())
			{
				TRACE1("PRECOMP: created precompiled data for file %d\n", m_oPrepFileDataStack.GetTop().m_IdFile);
				m_oPrepFileDataStack.GetTop().m_poPDSP = NewSCP( new CPrecompiledData());
			}
			
			m_oPrepFileDataStack.GetTop().m_poPDSP->AddDefinition( pcName, oValueString);
		}
	}

	//uwaga! AddDefinition mo¿e zmieniæ oValueString !! :)
	AddDefinition( pcName, oValueString);
}

bool CPreprocesor::_Kwd_Macro( TCHAR* pcCursor)
{
	 TCHAR* pcName;
	ReadIdentifier( pcName, pcCursor);

	if( *pcCursor != '(')
	{
		ThrowNavoException2( ERCO_TODO, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}
	
	CString oNameString( pcName, pcCursor - pcName);

	// swap '(' with MACRO_MARKER  
	*pcCursor = MACRO_MARKER;

	CString	oValueString( pcCursor);
	oValueString.TrimRight();
	_read_continuation_lines(oValueString);


	if( m_bStillPure)
	{
		if(m_poPreprocessedDataCacheSP.PointsObject())
		{
			if( m_oPrepFileDataStack.GetTop().m_poPDSP.PointsNull())
			{
				TRACE1("PRECOMP: created precompiled data for file %d\n", m_oPrepFileDataStack.GetTop().m_IdFile);
				m_oPrepFileDataStack.GetTop().m_poPDSP = NewSCP( new CPrecompiledData());
			}
			
			m_oPrepFileDataStack.GetTop().m_poPDSP->AddMacro( oNameString, oValueString);
		}
	}

	AddMacro( oNameString, oValueString);

	*pcCursor = '(';

	return true;
}

bool CPreprocesor::_Kwd_Ifdef( bool bExpectedDefined, TCHAR* pcCursor)
{
	 TCHAR* pcName;
	ReadIdentifier( pcName, pcCursor);
	SetNullAndMoveNext( pcCursor);

	if( !EnsureEndOfLine( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_EOL_EXPECTED, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}

	bool bDefined = is_symbol_defined(pcName);
	return ( ( bExpectedDefined && bDefined) || ( !bExpectedDefined && !bDefined));
}

bool CPreprocesor::_Kwd_If( TCHAR* pcCursor)
{
	const TCHAR* pcName = pcCursor;
	SkipWhiteCharacters( pcCursor);
	CEvaluator oEvaluator( pcCursor, this);

	if( m_bParseMode)
	{
		oEvaluator.SetParseOnlyMode();
	}

	CSmartOleVariant oSOV;

	if( !oEvaluator.Evaluate( oSOV))
	{
		ThrowNavoException3( ERCO_PREP_IF_EVAL_FAILED, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText(), 
			oEvaluator.GetLastErrorString());
	}
	oSOV.ChangeType( VT_BOOL);
	return oSOV.GetBool();
}

void CPreprocesor::_Kwd_Else( TCHAR* pcCursor)
{
	if( !EnsureEndOfLine( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_EOL_EXPECTED, IDPAGE_NOTAVAILABLE, pcCursor, GetErrorContextText());
	}
}

void CPreprocesor::_Kwd_Endif( TCHAR* pcCursor)
{
	if( !EnsureEndOfLine( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_EOL_EXPECTED, IDPAGE_NOTAVAILABLE, pcCursor, GetErrorContextText());
	}
}

void CPreprocesor::_Kwd_Undef( TCHAR* pcCursor)
{
	 TCHAR* pcName;
	ReadIdentifier( pcName, pcCursor);
	SetNullAndMoveNext( pcCursor);

	if( !EnsureEndOfLine( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_EOL_EXPECTED, IDPAGE_NOTAVAILABLE, pcName, GetErrorContextText());
	}

	RemoveDefinition( pcName);
}

void CPreprocesor::_Kwd_Include( TCHAR* pcCursor)
{
	SkipWhiteCharacters( pcCursor);

	if( *pcCursor != '\"')
	{
		ThrowNavoException2( ERCO_PREP_EXPECTED_QUOTE, IDPAGE_NOTAVAILABLE, pcCursor, GetErrorContextText());
	}
	
	pcCursor++;
	TCHAR* pcFileName = pcCursor;

	while( *pcCursor && *pcCursor != '\"')
	{
		pcCursor++;
	}

	if( !*pcCursor || pcCursor == pcFileName)
	{
		ThrowNavoException2( ERCO_PREP_EXPECTED_QUOTE, IDPAGE_NOTAVAILABLE, pcCursor, GetErrorContextText());
	}

	*pcCursor++ = '\0';

	if( !EnsureEndOfLine( pcCursor))
	{
		ThrowNavoException2( ERCO_PREP_EOL_EXPECTED, IDPAGE_NOTAVAILABLE, pcCursor, GetErrorContextText());
	}

	SCP<IStream> poIncludeStreamSP;
	long IdFile = -1;

	if( !_tcsncmp( pcFileName, _T( "local:"), 6))
	{
		//plik lokalny
		pcFileName += 6;
		poIncludeStreamSP = OpenFileStream_Read( pcFileName);
	}
	else
	{
		if( !IsDigit( *pcFileName))	//pomiñ ewentualnie jeden znak np. h
		{
			pcFileName++;
		}

		IdFile = _ttol( pcFileName);

		//to_do: ommited invalid file oNameString checking
		
		//check #define INCLUDED_file
		{
			CString oIncludedString;
			_build_file_included_define(IdFile,oIncludedString);
			CString oDummyString;
			if(GetDefinition(oIncludedString,oDummyString))
			{
				TRACE("SKIPPED %s\n",oIncludedString);
				return;
			}
			else
			{
				AddDefinition(oIncludedString, _T( ""));
			}
		}

		ASSERT( m_oPrepFileDataStack.GetCount() >= 1);

		if( m_oPrepFileDataStack.GetCount() == 1)	//direct #include file
		{
			AddIncludeDependency( IdFile);
		}

		if(m_poPreprocessedDataCacheSP.PointsObject())
		{
			SCP<IStream> poStreamSP;
			HRESULT hr = m_poPreprocessedDataCacheSP->GetData(IdFile,
				&poStreamSP.GetRawPointer());
			
			if(hr == S_OK)
			{
				SCP<CPrecompiledData> poPDSP = NewSCP(new CPrecompiledData());
				poPDSP->read(poStreamSP);
				long nCount = poPDSP->GetCount();
				
				for( long iter = 0; iter < nCount; iter++)
				{
					LPCTSTR pcName;
					LPCTSTR pcValue;
					switch(poPDSP->GetDefinition( iter, pcName, pcValue))
					{
					case cTypeDefine:
						AddDefinition( pcName, pcValue);
					break;
					case cTypeMacro:
						AddMacro(pcName,pcValue);
					break;
					default:
						ASSERT(false);
					}
				}
				
				ASSERT( FileIdIsHeader( IdFile));
				TRACE( "PRECOMP: applied data instead of %d(cnt=%d)\n", IdFile, nCount);
				return;
			}
		}

		TRACE("INCLUDING %d\n",IdFile);

		ASSERT( m_poStreamProviderSP.PointsObject());
		navostreaminfo oNSI;
		_init_navostreaminfo( oNSI);
		HRESULT hr = m_poStreamProviderSP->Get( IdFile, &poIncludeStreamSP.GetRawPointer(), &oNSI);

		if( hr != S_OK)
		{
			CNavoException oNavoException;
			GetErrorInfoFromInterface( m_poStreamProviderSP, oNavoException);
			ContinueThrowNavoException2( oNavoException, ERCO_PREP_UNABLE_TO_OPEN_INPUTFILE, IDPAGE_NOTAVAILABLE, IdFile, SCODE_To_String( hr));
		}

		ASSERT( oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');

		if( oNSI.m_bCompressed == '1')
		{
			poIncludeStreamSP = UncompressStream( poIncludeStreamSP);
		}
	}
	//disallow recursive includes
	POSITION pos = m_oPrepFileDataStack.GetTopPosition();

	while( pos)
	{
		if( IdFile == m_oPrepFileDataStack.MoveDown( pos).m_IdFile)
		{
			ThrowNavoException2( ERCO_PREP_RECURSIVE_INCLUDE, IDPAGE_NOTAVAILABLE, IdFile, GetErrorContextText());
		}
	}


	m_oPrepFileDataStack.Push( CPrepFileData( IdFile, poIncludeStreamSP));
}

void CPreprocesor::_Kwd_Pure()
{
}

bool CPreprocesor::ParseLine( LPCTSTR pcInputLine, CArrayWriter<TCHAR> &roOutputWriter)
{
	TCHAR * pcText = const_cast<TCHAR *>(pcInputLine);
	SkipWhiteCharacters( pcText);

	if( pcText[0] == '#')
	{
		if( pcText[1] != '*')
		{
			TCHAR * pcCursor;
			long nFoundKeyword = DetectKeyword( pcText, pcCursor);

			switch( nFoundKeyword)
			{
			case KEYWORD_DEFINE:
				if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
				{
					_Kwd_Define( pcCursor);
				}
			break;

			case KEYWORD_MACRO:
				if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
				{
					_Kwd_Macro( pcCursor);
				}
			break;

			case KEYWORD_IFDEF:
			if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
			{
				m_bStillPure = false;
				bool bCondition = _Kwd_Ifdef( true, pcCursor);
				m_oConditionStack.Push( bCondition);

				if( bCondition)
				{
					m_nPassedConditionsCount++;
				}
			}
			else
			{
				bool bConditionFalse = false;
				m_oConditionStack.Push(bConditionFalse);
			}
			break;

			case KEYWORD_IFNDEF:
			if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
			{
				m_bStillPure = false;
				bool bCondition = _Kwd_Ifdef( false, pcCursor);
				m_oConditionStack.Push( bCondition);

				if( bCondition)
				{
					m_nPassedConditionsCount++;
				}
			}
			else
			{
				bool bConditionFalse = false;
				m_oConditionStack.Push(bConditionFalse);
			}
			break;

			case KEYWORD_IF:
			if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
			{
				m_bStillPure = false;
				bool bCondition = _Kwd_If( pcCursor);
				m_oConditionStack.Push( bCondition);

				if( bCondition)
				{
					m_nPassedConditionsCount++;
				}
			}
			else
			{
				bool bConditionFalse = false;
				m_oConditionStack.Push(bConditionFalse);
			}
			break;

			case KEYWORD_ELSE:
				m_bStillPure = false;
				_Kwd_Else( pcCursor);

				if( m_oConditionStack.IsEmpty())
				{
					ThrowNavoException1( ERCO_PREP_UNEXPECTED_ELSE, IDPAGE_NOTAVAILABLE, GetErrorContextText());
				}

				m_oConditionStack.GetTop() = !m_oConditionStack.GetTop();

				if( m_oConditionStack.GetTop())
				{
					m_nPassedConditionsCount++;
				}
				else
				{
					m_nPassedConditionsCount--;
				}

			break;

			case KEYWORD_ENDIF:
				m_bStillPure = false;
				_Kwd_Endif( pcCursor);

				if( m_oConditionStack.IsEmpty())
				{
					ThrowNavoException1( ERCO_PREP_UNEXPECTED_ENDIF, IDPAGE_NOTAVAILABLE, GetErrorContextText());
				}

				if( m_oConditionStack.Pop())
				{
					m_nPassedConditionsCount--;
				}
			break;

			case KEYWORD_UNDEF:
				m_bStillPure = false;

				if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
				{
					_Kwd_Undef( pcCursor);
				}
			break;

			case KEYWORD_INCLUDE:
				if( ( m_nPassedConditionsCount == m_oConditionStack.GetCount()) || m_bParseMode)
				{
					_Kwd_Include( pcCursor);
				}
			break;

			case KEYWORD_COMMENT:
				//just skip line
			break;

			case KEYWORD_PURE:
			break;

			default:
				ThrowNavoException2( ERCO_PREP_UNKNOWN_DIRECTIVE, IDPAGE_NOTAVAILABLE, GetErrorContextText(), 
					pcInputLine);
			}
		}
		return true;
	}

	ASSERT( m_nPassedConditionsCount <= m_oConditionStack.GetCount());

	if( ( m_nPassedConditionsCount < m_oConditionStack.GetCount()) && !m_bParseMode)
	{
		//ignore line ( one of conditions failed)
		ASSERT( !m_bStillPure);
	}
	else 
	{
    	if( pcText[0] != '\0')
		{
			m_bStillPure = false;
			TranslateLine( pcInputLine, roOutputWriter);
		}

    	roOutputWriter << '\r';
		roOutputWriter << '\n';
	}

	return true;
}

//t³umaczy liniê ! uwaga mo¿e zmieniæ pcInputLine !!! :)

bool CPreprocesor::TranslateLine( LPCTSTR pcInputLine, CArrayWriter<TCHAR> &roOutputWriter)
{
	CIncDecHolder<int> oRecurLevel(m_recurLevel);

	if( m_recurLevel >= MAX_RECUR_DEPTH)
	{
		CString errMsg("exceded maximum recursion level while evaluating macro ");
		errMsg += CString( pcInputLine);
		ThrowNavoException2( ERCO_TODO, IDPAGE_NOTAVAILABLE, errMsg, GetErrorContextText());
	}

	LPCTSTR pcSource = pcInputLine;

	while( *pcSource)
	{
		bool bIsAsterisk = false;

		if( pcSource[0] == '#' && pcSource[1] == '#')
		{
			pcSource += 2;
			continue;
		}

		if( pcSource[0] == '#' && pcSource[1] == '*' && IsAlphaNum( pcSource[2]))
		{
			bIsAsterisk = true;
			pcSource += 2;
		}
		else
		{
			bool bFromBegin = false;

			while( *pcSource && !IsAlphaNum( *pcSource))
			{
				if( pcSource[0] == '#' && pcSource[1] == '*' && IsAlphaNum( pcSource[2]))
				{
					bFromBegin = true;
					break;
				}
				else
				{
					roOutputWriter << *pcSource;
					pcSource++;
				}
			}

			
			if( bFromBegin)
			{
				continue;
			}
			
			if( !*pcSource)
			{
				break;
			}

		}


		ASSERT( IsAlphaNum( *pcSource));
		TCHAR * pcWord = (TCHAR *) pcSource;

		while( *pcWord && IsAlphaNum( *pcWord))
		{
			pcWord++;
		}


		bool bMakro = false;
        const TCHAR* pcParam = pcWord;

        while( IsWhite( *pcParam))
        {
            pcParam ++;
        }

        if( *pcParam == '(') 
		{
			bMakro = true;
		}

		TCHAR cTempCharacter = *pcWord;
		*(LPTSTR)pcWord = '\0';

		const TCHAR* pcNewWord = pcSource;
		const TCHAR* pcNameString = pcSource;

		CString oDefinedString;
		
		if( pcWord - pcSource < m_lDefinedWordsMinLength)
		{
#ifdef _DEBUG
			m_lRejectedWords++;
#endif
		}
		else
		{
#ifdef _DEBUG
			m_lComparedWords++;
#endif
			if( GetDefinition( pcNameString, oDefinedString))
			{
				if( bMakro)
				{
//					*(LPTSTR)pcWord = cTempCharacter;
					pcWord = (TCHAR*) pcParam;
                    pcWord ++;  

					if( oDefinedString[0] == MACRO_MARKER)
					{
						FormatMacro( pcNameString, oDefinedString);
					}

					const TCHAR* pcParamStartArr[MAX_PARAM_COUNT];
					const TCHAR* pcParamEndArr[MAX_PARAM_COUNT];

					memset( pcParamStartArr, 0, sizeof( pcParamStartArr));
					memset( pcParamEndArr, 0, sizeof( pcParamEndArr));
					
					ExtractParams( pcSource, pcWord, pcParamStartArr, pcParamEndArr);

					cTempCharacter = *pcWord;
					*(LPTSTR)pcWord = '\0';

					TranslateMacro( oDefinedString, roOutputWriter, pcParamStartArr, pcParamEndArr);
					*(LPTSTR)pcNewWord = '\0';

				}
				else
				{
					if( m_macroCount > 0 && ( !bIsAsterisk))
					{
						TranslateLine( oDefinedString, roOutputWriter);
						*(LPTSTR)pcNewWord = '\0';
					}
					else
					{
						pcNewWord = oDefinedString;
					}

				}

#ifdef _DEBUG
;				m_lMatchedWords++;
#endif
			}
		}

		CString oEnvVarValueStr;
		CSmartOleVariant oSOV;

		if( bIsAsterisk)
		{
			GetVarVal eGVV = GetVariableValue( pcNewWord, oSOV);
			if( eGVV == gvv_vardef)
			{
				oSOV.ChangeType( VT_BSTR);
				oEnvVarValueStr = oSOV.GetBStr();
				pcNewWord = oEnvVarValueStr;
			}
			else
			{
				roOutputWriter << '#';
				roOutputWriter << '*';
			}

		}

		while( *pcNewWord)
		{
			roOutputWriter << *pcNewWord;
			pcNewWord++;
		}

		*(LPTSTR)pcWord = cTempCharacter;
		pcSource = pcWord;
	}

	return true;
}

bool CPreprocesor::TranslateMacro( LPCTSTR pcInputLine, CArrayWriter<TCHAR> &roOutputWriter,
                                   const TCHAR* pcParamStartArr[], const TCHAR* pcParamEndArr[])
{
	
	CArray<TCHAR, TCHAR&> oParamArray[MAX_PARAM_COUNT];
	int paramNo( 1);


	while( pcParamStartArr[paramNo] != NULL)
	{
		CArrayWriter<TCHAR> oParamWriter( oParamArray[paramNo]);
		TCHAR tmpChar = *pcParamEndArr[paramNo];
		*(LPTSTR)pcParamEndArr[paramNo] = '\0';		
		TranslateLine( pcParamStartArr[paramNo], oParamWriter);
		oParamArray[paramNo].SetSize( oParamWriter.CharactersWritten());
		*(LPTSTR)pcParamEndArr[paramNo] = tmpChar;
		paramNo ++;
	}
	
	LPCTSTR pcCursor = pcInputLine;
	CArray< TCHAR, TCHAR&> oInputArray;
	CArrayWriter< TCHAR> oInputArrayWriter( oInputArray);
	
	while( *pcCursor)
	{
		if ( *pcCursor == MACRO_PARAM_MARKER_BYTE0)
		{
			pcCursor ++;
			paramNo = ( int)( *pcCursor - 1);
			pcCursor ++;
			paramNo <<= 4;
			paramNo += ( int)( *pcCursor - 1);
			pcCursor ++;
			
			if( pcParamStartArr[paramNo] != NULL)
			{
				oInputArrayWriter.Write( oParamArray[paramNo].GetData(),oParamArray[paramNo].GetSize());
			}
			else
			{
				CString oString;
				oString.Format("Rozwiniêcie makra %s nieudane przy parametrze %d."
				" Prawdopodobnie za ma³o parametrów wywo³ania.\nKontekst [%s]",
				pcInputLine,paramNo,GetErrorContextText());
				
				ThrowNavoException1( ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
			}
		}
		else
		{
			oInputArrayWriter << *pcCursor;
			pcCursor ++;
		}
	}

	TranslateLine( oInputArray.GetData(), roOutputWriter);
	return true;
}

void CPreprocesor::FormatMacro( const TCHAR* &pcNameString, CString &oValueString)
{
	TCHAR * pcNewValue  = const_cast<TCHAR *>((const TCHAR*)oValueString);

	//move to the end of parameters
	while( *pcNewValue != ')')
	{
		pcNewValue ++;	
	}

	pcNewValue ++; // skip ')' 
	SkipWhiteCharacters( pcNewValue);

	CString oNewValueString( pcNewValue);

	TCHAR* pcName;

	TCHAR pcParamNo[4];
	pcParamNo[0] = MACRO_PARAM_MARKER_BYTE0;
	pcParamNo[3] = MACRO_PARAM_MARKER_BYTE3;

	TCHAR * pcOldValue = const_cast<TCHAR*>((const TCHAR*)oValueString);
	int paramNo = 1;
	TCHAR tmpChar;

	do 
	{
		pcOldValue ++;
		ReadIdentifier( pcName, pcOldValue);
		CString	param( pcName, pcOldValue - pcName);
		tmpChar = *pcOldValue;
		*(LPTSTR) pcOldValue = '\0';
		pcParamNo[1] = (TCHAR)( ( ( paramNo >> 4 ) & 15) + 1);
		pcParamNo[2] = (TCHAR)( ( paramNo & 15) + 1);

		CString oTmpValueString = oNewValueString;
		oNewValueString.Empty();

		int start = 0;
		int end = 0;
		int nameLen = _tcslen( pcName);
		int valueLen = oTmpValueString.GetLength(); 

		while( ( end = oTmpValueString.Find(pcName, end)) != -1)
		{
			TCHAR predChar = ( end > 0) ? ( oTmpValueString.GetAt( end - 1)) : (' ');
			TCHAR succChar = ( end + nameLen < valueLen) ? oTmpValueString.GetAt( end + nameLen) : (' ');
			

			if( !( IsAlphaNum( predChar) || IsAlphaNum( succChar)))
			{
				oNewValueString += oTmpValueString.Mid( start, end - start);
				oNewValueString += pcParamNo;
				end += nameLen;
				start = end;
			}
			else
			{
				end += nameLen;
			}
		}
		
		oNewValueString += oTmpValueString.Mid( start, valueLen - start);
		
		paramNo ++;
		*(LPTSTR) pcOldValue = tmpChar;

	} while( *pcOldValue == ',');

	if( *pcOldValue != ')')
	{
		ThrowNavoException2( ERCO_TODO, IDPAGE_NOTAVAILABLE, pcOldValue, GetErrorContextText());
	}

	RemoveDefinition( pcNameString);
	AddMacro( pcNameString, oNewValueString);
	oValueString = oNewValueString;
}

void CPreprocesor::ExtractParams( const TCHAR* &pcSource,TCHAR* &pcWord,const TCHAR* pcParamStartArr[], const TCHAR* pcParamEndArr[])
{
	int paramNo = 1;

	TCHAR pcParamNo[4];
	pcParamNo[0] = MACRO_PARAM_MARKER_BYTE0;
	pcParamNo[3] = MACRO_PARAM_MARKER_BYTE3;

	pcWord--;

	do
	{
		pcWord++;
		SkipWhiteCharacters( pcWord);
		
		pcSource = pcWord;

		int level = 1;
		TCHAR trigger='\0'; //string delimiter type: " '

		pcWord --;

		while (level > 0)
		{
			pcWord ++;


			if( *pcWord == trigger) // end of string found
			{
				level --;
				trigger = '\0';
			}
			else if( trigger == '\0') // we are outside string
			{
				if( *pcWord == '"' || *pcWord == '\'') //beggining of string
				{
					level ++;
					trigger = *pcWord;
				}

				if( *pcWord == '(') // enter another scope
				{
					level ++;
				}
				else if( *pcWord == ')') // leave the scope
				{
					level --;
				}
				else if( *pcWord == ',' && level == 1) // coma at the basic scope terminates parameter
				{
					level = 0;
				}
			}

		}


		TCHAR* pcTmpPos = pcWord; 

		do // trim the trailing whitespaces
		{
			pcWord --;
		} while( IsWhite( *pcWord));

		pcWord ++;

		pcParamNo[1] = (TCHAR)( ( paramNo >> 4 ) & 15 + 1);
		pcParamNo[2] = (TCHAR)( paramNo & 15 + 1);

 		pcParamStartArr[ paramNo] = pcSource;
		pcParamEndArr[ paramNo] = pcWord;

		pcWord = pcTmpPos;
		paramNo ++;
	} while( *pcWord == ',');

	if( *pcWord == ')')
	{
		pcWord ++;
	}
	else	
	{
		CString oString;
		oString.Format("Oczekiwany nawias zamykaj¹cy makro\nKontekst [%s]",
			GetErrorContextText());
		
		ThrowNavoException1( ERCO_TODO, IDPAGE_NOTAVAILABLE, oString);
	}
}
