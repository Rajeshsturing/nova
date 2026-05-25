/*
	NAVO Enterprise (2001)
	StdObj class Definition parser
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\saxhandler.h"
#include "..\include\InterfaceUtil.h"
#include "stdobjdefparser.h"
#include "stdobjdef.h"
#include "DefinitionManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum SODTokenType
{
	none = 0,
	objclass,
	table,
	humanname,
	isvirtual,
	identifier,
	idobj,
	script,
	embedded,
	ref,
	wildref,
	file,
	list,
	enumeration,
	name,
	sqltype,
	optional,
	computed,
	reftypeid,
	humannamef,
	isvirtualf,
	unique,
	nonempty,
	defaultvalue,
	cursors,
	cursor,
	where,
	join,
	orderby,
	forwardonly,
	storedproc,
	mssqlspbody,
	item,
	child,
	dontcacheonserver,
	dontcacheonclient,
	hidden,
	hiddenfield,
	alwayscandel
};

class CStdObjDefSAXHandler : public CSAXHandler__
{
public:
	CStdObjDefSAXHandler(SCP<CDefinitionManager> & rpoDefinitonManagerSP) : 
		CSAXHandler__(NULL),
		m_poDMSP(rpoDefinitonManagerSP),
		m_nTypeId(0),
		m_eState(stnone),
		m_eCurrentToken(none),
		m_eCurrentFieldTypeToken(none),
		m_bWasIdObj(false)
	{
		m_poObjectDefSP = rpoDefinitonManagerSP->NewStdObjDef();
	}
	virtual void OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes);
	virtual void OnEndElement(LPCTSTR lpElement);
	virtual bool IsDataDirect() const
	{
		return false;
	}
	virtual void OnDataValue(LPCTSTR,long)
	{
		ASSERT(false);
	}
	virtual void OnDataValue(LPCTSTR lpValue);

	enum State
	{
		stnone,		//expecting class
		stclass,	//expecting objlevel items
		stfield,	//expecting fieldlevel items
		stcursor,	//expecting cursor items
		stcursorlvl,//expecting cursor level items
	};
private:
	bool			m_bWasIdObj;
	State			m_eState;
	SODTokenType	m_eCurrentFieldTypeToken;
	SODTokenType	m_eCurrentToken;

	void InsertIdObjDefiniton();

	SCP<CDefinitionManager> m_poDMSP;
	long					m_nTypeId;
	SCP<CStdObjDef>			m_poObjectDefSP;
	SCP<CStdObjFieldDef>	m_poFieldDefSP;
	SCP<CCursorDef>			m_poCursorDefSP;
};

///////////////////////////////////////////

struct ClassNameAndToken
{
	const TCHAR *						m_pName;
	SODTokenType						m_eToken;
};

struct FldNameAndToken
{
	const TCHAR *						m_pName;
	SODTokenType						m_eToken;
};

struct CrsrNameAndToken
{
	const TCHAR *						m_pName;
	SODTokenType						m_eToken;
};

#define TOKMAP(_x_) \
	{ _T(#_x_), _x_ },

#define TOKMAPEX( _x_, _y_) \
	{ _T(#_x_), _y_ },

static const ClassNameAndToken StdObjDefTokens[] =
{
	TOKMAPEX(class,objclass)
	TOKMAP(table)
	TOKMAP(humanname)
	TOKMAPEX(virtual,isvirtual)
	TOKMAP(identifier)
	TOKMAP(idobj)
	TOKMAP(script)
	TOKMAP(embedded)
	TOKMAP(ref)
	TOKMAP(wildref)
	TOKMAP(file)
	TOKMAP(list)
	TOKMAPEX(enum,enumeration)
	TOKMAP(cursors)
	TOKMAP(cursor)
	TOKMAP(child)
	TOKMAP(dontcacheonserver)
	TOKMAP(dontcacheonclient)
	TOKMAP(hidden)
	TOKMAP(alwayscandel)
	{ NULL, none }
};

static const FldNameAndToken StdObjFieldDefTokens[] =
{
	TOKMAPEX(virtual,isvirtualf)
	TOKMAPEX(humanname,humannamef)
	TOKMAP(name)
	TOKMAP(sqltype)
	TOKMAP(optional)
	TOKMAP(computed)
	TOKMAPEX(typeid,reftypeid)
	TOKMAP(unique)
	TOKMAP(nonempty)
	TOKMAPEX(default,defaultvalue)
	TOKMAP(item)
	TOKMAPEX(hidden,hiddenfield)
	{ NULL,	none }
};

static const CrsrNameAndToken StdObjCursorTokens[] =
{
	TOKMAP(identifier)
	TOKMAP(humanname)
	TOKMAP(where)
	TOKMAP(join)
	TOKMAP(orderby)
	TOKMAP(forwardonly)
	TOKMAP(storedproc)
	TOKMAP(mssqlspbody)
};

static inline long FindSODT(LPCTSTR lpToken)
{
	long Index = 0;
	for(const ClassNameAndToken * pNAT = StdObjDefTokens; pNAT->m_pName; pNAT++, Index++)
	{
		if(!_tcscmp(lpToken,pNAT->m_pName))
		{
			return Index;
		}
	}
	return -1;
}

static inline long FindSOFDT(LPCTSTR lpToken)
{
	long Index = 0;
	for(const FldNameAndToken * pNAT = StdObjFieldDefTokens; pNAT->m_pName; pNAT++, Index++)
	{
		if(!_tcscmp(lpToken,pNAT->m_pName))
		{
			return Index;
		}
	}
	return -1;
}

static inline long FindSOCrsrT(LPCTSTR lpToken)
{
	long Index = 0;
	for(const CrsrNameAndToken * pNAT = StdObjCursorTokens; pNAT->m_pName; pNAT++, Index++)
	{
		if(!_tcscmp(lpToken,pNAT->m_pName))
		{
			return Index;
		}
	}
	return -1;
}

///////////////////////////////////////////

void CStdObjDefSAXHandler::InsertIdObjDefiniton()
{
	SCP<CStdObjFieldDef> poFieldDefSP = m_poObjectDefSP->NewField();

	poFieldDefSP->SetName(_T("IdObj"));
	poFieldDefSP->SetSQLType(SQLT_INT);
	m_poObjectDefSP->AddField(poFieldDefSP);
}

void CStdObjDefSAXHandler::OnStartElement(LPCTSTR lpElement,const CMapStringToString &)
{
	CString oElementString(lpElement);
	oElementString.MakeLower();

//	TRACE1("start=%s\n",oElementString);
	switch(m_eState)
	{
	case stnone:
		if(oElementString == _T("class"))		//this way, cause only one item
		{
			m_eState = stclass;
			m_eCurrentToken = objclass;
			return;
		}
	break;
	case stclass:
	{
		long Inx = FindSODT(oElementString);
		if(Inx != -1)
		{
			m_eCurrentToken = StdObjDefTokens[Inx].m_eToken;
			switch(m_eCurrentToken)
			{
			case isvirtual:
				m_poObjectDefSP->SetVolatile();
			break;
			case identifier:
				if(m_nTypeId != 0)
				{
					ThrowNavoException1(ERCO_PARSE_ONLY_ONCE,IDPAGE_NOTAVAILABLE,lpElement);
				}
			break;
			case idobj:
				InsertIdObjDefiniton();
				m_bWasIdObj = true;
			break;
			case embedded:
			case ref:
			case wildref:
			case file:
			case list:
			case enumeration:
			{
				m_eState = stfield;
				m_eCurrentFieldTypeToken = m_eCurrentToken;
				if(m_poFieldDefSP.PointsObject())
				{
					ThrowNavoException1(ERCO_PARSE_NEWFIELD_UNEXPECTED,IDPAGE_NOTAVAILABLE,oElementString);
				}
				m_poFieldDefSP = m_poObjectDefSP->NewField();
				switch(m_eCurrentFieldTypeToken)
				{
				case embedded:
					m_poFieldDefSP->SetRelationType(RELT_EMBED);
				break;
				case ref:
					m_poFieldDefSP->SetRelationType(RELT_REF);
				break;
				case wildref:
					m_poFieldDefSP->SetRelationType(RELT_WILDREF);
				break;
				case file:
					m_poFieldDefSP->SetRelationType(RELT_FILE);
				break;
				case list:
					m_poFieldDefSP->SetRelationType(RELT_LIST);
				break;
				case enumeration:
					m_poFieldDefSP->SetRelationType(RELT_ENUM);
				break;
				default:
					ASSERT(false);
				}
			}
			break;
			case child:
				m_poObjectDefSP->SetChild();
			break;
			case hidden:
				m_poObjectDefSP->SetHidden();
			break;
			case alwayscandel:
				m_poObjectDefSP->set_AlwaysCanDel();
			break;
			case dontcacheonserver:
				m_poObjectDefSP->SetDontCacheOnServer();
			break;
			case dontcacheonclient:
				m_poObjectDefSP->SetDontCacheOnClient();
			break;
			case humanname:
			case table:
			case script:
				//wait for value
			break;
			case cursors:
				m_eState = stcursor;
			break;
			default:
				ASSERT(false);
			}
			return;
		}
	}
	break;
	case stfield:
	{
		long Inx = FindSOFDT(oElementString);
		if(Inx != -1)
		{
			m_eCurrentToken = StdObjFieldDefTokens[ Inx ].m_eToken;
			switch(m_eCurrentToken)
			{
			case name:
			case sqltype:
			case reftypeid:
			case item:
			case humannamef:
			case defaultvalue:
			break;
			case optional:
				m_poFieldDefSP->SetRefOptional();
			break;
			case computed:
				m_poFieldDefSP->MarkComputed();
			break;
			case isvirtualf:
				m_poFieldDefSP->SetVirtual();
			break;
			case nonempty:
				m_poFieldDefSP->SetNonEmpty();
			break;
			case unique:
				m_poFieldDefSP->SetUnique();
			break;
			case hiddenfield:
				m_poFieldDefSP->set_hidden();
			break;
			default:
				ASSERT(false);
			}
			return;
		}
	}
	break;
	case stcursor:
	{
		if(oElementString == _T("cursor"))
		{
			m_eState = stcursorlvl;
			m_poCursorDefSP = NewSCP(new CCursorDef());
			return;
		}
	}
	break;
	case stcursorlvl:
	{
		long Inx = FindSOCrsrT(oElementString);
		if(Inx != -1)
		{
			m_eCurrentToken = StdObjCursorTokens[ Inx ].m_eToken;
			switch(m_eCurrentToken)
			{
			case forwardonly:
				ASSERT(m_poCursorDefSP.PointsObject());
				m_poCursorDefSP->SetForwardOnly(TRUE);
			break;
			}
			return;
		}

	}
	break;
	default:
		ASSERT(false);
	}
	ThrowNavoException1(ERCO_PARSE_EXPECTED_SOMETHING_ELSE,IDPAGE_NOTAVAILABLE,oElementString);
}

void CStdObjDefSAXHandler::OnEndElement(LPCTSTR lpElement)
{
	CString oElementString(lpElement);
	oElementString.MakeLower();
	
//	TRACE1("end=%s\n",oElementString);
	switch(m_eState)
	{
	case stclass:
		if(oElementString == _T("class"))		//this way, cause only one item
		{
			m_eState = stnone;
			if(m_nTypeId == 0)
			{
				ThrowNavoException(ERCO_PARSE_MISSING_TYPEID,IDPAGE_NOTAVAILABLE);
			}
			m_poDMSP->AddStdObjDef(m_nTypeId,m_poObjectDefSP);
			m_poObjectDefSP = 0;
		}
	break;
	case stfield:
	{
		long Inx = FindSOFDT(oElementString);
		if(Inx != -1)
		{
			break;
		}
		Inx = FindSODT(oElementString);
		if(Inx != -1)
		{
			switch(StdObjDefTokens[Inx].m_eToken)
			{
			case embedded:
			case ref:
			case wildref:
			case file:
			case list:
			case enumeration:
				m_poObjectDefSP->AddField(m_poFieldDefSP);
				m_eState = stclass;
				m_poFieldDefSP = 0;
				m_eCurrentFieldTypeToken = none;
			break;
			}
			break;
		}
	}
	break;
	case stcursor:
		if(oElementString == _T("cursors"))
		{
			m_eState = stclass;
		}
	break;
	case stcursorlvl:
		if(oElementString == _T("cursor"))
		{
			ASSERT(m_poObjectDefSP);
			ASSERT(m_poCursorDefSP.PointsObject());
			m_poObjectDefSP->AddCursorDef(m_poCursorDefSP);
			m_poCursorDefSP = 0;
			m_eState = stcursor;
		}
	break;
	default:
		ASSERT(false);
	}
}

void CStdObjDefSAXHandler::OnDataValue(LPCTSTR lpValue)
{
	CString oValueString(lpValue);
	oValueString.TrimLeft();
	oValueString.TrimRight();
	if(oValueString.IsEmpty())
	{
		return;
	}

	switch(m_eCurrentToken)
	{
	case objclass:
	case idobj:
	case isvirtualf:
	case optional:
	case computed:
		ThrowNavoException1(ERCO_PARSE_VALUE_UNEXPECTED,IDPAGE_NOTAVAILABLE,lpValue);
	break;
	case identifier:
		if(m_eState == stclass)		//stdobj id
		{
			m_nTypeId = _ttol(oValueString);	
			if(m_nTypeId == 0)
			{
				ThrowNavoException1(ERCO_PARSE_BAD_TYPEID,IDPAGE_NOTAVAILABLE,lpValue);
			}
		}
		else if(m_eState == stcursorlvl)	//cursor name
		{
			ASSERT(m_poCursorDefSP.PointsObject());
			m_poCursorDefSP->SetIdent(_ttol(oValueString));
		}
		else
		{
			ASSERT(false);
		}
	break;
	case script:
		//script - it is OK to insert original text with whitespaces (newlines etc.)
		m_poObjectDefSP->SetScriptCode(lpValue);
	break;
	case table:
		m_poObjectDefSP->SetTableName(oValueString);
	break;
	case humanname:
		if(m_eState == stclass)		//field name
		{
			m_poObjectDefSP->SetHumanName(oValueString);
		}
		else if(m_eState == stcursorlvl)	//cursor name
		{
			m_poCursorDefSP->SetHumanName(oValueString);
		}
		else
		{
			ASSERT(false);
		}
	break;
	//field definiton
	case name:
		ASSERT(m_poFieldDefSP.PointsObject());
		m_poFieldDefSP->SetName(oValueString);
	break;
	case sqltype:
	{
		if(m_eCurrentFieldTypeToken == ref || m_eCurrentFieldTypeToken == wildref || 
			m_eCurrentFieldTypeToken == file || m_eCurrentFieldTypeToken == list ||
			m_eCurrentFieldTypeToken == enumeration)
		{
			ThrowNavoException1(ERCO_PARSE_VALUE_UNEXPECTED,IDPAGE_NOTAVAILABLE,lpValue);
		}

		ASSERT(m_poFieldDefSP.PointsObject());
		TCHAR * pPtr = NULL;
		long nValue = _tcstol(oValueString,&pPtr,10);
		ASSERT(pPtr);
		if(!IsSpace(*pPtr) && !(*pPtr=='\0'))
		{
			ThrowNavoException1(ERCO_SOFD_INVALID_SQLTYPE,IDPAGE_NOTAVAILABLE,nValue);
		}
		m_poFieldDefSP->SetSQLType(nValue);
	}
	break;
	case reftypeid:
	{
		long nTypeId = _ttol(oValueString);
		if(nTypeId == 0)
		{
			ThrowNavoException1(ERCO_PARSE_BAD_TYPEID,IDPAGE_NOTAVAILABLE,lpValue);
		}
		ASSERT(m_poFieldDefSP.PointsObject());
		if(m_eCurrentFieldTypeToken == ref || m_eCurrentFieldTypeToken == list)
		{
			m_poFieldDefSP->SetReferenceTypeId(nTypeId);
		}
		else if(m_eCurrentFieldTypeToken == wildref)
		{
			m_poFieldDefSP->AddWildRefTypeId(nTypeId);
		}
		else
		{
			ThrowNavoException1(ERCO_PARSE_VALUE_UNEXPECTED,IDPAGE_NOTAVAILABLE,lpValue);
		}
	}
	break;
	case item:
	{
		m_poFieldDefSP->AddEnumValue(oValueString);
	}
	break;
	case humannamef:
		ASSERT(m_poFieldDefSP.PointsObject());
		m_poFieldDefSP->SetHumanName(oValueString);
	break;
	case defaultvalue:
	{
		ASSERT(m_poFieldDefSP.PointsObject());
		CSmartOleVariant oSOV(oValueString);
		//supply value as BSTR, will be converted by PostProcess
		m_poFieldDefSP->SetDefaultValue(oSOV);
	}
	break;
	case where:
		ASSERT(m_poCursorDefSP.PointsObject());
		m_poCursorDefSP->SetWhere(oValueString);
	break;
	case join:
		ASSERT(m_poCursorDefSP.PointsObject());
		m_poCursorDefSP->SetJoin(oValueString);
	break;
	case orderby:
		ASSERT(m_poCursorDefSP.PointsObject());
		m_poCursorDefSP->SetOrderBy(oValueString);
	break;
	case storedproc:
		ASSERT(m_poCursorDefSP.PointsObject());
		m_poCursorDefSP->SetSPName(oValueString);
	break;
	case mssqlspbody:
		ASSERT(m_poCursorDefSP.PointsObject());
		m_poCursorDefSP->SetSPBody(lpValue);
	break;
	default:
		ASSERT(false);
	}
}

bool ParseStdObjDefinition(SCP<IStream> & rpoIStreamSP,SCP<CDefinitionManager> & rpoDefinitonManagerSP,
						   SCP<INavoErrorInfo> & rpoNavoErrorInfoSP)
{
	ASSERT(rpoNavoErrorInfoSP.PointsNull());		//aby ktoœ nie poda³ czegoœ co nadpiszemy
	return ParseXML(NewSCP<CSAXHandler__>(new CStdObjDefSAXHandler(rpoDefinitonManagerSP)),rpoIStreamSP,rpoNavoErrorInfoSP);
}
