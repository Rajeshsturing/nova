/*
	NAVO Enterprise 2001
	Import Message
*/

#include "stdafx.h"
#include "CommonObject.h"
#include "ImportObject.h"
#include "ImportMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImportMessage::CImportMessage()
{
	EnableAutomation();
}

CImportMessage::~CImportMessage()
{
}

void CImportMessage::SetHeader(SCP<CImportObject> & rpoImportObjectSP)
{
	ASSERT(m_poHeaderImportObjectSP.PointsNull());
	m_poHeaderImportObjectSP = rpoImportObjectSP;
}

BEGIN_MESSAGE_MAP(CImportMessage, CCmdTargetInterface)
	//{{AFX_MSG_MAP(CImportMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImportMessage, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CImportMessage)
	DISP_PROPERTY_EX(CImportMessage, "header", GetHeaderAUTO, SetHeaderAUTO, VT_DISPATCH)
	DISP_PROPERTY_PARAM(CImportMessage, "mapid", GetMapidAUTO, SetMapidAUTO, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CImportMessage, "setmapidex", SetMapidExAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4)
	DISP_FUNCTION(CImportMessage, "getmapidex", GetMapidExAUTO, VT_I4, VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IImportMessage to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {D053D40F-21B9-4A96-AC23-2CCB0F7E0036}
static const IID IID_IImportMessage =
{ 0xd053d40f, 0x21b9, 0x4a96, { 0xac, 0x23, 0x2c, 0xcb, 0xf, 0x7e, 0x0, 0x36 } };

BEGIN_INTERFACE_MAP(CImportMessage, CCmdTargetInterface)
	INTERFACE_PART(CImportMessage, IID_IImportMessage, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportMessage message handlers

long CImportMessage::GetMapidAUTO(long nTypeId, long nOldIdObj) 
{
	ALL_TRY
	{
		hyper hyperKey = longlong(nTypeId,nOldIdObj);

		SCP<CMappingInfo> poMapInfoSP;
		if(m_oObjectMap.Lookup(hyperKey,poMapInfoSP))
		{
			return poMapInfoSP->get_destidobj();
		}
		else
		{
			return 0;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CImportMessage::SetMapidAUTO(long nTypeId, long nOldIdObj, long nNewValue) 
{
	ALL_TRY
	{
		if(nNewValue <= 0)
		{
			ThrowNavoException3(ERCO_EXPIMP_PCKG_NEWID_MUST_BE_POSITIVE,IDPAGE_NOTAVAILABLE,
				nTypeId,nOldIdObj,nNewValue);
		}

		hyper hyperKey = longlong(nTypeId,nOldIdObj);
		SCP<CMappingInfo> poMapInfoSP;
		if(m_oObjectMap.Lookup(hyperKey,poMapInfoSP))
		{
			ThrowNavoException3(ERCO_EXPIMP_PCKG_ID_ALREADY_MAPPED,IDPAGE_NOTAVAILABLE,
				nTypeId,nOldIdObj,poMapInfoSP->get_destidobj());
		}
		poMapInfoSP = NewSCP(new CMappingInfo(),false);
		poMapInfoSP->set_destidobj(nNewValue);
		m_oObjectMap[ hyperKey ] = poMapInfoSP;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

void CImportMessage::SetMapidExAUTO(long nTypeId,long nOldIdObj,long nDestIdObj,long nParentTypeId,long nSrcParentIdObj,LPCTSTR lpListFld,long nListLP)
{
	ALL_TRY
	{
		if(nDestIdObj <= 0)
		{
			ThrowNavoException3(ERCO_EXPIMP_PCKG_NEWID_MUST_BE_POSITIVE,IDPAGE_NOTAVAILABLE,
				nTypeId,nOldIdObj,nDestIdObj);
		}

		hyper hyperKey = longlong(nTypeId,nOldIdObj);
		SCP<CMappingInfo> poMapInfoSP;
		if(m_oObjectMap.Lookup(hyperKey,poMapInfoSP))
		{
			ThrowNavoException3(ERCO_EXPIMP_PCKG_ID_ALREADY_MAPPED,IDPAGE_NOTAVAILABLE,
				nTypeId,nOldIdObj,poMapInfoSP->get_destidobj());
		}
		poMapInfoSP = NewSCP(new CMappingInfo(),false);
		poMapInfoSP->set_all(nDestIdObj,nParentTypeId,nSrcParentIdObj,lpListFld,nListLP);
		m_oObjectMap[ hyperKey ] = poMapInfoSP;
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CImportMessage::GetMapidExAUTO(long nTypeId,long nOldIdObj,VARIANT * pnParentTypeId,VARIANT * pnSrcParentIdObj,VARIANT * plpListFld,VARIANT * pnListLP)
{
	ALL_TRY
	{
		hyper hyperKey = longlong(nTypeId,nOldIdObj);

		SCP<CMappingInfo> poMapInfoSP;
		if(m_oObjectMap.Lookup(hyperKey,poMapInfoSP))
		{
			//
			long nParentTypeId;
			long nSrcParentIdObj;
			CString oListFldString;
			long nListLP;

			long idDestObj = poMapInfoSP->get_all(nParentTypeId,nSrcParentIdObj,oListFldString,nListLP);
			* pnParentTypeId = CSmartOleVariant(nParentTypeId,VT_I4).Detach();
			* pnSrcParentIdObj= CSmartOleVariant(nSrcParentIdObj,VT_I4).Detach();
			* plpListFld = CSmartOleVariant(oListFldString).Detach();
			* pnListLP = CSmartOleVariant(nListLP,VT_I4).Detach();

			return idDestObj;
		}
		else
		{
			return 0;
		}
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

LPDISPATCH CImportMessage::GetHeaderAUTO() 
{
	ALL_TRY
	{
		ASSERT(m_poHeaderImportObjectSP.PointsObject());
		return m_poHeaderImportObjectSP->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CImportMessage::SetHeaderAUTO(LPDISPATCH) 
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"header","importmsg");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
