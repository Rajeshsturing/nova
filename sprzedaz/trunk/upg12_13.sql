-- upgrade from c:\sprzedaz\db12.desc to c:\sprzedaz\db13.desc
-- generated: 2017-06-29 11:51:14
 use %DBNAME% 
 go 
--========= BEGIN INJECT A ==============
-- alter table n5pozsprzedaz
sp_rename 'n5pozsprzedaz','upg___n5pozsprzedaz','OBJECT'
go
-- alter table n5sprzedaz
sp_rename 'n5sprzedaz','upg___n5sprzedaz','OBJECT'
go
-- alter table n5pozrealprod
sp_rename 'n5pozrealprod','upg___n5pozrealprod','OBJECT'
go
-- alter table n5pkpir
sp_rename 'n5pkpir','upg___n5pkpir','OBJECT'
go
-- alter table n5produkt
sp_rename 'n5produkt','upg___n5produkt','OBJECT'
go
-- alter table n5dowodksieg
sp_rename 'n5dowodksieg','upg___n5dowodksieg','OBJECT'
go
-- alter table n5opsrtrw
sp_rename 'n5opsrtrw','upg___n5opsrtrw','OBJECT'
go
-- alter table n5rejestrdok
sp_rename 'n5rejestrdok','upg___n5rejestrdok','OBJECT'
go
-- alter table n5dokmag
sp_rename 'n5dokmag','upg___n5dokmag','OBJECT'
go
-- alter table n5srtrw
sp_rename 'n5srtrw','upg___n5srtrw','OBJECT'
go
-- alter table n5klient
sp_rename 'n5klient','upg___n5klient','OBJECT'
go
-- alter table n5sposdost
sp_rename 'n5sposdost','upg___n5sposdost','OBJECT'
go
-- alter table n5zakup
sp_rename 'n5zakup','upg___n5zakup','OBJECT'
go
-- alter table n5pozzamowienie
sp_rename 'n5pozzamowienie','upg___n5pozzamowienie','OBJECT'
go
-- alter table n5zadanie
sp_rename 'n5zadanie','upg___n5zadanie','OBJECT'
go
-- alter table n5zlecprod
sp_rename 'n5zlecprod','upg___n5zlecprod','OBJECT'
go
-- alter table n5grupaproduktow
sp_rename 'n5grupaproduktow','upg___n5grupaproduktow','OBJECT'
go
-- alter table n5platnosc
sp_rename 'n5platnosc','upg___n5platnosc','OBJECT'
go
-- alter table n5opakowanie_produktu
sp_rename 'n5opakowanie_produktu','upg___n5opakowanie_produktu','OBJECT'
go
-- alter table n5sposplat
sp_rename 'n5sposplat','upg___n5sposplat','OBJECT'
go
-- alter table n5pozdokmag
sp_rename 'n5pozdokmag','upg___n5pozdokmag','OBJECT'
go
-- alter table n5rapkas
sp_rename 'n5rapkas','upg___n5rapkas','OBJECT'
go
-- alter table n5pozzakup
sp_rename 'n5pozzakup','upg___n5pozzakup','OBJECT'
go
-- alter table n5zamowienie
sp_rename 'n5zamowienie','upg___n5zamowienie','OBJECT'
go
-- alter table n5realprod
sp_rename 'n5realprod','upg___n5realprod','OBJECT'
go
-- alter table n5pozzlecprod
sp_rename 'n5pozzlecprod','upg___n5pozzlecprod','OBJECT'
go
--========= END INJECT A ==============
--========= BEGIN INJECT B ==============
create table n5pozsprzedaz
(
	IdObj integer not null,
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
	curWartBrutto decimal(12,2) not null,
	curCenaBazowaNettoWal decimal(14,4) not null,
	curCenaNettoWal decimal(14,4) not null,
	curWartWal decimal(12,2) not null,
	strUwagi varchar(512) not null,
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
	psprzed_pZadanie integer not null,
	psprzed_pKLOB integer not null,
	curCenaBazowaBruttoWal decimal(14,4) not null,
	curCenaBruttoWal decimal(14,4) not null,
	curWartBruttoWal decimal(12,2) not null,
	pProduktOrg integer not null,
	pOpakOrg integer not null,
	psp_curFundRolny decimal(14,4) not null,
	psp_iNrFundRolny integer not null
)
go

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
	sprzed_tLastSaved integer not null
)
go

create table n5pozrealprod
(
	IdObj integer not null,
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
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	curWspolczynnik decimal(12,2) not null,
	eRodzajWyceny integer not null,
	pozreal_pRecepta integer not null
)
go

create table n5pkpir
(
	IdObj integer not null,
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
	curKol16 decimal(12,2) not null,
	pkpir_wrefDokZrodl integer not null,
	pkpir_wrefDokZrodl_wrt integer not null,
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
	curKosztyBR decimal(12,2) not null,
	strOpisBR varchar(512) not null
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
	prod_strPublicName varchar(512) not null
)
go

create table n5dowodksieg
(
	IdObj integer not null,
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
	cAuto varchar(1) not null,
	dk_pUzytModyf integer not null,
	dk_dCreated datetime not null,
	dk_tCreated integer not null,
	dk_dLastSaved datetime not null,
	dk_tLastSaved integer not null
)
go

create table n5opsrtrw
(
	IdObj integer not null,
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
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	strUwagi varchar(512) not null,
	-- [virtual] fXMLCopy,
	opsrtrw_pPKPIR integer not null,
	opsrtrw_pUzytModyf integer not null
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
	rejdok_iJPKVAT integer not null
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
	dm_tLastSaved integer not null
)
go

create table n5srtrw
(
	IdObj integer not null,
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
	curWspolPod decimal(12,2) not null,
	curWspolBil decimal(12,2) not null,
	eMetAmPod integer not null,
	eMetAmBil integer not null,
	eStatus integer not null,
	nRokProd integer not null,
	srtrw_strIndeks varchar(32) not null,
	srtrw_pJednOrg integer not null,
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
	dExtra10 datetime not null
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
	kli_dDataVATUE datetime not null
)
go

create table n5sposdost
(
	IdObj integer not null,
	VersionId integer not null,
	sposdost_strNazwa varchar(32) not null,
	sposdost_nCzasDostawy integer not null,
	sposdost_cPublic varchar(1) not null,
	sposdost_pUsluga integer not null
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
	zak_pRozlVat_SP integer not null
)
go

create table n5pozzamowienie
(
	IdObj integer not null,
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
	curWartBrutto decimal(12,2) not null,
	curCenaBazowaNettoWal decimal(14,4) not null,
	curCenaNettoWal decimal(14,4) not null,
	curWartWal decimal(12,2) not null,
	strUwagi varchar(512) not null,
	curIloscOpakPoz decimal(14,4) not null,
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
	pzam_curIloscOpakZreal decimal(14,4) not null,
	pzam_dDataReal datetime not null,
	pzam_pZadanie integer not null,
	curCenaBazowaBruttoWal decimal(14,4) not null,
	curCenaBruttoWal decimal(14,4) not null,
	curWartBruttoWal decimal(12,2) not null,
	pProduktOrg integer not null,
	pOpakOrg integer not null
)
go

create table n5zadanie
(
	IdObj integer not null,
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
	pKlientPracownik integer not null,
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
	zad_pRejestrDok integer not null,
	zad_pKLOB integer not null,
	-- [virtual] zad_listRole,
	-- [virtual] zad_fExtras,
	pDokStatus integer not null,
	zad_dCreated datetime not null,
	zad_tCreated integer not null,
	zad_dLastSaved datetime not null,
	zad_tLastSaved integer not null
)
go

create table n5zlecprod
(
	IdObj integer not null,
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
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	pNadZlec integer not null,
	dDataReal datetime not null,
	zlp_pUzytModyf integer not null,
	zlp_eStatus integer not null
)
go

create table n5grupaproduktow
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	pGrupaNadrzedna integer not null,
	grp_strRZC varchar(255) not null,
	grp_strRZSM varchar(255) not null,
	grp_pJednostkaEwid integer not null,
	grp_pDostawca integer not null,
	grp_iDataWaznosci integer not null,
	grp_strIndeks varchar(128) not null,
	grp_pPracownik integer not null,
	grp_strUwagi varchar(512) not null,
	grp_cPublic varchar(1) not null,
	grp_strPublicName varchar(512) not null
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
	plat_tLastSaved integer not null
)
go

create table n5opakowanie_produktu
(
	IdObj integer not null,
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
	pZamiennik integer not null,
	strNazwaMiedzynarodowa varchar(32) not null,
	curIloscMin decimal(14,4) not null,
	curIloscMax decimal(14,4) not null,
	curNarzutMin decimal(14,4) not null,
	curNarzutMax decimal(14,4) not null,
	curNarzutZal decimal(14,4) not null,
	curStCelna decimal(14,4) not null,
	opak_curDlugosc decimal(14,4) not null,
	opak_curSzerokosc decimal(14,4) not null,
	opak_curWysokosc decimal(14,4) not null,
	opak_curObjetosc decimal(14,4) not null,
	opak_curCenaMinNetto decimal(14,4) not null,
	opak_curCenaMinBrutto decimal(14,4) not null,
	opak_pWalutaMinCenySprzed integer not null,
	opak_pWaluta2 integer not null,
	opak_pWaluta3 integer not null,
	opak_pWaluta4 integer not null,
	opak_pWaluta5 integer not null,
	opak_pWaluta6 integer not null,
	opak_eRodzajNrSer integer not null,
	opak_strSerNoMask varchar(64) not null,
	opak_nSerNoLicznik integer not null,
	opak_strRZC varchar(255) not null,
	opak_strRZSM varchar(255) not null,
	opak_pKolor integer not null,
	opak_pRozmiar integer not null,
	-- [virtual] opak_fZdjecie,
	opak_pOpakMag integer not null,
	curMinZamDostawca decimal(14,4) not null,
	curMinZamOdbiorca decimal(14,4) not null,
	opak_curGrubosc decimal(12,2) not null,
	curCenaNetto7 decimal(14,4) not null,
	curCenaBrutto7 decimal(14,4) not null,
	opak_pWaluta7 integer not null,
	curCenaNetto8 decimal(14,4) not null,
	curCenaBrutto8 decimal(14,4) not null,
	opak_pWaluta8 integer not null,
	curCenaNetto9 decimal(14,4) not null,
	curCenaBrutto9 decimal(14,4) not null,
	opak_pWaluta9 integer not null
)
go

create table n5sposplat
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(32) not null,
	nDni integer not null,
	eTyp integer not null,
	strNazwaMiedzynarodowa varchar(32) not null,
	cPublic varchar(1) not null
)
go

create table n5pozdokmag
(
	IdObj integer not null,
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
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	dDataWazn datetime not null,
	pdm_pObiektKlienta integer not null,
	pdm_strNrPartii varchar(64) not null
)
go

create table n5rapkas
(
	IdObj integer not null,
	VersionId integer not null,
	raka_strNrDok varchar(32) not null,
	raka_dDataOd datetime not null,
	raka_dDataDo datetime not null,
	raka_pRejestrDok integer not null,
	raka_pDowodKsieg integer not null,
	raka_pSchematDekr integer not null,
	raka_pPKPIR integer not null,
	raka_pUzytRej integer not null,
	raka_strExtra1 varchar(32) not null,
	raka_strExtra2 varchar(128) not null,
	raka_dExtra3 datetime not null,
	raka_curExtra4 decimal(12,2) not null,
	raka_curExtra5 decimal(12,2) not null,
	raka_pKwalifikatorEx integer not null,
	raka_pUzytModyf integer not null,
	raka_dCreated datetime not null,
	raka_tCreated integer not null,
	raka_dLastSaved datetime not null,
	raka_tLastSaved integer not null
)
go

create table n5pozzakup
(
	IdObj integer not null,
	VersionId integer not null,
	pProdukt integer not null,
	curIloscOpak decimal(14,4) not null,
	pOpak integer not null,
	eVAT integer not null,
	curCenaBrutto decimal(14,4) not null,
	curWartNetto decimal(12,2) not null,
	curVAT decimal(12,2) not null,
	curWartBrutto decimal(12,2) not null,
	curCenaNettoWal decimal(14,4) not null,
	curOplatyZagr decimal(12,2) not null,
	curClo decimal(12,2) not null,
	curAkcyza decimal(12,2) not null,
	curOplatyKraj decimal(12,2) not null,
	strUwagi varchar(512) not null,
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
	pzak_curStCelna decimal(14,4) not null,
	pzak_pZadanie integer not null,
	pzak_curWartWal decimal(12,2) not null,
	pzak_pObiektKlienta integer not null
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
	zam_tLastSaved integer not null
)
go

create table n5realprod
(
	IdObj integer not null,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	nNumOper integer not null,
	-- [virtual] listWyrob,
	-- [virtual] listCzynnosc,
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
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	-- [virtual] realprod_listEgzemplarzeWyroby,
	-- [virtual] realprod_listEgzemplarzeSurowce,
	realprod_pUzytModyf integer not null,
	-- [virtual] zak_listZalacznik,
	-- [virtual] realprod_listZasoby,
	pDokStatus integer not null
)
go

create table n5pozzlecprod
(
	IdObj integer not null,
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
	pKwalifikatorEx integer not null,
	strExtra6 varchar(128) not null,
	strExtra7 varchar(128) not null,
	curExtra8 decimal(12,2) not null,
	curExtra9 decimal(12,2) not null,
	dExtra10 datetime not null,
	curIloscOpakPoz decimal(14,4) not null,
	prp_curIloscOpakPozWyd decimal(14,4) not null,
	prp_curIloscOpakPozProd decimal(14,4) not null
)
go

create table n5straznik_cen
(
	IdObj integer not null,
	VersionId integer not null,
	scs_strNazwa varchar(128) not null,
	scs_wpProdGrupa integer not null,
	scs_wpProdGrupa_wrt integer not null,
	scs_wpKlientGrupa integer not null,
	scs_wpKlientGrupa_wrt integer not null,
	scs_curModyfikator decimal(12,2) not null,
	scs_eZestawCenowy integer not null,
	scs_eAktywny integer not null,
	scs_strExtra1 varchar(32) not null,
	scs_strExtra2 varchar(128) not null,
	scs_dExtra3 datetime not null,
	scs_curExtra4 decimal(12,2) not null,
	scs_curExtra5 decimal(12,2) not null,
	scs_pKwalifikatorEx integer not null
)
go



go 
create procedure upd_n5pozsprzedaz as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozsprzedaz(
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,curCenaBazNetto,curCenaBazBrutto,curRabat,eVAT,curCenaNetto
	,curCenaBrutto,curWartNetto,curVAT,curWartBrutto,curCenaBazowaNettoWal,curCenaNettoWal,curWartWal,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,psprzed_pZadanie,psprzed_pKLOB
	,curCenaBazowaBruttoWal,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg,psp_curFundRolny,psp_iNrFundRolny,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,curCenaBazNetto,curCenaBazBrutto,curRabat,eVAT,curCenaNetto
	,curCenaBrutto,curWartNetto,curVAT,curWartBrutto,curCenaBazowaNettoWal,curCenaNettoWal,curWartWal,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,psprzed_pZadanie,psprzed_pKLOB
	,curCenaBazowaBruttoWal,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg,psp_curFundRolny,psp_iNrFundRolny,''
	,'',0.0,0.0,{d '1899-12-31'}
from upg___n5pozsprzedaz

go
--TODO:check DEFAULT n5pozsprzedaz:strExtra6
--TODO:check DEFAULT n5pozsprzedaz:strExtra7
--TODO:check DEFAULT n5pozsprzedaz:curExtra8
--TODO:check DEFAULT n5pozsprzedaz:curExtra9
--TODO:check DEFAULT n5pozsprzedaz:dExtra10
exec upd_n5pozsprzedaz
go
drop procedure upd_n5pozsprzedaz
go
drop table upg___n5pozsprzedaz


go
raiserror('transfered n5pozsprzedaz',0,1)
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
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx
	,sprzed_cUETT,sprzed_pPKPIR,sprzed_strNrDokFisk,sprzed_curRata,sprzed_pSposobDostawy,sprzed_pHandlowiec,sprzed_pUzytModyf
	,curSumaWalBrutto,sprzed_iNrRachBank,pDokStatus,curNetto8,curVat8,curNetto23
	,curVat23,curNetto23oo,curVat23oo,sprzed_pDostawa,sprzed_cZmianaEksport,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,sprzed_strNrDokJPK,sprzed_iJPKVAT,sprzed_iJPKVAT_0,sprzed_iJPKVAT_np
	,sprzed_curJPK_K36,sprzed_cBezTransakcji,sprzed_dCreated,sprzed_tCreated,sprzed_dLastSaved,sprzed_tLastSaved)
select
	IdObj,VersionId,strNrDok,dDataWyst,dDataSprzed,dDataPlat,pSposobPlatnosci,pKlient,pKlient_JO,pKlientPracownik
	,pUzytRej,strUwagi,eSposVAT,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp
	,curNetto2,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17
	,curVat17,curNetto22,curVat22,curNetto5,curVat5
	,pPopSprzed,pFaktura,cAutoCalc,curSumaWal,pWaluta,pRozlVat,pZamowienie,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx
	,sprzed_cUETT,sprzed_pPKPIR,sprzed_strNrDokFisk,sprzed_curRata,sprzed_pSposobDostawy,sprzed_pHandlowiec,sprzed_pUzytModyf
	,curSumaWalBrutto,sprzed_iNrRachBank,pDokStatus,curNetto8,curVat8,curNetto23
	,curVat23,curNetto23oo,curVat23oo,sprzed_pDostawa,sprzed_cZmianaEksport,''
	,'',0.0,0.0,{d '1899-12-31'},'',0,0,0
	,0.0,'',{d '1899-12-31'},2500,{d '1899-12-31'},2500
from upg___n5sprzedaz

go
--TODO:check DEFAULT n5sprzedaz:strExtra6
--TODO:check DEFAULT n5sprzedaz:strExtra7
--TODO:check DEFAULT n5sprzedaz:curExtra8
--TODO:check DEFAULT n5sprzedaz:curExtra9
--TODO:check DEFAULT n5sprzedaz:dExtra10
--TODO:check DEFAULT n5sprzedaz:sprzed_strNrDokJPK
--TODO:check DEFAULT n5sprzedaz:sprzed_iJPKVAT
--TODO:check DEFAULT n5sprzedaz:sprzed_iJPKVAT_0
--TODO:check DEFAULT n5sprzedaz:sprzed_iJPKVAT_np
--TODO:check DEFAULT n5sprzedaz:sprzed_curJPK_K36
--TODO:check DEFAULT n5sprzedaz:sprzed_cBezTransakcji
--TODO:check DEFAULT n5sprzedaz:sprzed_dCreated
--TODO:check DEFAULT n5sprzedaz:sprzed_tCreated
--TODO:check DEFAULT n5sprzedaz:sprzed_dLastSaved
--TODO:check DEFAULT n5sprzedaz:sprzed_tLastSaved
exec upd_n5sprzedaz
go
drop procedure upd_n5sprzedaz
go
drop table upg___n5sprzedaz


go
raiserror('transfered n5sprzedaz',0,1)
go


go 
create procedure upd_n5pozrealprod as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozrealprod(
	IdObj,VersionId,pProdukt,pOpak,pMagazyn,pJednOpak,curIloscOpak,pJednEwid,curIloscEwid,curCenaMag
	,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,curWspolczynnik,eRodzajWyceny,pozreal_pRecepta,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,pOpak,pMagazyn,pJednOpak,curIloscOpak,pJednEwid,curIloscEwid,curCenaMag
	,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,curWspolczynnik,eRodzajWyceny,pozreal_pRecepta,'',''
	,0.0,0.0,{d '1899-12-31'}
from upg___n5pozrealprod

go
--TODO:check DEFAULT n5pozrealprod:strExtra6
--TODO:check DEFAULT n5pozrealprod:strExtra7
--TODO:check DEFAULT n5pozrealprod:curExtra8
--TODO:check DEFAULT n5pozrealprod:curExtra9
--TODO:check DEFAULT n5pozrealprod:dExtra10
exec upd_n5pozrealprod
go
drop procedure upd_n5pozrealprod
go
drop table upg___n5pozrealprod


go
raiserror('transfered n5pozrealprod',0,1)
go


go 
create procedure upd_n5pkpir as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pkpir(
	IdObj,VersionId,nNumOper,dDataOper,pRejestrDok,strNrDok,pKlient,strOpis,strUwagi,curWartSprzed
	,curPozPrzych,curZakTow,curKosztZak,curKosztRekl,curWynagrodz,curPozWyd
	,curKol16,pkpir_wrefDokZrodl,pkpir_wrefDokZrodl_wrt,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5
	,pKwalifikatorEx,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10,curKosztyBR,strOpisBR
	)
select
	IdObj,VersionId,nNumOper,dDataOper,pRejestrDok,strNrDok,pKlient,strOpis,strUwagi,curWartSprzed
	,curPozPrzych,curZakTow,curKosztZak,curKosztRekl,curWynagrodz,curPozWyd
	,curKol16,pkpir_wrefDokZrodl,pkpir_wrefDokZrodl_wrt,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5
	,pKwalifikatorEx,'','',0.0,0.0,{d '1899-12-31'},0.0,''
	
from upg___n5pkpir

go
--TODO:check DEFAULT n5pkpir:strExtra6
--TODO:check DEFAULT n5pkpir:strExtra7
--TODO:check DEFAULT n5pkpir:curExtra8
--TODO:check DEFAULT n5pkpir:curExtra9
--TODO:check DEFAULT n5pkpir:dExtra10
--TODO:check DEFAULT n5pkpir:curKosztyBR
--TODO:check DEFAULT n5pkpir:strOpisBR
exec upd_n5pkpir
go
drop procedure upd_n5pkpir
go
drop table upg___n5pkpir


go
raiserror('transfered n5pkpir',0,1)
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
	,prod_pZamiennik4,prod_pZamiennik5,prod_cZmianaEksport,prod_eRodzaj_VATUE,prod_cPublic,prod_strPublicName)
select
	IdObj,VersionId,strNazwa,strNazwaMiedzynarodowa,strIndeks,prod_pKodCelny,strKodPKWiU,eVAT,strOpis,pUlotka
	,pInstrukcja,pJednostkaEwid,eAktywny,pGrupaProd,strCecha1,strCecha2,strCecha3
	,eRodzaj,prod_cWyrob,prod_cSurowiec,prod_pDostawca,prod_cRolny,prod_strCN,prod_strCPC
	,prod_strNazwaObcojezyczna1,prod_strNazwaObcojezyczna2,prod_strNazwaObcojezyczna3,prod_pKrajPoch,prod_cCheckPrice,prod_nCzasDostawy,prod_cCzasDostawyUwzglednij,prod_pPaletaKolorow
	,prod_pTabelaRozmiarow,prod_iDataWaznosci,prod_iNrFundRolny,prod_pProdMag,prod_strPKWiU2008,prod_nVAT,prod_cProdEtyk,prod_pPracownik
	,prod_cTowarRot,prod_cTowarZam,prod_curMinWartZam,prod_strOpisZam,prod_cDoSprzed,prod_pZamiennik1,prod_pZamiennik2,prod_pZamiennik3
	,prod_pZamiennik4,prod_pZamiennik5,prod_cZmianaEksport,0,'',''
from upg___n5produkt

go
--TODO:check DEFAULT n5produkt:prod_eRodzaj_VATUE
--TODO:check DEFAULT n5produkt:prod_cPublic
--TODO:check DEFAULT n5produkt:prod_strPublicName
exec upd_n5produkt
go
drop procedure upd_n5produkt
go
drop table upg___n5produkt


go
raiserror('transfered n5produkt',0,1)
go


go 
create procedure upd_n5dowodksieg as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5dowodksieg(
	IdObj,VersionId,dDataRej,dDataKsieg,strNrDok,nNumDow,strOpis,eTyp,eStatus
	,pUzytRej,pRejestrDok,wrefDokZrod,wrefDokZrod_wrt,cAuto,dk_pUzytModyf,dk_dCreated
	,dk_tCreated,dk_dLastSaved,dk_tLastSaved)
select
	IdObj,VersionId,dDataRej,dDataKsieg,strNrDok,nNumDow,strOpis,eTyp,eStatus
	,pUzytRej,pRejestrDok,wrefDokZrod,wrefDokZrod_wrt,cAuto,dk_pUzytModyf,{d '1899-12-31'}
	,2500,{d '1899-12-31'},2500
from upg___n5dowodksieg

go
--TODO:check DEFAULT n5dowodksieg:dk_dCreated
--TODO:check DEFAULT n5dowodksieg:dk_tCreated
--TODO:check DEFAULT n5dowodksieg:dk_dLastSaved
--TODO:check DEFAULT n5dowodksieg:dk_tLastSaved
exec upd_n5dowodksieg
go
drop procedure upd_n5dowodksieg
go
drop table upg___n5dowodksieg


go
raiserror('transfered n5dowodksieg',0,1)
go


go 
create procedure upd_n5opsrtrw as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5opsrtrw(
	IdObj,VersionId,pSRTRW,nNumOpST,dDataOper,eRodzaj,curWartoscPod,curUmorzPod,curAmortPod,curStawkaPod
	,curWartoscBil,curUmorzBil,curAmortBil,curStawkaBil,dDataAmort,pMUJO,pUzytRej,pPracownik
	,wrefDokument,wrefDokument_wrt,pRejestrDok,pDowodKsieg,pSchematDekr,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,strUwagi,opsrtrw_pPKPIR,opsrtrw_pUzytModyf,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pSRTRW,nNumOpST,dDataOper,eRodzaj,curWartoscPod,curUmorzPod,curAmortPod,curStawkaPod
	,curWartoscBil,curUmorzBil,curAmortBil,curStawkaBil,dDataAmort,pMUJO,pUzytRej,pPracownik
	,wrefDokument,wrefDokument_wrt,pRejestrDok,pDowodKsieg,pSchematDekr,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,strUwagi,opsrtrw_pPKPIR,opsrtrw_pUzytModyf,''
	,'',0.0,0.0,{d '1899-12-31'}
from upg___n5opsrtrw

go
--TODO:check DEFAULT n5opsrtrw:strExtra6
--TODO:check DEFAULT n5opsrtrw:strExtra7
--TODO:check DEFAULT n5opsrtrw:curExtra8
--TODO:check DEFAULT n5opsrtrw:curExtra9
--TODO:check DEFAULT n5opsrtrw:dExtra10
exec upd_n5opsrtrw
go
drop procedure upd_n5opsrtrw
go
drop table upg___n5opsrtrw


go
raiserror('transfered n5opsrtrw',0,1)
go


go 
create procedure upd_n5rejestrdok as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5rejestrdok(
	IdObj,VersionId,strNazwa,eTyp,strFormatNumeracji,strFormatNumeracji2,eAktywny,nInternalID,nLicznik,strKonfiguracja
	,nLicznik2,pDefSchematdekr,dDataZamk,wrefParam1,wrefParam1_wrt,wrefParam2,wrefParam2_wrt,nParam3
	,pRokKsieg,rejdok_eZasadaRapKas,rejdok_strFormatNumeracji3,rejdok_nLicznik3,rejdok_pDefSchematdekr2,rejdok_pDefKlient,rejdok_strSkrot,rejdok_strKonfiguracja2
	,rejdok_dDataBK,rejdok_strTypDokZrodWyn,rejdok_pRejestrParam4,rejdok_iNrRachBank,rejdok_iJPKVAT)
select
	IdObj,VersionId,strNazwa,eTyp,strFormatNumeracji,strFormatNumeracji2,eAktywny,nInternalID,nLicznik,strKonfiguracja
	,nLicznik2,pDefSchematdekr,dDataZamk,wrefParam1,wrefParam1_wrt,wrefParam2,wrefParam2_wrt,nParam3
	,pRokKsieg,rejdok_eZasadaRapKas,rejdok_strFormatNumeracji3,rejdok_nLicznik3,rejdok_pDefSchematdekr2,rejdok_pDefKlient,rejdok_strSkrot,rejdok_strKonfiguracja2
	,rejdok_dDataBK,rejdok_strTypDokZrodWyn,rejdok_pRejestrParam4,rejdok_iNrRachBank,0
from upg___n5rejestrdok

go
--TODO:check DEFAULT n5rejestrdok:rejdok_iJPKVAT
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
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,dDataRezerw,tCzasRezerw,dm_pSposobDostawy
	,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii,pDokStatus,pPracownik,pObiektKlienta,dm_cZmianaEksport
	,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10,dm_dCreated,dm_tCreated,dm_dLastSaved
	,dm_tLastSaved)
select
	IdObj,VersionId,strNrDok,pKlient,pKlient_JO,pKlientPracownik,pDokMag,nNumOper,nTypDok,dDataWyst
	,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid
	,pMagZrod,pMagDocel,cAutoCalc,wrefDokHandl,wrefDokHandl_wrt,strExtra1,strExtra2
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,dDataRezerw,tCzasRezerw,dm_pSposobDostawy
	,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii,pDokStatus,pPracownik,pObiektKlienta,dm_cZmianaEksport
	,'','',0.0,0.0,{d '1899-12-31'},{d '1899-12-31'},2500,{d '1899-12-31'}
	,2500
from upg___n5dokmag

go
--TODO:check DEFAULT n5dokmag:strExtra6
--TODO:check DEFAULT n5dokmag:strExtra7
--TODO:check DEFAULT n5dokmag:curExtra8
--TODO:check DEFAULT n5dokmag:curExtra9
--TODO:check DEFAULT n5dokmag:dExtra10
--TODO:check DEFAULT n5dokmag:dm_dCreated
--TODO:check DEFAULT n5dokmag:dm_tCreated
--TODO:check DEFAULT n5dokmag:dm_dLastSaved
--TODO:check DEFAULT n5dokmag:dm_tLastSaved
exec upd_n5dokmag
go
drop procedure upd_n5dokmag
go
drop table upg___n5dokmag


go
raiserror('transfered n5dokmag',0,1)
go


go 
create procedure upd_n5srtrw as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5srtrw(
	IdObj,VersionId,strNazwa,strNumEwid,strNumSer,strKRST,pGrupa,dDataGwar,eRodzaj,pPracownik
	,strUwagi,pMUJO,nLicznik,curWartoscPod,curUmorzPod,curWartoscBil,curUmorzBil,curStawkaPod
	,curStawkaBil,curWspolPod,curWspolBil,eMetAmPod,eMetAmBil,eStatus,nRokProd,srtrw_strIndeks
	,srtrw_pJednOrg,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,strNazwa,strNumEwid,strNumSer,strKRST,pGrupa,dDataGwar,eRodzaj,pPracownik
	,strUwagi,pMUJO,nLicznik,curWartoscPod,curUmorzPod,curWartoscBil,curUmorzBil,curStawkaPod
	,curStawkaBil,curWspolPod,curWspolBil,eMetAmPod,eMetAmBil,eStatus,nRokProd,srtrw_strIndeks
	,srtrw_pJednOrg,'','',{d '1899-12-31'},0.0,0.0,0,''
	,'',0.0,0.0,{d '1899-12-31'}
from upg___n5srtrw

go
--TODO:check DEFAULT n5srtrw:strExtra1
--TODO:check DEFAULT n5srtrw:strExtra2
--TODO:check DEFAULT n5srtrw:dExtra3
--TODO:check DEFAULT n5srtrw:curExtra4
--TODO:check DEFAULT n5srtrw:curExtra5
--TODO:check DEFAULT n5srtrw:pKwalifikatorEx
--TODO:check DEFAULT n5srtrw:strExtra6
--TODO:check DEFAULT n5srtrw:strExtra7
--TODO:check DEFAULT n5srtrw:curExtra8
--TODO:check DEFAULT n5srtrw:curExtra9
--TODO:check DEFAULT n5srtrw:dExtra10
exec upd_n5srtrw
go
drop procedure upd_n5srtrw
go
drop table upg___n5srtrw


go
raiserror('transfered n5srtrw',0,1)
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
	,kli_pGrupaProd,kli_dDataKart,kli_cCzynnyPodatnikVAT,kli_cZmianaEksport,kli_pSposobDostawy,kli_cVATUE,kli_dDataVATUE)
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
	,kli_pGrupaProd,kli_dDataKart,kli_cCzynnyPodatnikVAT,kli_cZmianaEksport,0,'0',{d '1899-12-31'}
from upg___n5klient

go
--TODO:check DEFAULT n5klient:kli_pSposobDostawy
--TODO:check DEFAULT n5klient:kli_cVATUE
--TODO:check DEFAULT n5klient:kli_dDataVATUE
exec upd_n5klient
go
drop procedure upd_n5klient
go
drop table upg___n5klient


go
raiserror('transfered n5klient',0,1)
go


go 
create procedure upd_n5sposdost as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5sposdost(
	IdObj,VersionId,sposdost_strNazwa,sposdost_nCzasDostawy,sposdost_cPublic,sposdost_pUsluga)
select
	IdObj,VersionId,sposdost_strNazwa,sposdost_nCzasDostawy,'',0
from upg___n5sposdost

go
--TODO:check DEFAULT n5sposdost:sposdost_cPublic
--TODO:check DEFAULT n5sposdost:sposdost_pUsluga
exec upd_n5sposdost
go
drop procedure upd_n5sposdost
go
drop table upg___n5sposdost


go
raiserror('transfered n5sposdost',0,1)
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
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,curSumaOplatyZagr
	,curSumaClo,curSumaAkcyza,curSumaOplatyKraj,pTransakcjaImport,pUrzadCelny,pZamowienie,zak_cUETT,zak_pPKPIR
	,zak_curRata,zak_pSposobDostawy,zak_pUzytModyf,zak_iNrRachBank,zak_pKlientPracownik
	,pDokStatus,curNetto8,curVat8,curNetto23,curVat23,curNetto23oo
	,curVat23oo,zak_cZmianaEksport,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10
	,zak_strNrDokJPK,zak_iJPKVAT,zak_iJPKVAT_oo,zak_curJPK_K37,zak_curJPK_K38,zak_curJPK_K39,zak_cBezTransakcji,zak_dCreated
	,zak_tCreated,zak_dLastSaved,zak_tLastSaved,curVatOdl23,curVatOdl8,curVatOdl5,curVatOdloo,zak_pRozlVat_SP
	)
select
	IdObj,VersionId,strNrDok,strNrDokObcy,dDataWyst,dDataOtrzym,dDataZakupu,dDataPlat,pSposobPlatnosci,pDostawca
	,pDostawca_JO,pUzytRej,strUwagi,pZadanie,curSumaNetto,curSumaVAT,curSumaBrutto
	,pRejestrDok,pDowodKsieg,pSchematDekr,pTransakcja,curNetto0,curNettoZw,curNettoNp,curNetto2
	,curVat2,curNetto3,curVat3,curNetto4,curVat4
	,curNetto7,curVat7,curNetto12,curVat12,curNetto17,curVat17
	,curNetto22,curVat22,curNetto5,curVat5,pPopZAkup
	,curSumaWal,pWaluta,eZwOpSprz,eTypZakup,pRozlVat,curKurs,cAutoCalc,cNaliczajClo
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,curSumaOplatyZagr
	,curSumaClo,curSumaAkcyza,curSumaOplatyKraj,pTransakcjaImport,pUrzadCelny,pZamowienie,zak_cUETT,zak_pPKPIR
	,zak_curRata,zak_pSposobDostawy,zak_pUzytModyf,zak_iNrRachBank,zak_pKlientPracownik
	,pDokStatus,curNetto8,curVat8,curNetto23,curVat23,curNetto23oo
	,curVat23oo,zak_cZmianaEksport,'','',0.0,0.0,{d '1899-12-31'}
	,'',0,0,0.0,0.0,0.0,'',{d '1899-12-31'}
	,2500,{d '1899-12-31'},2500,0.0,0.0,0.0,0.0,0
	
from upg___n5zakup

go
--TODO:check DEFAULT n5zakup:strExtra6
--TODO:check DEFAULT n5zakup:strExtra7
--TODO:check DEFAULT n5zakup:curExtra8
--TODO:check DEFAULT n5zakup:curExtra9
--TODO:check DEFAULT n5zakup:dExtra10
--TODO:check DEFAULT n5zakup:zak_strNrDokJPK
--TODO:check DEFAULT n5zakup:zak_iJPKVAT
--TODO:check DEFAULT n5zakup:zak_iJPKVAT_oo
--TODO:check DEFAULT n5zakup:zak_curJPK_K37
--TODO:check DEFAULT n5zakup:zak_curJPK_K38
--TODO:check DEFAULT n5zakup:zak_curJPK_K39
--TODO:check DEFAULT n5zakup:zak_cBezTransakcji
--TODO:check DEFAULT n5zakup:zak_dCreated
--TODO:check DEFAULT n5zakup:zak_tCreated
--TODO:check DEFAULT n5zakup:zak_dLastSaved
--TODO:check DEFAULT n5zakup:zak_tLastSaved
--TODO:check DEFAULT n5zakup:curVatOdl23
--TODO:check DEFAULT n5zakup:curVatOdl8
--TODO:check DEFAULT n5zakup:curVatOdl5
--TODO:check DEFAULT n5zakup:curVatOdloo
--TODO:check DEFAULT n5zakup:zak_pRozlVat_SP
exec upd_n5zakup
go
drop procedure upd_n5zakup
go
drop table upg___n5zakup


go
raiserror('transfered n5zakup',0,1)
go


go 
create procedure upd_n5pozzamowienie as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozzamowienie(
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,curCenaBazNetto,curCenaBazBrutto,curRabat,eVAT,curCenaNetto
	,curCenaBrutto,curWartNetto,curVAT,curWartBrutto,curCenaBazowaNettoWal,curCenaNettoWal,curWartWal,strUwagi
	,curIloscOpakPoz,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pzam_curIloscOpakZreal
	,pzam_dDataReal,pzam_pZadanie,curCenaBazowaBruttoWal,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,curCenaBazNetto,curCenaBazBrutto,curRabat,eVAT,curCenaNetto
	,curCenaBrutto,curWartNetto,curVAT,curWartBrutto,curCenaBazowaNettoWal,curCenaNettoWal,curWartWal,strUwagi
	,curIloscOpakPoz,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pzam_curIloscOpakZreal
	,pzam_dDataReal,pzam_pZadanie,curCenaBazowaBruttoWal,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg,''
	,'',0.0,0.0,{d '1899-12-31'}
from upg___n5pozzamowienie

go
--TODO:check DEFAULT n5pozzamowienie:strExtra6
--TODO:check DEFAULT n5pozzamowienie:strExtra7
--TODO:check DEFAULT n5pozzamowienie:curExtra8
--TODO:check DEFAULT n5pozzamowienie:curExtra9
--TODO:check DEFAULT n5pozzamowienie:dExtra10
exec upd_n5pozzamowienie
go
drop procedure upd_n5pozzamowienie
go
drop table upg___n5pozzamowienie


go
raiserror('transfered n5pozzamowienie',0,1)
go


go 
create procedure upd_n5zadanie as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5zadanie(
	IdObj,VersionId,nStatus,dDataZlec,tCzasZlec,pZlecajacy,ePriorytet,eTypterminRozp,dDataTerminRozp,tCzasTerminRozp
	,eTypterminZak,strTemat,strOpis,nNaklad,pTypDzialania,pProcedura,wrefSzczegoly,wrefSzczegoly_wrt
	,pNadZadanie,pPopZadanie,pWykonawca,dDataPow,tCzasPow,dDataRozp,tCzasRozp,nZaawansowanie
	,dDataZakon,tCzasZakon,strUwagi,dDataZamk,tCzasZamk,strCecha1,strCecha2,strCecha3
	,dDataTerminZak,tCzasTerminZak,pKlient,pSchematDekretacji,pDowKsieg,dDataPrzyp,tCzasPrzyp
	,nIsSecurity,pKlientPracownik,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx
	,zad_pRejestrDok,zad_pKLOB,pDokStatus,strExtra6,strExtra7,curExtra8
	,curExtra9,dExtra10,zad_dCreated,zad_tCreated,zad_dLastSaved,zad_tLastSaved)
select
	IdObj,VersionId,nStatus,dDataZlec,tCzasZlec,pZlecajacy,ePriorytet,eTypterminRozp,dDataTerminRozp,tCzasTerminRozp
	,eTypterminZak,strTemat,strOpis,nNaklad,pTypDzialania,pProcedura,wrefSzczegoly,wrefSzczegoly_wrt
	,pNadZadanie,pPopZadanie,pWykonawca,dDataPow,tCzasPow,dDataRozp,tCzasRozp,nZaawansowanie
	,dDataZakon,tCzasZakon,strUwagi,dDataZamk,tCzasZamk,strCecha1,strCecha2,strCecha3
	,dDataTerminZak,tCzasTerminZak,pKlient,pSchematDekretacji,pDowKsieg,dDataPrzyp,tCzasPrzyp
	,nIsSecurity,pKlientPracownik,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx
	,zad_pRejestrDok,zad_pKLOB,pDokStatus,'','',0.0
	,0.0,{d '1899-12-31'},{d '1899-12-31'},2500,{d '1899-12-31'},2500
from upg___n5zadanie

go
--TODO:check DEFAULT n5zadanie:strExtra6
--TODO:check DEFAULT n5zadanie:strExtra7
--TODO:check DEFAULT n5zadanie:curExtra8
--TODO:check DEFAULT n5zadanie:curExtra9
--TODO:check DEFAULT n5zadanie:dExtra10
--TODO:check DEFAULT n5zadanie:zad_dCreated
--TODO:check DEFAULT n5zadanie:zad_tCreated
--TODO:check DEFAULT n5zadanie:zad_dLastSaved
--TODO:check DEFAULT n5zadanie:zad_tLastSaved
exec upd_n5zadanie
go
drop procedure upd_n5zadanie
go
drop table upg___n5zadanie


go
raiserror('transfered n5zadanie',0,1)
go


go 
create procedure upd_n5zlecprod as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5zlecprod(
	IdObj,VersionId,strNrDok,dDataWyst,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,pZadanie
	,pKlient,pKlient_JO,pZamowienie,strExtra1,strExtra2,dExtra3,curExtra4
	,curExtra5,pKwalifikatorEx,pNadZlec,dDataReal,zlp_pUzytModyf,zlp_eStatus,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,strNrDok,dDataWyst,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,pZadanie
	,pKlient,pKlient_JO,pZamowienie,strExtra1,strExtra2,dExtra3,curExtra4
	,curExtra5,pKwalifikatorEx,pNadZlec,dDataReal,zlp_pUzytModyf,zlp_eStatus,'',''
	,0.0,0.0,{d '1899-12-31'}
from upg___n5zlecprod

go
--TODO:check DEFAULT n5zlecprod:strExtra6
--TODO:check DEFAULT n5zlecprod:strExtra7
--TODO:check DEFAULT n5zlecprod:curExtra8
--TODO:check DEFAULT n5zlecprod:curExtra9
--TODO:check DEFAULT n5zlecprod:dExtra10
exec upd_n5zlecprod
go
drop procedure upd_n5zlecprod
go
drop table upg___n5zlecprod


go
raiserror('transfered n5zlecprod',0,1)
go


go 
create procedure upd_n5grupaproduktow as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5grupaproduktow(
	IdObj,VersionId,strNazwa,pGrupaNadrzedna,grp_strRZC,grp_strRZSM,grp_pJednostkaEwid,grp_pDostawca,grp_iDataWaznosci,grp_strIndeks
	,grp_pPracownik,grp_strUwagi,grp_cPublic,grp_strPublicName)
select
	IdObj,VersionId,strNazwa,pGrupaNadrzedna,grp_strRZC,grp_strRZSM,grp_pJednostkaEwid,grp_pDostawca,grp_iDataWaznosci,grp_strIndeks
	,grp_pPracownik,grp_strUwagi,'',''
from upg___n5grupaproduktow

go
--TODO:check DEFAULT n5grupaproduktow:grp_cPublic
--TODO:check DEFAULT n5grupaproduktow:grp_strPublicName
exec upd_n5grupaproduktow
go
drop procedure upd_n5grupaproduktow
go
drop table upg___n5grupaproduktow


go
raiserror('transfered n5grupaproduktow',0,1)
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
	,plat_tLastSaved)
select
	IdObj,VersionId,dDataOper,wrefPodmiot,wrefPodmiot_wrt,strOpis,pZadanie,pUzytRej,pRejestrDok,pDowodKsieg
	,pSchematDekr,strNrDok,nNumOper,curKwotaPodm,curKursPodm,pWalutaPodm,curKwotaStan
	,curKursEwid,curKwotaEwid,eStatus,plat_pPKPIR,plat_pRapKas
	,plat_pUzytModyf,pDokStatus,plat_cZmianaEksport,{d '1899-12-31'},2500,{d '1899-12-31'}
	,2500
from upg___n5platnosc

go
--TODO:check DEFAULT n5platnosc:plat_dCreated
--TODO:check DEFAULT n5platnosc:plat_tCreated
--TODO:check DEFAULT n5platnosc:plat_dLastSaved
--TODO:check DEFAULT n5platnosc:plat_tLastSaved
exec upd_n5platnosc
go
drop procedure upd_n5platnosc
go
drop table upg___n5platnosc


go
raiserror('transfered n5platnosc',0,1)
go


go 
create procedure upd_n5opakowanie_produktu as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5opakowanie_produktu(
	IdObj,VersionId,strNazwa,eRodzaj,pOpakowanieJedn,currKrotnosc,curIlosc,strEAN,curWagaNetto,curWagaBrutto
	,pJednostkaWagi,curCenaNetto1,curCenaBrutto1,curCenaNetto2,curCenaBrutto2,curCenaNetto3,curCenaBrutto3,curCenaNetto4
	,curCenaBrutto4,curCenaNetto5,curCenaBrutto5,curCenaNetto6,curCenaBrutto6,pWaluta,strKodOpak,pJednOpak
	,pZamiennik,strNazwaMiedzynarodowa,curIloscMin,curIloscMax,curNarzutMin,curNarzutMax,curNarzutZal,curStCelna
	,opak_curDlugosc,opak_curSzerokosc,opak_curWysokosc,opak_curObjetosc,opak_curCenaMinNetto,opak_curCenaMinBrutto,opak_pWalutaMinCenySprzed,opak_pWaluta2
	,opak_pWaluta3,opak_pWaluta4,opak_pWaluta5,opak_pWaluta6,opak_eRodzajNrSer,opak_strSerNoMask,opak_nSerNoLicznik,opak_strRZC
	,opak_strRZSM,opak_pKolor,opak_pRozmiar,opak_pOpakMag,curMinZamDostawca,curMinZamOdbiorca,opak_curGrubosc
	,curCenaNetto7,curCenaBrutto7,opak_pWaluta7,curCenaNetto8,curCenaBrutto8,opak_pWaluta8,curCenaNetto9,curCenaBrutto9
	,opak_pWaluta9)
select
	IdObj,VersionId,strNazwa,eRodzaj,pOpakowanieJedn,currKrotnosc,curIlosc,strEAN,curWagaNetto,curWagaBrutto
	,pJednostkaWagi,curCenaNetto1,curCenaBrutto1,curCenaNetto2,curCenaBrutto2,curCenaNetto3,curCenaBrutto3,curCenaNetto4
	,curCenaBrutto4,curCenaNetto5,curCenaBrutto5,curCenaNetto6,curCenaBrutto6,pWaluta,strKodOpak,pJednOpak
	,pZamiennik,strNazwaMiedzynarodowa,curIloscMin,curIloscMax,curNarzutMin,curNarzutMax,curNarzutZal,curStCelna
	,opak_curDlugosc,opak_curSzerokosc,opak_curWysokosc,opak_curObjetosc,opak_curCenaMinNetto,opak_curCenaMinBrutto,opak_pWalutaMinCenySprzed,opak_pWaluta2
	,opak_pWaluta3,opak_pWaluta4,opak_pWaluta5,opak_pWaluta6,opak_eRodzajNrSer,opak_strSerNoMask,opak_nSerNoLicznik,opak_strRZC
	,opak_strRZSM,opak_pKolor,opak_pRozmiar,opak_pOpakMag,curMinZamDostawca,curMinZamOdbiorca,opak_curGrubosc
	,0.0,0.0,0,0.0,0.0,0,0.0,0.0
	,0
from upg___n5opakowanie_produktu

go
--TODO:check DEFAULT n5opakowanie_produktu:curCenaNetto7
--TODO:check DEFAULT n5opakowanie_produktu:curCenaBrutto7
--TODO:check DEFAULT n5opakowanie_produktu:opak_pWaluta7
--TODO:check DEFAULT n5opakowanie_produktu:curCenaNetto8
--TODO:check DEFAULT n5opakowanie_produktu:curCenaBrutto8
--TODO:check DEFAULT n5opakowanie_produktu:opak_pWaluta8
--TODO:check DEFAULT n5opakowanie_produktu:curCenaNetto9
--TODO:check DEFAULT n5opakowanie_produktu:curCenaBrutto9
--TODO:check DEFAULT n5opakowanie_produktu:opak_pWaluta9
exec upd_n5opakowanie_produktu
go
drop procedure upd_n5opakowanie_produktu
go
drop table upg___n5opakowanie_produktu


go
raiserror('transfered n5opakowanie_produktu',0,1)
go


go 
create procedure upd_n5sposplat as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5sposplat(
	IdObj,VersionId,strNazwa,nDni,eTyp,strNazwaMiedzynarodowa,cPublic)
select
	IdObj,VersionId,strNazwa,nDni,eTyp,strNazwaMiedzynarodowa,''
from upg___n5sposplat

go
--TODO:check DEFAULT n5sposplat:cPublic
exec upd_n5sposplat
go
drop procedure upd_n5sposplat
go
drop table upg___n5sposplat


go
raiserror('transfered n5sposplat',0,1)
go


go 
create procedure upd_n5pozdokmag as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozdokmag(
	IdObj,VersionId,pProdukt,pOpak,nTypDok,pMagZrod,pMagDocel,pJednOpak,curIloscOpak,pJednEwid
	,curIloscEwid,curCenaMag,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,dDataWazn,pdm_pObiektKlienta
	,pdm_strNrPartii,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,pOpak,nTypDok,pMagZrod,pMagDocel,pJednOpak,curIloscOpak,pJednEwid
	,curIloscEwid,curCenaMag,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,dDataWazn,pdm_pObiektKlienta
	,pdm_strNrPartii,'','',0.0,0.0,{d '1899-12-31'}
from upg___n5pozdokmag

go
--TODO:check DEFAULT n5pozdokmag:strExtra6
--TODO:check DEFAULT n5pozdokmag:strExtra7
--TODO:check DEFAULT n5pozdokmag:curExtra8
--TODO:check DEFAULT n5pozdokmag:curExtra9
--TODO:check DEFAULT n5pozdokmag:dExtra10
exec upd_n5pozdokmag
go
drop procedure upd_n5pozdokmag
go
drop table upg___n5pozdokmag


go
raiserror('transfered n5pozdokmag',0,1)
go


go 
create procedure upd_n5rapkas as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5rapkas(
	IdObj,VersionId,raka_strNrDok,raka_dDataOd,raka_dDataDo,raka_pRejestrDok,raka_pDowodKsieg,raka_pSchematDekr,raka_pPKPIR,raka_pUzytRej
	,raka_strExtra1,raka_strExtra2,raka_dExtra3,raka_curExtra4,raka_curExtra5,raka_pKwalifikatorEx,raka_pUzytModyf,raka_dCreated
	,raka_tCreated,raka_dLastSaved,raka_tLastSaved)
select
	IdObj,VersionId,raka_strNrDok,raka_dDataOd,raka_dDataDo,raka_pRejestrDok,raka_pDowodKsieg,raka_pSchematDekr,raka_pPKPIR,raka_pUzytRej
	,raka_strExtra1,raka_strExtra2,raka_dExtra3,raka_curExtra4,raka_curExtra5,raka_pKwalifikatorEx,raka_pUzytModyf,{d '1899-12-31'}
	,2500,{d '1899-12-31'},2500
from upg___n5rapkas

go
--TODO:check DEFAULT n5rapkas:raka_dCreated
--TODO:check DEFAULT n5rapkas:raka_tCreated
--TODO:check DEFAULT n5rapkas:raka_dLastSaved
--TODO:check DEFAULT n5rapkas:raka_tLastSaved
exec upd_n5rapkas
go
drop procedure upd_n5rapkas
go
drop table upg___n5rapkas


go
raiserror('transfered n5rapkas',0,1)
go


go 
create procedure upd_n5pozzakup as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozzakup(
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,eVAT,curCenaBrutto,curWartNetto,curVAT,curWartBrutto
	,curCenaNettoWal,curOplatyZagr,curClo,curAkcyza,curOplatyKraj,strUwagi,strExtra1,strExtra2
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pzak_curStCelna,pzak_pZadanie,pzak_curWartWal,pzak_pObiektKlienta
	,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,eVAT,curCenaBrutto,curWartNetto,curVAT,curWartBrutto
	,curCenaNettoWal,curOplatyZagr,curClo,curAkcyza,curOplatyKraj,strUwagi,strExtra1,strExtra2
	,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pzak_curStCelna,pzak_pZadanie,pzak_curWartWal,pzak_pObiektKlienta
	,'','',0.0,0.0,{d '1899-12-31'}
from upg___n5pozzakup

go
--TODO:check DEFAULT n5pozzakup:strExtra6
--TODO:check DEFAULT n5pozzakup:strExtra7
--TODO:check DEFAULT n5pozzakup:curExtra8
--TODO:check DEFAULT n5pozzakup:curExtra9
--TODO:check DEFAULT n5pozzakup:dExtra10
exec upd_n5pozzakup
go
drop procedure upd_n5pozzakup
go
drop table upg___n5pozzakup


go
raiserror('transfered n5pozzakup',0,1)
go


go 
create procedure upd_n5zamowienie as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5zamowienie(
	IdObj,VersionId,strNrDok,dDataWyst,dDataPlat,dDataReal,dDataAkt,pSposobPlatnosci,pKlient,pKlient_JO
	,pKlientPracownik,pUzytRej,strUwagi,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaWal,pWaluta,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pZamowienie,zam_strNrDokObcy
	,zam_cNaliczajVat,zam_eWaznoscZam,zam_cKomplet,zam_curRata,zam_pSposobDostawy,zam_pUzytModyf,curSumaWalBrutto
	,zam_iNrRachBank,pDokStatus,zam_cZmianaEksport,strExtra6,strExtra7,curExtra8,curExtra9
	,dExtra10,zam_dCreated,zam_tCreated,zam_dLastSaved,zam_tLastSaved)
select
	IdObj,VersionId,strNrDok,dDataWyst,dDataPlat,dDataReal,dDataAkt,pSposobPlatnosci,pKlient,pKlient_JO
	,pKlientPracownik,pUzytRej,strUwagi,eNettoBrutto,pZadanie,curSumaNetto,curSumaVAT
	,curSumaBrutto,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaWal,pWaluta,curKurs
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,pZamowienie,zam_strNrDokObcy
	,zam_cNaliczajVat,zam_eWaznoscZam,zam_cKomplet,zam_curRata,zam_pSposobDostawy,zam_pUzytModyf,curSumaWalBrutto
	,zam_iNrRachBank,pDokStatus,zam_cZmianaEksport,'','',0.0,0.0
	,{d '1899-12-31'},{d '1899-12-31'},2500,{d '1899-12-31'},2500
from upg___n5zamowienie

go
--TODO:check DEFAULT n5zamowienie:strExtra6
--TODO:check DEFAULT n5zamowienie:strExtra7
--TODO:check DEFAULT n5zamowienie:curExtra8
--TODO:check DEFAULT n5zamowienie:curExtra9
--TODO:check DEFAULT n5zamowienie:dExtra10
--TODO:check DEFAULT n5zamowienie:zam_dCreated
--TODO:check DEFAULT n5zamowienie:zam_tCreated
--TODO:check DEFAULT n5zamowienie:zam_dLastSaved
--TODO:check DEFAULT n5zamowienie:zam_tLastSaved
exec upd_n5zamowienie
go
drop procedure upd_n5zamowienie
go
drop table upg___n5zamowienie


go
raiserror('transfered n5zamowienie',0,1)
go


go 
create procedure upd_n5realprod as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5realprod(
	IdObj,VersionId,strNrDok,nNumOper,dDataWyst,pUzytRej,pRejestrDok
	,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid,pMagazyn,cAutoCalc,pZlecProd,strExtra1
	,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,realprod_pUzytModyf
	,pDokStatus,strExtra6,strExtra7,curExtra8,curExtra9,dExtra10
	)
select
	IdObj,VersionId,strNrDok,nNumOper,dDataWyst,pUzytRej,pRejestrDok
	,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid,pMagazyn,cAutoCalc,pZlecProd,strExtra1
	,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,realprod_pUzytModyf
	,pDokStatus,'','',0.0,0.0,{d '1899-12-31'}
	
from upg___n5realprod

go
--TODO:check DEFAULT n5realprod:strExtra6
--TODO:check DEFAULT n5realprod:strExtra7
--TODO:check DEFAULT n5realprod:curExtra8
--TODO:check DEFAULT n5realprod:curExtra9
--TODO:check DEFAULT n5realprod:dExtra10
exec upd_n5realprod
go
drop procedure upd_n5realprod
go
drop table upg___n5realprod


go
raiserror('transfered n5realprod',0,1)
go


go 
create procedure upd_n5pozzlecprod as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozzlecprod(
	IdObj,VersionId,pProdukt,pOpak,pRecepta,curIloscOpak,strExtra1,strExtra2,dExtra3,curExtra4
	,curExtra5,pKwalifikatorEx,curIloscOpakPoz,prp_curIloscOpakPozWyd,prp_curIloscOpakPozProd,strExtra6,strExtra7,curExtra8
	,curExtra9,dExtra10)
select
	IdObj,VersionId,pProdukt,pOpak,pRecepta,curIloscOpak,strExtra1,strExtra2,dExtra3,curExtra4
	,curExtra5,pKwalifikatorEx,curIloscOpakPoz,prp_curIloscOpakPozWyd,prp_curIloscOpakPozProd,'','',0.0
	,0.0,{d '1899-12-31'}
from upg___n5pozzlecprod

go
--TODO:check DEFAULT n5pozzlecprod:strExtra6
--TODO:check DEFAULT n5pozzlecprod:strExtra7
--TODO:check DEFAULT n5pozzlecprod:curExtra8
--TODO:check DEFAULT n5pozzlecprod:curExtra9
--TODO:check DEFAULT n5pozzlecprod:dExtra10
exec upd_n5pozzlecprod
go
drop procedure upd_n5pozzlecprod
go
drop table upg___n5pozzlecprod


go
raiserror('transfered n5pozzlecprod',0,1)
go
--========= END INJECT B ==============
--========= BEGIN INJECT C ==============
--TODO: CHECK ORDER OF UPDATES (when more than 1 collection in object) !! update collections set idCollection=n+1 where idCollection=n
update collections set idCollection=10129074 where idCollection=10129069
update collections set idCollection=10129080 where idCollection=10129075
update collections set idCollection=10162035 where idCollection=10162030
update collections set idCollection=10162040 where idCollection=10162035
update collections set idCollection=10176079 where idCollection=10176074
update collections set idCollection=10176084 where idCollection=10176079
update collections set idCollection=10119055 where idCollection=10119050
update collections set idCollection=10172042 where idCollection=10172037
update collections set idCollection=10172047 where idCollection=10172042
update collections set idCollection=10206027 where idCollection=10206022
update collections set idCollection=10206028 where idCollection=10206023
update collections set idCollection=10206030 where idCollection=10206025
update collections set idCollection=10206031 where idCollection=10206026
--========= END INJECT C ==============
