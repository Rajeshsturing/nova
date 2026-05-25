/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2005 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	struktury do przechowywania n5gmop w pamieci

	KB:2005-12-07
*/

#include "stdafx.h"
#include "engineincl.h"
#include "types_consts_gm.h"
#include "n5gmop.h"
#include "mem_db.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace navogm_server;

void mem_base::load_from_rs(ADODB::_RecordsetPtr & rpoN5GMOPRS)
{
	long iLastNumOp = 0;
	long iLastLP = 0;
	CComPtr<mem_dok> poMemDokSP;
	SCP<mem_lp> poMemLPSP;

	while(!rpoN5GMOPRS->EOF)
	{
		SCP<db_n5gmop> poGMOPSP = NewSCP(new db_n5gmop(rpoN5GMOPRS),false);

//		TRACE("mem:loaded [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());
	
		if(iLastNumOp != poGMOPSP->get_numop())
		{
			iLastNumOp = poGMOPSP->get_numop();
			ASSERT(!is_document(iLastNumOp));
			poMemDokSP.Attach(new mem_dok());
			set_document(iLastNumOp,poMemDokSP);

			iLastLP = 0;
	
			TRACE("mem:loaded [%d,%d],%d\n",poGMOPSP->get_numop(),poGMOPSP->get_lp(),poGMOPSP->get_idobj());
		}
		ASSERT(poMemDokSP != NULL);

		if(iLastLP != poGMOPSP->get_lp())
		{
			iLastLP = poGMOPSP->get_lp();
			ASSERT(!poMemDokSP->is_lp(iLastLP));
			poMemLPSP = NewSCP<mem_lp>(new mem_lp());
			poMemDokSP->set_lp(poGMOPSP->get_lp(),poMemLPSP);
		}
		ASSERT(poMemLPSP.PointsObject());
		
		poMemLPSP->set_record(poMemLPSP->get_count(),poGMOPSP);

		rpoN5GMOPRS->MoveNext();
	}
}

