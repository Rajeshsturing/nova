/*
	NAVO Enterprise 2001
	Export Object
*/

#include "stdafx.h"
#include "CommonObject.h"
#include "ExportObject.h"
#include "ExportMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportObject::CExportObject(CExportMessage * poExportMessage,long TypeId,long IdObj) :
	CCommonObject(TypeId,IdObj),
	m_poExportMessage(poExportMessage)
{
	EnableAutomation();
}

CExportObject::~CExportObject()
{
}

BEGIN_MESSAGE_MAP(CExportObject, CCommonObject)
	//{{AFX_MSG_MAP(CExportObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CExportObject, CCommonObject)
	//{{AFX_DISPATCH_MAP(CExportObject)
	DISP_FUNCTION(CExportObject, "save", SaveAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IExportObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {6531C34A-8C52-4AA9-978B-CAAB7137D3F2}
static const IID IID_IExportObject =
{ 0x6531c34a, 0x8c52, 0x4aa9, { 0x97, 0x8b, 0xca, 0xab, 0x71, 0x37, 0xd3, 0xf2 } };

BEGIN_INTERFACE_MAP(CExportObject, CCommonObject)
	INTERFACE_PART(CExportObject, IID_IExportObject, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportObject message handlers


void CExportObject::SaveAUTO() 
{
	ALL_TRY
	{
		ASSERT(m_poExportMessage);
		m_poExportMessage->OnSaveObject(this);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
