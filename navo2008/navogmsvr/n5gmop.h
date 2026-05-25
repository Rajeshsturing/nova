/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13
*/

#ifndef _N5GMOP_H_
#define _N5GMOP_H_


namespace navogm_server
{
	class n5gmdostawa_prop;
	class db_n5gmop;

	/*
		gm operation work buffer
	*/

	enum en5gmtypop
	{
		N5GMOP_P_CZ_IZ_DS = 1,
		N5GMOP_R_CA_IZ_DF = 2,
		N5GMOP_R_CA_IZ_DZ = 3,
		N5GMOP_P_CA_IA_DS = 4,
		N5GMOP_R_CZ_IZ_DX = 5,
		N5GMOP_P_CP_IZ_DS = 6,
		N5GMOP_K_CA_IA_DI = 7,
		N5GMOP_R_CA_IZ_DI = 8,
		N5GMOP_P_CZ_IZ_BO = 9,	//podsumowanie archiwum (BO)
		N5GMOP_K_STORNO_WART  = 10, //storno zaokraglen wartosci
	};

	class n5gmop : public CInterface__
	{
	public:
		n5gmop(const n5gmop & ron5gmop);
		void operator = (const n5gmop & ron5gmop);

		const long get_idmag() const;
		const long get_idprod() const;
		const long get_idopak() const;

		const en5gmtypop get_typop() const;
		const long get_numop() const;
		const long get_lp() const;
		const quantity & get_ilosc() const;
		const price & get_cena() const;
		const price & get_wartosc() const;
		const supply_id get_iddostawa() const;
		const navogm_date get_datawazn() const;
		
		const long get_numop_rel() const;
		const long get_lp_rel() const;
		const quantity & get_przel() const;

		bool is_void_gmop() const;
	
		bool will_join(const db_n5gmop & ron5gmop,long nStartingNumOp);
		void do_join(const db_n5gmop & ron5gmop,long nStartingNumOp);
	
		void set_typop(en5gmtypop eTypOP);
		void set_numop_rel(long nNumOpRel);
		void set_lp_rel(long nLPRel);
		void set_idmag(long idMag);
		void set_ilosc(const quantity & rcurIlosc);
		void set_iddostawa(supply_id idDostawa);
		void set_cena(const price & rcurPrice);
		void set_wartosc_manual(const price & rcurWartosc);
	protected:
		n5gmop();
		void _wylicz_wartosc();

		en5gmtypop	m_eTypOp;
		long		m_nNumOp;
		long		m_nLP;
		quantity	m_curIlosc;
		price		m_curCena;
		price		m_curWartosc;
		long		m_idProd;
		long		m_idOpak;
		long		m_idMag;
		supply_id	m_idDost;
		navogm_date m_dDataWazn;
		long		m_nNumOpRel;
		long		m_nLPRel;
		quantity	m_curPrzel;
	};


	//-------------------------------------------
	// wrapper na obiekt DB "n5gmop"
	// czyta i zapisuje
	//-------------------------------------------
	class db_n5gmop : public n5gmop
	{
	public:
		db_n5gmop(ADODB::_RecordsetPtr & rpoN5GMOPRS);	//load from recordset
		
		db_n5gmop(const n5gmop & ron5gmop,const n5gmdostawa_prop & ron5gmdost_prop,
			long iNumOpRel,long iLPRel,const quantity & rcurIlosc);

		db_n5gmop(long iNumOper,long iLP,
				  long idProd,long idOpak,
				  long eTypOper,
				  quantity curIlosc,price curCena,long idMag,
				  long idDost,long idDostLP,
				  navogm_date dDataWazn,
				  long iNumOperRel,long iLPRel,quantity curPrzel);
		
		void fill_expend(const n5gmop & ron5gmop,const n5gmdostawa_prop & ron5gmdost_prop,
			long iNumOpRel,long iLPRel,const quantity & rcurIlosc);

		void insert_db(SCP<IObjectServer> & rpoObjectServerSP,ADODB::_ConnectionPtr & rpoConnection,eWorkMode eWM);
		void update_db(ADODB::_ConnectionPtr & rpoConnection,eWorkMode eWM);
		void delete_db(ADODB::_ConnectionPtr & rpoConnection,eWorkMode eWM);

		bool is_dbmodified() const;
		const long get_idobj() const;
		//--- próbuje scaliæ dwa w jeden
	private:
		void _fill_command_param(CADOCommand & roADOCommand);
		void _read_from_ado(ADODB::_RecordsetPtr & rpoN5GMOPRS);

		long m_idObj;		//undelying IdObj for 'old' objects
		long m_nVersion;

		bool m_bDBModified;
	};

	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	inline const long n5gmop::get_idmag() const
	{
		return m_idMag;
	}

	inline const long n5gmop::get_idprod() const
	{
		return m_idProd;
	}

	inline const long n5gmop::get_idopak() const
	{
		return m_idOpak;
	}
	
	inline const en5gmtypop n5gmop::get_typop() const
	{
		return m_eTypOp;
	}

	inline const long n5gmop::get_numop() const
	{
		return m_nNumOp;
	}

	inline const long n5gmop::get_lp() const
	{
		return m_nLP;
	}
	
	inline const quantity & n5gmop::get_ilosc() const
	{
		return m_curIlosc;
	}

	inline const price & n5gmop::get_cena() const
	{
		return m_curCena;
	}

	inline const price & n5gmop::get_wartosc() const
	{
		return m_curWartosc;
	}
	
	inline const supply_id n5gmop::get_iddostawa() const
	{
		return m_idDost;
	}

	inline const navogm_date n5gmop::get_datawazn() const
	{
		return m_dDataWazn;
	}

	inline const long n5gmop::get_numop_rel() const
	{
		return m_nNumOpRel;
	}
	
	inline const long n5gmop::get_lp_rel() const
	{
		return m_nLPRel;
	}
	
	inline const quantity & n5gmop::get_przel() const
	{
		return m_curPrzel;
	}

	inline bool n5gmop::is_void_gmop() const
	{
		return ((m_curIlosc == curZero) != FALSE);
	}

	inline void n5gmop::set_idmag(long idMag)
	{
		m_idMag = idMag;
	}
	
	inline void n5gmop::set_ilosc(const quantity & rcurIlosc)
	{
		m_curIlosc = rcurIlosc;
		
		_wylicz_wartosc();
	}

	inline void n5gmop::set_typop(en5gmtypop eTypOp)
	{
		m_eTypOp = eTypOp;
	}

	inline void n5gmop::set_numop_rel(long nNumOpRel)
	{
		m_nNumOpRel = nNumOpRel;
	}

	inline void n5gmop::set_lp_rel(long nLPRel)
	{
		m_nLPRel = nLPRel;
	}

	inline void n5gmop::set_iddostawa(supply_id idDostawa)
	{
		m_idDost = idDostawa;
	}

	inline void n5gmop::set_cena(const price & rcurPrice)
	{
		m_curCena = rcurPrice;
		_wylicz_wartosc();
	}

	inline void n5gmop::set_wartosc_manual(const price & rcurWartosc)
	{
		m_curWartosc = rcurWartosc;
		round_currency_2(m_curWartosc.m_cur);
	}

	inline void n5gmop::_wylicz_wartosc()
	{
		m_curWartosc = get_cena() * get_ilosc();
		round_currency_2(m_curWartosc.m_cur);
	}

	//----------------------------------------------------------------
	//--- próbuje scaliæ do tego n5gmop kolejny n5gmop
	inline bool n5gmop::will_join(const db_n5gmop & ron5gmop,long nStartingNumOp)
	{
		ASSERT(m_nNumOp == ron5gmop.m_nNumOp);
		ASSERT(m_nLP == ron5gmop.m_nLP);
		
		//nie sklejaj gdy nawet jedno jest sprzed border'a
		if(get_numop_rel() > 0 && get_numop_rel() < nStartingNumOp)
		{
			return false;
		}
		if(ron5gmop.get_numop_rel() > 0 && ron5gmop.get_numop_rel() < nStartingNumOp)
		{
			return false;
		}

		//nie sklejaj MM-ek (na granicy typow) - resztê sklejaj
		if((m_eTypOp == N5GMOP_R_CA_IZ_DF || m_eTypOp == N5GMOP_R_CA_IZ_DZ) && 
			ron5gmop.m_eTypOp == N5GMOP_P_CA_IA_DS)
		{
			return false;
		}
		
		//nie sklejaj KWZ (na granicy typow) 
		if(m_eTypOp == N5GMOP_P_CZ_IZ_DS && ron5gmop.m_eTypOp == N5GMOP_R_CA_IZ_DI)
		{
			return false;
		}

		//nie ruszaj podsumowan archiwum
		if(m_eTypOp == N5GMOP_P_CZ_IZ_BO)
		{
			return false;
		}

		return true;
	}

	inline void n5gmop::do_join(const db_n5gmop & ron5gmop,long nStartingNumOp)
	{
		ASSERT(will_join(ron5gmop,nStartingNumOp));

		//zapamiêtaj iloœæ i wartoœæ
		quantity	curIloscTemp = m_curIlosc;
		price		curWartoscTemp = m_curWartosc;

		//skopiuj
		(*this) = ron5gmop;

		//aktualizuj wartoœæ
		m_curIlosc += curIloscTemp;
		m_curWartosc += curWartoscTemp;
	}

	//----------------------------------------------------------------
	
	inline const long db_n5gmop::get_idobj() const
	{
		return m_idObj;
	}

	inline bool db_n5gmop::is_dbmodified() const
	{
		return m_bDBModified;
	}


}

using namespace navogm_server;

#else
	#error File already included
#endif

