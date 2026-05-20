#ifndef _H_1231_H_
#define _H_1231_H_

#comment -------------------------------------------------------------
#comment n5rule
#comment -------------------------------------------------------------
#define RULE_TYPE_G1R1		"G1R1"
#define RULE_TYPE_G2R1		"G2R1"
#define RULE_TYPE_G2R2		"G2R2"
#define RULE_TYPE_G2R3		"G2R3"
#define RULE_TYPE_G2R4		"G2R4"
#define RULE_TYPE_G2R5		"G2R5"
#define RULE_TYPE_G2R6		"G2R6"
#define RULE_TYPE_G2R7		"G2R7"
#define RULE_TYPE_G2R8		"G2R8"
#define RULE_TYPE_G2R9		"G2R9"
#define RULE_TYPE_G2R10		"G2R10"
#define RULE_TYPE_G3R1		"G3R1"
#define RULE_TYPE_G3R2		"G3R2"
#define RULE_TYPE_G3R3		"G3R3"
#define RULE_TYPE_G4R1		"G4R1"
#define RULE_TYPE_G4R2		"G4R2"
#define RULE_TYPE_G5R1		"G5R1"

#comment -------------------------------------------------------------
#comment n5konto i n5dekret
#comment -------------------------------------------------------------
#define N5KONTO_ANALITYCZNE		1
#define N5KONTO_SYNTETYCZNE		2

#define N5KONTO_AKTYWNE			1
#define N5KONTO_NIEAKTYWNE		2

#define N5KONTO_BILANSOWE		1
#define N5KONTO_POZABILANSOWE	2

#define N5_DEKRET_TYP_BO				1
#define N5_DEKRET_TYP_NORMALNY			2
#define N5_DEKRET_TYP_BZ				3
#define N5_DEKRET_TYP_BZ_OSTAT			4

#define N5_DEKRET_STATUS_BUFOR	1
#define N5_DEKRET_STATUS_ZAKS	2

#define N5_DEKRET_AUTO          "1"
#define N5_DEKRET_RECZ          "0"

#comment -------------------------------------------------------------
#comment n5klient
#comment -------------------------------------------------------------

#define N5KLIENT_AKTYWNY		1
#define N5KLIENT_NIEAKTYWNY		2

#define N5KLIENT_MALY			1
#define N5KLIENT_SREDNI			2
#define N5KLIENT_DUZY			3

#define N5KLIENT_DT_DOWOD		1
#define N5KLIENT_DT_PASZPORT	2
#define N5KLIENT_DT_INNY		3

#define N5KLIENT_PLEC_KOBIETA	1
#define N5KLIENT_PLEC_MEZCZYZNA	2

#define N5KLIENT_OSOBAPRYWATNA		1
#define N5KLIENT_FIRMA				2

#define N5KLIENT_FINANSE_NIEZN	1
#define N5KLIENT_FINANSE_DOBRA	2
#define N5KLIENT_FINANSE_PRZEC	3
#define N5KLIENT_FINANSE_ZLA	4

#define N5KLIENT_TYP_KLIE		1
#define N5KLIENT_TYP_DOST		2

#define N5KLIENT_DOST_KOSZT		1
#define N5KLIENT_DOST_MATER		2

#define N5FAKTURA_ELEKT_NIE		2
#define N5FAKTURA_ELEKT_TAK		1

#comment -------------------------------------------------------------
#comment n5zadanie
#comment -------------------------------------------------------------

#define N5ZADANIE_UTWORZONE		0
#define N5ZADANIE_NIEGOTOWE		4
#define N5ZADANIE_ZLECONE		10
#define N5ZADANIE_ODEBRANE		20
#define N5ZADANIE_WYKONYWANE	30
#define N5ZADANIE_WSTRZYMANE	31
#define N5ZADANIE_ZAKONCZONE	40
#define N5ZADANIE_ZAMKNIETE		50

#define N5ZADANIE_UTWORZONE_PIC		80204
#define N5ZADANIE_ZLECONE_PIC		80205
#define N5ZADANIE_ODEBRANE_PIC		80206
#define N5ZADANIE_WYKONYWANE_PIC	80207
#define N5ZADANIE_WSTRZYMANE_PIC	80208
#define N5ZADANIE_ZAKONCZONE_PIC	80209
#define N5ZADANIE_ZAMKNIETE_PIC		80210
#define N5ZADANIE_PUSTY_PIC			80211
#define N5ZADANIE_ZANIECHANE_PIC	80212

#define N5ZADANIE_P_NISKI		1
#define N5ZADANIE_P_NORMALNY	2
#define N5ZADANIE_P_WYSOKI		3
#define N5ZADANIE_P_KRYTYCZNY	4

#define N5ZADANIE_P_NISKI_PIC		80200
#define N5ZADANIE_P_NORMALNY_PIC	80201
#define N5ZADANIE_P_WYSOKI_PIC		80202
#define N5ZADANIE_P_KRYTYCZNY_PIC	80203

#define N5ZADANIE_ENDTYP_NAJSZYBCIEJ			1
#define N5ZADANIE_ENDTYP_NIE_WCZESNIEJ_NIZ		2
#define N5ZADANIE_ENDTYP_W_MOMENCIE				3
#define N5ZADANIE_ENDTYP_NIE_POZNIEJ_NIZ		4
#define N5ZADANIE_ENDTYP_OBOJETNY				5

#comment -------------------------------------------------------------
#comment n5typdzialania
#comment must match preload (i.e. 50300)
#comment -------------------------------------------------------------
#define N5TYPDZIALANIA_IID_KONTAKT			1
#define N5TYPDZIALANIA_IID_SPRZEDAZ			2
#define N5TYPDZIALANIA_IID_NOTATKA			3
#define N5TYPDZIALANIA_IID_WIADOMOSC		4
#define N5TYPDZIALANIA_IID_ZAMOWIENIE		12
#define N5TYPDZIALANIA_IID_PLATNOSC			13
#define N5TYPDZIALANIA_IID_ZAKUP			14
#define N5TYPDZIALANIA_IID_OPMAG			15
#define N5TYPDZIALANIA_IID_POLECENIE_SLUZB	16
#define N5TYPDZIALANIA_IID_ZLECENIASERWIS	20
#define N5TYPDZIALANIA_IID_KONSERWACJA		21

#comment -------------------------------------------------------------
#comment n5typdokumentu
#comment -------------------------------------------------------------

#define N5TYPDOKUMENTU_PRZYCHADZACY			1
#define N5TYPDOKUMENTU_WYCHODZACY			2
#define N5TYPDOKUMENTU_WEWNETRZNY			3

#comment -------------------------------------------------------------
#comment n5dokument
#comment -------------------------------------------------------------

#define N5DOKUMENT_FORMA_ELEKTRON			1
#define N5DOKUMENT_FORMA_PAPIER				2
#define N5DOKUMENT_FORMA_PAP_I_ELEKTR		3
#define N5DOKUMENT_FORMA_ELEKTR_I_PAP		4

#comment -------------------------------------------------------------
#comment jednostka
#comment -------------------------------------------------------------

#define N5JEDNOSTKA_MIARY		1
#define N5JEDNOSTKA_WALUTA		2

#comment -------------------------------------------------------------
#comment sprzedaz
#comment -------------------------------------------------------------
#define N5SPRZEDAZ_NETTO		1
#define N5SPRZEDAZ_BRUTTO		2

#define N5SPRZEDAZ_VAT_POZYCJE	1
#define N5SPRZEDAZ_VAT_STAWKI	2

#define N5SPRZEDAZ_JPKVAT_CALY_UJMIJ    1
#define N5SPRZEDAZ_JPKVAT_CALY_POMIN    2
#define N5SPRZEDAZ_JPKVAT_0_DOMYSLNIE    1
#define N5SPRZEDAZ_JPKVAT_0_KOL14	     2
#define N5SPRZEDAZ_JPKVAT_NP_DOMYSLNIE    1
#define N5SPRZEDAZ_JPKVAT_NP_KOL12	      2

#comment -------------------------------------------------------------
#comment zakup
#comment -------------------------------------------------------------
#define N5ZAKUP_TYPOPOD_OPODATK		1
#define N5ZAKUP_TYPOPOD_MIESZANE	2

#define N5ZAKUP_TYPZAKUP_SRODEKTRW		1
#define N5ZAKUP_TYPZAKUP_TOWARHANDL		2
#define N5ZAKUP_TYPZAKUP_PALIWO			3
#define N5ZAKUP_TYPZAKUP_SAMOCHOD_NO	4
#define N5ZAKUP_TYPZAKUP_SRODKI_TRW_50	5
#define N5ZAKUP_TYPZAKUP_ODLICZANE_75	6

#define N5ZAKUP_JPKVAT_KOL_46		1
#define N5ZAKUP_JPKVAT_KOL_POMIN    2
#define N5ZAKUP_JPKVAT_KOL_47		3
#define N5ZAKUP_JPKVAT_KOL_48		4
#define N5ZAKUP_JPKVAT_KOL_49		5
#define N5ZAKUP_JPKVAT_KOL_50		6
#define N5ZAKUP_VAT_OO_DOMYSLNIE	1
#define N5ZAKUP_VAT_OO_KOL_K32		2

#comment -------------------------------------------------------------
#comment n5pracownik
#comment -------------------------------------------------------------

#define N5PRACOWNIK_AKTYWNY_AKTYWNY		1
#define N5PRACOWNIK_AKTYWNY_NIEAKTYWNY	2
#define N5PRACOWNIK_AKTYWNY_KANDYDAT	3
#define N5PRACOWNIK_AKTYWNY_PRAKTYKANT	4

#define N5PRACOWNIK_PLEC_KOBIETA	1
#define N5PRACOWNIK_PLEC_MEZCZYZNA	2

#define N5PRACOWNIK_DT_DOWOD	1
#define N5PRACOWNIK_DT_PASZPORT	2
#define N5PRACOWNIK_DT_INNY		3

#comment -------------------------------------------------------------
#comment n5uzytkownik
#comment -------------------------------------------------------------

#define N5UZYTKOWNIK_AKTYWNY			1
#define N5UZYTKOWNIK_NIEAKTYWNY			2
#define N5UZYTKOWNIK_SZABLON			3

#comment -------------------------------------------------------------
#comment n5klientpracownik
#comment -------------------------------------------------------------

#define N5KLIENT_PRACOWNIK_AKTYWNY		1
#define N5KLIENT_PRACOWNIK_NIEAKTYWNY	2

#define N5KLIENT_PRACOWNIK_PLEC_KOBIETA	1
#define N5KLIENT_PRACOWNIK_PLEC_MEZCZYZNA	2

#define N5KLIENT_PRACOWNIK_KAWALER		1
#define N5KLIENT_PRACOWNIK_ZONATY		2
#define N5KLIENT_PRACOWNIK_PANNA		3
#define N5KLIENT_PRACOWNIK_MEZATKA		4
#define N5KLIENT_PRACOWNIK_NIEZNANY		5

#comment -------------------------------------------------------------
#comment n5produkt
#comment -------------------------------------------------------------
#define N5PRODUKT_AKTYWNY				1
#define N5PRODUKT_NIEAKTYWNY			2

#define N5PRODUKT_TOWAR					1
#define N5PRODUKT_USLUGA				2

#define N5PRODUKT_GTU_01				1
#define N5PRODUKT_GTU_02				2
#define N5PRODUKT_GTU_03				3
#define N5PRODUKT_GTU_04				4
#define N5PRODUKT_GTU_05				5
#define N5PRODUKT_GTU_06				6
#define N5PRODUKT_GTU_07				7
#define N5PRODUKT_GTU_08				8
#define N5PRODUKT_GTU_09				9
#define N5PRODUKT_GTU_10				10
#define N5PRODUKT_GTU_11				11
#define N5PRODUKT_GTU_12				12
#define N5PRODUKT_GTU_13				13
#define N5PRODUKT_GTU_NIEOKRESLONY		14

#comment -------------------------------------------------------------
#comment n5eventlog
#comment -------------------------------------------------------------
#define N5EVENTLOG_LOGON					1
#define N5EVENTLOG_LOGOUT					2
#define N5EVENTLOG_CHANGE_CURR_RATE			3
#define N5EVENTLOG_CHANGE_PRICE				4
#define N5EVENTLOG_GM_CHECK_OFF				5
#define N5EVENTLOG_SET_BLOK_SPRZED			6
#define N5EVENTLOG_REMOVE_BLOK_SPRZED		7
#define N5EVENTLOG_WYST_DOK_BLOK_KLI		8
#define N5EVENTLOG_ARCHIWIZACJA				9
#define N5EVENTLOG_MODYFIKACJA_DOK			10
#define N5EVENTLOG_NADANIE_UPRAWNIENIA		11
#define N5EVENTLOG_ODEBRANIE_UPRAWNIENIA	12
#define N5EVENTLOG_USUNIECIE_DOKUMENTU		13
#define N5EVENTLOG_POBRANIE_KURSOW_WALUT	14
#define N5EVENTLOG_VERIFY_TAX_ID			14
#define N5EVENTLOG_CHECK_SPLIT_PAYMENT		14


#comment -------------------------------------------------------------
#comment n5kurswalut
#comment -------------------------------------------------------------
#define N5KURSWALUT_KUPNA		1
#define N5KURSWALUT_SPRZEDAZY	2

#comment -------------------------------------------------------------
#comment n5schematdekr
#comment -------------------------------------------------------------
#define N5SCHEMATDEKR_AKTYWNY		1
#define N5SCHEMATDEKR_NIEAKTYWNY	2


#comment -------------------------------------------------------------
#comment n5transakcja
#comment -------------------------------------------------------------
#define N5TRANSAKCJA_ZOBOWIAZANIE		1
#define N5TRANSAKCJA_NALEZNOSC			2

#define N5TRANSAKCJA_OTWARTA			1
#define N5TRANSAKCJA_ZAMKNIETA			2

#define N5TRANSAKCJA_ODSETKI_USTAWOWE		1
#define N5TRANSAKCJA_ODSETKI_UMOWNE			2
#define N5TRANSAKCJA_ODSETKI_NIENALICZAJ	3

#comment -------------------------------------------------------------
#comment n5platnosc
#comment -------------------------------------------------------------
#define N5PLATNOSC_PLANOWANA			1
#define N5PLATNOSC_ZREALIZOWANA			2

#comment -------------------------------------------------------------
#comment n5opsrtrw
#comment -------------------------------------------------------------
#define N5OPSRTRW_ZAKUP					1
#define N5OPSRTRW_PRZYJECIE_OT			2
#define N5OPSRTRW_AMORTYZACJA			3
#define N5OPSRTRW_PRZESZACOWANIE_PK		4
#define N5OPSRTRW_ZMIANA_WARTOSCI_WK	5
#define N5OPSRTRW_SPRZEDAZ				6
#define N5OPSRTRW_LIKWIDACJA_LT			7
#define N5OPSRTRW_PRZYJECIE_PT			8
#define N5OPSRTRW_PRZEKAZANIE_PR		9
#define N5OPSRTRW_ZMIANA_OSOBY			10
#define N5OPSRTRW_ZMIANA_MIEJSCA		11
#define N5OPSRTRW_ZMIANA_STAWKI			12
#define N5OPSRTRW_KOREKTA_AMORT			13

#define N5SRTRW_METAM_JEDNORAZOWA		1
#define N5SRTRW_METAM_LINIOWA			2
#define N5SRTRW_METAM_DEGRESYWNA		3
#define N5SRTRW_METAM_NIEPODLEGA		4
#define N5SRTRW_METAM_RECZNA			5

#define N5SRTRW_STATUS_NOWY				1
#define N5SRTRW_STATUS_UZYTKOWANY		2
#define N5SRTRW_STATUS_NIEUZYTKOWANY	3
#define N5SRTRW_STATUS_UMORZONY			4
#define N5SRTRW_STATUS_ZLIKWIDOWANY		5
#define N5SRTRW_STATUS_SPRZEDANY		6

#define N5SRTRW_RODZAJ_SRODEK			1
#define N5SRTRW_RODZAJ_WYPOSAZENIE		2
#define N5SRTRW_RODZAJ_WART_NIEMAT		3
#define N5SRTRW_RODZAJ_INWESTYCJA		4


#comment -------------------------------------------------------------
#comment n5polrab
#comment -------------------------------------------------------------
#define N5POLRAB_TYP_CENA_NETTO			1
#define N5POLRAB_TYP_CENA_BRUTTO		2
#define N5POLRAB_TYP_CENA_RABAT_WYL		3
#define N5POLRAB_TYP_CENA_RABAT_DOD		4

#comment -------------------------------------------------------------
#comment n5pllistaplac
#comment -------------------------------------------------------------
#define N5PLWZORLP_AKTYWNY			1
#define N5PLWZORLP_NIEAKTYWNY		2

#comment -------------------------------------------------------------
#comment n5plsubkonto
#comment -------------------------------------------------------------
#define N5PL_SUBKONTO_AKTYWNE			1
#define N5PL_SUBKONTO_NIEAKTYWNE		2

#define N5PL_SUBKONTO_ZAKRES_PRACOWNIK		1
#define N5PL_SUBKONTO_ZAKRES_UMOWA			2
#define N5PL_SUBKONTO_ZAKRES_NALICZENIE		3

#comment -------------------------------------------------------------
#comment n5plschematnal
#comment -------------------------------------------------------------
#define N5PL_SCHEMATNAL_AKTYWNY			1
#define N5PL_SCHEMATNAL_NIEAKTYWNY		2

#comment -------------------------------------------------------------
#comment n5plkalcp
#comment -------------------------------------------------------------
#define N5PLKALCP_AKTYWNY			1
#define N5PLKALCP_NIEAKTYWNY		2

#comment -------------------------------------------------------------
#comment n5plpozkalcp
#comment -------------------------------------------------------------

#define N5PLPOZKALCP_OKRES_ROBOCZY		1
#define N5PLPOZKALCP_OKRES_WOLNY		2
#define N5PLPOZKALCP_OKRES_WOLNY_UST	3

#comment -------------------------------------------------------------
#define N5WYKONAWCA_AKTYWNY			1
#define N5WYKONAWCA_NIEAKTYWNY		2

#comment -------------------------------------------------------------
#comment n5plnieob
#comment -------------------------------------------------------------
#define N5PL_NIEOB_NIEUSP		1
#define N5PL_NIEOB_URL_WYP		2
#define N5PL_NIEOB_URL_ZADANIE	3
#define N5PL_NIEOB_URL_OKOL		4
#define N5PL_NIEOB_URL_WYCHOW	5	
#define N5PL_NIEOB_URL_SZKOL	6
#define N5PL_NIEOB_URL_BEZPL	7
#define N5PL_NIEOB_URL_PROFIL	8
#define N5PL_NIEOB_URL_OPIEK	9
#define N5PL_NIEOB_URL_BEZP_FIR	10
#define N5PL_NIEOB_USPRAW_PL	11

#comment -------------------------------------------------------------
#comment n5plumowa
#comment -------------------------------------------------------------
#define N5PL_UMOWA_ZLECENIA		1
#define N5PL_UMOWA_O_PRACE		2
#define N5PL_UMOWA_O_DZIELO		3

#comment -------------------------------------------------------------
#comment n5prop.prop_eStatus
#comment -------------------------------------------------------------
#define N5PROPS_SYMULACJA		1
#define N5PROPS_ZLECONE			2
#define N5PROPS_DOWYKONANIA		3
#define N5PROPS_WREALIZACJI		4
#define N5PROPS_ZREALIZOWANE	5
#define N5PROPS_INNY			6

#comment -------------------------------------------------------------
#comment n5prop.prop_eTyp
#comment -------------------------------------------------------------
#define N5PROPT_SUROWIEC		1
#define N5PROPT_WYROB			2
#define N5PROPT_PRACA			3
#define N5PROPT_ZASOB			4

#comment -------------------------------------------------------------
#comment n5zlecprod.zlp_eStatus
#comment -------------------------------------------------------------
#define N5ZLECPRODS_SYMULACJA		1
#define N5ZLECPRODS_ZAAKCEPTOWANE	2
#define N5ZLECPRODS_ZREALIZOWANE	3
#define N5ZLECPRODS_WSTRZYMANE		4
#define N5ZLECPRODS_ANULOWANE		5
#define N5ZLECPRODS_INNY			6

#comment -------------------------------------------------------------
#comment n5zlecprod.zlp_eStatus		HORYZONT
#comment -------------------------------------------------------------
#define N5ZLECPRODS_HORYZONT_NOWE			1
#define N5ZLECPRODS_HORYZONT_W_PRODUKCJI	2
#define N5ZLECPRODS_HORYZONT_ZAKONCZONE		3
#define N5ZLECPRODS_HORYZONT_ANULOWANE		4
#define N5ZLECPRODS_HORYZONT_ZMODYFIKOWANE	5
#define N5ZLECPRODS_HORYZONT_INNY			6

#comment -------------------------------------------------------------
#comment n5pojazd.poj_eTyp
#comment -------------------------------------------------------------
#define N5POJAZD_MOTOCYKL			1
#define N5POJAZD_SAM_OSOBOWY		2
#define N5POJAZD_SAM_CIEZAROWY		3
#define N5POJAZD_AUTOBUS			4
#define N5POJAZD_SPECJALNY			5
#define N5POJAZD_PRZYCZEPA			6
#define N5POJAZD_NACZEPA			7
#define N5POJAZD_CIAGNIK_ROL		8
#define N5POJAZD_INNE				9

#comment -------------------------------------------------------------
#comment n5polecenie_wyjazdu.pws_eTyp
#comment -------------------------------------------------------------
#define N5POLECENIE_WYJ_WEZWANIE		1
#define N5POLECENIE_WYJ_ZAPROSZENIE		2
#define N5POLECENIE_WYJ_INNE			3


#comment -------------------------------------------------------------
#comment rodzaj eksportu/importu
#comment -------------------------------------------------------------

#define EXPXML			200
#define IMPXML			201
#define IMPXLS			202
#define IMPFRM			203
#define IMPEXT			204

#comment -------------------------------------------------------------
#comment typ rejestru dokumentów
#comment -------------------------------------------------------------
#define N5REJESTRDOK_AKTYWNY			1
#define N5REJESTRDOK_NIEAKTYWNY			2

#comment REV:KB:DONE zaktualizowaæ zgodnie z <enum> n5rejestrdok.eTyp
#comment REV:KB:DONE przy imporcie z NAVO Firma zmieni siê mapowanie rejestrów

#define N5REJESTRDOK_FAKT_SP			1
#define	N5REJESTRDOK_KOR_FAKT_SP		2
#define N5REJESTRDOK_RACH				3
#define N5REJESTRDOK_KOR_RACH			4
#define N5REJESTRDOK_PARAGON			5
#define N5REJESTRDOK_KOR_PARAGON		6
#define N5REJESTRDOK_FAKT_ZAK			7
#define N5REJESTRDOK_KOR_FAKT_ZAK		8
#define N5REJESTRDOK_KASOWY				9
#define N5REJESTRDOK_BANKOWY			10
#define N5REJESTRDOK_REJ_ZALICZEK		11
#define N5REJESTRDOK__KWZ				12
#define N5REJESTRDOK_NOTA_ODSETKOWA		13

#comment uzywane dla protokolow serwisowych
#define N5REJESTRDOK_KARTA_POJAZDU		14

#define N5REJESTRDOK_SRODKI_TRWALE		15
#define N5REJESTRDOK_WYNAGR				16
#define N5REJESTRDOK_DZIENNIK_NORM		17
#define N5REJESTRDOK__PZ				18
#define N5REJESTRDOK__WZ				19
#define N5REJESTRDOK__ZD				20
#define N5REJESTRDOK__ZZ				21
#define N5REJESTRDOK__PW				22
#define N5REJESTRDOK__PP				23
#define N5REJESTRDOK__RP				24
#define N5REJESTRDOK__RW				25
#define N5REJESTRDOK__MM				26
#define N5REJESTRDOK__MR				27
#define N5REJESTRDOK__MP				28
#define N5REJESTRDOK__IP				29
#define N5REJESTRDOK__IR				30
#define N5REJESTRDOK__REALPROD			31
#define N5REJESTRDOK__ZLECPROD			32
#define N5REJESTRDOK__ZAM_OBCE			33
#define N5REJESTRDOK__ZAM_WLASNE		34
#define N5REJESTRDOK_FAKT_EXP			35
#define N5REJESTRDOK_KOR_FAKT_EXP		36
#define N5REJESTRDOK_FAKT_IMP			37
#define N5REJESTRDOK_KOR_FAKT_IMP		38
#define N5REJESTRDOK_PKPIR				39
#define N5REJESTRDOK_ZAPAKOWANIA		40
#define N5REJESTRDOK_ROZPAKOWANIA		41
#define N5REJESTRDOK_DZIENNIK_BO		42
#define N5REJESTRDOK_DZIENNIK_BZ		43
#define N5REJESTRDOK_DZIENNIK_BZ_OSTAT	44
#define N5REJESTRDOK_REZERWACJE			45
#define N5REJESTRDOK_ZAK_REZERWACJI		46
#define N5REJESTRDOK_KOMPENSATY			47
#define N5REJESTRDOK_WNT				48
#define N5REJESTRDOK_WDT				49
#define N5REJESTRDOK_KOREKTA_WNT		50
#define N5REJESTRDOK_KOREKTA_WDT		51
#define N5REJESTRDOK_FAKT_ZAK_RR		52
#define N5REJESTRDOK_KOR_FAKT_ZAK_RR	53
#define N5REJESTRDOK_FAKTURA_ZALICZKOWA	54
#define N5REJESTRDOK_ZADANIA			55
#define N5REJESTRDOK_ZAP_OFERTOWE_OBCE		56
#define N5REJESTRDOK_OFERTY_WLASNE			57
#define N5REJESTRDOK_ZAP_OFERTOWE_WLASNE	58
#define N5REJESTRDOK_OFERTY_OBCE			59
#define N5REJESTRDOK_FAKTURA_ZALICZKOWA_KOR	60
#define N5REJESTRDOK_DOSTAWA			61
#define N5REJESTRDOK_KOR_DOSTAWA		62
#define N5REJESTRDOK_DOSTAWA_WEGLA		63

#comment ENABLE_DB14
#define N5REJESTRDOK_BANKOWY_VAT			64

#comment ENABLE_DB14_A
#define N5REJESTRDOK_IMPORT_USLUG			65
#define N5REJESTRDOK_KOR_IMPORT_USLUG		66

#comment -------------------------------------------------------------
#comment TYPEID_N5POZDOKPROD / pdp_eRegulaNaliczania
#comment -------------------------------------------------------------
#define PDP_RN_CENAX1		1
#define PDP_RN_LICZBA		2
#define PDP_RN_SUMA			3


#define STAWKA_VAT_0				1
#define STAWKA_VAT_ZWOLNIONY		2
#define STAWKA_VAT_NIE_PODLEGA		3
#define STAWKA_VAT_2				4
#define STAWKA_VAT_3				5
#define STAWKA_VAT_4				6
#define STAWKA_VAT_7				7
#define STAWKA_VAT_12				8
#define STAWKA_VAT_17				9
#define STAWKA_VAT_22				10
#define STAWKA_VAT_5				11
#define STAWKA_VAT_6                12
#define STAWKA_VAT_8				13
#define STAWKA_VAT_23               14
#define STAWKA_VAT_23_OO            15

#define STAWKA_VAT_RR1				STAWKA_VAT_5
#define STAWKA_VAT_RR2              STAWKA_VAT_6

#define T_REQUIRED				50300
#define T_PODZIAL_TERYTORIALNY	50301
#define T_URZAD_SKRABOWY		50302
#define T_EKD					50507
#define T_NAVO					50308
#define T_SECURITYOBJ			50309
#define T_SECURITYOBJ_OPSPEC	50310
#define T_N5DPC					50311
#define T_SECURITYOBJ_DB4		50312
#define T_KPIR_SCHEMATY			50313
#define T_SECURITYOBJ_DB5		50314
#define T_SECURITYOBJ_DB6		50315
#define T_UZBR_PLAC_DB6			50316
#define T_REJDOK				50317
#define T_N5DPC_DB6PLUS			50318
#define T_SECURITYOBJ_DB7		50319
#define T_N5DPC_DOD_PUB			50324
#define T_IOW_UPR_ZMIANY_DATY_SP	50325
#define T_UPR_MODULOW			50326

#define T_DEMO					95003

#define QUICK_ACCESS_TITLE		EuroBusiness 5.0

#define AUTONO_NAME	"AUTONUMERACJA"

#define N5GMOP_P_CZ_IZ_DS		1
#define N5GMOP_R_CA_IZ_DF		2
#define N5GMOP_R_CA_IZ_DZ		3
#define N5GMOP_P_CA_IA_DS		4
#define N5GMOP_R_CZ_IZ_DX		5
#define N5GMOP_P_CP_IZ_DS		6
#define N5GMOP_K_CA_IA_DI		7
#define N5GMOP_R_CA_IZ_DI		8

#comment DB9 plus
#comment podsumowanie archiwum (BO)
#define N5GMOP_P_CZ_IZ_BO		9

#comment storno zaokraglen wartosci
#define N5GMOP_K_STORNO_WART	10


#define N5OPAK_JEDNOSTKOWE	1
#define N5OPAK_ZBIORCZE		2


#define N5SPOSPLAT_GOTOWKA			1
#define N5SPOSPLAT_KARTA			2
#define N5SPOSPLAT_PRZELEW			3
#define N5SPOSPLAT_PRZEDPLATA		4
#define N5SPOSPLAT_KOMPENSATA		5
#define N5SPOSPLAT_ZA_POBRANIEM		6

#define PRICE_PREC_DEFAULT			2


#define N5KONTO_BUDZET_ODNIESIENIE_OBROTY_WN		1	
#define N5KONTO_BUDZET_ODNIESIENIE_OBROTY_MA		2
#define N5KONTO_BUDZET_ODNIESIENIE_SALDO_WN			3
#define N5KONTO_BUDZET_ODNIESIENIE_SALDO_MA			4
#define N5KONTO_BUDZET_ODNIESIENIE_SALDO_SALD_WN	5
#define N5KONTO_BUDZET_ODNIESIENIE_SALDO_SALD_MA	6


#define N5REJESTRDOK_ZASADA_RAPKAS_CODZIENNIE		1
#define N5REJESTRDOK_ZASADA_RAPKAS_COTYDZIEN		2
#define N5REJESTRDOK_ZASADA_RAPKAS_CO10DNI			3
#define N5REJESTRDOK_ZASADA_RAPKAS_COMIESIAC		4


#define N5CHOICELIST_DYNAMIC_BRAK					1
#define N5CHOICELIST_DYNAMIC_ZACHOWAJ				2



#comment -------------------------------------------------------------
#comment n5bwinfo
#comment -------------------------------------------------------------
#define N5BWINFO_STATUS_ZGLOSZONY		1
#define N5BWINFO_STATUS_REALIZOWANY		2
#define N5BWINFO_STATUS_ZAMKNIETY		3


#comment -------------------------------------------------------------
#comment n5magazyn
#comment -------------------------------------------------------------
#define N5TYPMAG_PODSTAWOWY				1
#define N5TYPMAG_ZWROTY					2
#define N5TYPMAG_TOWARWARWDRODZE		3
#define N5TYPMAG_PRODUKCJAWTOKU			4
#define N5TYPMAG_REZERWACJE				5

#define N5MAGAZYN_AKTYWNY				1
#define N5MAGAZYN_NIEAKTYWNY			2

#comment -------------------------------------------------------------
#comment n5kwalifikator
#comment -------------------------------------------------------------

#define N5KWALIFITATOR_AKTYWNY			1
#define N5KWALIFITATOR_NIEAKTYWNY		2

#comment -------------------------------------------------------------
#comment n5typdzialania
#comment -------------------------------------------------------------

#define N5TYPDZIALANIA_AKTYWNY			1
#define N5TYPDZIALANIA_NIEAKTYWNY		2


#comment -------------------------------------------------------------
#comment n5dpc - publikacje
#comment -------------------------------------------------------------

#define N5DPC_PUBTYPE_FAKTURAVAT				1
#define N5DPC_PUBTYPE_FAKTURAVAT_KOREKTA		2
#define N5DPC_PUBTYPE_RACHUNEK					3
#define N5DPC_PUBTYPE_RACHUNEK_KOREKTA			4
#define N5DPC_PUBTYPE_PARAGON					5
#define N5DPC_PUBTYPE_PARAGON_KOREKTA			6
#define N5DPC_PUBTYPE_KP						7
#define N5DPC_PUBTYPE_KW						8
#define N5DPC_PUBTYPE_POLECPRZELEWU				9
#define N5DPC_PUBTYPE_POLECPRZELEWU_ZUS			10
#define N5DPC_PUBTYPE_POLECPRZELEWU_US			11

#define N5DPC_PUBTYPE_PZ						12
#define N5DPC_PUBTYPE_WZ						13
#define N5DPC_PUBTYPE_PW						14
#define N5DPC_PUBTYPE_RW						15
#define N5DPC_PUBTYPE_FAKTURAVAT_ZAGRANICZNA	16
#define N5DPC_PUBTYPE_FAKTURAVAT_EMAIL			17

#define N5DPC_PUBTYPE_ZAMOWIENIE_OBCE			18
#define N5DPC_PUBTYPE_ZAMOWIENIE_WLASNE			19
#define N5DPC_PUBTYPE_ZAKUP						20

#define N5DPC_PUBTYPE_NOTAODSETKOWA				21
#define N5DPC_PUBTYPE_WEZWANIE_DO_ZAPLATY		22

#define N5DPC_PUBTYPE_DOWOD_KSIEGOWY			23
#define N5DPC_PUBTYPE_KOMPENSATA				24

#define N5DPC_PUBTYPE_PP						25
#define N5DPC_PUBTYPE_RP						26
#define N5DPC_PUBTYPE_ZZ						27
#define N5DPC_PUBTYPE_ZD						28
#define N5DPC_PUBTYPE_MM						29
#define N5DPC_PUBTYPE_IR						30
#define N5DPC_PUBTYPE_IP						31

#define N5DPC_PUBTYPE_REZERWACJA				32
#define N5DPC_PUBTYPE_REZERWACJA_ZAK			33

#define N5DPC_PUBTYPE_REALIZACJA_PRODUKCJI		34


#define N5DPC_PUBTYPE_ZAKUP_KOREKTA				35
#define N5DPC_PUBTYPE_FAKTURA_RR				36
#define N5DPC_PUBTYPE_FAKTURA_RR_KOREKTA		37
#define N5DPC_PUBTYPE_ZAKUP_IMPORT				38
#define N5DPC_PUBTYPE_ZAKUP_IMPORT_KOREKTA		39
#define N5DPC_PUBTYPE_FAKTURA_PROFORMA			40
#define N5DPC_PUBTYPE_FAKTURAVAT_ZAGRANICZNA_KOREKTA	41

#define N5DPC_PUBTYPE_WNT						42
#define N5DPC_PUBTYPE_WNT_KOREKTA				43

#define N5DPC_PUBTYPE_WDT						44	
#define N5DPC_PUBTYPE_WDT_KOREKTA				45

#comment DB5
#define N5DPC_PUBTYPE_FAKTURA_ZALICZKOWA		46
#define N5DPC_PUBTYPE_RAPORT_KASOWY				47
#define N5DPC_PUBTYPE_LIST_PRZEWOZOWY			48


#comment BD6
#define N5DPC_PUBTYPE_OFERTY_WLASNE				49
#define N5DPC_PUBTYPE_OFERTY_OBCE				50
#define N5DPC_PUBTYPE_ZAPYTANIE_O_O				51
#define N5DPC_PUBTYPE_ZAPYTANIE_O_W				52
#define N5DPC_PUBTYPE_ZLEC_PROD					53
#define N5DPC_PUBTYPE_STATUS_REAL_ZAM			54
#define N5DPC_PUBTYPE_MP						55
#define N5DPC_PUBTYPE_MR						56
#define N5DPC_PUBTYPE_ETYKIETY_PRODUKCYJNE		57



#define N5DPC_PUBTYPE_INNY						58
#comment Dodatkowe typy publikacji - granice potrzebne do iteracji w czasie preloadu
#define N5DPC_PUBTYPE_INNY_FIRST					1
#define N5DPC_PUBTYPE_INNY_FVAT_POLECENIE_PRZELEWU	1
#define N5DPC_PUBTYPE_INNY_ZAM_INXOBCY				2
#define N5DPC_PUBTYPE_NALICZENIE_PLAC				3
#define N5DPC_PUBTYPE_INNY_WZ_INXOBCY				4
#define N5DPC_PUBTYPE_INNY_LISTPRZEWOZOWY_PL		5
#define N5DPC_PUBTYPE_INNY_ZADANIE					6
#define N5DPC_PUBTYPE_INNY_OPER_SRODEK_TRW			7
#define N5DPC_PUBTYPE_INNY_KOREKTA_WARTOSCIOWA		8
#define N5DPC_PUBTYPE_INNY_POLECENIE_PRZELEWU_NAL	9
#define N5DPC_PUBTYPE_INNY_WYDRUK_KODOW_KRESKOWYCH	10
#define N5DPC_PUBTYPE_INNY_WYDRUK_KOREKTY_FAK_ZAL	11
#define N5DPC_PUBTYPE_INNY_LAST						11
#define N5DPC_PUBTYPE_INNY_POZYCJE_DO_REALIZAJI     12
#define N5DPC_PUBTYPE_INNY_WYDRUK_UMOWY             13	
#define N5DPC_PUBTYPE_INNY_WYDRUK_INTRASTAT			14
#define N5DPC_PUBTYPE_INNY_PROTOKOL_CZESCIOWY_ABAS  15
#define N5DPC_PUBTYPE_INNY_WYDRUK_FISZEK			16
#define N5DPC_PUBTYPE_INNY_WYDRUK_KARTY_PRODUKTU	17
#define N5DPC_PUBTYPE_INNY_WYDRUK_ANKIETY			18
#define N5DPC_PUBTYPE_INNY_WYDRUK_ANKIETY_PUSTY		19
#define N5DPC_PUBTYPE_INNY_ADRES_NA_KOPERCIE		20
#define N5DPC_PUBTYPE_INNY_ROZLICZENIE_INW          21


#define N5DPC_CHANNEL_WYDRUK						1
#define N5DPC_CHANNEL_EMAIL							2
#define N5DPC_CHANNEL_FAX							3
#define N5DPC_CHANNEL_ONLINE						4

#define N5DPC_FORMAT_NAVO							1
#define N5DPC_FORMAT_WORD							2


#comment -------------------------------------------------------------
#comment n5projekt_abas
#comment -------------------------------------------------------------
#define N5PROJEKT_STATUS_PLANOWANY		1
#define N5PROJEKT_STATUS_W_TRAKCIE		2
#define N5PROJEKT_STATUS_ZAKOÑCZONY		3

#define N5PROJEKT_ZAL_BRAK				1
#define N5PROJEKT_ZAL_PIERW_FAKTURA		2
#define N5PROJEKT_ZAL_OSTAT_FAKTURA		3
#define N5PROJEKT_ZAL_FAKT_CZESCIOWE	4

#define N5PROJEKT_KAUCJA_KWOTOWA		1
#define N5PROJEKT_KAUCJA_PROCENTOWA		2


#comment -------------------------------------------------------------
#comment n5ankieta_toral
#comment -------------------------------------------------------------
#define N5POWIERZCHNIA_GOSP_0_50		1
#define N5POWIERZCHNIA_GOSP_50_100		2
#define N5POWIERZCHNIA_GOSP_100_150		3
#define N5POWIERZCHNIA_GOSP_POW_150		4

#comment -------------------------------------------------------------
#comment n5inwark
#comment -------------------------------------------------------------
#define N5INWARK_STATUS_OTWARTY			1
#define N5INWARK_STATUS_ZAKONCZONY		2
#define N5INWARK_STATUS_ZATWIERDZONY	3

#comment -------------------------------------------------------------
#comment n5inwmag
#comment -------------------------------------------------------------
#define N5INWMAG_STATUS_OTWARTY			1
#define N5INWMAG_STATUS_ZAKONCZONY		2
#define N5INWMAG_STATUS_ZATWIERDZONY	3

#comment -------------------------------------------------------------



#define RAPORT_DEFAULT						1
#define NALEZNOSCI_NIEROZLICZONE			3
#define PLATNOSCI_NIESKOJARZONE				2
#define NALEZNOSCI_PRZETERMINOWANE			4
#define ZOBOWIAZANIA_NIEROZLICZONE			5
#define ZOBOWIAZANIA_PRZETERMINOWANE		6
#define PLATNOSCI_NIESKOJARZONE_KLIENT		8
#define PLATNOSCI_NIESKOJARZONE_PRACOWNIK	9
#define PLATNOSCI_NIESKOJARZONE_INSTYTUCJA	10
#define WSZYSTKIE_PRZETERMINOWANE			11

#define RAPORT_PODSUMOWANIE				14
#define RAPORT_SZCZEGOLY				15
#define RAPORT_WPISY					17


#define RAPORT_PROD_ILOSC				4
#define RAPORT_PROD_OBROTY				5

#define RAPORT_KLIENCI_OBROTY			1

#define MODULE_RAPORT_PROMOTIONBYCLIENT		60156
#define MODULE_RAPORT_PROMOTIONBYPRODUCT	60157
#define MODULE_EXECUTE_RULES				60267
#define MODULE_AKTUALIZUJ_BUDZETY			60139


#define USAGE_VIEW			1
#define USAGE_EDIT			0
#define USAGE_USER_MY_DATA	2
#define USAGE_USER_TEMPLATE	3
#define USAGE_DO_CHOICE		4


#define USAGE_SP_VIEW				1
#define USAGE_SP_EDIT_SIMPLE		2
#define USAGE_SP_EDIT_ADVANCED		3
#define USAGE_SP_EDIT_VAT			4


#define USAGE_ZAK_EDIT_VAT			2

#comment usage do umowy
#define USAGE_ZAWARCIE				4
#define USAGE_ANEKS					5
#define USAGE_ROZWIAZANIE			6

#define USAGE_SIMPLE				10

#comment RAND
#define USAGE_ZADANIE_ZLECSERWIS	11




#comment Sta³e do trybów wywo³ania parametrów (filtrów) raportu

#comment TEXT
#define PARAM_TEXT_MODE_ASK			0
#define PARAM_TEXT_MODE_ANY_TEXT	1
#define PARAM_TEXT_MODE_EQUAL		2
#define PARAM_TEXT_MODE_BEGIN		3
#define PARAM_TEXT_MODE_CONTAIN		4
#define PARAM_TEXT_MODE_RANGE		5
#define PARAM_TEXT_MODE_NONE		6


#comment DATA
#define PARAM_DATE_MODE_ASK				0
#define PARAM_DATE_MODE_ANY_DATE		1
#define PARAM_DATE_MODE_CURRENT_YEAR	2
#define PARAM_DATE_MODE_CURRENT_MONTH   3
#define PARAM_DATE_MODE_TODAY			4
#define PARAM_DATE_MODE_BEFORE          5
#define PARAM_DATE_MODE_AFTER			6
#define PARAM_DATE_MODE_RANGE			7
#define PARAM_DATE_MODE_NONE			8


#comment CURR
#define PARAM_CURR_MODE_ASK				0
#define PARAM_CURR_MODE_ANY_VALUE		1
#define PARAM_CURR_MODE_LESS_THEN		2
#define PARAM_CURR_MODE_MORE_THEN		3
#define PARAM_CURR_MODE_EQUAL			4
#define PARAM_CURR_MODE_RANGE			5
#define PARAM_CURR_MODE_NONE			6

#comment CHOICE
#define PARAM_CHOICE_MODE_ASK			0
#define PARAM_CHOICE_MODE_NONE			1
#define PARAM_CHOICE_MODE_ALL			2


#define N5FIRMA_FORMA_JODG				1
#define N5FIRMA_FORMA_CYWILNA			2
#define N5FIRMA_FORMA_JAWNA				3
#define N5FIRMA_FORMA_ZOO				4
#define N5FIRMA_FORMA_AKCYJNA			5


#define N5PIT11_JEDEN_ZAKLAD							1
#define N5PIT11_WIECEJ_NIZ_JEDEN_ZAKLAD					2
#define N5PIT11_JEDEN_ZAKLAD_ZAM_POZA					3
#define N5PIT11_WIECEJ_NIZ_JEDEN_ZAKLAD_ZAM_POZA		4


#define N5POZREALPROD_RODZAJWYCENY_CENA				1
#define N5POZREALPROD_RODZAJWYCENY_WSPOLCZYNNIK		2


#define KREATOR_REAL_ZAM_MODE_ADVANCED	1
#define KREATOR_REAL_ZAM_MODE_SIMPLE	2
#define KREATOR_REAL_ZAM_WLASNE			1
#define KREATOR_REAL_ZAM_OBCE			2


#define MULTICASH_WIZZARD_EKSPORT		1
#define MULTICASH_WIZZARD_IMPORT		2

#define MULTICASH_IMPORT_FORMAT_MILLENIUM_MT940		1
#define MULTICASH_IMPORT_FORMAT_MILLENIUM_AIPP4		2
#define MULTICASH_IMPORT_FORMAT_ING_MT942			3
#define MULTICASH_IMPORT_FORMAT_RAIFFEISEN_MT940	4
#define MULTICASH_IMPORT_FORMAT_BNPPARIBAS_MT940	5


#define PIERWSZY_DZIEN_MCA				DateSerial(year(trans_.var(GVAR_TODAY)),month(trans_.var(GVAR_TODAY)),1)
#define OSTATNI_DZIEN_MCA				DateSerial(year(trans_.var(GVAR_TODAY)),month(trans_.var(GVAR_TODAY))+1,0)


#define DOC_EXPORT_FORMAT_ECOD					1000
#define DOC_EXPORT_FORMAT_EDIXML_ECRPOLSKA		1001
#define DOC_EXPORT_FORMAT_EDIXML_ECRPOLSKA_DE	1002
#define DOC_EXPORT_FORMAT_EDIXML_ECRPOLSKA_EN	1003


#define N5RECEPTA_AKTYWNA				1
#define N5RECEPTA_NIEAKTYWNA			2


#define N5RECEPTURA_RECEPTURA		1
#define N5RECEPTURA_ZESTAW			2


#define REJDOKCONF_STD_FSAVE_NAME			"fsave"
#define REJDOK_CONG_SEPARATOR				Chr(11) 
#define REJDOK_DPC_PRINT					1
#define REJDOK_DPC_PREVIEW					2


#define N5REJDOK_RESETFLAG_ROK				(r)
#define N5REJDOK_RESETFLAG_MIESIAC			(m)



#define N5ZAMOWIENIE_WAZNOSC_ZAM			1
#define N5ZAMOWIENIE_WAZNOSC_OFE			2
#define N5ZAMOWIENIE_WAZNOSC_PROG			3



#define N5DOKETYK_TYP_WYDANIE				1
#define N5DOKETYK_TYP_KONTROLA				2
#define N5DOKETYK_TYP_ZDANIE				3
#define N5DOKETYK_TYP_KASACJA				4


#define N5OPAK_RODZAJ_NR_SERYJNEGO_BRAK		1			
#define N5OPAK_RODZAJ_NR_SERYJNEGO_WLASNE	2		
#define N5OPAK_RODZAJ_NR_SERYJNEGO_OBCE		3


#define N5PROLOJ_TYP_NALICZENIE				1
#define N5PROLOJ_TYP_ODBIOR					2
#define N5PROLOJ_TYP_KASACJA				3


#define N5KLIENT_NAZWA_PROD_PELNA			1
#define N5KLIENT_NAZWA_PROD_MIEDZYNARODOWA	2
#define N5KLIENT_NAZWA_PROD_OBCA_1			3
#define N5KLIENT_NAZWA_PROD_OBCA_2			4
#define N5KLIENT_NAZWA_PROD_OBCA_3			5



#define CENA_OBCA_1_DEFAULT			"Nazwa obcojezyczna 1"
#define CENA_OBCA_2_DEFAULT			"Nazwa obcojezyczna 2"
#define CENA_OBCA_3_DEFAULT			"Nazwa obcojezyczna 3"
#define CENA_OBCA_SEPARATOR			"#"+vbTab+"#"

#comment DB11
#define N5PLATNOSC_TYP_WPLATA               1
#define N5PLATNOSC_TYP_WYPLATA              2

#comment DB12_B
#comment -------------------------------------------------------------
#comment n5straznik_cen
#comment -------------------------------------------------------------
#define N5STRAZNIK_CEN_AKTYWNY				1
#define N5STRAZNIK_CEN_NIEAKTYWNY			2

#comment -------------------------------------------------------------
#comment Znacznik w rejestrze dokumentów sprzeda¿y
#comment -------------------------------------------------------------
#define N5REJDOK_SPRZEDAZ_ZNACZNIK_BRAK			0
#define N5REJDOK_SPRZEDAZ_ZNACZNIK_WEWNETRZNE	1
#define N5REJDOK_SPRZEDAZ_ZNACZNIK_DO_PARAGONU	2

#endif


