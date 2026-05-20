
#define XDF_NRDOK										\
	<embedded>											\
		<name>strNrDok</name>							\
		<sqltype>SQLvc32</sqltype>						\
		<humanname>Numer dokumentu</humanname>			\
		<unique/>										\
	</embedded>

#macro XDF_OSTMODYF(_obj_)								\
	<ref>												\
		<name>_obj_##pUzytModyf</name>					\
		<humanname>Ostatnio zmodyfikowa³</humanname>	\
		<typeid>TYPEID_N5UZYTKOWNIK</typeid>			\
	</ref>

#macro XDF_NETTO(_stkod_,_sthname_)						\
	<embedded>											\
		<name>curNetto##_stkod_</name>					\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>Netto w stawce _sthname_</humanname>	\
	</embedded>

#macro XDF_VAT(_stkod_,_sthname_)						\
	<embedded>											\
		<name>curVat##_stkod_</name>					\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>VAT w stawce _sthname_</humanname>	\
	</embedded>

#macro XDF_VAT_ODL(_stkod_, _sthname_)							\
	<embedded>													\
	<name>curVatOdl##_stkod_</name>								\
		<sqltype>SQLcurrency</sqltype>							\
		<humanname>VAT odliczany w stawce _sthname_</humanname>	\
	</embedded>

#macro XDF_NETTOVAT(_stkod_,_sthname_)					\
	XDF_NETTO(_stkod_,_sthname_)						\
	XDF_VAT(_stkod_,_sthname_)							\
	<embedded>											\
		<name>curBrutto##_stkod_</name>					\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>Brutto w stawce _sthname_</humanname>	\
		<virtual/>										\
	</embedded>

#macro VDF_REINIT_BRUTTO(_obj_,_stkod_)						\
		this_.curBrutto##_stkod_ = this_.curNetto##_stkod_ + this_.curVat##_stkod_		\
		n5##_obj_##_curBrutto##_stkod_##_change ccur(0)									

#ifdef ENABLE_DB12

#define XDF_STAWKAVAT									\
	<embedded>											\
		<name>eVAT</name>								\
		<sqltype>SQLlong</sqltype>						\
		<humanname>Stawka VAT</humanname>				\
	</embedded>

#else

#define XDF_STAWKAVAT									\
	<enum>												\
		<name>eVAT</name>								\
		<humanname>Stawka VAT</humanname>				\
		<default>STAWKA_VAT_22</default>				\
		<item>0%</item>									\
		<item>zwolniony</item>							\
		<item>nie podlega</item>						\
		<item>2%</item>									\
		<item>3%</item>									\
		<item>4%</item>									\
		<item>7%</item>									\
		<item>12%</item>								\
		<item>17%</item>								\
		<item>22%</item>								\
		<item>5%</item>									\
		<item>6%</item>                                 \
		<item>8%</item>									\
		<item>23%</item>                                \
	</enum>

#endif

#macro XDF_ADRES(_kogo_)								\
	<embedded>											\
		<name>strUlica</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Ulica _kogo_</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>strNrDomu</name>							\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr domu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
		<name>strNrLokalu</name>						\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr lokalu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
		<name>strKod</name>								\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Kod pocztowy _kogo_</humanname>		\
	</embedded>											\
	<embedded>											\
		<name>strPoczta</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Poczta _kogo_</humanname>			\
	</embedded>											\
	<ref>												\
		<name>pMiejscowosc</name>						\
		<humanname>Miejscowoœæ _kogo_</humanname>		\
		<typeid>TYPEID_N5MIEJSCOWOSC</typeid>			\
	</ref>												\
	<ref>												\
		<name>pKraj</name>								\
		<humanname>Kraj _kogo_</humanname>				\
		<typeid>TYPEID_N5KRAJ</typeid>					\
	</ref>												\
	<embedded>											\
		<name>curSzerGeogr</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>Szerokoœc geograficzna</humanname>	\
	</embedded>											\
	<embedded>											\
		<name>curDlugGeogr</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>D³ugoœæ geograficzna</humanname>		\
	</embedded>											


#macro XDF_ADRES_NAZWA(_kogo_,_pre_,_suf_)				\
	<embedded>											\
		<name>_pre_##str##Nazwa##_suf_##</name>			\
		<sqltype>SQLvc128</sqltype>						\
		<humanname>Nazwa _kogo_</humanname>				\
	</embedded>											\
	XDF_ADRES_BLOCK2(_kogo_,_pre_,_suf_)


#macro XDF_ADRES_BLOCK(_kogo_,_pre_,_suf_)								\
	<embedded>											\
	<name>str##_pre_##Ulica##_suf_##</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Ulica _kogo_</humanname>				\
	</embedded>											\
	<embedded>											\
	<name>str##_pre_##NrDomu##_suf_##</name>							\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr domu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
	<name>str##_pre_##NrLokalu##_suf_##</name>						\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr lokalu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
	<name>str##_pre_##Kod##_suf_##</name>								\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Kod pocztowy _kogo_</humanname>		\
	</embedded>											\
	<embedded>											\
	<name>str##_pre_##Poczta##_suf_##</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Poczta _kogo_</humanname>			\
	</embedded>											\
	<ref>												\
	<name>p##_pre_##Miejscowosc##_suf_##</name>						\
		<humanname>Miejscowoœæ _kogo_</humanname>		\
		<typeid>TYPEID_N5MIEJSCOWOSC</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
	<name>p##_pre_##Kraj##_suf_##</name>								\
		<humanname>Kraj _kogo_</humanname>				\
		<typeid>TYPEID_N5KRAJ</typeid>					\
		<optional/>										\
	</ref>												\
	<embedded>											\
	<name>cur##_pre_##SzerGeogr##_suf_##</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>Szerokoœc geograficzna</humanname>	\
	</embedded>											\
	<embedded>											\
	<name>cur##_pre_##DlugGeogr##_suf_##</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>D³ugoœæ geograficzna</humanname>		\
	</embedded>											



#define XDF_REJDOWSCHEM									\
	<ref>												\
		<name>pRejestrDok</name>						\
		<humanname>Rejestr dokumentów</humanname>		\
		<typeid>TYPEID_N5REJESTRDOK</typeid>			\
	</ref>												\
	<ref>												\
		<name>pDowodKsieg</name>						\
		<humanname>Dowód ksiegowy</humanname>			\
		<typeid>TYPEID_N5DOWODKSIEG</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
		<name>pSchematDekr</name>						\
		<humanname>Schemat dekretacji</humanname>		\
		<typeid>TYPEID_N5SCHEMATDEKR</typeid>			\
		<optional/>										\
	</ref>
		

#macro XDF_ADRES_BLOCK2(_kogo_,_pre_,_suf_)								\
	<embedded>											\
	<name>_pre_##str##Ulica##_suf_##</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Ulica _kogo_</humanname>				\
	</embedded>											\
	<embedded>											\
	<name>_pre_##str##NrDomu##_suf_##</name>							\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr domu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
	<name>_pre_##str##NrLokalu##_suf_##</name>						\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Nr lokalu _kogo_</humanname>			\
	</embedded>											\
	<embedded>											\
	<name>_pre_##str##Kod##_suf_##</name>								\
		<sqltype>SQLvc8</sqltype>						\
		<humanname>Kod pocztowy _kogo_</humanname>		\
	</embedded>											\
	<embedded>											\
	<name>_pre_##str##Poczta##_suf_##</name>							\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Poczta _kogo_</humanname>			\
	</embedded>											\
	<ref>												\
	<name>_pre_##p##Miejscowosc##_suf_##</name>						\
		<humanname>Miejscowoœæ _kogo_</humanname>		\
		<typeid>TYPEID_N5MIEJSCOWOSC</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
	<name>_pre_##p##Kraj##_suf_##</name>								\
		<humanname>Kraj _kogo_</humanname>				\
		<typeid>TYPEID_N5KRAJ</typeid>					\
		<optional/>										\
	</ref>												\
	<embedded>											\
	<name>_pre_##cur##SzerGeogr##_suf_##</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>Szerokoœc geograficzna</humanname>	\
	</embedded>											\
	<embedded>											\
	<name>_pre_##cur##DlugGeogr##_suf_##</name>						\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>D³ugoœæ geograficzna</humanname>		\
	</embedded>		


#macro XDF_TELEKOM_BLOCK2(_kogo_,_pre_,_suf_)			\
	<embedded>											\
		<name>_pre_##strTel1##_suf_</name>				\
		<sqltype>SQLvc20</sqltype>						\
		<humanname>Numer telefonu 1</humanname>			\
	</embedded>											\
	<embedded>											\
		<name>_pre_##strTel2##_suf_</name>				\
		<sqltype>SQLvc20</sqltype>						\
		<humanname>Numer telefonu 2</humanname>			\
	</embedded>											\
	<embedded>											\
		<name>_pre_##strTel3##_suf_</name>				\
		<sqltype>SQLvc20</sqltype>						\
		<humanname>Numer telefonu 3</humanname>			\
	</embedded>											\
	<embedded>											\
		<name>_pre_##strFax##_suf_</name>				\
		<sqltype>SQLvc20</sqltype>						\
		<humanname>Numer faksu</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_pre_##strEmail##_suf_</name>				\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Adres e-mail</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_pre_##strWWW##_suf_</name>				\
		<sqltype>SQLvc64</sqltype>						\
		<humanname>Strona WWW</humanname>				\
	</embedded>


#macro XDF_PLACE_DOKUMENT_EXTRA(_datado_opt_)			\
	<ref>												\
		<name>pPracownik</name>							\
		<humanname>Pracownik</humanname>				\
		<typeid>TYPEID_N5PRACOWNIK</typeid>				\
		<optional/>										\
	</ref>												\
	<embedded>											\
		<name>dDataRej</name>							\
		<sqltype>SQLdate</sqltype>						\
		<humanname>Data rejestracji</humanname>			\
		<nonempty/>										\
	</embedded>											\
	<embedded>											\
		<name>dDataOd</name>							\
		<sqltype>SQLdate</sqltype>						\
		<humanname>Pocz¹tek okresu</humanname>			\
		<nonempty/>										\
	</embedded>											\
	<embedded>											\
		<name>dDataDo</name>							\
		<sqltype>SQLdate</sqltype>						\
		<humanname>Koniec okresu</humanname>			\
		_datado_opt_									\
	</embedded>											\
	<ref>												\
		<name>pUzytRej</name>							\
		<humanname>Wprowadzi³</humanname>				\
		<typeid>TYPEID_N5UZYTKOWNIK</typeid>			\
	</ref>												\
	<ref>												\
		<name>pUzytModyf</name>							\
		<humanname>Ostatnio zmodyfikowa³</humanname>	\
		<typeid>TYPEID_N5UZYTKOWNIK</typeid>			\
	</ref>

#define XDF_PLACE_DOKUMENT								\
	XDF_PLACE_DOKUMENT_EXTRA(<nonempty/>)

#define XDF_PLACE_DOKUMENT_NO_END						\
	XDF_PLACE_DOKUMENT_EXTRA(<default>null</default>)


#define XDF_PLACE_TYP_UMOWY								\
	<enum>												\
		<name>eTypUmowy</name>							\
		<humanname>Typ umowy</humanname>				\
		<default>N5PL_UMOWA_O_PRACE</default>			\
		<item>umowa zlecenia</item>						\
		<item>umowa o pracê</item>						\
		<item>umowa o dzie³o</item>						\
	</enum>

#define XDF_PLACE_DOK_ZROD								\
	<wildref>											\
		<name>wrefDokument</name>						\
		<humanname>Dokument Ÿród³owy</humanname>		\
		<typeid>TYPEID_N5PLUMOWA</typeid>				\
		<typeid>TYPEID_N5PLCHOROBA</typeid>				\
		<typeid>TYPEID_N5PLNIEOB</typeid>				\
		<typeid>TYPEID_N5PLPOZOSTALE</typeid>			\
		<optional/>										\
	</wildref>											\
	<embedded>											\
		<name>nLPDokZrodl</name>						\
		<sqltype>SQLlong</sqltype>						\
		<humanname>Pozycja dok. Ÿród³</humanname>		\
	</embedded>

#define XDF_PLACE_SKLADNIK_PARAM_0						\
	<embedded>											\
		<name>curParam1</name>							\
		<sqltype>SQLqty</sqltype>						\
		<humanname>Parametr 1</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>curParam2</name>							\
		<sqltype>SQLqty</sqltype>						\
		<humanname>Parametr 2</humanname>				\
	</embedded>											\
	<ref>												\
		<name>pTerminNal</name>							\
		<humanname>Termin naliczenia</humanname>		\
		<typeid>TYPEID_N5PLTERMINNAL</typeid>			\
	</ref>												\
	<embedded>											\
		<name>cConfParam1</name>						\
		<sqltype>SQLc1</sqltype>						\
		<humanname>Potwierdzaj parametr 1</humanname>	\
		<default>0</default>							\
	</embedded>											\
	<embedded>											\
		<name>cConfParam2</name>						\
		<sqltype>SQLc1</sqltype>						\
		<humanname>Potwierdzaj parametr 2</humanname>	\
		<default>0</default>							\
	</embedded>

#define XDF_PLACE_SKLADNIK_PARAM						\
	<ref>												\
		<name>pSchemat</name>							\
		<humanname>Schemat naliczenia</humanname>		\
		<typeid>TYPEID_N5PLSCHEMATNAL</typeid>			\
	</ref>												\
	XDF_PLACE_SKLADNIK_PARAM_0

#ifdef ENABLE_DB13

#define XDF_EXTRAS										\
	<embedded>											\
		<name>strExtra1</name>							\	
		<sqltype>SQLvc32</sqltype>						\
		<humanname>strExtra1</humanname>				\
		</embedded>											\
		<embedded>											\
		<name>strExtra2</name>							\
		<sqltype>SQLvc128</sqltype>						\
		<humanname>strExtra2</humanname>				\
		</embedded>											\
		<embedded>											\
		<name>dExtra3</name>							\
		<sqltype>SQLdate</sqltype>						\
		<humanname>dExtra3</humanname>					\
		<default>null</default>							\
		</embedded>											\
		<embedded>											\
		<name>curExtra4</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra4</humanname>				\
		</embedded>											\
		<embedded>											\
		<name>curExtra5</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra5</humanname>				\
		</embedded>											\
		<ref>												\
		<name>pKwalifikatorEx</name>					\
		<humanname>Kwalifikator</humanname>				\
		<typeid>TYPEID_N5KWALIFIKATOR</typeid>			\
		<optional />										\
		</ref>											\
		<embedded>											\
		<name>strExtra6</name>							\
		<sqltype>SQLvc128</sqltype>						\
		<humanname>strExtra2</humanname>					\
		</embedded>										\
		<embedded>											\
		<name>strExtra7</name>							\
		<sqltype>SQLvc128</sqltype>						\
		<humanname>strExtra7</humanname>					\
		</embedded>										\
		<embedded>											\
		<name>curExtra8</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra8</humanname>					\
		</embedded>										\
		<embedded>											\
		<name>curExtra9</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra9</humanname>					\
		</embedded>										\
		<embedded>											\
		<name>dExtra10</name>								\
		<sqltype>SQLdate</sqltype>						\
		<humanname>dExtra10</humanname>					\
		<default>null</default>							\
		</embedded>

#else

#define XDF_EXTRAS										\
	<embedded>											\
		<name>strExtra1</name>							\	
		<sqltype>SQLvc32</sqltype>						\
		<humanname>strExtra1</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>strExtra2</name>							\	
		<sqltype>SQLvc128</sqltype>						\
		<humanname>strExtra2</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>dExtra3</name>							\
		<sqltype>SQLdate</sqltype>						\
		<humanname>dExtra3</humanname>					\
		<default>null</default>							\
	</embedded>											\
	<embedded>											\
		<name>curExtra4</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra4</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>curExtra5</name>							\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra5</humanname>				\
	</embedded>											\
	<ref>												\
		<name>pKwalifikatorEx</name>					\
		<humanname>Kwalifikator</humanname>				\
		<typeid>TYPEID_N5KWALIFIKATOR</typeid>			\
		<optional/>										\
	</ref>																					

#endif




#define XDF_SRTRW_METODY_AMORT							\
	<enum>												\
		<name>eMetAmPod</name>							\
		<humanname>Metoda amortyzacji podatkowej</humanname>		\
		<default>N5SRTRW_METAM_LINIOWA</default>		\
		<item>jednorazowa</item>						\
		<item>liniowa</item>							\
		<item>degresywna</item>							\
		<item>nie podlega</item>						\
		<item>rêczna</item>								\
	</enum>												\
	<enum>												\
		<name>eMetAmBil</name>							\
		<humanname>Metoda amortyzacji bilansowej</humanname>		\
		<default>N5SRTRW_METAM_LINIOWA</default>		\
		<item>jednorazowa</item>						\
		<item>liniowa</item>							\
		<item>degresywna</item>							\
		<item>nie podlega</item>						\
	</enum>


#macro VDF_PREJESTRDOK_DISABLE_CHANGE(_obj_type_)				\
function _obj_type_##_pRejestrDok_change(oldval)				\	
	if trans_.var(GVAR_OPERATION_MODE) = clng(OPERATION_MODE_IMPORT) then	\
		_obj_type_##_pRejestrDok_change = true				\
		exit function										\
	end if														\
	trans_.message 7000, 0, "Zmiana rejestru jest niedozwolona: " + this_.text	\
	_obj_type_##_pRejestrDok_change = false						\
end function										





#macro XDF_RATY_PLATNOSCI(_objtype_)			\
	<embedded>									\
		<name>_objtype_##curRata</name>			\
		<sqltype>SQLcurrency</sqltype>			\
		<humanname>Kwota platnosci</humanname>	\
	</embedded>									\
	<list>										\
		<name>_objtype_##listRata</name>		\
		<humanname>Lista rat</humanname>		\
		<typeid>TYPEID_N5POZRATA</typeid>		\
	</list>



#macro XDF_REF_OPT(_fld_,_typeid_,_hname_)				\
	<ref>												\
		<name>_fld_</name>								\
		<humanname>_hname_</humanname>					\
		<typeid>_typeid_</typeid>						\
		<optional/>										\
	</ref>												


#macro XDF_ENUM(_fld_,_hname_,_default_,_items_)		\
	<enum>												\
		<name>_fld_</name>								\
		<humanname>_hname_</humanname>					\
		<default>_default_</default>					\
		_items_											\
	</enum>





#macro XDF_LIST(_fld_,_hname_,_typeid_)					\
	<list>												\
		<name>_fld_</name>								\
		<humanname>_hname_</humanname>					\
		<typeid>_typeid_</typeid>						\
	</list>





#macro XDF_QTY(_fld_,_hname_,_default_)					\
	<embedded>											\	
		<name>_fld_</name>								\
		<sqltype>SQLqty</sqltype>						\
		<humanname>_hname_</humanname>					\
		<default>_default_</default>					\
	</embedded>
	
#ifdef ENABLE_DB13

	#macro XDF_CHANGE_TIME(_objtype_)			\
	<embedded>									\
		<name>_objtype_##dCreated</name>		\
		<sqltype>SQLdate</sqltype>				\
		<humanname>Data utworzenia</humanname>	\
	</embedded>									\
	<embedded>									\
		<name>_objtype_##tCreated</name>		\
		<sqltype>SQLtime</sqltype>				\
		<humanname>Czas utworzenia</humanname>	\
	</embedded>									\
	<embedded>									\
		<name>_objtype_##dLastSaved</name>		\
		<sqltype>SQLdate</sqltype>				\
		<humanname>Data ostatniej zmiany</humanname>	\
	</embedded>									\
	<embedded>									\
		<name>_objtype_##tLastSaved</name>		\
		<sqltype>SQLtime</sqltype>				\
		<humanname>Czas ostatniej zmiany</humanname>	\
	</embedded>

#endif

#comment funkcja sprawdza czy w przypadku update dokumentu zmieniane by³y pola u¿ytkownika
#define	VDF_EXTRAS_CHANGED								\
function extrasChanged(): extrasChanged = false			\
	if this_.strExtra1 <> this_.old_strExtra1 then		\
		extrasChanged = true							\
		exit function									\
	end if												\
	if this_.strExtra2 <> this_.old_strExtra2 then		\
		extrasChanged = true							\
		exit function									\
	end if												\
	if this_.dExtra3 <> this_.old_dExtra3 then			\
		extrasChanged = true							\
		exit function									\	
	end if												\
	if this_.curExtra4 <> this_.old_curExtra4 then		\
		extrasChanged = true							\
		exit function									\
	end if												\
	if this_.curExtra5 <> this_.old_curExtra5 then		\
		extrasChanged = true							\
		exit function									\
	end if												\
	if not this_.pKwalifikatorEx is this_.old_pKwalifikatorEx then	\
		extrasChanged = true							\
		exit function									\
	end if												\	
end function

