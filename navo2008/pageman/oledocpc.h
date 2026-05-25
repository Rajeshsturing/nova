/*
	NAVO Sp. z o.o. (2001)
	NAVO Enterprise
	class:
		COleDocPageContext - page context dla Active Documents
*/

#ifndef _OLEDOCPC_H_
#define _OLEDOCPC_H_

//------------------------------------------------------
//	dokument pomocniczy, odpowiednik CUIPageManager'a 
//------------------------------------------------------

class CNavoOleDoc : public COleDocument
{
public:
	CNavoOleDoc(){}
	virtual BOOL CanCloseFrame(CFrameWnd*)
	{
		return TRUE;
	}
};


//----------------------------------------------------------
//	CNavoOleDocCntrItem - daleki odpowiednim CUIOleControlElement
//----------------------------------------------------------
class CNavoOleDocCntrItem : public COleDocObjectItem
{
public:
	CNavoOleDocCntrItem(CNavoOleDoc * poNavoOleDoc) :
	  COleDocObjectItem(poNavoOleDoc),
	  m_hCreateResult(S_OK)
	{
	}
	virtual BOOL FinishCreate(SCODE sc);
	virtual void OnInsertMenus(CMenu* pMenuShared,
		LPOLEMENUGROUPWIDTHS lpMenuWidths);
	virtual void OnRemoveMenus(CMenu *pMenuShared);

	HRESULT GetCreateResult() const
	{
		return m_hCreateResult;
	}
  //{{AFX_VIRTUAL(CNavoOleDocCntrItem)
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL
private:
	HRESULT m_hCreateResult;
};

class COleDocPageContext : public CPageContext
{
public:
	COleDocPageContext(CPageContextStack * poPageContextStack,SCP <CHyperLinkInfo> & rpoOpeningHLISP);
	virtual ~COleDocPageContext();
	virtual bool Prepare();					//inicjuje przygotowanie do pracy
	virtual bool UnPrepare();
	virtual void __Reactivate(CWnd * pWnd);	//pod³¹cza do view
	virtual void __Deactivate(bool bFinal);	//od³acza od view
	virtual CRuntimeClass * GetViewType() const;
	virtual CUserCmdResult ProcessCommand(SCP <CHyperLinkInfo> & poHLISP);
	virtual bool OnDataEvent(CDC & roDC,const CDataUnit & roDataUnit);
	virtual bool IsCommandEnabled(long IdCommand);
	virtual long Print();
	virtual void OnZoom()
	{
		//to_do:
	}
private:
	CNavoOleDoc *			m_poNavoOleDoc;
	CNavoOleDocCntrItem *	m_poNODCI;
	CView *	m_poNODView;
};

#else
	#error __FILE__ already included
#endif