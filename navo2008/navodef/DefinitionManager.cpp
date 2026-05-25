/*
NAVO Sp. z o.o. (2001)

NAVO Enterprise

CDefinitionManager - definition manager
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\InterfaceUtil.h"
#include "stdobjdef.h"
#include "DefinitionManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif

#ifdef _DEBUG
#ifdef _NAVODOTNET
//-- nothing here -- 
#else
#if defined(NAVO2008)
//-- nothing here
#else
#include <fstream.h>
#include <iomanip.h>
#endif
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CDefinitionManager

IMPLEMENT_DYNCREATE(CDefinitionManager, CCmdTarget)

CDefinitionManager::CDefinitionManager()
{
	EnableAutomation();
	AfxOleLockApp();
}

CDefinitionManager::~CDefinitionManager()
{
	AfxOleUnlockApp();
}

void CDefinitionManager::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDefinitionManager, CCmdTargetWithErrorInfo)
	//{{AFX_MSG_MAP(CDefinitionManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDefinitionManager, CCmdTargetWithErrorInfo)
	//{{AFX_DISPATCH_MAP(CDefinitionManager)
	DISP_FUNCTION(CDefinitionManager, "getobjdef", GetStdObjDefAUTO, VT_DISPATCH, VTS_I4)
	DISP_PROPERTY_EX_ID(CDefinitionManager, "_NewEnum", DISPID_NEWENUM, GetNewEnumAUTO, SetNewEnumAUTO, VT_UNKNOWN)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//------------------------------------------------------------------
void CDefinitionManager::QuasiDtor()
{
	SetDOC_Dispatch( SCP<IDispatch>() );
	SetNX_Dispatch( SCP<IDispatch>() );
	
	POSITION pos = m_oStdObjDefMap.GetStartPosition();
	while(pos)
	{
		long nTypeId;
		SCP<CStdObjDef> poStdObjDefSP;
		m_oStdObjDefMap.GetNextAssoc(pos,nTypeId,poStdObjDefSP);
		poStdObjDefSP->QuasiDtor();
	}
	m_oStdObjDefMap.RemoveAll();
}

void CDefinitionManager::InitializeFrom(IStream * pDataStream)
{
	COleStreamFile oOleStreamFile(pDataStream);
	CArchive oArchive(&oOleStreamFile,CArchive::load);
	ReadFromArchive(oArchive);
}

const BYTE cbVersionMarker = '9';

void CDefinitionManager::WriteToArchive(CArchive & roArchive)
{
	roArchive << cbVersionMarker << (long) m_oStdObjDefMap.GetCount();
	POSITION pos = m_oStdObjDefMap.GetStartPosition();
	while(pos)
	{
		long nTypeId;
		SCP<CStdObjDef> poStdObjDefSP;
		m_oStdObjDefMap.GetNextAssoc(pos,nTypeId,poStdObjDefSP);
		ASSERT(poStdObjDefSP->m_nTypeId == nTypeId);
		roArchive << nTypeId;
		poStdObjDefSP->WriteToArchive(roArchive);
	}
}

void CDefinitionManager::ReadFromArchive(CArchive & roArchive)
{
	BYTE byteVersion;
	roArchive >> byteVersion;
	if(byteVersion != cbVersionMarker)
	{
		//incorrect version
		ThrowNavoException(ERCO_DEFMAN_INVALID_ARCHIVE_VERSION,IDPAGE_NOTAVAILABLE);
	}
	long nCount;
	roArchive >> nCount;
	while(nCount--)
	{
		long nTypeId;
		roArchive >> nTypeId;
		SCP<CStdObjDef> poStdObjDefSP = NewSCP(new CStdObjDef(GetErrorStorage()));
		poStdObjDefSP->ReadFromArchive(roArchive);
		poStdObjDefSP->__attach(this,nTypeId);
		m_oStdObjDefMap[ nTypeId ] = poStdObjDefSP;
	}
}

SCP<CStdObjDef> CDefinitionManager::GetStdObjDef(long nTypeId)
{
	SCP<CStdObjDef> poStdObjDefSP;

	{
		CSimpleLock oSimpleLock(m_oStdObjDefCS);
		if(!m_oStdObjDefMap.Lookup(nTypeId,poStdObjDefSP))
		{
			ThrowNavoException1(ERCO_SOD_UNAVAILABLE,IDPAGE_NOTAVAILABLE,nTypeId);
		}
	}
	ASSERT(poStdObjDefSP->m_nTypeId == nTypeId);
	return poStdObjDefSP;
}

void CDefinitionManager::SaveTo(IStream * pDataStream)
{
	COleStreamFile oOleStreamFile(pDataStream);
	CArchive oArchive(&oOleStreamFile,CArchive::store);
	WriteToArchive(oArchive);
}

SCP<CStdObjDef> CDefinitionManager::NewStdObjDef()
{
	return NewSCP(new CStdObjDef(GetErrorStorage()));
}

void CDefinitionManager::AddStdObjDef(long nTypeId,SCP<CStdObjDef> & rpoStdObjDefSP)
{
	CSimpleLock oSimpleLock(m_oStdObjDefCS);
#ifdef _DEBUG
	SCP<CStdObjDef> poTestStdObjDefSP;
	ASSERT(!m_oStdObjDefMap.Lookup(nTypeId,poTestStdObjDefSP));
#endif
	rpoStdObjDefSP->__attach(this,nTypeId);
	m_oStdObjDefMap[ nTypeId ] = rpoStdObjDefSP;
}

void CDefinitionManager::DeleteStdObjDef(long nTypeId)
{
	CSimpleLock oSimpleLock(m_oStdObjDefCS);

#ifdef _DEBUG
	SCP<CStdObjDef> poStdObjDefSP;
	ASSERT(m_oStdObjDefMap.Lookup(nTypeId,poStdObjDefSP));
	ASSERT(poStdObjDefSP->m_nTypeId == nTypeId);
#endif

	VERIFY(m_oStdObjDefMap.RemoveKey(nTypeId));
}

SCP<ITypeInfo> CDefinitionManager::GetStdObjDefTypeInfo(long /*to_do: nTypeId*/)
{
	//to_do
	return SCP<ITypeInfo>();
}


void CDefinitionManager::CommitStdObjDef()
{
#ifdef _DEBUG
#if !defined(NAVO2008)
	Dump();
#endif
#endif
	/*
	supply parent typeid to child definitions
	*/

	POSITION pos = m_oStdObjDefMap.GetStartPosition();
	while(pos)
	{
		long nTypeId;
		SCP<CStdObjDef> poStdObjDefSP;
		m_oStdObjDefMap.GetNextAssoc(pos,nTypeId,poStdObjDefSP);
		if(poStdObjDefSP->HasAnyList())
		{
			for(long iter = 0; iter < poStdObjDefSP->GetFieldCount(); iter++)
			{
				SCP<CStdObjFieldDef> & rpoFieldDefSP = poStdObjDefSP->GetField(iter);
				if(rpoFieldDefSP->GetRelationType() == RELT_LIST)
				{
					long nChildTypeId = rpoFieldDefSP->GetReferenceTypeId();
					SCP<CStdObjDef> poChildDefSP = GetStdObjDef(nChildTypeId);
					//ASSERT(poChildDefSP->m_nParentTypeId == 0 || poChildDefSP->m_nParentTypeId == nTypeId);
					poChildDefSP->m_nParentTypeId = nTypeId;
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------
//		automation
//----------------------------------------------------------------------------------

LPDISPATCH CDefinitionManager::GetStdObjDefAUTO(long nTypeId) 
{
	ALL_TRY
	{
		return GetStdObjDef(nTypeId)->GetIDispatch(TRUE);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

IMPLEMENT_ARRAYENUMERATOR(SCP<CStdObjDef>)

LPUNKNOWN CDefinitionManager::GetNewEnumAUTO()
{
	ALL_TRY
	{
		SCP< CArrayEnumeratorWithArray< SCP<CStdObjDef> > > poSODNewArrayEnumSP = 
			NewSCP(new CArrayEnumeratorWithArray< SCP<CStdObjDef> >(m_oStdObjDefMap.GetCount()) );
		//fill with items
		long iter = 0;
		POSITION pos = m_oStdObjDefMap.GetStartPosition();
		while(pos)
		{
			long nTypeId;
			SCP<CStdObjDef> poStdObjDefSP;
			m_oStdObjDefMap.GetNextAssoc(pos,nTypeId,poStdObjDefSP);
			ASSERT(poStdObjDefSP.PointsObject());
			ASSERT(poStdObjDefSP->m_nTypeId == nTypeId);
			poSODNewArrayEnumSP->SetAt(iter,poStdObjDefSP);
			iter++;
		}
		ASSERT(iter == m_oStdObjDefMap.GetCount());
		return poSODNewArrayEnumSP->GetEnumVARIANT().Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
};

void CDefinitionManager::SetNewEnumAUTO(LPUNKNOWN)
{
	ALL_TRY
	{
		ThrowNavoException2(ERCO_SET_METHOD_NOT_ALLOWED,IDPAGE_NOTAVAILABLE,"(iterator)","stdobjdef");
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

#ifdef _DEBUG
#if !defined(NAVO2008)
void CDefinitionManager::Dump()
{
	ofstream out(".\\stdobjdef_dump.txt");
	CSimpleLock oSimpleLock(m_oStdObjDefCS);
	out << "begin of stdobjdef dump" << endl;
	POSITION pos = m_oStdObjDefMap.GetStartPosition();
	while(pos)
	{
		long nTypeId;
		SCP<CStdObjDef> poStdObjDefSP;
		m_oStdObjDefMap.GetNextAssoc(pos,nTypeId,poStdObjDefSP);
		out << "\tbegin of object #" << nTypeId << " dump" << endl;
		poStdObjDefSP->Dump(out);
		out << "\tend of object #" << nTypeId << " dump" << endl;
	}
	out << "end of stdobjdef dump" << endl;
}
#endif
#endif
