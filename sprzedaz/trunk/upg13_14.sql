-- upgrade from c:\sprzedaz\db13.desc to c:\sprzedaz\db14.desc
-- generated: 28.06.2018 14:42:58
 use %DBNAME% 
 go 
--========= BEGIN INJECT A ==============
-- alter table n5sprzedaz
sp_rename 'n5sprzedaz','upg___n5sprzedaz','OBJECT'
go
-- alter table n5transakcja
sp_rename 'n5transakcja','upg___n5transakcja','OBJECT'
go
-- alter table n5produkt
sp_rename 'n5produkt','upg___n5produkt','OBJECT'
go
-- alter table n5rejestrdok
sp_rename 'n5rejestrdok','upg___n5rejestrdok','OBJECT'
go
-- alter table n5dokmag
sp_rename 'n5dokmag','upg___n5dokmag','OBJECT'
go
-- alter table n5klient
sp_rename 'n5klient','upg___n5klient','OBJECT'
go
-- alter table n5zakup
sp_rename 'n5zakup','upg___n5zakup','OBJECT'
go
-- alter table n5platnosc
sp_rename 'n5platnosc','upg___n5platnosc','OBJECT'
go
-- alter table n5transakcja_operacja
sp_rename 'n5transakcja_operacja','upg___n5transakcja_operacja','OBJECT'
go
-- alter table n5dekret
sp_rename 'n5dekret','upg___n5dekret','OBJECT'
go
-- alter table n5firma
sp_rename 'n5firma','upg___n5firma','OBJECT'
go
-- alter table n5pozplatnosc
sp_rename 'n5pozplatnosc','upg___n5pozplatnosc','OBJECT'
go
-- alter table n5zamowienie
sp_rename 'n5zamowienie','upg___n5zamowienie','OBJECT'
go
--========= END INJECT A ==============
--========= BEGIN INJECT B ==============
create table n5sprzedaz
(
	IdObj integer not null,
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
	curNetto5 decimal(12,2) not null,
	curVat5 decimal(12,2) not null,
	-- [virtual] curBrutto5,
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
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	-- [virtual] cInternalAllowChanges,
	sprzed_cUETT varchar(1) not null,
	sprzed_pPKPIR integer not null,
	sprzed_strNrDokFisk varchar(32) not null,
	sprzed_curRata decimal(12,2) not null,
	-- [virtual] sprzed_listRata,
	sprzed_pSposobDostawy integer not null,
	sprzed_pHandlowiec integer not null,
	sprzed_pUzytModyf integer not null,
	curSumaWalBrutto decimal(12,2) not null,
	sprzed_iNrRachBank integer not null,
	-- [virtual] sprzed_listZalacznik,
	pDokStatus integer not null,
	curNetto8 decimal(12,2) not null,
	curVat8 decimal(12,2) not null,
	-- [virtual] curBrutto8,
	curNetto23 decimal(12,2) not null,
	curVat23 decimal(12,2) not null,
	-- [virtual] curBrutto23,
	curNetto23oo decimal(12,2) not null,
	curVat23oo decimal(12,2) not null,
	-- [virtual] curBrutto23oo,
	sprzed_pDostawa integer not null,
	sprzed_cZmianaEksport varchar(1) not null,
	sprzed_strNrDokJPK varchar(64) not null,
	sprzed_iJPKVAT integer not null,
	sprzed_iJPKVAT_0 integer not null,
	sprzed_iJPKVAT_np integer not null,
	sprzed_curJPK_K36 decimal(12,2) not null,
	sprzed_cBezTransakcji varchar(1) not null,
	sprzed_dCreated datetime not null,
	sprzed_tCreated integer not null,
	sprzed_dLastSaved datetime not null,
	sprzed_tLastSaved integer not null,
	sprzed_strPrzyczynaKorekty varchar(512) not null,
	sprzed_strOkresKorekty varchar(512) not null,
	sprzed_cSplit varchar(1) not null,
	sprzed_strNazwa_dost varchar(128) not null,
	sprzed_strUlica_dost varchar(64) not null,
	sprzed_strNrDomu_dost varchar(8) not null,
	sprzed_strNrLokalu_dost varchar(8) not null,
	sprzed_strKod_dost varchar(8) not null,
	sprzed_strPoczta_dost varchar(64) not null,
	sprzed_pMiejscowosc_dost integer not null,
	sprzed_pKraj_dost integer not null,
	sprzed_curSzerGeogr_dost decimal(12,2) not null,
	sprzed_curDlugGeogr_dost decimal(12,2) not null
)
go

create table n5transakcja
(
	IdObj integer not null,
	VersionId integer not null,
	strSymTrans varchar(64) not null,
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
	pNotaOds integer not null,
	trn_eRodzaj integer not null,
	trn_curKurs decimal(14,4) not null,
	trn_pHandlowiec integer not null,
	trn_curWnVAT decimal(12,2) not null,
	trn_curMaVAT decimal(12,2) not null
)
go

create table n5produkt
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNazwaMiedzynarodowa varchar(128) not null,
	strIndeks varchar(32) not null,
	prod_pKodCelny integer not null,
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
	prod_cWyrob varchar(1) not null,
	prod_cSurowiec varchar(1) not null,
	prod_pDostawca integer not null,
	prod_cRolny varchar(1) not null,
	prod_strCN varchar(32) not null,
	prod_strCPC varchar(32) not null,
	prod_strNazwaObcojezyczna1 varchar(128) not null,
	prod_strNazwaObcojezyczna2 varchar(128) not null,
	prod_strNazwaObcojezyczna3 varchar(128) not null,
	prod_pKrajPoch integer not null,
	prod_cCheckPrice varchar(1) not null,
	prod_nCzasDostawy integer not null,
	prod_cCzasDostawyUwzglednij varchar(1) not null,
	prod_pPaletaKolorow integer not null,
	prod_pTabelaRozmiarow integer not null,
	prod_iDataWaznosci integer not null,
	prod_iNrFundRolny integer not null,
	prod_pProdMag integer not null,
	prod_strPKWiU2008 varchar(32) not null,
	prod_nVAT integer not null,
	prod_cProdEtyk varchar(1) not null,
	prod_pPracownik integer not null,
	prod_cTowarRot varchar(1) not null,
	prod_cTowarZam varchar(1) not null,
	prod_curMinWartZam decimal(12,2) not null,
	prod_strOpisZam varchar(64) not null,
	prod_cDoSprzed varchar(1) not null,
	prod_pZamiennik1 integer not null,
	prod_pZamiennik2 integer not null,
	prod_pZamiennik3 integer not null,
	prod_pZamiennik4 integer not null,
	prod_pZamiennik5 integer not null,
	prod_cZmianaEksport varchar(1) not null,
	prod_eRodzaj_VATUE integer not null,
	prod_cPublic varchar(1) not null,
	prod_strPublicName varchar(512) not null,
	prod_pGrupaProdAlt integer not null
)
go

create table n5rejestrdok
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	eTyp integer not null,
	strFormatNumeracji varchar(32) not null,
	strFormatNumeracji2 varchar(32) not null,
	eAktywny integer not null,
	nInternalID integer not null,
	nLicznik integer not null,
	strKonfiguracja varchar(1024) not null,
	nLicznik2 integer not null,
	pDefSchematdekr integer not null,
	dDataZamk datetime not null,
	wrefParam1 integer not null,
	wrefParam1_wrt integer not null,
	wrefParam2 integer not null,
	wrefParam2_wrt integer not null,
	nParam3 integer not null,
	pRokKsieg integer not null,
	rejdok_eZasadaRapKas integer not null,
	rejdok_strFormatNumeracji3 varchar(32) not null,
	rejdok_nLicznik3 integer not null,
	rejdok_pDefSchematdekr2 integer not null,
	rejdok_pDefKlient integer not null,
	rejdok_strSkrot varchar(32) not null,
	rejdok_strKonfiguracja2 varchar(1024) not null,
	rejdok_dDataBK datetime not null,
	rejdok_strTypDokZrodWyn varchar(8) not null,
	rejdok_pRejestrParam4 integer not null,
	-- [virtual] rejdok_fFK_XML,
	rejdok_iNrRachBank integer not null,
	-- [virtual] rejdok_listMagazyn,
	rejdok_iJPKVAT integer not null,
	rejdok_pRejestrDok integer not null
)
go

create table n5dokmag
(
	IdObj integer not null,
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
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	dDataRezerw datetime not null,
	tCzasRezerw integer not null,
	-- [virtual] dm_listEgzemplarze,
	dm_pSposobDostawy integer not null,
	dm_strNrDokObcy varchar(32) not null,
	dm_pUzytModyf integer not null,
	dm_strNrPartii varchar(64) not null,
	-- [virtual] zak_listZalacznik,
	pDokStatus integer not null,
	pPracownik integer not null,
	pObiektKlienta integer not null,
	dm_cZmianaEksport varchar(1) not null,
	dm_dCreated datetime not null,
	dm_tCreated integer not null,
	dm_dLastSaved datetime not null,
	dm_tLastSaved integer not null,
	dm_strNazwa_dost varchar(128) not null,
	dm_strUlica_dost varchar(64) not null,
	dm_strNrDomu_dost varchar(8) not null,
	dm_strNrLokalu_dost varchar(8) not null,
	dm_strKod_dost varchar(8) not null,
	dm_strPoczta_dost varchar(64) not null,
	dm_pMiejscowosc_dost integer not null,
	dm_pKraj_dost integer not null,
	dm_curSzerGeogr_dost decimal(12,2) not null,
	dm_curDlugGeogr_dost decimal(12,2) not null
)
go

create table n5klient
(
	IdObj integer not null,
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
	pKraj integer not null,
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
	strUpodobania varchar(1024) not null,
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
	pKrajSDB integer not null,
	curSzerGeogrSDB decimal(12,2) not null,
	curDlugGeogrSDB decimal(12,2) not null,
	eWiarFin integer not null,
	curLimitKred decimal(12,2) not null,
	pWalutaLimitu integer not null,
	strHaslo varchar(32) not null,
	curObroty decimal(12,2) not null,
	nOcena integer not null,
	dDataOceny datetime not null,
	pSposobPlatnosci integer not null,
	kli_strILN varchar(20) not null,
	kli_strDTOrganWyst varchar(255) not null,
	kli_dDTDataWyst datetime not null,
	kli_strIndeksNaszaFirma varchar(32) not null,
	kli_eZestawCenowy integer not null,
	kli_cBlokadaSprz varchar(1) not null,
	kli_eNazwaProduktu integer not null,
	kli_pKursIndywidualnyWaluta integer not null,
	kli_curKursIndywidualnyWartosc decimal(14,4) not null,
	kli_iNrRachBank integer not null,
	kli_cDokumentyInfo varchar(1) not null,
	kli_strRodzajProd varchar(512) not null,
	kli_eTyp integer not null,
	kli_cRodzajDostawcy varchar(1) not null,
	kli_iTerminSkonta integer not null,
	kli_curWartSkonta decimal(12,2) not null,
	kli_cUmowa varchar(1) not null,
	kli_strBonusy varchar(128) not null,
	kli_cCennik varchar(1) not null,
	kli_dDataCennika datetime not null,
	kli_strDostawa varchar(64) not null,
	kli_strCzasRealZam varchar(64) not null,
	kli_curMinWartZam decimal(12,2) not null,
	kli_strOpisZam varchar(64) not null,
	kli_pGrupaProd integer not null,
	kli_dDataKart datetime not null,
	kli_cCzynnyPodatnikVAT varchar(1) not null,
	kli_cZmianaEksport varchar(1) not null,
	kli_pSposobDostawy integer not null,
	kli_cVATUE varchar(1) not null,
	kli_dDataVATUE datetime not null,
	kli_cSplit varchar(1) not null
)
go

create table n5zakup
(
	IdObj integer not null,
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
	curNetto5 decimal(12,2) not null,
	curVat5 decimal(12,2) not null,
	-- [virtual] curBrutto5,
	pPopZAkup integer not null,
	curSumaWal decimal(12,2) not null,
	pWaluta integer not null,
	eZwOpSprz integer not null,
	eTypZakup integer not null,
	pRozlVat integer not null,
	curKurs decimal(14,4) not null,
	cAutoCalc varchar(1) not null,
	cNaliczajClo varchar(1) not null,
	-- [virtual] fXMLCopy,
	strExtra1 varchar(32) not null,
	strExtra2 varchar(128) not null,
	dExtra3 datetime not null,
	curExtra4 decimal(12,2) not null,
	curExtra5 decimal(12,2) not null,
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	curSumaOplatyZagr decimal(12,2) not null,
	curSumaClo decimal(12,2) not null,
	curSumaAkcyza decimal(12,2) not null,
	curSumaOplatyKraj decimal(12,2) not null,
	pTransakcjaImport integer not null,
	pUrzadCelny integer not null,
	pZamowienie integer not null,
	zak_cUETT varchar(1) not null,
	zak_pPKPIR integer not null,
	zak_curRata decimal(12,2) not null,
	-- [virtual] zak_listRata,
	zak_pSposobDostawy integer not null,
	-- [virtual] cInternalAllowChanges,
	zak_pUzytModyf integer not null,
	zak_iNrRachBank integer not null,
	-- [virtual] zak_listZalacznik,
	zak_pKlientPracownik integer not null,
	pDokStatus integer not null,
	curNetto8 decimal(12,2) not null,
	curVat8 decimal(12,2) not null,
	-- [virtual] curBrutto8,
	curNetto23 decimal(12,2) not null,
	curVat23 decimal(12,2) not null,
	-- [virtual] curBrutto23,
	curNetto23oo decimal(12,2) not null,
	curVat23oo decimal(12,2) not null,
	-- [virtual] curBrutto23oo,
	zak_cZmianaEksport varchar(1) not null,
	zak_strNrDokJPK varchar(64) not null,
	zak_iJPKVAT integer not null,
	zak_iJPKVAT_oo integer not null,
	zak_curJPK_K37 decimal(12,2) not null,
	zak_curJPK_K38 decimal(12,2) not null,
	zak_curJPK_K39 decimal(12,2) not null,
	zak_cBezTransakcji varchar(1) not null,
	zak_dCreated datetime not null,
	zak_tCreated integer not null,
	zak_dLastSaved datetime not null,
	zak_tLastSaved integer not null,
	curVatOdl23 decimal(12,2) not null,
	curVatOdl8 decimal(12,2) not null,
	curVatOdl5 decimal(12,2) not null,
	curVatOdloo decimal(12,2) not null,
	zak_pRozlVat_SP integer not null,
	zak_cSplit varchar(1) not null
)
go

create table n5platnosc
(
	IdObj integer not null,
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
	-- [virtual] cInternalAllowZero,
	plat_pPKPIR integer not null,
	plat_pRapKas integer not null,
	-- [virtual] plat_curSumaPozEwid,
	-- [virtual] plat_curRoznicaKursowa,
	plat_pUzytModyf integer not null,
	-- [virtual] zak_listZalacznik,
	pDokStatus integer not null,
	plat_cZmianaEksport varchar(1) not null,
	plat_dCreated datetime not null,
	plat_tCreated integer not null,
	plat_dLastSaved datetime not null,
	plat_tLastSaved integer not null,
	plat_curVAT decimal(12,2) not null,
	plat_strNrRef varchar(128) not null
)
go

create table n5transakcja_operacja
(
	IdObj integer not null,
	VersionId integer not null,
	trop_pTransakcja integer not null,
	trop_wrefDokument integer not null,
	trop_wrefDokument_wrt integer not null,
	trop_dDataOp datetime not null,
	trop_curWn decimal(12,2) not null,
	trop_curMa decimal(12,2) not null,
	trop_curWnEwid decimal(12,2) not null,
	trop_curMaEwid decimal(12,2) not null,
	trop_curKursOp decimal(14,4) not null,
	trop_strOpis varchar(64) not null,
	trop_pUzytRej integer not null,
	trop_pUzytModyf integer not null,
	trop_curWnVAT decimal(12,2) not null,
	trop_curMaVAT decimal(12,2) not null
)
go

create table n5dekret
(
	IdObj integer not null,
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
	cAuto varchar(1) not null,
	dek_strExtras varchar(128) not null
)
go

create table n5firma
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(255) not null,
	strSkrot varchar(32) not null,
	strUlica varchar(64) not null,
	strNrDomu varchar(8) not null,
	strNrLokalu varchar(8) not null,
	strKod varchar(8) not null,
	strPoczta varchar(64) not null,
	pMiejscowosc integer not null,
	pKraj integer not null,
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
	pMainJO integer not null,
	frm_strILN varchar(20) not null,
	frm_strPESEL varchar(20) not null,
	frm_eTypDT integer not null,
	frm_strNrDokTozsamosci varchar(20) not null,
	frm_strNazwisko varchar(32) not null,
	frm_strImie varchar(32) not null,
	frm_dDataUr datetime not null,
	strRachunek4 varchar(32) not null,
	pBank4 integer not null,
	strPrzeznaczenie4 varchar(64) not null,
	strRachunek5 varchar(32) not null,
	pBank5 integer not null,
	strPrzeznaczenie5 varchar(64) not null,
	strRachunek6 varchar(32) not null,
	pBank6 integer not null,
	strPrzeznaczenie6 varchar(64) not null,
	strRachunek7 varchar(32) not null,
	pBank7 integer not null,
	strPrzeznaczenie7 varchar(64) not null,
	strRachunek8 varchar(32) not null,
	pBank8 integer not null,
	strPrzeznaczenie8 varchar(64) not null,
	strRachunek9 varchar(32) not null,
	pBank9 integer not null,
	strPrzeznaczenie9 varchar(64) not null,
	strRachunek10 varchar(32) not null,
	pBank10 integer not null,
	strPrzeznaczenie10 varchar(64) not null,
	frm_cSplit varchar(1) not null
)
go

create table n5pozplatnosc
(
	IdObj integer not null,
	VersionId integer not null,
	curPozKwotaPodm decimal(12,2) not null,
	curPozKwotaEwid decimal(12,2) not null,
	curPozKwotaTrans decimal(12,2) not null,
	curPozKursPodm decimal(14,4) not null,
	curPozKursEwid decimal(14,4) not null,
	pTransakcja integer not null,
	-- [virtual] pplat_curPozRoznicaKursowa,
	pplat_curVAT decimal(12,2) not null
)
go

create table n5zamowienie
(
	IdObj integer not null,
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
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	pZamowienie integer not null,
	zam_strNrDokObcy varchar(32) not null,
	zam_cNaliczajVat varchar(1) not null,
	zam_eWaznoscZam integer not null,
	zam_cKomplet varchar(1) not null,
	zam_curRata decimal(12,2) not null,
	-- [virtual] zam_listRata,
	zam_pSposobDostawy integer not null,
	zam_pUzytModyf integer not null,
	curSumaWalBrutto decimal(12,2) not null,
	zam_iNrRachBank integer not null,
	-- [virtual] zam_listZalacznik,
	pDokStatus integer not null,
	zam_cZmianaEksport varchar(1) not null,
	zam_dCreated datetime not null,
	zam_tCreated integer not null,
	zam_dLastSaved datetime not null,
	zam_tLastSaved integer not null,
	zam_cSplit varchar(1) not null,
	zam_strNazwa_dost varchar(128) not null,
	zam_strUlica_dost varchar(64) not null,
	zam_strNrDomu_dost varchar(8) not null,
	zam_strNrLokalu_dost varchar(8) not null,
	zam_strKod_dost varchar(8) not null,
	zam_strPoczta_dost varchar(64) not null,
	zam_pMiejscowosc_dost integer not null,
	zam_pKraj_dost integer not null,
	zam_curSzerGeogr_dost decimal(12,2) not null,
	zam_curDlugGeogr_dost decimal(12,2) not null
)
go



go 
create procedure upd_n5sprzedaz as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5sprzedaz(
	IdObj,VersionId,strNrDok,dDataWyst,dDataSprzed,dDataPlat,pSposobPlatnosci,pKlient,pKlient_JO,pKlientPracownik
	,pUzytRej,strUwagi,eSposVAT,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp
	,curNetto2,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17
	,curVat17,curNetto22,curVat22,curNetto5,curVat5
	,pPopSprzed,pFaktura,cAutoCalc,curSumaWal,pWaluta,pRozlVat,pZamowienie,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,sprzed_cUETT,sprzed_pPKPIR,sprzed_strNrDokFisk
	,sprzed_curRata,sprzed_pSposobDostawy,sprzed_pHandlowiec,sprzed_pUzytModyf,curSumaWalBrutto,sprzed_iNrRachBank
	,pDokStatus,curNetto8,curVat8,curNetto23,curVat23,curNetto23oo
	,curVat23oo,sprzed_pDostawa,sprzed_cZmianaEksport,sprzed_strNrDokJPK,sprzed_iJPKVAT,sprzed_iJPKVAT_0,sprzed_iJPKVAT_np
	,sprzed_curJPK_K36,sprzed_cBezTransakcji,sprzed_dCreated,sprzed_tCreated,sprzed_dLastSaved,sprzed_tLastSaved,sprzed_strPrzyczynaKorekty,sprzed_strOkresKorekty
	,sprzed_cSplit,sprzed_strNazwa_dost,sprzed_strUlica_dost,sprzed_strNrDomu_dost,sprzed_strNrLokalu_dost,sprzed_strKod_dost,sprzed_strPoczta_dost,sprzed_pMiejscowosc_dost
	,sprzed_pKraj_dost,sprzed_curSzerGeogr_dost,sprzed_curDlugGeogr_dost)
select
	IdObj,VersionId,strNrDok,dDataWyst,dDataSprzed,dDataPlat,pSposobPlatnosci,pKlient,pKlient_JO,pKlientPracownik
	,pUzytRej,strUwagi,eSposVAT,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp
	,curNetto2,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17
	,curVat17,curNetto22,curVat22,curNetto5,curVat5
	,pPopSprzed,pFaktura,cAutoCalc,curSumaWal,pWaluta,pRozlVat,pZamowienie,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,sprzed_cUETT,sprzed_pPKPIR,sprzed_strNrDokFisk
	,sprzed_curRata,sprzed_pSposobDostawy,sprzed_pHandlowiec,sprzed_pUzytModyf,curSumaWalBrutto,sprzed_iNrRachBank
	,pDokStatus,curNetto8,curVat8,curNetto23,curVat23,curNetto23oo
	,curVat23oo,sprzed_pDostawa,sprzed_cZmianaEksport,sprzed_strNrDokJPK,sprzed_iJPKVAT,sprzed_iJPKVAT_0,sprzed_iJPKVAT_np
	,sprzed_curJPK_K36,sprzed_cBezTransakcji,sprzed_dCreated,sprzed_tCreated,sprzed_dLastSaved,sprzed_tLastSaved,'',''
	,'0','','','','','','',0
	,0,0.0,0.0
from upg___n5sprzedaz

go
--TODO:check DEFAULT n5sprzedaz:sprzed_strPrzyczynaKorekty
--TODO:check DEFAULT n5sprzedaz:sprzed_strOkresKorekty
--TODO:check DEFAULT n5sprzedaz:sprzed_cSplit
--TODO:check DEFAULT n5sprzedaz:sprzed_strNazwa_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_strUlica_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_strNrDomu_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_strNrLokalu_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_strKod_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_strPoczta_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_pMiejscowosc_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_pKraj_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_curSzerGeogr_dost
--TODO:check DEFAULT n5sprzedaz:sprzed_curDlugGeogr_dost
exec upd_n5sprzedaz
go
drop procedure upd_n5sprzedaz
go
drop table upg___n5sprzedaz


go
raiserror('transfered n5sprzedaz',0,1)
go


go 
create procedure upd_n5transakcja as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5transakcja(
	IdObj,VersionId,strSymTrans,pWaluta,wrefPodmiot,wrefPodmiot_wrt,dDataRozp,dDataWym,dDataZamk,curWn
	,curMa,eTyp,eStatus,curWnEwid,curMaEwid,eTypOdset,curOdsetkiUmowne,pNotaOds
	,trn_eRodzaj,trn_curKurs,trn_pHandlowiec,trn_curWnVAT,trn_curMaVAT)
select
	IdObj,VersionId,strSymTrans,pWaluta,wrefPodmiot,wrefPodmiot_wrt,dDataRozp,dDataWym,dDataZamk,curWn
	,curMa,eTyp,eStatus,curWnEwid,curMaEwid,eTypOdset,curOdsetkiUmowne,pNotaOds
	,trn_eRodzaj,trn_curKurs,trn_pHandlowiec,0.0,0.0
from upg___n5transakcja

go
--TODO:check DEFAULT n5transakcja:trn_curWnVAT
--TODO:check DEFAULT n5transakcja:trn_curMaVAT
exec upd_n5transakcja
go
drop procedure upd_n5transakcja
go
drop table upg___n5transakcja


go
raiserror('transfered n5transakcja',0,1)
go


go 
create procedure upd_n5produkt as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5produkt(
	IdObj,VersionId,strNazwa,strNazwaMiedzynarodowa,strIndeks,prod_pKodCelny,strKodPKWiU,eVAT,strOpis,pUlotka
	,pInstrukcja,pJednostkaEwid,eAktywny,pGrupaProd,strCecha1,strCecha2,strCecha3
	,eRodzaj,prod_cWyrob,prod_cSurowiec,prod_pDostawca,prod_cRolny,prod_strCN,prod_strCPC
	,prod_strNazwaObcojezyczna1,prod_strNazwaObcojezyczna2,prod_strNazwaObcojezyczna3,prod_pKrajPoch,prod_cCheckPrice,prod_nCzasDostawy,prod_cCzasDostawyUwzglednij,prod_pPaletaKolorow
	,prod_pTabelaRozmiarow,prod_iDataWaznosci,prod_iNrFundRolny,prod_pProdMag,prod_strPKWiU2008,prod_nVAT,prod_cProdEtyk,prod_pPracownik
	,prod_cTowarRot,prod_cTowarZam,prod_curMinWartZam,prod_strOpisZam,prod_cDoSprzed,prod_pZamiennik1,prod_pZamiennik2,prod_pZamiennik3
	,prod_pZamiennik4,prod_pZamiennik5,prod_cZmianaEksport,prod_eRodzaj_VATUE,prod_cPublic,prod_strPublicName,prod_pGrupaProdAlt)
select
	IdObj,VersionId,strNazwa,strNazwaMiedzynarodowa,strIndeks,prod_pKodCelny,strKodPKWiU,eVAT,strOpis,pUlotka
	,pInstrukcja,pJednostkaEwid,eAktywny,pGrupaProd,strCecha1,strCecha2,strCecha3
	,eRodzaj,prod_cWyrob,prod_cSurowiec,prod_pDostawca,prod_cRolny,prod_strCN,prod_strCPC
	,prod_strNazwaObcojezyczna1,prod_strNazwaObcojezyczna2,prod_strNazwaObcojezyczna3,prod_pKrajPoch,prod_cCheckPrice,prod_nCzasDostawy,prod_cCzasDostawyUwzglednij,prod_pPaletaKolorow
	,prod_pTabelaRozmiarow,prod_iDataWaznosci,prod_iNrFundRolny,prod_pProdMag,prod_strPKWiU2008,prod_nVAT,prod_cProdEtyk,prod_pPracownik
	,prod_cTowarRot,prod_cTowarZam,prod_curMinWartZam,prod_strOpisZam,prod_cDoSprzed,prod_pZamiennik1,prod_pZamiennik2,prod_pZamiennik3
	,prod_pZamiennik4,prod_pZamiennik5,prod_cZmianaEksport,prod_eRodzaj_VATUE,prod_cPublic,prod_strPublicName,0
from upg___n5produkt

go
--TODO:check DEFAULT n5produkt:prod_pGrupaProdAlt
exec upd_n5produkt
go
drop procedure upd_n5produkt
go
drop table upg___n5produkt


go
raiserror('transfered n5produkt',0,1)
go


go 
create procedure upd_n5rejestrdok as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5rejestrdok(
	IdObj,VersionId,strNazwa,eTyp,strFormatNumeracji,strFormatNumeracji2,eAktywny,nInternalID,nLicznik,strKonfiguracja
	,nLicznik2,pDefSchematdekr,dDataZamk,wrefParam1,wrefParam1_wrt,wrefParam2,wrefParam2_wrt,nParam3
	,pRokKsieg,rejdok_eZasadaRapKas,rejdok_strFormatNumeracji3,rejdok_nLicznik3,rejdok_pDefSchematdekr2,rejdok_pDefKlient,rejdok_strSkrot,rejdok_strKonfiguracja2
	,rejdok_dDataBK,rejdok_strTypDokZrodWyn,rejdok_pRejestrParam4,rejdok_iNrRachBank,rejdok_iJPKVAT,rejdok_pRejestrDok
	)
select
	IdObj,VersionId,strNazwa,eTyp,strFormatNumeracji,strFormatNumeracji2,eAktywny,nInternalID,nLicznik,strKonfiguracja
	,nLicznik2,pDefSchematdekr,dDataZamk,wrefParam1,wrefParam1_wrt,wrefParam2,wrefParam2_wrt,nParam3
	,pRokKsieg,rejdok_eZasadaRapKas,rejdok_strFormatNumeracji3,rejdok_nLicznik3,rejdok_pDefSchematdekr2,rejdok_pDefKlient,rejdok_strSkrot,rejdok_strKonfiguracja2
	,rejdok_dDataBK,rejdok_strTypDokZrodWyn,rejdok_pRejestrParam4,rejdok_iNrRachBank,rejdok_iJPKVAT,0
	
from upg___n5rejestrdok

go
--TODO:check DEFAULT n5rejestrdok:rejdok_pRejestrDok
exec upd_n5rejestrdok
go
drop procedure upd_n5rejestrdok
go
drop table upg___n5rejestrdok


go
raiserror('transfered n5rejestrdok',0,1)
go


go 
create procedure upd_n5dokmag as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5dokmag(
	IdObj,VersionId,strNrDok,pKlient,pKlient_JO,pKlientPracownik,pDokMag,nNumOper,nTypDok,dDataWyst
	,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid
	,pMagZrod,pMagDocel,cAutoCalc,wrefDokHandl,wrefDokHandl_wrt,strExtra1,strExtra2
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7,curExtra8,curExtra9
	,dExtra10,dDataRezerw,tCzasRezerw,dm_pSposobDostawy,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii
	,pDokStatus,pPracownik,pObiektKlienta,dm_cZmianaEksport,dm_dCreated,dm_tCreated,dm_dLastSaved
	,dm_tLastSaved,dm_strNazwa_dost,dm_strUlica_dost,dm_strNrDomu_dost,dm_strNrLokalu_dost,dm_strKod_dost,dm_strPoczta_dost,dm_pMiejscowosc_dost
	,dm_pKraj_dost,dm_curSzerGeogr_dost,dm_curDlugGeogr_dost)
select
	IdObj,VersionId,strNrDok,pKlient,pKlient_JO,pKlientPracownik,pDokMag,nNumOper,nTypDok,dDataWyst
	,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid
	,pMagZrod,pMagDocel,cAutoCalc,wrefDokHandl,wrefDokHandl_wrt,strExtra1,strExtra2
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7,curExtra8,curExtra9
	,dExtra10,dDataRezerw,tCzasRezerw,dm_pSposobDostawy,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii
	,pDokStatus,pPracownik,pObiektKlienta,dm_cZmianaEksport,dm_dCreated,dm_tCreated,dm_dLastSaved
	,dm_tLastSaved,'','','','','','',0
	,0,0.0,0.0
from upg___n5dokmag

go
--TODO:check DEFAULT n5dokmag:dm_strNazwa_dost
--TODO:check DEFAULT n5dokmag:dm_strUlica_dost
--TODO:check DEFAULT n5dokmag:dm_strNrDomu_dost
--TODO:check DEFAULT n5dokmag:dm_strNrLokalu_dost
--TODO:check DEFAULT n5dokmag:dm_strKod_dost
--TODO:check DEFAULT n5dokmag:dm_strPoczta_dost
--TODO:check DEFAULT n5dokmag:dm_pMiejscowosc_dost
--TODO:check DEFAULT n5dokmag:dm_pKraj_dost
--TODO:check DEFAULT n5dokmag:dm_curSzerGeogr_dost
--TODO:check DEFAULT n5dokmag:dm_curDlugGeogr_dost
exec upd_n5dokmag
go
drop procedure upd_n5dokmag
go
drop table upg___n5dokmag


go
raiserror('transfered n5dokmag',0,1)
go


go 
create procedure upd_n5klient as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5klient(
	IdObj,VersionId,strNazwa,strSkrot,strIndeks,strUlica,strNrDomu,strNrLokalu,strKod,strPoczta
	,pMiejscowosc,pKraj,curSzerGeogr,curDlugGeogr,strTel1,strTel2,strTel3,strTel4
	,strFax,strEmail,strWWW,strRejestr,strSad,strNIP,strREGON,pBranza
	,eTypDT,strNrDokTozsamosci,strRachunek1,strPrzeznaczenie1,pBank1,strRachunek2,strPrzeznaczenie2,pBank2
	,strRachunek3,strPrzeznaczenie3,pBank3,nLiczbaPracownikow,eAktywny,eKlasaKlienta,pWaluta,strUwagi
	,strUpodobania,strCecha1,strCecha2,strCecha3,strNazwisko,strImie,dDataUr,strMiejsceUr
	,strPESEL,ePlec,nWiek,strWydzial,pPracownik,pGrupaKlient,ePrywat,strUlicaSDB
	,strNrDomuSDB,strNrLokaluSDB,strKodSDB,strPocztaSDB,pMiejscowoscSDB,pKrajSDB,curSzerGeogrSDB,curDlugGeogrSDB
	,eWiarFin,curLimitKred,pWalutaLimitu,strHaslo,curObroty,nOcena,dDataOceny,pSposobPlatnosci
	,kli_strILN,kli_strDTOrganWyst,kli_dDTDataWyst,kli_strIndeksNaszaFirma,kli_eZestawCenowy,kli_cBlokadaSprz,kli_eNazwaProduktu,kli_pKursIndywidualnyWaluta
	,kli_curKursIndywidualnyWartosc,kli_iNrRachBank,kli_cDokumentyInfo,kli_strRodzajProd,kli_eTyp,kli_cRodzajDostawcy,kli_iTerminSkonta,kli_curWartSkonta
	,kli_cUmowa,kli_strBonusy,kli_cCennik,kli_dDataCennika,kli_strDostawa,kli_strCzasRealZam,kli_curMinWartZam,kli_strOpisZam
	,kli_pGrupaProd,kli_dDataKart,kli_cCzynnyPodatnikVAT,kli_cZmianaEksport,kli_pSposobDostawy,kli_cVATUE,kli_dDataVATUE,kli_cSplit
	)
select
	IdObj,VersionId,strNazwa,strSkrot,strIndeks,strUlica,strNrDomu,strNrLokalu,strKod,strPoczta
	,pMiejscowosc,pKraj,curSzerGeogr,curDlugGeogr,strTel1,strTel2,strTel3,strTel4
	,strFax,strEmail,strWWW,strRejestr,strSad,strNIP,strREGON,pBranza
	,eTypDT,strNrDokTozsamosci,strRachunek1,strPrzeznaczenie1,pBank1,strRachunek2,strPrzeznaczenie2,pBank2
	,strRachunek3,strPrzeznaczenie3,pBank3,nLiczbaPracownikow,eAktywny,eKlasaKlienta,pWaluta,strUwagi
	,strUpodobania,strCecha1,strCecha2,strCecha3,strNazwisko,strImie,dDataUr,strMiejsceUr
	,strPESEL,ePlec,nWiek,strWydzial,pPracownik,pGrupaKlient,ePrywat,strUlicaSDB
	,strNrDomuSDB,strNrLokaluSDB,strKodSDB,strPocztaSDB,pMiejscowoscSDB,pKrajSDB,curSzerGeogrSDB,curDlugGeogrSDB
	,eWiarFin,curLimitKred,pWalutaLimitu,strHaslo,curObroty,nOcena,dDataOceny,pSposobPlatnosci
	,kli_strILN,kli_strDTOrganWyst,kli_dDTDataWyst,kli_strIndeksNaszaFirma,kli_eZestawCenowy,kli_cBlokadaSprz,kli_eNazwaProduktu,kli_pKursIndywidualnyWaluta
	,kli_curKursIndywidualnyWartosc,kli_iNrRachBank,kli_cDokumentyInfo,kli_strRodzajProd,kli_eTyp,kli_cRodzajDostawcy,kli_iTerminSkonta,kli_curWartSkonta
	,kli_cUmowa,kli_strBonusy,kli_cCennik,kli_dDataCennika,kli_strDostawa,kli_strCzasRealZam,kli_curMinWartZam,kli_strOpisZam
	,kli_pGrupaProd,kli_dDataKart,kli_cCzynnyPodatnikVAT,kli_cZmianaEksport,kli_pSposobDostawy,kli_cVATUE,kli_dDataVATUE,'0'
	
from upg___n5klient

go
--TODO:check DEFAULT n5klient:kli_cSplit
exec upd_n5klient
go
drop procedure upd_n5klient
go
drop table upg___n5klient


go
raiserror('transfered n5klient',0,1)
go


go 
create procedure upd_n5zakup as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5zakup(
	IdObj,VersionId,strNrDok,strNrDokObcy,dDataWyst,dDataOtrzym,dDataZakupu,dDataPlat,pSposobPlatnosci,pDostawca
	,pDostawca_JO,pUzytRej,strUwagi,pZadanie,curSumaNetto,curSumaVAT,curSumaBrutto
	,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp,curNetto2
	,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17,curVat17
	,curNetto22,curVat22,curNetto5,curVat5,pPopZAkup
	,curSumaWal,pWaluta,eZwOpSprz,eTypZakup,pRozlVat,curKurs,cAutoCalc,cNaliczajClo
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,curSumaOplatyZagr,curSumaClo,curSumaAkcyza,curSumaOplatyKraj
	,pTransakcjaImport,pUrzadCelny,pZamowienie,zak_cUETT,zak_pPKPIR,zak_curRata,zak_pSposobDostawy
	,zak_pUzytModyf,zak_iNrRachBank,zak_pKlientPracownik,pDokStatus,curNetto8,curVat8
	,curNetto23,curVat23,curNetto23oo,curVat23oo,zak_cZmianaEksport
	,zak_strNrDokJPK,zak_iJPKVAT,zak_iJPKVAT_oo,zak_curJPK_K37,zak_curJPK_K38,zak_curJPK_K39,zak_cBezTransakcji,zak_dCreated
	,zak_tCreated,zak_dLastSaved,zak_tLastSaved,curVatOdl23,curVatOdl8,curVatOdl5,curVatOdloo,zak_pRozlVat_SP
	,zak_cSplit)
select
	IdObj,VersionId,strNrDok,strNrDokObcy,dDataWyst,dDataOtrzym,dDataZakupu,dDataPlat,pSposobPlatnosci,pDostawca
	,pDostawca_JO,pUzytRej,strUwagi,pZadanie,curSumaNetto,curSumaVAT,curSumaBrutto
	,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp,curNetto2
	,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17,curVat17
	,curNetto22,curVat22,curNetto5,curVat5,pPopZAkup
	,curSumaWal,pWaluta,eZwOpSprz,eTypZakup,pRozlVat,curKurs,cAutoCalc,cNaliczajClo
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,curSumaOplatyZagr,curSumaClo,curSumaAkcyza,curSumaOplatyKraj
	,pTransakcjaImport,pUrzadCelny,pZamowienie,zak_cUETT,zak_pPKPIR,zak_curRata,zak_pSposobDostawy
	,zak_pUzytModyf,zak_iNrRachBank,zak_pKlientPracownik,pDokStatus,curNetto8,curVat8
	,curNetto23,curVat23,curNetto23oo,curVat23oo,zak_cZmianaEksport
	,zak_strNrDokJPK,zak_iJPKVAT,zak_iJPKVAT_oo,zak_curJPK_K37,zak_curJPK_K38,zak_curJPK_K39,zak_cBezTransakcji,zak_dCreated
	,zak_tCreated,zak_dLastSaved,zak_tLastSaved,curVatOdl23,curVatOdl8,curVatOdl5,curVatOdloo,zak_pRozlVat_SP
	,'0'
from upg___n5zakup

go
--TODO:check DEFAULT n5zakup:zak_cSplit
exec upd_n5zakup
go
drop procedure upd_n5zakup
go
drop table upg___n5zakup


go
raiserror('transfered n5zakup',0,1)
go


go 
create procedure upd_n5platnosc as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5platnosc(
	IdObj,VersionId,dDataOper,wrefPodmiot,wrefPodmiot_wrt,strOpis,pZadanie,pUzytRej,pRejestrDok,pDowodKsieg
	,pSchematDekr,strNrDok,nNumOper,curKwotaPodm,curKursPodm,pWalutaPodm,curKwotaStan
	,curKursEwid,curKwotaEwid,eStatus,plat_pPKPIR,plat_pRapKas
	,plat_pUzytModyf,pDokStatus,plat_cZmianaEksport,plat_dCreated,plat_tCreated,plat_dLastSaved
	,plat_tLastSaved,plat_curVAT,plat_strNrRef)
select
	IdObj,VersionId,dDataOper,wrefPodmiot,wrefPodmiot_wrt,strOpis,pZadanie,pUzytRej,pRejestrDok,pDowodKsieg
	,pSchematDekr,strNrDok,nNumOper,curKwotaPodm,curKursPodm,pWalutaPodm,curKwotaStan
	,curKursEwid,curKwotaEwid,eStatus,plat_pPKPIR,plat_pRapKas
	,plat_pUzytModyf,pDokStatus,plat_cZmianaEksport,plat_dCreated,plat_tCreated,plat_dLastSaved
	,plat_tLastSaved,0.0,''
from upg___n5platnosc

go
--TODO:check DEFAULT n5platnosc:plat_curVAT
--TODO:check DEFAULT n5platnosc:plat_strNrRef
exec upd_n5platnosc
go
drop procedure upd_n5platnosc
go
drop table upg___n5platnosc


go
raiserror('transfered n5platnosc',0,1)
go


go 
create procedure upd_n5transakcja_operacja as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5transakcja_operacja(
	IdObj,VersionId,trop_pTransakcja,trop_wrefDokument,trop_wrefDokument_wrt,trop_dDataOp,trop_curWn,trop_curMa,trop_curWnEwid,trop_curMaEwid
	,trop_curKursOp,trop_strOpis,trop_pUzytRej,trop_pUzytModyf,trop_curWnVAT,trop_curMaVAT)
select
	IdObj,VersionId,trop_pTransakcja,trop_wrefDokument,trop_wrefDokument_wrt,trop_dDataOp,trop_curWn,trop_curMa,trop_curWnEwid,trop_curMaEwid
	,trop_curKursOp,trop_strOpis,trop_pUzytRej,trop_pUzytModyf,0.0,0.0
from upg___n5transakcja_operacja

go
--TODO:check DEFAULT n5transakcja_operacja:trop_curWnVAT
--TODO:check DEFAULT n5transakcja_operacja:trop_curMaVAT
exec upd_n5transakcja_operacja
go
drop procedure upd_n5transakcja_operacja
go
drop table upg___n5transakcja_operacja


go
raiserror('transfered n5transakcja_operacja',0,1)
go


go 
create procedure upd_n5dekret as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5dekret(
	IdObj,VersionId,pKonto,curWn,curMa,dDataKsieg,strOpis,eTyp,eStatus,pTransakcja
	,pKwalifikator,cAuto,dek_strExtras)
select
	IdObj,VersionId,pKonto,curWn,curMa,dDataKsieg,strOpis,eTyp,eStatus,pTransakcja
	,pKwalifikator,cAuto,''
from upg___n5dekret

go
--TODO:check DEFAULT n5dekret:dek_strExtras
exec upd_n5dekret
go
drop procedure upd_n5dekret
go
drop table upg___n5dekret


go
raiserror('transfered n5dekret',0,1)
go


go 
create procedure upd_n5firma as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5firma(
	IdObj,VersionId,strNazwa,strSkrot,strUlica,strNrDomu,strNrLokalu,strKod,strPoczta,pMiejscowosc
	,pKraj,curSzerGeogr,curDlugGeogr,strFax,strTel1,strTel2,strTel3,strEmail
	,strWWW,strRejestr,strSad,strWydzial,eForma,strNIP,strREGON,strEKD
	,strRachunek1,pBank1,strPrzeznaczenie1,strRachunek2,pBank2,strPrzeznaczenie2,strRachunek3,strPrzeznaczenie3
	,pWaluta,pBank3,pUrzadSkarbowyVAT,pUrzadSkarbowyPD,pZUS,pMainJO,frm_strILN
	,frm_strPESEL,frm_eTypDT,frm_strNrDokTozsamosci,frm_strNazwisko,frm_strImie,frm_dDataUr,strRachunek4,pBank4
	,strPrzeznaczenie4,strRachunek5,pBank5,strPrzeznaczenie5,strRachunek6,pBank6,strPrzeznaczenie6,strRachunek7
	,pBank7,strPrzeznaczenie7,strRachunek8,pBank8,strPrzeznaczenie8,strRachunek9,pBank9,strPrzeznaczenie9
	,strRachunek10,pBank10,strPrzeznaczenie10,frm_cSplit)
select
	IdObj,VersionId,strNazwa,strSkrot,strUlica,strNrDomu,strNrLokalu,strKod,strPoczta,pMiejscowosc
	,pKraj,curSzerGeogr,curDlugGeogr,strFax,strTel1,strTel2,strTel3,strEmail
	,strWWW,strRejestr,strSad,strWydzial,eForma,strNIP,strREGON,strEKD
	,strRachunek1,pBank1,strPrzeznaczenie1,strRachunek2,pBank2,strPrzeznaczenie2,strRachunek3,strPrzeznaczenie3
	,pWaluta,pBank3,pUrzadSkarbowyVAT,pUrzadSkarbowyPD,pZUS,pMainJO,frm_strILN
	,frm_strPESEL,frm_eTypDT,frm_strNrDokTozsamosci,frm_strNazwisko,frm_strImie,frm_dDataUr,strRachunek4,pBank4
	,strPrzeznaczenie4,strRachunek5,pBank5,strPrzeznaczenie5,strRachunek6,pBank6,strPrzeznaczenie6,strRachunek7
	,pBank7,strPrzeznaczenie7,strRachunek8,pBank8,strPrzeznaczenie8,strRachunek9,pBank9,strPrzeznaczenie9
	,strRachunek10,pBank10,strPrzeznaczenie10,'0'
from upg___n5firma

go
--TODO:check DEFAULT n5firma:frm_cSplit
exec upd_n5firma
go
drop procedure upd_n5firma
go
drop table upg___n5firma


go
raiserror('transfered n5firma',0,1)
go


go 
create procedure upd_n5pozplatnosc as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozplatnosc(
	IdObj,VersionId,curPozKwotaPodm,curPozKwotaEwid,curPozKwotaTrans,curPozKursPodm,curPozKursEwid,pTransakcja,pplat_curVAT
	)
select
	IdObj,VersionId,curPozKwotaPodm,curPozKwotaEwid,curPozKwotaTrans,curPozKursPodm,curPozKursEwid,pTransakcja,0.0
	
from upg___n5pozplatnosc

go
--TODO:check DEFAULT n5pozplatnosc:pplat_curVAT
exec upd_n5pozplatnosc
go
drop procedure upd_n5pozplatnosc
go
drop table upg___n5pozplatnosc


go
raiserror('transfered n5pozplatnosc',0,1)
go


go 
create procedure upd_n5zamowienie as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5zamowienie(
	IdObj,VersionId,strNrDok,dDataWyst,dDataPlat,dDataReal,dDataAkt,pSposobPlatnosci,pKlient,pKlient_JO
	,pKlientPracownik,pUzytRej,strUwagi,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaWal,pWaluta,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10,pZamowienie,zam_strNrDokObcy,zam_cNaliczajVat,zam_eWaznoscZam,zam_cKomplet
	,zam_curRata,zam_pSposobDostawy,zam_pUzytModyf,curSumaWalBrutto,zam_iNrRachBank,pDokStatus
	,zam_cZmianaEksport,zam_dCreated,zam_tCreated,zam_dLastSaved,zam_tLastSaved,zam_cSplit,zam_strNazwa_dost,zam_strUlica_dost
	,zam_strNrDomu_dost,zam_strNrLokalu_dost,zam_strKod_dost,zam_strPoczta_dost,zam_pMiejscowosc_dost,zam_pKraj_dost,zam_curSzerGeogr_dost,zam_curDlugGeogr_dost
	)
select
	IdObj,VersionId,strNrDok,dDataWyst,dDataPlat,dDataReal,dDataAkt,pSposobPlatnosci,pKlient,pKlient_JO
	,pKlientPracownik,pUzytRej,strUwagi,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaWal,pWaluta,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10,pZamowienie,zam_strNrDokObcy,zam_cNaliczajVat,zam_eWaznoscZam,zam_cKomplet
	,zam_curRata,zam_pSposobDostawy,zam_pUzytModyf,curSumaWalBrutto,zam_iNrRachBank,pDokStatus
	,zam_cZmianaEksport,zam_dCreated,zam_tCreated,zam_dLastSaved,zam_tLastSaved,'0','',''
	,'','','','',0,0,0.0,0.0
	
from upg___n5zamowienie

go
--TODO:check DEFAULT n5zamowienie:zam_cSplit
--TODO:check DEFAULT n5zamowienie:zam_strNazwa_dost
--TODO:check DEFAULT n5zamowienie:zam_strUlica_dost
--TODO:check DEFAULT n5zamowienie:zam_strNrDomu_dost
--TODO:check DEFAULT n5zamowienie:zam_strNrLokalu_dost
--TODO:check DEFAULT n5zamowienie:zam_strKod_dost
--TODO:check DEFAULT n5zamowienie:zam_strPoczta_dost
--TODO:check DEFAULT n5zamowienie:zam_pMiejscowosc_dost
--TODO:check DEFAULT n5zamowienie:zam_pKraj_dost
--TODO:check DEFAULT n5zamowienie:zam_curSzerGeogr_dost
--TODO:check DEFAULT n5zamowienie:zam_curDlugGeogr_dost
exec upd_n5zamowienie
go
drop procedure upd_n5zamowienie
go
drop table upg___n5zamowienie


go
raiserror('transfered n5zamowienie',0,1)
go
--========= END INJECT B ==============
--========= BEGIN INJECT C ==============
--TODO: CHECK ORDER OF UPDATES (when more than 1 collection in object) !! update collections set idCollection=n+1 where idCollection=n
--========= END INJECT C ==============
