/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CHyperSetAutoObject implementuje zbiory par liczb long (x,y) dostêpne
		przez automation
*/

#ifndef _HYPERSETAUTO_H_
#define _HYPERSETAUTO_H_

typedef bool mapvalue;
typedef hyper mapkey;

class CHyperSetAutoObject : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CHyperSetAutoObject)
	CHyperSetAutoObject();
public:
	static SCP<CHyperSetAutoObject> FromIDispatch(LPDISPATCH lpDispatch);

	//{{AFX_VIRTUAL(CHyperSetAutoObject)
virtual void OnFinalRelease();
	//}}AFX_VIRTUAL
protected:
	virtual ~CHyperSetAutoObject();

	//{{AFX_MSG(CHyperSetAutoObject)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CHyperSetAutoObject)

	//{{AFX_DISPATCH(CHyperSetAutoObject)
	afx_msg BOOL ExistsAUTO(long TypeId,long IdObj);
	afx_msg void AddAUTO(long TypeId,long IdObj);
	afx_msg void RemoveAuto(long TypeId,long ldObj);
	afx_msg LPDISPATCH OrAUTO(LPDISPATCH hyperset);
	afx_msg LPDISPATCH AndAUTO(LPDISPATCH hyperset);
	afx_msg LPDISPATCH MinusAUTO(LPDISPATCH hyperset);
	afx_msg BOOL IsEmptyAUTO();
	afx_msg void EmptyAUTO();
	afx_msg void ExtractAUTO(CURRENCY hyperValue, VARIANT FAR* nHiPart, VARIANT FAR* nLoPart);
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	void __raw_copy(const CHyperSetAutoObject & roHSAO);
	void __copy(const CHyperSetAutoObject & roHSAO);
	void __and(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2);
	void __or(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2);
	void __minus(const CHyperSetAutoObject & roHSAO1,const CHyperSetAutoObject & roHSAO2);
	void __add(long TypeId,long IdObj);
	void __remove(long TypeId,long IdObj);
	void __empty();
	bool __exists(long TypeId,long IdObj) const;
	bool __isempty() const;

	CMap<mapkey,mapkey,mapvalue,mapvalue>		m_oItemMap;	//mapvalue - placeholder
};

/////////////////////////////////////////////////////////////////////////////

#else
	#error __FILE__ already included
#endif
