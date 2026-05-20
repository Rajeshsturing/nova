-- NAVO Enterprise SQL script (drop) --
-- generated: 10/1/2020 6:06:47 PM
use %DBNAME%
go
--========= dropping FK =========

if exists (select * from sysobjects where name='FK_n5userfile_n5uzytkownik_3')
	alter table n5userfile drop constraint FK_n5userfile_n5uzytkownik_3
go
if exists (select * from sysobjects where name='ENUM_n5typdokumentu_eRodzaj_4')
	alter table n5typdokumentu drop constraint ENUM_n5typdokumentu_eRodzaj_4
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
if exists (select * from sysobjects where name='ENUM_n5pozsprzedaz_psp_iJPK_GTU_38')
	alter table n5pozsprzedaz drop constraint ENUM_n5pozsprzedaz_psp_iJPK_GTU_38
go
if exists (select * from sysobjects where name='FK_n5egzemplarz_n5produkt_2')
	alter table n5egzemplarz drop constraint FK_n5egzemplarz_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5egzemplarz_n5opakowanie_produktu_3')
	alter table n5egzemplarz drop constraint FK_n5egzemplarz_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='ENUM_n5doketyk_doet_eTypOper_3')
	alter table n5doketyk drop constraint ENUM_n5doketyk_doet_eTypOper_3
go
if exists (select * from sysobjects where name='FK_n5doketyk_n5uzytkownik_5')
	alter table n5doketyk drop constraint FK_n5doketyk_n5uzytkownik_5
go
if exists (select * from sysobjects where name='FK_n5doketyk_n5jedn_org_6')
	alter table n5doketyk drop constraint FK_n5doketyk_n5jedn_org_6
go
if exists (select * from sysobjects where name='FK_n5doketyk_n5uzytkownik_19')
	alter table n5doketyk drop constraint FK_n5doketyk_n5uzytkownik_19
go
if exists (select * from sysobjects where name='FK_n5klient_obiekt_n5klient_4')
	alter table n5klient_obiekt drop constraint FK_n5klient_obiekt_n5klient_4
go
if exists (select * from sysobjects where name='FK_n5ptstan_n5produkt_2')
	alter table n5ptstan drop constraint FK_n5ptstan_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5ptstan_n5opakowanie_produktu_3')
	alter table n5ptstan drop constraint FK_n5ptstan_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5ptstan_n5rejestrdok_4')
	alter table n5ptstan drop constraint FK_n5ptstan_n5rejestrdok_4
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
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5jednostka_54')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5jednostka_54
go
if exists (select * from sysobjects where name='FK_n5sprzedaz_n5uzytkownik_78')
	alter table n5sprzedaz drop constraint FK_n5sprzedaz_n5uzytkownik_78
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
if exists (select * from sysobjects where name='FK_n5zadaniedw_n5wykonawca_2')
	alter table n5zadaniedw drop constraint FK_n5zadaniedw_n5wykonawca_2
go
if exists (select * from sysobjects where name='FK_n5poznotaods_n5transakcja_2')
	alter table n5poznotaods drop constraint FK_n5poznotaods_n5transakcja_2
go
if exists (select * from sysobjects where name='FK_n5poz_hist_stan_n5stanowisko_2')
	alter table n5poz_hist_stan drop constraint FK_n5poz_hist_stan_n5stanowisko_2
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_ePlec_9')
	alter table n5pracownik drop constraint ENUM_n5pracownik_ePlec_9
go
if exists (select * from sysobjects where name='FK_n5pracownik_n5miejscowosc_15')
	alter table n5pracownik drop constraint FK_n5pracownik_n5miejscowosc_15
go
if exists (select * from sysobjects where name='FK_n5pracownik_n5kraj_16')
	alter table n5pracownik drop constraint FK_n5pracownik_n5kraj_16
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_eAktywny_28')
	alter table n5pracownik drop constraint ENUM_n5pracownik_eAktywny_28
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_eTypDT_30')
	alter table n5pracownik drop constraint ENUM_n5pracownik_eTypDT_30
go
if exists (select * from sysobjects where name='FK_n5pracownik_n5jedn_org_33')
	alter table n5pracownik drop constraint FK_n5pracownik_n5jedn_org_33
go
if exists (select * from sysobjects where name='ENUM_n5pracownik_eprac_Oddzial_NFZ_61')
	alter table n5pracownik drop constraint ENUM_n5pracownik_eprac_Oddzial_NFZ_61
go
if exists (select * from sysobjects where name='FK_n5WizzardEmailDokumElem_n5dokument_2')
	alter table n5WizzardEmailDokumElem drop constraint FK_n5WizzardEmailDokumElem_n5dokument_2
go
if exists (select * from sysobjects where name='ENUM_n5vatue_vtue_eTypPlatnika_15')
	alter table n5vatue drop constraint ENUM_n5vatue_vtue_eTypPlatnika_15
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
if exists (select * from sysobjects where name='ENUM_n5magazyn_mag_eAktywny_6')
	alter table n5magazyn drop constraint ENUM_n5magazyn_mag_eAktywny_6
go
if exists (select * from sysobjects where name='ENUM_n5rozlvat_vat7_eTypPlatnika_16')
	alter table n5rozlvat drop constraint ENUM_n5rozlvat_vat7_eTypPlatnika_16
go
if exists (select * from sysobjects where name='FK_n5pllistaplac_n5rejestrdok_6')
	alter table n5pllistaplac drop constraint FK_n5pllistaplac_n5rejestrdok_6
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
if exists (select * from sysobjects where name='FK_n5bwinfo_n5uzytkownik_17')
	alter table n5bwinfo drop constraint FK_n5bwinfo_n5uzytkownik_17
go
if exists (select * from sysobjects where name='ENUM_n5tabela_rozmiarow_crz_eAktywna_3')
	alter table n5tabela_rozmiarow drop constraint ENUM_n5tabela_rozmiarow_crz_eAktywna_3
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5opakowanie_produktu_3')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_19')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_19
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_20')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_20
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_21')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_21
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_22')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_22
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_23')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_23
go
if exists (select * from sysobjects where name='FK_n5produkt_magazyn_n5jednostka_24')
	alter table n5produkt_magazyn drop constraint FK_n5produkt_magazyn_n5jednostka_24
go
if exists (select * from sysobjects where name='FK_n5plstawka_n5jednostka_7')
	alter table n5plstawka drop constraint FK_n5plstawka_n5jednostka_7
go
if exists (select * from sysobjects where name='ENUM_n5gmop_gmo_eTypOp_2')
	alter table n5gmop drop constraint ENUM_n5gmop_gmo_eTypOp_2
go
if exists (select * from sysobjects where name='FK_n5gmop_n5produkt_8')
	alter table n5gmop drop constraint FK_n5gmop_n5produkt_8
go
if exists (select * from sysobjects where name='FK_n5gmop_n5opakowanie_produktu_9')
	alter table n5gmop drop constraint FK_n5gmop_n5opakowanie_produktu_9
go
if exists (select * from sysobjects where name='FK_n5gmop_n5magazyn_10')
	alter table n5gmop drop constraint FK_n5gmop_n5magazyn_10
go
if exists (select * from sysobjects where name='FK_n5projekt_abas_n5kraj_10')
	alter table n5projekt_abas drop constraint FK_n5projekt_abas_n5kraj_10
go
if exists (select * from sysobjects where name='FK_n5projekt_abas_n5jednostka_13')
	alter table n5projekt_abas drop constraint FK_n5projekt_abas_n5jednostka_13
go
if exists (select * from sysobjects where name='FK_n5projekt_abas_n5klient_23')
	alter table n5projekt_abas drop constraint FK_n5projekt_abas_n5klient_23
go
if exists (select * from sysobjects where name='ENUM_n5projekt_abas_proj_eStatus_25')
	alter table n5projekt_abas drop constraint ENUM_n5projekt_abas_proj_eStatus_25
go
if exists (select * from sysobjects where name='FK_n5pozdok_zalacznik_n5dokument_2')
	alter table n5pozdok_zalacznik drop constraint FK_n5pozdok_zalacznik_n5dokument_2
go
if exists (select * from sysobjects where name='FK_n5klient_grupaprod_n5klient_2')
	alter table n5klient_grupaprod drop constraint FK_n5klient_grupaprod_n5klient_2
go
if exists (select * from sysobjects where name='FK_n5klient_grupaprod_n5grupaproduktow_3')
	alter table n5klient_grupaprod drop constraint FK_n5klient_grupaprod_n5grupaproduktow_3
go
if exists (select * from sysobjects where name='FK_n5kraj_n5jednostka_4')
	alter table n5kraj drop constraint FK_n5kraj_n5jednostka_4
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
if exists (select * from sysobjects where name='ENUM_n5transakcja_trn_eRodzaj_17')
	alter table n5transakcja drop constraint ENUM_n5transakcja_trn_eRodzaj_17
go
if exists (select * from sysobjects where name='ENUM_n5eventlog_eTyp_2')
	alter table n5eventlog drop constraint ENUM_n5eventlog_eTyp_2
go
if exists (select * from sysobjects where name='FK_n5eventlog_n5uzytkownik_5')
	alter table n5eventlog drop constraint FK_n5eventlog_n5uzytkownik_5
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
if exists (select * from sysobjects where name='ENUM_n5pozrealprod_eRodzajWyceny_27')
	alter table n5pozrealprod drop constraint ENUM_n5pozrealprod_eRodzajWyceny_27
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_oper_n5recepta_4')
	alter table n5pozrecepta_oper drop constraint FK_n5pozrecepta_oper_n5recepta_4
go
if exists (select * from sysobjects where name='FK_n5inwark_n5inwmag_5')
	alter table n5inwark drop constraint FK_n5inwark_n5inwmag_5
go
if exists (select * from sysobjects where name='ENUM_n5inwark_ia_eStatus_8')
	alter table n5inwark drop constraint ENUM_n5inwark_ia_eStatus_8
go
if exists (select * from sysobjects where name='FK_n5wojewodztwo_n5kraj_3')
	alter table n5wojewodztwo drop constraint FK_n5wojewodztwo_n5kraj_3
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
if exists (select * from sysobjects where name='FK_n5dokument_n5uzytkownik_40')
	alter table n5dokument drop constraint FK_n5dokument_n5uzytkownik_40
go
if exists (select * from sysobjects where name='FK_n5dokument_n5uzytkownik_41')
	alter table n5dokument drop constraint FK_n5dokument_n5uzytkownik_41
go
if exists (select * from sysobjects where name='FK_n5pkpir_n5rejestrdok_4')
	alter table n5pkpir drop constraint FK_n5pkpir_n5rejestrdok_4
go
if exists (select * from sysobjects where name='WRT_n5pkpir_pkpir_wrefDokZrodl_19')
	alter table n5pkpir drop constraint WRT_n5pkpir_pkpir_wrefDokZrodl_19
go
if exists (select * from sysobjects where name='FK_n5klient_produkt_n5klient_2')
	alter table n5klient_produkt drop constraint FK_n5klient_produkt_n5klient_2
go
if exists (select * from sysobjects where name='FK_n5klient_produkt_n5produkt_3')
	alter table n5klient_produkt drop constraint FK_n5klient_produkt_n5produkt_3
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_egz_n5egzemplarz_2')
	alter table n5pozdokmag_egz drop constraint FK_n5pozdokmag_egz_n5egzemplarz_2
go
if exists (select * from sysobjects where name='ENUM_n5recepta_rcpt_eAktywny_8')
	alter table n5recepta drop constraint ENUM_n5recepta_rcpt_eAktywny_8
go
if exists (select * from sysobjects where name='ENUM_n5recepta_rcpt_eTyp_11')
	alter table n5recepta drop constraint ENUM_n5recepta_rcpt_eTyp_11
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5uzytkownik_6')
	alter table n5plnieob drop constraint FK_n5plnieob_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5uzytkownik_7')
	alter table n5plnieob drop constraint FK_n5plnieob_n5uzytkownik_7
go
if exists (select * from sysobjects where name='FK_n5plnieob_n5plumowa_8')
	alter table n5plnieob drop constraint FK_n5plnieob_n5plumowa_8
go
if exists (select * from sysobjects where name='ENUM_n5plnieob_eTyp_10')
	alter table n5plnieob drop constraint ENUM_n5plnieob_eTyp_10
go
if exists (select * from sysobjects where name='ENUM_n5plpozkalcp_eTypOkresu_7')
	alter table n5plpozkalcp drop constraint ENUM_n5plpozkalcp_eTypOkresu_7
go
if exists (select * from sysobjects where name='FK_n5zasobprod_n5typzasobprod_5')
	alter table n5zasobprod drop constraint FK_n5zasobprod_n5typzasobprod_5
go
if exists (select * from sysobjects where name='ENUM_n5zasobprod_zsp_eAktywny_8')
	alter table n5zasobprod drop constraint ENUM_n5zasobprod_zsp_eAktywny_8
go
if exists (select * from sysobjects where name='FK_n5_klient_jedn_org_n5miejscowosc_9')
	alter table n5_klient_jedn_org drop constraint FK_n5_klient_jedn_org_n5miejscowosc_9
go
if exists (select * from sysobjects where name='FK_n5_klient_jedn_org_n5kraj_10')
	alter table n5_klient_jedn_org drop constraint FK_n5_klient_jedn_org_n5kraj_10
go
if exists (select * from sysobjects where name='FK_n5_klient_jedn_org_n5klient_28')
	alter table n5_klient_jedn_org drop constraint FK_n5_klient_jedn_org_n5klient_28
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
if exists (select * from sysobjects where name='ENUM_n5produkt_prod_eRodzaj_VATUE_53')
	alter table n5produkt drop constraint ENUM_n5produkt_prod_eRodzaj_VATUE_53
go
if exists (select * from sysobjects where name='ENUM_n5produkt_prod_iJPK_GTU_57')
	alter table n5produkt drop constraint ENUM_n5produkt_prod_iJPK_GTU_57
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
if exists (select * from sysobjects where name='FK_n5dowodksieg_n5uzytkownik_15')
	alter table n5dowodksieg drop constraint FK_n5dowodksieg_n5uzytkownik_15
go
if exists (select * from sysobjects where name='FK_n5kurswalut_n5jednostka_2')
	alter table n5kurswalut drop constraint FK_n5kurswalut_n5jednostka_2
go
if exists (select * from sysobjects where name='FK_n5kurswalut_n5jednostka_3')
	alter table n5kurswalut drop constraint FK_n5kurswalut_n5jednostka_3
go
if exists (select * from sysobjects where name='FK_n5plumowa_n5uzytkownik_6')
	alter table n5plumowa drop constraint FK_n5plumowa_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plumowa_n5uzytkownik_7')
	alter table n5plumowa drop constraint FK_n5plumowa_n5uzytkownik_7
go
if exists (select * from sysobjects where name='ENUM_n5plumowa_eTypUmowy_8')
	alter table n5plumowa drop constraint ENUM_n5plumowa_eTypUmowy_8
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
if exists (select * from sysobjects where name='FK_n5opsrtrw_n5uzytkownik_36')
	alter table n5opsrtrw drop constraint FK_n5opsrtrw_n5uzytkownik_36
go
if exists (select * from sysobjects where name='FK_n5rolawyk_n5rola_2')
	alter table n5rolawyk drop constraint FK_n5rolawyk_n5rola_2
go
if exists (select * from sysobjects where name='FK_n5rolawyk_n5rola_prior_3')
	alter table n5rolawyk drop constraint FK_n5rolawyk_n5rola_prior_3
go
if exists (select * from sysobjects where name='ENUM_n5ptop_gmo_eTypOp_2')
	alter table n5ptop drop constraint ENUM_n5ptop_gmo_eTypOp_2
go
if exists (select * from sysobjects where name='FK_n5ptop_n5produkt_8')
	alter table n5ptop drop constraint FK_n5ptop_n5produkt_8
go
if exists (select * from sysobjects where name='FK_n5ptop_n5opakowanie_produktu_9')
	alter table n5ptop drop constraint FK_n5ptop_n5opakowanie_produktu_9
go
if exists (select * from sysobjects where name='FK_n5ptop_n5rejestrdok_10')
	alter table n5ptop drop constraint FK_n5ptop_n5rejestrdok_10
go
if exists (select * from sysobjects where name='FK_n5poz_koszt_wyjazdu_n5miejscowosc_2')
	alter table n5poz_koszt_wyjazdu drop constraint FK_n5poz_koszt_wyjazdu_n5miejscowosc_2
go
if exists (select * from sysobjects where name='FK_n5poz_koszt_wyjazdu_n5miejscowosc_3')
	alter table n5poz_koszt_wyjazdu drop constraint FK_n5poz_koszt_wyjazdu_n5miejscowosc_3
go
if exists (select * from sysobjects where name='FK_n5poz_koszt_wyjazdu_n5srodek_lok_8')
	alter table n5poz_koszt_wyjazdu drop constraint FK_n5poz_koszt_wyjazdu_n5srodek_lok_8
go
if exists (select * from sysobjects where name='ENUM_n5miejscowosc_eWielkosc_3')
	alter table n5miejscowosc drop constraint ENUM_n5miejscowosc_eWielkosc_3
go
if exists (select * from sysobjects where name='FK_n5miejscowosc_n5wojewodztwo_4')
	alter table n5miejscowosc drop constraint FK_n5miejscowosc_n5wojewodztwo_4
go
if exists (select * from sysobjects where name='WRT_n5SendEmail_wpNadawca_2')
	alter table n5SendEmail drop constraint WRT_n5SendEmail_wpNadawca_2
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
if exists (select * from sysobjects where name='ENUM_n5rejestrdok_rejdok_eZasadaRapKas_17')
	alter table n5rejestrdok drop constraint ENUM_n5rejestrdok_rejdok_eZasadaRapKas_17
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
if exists (select * from sysobjects where name='FK_n5dokmag_n5uzytkownik_39')
	alter table n5dokmag drop constraint FK_n5dokmag_n5uzytkownik_39
go
if exists (select * from sysobjects where name='FK_n5srtrw_n5grupasrtrw_6')
	alter table n5srtrw drop constraint FK_n5srtrw_n5grupasrtrw_6
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eRodzaj_8')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eRodzaj_8
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eMetAmPod_21')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eMetAmPod_21
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eMetAmBil_22')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eMetAmBil_22
go
if exists (select * from sysobjects where name='ENUM_n5srtrw_eStatus_23')
	alter table n5srtrw drop constraint ENUM_n5srtrw_eStatus_23
go
if exists (select * from sysobjects where name='ENUM_n5plsubkonto_eAktywne_5')
	alter table n5plsubkonto drop constraint ENUM_n5plsubkonto_eAktywne_5
go
if exists (select * from sysobjects where name='FK_n5plsubkonto_n5jednostka_6')
	alter table n5plsubkonto drop constraint FK_n5plsubkonto_n5jednostka_6
go
if exists (select * from sysobjects where name='ENUM_n5plsubkonto_eZakres_7')
	alter table n5plsubkonto drop constraint ENUM_n5plsubkonto_eZakres_7
go
if exists (select * from sysobjects where name='WRT_n5bwinfo_zal_wrefZal_2')
	alter table n5bwinfo_zal drop constraint WRT_n5bwinfo_zal_wrefZal_2
go
if exists (select * from sysobjects where name='FK_n5securityobj_n5sod_2')
	alter table n5securityobj drop constraint FK_n5securityobj_n5sod_2
go
if exists (select * from sysobjects where name='FK_n5securityobj_n5uzytkownik_3')
	alter table n5securityobj drop constraint FK_n5securityobj_n5uzytkownik_3
go
if exists (select * from sysobjects where name='FK_n5klient_n5miejscowosc_10')
	alter table n5klient drop constraint FK_n5klient_n5miejscowosc_10
go
if exists (select * from sysobjects where name='FK_n5klient_n5kraj_11')
	alter table n5klient drop constraint FK_n5klient_n5kraj_11
go
if exists (select * from sysobjects where name='ENUM_n5klient_eTypDT_26')
	alter table n5klient drop constraint ENUM_n5klient_eTypDT_26
go
if exists (select * from sysobjects where name='ENUM_n5klient_eAktywny_38')
	alter table n5klient drop constraint ENUM_n5klient_eAktywny_38
go
if exists (select * from sysobjects where name='ENUM_n5klient_eKlasaKlienta_39')
	alter table n5klient drop constraint ENUM_n5klient_eKlasaKlienta_39
go
if exists (select * from sysobjects where name='FK_n5klient_n5jednostka_40')
	alter table n5klient drop constraint FK_n5klient_n5jednostka_40
go
if exists (select * from sysobjects where name='ENUM_n5klient_ePlec_51')
	alter table n5klient drop constraint ENUM_n5klient_ePlec_51
go
if exists (select * from sysobjects where name='FK_n5klient_n5grupaklient_55')
	alter table n5klient drop constraint FK_n5klient_n5grupaklient_55
go
if exists (select * from sysobjects where name='ENUM_n5klient_ePrywat_56')
	alter table n5klient drop constraint ENUM_n5klient_ePrywat_56
go
if exists (select * from sysobjects where name='FK_n5klient_n5kraj_63')
	alter table n5klient drop constraint FK_n5klient_n5kraj_63
go
if exists (select * from sysobjects where name='ENUM_n5klient_eWiarFin_66')
	alter table n5klient drop constraint ENUM_n5klient_eWiarFin_66
go
if exists (select * from sysobjects where name='ENUM_n5klient_kli_eZestawCenowy_78')
	alter table n5klient drop constraint ENUM_n5klient_kli_eZestawCenowy_78
go
if exists (select * from sysobjects where name='ENUM_n5klient_kli_eNazwaProduktu_80')
	alter table n5klient drop constraint ENUM_n5klient_kli_eNazwaProduktu_80
go
if exists (select * from sysobjects where name='ENUM_n5klient_kli_eTyp_86')
	alter table n5klient drop constraint ENUM_n5klient_kli_eTyp_86
go
if exists (select * from sysobjects where name='WRT_n5zadaniezal_wrefZal_2')
	alter table n5zadaniezal drop constraint WRT_n5zadaniezal_wrefZal_2
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
if exists (select * from sysobjects where name='FK_n5zakup_n5jednostka_51')
	alter table n5zakup drop constraint FK_n5zakup_n5jednostka_51
go
if exists (select * from sysobjects where name='ENUM_n5zakup_eZwOpSprz_52')
	alter table n5zakup drop constraint ENUM_n5zakup_eZwOpSprz_52
go
if exists (select * from sysobjects where name='ENUM_n5zakup_eTypZakup_53')
	alter table n5zakup drop constraint ENUM_n5zakup_eTypZakup_53
go
if exists (select * from sysobjects where name='FK_n5zakup_n5uzytkownik_83')
	alter table n5zakup drop constraint FK_n5zakup_n5uzytkownik_83
go
if exists (select * from sysobjects where name='WRT_n5plsklnal_wrefDokument_2')
	alter table n5plsklnal drop constraint WRT_n5plsklnal_wrefDokument_2
go
if exists (select * from sysobjects where name='ENUM_n5istat_istt_eTypDekl_2')
	alter table n5istat drop constraint ENUM_n5istat_istt_eTypDekl_2
go
if exists (select * from sysobjects where name='ENUM_n5istat_istt_eRodzDekl_3')
	alter table n5istat drop constraint ENUM_n5istat_istt_eRodzDekl_3
go
if exists (select * from sysobjects where name='ENUM_n5istat_istt_eTypPlatnika_20')
	alter table n5istat drop constraint ENUM_n5istat_istt_eTypPlatnika_20
go
if exists (select * from sysobjects where name='ENUM_n5istat_istp_eTypPlatnika_37')
	alter table n5istat drop constraint ENUM_n5istat_istp_eTypPlatnika_37
go
if exists (select * from sysobjects where name='FK_n5protokol_abas_n5jednostka_7')
	alter table n5protokol_abas drop constraint FK_n5protokol_abas_n5jednostka_7
go
if exists (select * from sysobjects where name='FK_n5kolor_n5paleta_kolorow_10')
	alter table n5kolor drop constraint FK_n5kolor_n5paleta_kolorow_10
go
if exists (select * from sysobjects where name='ENUM_n5kolor_kol_eAktywny_11')
	alter table n5kolor drop constraint ENUM_n5kolor_kol_eAktywny_11
go
if exists (select * from sysobjects where name='FK_n5instytucja_n5typinstytucji_4')
	alter table n5instytucja drop constraint FK_n5instytucja_n5typinstytucji_4
go
if exists (select * from sysobjects where name='FK_n5instytucja_n5miejscowosc_10')
	alter table n5instytucja drop constraint FK_n5instytucja_n5miejscowosc_10
go
if exists (select * from sysobjects where name='FK_n5instytucja_n5kraj_11')
	alter table n5instytucja drop constraint FK_n5instytucja_n5kraj_11
go
if exists (select * from sysobjects where name='WRT_n5wykonawca_wrefObiekt_3')
	alter table n5wykonawca drop constraint WRT_n5wykonawca_wrefObiekt_3
go
if exists (select * from sysobjects where name='ENUM_n5wykonawca_eAktywny_6')
	alter table n5wykonawca drop constraint ENUM_n5wykonawca_eAktywny_6
go
if exists (select * from sysobjects where name='FK_n5pozrata_n5sposplat_3')
	alter table n5pozrata drop constraint FK_n5pozrata_n5sposplat_3
go
if exists (select * from sysobjects where name='FK_n5pozrata_n5klient_4')
	alter table n5pozrata drop constraint FK_n5pozrata_n5klient_4
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
if exists (select * from sysobjects where name='FK_n5plschematnal_n5plterminnal_9')
	alter table n5plschematnal drop constraint FK_n5plschematnal_n5plterminnal_9
go
if exists (select * from sysobjects where name='ENUM_n5plschematnal_eRodzaj_12')
	alter table n5plschematnal drop constraint ENUM_n5plschematnal_eRodzaj_12
go
if exists (select * from sysobjects where name='FK_n5plschematnal_n5plgrupaschemnal_16')
	alter table n5plschematnal drop constraint FK_n5plschematnal_n5plgrupaschemnal_16
go
if exists (select * from sysobjects where name='ENUM_n5kwalifikator_eAktywny_3')
	alter table n5kwalifikator drop constraint ENUM_n5kwalifikator_eAktywny_3
go
if exists (select * from sysobjects where name='FK_n5plpozschnal_n5plschematnal_2')
	alter table n5plpozschnal drop constraint FK_n5plpozschnal_n5plschematnal_2
go
-- skipped virtual table: n5vatuek
if exists (select * from sysobjects where name='FK_n5pozrealprod_zasob_n5typzasobprod_2')
	alter table n5pozrealprod_zasob drop constraint FK_n5pozrealprod_zasob_n5typzasobprod_2
go
if exists (select * from sysobjects where name='WRT_n5straznik_cen_scs_wpProdGrupa_3')
	alter table n5straznik_cen drop constraint WRT_n5straznik_cen_scs_wpProdGrupa_3
go
if exists (select * from sysobjects where name='WRT_n5straznik_cen_scs_wpKlientGrupa_4')
	alter table n5straznik_cen drop constraint WRT_n5straznik_cen_scs_wpKlientGrupa_4
go
if exists (select * from sysobjects where name='ENUM_n5straznik_cen_scs_eZestawCenowy_6')
	alter table n5straznik_cen drop constraint ENUM_n5straznik_cen_scs_eZestawCenowy_6
go
if exists (select * from sysobjects where name='ENUM_n5straznik_cen_scs_eAktywny_7')
	alter table n5straznik_cen drop constraint ENUM_n5straznik_cen_scs_eAktywny_7
go
if exists (select * from sysobjects where name='ENUM_n5jednostka_eTyp_5')
	alter table n5jednostka drop constraint ENUM_n5jednostka_eTyp_5
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
if exists (select * from sysobjects where name='FK_n5zadanie_n5rejestrdok_54')
	alter table n5zadanie drop constraint FK_n5zadanie_n5rejestrdok_54
go
if exists (select * from sysobjects where name='ENUM_n5typdzialania_tpdz_eAktywny_8')
	alter table n5typdzialania drop constraint ENUM_n5typdzialania_tpdz_eAktywny_8
go
if exists (select * from sysobjects where name='FK_n5zlecprod_n5uzytkownik_4')
	alter table n5zlecprod drop constraint FK_n5zlecprod_n5uzytkownik_4
go
if exists (select * from sysobjects where name='FK_n5zlecprod_n5rejestrdok_6')
	alter table n5zlecprod drop constraint FK_n5zlecprod_n5rejestrdok_6
go
if exists (select * from sysobjects where name='FK_n5zlecprod_n5uzytkownik_27')
	alter table n5zlecprod drop constraint FK_n5zlecprod_n5uzytkownik_27
go
if exists (select * from sysobjects where name='ENUM_n5zlecprod_zlp_eStatus_28')
	alter table n5zlecprod drop constraint ENUM_n5zlecprod_zlp_eStatus_28
go
if exists (select * from sysobjects where name='ENUM_n5rule_eSignificance_5')
	alter table n5rule drop constraint ENUM_n5rule_eSignificance_5
go
if exists (select * from sysobjects where name='FK_n5plpozostale_n5uzytkownik_6')
	alter table n5plpozostale drop constraint FK_n5plpozostale_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plpozostale_n5uzytkownik_7')
	alter table n5plpozostale drop constraint FK_n5plpozostale_n5uzytkownik_7
go
if exists (select * from sysobjects where name='FK_n5plpozostale_n5plumowa_8')
	alter table n5plpozostale drop constraint FK_n5plpozostale_n5plumowa_8
go
if exists (select * from sysobjects where name='FK_n5pozdokprod_n5produkt_2')
	alter table n5pozdokprod drop constraint FK_n5pozdokprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozdokprod_n5opakowanie_produktu_3')
	alter table n5pozdokprod drop constraint FK_n5pozdokprod_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5pozdokprod_n5jednostka_5')
	alter table n5pozdokprod drop constraint FK_n5pozdokprod_n5jednostka_5
go
if exists (select * from sysobjects where name='FK_n5pozdokprod_n5klient_obiekt_6')
	alter table n5pozdokprod drop constraint FK_n5pozdokprod_n5klient_obiekt_6
go
if exists (select * from sysobjects where name='ENUM_n5pozdokprod_pdp_eRegulaNaliczania_8')
	alter table n5pozdokprod drop constraint ENUM_n5pozdokprod_pdp_eRegulaNaliczania_8
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_zasob_n5typzasobprod_2')
	alter table n5pozrecepta_zasob drop constraint FK_n5pozrecepta_zasob_n5typzasobprod_2
go
if exists (select * from sysobjects where name='FK_n5inwmag_n5magazyn_5')
	alter table n5inwmag drop constraint FK_n5inwmag_n5magazyn_5
go
if exists (select * from sysobjects where name='ENUM_n5inwmag_im_eStatus_8')
	alter table n5inwmag drop constraint ENUM_n5inwmag_im_eStatus_8
go
if exists (select * from sysobjects where name='FK_n5dokumentlinks_n5dokument_2')
	alter table n5dokumentlinks drop constraint FK_n5dokumentlinks_n5dokument_2
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
if exists (select * from sysobjects where name='FK_n5platnosc_n5uzytkownik_26')
	alter table n5platnosc drop constraint FK_n5platnosc_n5uzytkownik_26
go
if exists (select * from sysobjects where name='FK_n5pozdoketyk_n5produkt_3')
	alter table n5pozdoketyk drop constraint FK_n5pozdoketyk_n5produkt_3
go
if exists (select * from sysobjects where name='FK_n5pozdoketyk_n5opakowanie_produktu_4')
	alter table n5pozdoketyk drop constraint FK_n5pozdoketyk_n5opakowanie_produktu_4
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_n5produkt_2')
	alter table n5pozrecepta drop constraint FK_n5pozrecepta_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_n5opakowanie_produktu_3')
	alter table n5pozrecepta drop constraint FK_n5pozrecepta_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='ENUM_n5pozrecepta_eRodzajWyceny_6')
	alter table n5pozrecepta drop constraint ENUM_n5pozrecepta_eRodzajWyceny_6
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5uzytkownik_6')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5uzytkownik_7')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5uzytkownik_7
go
if exists (select * from sysobjects where name='FK_n5plchoroba_n5plumowa_8')
	alter table n5plchoroba drop constraint FK_n5plchoroba_n5plumowa_8
go
if exists (select * from sysobjects where name='ENUM_n5plkalcp_eAktywny_3')
	alter table n5plkalcp drop constraint ENUM_n5plkalcp_eAktywny_3
go
if exists (select * from sysobjects where name='FK_n5plrcp_n5pracownik_2')
	alter table n5plrcp drop constraint FK_n5plrcp_n5pracownik_2
go
if exists (select * from sysobjects where name='FK_n5plrcp_n5plumowa_3')
	alter table n5plrcp drop constraint FK_n5plrcp_n5plumowa_3
go
if exists (select * from sysobjects where name='FK_n5plrcp_n5uzytkownik_5')
	alter table n5plrcp drop constraint FK_n5plrcp_n5uzytkownik_5
go
if exists (select * from sysobjects where name='FK_n5plrcp_n5pltyppracy_11')
	alter table n5plrcp drop constraint FK_n5plrcp_n5pltyppracy_11
go
if exists (select * from sysobjects where name='FK_n5transakcja_operacja_n5transakcja_2')
	alter table n5transakcja_operacja drop constraint FK_n5transakcja_operacja_n5transakcja_2
go
if exists (select * from sysobjects where name='WRT_n5transakcja_operacja_trop_wrefDokument_3')
	alter table n5transakcja_operacja drop constraint WRT_n5transakcja_operacja_trop_wrefDokument_3
go
if exists (select * from sysobjects where name='FK_n5transakcja_operacja_n5uzytkownik_11')
	alter table n5transakcja_operacja drop constraint FK_n5transakcja_operacja_n5uzytkownik_11
go
if exists (select * from sysobjects where name='FK_n5transakcja_operacja_n5uzytkownik_12')
	alter table n5transakcja_operacja drop constraint FK_n5transakcja_operacja_n5uzytkownik_12
go
if exists (select * from sysobjects where name='FK_n5ankieta_toral_n5uzytkownik_2')
	alter table n5ankieta_toral drop constraint FK_n5ankieta_toral_n5uzytkownik_2
go
if exists (select * from sysobjects where name='FK_n5ankieta_toral_n5klient_5')
	alter table n5ankieta_toral drop constraint FK_n5ankieta_toral_n5klient_5
go
if exists (select * from sysobjects where name='ENUM_n5ankieta_toral_ank_ePowGosp_7')
	alter table n5ankieta_toral drop constraint ENUM_n5ankieta_toral_ank_ePowGosp_7
go
if exists (select * from sysobjects where name='FK_n5userprof_n5uzytkownik_4')
	alter table n5userprof drop constraint FK_n5userprof_n5uzytkownik_4
go
if exists (select * from sysobjects where name='FK_n5jedn_org_n5miejscowosc_11')
	alter table n5jedn_org drop constraint FK_n5jedn_org_n5miejscowosc_11
go
if exists (select * from sysobjects where name='FK_n5jedn_org_n5kraj_12')
	alter table n5jedn_org drop constraint FK_n5jedn_org_n5kraj_12
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
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_40')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_40
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_41')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_41
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_42')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_42
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_43')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_43
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_44')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_44
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_45')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_45
go
if exists (select * from sysobjects where name='ENUM_n5opakowanie_produktu_opak_eRodzajNrSer_46')
	alter table n5opakowanie_produktu drop constraint ENUM_n5opakowanie_produktu_opak_eRodzajNrSer_46
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_60')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_60
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_63')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_63
go
if exists (select * from sysobjects where name='FK_n5opakowanie_produktu_n5jednostka_66')
	alter table n5opakowanie_produktu drop constraint FK_n5opakowanie_produktu_n5jednostka_66
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
if exists (select * from sysobjects where name='ENUM_n5sposplat_eTyp_4')
	alter table n5sposplat drop constraint ENUM_n5sposplat_eTyp_4
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5pracownik_3')
	alter table n5pldekret drop constraint FK_n5pldekret_n5pracownik_3
go
if exists (select * from sysobjects where name='FK_n5pldekret_n5plsubkonto_4')
	alter table n5pldekret drop constraint FK_n5pldekret_n5plsubkonto_4
go
if exists (select * from sysobjects where name='WRT_n5pldekret_wrefDokument_8')
	alter table n5pldekret drop constraint WRT_n5pldekret_wrefDokument_8
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
if exists (select * from sysobjects where name='FK_n5notaods_n5uzytkownik_19')
	alter table n5notaods drop constraint FK_n5notaods_n5uzytkownik_19
go
if exists (select * from sysobjects where name='FK_n5zadanie_rola_n5rola_2')
	alter table n5zadanie_rola drop constraint FK_n5zadanie_rola_n5rola_2
go
if exists (select * from sysobjects where name='FK_n5zadanie_rola_n5rola_prior_3')
	alter table n5zadanie_rola drop constraint FK_n5zadanie_rola_n5rola_prior_3
go
if exists (select * from sysobjects where name='ENUM_n5polecenie_wyjazdu_pws_eTyp_3')
	alter table n5polecenie_wyjazdu drop constraint ENUM_n5polecenie_wyjazdu_pws_eTyp_3
go
if exists (select * from sysobjects where name='FK_n5polecenie_wyjazdu_n5pracownik_6')
	alter table n5polecenie_wyjazdu drop constraint FK_n5polecenie_wyjazdu_n5pracownik_6
go
if exists (select * from sysobjects where name='FK_n5polecenie_wyjazdu_n5stanowisko_7')
	alter table n5polecenie_wyjazdu drop constraint FK_n5polecenie_wyjazdu_n5stanowisko_7
go
if exists (select * from sysobjects where name='FK_n5polecenie_wyjazdu_n5uzytkownik_13')
	alter table n5polecenie_wyjazdu drop constraint FK_n5polecenie_wyjazdu_n5uzytkownik_13
go
if exists (select * from sysobjects where name='FK_n5polecenie_wyjazdu_n5jednostka_16')
	alter table n5polecenie_wyjazdu drop constraint FK_n5polecenie_wyjazdu_n5jednostka_16
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
if exists (select * from sysobjects where name='FK_n5firma_n5miejscowosc_9')
	alter table n5firma drop constraint FK_n5firma_n5miejscowosc_9
go
if exists (select * from sysobjects where name='FK_n5firma_n5kraj_10')
	alter table n5firma drop constraint FK_n5firma_n5kraj_10
go
if exists (select * from sysobjects where name='ENUM_n5firma_eForma_22')
	alter table n5firma drop constraint ENUM_n5firma_eForma_22
go
if exists (select * from sysobjects where name='FK_n5firma_n5jednostka_34')
	alter table n5firma drop constraint FK_n5firma_n5jednostka_34
go
if exists (select * from sysobjects where name='FK_n5firma_n5jedn_org_40')
	alter table n5firma drop constraint FK_n5firma_n5jedn_org_40
go
if exists (select * from sysobjects where name='ENUM_n5firma_frm_eTypDT_43')
	alter table n5firma drop constraint ENUM_n5firma_frm_eTypDT_43
go
if exists (select * from sysobjects where name='FK_n5WizzardEmail_choicelist_2')
	alter table n5WizzardEmail drop constraint FK_n5WizzardEmail_choicelist_2
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
if exists (select * from sysobjects where name='WRT_n5bwinfo_produkt_wpProdGrupa_2')
	alter table n5bwinfo_produkt drop constraint WRT_n5bwinfo_produkt_wpProdGrupa_2
go
if exists (select * from sysobjects where name='FK_n5rozmiar_n5tabela_rozmiarow_4')
	alter table n5rozmiar drop constraint FK_n5rozmiar_n5tabela_rozmiarow_4
go
if exists (select * from sysobjects where name='ENUM_n5rozmiar_roz_eAktywny_5')
	alter table n5rozmiar drop constraint ENUM_n5rozmiar_roz_eAktywny_5
go
if exists (select * from sysobjects where name='ENUM_n5pojazd_poj_eTyp_3')
	alter table n5pojazd drop constraint ENUM_n5pojazd_poj_eTyp_3
go
if exists (select * from sysobjects where name='FK_n5pojazd_n5klient_23')
	alter table n5pojazd drop constraint FK_n5pojazd_n5klient_23
go
if exists (select * from sysobjects where name='FK_n5pojazd_n5pracownik_27')
	alter table n5pojazd drop constraint FK_n5pojazd_n5pracownik_27
go
if exists (select * from sysobjects where name='FK_n5pojazd_n5jednostka_31')
	alter table n5pojazd drop constraint FK_n5pojazd_n5jednostka_31
go
if exists (select * from sysobjects where name='FK_n5sod_n5sodgroup_3')
	alter table n5sod drop constraint FK_n5sod_n5sodgroup_3
go
if exists (select * from sysobjects where name='ENUM_n5uzytkownik_eAktywny_7')
	alter table n5uzytkownik drop constraint ENUM_n5uzytkownik_eAktywny_7
go
if exists (select * from sysobjects where name='ENUM_choicelist_edynamic_4')
	alter table choicelist drop constraint ENUM_choicelist_edynamic_4
go
if exists (select * from sysobjects where name='FK_n5rapkas_n5rejestrdok_5')
	alter table n5rapkas drop constraint FK_n5rapkas_n5rejestrdok_5
go
if exists (select * from sysobjects where name='FK_n5rapkas_n5uzytkownik_9')
	alter table n5rapkas drop constraint FK_n5rapkas_n5uzytkownik_9
go
if exists (select * from sysobjects where name='FK_n5rapkas_n5uzytkownik_16')
	alter table n5rapkas drop constraint FK_n5rapkas_n5uzytkownik_16
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
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5uzytkownik_6')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5uzytkownik_6
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5uzytkownik_7')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5uzytkownik_7
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5rejestrdok_8')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5rejestrdok_8
go
if exists (select * from sysobjects where name='FK_n5plnaliczenie_n5pllistaplac_13')
	alter table n5plnaliczenie drop constraint FK_n5plnaliczenie_n5pllistaplac_13
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
if exists (select * from sysobjects where name='FK_n5gmstan_n5produkt_2')
	alter table n5gmstan drop constraint FK_n5gmstan_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5gmstan_n5opakowanie_produktu_3')
	alter table n5gmstan drop constraint FK_n5gmstan_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='FK_n5gmstan_n5magazyn_4')
	alter table n5gmstan drop constraint FK_n5gmstan_n5magazyn_4
go
if exists (select * from sysobjects where name='FK_n5pozprojekt_abas_n5produkt_2')
	alter table n5pozprojekt_abas drop constraint FK_n5pozprojekt_abas_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozprojekt_abas_n5opakowanie_produktu_3')
	alter table n5pozprojekt_abas drop constraint FK_n5pozprojekt_abas_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='ENUM_n5paleta_kolorow_pkol_eAktywna_3')
	alter table n5paleta_kolorow drop constraint ENUM_n5paleta_kolorow_pkol_eAktywna_3
go
if exists (select * from sysobjects where name='FK_n5bank_n5miejscowosc_11')
	alter table n5bank drop constraint FK_n5bank_n5miejscowosc_11
go
if exists (select * from sysobjects where name='FK_n5bank_n5kraj_12')
	alter table n5bank drop constraint FK_n5bank_n5kraj_12
go
if exists (select * from sysobjects where name='FK_n5pozplatnosc_n5transakcja_7')
	alter table n5pozplatnosc drop constraint FK_n5pozplatnosc_n5transakcja_7
go
if exists (select * from sysobjects where name='ENUM_n5pit11_pt11_eTypPlatnika_16')
	alter table n5pit11 drop constraint ENUM_n5pit11_pt11_eTypPlatnika_16
go
if exists (select * from sysobjects where name='ENUM_n5pit11_pt11_eKosztUPOd_45')
	alter table n5pit11 drop constraint ENUM_n5pit11_pt11_eKosztUPOd_45
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
if exists (select * from sysobjects where name='ENUM_n5zamowienie_zam_eWaznoscZam_40')
	alter table n5zamowienie drop constraint ENUM_n5zamowienie_zam_eWaznoscZam_40
go
if exists (select * from sysobjects where name='FK_n5zamowienie_n5uzytkownik_45')
	alter table n5zamowienie drop constraint FK_n5zamowienie_n5uzytkownik_45
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
if exists (select * from sysobjects where name='FK_n5polrab_n5jednostka_11')
	alter table n5polrab drop constraint FK_n5polrab_n5jednostka_11
go
if exists (select * from sysobjects where name='ENUM_n5polrab_polrab_eZestawCenowy_12')
	alter table n5polrab drop constraint ENUM_n5polrab_polrab_eZestawCenowy_12
go
if exists (select * from sysobjects where name='FK_n5realprod_n5uzytkownik_7')
	alter table n5realprod drop constraint FK_n5realprod_n5uzytkownik_7
go
if exists (select * from sysobjects where name='FK_n5realprod_n5rejestrdok_9')
	alter table n5realprod drop constraint FK_n5realprod_n5rejestrdok_9
go
if exists (select * from sysobjects where name='FK_n5realprod_n5uzytkownik_30')
	alter table n5realprod drop constraint FK_n5realprod_n5uzytkownik_30
go
-- skipped virtual table: n5pit4r
if exists (select * from sysobjects where name='ENUM_n5prop_prop_eStatus_3')
	alter table n5prop drop constraint ENUM_n5prop_prop_eStatus_3
go
if exists (select * from sysobjects where name='ENUM_n5prop_prop_eTyp_4')
	alter table n5prop drop constraint ENUM_n5prop_prop_eTyp_4
go
if exists (select * from sysobjects where name='FK_n5prop_n5zlecprod_5')
	alter table n5prop drop constraint FK_n5prop_n5zlecprod_5
go
if exists (select * from sysobjects where name='FK_n5pozinwark_n5produkt_2')
	alter table n5pozinwark drop constraint FK_n5pozinwark_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozinwark_n5opakowanie_produktu_3')
	alter table n5pozinwark drop constraint FK_n5pozinwark_n5opakowanie_produktu_3
go
if exists (select * from sysobjects where name='ENUM_n5grupaklient_gkli_eZestawCenowy_6')
	alter table n5grupaklient drop constraint ENUM_n5grupaklient_gkli_eZestawCenowy_6
go
if exists (select * from sysobjects where name='ENUM_n5pit4_pt4_eTypPlatnika_3')
	alter table n5pit4 drop constraint ENUM_n5pit4_pt4_eTypPlatnika_3
go
if exists (select * from sysobjects where name='FK_n5klient_opakowanie_n5opakowanie_produktu_2')
	alter table n5klient_opakowanie drop constraint FK_n5klient_opakowanie_n5opakowanie_produktu_2
go
if exists (select * from sysobjects where name='FK_n5proglojal_n5klient_3')
	alter table n5proglojal drop constraint FK_n5proglojal_n5klient_3
go
if exists (select * from sysobjects where name='ENUM_n5proglojal_proloj_eTypOper_9')
	alter table n5proglojal drop constraint ENUM_n5proglojal_proloj_eTypOper_9
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
if exists (select * from sysobjects where name='FK_n5rozlcit_n5uzytkownik_34')
	alter table n5rozlcit drop constraint FK_n5rozlcit_n5uzytkownik_34
go
if exists (select * from sysobjects where name='FK_n5rozlcit_n5uzytkownik_61')
	alter table n5rozlcit drop constraint FK_n5rozlcit_n5uzytkownik_61
go
if exists (select * from sysobjects where name='FK_n5plsklwyn_n5plschematnal_2')
	alter table n5plsklwyn drop constraint FK_n5plsklwyn_n5plschematnal_2
go
if exists (select * from sysobjects where name='FK_n5plsklwyn_n5plterminnal_5')
	alter table n5plsklwyn drop constraint FK_n5plsklwyn_n5plterminnal_5
go
if exists (select * from sysobjects where name='ENUM_n5typzasobprod_tzp_eRodzaj_4')
	alter table n5typzasobprod drop constraint ENUM_n5typzasobprod_tzp_eRodzaj_4
go
if exists (select * from sysobjects where name='ENUM_n5typzasobprod_tzp_eAktywny_6')
	alter table n5typzasobprod drop constraint ENUM_n5typzasobprod_tzp_eAktywny_6
go
--========= dropping PK =========

if exists (select * from sysobjects where name='PK_n5userfile_IdObj')
	alter table n5userfile drop constraint PK_n5userfile_IdObj
go
if exists (select * from sysobjects where name='PK_n5typdokumentu_IdObj')
	alter table n5typdokumentu drop constraint PK_n5typdokumentu_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozsprzedaz_IdObj')
	alter table n5pozsprzedaz drop constraint PK_n5pozsprzedaz_IdObj
go
if exists (select * from sysobjects where name='PK_n5egzemplarz_IdObj')
	alter table n5egzemplarz drop constraint PK_n5egzemplarz_IdObj
go
if exists (select * from sysobjects where name='PK_n5doketyk_IdObj')
	alter table n5doketyk drop constraint PK_n5doketyk_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_obiekt_IdObj')
	alter table n5klient_obiekt drop constraint PK_n5klient_obiekt_IdObj
go
if exists (select * from sysobjects where name='PK_n5ptstan_IdObj')
	alter table n5ptstan drop constraint PK_n5ptstan_IdObj
go
if exists (select * from sysobjects where name='PK_n5srodek_lok_IdObj')
	alter table n5srodek_lok drop constraint PK_n5srodek_lok_IdObj
go
if exists (select * from sysobjects where name='PK_n5globprof_IdObj')
	alter table n5globprof drop constraint PK_n5globprof_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_pracownik_IdObj')
	alter table n5klient_pracownik drop constraint PK_n5klient_pracownik_IdObj
go
if exists (select * from sysobjects where name='PK_n5sprzedaz_IdObj')
	alter table n5sprzedaz drop constraint PK_n5sprzedaz_IdObj
go
if exists (select * from sysobjects where name='PK_n5konto_IdObj')
	alter table n5konto drop constraint PK_n5konto_IdObj
go
if exists (select * from sysobjects where name='PK_n5zadaniedw_IdObj')
	alter table n5zadaniedw drop constraint PK_n5zadaniedw_IdObj
go
if exists (select * from sysobjects where name='PK_n5poznotaods_IdObj')
	alter table n5poznotaods drop constraint PK_n5poznotaods_IdObj
go
if exists (select * from sysobjects where name='PK_n5rola_prior_IdObj')
	alter table n5rola_prior drop constraint PK_n5rola_prior_IdObj
go
if exists (select * from sysobjects where name='PK_n5poz_hist_stan_IdObj')
	alter table n5poz_hist_stan drop constraint PK_n5poz_hist_stan_IdObj
go
if exists (select * from sysobjects where name='PK_n5miesiac_IdObj')
	alter table n5miesiac drop constraint PK_n5miesiac_IdObj
go
if exists (select * from sysobjects where name='PK_n5pracownik_IdObj')
	alter table n5pracownik drop constraint PK_n5pracownik_IdObj
go
if exists (select * from sysobjects where name='PK_n5WizzardEmailDokumElem_IdObj')
	alter table n5WizzardEmailDokumElem drop constraint PK_n5WizzardEmailDokumElem_IdObj
go
if exists (select * from sysobjects where name='PK_n5vatue_IdObj')
	alter table n5vatue drop constraint PK_n5vatue_IdObj
go
if exists (select * from sysobjects where name='PK_n5magazyn_IdObj')
	alter table n5magazyn drop constraint PK_n5magazyn_IdObj
go
if exists (select * from sysobjects where name='PK_n5rozlvat_IdObj')
	alter table n5rozlvat drop constraint PK_n5rozlvat_IdObj
go
if exists (select * from sysobjects where name='PK_n5pllistaplac_IdObj')
	alter table n5pllistaplac drop constraint PK_n5pllistaplac_IdObj
go
if exists (select * from sysobjects where name='PK_n5bwinfo_IdObj')
	alter table n5bwinfo drop constraint PK_n5bwinfo_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozistat_IdObj')
	alter table n5pozistat drop constraint PK_n5pozistat_IdObj
go
if exists (select * from sysobjects where name='PK_n5tabela_rozmiarow_IdObj')
	alter table n5tabela_rozmiarow drop constraint PK_n5tabela_rozmiarow_IdObj
go
if exists (select * from sysobjects where name='PK_n5produkt_magazyn_IdObj')
	alter table n5produkt_magazyn drop constraint PK_n5produkt_magazyn_IdObj
go
if exists (select * from sysobjects where name='PK_n5sodgroup_IdObj')
	alter table n5sodgroup drop constraint PK_n5sodgroup_IdObj
go
if exists (select * from sysobjects where name='PK_n5licencja_IdObj')
	alter table n5licencja drop constraint PK_n5licencja_IdObj
go
if exists (select * from sysobjects where name='PK_choicelistitem_IdObj')
	alter table choicelistitem drop constraint PK_choicelistitem_IdObj
go
if exists (select * from sysobjects where name='PK_n5gmina_IdObj')
	alter table n5gmina drop constraint PK_n5gmina_IdObj
go
if exists (select * from sysobjects where name='PK_n5branza_IdObj')
	alter table n5branza drop constraint PK_n5branza_IdObj
go
if exists (select * from sysobjects where name='PK_n5plstawka_IdObj')
	alter table n5plstawka drop constraint PK_n5plstawka_IdObj
go
if exists (select * from sysobjects where name='PK_n5budzet_IdObj')
	alter table n5budzet drop constraint PK_n5budzet_IdObj
go
if exists (select * from sysobjects where name='PK_n5gmop_IdObj')
	alter table n5gmop drop constraint PK_n5gmop_IdObj
go
if exists (select * from sysobjects where name='PK_n5projekt_abas_IdObj')
	alter table n5projekt_abas drop constraint PK_n5projekt_abas_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozdok_zalacznik_IdObj')
	alter table n5pozdok_zalacznik drop constraint PK_n5pozdok_zalacznik_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_grupaprod_IdObj')
	alter table n5klient_grupaprod drop constraint PK_n5klient_grupaprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5kraj_IdObj')
	alter table n5kraj drop constraint PK_n5kraj_IdObj
go
if exists (select * from sysobjects where name='PK_n5procedura_IdObj')
	alter table n5procedura drop constraint PK_n5procedura_IdObj
go
if exists (select * from sysobjects where name='PK_n5pit5l_IdObj')
	alter table n5pit5l drop constraint PK_n5pit5l_IdObj
go
if exists (select * from sysobjects where name='PK_n5transakcja_IdObj')
	alter table n5transakcja drop constraint PK_n5transakcja_IdObj
go
if exists (select * from sysobjects where name='PK_n5rokksieg_IdObj')
	alter table n5rokksieg drop constraint PK_n5rokksieg_IdObj
go
if exists (select * from sysobjects where name='PK_n5eventlog_IdObj')
	alter table n5eventlog drop constraint PK_n5eventlog_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrealprod_IdObj')
	alter table n5pozrealprod drop constraint PK_n5pozrealprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5plgrupaschemnal_IdObj')
	alter table n5plgrupaschemnal drop constraint PK_n5plgrupaschemnal_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrecepta_oper_IdObj')
	alter table n5pozrecepta_oper drop constraint PK_n5pozrecepta_oper_IdObj
go
if exists (select * from sysobjects where name='PK_n5inwark_IdObj')
	alter table n5inwark drop constraint PK_n5inwark_IdObj
go
if exists (select * from sysobjects where name='PK_n5wojewodztwo_IdObj')
	alter table n5wojewodztwo drop constraint PK_n5wojewodztwo_IdObj
go
if exists (select * from sysobjects where name='PK_n5dokument_IdObj')
	alter table n5dokument drop constraint PK_n5dokument_IdObj
go
if exists (select * from sysobjects where name='PK_n5pkpir_IdObj')
	alter table n5pkpir drop constraint PK_n5pkpir_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_produkt_IdObj')
	alter table n5klient_produkt drop constraint PK_n5klient_produkt_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozdokmag_egz_IdObj')
	alter table n5pozdokmag_egz drop constraint PK_n5pozdokmag_egz_IdObj
go
if exists (select * from sysobjects where name='PK_n5recepta_IdObj')
	alter table n5recepta drop constraint PK_n5recepta_IdObj
go
if exists (select * from sysobjects where name='PK_n5plnieob_IdObj')
	alter table n5plnieob drop constraint PK_n5plnieob_IdObj
go
if exists (select * from sysobjects where name='PK_n5plpozkalcp_IdObj')
	alter table n5plpozkalcp drop constraint PK_n5plpozkalcp_IdObj
go
if exists (select * from sysobjects where name='PK_n5pltyppracy_IdObj')
	alter table n5pltyppracy drop constraint PK_n5pltyppracy_IdObj
go
if exists (select * from sysobjects where name='PK_n5zasobprod_IdObj')
	alter table n5zasobprod drop constraint PK_n5zasobprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozankieta_toral_IdObj')
	alter table n5pozankieta_toral drop constraint PK_n5pozankieta_toral_IdObj
go
if exists (select * from sysobjects where name='PK_n5globfile_IdObj')
	alter table n5globfile drop constraint PK_n5globfile_IdObj
go
if exists (select * from sysobjects where name='PK_n5_klient_jedn_org_IdObj')
	alter table n5_klient_jedn_org drop constraint PK_n5_klient_jedn_org_IdObj
go
if exists (select * from sysobjects where name='PK_n5produkt_IdObj')
	alter table n5produkt drop constraint PK_n5produkt_IdObj
go
if exists (select * from sysobjects where name='PK_n5dowodksieg_IdObj')
	alter table n5dowodksieg drop constraint PK_n5dowodksieg_IdObj
go
if exists (select * from sysobjects where name='PK_n5kurswalut_IdObj')
	alter table n5kurswalut drop constraint PK_n5kurswalut_IdObj
go
if exists (select * from sysobjects where name='PK_n5plumowa_IdObj')
	alter table n5plumowa drop constraint PK_n5plumowa_IdObj
go
if exists (select * from sysobjects where name='PK_n5opsrtrw_IdObj')
	alter table n5opsrtrw drop constraint PK_n5opsrtrw_IdObj
go
if exists (select * from sysobjects where name='PK_n5rolawyk_IdObj')
	alter table n5rolawyk drop constraint PK_n5rolawyk_IdObj
go
if exists (select * from sysobjects where name='PK_n5ptop_IdObj')
	alter table n5ptop drop constraint PK_n5ptop_IdObj
go
if exists (select * from sysobjects where name='PK_n5poz_koszt_wyjazdu_IdObj')
	alter table n5poz_koszt_wyjazdu drop constraint PK_n5poz_koszt_wyjazdu_IdObj
go
if exists (select * from sysobjects where name='PK_n5miejscowosc_IdObj')
	alter table n5miejscowosc drop constraint PK_n5miejscowosc_IdObj
go
if exists (select * from sysobjects where name='PK_n5SendEmail_IdObj')
	alter table n5SendEmail drop constraint PK_n5SendEmail_IdObj
go
if exists (select * from sysobjects where name='PK_n5rejestrdok_IdObj')
	alter table n5rejestrdok drop constraint PK_n5rejestrdok_IdObj
go
if exists (select * from sysobjects where name='PK_n5dokmag_IdObj')
	alter table n5dokmag drop constraint PK_n5dokmag_IdObj
go
if exists (select * from sysobjects where name='PK_n5srtrw_IdObj')
	alter table n5srtrw drop constraint PK_n5srtrw_IdObj
go
if exists (select * from sysobjects where name='PK_n5plsubkonto_IdObj')
	alter table n5plsubkonto drop constraint PK_n5plsubkonto_IdObj
go
if exists (select * from sysobjects where name='PK_n5bwinfo_zal_IdObj')
	alter table n5bwinfo_zal drop constraint PK_n5bwinfo_zal_IdObj
go
if exists (select * from sysobjects where name='PK_n5rola_IdObj')
	alter table n5rola drop constraint PK_n5rola_IdObj
go
if exists (select * from sysobjects where name='PK_n5stanowisko_IdObj')
	alter table n5stanowisko drop constraint PK_n5stanowisko_IdObj
go
if exists (select * from sysobjects where name='PK_n5securityobj_IdObj')
	alter table n5securityobj drop constraint PK_n5securityobj_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_IdObj')
	alter table n5klient drop constraint PK_n5klient_IdObj
go
if exists (select * from sysobjects where name='PK_n5zadaniezal_IdObj')
	alter table n5zadaniezal drop constraint PK_n5zadaniezal_IdObj
go
if exists (select * from sysobjects where name='PK_n5analfinans_IdObj')
	alter table n5analfinans drop constraint PK_n5analfinans_IdObj
go
if exists (select * from sysobjects where name='PK_n5sposdost_IdObj')
	alter table n5sposdost drop constraint PK_n5sposdost_IdObj
go
if exists (select * from sysobjects where name='PK_n5zakup_IdObj')
	alter table n5zakup drop constraint PK_n5zakup_IdObj
go
if exists (select * from sysobjects where name='PK_n5plsklnal_IdObj')
	alter table n5plsklnal drop constraint PK_n5plsklnal_IdObj
go
if exists (select * from sysobjects where name='PK_n5bwinfo_kat_IdObj')
	alter table n5bwinfo_kat drop constraint PK_n5bwinfo_kat_IdObj
go
if exists (select * from sysobjects where name='PK_n5istat_IdObj')
	alter table n5istat drop constraint PK_n5istat_IdObj
go
if exists (select * from sysobjects where name='PK_n5protokol_abas_IdObj')
	alter table n5protokol_abas drop constraint PK_n5protokol_abas_IdObj
go
if exists (select * from sysobjects where name='PK_n5kolor_IdObj')
	alter table n5kolor drop constraint PK_n5kolor_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrejestrdok_mag_IdObj')
	alter table n5pozrejestrdok_mag drop constraint PK_n5pozrejestrdok_mag_IdObj
go
if exists (select * from sysobjects where name='PK_SearchTypeItem_IdObj')
	alter table SearchTypeItem drop constraint PK_SearchTypeItem_IdObj
go
if exists (select * from sysobjects where name='PK_n5instytucja_IdObj')
	alter table n5instytucja drop constraint PK_n5instytucja_IdObj
go
if exists (select * from sysobjects where name='PK_n5wykonawca_IdObj')
	alter table n5wykonawca drop constraint PK_n5wykonawca_IdObj
go
if exists (select * from sysobjects where name='PK_n5powiat_IdObj')
	alter table n5powiat drop constraint PK_n5powiat_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrata_IdObj')
	alter table n5pozrata drop constraint PK_n5pozrata_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozzamowienie_IdObj')
	alter table n5pozzamowienie drop constraint PK_n5pozzamowienie_IdObj
go
if exists (select * from sysobjects where name='PK_n5plschematnal_IdObj')
	alter table n5plschematnal drop constraint PK_n5plschematnal_IdObj
go
if exists (select * from sysobjects where name='PK_n5kwalifikator_IdObj')
	alter table n5kwalifikator drop constraint PK_n5kwalifikator_IdObj
go
if exists (select * from sysobjects where name='PK_n5plpozschnal_IdObj')
	alter table n5plpozschnal drop constraint PK_n5plpozschnal_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrealprod_zasob_IdObj')
	alter table n5pozrealprod_zasob drop constraint PK_n5pozrealprod_zasob_IdObj
go
if exists (select * from sysobjects where name='PK_n5straznik_cen_IdObj')
	alter table n5straznik_cen drop constraint PK_n5straznik_cen_IdObj
go
if exists (select * from sysobjects where name='PK_n5jednostka_IdObj')
	alter table n5jednostka drop constraint PK_n5jednostka_IdObj
go
if exists (select * from sysobjects where name='PK_n5zadanie_IdObj')
	alter table n5zadanie drop constraint PK_n5zadanie_IdObj
go
if exists (select * from sysobjects where name='PK_n5pit5_IdObj')
	alter table n5pit5 drop constraint PK_n5pit5_IdObj
go
if exists (select * from sysobjects where name='PK_n5typdzialania_IdObj')
	alter table n5typdzialania drop constraint PK_n5typdzialania_IdObj
go
if exists (select * from sysobjects where name='PK_n5zlecprod_IdObj')
	alter table n5zlecprod drop constraint PK_n5zlecprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5rule_IdObj')
	alter table n5rule drop constraint PK_n5rule_IdObj
go
if exists (select * from sysobjects where name='PK_n5plpozostale_IdObj')
	alter table n5plpozostale drop constraint PK_n5plpozostale_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozdokprod_IdObj')
	alter table n5pozdokprod drop constraint PK_n5pozdokprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrecepta_zasob_IdObj')
	alter table n5pozrecepta_zasob drop constraint PK_n5pozrecepta_zasob_IdObj
go
if exists (select * from sysobjects where name='PK_n5inwmag_IdObj')
	alter table n5inwmag drop constraint PK_n5inwmag_IdObj
go
if exists (select * from sysobjects where name='PK_n5grupaproduktow_IdObj')
	alter table n5grupaproduktow drop constraint PK_n5grupaproduktow_IdObj
go
if exists (select * from sysobjects where name='PK_n5dokumentlinks_IdObj')
	alter table n5dokumentlinks drop constraint PK_n5dokumentlinks_IdObj
go
if exists (select * from sysobjects where name='PK_n5platnosc_IdObj')
	alter table n5platnosc drop constraint PK_n5platnosc_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozdoketyk_IdObj')
	alter table n5pozdoketyk drop constraint PK_n5pozdoketyk_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozrecepta_IdObj')
	alter table n5pozrecepta drop constraint PK_n5pozrecepta_IdObj
go
if exists (select * from sysobjects where name='PK_n5plchoroba_IdObj')
	alter table n5plchoroba drop constraint PK_n5plchoroba_IdObj
go
if exists (select * from sysobjects where name='PK_n5plkalcp_IdObj')
	alter table n5plkalcp drop constraint PK_n5plkalcp_IdObj
go
if exists (select * from sysobjects where name='PK_n5plrcp_IdObj')
	alter table n5plrcp drop constraint PK_n5plrcp_IdObj
go
if exists (select * from sysobjects where name='PK_n5transakcja_operacja_IdObj')
	alter table n5transakcja_operacja drop constraint PK_n5transakcja_operacja_IdObj
go
if exists (select * from sysobjects where name='PK_n5ankieta_toral_IdObj')
	alter table n5ankieta_toral drop constraint PK_n5ankieta_toral_IdObj
go
if exists (select * from sysobjects where name='PK_n5userprof_IdObj')
	alter table n5userprof drop constraint PK_n5userprof_IdObj
go
if exists (select * from sysobjects where name='PK_n5jedn_org_IdObj')
	alter table n5jedn_org drop constraint PK_n5jedn_org_IdObj
go
if exists (select * from sysobjects where name='PK_n5opakowanie_produktu_IdObj')
	alter table n5opakowanie_produktu drop constraint PK_n5opakowanie_produktu_IdObj
go
if exists (select * from sysobjects where name='PK_n5dekret_IdObj')
	alter table n5dekret drop constraint PK_n5dekret_IdObj
go
if exists (select * from sysobjects where name='PK_n5sposplat_IdObj')
	alter table n5sposplat drop constraint PK_n5sposplat_IdObj
go
if exists (select * from sysobjects where name='PK_n5pldekret_IdObj')
	alter table n5pldekret drop constraint PK_n5pldekret_IdObj
go
if exists (select * from sysobjects where name='PK_n5notaods_IdObj')
	alter table n5notaods drop constraint PK_n5notaods_IdObj
go
if exists (select * from sysobjects where name='PK_n5zadanie_rola_IdObj')
	alter table n5zadanie_rola drop constraint PK_n5zadanie_rola_IdObj
go
if exists (select * from sysobjects where name='PK_n5polecenie_wyjazdu_IdObj')
	alter table n5polecenie_wyjazdu drop constraint PK_n5polecenie_wyjazdu_IdObj
go
if exists (select * from sysobjects where name='PK_n5dpc_IdObj')
	alter table n5dpc drop constraint PK_n5dpc_IdObj
go
if exists (select * from sysobjects where name='PK_n5firma_IdObj')
	alter table n5firma drop constraint PK_n5firma_IdObj
go
if exists (select * from sysobjects where name='PK_n5WizzardEmail_IdObj')
	alter table n5WizzardEmail drop constraint PK_n5WizzardEmail_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozvatue_IdObj')
	alter table n5pozvatue drop constraint PK_n5pozvatue_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozdokmag_IdObj')
	alter table n5pozdokmag drop constraint PK_n5pozdokmag_IdObj
go
if exists (select * from sysobjects where name='PK_n5grupasrtrw_IdObj')
	alter table n5grupasrtrw drop constraint PK_n5grupasrtrw_IdObj
go
if exists (select * from sysobjects where name='PK_n5plgrzas_IdObj')
	alter table n5plgrzas drop constraint PK_n5plgrzas_IdObj
go
if exists (select * from sysobjects where name='PK_n5bwinfo_produkt_IdObj')
	alter table n5bwinfo_produkt drop constraint PK_n5bwinfo_produkt_IdObj
go
if exists (select * from sysobjects where name='PK_n5rozmiar_IdObj')
	alter table n5rozmiar drop constraint PK_n5rozmiar_IdObj
go
if exists (select * from sysobjects where name='PK_n5pojazd_IdObj')
	alter table n5pojazd drop constraint PK_n5pojazd_IdObj
go
if exists (select * from sysobjects where name='PK_n5sod_IdObj')
	alter table n5sod drop constraint PK_n5sod_IdObj
go
if exists (select * from sysobjects where name='PK_n5uzytkownik_IdObj')
	alter table n5uzytkownik drop constraint PK_n5uzytkownik_IdObj
go
if exists (select * from sysobjects where name='PK_choicelist_IdObj')
	alter table choicelist drop constraint PK_choicelist_IdObj
go
if exists (select * from sysobjects where name='PK_n5typinstytucji_IdObj')
	alter table n5typinstytucji drop constraint PK_n5typinstytucji_IdObj
go
if exists (select * from sysobjects where name='PK_n5rapkas_IdObj')
	alter table n5rapkas drop constraint PK_n5rapkas_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozzakup_IdObj')
	alter table n5pozzakup drop constraint PK_n5pozzakup_IdObj
go
if exists (select * from sysobjects where name='PK_n5plnaliczenie_IdObj')
	alter table n5plnaliczenie drop constraint PK_n5plnaliczenie_IdObj
go
if exists (select * from sysobjects where name='PK_n5konto_budzet_IdObj')
	alter table n5konto_budzet drop constraint PK_n5konto_budzet_IdObj
go
if exists (select * from sysobjects where name='PK_n5gmstan_IdObj')
	alter table n5gmstan drop constraint PK_n5gmstan_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozprojekt_abas_IdObj')
	alter table n5pozprojekt_abas drop constraint PK_n5pozprojekt_abas_IdObj
go
if exists (select * from sysobjects where name='PK_n5paleta_kolorow_IdObj')
	alter table n5paleta_kolorow drop constraint PK_n5paleta_kolorow_IdObj
go
if exists (select * from sysobjects where name='PK_n5dokstatus_IdObj')
	alter table n5dokstatus drop constraint PK_n5dokstatus_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_reprezentacja_IdObj')
	alter table n5klient_reprezentacja drop constraint PK_n5klient_reprezentacja_IdObj
go
if exists (select * from sysobjects where name='PK_SearchType_IdObj')
	alter table SearchType drop constraint PK_SearchType_IdObj
go
if exists (select * from sysobjects where name='PK_n5bank_IdObj')
	alter table n5bank drop constraint PK_n5bank_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozplatnosc_IdObj')
	alter table n5pozplatnosc drop constraint PK_n5pozplatnosc_IdObj
go
if exists (select * from sysobjects where name='PK_n5pit11_IdObj')
	alter table n5pit11 drop constraint PK_n5pit11_IdObj
go
if exists (select * from sysobjects where name='PK_n5schematdekr_IdObj')
	alter table n5schematdekr drop constraint PK_n5schematdekr_IdObj
go
if exists (select * from sysobjects where name='PK_n5zamowienie_IdObj')
	alter table n5zamowienie drop constraint PK_n5zamowienie_IdObj
go
if exists (select * from sysobjects where name='PK_n5polrab_IdObj')
	alter table n5polrab drop constraint PK_n5polrab_IdObj
go
if exists (select * from sysobjects where name='PK_n5realprod_IdObj')
	alter table n5realprod drop constraint PK_n5realprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5plterminnal_IdObj')
	alter table n5plterminnal drop constraint PK_n5plterminnal_IdObj
go
if exists (select * from sysobjects where name='PK_n5prop_IdObj')
	alter table n5prop drop constraint PK_n5prop_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozinwark_IdObj')
	alter table n5pozinwark drop constraint PK_n5pozinwark_IdObj
go
if exists (select * from sysobjects where name='PK_n5region_IdObj')
	alter table n5region drop constraint PK_n5region_IdObj
go
if exists (select * from sysobjects where name='PK_n5grupaklient_IdObj')
	alter table n5grupaklient drop constraint PK_n5grupaklient_IdObj
go
if exists (select * from sysobjects where name='PK_n5pit4_IdObj')
	alter table n5pit4 drop constraint PK_n5pit4_IdObj
go
if exists (select * from sysobjects where name='PK_n5klient_opakowanie_IdObj')
	alter table n5klient_opakowanie drop constraint PK_n5klient_opakowanie_IdObj
go
if exists (select * from sysobjects where name='PK_n5proglojal_IdObj')
	alter table n5proglojal drop constraint PK_n5proglojal_IdObj
go
if exists (select * from sysobjects where name='PK_n5pozzlecprod_IdObj')
	alter table n5pozzlecprod drop constraint PK_n5pozzlecprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5rozlcit_IdObj')
	alter table n5rozlcit drop constraint PK_n5rozlcit_IdObj
go
if exists (select * from sysobjects where name='PK_n5plsklwyn_IdObj')
	alter table n5plsklwyn drop constraint PK_n5plsklwyn_IdObj
go
if exists (select * from sysobjects where name='PK_n5kodpcn_IdObj')
	alter table n5kodpcn drop constraint PK_n5kodpcn_IdObj
go
if exists (select * from sysobjects where name='PK_n5typzasobprod_IdObj')
	alter table n5typzasobprod drop constraint PK_n5typzasobprod_IdObj
go
if exists (select * from sysobjects where name='PK_n5maszyna_toral_IdObj')
	alter table n5maszyna_toral drop constraint PK_n5maszyna_toral_IdObj
go


--========= dropping standard stored procedures =========

-- table: n5userfile
if exists (select * from sysobjects where name='n5userfile_select')
	drop procedure n5userfile_select
go
if exists (select * from sysobjects where name='n5userfile_insert')
	drop procedure n5userfile_insert
go
if exists (select * from sysobjects where name='n5userfile_update')
	drop procedure n5userfile_update
go
if exists (select * from sysobjects where name='n5userfile_delete')
	drop procedure n5userfile_delete
go
if exists (select * from sysobjects where name='n5userfile_maxid')
	drop procedure n5userfile_maxid
go
if exists (select * from sysobjects where name='n5userfile_candel')
	drop procedure n5userfile_candel
go
-- table: n5typdokumentu
if exists (select * from sysobjects where name='n5typdokumentu_select')
	drop procedure n5typdokumentu_select
go
if exists (select * from sysobjects where name='n5typdokumentu_insert')
	drop procedure n5typdokumentu_insert
go
if exists (select * from sysobjects where name='n5typdokumentu_update')
	drop procedure n5typdokumentu_update
go
if exists (select * from sysobjects where name='n5typdokumentu_delete')
	drop procedure n5typdokumentu_delete
go
if exists (select * from sysobjects where name='n5typdokumentu_maxid')
	drop procedure n5typdokumentu_maxid
go
if exists (select * from sysobjects where name='n5typdokumentu_candel')
	drop procedure n5typdokumentu_candel
go
-- table: n5pozsprzedaz
if exists (select * from sysobjects where name='n5pozsprzedaz_select')
	drop procedure n5pozsprzedaz_select
go
if exists (select * from sysobjects where name='n5pozsprzedaz_insert')
	drop procedure n5pozsprzedaz_insert
go
if exists (select * from sysobjects where name='n5pozsprzedaz_update')
	drop procedure n5pozsprzedaz_update
go
if exists (select * from sysobjects where name='n5pozsprzedaz_delete')
	drop procedure n5pozsprzedaz_delete
go
if exists (select * from sysobjects where name='n5pozsprzedaz_maxid')
	drop procedure n5pozsprzedaz_maxid
go
if exists (select * from sysobjects where name='n5pozsprzedaz_candel')
	drop procedure n5pozsprzedaz_candel
go
-- table: n5egzemplarz
if exists (select * from sysobjects where name='n5egzemplarz_select')
	drop procedure n5egzemplarz_select
go
if exists (select * from sysobjects where name='n5egzemplarz_insert')
	drop procedure n5egzemplarz_insert
go
if exists (select * from sysobjects where name='n5egzemplarz_update')
	drop procedure n5egzemplarz_update
go
if exists (select * from sysobjects where name='n5egzemplarz_delete')
	drop procedure n5egzemplarz_delete
go
if exists (select * from sysobjects where name='n5egzemplarz_maxid')
	drop procedure n5egzemplarz_maxid
go
if exists (select * from sysobjects where name='n5egzemplarz_candel')
	drop procedure n5egzemplarz_candel
go
-- table: n5doketyk
if exists (select * from sysobjects where name='n5doketyk_select')
	drop procedure n5doketyk_select
go
if exists (select * from sysobjects where name='n5doketyk_insert')
	drop procedure n5doketyk_insert
go
if exists (select * from sysobjects where name='n5doketyk_update')
	drop procedure n5doketyk_update
go
if exists (select * from sysobjects where name='n5doketyk_delete')
	drop procedure n5doketyk_delete
go
if exists (select * from sysobjects where name='n5doketyk_maxid')
	drop procedure n5doketyk_maxid
go
if exists (select * from sysobjects where name='n5doketyk_candel')
	drop procedure n5doketyk_candel
go
-- table: n5klient_obiekt
if exists (select * from sysobjects where name='n5klient_obiekt_select')
	drop procedure n5klient_obiekt_select
go
if exists (select * from sysobjects where name='n5klient_obiekt_insert')
	drop procedure n5klient_obiekt_insert
go
if exists (select * from sysobjects where name='n5klient_obiekt_update')
	drop procedure n5klient_obiekt_update
go
if exists (select * from sysobjects where name='n5klient_obiekt_delete')
	drop procedure n5klient_obiekt_delete
go
if exists (select * from sysobjects where name='n5klient_obiekt_maxid')
	drop procedure n5klient_obiekt_maxid
go
if exists (select * from sysobjects where name='n5klient_obiekt_candel')
	drop procedure n5klient_obiekt_candel
go
-- table: n5ptstan
if exists (select * from sysobjects where name='n5ptstan_select')
	drop procedure n5ptstan_select
go
if exists (select * from sysobjects where name='n5ptstan_insert')
	drop procedure n5ptstan_insert
go
if exists (select * from sysobjects where name='n5ptstan_update')
	drop procedure n5ptstan_update
go
if exists (select * from sysobjects where name='n5ptstan_delete')
	drop procedure n5ptstan_delete
go
if exists (select * from sysobjects where name='n5ptstan_maxid')
	drop procedure n5ptstan_maxid
go
if exists (select * from sysobjects where name='n5ptstan_candel')
	drop procedure n5ptstan_candel
go
-- table: n5srodek_lok
if exists (select * from sysobjects where name='n5srodek_lok_select')
	drop procedure n5srodek_lok_select
go
if exists (select * from sysobjects where name='n5srodek_lok_insert')
	drop procedure n5srodek_lok_insert
go
if exists (select * from sysobjects where name='n5srodek_lok_update')
	drop procedure n5srodek_lok_update
go
if exists (select * from sysobjects where name='n5srodek_lok_delete')
	drop procedure n5srodek_lok_delete
go
if exists (select * from sysobjects where name='n5srodek_lok_maxid')
	drop procedure n5srodek_lok_maxid
go
if exists (select * from sysobjects where name='n5srodek_lok_candel')
	drop procedure n5srodek_lok_candel
go
-- table: n5globprof
if exists (select * from sysobjects where name='n5globprof_select')
	drop procedure n5globprof_select
go
if exists (select * from sysobjects where name='n5globprof_insert')
	drop procedure n5globprof_insert
go
if exists (select * from sysobjects where name='n5globprof_update')
	drop procedure n5globprof_update
go
if exists (select * from sysobjects where name='n5globprof_delete')
	drop procedure n5globprof_delete
go
if exists (select * from sysobjects where name='n5globprof_maxid')
	drop procedure n5globprof_maxid
go
if exists (select * from sysobjects where name='n5globprof_candel')
	drop procedure n5globprof_candel
go
-- table: n5klient_pracownik
if exists (select * from sysobjects where name='n5klient_pracownik_select')
	drop procedure n5klient_pracownik_select
go
if exists (select * from sysobjects where name='n5klient_pracownik_insert')
	drop procedure n5klient_pracownik_insert
go
if exists (select * from sysobjects where name='n5klient_pracownik_update')
	drop procedure n5klient_pracownik_update
go
if exists (select * from sysobjects where name='n5klient_pracownik_delete')
	drop procedure n5klient_pracownik_delete
go
if exists (select * from sysobjects where name='n5klient_pracownik_maxid')
	drop procedure n5klient_pracownik_maxid
go
if exists (select * from sysobjects where name='n5klient_pracownik_candel')
	drop procedure n5klient_pracownik_candel
go
-- table: n5sprzedaz
if exists (select * from sysobjects where name='n5sprzedaz_select')
	drop procedure n5sprzedaz_select
go
if exists (select * from sysobjects where name='n5sprzedaz_insert')
	drop procedure n5sprzedaz_insert
go
if exists (select * from sysobjects where name='n5sprzedaz_update')
	drop procedure n5sprzedaz_update
go
if exists (select * from sysobjects where name='n5sprzedaz_delete')
	drop procedure n5sprzedaz_delete
go
if exists (select * from sysobjects where name='n5sprzedaz_maxid')
	drop procedure n5sprzedaz_maxid
go
if exists (select * from sysobjects where name='n5sprzedaz_candel')
	drop procedure n5sprzedaz_candel
go
-- table: n5konto
if exists (select * from sysobjects where name='n5konto_select')
	drop procedure n5konto_select
go
if exists (select * from sysobjects where name='n5konto_insert')
	drop procedure n5konto_insert
go
if exists (select * from sysobjects where name='n5konto_update')
	drop procedure n5konto_update
go
if exists (select * from sysobjects where name='n5konto_delete')
	drop procedure n5konto_delete
go
if exists (select * from sysobjects where name='n5konto_maxid')
	drop procedure n5konto_maxid
go
if exists (select * from sysobjects where name='n5konto_candel')
	drop procedure n5konto_candel
go
-- table: n5zadaniedw
if exists (select * from sysobjects where name='n5zadaniedw_select')
	drop procedure n5zadaniedw_select
go
if exists (select * from sysobjects where name='n5zadaniedw_insert')
	drop procedure n5zadaniedw_insert
go
if exists (select * from sysobjects where name='n5zadaniedw_update')
	drop procedure n5zadaniedw_update
go
if exists (select * from sysobjects where name='n5zadaniedw_delete')
	drop procedure n5zadaniedw_delete
go
if exists (select * from sysobjects where name='n5zadaniedw_maxid')
	drop procedure n5zadaniedw_maxid
go
if exists (select * from sysobjects where name='n5zadaniedw_candel')
	drop procedure n5zadaniedw_candel
go
-- table: n5poznotaods
if exists (select * from sysobjects where name='n5poznotaods_select')
	drop procedure n5poznotaods_select
go
if exists (select * from sysobjects where name='n5poznotaods_insert')
	drop procedure n5poznotaods_insert
go
if exists (select * from sysobjects where name='n5poznotaods_update')
	drop procedure n5poznotaods_update
go
if exists (select * from sysobjects where name='n5poznotaods_delete')
	drop procedure n5poznotaods_delete
go
if exists (select * from sysobjects where name='n5poznotaods_maxid')
	drop procedure n5poznotaods_maxid
go
if exists (select * from sysobjects where name='n5poznotaods_candel')
	drop procedure n5poznotaods_candel
go
-- table: n5rola_prior
if exists (select * from sysobjects where name='n5rola_prior_select')
	drop procedure n5rola_prior_select
go
if exists (select * from sysobjects where name='n5rola_prior_insert')
	drop procedure n5rola_prior_insert
go
if exists (select * from sysobjects where name='n5rola_prior_update')
	drop procedure n5rola_prior_update
go
if exists (select * from sysobjects where name='n5rola_prior_delete')
	drop procedure n5rola_prior_delete
go
if exists (select * from sysobjects where name='n5rola_prior_maxid')
	drop procedure n5rola_prior_maxid
go
if exists (select * from sysobjects where name='n5rola_prior_candel')
	drop procedure n5rola_prior_candel
go
-- table: n5poz_hist_stan
if exists (select * from sysobjects where name='n5poz_hist_stan_select')
	drop procedure n5poz_hist_stan_select
go
if exists (select * from sysobjects where name='n5poz_hist_stan_insert')
	drop procedure n5poz_hist_stan_insert
go
if exists (select * from sysobjects where name='n5poz_hist_stan_update')
	drop procedure n5poz_hist_stan_update
go
if exists (select * from sysobjects where name='n5poz_hist_stan_delete')
	drop procedure n5poz_hist_stan_delete
go
if exists (select * from sysobjects where name='n5poz_hist_stan_maxid')
	drop procedure n5poz_hist_stan_maxid
go
if exists (select * from sysobjects where name='n5poz_hist_stan_candel')
	drop procedure n5poz_hist_stan_candel
go
-- table: n5miesiac
if exists (select * from sysobjects where name='n5miesiac_select')
	drop procedure n5miesiac_select
go
if exists (select * from sysobjects where name='n5miesiac_insert')
	drop procedure n5miesiac_insert
go
if exists (select * from sysobjects where name='n5miesiac_update')
	drop procedure n5miesiac_update
go
if exists (select * from sysobjects where name='n5miesiac_delete')
	drop procedure n5miesiac_delete
go
if exists (select * from sysobjects where name='n5miesiac_maxid')
	drop procedure n5miesiac_maxid
go
if exists (select * from sysobjects where name='n5miesiac_candel')
	drop procedure n5miesiac_candel
go
-- table: n5pracownik
if exists (select * from sysobjects where name='n5pracownik_select')
	drop procedure n5pracownik_select
go
if exists (select * from sysobjects where name='n5pracownik_insert')
	drop procedure n5pracownik_insert
go
if exists (select * from sysobjects where name='n5pracownik_update')
	drop procedure n5pracownik_update
go
if exists (select * from sysobjects where name='n5pracownik_delete')
	drop procedure n5pracownik_delete
go
if exists (select * from sysobjects where name='n5pracownik_maxid')
	drop procedure n5pracownik_maxid
go
if exists (select * from sysobjects where name='n5pracownik_candel')
	drop procedure n5pracownik_candel
go
-- table: n5WizzardEmailDokumElem
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_select')
	drop procedure n5WizzardEmailDokumElem_select
go
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_insert')
	drop procedure n5WizzardEmailDokumElem_insert
go
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_update')
	drop procedure n5WizzardEmailDokumElem_update
go
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_delete')
	drop procedure n5WizzardEmailDokumElem_delete
go
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_maxid')
	drop procedure n5WizzardEmailDokumElem_maxid
go
if exists (select * from sysobjects where name='n5WizzardEmailDokumElem_candel')
	drop procedure n5WizzardEmailDokumElem_candel
go
-- table: n5vatue
if exists (select * from sysobjects where name='n5vatue_select')
	drop procedure n5vatue_select
go
if exists (select * from sysobjects where name='n5vatue_insert')
	drop procedure n5vatue_insert
go
if exists (select * from sysobjects where name='n5vatue_update')
	drop procedure n5vatue_update
go
if exists (select * from sysobjects where name='n5vatue_delete')
	drop procedure n5vatue_delete
go
if exists (select * from sysobjects where name='n5vatue_maxid')
	drop procedure n5vatue_maxid
go
if exists (select * from sysobjects where name='n5vatue_candel')
	drop procedure n5vatue_candel
go
-- table: n5magazyn
if exists (select * from sysobjects where name='n5magazyn_select')
	drop procedure n5magazyn_select
go
if exists (select * from sysobjects where name='n5magazyn_insert')
	drop procedure n5magazyn_insert
go
if exists (select * from sysobjects where name='n5magazyn_update')
	drop procedure n5magazyn_update
go
if exists (select * from sysobjects where name='n5magazyn_delete')
	drop procedure n5magazyn_delete
go
if exists (select * from sysobjects where name='n5magazyn_maxid')
	drop procedure n5magazyn_maxid
go
if exists (select * from sysobjects where name='n5magazyn_candel')
	drop procedure n5magazyn_candel
go
-- table: n5rozlvat
if exists (select * from sysobjects where name='n5rozlvat_select')
	drop procedure n5rozlvat_select
go
if exists (select * from sysobjects where name='n5rozlvat_insert')
	drop procedure n5rozlvat_insert
go
if exists (select * from sysobjects where name='n5rozlvat_update')
	drop procedure n5rozlvat_update
go
if exists (select * from sysobjects where name='n5rozlvat_delete')
	drop procedure n5rozlvat_delete
go
if exists (select * from sysobjects where name='n5rozlvat_maxid')
	drop procedure n5rozlvat_maxid
go
if exists (select * from sysobjects where name='n5rozlvat_candel')
	drop procedure n5rozlvat_candel
go
-- table: n5pllistaplac
if exists (select * from sysobjects where name='n5pllistaplac_select')
	drop procedure n5pllistaplac_select
go
if exists (select * from sysobjects where name='n5pllistaplac_insert')
	drop procedure n5pllistaplac_insert
go
if exists (select * from sysobjects where name='n5pllistaplac_update')
	drop procedure n5pllistaplac_update
go
if exists (select * from sysobjects where name='n5pllistaplac_delete')
	drop procedure n5pllistaplac_delete
go
if exists (select * from sysobjects where name='n5pllistaplac_maxid')
	drop procedure n5pllistaplac_maxid
go
if exists (select * from sysobjects where name='n5pllistaplac_candel')
	drop procedure n5pllistaplac_candel
go
-- table: n5bwinfo
if exists (select * from sysobjects where name='n5bwinfo_select')
	drop procedure n5bwinfo_select
go
if exists (select * from sysobjects where name='n5bwinfo_insert')
	drop procedure n5bwinfo_insert
go
if exists (select * from sysobjects where name='n5bwinfo_update')
	drop procedure n5bwinfo_update
go
if exists (select * from sysobjects where name='n5bwinfo_delete')
	drop procedure n5bwinfo_delete
go
if exists (select * from sysobjects where name='n5bwinfo_maxid')
	drop procedure n5bwinfo_maxid
go
if exists (select * from sysobjects where name='n5bwinfo_candel')
	drop procedure n5bwinfo_candel
go
-- table: n5pozistat
if exists (select * from sysobjects where name='n5pozistat_select')
	drop procedure n5pozistat_select
go
if exists (select * from sysobjects where name='n5pozistat_insert')
	drop procedure n5pozistat_insert
go
if exists (select * from sysobjects where name='n5pozistat_update')
	drop procedure n5pozistat_update
go
if exists (select * from sysobjects where name='n5pozistat_delete')
	drop procedure n5pozistat_delete
go
if exists (select * from sysobjects where name='n5pozistat_maxid')
	drop procedure n5pozistat_maxid
go
if exists (select * from sysobjects where name='n5pozistat_candel')
	drop procedure n5pozistat_candel
go
-- table: n5tabela_rozmiarow
if exists (select * from sysobjects where name='n5tabela_rozmiarow_select')
	drop procedure n5tabela_rozmiarow_select
go
if exists (select * from sysobjects where name='n5tabela_rozmiarow_insert')
	drop procedure n5tabela_rozmiarow_insert
go
if exists (select * from sysobjects where name='n5tabela_rozmiarow_update')
	drop procedure n5tabela_rozmiarow_update
go
if exists (select * from sysobjects where name='n5tabela_rozmiarow_delete')
	drop procedure n5tabela_rozmiarow_delete
go
if exists (select * from sysobjects where name='n5tabela_rozmiarow_maxid')
	drop procedure n5tabela_rozmiarow_maxid
go
if exists (select * from sysobjects where name='n5tabela_rozmiarow_candel')
	drop procedure n5tabela_rozmiarow_candel
go
-- table: n5produkt_magazyn
if exists (select * from sysobjects where name='n5produkt_magazyn_select')
	drop procedure n5produkt_magazyn_select
go
if exists (select * from sysobjects where name='n5produkt_magazyn_insert')
	drop procedure n5produkt_magazyn_insert
go
if exists (select * from sysobjects where name='n5produkt_magazyn_update')
	drop procedure n5produkt_magazyn_update
go
if exists (select * from sysobjects where name='n5produkt_magazyn_delete')
	drop procedure n5produkt_magazyn_delete
go
if exists (select * from sysobjects where name='n5produkt_magazyn_maxid')
	drop procedure n5produkt_magazyn_maxid
go
if exists (select * from sysobjects where name='n5produkt_magazyn_candel')
	drop procedure n5produkt_magazyn_candel
go
-- table: n5sodgroup
if exists (select * from sysobjects where name='n5sodgroup_select')
	drop procedure n5sodgroup_select
go
if exists (select * from sysobjects where name='n5sodgroup_insert')
	drop procedure n5sodgroup_insert
go
if exists (select * from sysobjects where name='n5sodgroup_update')
	drop procedure n5sodgroup_update
go
if exists (select * from sysobjects where name='n5sodgroup_delete')
	drop procedure n5sodgroup_delete
go
if exists (select * from sysobjects where name='n5sodgroup_maxid')
	drop procedure n5sodgroup_maxid
go
if exists (select * from sysobjects where name='n5sodgroup_candel')
	drop procedure n5sodgroup_candel
go
-- table: n5licencja
if exists (select * from sysobjects where name='n5licencja_select')
	drop procedure n5licencja_select
go
if exists (select * from sysobjects where name='n5licencja_insert')
	drop procedure n5licencja_insert
go
if exists (select * from sysobjects where name='n5licencja_update')
	drop procedure n5licencja_update
go
if exists (select * from sysobjects where name='n5licencja_delete')
	drop procedure n5licencja_delete
go
if exists (select * from sysobjects where name='n5licencja_maxid')
	drop procedure n5licencja_maxid
go
if exists (select * from sysobjects where name='n5licencja_candel')
	drop procedure n5licencja_candel
go
-- table: choicelistitem
if exists (select * from sysobjects where name='choicelistitem_select')
	drop procedure choicelistitem_select
go
if exists (select * from sysobjects where name='choicelistitem_insert')
	drop procedure choicelistitem_insert
go
if exists (select * from sysobjects where name='choicelistitem_update')
	drop procedure choicelistitem_update
go
if exists (select * from sysobjects where name='choicelistitem_delete')
	drop procedure choicelistitem_delete
go
if exists (select * from sysobjects where name='choicelistitem_maxid')
	drop procedure choicelistitem_maxid
go
if exists (select * from sysobjects where name='choicelistitem_candel')
	drop procedure choicelistitem_candel
go
-- table: n5gmina
if exists (select * from sysobjects where name='n5gmina_select')
	drop procedure n5gmina_select
go
if exists (select * from sysobjects where name='n5gmina_insert')
	drop procedure n5gmina_insert
go
if exists (select * from sysobjects where name='n5gmina_update')
	drop procedure n5gmina_update
go
if exists (select * from sysobjects where name='n5gmina_delete')
	drop procedure n5gmina_delete
go
if exists (select * from sysobjects where name='n5gmina_maxid')
	drop procedure n5gmina_maxid
go
if exists (select * from sysobjects where name='n5gmina_candel')
	drop procedure n5gmina_candel
go
-- table: n5branza
if exists (select * from sysobjects where name='n5branza_select')
	drop procedure n5branza_select
go
if exists (select * from sysobjects where name='n5branza_insert')
	drop procedure n5branza_insert
go
if exists (select * from sysobjects where name='n5branza_update')
	drop procedure n5branza_update
go
if exists (select * from sysobjects where name='n5branza_delete')
	drop procedure n5branza_delete
go
if exists (select * from sysobjects where name='n5branza_maxid')
	drop procedure n5branza_maxid
go
if exists (select * from sysobjects where name='n5branza_candel')
	drop procedure n5branza_candel
go
-- table: n5plstawka
if exists (select * from sysobjects where name='n5plstawka_select')
	drop procedure n5plstawka_select
go
if exists (select * from sysobjects where name='n5plstawka_insert')
	drop procedure n5plstawka_insert
go
if exists (select * from sysobjects where name='n5plstawka_update')
	drop procedure n5plstawka_update
go
if exists (select * from sysobjects where name='n5plstawka_delete')
	drop procedure n5plstawka_delete
go
if exists (select * from sysobjects where name='n5plstawka_maxid')
	drop procedure n5plstawka_maxid
go
if exists (select * from sysobjects where name='n5plstawka_candel')
	drop procedure n5plstawka_candel
go
-- table: n5budzet
if exists (select * from sysobjects where name='n5budzet_select')
	drop procedure n5budzet_select
go
if exists (select * from sysobjects where name='n5budzet_insert')
	drop procedure n5budzet_insert
go
if exists (select * from sysobjects where name='n5budzet_update')
	drop procedure n5budzet_update
go
if exists (select * from sysobjects where name='n5budzet_delete')
	drop procedure n5budzet_delete
go
if exists (select * from sysobjects where name='n5budzet_maxid')
	drop procedure n5budzet_maxid
go
if exists (select * from sysobjects where name='n5budzet_candel')
	drop procedure n5budzet_candel
go
-- table: n5gmop
if exists (select * from sysobjects where name='n5gmop_select')
	drop procedure n5gmop_select
go
if exists (select * from sysobjects where name='n5gmop_insert')
	drop procedure n5gmop_insert
go
if exists (select * from sysobjects where name='n5gmop_update')
	drop procedure n5gmop_update
go
if exists (select * from sysobjects where name='n5gmop_delete')
	drop procedure n5gmop_delete
go
if exists (select * from sysobjects where name='n5gmop_maxid')
	drop procedure n5gmop_maxid
go
if exists (select * from sysobjects where name='n5gmop_candel')
	drop procedure n5gmop_candel
go
-- table: n5projekt_abas
if exists (select * from sysobjects where name='n5projekt_abas_select')
	drop procedure n5projekt_abas_select
go
if exists (select * from sysobjects where name='n5projekt_abas_insert')
	drop procedure n5projekt_abas_insert
go
if exists (select * from sysobjects where name='n5projekt_abas_update')
	drop procedure n5projekt_abas_update
go
if exists (select * from sysobjects where name='n5projekt_abas_delete')
	drop procedure n5projekt_abas_delete
go
if exists (select * from sysobjects where name='n5projekt_abas_maxid')
	drop procedure n5projekt_abas_maxid
go
if exists (select * from sysobjects where name='n5projekt_abas_candel')
	drop procedure n5projekt_abas_candel
go
-- table: n5pozdok_zalacznik
if exists (select * from sysobjects where name='n5pozdok_zalacznik_select')
	drop procedure n5pozdok_zalacznik_select
go
if exists (select * from sysobjects where name='n5pozdok_zalacznik_insert')
	drop procedure n5pozdok_zalacznik_insert
go
if exists (select * from sysobjects where name='n5pozdok_zalacznik_update')
	drop procedure n5pozdok_zalacznik_update
go
if exists (select * from sysobjects where name='n5pozdok_zalacznik_delete')
	drop procedure n5pozdok_zalacznik_delete
go
if exists (select * from sysobjects where name='n5pozdok_zalacznik_maxid')
	drop procedure n5pozdok_zalacznik_maxid
go
if exists (select * from sysobjects where name='n5pozdok_zalacznik_candel')
	drop procedure n5pozdok_zalacznik_candel
go
-- table: n5klient_grupaprod
if exists (select * from sysobjects where name='n5klient_grupaprod_select')
	drop procedure n5klient_grupaprod_select
go
if exists (select * from sysobjects where name='n5klient_grupaprod_insert')
	drop procedure n5klient_grupaprod_insert
go
if exists (select * from sysobjects where name='n5klient_grupaprod_update')
	drop procedure n5klient_grupaprod_update
go
if exists (select * from sysobjects where name='n5klient_grupaprod_delete')
	drop procedure n5klient_grupaprod_delete
go
if exists (select * from sysobjects where name='n5klient_grupaprod_maxid')
	drop procedure n5klient_grupaprod_maxid
go
if exists (select * from sysobjects where name='n5klient_grupaprod_candel')
	drop procedure n5klient_grupaprod_candel
go
-- table: n5kraj
if exists (select * from sysobjects where name='n5kraj_select')
	drop procedure n5kraj_select
go
if exists (select * from sysobjects where name='n5kraj_insert')
	drop procedure n5kraj_insert
go
if exists (select * from sysobjects where name='n5kraj_update')
	drop procedure n5kraj_update
go
if exists (select * from sysobjects where name='n5kraj_delete')
	drop procedure n5kraj_delete
go
if exists (select * from sysobjects where name='n5kraj_maxid')
	drop procedure n5kraj_maxid
go
if exists (select * from sysobjects where name='n5kraj_candel')
	drop procedure n5kraj_candel
go
-- table: n5procedura
if exists (select * from sysobjects where name='n5procedura_select')
	drop procedure n5procedura_select
go
if exists (select * from sysobjects where name='n5procedura_insert')
	drop procedure n5procedura_insert
go
if exists (select * from sysobjects where name='n5procedura_update')
	drop procedure n5procedura_update
go
if exists (select * from sysobjects where name='n5procedura_delete')
	drop procedure n5procedura_delete
go
if exists (select * from sysobjects where name='n5procedura_maxid')
	drop procedure n5procedura_maxid
go
if exists (select * from sysobjects where name='n5procedura_candel')
	drop procedure n5procedura_candel
go
-- table: n5pit5l
if exists (select * from sysobjects where name='n5pit5l_select')
	drop procedure n5pit5l_select
go
if exists (select * from sysobjects where name='n5pit5l_insert')
	drop procedure n5pit5l_insert
go
if exists (select * from sysobjects where name='n5pit5l_update')
	drop procedure n5pit5l_update
go
if exists (select * from sysobjects where name='n5pit5l_delete')
	drop procedure n5pit5l_delete
go
if exists (select * from sysobjects where name='n5pit5l_maxid')
	drop procedure n5pit5l_maxid
go
if exists (select * from sysobjects where name='n5pit5l_candel')
	drop procedure n5pit5l_candel
go
-- table: n5transakcja
if exists (select * from sysobjects where name='n5transakcja_select')
	drop procedure n5transakcja_select
go
if exists (select * from sysobjects where name='n5transakcja_insert')
	drop procedure n5transakcja_insert
go
if exists (select * from sysobjects where name='n5transakcja_update')
	drop procedure n5transakcja_update
go
if exists (select * from sysobjects where name='n5transakcja_delete')
	drop procedure n5transakcja_delete
go
if exists (select * from sysobjects where name='n5transakcja_maxid')
	drop procedure n5transakcja_maxid
go
if exists (select * from sysobjects where name='n5transakcja_candel')
	drop procedure n5transakcja_candel
go
-- table: n5rokksieg
if exists (select * from sysobjects where name='n5rokksieg_select')
	drop procedure n5rokksieg_select
go
if exists (select * from sysobjects where name='n5rokksieg_insert')
	drop procedure n5rokksieg_insert
go
if exists (select * from sysobjects where name='n5rokksieg_update')
	drop procedure n5rokksieg_update
go
if exists (select * from sysobjects where name='n5rokksieg_delete')
	drop procedure n5rokksieg_delete
go
if exists (select * from sysobjects where name='n5rokksieg_maxid')
	drop procedure n5rokksieg_maxid
go
if exists (select * from sysobjects where name='n5rokksieg_candel')
	drop procedure n5rokksieg_candel
go
-- table: n5eventlog
if exists (select * from sysobjects where name='n5eventlog_select')
	drop procedure n5eventlog_select
go
if exists (select * from sysobjects where name='n5eventlog_insert')
	drop procedure n5eventlog_insert
go
if exists (select * from sysobjects where name='n5eventlog_update')
	drop procedure n5eventlog_update
go
if exists (select * from sysobjects where name='n5eventlog_delete')
	drop procedure n5eventlog_delete
go
if exists (select * from sysobjects where name='n5eventlog_maxid')
	drop procedure n5eventlog_maxid
go
if exists (select * from sysobjects where name='n5eventlog_candel')
	drop procedure n5eventlog_candel
go
-- table: n5pozrealprod
if exists (select * from sysobjects where name='n5pozrealprod_select')
	drop procedure n5pozrealprod_select
go
if exists (select * from sysobjects where name='n5pozrealprod_insert')
	drop procedure n5pozrealprod_insert
go
if exists (select * from sysobjects where name='n5pozrealprod_update')
	drop procedure n5pozrealprod_update
go
if exists (select * from sysobjects where name='n5pozrealprod_delete')
	drop procedure n5pozrealprod_delete
go
if exists (select * from sysobjects where name='n5pozrealprod_maxid')
	drop procedure n5pozrealprod_maxid
go
if exists (select * from sysobjects where name='n5pozrealprod_candel')
	drop procedure n5pozrealprod_candel
go
-- table: n5plgrupaschemnal
if exists (select * from sysobjects where name='n5plgrupaschemnal_select')
	drop procedure n5plgrupaschemnal_select
go
if exists (select * from sysobjects where name='n5plgrupaschemnal_insert')
	drop procedure n5plgrupaschemnal_insert
go
if exists (select * from sysobjects where name='n5plgrupaschemnal_update')
	drop procedure n5plgrupaschemnal_update
go
if exists (select * from sysobjects where name='n5plgrupaschemnal_delete')
	drop procedure n5plgrupaschemnal_delete
go
if exists (select * from sysobjects where name='n5plgrupaschemnal_maxid')
	drop procedure n5plgrupaschemnal_maxid
go
if exists (select * from sysobjects where name='n5plgrupaschemnal_candel')
	drop procedure n5plgrupaschemnal_candel
go
-- table: n5pozrecepta_oper
if exists (select * from sysobjects where name='n5pozrecepta_oper_select')
	drop procedure n5pozrecepta_oper_select
go
if exists (select * from sysobjects where name='n5pozrecepta_oper_insert')
	drop procedure n5pozrecepta_oper_insert
go
if exists (select * from sysobjects where name='n5pozrecepta_oper_update')
	drop procedure n5pozrecepta_oper_update
go
if exists (select * from sysobjects where name='n5pozrecepta_oper_delete')
	drop procedure n5pozrecepta_oper_delete
go
if exists (select * from sysobjects where name='n5pozrecepta_oper_maxid')
	drop procedure n5pozrecepta_oper_maxid
go
if exists (select * from sysobjects where name='n5pozrecepta_oper_candel')
	drop procedure n5pozrecepta_oper_candel
go
-- table: n5inwark
if exists (select * from sysobjects where name='n5inwark_select')
	drop procedure n5inwark_select
go
if exists (select * from sysobjects where name='n5inwark_insert')
	drop procedure n5inwark_insert
go
if exists (select * from sysobjects where name='n5inwark_update')
	drop procedure n5inwark_update
go
if exists (select * from sysobjects where name='n5inwark_delete')
	drop procedure n5inwark_delete
go
if exists (select * from sysobjects where name='n5inwark_maxid')
	drop procedure n5inwark_maxid
go
if exists (select * from sysobjects where name='n5inwark_candel')
	drop procedure n5inwark_candel
go
-- table: n5wojewodztwo
if exists (select * from sysobjects where name='n5wojewodztwo_select')
	drop procedure n5wojewodztwo_select
go
if exists (select * from sysobjects where name='n5wojewodztwo_insert')
	drop procedure n5wojewodztwo_insert
go
if exists (select * from sysobjects where name='n5wojewodztwo_update')
	drop procedure n5wojewodztwo_update
go
if exists (select * from sysobjects where name='n5wojewodztwo_delete')
	drop procedure n5wojewodztwo_delete
go
if exists (select * from sysobjects where name='n5wojewodztwo_maxid')
	drop procedure n5wojewodztwo_maxid
go
if exists (select * from sysobjects where name='n5wojewodztwo_candel')
	drop procedure n5wojewodztwo_candel
go
-- table: n5dokument
if exists (select * from sysobjects where name='n5dokument_select')
	drop procedure n5dokument_select
go
if exists (select * from sysobjects where name='n5dokument_insert')
	drop procedure n5dokument_insert
go
if exists (select * from sysobjects where name='n5dokument_update')
	drop procedure n5dokument_update
go
if exists (select * from sysobjects where name='n5dokument_delete')
	drop procedure n5dokument_delete
go
if exists (select * from sysobjects where name='n5dokument_maxid')
	drop procedure n5dokument_maxid
go
if exists (select * from sysobjects where name='n5dokument_candel')
	drop procedure n5dokument_candel
go
-- table: n5pkpir
if exists (select * from sysobjects where name='n5pkpir_select')
	drop procedure n5pkpir_select
go
if exists (select * from sysobjects where name='n5pkpir_insert')
	drop procedure n5pkpir_insert
go
if exists (select * from sysobjects where name='n5pkpir_update')
	drop procedure n5pkpir_update
go
if exists (select * from sysobjects where name='n5pkpir_delete')
	drop procedure n5pkpir_delete
go
if exists (select * from sysobjects where name='n5pkpir_maxid')
	drop procedure n5pkpir_maxid
go
if exists (select * from sysobjects where name='n5pkpir_candel')
	drop procedure n5pkpir_candel
go
-- table: n5klient_produkt
if exists (select * from sysobjects where name='n5klient_produkt_select')
	drop procedure n5klient_produkt_select
go
if exists (select * from sysobjects where name='n5klient_produkt_insert')
	drop procedure n5klient_produkt_insert
go
if exists (select * from sysobjects where name='n5klient_produkt_update')
	drop procedure n5klient_produkt_update
go
if exists (select * from sysobjects where name='n5klient_produkt_delete')
	drop procedure n5klient_produkt_delete
go
if exists (select * from sysobjects where name='n5klient_produkt_maxid')
	drop procedure n5klient_produkt_maxid
go
if exists (select * from sysobjects where name='n5klient_produkt_candel')
	drop procedure n5klient_produkt_candel
go
-- table: n5pozdokmag_egz
if exists (select * from sysobjects where name='n5pozdokmag_egz_select')
	drop procedure n5pozdokmag_egz_select
go
if exists (select * from sysobjects where name='n5pozdokmag_egz_insert')
	drop procedure n5pozdokmag_egz_insert
go
if exists (select * from sysobjects where name='n5pozdokmag_egz_update')
	drop procedure n5pozdokmag_egz_update
go
if exists (select * from sysobjects where name='n5pozdokmag_egz_delete')
	drop procedure n5pozdokmag_egz_delete
go
if exists (select * from sysobjects where name='n5pozdokmag_egz_maxid')
	drop procedure n5pozdokmag_egz_maxid
go
if exists (select * from sysobjects where name='n5pozdokmag_egz_candel')
	drop procedure n5pozdokmag_egz_candel
go
-- table: n5recepta
if exists (select * from sysobjects where name='n5recepta_select')
	drop procedure n5recepta_select
go
if exists (select * from sysobjects where name='n5recepta_insert')
	drop procedure n5recepta_insert
go
if exists (select * from sysobjects where name='n5recepta_update')
	drop procedure n5recepta_update
go
if exists (select * from sysobjects where name='n5recepta_delete')
	drop procedure n5recepta_delete
go
if exists (select * from sysobjects where name='n5recepta_maxid')
	drop procedure n5recepta_maxid
go
if exists (select * from sysobjects where name='n5recepta_candel')
	drop procedure n5recepta_candel
go
-- table: n5plnieob
if exists (select * from sysobjects where name='n5plnieob_select')
	drop procedure n5plnieob_select
go
if exists (select * from sysobjects where name='n5plnieob_insert')
	drop procedure n5plnieob_insert
go
if exists (select * from sysobjects where name='n5plnieob_update')
	drop procedure n5plnieob_update
go
if exists (select * from sysobjects where name='n5plnieob_delete')
	drop procedure n5plnieob_delete
go
if exists (select * from sysobjects where name='n5plnieob_maxid')
	drop procedure n5plnieob_maxid
go
if exists (select * from sysobjects where name='n5plnieob_candel')
	drop procedure n5plnieob_candel
go
-- table: n5plpozkalcp
if exists (select * from sysobjects where name='n5plpozkalcp_select')
	drop procedure n5plpozkalcp_select
go
if exists (select * from sysobjects where name='n5plpozkalcp_insert')
	drop procedure n5plpozkalcp_insert
go
if exists (select * from sysobjects where name='n5plpozkalcp_update')
	drop procedure n5plpozkalcp_update
go
if exists (select * from sysobjects where name='n5plpozkalcp_delete')
	drop procedure n5plpozkalcp_delete
go
if exists (select * from sysobjects where name='n5plpozkalcp_maxid')
	drop procedure n5plpozkalcp_maxid
go
if exists (select * from sysobjects where name='n5plpozkalcp_candel')
	drop procedure n5plpozkalcp_candel
go
-- table: n5pltyppracy
if exists (select * from sysobjects where name='n5pltyppracy_select')
	drop procedure n5pltyppracy_select
go
if exists (select * from sysobjects where name='n5pltyppracy_insert')
	drop procedure n5pltyppracy_insert
go
if exists (select * from sysobjects where name='n5pltyppracy_update')
	drop procedure n5pltyppracy_update
go
if exists (select * from sysobjects where name='n5pltyppracy_delete')
	drop procedure n5pltyppracy_delete
go
if exists (select * from sysobjects where name='n5pltyppracy_maxid')
	drop procedure n5pltyppracy_maxid
go
if exists (select * from sysobjects where name='n5pltyppracy_candel')
	drop procedure n5pltyppracy_candel
go
-- table: n5zasobprod
if exists (select * from sysobjects where name='n5zasobprod_select')
	drop procedure n5zasobprod_select
go
if exists (select * from sysobjects where name='n5zasobprod_insert')
	drop procedure n5zasobprod_insert
go
if exists (select * from sysobjects where name='n5zasobprod_update')
	drop procedure n5zasobprod_update
go
if exists (select * from sysobjects where name='n5zasobprod_delete')
	drop procedure n5zasobprod_delete
go
if exists (select * from sysobjects where name='n5zasobprod_maxid')
	drop procedure n5zasobprod_maxid
go
if exists (select * from sysobjects where name='n5zasobprod_candel')
	drop procedure n5zasobprod_candel
go
-- table: n5pozankieta_toral
if exists (select * from sysobjects where name='n5pozankieta_toral_select')
	drop procedure n5pozankieta_toral_select
go
if exists (select * from sysobjects where name='n5pozankieta_toral_insert')
	drop procedure n5pozankieta_toral_insert
go
if exists (select * from sysobjects where name='n5pozankieta_toral_update')
	drop procedure n5pozankieta_toral_update
go
if exists (select * from sysobjects where name='n5pozankieta_toral_delete')
	drop procedure n5pozankieta_toral_delete
go
if exists (select * from sysobjects where name='n5pozankieta_toral_maxid')
	drop procedure n5pozankieta_toral_maxid
go
if exists (select * from sysobjects where name='n5pozankieta_toral_candel')
	drop procedure n5pozankieta_toral_candel
go
-- table: n5globfile
if exists (select * from sysobjects where name='n5globfile_select')
	drop procedure n5globfile_select
go
if exists (select * from sysobjects where name='n5globfile_insert')
	drop procedure n5globfile_insert
go
if exists (select * from sysobjects where name='n5globfile_update')
	drop procedure n5globfile_update
go
if exists (select * from sysobjects where name='n5globfile_delete')
	drop procedure n5globfile_delete
go
if exists (select * from sysobjects where name='n5globfile_maxid')
	drop procedure n5globfile_maxid
go
if exists (select * from sysobjects where name='n5globfile_candel')
	drop procedure n5globfile_candel
go
-- table: n5_klient_jedn_org
if exists (select * from sysobjects where name='n5_klient_jedn_org_select')
	drop procedure n5_klient_jedn_org_select
go
if exists (select * from sysobjects where name='n5_klient_jedn_org_insert')
	drop procedure n5_klient_jedn_org_insert
go
if exists (select * from sysobjects where name='n5_klient_jedn_org_update')
	drop procedure n5_klient_jedn_org_update
go
if exists (select * from sysobjects where name='n5_klient_jedn_org_delete')
	drop procedure n5_klient_jedn_org_delete
go
if exists (select * from sysobjects where name='n5_klient_jedn_org_maxid')
	drop procedure n5_klient_jedn_org_maxid
go
if exists (select * from sysobjects where name='n5_klient_jedn_org_candel')
	drop procedure n5_klient_jedn_org_candel
go
-- table: n5produkt
if exists (select * from sysobjects where name='n5produkt_select')
	drop procedure n5produkt_select
go
if exists (select * from sysobjects where name='n5produkt_insert')
	drop procedure n5produkt_insert
go
if exists (select * from sysobjects where name='n5produkt_update')
	drop procedure n5produkt_update
go
if exists (select * from sysobjects where name='n5produkt_delete')
	drop procedure n5produkt_delete
go
if exists (select * from sysobjects where name='n5produkt_maxid')
	drop procedure n5produkt_maxid
go
if exists (select * from sysobjects where name='n5produkt_candel')
	drop procedure n5produkt_candel
go
-- table: n5dowodksieg
if exists (select * from sysobjects where name='n5dowodksieg_select')
	drop procedure n5dowodksieg_select
go
if exists (select * from sysobjects where name='n5dowodksieg_insert')
	drop procedure n5dowodksieg_insert
go
if exists (select * from sysobjects where name='n5dowodksieg_update')
	drop procedure n5dowodksieg_update
go
if exists (select * from sysobjects where name='n5dowodksieg_delete')
	drop procedure n5dowodksieg_delete
go
if exists (select * from sysobjects where name='n5dowodksieg_maxid')
	drop procedure n5dowodksieg_maxid
go
if exists (select * from sysobjects where name='n5dowodksieg_candel')
	drop procedure n5dowodksieg_candel
go
-- table: n5kurswalut
if exists (select * from sysobjects where name='n5kurswalut_select')
	drop procedure n5kurswalut_select
go
if exists (select * from sysobjects where name='n5kurswalut_insert')
	drop procedure n5kurswalut_insert
go
if exists (select * from sysobjects where name='n5kurswalut_update')
	drop procedure n5kurswalut_update
go
if exists (select * from sysobjects where name='n5kurswalut_delete')
	drop procedure n5kurswalut_delete
go
if exists (select * from sysobjects where name='n5kurswalut_maxid')
	drop procedure n5kurswalut_maxid
go
if exists (select * from sysobjects where name='n5kurswalut_candel')
	drop procedure n5kurswalut_candel
go
-- table: n5plumowa
if exists (select * from sysobjects where name='n5plumowa_select')
	drop procedure n5plumowa_select
go
if exists (select * from sysobjects where name='n5plumowa_insert')
	drop procedure n5plumowa_insert
go
if exists (select * from sysobjects where name='n5plumowa_update')
	drop procedure n5plumowa_update
go
if exists (select * from sysobjects where name='n5plumowa_delete')
	drop procedure n5plumowa_delete
go
if exists (select * from sysobjects where name='n5plumowa_maxid')
	drop procedure n5plumowa_maxid
go
if exists (select * from sysobjects where name='n5plumowa_candel')
	drop procedure n5plumowa_candel
go
-- table: n5opsrtrw
if exists (select * from sysobjects where name='n5opsrtrw_select')
	drop procedure n5opsrtrw_select
go
if exists (select * from sysobjects where name='n5opsrtrw_insert')
	drop procedure n5opsrtrw_insert
go
if exists (select * from sysobjects where name='n5opsrtrw_update')
	drop procedure n5opsrtrw_update
go
if exists (select * from sysobjects where name='n5opsrtrw_delete')
	drop procedure n5opsrtrw_delete
go
if exists (select * from sysobjects where name='n5opsrtrw_maxid')
	drop procedure n5opsrtrw_maxid
go
if exists (select * from sysobjects where name='n5opsrtrw_candel')
	drop procedure n5opsrtrw_candel
go
-- table: n5rolawyk
if exists (select * from sysobjects where name='n5rolawyk_select')
	drop procedure n5rolawyk_select
go
if exists (select * from sysobjects where name='n5rolawyk_insert')
	drop procedure n5rolawyk_insert
go
if exists (select * from sysobjects where name='n5rolawyk_update')
	drop procedure n5rolawyk_update
go
if exists (select * from sysobjects where name='n5rolawyk_delete')
	drop procedure n5rolawyk_delete
go
if exists (select * from sysobjects where name='n5rolawyk_maxid')
	drop procedure n5rolawyk_maxid
go
if exists (select * from sysobjects where name='n5rolawyk_candel')
	drop procedure n5rolawyk_candel
go
-- table: n5ptop
if exists (select * from sysobjects where name='n5ptop_select')
	drop procedure n5ptop_select
go
if exists (select * from sysobjects where name='n5ptop_insert')
	drop procedure n5ptop_insert
go
if exists (select * from sysobjects where name='n5ptop_update')
	drop procedure n5ptop_update
go
if exists (select * from sysobjects where name='n5ptop_delete')
	drop procedure n5ptop_delete
go
if exists (select * from sysobjects where name='n5ptop_maxid')
	drop procedure n5ptop_maxid
go
if exists (select * from sysobjects where name='n5ptop_candel')
	drop procedure n5ptop_candel
go
-- table: n5poz_koszt_wyjazdu
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_select')
	drop procedure n5poz_koszt_wyjazdu_select
go
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_insert')
	drop procedure n5poz_koszt_wyjazdu_insert
go
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_update')
	drop procedure n5poz_koszt_wyjazdu_update
go
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_delete')
	drop procedure n5poz_koszt_wyjazdu_delete
go
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_maxid')
	drop procedure n5poz_koszt_wyjazdu_maxid
go
if exists (select * from sysobjects where name='n5poz_koszt_wyjazdu_candel')
	drop procedure n5poz_koszt_wyjazdu_candel
go
-- table: n5miejscowosc
if exists (select * from sysobjects where name='n5miejscowosc_select')
	drop procedure n5miejscowosc_select
go
if exists (select * from sysobjects where name='n5miejscowosc_insert')
	drop procedure n5miejscowosc_insert
go
if exists (select * from sysobjects where name='n5miejscowosc_update')
	drop procedure n5miejscowosc_update
go
if exists (select * from sysobjects where name='n5miejscowosc_delete')
	drop procedure n5miejscowosc_delete
go
if exists (select * from sysobjects where name='n5miejscowosc_maxid')
	drop procedure n5miejscowosc_maxid
go
if exists (select * from sysobjects where name='n5miejscowosc_candel')
	drop procedure n5miejscowosc_candel
go
-- table: n5SendEmail
if exists (select * from sysobjects where name='n5SendEmail_select')
	drop procedure n5SendEmail_select
go
if exists (select * from sysobjects where name='n5SendEmail_insert')
	drop procedure n5SendEmail_insert
go
if exists (select * from sysobjects where name='n5SendEmail_update')
	drop procedure n5SendEmail_update
go
if exists (select * from sysobjects where name='n5SendEmail_delete')
	drop procedure n5SendEmail_delete
go
if exists (select * from sysobjects where name='n5SendEmail_maxid')
	drop procedure n5SendEmail_maxid
go
if exists (select * from sysobjects where name='n5SendEmail_candel')
	drop procedure n5SendEmail_candel
go
-- table: n5rejestrdok
if exists (select * from sysobjects where name='n5rejestrdok_select')
	drop procedure n5rejestrdok_select
go
if exists (select * from sysobjects where name='n5rejestrdok_insert')
	drop procedure n5rejestrdok_insert
go
if exists (select * from sysobjects where name='n5rejestrdok_update')
	drop procedure n5rejestrdok_update
go
if exists (select * from sysobjects where name='n5rejestrdok_delete')
	drop procedure n5rejestrdok_delete
go
if exists (select * from sysobjects where name='n5rejestrdok_maxid')
	drop procedure n5rejestrdok_maxid
go
if exists (select * from sysobjects where name='n5rejestrdok_candel')
	drop procedure n5rejestrdok_candel
go
-- table: n5dokmag
if exists (select * from sysobjects where name='n5dokmag_select')
	drop procedure n5dokmag_select
go
if exists (select * from sysobjects where name='n5dokmag_insert')
	drop procedure n5dokmag_insert
go
if exists (select * from sysobjects where name='n5dokmag_update')
	drop procedure n5dokmag_update
go
if exists (select * from sysobjects where name='n5dokmag_delete')
	drop procedure n5dokmag_delete
go
if exists (select * from sysobjects where name='n5dokmag_maxid')
	drop procedure n5dokmag_maxid
go
if exists (select * from sysobjects where name='n5dokmag_candel')
	drop procedure n5dokmag_candel
go
-- table: n5srtrw
if exists (select * from sysobjects where name='n5srtrw_select')
	drop procedure n5srtrw_select
go
if exists (select * from sysobjects where name='n5srtrw_insert')
	drop procedure n5srtrw_insert
go
if exists (select * from sysobjects where name='n5srtrw_update')
	drop procedure n5srtrw_update
go
if exists (select * from sysobjects where name='n5srtrw_delete')
	drop procedure n5srtrw_delete
go
if exists (select * from sysobjects where name='n5srtrw_maxid')
	drop procedure n5srtrw_maxid
go
if exists (select * from sysobjects where name='n5srtrw_candel')
	drop procedure n5srtrw_candel
go
-- table: n5plsubkonto
if exists (select * from sysobjects where name='n5plsubkonto_select')
	drop procedure n5plsubkonto_select
go
if exists (select * from sysobjects where name='n5plsubkonto_insert')
	drop procedure n5plsubkonto_insert
go
if exists (select * from sysobjects where name='n5plsubkonto_update')
	drop procedure n5plsubkonto_update
go
if exists (select * from sysobjects where name='n5plsubkonto_delete')
	drop procedure n5plsubkonto_delete
go
if exists (select * from sysobjects where name='n5plsubkonto_maxid')
	drop procedure n5plsubkonto_maxid
go
if exists (select * from sysobjects where name='n5plsubkonto_candel')
	drop procedure n5plsubkonto_candel
go
-- table: n5bwinfo_zal
if exists (select * from sysobjects where name='n5bwinfo_zal_select')
	drop procedure n5bwinfo_zal_select
go
if exists (select * from sysobjects where name='n5bwinfo_zal_insert')
	drop procedure n5bwinfo_zal_insert
go
if exists (select * from sysobjects where name='n5bwinfo_zal_update')
	drop procedure n5bwinfo_zal_update
go
if exists (select * from sysobjects where name='n5bwinfo_zal_delete')
	drop procedure n5bwinfo_zal_delete
go
if exists (select * from sysobjects where name='n5bwinfo_zal_maxid')
	drop procedure n5bwinfo_zal_maxid
go
if exists (select * from sysobjects where name='n5bwinfo_zal_candel')
	drop procedure n5bwinfo_zal_candel
go
-- table: n5rola
if exists (select * from sysobjects where name='n5rola_select')
	drop procedure n5rola_select
go
if exists (select * from sysobjects where name='n5rola_insert')
	drop procedure n5rola_insert
go
if exists (select * from sysobjects where name='n5rola_update')
	drop procedure n5rola_update
go
if exists (select * from sysobjects where name='n5rola_delete')
	drop procedure n5rola_delete
go
if exists (select * from sysobjects where name='n5rola_maxid')
	drop procedure n5rola_maxid
go
if exists (select * from sysobjects where name='n5rola_candel')
	drop procedure n5rola_candel
go
-- table: n5stanowisko
if exists (select * from sysobjects where name='n5stanowisko_select')
	drop procedure n5stanowisko_select
go
if exists (select * from sysobjects where name='n5stanowisko_insert')
	drop procedure n5stanowisko_insert
go
if exists (select * from sysobjects where name='n5stanowisko_update')
	drop procedure n5stanowisko_update
go
if exists (select * from sysobjects where name='n5stanowisko_delete')
	drop procedure n5stanowisko_delete
go
if exists (select * from sysobjects where name='n5stanowisko_maxid')
	drop procedure n5stanowisko_maxid
go
if exists (select * from sysobjects where name='n5stanowisko_candel')
	drop procedure n5stanowisko_candel
go
-- table: n5securityobj
if exists (select * from sysobjects where name='n5securityobj_select')
	drop procedure n5securityobj_select
go
if exists (select * from sysobjects where name='n5securityobj_insert')
	drop procedure n5securityobj_insert
go
if exists (select * from sysobjects where name='n5securityobj_update')
	drop procedure n5securityobj_update
go
if exists (select * from sysobjects where name='n5securityobj_delete')
	drop procedure n5securityobj_delete
go
if exists (select * from sysobjects where name='n5securityobj_maxid')
	drop procedure n5securityobj_maxid
go
if exists (select * from sysobjects where name='n5securityobj_candel')
	drop procedure n5securityobj_candel
go
-- table: n5klient
if exists (select * from sysobjects where name='n5klient_select')
	drop procedure n5klient_select
go
if exists (select * from sysobjects where name='n5klient_insert')
	drop procedure n5klient_insert
go
if exists (select * from sysobjects where name='n5klient_update')
	drop procedure n5klient_update
go
if exists (select * from sysobjects where name='n5klient_delete')
	drop procedure n5klient_delete
go
if exists (select * from sysobjects where name='n5klient_maxid')
	drop procedure n5klient_maxid
go
if exists (select * from sysobjects where name='n5klient_candel')
	drop procedure n5klient_candel
go
-- table: n5zadaniezal
if exists (select * from sysobjects where name='n5zadaniezal_select')
	drop procedure n5zadaniezal_select
go
if exists (select * from sysobjects where name='n5zadaniezal_insert')
	drop procedure n5zadaniezal_insert
go
if exists (select * from sysobjects where name='n5zadaniezal_update')
	drop procedure n5zadaniezal_update
go
if exists (select * from sysobjects where name='n5zadaniezal_delete')
	drop procedure n5zadaniezal_delete
go
if exists (select * from sysobjects where name='n5zadaniezal_maxid')
	drop procedure n5zadaniezal_maxid
go
if exists (select * from sysobjects where name='n5zadaniezal_candel')
	drop procedure n5zadaniezal_candel
go
-- table: n5analfinans
if exists (select * from sysobjects where name='n5analfinans_select')
	drop procedure n5analfinans_select
go
if exists (select * from sysobjects where name='n5analfinans_insert')
	drop procedure n5analfinans_insert
go
if exists (select * from sysobjects where name='n5analfinans_update')
	drop procedure n5analfinans_update
go
if exists (select * from sysobjects where name='n5analfinans_delete')
	drop procedure n5analfinans_delete
go
if exists (select * from sysobjects where name='n5analfinans_maxid')
	drop procedure n5analfinans_maxid
go
if exists (select * from sysobjects where name='n5analfinans_candel')
	drop procedure n5analfinans_candel
go
-- table: n5sposdost
if exists (select * from sysobjects where name='n5sposdost_select')
	drop procedure n5sposdost_select
go
if exists (select * from sysobjects where name='n5sposdost_insert')
	drop procedure n5sposdost_insert
go
if exists (select * from sysobjects where name='n5sposdost_update')
	drop procedure n5sposdost_update
go
if exists (select * from sysobjects where name='n5sposdost_delete')
	drop procedure n5sposdost_delete
go
if exists (select * from sysobjects where name='n5sposdost_maxid')
	drop procedure n5sposdost_maxid
go
if exists (select * from sysobjects where name='n5sposdost_candel')
	drop procedure n5sposdost_candel
go
-- table: n5zakup
if exists (select * from sysobjects where name='n5zakup_select')
	drop procedure n5zakup_select
go
if exists (select * from sysobjects where name='n5zakup_insert')
	drop procedure n5zakup_insert
go
if exists (select * from sysobjects where name='n5zakup_update')
	drop procedure n5zakup_update
go
if exists (select * from sysobjects where name='n5zakup_delete')
	drop procedure n5zakup_delete
go
if exists (select * from sysobjects where name='n5zakup_maxid')
	drop procedure n5zakup_maxid
go
if exists (select * from sysobjects where name='n5zakup_candel')
	drop procedure n5zakup_candel
go
-- table: n5plsklnal
if exists (select * from sysobjects where name='n5plsklnal_select')
	drop procedure n5plsklnal_select
go
if exists (select * from sysobjects where name='n5plsklnal_insert')
	drop procedure n5plsklnal_insert
go
if exists (select * from sysobjects where name='n5plsklnal_update')
	drop procedure n5plsklnal_update
go
if exists (select * from sysobjects where name='n5plsklnal_delete')
	drop procedure n5plsklnal_delete
go
if exists (select * from sysobjects where name='n5plsklnal_maxid')
	drop procedure n5plsklnal_maxid
go
if exists (select * from sysobjects where name='n5plsklnal_candel')
	drop procedure n5plsklnal_candel
go
-- table: n5bwinfo_kat
if exists (select * from sysobjects where name='n5bwinfo_kat_select')
	drop procedure n5bwinfo_kat_select
go
if exists (select * from sysobjects where name='n5bwinfo_kat_insert')
	drop procedure n5bwinfo_kat_insert
go
if exists (select * from sysobjects where name='n5bwinfo_kat_update')
	drop procedure n5bwinfo_kat_update
go
if exists (select * from sysobjects where name='n5bwinfo_kat_delete')
	drop procedure n5bwinfo_kat_delete
go
if exists (select * from sysobjects where name='n5bwinfo_kat_maxid')
	drop procedure n5bwinfo_kat_maxid
go
if exists (select * from sysobjects where name='n5bwinfo_kat_candel')
	drop procedure n5bwinfo_kat_candel
go
-- table: n5istat
if exists (select * from sysobjects where name='n5istat_select')
	drop procedure n5istat_select
go
if exists (select * from sysobjects where name='n5istat_insert')
	drop procedure n5istat_insert
go
if exists (select * from sysobjects where name='n5istat_update')
	drop procedure n5istat_update
go
if exists (select * from sysobjects where name='n5istat_delete')
	drop procedure n5istat_delete
go
if exists (select * from sysobjects where name='n5istat_maxid')
	drop procedure n5istat_maxid
go
if exists (select * from sysobjects where name='n5istat_candel')
	drop procedure n5istat_candel
go
-- table: n5protokol_abas
if exists (select * from sysobjects where name='n5protokol_abas_select')
	drop procedure n5protokol_abas_select
go
if exists (select * from sysobjects where name='n5protokol_abas_insert')
	drop procedure n5protokol_abas_insert
go
if exists (select * from sysobjects where name='n5protokol_abas_update')
	drop procedure n5protokol_abas_update
go
if exists (select * from sysobjects where name='n5protokol_abas_delete')
	drop procedure n5protokol_abas_delete
go
if exists (select * from sysobjects where name='n5protokol_abas_maxid')
	drop procedure n5protokol_abas_maxid
go
if exists (select * from sysobjects where name='n5protokol_abas_candel')
	drop procedure n5protokol_abas_candel
go
-- table: n5kolor
if exists (select * from sysobjects where name='n5kolor_select')
	drop procedure n5kolor_select
go
if exists (select * from sysobjects where name='n5kolor_insert')
	drop procedure n5kolor_insert
go
if exists (select * from sysobjects where name='n5kolor_update')
	drop procedure n5kolor_update
go
if exists (select * from sysobjects where name='n5kolor_delete')
	drop procedure n5kolor_delete
go
if exists (select * from sysobjects where name='n5kolor_maxid')
	drop procedure n5kolor_maxid
go
if exists (select * from sysobjects where name='n5kolor_candel')
	drop procedure n5kolor_candel
go
-- table: n5pozrejestrdok_mag
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_select')
	drop procedure n5pozrejestrdok_mag_select
go
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_insert')
	drop procedure n5pozrejestrdok_mag_insert
go
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_update')
	drop procedure n5pozrejestrdok_mag_update
go
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_delete')
	drop procedure n5pozrejestrdok_mag_delete
go
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_maxid')
	drop procedure n5pozrejestrdok_mag_maxid
go
if exists (select * from sysobjects where name='n5pozrejestrdok_mag_candel')
	drop procedure n5pozrejestrdok_mag_candel
go
-- table: SearchTypeItem
if exists (select * from sysobjects where name='SearchTypeItem_select')
	drop procedure SearchTypeItem_select
go
if exists (select * from sysobjects where name='SearchTypeItem_insert')
	drop procedure SearchTypeItem_insert
go
if exists (select * from sysobjects where name='SearchTypeItem_update')
	drop procedure SearchTypeItem_update
go
if exists (select * from sysobjects where name='SearchTypeItem_delete')
	drop procedure SearchTypeItem_delete
go
if exists (select * from sysobjects where name='SearchTypeItem_maxid')
	drop procedure SearchTypeItem_maxid
go
if exists (select * from sysobjects where name='SearchTypeItem_candel')
	drop procedure SearchTypeItem_candel
go
-- table: n5instytucja
if exists (select * from sysobjects where name='n5instytucja_select')
	drop procedure n5instytucja_select
go
if exists (select * from sysobjects where name='n5instytucja_insert')
	drop procedure n5instytucja_insert
go
if exists (select * from sysobjects where name='n5instytucja_update')
	drop procedure n5instytucja_update
go
if exists (select * from sysobjects where name='n5instytucja_delete')
	drop procedure n5instytucja_delete
go
if exists (select * from sysobjects where name='n5instytucja_maxid')
	drop procedure n5instytucja_maxid
go
if exists (select * from sysobjects where name='n5instytucja_candel')
	drop procedure n5instytucja_candel
go
-- table: n5wykonawca
if exists (select * from sysobjects where name='n5wykonawca_select')
	drop procedure n5wykonawca_select
go
if exists (select * from sysobjects where name='n5wykonawca_insert')
	drop procedure n5wykonawca_insert
go
if exists (select * from sysobjects where name='n5wykonawca_update')
	drop procedure n5wykonawca_update
go
if exists (select * from sysobjects where name='n5wykonawca_delete')
	drop procedure n5wykonawca_delete
go
if exists (select * from sysobjects where name='n5wykonawca_maxid')
	drop procedure n5wykonawca_maxid
go
if exists (select * from sysobjects where name='n5wykonawca_candel')
	drop procedure n5wykonawca_candel
go
-- table: n5powiat
if exists (select * from sysobjects where name='n5powiat_select')
	drop procedure n5powiat_select
go
if exists (select * from sysobjects where name='n5powiat_insert')
	drop procedure n5powiat_insert
go
if exists (select * from sysobjects where name='n5powiat_update')
	drop procedure n5powiat_update
go
if exists (select * from sysobjects where name='n5powiat_delete')
	drop procedure n5powiat_delete
go
if exists (select * from sysobjects where name='n5powiat_maxid')
	drop procedure n5powiat_maxid
go
if exists (select * from sysobjects where name='n5powiat_candel')
	drop procedure n5powiat_candel
go
-- table: n5pozrata
if exists (select * from sysobjects where name='n5pozrata_select')
	drop procedure n5pozrata_select
go
if exists (select * from sysobjects where name='n5pozrata_insert')
	drop procedure n5pozrata_insert
go
if exists (select * from sysobjects where name='n5pozrata_update')
	drop procedure n5pozrata_update
go
if exists (select * from sysobjects where name='n5pozrata_delete')
	drop procedure n5pozrata_delete
go
if exists (select * from sysobjects where name='n5pozrata_maxid')
	drop procedure n5pozrata_maxid
go
if exists (select * from sysobjects where name='n5pozrata_candel')
	drop procedure n5pozrata_candel
go
-- table: n5pozzamowienie
if exists (select * from sysobjects where name='n5pozzamowienie_select')
	drop procedure n5pozzamowienie_select
go
if exists (select * from sysobjects where name='n5pozzamowienie_insert')
	drop procedure n5pozzamowienie_insert
go
if exists (select * from sysobjects where name='n5pozzamowienie_update')
	drop procedure n5pozzamowienie_update
go
if exists (select * from sysobjects where name='n5pozzamowienie_delete')
	drop procedure n5pozzamowienie_delete
go
if exists (select * from sysobjects where name='n5pozzamowienie_maxid')
	drop procedure n5pozzamowienie_maxid
go
if exists (select * from sysobjects where name='n5pozzamowienie_candel')
	drop procedure n5pozzamowienie_candel
go
-- table: n5plschematnal
if exists (select * from sysobjects where name='n5plschematnal_select')
	drop procedure n5plschematnal_select
go
if exists (select * from sysobjects where name='n5plschematnal_insert')
	drop procedure n5plschematnal_insert
go
if exists (select * from sysobjects where name='n5plschematnal_update')
	drop procedure n5plschematnal_update
go
if exists (select * from sysobjects where name='n5plschematnal_delete')
	drop procedure n5plschematnal_delete
go
if exists (select * from sysobjects where name='n5plschematnal_maxid')
	drop procedure n5plschematnal_maxid
go
if exists (select * from sysobjects where name='n5plschematnal_candel')
	drop procedure n5plschematnal_candel
go
-- table: n5kwalifikator
if exists (select * from sysobjects where name='n5kwalifikator_select')
	drop procedure n5kwalifikator_select
go
if exists (select * from sysobjects where name='n5kwalifikator_insert')
	drop procedure n5kwalifikator_insert
go
if exists (select * from sysobjects where name='n5kwalifikator_update')
	drop procedure n5kwalifikator_update
go
if exists (select * from sysobjects where name='n5kwalifikator_delete')
	drop procedure n5kwalifikator_delete
go
if exists (select * from sysobjects where name='n5kwalifikator_maxid')
	drop procedure n5kwalifikator_maxid
go
if exists (select * from sysobjects where name='n5kwalifikator_candel')
	drop procedure n5kwalifikator_candel
go
-- table: n5plpozschnal
if exists (select * from sysobjects where name='n5plpozschnal_select')
	drop procedure n5plpozschnal_select
go
if exists (select * from sysobjects where name='n5plpozschnal_insert')
	drop procedure n5plpozschnal_insert
go
if exists (select * from sysobjects where name='n5plpozschnal_update')
	drop procedure n5plpozschnal_update
go
if exists (select * from sysobjects where name='n5plpozschnal_delete')
	drop procedure n5plpozschnal_delete
go
if exists (select * from sysobjects where name='n5plpozschnal_maxid')
	drop procedure n5plpozschnal_maxid
go
if exists (select * from sysobjects where name='n5plpozschnal_candel')
	drop procedure n5plpozschnal_candel
go
-- skipped virtual table: n5vatuek
-- table: n5pozrealprod_zasob
if exists (select * from sysobjects where name='n5pozrealprod_zasob_select')
	drop procedure n5pozrealprod_zasob_select
go
if exists (select * from sysobjects where name='n5pozrealprod_zasob_insert')
	drop procedure n5pozrealprod_zasob_insert
go
if exists (select * from sysobjects where name='n5pozrealprod_zasob_update')
	drop procedure n5pozrealprod_zasob_update
go
if exists (select * from sysobjects where name='n5pozrealprod_zasob_delete')
	drop procedure n5pozrealprod_zasob_delete
go
if exists (select * from sysobjects where name='n5pozrealprod_zasob_maxid')
	drop procedure n5pozrealprod_zasob_maxid
go
if exists (select * from sysobjects where name='n5pozrealprod_zasob_candel')
	drop procedure n5pozrealprod_zasob_candel
go
-- table: n5straznik_cen
if exists (select * from sysobjects where name='n5straznik_cen_select')
	drop procedure n5straznik_cen_select
go
if exists (select * from sysobjects where name='n5straznik_cen_insert')
	drop procedure n5straznik_cen_insert
go
if exists (select * from sysobjects where name='n5straznik_cen_update')
	drop procedure n5straznik_cen_update
go
if exists (select * from sysobjects where name='n5straznik_cen_delete')
	drop procedure n5straznik_cen_delete
go
if exists (select * from sysobjects where name='n5straznik_cen_maxid')
	drop procedure n5straznik_cen_maxid
go
if exists (select * from sysobjects where name='n5straznik_cen_candel')
	drop procedure n5straznik_cen_candel
go
-- table: n5jednostka
if exists (select * from sysobjects where name='n5jednostka_select')
	drop procedure n5jednostka_select
go
if exists (select * from sysobjects where name='n5jednostka_insert')
	drop procedure n5jednostka_insert
go
if exists (select * from sysobjects where name='n5jednostka_update')
	drop procedure n5jednostka_update
go
if exists (select * from sysobjects where name='n5jednostka_delete')
	drop procedure n5jednostka_delete
go
if exists (select * from sysobjects where name='n5jednostka_maxid')
	drop procedure n5jednostka_maxid
go
if exists (select * from sysobjects where name='n5jednostka_candel')
	drop procedure n5jednostka_candel
go
-- table: n5zadanie
if exists (select * from sysobjects where name='n5zadanie_select')
	drop procedure n5zadanie_select
go
if exists (select * from sysobjects where name='n5zadanie_insert')
	drop procedure n5zadanie_insert
go
if exists (select * from sysobjects where name='n5zadanie_update')
	drop procedure n5zadanie_update
go
if exists (select * from sysobjects where name='n5zadanie_delete')
	drop procedure n5zadanie_delete
go
if exists (select * from sysobjects where name='n5zadanie_maxid')
	drop procedure n5zadanie_maxid
go
if exists (select * from sysobjects where name='n5zadanie_candel')
	drop procedure n5zadanie_candel
go
-- table: n5pit5
if exists (select * from sysobjects where name='n5pit5_select')
	drop procedure n5pit5_select
go
if exists (select * from sysobjects where name='n5pit5_insert')
	drop procedure n5pit5_insert
go
if exists (select * from sysobjects where name='n5pit5_update')
	drop procedure n5pit5_update
go
if exists (select * from sysobjects where name='n5pit5_delete')
	drop procedure n5pit5_delete
go
if exists (select * from sysobjects where name='n5pit5_maxid')
	drop procedure n5pit5_maxid
go
if exists (select * from sysobjects where name='n5pit5_candel')
	drop procedure n5pit5_candel
go
-- table: n5typdzialania
if exists (select * from sysobjects where name='n5typdzialania_select')
	drop procedure n5typdzialania_select
go
if exists (select * from sysobjects where name='n5typdzialania_insert')
	drop procedure n5typdzialania_insert
go
if exists (select * from sysobjects where name='n5typdzialania_update')
	drop procedure n5typdzialania_update
go
if exists (select * from sysobjects where name='n5typdzialania_delete')
	drop procedure n5typdzialania_delete
go
if exists (select * from sysobjects where name='n5typdzialania_maxid')
	drop procedure n5typdzialania_maxid
go
if exists (select * from sysobjects where name='n5typdzialania_candel')
	drop procedure n5typdzialania_candel
go
-- table: n5zlecprod
if exists (select * from sysobjects where name='n5zlecprod_select')
	drop procedure n5zlecprod_select
go
if exists (select * from sysobjects where name='n5zlecprod_insert')
	drop procedure n5zlecprod_insert
go
if exists (select * from sysobjects where name='n5zlecprod_update')
	drop procedure n5zlecprod_update
go
if exists (select * from sysobjects where name='n5zlecprod_delete')
	drop procedure n5zlecprod_delete
go
if exists (select * from sysobjects where name='n5zlecprod_maxid')
	drop procedure n5zlecprod_maxid
go
if exists (select * from sysobjects where name='n5zlecprod_candel')
	drop procedure n5zlecprod_candel
go
-- table: n5rule
if exists (select * from sysobjects where name='n5rule_select')
	drop procedure n5rule_select
go
if exists (select * from sysobjects where name='n5rule_insert')
	drop procedure n5rule_insert
go
if exists (select * from sysobjects where name='n5rule_update')
	drop procedure n5rule_update
go
if exists (select * from sysobjects where name='n5rule_delete')
	drop procedure n5rule_delete
go
if exists (select * from sysobjects where name='n5rule_maxid')
	drop procedure n5rule_maxid
go
if exists (select * from sysobjects where name='n5rule_candel')
	drop procedure n5rule_candel
go
-- table: n5plpozostale
if exists (select * from sysobjects where name='n5plpozostale_select')
	drop procedure n5plpozostale_select
go
if exists (select * from sysobjects where name='n5plpozostale_insert')
	drop procedure n5plpozostale_insert
go
if exists (select * from sysobjects where name='n5plpozostale_update')
	drop procedure n5plpozostale_update
go
if exists (select * from sysobjects where name='n5plpozostale_delete')
	drop procedure n5plpozostale_delete
go
if exists (select * from sysobjects where name='n5plpozostale_maxid')
	drop procedure n5plpozostale_maxid
go
if exists (select * from sysobjects where name='n5plpozostale_candel')
	drop procedure n5plpozostale_candel
go
-- table: n5pozdokprod
if exists (select * from sysobjects where name='n5pozdokprod_select')
	drop procedure n5pozdokprod_select
go
if exists (select * from sysobjects where name='n5pozdokprod_insert')
	drop procedure n5pozdokprod_insert
go
if exists (select * from sysobjects where name='n5pozdokprod_update')
	drop procedure n5pozdokprod_update
go
if exists (select * from sysobjects where name='n5pozdokprod_delete')
	drop procedure n5pozdokprod_delete
go
if exists (select * from sysobjects where name='n5pozdokprod_maxid')
	drop procedure n5pozdokprod_maxid
go
if exists (select * from sysobjects where name='n5pozdokprod_candel')
	drop procedure n5pozdokprod_candel
go
-- table: n5pozrecepta_zasob
if exists (select * from sysobjects where name='n5pozrecepta_zasob_select')
	drop procedure n5pozrecepta_zasob_select
go
if exists (select * from sysobjects where name='n5pozrecepta_zasob_insert')
	drop procedure n5pozrecepta_zasob_insert
go
if exists (select * from sysobjects where name='n5pozrecepta_zasob_update')
	drop procedure n5pozrecepta_zasob_update
go
if exists (select * from sysobjects where name='n5pozrecepta_zasob_delete')
	drop procedure n5pozrecepta_zasob_delete
go
if exists (select * from sysobjects where name='n5pozrecepta_zasob_maxid')
	drop procedure n5pozrecepta_zasob_maxid
go
if exists (select * from sysobjects where name='n5pozrecepta_zasob_candel')
	drop procedure n5pozrecepta_zasob_candel
go
-- table: n5inwmag
if exists (select * from sysobjects where name='n5inwmag_select')
	drop procedure n5inwmag_select
go
if exists (select * from sysobjects where name='n5inwmag_insert')
	drop procedure n5inwmag_insert
go
if exists (select * from sysobjects where name='n5inwmag_update')
	drop procedure n5inwmag_update
go
if exists (select * from sysobjects where name='n5inwmag_delete')
	drop procedure n5inwmag_delete
go
if exists (select * from sysobjects where name='n5inwmag_maxid')
	drop procedure n5inwmag_maxid
go
if exists (select * from sysobjects where name='n5inwmag_candel')
	drop procedure n5inwmag_candel
go
-- table: n5grupaproduktow
if exists (select * from sysobjects where name='n5grupaproduktow_select')
	drop procedure n5grupaproduktow_select
go
if exists (select * from sysobjects where name='n5grupaproduktow_insert')
	drop procedure n5grupaproduktow_insert
go
if exists (select * from sysobjects where name='n5grupaproduktow_update')
	drop procedure n5grupaproduktow_update
go
if exists (select * from sysobjects where name='n5grupaproduktow_delete')
	drop procedure n5grupaproduktow_delete
go
if exists (select * from sysobjects where name='n5grupaproduktow_maxid')
	drop procedure n5grupaproduktow_maxid
go
if exists (select * from sysobjects where name='n5grupaproduktow_candel')
	drop procedure n5grupaproduktow_candel
go
-- table: n5dokumentlinks
if exists (select * from sysobjects where name='n5dokumentlinks_select')
	drop procedure n5dokumentlinks_select
go
if exists (select * from sysobjects where name='n5dokumentlinks_insert')
	drop procedure n5dokumentlinks_insert
go
if exists (select * from sysobjects where name='n5dokumentlinks_update')
	drop procedure n5dokumentlinks_update
go
if exists (select * from sysobjects where name='n5dokumentlinks_delete')
	drop procedure n5dokumentlinks_delete
go
if exists (select * from sysobjects where name='n5dokumentlinks_maxid')
	drop procedure n5dokumentlinks_maxid
go
if exists (select * from sysobjects where name='n5dokumentlinks_candel')
	drop procedure n5dokumentlinks_candel
go
-- table: n5platnosc
if exists (select * from sysobjects where name='n5platnosc_select')
	drop procedure n5platnosc_select
go
if exists (select * from sysobjects where name='n5platnosc_insert')
	drop procedure n5platnosc_insert
go
if exists (select * from sysobjects where name='n5platnosc_update')
	drop procedure n5platnosc_update
go
if exists (select * from sysobjects where name='n5platnosc_delete')
	drop procedure n5platnosc_delete
go
if exists (select * from sysobjects where name='n5platnosc_maxid')
	drop procedure n5platnosc_maxid
go
if exists (select * from sysobjects where name='n5platnosc_candel')
	drop procedure n5platnosc_candel
go
-- table: n5pozdoketyk
if exists (select * from sysobjects where name='n5pozdoketyk_select')
	drop procedure n5pozdoketyk_select
go
if exists (select * from sysobjects where name='n5pozdoketyk_insert')
	drop procedure n5pozdoketyk_insert
go
if exists (select * from sysobjects where name='n5pozdoketyk_update')
	drop procedure n5pozdoketyk_update
go
if exists (select * from sysobjects where name='n5pozdoketyk_delete')
	drop procedure n5pozdoketyk_delete
go
if exists (select * from sysobjects where name='n5pozdoketyk_maxid')
	drop procedure n5pozdoketyk_maxid
go
if exists (select * from sysobjects where name='n5pozdoketyk_candel')
	drop procedure n5pozdoketyk_candel
go
-- table: n5pozrecepta
if exists (select * from sysobjects where name='n5pozrecepta_select')
	drop procedure n5pozrecepta_select
go
if exists (select * from sysobjects where name='n5pozrecepta_insert')
	drop procedure n5pozrecepta_insert
go
if exists (select * from sysobjects where name='n5pozrecepta_update')
	drop procedure n5pozrecepta_update
go
if exists (select * from sysobjects where name='n5pozrecepta_delete')
	drop procedure n5pozrecepta_delete
go
if exists (select * from sysobjects where name='n5pozrecepta_maxid')
	drop procedure n5pozrecepta_maxid
go
if exists (select * from sysobjects where name='n5pozrecepta_candel')
	drop procedure n5pozrecepta_candel
go
-- table: n5plchoroba
if exists (select * from sysobjects where name='n5plchoroba_select')
	drop procedure n5plchoroba_select
go
if exists (select * from sysobjects where name='n5plchoroba_insert')
	drop procedure n5plchoroba_insert
go
if exists (select * from sysobjects where name='n5plchoroba_update')
	drop procedure n5plchoroba_update
go
if exists (select * from sysobjects where name='n5plchoroba_delete')
	drop procedure n5plchoroba_delete
go
if exists (select * from sysobjects where name='n5plchoroba_maxid')
	drop procedure n5plchoroba_maxid
go
if exists (select * from sysobjects where name='n5plchoroba_candel')
	drop procedure n5plchoroba_candel
go
-- table: n5plkalcp
if exists (select * from sysobjects where name='n5plkalcp_select')
	drop procedure n5plkalcp_select
go
if exists (select * from sysobjects where name='n5plkalcp_insert')
	drop procedure n5plkalcp_insert
go
if exists (select * from sysobjects where name='n5plkalcp_update')
	drop procedure n5plkalcp_update
go
if exists (select * from sysobjects where name='n5plkalcp_delete')
	drop procedure n5plkalcp_delete
go
if exists (select * from sysobjects where name='n5plkalcp_maxid')
	drop procedure n5plkalcp_maxid
go
if exists (select * from sysobjects where name='n5plkalcp_candel')
	drop procedure n5plkalcp_candel
go
-- table: n5plrcp
if exists (select * from sysobjects where name='n5plrcp_select')
	drop procedure n5plrcp_select
go
if exists (select * from sysobjects where name='n5plrcp_insert')
	drop procedure n5plrcp_insert
go
if exists (select * from sysobjects where name='n5plrcp_update')
	drop procedure n5plrcp_update
go
if exists (select * from sysobjects where name='n5plrcp_delete')
	drop procedure n5plrcp_delete
go
if exists (select * from sysobjects where name='n5plrcp_maxid')
	drop procedure n5plrcp_maxid
go
if exists (select * from sysobjects where name='n5plrcp_candel')
	drop procedure n5plrcp_candel
go
-- table: n5transakcja_operacja
if exists (select * from sysobjects where name='n5transakcja_operacja_select')
	drop procedure n5transakcja_operacja_select
go
if exists (select * from sysobjects where name='n5transakcja_operacja_insert')
	drop procedure n5transakcja_operacja_insert
go
if exists (select * from sysobjects where name='n5transakcja_operacja_update')
	drop procedure n5transakcja_operacja_update
go
if exists (select * from sysobjects where name='n5transakcja_operacja_delete')
	drop procedure n5transakcja_operacja_delete
go
if exists (select * from sysobjects where name='n5transakcja_operacja_maxid')
	drop procedure n5transakcja_operacja_maxid
go
if exists (select * from sysobjects where name='n5transakcja_operacja_candel')
	drop procedure n5transakcja_operacja_candel
go
-- table: n5ankieta_toral
if exists (select * from sysobjects where name='n5ankieta_toral_select')
	drop procedure n5ankieta_toral_select
go
if exists (select * from sysobjects where name='n5ankieta_toral_insert')
	drop procedure n5ankieta_toral_insert
go
if exists (select * from sysobjects where name='n5ankieta_toral_update')
	drop procedure n5ankieta_toral_update
go
if exists (select * from sysobjects where name='n5ankieta_toral_delete')
	drop procedure n5ankieta_toral_delete
go
if exists (select * from sysobjects where name='n5ankieta_toral_maxid')
	drop procedure n5ankieta_toral_maxid
go
if exists (select * from sysobjects where name='n5ankieta_toral_candel')
	drop procedure n5ankieta_toral_candel
go
-- table: n5userprof
if exists (select * from sysobjects where name='n5userprof_select')
	drop procedure n5userprof_select
go
if exists (select * from sysobjects where name='n5userprof_insert')
	drop procedure n5userprof_insert
go
if exists (select * from sysobjects where name='n5userprof_update')
	drop procedure n5userprof_update
go
if exists (select * from sysobjects where name='n5userprof_delete')
	drop procedure n5userprof_delete
go
if exists (select * from sysobjects where name='n5userprof_maxid')
	drop procedure n5userprof_maxid
go
if exists (select * from sysobjects where name='n5userprof_candel')
	drop procedure n5userprof_candel
go
-- table: n5jedn_org
if exists (select * from sysobjects where name='n5jedn_org_select')
	drop procedure n5jedn_org_select
go
if exists (select * from sysobjects where name='n5jedn_org_insert')
	drop procedure n5jedn_org_insert
go
if exists (select * from sysobjects where name='n5jedn_org_update')
	drop procedure n5jedn_org_update
go
if exists (select * from sysobjects where name='n5jedn_org_delete')
	drop procedure n5jedn_org_delete
go
if exists (select * from sysobjects where name='n5jedn_org_maxid')
	drop procedure n5jedn_org_maxid
go
if exists (select * from sysobjects where name='n5jedn_org_candel')
	drop procedure n5jedn_org_candel
go
-- table: n5opakowanie_produktu
if exists (select * from sysobjects where name='n5opakowanie_produktu_select')
	drop procedure n5opakowanie_produktu_select
go
if exists (select * from sysobjects where name='n5opakowanie_produktu_insert')
	drop procedure n5opakowanie_produktu_insert
go
if exists (select * from sysobjects where name='n5opakowanie_produktu_update')
	drop procedure n5opakowanie_produktu_update
go
if exists (select * from sysobjects where name='n5opakowanie_produktu_delete')
	drop procedure n5opakowanie_produktu_delete
go
if exists (select * from sysobjects where name='n5opakowanie_produktu_maxid')
	drop procedure n5opakowanie_produktu_maxid
go
if exists (select * from sysobjects where name='n5opakowanie_produktu_candel')
	drop procedure n5opakowanie_produktu_candel
go
-- table: n5dekret
if exists (select * from sysobjects where name='n5dekret_select')
	drop procedure n5dekret_select
go
if exists (select * from sysobjects where name='n5dekret_insert')
	drop procedure n5dekret_insert
go
if exists (select * from sysobjects where name='n5dekret_update')
	drop procedure n5dekret_update
go
if exists (select * from sysobjects where name='n5dekret_delete')
	drop procedure n5dekret_delete
go
if exists (select * from sysobjects where name='n5dekret_maxid')
	drop procedure n5dekret_maxid
go
if exists (select * from sysobjects where name='n5dekret_candel')
	drop procedure n5dekret_candel
go
-- table: n5sposplat
if exists (select * from sysobjects where name='n5sposplat_select')
	drop procedure n5sposplat_select
go
if exists (select * from sysobjects where name='n5sposplat_insert')
	drop procedure n5sposplat_insert
go
if exists (select * from sysobjects where name='n5sposplat_update')
	drop procedure n5sposplat_update
go
if exists (select * from sysobjects where name='n5sposplat_delete')
	drop procedure n5sposplat_delete
go
if exists (select * from sysobjects where name='n5sposplat_maxid')
	drop procedure n5sposplat_maxid
go
if exists (select * from sysobjects where name='n5sposplat_candel')
	drop procedure n5sposplat_candel
go
-- table: n5pldekret
if exists (select * from sysobjects where name='n5pldekret_select')
	drop procedure n5pldekret_select
go
if exists (select * from sysobjects where name='n5pldekret_insert')
	drop procedure n5pldekret_insert
go
if exists (select * from sysobjects where name='n5pldekret_update')
	drop procedure n5pldekret_update
go
if exists (select * from sysobjects where name='n5pldekret_delete')
	drop procedure n5pldekret_delete
go
if exists (select * from sysobjects where name='n5pldekret_maxid')
	drop procedure n5pldekret_maxid
go
if exists (select * from sysobjects where name='n5pldekret_candel')
	drop procedure n5pldekret_candel
go
-- table: n5notaods
if exists (select * from sysobjects where name='n5notaods_select')
	drop procedure n5notaods_select
go
if exists (select * from sysobjects where name='n5notaods_insert')
	drop procedure n5notaods_insert
go
if exists (select * from sysobjects where name='n5notaods_update')
	drop procedure n5notaods_update
go
if exists (select * from sysobjects where name='n5notaods_delete')
	drop procedure n5notaods_delete
go
if exists (select * from sysobjects where name='n5notaods_maxid')
	drop procedure n5notaods_maxid
go
if exists (select * from sysobjects where name='n5notaods_candel')
	drop procedure n5notaods_candel
go
-- table: n5zadanie_rola
if exists (select * from sysobjects where name='n5zadanie_rola_select')
	drop procedure n5zadanie_rola_select
go
if exists (select * from sysobjects where name='n5zadanie_rola_insert')
	drop procedure n5zadanie_rola_insert
go
if exists (select * from sysobjects where name='n5zadanie_rola_update')
	drop procedure n5zadanie_rola_update
go
if exists (select * from sysobjects where name='n5zadanie_rola_delete')
	drop procedure n5zadanie_rola_delete
go
if exists (select * from sysobjects where name='n5zadanie_rola_maxid')
	drop procedure n5zadanie_rola_maxid
go
if exists (select * from sysobjects where name='n5zadanie_rola_candel')
	drop procedure n5zadanie_rola_candel
go
-- table: n5polecenie_wyjazdu
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_select')
	drop procedure n5polecenie_wyjazdu_select
go
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_insert')
	drop procedure n5polecenie_wyjazdu_insert
go
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_update')
	drop procedure n5polecenie_wyjazdu_update
go
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_delete')
	drop procedure n5polecenie_wyjazdu_delete
go
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_maxid')
	drop procedure n5polecenie_wyjazdu_maxid
go
if exists (select * from sysobjects where name='n5polecenie_wyjazdu_candel')
	drop procedure n5polecenie_wyjazdu_candel
go
-- table: n5dpc
if exists (select * from sysobjects where name='n5dpc_select')
	drop procedure n5dpc_select
go
if exists (select * from sysobjects where name='n5dpc_insert')
	drop procedure n5dpc_insert
go
if exists (select * from sysobjects where name='n5dpc_update')
	drop procedure n5dpc_update
go
if exists (select * from sysobjects where name='n5dpc_delete')
	drop procedure n5dpc_delete
go
if exists (select * from sysobjects where name='n5dpc_maxid')
	drop procedure n5dpc_maxid
go
if exists (select * from sysobjects where name='n5dpc_candel')
	drop procedure n5dpc_candel
go
-- table: n5firma
if exists (select * from sysobjects where name='n5firma_select')
	drop procedure n5firma_select
go
if exists (select * from sysobjects where name='n5firma_insert')
	drop procedure n5firma_insert
go
if exists (select * from sysobjects where name='n5firma_update')
	drop procedure n5firma_update
go
if exists (select * from sysobjects where name='n5firma_delete')
	drop procedure n5firma_delete
go
if exists (select * from sysobjects where name='n5firma_maxid')
	drop procedure n5firma_maxid
go
if exists (select * from sysobjects where name='n5firma_candel')
	drop procedure n5firma_candel
go
-- table: n5WizzardEmail
if exists (select * from sysobjects where name='n5WizzardEmail_select')
	drop procedure n5WizzardEmail_select
go
if exists (select * from sysobjects where name='n5WizzardEmail_insert')
	drop procedure n5WizzardEmail_insert
go
if exists (select * from sysobjects where name='n5WizzardEmail_update')
	drop procedure n5WizzardEmail_update
go
if exists (select * from sysobjects where name='n5WizzardEmail_delete')
	drop procedure n5WizzardEmail_delete
go
if exists (select * from sysobjects where name='n5WizzardEmail_maxid')
	drop procedure n5WizzardEmail_maxid
go
if exists (select * from sysobjects where name='n5WizzardEmail_candel')
	drop procedure n5WizzardEmail_candel
go
-- table: n5pozvatue
if exists (select * from sysobjects where name='n5pozvatue_select')
	drop procedure n5pozvatue_select
go
if exists (select * from sysobjects where name='n5pozvatue_insert')
	drop procedure n5pozvatue_insert
go
if exists (select * from sysobjects where name='n5pozvatue_update')
	drop procedure n5pozvatue_update
go
if exists (select * from sysobjects where name='n5pozvatue_delete')
	drop procedure n5pozvatue_delete
go
if exists (select * from sysobjects where name='n5pozvatue_maxid')
	drop procedure n5pozvatue_maxid
go
if exists (select * from sysobjects where name='n5pozvatue_candel')
	drop procedure n5pozvatue_candel
go
-- table: n5pozdokmag
if exists (select * from sysobjects where name='n5pozdokmag_select')
	drop procedure n5pozdokmag_select
go
if exists (select * from sysobjects where name='n5pozdokmag_insert')
	drop procedure n5pozdokmag_insert
go
if exists (select * from sysobjects where name='n5pozdokmag_update')
	drop procedure n5pozdokmag_update
go
if exists (select * from sysobjects where name='n5pozdokmag_delete')
	drop procedure n5pozdokmag_delete
go
if exists (select * from sysobjects where name='n5pozdokmag_maxid')
	drop procedure n5pozdokmag_maxid
go
if exists (select * from sysobjects where name='n5pozdokmag_candel')
	drop procedure n5pozdokmag_candel
go
-- table: n5grupasrtrw
if exists (select * from sysobjects where name='n5grupasrtrw_select')
	drop procedure n5grupasrtrw_select
go
if exists (select * from sysobjects where name='n5grupasrtrw_insert')
	drop procedure n5grupasrtrw_insert
go
if exists (select * from sysobjects where name='n5grupasrtrw_update')
	drop procedure n5grupasrtrw_update
go
if exists (select * from sysobjects where name='n5grupasrtrw_delete')
	drop procedure n5grupasrtrw_delete
go
if exists (select * from sysobjects where name='n5grupasrtrw_maxid')
	drop procedure n5grupasrtrw_maxid
go
if exists (select * from sysobjects where name='n5grupasrtrw_candel')
	drop procedure n5grupasrtrw_candel
go
-- table: n5plgrzas
if exists (select * from sysobjects where name='n5plgrzas_select')
	drop procedure n5plgrzas_select
go
if exists (select * from sysobjects where name='n5plgrzas_insert')
	drop procedure n5plgrzas_insert
go
if exists (select * from sysobjects where name='n5plgrzas_update')
	drop procedure n5plgrzas_update
go
if exists (select * from sysobjects where name='n5plgrzas_delete')
	drop procedure n5plgrzas_delete
go
if exists (select * from sysobjects where name='n5plgrzas_maxid')
	drop procedure n5plgrzas_maxid
go
if exists (select * from sysobjects where name='n5plgrzas_candel')
	drop procedure n5plgrzas_candel
go
-- table: n5bwinfo_produkt
if exists (select * from sysobjects where name='n5bwinfo_produkt_select')
	drop procedure n5bwinfo_produkt_select
go
if exists (select * from sysobjects where name='n5bwinfo_produkt_insert')
	drop procedure n5bwinfo_produkt_insert
go
if exists (select * from sysobjects where name='n5bwinfo_produkt_update')
	drop procedure n5bwinfo_produkt_update
go
if exists (select * from sysobjects where name='n5bwinfo_produkt_delete')
	drop procedure n5bwinfo_produkt_delete
go
if exists (select * from sysobjects where name='n5bwinfo_produkt_maxid')
	drop procedure n5bwinfo_produkt_maxid
go
if exists (select * from sysobjects where name='n5bwinfo_produkt_candel')
	drop procedure n5bwinfo_produkt_candel
go
-- table: n5rozmiar
if exists (select * from sysobjects where name='n5rozmiar_select')
	drop procedure n5rozmiar_select
go
if exists (select * from sysobjects where name='n5rozmiar_insert')
	drop procedure n5rozmiar_insert
go
if exists (select * from sysobjects where name='n5rozmiar_update')
	drop procedure n5rozmiar_update
go
if exists (select * from sysobjects where name='n5rozmiar_delete')
	drop procedure n5rozmiar_delete
go
if exists (select * from sysobjects where name='n5rozmiar_maxid')
	drop procedure n5rozmiar_maxid
go
if exists (select * from sysobjects where name='n5rozmiar_candel')
	drop procedure n5rozmiar_candel
go
-- table: n5pojazd
if exists (select * from sysobjects where name='n5pojazd_select')
	drop procedure n5pojazd_select
go
if exists (select * from sysobjects where name='n5pojazd_insert')
	drop procedure n5pojazd_insert
go
if exists (select * from sysobjects where name='n5pojazd_update')
	drop procedure n5pojazd_update
go
if exists (select * from sysobjects where name='n5pojazd_delete')
	drop procedure n5pojazd_delete
go
if exists (select * from sysobjects where name='n5pojazd_maxid')
	drop procedure n5pojazd_maxid
go
if exists (select * from sysobjects where name='n5pojazd_candel')
	drop procedure n5pojazd_candel
go
-- table: n5sod
if exists (select * from sysobjects where name='n5sod_select')
	drop procedure n5sod_select
go
if exists (select * from sysobjects where name='n5sod_insert')
	drop procedure n5sod_insert
go
if exists (select * from sysobjects where name='n5sod_update')
	drop procedure n5sod_update
go
if exists (select * from sysobjects where name='n5sod_delete')
	drop procedure n5sod_delete
go
if exists (select * from sysobjects where name='n5sod_maxid')
	drop procedure n5sod_maxid
go
if exists (select * from sysobjects where name='n5sod_candel')
	drop procedure n5sod_candel
go
-- table: n5uzytkownik
if exists (select * from sysobjects where name='n5uzytkownik_select')
	drop procedure n5uzytkownik_select
go
if exists (select * from sysobjects where name='n5uzytkownik_insert')
	drop procedure n5uzytkownik_insert
go
if exists (select * from sysobjects where name='n5uzytkownik_update')
	drop procedure n5uzytkownik_update
go
if exists (select * from sysobjects where name='n5uzytkownik_delete')
	drop procedure n5uzytkownik_delete
go
if exists (select * from sysobjects where name='n5uzytkownik_maxid')
	drop procedure n5uzytkownik_maxid
go
if exists (select * from sysobjects where name='n5uzytkownik_candel')
	drop procedure n5uzytkownik_candel
go
-- table: choicelist
if exists (select * from sysobjects where name='choicelist_select')
	drop procedure choicelist_select
go
if exists (select * from sysobjects where name='choicelist_insert')
	drop procedure choicelist_insert
go
if exists (select * from sysobjects where name='choicelist_update')
	drop procedure choicelist_update
go
if exists (select * from sysobjects where name='choicelist_delete')
	drop procedure choicelist_delete
go
if exists (select * from sysobjects where name='choicelist_maxid')
	drop procedure choicelist_maxid
go
if exists (select * from sysobjects where name='choicelist_candel')
	drop procedure choicelist_candel
go
-- table: n5typinstytucji
if exists (select * from sysobjects where name='n5typinstytucji_select')
	drop procedure n5typinstytucji_select
go
if exists (select * from sysobjects where name='n5typinstytucji_insert')
	drop procedure n5typinstytucji_insert
go
if exists (select * from sysobjects where name='n5typinstytucji_update')
	drop procedure n5typinstytucji_update
go
if exists (select * from sysobjects where name='n5typinstytucji_delete')
	drop procedure n5typinstytucji_delete
go
if exists (select * from sysobjects where name='n5typinstytucji_maxid')
	drop procedure n5typinstytucji_maxid
go
if exists (select * from sysobjects where name='n5typinstytucji_candel')
	drop procedure n5typinstytucji_candel
go
-- table: n5rapkas
if exists (select * from sysobjects where name='n5rapkas_select')
	drop procedure n5rapkas_select
go
if exists (select * from sysobjects where name='n5rapkas_insert')
	drop procedure n5rapkas_insert
go
if exists (select * from sysobjects where name='n5rapkas_update')
	drop procedure n5rapkas_update
go
if exists (select * from sysobjects where name='n5rapkas_delete')
	drop procedure n5rapkas_delete
go
if exists (select * from sysobjects where name='n5rapkas_maxid')
	drop procedure n5rapkas_maxid
go
if exists (select * from sysobjects where name='n5rapkas_candel')
	drop procedure n5rapkas_candel
go
-- table: n5pozzakup
if exists (select * from sysobjects where name='n5pozzakup_select')
	drop procedure n5pozzakup_select
go
if exists (select * from sysobjects where name='n5pozzakup_insert')
	drop procedure n5pozzakup_insert
go
if exists (select * from sysobjects where name='n5pozzakup_update')
	drop procedure n5pozzakup_update
go
if exists (select * from sysobjects where name='n5pozzakup_delete')
	drop procedure n5pozzakup_delete
go
if exists (select * from sysobjects where name='n5pozzakup_maxid')
	drop procedure n5pozzakup_maxid
go
if exists (select * from sysobjects where name='n5pozzakup_candel')
	drop procedure n5pozzakup_candel
go
-- table: n5plnaliczenie
if exists (select * from sysobjects where name='n5plnaliczenie_select')
	drop procedure n5plnaliczenie_select
go
if exists (select * from sysobjects where name='n5plnaliczenie_insert')
	drop procedure n5plnaliczenie_insert
go
if exists (select * from sysobjects where name='n5plnaliczenie_update')
	drop procedure n5plnaliczenie_update
go
if exists (select * from sysobjects where name='n5plnaliczenie_delete')
	drop procedure n5plnaliczenie_delete
go
if exists (select * from sysobjects where name='n5plnaliczenie_maxid')
	drop procedure n5plnaliczenie_maxid
go
if exists (select * from sysobjects where name='n5plnaliczenie_candel')
	drop procedure n5plnaliczenie_candel
go
-- table: n5konto_budzet
if exists (select * from sysobjects where name='n5konto_budzet_select')
	drop procedure n5konto_budzet_select
go
if exists (select * from sysobjects where name='n5konto_budzet_insert')
	drop procedure n5konto_budzet_insert
go
if exists (select * from sysobjects where name='n5konto_budzet_update')
	drop procedure n5konto_budzet_update
go
if exists (select * from sysobjects where name='n5konto_budzet_delete')
	drop procedure n5konto_budzet_delete
go
if exists (select * from sysobjects where name='n5konto_budzet_maxid')
	drop procedure n5konto_budzet_maxid
go
if exists (select * from sysobjects where name='n5konto_budzet_candel')
	drop procedure n5konto_budzet_candel
go
-- table: n5gmstan
if exists (select * from sysobjects where name='n5gmstan_select')
	drop procedure n5gmstan_select
go
if exists (select * from sysobjects where name='n5gmstan_insert')
	drop procedure n5gmstan_insert
go
if exists (select * from sysobjects where name='n5gmstan_update')
	drop procedure n5gmstan_update
go
if exists (select * from sysobjects where name='n5gmstan_delete')
	drop procedure n5gmstan_delete
go
if exists (select * from sysobjects where name='n5gmstan_maxid')
	drop procedure n5gmstan_maxid
go
if exists (select * from sysobjects where name='n5gmstan_candel')
	drop procedure n5gmstan_candel
go
-- table: n5pozprojekt_abas
if exists (select * from sysobjects where name='n5pozprojekt_abas_select')
	drop procedure n5pozprojekt_abas_select
go
if exists (select * from sysobjects where name='n5pozprojekt_abas_insert')
	drop procedure n5pozprojekt_abas_insert
go
if exists (select * from sysobjects where name='n5pozprojekt_abas_update')
	drop procedure n5pozprojekt_abas_update
go
if exists (select * from sysobjects where name='n5pozprojekt_abas_delete')
	drop procedure n5pozprojekt_abas_delete
go
if exists (select * from sysobjects where name='n5pozprojekt_abas_maxid')
	drop procedure n5pozprojekt_abas_maxid
go
if exists (select * from sysobjects where name='n5pozprojekt_abas_candel')
	drop procedure n5pozprojekt_abas_candel
go
-- table: n5paleta_kolorow
if exists (select * from sysobjects where name='n5paleta_kolorow_select')
	drop procedure n5paleta_kolorow_select
go
if exists (select * from sysobjects where name='n5paleta_kolorow_insert')
	drop procedure n5paleta_kolorow_insert
go
if exists (select * from sysobjects where name='n5paleta_kolorow_update')
	drop procedure n5paleta_kolorow_update
go
if exists (select * from sysobjects where name='n5paleta_kolorow_delete')
	drop procedure n5paleta_kolorow_delete
go
if exists (select * from sysobjects where name='n5paleta_kolorow_maxid')
	drop procedure n5paleta_kolorow_maxid
go
if exists (select * from sysobjects where name='n5paleta_kolorow_candel')
	drop procedure n5paleta_kolorow_candel
go
-- table: n5dokstatus
if exists (select * from sysobjects where name='n5dokstatus_select')
	drop procedure n5dokstatus_select
go
if exists (select * from sysobjects where name='n5dokstatus_insert')
	drop procedure n5dokstatus_insert
go
if exists (select * from sysobjects where name='n5dokstatus_update')
	drop procedure n5dokstatus_update
go
if exists (select * from sysobjects where name='n5dokstatus_delete')
	drop procedure n5dokstatus_delete
go
if exists (select * from sysobjects where name='n5dokstatus_maxid')
	drop procedure n5dokstatus_maxid
go
if exists (select * from sysobjects where name='n5dokstatus_candel')
	drop procedure n5dokstatus_candel
go
-- table: n5klient_reprezentacja
if exists (select * from sysobjects where name='n5klient_reprezentacja_select')
	drop procedure n5klient_reprezentacja_select
go
if exists (select * from sysobjects where name='n5klient_reprezentacja_insert')
	drop procedure n5klient_reprezentacja_insert
go
if exists (select * from sysobjects where name='n5klient_reprezentacja_update')
	drop procedure n5klient_reprezentacja_update
go
if exists (select * from sysobjects where name='n5klient_reprezentacja_delete')
	drop procedure n5klient_reprezentacja_delete
go
if exists (select * from sysobjects where name='n5klient_reprezentacja_maxid')
	drop procedure n5klient_reprezentacja_maxid
go
if exists (select * from sysobjects where name='n5klient_reprezentacja_candel')
	drop procedure n5klient_reprezentacja_candel
go
-- table: SearchType
if exists (select * from sysobjects where name='SearchType_select')
	drop procedure SearchType_select
go
if exists (select * from sysobjects where name='SearchType_insert')
	drop procedure SearchType_insert
go
if exists (select * from sysobjects where name='SearchType_update')
	drop procedure SearchType_update
go
if exists (select * from sysobjects where name='SearchType_delete')
	drop procedure SearchType_delete
go
if exists (select * from sysobjects where name='SearchType_maxid')
	drop procedure SearchType_maxid
go
if exists (select * from sysobjects where name='SearchType_candel')
	drop procedure SearchType_candel
go
-- table: n5bank
if exists (select * from sysobjects where name='n5bank_select')
	drop procedure n5bank_select
go
if exists (select * from sysobjects where name='n5bank_insert')
	drop procedure n5bank_insert
go
if exists (select * from sysobjects where name='n5bank_update')
	drop procedure n5bank_update
go
if exists (select * from sysobjects where name='n5bank_delete')
	drop procedure n5bank_delete
go
if exists (select * from sysobjects where name='n5bank_maxid')
	drop procedure n5bank_maxid
go
if exists (select * from sysobjects where name='n5bank_candel')
	drop procedure n5bank_candel
go
-- table: n5pozplatnosc
if exists (select * from sysobjects where name='n5pozplatnosc_select')
	drop procedure n5pozplatnosc_select
go
if exists (select * from sysobjects where name='n5pozplatnosc_insert')
	drop procedure n5pozplatnosc_insert
go
if exists (select * from sysobjects where name='n5pozplatnosc_update')
	drop procedure n5pozplatnosc_update
go
if exists (select * from sysobjects where name='n5pozplatnosc_delete')
	drop procedure n5pozplatnosc_delete
go
if exists (select * from sysobjects where name='n5pozplatnosc_maxid')
	drop procedure n5pozplatnosc_maxid
go
if exists (select * from sysobjects where name='n5pozplatnosc_candel')
	drop procedure n5pozplatnosc_candel
go
-- table: n5pit11
if exists (select * from sysobjects where name='n5pit11_select')
	drop procedure n5pit11_select
go
if exists (select * from sysobjects where name='n5pit11_insert')
	drop procedure n5pit11_insert
go
if exists (select * from sysobjects where name='n5pit11_update')
	drop procedure n5pit11_update
go
if exists (select * from sysobjects where name='n5pit11_delete')
	drop procedure n5pit11_delete
go
if exists (select * from sysobjects where name='n5pit11_maxid')
	drop procedure n5pit11_maxid
go
if exists (select * from sysobjects where name='n5pit11_candel')
	drop procedure n5pit11_candel
go
-- table: n5schematdekr
if exists (select * from sysobjects where name='n5schematdekr_select')
	drop procedure n5schematdekr_select
go
if exists (select * from sysobjects where name='n5schematdekr_insert')
	drop procedure n5schematdekr_insert
go
if exists (select * from sysobjects where name='n5schematdekr_update')
	drop procedure n5schematdekr_update
go
if exists (select * from sysobjects where name='n5schematdekr_delete')
	drop procedure n5schematdekr_delete
go
if exists (select * from sysobjects where name='n5schematdekr_maxid')
	drop procedure n5schematdekr_maxid
go
if exists (select * from sysobjects where name='n5schematdekr_candel')
	drop procedure n5schematdekr_candel
go
-- table: n5zamowienie
if exists (select * from sysobjects where name='n5zamowienie_select')
	drop procedure n5zamowienie_select
go
if exists (select * from sysobjects where name='n5zamowienie_insert')
	drop procedure n5zamowienie_insert
go
if exists (select * from sysobjects where name='n5zamowienie_update')
	drop procedure n5zamowienie_update
go
if exists (select * from sysobjects where name='n5zamowienie_delete')
	drop procedure n5zamowienie_delete
go
if exists (select * from sysobjects where name='n5zamowienie_maxid')
	drop procedure n5zamowienie_maxid
go
if exists (select * from sysobjects where name='n5zamowienie_candel')
	drop procedure n5zamowienie_candel
go
-- table: n5polrab
if exists (select * from sysobjects where name='n5polrab_select')
	drop procedure n5polrab_select
go
if exists (select * from sysobjects where name='n5polrab_insert')
	drop procedure n5polrab_insert
go
if exists (select * from sysobjects where name='n5polrab_update')
	drop procedure n5polrab_update
go
if exists (select * from sysobjects where name='n5polrab_delete')
	drop procedure n5polrab_delete
go
if exists (select * from sysobjects where name='n5polrab_maxid')
	drop procedure n5polrab_maxid
go
if exists (select * from sysobjects where name='n5polrab_candel')
	drop procedure n5polrab_candel
go
-- table: n5realprod
if exists (select * from sysobjects where name='n5realprod_select')
	drop procedure n5realprod_select
go
if exists (select * from sysobjects where name='n5realprod_insert')
	drop procedure n5realprod_insert
go
if exists (select * from sysobjects where name='n5realprod_update')
	drop procedure n5realprod_update
go
if exists (select * from sysobjects where name='n5realprod_delete')
	drop procedure n5realprod_delete
go
if exists (select * from sysobjects where name='n5realprod_maxid')
	drop procedure n5realprod_maxid
go
if exists (select * from sysobjects where name='n5realprod_candel')
	drop procedure n5realprod_candel
go
-- table: n5plterminnal
if exists (select * from sysobjects where name='n5plterminnal_select')
	drop procedure n5plterminnal_select
go
if exists (select * from sysobjects where name='n5plterminnal_insert')
	drop procedure n5plterminnal_insert
go
if exists (select * from sysobjects where name='n5plterminnal_update')
	drop procedure n5plterminnal_update
go
if exists (select * from sysobjects where name='n5plterminnal_delete')
	drop procedure n5plterminnal_delete
go
if exists (select * from sysobjects where name='n5plterminnal_maxid')
	drop procedure n5plterminnal_maxid
go
if exists (select * from sysobjects where name='n5plterminnal_candel')
	drop procedure n5plterminnal_candel
go
-- skipped virtual table: n5pit4r
-- table: n5prop
if exists (select * from sysobjects where name='n5prop_select')
	drop procedure n5prop_select
go
if exists (select * from sysobjects where name='n5prop_insert')
	drop procedure n5prop_insert
go
if exists (select * from sysobjects where name='n5prop_update')
	drop procedure n5prop_update
go
if exists (select * from sysobjects where name='n5prop_delete')
	drop procedure n5prop_delete
go
if exists (select * from sysobjects where name='n5prop_maxid')
	drop procedure n5prop_maxid
go
if exists (select * from sysobjects where name='n5prop_candel')
	drop procedure n5prop_candel
go
-- table: n5pozinwark
if exists (select * from sysobjects where name='n5pozinwark_select')
	drop procedure n5pozinwark_select
go
if exists (select * from sysobjects where name='n5pozinwark_insert')
	drop procedure n5pozinwark_insert
go
if exists (select * from sysobjects where name='n5pozinwark_update')
	drop procedure n5pozinwark_update
go
if exists (select * from sysobjects where name='n5pozinwark_delete')
	drop procedure n5pozinwark_delete
go
if exists (select * from sysobjects where name='n5pozinwark_maxid')
	drop procedure n5pozinwark_maxid
go
if exists (select * from sysobjects where name='n5pozinwark_candel')
	drop procedure n5pozinwark_candel
go
-- table: n5region
if exists (select * from sysobjects where name='n5region_select')
	drop procedure n5region_select
go
if exists (select * from sysobjects where name='n5region_insert')
	drop procedure n5region_insert
go
if exists (select * from sysobjects where name='n5region_update')
	drop procedure n5region_update
go
if exists (select * from sysobjects where name='n5region_delete')
	drop procedure n5region_delete
go
if exists (select * from sysobjects where name='n5region_maxid')
	drop procedure n5region_maxid
go
if exists (select * from sysobjects where name='n5region_candel')
	drop procedure n5region_candel
go
-- table: n5grupaklient
if exists (select * from sysobjects where name='n5grupaklient_select')
	drop procedure n5grupaklient_select
go
if exists (select * from sysobjects where name='n5grupaklient_insert')
	drop procedure n5grupaklient_insert
go
if exists (select * from sysobjects where name='n5grupaklient_update')
	drop procedure n5grupaklient_update
go
if exists (select * from sysobjects where name='n5grupaklient_delete')
	drop procedure n5grupaklient_delete
go
if exists (select * from sysobjects where name='n5grupaklient_maxid')
	drop procedure n5grupaklient_maxid
go
if exists (select * from sysobjects where name='n5grupaklient_candel')
	drop procedure n5grupaklient_candel
go
-- table: n5pit4
if exists (select * from sysobjects where name='n5pit4_select')
	drop procedure n5pit4_select
go
if exists (select * from sysobjects where name='n5pit4_insert')
	drop procedure n5pit4_insert
go
if exists (select * from sysobjects where name='n5pit4_update')
	drop procedure n5pit4_update
go
if exists (select * from sysobjects where name='n5pit4_delete')
	drop procedure n5pit4_delete
go
if exists (select * from sysobjects where name='n5pit4_maxid')
	drop procedure n5pit4_maxid
go
if exists (select * from sysobjects where name='n5pit4_candel')
	drop procedure n5pit4_candel
go
-- table: n5klient_opakowanie
if exists (select * from sysobjects where name='n5klient_opakowanie_select')
	drop procedure n5klient_opakowanie_select
go
if exists (select * from sysobjects where name='n5klient_opakowanie_insert')
	drop procedure n5klient_opakowanie_insert
go
if exists (select * from sysobjects where name='n5klient_opakowanie_update')
	drop procedure n5klient_opakowanie_update
go
if exists (select * from sysobjects where name='n5klient_opakowanie_delete')
	drop procedure n5klient_opakowanie_delete
go
if exists (select * from sysobjects where name='n5klient_opakowanie_maxid')
	drop procedure n5klient_opakowanie_maxid
go
if exists (select * from sysobjects where name='n5klient_opakowanie_candel')
	drop procedure n5klient_opakowanie_candel
go
-- table: n5proglojal
if exists (select * from sysobjects where name='n5proglojal_select')
	drop procedure n5proglojal_select
go
if exists (select * from sysobjects where name='n5proglojal_insert')
	drop procedure n5proglojal_insert
go
if exists (select * from sysobjects where name='n5proglojal_update')
	drop procedure n5proglojal_update
go
if exists (select * from sysobjects where name='n5proglojal_delete')
	drop procedure n5proglojal_delete
go
if exists (select * from sysobjects where name='n5proglojal_maxid')
	drop procedure n5proglojal_maxid
go
if exists (select * from sysobjects where name='n5proglojal_candel')
	drop procedure n5proglojal_candel
go
-- table: n5pozzlecprod
if exists (select * from sysobjects where name='n5pozzlecprod_select')
	drop procedure n5pozzlecprod_select
go
if exists (select * from sysobjects where name='n5pozzlecprod_insert')
	drop procedure n5pozzlecprod_insert
go
if exists (select * from sysobjects where name='n5pozzlecprod_update')
	drop procedure n5pozzlecprod_update
go
if exists (select * from sysobjects where name='n5pozzlecprod_delete')
	drop procedure n5pozzlecprod_delete
go
if exists (select * from sysobjects where name='n5pozzlecprod_maxid')
	drop procedure n5pozzlecprod_maxid
go
if exists (select * from sysobjects where name='n5pozzlecprod_candel')
	drop procedure n5pozzlecprod_candel
go
-- table: n5rozlcit
if exists (select * from sysobjects where name='n5rozlcit_select')
	drop procedure n5rozlcit_select
go
if exists (select * from sysobjects where name='n5rozlcit_insert')
	drop procedure n5rozlcit_insert
go
if exists (select * from sysobjects where name='n5rozlcit_update')
	drop procedure n5rozlcit_update
go
if exists (select * from sysobjects where name='n5rozlcit_delete')
	drop procedure n5rozlcit_delete
go
if exists (select * from sysobjects where name='n5rozlcit_maxid')
	drop procedure n5rozlcit_maxid
go
if exists (select * from sysobjects where name='n5rozlcit_candel')
	drop procedure n5rozlcit_candel
go
-- table: n5plsklwyn
if exists (select * from sysobjects where name='n5plsklwyn_select')
	drop procedure n5plsklwyn_select
go
if exists (select * from sysobjects where name='n5plsklwyn_insert')
	drop procedure n5plsklwyn_insert
go
if exists (select * from sysobjects where name='n5plsklwyn_update')
	drop procedure n5plsklwyn_update
go
if exists (select * from sysobjects where name='n5plsklwyn_delete')
	drop procedure n5plsklwyn_delete
go
if exists (select * from sysobjects where name='n5plsklwyn_maxid')
	drop procedure n5plsklwyn_maxid
go
if exists (select * from sysobjects where name='n5plsklwyn_candel')
	drop procedure n5plsklwyn_candel
go
-- table: n5kodpcn
if exists (select * from sysobjects where name='n5kodpcn_select')
	drop procedure n5kodpcn_select
go
if exists (select * from sysobjects where name='n5kodpcn_insert')
	drop procedure n5kodpcn_insert
go
if exists (select * from sysobjects where name='n5kodpcn_update')
	drop procedure n5kodpcn_update
go
if exists (select * from sysobjects where name='n5kodpcn_delete')
	drop procedure n5kodpcn_delete
go
if exists (select * from sysobjects where name='n5kodpcn_maxid')
	drop procedure n5kodpcn_maxid
go
if exists (select * from sysobjects where name='n5kodpcn_candel')
	drop procedure n5kodpcn_candel
go
-- table: n5typzasobprod
if exists (select * from sysobjects where name='n5typzasobprod_select')
	drop procedure n5typzasobprod_select
go
if exists (select * from sysobjects where name='n5typzasobprod_insert')
	drop procedure n5typzasobprod_insert
go
if exists (select * from sysobjects where name='n5typzasobprod_update')
	drop procedure n5typzasobprod_update
go
if exists (select * from sysobjects where name='n5typzasobprod_delete')
	drop procedure n5typzasobprod_delete
go
if exists (select * from sysobjects where name='n5typzasobprod_maxid')
	drop procedure n5typzasobprod_maxid
go
if exists (select * from sysobjects where name='n5typzasobprod_candel')
	drop procedure n5typzasobprod_candel
go
-- table: n5maszyna_toral
if exists (select * from sysobjects where name='n5maszyna_toral_select')
	drop procedure n5maszyna_toral_select
go
if exists (select * from sysobjects where name='n5maszyna_toral_insert')
	drop procedure n5maszyna_toral_insert
go
if exists (select * from sysobjects where name='n5maszyna_toral_update')
	drop procedure n5maszyna_toral_update
go
if exists (select * from sysobjects where name='n5maszyna_toral_delete')
	drop procedure n5maszyna_toral_delete
go
if exists (select * from sysobjects where name='n5maszyna_toral_maxid')
	drop procedure n5maszyna_toral_maxid
go
if exists (select * from sysobjects where name='n5maszyna_toral_candel')
	drop procedure n5maszyna_toral_candel
go
--========= dropping vlist_ views =========
if exists (select * from sysobjects where name='vlist_n5doketyk_doet_listPozycje')
	drop view vlist_n5doketyk_doet_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5sprzedaz_listPozycje')
	drop view vlist_n5sprzedaz_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5sprzedaz_sprzed_listRata')
	drop view vlist_n5sprzedaz_sprzed_listRata
go
if exists (select * from sysobjects where name='vlist_n5sprzedaz_sprzed_listZalacznik')
	drop view vlist_n5sprzedaz_sprzed_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5pracownik_prac_listStanowisko')
	drop view vlist_n5pracownik_prac_listStanowisko
go
if exists (select * from sysobjects where name='vlist_n5vatue_vtue_listWDT')
	drop view vlist_n5vatue_vtue_listWDT
go
if exists (select * from sysobjects where name='vlist_n5vatue_vtue_listWNT')
	drop view vlist_n5vatue_vtue_listWNT
go
if exists (select * from sysobjects where name='vlist_n5vatue_vtue_listWSU')
	drop view vlist_n5vatue_vtue_listWSU
go
if exists (select * from sysobjects where name='vlist_n5vatue_vtue_listPTPM')
	drop view vlist_n5vatue_vtue_listPTPM
go
if exists (select * from sysobjects where name='vlist_n5bwinfo_listProdukt')
	drop view vlist_n5bwinfo_listProdukt
go
if exists (select * from sysobjects where name='vlist_n5bwinfo_listObjawyZal')
	drop view vlist_n5bwinfo_listObjawyZal
go
if exists (select * from sysobjects where name='vlist_n5bwinfo_listRozwiazanieZal')
	drop view vlist_n5bwinfo_listRozwiazanieZal
go
if exists (select * from sysobjects where name='vlist_n5bwinfo_listUwagiZal')
	drop view vlist_n5bwinfo_listUwagiZal
go
if exists (select * from sysobjects where name='vlist_n5projekt_abas_proj_listPozycje')
	drop view vlist_n5projekt_abas_proj_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5inwark_ia_listPozycje')
	drop view vlist_n5inwark_ia_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5dokument_listLinks')
	drop view vlist_n5dokument_listLinks
go
if exists (select * from sysobjects where name='vlist_n5dokument_dok_listPozDokProd')
	drop view vlist_n5dokument_dok_listPozDokProd
go
if exists (select * from sysobjects where name='vlist_n5klient_produkt_klpr_listOpakowania')
	drop view vlist_n5klient_produkt_klpr_listOpakowania
go
if exists (select * from sysobjects where name='vlist_n5recepta_listWyrob')
	drop view vlist_n5recepta_listWyrob
go
if exists (select * from sysobjects where name='vlist_n5recepta_listSurowce')
	drop view vlist_n5recepta_listSurowce
go
if exists (select * from sysobjects where name='vlist_n5recepta_listCzynnosci')
	drop view vlist_n5recepta_listCzynnosci
go
if exists (select * from sysobjects where name='vlist_n5recepta_rcpt_listZasob')
	drop view vlist_n5recepta_rcpt_listZasob
go
if exists (select * from sysobjects where name='vlist_n5recepta_rcpt_listOper')
	drop view vlist_n5recepta_rcpt_listOper
go
if exists (select * from sysobjects where name='vlist_n5plnieob_listSkladnik')
	drop view vlist_n5plnieob_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5produkt_listOpakowania')
	drop view vlist_n5produkt_listOpakowania
go
if exists (select * from sysobjects where name='vlist_n5dowodksieg_listDekret')
	drop view vlist_n5dowodksieg_listDekret
go
if exists (select * from sysobjects where name='vlist_n5plumowa_listSkladnik')
	drop view vlist_n5plumowa_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5SendEmail_listDokumenty')
	drop view vlist_n5SendEmail_listDokumenty
go
if exists (select * from sysobjects where name='vlist_n5rejestrdok_rejdok_listMagazyn')
	drop view vlist_n5rejestrdok_rejdok_listMagazyn
go
if exists (select * from sysobjects where name='vlist_n5dokmag_listPozycje')
	drop view vlist_n5dokmag_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5dokmag_dm_listEgzemplarze')
	drop view vlist_n5dokmag_dm_listEgzemplarze
go
if exists (select * from sysobjects where name='vlist_n5dokmag_zak_listZalacznik')
	drop view vlist_n5dokmag_zak_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5klient_kli_listReprezentacja')
	drop view vlist_n5klient_kli_listReprezentacja
go
if exists (select * from sysobjects where name='vlist_n5zakup_listPozycje')
	drop view vlist_n5zakup_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5zakup_zak_listRata')
	drop view vlist_n5zakup_zak_listRata
go
if exists (select * from sysobjects where name='vlist_n5zakup_zak_listZalacznik')
	drop view vlist_n5zakup_zak_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5istat_istt_pozistat')
	drop view vlist_n5istat_istt_pozistat
go
if exists (select * from sysobjects where name='vlist_n5protokol_abas_prot_listPozycje')
	drop view vlist_n5protokol_abas_prot_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5wykonawca_wyk_listRole')
	drop view vlist_n5wykonawca_wyk_listRole
go
if exists (select * from sysobjects where name='vlist_n5plschematnal_listSkladnik')
	drop view vlist_n5plschematnal_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5zadanie_listZalaczniki')
	drop view vlist_n5zadanie_listZalaczniki
go
if exists (select * from sysobjects where name='vlist_n5zadanie_zad_listRole')
	drop view vlist_n5zadanie_zad_listRole
go
if exists (select * from sysobjects where name='vlist_n5zlecprod_listPozycje')
	drop view vlist_n5zlecprod_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5plpozostale_listSkladnik')
	drop view vlist_n5plpozostale_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5platnosc_listPozycje')
	drop view vlist_n5platnosc_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5platnosc_zak_listZalacznik')
	drop view vlist_n5platnosc_zak_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5plchoroba_listSkladnik')
	drop view vlist_n5plchoroba_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5plkalcp_listPozycje')
	drop view vlist_n5plkalcp_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5ankieta_toral_ank_listPozycje')
	drop view vlist_n5ankieta_toral_ank_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5notaods_listPozycje')
	drop view vlist_n5notaods_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5polecenie_wyjazdu_pws_listPozycje')
	drop view vlist_n5polecenie_wyjazdu_pws_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5polecenie_wyjazdu_pws_listZalacznik')
	drop view vlist_n5polecenie_wyjazdu_pws_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5WizzardEmail_listDokumenty')
	drop view vlist_n5WizzardEmail_listDokumenty
go
if exists (select * from sysobjects where name='vlist_choicelist_listElement')
	drop view vlist_choicelist_listElement
go
if exists (select * from sysobjects where name='vlist_n5plnaliczenie_listSkladnik')
	drop view vlist_n5plnaliczenie_listSkladnik
go
if exists (select * from sysobjects where name='vlist_n5plnaliczenie_listDekret')
	drop view vlist_n5plnaliczenie_listDekret
go
if exists (select * from sysobjects where name='vlist_SearchType_listFilter')
	drop view vlist_SearchType_listFilter
go
if exists (select * from sysobjects where name='vlist_SearchType_listOrder')
	drop view vlist_SearchType_listOrder
go
if exists (select * from sysobjects where name='vlist_SearchType_listColumn')
	drop view vlist_SearchType_listColumn
go
if exists (select * from sysobjects where name='vlist_n5zamowienie_listPozycje')
	drop view vlist_n5zamowienie_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5zamowienie_zam_listRata')
	drop view vlist_n5zamowienie_zam_listRata
go
if exists (select * from sysobjects where name='vlist_n5zamowienie_zam_listZalacznik')
	drop view vlist_n5zamowienie_zam_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5realprod_listWyrob')
	drop view vlist_n5realprod_listWyrob
go
if exists (select * from sysobjects where name='vlist_n5realprod_listCzynnosc')
	drop view vlist_n5realprod_listCzynnosc
go
if exists (select * from sysobjects where name='vlist_n5realprod_listPozycje')
	drop view vlist_n5realprod_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5realprod_realprod_listEgzemplarzeWyroby')
	drop view vlist_n5realprod_realprod_listEgzemplarzeWyroby
go
if exists (select * from sysobjects where name='vlist_n5realprod_realprod_listEgzemplarzeSurowce')
	drop view vlist_n5realprod_realprod_listEgzemplarzeSurowce
go
if exists (select * from sysobjects where name='vlist_n5realprod_zak_listZalacznik')
	drop view vlist_n5realprod_zak_listZalacznik
go
if exists (select * from sysobjects where name='vlist_n5realprod_realprod_listZasoby')
	drop view vlist_n5realprod_realprod_listZasoby
go
--========= dropping indices (UQ) =========

if exists (select * from sysindexes where name='UQ_n5typdokumentu_strNazwa')
	drop index n5typdokumentu.UQ_n5typdokumentu_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5klient_obiekt_klob_strIndeks')
	drop index n5klient_obiekt.UQ_n5klient_obiekt_klob_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5globprof_Indeks')
	drop index n5globprof.UQ_n5globprof_Indeks
go

if exists (select * from sysindexes where name='UQ_n5sprzedaz_strNrDok')
	drop index n5sprzedaz.UQ_n5sprzedaz_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5konto_strSymbol')
	drop index n5konto.UQ_n5konto_strSymbol
go

if exists (select * from sysindexes where name='UQ_n5rola_prior_rolap_strNazwa')
	drop index n5rola_prior.UQ_n5rola_prior_rolap_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5pracownik_prac_strIndeks')
	drop index n5pracownik.UQ_n5pracownik_prac_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5magazyn_strNazwa')
	drop index n5magazyn.UQ_n5magazyn_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5pllistaplac_strNrDok')
	drop index n5pllistaplac.UQ_n5pllistaplac_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5bwinfo_strNrInfo')
	drop index n5bwinfo.UQ_n5bwinfo_strNrInfo
go

if exists (select * from sysindexes where name='UQ_n5tabela_rozmiarow_crz_strNazwa')
	drop index n5tabela_rozmiarow.UQ_n5tabela_rozmiarow_crz_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5sodgroup_strNazwa')
	drop index n5sodgroup.UQ_n5sodgroup_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5licencja_strKod')
	drop index n5licencja.UQ_n5licencja_strKod
go

if exists (select * from sysindexes where name='UQ_n5gmina_gmi_strNazwa')
	drop index n5gmina.UQ_n5gmina_gmi_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5branza_strNazwa')
	drop index n5branza.UQ_n5branza_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5kraj_strSkrot')
	drop index n5kraj.UQ_n5kraj_strSkrot
go

if exists (select * from sysindexes where name='UQ_n5procedura_strNazwa')
	drop index n5procedura.UQ_n5procedura_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5plgrupaschemnal_strNazwa')
	drop index n5plgrupaschemnal.UQ_n5plgrupaschemnal_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5inwark_strNrDok')
	drop index n5inwark.UQ_n5inwark_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5wojewodztwo_strNazwa')
	drop index n5wojewodztwo.UQ_n5wojewodztwo_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5dokument_strNumDok')
	drop index n5dokument.UQ_n5dokument_strNumDok
go

if exists (select * from sysindexes where name='UQ_n5recepta_strNazwa')
	drop index n5recepta.UQ_n5recepta_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5pltyppracy_tpr_strKod')
	drop index n5pltyppracy.UQ_n5pltyppracy_tpr_strKod
go

if exists (select * from sysindexes where name='UQ_n5zasobprod_zsp_strNazwa')
	drop index n5zasobprod.UQ_n5zasobprod_zsp_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5zasobprod_zsp_strIndeks')
	drop index n5zasobprod.UQ_n5zasobprod_zsp_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5globfile_nIndeks')
	drop index n5globfile.UQ_n5globfile_nIndeks
go

if exists (select * from sysindexes where name='UQ_n5produkt_strIndeks')
	drop index n5produkt.UQ_n5produkt_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5dowodksieg_strNrDok')
	drop index n5dowodksieg.UQ_n5dowodksieg_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5miejscowosc_strNazwa')
	drop index n5miejscowosc.UQ_n5miejscowosc_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5rejestrdok_strNazwa')
	drop index n5rejestrdok.UQ_n5rejestrdok_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5dokmag_strNrDok')
	drop index n5dokmag.UQ_n5dokmag_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5dokmag_nNumOper')
	drop index n5dokmag.UQ_n5dokmag_nNumOper
go

if exists (select * from sysindexes where name='UQ_n5srtrw_strNumEwid')
	drop index n5srtrw.UQ_n5srtrw_strNumEwid
go

if exists (select * from sysindexes where name='UQ_n5srtrw_srtrw_strIndeks')
	drop index n5srtrw.UQ_n5srtrw_srtrw_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5plsubkonto_strNazwa')
	drop index n5plsubkonto.UQ_n5plsubkonto_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5plsubkonto_strKod')
	drop index n5plsubkonto.UQ_n5plsubkonto_strKod
go

if exists (select * from sysindexes where name='UQ_n5rola_rola_strNazwa')
	drop index n5rola.UQ_n5rola_rola_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5rola_rola_strSygnatura')
	drop index n5rola.UQ_n5rola_rola_strSygnatura
go

if exists (select * from sysindexes where name='UQ_n5klient_strIndeks')
	drop index n5klient.UQ_n5klient_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5analfinans_strNazwa')
	drop index n5analfinans.UQ_n5analfinans_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5sposdost_sposdost_strNazwa')
	drop index n5sposdost.UQ_n5sposdost_sposdost_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5zakup_strNrDok')
	drop index n5zakup.UQ_n5zakup_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5wykonawca_strIndeks')
	drop index n5wykonawca.UQ_n5wykonawca_strIndeks
go

if exists (select * from sysindexes where name='UQ_n5powiat_pow_strNazwa')
	drop index n5powiat.UQ_n5powiat_pow_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5plschematnal_strKod')
	drop index n5plschematnal.UQ_n5plschematnal_strKod
go

if exists (select * from sysindexes where name='UQ_n5kwalifikator_strNazwa')
	drop index n5kwalifikator.UQ_n5kwalifikator_strNazwa
go

-- skipped virtual table: n5vatuek
if exists (select * from sysindexes where name='UQ_n5jednostka_strSkrot')
	drop index n5jednostka.UQ_n5jednostka_strSkrot
go

if exists (select * from sysindexes where name='UQ_n5typdzialania_strNazwa')
	drop index n5typdzialania.UQ_n5typdzialania_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5zlecprod_strNrDok')
	drop index n5zlecprod.UQ_n5zlecprod_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5inwmag_strNrDok')
	drop index n5inwmag.UQ_n5inwmag_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5grupaproduktow_strNazwa')
	drop index n5grupaproduktow.UQ_n5grupaproduktow_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5platnosc_strNrDok')
	drop index n5platnosc.UQ_n5platnosc_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5plkalcp_strNazwa')
	drop index n5plkalcp.UQ_n5plkalcp_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5jedn_org_strNazwa')
	drop index n5jedn_org.UQ_n5jedn_org_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5sposplat_strNazwa')
	drop index n5sposplat.UQ_n5sposplat_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5notaods_strNrDok')
	drop index n5notaods.UQ_n5notaods_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5polecenie_wyjazdu_pws_strNrDok')
	drop index n5polecenie_wyjazdu.UQ_n5polecenie_wyjazdu_pws_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5grupasrtrw_strNazwa')
	drop index n5grupasrtrw.UQ_n5grupasrtrw_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5plgrzas_strNazwa')
	drop index n5plgrzas.UQ_n5plgrzas_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5uzytkownik_strNazwa')
	drop index n5uzytkownik.UQ_n5uzytkownik_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5uzytkownik_strLogin')
	drop index n5uzytkownik.UQ_n5uzytkownik_strLogin
go

if exists (select * from sysindexes where name='UQ_n5typinstytucji_strNazwa')
	drop index n5typinstytucji.UQ_n5typinstytucji_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5rapkas_raka_strNrDok')
	drop index n5rapkas.UQ_n5rapkas_raka_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5paleta_kolorow_pkol_strNazwa')
	drop index n5paleta_kolorow.UQ_n5paleta_kolorow_pkol_strNazwa
go

if exists (select * from sysindexes where name='UQ_SearchType_Nazwa')
	drop index SearchType.UQ_SearchType_Nazwa
go

if exists (select * from sysindexes where name='UQ_n5zamowienie_strNrDok')
	drop index n5zamowienie.UQ_n5zamowienie_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5realprod_strNrDok')
	drop index n5realprod.UQ_n5realprod_strNrDok
go

if exists (select * from sysindexes where name='UQ_n5realprod_nNumOper')
	drop index n5realprod.UQ_n5realprod_nNumOper
go

if exists (select * from sysindexes where name='UQ_n5plterminnal_strNazwa')
	drop index n5plterminnal.UQ_n5plterminnal_strNazwa
go

-- skipped virtual table: n5pit4r
if exists (select * from sysindexes where name='UQ_n5region_strNazwa')
	drop index n5region.UQ_n5region_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5grupaklient_strNazwa')
	drop index n5grupaklient.UQ_n5grupaklient_strNazwa
go

if exists (select * from sysindexes where name='UQ_n5kodpcn_pcn_strKod')
	drop index n5kodpcn.UQ_n5kodpcn_pcn_strKod
go

if exists (select * from sysindexes where name='UQ_n5typzasobprod_tzp_strNazwa')
	drop index n5typzasobprod.UQ_n5typzasobprod_tzp_strNazwa
go

--========= dropping indices (FKI) =========

if exists (select * from sysindexes where name='FKI_n5userfile_pUzytkownik')
	drop index n5userfile.FKI_n5userfile_pUzytkownik
go

if exists (select * from sysindexes where name='FKI_n5typdokumentu_pTypNadrzedny')
	drop index n5typdokumentu.FKI_n5typdokumentu_pTypNadrzedny
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pProdukt')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pOpak')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pKwalifikatorEx')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_psprzed_pZadanie')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_psprzed_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_psprzed_pKLOB')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_psprzed_pKLOB
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pProduktOrg')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pProduktOrg
go

if exists (select * from sysindexes where name='FKI_n5pozsprzedaz_pOpakOrg')
	drop index n5pozsprzedaz.FKI_n5pozsprzedaz_pOpakOrg
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pProdukt')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pOpak')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pOpak
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pMagazyn')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pKlient')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pKlient
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pKlientJO')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pKlientJO
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pKlientPracownik')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5egzemplarz_egze_pKlientObiekt')
	drop index n5egzemplarz.FKI_n5egzemplarz_egze_pKlientObiekt
go

if exists (select * from sysindexes where name='FKI_n5doketyk_doet_pUzytRej')
	drop index n5doketyk.FKI_n5doketyk_doet_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5doketyk_doet_pJednOrg')
	drop index n5doketyk.FKI_n5doketyk_doet_pJednOrg
go

if exists (select * from sysindexes where name='FKI_n5doketyk_doet_pKwalifikatorEx')
	drop index n5doketyk.FKI_n5doketyk_doet_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5doketyk_doet_pDokMag')
	drop index n5doketyk.FKI_n5doketyk_doet_pDokMag
go

if exists (select * from sysindexes where name='FKI_n5doketyk_doet_pUzytModyf')
	drop index n5doketyk.FKI_n5doketyk_doet_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pKlient')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pKlient
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pKlientJO')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pKlientJO
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pKlientPracownik')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pMiejscowosc')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pKraj')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pKraj
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pPracownik')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_pKwalifikatorEx')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pProdukt')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5klient_obiekt_klob_pOpak')
	drop index n5klient_obiekt.FKI_n5klient_obiekt_klob_pOpak
go

if exists (select * from sysindexes where name='FKI_n5ptstan_gms_pProd')
	drop index n5ptstan.FKI_n5ptstan_gms_pProd
go

if exists (select * from sysindexes where name='FKI_n5ptstan_gms_pOpak')
	drop index n5ptstan.FKI_n5ptstan_gms_pOpak
go

if exists (select * from sysindexes where name='FKI_n5ptstan_gms_pMag')
	drop index n5ptstan.FKI_n5ptstan_gms_pMag
go

if exists (select * from sysindexes where name='FKI_n5srodek_lok_slok_pStawka')
	drop index n5srodek_lok.FKI_n5srodek_lok_slok_pStawka
go

if exists (select * from sysindexes where name='FKI_n5srodek_lok_slok_pKwalifikatorEx')
	drop index n5srodek_lok.FKI_n5srodek_lok_slok_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pKlient')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pKlient
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pJednOrgKlienta')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pJednOrgKlienta
go

if exists (select * from sysindexes where name='FKI_n5klient_pracownik_pPracownik')
	drop index n5klient_pracownik.FKI_n5klient_pracownik_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pSposobPlatnosci')
	drop index n5sprzedaz.FKI_n5sprzedaz_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlient')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlient
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlient_JO')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlient_JO
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKlientPracownik')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pUzytRej')
	drop index n5sprzedaz.FKI_n5sprzedaz_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pZadanie')
	drop index n5sprzedaz.FKI_n5sprzedaz_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pRejestrDok')
	drop index n5sprzedaz.FKI_n5sprzedaz_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pDowodKsieg')
	drop index n5sprzedaz.FKI_n5sprzedaz_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pSchematDekr')
	drop index n5sprzedaz.FKI_n5sprzedaz_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pTransakcja')
	drop index n5sprzedaz.FKI_n5sprzedaz_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pPopSprzed')
	drop index n5sprzedaz.FKI_n5sprzedaz_pPopSprzed
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pFaktura')
	drop index n5sprzedaz.FKI_n5sprzedaz_pFaktura
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pWaluta')
	drop index n5sprzedaz.FKI_n5sprzedaz_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pRozlVat')
	drop index n5sprzedaz.FKI_n5sprzedaz_pRozlVat
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pZamowienie')
	drop index n5sprzedaz.FKI_n5sprzedaz_pZamowienie
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pKwalifikatorEx')
	drop index n5sprzedaz.FKI_n5sprzedaz_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pPKPIR')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pSposobDostawy')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pSposobDostawy
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pHandlowiec')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pHandlowiec
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pUzytModyf')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_pDokStatus')
	drop index n5sprzedaz.FKI_n5sprzedaz_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pDostawa')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pDostawa
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pMiejscowosc_dost')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pMiejscowosc_dost
go

if exists (select * from sysindexes where name='FKI_n5sprzedaz_sprzed_pKraj_dost')
	drop index n5sprzedaz.FKI_n5sprzedaz_sprzed_pKraj_dost
go

if exists (select * from sysindexes where name='FKI_n5konto_pJednostka')
	drop index n5konto.FKI_n5konto_pJednostka
go

if exists (select * from sysindexes where name='WFKI_n5konto_wrefPodmiotRozrach')
	drop index n5konto.WFKI_n5konto_wrefPodmiotRozrach
go

if exists (select * from sysindexes where name='FKI_n5konto_pKontoNadrz')
	drop index n5konto.FKI_n5konto_pKontoNadrz
go

if exists (select * from sysindexes where name='FKI_n5zadaniedw_pWykonawcaDW')
	drop index n5zadaniedw.FKI_n5zadaniedw_pWykonawcaDW
go

if exists (select * from sysindexes where name='FKI_n5poznotaods_pTransakcja')
	drop index n5poznotaods.FKI_n5poznotaods_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5poz_hist_stan_pstn_pStanowisko')
	drop index n5poz_hist_stan.FKI_n5poz_hist_stan_pstn_pStanowisko
go

if exists (select * from sysindexes where name='FKI_n5poz_hist_stan_pstn_pKwalifikatorEx')
	drop index n5poz_hist_stan.FKI_n5poz_hist_stan_pstn_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pMiejscowosc')
	drop index n5pracownik.FKI_n5pracownik_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pKraj')
	drop index n5pracownik.FKI_n5pracownik_pKraj
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pBank1')
	drop index n5pracownik.FKI_n5pracownik_pBank1
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pJednostkaOrg')
	drop index n5pracownik.FKI_n5pracownik_pJednostkaOrg
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pUrzadSkarbowy')
	drop index n5pracownik.FKI_n5pracownik_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pprac_Miejscowosc_zameld')
	drop index n5pracownik.FKI_n5pracownik_pprac_Miejscowosc_zameld
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pprac_Kraj_zameld')
	drop index n5pracownik.FKI_n5pracownik_pprac_Kraj_zameld
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pprac_Miejscowosc_koresp')
	drop index n5pracownik.FKI_n5pracownik_pprac_Miejscowosc_koresp
go

if exists (select * from sysindexes where name='FKI_n5pracownik_pprac_Kraj_koresp')
	drop index n5pracownik.FKI_n5pracownik_pprac_Kraj_koresp
go

if exists (select * from sysindexes where name='FKI_n5WizzardEmailDokumElem_pDokument')
	drop index n5WizzardEmailDokumElem.FKI_n5WizzardEmailDokumElem_pDokument
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pUrzadSkarbowy')
	drop index n5vatue.FKI_n5vatue_vtue_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pUzytRej')
	drop index n5vatue.FKI_n5vatue_vtue_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pZadanie')
	drop index n5vatue.FKI_n5vatue_vtue_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pSchematDekr')
	drop index n5vatue.FKI_n5vatue_vtue_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pDowKsieg')
	drop index n5vatue.FKI_n5vatue_vtue_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pTransakcja')
	drop index n5vatue.FKI_n5vatue_vtue_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5vatue_vtue_pUzytModyf')
	drop index n5vatue.FKI_n5vatue_vtue_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5magazyn_pWaluta')
	drop index n5magazyn.FKI_n5magazyn_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5magazyn_pJednostkaOrg')
	drop index n5magazyn.FKI_n5magazyn_pJednostkaOrg
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pUrzadSkarbowy')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pUzytRej')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pZadanie')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pSchematDekr')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pDowKsieg')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pTransakcja')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5rozlvat_vat7_pUzytModyf')
	drop index n5rozlvat.FKI_n5rozlvat_vat7_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5pllistaplac_lppl_pRejestrDok')
	drop index n5pllistaplac.FKI_n5pllistaplac_lppl_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5pllistaplac_lppl_pDowodKsieg')
	drop index n5pllistaplac.FKI_n5pllistaplac_lppl_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5pllistaplac_lppl_pSchematDekr')
	drop index n5pllistaplac.FKI_n5pllistaplac_lppl_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_pKategoria')
	drop index n5bwinfo.FKI_n5bwinfo_pKategoria
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_pUzytRej')
	drop index n5bwinfo.FKI_n5bwinfo_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_bwi_pUzytModyf')
	drop index n5bwinfo.FKI_n5bwinfo_bwi_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5pozistat_pistt_pProdukt')
	drop index n5pozistat.FKI_n5pozistat_pistt_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozistat_pistt_pOpak')
	drop index n5pozistat.FKI_n5pozistat_pistt_pOpak
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pProdukt')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pOpakowanie')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pOpakowanie
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pMagazyn')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta1')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta1
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta2')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta2
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta3')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta3
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta4')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta4
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta5')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta5
go

if exists (select * from sysindexes where name='FKI_n5produkt_magazyn_prmg_pWaluta6')
	drop index n5produkt_magazyn.FKI_n5produkt_magazyn_prmg_pWaluta6
go

if exists (select * from sysindexes where name='FKI_n5sodgroup_pSODGroup')
	drop index n5sodgroup.FKI_n5sodgroup_pSODGroup
go

if exists (select * from sysindexes where name='FKI_n5gmina_gmi_pWojewodztwo')
	drop index n5gmina.FKI_n5gmina_gmi_pWojewodztwo
go

if exists (select * from sysindexes where name='FKI_n5gmina_gmi_pPowiat')
	drop index n5gmina.FKI_n5gmina_gmi_pPowiat
go

if exists (select * from sysindexes where name='FKI_n5branza_pBranzaNad')
	drop index n5branza.FKI_n5branza_pBranzaNad
go

if exists (select * from sysindexes where name='FKI_n5plstawka_pJednostka')
	drop index n5plstawka.FKI_n5plstawka_pJednostka
go

if exists (select * from sysindexes where name='FKI_n5gmop_gmo_pProd')
	drop index n5gmop.FKI_n5gmop_gmo_pProd
go

if exists (select * from sysindexes where name='FKI_n5gmop_gmo_pOpak')
	drop index n5gmop.FKI_n5gmop_gmo_pOpak
go

if exists (select * from sysindexes where name='FKI_n5gmop_gmo_pMag')
	drop index n5gmop.FKI_n5gmop_gmo_pMag
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pMiejscowosc')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKraj')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKraj
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pWaluta')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pPracownik')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKlient')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKlient
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKlient_JO')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKlient_JO
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKlientPracTech')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKlientPracTech
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKlientPracFin')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKlientPracFin
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pZamowienie')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pZamowienie
go

if exists (select * from sysindexes where name='FKI_n5projekt_abas_proj_pKwalifikatorEx')
	drop index n5projekt_abas.FKI_n5projekt_abas_proj_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozdok_zalacznik_pdza_pDokument')
	drop index n5pozdok_zalacznik.FKI_n5pozdok_zalacznik_pdza_pDokument
go

if exists (select * from sysindexes where name='FKI_n5klient_grupaprod_klgpr_pKlient')
	drop index n5klient_grupaprod.FKI_n5klient_grupaprod_klgpr_pKlient
go

if exists (select * from sysindexes where name='FKI_n5klient_grupaprod_klgpr_pGrupaProd')
	drop index n5klient_grupaprod.FKI_n5klient_grupaprod_klgpr_pGrupaProd
go

if exists (select * from sysindexes where name='FKI_n5kraj_pWaluta')
	drop index n5kraj.FKI_n5kraj_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pUrzadSkarbowy')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pUzytRej')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pZadanie')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pSchematDekr')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pDowKsieg')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pTransakcja')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pit5l_pt5l_pUzytModyf')
	drop index n5pit5l.FKI_n5pit5l_pt5l_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5transakcja_pWaluta')
	drop index n5transakcja.FKI_n5transakcja_pWaluta
go

if exists (select * from sysindexes where name='WFKI_n5transakcja_wrefPodmiot')
	drop index n5transakcja.WFKI_n5transakcja_wrefPodmiot
go

if exists (select * from sysindexes where name='FKI_n5transakcja_pNotaOds')
	drop index n5transakcja.FKI_n5transakcja_pNotaOds
go

if exists (select * from sysindexes where name='FKI_n5transakcja_trn_pHandlowiec')
	drop index n5transakcja.FKI_n5transakcja_trn_pHandlowiec
go

if exists (select * from sysindexes where name='FKI_n5eventlog_pUser')
	drop index n5eventlog.FKI_n5eventlog_pUser
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pProdukt')
	drop index n5pozrealprod.FKI_n5pozrealprod_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pOpak')
	drop index n5pozrealprod.FKI_n5pozrealprod_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pMagazyn')
	drop index n5pozrealprod.FKI_n5pozrealprod_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pJednOpak')
	drop index n5pozrealprod.FKI_n5pozrealprod_pJednOpak
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pJednEwid')
	drop index n5pozrealprod.FKI_n5pozrealprod_pJednEwid
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pKwalifikatorEx')
	drop index n5pozrealprod.FKI_n5pozrealprod_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozrealprod_pozreal_pRecepta')
	drop index n5pozrealprod.FKI_n5pozrealprod_pozreal_pRecepta
go

if exists (select * from sysindexes where name='FKI_n5plgrupaschemnal_pGrupaNadrzedna')
	drop index n5plgrupaschemnal.FKI_n5plgrupaschemnal_pGrupaNadrzedna
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_oper_pro_pRecepta')
	drop index n5pozrecepta_oper.FKI_n5pozrecepta_oper_pro_pRecepta
go

if exists (select * from sysindexes where name='FKI_n5inwark_ia_pInwentaryzacja')
	drop index n5inwark.FKI_n5inwark_ia_pInwentaryzacja
go

if exists (select * from sysindexes where name='FKI_n5inwark_ia_pKwalifikatorEx')
	drop index n5inwark.FKI_n5inwark_ia_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5wojewodztwo_pKraj')
	drop index n5wojewodztwo.FKI_n5wojewodztwo_pKraj
go

if exists (select * from sysindexes where name='FKI_n5dokument_pTypDokumentu')
	drop index n5dokument.FKI_n5dokument_pTypDokumentu
go

if exists (select * from sysindexes where name='WFKI_n5dokument_wpNadawca')
	drop index n5dokument.WFKI_n5dokument_wpNadawca
go

if exists (select * from sysindexes where name='WFKI_n5dokument_wpAdresat')
	drop index n5dokument.WFKI_n5dokument_wpAdresat
go

if exists (select * from sysindexes where name='FKI_n5dokument_pUzytkWypoz')
	drop index n5dokument.FKI_n5dokument_pUzytkWypoz
go

if exists (select * from sysindexes where name='FKI_n5dokument_pReplaces')
	drop index n5dokument.FKI_n5dokument_pReplaces
go

if exists (select * from sysindexes where name='FKI_n5dokument_pReplaced')
	drop index n5dokument.FKI_n5dokument_pReplaced
go

if exists (select * from sysindexes where name='FKI_n5dokument_dok_pUFPracKlient13')
	drop index n5dokument.FKI_n5dokument_dok_pUFPracKlient13
go

if exists (select * from sysindexes where name='FKI_n5dokument_dok_pUFPracKlient14')
	drop index n5dokument.FKI_n5dokument_dok_pUFPracKlient14
go

if exists (select * from sysindexes where name='FKI_n5dokument_dok_pUFKlient15')
	drop index n5dokument.FKI_n5dokument_dok_pUFKlient15
go

if exists (select * from sysindexes where name='FKI_n5dokument_pUzytRej')
	drop index n5dokument.FKI_n5dokument_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5dokument_dok_pUzytModyf')
	drop index n5dokument.FKI_n5dokument_dok_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5dokument_dok_pSposobPlatnosci')
	drop index n5dokument.FKI_n5dokument_dok_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5pkpir_pRejestrDok')
	drop index n5pkpir.FKI_n5pkpir_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5pkpir_pKlient')
	drop index n5pkpir.FKI_n5pkpir_pKlient
go

if exists (select * from sysindexes where name='WFKI_n5pkpir_pkpir_wrefDokZrodl')
	drop index n5pkpir.WFKI_n5pkpir_pkpir_wrefDokZrodl
go

if exists (select * from sysindexes where name='FKI_n5pkpir_pKwalifikatorEx')
	drop index n5pkpir.FKI_n5pkpir_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5klient_produkt_klpr_pKlient')
	drop index n5klient_produkt.FKI_n5klient_produkt_klpr_pKlient
go

if exists (select * from sysindexes where name='FKI_n5klient_produkt_klpr_pProdukt')
	drop index n5klient_produkt.FKI_n5klient_produkt_klpr_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_egz_pdmeg_pEgz')
	drop index n5pozdokmag_egz.FKI_n5pozdokmag_egz_pdmeg_pEgz
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pPracownik')
	drop index n5plnieob.FKI_n5plnieob_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pUzytRej')
	drop index n5plnieob.FKI_n5plnieob_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pUzytModyf')
	drop index n5plnieob.FKI_n5plnieob_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plnieob_pUmowa')
	drop index n5plnieob.FKI_n5plnieob_pUmowa
go

if exists (select * from sysindexes where name='FKI_n5pltyppracy_tpr_pUsluga')
	drop index n5pltyppracy.FKI_n5pltyppracy_tpr_pUsluga
go

if exists (select * from sysindexes where name='FKI_n5pltyppracy_tpr_pOpak')
	drop index n5pltyppracy.FKI_n5pltyppracy_tpr_pOpak
go

if exists (select * from sysindexes where name='FKI_n5zasobprod_zsp_pTypZasobu')
	drop index n5zasobprod.FKI_n5zasobprod_zsp_pTypZasobu
go

if exists (select * from sysindexes where name='FKI_n5zasobprod_zsp_pKalendarz')
	drop index n5zasobprod.FKI_n5zasobprod_zsp_pKalendarz
go

if exists (select * from sysindexes where name='FKI_n5zasobprod_zsp_pPracownik')
	drop index n5zasobprod.FKI_n5zasobprod_zsp_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5pozankieta_toral_pank_pMaszyna')
	drop index n5pozankieta_toral.FKI_n5pozankieta_toral_pank_pMaszyna
go

if exists (select * from sysindexes where name='FKI_n5pozankieta_toral_pank_pKwalifikatorEx')
	drop index n5pozankieta_toral.FKI_n5pozankieta_toral_pank_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pMiejscowosc')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pKraj')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pKraj
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank1')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank1
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank2')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank2
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pBank3')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pBank3
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pKlient')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pKlient
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_p_Klient_JO_Nadrzedna')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_p_Klient_JO_Nadrzedna
go

if exists (select * from sysindexes where name='FKI_n5_klient_jedn_org_pKlientPracownik')
	drop index n5_klient_jedn_org.FKI_n5_klient_jedn_org_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pKodCelny')
	drop index n5produkt.FKI_n5produkt_prod_pKodCelny
go

if exists (select * from sysindexes where name='FKI_n5produkt_pUlotka')
	drop index n5produkt.FKI_n5produkt_pUlotka
go

if exists (select * from sysindexes where name='FKI_n5produkt_pInstrukcja')
	drop index n5produkt.FKI_n5produkt_pInstrukcja
go

if exists (select * from sysindexes where name='FKI_n5produkt_pJednostkaEwid')
	drop index n5produkt.FKI_n5produkt_pJednostkaEwid
go

if exists (select * from sysindexes where name='FKI_n5produkt_pGrupaProd')
	drop index n5produkt.FKI_n5produkt_pGrupaProd
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pDostawca')
	drop index n5produkt.FKI_n5produkt_prod_pDostawca
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pKrajPoch')
	drop index n5produkt.FKI_n5produkt_prod_pKrajPoch
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pPaletaKolorow')
	drop index n5produkt.FKI_n5produkt_prod_pPaletaKolorow
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pTabelaRozmiarow')
	drop index n5produkt.FKI_n5produkt_prod_pTabelaRozmiarow
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pProdMag')
	drop index n5produkt.FKI_n5produkt_prod_pProdMag
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pPracownik')
	drop index n5produkt.FKI_n5produkt_prod_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pZamiennik1')
	drop index n5produkt.FKI_n5produkt_prod_pZamiennik1
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pZamiennik2')
	drop index n5produkt.FKI_n5produkt_prod_pZamiennik2
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pZamiennik3')
	drop index n5produkt.FKI_n5produkt_prod_pZamiennik3
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pZamiennik4')
	drop index n5produkt.FKI_n5produkt_prod_pZamiennik4
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pZamiennik5')
	drop index n5produkt.FKI_n5produkt_prod_pZamiennik5
go

if exists (select * from sysindexes where name='FKI_n5produkt_prod_pGrupaProdAlt')
	drop index n5produkt.FKI_n5produkt_prod_pGrupaProdAlt
go

if exists (select * from sysindexes where name='FKI_n5dowodksieg_pUzytRej')
	drop index n5dowodksieg.FKI_n5dowodksieg_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5dowodksieg_pRejestrDok')
	drop index n5dowodksieg.FKI_n5dowodksieg_pRejestrDok
go

if exists (select * from sysindexes where name='WFKI_n5dowodksieg_wrefDokZrod')
	drop index n5dowodksieg.WFKI_n5dowodksieg_wrefDokZrod
go

if exists (select * from sysindexes where name='FKI_n5dowodksieg_dk_pUzytModyf')
	drop index n5dowodksieg.FKI_n5dowodksieg_dk_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5kurswalut_pWalZ')
	drop index n5kurswalut.FKI_n5kurswalut_pWalZ
go

if exists (select * from sysindexes where name='FKI_n5kurswalut_pWalN')
	drop index n5kurswalut.FKI_n5kurswalut_pWalN
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pPracownik')
	drop index n5plumowa.FKI_n5plumowa_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pUzytRej')
	drop index n5plumowa.FKI_n5plumowa_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pUzytModyf')
	drop index n5plumowa.FKI_n5plumowa_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pUmowaPop')
	drop index n5plumowa.FKI_n5plumowa_pUmowaPop
go

if exists (select * from sysindexes where name='FKI_n5plumowa_pKalendarz')
	drop index n5plumowa.FKI_n5plumowa_pKalendarz
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pSRTRW')
	drop index n5opsrtrw.FKI_n5opsrtrw_pSRTRW
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pMUJO')
	drop index n5opsrtrw.FKI_n5opsrtrw_pMUJO
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pUzytRej')
	drop index n5opsrtrw.FKI_n5opsrtrw_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pPracownik')
	drop index n5opsrtrw.FKI_n5opsrtrw_pPracownik
go

if exists (select * from sysindexes where name='WFKI_n5opsrtrw_wrefDokument')
	drop index n5opsrtrw.WFKI_n5opsrtrw_wrefDokument
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pRejestrDok')
	drop index n5opsrtrw.FKI_n5opsrtrw_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pDowodKsieg')
	drop index n5opsrtrw.FKI_n5opsrtrw_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pSchematDekr')
	drop index n5opsrtrw.FKI_n5opsrtrw_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_pKwalifikatorEx')
	drop index n5opsrtrw.FKI_n5opsrtrw_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_opsrtrw_pPKPIR')
	drop index n5opsrtrw.FKI_n5opsrtrw_opsrtrw_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5opsrtrw_opsrtrw_pUzytModyf')
	drop index n5opsrtrw.FKI_n5opsrtrw_opsrtrw_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5rolawyk_rolaw_pRola')
	drop index n5rolawyk.FKI_n5rolawyk_rolaw_pRola
go

if exists (select * from sysindexes where name='FKI_n5rolawyk_rolaw_pRolaPrior')
	drop index n5rolawyk.FKI_n5rolawyk_rolaw_pRolaPrior
go

if exists (select * from sysindexes where name='FKI_n5ptop_gmo_pProd')
	drop index n5ptop.FKI_n5ptop_gmo_pProd
go

if exists (select * from sysindexes where name='FKI_n5ptop_gmo_pOpak')
	drop index n5ptop.FKI_n5ptop_gmo_pOpak
go

if exists (select * from sysindexes where name='FKI_n5ptop_gmo_pMag')
	drop index n5ptop.FKI_n5ptop_gmo_pMag
go

if exists (select * from sysindexes where name='FKI_n5poz_koszt_wyjazdu_pdkw_pMiejscowoscWy')
	drop index n5poz_koszt_wyjazdu.FKI_n5poz_koszt_wyjazdu_pdkw_pMiejscowoscWy
go

if exists (select * from sysindexes where name='FKI_n5poz_koszt_wyjazdu_pdkw_pMiejscowoscPrzy')
	drop index n5poz_koszt_wyjazdu.FKI_n5poz_koszt_wyjazdu_pdkw_pMiejscowoscPrzy
go

if exists (select * from sysindexes where name='FKI_n5poz_koszt_wyjazdu_pdkw_pSrodekLok')
	drop index n5poz_koszt_wyjazdu.FKI_n5poz_koszt_wyjazdu_pdkw_pSrodekLok
go

if exists (select * from sysindexes where name='FKI_n5poz_koszt_wyjazdu_pdkw_pKwalifikatorEx')
	drop index n5poz_koszt_wyjazdu.FKI_n5poz_koszt_wyjazdu_pdkw_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_pWojewodztwo')
	drop index n5miejscowosc.FKI_n5miejscowosc_pWojewodztwo
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_pRegion')
	drop index n5miejscowosc.FKI_n5miejscowosc_pRegion
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_mie_pPowiat')
	drop index n5miejscowosc.FKI_n5miejscowosc_mie_pPowiat
go

if exists (select * from sysindexes where name='FKI_n5miejscowosc_mie_pGmina')
	drop index n5miejscowosc.FKI_n5miejscowosc_mie_pGmina
go

if exists (select * from sysindexes where name='WFKI_n5SendEmail_wpNadawca')
	drop index n5SendEmail.WFKI_n5SendEmail_wpNadawca
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_pDefSchematdekr')
	drop index n5rejestrdok.FKI_n5rejestrdok_pDefSchematdekr
go

if exists (select * from sysindexes where name='WFKI_n5rejestrdok_wrefParam1')
	drop index n5rejestrdok.WFKI_n5rejestrdok_wrefParam1
go

if exists (select * from sysindexes where name='WFKI_n5rejestrdok_wrefParam2')
	drop index n5rejestrdok.WFKI_n5rejestrdok_wrefParam2
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_pRokKsieg')
	drop index n5rejestrdok.FKI_n5rejestrdok_pRokKsieg
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_rejdok_pDefSchematdekr2')
	drop index n5rejestrdok.FKI_n5rejestrdok_rejdok_pDefSchematdekr2
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_rejdok_pDefKlient')
	drop index n5rejestrdok.FKI_n5rejestrdok_rejdok_pDefKlient
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_rejdok_pRejestrParam4')
	drop index n5rejestrdok.FKI_n5rejestrdok_rejdok_pRejestrParam4
go

if exists (select * from sysindexes where name='FKI_n5rejestrdok_rejdok_pRejestrDok')
	drop index n5rejestrdok.FKI_n5rejestrdok_rejdok_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlient')
	drop index n5dokmag.FKI_n5dokmag_pKlient
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlient_JO')
	drop index n5dokmag.FKI_n5dokmag_pKlient_JO
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKlientPracownik')
	drop index n5dokmag.FKI_n5dokmag_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pDokMag')
	drop index n5dokmag.FKI_n5dokmag_pDokMag
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pUzytRej')
	drop index n5dokmag.FKI_n5dokmag_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pRejestrDok')
	drop index n5dokmag.FKI_n5dokmag_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pDowodKsieg')
	drop index n5dokmag.FKI_n5dokmag_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pSchematDekr')
	drop index n5dokmag.FKI_n5dokmag_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pMagZrod')
	drop index n5dokmag.FKI_n5dokmag_pMagZrod
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pMagDocel')
	drop index n5dokmag.FKI_n5dokmag_pMagDocel
go

if exists (select * from sysindexes where name='WFKI_n5dokmag_wrefDokHandl')
	drop index n5dokmag.WFKI_n5dokmag_wrefDokHandl
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pKwalifikatorEx')
	drop index n5dokmag.FKI_n5dokmag_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5dokmag_dm_pSposobDostawy')
	drop index n5dokmag.FKI_n5dokmag_dm_pSposobDostawy
go

if exists (select * from sysindexes where name='FKI_n5dokmag_dm_pUzytModyf')
	drop index n5dokmag.FKI_n5dokmag_dm_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pDokStatus')
	drop index n5dokmag.FKI_n5dokmag_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pPracownik')
	drop index n5dokmag.FKI_n5dokmag_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5dokmag_pObiektKlienta')
	drop index n5dokmag.FKI_n5dokmag_pObiektKlienta
go

if exists (select * from sysindexes where name='FKI_n5dokmag_dm_pMiejscowosc_dost')
	drop index n5dokmag.FKI_n5dokmag_dm_pMiejscowosc_dost
go

if exists (select * from sysindexes where name='FKI_n5dokmag_dm_pKraj_dost')
	drop index n5dokmag.FKI_n5dokmag_dm_pKraj_dost
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pGrupa')
	drop index n5srtrw.FKI_n5srtrw_pGrupa
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pPracownik')
	drop index n5srtrw.FKI_n5srtrw_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pMUJO')
	drop index n5srtrw.FKI_n5srtrw_pMUJO
go

if exists (select * from sysindexes where name='FKI_n5srtrw_srtrw_pJednOrg')
	drop index n5srtrw.FKI_n5srtrw_srtrw_pJednOrg
go

if exists (select * from sysindexes where name='FKI_n5srtrw_pKwalifikatorEx')
	drop index n5srtrw.FKI_n5srtrw_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5plsubkonto_pJednostka')
	drop index n5plsubkonto.FKI_n5plsubkonto_pJednostka
go

if exists (select * from sysindexes where name='WFKI_n5bwinfo_zal_wrefZal')
	drop index n5bwinfo_zal.WFKI_n5bwinfo_zal_wrefZal
go

if exists (select * from sysindexes where name='FKI_n5stanowisko_stn_pKwalifikatorEx')
	drop index n5stanowisko.FKI_n5stanowisko_stn_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5securityobj_pSOD')
	drop index n5securityobj.FKI_n5securityobj_pSOD
go

if exists (select * from sysindexes where name='FKI_n5securityobj_pUser')
	drop index n5securityobj.FKI_n5securityobj_pUser
go

if exists (select * from sysindexes where name='FKI_n5klient_pMiejscowosc')
	drop index n5klient.FKI_n5klient_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5klient_pKraj')
	drop index n5klient.FKI_n5klient_pKraj
go

if exists (select * from sysindexes where name='FKI_n5klient_pBranza')
	drop index n5klient.FKI_n5klient_pBranza
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank1')
	drop index n5klient.FKI_n5klient_pBank1
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank2')
	drop index n5klient.FKI_n5klient_pBank2
go

if exists (select * from sysindexes where name='FKI_n5klient_pBank3')
	drop index n5klient.FKI_n5klient_pBank3
go

if exists (select * from sysindexes where name='FKI_n5klient_pWaluta')
	drop index n5klient.FKI_n5klient_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5klient_pPracownik')
	drop index n5klient.FKI_n5klient_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5klient_pGrupaKlient')
	drop index n5klient.FKI_n5klient_pGrupaKlient
go

if exists (select * from sysindexes where name='FKI_n5klient_pMiejscowoscSDB')
	drop index n5klient.FKI_n5klient_pMiejscowoscSDB
go

if exists (select * from sysindexes where name='FKI_n5klient_pKrajSDB')
	drop index n5klient.FKI_n5klient_pKrajSDB
go

if exists (select * from sysindexes where name='FKI_n5klient_pWalutaLimitu')
	drop index n5klient.FKI_n5klient_pWalutaLimitu
go

if exists (select * from sysindexes where name='FKI_n5klient_pSposobPlatnosci')
	drop index n5klient.FKI_n5klient_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5klient_kli_pKursIndywidualnyWaluta')
	drop index n5klient.FKI_n5klient_kli_pKursIndywidualnyWaluta
go

if exists (select * from sysindexes where name='FKI_n5klient_kli_pGrupaProd')
	drop index n5klient.FKI_n5klient_kli_pGrupaProd
go

if exists (select * from sysindexes where name='FKI_n5klient_kli_pSposobDostawy')
	drop index n5klient.FKI_n5klient_kli_pSposobDostawy
go

if exists (select * from sysindexes where name='WFKI_n5zadaniezal_wrefZal')
	drop index n5zadaniezal.WFKI_n5zadaniezal_wrefZal
go

if exists (select * from sysindexes where name='FKI_n5sposdost_sposdost_pUsluga')
	drop index n5sposdost.FKI_n5sposdost_sposdost_pUsluga
go

if exists (select * from sysindexes where name='FKI_n5zakup_pSposobPlatnosci')
	drop index n5zakup.FKI_n5zakup_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDostawca')
	drop index n5zakup.FKI_n5zakup_pDostawca
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDostawca_JO')
	drop index n5zakup.FKI_n5zakup_pDostawca_JO
go

if exists (select * from sysindexes where name='FKI_n5zakup_pUzytRej')
	drop index n5zakup.FKI_n5zakup_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5zakup_pZadanie')
	drop index n5zakup.FKI_n5zakup_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5zakup_pRejestrDok')
	drop index n5zakup.FKI_n5zakup_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDowodKsieg')
	drop index n5zakup.FKI_n5zakup_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5zakup_pSchematDekr')
	drop index n5zakup.FKI_n5zakup_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5zakup_pTransakcja')
	drop index n5zakup.FKI_n5zakup_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5zakup_pPopZAkup')
	drop index n5zakup.FKI_n5zakup_pPopZAkup
go

if exists (select * from sysindexes where name='FKI_n5zakup_pWaluta')
	drop index n5zakup.FKI_n5zakup_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5zakup_pRozlVat')
	drop index n5zakup.FKI_n5zakup_pRozlVat
go

if exists (select * from sysindexes where name='FKI_n5zakup_pKwalifikatorEx')
	drop index n5zakup.FKI_n5zakup_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5zakup_pTransakcjaImport')
	drop index n5zakup.FKI_n5zakup_pTransakcjaImport
go

if exists (select * from sysindexes where name='FKI_n5zakup_pUrzadCelny')
	drop index n5zakup.FKI_n5zakup_pUrzadCelny
go

if exists (select * from sysindexes where name='FKI_n5zakup_pZamowienie')
	drop index n5zakup.FKI_n5zakup_pZamowienie
go

if exists (select * from sysindexes where name='FKI_n5zakup_zak_pPKPIR')
	drop index n5zakup.FKI_n5zakup_zak_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5zakup_zak_pSposobDostawy')
	drop index n5zakup.FKI_n5zakup_zak_pSposobDostawy
go

if exists (select * from sysindexes where name='FKI_n5zakup_zak_pUzytModyf')
	drop index n5zakup.FKI_n5zakup_zak_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5zakup_zak_pKlientPracownik')
	drop index n5zakup.FKI_n5zakup_zak_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5zakup_pDokStatus')
	drop index n5zakup.FKI_n5zakup_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5zakup_zak_pRozlVat_SP')
	drop index n5zakup.FKI_n5zakup_zak_pRozlVat_SP
go

if exists (select * from sysindexes where name='WFKI_n5plsklnal_wrefDokument')
	drop index n5plsklnal.WFKI_n5plsklnal_wrefDokument
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pUrzadSkarbowy')
	drop index n5istat.FKI_n5istat_istt_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pUzytRej')
	drop index n5istat.FKI_n5istat_istt_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pZadanie')
	drop index n5istat.FKI_n5istat_istt_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pSchematDekr')
	drop index n5istat.FKI_n5istat_istt_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pDowKsieg')
	drop index n5istat.FKI_n5istat_istt_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pTransakcja')
	drop index n5istat.FKI_n5istat_istt_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5istat_istt_pUzytModyf')
	drop index n5istat.FKI_n5istat_istt_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5protokol_abas_prot_pProjekt')
	drop index n5protokol_abas.FKI_n5protokol_abas_prot_pProjekt
go

if exists (select * from sysindexes where name='FKI_n5protokol_abas_prot_pWaluta')
	drop index n5protokol_abas.FKI_n5protokol_abas_prot_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5protokol_abas_prot_pFaktura')
	drop index n5protokol_abas.FKI_n5protokol_abas_prot_pFaktura
go

if exists (select * from sysindexes where name='FKI_n5protokol_abas_prot_pKwalifikatorEx')
	drop index n5protokol_abas.FKI_n5protokol_abas_prot_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5kolor_kol_pPaleta')
	drop index n5kolor.FKI_n5kolor_kol_pPaleta
go

if exists (select * from sysindexes where name='FKI_n5pozrejestrdok_mag_prdm_pMagazyn')
	drop index n5pozrejestrdok_mag.FKI_n5pozrejestrdok_mag_prdm_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pTyp')
	drop index n5instytucja.FKI_n5instytucja_pTyp
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pMiejscowosc')
	drop index n5instytucja.FKI_n5instytucja_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pKraj')
	drop index n5instytucja.FKI_n5instytucja_pKraj
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank1')
	drop index n5instytucja.FKI_n5instytucja_pBank1
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank2')
	drop index n5instytucja.FKI_n5instytucja_pBank2
go

if exists (select * from sysindexes where name='FKI_n5instytucja_pBank3')
	drop index n5instytucja.FKI_n5instytucja_pBank3
go

if exists (select * from sysindexes where name='WFKI_n5wykonawca_wrefObiekt')
	drop index n5wykonawca.WFKI_n5wykonawca_wrefObiekt
go

if exists (select * from sysindexes where name='FKI_n5powiat_pow_pWojewodztwo')
	drop index n5powiat.FKI_n5powiat_pow_pWojewodztwo
go

if exists (select * from sysindexes where name='FKI_n5pozrata_prat_pSposobPlatnosci')
	drop index n5pozrata.FKI_n5pozrata_prat_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5pozrata_prat_pPlatnik')
	drop index n5pozrata.FKI_n5pozrata_prat_pPlatnik
go

if exists (select * from sysindexes where name='FKI_n5pozrata_prat_pTransakcja')
	drop index n5pozrata.FKI_n5pozrata_prat_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pProdukt')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pOpak')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pKwalifikatorEx')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pzam_pZadanie')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pzam_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pProduktOrg')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pProduktOrg
go

if exists (select * from sysindexes where name='FKI_n5pozzamowienie_pOpakOrg')
	drop index n5pozzamowienie.FKI_n5pozzamowienie_pOpakOrg
go

if exists (select * from sysindexes where name='FKI_n5plschematnal_pTerminNal')
	drop index n5plschematnal.FKI_n5plschematnal_pTerminNal
go

if exists (select * from sysindexes where name='FKI_n5plschematnal_pJednostkaParam1')
	drop index n5plschematnal.FKI_n5plschematnal_pJednostkaParam1
go

if exists (select * from sysindexes where name='FKI_n5plschematnal_pJednostkaParam2')
	drop index n5plschematnal.FKI_n5plschematnal_pJednostkaParam2
go

if exists (select * from sysindexes where name='FKI_n5plschematnal_pGrupaSchemNal')
	drop index n5plschematnal.FKI_n5plschematnal_pGrupaSchemNal
go

if exists (select * from sysindexes where name='FKI_n5plpozschnal_pSchemat')
	drop index n5plpozschnal.FKI_n5plpozschnal_pSchemat
go

-- skipped virtual table: n5vatuek
if exists (select * from sysindexes where name='FKI_n5pozrealprod_zasob_prpz_pTypZasobu')
	drop index n5pozrealprod_zasob.FKI_n5pozrealprod_zasob_prpz_pTypZasobu
go

if exists (select * from sysindexes where name='WFKI_n5straznik_cen_scs_wpProdGrupa')
	drop index n5straznik_cen.WFKI_n5straznik_cen_scs_wpProdGrupa
go

if exists (select * from sysindexes where name='WFKI_n5straznik_cen_scs_wpKlientGrupa')
	drop index n5straznik_cen.WFKI_n5straznik_cen_scs_wpKlientGrupa
go

if exists (select * from sysindexes where name='FKI_n5straznik_cen_scs_pKwalifikatorEx')
	drop index n5straznik_cen.FKI_n5straznik_cen_scs_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pZlecajacy')
	drop index n5zadanie.FKI_n5zadanie_pZlecajacy
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pTypDzialania')
	drop index n5zadanie.FKI_n5zadanie_pTypDzialania
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pProcedura')
	drop index n5zadanie.FKI_n5zadanie_pProcedura
go

if exists (select * from sysindexes where name='WFKI_n5zadanie_wrefSzczegoly')
	drop index n5zadanie.WFKI_n5zadanie_wrefSzczegoly
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pNadZadanie')
	drop index n5zadanie.FKI_n5zadanie_pNadZadanie
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pPopZadanie')
	drop index n5zadanie.FKI_n5zadanie_pPopZadanie
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pWykonawca')
	drop index n5zadanie.FKI_n5zadanie_pWykonawca
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKlient')
	drop index n5zadanie.FKI_n5zadanie_pKlient
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pSchematDekretacji')
	drop index n5zadanie.FKI_n5zadanie_pSchematDekretacji
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pDowKsieg')
	drop index n5zadanie.FKI_n5zadanie_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKlientPracownik')
	drop index n5zadanie.FKI_n5zadanie_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pKwalifikatorEx')
	drop index n5zadanie.FKI_n5zadanie_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5zadanie_zad_pRejestrDok')
	drop index n5zadanie.FKI_n5zadanie_zad_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5zadanie_zad_pKLOB')
	drop index n5zadanie.FKI_n5zadanie_zad_pKLOB
go

if exists (select * from sysindexes where name='FKI_n5zadanie_pDokStatus')
	drop index n5zadanie.FKI_n5zadanie_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pUrzadSkarbowy')
	drop index n5pit5.FKI_n5pit5_pt5_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pUzytRej')
	drop index n5pit5.FKI_n5pit5_pt5_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pZadanie')
	drop index n5pit5.FKI_n5pit5_pt5_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pSchematDekr')
	drop index n5pit5.FKI_n5pit5_pt5_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pDowKsieg')
	drop index n5pit5.FKI_n5pit5_pt5_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pTransakcja')
	drop index n5pit5.FKI_n5pit5_pt5_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pit5_pt5_pUzytModyf')
	drop index n5pit5.FKI_n5pit5_pt5_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5typdzialania_pTypNadrzedny')
	drop index n5typdzialania.FKI_n5typdzialania_pTypNadrzedny
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pUzytRej')
	drop index n5zlecprod.FKI_n5zlecprod_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pRejestrDok')
	drop index n5zlecprod.FKI_n5zlecprod_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pDowodKsieg')
	drop index n5zlecprod.FKI_n5zlecprod_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pSchematDekr')
	drop index n5zlecprod.FKI_n5zlecprod_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pZadanie')
	drop index n5zlecprod.FKI_n5zlecprod_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKlient')
	drop index n5zlecprod.FKI_n5zlecprod_pKlient
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKlient_JO')
	drop index n5zlecprod.FKI_n5zlecprod_pKlient_JO
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pZamowienie')
	drop index n5zlecprod.FKI_n5zlecprod_pZamowienie
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pKwalifikatorEx')
	drop index n5zlecprod.FKI_n5zlecprod_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_pNadZlec')
	drop index n5zlecprod.FKI_n5zlecprod_pNadZlec
go

if exists (select * from sysindexes where name='FKI_n5zlecprod_zlp_pUzytModyf')
	drop index n5zlecprod.FKI_n5zlecprod_zlp_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plpozostale_pPracownik')
	drop index n5plpozostale.FKI_n5plpozostale_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plpozostale_pUzytRej')
	drop index n5plpozostale.FKI_n5plpozostale_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plpozostale_pUzytModyf')
	drop index n5plpozostale.FKI_n5plpozostale_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plpozostale_pUmowa')
	drop index n5plpozostale.FKI_n5plpozostale_pUmowa
go

if exists (select * from sysindexes where name='FKI_n5pozdokprod_pdp_pProdukt')
	drop index n5pozdokprod.FKI_n5pozdokprod_pdp_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozdokprod_pdp_pOpak')
	drop index n5pozdokprod.FKI_n5pozdokprod_pdp_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozdokprod_pdp_pWalutaCeny')
	drop index n5pozdokprod.FKI_n5pozdokprod_pdp_pWalutaCeny
go

if exists (select * from sysindexes where name='FKI_n5pozdokprod_pdp_pKLOB')
	drop index n5pozdokprod.FKI_n5pozdokprod_pdp_pKLOB
go

if exists (select * from sysindexes where name='FKI_n5pozdokprod_pdp_pTypDzial')
	drop index n5pozdokprod.FKI_n5pozdokprod_pdp_pTypDzial
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_zasob_prz_pTypZasobu')
	drop index n5pozrecepta_zasob.FKI_n5pozrecepta_zasob_prz_pTypZasobu
go

if exists (select * from sysindexes where name='FKI_n5inwmag_im_pMagazyn')
	drop index n5inwmag.FKI_n5inwmag_im_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5inwmag_im_pIR')
	drop index n5inwmag.FKI_n5inwmag_im_pIR
go

if exists (select * from sysindexes where name='FKI_n5inwmag_im_pIP')
	drop index n5inwmag.FKI_n5inwmag_im_pIP
go

if exists (select * from sysindexes where name='FKI_n5inwmag_im_pKwalifikatorEx')
	drop index n5inwmag.FKI_n5inwmag_im_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5grupaproduktow_pGrupaNadrzedna')
	drop index n5grupaproduktow.FKI_n5grupaproduktow_pGrupaNadrzedna
go

if exists (select * from sysindexes where name='FKI_n5grupaproduktow_grp_pJednostkaEwid')
	drop index n5grupaproduktow.FKI_n5grupaproduktow_grp_pJednostkaEwid
go

if exists (select * from sysindexes where name='FKI_n5grupaproduktow_grp_pDostawca')
	drop index n5grupaproduktow.FKI_n5grupaproduktow_grp_pDostawca
go

if exists (select * from sysindexes where name='FKI_n5grupaproduktow_grp_pPracownik')
	drop index n5grupaproduktow.FKI_n5grupaproduktow_grp_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5dokumentlinks_pDokument')
	drop index n5dokumentlinks.FKI_n5dokumentlinks_pDokument
go

if exists (select * from sysindexes where name='WFKI_n5platnosc_wrefPodmiot')
	drop index n5platnosc.WFKI_n5platnosc_wrefPodmiot
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pZadanie')
	drop index n5platnosc.FKI_n5platnosc_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pUzytRej')
	drop index n5platnosc.FKI_n5platnosc_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pRejestrDok')
	drop index n5platnosc.FKI_n5platnosc_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pDowodKsieg')
	drop index n5platnosc.FKI_n5platnosc_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pSchematDekr')
	drop index n5platnosc.FKI_n5platnosc_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pWalutaPodm')
	drop index n5platnosc.FKI_n5platnosc_pWalutaPodm
go

if exists (select * from sysindexes where name='FKI_n5platnosc_plat_pPKPIR')
	drop index n5platnosc.FKI_n5platnosc_plat_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5platnosc_plat_pRapKas')
	drop index n5platnosc.FKI_n5platnosc_plat_pRapKas
go

if exists (select * from sysindexes where name='FKI_n5platnosc_plat_pUzytModyf')
	drop index n5platnosc.FKI_n5platnosc_plat_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5platnosc_pDokStatus')
	drop index n5platnosc.FKI_n5platnosc_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5pozdoketyk_pdet_pWyrob')
	drop index n5pozdoketyk.FKI_n5pozdoketyk_pdet_pWyrob
go

if exists (select * from sysindexes where name='FKI_n5pozdoketyk_pdet_pOpak')
	drop index n5pozdoketyk.FKI_n5pozdoketyk_pdet_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozdoketyk_pdet_pKwalifikatorEx')
	drop index n5pozdoketyk.FKI_n5pozdoketyk_pdet_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pProdukt')
	drop index n5pozrecepta.FKI_n5pozrecepta_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pOpak')
	drop index n5pozrecepta.FKI_n5pozrecepta_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pZamiennik1')
	drop index n5pozrecepta.FKI_n5pozrecepta_pZamiennik1
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pZamiennik2')
	drop index n5pozrecepta.FKI_n5pozrecepta_pZamiennik2
go

if exists (select * from sysindexes where name='FKI_n5pozrecepta_pZamiennik3')
	drop index n5pozrecepta.FKI_n5pozrecepta_pZamiennik3
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pPracownik')
	drop index n5plchoroba.FKI_n5plchoroba_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pUzytRej')
	drop index n5plchoroba.FKI_n5plchoroba_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pUzytModyf')
	drop index n5plchoroba.FKI_n5plchoroba_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plchoroba_pUmowa')
	drop index n5plchoroba.FKI_n5plchoroba_pUmowa
go

if exists (select * from sysindexes where name='FKI_n5plrcp_rcp_pPracownik')
	drop index n5plrcp.FKI_n5plrcp_rcp_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plrcp_rcp_pUmowa')
	drop index n5plrcp.FKI_n5plrcp_rcp_pUmowa
go

if exists (select * from sysindexes where name='FKI_n5plrcp_rcp_pUzytRej')
	drop index n5plrcp.FKI_n5plrcp_rcp_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plrcp_rcp_pTypPracy')
	drop index n5plrcp.FKI_n5plrcp_rcp_pTypPracy
go

if exists (select * from sysindexes where name='FKI_n5plrcp_rcp_pZadanie')
	drop index n5plrcp.FKI_n5plrcp_rcp_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5transakcja_operacja_trop_pTransakcja')
	drop index n5transakcja_operacja.FKI_n5transakcja_operacja_trop_pTransakcja
go

if exists (select * from sysindexes where name='WFKI_n5transakcja_operacja_trop_wrefDokument')
	drop index n5transakcja_operacja.WFKI_n5transakcja_operacja_trop_wrefDokument
go

if exists (select * from sysindexes where name='FKI_n5transakcja_operacja_trop_pUzytRej')
	drop index n5transakcja_operacja.FKI_n5transakcja_operacja_trop_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5transakcja_operacja_trop_pUzytModyf')
	drop index n5transakcja_operacja.FKI_n5transakcja_operacja_trop_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5ankieta_toral_ank_pUzytRej')
	drop index n5ankieta_toral.FKI_n5ankieta_toral_ank_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5ankieta_toral_ank_pKlient')
	drop index n5ankieta_toral.FKI_n5ankieta_toral_ank_pKlient
go

if exists (select * from sysindexes where name='FKI_n5ankieta_toral_ank_pKwalifikatorEx')
	drop index n5ankieta_toral.FKI_n5ankieta_toral_ank_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5userprof_pn5user')
	drop index n5userprof.FKI_n5userprof_pn5user
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pMiejscowosc')
	drop index n5jedn_org.FKI_n5jedn_org_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pKraj')
	drop index n5jedn_org.FKI_n5jedn_org_pKraj
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank1')
	drop index n5jedn_org.FKI_n5jedn_org_pBank1
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank2')
	drop index n5jedn_org.FKI_n5jedn_org_pBank2
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pBank3')
	drop index n5jedn_org.FKI_n5jedn_org_pBank3
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_pPracownik')
	drop index n5jedn_org.FKI_n5jedn_org_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5jedn_org_p_Jend_Org_Nadrzedna')
	drop index n5jedn_org.FKI_n5jedn_org_p_Jend_Org_Nadrzedna
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pOpakowanieJedn')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pOpakowanieJedn
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pJednostkaWagi')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pJednostkaWagi
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pWaluta')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pJednOpak')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pJednOpak
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_pZamiennik')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_pZamiennik
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWalutaMinCenySprzed')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWalutaMinCenySprzed
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta2')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta2
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta3')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta3
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta4')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta4
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta5')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta5
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta6')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta6
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pKolor')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pKolor
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pRozmiar')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pRozmiar
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pOpakMag')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pOpakMag
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta7')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta7
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta8')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta8
go

if exists (select * from sysindexes where name='FKI_n5opakowanie_produktu_opak_pWaluta9')
	drop index n5opakowanie_produktu.FKI_n5opakowanie_produktu_opak_pWaluta9
go

if exists (select * from sysindexes where name='FKI_n5dekret_pKonto')
	drop index n5dekret.FKI_n5dekret_pKonto
go

if exists (select * from sysindexes where name='FKI_n5dekret_pTransakcja')
	drop index n5dekret.FKI_n5dekret_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5dekret_pKwalifikator')
	drop index n5dekret.FKI_n5dekret_pKwalifikator
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pPracownik')
	drop index n5pldekret.FKI_n5pldekret_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5pldekret_pSubKonto')
	drop index n5pldekret.FKI_n5pldekret_pSubKonto
go

if exists (select * from sysindexes where name='WFKI_n5pldekret_wrefDokument')
	drop index n5pldekret.WFKI_n5pldekret_wrefDokument
go

if exists (select * from sysindexes where name='FKI_n5notaods_pKlient')
	drop index n5notaods.FKI_n5notaods_pKlient
go

if exists (select * from sysindexes where name='FKI_n5notaods_pUzytRej')
	drop index n5notaods.FKI_n5notaods_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5notaods_pRejestrDok')
	drop index n5notaods.FKI_n5notaods_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5notaods_pDowodKsieg')
	drop index n5notaods.FKI_n5notaods_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5notaods_pSchematDekr')
	drop index n5notaods.FKI_n5notaods_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5notaods_pKwalifikatorEx')
	drop index n5notaods.FKI_n5notaods_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5notaods_pTransakcja')
	drop index n5notaods.FKI_n5notaods_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5notaods_nos_pUzytModyf')
	drop index n5notaods.FKI_n5notaods_nos_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5zadanie_rola_zadr_pRola')
	drop index n5zadanie_rola.FKI_n5zadanie_rola_zadr_pRola
go

if exists (select * from sysindexes where name='FKI_n5zadanie_rola_zadr_pRolaPrior')
	drop index n5zadanie_rola.FKI_n5zadanie_rola_zadr_pRolaPrior
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pPracownik')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pStanowisko')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pStanowisko
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pUzytRej')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pWaluta')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pDokStatus')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5polecenie_wyjazdu_pws_pKwalifikatorEx')
	drop index n5polecenie_wyjazdu.FKI_n5polecenie_wyjazdu_pws_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5dpc_pDocTemplate')
	drop index n5dpc.FKI_n5dpc_pDocTemplate
go

if exists (select * from sysindexes where name='FKI_n5firma_pMiejscowosc')
	drop index n5firma.FKI_n5firma_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5firma_pKraj')
	drop index n5firma.FKI_n5firma_pKraj
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank1')
	drop index n5firma.FKI_n5firma_pBank1
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank2')
	drop index n5firma.FKI_n5firma_pBank2
go

if exists (select * from sysindexes where name='FKI_n5firma_pWaluta')
	drop index n5firma.FKI_n5firma_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank3')
	drop index n5firma.FKI_n5firma_pBank3
go

if exists (select * from sysindexes where name='FKI_n5firma_pUrzadSkarbowyVAT')
	drop index n5firma.FKI_n5firma_pUrzadSkarbowyVAT
go

if exists (select * from sysindexes where name='FKI_n5firma_pUrzadSkarbowyPD')
	drop index n5firma.FKI_n5firma_pUrzadSkarbowyPD
go

if exists (select * from sysindexes where name='FKI_n5firma_pZUS')
	drop index n5firma.FKI_n5firma_pZUS
go

if exists (select * from sysindexes where name='FKI_n5firma_pMainJO')
	drop index n5firma.FKI_n5firma_pMainJO
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank4')
	drop index n5firma.FKI_n5firma_pBank4
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank5')
	drop index n5firma.FKI_n5firma_pBank5
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank6')
	drop index n5firma.FKI_n5firma_pBank6
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank7')
	drop index n5firma.FKI_n5firma_pBank7
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank8')
	drop index n5firma.FKI_n5firma_pBank8
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank9')
	drop index n5firma.FKI_n5firma_pBank9
go

if exists (select * from sysindexes where name='FKI_n5firma_pBank10')
	drop index n5firma.FKI_n5firma_pBank10
go

if exists (select * from sysindexes where name='FKI_n5WizzardEmail_pChoiceList')
	drop index n5WizzardEmail.FKI_n5WizzardEmail_pChoiceList
go

if exists (select * from sysindexes where name='FKI_n5pozvatue_pvtue_refKlient')
	drop index n5pozvatue.FKI_n5pozvatue_pvtue_refKlient
go

if exists (select * from sysindexes where name='FKI_n5pozvatue_pvtue_refKlientZast')
	drop index n5pozvatue.FKI_n5pozvatue_pvtue_refKlientZast
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pProdukt')
	drop index n5pozdokmag.FKI_n5pozdokmag_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pOpak')
	drop index n5pozdokmag.FKI_n5pozdokmag_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pMagZrod')
	drop index n5pozdokmag.FKI_n5pozdokmag_pMagZrod
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pMagDocel')
	drop index n5pozdokmag.FKI_n5pozdokmag_pMagDocel
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pJednOpak')
	drop index n5pozdokmag.FKI_n5pozdokmag_pJednOpak
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pJednEwid')
	drop index n5pozdokmag.FKI_n5pozdokmag_pJednEwid
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pKwalifikatorEx')
	drop index n5pozdokmag.FKI_n5pozdokmag_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozdokmag_pdm_pObiektKlienta')
	drop index n5pozdokmag.FKI_n5pozdokmag_pdm_pObiektKlienta
go

if exists (select * from sysindexes where name='FKI_n5grupasrtrw_pGrupaNadrzedna')
	drop index n5grupasrtrw.FKI_n5grupasrtrw_pGrupaNadrzedna
go

if exists (select * from sysindexes where name='WFKI_n5bwinfo_produkt_wpProdGrupa')
	drop index n5bwinfo_produkt.WFKI_n5bwinfo_produkt_wpProdGrupa
go

if exists (select * from sysindexes where name='FKI_n5bwinfo_produkt_pOpak')
	drop index n5bwinfo_produkt.FKI_n5bwinfo_produkt_pOpak
go

if exists (select * from sysindexes where name='FKI_n5rozmiar_roz_pTabelaRozmiarow')
	drop index n5rozmiar.FKI_n5rozmiar_roz_pTabelaRozmiarow
go

if exists (select * from sysindexes where name='FKI_n5pojazd_poj_pKlient')
	drop index n5pojazd.FKI_n5pojazd_poj_pKlient
go

if exists (select * from sysindexes where name='FKI_n5pojazd_poj_pPracownik')
	drop index n5pojazd.FKI_n5pojazd_poj_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5pojazd_poj_pJednOrg')
	drop index n5pojazd.FKI_n5pojazd_poj_pJednOrg
go

if exists (select * from sysindexes where name='FKI_n5pojazd_poj_pWaluta')
	drop index n5pojazd.FKI_n5pojazd_poj_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5pojazd_poj_pKwalifikatorEx')
	drop index n5pojazd.FKI_n5pojazd_poj_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5sod_pSODGroup')
	drop index n5sod.FKI_n5sod_pSODGroup
go

if exists (select * from sysindexes where name='FKI_n5uzytkownik_pWykonawca')
	drop index n5uzytkownik.FKI_n5uzytkownik_pWykonawca
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pRejestrDok')
	drop index n5rapkas.FKI_n5rapkas_raka_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pDowodKsieg')
	drop index n5rapkas.FKI_n5rapkas_raka_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pSchematDekr')
	drop index n5rapkas.FKI_n5rapkas_raka_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pPKPIR')
	drop index n5rapkas.FKI_n5rapkas_raka_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pUzytRej')
	drop index n5rapkas.FKI_n5rapkas_raka_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pKwalifikatorEx')
	drop index n5rapkas.FKI_n5rapkas_raka_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5rapkas_raka_pUzytModyf')
	drop index n5rapkas.FKI_n5rapkas_raka_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pProdukt')
	drop index n5pozzakup.FKI_n5pozzakup_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pOpak')
	drop index n5pozzakup.FKI_n5pozzakup_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pKwalifikatorEx')
	drop index n5pozzakup.FKI_n5pozzakup_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pzak_pZadanie')
	drop index n5pozzakup.FKI_n5pozzakup_pzak_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pozzakup_pzak_pObiektKlienta')
	drop index n5pozzakup.FKI_n5pozzakup_pzak_pObiektKlienta
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pPracownik')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pPracownik
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pUzytRej')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pUzytModyf')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pRejestrDok')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pDowodKsieg')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pSchematDekr')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pListaPlac')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pListaPlac
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pTransakcja')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_pZadanie')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pPKPIR')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pPKPIR
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaUS')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaUS
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaZUS51')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaZUS51
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaZUS52')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaZUS52
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaZUS53')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaZUS53
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaInne')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaInne
go

if exists (select * from sysindexes where name='FKI_n5plnaliczenie_plnal_pTransakcjaInne2')
	drop index n5plnaliczenie.FKI_n5plnaliczenie_plnal_pTransakcjaInne2
go

if exists (select * from sysindexes where name='FKI_n5konto_budzet_pKonto')
	drop index n5konto_budzet.FKI_n5konto_budzet_pKonto
go

if exists (select * from sysindexes where name='FKI_n5konto_budzet_pBudzet')
	drop index n5konto_budzet.FKI_n5konto_budzet_pBudzet
go

if exists (select * from sysindexes where name='FKI_n5gmstan_gms_pProd')
	drop index n5gmstan.FKI_n5gmstan_gms_pProd
go

if exists (select * from sysindexes where name='FKI_n5gmstan_gms_pOpak')
	drop index n5gmstan.FKI_n5gmstan_gms_pOpak
go

if exists (select * from sysindexes where name='FKI_n5gmstan_gms_pMag')
	drop index n5gmstan.FKI_n5gmstan_gms_pMag
go

if exists (select * from sysindexes where name='FKI_n5pozprojekt_abas_pproj_pProdukt')
	drop index n5pozprojekt_abas.FKI_n5pozprojekt_abas_pproj_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozprojekt_abas_pproj_pOpak')
	drop index n5pozprojekt_abas.FKI_n5pozprojekt_abas_pproj_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozprojekt_abas_pproj_pKwalifikatorEx')
	drop index n5pozprojekt_abas.FKI_n5pozprojekt_abas_pproj_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5bank_pMiejscowosc')
	drop index n5bank.FKI_n5bank_pMiejscowosc
go

if exists (select * from sysindexes where name='FKI_n5bank_pKraj')
	drop index n5bank.FKI_n5bank_pKraj
go

if exists (select * from sysindexes where name='FKI_n5pozplatnosc_pTransakcja')
	drop index n5pozplatnosc.FKI_n5pozplatnosc_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pUrzadSkarbowy')
	drop index n5pit11.FKI_n5pit11_pt11_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pUzytRej')
	drop index n5pit11.FKI_n5pit11_pt11_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pZadanie')
	drop index n5pit11.FKI_n5pit11_pt11_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pSchematDekr')
	drop index n5pit11.FKI_n5pit11_pt11_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pDowKsieg')
	drop index n5pit11.FKI_n5pit11_pt11_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pTransakcja')
	drop index n5pit11.FKI_n5pit11_pt11_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pUzytModyf')
	drop index n5pit11.FKI_n5pit11_pt11_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5pit11_pt11_pPodatnik')
	drop index n5pit11.FKI_n5pit11_pt11_pPodatnik
go

if exists (select * from sysindexes where name='FKI_n5schematdekr_pRejestrDok')
	drop index n5schematdekr.FKI_n5schematdekr_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5schematdekr_pDziennik')
	drop index n5schematdekr.FKI_n5schematdekr_pDziennik
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pSposobPlatnosci')
	drop index n5zamowienie.FKI_n5zamowienie_pSposobPlatnosci
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlient')
	drop index n5zamowienie.FKI_n5zamowienie_pKlient
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlient_JO')
	drop index n5zamowienie.FKI_n5zamowienie_pKlient_JO
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKlientPracownik')
	drop index n5zamowienie.FKI_n5zamowienie_pKlientPracownik
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pUzytRej')
	drop index n5zamowienie.FKI_n5zamowienie_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pZadanie')
	drop index n5zamowienie.FKI_n5zamowienie_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pRejestrDok')
	drop index n5zamowienie.FKI_n5zamowienie_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pDowodKsieg')
	drop index n5zamowienie.FKI_n5zamowienie_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pSchematDekr')
	drop index n5zamowienie.FKI_n5zamowienie_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pWaluta')
	drop index n5zamowienie.FKI_n5zamowienie_pWaluta
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pKwalifikatorEx')
	drop index n5zamowienie.FKI_n5zamowienie_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pZamowienie')
	drop index n5zamowienie.FKI_n5zamowienie_pZamowienie
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_zam_pSposobDostawy')
	drop index n5zamowienie.FKI_n5zamowienie_zam_pSposobDostawy
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_zam_pUzytModyf')
	drop index n5zamowienie.FKI_n5zamowienie_zam_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_pDokStatus')
	drop index n5zamowienie.FKI_n5zamowienie_pDokStatus
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_zam_pMiejscowosc_dost')
	drop index n5zamowienie.FKI_n5zamowienie_zam_pMiejscowosc_dost
go

if exists (select * from sysindexes where name='FKI_n5zamowienie_zam_pKraj_dost')
	drop index n5zamowienie.FKI_n5zamowienie_zam_pKraj_dost
go

if exists (select * from sysindexes where name='WFKI_n5polrab_wpProdGrupa')
	drop index n5polrab.WFKI_n5polrab_wpProdGrupa
go

if exists (select * from sysindexes where name='FKI_n5polrab_pOpak')
	drop index n5polrab.FKI_n5polrab_pOpak
go

if exists (select * from sysindexes where name='WFKI_n5polrab_wpKlientGrupa')
	drop index n5polrab.WFKI_n5polrab_wpKlientGrupa
go

if exists (select * from sysindexes where name='FKI_n5polrab_polrab_pWalutaCeny')
	drop index n5polrab.FKI_n5polrab_polrab_pWalutaCeny
go

if exists (select * from sysindexes where name='FKI_n5polrab_polrab_pJednOrg')
	drop index n5polrab.FKI_n5polrab_polrab_pJednOrg
go

if exists (select * from sysindexes where name='FKI_n5realprod_pUzytRej')
	drop index n5realprod.FKI_n5realprod_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5realprod_pRejestrDok')
	drop index n5realprod.FKI_n5realprod_pRejestrDok
go

if exists (select * from sysindexes where name='FKI_n5realprod_pDowodKsieg')
	drop index n5realprod.FKI_n5realprod_pDowodKsieg
go

if exists (select * from sysindexes where name='FKI_n5realprod_pSchematDekr')
	drop index n5realprod.FKI_n5realprod_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5realprod_pMagazyn')
	drop index n5realprod.FKI_n5realprod_pMagazyn
go

if exists (select * from sysindexes where name='FKI_n5realprod_pZlecProd')
	drop index n5realprod.FKI_n5realprod_pZlecProd
go

if exists (select * from sysindexes where name='FKI_n5realprod_pKwalifikatorEx')
	drop index n5realprod.FKI_n5realprod_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5realprod_realprod_pUzytModyf')
	drop index n5realprod.FKI_n5realprod_realprod_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5realprod_pDokStatus')
	drop index n5realprod.FKI_n5realprod_pDokStatus
go

-- skipped virtual table: n5pit4r
if exists (select * from sysindexes where name='FKI_n5prop_prop_pZlecProd')
	drop index n5prop.FKI_n5prop_prop_pZlecProd
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pEgzemplarz')
	drop index n5prop.FKI_n5prop_prop_pEgzemplarz
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pZasob')
	drop index n5prop.FKI_n5prop_prop_pZasob
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pTypZasobu')
	drop index n5prop.FKI_n5prop_prop_pTypZasobu
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pOperacja')
	drop index n5prop.FKI_n5prop_prop_pOperacja
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pProdukt')
	drop index n5prop.FKI_n5prop_prop_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pOpak')
	drop index n5prop.FKI_n5prop_prop_pOpak
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pDokMag')
	drop index n5prop.FKI_n5prop_prop_pDokMag
go

if exists (select * from sysindexes where name='FKI_n5prop_prop_pRealProd')
	drop index n5prop.FKI_n5prop_prop_pRealProd
go

if exists (select * from sysindexes where name='FKI_n5pozinwark_pia_pProdukt')
	drop index n5pozinwark.FKI_n5pozinwark_pia_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozinwark_pia_pOpak')
	drop index n5pozinwark.FKI_n5pozinwark_pia_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozinwark_pia_pKwalifikatorEx')
	drop index n5pozinwark.FKI_n5pozinwark_pia_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5grupaklient_pGrupaNadrzedna')
	drop index n5grupaklient.FKI_n5grupaklient_pGrupaNadrzedna
go

if exists (select * from sysindexes where name='FKI_n5grupaklient_pWalutaLimitu')
	drop index n5grupaklient.FKI_n5grupaklient_pWalutaLimitu
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pUrzadSkarbowy')
	drop index n5pit4.FKI_n5pit4_pt4_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pUzytRej')
	drop index n5pit4.FKI_n5pit4_pt4_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pZadanie')
	drop index n5pit4.FKI_n5pit4_pt4_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pSchematDekr')
	drop index n5pit4.FKI_n5pit4_pt4_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pDowKsieg')
	drop index n5pit4.FKI_n5pit4_pt4_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pTransakcja')
	drop index n5pit4.FKI_n5pit4_pt4_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5pit4_pt4_pUzytModyf')
	drop index n5pit4.FKI_n5pit4_pt4_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5klient_opakowanie_klop_pOpakowanie')
	drop index n5klient_opakowanie.FKI_n5klient_opakowanie_klop_pOpakowanie
go

if exists (select * from sysindexes where name='FKI_n5proglojal_proloj_pKlient')
	drop index n5proglojal.FKI_n5proglojal_proloj_pKlient
go

if exists (select * from sysindexes where name='FKI_n5proglojal_proloj_pPracKlient')
	drop index n5proglojal.FKI_n5proglojal_proloj_pPracKlient
go

if exists (select * from sysindexes where name='FKI_n5proglojal_proloj_pSprzedaz')
	drop index n5proglojal.FKI_n5proglojal_proloj_pSprzedaz
go

if exists (select * from sysindexes where name='FKI_n5proglojal_proloj_pDokMag')
	drop index n5proglojal.FKI_n5proglojal_proloj_pDokMag
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pProdukt')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pProdukt
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pOpak')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pOpak
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pRecepta')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pRecepta
go

if exists (select * from sysindexes where name='FKI_n5pozzlecprod_pKwalifikatorEx')
	drop index n5pozzlecprod.FKI_n5pozzlecprod_pKwalifikatorEx
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pUzytRej')
	drop index n5rozlcit.FKI_n5rozlcit_pUzytRej
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pZadanie')
	drop index n5rozlcit.FKI_n5rozlcit_pZadanie
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pSchematDekr')
	drop index n5rozlcit.FKI_n5rozlcit_pSchematDekr
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pDowKsieg')
	drop index n5rozlcit.FKI_n5rozlcit_pDowKsieg
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pTransakcja')
	drop index n5rozlcit.FKI_n5rozlcit_pTransakcja
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_pUrzadSkarbowy')
	drop index n5rozlcit.FKI_n5rozlcit_pUrzadSkarbowy
go

if exists (select * from sysindexes where name='FKI_n5rozlcit_cit2_pUzytModyf')
	drop index n5rozlcit.FKI_n5rozlcit_cit2_pUzytModyf
go

if exists (select * from sysindexes where name='FKI_n5plsklwyn_pSchemat')
	drop index n5plsklwyn.FKI_n5plsklwyn_pSchemat
go

if exists (select * from sysindexes where name='FKI_n5plsklwyn_pTerminNal')
	drop index n5plsklwyn.FKI_n5plsklwyn_pTerminNal
go

if exists (select * from sysindexes where name='FKI_n5maszyna_toral_masz_pKwalifikatorEx')
	drop index n5maszyna_toral.FKI_n5maszyna_toral_masz_pKwalifikatorEx
go

-- end of script ----
