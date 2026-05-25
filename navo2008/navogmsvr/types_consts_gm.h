/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2003 NAVO

	navogm - modu³ gospodarki magazynowej (server)

	REV:KB:2003-11-09
*/


#ifndef _TYPES_CONSTS_GM_H_
#define _TYPES_CONSTS_GM_H_

#define PRODUKCJA_DOKLADNOSC_4_NIE_ZDEF

CY navo_VarCyDiv(CY cyLeft, CY cyRight);


namespace navogm_server
{

	typedef COleCurrency	quantity;
	typedef COleCurrency	price;
	typedef COleCurrency	factor;
	typedef DATE			navogm_date;
	typedef __int64			supply_id;

	//--------------------------------------------------------------------
	const long GMBORDER_VALID	= 999999999;
	const long GLOBPROF_GMBORDER = 1063;
	const long GLOBPROF_PTBORDER = 1091;

	const long TYPEID_N5GMOP	= 10225;
	const long TYPEID_N5GMSTAN	= 10226;
	const long TYPEID_N5GMREPAIR= 10227;
	
	//DB11
	const long TYPEID_N5PTOP = 10250;
	const long TYPEID_N5PTSTAN = 10251;


	const long N5GMOP_FLD_IDOBJ		= 0;
	const long N5GMOP_FLD_VERSION	= 1;
	const long N5GMOP_FLD_TYPOP		= 2;
	const long N5GMOP_FLD_NUMOP		= 3;
	const long N5GMOP_FLD_LP		= 4;
	const long N5GMOP_FLD_ILOSC		= 5;
	const long N5GMOP_FLD_CENA		= 6;
	const long N5GMOP_FLD_WARTOSC	= 7;
	const long N5GMOP_FLD_IDPROD	= 8;
	const long N5GMOP_FLD_IDOPAK	= 9;
	const long N5GMOP_FLD_IDMAG		= 10;
	const long N5GMOP_FLD_IDDOST	= 11;
	const long N5GMOP_FLD_IDDOSTLP	= 12;
	const long N5GMOP_FLD_DATAWAZN	= 13;
	const long N5GMOP_FLD_NUMOPREL	= 14;
	const long N5GMOP_FLD_LPREL		= 15;
	const long N5GMOP_FLD_PREL		= 16;

	const long N5GMSTAN_FLD_IDOBJ	= 0;
	const long N5GMSTAN_FLD_VERSION = 1;
	const long N5GMSTAN_FLD_IDPROD	= 2;
	const long N5GMSTAN_FLD_IDOPAK	= 3;
	const long N5GMSTAN_FLD_IDMAG	= 4;
	const long N5GMSTAN_FLD_CENA	= 5;
	const long N5GMSTAN_FLD_ILOSC	= 6;
	const long N5GMSTAN_FLD_IDDOST	= 7;
	const long N5GMSTAN_FLD_IDDOSTLP= 8;
	const long N5GMSTAN_FLD_DATAWAZN= 9;
	const long N5GMSTAN_FLD_NUMOP	= 10;
	const long N5GMSTAN_FLD_LP		= 11;

	const COleCurrency curZero = COleCurrency(0,0);
	const COleCurrency curEverything = COleCurrency(999999999,0);
	//--------------------------------------------------------------------

	inline long _ado_getlong(ADODB::_RecordsetPtr & rpoRS, long nFldNr)
	{
		return rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue().lVal;
	}

	inline DATE _ado_getdate(ADODB::_RecordsetPtr & rpoRS, long nFldNr)
	{
		return rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue().date;
	}

	inline CURRENCY _ado_getcurrency(ADODB::_RecordsetPtr & rpoRS, long nFldNr)
	{
		CSmartOleVariant oSOV(rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue());
		oSOV.ChangeType(VT_CY);
		return oSOV.GetCurrency();
	}

	inline CString _ado_getstring(ADODB::_RecordsetPtr & rpoRS, long nFldNr)
	{
		return CString(rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue().bstrVal);
	}

	inline bool _ado_isnull(ADODB::_RecordsetPtr & rpoRS, long nFldNr)
	{
		return rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue().vt == VT_NULL ||
			rpoRS->Fields->GetItem(_variant_t(nFldNr))->GetValue().vt == VT_EMPTY;
	}

	ADODB::_RecordsetPtr _ado_openRS(const CString & roSQL,ADODB::_ConnectionPtr & rpoConnectionPtr, bool bLargeGM);

	inline price operator * (price cyPrc, quantity cyQty)
	{
		CURRENCY cyResult;
		::VarCyMul( cyPrc, cyQty, &cyResult);
		return cyResult;
	}

	inline price operator / (price cyPrc, quantity cyQty)
	{
		return navo_VarCyDiv(cyPrc, cyQty);
	}

	void floor_currency_2(CY & rcurRaw);
	//zaokr¹glenie do dwóch znaków po precinku
	inline void round_currency_2(CY & rcurRaw)
	{
		long nDroppedPart = long(rcurRaw.int64 % __int64(100));
		if(nDroppedPart != 0)
		{
			floor_currency_2(rcurRaw);

			if(nDroppedPart > 49)
			{
				rcurRaw.int64 += __int64(100);
			}
			else
			{
				if(nDroppedPart < -49)
				{
					rcurRaw.int64 -= __int64(100);
				}
			}
		}
	}
	
	//obciêcie w dó³ do dwóch znaków po przecinku
	inline void floor_currency_2(CY & rcurRaw)
	{
		rcurRaw.int64 = (rcurRaw.int64 / __int64(100)) * __int64(100);
	}

	//--------------------------------------------------------------------
	enum eWorkMode
	{
		wm_gm,	//GMop - gospodarka magazynowa
		wm_pt,	//PTop - platnosci
	};
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	//-------------- server's privte exceptions --------------------------
	//-------------- also used as error information (not throwing) -------
	//--------------------------------------------------------------------
	
	class cgms_exception
	{
	public:
		enum eExcCode
		{
			sec_operation_doesnt_compensate		= 1,//Rozbicia i warianty operacji siê nie kompensuj¹!
			sec_no_such_supply			= 2,		//Brak dostawy o wskazanym (rêcznie) numerze
			sec_not_enough_quantity		= 3,		//Zabrak³o towaru
			sec_zero_product_quantity	= 4,		//Zerowa iloœæ wyrobu
			sec_not_supply_at_all		= 5,		//Nie bylo nigdy dostawy
			sec_lock_failed				= 6,		//Lock failed
		};
		cgms_exception(eExcCode eCode);
		cgms_exception(eExcCode eCode,long nNumOp,long nLP,long idObj);
		cgms_exception(eExcCode eCode,long nNumOp,long nLP,long idObj,
			long idProdukt,long idOpakowanie,long idMagazyn,quantity curIlosc);
		~cgms_exception();

		eExcCode get_code() const;
		
		const long get_numop() const;
		const long get_lp() const;
		const long get_idprod() const;
		const long get_idopak() const;
		const long get_idmag() const;
		const quantity get_ilosc() const;
	private:
		eExcCode m_eCode;
		const long m_nNumOp;
		const long m_nLP;
		const long m_idObj;
		const long m_idProdukt;
		const long m_idOpakowanie;
		const long m_idMagazyn;
		const quantity	m_curIlosc;
	};

	//--------------------------------------------------------------------
	// logging utility
	//--------------------------------------------------------------------
	
	class csrvlogger
	{
	public:
		csrvlogger(SCP<IStream> poLogStreamSP,bool bContinueOnError);
		~csrvlogger();
		csrvlogger & operator << (const TCHAR * poText);
		
		void on_error(const cgms_exception & roException);

		bool is_open() const;
		bool was_error() const;
		int get_error_count() const;
		bool was_only_missing_qty_errors();
	private:
		CStreamHolder m_oStreamHolder;
		bool		  m_bContinueOnError;
		int			  m_iErrorCount;
		int			  m_iNotEnoughQtyErrorCount;
	};

	//-----------------------------------------------------------
	//-----------------------------------------------------------

	inline cgms_exception::cgms_exception(eExcCode eCode) :
		m_eCode(eCode),
		m_nNumOp(0),
		m_nLP(0),
		m_idObj(0),
		m_idProdukt(0),
		m_idOpakowanie(0),
		m_idMagazyn(0)
	{
	}

	inline cgms_exception::cgms_exception(eExcCode eCode,long nNumerDost,long nLPDost,long idObj) :
		m_eCode(eCode),
		m_nNumOp(nNumerDost),
		m_nLP(nLPDost),
		m_idObj(idObj),
		m_idProdukt(0),
		m_idOpakowanie(0),
		m_idMagazyn(0)
	{
	}

	inline cgms_exception::cgms_exception(eExcCode eCode,long nNumerDost,long nLPDost,long idObj,
			long idProdukt,long idOpakowanie,long idMagazyn,quantity curIlosc) :
		m_eCode(eCode),
		m_nNumOp(nNumerDost),
		m_nLP(nLPDost),
		m_idObj(idObj),
		m_idProdukt(idProdukt),
		m_idOpakowanie(idOpakowanie),
		m_idMagazyn(idMagazyn),
		m_curIlosc(curIlosc)
	{
	}

	inline cgms_exception::~cgms_exception()
	{
	}

	inline cgms_exception::eExcCode cgms_exception::get_code() const
	{
		return m_eCode;
	}
		
	inline const long cgms_exception::get_numop() const
	{
		return m_nNumOp;
	}

	inline const long cgms_exception::get_lp() const
	{
		return m_nLP;
	}

	inline const long cgms_exception::get_idprod() const
	{
		return m_idProdukt;
	}

	inline const long cgms_exception::get_idopak() const
	{
		return m_idOpakowanie;
	}

	inline const long cgms_exception::get_idmag() const
	{
		return m_idMagazyn;
	}
	
	inline const quantity cgms_exception::get_ilosc() const
	{
		return m_curIlosc;
	}

	//-----------------------------------------------------
	// funkcja rozdziela cyTotalQty na 1 lub 2 czêœci, tak aby 
	// cyQty1 + cyQty2 = cyTotalQty
	// oraz
	// cyVal1 + cyVal2 = cyTotalVal
	//
	// algorytm wyznacza odpowiedni podzial ilosci i cen
	//
	// funkcja zwraca true gdy powsta³y 2 pozycje
	//-----------------------------------------------------
	bool split_value(price cyTotalValue,quantity cyTotalQty,price & rcyPrice1,quantity & rcyQty1,price & rcyPrice2,quantity & rcyQty2,long nRoundQty);
	//--------------------------------------------------------------------
	// logging utility
	//--------------------------------------------------------------------
	inline csrvlogger::csrvlogger(SCP<IStream> poLogStreamSP,bool bContinueOnError) :
		m_oStreamHolder(poLogStreamSP),
		m_bContinueOnError(bContinueOnError),
		m_iErrorCount(0),
		m_iNotEnoughQtyErrorCount(0)
	{
		(*this) << "<?xml version=\"1.0\" encoding=\"windows-1250\" ?>\r\n<navogmsrvlog>\r\n";
	}

	inline csrvlogger::~csrvlogger()
	{
		(*this) << "</navogmsrvlog>\r\n";
	}

	inline csrvlogger & csrvlogger::operator << (const TCHAR * poText)
	{
		if(is_open())
		{
			m_oStreamHolder.WriteString(poText);
		}
		return *this;
	}

	inline bool csrvlogger::is_open() const
	{
		return m_oStreamHolder.IsStream();
	}

	inline void csrvlogger::on_error(const cgms_exception & roException)
	{
		(*this) << "<error>\r\n";
		(*this) << "\t<code>" + Long2String(long(roException.get_code())) + "</code>\r\n";
		(*this) << "\t<numop>" + Long2String(roException.get_numop()) + "</numop>\r\n";
		(*this) << "\t<lp>" + Long2String(roException.get_lp()) + "</lp>\r\n";
		(*this) << "\t<idprod>" + Long2String(roException.get_idprod()) + "</idprod>\r\n";
		(*this) << "\t<idopak>" + Long2String(roException.get_idopak()) + "</idopak>\r\n";
		(*this) << "\t<quantity>" + Variant2String(roException.get_ilosc()) + "</quantity>\r\n";
		(*this) << "\t<idmag>" + Long2String(roException.get_idmag()) + "</idmag>\r\n";
		
		(*this) << "</error>\r\n";
		m_iErrorCount++;
		
		if(roException.get_code() == cgms_exception::sec_not_enough_quantity)
		{
			m_iNotEnoughQtyErrorCount++;
		}

		if(!m_bContinueOnError)
		{
			throw roException;
		}
	}
	
	inline bool csrvlogger::was_error() const
	{
		return (m_iErrorCount != 0);
	}

	inline int csrvlogger::get_error_count() const
	{
		return m_iErrorCount;
	}

	inline bool csrvlogger::was_only_missing_qty_errors()
	{
		return (m_iErrorCount == m_iNotEnoughQtyErrorCount);
	}
}


class CNavoObjectCoordinator;

/*
namespace navogm_svr
{
	//--------------------------------------------------------------------
	//-------------- server's privte exceptions --------------------------
	//--------------------------------------------------------------------
	
	class csrvexception
	{
	public:
		enum eExcCode
		{
			sec_eof_in_next_oper		= 1,		//Nieoczekiwany EOF podczas wczytywania kolejnej operacji
			sec_no_such_supply			= 2,		//Brak dostawy o wskazanym (rêcznie) numerze
			sec_not_enough_quantity		= 3,		//Zabrak³o towaru
			sec_duplicated_entry_in_korop=4,		//Powielenie wpisów n5koropmag
		};
		csrvexception(eExcCode eCode);
		csrvexception(eExcCode eCode,long nNumerDost,long nLPDost);
		csrvexception(eExcCode eCode,long nNumerDost,long nLPDost,long idProdukt,long idOpakowanie,long idMagazyn);
		~csrvexception();

		eExcCode get_code() const;
	private:
		eExcCode m_eCode;
		long m_nNumerDost;
		long m_nLPDost;
		long m_idProdukt;
		long m_idOpakowanie;
		long m_idMagazyn;
	};


	//-----------------------------------------------------------
	//-----------------------------------------------------------

	inline csrvexception::csrvexception(eExcCode eCode) :
		m_eCode(eCode),
		m_nNumerDost(0),
		m_nLPDost(0),
		m_idProdukt(0),
		m_idOpakowanie(0),
		m_idMagazyn(0)
	{
	}

	inline csrvexception::csrvexception(eExcCode eCode,long nNumerDost,long nLPDost) :
		m_eCode(eCode),
		m_nNumerDost(nNumerDost),
		m_nLPDost(nLPDost),
		m_idProdukt(0),
		m_idOpakowanie(0),
		m_idMagazyn(0)
	{
	}

	inline csrvexception::csrvexception(eExcCode eCode,long nNumerDost,long nLPDost,long idProdukt,long idOpakowanie,long idMagazyn) :
		m_eCode(eCode),
		m_nNumerDost(nNumerDost),
		m_nLPDost(nLPDost),
		m_idProdukt(idProdukt),
		m_idOpakowanie(idOpakowanie),
		m_idMagazyn(idMagazyn)
	{
	}

	inline csrvexception::~csrvexception()
	{
	}

	inline csrvexception::eExcCode csrvexception::get_code() const
	{
		return m_eCode;
	}


}

*/

inline CY navo_VarCyDiv(CY cyLeft, CY cyRight)
{
	if(cyRight.int64 == __int64(0))
	{
		ThrowNavoException1(ERCO_TODO,IDPAGE_NOTAVAILABLE,SCODE_To_String(DISP_E_OVERFLOW));
	}
	
	//TODO:LR: SPRAWDZAC i RAPORTOWAÆ PRZEPELNIENIA
	
	CY cyResult;
	cyResult.int64 = ( cyLeft.int64 * _int64(10000)) / cyRight.int64;
	
	return cyResult;
}

namespace navogm_server
{

inline bool split_value(price cyTotalValue,quantity cyTotalQty,price & rcyPrice1,quantity & rcyQty1,price & rcyPrice2,quantity & rcyQty2,long /*nRoundQty*/)
{
	//oryginalny algorytm
#ifndef PRODUKCJA_DOKLADNOSC_4	
	//srednia cena
	price curAvePrice = cyTotalValue / cyTotalQty;
	floor_currency_2(curAvePrice.m_cur);	//zaokr w dol do 0,00
	rcyPrice1 = curAvePrice;
	//wartoœæ "przenoszona" przez 1-sz¹ czêœæ
	price cyValue1 = rcyPrice1 * cyTotalQty;
	round_currency_2(cyValue1.m_cur);	
	//próbuj wyliczyæ drug¹ czêœæ
	rcyPrice2.m_cur.int64 = rcyPrice1.m_cur.int64 + 100;
	rcyQty2 = (cyTotalValue - cyValue1) / price(0,100);
	rcyQty1 = cyTotalQty - rcyQty2;
	return ((rcyQty2 != curZero) != FALSE);
#else
	//niby split
	rcyPrice1 = cyTotalValue / cyTotalQty;
	rcyQty1 = cyTotalQty;
	rcyQty2 = curZero;
	rcyPrice2 = rcyPrice1;
	return ((rcyQty2 != curZero) != FALSE);
#endif
}
}

#else
	#error File already included
#endif


/*
STDAPI VarHiLoDiv( long leftHi, LONGLONG rightLo, CY & rcyResult, unsigned long & reminder)
{
	if( rightLo == 0)
	{
		return DISP_E_OVERFLOW;
	}

	long tmp = (leftHi % rightLo)*long(10000);
	rcyResult.Hi = (leftHi / rightLo)*long(10000) + tmp / rightLo;
	tmp = (tmp % rightLo)*long(10000);
	rcyResult.Lo = tmp / rightLo;
	reminder = tmp % rightLo;
    return NOERROR;
}

STDAPI VarHiHiDiv( long leftHi, LONGLONG rightHi, CY & rcyResult, unsigned long & reminder)
{
	if( rightHi == 0)
	{
		return DISP_E_OVERFLOW;
	}

	rcyResult.Hi = (leftHi / rightHi);
	long tmp = (leftHi % rightHi)*long(10000);
	rcyResult.Lo = tmp / rightHi;
	reminder = tmp % rightHi;
    return NOERROR;
}

STDAPI VarLoLoDiv( long leftLo, LONGLONG rightLo, CY & rcyResult, unsigned long & reminder)
{
	rcyResult.Hi = (leftLo / rightLo);
	long tmp = (leftLo % rightLo)*long(10000);
	rcyResult.Lo = tmp / rightLo;
	reminder = tmp % rightLo;
    return NOERROR;
}

STDAPI VarLoHiDiv( long leftLo, LONGLONG rightHi, CY & rcyResult, unsigned long & reminder)
{
	if( rightHi == 0)
	{
		return DISP_E_OVERFLOW;
	}

	rcyResult.Hi = 0;

	if( rightHi > 100000)
	{
		rcyResult.Lo = long(0);
		reminder = long(0);
	}
	else
	{
		rcyResult.Lo = leftLo / rightHi;
		reminder = leftLo % rightHi;
	}

    return NOERROR;
}
*/
