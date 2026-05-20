#ifndef _H1203_APPCONFIG_H_
#define _H1203_APPCONFIG_H_

#comment --------------------------------------------
#comment lista wariantów indywidualnych aplikacji
#comment 
#comment ZAMIEN DOKLADNIE JEDEN COMMENT NA DEFINE ABY UAKTYWNIC WERSJE!
#comment 
#comment --------------------------------------------
#comment _INTERGLOBAL
#comment _SISCO
#comment _CONTRANS
#comment _MGTPLAST
#comment _DENIS
#comment _MILOMLYN
#comment _IZOLACJE
#comment _ABAKUS => NIE DEFINIOWAC jako wersja. Uzyj _ABAKOSTEEL lub _GLOBTECHNIC
#comment _BARTEK
#comment _HJORT => zdefiniowaæ ENABLE_DB11_C
#comment _INTERCO
#comment _SZKOLA
#comment _SECURITY
#comment _TERRANOVA		- nazwy plikow zawieraja gandg (operator brandu Terranova)
#comment _HENRYLLOYD
#comment _ARTECH - z KPIR
#comment _ARTECH_FK - z pelna ksiegowoscia
#comment _ADOINTERNATIONAL
#comment _BARON
#comment _IOW 
#comment _RAND
#comment _GRAJEWSCY => pobraæ plik konfiguracyjny z wersji indywidualnej (SVN)
#comment _FRAM
#comment _HADEX => zdefiniowaæ ENABLE_DB11_F
#comment _TAYAMA
#comment _CDNOLAWA
#comment _UNIPLAST
#comment _ZMM
#comment _CTP
#comment _TANDEM_BAITS
#comment _IDAGA
#comment _DREWTUR
#comment _AMPLUS => pobraæ plik konfiguracyjny z wersji indywidualnej
#comment _SIGMA
#comment _TEST
#comment _PAKART
#comment _KOMPOZYTY
#comment _SWIAT_TOREBEK
#comment _TWINS_INSTALL
#comment _INTER_DIAMENT
#comment _PRINTY_LAND
#comment _MEBLE_KRASZEWICE
#comment _ABAS_INWESTYCJE
#comment _METROX
#comment _HANG_ALL
#comment _SONO
#comment _LABELMARKET
#comment _KES
#comment _ABAS
#comment _ALMA_TREND => DB12
#comment _RAFTEX
#comment _AVISTA
#comment _AB_ENZYMES
#comment _TORAL
#comment _GLOBTECHNIC
#comment _ABAKOSTEEL
#comment _NXM

#comment --------------------------------------------

#comment --------------------------------------------
#comment global tracing switches

#comment TRACE_GM

#comment --------------------------------------------
#comment version switches

#comment --------------------------------------------

#define APPCONFIG_EDITION_DATE		__APP_EDITION_DATE__
#define __APP_EDITION_VERSION__

#comment WAZNE!!!!!!!!!!!
#comment Includowaæ PRZED 1222 - to header z makrami do formularzy

#comment APPCONFIG

#comment - sposób szybkiego wybierania klienta na dokumentach handlowych
#comment APPCONFIG_CUST_QUICK_SEARCH_MODE = 1 - NIP
#comment APPCONFIG_CUST_QUICK_SEARCH_MODE = 2 - INX
#comment APPCONFIG_CUST_QUICK_SEARCH_MODE = 3 - skrot
#comment APPCONFIG_CUST_QUICK_SEARCH_MODE = 4 - INX, listy z dwoma kolumanmi

#comment - d³uga nazwa produktu na fakturze, kosztem ceny baz. netto
#comment APPCONFIG_FAKTURA_DLUGA_NAZWA

#comment - d³uga nazwa produktu na dokumentach magazynowych
#comment APPCONFIG_DM_DLUGA_NAZWA

#comment APPCONFIG_GIS	- informacja geograficzna

#comment Alternatywny sposób wybierania produktów na gridzie
#comment Wyswietlenie listy produktow - po wybraniu edycja nowej pozycji z wybranym wlasnie produktem
#comment APPCONFIG_GRID_CHOOSE_PROD_MODE_2


#comment Plugin dla firmy sisco z danyi kont w³asnych na karcie klienta
#comment APPCONFIG_SISCO_PLUGIN_CLIENT_CARD


#comment Prze³¹cznik do sterowania wyborem dokmag z dokhandl - jesli jeden to update a nie pytanie
#comment APPCONFIG_ALWAYS_UPDATE_DOKMAG


#comment Prze³¹cznik do sterowania wyborem dokmag z dokhandl - jesli jeden to update a nie pytanie
#comment APPCONFIG_NEW_SPRZEDAZ_AFTER_PUB

#comment Prze³¹cznik do traktowania uwag produktu jako zestawu parametrów
#comment APPCONFIG_PRODUKT_UWAGI_AS_PARAMSET

#comment Prze³¹cznik do sterowania wyœwietlaniem stawek VAT
#comment APPCONFIG_HIDE_12_VAT
#comment APPCONFIG_HIDE_5_VAT
#comment APPCONFIG_HIDE_17_VAT
#comment APPCONFIG_HIDE_NP_VAT

#comment Generuj raporty wg indeksu produktu a nie nazwy
#comment APPCONFIG_RAPORT_BY_PROD_INX


#comment blokowanie netto i vatu na fakturze
#comment APPCONFIG_FAKTURA_BLOKUJ_NETTOVAT

#comment Dla wyrobów sprawdzenie mo¿liwej realizacji
#define APPCONFIG_WYROBY_DO_REAL	1
 
#comment Nazwa edycji (typowo nazwa firmy) - musisz un_def aby zmienic
#define APPCONFIG_EDITION_NAME		(ogólna)

#comment Jeœli zdefiniowany to u¿ywamy PKPIR a nie pe³ne FK
#comment APPCONFIG_PKPIR

#comment Faktura netto albo brutto w zaleznosci od rodzaju klienta
#comment APPCONFIG_FAKTURA_NETTO_DLA_FIRM


#comment domyœlnie d³uga nazwa
#define APPCONFIG_FAKTURA_DLUGA_NAZWA 
#define APPCONFIG_DM_DLUGA_NAZWA

#comment raporty GM wg daty a nie numop
#comment APPCONFIG_GM_RAPORT_BY_DATE


#comment Import indeksow obcych jako EAN
#comment APPCONFIG_IMPORT_OBCY_2_EAN

#comment pokazuje koszty na dok. krajowych
#comment APPCONFIG_ZAKUP_KOSZTY_KRAJ

#comment Wprowadzanie ilosci kartonw na dokumentach handlowych
#comment APPCONFIG_SHOW_ILOSC_KARTON

#comment Dodatkowy filtr na klientów
#comment APPCONFIG_EXTRA_CUSTOMER_FILTER
#comment 0 - brak
#comment 1 - kod pocztowy



#comment Kopiowanie adnotacji z dokumentów sprzedazy
#comment APPCONFIG_KOPIUJ_ADNOTACJE_Z_FAKTUR

#comment Ukrywanie akcyzy i oplat importowych
#comment APPCONFIG_HIDE_AKCYZA_OPL_IMPORTOWE

#comment Ukrywanie daty wa¿noœci na dokmag
#comment APPCONFIG_HIDE_DATA_WAZNOSCI_DOKMAG



#comment Generowanie numerów dokumentów bez wiod¹cych zer (wedle zyczenia SISCO - tam nalezy dodac define'a)
#comment APPCONFIG_BRAK_ZER_WIODACYCH

#comment Wyszukiwanie klienta na platnosci by indeks
#comment APPCONFIG_PLATNOSC_KLIENT_BY_INX 

#comment Blokada kopiowania rabatu na pozycjach 
#comment APPCONFIG_DONOT_COPY_RABAT

#comment Blokada przeliczania ceny bazowej po rabacie
#comment APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO

#comment Zdjêcie na fakturach
#comment APPCONFIG_PICTURE_AS_XMLCOPY


#comment Blokada zapisu dowksieg jesli suma bilansowych sie nie zgadza
#comment APPCONFIG_BLOCK_SAVE_DOWKSIEG_IF_SUM_FAILS


#comment Kopiowanie cen z kartoteki produktu dla iektorych dokmag
#comment APPCONFIG_INSERT_PRICE_FROM_PROD_ON_DOKMAG


#comment JEdnolinijkowy multiline - po rozwinieciu sekcji zwiekszony do normalnego rozmiaru
#comment APPCONFIG_SMALL_MULTILINE



#comment Widoczny import cenników
#comment APPCONFIG_IMPORT_CENNIKI


#comment Widoczny import cenników
#comment APPCONFIG_POZWOL_REALIZOAWAC_PROD_GDY_BRAKI

#comment raporty rentownosc wzgledem ceny zakupu (a nie magazynu)
#comment APPCONFIG_RENTOWNOSC_ON_LAST_ZAKUP





#comment wstawianie cen na zakupach / zamowieniach obcych z polityki rabatowej
#comment APPCONFIG_WSTAWIAJ_CENY_NA_DOK_OBCYCH



#comment APPCONFIG_PROGLOJ_DEFAULT_ALGORYTM
#comment domyslny modul z funkcj¹ liczenia punktów programu lojalnosciopwego

#comment APPCONFIG_SEARCH_OTHER_DB
#comment szukanie w 2 bazach danych

#comment APPCONFIG_PLUGIN_RAPORT_ROW_COUNT
#comment liczba wierszy w mini-raportach na kartach (produktu/klienta)


#comment APPCONFIG_SHOW_TRANS_NIEROZL
#comment Pokazuj tylko transakcje nierozliczone

#define APPCONFIG_HIDE_2_VAT
#define APPCONFIG_HIDE_4_VAT
#define APPCONFIG_HIDE_5_VAT
#define APPCONFIG_HIDE_12_VAT
#define APPCONFIG_HIDE_17_VAT
#define APPCONFIG_SMALL_MULTILINE

#comment domyœlnie wszystkie !!
#comment APPCONFIG_SHOW_TRANS_NIEROZL

#comment APPCONFIG_KARTA_KLIENTA_OBIEKTY
#comment pokazywac obiekty na karcie klienta

#comment podczas tworzenia faktury z paragonu, bilansuje transakcje na paragonach
#comment APPCONFIG_FAKTURA_Z_PARAGONU_BILANS_TRANS

#comment Zwiêkszenie pola Nazwa produktu na formularzach dokumentów sprzeda¿y (Edit->Multiline)
#comment APPCONFIG_PRODUKT_NAZWA_SPRZEDAZ_MULTILINE

#comment blokada importu dokumentów, które maj¹ korektê
#comment APPCONFIG_NO_IMP_CORR

#comment blokada importu dokumentów z zamknietego okresu
#comment od 2008-02-15 domyslne ustawienie
#define APPCONFIG_NO_IMP_CLOSED

#comment pit4r dla wersji bez tabel w db10
#define APPCONFIG_DEKLARACJE4R

#comment mechanizm definiowania i przydzielania rabatów
#comment APPCONFIG_RABATY

#comment zakup koszty krajowe
#comment APPCONFIG_ZAKUP_KOSZTY_KRAJ


#comment korekty maja swoje transakcje
#comment APPCONFIG_KORTRANS_OSOBNO

#comment korekty faktur WNT maja swoje transakcje
#comment APPCONFIG_KORWNTTRANS_OSOBNO

#comment prze³¹cznik dla operacji na p³atnoœci
#comment ENABLE_DB11_PLATNOSCI_FIFO

#comment kreator p³atnoœci
#define APPCONFIG_KREATOR_PLATNOSCI

#comment kreator inwentaryzacji na dzieñ
#define APPCONFIG_INWENTARYZACJA_NA_DZIEN


#comment przenumerowanie numerów w dzienniku
#comment APPCONFIG_PRZENUM_DZIENNIK

#comment mo¿liwoœæ poprawiania transakcji (rêczne dekrety)
#comment APPCONFIG_DEKRETY_RECZNE

#comment w³¹czanie opcji wyœwietlania tylko produktów dostêpnych na magazynie
#comment APPCONFIG_SHOW_PROD_DOST

#comment przeliczanie wartoœci w walucie wed³ug ceny netto w walucie (zakup)
#comment APPCONFIG_WARTWAL_WG_NETTOWAL

#comment przegl¹danie dokumentów zakupowych wg nr dokumentu
#comment APPCONFIG_ORDERBY_NRDOK_ZAKUP

#comment raport twoja firma dzisiaj (nowy)
#define APPCONFIG_NEW_TWOJA_FIRMA_DZISIAJ

#comment umo¿liwienie realizacji zlecenia produkcyjnego z innego roku ksiêgowego
#comment APPCONFIG_ZLECPROD_CHECKDATE_FALSE

#comment pokazywanie wagi produktow na formularzach (sprzedaz,zamowienie)
#comment APPCONFIG_SHOW_WAGA_ON_FORMS

#comment raport kalendarz czasu pracy
#comment APPCONFIG_KALENDARZ_CZASU_PRACY

#comment fundusz promocji produktów rolno-spo¿ywczych
#comment APPCONFIG_FUNDUSZ_ROLNO_SPOZYWCZY

#comment dodanie schematu p³acowego dla wybranej grupy pracowników
#comment APPCONFIG_SCHEMAT_GRUPA_PRACOWNIKOW

#comment Jeœli zdefiniowany to widoczna jest edycja w postaci macierzy produktow
#comment APPCONFIG_MACIERZ_PROD

#comment przenumerowanie wpisów kasowych i bankowych po dacie
#comment APPCONFIG_REGIST_NUMBER_DATE

#comment wybór na pozycji p³atnoœci transakcji nierozliczonych oraz wszystkich
#define APPCONFIG_SHOW_TRANSAKCJE_2X

#comment modu³ serwisowy
#comment APPCONFIG_PROTOKOLY

#comment korekta VAT-UE
#define APPCONFIG_DEKLARACJE_VATUEK

#comment Blokada edycji zaksiêgowanych dokumentów (sprzeda¿, zakup, dokmag)
#comment APPCONFIG_DONOT_EDIT_DOK

#comment W przypadku tworzenia korekty do faktury sprzeda¿y nie zmieniaj terminu p³atnoœci na transakcji
#comment APPCONFIG_DONOT_EDIT_TERMIN_PLAT

#comment Mo¿liwoœc dodania dodaktowych za³¹czników do wysy³anego maila
#comment APPCONFIG_ZALACZNIKI_EMAIL

#comment Rêczna rejestracja dokumentów
#comment APPCONFIG_REGIST_NR_DOK

#comment Numer listu przewozowego na WZ (wykorzystanie strExtra1)
#comment APPCONFIG_NR_LISTU_PRZEWOZ

#define APPCONFIG_DOMYSLNY_ZESTAW_CEN	1

#ifndef APPCONFIG_KARTONY_PRECYZJA
#define APPCONFIG_KARTONY_PRECYZJA	0
#endif

#comment wersja DB10 dodatkowo z produkcja_2 (z zasobami, bez harmonogramowania)
#comment APPCONFIG_DB10_PLUS_PRODUKCJA_2

#comment czy podanie pracownika na dokumencie mag. jest wymagane
#define APPCONFIG_PRACOWNIK_WYMAGANY	0

#comment pozwól na zmianê dokumentu oryginalnego pomimo powi¹zanej korekty
#comment APPCONFIG_CHANGE_DOKORG

#comment wyszukiwanie produktu po kodzie EAN
#comment APPCONFIG_FIND_EAN

#comment import z Excel 8 (domyslnie z Excel 12)
#comment APPCONFIG_USE_EXCEL_8

#comment pokazuj opcje generowania raportow przyjaznych dla Excel
#comment APPCONFIG_SHOW_EXCEL_FRIENDLY_RAPORTS
#define APPCONFIG_SHOW_EXCEL_FRIENDLY_RAPORTS

#comment show execution time
#comment APPCONFIG_SHOW_EXEC_TIME

#comment WDT, korekta WDT => us³uga zawsze w stawce 0%
#comment APPCONFIG_VAT_0_FOR_WDT

#comment pokazywanie wszystkich dokumentów na wybranych zak³adkach karty klienta
#define APPCONFIG_SHOW_ALL_DOKUM   => musi byæ zdefiniowane gdy w³¹czamy przynajmniej 1 z poni¿szych zak³adek
#define APPCONFIG_SHOW_ALL_DOKUM_SPRZEDAZ
#define APPCONFIG_SHOW_ALL_DOKUM_ZAKUP
#define APPCONFIG_SHOW_ALL_DOKUM_TRANSAKCJA
#define APPCONFIG_SHOW_ALL_DOKUM_PLATNOSCI
#comment APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
#comment APPCONFIG_SHOW_ALL_DOKUM_REZERWACJE
#define APPCONFIG_SHOW_ALL_DOKUM_DOKUMENTY

#comment pokazywanie wszystkich dokumentów na wybranych zak³adkach karty produktu
#define APPCONFIG_SHOW_ALL_DOKUM_PROD   => musi byæ zdefiniowane gdy w³¹czamy przynajmniej 1 z poni¿szych zak³adek
#define APPCONFIG_SHOW_ALL_DOKUM_SPRZEDAZ_PROD
#define APPCONFIG_SHOW_ALL_DOKUM_ZAKUP_PROD
#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIA_PROD

#comment czy udostepniac opcje "korekty zbiorcze"
#comment APPCONFIG_KOREKTY_ZBIORCZE
#comment prze³¹cznik dla niezmiennych wydruków pamiêtanych jako za³¹czniki
#comment APPCONFIG_NIEZMIENNE_WYDRUKI

#comment prze³¹cznik dla wy³¹czenia sprawdzania roku ksiêgowego na zleceniu
#define APPCONFIG_DONOT_CHECK_ROKKSIEG_ON_ZAMOWIENIE

#comment prze³¹cznik dla wyszukiwania po kodzie EAN
#comment APPCONFIG_FIND_EAN_AND_INDEKS

#comment prze³¹cznik dla kopiowania terminu p³atnoœci z dokumentu oryginalnego na korekcie sprzeda¿y  
#comment APPCONFIG_DATA_WYM_ORG

#comment pracownik na dokumencie magazynowym (wymaga ENABLE_DB11_F)
#comment 
#comment APPCONFIG_DOKMAG_PRACOWNIK

#comment definiowanie do 5 bezposrenich zamiennikow produktu (wymaga ENABLE_DB11_F)
#comment 
#comment APPCONFIG_ZAMIENNIKI_EX

#comment prze³¹cznik do wyœwietlania na karcie klienta dokumentu oryginalnego (zak³adka sprzeda¿)
#comment APPCONFIG_KARTA_KLIENTA_ORG_SPRZEDAZ

#comment prze³¹cznik do wyœwietlania na karcie klienta dokumentu oryginalnego (zak³adka zakup)
#comment APPCONFIG_KARTA_KLIENTA_ORG_ZAKUP

#comment prze³¹cznik do wyœwietlania wszystkich naliczeñ na karcie pracownika
#define APPCONFIG_SHOW_ALL_NALICZENIA

#comment prze³¹cznik blokady zapisu dowodu ksiêgowego bez dekretu
#comment APPCONFIG_DOWOD_KSIEG_WITHOUT_DEKRET

#comment prze³¹cznik podsumowania kolumny Saldo sald (ZOiS)
#comment APPCONFIG_SUMA_SALDO_SALD

#comment prze³¹cznik dla uprawnienia do odksiêgowania faktury maj¹cej przypisan¹ korektê
#define APPCONFIG_ODKSIEGOWANIE_FAKTURY

#comment prze³¹cznik dla uwzglêdniania kwoty zagranicznej w obcej walucie dla WNT/Import spoza UE (karta klienta)
#comment APPCONFIG_ZAKUP_OPLATY_ZAGRANICZNE_KARTA_KLIENTA

#comment prze³¹cznik dla ograniczonego wyboru/podpowiedzi klienta na formularzach
#comment APPCONFIG_OGRANICZONY_WYBOR_KLIENTA

#comment prze³¹cznik dla sortowania dokumentów zakupu wg daty otrzymania potem nr dokumentu
#comment APPCONFIG_ZAKUP_ORDER_BY_DATA_OTRZYM

#comment prze³¹cznik dla kreatora wysy³ki faktur mailem w postaci pdf
#define APPCONFIG_SPRZEDAZ_EMAIL_PDF
#comment dodatkowy parametr do kreatora wysy³ki faktur mailem w postaci pdf (znacznik Tak/Nie na kliencie)
#comment APPCONFIG_SPRZEDAZ_EMAIL_PDF_ZNACZNIK

#comment prze³¹cznik zapisu dokumentu handlowego bez rozliczenia VAT
#comment APPCONFIG_SAVE_DOKHANDL_BEZ_ROZL_VAT

#comment prze³¹cznik dla ustawiania magazynu Ÿród³owego WZ z dokumentu handlowego (magazyn wydania)
#comment APPCONFIG_MAGAZYN_ZRODLOWY_Z_DOKHANDL

#comment prze³¹cznik dla wyboru banku przy eksporcie do multicash
#comment APPCONFIG_CHECK_BANK_MULTICASH

#comment prze³¹cznik dla kreatora ksiêgowañ grupowych z kilku rejestrów
#define APPCONFIG_KREATOR_KSIEGOWAN_WIELE_REJESTROW

#comment prze³¹cznik dla sprawdzacza nowych zamówieñ
#comment APPCONFIG_POWIADOMIENIA_NOWE_ZAMOWIENIA
#define APPCONFIG_POWIADOMIENIA_NOWE_ZAMOWIENIA

#comment prze³¹cznik dla raportu ewidencji korekt paragonów
#comment APPCONFIG_EWIDENCJA_KOREKT_PARAGONOW

#comment dokument dostawy wyrobów wêglowych
#comment APPCONFIG_DOSTAWA_WEGLA

#comment tworzenie dostawy podczas rejestracji faktury
#comment APPCONFIG_UTWORZ_DOSTAWE_W_TLE

#comment wysy³ka emaila bezpoœrednio z serwera pocztowego
#comment APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO

#comment wyszukiwanie klientów w bazie GUS
#comment WESZLO DO STANDARDU - WSZYSCY MAJA MIEC WLACZONE 
#define APPCONFIG_FIND_KLIENT_GUS

#comment zezwól na korzystanie z NXM_JSE
#comment APPCONFIG_ALLOW_NXM_JSE

#comment tworzenie dostawy w tle przy akcji przycisku na formularzu sprzeda¿y
#comment APPCONFIG_UTWORZ_DOSTAWE_W_TLE_PRZYCISK

#comment automat przeksiêgowañ na dowodzie ksiêgowym
#comment APPCONFIG_AUTOMAT_PRZEKSIEGOWAN


#comment wklejanie produktów z Excela
#comment WESZLO DO STANDARDU - WSZYSCY MAJA MIEC WLACZONE
#define APPCONFIG_PASTE_PRODUCT_FROM_EXCEL

#comment kreator wyci¹gów bankowych
#comment WESZLO DO STANDARDU - WSZYSCY MAJA MIEC WLACZONE

#comment APPCONFIG_KREATOR_WYCIAGOW_BANKOWYCH
#define APPCONFIG_KREATOR_WYCIAGOW_BANKOWYCH

#comment prze³¹cznik kreatora dokumentów do wysy³ki
#comment APPCONFIG_KREATOR_DOKUMENTOW_DO_WYSYLKI

#comment Prze³acznik depe³niania numeracji dokumentów dla miesi¹ca 0 na pocz¹tku (styczeñ - 01, luty - 02, itd.)
#comment APPCONFIG_DOPELNIENIE_NUMERACJI_MIESIACA

#comment prze³¹cznik aktualizacji cen na kilku dokumentach PZ
#comment APPCONFIG_AKTUALIZACJA_CEN_PZ

#comment prze³¹cznik definiowania widocznoœci grup produtków w kartotece klienta DB15
#comment APPCONFIG_WIDOCZNOSC_GRUP_PRODUKTOW

#comment prze³¹cznik eksportu dokumentów WZ do EDI
#comment APPCONFIG_EKSPORT_WZ_TO_EDI

#comment prze³¹cznik pobierania adresów na podstawie kodu pocztowego
#comment APPCONFIG_ADDRESSES_BY_ZIP

#comment prze³¹cznik sprawdzania statusu rachunku bankowego w KAS
#comment APPCONFIG_STATUS_KAS

#comment prze³¹cznik domyœlnie w³¹czonego mechanizmu sprawdzania MPP
#comment APPCONFIG_MPP_ENABLED

#comment prze³¹cznik dla rozró¿niania wo³ania raportu Rezerwacje do zwolnienia z pomiomu menu -> Raport
#comment APPCONFIG_MANUAL_CALL_REZERWACJE

#comment prze³¹cznik tworzenia ZZ z korekty faktury do wielu WZ podpiêtych do faktury
#comment APPCONFIG_UTWORZ_ZZ_WIELE_WZ

#comment prze³¹cznik dla pokazywania statusu faktury wysy³anej droga elektroniczn¹ + przycisk WYŒLIJ MAIL
#comment APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS

#comment prze³¹cznik dla pokazywania statusu dokumentu magazynowego wysy³anego droga elektroniczn¹ + przycisk WYŒLIJ MAIL
#comment APPCONFIG_DOKMAG_ELEKTRONICZNY_STATUS

#comment Mechanizm Podzielonej P³atnoœci 3 stanowy (brak, obligatoryjne, fakultatywne)
#comment APPCONFIG_MPP_3_STANOWE

#comment Wspólna faktura zaliczkowa w PLN i walucie
#comment APPCONFIG_COMMON_FZAL

#comment £adowanie zadañ w tle bez aktywacji okna komunikatów
#comment APPCONFIG_RUN_TASK_SILENT

#comment Pokazywanie komunikatu o wybranej drukarce
#comment APPCONFIG_SHOW_MESSAGE_ABOUT_PRINTER

#comment obs³uga bramek p³atniczych
#comment APPCONFIG_PAYMENT_GATEWAYS

#ifdef _CDNOLAWA
   #undef APPCONFIG_EDITION_NAME
   #define APPCONFIG_EDITION_NAME	"CDN Sp. j."
   #define APPCONFIG_PRODUKT_NAZWA_SPRZEDAZ_MULTILINE
   #define APPCONFIG_DATA_WYM_ORG
   #define APPCONFIG_EWIDENCJA_KOREKT_PARAGONOW
#endif


#comment domyœlnie wg NIP	 1-NIP, 2-INX


#ifdef _DEBUG
	#define APPCONFIG_GIS
#endif

#ifdef _IZOLACJE
	#define APPCONFIG_GRID_CHOOSE_PROD_MODE_2
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"ISOLACJE POLSKA"
	#define APPCONFIG_FAKTURA_NETTO_DLA_FIRM
	#define APPCONFIG_PICTURE_AS_XMLCOPY
	#undef APPCONFIG_WYROBY_DO_REAL
	#define APPCONFIG_WYROBY_DO_REAL	0
#endif

#ifdef _HJORT	
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Hjort-Knudsen"
	#define APPCONFIG_RAPORT_BY_PROD_INX
    #define APPCONFIG_WARTWAL_WG_NETTOWAL
	#define APPCONFIG_FIND_EAN
#endif

#ifdef _BARTEK
	#define APPCONFIG_SHOW_TRANS_NIEROZL
	#define APPCONFIG_SHOW_ILOSC_KARTON
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Bartek"
	#define APPCONFIG_IMPORT_OBCY_2_EAN
	#define APPCONFIG_INSERT_PRICE_FROM_PROD_ON_DOKMAG
	#define APPCONFIG_POZWOL_REALIZOAWAC_PROD_GDY_BRAKI
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		3
	#undef APPCONFIG_DOMYSLNY_ZESTAW_CEN
	#define APPCONFIG_DOMYSLNY_ZESTAW_CEN	6
    #define APPCONFIG_PRZENUM_DZIENNIK
    #define APPCONFIG_SCHEMAT_GRUPA_PRACOWNIKOW
    #define APPCONFIG_KALENDARZ_CZASU_PRACY
	#define APPCONFIG_REGIST_NUMBER_DATE
	#define APPCONFIG_KARTA_KLIENTA_ORG_SPRZEDAZ
	#define APPCONFIG_KARTA_KLIENTA_ORG_ZAKUP
	#define APPCONFIG_DOWOD_KSIEG_WITHOUT_DEKRET
#endif

#ifdef _INTERGLOBAL
	#define APPCONFIG_BCS_ENABLED
	#define APPCONFIG_KOREKTA_MM
	#define APPCONFIG_GRID_CHOOSE_PROD_MODE_2
	#define APPCONFIG_ALWAYS_UPDATE_DOKMAG
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Inter Global"
	#define APPCONFIG_RAPORT_BY_PROD_INX
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		2
	#undef APPCONFIG_FAKTURA_DLUGA_NAZWA
	#undef APPCONFIG_DM_DLUGA_NAZWA
	#define APPCONFIG_FAKTURA_BLOKUJ_NETTOVAT 
	#define APPCONFIG_GM_RAPORT_BY_DATE
#endif

#ifdef _DENIS
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		2
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Denis Foods"
	#define APPCONFIG_EKSPORT_WZ_TO_EDI
	#define APPCONFIG_KREATOR_DOKUMENTOW_DO_WYSYLKI
	#define APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_DOKMAG_ELEKTRONICZNY_STATUS
	#define APPCONFIG_DONOT_COPY_RABAT
#endif

#ifdef _MILOMLYN
	#define APPCONFIG_PRODUKT_UWAGI_AS_PARAMSET
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Mi³oM³yn"
	#undef  APPCONFIG_HIDE_5_VAT
	#define APPCONFIG_BLOCK_SAVE_DOWKSIEG_IF_SUM_FAILS
    #define APPCONFIG_FUNDUSZ_ROLNO_SPOZYWCZY
	#define N5REJESTRDOK_IDOBJ_FAKTUR_SPRZEDAZY			107
	#define N5REJESTRDOK_IDOBJ_FAKTUR_ZAKUPU			95
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE_PRZYCISK
#endif

#ifdef _ABAKOSTEEL
	#define _ABAKUS
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Abakosteel"
	#define APPCONFIG_AKTUALIZACJA_CEN_PZ
	#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
	#define APPCONFIG_UTWORZ_ZZ_WIELE_WZ
	#define ENABLE_DB11_PLATNOSCI_FIFO
	#define APPCONFIG_SHOW_MESSAGE_ABOUT_PRINTER
	#define APPCONFIG_MACIERZ_PROD
	#define APPCONFIG_DONOT_EDIT_TERMIN_PLAT
	#define APPCONFIG_SHOW_WAGA_ON_FORMS
	
	#define ZAMF_LINE_CHECKBOX

#define APPCONFIG_PROD_STORE_INFO_BY_NXM

#define _NOT_DEF_NXM_EXPERIMENTAL_SET_1

#endif 

#ifdef _GLOBTECHNIC
	#define _ABAKUS
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"GlobTechnic"
#endif 

#ifdef _ABAKUS
	#define APPCONFIG_RAPORT_BY_PROD_INX
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		3
	#define APPCONFIG_HIDE_DATA_WAZNOSCI_DOKMAG
	#define APPCONFIG_PLATNOSC_KLIENT_BY_INX
	#define APPCONFIG_DONOT_COPY_RABAT
	#define APPCONFIG_RENTOWNOSC_ON_LAST_ZAKUP
	#define APPCONFIG_PLUGIN_RAPORT_ROW_COUNT		20
	#define APPCONFIG_OGRANICZONY_WYBOR_KLIENTA
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE_PRZYCISK
	#define APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS
#endif

#ifdef _INTERCO
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Interco"
	#define APPCONFIG_COPY_DOKMAG_AS_INTERCO_STRING
	#define APPCONFIG_RAPORT_BY_PROD_INX	
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		1
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
	#define APPCONFIG_DONOT_COPY_RABAT
	#define APPCONFIG_SHOW_TRANS_NIEROZL
    #define APPCONFIG_WARTWAL_WG_NETTOWAL
	#define APPCONFIG_USE_EXCEL_8
	#define _IOW_ECWS_ON_CUSTOMER_LEVEL
	#define APPCONFIG_AUTOMAT_PRZEKSIEGOWAN
	#define APPCONFIG_DEKRETY_RECZNE
	#define APPCONFIG_KREATOR_DOKUMENTOW_DO_WYSYLKI
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS
	#define APPCONFIG_DOKMAG_ELEKTRONICZNY_STATUS
#endif

#ifdef _HENRYLLOYD
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Henry Lloyd"
	#define APPCONFIG_RAPORT_BY_PROD_INX
#endif

#ifdef _ARTECH
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Artech"
	#define APPCONFIG_KARTA_KLIENTA_OBIEKTY
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
	#define APPCONFIG_DONOT_COPY_RABAT
    #define APPCONFIG_WARTWAL_WG_NETTOWAL
	#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
	#define APPCONFIG_PKPIR
#endif

#ifdef _ARTECH_FK
#undef  APPCONFIG_EDITION_NAME
#define APPCONFIG_EDITION_NAME	"Artech (Pe³na ksiêgowoœæ)"
#define APPCONFIG_KARTA_KLIENTA_OBIEKTY
#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
#define APPCONFIG_DONOT_COPY_RABAT
#define APPCONFIG_WARTWAL_WG_NETTOWAL
#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
#define _ARTECH
#endif


#ifdef _TANDEM_BAITS
	#undef  APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Tandem Baits"
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
	#define APPCONFIG_DONOT_COPY_RABAT
	#define APPCONFIG_REGIST_NUMBER_DATE
	#define APPCONFIG_UNIVERSAL_VAT
	#define APPCONFIG_PAYMENT_GATEWAYS
#endif

#ifdef _IOW
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"IOW Service Sp. z o.o."
	#define APPCONFIG_OZNACZENIE_PRODUCENTA
	#define APPCONFIG_OZNACZENIE_DOKUMENTU
	#define APPCONFIG_PRODUKT_ORG
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		2
	#define APPCONFIG_KONTROLUJ_KWOTY_ZARACHOWANIA
	#define APPCONFIG_TRANSAKCJA_BY_FZALICZKOWA
	#comment pokazuje na dokumencie superaty cene netto3 produktu. Zmien na (..._cene_netto3) lub (..._cene_brutto3) lub (..._cene_brutto1) lub (..._cene_netto1) plik x10161
	#define SUPERATA_POKAZ_CENE_NETTO3
	#define APPCONFIG_KORTRANS_OSOBNO
	#define APPCONFIG_KORWNTTRANS_OSOBNO
	#define APPCONFIG_GM_RAPORT_BY_DATE
    #define APPCONFIG_PRZENUM_DZIENNIK
    #define APPCONFIG_ZLECPROD_CHECKDATE_FALSE
	#define N5REJESTRDOK_IDOBJ_FVAT_EUR			428
	#define N5REJESTRDOK_IDOBJ_KOR_FVAT_EUR			430
	#define APPCONFIG_REGIST_NUMBER_DATE
	#define APPCONFIG_REGIST_NR_DOK
	#define APPCONFIG_VAT_0_FOR_WDT
	#comment APPCONFIG_DONOT_CHECK_ROKKSIEG_ON_ZAMOWIENIE
	#define APPCONFIG_ZAMIENNIKI_EX
	#define APPCONFIG_SUMA_SALDO_SALD
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE
	#define APPCONFIG_DOPELNIENIE_NUMERACJI_MIESIACA
	#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
	#define APPCONFIG_MANUAL_CALL_REZERWACJE
	#define APPCONFIG_COMMON_FZAL
	#define APPCONFIG_SHOW_ALL_DOKUM_REZERWACJE
#endif


#ifdef _CTP
	#undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Centrum Taœm i Pasów"
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		3
    #define APPCONFIG_KALENDARZ_CZASU_PRACY
	#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
	#define APPCONFIG_KREATOR_DOKUMENTOW_DO_WYSYLKI
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS
	#define APPCONFIG_DOKMAG_ELEKTRONICZNY_STATUS
#endif

#ifdef _IDAGA
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Idaga"
#endif

#ifdef _ZMM
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"ZMM S.C."
    #define APPCONFIG_SHOW_PROD_DOST
    #define APPCONFIG_ZLECPROD_CHECKDATE_FALSE
#endif

#ifdef _PRINTY_LAND
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Printy Land Sp. z o.o."
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
	#define APPCONFIG_DONOT_COPY_RABAT
#endif

#ifdef _ABAS_INWESTYCJE
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Abas Inwestycje Sp. z o.o."
	#define APPCONFIG_PROTOKOLY
	#define APPCONFIG_KARTA_KLIENTA_OBIEKTY
	#define APPCONFIG_ZALACZNIKI_EMAIL
	#define APPCONFIG_CHECK_BANK_MULTICASH
#endif

#ifdef _LABELMARKET
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"LABELMARKET Sp. z o.o."
	#define APPCONFIG_KREATOR_DOKUMENTOW_DO_WYSYLKI
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_FAKTURA_ELEKTRONICZNA_STATUS
	#define APPCONFIG_DOKMAG_ELEKTRONICZNY_STATUS
#endif

#ifdef _KES
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Kontny Elektronik Service Sp.j."
	#define APPCONFIG_PROTOKOLY
	#define APPCONFIG_KARTA_KLIENTA_OBIEKTY
	#define APPCONFIG_FIND_EAN
	#define APPCONFIG_MAGAZYN_ZRODLOWY_Z_DOKHANDL
	#define APPCONFIG_EWIDENCJA_KOREKT_PARAGONOW
	#define APPCONFIG_EMAIL_Z_SERWERA_POCZTOWEGO
	#define APPCONFIG_SHOW_ALL_DOKUM_ZAMOWIENIE
	#define APPCONFIG_SHOW_ALL_DOKUM_REZERWACJE
	#define APPCONFIG_RUN_TASK_SILENT
#endif

#ifdef _ABAS
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Abas"
#endif

#ifdef _ABAS_KPIR
#undef APPCONFIG_EDITION_NAME
#define APPCONFIG_EDITION_NAME	"Abas - PKPIR"
#define APPCONFIG_PKPIR
#define _ABAS
#endif


#ifdef _ALMA_TREND
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Alma Trend Sp. z o.o."
	#define APPCONFIG_REGIST_NR_DOK
	#ifdef APPCONFIG_CUST_QUICK_SEARCH_MODE
		#undef  APPCONFIG_CUST_QUICK_SEARCH_MODE
	#endif
	#define APPCONFIG_CUST_QUICK_SEARCH_MODE		2
	#define APPCONFIG_NR_LISTU_PRZEWOZ
	#define APPCONFIG_SHOW_EXEC_TIME
    #define APPCONFIG_DEKRETY_RECZNE
	#define ENABLE_DB11_PLATNOSCI_FIFO
	#define APPCONFIG_NIEZMIENNE_WYDRUKI
	#define APPCONFIG_ZAKUP_OPLATY_ZAGRANICZNE_KARTA_KLIENTA
	#define APPCONFIG_OGRANICZONY_WYBOR_KLIENTA
	#define APPCONFIG_SAVE_DOKHANDL_BEZ_ROZL_VAT
	#define APPCONFIG_CHECK_BANK_MULTICASH
	#define APPCONFIG_FIND_EAN_AND_INDEKS
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE
	#define APPCONFIG_DONOT_COPY_RABAT
	#define APPCONFIG_CENABAZOWA_I_RABAT_OSOBNO
#endif

#ifdef _TORAL
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"T.H.O.R. Toral"
	#define APPCONFIG_KARTA_KLIENTA_OBIEKTY
	#define APPCONFIG_PROTOKOLY
    #define ENABLE_DB11_PLATNOSCI_FIFO
	#define APPCONFIG_NUMER_KATALOGOWY
	#define APPCONFIG_GM_RAPORT_BY_DATE
    #define APPCONFIG_DEKRETY_RECZNE
	#define APPCONFIG_DATA_WYM_ORG
	#define APPCONFIG_FIND_EAN_AND_INDEKS
	#define APPCONFIG_DONOT_COPY_RABAT
	#define APPCONFIG_DOKMAG_PRACOWNIK
	#define APPCONFIG_ZAKUP_ORDER_BY_DATA_OTRZYM
	#define APPCONFIG_DOSTAWA_WEGLA
	#define APPCONFIG_EWIDENCJA_KOREKT_PARAGONOW
	#define APPCONFIG_AUTOMAT_PRZEKSIEGOWAN
	#define APPCONFIG_UTWORZ_DOSTAWE_W_TLE_PRZYCISK
	#define APPCONFIG_FAKTURA_BLOKUJ_NETTOVAT
	#define APPCONFIG_MANUAL_CALL_REZERWACJE
#endif

#ifdef _TEST
    #undef APPCONFIG_EDITION_NAME
	#define APPCONFIG_EDITION_NAME	"Wersja testowa"
	#define APPCONFIG_INTG_POROW_DOK
#endif


#ifdef _NXM
#undef  APPCONFIG_EDITION_NAME
#define APPCONFIG_EDITION_NAME	"NXM Sp. z o.o."
#endif

#ifndef APPCONFIG_EXTRA_CUSTOMER_FILTER
	#define APPCONFIG_EXTRA_CUSTOMER_FILTER	1
#endif

#ifndef APPCONFIG_PROGLOJ_DEFAULT_ALGORYTM
#define APPCONFIG_PROGLOJ_DEFAULT_ALGORYTM		1
#endif

#define APPCONFIG_KOPIUJ_ADNOTACJE_Z_FAKTUR
#define APPCONFIG_WSTAWIAJ_CENY_NA_DOK_OBCYCH
#comment 27_04_2005 - wlatuje do standardu
#define APPCONFIG_IMPORT_CENNIKI


#ifndef APPCONFIG_PLUGIN_RAPORT_ROW_COUNT
#define APPCONFIG_PLUGIN_RAPORT_ROW_COUNT		10
#endif

#ifdef ENABLE_DB15
#ifndef APPCONFIG_ADDRESSES_BY_ZIP
#define APPCONFIG_ADDRESSES_BY_ZIP
#endif

#ifndef APPCONFIG_STATUS_KAS
#define APPCONFIG_STATUS_KAS
#endif

#ifndef APPCONFIG_WIDOCZNOSC_GRUP_PRODUKTOW
#define APPCONFIG_WIDOCZNOSC_GRUP_PRODUKTOW
#endif

#endif

#endif
