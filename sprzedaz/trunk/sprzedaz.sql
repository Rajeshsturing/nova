-- NAVO Enterprise SQL script--
-- generated: 2003-12-03 13:26:30
use %DBNAME%
go
-- dropping FK

if exists (select * from sysobjects where name='ENUM_n5jednostka_eTyp_5')
	alter table n5jednostka drop constraint ENUM_n5jednostka_eTyp_5
go
if exists (select * from sysobjects where name='FK_n5kraj_n5jednostka_4')
	alter table n5kraj drop constraint FK_n5kraj_n5jednostka_4
go
if exists (select * from sysobjects where name='FK_n5bank_n5miejscowosc_11')
	alter table n5bank drop constraint FK_n5bank_n5miejscowosc_11
go
if exists (select * from sysobjects where name='FK_n5instytucja_n5typinstytucji_4')
	alter table n5instytucja drop constraint FK_n5instytucja_n5typinstytucji_4
go
if exists (select * from sysobjects where name='FK_n5instytucja_n5miejscowosc_10')
	alter table n5instytucja drop constraint FK_n5instytucja_n5miejscowosc_10
go
if exists (select * from sysobjects where name='ENUM_n5uzytkownik_eAktywny_7')
	alter table n5uzytkownik drop constraint ENUM_n5uzytkownik_eAktywny_7
go
if exists (select * from sysobjects where name='FK_n5klient_n5miejscowosc_10')
	alter table n5klient drop constraint FK_n5klient_n5miejscowosc_10
go
if exists (select * from sysobjects where name='ENUM_n5klient_eTypDT_25')
	alter table n5klient drop constraint ENUM_n5klient_eTypDT_25
go
if exists (select * from sysobjects where name='ENUM_n5klient_eAktywny_37')
	alter table n5klient drop constraint ENUM_n5klient_eAktywny_37
go
if exists (select * from sysobjects where name='ENUM_n5klient_eKlasaKlienta_38')
	alter table n5klient drop constraint ENUM_n5klient_eKlasaKlienta_38
go
if exists (select * from sysobjects where name='FK_n5klient_n5jednostka_39')
	alter table n5klient drop constraint FK_n5klient_n5jednostka_39
go
if exists (select * from sysobjects where name='ENUM_n5klient_ePlec_50')
	alter table n5klient drop constraint ENUM_n5klient_ePlec_50
go
if exists (select * from sysobjects where name='FK_n5klient_n5grupaklient_54')
	alter table n5klient drop constraint FK_n5klient_n5grupaklient_54
go
if exists (select * from sysobjects where name='ENUM_n5klient_ePrywat_55')
	alter table n5klient drop constraint ENUM_n5klient_ePrywat_55
go
if exists (select * from sysobjects where name='ENUM_n5klient_eWiarFin_64')
	alter table n5klient drop constraint ENUM_n5klient_eWiarFin_64
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_ePlec_9')
	alter table n5pracownik drop constraint ENUM_n5pracownik_ePlec_9
go
if exists (select * from sysobjects where name='FK_n5pracownik_n5miejscowosc_15')
	alter table n5pracownik drop constraint FK_n5pracownik_n5miejscowosc_15
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_eAktywny_27')
	alter table n5pracownik drop constraint ENUM_n5pracownik_eAktywny_27
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_eTypDT_31')
	alter table n5pracownik drop constraint ENUM_n5pracownik_eTypDT_31
go
if exists (select * from sysobjects where name='FK_n5pracownik_n5jedn_org_34')
	alter table n5pracownik drop constraint FK_n5pracownik_n5jedn_org_34
go
if exists (select * from sysobjects where name='FK_n5firma_n5miejscowosc_9')
	alter table n5firma drop constraint FK_n5firma_n5miejscowosc_9
go
if exists (select * from sysobjects where name='ENUM_n5firma_eForma_21')
	alter table n5firma drop constraint ENUM_n5firma_eForma_21
go
if exists (select * from sysobjects where name='FK_n5firma_n5jednostka_33')
	alter table n5firma drop constraint FK_n5firma_n5jednostka_33
go
if exists (select * from sysobjects where name='FK_n5firma_n5jedn_org_39')
	alter table n5firma drop constraint FK_n5firma_n5jedn_org_39
go
if exists (select * from sysobjects where name='ENUM_n5miejscowosc_eWielkosc_3')
	alter table n5miejscowosc drop constraint ENUM_n5miejscowosc_eWielkosc_3
go
if exists (select * from sysobjects where name='FK_n5miejscowosc_n5wojewodztwo_4')
	alter table n5miejscowosc drop constraint FK_n5miejscowosc_n5wojewodztwo_4
go
if exists (select * from sysobjects where name='ENUM_n5klient_pracownik_ePlec_5')
	alter table n5klient_pracownik drop constraint ENUM_n5klient_pracownik_ePlec_5
go
if exists (select * from sysobjects where name='ENUM_n5klient_pracownik_eStanCywilny_8')
	alter table n5klient_pracownik drop constraint ENUM_n5klient_pracownik_eStanCywilny_8
go
if exists (select * from sysobjects where name='FK_n5klient_pracownik_n5klient_10')
	alter table n5klient_pracownik drop constraint FK_n5klient_pracownik_n5klient_10
go
if exists (select * from sysobjects where name='ENUM_n5klient_pracownik_eAktywny_22')
	alter table n5klient_pracownik drop constraint ENUM_n5klient_pracownik_eAktywny_22
go
if exists (select * from sysobjects where name='FK_n5jedn_org_n5miejscowosc_11')
	alter table n5jedn_org drop constraint FK_n5jedn_org_n5miejscowosc_11
go
if exists (select * from sysobjects where name='FK_n5_klient_jedn_org_n5miejscowosc_9')
	alter table n5_klient_jedn_org drop constraint FK_n5_klient_jedn_org_n5miejscowosc_9
go
if exists (select * from sysobjects where name='FK_n5_klient_jedn_org_n5klient_27')
	alter table n5_klient_jedn_org drop constraint FK_n5_klient_jedn_org_n5klient_27
go
if exists (select * from sysobjects where name='ENUM_n5typdokumentu_eRodzaj_4')
	alter table n5typdokumentu drop constraint ENUM_n5typdokumentu_eRodzaj_4
go
if exists (select * from sysobjects where name='FK_n5dokument_n5typdokumentu_5')
	alter table n5dokument drop constraint FK_n5dokument_n5typdokumentu_5
go
if exists (select * from sysobjects where name='WRT_n5dokument_wpNadawca_8')
	alter table n5dokument drop constraint WRT_n5dokument_wpNadawca_8
go
if exists (select * from sysobjects where name='WRT_n5dokument_wpAdresat_9')
	alter table n5dokument drop constraint WRT_n5dokument_wpAdresat_9
go
if exists (select * from sysobjects where name='ENUM_n5dokument_nForma_11')
	alter table n5dokument drop constraint ENUM_n5dokument_nForma_11
go
if exists (select * from sysobjects where name='FK_n5zadanie_n5wykonawca_5')
	alter table n5zadanie drop constraint FK_n5zadanie_n5wykonawca_5
go
if exists (select * from sysobjects where name='ENUM_n5zadanie_ePriorytet_6')
	alter table n5zadanie drop constraint ENUM_n5zadanie_ePriorytet_6
go
if exists (select * from sysobjects where name='ENUM_n5zadanie_eTypterminRozp_7')
	alter table n5zadanie drop constraint ENUM_n5zadanie_eTypterminRozp_7
go
if exists (select * from sysobjects where name='ENUM_n5zadanie_eTypterminZak_10')
	alter table n5zadanie drop constraint ENUM_n5zadanie_eTypterminZak_10
go
if exists (select * from sysobjects where name='FK_n5zadanie_n5typdzialania_14')
	alter table n5zadanie drop constraint FK_n5zadanie_n5typdzialania_14
go
if exists (select * from sysobjects where name='WRT_n5zadanie_wrefSzczegoly_16')
	alter table n5zadanie drop constraint WRT_n5zadanie_wrefSzczegoly_16
go
if exists (select * from sysobjects where name='FK_n5pozplatnosc_n5transakcja_7')
	alter table n5pozplatnosc drop constraint FK_n5pozplatnosc_n5transakcja_7
go
if exists (select * from sysobjects where name='WRT_n5wykonawca_wrefObiekt_3')
	alter table n5wykonawca drop constraint WRT_n5wykonawca_wrefObiekt_3
go
if exists (select * from sysobjects where name='ENUM_choicelist_edynamic_4')
	alter table choicelist drop constraint ENUM_choicelist_edynamic_4
go
if exists (select * from sysobjects where name='WRT_n5zadaniezal_wrefZal_2')
	alter table n5zadaniezal drop constraint WRT_n5zadaniezal_wrefZal_2
go
if exists (select * from sysobjects where name='FK_n5WizzardEmailDokumElem_n5dokument_2')
	alter table n5WizzardEmailDokumElem drop constraint FK_n5WizzardEmailDokumElem_n5dokument_2
go
if exists (select * from sysobjects where name='FK_n5WizzardEmail_choicelist_2')
	alter table n5WizzardEmail drop constraint FK_n5WizzardEmail_choicelist_2
go
if exists (select * from sysobjects where name='WRT_n5SendEmail_wpNadawca_2')
	alter table n5SendEmail drop constraint WRT_n5SendEmail_wpNadawca_2
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5sposplat_6')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5sposplat_6
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5klient_7')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5klient_7
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5uzytkownik_10')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5uzytkownik_10
go
if exists (select * from sysobjects where name='ENUM_n5sprzedaz_eSposVAT_12')
	alter table n5sprzedaz drop constraint ENUM_n5sprzedaz_eSposVAT_12
go
if exists (select * from sysobjects where name='ENUM_n5sprzedaz_eNettoBrutto_13')
	alter table n5sprzedaz drop constraint ENUM_n5sprzedaz_eNettoBrutto_13
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5rejestrdok_19')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5rejestrdok_19
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5jednostka_51')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5jednostka_51
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5rozlvat_52')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5rozlvat_52
go
if exists (select * from sysobjects where name='ENUM_n5opakowanie_produktu_eRodzaj_3')
	alter table n5opakowanie_produktu drop constraint ENUM_n5opakowanie_produktu_eRodzaj_3
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_10')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_10
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_23')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_23
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_25')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_25
go
if exists (select * from sysobjects where name='ENUM_n5produkt_eVAT_7')
	alter table n5produkt drop constraint ENUM_n5produkt_eVAT_7
go
if exists (select * from sysobjects where name='FK_n5produkt_n5jednostka_11')
	alter table n5produkt drop constraint FK_n5produkt_n5jednostka_11
go
if exists (select * from sysobjects where name='ENUM_n5produkt_eAktywny_12')
	alter table n5produkt drop constraint ENUM_n5produkt_eAktywny_12
go
if exists (select * from sysobjects where name='FK_n5produkt_n5grupaproduktow_14')
	alter table n5produkt drop constraint FK_n5produkt_n5grupaproduktow_14
go
if exists (select * from sysobjects where name='ENUM_n5produkt_eRodzaj_19')
	alter table n5produkt drop constraint ENUM_n5produkt_eRodzaj_19
go
if exists (select * from sysobjects where name='FK_n5pozsprzedaz_n5produkt_2')
	alter table n5pozsprzedaz drop constraint FK_n5pozsprzedaz_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozsprzedaz_n5opakowanie_produktu_4')
	alter table n5pozsprzedaz drop constraint FK_n5pozsprzedaz_n5opakowanie_produktu_4
go
if exists (select * from sysobjects where name='ENUM_n5pozsprzedaz_eVAT_8')
	alter table n5pozsprzedaz drop constraint ENUM_n5pozsprzedaz_eVAT_8
go
if exists (select * from sysobjects where name='FK_n5dokumentlinks_n5dokument_2')
	alter table n5dokumentlinks drop constraint FK_n5dokumentlinks_n5dokument_2
go
if exists (select * from sysobjects where name='FK_n5pkpir_n5rejestrdok_4')
	alter table n5pkpir drop constraint FK_n5pkpir_n5rejestrdok_4
go
if exists (select * from sysobjects where name='ENUM_n5rejestrdok_eTyp_3')
	alter table n5rejestrdok drop constraint ENUM_n5rejestrdok_eTyp_3
go
if exists (select * from sysobjects where name='ENUM_n5rejestrdok_eAktywny_6')
	alter table n5rejestrdok drop constraint ENUM_n5rejestrdok_eAktywny_6
go
if exists (select * from sysobjects where name='WRT_n5rejestrdok_wrefParam1_13')
	alter table n5rejestrdok drop constraint WRT_n5rejestrdok_wrefParam1_13
go
if exists (select * from sysobjects where name='WRT_n5rejestrdok_wrefParam2_14')
	alter table n5rejestrdok drop constraint WRT_n5rejestrdok_wrefParam2_14
go
if exists (select * from sysobjects where name='FK_n5konto_n5jednostka_5')
	alter table n5konto drop constraint FK_n5konto_n5jednostka_5
go
if exists (select * from sysobjects where name='WRT_n5konto_wrefPodmiotRozrach_6')
	alter table n5konto drop constraint WRT_n5konto_wrefPodmiotRozrach_6
go
if exists (select * from sysobjects where name='ENUM_n5konto_eAnalit_8')
	alter table n5konto drop constraint ENUM_n5konto_eAnalit_8
go
if exists (select * from sysobjects where name='ENUM_n5konto_eBilans_9')
	alter table n5konto drop constraint ENUM_n5konto_eBilans_9
go
if exists (select * from sysobjects where name='ENUM_n5konto_eAktywne_10')
	alter table n5konto drop constraint ENUM_n5konto_eAktywne_10
go
if exists (select * from sysobjects where name='FK_n5dekret_n5konto_2')
	alter table n5dekret drop constraint FK_n5dekret_n5konto_2
go
if exists (select * from sysobjects where name='ENUM_n5dekret_eTyp_7')
	alter table n5dekret drop constraint ENUM_n5dekret_eTyp_7
go
if exists (select * from sysobjects where name='ENUM_n5dekret_eStatus_8')
	alter table n5dekret drop constraint ENUM_n5dekret_eStatus_8
go
if exists (select * from sysobjects where name='ENUM_n5dowodksieg_eTyp_7')
	alter table n5dowodksieg drop constraint ENUM_n5dowodksieg_eTyp_7
go
if exists (select * from sysobjects where name='ENUM_n5dowodksieg_eStatus_8')
	alter table n5dowodksieg drop constraint ENUM_n5dowodksieg_eStatus_8
go
if exists (select * from sysobjects where name='FK_n5dowodksieg_n5uzytkownik_10')
	alter table n5dowodksieg drop constraint FK_n5dowodksieg_n5uzytkownik_10
go
if exists (select * from sysobjects where name='FK_n5dowodksieg_n5rejestrdok_11')
	alter table n5dowodksieg drop constraint FK_n5dowodksieg_n5rejestrdok_11
go
if exists (select * from sysobjects where name='WRT_n5dowodksieg_wrefDokZrod_12')
	alter table n5dowodksieg drop constraint WRT_n5dowodksieg_wrefDokZrod_12
go
if exists (select * from sysobjects where name='WRT_n5platnosc_wrefPodmiot_3')
	alter table n5platnosc drop constraint WRT_n5platnosc_wrefPodmiot_3
go
if exists (select * from sysobjects where name='FK_n5platnosc_n5uzytkownik_6')
	alter table n5platnosc drop constraint FK_n5platnosc_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5platnosc_n5rejestrdok_7')
	alter table n5platnosc drop constraint FK_n5platnosc_n5rejestrdok_7
go
if exists (select * from sysobjects where name='FK_n5platnosc_n5jednostka_15')
	alter table n5platnosc drop constraint FK_n5platnosc_n5jednostka_15
go
if exists (select * from sysobjects where name='ENUM_n5platnosc_eStatus_20')
	alter table n5platnosc drop constraint ENUM_n5platnosc_eStatus_20
go
if exists (select * from sysobjects where name='FK_n5transakcja_n5jednostka_3')
	alter table n5transakcja drop constraint FK_n5transakcja_n5jednostka_3
go
if exists (select * from sysobjects where name='WRT_n5transakcja_wrefPodmiot_4')
	alter table n5transakcja drop constraint WRT_n5transakcja_wrefPodmiot_4
go
if exists (select * from sysobjects where name='ENUM_n5transakcja_eTyp_10')
	alter table n5transakcja drop constraint ENUM_n5transakcja_eTyp_10
go
if exists (select * from sysobjects where name='ENUM_n5transakcja_eStatus_11')
	alter table n5transakcja drop constraint ENUM_n5transakcja_eStatus_11
go
if exists (select * from sysobjects where name='ENUM_n5transakcja_eTypOdset_14')
	alter table n5transakcja drop constraint ENUM_n5transakcja_eTypOdset_14
go
if exists (select * from sysobjects where name='FK_n5schematdekr_n5rejestrdok_3')
	alter table n5schematdekr drop constraint FK_n5schematdekr_n5rejestrdok_3
go
if exists (select * from sysobjects where name='FK_n5schematdekr_n5rejestrdok_4')
	alter table n5schematdekr drop constraint FK_n5schematdekr_n5rejestrdok_4
go
if exists (select * from sysobjects where name='ENUM_n5schematdekr_eAktywny_7')
	alter table n5schematdekr drop constraint ENUM_n5schematdekr_eAktywny_7
go
if exists (select * from sysobjects where name='FK_n5magazyn_n5jednostka_3')
	alter table n5magazyn drop constraint FK_n5magazyn_n5jednostka_3
go
if exists (select * from sysobjects where name='ENUM_n5magazyn_eTyp_4')
	alter table n5magazyn drop constraint ENUM_n5magazyn_eTyp_4
go
if exists (select * from sysobjects where name='FK_n5magazyn_n5jedn_org_5')
	alter table n5magazyn drop constraint FK_n5magazyn_n5jedn_org_5
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_n5produkt_2')
	alter table n5pozdokmag drop constraint FK_n5pozdokmag_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_n5opakowanie_produktu_3')
	alter table n5pozdokmag drop constraint FK_n5pozdokmag_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_n5jednostka_7')
	alter table n5pozdokmag drop constraint FK_n5pozdokmag_n5jednostka_7
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_n5jednostka_9')
	alter table n5pozdokmag drop constraint FK_n5pozdokmag_n5jednostka_9
go
if exists (select * from sysobjects where name='FK_n5dokmag_n5uzytkownik_10')
	alter table n5dokmag drop constraint FK_n5dokmag_n5uzytkownik_10
go
if exists (select * from sysobjects where name='FK_n5dokmag_n5rejestrdok_13')
	alter table n5dokmag drop constraint FK_n5dokmag_n5rejestrdok_13
go
if exists (select * from sysobjects where name='WRT_n5dokmag_wrefDokHandl_21')
	alter table n5dokmag drop constraint WRT_n5dokmag_wrefDokHandl_21
go
if exists (select * from sysobjects where name='FK_n5zadaniedw_n5wykonawca_2')
	alter table n5zadaniedw drop constraint FK_n5zadaniedw_n5wykonawca_2
go
if exists (select * from sysobjects where name='ENUM_n5sposplat_eTyp_4')
	alter table n5sposplat drop constraint ENUM_n5sposplat_eTyp_4
go
if exists (select * from sysobjects where name='FK_n5kurswalut_n5jednostka_2')
	alter table n5kurswalut drop constraint FK_n5kurswalut_n5jednostka_2
go
if exists (select * from sysobjects where name='FK_n5kurswalut_n5jednostka_3')
	alter table n5kurswalut drop constraint FK_n5kurswalut_n5jednostka_3
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5sposplat_7')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5sposplat_7
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5klient_8')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5klient_8
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5uzytkownik_11')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5uzytkownik_11
go
if exists (select * from sysobjects where name='ENUM_n5zamowienie_eNettoBrutto_13')
	alter table n5zamowienie drop constraint ENUM_n5zamowienie_eNettoBrutto_13
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5rejestrdok_19')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5rejestrdok_19
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5jednostka_24')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5jednostka_24
go
if exists (select * from sysobjects where name='FK_n5pozzamowienie_n5produkt_2')
	alter table n5pozzamowienie drop constraint FK_n5pozzamowienie_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozzamowienie_n5opakowanie_produktu_4')
	alter table n5pozzamowienie drop constraint FK_n5pozzamowienie_n5opakowanie_produktu_4
go
if exists (select * from sysobjects where name='ENUM_n5pozzamowienie_eVAT_8')
	alter table n5pozzamowienie drop constraint ENUM_n5pozzamowienie_eVAT_8
go
if exists (select * from sysobjects where name='FK_n5pozzakup_n5produkt_2')
	alter table n5pozzakup drop constraint FK_n5pozzakup_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozzakup_n5opakowanie_produktu_4')
	alter table n5pozzakup drop constraint FK_n5pozzakup_n5opakowanie_produktu_4
go
if exists (select * from sysobjects where name='ENUM_n5pozzakup_eVAT_5')
	alter table n5pozzakup drop constraint ENUM_n5pozzakup_eVAT_5
go
if exists (select * from sysobjects where name='FK_n5zakup_n5sposplat_8')
	alter table n5zakup drop constraint FK_n5zakup_n5sposplat_8
go
if exists (select * from sysobjects where name='FK_n5zakup_n5klient_9')
	alter table n5zakup drop constraint FK_n5zakup_n5klient_9
go
if exists (select * from sysobjects where name='FK_n5zakup_n5uzytkownik_11')
	alter table n5zakup drop constraint FK_n5zakup_n5uzytkownik_11
go
if exists (select * from sysobjects where name='FK_n5zakup_n5rejestrdok_18')
	alter table n5zakup drop constraint FK_n5zakup_n5rejestrdok_18
go
if exists (select * from sysobjects where name='FK_n5zakup_n5jednostka_48')
	alter table n5zakup drop constraint FK_n5zakup_n5jednostka_48
go
if exists (select * from sysobjects where name='ENUM_n5zakup_eZwOpSprz_49')
	alter table n5zakup drop constraint ENUM_n5zakup_eZwOpSprz_49
go
if exists (select * from sysobjects where name='ENUM_n5zakup_eTypZakup_50')
	alter table n5zakup drop constraint ENUM_n5zakup_eTypZakup_50
go
if exists (select * from sysobjects where name='FK_n5rozlvat_n5uzytkownik_52')
	alter table n5rozlvat drop constraint FK_n5rozlvat_n5uzytkownik_52
go
if exists (select * from sysobjects where name='FK_n5srtrw_n5grupasrtrw_6')
	alter table n5srtrw drop constraint FK_n5srtrw_n5grupasrtrw_6
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eRodzaj_8')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eRodzaj_8
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eMetAmPod_19')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eMetAmPod_19
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eMetAmBil_20')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eMetAmBil_20
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eStatus_21')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eStatus_21
go
if exists (select * from sysobjects where name='ENUM_n5opmag_eTypPow_16')
	alter table n5opmag drop constraint ENUM_n5opmag_eTypPow_16
go
if exists (select * from sysobjects where name='ENUM_n5koropmag_eTypPow_16')
	alter table n5koropmag drop constraint ENUM_n5koropmag_eTypPow_16
go
if exists (select * from sysobjects where name='FK_n5stanmag_n5magazyn_2')
	alter table n5stanmag drop constraint FK_n5stanmag_n5magazyn_2
go
if exists (select * from sysobjects where name='FK_n5stanmag_n5produkt_3')
	alter table n5stanmag drop constraint FK_n5stanmag_n5produkt_3
go
if exists (select * from sysobjects where name='FK_n5stanmag_n5opakowanie_produktu_4')
	alter table n5stanmag drop constraint FK_n5stanmag_n5opakowanie_produktu_4
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_n5produkt_2')
	alter table n5pozrecepta drop constraint FK_n5pozrecepta_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_n5opakowanie_produktu_3')
	alter table n5pozrecepta drop constraint FK_n5pozrecepta_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5recepta_n5produkt_5')
	alter table n5recepta drop constraint FK_n5recepta_n5produkt_5
go
if exists (select * from sysobjects where name='FK_n5recepta_n5opakowanie_produktu_6')
	alter table n5recepta drop constraint FK_n5recepta_n5opakowanie_produktu_6
go
if exists (select * from sysobjects where name='FK_n5pozzlecprod_n5produkt_2')
	alter table n5pozzlecprod drop constraint FK_n5pozzlecprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozzlecprod_n5opakowanie_produktu_3')
	alter table n5pozzlecprod drop constraint FK_n5pozzlecprod_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5pozzlecprod_n5recepta_4')
	alter table n5pozzlecprod drop constraint FK_n5pozzlecprod_n5recepta_4
go
if exists (select * from sysobjects where name='FK_n5zlecprod_n5uzytkownik_4')
	alter table n5zlecprod drop constraint FK_n5zlecprod_n5uzytkownik_4
go
if exists (select * from sysobjects where name='FK_n5zlecprod_n5rejestrdok_6')
	alter table n5zlecprod drop constraint FK_n5zlecprod_n5rejestrdok_6
go
if exists (select * from sysobjects where name='ENUM_n5eventlog_eTyp_2')
	alter table n5eventlog drop constraint ENUM_n5eventlog_eTyp_2
go
if exists (select * from sysobjects where name='FK_n5eventlog_n5uzytkownik_5')
	alter table n5eventlog drop constraint FK_n5eventlog_n5uzytkownik_5
go
if exists (select * from sysobjects where name='WRT_n5polrab_wpProdGrupa_2')
	alter table n5polrab drop constraint WRT_n5polrab_wpProdGrupa_2
go
if exists (select * from sysobjects where name='WRT_n5polrab_wpKlientGrupa_4')
	alter table n5polrab drop constraint WRT_n5polrab_wpKlientGrupa_4
go
if exists (select * from sysobjects where name='ENUM_n5polrab_eTyp_10')
	alter table n5polrab drop constraint ENUM_n5polrab_eTyp_10
go
if exists (select * from sysobjects where name='FK_n5plstawka_n5jednostka_7')
	alter table n5plstawka drop constraint FK_n5plstawka_n5jednostka_7
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5uzytkownik_6')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5rejestrdok_7')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5rejestrdok_7
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5pllistaplac_10')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5pllistaplac_10
go
if exists (select * from sysobjects where name='FK_n5plsklnal_n5plschematnal_2')
	alter table n5plsklnal drop constraint FK_n5plsklnal_n5plschematnal_2
go
if exists (select * from sysobjects where name='ENUM_n5plsubkonto_eAktywne_5')
	alter table n5plsubkonto drop constraint ENUM_n5plsubkonto_eAktywne_5
go
if exists (select * from sysobjects where name='FK_n5plsubkonto_n5jednostka_6')
	alter table n5plsubkonto drop constraint FK_n5plsubkonto_n5jednostka_6
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5pracownik_2')
	alter table n5pldekret drop constraint FK_n5pldekret_n5pracownik_2
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5plsubkonto_3')
	alter table n5pldekret drop constraint FK_n5pldekret_n5plsubkonto_3
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5pllistaplac_7')
	alter table n5pldekret drop constraint FK_n5pldekret_n5pllistaplac_7
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5plnaliczenie_8')
	alter table n5pldekret drop constraint FK_n5pldekret_n5plnaliczenie_8
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5plschematnal_9')
	alter table n5pldekret drop constraint FK_n5pldekret_n5plschematnal_9
go
if exists (select * from sysobjects where name='WRT_n5pldekret_wrefDokument_10')
	alter table n5pldekret drop constraint WRT_n5pldekret_wrefDokument_10
go
if exists (select * from sysobjects where name='FK_n5plumowa_n5uzytkownik_6')
	alter table n5plumowa drop constraint FK_n5plumowa_n5uzytkownik_6
go
if exists (select * from sysobjects where name='ENUM_n5plumowa_eTypUmowy_7')
	alter table n5plumowa drop constraint ENUM_n5plumowa_eTypUmowy_7
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5uzytkownik_6')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5plumowa_7')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5plumowa_7
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5plschematnal_8')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5plschematnal_8
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5uzytkownik_6')
	alter table n5plnieob drop constraint FK_n5plnieob_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5plumowa_7')
	alter table n5plnieob drop constraint FK_n5plnieob_n5plumowa_7
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5plschematnal_8')
	alter table n5plnieob drop constraint FK_n5plnieob_n5plschematnal_8
go
if exists (select * from sysobjects where name='ENUM_n5plnieob_eTyp_9')
	alter table n5plnieob drop constraint ENUM_n5plnieob_eTyp_9
go
if exists (select * from sysobjects where name='FK_n5rozlcit_n5uzytkownik_34')
	alter table n5rozlcit drop constraint FK_n5rozlcit_n5uzytkownik_34
go
if exists (select * from sysobjects where name='FK_n5rozlcit_n5zadanie_35')
	alter table n5rozlcit drop constraint FK_n5rozlcit_n5zadanie_35
go
if exists (select * from sysobjects where name='ENUM_n5rule_eSignificance_5')
	alter table n5rule drop constraint ENUM_n5rule_eSignificance_5
go
if exists (select * from sysobjects where name='FK_n5pozrealprod_n5produkt_2')
	alter table n5pozrealprod drop constraint FK_n5pozrealprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozrealprod_n5opakowanie_produktu_3')
	alter table n5pozrealprod drop constraint FK_n5pozrealprod_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5pozrealprod_n5jednostka_5')
	alter table n5pozrealprod drop constraint FK_n5pozrealprod_n5jednostka_5
go
if exists (select * from sysobjects where name='FK_n5pozrealprod_n5jednostka_7')
	alter table n5pozrealprod drop constraint FK_n5pozrealprod_n5jednostka_7
go
if exists (select * from sysobjects where name='FK_n5realprod_n5produkt_4')
	alter table n5realprod drop constraint FK_n5realprod_n5produkt_4
go
if exists (select * from sysobjects where name='FK_n5realprod_n5opakowanie_produktu_5')
	alter table n5realprod drop constraint FK_n5realprod_n5opakowanie_produktu_5
go
if exists (select * from sysobjects where name='FK_n5realprod_n5uzytkownik_9')
	alter table n5realprod drop constraint FK_n5realprod_n5uzytkownik_9
go
if exists (select * from sysobjects where name='FK_n5realprod_n5rejestrdok_11')
	alter table n5realprod drop constraint FK_n5realprod_n5rejestrdok_11
go
if exists (select * from sysobjects where name='FK_n5konto_budzet_n5konto_2')
	alter table n5konto_budzet drop constraint FK_n5konto_budzet_n5konto_2
go
if exists (select * from sysobjects where name='FK_n5konto_budzet_n5budzet_3')
	alter table n5konto_budzet drop constraint FK_n5konto_budzet_n5budzet_3
go
if exists (select * from sysobjects where name='ENUM_n5konto_budzet_eOdniesienie_5')
	alter table n5konto_budzet drop constraint ENUM_n5konto_budzet_eOdniesienie_5
go
if exists (select * from sysobjects where name='ENUM_n5bwinfo_eStatus_6')
	alter table n5bwinfo drop constraint ENUM_n5bwinfo_eStatus_6
go
if exists (select * from sysobjects where name='FK_n5bwinfo_n5bwinfo_kat_7')
	alter table n5bwinfo drop constraint FK_n5bwinfo_n5bwinfo_kat_7
go
if exists (select * from sysobjects where name='FK_n5bwinfo_n5uzytkownik_15')
	alter table n5bwinfo drop constraint FK_n5bwinfo_n5uzytkownik_15
go
if exists (select * from sysobjects where name='WRT_n5bwinfo_produkt_wpProdGrupa_2')
	alter table n5bwinfo_produkt drop constraint WRT_n5bwinfo_produkt_wpProdGrupa_2
go
if exists (select * from sysobjects where name='WRT_n5bwinfo_zal_wrefZal_2')
	alter table n5bwinfo_zal drop constraint WRT_n5bwinfo_zal_wrefZal_2
go
if exists (select * from sysobjects where name='FK_n5poznotaods_n5transakcja_2')
	alter table n5poznotaods drop constraint FK_n5poznotaods_n5transakcja_2
go
if exists (select * from sysobjects where name='FK_n5notaods_n5klient_4')
	alter table n5notaods drop constraint FK_n5notaods_n5klient_4
go
if exists (select * from sysobjects where name='FK_n5notaods_n5uzytkownik_5')
	alter table n5notaods drop constraint FK_n5notaods_n5uzytkownik_5
go
if exists (select * from sysobjects where name='FK_n5notaods_n5rejestrdok_9')
	alter table n5notaods drop constraint FK_n5notaods_n5rejestrdok_9
go
if exists (select * from sysobjects where name='FK_n5opsrtrw_n5srtrw_2')
	alter table n5opsrtrw drop constraint FK_n5opsrtrw_n5srtrw_2
go
if exists (select * from sysobjects where name='ENUM_n5opsrtrw_eRodzaj_5')
	alter table n5opsrtrw drop constraint ENUM_n5opsrtrw_eRodzaj_5
go
if exists (select * from sysobjects where name='FK_n5opsrtrw_n5uzytkownik_16')
	alter table n5opsrtrw drop constraint FK_n5opsrtrw_n5uzytkownik_16
go
if exists (select * from sysobjects where name='WRT_n5opsrtrw_wrefDokument_18')
	alter table n5opsrtrw drop constraint WRT_n5opsrtrw_wrefDokument_18
go
if exists (select * from sysobjects where name='FK_n5opsrtrw_n5rejestrdok_19')
	alter table n5opsrtrw drop constraint FK_n5opsrtrw_n5rejestrdok_19
go
if exists (select * from sysobjects where name='ENUM_n5plwzorlp_eTypUmowy_3')
	alter table n5plwzorlp drop constraint ENUM_n5plwzorlp_eTypUmowy_3
go
if exists (select * from sysobjects where name='ENUM_n5plwzorlp_eAktywny_7')
	alter table n5plwzorlp drop constraint ENUM_n5plwzorlp_eAktywny_7
go
if exists (select * from sysobjects where name='ENUM_n5plkalcp_eAktywny_3')
	alter table n5plkalcp drop constraint ENUM_n5plkalcp_eAktywny_3
go
if exists (select * from sysobjects where name='ENUM_n5plpozkalcp_eTypOkresu_7')
	alter table n5plpozkalcp drop constraint ENUM_n5plpozkalcp_eTypOkresu_7
go
if exists (select * from sysobjects where name='FK_n5plsklumowy_n5plschematnal_2')
	alter table n5plsklumowy drop constraint FK_n5plsklumowy_n5plschematnal_2
go
if exists (select * from sysobjects where name='WRT_n5plsklnalzrod_wrefDokument_2')
	alter table n5plsklnalzrod drop constraint WRT_n5plsklnalzrod_wrefDokument_2
go
if exists (select * from sysobjects where name='FK_n5sod_n5sodgroup_3')
	alter table n5sod drop constraint FK_n5sod_n5sodgroup_3
go
if exists (select * from sysobjects where name='FK_n5securityobj_n5sod_2')
	alter table n5securityobj drop constraint FK_n5securityobj_n5sod_2
go
if exists (select * from sysobjects where name='FK_n5securityobj_n5uzytkownik_3')
	alter table n5securityobj drop constraint FK_n5securityobj_n5uzytkownik_3
go
if exists (select * from sysobjects where name='ENUM_n5dpc_ePubType_3')
	alter table n5dpc drop constraint ENUM_n5dpc_ePubType_3
go
if exists (select * from sysobjects where name='ENUM_n5dpc_eChannel_4')
	alter table n5dpc drop constraint ENUM_n5dpc_eChannel_4
go
if exists (select * from sysobjects where name='ENUM_n5dpc_eFormat_6')
	alter table n5dpc drop constraint ENUM_n5dpc_eFormat_6
go
if exists (select * from sysobjects where name='FK_n5userprof_n5uzytkownik_4')
	alter table n5userprof drop constraint FK_n5userprof_n5uzytkownik_4
go
if exists (select * from sysobjects where name='FK_n5userfile_n5uzytkownik_3')
	alter table n5userfile drop constraint FK_n5userfile_n5uzytkownik_3
go


--INJECT A here -- 
-- creating database tables
if exists (select * from sysobjects where name='n5wojewodztwo')
	drop table n5wojewodztwo
go

create table n5wojewodztwo
(
	IdObj integer not null constraint PK_n5wojewodztwo_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5region')
	drop table n5region
go

create table n5region
(
	IdObj integer not null constraint PK_n5region_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5jednostka')
	drop table n5jednostka
go

create table n5jednostka
(
	IdObj integer not null constraint PK_n5jednostka_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(32) not null,
	strSkrot varchar(4) not null,
	nDokladnosc integer not null,
	eTyp integer not null,
	strNazwaMiedzynarodowa varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5kraj')
	drop table n5kraj
go

create table n5kraj
(
	IdObj integer not null constraint PK_n5kraj_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	strSkrot varchar(20) not null,
	pWaluta integer not null
)
go

if exists (select * from sysobjects where name='n5bank')
	drop table n5bank
go

create table n5bank
(
	IdObj integer not null constraint PK_n5bank_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strOddzial varchar(128) not null,
	strKodRach varchar(32) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null
)
go

if exists (select * from sysobjects where name='n5instytucja')
	drop table n5instytucja
go

create table n5instytucja
(
	IdObj integer not null constraint PK_n5instytucja_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	pTyp integer not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRachunek1 varchar(32) not null,
	strPrzeznaczenie1 varchar(64) not null,
	pBank1 integer not null,
	strRachunek2 varchar(32) not null,
	strPrzeznaczenie2 varchar(64) not null,
	pBank2 integer not null,
	strRachunek3 varchar(32) not null,
	strPrzeznaczenie3 varchar(64) not null,
	pBank3 integer not null
)
go

if exists (select * from sysobjects where name='n5licencja')
	drop table n5licencja
go

create table n5licencja
(
	IdObj integer not null constraint PK_n5licencja_IdObj primary key clustered,
	VersionId integer not null,
	strKod varchar(8) not null,
	strIdUser varchar(20) not null,
	dDataWazn datetime not null,
	nStanowiska integer not null,
	strKontrola varchar(512) not null,
	strLogin varchar(32) not null,
	strHaslo varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5uzytkownik')
	drop table n5uzytkownik
go

create table n5uzytkownik
(
	IdObj integer not null constraint PK_n5uzytkownik_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	strLogin varchar(20) not null,
	strHaslo varchar(20) not null,
	strMail varchar(64) not null,
	strTelefon varchar(20) not null,
	eAktywny integer not null,
	pWykonawca integer not null
)
go

if exists (select * from sysobjects where name='n5klient')
	drop table n5klient
go

create table n5klient
(
	IdObj integer not null constraint PK_n5klient_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strIndeks varchar(32) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strTel4 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRejestr varchar(64) not null,
	strSad varchar(128) not null,
	strNIP varchar(20) not null,
	strREGON varchar(20) not null,
	pBranza integer not null,
	eTypDT integer not null,
	strNrDokTozsamosci varchar(20) not null,
	strRachunek1 varchar(32) not null,
	strPrzeznaczenie1 varchar(64) not null,
	pBank1 integer not null,
	strRachunek2 varchar(32) not null,
	strPrzeznaczenie2 varchar(64) not null,
	pBank2 integer not null,
	strRachunek3 varchar(32) not null,
	strPrzeznaczenie3 varchar(64) not null,
	pBank3 integer not null,
	nLiczbaPracownikow integer not null,
	eAktywny integer not null,
	eKlasaKlienta integer not null,
	pWaluta integer not null,
	strUwagi varchar(255) not null,
	strUpodobania varchar(255) not null,
	strCecha1 varchar(128) not null,
	strCecha2 varchar(128) not null,
	strCecha3 varchar(128) not null,
	strNazwisko varchar(128) not null,
	strImie varchar(32) not null,
	dDataUr datetime not null,
	strMiejsceUr varchar(32) not null,
	strPESEL varchar(20) not null,
	ePlec integer not null,
	nWiek integer not null,
	strWydzial varchar(128) not null,
	pPracownik integer not null,
	pGrupaKlient integer not null,
	ePrywat integer not null,
	strUlicaSDB varchar(64) not null,
	strNrDomuSDB varchar(8) not null,
	strNrLokaluSDB varchar(8) not null,
	strKodSDB varchar(8) not null,
	strPocztaSDB varchar(64) not null,
	pMiejscowoscSDB integer not null,
	curSzerGeogrSDB decimal(12,2) not null,
	curDlugGeogrSDB decimal(12,2) not null,
	eWiarFin integer not null,
	curLimitKred decimal(12,2) not null,
	pWalutaLimitu integer not null,
	strHaslo varchar(32) not null,
	curObroty decimal(12,2) not null,
	nOcena integer not null,
	dDataOceny datetime not null,
	pSposobPlatnosci integer not null
)
go

if exists (select * from sysobjects where name='n5pracownik')
	drop table n5pracownik
go

create table n5pracownik
(
	IdObj integer not null constraint PK_n5pracownik_IdObj primary key clustered,
	VersionId integer not null,
	strNazwisko varchar(32) not null,
	strImie varchar(32) not null,
	strImie2 varchar(32) not null,
	dDataUr datetime not null,
	strMiejsceUr varchar(32) not null,
	strPESEL varchar(20) not null,
	strNIP varchar(20) not null,
	ePlec integer not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strTel4 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRachunek1 varchar(32) not null,
	pBank1 integer not null,
	eAktywny integer not null,
	dDataZatrudnienia datetime not null,
	dDataZwolnienia datetime not null,
	strStanowisko varchar(64) not null,
	eTypDT integer not null,
	strNrDokTozsamosci varchar(20) not null,
	strEmail2 varchar(64) not null,
	pJednostkaOrg integer not null,
	pUrzadSkarbowy integer not null,
	-- [virtual] fZdjecie
)
go

if exists (select * from sysobjects where name='n5firma')
	drop table n5firma
go

create table n5firma
(
	IdObj integer not null constraint PK_n5firma_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strFax varchar(20) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRejestr varchar(64) not null,
	strSad varchar(128) not null,
	strWydzial varchar(128) not null,
	eForma integer not null,
	strNIP varchar(20) not null,
	strREGON varchar(20) not null,
	strEKD varchar(20) not null,
	strRachunek1 varchar(32) not null,
	pBank1 integer not null,
	strPrzeznaczenie1 varchar(64) not null,
	strRachunek2 varchar(32) not null,
	pBank2 integer not null,
	strPrzeznaczenie2 varchar(64) not null,
	strRachunek3 varchar(32) not null,
	strPrzeznaczenie3 varchar(64) not null,
	pWaluta integer not null,
	pBank3 integer not null,
	-- [virtual] fLogo,
	pUrzadSkarbowyVAT integer not null,
	pUrzadSkarbowyPD integer not null,
	pZUS integer not null,
	pMainJO integer not null
)
go

if exists (select * from sysobjects where name='n5miejscowosc')
	drop table n5miejscowosc
go

create table n5miejscowosc
(
	IdObj integer not null constraint PK_n5miejscowosc_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	eWielkosc integer not null,
	pWojewodztwo integer not null,
	pRegion integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null
)
go

if exists (select * from sysobjects where name='n5klient_pracownik')
	drop table n5klient_pracownik
go

create table n5klient_pracownik
(
	IdObj integer not null constraint PK_n5klient_pracownik_IdObj primary key clustered,
	VersionId integer not null,
	strNazwisko varchar(32) not null,
	strImie varchar(32) not null,
	strImie2 varchar(32) not null,
	ePlec integer not null,
	nWiek integer not null,
	strTytul varchar(32) not null,
	eStanCywilny integer not null,
	strTel1 varchar(20) not null,
	pKlient integer not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strTel4 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	pJednOrgKlienta integer not null,
	strUwagi varchar(255) not null,
	strUpodobania varchar(255) not null,
	pPracownik integer not null,
	strStanowisko varchar(64) not null,
	eAktywny integer not null,
	strEmail2 varchar(64) not null
)
go

if exists (select * from sysobjects where name='n5jedn_org')
	drop table n5jedn_org
go

create table n5jedn_org
(
	IdObj integer not null constraint PK_n5jedn_org_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strDzial varchar(255) not null,
	strWydzial varchar(255) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRachunek1 varchar(32) not null,
	strPrzeznaczenie1 varchar(64) not null,
	pBank1 integer not null,
	strRachunek2 varchar(32) not null,
	strPrzeznaczenie2 varchar(64) not null,
	pBank2 integer not null,
	strRachunek3 varchar(32) not null,
	strPrzeznaczenie3 varchar(64) not null,
	pBank3 integer not null,
	pPracownik integer not null,
	p_Jend_Org_Nadrzedna integer not null
)
go

if exists (select * from sysobjects where name='n5_klient_jedn_org')
	drop table n5_klient_jedn_org
go

create table n5_klient_jedn_org
(
	IdObj integer not null constraint PK_n5_klient_jedn_org_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	curSzerGeogr decimal(12,2) not null,
	curDlugGeogr decimal(12,2) not null,
	strTel1 varchar(20) not null,
	strTel2 varchar(20) not null,
	strTel3 varchar(20) not null,
	strFax varchar(20) not null,
	strEmail varchar(64) not null,
	strWWW varchar(64) not null,
	strRachunek1 varchar(32) not null,
	strPrzeznaczenie1 varchar(64) not null,
	pBank1 integer not null,
	strRachunek2 varchar(32) not null,
	strPrzeznaczenie2 varchar(64) not null,
	pBank2 integer not null,
	strRachunek3 varchar(32) not null,
	strPrzeznaczenie3 varchar(64) not null,
	pBank3 integer not null,
	pKlient integer not null,
	p_Klient_JO_Nadrzedna integer not null,
	pKlientPracownik integer not null
)
go

if exists (select * from sysobjects where name='n5typdokumentu')
	drop table n5typdokumentu
go

create table n5typdokumentu
(
	IdObj integer not null constraint PK_n5typdokumentu_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pTypNadrzedny integer not null,
	eRodzaj integer not null,
	nInternalID integer not null
)
go

if exists (select * from sysobjects where name='n5grupaproduktow')
	drop table n5grupaproduktow
go

create table n5grupaproduktow
(
	IdObj integer not null constraint PK_n5grupaproduktow_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	pGrupaNadrzedna integer not null
)
go

if exists (select * from sysobjects where name='n5dokument')
	drop table n5dokument
go

create table n5dokument
(
	IdObj integer not null constraint PK_n5dokument_IdObj primary key clustered,
	VersionId integer not null,
	strNumDok varchar(32) not null,
	strNumDokObcy varchar(64) not null,
	strTematDokum varchar(128) not null,
	pTypDokumentu integer not null,
	dDataWeWy datetime not null,
	dDataRejestracji datetime not null,
	wpNadawca integer not null,
	wpNadawca_wrt integer not null,
	wpAdresat integer not null,
	wpAdresat_wrt integer not null,
	strStreszczenie varchar(1024) not null,
	nForma integer not null,
	nLiczbaStron integer not null,
	strLokalizacja varchar(128) not null,
	-- [virtual] fPlik,
	strFileName varchar(1024) not null,
	strCheckoutFileName varchar(1024) not null,
	pUzytkWypoz integer not null,
	strCecha1 varchar(128) not null,
	strCecha2 varchar(128) not null,
	strCecha3 varchar(128) not null,
	nIsSecurity integer not null,
	pReplaces integer not null,
	pReplaced integer not null,
	-- [virtual] listLinks
)
go

if exists (select * from sysobjects where name='n5grupaklient')
	drop table n5grupaklient
go

create table n5grupaklient
(
	IdObj integer not null constraint PK_n5grupaklient_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pGrupaNadrzedna integer not null,
	curLimitKred decimal(12,2) not null,
	pWalutaLimitu integer not null
)
go

if exists (select * from sysobjects where name='n5zadanie')
	drop table n5zadanie
go

create table n5zadanie
(
	IdObj integer not null constraint PK_n5zadanie_IdObj primary key clustered,
	VersionId integer not null,
	nStatus integer not null,
	dDataZlec datetime not null,
	tCzasZlec integer not null,
	pZlecajacy integer not null,
	ePriorytet integer not null,
	eTypterminRozp integer not null,
	dDataTerminRozp datetime not null,
	tCzasTerminRozp integer not null,
	eTypterminZak integer not null,
	strTemat varchar(128) not null,
	strOpis varchar(1024) not null,
	nNaklad integer not null,
	pTypDzialania integer not null,
	pProcedura integer not null,
	wrefSzczegoly integer not null,
	wrefSzczegoly_wrt integer not null,
	pNadZadanie integer not null,
	pPopZadanie integer not null,
	pWykonawca integer not null,
	dDataPow datetime not null,
	tCzasPow integer not null,
	dDataRozp datetime not null,
	tCzasRozp integer not null,
	nZaawansowanie integer not null,
	dDataZakon datetime not null,
	tCzasZakon integer not null,
	strUwagi varchar(1024) not null,
	dDataZamk datetime not null,
	tCzasZamk integer not null,
	strCecha1 varchar(128) not null,
	strCecha2 varchar(128) not null,
	strCecha3 varchar(128) not null,
	dDataTerminZak datetime not null,
	tCzasTerminZak integer not null,
	pKlient integer not null,
	-- [virtual] listZalaczniki,
	pSchematDekretacji integer not null,
	pDowKsieg integer not null,
	dDataPrzyp datetime not null,
	tCzasPrzyp integer not null,
	nIsSecurity integer not null,
	-- [virtual] listZadanieDW,
	pKlientPracownik integer not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5procedura')
	drop table n5procedura
go

create table n5procedura
(
	IdObj integer not null constraint PK_n5procedura_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	strOpis varchar(1024) not null,
	nModule integer not null,
	nInternalID integer not null
)
go

if exists (select * from sysobjects where name='n5pozplatnosc')
	drop table n5pozplatnosc
go

create table n5pozplatnosc
(
	IdObj integer not null constraint PK_n5pozplatnosc_IdObj primary key clustered,
	VersionId integer not null,
	curPozKwotaPodm decimal(12,2) not null,
	curPozKwotaEwid decimal(12,2) not null,
	curPozKwotaTrans decimal(12,2) not null,
	curPozKursPodm decimal(14,4) not null,
	curPozKursEwid decimal(14,4) not null,
	pTransakcja integer not null
)
go

if exists (select * from sysobjects where name='n5wykonawca')
	drop table n5wykonawca
go

create table n5wykonawca
(
	IdObj integer not null constraint PK_n5wykonawca_IdObj primary key clustered,
	VersionId integer not null,
	strIndeks varchar(64) not null,
	wrefObiekt integer not null,
	wrefObiekt_wrt integer not null,
	strMetPow varchar(8) not null
)
go

if exists (select * from sysobjects where name='choicelistitem')
	drop table choicelistitem
go

create table choicelistitem
(
	IdObj integer not null constraint PK_choicelistitem_IdObj primary key clustered,
	VersionId integer not null,
	IdElement integer not null
)
go

if exists (select * from sysobjects where name='choicelist')
	drop table choicelist
go

create table choicelist
(
	IdObj integer not null constraint PK_choicelist_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	nTypeId integer not null,
	edynamic integer not null,
	-- [virtual] listElement,
	nIsSecurity integer not null
)
go

if exists (select * from sysobjects where name='n5zadaniezal')
	drop table n5zadaniezal
go

create table n5zadaniezal
(
	IdObj integer not null constraint PK_n5zadaniezal_IdObj primary key clustered,
	VersionId integer not null,
	wrefZal integer not null,
	wrefZal_wrt integer not null
)
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem')
	drop table n5WizzardEmailDokumElem
go

create table n5WizzardEmailDokumElem
(
	IdObj integer not null constraint PK_n5WizzardEmailDokumElem_IdObj primary key clustered,
	VersionId integer not null,
	pDokument integer not null
)
go

if exists (select * from sysobjects where name='n5WizzardEmail')
	drop table n5WizzardEmail
go

create table n5WizzardEmail
(
	IdObj integer not null constraint PK_n5WizzardEmail_IdObj primary key clustered,
	VersionId integer not null,
	pChoiceList integer not null,
	-- [virtual] listDokumenty,
	cZarejestruj varchar(1) not null,
	cWysylkaEmail varchar(1) not null,
	cWysylkaFax varchar(1) not null,
	cWysylkaWydruk varchar(1) not null,
	cWysylkaEmailFax varchar(1) not null,
	cWysylkaEmailWydruk varchar(32) not null,
	strTytul varchar(512) not null,
	strTresc varchar(1024) not null,
	cSzablon varchar(1) not null
)
go

if exists (select * from sysobjects where name='n5SendEmail')
	drop table n5SendEmail
go

create table n5SendEmail
(
	IdObj integer not null constraint PK_n5SendEmail_IdObj primary key clustered,
	VersionId integer not null,
	wpNadawca integer not null,
	wpNadawca_wrt integer not null,
	-- [virtual] listDokumenty
)
go

if exists (select * from sysobjects where name='n5sprzedaz')
	drop table n5sprzedaz
go

create table n5sprzedaz
(
	IdObj integer not null constraint PK_n5sprzedaz_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	dDataWyst datetime not null,
	dDataSprzed datetime not null,
	dDataPlat datetime not null,
	pSposobPlatnosci integer not null,
	pKlient integer not null,
	pKlient_JO integer not null,
	pKlientPracownik integer not null,
	pUzytRej integer not null,
	strUwagi varchar(512) not null,
	eSposVAT integer not null,
	eNettoBrutto integer not null,
	-- [virtual] listPozycje,
	pZadanie integer not null,
	curSumaNetto decimal(12,2) not null,
	curSumaVAT decimal(12,2) not null,
	curSumaBrutto decimal(12,2) not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	pTransakcja integer not null,
	curNetto0 decimal(12,2) not null,
	curNettoZw decimal(12,2) not null,
	curNettoNp decimal(12,2) not null,
	curNetto2 decimal(12,2) not null,
	curVat2 decimal(12,2) not null,
	-- [virtual] curBrutto2,
	curNetto3 decimal(12,2) not null,
	curVat3 decimal(12,2) not null,
	-- [virtual] curBrutto3,
	curNetto4 decimal(12,2) not null,
	curVat4 decimal(12,2) not null,
	-- [virtual] curBrutto4,
	curNetto7 decimal(12,2) not null,
	curVat7 decimal(12,2) not null,
	-- [virtual] curBrutto7,
	curNetto12 decimal(12,2) not null,
	curVat12 decimal(12,2) not null,
	-- [virtual] curBrutto12,
	curNetto17 decimal(12,2) not null,
	curVat17 decimal(12,2) not null,
	-- [virtual] curBrutto17,
	curNetto22 decimal(12,2) not null,
	curVat22 decimal(12,2) not null,
	-- [virtual] curBrutto22,
	pPopSprzed integer not null,
	pFaktura integer not null,
	cAutoCalc varchar(1) not null,
	curSumaWal decimal(12,2) not null,
	pWaluta integer not null,
	pRozlVat integer not null,
	pZamowienie integer not null,
	curKurs decimal(14,4) not null,
	-- [virtual] fXMLCopy,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5opakowanie_produktu')
	drop table n5opakowanie_produktu
go

create table n5opakowanie_produktu
(
	IdObj integer not null constraint PK_n5opakowanie_produktu_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(32) not null,
	eRodzaj integer not null,
	pOpakowanieJedn integer not null,
	currKrotnosc decimal(14,4) not null,
	curIlosc decimal(14,4) not null,
	strEAN varchar(32) not null,
	curWagaNetto decimal(14,4) not null,
	curWagaBrutto decimal(14,4) not null,
	pJednostkaWagi integer not null,
	curCenaNetto1 decimal(14,4) not null,
	curCenaBrutto1 decimal(14,4) not null,
	curCenaNetto2 decimal(14,4) not null,
	curCenaBrutto2 decimal(14,4) not null,
	curCenaNetto3 decimal(14,4) not null,
	curCenaBrutto3 decimal(14,4) not null,
	curCenaNetto4 decimal(14,4) not null,
	curCenaBrutto4 decimal(14,4) not null,
	curCenaNetto5 decimal(14,4) not null,
	curCenaBrutto5 decimal(14,4) not null,
	curCenaNetto6 decimal(14,4) not null,
	curCenaBrutto6 decimal(14,4) not null,
	pWaluta integer not null,
	strKodOpak varchar(8) not null,
	pJednOpak integer not null,
	-- [virtual] nPriceRecalc,
	pZamiennik integer not null,
	strNazwaMiedzynarodowa varchar(32) not null,
	curIloscMin decimal(14,4) not null,
	curIloscMax decimal(14,4) not null,
	curNarzutMin decimal(14,4) not null,
	curNarzutMax decimal(14,4) not null,
	curNarzutZal decimal(14,4) not null
)
go

if exists (select * from sysobjects where name='n5produkt')
	drop table n5produkt
go

create table n5produkt
(
	IdObj integer not null constraint PK_n5produkt_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNazwaMiedzynarodowa varchar(128) not null,
	strIndeks varchar(32) not null,
	strKodCelny varchar(32) not null,
	strKodPKWiU varchar(32) not null,
	eVAT integer not null,
	strOpis varchar(512) not null,
	pUlotka integer not null,
	pInstrukcja integer not null,
	pJednostkaEwid integer not null,
	eAktywny integer not null,
	-- [virtual] listOpakowania,
	pGrupaProd integer not null,
	strCecha1 varchar(128) not null,
	strCecha2 varchar(128) not null,
	strCecha3 varchar(128) not null,
	-- [virtual] fZdjecie,
	eRodzaj integer not null,
	cProdukowalny varchar(1) not null
)
go

if exists (select * from sysobjects where name='n5pozsprzedaz')
	drop table n5pozsprzedaz
go

create table n5pozsprzedaz
(
	IdObj integer not null constraint PK_n5pozsprzedaz_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	curIloscOpak decimal(14,4) not null,
	pOpak integer not null,
	curCenaBazNetto decimal(14,4) not null,
	curCenaBazBrutto decimal(14,4) not null,
	curRabat decimal(12,2) not null,
	eVAT integer not null,
	curCenaNetto decimal(14,4) not null,
	curCenaBrutto decimal(14,4) not null,
	curWartNetto decimal(12,2) not null,
	curVAT decimal(12,2) not null,
	-- [virtual] curWartBrutto,
	curCenaBazowaNettoWal decimal(14,4) not null,
	curCenaNettoWal decimal(14,4) not null,
	curWartWal decimal(12,2) not null,
	strUwagi varchar(512) not null,
	-- [virtual] nRabatRecalc,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5dokumentlinks')
	drop table n5dokumentlinks
go

create table n5dokumentlinks
(
	IdObj integer not null constraint PK_n5dokumentlinks_IdObj primary key clustered,
	VersionId integer not null,
	pDokument integer not null
)
go

if exists (select * from sysobjects where name='n5pkpir')
	drop table n5pkpir
go

create table n5pkpir
(
	IdObj integer not null constraint PK_n5pkpir_IdObj primary key clustered,
	VersionId integer not null,
	nNumOper integer not null,
	dDataOper datetime not null,
	pRejestrDok integer not null,
	strNrDok varchar(32) not null,
	pKlient integer not null,
	strOpis varchar(128) not null,
	strUwagi varchar(512) not null,
	curWartSprzed decimal(12,2) not null,
	curPozPrzych decimal(12,2) not null,
	-- [virtual] curRazemPrzych,
	curZakTow decimal(12,2) not null,
	curKosztZak decimal(12,2) not null,
	curKosztRekl decimal(12,2) not null,
	curWynagrodz decimal(12,2) not null,
	curPozWyd decimal(12,2) not null,
	-- [virtual] curRazemWyd,
	curKol16 decimal(12,2) not null
)
go

if exists (select * from sysobjects where name='n5typinstytucji')
	drop table n5typinstytucji
go

create table n5typinstytucji
(
	IdObj integer not null constraint PK_n5typinstytucji_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null
)
go

if exists (select * from sysobjects where name='n5analfinans')
	drop table n5analfinans
go

create table n5analfinans
(
	IdObj integer not null constraint PK_n5analfinans_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	-- [virtual] fXML
)
go

if exists (select * from sysobjects where name='n5rejestrdok')
	drop table n5rejestrdok
go

create table n5rejestrdok
(
	IdObj integer not null constraint PK_n5rejestrdok_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	eTyp integer not null,
	strFormatNumeracji varchar(32) not null,
	strFormatNumeracji2 varchar(32) not null,
	eAktywny integer not null,
	nInternalID integer not null,
	nLicznik integer not null,
	strKonfiguracja varchar(512) not null,
	nLicznik2 integer not null,
	pDefSchematdekr integer not null,
	dDataZamk datetime not null,
	wrefParam1 integer not null,
	wrefParam1_wrt integer not null,
	wrefParam2 integer not null,
	wrefParam2_wrt integer not null,
	nParam3 integer not null,
	pRokKsieg integer not null
)
go

if exists (select * from sysobjects where name='n5konto')
	drop table n5konto
go

create table n5konto
(
	IdObj integer not null constraint PK_n5konto_IdObj primary key clustered,
	VersionId integer not null,
	strSymbol varchar(64) not null,
	strNazwa varchar(128) not null,
	strOpis varchar(1024) not null,
	pJednostka integer not null,
	wrefPodmiotRozrach integer not null,
	wrefPodmiotRozrach_wrt integer not null,
	pKontoNadrz integer not null,
	eAnalit integer not null,
	eBilans integer not null,
	eAktywne integer not null
)
go

if exists (select * from sysobjects where name='n5dekret')
	drop table n5dekret
go

create table n5dekret
(
	IdObj integer not null constraint PK_n5dekret_IdObj primary key clustered,
	VersionId integer not null,
	pKonto integer not null,
	curWn decimal(12,2) not null,
	curMa decimal(12,2) not null,
	dDataKsieg datetime not null,
	strOpis varchar(128) not null,
	eTyp integer not null,
	eStatus integer not null,
	pTransakcja integer not null,
	pKwalifikator integer not null,
	cAuto varchar(1) not null
)
go

if exists (select * from sysobjects where name='n5dowodksieg')
	drop table n5dowodksieg
go

create table n5dowodksieg
(
	IdObj integer not null constraint PK_n5dowodksieg_IdObj primary key clustered,
	VersionId integer not null,
	dDataRej datetime not null,
	dDataKsieg datetime not null,
	strNrDok varchar(32) not null,
	nNumDow integer not null,
	strOpis varchar(512) not null,
	eTyp integer not null,
	eStatus integer not null,
	-- [virtual] listDekret,
	pUzytRej integer not null,
	pRejestrDok integer not null,
	wrefDokZrod integer not null,
	wrefDokZrod_wrt integer not null,
	-- [virtual] pSumator,
	cAuto varchar(1) not null
)
go

if exists (select * from sysobjects where name='n5platnosc')
	drop table n5platnosc
go

create table n5platnosc
(
	IdObj integer not null constraint PK_n5platnosc_IdObj primary key clustered,
	VersionId integer not null,
	dDataOper datetime not null,
	wrefPodmiot integer not null,
	wrefPodmiot_wrt integer not null,
	strOpis varchar(128) not null,
	pZadanie integer not null,
	pUzytRej integer not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	strNrDok varchar(32) not null,
	-- [virtual] listPozycje,
	nNumOper integer not null,
	curKwotaPodm decimal(12,2) not null,
	curKursPodm decimal(14,4) not null,
	pWalutaPodm integer not null,
	curKwotaStan decimal(12,2) not null,
	curKursEwid decimal(14,4) not null,
	curKwotaEwid decimal(12,2) not null,
	-- [virtual] curSumaPozPodm,
	eStatus integer not null,
	-- [virtual] cInternalAllowZero
)
go

if exists (select * from sysobjects where name='n5typdzialania')
	drop table n5typdzialania
go

create table n5typdzialania
(
	IdObj integer not null constraint PK_n5typdzialania_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	nInternalID integer not null,
	pTypNadrzedny integer not null,
	strOpis varchar(255) not null
)
go

if exists (select * from sysobjects where name='n5transakcja')
	drop table n5transakcja
go

create table n5transakcja
(
	IdObj integer not null constraint PK_n5transakcja_IdObj primary key clustered,
	VersionId integer not null,
	strSymTrans varchar(32) not null,
	pWaluta integer not null,
	wrefPodmiot integer not null,
	wrefPodmiot_wrt integer not null,
	dDataRozp datetime not null,
	dDataWym datetime not null,
	dDataZamk datetime not null,
	curWn decimal(12,2) not null,
	curMa decimal(12,2) not null,
	eTyp integer not null,
	eStatus integer not null,
	curWnEwid decimal(12,2) not null,
	curMaEwid decimal(12,2) not null,
	eTypOdset integer not null,
	curOdsetkiUmowne decimal(12,2) not null,
	pNotaOds integer not null
)
go

if exists (select * from sysobjects where name='n5schematdekr')
	drop table n5schematdekr
go

create table n5schematdekr
(
	IdObj integer not null constraint PK_n5schematdekr_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pRejestrDok integer not null,
	pDziennik integer not null,
	strOpis varchar(255) not null,
	strVBcode varchar(7900) not null,
	eAktywny integer not null,
	-- [virtual] fXMLDefinition
)
go

if exists (select * from sysobjects where name='n5branza')
	drop table n5branza
go

create table n5branza
(
	IdObj integer not null constraint PK_n5branza_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	pBranzaNad integer not null,
	strKOD varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5magazyn')
	drop table n5magazyn
go

create table n5magazyn
(
	IdObj integer not null constraint PK_n5magazyn_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pWaluta integer not null,
	eTyp integer not null,
	pJednostkaOrg integer not null
)
go

if exists (select * from sysobjects where name='n5pozdokmag')
	drop table n5pozdokmag
go

create table n5pozdokmag
(
	IdObj integer not null constraint PK_n5pozdokmag_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	pOpak integer not null,
	nTypDok integer not null,
	pMagZrod integer not null,
	pMagDocel integer not null,
	pJednOpak integer not null,
	curIloscOpak decimal(14,4) not null,
	pJednEwid integer not null,
	curIloscEwid decimal(14,4) not null,
	curCenaMag decimal(14,4) not null,
	curCenaEwid decimal(14,4) not null,
	curWartMag decimal(12,2) not null,
	curWartEwid decimal(12,2) not null,
	nNumOpMagDost integer not null,
	nLpDost integer not null,
	strUwagi varchar(512) not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	dDataWazn datetime not null
)
go

if exists (select * from sysobjects where name='n5dokmag')
	drop table n5dokmag
go

create table n5dokmag
(
	IdObj integer not null constraint PK_n5dokmag_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	pKlient integer not null,
	pKlient_JO integer not null,
	pKlientPracownik integer not null,
	pDokMag integer not null,
	nNumOper integer not null,
	nTypDok integer not null,
	dDataWyst datetime not null,
	pUzytRej integer not null,
	strUwagi varchar(512) not null,
	-- [virtual] listPozycje,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	curSumaMag decimal(12,2) not null,
	curSumaEwid decimal(12,2) not null,
	pMagZrod integer not null,
	pMagDocel integer not null,
	cAutoCalc varchar(1) not null,
	wrefDokHandl integer not null,
	wrefDokHandl_wrt integer not null,
	-- [virtual] cInternalAllowChanges,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	dDataRezerw datetime not null,
	tCzasRezerw integer not null
)
go

if exists (select * from sysobjects where name='n5zadaniedw')
	drop table n5zadaniedw
go

create table n5zadaniedw
(
	IdObj integer not null constraint PK_n5zadaniedw_IdObj primary key clustered,
	VersionId integer not null,
	pWykonawcaDW integer not null,
	dDataPow datetime not null,
	tCzasPow integer not null
)
go

if exists (select * from sysobjects where name='n5sposplat')
	drop table n5sposplat
go

create table n5sposplat
(
	IdObj integer not null constraint PK_n5sposplat_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(32) not null,
	nDni integer not null,
	eTyp integer not null,
	strNazwaMiedzynarodowa varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5kurswalut')
	drop table n5kurswalut
go

create table n5kurswalut
(
	IdObj integer not null constraint PK_n5kurswalut_IdObj primary key clustered,
	VersionId integer not null,
	pWalZ integer not null,
	pWalN integer not null,
	dData datetime not null,
	curMnoznik decimal(12,2) not null,
	curKupnoWal decimal(14,4) not null,
	curSprzedWal decimal(14,4) not null
)
go

if exists (select * from sysobjects where name='n5rokksieg')
	drop table n5rokksieg
go

create table n5rokksieg
(
	IdObj integer not null constraint PK_n5rokksieg_IdObj primary key clustered,
	VersionId integer not null,
	dDataRozp datetime not null,
	dDataZakon datetime not null,
	dDataZamk datetime not null,
	-- [virtual] dLastDataZakon
)
go

if exists (select * from sysobjects where name='n5zamowienie')
	drop table n5zamowienie
go

create table n5zamowienie
(
	IdObj integer not null constraint PK_n5zamowienie_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	dDataWyst datetime not null,
	dDataPlat datetime not null,
	dDataReal datetime not null,
	dDataAkt datetime not null,
	pSposobPlatnosci integer not null,
	pKlient integer not null,
	pKlient_JO integer not null,
	pKlientPracownik integer not null,
	pUzytRej integer not null,
	strUwagi varchar(512) not null,
	eNettoBrutto integer not null,
	-- [virtual] listPozycje,
	pZadanie integer not null,
	curSumaNetto decimal(12,2) not null,
	curSumaVAT decimal(12,2) not null,
	curSumaBrutto decimal(12,2) not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	-- [virtual] fXMLCopy,
	curSumaWal decimal(12,2) not null,
	pWaluta integer not null,
	curKurs decimal(14,4) not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5pozzamowienie')
	drop table n5pozzamowienie
go

create table n5pozzamowienie
(
	IdObj integer not null constraint PK_n5pozzamowienie_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	curIloscOpak decimal(14,4) not null,
	pOpak integer not null,
	curCenaBazNetto decimal(14,4) not null,
	curCenaBazBrutto decimal(14,4) not null,
	curRabat decimal(12,2) not null,
	eVAT integer not null,
	curCenaNetto decimal(14,4) not null,
	curCenaBrutto decimal(14,4) not null,
	curWartNetto decimal(12,2) not null,
	curVAT decimal(12,2) not null,
	-- [virtual] curWartBrutto,
	curCenaBazowaNettoWal decimal(14,4) not null,
	curCenaNettoWal decimal(14,4) not null,
	curWartWal decimal(12,2) not null,
	strUwagi varchar(512) not null,
	curIloscOpakPoz decimal(14,4) not null,
	-- [virtual] nRabatRecalc,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5pozzakup')
	drop table n5pozzakup
go

create table n5pozzakup
(
	IdObj integer not null constraint PK_n5pozzakup_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	curIloscOpak decimal(14,4) not null,
	pOpak integer not null,
	eVAT integer not null,
	curCenaNetto decimal(14,4) not null,
	curCenaBrutto decimal(14,4) not null,
	curWartNetto decimal(12,2) not null,
	curVAT decimal(12,2) not null,
	curWartBrutto decimal(12,2) not null,
	curCenaNettoWal decimal(14,4) not null,
	strUwagi varchar(512) not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5zakup')
	drop table n5zakup
go

create table n5zakup
(
	IdObj integer not null constraint PK_n5zakup_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	strNrDokObcy varchar(32) not null,
	dDataWyst datetime not null,
	dDataOtrzym datetime not null,
	dDataZakupu datetime not null,
	dDataPlat datetime not null,
	pSposobPlatnosci integer not null,
	pDostawca integer not null,
	pDostawca_JO integer not null,
	pUzytRej integer not null,
	strUwagi varchar(128) not null,
	-- [virtual] listPozycje,
	pZadanie integer not null,
	curSumaNetto decimal(12,2) not null,
	curSumaVAT decimal(12,2) not null,
	curSumaBrutto decimal(12,2) not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	pTransakcja integer not null,
	curNetto0 decimal(12,2) not null,
	curNettoZw decimal(12,2) not null,
	curNettoNp decimal(12,2) not null,
	curNetto2 decimal(12,2) not null,
	curVat2 decimal(12,2) not null,
	-- [virtual] curBrutto2,
	curNetto3 decimal(12,2) not null,
	curVat3 decimal(12,2) not null,
	-- [virtual] curBrutto3,
	curNetto4 decimal(12,2) not null,
	curVat4 decimal(12,2) not null,
	-- [virtual] curBrutto4,
	curNetto7 decimal(12,2) not null,
	curVat7 decimal(12,2) not null,
	-- [virtual] curBrutto7,
	curNetto12 decimal(12,2) not null,
	curVat12 decimal(12,2) not null,
	-- [virtual] curBrutto12,
	curNetto17 decimal(12,2) not null,
	curVat17 decimal(12,2) not null,
	-- [virtual] curBrutto17,
	curNetto22 decimal(12,2) not null,
	curVat22 decimal(12,2) not null,
	-- [virtual] curBrutto22,
	pPopZAkup integer not null,
	curSumaWal decimal(12,2) not null,
	pWaluta integer not null,
	eZwOpSprz integer not null,
	eTypZakup integer not null,
	pRozlVat integer not null,
	curKurs decimal(12,2) not null,
	cAutoCalc varchar(1) not null,
	-- [virtual] fXMLCopy,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	curOplatyZagr decimal(12,2) not null,
	curClo decimal(12,2) not null,
	curAkcyza decimal(12,2) not null,
	curOplatyKraj decimal(12,2) not null,
	curKursCelny decimal(12,2) not null
)
go

if exists (select * from sysobjects where name='n5rozlvat')
	drop table n5rozlvat
go

create table n5rozlvat
(
	IdObj integer not null constraint PK_n5rozlvat_IdObj primary key clustered,
	VersionId integer not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	curSpZwN decimal(12,2) not null,
	curSpExN decimal(12,2) not null,
	curSpEx21N decimal(12,2) not null,
	curSpOp0 decimal(12,2) not null,
	curSpOp3N decimal(12,2) not null,
	curSpOp3V decimal(12,2) not null,
	curSpOp7N decimal(12,2) not null,
	curSpOp7V decimal(12,2) not null,
	curSpOp22N decimal(12,2) not null,
	curSpOp22V decimal(12,2) not null,
	curSpNP decimal(12,2) not null,
	curSpSpis6V decimal(12,2) not null,
	curSpRazemN decimal(12,2) not null,
	curSpRazemV decimal(12,2) not null,
	curPrNadV decimal(12,2) not null,
	curPrRU14V decimal(12,2) not null,
	curZPSON decimal(12,2) not null,
	curZPSOV decimal(12,2) not null,
	curZPSMN decimal(12,2) not null,
	curZPSMV decimal(12,2) not null,
	curZPTON decimal(12,2) not null,
	curZPTOV decimal(12,2) not null,
	curZPTMN decimal(12,2) not null,
	curZPTMV decimal(12,2) not null,
	curZASON decimal(12,2) not null,
	curZASOV decimal(12,2) not null,
	curZASMN decimal(12,2) not null,
	curZASMV decimal(12,2) not null,
	curZATON decimal(12,2) not null,
	curZATOV decimal(12,2) not null,
	curZATMN decimal(12,2) not null,
	curZATMV decimal(12,2) not null,
	curZNON decimal(12,2) not null,
	curZNOV decimal(12,2) not null,
	curSpOpod6MN decimal(12,2) not null,
	curSpTotal6MN decimal(12,2) not null,
	curVATZSMV decimal(12,2) not null,
	curVATZTMV decimal(12,2) not null,
	curVATOdl decimal(12,2) not null,
	curVATNadPlus decimal(12,2) not null,
	curKasaOdl decimal(12,2) not null,
	curVATZaniech decimal(12,2) not null,
	curVATDoZapl decimal(12,2) not null,
	curVATNadMin decimal(12,2) not null,
	curKasaZwrot decimal(12,2) not null,
	curNadMinTotal decimal(12,2) not null,
	curNadMinZwrot decimal(12,2) not null,
	curNadMinNast decimal(12,2) not null,
	pUzytRej integer not null,
	pZadanie integer not null,
	pSchematDekr integer not null,
	pDowKsieg integer not null,
	pTransakcja integer not null,
	pUrzadSkarbowy integer not null
)
go

if exists (select * from sysobjects where name='n5grupasrtrw')
	drop table n5grupasrtrw
go

create table n5grupasrtrw
(
	IdObj integer not null constraint PK_n5grupasrtrw_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pGrupaNadrzedna integer not null
)
go

if exists (select * from sysobjects where name='n5srtrw')
	drop table n5srtrw
go

create table n5srtrw
(
	IdObj integer not null constraint PK_n5srtrw_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNumEwid varchar(64) not null,
	strNumSer varchar(64) not null,
	strKRST varchar(64) not null,
	pGrupa integer not null,
	dDataGwar datetime not null,
	eRodzaj integer not null,
	pPracownik integer not null,
	strUwagi varchar(255) not null,
	pMUJO integer not null,
	nLicznik integer not null,
	curWartoscPod decimal(12,2) not null,
	curUmorzPod decimal(12,2) not null,
	curWartoscBil decimal(12,2) not null,
	curUmorzBil decimal(12,2) not null,
	curStawkaPod decimal(12,2) not null,
	curStawkaBil decimal(12,2) not null,
	eMetAmPod integer not null,
	eMetAmBil integer not null,
	eStatus integer not null,
	nRokProd integer not null
)
go

if exists (select * from sysobjects where name='n5opmag')
	drop table n5opmag
go

create table n5opmag
(
	IdObj integer not null constraint PK_n5opmag_IdObj primary key clustered,
	VersionId integer not null,
	nNumerOp integer not null,
	nLP integer not null,
	curIloscZrod decimal(14,4) not null,
	curCenaZrod decimal(14,4) not null,
	pProdZrod integer not null,
	pOpakZrod integer not null,
	pMagZrod integer not null,
	curIloscDocel decimal(14,4) not null,
	curWspZmianyCeny decimal(14,4) not null,
	pProdDocel integer not null,
	pOpakDocel integer not null,
	pMagDocel integer not null,
	nNumOpMagDost integer not null,
	nLpDost integer not null,
	eTypPow integer not null,
	dDataWazn datetime not null
)
go

if exists (select * from sysobjects where name='n5koropmag')
	drop table n5koropmag
go

create table n5koropmag
(
	IdObj integer not null constraint PK_n5koropmag_IdObj primary key clustered,
	VersionId integer not null,
	nNumerOp integer not null,
	nLP integer not null,
	curIloscZrod decimal(14,4) not null,
	curCenaZrod decimal(14,4) not null,
	pProdZrod integer not null,
	pOpakZrod integer not null,
	pMagZrod integer not null,
	curIloscDocel decimal(14,4) not null,
	curWspZmianyCeny decimal(14,4) not null,
	pProdDocel integer not null,
	pOpakDocel integer not null,
	pMagDocel integer not null,
	nNumOpMagDost integer not null,
	nLpDost integer not null,
	eTypPow integer not null,
	dDataWazn datetime not null
)
go

if exists (select * from sysobjects where name='n5stanmag')
	drop table n5stanmag
go

create table n5stanmag
(
	IdObj integer not null constraint PK_n5stanmag_IdObj primary key clustered,
	VersionId integer not null,
	pMagazyn integer not null,
	pProdukt integer not null,
	pOpak integer not null,
	curCena decimal(14,4) not null,
	curIloscOpak decimal(14,4) not null,
	nNumOpMag integer not null,
	nLP integer not null,
	dDataWazn datetime not null
)
go

if exists (select * from sysobjects where name='n5pozrecepta')
	drop table n5pozrecepta
go

create table n5pozrecepta
(
	IdObj integer not null constraint PK_n5pozrecepta_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	pOpak integer not null,
	curIloscOpak decimal(14,4) not null
)
go

if exists (select * from sysobjects where name='n5recepta')
	drop table n5recepta
go

create table n5recepta
(
	IdObj integer not null constraint PK_n5recepta_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNorma varchar(64) not null,
	strOpis varchar(1024) not null,
	pWyrob integer not null,
	pWyrOpak integer not null,
	curIloscOpak decimal(14,4) not null,
	-- [virtual] listSurowce,
	-- [virtual] listCzynnosci
)
go

if exists (select * from sysobjects where name='n5pozzlecprod')
	drop table n5pozzlecprod
go

create table n5pozzlecprod
(
	IdObj integer not null constraint PK_n5pozzlecprod_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	pOpak integer not null,
	pRecepta integer not null,
	curIloscOpak decimal(14,4) not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5zlecprod')
	drop table n5zlecprod
go

create table n5zlecprod
(
	IdObj integer not null constraint PK_n5zlecprod_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	dDataWyst datetime not null,
	pUzytRej integer not null,
	strUwagi varchar(512) not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	pZadanie integer not null,
	pKlient integer not null,
	pKlient_JO integer not null,
	pZamowienie integer not null,
	-- [virtual] listPozycje,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5eventlog')
	drop table n5eventlog
go

create table n5eventlog
(
	IdObj integer not null constraint PK_n5eventlog_IdObj primary key clustered,
	VersionId integer not null,
	eTyp integer not null,
	dDataZdarz datetime not null,
	tCzasZdarz integer not null,
	pUser integer not null,
	strOpis varchar(7900) not null
)
go

if exists (select * from sysobjects where name='n5polrab')
	drop table n5polrab
go

create table n5polrab
(
	IdObj integer not null constraint PK_n5polrab_IdObj primary key clustered,
	VersionId integer not null,
	wpProdGrupa integer not null,
	wpProdGrupa_wrt integer not null,
	pOpak integer not null,
	wpKlientGrupa integer not null,
	wpKlientGrupa_wrt integer not null,
	nPriorytet integer not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	strNazwaPromocji varchar(128) not null,
	curCenaRab decimal(14,4) not null,
	eTyp integer not null
)
go

if exists (select * from sysobjects where name='n5plschematnal')
	drop table n5plschematnal
go

create table n5plschematnal
(
	IdObj integer not null constraint PK_n5plschematnal_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strOpis varchar(1024) not null,
	strVBcode varchar(7900) not null,
	nPriorytet integer not null,
	-- [virtual] fXMLDefinition
)
go

if exists (select * from sysobjects where name='n5plstawka')
	drop table n5plstawka
go

create table n5plstawka
(
	IdObj integer not null constraint PK_n5plstawka_IdObj primary key clustered,
	VersionId integer not null,
	strKod varchar(8) not null,
	strOpis varchar(1024) not null,
	curWartosc decimal(14,4) not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	pJednostka integer not null
)
go

if exists (select * from sysobjects where name='n5plnaliczenie')
	drop table n5plnaliczenie
go

create table n5plnaliczenie
(
	IdObj integer not null constraint PK_n5plnaliczenie_IdObj primary key clustered,
	VersionId integer not null,
	pPracownik integer not null,
	dDataRej datetime not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	pUzytRej integer not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	pListaPlac integer not null,
	pTransakcja integer not null,
	pZadanie integer not null,
	-- [virtual] listDokZrod,
	-- [virtual] listSkladnik
)
go

if exists (select * from sysobjects where name='n5plsklnal')
	drop table n5plsklnal
go

create table n5plsklnal
(
	IdObj integer not null constraint PK_n5plsklnal_IdObj primary key clustered,
	VersionId integer not null,
	pSchemat integer not null
)
go

if exists (select * from sysobjects where name='n5pllistaplac')
	drop table n5pllistaplac
go

create table n5pllistaplac
(
	IdObj integer not null constraint PK_n5pllistaplac_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5plgrzas')
	drop table n5plgrzas
go

create table n5plgrzas
(
	IdObj integer not null constraint PK_n5plgrzas_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null
)
go

if exists (select * from sysobjects where name='n5plsubkonto')
	drop table n5plsubkonto
go

create table n5plsubkonto
(
	IdObj integer not null constraint PK_n5plsubkonto_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	strKod varchar(8) not null,
	strOpis varchar(1024) not null,
	eAktywne integer not null,
	pJednostka integer not null
)
go

if exists (select * from sysobjects where name='n5pldekret')
	drop table n5pldekret
go

create table n5pldekret
(
	IdObj integer not null constraint PK_n5pldekret_IdObj primary key clustered,
	VersionId integer not null,
	pPracownik integer not null,
	pSubKonto integer not null,
	curWn decimal(14,4) not null,
	curMa decimal(14,4) not null,
	dDataKsieg datetime not null,
	pListaPlac integer not null,
	pNaliczenie integer not null,
	pSchematNal integer not null,
	wrefDokument integer not null,
	wrefDokument_wrt integer not null,
	strOpis varchar(64) not null
)
go

if exists (select * from sysobjects where name='n5plumowa')
	drop table n5plumowa
go

create table n5plumowa
(
	IdObj integer not null constraint PK_n5plumowa_IdObj primary key clustered,
	VersionId integer not null,
	pPracownik integer not null,
	dDataRej datetime not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	pUzytRej integer not null,
	eTypUmowy integer not null,
	-- [virtual] listSkladnik,
	pUmowaPop integer not null,
	pKalendarz integer not null
)
go

if exists (select * from sysobjects where name='n5plchoroba')
	drop table n5plchoroba
go

create table n5plchoroba
(
	IdObj integer not null constraint PK_n5plchoroba_IdObj primary key clustered,
	VersionId integer not null,
	pPracownik integer not null,
	dDataRej datetime not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	pUzytRej integer not null,
	pUmowa integer not null,
	pSchemat integer not null,
	strNumZwol varchar(8) not null,
	strKodStat varchar(4) not null,
	strKodPlatnik varchar(4) not null
)
go

if exists (select * from sysobjects where name='n5plnieob')
	drop table n5plnieob
go

create table n5plnieob
(
	IdObj integer not null constraint PK_n5plnieob_IdObj primary key clustered,
	VersionId integer not null,
	pPracownik integer not null,
	dDataRej datetime not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	pUzytRej integer not null,
	pUmowa integer not null,
	pSchemat integer not null,
	eTyp integer not null
)
go

if exists (select * from sysobjects where name='n5rozlcit')
	drop table n5rozlcit
go

create table n5rozlcit
(
	IdObj integer not null constraint PK_n5rozlcit_IdObj primary key clustered,
	VersionId integer not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	curPrzych decimal(12,2) not null,
	curPrzychZagr decimal(12,2) not null,
	curKoszty decimal(12,2) not null,
	curDochodWst decimal(12,2) not null,
	curStrataWst decimal(12,2) not null,
	curStrataZwol decimal(12,2) not null,
	curDochod decimal(12,2) not null,
	curStrata decimal(12,2) not null,
	curDochWolne decimal(12,2) not null,
	curOdlDoch decimal(12,2) not null,
	curOdlInwest decimal(12,2) not null,
	curRazemOdl decimal(12,2) not null,
	curOdlInwestPoprz decimal(12,2) not null,
	curDochZwol decimal(12,2) not null,
	curZwiekszajacaPodstawe decimal(12,2) not null,
	curPodstawa decimal(12,2) not null,
	curPodstawaStrata decimal(12,2) not null,
	curStawka decimal(12,2) not null,
	curPodWst decimal(12,2) not null,
	curOdlPod decimal(12,2) not null,
	curPodatek decimal(12,2) not null,
	curSumaPoprzZal decimal(12,2) not null,
	curZaliczka decimal(12,2) not null,
	curSumaZal decimal(12,2) not null,
	curOgraniczeniePoboruZaliczek decimal(12,2) not null,
	curZaliczkaPoOgraniczeniu decimal(12,2) not null,
	curInneDoch decimal(12,2) not null,
	curPodInne decimal(12,2) not null,
	curPodArt37 decimal(12,2) not null,
	curOdsetkiArt16 decimal(12,2) not null,
	pUzytRej integer not null,
	pZadanie integer not null,
	pSchematDekr integer not null,
	pDowKsieg integer not null,
	pTransakcja integer not null,
	pUrzadSkarbowy integer not null
)
go

if exists (select * from sysobjects where name='n5rule')
	drop table n5rule
go

create table n5rule
(
	IdObj integer not null constraint PK_n5rule_IdObj primary key clustered,
	VersionId integer not null,
	strCode varchar(8) not null,
	strName varchar(128) not null,
	cVisible varchar(1) not null,
	eSignificance integer not null,
	strParam varchar(7900) not null,
	strOptionalParam varchar(7900) not null
)
go

if exists (select * from sysobjects where name='n5pozrealprod')
	drop table n5pozrealprod
go

create table n5pozrealprod
(
	IdObj integer not null constraint PK_n5pozrealprod_IdObj primary key clustered,
	VersionId integer not null,
	pProdukt integer not null,
	pOpak integer not null,
	pMagazyn integer not null,
	pJednOpak integer not null,
	curIloscOpak decimal(14,4) not null,
	pJednEwid integer not null,
	curIloscEwid decimal(14,4) not null,
	curCenaMag decimal(14,4) not null,
	curCenaEwid decimal(14,4) not null,
	curWartMag decimal(12,2) not null,
	curWartEwid decimal(12,2) not null,
	nNumOpMagDost integer not null,
	nLpDost integer not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null
)
go

if exists (select * from sysobjects where name='n5realprod')
	drop table n5realprod
go

create table n5realprod
(
	IdObj integer not null constraint PK_n5realprod_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	nNumOper integer not null,
	pWyrob integer not null,
	pOpak integer not null,
	curIloscOpak decimal(14,4) not null,
	dDataWazn datetime not null,
	dDataWyst datetime not null,
	pUzytRej integer not null,
	-- [virtual] listPozycje,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	curSumaMag decimal(12,2) not null,
	curSumaEwid decimal(12,2) not null,
	pMagazyn integer not null,
	cAutoCalc varchar(1) not null,
	pZlecProd integer not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	-- [virtual] calculate
)
go

if exists (select * from sysobjects where name='n5kwalifikator')
	drop table n5kwalifikator
go

create table n5kwalifikator
(
	IdObj integer not null constraint PK_n5kwalifikator_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null
)
go

if exists (select * from sysobjects where name='n5budzet')
	drop table n5budzet
go

create table n5budzet
(
	IdObj integer not null constraint PK_n5budzet_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	dDataOd datetime not null,
	dDataDo datetime not null
)
go

if exists (select * from sysobjects where name='n5konto_budzet')
	drop table n5konto_budzet
go

create table n5konto_budzet
(
	IdObj integer not null constraint PK_n5konto_budzet_IdObj primary key clustered,
	VersionId integer not null,
	pKonto integer not null,
	pBudzet integer not null,
	curKwota decimal(12,2) not null,
	eOdniesienie integer not null,
	curRealizacja decimal(12,2) not null,
	curPrognoza decimal(12,2) not null
)
go

if exists (select * from sysobjects where name='n5bwinfo_kat')
	drop table n5bwinfo_kat
go

create table n5bwinfo_kat
(
	IdObj integer not null constraint PK_n5bwinfo_kat_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null
)
go

if exists (select * from sysobjects where name='n5bwinfo')
	drop table n5bwinfo
go

create table n5bwinfo
(
	IdObj integer not null constraint PK_n5bwinfo_IdObj primary key clustered,
	VersionId integer not null,
	strTytul varchar(128) not null,
	strNrInfo varchar(32) not null,
	dDataRej datetime not null,
	dDataAkt datetime not null,
	eStatus integer not null,
	pKategoria integer not null,
	-- [virtual] listProdukt,
	strObjaw varchar(1024) not null,
	-- [virtual] listObjawyZal,
	strPrzyczyna varchar(1024) not null,
	strRozwiazanie varchar(1024) not null,
	-- [virtual] listRozwiazanieZal,
	strUwagi varchar(1024) not null,
	pUzytRej integer not null,
	-- [virtual] listUwagiZal
)
go

if exists (select * from sysobjects where name='n5bwinfo_produkt')
	drop table n5bwinfo_produkt
go

create table n5bwinfo_produkt
(
	IdObj integer not null constraint PK_n5bwinfo_produkt_IdObj primary key clustered,
	VersionId integer not null,
	wpProdGrupa integer not null,
	wpProdGrupa_wrt integer not null,
	pOpak integer not null
)
go

if exists (select * from sysobjects where name='n5bwinfo_zal')
	drop table n5bwinfo_zal
go

create table n5bwinfo_zal
(
	IdObj integer not null constraint PK_n5bwinfo_zal_IdObj primary key clustered,
	VersionId integer not null,
	wrefZal integer not null,
	wrefZal_wrt integer not null
)
go

if exists (select * from sysobjects where name='n5poznotaods')
	drop table n5poznotaods
go

create table n5poznotaods
(
	IdObj integer not null constraint PK_n5poznotaods_IdObj primary key clustered,
	VersionId integer not null,
	pTransakcja integer not null,
	curStawka decimal(12,2) not null,
	curKwotaZal decimal(12,2) not null,
	curKwotaOds decimal(12,2) not null,
	nLiczbaDni integer not null,
	dDataZaplaty datetime not null
)
go

if exists (select * from sysobjects where name='n5notaods')
	drop table n5notaods
go

create table n5notaods
(
	IdObj integer not null constraint PK_n5notaods_IdObj primary key clustered,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	dDataWyst datetime not null,
	pKlient integer not null,
	pUzytRej integer not null,
	strUwagi varchar(512) not null,
	curSumaOds decimal(12,2) not null,
	-- [virtual] listPozycje,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	pTransakcja integer not null
)
go

if exists (select * from sysobjects where name='n5opsrtrw')
	drop table n5opsrtrw
go

create table n5opsrtrw
(
	IdObj integer not null constraint PK_n5opsrtrw_IdObj primary key clustered,
	VersionId integer not null,
	pSRTRW integer not null,
	nNumOpST integer not null,
	dDataOper datetime not null,
	eRodzaj integer not null,
	curWartoscPod decimal(12,2) not null,
	curUmorzPod decimal(12,2) not null,
	curAmortPod decimal(12,2) not null,
	curStawkaPod decimal(12,2) not null,
	curWartoscBil decimal(12,2) not null,
	curUmorzBil decimal(12,2) not null,
	curAmortBil decimal(12,2) not null,
	curStawkaBil decimal(12,2) not null,
	dDataAmort datetime not null,
	pMUJO integer not null,
	pUzytRej integer not null,
	pPracownik integer not null,
	wrefDokument integer not null,
	wrefDokument_wrt integer not null,
	pRejestrDok integer not null,
	pDowodKsieg integer not null,
	pSchematDekr integer not null,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	strUwagi varchar(512) not null,
	-- [virtual] fXMLCopy
)
go

if exists (select * from sysobjects where name='n5plwzorlp')
	drop table n5plwzorlp
go

create table n5plwzorlp
(
	IdObj integer not null constraint PK_n5plwzorlp_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	eTypUmowy integer not null,
	pCLPracownicy integer not null,
	pCLSkladniki integer not null,
	strFormatNumeracji varchar(32) not null,
	eAktywny integer not null
)
go

if exists (select * from sysobjects where name='n5plkalcp')
	drop table n5plkalcp
go

create table n5plkalcp
(
	IdObj integer not null constraint PK_n5plkalcp_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	eAktywny integer not null,
	-- [virtual] listPozycje,
	strUwagi varchar(512) not null
)
go

if exists (select * from sysobjects where name='n5plpozkalcp')
	drop table n5plpozkalcp
go

create table n5plpozkalcp
(
	IdObj integer not null constraint PK_n5plpozkalcp_IdObj primary key clustered,
	VersionId integer not null,
	cDniTyg varchar(8) not null,
	dDataOd datetime not null,
	dDataDo datetime not null,
	tCzasOd integer not null,
	tCzasDo integer not null,
	eTypOkresu integer not null
)
go

if exists (select * from sysobjects where name='n5plsklumowy')
	drop table n5plsklumowy
go

create table n5plsklumowy
(
	IdObj integer not null constraint PK_n5plsklumowy_IdObj primary key clustered,
	VersionId integer not null,
	pSchemat integer not null
)
go

if exists (select * from sysobjects where name='n5plsklnalzrod')
	drop table n5plsklnalzrod
go

create table n5plsklnalzrod
(
	IdObj integer not null constraint PK_n5plsklnalzrod_IdObj primary key clustered,
	VersionId integer not null,
	wrefDokument integer not null,
	wrefDokument_wrt integer not null
)
go

if exists (select * from sysobjects where name='SearchType')
	drop table SearchType
go

create table SearchType
(
	IdObj integer not null constraint PK_SearchType_IdObj primary key clustered,
	VersionId integer not null,
	Nazwa varchar(255) not null,
	ResultTypeId integer not null,
	-- [virtual] listFilter,
	-- [virtual] listOrder,
	-- [virtual] listColumn,
	cKind varchar(1) not null,
	strKod varchar(8) not null,
	nIsSecurity integer not null,
	Opis varchar(512) not null
)
go

if exists (select * from sysobjects where name='SearchTypeItem')
	drop table SearchTypeItem
go

create table SearchTypeItem
(
	IdObj integer not null constraint PK_SearchTypeItem_IdObj primary key clustered,
	VersionId integer not null,
	ComposedPath varchar(255) not null,
	-- [virtual] selectiontype,
	cGroup varchar(1) not null,
	cDesc varchar(1) not null,
	cLink varchar(1) not null
)
go

if exists (select * from sysobjects where name='n5sodgroup')
	drop table n5sodgroup
go

create table n5sodgroup
(
	IdObj integer not null constraint PK_n5sodgroup_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pSODGroup integer not null,
	strKod varchar(8) not null
)
go

if exists (select * from sysobjects where name='n5sod')
	drop table n5sod
go

create table n5sod
(
	IdObj integer not null constraint PK_n5sod_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(64) not null,
	pSODGroup integer not null,
	nSecId integer not null,
	nIdent integer not null,
	strKod varchar(8) not null
)
go

if exists (select * from sysobjects where name='n5securityobj')
	drop table n5securityobj
go

create table n5securityobj
(
	IdObj integer not null constraint PK_n5securityobj_IdObj primary key clustered,
	VersionId integer not null,
	pSOD integer not null,
	pUser integer not null
)
go

if exists (select * from sysobjects where name='n5miesiac')
	drop table n5miesiac
go

create table n5miesiac
(
	IdObj integer not null constraint PK_n5miesiac_IdObj primary key clustered,
	VersionId integer not null,
	nNumer integer not null,
	strNazwa varchar(32) not null
)
go

if exists (select * from sysobjects where name='n5dpc')
	drop table n5dpc
go

create table n5dpc
(
	IdObj integer not null constraint PK_n5dpc_IdObj primary key clustered,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	ePubType integer not null,
	eChannel integer not null,
	pDocTemplate integer not null,
	eFormat integer not null,
	strDevice varchar(128) not null,
	strConfig varchar(128) not null
)
go

if exists (select * from sysobjects where name='n5globprof')
	drop table n5globprof
go

create table n5globprof
(
	IdObj integer not null constraint PK_n5globprof_IdObj primary key clustered,
	VersionId integer not null,
	Indeks integer not null,
	Wartosc varchar(255) not null
)
go

if exists (select * from sysobjects where name='n5userprof')
	drop table n5userprof
go

create table n5userprof
(
	IdObj integer not null constraint PK_n5userprof_IdObj primary key clustered,
	VersionId integer not null,
	Indeks integer not null,
	Wartosc varchar(255) not null,
	pn5user integer not null
)
go

if exists (select * from sysobjects where name='n5globfile')
	drop table n5globfile
go

create table n5globfile
(
	IdObj integer not null constraint PK_n5globfile_IdObj primary key clustered,
	VersionId integer not null,
	nIndeks integer not null,
	-- [virtual] fPlik
)
go

if exists (select * from sysobjects where name='n5userfile')
	drop table n5userfile
go

create table n5userfile
(
	IdObj integer not null constraint PK_n5userfile_IdObj primary key clustered,
	VersionId integer not null,
	nIndeks integer not null,
	pUzytkownik integer not null,
	-- [virtual] fPlik
)
go


--end of tables

-- creating views
create view vlist_n5dokument_listLinks as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnumdok'=p.strNumDok
,'p_strnumdokobcy'=p.strNumDokObcy
,'p_strtematdokum'=p.strTematDokum
,'p_ptypdokumentu'=p.pTypDokumentu
,'p_ddatawewy'=p.dDataWeWy
,'p_ddatarejestracji'=p.dDataRejestracji
,'p_wpnadawca'=p.wpNadawca
,'p_wpnadawca_wrt'=p.wpNadawca_wrt
,'p_wpadresat'=p.wpAdresat
,'p_wpadresat_wrt'=p.wpAdresat_wrt
,'p_strstreszczenie'=p.strStreszczenie
,'p_nforma'=p.nForma
,'p_nliczbastron'=p.nLiczbaStron
,'p_strlokalizacja'=p.strLokalizacja
,'p_strfilename'=p.strFileName
,'p_strcheckoutfilename'=p.strCheckoutFileName
,'p_puzytkwypoz'=p.pUzytkWypoz
,'p_strcecha1'=p.strCecha1
,'p_strcecha2'=p.strCecha2
,'p_strcecha3'=p.strCecha3
,'p_nissecurity'=p.nIsSecurity
,'p_preplaces'=p.pReplaces
,'p_preplaced'=p.pReplaced
,'c_idobj'=c.IdObj
,'c_pdokument'=c.pDokument
 from n5dokument as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10117023
 join n5dokumentlinks as c on c.idobj = collections.idobj 
 go

create view vlist_n5zadanie_listZalaczniki as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_nstatus'=p.nStatus
,'p_ddatazlec'=p.dDataZlec
,'p_tczaszlec'=p.tCzasZlec
,'p_pzlecajacy'=p.pZlecajacy
,'p_epriorytet'=p.ePriorytet
,'p_etypterminrozp'=p.eTypterminRozp
,'p_ddataterminrozp'=p.dDataTerminRozp
,'p_tczasterminrozp'=p.tCzasTerminRozp
,'p_etypterminzak'=p.eTypterminZak
,'p_strtemat'=p.strTemat
,'p_stropis'=p.strOpis
,'p_nnaklad'=p.nNaklad
,'p_ptypdzialania'=p.pTypDzialania
,'p_pprocedura'=p.pProcedura
,'p_wrefszczegoly'=p.wrefSzczegoly
,'p_wrefszczegoly_wrt'=p.wrefSzczegoly_wrt
,'p_pnadzadanie'=p.pNadZadanie
,'p_ppopzadanie'=p.pPopZadanie
,'p_pwykonawca'=p.pWykonawca
,'p_ddatapow'=p.dDataPow
,'p_tczaspow'=p.tCzasPow
,'p_ddatarozp'=p.dDataRozp
,'p_tczasrozp'=p.tCzasRozp
,'p_nzaawansowanie'=p.nZaawansowanie
,'p_ddatazakon'=p.dDataZakon
,'p_tczaszakon'=p.tCzasZakon
,'p_struwagi'=p.strUwagi
,'p_ddatazamk'=p.dDataZamk
,'p_tczaszamk'=p.tCzasZamk
,'p_strcecha1'=p.strCecha1
,'p_strcecha2'=p.strCecha2
,'p_strcecha3'=p.strCecha3
,'p_ddataterminzak'=p.dDataTerminZak
,'p_tczasterminzak'=p.tCzasTerminZak
,'p_pklient'=p.pKlient
,'p_pschematdekretacji'=p.pSchematDekretacji
,'p_pdowksieg'=p.pDowKsieg
,'p_ddataprzyp'=p.dDataPrzyp
,'p_tczasprzyp'=p.tCzasPrzyp
,'p_nissecurity'=p.nIsSecurity
,'p_pklientpracownik'=p.pKlientPracownik
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_wrefzal'=c.wrefZal
,'c_wrefzal_wrt'=c.wrefZal_wrt
 from n5zadanie as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10119035
 join n5zadaniezal as c on c.idobj = collections.idobj 
 go

create view vlist_n5zadanie_listZadanieDW as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_nstatus'=p.nStatus
,'p_ddatazlec'=p.dDataZlec
,'p_tczaszlec'=p.tCzasZlec
,'p_pzlecajacy'=p.pZlecajacy
,'p_epriorytet'=p.ePriorytet
,'p_etypterminrozp'=p.eTypterminRozp
,'p_ddataterminrozp'=p.dDataTerminRozp
,'p_tczasterminrozp'=p.tCzasTerminRozp
,'p_etypterminzak'=p.eTypterminZak
,'p_strtemat'=p.strTemat
,'p_stropis'=p.strOpis
,'p_nnaklad'=p.nNaklad
,'p_ptypdzialania'=p.pTypDzialania
,'p_pprocedura'=p.pProcedura
,'p_wrefszczegoly'=p.wrefSzczegoly
,'p_wrefszczegoly_wrt'=p.wrefSzczegoly_wrt
,'p_pnadzadanie'=p.pNadZadanie
,'p_ppopzadanie'=p.pPopZadanie
,'p_pwykonawca'=p.pWykonawca
,'p_ddatapow'=p.dDataPow
,'p_tczaspow'=p.tCzasPow
,'p_ddatarozp'=p.dDataRozp
,'p_tczasrozp'=p.tCzasRozp
,'p_nzaawansowanie'=p.nZaawansowanie
,'p_ddatazakon'=p.dDataZakon
,'p_tczaszakon'=p.tCzasZakon
,'p_struwagi'=p.strUwagi
,'p_ddatazamk'=p.dDataZamk
,'p_tczaszamk'=p.tCzasZamk
,'p_strcecha1'=p.strCecha1
,'p_strcecha2'=p.strCecha2
,'p_strcecha3'=p.strCecha3
,'p_ddataterminzak'=p.dDataTerminZak
,'p_tczasterminzak'=p.tCzasTerminZak
,'p_pklient'=p.pKlient
,'p_pschematdekretacji'=p.pSchematDekretacji
,'p_pdowksieg'=p.pDowKsieg
,'p_ddataprzyp'=p.dDataPrzyp
,'p_tczasprzyp'=p.tCzasPrzyp
,'p_nissecurity'=p.nIsSecurity
,'p_pklientpracownik'=p.pKlientPracownik
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_pwykonawcadw'=c.pWykonawcaDW
,'c_ddatapow'=c.dDataPow
,'c_tczaspow'=c.tCzasPow
 from n5zadanie as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10119041
 join n5zadaniedw as c on c.idobj = collections.idobj 
 go

create view vlist_choicelist_listElement as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_ntypeid'=p.nTypeId
,'p_edynamic'=p.edynamic
,'p_nissecurity'=p.nIsSecurity
,'c_idobj'=c.IdObj
,'c_idelement'=c.IdElement
 from choicelist as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10124004
 join choicelistitem as c on c.idobj = collections.idobj 
 go

create view vlist_n5WizzardEmail_listDokumenty as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_pchoicelist'=p.pChoiceList
,'p_czarejestruj'=p.cZarejestruj
,'p_cwysylkaemail'=p.cWysylkaEmail
,'p_cwysylkafax'=p.cWysylkaFax
,'p_cwysylkawydruk'=p.cWysylkaWydruk
,'p_cwysylkaemailfax'=p.cWysylkaEmailFax
,'p_cwysylkaemailwydruk'=p.cWysylkaEmailWydruk
,'p_strtytul'=p.strTytul
,'p_strtresc'=p.strTresc
,'p_cszablon'=p.cSzablon
,'c_idobj'=c.IdObj
,'c_pdokument'=c.pDokument
 from n5WizzardEmail as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10127002
 join n5WizzardEmailDokumElem as c on c.idobj = collections.idobj 
 go

create view vlist_n5SendEmail_listDokumenty as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_wpnadawca'=p.wpNadawca
,'p_wpnadawca_wrt'=p.wpNadawca_wrt
,'c_idobj'=c.IdObj
,'c_pdokument'=c.pDokument
 from n5SendEmail as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10128002
 join n5WizzardEmailDokumElem as c on c.idobj = collections.idobj 
 go

create view vlist_n5sprzedaz_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_ddatawyst'=p.dDataWyst
,'p_ddatasprzed'=p.dDataSprzed
,'p_ddataplat'=p.dDataPlat
,'p_psposobplatnosci'=p.pSposobPlatnosci
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_esposvat'=p.eSposVAT
,'p_enettobrutto'=p.eNettoBrutto
,'p_pzadanie'=p.pZadanie
,'p_cursumanetto'=p.curSumaNetto
,'p_cursumavat'=p.curSumaVAT
,'p_cursumabrutto'=p.curSumaBrutto
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_ptransakcja'=p.pTransakcja
,'p_curnetto0'=p.curNetto0
,'p_curnettozw'=p.curNettoZw
,'p_curnettonp'=p.curNettoNp
,'p_curnetto2'=p.curNetto2
,'p_curvat2'=p.curVat2
,'p_curnetto3'=p.curNetto3
,'p_curvat3'=p.curVat3
,'p_curnetto4'=p.curNetto4
,'p_curvat4'=p.curVat4
,'p_curnetto7'=p.curNetto7
,'p_curvat7'=p.curVat7
,'p_curnetto12'=p.curNetto12
,'p_curvat12'=p.curVat12
,'p_curnetto17'=p.curNetto17
,'p_curvat17'=p.curVat17
,'p_curnetto22'=p.curNetto22
,'p_curvat22'=p.curVat22
,'p_ppopsprzed'=p.pPopSprzed
,'p_pfaktura'=p.pFaktura
,'p_cautocalc'=p.cAutoCalc
,'p_cursumawal'=p.curSumaWal
,'p_pwaluta'=p.pWaluta
,'p_prozlvat'=p.pRozlVat
,'p_pzamowienie'=p.pZamowienie
,'p_curkurs'=p.curKurs
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_curiloscopak'=c.curIloscOpak
,'c_popak'=c.pOpak
,'c_curcenabaznetto'=c.curCenaBazNetto
,'c_curcenabazbrutto'=c.curCenaBazBrutto
,'c_currabat'=c.curRabat
,'c_evat'=c.eVAT
,'c_curcenanetto'=c.curCenaNetto
,'c_curcenabrutto'=c.curCenaBrutto
,'c_curwartnetto'=c.curWartNetto
,'c_curvat'=c.curVAT
,'c_curcenabazowanettowal'=c.curCenaBazowaNettoWal
,'c_curcenanettowal'=c.curCenaNettoWal
,'c_curwartwal'=c.curWartWal
,'c_struwagi'=c.strUwagi
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
 from n5sprzedaz as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10129013
 join n5pozsprzedaz as c on c.idobj = collections.idobj 
 go

create view vlist_n5produkt_listOpakowania as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_strnazwamiedzynarodowa'=p.strNazwaMiedzynarodowa
,'p_strindeks'=p.strIndeks
,'p_strkodcelny'=p.strKodCelny
,'p_strkodpkwiu'=p.strKodPKWiU
,'p_evat'=p.eVAT
,'p_stropis'=p.strOpis
,'p_pulotka'=p.pUlotka
,'p_pinstrukcja'=p.pInstrukcja
,'p_pjednostkaewid'=p.pJednostkaEwid
,'p_eaktywny'=p.eAktywny
,'p_pgrupaprod'=p.pGrupaProd
,'p_strcecha1'=p.strCecha1
,'p_strcecha2'=p.strCecha2
,'p_strcecha3'=p.strCecha3
,'p_erodzaj'=p.eRodzaj
,'p_cprodukowalny'=p.cProdukowalny
,'c_idobj'=c.IdObj
,'c_strnazwa'=c.strNazwa
,'c_erodzaj'=c.eRodzaj
,'c_popakowaniejedn'=c.pOpakowanieJedn
,'c_currkrotnosc'=c.currKrotnosc
,'c_curilosc'=c.curIlosc
,'c_strean'=c.strEAN
,'c_curwaganetto'=c.curWagaNetto
,'c_curwagabrutto'=c.curWagaBrutto
,'c_pjednostkawagi'=c.pJednostkaWagi
,'c_curcenanetto1'=c.curCenaNetto1
,'c_curcenabrutto1'=c.curCenaBrutto1
,'c_curcenanetto2'=c.curCenaNetto2
,'c_curcenabrutto2'=c.curCenaBrutto2
,'c_curcenanetto3'=c.curCenaNetto3
,'c_curcenabrutto3'=c.curCenaBrutto3
,'c_curcenanetto4'=c.curCenaNetto4
,'c_curcenabrutto4'=c.curCenaBrutto4
,'c_curcenanetto5'=c.curCenaNetto5
,'c_curcenabrutto5'=c.curCenaBrutto5
,'c_curcenanetto6'=c.curCenaNetto6
,'c_curcenabrutto6'=c.curCenaBrutto6
,'c_pwaluta'=c.pWaluta
,'c_strkodopak'=c.strKodOpak
,'c_pjednopak'=c.pJednOpak
,'c_pzamiennik'=c.pZamiennik
,'c_strnazwamiedzynarodowa'=c.strNazwaMiedzynarodowa
,'c_curiloscmin'=c.curIloscMin
,'c_curiloscmax'=c.curIloscMax
,'c_curnarzutmin'=c.curNarzutMin
,'c_curnarzutmax'=c.curNarzutMax
,'c_curnarzutzal'=c.curNarzutZal
 from n5produkt as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10131012
 join n5opakowanie_produktu as c on c.idobj = collections.idobj 
 go

create view vlist_n5dowodksieg_listDekret as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_ddatarej'=p.dDataRej
,'p_ddataksieg'=p.dDataKsieg
,'p_strnrdok'=p.strNrDok
,'p_nnumdow'=p.nNumDow
,'p_stropis'=p.strOpis
,'p_etyp'=p.eTyp
,'p_estatus'=p.eStatus
,'p_puzytrej'=p.pUzytRej
,'p_prejestrdok'=p.pRejestrDok
,'p_wrefdokzrod'=p.wrefDokZrod
,'p_wrefdokzrod_wrt'=p.wrefDokZrod_wrt
,'p_cauto'=p.cAuto
,'c_idobj'=c.IdObj
,'c_pkonto'=c.pKonto
,'c_curwn'=c.curWn
,'c_curma'=c.curMa
,'c_ddataksieg'=c.dDataKsieg
,'c_stropis'=c.strOpis
,'c_etyp'=c.eTyp
,'c_estatus'=c.eStatus
,'c_ptransakcja'=c.pTransakcja
,'c_pkwalifikator'=c.pKwalifikator
,'c_cauto'=c.cAuto
 from n5dowodksieg as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10148008
 join n5dekret as c on c.idobj = collections.idobj 
 go

create view vlist_n5platnosc_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_ddataoper'=p.dDataOper
,'p_wrefpodmiot'=p.wrefPodmiot
,'p_wrefpodmiot_wrt'=p.wrefPodmiot_wrt
,'p_stropis'=p.strOpis
,'p_pzadanie'=p.pZadanie
,'p_puzytrej'=p.pUzytRej
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_strnrdok'=p.strNrDok
,'p_nnumoper'=p.nNumOper
,'p_curkwotapodm'=p.curKwotaPodm
,'p_curkurspodm'=p.curKursPodm
,'p_pwalutapodm'=p.pWalutaPodm
,'p_curkwotastan'=p.curKwotaStan
,'p_curkursewid'=p.curKursEwid
,'p_curkwotaewid'=p.curKwotaEwid
,'p_estatus'=p.eStatus
,'c_idobj'=c.IdObj
,'c_curpozkwotapodm'=c.curPozKwotaPodm
,'c_curpozkwotaewid'=c.curPozKwotaEwid
,'c_curpozkwotatrans'=c.curPozKwotaTrans
,'c_curpozkurspodm'=c.curPozKursPodm
,'c_curpozkursewid'=c.curPozKursEwid
,'c_ptransakcja'=c.pTransakcja
 from n5platnosc as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10150010
 join n5pozplatnosc as c on c.idobj = collections.idobj 
 go

create view vlist_n5dokmag_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_pdokmag'=p.pDokMag
,'p_nnumoper'=p.nNumOper
,'p_ntypdok'=p.nTypDok
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumamag'=p.curSumaMag
,'p_cursumaewid'=p.curSumaEwid
,'p_pmagzrod'=p.pMagZrod
,'p_pmagdocel'=p.pMagDocel
,'p_cautocalc'=p.cAutoCalc
,'p_wrefdokhandl'=p.wrefDokHandl
,'p_wrefdokhandl_wrt'=p.wrefDokHandl_wrt
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_ddatarezerw'=p.dDataRezerw
,'p_tczasrezerw'=p.tCzasRezerw
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_ntypdok'=c.nTypDok
,'c_pmagzrod'=c.pMagZrod
,'c_pmagdocel'=c.pMagDocel
,'c_pjednopak'=c.pJednOpak
,'c_curiloscopak'=c.curIloscOpak
,'c_pjednewid'=c.pJednEwid
,'c_curiloscewid'=c.curIloscEwid
,'c_curcenamag'=c.curCenaMag
,'c_curcenaewid'=c.curCenaEwid
,'c_curwartmag'=c.curWartMag
,'c_curwartewid'=c.curWartEwid
,'c_nnumopmagdost'=c.nNumOpMagDost
,'c_nlpdost'=c.nLpDost
,'c_struwagi'=c.strUwagi
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
,'c_ddatawazn'=c.dDataWazn
 from n5dokmag as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10162011
 join n5pozdokmag as c on c.idobj = collections.idobj 
 go

create view vlist_n5zamowienie_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_ddatawyst'=p.dDataWyst
,'p_ddataplat'=p.dDataPlat
,'p_ddatareal'=p.dDataReal
,'p_ddataakt'=p.dDataAkt
,'p_psposobplatnosci'=p.pSposobPlatnosci
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_enettobrutto'=p.eNettoBrutto
,'p_pzadanie'=p.pZadanie
,'p_cursumanetto'=p.curSumaNetto
,'p_cursumavat'=p.curSumaVAT
,'p_cursumabrutto'=p.curSumaBrutto
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumawal'=p.curSumaWal
,'p_pwaluta'=p.pWaluta
,'p_curkurs'=p.curKurs
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_curiloscopak'=c.curIloscOpak
,'c_popak'=c.pOpak
,'c_curcenabaznetto'=c.curCenaBazNetto
,'c_curcenabazbrutto'=c.curCenaBazBrutto
,'c_currabat'=c.curRabat
,'c_evat'=c.eVAT
,'c_curcenanetto'=c.curCenaNetto
,'c_curcenabrutto'=c.curCenaBrutto
,'c_curwartnetto'=c.curWartNetto
,'c_curvat'=c.curVAT
,'c_curcenabazowanettowal'=c.curCenaBazowaNettoWal
,'c_curcenanettowal'=c.curCenaNettoWal
,'c_curwartwal'=c.curWartWal
,'c_struwagi'=c.strUwagi
,'c_curiloscopakpoz'=c.curIloscOpakPoz
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
 from n5zamowienie as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10172013
 join n5pozzamowienie as c on c.idobj = collections.idobj 
 go

create view vlist_n5zakup_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_strnrdokobcy'=p.strNrDokObcy
,'p_ddatawyst'=p.dDataWyst
,'p_ddataotrzym'=p.dDataOtrzym
,'p_ddatazakupu'=p.dDataZakupu
,'p_ddataplat'=p.dDataPlat
,'p_psposobplatnosci'=p.pSposobPlatnosci
,'p_pdostawca'=p.pDostawca
,'p_pdostawca_jo'=p.pDostawca_JO
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_pzadanie'=p.pZadanie
,'p_cursumanetto'=p.curSumaNetto
,'p_cursumavat'=p.curSumaVAT
,'p_cursumabrutto'=p.curSumaBrutto
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_ptransakcja'=p.pTransakcja
,'p_curnetto0'=p.curNetto0
,'p_curnettozw'=p.curNettoZw
,'p_curnettonp'=p.curNettoNp
,'p_curnetto2'=p.curNetto2
,'p_curvat2'=p.curVat2
,'p_curnetto3'=p.curNetto3
,'p_curvat3'=p.curVat3
,'p_curnetto4'=p.curNetto4
,'p_curvat4'=p.curVat4
,'p_curnetto7'=p.curNetto7
,'p_curvat7'=p.curVat7
,'p_curnetto12'=p.curNetto12
,'p_curvat12'=p.curVat12
,'p_curnetto17'=p.curNetto17
,'p_curvat17'=p.curVat17
,'p_curnetto22'=p.curNetto22
,'p_curvat22'=p.curVat22
,'p_ppopzakup'=p.pPopZAkup
,'p_cursumawal'=p.curSumaWal
,'p_pwaluta'=p.pWaluta
,'p_ezwopsprz'=p.eZwOpSprz
,'p_etypzakup'=p.eTypZakup
,'p_prozlvat'=p.pRozlVat
,'p_curkurs'=p.curKurs
,'p_cautocalc'=p.cAutoCalc
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_curoplatyzagr'=p.curOplatyZagr
,'p_curclo'=p.curClo
,'p_curakcyza'=p.curAkcyza
,'p_curoplatykraj'=p.curOplatyKraj
,'p_curkurscelny'=p.curKursCelny
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_curiloscopak'=c.curIloscOpak
,'c_popak'=c.pOpak
,'c_evat'=c.eVAT
,'c_curcenanetto'=c.curCenaNetto
,'c_curcenabrutto'=c.curCenaBrutto
,'c_curwartnetto'=c.curWartNetto
,'c_curvat'=c.curVAT
,'c_curwartbrutto'=c.curWartBrutto
,'c_curcenanettowal'=c.curCenaNettoWal
,'c_struwagi'=c.strUwagi
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
 from n5zakup as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10176012
 join n5pozzakup as c on c.idobj = collections.idobj 
 go

create view vlist_n5recepta_listSurowce as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_strnorma'=p.strNorma
,'p_stropis'=p.strOpis
,'p_pwyrob'=p.pWyrob
,'p_pwyropak'=p.pWyrOpak
,'p_curiloscopak'=p.curIloscOpak
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_curiloscopak'=c.curIloscOpak
 from n5recepta as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10185007
 join n5pozrecepta as c on c.idobj = collections.idobj 
 go

create view vlist_n5recepta_listCzynnosci as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_strnorma'=p.strNorma
,'p_stropis'=p.strOpis
,'p_pwyrob'=p.pWyrob
,'p_pwyropak'=p.pWyrOpak
,'p_curiloscopak'=p.curIloscOpak
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_curiloscopak'=c.curIloscOpak
 from n5recepta as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10185008
 join n5pozrecepta as c on c.idobj = collections.idobj 
 go

create view vlist_n5zlecprod_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_pzadanie'=p.pZadanie
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pzamowienie'=p.pZamowienie
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_precepta'=c.pRecepta
,'c_curiloscopak'=c.curIloscOpak
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
 from n5zlecprod as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10187012
 join n5pozzlecprod as c on c.idobj = collections.idobj 
 go

create view vlist_n5plnaliczenie_listDokZrod as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_ppracownik'=p.pPracownik
,'p_ddatarej'=p.dDataRej
,'p_ddataod'=p.dDataOd
,'p_ddatado'=p.dDataDo
,'p_puzytrej'=p.pUzytRej
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_plistaplac'=p.pListaPlac
,'p_ptransakcja'=p.pTransakcja
,'p_pzadanie'=p.pZadanie
,'c_idobj'=c.IdObj
,'c_wrefdokument'=c.wrefDokument
,'c_wrefdokument_wrt'=c.wrefDokument_wrt
 from n5plnaliczenie as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10192012
 join n5plsklnalzrod as c on c.idobj = collections.idobj 
 go

create view vlist_n5plnaliczenie_listSkladnik as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_ppracownik'=p.pPracownik
,'p_ddatarej'=p.dDataRej
,'p_ddataod'=p.dDataOd
,'p_ddatado'=p.dDataDo
,'p_puzytrej'=p.pUzytRej
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_plistaplac'=p.pListaPlac
,'p_ptransakcja'=p.pTransakcja
,'p_pzadanie'=p.pZadanie
,'c_idobj'=c.IdObj
,'c_pschemat'=c.pSchemat
 from n5plnaliczenie as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10192013
 join n5plsklnal as c on c.idobj = collections.idobj 
 go

create view vlist_n5plumowa_listSkladnik as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_ppracownik'=p.pPracownik
,'p_ddatarej'=p.dDataRej
,'p_ddataod'=p.dDataOd
,'p_ddatado'=p.dDataDo
,'p_puzytrej'=p.pUzytRej
,'p_etypumowy'=p.eTypUmowy
,'p_pumowapop'=p.pUmowaPop
,'p_pkalendarz'=p.pKalendarz
,'c_idobj'=c.IdObj
,'c_pschemat'=c.pSchemat
 from n5plumowa as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10199007
 join n5plsklumowy as c on c.idobj = collections.idobj 
 go

create view vlist_n5realprod_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_nnumoper'=p.nNumOper
,'p_pwyrob'=p.pWyrob
,'p_popak'=p.pOpak
,'p_curiloscopak'=p.curIloscOpak
,'p_ddatawazn'=p.dDataWazn
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumamag'=p.curSumaMag
,'p_cursumaewid'=p.curSumaEwid
,'p_pmagazyn'=p.pMagazyn
,'p_cautocalc'=p.cAutoCalc
,'p_pzlecprod'=p.pZlecProd
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_pmagazyn'=c.pMagazyn
,'c_pjednopak'=c.pJednOpak
,'c_curiloscopak'=c.curIloscOpak
,'c_pjednewid'=c.pJednEwid
,'c_curiloscewid'=c.curIloscEwid
,'c_curcenamag'=c.curCenaMag
,'c_curcenaewid'=c.curCenaEwid
,'c_curwartmag'=c.curWartMag
,'c_curwartewid'=c.curWartEwid
,'c_nnumopmagdost'=c.nNumOpMagDost
,'c_nlpdost'=c.nLpDost
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
 from n5realprod as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10206009
 join n5pozrealprod as c on c.idobj = collections.idobj 
 go

create view vlist_n5bwinfo_listProdukt as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strtytul'=p.strTytul
,'p_strnrinfo'=p.strNrInfo
,'p_ddatarej'=p.dDataRej
,'p_ddataakt'=p.dDataAkt
,'p_estatus'=p.eStatus
,'p_pkategoria'=p.pKategoria
,'p_strobjaw'=p.strObjaw
,'p_strprzyczyna'=p.strPrzyczyna
,'p_strrozwiazanie'=p.strRozwiazanie
,'p_struwagi'=p.strUwagi
,'p_puzytrej'=p.pUzytRej
,'c_idobj'=c.IdObj
,'c_wpprodgrupa'=c.wpProdGrupa
,'c_wpprodgrupa_wrt'=c.wpProdGrupa_wrt
,'c_popak'=c.pOpak
 from n5bwinfo as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10211007
 join n5bwinfo_produkt as c on c.idobj = collections.idobj 
 go

create view vlist_n5bwinfo_listObjawyZal as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strtytul'=p.strTytul
,'p_strnrinfo'=p.strNrInfo
,'p_ddatarej'=p.dDataRej
,'p_ddataakt'=p.dDataAkt
,'p_estatus'=p.eStatus
,'p_pkategoria'=p.pKategoria
,'p_strobjaw'=p.strObjaw
,'p_strprzyczyna'=p.strPrzyczyna
,'p_strrozwiazanie'=p.strRozwiazanie
,'p_struwagi'=p.strUwagi
,'p_puzytrej'=p.pUzytRej
,'c_idobj'=c.IdObj
,'c_wrefzal'=c.wrefZal
,'c_wrefzal_wrt'=c.wrefZal_wrt
 from n5bwinfo as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10211009
 join n5bwinfo_zal as c on c.idobj = collections.idobj 
 go

create view vlist_n5bwinfo_listRozwiazanieZal as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strtytul'=p.strTytul
,'p_strnrinfo'=p.strNrInfo
,'p_ddatarej'=p.dDataRej
,'p_ddataakt'=p.dDataAkt
,'p_estatus'=p.eStatus
,'p_pkategoria'=p.pKategoria
,'p_strobjaw'=p.strObjaw
,'p_strprzyczyna'=p.strPrzyczyna
,'p_strrozwiazanie'=p.strRozwiazanie
,'p_struwagi'=p.strUwagi
,'p_puzytrej'=p.pUzytRej
,'c_idobj'=c.IdObj
,'c_wrefzal'=c.wrefZal
,'c_wrefzal_wrt'=c.wrefZal_wrt
 from n5bwinfo as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10211012
 join n5bwinfo_zal as c on c.idobj = collections.idobj 
 go

create view vlist_n5bwinfo_listUwagiZal as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strtytul'=p.strTytul
,'p_strnrinfo'=p.strNrInfo
,'p_ddatarej'=p.dDataRej
,'p_ddataakt'=p.dDataAkt
,'p_estatus'=p.eStatus
,'p_pkategoria'=p.pKategoria
,'p_strobjaw'=p.strObjaw
,'p_strprzyczyna'=p.strPrzyczyna
,'p_strrozwiazanie'=p.strRozwiazanie
,'p_struwagi'=p.strUwagi
,'p_puzytrej'=p.pUzytRej
,'c_idobj'=c.IdObj
,'c_wrefzal'=c.wrefZal
,'c_wrefzal_wrt'=c.wrefZal_wrt
 from n5bwinfo as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10211015
 join n5bwinfo_zal as c on c.idobj = collections.idobj 
 go

create view vlist_n5notaods_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_ddatawyst'=p.dDataWyst
,'p_pklient'=p.pKlient
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_cursumaods'=p.curSumaOds
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_ptransakcja'=p.pTransakcja
,'c_idobj'=c.IdObj
,'c_ptransakcja'=c.pTransakcja
,'c_curstawka'=c.curStawka
,'c_curkwotazal'=c.curKwotaZal
,'c_curkwotaods'=c.curKwotaOds
,'c_nliczbadni'=c.nLiczbaDni
,'c_ddatazaplaty'=c.dDataZaplaty
 from n5notaods as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10215007
 join n5poznotaods as c on c.idobj = collections.idobj 
 go

create view vlist_n5plkalcp_listPozycje as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_eaktywny'=p.eAktywny
,'p_struwagi'=p.strUwagi
,'c_idobj'=c.IdObj
,'c_cdnityg'=c.cDniTyg
,'c_ddataod'=c.dDataOd
,'c_ddatado'=c.dDataDo
,'c_tczasod'=c.tCzasOd
,'c_tczasdo'=c.tCzasDo
,'c_etypokresu'=c.eTypOkresu
 from n5plkalcp as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10218003
 join n5plpozkalcp as c on c.idobj = collections.idobj 
 go

create view vlist_SearchType_listFilter as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_nazwa'=p.Nazwa
,'p_resulttypeid'=p.ResultTypeId
,'p_ckind'=p.cKind
,'p_strkod'=p.strKod
,'p_nissecurity'=p.nIsSecurity
,'p_opis'=p.Opis
,'c_idobj'=c.IdObj
,'c_composedpath'=c.ComposedPath
,'c_cgroup'=c.cGroup
,'c_cdesc'=c.cDesc
,'c_clink'=c.cLink
 from SearchType as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10002003
 join SearchTypeItem as c on c.idobj = collections.idobj 
 go

create view vlist_SearchType_listOrder as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_nazwa'=p.Nazwa
,'p_resulttypeid'=p.ResultTypeId
,'p_ckind'=p.cKind
,'p_strkod'=p.strKod
,'p_nissecurity'=p.nIsSecurity
,'p_opis'=p.Opis
,'c_idobj'=c.IdObj
,'c_composedpath'=c.ComposedPath
,'c_cgroup'=c.cGroup
,'c_cdesc'=c.cDesc
,'c_clink'=c.cLink
 from SearchType as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10002004
 join SearchTypeItem as c on c.idobj = collections.idobj 
 go

create view vlist_SearchType_listColumn as select 
'coll_lp'=collections.lp,'p_idobj'=p.IdObj
,'p_nazwa'=p.Nazwa
,'p_resulttypeid'=p.ResultTypeId
,'p_ckind'=p.cKind
,'p_strkod'=p.strKod
,'p_nissecurity'=p.nIsSecurity
,'p_opis'=p.Opis
,'c_idobj'=c.IdObj
,'c_composedpath'=c.ComposedPath
,'c_cgroup'=c.cGroup
,'c_cdesc'=c.cDesc
,'c_clink'=c.cLink
 from SearchType as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10002005
 join SearchTypeItem as c on c.idobj = collections.idobj 
 go

-- creating standard stored procedures

-- table: n5wojewodztwo
if exists (select * from sysobjects where name='n5wojewodztwo_select')
	drop procedure n5wojewodztwo_select
go

create procedure n5wojewodztwo_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5wojewodztwo where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wojewodztwo_insert')
	drop procedure n5wojewodztwo_insert
go

create procedure n5wojewodztwo_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32)) with encryption as 
	insert into n5wojewodztwo values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5wojewodztwo_update')
	drop procedure n5wojewodztwo_update
go

create procedure n5wojewodztwo_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32)) with encryption as 
	update n5wojewodztwo set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wojewodztwo_delete')
	drop procedure n5wojewodztwo_delete
go

create procedure n5wojewodztwo_delete(@idobj_par integer) with encryption as 
	delete from n5wojewodztwo where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wojewodztwo_maxid')
	drop procedure n5wojewodztwo_maxid
go

create procedure n5wojewodztwo_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5wojewodztwo
go

if exists (select * from sysobjects where name='n5wojewodztwo_candel')
	drop procedure n5wojewodztwo_candel
go

create procedure n5wojewodztwo_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10111 as integer),idobj from n5miejscowosc where pWojewodztwo=@idobj_par
go

-- table: n5region
if exists (select * from sysobjects where name='n5region_select')
	drop procedure n5region_select
go

create procedure n5region_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5region where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5region_insert')
	drop procedure n5region_insert
go

create procedure n5region_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32)) with encryption as 
	insert into n5region values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5region_update')
	drop procedure n5region_update
go

create procedure n5region_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32)) with encryption as 
	update n5region set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5region_delete')
	drop procedure n5region_delete
go

create procedure n5region_delete(@idobj_par integer) with encryption as 
	delete from n5region where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5region_maxid')
	drop procedure n5region_maxid
go

create procedure n5region_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5region
go

if exists (select * from sysobjects where name='n5region_candel')
	drop procedure n5region_candel
go

create procedure n5region_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10111 as integer),idobj from n5miejscowosc where pRegion=@idobj_par
go

-- table: n5jednostka
if exists (select * from sysobjects where name='n5jednostka_select')
	drop procedure n5jednostka_select
go

create procedure n5jednostka_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(32) output,
	@strSkrot_par varchar(4) output,
	@nDokladnosc_par integer output,
	@eTyp_par integer output,
	@strNazwaMiedzynarodowa_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@nDokladnosc_par=nDokladnosc,
	@eTyp_par=eTyp,
	@strNazwaMiedzynarodowa_par=strNazwaMiedzynarodowa from n5jednostka where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jednostka_insert')
	drop procedure n5jednostka_insert
go

create procedure n5jednostka_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@strSkrot_par varchar(4),@nDokladnosc_par integer,@eTyp_par integer,@strNazwaMiedzynarodowa_par varchar(32)) with encryption as 
	insert into n5jednostka values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@nDokladnosc_par,@eTyp_par,@strNazwaMiedzynarodowa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5jednostka_update')
	drop procedure n5jednostka_update
go

create procedure n5jednostka_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@strSkrot_par varchar(4),@nDokladnosc_par integer,@eTyp_par integer,@strNazwaMiedzynarodowa_par varchar(32)) with encryption as 
	update n5jednostka set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	nDokladnosc=@nDokladnosc_par,
	eTyp=@eTyp_par,
	strNazwaMiedzynarodowa=@strNazwaMiedzynarodowa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jednostka_delete')
	drop procedure n5jednostka_delete
go

create procedure n5jednostka_delete(@idobj_par integer) with encryption as 
	delete from n5jednostka where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jednostka_maxid')
	drop procedure n5jednostka_maxid
go

create procedure n5jednostka_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5jednostka
go

if exists (select * from sysobjects where name='n5jednostka_candel')
	drop procedure n5jednostka_candel
go

create procedure n5jednostka_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10103 as integer),idobj from n5kraj where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pWalutaLimitu=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10118 as integer),idobj from n5grupaklient where pWalutaLimitu=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10130 as integer),idobj from n5opakowanie_produktu where pJednostkaWagi=@idobj_par
union
select TOP 5 'typeid'=cast(10130 as integer),idobj from n5opakowanie_produktu where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10130 as integer),idobj from n5opakowanie_produktu where pJednOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where pJednostkaEwid=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where wrefParam1=@idobj_par and wrefParam1_wrt=10102
union
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where pJednostka=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pWalutaPodm=@idobj_par
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10160 as integer),idobj from n5magazyn where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pJednOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pJednEwid=@idobj_par
union
select TOP 5 'typeid'=cast(10165 as integer),idobj from n5kurswalut where pWalZ=@idobj_par
union
select TOP 5 'typeid'=cast(10165 as integer),idobj from n5kurswalut where pWalN=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pWaluta=@idobj_par
union
select TOP 5 'typeid'=cast(10191 as integer),idobj from n5plstawka where pJednostka=@idobj_par
union
select TOP 5 'typeid'=cast(10196 as integer),idobj from n5plsubkonto where pJednostka=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pJednOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pJednEwid=@idobj_par
go

-- table: n5kraj
if exists (select * from sysobjects where name='n5kraj_select')
	drop procedure n5kraj_select
go

create procedure n5kraj_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@strSkrot_par varchar(20) output,
	@pWaluta_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@pWaluta_par=pWaluta from n5kraj where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kraj_insert')
	drop procedure n5kraj_insert
go

create procedure n5kraj_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strSkrot_par varchar(20),@pWaluta_par integer) with encryption as 
	insert into n5kraj values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@pWaluta_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5kraj_update')
	drop procedure n5kraj_update
go

create procedure n5kraj_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strSkrot_par varchar(20),@pWaluta_par integer) with encryption as 
	update n5kraj set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	pWaluta=@pWaluta_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kraj_delete')
	drop procedure n5kraj_delete
go

create procedure n5kraj_delete(@idobj_par integer) with encryption as 
	delete from n5kraj where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kraj_maxid')
	drop procedure n5kraj_maxid
go

create procedure n5kraj_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5kraj
go

if exists (select * from sysobjects where name='n5kraj_candel')
	drop procedure n5kraj_candel
go

create procedure n5kraj_candel(@idobj_par integer) with encryption as 
go

-- table: n5bank
if exists (select * from sysobjects where name='n5bank_select')
	drop procedure n5bank_select
go

create procedure n5bank_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@strOddzial_par varchar(128) output,
	@strKodRach_par varchar(32) output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@strOddzial_par=strOddzial,
	@strKodRach_par=strKodRach,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW from n5bank where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bank_insert')
	drop procedure n5bank_insert
go

create procedure n5bank_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strOddzial_par varchar(128),@strKodRach_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64)) with encryption as 
	insert into n5bank values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@strOddzial_par,@strKodRach_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strFax_par,@strEmail_par,@strWWW_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5bank_update')
	drop procedure n5bank_update
go

create procedure n5bank_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strOddzial_par varchar(128),@strKodRach_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64)) with encryption as 
	update n5bank set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	strOddzial=@strOddzial_par,
	strKodRach=@strKodRach_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bank_delete')
	drop procedure n5bank_delete
go

create procedure n5bank_delete(@idobj_par integer) with encryption as 
	delete from n5bank where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bank_maxid')
	drop procedure n5bank_maxid
go

create procedure n5bank_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5bank
go

if exists (select * from sysobjects where name='n5bank_candel')
	drop procedure n5bank_candel
go

create procedure n5bank_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10105 as integer),idobj from n5instytucja where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10105 as integer),idobj from n5instytucja where pBank2=@idobj_par
union
select TOP 5 'typeid'=cast(10105 as integer),idobj from n5instytucja where pBank3=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pBank2=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pBank3=@idobj_par
union
select TOP 5 'typeid'=cast(10109 as integer),idobj from n5pracownik where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pBank2=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pBank3=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where pBank2=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where pBank3=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pBank1=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pBank2=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pBank3=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10104
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10104
go

-- table: n5instytucja
if exists (select * from sysobjects where name='n5instytucja_select')
	drop procedure n5instytucja_select
go

create procedure n5instytucja_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@pTyp_par integer output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRachunek1_par varchar(32) output,
	@strPrzeznaczenie1_par varchar(64) output,
	@pBank1_par integer output,
	@strRachunek2_par varchar(32) output,
	@strPrzeznaczenie2_par varchar(64) output,
	@pBank2_par integer output,
	@strRachunek3_par varchar(32) output,
	@strPrzeznaczenie3_par varchar(64) output,
	@pBank3_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@pTyp_par=pTyp,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRachunek1_par=strRachunek1,
	@strPrzeznaczenie1_par=strPrzeznaczenie1,
	@pBank1_par=pBank1,
	@strRachunek2_par=strRachunek2,
	@strPrzeznaczenie2_par=strPrzeznaczenie2,
	@pBank2_par=pBank2,
	@strRachunek3_par=strRachunek3,
	@strPrzeznaczenie3_par=strPrzeznaczenie3,
	@pBank3_par=pBank3 from n5instytucja where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5instytucja_insert')
	drop procedure n5instytucja_insert
go

create procedure n5instytucja_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@pTyp_par integer,@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer) with encryption as 
	insert into n5instytucja values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@pTyp_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strFax_par,@strEmail_par,@strWWW_par,@strRachunek1_par,@strPrzeznaczenie1_par,@pBank1_par,@strRachunek2_par,@strPrzeznaczenie2_par,@pBank2_par,@strRachunek3_par,@strPrzeznaczenie3_par,@pBank3_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5instytucja_update')
	drop procedure n5instytucja_update
go

create procedure n5instytucja_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@pTyp_par integer,@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer) with encryption as 
	update n5instytucja set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	pTyp=@pTyp_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRachunek1=@strRachunek1_par,
	strPrzeznaczenie1=@strPrzeznaczenie1_par,
	pBank1=@pBank1_par,
	strRachunek2=@strRachunek2_par,
	strPrzeznaczenie2=@strPrzeznaczenie2_par,
	pBank2=@pBank2_par,
	strRachunek3=@strRachunek3_par,
	strPrzeznaczenie3=@strPrzeznaczenie3_par,
	pBank3=@pBank3_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5instytucja_delete')
	drop procedure n5instytucja_delete
go

create procedure n5instytucja_delete(@idobj_par integer) with encryption as 
	delete from n5instytucja where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5instytucja_maxid')
	drop procedure n5instytucja_maxid
go

create procedure n5instytucja_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5instytucja
go

if exists (select * from sysobjects where name='n5instytucja_candel')
	drop procedure n5instytucja_candel
go

create procedure n5instytucja_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10109 as integer),idobj from n5pracownik where pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pUrzadSkarbowyVAT=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pUrzadSkarbowyPD=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pZUS=@idobj_par
union
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where wrefPodmiotRozrach=@idobj_par and wrefPodmiotRozrach_wrt=10105
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10105
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10105
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pUrzadSkarbowy=@idobj_par
go

-- table: n5licencja
if exists (select * from sysobjects where name='n5licencja_select')
	drop procedure n5licencja_select
go

create procedure n5licencja_select(@idobj_par integer,@versionid_par integer output,
	@strKod_par varchar(8) output,
	@strIdUser_par varchar(20) output,
	@dDataWazn_par datetime output,
	@nStanowiska_par integer output,
	@strKontrola_par varchar(512) output,
	@strLogin_par varchar(32) output,
	@strHaslo_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strKod_par=strKod,
	@strIdUser_par=strIdUser,
	@dDataWazn_par=dDataWazn,
	@nStanowiska_par=nStanowiska,
	@strKontrola_par=strKontrola,
	@strLogin_par=strLogin,
	@strHaslo_par=strHaslo from n5licencja where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5licencja_insert')
	drop procedure n5licencja_insert
go

create procedure n5licencja_insert(@idobj_par integer,@versionid_par integer,@strKod_par varchar(8),@strIdUser_par varchar(20),@dDataWazn_par datetime,@nStanowiska_par integer,@strKontrola_par varchar(512),@strLogin_par varchar(32),@strHaslo_par varchar(32)) with encryption as 
	insert into n5licencja values(@idobj_par,@versionid_par,@strKod_par,@strIdUser_par,@dDataWazn_par,@nStanowiska_par,@strKontrola_par,@strLogin_par,@strHaslo_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5licencja_update')
	drop procedure n5licencja_update
go

create procedure n5licencja_update(@idobj_par integer,@versionid_par integer,@strKod_par varchar(8),@strIdUser_par varchar(20),@dDataWazn_par datetime,@nStanowiska_par integer,@strKontrola_par varchar(512),@strLogin_par varchar(32),@strHaslo_par varchar(32)) with encryption as 
	update n5licencja set VersionId=@versionid_par,
	strKod=@strKod_par,
	strIdUser=@strIdUser_par,
	dDataWazn=@dDataWazn_par,
	nStanowiska=@nStanowiska_par,
	strKontrola=@strKontrola_par,
	strLogin=@strLogin_par,
	strHaslo=@strHaslo_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5licencja_delete')
	drop procedure n5licencja_delete
go

create procedure n5licencja_delete(@idobj_par integer) with encryption as 
	delete from n5licencja where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5licencja_maxid')
	drop procedure n5licencja_maxid
go

create procedure n5licencja_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5licencja
go

if exists (select * from sysobjects where name='n5licencja_candel')
	drop procedure n5licencja_candel
go

create procedure n5licencja_candel(@idobj_par integer) with encryption as 
go

-- table: n5uzytkownik
if exists (select * from sysobjects where name='n5uzytkownik_select')
	drop procedure n5uzytkownik_select
go

create procedure n5uzytkownik_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@strLogin_par varchar(20) output,
	@strHaslo_par varchar(20) output,
	@strMail_par varchar(64) output,
	@strTelefon_par varchar(20) output,
	@eAktywny_par integer output,
	@pWykonawca_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strLogin_par=strLogin,
	@strHaslo_par=strHaslo,
	@strMail_par=strMail,
	@strTelefon_par=strTelefon,
	@eAktywny_par=eAktywny,
	@pWykonawca_par=pWykonawca from n5uzytkownik where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5uzytkownik_insert')
	drop procedure n5uzytkownik_insert
go

create procedure n5uzytkownik_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strLogin_par varchar(20),@strHaslo_par varchar(20),@strMail_par varchar(64),@strTelefon_par varchar(20),@eAktywny_par integer,@pWykonawca_par integer) with encryption as 
	insert into n5uzytkownik values(@idobj_par,@versionid_par,@strNazwa_par,@strLogin_par,@strHaslo_par,@strMail_par,@strTelefon_par,@eAktywny_par,@pWykonawca_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5uzytkownik_update')
	drop procedure n5uzytkownik_update
go

create procedure n5uzytkownik_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strLogin_par varchar(20),@strHaslo_par varchar(20),@strMail_par varchar(64),@strTelefon_par varchar(20),@eAktywny_par integer,@pWykonawca_par integer) with encryption as 
	update n5uzytkownik set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strLogin=@strLogin_par,
	strHaslo=@strHaslo_par,
	strMail=@strMail_par,
	strTelefon=@strTelefon_par,
	eAktywny=@eAktywny_par,
	pWykonawca=@pWykonawca_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5uzytkownik_delete')
	drop procedure n5uzytkownik_delete
go

create procedure n5uzytkownik_delete(@idobj_par integer) with encryption as 
	delete from n5uzytkownik where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5uzytkownik_maxid')
	drop procedure n5uzytkownik_maxid
go

create procedure n5uzytkownik_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5uzytkownik
go

if exists (select * from sysobjects where name='n5uzytkownik_candel')
	drop procedure n5uzytkownik_candel
go

create procedure n5uzytkownik_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pUzytkWypoz=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10188 as integer),idobj from n5eventlog where pUser=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10211 as integer),idobj from n5bwinfo where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10006 as integer),idobj from n5securityobj where pUser=@idobj_par
union
select TOP 5 'typeid'=cast(10011 as integer),idobj from n5userprof where pn5user=@idobj_par
union
select TOP 5 'typeid'=cast(10013 as integer),idobj from n5userfile where pUzytkownik=@idobj_par
go

-- table: n5klient
if exists (select * from sysobjects where name='n5klient_select')
	drop procedure n5klient_select
go

create procedure n5klient_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@strIndeks_par varchar(32) output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strTel4_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRejestr_par varchar(64) output,
	@strSad_par varchar(128) output,
	@strNIP_par varchar(20) output,
	@strREGON_par varchar(20) output,
	@pBranza_par integer output,
	@eTypDT_par integer output,
	@strNrDokTozsamosci_par varchar(20) output,
	@strRachunek1_par varchar(32) output,
	@strPrzeznaczenie1_par varchar(64) output,
	@pBank1_par integer output,
	@strRachunek2_par varchar(32) output,
	@strPrzeznaczenie2_par varchar(64) output,
	@pBank2_par integer output,
	@strRachunek3_par varchar(32) output,
	@strPrzeznaczenie3_par varchar(64) output,
	@pBank3_par integer output,
	@nLiczbaPracownikow_par integer output,
	@eAktywny_par integer output,
	@eKlasaKlienta_par integer output,
	@pWaluta_par integer output,
	@strUwagi_par varchar(255) output,
	@strUpodobania_par varchar(255) output,
	@strCecha1_par varchar(128) output,
	@strCecha2_par varchar(128) output,
	@strCecha3_par varchar(128) output,
	@strNazwisko_par varchar(128) output,
	@strImie_par varchar(32) output,
	@dDataUr_par datetime output,
	@strMiejsceUr_par varchar(32) output,
	@strPESEL_par varchar(20) output,
	@ePlec_par integer output,
	@nWiek_par integer output,
	@strWydzial_par varchar(128) output,
	@pPracownik_par integer output,
	@pGrupaKlient_par integer output,
	@ePrywat_par integer output,
	@strUlicaSDB_par varchar(64) output,
	@strNrDomuSDB_par varchar(8) output,
	@strNrLokaluSDB_par varchar(8) output,
	@strKodSDB_par varchar(8) output,
	@strPocztaSDB_par varchar(64) output,
	@pMiejscowoscSDB_par integer output,
	@curSzerGeogrSDB_par decimal(12,2) output,
	@curDlugGeogrSDB_par decimal(12,2) output,
	@eWiarFin_par integer output,
	@curLimitKred_par decimal(12,2) output,
	@pWalutaLimitu_par integer output,
	@strHaslo_par varchar(32) output,
	@curObroty_par decimal(12,2) output,
	@nOcena_par integer output,
	@dDataOceny_par datetime output,
	@pSposobPlatnosci_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@strIndeks_par=strIndeks,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strTel4_par=strTel4,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRejestr_par=strRejestr,
	@strSad_par=strSad,
	@strNIP_par=strNIP,
	@strREGON_par=strREGON,
	@pBranza_par=pBranza,
	@eTypDT_par=eTypDT,
	@strNrDokTozsamosci_par=strNrDokTozsamosci,
	@strRachunek1_par=strRachunek1,
	@strPrzeznaczenie1_par=strPrzeznaczenie1,
	@pBank1_par=pBank1,
	@strRachunek2_par=strRachunek2,
	@strPrzeznaczenie2_par=strPrzeznaczenie2,
	@pBank2_par=pBank2,
	@strRachunek3_par=strRachunek3,
	@strPrzeznaczenie3_par=strPrzeznaczenie3,
	@pBank3_par=pBank3,
	@nLiczbaPracownikow_par=nLiczbaPracownikow,
	@eAktywny_par=eAktywny,
	@eKlasaKlienta_par=eKlasaKlienta,
	@pWaluta_par=pWaluta,
	@strUwagi_par=strUwagi,
	@strUpodobania_par=strUpodobania,
	@strCecha1_par=strCecha1,
	@strCecha2_par=strCecha2,
	@strCecha3_par=strCecha3,
	@strNazwisko_par=strNazwisko,
	@strImie_par=strImie,
	@dDataUr_par=dDataUr,
	@strMiejsceUr_par=strMiejsceUr,
	@strPESEL_par=strPESEL,
	@ePlec_par=ePlec,
	@nWiek_par=nWiek,
	@strWydzial_par=strWydzial,
	@pPracownik_par=pPracownik,
	@pGrupaKlient_par=pGrupaKlient,
	@ePrywat_par=ePrywat,
	@strUlicaSDB_par=strUlicaSDB,
	@strNrDomuSDB_par=strNrDomuSDB,
	@strNrLokaluSDB_par=strNrLokaluSDB,
	@strKodSDB_par=strKodSDB,
	@strPocztaSDB_par=strPocztaSDB,
	@pMiejscowoscSDB_par=pMiejscowoscSDB,
	@curSzerGeogrSDB_par=curSzerGeogrSDB,
	@curDlugGeogrSDB_par=curDlugGeogrSDB,
	@eWiarFin_par=eWiarFin,
	@curLimitKred_par=curLimitKred,
	@pWalutaLimitu_par=pWalutaLimitu,
	@strHaslo_par=strHaslo,
	@curObroty_par=curObroty,
	@nOcena_par=nOcena,
	@dDataOceny_par=dDataOceny,
	@pSposobPlatnosci_par=pSposobPlatnosci from n5klient where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_insert')
	drop procedure n5klient_insert
go

create procedure n5klient_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strIndeks_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRejestr_par varchar(64),@strSad_par varchar(128),@strNIP_par varchar(20),@strREGON_par varchar(20),@pBranza_par integer,@eTypDT_par integer,@strNrDokTozsamosci_par varchar(20),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@nLiczbaPracownikow_par integer,@eAktywny_par integer,@eKlasaKlienta_par integer,@pWaluta_par integer,@strUwagi_par varchar(255),@strUpodobania_par varchar(255),@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@strNazwisko_par varchar(128),@strImie_par varchar(32),@dDataUr_par datetime,@strMiejsceUr_par varchar(32),@strPESEL_par varchar(20),@ePlec_par integer,@nWiek_par integer,@strWydzial_par varchar(128),@pPracownik_par integer,@pGrupaKlient_par integer,@ePrywat_par integer,@strUlicaSDB_par varchar(64),@strNrDomuSDB_par varchar(8),@strNrLokaluSDB_par varchar(8),@strKodSDB_par varchar(8),@strPocztaSDB_par varchar(64),@pMiejscowoscSDB_par integer,@curSzerGeogrSDB_par decimal(12,2),@curDlugGeogrSDB_par decimal(12,2),@eWiarFin_par integer,@curLimitKred_par decimal(12,2),@pWalutaLimitu_par integer,@strHaslo_par varchar(32),@curObroty_par decimal(12,2),@nOcena_par integer,@dDataOceny_par datetime,@pSposobPlatnosci_par integer) with encryption as 
	insert into n5klient values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@strIndeks_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strTel4_par,@strFax_par,@strEmail_par,@strWWW_par,@strRejestr_par,@strSad_par,@strNIP_par,@strREGON_par,@pBranza_par,@eTypDT_par,@strNrDokTozsamosci_par,@strRachunek1_par,@strPrzeznaczenie1_par,@pBank1_par,@strRachunek2_par,@strPrzeznaczenie2_par,@pBank2_par,@strRachunek3_par,@strPrzeznaczenie3_par,@pBank3_par,@nLiczbaPracownikow_par,@eAktywny_par,@eKlasaKlienta_par,@pWaluta_par,@strUwagi_par,@strUpodobania_par,@strCecha1_par,@strCecha2_par,@strCecha3_par,@strNazwisko_par,@strImie_par,@dDataUr_par,@strMiejsceUr_par,@strPESEL_par,@ePlec_par,@nWiek_par,@strWydzial_par,@pPracownik_par,@pGrupaKlient_par,@ePrywat_par,@strUlicaSDB_par,@strNrDomuSDB_par,@strNrLokaluSDB_par,@strKodSDB_par,@strPocztaSDB_par,@pMiejscowoscSDB_par,@curSzerGeogrSDB_par,@curDlugGeogrSDB_par,@eWiarFin_par,@curLimitKred_par,@pWalutaLimitu_par,@strHaslo_par,@curObroty_par,@nOcena_par,@dDataOceny_par,@pSposobPlatnosci_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_update')
	drop procedure n5klient_update
go

create procedure n5klient_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strIndeks_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRejestr_par varchar(64),@strSad_par varchar(128),@strNIP_par varchar(20),@strREGON_par varchar(20),@pBranza_par integer,@eTypDT_par integer,@strNrDokTozsamosci_par varchar(20),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@nLiczbaPracownikow_par integer,@eAktywny_par integer,@eKlasaKlienta_par integer,@pWaluta_par integer,@strUwagi_par varchar(255),@strUpodobania_par varchar(255),@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@strNazwisko_par varchar(128),@strImie_par varchar(32),@dDataUr_par datetime,@strMiejsceUr_par varchar(32),@strPESEL_par varchar(20),@ePlec_par integer,@nWiek_par integer,@strWydzial_par varchar(128),@pPracownik_par integer,@pGrupaKlient_par integer,@ePrywat_par integer,@strUlicaSDB_par varchar(64),@strNrDomuSDB_par varchar(8),@strNrLokaluSDB_par varchar(8),@strKodSDB_par varchar(8),@strPocztaSDB_par varchar(64),@pMiejscowoscSDB_par integer,@curSzerGeogrSDB_par decimal(12,2),@curDlugGeogrSDB_par decimal(12,2),@eWiarFin_par integer,@curLimitKred_par decimal(12,2),@pWalutaLimitu_par integer,@strHaslo_par varchar(32),@curObroty_par decimal(12,2),@nOcena_par integer,@dDataOceny_par datetime,@pSposobPlatnosci_par integer) with encryption as 
	update n5klient set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	strIndeks=@strIndeks_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strTel4=@strTel4_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRejestr=@strRejestr_par,
	strSad=@strSad_par,
	strNIP=@strNIP_par,
	strREGON=@strREGON_par,
	pBranza=@pBranza_par,
	eTypDT=@eTypDT_par,
	strNrDokTozsamosci=@strNrDokTozsamosci_par,
	strRachunek1=@strRachunek1_par,
	strPrzeznaczenie1=@strPrzeznaczenie1_par,
	pBank1=@pBank1_par,
	strRachunek2=@strRachunek2_par,
	strPrzeznaczenie2=@strPrzeznaczenie2_par,
	pBank2=@pBank2_par,
	strRachunek3=@strRachunek3_par,
	strPrzeznaczenie3=@strPrzeznaczenie3_par,
	pBank3=@pBank3_par,
	nLiczbaPracownikow=@nLiczbaPracownikow_par,
	eAktywny=@eAktywny_par,
	eKlasaKlienta=@eKlasaKlienta_par,
	pWaluta=@pWaluta_par,
	strUwagi=@strUwagi_par,
	strUpodobania=@strUpodobania_par,
	strCecha1=@strCecha1_par,
	strCecha2=@strCecha2_par,
	strCecha3=@strCecha3_par,
	strNazwisko=@strNazwisko_par,
	strImie=@strImie_par,
	dDataUr=@dDataUr_par,
	strMiejsceUr=@strMiejsceUr_par,
	strPESEL=@strPESEL_par,
	ePlec=@ePlec_par,
	nWiek=@nWiek_par,
	strWydzial=@strWydzial_par,
	pPracownik=@pPracownik_par,
	pGrupaKlient=@pGrupaKlient_par,
	ePrywat=@ePrywat_par,
	strUlicaSDB=@strUlicaSDB_par,
	strNrDomuSDB=@strNrDomuSDB_par,
	strNrLokaluSDB=@strNrLokaluSDB_par,
	strKodSDB=@strKodSDB_par,
	strPocztaSDB=@strPocztaSDB_par,
	pMiejscowoscSDB=@pMiejscowoscSDB_par,
	curSzerGeogrSDB=@curSzerGeogrSDB_par,
	curDlugGeogrSDB=@curDlugGeogrSDB_par,
	eWiarFin=@eWiarFin_par,
	curLimitKred=@curLimitKred_par,
	pWalutaLimitu=@pWalutaLimitu_par,
	strHaslo=@strHaslo_par,
	curObroty=@curObroty_par,
	nOcena=@nOcena_par,
	dDataOceny=@dDataOceny_par,
	pSposobPlatnosci=@pSposobPlatnosci_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_delete')
	drop procedure n5klient_delete
go

create procedure n5klient_delete(@idobj_par integer) with encryption as 
	delete from n5klient where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_maxid')
	drop procedure n5klient_maxid
go

create procedure n5klient_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5klient
go

if exists (select * from sysobjects where name='n5klient_candel')
	drop procedure n5klient_candel
go

create procedure n5klient_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10112 as integer),idobj from n5klient_pracownik where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpNadawca=@idobj_par and wpNadawca_wrt=10108
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpAdresat=@idobj_par and wpAdresat_wrt=10108
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10122 as integer),idobj from n5wykonawca where wrefObiekt=@idobj_par and wrefObiekt_wrt=10108
union
select TOP 5 'typeid'=cast(10128 as integer),idobj from n5SendEmail where wpNadawca=@idobj_par and wpNadawca_wrt=10108
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10134 as integer),idobj from n5pkpir where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where wrefPodmiotRozrach=@idobj_par and wrefPodmiotRozrach_wrt=10108
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10108
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10108
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pDostawca=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpKlientGrupa=@idobj_par and wpKlientGrupa_wrt=10108
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pKlient=@idobj_par
go

-- table: n5pracownik
if exists (select * from sysobjects where name='n5pracownik_select')
	drop procedure n5pracownik_select
go

create procedure n5pracownik_select(@idobj_par integer,@versionid_par integer output,
	@strNazwisko_par varchar(32) output,
	@strImie_par varchar(32) output,
	@strImie2_par varchar(32) output,
	@dDataUr_par datetime output,
	@strMiejsceUr_par varchar(32) output,
	@strPESEL_par varchar(20) output,
	@strNIP_par varchar(20) output,
	@ePlec_par integer output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strTel4_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRachunek1_par varchar(32) output,
	@pBank1_par integer output,
	@eAktywny_par integer output,
	@dDataZatrudnienia_par datetime output,
	@dDataZwolnienia_par datetime output,
	@strStanowisko_par varchar(64) output,
	@eTypDT_par integer output,
	@strNrDokTozsamosci_par varchar(20) output,
	@strEmail2_par varchar(64) output,
	@pJednostkaOrg_par integer output,
	@pUrzadSkarbowy_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwisko_par=strNazwisko,
	@strImie_par=strImie,
	@strImie2_par=strImie2,
	@dDataUr_par=dDataUr,
	@strMiejsceUr_par=strMiejsceUr,
	@strPESEL_par=strPESEL,
	@strNIP_par=strNIP,
	@ePlec_par=ePlec,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strTel4_par=strTel4,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRachunek1_par=strRachunek1,
	@pBank1_par=pBank1,
	@eAktywny_par=eAktywny,
	@dDataZatrudnienia_par=dDataZatrudnienia,
	@dDataZwolnienia_par=dDataZwolnienia,
	@strStanowisko_par=strStanowisko,
	@eTypDT_par=eTypDT,
	@strNrDokTozsamosci_par=strNrDokTozsamosci,
	@strEmail2_par=strEmail2,
	@pJednostkaOrg_par=pJednostkaOrg,
	@pUrzadSkarbowy_par=pUrzadSkarbowy from n5pracownik where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pracownik_insert')
	drop procedure n5pracownik_insert
go

create procedure n5pracownik_insert(@idobj_par integer,@versionid_par integer,@strNazwisko_par varchar(32),@strImie_par varchar(32),@strImie2_par varchar(32),@dDataUr_par datetime,@strMiejsceUr_par varchar(32),@strPESEL_par varchar(20),@strNIP_par varchar(20),@ePlec_par integer,@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@pBank1_par integer,@eAktywny_par integer,@dDataZatrudnienia_par datetime,@dDataZwolnienia_par datetime,@strStanowisko_par varchar(64),@eTypDT_par integer,@strNrDokTozsamosci_par varchar(20),@strEmail2_par varchar(64),@pJednostkaOrg_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	insert into n5pracownik values(@idobj_par,@versionid_par,@strNazwisko_par,@strImie_par,@strImie2_par,@dDataUr_par,@strMiejsceUr_par,@strPESEL_par,@strNIP_par,@ePlec_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strTel4_par,@strFax_par,@strEmail_par,@strWWW_par,@strRachunek1_par,@pBank1_par,@eAktywny_par,@dDataZatrudnienia_par,@dDataZwolnienia_par,@strStanowisko_par,@eTypDT_par,@strNrDokTozsamosci_par,@strEmail2_par,@pJednostkaOrg_par,@pUrzadSkarbowy_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pracownik_update')
	drop procedure n5pracownik_update
go

create procedure n5pracownik_update(@idobj_par integer,@versionid_par integer,@strNazwisko_par varchar(32),@strImie_par varchar(32),@strImie2_par varchar(32),@dDataUr_par datetime,@strMiejsceUr_par varchar(32),@strPESEL_par varchar(20),@strNIP_par varchar(20),@ePlec_par integer,@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@pBank1_par integer,@eAktywny_par integer,@dDataZatrudnienia_par datetime,@dDataZwolnienia_par datetime,@strStanowisko_par varchar(64),@eTypDT_par integer,@strNrDokTozsamosci_par varchar(20),@strEmail2_par varchar(64),@pJednostkaOrg_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	update n5pracownik set VersionId=@versionid_par,
	strNazwisko=@strNazwisko_par,
	strImie=@strImie_par,
	strImie2=@strImie2_par,
	dDataUr=@dDataUr_par,
	strMiejsceUr=@strMiejsceUr_par,
	strPESEL=@strPESEL_par,
	strNIP=@strNIP_par,
	ePlec=@ePlec_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strTel4=@strTel4_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRachunek1=@strRachunek1_par,
	pBank1=@pBank1_par,
	eAktywny=@eAktywny_par,
	dDataZatrudnienia=@dDataZatrudnienia_par,
	dDataZwolnienia=@dDataZwolnienia_par,
	strStanowisko=@strStanowisko_par,
	eTypDT=@eTypDT_par,
	strNrDokTozsamosci=@strNrDokTozsamosci_par,
	strEmail2=@strEmail2_par,
	pJednostkaOrg=@pJednostkaOrg_par,
	pUrzadSkarbowy=@pUrzadSkarbowy_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pracownik_delete')
	drop procedure n5pracownik_delete
go

create procedure n5pracownik_delete(@idobj_par integer) with encryption as 
	delete from n5pracownik where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pracownik_maxid')
	drop procedure n5pracownik_maxid
go

create procedure n5pracownik_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pracownik
go

if exists (select * from sysobjects where name='n5pracownik_candel')
	drop procedure n5pracownik_candel
go

create procedure n5pracownik_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10112 as integer),idobj from n5klient_pracownik where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpNadawca=@idobj_par and wpNadawca_wrt=10109
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpAdresat=@idobj_par and wpAdresat_wrt=10109
union
select TOP 5 'typeid'=cast(10122 as integer),idobj from n5wykonawca where wrefObiekt=@idobj_par and wrefObiekt_wrt=10109
union
select TOP 5 'typeid'=cast(10128 as integer),idobj from n5SendEmail where wpNadawca=@idobj_par and wpNadawca_wrt=10109
union
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where wrefPodmiotRozrach=@idobj_par and wrefPodmiotRozrach_wrt=10109
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10109
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10109
union
select TOP 5 'typeid'=cast(10179 as integer),idobj from n5srtrw where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pPracownik=@idobj_par
go

-- table: n5firma
if exists (select * from sysobjects where name='n5firma_select')
	drop procedure n5firma_select
go

create procedure n5firma_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strFax_par varchar(20) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRejestr_par varchar(64) output,
	@strSad_par varchar(128) output,
	@strWydzial_par varchar(128) output,
	@eForma_par integer output,
	@strNIP_par varchar(20) output,
	@strREGON_par varchar(20) output,
	@strEKD_par varchar(20) output,
	@strRachunek1_par varchar(32) output,
	@pBank1_par integer output,
	@strPrzeznaczenie1_par varchar(64) output,
	@strRachunek2_par varchar(32) output,
	@pBank2_par integer output,
	@strPrzeznaczenie2_par varchar(64) output,
	@strRachunek3_par varchar(32) output,
	@strPrzeznaczenie3_par varchar(64) output,
	@pWaluta_par integer output,
	@pBank3_par integer output,
	@pUrzadSkarbowyVAT_par integer output,
	@pUrzadSkarbowyPD_par integer output,
	@pZUS_par integer output,
	@pMainJO_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strFax_par=strFax,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRejestr_par=strRejestr,
	@strSad_par=strSad,
	@strWydzial_par=strWydzial,
	@eForma_par=eForma,
	@strNIP_par=strNIP,
	@strREGON_par=strREGON,
	@strEKD_par=strEKD,
	@strRachunek1_par=strRachunek1,
	@pBank1_par=pBank1,
	@strPrzeznaczenie1_par=strPrzeznaczenie1,
	@strRachunek2_par=strRachunek2,
	@pBank2_par=pBank2,
	@strPrzeznaczenie2_par=strPrzeznaczenie2,
	@strRachunek3_par=strRachunek3,
	@strPrzeznaczenie3_par=strPrzeznaczenie3,
	@pWaluta_par=pWaluta,
	@pBank3_par=pBank3,
	@pUrzadSkarbowyVAT_par=pUrzadSkarbowyVAT,
	@pUrzadSkarbowyPD_par=pUrzadSkarbowyPD,
	@pZUS_par=pZUS,
	@pMainJO_par=pMainJO from n5firma where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5firma_insert')
	drop procedure n5firma_insert
go

create procedure n5firma_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strFax_par varchar(20),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRejestr_par varchar(64),@strSad_par varchar(128),@strWydzial_par varchar(128),@eForma_par integer,@strNIP_par varchar(20),@strREGON_par varchar(20),@strEKD_par varchar(20),@strRachunek1_par varchar(32),@pBank1_par integer,@strPrzeznaczenie1_par varchar(64),@strRachunek2_par varchar(32),@pBank2_par integer,@strPrzeznaczenie2_par varchar(64),@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pWaluta_par integer,@pBank3_par integer,@pUrzadSkarbowyVAT_par integer,@pUrzadSkarbowyPD_par integer,@pZUS_par integer,@pMainJO_par integer) with encryption as 
	insert into n5firma values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strFax_par,@strTel1_par,@strTel2_par,@strTel3_par,@strEmail_par,@strWWW_par,@strRejestr_par,@strSad_par,@strWydzial_par,@eForma_par,@strNIP_par,@strREGON_par,@strEKD_par,@strRachunek1_par,@pBank1_par,@strPrzeznaczenie1_par,@strRachunek2_par,@pBank2_par,@strPrzeznaczenie2_par,@strRachunek3_par,@strPrzeznaczenie3_par,@pWaluta_par,@pBank3_par,@pUrzadSkarbowyVAT_par,@pUrzadSkarbowyPD_par,@pZUS_par,@pMainJO_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5firma_update')
	drop procedure n5firma_update
go

create procedure n5firma_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strFax_par varchar(20),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRejestr_par varchar(64),@strSad_par varchar(128),@strWydzial_par varchar(128),@eForma_par integer,@strNIP_par varchar(20),@strREGON_par varchar(20),@strEKD_par varchar(20),@strRachunek1_par varchar(32),@pBank1_par integer,@strPrzeznaczenie1_par varchar(64),@strRachunek2_par varchar(32),@pBank2_par integer,@strPrzeznaczenie2_par varchar(64),@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pWaluta_par integer,@pBank3_par integer,@pUrzadSkarbowyVAT_par integer,@pUrzadSkarbowyPD_par integer,@pZUS_par integer,@pMainJO_par integer) with encryption as 
	update n5firma set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strFax=@strFax_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRejestr=@strRejestr_par,
	strSad=@strSad_par,
	strWydzial=@strWydzial_par,
	eForma=@eForma_par,
	strNIP=@strNIP_par,
	strREGON=@strREGON_par,
	strEKD=@strEKD_par,
	strRachunek1=@strRachunek1_par,
	pBank1=@pBank1_par,
	strPrzeznaczenie1=@strPrzeznaczenie1_par,
	strRachunek2=@strRachunek2_par,
	pBank2=@pBank2_par,
	strPrzeznaczenie2=@strPrzeznaczenie2_par,
	strRachunek3=@strRachunek3_par,
	strPrzeznaczenie3=@strPrzeznaczenie3_par,
	pWaluta=@pWaluta_par,
	pBank3=@pBank3_par,
	pUrzadSkarbowyVAT=@pUrzadSkarbowyVAT_par,
	pUrzadSkarbowyPD=@pUrzadSkarbowyPD_par,
	pZUS=@pZUS_par,
	pMainJO=@pMainJO_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5firma_delete')
	drop procedure n5firma_delete
go

create procedure n5firma_delete(@idobj_par integer) with encryption as 
	delete from n5firma where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5firma_maxid')
	drop procedure n5firma_maxid
go

create procedure n5firma_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5firma
go

if exists (select * from sysobjects where name='n5firma_candel')
	drop procedure n5firma_candel
go

create procedure n5firma_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10110
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10110
go

-- table: n5miejscowosc
if exists (select * from sysobjects where name='n5miejscowosc_select')
	drop procedure n5miejscowosc_select
go

create procedure n5miejscowosc_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@eWielkosc_par integer output,
	@pWojewodztwo_par integer output,
	@pRegion_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@eWielkosc_par=eWielkosc,
	@pWojewodztwo_par=pWojewodztwo,
	@pRegion_par=pRegion,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr from n5miejscowosc where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miejscowosc_insert')
	drop procedure n5miejscowosc_insert
go

create procedure n5miejscowosc_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eWielkosc_par integer,@pWojewodztwo_par integer,@pRegion_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2)) with encryption as 
	insert into n5miejscowosc values(@idobj_par,@versionid_par,@strNazwa_par,@eWielkosc_par,@pWojewodztwo_par,@pRegion_par,@curSzerGeogr_par,@curDlugGeogr_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5miejscowosc_update')
	drop procedure n5miejscowosc_update
go

create procedure n5miejscowosc_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eWielkosc_par integer,@pWojewodztwo_par integer,@pRegion_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2)) with encryption as 
	update n5miejscowosc set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	eWielkosc=@eWielkosc_par,
	pWojewodztwo=@pWojewodztwo_par,
	pRegion=@pRegion_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miejscowosc_delete')
	drop procedure n5miejscowosc_delete
go

create procedure n5miejscowosc_delete(@idobj_par integer) with encryption as 
	delete from n5miejscowosc where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miejscowosc_maxid')
	drop procedure n5miejscowosc_maxid
go

create procedure n5miejscowosc_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5miejscowosc
go

if exists (select * from sysobjects where name='n5miejscowosc_candel')
	drop procedure n5miejscowosc_candel
go

create procedure n5miejscowosc_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10104 as integer),idobj from n5bank where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10105 as integer),idobj from n5instytucja where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pMiejscowoscSDB=@idobj_par
union
select TOP 5 'typeid'=cast(10109 as integer),idobj from n5pracownik where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where pMiejscowosc=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pMiejscowosc=@idobj_par
go

-- table: n5klient_pracownik
if exists (select * from sysobjects where name='n5klient_pracownik_select')
	drop procedure n5klient_pracownik_select
go

create procedure n5klient_pracownik_select(@idobj_par integer,@versionid_par integer output,
	@strNazwisko_par varchar(32) output,
	@strImie_par varchar(32) output,
	@strImie2_par varchar(32) output,
	@ePlec_par integer output,
	@nWiek_par integer output,
	@strTytul_par varchar(32) output,
	@eStanCywilny_par integer output,
	@strTel1_par varchar(20) output,
	@pKlient_par integer output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strTel4_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@pJednOrgKlienta_par integer output,
	@strUwagi_par varchar(255) output,
	@strUpodobania_par varchar(255) output,
	@pPracownik_par integer output,
	@strStanowisko_par varchar(64) output,
	@eAktywny_par integer output,
	@strEmail2_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwisko_par=strNazwisko,
	@strImie_par=strImie,
	@strImie2_par=strImie2,
	@ePlec_par=ePlec,
	@nWiek_par=nWiek,
	@strTytul_par=strTytul,
	@eStanCywilny_par=eStanCywilny,
	@strTel1_par=strTel1,
	@pKlient_par=pKlient,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strTel4_par=strTel4,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@pJednOrgKlienta_par=pJednOrgKlienta,
	@strUwagi_par=strUwagi,
	@strUpodobania_par=strUpodobania,
	@pPracownik_par=pPracownik,
	@strStanowisko_par=strStanowisko,
	@eAktywny_par=eAktywny,
	@strEmail2_par=strEmail2 from n5klient_pracownik where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_pracownik_insert')
	drop procedure n5klient_pracownik_insert
go

create procedure n5klient_pracownik_insert(@idobj_par integer,@versionid_par integer,@strNazwisko_par varchar(32),@strImie_par varchar(32),@strImie2_par varchar(32),@ePlec_par integer,@nWiek_par integer,@strTytul_par varchar(32),@eStanCywilny_par integer,@strTel1_par varchar(20),@pKlient_par integer,@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@pJednOrgKlienta_par integer,@strUwagi_par varchar(255),@strUpodobania_par varchar(255),@pPracownik_par integer,@strStanowisko_par varchar(64),@eAktywny_par integer,@strEmail2_par varchar(64)) with encryption as 
	insert into n5klient_pracownik values(@idobj_par,@versionid_par,@strNazwisko_par,@strImie_par,@strImie2_par,@ePlec_par,@nWiek_par,@strTytul_par,@eStanCywilny_par,@strTel1_par,@pKlient_par,@strTel2_par,@strTel3_par,@strTel4_par,@strFax_par,@strEmail_par,@strWWW_par,@pJednOrgKlienta_par,@strUwagi_par,@strUpodobania_par,@pPracownik_par,@strStanowisko_par,@eAktywny_par,@strEmail2_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_pracownik_update')
	drop procedure n5klient_pracownik_update
go

create procedure n5klient_pracownik_update(@idobj_par integer,@versionid_par integer,@strNazwisko_par varchar(32),@strImie_par varchar(32),@strImie2_par varchar(32),@ePlec_par integer,@nWiek_par integer,@strTytul_par varchar(32),@eStanCywilny_par integer,@strTel1_par varchar(20),@pKlient_par integer,@strTel2_par varchar(20),@strTel3_par varchar(20),@strTel4_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@pJednOrgKlienta_par integer,@strUwagi_par varchar(255),@strUpodobania_par varchar(255),@pPracownik_par integer,@strStanowisko_par varchar(64),@eAktywny_par integer,@strEmail2_par varchar(64)) with encryption as 
	update n5klient_pracownik set VersionId=@versionid_par,
	strNazwisko=@strNazwisko_par,
	strImie=@strImie_par,
	strImie2=@strImie2_par,
	ePlec=@ePlec_par,
	nWiek=@nWiek_par,
	strTytul=@strTytul_par,
	eStanCywilny=@eStanCywilny_par,
	strTel1=@strTel1_par,
	pKlient=@pKlient_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strTel4=@strTel4_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	pJednOrgKlienta=@pJednOrgKlienta_par,
	strUwagi=@strUwagi_par,
	strUpodobania=@strUpodobania_par,
	pPracownik=@pPracownik_par,
	strStanowisko=@strStanowisko_par,
	eAktywny=@eAktywny_par,
	strEmail2=@strEmail2_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_pracownik_delete')
	drop procedure n5klient_pracownik_delete
go

create procedure n5klient_pracownik_delete(@idobj_par integer) with encryption as 
	delete from n5klient_pracownik where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5klient_pracownik_maxid')
	drop procedure n5klient_pracownik_maxid
go

create procedure n5klient_pracownik_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5klient_pracownik
go

if exists (select * from sysobjects where name='n5klient_pracownik_candel')
	drop procedure n5klient_pracownik_candel
go

create procedure n5klient_pracownik_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pKlientPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpNadawca=@idobj_par and wpNadawca_wrt=10112
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpAdresat=@idobj_par and wpAdresat_wrt=10112
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pKlientPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10122 as integer),idobj from n5wykonawca where wrefObiekt=@idobj_par and wrefObiekt_wrt=10112
union
select TOP 5 'typeid'=cast(10128 as integer),idobj from n5SendEmail where wpNadawca=@idobj_par and wpNadawca_wrt=10112
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKlientPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKlientPracownik=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKlientPracownik=@idobj_par
go

-- table: n5jedn_org
if exists (select * from sysobjects where name='n5jedn_org_select')
	drop procedure n5jedn_org_select
go

create procedure n5jedn_org_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@strDzial_par varchar(255) output,
	@strWydzial_par varchar(255) output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRachunek1_par varchar(32) output,
	@strPrzeznaczenie1_par varchar(64) output,
	@pBank1_par integer output,
	@strRachunek2_par varchar(32) output,
	@strPrzeznaczenie2_par varchar(64) output,
	@pBank2_par integer output,
	@strRachunek3_par varchar(32) output,
	@strPrzeznaczenie3_par varchar(64) output,
	@pBank3_par integer output,
	@pPracownik_par integer output,
	@p_Jend_Org_Nadrzedna_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@strDzial_par=strDzial,
	@strWydzial_par=strWydzial,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRachunek1_par=strRachunek1,
	@strPrzeznaczenie1_par=strPrzeznaczenie1,
	@pBank1_par=pBank1,
	@strRachunek2_par=strRachunek2,
	@strPrzeznaczenie2_par=strPrzeznaczenie2,
	@pBank2_par=pBank2,
	@strRachunek3_par=strRachunek3,
	@strPrzeznaczenie3_par=strPrzeznaczenie3,
	@pBank3_par=pBank3,
	@pPracownik_par=pPracownik,
	@p_Jend_Org_Nadrzedna_par=p_Jend_Org_Nadrzedna from n5jedn_org where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jedn_org_insert')
	drop procedure n5jedn_org_insert
go

create procedure n5jedn_org_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strDzial_par varchar(255),@strWydzial_par varchar(255),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@pPracownik_par integer,@p_Jend_Org_Nadrzedna_par integer) with encryption as 
	insert into n5jedn_org values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@strDzial_par,@strWydzial_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strFax_par,@strEmail_par,@strWWW_par,@strRachunek1_par,@strPrzeznaczenie1_par,@pBank1_par,@strRachunek2_par,@strPrzeznaczenie2_par,@pBank2_par,@strRachunek3_par,@strPrzeznaczenie3_par,@pBank3_par,@pPracownik_par,@p_Jend_Org_Nadrzedna_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5jedn_org_update')
	drop procedure n5jedn_org_update
go

create procedure n5jedn_org_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strDzial_par varchar(255),@strWydzial_par varchar(255),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@pPracownik_par integer,@p_Jend_Org_Nadrzedna_par integer) with encryption as 
	update n5jedn_org set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	strDzial=@strDzial_par,
	strWydzial=@strWydzial_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRachunek1=@strRachunek1_par,
	strPrzeznaczenie1=@strPrzeznaczenie1_par,
	pBank1=@pBank1_par,
	strRachunek2=@strRachunek2_par,
	strPrzeznaczenie2=@strPrzeznaczenie2_par,
	pBank2=@pBank2_par,
	strRachunek3=@strRachunek3_par,
	strPrzeznaczenie3=@strPrzeznaczenie3_par,
	pBank3=@pBank3_par,
	pPracownik=@pPracownik_par,
	p_Jend_Org_Nadrzedna=@p_Jend_Org_Nadrzedna_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jedn_org_delete')
	drop procedure n5jedn_org_delete
go

create procedure n5jedn_org_delete(@idobj_par integer) with encryption as 
	delete from n5jedn_org where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5jedn_org_maxid')
	drop procedure n5jedn_org_maxid
go

create procedure n5jedn_org_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5jedn_org
go

if exists (select * from sysobjects where name='n5jedn_org_candel')
	drop procedure n5jedn_org_candel
go

create procedure n5jedn_org_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10109 as integer),idobj from n5pracownik where pJednostkaOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pMainJO=@idobj_par
union
select TOP 5 'typeid'=cast(10113 as integer),idobj from n5jedn_org where p_Jend_Org_Nadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10160 as integer),idobj from n5magazyn where pJednostkaOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10179 as integer),idobj from n5srtrw where pMUJO=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pMUJO=@idobj_par
go

-- table: n5_klient_jedn_org
if exists (select * from sysobjects where name='n5_klient_jedn_org_select')
	drop procedure n5_klient_jedn_org_select
go

create procedure n5_klient_jedn_org_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(255) output,
	@strSkrot_par varchar(32) output,
	@strUlica_par varchar(64) output,
	@strNrDomu_par varchar(8) output,
	@strNrLokalu_par varchar(8) output,
	@strKod_par varchar(8) output,
	@strPoczta_par varchar(64) output,
	@pMiejscowosc_par integer output,
	@curSzerGeogr_par decimal(12,2) output,
	@curDlugGeogr_par decimal(12,2) output,
	@strTel1_par varchar(20) output,
	@strTel2_par varchar(20) output,
	@strTel3_par varchar(20) output,
	@strFax_par varchar(20) output,
	@strEmail_par varchar(64) output,
	@strWWW_par varchar(64) output,
	@strRachunek1_par varchar(32) output,
	@strPrzeznaczenie1_par varchar(64) output,
	@pBank1_par integer output,
	@strRachunek2_par varchar(32) output,
	@strPrzeznaczenie2_par varchar(64) output,
	@pBank2_par integer output,
	@strRachunek3_par varchar(32) output,
	@strPrzeznaczenie3_par varchar(64) output,
	@pBank3_par integer output,
	@pKlient_par integer output,
	@p_Klient_JO_Nadrzedna_par integer output,
	@pKlientPracownik_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strSkrot_par=strSkrot,
	@strUlica_par=strUlica,
	@strNrDomu_par=strNrDomu,
	@strNrLokalu_par=strNrLokalu,
	@strKod_par=strKod,
	@strPoczta_par=strPoczta,
	@pMiejscowosc_par=pMiejscowosc,
	@curSzerGeogr_par=curSzerGeogr,
	@curDlugGeogr_par=curDlugGeogr,
	@strTel1_par=strTel1,
	@strTel2_par=strTel2,
	@strTel3_par=strTel3,
	@strFax_par=strFax,
	@strEmail_par=strEmail,
	@strWWW_par=strWWW,
	@strRachunek1_par=strRachunek1,
	@strPrzeznaczenie1_par=strPrzeznaczenie1,
	@pBank1_par=pBank1,
	@strRachunek2_par=strRachunek2,
	@strPrzeznaczenie2_par=strPrzeznaczenie2,
	@pBank2_par=pBank2,
	@strRachunek3_par=strRachunek3,
	@strPrzeznaczenie3_par=strPrzeznaczenie3,
	@pBank3_par=pBank3,
	@pKlient_par=pKlient,
	@p_Klient_JO_Nadrzedna_par=p_Klient_JO_Nadrzedna,
	@pKlientPracownik_par=pKlientPracownik from n5_klient_jedn_org where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5_klient_jedn_org_insert')
	drop procedure n5_klient_jedn_org_insert
go

create procedure n5_klient_jedn_org_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@pKlient_par integer,@p_Klient_JO_Nadrzedna_par integer,@pKlientPracownik_par integer) with encryption as 
	insert into n5_klient_jedn_org values(@idobj_par,@versionid_par,@strNazwa_par,@strSkrot_par,@strUlica_par,@strNrDomu_par,@strNrLokalu_par,@strKod_par,@strPoczta_par,@pMiejscowosc_par,@curSzerGeogr_par,@curDlugGeogr_par,@strTel1_par,@strTel2_par,@strTel3_par,@strFax_par,@strEmail_par,@strWWW_par,@strRachunek1_par,@strPrzeznaczenie1_par,@pBank1_par,@strRachunek2_par,@strPrzeznaczenie2_par,@pBank2_par,@strRachunek3_par,@strPrzeznaczenie3_par,@pBank3_par,@pKlient_par,@p_Klient_JO_Nadrzedna_par,@pKlientPracownik_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5_klient_jedn_org_update')
	drop procedure n5_klient_jedn_org_update
go

create procedure n5_klient_jedn_org_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(255),@strSkrot_par varchar(32),@strUlica_par varchar(64),@strNrDomu_par varchar(8),@strNrLokalu_par varchar(8),@strKod_par varchar(8),@strPoczta_par varchar(64),@pMiejscowosc_par integer,@curSzerGeogr_par decimal(12,2),@curDlugGeogr_par decimal(12,2),@strTel1_par varchar(20),@strTel2_par varchar(20),@strTel3_par varchar(20),@strFax_par varchar(20),@strEmail_par varchar(64),@strWWW_par varchar(64),@strRachunek1_par varchar(32),@strPrzeznaczenie1_par varchar(64),@pBank1_par integer,@strRachunek2_par varchar(32),@strPrzeznaczenie2_par varchar(64),@pBank2_par integer,@strRachunek3_par varchar(32),@strPrzeznaczenie3_par varchar(64),@pBank3_par integer,@pKlient_par integer,@p_Klient_JO_Nadrzedna_par integer,@pKlientPracownik_par integer) with encryption as 
	update n5_klient_jedn_org set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strSkrot=@strSkrot_par,
	strUlica=@strUlica_par,
	strNrDomu=@strNrDomu_par,
	strNrLokalu=@strNrLokalu_par,
	strKod=@strKod_par,
	strPoczta=@strPoczta_par,
	pMiejscowosc=@pMiejscowosc_par,
	curSzerGeogr=@curSzerGeogr_par,
	curDlugGeogr=@curDlugGeogr_par,
	strTel1=@strTel1_par,
	strTel2=@strTel2_par,
	strTel3=@strTel3_par,
	strFax=@strFax_par,
	strEmail=@strEmail_par,
	strWWW=@strWWW_par,
	strRachunek1=@strRachunek1_par,
	strPrzeznaczenie1=@strPrzeznaczenie1_par,
	pBank1=@pBank1_par,
	strRachunek2=@strRachunek2_par,
	strPrzeznaczenie2=@strPrzeznaczenie2_par,
	pBank2=@pBank2_par,
	strRachunek3=@strRachunek3_par,
	strPrzeznaczenie3=@strPrzeznaczenie3_par,
	pBank3=@pBank3_par,
	pKlient=@pKlient_par,
	p_Klient_JO_Nadrzedna=@p_Klient_JO_Nadrzedna_par,
	pKlientPracownik=@pKlientPracownik_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5_klient_jedn_org_delete')
	drop procedure n5_klient_jedn_org_delete
go

create procedure n5_klient_jedn_org_delete(@idobj_par integer) with encryption as 
	delete from n5_klient_jedn_org where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5_klient_jedn_org_maxid')
	drop procedure n5_klient_jedn_org_maxid
go

create procedure n5_klient_jedn_org_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5_klient_jedn_org
go

if exists (select * from sysobjects where name='n5_klient_jedn_org_candel')
	drop procedure n5_klient_jedn_org_candel
go

create procedure n5_klient_jedn_org_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10112 as integer),idobj from n5klient_pracownik where pJednOrgKlienta=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where p_Klient_JO_Nadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKlient_JO=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKlient_JO=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKlient_JO=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pDostawca_JO=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pKlient_JO=@idobj_par
go

-- table: n5typdokumentu
if exists (select * from sysobjects where name='n5typdokumentu_select')
	drop procedure n5typdokumentu_select
go

create procedure n5typdokumentu_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pTypNadrzedny_par integer output,
	@eRodzaj_par integer output,
	@nInternalID_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pTypNadrzedny_par=pTypNadrzedny,
	@eRodzaj_par=eRodzaj,
	@nInternalID_par=nInternalID from n5typdokumentu where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdokumentu_insert')
	drop procedure n5typdokumentu_insert
go

create procedure n5typdokumentu_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pTypNadrzedny_par integer,@eRodzaj_par integer,@nInternalID_par integer) with encryption as 
	insert into n5typdokumentu values(@idobj_par,@versionid_par,@strNazwa_par,@pTypNadrzedny_par,@eRodzaj_par,@nInternalID_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdokumentu_update')
	drop procedure n5typdokumentu_update
go

create procedure n5typdokumentu_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pTypNadrzedny_par integer,@eRodzaj_par integer,@nInternalID_par integer) with encryption as 
	update n5typdokumentu set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pTypNadrzedny=@pTypNadrzedny_par,
	eRodzaj=@eRodzaj_par,
	nInternalID=@nInternalID_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdokumentu_delete')
	drop procedure n5typdokumentu_delete
go

create procedure n5typdokumentu_delete(@idobj_par integer) with encryption as 
	delete from n5typdokumentu where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdokumentu_maxid')
	drop procedure n5typdokumentu_maxid
go

create procedure n5typdokumentu_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5typdokumentu
go

if exists (select * from sysobjects where name='n5typdokumentu_candel')
	drop procedure n5typdokumentu_candel
go

create procedure n5typdokumentu_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10115 as integer),idobj from n5typdokumentu where pTypNadrzedny=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pTypDokumentu=@idobj_par
go

-- table: n5grupaproduktow
if exists (select * from sysobjects where name='n5grupaproduktow_select')
	drop procedure n5grupaproduktow_select
go

create procedure n5grupaproduktow_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@pGrupaNadrzedna_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pGrupaNadrzedna_par=pGrupaNadrzedna from n5grupaproduktow where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaproduktow_insert')
	drop procedure n5grupaproduktow_insert
go

create procedure n5grupaproduktow_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@pGrupaNadrzedna_par integer) with encryption as 
	insert into n5grupaproduktow values(@idobj_par,@versionid_par,@strNazwa_par,@pGrupaNadrzedna_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaproduktow_update')
	drop procedure n5grupaproduktow_update
go

create procedure n5grupaproduktow_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@pGrupaNadrzedna_par integer) with encryption as 
	update n5grupaproduktow set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pGrupaNadrzedna=@pGrupaNadrzedna_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaproduktow_delete')
	drop procedure n5grupaproduktow_delete
go

create procedure n5grupaproduktow_delete(@idobj_par integer) with encryption as 
	delete from n5grupaproduktow where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaproduktow_maxid')
	drop procedure n5grupaproduktow_maxid
go

create procedure n5grupaproduktow_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5grupaproduktow
go

if exists (select * from sysobjects where name='n5grupaproduktow_candel')
	drop procedure n5grupaproduktow_candel
go

create procedure n5grupaproduktow_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10116 as integer),idobj from n5grupaproduktow where pGrupaNadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where pGrupaProd=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10116
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10116
go

-- table: n5dokument
if exists (select * from sysobjects where name='n5dokument_select')
	drop procedure n5dokument_select
go

create procedure n5dokument_select(@idobj_par integer,@versionid_par integer output,
	@strNumDok_par varchar(32) output,
	@strNumDokObcy_par varchar(64) output,
	@strTematDokum_par varchar(128) output,
	@pTypDokumentu_par integer output,
	@dDataWeWy_par datetime output,
	@dDataRejestracji_par datetime output,
	@wpNadawca_par integer output,
	@wpNadawca_wrt_par integer output,
	@wpAdresat_par integer output,
	@wpAdresat_wrt_par integer output,
	@strStreszczenie_par varchar(1024) output,
	@nForma_par integer output,
	@nLiczbaStron_par integer output,
	@strLokalizacja_par varchar(128) output,
	@strFileName_par varchar(1024) output,
	@strCheckoutFileName_par varchar(1024) output,
	@pUzytkWypoz_par integer output,
	@strCecha1_par varchar(128) output,
	@strCecha2_par varchar(128) output,
	@strCecha3_par varchar(128) output,
	@nIsSecurity_par integer output,
	@pReplaces_par integer output,
	@pReplaced_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNumDok_par=strNumDok,
	@strNumDokObcy_par=strNumDokObcy,
	@strTematDokum_par=strTematDokum,
	@pTypDokumentu_par=pTypDokumentu,
	@dDataWeWy_par=dDataWeWy,
	@dDataRejestracji_par=dDataRejestracji,
	@wpNadawca_par=wpNadawca,
	@wpNadawca_wrt_par=wpNadawca_wrt,
	@wpAdresat_par=wpAdresat,
	@wpAdresat_wrt_par=wpAdresat_wrt,
	@strStreszczenie_par=strStreszczenie,
	@nForma_par=nForma,
	@nLiczbaStron_par=nLiczbaStron,
	@strLokalizacja_par=strLokalizacja,
	@strFileName_par=strFileName,
	@strCheckoutFileName_par=strCheckoutFileName,
	@pUzytkWypoz_par=pUzytkWypoz,
	@strCecha1_par=strCecha1,
	@strCecha2_par=strCecha2,
	@strCecha3_par=strCecha3,
	@nIsSecurity_par=nIsSecurity,
	@pReplaces_par=pReplaces,
	@pReplaced_par=pReplaced from n5dokument where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokument_insert')
	drop procedure n5dokument_insert
go

create procedure n5dokument_insert(@idobj_par integer,@versionid_par integer,@strNumDok_par varchar(32),@strNumDokObcy_par varchar(64),@strTematDokum_par varchar(128),@pTypDokumentu_par integer,@dDataWeWy_par datetime,@dDataRejestracji_par datetime,@wpNadawca_par integer,@wpNadawca_wrt_par integer,@wpAdresat_par integer,@wpAdresat_wrt_par integer,@strStreszczenie_par varchar(1024),@nForma_par integer,@nLiczbaStron_par integer,@strLokalizacja_par varchar(128),@strFileName_par varchar(1024),@strCheckoutFileName_par varchar(1024),@pUzytkWypoz_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@nIsSecurity_par integer,@pReplaces_par integer,@pReplaced_par integer) with encryption as 
	insert into n5dokument values(@idobj_par,@versionid_par,@strNumDok_par,@strNumDokObcy_par,@strTematDokum_par,@pTypDokumentu_par,@dDataWeWy_par,@dDataRejestracji_par,@wpNadawca_par,@wpNadawca_wrt_par,@wpAdresat_par,@wpAdresat_wrt_par,@strStreszczenie_par,@nForma_par,@nLiczbaStron_par,@strLokalizacja_par,@strFileName_par,@strCheckoutFileName_par,@pUzytkWypoz_par,@strCecha1_par,@strCecha2_par,@strCecha3_par,@nIsSecurity_par,@pReplaces_par,@pReplaced_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokument_update')
	drop procedure n5dokument_update
go

create procedure n5dokument_update(@idobj_par integer,@versionid_par integer,@strNumDok_par varchar(32),@strNumDokObcy_par varchar(64),@strTematDokum_par varchar(128),@pTypDokumentu_par integer,@dDataWeWy_par datetime,@dDataRejestracji_par datetime,@wpNadawca_par integer,@wpNadawca_wrt_par integer,@wpAdresat_par integer,@wpAdresat_wrt_par integer,@strStreszczenie_par varchar(1024),@nForma_par integer,@nLiczbaStron_par integer,@strLokalizacja_par varchar(128),@strFileName_par varchar(1024),@strCheckoutFileName_par varchar(1024),@pUzytkWypoz_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@nIsSecurity_par integer,@pReplaces_par integer,@pReplaced_par integer) with encryption as 
	update n5dokument set VersionId=@versionid_par,
	strNumDok=@strNumDok_par,
	strNumDokObcy=@strNumDokObcy_par,
	strTematDokum=@strTematDokum_par,
	pTypDokumentu=@pTypDokumentu_par,
	dDataWeWy=@dDataWeWy_par,
	dDataRejestracji=@dDataRejestracji_par,
	wpNadawca=@wpNadawca_par,
	wpNadawca_wrt=@wpNadawca_wrt_par,
	wpAdresat=@wpAdresat_par,
	wpAdresat_wrt=@wpAdresat_wrt_par,
	strStreszczenie=@strStreszczenie_par,
	nForma=@nForma_par,
	nLiczbaStron=@nLiczbaStron_par,
	strLokalizacja=@strLokalizacja_par,
	strFileName=@strFileName_par,
	strCheckoutFileName=@strCheckoutFileName_par,
	pUzytkWypoz=@pUzytkWypoz_par,
	strCecha1=@strCecha1_par,
	strCecha2=@strCecha2_par,
	strCecha3=@strCecha3_par,
	nIsSecurity=@nIsSecurity_par,
	pReplaces=@pReplaces_par,
	pReplaced=@pReplaced_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokument_delete')
	drop procedure n5dokument_delete
go

create procedure n5dokument_delete(@idobj_par integer) with encryption as 
	delete from n5dokument where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokument_maxid')
	drop procedure n5dokument_maxid
go

create procedure n5dokument_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dokument
go

if exists (select * from sysobjects where name='n5dokument_candel')
	drop procedure n5dokument_candel
go

create procedure n5dokument_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pReplaces=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pReplaced=@idobj_par
union
select TOP 5 'typeid'=cast(10125 as integer),idobj from n5zadaniezal where wrefZal=@idobj_par and wrefZal_wrt=10117
union
select TOP 5 'typeid'=cast(10126 as integer),idobj from n5WizzardEmailDokumElem where pDokument=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where pUlotka=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where pInstrukcja=@idobj_par
union
select TOP 5 'typeid'=cast(10133 as integer),idobj from n5dokumentlinks where pDokument=@idobj_par
union
select TOP 5 'typeid'=cast(10213 as integer),idobj from n5bwinfo_zal where wrefZal=@idobj_par and wrefZal_wrt=10117
union
select TOP 5 'typeid'=cast(10008 as integer),idobj from n5dpc where pDocTemplate=@idobj_par
go

-- table: n5grupaklient
if exists (select * from sysobjects where name='n5grupaklient_select')
	drop procedure n5grupaklient_select
go

create procedure n5grupaklient_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pGrupaNadrzedna_par integer output,
	@curLimitKred_par decimal(12,2) output,
	@pWalutaLimitu_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pGrupaNadrzedna_par=pGrupaNadrzedna,
	@curLimitKred_par=curLimitKred,
	@pWalutaLimitu_par=pWalutaLimitu from n5grupaklient where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaklient_insert')
	drop procedure n5grupaklient_insert
go

create procedure n5grupaklient_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pGrupaNadrzedna_par integer,@curLimitKred_par decimal(12,2),@pWalutaLimitu_par integer) with encryption as 
	insert into n5grupaklient values(@idobj_par,@versionid_par,@strNazwa_par,@pGrupaNadrzedna_par,@curLimitKred_par,@pWalutaLimitu_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaklient_update')
	drop procedure n5grupaklient_update
go

create procedure n5grupaklient_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pGrupaNadrzedna_par integer,@curLimitKred_par decimal(12,2),@pWalutaLimitu_par integer) with encryption as 
	update n5grupaklient set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pGrupaNadrzedna=@pGrupaNadrzedna_par,
	curLimitKred=@curLimitKred_par,
	pWalutaLimitu=@pWalutaLimitu_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaklient_delete')
	drop procedure n5grupaklient_delete
go

create procedure n5grupaklient_delete(@idobj_par integer) with encryption as 
	delete from n5grupaklient where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupaklient_maxid')
	drop procedure n5grupaklient_maxid
go

create procedure n5grupaklient_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5grupaklient
go

if exists (select * from sysobjects where name='n5grupaklient_candel')
	drop procedure n5grupaklient_candel
go

create procedure n5grupaklient_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pGrupaKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10118 as integer),idobj from n5grupaklient where pGrupaNadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpKlientGrupa=@idobj_par and wpKlientGrupa_wrt=10118
go

-- table: n5zadanie
if exists (select * from sysobjects where name='n5zadanie_select')
	drop procedure n5zadanie_select
go

create procedure n5zadanie_select(@idobj_par integer,@versionid_par integer output,
	@nStatus_par integer output,
	@dDataZlec_par datetime output,
	@tCzasZlec_par integer output,
	@pZlecajacy_par integer output,
	@ePriorytet_par integer output,
	@eTypterminRozp_par integer output,
	@dDataTerminRozp_par datetime output,
	@tCzasTerminRozp_par integer output,
	@eTypterminZak_par integer output,
	@strTemat_par varchar(128) output,
	@strOpis_par varchar(1024) output,
	@nNaklad_par integer output,
	@pTypDzialania_par integer output,
	@pProcedura_par integer output,
	@wrefSzczegoly_par integer output,
	@wrefSzczegoly_wrt_par integer output,
	@pNadZadanie_par integer output,
	@pPopZadanie_par integer output,
	@pWykonawca_par integer output,
	@dDataPow_par datetime output,
	@tCzasPow_par integer output,
	@dDataRozp_par datetime output,
	@tCzasRozp_par integer output,
	@nZaawansowanie_par integer output,
	@dDataZakon_par datetime output,
	@tCzasZakon_par integer output,
	@strUwagi_par varchar(1024) output,
	@dDataZamk_par datetime output,
	@tCzasZamk_par integer output,
	@strCecha1_par varchar(128) output,
	@strCecha2_par varchar(128) output,
	@strCecha3_par varchar(128) output,
	@dDataTerminZak_par datetime output,
	@tCzasTerminZak_par integer output,
	@pKlient_par integer output,
	@pSchematDekretacji_par integer output,
	@pDowKsieg_par integer output,
	@dDataPrzyp_par datetime output,
	@tCzasPrzyp_par integer output,
	@nIsSecurity_par integer output,
	@pKlientPracownik_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@nStatus_par=nStatus,
	@dDataZlec_par=dDataZlec,
	@tCzasZlec_par=tCzasZlec,
	@pZlecajacy_par=pZlecajacy,
	@ePriorytet_par=ePriorytet,
	@eTypterminRozp_par=eTypterminRozp,
	@dDataTerminRozp_par=dDataTerminRozp,
	@tCzasTerminRozp_par=tCzasTerminRozp,
	@eTypterminZak_par=eTypterminZak,
	@strTemat_par=strTemat,
	@strOpis_par=strOpis,
	@nNaklad_par=nNaklad,
	@pTypDzialania_par=pTypDzialania,
	@pProcedura_par=pProcedura,
	@wrefSzczegoly_par=wrefSzczegoly,
	@wrefSzczegoly_wrt_par=wrefSzczegoly_wrt,
	@pNadZadanie_par=pNadZadanie,
	@pPopZadanie_par=pPopZadanie,
	@pWykonawca_par=pWykonawca,
	@dDataPow_par=dDataPow,
	@tCzasPow_par=tCzasPow,
	@dDataRozp_par=dDataRozp,
	@tCzasRozp_par=tCzasRozp,
	@nZaawansowanie_par=nZaawansowanie,
	@dDataZakon_par=dDataZakon,
	@tCzasZakon_par=tCzasZakon,
	@strUwagi_par=strUwagi,
	@dDataZamk_par=dDataZamk,
	@tCzasZamk_par=tCzasZamk,
	@strCecha1_par=strCecha1,
	@strCecha2_par=strCecha2,
	@strCecha3_par=strCecha3,
	@dDataTerminZak_par=dDataTerminZak,
	@tCzasTerminZak_par=tCzasTerminZak,
	@pKlient_par=pKlient,
	@pSchematDekretacji_par=pSchematDekretacji,
	@pDowKsieg_par=pDowKsieg,
	@dDataPrzyp_par=dDataPrzyp,
	@tCzasPrzyp_par=tCzasPrzyp,
	@nIsSecurity_par=nIsSecurity,
	@pKlientPracownik_par=pKlientPracownik,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5zadanie where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadanie_insert')
	drop procedure n5zadanie_insert
go

create procedure n5zadanie_insert(@idobj_par integer,@versionid_par integer,@nStatus_par integer,@dDataZlec_par datetime,@tCzasZlec_par integer,@pZlecajacy_par integer,@ePriorytet_par integer,@eTypterminRozp_par integer,@dDataTerminRozp_par datetime,@tCzasTerminRozp_par integer,@eTypterminZak_par integer,@strTemat_par varchar(128),@strOpis_par varchar(1024),@nNaklad_par integer,@pTypDzialania_par integer,@pProcedura_par integer,@wrefSzczegoly_par integer,@wrefSzczegoly_wrt_par integer,@pNadZadanie_par integer,@pPopZadanie_par integer,@pWykonawca_par integer,@dDataPow_par datetime,@tCzasPow_par integer,@dDataRozp_par datetime,@tCzasRozp_par integer,@nZaawansowanie_par integer,@dDataZakon_par datetime,@tCzasZakon_par integer,@strUwagi_par varchar(1024),@dDataZamk_par datetime,@tCzasZamk_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@dDataTerminZak_par datetime,@tCzasTerminZak_par integer,@pKlient_par integer,@pSchematDekretacji_par integer,@pDowKsieg_par integer,@dDataPrzyp_par datetime,@tCzasPrzyp_par integer,@nIsSecurity_par integer,@pKlientPracownik_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5zadanie values(@idobj_par,@versionid_par,@nStatus_par,@dDataZlec_par,@tCzasZlec_par,@pZlecajacy_par,@ePriorytet_par,@eTypterminRozp_par,@dDataTerminRozp_par,@tCzasTerminRozp_par,@eTypterminZak_par,@strTemat_par,@strOpis_par,@nNaklad_par,@pTypDzialania_par,@pProcedura_par,@wrefSzczegoly_par,@wrefSzczegoly_wrt_par,@pNadZadanie_par,@pPopZadanie_par,@pWykonawca_par,@dDataPow_par,@tCzasPow_par,@dDataRozp_par,@tCzasRozp_par,@nZaawansowanie_par,@dDataZakon_par,@tCzasZakon_par,@strUwagi_par,@dDataZamk_par,@tCzasZamk_par,@strCecha1_par,@strCecha2_par,@strCecha3_par,@dDataTerminZak_par,@tCzasTerminZak_par,@pKlient_par,@pSchematDekretacji_par,@pDowKsieg_par,@dDataPrzyp_par,@tCzasPrzyp_par,@nIsSecurity_par,@pKlientPracownik_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadanie_update')
	drop procedure n5zadanie_update
go

create procedure n5zadanie_update(@idobj_par integer,@versionid_par integer,@nStatus_par integer,@dDataZlec_par datetime,@tCzasZlec_par integer,@pZlecajacy_par integer,@ePriorytet_par integer,@eTypterminRozp_par integer,@dDataTerminRozp_par datetime,@tCzasTerminRozp_par integer,@eTypterminZak_par integer,@strTemat_par varchar(128),@strOpis_par varchar(1024),@nNaklad_par integer,@pTypDzialania_par integer,@pProcedura_par integer,@wrefSzczegoly_par integer,@wrefSzczegoly_wrt_par integer,@pNadZadanie_par integer,@pPopZadanie_par integer,@pWykonawca_par integer,@dDataPow_par datetime,@tCzasPow_par integer,@dDataRozp_par datetime,@tCzasRozp_par integer,@nZaawansowanie_par integer,@dDataZakon_par datetime,@tCzasZakon_par integer,@strUwagi_par varchar(1024),@dDataZamk_par datetime,@tCzasZamk_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@dDataTerminZak_par datetime,@tCzasTerminZak_par integer,@pKlient_par integer,@pSchematDekretacji_par integer,@pDowKsieg_par integer,@dDataPrzyp_par datetime,@tCzasPrzyp_par integer,@nIsSecurity_par integer,@pKlientPracownik_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5zadanie set VersionId=@versionid_par,
	nStatus=@nStatus_par,
	dDataZlec=@dDataZlec_par,
	tCzasZlec=@tCzasZlec_par,
	pZlecajacy=@pZlecajacy_par,
	ePriorytet=@ePriorytet_par,
	eTypterminRozp=@eTypterminRozp_par,
	dDataTerminRozp=@dDataTerminRozp_par,
	tCzasTerminRozp=@tCzasTerminRozp_par,
	eTypterminZak=@eTypterminZak_par,
	strTemat=@strTemat_par,
	strOpis=@strOpis_par,
	nNaklad=@nNaklad_par,
	pTypDzialania=@pTypDzialania_par,
	pProcedura=@pProcedura_par,
	wrefSzczegoly=@wrefSzczegoly_par,
	wrefSzczegoly_wrt=@wrefSzczegoly_wrt_par,
	pNadZadanie=@pNadZadanie_par,
	pPopZadanie=@pPopZadanie_par,
	pWykonawca=@pWykonawca_par,
	dDataPow=@dDataPow_par,
	tCzasPow=@tCzasPow_par,
	dDataRozp=@dDataRozp_par,
	tCzasRozp=@tCzasRozp_par,
	nZaawansowanie=@nZaawansowanie_par,
	dDataZakon=@dDataZakon_par,
	tCzasZakon=@tCzasZakon_par,
	strUwagi=@strUwagi_par,
	dDataZamk=@dDataZamk_par,
	tCzasZamk=@tCzasZamk_par,
	strCecha1=@strCecha1_par,
	strCecha2=@strCecha2_par,
	strCecha3=@strCecha3_par,
	dDataTerminZak=@dDataTerminZak_par,
	tCzasTerminZak=@tCzasTerminZak_par,
	pKlient=@pKlient_par,
	pSchematDekretacji=@pSchematDekretacji_par,
	pDowKsieg=@pDowKsieg_par,
	dDataPrzyp=@dDataPrzyp_par,
	tCzasPrzyp=@tCzasPrzyp_par,
	nIsSecurity=@nIsSecurity_par,
	pKlientPracownik=@pKlientPracownik_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadanie_delete')
	drop procedure n5zadanie_delete
go

create procedure n5zadanie_delete(@idobj_par integer) with encryption as 
	delete from n5zadanie where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadanie_maxid')
	drop procedure n5zadanie_maxid
go

create procedure n5zadanie_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zadanie
go

if exists (select * from sysobjects where name='n5zadanie_candel')
	drop procedure n5zadanie_candel
go

create procedure n5zadanie_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pNadZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pPopZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10125 as integer),idobj from n5zadaniezal where wrefZal=@idobj_par and wrefZal_wrt=10119
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10119
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pZadanie=@idobj_par
go

-- table: n5procedura
if exists (select * from sysobjects where name='n5procedura_select')
	drop procedure n5procedura_select
go

create procedure n5procedura_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@strOpis_par varchar(1024) output,
	@nModule_par integer output,
	@nInternalID_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strOpis_par=strOpis,
	@nModule_par=nModule,
	@nInternalID_par=nInternalID from n5procedura where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5procedura_insert')
	drop procedure n5procedura_insert
go

create procedure n5procedura_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strOpis_par varchar(1024),@nModule_par integer,@nInternalID_par integer) with encryption as 
	insert into n5procedura values(@idobj_par,@versionid_par,@strNazwa_par,@strOpis_par,@nModule_par,@nInternalID_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5procedura_update')
	drop procedure n5procedura_update
go

create procedure n5procedura_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strOpis_par varchar(1024),@nModule_par integer,@nInternalID_par integer) with encryption as 
	update n5procedura set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strOpis=@strOpis_par,
	nModule=@nModule_par,
	nInternalID=@nInternalID_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5procedura_delete')
	drop procedure n5procedura_delete
go

create procedure n5procedura_delete(@idobj_par integer) with encryption as 
	delete from n5procedura where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5procedura_maxid')
	drop procedure n5procedura_maxid
go

create procedure n5procedura_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5procedura
go

if exists (select * from sysobjects where name='n5procedura_candel')
	drop procedure n5procedura_candel
go

create procedure n5procedura_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pProcedura=@idobj_par
go

-- table: n5pozplatnosc
if exists (select * from sysobjects where name='n5pozplatnosc_select')
	drop procedure n5pozplatnosc_select
go

create procedure n5pozplatnosc_select(@idobj_par integer,@versionid_par integer output,
	@curPozKwotaPodm_par decimal(12,2) output,
	@curPozKwotaEwid_par decimal(12,2) output,
	@curPozKwotaTrans_par decimal(12,2) output,
	@curPozKursPodm_par decimal(14,4) output,
	@curPozKursEwid_par decimal(14,4) output,
	@pTransakcja_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@curPozKwotaPodm_par=curPozKwotaPodm,
	@curPozKwotaEwid_par=curPozKwotaEwid,
	@curPozKwotaTrans_par=curPozKwotaTrans,
	@curPozKursPodm_par=curPozKursPodm,
	@curPozKursEwid_par=curPozKursEwid,
	@pTransakcja_par=pTransakcja from n5pozplatnosc where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozplatnosc_insert')
	drop procedure n5pozplatnosc_insert
go

create procedure n5pozplatnosc_insert(@idobj_par integer,@versionid_par integer,@curPozKwotaPodm_par decimal(12,2),@curPozKwotaEwid_par decimal(12,2),@curPozKwotaTrans_par decimal(12,2),@curPozKursPodm_par decimal(14,4),@curPozKursEwid_par decimal(14,4),@pTransakcja_par integer) with encryption as 
	insert into n5pozplatnosc values(@idobj_par,@versionid_par,@curPozKwotaPodm_par,@curPozKwotaEwid_par,@curPozKwotaTrans_par,@curPozKursPodm_par,@curPozKursEwid_par,@pTransakcja_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozplatnosc_update')
	drop procedure n5pozplatnosc_update
go

create procedure n5pozplatnosc_update(@idobj_par integer,@versionid_par integer,@curPozKwotaPodm_par decimal(12,2),@curPozKwotaEwid_par decimal(12,2),@curPozKwotaTrans_par decimal(12,2),@curPozKursPodm_par decimal(14,4),@curPozKursEwid_par decimal(14,4),@pTransakcja_par integer) with encryption as 
	update n5pozplatnosc set VersionId=@versionid_par,
	curPozKwotaPodm=@curPozKwotaPodm_par,
	curPozKwotaEwid=@curPozKwotaEwid_par,
	curPozKwotaTrans=@curPozKwotaTrans_par,
	curPozKursPodm=@curPozKursPodm_par,
	curPozKursEwid=@curPozKursEwid_par,
	pTransakcja=@pTransakcja_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozplatnosc_delete')
	drop procedure n5pozplatnosc_delete
go

create procedure n5pozplatnosc_delete(@idobj_par integer) with encryption as 
	delete from n5pozplatnosc where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozplatnosc_maxid')
	drop procedure n5pozplatnosc_maxid
go

create procedure n5pozplatnosc_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozplatnosc
go

if exists (select * from sysobjects where name='n5pozplatnosc_candel')
	drop procedure n5pozplatnosc_candel
go

create procedure n5pozplatnosc_candel(@idobj_par integer) with encryption as 
go

-- table: n5wykonawca
if exists (select * from sysobjects where name='n5wykonawca_select')
	drop procedure n5wykonawca_select
go

create procedure n5wykonawca_select(@idobj_par integer,@versionid_par integer output,
	@strIndeks_par varchar(64) output,
	@wrefObiekt_par integer output,
	@wrefObiekt_wrt_par integer output,
	@strMetPow_par varchar(8) output) with encryption as 
	select @versionid_par=VersionId,
	@strIndeks_par=strIndeks,
	@wrefObiekt_par=wrefObiekt,
	@wrefObiekt_wrt_par=wrefObiekt_wrt,
	@strMetPow_par=strMetPow from n5wykonawca where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wykonawca_insert')
	drop procedure n5wykonawca_insert
go

create procedure n5wykonawca_insert(@idobj_par integer,@versionid_par integer,@strIndeks_par varchar(64),@wrefObiekt_par integer,@wrefObiekt_wrt_par integer,@strMetPow_par varchar(8)) with encryption as 
	insert into n5wykonawca values(@idobj_par,@versionid_par,@strIndeks_par,@wrefObiekt_par,@wrefObiekt_wrt_par,@strMetPow_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5wykonawca_update')
	drop procedure n5wykonawca_update
go

create procedure n5wykonawca_update(@idobj_par integer,@versionid_par integer,@strIndeks_par varchar(64),@wrefObiekt_par integer,@wrefObiekt_wrt_par integer,@strMetPow_par varchar(8)) with encryption as 
	update n5wykonawca set VersionId=@versionid_par,
	strIndeks=@strIndeks_par,
	wrefObiekt=@wrefObiekt_par,
	wrefObiekt_wrt=@wrefObiekt_wrt_par,
	strMetPow=@strMetPow_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wykonawca_delete')
	drop procedure n5wykonawca_delete
go

create procedure n5wykonawca_delete(@idobj_par integer) with encryption as 
	delete from n5wykonawca where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5wykonawca_maxid')
	drop procedure n5wykonawca_maxid
go

create procedure n5wykonawca_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5wykonawca
go

if exists (select * from sysobjects where name='n5wykonawca_candel')
	drop procedure n5wykonawca_candel
go

create procedure n5wykonawca_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10107 as integer),idobj from n5uzytkownik where pWykonawca=@idobj_par
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pZlecajacy=@idobj_par
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pWykonawca=@idobj_par
union
select TOP 5 'typeid'=cast(10163 as integer),idobj from n5zadaniedw where pWykonawcaDW=@idobj_par
go

-- table: choicelistitem
if exists (select * from sysobjects where name='choicelistitem_select')
	drop procedure choicelistitem_select
go

create procedure choicelistitem_select(@idobj_par integer,@versionid_par integer output,
	@IdElement_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@IdElement_par=IdElement from choicelistitem where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelistitem_insert')
	drop procedure choicelistitem_insert
go

create procedure choicelistitem_insert(@idobj_par integer,@versionid_par integer,@IdElement_par integer) with encryption as 
	insert into choicelistitem values(@idobj_par,@versionid_par,@IdElement_par)
return @@rowcount
go

if exists (select * from sysobjects where name='choicelistitem_update')
	drop procedure choicelistitem_update
go

create procedure choicelistitem_update(@idobj_par integer,@versionid_par integer,@IdElement_par integer) with encryption as 
	update choicelistitem set VersionId=@versionid_par,
	IdElement=@IdElement_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelistitem_delete')
	drop procedure choicelistitem_delete
go

create procedure choicelistitem_delete(@idobj_par integer) with encryption as 
	delete from choicelistitem where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelistitem_maxid')
	drop procedure choicelistitem_maxid
go

create procedure choicelistitem_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from choicelistitem
go

if exists (select * from sysobjects where name='choicelistitem_candel')
	drop procedure choicelistitem_candel
go

create procedure choicelistitem_candel(@idobj_par integer) with encryption as 
go

-- table: choicelist
if exists (select * from sysobjects where name='choicelist_select')
	drop procedure choicelist_select
go

create procedure choicelist_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@nTypeId_par integer output,
	@edynamic_par integer output,
	@nIsSecurity_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@nTypeId_par=nTypeId,
	@edynamic_par=edynamic,
	@nIsSecurity_par=nIsSecurity from choicelist where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelist_insert')
	drop procedure choicelist_insert
go

create procedure choicelist_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@nTypeId_par integer,@edynamic_par integer,@nIsSecurity_par integer) with encryption as 
	insert into choicelist values(@idobj_par,@versionid_par,@strNazwa_par,@nTypeId_par,@edynamic_par,@nIsSecurity_par)
return @@rowcount
go

if exists (select * from sysobjects where name='choicelist_update')
	drop procedure choicelist_update
go

create procedure choicelist_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@nTypeId_par integer,@edynamic_par integer,@nIsSecurity_par integer) with encryption as 
	update choicelist set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	nTypeId=@nTypeId_par,
	edynamic=@edynamic_par,
	nIsSecurity=@nIsSecurity_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelist_delete')
	drop procedure choicelist_delete
go

create procedure choicelist_delete(@idobj_par integer) with encryption as 
	delete from choicelist where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='choicelist_maxid')
	drop procedure choicelist_maxid
go

create procedure choicelist_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from choicelist
go

if exists (select * from sysobjects where name='choicelist_candel')
	drop procedure choicelist_candel
go

create procedure choicelist_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10127 as integer),idobj from n5WizzardEmail where pChoiceList=@idobj_par
union
select TOP 5 'typeid'=cast(10217 as integer),idobj from n5plwzorlp where pCLPracownicy=@idobj_par
union
select TOP 5 'typeid'=cast(10217 as integer),idobj from n5plwzorlp where pCLSkladniki=@idobj_par
go

-- table: n5zadaniezal
if exists (select * from sysobjects where name='n5zadaniezal_select')
	drop procedure n5zadaniezal_select
go

create procedure n5zadaniezal_select(@idobj_par integer,@versionid_par integer output,
	@wrefZal_par integer output,
	@wrefZal_wrt_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wrefZal_par=wrefZal,
	@wrefZal_wrt_par=wrefZal_wrt from n5zadaniezal where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniezal_insert')
	drop procedure n5zadaniezal_insert
go

create procedure n5zadaniezal_insert(@idobj_par integer,@versionid_par integer,@wrefZal_par integer,@wrefZal_wrt_par integer) with encryption as 
	insert into n5zadaniezal values(@idobj_par,@versionid_par,@wrefZal_par,@wrefZal_wrt_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniezal_update')
	drop procedure n5zadaniezal_update
go

create procedure n5zadaniezal_update(@idobj_par integer,@versionid_par integer,@wrefZal_par integer,@wrefZal_wrt_par integer) with encryption as 
	update n5zadaniezal set VersionId=@versionid_par,
	wrefZal=@wrefZal_par,
	wrefZal_wrt=@wrefZal_wrt_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniezal_delete')
	drop procedure n5zadaniezal_delete
go

create procedure n5zadaniezal_delete(@idobj_par integer) with encryption as 
	delete from n5zadaniezal where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniezal_maxid')
	drop procedure n5zadaniezal_maxid
go

create procedure n5zadaniezal_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zadaniezal
go

if exists (select * from sysobjects where name='n5zadaniezal_candel')
	drop procedure n5zadaniezal_candel
go

create procedure n5zadaniezal_candel(@idobj_par integer) with encryption as 
go

-- table: n5WizzardEmailDokumElem
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_select')
	drop procedure n5WizzardEmailDokumElem_select
go

create procedure n5WizzardEmailDokumElem_select(@idobj_par integer,@versionid_par integer output,
	@pDokument_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pDokument_par=pDokument from n5WizzardEmailDokumElem where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_insert')
	drop procedure n5WizzardEmailDokumElem_insert
go

create procedure n5WizzardEmailDokumElem_insert(@idobj_par integer,@versionid_par integer,@pDokument_par integer) with encryption as 
	insert into n5WizzardEmailDokumElem values(@idobj_par,@versionid_par,@pDokument_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_update')
	drop procedure n5WizzardEmailDokumElem_update
go

create procedure n5WizzardEmailDokumElem_update(@idobj_par integer,@versionid_par integer,@pDokument_par integer) with encryption as 
	update n5WizzardEmailDokumElem set VersionId=@versionid_par,
	pDokument=@pDokument_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_delete')
	drop procedure n5WizzardEmailDokumElem_delete
go

create procedure n5WizzardEmailDokumElem_delete(@idobj_par integer) with encryption as 
	delete from n5WizzardEmailDokumElem where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_maxid')
	drop procedure n5WizzardEmailDokumElem_maxid
go

create procedure n5WizzardEmailDokumElem_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5WizzardEmailDokumElem
go

if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_candel')
	drop procedure n5WizzardEmailDokumElem_candel
go

create procedure n5WizzardEmailDokumElem_candel(@idobj_par integer) with encryption as 
go

-- table: n5WizzardEmail
if exists (select * from sysobjects where name='n5WizzardEmail_select')
	drop procedure n5WizzardEmail_select
go

create procedure n5WizzardEmail_select(@idobj_par integer,@versionid_par integer output,
	@pChoiceList_par integer output,
	@cZarejestruj_par varchar(1) output,
	@cWysylkaEmail_par varchar(1) output,
	@cWysylkaFax_par varchar(1) output,
	@cWysylkaWydruk_par varchar(1) output,
	@cWysylkaEmailFax_par varchar(1) output,
	@cWysylkaEmailWydruk_par varchar(32) output,
	@strTytul_par varchar(512) output,
	@strTresc_par varchar(1024) output,
	@cSzablon_par varchar(1) output) with encryption as 
	select @versionid_par=VersionId,
	@pChoiceList_par=pChoiceList,
	@cZarejestruj_par=cZarejestruj,
	@cWysylkaEmail_par=cWysylkaEmail,
	@cWysylkaFax_par=cWysylkaFax,
	@cWysylkaWydruk_par=cWysylkaWydruk,
	@cWysylkaEmailFax_par=cWysylkaEmailFax,
	@cWysylkaEmailWydruk_par=cWysylkaEmailWydruk,
	@strTytul_par=strTytul,
	@strTresc_par=strTresc,
	@cSzablon_par=cSzablon from n5WizzardEmail where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmail_insert')
	drop procedure n5WizzardEmail_insert
go

create procedure n5WizzardEmail_insert(@idobj_par integer,@versionid_par integer,@pChoiceList_par integer,@cZarejestruj_par varchar(1),@cWysylkaEmail_par varchar(1),@cWysylkaFax_par varchar(1),@cWysylkaWydruk_par varchar(1),@cWysylkaEmailFax_par varchar(1),@cWysylkaEmailWydruk_par varchar(32),@strTytul_par varchar(512),@strTresc_par varchar(1024),@cSzablon_par varchar(1)) with encryption as 
	insert into n5WizzardEmail values(@idobj_par,@versionid_par,@pChoiceList_par,@cZarejestruj_par,@cWysylkaEmail_par,@cWysylkaFax_par,@cWysylkaWydruk_par,@cWysylkaEmailFax_par,@cWysylkaEmailWydruk_par,@strTytul_par,@strTresc_par,@cSzablon_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmail_update')
	drop procedure n5WizzardEmail_update
go

create procedure n5WizzardEmail_update(@idobj_par integer,@versionid_par integer,@pChoiceList_par integer,@cZarejestruj_par varchar(1),@cWysylkaEmail_par varchar(1),@cWysylkaFax_par varchar(1),@cWysylkaWydruk_par varchar(1),@cWysylkaEmailFax_par varchar(1),@cWysylkaEmailWydruk_par varchar(32),@strTytul_par varchar(512),@strTresc_par varchar(1024),@cSzablon_par varchar(1)) with encryption as 
	update n5WizzardEmail set VersionId=@versionid_par,
	pChoiceList=@pChoiceList_par,
	cZarejestruj=@cZarejestruj_par,
	cWysylkaEmail=@cWysylkaEmail_par,
	cWysylkaFax=@cWysylkaFax_par,
	cWysylkaWydruk=@cWysylkaWydruk_par,
	cWysylkaEmailFax=@cWysylkaEmailFax_par,
	cWysylkaEmailWydruk=@cWysylkaEmailWydruk_par,
	strTytul=@strTytul_par,
	strTresc=@strTresc_par,
	cSzablon=@cSzablon_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmail_delete')
	drop procedure n5WizzardEmail_delete
go

create procedure n5WizzardEmail_delete(@idobj_par integer) with encryption as 
	delete from n5WizzardEmail where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5WizzardEmail_maxid')
	drop procedure n5WizzardEmail_maxid
go

create procedure n5WizzardEmail_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5WizzardEmail
go

if exists (select * from sysobjects where name='n5WizzardEmail_candel')
	drop procedure n5WizzardEmail_candel
go

create procedure n5WizzardEmail_candel(@idobj_par integer) with encryption as 
go

-- table: n5SendEmail
if exists (select * from sysobjects where name='n5SendEmail_select')
	drop procedure n5SendEmail_select
go

create procedure n5SendEmail_select(@idobj_par integer,@versionid_par integer output,
	@wpNadawca_par integer output,
	@wpNadawca_wrt_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wpNadawca_par=wpNadawca,
	@wpNadawca_wrt_par=wpNadawca_wrt from n5SendEmail where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5SendEmail_insert')
	drop procedure n5SendEmail_insert
go

create procedure n5SendEmail_insert(@idobj_par integer,@versionid_par integer,@wpNadawca_par integer,@wpNadawca_wrt_par integer) with encryption as 
	insert into n5SendEmail values(@idobj_par,@versionid_par,@wpNadawca_par,@wpNadawca_wrt_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5SendEmail_update')
	drop procedure n5SendEmail_update
go

create procedure n5SendEmail_update(@idobj_par integer,@versionid_par integer,@wpNadawca_par integer,@wpNadawca_wrt_par integer) with encryption as 
	update n5SendEmail set VersionId=@versionid_par,
	wpNadawca=@wpNadawca_par,
	wpNadawca_wrt=@wpNadawca_wrt_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5SendEmail_delete')
	drop procedure n5SendEmail_delete
go

create procedure n5SendEmail_delete(@idobj_par integer) with encryption as 
	delete from n5SendEmail where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5SendEmail_maxid')
	drop procedure n5SendEmail_maxid
go

create procedure n5SendEmail_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5SendEmail
go

if exists (select * from sysobjects where name='n5SendEmail_candel')
	drop procedure n5SendEmail_candel
go

create procedure n5SendEmail_candel(@idobj_par integer) with encryption as 
go

-- table: n5sprzedaz
if exists (select * from sysobjects where name='n5sprzedaz_select')
	drop procedure n5sprzedaz_select
go

create procedure n5sprzedaz_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@dDataWyst_par datetime output,
	@dDataSprzed_par datetime output,
	@dDataPlat_par datetime output,
	@pSposobPlatnosci_par integer output,
	@pKlient_par integer output,
	@pKlient_JO_par integer output,
	@pKlientPracownik_par integer output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@eSposVAT_par integer output,
	@eNettoBrutto_par integer output,
	@pZadanie_par integer output,
	@curSumaNetto_par decimal(12,2) output,
	@curSumaVAT_par decimal(12,2) output,
	@curSumaBrutto_par decimal(12,2) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@pTransakcja_par integer output,
	@curNetto0_par decimal(12,2) output,
	@curNettoZw_par decimal(12,2) output,
	@curNettoNp_par decimal(12,2) output,
	@curNetto2_par decimal(12,2) output,
	@curVat2_par decimal(12,2) output,
	@curNetto3_par decimal(12,2) output,
	@curVat3_par decimal(12,2) output,
	@curNetto4_par decimal(12,2) output,
	@curVat4_par decimal(12,2) output,
	@curNetto7_par decimal(12,2) output,
	@curVat7_par decimal(12,2) output,
	@curNetto12_par decimal(12,2) output,
	@curVat12_par decimal(12,2) output,
	@curNetto17_par decimal(12,2) output,
	@curVat17_par decimal(12,2) output,
	@curNetto22_par decimal(12,2) output,
	@curVat22_par decimal(12,2) output,
	@pPopSprzed_par integer output,
	@pFaktura_par integer output,
	@cAutoCalc_par varchar(1) output,
	@curSumaWal_par decimal(12,2) output,
	@pWaluta_par integer output,
	@pRozlVat_par integer output,
	@pZamowienie_par integer output,
	@curKurs_par decimal(14,4) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@dDataWyst_par=dDataWyst,
	@dDataSprzed_par=dDataSprzed,
	@dDataPlat_par=dDataPlat,
	@pSposobPlatnosci_par=pSposobPlatnosci,
	@pKlient_par=pKlient,
	@pKlient_JO_par=pKlient_JO,
	@pKlientPracownik_par=pKlientPracownik,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@eSposVAT_par=eSposVAT,
	@eNettoBrutto_par=eNettoBrutto,
	@pZadanie_par=pZadanie,
	@curSumaNetto_par=curSumaNetto,
	@curSumaVAT_par=curSumaVAT,
	@curSumaBrutto_par=curSumaBrutto,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@pTransakcja_par=pTransakcja,
	@curNetto0_par=curNetto0,
	@curNettoZw_par=curNettoZw,
	@curNettoNp_par=curNettoNp,
	@curNetto2_par=curNetto2,
	@curVat2_par=curVat2,
	@curNetto3_par=curNetto3,
	@curVat3_par=curVat3,
	@curNetto4_par=curNetto4,
	@curVat4_par=curVat4,
	@curNetto7_par=curNetto7,
	@curVat7_par=curVat7,
	@curNetto12_par=curNetto12,
	@curVat12_par=curVat12,
	@curNetto17_par=curNetto17,
	@curVat17_par=curVat17,
	@curNetto22_par=curNetto22,
	@curVat22_par=curVat22,
	@pPopSprzed_par=pPopSprzed,
	@pFaktura_par=pFaktura,
	@cAutoCalc_par=cAutoCalc,
	@curSumaWal_par=curSumaWal,
	@pWaluta_par=pWaluta,
	@pRozlVat_par=pRozlVat,
	@pZamowienie_par=pZamowienie,
	@curKurs_par=curKurs,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5sprzedaz where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sprzedaz_insert')
	drop procedure n5sprzedaz_insert
go

create procedure n5sprzedaz_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@dDataSprzed_par datetime,@dDataPlat_par datetime,@pSposobPlatnosci_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@eSposVAT_par integer,@eNettoBrutto_par integer,@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pTransakcja_par integer,@curNetto0_par decimal(12,2),@curNettoZw_par decimal(12,2),@curNettoNp_par decimal(12,2),@curNetto2_par decimal(12,2),@curVat2_par decimal(12,2),@curNetto3_par decimal(12,2),@curVat3_par decimal(12,2),@curNetto4_par decimal(12,2),@curVat4_par decimal(12,2),@curNetto7_par decimal(12,2),@curVat7_par decimal(12,2),@curNetto12_par decimal(12,2),@curVat12_par decimal(12,2),@curNetto17_par decimal(12,2),@curVat17_par decimal(12,2),@curNetto22_par decimal(12,2),@curVat22_par decimal(12,2),@pPopSprzed_par integer,@pFaktura_par integer,@cAutoCalc_par varchar(1),@curSumaWal_par decimal(12,2),@pWaluta_par integer,@pRozlVat_par integer,@pZamowienie_par integer,@curKurs_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5sprzedaz values(@idobj_par,@versionid_par,@strNrDok_par,@dDataWyst_par,@dDataSprzed_par,@dDataPlat_par,@pSposobPlatnosci_par,@pKlient_par,@pKlient_JO_par,@pKlientPracownik_par,@pUzytRej_par,@strUwagi_par,@eSposVAT_par,@eNettoBrutto_par,@pZadanie_par,@curSumaNetto_par,@curSumaVAT_par,@curSumaBrutto_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@pTransakcja_par,@curNetto0_par,@curNettoZw_par,@curNettoNp_par,@curNetto2_par,@curVat2_par,@curNetto3_par,@curVat3_par,@curNetto4_par,@curVat4_par,@curNetto7_par,@curVat7_par,@curNetto12_par,@curVat12_par,@curNetto17_par,@curVat17_par,@curNetto22_par,@curVat22_par,@pPopSprzed_par,@pFaktura_par,@cAutoCalc_par,@curSumaWal_par,@pWaluta_par,@pRozlVat_par,@pZamowienie_par,@curKurs_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5sprzedaz_update')
	drop procedure n5sprzedaz_update
go

create procedure n5sprzedaz_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@dDataSprzed_par datetime,@dDataPlat_par datetime,@pSposobPlatnosci_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@eSposVAT_par integer,@eNettoBrutto_par integer,@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pTransakcja_par integer,@curNetto0_par decimal(12,2),@curNettoZw_par decimal(12,2),@curNettoNp_par decimal(12,2),@curNetto2_par decimal(12,2),@curVat2_par decimal(12,2),@curNetto3_par decimal(12,2),@curVat3_par decimal(12,2),@curNetto4_par decimal(12,2),@curVat4_par decimal(12,2),@curNetto7_par decimal(12,2),@curVat7_par decimal(12,2),@curNetto12_par decimal(12,2),@curVat12_par decimal(12,2),@curNetto17_par decimal(12,2),@curVat17_par decimal(12,2),@curNetto22_par decimal(12,2),@curVat22_par decimal(12,2),@pPopSprzed_par integer,@pFaktura_par integer,@cAutoCalc_par varchar(1),@curSumaWal_par decimal(12,2),@pWaluta_par integer,@pRozlVat_par integer,@pZamowienie_par integer,@curKurs_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5sprzedaz set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	dDataWyst=@dDataWyst_par,
	dDataSprzed=@dDataSprzed_par,
	dDataPlat=@dDataPlat_par,
	pSposobPlatnosci=@pSposobPlatnosci_par,
	pKlient=@pKlient_par,
	pKlient_JO=@pKlient_JO_par,
	pKlientPracownik=@pKlientPracownik_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	eSposVAT=@eSposVAT_par,
	eNettoBrutto=@eNettoBrutto_par,
	pZadanie=@pZadanie_par,
	curSumaNetto=@curSumaNetto_par,
	curSumaVAT=@curSumaVAT_par,
	curSumaBrutto=@curSumaBrutto_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	pTransakcja=@pTransakcja_par,
	curNetto0=@curNetto0_par,
	curNettoZw=@curNettoZw_par,
	curNettoNp=@curNettoNp_par,
	curNetto2=@curNetto2_par,
	curVat2=@curVat2_par,
	curNetto3=@curNetto3_par,
	curVat3=@curVat3_par,
	curNetto4=@curNetto4_par,
	curVat4=@curVat4_par,
	curNetto7=@curNetto7_par,
	curVat7=@curVat7_par,
	curNetto12=@curNetto12_par,
	curVat12=@curVat12_par,
	curNetto17=@curNetto17_par,
	curVat17=@curVat17_par,
	curNetto22=@curNetto22_par,
	curVat22=@curVat22_par,
	pPopSprzed=@pPopSprzed_par,
	pFaktura=@pFaktura_par,
	cAutoCalc=@cAutoCalc_par,
	curSumaWal=@curSumaWal_par,
	pWaluta=@pWaluta_par,
	pRozlVat=@pRozlVat_par,
	pZamowienie=@pZamowienie_par,
	curKurs=@curKurs_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sprzedaz_delete')
	drop procedure n5sprzedaz_delete
go

create procedure n5sprzedaz_delete(@idobj_par integer) with encryption as 
	delete from n5sprzedaz where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sprzedaz_maxid')
	drop procedure n5sprzedaz_maxid
go

create procedure n5sprzedaz_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5sprzedaz
go

if exists (select * from sysobjects where name='n5sprzedaz_candel')
	drop procedure n5sprzedaz_candel
go

create procedure n5sprzedaz_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10129
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pPopSprzed=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pFaktura=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10129
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where wrefDokHandl=@idobj_par and wrefDokHandl_wrt=10129
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where wrefDokument=@idobj_par and wrefDokument_wrt=10129
go

-- table: n5opakowanie_produktu
if exists (select * from sysobjects where name='n5opakowanie_produktu_select')
	drop procedure n5opakowanie_produktu_select
go

create procedure n5opakowanie_produktu_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(32) output,
	@eRodzaj_par integer output,
	@pOpakowanieJedn_par integer output,
	@currKrotnosc_par decimal(14,4) output,
	@curIlosc_par decimal(14,4) output,
	@strEAN_par varchar(32) output,
	@curWagaNetto_par decimal(14,4) output,
	@curWagaBrutto_par decimal(14,4) output,
	@pJednostkaWagi_par integer output,
	@curCenaNetto1_par decimal(14,4) output,
	@curCenaBrutto1_par decimal(14,4) output,
	@curCenaNetto2_par decimal(14,4) output,
	@curCenaBrutto2_par decimal(14,4) output,
	@curCenaNetto3_par decimal(14,4) output,
	@curCenaBrutto3_par decimal(14,4) output,
	@curCenaNetto4_par decimal(14,4) output,
	@curCenaBrutto4_par decimal(14,4) output,
	@curCenaNetto5_par decimal(14,4) output,
	@curCenaBrutto5_par decimal(14,4) output,
	@curCenaNetto6_par decimal(14,4) output,
	@curCenaBrutto6_par decimal(14,4) output,
	@pWaluta_par integer output,
	@strKodOpak_par varchar(8) output,
	@pJednOpak_par integer output,
	@pZamiennik_par integer output,
	@strNazwaMiedzynarodowa_par varchar(32) output,
	@curIloscMin_par decimal(14,4) output,
	@curIloscMax_par decimal(14,4) output,
	@curNarzutMin_par decimal(14,4) output,
	@curNarzutMax_par decimal(14,4) output,
	@curNarzutZal_par decimal(14,4) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@eRodzaj_par=eRodzaj,
	@pOpakowanieJedn_par=pOpakowanieJedn,
	@currKrotnosc_par=currKrotnosc,
	@curIlosc_par=curIlosc,
	@strEAN_par=strEAN,
	@curWagaNetto_par=curWagaNetto,
	@curWagaBrutto_par=curWagaBrutto,
	@pJednostkaWagi_par=pJednostkaWagi,
	@curCenaNetto1_par=curCenaNetto1,
	@curCenaBrutto1_par=curCenaBrutto1,
	@curCenaNetto2_par=curCenaNetto2,
	@curCenaBrutto2_par=curCenaBrutto2,
	@curCenaNetto3_par=curCenaNetto3,
	@curCenaBrutto3_par=curCenaBrutto3,
	@curCenaNetto4_par=curCenaNetto4,
	@curCenaBrutto4_par=curCenaBrutto4,
	@curCenaNetto5_par=curCenaNetto5,
	@curCenaBrutto5_par=curCenaBrutto5,
	@curCenaNetto6_par=curCenaNetto6,
	@curCenaBrutto6_par=curCenaBrutto6,
	@pWaluta_par=pWaluta,
	@strKodOpak_par=strKodOpak,
	@pJednOpak_par=pJednOpak,
	@pZamiennik_par=pZamiennik,
	@strNazwaMiedzynarodowa_par=strNazwaMiedzynarodowa,
	@curIloscMin_par=curIloscMin,
	@curIloscMax_par=curIloscMax,
	@curNarzutMin_par=curNarzutMin,
	@curNarzutMax_par=curNarzutMax,
	@curNarzutZal_par=curNarzutZal from n5opakowanie_produktu where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opakowanie_produktu_insert')
	drop procedure n5opakowanie_produktu_insert
go

create procedure n5opakowanie_produktu_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@eRodzaj_par integer,@pOpakowanieJedn_par integer,@currKrotnosc_par decimal(14,4),@curIlosc_par decimal(14,4),@strEAN_par varchar(32),@curWagaNetto_par decimal(14,4),@curWagaBrutto_par decimal(14,4),@pJednostkaWagi_par integer,@curCenaNetto1_par decimal(14,4),@curCenaBrutto1_par decimal(14,4),@curCenaNetto2_par decimal(14,4),@curCenaBrutto2_par decimal(14,4),@curCenaNetto3_par decimal(14,4),@curCenaBrutto3_par decimal(14,4),@curCenaNetto4_par decimal(14,4),@curCenaBrutto4_par decimal(14,4),@curCenaNetto5_par decimal(14,4),@curCenaBrutto5_par decimal(14,4),@curCenaNetto6_par decimal(14,4),@curCenaBrutto6_par decimal(14,4),@pWaluta_par integer,@strKodOpak_par varchar(8),@pJednOpak_par integer,@pZamiennik_par integer,@strNazwaMiedzynarodowa_par varchar(32),@curIloscMin_par decimal(14,4),@curIloscMax_par decimal(14,4),@curNarzutMin_par decimal(14,4),@curNarzutMax_par decimal(14,4),@curNarzutZal_par decimal(14,4)) with encryption as 
	insert into n5opakowanie_produktu values(@idobj_par,@versionid_par,@strNazwa_par,@eRodzaj_par,@pOpakowanieJedn_par,@currKrotnosc_par,@curIlosc_par,@strEAN_par,@curWagaNetto_par,@curWagaBrutto_par,@pJednostkaWagi_par,@curCenaNetto1_par,@curCenaBrutto1_par,@curCenaNetto2_par,@curCenaBrutto2_par,@curCenaNetto3_par,@curCenaBrutto3_par,@curCenaNetto4_par,@curCenaBrutto4_par,@curCenaNetto5_par,@curCenaBrutto5_par,@curCenaNetto6_par,@curCenaBrutto6_par,@pWaluta_par,@strKodOpak_par,@pJednOpak_par,@pZamiennik_par,@strNazwaMiedzynarodowa_par,@curIloscMin_par,@curIloscMax_par,@curNarzutMin_par,@curNarzutMax_par,@curNarzutZal_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5opakowanie_produktu_update')
	drop procedure n5opakowanie_produktu_update
go

create procedure n5opakowanie_produktu_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@eRodzaj_par integer,@pOpakowanieJedn_par integer,@currKrotnosc_par decimal(14,4),@curIlosc_par decimal(14,4),@strEAN_par varchar(32),@curWagaNetto_par decimal(14,4),@curWagaBrutto_par decimal(14,4),@pJednostkaWagi_par integer,@curCenaNetto1_par decimal(14,4),@curCenaBrutto1_par decimal(14,4),@curCenaNetto2_par decimal(14,4),@curCenaBrutto2_par decimal(14,4),@curCenaNetto3_par decimal(14,4),@curCenaBrutto3_par decimal(14,4),@curCenaNetto4_par decimal(14,4),@curCenaBrutto4_par decimal(14,4),@curCenaNetto5_par decimal(14,4),@curCenaBrutto5_par decimal(14,4),@curCenaNetto6_par decimal(14,4),@curCenaBrutto6_par decimal(14,4),@pWaluta_par integer,@strKodOpak_par varchar(8),@pJednOpak_par integer,@pZamiennik_par integer,@strNazwaMiedzynarodowa_par varchar(32),@curIloscMin_par decimal(14,4),@curIloscMax_par decimal(14,4),@curNarzutMin_par decimal(14,4),@curNarzutMax_par decimal(14,4),@curNarzutZal_par decimal(14,4)) with encryption as 
	update n5opakowanie_produktu set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	eRodzaj=@eRodzaj_par,
	pOpakowanieJedn=@pOpakowanieJedn_par,
	currKrotnosc=@currKrotnosc_par,
	curIlosc=@curIlosc_par,
	strEAN=@strEAN_par,
	curWagaNetto=@curWagaNetto_par,
	curWagaBrutto=@curWagaBrutto_par,
	pJednostkaWagi=@pJednostkaWagi_par,
	curCenaNetto1=@curCenaNetto1_par,
	curCenaBrutto1=@curCenaBrutto1_par,
	curCenaNetto2=@curCenaNetto2_par,
	curCenaBrutto2=@curCenaBrutto2_par,
	curCenaNetto3=@curCenaNetto3_par,
	curCenaBrutto3=@curCenaBrutto3_par,
	curCenaNetto4=@curCenaNetto4_par,
	curCenaBrutto4=@curCenaBrutto4_par,
	curCenaNetto5=@curCenaNetto5_par,
	curCenaBrutto5=@curCenaBrutto5_par,
	curCenaNetto6=@curCenaNetto6_par,
	curCenaBrutto6=@curCenaBrutto6_par,
	pWaluta=@pWaluta_par,
	strKodOpak=@strKodOpak_par,
	pJednOpak=@pJednOpak_par,
	pZamiennik=@pZamiennik_par,
	strNazwaMiedzynarodowa=@strNazwaMiedzynarodowa_par,
	curIloscMin=@curIloscMin_par,
	curIloscMax=@curIloscMax_par,
	curNarzutMin=@curNarzutMin_par,
	curNarzutMax=@curNarzutMax_par,
	curNarzutZal=@curNarzutZal_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opakowanie_produktu_delete')
	drop procedure n5opakowanie_produktu_delete
go

create procedure n5opakowanie_produktu_delete(@idobj_par integer) with encryption as 
	delete from n5opakowanie_produktu where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opakowanie_produktu_maxid')
	drop procedure n5opakowanie_produktu_maxid
go

create procedure n5opakowanie_produktu_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5opakowanie_produktu
go

if exists (select * from sysobjects where name='n5opakowanie_produktu_candel')
	drop procedure n5opakowanie_produktu_candel
go

create procedure n5opakowanie_produktu_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10130 as integer),idobj from n5opakowanie_produktu where pOpakowanieJedn=@idobj_par
union
select TOP 5 'typeid'=cast(10130 as integer),idobj from n5opakowanie_produktu where pZamiennik=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pOpakZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pOpakDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pOpakZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pOpakDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10182 as integer),idobj from n5stanmag where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10184 as integer),idobj from n5pozrecepta where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10185 as integer),idobj from n5recepta where pWyrOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pOpak=@idobj_par
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where pOpak=@idobj_par
go

-- table: n5produkt
if exists (select * from sysobjects where name='n5produkt_select')
	drop procedure n5produkt_select
go

create procedure n5produkt_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@strNazwaMiedzynarodowa_par varchar(128) output,
	@strIndeks_par varchar(32) output,
	@strKodCelny_par varchar(32) output,
	@strKodPKWiU_par varchar(32) output,
	@eVAT_par integer output,
	@strOpis_par varchar(512) output,
	@pUlotka_par integer output,
	@pInstrukcja_par integer output,
	@pJednostkaEwid_par integer output,
	@eAktywny_par integer output,
	@pGrupaProd_par integer output,
	@strCecha1_par varchar(128) output,
	@strCecha2_par varchar(128) output,
	@strCecha3_par varchar(128) output,
	@eRodzaj_par integer output,
	@cProdukowalny_par varchar(1) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strNazwaMiedzynarodowa_par=strNazwaMiedzynarodowa,
	@strIndeks_par=strIndeks,
	@strKodCelny_par=strKodCelny,
	@strKodPKWiU_par=strKodPKWiU,
	@eVAT_par=eVAT,
	@strOpis_par=strOpis,
	@pUlotka_par=pUlotka,
	@pInstrukcja_par=pInstrukcja,
	@pJednostkaEwid_par=pJednostkaEwid,
	@eAktywny_par=eAktywny,
	@pGrupaProd_par=pGrupaProd,
	@strCecha1_par=strCecha1,
	@strCecha2_par=strCecha2,
	@strCecha3_par=strCecha3,
	@eRodzaj_par=eRodzaj,
	@cProdukowalny_par=cProdukowalny from n5produkt where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5produkt_insert')
	drop procedure n5produkt_insert
go

create procedure n5produkt_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNazwaMiedzynarodowa_par varchar(128),@strIndeks_par varchar(32),@strKodCelny_par varchar(32),@strKodPKWiU_par varchar(32),@eVAT_par integer,@strOpis_par varchar(512),@pUlotka_par integer,@pInstrukcja_par integer,@pJednostkaEwid_par integer,@eAktywny_par integer,@pGrupaProd_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@eRodzaj_par integer,@cProdukowalny_par varchar(1)) with encryption as 
	insert into n5produkt values(@idobj_par,@versionid_par,@strNazwa_par,@strNazwaMiedzynarodowa_par,@strIndeks_par,@strKodCelny_par,@strKodPKWiU_par,@eVAT_par,@strOpis_par,@pUlotka_par,@pInstrukcja_par,@pJednostkaEwid_par,@eAktywny_par,@pGrupaProd_par,@strCecha1_par,@strCecha2_par,@strCecha3_par,@eRodzaj_par,@cProdukowalny_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5produkt_update')
	drop procedure n5produkt_update
go

create procedure n5produkt_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNazwaMiedzynarodowa_par varchar(128),@strIndeks_par varchar(32),@strKodCelny_par varchar(32),@strKodPKWiU_par varchar(32),@eVAT_par integer,@strOpis_par varchar(512),@pUlotka_par integer,@pInstrukcja_par integer,@pJednostkaEwid_par integer,@eAktywny_par integer,@pGrupaProd_par integer,@strCecha1_par varchar(128),@strCecha2_par varchar(128),@strCecha3_par varchar(128),@eRodzaj_par integer,@cProdukowalny_par varchar(1)) with encryption as 
	update n5produkt set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strNazwaMiedzynarodowa=@strNazwaMiedzynarodowa_par,
	strIndeks=@strIndeks_par,
	strKodCelny=@strKodCelny_par,
	strKodPKWiU=@strKodPKWiU_par,
	eVAT=@eVAT_par,
	strOpis=@strOpis_par,
	pUlotka=@pUlotka_par,
	pInstrukcja=@pInstrukcja_par,
	pJednostkaEwid=@pJednostkaEwid_par,
	eAktywny=@eAktywny_par,
	pGrupaProd=@pGrupaProd_par,
	strCecha1=@strCecha1_par,
	strCecha2=@strCecha2_par,
	strCecha3=@strCecha3_par,
	eRodzaj=@eRodzaj_par,
	cProdukowalny=@cProdukowalny_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5produkt_delete')
	drop procedure n5produkt_delete
go

create procedure n5produkt_delete(@idobj_par integer) with encryption as 
	delete from n5produkt where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5produkt_maxid')
	drop procedure n5produkt_maxid
go

create procedure n5produkt_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5produkt
go

if exists (select * from sysobjects where name='n5produkt_candel')
	drop procedure n5produkt_candel
go

create procedure n5produkt_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pProdZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pProdDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pProdZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pProdDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10182 as integer),idobj from n5stanmag where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10184 as integer),idobj from n5pozrecepta where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10185 as integer),idobj from n5recepta where pWyrob=@idobj_par
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pWyrob=@idobj_par
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
go

-- table: n5pozsprzedaz
if exists (select * from sysobjects where name='n5pozsprzedaz_select')
	drop procedure n5pozsprzedaz_select
go

create procedure n5pozsprzedaz_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@pOpak_par integer output,
	@curCenaBazNetto_par decimal(14,4) output,
	@curCenaBazBrutto_par decimal(14,4) output,
	@curRabat_par decimal(12,2) output,
	@eVAT_par integer output,
	@curCenaNetto_par decimal(14,4) output,
	@curCenaBrutto_par decimal(14,4) output,
	@curWartNetto_par decimal(12,2) output,
	@curVAT_par decimal(12,2) output,
	@curCenaBazowaNettoWal_par decimal(14,4) output,
	@curCenaNettoWal_par decimal(14,4) output,
	@curWartWal_par decimal(12,2) output,
	@strUwagi_par varchar(512) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@curIloscOpak_par=curIloscOpak,
	@pOpak_par=pOpak,
	@curCenaBazNetto_par=curCenaBazNetto,
	@curCenaBazBrutto_par=curCenaBazBrutto,
	@curRabat_par=curRabat,
	@eVAT_par=eVAT,
	@curCenaNetto_par=curCenaNetto,
	@curCenaBrutto_par=curCenaBrutto,
	@curWartNetto_par=curWartNetto,
	@curVAT_par=curVAT,
	@curCenaBazowaNettoWal_par=curCenaBazowaNettoWal,
	@curCenaNettoWal_par=curCenaNettoWal,
	@curWartWal_par=curWartWal,
	@strUwagi_par=strUwagi,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5pozsprzedaz where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozsprzedaz_insert')
	drop procedure n5pozsprzedaz_insert
go

create procedure n5pozsprzedaz_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@curCenaBazNetto_par decimal(14,4),@curCenaBazBrutto_par decimal(14,4),@curRabat_par decimal(12,2),@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curCenaBazowaNettoWal_par decimal(14,4),@curCenaNettoWal_par decimal(14,4),@curWartWal_par decimal(12,2),@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozsprzedaz values(@idobj_par,@versionid_par,@pProdukt_par,@curIloscOpak_par,@pOpak_par,@curCenaBazNetto_par,@curCenaBazBrutto_par,@curRabat_par,@eVAT_par,@curCenaNetto_par,@curCenaBrutto_par,@curWartNetto_par,@curVAT_par,@curCenaBazowaNettoWal_par,@curCenaNettoWal_par,@curWartWal_par,@strUwagi_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozsprzedaz_update')
	drop procedure n5pozsprzedaz_update
go

create procedure n5pozsprzedaz_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@curCenaBazNetto_par decimal(14,4),@curCenaBazBrutto_par decimal(14,4),@curRabat_par decimal(12,2),@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curCenaBazowaNettoWal_par decimal(14,4),@curCenaNettoWal_par decimal(14,4),@curWartWal_par decimal(12,2),@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5pozsprzedaz set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	curIloscOpak=@curIloscOpak_par,
	pOpak=@pOpak_par,
	curCenaBazNetto=@curCenaBazNetto_par,
	curCenaBazBrutto=@curCenaBazBrutto_par,
	curRabat=@curRabat_par,
	eVAT=@eVAT_par,
	curCenaNetto=@curCenaNetto_par,
	curCenaBrutto=@curCenaBrutto_par,
	curWartNetto=@curWartNetto_par,
	curVAT=@curVAT_par,
	curCenaBazowaNettoWal=@curCenaBazowaNettoWal_par,
	curCenaNettoWal=@curCenaNettoWal_par,
	curWartWal=@curWartWal_par,
	strUwagi=@strUwagi_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozsprzedaz_delete')
	drop procedure n5pozsprzedaz_delete
go

create procedure n5pozsprzedaz_delete(@idobj_par integer) with encryption as 
	delete from n5pozsprzedaz where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozsprzedaz_maxid')
	drop procedure n5pozsprzedaz_maxid
go

create procedure n5pozsprzedaz_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozsprzedaz
go

if exists (select * from sysobjects where name='n5pozsprzedaz_candel')
	drop procedure n5pozsprzedaz_candel
go

create procedure n5pozsprzedaz_candel(@idobj_par integer) with encryption as 
go

-- table: n5dokumentlinks
if exists (select * from sysobjects where name='n5dokumentlinks_select')
	drop procedure n5dokumentlinks_select
go

create procedure n5dokumentlinks_select(@idobj_par integer,@versionid_par integer output,
	@pDokument_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pDokument_par=pDokument from n5dokumentlinks where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokumentlinks_insert')
	drop procedure n5dokumentlinks_insert
go

create procedure n5dokumentlinks_insert(@idobj_par integer,@versionid_par integer,@pDokument_par integer) with encryption as 
	insert into n5dokumentlinks values(@idobj_par,@versionid_par,@pDokument_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokumentlinks_update')
	drop procedure n5dokumentlinks_update
go

create procedure n5dokumentlinks_update(@idobj_par integer,@versionid_par integer,@pDokument_par integer) with encryption as 
	update n5dokumentlinks set VersionId=@versionid_par,
	pDokument=@pDokument_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokumentlinks_delete')
	drop procedure n5dokumentlinks_delete
go

create procedure n5dokumentlinks_delete(@idobj_par integer) with encryption as 
	delete from n5dokumentlinks where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokumentlinks_maxid')
	drop procedure n5dokumentlinks_maxid
go

create procedure n5dokumentlinks_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dokumentlinks
go

if exists (select * from sysobjects where name='n5dokumentlinks_candel')
	drop procedure n5dokumentlinks_candel
go

create procedure n5dokumentlinks_candel(@idobj_par integer) with encryption as 
go

-- table: n5pkpir
if exists (select * from sysobjects where name='n5pkpir_select')
	drop procedure n5pkpir_select
go

create procedure n5pkpir_select(@idobj_par integer,@versionid_par integer output,
	@nNumOper_par integer output,
	@dDataOper_par datetime output,
	@pRejestrDok_par integer output,
	@strNrDok_par varchar(32) output,
	@pKlient_par integer output,
	@strOpis_par varchar(128) output,
	@strUwagi_par varchar(512) output,
	@curWartSprzed_par decimal(12,2) output,
	@curPozPrzych_par decimal(12,2) output,
	@curZakTow_par decimal(12,2) output,
	@curKosztZak_par decimal(12,2) output,
	@curKosztRekl_par decimal(12,2) output,
	@curWynagrodz_par decimal(12,2) output,
	@curPozWyd_par decimal(12,2) output,
	@curKol16_par decimal(12,2) output) with encryption as 
	select @versionid_par=VersionId,
	@nNumOper_par=nNumOper,
	@dDataOper_par=dDataOper,
	@pRejestrDok_par=pRejestrDok,
	@strNrDok_par=strNrDok,
	@pKlient_par=pKlient,
	@strOpis_par=strOpis,
	@strUwagi_par=strUwagi,
	@curWartSprzed_par=curWartSprzed,
	@curPozPrzych_par=curPozPrzych,
	@curZakTow_par=curZakTow,
	@curKosztZak_par=curKosztZak,
	@curKosztRekl_par=curKosztRekl,
	@curWynagrodz_par=curWynagrodz,
	@curPozWyd_par=curPozWyd,
	@curKol16_par=curKol16 from n5pkpir where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pkpir_insert')
	drop procedure n5pkpir_insert
go

create procedure n5pkpir_insert(@idobj_par integer,@versionid_par integer,@nNumOper_par integer,@dDataOper_par datetime,@pRejestrDok_par integer,@strNrDok_par varchar(32),@pKlient_par integer,@strOpis_par varchar(128),@strUwagi_par varchar(512),@curWartSprzed_par decimal(12,2),@curPozPrzych_par decimal(12,2),@curZakTow_par decimal(12,2),@curKosztZak_par decimal(12,2),@curKosztRekl_par decimal(12,2),@curWynagrodz_par decimal(12,2),@curPozWyd_par decimal(12,2),@curKol16_par decimal(12,2)) with encryption as 
	insert into n5pkpir values(@idobj_par,@versionid_par,@nNumOper_par,@dDataOper_par,@pRejestrDok_par,@strNrDok_par,@pKlient_par,@strOpis_par,@strUwagi_par,@curWartSprzed_par,@curPozPrzych_par,@curZakTow_par,@curKosztZak_par,@curKosztRekl_par,@curWynagrodz_par,@curPozWyd_par,@curKol16_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pkpir_update')
	drop procedure n5pkpir_update
go

create procedure n5pkpir_update(@idobj_par integer,@versionid_par integer,@nNumOper_par integer,@dDataOper_par datetime,@pRejestrDok_par integer,@strNrDok_par varchar(32),@pKlient_par integer,@strOpis_par varchar(128),@strUwagi_par varchar(512),@curWartSprzed_par decimal(12,2),@curPozPrzych_par decimal(12,2),@curZakTow_par decimal(12,2),@curKosztZak_par decimal(12,2),@curKosztRekl_par decimal(12,2),@curWynagrodz_par decimal(12,2),@curPozWyd_par decimal(12,2),@curKol16_par decimal(12,2)) with encryption as 
	update n5pkpir set VersionId=@versionid_par,
	nNumOper=@nNumOper_par,
	dDataOper=@dDataOper_par,
	pRejestrDok=@pRejestrDok_par,
	strNrDok=@strNrDok_par,
	pKlient=@pKlient_par,
	strOpis=@strOpis_par,
	strUwagi=@strUwagi_par,
	curWartSprzed=@curWartSprzed_par,
	curPozPrzych=@curPozPrzych_par,
	curZakTow=@curZakTow_par,
	curKosztZak=@curKosztZak_par,
	curKosztRekl=@curKosztRekl_par,
	curWynagrodz=@curWynagrodz_par,
	curPozWyd=@curPozWyd_par,
	curKol16=@curKol16_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pkpir_delete')
	drop procedure n5pkpir_delete
go

create procedure n5pkpir_delete(@idobj_par integer) with encryption as 
	delete from n5pkpir where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pkpir_maxid')
	drop procedure n5pkpir_maxid
go

create procedure n5pkpir_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pkpir
go

if exists (select * from sysobjects where name='n5pkpir_candel')
	drop procedure n5pkpir_candel
go

create procedure n5pkpir_candel(@idobj_par integer) with encryption as 
go

-- table: n5typinstytucji
if exists (select * from sysobjects where name='n5typinstytucji_select')
	drop procedure n5typinstytucji_select
go

create procedure n5typinstytucji_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5typinstytucji where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typinstytucji_insert')
	drop procedure n5typinstytucji_insert
go

create procedure n5typinstytucji_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	insert into n5typinstytucji values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5typinstytucji_update')
	drop procedure n5typinstytucji_update
go

create procedure n5typinstytucji_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	update n5typinstytucji set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typinstytucji_delete')
	drop procedure n5typinstytucji_delete
go

create procedure n5typinstytucji_delete(@idobj_par integer) with encryption as 
	delete from n5typinstytucji where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typinstytucji_maxid')
	drop procedure n5typinstytucji_maxid
go

create procedure n5typinstytucji_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5typinstytucji
go

if exists (select * from sysobjects where name='n5typinstytucji_candel')
	drop procedure n5typinstytucji_candel
go

create procedure n5typinstytucji_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10105 as integer),idobj from n5instytucja where pTyp=@idobj_par
go

-- table: n5analfinans
if exists (select * from sysobjects where name='n5analfinans_select')
	drop procedure n5analfinans_select
go

create procedure n5analfinans_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5analfinans where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5analfinans_insert')
	drop procedure n5analfinans_insert
go

create procedure n5analfinans_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	insert into n5analfinans values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5analfinans_update')
	drop procedure n5analfinans_update
go

create procedure n5analfinans_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	update n5analfinans set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5analfinans_delete')
	drop procedure n5analfinans_delete
go

create procedure n5analfinans_delete(@idobj_par integer) with encryption as 
	delete from n5analfinans where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5analfinans_maxid')
	drop procedure n5analfinans_maxid
go

create procedure n5analfinans_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5analfinans
go

if exists (select * from sysobjects where name='n5analfinans_candel')
	drop procedure n5analfinans_candel
go

create procedure n5analfinans_candel(@idobj_par integer) with encryption as 
go

-- table: n5rejestrdok
if exists (select * from sysobjects where name='n5rejestrdok_select')
	drop procedure n5rejestrdok_select
go

create procedure n5rejestrdok_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@eTyp_par integer output,
	@strFormatNumeracji_par varchar(32) output,
	@strFormatNumeracji2_par varchar(32) output,
	@eAktywny_par integer output,
	@nInternalID_par integer output,
	@nLicznik_par integer output,
	@strKonfiguracja_par varchar(512) output,
	@nLicznik2_par integer output,
	@pDefSchematdekr_par integer output,
	@dDataZamk_par datetime output,
	@wrefParam1_par integer output,
	@wrefParam1_wrt_par integer output,
	@wrefParam2_par integer output,
	@wrefParam2_wrt_par integer output,
	@nParam3_par integer output,
	@pRokKsieg_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@eTyp_par=eTyp,
	@strFormatNumeracji_par=strFormatNumeracji,
	@strFormatNumeracji2_par=strFormatNumeracji2,
	@eAktywny_par=eAktywny,
	@nInternalID_par=nInternalID,
	@nLicznik_par=nLicznik,
	@strKonfiguracja_par=strKonfiguracja,
	@nLicznik2_par=nLicznik2,
	@pDefSchematdekr_par=pDefSchematdekr,
	@dDataZamk_par=dDataZamk,
	@wrefParam1_par=wrefParam1,
	@wrefParam1_wrt_par=wrefParam1_wrt,
	@wrefParam2_par=wrefParam2,
	@wrefParam2_wrt_par=wrefParam2_wrt,
	@nParam3_par=nParam3,
	@pRokKsieg_par=pRokKsieg from n5rejestrdok where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rejestrdok_insert')
	drop procedure n5rejestrdok_insert
go

create procedure n5rejestrdok_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@eTyp_par integer,@strFormatNumeracji_par varchar(32),@strFormatNumeracji2_par varchar(32),@eAktywny_par integer,@nInternalID_par integer,@nLicznik_par integer,@strKonfiguracja_par varchar(512),@nLicznik2_par integer,@pDefSchematdekr_par integer,@dDataZamk_par datetime,@wrefParam1_par integer,@wrefParam1_wrt_par integer,@wrefParam2_par integer,@wrefParam2_wrt_par integer,@nParam3_par integer,@pRokKsieg_par integer) with encryption as 
	insert into n5rejestrdok values(@idobj_par,@versionid_par,@strNazwa_par,@eTyp_par,@strFormatNumeracji_par,@strFormatNumeracji2_par,@eAktywny_par,@nInternalID_par,@nLicznik_par,@strKonfiguracja_par,@nLicznik2_par,@pDefSchematdekr_par,@dDataZamk_par,@wrefParam1_par,@wrefParam1_wrt_par,@wrefParam2_par,@wrefParam2_wrt_par,@nParam3_par,@pRokKsieg_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5rejestrdok_update')
	drop procedure n5rejestrdok_update
go

create procedure n5rejestrdok_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@eTyp_par integer,@strFormatNumeracji_par varchar(32),@strFormatNumeracji2_par varchar(32),@eAktywny_par integer,@nInternalID_par integer,@nLicznik_par integer,@strKonfiguracja_par varchar(512),@nLicznik2_par integer,@pDefSchematdekr_par integer,@dDataZamk_par datetime,@wrefParam1_par integer,@wrefParam1_wrt_par integer,@wrefParam2_par integer,@wrefParam2_wrt_par integer,@nParam3_par integer,@pRokKsieg_par integer) with encryption as 
	update n5rejestrdok set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	eTyp=@eTyp_par,
	strFormatNumeracji=@strFormatNumeracji_par,
	strFormatNumeracji2=@strFormatNumeracji2_par,
	eAktywny=@eAktywny_par,
	nInternalID=@nInternalID_par,
	nLicznik=@nLicznik_par,
	strKonfiguracja=@strKonfiguracja_par,
	nLicznik2=@nLicznik2_par,
	pDefSchematdekr=@pDefSchematdekr_par,
	dDataZamk=@dDataZamk_par,
	wrefParam1=@wrefParam1_par,
	wrefParam1_wrt=@wrefParam1_wrt_par,
	wrefParam2=@wrefParam2_par,
	wrefParam2_wrt=@wrefParam2_wrt_par,
	nParam3=@nParam3_par,
	pRokKsieg=@pRokKsieg_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rejestrdok_delete')
	drop procedure n5rejestrdok_delete
go

create procedure n5rejestrdok_delete(@idobj_par integer) with encryption as 
	delete from n5rejestrdok where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rejestrdok_maxid')
	drop procedure n5rejestrdok_maxid
go

create procedure n5rejestrdok_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5rejestrdok
go

if exists (select * from sysobjects where name='n5rejestrdok_candel')
	drop procedure n5rejestrdok_candel
go

create procedure n5rejestrdok_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10134 as integer),idobj from n5pkpir where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where wrefParam2=@idobj_par and wrefParam2_wrt=10145
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10155 as integer),idobj from n5schematdekr where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10155 as integer),idobj from n5schematdekr where pDziennik=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pRejestrDok=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pRejestrDok=@idobj_par
go

-- table: n5konto
if exists (select * from sysobjects where name='n5konto_select')
	drop procedure n5konto_select
go

create procedure n5konto_select(@idobj_par integer,@versionid_par integer output,
	@strSymbol_par varchar(64) output,
	@strNazwa_par varchar(128) output,
	@strOpis_par varchar(1024) output,
	@pJednostka_par integer output,
	@wrefPodmiotRozrach_par integer output,
	@wrefPodmiotRozrach_wrt_par integer output,
	@pKontoNadrz_par integer output,
	@eAnalit_par integer output,
	@eBilans_par integer output,
	@eAktywne_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strSymbol_par=strSymbol,
	@strNazwa_par=strNazwa,
	@strOpis_par=strOpis,
	@pJednostka_par=pJednostka,
	@wrefPodmiotRozrach_par=wrefPodmiotRozrach,
	@wrefPodmiotRozrach_wrt_par=wrefPodmiotRozrach_wrt,
	@pKontoNadrz_par=pKontoNadrz,
	@eAnalit_par=eAnalit,
	@eBilans_par=eBilans,
	@eAktywne_par=eAktywne from n5konto where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_insert')
	drop procedure n5konto_insert
go

create procedure n5konto_insert(@idobj_par integer,@versionid_par integer,@strSymbol_par varchar(64),@strNazwa_par varchar(128),@strOpis_par varchar(1024),@pJednostka_par integer,@wrefPodmiotRozrach_par integer,@wrefPodmiotRozrach_wrt_par integer,@pKontoNadrz_par integer,@eAnalit_par integer,@eBilans_par integer,@eAktywne_par integer) with encryption as 
	insert into n5konto values(@idobj_par,@versionid_par,@strSymbol_par,@strNazwa_par,@strOpis_par,@pJednostka_par,@wrefPodmiotRozrach_par,@wrefPodmiotRozrach_wrt_par,@pKontoNadrz_par,@eAnalit_par,@eBilans_par,@eAktywne_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_update')
	drop procedure n5konto_update
go

create procedure n5konto_update(@idobj_par integer,@versionid_par integer,@strSymbol_par varchar(64),@strNazwa_par varchar(128),@strOpis_par varchar(1024),@pJednostka_par integer,@wrefPodmiotRozrach_par integer,@wrefPodmiotRozrach_wrt_par integer,@pKontoNadrz_par integer,@eAnalit_par integer,@eBilans_par integer,@eAktywne_par integer) with encryption as 
	update n5konto set VersionId=@versionid_par,
	strSymbol=@strSymbol_par,
	strNazwa=@strNazwa_par,
	strOpis=@strOpis_par,
	pJednostka=@pJednostka_par,
	wrefPodmiotRozrach=@wrefPodmiotRozrach_par,
	wrefPodmiotRozrach_wrt=@wrefPodmiotRozrach_wrt_par,
	pKontoNadrz=@pKontoNadrz_par,
	eAnalit=@eAnalit_par,
	eBilans=@eBilans_par,
	eAktywne=@eAktywne_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_delete')
	drop procedure n5konto_delete
go

create procedure n5konto_delete(@idobj_par integer) with encryption as 
	delete from n5konto where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_maxid')
	drop procedure n5konto_maxid
go

create procedure n5konto_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5konto
go

if exists (select * from sysobjects where name='n5konto_candel')
	drop procedure n5konto_candel
go

create procedure n5konto_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where pKontoNadrz=@idobj_par
union
select TOP 5 'typeid'=cast(10147 as integer),idobj from n5dekret where pKonto=@idobj_par
union
select TOP 5 'typeid'=cast(10209 as integer),idobj from n5konto_budzet where pKonto=@idobj_par
go

-- table: n5dekret
if exists (select * from sysobjects where name='n5dekret_select')
	drop procedure n5dekret_select
go

create procedure n5dekret_select(@idobj_par integer,@versionid_par integer output,
	@pKonto_par integer output,
	@curWn_par decimal(12,2) output,
	@curMa_par decimal(12,2) output,
	@dDataKsieg_par datetime output,
	@strOpis_par varchar(128) output,
	@eTyp_par integer output,
	@eStatus_par integer output,
	@pTransakcja_par integer output,
	@pKwalifikator_par integer output,
	@cAuto_par varchar(1) output) with encryption as 
	select @versionid_par=VersionId,
	@pKonto_par=pKonto,
	@curWn_par=curWn,
	@curMa_par=curMa,
	@dDataKsieg_par=dDataKsieg,
	@strOpis_par=strOpis,
	@eTyp_par=eTyp,
	@eStatus_par=eStatus,
	@pTransakcja_par=pTransakcja,
	@pKwalifikator_par=pKwalifikator,
	@cAuto_par=cAuto from n5dekret where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dekret_insert')
	drop procedure n5dekret_insert
go

create procedure n5dekret_insert(@idobj_par integer,@versionid_par integer,@pKonto_par integer,@curWn_par decimal(12,2),@curMa_par decimal(12,2),@dDataKsieg_par datetime,@strOpis_par varchar(128),@eTyp_par integer,@eStatus_par integer,@pTransakcja_par integer,@pKwalifikator_par integer,@cAuto_par varchar(1)) with encryption as 
	insert into n5dekret values(@idobj_par,@versionid_par,@pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@strOpis_par,@eTyp_par,@eStatus_par,@pTransakcja_par,@pKwalifikator_par,@cAuto_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dekret_update')
	drop procedure n5dekret_update
go

create procedure n5dekret_update(@idobj_par integer,@versionid_par integer,@pKonto_par integer,@curWn_par decimal(12,2),@curMa_par decimal(12,2),@dDataKsieg_par datetime,@strOpis_par varchar(128),@eTyp_par integer,@eStatus_par integer,@pTransakcja_par integer,@pKwalifikator_par integer,@cAuto_par varchar(1)) with encryption as 
	update n5dekret set VersionId=@versionid_par,
	pKonto=@pKonto_par,
	curWn=@curWn_par,
	curMa=@curMa_par,
	dDataKsieg=@dDataKsieg_par,
	strOpis=@strOpis_par,
	eTyp=@eTyp_par,
	eStatus=@eStatus_par,
	pTransakcja=@pTransakcja_par,
	pKwalifikator=@pKwalifikator_par,
	cAuto=@cAuto_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dekret_delete')
	drop procedure n5dekret_delete
go

create procedure n5dekret_delete(@idobj_par integer) with encryption as 
	delete from n5dekret where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dekret_maxid')
	drop procedure n5dekret_maxid
go

create procedure n5dekret_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dekret
go

if exists (select * from sysobjects where name='n5dekret_candel')
	drop procedure n5dekret_candel
go

create procedure n5dekret_candel(@idobj_par integer) with encryption as 
go

-- table: n5dowodksieg
if exists (select * from sysobjects where name='n5dowodksieg_select')
	drop procedure n5dowodksieg_select
go

create procedure n5dowodksieg_select(@idobj_par integer,@versionid_par integer output,
	@dDataRej_par datetime output,
	@dDataKsieg_par datetime output,
	@strNrDok_par varchar(32) output,
	@nNumDow_par integer output,
	@strOpis_par varchar(512) output,
	@eTyp_par integer output,
	@eStatus_par integer output,
	@pUzytRej_par integer output,
	@pRejestrDok_par integer output,
	@wrefDokZrod_par integer output,
	@wrefDokZrod_wrt_par integer output,
	@cAuto_par varchar(1) output) with encryption as 
	select @versionid_par=VersionId,
	@dDataRej_par=dDataRej,
	@dDataKsieg_par=dDataKsieg,
	@strNrDok_par=strNrDok,
	@nNumDow_par=nNumDow,
	@strOpis_par=strOpis,
	@eTyp_par=eTyp,
	@eStatus_par=eStatus,
	@pUzytRej_par=pUzytRej,
	@pRejestrDok_par=pRejestrDok,
	@wrefDokZrod_par=wrefDokZrod,
	@wrefDokZrod_wrt_par=wrefDokZrod_wrt,
	@cAuto_par=cAuto from n5dowodksieg where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dowodksieg_insert')
	drop procedure n5dowodksieg_insert
go

create procedure n5dowodksieg_insert(@idobj_par integer,@versionid_par integer,@dDataRej_par datetime,@dDataKsieg_par datetime,@strNrDok_par varchar(32),@nNumDow_par integer,@strOpis_par varchar(512),@eTyp_par integer,@eStatus_par integer,@pUzytRej_par integer,@pRejestrDok_par integer,@wrefDokZrod_par integer,@wrefDokZrod_wrt_par integer,@cAuto_par varchar(1)) with encryption as 
	insert into n5dowodksieg values(@idobj_par,@versionid_par,@dDataRej_par,@dDataKsieg_par,@strNrDok_par,@nNumDow_par,@strOpis_par,@eTyp_par,@eStatus_par,@pUzytRej_par,@pRejestrDok_par,@wrefDokZrod_par,@wrefDokZrod_wrt_par,@cAuto_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dowodksieg_update')
	drop procedure n5dowodksieg_update
go

create procedure n5dowodksieg_update(@idobj_par integer,@versionid_par integer,@dDataRej_par datetime,@dDataKsieg_par datetime,@strNrDok_par varchar(32),@nNumDow_par integer,@strOpis_par varchar(512),@eTyp_par integer,@eStatus_par integer,@pUzytRej_par integer,@pRejestrDok_par integer,@wrefDokZrod_par integer,@wrefDokZrod_wrt_par integer,@cAuto_par varchar(1)) with encryption as 
	update n5dowodksieg set VersionId=@versionid_par,
	dDataRej=@dDataRej_par,
	dDataKsieg=@dDataKsieg_par,
	strNrDok=@strNrDok_par,
	nNumDow=@nNumDow_par,
	strOpis=@strOpis_par,
	eTyp=@eTyp_par,
	eStatus=@eStatus_par,
	pUzytRej=@pUzytRej_par,
	pRejestrDok=@pRejestrDok_par,
	wrefDokZrod=@wrefDokZrod_par,
	wrefDokZrod_wrt=@wrefDokZrod_wrt_par,
	cAuto=@cAuto_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dowodksieg_delete')
	drop procedure n5dowodksieg_delete
go

create procedure n5dowodksieg_delete(@idobj_par integer) with encryption as 
	delete from n5dowodksieg where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dowodksieg_maxid')
	drop procedure n5dowodksieg_maxid
go

create procedure n5dowodksieg_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dowodksieg
go

if exists (select * from sysobjects where name='n5dowodksieg_candel')
	drop procedure n5dowodksieg_candel
go

create procedure n5dowodksieg_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10148
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pDowodKsieg=@idobj_par
go

-- table: n5platnosc
if exists (select * from sysobjects where name='n5platnosc_select')
	drop procedure n5platnosc_select
go

create procedure n5platnosc_select(@idobj_par integer,@versionid_par integer output,
	@dDataOper_par datetime output,
	@wrefPodmiot_par integer output,
	@wrefPodmiot_wrt_par integer output,
	@strOpis_par varchar(128) output,
	@pZadanie_par integer output,
	@pUzytRej_par integer output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@strNrDok_par varchar(32) output,
	@nNumOper_par integer output,
	@curKwotaPodm_par decimal(12,2) output,
	@curKursPodm_par decimal(14,4) output,
	@pWalutaPodm_par integer output,
	@curKwotaStan_par decimal(12,2) output,
	@curKursEwid_par decimal(14,4) output,
	@curKwotaEwid_par decimal(12,2) output,
	@eStatus_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@dDataOper_par=dDataOper,
	@wrefPodmiot_par=wrefPodmiot,
	@wrefPodmiot_wrt_par=wrefPodmiot_wrt,
	@strOpis_par=strOpis,
	@pZadanie_par=pZadanie,
	@pUzytRej_par=pUzytRej,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@strNrDok_par=strNrDok,
	@nNumOper_par=nNumOper,
	@curKwotaPodm_par=curKwotaPodm,
	@curKursPodm_par=curKursPodm,
	@pWalutaPodm_par=pWalutaPodm,
	@curKwotaStan_par=curKwotaStan,
	@curKursEwid_par=curKursEwid,
	@curKwotaEwid_par=curKwotaEwid,
	@eStatus_par=eStatus from n5platnosc where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5platnosc_insert')
	drop procedure n5platnosc_insert
go

create procedure n5platnosc_insert(@idobj_par integer,@versionid_par integer,@dDataOper_par datetime,@wrefPodmiot_par integer,@wrefPodmiot_wrt_par integer,@strOpis_par varchar(128),@pZadanie_par integer,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strNrDok_par varchar(32),@nNumOper_par integer,@curKwotaPodm_par decimal(12,2),@curKursPodm_par decimal(14,4),@pWalutaPodm_par integer,@curKwotaStan_par decimal(12,2),@curKursEwid_par decimal(14,4),@curKwotaEwid_par decimal(12,2),@eStatus_par integer) with encryption as 
	insert into n5platnosc values(@idobj_par,@versionid_par,@dDataOper_par,@wrefPodmiot_par,@wrefPodmiot_wrt_par,@strOpis_par,@pZadanie_par,@pUzytRej_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@strNrDok_par,@nNumOper_par,@curKwotaPodm_par,@curKursPodm_par,@pWalutaPodm_par,@curKwotaStan_par,@curKursEwid_par,@curKwotaEwid_par,@eStatus_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5platnosc_update')
	drop procedure n5platnosc_update
go

create procedure n5platnosc_update(@idobj_par integer,@versionid_par integer,@dDataOper_par datetime,@wrefPodmiot_par integer,@wrefPodmiot_wrt_par integer,@strOpis_par varchar(128),@pZadanie_par integer,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strNrDok_par varchar(32),@nNumOper_par integer,@curKwotaPodm_par decimal(12,2),@curKursPodm_par decimal(14,4),@pWalutaPodm_par integer,@curKwotaStan_par decimal(12,2),@curKursEwid_par decimal(14,4),@curKwotaEwid_par decimal(12,2),@eStatus_par integer) with encryption as 
	update n5platnosc set VersionId=@versionid_par,
	dDataOper=@dDataOper_par,
	wrefPodmiot=@wrefPodmiot_par,
	wrefPodmiot_wrt=@wrefPodmiot_wrt_par,
	strOpis=@strOpis_par,
	pZadanie=@pZadanie_par,
	pUzytRej=@pUzytRej_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	strNrDok=@strNrDok_par,
	nNumOper=@nNumOper_par,
	curKwotaPodm=@curKwotaPodm_par,
	curKursPodm=@curKursPodm_par,
	pWalutaPodm=@pWalutaPodm_par,
	curKwotaStan=@curKwotaStan_par,
	curKursEwid=@curKursEwid_par,
	curKwotaEwid=@curKwotaEwid_par,
	eStatus=@eStatus_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5platnosc_delete')
	drop procedure n5platnosc_delete
go

create procedure n5platnosc_delete(@idobj_par integer) with encryption as 
	delete from n5platnosc where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5platnosc_maxid')
	drop procedure n5platnosc_maxid
go

create procedure n5platnosc_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5platnosc
go

if exists (select * from sysobjects where name='n5platnosc_candel')
	drop procedure n5platnosc_candel
go

create procedure n5platnosc_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10150
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10150
go

-- table: n5typdzialania
if exists (select * from sysobjects where name='n5typdzialania_select')
	drop procedure n5typdzialania_select
go

create procedure n5typdzialania_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@nInternalID_par integer output,
	@pTypNadrzedny_par integer output,
	@strOpis_par varchar(255) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@nInternalID_par=nInternalID,
	@pTypNadrzedny_par=pTypNadrzedny,
	@strOpis_par=strOpis from n5typdzialania where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdzialania_insert')
	drop procedure n5typdzialania_insert
go

create procedure n5typdzialania_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@nInternalID_par integer,@pTypNadrzedny_par integer,@strOpis_par varchar(255)) with encryption as 
	insert into n5typdzialania values(@idobj_par,@versionid_par,@strNazwa_par,@nInternalID_par,@pTypNadrzedny_par,@strOpis_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdzialania_update')
	drop procedure n5typdzialania_update
go

create procedure n5typdzialania_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@nInternalID_par integer,@pTypNadrzedny_par integer,@strOpis_par varchar(255)) with encryption as 
	update n5typdzialania set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	nInternalID=@nInternalID_par,
	pTypNadrzedny=@pTypNadrzedny_par,
	strOpis=@strOpis_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdzialania_delete')
	drop procedure n5typdzialania_delete
go

create procedure n5typdzialania_delete(@idobj_par integer) with encryption as 
	delete from n5typdzialania where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5typdzialania_maxid')
	drop procedure n5typdzialania_maxid
go

create procedure n5typdzialania_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5typdzialania
go

if exists (select * from sysobjects where name='n5typdzialania_candel')
	drop procedure n5typdzialania_candel
go

create procedure n5typdzialania_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pTypDzialania=@idobj_par
union
select TOP 5 'typeid'=cast(10153 as integer),idobj from n5typdzialania where pTypNadrzedny=@idobj_par
go

-- table: n5transakcja
if exists (select * from sysobjects where name='n5transakcja_select')
	drop procedure n5transakcja_select
go

create procedure n5transakcja_select(@idobj_par integer,@versionid_par integer output,
	@strSymTrans_par varchar(32) output,
	@pWaluta_par integer output,
	@wrefPodmiot_par integer output,
	@wrefPodmiot_wrt_par integer output,
	@dDataRozp_par datetime output,
	@dDataWym_par datetime output,
	@dDataZamk_par datetime output,
	@curWn_par decimal(12,2) output,
	@curMa_par decimal(12,2) output,
	@eTyp_par integer output,
	@eStatus_par integer output,
	@curWnEwid_par decimal(12,2) output,
	@curMaEwid_par decimal(12,2) output,
	@eTypOdset_par integer output,
	@curOdsetkiUmowne_par decimal(12,2) output,
	@pNotaOds_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strSymTrans_par=strSymTrans,
	@pWaluta_par=pWaluta,
	@wrefPodmiot_par=wrefPodmiot,
	@wrefPodmiot_wrt_par=wrefPodmiot_wrt,
	@dDataRozp_par=dDataRozp,
	@dDataWym_par=dDataWym,
	@dDataZamk_par=dDataZamk,
	@curWn_par=curWn,
	@curMa_par=curMa,
	@eTyp_par=eTyp,
	@eStatus_par=eStatus,
	@curWnEwid_par=curWnEwid,
	@curMaEwid_par=curMaEwid,
	@eTypOdset_par=eTypOdset,
	@curOdsetkiUmowne_par=curOdsetkiUmowne,
	@pNotaOds_par=pNotaOds from n5transakcja where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5transakcja_insert')
	drop procedure n5transakcja_insert
go

create procedure n5transakcja_insert(@idobj_par integer,@versionid_par integer,@strSymTrans_par varchar(32),@pWaluta_par integer,@wrefPodmiot_par integer,@wrefPodmiot_wrt_par integer,@dDataRozp_par datetime,@dDataWym_par datetime,@dDataZamk_par datetime,@curWn_par decimal(12,2),@curMa_par decimal(12,2),@eTyp_par integer,@eStatus_par integer,@curWnEwid_par decimal(12,2),@curMaEwid_par decimal(12,2),@eTypOdset_par integer,@curOdsetkiUmowne_par decimal(12,2),@pNotaOds_par integer) with encryption as 
	insert into n5transakcja values(@idobj_par,@versionid_par,@strSymTrans_par,@pWaluta_par,@wrefPodmiot_par,@wrefPodmiot_wrt_par,@dDataRozp_par,@dDataWym_par,@dDataZamk_par,@curWn_par,@curMa_par,@eTyp_par,@eStatus_par,@curWnEwid_par,@curMaEwid_par,@eTypOdset_par,@curOdsetkiUmowne_par,@pNotaOds_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5transakcja_update')
	drop procedure n5transakcja_update
go

create procedure n5transakcja_update(@idobj_par integer,@versionid_par integer,@strSymTrans_par varchar(32),@pWaluta_par integer,@wrefPodmiot_par integer,@wrefPodmiot_wrt_par integer,@dDataRozp_par datetime,@dDataWym_par datetime,@dDataZamk_par datetime,@curWn_par decimal(12,2),@curMa_par decimal(12,2),@eTyp_par integer,@eStatus_par integer,@curWnEwid_par decimal(12,2),@curMaEwid_par decimal(12,2),@eTypOdset_par integer,@curOdsetkiUmowne_par decimal(12,2),@pNotaOds_par integer) with encryption as 
	update n5transakcja set VersionId=@versionid_par,
	strSymTrans=@strSymTrans_par,
	pWaluta=@pWaluta_par,
	wrefPodmiot=@wrefPodmiot_par,
	wrefPodmiot_wrt=@wrefPodmiot_wrt_par,
	dDataRozp=@dDataRozp_par,
	dDataWym=@dDataWym_par,
	dDataZamk=@dDataZamk_par,
	curWn=@curWn_par,
	curMa=@curMa_par,
	eTyp=@eTyp_par,
	eStatus=@eStatus_par,
	curWnEwid=@curWnEwid_par,
	curMaEwid=@curMaEwid_par,
	eTypOdset=@eTypOdset_par,
	curOdsetkiUmowne=@curOdsetkiUmowne_par,
	pNotaOds=@pNotaOds_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5transakcja_delete')
	drop procedure n5transakcja_delete
go

create procedure n5transakcja_delete(@idobj_par integer) with encryption as 
	delete from n5transakcja where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5transakcja_maxid')
	drop procedure n5transakcja_maxid
go

create procedure n5transakcja_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5transakcja
go

if exists (select * from sysobjects where name='n5transakcja_candel')
	drop procedure n5transakcja_candel
go

create procedure n5transakcja_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10121 as integer),idobj from n5pozplatnosc where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10147 as integer),idobj from n5dekret where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10214 as integer),idobj from n5poznotaods where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pTransakcja=@idobj_par
go

-- table: n5schematdekr
if exists (select * from sysobjects where name='n5schematdekr_select')
	drop procedure n5schematdekr_select
go

create procedure n5schematdekr_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pRejestrDok_par integer output,
	@pDziennik_par integer output,
	@strOpis_par varchar(255) output,
	@strVBcode_par varchar(7900) output,
	@eAktywny_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pRejestrDok_par=pRejestrDok,
	@pDziennik_par=pDziennik,
	@strOpis_par=strOpis,
	@strVBcode_par=strVBcode,
	@eAktywny_par=eAktywny from n5schematdekr where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5schematdekr_insert')
	drop procedure n5schematdekr_insert
go

create procedure n5schematdekr_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pRejestrDok_par integer,@pDziennik_par integer,@strOpis_par varchar(255),@strVBcode_par varchar(7900),@eAktywny_par integer) with encryption as 
	insert into n5schematdekr values(@idobj_par,@versionid_par,@strNazwa_par,@pRejestrDok_par,@pDziennik_par,@strOpis_par,@strVBcode_par,@eAktywny_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5schematdekr_update')
	drop procedure n5schematdekr_update
go

create procedure n5schematdekr_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pRejestrDok_par integer,@pDziennik_par integer,@strOpis_par varchar(255),@strVBcode_par varchar(7900),@eAktywny_par integer) with encryption as 
	update n5schematdekr set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pRejestrDok=@pRejestrDok_par,
	pDziennik=@pDziennik_par,
	strOpis=@strOpis_par,
	strVBcode=@strVBcode_par,
	eAktywny=@eAktywny_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5schematdekr_delete')
	drop procedure n5schematdekr_delete
go

create procedure n5schematdekr_delete(@idobj_par integer) with encryption as 
	delete from n5schematdekr where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5schematdekr_maxid')
	drop procedure n5schematdekr_maxid
go

create procedure n5schematdekr_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5schematdekr
go

if exists (select * from sysobjects where name='n5schematdekr_candel')
	drop procedure n5schematdekr_candel
go

create procedure n5schematdekr_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pSchematDekretacji=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where pDefSchematdekr=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pSchematDekr=@idobj_par
go

-- table: n5branza
if exists (select * from sysobjects where name='n5branza_select')
	drop procedure n5branza_select
go

create procedure n5branza_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@pBranzaNad_par integer output,
	@strKOD_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pBranzaNad_par=pBranzaNad,
	@strKOD_par=strKOD from n5branza where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5branza_insert')
	drop procedure n5branza_insert
go

create procedure n5branza_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@pBranzaNad_par integer,@strKOD_par varchar(32)) with encryption as 
	insert into n5branza values(@idobj_par,@versionid_par,@strNazwa_par,@pBranzaNad_par,@strKOD_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5branza_update')
	drop procedure n5branza_update
go

create procedure n5branza_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@pBranzaNad_par integer,@strKOD_par varchar(32)) with encryption as 
	update n5branza set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pBranzaNad=@pBranzaNad_par,
	strKOD=@strKOD_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5branza_delete')
	drop procedure n5branza_delete
go

create procedure n5branza_delete(@idobj_par integer) with encryption as 
	delete from n5branza where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5branza_maxid')
	drop procedure n5branza_maxid
go

create procedure n5branza_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5branza
go

if exists (select * from sysobjects where name='n5branza_candel')
	drop procedure n5branza_candel
go

create procedure n5branza_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pBranza=@idobj_par
union
select TOP 5 'typeid'=cast(10157 as integer),idobj from n5branza where pBranzaNad=@idobj_par
go

-- table: n5magazyn
if exists (select * from sysobjects where name='n5magazyn_select')
	drop procedure n5magazyn_select
go

create procedure n5magazyn_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pWaluta_par integer output,
	@eTyp_par integer output,
	@pJednostkaOrg_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pWaluta_par=pWaluta,
	@eTyp_par=eTyp,
	@pJednostkaOrg_par=pJednostkaOrg from n5magazyn where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5magazyn_insert')
	drop procedure n5magazyn_insert
go

create procedure n5magazyn_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pWaluta_par integer,@eTyp_par integer,@pJednostkaOrg_par integer) with encryption as 
	insert into n5magazyn values(@idobj_par,@versionid_par,@strNazwa_par,@pWaluta_par,@eTyp_par,@pJednostkaOrg_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5magazyn_update')
	drop procedure n5magazyn_update
go

create procedure n5magazyn_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pWaluta_par integer,@eTyp_par integer,@pJednostkaOrg_par integer) with encryption as 
	update n5magazyn set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pWaluta=@pWaluta_par,
	eTyp=@eTyp_par,
	pJednostkaOrg=@pJednostkaOrg_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5magazyn_delete')
	drop procedure n5magazyn_delete
go

create procedure n5magazyn_delete(@idobj_par integer) with encryption as 
	delete from n5magazyn where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5magazyn_maxid')
	drop procedure n5magazyn_maxid
go

create procedure n5magazyn_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5magazyn
go

if exists (select * from sysobjects where name='n5magazyn_candel')
	drop procedure n5magazyn_candel
go

create procedure n5magazyn_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where wrefParam1=@idobj_par and wrefParam1_wrt=10160
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where wrefParam2=@idobj_par and wrefParam2_wrt=10160
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pMagZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pMagDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pMagZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pMagDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pMagZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10180 as integer),idobj from n5opmag where pMagDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pMagZrod=@idobj_par
union
select TOP 5 'typeid'=cast(10181 as integer),idobj from n5koropmag where pMagDocel=@idobj_par
union
select TOP 5 'typeid'=cast(10182 as integer),idobj from n5stanmag where pMagazyn=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pMagazyn=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pMagazyn=@idobj_par
go

-- table: n5pozdokmag
if exists (select * from sysobjects where name='n5pozdokmag_select')
	drop procedure n5pozdokmag_select
go

create procedure n5pozdokmag_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@pOpak_par integer output,
	@nTypDok_par integer output,
	@pMagZrod_par integer output,
	@pMagDocel_par integer output,
	@pJednOpak_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@pJednEwid_par integer output,
	@curIloscEwid_par decimal(14,4) output,
	@curCenaMag_par decimal(14,4) output,
	@curCenaEwid_par decimal(14,4) output,
	@curWartMag_par decimal(12,2) output,
	@curWartEwid_par decimal(12,2) output,
	@nNumOpMagDost_par integer output,
	@nLpDost_par integer output,
	@strUwagi_par varchar(512) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@dDataWazn_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@pOpak_par=pOpak,
	@nTypDok_par=nTypDok,
	@pMagZrod_par=pMagZrod,
	@pMagDocel_par=pMagDocel,
	@pJednOpak_par=pJednOpak,
	@curIloscOpak_par=curIloscOpak,
	@pJednEwid_par=pJednEwid,
	@curIloscEwid_par=curIloscEwid,
	@curCenaMag_par=curCenaMag,
	@curCenaEwid_par=curCenaEwid,
	@curWartMag_par=curWartMag,
	@curWartEwid_par=curWartEwid,
	@nNumOpMagDost_par=nNumOpMagDost,
	@nLpDost_par=nLpDost,
	@strUwagi_par=strUwagi,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@dDataWazn_par=dDataWazn from n5pozdokmag where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozdokmag_insert')
	drop procedure n5pozdokmag_insert
go

create procedure n5pozdokmag_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@nTypDok_par integer,@pMagZrod_par integer,@pMagDocel_par integer,@pJednOpak_par integer,@curIloscOpak_par decimal(14,4),@pJednEwid_par integer,@curIloscEwid_par decimal(14,4),@curCenaMag_par decimal(14,4),@curCenaEwid_par decimal(14,4),@curWartMag_par decimal(12,2),@curWartEwid_par decimal(12,2),@nNumOpMagDost_par integer,@nLpDost_par integer,@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@dDataWazn_par datetime) with encryption as 
	insert into n5pozdokmag values(@idobj_par,@versionid_par,@pProdukt_par,@pOpak_par,@nTypDok_par,@pMagZrod_par,@pMagDocel_par,@pJednOpak_par,@curIloscOpak_par,@pJednEwid_par,@curIloscEwid_par,@curCenaMag_par,@curCenaEwid_par,@curWartMag_par,@curWartEwid_par,@nNumOpMagDost_par,@nLpDost_par,@strUwagi_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par,@dDataWazn_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozdokmag_update')
	drop procedure n5pozdokmag_update
go

create procedure n5pozdokmag_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@nTypDok_par integer,@pMagZrod_par integer,@pMagDocel_par integer,@pJednOpak_par integer,@curIloscOpak_par decimal(14,4),@pJednEwid_par integer,@curIloscEwid_par decimal(14,4),@curCenaMag_par decimal(14,4),@curCenaEwid_par decimal(14,4),@curWartMag_par decimal(12,2),@curWartEwid_par decimal(12,2),@nNumOpMagDost_par integer,@nLpDost_par integer,@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@dDataWazn_par datetime) with encryption as 
	update n5pozdokmag set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	pOpak=@pOpak_par,
	nTypDok=@nTypDok_par,
	pMagZrod=@pMagZrod_par,
	pMagDocel=@pMagDocel_par,
	pJednOpak=@pJednOpak_par,
	curIloscOpak=@curIloscOpak_par,
	pJednEwid=@pJednEwid_par,
	curIloscEwid=@curIloscEwid_par,
	curCenaMag=@curCenaMag_par,
	curCenaEwid=@curCenaEwid_par,
	curWartMag=@curWartMag_par,
	curWartEwid=@curWartEwid_par,
	nNumOpMagDost=@nNumOpMagDost_par,
	nLpDost=@nLpDost_par,
	strUwagi=@strUwagi_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	dDataWazn=@dDataWazn_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozdokmag_delete')
	drop procedure n5pozdokmag_delete
go

create procedure n5pozdokmag_delete(@idobj_par integer) with encryption as 
	delete from n5pozdokmag where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozdokmag_maxid')
	drop procedure n5pozdokmag_maxid
go

create procedure n5pozdokmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozdokmag
go

if exists (select * from sysobjects where name='n5pozdokmag_candel')
	drop procedure n5pozdokmag_candel
go

create procedure n5pozdokmag_candel(@idobj_par integer) with encryption as 
go

-- table: n5dokmag
if exists (select * from sysobjects where name='n5dokmag_select')
	drop procedure n5dokmag_select
go

create procedure n5dokmag_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@pKlient_par integer output,
	@pKlient_JO_par integer output,
	@pKlientPracownik_par integer output,
	@pDokMag_par integer output,
	@nNumOper_par integer output,
	@nTypDok_par integer output,
	@dDataWyst_par datetime output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@curSumaMag_par decimal(12,2) output,
	@curSumaEwid_par decimal(12,2) output,
	@pMagZrod_par integer output,
	@pMagDocel_par integer output,
	@cAutoCalc_par varchar(1) output,
	@wrefDokHandl_par integer output,
	@wrefDokHandl_wrt_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@dDataRezerw_par datetime output,
	@tCzasRezerw_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@pKlient_par=pKlient,
	@pKlient_JO_par=pKlient_JO,
	@pKlientPracownik_par=pKlientPracownik,
	@pDokMag_par=pDokMag,
	@nNumOper_par=nNumOper,
	@nTypDok_par=nTypDok,
	@dDataWyst_par=dDataWyst,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@curSumaMag_par=curSumaMag,
	@curSumaEwid_par=curSumaEwid,
	@pMagZrod_par=pMagZrod,
	@pMagDocel_par=pMagDocel,
	@cAutoCalc_par=cAutoCalc,
	@wrefDokHandl_par=wrefDokHandl,
	@wrefDokHandl_wrt_par=wrefDokHandl_wrt,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@dDataRezerw_par=dDataRezerw,
	@tCzasRezerw_par=tCzasRezerw from n5dokmag where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokmag_insert')
	drop procedure n5dokmag_insert
go

create procedure n5dokmag_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pDokMag_par integer,@nNumOper_par integer,@nTypDok_par integer,@dDataWyst_par datetime,@pUzytRej_par integer,@strUwagi_par varchar(512),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaMag_par decimal(12,2),@curSumaEwid_par decimal(12,2),@pMagZrod_par integer,@pMagDocel_par integer,@cAutoCalc_par varchar(1),@wrefDokHandl_par integer,@wrefDokHandl_wrt_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@dDataRezerw_par datetime,@tCzasRezerw_par integer) with encryption as 
	insert into n5dokmag values(@idobj_par,@versionid_par,@strNrDok_par,@pKlient_par,@pKlient_JO_par,@pKlientPracownik_par,@pDokMag_par,@nNumOper_par,@nTypDok_par,@dDataWyst_par,@pUzytRej_par,@strUwagi_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@curSumaMag_par,@curSumaEwid_par,@pMagZrod_par,@pMagDocel_par,@cAutoCalc_par,@wrefDokHandl_par,@wrefDokHandl_wrt_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par,@dDataRezerw_par,@tCzasRezerw_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokmag_update')
	drop procedure n5dokmag_update
go

create procedure n5dokmag_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pDokMag_par integer,@nNumOper_par integer,@nTypDok_par integer,@dDataWyst_par datetime,@pUzytRej_par integer,@strUwagi_par varchar(512),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaMag_par decimal(12,2),@curSumaEwid_par decimal(12,2),@pMagZrod_par integer,@pMagDocel_par integer,@cAutoCalc_par varchar(1),@wrefDokHandl_par integer,@wrefDokHandl_wrt_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@dDataRezerw_par datetime,@tCzasRezerw_par integer) with encryption as 
	update n5dokmag set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	pKlient=@pKlient_par,
	pKlient_JO=@pKlient_JO_par,
	pKlientPracownik=@pKlientPracownik_par,
	pDokMag=@pDokMag_par,
	nNumOper=@nNumOper_par,
	nTypDok=@nTypDok_par,
	dDataWyst=@dDataWyst_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	curSumaMag=@curSumaMag_par,
	curSumaEwid=@curSumaEwid_par,
	pMagZrod=@pMagZrod_par,
	pMagDocel=@pMagDocel_par,
	cAutoCalc=@cAutoCalc_par,
	wrefDokHandl=@wrefDokHandl_par,
	wrefDokHandl_wrt=@wrefDokHandl_wrt_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	dDataRezerw=@dDataRezerw_par,
	tCzasRezerw=@tCzasRezerw_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokmag_delete')
	drop procedure n5dokmag_delete
go

create procedure n5dokmag_delete(@idobj_par integer) with encryption as 
	delete from n5dokmag where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dokmag_maxid')
	drop procedure n5dokmag_maxid
go

create procedure n5dokmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dokmag
go

if exists (select * from sysobjects where name='n5dokmag_candel')
	drop procedure n5dokmag_candel
go

create procedure n5dokmag_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10162
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pDokMag=@idobj_par
go

-- table: n5zadaniedw
if exists (select * from sysobjects where name='n5zadaniedw_select')
	drop procedure n5zadaniedw_select
go

create procedure n5zadaniedw_select(@idobj_par integer,@versionid_par integer output,
	@pWykonawcaDW_par integer output,
	@dDataPow_par datetime output,
	@tCzasPow_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pWykonawcaDW_par=pWykonawcaDW,
	@dDataPow_par=dDataPow,
	@tCzasPow_par=tCzasPow from n5zadaniedw where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniedw_insert')
	drop procedure n5zadaniedw_insert
go

create procedure n5zadaniedw_insert(@idobj_par integer,@versionid_par integer,@pWykonawcaDW_par integer,@dDataPow_par datetime,@tCzasPow_par integer) with encryption as 
	insert into n5zadaniedw values(@idobj_par,@versionid_par,@pWykonawcaDW_par,@dDataPow_par,@tCzasPow_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniedw_update')
	drop procedure n5zadaniedw_update
go

create procedure n5zadaniedw_update(@idobj_par integer,@versionid_par integer,@pWykonawcaDW_par integer,@dDataPow_par datetime,@tCzasPow_par integer) with encryption as 
	update n5zadaniedw set VersionId=@versionid_par,
	pWykonawcaDW=@pWykonawcaDW_par,
	dDataPow=@dDataPow_par,
	tCzasPow=@tCzasPow_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniedw_delete')
	drop procedure n5zadaniedw_delete
go

create procedure n5zadaniedw_delete(@idobj_par integer) with encryption as 
	delete from n5zadaniedw where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zadaniedw_maxid')
	drop procedure n5zadaniedw_maxid
go

create procedure n5zadaniedw_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zadaniedw
go

if exists (select * from sysobjects where name='n5zadaniedw_candel')
	drop procedure n5zadaniedw_candel
go

create procedure n5zadaniedw_candel(@idobj_par integer) with encryption as 
go

-- table: n5sposplat
if exists (select * from sysobjects where name='n5sposplat_select')
	drop procedure n5sposplat_select
go

create procedure n5sposplat_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(32) output,
	@nDni_par integer output,
	@eTyp_par integer output,
	@strNazwaMiedzynarodowa_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@nDni_par=nDni,
	@eTyp_par=eTyp,
	@strNazwaMiedzynarodowa_par=strNazwaMiedzynarodowa from n5sposplat where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sposplat_insert')
	drop procedure n5sposplat_insert
go

create procedure n5sposplat_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@nDni_par integer,@eTyp_par integer,@strNazwaMiedzynarodowa_par varchar(32)) with encryption as 
	insert into n5sposplat values(@idobj_par,@versionid_par,@strNazwa_par,@nDni_par,@eTyp_par,@strNazwaMiedzynarodowa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5sposplat_update')
	drop procedure n5sposplat_update
go

create procedure n5sposplat_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(32),@nDni_par integer,@eTyp_par integer,@strNazwaMiedzynarodowa_par varchar(32)) with encryption as 
	update n5sposplat set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	nDni=@nDni_par,
	eTyp=@eTyp_par,
	strNazwaMiedzynarodowa=@strNazwaMiedzynarodowa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sposplat_delete')
	drop procedure n5sposplat_delete
go

create procedure n5sposplat_delete(@idobj_par integer) with encryption as 
	delete from n5sposplat where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sposplat_maxid')
	drop procedure n5sposplat_maxid
go

create procedure n5sposplat_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5sposplat
go

if exists (select * from sysobjects where name='n5sposplat_candel')
	drop procedure n5sposplat_candel
go

create procedure n5sposplat_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pSposobPlatnosci=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pSposobPlatnosci=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where wrefParam1=@idobj_par and wrefParam1_wrt=10164
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pSposobPlatnosci=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pSposobPlatnosci=@idobj_par
go

-- table: n5kurswalut
if exists (select * from sysobjects where name='n5kurswalut_select')
	drop procedure n5kurswalut_select
go

create procedure n5kurswalut_select(@idobj_par integer,@versionid_par integer output,
	@pWalZ_par integer output,
	@pWalN_par integer output,
	@dData_par datetime output,
	@curMnoznik_par decimal(12,2) output,
	@curKupnoWal_par decimal(14,4) output,
	@curSprzedWal_par decimal(14,4) output) with encryption as 
	select @versionid_par=VersionId,
	@pWalZ_par=pWalZ,
	@pWalN_par=pWalN,
	@dData_par=dData,
	@curMnoznik_par=curMnoznik,
	@curKupnoWal_par=curKupnoWal,
	@curSprzedWal_par=curSprzedWal from n5kurswalut where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kurswalut_insert')
	drop procedure n5kurswalut_insert
go

create procedure n5kurswalut_insert(@idobj_par integer,@versionid_par integer,@pWalZ_par integer,@pWalN_par integer,@dData_par datetime,@curMnoznik_par decimal(12,2),@curKupnoWal_par decimal(14,4),@curSprzedWal_par decimal(14,4)) with encryption as 
	insert into n5kurswalut values(@idobj_par,@versionid_par,@pWalZ_par,@pWalN_par,@dData_par,@curMnoznik_par,@curKupnoWal_par,@curSprzedWal_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5kurswalut_update')
	drop procedure n5kurswalut_update
go

create procedure n5kurswalut_update(@idobj_par integer,@versionid_par integer,@pWalZ_par integer,@pWalN_par integer,@dData_par datetime,@curMnoznik_par decimal(12,2),@curKupnoWal_par decimal(14,4),@curSprzedWal_par decimal(14,4)) with encryption as 
	update n5kurswalut set VersionId=@versionid_par,
	pWalZ=@pWalZ_par,
	pWalN=@pWalN_par,
	dData=@dData_par,
	curMnoznik=@curMnoznik_par,
	curKupnoWal=@curKupnoWal_par,
	curSprzedWal=@curSprzedWal_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kurswalut_delete')
	drop procedure n5kurswalut_delete
go

create procedure n5kurswalut_delete(@idobj_par integer) with encryption as 
	delete from n5kurswalut where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kurswalut_maxid')
	drop procedure n5kurswalut_maxid
go

create procedure n5kurswalut_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5kurswalut
go

if exists (select * from sysobjects where name='n5kurswalut_candel')
	drop procedure n5kurswalut_candel
go

create procedure n5kurswalut_candel(@idobj_par integer) with encryption as 
go

-- table: n5rokksieg
if exists (select * from sysobjects where name='n5rokksieg_select')
	drop procedure n5rokksieg_select
go

create procedure n5rokksieg_select(@idobj_par integer,@versionid_par integer output,
	@dDataRozp_par datetime output,
	@dDataZakon_par datetime output,
	@dDataZamk_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@dDataRozp_par=dDataRozp,
	@dDataZakon_par=dDataZakon,
	@dDataZamk_par=dDataZamk from n5rokksieg where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rokksieg_insert')
	drop procedure n5rokksieg_insert
go

create procedure n5rokksieg_insert(@idobj_par integer,@versionid_par integer,@dDataRozp_par datetime,@dDataZakon_par datetime,@dDataZamk_par datetime) with encryption as 
	insert into n5rokksieg values(@idobj_par,@versionid_par,@dDataRozp_par,@dDataZakon_par,@dDataZamk_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5rokksieg_update')
	drop procedure n5rokksieg_update
go

create procedure n5rokksieg_update(@idobj_par integer,@versionid_par integer,@dDataRozp_par datetime,@dDataZakon_par datetime,@dDataZamk_par datetime) with encryption as 
	update n5rokksieg set VersionId=@versionid_par,
	dDataRozp=@dDataRozp_par,
	dDataZakon=@dDataZakon_par,
	dDataZamk=@dDataZamk_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rokksieg_delete')
	drop procedure n5rokksieg_delete
go

create procedure n5rokksieg_delete(@idobj_par integer) with encryption as 
	delete from n5rokksieg where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rokksieg_maxid')
	drop procedure n5rokksieg_maxid
go

create procedure n5rokksieg_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5rokksieg
go

if exists (select * from sysobjects where name='n5rokksieg_candel')
	drop procedure n5rokksieg_candel
go

create procedure n5rokksieg_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where pRokKsieg=@idobj_par
go

-- table: n5zamowienie
if exists (select * from sysobjects where name='n5zamowienie_select')
	drop procedure n5zamowienie_select
go

create procedure n5zamowienie_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@dDataWyst_par datetime output,
	@dDataPlat_par datetime output,
	@dDataReal_par datetime output,
	@dDataAkt_par datetime output,
	@pSposobPlatnosci_par integer output,
	@pKlient_par integer output,
	@pKlient_JO_par integer output,
	@pKlientPracownik_par integer output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@eNettoBrutto_par integer output,
	@pZadanie_par integer output,
	@curSumaNetto_par decimal(12,2) output,
	@curSumaVAT_par decimal(12,2) output,
	@curSumaBrutto_par decimal(12,2) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@curSumaWal_par decimal(12,2) output,
	@pWaluta_par integer output,
	@curKurs_par decimal(14,4) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@dDataWyst_par=dDataWyst,
	@dDataPlat_par=dDataPlat,
	@dDataReal_par=dDataReal,
	@dDataAkt_par=dDataAkt,
	@pSposobPlatnosci_par=pSposobPlatnosci,
	@pKlient_par=pKlient,
	@pKlient_JO_par=pKlient_JO,
	@pKlientPracownik_par=pKlientPracownik,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@eNettoBrutto_par=eNettoBrutto,
	@pZadanie_par=pZadanie,
	@curSumaNetto_par=curSumaNetto,
	@curSumaVAT_par=curSumaVAT,
	@curSumaBrutto_par=curSumaBrutto,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@curSumaWal_par=curSumaWal,
	@pWaluta_par=pWaluta,
	@curKurs_par=curKurs,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5zamowienie where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zamowienie_insert')
	drop procedure n5zamowienie_insert
go

create procedure n5zamowienie_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@dDataPlat_par datetime,@dDataReal_par datetime,@dDataAkt_par datetime,@pSposobPlatnosci_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@eNettoBrutto_par integer,@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaWal_par decimal(12,2),@pWaluta_par integer,@curKurs_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5zamowienie values(@idobj_par,@versionid_par,@strNrDok_par,@dDataWyst_par,@dDataPlat_par,@dDataReal_par,@dDataAkt_par,@pSposobPlatnosci_par,@pKlient_par,@pKlient_JO_par,@pKlientPracownik_par,@pUzytRej_par,@strUwagi_par,@eNettoBrutto_par,@pZadanie_par,@curSumaNetto_par,@curSumaVAT_par,@curSumaBrutto_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@curSumaWal_par,@pWaluta_par,@curKurs_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zamowienie_update')
	drop procedure n5zamowienie_update
go

create procedure n5zamowienie_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@dDataPlat_par datetime,@dDataReal_par datetime,@dDataAkt_par datetime,@pSposobPlatnosci_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pKlientPracownik_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@eNettoBrutto_par integer,@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaWal_par decimal(12,2),@pWaluta_par integer,@curKurs_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5zamowienie set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	dDataWyst=@dDataWyst_par,
	dDataPlat=@dDataPlat_par,
	dDataReal=@dDataReal_par,
	dDataAkt=@dDataAkt_par,
	pSposobPlatnosci=@pSposobPlatnosci_par,
	pKlient=@pKlient_par,
	pKlient_JO=@pKlient_JO_par,
	pKlientPracownik=@pKlientPracownik_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	eNettoBrutto=@eNettoBrutto_par,
	pZadanie=@pZadanie_par,
	curSumaNetto=@curSumaNetto_par,
	curSumaVAT=@curSumaVAT_par,
	curSumaBrutto=@curSumaBrutto_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	curSumaWal=@curSumaWal_par,
	pWaluta=@pWaluta_par,
	curKurs=@curKurs_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zamowienie_delete')
	drop procedure n5zamowienie_delete
go

create procedure n5zamowienie_delete(@idobj_par integer) with encryption as 
	delete from n5zamowienie where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zamowienie_maxid')
	drop procedure n5zamowienie_maxid
go

create procedure n5zamowienie_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zamowienie
go

if exists (select * from sysobjects where name='n5zamowienie_candel')
	drop procedure n5zamowienie_candel
go

create procedure n5zamowienie_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10172
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pZamowienie=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10172
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where wrefDokHandl=@idobj_par and wrefDokHandl_wrt=10172
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pZamowienie=@idobj_par
go

-- table: n5pozzamowienie
if exists (select * from sysobjects where name='n5pozzamowienie_select')
	drop procedure n5pozzamowienie_select
go

create procedure n5pozzamowienie_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@pOpak_par integer output,
	@curCenaBazNetto_par decimal(14,4) output,
	@curCenaBazBrutto_par decimal(14,4) output,
	@curRabat_par decimal(12,2) output,
	@eVAT_par integer output,
	@curCenaNetto_par decimal(14,4) output,
	@curCenaBrutto_par decimal(14,4) output,
	@curWartNetto_par decimal(12,2) output,
	@curVAT_par decimal(12,2) output,
	@curCenaBazowaNettoWal_par decimal(14,4) output,
	@curCenaNettoWal_par decimal(14,4) output,
	@curWartWal_par decimal(12,2) output,
	@strUwagi_par varchar(512) output,
	@curIloscOpakPoz_par decimal(14,4) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@curIloscOpak_par=curIloscOpak,
	@pOpak_par=pOpak,
	@curCenaBazNetto_par=curCenaBazNetto,
	@curCenaBazBrutto_par=curCenaBazBrutto,
	@curRabat_par=curRabat,
	@eVAT_par=eVAT,
	@curCenaNetto_par=curCenaNetto,
	@curCenaBrutto_par=curCenaBrutto,
	@curWartNetto_par=curWartNetto,
	@curVAT_par=curVAT,
	@curCenaBazowaNettoWal_par=curCenaBazowaNettoWal,
	@curCenaNettoWal_par=curCenaNettoWal,
	@curWartWal_par=curWartWal,
	@strUwagi_par=strUwagi,
	@curIloscOpakPoz_par=curIloscOpakPoz,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5pozzamowienie where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzamowienie_insert')
	drop procedure n5pozzamowienie_insert
go

create procedure n5pozzamowienie_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@curCenaBazNetto_par decimal(14,4),@curCenaBazBrutto_par decimal(14,4),@curRabat_par decimal(12,2),@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curCenaBazowaNettoWal_par decimal(14,4),@curCenaNettoWal_par decimal(14,4),@curWartWal_par decimal(12,2),@strUwagi_par varchar(512),@curIloscOpakPoz_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozzamowienie values(@idobj_par,@versionid_par,@pProdukt_par,@curIloscOpak_par,@pOpak_par,@curCenaBazNetto_par,@curCenaBazBrutto_par,@curRabat_par,@eVAT_par,@curCenaNetto_par,@curCenaBrutto_par,@curWartNetto_par,@curVAT_par,@curCenaBazowaNettoWal_par,@curCenaNettoWal_par,@curWartWal_par,@strUwagi_par,@curIloscOpakPoz_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzamowienie_update')
	drop procedure n5pozzamowienie_update
go

create procedure n5pozzamowienie_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@curCenaBazNetto_par decimal(14,4),@curCenaBazBrutto_par decimal(14,4),@curRabat_par decimal(12,2),@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curCenaBazowaNettoWal_par decimal(14,4),@curCenaNettoWal_par decimal(14,4),@curWartWal_par decimal(12,2),@strUwagi_par varchar(512),@curIloscOpakPoz_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5pozzamowienie set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	curIloscOpak=@curIloscOpak_par,
	pOpak=@pOpak_par,
	curCenaBazNetto=@curCenaBazNetto_par,
	curCenaBazBrutto=@curCenaBazBrutto_par,
	curRabat=@curRabat_par,
	eVAT=@eVAT_par,
	curCenaNetto=@curCenaNetto_par,
	curCenaBrutto=@curCenaBrutto_par,
	curWartNetto=@curWartNetto_par,
	curVAT=@curVAT_par,
	curCenaBazowaNettoWal=@curCenaBazowaNettoWal_par,
	curCenaNettoWal=@curCenaNettoWal_par,
	curWartWal=@curWartWal_par,
	strUwagi=@strUwagi_par,
	curIloscOpakPoz=@curIloscOpakPoz_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzamowienie_delete')
	drop procedure n5pozzamowienie_delete
go

create procedure n5pozzamowienie_delete(@idobj_par integer) with encryption as 
	delete from n5pozzamowienie where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzamowienie_maxid')
	drop procedure n5pozzamowienie_maxid
go

create procedure n5pozzamowienie_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozzamowienie
go

if exists (select * from sysobjects where name='n5pozzamowienie_candel')
	drop procedure n5pozzamowienie_candel
go

create procedure n5pozzamowienie_candel(@idobj_par integer) with encryption as 
go

-- table: n5pozzakup
if exists (select * from sysobjects where name='n5pozzakup_select')
	drop procedure n5pozzakup_select
go

create procedure n5pozzakup_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@pOpak_par integer output,
	@eVAT_par integer output,
	@curCenaNetto_par decimal(14,4) output,
	@curCenaBrutto_par decimal(14,4) output,
	@curWartNetto_par decimal(12,2) output,
	@curVAT_par decimal(12,2) output,
	@curWartBrutto_par decimal(12,2) output,
	@curCenaNettoWal_par decimal(14,4) output,
	@strUwagi_par varchar(512) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@curIloscOpak_par=curIloscOpak,
	@pOpak_par=pOpak,
	@eVAT_par=eVAT,
	@curCenaNetto_par=curCenaNetto,
	@curCenaBrutto_par=curCenaBrutto,
	@curWartNetto_par=curWartNetto,
	@curVAT_par=curVAT,
	@curWartBrutto_par=curWartBrutto,
	@curCenaNettoWal_par=curCenaNettoWal,
	@strUwagi_par=strUwagi,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5pozzakup where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzakup_insert')
	drop procedure n5pozzakup_insert
go

create procedure n5pozzakup_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curWartBrutto_par decimal(12,2),@curCenaNettoWal_par decimal(14,4),@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozzakup values(@idobj_par,@versionid_par,@pProdukt_par,@curIloscOpak_par,@pOpak_par,@eVAT_par,@curCenaNetto_par,@curCenaBrutto_par,@curWartNetto_par,@curVAT_par,@curWartBrutto_par,@curCenaNettoWal_par,@strUwagi_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzakup_update')
	drop procedure n5pozzakup_update
go

create procedure n5pozzakup_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@curIloscOpak_par decimal(14,4),@pOpak_par integer,@eVAT_par integer,@curCenaNetto_par decimal(14,4),@curCenaBrutto_par decimal(14,4),@curWartNetto_par decimal(12,2),@curVAT_par decimal(12,2),@curWartBrutto_par decimal(12,2),@curCenaNettoWal_par decimal(14,4),@strUwagi_par varchar(512),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5pozzakup set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	curIloscOpak=@curIloscOpak_par,
	pOpak=@pOpak_par,
	eVAT=@eVAT_par,
	curCenaNetto=@curCenaNetto_par,
	curCenaBrutto=@curCenaBrutto_par,
	curWartNetto=@curWartNetto_par,
	curVAT=@curVAT_par,
	curWartBrutto=@curWartBrutto_par,
	curCenaNettoWal=@curCenaNettoWal_par,
	strUwagi=@strUwagi_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzakup_delete')
	drop procedure n5pozzakup_delete
go

create procedure n5pozzakup_delete(@idobj_par integer) with encryption as 
	delete from n5pozzakup where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzakup_maxid')
	drop procedure n5pozzakup_maxid
go

create procedure n5pozzakup_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozzakup
go

if exists (select * from sysobjects where name='n5pozzakup_candel')
	drop procedure n5pozzakup_candel
go

create procedure n5pozzakup_candel(@idobj_par integer) with encryption as 
go

-- table: n5zakup
if exists (select * from sysobjects where name='n5zakup_select')
	drop procedure n5zakup_select
go

create procedure n5zakup_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@strNrDokObcy_par varchar(32) output,
	@dDataWyst_par datetime output,
	@dDataOtrzym_par datetime output,
	@dDataZakupu_par datetime output,
	@dDataPlat_par datetime output,
	@pSposobPlatnosci_par integer output,
	@pDostawca_par integer output,
	@pDostawca_JO_par integer output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(128) output,
	@pZadanie_par integer output,
	@curSumaNetto_par decimal(12,2) output,
	@curSumaVAT_par decimal(12,2) output,
	@curSumaBrutto_par decimal(12,2) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@pTransakcja_par integer output,
	@curNetto0_par decimal(12,2) output,
	@curNettoZw_par decimal(12,2) output,
	@curNettoNp_par decimal(12,2) output,
	@curNetto2_par decimal(12,2) output,
	@curVat2_par decimal(12,2) output,
	@curNetto3_par decimal(12,2) output,
	@curVat3_par decimal(12,2) output,
	@curNetto4_par decimal(12,2) output,
	@curVat4_par decimal(12,2) output,
	@curNetto7_par decimal(12,2) output,
	@curVat7_par decimal(12,2) output,
	@curNetto12_par decimal(12,2) output,
	@curVat12_par decimal(12,2) output,
	@curNetto17_par decimal(12,2) output,
	@curVat17_par decimal(12,2) output,
	@curNetto22_par decimal(12,2) output,
	@curVat22_par decimal(12,2) output,
	@pPopZAkup_par integer output,
	@curSumaWal_par decimal(12,2) output,
	@pWaluta_par integer output,
	@eZwOpSprz_par integer output,
	@eTypZakup_par integer output,
	@pRozlVat_par integer output,
	@curKurs_par decimal(12,2) output,
	@cAutoCalc_par varchar(1) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@curOplatyZagr_par decimal(12,2) output,
	@curClo_par decimal(12,2) output,
	@curAkcyza_par decimal(12,2) output,
	@curOplatyKraj_par decimal(12,2) output,
	@curKursCelny_par decimal(12,2) output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@strNrDokObcy_par=strNrDokObcy,
	@dDataWyst_par=dDataWyst,
	@dDataOtrzym_par=dDataOtrzym,
	@dDataZakupu_par=dDataZakupu,
	@dDataPlat_par=dDataPlat,
	@pSposobPlatnosci_par=pSposobPlatnosci,
	@pDostawca_par=pDostawca,
	@pDostawca_JO_par=pDostawca_JO,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@pZadanie_par=pZadanie,
	@curSumaNetto_par=curSumaNetto,
	@curSumaVAT_par=curSumaVAT,
	@curSumaBrutto_par=curSumaBrutto,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@pTransakcja_par=pTransakcja,
	@curNetto0_par=curNetto0,
	@curNettoZw_par=curNettoZw,
	@curNettoNp_par=curNettoNp,
	@curNetto2_par=curNetto2,
	@curVat2_par=curVat2,
	@curNetto3_par=curNetto3,
	@curVat3_par=curVat3,
	@curNetto4_par=curNetto4,
	@curVat4_par=curVat4,
	@curNetto7_par=curNetto7,
	@curVat7_par=curVat7,
	@curNetto12_par=curNetto12,
	@curVat12_par=curVat12,
	@curNetto17_par=curNetto17,
	@curVat17_par=curVat17,
	@curNetto22_par=curNetto22,
	@curVat22_par=curVat22,
	@pPopZAkup_par=pPopZAkup,
	@curSumaWal_par=curSumaWal,
	@pWaluta_par=pWaluta,
	@eZwOpSprz_par=eZwOpSprz,
	@eTypZakup_par=eTypZakup,
	@pRozlVat_par=pRozlVat,
	@curKurs_par=curKurs,
	@cAutoCalc_par=cAutoCalc,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@curOplatyZagr_par=curOplatyZagr,
	@curClo_par=curClo,
	@curAkcyza_par=curAkcyza,
	@curOplatyKraj_par=curOplatyKraj,
	@curKursCelny_par=curKursCelny from n5zakup where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zakup_insert')
	drop procedure n5zakup_insert
go

create procedure n5zakup_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@strNrDokObcy_par varchar(32),@dDataWyst_par datetime,@dDataOtrzym_par datetime,@dDataZakupu_par datetime,@dDataPlat_par datetime,@pSposobPlatnosci_par integer,@pDostawca_par integer,@pDostawca_JO_par integer,@pUzytRej_par integer,@strUwagi_par varchar(128),@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pTransakcja_par integer,@curNetto0_par decimal(12,2),@curNettoZw_par decimal(12,2),@curNettoNp_par decimal(12,2),@curNetto2_par decimal(12,2),@curVat2_par decimal(12,2),@curNetto3_par decimal(12,2),@curVat3_par decimal(12,2),@curNetto4_par decimal(12,2),@curVat4_par decimal(12,2),@curNetto7_par decimal(12,2),@curVat7_par decimal(12,2),@curNetto12_par decimal(12,2),@curVat12_par decimal(12,2),@curNetto17_par decimal(12,2),@curVat17_par decimal(12,2),@curNetto22_par decimal(12,2),@curVat22_par decimal(12,2),@pPopZAkup_par integer,@curSumaWal_par decimal(12,2),@pWaluta_par integer,@eZwOpSprz_par integer,@eTypZakup_par integer,@pRozlVat_par integer,@curKurs_par decimal(12,2),@cAutoCalc_par varchar(1),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@curOplatyZagr_par decimal(12,2),@curClo_par decimal(12,2),@curAkcyza_par decimal(12,2),@curOplatyKraj_par decimal(12,2),@curKursCelny_par decimal(12,2)) with encryption as 
	insert into n5zakup values(@idobj_par,@versionid_par,@strNrDok_par,@strNrDokObcy_par,@dDataWyst_par,@dDataOtrzym_par,@dDataZakupu_par,@dDataPlat_par,@pSposobPlatnosci_par,@pDostawca_par,@pDostawca_JO_par,@pUzytRej_par,@strUwagi_par,@pZadanie_par,@curSumaNetto_par,@curSumaVAT_par,@curSumaBrutto_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@pTransakcja_par,@curNetto0_par,@curNettoZw_par,@curNettoNp_par,@curNetto2_par,@curVat2_par,@curNetto3_par,@curVat3_par,@curNetto4_par,@curVat4_par,@curNetto7_par,@curVat7_par,@curNetto12_par,@curVat12_par,@curNetto17_par,@curVat17_par,@curNetto22_par,@curVat22_par,@pPopZAkup_par,@curSumaWal_par,@pWaluta_par,@eZwOpSprz_par,@eTypZakup_par,@pRozlVat_par,@curKurs_par,@cAutoCalc_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par,@curOplatyZagr_par,@curClo_par,@curAkcyza_par,@curOplatyKraj_par,@curKursCelny_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zakup_update')
	drop procedure n5zakup_update
go

create procedure n5zakup_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@strNrDokObcy_par varchar(32),@dDataWyst_par datetime,@dDataOtrzym_par datetime,@dDataZakupu_par datetime,@dDataPlat_par datetime,@pSposobPlatnosci_par integer,@pDostawca_par integer,@pDostawca_JO_par integer,@pUzytRej_par integer,@strUwagi_par varchar(128),@pZadanie_par integer,@curSumaNetto_par decimal(12,2),@curSumaVAT_par decimal(12,2),@curSumaBrutto_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pTransakcja_par integer,@curNetto0_par decimal(12,2),@curNettoZw_par decimal(12,2),@curNettoNp_par decimal(12,2),@curNetto2_par decimal(12,2),@curVat2_par decimal(12,2),@curNetto3_par decimal(12,2),@curVat3_par decimal(12,2),@curNetto4_par decimal(12,2),@curVat4_par decimal(12,2),@curNetto7_par decimal(12,2),@curVat7_par decimal(12,2),@curNetto12_par decimal(12,2),@curVat12_par decimal(12,2),@curNetto17_par decimal(12,2),@curVat17_par decimal(12,2),@curNetto22_par decimal(12,2),@curVat22_par decimal(12,2),@pPopZAkup_par integer,@curSumaWal_par decimal(12,2),@pWaluta_par integer,@eZwOpSprz_par integer,@eTypZakup_par integer,@pRozlVat_par integer,@curKurs_par decimal(12,2),@cAutoCalc_par varchar(1),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@curOplatyZagr_par decimal(12,2),@curClo_par decimal(12,2),@curAkcyza_par decimal(12,2),@curOplatyKraj_par decimal(12,2),@curKursCelny_par decimal(12,2)) with encryption as 
	update n5zakup set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	strNrDokObcy=@strNrDokObcy_par,
	dDataWyst=@dDataWyst_par,
	dDataOtrzym=@dDataOtrzym_par,
	dDataZakupu=@dDataZakupu_par,
	dDataPlat=@dDataPlat_par,
	pSposobPlatnosci=@pSposobPlatnosci_par,
	pDostawca=@pDostawca_par,
	pDostawca_JO=@pDostawca_JO_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	pZadanie=@pZadanie_par,
	curSumaNetto=@curSumaNetto_par,
	curSumaVAT=@curSumaVAT_par,
	curSumaBrutto=@curSumaBrutto_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	pTransakcja=@pTransakcja_par,
	curNetto0=@curNetto0_par,
	curNettoZw=@curNettoZw_par,
	curNettoNp=@curNettoNp_par,
	curNetto2=@curNetto2_par,
	curVat2=@curVat2_par,
	curNetto3=@curNetto3_par,
	curVat3=@curVat3_par,
	curNetto4=@curNetto4_par,
	curVat4=@curVat4_par,
	curNetto7=@curNetto7_par,
	curVat7=@curVat7_par,
	curNetto12=@curNetto12_par,
	curVat12=@curVat12_par,
	curNetto17=@curNetto17_par,
	curVat17=@curVat17_par,
	curNetto22=@curNetto22_par,
	curVat22=@curVat22_par,
	pPopZAkup=@pPopZAkup_par,
	curSumaWal=@curSumaWal_par,
	pWaluta=@pWaluta_par,
	eZwOpSprz=@eZwOpSprz_par,
	eTypZakup=@eTypZakup_par,
	pRozlVat=@pRozlVat_par,
	curKurs=@curKurs_par,
	cAutoCalc=@cAutoCalc_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	curOplatyZagr=@curOplatyZagr_par,
	curClo=@curClo_par,
	curAkcyza=@curAkcyza_par,
	curOplatyKraj=@curOplatyKraj_par,
	curKursCelny=@curKursCelny_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zakup_delete')
	drop procedure n5zakup_delete
go

create procedure n5zakup_delete(@idobj_par integer) with encryption as 
	delete from n5zakup where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zakup_maxid')
	drop procedure n5zakup_maxid
go

create procedure n5zakup_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zakup
go

if exists (select * from sysobjects where name='n5zakup_candel')
	drop procedure n5zakup_candel
go

create procedure n5zakup_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10176
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10176
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where wrefDokHandl=@idobj_par and wrefDokHandl_wrt=10176
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pPopZAkup=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where wrefDokument=@idobj_par and wrefDokument_wrt=10176
go

-- table: n5rozlvat
if exists (select * from sysobjects where name='n5rozlvat_select')
	drop procedure n5rozlvat_select
go

create procedure n5rozlvat_select(@idobj_par integer,@versionid_par integer output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@curSpZwN_par decimal(12,2) output,
	@curSpExN_par decimal(12,2) output,
	@curSpEx21N_par decimal(12,2) output,
	@curSpOp0_par decimal(12,2) output,
	@curSpOp3N_par decimal(12,2) output,
	@curSpOp3V_par decimal(12,2) output,
	@curSpOp7N_par decimal(12,2) output,
	@curSpOp7V_par decimal(12,2) output,
	@curSpOp22N_par decimal(12,2) output,
	@curSpOp22V_par decimal(12,2) output,
	@curSpNP_par decimal(12,2) output,
	@curSpSpis6V_par decimal(12,2) output,
	@curSpRazemN_par decimal(12,2) output,
	@curSpRazemV_par decimal(12,2) output,
	@curPrNadV_par decimal(12,2) output,
	@curPrRU14V_par decimal(12,2) output,
	@curZPSON_par decimal(12,2) output,
	@curZPSOV_par decimal(12,2) output,
	@curZPSMN_par decimal(12,2) output,
	@curZPSMV_par decimal(12,2) output,
	@curZPTON_par decimal(12,2) output,
	@curZPTOV_par decimal(12,2) output,
	@curZPTMN_par decimal(12,2) output,
	@curZPTMV_par decimal(12,2) output,
	@curZASON_par decimal(12,2) output,
	@curZASOV_par decimal(12,2) output,
	@curZASMN_par decimal(12,2) output,
	@curZASMV_par decimal(12,2) output,
	@curZATON_par decimal(12,2) output,
	@curZATOV_par decimal(12,2) output,
	@curZATMN_par decimal(12,2) output,
	@curZATMV_par decimal(12,2) output,
	@curZNON_par decimal(12,2) output,
	@curZNOV_par decimal(12,2) output,
	@curSpOpod6MN_par decimal(12,2) output,
	@curSpTotal6MN_par decimal(12,2) output,
	@curVATZSMV_par decimal(12,2) output,
	@curVATZTMV_par decimal(12,2) output,
	@curVATOdl_par decimal(12,2) output,
	@curVATNadPlus_par decimal(12,2) output,
	@curKasaOdl_par decimal(12,2) output,
	@curVATZaniech_par decimal(12,2) output,
	@curVATDoZapl_par decimal(12,2) output,
	@curVATNadMin_par decimal(12,2) output,
	@curKasaZwrot_par decimal(12,2) output,
	@curNadMinTotal_par decimal(12,2) output,
	@curNadMinZwrot_par decimal(12,2) output,
	@curNadMinNast_par decimal(12,2) output,
	@pUzytRej_par integer output,
	@pZadanie_par integer output,
	@pSchematDekr_par integer output,
	@pDowKsieg_par integer output,
	@pTransakcja_par integer output,
	@pUrzadSkarbowy_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@curSpZwN_par=curSpZwN,
	@curSpExN_par=curSpExN,
	@curSpEx21N_par=curSpEx21N,
	@curSpOp0_par=curSpOp0,
	@curSpOp3N_par=curSpOp3N,
	@curSpOp3V_par=curSpOp3V,
	@curSpOp7N_par=curSpOp7N,
	@curSpOp7V_par=curSpOp7V,
	@curSpOp22N_par=curSpOp22N,
	@curSpOp22V_par=curSpOp22V,
	@curSpNP_par=curSpNP,
	@curSpSpis6V_par=curSpSpis6V,
	@curSpRazemN_par=curSpRazemN,
	@curSpRazemV_par=curSpRazemV,
	@curPrNadV_par=curPrNadV,
	@curPrRU14V_par=curPrRU14V,
	@curZPSON_par=curZPSON,
	@curZPSOV_par=curZPSOV,
	@curZPSMN_par=curZPSMN,
	@curZPSMV_par=curZPSMV,
	@curZPTON_par=curZPTON,
	@curZPTOV_par=curZPTOV,
	@curZPTMN_par=curZPTMN,
	@curZPTMV_par=curZPTMV,
	@curZASON_par=curZASON,
	@curZASOV_par=curZASOV,
	@curZASMN_par=curZASMN,
	@curZASMV_par=curZASMV,
	@curZATON_par=curZATON,
	@curZATOV_par=curZATOV,
	@curZATMN_par=curZATMN,
	@curZATMV_par=curZATMV,
	@curZNON_par=curZNON,
	@curZNOV_par=curZNOV,
	@curSpOpod6MN_par=curSpOpod6MN,
	@curSpTotal6MN_par=curSpTotal6MN,
	@curVATZSMV_par=curVATZSMV,
	@curVATZTMV_par=curVATZTMV,
	@curVATOdl_par=curVATOdl,
	@curVATNadPlus_par=curVATNadPlus,
	@curKasaOdl_par=curKasaOdl,
	@curVATZaniech_par=curVATZaniech,
	@curVATDoZapl_par=curVATDoZapl,
	@curVATNadMin_par=curVATNadMin,
	@curKasaZwrot_par=curKasaZwrot,
	@curNadMinTotal_par=curNadMinTotal,
	@curNadMinZwrot_par=curNadMinZwrot,
	@curNadMinNast_par=curNadMinNast,
	@pUzytRej_par=pUzytRej,
	@pZadanie_par=pZadanie,
	@pSchematDekr_par=pSchematDekr,
	@pDowKsieg_par=pDowKsieg,
	@pTransakcja_par=pTransakcja,
	@pUrzadSkarbowy_par=pUrzadSkarbowy from n5rozlvat where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlvat_insert')
	drop procedure n5rozlvat_insert
go

create procedure n5rozlvat_insert(@idobj_par integer,@versionid_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@curSpZwN_par decimal(12,2),@curSpExN_par decimal(12,2),@curSpEx21N_par decimal(12,2),@curSpOp0_par decimal(12,2),@curSpOp3N_par decimal(12,2),@curSpOp3V_par decimal(12,2),@curSpOp7N_par decimal(12,2),@curSpOp7V_par decimal(12,2),@curSpOp22N_par decimal(12,2),@curSpOp22V_par decimal(12,2),@curSpNP_par decimal(12,2),@curSpSpis6V_par decimal(12,2),@curSpRazemN_par decimal(12,2),@curSpRazemV_par decimal(12,2),@curPrNadV_par decimal(12,2),@curPrRU14V_par decimal(12,2),@curZPSON_par decimal(12,2),@curZPSOV_par decimal(12,2),@curZPSMN_par decimal(12,2),@curZPSMV_par decimal(12,2),@curZPTON_par decimal(12,2),@curZPTOV_par decimal(12,2),@curZPTMN_par decimal(12,2),@curZPTMV_par decimal(12,2),@curZASON_par decimal(12,2),@curZASOV_par decimal(12,2),@curZASMN_par decimal(12,2),@curZASMV_par decimal(12,2),@curZATON_par decimal(12,2),@curZATOV_par decimal(12,2),@curZATMN_par decimal(12,2),@curZATMV_par decimal(12,2),@curZNON_par decimal(12,2),@curZNOV_par decimal(12,2),@curSpOpod6MN_par decimal(12,2),@curSpTotal6MN_par decimal(12,2),@curVATZSMV_par decimal(12,2),@curVATZTMV_par decimal(12,2),@curVATOdl_par decimal(12,2),@curVATNadPlus_par decimal(12,2),@curKasaOdl_par decimal(12,2),@curVATZaniech_par decimal(12,2),@curVATDoZapl_par decimal(12,2),@curVATNadMin_par decimal(12,2),@curKasaZwrot_par decimal(12,2),@curNadMinTotal_par decimal(12,2),@curNadMinZwrot_par decimal(12,2),@curNadMinNast_par decimal(12,2),@pUzytRej_par integer,@pZadanie_par integer,@pSchematDekr_par integer,@pDowKsieg_par integer,@pTransakcja_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	insert into n5rozlvat values(@idobj_par,@versionid_par,@dDataOd_par,@dDataDo_par,@curSpZwN_par,@curSpExN_par,@curSpEx21N_par,@curSpOp0_par,@curSpOp3N_par,@curSpOp3V_par,@curSpOp7N_par,@curSpOp7V_par,@curSpOp22N_par,@curSpOp22V_par,@curSpNP_par,@curSpSpis6V_par,@curSpRazemN_par,@curSpRazemV_par,@curPrNadV_par,@curPrRU14V_par,@curZPSON_par,@curZPSOV_par,@curZPSMN_par,@curZPSMV_par,@curZPTON_par,@curZPTOV_par,@curZPTMN_par,@curZPTMV_par,@curZASON_par,@curZASOV_par,@curZASMN_par,@curZASMV_par,@curZATON_par,@curZATOV_par,@curZATMN_par,@curZATMV_par,@curZNON_par,@curZNOV_par,@curSpOpod6MN_par,@curSpTotal6MN_par,@curVATZSMV_par,@curVATZTMV_par,@curVATOdl_par,@curVATNadPlus_par,@curKasaOdl_par,@curVATZaniech_par,@curVATDoZapl_par,@curVATNadMin_par,@curKasaZwrot_par,@curNadMinTotal_par,@curNadMinZwrot_par,@curNadMinNast_par,@pUzytRej_par,@pZadanie_par,@pSchematDekr_par,@pDowKsieg_par,@pTransakcja_par,@pUrzadSkarbowy_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlvat_update')
	drop procedure n5rozlvat_update
go

create procedure n5rozlvat_update(@idobj_par integer,@versionid_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@curSpZwN_par decimal(12,2),@curSpExN_par decimal(12,2),@curSpEx21N_par decimal(12,2),@curSpOp0_par decimal(12,2),@curSpOp3N_par decimal(12,2),@curSpOp3V_par decimal(12,2),@curSpOp7N_par decimal(12,2),@curSpOp7V_par decimal(12,2),@curSpOp22N_par decimal(12,2),@curSpOp22V_par decimal(12,2),@curSpNP_par decimal(12,2),@curSpSpis6V_par decimal(12,2),@curSpRazemN_par decimal(12,2),@curSpRazemV_par decimal(12,2),@curPrNadV_par decimal(12,2),@curPrRU14V_par decimal(12,2),@curZPSON_par decimal(12,2),@curZPSOV_par decimal(12,2),@curZPSMN_par decimal(12,2),@curZPSMV_par decimal(12,2),@curZPTON_par decimal(12,2),@curZPTOV_par decimal(12,2),@curZPTMN_par decimal(12,2),@curZPTMV_par decimal(12,2),@curZASON_par decimal(12,2),@curZASOV_par decimal(12,2),@curZASMN_par decimal(12,2),@curZASMV_par decimal(12,2),@curZATON_par decimal(12,2),@curZATOV_par decimal(12,2),@curZATMN_par decimal(12,2),@curZATMV_par decimal(12,2),@curZNON_par decimal(12,2),@curZNOV_par decimal(12,2),@curSpOpod6MN_par decimal(12,2),@curSpTotal6MN_par decimal(12,2),@curVATZSMV_par decimal(12,2),@curVATZTMV_par decimal(12,2),@curVATOdl_par decimal(12,2),@curVATNadPlus_par decimal(12,2),@curKasaOdl_par decimal(12,2),@curVATZaniech_par decimal(12,2),@curVATDoZapl_par decimal(12,2),@curVATNadMin_par decimal(12,2),@curKasaZwrot_par decimal(12,2),@curNadMinTotal_par decimal(12,2),@curNadMinZwrot_par decimal(12,2),@curNadMinNast_par decimal(12,2),@pUzytRej_par integer,@pZadanie_par integer,@pSchematDekr_par integer,@pDowKsieg_par integer,@pTransakcja_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	update n5rozlvat set VersionId=@versionid_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	curSpZwN=@curSpZwN_par,
	curSpExN=@curSpExN_par,
	curSpEx21N=@curSpEx21N_par,
	curSpOp0=@curSpOp0_par,
	curSpOp3N=@curSpOp3N_par,
	curSpOp3V=@curSpOp3V_par,
	curSpOp7N=@curSpOp7N_par,
	curSpOp7V=@curSpOp7V_par,
	curSpOp22N=@curSpOp22N_par,
	curSpOp22V=@curSpOp22V_par,
	curSpNP=@curSpNP_par,
	curSpSpis6V=@curSpSpis6V_par,
	curSpRazemN=@curSpRazemN_par,
	curSpRazemV=@curSpRazemV_par,
	curPrNadV=@curPrNadV_par,
	curPrRU14V=@curPrRU14V_par,
	curZPSON=@curZPSON_par,
	curZPSOV=@curZPSOV_par,
	curZPSMN=@curZPSMN_par,
	curZPSMV=@curZPSMV_par,
	curZPTON=@curZPTON_par,
	curZPTOV=@curZPTOV_par,
	curZPTMN=@curZPTMN_par,
	curZPTMV=@curZPTMV_par,
	curZASON=@curZASON_par,
	curZASOV=@curZASOV_par,
	curZASMN=@curZASMN_par,
	curZASMV=@curZASMV_par,
	curZATON=@curZATON_par,
	curZATOV=@curZATOV_par,
	curZATMN=@curZATMN_par,
	curZATMV=@curZATMV_par,
	curZNON=@curZNON_par,
	curZNOV=@curZNOV_par,
	curSpOpod6MN=@curSpOpod6MN_par,
	curSpTotal6MN=@curSpTotal6MN_par,
	curVATZSMV=@curVATZSMV_par,
	curVATZTMV=@curVATZTMV_par,
	curVATOdl=@curVATOdl_par,
	curVATNadPlus=@curVATNadPlus_par,
	curKasaOdl=@curKasaOdl_par,
	curVATZaniech=@curVATZaniech_par,
	curVATDoZapl=@curVATDoZapl_par,
	curVATNadMin=@curVATNadMin_par,
	curKasaZwrot=@curKasaZwrot_par,
	curNadMinTotal=@curNadMinTotal_par,
	curNadMinZwrot=@curNadMinZwrot_par,
	curNadMinNast=@curNadMinNast_par,
	pUzytRej=@pUzytRej_par,
	pZadanie=@pZadanie_par,
	pSchematDekr=@pSchematDekr_par,
	pDowKsieg=@pDowKsieg_par,
	pTransakcja=@pTransakcja_par,
	pUrzadSkarbowy=@pUrzadSkarbowy_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlvat_delete')
	drop procedure n5rozlvat_delete
go

create procedure n5rozlvat_delete(@idobj_par integer) with encryption as 
	delete from n5rozlvat where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlvat_maxid')
	drop procedure n5rozlvat_maxid
go

create procedure n5rozlvat_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5rozlvat
go

if exists (select * from sysobjects where name='n5rozlvat_candel')
	drop procedure n5rozlvat_candel
go

create procedure n5rozlvat_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10177
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pRozlVat=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10177
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pRozlVat=@idobj_par
go

-- table: n5grupasrtrw
if exists (select * from sysobjects where name='n5grupasrtrw_select')
	drop procedure n5grupasrtrw_select
go

create procedure n5grupasrtrw_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pGrupaNadrzedna_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pGrupaNadrzedna_par=pGrupaNadrzedna from n5grupasrtrw where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupasrtrw_insert')
	drop procedure n5grupasrtrw_insert
go

create procedure n5grupasrtrw_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pGrupaNadrzedna_par integer) with encryption as 
	insert into n5grupasrtrw values(@idobj_par,@versionid_par,@strNazwa_par,@pGrupaNadrzedna_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupasrtrw_update')
	drop procedure n5grupasrtrw_update
go

create procedure n5grupasrtrw_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pGrupaNadrzedna_par integer) with encryption as 
	update n5grupasrtrw set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pGrupaNadrzedna=@pGrupaNadrzedna_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupasrtrw_delete')
	drop procedure n5grupasrtrw_delete
go

create procedure n5grupasrtrw_delete(@idobj_par integer) with encryption as 
	delete from n5grupasrtrw where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5grupasrtrw_maxid')
	drop procedure n5grupasrtrw_maxid
go

create procedure n5grupasrtrw_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5grupasrtrw
go

if exists (select * from sysobjects where name='n5grupasrtrw_candel')
	drop procedure n5grupasrtrw_candel
go

create procedure n5grupasrtrw_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10178 as integer),idobj from n5grupasrtrw where pGrupaNadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10179 as integer),idobj from n5srtrw where pGrupa=@idobj_par
go

-- table: n5srtrw
if exists (select * from sysobjects where name='n5srtrw_select')
	drop procedure n5srtrw_select
go

create procedure n5srtrw_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@strNumEwid_par varchar(64) output,
	@strNumSer_par varchar(64) output,
	@strKRST_par varchar(64) output,
	@pGrupa_par integer output,
	@dDataGwar_par datetime output,
	@eRodzaj_par integer output,
	@pPracownik_par integer output,
	@strUwagi_par varchar(255) output,
	@pMUJO_par integer output,
	@nLicznik_par integer output,
	@curWartoscPod_par decimal(12,2) output,
	@curUmorzPod_par decimal(12,2) output,
	@curWartoscBil_par decimal(12,2) output,
	@curUmorzBil_par decimal(12,2) output,
	@curStawkaPod_par decimal(12,2) output,
	@curStawkaBil_par decimal(12,2) output,
	@eMetAmPod_par integer output,
	@eMetAmBil_par integer output,
	@eStatus_par integer output,
	@nRokProd_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strNumEwid_par=strNumEwid,
	@strNumSer_par=strNumSer,
	@strKRST_par=strKRST,
	@pGrupa_par=pGrupa,
	@dDataGwar_par=dDataGwar,
	@eRodzaj_par=eRodzaj,
	@pPracownik_par=pPracownik,
	@strUwagi_par=strUwagi,
	@pMUJO_par=pMUJO,
	@nLicznik_par=nLicznik,
	@curWartoscPod_par=curWartoscPod,
	@curUmorzPod_par=curUmorzPod,
	@curWartoscBil_par=curWartoscBil,
	@curUmorzBil_par=curUmorzBil,
	@curStawkaPod_par=curStawkaPod,
	@curStawkaBil_par=curStawkaBil,
	@eMetAmPod_par=eMetAmPod,
	@eMetAmBil_par=eMetAmBil,
	@eStatus_par=eStatus,
	@nRokProd_par=nRokProd from n5srtrw where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5srtrw_insert')
	drop procedure n5srtrw_insert
go

create procedure n5srtrw_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNumEwid_par varchar(64),@strNumSer_par varchar(64),@strKRST_par varchar(64),@pGrupa_par integer,@dDataGwar_par datetime,@eRodzaj_par integer,@pPracownik_par integer,@strUwagi_par varchar(255),@pMUJO_par integer,@nLicznik_par integer,@curWartoscPod_par decimal(12,2),@curUmorzPod_par decimal(12,2),@curWartoscBil_par decimal(12,2),@curUmorzBil_par decimal(12,2),@curStawkaPod_par decimal(12,2),@curStawkaBil_par decimal(12,2),@eMetAmPod_par integer,@eMetAmBil_par integer,@eStatus_par integer,@nRokProd_par integer) with encryption as 
	insert into n5srtrw values(@idobj_par,@versionid_par,@strNazwa_par,@strNumEwid_par,@strNumSer_par,@strKRST_par,@pGrupa_par,@dDataGwar_par,@eRodzaj_par,@pPracownik_par,@strUwagi_par,@pMUJO_par,@nLicznik_par,@curWartoscPod_par,@curUmorzPod_par,@curWartoscBil_par,@curUmorzBil_par,@curStawkaPod_par,@curStawkaBil_par,@eMetAmPod_par,@eMetAmBil_par,@eStatus_par,@nRokProd_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5srtrw_update')
	drop procedure n5srtrw_update
go

create procedure n5srtrw_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNumEwid_par varchar(64),@strNumSer_par varchar(64),@strKRST_par varchar(64),@pGrupa_par integer,@dDataGwar_par datetime,@eRodzaj_par integer,@pPracownik_par integer,@strUwagi_par varchar(255),@pMUJO_par integer,@nLicznik_par integer,@curWartoscPod_par decimal(12,2),@curUmorzPod_par decimal(12,2),@curWartoscBil_par decimal(12,2),@curUmorzBil_par decimal(12,2),@curStawkaPod_par decimal(12,2),@curStawkaBil_par decimal(12,2),@eMetAmPod_par integer,@eMetAmBil_par integer,@eStatus_par integer,@nRokProd_par integer) with encryption as 
	update n5srtrw set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strNumEwid=@strNumEwid_par,
	strNumSer=@strNumSer_par,
	strKRST=@strKRST_par,
	pGrupa=@pGrupa_par,
	dDataGwar=@dDataGwar_par,
	eRodzaj=@eRodzaj_par,
	pPracownik=@pPracownik_par,
	strUwagi=@strUwagi_par,
	pMUJO=@pMUJO_par,
	nLicznik=@nLicznik_par,
	curWartoscPod=@curWartoscPod_par,
	curUmorzPod=@curUmorzPod_par,
	curWartoscBil=@curWartoscBil_par,
	curUmorzBil=@curUmorzBil_par,
	curStawkaPod=@curStawkaPod_par,
	curStawkaBil=@curStawkaBil_par,
	eMetAmPod=@eMetAmPod_par,
	eMetAmBil=@eMetAmBil_par,
	eStatus=@eStatus_par,
	nRokProd=@nRokProd_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5srtrw_delete')
	drop procedure n5srtrw_delete
go

create procedure n5srtrw_delete(@idobj_par integer) with encryption as 
	delete from n5srtrw where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5srtrw_maxid')
	drop procedure n5srtrw_maxid
go

create procedure n5srtrw_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5srtrw
go

if exists (select * from sysobjects where name='n5srtrw_candel')
	drop procedure n5srtrw_candel
go

create procedure n5srtrw_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pSRTRW=@idobj_par
go

-- table: n5opmag
if exists (select * from sysobjects where name='n5opmag_select')
	drop procedure n5opmag_select
go

create procedure n5opmag_select(@idobj_par integer,@versionid_par integer output,
	@nNumerOp_par integer output,
	@nLP_par integer output,
	@curIloscZrod_par decimal(14,4) output,
	@curCenaZrod_par decimal(14,4) output,
	@pProdZrod_par integer output,
	@pOpakZrod_par integer output,
	@pMagZrod_par integer output,
	@curIloscDocel_par decimal(14,4) output,
	@curWspZmianyCeny_par decimal(14,4) output,
	@pProdDocel_par integer output,
	@pOpakDocel_par integer output,
	@pMagDocel_par integer output,
	@nNumOpMagDost_par integer output,
	@nLpDost_par integer output,
	@eTypPow_par integer output,
	@dDataWazn_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@nNumerOp_par=nNumerOp,
	@nLP_par=nLP,
	@curIloscZrod_par=curIloscZrod,
	@curCenaZrod_par=curCenaZrod,
	@pProdZrod_par=pProdZrod,
	@pOpakZrod_par=pOpakZrod,
	@pMagZrod_par=pMagZrod,
	@curIloscDocel_par=curIloscDocel,
	@curWspZmianyCeny_par=curWspZmianyCeny,
	@pProdDocel_par=pProdDocel,
	@pOpakDocel_par=pOpakDocel,
	@pMagDocel_par=pMagDocel,
	@nNumOpMagDost_par=nNumOpMagDost,
	@nLpDost_par=nLpDost,
	@eTypPow_par=eTypPow,
	@dDataWazn_par=dDataWazn from n5opmag where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opmag_insert')
	drop procedure n5opmag_insert
go

create procedure n5opmag_insert(@idobj_par integer,@versionid_par integer,@nNumerOp_par integer,@nLP_par integer,@curIloscZrod_par decimal(14,4),@curCenaZrod_par decimal(14,4),@pProdZrod_par integer,@pOpakZrod_par integer,@pMagZrod_par integer,@curIloscDocel_par decimal(14,4),@curWspZmianyCeny_par decimal(14,4),@pProdDocel_par integer,@pOpakDocel_par integer,@pMagDocel_par integer,@nNumOpMagDost_par integer,@nLpDost_par integer,@eTypPow_par integer,@dDataWazn_par datetime) with encryption as 
	insert into n5opmag values(@idobj_par,@versionid_par,@nNumerOp_par,@nLP_par,@curIloscZrod_par,@curCenaZrod_par,@pProdZrod_par,@pOpakZrod_par,@pMagZrod_par,@curIloscDocel_par,@curWspZmianyCeny_par,@pProdDocel_par,@pOpakDocel_par,@pMagDocel_par,@nNumOpMagDost_par,@nLpDost_par,@eTypPow_par,@dDataWazn_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5opmag_update')
	drop procedure n5opmag_update
go

create procedure n5opmag_update(@idobj_par integer,@versionid_par integer,@nNumerOp_par integer,@nLP_par integer,@curIloscZrod_par decimal(14,4),@curCenaZrod_par decimal(14,4),@pProdZrod_par integer,@pOpakZrod_par integer,@pMagZrod_par integer,@curIloscDocel_par decimal(14,4),@curWspZmianyCeny_par decimal(14,4),@pProdDocel_par integer,@pOpakDocel_par integer,@pMagDocel_par integer,@nNumOpMagDost_par integer,@nLpDost_par integer,@eTypPow_par integer,@dDataWazn_par datetime) with encryption as 
	update n5opmag set VersionId=@versionid_par,
	nNumerOp=@nNumerOp_par,
	nLP=@nLP_par,
	curIloscZrod=@curIloscZrod_par,
	curCenaZrod=@curCenaZrod_par,
	pProdZrod=@pProdZrod_par,
	pOpakZrod=@pOpakZrod_par,
	pMagZrod=@pMagZrod_par,
	curIloscDocel=@curIloscDocel_par,
	curWspZmianyCeny=@curWspZmianyCeny_par,
	pProdDocel=@pProdDocel_par,
	pOpakDocel=@pOpakDocel_par,
	pMagDocel=@pMagDocel_par,
	nNumOpMagDost=@nNumOpMagDost_par,
	nLpDost=@nLpDost_par,
	eTypPow=@eTypPow_par,
	dDataWazn=@dDataWazn_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opmag_delete')
	drop procedure n5opmag_delete
go

create procedure n5opmag_delete(@idobj_par integer) with encryption as 
	delete from n5opmag where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opmag_maxid')
	drop procedure n5opmag_maxid
go

create procedure n5opmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5opmag
go

if exists (select * from sysobjects where name='n5opmag_candel')
	drop procedure n5opmag_candel
go

create procedure n5opmag_candel(@idobj_par integer) with encryption as 
go

-- table: n5koropmag
if exists (select * from sysobjects where name='n5koropmag_select')
	drop procedure n5koropmag_select
go

create procedure n5koropmag_select(@idobj_par integer,@versionid_par integer output,
	@nNumerOp_par integer output,
	@nLP_par integer output,
	@curIloscZrod_par decimal(14,4) output,
	@curCenaZrod_par decimal(14,4) output,
	@pProdZrod_par integer output,
	@pOpakZrod_par integer output,
	@pMagZrod_par integer output,
	@curIloscDocel_par decimal(14,4) output,
	@curWspZmianyCeny_par decimal(14,4) output,
	@pProdDocel_par integer output,
	@pOpakDocel_par integer output,
	@pMagDocel_par integer output,
	@nNumOpMagDost_par integer output,
	@nLpDost_par integer output,
	@eTypPow_par integer output,
	@dDataWazn_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@nNumerOp_par=nNumerOp,
	@nLP_par=nLP,
	@curIloscZrod_par=curIloscZrod,
	@curCenaZrod_par=curCenaZrod,
	@pProdZrod_par=pProdZrod,
	@pOpakZrod_par=pOpakZrod,
	@pMagZrod_par=pMagZrod,
	@curIloscDocel_par=curIloscDocel,
	@curWspZmianyCeny_par=curWspZmianyCeny,
	@pProdDocel_par=pProdDocel,
	@pOpakDocel_par=pOpakDocel,
	@pMagDocel_par=pMagDocel,
	@nNumOpMagDost_par=nNumOpMagDost,
	@nLpDost_par=nLpDost,
	@eTypPow_par=eTypPow,
	@dDataWazn_par=dDataWazn from n5koropmag where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5koropmag_insert')
	drop procedure n5koropmag_insert
go

create procedure n5koropmag_insert(@idobj_par integer,@versionid_par integer,@nNumerOp_par integer,@nLP_par integer,@curIloscZrod_par decimal(14,4),@curCenaZrod_par decimal(14,4),@pProdZrod_par integer,@pOpakZrod_par integer,@pMagZrod_par integer,@curIloscDocel_par decimal(14,4),@curWspZmianyCeny_par decimal(14,4),@pProdDocel_par integer,@pOpakDocel_par integer,@pMagDocel_par integer,@nNumOpMagDost_par integer,@nLpDost_par integer,@eTypPow_par integer,@dDataWazn_par datetime) with encryption as 
	insert into n5koropmag values(@idobj_par,@versionid_par,@nNumerOp_par,@nLP_par,@curIloscZrod_par,@curCenaZrod_par,@pProdZrod_par,@pOpakZrod_par,@pMagZrod_par,@curIloscDocel_par,@curWspZmianyCeny_par,@pProdDocel_par,@pOpakDocel_par,@pMagDocel_par,@nNumOpMagDost_par,@nLpDost_par,@eTypPow_par,@dDataWazn_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5koropmag_update')
	drop procedure n5koropmag_update
go

create procedure n5koropmag_update(@idobj_par integer,@versionid_par integer,@nNumerOp_par integer,@nLP_par integer,@curIloscZrod_par decimal(14,4),@curCenaZrod_par decimal(14,4),@pProdZrod_par integer,@pOpakZrod_par integer,@pMagZrod_par integer,@curIloscDocel_par decimal(14,4),@curWspZmianyCeny_par decimal(14,4),@pProdDocel_par integer,@pOpakDocel_par integer,@pMagDocel_par integer,@nNumOpMagDost_par integer,@nLpDost_par integer,@eTypPow_par integer,@dDataWazn_par datetime) with encryption as 
	update n5koropmag set VersionId=@versionid_par,
	nNumerOp=@nNumerOp_par,
	nLP=@nLP_par,
	curIloscZrod=@curIloscZrod_par,
	curCenaZrod=@curCenaZrod_par,
	pProdZrod=@pProdZrod_par,
	pOpakZrod=@pOpakZrod_par,
	pMagZrod=@pMagZrod_par,
	curIloscDocel=@curIloscDocel_par,
	curWspZmianyCeny=@curWspZmianyCeny_par,
	pProdDocel=@pProdDocel_par,
	pOpakDocel=@pOpakDocel_par,
	pMagDocel=@pMagDocel_par,
	nNumOpMagDost=@nNumOpMagDost_par,
	nLpDost=@nLpDost_par,
	eTypPow=@eTypPow_par,
	dDataWazn=@dDataWazn_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5koropmag_delete')
	drop procedure n5koropmag_delete
go

create procedure n5koropmag_delete(@idobj_par integer) with encryption as 
	delete from n5koropmag where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5koropmag_maxid')
	drop procedure n5koropmag_maxid
go

create procedure n5koropmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5koropmag
go

if exists (select * from sysobjects where name='n5koropmag_candel')
	drop procedure n5koropmag_candel
go

create procedure n5koropmag_candel(@idobj_par integer) with encryption as 
go

-- table: n5stanmag
if exists (select * from sysobjects where name='n5stanmag_select')
	drop procedure n5stanmag_select
go

create procedure n5stanmag_select(@idobj_par integer,@versionid_par integer output,
	@pMagazyn_par integer output,
	@pProdukt_par integer output,
	@pOpak_par integer output,
	@curCena_par decimal(14,4) output,
	@curIloscOpak_par decimal(14,4) output,
	@nNumOpMag_par integer output,
	@nLP_par integer output,
	@dDataWazn_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@pMagazyn_par=pMagazyn,
	@pProdukt_par=pProdukt,
	@pOpak_par=pOpak,
	@curCena_par=curCena,
	@curIloscOpak_par=curIloscOpak,
	@nNumOpMag_par=nNumOpMag,
	@nLP_par=nLP,
	@dDataWazn_par=dDataWazn from n5stanmag where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5stanmag_insert')
	drop procedure n5stanmag_insert
go

create procedure n5stanmag_insert(@idobj_par integer,@versionid_par integer,@pMagazyn_par integer,@pProdukt_par integer,@pOpak_par integer,@curCena_par decimal(14,4),@curIloscOpak_par decimal(14,4),@nNumOpMag_par integer,@nLP_par integer,@dDataWazn_par datetime) with encryption as 
	insert into n5stanmag values(@idobj_par,@versionid_par,@pMagazyn_par,@pProdukt_par,@pOpak_par,@curCena_par,@curIloscOpak_par,@nNumOpMag_par,@nLP_par,@dDataWazn_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5stanmag_update')
	drop procedure n5stanmag_update
go

create procedure n5stanmag_update(@idobj_par integer,@versionid_par integer,@pMagazyn_par integer,@pProdukt_par integer,@pOpak_par integer,@curCena_par decimal(14,4),@curIloscOpak_par decimal(14,4),@nNumOpMag_par integer,@nLP_par integer,@dDataWazn_par datetime) with encryption as 
	update n5stanmag set VersionId=@versionid_par,
	pMagazyn=@pMagazyn_par,
	pProdukt=@pProdukt_par,
	pOpak=@pOpak_par,
	curCena=@curCena_par,
	curIloscOpak=@curIloscOpak_par,
	nNumOpMag=@nNumOpMag_par,
	nLP=@nLP_par,
	dDataWazn=@dDataWazn_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5stanmag_delete')
	drop procedure n5stanmag_delete
go

create procedure n5stanmag_delete(@idobj_par integer) with encryption as 
	delete from n5stanmag where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5stanmag_maxid')
	drop procedure n5stanmag_maxid
go

create procedure n5stanmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5stanmag
go

if exists (select * from sysobjects where name='n5stanmag_candel')
	drop procedure n5stanmag_candel
go

create procedure n5stanmag_candel(@idobj_par integer) with encryption as 
go

-- table: n5pozrecepta
if exists (select * from sysobjects where name='n5pozrecepta_select')
	drop procedure n5pozrecepta_select
go

create procedure n5pozrecepta_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@pOpak_par integer output,
	@curIloscOpak_par decimal(14,4) output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@pOpak_par=pOpak,
	@curIloscOpak_par=curIloscOpak from n5pozrecepta where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrecepta_insert')
	drop procedure n5pozrecepta_insert
go

create procedure n5pozrecepta_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@curIloscOpak_par decimal(14,4)) with encryption as 
	insert into n5pozrecepta values(@idobj_par,@versionid_par,@pProdukt_par,@pOpak_par,@curIloscOpak_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrecepta_update')
	drop procedure n5pozrecepta_update
go

create procedure n5pozrecepta_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@curIloscOpak_par decimal(14,4)) with encryption as 
	update n5pozrecepta set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	pOpak=@pOpak_par,
	curIloscOpak=@curIloscOpak_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrecepta_delete')
	drop procedure n5pozrecepta_delete
go

create procedure n5pozrecepta_delete(@idobj_par integer) with encryption as 
	delete from n5pozrecepta where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrecepta_maxid')
	drop procedure n5pozrecepta_maxid
go

create procedure n5pozrecepta_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozrecepta
go

if exists (select * from sysobjects where name='n5pozrecepta_candel')
	drop procedure n5pozrecepta_candel
go

create procedure n5pozrecepta_candel(@idobj_par integer) with encryption as 
go

-- table: n5recepta
if exists (select * from sysobjects where name='n5recepta_select')
	drop procedure n5recepta_select
go

create procedure n5recepta_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@strNorma_par varchar(64) output,
	@strOpis_par varchar(1024) output,
	@pWyrob_par integer output,
	@pWyrOpak_par integer output,
	@curIloscOpak_par decimal(14,4) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strNorma_par=strNorma,
	@strOpis_par=strOpis,
	@pWyrob_par=pWyrob,
	@pWyrOpak_par=pWyrOpak,
	@curIloscOpak_par=curIloscOpak from n5recepta where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5recepta_insert')
	drop procedure n5recepta_insert
go

create procedure n5recepta_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNorma_par varchar(64),@strOpis_par varchar(1024),@pWyrob_par integer,@pWyrOpak_par integer,@curIloscOpak_par decimal(14,4)) with encryption as 
	insert into n5recepta values(@idobj_par,@versionid_par,@strNazwa_par,@strNorma_par,@strOpis_par,@pWyrob_par,@pWyrOpak_par,@curIloscOpak_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5recepta_update')
	drop procedure n5recepta_update
go

create procedure n5recepta_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strNorma_par varchar(64),@strOpis_par varchar(1024),@pWyrob_par integer,@pWyrOpak_par integer,@curIloscOpak_par decimal(14,4)) with encryption as 
	update n5recepta set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strNorma=@strNorma_par,
	strOpis=@strOpis_par,
	pWyrob=@pWyrob_par,
	pWyrOpak=@pWyrOpak_par,
	curIloscOpak=@curIloscOpak_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5recepta_delete')
	drop procedure n5recepta_delete
go

create procedure n5recepta_delete(@idobj_par integer) with encryption as 
	delete from n5recepta where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5recepta_maxid')
	drop procedure n5recepta_maxid
go

create procedure n5recepta_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5recepta
go

if exists (select * from sysobjects where name='n5recepta_candel')
	drop procedure n5recepta_candel
go

create procedure n5recepta_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pRecepta=@idobj_par
go

-- table: n5pozzlecprod
if exists (select * from sysobjects where name='n5pozzlecprod_select')
	drop procedure n5pozzlecprod_select
go

create procedure n5pozzlecprod_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@pOpak_par integer output,
	@pRecepta_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@pOpak_par=pOpak,
	@pRecepta_par=pRecepta,
	@curIloscOpak_par=curIloscOpak,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5pozzlecprod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzlecprod_insert')
	drop procedure n5pozzlecprod_insert
go

create procedure n5pozzlecprod_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@pRecepta_par integer,@curIloscOpak_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozzlecprod values(@idobj_par,@versionid_par,@pProdukt_par,@pOpak_par,@pRecepta_par,@curIloscOpak_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzlecprod_update')
	drop procedure n5pozzlecprod_update
go

create procedure n5pozzlecprod_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@pRecepta_par integer,@curIloscOpak_par decimal(14,4),@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5pozzlecprod set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	pOpak=@pOpak_par,
	pRecepta=@pRecepta_par,
	curIloscOpak=@curIloscOpak_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzlecprod_delete')
	drop procedure n5pozzlecprod_delete
go

create procedure n5pozzlecprod_delete(@idobj_par integer) with encryption as 
	delete from n5pozzlecprod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozzlecprod_maxid')
	drop procedure n5pozzlecprod_maxid
go

create procedure n5pozzlecprod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozzlecprod
go

if exists (select * from sysobjects where name='n5pozzlecprod_candel')
	drop procedure n5pozzlecprod_candel
go

create procedure n5pozzlecprod_candel(@idobj_par integer) with encryption as 
go

-- table: n5zlecprod
if exists (select * from sysobjects where name='n5zlecprod_select')
	drop procedure n5zlecprod_select
go

create procedure n5zlecprod_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@dDataWyst_par datetime output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@pZadanie_par integer output,
	@pKlient_par integer output,
	@pKlient_JO_par integer output,
	@pZamowienie_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@dDataWyst_par=dDataWyst,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@pZadanie_par=pZadanie,
	@pKlient_par=pKlient,
	@pKlient_JO_par=pKlient_JO,
	@pZamowienie_par=pZamowienie,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5zlecprod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zlecprod_insert')
	drop procedure n5zlecprod_insert
go

create procedure n5zlecprod_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@pUzytRej_par integer,@strUwagi_par varchar(512),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pZadanie_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pZamowienie_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5zlecprod values(@idobj_par,@versionid_par,@strNrDok_par,@dDataWyst_par,@pUzytRej_par,@strUwagi_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@pZadanie_par,@pKlient_par,@pKlient_JO_par,@pZamowienie_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5zlecprod_update')
	drop procedure n5zlecprod_update
go

create procedure n5zlecprod_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@pUzytRej_par integer,@strUwagi_par varchar(512),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pZadanie_par integer,@pKlient_par integer,@pKlient_JO_par integer,@pZamowienie_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5zlecprod set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	dDataWyst=@dDataWyst_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	pZadanie=@pZadanie_par,
	pKlient=@pKlient_par,
	pKlient_JO=@pKlient_JO_par,
	pZamowienie=@pZamowienie_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zlecprod_delete')
	drop procedure n5zlecprod_delete
go

create procedure n5zlecprod_delete(@idobj_par integer) with encryption as 
	delete from n5zlecprod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5zlecprod_maxid')
	drop procedure n5zlecprod_maxid
go

create procedure n5zlecprod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5zlecprod
go

if exists (select * from sysobjects where name='n5zlecprod_candel')
	drop procedure n5zlecprod_candel
go

create procedure n5zlecprod_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10187
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where wrefDokHandl=@idobj_par and wrefDokHandl_wrt=10187
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pZlecProd=@idobj_par
go

-- table: n5eventlog
if exists (select * from sysobjects where name='n5eventlog_select')
	drop procedure n5eventlog_select
go

create procedure n5eventlog_select(@idobj_par integer,@versionid_par integer output,
	@eTyp_par integer output,
	@dDataZdarz_par datetime output,
	@tCzasZdarz_par integer output,
	@pUser_par integer output,
	@strOpis_par varchar(7900) output) with encryption as 
	select @versionid_par=VersionId,
	@eTyp_par=eTyp,
	@dDataZdarz_par=dDataZdarz,
	@tCzasZdarz_par=tCzasZdarz,
	@pUser_par=pUser,
	@strOpis_par=strOpis from n5eventlog where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5eventlog_insert')
	drop procedure n5eventlog_insert
go

create procedure n5eventlog_insert(@idobj_par integer,@versionid_par integer,@eTyp_par integer,@dDataZdarz_par datetime,@tCzasZdarz_par integer,@pUser_par integer,@strOpis_par varchar(7900)) with encryption as 
	insert into n5eventlog values(@idobj_par,@versionid_par,@eTyp_par,@dDataZdarz_par,@tCzasZdarz_par,@pUser_par,@strOpis_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5eventlog_update')
	drop procedure n5eventlog_update
go

create procedure n5eventlog_update(@idobj_par integer,@versionid_par integer,@eTyp_par integer,@dDataZdarz_par datetime,@tCzasZdarz_par integer,@pUser_par integer,@strOpis_par varchar(7900)) with encryption as 
	update n5eventlog set VersionId=@versionid_par,
	eTyp=@eTyp_par,
	dDataZdarz=@dDataZdarz_par,
	tCzasZdarz=@tCzasZdarz_par,
	pUser=@pUser_par,
	strOpis=@strOpis_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5eventlog_delete')
	drop procedure n5eventlog_delete
go

create procedure n5eventlog_delete(@idobj_par integer) with encryption as 
	delete from n5eventlog where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5eventlog_maxid')
	drop procedure n5eventlog_maxid
go

create procedure n5eventlog_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5eventlog
go

if exists (select * from sysobjects where name='n5eventlog_candel')
	drop procedure n5eventlog_candel
go

create procedure n5eventlog_candel(@idobj_par integer) with encryption as 
go

-- table: n5polrab
if exists (select * from sysobjects where name='n5polrab_select')
	drop procedure n5polrab_select
go

create procedure n5polrab_select(@idobj_par integer,@versionid_par integer output,
	@wpProdGrupa_par integer output,
	@wpProdGrupa_wrt_par integer output,
	@pOpak_par integer output,
	@wpKlientGrupa_par integer output,
	@wpKlientGrupa_wrt_par integer output,
	@nPriorytet_par integer output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@strNazwaPromocji_par varchar(128) output,
	@curCenaRab_par decimal(14,4) output,
	@eTyp_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wpProdGrupa_par=wpProdGrupa,
	@wpProdGrupa_wrt_par=wpProdGrupa_wrt,
	@pOpak_par=pOpak,
	@wpKlientGrupa_par=wpKlientGrupa,
	@wpKlientGrupa_wrt_par=wpKlientGrupa_wrt,
	@nPriorytet_par=nPriorytet,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@strNazwaPromocji_par=strNazwaPromocji,
	@curCenaRab_par=curCenaRab,
	@eTyp_par=eTyp from n5polrab where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5polrab_insert')
	drop procedure n5polrab_insert
go

create procedure n5polrab_insert(@idobj_par integer,@versionid_par integer,@wpProdGrupa_par integer,@wpProdGrupa_wrt_par integer,@pOpak_par integer,@wpKlientGrupa_par integer,@wpKlientGrupa_wrt_par integer,@nPriorytet_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@strNazwaPromocji_par varchar(128),@curCenaRab_par decimal(14,4),@eTyp_par integer) with encryption as 
	insert into n5polrab values(@idobj_par,@versionid_par,@wpProdGrupa_par,@wpProdGrupa_wrt_par,@pOpak_par,@wpKlientGrupa_par,@wpKlientGrupa_wrt_par,@nPriorytet_par,@dDataOd_par,@dDataDo_par,@strNazwaPromocji_par,@curCenaRab_par,@eTyp_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5polrab_update')
	drop procedure n5polrab_update
go

create procedure n5polrab_update(@idobj_par integer,@versionid_par integer,@wpProdGrupa_par integer,@wpProdGrupa_wrt_par integer,@pOpak_par integer,@wpKlientGrupa_par integer,@wpKlientGrupa_wrt_par integer,@nPriorytet_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@strNazwaPromocji_par varchar(128),@curCenaRab_par decimal(14,4),@eTyp_par integer) with encryption as 
	update n5polrab set VersionId=@versionid_par,
	wpProdGrupa=@wpProdGrupa_par,
	wpProdGrupa_wrt=@wpProdGrupa_wrt_par,
	pOpak=@pOpak_par,
	wpKlientGrupa=@wpKlientGrupa_par,
	wpKlientGrupa_wrt=@wpKlientGrupa_wrt_par,
	nPriorytet=@nPriorytet_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	strNazwaPromocji=@strNazwaPromocji_par,
	curCenaRab=@curCenaRab_par,
	eTyp=@eTyp_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5polrab_delete')
	drop procedure n5polrab_delete
go

create procedure n5polrab_delete(@idobj_par integer) with encryption as 
	delete from n5polrab where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5polrab_maxid')
	drop procedure n5polrab_maxid
go

create procedure n5polrab_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5polrab
go

if exists (select * from sysobjects where name='n5polrab_candel')
	drop procedure n5polrab_candel
go

create procedure n5polrab_candel(@idobj_par integer) with encryption as 
go

-- table: n5plschematnal
if exists (select * from sysobjects where name='n5plschematnal_select')
	drop procedure n5plschematnal_select
go

create procedure n5plschematnal_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@strOpis_par varchar(1024) output,
	@strVBcode_par varchar(7900) output,
	@nPriorytet_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strOpis_par=strOpis,
	@strVBcode_par=strVBcode,
	@nPriorytet_par=nPriorytet from n5plschematnal where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plschematnal_insert')
	drop procedure n5plschematnal_insert
go

create procedure n5plschematnal_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strOpis_par varchar(1024),@strVBcode_par varchar(7900),@nPriorytet_par integer) with encryption as 
	insert into n5plschematnal values(@idobj_par,@versionid_par,@strNazwa_par,@strOpis_par,@strVBcode_par,@nPriorytet_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plschematnal_update')
	drop procedure n5plschematnal_update
go

create procedure n5plschematnal_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@strOpis_par varchar(1024),@strVBcode_par varchar(7900),@nPriorytet_par integer) with encryption as 
	update n5plschematnal set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strOpis=@strOpis_par,
	strVBcode=@strVBcode_par,
	nPriorytet=@nPriorytet_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plschematnal_delete')
	drop procedure n5plschematnal_delete
go

create procedure n5plschematnal_delete(@idobj_par integer) with encryption as 
	delete from n5plschematnal where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plschematnal_maxid')
	drop procedure n5plschematnal_maxid
go

create procedure n5plschematnal_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plschematnal
go

if exists (select * from sysobjects where name='n5plschematnal_candel')
	drop procedure n5plschematnal_candel
go

create procedure n5plschematnal_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10193 as integer),idobj from n5plsklnal where pSchemat=@idobj_par
union
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where pSchematNal=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pSchemat=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pSchemat=@idobj_par
union
select TOP 5 'typeid'=cast(10220 as integer),idobj from n5plsklumowy where pSchemat=@idobj_par
go

-- table: n5plstawka
if exists (select * from sysobjects where name='n5plstawka_select')
	drop procedure n5plstawka_select
go

create procedure n5plstawka_select(@idobj_par integer,@versionid_par integer output,
	@strKod_par varchar(8) output,
	@strOpis_par varchar(1024) output,
	@curWartosc_par decimal(14,4) output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@pJednostka_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strKod_par=strKod,
	@strOpis_par=strOpis,
	@curWartosc_par=curWartosc,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@pJednostka_par=pJednostka from n5plstawka where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plstawka_insert')
	drop procedure n5plstawka_insert
go

create procedure n5plstawka_insert(@idobj_par integer,@versionid_par integer,@strKod_par varchar(8),@strOpis_par varchar(1024),@curWartosc_par decimal(14,4),@dDataOd_par datetime,@dDataDo_par datetime,@pJednostka_par integer) with encryption as 
	insert into n5plstawka values(@idobj_par,@versionid_par,@strKod_par,@strOpis_par,@curWartosc_par,@dDataOd_par,@dDataDo_par,@pJednostka_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plstawka_update')
	drop procedure n5plstawka_update
go

create procedure n5plstawka_update(@idobj_par integer,@versionid_par integer,@strKod_par varchar(8),@strOpis_par varchar(1024),@curWartosc_par decimal(14,4),@dDataOd_par datetime,@dDataDo_par datetime,@pJednostka_par integer) with encryption as 
	update n5plstawka set VersionId=@versionid_par,
	strKod=@strKod_par,
	strOpis=@strOpis_par,
	curWartosc=@curWartosc_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	pJednostka=@pJednostka_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plstawka_delete')
	drop procedure n5plstawka_delete
go

create procedure n5plstawka_delete(@idobj_par integer) with encryption as 
	delete from n5plstawka where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plstawka_maxid')
	drop procedure n5plstawka_maxid
go

create procedure n5plstawka_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plstawka
go

if exists (select * from sysobjects where name='n5plstawka_candel')
	drop procedure n5plstawka_candel
go

create procedure n5plstawka_candel(@idobj_par integer) with encryption as 
go

-- table: n5plnaliczenie
if exists (select * from sysobjects where name='n5plnaliczenie_select')
	drop procedure n5plnaliczenie_select
go

create procedure n5plnaliczenie_select(@idobj_par integer,@versionid_par integer output,
	@pPracownik_par integer output,
	@dDataRej_par datetime output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@pUzytRej_par integer output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@pListaPlac_par integer output,
	@pTransakcja_par integer output,
	@pZadanie_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pPracownik_par=pPracownik,
	@dDataRej_par=dDataRej,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@pUzytRej_par=pUzytRej,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@pListaPlac_par=pListaPlac,
	@pTransakcja_par=pTransakcja,
	@pZadanie_par=pZadanie from n5plnaliczenie where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnaliczenie_insert')
	drop procedure n5plnaliczenie_insert
go

create procedure n5plnaliczenie_insert(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pListaPlac_par integer,@pTransakcja_par integer,@pZadanie_par integer) with encryption as 
	insert into n5plnaliczenie values(@idobj_par,@versionid_par,@pPracownik_par,@dDataRej_par,@dDataOd_par,@dDataDo_par,@pUzytRej_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@pListaPlac_par,@pTransakcja_par,@pZadanie_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnaliczenie_update')
	drop procedure n5plnaliczenie_update
go

create procedure n5plnaliczenie_update(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@pListaPlac_par integer,@pTransakcja_par integer,@pZadanie_par integer) with encryption as 
	update n5plnaliczenie set VersionId=@versionid_par,
	pPracownik=@pPracownik_par,
	dDataRej=@dDataRej_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	pUzytRej=@pUzytRej_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	pListaPlac=@pListaPlac_par,
	pTransakcja=@pTransakcja_par,
	pZadanie=@pZadanie_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnaliczenie_delete')
	drop procedure n5plnaliczenie_delete
go

create procedure n5plnaliczenie_delete(@idobj_par integer) with encryption as 
	delete from n5plnaliczenie where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnaliczenie_maxid')
	drop procedure n5plnaliczenie_maxid
go

create procedure n5plnaliczenie_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plnaliczenie
go

if exists (select * from sysobjects where name='n5plnaliczenie_candel')
	drop procedure n5plnaliczenie_candel
go

create procedure n5plnaliczenie_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10192
union
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where pNaliczenie=@idobj_par
go

-- table: n5plsklnal
if exists (select * from sysobjects where name='n5plsklnal_select')
	drop procedure n5plsklnal_select
go

create procedure n5plsklnal_select(@idobj_par integer,@versionid_par integer output,
	@pSchemat_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pSchemat_par=pSchemat from n5plsklnal where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnal_insert')
	drop procedure n5plsklnal_insert
go

create procedure n5plsklnal_insert(@idobj_par integer,@versionid_par integer,@pSchemat_par integer) with encryption as 
	insert into n5plsklnal values(@idobj_par,@versionid_par,@pSchemat_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnal_update')
	drop procedure n5plsklnal_update
go

create procedure n5plsklnal_update(@idobj_par integer,@versionid_par integer,@pSchemat_par integer) with encryption as 
	update n5plsklnal set VersionId=@versionid_par,
	pSchemat=@pSchemat_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnal_delete')
	drop procedure n5plsklnal_delete
go

create procedure n5plsklnal_delete(@idobj_par integer) with encryption as 
	delete from n5plsklnal where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnal_maxid')
	drop procedure n5plsklnal_maxid
go

create procedure n5plsklnal_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plsklnal
go

if exists (select * from sysobjects where name='n5plsklnal_candel')
	drop procedure n5plsklnal_candel
go

create procedure n5plsklnal_candel(@idobj_par integer) with encryption as 
go

-- table: n5pllistaplac
if exists (select * from sysobjects where name='n5pllistaplac_select')
	drop procedure n5pllistaplac_select
go

create procedure n5pllistaplac_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok from n5pllistaplac where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pllistaplac_insert')
	drop procedure n5pllistaplac_insert
go

create procedure n5pllistaplac_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32)) with encryption as 
	insert into n5pllistaplac values(@idobj_par,@versionid_par,@strNrDok_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pllistaplac_update')
	drop procedure n5pllistaplac_update
go

create procedure n5pllistaplac_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32)) with encryption as 
	update n5pllistaplac set VersionId=@versionid_par,
	strNrDok=@strNrDok_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pllistaplac_delete')
	drop procedure n5pllistaplac_delete
go

create procedure n5pllistaplac_delete(@idobj_par integer) with encryption as 
	delete from n5pllistaplac where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pllistaplac_maxid')
	drop procedure n5pllistaplac_maxid
go

create procedure n5pllistaplac_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pllistaplac
go

if exists (select * from sysobjects where name='n5pllistaplac_candel')
	drop procedure n5pllistaplac_candel
go

create procedure n5pllistaplac_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pListaPlac=@idobj_par
union
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where pListaPlac=@idobj_par
go

-- table: n5plgrzas
if exists (select * from sysobjects where name='n5plgrzas_select')
	drop procedure n5plgrzas_select
go

create procedure n5plgrzas_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5plgrzas where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plgrzas_insert')
	drop procedure n5plgrzas_insert
go

create procedure n5plgrzas_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128)) with encryption as 
	insert into n5plgrzas values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plgrzas_update')
	drop procedure n5plgrzas_update
go

create procedure n5plgrzas_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128)) with encryption as 
	update n5plgrzas set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plgrzas_delete')
	drop procedure n5plgrzas_delete
go

create procedure n5plgrzas_delete(@idobj_par integer) with encryption as 
	delete from n5plgrzas where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plgrzas_maxid')
	drop procedure n5plgrzas_maxid
go

create procedure n5plgrzas_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plgrzas
go

if exists (select * from sysobjects where name='n5plgrzas_candel')
	drop procedure n5plgrzas_candel
go

create procedure n5plgrzas_candel(@idobj_par integer) with encryption as 
go

-- table: n5plsubkonto
if exists (select * from sysobjects where name='n5plsubkonto_select')
	drop procedure n5plsubkonto_select
go

create procedure n5plsubkonto_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@strKod_par varchar(8) output,
	@strOpis_par varchar(1024) output,
	@eAktywne_par integer output,
	@pJednostka_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strKod_par=strKod,
	@strOpis_par=strOpis,
	@eAktywne_par=eAktywne,
	@pJednostka_par=pJednostka from n5plsubkonto where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsubkonto_insert')
	drop procedure n5plsubkonto_insert
go

create procedure n5plsubkonto_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strKod_par varchar(8),@strOpis_par varchar(1024),@eAktywne_par integer,@pJednostka_par integer) with encryption as 
	insert into n5plsubkonto values(@idobj_par,@versionid_par,@strNazwa_par,@strKod_par,@strOpis_par,@eAktywne_par,@pJednostka_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsubkonto_update')
	drop procedure n5plsubkonto_update
go

create procedure n5plsubkonto_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@strKod_par varchar(8),@strOpis_par varchar(1024),@eAktywne_par integer,@pJednostka_par integer) with encryption as 
	update n5plsubkonto set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strKod=@strKod_par,
	strOpis=@strOpis_par,
	eAktywne=@eAktywne_par,
	pJednostka=@pJednostka_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsubkonto_delete')
	drop procedure n5plsubkonto_delete
go

create procedure n5plsubkonto_delete(@idobj_par integer) with encryption as 
	delete from n5plsubkonto where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsubkonto_maxid')
	drop procedure n5plsubkonto_maxid
go

create procedure n5plsubkonto_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plsubkonto
go

if exists (select * from sysobjects where name='n5plsubkonto_candel')
	drop procedure n5plsubkonto_candel
go

create procedure n5plsubkonto_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where pSubKonto=@idobj_par
go

-- table: n5pldekret
if exists (select * from sysobjects where name='n5pldekret_select')
	drop procedure n5pldekret_select
go

create procedure n5pldekret_select(@idobj_par integer,@versionid_par integer output,
	@pPracownik_par integer output,
	@pSubKonto_par integer output,
	@curWn_par decimal(14,4) output,
	@curMa_par decimal(14,4) output,
	@dDataKsieg_par datetime output,
	@pListaPlac_par integer output,
	@pNaliczenie_par integer output,
	@pSchematNal_par integer output,
	@wrefDokument_par integer output,
	@wrefDokument_wrt_par integer output,
	@strOpis_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@pPracownik_par=pPracownik,
	@pSubKonto_par=pSubKonto,
	@curWn_par=curWn,
	@curMa_par=curMa,
	@dDataKsieg_par=dDataKsieg,
	@pListaPlac_par=pListaPlac,
	@pNaliczenie_par=pNaliczenie,
	@pSchematNal_par=pSchematNal,
	@wrefDokument_par=wrefDokument,
	@wrefDokument_wrt_par=wrefDokument_wrt,
	@strOpis_par=strOpis from n5pldekret where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pldekret_insert')
	drop procedure n5pldekret_insert
go

create procedure n5pldekret_insert(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@pSubKonto_par integer,@curWn_par decimal(14,4),@curMa_par decimal(14,4),@dDataKsieg_par datetime,@pListaPlac_par integer,@pNaliczenie_par integer,@pSchematNal_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer,@strOpis_par varchar(64)) with encryption as 
	insert into n5pldekret values(@idobj_par,@versionid_par,@pPracownik_par,@pSubKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@pListaPlac_par,@pNaliczenie_par,@pSchematNal_par,@wrefDokument_par,@wrefDokument_wrt_par,@strOpis_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pldekret_update')
	drop procedure n5pldekret_update
go

create procedure n5pldekret_update(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@pSubKonto_par integer,@curWn_par decimal(14,4),@curMa_par decimal(14,4),@dDataKsieg_par datetime,@pListaPlac_par integer,@pNaliczenie_par integer,@pSchematNal_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer,@strOpis_par varchar(64)) with encryption as 
	update n5pldekret set VersionId=@versionid_par,
	pPracownik=@pPracownik_par,
	pSubKonto=@pSubKonto_par,
	curWn=@curWn_par,
	curMa=@curMa_par,
	dDataKsieg=@dDataKsieg_par,
	pListaPlac=@pListaPlac_par,
	pNaliczenie=@pNaliczenie_par,
	pSchematNal=@pSchematNal_par,
	wrefDokument=@wrefDokument_par,
	wrefDokument_wrt=@wrefDokument_wrt_par,
	strOpis=@strOpis_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pldekret_delete')
	drop procedure n5pldekret_delete
go

create procedure n5pldekret_delete(@idobj_par integer) with encryption as 
	delete from n5pldekret where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pldekret_maxid')
	drop procedure n5pldekret_maxid
go

create procedure n5pldekret_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pldekret
go

if exists (select * from sysobjects where name='n5pldekret_candel')
	drop procedure n5pldekret_candel
go

create procedure n5pldekret_candel(@idobj_par integer) with encryption as 
go

-- table: n5plumowa
if exists (select * from sysobjects where name='n5plumowa_select')
	drop procedure n5plumowa_select
go

create procedure n5plumowa_select(@idobj_par integer,@versionid_par integer output,
	@pPracownik_par integer output,
	@dDataRej_par datetime output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@pUzytRej_par integer output,
	@eTypUmowy_par integer output,
	@pUmowaPop_par integer output,
	@pKalendarz_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pPracownik_par=pPracownik,
	@dDataRej_par=dDataRej,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@pUzytRej_par=pUzytRej,
	@eTypUmowy_par=eTypUmowy,
	@pUmowaPop_par=pUmowaPop,
	@pKalendarz_par=pKalendarz from n5plumowa where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plumowa_insert')
	drop procedure n5plumowa_insert
go

create procedure n5plumowa_insert(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@eTypUmowy_par integer,@pUmowaPop_par integer,@pKalendarz_par integer) with encryption as 
	insert into n5plumowa values(@idobj_par,@versionid_par,@pPracownik_par,@dDataRej_par,@dDataOd_par,@dDataDo_par,@pUzytRej_par,@eTypUmowy_par,@pUmowaPop_par,@pKalendarz_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plumowa_update')
	drop procedure n5plumowa_update
go

create procedure n5plumowa_update(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@eTypUmowy_par integer,@pUmowaPop_par integer,@pKalendarz_par integer) with encryption as 
	update n5plumowa set VersionId=@versionid_par,
	pPracownik=@pPracownik_par,
	dDataRej=@dDataRej_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	pUzytRej=@pUzytRej_par,
	eTypUmowy=@eTypUmowy_par,
	pUmowaPop=@pUmowaPop_par,
	pKalendarz=@pKalendarz_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plumowa_delete')
	drop procedure n5plumowa_delete
go

create procedure n5plumowa_delete(@idobj_par integer) with encryption as 
	delete from n5plumowa where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plumowa_maxid')
	drop procedure n5plumowa_maxid
go

create procedure n5plumowa_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plumowa
go

if exists (select * from sysobjects where name='n5plumowa_candel')
	drop procedure n5plumowa_candel
go

create procedure n5plumowa_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where wrefDokument=@idobj_par and wrefDokument_wrt=10199
union
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pUmowaPop=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pUmowa=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pUmowa=@idobj_par
union
select TOP 5 'typeid'=cast(10221 as integer),idobj from n5plsklnalzrod where wrefDokument=@idobj_par and wrefDokument_wrt=10199
go

-- table: n5plchoroba
if exists (select * from sysobjects where name='n5plchoroba_select')
	drop procedure n5plchoroba_select
go

create procedure n5plchoroba_select(@idobj_par integer,@versionid_par integer output,
	@pPracownik_par integer output,
	@dDataRej_par datetime output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@pUzytRej_par integer output,
	@pUmowa_par integer output,
	@pSchemat_par integer output,
	@strNumZwol_par varchar(8) output,
	@strKodStat_par varchar(4) output,
	@strKodPlatnik_par varchar(4) output) with encryption as 
	select @versionid_par=VersionId,
	@pPracownik_par=pPracownik,
	@dDataRej_par=dDataRej,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@pUzytRej_par=pUzytRej,
	@pUmowa_par=pUmowa,
	@pSchemat_par=pSchemat,
	@strNumZwol_par=strNumZwol,
	@strKodStat_par=strKodStat,
	@strKodPlatnik_par=strKodPlatnik from n5plchoroba where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plchoroba_insert')
	drop procedure n5plchoroba_insert
go

create procedure n5plchoroba_insert(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pUmowa_par integer,@pSchemat_par integer,@strNumZwol_par varchar(8),@strKodStat_par varchar(4),@strKodPlatnik_par varchar(4)) with encryption as 
	insert into n5plchoroba values(@idobj_par,@versionid_par,@pPracownik_par,@dDataRej_par,@dDataOd_par,@dDataDo_par,@pUzytRej_par,@pUmowa_par,@pSchemat_par,@strNumZwol_par,@strKodStat_par,@strKodPlatnik_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plchoroba_update')
	drop procedure n5plchoroba_update
go

create procedure n5plchoroba_update(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pUmowa_par integer,@pSchemat_par integer,@strNumZwol_par varchar(8),@strKodStat_par varchar(4),@strKodPlatnik_par varchar(4)) with encryption as 
	update n5plchoroba set VersionId=@versionid_par,
	pPracownik=@pPracownik_par,
	dDataRej=@dDataRej_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	pUzytRej=@pUzytRej_par,
	pUmowa=@pUmowa_par,
	pSchemat=@pSchemat_par,
	strNumZwol=@strNumZwol_par,
	strKodStat=@strKodStat_par,
	strKodPlatnik=@strKodPlatnik_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plchoroba_delete')
	drop procedure n5plchoroba_delete
go

create procedure n5plchoroba_delete(@idobj_par integer) with encryption as 
	delete from n5plchoroba where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plchoroba_maxid')
	drop procedure n5plchoroba_maxid
go

create procedure n5plchoroba_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plchoroba
go

if exists (select * from sysobjects where name='n5plchoroba_candel')
	drop procedure n5plchoroba_candel
go

create procedure n5plchoroba_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where wrefDokument=@idobj_par and wrefDokument_wrt=10201
union
select TOP 5 'typeid'=cast(10221 as integer),idobj from n5plsklnalzrod where wrefDokument=@idobj_par and wrefDokument_wrt=10201
go

-- table: n5plnieob
if exists (select * from sysobjects where name='n5plnieob_select')
	drop procedure n5plnieob_select
go

create procedure n5plnieob_select(@idobj_par integer,@versionid_par integer output,
	@pPracownik_par integer output,
	@dDataRej_par datetime output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@pUzytRej_par integer output,
	@pUmowa_par integer output,
	@pSchemat_par integer output,
	@eTyp_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pPracownik_par=pPracownik,
	@dDataRej_par=dDataRej,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@pUzytRej_par=pUzytRej,
	@pUmowa_par=pUmowa,
	@pSchemat_par=pSchemat,
	@eTyp_par=eTyp from n5plnieob where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnieob_insert')
	drop procedure n5plnieob_insert
go

create procedure n5plnieob_insert(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pUmowa_par integer,@pSchemat_par integer,@eTyp_par integer) with encryption as 
	insert into n5plnieob values(@idobj_par,@versionid_par,@pPracownik_par,@dDataRej_par,@dDataOd_par,@dDataDo_par,@pUzytRej_par,@pUmowa_par,@pSchemat_par,@eTyp_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnieob_update')
	drop procedure n5plnieob_update
go

create procedure n5plnieob_update(@idobj_par integer,@versionid_par integer,@pPracownik_par integer,@dDataRej_par datetime,@dDataOd_par datetime,@dDataDo_par datetime,@pUzytRej_par integer,@pUmowa_par integer,@pSchemat_par integer,@eTyp_par integer) with encryption as 
	update n5plnieob set VersionId=@versionid_par,
	pPracownik=@pPracownik_par,
	dDataRej=@dDataRej_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	pUzytRej=@pUzytRej_par,
	pUmowa=@pUmowa_par,
	pSchemat=@pSchemat_par,
	eTyp=@eTyp_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnieob_delete')
	drop procedure n5plnieob_delete
go

create procedure n5plnieob_delete(@idobj_par integer) with encryption as 
	delete from n5plnieob where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plnieob_maxid')
	drop procedure n5plnieob_maxid
go

create procedure n5plnieob_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plnieob
go

if exists (select * from sysobjects where name='n5plnieob_candel')
	drop procedure n5plnieob_candel
go

create procedure n5plnieob_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10198 as integer),idobj from n5pldekret where wrefDokument=@idobj_par and wrefDokument_wrt=10202
union
select TOP 5 'typeid'=cast(10221 as integer),idobj from n5plsklnalzrod where wrefDokument=@idobj_par and wrefDokument_wrt=10202
go

-- table: n5rozlcit
if exists (select * from sysobjects where name='n5rozlcit_select')
	drop procedure n5rozlcit_select
go

create procedure n5rozlcit_select(@idobj_par integer,@versionid_par integer output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@curPrzych_par decimal(12,2) output,
	@curPrzychZagr_par decimal(12,2) output,
	@curKoszty_par decimal(12,2) output,
	@curDochodWst_par decimal(12,2) output,
	@curStrataWst_par decimal(12,2) output,
	@curStrataZwol_par decimal(12,2) output,
	@curDochod_par decimal(12,2) output,
	@curStrata_par decimal(12,2) output,
	@curDochWolne_par decimal(12,2) output,
	@curOdlDoch_par decimal(12,2) output,
	@curOdlInwest_par decimal(12,2) output,
	@curRazemOdl_par decimal(12,2) output,
	@curOdlInwestPoprz_par decimal(12,2) output,
	@curDochZwol_par decimal(12,2) output,
	@curZwiekszajacaPodstawe_par decimal(12,2) output,
	@curPodstawa_par decimal(12,2) output,
	@curPodstawaStrata_par decimal(12,2) output,
	@curStawka_par decimal(12,2) output,
	@curPodWst_par decimal(12,2) output,
	@curOdlPod_par decimal(12,2) output,
	@curPodatek_par decimal(12,2) output,
	@curSumaPoprzZal_par decimal(12,2) output,
	@curZaliczka_par decimal(12,2) output,
	@curSumaZal_par decimal(12,2) output,
	@curOgraniczeniePoboruZaliczek_par decimal(12,2) output,
	@curZaliczkaPoOgraniczeniu_par decimal(12,2) output,
	@curInneDoch_par decimal(12,2) output,
	@curPodInne_par decimal(12,2) output,
	@curPodArt37_par decimal(12,2) output,
	@curOdsetkiArt16_par decimal(12,2) output,
	@pUzytRej_par integer output,
	@pZadanie_par integer output,
	@pSchematDekr_par integer output,
	@pDowKsieg_par integer output,
	@pTransakcja_par integer output,
	@pUrzadSkarbowy_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@curPrzych_par=curPrzych,
	@curPrzychZagr_par=curPrzychZagr,
	@curKoszty_par=curKoszty,
	@curDochodWst_par=curDochodWst,
	@curStrataWst_par=curStrataWst,
	@curStrataZwol_par=curStrataZwol,
	@curDochod_par=curDochod,
	@curStrata_par=curStrata,
	@curDochWolne_par=curDochWolne,
	@curOdlDoch_par=curOdlDoch,
	@curOdlInwest_par=curOdlInwest,
	@curRazemOdl_par=curRazemOdl,
	@curOdlInwestPoprz_par=curOdlInwestPoprz,
	@curDochZwol_par=curDochZwol,
	@curZwiekszajacaPodstawe_par=curZwiekszajacaPodstawe,
	@curPodstawa_par=curPodstawa,
	@curPodstawaStrata_par=curPodstawaStrata,
	@curStawka_par=curStawka,
	@curPodWst_par=curPodWst,
	@curOdlPod_par=curOdlPod,
	@curPodatek_par=curPodatek,
	@curSumaPoprzZal_par=curSumaPoprzZal,
	@curZaliczka_par=curZaliczka,
	@curSumaZal_par=curSumaZal,
	@curOgraniczeniePoboruZaliczek_par=curOgraniczeniePoboruZaliczek,
	@curZaliczkaPoOgraniczeniu_par=curZaliczkaPoOgraniczeniu,
	@curInneDoch_par=curInneDoch,
	@curPodInne_par=curPodInne,
	@curPodArt37_par=curPodArt37,
	@curOdsetkiArt16_par=curOdsetkiArt16,
	@pUzytRej_par=pUzytRej,
	@pZadanie_par=pZadanie,
	@pSchematDekr_par=pSchematDekr,
	@pDowKsieg_par=pDowKsieg,
	@pTransakcja_par=pTransakcja,
	@pUrzadSkarbowy_par=pUrzadSkarbowy from n5rozlcit where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlcit_insert')
	drop procedure n5rozlcit_insert
go

create procedure n5rozlcit_insert(@idobj_par integer,@versionid_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@curPrzych_par decimal(12,2),@curPrzychZagr_par decimal(12,2),@curKoszty_par decimal(12,2),@curDochodWst_par decimal(12,2),@curStrataWst_par decimal(12,2),@curStrataZwol_par decimal(12,2),@curDochod_par decimal(12,2),@curStrata_par decimal(12,2),@curDochWolne_par decimal(12,2),@curOdlDoch_par decimal(12,2),@curOdlInwest_par decimal(12,2),@curRazemOdl_par decimal(12,2),@curOdlInwestPoprz_par decimal(12,2),@curDochZwol_par decimal(12,2),@curZwiekszajacaPodstawe_par decimal(12,2),@curPodstawa_par decimal(12,2),@curPodstawaStrata_par decimal(12,2),@curStawka_par decimal(12,2),@curPodWst_par decimal(12,2),@curOdlPod_par decimal(12,2),@curPodatek_par decimal(12,2),@curSumaPoprzZal_par decimal(12,2),@curZaliczka_par decimal(12,2),@curSumaZal_par decimal(12,2),@curOgraniczeniePoboruZaliczek_par decimal(12,2),@curZaliczkaPoOgraniczeniu_par decimal(12,2),@curInneDoch_par decimal(12,2),@curPodInne_par decimal(12,2),@curPodArt37_par decimal(12,2),@curOdsetkiArt16_par decimal(12,2),@pUzytRej_par integer,@pZadanie_par integer,@pSchematDekr_par integer,@pDowKsieg_par integer,@pTransakcja_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	insert into n5rozlcit values(@idobj_par,@versionid_par,@dDataOd_par,@dDataDo_par,@curPrzych_par,@curPrzychZagr_par,@curKoszty_par,@curDochodWst_par,@curStrataWst_par,@curStrataZwol_par,@curDochod_par,@curStrata_par,@curDochWolne_par,@curOdlDoch_par,@curOdlInwest_par,@curRazemOdl_par,@curOdlInwestPoprz_par,@curDochZwol_par,@curZwiekszajacaPodstawe_par,@curPodstawa_par,@curPodstawaStrata_par,@curStawka_par,@curPodWst_par,@curOdlPod_par,@curPodatek_par,@curSumaPoprzZal_par,@curZaliczka_par,@curSumaZal_par,@curOgraniczeniePoboruZaliczek_par,@curZaliczkaPoOgraniczeniu_par,@curInneDoch_par,@curPodInne_par,@curPodArt37_par,@curOdsetkiArt16_par,@pUzytRej_par,@pZadanie_par,@pSchematDekr_par,@pDowKsieg_par,@pTransakcja_par,@pUrzadSkarbowy_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlcit_update')
	drop procedure n5rozlcit_update
go

create procedure n5rozlcit_update(@idobj_par integer,@versionid_par integer,@dDataOd_par datetime,@dDataDo_par datetime,@curPrzych_par decimal(12,2),@curPrzychZagr_par decimal(12,2),@curKoszty_par decimal(12,2),@curDochodWst_par decimal(12,2),@curStrataWst_par decimal(12,2),@curStrataZwol_par decimal(12,2),@curDochod_par decimal(12,2),@curStrata_par decimal(12,2),@curDochWolne_par decimal(12,2),@curOdlDoch_par decimal(12,2),@curOdlInwest_par decimal(12,2),@curRazemOdl_par decimal(12,2),@curOdlInwestPoprz_par decimal(12,2),@curDochZwol_par decimal(12,2),@curZwiekszajacaPodstawe_par decimal(12,2),@curPodstawa_par decimal(12,2),@curPodstawaStrata_par decimal(12,2),@curStawka_par decimal(12,2),@curPodWst_par decimal(12,2),@curOdlPod_par decimal(12,2),@curPodatek_par decimal(12,2),@curSumaPoprzZal_par decimal(12,2),@curZaliczka_par decimal(12,2),@curSumaZal_par decimal(12,2),@curOgraniczeniePoboruZaliczek_par decimal(12,2),@curZaliczkaPoOgraniczeniu_par decimal(12,2),@curInneDoch_par decimal(12,2),@curPodInne_par decimal(12,2),@curPodArt37_par decimal(12,2),@curOdsetkiArt16_par decimal(12,2),@pUzytRej_par integer,@pZadanie_par integer,@pSchematDekr_par integer,@pDowKsieg_par integer,@pTransakcja_par integer,@pUrzadSkarbowy_par integer) with encryption as 
	update n5rozlcit set VersionId=@versionid_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	curPrzych=@curPrzych_par,
	curPrzychZagr=@curPrzychZagr_par,
	curKoszty=@curKoszty_par,
	curDochodWst=@curDochodWst_par,
	curStrataWst=@curStrataWst_par,
	curStrataZwol=@curStrataZwol_par,
	curDochod=@curDochod_par,
	curStrata=@curStrata_par,
	curDochWolne=@curDochWolne_par,
	curOdlDoch=@curOdlDoch_par,
	curOdlInwest=@curOdlInwest_par,
	curRazemOdl=@curRazemOdl_par,
	curOdlInwestPoprz=@curOdlInwestPoprz_par,
	curDochZwol=@curDochZwol_par,
	curZwiekszajacaPodstawe=@curZwiekszajacaPodstawe_par,
	curPodstawa=@curPodstawa_par,
	curPodstawaStrata=@curPodstawaStrata_par,
	curStawka=@curStawka_par,
	curPodWst=@curPodWst_par,
	curOdlPod=@curOdlPod_par,
	curPodatek=@curPodatek_par,
	curSumaPoprzZal=@curSumaPoprzZal_par,
	curZaliczka=@curZaliczka_par,
	curSumaZal=@curSumaZal_par,
	curOgraniczeniePoboruZaliczek=@curOgraniczeniePoboruZaliczek_par,
	curZaliczkaPoOgraniczeniu=@curZaliczkaPoOgraniczeniu_par,
	curInneDoch=@curInneDoch_par,
	curPodInne=@curPodInne_par,
	curPodArt37=@curPodArt37_par,
	curOdsetkiArt16=@curOdsetkiArt16_par,
	pUzytRej=@pUzytRej_par,
	pZadanie=@pZadanie_par,
	pSchematDekr=@pSchematDekr_par,
	pDowKsieg=@pDowKsieg_par,
	pTransakcja=@pTransakcja_par,
	pUrzadSkarbowy=@pUrzadSkarbowy_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlcit_delete')
	drop procedure n5rozlcit_delete
go

create procedure n5rozlcit_delete(@idobj_par integer) with encryption as 
	delete from n5rozlcit where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rozlcit_maxid')
	drop procedure n5rozlcit_maxid
go

create procedure n5rozlcit_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5rozlcit
go

if exists (select * from sysobjects where name='n5rozlcit_candel')
	drop procedure n5rozlcit_candel
go

create procedure n5rozlcit_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10203
go

-- table: n5rule
if exists (select * from sysobjects where name='n5rule_select')
	drop procedure n5rule_select
go

create procedure n5rule_select(@idobj_par integer,@versionid_par integer output,
	@strCode_par varchar(8) output,
	@strName_par varchar(128) output,
	@cVisible_par varchar(1) output,
	@eSignificance_par integer output,
	@strParam_par varchar(7900) output,
	@strOptionalParam_par varchar(7900) output) with encryption as 
	select @versionid_par=VersionId,
	@strCode_par=strCode,
	@strName_par=strName,
	@cVisible_par=cVisible,
	@eSignificance_par=eSignificance,
	@strParam_par=strParam,
	@strOptionalParam_par=strOptionalParam from n5rule where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rule_insert')
	drop procedure n5rule_insert
go

create procedure n5rule_insert(@idobj_par integer,@versionid_par integer,@strCode_par varchar(8),@strName_par varchar(128),@cVisible_par varchar(1),@eSignificance_par integer,@strParam_par varchar(7900),@strOptionalParam_par varchar(7900)) with encryption as 
	insert into n5rule values(@idobj_par,@versionid_par,@strCode_par,@strName_par,@cVisible_par,@eSignificance_par,@strParam_par,@strOptionalParam_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5rule_update')
	drop procedure n5rule_update
go

create procedure n5rule_update(@idobj_par integer,@versionid_par integer,@strCode_par varchar(8),@strName_par varchar(128),@cVisible_par varchar(1),@eSignificance_par integer,@strParam_par varchar(7900),@strOptionalParam_par varchar(7900)) with encryption as 
	update n5rule set VersionId=@versionid_par,
	strCode=@strCode_par,
	strName=@strName_par,
	cVisible=@cVisible_par,
	eSignificance=@eSignificance_par,
	strParam=@strParam_par,
	strOptionalParam=@strOptionalParam_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rule_delete')
	drop procedure n5rule_delete
go

create procedure n5rule_delete(@idobj_par integer) with encryption as 
	delete from n5rule where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5rule_maxid')
	drop procedure n5rule_maxid
go

create procedure n5rule_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5rule
go

if exists (select * from sysobjects where name='n5rule_candel')
	drop procedure n5rule_candel
go

create procedure n5rule_candel(@idobj_par integer) with encryption as 
go

-- table: n5pozrealprod
if exists (select * from sysobjects where name='n5pozrealprod_select')
	drop procedure n5pozrealprod_select
go

create procedure n5pozrealprod_select(@idobj_par integer,@versionid_par integer output,
	@pProdukt_par integer output,
	@pOpak_par integer output,
	@pMagazyn_par integer output,
	@pJednOpak_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@pJednEwid_par integer output,
	@curIloscEwid_par decimal(14,4) output,
	@curCenaMag_par decimal(14,4) output,
	@curCenaEwid_par decimal(14,4) output,
	@curWartMag_par decimal(12,2) output,
	@curWartEwid_par decimal(12,2) output,
	@nNumOpMagDost_par integer output,
	@nLpDost_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pProdukt_par=pProdukt,
	@pOpak_par=pOpak,
	@pMagazyn_par=pMagazyn,
	@pJednOpak_par=pJednOpak,
	@curIloscOpak_par=curIloscOpak,
	@pJednEwid_par=pJednEwid,
	@curIloscEwid_par=curIloscEwid,
	@curCenaMag_par=curCenaMag,
	@curCenaEwid_par=curCenaEwid,
	@curWartMag_par=curWartMag,
	@curWartEwid_par=curWartEwid,
	@nNumOpMagDost_par=nNumOpMagDost,
	@nLpDost_par=nLpDost,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5pozrealprod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrealprod_insert')
	drop procedure n5pozrealprod_insert
go

create procedure n5pozrealprod_insert(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@pMagazyn_par integer,@pJednOpak_par integer,@curIloscOpak_par decimal(14,4),@pJednEwid_par integer,@curIloscEwid_par decimal(14,4),@curCenaMag_par decimal(14,4),@curCenaEwid_par decimal(14,4),@curWartMag_par decimal(12,2),@curWartEwid_par decimal(12,2),@nNumOpMagDost_par integer,@nLpDost_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozrealprod values(@idobj_par,@versionid_par,@pProdukt_par,@pOpak_par,@pMagazyn_par,@pJednOpak_par,@curIloscOpak_par,@pJednEwid_par,@curIloscEwid_par,@curCenaMag_par,@curCenaEwid_par,@curWartMag_par,@curWartEwid_par,@nNumOpMagDost_par,@nLpDost_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrealprod_update')
	drop procedure n5pozrealprod_update
go

create procedure n5pozrealprod_update(@idobj_par integer,@versionid_par integer,@pProdukt_par integer,@pOpak_par integer,@pMagazyn_par integer,@pJednOpak_par integer,@curIloscOpak_par decimal(14,4),@pJednEwid_par integer,@curIloscEwid_par decimal(14,4),@curCenaMag_par decimal(14,4),@curCenaEwid_par decimal(14,4),@curWartMag_par decimal(12,2),@curWartEwid_par decimal(12,2),@nNumOpMagDost_par integer,@nLpDost_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5pozrealprod set VersionId=@versionid_par,
	pProdukt=@pProdukt_par,
	pOpak=@pOpak_par,
	pMagazyn=@pMagazyn_par,
	pJednOpak=@pJednOpak_par,
	curIloscOpak=@curIloscOpak_par,
	pJednEwid=@pJednEwid_par,
	curIloscEwid=@curIloscEwid_par,
	curCenaMag=@curCenaMag_par,
	curCenaEwid=@curCenaEwid_par,
	curWartMag=@curWartMag_par,
	curWartEwid=@curWartEwid_par,
	nNumOpMagDost=@nNumOpMagDost_par,
	nLpDost=@nLpDost_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrealprod_delete')
	drop procedure n5pozrealprod_delete
go

create procedure n5pozrealprod_delete(@idobj_par integer) with encryption as 
	delete from n5pozrealprod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5pozrealprod_maxid')
	drop procedure n5pozrealprod_maxid
go

create procedure n5pozrealprod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozrealprod
go

if exists (select * from sysobjects where name='n5pozrealprod_candel')
	drop procedure n5pozrealprod_candel
go

create procedure n5pozrealprod_candel(@idobj_par integer) with encryption as 
go

-- table: n5realprod
if exists (select * from sysobjects where name='n5realprod_select')
	drop procedure n5realprod_select
go

create procedure n5realprod_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@nNumOper_par integer output,
	@pWyrob_par integer output,
	@pOpak_par integer output,
	@curIloscOpak_par decimal(14,4) output,
	@dDataWazn_par datetime output,
	@dDataWyst_par datetime output,
	@pUzytRej_par integer output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@curSumaMag_par decimal(12,2) output,
	@curSumaEwid_par decimal(12,2) output,
	@pMagazyn_par integer output,
	@cAutoCalc_par varchar(1) output,
	@pZlecProd_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@nNumOper_par=nNumOper,
	@pWyrob_par=pWyrob,
	@pOpak_par=pOpak,
	@curIloscOpak_par=curIloscOpak,
	@dDataWazn_par=dDataWazn,
	@dDataWyst_par=dDataWyst,
	@pUzytRej_par=pUzytRej,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@curSumaMag_par=curSumaMag,
	@curSumaEwid_par=curSumaEwid,
	@pMagazyn_par=pMagazyn,
	@cAutoCalc_par=cAutoCalc,
	@pZlecProd_par=pZlecProd,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx from n5realprod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5realprod_insert')
	drop procedure n5realprod_insert
go

create procedure n5realprod_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@nNumOper_par integer,@pWyrob_par integer,@pOpak_par integer,@curIloscOpak_par decimal(14,4),@dDataWazn_par datetime,@dDataWyst_par datetime,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaMag_par decimal(12,2),@curSumaEwid_par decimal(12,2),@pMagazyn_par integer,@cAutoCalc_par varchar(1),@pZlecProd_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	insert into n5realprod values(@idobj_par,@versionid_par,@strNrDok_par,@nNumOper_par,@pWyrob_par,@pOpak_par,@curIloscOpak_par,@dDataWazn_par,@dDataWyst_par,@pUzytRej_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@curSumaMag_par,@curSumaEwid_par,@pMagazyn_par,@cAutoCalc_par,@pZlecProd_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5realprod_update')
	drop procedure n5realprod_update
go

create procedure n5realprod_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@nNumOper_par integer,@pWyrob_par integer,@pOpak_par integer,@curIloscOpak_par decimal(14,4),@dDataWazn_par datetime,@dDataWyst_par datetime,@pUzytRej_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@curSumaMag_par decimal(12,2),@curSumaEwid_par decimal(12,2),@pMagazyn_par integer,@cAutoCalc_par varchar(1),@pZlecProd_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer) with encryption as 
	update n5realprod set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	nNumOper=@nNumOper_par,
	pWyrob=@pWyrob_par,
	pOpak=@pOpak_par,
	curIloscOpak=@curIloscOpak_par,
	dDataWazn=@dDataWazn_par,
	dDataWyst=@dDataWyst_par,
	pUzytRej=@pUzytRej_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	curSumaMag=@curSumaMag_par,
	curSumaEwid=@curSumaEwid_par,
	pMagazyn=@pMagazyn_par,
	cAutoCalc=@cAutoCalc_par,
	pZlecProd=@pZlecProd_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5realprod_delete')
	drop procedure n5realprod_delete
go

create procedure n5realprod_delete(@idobj_par integer) with encryption as 
	delete from n5realprod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5realprod_maxid')
	drop procedure n5realprod_maxid
go

create procedure n5realprod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5realprod
go

if exists (select * from sysobjects where name='n5realprod_candel')
	drop procedure n5realprod_candel
go

create procedure n5realprod_candel(@idobj_par integer) with encryption as 
go

-- table: n5kwalifikator
if exists (select * from sysobjects where name='n5kwalifikator_select')
	drop procedure n5kwalifikator_select
go

create procedure n5kwalifikator_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5kwalifikator where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kwalifikator_insert')
	drop procedure n5kwalifikator_insert
go

create procedure n5kwalifikator_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	insert into n5kwalifikator values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5kwalifikator_update')
	drop procedure n5kwalifikator_update
go

create procedure n5kwalifikator_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64)) with encryption as 
	update n5kwalifikator set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kwalifikator_delete')
	drop procedure n5kwalifikator_delete
go

create procedure n5kwalifikator_delete(@idobj_par integer) with encryption as 
	delete from n5kwalifikator where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5kwalifikator_maxid')
	drop procedure n5kwalifikator_maxid
go

create procedure n5kwalifikator_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5kwalifikator
go

if exists (select * from sysobjects where name='n5kwalifikator_candel')
	drop procedure n5kwalifikator_candel
go

create procedure n5kwalifikator_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10147 as integer),idobj from n5dekret where pKwalifikator=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pKwalifikatorEx=@idobj_par
go

-- table: n5budzet
if exists (select * from sysobjects where name='n5budzet_select')
	drop procedure n5budzet_select
go

create procedure n5budzet_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo from n5budzet where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5budzet_insert')
	drop procedure n5budzet_insert
go

create procedure n5budzet_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@dDataOd_par datetime,@dDataDo_par datetime) with encryption as 
	insert into n5budzet values(@idobj_par,@versionid_par,@strNazwa_par,@dDataOd_par,@dDataDo_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5budzet_update')
	drop procedure n5budzet_update
go

create procedure n5budzet_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@dDataOd_par datetime,@dDataDo_par datetime) with encryption as 
	update n5budzet set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5budzet_delete')
	drop procedure n5budzet_delete
go

create procedure n5budzet_delete(@idobj_par integer) with encryption as 
	delete from n5budzet where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5budzet_maxid')
	drop procedure n5budzet_maxid
go

create procedure n5budzet_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5budzet
go

if exists (select * from sysobjects where name='n5budzet_candel')
	drop procedure n5budzet_candel
go

create procedure n5budzet_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10209 as integer),idobj from n5konto_budzet where pBudzet=@idobj_par
go

-- table: n5konto_budzet
if exists (select * from sysobjects where name='n5konto_budzet_select')
	drop procedure n5konto_budzet_select
go

create procedure n5konto_budzet_select(@idobj_par integer,@versionid_par integer output,
	@pKonto_par integer output,
	@pBudzet_par integer output,
	@curKwota_par decimal(12,2) output,
	@eOdniesienie_par integer output,
	@curRealizacja_par decimal(12,2) output,
	@curPrognoza_par decimal(12,2) output) with encryption as 
	select @versionid_par=VersionId,
	@pKonto_par=pKonto,
	@pBudzet_par=pBudzet,
	@curKwota_par=curKwota,
	@eOdniesienie_par=eOdniesienie,
	@curRealizacja_par=curRealizacja,
	@curPrognoza_par=curPrognoza from n5konto_budzet where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_budzet_insert')
	drop procedure n5konto_budzet_insert
go

create procedure n5konto_budzet_insert(@idobj_par integer,@versionid_par integer,@pKonto_par integer,@pBudzet_par integer,@curKwota_par decimal(12,2),@eOdniesienie_par integer,@curRealizacja_par decimal(12,2),@curPrognoza_par decimal(12,2)) with encryption as 
	insert into n5konto_budzet values(@idobj_par,@versionid_par,@pKonto_par,@pBudzet_par,@curKwota_par,@eOdniesienie_par,@curRealizacja_par,@curPrognoza_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_budzet_update')
	drop procedure n5konto_budzet_update
go

create procedure n5konto_budzet_update(@idobj_par integer,@versionid_par integer,@pKonto_par integer,@pBudzet_par integer,@curKwota_par decimal(12,2),@eOdniesienie_par integer,@curRealizacja_par decimal(12,2),@curPrognoza_par decimal(12,2)) with encryption as 
	update n5konto_budzet set VersionId=@versionid_par,
	pKonto=@pKonto_par,
	pBudzet=@pBudzet_par,
	curKwota=@curKwota_par,
	eOdniesienie=@eOdniesienie_par,
	curRealizacja=@curRealizacja_par,
	curPrognoza=@curPrognoza_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_budzet_delete')
	drop procedure n5konto_budzet_delete
go

create procedure n5konto_budzet_delete(@idobj_par integer) with encryption as 
	delete from n5konto_budzet where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5konto_budzet_maxid')
	drop procedure n5konto_budzet_maxid
go

create procedure n5konto_budzet_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5konto_budzet
go

if exists (select * from sysobjects where name='n5konto_budzet_candel')
	drop procedure n5konto_budzet_candel
go

create procedure n5konto_budzet_candel(@idobj_par integer) with encryption as 
go

-- table: n5bwinfo_kat
if exists (select * from sysobjects where name='n5bwinfo_kat_select')
	drop procedure n5bwinfo_kat_select
go

create procedure n5bwinfo_kat_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa from n5bwinfo_kat where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_kat_insert')
	drop procedure n5bwinfo_kat_insert
go

create procedure n5bwinfo_kat_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128)) with encryption as 
	insert into n5bwinfo_kat values(@idobj_par,@versionid_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_kat_update')
	drop procedure n5bwinfo_kat_update
go

create procedure n5bwinfo_kat_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128)) with encryption as 
	update n5bwinfo_kat set VersionId=@versionid_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_kat_delete')
	drop procedure n5bwinfo_kat_delete
go

create procedure n5bwinfo_kat_delete(@idobj_par integer) with encryption as 
	delete from n5bwinfo_kat where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_kat_maxid')
	drop procedure n5bwinfo_kat_maxid
go

create procedure n5bwinfo_kat_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5bwinfo_kat
go

if exists (select * from sysobjects where name='n5bwinfo_kat_candel')
	drop procedure n5bwinfo_kat_candel
go

create procedure n5bwinfo_kat_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10211 as integer),idobj from n5bwinfo where pKategoria=@idobj_par
go

-- table: n5bwinfo
if exists (select * from sysobjects where name='n5bwinfo_select')
	drop procedure n5bwinfo_select
go

create procedure n5bwinfo_select(@idobj_par integer,@versionid_par integer output,
	@strTytul_par varchar(128) output,
	@strNrInfo_par varchar(32) output,
	@dDataRej_par datetime output,
	@dDataAkt_par datetime output,
	@eStatus_par integer output,
	@pKategoria_par integer output,
	@strObjaw_par varchar(1024) output,
	@strPrzyczyna_par varchar(1024) output,
	@strRozwiazanie_par varchar(1024) output,
	@strUwagi_par varchar(1024) output,
	@pUzytRej_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strTytul_par=strTytul,
	@strNrInfo_par=strNrInfo,
	@dDataRej_par=dDataRej,
	@dDataAkt_par=dDataAkt,
	@eStatus_par=eStatus,
	@pKategoria_par=pKategoria,
	@strObjaw_par=strObjaw,
	@strPrzyczyna_par=strPrzyczyna,
	@strRozwiazanie_par=strRozwiazanie,
	@strUwagi_par=strUwagi,
	@pUzytRej_par=pUzytRej from n5bwinfo where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_insert')
	drop procedure n5bwinfo_insert
go

create procedure n5bwinfo_insert(@idobj_par integer,@versionid_par integer,@strTytul_par varchar(128),@strNrInfo_par varchar(32),@dDataRej_par datetime,@dDataAkt_par datetime,@eStatus_par integer,@pKategoria_par integer,@strObjaw_par varchar(1024),@strPrzyczyna_par varchar(1024),@strRozwiazanie_par varchar(1024),@strUwagi_par varchar(1024),@pUzytRej_par integer) with encryption as 
	insert into n5bwinfo values(@idobj_par,@versionid_par,@strTytul_par,@strNrInfo_par,@dDataRej_par,@dDataAkt_par,@eStatus_par,@pKategoria_par,@strObjaw_par,@strPrzyczyna_par,@strRozwiazanie_par,@strUwagi_par,@pUzytRej_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_update')
	drop procedure n5bwinfo_update
go

create procedure n5bwinfo_update(@idobj_par integer,@versionid_par integer,@strTytul_par varchar(128),@strNrInfo_par varchar(32),@dDataRej_par datetime,@dDataAkt_par datetime,@eStatus_par integer,@pKategoria_par integer,@strObjaw_par varchar(1024),@strPrzyczyna_par varchar(1024),@strRozwiazanie_par varchar(1024),@strUwagi_par varchar(1024),@pUzytRej_par integer) with encryption as 
	update n5bwinfo set VersionId=@versionid_par,
	strTytul=@strTytul_par,
	strNrInfo=@strNrInfo_par,
	dDataRej=@dDataRej_par,
	dDataAkt=@dDataAkt_par,
	eStatus=@eStatus_par,
	pKategoria=@pKategoria_par,
	strObjaw=@strObjaw_par,
	strPrzyczyna=@strPrzyczyna_par,
	strRozwiazanie=@strRozwiazanie_par,
	strUwagi=@strUwagi_par,
	pUzytRej=@pUzytRej_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_delete')
	drop procedure n5bwinfo_delete
go

create procedure n5bwinfo_delete(@idobj_par integer) with encryption as 
	delete from n5bwinfo where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_maxid')
	drop procedure n5bwinfo_maxid
go

create procedure n5bwinfo_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5bwinfo
go

if exists (select * from sysobjects where name='n5bwinfo_candel')
	drop procedure n5bwinfo_candel
go

create procedure n5bwinfo_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10213 as integer),idobj from n5bwinfo_zal where wrefZal=@idobj_par and wrefZal_wrt=10211
go

-- table: n5bwinfo_produkt
if exists (select * from sysobjects where name='n5bwinfo_produkt_select')
	drop procedure n5bwinfo_produkt_select
go

create procedure n5bwinfo_produkt_select(@idobj_par integer,@versionid_par integer output,
	@wpProdGrupa_par integer output,
	@wpProdGrupa_wrt_par integer output,
	@pOpak_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wpProdGrupa_par=wpProdGrupa,
	@wpProdGrupa_wrt_par=wpProdGrupa_wrt,
	@pOpak_par=pOpak from n5bwinfo_produkt where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_produkt_insert')
	drop procedure n5bwinfo_produkt_insert
go

create procedure n5bwinfo_produkt_insert(@idobj_par integer,@versionid_par integer,@wpProdGrupa_par integer,@wpProdGrupa_wrt_par integer,@pOpak_par integer) with encryption as 
	insert into n5bwinfo_produkt values(@idobj_par,@versionid_par,@wpProdGrupa_par,@wpProdGrupa_wrt_par,@pOpak_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_produkt_update')
	drop procedure n5bwinfo_produkt_update
go

create procedure n5bwinfo_produkt_update(@idobj_par integer,@versionid_par integer,@wpProdGrupa_par integer,@wpProdGrupa_wrt_par integer,@pOpak_par integer) with encryption as 
	update n5bwinfo_produkt set VersionId=@versionid_par,
	wpProdGrupa=@wpProdGrupa_par,
	wpProdGrupa_wrt=@wpProdGrupa_wrt_par,
	pOpak=@pOpak_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_produkt_delete')
	drop procedure n5bwinfo_produkt_delete
go

create procedure n5bwinfo_produkt_delete(@idobj_par integer) with encryption as 
	delete from n5bwinfo_produkt where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_produkt_maxid')
	drop procedure n5bwinfo_produkt_maxid
go

create procedure n5bwinfo_produkt_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5bwinfo_produkt
go

if exists (select * from sysobjects where name='n5bwinfo_produkt_candel')
	drop procedure n5bwinfo_produkt_candel
go

create procedure n5bwinfo_produkt_candel(@idobj_par integer) with encryption as 
go

-- table: n5bwinfo_zal
if exists (select * from sysobjects where name='n5bwinfo_zal_select')
	drop procedure n5bwinfo_zal_select
go

create procedure n5bwinfo_zal_select(@idobj_par integer,@versionid_par integer output,
	@wrefZal_par integer output,
	@wrefZal_wrt_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wrefZal_par=wrefZal,
	@wrefZal_wrt_par=wrefZal_wrt from n5bwinfo_zal where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_zal_insert')
	drop procedure n5bwinfo_zal_insert
go

create procedure n5bwinfo_zal_insert(@idobj_par integer,@versionid_par integer,@wrefZal_par integer,@wrefZal_wrt_par integer) with encryption as 
	insert into n5bwinfo_zal values(@idobj_par,@versionid_par,@wrefZal_par,@wrefZal_wrt_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_zal_update')
	drop procedure n5bwinfo_zal_update
go

create procedure n5bwinfo_zal_update(@idobj_par integer,@versionid_par integer,@wrefZal_par integer,@wrefZal_wrt_par integer) with encryption as 
	update n5bwinfo_zal set VersionId=@versionid_par,
	wrefZal=@wrefZal_par,
	wrefZal_wrt=@wrefZal_wrt_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_zal_delete')
	drop procedure n5bwinfo_zal_delete
go

create procedure n5bwinfo_zal_delete(@idobj_par integer) with encryption as 
	delete from n5bwinfo_zal where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5bwinfo_zal_maxid')
	drop procedure n5bwinfo_zal_maxid
go

create procedure n5bwinfo_zal_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5bwinfo_zal
go

if exists (select * from sysobjects where name='n5bwinfo_zal_candel')
	drop procedure n5bwinfo_zal_candel
go

create procedure n5bwinfo_zal_candel(@idobj_par integer) with encryption as 
go

-- table: n5poznotaods
if exists (select * from sysobjects where name='n5poznotaods_select')
	drop procedure n5poznotaods_select
go

create procedure n5poznotaods_select(@idobj_par integer,@versionid_par integer output,
	@pTransakcja_par integer output,
	@curStawka_par decimal(12,2) output,
	@curKwotaZal_par decimal(12,2) output,
	@curKwotaOds_par decimal(12,2) output,
	@nLiczbaDni_par integer output,
	@dDataZaplaty_par datetime output) with encryption as 
	select @versionid_par=VersionId,
	@pTransakcja_par=pTransakcja,
	@curStawka_par=curStawka,
	@curKwotaZal_par=curKwotaZal,
	@curKwotaOds_par=curKwotaOds,
	@nLiczbaDni_par=nLiczbaDni,
	@dDataZaplaty_par=dDataZaplaty from n5poznotaods where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5poznotaods_insert')
	drop procedure n5poznotaods_insert
go

create procedure n5poznotaods_insert(@idobj_par integer,@versionid_par integer,@pTransakcja_par integer,@curStawka_par decimal(12,2),@curKwotaZal_par decimal(12,2),@curKwotaOds_par decimal(12,2),@nLiczbaDni_par integer,@dDataZaplaty_par datetime) with encryption as 
	insert into n5poznotaods values(@idobj_par,@versionid_par,@pTransakcja_par,@curStawka_par,@curKwotaZal_par,@curKwotaOds_par,@nLiczbaDni_par,@dDataZaplaty_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5poznotaods_update')
	drop procedure n5poznotaods_update
go

create procedure n5poznotaods_update(@idobj_par integer,@versionid_par integer,@pTransakcja_par integer,@curStawka_par decimal(12,2),@curKwotaZal_par decimal(12,2),@curKwotaOds_par decimal(12,2),@nLiczbaDni_par integer,@dDataZaplaty_par datetime) with encryption as 
	update n5poznotaods set VersionId=@versionid_par,
	pTransakcja=@pTransakcja_par,
	curStawka=@curStawka_par,
	curKwotaZal=@curKwotaZal_par,
	curKwotaOds=@curKwotaOds_par,
	nLiczbaDni=@nLiczbaDni_par,
	dDataZaplaty=@dDataZaplaty_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5poznotaods_delete')
	drop procedure n5poznotaods_delete
go

create procedure n5poznotaods_delete(@idobj_par integer) with encryption as 
	delete from n5poznotaods where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5poznotaods_maxid')
	drop procedure n5poznotaods_maxid
go

create procedure n5poznotaods_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5poznotaods
go

if exists (select * from sysobjects where name='n5poznotaods_candel')
	drop procedure n5poznotaods_candel
go

create procedure n5poznotaods_candel(@idobj_par integer) with encryption as 
go

-- table: n5notaods
if exists (select * from sysobjects where name='n5notaods_select')
	drop procedure n5notaods_select
go

create procedure n5notaods_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@dDataWyst_par datetime output,
	@pKlient_par integer output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@curSumaOds_par decimal(12,2) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@pTransakcja_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@dDataWyst_par=dDataWyst,
	@pKlient_par=pKlient,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@curSumaOds_par=curSumaOds,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@pTransakcja_par=pTransakcja from n5notaods where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5notaods_insert')
	drop procedure n5notaods_insert
go

create procedure n5notaods_insert(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@pKlient_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@curSumaOds_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@pTransakcja_par integer) with encryption as 
	insert into n5notaods values(@idobj_par,@versionid_par,@strNrDok_par,@dDataWyst_par,@pKlient_par,@pUzytRej_par,@strUwagi_par,@curSumaOds_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par,@pTransakcja_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5notaods_update')
	drop procedure n5notaods_update
go

create procedure n5notaods_update(@idobj_par integer,@versionid_par integer,@strNrDok_par varchar(32),@dDataWyst_par datetime,@pKlient_par integer,@pUzytRej_par integer,@strUwagi_par varchar(512),@curSumaOds_par decimal(12,2),@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@pTransakcja_par integer) with encryption as 
	update n5notaods set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	dDataWyst=@dDataWyst_par,
	pKlient=@pKlient_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	curSumaOds=@curSumaOds_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	pTransakcja=@pTransakcja_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5notaods_delete')
	drop procedure n5notaods_delete
go

create procedure n5notaods_delete(@idobj_par integer) with encryption as 
	delete from n5notaods where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5notaods_maxid')
	drop procedure n5notaods_maxid
go

create procedure n5notaods_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5notaods
go

if exists (select * from sysobjects where name='n5notaods_candel')
	drop procedure n5notaods_candel
go

create procedure n5notaods_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where pNotaOds=@idobj_par
go

-- table: n5opsrtrw
if exists (select * from sysobjects where name='n5opsrtrw_select')
	drop procedure n5opsrtrw_select
go

create procedure n5opsrtrw_select(@idobj_par integer,@versionid_par integer output,
	@pSRTRW_par integer output,
	@nNumOpST_par integer output,
	@dDataOper_par datetime output,
	@eRodzaj_par integer output,
	@curWartoscPod_par decimal(12,2) output,
	@curUmorzPod_par decimal(12,2) output,
	@curAmortPod_par decimal(12,2) output,
	@curStawkaPod_par decimal(12,2) output,
	@curWartoscBil_par decimal(12,2) output,
	@curUmorzBil_par decimal(12,2) output,
	@curAmortBil_par decimal(12,2) output,
	@curStawkaBil_par decimal(12,2) output,
	@dDataAmort_par datetime output,
	@pMUJO_par integer output,
	@pUzytRej_par integer output,
	@pPracownik_par integer output,
	@wrefDokument_par integer output,
	@wrefDokument_wrt_par integer output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@strUwagi_par varchar(512) output) with encryption as 
	select @versionid_par=VersionId,
	@pSRTRW_par=pSRTRW,
	@nNumOpST_par=nNumOpST,
	@dDataOper_par=dDataOper,
	@eRodzaj_par=eRodzaj,
	@curWartoscPod_par=curWartoscPod,
	@curUmorzPod_par=curUmorzPod,
	@curAmortPod_par=curAmortPod,
	@curStawkaPod_par=curStawkaPod,
	@curWartoscBil_par=curWartoscBil,
	@curUmorzBil_par=curUmorzBil,
	@curAmortBil_par=curAmortBil,
	@curStawkaBil_par=curStawkaBil,
	@dDataAmort_par=dDataAmort,
	@pMUJO_par=pMUJO,
	@pUzytRej_par=pUzytRej,
	@pPracownik_par=pPracownik,
	@wrefDokument_par=wrefDokument,
	@wrefDokument_wrt_par=wrefDokument_wrt,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@strUwagi_par=strUwagi from n5opsrtrw where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opsrtrw_insert')
	drop procedure n5opsrtrw_insert
go

create procedure n5opsrtrw_insert(@idobj_par integer,@versionid_par integer,@pSRTRW_par integer,@nNumOpST_par integer,@dDataOper_par datetime,@eRodzaj_par integer,@curWartoscPod_par decimal(12,2),@curUmorzPod_par decimal(12,2),@curAmortPod_par decimal(12,2),@curStawkaPod_par decimal(12,2),@curWartoscBil_par decimal(12,2),@curUmorzBil_par decimal(12,2),@curAmortBil_par decimal(12,2),@curStawkaBil_par decimal(12,2),@dDataAmort_par datetime,@pMUJO_par integer,@pUzytRej_par integer,@pPracownik_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@strUwagi_par varchar(512)) with encryption as 
	insert into n5opsrtrw values(@idobj_par,@versionid_par,@pSRTRW_par,@nNumOpST_par,@dDataOper_par,@eRodzaj_par,@curWartoscPod_par,@curUmorzPod_par,@curAmortPod_par,@curStawkaPod_par,@curWartoscBil_par,@curUmorzBil_par,@curAmortBil_par,@curStawkaBil_par,@dDataAmort_par,@pMUJO_par,@pUzytRej_par,@pPracownik_par,@wrefDokument_par,@wrefDokument_wrt_par,@pRejestrDok_par,@pDowodKsieg_par,@pSchematDekr_par,@strExtra1_par,@strExtra2_par,@dExtra3_par,@curExtra4_par,@curExtra5_par,@pKwalifikatorEx_par,@strUwagi_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5opsrtrw_update')
	drop procedure n5opsrtrw_update
go

create procedure n5opsrtrw_update(@idobj_par integer,@versionid_par integer,@pSRTRW_par integer,@nNumOpST_par integer,@dDataOper_par datetime,@eRodzaj_par integer,@curWartoscPod_par decimal(12,2),@curUmorzPod_par decimal(12,2),@curAmortPod_par decimal(12,2),@curStawkaPod_par decimal(12,2),@curWartoscBil_par decimal(12,2),@curUmorzBil_par decimal(12,2),@curAmortBil_par decimal(12,2),@curStawkaBil_par decimal(12,2),@dDataAmort_par datetime,@pMUJO_par integer,@pUzytRej_par integer,@pPracownik_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer,@pRejestrDok_par integer,@pDowodKsieg_par integer,@pSchematDekr_par integer,@strExtra1_par varchar(32),@strExtra2_par varchar(128),@dExtra3_par datetime,@curExtra4_par decimal(12,2),@curExtra5_par decimal(12,2),@pKwalifikatorEx_par integer,@strUwagi_par varchar(512)) with encryption as 
	update n5opsrtrw set VersionId=@versionid_par,
	pSRTRW=@pSRTRW_par,
	nNumOpST=@nNumOpST_par,
	dDataOper=@dDataOper_par,
	eRodzaj=@eRodzaj_par,
	curWartoscPod=@curWartoscPod_par,
	curUmorzPod=@curUmorzPod_par,
	curAmortPod=@curAmortPod_par,
	curStawkaPod=@curStawkaPod_par,
	curWartoscBil=@curWartoscBil_par,
	curUmorzBil=@curUmorzBil_par,
	curAmortBil=@curAmortBil_par,
	curStawkaBil=@curStawkaBil_par,
	dDataAmort=@dDataAmort_par,
	pMUJO=@pMUJO_par,
	pUzytRej=@pUzytRej_par,
	pPracownik=@pPracownik_par,
	wrefDokument=@wrefDokument_par,
	wrefDokument_wrt=@wrefDokument_wrt_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	strUwagi=@strUwagi_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opsrtrw_delete')
	drop procedure n5opsrtrw_delete
go

create procedure n5opsrtrw_delete(@idobj_par integer) with encryption as 
	delete from n5opsrtrw where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5opsrtrw_maxid')
	drop procedure n5opsrtrw_maxid
go

create procedure n5opsrtrw_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5opsrtrw
go

if exists (select * from sysobjects where name='n5opsrtrw_candel')
	drop procedure n5opsrtrw_candel
go

create procedure n5opsrtrw_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where wrefDokument=@idobj_par and wrefDokument_wrt=10216
go

-- table: n5plwzorlp
if exists (select * from sysobjects where name='n5plwzorlp_select')
	drop procedure n5plwzorlp_select
go

create procedure n5plwzorlp_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@eTypUmowy_par integer output,
	@pCLPracownicy_par integer output,
	@pCLSkladniki_par integer output,
	@strFormatNumeracji_par varchar(32) output,
	@eAktywny_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@eTypUmowy_par=eTypUmowy,
	@pCLPracownicy_par=pCLPracownicy,
	@pCLSkladniki_par=pCLSkladniki,
	@strFormatNumeracji_par=strFormatNumeracji,
	@eAktywny_par=eAktywny from n5plwzorlp where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plwzorlp_insert')
	drop procedure n5plwzorlp_insert
go

create procedure n5plwzorlp_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eTypUmowy_par integer,@pCLPracownicy_par integer,@pCLSkladniki_par integer,@strFormatNumeracji_par varchar(32),@eAktywny_par integer) with encryption as 
	insert into n5plwzorlp values(@idobj_par,@versionid_par,@strNazwa_par,@eTypUmowy_par,@pCLPracownicy_par,@pCLSkladniki_par,@strFormatNumeracji_par,@eAktywny_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plwzorlp_update')
	drop procedure n5plwzorlp_update
go

create procedure n5plwzorlp_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eTypUmowy_par integer,@pCLPracownicy_par integer,@pCLSkladniki_par integer,@strFormatNumeracji_par varchar(32),@eAktywny_par integer) with encryption as 
	update n5plwzorlp set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	eTypUmowy=@eTypUmowy_par,
	pCLPracownicy=@pCLPracownicy_par,
	pCLSkladniki=@pCLSkladniki_par,
	strFormatNumeracji=@strFormatNumeracji_par,
	eAktywny=@eAktywny_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plwzorlp_delete')
	drop procedure n5plwzorlp_delete
go

create procedure n5plwzorlp_delete(@idobj_par integer) with encryption as 
	delete from n5plwzorlp where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plwzorlp_maxid')
	drop procedure n5plwzorlp_maxid
go

create procedure n5plwzorlp_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plwzorlp
go

if exists (select * from sysobjects where name='n5plwzorlp_candel')
	drop procedure n5plwzorlp_candel
go

create procedure n5plwzorlp_candel(@idobj_par integer) with encryption as 
go

-- table: n5plkalcp
if exists (select * from sysobjects where name='n5plkalcp_select')
	drop procedure n5plkalcp_select
go

create procedure n5plkalcp_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@eAktywny_par integer output,
	@strUwagi_par varchar(512) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@eAktywny_par=eAktywny,
	@strUwagi_par=strUwagi from n5plkalcp where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plkalcp_insert')
	drop procedure n5plkalcp_insert
go

create procedure n5plkalcp_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eAktywny_par integer,@strUwagi_par varchar(512)) with encryption as 
	insert into n5plkalcp values(@idobj_par,@versionid_par,@strNazwa_par,@eAktywny_par,@strUwagi_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plkalcp_update')
	drop procedure n5plkalcp_update
go

create procedure n5plkalcp_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@eAktywny_par integer,@strUwagi_par varchar(512)) with encryption as 
	update n5plkalcp set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	eAktywny=@eAktywny_par,
	strUwagi=@strUwagi_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plkalcp_delete')
	drop procedure n5plkalcp_delete
go

create procedure n5plkalcp_delete(@idobj_par integer) with encryption as 
	delete from n5plkalcp where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plkalcp_maxid')
	drop procedure n5plkalcp_maxid
go

create procedure n5plkalcp_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plkalcp
go

if exists (select * from sysobjects where name='n5plkalcp_candel')
	drop procedure n5plkalcp_candel
go

create procedure n5plkalcp_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pKalendarz=@idobj_par
go

-- table: n5plpozkalcp
if exists (select * from sysobjects where name='n5plpozkalcp_select')
	drop procedure n5plpozkalcp_select
go

create procedure n5plpozkalcp_select(@idobj_par integer,@versionid_par integer output,
	@cDniTyg_par varchar(8) output,
	@dDataOd_par datetime output,
	@dDataDo_par datetime output,
	@tCzasOd_par integer output,
	@tCzasDo_par integer output,
	@eTypOkresu_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@cDniTyg_par=cDniTyg,
	@dDataOd_par=dDataOd,
	@dDataDo_par=dDataDo,
	@tCzasOd_par=tCzasOd,
	@tCzasDo_par=tCzasDo,
	@eTypOkresu_par=eTypOkresu from n5plpozkalcp where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plpozkalcp_insert')
	drop procedure n5plpozkalcp_insert
go

create procedure n5plpozkalcp_insert(@idobj_par integer,@versionid_par integer,@cDniTyg_par varchar(8),@dDataOd_par datetime,@dDataDo_par datetime,@tCzasOd_par integer,@tCzasDo_par integer,@eTypOkresu_par integer) with encryption as 
	insert into n5plpozkalcp values(@idobj_par,@versionid_par,@cDniTyg_par,@dDataOd_par,@dDataDo_par,@tCzasOd_par,@tCzasDo_par,@eTypOkresu_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plpozkalcp_update')
	drop procedure n5plpozkalcp_update
go

create procedure n5plpozkalcp_update(@idobj_par integer,@versionid_par integer,@cDniTyg_par varchar(8),@dDataOd_par datetime,@dDataDo_par datetime,@tCzasOd_par integer,@tCzasDo_par integer,@eTypOkresu_par integer) with encryption as 
	update n5plpozkalcp set VersionId=@versionid_par,
	cDniTyg=@cDniTyg_par,
	dDataOd=@dDataOd_par,
	dDataDo=@dDataDo_par,
	tCzasOd=@tCzasOd_par,
	tCzasDo=@tCzasDo_par,
	eTypOkresu=@eTypOkresu_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plpozkalcp_delete')
	drop procedure n5plpozkalcp_delete
go

create procedure n5plpozkalcp_delete(@idobj_par integer) with encryption as 
	delete from n5plpozkalcp where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plpozkalcp_maxid')
	drop procedure n5plpozkalcp_maxid
go

create procedure n5plpozkalcp_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plpozkalcp
go

if exists (select * from sysobjects where name='n5plpozkalcp_candel')
	drop procedure n5plpozkalcp_candel
go

create procedure n5plpozkalcp_candel(@idobj_par integer) with encryption as 
go

-- table: n5plsklumowy
if exists (select * from sysobjects where name='n5plsklumowy_select')
	drop procedure n5plsklumowy_select
go

create procedure n5plsklumowy_select(@idobj_par integer,@versionid_par integer output,
	@pSchemat_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pSchemat_par=pSchemat from n5plsklumowy where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklumowy_insert')
	drop procedure n5plsklumowy_insert
go

create procedure n5plsklumowy_insert(@idobj_par integer,@versionid_par integer,@pSchemat_par integer) with encryption as 
	insert into n5plsklumowy values(@idobj_par,@versionid_par,@pSchemat_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklumowy_update')
	drop procedure n5plsklumowy_update
go

create procedure n5plsklumowy_update(@idobj_par integer,@versionid_par integer,@pSchemat_par integer) with encryption as 
	update n5plsklumowy set VersionId=@versionid_par,
	pSchemat=@pSchemat_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklumowy_delete')
	drop procedure n5plsklumowy_delete
go

create procedure n5plsklumowy_delete(@idobj_par integer) with encryption as 
	delete from n5plsklumowy where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklumowy_maxid')
	drop procedure n5plsklumowy_maxid
go

create procedure n5plsklumowy_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plsklumowy
go

if exists (select * from sysobjects where name='n5plsklumowy_candel')
	drop procedure n5plsklumowy_candel
go

create procedure n5plsklumowy_candel(@idobj_par integer) with encryption as 
go

-- table: n5plsklnalzrod
if exists (select * from sysobjects where name='n5plsklnalzrod_select')
	drop procedure n5plsklnalzrod_select
go

create procedure n5plsklnalzrod_select(@idobj_par integer,@versionid_par integer output,
	@wrefDokument_par integer output,
	@wrefDokument_wrt_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@wrefDokument_par=wrefDokument,
	@wrefDokument_wrt_par=wrefDokument_wrt from n5plsklnalzrod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnalzrod_insert')
	drop procedure n5plsklnalzrod_insert
go

create procedure n5plsklnalzrod_insert(@idobj_par integer,@versionid_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer) with encryption as 
	insert into n5plsklnalzrod values(@idobj_par,@versionid_par,@wrefDokument_par,@wrefDokument_wrt_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnalzrod_update')
	drop procedure n5plsklnalzrod_update
go

create procedure n5plsklnalzrod_update(@idobj_par integer,@versionid_par integer,@wrefDokument_par integer,@wrefDokument_wrt_par integer) with encryption as 
	update n5plsklnalzrod set VersionId=@versionid_par,
	wrefDokument=@wrefDokument_par,
	wrefDokument_wrt=@wrefDokument_wrt_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnalzrod_delete')
	drop procedure n5plsklnalzrod_delete
go

create procedure n5plsklnalzrod_delete(@idobj_par integer) with encryption as 
	delete from n5plsklnalzrod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5plsklnalzrod_maxid')
	drop procedure n5plsklnalzrod_maxid
go

create procedure n5plsklnalzrod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5plsklnalzrod
go

if exists (select * from sysobjects where name='n5plsklnalzrod_candel')
	drop procedure n5plsklnalzrod_candel
go

create procedure n5plsklnalzrod_candel(@idobj_par integer) with encryption as 
go

-- table: SearchType
if exists (select * from sysobjects where name='SearchType_select')
	drop procedure SearchType_select
go

create procedure SearchType_select(@idobj_par integer,@versionid_par integer output,
	@Nazwa_par varchar(255) output,
	@ResultTypeId_par integer output,
	@cKind_par varchar(1) output,
	@strKod_par varchar(8) output,
	@nIsSecurity_par integer output,
	@Opis_par varchar(512) output) with encryption as 
	select @versionid_par=VersionId,
	@Nazwa_par=Nazwa,
	@ResultTypeId_par=ResultTypeId,
	@cKind_par=cKind,
	@strKod_par=strKod,
	@nIsSecurity_par=nIsSecurity,
	@Opis_par=Opis from SearchType where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchType_insert')
	drop procedure SearchType_insert
go

create procedure SearchType_insert(@idobj_par integer,@versionid_par integer,@Nazwa_par varchar(255),@ResultTypeId_par integer,@cKind_par varchar(1),@strKod_par varchar(8),@nIsSecurity_par integer,@Opis_par varchar(512)) with encryption as 
	insert into SearchType values(@idobj_par,@versionid_par,@Nazwa_par,@ResultTypeId_par,@cKind_par,@strKod_par,@nIsSecurity_par,@Opis_par)
return @@rowcount
go

if exists (select * from sysobjects where name='SearchType_update')
	drop procedure SearchType_update
go

create procedure SearchType_update(@idobj_par integer,@versionid_par integer,@Nazwa_par varchar(255),@ResultTypeId_par integer,@cKind_par varchar(1),@strKod_par varchar(8),@nIsSecurity_par integer,@Opis_par varchar(512)) with encryption as 
	update SearchType set VersionId=@versionid_par,
	Nazwa=@Nazwa_par,
	ResultTypeId=@ResultTypeId_par,
	cKind=@cKind_par,
	strKod=@strKod_par,
	nIsSecurity=@nIsSecurity_par,
	Opis=@Opis_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchType_delete')
	drop procedure SearchType_delete
go

create procedure SearchType_delete(@idobj_par integer) with encryption as 
	delete from SearchType where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchType_maxid')
	drop procedure SearchType_maxid
go

create procedure SearchType_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from SearchType
go

if exists (select * from sysobjects where name='SearchType_candel')
	drop procedure SearchType_candel
go

create procedure SearchType_candel(@idobj_par integer) with encryption as 
go

-- table: SearchTypeItem
if exists (select * from sysobjects where name='SearchTypeItem_select')
	drop procedure SearchTypeItem_select
go

create procedure SearchTypeItem_select(@idobj_par integer,@versionid_par integer output,
	@ComposedPath_par varchar(255) output,
	@cGroup_par varchar(1) output,
	@cDesc_par varchar(1) output,
	@cLink_par varchar(1) output) with encryption as 
	select @versionid_par=VersionId,
	@ComposedPath_par=ComposedPath,
	@cGroup_par=cGroup,
	@cDesc_par=cDesc,
	@cLink_par=cLink from SearchTypeItem where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchTypeItem_insert')
	drop procedure SearchTypeItem_insert
go

create procedure SearchTypeItem_insert(@idobj_par integer,@versionid_par integer,@ComposedPath_par varchar(255),@cGroup_par varchar(1),@cDesc_par varchar(1),@cLink_par varchar(1)) with encryption as 
	insert into SearchTypeItem values(@idobj_par,@versionid_par,@ComposedPath_par,@cGroup_par,@cDesc_par,@cLink_par)
return @@rowcount
go

if exists (select * from sysobjects where name='SearchTypeItem_update')
	drop procedure SearchTypeItem_update
go

create procedure SearchTypeItem_update(@idobj_par integer,@versionid_par integer,@ComposedPath_par varchar(255),@cGroup_par varchar(1),@cDesc_par varchar(1),@cLink_par varchar(1)) with encryption as 
	update SearchTypeItem set VersionId=@versionid_par,
	ComposedPath=@ComposedPath_par,
	cGroup=@cGroup_par,
	cDesc=@cDesc_par,
	cLink=@cLink_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchTypeItem_delete')
	drop procedure SearchTypeItem_delete
go

create procedure SearchTypeItem_delete(@idobj_par integer) with encryption as 
	delete from SearchTypeItem where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='SearchTypeItem_maxid')
	drop procedure SearchTypeItem_maxid
go

create procedure SearchTypeItem_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from SearchTypeItem
go

if exists (select * from sysobjects where name='SearchTypeItem_candel')
	drop procedure SearchTypeItem_candel
go

create procedure SearchTypeItem_candel(@idobj_par integer) with encryption as 
go

-- table: n5sodgroup
if exists (select * from sysobjects where name='n5sodgroup_select')
	drop procedure n5sodgroup_select
go

create procedure n5sodgroup_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pSODGroup_par integer output,
	@strKod_par varchar(8) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pSODGroup_par=pSODGroup,
	@strKod_par=strKod from n5sodgroup where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sodgroup_insert')
	drop procedure n5sodgroup_insert
go

create procedure n5sodgroup_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pSODGroup_par integer,@strKod_par varchar(8)) with encryption as 
	insert into n5sodgroup values(@idobj_par,@versionid_par,@strNazwa_par,@pSODGroup_par,@strKod_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5sodgroup_update')
	drop procedure n5sodgroup_update
go

create procedure n5sodgroup_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pSODGroup_par integer,@strKod_par varchar(8)) with encryption as 
	update n5sodgroup set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pSODGroup=@pSODGroup_par,
	strKod=@strKod_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sodgroup_delete')
	drop procedure n5sodgroup_delete
go

create procedure n5sodgroup_delete(@idobj_par integer) with encryption as 
	delete from n5sodgroup where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sodgroup_maxid')
	drop procedure n5sodgroup_maxid
go

create procedure n5sodgroup_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5sodgroup
go

if exists (select * from sysobjects where name='n5sodgroup_candel')
	drop procedure n5sodgroup_candel
go

create procedure n5sodgroup_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10004 as integer),idobj from n5sodgroup where pSODGroup=@idobj_par
union
select TOP 5 'typeid'=cast(10005 as integer),idobj from n5sod where pSODGroup=@idobj_par
go

-- table: n5sod
if exists (select * from sysobjects where name='n5sod_select')
	drop procedure n5sod_select
go

create procedure n5sod_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(64) output,
	@pSODGroup_par integer output,
	@nSecId_par integer output,
	@nIdent_par integer output,
	@strKod_par varchar(8) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pSODGroup_par=pSODGroup,
	@nSecId_par=nSecId,
	@nIdent_par=nIdent,
	@strKod_par=strKod from n5sod where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sod_insert')
	drop procedure n5sod_insert
go

create procedure n5sod_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pSODGroup_par integer,@nSecId_par integer,@nIdent_par integer,@strKod_par varchar(8)) with encryption as 
	insert into n5sod values(@idobj_par,@versionid_par,@strNazwa_par,@pSODGroup_par,@nSecId_par,@nIdent_par,@strKod_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5sod_update')
	drop procedure n5sod_update
go

create procedure n5sod_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(64),@pSODGroup_par integer,@nSecId_par integer,@nIdent_par integer,@strKod_par varchar(8)) with encryption as 
	update n5sod set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pSODGroup=@pSODGroup_par,
	nSecId=@nSecId_par,
	nIdent=@nIdent_par,
	strKod=@strKod_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sod_delete')
	drop procedure n5sod_delete
go

create procedure n5sod_delete(@idobj_par integer) with encryption as 
	delete from n5sod where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5sod_maxid')
	drop procedure n5sod_maxid
go

create procedure n5sod_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5sod
go

if exists (select * from sysobjects where name='n5sod_candel')
	drop procedure n5sod_candel
go

create procedure n5sod_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10006 as integer),idobj from n5securityobj where pSOD=@idobj_par
go

-- table: n5securityobj
if exists (select * from sysobjects where name='n5securityobj_select')
	drop procedure n5securityobj_select
go

create procedure n5securityobj_select(@idobj_par integer,@versionid_par integer output,
	@pSOD_par integer output,
	@pUser_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pSOD_par=pSOD,
	@pUser_par=pUser from n5securityobj where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5securityobj_insert')
	drop procedure n5securityobj_insert
go

create procedure n5securityobj_insert(@idobj_par integer,@versionid_par integer,@pSOD_par integer,@pUser_par integer) with encryption as 
	insert into n5securityobj values(@idobj_par,@versionid_par,@pSOD_par,@pUser_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5securityobj_update')
	drop procedure n5securityobj_update
go

create procedure n5securityobj_update(@idobj_par integer,@versionid_par integer,@pSOD_par integer,@pUser_par integer) with encryption as 
	update n5securityobj set VersionId=@versionid_par,
	pSOD=@pSOD_par,
	pUser=@pUser_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5securityobj_delete')
	drop procedure n5securityobj_delete
go

create procedure n5securityobj_delete(@idobj_par integer) with encryption as 
	delete from n5securityobj where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5securityobj_maxid')
	drop procedure n5securityobj_maxid
go

create procedure n5securityobj_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5securityobj
go

if exists (select * from sysobjects where name='n5securityobj_candel')
	drop procedure n5securityobj_candel
go

create procedure n5securityobj_candel(@idobj_par integer) with encryption as 
go

-- table: n5miesiac
if exists (select * from sysobjects where name='n5miesiac_select')
	drop procedure n5miesiac_select
go

create procedure n5miesiac_select(@idobj_par integer,@versionid_par integer output,
	@nNumer_par integer output,
	@strNazwa_par varchar(32) output) with encryption as 
	select @versionid_par=VersionId,
	@nNumer_par=nNumer,
	@strNazwa_par=strNazwa from n5miesiac where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miesiac_insert')
	drop procedure n5miesiac_insert
go

create procedure n5miesiac_insert(@idobj_par integer,@versionid_par integer,@nNumer_par integer,@strNazwa_par varchar(32)) with encryption as 
	insert into n5miesiac values(@idobj_par,@versionid_par,@nNumer_par,@strNazwa_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5miesiac_update')
	drop procedure n5miesiac_update
go

create procedure n5miesiac_update(@idobj_par integer,@versionid_par integer,@nNumer_par integer,@strNazwa_par varchar(32)) with encryption as 
	update n5miesiac set VersionId=@versionid_par,
	nNumer=@nNumer_par,
	strNazwa=@strNazwa_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miesiac_delete')
	drop procedure n5miesiac_delete
go

create procedure n5miesiac_delete(@idobj_par integer) with encryption as 
	delete from n5miesiac where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5miesiac_maxid')
	drop procedure n5miesiac_maxid
go

create procedure n5miesiac_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5miesiac
go

if exists (select * from sysobjects where name='n5miesiac_candel')
	drop procedure n5miesiac_candel
go

create procedure n5miesiac_candel(@idobj_par integer) with encryption as 
go

-- table: n5dpc
if exists (select * from sysobjects where name='n5dpc_select')
	drop procedure n5dpc_select
go

create procedure n5dpc_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@ePubType_par integer output,
	@eChannel_par integer output,
	@pDocTemplate_par integer output,
	@eFormat_par integer output,
	@strDevice_par varchar(128) output,
	@strConfig_par varchar(128) output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@ePubType_par=ePubType,
	@eChannel_par=eChannel,
	@pDocTemplate_par=pDocTemplate,
	@eFormat_par=eFormat,
	@strDevice_par=strDevice,
	@strConfig_par=strConfig from n5dpc where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dpc_insert')
	drop procedure n5dpc_insert
go

create procedure n5dpc_insert(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@ePubType_par integer,@eChannel_par integer,@pDocTemplate_par integer,@eFormat_par integer,@strDevice_par varchar(128),@strConfig_par varchar(128)) with encryption as 
	insert into n5dpc values(@idobj_par,@versionid_par,@strNazwa_par,@ePubType_par,@eChannel_par,@pDocTemplate_par,@eFormat_par,@strDevice_par,@strConfig_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5dpc_update')
	drop procedure n5dpc_update
go

create procedure n5dpc_update(@idobj_par integer,@versionid_par integer,@strNazwa_par varchar(128),@ePubType_par integer,@eChannel_par integer,@pDocTemplate_par integer,@eFormat_par integer,@strDevice_par varchar(128),@strConfig_par varchar(128)) with encryption as 
	update n5dpc set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	ePubType=@ePubType_par,
	eChannel=@eChannel_par,
	pDocTemplate=@pDocTemplate_par,
	eFormat=@eFormat_par,
	strDevice=@strDevice_par,
	strConfig=@strConfig_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dpc_delete')
	drop procedure n5dpc_delete
go

create procedure n5dpc_delete(@idobj_par integer) with encryption as 
	delete from n5dpc where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5dpc_maxid')
	drop procedure n5dpc_maxid
go

create procedure n5dpc_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dpc
go

if exists (select * from sysobjects where name='n5dpc_candel')
	drop procedure n5dpc_candel
go

create procedure n5dpc_candel(@idobj_par integer) with encryption as 
go

-- table: n5globprof
if exists (select * from sysobjects where name='n5globprof_select')
	drop procedure n5globprof_select
go

create procedure n5globprof_select(@idobj_par integer,@versionid_par integer output,
	@Indeks_par integer output,
	@Wartosc_par varchar(255) output) with encryption as 
	select @versionid_par=VersionId,
	@Indeks_par=Indeks,
	@Wartosc_par=Wartosc from n5globprof where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globprof_insert')
	drop procedure n5globprof_insert
go

create procedure n5globprof_insert(@idobj_par integer,@versionid_par integer,@Indeks_par integer,@Wartosc_par varchar(255)) with encryption as 
	insert into n5globprof values(@idobj_par,@versionid_par,@Indeks_par,@Wartosc_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5globprof_update')
	drop procedure n5globprof_update
go

create procedure n5globprof_update(@idobj_par integer,@versionid_par integer,@Indeks_par integer,@Wartosc_par varchar(255)) with encryption as 
	update n5globprof set VersionId=@versionid_par,
	Indeks=@Indeks_par,
	Wartosc=@Wartosc_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globprof_delete')
	drop procedure n5globprof_delete
go

create procedure n5globprof_delete(@idobj_par integer) with encryption as 
	delete from n5globprof where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globprof_maxid')
	drop procedure n5globprof_maxid
go

create procedure n5globprof_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5globprof
go

if exists (select * from sysobjects where name='n5globprof_candel')
	drop procedure n5globprof_candel
go

create procedure n5globprof_candel(@idobj_par integer) with encryption as 
go

-- table: n5userprof
if exists (select * from sysobjects where name='n5userprof_select')
	drop procedure n5userprof_select
go

create procedure n5userprof_select(@idobj_par integer,@versionid_par integer output,
	@Indeks_par integer output,
	@Wartosc_par varchar(255) output,
	@pn5user_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@Indeks_par=Indeks,
	@Wartosc_par=Wartosc,
	@pn5user_par=pn5user from n5userprof where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userprof_insert')
	drop procedure n5userprof_insert
go

create procedure n5userprof_insert(@idobj_par integer,@versionid_par integer,@Indeks_par integer,@Wartosc_par varchar(255),@pn5user_par integer) with encryption as 
	insert into n5userprof values(@idobj_par,@versionid_par,@Indeks_par,@Wartosc_par,@pn5user_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5userprof_update')
	drop procedure n5userprof_update
go

create procedure n5userprof_update(@idobj_par integer,@versionid_par integer,@Indeks_par integer,@Wartosc_par varchar(255),@pn5user_par integer) with encryption as 
	update n5userprof set VersionId=@versionid_par,
	Indeks=@Indeks_par,
	Wartosc=@Wartosc_par,
	pn5user=@pn5user_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userprof_delete')
	drop procedure n5userprof_delete
go

create procedure n5userprof_delete(@idobj_par integer) with encryption as 
	delete from n5userprof where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userprof_maxid')
	drop procedure n5userprof_maxid
go

create procedure n5userprof_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5userprof
go

if exists (select * from sysobjects where name='n5userprof_candel')
	drop procedure n5userprof_candel
go

create procedure n5userprof_candel(@idobj_par integer) with encryption as 
go

-- table: n5globfile
if exists (select * from sysobjects where name='n5globfile_select')
	drop procedure n5globfile_select
go

create procedure n5globfile_select(@idobj_par integer,@versionid_par integer output,
	@nIndeks_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@nIndeks_par=nIndeks from n5globfile where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globfile_insert')
	drop procedure n5globfile_insert
go

create procedure n5globfile_insert(@idobj_par integer,@versionid_par integer,@nIndeks_par integer) with encryption as 
	insert into n5globfile values(@idobj_par,@versionid_par,@nIndeks_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5globfile_update')
	drop procedure n5globfile_update
go

create procedure n5globfile_update(@idobj_par integer,@versionid_par integer,@nIndeks_par integer) with encryption as 
	update n5globfile set VersionId=@versionid_par,
	nIndeks=@nIndeks_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globfile_delete')
	drop procedure n5globfile_delete
go

create procedure n5globfile_delete(@idobj_par integer) with encryption as 
	delete from n5globfile where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5globfile_maxid')
	drop procedure n5globfile_maxid
go

create procedure n5globfile_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5globfile
go

if exists (select * from sysobjects where name='n5globfile_candel')
	drop procedure n5globfile_candel
go

create procedure n5globfile_candel(@idobj_par integer) with encryption as 
go

-- table: n5userfile
if exists (select * from sysobjects where name='n5userfile_select')
	drop procedure n5userfile_select
go

create procedure n5userfile_select(@idobj_par integer,@versionid_par integer output,
	@nIndeks_par integer output,
	@pUzytkownik_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@nIndeks_par=nIndeks,
	@pUzytkownik_par=pUzytkownik from n5userfile where IdObj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userfile_insert')
	drop procedure n5userfile_insert
go

create procedure n5userfile_insert(@idobj_par integer,@versionid_par integer,@nIndeks_par integer,@pUzytkownik_par integer) with encryption as 
	insert into n5userfile values(@idobj_par,@versionid_par,@nIndeks_par,@pUzytkownik_par)
return @@rowcount
go

if exists (select * from sysobjects where name='n5userfile_update')
	drop procedure n5userfile_update
go

create procedure n5userfile_update(@idobj_par integer,@versionid_par integer,@nIndeks_par integer,@pUzytkownik_par integer) with encryption as 
	update n5userfile set VersionId=@versionid_par,
	nIndeks=@nIndeks_par,
	pUzytkownik=@pUzytkownik_par
	where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userfile_delete')
	drop procedure n5userfile_delete
go

create procedure n5userfile_delete(@idobj_par integer) with encryption as 
	delete from n5userfile where idobj=@idobj_par
return @@rowcount
go

if exists (select * from sysobjects where name='n5userfile_maxid')
	drop procedure n5userfile_maxid
go

create procedure n5userfile_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5userfile
go

if exists (select * from sysobjects where name='n5userfile_candel')
	drop procedure n5userfile_candel
go

create procedure n5userfile_candel(@idobj_par integer) with encryption as 
go

-- creating FK

alter table n5jednostka add constraint ENUM_n5jednostka_eTyp_5 check (
eTyp between 0 and 2
)
go
alter table n5kraj add constraint FK_n5kraj_n5jednostka_4 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5bank add constraint FK_n5bank_n5miejscowosc_11 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5instytucja add constraint FK_n5instytucja_n5typinstytucji_4 foreign key (pTyp ) references n5typinstytucji ( IdObj )
go
alter table n5instytucja add constraint FK_n5instytucja_n5miejscowosc_10 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5uzytkownik add constraint ENUM_n5uzytkownik_eAktywny_7 check (
eAktywny between 0 and 3
)
go
alter table n5klient add constraint FK_n5klient_n5miejscowosc_10 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5klient add constraint ENUM_n5klient_eTypDT_25 check (
eTypDT between 0 and 3
)
go
alter table n5klient add constraint ENUM_n5klient_eAktywny_37 check (
eAktywny between 0 and 2
)
go
alter table n5klient add constraint ENUM_n5klient_eKlasaKlienta_38 check (
eKlasaKlienta between 0 and 3
)
go
alter table n5klient add constraint FK_n5klient_n5jednostka_39 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5klient add constraint ENUM_n5klient_ePlec_50 check (
ePlec between 0 and 2
)
go
alter table n5klient add constraint FK_n5klient_n5grupaklient_54 foreign key (pGrupaKlient ) references n5grupaklient ( IdObj )
go
alter table n5klient add constraint ENUM_n5klient_ePrywat_55 check (
ePrywat between 0 and 2
)
go
alter table n5klient add constraint ENUM_n5klient_eWiarFin_64 check (
eWiarFin between 0 and 4
)
go
alter table n5pracownik add constraint ENUM_n5pracownik_ePlec_9 check (
ePlec between 0 and 2
)
go
alter table n5pracownik add constraint FK_n5pracownik_n5miejscowosc_15 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5pracownik add constraint ENUM_n5pracownik_eAktywny_27 check (
eAktywny between 0 and 4
)
go
alter table n5pracownik add constraint ENUM_n5pracownik_eTypDT_31 check (
eTypDT between 0 and 3
)
go
alter table n5pracownik add constraint FK_n5pracownik_n5jedn_org_34 foreign key (pJednostkaOrg ) references n5jedn_org ( IdObj )
go
alter table n5firma add constraint FK_n5firma_n5miejscowosc_9 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5firma add constraint ENUM_n5firma_eForma_21 check (
eForma between 0 and 5
)
go
alter table n5firma add constraint FK_n5firma_n5jednostka_33 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5firma add constraint FK_n5firma_n5jedn_org_39 foreign key (pMainJO ) references n5jedn_org ( IdObj )
go
alter table n5miejscowosc add constraint ENUM_n5miejscowosc_eWielkosc_3 check (
eWielkosc between 0 and 7
)
go
alter table n5miejscowosc add constraint FK_n5miejscowosc_n5wojewodztwo_4 foreign key (pWojewodztwo ) references n5wojewodztwo ( IdObj )
go
alter table n5klient_pracownik add constraint ENUM_n5klient_pracownik_ePlec_5 check (
ePlec between 0 and 2
)
go
alter table n5klient_pracownik add constraint ENUM_n5klient_pracownik_eStanCywilny_8 check (
eStanCywilny between 0 and 5
)
go
alter table n5klient_pracownik add constraint FK_n5klient_pracownik_n5klient_10 foreign key (pKlient ) references n5klient ( IdObj )
go
alter table n5klient_pracownik add constraint ENUM_n5klient_pracownik_eAktywny_22 check (
eAktywny between 0 and 2
)
go
alter table n5jedn_org add constraint FK_n5jedn_org_n5miejscowosc_11 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5_klient_jedn_org add constraint FK_n5_klient_jedn_org_n5miejscowosc_9 foreign key (pMiejscowosc ) references n5miejscowosc ( IdObj )
go
alter table n5_klient_jedn_org add constraint FK_n5_klient_jedn_org_n5klient_27 foreign key (pKlient ) references n5klient ( IdObj )
go
alter table n5typdokumentu add constraint ENUM_n5typdokumentu_eRodzaj_4 check (
eRodzaj between 0 and 3
)
go
alter table n5dokument add constraint FK_n5dokument_n5typdokumentu_5 foreign key (pTypDokumentu ) references n5typdokumentu ( IdObj )
go
alter table n5dokument add constraint WRT_n5dokument_wpNadawca_8 check (
	wpNadawca_wrt=0 or 
	wpNadawca_wrt=10112 or 
	wpNadawca_wrt=10109 or 
	wpNadawca_wrt=10108
)
go
alter table n5dokument add constraint WRT_n5dokument_wpAdresat_9 check (
	wpAdresat_wrt=0 or 
	wpAdresat_wrt=10112 or 
	wpAdresat_wrt=10109 or 
	wpAdresat_wrt=10108
)
go
alter table n5dokument add constraint ENUM_n5dokument_nForma_11 check (
nForma between 0 and 4
)
go
alter table n5zadanie add constraint FK_n5zadanie_n5wykonawca_5 foreign key (pZlecajacy ) references n5wykonawca ( IdObj )
go
alter table n5zadanie add constraint ENUM_n5zadanie_ePriorytet_6 check (
ePriorytet between 0 and 4
)
go
alter table n5zadanie add constraint ENUM_n5zadanie_eTypterminRozp_7 check (
eTypterminRozp between 0 and 5
)
go
alter table n5zadanie add constraint ENUM_n5zadanie_eTypterminZak_10 check (
eTypterminZak between 0 and 5
)
go
alter table n5zadanie add constraint FK_n5zadanie_n5typdzialania_14 foreign key (pTypDzialania ) references n5typdzialania ( IdObj )
go
alter table n5zadanie add constraint WRT_n5zadanie_wrefSzczegoly_16 check (
	wrefSzczegoly_wrt=0 or 
	wrefSzczegoly_wrt=10129 or 
	wrefSzczegoly_wrt=10150 or 
	wrefSzczegoly_wrt=10148 or 
	wrefSzczegoly_wrt=10172 or 
	wrefSzczegoly_wrt=10176 or 
	wrefSzczegoly_wrt=10177 or 
	wrefSzczegoly_wrt=10187 or 
	wrefSzczegoly_wrt=10192 or 
	wrefSzczegoly_wrt=10203
)
go
alter table n5pozplatnosc add constraint FK_n5pozplatnosc_n5transakcja_7 foreign key (pTransakcja ) references n5transakcja ( IdObj )
go
alter table n5wykonawca add constraint WRT_n5wykonawca_wrefObiekt_3 check (
	wrefObiekt_wrt=10109 or 
	wrefObiekt_wrt=10112 or 
	wrefObiekt_wrt=10108
)
go
alter table choicelist add constraint ENUM_choicelist_edynamic_4 check (
edynamic between 0 and 2
)
go
alter table n5zadaniezal add constraint WRT_n5zadaniezal_wrefZal_2 check (
	wrefZal_wrt=10117 or 
	wrefZal_wrt=10119
)
go
alter table n5WizzardEmailDokumElem add constraint FK_n5WizzardEmailDokumElem_n5dokument_2 foreign key (pDokument ) references n5dokument ( IdObj )
go
alter table n5WizzardEmail add constraint FK_n5WizzardEmail_choicelist_2 foreign key (pChoiceList ) references choicelist ( IdObj )
go
alter table n5SendEmail add constraint WRT_n5SendEmail_wpNadawca_2 check (
	wpNadawca_wrt=0 or 
	wpNadawca_wrt=10112 or 
	wpNadawca_wrt=10109 or 
	wpNadawca_wrt=10108
)
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5sposplat_6 foreign key (pSposobPlatnosci ) references n5sposplat ( IdObj )
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5klient_7 foreign key (pKlient ) references n5klient ( IdObj )
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5uzytkownik_10 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5sprzedaz add constraint ENUM_n5sprzedaz_eSposVAT_12 check (
eSposVAT between 0 and 2
)
go
alter table n5sprzedaz add constraint ENUM_n5sprzedaz_eNettoBrutto_13 check (
eNettoBrutto between 0 and 2
)
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5rejestrdok_19 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5jednostka_51 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5sprzedaz add constraint FK_n5sprzedaz_n5rozlvat_52 foreign key (pRozlVat ) references n5rozlvat ( IdObj )
go
alter table n5opakowanie_produktu add constraint ENUM_n5opakowanie_produktu_eRodzaj_3 check (
eRodzaj between 0 and 2
)
go
alter table n5opakowanie_produktu add constraint FK_n5opakowanie_produktu_n5jednostka_10 foreign key (pJednostkaWagi ) references n5jednostka ( IdObj )
go
alter table n5opakowanie_produktu add constraint FK_n5opakowanie_produktu_n5jednostka_23 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5opakowanie_produktu add constraint FK_n5opakowanie_produktu_n5jednostka_25 foreign key (pJednOpak ) references n5jednostka ( IdObj )
go
alter table n5produkt add constraint ENUM_n5produkt_eVAT_7 check (
eVAT between 0 and 10
)
go
alter table n5produkt add constraint FK_n5produkt_n5jednostka_11 foreign key (pJednostkaEwid ) references n5jednostka ( IdObj )
go
alter table n5produkt add constraint ENUM_n5produkt_eAktywny_12 check (
eAktywny between 0 and 2
)
go
alter table n5produkt add constraint FK_n5produkt_n5grupaproduktow_14 foreign key (pGrupaProd ) references n5grupaproduktow ( IdObj )
go
alter table n5produkt add constraint ENUM_n5produkt_eRodzaj_19 check (
eRodzaj between 0 and 2
)
go
alter table n5pozsprzedaz add constraint FK_n5pozsprzedaz_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozsprzedaz add constraint FK_n5pozsprzedaz_n5opakowanie_produktu_4 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozsprzedaz add constraint ENUM_n5pozsprzedaz_eVAT_8 check (
eVAT between 0 and 10
)
go
alter table n5dokumentlinks add constraint FK_n5dokumentlinks_n5dokument_2 foreign key (pDokument ) references n5dokument ( IdObj )
go
alter table n5pkpir add constraint FK_n5pkpir_n5rejestrdok_4 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5rejestrdok add constraint ENUM_n5rejestrdok_eTyp_3 check (
eTyp between 0 and 46
)
go
alter table n5rejestrdok add constraint ENUM_n5rejestrdok_eAktywny_6 check (
eAktywny between 0 and 2
)
go
alter table n5rejestrdok add constraint WRT_n5rejestrdok_wrefParam1_13 check (
	wrefParam1_wrt=0 or 
	wrefParam1_wrt=10102 or 
	wrefParam1_wrt=10164 or 
	wrefParam1_wrt=10160
)
go
alter table n5rejestrdok add constraint WRT_n5rejestrdok_wrefParam2_14 check (
	wrefParam2_wrt=0 or 
	wrefParam2_wrt=10145 or 
	wrefParam2_wrt=10160
)
go
alter table n5konto add constraint FK_n5konto_n5jednostka_5 foreign key (pJednostka ) references n5jednostka ( IdObj )
go
alter table n5konto add constraint WRT_n5konto_wrefPodmiotRozrach_6 check (
	wrefPodmiotRozrach_wrt=0 or 
	wrefPodmiotRozrach_wrt=10108 or 
	wrefPodmiotRozrach_wrt=10109 or 
	wrefPodmiotRozrach_wrt=10105
)
go
alter table n5konto add constraint ENUM_n5konto_eAnalit_8 check (
eAnalit between 0 and 2
)
go
alter table n5konto add constraint ENUM_n5konto_eBilans_9 check (
eBilans between 0 and 2
)
go
alter table n5konto add constraint ENUM_n5konto_eAktywne_10 check (
eAktywne between 0 and 2
)
go
alter table n5dekret add constraint FK_n5dekret_n5konto_2 foreign key (pKonto ) references n5konto ( IdObj )
go
alter table n5dekret add constraint ENUM_n5dekret_eTyp_7 check (
eTyp between 0 and 4
)
go
alter table n5dekret add constraint ENUM_n5dekret_eStatus_8 check (
eStatus between 0 and 2
)
go
alter table n5dowodksieg add constraint ENUM_n5dowodksieg_eTyp_7 check (
eTyp between 0 and 4
)
go
alter table n5dowodksieg add constraint ENUM_n5dowodksieg_eStatus_8 check (
eStatus between 0 and 2
)
go
alter table n5dowodksieg add constraint FK_n5dowodksieg_n5uzytkownik_10 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5dowodksieg add constraint FK_n5dowodksieg_n5rejestrdok_11 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5dowodksieg add constraint WRT_n5dowodksieg_wrefDokZrod_12 check (
	wrefDokZrod_wrt=0 or 
	wrefDokZrod_wrt=10129 or 
	wrefDokZrod_wrt=10150 or 
	wrefDokZrod_wrt=10119 or 
	wrefDokZrod_wrt=10177 or 
	wrefDokZrod_wrt=10176 or 
	wrefDokZrod_wrt=10172 or 
	wrefDokZrod_wrt=10162
)
go
alter table n5platnosc add constraint WRT_n5platnosc_wrefPodmiot_3 check (
	wrefPodmiot_wrt=0 or 
	wrefPodmiot_wrt=10108 or 
	wrefPodmiot_wrt=10109 or 
	wrefPodmiot_wrt=10105 or 
	wrefPodmiot_wrt=10104 or 
	wrefPodmiot_wrt=10110
)
go
alter table n5platnosc add constraint FK_n5platnosc_n5uzytkownik_6 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5platnosc add constraint FK_n5platnosc_n5rejestrdok_7 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5platnosc add constraint FK_n5platnosc_n5jednostka_15 foreign key (pWalutaPodm ) references n5jednostka ( IdObj )
go
alter table n5platnosc add constraint ENUM_n5platnosc_eStatus_20 check (
eStatus between 0 and 2
)
go
alter table n5transakcja add constraint FK_n5transakcja_n5jednostka_3 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5transakcja add constraint WRT_n5transakcja_wrefPodmiot_4 check (
	wrefPodmiot_wrt=10108 or 
	wrefPodmiot_wrt=10109 or 
	wrefPodmiot_wrt=10105 or 
	wrefPodmiot_wrt=10104 or 
	wrefPodmiot_wrt=10110
)
go
alter table n5transakcja add constraint ENUM_n5transakcja_eTyp_10 check (
eTyp between 0 and 2
)
go
alter table n5transakcja add constraint ENUM_n5transakcja_eStatus_11 check (
eStatus between 0 and 2
)
go
alter table n5transakcja add constraint ENUM_n5transakcja_eTypOdset_14 check (
eTypOdset between 0 and 3
)
go
alter table n5schematdekr add constraint FK_n5schematdekr_n5rejestrdok_3 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5schematdekr add constraint FK_n5schematdekr_n5rejestrdok_4 foreign key (pDziennik ) references n5rejestrdok ( IdObj )
go
alter table n5schematdekr add constraint ENUM_n5schematdekr_eAktywny_7 check (
eAktywny between 0 and 2
)
go
alter table n5magazyn add constraint FK_n5magazyn_n5jednostka_3 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5magazyn add constraint ENUM_n5magazyn_eTyp_4 check (
eTyp between 0 and 5
)
go
alter table n5magazyn add constraint FK_n5magazyn_n5jedn_org_5 foreign key (pJednostkaOrg ) references n5jedn_org ( IdObj )
go
alter table n5pozdokmag add constraint FK_n5pozdokmag_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozdokmag add constraint FK_n5pozdokmag_n5opakowanie_produktu_3 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozdokmag add constraint FK_n5pozdokmag_n5jednostka_7 foreign key (pJednOpak ) references n5jednostka ( IdObj )
go
alter table n5pozdokmag add constraint FK_n5pozdokmag_n5jednostka_9 foreign key (pJednEwid ) references n5jednostka ( IdObj )
go
alter table n5dokmag add constraint FK_n5dokmag_n5uzytkownik_10 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5dokmag add constraint FK_n5dokmag_n5rejestrdok_13 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5dokmag add constraint WRT_n5dokmag_wrefDokHandl_21 check (
	wrefDokHandl_wrt=0 or 
	wrefDokHandl_wrt=10129 or 
	wrefDokHandl_wrt=10172 or 
	wrefDokHandl_wrt=10176 or 
	wrefDokHandl_wrt=10187
)
go
alter table n5zadaniedw add constraint FK_n5zadaniedw_n5wykonawca_2 foreign key (pWykonawcaDW ) references n5wykonawca ( IdObj )
go
alter table n5sposplat add constraint ENUM_n5sposplat_eTyp_4 check (
eTyp between 0 and 4
)
go
alter table n5kurswalut add constraint FK_n5kurswalut_n5jednostka_2 foreign key (pWalZ ) references n5jednostka ( IdObj )
go
alter table n5kurswalut add constraint FK_n5kurswalut_n5jednostka_3 foreign key (pWalN ) references n5jednostka ( IdObj )
go
alter table n5zamowienie add constraint FK_n5zamowienie_n5sposplat_7 foreign key (pSposobPlatnosci ) references n5sposplat ( IdObj )
go
alter table n5zamowienie add constraint FK_n5zamowienie_n5klient_8 foreign key (pKlient ) references n5klient ( IdObj )
go
alter table n5zamowienie add constraint FK_n5zamowienie_n5uzytkownik_11 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5zamowienie add constraint ENUM_n5zamowienie_eNettoBrutto_13 check (
eNettoBrutto between 0 and 2
)
go
alter table n5zamowienie add constraint FK_n5zamowienie_n5rejestrdok_19 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5zamowienie add constraint FK_n5zamowienie_n5jednostka_24 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5pozzamowienie add constraint FK_n5pozzamowienie_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozzamowienie add constraint FK_n5pozzamowienie_n5opakowanie_produktu_4 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozzamowienie add constraint ENUM_n5pozzamowienie_eVAT_8 check (
eVAT between 0 and 10
)
go
alter table n5pozzakup add constraint FK_n5pozzakup_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozzakup add constraint FK_n5pozzakup_n5opakowanie_produktu_4 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozzakup add constraint ENUM_n5pozzakup_eVAT_5 check (
eVAT between 0 and 10
)
go
alter table n5zakup add constraint FK_n5zakup_n5sposplat_8 foreign key (pSposobPlatnosci ) references n5sposplat ( IdObj )
go
alter table n5zakup add constraint FK_n5zakup_n5klient_9 foreign key (pDostawca ) references n5klient ( IdObj )
go
alter table n5zakup add constraint FK_n5zakup_n5uzytkownik_11 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5zakup add constraint FK_n5zakup_n5rejestrdok_18 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5zakup add constraint FK_n5zakup_n5jednostka_48 foreign key (pWaluta ) references n5jednostka ( IdObj )
go
alter table n5zakup add constraint ENUM_n5zakup_eZwOpSprz_49 check (
eZwOpSprz between 0 and 2
)
go
alter table n5zakup add constraint ENUM_n5zakup_eTypZakup_50 check (
eTypZakup between 0 and 3
)
go
alter table n5rozlvat add constraint FK_n5rozlvat_n5uzytkownik_52 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5srtrw add constraint FK_n5srtrw_n5grupasrtrw_6 foreign key (pGrupa ) references n5grupasrtrw ( IdObj )
go
alter table n5srtrw add constraint ENUM_n5srtrw_eRodzaj_8 check (
eRodzaj between 0 and 4
)
go
alter table n5srtrw add constraint ENUM_n5srtrw_eMetAmPod_19 check (
eMetAmPod between 0 and 5
)
go
alter table n5srtrw add constraint ENUM_n5srtrw_eMetAmBil_20 check (
eMetAmBil between 0 and 4
)
go
alter table n5srtrw add constraint ENUM_n5srtrw_eStatus_21 check (
eStatus between 0 and 6
)
go
alter table n5opmag add constraint ENUM_n5opmag_eTypPow_16 check (
eTypPow between 0 and 2
)
go
alter table n5koropmag add constraint ENUM_n5koropmag_eTypPow_16 check (
eTypPow between 0 and 2
)
go
alter table n5stanmag add constraint FK_n5stanmag_n5magazyn_2 foreign key (pMagazyn ) references n5magazyn ( IdObj )
go
alter table n5stanmag add constraint FK_n5stanmag_n5produkt_3 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5stanmag add constraint FK_n5stanmag_n5opakowanie_produktu_4 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozrecepta add constraint FK_n5pozrecepta_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozrecepta add constraint FK_n5pozrecepta_n5opakowanie_produktu_3 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5recepta add constraint FK_n5recepta_n5produkt_5 foreign key (pWyrob ) references n5produkt ( IdObj )
go
alter table n5recepta add constraint FK_n5recepta_n5opakowanie_produktu_6 foreign key (pWyrOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozzlecprod add constraint FK_n5pozzlecprod_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozzlecprod add constraint FK_n5pozzlecprod_n5opakowanie_produktu_3 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozzlecprod add constraint FK_n5pozzlecprod_n5recepta_4 foreign key (pRecepta ) references n5recepta ( IdObj )
go
alter table n5zlecprod add constraint FK_n5zlecprod_n5uzytkownik_4 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5zlecprod add constraint FK_n5zlecprod_n5rejestrdok_6 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5eventlog add constraint ENUM_n5eventlog_eTyp_2 check (
eTyp between 0 and 5
)
go
alter table n5eventlog add constraint FK_n5eventlog_n5uzytkownik_5 foreign key (pUser ) references n5uzytkownik ( IdObj )
go
alter table n5polrab add constraint WRT_n5polrab_wpProdGrupa_2 check (
	wpProdGrupa_wrt=0 or 
	wpProdGrupa_wrt=10131 or 
	wpProdGrupa_wrt=10116
)
go
alter table n5polrab add constraint WRT_n5polrab_wpKlientGrupa_4 check (
	wpKlientGrupa_wrt=0 or 
	wpKlientGrupa_wrt=10108 or 
	wpKlientGrupa_wrt=10118
)
go
alter table n5polrab add constraint ENUM_n5polrab_eTyp_10 check (
eTyp between 0 and 4
)
go
alter table n5plstawka add constraint FK_n5plstawka_n5jednostka_7 foreign key (pJednostka ) references n5jednostka ( IdObj )
go
alter table n5plnaliczenie add constraint FK_n5plnaliczenie_n5uzytkownik_6 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5plnaliczenie add constraint FK_n5plnaliczenie_n5rejestrdok_7 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5plnaliczenie add constraint FK_n5plnaliczenie_n5pllistaplac_10 foreign key (pListaPlac ) references n5pllistaplac ( IdObj )
go
alter table n5plsklnal add constraint FK_n5plsklnal_n5plschematnal_2 foreign key (pSchemat ) references n5plschematnal ( IdObj )
go
alter table n5plsubkonto add constraint ENUM_n5plsubkonto_eAktywne_5 check (
eAktywne between 0 and 2
)
go
alter table n5plsubkonto add constraint FK_n5plsubkonto_n5jednostka_6 foreign key (pJednostka ) references n5jednostka ( IdObj )
go
alter table n5pldekret add constraint FK_n5pldekret_n5pracownik_2 foreign key (pPracownik ) references n5pracownik ( IdObj )
go
alter table n5pldekret add constraint FK_n5pldekret_n5plsubkonto_3 foreign key (pSubKonto ) references n5plsubkonto ( IdObj )
go
alter table n5pldekret add constraint FK_n5pldekret_n5pllistaplac_7 foreign key (pListaPlac ) references n5pllistaplac ( IdObj )
go
alter table n5pldekret add constraint FK_n5pldekret_n5plnaliczenie_8 foreign key (pNaliczenie ) references n5plnaliczenie ( IdObj )
go
alter table n5pldekret add constraint FK_n5pldekret_n5plschematnal_9 foreign key (pSchematNal ) references n5plschematnal ( IdObj )
go
alter table n5pldekret add constraint WRT_n5pldekret_wrefDokument_10 check (
	wrefDokument_wrt=0 or 
	wrefDokument_wrt=10199 or 
	wrefDokument_wrt=10201 or 
	wrefDokument_wrt=10202
)
go
alter table n5plumowa add constraint FK_n5plumowa_n5uzytkownik_6 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5plumowa add constraint ENUM_n5plumowa_eTypUmowy_7 check (
eTypUmowy between 0 and 5
)
go
alter table n5plchoroba add constraint FK_n5plchoroba_n5uzytkownik_6 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5plchoroba add constraint FK_n5plchoroba_n5plumowa_7 foreign key (pUmowa ) references n5plumowa ( IdObj )
go
alter table n5plchoroba add constraint FK_n5plchoroba_n5plschematnal_8 foreign key (pSchemat ) references n5plschematnal ( IdObj )
go
alter table n5plnieob add constraint FK_n5plnieob_n5uzytkownik_6 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5plnieob add constraint FK_n5plnieob_n5plumowa_7 foreign key (pUmowa ) references n5plumowa ( IdObj )
go
alter table n5plnieob add constraint FK_n5plnieob_n5plschematnal_8 foreign key (pSchemat ) references n5plschematnal ( IdObj )
go
alter table n5plnieob add constraint ENUM_n5plnieob_eTyp_9 check (
eTyp between 0 and 14
)
go
alter table n5rozlcit add constraint FK_n5rozlcit_n5uzytkownik_34 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5rozlcit add constraint FK_n5rozlcit_n5zadanie_35 foreign key (pZadanie ) references n5zadanie ( IdObj )
go
alter table n5rule add constraint ENUM_n5rule_eSignificance_5 check (
eSignificance between 0 and 2
)
go
alter table n5pozrealprod add constraint FK_n5pozrealprod_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozrealprod add constraint FK_n5pozrealprod_n5opakowanie_produktu_3 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5pozrealprod add constraint FK_n5pozrealprod_n5jednostka_5 foreign key (pJednOpak ) references n5jednostka ( IdObj )
go
alter table n5pozrealprod add constraint FK_n5pozrealprod_n5jednostka_7 foreign key (pJednEwid ) references n5jednostka ( IdObj )
go
alter table n5realprod add constraint FK_n5realprod_n5produkt_4 foreign key (pWyrob ) references n5produkt ( IdObj )
go
alter table n5realprod add constraint FK_n5realprod_n5opakowanie_produktu_5 foreign key (pOpak ) references n5opakowanie_produktu ( IdObj )
go
alter table n5realprod add constraint FK_n5realprod_n5uzytkownik_9 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5realprod add constraint FK_n5realprod_n5rejestrdok_11 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5konto_budzet add constraint FK_n5konto_budzet_n5konto_2 foreign key (pKonto ) references n5konto ( IdObj )
go
alter table n5konto_budzet add constraint FK_n5konto_budzet_n5budzet_3 foreign key (pBudzet ) references n5budzet ( IdObj )
go
alter table n5konto_budzet add constraint ENUM_n5konto_budzet_eOdniesienie_5 check (
eOdniesienie between 0 and 6
)
go
alter table n5bwinfo add constraint ENUM_n5bwinfo_eStatus_6 check (
eStatus between 0 and 3
)
go
alter table n5bwinfo add constraint FK_n5bwinfo_n5bwinfo_kat_7 foreign key (pKategoria ) references n5bwinfo_kat ( IdObj )
go
alter table n5bwinfo add constraint FK_n5bwinfo_n5uzytkownik_15 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5bwinfo_produkt add constraint WRT_n5bwinfo_produkt_wpProdGrupa_2 check (
	wpProdGrupa_wrt=10131 or 
	wpProdGrupa_wrt=10116
)
go
alter table n5bwinfo_zal add constraint WRT_n5bwinfo_zal_wrefZal_2 check (
	wrefZal_wrt=10117 or 
	wrefZal_wrt=10211
)
go
alter table n5poznotaods add constraint FK_n5poznotaods_n5transakcja_2 foreign key (pTransakcja ) references n5transakcja ( IdObj )
go
alter table n5notaods add constraint FK_n5notaods_n5klient_4 foreign key (pKlient ) references n5klient ( IdObj )
go
alter table n5notaods add constraint FK_n5notaods_n5uzytkownik_5 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5notaods add constraint FK_n5notaods_n5rejestrdok_9 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5opsrtrw add constraint FK_n5opsrtrw_n5srtrw_2 foreign key (pSRTRW ) references n5srtrw ( IdObj )
go
alter table n5opsrtrw add constraint ENUM_n5opsrtrw_eRodzaj_5 check (
eRodzaj between 0 and 13
)
go
alter table n5opsrtrw add constraint FK_n5opsrtrw_n5uzytkownik_16 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5opsrtrw add constraint WRT_n5opsrtrw_wrefDokument_18 check (
	wrefDokument_wrt=0 or 
	wrefDokument_wrt=10216 or 
	wrefDokument_wrt=10176 or 
	wrefDokument_wrt=10129
)
go
alter table n5opsrtrw add constraint FK_n5opsrtrw_n5rejestrdok_19 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5plwzorlp add constraint ENUM_n5plwzorlp_eTypUmowy_3 check (
eTypUmowy between 0 and 5
)
go
alter table n5plwzorlp add constraint ENUM_n5plwzorlp_eAktywny_7 check (
eAktywny between 0 and 2
)
go
alter table n5plkalcp add constraint ENUM_n5plkalcp_eAktywny_3 check (
eAktywny between 0 and 2
)
go
alter table n5plpozkalcp add constraint ENUM_n5plpozkalcp_eTypOkresu_7 check (
eTypOkresu between 0 and 3
)
go
alter table n5plsklumowy add constraint FK_n5plsklumowy_n5plschematnal_2 foreign key (pSchemat ) references n5plschematnal ( IdObj )
go
alter table n5plsklnalzrod add constraint WRT_n5plsklnalzrod_wrefDokument_2 check (
	wrefDokument_wrt=0 or 
	wrefDokument_wrt=10199 or 
	wrefDokument_wrt=10201 or 
	wrefDokument_wrt=10202
)
go
alter table n5sod add constraint FK_n5sod_n5sodgroup_3 foreign key (pSODGroup ) references n5sodgroup ( IdObj )
go
alter table n5securityobj add constraint FK_n5securityobj_n5sod_2 foreign key (pSOD ) references n5sod ( IdObj )
go
alter table n5securityobj add constraint FK_n5securityobj_n5uzytkownik_3 foreign key (pUser ) references n5uzytkownik ( IdObj )
go
alter table n5dpc add constraint ENUM_n5dpc_ePubType_3 check (
ePubType between 0 and 21
)
go
alter table n5dpc add constraint ENUM_n5dpc_eChannel_4 check (
eChannel between 0 and 4
)
go
alter table n5dpc add constraint ENUM_n5dpc_eFormat_6 check (
eFormat between 0 and 2
)
go
alter table n5userprof add constraint FK_n5userprof_n5uzytkownik_4 foreign key (pn5user ) references n5uzytkownik ( IdObj )
go
alter table n5userfile add constraint FK_n5userfile_n5uzytkownik_3 foreign key (pUzytkownik ) references n5uzytkownik ( IdObj )
go
-- creating integrity test stored procedure

if exists (select * from sysobjects where name='n5check')
	drop procedure n5check
go

create procedure n5check with encryption as 
select 10122,n5wykonawca.IdObj, 1 from n5wykonawca
	left outer join n5pracownik on n5wykonawca.wrefObiekt=n5pracownik.IdObj and n5wykonawca.wrefObiekt_wrt=10109
	left outer join n5klient_pracownik on n5wykonawca.wrefObiekt=n5klient_pracownik.IdObj and n5wykonawca.wrefObiekt_wrt=10112
	left outer join n5klient on n5wykonawca.wrefObiekt=n5klient.IdObj and n5wykonawca.wrefObiekt_wrt=10108
 where 
	(n5pracownik.IdObj is null) and 
	(n5klient_pracownik.IdObj is null) and 
	(n5klient.IdObj is null)

select 10125,n5zadaniezal.IdObj, 1 from n5zadaniezal
	left outer join n5dokument on n5zadaniezal.wrefZal=n5dokument.IdObj and n5zadaniezal.wrefZal_wrt=10117
	left outer join n5zadanie on n5zadaniezal.wrefZal=n5zadanie.IdObj and n5zadaniezal.wrefZal_wrt=10119
 where 
	(n5dokument.IdObj is null) and 
	(n5zadanie.IdObj is null)

select 10154,n5transakcja.IdObj, 1 from n5transakcja
	left outer join n5klient on n5transakcja.wrefPodmiot=n5klient.IdObj and n5transakcja.wrefPodmiot_wrt=10108
	left outer join n5pracownik on n5transakcja.wrefPodmiot=n5pracownik.IdObj and n5transakcja.wrefPodmiot_wrt=10109
	left outer join n5instytucja on n5transakcja.wrefPodmiot=n5instytucja.IdObj and n5transakcja.wrefPodmiot_wrt=10105
	left outer join n5bank on n5transakcja.wrefPodmiot=n5bank.IdObj and n5transakcja.wrefPodmiot_wrt=10104
	left outer join n5firma on n5transakcja.wrefPodmiot=n5firma.IdObj and n5transakcja.wrefPodmiot_wrt=10110
 where 
	(n5klient.IdObj is null) and 
	(n5pracownik.IdObj is null) and 
	(n5instytucja.IdObj is null) and 
	(n5bank.IdObj is null) and 
	(n5firma.IdObj is null)

select 10212,n5bwinfo_produkt.IdObj, 1 from n5bwinfo_produkt
	left outer join n5produkt on n5bwinfo_produkt.wpProdGrupa=n5produkt.IdObj and n5bwinfo_produkt.wpProdGrupa_wrt=10131
	left outer join n5grupaproduktow on n5bwinfo_produkt.wpProdGrupa=n5grupaproduktow.IdObj and n5bwinfo_produkt.wpProdGrupa_wrt=10116
 where 
	(n5produkt.IdObj is null) and 
	(n5grupaproduktow.IdObj is null)

select 10213,n5bwinfo_zal.IdObj, 1 from n5bwinfo_zal
	left outer join n5dokument on n5bwinfo_zal.wrefZal=n5dokument.IdObj and n5bwinfo_zal.wrefZal_wrt=10117
	left outer join n5bwinfo on n5bwinfo_zal.wrefZal=n5bwinfo.IdObj and n5bwinfo_zal.wrefZal_wrt=10211
 where 
	(n5dokument.IdObj is null) and 
	(n5bwinfo.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

select 10107,t1.IdObj, 2 from n5uzytkownik t1 
 left outer join n5wykonawca t2 on t1.pWykonawca=t2.IdObj where (t1.pWykonawca<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5branza t2 on t1.pBranza=t2.IdObj where (t1.pBranza<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5miejscowosc t2 on t1.pMiejscowoscSDB=t2.IdObj where (t1.pMiejscowoscSDB<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5jednostka t2 on t1.pWalutaLimitu=t2.IdObj where (t1.pWalutaLimitu<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5sposplat t2 on t1.pSposobPlatnosci=t2.IdObj where (t1.pSposobPlatnosci<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowy=t2.IdObj where (t1.pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowyVAT=t2.IdObj where (t1.pUrzadSkarbowyVAT<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowyPD=t2.IdObj where (t1.pUrzadSkarbowyPD<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5instytucja t2 on t1.pZUS=t2.IdObj where (t1.pZUS<>0 and t2.IdObj is null)

select 10111,t1.IdObj, 2 from n5miejscowosc t1 
 left outer join n5region t2 on t1.pRegion=t2.IdObj where (t1.pRegion<>0 and t2.IdObj is null)

select 10112,t1.IdObj, 2 from n5klient_pracownik t1 
 left outer join n5_klient_jedn_org t2 on t1.pJednOrgKlienta=t2.IdObj where (t1.pJednOrgKlienta<>0 and t2.IdObj is null)

select 10112,t1.IdObj, 2 from n5klient_pracownik t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10113,t1.IdObj, 2 from n5jedn_org t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10113,t1.IdObj, 2 from n5jedn_org t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10113,t1.IdObj, 2 from n5jedn_org t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

select 10113,t1.IdObj, 2 from n5jedn_org t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10113,t1.IdObj, 2 from n5jedn_org t1 
 left outer join n5jedn_org t2 on t1.p_Jend_Org_Nadrzedna=t2.IdObj where (t1.p_Jend_Org_Nadrzedna<>0 and t2.IdObj is null)

select 10114,t1.IdObj, 2 from n5_klient_jedn_org t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10114,t1.IdObj, 2 from n5_klient_jedn_org t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10114,t1.IdObj, 2 from n5_klient_jedn_org t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

select 10114,t1.IdObj, 2 from n5_klient_jedn_org t1 
 left outer join n5_klient_jedn_org t2 on t1.p_Klient_JO_Nadrzedna=t2.IdObj where (t1.p_Klient_JO_Nadrzedna<>0 and t2.IdObj is null)

select 10114,t1.IdObj, 2 from n5_klient_jedn_org t1 
 left outer join n5klient_pracownik t2 on t1.pKlientPracownik=t2.IdObj where (t1.pKlientPracownik<>0 and t2.IdObj is null)

select 10115,t1.IdObj, 2 from n5typdokumentu t1 
 left outer join n5typdokumentu t2 on t1.pTypNadrzedny=t2.IdObj where (t1.pTypNadrzedny<>0 and t2.IdObj is null)

select 10116,t1.IdObj, 2 from n5grupaproduktow t1 
 left outer join n5grupaproduktow t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5uzytkownik t2 on t1.pUzytkWypoz=t2.IdObj where (t1.pUzytkWypoz<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5dokument t2 on t1.pReplaces=t2.IdObj where (t1.pReplaces<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5dokument t2 on t1.pReplaced=t2.IdObj where (t1.pReplaced<>0 and t2.IdObj is null)

select 10118,t1.IdObj, 2 from n5grupaklient t1 
 left outer join n5grupaklient t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10118,t1.IdObj, 2 from n5grupaklient t1 
 left outer join n5jednostka t2 on t1.pWalutaLimitu=t2.IdObj where (t1.pWalutaLimitu<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5procedura t2 on t1.pProcedura=t2.IdObj where (t1.pProcedura<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5zadanie t2 on t1.pNadZadanie=t2.IdObj where (t1.pNadZadanie<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5zadanie t2 on t1.pPopZadanie=t2.IdObj where (t1.pPopZadanie<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5wykonawca t2 on t1.pWykonawca=t2.IdObj where (t1.pWykonawca<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5klient t2 on t1.pKlient=t2.IdObj where (t1.pKlient<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5schematdekr t2 on t1.pSchematDekretacji=t2.IdObj where (t1.pSchematDekretacji<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5dowodksieg t2 on t1.pDowKsieg=t2.IdObj where (t1.pDowKsieg<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5klient_pracownik t2 on t1.pKlientPracownik=t2.IdObj where (t1.pKlientPracownik<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5_klient_jedn_org t2 on t1.pKlient_JO=t2.IdObj where (t1.pKlient_JO<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5klient_pracownik t2 on t1.pKlientPracownik=t2.IdObj where (t1.pKlientPracownik<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5sprzedaz t2 on t1.pPopSprzed=t2.IdObj where (t1.pPopSprzed<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5sprzedaz t2 on t1.pFaktura=t2.IdObj where (t1.pFaktura<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5zamowienie t2 on t1.pZamowienie=t2.IdObj where (t1.pZamowienie<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakowanieJedn=t2.IdObj where (t1.pOpakowanieJedn<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5opakowanie_produktu t2 on t1.pZamiennik=t2.IdObj where (t1.pZamiennik<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5dokument t2 on t1.pUlotka=t2.IdObj where (t1.pUlotka<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5dokument t2 on t1.pInstrukcja=t2.IdObj where (t1.pInstrukcja<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10134,t1.IdObj, 2 from n5pkpir t1 
 left outer join n5klient t2 on t1.pKlient=t2.IdObj where (t1.pKlient<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5schematdekr t2 on t1.pDefSchematdekr=t2.IdObj where (t1.pDefSchematdekr<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5rokksieg t2 on t1.pRokKsieg=t2.IdObj where (t1.pRokKsieg<>0 and t2.IdObj is null)

select 10146,t1.IdObj, 2 from n5konto t1 
 left outer join n5konto t2 on t1.pKontoNadrz=t2.IdObj where (t1.pKontoNadrz<>0 and t2.IdObj is null)

select 10147,t1.IdObj, 2 from n5dekret t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10147,t1.IdObj, 2 from n5dekret t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikator=t2.IdObj where (t1.pKwalifikator<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10153,t1.IdObj, 2 from n5typdzialania t1 
 left outer join n5typdzialania t2 on t1.pTypNadrzedny=t2.IdObj where (t1.pTypNadrzedny<>0 and t2.IdObj is null)

select 10154,t1.IdObj, 2 from n5transakcja t1 
 left outer join n5notaods t2 on t1.pNotaOds=t2.IdObj where (t1.pNotaOds<>0 and t2.IdObj is null)

select 10157,t1.IdObj, 2 from n5branza t1 
 left outer join n5branza t2 on t1.pBranzaNad=t2.IdObj where (t1.pBranzaNad<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5magazyn t2 on t1.pMagZrod=t2.IdObj where (t1.pMagZrod<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5magazyn t2 on t1.pMagDocel=t2.IdObj where (t1.pMagDocel<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5klient t2 on t1.pKlient=t2.IdObj where (t1.pKlient<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5_klient_jedn_org t2 on t1.pKlient_JO=t2.IdObj where (t1.pKlient_JO<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5klient_pracownik t2 on t1.pKlientPracownik=t2.IdObj where (t1.pKlientPracownik<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5dokmag t2 on t1.pDokMag=t2.IdObj where (t1.pDokMag<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5magazyn t2 on t1.pMagZrod=t2.IdObj where (t1.pMagZrod<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5magazyn t2 on t1.pMagDocel=t2.IdObj where (t1.pMagDocel<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5_klient_jedn_org t2 on t1.pKlient_JO=t2.IdObj where (t1.pKlient_JO<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5klient_pracownik t2 on t1.pKlientPracownik=t2.IdObj where (t1.pKlientPracownik<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10173,t1.IdObj, 2 from n5pozzamowienie t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10175,t1.IdObj, 2 from n5pozzakup t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5_klient_jedn_org t2 on t1.pDostawca_JO=t2.IdObj where (t1.pDostawca_JO<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5zakup t2 on t1.pPopZAkup=t2.IdObj where (t1.pPopZAkup<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5rozlvat t2 on t1.pRozlVat=t2.IdObj where (t1.pRozlVat<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5dowodksieg t2 on t1.pDowKsieg=t2.IdObj where (t1.pDowKsieg<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowy=t2.IdObj where (t1.pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10178,t1.IdObj, 2 from n5grupasrtrw t1 
 left outer join n5grupasrtrw t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10179,t1.IdObj, 2 from n5srtrw t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10179,t1.IdObj, 2 from n5srtrw t1 
 left outer join n5jedn_org t2 on t1.pMUJO=t2.IdObj where (t1.pMUJO<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5produkt t2 on t1.pProdZrod=t2.IdObj where (t1.pProdZrod<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakZrod=t2.IdObj where (t1.pOpakZrod<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5magazyn t2 on t1.pMagZrod=t2.IdObj where (t1.pMagZrod<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5produkt t2 on t1.pProdDocel=t2.IdObj where (t1.pProdDocel<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakDocel=t2.IdObj where (t1.pOpakDocel<>0 and t2.IdObj is null)

select 10180,t1.IdObj, 2 from n5opmag t1 
 left outer join n5magazyn t2 on t1.pMagDocel=t2.IdObj where (t1.pMagDocel<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5produkt t2 on t1.pProdZrod=t2.IdObj where (t1.pProdZrod<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakZrod=t2.IdObj where (t1.pOpakZrod<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5magazyn t2 on t1.pMagZrod=t2.IdObj where (t1.pMagZrod<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5produkt t2 on t1.pProdDocel=t2.IdObj where (t1.pProdDocel<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakDocel=t2.IdObj where (t1.pOpakDocel<>0 and t2.IdObj is null)

select 10181,t1.IdObj, 2 from n5koropmag t1 
 left outer join n5magazyn t2 on t1.pMagDocel=t2.IdObj where (t1.pMagDocel<>0 and t2.IdObj is null)

select 10186,t1.IdObj, 2 from n5pozzlecprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5klient t2 on t1.pKlient=t2.IdObj where (t1.pKlient<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5_klient_jedn_org t2 on t1.pKlient_JO=t2.IdObj where (t1.pKlient_JO<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5zamowienie t2 on t1.pZamowienie=t2.IdObj where (t1.pZamowienie<>0 and t2.IdObj is null)

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10189,t1.IdObj, 2 from n5polrab t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpak=t2.IdObj where (t1.pOpak<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5plumowa t2 on t1.pUmowaPop=t2.IdObj where (t1.pUmowaPop<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5plkalcp t2 on t1.pKalendarz=t2.IdObj where (t1.pKalendarz<>0 and t2.IdObj is null)

select 10201,t1.IdObj, 2 from n5plchoroba t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10202,t1.IdObj, 2 from n5plnieob t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5dowodksieg t2 on t1.pDowKsieg=t2.IdObj where (t1.pDowKsieg<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowy=t2.IdObj where (t1.pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10205,t1.IdObj, 2 from n5pozrealprod t1 
 left outer join n5magazyn t2 on t1.pMagazyn=t2.IdObj where (t1.pMagazyn<>0 and t2.IdObj is null)

select 10205,t1.IdObj, 2 from n5pozrealprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5magazyn t2 on t1.pMagazyn=t2.IdObj where (t1.pMagazyn<>0 and t2.IdObj is null)

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5zlecprod t2 on t1.pZlecProd=t2.IdObj where (t1.pZlecProd<>0 and t2.IdObj is null)

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10212,t1.IdObj, 2 from n5bwinfo_produkt t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpak=t2.IdObj where (t1.pOpak<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5jedn_org t2 on t1.pMUJO=t2.IdObj where (t1.pMUJO<>0 and t2.IdObj is null)

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10217,t1.IdObj, 2 from n5plwzorlp t1 
 left outer join choicelist t2 on t1.pCLPracownicy=t2.IdObj where (t1.pCLPracownicy<>0 and t2.IdObj is null)

select 10217,t1.IdObj, 2 from n5plwzorlp t1 
 left outer join choicelist t2 on t1.pCLSkladniki=t2.IdObj where (t1.pCLSkladniki<>0 and t2.IdObj is null)

select 10004,t1.IdObj, 2 from n5sodgroup t1 
 left outer join n5sodgroup t2 on t1.pSODGroup=t2.IdObj where (t1.pSODGroup<>0 and t2.IdObj is null)

select 10008,t1.IdObj, 2 from n5dpc t1 
 left outer join n5dokument t2 on t1.pDocTemplate=t2.IdObj where (t1.pDocTemplate<>0 and t2.IdObj is null)

select idcollection, idparent,3 from collections group by idcollection, idparent having max(lp) > count(*)
select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokument on collections.idparent=n5dokument.idobj where idcollection=10117023 and n5dokument.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zadanie on collections.idparent=n5zadanie.idobj where idcollection=10119035 and n5zadanie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zadanie on collections.idparent=n5zadanie.idobj where idcollection=10119041 and n5zadanie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join choicelist on collections.idparent=choicelist.idobj where idcollection=10124004 and choicelist.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5WizzardEmail on collections.idparent=n5WizzardEmail.idobj where idcollection=10127002 and n5WizzardEmail.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5SendEmail on collections.idparent=n5SendEmail.idobj where idcollection=10128002 and n5SendEmail.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5sprzedaz on collections.idparent=n5sprzedaz.idobj where idcollection=10129013 and n5sprzedaz.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5produkt on collections.idparent=n5produkt.idobj where idcollection=10131012 and n5produkt.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dowodksieg on collections.idparent=n5dowodksieg.idobj where idcollection=10148008 and n5dowodksieg.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5platnosc on collections.idparent=n5platnosc.idobj where idcollection=10150010 and n5platnosc.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokmag on collections.idparent=n5dokmag.idobj where idcollection=10162011 and n5dokmag.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zamowienie on collections.idparent=n5zamowienie.idobj where idcollection=10172013 and n5zamowienie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zakup on collections.idparent=n5zakup.idobj where idcollection=10176012 and n5zakup.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185007 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185008 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zlecprod on collections.idparent=n5zlecprod.idobj where idcollection=10187012 and n5zlecprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plnaliczenie on collections.idparent=n5plnaliczenie.idobj where idcollection=10192012 and n5plnaliczenie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plnaliczenie on collections.idparent=n5plnaliczenie.idobj where idcollection=10192013 and n5plnaliczenie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plumowa on collections.idparent=n5plumowa.idobj where idcollection=10199007 and n5plumowa.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206009 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211007 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211009 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211012 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211015 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5notaods on collections.idparent=n5notaods.idobj where idcollection=10215007 and n5notaods.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plkalcp on collections.idparent=n5plkalcp.idobj where idcollection=10218003 and n5plkalcp.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002003 and SearchType.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002004 and SearchType.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002005 and SearchType.idobj is null

select collections.idcollection, collections.idobj,5 from collections left outer join n5dokumentlinks on collections.idobj=n5dokumentlinks.idobj where idcollection=10117023 and (n5dokumentlinks.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5zadaniezal on collections.idobj=n5zadaniezal.idobj where idcollection=10119035 and (n5zadaniezal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5zadaniedw on collections.idobj=n5zadaniedw.idobj where idcollection=10119041 and (n5zadaniedw.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join choicelistitem on collections.idobj=choicelistitem.idobj where idcollection=10124004 and (choicelistitem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5WizzardEmailDokumElem on collections.idobj=n5WizzardEmailDokumElem.idobj where idcollection=10127002 and (n5WizzardEmailDokumElem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5WizzardEmailDokumElem on collections.idobj=n5WizzardEmailDokumElem.idobj where idcollection=10128002 and (n5WizzardEmailDokumElem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozsprzedaz on collections.idobj=n5pozsprzedaz.idobj where idcollection=10129013 and (n5pozsprzedaz.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5opakowanie_produktu on collections.idobj=n5opakowanie_produktu.idobj where idcollection=10131012 and (n5opakowanie_produktu.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5dekret on collections.idobj=n5dekret.idobj where idcollection=10148008 and (n5dekret.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozplatnosc on collections.idobj=n5pozplatnosc.idobj where idcollection=10150010 and (n5pozplatnosc.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokmag on collections.idobj=n5pozdokmag.idobj where idcollection=10162011 and (n5pozdokmag.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzamowienie on collections.idobj=n5pozzamowienie.idobj where idcollection=10172013 and (n5pozzamowienie.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzakup on collections.idobj=n5pozzakup.idobj where idcollection=10176012 and (n5pozzakup.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta on collections.idobj=n5pozrecepta.idobj where idcollection=10185007 and (n5pozrecepta.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta on collections.idobj=n5pozrecepta.idobj where idcollection=10185008 and (n5pozrecepta.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzlecprod on collections.idobj=n5pozzlecprod.idobj where idcollection=10187012 and (n5pozzlecprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklnalzrod on collections.idobj=n5plsklnalzrod.idobj where idcollection=10192012 and (n5plsklnalzrod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklnal on collections.idobj=n5plsklnal.idobj where idcollection=10192013 and (n5plsklnal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklumowy on collections.idobj=n5plsklumowy.idobj where idcollection=10199007 and (n5plsklumowy.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrealprod on collections.idobj=n5pozrealprod.idobj where idcollection=10206009 and (n5pozrealprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_produkt on collections.idobj=n5bwinfo_produkt.idobj where idcollection=10211007 and (n5bwinfo_produkt.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211009 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211012 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211015 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5poznotaods on collections.idobj=n5poznotaods.idobj where idcollection=10215007 and (n5poznotaods.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plpozkalcp on collections.idobj=n5plpozkalcp.idobj where idcollection=10218003 and (n5plpozkalcp.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002003 and (SearchTypeItem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002004 and (SearchTypeItem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002005 and (SearchTypeItem.idobj is null)

select 10133,n5dokumentlinks.idobj,6 from n5dokumentlinks where n5dokumentlinks.idobj not in (select collections.idobj from collections where collections.idcollection=10117023)

select 10125,n5zadaniezal.idobj,6 from n5zadaniezal where n5zadaniezal.idobj not in (select collections.idobj from collections where collections.idcollection=10119035)

select 10163,n5zadaniedw.idobj,6 from n5zadaniedw where n5zadaniedw.idobj not in (select collections.idobj from collections where collections.idcollection=10119041)

select 10123,choicelistitem.idobj,6 from choicelistitem where choicelistitem.idobj not in (select collections.idobj from collections where collections.idcollection=10124004)

select 10126,n5WizzardEmailDokumElem.idobj,6 from n5WizzardEmailDokumElem where n5WizzardEmailDokumElem.idobj not in (select collections.idobj from collections where collections.idcollection=10127002)

select 10126,n5WizzardEmailDokumElem.idobj,6 from n5WizzardEmailDokumElem where n5WizzardEmailDokumElem.idobj not in (select collections.idobj from collections where collections.idcollection=10128002)

select 10132,n5pozsprzedaz.idobj,6 from n5pozsprzedaz where n5pozsprzedaz.idobj not in (select collections.idobj from collections where collections.idcollection=10129013)

select 10130,n5opakowanie_produktu.idobj,6 from n5opakowanie_produktu where n5opakowanie_produktu.idobj not in (select collections.idobj from collections where collections.idcollection=10131012)

select 10147,n5dekret.idobj,6 from n5dekret where n5dekret.idobj not in (select collections.idobj from collections where collections.idcollection=10148008)

select 10121,n5pozplatnosc.idobj,6 from n5pozplatnosc where n5pozplatnosc.idobj not in (select collections.idobj from collections where collections.idcollection=10150010)

select 10161,n5pozdokmag.idobj,6 from n5pozdokmag where n5pozdokmag.idobj not in (select collections.idobj from collections where collections.idcollection=10162011)

select 10173,n5pozzamowienie.idobj,6 from n5pozzamowienie where n5pozzamowienie.idobj not in (select collections.idobj from collections where collections.idcollection=10172013)

select 10175,n5pozzakup.idobj,6 from n5pozzakup where n5pozzakup.idobj not in (select collections.idobj from collections where collections.idcollection=10176012)

select 10184,n5pozrecepta.idobj,6 from n5pozrecepta where n5pozrecepta.idobj not in (select collections.idobj from collections where collections.idcollection=10185007)

select 10184,n5pozrecepta.idobj,6 from n5pozrecepta where n5pozrecepta.idobj not in (select collections.idobj from collections where collections.idcollection=10185008)

select 10186,n5pozzlecprod.idobj,6 from n5pozzlecprod where n5pozzlecprod.idobj not in (select collections.idobj from collections where collections.idcollection=10187012)

select 10221,n5plsklnalzrod.idobj,6 from n5plsklnalzrod where n5plsklnalzrod.idobj not in (select collections.idobj from collections where collections.idcollection=10192012)

select 10193,n5plsklnal.idobj,6 from n5plsklnal where n5plsklnal.idobj not in (select collections.idobj from collections where collections.idcollection=10192013)

select 10220,n5plsklumowy.idobj,6 from n5plsklumowy where n5plsklumowy.idobj not in (select collections.idobj from collections where collections.idcollection=10199007)

select 10205,n5pozrealprod.idobj,6 from n5pozrealprod where n5pozrealprod.idobj not in (select collections.idobj from collections where collections.idcollection=10206009)

select 10212,n5bwinfo_produkt.idobj,6 from n5bwinfo_produkt where n5bwinfo_produkt.idobj not in (select collections.idobj from collections where collections.idcollection=10211007)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211009)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211012)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211015)

select 10214,n5poznotaods.idobj,6 from n5poznotaods where n5poznotaods.idobj not in (select collections.idobj from collections where collections.idcollection=10215007)

select 10219,n5plpozkalcp.idobj,6 from n5plpozkalcp where n5plpozkalcp.idobj not in (select collections.idobj from collections where collections.idcollection=10218003)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002003)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002004)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002005)


go


--INJECT B here -- 
-- creating indices (UQ)

if exists (select * from sysindexes where name='UQ_n5wojewodztwo_strNazwa')
	drop index n5wojewodztwo.UQ_n5wojewodztwo_strNazwa
go

create unique index UQ_n5wojewodztwo_strNazwa on n5wojewodztwo (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5region_strNazwa')
	drop index n5region.UQ_n5region_strNazwa
go

create unique index UQ_n5region_strNazwa on n5region (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5jednostka_strSkrot')
	drop index n5jednostka.UQ_n5jednostka_strSkrot
go

create unique index UQ_n5jednostka_strSkrot on n5jednostka (strSkrot)
go

if exists (select * from sysindexes where name='UQ_n5kraj_strSkrot')
	drop index n5kraj.UQ_n5kraj_strSkrot
go

create unique index UQ_n5kraj_strSkrot on n5kraj (strSkrot)
go

if exists (select * from sysindexes where name='UQ_n5licencja_strKod')
	drop index n5licencja.UQ_n5licencja_strKod
go

create unique index UQ_n5licencja_strKod on n5licencja (strKod)
go

if exists (select * from sysindexes where name='UQ_n5uzytkownik_strNazwa')
	drop index n5uzytkownik.UQ_n5uzytkownik_strNazwa
go

create unique index UQ_n5uzytkownik_strNazwa on n5uzytkownik (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5uzytkownik_strLogin')
	drop index n5uzytkownik.UQ_n5uzytkownik_strLogin
go

create unique index UQ_n5uzytkownik_strLogin on n5uzytkownik (strLogin)
go

if exists (select * from sysindexes where name='UQ_n5klient_strIndeks')
	drop index n5klient.UQ_n5klient_strIndeks
go

create unique index UQ_n5klient_strIndeks on n5klient (strIndeks)
go

if exists (select * from sysindexes where name='UQ_n5miejscowosc_strNazwa')
	drop index n5miejscowosc.UQ_n5miejscowosc_strNazwa
go

create unique index UQ_n5miejscowosc_strNazwa on n5miejscowosc (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5jedn_org_strNazwa')
	drop index n5jedn_org.UQ_n5jedn_org_strNazwa
go

create unique index UQ_n5jedn_org_strNazwa on n5jedn_org (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5typdokumentu_strNazwa')
	drop index n5typdokumentu.UQ_n5typdokumentu_strNazwa
go

create unique index UQ_n5typdokumentu_strNazwa on n5typdokumentu (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5grupaproduktow_strNazwa')
	drop index n5grupaproduktow.UQ_n5grupaproduktow_strNazwa
go

create unique index UQ_n5grupaproduktow_strNazwa on n5grupaproduktow (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5dokument_strNumDok')
	drop index n5dokument.UQ_n5dokument_strNumDok
go

create unique index UQ_n5dokument_strNumDok on n5dokument (strNumDok)
go

if exists (select * from sysindexes where name='UQ_n5grupaklient_strNazwa')
	drop index n5grupaklient.UQ_n5grupaklient_strNazwa
go

create unique index UQ_n5grupaklient_strNazwa on n5grupaklient (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5procedura_strNazwa')
	drop index n5procedura.UQ_n5procedura_strNazwa
go

create unique index UQ_n5procedura_strNazwa on n5procedura (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5wykonawca_strIndeks')
	drop index n5wykonawca.UQ_n5wykonawca_strIndeks
go

create unique index UQ_n5wykonawca_strIndeks on n5wykonawca (strIndeks)
go

if exists (select * from sysindexes where name='UQ_n5sprzedaz_strNrDok')
	drop index n5sprzedaz.UQ_n5sprzedaz_strNrDok
go

create unique index UQ_n5sprzedaz_strNrDok on n5sprzedaz (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5produkt_strIndeks')
	drop index n5produkt.UQ_n5produkt_strIndeks
go

create unique index UQ_n5produkt_strIndeks on n5produkt (strIndeks)
go

if exists (select * from sysindexes where name='UQ_n5typinstytucji_strNazwa')
	drop index n5typinstytucji.UQ_n5typinstytucji_strNazwa
go

create unique index UQ_n5typinstytucji_strNazwa on n5typinstytucji (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5analfinans_strNazwa')
	drop index n5analfinans.UQ_n5analfinans_strNazwa
go

create unique index UQ_n5analfinans_strNazwa on n5analfinans (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5rejestrdok_strNazwa')
	drop index n5rejestrdok.UQ_n5rejestrdok_strNazwa
go

create unique index UQ_n5rejestrdok_strNazwa on n5rejestrdok (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5konto_strSymbol')
	drop index n5konto.UQ_n5konto_strSymbol
go

create unique index UQ_n5konto_strSymbol on n5konto (strSymbol)
go

if exists (select * from sysindexes where name='UQ_n5dowodksieg_strNrDok')
	drop index n5dowodksieg.UQ_n5dowodksieg_strNrDok
go

create unique index UQ_n5dowodksieg_strNrDok on n5dowodksieg (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5platnosc_strNrDok')
	drop index n5platnosc.UQ_n5platnosc_strNrDok
go

create unique index UQ_n5platnosc_strNrDok on n5platnosc (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5typdzialania_strNazwa')
	drop index n5typdzialania.UQ_n5typdzialania_strNazwa
go

create unique index UQ_n5typdzialania_strNazwa on n5typdzialania (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5transakcja_strSymTrans')
	drop index n5transakcja.UQ_n5transakcja_strSymTrans
go

create unique index UQ_n5transakcja_strSymTrans on n5transakcja (strSymTrans)
go

if exists (select * from sysindexes where name='UQ_n5branza_strNazwa')
	drop index n5branza.UQ_n5branza_strNazwa
go

create unique index UQ_n5branza_strNazwa on n5branza (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5magazyn_strNazwa')
	drop index n5magazyn.UQ_n5magazyn_strNazwa
go

create unique index UQ_n5magazyn_strNazwa on n5magazyn (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5dokmag_strNrDok')
	drop index n5dokmag.UQ_n5dokmag_strNrDok
go

create unique index UQ_n5dokmag_strNrDok on n5dokmag (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5dokmag_nNumOper')
	drop index n5dokmag.UQ_n5dokmag_nNumOper
go

create unique index UQ_n5dokmag_nNumOper on n5dokmag (nNumOper)
go

if exists (select * from sysindexes where name='UQ_n5sposplat_strNazwa')
	drop index n5sposplat.UQ_n5sposplat_strNazwa
go

create unique index UQ_n5sposplat_strNazwa on n5sposplat (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5zamowienie_strNrDok')
	drop index n5zamowienie.UQ_n5zamowienie_strNrDok
go

create unique index UQ_n5zamowienie_strNrDok on n5zamowienie (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5zakup_strNrDok')
	drop index n5zakup.UQ_n5zakup_strNrDok
go

create unique index UQ_n5zakup_strNrDok on n5zakup (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5grupasrtrw_strNazwa')
	drop index n5grupasrtrw.UQ_n5grupasrtrw_strNazwa
go

create unique index UQ_n5grupasrtrw_strNazwa on n5grupasrtrw (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5srtrw_strNumEwid')
	drop index n5srtrw.UQ_n5srtrw_strNumEwid
go

create unique index UQ_n5srtrw_strNumEwid on n5srtrw (strNumEwid)
go

if exists (select * from sysindexes where name='UQ_n5recepta_strNazwa')
	drop index n5recepta.UQ_n5recepta_strNazwa
go

create unique index UQ_n5recepta_strNazwa on n5recepta (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5zlecprod_strNrDok')
	drop index n5zlecprod.UQ_n5zlecprod_strNrDok
go

create unique index UQ_n5zlecprod_strNrDok on n5zlecprod (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5pllistaplac_strNrDok')
	drop index n5pllistaplac.UQ_n5pllistaplac_strNrDok
go

create unique index UQ_n5pllistaplac_strNrDok on n5pllistaplac (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5plgrzas_strNazwa')
	drop index n5plgrzas.UQ_n5plgrzas_strNazwa
go

create unique index UQ_n5plgrzas_strNazwa on n5plgrzas (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5plsubkonto_strNazwa')
	drop index n5plsubkonto.UQ_n5plsubkonto_strNazwa
go

create unique index UQ_n5plsubkonto_strNazwa on n5plsubkonto (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5plsubkonto_strKod')
	drop index n5plsubkonto.UQ_n5plsubkonto_strKod
go

create unique index UQ_n5plsubkonto_strKod on n5plsubkonto (strKod)
go

if exists (select * from sysindexes where name='UQ_n5realprod_strNrDok')
	drop index n5realprod.UQ_n5realprod_strNrDok
go

create unique index UQ_n5realprod_strNrDok on n5realprod (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5realprod_nNumOper')
	drop index n5realprod.UQ_n5realprod_nNumOper
go

create unique index UQ_n5realprod_nNumOper on n5realprod (nNumOper)
go

if exists (select * from sysindexes where name='UQ_n5kwalifikator_strNazwa')
	drop index n5kwalifikator.UQ_n5kwalifikator_strNazwa
go

create unique index UQ_n5kwalifikator_strNazwa on n5kwalifikator (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5bwinfo_strNrInfo')
	drop index n5bwinfo.UQ_n5bwinfo_strNrInfo
go

create unique index UQ_n5bwinfo_strNrInfo on n5bwinfo (strNrInfo)
go

if exists (select * from sysindexes where name='UQ_n5notaods_strNrDok')
	drop index n5notaods.UQ_n5notaods_strNrDok
go

create unique index UQ_n5notaods_strNrDok on n5notaods (strNrDok)
go

if exists (select * from sysindexes where name='UQ_n5plwzorlp_strNazwa')
	drop index n5plwzorlp.UQ_n5plwzorlp_strNazwa
go

create unique index UQ_n5plwzorlp_strNazwa on n5plwzorlp (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5plkalcp_strNazwa')
	drop index n5plkalcp.UQ_n5plkalcp_strNazwa
go

create unique index UQ_n5plkalcp_strNazwa on n5plkalcp (strNazwa)
go

if exists (select * from sysindexes where name='UQ_SearchType_Nazwa')
	drop index SearchType.UQ_SearchType_Nazwa
go

create unique index UQ_SearchType_Nazwa on SearchType (Nazwa)
go

if exists (select * from sysindexes where name='UQ_n5sodgroup_strNazwa')
	drop index n5sodgroup.UQ_n5sodgroup_strNazwa
go

create unique index UQ_n5sodgroup_strNazwa on n5sodgroup (strNazwa)
go

if exists (select * from sysindexes where name='UQ_n5globprof_Indeks')
	drop index n5globprof.UQ_n5globprof_Indeks
go

create unique index UQ_n5globprof_Indeks on n5globprof (Indeks)
go

if exists (select * from sysindexes where name='UQ_n5globfile_nIndeks')
	drop index n5globfile.UQ_n5globfile_nIndeks
go

create unique index UQ_n5globfile_nIndeks on n5globfile (nIndeks)
go

-- creating indices (FKI)

if exists (select * from sysindexes where name='FKI_n5kraj_pWaluta')
	drop index n5kraj.FKI_n5kraj_pWaluta
go

create index FKI_n5kraj_pWaluta on n5kraj (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5bank_pMiejscowosc')
	drop index n5bank.FKI_n5bank_pMiejscowosc
go

create index FKI_n5bank_pMiejscowosc on n5bank (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pTyp')
	drop index n5instytucja.FKI_n5instytucja_pTyp
go

create index FKI_n5instytucja_pTyp on n5instytucja (pTyp)
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pMiejscowosc')
	drop index n5instytucja.FKI_n5instytucja_pMiejscowosc
go

create index FKI_n5instytucja_pMiejscowosc on n5instytucja (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank1')
	drop index n5instytucja.FKI_n5instytucja_pBank1
go

create index FKI_n5instytucja_pBank1 on n5instytucja (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank2')
	drop index n5instytucja.FKI_n5instytucja_pBank2
go

create index FKI_n5instytucja_pBank2 on n5instytucja (pBank2)
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank3')
	drop index n5instytucja.FKI_n5instytucja_pBank3
go

create index FKI_n5instytucja_pBank3 on n5instytucja (pBank3)
go

if exists (select * from sysindexes where name='FKI_n5uzytkownik_pWykonawca')
	drop index n5uzytkownik.FKI_n5uzytkownik_pWykonawca
go

create index FKI_n5uzytkownik_pWykonawca on n5uzytkownik (pWykonawca)
go

if exists (select * from sysindexes where name='FKI_n5klient_pMiejscowosc')
	drop index n5klient.FKI_n5klient_pMiejscowosc
go

create index FKI_n5klient_pMiejscowosc on n5klient (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5klient_pBranza')
	drop index n5klient.FKI_n5klient_pBranza
go

create index FKI_n5klient_pBranza on n5klient (pBranza)
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank1')
	drop index n5klient.FKI_n5klient_pBank1
go

create index FKI_n5klient_pBank1 on n5klient (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank2')
	drop index n5klient.FKI_n5klient_pBank2
go

create index FKI_n5klient_pBank2 on n5klient (pBank2)
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank3')
	drop index n5klient.FKI_n5klient_pBank3
go

create index FKI_n5klient_pBank3 on n5klient (pBank3)
go

if exists (select * from sysindexes where name='FKI_n5klient_pWaluta')
	drop index n5klient.FKI_n5klient_pWaluta
go

create index FKI_n5klient_pWaluta on n5klient (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5klient_pPracownik')
	drop index n5klient.FKI_n5klient_pPracownik
go

create index FKI_n5klient_pPracownik on n5klient (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5klient_pGrupaKlient')
	drop index n5klient.FKI_n5klient_pGrupaKlient
go

create index FKI_n5klient_pGrupaKlient on n5klient (pGrupaKlient)
go

if exists (select * from sysindexes where name='FKI_n5klient_pMiejscowoscSDB')
	drop index n5klient.FKI_n5klient_pMiejscowoscSDB
go

create index FKI_n5klient_pMiejscowoscSDB on n5klient (pMiejscowoscSDB)
go

if exists (select * from sysindexes where name='FKI_n5klient_pWalutaLimitu')
	drop index n5klient.FKI_n5klient_pWalutaLimitu
go

create index FKI_n5klient_pWalutaLimitu on n5klient (pWalutaLimitu)
go

if exists (select * from sysindexes where name='FKI_n5klient_pSposobPlatnosci')
	drop index n5klient.FKI_n5klient_pSposobPlatnosci
go

create index FKI_n5klient_pSposobPlatnosci on n5klient (pSposobPlatnosci)
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pMiejscowosc')
	drop index n5pracownik.FKI_n5pracownik_pMiejscowosc
go

create index FKI_n5pracownik_pMiejscowosc on n5pracownik (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pBank1')
	drop index n5pracownik.FKI_n5pracownik_pBank1
go

create index FKI_n5pracownik_pBank1 on n5pracownik (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pJednostkaOrg')
	drop index n5pracownik.FKI_n5pracownik_pJednostkaOrg
go

create index FKI_n5pracownik_pJednostkaOrg on n5pracownik (pJednostkaOrg)
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pUrzadSkarbowy')
	drop index n5pracownik.FKI_n5pracownik_pUrzadSkarbowy
go

create index FKI_n5pracownik_pUrzadSkarbowy on n5pracownik (pUrzadSkarbowy)
go

if exists (select * from sysindexes where name='FKI_n5firma_pMiejscowosc')
	drop index n5firma.FKI_n5firma_pMiejscowosc
go

create index FKI_n5firma_pMiejscowosc on n5firma (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank1')
	drop index n5firma.FKI_n5firma_pBank1
go

create index FKI_n5firma_pBank1 on n5firma (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank2')
	drop index n5firma.FKI_n5firma_pBank2
go

create index FKI_n5firma_pBank2 on n5firma (pBank2)
go

if exists (select * from sysindexes where name='FKI_n5firma_pWaluta')
	drop index n5firma.FKI_n5firma_pWaluta
go

create index FKI_n5firma_pWaluta on n5firma (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank3')
	drop index n5firma.FKI_n5firma_pBank3
go

create index FKI_n5firma_pBank3 on n5firma (pBank3)
go

if exists (select * from sysindexes where name='FKI_n5firma_pUrzadSkarbowyVAT')
	drop index n5firma.FKI_n5firma_pUrzadSkarbowyVAT
go

create index FKI_n5firma_pUrzadSkarbowyVAT on n5firma (pUrzadSkarbowyVAT)
go

if exists (select * from sysindexes where name='FKI_n5firma_pUrzadSkarbowyPD')
	drop index n5firma.FKI_n5firma_pUrzadSkarbowyPD
go

create index FKI_n5firma_pUrzadSkarbowyPD on n5firma (pUrzadSkarbowyPD)
go

if exists (select * from sysindexes where name='FKI_n5firma_pZUS')
	drop index n5firma.FKI_n5firma_pZUS
go

create index FKI_n5firma_pZUS on n5firma (pZUS)
go

if exists (select * from sysindexes where name='FKI_n5firma_pMainJO')
	drop index n5firma.FKI_n5firma_pMainJO
go

create index FKI_n5firma_pMainJO on n5firma (pMainJO)
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_pWojewodztwo')
	drop index n5miejscowosc.FKI_n5miejscowosc_pWojewodztwo
go

create index FKI_n5miejscowosc_pWojewodztwo on n5miejscowosc (pWojewodztwo)
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_pRegion')
	drop index n5miejscowosc.FKI_n5miejscowosc_pRegion
go

create index FKI_n5miejscowosc_pRegion on n5miejscowosc (pRegion)
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pKlient')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pKlient
go

create index FKI_n5klient_pracownik_pKlient on n5klient_pracownik (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pJednOrgKlienta')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pJednOrgKlienta
go

create index FKI_n5klient_pracownik_pJednOrgKlienta on n5klient_pracownik (pJednOrgKlienta)
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pPracownik')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pPracownik
go

create index FKI_n5klient_pracownik_pPracownik on n5klient_pracownik (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pMiejscowosc')
	drop index n5jedn_org.FKI_n5jedn_org_pMiejscowosc
go

create index FKI_n5jedn_org_pMiejscowosc on n5jedn_org (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank1')
	drop index n5jedn_org.FKI_n5jedn_org_pBank1
go

create index FKI_n5jedn_org_pBank1 on n5jedn_org (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank2')
	drop index n5jedn_org.FKI_n5jedn_org_pBank2
go

create index FKI_n5jedn_org_pBank2 on n5jedn_org (pBank2)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank3')
	drop index n5jedn_org.FKI_n5jedn_org_pBank3
go

create index FKI_n5jedn_org_pBank3 on n5jedn_org (pBank3)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pPracownik')
	drop index n5jedn_org.FKI_n5jedn_org_pPracownik
go

create index FKI_n5jedn_org_pPracownik on n5jedn_org (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_p_Jend_Org_Nadrzedna')
	drop index n5jedn_org.FKI_n5jedn_org_p_Jend_Org_Nadrzedna
go

create index FKI_n5jedn_org_p_Jend_Org_Nadrzedna on n5jedn_org (p_Jend_Org_Nadrzedna)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pMiejscowosc')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pMiejscowosc
go

create index FKI_n5_klient_jedn_org_pMiejscowosc on n5_klient_jedn_org (pMiejscowosc)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank1')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank1
go

create index FKI_n5_klient_jedn_org_pBank1 on n5_klient_jedn_org (pBank1)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank2')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank2
go

create index FKI_n5_klient_jedn_org_pBank2 on n5_klient_jedn_org (pBank2)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank3')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank3
go

create index FKI_n5_klient_jedn_org_pBank3 on n5_klient_jedn_org (pBank3)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pKlient')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pKlient
go

create index FKI_n5_klient_jedn_org_pKlient on n5_klient_jedn_org (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_p_Klient_JO_Nadrzedna')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_p_Klient_JO_Nadrzedna
go

create index FKI_n5_klient_jedn_org_p_Klient_JO_Nadrzedna on n5_klient_jedn_org (p_Klient_JO_Nadrzedna)
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pKlientPracownik')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pKlientPracownik
go

create index FKI_n5_klient_jedn_org_pKlientPracownik on n5_klient_jedn_org (pKlientPracownik)
go

if exists (select * from sysindexes where name='FKI_n5typdokumentu_pTypNadrzedny')
	drop index n5typdokumentu.FKI_n5typdokumentu_pTypNadrzedny
go

create index FKI_n5typdokumentu_pTypNadrzedny on n5typdokumentu (pTypNadrzedny)
go

if exists (select * from sysindexes where name='FKI_n5grupaproduktow_pGrupaNadrzedna')
	drop index n5grupaproduktow.FKI_n5grupaproduktow_pGrupaNadrzedna
go

create index FKI_n5grupaproduktow_pGrupaNadrzedna on n5grupaproduktow (pGrupaNadrzedna)
go

if exists (select * from sysindexes where name='FKI_n5dokument_pTypDokumentu')
	drop index n5dokument.FKI_n5dokument_pTypDokumentu
go

create index FKI_n5dokument_pTypDokumentu on n5dokument (pTypDokumentu)
go

if exists (select * from sysindexes where name='WFKI_n5dokument_wpNadawca')
	drop index n5dokument.WFKI_n5dokument_wpNadawca
go

create index WFKI_n5dokument_wpNadawca on n5dokument (wpNadawca,wpNadawca_wrt )
go

if exists (select * from sysindexes where name='WFKI_n5dokument_wpAdresat')
	drop index n5dokument.WFKI_n5dokument_wpAdresat
go

create index WFKI_n5dokument_wpAdresat on n5dokument (wpAdresat,wpAdresat_wrt )
go

if exists (select * from sysindexes where name='FKI_n5dokument_pUzytkWypoz')
	drop index n5dokument.FKI_n5dokument_pUzytkWypoz
go

create index FKI_n5dokument_pUzytkWypoz on n5dokument (pUzytkWypoz)
go

if exists (select * from sysindexes where name='FKI_n5dokument_pReplaces')
	drop index n5dokument.FKI_n5dokument_pReplaces
go

create index FKI_n5dokument_pReplaces on n5dokument (pReplaces)
go

if exists (select * from sysindexes where name='FKI_n5dokument_pReplaced')
	drop index n5dokument.FKI_n5dokument_pReplaced
go

create index FKI_n5dokument_pReplaced on n5dokument (pReplaced)
go

if exists (select * from sysindexes where name='FKI_n5grupaklient_pGrupaNadrzedna')
	drop index n5grupaklient.FKI_n5grupaklient_pGrupaNadrzedna
go

create index FKI_n5grupaklient_pGrupaNadrzedna on n5grupaklient (pGrupaNadrzedna)
go

if exists (select * from sysindexes where name='FKI_n5grupaklient_pWalutaLimitu')
	drop index n5grupaklient.FKI_n5grupaklient_pWalutaLimitu
go

create index FKI_n5grupaklient_pWalutaLimitu on n5grupaklient (pWalutaLimitu)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pZlecajacy')
	drop index n5zadanie.FKI_n5zadanie_pZlecajacy
go

create index FKI_n5zadanie_pZlecajacy on n5zadanie (pZlecajacy)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pTypDzialania')
	drop index n5zadanie.FKI_n5zadanie_pTypDzialania
go

create index FKI_n5zadanie_pTypDzialania on n5zadanie (pTypDzialania)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pProcedura')
	drop index n5zadanie.FKI_n5zadanie_pProcedura
go

create index FKI_n5zadanie_pProcedura on n5zadanie (pProcedura)
go

if exists (select * from sysindexes where name='WFKI_n5zadanie_wrefSzczegoly')
	drop index n5zadanie.WFKI_n5zadanie_wrefSzczegoly
go

create index WFKI_n5zadanie_wrefSzczegoly on n5zadanie (wrefSzczegoly,wrefSzczegoly_wrt )
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pNadZadanie')
	drop index n5zadanie.FKI_n5zadanie_pNadZadanie
go

create index FKI_n5zadanie_pNadZadanie on n5zadanie (pNadZadanie)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pPopZadanie')
	drop index n5zadanie.FKI_n5zadanie_pPopZadanie
go

create index FKI_n5zadanie_pPopZadanie on n5zadanie (pPopZadanie)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pWykonawca')
	drop index n5zadanie.FKI_n5zadanie_pWykonawca
go

create index FKI_n5zadanie_pWykonawca on n5zadanie (pWykonawca)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKlient')
	drop index n5zadanie.FKI_n5zadanie_pKlient
go

create index FKI_n5zadanie_pKlient on n5zadanie (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pSchematDekretacji')
	drop index n5zadanie.FKI_n5zadanie_pSchematDekretacji
go

create index FKI_n5zadanie_pSchematDekretacji on n5zadanie (pSchematDekretacji)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pDowKsieg')
	drop index n5zadanie.FKI_n5zadanie_pDowKsieg
go

create index FKI_n5zadanie_pDowKsieg on n5zadanie (pDowKsieg)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKlientPracownik')
	drop index n5zadanie.FKI_n5zadanie_pKlientPracownik
go

create index FKI_n5zadanie_pKlientPracownik on n5zadanie (pKlientPracownik)
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKwalifikatorEx')
	drop index n5zadanie.FKI_n5zadanie_pKwalifikatorEx
go

create index FKI_n5zadanie_pKwalifikatorEx on n5zadanie (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5pozplatnosc_pTransakcja')
	drop index n5pozplatnosc.FKI_n5pozplatnosc_pTransakcja
go

create index FKI_n5pozplatnosc_pTransakcja on n5pozplatnosc (pTransakcja)
go

if exists (select * from sysindexes where name='WFKI_n5wykonawca_wrefObiekt')
	drop index n5wykonawca.WFKI_n5wykonawca_wrefObiekt
go

create index WFKI_n5wykonawca_wrefObiekt on n5wykonawca (wrefObiekt,wrefObiekt_wrt )
go

if exists (select * from sysindexes where name='WFKI_n5zadaniezal_wrefZal')
	drop index n5zadaniezal.WFKI_n5zadaniezal_wrefZal
go

create index WFKI_n5zadaniezal_wrefZal on n5zadaniezal (wrefZal,wrefZal_wrt )
go

if exists (select * from sysindexes where name='FKI_n5WizzardEmailDokumElem_pDokument')
	drop index n5WizzardEmailDokumElem.FKI_n5WizzardEmailDokumElem_pDokument
go

create index FKI_n5WizzardEmailDokumElem_pDokument on n5WizzardEmailDokumElem (pDokument)
go

if exists (select * from sysindexes where name='FKI_n5WizzardEmail_pChoiceList')
	drop index n5WizzardEmail.FKI_n5WizzardEmail_pChoiceList
go

create index FKI_n5WizzardEmail_pChoiceList on n5WizzardEmail (pChoiceList)
go

if exists (select * from sysindexes where name='WFKI_n5SendEmail_wpNadawca')
	drop index n5SendEmail.WFKI_n5SendEmail_wpNadawca
go

create index WFKI_n5SendEmail_wpNadawca on n5SendEmail (wpNadawca,wpNadawca_wrt )
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pSposobPlatnosci')
	drop index n5sprzedaz.FKI_n5sprzedaz_pSposobPlatnosci
go

create index FKI_n5sprzedaz_pSposobPlatnosci on n5sprzedaz (pSposobPlatnosci)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlient')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlient
go

create index FKI_n5sprzedaz_pKlient on n5sprzedaz (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlient_JO')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlient_JO
go

create index FKI_n5sprzedaz_pKlient_JO on n5sprzedaz (pKlient_JO)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlientPracownik')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlientPracownik
go

create index FKI_n5sprzedaz_pKlientPracownik on n5sprzedaz (pKlientPracownik)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pUzytRej')
	drop index n5sprzedaz.FKI_n5sprzedaz_pUzytRej
go

create index FKI_n5sprzedaz_pUzytRej on n5sprzedaz (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pZadanie')
	drop index n5sprzedaz.FKI_n5sprzedaz_pZadanie
go

create index FKI_n5sprzedaz_pZadanie on n5sprzedaz (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pRejestrDok')
	drop index n5sprzedaz.FKI_n5sprzedaz_pRejestrDok
go

create index FKI_n5sprzedaz_pRejestrDok on n5sprzedaz (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pDowodKsieg')
	drop index n5sprzedaz.FKI_n5sprzedaz_pDowodKsieg
go

create index FKI_n5sprzedaz_pDowodKsieg on n5sprzedaz (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pSchematDekr')
	drop index n5sprzedaz.FKI_n5sprzedaz_pSchematDekr
go

create index FKI_n5sprzedaz_pSchematDekr on n5sprzedaz (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pTransakcja')
	drop index n5sprzedaz.FKI_n5sprzedaz_pTransakcja
go

create index FKI_n5sprzedaz_pTransakcja on n5sprzedaz (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pPopSprzed')
	drop index n5sprzedaz.FKI_n5sprzedaz_pPopSprzed
go

create index FKI_n5sprzedaz_pPopSprzed on n5sprzedaz (pPopSprzed)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pFaktura')
	drop index n5sprzedaz.FKI_n5sprzedaz_pFaktura
go

create index FKI_n5sprzedaz_pFaktura on n5sprzedaz (pFaktura)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pWaluta')
	drop index n5sprzedaz.FKI_n5sprzedaz_pWaluta
go

create index FKI_n5sprzedaz_pWaluta on n5sprzedaz (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pRozlVat')
	drop index n5sprzedaz.FKI_n5sprzedaz_pRozlVat
go

create index FKI_n5sprzedaz_pRozlVat on n5sprzedaz (pRozlVat)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pZamowienie')
	drop index n5sprzedaz.FKI_n5sprzedaz_pZamowienie
go

create index FKI_n5sprzedaz_pZamowienie on n5sprzedaz (pZamowienie)
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKwalifikatorEx')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKwalifikatorEx
go

create index FKI_n5sprzedaz_pKwalifikatorEx on n5sprzedaz (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pOpakowanieJedn')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pOpakowanieJedn
go

create index FKI_n5opakowanie_produktu_pOpakowanieJedn on n5opakowanie_produktu (pOpakowanieJedn)
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pJednostkaWagi')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pJednostkaWagi
go

create index FKI_n5opakowanie_produktu_pJednostkaWagi on n5opakowanie_produktu (pJednostkaWagi)
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pWaluta')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pWaluta
go

create index FKI_n5opakowanie_produktu_pWaluta on n5opakowanie_produktu (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pJednOpak')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pJednOpak
go

create index FKI_n5opakowanie_produktu_pJednOpak on n5opakowanie_produktu (pJednOpak)
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pZamiennik')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pZamiennik
go

create index FKI_n5opakowanie_produktu_pZamiennik on n5opakowanie_produktu (pZamiennik)
go

if exists (select * from sysindexes where name='FKI_n5produkt_pUlotka')
	drop index n5produkt.FKI_n5produkt_pUlotka
go

create index FKI_n5produkt_pUlotka on n5produkt (pUlotka)
go

if exists (select * from sysindexes where name='FKI_n5produkt_pInstrukcja')
	drop index n5produkt.FKI_n5produkt_pInstrukcja
go

create index FKI_n5produkt_pInstrukcja on n5produkt (pInstrukcja)
go

if exists (select * from sysindexes where name='FKI_n5produkt_pJednostkaEwid')
	drop index n5produkt.FKI_n5produkt_pJednostkaEwid
go

create index FKI_n5produkt_pJednostkaEwid on n5produkt (pJednostkaEwid)
go

if exists (select * from sysindexes where name='FKI_n5produkt_pGrupaProd')
	drop index n5produkt.FKI_n5produkt_pGrupaProd
go

create index FKI_n5produkt_pGrupaProd on n5produkt (pGrupaProd)
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pProdukt')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pProdukt
go

create index FKI_n5pozsprzedaz_pProdukt on n5pozsprzedaz (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pOpak')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pOpak
go

create index FKI_n5pozsprzedaz_pOpak on n5pozsprzedaz (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pKwalifikatorEx')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pKwalifikatorEx
go

create index FKI_n5pozsprzedaz_pKwalifikatorEx on n5pozsprzedaz (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5dokumentlinks_pDokument')
	drop index n5dokumentlinks.FKI_n5dokumentlinks_pDokument
go

create index FKI_n5dokumentlinks_pDokument on n5dokumentlinks (pDokument)
go

if exists (select * from sysindexes where name='FKI_n5pkpir_pRejestrDok')
	drop index n5pkpir.FKI_n5pkpir_pRejestrDok
go

create index FKI_n5pkpir_pRejestrDok on n5pkpir (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5pkpir_pKlient')
	drop index n5pkpir.FKI_n5pkpir_pKlient
go

create index FKI_n5pkpir_pKlient on n5pkpir (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_pDefSchematdekr')
	drop index n5rejestrdok.FKI_n5rejestrdok_pDefSchematdekr
go

create index FKI_n5rejestrdok_pDefSchematdekr on n5rejestrdok (pDefSchematdekr)
go

if exists (select * from sysindexes where name='WFKI_n5rejestrdok_wrefParam1')
	drop index n5rejestrdok.WFKI_n5rejestrdok_wrefParam1
go

create index WFKI_n5rejestrdok_wrefParam1 on n5rejestrdok (wrefParam1,wrefParam1_wrt )
go

if exists (select * from sysindexes where name='WFKI_n5rejestrdok_wrefParam2')
	drop index n5rejestrdok.WFKI_n5rejestrdok_wrefParam2
go

create index WFKI_n5rejestrdok_wrefParam2 on n5rejestrdok (wrefParam2,wrefParam2_wrt )
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_pRokKsieg')
	drop index n5rejestrdok.FKI_n5rejestrdok_pRokKsieg
go

create index FKI_n5rejestrdok_pRokKsieg on n5rejestrdok (pRokKsieg)
go

if exists (select * from sysindexes where name='FKI_n5konto_pJednostka')
	drop index n5konto.FKI_n5konto_pJednostka
go

create index FKI_n5konto_pJednostka on n5konto (pJednostka)
go

if exists (select * from sysindexes where name='WFKI_n5konto_wrefPodmiotRozrach')
	drop index n5konto.WFKI_n5konto_wrefPodmiotRozrach
go

create index WFKI_n5konto_wrefPodmiotRozrach on n5konto (wrefPodmiotRozrach,wrefPodmiotRozrach_wrt )
go

if exists (select * from sysindexes where name='FKI_n5konto_pKontoNadrz')
	drop index n5konto.FKI_n5konto_pKontoNadrz
go

create index FKI_n5konto_pKontoNadrz on n5konto (pKontoNadrz)
go

if exists (select * from sysindexes where name='FKI_n5dekret_pKonto')
	drop index n5dekret.FKI_n5dekret_pKonto
go

create index FKI_n5dekret_pKonto on n5dekret (pKonto)
go

if exists (select * from sysindexes where name='FKI_n5dekret_pTransakcja')
	drop index n5dekret.FKI_n5dekret_pTransakcja
go

create index FKI_n5dekret_pTransakcja on n5dekret (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5dekret_pKwalifikator')
	drop index n5dekret.FKI_n5dekret_pKwalifikator
go

create index FKI_n5dekret_pKwalifikator on n5dekret (pKwalifikator)
go

if exists (select * from sysindexes where name='FKI_n5dowodksieg_pUzytRej')
	drop index n5dowodksieg.FKI_n5dowodksieg_pUzytRej
go

create index FKI_n5dowodksieg_pUzytRej on n5dowodksieg (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5dowodksieg_pRejestrDok')
	drop index n5dowodksieg.FKI_n5dowodksieg_pRejestrDok
go

create index FKI_n5dowodksieg_pRejestrDok on n5dowodksieg (pRejestrDok)
go

if exists (select * from sysindexes where name='WFKI_n5dowodksieg_wrefDokZrod')
	drop index n5dowodksieg.WFKI_n5dowodksieg_wrefDokZrod
go

create index WFKI_n5dowodksieg_wrefDokZrod on n5dowodksieg (wrefDokZrod,wrefDokZrod_wrt )
go

if exists (select * from sysindexes where name='WFKI_n5platnosc_wrefPodmiot')
	drop index n5platnosc.WFKI_n5platnosc_wrefPodmiot
go

create index WFKI_n5platnosc_wrefPodmiot on n5platnosc (wrefPodmiot,wrefPodmiot_wrt )
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pZadanie')
	drop index n5platnosc.FKI_n5platnosc_pZadanie
go

create index FKI_n5platnosc_pZadanie on n5platnosc (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pUzytRej')
	drop index n5platnosc.FKI_n5platnosc_pUzytRej
go

create index FKI_n5platnosc_pUzytRej on n5platnosc (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pRejestrDok')
	drop index n5platnosc.FKI_n5platnosc_pRejestrDok
go

create index FKI_n5platnosc_pRejestrDok on n5platnosc (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pDowodKsieg')
	drop index n5platnosc.FKI_n5platnosc_pDowodKsieg
go

create index FKI_n5platnosc_pDowodKsieg on n5platnosc (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pSchematDekr')
	drop index n5platnosc.FKI_n5platnosc_pSchematDekr
go

create index FKI_n5platnosc_pSchematDekr on n5platnosc (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pWalutaPodm')
	drop index n5platnosc.FKI_n5platnosc_pWalutaPodm
go

create index FKI_n5platnosc_pWalutaPodm on n5platnosc (pWalutaPodm)
go

if exists (select * from sysindexes where name='FKI_n5typdzialania_pTypNadrzedny')
	drop index n5typdzialania.FKI_n5typdzialania_pTypNadrzedny
go

create index FKI_n5typdzialania_pTypNadrzedny on n5typdzialania (pTypNadrzedny)
go

if exists (select * from sysindexes where name='FKI_n5transakcja_pWaluta')
	drop index n5transakcja.FKI_n5transakcja_pWaluta
go

create index FKI_n5transakcja_pWaluta on n5transakcja (pWaluta)
go

if exists (select * from sysindexes where name='WFKI_n5transakcja_wrefPodmiot')
	drop index n5transakcja.WFKI_n5transakcja_wrefPodmiot
go

create index WFKI_n5transakcja_wrefPodmiot on n5transakcja (wrefPodmiot,wrefPodmiot_wrt )
go

if exists (select * from sysindexes where name='FKI_n5transakcja_pNotaOds')
	drop index n5transakcja.FKI_n5transakcja_pNotaOds
go

create index FKI_n5transakcja_pNotaOds on n5transakcja (pNotaOds)
go

if exists (select * from sysindexes where name='FKI_n5schematdekr_pRejestrDok')
	drop index n5schematdekr.FKI_n5schematdekr_pRejestrDok
go

create index FKI_n5schematdekr_pRejestrDok on n5schematdekr (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5schematdekr_pDziennik')
	drop index n5schematdekr.FKI_n5schematdekr_pDziennik
go

create index FKI_n5schematdekr_pDziennik on n5schematdekr (pDziennik)
go

if exists (select * from sysindexes where name='FKI_n5branza_pBranzaNad')
	drop index n5branza.FKI_n5branza_pBranzaNad
go

create index FKI_n5branza_pBranzaNad on n5branza (pBranzaNad)
go

if exists (select * from sysindexes where name='FKI_n5magazyn_pWaluta')
	drop index n5magazyn.FKI_n5magazyn_pWaluta
go

create index FKI_n5magazyn_pWaluta on n5magazyn (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5magazyn_pJednostkaOrg')
	drop index n5magazyn.FKI_n5magazyn_pJednostkaOrg
go

create index FKI_n5magazyn_pJednostkaOrg on n5magazyn (pJednostkaOrg)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pProdukt')
	drop index n5pozdokmag.FKI_n5pozdokmag_pProdukt
go

create index FKI_n5pozdokmag_pProdukt on n5pozdokmag (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pOpak')
	drop index n5pozdokmag.FKI_n5pozdokmag_pOpak
go

create index FKI_n5pozdokmag_pOpak on n5pozdokmag (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pMagZrod')
	drop index n5pozdokmag.FKI_n5pozdokmag_pMagZrod
go

create index FKI_n5pozdokmag_pMagZrod on n5pozdokmag (pMagZrod)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pMagDocel')
	drop index n5pozdokmag.FKI_n5pozdokmag_pMagDocel
go

create index FKI_n5pozdokmag_pMagDocel on n5pozdokmag (pMagDocel)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pJednOpak')
	drop index n5pozdokmag.FKI_n5pozdokmag_pJednOpak
go

create index FKI_n5pozdokmag_pJednOpak on n5pozdokmag (pJednOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pJednEwid')
	drop index n5pozdokmag.FKI_n5pozdokmag_pJednEwid
go

create index FKI_n5pozdokmag_pJednEwid on n5pozdokmag (pJednEwid)
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pKwalifikatorEx')
	drop index n5pozdokmag.FKI_n5pozdokmag_pKwalifikatorEx
go

create index FKI_n5pozdokmag_pKwalifikatorEx on n5pozdokmag (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlient')
	drop index n5dokmag.FKI_n5dokmag_pKlient
go

create index FKI_n5dokmag_pKlient on n5dokmag (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlient_JO')
	drop index n5dokmag.FKI_n5dokmag_pKlient_JO
go

create index FKI_n5dokmag_pKlient_JO on n5dokmag (pKlient_JO)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlientPracownik')
	drop index n5dokmag.FKI_n5dokmag_pKlientPracownik
go

create index FKI_n5dokmag_pKlientPracownik on n5dokmag (pKlientPracownik)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pDokMag')
	drop index n5dokmag.FKI_n5dokmag_pDokMag
go

create index FKI_n5dokmag_pDokMag on n5dokmag (pDokMag)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pUzytRej')
	drop index n5dokmag.FKI_n5dokmag_pUzytRej
go

create index FKI_n5dokmag_pUzytRej on n5dokmag (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pRejestrDok')
	drop index n5dokmag.FKI_n5dokmag_pRejestrDok
go

create index FKI_n5dokmag_pRejestrDok on n5dokmag (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pDowodKsieg')
	drop index n5dokmag.FKI_n5dokmag_pDowodKsieg
go

create index FKI_n5dokmag_pDowodKsieg on n5dokmag (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pSchematDekr')
	drop index n5dokmag.FKI_n5dokmag_pSchematDekr
go

create index FKI_n5dokmag_pSchematDekr on n5dokmag (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pMagZrod')
	drop index n5dokmag.FKI_n5dokmag_pMagZrod
go

create index FKI_n5dokmag_pMagZrod on n5dokmag (pMagZrod)
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pMagDocel')
	drop index n5dokmag.FKI_n5dokmag_pMagDocel
go

create index FKI_n5dokmag_pMagDocel on n5dokmag (pMagDocel)
go

if exists (select * from sysindexes where name='WFKI_n5dokmag_wrefDokHandl')
	drop index n5dokmag.WFKI_n5dokmag_wrefDokHandl
go

create index WFKI_n5dokmag_wrefDokHandl on n5dokmag (wrefDokHandl,wrefDokHandl_wrt )
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKwalifikatorEx')
	drop index n5dokmag.FKI_n5dokmag_pKwalifikatorEx
go

create index FKI_n5dokmag_pKwalifikatorEx on n5dokmag (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5zadaniedw_pWykonawcaDW')
	drop index n5zadaniedw.FKI_n5zadaniedw_pWykonawcaDW
go

create index FKI_n5zadaniedw_pWykonawcaDW on n5zadaniedw (pWykonawcaDW)
go

if exists (select * from sysindexes where name='FKI_n5kurswalut_pWalZ')
	drop index n5kurswalut.FKI_n5kurswalut_pWalZ
go

create index FKI_n5kurswalut_pWalZ on n5kurswalut (pWalZ)
go

if exists (select * from sysindexes where name='FKI_n5kurswalut_pWalN')
	drop index n5kurswalut.FKI_n5kurswalut_pWalN
go

create index FKI_n5kurswalut_pWalN on n5kurswalut (pWalN)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pSposobPlatnosci')
	drop index n5zamowienie.FKI_n5zamowienie_pSposobPlatnosci
go

create index FKI_n5zamowienie_pSposobPlatnosci on n5zamowienie (pSposobPlatnosci)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlient')
	drop index n5zamowienie.FKI_n5zamowienie_pKlient
go

create index FKI_n5zamowienie_pKlient on n5zamowienie (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlient_JO')
	drop index n5zamowienie.FKI_n5zamowienie_pKlient_JO
go

create index FKI_n5zamowienie_pKlient_JO on n5zamowienie (pKlient_JO)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlientPracownik')
	drop index n5zamowienie.FKI_n5zamowienie_pKlientPracownik
go

create index FKI_n5zamowienie_pKlientPracownik on n5zamowienie (pKlientPracownik)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pUzytRej')
	drop index n5zamowienie.FKI_n5zamowienie_pUzytRej
go

create index FKI_n5zamowienie_pUzytRej on n5zamowienie (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pZadanie')
	drop index n5zamowienie.FKI_n5zamowienie_pZadanie
go

create index FKI_n5zamowienie_pZadanie on n5zamowienie (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pRejestrDok')
	drop index n5zamowienie.FKI_n5zamowienie_pRejestrDok
go

create index FKI_n5zamowienie_pRejestrDok on n5zamowienie (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pDowodKsieg')
	drop index n5zamowienie.FKI_n5zamowienie_pDowodKsieg
go

create index FKI_n5zamowienie_pDowodKsieg on n5zamowienie (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pSchematDekr')
	drop index n5zamowienie.FKI_n5zamowienie_pSchematDekr
go

create index FKI_n5zamowienie_pSchematDekr on n5zamowienie (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pWaluta')
	drop index n5zamowienie.FKI_n5zamowienie_pWaluta
go

create index FKI_n5zamowienie_pWaluta on n5zamowienie (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKwalifikatorEx')
	drop index n5zamowienie.FKI_n5zamowienie_pKwalifikatorEx
go

create index FKI_n5zamowienie_pKwalifikatorEx on n5zamowienie (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pProdukt')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pProdukt
go

create index FKI_n5pozzamowienie_pProdukt on n5pozzamowienie (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pOpak')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pOpak
go

create index FKI_n5pozzamowienie_pOpak on n5pozzamowienie (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pKwalifikatorEx')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pKwalifikatorEx
go

create index FKI_n5pozzamowienie_pKwalifikatorEx on n5pozzamowienie (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pProdukt')
	drop index n5pozzakup.FKI_n5pozzakup_pProdukt
go

create index FKI_n5pozzakup_pProdukt on n5pozzakup (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pOpak')
	drop index n5pozzakup.FKI_n5pozzakup_pOpak
go

create index FKI_n5pozzakup_pOpak on n5pozzakup (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pKwalifikatorEx')
	drop index n5pozzakup.FKI_n5pozzakup_pKwalifikatorEx
go

create index FKI_n5pozzakup_pKwalifikatorEx on n5pozzakup (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pSposobPlatnosci')
	drop index n5zakup.FKI_n5zakup_pSposobPlatnosci
go

create index FKI_n5zakup_pSposobPlatnosci on n5zakup (pSposobPlatnosci)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDostawca')
	drop index n5zakup.FKI_n5zakup_pDostawca
go

create index FKI_n5zakup_pDostawca on n5zakup (pDostawca)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDostawca_JO')
	drop index n5zakup.FKI_n5zakup_pDostawca_JO
go

create index FKI_n5zakup_pDostawca_JO on n5zakup (pDostawca_JO)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pUzytRej')
	drop index n5zakup.FKI_n5zakup_pUzytRej
go

create index FKI_n5zakup_pUzytRej on n5zakup (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pZadanie')
	drop index n5zakup.FKI_n5zakup_pZadanie
go

create index FKI_n5zakup_pZadanie on n5zakup (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pRejestrDok')
	drop index n5zakup.FKI_n5zakup_pRejestrDok
go

create index FKI_n5zakup_pRejestrDok on n5zakup (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDowodKsieg')
	drop index n5zakup.FKI_n5zakup_pDowodKsieg
go

create index FKI_n5zakup_pDowodKsieg on n5zakup (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pSchematDekr')
	drop index n5zakup.FKI_n5zakup_pSchematDekr
go

create index FKI_n5zakup_pSchematDekr on n5zakup (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pTransakcja')
	drop index n5zakup.FKI_n5zakup_pTransakcja
go

create index FKI_n5zakup_pTransakcja on n5zakup (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pPopZAkup')
	drop index n5zakup.FKI_n5zakup_pPopZAkup
go

create index FKI_n5zakup_pPopZAkup on n5zakup (pPopZAkup)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pWaluta')
	drop index n5zakup.FKI_n5zakup_pWaluta
go

create index FKI_n5zakup_pWaluta on n5zakup (pWaluta)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pRozlVat')
	drop index n5zakup.FKI_n5zakup_pRozlVat
go

create index FKI_n5zakup_pRozlVat on n5zakup (pRozlVat)
go

if exists (select * from sysindexes where name='FKI_n5zakup_pKwalifikatorEx')
	drop index n5zakup.FKI_n5zakup_pKwalifikatorEx
go

create index FKI_n5zakup_pKwalifikatorEx on n5zakup (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pUzytRej')
	drop index n5rozlvat.FKI_n5rozlvat_pUzytRej
go

create index FKI_n5rozlvat_pUzytRej on n5rozlvat (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pZadanie')
	drop index n5rozlvat.FKI_n5rozlvat_pZadanie
go

create index FKI_n5rozlvat_pZadanie on n5rozlvat (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pSchematDekr')
	drop index n5rozlvat.FKI_n5rozlvat_pSchematDekr
go

create index FKI_n5rozlvat_pSchematDekr on n5rozlvat (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pDowKsieg')
	drop index n5rozlvat.FKI_n5rozlvat_pDowKsieg
go

create index FKI_n5rozlvat_pDowKsieg on n5rozlvat (pDowKsieg)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pTransakcja')
	drop index n5rozlvat.FKI_n5rozlvat_pTransakcja
go

create index FKI_n5rozlvat_pTransakcja on n5rozlvat (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_pUrzadSkarbowy')
	drop index n5rozlvat.FKI_n5rozlvat_pUrzadSkarbowy
go

create index FKI_n5rozlvat_pUrzadSkarbowy on n5rozlvat (pUrzadSkarbowy)
go

if exists (select * from sysindexes where name='FKI_n5grupasrtrw_pGrupaNadrzedna')
	drop index n5grupasrtrw.FKI_n5grupasrtrw_pGrupaNadrzedna
go

create index FKI_n5grupasrtrw_pGrupaNadrzedna on n5grupasrtrw (pGrupaNadrzedna)
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pGrupa')
	drop index n5srtrw.FKI_n5srtrw_pGrupa
go

create index FKI_n5srtrw_pGrupa on n5srtrw (pGrupa)
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pPracownik')
	drop index n5srtrw.FKI_n5srtrw_pPracownik
go

create index FKI_n5srtrw_pPracownik on n5srtrw (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pMUJO')
	drop index n5srtrw.FKI_n5srtrw_pMUJO
go

create index FKI_n5srtrw_pMUJO on n5srtrw (pMUJO)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pProdZrod')
	drop index n5opmag.FKI_n5opmag_pProdZrod
go

create index FKI_n5opmag_pProdZrod on n5opmag (pProdZrod)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pOpakZrod')
	drop index n5opmag.FKI_n5opmag_pOpakZrod
go

create index FKI_n5opmag_pOpakZrod on n5opmag (pOpakZrod)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pMagZrod')
	drop index n5opmag.FKI_n5opmag_pMagZrod
go

create index FKI_n5opmag_pMagZrod on n5opmag (pMagZrod)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pProdDocel')
	drop index n5opmag.FKI_n5opmag_pProdDocel
go

create index FKI_n5opmag_pProdDocel on n5opmag (pProdDocel)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pOpakDocel')
	drop index n5opmag.FKI_n5opmag_pOpakDocel
go

create index FKI_n5opmag_pOpakDocel on n5opmag (pOpakDocel)
go

if exists (select * from sysindexes where name='FKI_n5opmag_pMagDocel')
	drop index n5opmag.FKI_n5opmag_pMagDocel
go

create index FKI_n5opmag_pMagDocel on n5opmag (pMagDocel)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pProdZrod')
	drop index n5koropmag.FKI_n5koropmag_pProdZrod
go

create index FKI_n5koropmag_pProdZrod on n5koropmag (pProdZrod)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pOpakZrod')
	drop index n5koropmag.FKI_n5koropmag_pOpakZrod
go

create index FKI_n5koropmag_pOpakZrod on n5koropmag (pOpakZrod)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pMagZrod')
	drop index n5koropmag.FKI_n5koropmag_pMagZrod
go

create index FKI_n5koropmag_pMagZrod on n5koropmag (pMagZrod)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pProdDocel')
	drop index n5koropmag.FKI_n5koropmag_pProdDocel
go

create index FKI_n5koropmag_pProdDocel on n5koropmag (pProdDocel)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pOpakDocel')
	drop index n5koropmag.FKI_n5koropmag_pOpakDocel
go

create index FKI_n5koropmag_pOpakDocel on n5koropmag (pOpakDocel)
go

if exists (select * from sysindexes where name='FKI_n5koropmag_pMagDocel')
	drop index n5koropmag.FKI_n5koropmag_pMagDocel
go

create index FKI_n5koropmag_pMagDocel on n5koropmag (pMagDocel)
go

if exists (select * from sysindexes where name='FKI_n5stanmag_pMagazyn')
	drop index n5stanmag.FKI_n5stanmag_pMagazyn
go

create index FKI_n5stanmag_pMagazyn on n5stanmag (pMagazyn)
go

if exists (select * from sysindexes where name='FKI_n5stanmag_pProdukt')
	drop index n5stanmag.FKI_n5stanmag_pProdukt
go

create index FKI_n5stanmag_pProdukt on n5stanmag (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5stanmag_pOpak')
	drop index n5stanmag.FKI_n5stanmag_pOpak
go

create index FKI_n5stanmag_pOpak on n5stanmag (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pProdukt')
	drop index n5pozrecepta.FKI_n5pozrecepta_pProdukt
go

create index FKI_n5pozrecepta_pProdukt on n5pozrecepta (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pOpak')
	drop index n5pozrecepta.FKI_n5pozrecepta_pOpak
go

create index FKI_n5pozrecepta_pOpak on n5pozrecepta (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5recepta_pWyrob')
	drop index n5recepta.FKI_n5recepta_pWyrob
go

create index FKI_n5recepta_pWyrob on n5recepta (pWyrob)
go

if exists (select * from sysindexes where name='FKI_n5recepta_pWyrOpak')
	drop index n5recepta.FKI_n5recepta_pWyrOpak
go

create index FKI_n5recepta_pWyrOpak on n5recepta (pWyrOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pProdukt')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pProdukt
go

create index FKI_n5pozzlecprod_pProdukt on n5pozzlecprod (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pOpak')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pOpak
go

create index FKI_n5pozzlecprod_pOpak on n5pozzlecprod (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pRecepta')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pRecepta
go

create index FKI_n5pozzlecprod_pRecepta on n5pozzlecprod (pRecepta)
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pKwalifikatorEx')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pKwalifikatorEx
go

create index FKI_n5pozzlecprod_pKwalifikatorEx on n5pozzlecprod (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pUzytRej')
	drop index n5zlecprod.FKI_n5zlecprod_pUzytRej
go

create index FKI_n5zlecprod_pUzytRej on n5zlecprod (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pRejestrDok')
	drop index n5zlecprod.FKI_n5zlecprod_pRejestrDok
go

create index FKI_n5zlecprod_pRejestrDok on n5zlecprod (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pDowodKsieg')
	drop index n5zlecprod.FKI_n5zlecprod_pDowodKsieg
go

create index FKI_n5zlecprod_pDowodKsieg on n5zlecprod (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pSchematDekr')
	drop index n5zlecprod.FKI_n5zlecprod_pSchematDekr
go

create index FKI_n5zlecprod_pSchematDekr on n5zlecprod (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pZadanie')
	drop index n5zlecprod.FKI_n5zlecprod_pZadanie
go

create index FKI_n5zlecprod_pZadanie on n5zlecprod (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKlient')
	drop index n5zlecprod.FKI_n5zlecprod_pKlient
go

create index FKI_n5zlecprod_pKlient on n5zlecprod (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKlient_JO')
	drop index n5zlecprod.FKI_n5zlecprod_pKlient_JO
go

create index FKI_n5zlecprod_pKlient_JO on n5zlecprod (pKlient_JO)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pZamowienie')
	drop index n5zlecprod.FKI_n5zlecprod_pZamowienie
go

create index FKI_n5zlecprod_pZamowienie on n5zlecprod (pZamowienie)
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKwalifikatorEx')
	drop index n5zlecprod.FKI_n5zlecprod_pKwalifikatorEx
go

create index FKI_n5zlecprod_pKwalifikatorEx on n5zlecprod (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5eventlog_pUser')
	drop index n5eventlog.FKI_n5eventlog_pUser
go

create index FKI_n5eventlog_pUser on n5eventlog (pUser)
go

if exists (select * from sysindexes where name='WFKI_n5polrab_wpProdGrupa')
	drop index n5polrab.WFKI_n5polrab_wpProdGrupa
go

create index WFKI_n5polrab_wpProdGrupa on n5polrab (wpProdGrupa,wpProdGrupa_wrt )
go

if exists (select * from sysindexes where name='FKI_n5polrab_pOpak')
	drop index n5polrab.FKI_n5polrab_pOpak
go

create index FKI_n5polrab_pOpak on n5polrab (pOpak)
go

if exists (select * from sysindexes where name='WFKI_n5polrab_wpKlientGrupa')
	drop index n5polrab.WFKI_n5polrab_wpKlientGrupa
go

create index WFKI_n5polrab_wpKlientGrupa on n5polrab (wpKlientGrupa,wpKlientGrupa_wrt )
go

if exists (select * from sysindexes where name='FKI_n5plstawka_pJednostka')
	drop index n5plstawka.FKI_n5plstawka_pJednostka
go

create index FKI_n5plstawka_pJednostka on n5plstawka (pJednostka)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pPracownik')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pPracownik
go

create index FKI_n5plnaliczenie_pPracownik on n5plnaliczenie (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pUzytRej')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pUzytRej
go

create index FKI_n5plnaliczenie_pUzytRej on n5plnaliczenie (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pRejestrDok')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pRejestrDok
go

create index FKI_n5plnaliczenie_pRejestrDok on n5plnaliczenie (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pDowodKsieg')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pDowodKsieg
go

create index FKI_n5plnaliczenie_pDowodKsieg on n5plnaliczenie (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pSchematDekr')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pSchematDekr
go

create index FKI_n5plnaliczenie_pSchematDekr on n5plnaliczenie (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pListaPlac')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pListaPlac
go

create index FKI_n5plnaliczenie_pListaPlac on n5plnaliczenie (pListaPlac)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pTransakcja')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pTransakcja
go

create index FKI_n5plnaliczenie_pTransakcja on n5plnaliczenie (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pZadanie')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pZadanie
go

create index FKI_n5plnaliczenie_pZadanie on n5plnaliczenie (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5plsklnal_pSchemat')
	drop index n5plsklnal.FKI_n5plsklnal_pSchemat
go

create index FKI_n5plsklnal_pSchemat on n5plsklnal (pSchemat)
go

if exists (select * from sysindexes where name='FKI_n5plsubkonto_pJednostka')
	drop index n5plsubkonto.FKI_n5plsubkonto_pJednostka
go

create index FKI_n5plsubkonto_pJednostka on n5plsubkonto (pJednostka)
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pPracownik')
	drop index n5pldekret.FKI_n5pldekret_pPracownik
go

create index FKI_n5pldekret_pPracownik on n5pldekret (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pSubKonto')
	drop index n5pldekret.FKI_n5pldekret_pSubKonto
go

create index FKI_n5pldekret_pSubKonto on n5pldekret (pSubKonto)
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pListaPlac')
	drop index n5pldekret.FKI_n5pldekret_pListaPlac
go

create index FKI_n5pldekret_pListaPlac on n5pldekret (pListaPlac)
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pNaliczenie')
	drop index n5pldekret.FKI_n5pldekret_pNaliczenie
go

create index FKI_n5pldekret_pNaliczenie on n5pldekret (pNaliczenie)
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pSchematNal')
	drop index n5pldekret.FKI_n5pldekret_pSchematNal
go

create index FKI_n5pldekret_pSchematNal on n5pldekret (pSchematNal)
go

if exists (select * from sysindexes where name='WFKI_n5pldekret_wrefDokument')
	drop index n5pldekret.WFKI_n5pldekret_wrefDokument
go

create index WFKI_n5pldekret_wrefDokument on n5pldekret (wrefDokument,wrefDokument_wrt )
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pPracownik')
	drop index n5plumowa.FKI_n5plumowa_pPracownik
go

create index FKI_n5plumowa_pPracownik on n5plumowa (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pUzytRej')
	drop index n5plumowa.FKI_n5plumowa_pUzytRej
go

create index FKI_n5plumowa_pUzytRej on n5plumowa (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pUmowaPop')
	drop index n5plumowa.FKI_n5plumowa_pUmowaPop
go

create index FKI_n5plumowa_pUmowaPop on n5plumowa (pUmowaPop)
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pKalendarz')
	drop index n5plumowa.FKI_n5plumowa_pKalendarz
go

create index FKI_n5plumowa_pKalendarz on n5plumowa (pKalendarz)
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pPracownik')
	drop index n5plchoroba.FKI_n5plchoroba_pPracownik
go

create index FKI_n5plchoroba_pPracownik on n5plchoroba (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pUzytRej')
	drop index n5plchoroba.FKI_n5plchoroba_pUzytRej
go

create index FKI_n5plchoroba_pUzytRej on n5plchoroba (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pUmowa')
	drop index n5plchoroba.FKI_n5plchoroba_pUmowa
go

create index FKI_n5plchoroba_pUmowa on n5plchoroba (pUmowa)
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pSchemat')
	drop index n5plchoroba.FKI_n5plchoroba_pSchemat
go

create index FKI_n5plchoroba_pSchemat on n5plchoroba (pSchemat)
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pPracownik')
	drop index n5plnieob.FKI_n5plnieob_pPracownik
go

create index FKI_n5plnieob_pPracownik on n5plnieob (pPracownik)
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pUzytRej')
	drop index n5plnieob.FKI_n5plnieob_pUzytRej
go

create index FKI_n5plnieob_pUzytRej on n5plnieob (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pUmowa')
	drop index n5plnieob.FKI_n5plnieob_pUmowa
go

create index FKI_n5plnieob_pUmowa on n5plnieob (pUmowa)
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pSchemat')
	drop index n5plnieob.FKI_n5plnieob_pSchemat
go

create index FKI_n5plnieob_pSchemat on n5plnieob (pSchemat)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pUzytRej')
	drop index n5rozlcit.FKI_n5rozlcit_pUzytRej
go

create index FKI_n5rozlcit_pUzytRej on n5rozlcit (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pZadanie')
	drop index n5rozlcit.FKI_n5rozlcit_pZadanie
go

create index FKI_n5rozlcit_pZadanie on n5rozlcit (pZadanie)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pSchematDekr')
	drop index n5rozlcit.FKI_n5rozlcit_pSchematDekr
go

create index FKI_n5rozlcit_pSchematDekr on n5rozlcit (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pDowKsieg')
	drop index n5rozlcit.FKI_n5rozlcit_pDowKsieg
go

create index FKI_n5rozlcit_pDowKsieg on n5rozlcit (pDowKsieg)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pTransakcja')
	drop index n5rozlcit.FKI_n5rozlcit_pTransakcja
go

create index FKI_n5rozlcit_pTransakcja on n5rozlcit (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pUrzadSkarbowy')
	drop index n5rozlcit.FKI_n5rozlcit_pUrzadSkarbowy
go

create index FKI_n5rozlcit_pUrzadSkarbowy on n5rozlcit (pUrzadSkarbowy)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pProdukt')
	drop index n5pozrealprod.FKI_n5pozrealprod_pProdukt
go

create index FKI_n5pozrealprod_pProdukt on n5pozrealprod (pProdukt)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pOpak')
	drop index n5pozrealprod.FKI_n5pozrealprod_pOpak
go

create index FKI_n5pozrealprod_pOpak on n5pozrealprod (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pMagazyn')
	drop index n5pozrealprod.FKI_n5pozrealprod_pMagazyn
go

create index FKI_n5pozrealprod_pMagazyn on n5pozrealprod (pMagazyn)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pJednOpak')
	drop index n5pozrealprod.FKI_n5pozrealprod_pJednOpak
go

create index FKI_n5pozrealprod_pJednOpak on n5pozrealprod (pJednOpak)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pJednEwid')
	drop index n5pozrealprod.FKI_n5pozrealprod_pJednEwid
go

create index FKI_n5pozrealprod_pJednEwid on n5pozrealprod (pJednEwid)
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pKwalifikatorEx')
	drop index n5pozrealprod.FKI_n5pozrealprod_pKwalifikatorEx
go

create index FKI_n5pozrealprod_pKwalifikatorEx on n5pozrealprod (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pWyrob')
	drop index n5realprod.FKI_n5realprod_pWyrob
go

create index FKI_n5realprod_pWyrob on n5realprod (pWyrob)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pOpak')
	drop index n5realprod.FKI_n5realprod_pOpak
go

create index FKI_n5realprod_pOpak on n5realprod (pOpak)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pUzytRej')
	drop index n5realprod.FKI_n5realprod_pUzytRej
go

create index FKI_n5realprod_pUzytRej on n5realprod (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pRejestrDok')
	drop index n5realprod.FKI_n5realprod_pRejestrDok
go

create index FKI_n5realprod_pRejestrDok on n5realprod (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pDowodKsieg')
	drop index n5realprod.FKI_n5realprod_pDowodKsieg
go

create index FKI_n5realprod_pDowodKsieg on n5realprod (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pSchematDekr')
	drop index n5realprod.FKI_n5realprod_pSchematDekr
go

create index FKI_n5realprod_pSchematDekr on n5realprod (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pMagazyn')
	drop index n5realprod.FKI_n5realprod_pMagazyn
go

create index FKI_n5realprod_pMagazyn on n5realprod (pMagazyn)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pZlecProd')
	drop index n5realprod.FKI_n5realprod_pZlecProd
go

create index FKI_n5realprod_pZlecProd on n5realprod (pZlecProd)
go

if exists (select * from sysindexes where name='FKI_n5realprod_pKwalifikatorEx')
	drop index n5realprod.FKI_n5realprod_pKwalifikatorEx
go

create index FKI_n5realprod_pKwalifikatorEx on n5realprod (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5konto_budzet_pKonto')
	drop index n5konto_budzet.FKI_n5konto_budzet_pKonto
go

create index FKI_n5konto_budzet_pKonto on n5konto_budzet (pKonto)
go

if exists (select * from sysindexes where name='FKI_n5konto_budzet_pBudzet')
	drop index n5konto_budzet.FKI_n5konto_budzet_pBudzet
go

create index FKI_n5konto_budzet_pBudzet on n5konto_budzet (pBudzet)
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_pKategoria')
	drop index n5bwinfo.FKI_n5bwinfo_pKategoria
go

create index FKI_n5bwinfo_pKategoria on n5bwinfo (pKategoria)
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_pUzytRej')
	drop index n5bwinfo.FKI_n5bwinfo_pUzytRej
go

create index FKI_n5bwinfo_pUzytRej on n5bwinfo (pUzytRej)
go

if exists (select * from sysindexes where name='WFKI_n5bwinfo_produkt_wpProdGrupa')
	drop index n5bwinfo_produkt.WFKI_n5bwinfo_produkt_wpProdGrupa
go

create index WFKI_n5bwinfo_produkt_wpProdGrupa on n5bwinfo_produkt (wpProdGrupa,wpProdGrupa_wrt )
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_produkt_pOpak')
	drop index n5bwinfo_produkt.FKI_n5bwinfo_produkt_pOpak
go

create index FKI_n5bwinfo_produkt_pOpak on n5bwinfo_produkt (pOpak)
go

if exists (select * from sysindexes where name='WFKI_n5bwinfo_zal_wrefZal')
	drop index n5bwinfo_zal.WFKI_n5bwinfo_zal_wrefZal
go

create index WFKI_n5bwinfo_zal_wrefZal on n5bwinfo_zal (wrefZal,wrefZal_wrt )
go

if exists (select * from sysindexes where name='FKI_n5poznotaods_pTransakcja')
	drop index n5poznotaods.FKI_n5poznotaods_pTransakcja
go

create index FKI_n5poznotaods_pTransakcja on n5poznotaods (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pKlient')
	drop index n5notaods.FKI_n5notaods_pKlient
go

create index FKI_n5notaods_pKlient on n5notaods (pKlient)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pUzytRej')
	drop index n5notaods.FKI_n5notaods_pUzytRej
go

create index FKI_n5notaods_pUzytRej on n5notaods (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pRejestrDok')
	drop index n5notaods.FKI_n5notaods_pRejestrDok
go

create index FKI_n5notaods_pRejestrDok on n5notaods (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pDowodKsieg')
	drop index n5notaods.FKI_n5notaods_pDowodKsieg
go

create index FKI_n5notaods_pDowodKsieg on n5notaods (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pSchematDekr')
	drop index n5notaods.FKI_n5notaods_pSchematDekr
go

create index FKI_n5notaods_pSchematDekr on n5notaods (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pKwalifikatorEx')
	drop index n5notaods.FKI_n5notaods_pKwalifikatorEx
go

create index FKI_n5notaods_pKwalifikatorEx on n5notaods (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5notaods_pTransakcja')
	drop index n5notaods.FKI_n5notaods_pTransakcja
go

create index FKI_n5notaods_pTransakcja on n5notaods (pTransakcja)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pSRTRW')
	drop index n5opsrtrw.FKI_n5opsrtrw_pSRTRW
go

create index FKI_n5opsrtrw_pSRTRW on n5opsrtrw (pSRTRW)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pMUJO')
	drop index n5opsrtrw.FKI_n5opsrtrw_pMUJO
go

create index FKI_n5opsrtrw_pMUJO on n5opsrtrw (pMUJO)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pUzytRej')
	drop index n5opsrtrw.FKI_n5opsrtrw_pUzytRej
go

create index FKI_n5opsrtrw_pUzytRej on n5opsrtrw (pUzytRej)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pPracownik')
	drop index n5opsrtrw.FKI_n5opsrtrw_pPracownik
go

create index FKI_n5opsrtrw_pPracownik on n5opsrtrw (pPracownik)
go

if exists (select * from sysindexes where name='WFKI_n5opsrtrw_wrefDokument')
	drop index n5opsrtrw.WFKI_n5opsrtrw_wrefDokument
go

create index WFKI_n5opsrtrw_wrefDokument on n5opsrtrw (wrefDokument,wrefDokument_wrt )
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pRejestrDok')
	drop index n5opsrtrw.FKI_n5opsrtrw_pRejestrDok
go

create index FKI_n5opsrtrw_pRejestrDok on n5opsrtrw (pRejestrDok)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pDowodKsieg')
	drop index n5opsrtrw.FKI_n5opsrtrw_pDowodKsieg
go

create index FKI_n5opsrtrw_pDowodKsieg on n5opsrtrw (pDowodKsieg)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pSchematDekr')
	drop index n5opsrtrw.FKI_n5opsrtrw_pSchematDekr
go

create index FKI_n5opsrtrw_pSchematDekr on n5opsrtrw (pSchematDekr)
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pKwalifikatorEx')
	drop index n5opsrtrw.FKI_n5opsrtrw_pKwalifikatorEx
go

create index FKI_n5opsrtrw_pKwalifikatorEx on n5opsrtrw (pKwalifikatorEx)
go

if exists (select * from sysindexes where name='FKI_n5plwzorlp_pCLPracownicy')
	drop index n5plwzorlp.FKI_n5plwzorlp_pCLPracownicy
go

create index FKI_n5plwzorlp_pCLPracownicy on n5plwzorlp (pCLPracownicy)
go

if exists (select * from sysindexes where name='FKI_n5plwzorlp_pCLSkladniki')
	drop index n5plwzorlp.FKI_n5plwzorlp_pCLSkladniki
go

create index FKI_n5plwzorlp_pCLSkladniki on n5plwzorlp (pCLSkladniki)
go

if exists (select * from sysindexes where name='FKI_n5plsklumowy_pSchemat')
	drop index n5plsklumowy.FKI_n5plsklumowy_pSchemat
go

create index FKI_n5plsklumowy_pSchemat on n5plsklumowy (pSchemat)
go

if exists (select * from sysindexes where name='WFKI_n5plsklnalzrod_wrefDokument')
	drop index n5plsklnalzrod.WFKI_n5plsklnalzrod_wrefDokument
go

create index WFKI_n5plsklnalzrod_wrefDokument on n5plsklnalzrod (wrefDokument,wrefDokument_wrt )
go

if exists (select * from sysindexes where name='FKI_n5sodgroup_pSODGroup')
	drop index n5sodgroup.FKI_n5sodgroup_pSODGroup
go

create index FKI_n5sodgroup_pSODGroup on n5sodgroup (pSODGroup)
go

if exists (select * from sysindexes where name='FKI_n5sod_pSODGroup')
	drop index n5sod.FKI_n5sod_pSODGroup
go

create index FKI_n5sod_pSODGroup on n5sod (pSODGroup)
go

if exists (select * from sysindexes where name='FKI_n5securityobj_pSOD')
	drop index n5securityobj.FKI_n5securityobj_pSOD
go

create index FKI_n5securityobj_pSOD on n5securityobj (pSOD)
go

if exists (select * from sysindexes where name='FKI_n5securityobj_pUser')
	drop index n5securityobj.FKI_n5securityobj_pUser
go

create index FKI_n5securityobj_pUser on n5securityobj (pUser)
go

if exists (select * from sysindexes where name='FKI_n5dpc_pDocTemplate')
	drop index n5dpc.FKI_n5dpc_pDocTemplate
go

create index FKI_n5dpc_pDocTemplate on n5dpc (pDocTemplate)
go

if exists (select * from sysindexes where name='FKI_n5userprof_pn5user')
	drop index n5userprof.FKI_n5userprof_pn5user
go

create index FKI_n5userprof_pn5user on n5userprof (pn5user)
go

if exists (select * from sysindexes where name='FKI_n5userfile_pUzytkownik')
	drop index n5userfile.FKI_n5userfile_pUzytkownik
go

create index FKI_n5userfile_pUzytkownik on n5userfile (pUzytkownik)
go

-- end of script ----
