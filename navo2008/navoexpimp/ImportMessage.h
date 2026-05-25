/*
	NAVO Enterprise 2001
	Import Message
*/

#if !defined(AFX_IMPORTMESSAGE_H__35CAD139_A3F2_497C_B069_FCDE8BB78E11__INCLUDED_)
#define AFX_IMPORTMESSAGE_H__35CAD139_A3F2_497C_B069_FCDE8BB78E11__INCLUDED_

class CImportObject;

class CMappingInfo : public CInterface__
{
public:
	CMappingInfo();
	~CMappingInfo();

	long get_destidobj() const;
	void set_destidobj(long nDestIdObj);
	long get_all(long & rnParentTypeId,long & rnSrcParentIdObj,CString & roListFldString,long & rnListLP) const;
	void set_all(long nDestIdObj,long nParentTypeId,long nSrcParentIdObj,const CString & roListFldString,long nListLP);
private:
	long m_nDestIdObj;			//translated idobj
	long m_nParentTypeId;		//for children: parent typeid
	long m_nSrcParentIdObj;		//for children: original parent idobj
	CString m_oListFieldString; //for children: <list> field name in parent
	long m_nListLP;				//for children: position of this object in original <list>
};

class CImportMessage : public CCmdTargetInterface
{
public:
	CImportMessage();
	//{{AFX_VIRTUAL(CImportMessage)
	//}}AFX_VIRTUAL
	void SetHeader(SCP<CImportObject> & rpoImportObjectSP);
protected:
	virtual ~CImportMessage();
	//{{AFX_MSG(CImportMessage)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CImportMessage)
	afx_msg long GetMapidAUTO(long nTypeId, long nOldIdObj);
	afx_msg void SetMapidAUTO(long nTypeId, long nOldIdObj, long nNewValue);
	afx_msg void SetMapidExAUTO(long nTypeId,long nOldIdObj,long nDestIdObj,long nParentTypeId,long nSrcParentIdObj,LPCTSTR lpListFld,long nListLP);
	afx_msg long GetMapidExAUTO(long nTypeId,long nOldIdObj,VARIANT * pnParentTypeId,VARIANT * pnSrcParentIdObj,VARIANT * plpListFld,VARIANT * pnListLP);
	afx_msg LPDISPATCH GetHeaderAUTO();
	afx_msg void SetHeaderAUTO(LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CMap<hyper,hyper, SCP<CMappingInfo>, SCP<CMappingInfo> >	m_oObjectMap;	//key - (typeid,oldidobj), value= new idobj
	SCP<CImportObject>	m_poHeaderImportObjectSP;
};

/////////////////////////////////////////////////////////////////////////////
inline CMappingInfo::CMappingInfo() :
	m_nDestIdObj(0),
	m_nParentTypeId(0),
	m_nSrcParentIdObj(0),
	m_nListLP(-1)
{
}

inline CMappingInfo::~CMappingInfo()
{
}

inline long CMappingInfo::get_destidobj() const
{
	ASSERT(m_nDestIdObj != 0);
	return m_nDestIdObj;
}

inline long CMappingInfo::get_all(long & rnParentTypeId,long & rnSrcParentIdObj,
	CString & roListFldString,long & rnListLP) const
{
	ASSERT(m_nParentTypeId != 0);

	rnParentTypeId = m_nParentTypeId;
	rnSrcParentIdObj = m_nSrcParentIdObj;
	roListFldString = m_oListFieldString;
	rnListLP = m_nListLP;

	ASSERT(m_nDestIdObj != 0);
	return m_nDestIdObj;
}

inline void CMappingInfo::set_destidobj(long nDestIdObj)
{
	ASSERT(nDestIdObj != 0);
	m_nDestIdObj = nDestIdObj;
}

inline void CMappingInfo::set_all(long nDestIdObj,long nParentTypeId,long nSrcParentIdObj,const CString & roListFldString,long nListLP)
{
	ASSERT(nDestIdObj != 0);
	m_nDestIdObj = nDestIdObj;
	m_nParentTypeId = nParentTypeId;
	m_nSrcParentIdObj = nSrcParentIdObj;
	m_oListFieldString = roListFldString;
	m_nListLP = nListLP;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTMESSAGE_H__35CAD139_A3F2_497C_B069_FCDE8BB78E11__INCLUDED_)
