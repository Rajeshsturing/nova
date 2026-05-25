/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CTreeDataProvider__ = 	abstract class for different tree data providers
		CTreeXMLDataProvider=	implementation for XML files (currently on DOM)
*/

#include "stdafx.h"
#pragma warning(disable:4786)

#include "..\include\h1000.h"
#include "..\navopx\navopx.h"
#include "..\include\saxhandler.h"

#include "treedataprov.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTreeDataProvider__::CTreeDataProvider__()
{
}

static const TCHAR * pcTokenNode	= _T("node");
static const TCHAR * pcTokenLabel	= _T("label");
static const TCHAR * pcTokenHLI		= _T("hli");
static const TCHAR * pcTokenIcon	= _T("icon");
static const TCHAR * pcTokenCmdIID	= _T("cmdiid");
static const TCHAR * pcAttribNoMenu	= _T("nomenu");


class CTreeXMLSAXHandler : public CSAXHandler__
{
public:
	CTreeXMLSAXHandler(CTreeXMLDataProvider * poProvider):
		CSAXHandler__(NULL),
	  m_poProvider(poProvider)
	{
		ASSERT(poProvider);
		m_oNodesStack.Push(NewSCP(new CTreeXMLDataProvider::CNodeInfo()));
		poProvider->m_oNodesMap[ 0 ] = _get_current_node();
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
private:
	SCP<CTreeXMLDataProvider::CNodeInfo> _get_current_node()
	{
		ASSERT(!m_oNodesStack.IsEmpty());
		return m_oNodesStack.GetTop();
	}
	CTreeXMLDataProvider * m_poProvider;
	CEnhancedStack< SCP<CTreeXMLDataProvider::CNodeInfo> > m_oNodesStack;
	enum eLastElement
	{
		ela_other,
		ela_label,
		ela_hli,
		ela_icon,
		ela_cmdiid,
	};
	
	eLastElement m_eLastElement;
};

void CTreeXMLSAXHandler::OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttribMap)
{
	ASSERT(_get_current_node().PointsObject());
	m_eLastElement = ela_other;

	if(_tcscmp(pcTokenNode,lpElement) == 0)		//node
	{
		SCP<CTreeXMLDataProvider::CNodeInfo> poNewNodeSP = NewSCP(new CTreeXMLDataProvider::CNodeInfo());
		long nIdent = m_poProvider->m_oNodesMap.GetCount();
		m_poProvider->m_oNodesMap[ nIdent ] = poNewNodeSP;
		_get_current_node()->m_oChildrenArray.Add(nIdent);

		{
			CString oDummyString;
			if(roAttribMap.Lookup(pcAttribNoMenu,oDummyString))
			{
				poNewNodeSP->m_bAdd2Menu = false;
			}
		}

		m_oNodesStack.Push(poNewNodeSP);
	}
	else
	{
		if(_tcscmp(pcTokenLabel,lpElement) == 0)		//label
		{
			m_eLastElement = ela_label;
		}
		else
		{
			if(_tcscmp(pcTokenHLI,lpElement) == 0)		//hyperlink
			{
				m_eLastElement = ela_hli;
			}
			else
			{
				if(_tcscmp(pcTokenIcon,lpElement) == 0)		//icon
				{
					m_eLastElement = ela_icon;
				}
				else
				{
					if(_tcscmp(pcTokenCmdIID,lpElement) == 0)		//cmdiid
					{
						m_eLastElement = ela_cmdiid;
					}
				}
			}
		}
	}

	if(m_eLastElement != ela_other)
	{
		if(_get_current_node()->m_poHLISP.PointsNull())
		{
			_get_current_node()->m_poHLISP = NewSCP(new CHyperLinkInfo());
			_get_current_node()->m_poHLISP->SetStrProp(PROPC_LABEL,"");
			_get_current_node()->m_poHLISP->SetNumProp(PROPC_CMD_IID,0);
		}
	}
}

void CTreeXMLSAXHandler::OnEndElement(LPCTSTR lpElement)
{
	if(_tcscmp(pcTokenNode,lpElement) == 0)		//node
	{
		m_oNodesStack.Pop();
	}
}

void CTreeXMLSAXHandler::OnDataValue(LPCTSTR lpValue)
{
	ASSERT(_get_current_node().PointsObject());

	switch(m_eLastElement)
	{
	case ela_label:
	{
		CString oLabelString = lpValue;
		oLabelString.TrimLeft();
		oLabelString.TrimRight();
		_get_current_node()->m_poHLISP->SetStrProp(PROPC_LABEL,oLabelString);
	}
	break;
	case ela_hli:
		{
			SCP<CHyperLinkInfo> poHLISP = ReadHLIFromString(lpValue);
			//podmieniamy istniej¹ce property
			//hyperlink nie ma operator += :(
			if(_get_current_node()->m_poHLISP->PropertyExists(PROPC_ICON))
			{
				poHLISP->SetProp(PROPC_ICON,
					_get_current_node()->m_poHLISP->GetProp(PROPC_ICON));
			}
			if(_get_current_node()->m_poHLISP->PropertyExists(PROPC_LABEL))
			{
				poHLISP->SetProp(PROPC_LABEL,
					_get_current_node()->m_poHLISP->GetProp(PROPC_LABEL));
			}
			if(_get_current_node()->m_poHLISP->PropertyExists(PROPC_CMD_IID))
			{
				poHLISP->SetProp(PROPC_CMD_IID,
					_get_current_node()->m_poHLISP->GetProp(PROPC_CMD_IID));
			}
			_get_current_node()->m_poHLISP = poHLISP;
		}
	break;
	case ela_icon:
		{
			CString oIconString = lpValue;
			oIconString.TrimLeft();
			oIconString.TrimRight();
			CSmartOleVariant oIconSOV;
			if(!oIconString.IsEmpty())
			{
				long nIdImageList = _ttol(oIconString);

				if(nIdImageList != 0)
				{
					oIconSOV = CSmartOleVariant(long(nIdImageList),VT_I4);
				}
				else
				{
					oIconSOV = oIconString;
				}
				_get_current_node()->m_poHLISP->SetProp(PROPC_ICON,oIconSOV);
			}
		}
	break;
	case ela_cmdiid:
		{
			_get_current_node()->m_poHLISP->SetNumProp(PROPC_CMD_IID,_ttol(lpValue));
		}
	case ela_other:
		;
	break;
	default:
		ASSERT(false);
	}
}



CTreeXMLDataProvider::CTreeXMLDataProvider(SCP<IStream> & rpoInputStreamSP) :
	CTreeDataProvider__()
{
	SCP<INavoErrorInfo> poNavoErrorInfoSP;
	if(!ParseXML(NewSCP<CSAXHandler__>(new CTreeXMLSAXHandler(this)),rpoInputStreamSP,poNavoErrorInfoSP))
	{
		ThrowFromInterface(poNavoErrorInfoSP);
	}
}

void CTreeXMLDataProvider::GetChildren(long IdNode,CArray<long,long> & roChildrenArray)
{
	SCP<CNodeInfo> poNodeInfoSP;
	if(!m_oNodesMap.Lookup(IdNode,poNodeInfoSP))
	{
		ThrowNavoException1(ERCO_TREEXML_NO_SUCH_NODE,IDPAGE_NOTAVAILABLE,IdNode);
	}
	ASSERT(poNodeInfoSP.PointsObject());
	roChildrenArray.Copy(poNodeInfoSP->m_oChildrenArray);
}



SCP<CHyperLinkInfo> CTreeXMLDataProvider::GetNode(long IdNode)
{
	SCP<CNodeInfo> poNodeInfoSP = _get_node(IdNode);
	ASSERT(poNodeInfoSP->m_poHLISP.PointsObject());
	return poNodeInfoSP->m_poHLISP; 
}

bool CTreeXMLDataProvider::Add2Menu(long IdNode)
{
	return _get_node(IdNode)->m_bAdd2Menu;
}

SCP<CTreeXMLDataProvider::CNodeInfo> CTreeXMLDataProvider::_get_node(long IdNode)
{
	SCP<CNodeInfo> poNodeInfoSP;
	if(!m_oNodesMap.Lookup(IdNode,poNodeInfoSP))
	{
		ThrowNavoException1(ERCO_TREEXML_NO_SUCH_NODE,IDPAGE_NOTAVAILABLE,IdNode);
	}
	ASSERT(poNodeInfoSP.PointsObject());
	return poNodeInfoSP;
}

//--------------------------------------------------------------------------------
// automation support
//--------------------------------------------------------------------------------
class CTreeXMLAutoObject;

class CTreeXMLNodeAutoObject : public CCmdTargetInterface
{
public:
	CTreeXMLNodeAutoObject(SCP<CTreeXMLAutoObject> & rpoTreeXMLObjectSP,
		SCP<CTreeXMLDataProvider::CNodeInfo> & rpoNodeInfoSP,long nNodeId);
	//{{AFX_MSG(CTreeXMLNodeAutoObject)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CTreeXMLNodeAutoObject)
	afx_msg LPDISPATCH GetHyperLinkAUTO();
	afx_msg long GetNodeIdAUTO();
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	afx_msg long GetChildrenCountAUTO();
	afx_msg BOOL Add2MenuAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	SCP<CTreeXMLAutoObject> m_poTreeXMLObjectSP;
	SCP<CTreeXMLDataProvider::CNodeInfo> m_poNodeInfoSP;
	long m_nNodeId;
};

class CTreeXMLAutoObject : public CCmdTargetInterface
{
public:
	CTreeXMLAutoObject(SCP<CTreeXMLDataProvider> & rpoTreeXMLDataProviderSP);
	
	SCP<CTreeXMLDataProvider> _get_provider()
	{
		return m_poTreeXMLDataProviderSP;
	}
	//{{AFX_MSG(CTreeXMLAutoObject)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CTreeXMLAutoObject)
	afx_msg LPDISPATCH GetNodeAUTO(long nNodeId);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	SCP<CTreeXMLDataProvider> m_poTreeXMLDataProviderSP;
};


SCP<IDispatch> CTreeXMLDataProvider::get_automation_object()
{
	SCP<CTreeXMLAutoObject> poTreeXMLAutoObjectSP = NewSCP(new CTreeXMLAutoObject(NewSCP(this,true)));
	return poTreeXMLAutoObjectSP->GetDispatchSP();
}

CTreeXMLAutoObject::CTreeXMLAutoObject(SCP<CTreeXMLDataProvider> & rpoTreeXMLDataProviderSP) :
	m_poTreeXMLDataProviderSP(rpoTreeXMLDataProviderSP)
{
	EnableAutomation();
}

CTreeXMLNodeAutoObject::CTreeXMLNodeAutoObject(SCP<CTreeXMLAutoObject> & rpoTreeXMLObjectSP,
	SCP<CTreeXMLDataProvider::CNodeInfo> & rpoNodeInfoSP,long nNodeId) :
		m_poTreeXMLObjectSP(rpoTreeXMLObjectSP),
		m_poNodeInfoSP(rpoNodeInfoSP),
		m_nNodeId(nNodeId)
{
	EnableAutomation();
}


//{{AFX_MSG_MAP(CTreeXMLNodeAutoObject)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CTreeXMLNodeAutoObject, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CTreeXMLNodeAutoObject)
	DISP_FUNCTION(CTreeXMLNodeAutoObject, "hli", GetHyperLinkAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CTreeXMLNodeAutoObject, "ident", GetNodeIdAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CTreeXMLNodeAutoObject, "count", GetChildrenCountAUTO, VT_I4, VTS_NONE)
	DISP_FUNCTION(CTreeXMLNodeAutoObject, "add2menu", Add2MenuAUTO, VT_BOOL, VTS_NONE)
	DISP_PROPERTY_EX_ID(CTreeXMLNodeAutoObject, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//{{AFX_MSG_MAP(CTreeXMLAutoObject)
//}}AFX_MSG_MAP

BEGIN_DISPATCH_MAP(CTreeXMLAutoObject, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CTreeXMLAutoObject)
	DISP_FUNCTION(CTreeXMLAutoObject, "node", GetNodeAUTO, VT_DISPATCH, VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_ARRAYENUMERATOR(SCP<CTreeXMLNodeAutoObject>)

LPDISPATCH CTreeXMLNodeAutoObject::GetHyperLinkAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poNodeInfoSP.PointsObject());
		ASSERT(m_poNodeInfoSP->m_poHLISP.PointsObject());
		return m_poNodeInfoSP->m_poHLISP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CTreeXMLNodeAutoObject::GetNodeIdAUTO()
{
	ALL_TRY
	{
		return m_nNodeId;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}
	
BOOL CTreeXMLNodeAutoObject::Add2MenuAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poNodeInfoSP.PointsObject());
		return (m_poNodeInfoSP->m_bAdd2Menu != false);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

long CTreeXMLNodeAutoObject::GetChildrenCountAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poNodeInfoSP.PointsObject());
		return m_poNodeInfoSP->m_oChildrenArray.GetSize();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPUNKNOWN CTreeXMLNodeAutoObject::GetNewEnumAUTO()
{
	ALL_TRY
	{
		ASSERT(m_poNodeInfoSP.PointsObject());
		SCP< CArrayEnumeratorWithArray< SCP<CTreeXMLNodeAutoObject> > > poNewArrayEnumSP = 
			NewSCP(new CArrayEnumeratorWithArray< SCP<CTreeXMLNodeAutoObject> >(m_poNodeInfoSP->m_oChildrenArray.GetSize()));
		
		for(long iter = 0; iter <= m_poNodeInfoSP->m_oChildrenArray.GetUpperBound(); iter++)
		{
			long nNodeId = m_poNodeInfoSP->m_oChildrenArray[iter];
			poNewArrayEnumSP->SetAt(iter,
				NewSCP(new CTreeXMLNodeAutoObject(m_poTreeXMLObjectSP,
				m_poTreeXMLObjectSP->_get_provider()->_get_node(nNodeId),nNodeId)));
		}

		return poNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CTreeXMLNodeAutoObject::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","treexmlnode");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CTreeXMLAutoObject::GetNodeAUTO(long nNodeId)
{
	ALL_TRY
	{
		return NewSCP(new CTreeXMLNodeAutoObject(NewSCP(this,true),
			m_poTreeXMLDataProviderSP->_get_node(nNodeId),nNodeId))->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}


