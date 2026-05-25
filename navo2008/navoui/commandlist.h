/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCommandList - obiekt AUTO do tworzenia listy poleceñ np. prawy klawisz menu
*/

#ifndef _COMMANDLIST_H_
#define _COMMANDLIST_H_

/////////////////////////////////////////////////////////////////////////////
// CCommandList command target

class CCommandList : public CCmdTargetInterface
{
public:
	CCommandList();           // protected constructor used by dynamic creation
	virtual ~CCommandList();

	void AddCommand(LPCTSTR lpText,SCP<CHyperLinkInfo> poHLISP);
	void AddSeparator();
	void AddSubMenu(LPCTSTR lpText);
	void EndSubMenu();
	bool IsEmpty() const
	{
		return m_oCommandArray.GetSize() == 0;
	}
	
	SCP<CHyperLinkInfo> Show(CPoint PtScreenPos,HWND hWnd);
	//{{AFX_VIRTUAL(CCommandList)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CCommandList)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CCommandList)
	afx_msg void AddCommandAUTO(LPCTSTR lpText, const VARIANT FAR& pHLI);
	afx_msg void AddSeparatorAUTO();
	afx_msg void AddSubMenuAUTO(LPCTSTR lpText);
	afx_msg void EndSubMenuAUTO();
	afx_msg BOOL IsEmptyAUTO();
	afx_msg BOOL GetCommandAUTO(long nItem, VARIANT * lpType, VARIANT * lpText, VARIANT * lpHLI);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	struct CCommandItem
	{
		enum eCIType
		{
			CIT_ITEM,
			CIT_SEPARATOR,
			CIT_SUBMENU,
			CIT_ENDSUB
		};
		CCommandItem(const CCommandItem & roCommandItem) :
			m_eCIT(roCommandItem.m_eCIT),
			m_oTextString(roCommandItem.m_oTextString),
			m_poHLISP(NewSCP(m_poHLISP.ConstCastObject(),true))
		{
		}
		CCommandItem(eCIType eCIT = CIT_ITEM,LPCTSTR lpText = NULL,
			SCP<CHyperLinkInfo> poHLISP = SCP<CHyperLinkInfo>()) :
			m_eCIT(eCIT),
			m_oTextString(lpText),
			m_poHLISP(poHLISP)
		{
		}
		
		eCIType m_eCIT;
		CString m_oTextString;
		SCP<CHyperLinkInfo> m_poHLISP;
	};
	CArray<CCommandItem,CCommandItem &> m_oCommandArray;
};

#else
	#error __FILE__ already included
#endif
