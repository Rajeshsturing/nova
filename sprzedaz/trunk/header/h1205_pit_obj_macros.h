





#macro XDF_PIT_REJESTRACJA(_pit_)				\
	<embedded>									\
		<name>_pit_##_dDataOd</name>			\
		<sqltype>SQLdate</sqltype>				\
		<humanname>Pocz¹tek okresu</humanname>	\
		<nonempty/>								\
	</embedded>									\
	<embedded>									\
		<name>_pit_##_dDataDo</name>			\
		<sqltype>SQLdate</sqltype>				\
		<humanname>Koniec okresu</humanname>	\
		<nonempty/>								\
	</embedded>									\
	<ref>										\
		<name>_pit_##_pUrzadSkarbowy</name>		\
		<humanname>Urz¹d skarbowy</humanname>	\
		<typeid>TYPEID_N5INSTYTUCJA</typeid>	\
		<optional/>									\
	</ref>											\
	<embedded>										\
		<name>_pit_##_strUS</name>					\
		<sqltype>SQLvc256</sqltype>					\
		<humanname>Urz¹d skarbowy</humanname>		\
	</embedded>										\
	<ref>											\
		<name>_pit_##_pUzytRej</name>				\
		<humanname>Wprowadzi³</humanname>			\
		<typeid>TYPEID_N5UZYTKOWNIK</typeid>		\
		<optional/>									\
	</ref>											\
	<embedded>										\
		<name>_pit_##_strImieRej</name>				\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Imiê</humanname>					\
	</embedded>										\				
	<embedded>										\
		<name>_pit_##_strNazwiskoRej</name>			\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Nazwisko</humanname>				\
	</embedded>										\
	<ref>									\
		<name>_pit_##_pZadanie</name>			\
		<humanname>Zadanie</humanname>			\
		<typeid>TYPEID_N5ZADANIE</typeid>		\
		<optional/>								\
	</ref>										\
	<ref>										\
		<name>_pit_##_pSchematDekr</name>		\
		<humanname>Schemat dekretacji</humanname>\
		<typeid>TYPEID_N5SCHEMATDEKR</typeid>		\
		<optional/>									\
	</ref>											\
	<ref>											\
		<name>_pit_##_pDowKsieg</name>				\
		<humanname>Dowód ksiêgowy</humanname>			\
		<typeid>TYPEID_N5DOWODKSIEG</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
		<name>_pit_##_pTransakcja</name>				\
		<humanname>Transakcja</humanname>				\
		<typeid>TYPEID_N5TRANSAKCJA</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
		<name>_pit_##_pUzytModyf</name>					\
		<humanname>Ostatnio zmodyfikowa³</humanname>	\
		<typeid>TYPEID_N5UZYTKOWNIK</typeid>			\
		<optional/>										\
	</ref>



#macro XDF_PIT_PLATNIK(_pit_)						\
	<embedded>										\
		<name>_pit_##_strNIPPlatnik</name>			\
		<sqltype>SQLvc20</sqltype>					\
		<humanname>NIP P³atnika</humanname>			\
		<nonempty/>									\
	</embedded>										\
	<enum>											\
		<name>_pit_##_eTypPlatnika</name>			\
		<humanname>Rodzaj p³atnika</humanname>		\
		<default>1</default>						\
		<item>p³atnik niebêdacy osob¹ fizyczn¹</item>	\
		<item>osoba fizyczna</item>						\
	</enum>												\
	<embedded>										\		
		<name>_pit_##_strNazwaPlatnik</name>		\
		<sqltype>SQLvc256</sqltype>					\
		<humanname>Nazwa p³atnika</humanname>					\
	</embedded>										\				
	<embedded>										\
		<name>_pit_##_strImiePlatnik</name>			\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Imiê</humanname>					\
	</embedded>										\				
	<embedded>										\
		<name>_pit_##_strNazwiskoPlatnik</name>		\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Nazwisko</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_dDataUrPlatnik</name>			\
		<sqltype>SQLdate</sqltype>					\
		<humanname>Data urodzenia</humanname>		\
		<default>null</default>						\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strKrajPlatnik</name>			\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Kraj</humanname>					\
		<default>Polska</default>					\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strWojewodztwoPlatnik</name>	\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Wojewodztwo</humanname>			\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strPowiatPlatnik</name>		\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Powiat</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strGminaPlatnik</name>		\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Gmina</humanname>				\
	</embedded>										\
		<embedded>									\
		<name>_pit_##_strUlicaPlatnik</name>		\
		<sqltype>SQLvc64</sqltype>					\
		<humanname>Ulica</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strNrDomuPlatnik</name>		\
		<sqltype>SQLvc8</sqltype>					\
		<humanname>Nr domu</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strNrLokaluPlatnik</name>		\
		<sqltype>SQLvc8</sqltype>					\
		<humanname>Nr lokalu</humanname>			\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strKodPlatnik</name>			\
		<sqltype>SQLvc8</sqltype>					\
		<humanname>Kod pocztowy</humanname>			\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strPocztaPlatnik</name>		\
		<sqltype>SQLvc64</sqltype>					\
		<humanname>Poczta</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strMiejscowoscPlatnik</name>	\
		<sqltype>SQLvc64</sqltype>					\
		<humanname>Miejscowosc</humanname>			\
	</embedded>											
		


#macro XDF_PIT_PODATNIK(_pit_)						\
	<embedded>										\
		<name>_pit_##_strNIPPodatnik</name>			\
		<sqltype>SQLvc20</sqltype>					\
		<humanname>NIP Podatnika</humanname>		\
		<nonempty/>									\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strImie</name>				\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Imiê</humanname>					\
		<nonempty/>									\
	</embedded>										\				
	<embedded>										\
		<name>_pit_##_strNazwisko</name>			\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Nazwisko</humanname>				\
		<nonempty/>									\
	</embedded>										\
	<embedded>									\
		<name>_pit_##_dDataUr</name>			\
		<sqltype>SQLdate</sqltype>				\
		<humanname>Data urodzenia</humanname>	\
		<default>null</default>					\
		<nonempty/>									\
	</embedded>									\
	<embedded>										\
		<name>_pit_##_strKraj</name>				\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Kraj</humanname>					\
		<default>Polska</default>					\
		<nonempty/>									\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strWojewodztwo</name>			\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Wojewodztwo</humanname>			\
		<nonempty/>									\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strPowiat</name>				\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Powiat</humanname>				\
	</embedded>										\
	<embedded>										\
		<name>_pit_##_strGmina</name>				\
		<sqltype>SQLvc32</sqltype>					\
		<humanname>Gmina</humanname>					\
	</embedded>											\
		<embedded>										\
		<name>_pit_##_strUlica</name>					\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Ulica</humanname>					\
	</embedded>											\
	<embedded>											\
		<name>_pit_##_strNrDomu</name>					\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr domu</humanname>					\
		<nonempty/>									\
	</embedded>											\
	<embedded>											\
		<name>_pit_##_strNrLokalu</name>				\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr lokalu</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_pit_##_strKod</name>						\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Kod pocztowy</humanname>				\
		<nonempty/>									\
	</embedded>											\
	<embedded>											\
		<name>_pit_##_strPoczta</name>					\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Poczta</humanname>					\
	</embedded>											\
	<embedded>											\
		<name>_pit_##_strMiejscowosc</name>				\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Miejscowosc</humanname>				\
		<nonempty/>									\
	</embedded>											



		

#macro XDF_CURRENCY(_fld_,_hname_)							\
	<embedded>												\
		<name>_fld_</name>									\
		<sqltype>SQLcurrency</sqltype>						\
		<humanname>_hname_</humanname>						\
	</embedded>

#macro XDF_CURRENCY_VIRTUAL(_fld_,_hname_)					\
	<embedded>												\
		<name>_fld_</name>									\
		<sqltype>SQLcurrency</sqltype>						\
		<humanname>_hname_</humanname>						\
		<hidden/>											\
		<virtual/>											\
	</embedded>

#macro XDF_C1_VIRTUAL(_fld_,_hname_)						\
	<embedded>												\
		<name>_fld_</name>									\
		<sqltype>SQLc1</sqltype>							\
		<humanname>_hname_</humanname>						\
		<default>0</default>								\
		<hidden/>											\
		<virtual/>											\
	</embedded>


#macro XDF_LONG(_fld_,_hname_)								\
	<embedded>												\
		<name>_fld_</name>									\
		<sqltype>SQLlong</sqltype>							\
		<humanname>_hname_</humanname>						\
	</embedded>




#macro XDF_PIT_POZROLDZIALGOSP(_pit_,_nr_)					\
	<embedded>												\
		<name>_pit_##_strNIP##_nr_</name>					\
		<sqltype>SQLvc20</sqltype>							\
		<humanname>NIP _nr_</humanname>							\
	</embedded>												\
	<embedded>												\
		<name>_pit_##_strREGON##_nr_</name>					\
		<sqltype>SQLvc20</sqltype>							\
		<humanname>REGON _nr_</humanname>						\
	</embedded>													\
	<embedded>													\
		<name>_pit_##_strNazwa##_nr_</name>						\
		<sqltype>SQLvc256</sqltype>								\
		<humanname>Nazwa pe³na _nr_</humanname>				\
	</embedded>													\
	<embedded>													\
		<name>_pit_##_strMiejsce##_nr_</name>					\
		<sqltype>SQLvc256</sqltype>								\
		<humanname>Miejsce prowadzenia dzia³alnoœci _nr_</humanname>	\
	</embedded>															\	
	XDF_CURRENCY(_pit_##_curUdzial##_nr_,Udzia³ _nr_)					\
	XDF_CURRENCY(_pit_##_curPrzychod##_nr_,Przychod _nr_)				\
	XDF_CURRENCY(_pit_##_curKoszty##_nr_,Koszty _nr_)					\
	XDF_CURRENCY(_pit_##_curDochod##_nr_,Dochód _nr_)					\
	XDF_CURRENCY(_pit_##_curStrata##_nr_,Strata _nr_)




#macro XDF_ISTAT_PLATNIK(_pit_)						\
	XDF_PIT_PLATNIK(_pit_)							\
	<embedded>										\
		<name>_pit_##_strREGONPlatnik</name>		\
		<sqltype>SQLvc20</sqltype>					\
		<humanname>REGON P³atnika</humanname>		\
		<nonempty/>									\
	</embedded>	





#macro INIT_PLATIK_FROM_CURRENT_FIRMA(_deklaracja_,_table_)				\
function _table_##_init_from_current_firma()			\
	dim pFirma:set pFirma = getCurrentFirma()				\
	this_._deklaracja_##_strNIPPlatnik = pFirma.strNip			\
	if this_.type = TYPEID_N5ISTAT then							\
		this_._deklaracja_##_strREGONPlatnik = pFirma.strREGON	\
	end if														\
	this_._deklaracja_##_strNazwaPlatnik = pFirma.strNazwa		\
	this_._deklaracja_##_strKrajPlatnik = "Polska"				\
	if pFirma.n5firma_osoba_fizyczna then					\
		this_._deklaracja_##_eTypPlatnika = clng(2)			\
	else													\
		this_._deklaracja_##_eTypPlatnika = clng(1)			\
	end if													\
	if not pFirma.pMiejscowosc is nothing then				\
		this_._deklaracja_##_strMiejscowoscPlatnik = pFirma.pMiejscowosc.text	\
		if not pFirma.pMiejscowosc.pWojewodztwo is nothing then				\
			this_._deklaracja_##_strWojewodztwoPlatnik = pFirma.pMiejscowosc.pWojewodztwo.text	\
		end if																				\
		if not pFirma.pMiejscowosc.mie_pPowiat is nothing then								\
			this_._deklaracja_##_strPowiatPlatnik = pFirma.pMiejscowosc.mie_pPowiat.text		\
		end if																				\
		if not pFirma.pMiejscowosc.mie_pGmina is nothing then								\
			this_._deklaracja_##_strGminaPlatnik = pFirma.pMiejscowosc.mie_pGmina.text			\
		end if																				\
	end if																					\
	this_._deklaracja_##_strUlicaPlatnik = pFirma.strUlica										\
	this_._deklaracja_##_strNrDomuPlatnik = pFirma.strNrDomu									\
	this_._deklaracja_##_strNrLokaluPlatnik = pFirma.strNrLokalu								\
	this_._deklaracja_##_strKodPlatnik = pFirma.strKod											\
	this_._deklaracja_##_strPocztaPlatnik = pFirma.strPoczta									\
	if this_.type = TYPEID_N5PIT4 then														\
		this_.n5pit4_custom_init															\
	end if																					\
	if this_.type = TYPEID_N5ROZLVAT then													\
		this_.n5rozlvat_custom_init															\	
	end if																					\
	if this_.type = TYPEID_N5PIT11 then														\
		this_.n5pit11_custom_init															\
	end if																					\
end function																		