/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-14
*/

#ifndef _N5GMSTAN_H_
#define _N5GMSTAN_H_


namespace navogm_server
{
	//-------------------------------------------
	// properties dostawy (niezmienniki)
	// cena, identyfikator, data wa¿noœci
	//-------------------------------------------
	class n5gmdostawa_prop
	{
	public:
		n5gmdostawa_prop();
		n5gmdostawa_prop(long nNumOpDost,long nLPDost,supply_id idDost,const price & rcurCena,
			const navogm_date & rdDataWazn);
		void operator = (const n5gmdostawa_prop & roDostawaProp);
		bool operator == (const n5gmdostawa_prop & roDostawaProp) const;

		const long get_numop() const;
		const long get_lp() const;
		const supply_id get_iddostawa() const;
		const price & get_cena() const;
		const navogm_date get_datawazn() const;

	private:

		long		m_nNumOp_Dostawy;
		long		m_nLP_Dostawy;
		price		m_curCena;
		supply_id	m_idDost;
		navogm_date m_dDataWazn;

		friend class db_n5gmstan;
	};

	//-------------------------------------------
	// operacja na stanie magazynowym - stan bie¿¹cy
	// operacje bior¹ siê z dostaw (pierwotnych lub wtórnych)
	//-------------------------------------------
	class n5gmstan_operation : public CInterface__
	{
	public:
		n5gmstan_operation(const n5gmop & ron5gmop);
		n5gmstan_operation(const n5gmstan_operation & roOperation);

		void operator = (const n5gmstan_operation & roDostawa);
		bool operator == (const n5gmstan_operation & roDostawa);
		void wydaj(const quantity & rcurInpIlosc,quantity & rcurOutIlosc);
		void ujmij_zawsze(const quantity & rcurInpIlosc);
		void dodaj(const quantity & rcurInpIlosc);

		bool is_void() const;
		
		bool can_be_joined(const n5gmop & ron5gmop) const;

		const quantity & get_ilosc() const;
		
		const n5gmdostawa_prop & properties() const;

		static SCP<n5gmstan_operation> create_artifical_operation();
	protected:
		n5gmstan_operation();

		n5gmdostawa_prop m_oDostawaProp;
		quantity	m_curIlosc;

		SCP<n5gmstan_operation> m_poNextOperationSP;
		SCP<n5gmstan_operation> m_poPrevOperationSP;

		friend class n5gmstan_element;
	};

	//-------------------------------------------
	// wrapper na obiekt DB "n5gmstan"
	// czyta i zapisuje
	//-------------------------------------------
	class db_n5gmstan : public n5gmstan_operation
	{
	public:
		db_n5gmstan(ADODB::_RecordsetPtr & rpoN5GMOPRS);
		db_n5gmstan(const n5gmstan_operation & ron5gmop);

		void insert_db(SCP<IObjectServer> & rpoObjectServerSP,ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak,eWorkMode eWM);
		void update_db(ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak,eWorkMode eWM);
		static void delete_db(ADODB::_ConnectionPtr & rpoConnection,long idObj,eWorkMode eWM);
		void set_ilosc(const quantity & rcurInpIlosc);
	private:
		void _fill_command_param(CADOCommand & roADOCommand,long idMag,long idProd,long idOpak);
		void _read_from_ado(ADODB::_RecordsetPtr & rpoN5GMOPRS);

		long m_idObj;		//undelying IdObj for 'old' objects
		long m_nVersion;
	};
	
	//-----------------------------------------------------------------------
	// aktualnie dostêpne dostawy dla danego produktu / magazynu
	// current set danego elementu [produkt,opakowanie,magazyn]
	//-----------------------------------------------------------------------
	enum eStanFlushMode
	{
		sfm_just_append,	//dopisuje nowe operacje do konca
		sfm_diff_delivery,	//rozroznia dostawy
		sfm_just_qty,		//aktualizuje tylko ilosc
	};
	
	class n5gmstan_element : public CInterface__
	{
	public:
		n5gmstan_element(bool bAllowNegativeQuantity);
		~n5gmstan_element();

		bool flush(eStanFlushMode eSFM,long nGlobalStartingNumOp,SCP<IObjectServer> & rpoObjectServerSP,
			ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak,eWorkMode eWM, bool bLargeGM);
		
		bool write_as_bo(long iNumOpBO,long iLP,long & rIdObj,SCP<IObjectServer> & rpoObjectServerSP,
			ADODB::_ConnectionPtr & rpoConnection,long idMag,long idProd,long idOpak);

		void mark_need_flush();
		bool is_flush_needed() const;

		const n5gmstan_operation & nowa_dostawa(const n5gmop & ron5gmop);
		const n5gmstan_operation & stara_dostawa(const n5gmop & ron5gmop);

		//wydaje produkt z odpowiedniej dostawy i zwraca dostawê, która zosta³a "zu¿yta"
		//funkcje te nie 'sklejaj¹' jednakowych dostaw
		bool wydaj_produkt_fifo(const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp);
		bool wydaj_produkt_numop(long nNumOp,long nLP,const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp);
		bool wydaj_produkt_iddost(supply_id idDost,const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp);

		bool is_missing_quantity() const;
		quantity get_missing_quantity() const;
	private:

		void _handle_missing_quantity(const quantity & rcurInpIlosc,quantity & rcurOutIlosc,
			n5gmdostawa_prop & roDostawaProp);

		void _link_operation(SCP<n5gmstan_operation> & rpoNewOperationSP,
				SCP<n5gmstan_operation> & rpoBeforeOperationSP);

		void _unlink_operation(SCP<n5gmstan_operation> & rpoOldOperationSP);

		//szuka operacji o zadanym lub wiêkszym iddost,nnumop,lp
		SCP<n5gmstan_operation> _find_ordered_operation(supply_id idDost,long nNumOp,long nLP);

		SCP<n5gmstan_operation> m_poFirstOperationSP;
		SCP<n5gmstan_operation> m_poLastOperationSP;
		SCP<n5gmstan_operation> m_poArtificialOperationSP;

		bool m_bNeedFlush;
		const bool m_bAllowNegativeQuantity;
	};

	//-----------------------------------------------------------------
	// globalny bie¿¹cy stan magazynu
	//-----------------------------------------------------------------
	typedef unsigned __int64 hyper_key;
	class n5gmop_document;

	class n5gmstan_glob
	{
	public:
		n5gmstan_glob(csrvlogger & roLogger,bool bAllowNegativeQuantity,long nGlobalStartingNumOp,eWorkMode eWM);
		void flush(bool bForce,eStanFlushMode eSFM,SCP<IObjectServer> & rpoObjectServerSP,
			ADODB::_ConnectionPtr & rpoConnection, bool bLargeGM);
		SCP<n5gmstan_element> get_dostawy(long idMag,long idProd,long idOpak);
		
		void write_as_bo(long iNumOpBO,SCP<IObjectServer> & rpoObjectServerSP,ADODB::_ConnectionPtr & rpoConnection);

		static void _crack_key(hyper_key hypKey,long & ridMag,long & ridProd,long & ridOpak);
	private:
		hyper_key _compose_key(long idMag,long idProd,long idOpak);

		CMap<hyper_key,hyper_key, SCP<n5gmstan_element>, SCP<n5gmstan_element> & > m_oDostawaSetMap;
		const bool m_bAllowNegativeQuantity;
		const long m_nGlobalStartingNumOp;
		csrvlogger & m_roLogger;

		//work mode (GM or PT)
		eWorkMode m_eWorkMode;
	};

	//-----------------------------------------------------------------
	// inlines
	//-----------------------------------------------------------------

	inline n5gmstan_operation::n5gmstan_operation() :
		m_oDostawaProp(),
		m_curIlosc(curZero)
	{
	}

	inline n5gmstan_operation::n5gmstan_operation(const n5gmop & ron5gmop) :
			m_oDostawaProp(ron5gmop.get_numop(),ron5gmop.get_lp(),ron5gmop.get_iddostawa(),
				ron5gmop.get_cena(),ron5gmop.get_datawazn()),
			m_curIlosc(ron5gmop.get_ilosc())
	{
	}

	inline n5gmstan_operation::n5gmstan_operation(const n5gmstan_operation & roOperation)
	{
		(*this) = roOperation;
	}

	inline SCP<n5gmstan_operation> n5gmstan_operation::create_artifical_operation()
	{
		SCP<n5gmstan_operation> poOperationSP = NewSCP(new n5gmstan_operation(),false);
		return poOperationSP;
	}

	inline void n5gmstan_operation::operator = (const n5gmstan_operation & roDostawa)
	{
		m_oDostawaProp = roDostawa.m_oDostawaProp;
		m_curIlosc = roDostawa.m_curIlosc;
	}

	inline bool n5gmstan_operation::operator == (const n5gmstan_operation & roDostawa)
	{
		return (m_oDostawaProp == roDostawa.m_oDostawaProp) &&
			(m_curIlosc == roDostawa.m_curIlosc);
	}

	inline bool n5gmstan_operation::can_be_joined(const n5gmop & ron5gmop) const
	{
		return 
			(m_oDostawaProp.get_numop() == ron5gmop.get_numop()) &&
			(m_oDostawaProp.get_lp() == ron5gmop.get_lp()) &&
			(m_oDostawaProp.get_iddostawa() == ron5gmop.get_iddostawa()) &&
			(m_oDostawaProp.get_cena() == ron5gmop.get_cena()) &&
			(m_oDostawaProp.get_datawazn() == ron5gmop.get_datawazn());
	}

	inline void n5gmstan_operation::wydaj(const quantity & rcurInpIlosc,quantity & rcurOutIlosc)
	{
		ASSERT(!is_void());
		ASSERT(rcurInpIlosc > curZero);

		if(m_curIlosc < rcurInpIlosc)
		{
			rcurOutIlosc = m_curIlosc;
			m_curIlosc = curZero;

			ASSERT(rcurOutIlosc > curZero);
		}
		else
		{
			rcurOutIlosc = rcurInpIlosc;
			m_curIlosc -= rcurInpIlosc;
			
			ASSERT(m_curIlosc >= curZero);
			ASSERT(rcurOutIlosc > curZero);
		}
	}

	inline void n5gmstan_operation::ujmij_zawsze(const quantity & rcurInpIlosc)
	{
		ASSERT(rcurInpIlosc > curZero);
		m_curIlosc -= rcurInpIlosc;
		ASSERT(m_curIlosc < curZero);
	}

	inline void n5gmstan_operation::dodaj(const quantity & rcurInpIlosc)
	{
		ASSERT(m_curIlosc >= curZero);
		ASSERT(rcurInpIlosc > curZero);
		m_curIlosc += rcurInpIlosc;
		ASSERT(m_curIlosc >= curZero);
	}


	inline bool n5gmstan_operation::is_void() const
	{
		return ((m_curIlosc == curZero) != FALSE);
	}

	inline const quantity & n5gmstan_operation::get_ilosc() const
	{
		return m_curIlosc;
	}

	inline const n5gmdostawa_prop & n5gmstan_operation::properties() const
	{
		return m_oDostawaProp;
	}

	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	inline n5gmdostawa_prop::n5gmdostawa_prop() :
		m_nNumOp_Dostawy(-1),
		m_nLP_Dostawy(-1),
		m_curCena(curZero),
		m_idDost(longlong(-1,-1)),
		m_dDataWazn(0)
	{
	}

	inline n5gmdostawa_prop::n5gmdostawa_prop(long nNumOpDost,long nLPDost,supply_id idDost,
			const price & rcurCena,const navogm_date & rdDataWazn) :
		m_nNumOp_Dostawy(nNumOpDost),
		m_nLP_Dostawy(nLPDost),
		m_curCena(rcurCena),
		m_idDost(idDost),
		m_dDataWazn(rdDataWazn)
	{
	}

	inline void n5gmdostawa_prop::operator = (const n5gmdostawa_prop & roDostawaProp)
	{
		m_nNumOp_Dostawy	= roDostawaProp.m_nNumOp_Dostawy;
		m_nLP_Dostawy		= roDostawaProp.m_nLP_Dostawy;
		m_curCena			= roDostawaProp.m_curCena;
		m_idDost			= roDostawaProp.m_idDost;
		m_dDataWazn			= roDostawaProp.m_dDataWazn;
	}

	inline bool n5gmdostawa_prop::operator == (const n5gmdostawa_prop & roDostawaProp) const
	{
		return
			(m_nNumOp_Dostawy	== roDostawaProp.m_nNumOp_Dostawy) &&
			(m_nLP_Dostawy		== roDostawaProp.m_nLP_Dostawy) &&
			(m_curCena			== roDostawaProp.m_curCena) &&
			(m_idDost			== roDostawaProp.m_idDost) &&
			(m_dDataWazn		== roDostawaProp.m_dDataWazn);
	}

	inline const long n5gmdostawa_prop::get_numop() const
	{
		return m_nNumOp_Dostawy;
	}

	inline const long n5gmdostawa_prop::get_lp() const
	{
		return m_nLP_Dostawy;
	}
	
	inline const supply_id n5gmdostawa_prop::get_iddostawa() const
	{
		return m_idDost;
	}

	inline const price & n5gmdostawa_prop::get_cena() const
	{
		return m_curCena;
	}
	
	inline const navogm_date n5gmdostawa_prop::get_datawazn() const
	{
		return m_dDataWazn;
	}

	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	inline db_n5gmstan::db_n5gmstan(ADODB::_RecordsetPtr & rpoN5GMOPRS) :
		n5gmstan_operation()
	{
		_read_from_ado(rpoN5GMOPRS);
	}

	inline db_n5gmstan::db_n5gmstan(const n5gmstan_operation & ron5gmstan) :
		n5gmstan_operation(ron5gmstan),
		m_idObj(0),
		m_nVersion(1)
	{
	}

	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	inline n5gmstan_element::n5gmstan_element(bool bAllowNegativeQuantity) :
		m_bAllowNegativeQuantity(bAllowNegativeQuantity),
		m_bNeedFlush(false)
	{
	}

	inline n5gmstan_element::~n5gmstan_element()
	{
		while(m_poLastOperationSP.PointsObject())
		{
			SCP<n5gmstan_operation> poOldOperationSP = m_poLastOperationSP;
			_unlink_operation(poOldOperationSP);
		}
	}

	inline void n5gmstan_element::mark_need_flush()
	{
		m_bNeedFlush = true;
	}

	inline bool n5gmstan_element::is_flush_needed() const
	{
		return m_bNeedFlush;
	}

	inline void n5gmstan_element::_link_operation(SCP<n5gmstan_operation> & rpoNewOperationSP,
			SCP<n5gmstan_operation> & rpoBeforeOperationSP)
	{
		if(rpoBeforeOperationSP.PointsObject())
		{
			if(rpoBeforeOperationSP->m_poPrevOperationSP.PointsObject())
			{
				rpoNewOperationSP->m_poPrevOperationSP = rpoBeforeOperationSP->m_poPrevOperationSP;
				rpoBeforeOperationSP->m_poPrevOperationSP->m_poNextOperationSP = rpoNewOperationSP;
			}
			else
			{
				ASSERT(m_poFirstOperationSP.Get() == rpoBeforeOperationSP.Get());
				m_poFirstOperationSP = rpoNewOperationSP;
			}
			rpoNewOperationSP->m_poNextOperationSP = rpoBeforeOperationSP;
			rpoBeforeOperationSP->m_poPrevOperationSP = rpoNewOperationSP;
		}
		else
		{
			if(m_poLastOperationSP.PointsObject())
			{
				rpoNewOperationSP->m_poPrevOperationSP = m_poLastOperationSP;
				m_poLastOperationSP->m_poNextOperationSP = rpoNewOperationSP;
			}
			else
			{
				ASSERT(m_poFirstOperationSP.PointsNull());
				m_poFirstOperationSP = rpoNewOperationSP;
			}
			m_poLastOperationSP = rpoNewOperationSP;
		}

		ASSERT(m_poFirstOperationSP.PointsObject() && m_poLastOperationSP.PointsObject());
	}

	inline void n5gmstan_element::_unlink_operation(SCP<n5gmstan_operation> & rpoOldOperationSP)
	{
		if(rpoOldOperationSP->m_poNextOperationSP.PointsObject())
		{
			rpoOldOperationSP->m_poNextOperationSP->m_poPrevOperationSP = rpoOldOperationSP->m_poPrevOperationSP;
		}
		else
		{
			ASSERT(rpoOldOperationSP.Get() == m_poLastOperationSP.Get());
			m_poLastOperationSP = rpoOldOperationSP->m_poPrevOperationSP;
		}

		if(rpoOldOperationSP->m_poPrevOperationSP.PointsObject())
		{
			rpoOldOperationSP->m_poPrevOperationSP->m_poNextOperationSP = rpoOldOperationSP->m_poNextOperationSP;
		}
		else
		{
			ASSERT(rpoOldOperationSP.Get() == m_poFirstOperationSP.Get());
			m_poFirstOperationSP = rpoOldOperationSP->m_poNextOperationSP;
		}

		ASSERT((m_poFirstOperationSP.PointsObject() && m_poLastOperationSP.PointsObject()) ||
			   (m_poFirstOperationSP.PointsNull() && m_poLastOperationSP.PointsNull()));
	}

	inline bool n5gmstan_element::is_missing_quantity() const
	{
		return m_poArtificialOperationSP.PointsObject();
	}

	inline quantity n5gmstan_element::get_missing_quantity() const
	{
		if(is_missing_quantity())
		{
			return m_poArtificialOperationSP->get_ilosc();
		}
		else
		{
			return curZero;
		}
	}
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	inline n5gmstan_glob::n5gmstan_glob(csrvlogger & roLogger,bool bAllowNegativeQuantity,
		long nGlobalStartingNumOp,eWorkMode eWM) :
		m_bAllowNegativeQuantity(bAllowNegativeQuantity),
		m_nGlobalStartingNumOp(nGlobalStartingNumOp),
		m_roLogger(roLogger),
		m_eWorkMode(eWM)
	{
		m_oDostawaSetMap.InitHashTable(599);
	}

	inline hyper_key n5gmstan_glob::_compose_key(long idMag,long idProd,long idOpak)
	{
		ASSERT(idMag != 0);
		ASSERT(idProd != 0);
		ASSERT(idOpak != 0);

		ASSERT((idProd & 0x00ffffff) == idProd);	//24 bity max
		ASSERT((idOpak & 0x00ffffff) == idOpak);	//24 bity max
		ASSERT((idMag &  0x0000ffff) == idMag);		//16 bitów max

		return 
			(hyper_key(idProd) << 40) | (hyper_key(idOpak) << 16) | hyper_key(idMag);
	}

	inline void n5gmstan_glob::_crack_key(hyper_key hypKey,long & ridMag,long & ridProd,long & ridOpak)
	{
		ridMag = long(hypKey & 0x0000ffff);
		ridOpak = long((hypKey >> 16) & 0x00ffffff);
		ridProd = long((hypKey >> 40) & 0x00ffffff);
	}

	inline void db_n5gmstan::set_ilosc(const quantity & rcurInpIlosc)
	{
		m_curIlosc = rcurInpIlosc;
	}

	//------------------------------------------------------------------------------
}

using namespace navogm_server;

#else
	#error File already included
#endif

