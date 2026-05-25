/*
NAVO Eurobiznes 5.0
Copyright (c) 2004 NAVO

navogm - modu³ gospodarki magazynowej (server)
wersja dla n5gmop

REV:KB:2004-02-13
*/

#ifndef _N5GMOPSET_H_
#define _N5GMOPSET_H_

namespace navogm_server
{
	class n5gmstan_glob;

	class mem_dok;
	class mem_lp;

	//------ runtime representation of gm document
	//------ it contains set of db_n5gmop records which are analyzed and eventually updated/inserted/
	//single set is processed in any moment

	class n5gmop_document
	{
	public:
		enum eload_result
		{
			lr_eof,			//EOF recordset
			lr_eod,			//end of document
			lr_eolp,		//end of lp
		};

		n5gmop_document(csrvlogger & roLogger,long nGlobalStartingNumOp,eWorkMode eWM);
		eload_result load_single_lp(n5gmstan_glob & roStanMag,ADODB::_RecordsetPtr & rpoN5GMOPRS,
			long & riLoadedLP);

		void load_single_mem_lp(n5gmstan_glob & roStanMag,SCP<mem_lp> & rpoMemLPSP);

		void move_single_dbgmop(n5gmstan_glob & roStanMag,SCP<db_n5gmop> poGMOPSP);
		void process_single_lp(n5gmstan_glob & roStanMag,long iLP);

		void finish_document(n5gmstan_glob & roStanMag);
		void flush_document(n5gmstan_glob & roStanMag,SCP<IObjectServer> & rpoObjectServerSP,ADODB::_ConnectionPtr & rpoConnection,
			bool bLargeGM);

		void flush_document_mem(n5gmstan_glob & roStanMag,SCP<IObjectServer> & rpoObjectServerSP,
			CComPtr<mem_dok> poMemDokSP);
	private:
		long _get_global_starting_numop() const;

		void _process_independent_supply(n5gmstan_glob & roStanMag,const n5gmop & roGMOP,bool bUpdateWartosc);
		void _process_secondary_supply(n5gmstan_glob & roStanMag,const n5gmop & roGMOP,bool bUpdateWartosc);
		void _process_self_supply(n5gmstan_glob & roStanMag,const n5gmop & roGMOP,long & rnPreviousDBInx);

		void _process_ordered_expend(n5gmstan_glob & roStanMag,const n5gmop & roGMOP);
		void _process_numop_rel_expend(n5gmstan_glob & roStanMag,const n5gmop & roGMOP);
		void _process_iddost_rel_expend(n5gmstan_glob & roStanMag,const n5gmop & roGMOP,
			bool bAutoIlosc);
		void _process_to_output(const n5gmop & roGMOP);

		void _process_product_phase1(SCP<n5gmop> poGMOPWyrobSP);
		void _process_product_phase2(n5gmstan_glob & roStanMag,const n5gmop & roGMOP);

		//wstepne ladowanie tablicy (nie zmienia outinx)
		void load_output_db_n5gmop_lp(long iLP,SCP<db_n5gmop> & rpoGMOPSP);
		//wynikowe ladowanie tablicy (zmienia outinx)
		SCP<db_n5gmop> transfer_to_output_db_n5gmop_lp(long iLP,
			const n5gmop & ron5gmop,const n5gmdostawa_prop & ron5gmdost_prop,long iNumOpRel,long iLPRel,
			const quantity & rcurIlosc);
		void add_to_output_db_n5gmop_lp(long iLP,SCP<db_n5gmop> poGMOPSP);

		long get_complete_upper_bound_lp(long iLP);
		long get_current_output_index_lp(long iLP);
		SCP<db_n5gmop> get_output_at_lp(long iLP,long iIndex);

		//bufor wejœciowy/roboczy operacji (single lp)
		CArray< SCP<n5gmop>, SCP<n5gmop> & > m_oGMOP_BuffArray;

		CArray< SCP<n5gmop>, SCP<n5gmop> & > m_oGMOPWyroby_BuffArray;

		//bufor wyjsciowy z wczytanymi, a potem przetworzonymi rekordami n5gmop 
		//dla pojedynczego lp w nnumop
		class n5gmop_lp_out_buffer : public CInterface__
		{
		public:
			n5gmop_lp_out_buffer() :
			  m_iOutDBInx(0)
			  {
			  }

			  void load_output_db_n5gmop(SCP<db_n5gmop> & rpoGMOPSP)
			  {
				  m_oN5GMOP_Array.Add(rpoGMOPSP);
				  ASSERT(m_iOutDBInx == 0);
			  }

			  SCP<db_n5gmop> transfer_to_output_db_n5gmop(
				  const n5gmop & ron5gmop,
				  const n5gmdostawa_prop & ron5gmdost_prop,
				  long iNumOpRel,
				  long iLPRel,
				  const quantity & rcurIlosc)
			  {
				  if(m_iOutDBInx <= m_oN5GMOP_Array.GetUpperBound())
				  {
					  m_oN5GMOP_Array[ m_iOutDBInx ]->fill_expend(ron5gmop,ron5gmdost_prop,iNumOpRel,iLPRel,rcurIlosc);
					  return m_oN5GMOP_Array[ m_iOutDBInx++ ];
				  }
				  else
				  {
					  SCP<db_n5gmop> poNewN5GMOPSP = 
						  NewSCP(new db_n5gmop(ron5gmop,ron5gmdost_prop,iNumOpRel,iLPRel,rcurIlosc),false);

					  m_oN5GMOP_Array.Add(poNewN5GMOPSP);
					  m_iOutDBInx++;
					  return poNewN5GMOPSP;
				  }
			  }

			  void add_to_output_db_n5gmop(SCP<db_n5gmop> poGMOPSP)
			  {
				  m_oN5GMOP_Array.Add(poGMOPSP);
				  m_iOutDBInx++;
			  }

			  long get_current_output_index()
			  {
				  return m_iOutDBInx;
			  }

			  long get_complete_upper_bound()
			  {
				  return m_oN5GMOP_Array.GetUpperBound();
			  }

			  SCP<db_n5gmop> get_at(long iIndex)
			  {
				  ASSERT(iIndex >= 0 && iIndex <= m_oN5GMOP_Array.GetUpperBound());
				  return m_oN5GMOP_Array[ iIndex ];
			  }

		private:
			CArray< SCP<db_n5gmop>, SCP<db_n5gmop> & > m_oN5GMOP_Array;
			long m_iOutDBInx;	//indeks pierwszego wolnego w m_oGMOP_DBArray traktowanej jako wyjœcie
		};

		//wczytane rekordy db_n5gmop - (single lp)
		CArray< SCP<n5gmop_lp_out_buffer>, SCP<n5gmop_lp_out_buffer> & > m_oGMOPLP_Output_Array;

		price m_curWartoscDok;		//wartoœæ zu¿ytych materia³ów i robocizna

		long m_nGlobalStartingNumOp;//pocz¹tkowy numer operacji dla naprawy (rozchody przed tym numerem pomijamy)
		csrvlogger & m_roLogger;

		//work mode (GM or PT)
		eWorkMode m_eWorkMode;
	};

	inline long n5gmop_document::_get_global_starting_numop() const
	{
		return m_nGlobalStartingNumOp;
	}

	inline void n5gmop_document::load_output_db_n5gmop_lp(long iLP,SCP<db_n5gmop> & rpoGMOPSP)
	{
		bool bNewAlloc = (iLP > m_oGMOPLP_Output_Array.GetUpperBound());
		if(!bNewAlloc)
		{
			bNewAlloc = m_oGMOPLP_Output_Array[ iLP ].PointsNull();
		}
		if(bNewAlloc)
		{
			m_oGMOPLP_Output_Array.SetAtGrow(iLP,NewSCP(new n5gmop_lp_out_buffer(),false));
		}
		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		m_oGMOPLP_Output_Array[ iLP ]->load_output_db_n5gmop(rpoGMOPSP);
	}

	inline SCP<db_n5gmop> n5gmop_document::transfer_to_output_db_n5gmop_lp(long iLP,
		const n5gmop & ron5gmop,const n5gmdostawa_prop & ron5gmdost_prop,long iNumOpRel,long iLPRel,
		const quantity & rcurIlosc)
	{
		bool bNewAlloc = (iLP > m_oGMOPLP_Output_Array.GetUpperBound());
		if(!bNewAlloc)
		{
			bNewAlloc = m_oGMOPLP_Output_Array[ iLP ].PointsNull();
		}
		if(bNewAlloc)
		{
			m_oGMOPLP_Output_Array.SetAtGrow(iLP,NewSCP(new n5gmop_lp_out_buffer(),false));
		}
		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		return m_oGMOPLP_Output_Array[ iLP ]->transfer_to_output_db_n5gmop(ron5gmop,
			ron5gmdost_prop,iNumOpRel,iLPRel,rcurIlosc);
	}

	inline void n5gmop_document::add_to_output_db_n5gmop_lp(long iLP,SCP<db_n5gmop> poGMOPSP)
	{
		bool bNewAlloc = (iLP > m_oGMOPLP_Output_Array.GetUpperBound());
		if(!bNewAlloc)
		{
			bNewAlloc = m_oGMOPLP_Output_Array[ iLP ].PointsNull();
		}
		if(bNewAlloc)
		{
			m_oGMOPLP_Output_Array.SetAtGrow(iLP,NewSCP(new n5gmop_lp_out_buffer(),false));
		}

		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		m_oGMOPLP_Output_Array[ iLP ]->add_to_output_db_n5gmop(poGMOPSP);
	}

	inline long n5gmop_document::get_current_output_index_lp(long iLP)
	{
		if(iLP > m_oGMOPLP_Output_Array.GetUpperBound())
		{
			ASSERT(false); //chcemy wiedziec kiedy to jest wolane w ten sposob
			return 0;
		}
		//dziury sa dozwolone
		if(m_oGMOPLP_Output_Array[ iLP ].PointsNull())
		{
			return 0;
		}

		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		return m_oGMOPLP_Output_Array[ iLP ]->get_current_output_index();
	}

	inline long n5gmop_document::get_complete_upper_bound_lp(long iLP)
	{
		if(iLP > m_oGMOPLP_Output_Array.GetUpperBound())
		{
			ASSERT(false); //chcemy wiedziec kiedy to jest wolane w ten sposob
			return -1;
		}

		//dziury sa dozwolone
		if(m_oGMOPLP_Output_Array[ iLP ].PointsNull())
		{
			return -1;
		}

		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		return m_oGMOPLP_Output_Array[ iLP ]->get_complete_upper_bound();
	}

	inline SCP<db_n5gmop> n5gmop_document::get_output_at_lp(long iLP,long iIndex)
	{
		if(iLP > m_oGMOPLP_Output_Array.GetUpperBound())
		{
			ASSERT(false); //chcemy wiedziec kiedy to jest wolane w ten sposob
			return SCP<db_n5gmop>();
		}
		//jesli sie juz pytamy to musimy wiedziec ze jest
		ASSERT(m_oGMOPLP_Output_Array[ iLP ].PointsObject());

		return m_oGMOPLP_Output_Array[ iLP ]->get_at(iIndex);
	}
}

namespace navogm_server
{
	class ado_trans
	{
	public:
		ado_trans(ADODB::_ConnectionPtr & oConnectionPtr, bool bUseMainConnection)
		{
			m_bPrivateConnection = false;

			if(true || bUseMainConnection)
			{
				m_oConnection=oConnectionPtr;
			}
			else
			{
				m_oConnection = 0;
			}
		}
		void open()
		{
			if(m_oConnection)
			{
				return;
			}
			m_oConnection.CreateInstance(_T("ADODB.Connection"));
			m_oConnection->Provider = _T("SQLOLEDB");
			m_oConnection->Attributes = ADODB::adXactCommitRetaining + ADODB::adXactAbortRetaining;
			m_oConnection->CommandTimeout = 60 * 60;

			throw;

			CString oDSNDBString;
			//oDSNDBString = _T("Server=NAVO_B\\SQLFULL;DATABASE=navo2012hk");
			//oDSNDBString = _T("Server=WIN-71N1I9CFQX3\\NAVO2002;DATABASE=navo2002");	//HK-testy
			oDSNDBString = _T("Server=.\\sql2014;DATABASE=navo2002");
			
			//AfxMessageBox(oDSNDBString);

			m_oConnection->Open(_bstr_t(oDSNDBString),_bstr_t("navo2002user"),_bstr_t("y7410xru3"),-1);
			m_oConnection->CommandTimeout = 60 * 60;

			CADOCommand(m_oConnection).ExecDirect(_T("SET CURSOR_CLOSE_ON_COMMIT OFF"),true);
			CADOCommand(m_oConnection).ExecDirect(_T("SET DATEFORMAT DMY"),true);
			CADOCommand(m_oConnection).ExecDirect(_T("SET XACT_ABORT OFF"),true);
			CADOCommand(m_oConnection).ExecDirect(_T("SET ANSI_PADDING OFF"),true);

			m_oConnection->BeginTrans();
			m_bPrivateConnection = true;
		}
		~ado_trans()
		{
			if(m_bPrivateConnection && m_oConnection)
			{
				m_oConnection->CommitTrans();
				m_oConnection = 0;
				m_bPrivateConnection = false;
			}
		}
		void rollback()
		{
			if(m_oConnection)
			{
				m_oConnection->RollbackTrans();
				m_oConnection=0;
			}
		}
		ADODB::_ConnectionPtr get_connection()
		{
			open();
			return m_oConnection;
		};

		ADODB::_ConnectionPtr m_oConnection;
		bool m_bPrivateConnection;
	};
}

using namespace navogm_server;

#else
#error File already included
#endif


