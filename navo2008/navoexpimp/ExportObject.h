/*
	NAVO Enterprise 2001
	Export Object
*/

#if !defined(AFX_EXPORTOBJECT_H__98D92474_EAEB_4DAD_AD34_2816225D3791__INCLUDED_)
#define AFX_EXPORTOBJECT_H__98D92474_EAEB_4DAD_AD34_2816225D3791__INCLUDED_

class CExportMessage;
class CExportObject : public CCommonObject
{
public:
	CExportObject(CExportMessage * poExportMessage,long TypeId,long IdObj);
	//{{AFX_VIRTUAL(CExportObject)
	//}}AFX_VIRTUAL

	virtual ~CExportObject();
	//{{AFX_MSG(CExportObject)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:

	//{{AFX_DISPATCH(CExportObject)
	afx_msg void SaveAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CExportMessage * m_poExportMessage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTOBJECT_H__98D92474_EAEB_4DAD_AD34_2816225D3791__INCLUDED_)
