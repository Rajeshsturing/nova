/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13
	REV:KB:2005-09-03 - przeniesienie n5gmop na serwer

*/
#include "stdafx.h"
#include "engineincl.h"
#include "types_consts_gm.h"
#include "n5gmop.h"
#include "n5gmopset.h"
#include "n5gmstan.h"
#include "n5gmserverobject.h"
#include "mem_db.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNavoLog g_oLog;

#define VLOCK_OPER_GM_ENSURE				1001
#define VLOCK_OPER_PT_ENSURE				1002

inline void init_navo_lock_oper_gm_ensure(navolock& roNavoLock, eWorkMode eWM)
{
	roNavoLock.m_fullid.m_class = LOCKCLASS_OPERATION;
	roNavoLock.m_fullid.m_typeid = ((eWM == wm_gm) ? VLOCK_OPER_GM_ENSURE : VLOCK_OPER_PT_ENSURE);
	roNavoLock.m_fullid.m_idobj = 0;
	roNavoLock.m_fullid.m_extra = 0;
	roNavoLock.m_type = nlt_exlock;
}

#define DIV_TO_KB 1024
#define WIDTH 7

static void _display_memory_info(bool bBefore)
{
	if (g_oLog.IsHandleValid())
	{
		if (bBefore)
		{
			g_oLog << "MEMORY BEFORE:";
		}
		else
		{
			g_oLog << "MEMORY AFTER:";
		}

		MEMORYSTATUSEX statex;

		statex.dwLength = sizeof(statex);

		GlobalMemoryStatusEx(&statex);
		g_oLog
			<< "There is percent of memory in use:" + Long2String(statex.dwMemoryLoad) +
			"\nThere are total KB of physical memory:" + Long2String(statex.ullTotalPhys / DIV_TO_KB) +
			"\nThere are free  KB of physical memory:" + Long2String(statex.ullAvailPhys / DIV_TO_KB) +
			"\nThere are free  KB of paging file:" + Long2String(statex.ullAvailPageFile / DIV_TO_KB) +
			"\nThere are free KB of virtual memory:" + Long2String(statex.ullAvailVirtual / DIV_TO_KB) + ".\n";
	}
}

static bool try_acquire_gm_ensure_lock(navolock& roNavoLock, SCP<IObjectServerExtensionHost> poOSEHSP)
{
	long iCounter = 5 * 60 * 3;		//3 minuty

	HRESULT hr = S_OK;

	for (hr = poOSEHSP->Lock(roNavoLock);
		hr != S_OK && (iCounter != 0);
		hr = poOSEHSP->Lock(roNavoLock))
	{
		iCounter--;
		::Sleep(200);
	}

	return (hr == S_OK);
}

CN5GMServerObjAUTO::CN5GMServerObjAUTO()
{
	AfxOleLockApp();
	EnableAutomation();
}

CN5GMServerObjAUTO::~CN5GMServerObjAUTO()
{
	AfxOleUnlockApp();
}

BEGIN_DISPATCH_MAP(CN5GMServerObjAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CN5GMServerObjAUTO)
	DISP_FUNCTION(CN5GMServerObjAUTO, "isvalid", IsValidAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CN5GMServerObjAUTO, "validate", RepairAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "check", CheckAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "forcerepair", ForceRepairAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "new_gmdoc", NewGMDocumentAUTO, VT_DISPATCH, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "movetoarchive", MoveToArchiveAUTO, VT_BOOL, VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "movefromarchive", MoveFromArchiveAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "createstorno", CreateStornoAUTO, VT_BOOL, VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "isvalid_pt", IsValidPTAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CN5GMServerObjAUTO, "validate_pt", RepairPTAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "check_pt", CheckPTAUTO, VT_BOOL, VTS_VARIANT)
	DISP_FUNCTION(CN5GMServerObjAUTO, "forcerepair_pt", ForceRepairPTAUTO, VT_BOOL, VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_DYNCREATE(CN5GMServerObjAUTO, CCmdTargetInterface)
// {188cb17B-82a4-4498-87d0-ebd8d9a00fb8}
IMPLEMENT_OLECREATE(CN5GMServerObjAUTO, "navogm.n5gmsvr", 0x188cb17B, 0x82a4, 0x4498, 0x87, 0xd0, 0xeb, 0xd8, 0xd9, 0xa0, 0x0f, 0xb8)

BEGIN_INTERFACE_MAP(CN5GMServerObjAUTO, CCmdTargetInterface)
	INTERFACE_PART(CN5GMServerObjAUTO, IID_IObjectServerExtension, ObjectServerExtension)
END_INTERFACE_MAP()


DELEGATE_UNKNOWN_INTERFACE(CN5GMServerObjAUTO, ObjectServerExtension)

BOOL CN5GMServerObjAUTO::IsValidAUTO()
{
	ALL_TRY
	{
		return (get_gmborder(m_poConnection,wm_gm) == GMBORDER_VALID);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CN5GMServerObjAUTO::IsValidPTAUTO()
{
	ALL_TRY
	{
		return (get_gmborder(m_poConnection,wm_pt) == GMBORDER_VALID);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CN5GMServerObjAUTO::RepairAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return Repair_or_CheckAUTO(roLogStreamVariant, false, wm_gm);
}

BOOL CN5GMServerObjAUTO::CheckAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return Repair_or_CheckAUTO(roLogStreamVariant, true, wm_gm);
}

BOOL CN5GMServerObjAUTO::RepairPTAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return Repair_or_CheckAUTO(roLogStreamVariant, false, wm_pt);
}

BOOL CN5GMServerObjAUTO::CheckPTAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return Repair_or_CheckAUTO(roLogStreamVariant, true, wm_pt);
}

BOOL CN5GMServerObjAUTO::Repair_or_CheckAUTO(const VARIANT FAR& roLogStreamVariant, bool bCheckOnly,
	eWorkMode eWM)
{
	bool bHoldsLock = false;
	navolock oNavoLock;
	init_navo_lock_oper_gm_ensure(oNavoLock, eWM);

	ALL_TRY
	{
		_display_memory_info(true);

	//prepare log
	SCP<CFileRemover> poFileRemoverSP;
	SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
			reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
			poFileRemoverSP);
	if (poFileRemoverSP.PointsObject())
	{
		poFileRemoverSP->DontRemove();
	}
	csrvlogger oLogger(poLogStreamSP,true);

	if (!try_acquire_gm_ensure_lock(oNavoLock,m_poOSEH_SP))
	{
		oLogger.on_error(cgms_exception(cgms_exception::sec_lock_failed));

		if (g_oLog.IsHandleValid())
		{
			g_oLog << "repair auto=lock FAILED";
		}

		return false;
	}
	bHoldsLock = true;

	SCP<IObjectServer> poObjectServerSP;
	poObjectServerSP.QueryInterface(m_poOSEH_SP);

	long nStartingNumOp = get_gmborder(m_poConnection, eWM);
	bool bResult = (nStartingNumOp == GMBORDER_VALID);

	if (!bResult)
	{
		bResult = repair_all_products_one_stroke(nStartingNumOp,m_poConnection,poObjectServerSP,
			oLogger,false,bCheckOnly,GMBORDER_VALID, eWM, false);

		if (bResult && !bCheckOnly)
		{
			set_gmborder(m_poConnection,GMBORDER_VALID, eWM);
		}
	}

	m_poOSEH_SP->UnLock(oNavoLock);
	bHoldsLock = false;

	_display_memory_info(false);

	return (bResult != false);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		if (bHoldsLock)
		{
			m_poOSEH_SP->UnLock(oNavoLock);
			bHoldsLock = false;
		}
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CN5GMServerObjAUTO::ForceRepairAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return ForceRepairAUTO_WorkMode(roLogStreamVariant, wm_gm);
}

BOOL CN5GMServerObjAUTO::ForceRepairPTAUTO(const VARIANT FAR& roLogStreamVariant)
{
	return ForceRepairAUTO_WorkMode(roLogStreamVariant, wm_pt);
}

BOOL CN5GMServerObjAUTO::ForceRepairAUTO_WorkMode(const VARIANT FAR& roLogStreamVariant, eWorkMode eWM)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;

		SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
				reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
				poFileRemoverSP);

		if (poFileRemoverSP.PointsObject())
		{
			poFileRemoverSP->DontRemove();
		}
		csrvlogger oLogger(poLogStreamSP,true);

		SCP<IObjectServer> poObjectServerSP;
		poObjectServerSP.QueryInterface(m_poOSEH_SP);

		return (repair_all_products_one_stroke(0,m_poConnection,poObjectServerSP,oLogger,
			true, false, GMBORDER_VALID, eWM, true) != false);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

//---------------------------------------------------------------------------------------

LPDISPATCH CN5GMServerObjAUTO::NewGMDocumentAUTO(const VARIANT FAR& roLogStreamVariant)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;

		SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
				reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
				poFileRemoverSP);

		if (poFileRemoverSP.PointsObject())
		{
			poFileRemoverSP->DontRemove();
		}

		SCP<IObjectServer> poObjectServerSP;
		poObjectServerSP.QueryInterface(m_poOSEH_SP);

		SCP<CN5GMOpAUTO> poGMOpSP = NewSCP<CN5GMOpAUTO>(new CN5GMOpAUTO(poLogStreamSP, m_poConnection, poObjectServerSP));

		return poGMOpSP->GetDispatch(TRUE);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}
//---------------------------------------------------------------------------------------
// called by navoserver which is the host for extensions
//---------------------------------------------------------------------------------------

STDMETHODIMP CN5GMServerObjAUTO::XObjectServerExtension::
Init(IObjectServerExtensionHost* pHost)
{
	METHOD_PROLOGUE(CN5GMServerObjAUTO, ObjectServerExtension)

		ALL_TRY
	{
		ASSERT(pHost != NULL);

		pThis->m_poOSEH_SP = NewSCP(pHost, true);
		SCP<IUnknown> poConUnkSP;

		HRESULT hr = pHost->GetDBConnection(&(poConUnkSP.GetRawPointer()));

		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_TODO, IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		}

		pThis->m_poConnection = poConUnkSP.SafeGet();
	}
	TOP_ALL_CATCH(pThis->GetErrorStorage(), DISP_E_EXCEPTION);

	return S_OK;
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
CN5GMOpAUTO::CN5GMOpAUTO(SCP<IStream> poLogStreamSP,
	ADODB::_ConnectionPtr poConnection, SCP<IObjectServer> poObjectServerSP) :
	m_poConnection(poConnection),
	m_poObjectServerSP(poObjectServerSP),
	m_poLogStreamSP(poLogStreamSP)
{
	AfxOleLockApp();
	EnableAutomation();

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "> batch=" + Long2String(reinterpret_cast<long>(this));
	}
}

CN5GMOpAUTO::~CN5GMOpAUTO()
{
	if (g_oLog.IsHandleValid())
	{
		g_oLog << "< batch=" + Long2String(reinterpret_cast<long>(this));
	}
	AfxOleUnlockApp();
}

void CN5GMOpAUTO::AddOperationAUTO(long iNumOper, long iLP, long idProd, long idOpak,
	long eTypOper, CY curIlosc, CY curCena, long idMag, long idDost, long idDostLP, DATE dDataWazn,
	long iNumOperRel, long iLPRel, CY curPrzelicznik)
{
	ALL_TRY
	{
		if (g_oLog.IsHandleValid())
		{
			CString strMsgParam;
			quantity tmpIlosc = COleCurrency(curIlosc);
			quantity tmpCena = COleCurrency(curCena);
			strMsgParam.Format("numop=%d/%d,idprod=%d,idmag=%d,typop=%d,ilosc=%s,cena=%s",iNumOper,iLP,idProd,idMag,eTypOper,
				tmpIlosc.Format(),tmpCena.Format());

			g_oLog << "= batch=" + Long2String(reinterpret_cast<long>(this)) + "," +
				strMsgParam;
		}
		SCP<db_n5gmop> poGMOPSP = NewSCP(new db_n5gmop(iNumOper,iLP,idProd,idOpak,eTypOper,
				curIlosc,curCena,idMag,idDost,idDostLP,dDataWazn,iNumOperRel,iLPRel,curPrzelicznik),false);
		m_oInputGMDBArray.Add(poGMOPSP);
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CN5GMOpAUTO::FinishAUTO()
{
	return FinishAUTO_WorkMode(wm_gm);
}

BOOL CN5GMOpAUTO::FinishPTAUTO()
{
	return FinishAUTO_WorkMode(wm_pt);
}

BOOL CN5GMOpAUTO::FinishAUTO_WorkMode(eWorkMode eWM)
{
	bool bHoldsLock = false;
	navolock oNavoLock;
	init_navo_lock_oper_gm_ensure(oNavoLock, eWM);

	SCP<IObjectServerExtensionHost> poOSEHSP;

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!1batch=" + Long2String(reinterpret_cast<long>(this));
	}

	ALL_TRY
	{
		csrvlogger oLogger(m_poLogStreamSP,true);

	//--------- wyznaczenie nowego border'a
	//gmborder_load
	long iOldBorder = get_gmborder(m_poConnection, eWM);

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!2batch=" + Long2String(reinterpret_cast<long>(this)) +
			",oldbrd=" + Long2String(iOldBorder);
	}

	//gmborder_from_gmop
	long iBorder = iOldBorder;
	if (iBorder > 0)
	{
		for (long iter = 0; iter <= m_oInputGMDBArray.GetUpperBound(); iter++)
		{
			SCP<db_n5gmop> poGMOPSP = m_oInputGMDBArray[iter];

			long iOperationBorder = _find_border(poGMOPSP, eWM);
			ASSERT(iOperationBorder >= 0 || iOperationBorder == -2);

			if (g_oLog.IsHandleValid())
			{
				g_oLog << "!3batch=" + Long2String(reinterpret_cast<long>(this)) +
					",iter=" + Long2String(iter) + ",opbrd=" + Long2String(iOperationBorder);
			}

			iBorder = min(iBorder,iOperationBorder);
			if (iBorder == -2)
			{
				oLogger.on_error(cgms_exception(cgms_exception::sec_not_supply_at_all,
					poGMOPSP->get_numop(),poGMOPSP->get_lp(),0,
						poGMOPSP->get_idprod(),poGMOPSP->get_idopak(),poGMOPSP->get_idmag(),
							poGMOPSP->get_ilosc()));
				return false;
			}

			if (iBorder == 0)
			{
				break;
			}
		}
	}

	//--------- przetwarzanie
	n5gmop_document oDocument(oLogger,GMBORDER_VALID,eWM);
	n5gmstan_glob oGlobStan(oLogger,true,GMBORDER_VALID,eWM);

	for (long iter = 0; iter <= m_oInputGMDBArray.GetUpperBound(); iter++)
	{
		SCP<db_n5gmop> poGMOPSP = m_oInputGMDBArray[iter];
		oDocument.move_single_dbgmop(oGlobStan,poGMOPSP);
	}

	poOSEHSP.QueryInterface(m_poObjectServerSP);

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!4batch=" + Long2String(reinterpret_cast<long>(this)) +
			"trying 2 lock";
	}

	if (!try_acquire_gm_ensure_lock(oNavoLock,poOSEHSP))
	{
		oLogger.on_error(cgms_exception(cgms_exception::sec_lock_failed));

		if (g_oLog.IsHandleValid())
		{
			g_oLog << "!5batch=" + Long2String(reinterpret_cast<long>(this)) +
				"lock FAILED";
		}
		return false;
	}
	bHoldsLock = true;

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!6batch=" + Long2String(reinterpret_cast<long>(this)) +
			"lock acquired";
	}

	oDocument.finish_document(oGlobStan);
	oDocument.flush_document(oGlobStan,m_poObjectServerSP,m_poConnection, false);
	oGlobStan.flush(false,sfm_just_append,m_poObjectServerSP,m_poConnection, false);

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!7batch=" + Long2String(reinterpret_cast<long>(this)) +
			",newbrd=" + Long2String(iBorder);
	}

	//--- zaktualizuj border (gmborder_save)
	if (iBorder < iOldBorder)
	{
		set_gmborder(m_poConnection,iBorder,eWM);
	}

	poOSEHSP->UnLock(oNavoLock);
	bHoldsLock = false;

	if (g_oLog.IsHandleValid())
	{
		g_oLog << "!8batch=" + Long2String(reinterpret_cast<long>(this)) +
			",result=" + (oLogger.was_error() ? "ERROR" : "ok");
	}

	if (!oLogger.was_error())
	{
		return true;
	}
	else
	{
		return false;
	}
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		if (bHoldsLock)
		{
			poOSEHSP->UnLock(oNavoLock);
			bHoldsLock = false;
		}

		ContinueThrowNavoAutoException(roNavoException);
	};
}

long CN5GMOpAUTO::_find_border(SCP<db_n5gmop>& rpoGMOP, eWorkMode eWM)
{
	LPCTSTR lpTable = (eWM == wm_gm) ? "n5gmop" : "n5ptop";

	long iBorder = 0;
	switch (rpoGMOP->get_typop())
	{
	case N5GMOP_P_CZ_IZ_DS:
	case N5GMOP_P_CZ_IZ_BO:
	case N5GMOP_P_CP_IZ_DS:
	case N5GMOP_R_CA_IZ_DI:
	case N5GMOP_K_CA_IA_DI:
	{
		//'przychody
		//'zadana (iddost)

		iBorder = hihyper(rpoGMOP->get_iddostawa());
	}
	break;
	case N5GMOP_R_CA_IZ_DZ:
	{
		//'zadana (numop)
		iBorder = rpoGMOP->get_numop_rel();
	}
	break;
	case N5GMOP_R_CA_IZ_DF:
	{
		//'fifo
		//'znajdŸ ostatni 'taki sam' rozchod wczeœniejszy o naszego. dostawa z której wzi¹³ jest LB 
		 //'uwgzlednienie innych typow w gmo_eTypOp mo¿e spowodowaæ optymalizacje, ale teraz jest 
		//'"bezpiecznie", choæ byæ mo¿e nieoptymalnie
		CString oSQLQueryString;
		oSQLQueryString.Format("select top 1 gmo_idDost from %s where gmo_pProd=%d and "
			"gmo_pOpak=%d and gmo_pMag=%d and gmo_nNumOp<%d and gmo_idDost <> -1 and gmo_eTypOp in (%d)"
			" order by gmo_nNumOp desc, gmo_nLP desc, gmo_idDost desc , gmo_idDostLP desc",
			lpTable, rpoGMOP->get_idprod(), rpoGMOP->get_idopak(), rpoGMOP->get_idmag(), rpoGMOP->get_numop(), N5GMOP_R_CA_IZ_DF);
		ADODB::_RecordsetPtr ponBorderRS = _ado_openRS(oSQLQueryString, m_poConnection, false);
		if (ponBorderRS->EOF)
		{
			//'nie ma rozchodu - znajdŸ pierwsz¹ dostawê tego produktu
			oSQLQueryString.Format("select top 1 gmo_idDost from %s where gmo_pProd=%d and "
				"gmo_pOpak=%d and gmo_pMag=%d and gmo_nNumOp < %d and gmo_eTypOp in (%d,%d,%d,%d)"
				"order by gmo_nNumOp, gmo_nLP, gmo_idDost, gmo_idDostLP",
				lpTable, rpoGMOP->get_idprod(), rpoGMOP->get_idopak(), rpoGMOP->get_idmag(), rpoGMOP->get_numop(),
				N5GMOP_P_CZ_IZ_DS, N5GMOP_P_CP_IZ_DS, N5GMOP_P_CA_IA_DS, N5GMOP_P_CZ_IZ_BO);

			ponBorderRS = _ado_openRS(oSQLQueryString, m_poConnection, false);

			if (ponBorderRS->EOF)
			{
				if (eWM == wm_gm)
				{
					return -2;	//brak jakiejkolwiek dostawy
				}
				else
				{
					return 0;	//PT: przyjmujemy poczatek obliczen
				}
			}
			else
			{
				iBorder = _ado_getlong(ponBorderRS, 0);
			}
		}
		else
		{
			iBorder = _ado_getlong(ponBorderRS, 0);
		}
	}
	break;
	case N5GMOP_R_CZ_IZ_DX:
	{
		//'robocizna - ustaw na tê operacjê
		iBorder = rpoGMOP->get_numop();
	}
	break;
	case N5GMOP_P_CA_IA_DS:
	{
		//'MM+ - ignoruj bo i tak jest rozchód, który ustawi border
		iBorder = rpoGMOP->get_numop();
	}
	break;
	default:
		ASSERT(false);
	}

	ASSERT(iBorder <= rpoGMOP->get_numop());

	iBorder = max(0, iBorder);
	return iBorder;
}

BEGIN_DISPATCH_MAP(CN5GMOpAUTO, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CN5GMOpAUTO)
	DISP_FUNCTION(CN5GMOpAUTO, "addgmop", AddOperationAUTO, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_CY VTS_CY VTS_I4 VTS_I4 VTS_I4 VTS_DATE VTS_I4 VTS_I4 VTS_CY)
	DISP_FUNCTION(CN5GMOpAUTO, "finish", FinishAUTO, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CN5GMOpAUTO, "finish_pt", FinishPTAUTO, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
//---------------------------------------------------------------------------------------
// main repair procedure
//---------------------------------------------------------------------------------------
ADODB::_RecordsetPtr navogm_server::_ado_openRS(const CString& roSQLString, ADODB::_ConnectionPtr& rpoConnectionPtr, bool bLargeGM)
{
	ADODB::_RecordsetPtr poRecordsetPtr;
	poRecordsetPtr.CreateInstance("ADODB.Recordset");

	if (!bLargeGM)
	{
		poRecordsetPtr->CursorLocation = ADODB::adUseClient;
		poRecordsetPtr->Open(_bstr_t(roSQLString), rpoConnectionPtr.GetInterfacePtr(),
			ADODB::adOpenForwardOnly,
			ADODB::adLockReadOnly,
			ADODB::adCmdUnspecified);

		poRecordsetPtr->PutRefActiveConnection(NULL);
	}
	else
	{
		poRecordsetPtr->CursorLocation = ADODB::adUseServer;
		poRecordsetPtr->Open(_bstr_t(roSQLString), rpoConnectionPtr.GetInterfacePtr(),
			ADODB::adOpenStatic,
			ADODB::adLockReadOnly,
			ADODB::adCmdUnspecified);

		//poRecordsetPtr->PutRefActiveConnection(NULL);
	}

	return poRecordsetPtr;
}

long navogm_server::get_gmborder(ADODB::_ConnectionPtr& rpoConnection, eWorkMode eWM)
{
	ADODB::_RecordsetPtr pon5globprofRS = _ado_openRS("select Wartosc from n5globprof where Indeks=" +
		Long2String(((eWM == wm_gm) ? GLOBPROF_GMBORDER : GLOBPROF_PTBORDER)), rpoConnection, false);
	if (pon5globprofRS->EOF)
	{
		return 0;
	}

	return _ttol(_ado_getstring(pon5globprofRS, 0));
}

void navogm_server::set_gmborder(ADODB::_ConnectionPtr& rpoConnection, long iBorderValue, eWorkMode eWM)
{
	CADOCommand oCommand(rpoConnection);
	CString oCmdString;
	oCmdString.Format("update n5globprof set Wartosc=%d where Indeks=%d", iBorderValue,
		(eWM == wm_gm) ? GLOBPROF_GMBORDER : GLOBPROF_PTBORDER);
	oCommand.ExecDirect(oCmdString, true);
}


bool navogm_server::repair_recordset(long nStartingNumOp, ADODB::_RecordsetPtr pon5opmagRS,
	ADODB::_ConnectionPtr& rpoConnection,
	SCP<IObjectServer>& rpoObjectServerSP, csrvlogger& roLogger,
	bool bForce, bool bCheckOnly, long iLastNumOp, eWorkMode eWM, bool bLargeGM)
{
	try
	{
		if (g_oLog.IsHandleValid())
		{
			g_oLog << "> repair, start=" + Long2String(nStartingNumOp);

			if (bCheckOnly)
			{
				g_oLog << "checkonly mode";
			}
			else
			{
				g_oLog << "update mode";
			}
		}

		//---------------------------------------------
		// flagi do przestawiania trybu
		// g_bContinueOnError - rejestruj b³¹d i kontunuj / rzucaj wyj¹tek
		// g_bAllowNegativeQuantity - pozwala na wydanie ujemnej iloœci
		// (zawsze jednak to sygnalizuje)
		//---------------------------------------------
		const bool g_bContinueOnError = true;
		const bool g_bAllowNegativeQuantity = true;

		//-----------------------------------------------------------------------------
		// przyjmujemy, ¿e gdy naprawiamy od pocz¹tku, to jest to forcerepair
		//-----------------------------------------------------------------------------

		if (bLargeGM)
		{
			long iDummyIdObj;
			int iTypeId = (eWM == wm_gm) ? TYPEID_N5GMOP : TYPEID_N5PTOP;
			VERIFY(rpoObjectServerSP->GetUniqueIdent(iTypeId, &iDummyIdObj) == S_OK);
		}

		bool bForceFlushStanMag = bForce;

		n5gmstan_glob oStanMag(roLogger, g_bAllowNegativeQuantity, nStartingNumOp, eWM);

		while (!pon5opmagRS->EOF)
		{
			n5gmop_document oRepairSet(roLogger, nStartingNumOp, eWM);
			n5gmop_document::eload_result eLR;

			do
			{
				long iLoadedLP = 0;
				eLR = oRepairSet.load_single_lp(oStanMag, pon5opmagRS, iLoadedLP);
				ASSERT(iLoadedLP != 0);
				oRepairSet.process_single_lp(oStanMag, iLoadedLP);
			} while (eLR == n5gmop_document::lr_eolp);

			oRepairSet.finish_document(oStanMag);

			if (!bCheckOnly)
			{
				oRepairSet.flush_document(oStanMag, rpoObjectServerSP, rpoConnection, bLargeGM);
			}

			if (roLogger.was_error())
			{
				bool bBreak = false;
				if (bCheckOnly)		//zawsze w trybie 'tylko sprawdz'
				{
					bBreak = true;
				}
				else
				{
					if (!roLogger.was_only_missing_qty_errors())
					{
						bBreak = true;	//przerwij gdy inne bledy
					}
				}

				if (bBreak)
				{
					if (g_oLog.IsHandleValid())
					{
						g_oLog << "! repair ERROR - breaking";
					}
					if (!bForce)
					{
						break;
					}
				}
			}
		}


		if (roLogger.was_error() && !bForce)
		{
			if (g_oLog.IsHandleValid())
			{
				g_oLog << "! repair ERROR - skipping flush";
			}
		}
		else
		{
			if (g_oLog.IsHandleValid())
			{
				g_oLog << "= repair, flushing";
			}

			if (!bCheckOnly)
			{
				if (iLastNumOp != GMBORDER_VALID)
				{
					//tworzenie BO
					oStanMag.write_as_bo(iLastNumOp, rpoObjectServerSP, rpoConnection);
				}
				else
				{
					oStanMag.flush(bForceFlushStanMag, sfm_diff_delivery, rpoObjectServerSP, rpoConnection, bLargeGM);
				}
			}
		}

		if (g_oLog.IsHandleValid())
		{
			g_oLog << CString("< repair, result=") + (roLogger.was_error() ? "ERROR" : "ok");
		}
		return !roLogger.was_error();
	}
	catch (const cgms_exception& /*roException*/)
	{
		return false;
	}
}

bool navogm_server::repair_all_products_one_stroke(long nStartingNumOp,
	ADODB::_ConnectionPtr& rpoConnection, SCP<IObjectServer>& rpoObjectServerSP,
	csrvlogger& roLogger, bool bForce, bool bCheckOnly, long iLastNumOp, eWorkMode eWM, bool bLargeGM)
{
	CString oSQLQueryString;
	if (iLastNumOp != GMBORDER_VALID) //tylko z archiwum
	{
		oSQLQueryString = _T("select * from n5gmop_arch");
	}
	else
	{
		if (eWM == wm_gm)
		{
			oSQLQueryString = _T("select * from n5gmop");
		}
		else
		{
			oSQLQueryString = _T("select * from n5ptop");
		}
	}
	if (nStartingNumOp != 0 || iLastNumOp != GMBORDER_VALID)
	{
		oSQLQueryString += _T(" where ");
		if (nStartingNumOp != 0)
		{
			oSQLQueryString += _T("gmo_nNumOp >= ") + Long2String(nStartingNumOp);
		}
		if (nStartingNumOp != 0 && iLastNumOp != GMBORDER_VALID)
		{
			oSQLQueryString += _T(" and ");
		}
		if (iLastNumOp != GMBORDER_VALID)
		{
			oSQLQueryString += _T("gmo_nNumOp <= ") + Long2String(iLastNumOp);
		}
	}

	//order by gmo_nNumOp, gmo_nLP, gmo_eTypOp, gmo_nNumOpRel, gmo_nLPRel, idobj
	//uwaga! nie mozna zmieniac kolejnosci gdyz istotne jest w przypadku update
	//aby zmiany byly przetwarzane na koncu ('na wierzchu') i nadpisywaly
	//'poprzednie wersje'
	//uwaga, uporzadkowanie (gmo_nNumOp, gmo_nLP, gmo_eTypOp, idobj) powoduje w pewnych przypadkach
	//niejednoznacznosc (zmiennosc wynikow) gdyz idobj nie jest kontrolowany w zaden sposob

	oSQLQueryString += _T(" order by gmo_nNumOp, gmo_nLP, gmo_eTypOp, idobj");

	ADODB::_RecordsetPtr pon5opmagRS = _ado_openRS(oSQLQueryString, rpoConnection, bLargeGM);

	if (false)
	{
		mem_base oMemBase;
		if (g_oLog.IsHandleValid())
		{
			g_oLog << "= membase - loadstart";
		}

		oMemBase.load_from_rs(pon5opmagRS);

		if (g_oLog.IsHandleValid())
		{
			g_oLog << "= membase - loadend";
		}

		return repair_recordset_mem(nStartingNumOp, oMemBase, rpoObjectServerSP, roLogger, bForce);
	}
	else
	{
		return repair_recordset(nStartingNumOp, pon5opmagRS, rpoConnection, rpoObjectServerSP,
			roLogger, bForce, bCheckOnly, iLastNumOp, eWM, bLargeGM);
	}
}


BOOL CN5GMServerObjAUTO::MoveFromArchiveAUTO(const VARIANT FAR& roLogStreamVariant)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;

		SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
				reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
				poFileRemoverSP);

		if (poFileRemoverSP.PointsObject())
		{
			poFileRemoverSP->DontRemove();
		}
		csrvlogger oLogger(poLogStreamSP,true);

		SCP<IObjectServer> poObjectServerSP;
		poObjectServerSP.QueryInterface(m_poOSEH_SP);


		CADOCommand oCommand(m_poConnection);
		oCommand.set_timeout(0);
		oCommand.ExecProc("n5gmop_move_from_archive",true);

		return TRUE;
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}

BOOL CN5GMServerObjAUTO::MoveToArchiveAUTO(long iBorder, const VARIANT FAR& roLogStreamVariant)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;

		SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
				reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
				poFileRemoverSP);

		if (poFileRemoverSP.PointsObject())
		{
			poFileRemoverSP->DontRemove();
		}
		csrvlogger oLogger(poLogStreamSP,true);

		SCP<IObjectServer> poObjectServerSP;
		poObjectServerSP.QueryInterface(m_poOSEH_SP);

		{
			CADOCommand oCommand(m_poConnection);
			oCommand.set_timeout(0);
			oCommand.AddInParam(SQLT_INT,(LPVOID)&iBorder);
			oCommand.ExecProc("n5gmop_move_to_archive",true);
		}

		if (repair_all_products_one_stroke(0, m_poConnection, poObjectServerSP, oLogger, true, false, iBorder, wm_gm, false))
		{
			//to dopiero po przerzuceniu
			CADOCommand oCommand(m_poConnection);
			oCommand.ExecProc("n5gmop_map_archive",true);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}



BOOL CN5GMServerObjAUTO::CreateStornoAUTO(long iBorder, const VARIANT FAR& roLogStreamVariant)
{
	ALL_TRY
	{
		SCP<CFileRemover> poFileRemoverSP;

		SCP<IStream> poLogStreamSP = CreateFileStream_Write_On_SOV(
				reinterpret_cast<const CSmartOleVariant&>(roLogStreamVariant),
				poFileRemoverSP);

		if (poFileRemoverSP.PointsObject())
		{
			poFileRemoverSP->DontRemove();
		}
		csrvlogger oLogger(poLogStreamSP,true);

		SCP<IObjectServer> poObjectServerSP;
		poObjectServerSP.QueryInterface(m_poOSEH_SP);

		//usun stare storno z tego miejsca
		{
			CADOCommand oCommand(m_poConnection);
			oCommand.set_timeout(0);
			oCommand.ExecDirect("delete from n5gmop where gmo_eTypOp=10 and gmo_nNumOp=" + Long2String(iBorder),true);
		}

		CString oSQLQueryString =
			"select gmo_pprod,gmo_popak,gmo_pmag,sum(gmo_curIlosc * gmo_curCena) - sum(gmo_curWartosc) "
			"from n5gmop "
			"where gmo_nnumop < " + Long2String(iBorder) +
			"group by gmo_pprod,gmo_popak,gmo_pmag "
			"having abs(sum(gmo_curWartosc) - sum(gmo_curIlosc * gmo_curCena)) >= 0.01";

		ADODB::_RecordsetPtr pon5opmagRS = _ado_openRS(oSQLQueryString,m_poConnection, false);
		long iLP = 1;
		while (!pon5opmagRS->EOF)
		{
			long idProd = _ado_getlong(pon5opmagRS,0);
			long idOpak = _ado_getlong(pon5opmagRS,1);
			long idMag = _ado_getlong(pon5opmagRS,2);
			price curWartosc = _ado_getcurrency(pon5opmagRS,3);

			db_n5gmop oDBGMOP(iBorder,iLP,
				  idProd,idOpak,N5GMOP_K_STORNO_WART,
				  curZero,
				  curZero,idMag,
				  iBorder,iLP,
				  (navogm_date)0,
				  iBorder,iLP,COleCurrency(1,0));
			oDBGMOP.set_wartosc_manual(curWartosc);

			oDBGMOP.insert_db(poObjectServerSP,m_poConnection,wm_gm);

			pon5opmagRS->MoveNext();
			iLP++;
		}

		return TRUE;
	}
		ALL_CATCH(CNavoException& roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	};
}



//=======================================================================================
// memory version
//=======================================================================================


bool navogm_server::repair_recordset_mem(long nStartingNumOp, mem_base& roMemBase,
	SCP<IObjectServer>& rpoObjectServerSP,
	csrvlogger& roLogger, bool bForce)
{
	try
	{
		if (g_oLog.IsHandleValid())
		{
			g_oLog << "> memrepair, start=" + Long2String(nStartingNumOp);
		}

		//---------------------------------------------
		// flagi do przestawiania trybu
		// g_bContinueOnError - rejestruj b³¹d i kontunuj / rzucaj wyj¹tek
		// g_bAllowNegativeQuantity - pozwala na wydanie ujemnej iloœci
		// (zawsze jednak to sygnalizuje)
		//---------------------------------------------
		const bool g_bContinueOnError = true;
		const bool g_bAllowNegativeQuantity = true;
		const int g_iMaxErrors = 100;

		//-----------------------------------------------------------------------------
		// przyjmujemy, ¿e gdy naprawiamy od pocz¹tku, to jest to forcerepair
		//-----------------------------------------------------------------------------

		bool bForceFlushStanMag = bForce;

		n5gmstan_glob oStanMag(roLogger, g_bAllowNegativeQuantity, nStartingNumOp, wm_gm);

		mem_base_iterator oIterator(roMemBase);

		while (!oIterator.is_end())
		{
			CComPtr<mem_dok> poMemDokSP = oIterator.get_next();
			ASSERT(poMemDokSP != NULL);
			n5gmop_document oRepairSet(roLogger, nStartingNumOp, wm_gm);

			long iLP = 1;
			while (poMemDokSP->is_lp(iLP))
			{
				//todo: pomijanie dziur dla produkcji
				SCP<mem_lp> poMemLPSP = poMemDokSP->get_lp(iLP);
				if (poMemLPSP.PointsObject())
				{
					oRepairSet.load_single_mem_lp(oStanMag, poMemDokSP->get_lp(iLP));
					oRepairSet.process_single_lp(oStanMag, iLP);
				}

				iLP++;
			}

			oRepairSet.finish_document(oStanMag);

			oRepairSet.flush_document_mem(oStanMag, rpoObjectServerSP, poMemDokSP);

			if (roLogger.was_error() && roLogger.was_only_missing_qty_errors())
			{
				if (g_oLog.IsHandleValid())
				{
					g_oLog << "! memrepair ERROR - breaking";
				}
				if (!bForce)
				{
					break;
				}
			}
		}


		if (roLogger.was_error() && !bForce)
		{
			if (g_oLog.IsHandleValid())
			{
				g_oLog << "! memrepair ERROR - skipping flush";
			}
		}
		else
		{
			if (g_oLog.IsHandleValid())
			{
				g_oLog << "= memrepair, flushing";
			}
			//		oStanMag.flush(bForceFlushStanMag,sfm_diff_delivery,rpoObjectServerSP,rpoConnection);
		}

		if (g_oLog.IsHandleValid())
		{
			g_oLog << CString("< memrepair, result=") + (roLogger.was_error() ? "ERROR" : "ok");
		}
		return !roLogger.was_error();
	}
	catch (const cgms_exception& /*roException*/)
	{
		return false;
	}
}

//=======================================================================================
// memory version
//=======================================================================================
