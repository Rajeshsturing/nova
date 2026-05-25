/*
	NAVO Enterprise 2001
	Export Message
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "CommonObject.h"
#include "ExportObject.h"
#include "ExportMessage.h"
#include "ImportObject.h"
#include "ImportMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportMessage::CExportMessage(ExportImportFormat eif,SCP<IStream> & rpoOutputStreamSP) :
	m_eif(eif),
	m_poOutputStreamSP(rpoOutputStreamSP),
	m_bSaved(false)
{
	WriteMsgHeader();
	InitHeader();
	EnableAutomation();
}

CExportMessage::~CExportMessage()
{
#ifdef _DEBUG
	if(!m_bSaved)
	{
		TRACE0("deleting export message which wasn't saved");
		ASSERT(false);
	}
#endif
}

void CExportMessage::InitHeader()
{
	m_poHeaderExportObjectSP = GetNewObj(TYPEID_EXPIMPMSGHEADER,1);
}

bool CExportMessage::WasObject(long nType, long nIdObj)
{
	bool bSaved;
	return m_oObjectMap.Lookup(longlong(nType,nIdObj),bSaved) != FALSE;
}

SCP<CExportObject> CExportMessage::GetNewObj(long nType, long nIdObj)
{
	if(WasObject(nType,nIdObj))
	{
		ThrowNavoException2(ERCO_EXPIMP_OBJECT_ALREADY_CRTD,IDPAGE_NOTAVAILABLE,nType,nIdObj);
	}
	SCP<CExportObject> poExportObjectSP = NewSCP(new CExportObject(this,nType,nIdObj));
	m_oObjectMap[ longlong(nType,nIdObj) ] = false;
	return poExportObjectSP;
}

void CExportMessage::OnSaveObject(CExportObject * poExportObject)
{
	ASSERT(poExportObject);
	long nType = poExportObject->GetTypeidAUTO();
	long nIdObj= poExportObject->GetIdobjAUTO();
	bool bSaved;
	VERIFY(m_oObjectMap.Lookup(longlong(nType,nIdObj),bSaved));		//must exists
	if(bSaved)
	{
		ThrowNavoException2(ERCO_EXPIMP_OBJECT_ALREADY_SAVED,IDPAGE_NOTAVAILABLE,nType,nIdObj);
	}
	poExportObject->Write(m_eif,m_poOutputStreamSP);
	m_oObjectMap[ longlong(nType,nIdObj) ] = true;
}

void CExportMessage::WriteMsgHeader()
{
	ASSERT(m_poOutputStreamSP.PointsObject());
	if(m_eif == eif_xml)
	{
		CStreamHolder oSH(m_poOutputStreamSP);
		oSH.WriteString("\t<neimsg>\r\n");
	}
	else
	{
		ASSERT(false);	//to_do
	}
}

void CExportMessage::WriteMsgFooter()
{
	ASSERT(m_poOutputStreamSP.PointsObject());
	if(m_eif == eif_xml)
	{
		CStreamHolder oSH(m_poOutputStreamSP);
		oSH.WriteString("\t</neimsg>\r\n");
	}
	else
	{
		ASSERT(false);	//to_do
	}
}


BEGIN_MESSAGE_MAP(CExportMessage, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CExportMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CExportMessage, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CExportMessage)
	DISP_PROPERTY_EX(CExportMessage, "header", GetHeaderAUTO, SetHeaderAUTO, VT_DISPATCH)
	DISP_FUNCTION(CExportMessage, "newobj", GetNewObjAUTO, VT_DISPATCH, VTS_I4 VTS_I4)
	DISP_FUNCTION(CExportMessage, "wasobj", WasObjAUTO, VT_BOOL, VTS_I4 VTS_I4)
	DISP_FUNCTION(CExportMessage, "save", SaveAUTO, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CExportMessage, "importmessage", CloneToImportMessageAUTO, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IExportMessage to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {DAD0441C-EB20-4318-A6AE-96B0A84E6A06}
static const IID IID_IExportMessage =
{ 0xdad0441c, 0xeb20, 0x4318, { 0xa6, 0xae, 0x96, 0xb0, 0xa8, 0x4e, 0x6a, 0x6 } };

BEGIN_INTERFACE_MAP(CExportMessage, CCmdTargetInterface)
	INTERFACE_PART(CExportMessage, IID_IExportMessage, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportMessage message handlers

LPDISPATCH CExportMessage::GetNewObjAUTO(long nType, long nIdObj) 
{
	ALL_TRY
	{
		if(m_bSaved)
		{
			ThrowNavoException(ERCO_EXPIMP_MSG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
		}
		return GetNewObj(nType,nIdObj)->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

LPDISPATCH CExportMessage::GetHeaderAUTO() 
{
	ALL_TRY
	{
		if(m_bSaved)
		{
			ThrowNavoException(ERCO_EXPIMP_MSG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
		}
		ASSERT(m_poHeaderExportObjectSP.PointsObject());
		return m_poHeaderExportObjectSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CExportMessage::SetHeaderAUTO(LPDISPATCH) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"header","exportmsg");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CExportMessage::WasObjAUTO(long nType, long nIdObj) 
{
	ALL_TRY
	{
		return WasObject(nType,nIdObj) != FALSE;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CExportMessage::SaveAUTO() 
{
	if(m_bSaved)
	{
		ThrowNavoException(ERCO_EXPIMP_MSG_ALREADY_SAVED,IDPAGE_NOTAVAILABLE);
	}
	//save header if neccessary
	bool bSavedHeader;
	VERIFY(m_oObjectMap.Lookup(longlong(TYPEID_EXPIMPMSGHEADER,1),bSavedHeader));		//must exists
	if(!bSavedHeader)
	{
		m_poHeaderExportObjectSP->SaveAUTO();
	}
	//check for unsaved objects - all must be saved at this moment
	POSITION pos = m_oObjectMap.GetStartPosition();
	while(pos)
	{
		hyper hyperkey;
		bool bState;
		m_oObjectMap.GetNextAssoc(pos, hyperkey, bState);
		if(!bState)
		{
			ThrowNavoException2(ERCO_EXPIMP_MSG_SAVING_WITH_UNSAVED_OBJS,IDPAGE_NOTAVAILABLE,
				hihyper(hyperkey),lohyper(hyperkey));
		}
	}
	WriteMsgFooter();
	m_bSaved = true;
}

LPDISPATCH CExportMessage::CloneToImportMessageAUTO()
{
	ALL_TRY
	{
		SCP<CImportMessage> poImportMessageSP = NewSCP(new CImportMessage());
		CCommonObject * poHeaderCommonObject = (CCommonObject*)(m_poHeaderExportObjectSP.Get());
		SCP<CImportObject> poHeaderImportObjecTSP = 
			NewSCP<CImportObject>(reinterpret_cast<CImportObject*>(poHeaderCommonObject),true);
		poImportMessageSP->SetHeader(poHeaderImportObjecTSP);

		return poImportMessageSP->GetDispatch(true);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

