/*
	NAVO Enterprise 2001
	Common Export/Import base Object
*/

#ifndef _COMMONOBJECT_H_
#define _COMMONOBJECT_H_

enum ExportImportFormat
{
	eif_xml,
	eif_flat
};

class CCommonObject : public CCmdTargetInterface
{
protected:
	CCommonObject(long TypeId,long IdObj) :
		m_nTypeId(TypeId),
		m_nIdObj(IdObj)
	{
	}
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
public:
	bool IsField(LPCTSTR lpFieldName);
	void SetField(LPCTSTR lpFieldName,const CSmartOleVariant & roSOV);
	void GetField(LPCTSTR lpFieldName,CSmartOleVariant & roSOV);

	void Write(ExportImportFormat eif,SCP<IStream> & rpoOutputStreamSP);
	//{{AFX_VIRTUAL(CCommonObject)
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CCommonObject)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CCommonObject)
	afx_msg long GetTypeidAUTO();
	afx_msg void SetTypeidAUTO(long nNewValue);
	afx_msg long GetIdobjAUTO();
	afx_msg void SetIdobjAUTO(long nNewValue);
	afx_msg VARIANT GetFieldAUTO(LPCTSTR lpName);
	afx_msg void SetFieldAUTO(LPCTSTR lpName, const VARIANT FAR& newValue);
	afx_msg BOOL IsFieldAUTO(LPCTSTR lpName);
	//}}AFX_DISPATCH

protected:
	long	m_nTypeId;
	long	m_nIdObj;
private:
	CMap<CString,LPCTSTR,CSmartOleVariant,CSmartOleVariant &> m_oFieldMap;
};

#else
	#error __FILE__ already included
#endif
