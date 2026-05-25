/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13

	a) nowa_dostawa dopisuje na koniec 
	b) stara_dostawa mo¿e dopisaæ siê w œrodek
	c) uporz¹dkowanie dostaw jest okreœlone przez _find_ordered_operation i musi byæ zgodne z kolejnoœci¹
		ich wpisywania - tzn. z kursorem w repair_all_products_one_stroke - inaczej bêd¹ asercje w nowa_dostawa
		-> ¿e powinna byæ na koncu a nie jest

	d) funkcje wydaj_* wydaj¹ wg ró¿nych schematów postêpowania. Wydanie odbywa siê z pojedyñczej operacji
		i nie skleja mo¿liwych wydañ o tych samych parametrach. 
		Pojedyñcze wywo³anie wydaj_* mo¿e nie zaspokoiæ potrzeb wydawania - nale¿y je wo³aæ tyle razy ile chcemy
		true - uda³o siê coœ wydaæ
		false - brak towaru (co oznacza ró¿nie w zale¿noœci od przyjêtej metody dzia³ania)
*/

#include "stdafx.h"
#include "engineincl.h"
#include "types_consts_gm.h"
#include "n5gmop.h"
#include "n5gmstan.h"
#include "n5gmopset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace navogm_server;

extern CNavoLog g_oLog;

void db_n5gmstan::insert_db(SCP<IObjectServer> & rpoObjectServerSP,
	ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak,eWorkMode eWM)
{
	ASSERT(m_idObj == 0);
	int iTypeId = (eWM == wm_gm) ? TYPEID_N5GMSTAN : TYPEID_N5PTSTAN;
	VERIFY(rpoObjectServerSP->GetUniqueIdent(iTypeId,&m_idObj) == S_OK);
	ASSERT(m_idObj != 0);

	CADOCommand oCommand(rpoConnection);
	
	_fill_command_param(oCommand,idMag,idProd,idOpak);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmstan_insert" : "n5ptstan_insert",true);

	if(g_oLog.IsHandleValid())
	{
		CString oIloscString = m_curIlosc.Format();
		CString oCenaString = m_oDostawaProp.get_cena().Format();

		CString strMsg;
		strMsg.Format("n5gmstan::insert_db [idobj=%d]=[idprod=%d,idmag=%d,%d][ilosc=%s,cena=%s]",
			m_idObj,idProd,idMag,idOpak,(LPCTSTR)oIloscString,(LPCTSTR)oCenaString);
		g_oLog << strMsg;
		
		TRACE(strMsg + "\n");
	}
}

void db_n5gmstan::update_db(ADODB::_ConnectionPtr & rpoConnection,
							long idMag,long idProd,long idOpak,eWorkMode eWM)
{
	ASSERT(m_idObj != 0);
	CADOCommand oCommand(rpoConnection);
	
	m_nVersion++;

	_fill_command_param(oCommand,idMag,idProd,idOpak);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmstan_update" : "n5ptstan_update",true);

	if(g_oLog.IsHandleValid())
	{
		CString oIloscString = m_curIlosc.Format();
		CString oCenaString = m_oDostawaProp.get_cena().Format();

		CString strMsg;
		strMsg.Format("n5gmstan::update_db [idobj=%d]=[idprod=%d,idmag=%d,%d][ilosc=%s,cena=%s]",
			m_idObj,idProd,idMag,idOpak,(LPCTSTR)oIloscString,(LPCTSTR)oCenaString);
		g_oLog << strMsg;
		
		TRACE(strMsg + "\n");
	}
}

void db_n5gmstan::delete_db(ADODB::_ConnectionPtr & rpoConnection,long idObj,eWorkMode eWM)
{
	ASSERT(idObj != 0);
	CADOCommand oCommand(rpoConnection);
	
	oCommand.AddInParam(SQLT_INT,(LPVOID)&idObj);

	oCommand.ExecProc((eWM == wm_gm) ? "n5gmstan_delete" : "n5ptstan_delete",true);

	if(g_oLog.IsHandleValid())
	{
		CString strMsg;
		strMsg.Format("n5gmstan::delete_db [%d]",idObj);
		g_oLog << strMsg;
		
		TRACE(strMsg + "\n");
	}
}

void db_n5gmstan::_fill_command_param(CADOCommand & roCommand,
									  long idMag,long idProd,long idOpak)
{
	roCommand.AddInParam(SQLT_INT,(LPVOID)&m_idObj);
	roCommand.AddInParam(SQLT_INT,(LPVOID)&m_nVersion);

	roCommand.AddInParam(SQLT_INT, (LPVOID)&idProd);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idOpak);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idMag);
	roCommand.AddInParam(SQLT_MONEY, (LPVOID)&m_oDostawaProp.m_curCena);
	roCommand.AddInParam(SQLT_QUANTITY, (LPVOID)&m_curIlosc);

	long idDost = hihyper(m_oDostawaProp.m_idDost);
	long idDostLP = lohyper(m_oDostawaProp.m_idDost);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idDost);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&idDostLP);

	roCommand.AddInParam(SQLT_DATE, (LPVOID)&m_oDostawaProp.m_dDataWazn);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_oDostawaProp.m_nNumOp_Dostawy);
	roCommand.AddInParam(SQLT_INT, (LPVOID)&m_oDostawaProp.m_nLP_Dostawy);

}

void db_n5gmstan::_read_from_ado(ADODB::_RecordsetPtr & rpoN5GMStanRS)
{
	m_idObj		= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_IDOBJ);
	m_nVersion	= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_VERSION);
	
	//idProd =	N5GMSTAN_FLD_IDPROD
	//idOpak =	N5GMSTAN_FLD_IDOPAK
	//idMag =	N5GMSTAN_FLD_IDMAG
	
	m_oDostawaProp.m_curCena	= _ado_getcurrency(rpoN5GMStanRS,N5GMSTAN_FLD_CENA);
	m_curIlosc					= _ado_getcurrency(rpoN5GMStanRS,N5GMSTAN_FLD_ILOSC);

	long idDost					= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_IDDOST);
	long idDostLP				= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_IDDOSTLP);
	m_oDostawaProp.m_idDost		= longlong(idDost,idDostLP);
	m_oDostawaProp.m_dDataWazn	= _ado_getdate(rpoN5GMStanRS,N5GMSTAN_FLD_DATAWAZN);
	m_oDostawaProp.m_nNumOp_Dostawy	= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_NUMOP);
	m_oDostawaProp.m_nLP_Dostawy= _ado_getlong(rpoN5GMStanRS,N5GMSTAN_FLD_LP);
}

//---------------------------------------------------------------------------------------
//szuka operacji o zadanym lub wiêkszym iddost,nnumop,lp

//sortowanie: numop, lp, iddost
//
//mo¿liwe jest alternatywne sortowanie:
//		iddost, numop, lp
//---------------------------------------------------------------------------------------


SCP<n5gmstan_operation> n5gmstan_element::_find_ordered_operation(supply_id idDost,long nNumOp,long nLP)
{
	SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
	while(poOperationSP.PointsObject())
	{
		if(poOperationSP->properties().get_numop() > nNumOp)
		{
			return poOperationSP;
		}

		if(poOperationSP->properties().get_numop() == nNumOp)
		{
			if(poOperationSP->properties().get_lp() > nLP)
			{
				return poOperationSP;
			}
		}
		
		poOperationSP = poOperationSP->m_poNextOperationSP;
	}
	return SCP<n5gmstan_operation>();
}


//---------------------------------------------------------------------------------------
// dodaje now¹ dostawê - taka dostawa nie mo¿e istnieæ w liœcie dostaw
//---------------------------------------------------------------------------------------
const n5gmstan_operation & n5gmstan_element::nowa_dostawa(const n5gmop & ron5gmop)
{
	//nowa = rozumiemy ¿e ostatnia
	ASSERT(_find_ordered_operation(ron5gmop.get_iddostawa(),
			ron5gmop.get_numop(),ron5gmop.get_lp()).PointsNull());

	SCP<n5gmstan_operation> poNewOperationSP = NewSCP(new n5gmstan_operation(ron5gmop),false);
	_link_operation(poNewOperationSP,SCP<n5gmstan_operation>());

	return *poNewOperationSP;
}

//---------------------------------------------------------------------------------------
// dodaje "star¹" dostawê - wtórn¹, która mo¿e istnieæ
// jesli znaleziona dostawa jest taka sama jak juz istniejaca to ja laczy
//---------------------------------------------------------------------------------------
const n5gmstan_operation & n5gmstan_element::stara_dostawa(const n5gmop & ron5gmop)
{
	SCP<n5gmstan_operation> poBeforeOperationSP = _find_ordered_operation(ron5gmop.get_iddostawa(),
			ron5gmop.get_numop(),ron5gmop.get_lp());
	
	if(poBeforeOperationSP.PointsObject())
	{
		if(poBeforeOperationSP->can_be_joined(ron5gmop))
		{
			poBeforeOperationSP->dodaj(ron5gmop.get_ilosc());
			return *poBeforeOperationSP;
		}
	}

	SCP<n5gmstan_operation> poNewOperationSP = NewSCP(new n5gmstan_operation(ron5gmop),false);
	_link_operation(poNewOperationSP,poBeforeOperationSP);

	return *poNewOperationSP;
}

//--------------------------------------------------------------
// dokonuje pojedynczego wydania z 1-szej operacji
//--------------------------------------------------------------
bool n5gmstan_element::wydaj_produkt_fifo(const quantity & rcurInpIlosc,
	quantity & rcurOutIlosc,n5gmdostawa_prop & roDostawaProp)
{
	if(m_poFirstOperationSP.PointsObject())
	{
		SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
		poOperationSP->wydaj(rcurInpIlosc,rcurOutIlosc);
		roDostawaProp = poOperationSP->properties();
			
		if(poOperationSP->is_void())
		{
			_unlink_operation(poOperationSP);
		}
		return true;
	}
	else
	{
		_handle_missing_quantity(rcurInpIlosc,rcurOutIlosc,roDostawaProp);
		return false;
	}
}

//--------------------------------------------------------------
// dokonuje pojedynczego wydania z operacji o zgodnym iddost
//--------------------------------------------------------------
bool n5gmstan_element::wydaj_produkt_iddost(supply_id idDost,const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp)
{
	SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
	while(poOperationSP.PointsObject())
	{
		if(poOperationSP->properties().get_iddostawa() == idDost)
		{
			poOperationSP->wydaj(rcurInpIlosc,rcurOutIlosc);
			roDostawaProp = poOperationSP->properties();
			
			if(poOperationSP->is_void())
			{
				_unlink_operation(poOperationSP);
			}
			return true;
		}
		poOperationSP = poOperationSP->m_poNextOperationSP;
	}

	_handle_missing_quantity(rcurInpIlosc,rcurOutIlosc,roDostawaProp);
	return false;
}

//--------------------------------------------------------------
// dokonuje pojedynczego wydania z operacji o zgodnym numop/lp
//--------------------------------------------------------------
bool n5gmstan_element::wydaj_produkt_numop(long nNumOp,long nLP,const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
		n5gmdostawa_prop & roDostawaProp)
{
	SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
	while(poOperationSP.PointsObject())
	{
		if(poOperationSP->properties().get_numop() == nNumOp && poOperationSP->properties().get_lp() == nLP)
		{
			poOperationSP->wydaj(rcurInpIlosc,rcurOutIlosc);
			roDostawaProp = poOperationSP->properties();
			
			if(poOperationSP->is_void())
			{
				_unlink_operation(poOperationSP);
			}
			return true;
		}
		poOperationSP = poOperationSP->m_poNextOperationSP;
	}
	
	_handle_missing_quantity(rcurInpIlosc,rcurOutIlosc,roDostawaProp);
	return false;
}

//--------------------------------------------------------------
// tworzy sztuczn¹ dostawê na braki - jest ona conajwy¿ej jedna
// i jest konsumowana przez flush
//--------------------------------------------------------------
void n5gmstan_element::_handle_missing_quantity(const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp)
{
	if(g_oLog.IsHandleValid())
	{
		g_oLog << "ERROR: missing quantity " + rcurInpIlosc.Format();
	}

	if(!m_bAllowNegativeQuantity)
	{
		return;
	}

	if(m_poArtificialOperationSP.PointsNull())
	{
		m_poArtificialOperationSP = n5gmstan_operation::create_artifical_operation();
		mark_need_flush();
	}
	m_poArtificialOperationSP->ujmij_zawsze(rcurInpIlosc);
	rcurOutIlosc = rcurInpIlosc;
	roDostawaProp = m_poArtificialOperationSP->properties();
}


bool n5gmstan_element::flush(eStanFlushMode eSFM,long nGlobalStartingNumOp,SCP<IObjectServer> & rpoObjectServerSP,
	ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak,eWorkMode eWM, bool bLargeGM)
{
	bool bWasDBOperation = false;

	//do³¹cz sztuczn¹ dostawê na koniec i przetwarzaj jak inne
	if(m_poArtificialOperationSP.PointsObject())
	{
		_link_operation(m_poArtificialOperationSP,SCP<n5gmstan_operation>());
		m_poArtificialOperationSP = 0;
	}

	//--- usuñ puste dostawy jeœli jakieœ zosta³y
	SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
	while(poOperationSP.PointsObject())
	{
		SCP<n5gmstan_operation> poNextOperationSP = poOperationSP->m_poNextOperationSP;
		if(poOperationSP->is_void())
		{
			_unlink_operation(poOperationSP);
		}
		poOperationSP = poNextOperationSP;
	}
		
	LPCTSTR lpTableName = (eWM == wm_gm)? "n5gmstan"  : "n5ptstan";

	switch(eSFM)
	{
	case sfm_just_append:
	{
		if(m_poFirstOperationSP.PointsObject())
		{
			//inicjujemy 1-sza operacja
			db_n5gmstan oNewDostawa(*m_poFirstOperationSP);

			//dodajemy wszystkie nastepne
			poOperationSP = m_poFirstOperationSP->m_poNextOperationSP;			
			while(poOperationSP.PointsObject())
			{
				oNewDostawa.dodaj(poOperationSP->get_ilosc());
				poOperationSP = poOperationSP->m_poNextOperationSP;
			}
			
			if(!oNewDostawa.is_void())
			{
				oNewDostawa.insert_db(rpoObjectServerSP,rpoConnection,idMag,idProd,idOpak,eWM);
				bWasDBOperation = true;
			}
		}
	}
	break;
	case sfm_diff_delivery:
	{
		//------ zsynchronizuj z baz¹ 
		ADODB::_RecordsetPtr pon5stanmagRS;
		CString oSQLQueryString;
		oSQLQueryString.Format("select * from %s where "
			"gms_pProd=%d and gms_pOpak=%d and gms_pMag=%d and (gms_nNumOp >= %d or gms_nNumOp = -1) " 
			"order by idObj",lpTableName,idProd,idOpak,idMag,nGlobalStartingNumOp);
		pon5stanmagRS = _ado_openRS(oSQLQueryString, rpoConnection, bLargeGM);

		poOperationSP = m_poFirstOperationSP;

		while(poOperationSP.PointsObject())
		{
			if(!pon5stanmagRS->EOF)
			{
				//wykonaj update
				db_n5gmstan oExistingDostawa(pon5stanmagRS);
				if(!(oExistingDostawa == (*poOperationSP)))
				{
					((n5gmstan_operation & )oExistingDostawa) = (*poOperationSP);
					oExistingDostawa.update_db(rpoConnection,idMag,idProd,idOpak,eWM);
					bWasDBOperation = true;
				}
				pon5stanmagRS->MoveNext();
			}
			else
			{
				//wiêcej dostaw ni¿ w bazie - insert
				db_n5gmstan oNewDostawa(*poOperationSP);
				oNewDostawa.insert_db(rpoObjectServerSP,rpoConnection,idMag,idProd,idOpak,eWM);
				bWasDBOperation = true;
			}

			poOperationSP = poOperationSP->m_poNextOperationSP;
		}
		
		//usuñ z bazy nadmiarowe
		while(!pon5stanmagRS->EOF)
		{
			db_n5gmstan::delete_db(rpoConnection,_ado_getlong(pon5stanmagRS,N5GMSTAN_FLD_IDOBJ),eWM);
			bWasDBOperation = true;
			pon5stanmagRS->MoveNext();
		}
	}	
	break;
	case sfm_just_qty:
	{
		//------ zsynchronizuj z baz¹ 
		ADODB::_RecordsetPtr pon5stanmagRS;
		CString oSQLQueryString;
		oSQLQueryString.Format("select * from %s where "
			"gms_pProd=%d and gms_pOpak=%d and gms_pMag=%d order by idObj",lpTableName,idProd,idOpak,idMag);
		pon5stanmagRS = _ado_openRS(oSQLQueryString,rpoConnection, bLargeGM);

		if(m_poFirstOperationSP.PointsObject())
		{
			poOperationSP = m_poFirstOperationSP;

			quantity curTotalQty = curZero;
			while(poOperationSP.PointsObject())
			{
				curTotalQty += poOperationSP->get_ilosc();
				poOperationSP = poOperationSP->m_poNextOperationSP;
			}
			if(!pon5stanmagRS->EOF)
			{
				//wykonaj update
				db_n5gmstan oExistingDostawa(pon5stanmagRS);
				bool bPerformUpdate = ((oExistingDostawa.get_ilosc() != curTotalQty) != FALSE);
				if(!bPerformUpdate)
				{
					bPerformUpdate = !(oExistingDostawa == (*m_poFirstOperationSP));
				}
				if(bPerformUpdate)
				{
					oExistingDostawa.set_ilosc(curTotalQty);
					oExistingDostawa.update_db(rpoConnection,idMag,idProd,idOpak,eWM);
					bWasDBOperation = true;
				}
				pon5stanmagRS->MoveNext();
			}
			else
			{
				//wiêcej dostaw ni¿ w bazie - insert
				db_n5gmstan oNewDostawa(*m_poFirstOperationSP);
				oNewDostawa.set_ilosc(curTotalQty);
				oNewDostawa.insert_db(rpoObjectServerSP,rpoConnection,idMag,idProd,idOpak,eWM);
				bWasDBOperation = true;
			}		
		}
		//usuñ z bazy nadmiarowe
		while(!pon5stanmagRS->EOF)
		{
			db_n5gmstan::delete_db(rpoConnection,_ado_getlong(pon5stanmagRS,N5GMSTAN_FLD_IDOBJ),eWM);
			bWasDBOperation = true;
			pon5stanmagRS->MoveNext();
		}	
	}
	break;
	}
	
	return bWasDBOperation;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

bool n5gmstan_element::write_as_bo(long iNumOpBO,long iLP,long & rIdObj,SCP<IObjectServer> & rpoObjectServerSP,
	ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak)
{
	bool bWasDBOp = false;
	//do³¹cz sztuczn¹ dostawê na koniec i przetwarzaj jak inne
	if(m_poArtificialOperationSP.PointsObject())
	{
		_link_operation(m_poArtificialOperationSP,SCP<n5gmstan_operation>());
		m_poArtificialOperationSP = 0;
	}

	//--- usuñ puste dostawy jeœli jakieœ zosta³y
	SCP<n5gmstan_operation> poOperationSP = m_poFirstOperationSP;
	while(poOperationSP.PointsObject())
	{
		SCP<n5gmstan_operation> poNextOperationSP = poOperationSP->m_poNextOperationSP;
		if(poOperationSP->is_void())
		{
			_unlink_operation(poOperationSP);
		}
		poOperationSP = poNextOperationSP;
	}

	//-- zapisz w basie
	poOperationSP = m_poFirstOperationSP;			
	while(poOperationSP.PointsObject())
	{
		supply_id i64Supply = poOperationSP->properties().get_iddostawa();
		long idDost = hihyper(i64Supply);
		long idDostLP = lohyper(i64Supply);

		db_n5gmop oDBGMOP(poOperationSP->properties().get_numop(),
				  poOperationSP->properties().get_lp(),
				  idProd,idOpak,N5GMOP_P_CZ_IZ_BO,
				  poOperationSP->get_ilosc(),
				  poOperationSP->properties().get_cena(),idMag,
				  idDost,idDostLP,
				  (navogm_date)poOperationSP->properties().get_datawazn(),
				  iNumOpBO,iLP,COleCurrency(1,0));

		//wersja zakomentowana skleja wszystko do jedej operacji
		//i wymaga mapowania pola nnumoprel dla operacji powyzej bordera typu 3
		//co wiecej mapowanie nie jest do konca jednoznaczne
		//
		//db_n5gmop oDBGMOP(iNumOpBO,iLP,
		//		  idProd,idOpak,N5GMOP_P_CZ_IZ_BO,
		//		  poOperationSP->get_ilosc(),
		//		  poOperationSP->properties().get_cena(),idMag,
		//		  idDost,idDostLP,
		//		  (navogm_date)poOperationSP->properties().get_datawazn(),
		//		  iNumOpBO,iLP,COleCurrency(1,0));

		oDBGMOP.insert_db(rpoObjectServerSP,rpoConnection,wm_gm);
		bWasDBOp = true;
		poOperationSP = poOperationSP->m_poNextOperationSP;
	}

	return bWasDBOp;
}

SCP<n5gmstan_element> n5gmstan_glob::get_dostawy(long idMag,long idProd,long idOpak)
{
	hyper_key hypKey = _compose_key(idMag,idProd,idOpak);

	SCP<n5gmstan_element> poDostawaSetSP;
	
	if(!m_oDostawaSetMap.Lookup(hypKey,poDostawaSetSP))
	{
		poDostawaSetSP = NewSCP(new n5gmstan_element(m_bAllowNegativeQuantity),false);
		m_oDostawaSetMap.SetAt(hypKey,poDostawaSetSP);
	}

	return poDostawaSetSP;
}

void n5gmstan_glob::flush(bool bForce,eStanFlushMode eSFM,SCP<IObjectServer> & rpoObjectServerSP,
						  ADODB::_ConnectionPtr & rpoConnection, bool bLargeGM)
{
	ado_trans oADOTrans(rpoConnection, !bLargeGM);

	if(bForce)
	{
		CADOCommand oDeleteAllStanCommand(oADOTrans.get_connection());
		CString strTableName = (m_eWorkMode == wm_gm) ? "n5gmstan" : "n5ptstan";
		oDeleteAllStanCommand.ExecDirect("truncate table " + strTableName, true);
	}

	POSITION pos = m_oDostawaSetMap.GetStartPosition();
	while(pos)
	{
		hyper_key hypKey;
		SCP<n5gmstan_element> poDostawaSetSP;
		m_oDostawaSetMap.GetNextAssoc(pos,hypKey,poDostawaSetSP);

		bool bNeedFlush = bForce || poDostawaSetSP->is_flush_needed();

		if(bNeedFlush)
		{

			long idMag;
			long idProd;
			long idOpak;
			_crack_key(hypKey,idMag,idProd,idOpak);
			bool bWasFlush = poDostawaSetSP->flush(eSFM,m_nGlobalStartingNumOp,rpoObjectServerSP, oADOTrans.get_connection(),
				idMag,idProd,idOpak, m_eWorkMode, bLargeGM);

#ifdef _DEBUG
			{
				//byæ mo¿e zadanie flusha'a jest nadmiarowe, ale jeœli by³ flush to zadanie 
				//flusha musi byc zgloszone - inaczej to jest blad!!
				//zadanie flusha moze nie byc zgloszone tylko gdy bForce
				if(bWasFlush && !bForce)
				{
					ASSERT(poDostawaSetSP->is_flush_needed());
				}
			}
#endif
		}
/*
		if(poDostawaSetSP->is_missing_quantity())
		{
			long idMag;
			long idProd;
			long idOpak;
			_crack_key(hypKey,idMag,idProd,idOpak);
			m_roLogger.on_error(cgms_exception(cgms_exception::sec_not_enough_quantity,
				0,0,0,idProd,idOpak,idMag,poDostawaSetSP->get_missing_quantity()));
		}
*/
	}
}

void n5gmstan_glob::write_as_bo(long iNumOpBO,SCP<IObjectServer> & rpoObjectServerSP,
								ADODB::_ConnectionPtr & rpoConnection)
{
	long iLP = 1;
	long idObj = 1;
	POSITION pos = m_oDostawaSetMap.GetStartPosition();
	while(pos)
	{
		hyper_key hypKey;
		SCP<n5gmstan_element> poDostawaSetSP;
		m_oDostawaSetMap.GetNextAssoc(pos,hypKey,poDostawaSetSP);

		long idMag;
		long idProd;
		long idOpak;
		_crack_key(hypKey,idMag,idProd,idOpak);

		if(poDostawaSetSP->write_as_bo(iNumOpBO,iLP,idObj,rpoObjectServerSP,
			rpoConnection,idMag,idProd,idOpak))
		{
			iLP++;
		}
	}
}


