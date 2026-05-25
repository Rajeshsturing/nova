/*
	NAVO Enterprise 2001
	Import Object
*/

#if !defined(AFX_IMPORTOBJECT_H__6471B279_8947_43AB_9819_159B6D51421A__INCLUDED_)
#define AFX_IMPORTOBJECT_H__6471B279_8947_43AB_9819_159B6D51421A__INCLUDED_

class CImportMessage;
class CImportObject : public CCommonObject
{
public:
	CImportObject(CImportMessage * poImportMessage);
	
	//{{AFX_VIRTUAL(CImportObject)
	//}}AFX_VIRTUAL

	void SetTypeId(long nTypeId)
	{
		m_nTypeId = nTypeId;
	}
	void SetIdObj(long nIdObj)
	{
		m_nIdObj = nIdObj;
	}
protected:
	virtual ~CImportObject();
	//{{AFX_MSG(CImportObject)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CImportObject)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CImportMessage * m_poImportMessage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTOBJECT_H__6471B279_8947_43AB_9819_159B6D51421A__INCLUDED_)
