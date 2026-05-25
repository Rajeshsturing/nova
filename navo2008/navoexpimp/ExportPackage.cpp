/*
	NAVO Enterprise 2001
	ExportPackage
*/

#include "stdafx.h"
#include "CommonObject.h"
#include "ExportObject.h"
#include "ExportMessage.h"
#include "ExportPackage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExportPackage, CCmdTarget)

CExportPackage::CExportPackage() :
	m_bSaved(false),
	m_eif(eif_xml)
{
	EnableAutomation();
	AfxOleLockApp();
}

CExportPackage::~CExportPackage()
{
#ifdef _DEBUG
	if(!m_bSaved)
	{
		TRACE0("deleting export package which wasn't saved");
		ASSERT(false);
	}
	if(m_poOutputStreamSP.PointsObject())
	{
		CFile oFile("c:\\temp\\export.xml",CFile::modeWrite | CFile::modeCreate);
		CStreamHolder oSH(m_poOutputStreamSP);
		oSH.SeekToBegin();
		SaveStreamToFile(m_poOutputStreamSP,&oFile,false,100000000);
	}
#endif
	if(m_poFileRemoverSP.PointsObject())
	{
		m_poFileRemoverSP->DontRemove();
	}
	AfxOleUnlockApp();
}

void CExportPackage::WritePackageHeader()
{
	ASSERT(m_poOutputStreamSP.PointsObject());
	if(m_eif == eif_xml)
	{
		CStreamHolder oSH(m_poOutputStreamSP);
		oSH.WriteString("<neipckg>\r\n");
	}
	else
	{
		ASSERT(false);	//to_do
	}
}

void CExportPackage::WritePackageFooter()
{
	ASSERT(m_poOutputStreamSP.PointsObject());
	if(m_eif == eif_xml)
	{
		CStreamHolder oSH(m_poOutputStreamSP);
		oSH.WriteString("</neipckg>\r\n");
	}
	else
	{
		ASSERT(false);	//to_do
	}
}

BEGIN_MESSAGE_MAP(CExportPackage, CCmdTarget)
	//{{AFX_MSG_MAP(CExportPackage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CExportPackage, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CExportPackage)
	DISP_FUNCTION(CExportPackage, "newmsg", NewMsgAUTO, VT_DISPATCH, VTS_NONE)
	DISP_FUNCTION(CExportPackage, "ostream", SetOutputStreamAUTO, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CExportPackage, "save", SaveAUTO, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IExportPackage to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B604E7DE-C3A7-4ABF-9E11-71234D2019F2}
static const IID IID_IExportPackage =
{ 0xb604e7de, 0xc3a7, 0x4abf, { 0x9e, 0x11, 0x71, 0x23, 0x4d, 0x20, 0x19, 0xf2 } };

BEGIN_INTERFACE_MAP(CExportPackage, CCmdTarget)
	INTERFACE_PART(CExportPackage, IID_IExportPackage, Dispatch)
END_INTERFACE_MAP()

// {188cb171-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CExportPackage, "navoexpimp.ExportPackage", 0x188cb171,0x82a4,0x4498,0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

/////////////////////////////////////////////////////////////////////////////
// CExportPackage message handlers

LPDISPATCH CExportPackage::NewMsgAUTO() 
{
	ALL_TRY
	{
		if(m_bSaved)
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
		}
		//musi byæ podany stream
		if(m_poOutputStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_MUST_SET_STREAM_FIRST,IDPAGE_NOTAVAILABLE);
		}
		SCP<CExportMessage>	poExportMessageSP = NewSCP(new CExportMessage(m_eif,m_poOutputStreamSP));
		return poExportMessageSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CExportPackage::SetOutputStreamAUTO(const VARIANT FAR& varOStream) 
{
	ALL_TRY
	{
		if(m_bSaved)
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
		}
		CSmartOleVariant oSOV(varOStream);
		
		m_poOutputStreamSP = CreateFileStream_Write_On_SOV(oSOV,m_poFileRemoverSP);
		ASSERT(m_poOutputStreamSP.PointsObject());
		WritePackageHeader();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CExportPackage::SaveAUTO() 
{
	ALL_TRY
	{
		if(m_bSaved)
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
		}
		if(m_poOutputStreamSP.PointsNull())
		{
			ThrowNavoException(ERCO_EXPIMP_PCKG_MUST_SET_STREAM_FIRST,IDPAGE_NOTAVAILABLE);
		}
		WritePackageFooter();
		m_bSaved = true;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
