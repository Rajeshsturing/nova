/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13
*/
#include "stdafx.h"
#include "engineincl.h"
#include "types_consts_gm.h"
#include "n5gmop.h"
#include "n5gmstan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace navogm_server;

extern CNavoLog g_oLog;

n5gmop::n5gmop(const n5gmop & ron5gmop)
{
	(*this) = ron5gmop;
}

n5gmop::n5gmop()
{
	//protected constructor for n5gmop
}

void n5gmop::operator = (const n5gmop & ron5gmop_base)
{
	m_eTypOp	= ron5gmop_base.m_eTypOp;
	m_nNumOp	= ron5gmop_base.m_nNumOp;
	m_nLP		= ron5gmop_base.m_nLP;
	m_curIlosc	= ron5gmop_base.m_curIlosc;
	m_curCena	= ron5gmop_base.m_curCena;
	m_curWartosc= ron5gmop_base.m_curWartosc;
	m_idProd	= ron5gmop_base.m_idProd;
	m_idOpak	= ron5gmop_base.m_idOpak;
	m_idMag		= ron5gmop_base.m_idMag;
	m_idDost	= ron5gmop_base.m_idDost;
	m_dDataWazn	= ron5gmop_base.m_dDataWazn;
	m_nNumOpRel	= ron5gmop_base.m_nNumOpRel;
	m_nLPRel	= ron5gmop_base.m_nLPRel;
	m_curPrzel	= ron5gmop_base.m_curPrzel;
}



//=================================================
//=================================================

//--------- read "old" constructor ---------

db_n5gmop::db_n5gmop(ADODB::_RecordsetPtr & rpoN5GMOPRS) :
	n5gmop(),
	m_bDBModified(false)
{
	_read_from_ado(rpoN5GMOPRS);
}

//--------- clone "new" --------------------

db_n5gmop::db_n5gmop(const n5gmop & ron5gmop,const n5gmdostawa_prop & ron5gmdost_prop,
					 long iNumOpRel,long iLPRel,const quantity & rcurIlosc) :
	n5gmop(),
	m_bDBModified(true)
{
	m_idObj = 0;
	m_nVersion = 1;

	fill_expend(ron5gmop,ron5gmdost_prop,iNumOpRel,iLPRel,rcurIlosc);
}

db_n5gmop::db_n5gmop(long iNumOper,long iLP,
				  long idProd,long idOpak,
				  long eTypOper,
				  quantity curIlosc,price curCena,long idMag,
				  long idDost,long idDostLP,
				  navogm_date dDataWazn,
				  long iNumOperRel,long iLPRel,quantity curPrzel) :
	n5gmop(),
	m_bDBModified(true)
{
	m_idObj		= 0;
	m_nVersion	= 1;

	m_eTypOp	= en5gmtypop(eTypOper);
	m_nNumOp	= iNumOper;
	m_nLP		= iLP;
	m_curIlosc	= curIlosc;
	m_curCena	= curCena;

	m_curWartosc = curIlosc * curCena;
	round_currency_2(m_curWartosc.m_cur);

	m_idProd	= idProd;
	m_idOpak	= idOpak;
	m_idMag		= idMag;
	m_idDost	= longlong(idDost,idDostLP);
	m_dDataWazn	= dDataWazn;
	m_nNumOpRel	= iNumOperRel;
	m_nLPRel	= iLPRel;
	m_curPrzel	= curPrzel;
	
}

void db_n5gmop::fill_expend(const n5gmop & ron5gmop,
	const n5gmdostawa_prop & ron5gmdost_prop,long iNumOpRel,long iLPRel,const quantity & rcurIlosc)
{
	price curNewWartosc;

	if(ron5gmop.get_typop() == N5GMOP_K_STORNO_WART)
	{
		curNewWartosc = ron5gmop.get_wartosc();
	}
	else
	{
		curNewWartosc = rcurIlosc * ron5gmdost_prop.get_cena();
		round_currency_2(curNewWartosc.m_cur);
	}

	m_bDBModified = (m_idObj == 0) || 
		(m_eTypOp	!= ron5gmop.get_typop()) || 
		(m_nNumOp != ron5gmop.get_numop()) || 
		(m_nLP	!= ron5gmop.get_lp()) || 
		(m_curIlosc != rcurIlosc) || 
		(m_curCena	!= ron5gmdost_prop.get_cena()) || 
		(m_curWartosc != curNewWartosc) || 
		(m_idProd != ron5gmop.get_idprod()) || 
		(m_idOpak != ron5gmop.get_idopak()) || 
		(m_idMag != ron5gmop.get_idmag()) || 
		(m_idDost != ron5gmdost_prop.get_iddostawa()) || 
		(m_dDataWazn != ron5gmdost_prop.get_datawazn()) || 
		(m_nNumOpRel != iNumOpRel) || 
		(m_nLPRel != iLPRel) || 
		(m_curPrzel != ron5gmop.get_przel());

	m_eTypOp	= ron5gmop.get_typop();
	m_nNumOp	= ron5gmop.get_numop();
	m_nLP		= ron5gmop.get_lp();

	m_curIlosc	= rcurIlosc;
	m_curCena	= ron5gmdost_prop.get_cena();
	
	m_curWartosc= curNewWartosc;
	m_idProd	= ron5gmop.get_idprod();
	m_idOpak	= ron5gmop.get_idopak();
	m_idMag		= ron5gmop.get_idmag();
	m_idDost	= ron5gmdost_prop.get_iddostawa();
	m_dDataWazn	= ron5gmdost_prop.get_datawazn();
	m_nNumOpRel	= iNumOpRel;
	m_nLPRel	= iLPRel;
	m_curPrzel	= ron5gmop.get_przel();
}

void db_n5gmop::insert_db(SCP<IObjectServer> & rpoObjectServerSP,ADODB::_ConnectionPtr & rpoConnection,
						  eWorkMode eWM)
{
	ASSERT(m_idObj == 0);
	int iTypeId = (eWM == wm_gm) ? TYPEID_N5GMOP : TYPEID_N5PTOP;
	VERIFY(rpoObjectServerSP->GetUniqueIdent(iTypeId,&m_idObj) == S_OK);
	ASSERT(m_idObj != 0);

	CADOCommand oCommand(rpoConnection);
	
	_fill_command_param(oCommand);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmop_insert" : "n5ptop_insert",true);
	m_bDBModified = false;

	if(g_oLog.IsHandleValid())
	{
		CString oIloscString = m_curIlosc.Format();
		CString oCenaString = m_curCena.Format();
		
		CString strMsg;
		strMsg.Format("db_n5gmop::insert_db [idobj=%d,numop=%d/%d]=[idprod=%d,idmag=%d,%d][ilosc=%s,cena=%s]",
			m_idObj,m_nNumOp,m_nLP,m_idProd,m_idMag,m_idOpak,(LPCTSTR)oIloscString,(LPCTSTR)oCenaString);
		g_oLog << strMsg;
		
		TRACE(strMsg + "\n");
	}
}

void db_n5gmop::update_db(ADODB::_ConnectionPtr & rpoConnection,
						  eWorkMode eWM)
{
	ASSERT(m_idObj != 0);
	CADOCommand oCommand(rpoConnection);
	
	m_nVersion++;

	_fill_command_param(oCommand);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmop_update" : "n5ptop_update",true);
	m_bDBModified = false;

	if(g_oLog.IsHandleValid())
	{
		CString oIloscString = m_curIlosc.Format();
		CString oCenaString = m_curCena.Format();
		CString strMsg;
		strMsg.Format("db_n5gmop::update_db [idobj=%d,numop=%d/%d]=[idprod=%d,idmag=%d,%d][ilosc=%s,cena=%s]",
			m_idObj,m_nNumOp,m_nLP,m_idProd,m_idMag,m_idOpak,(LPCTSTR)oIloscString,(LPCTSTR)oCenaString);

		g_oLog << strMsg;
		TRACE(strMsg + "\n");
	}
}

void db_n5gmop::delete_db(ADODB::_ConnectionPtr & rpoConnection,
						  eWorkMode eWM)
{
	ASSERT(m_idObj != 0);
	CADOCommand oCommand(rpoConnection);
	
	oCommand.AddInParam(SQLT_INT,(LPVOID)&m_idObj);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmop_delete" : "n5ptop_delete",true);
	m_bDBModified = false;

	if(g_oLog.IsHandleValid())
	{
		CString oIloscString = m_curIlosc.Format();
		CString oCenaString = m_curCena.Format();
		CString strMsg;
		strMsg.Format("db_n5gmop::delete_db [idobj=%d,numop=%d/%d]=[idprod=%d,idmag=%d,%d][ilosc=%s,cena=%s]",
			m_idObj,m_nNumOp,m_nLP,m_idProd,m_idMag,m_idOpak,(LPCTSTR)oIloscString,(LPCTSTR)oCenaString);
		
		g_oLog << strMsg;
		TRACE(strMsg + "\n");
	}
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void db_n5gmop::_read_from_ado(ADODB::_RecordsetPtr & rpoN5GMOPRS)
{
	m_idObj		= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDOBJ);
	m_nVersion	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_VERSION);

	m_eTypOp	= en5gmtypop(_ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_TYPOP));
	m_nNumOp	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_NUMOP);
	m_nLP		= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_LP);
	m_curIlosc	= _ado_getcurrency(rpoN5GMOPRS,N5GMOP_FLD_ILOSC);
	m_curCena	= _ado_getcurrency(rpoN5GMOPRS,N5GMOP_FLD_CENA);
	m_curWartosc = _ado_getcurrency(rpoN5GMOPRS,N5GMOP_FLD_WARTOSC);
	m_idProd	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDPROD);
	m_idOpak	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDOPAK);
	m_idMag		= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDMAG);
	long idDost	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDDOST);
	long idDostLP= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_IDDOSTLP);
	m_idDost	= longlong(idDost,idDostLP);
	m_dDataWazn	= _ado_getdate(rpoN5GMOPRS,N5GMOP_FLD_DATAWAZN);
	m_nNumOpRel	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_NUMOPREL);
	m_nLPRel	= _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_LPREL);
	m_curPrzel	= _ado_getcurrency(rpoN5GMOPRS,N5GMOP_FLD_PREL);
}

void db_n5gmop::_fill_command_param(CADOCommand & roCommand)
{
	roCommand.AddInParam(SQLT_INT,(LPVOID)&m_idObj);

	roCommand.AddInParam(SQLT_INT,(LPVOID)&m_nVersion);

	long nTypOp = long(m_eTypOp);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&nTypOp);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_nNumOp);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_nLP);

	roCommand.AddInParam(SQLT_QUANTITY, (LPVOID)&m_curIlosc);
	roCommand.AddInParam(SQLT_MONEY, (LPVOID)&m_curCena);
	roCommand.AddInParam(SQLT_MONEY, (LPVOID)&m_curWartosc);

	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_idProd);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_idOpak);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_idMag);
	long idDost = hihyper(m_idDost);
	long idDostLP = lohyper(m_idDost);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idDost);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idDostLP);

	roCommand.AddInParam(SQLT_DATE, (LPVOID)&m_dDataWazn);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_nNumOpRel);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_nLPRel);

	roCommand.AddInParam(SQLT_QUANTITY, (LPVOID)&m_curPrzel);
}

