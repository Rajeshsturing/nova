/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CNAVOOleServerDoc - wsparcie dla OLE InPlace
*/

#ifndef _OLESERDOC_H_
#define _OLESERDOC_H_

class CNAVOOleServerDoc;

class CNAVOSrvrItem : public CDocObjectServerItem
{
public:
	CNAVOSrvrItem(CNAVOOleServerDoc* pContainerDoc);

	//{{AFX_VIRTUAL(CNAVOSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL
	CNAVOOleServerDoc * GetDocument() const
		{ return (CNAVOOleServerDoc*)CDocObjectServerItem::GetDocument(); }
};

class CNAVOOleServerDoc : public COleServerDoc
{
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
};

#else
	#error __FILE__ already included
#endif