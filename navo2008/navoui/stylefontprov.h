/*
	NAVO Enterprise (2001)
	
	Style and Font provider

	This object analyzes, manages and provides "style" and font information
	to the UIElements created by various parsers
*/

#ifndef _STYLEFONTPROV_H_
#define _STYLEFONTPROV_H_

class CUIAttributes;
interface IStreamProvider;

/*
	element stylu, bazuje na UIAttributes, jest AUTOMATION
*/

class CStyleItem : public CCmdTargetInterface, public CUIAttributes
{
public:
	CStyleItem();
	CStyleItem(const CStyleItem & roStyleItem);
	virtual void operator = (const CStyleItem & roStyleItem);
};

class CStyleDefinition : public CCmdTargetInterface
{
public:
	CStyleDefinition(long IdStyle) :
	  m_IdStyle(IdStyle)
	{
		EnableAutomation();
	}
	void GetElementOnId(long IdElement,SCP<CStyleItem> & rpoStyleItemSP);

	void AddItem(SCP<CStyleItem> & rpoStyleItemSP)
	{
		ASSERT(rpoStyleItemSP->GetStyleItemId() != -1);
		m_oItemMap[ rpoStyleItemSP->GetStyleItemId() ] = rpoStyleItemSP;
	}
	long GetStyleId() const
	{
		return m_IdStyle;
	}
	void SetName(LPCTSTR lpStyleName)
	{
		m_oNameString = lpStyleName;
	}
	LPCTSTR GetName() const
	{
		return m_oNameString;
	}
	//{{AFX_MSG(CStyleDefinition)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CStyleDefinition)
	afx_msg LPDISPATCH GetItemAUTO(long IdElement);
	afx_msg BSTR GetNameAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	CString m_oNameString;
	long m_IdStyle;
	CMap<long,long,SCP<CStyleItem>,SCP<CStyleItem> &>	m_oItemMap;
};

class CStyleAndFontProvider : public CCmdTargetInterface
{
public:
	CStyleAndFontProvider();

	SCP<IFont>	GetFontFromStyleItem(SCP<CStyleItem> & rpoStyleItemSP);

	long GetFontInxOnSpec(LPCTSTR lpFontName,long nSize,bool bBold,bool bItalic,bool bStrikeThrough);
	void GetFontSpecOnInx(long nInx,CString & roFontNameString,long & rnSize,
		bool & rbBold,bool & rbItalic,bool & rbStrikeThrough);
	SCP<IFont>	GetFontOnInx(long nInx);

	long GetCurrentStyle() const
	{
		return m_nCurrentDefaultStyle;
	}
	void SetCurrentStyle(long nCurrentDefaultStyle)
	{
		m_nCurrentDefaultStyle = nCurrentDefaultStyle;
	}

	SCP<CStyleDefinition> GetStyle(long IdStyle);
	void SetStyle(long IdStyle,SCP<CStyleDefinition> & rpoStyleDefinitionSP)
	{
		m_oStyleMap[ IdStyle ] = rpoStyleDefinitionSP;
	}

	//{{AFX_MSG(CStyleAndFontProvider)
	//}}AFX_MSG
	//{{AFX_DISPATCH(CStyleAndFontProvider)
	afx_msg LPDISPATCH GetStyleAUTO(long IdStyle);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	SCP<IFont>	CreateFontOnDescription(LPCTSTR lpFontName,long nSize,bool bBold,bool bItalic,bool bStrikeThrough);
	
	
	CMap<long,long,SCP<CStyleDefinition>,SCP<CStyleDefinition> &> m_oStyleMap;

	
	//mapa opisów fontów (jako string) -> indeks fontu
	CMap<CString,LPCTSTR,long,long &> m_oFontInxMap;

	long m_nCurrentDefaultStyle;

	struct FontWithDescription
	{
		FontWithDescription()
		{
		}
		FontWithDescription(SCP<IFont> poFontSP, const CString & roFontDescString) :
			m_poFontSP(poFontSP),
			m_oFontDescriptionString(roFontDescString)
		{
		}
		SCP<IFont>	m_poFontSP;
		CString		m_oFontDescriptionString;
	};
	//tablica opisów fontów i IFont * (OLE implementacji fontu)
	CArray<FontWithDescription,FontWithDescription &> m_oFontWithDescArray;
};

#else
	#error __FILE__ already included
#endif
