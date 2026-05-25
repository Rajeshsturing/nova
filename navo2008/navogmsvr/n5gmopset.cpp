/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13
	REV:KB:2005-10-09
*/
#include "stdafx.h"
#include "engineincl.h"
#include "types_consts_gm.h"
#include "n5gmop.h"
#include "n5gmopset.h"
#include "n5gmstan.h"
#include "mem_db.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNavoLog g_oLog;

using namespace navogm_server;

n5gmop_document::n5gmop_document(csrvlogger & roLogger,long nGlobalStartingNumOp,eWorkMode eWM) :
	m_roLogger(roLogger),
	m_nGlobalStartingNumOp(nGlobalStartingNumOp),
	m_curWartoscDok(curZero),
	m_eWorkMode(eWM)
{
}

n5gmop_document::eload_result n5gmop_document::load_single_lp(
	n5gmstan_glob & roStanMag,ADODB::_RecordsetPtr & rpoN5GMOPRS,long & riLoadedLP)
{
	m_oGMOP_BuffArray.RemoveAll();

	ASSERT(!rpoN5GMOPRS->EOF);

	//------- wczytujemy 1-szy rekord operacji
	SCP<db_n5gmop> poGMOPSP = NewSCP(new db_n5gmop(rpoN5GMOPRS),false);
	TRACE("loaded [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());

	ASSERT(riLoadedLP == 0);
	riLoadedLP = poGMOPSP->get_lp();
	ASSERT(riLoadedLP != 0);

	load_output_db_n5gmop_lp(poGMOPSP->get_lp(),poGMOPSP);

	SCP<n5gmop> poLastInBuffGMOPSP = NewSCP(new n5gmop(*poGMOPSP),false);
	m_oGMOP_BuffArray.Add(poLastInBuffGMOPSP);

	rpoN5GMOPRS->MoveNext();

	while(true)
	{
		//uwaga! kolejnoœæ warunków jest wa¿na
		//czy koniec recordseta ?
		if(rpoN5GMOPRS->EOF)
		{
			TRACE("======= EOF ==========\n");
			return lr_eof;
		}

		//czy to ju¿ nastêpny dokument (numop) ?
		if(poLastInBuffGMOPSP->get_numop() != _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_NUMOP))
		{
			TRACE("======= EOD [%d] ==========\n",poLastInBuffGMOPSP->get_numop());
			return lr_eod;
		}

		//czy to ju¿ nastêpna operacja (lp) ?
		if(poLastInBuffGMOPSP->get_lp() != _ado_getlong(rpoN5GMOPRS,N5GMOP_FLD_LP))
		{
			TRACE("======= EOLP [%d,%d] ==========\n",poLastInBuffGMOPSP->get_numop(),poLastInBuffGMOPSP->get_lp());
			return lr_eolp;
		}
		
		//ta sama operacja - wczytaj
		poGMOPSP = NewSCP(new db_n5gmop(rpoN5GMOPRS),false);
		
		TRACE("loaded [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());
		
		load_output_db_n5gmop_lp(poGMOPSP->get_lp(),poGMOPSP);
		
	
		
		//spróbuj j¹ skompressowaæ
		if(poLastInBuffGMOPSP->will_join(*poGMOPSP,_get_global_starting_numop()))
		{
			//zaznacz tylko jesli sie roznia
			if( (poLastInBuffGMOPSP->get_idmag()  != poGMOPSP->get_idmag()) ||
				(poLastInBuffGMOPSP->get_idprod() != poGMOPSP->get_idprod()) ||
				(poLastInBuffGMOPSP->get_idopak() != poGMOPSP->get_idopak())
			)
			{
				roStanMag.get_dostawy(poLastInBuffGMOPSP->get_idmag(),
						poLastInBuffGMOPSP->get_idprod(),poLastInBuffGMOPSP->get_idopak())->mark_need_flush();
				roStanMag.get_dostawy(poGMOPSP->get_idmag(),
						poGMOPSP->get_idprod(),poGMOPSP->get_idopak())->mark_need_flush();
			}
			poLastInBuffGMOPSP->do_join(*poGMOPSP,_get_global_starting_numop());
		}
		else
		{
			poLastInBuffGMOPSP = NewSCP(new n5gmop(*poGMOPSP),false);
			m_oGMOP_BuffArray.Add(poLastInBuffGMOPSP);
		}

		rpoN5GMOPRS->MoveNext();
	}
}

void n5gmop_document::load_single_mem_lp(n5gmstan_glob & roStanMag,SCP<mem_lp> & rpoMemLPSP)
{
	ASSERT(rpoMemLPSP.PointsObject());

	m_oGMOP_BuffArray.RemoveAll();
	long iter = 0;
	
	ASSERT(rpoMemLPSP->get_record(iter).PointsObject());


	//------- wczytujemy 1-szy rekord operacji
	SCP<db_n5gmop> poGMOPSP = rpoMemLPSP->get_record(iter);
//	TRACE("preprocessing [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());

	load_output_db_n5gmop_lp(poGMOPSP->get_lp(),poGMOPSP);

	SCP<n5gmop> poLastInBuffGMOPSP = NewSCP(new n5gmop(*poGMOPSP),false);
	m_oGMOP_BuffArray.Add(poLastInBuffGMOPSP);

	iter++;

	while(true)
	{
		if(rpoMemLPSP->get_record(iter).PointsNull())
		{
			return;
		}

		//ta sama operacja - wczytaj
		poGMOPSP = rpoMemLPSP->get_record(iter);
	//	TRACE("preprocessing [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());
		load_output_db_n5gmop_lp(poGMOPSP->get_lp(),poGMOPSP);
		
		//spróbuj j¹ skompressowaæ
		if(poLastInBuffGMOPSP->will_join(*poGMOPSP,_get_global_starting_numop()))
		{
			//zaznacz tylko jesli sie roznia
			if( (poLastInBuffGMOPSP->get_idmag()  != poGMOPSP->get_idmag()) ||
				(poLastInBuffGMOPSP->get_idprod() != poGMOPSP->get_idprod()) ||
				(poLastInBuffGMOPSP->get_idopak() != poGMOPSP->get_idopak())
			)
			{
				roStanMag.get_dostawy(poLastInBuffGMOPSP->get_idmag(),
						poLastInBuffGMOPSP->get_idprod(),poLastInBuffGMOPSP->get_idopak())->mark_need_flush();
				roStanMag.get_dostawy(poGMOPSP->get_idmag(),
						poGMOPSP->get_idprod(),poGMOPSP->get_idopak())->mark_need_flush();
			}
			poLastInBuffGMOPSP->do_join(*poGMOPSP,_get_global_starting_numop());
		}
		else
		{
			poLastInBuffGMOPSP = NewSCP(new n5gmop(*poGMOPSP),false);
			m_oGMOP_BuffArray.Add(poLastInBuffGMOPSP);
		}

		iter++;
	}
}

void n5gmop_document::move_single_dbgmop(n5gmstan_glob & roStanMag,SCP<db_n5gmop> poGMOPSP)
{
	//zarejestruj dostawê
	SCP<n5gmstan_element> poDostawaSetSP = 
		roStanMag.get_dostawy(poGMOPSP->get_idmag(),poGMOPSP->get_idprod(),poGMOPSP->get_idopak());
	
	poDostawaSetSP->stara_dostawa(*poGMOPSP);

	add_to_output_db_n5gmop_lp(poGMOPSP->get_lp(),poGMOPSP);

	m_curWartoscDok += poGMOPSP->get_wartosc();
}

void n5gmop_document::flush_document(n5gmstan_glob & roStanMag,SCP<IObjectServer> & rpoObjectServerSP,
									 ADODB::_ConnectionPtr & oConnectionPtr, bool bLargeGM)
{ 
	ado_trans oADOTrans(oConnectionPtr, !bLargeGM);

	//insert or update
	long iMaxLP = m_oGMOPLP_Output_Array.GetUpperBound();
	for(long iLP = 1; iLP <= iMaxLP; iLP++)
	{
		//osobno dla kazdego lp
		long iOutDBInx = get_current_output_index_lp(iLP);
		
		long iter = 0;
		for(iter = 0; iter < iOutDBInx; iter++)
		{
			SCP<db_n5gmop> poGMOPSP = get_output_at_lp(iLP,iter);
			if(poGMOPSP->is_dbmodified())
			{
				roStanMag.get_dostawy(poGMOPSP->get_idmag(),
					poGMOPSP->get_idprod(),poGMOPSP->get_idopak())->mark_need_flush();

				if(poGMOPSP->get_idobj() == 0)
				{
					poGMOPSP->insert_db(rpoObjectServerSP,oADOTrans.get_connection(),m_eWorkMode);
				}
				else
				{
					poGMOPSP->update_db(oADOTrans.get_connection(),m_eWorkMode);	
				}
				
			}
		}
		
		//delete rest
		for(;iter <= get_complete_upper_bound_lp(iLP);iter++)
		{
			SCP<db_n5gmop> poGMOPSP = get_output_at_lp(iLP,iter);
			ASSERT(poGMOPSP->get_idobj() != 0);

			roStanMag.get_dostawy(poGMOPSP->get_idmag(),
				poGMOPSP->get_idprod(),poGMOPSP->get_idopak())->mark_need_flush();

			poGMOPSP->delete_db(oADOTrans.get_connection(),m_eWorkMode);
		}

		ASSERT(iOutDBInx == get_current_output_index_lp(iLP));
	}
}


void n5gmop_document::flush_document_mem(n5gmstan_glob & roStanMag,
	SCP<IObjectServer> & rpoObjectServerSP,CComPtr<mem_dok> poMemDokSP)
{
	//insert or update
	long iMaxLP = m_oGMOPLP_Output_Array.GetUpperBound();
	
	long iLP = 1;
	
	for(iLP = 1; iLP <= iMaxLP; iLP++)
	{
		SCP<mem_lp> poMemLPSP;
		
		if(poMemDokSP->is_lp(iLP))
		{
			poMemLPSP = poMemDokSP->get_lp(iLP);
			
			if(poMemLPSP.PointsNull())
			{
				poMemLPSP = NewSCP<mem_lp>(new mem_lp());
				poMemDokSP->set_lp(iLP,poMemLPSP);
			}
		}
		
		if(poMemLPSP.PointsNull())
		{
			poMemLPSP = NewSCP<mem_lp>(new mem_lp());
			poMemDokSP->set_lp(iLP,poMemLPSP);
		}

		//osobno dla kazdego lp
		long iOutDBInx = get_current_output_index_lp(iLP);
		
		long iter = 0;
		
		for(iter = 0; iter < iOutDBInx; iter++)
		{
			SCP<db_n5gmop> poGMOPSP = get_output_at_lp(iLP,iter);
			poMemLPSP->set_record(iter,poGMOPSP);

			//roStanMag.get_dostawy(poGMOPSP->get_idmag(),
			//		poGMOPSP->get_idprod(),poGMOPSP->get_idopak())->mark_need_flush();
		}
		
		//todo: to tak nie moze byc - trzeba je przeniesc
		//operacji do skasowania
		poMemLPSP->set_size(iter);
	}
	
	//todo: to tak nie moze byc - trzeba je przeniesc
	//operacji do skasowania
	poMemDokSP->set_size(iLP);
}


void n5gmop_document::process_single_lp(n5gmstan_glob & roStanMag,long iLP)
{
	long nPrevPosDBInx = get_current_output_index_lp(iLP);

	for(long iter = 0; iter <= m_oGMOP_BuffArray.GetUpperBound(); iter++)
	{
		const n5gmop & roGMOP = * m_oGMOP_BuffArray[iter];
		
		if(roGMOP.get_typop() != N5GMOP_K_STORNO_WART)
		{
			if(roGMOP.is_void_gmop())
			{
				continue;
			}
		}

		switch(roGMOP.get_typop())
		{
		case N5GMOP_P_CZ_IZ_DS:
		case N5GMOP_P_CZ_IZ_BO:
			_process_independent_supply(roStanMag,roGMOP,true);
		break;
		case N5GMOP_R_CA_IZ_DF:
			_process_ordered_expend(roStanMag,roGMOP);
		break;
		case N5GMOP_R_CA_IZ_DZ:
			_process_numop_rel_expend(roStanMag,roGMOP);
		break;
		case N5GMOP_R_CA_IZ_DI:
			_process_iddost_rel_expend(roStanMag,roGMOP,false);
		break;
		case N5GMOP_K_CA_IA_DI:
			_process_iddost_rel_expend(roStanMag,roGMOP,true);
		break;
		case N5GMOP_P_CA_IA_DS:
			_process_self_supply(roStanMag,roGMOP,nPrevPosDBInx);
		break;
		case N5GMOP_R_CZ_IZ_DX:
		case N5GMOP_K_STORNO_WART:
			_process_to_output(roGMOP);
		break;
		case N5GMOP_P_CP_IZ_DS:
			_process_product_phase1(m_oGMOP_BuffArray[iter]);
		break;

		default:
			ASSERT(false);
		}
	}
}

void n5gmop_document::finish_document(n5gmstan_glob & roStanMag)
{
	//w tym momencie wartoœæ dokumentu jest ju¿ ustabilizowana
#ifdef _DEBUG
	price old_curWartoscDok = m_curWartoscDok;
#endif

	for(long iter = 0; iter <= m_oGMOPWyroby_BuffArray.GetUpperBound(); iter++)
	{
		const n5gmop & roGMOPWyrob = *m_oGMOPWyroby_BuffArray[ iter ];
		ASSERT(!roGMOPWyrob.is_void_gmop());
		ASSERT(roGMOPWyrob.get_typop() == N5GMOP_P_CP_IZ_DS);
		
		_process_product_phase2(roStanMag,roGMOPWyrob);
	}

#ifdef _DEBUG
	ASSERT(old_curWartoscDok == m_curWartoscDok);
#endif
}

//------------------------------------------------------------------------------------------
// przetwarza niezale¿n¹ dostawê
//
// 1. rejestruje now¹ dostawê w bie¿¹cych dostawach
// 2. przepisuje na wyjœcie
//------------------------------------------------------------------------------------------

void n5gmop_document::_process_independent_supply(n5gmstan_glob & roStanMag,
	const n5gmop & roGMOP,bool bUpdateWartosc)
{
	//zarejestruj dostawê
	SCP<n5gmstan_element> poDostawaSetSP = roStanMag.get_dostawy(
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());
	
	const n5gmstan_operation & roOperacjaNowaDostawa = poDostawaSetSP->nowa_dostawa(roGMOP);
	
	ASSERT(roOperacjaNowaDostawa.get_ilosc() == roGMOP.get_ilosc());
	ASSERT(roOperacjaNowaDostawa.properties().get_numop() == roGMOP.get_numop());
	ASSERT(roOperacjaNowaDostawa.properties().get_lp() == roGMOP.get_lp());

	SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
		roGMOP.get_lp(),
		roGMOP,
		roOperacjaNowaDostawa.properties(),
		roOperacjaNowaDostawa.properties().get_numop(),
		roOperacjaNowaDostawa.properties().get_lp(),
		roOperacjaNowaDostawa.get_ilosc()
		);
	
	if(bUpdateWartosc)
	{
		m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
	}
}

//------------------------------------------------------------------------------------------
// przetwarza dostawê wtórn¹
//
// 1. rejestruje w bie¿¹cych dostawach - stara siê j¹ po³¹czyæ z istniej¹c¹ (robi to stara dostawa)
// 2. przepisuje na wyjœcie
//------------------------------------------------------------------------------------------

void n5gmop_document::_process_secondary_supply(n5gmstan_glob & roStanMag,
	const n5gmop & roGMOP,bool bUpdateWartosc)
{
	//zarejestruj dostawê
	SCP<n5gmstan_element> poDostawaSetSP = roStanMag.get_dostawy(
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());
	
	const n5gmstan_operation & roOperacjaDostawa = poDostawaSetSP->stara_dostawa(roGMOP);

	ASSERT(roOperacjaDostawa.get_ilosc() >= roGMOP.get_ilosc());

	SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
			roGMOP.get_lp(),
			roGMOP,
			roOperacjaDostawa.properties(),
			roOperacjaDostawa.properties().get_numop(),
			roOperacjaDostawa.properties().get_lp(),
			roGMOP.get_ilosc()
	);
	
	if(bUpdateWartosc)
	{
		m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
	}
}

//------------------------------------------------------------------------------------------
// przepisuje na wyjœcie, zwiêksza wartoœæ dokumentu
// np. sama robocizna
//
// 1. przepisuje na wyjœcie
//------------------------------------------------------------------------------------------

void n5gmop_document::_process_to_output(const n5gmop & roGMOP)
{
	n5gmdostawa_prop oDostawaProp(roGMOP.get_numop_rel(),roGMOP.get_lp_rel(),
		roGMOP.get_iddostawa(),roGMOP.get_cena(),roGMOP.get_datawazn());
	
	ASSERT(roGMOP.get_numop_rel() == oDostawaProp.get_numop());
	ASSERT(roGMOP.get_lp_rel() == oDostawaProp.get_lp());

	SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
		roGMOP.get_lp(),
		roGMOP,
		oDostawaProp,
		oDostawaProp.get_numop(),
		oDostawaProp.get_lp(),
		roGMOP.get_ilosc()
	);
	
	ASSERT(poDBN5GMOPSP.PointsObject());

	m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
}

//------------------------------------------------------------------------------------------
// przetwarza dostawê na podstawie rozchodu w tej samej operacji (numop/lp)
//
// MM+ i pochodne
//
// dla ka¿dego rozbicia wskazanego rozchodu robi dostawê
// za pomoc¹ secondary supply
//------------------------------------------------------------------------------------------

void n5gmop_document::_process_self_supply(n5gmstan_glob & roStanMag,const n5gmop & roGMOP,
	long & rnPreviousDBInx)
{
	//zrób z rozchodów nowe dostawy
	ASSERT(rnPreviousDBInx >= 0);
	
	long nStarInx = get_current_output_index_lp(roGMOP.get_lp());
	
	for(long iter = rnPreviousDBInx; iter < nStarInx; iter++)
	{
		//weŸ rozbicie
		SCP<db_n5gmop> poDBGMOPSP = get_output_at_lp(roGMOP.get_lp(),iter);
		
		n5gmop oMPOPBase(*poDBGMOPSP);
		//zmieñ magazyn i znak iloœci na okreœlony w operacji
		oMPOPBase.set_idmag(roGMOP.get_idmag());
		oMPOPBase.set_ilosc(-poDBGMOPSP->get_ilosc());
		oMPOPBase.set_typop(roGMOP.get_typop());
		oMPOPBase.set_iddostawa(poDBGMOPSP->get_iddostawa());
		oMPOPBase.set_numop_rel(roGMOP.get_numop());
		oMPOPBase.set_lp_rel(roGMOP.get_lp());

		_process_secondary_supply(roStanMag,oMPOPBase,true);
	}
	
	rnPreviousDBInx = get_current_output_index_lp(roGMOP.get_lp());
}

//------------------------------------------------------------------------------------------
// przetwarza rozchód wg FIFO
//
// pobiera z aktualnych dostaw iloœci, a¿ do wyczerpania iloœci wskazanej w db_n5gmop
// tworzy rozchód na ka¿d¹ z takich operacji (rozbicie)
//
//------------------------------------------------------------------------------------------

void n5gmop_document::_process_ordered_expend(n5gmstan_glob & roStanMag,const n5gmop & roGMOP)
{
	if(roGMOP.get_numop_rel() > 0 && roGMOP.get_numop_rel() < _get_global_starting_numop())
	{
		TRACE("SKIPPED::ordered_rel [%d,%d]=[%d,%d,%d]\n",
			roGMOP.get_numop(),roGMOP.get_lp(),
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());

		_process_to_output(roGMOP);
	}
	else
	{
		SCP<n5gmstan_element> poDostawaSetSP = roStanMag.get_dostawy(
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());
		
		quantity curIlosc = - roGMOP.get_ilosc();
		
		//generuj kolejne rozbicia
		//OPT: mo¿na ewentualnie sklejaæ powsta³e dostawy, jeœli "n5gmdostawa_prop" jest taka sama
		while(curIlosc > curZero)
		{
			quantity curIloscWydana(curZero);
			n5gmdostawa_prop oDostawaProp;
			if(!poDostawaSetSP->wydaj_produkt_fifo(curIlosc,curIloscWydana,oDostawaProp))
			{
				m_roLogger.on_error(cgms_exception(cgms_exception::sec_not_enough_quantity,
					roGMOP.get_numop(),roGMOP.get_lp(),0,
					roGMOP.get_idprod(),roGMOP.get_idopak(),roGMOP.get_idmag(),
						poDostawaSetSP->get_missing_quantity()));
			}
			
			ASSERT(curIloscWydana > curZero);
			
			SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
				roGMOP.get_lp(),
				roGMOP,
				oDostawaProp,
				oDostawaProp.get_numop(),
				oDostawaProp.get_lp(),
				-curIloscWydana
			);
			
			ASSERT(poDBN5GMOPSP.PointsObject());

			m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
			
			curIlosc -= curIloscWydana;
		}
	}
}

//------------------------------------------------------------------------------------------
// przetwarza rozchód ze wskazanej dostawy (numop/lp)
//
// pobiera z aktualnych dostaw iloœci, a¿ do wyczerpania iloœci wskazanej w db_n5gmop
// tworzy rozchód na ka¿d¹ z takich operacji (rozbicie)
//
//------------------------------------------------------------------------------------------
void n5gmop_document::_process_numop_rel_expend(n5gmstan_glob & roStanMag,const n5gmop & roGMOP)
{
	if(roGMOP.get_numop_rel() > 0 && roGMOP.get_numop_rel() < _get_global_starting_numop())
	{
		TRACE("SKIPPED::numop_rel [%d,%d]=[%d,%d,%d]\n",
			roGMOP.get_numop(),roGMOP.get_lp(),
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());

		_process_to_output(roGMOP);
	}
	else
	{
		SCP<n5gmstan_element> poDostawaSetSP = roStanMag.get_dostawy(
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());
		
		quantity curIlosc = - roGMOP.get_ilosc();
	
		//generuj kolejne rozbicia
		//OPT: mo¿na ewentualnie sklejaæ powsta³e dostawy, jeœli "n5gmdostawa_prop" jest taka sama

		while(curIlosc > curZero)
		{
			quantity curIloscWydana(curZero);
			n5gmdostawa_prop oDostawaProp;

			if(!poDostawaSetSP->wydaj_produkt_numop(roGMOP.get_numop_rel(),roGMOP.get_lp_rel(),
					curIlosc,curIloscWydana,oDostawaProp))
			{
				m_roLogger.on_error(cgms_exception(cgms_exception::sec_not_enough_quantity,
					roGMOP.get_numop(),roGMOP.get_lp(),0,
					roGMOP.get_idprod(),roGMOP.get_idopak(),roGMOP.get_idmag(),
						poDostawaSetSP->get_missing_quantity()));
			}
			
			//commented out to simplify debugging but valid ASSERT(oDostawaProp.get_numop() == roGMOP.get_numop_rel());
			//commented out to simplify debugging but valid ASSERT(oDostawaProp.get_lp() == roGMOP.get_lp_rel());

			SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
				roGMOP.get_lp(),
				roGMOP,
				oDostawaProp,
				roGMOP.get_numop_rel(),
				roGMOP.get_lp_rel(),
				-curIloscWydana
			);
			
			ASSERT(poDBN5GMOPSP.PointsObject());

			m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
			curIlosc -= curIloscWydana;
		}
	}
}

//------------------------------------------------------------------------------------------
// przetwarza rozchód ze wskazanej dostawy (iddost)
//
// pobiera z aktualnych dostaw iloœci, a¿ do wyczerpania iloœci wskazanej w db_n5gmop
// tworzy rozchód na ka¿d¹ z takich operacji (rozbicie)
//
//------------------------------------------------------------------------------------------
void n5gmop_document::_process_iddost_rel_expend(n5gmstan_glob & roStanMag,
	const n5gmop & roGMOP,bool bAutoIlosc)
{
	if(roGMOP.get_numop_rel() > 0 && roGMOP.get_numop_rel() < _get_global_starting_numop())
	{
		TRACE("SKIPPED::iddost_rel [%d,%d]=[%d,%d,%d]\n",
			roGMOP.get_numop(),roGMOP.get_lp(),
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());

		_process_to_output(roGMOP);
	}
	else
	{
		SCP<n5gmstan_element> poDostawaSetSP = roStanMag.get_dostawy(
			roGMOP.get_idmag(),roGMOP.get_idprod(),roGMOP.get_idopak());
		
		quantity curIlosc = (bAutoIlosc) ? (curEverything) : (- roGMOP.get_ilosc());
		bool bWasAny = false;

		//generuj kolejne rozbicia
		//OPT: mo¿na ewentualnie sklejaæ powsta³e dostawy, jeœli "n5gmdostawa_prop" jest taka sama
		while(curIlosc > curZero)
		{
			quantity curIloscWydana(curZero);
			n5gmdostawa_prop oDostawaProp;

			if(!poDostawaSetSP->wydaj_produkt_iddost(roGMOP.get_iddostawa(),curIlosc,curIloscWydana,oDostawaProp))
			{
				if(!bWasAny)
				{
					m_roLogger.on_error(cgms_exception(cgms_exception::sec_no_such_supply,
						roGMOP.get_numop(),roGMOP.get_lp(),0,
						roGMOP.get_idprod(),roGMOP.get_idopak(),roGMOP.get_idmag(),
							curZero));
				}
				else
				{
					if(bAutoIlosc)
					{
						break;
					}
					else
					{
						m_roLogger.on_error(cgms_exception(cgms_exception::sec_not_enough_quantity,
							roGMOP.get_numop(),roGMOP.get_lp(),0,
							roGMOP.get_idprod(),roGMOP.get_idopak(),roGMOP.get_idmag(),
								poDostawaSetSP->get_missing_quantity()));
					}
				}
			}
			
			ASSERT(curIloscWydana > curZero);
			
			SCP<db_n5gmop> poDBN5GMOPSP = transfer_to_output_db_n5gmop_lp(
				roGMOP.get_lp(),
				roGMOP,
				oDostawaProp,
				oDostawaProp.get_numop(),
				oDostawaProp.get_lp(),
				- curIloscWydana
			);
			
			ASSERT(poDBN5GMOPSP.PointsObject());

			m_curWartoscDok += poDBN5GMOPSP->get_wartosc();
			curIlosc -= curIloscWydana;
		
			bWasAny = true;
		}
	}
}


//------------------------------------------------------------------------------------------
// przetwarza dostawê wyrobu - PHASE 1
// ze wzglêdu na zale¿noœci pomiêdzy wyrobami jest to opóŸniane do konca dokumentu
//------------------------------------------------------------------------------------------
void n5gmop_document::_process_product_phase1(SCP<n5gmop> poGMOPWyrobSP)
{
	if(poGMOPWyrobSP->get_ilosc() != curZero)
	{
		m_oGMOPWyroby_BuffArray.Add(poGMOPWyrobSP);
	}
}

//------------------------------------------------------------------------------------------
// przetwarza dostawê wyrobu - PHASE 2
// tworzy dostawê wyrobu opisanego w db_n5gmop
// wartoœæ dostawy brana jest w odpowiedniej proporcji z wartoœci dokumentu
//
//------------------------------------------------------------------------------------------
void n5gmop_document::_process_product_phase2(n5gmstan_glob & roStanMag,const n5gmop & roGMOP)
{
	price curWartWyrob = - m_curWartoscDok * roGMOP.get_przel();

	quantity curIlosc = roGMOP.get_ilosc();

	if(curIlosc == curZero)
	{
		m_roLogger.on_error(cgms_exception(cgms_exception::sec_zero_product_quantity,
			roGMOP.get_numop(),roGMOP.get_lp(),0,
				roGMOP.get_idprod(),roGMOP.get_idopak(),roGMOP.get_idmag(),curZero));
	}
	
	price curPrice1;
	price curPrice2;
	quantity curIlosc1;
	quantity curIlosc2;


	//sprawdŸ czy jest podzia³ - jeœli tak to go zapisz
	if(split_value(curWartWyrob,curIlosc,curPrice1,curIlosc1,curPrice2,curIlosc2,4))
	{
		n5gmop oGMOpWyrob(roGMOP);
		oGMOpWyrob.set_cena(curPrice2);
		oGMOpWyrob.set_ilosc(curIlosc2);
		_process_secondary_supply(roStanMag,oGMOpWyrob,false);
	}

	if(g_oLog.IsHandleValid())
	{
		LCID lcid = MAKELCID(LANG_ID_FOR_CONVERTIONS, SORT_DEFAULT);

		g_oLog << "{production split:[nnumop]=" + 
			Long2String(roGMOP.get_numop()) + 
			Long2String(roGMOP.get_lp()) +
			";[wartosc wyr]=" + curWartWyrob.Format(0,lcid) + 
			";[ilosc]=" + curIlosc.Format(0,lcid) + 
			";[cena1]=" + curPrice1.Format(0,lcid) + 
			";[ilosc1]=" + curIlosc1.Format(0,lcid) + 
			";[cena2]=" + curPrice2.Format(0,lcid) + 
			";[ilosc2]=" + curIlosc2.Format(0,lcid) + "}";
	}

	//zawsze 1-sza pozycja
	{
		n5gmop oGMOpWyrob(roGMOP);
		oGMOpWyrob.set_cena(curPrice1);
		oGMOpWyrob.set_ilosc(curIlosc1);
		_process_secondary_supply(roStanMag,oGMOpWyrob,false);
	}
}


