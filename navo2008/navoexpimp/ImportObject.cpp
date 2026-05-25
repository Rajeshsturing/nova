/*
	NAVO Enterprise 2001
	Import Object
*/

#include "stdafx.h"
#include "CommonObject.h"
#include "ImportObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImportObject::CImportObject(CImportMessage * poImportMessage) :
	CCommonObject(0,0),
	m_poImportMessage(poImportMessage)
{
	EnableAutomation();
}

CImportObject::~CImportObject()
{
}

BEGIN_MESSAGE_MAP(CImportObject, CCommonObject)
	//{{AFX_MSG_MAP(CImportObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImportObject, CCommonObject)
	//{{AFX_DISPATCH_MAP(CImportObject)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IImportObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {9071B514-E4D2-4C55-8686-8CD3D4703BBB}
static const IID IID_IImportObject =
{ 0x9071b514, 0xe4d2, 0x4c55, { 0x86, 0x86, 0x8c, 0xd3, 0xd4, 0x70, 0x3b, 0xbb } };

BEGIN_INTERFACE_MAP(CImportObject, CCommonObject)
	INTERFACE_PART(CImportObject, IID_IImportObject, Dispatch)
END_INTERFACE_MAP()
