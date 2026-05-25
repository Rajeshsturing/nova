#pragma once

// CNAVOBRMPpg.h : Declaration of the CCNAVOBRMPropPage property page class.


// CCNAVOBRMPropPage : See CNAVOBRMPpg.cpp for implementation.

class CCNAVOBRMPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCNAVOBRMPropPage)
	DECLARE_OLECREATE_EX(CCNAVOBRMPropPage)

// Constructor
public:
	CCNAVOBRMPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_NAVOBRMCTRL2008 };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

