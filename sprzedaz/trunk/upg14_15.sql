-- upgrade from c:\navo_eb\sprzedaz\db14.desc to c:\navo_eb\sprzedaz\db15.desc
-- generated: 2019-04-14 9:15:46 PM
 use %DBNAME% 
 go 
--========= BEGIN INJECT A ==============
-- alter table n5rozlvat
sp_rename 'n5rozlvat','upg___n5rozlvat','OBJECT'
go
-- alter table n5klient_produkt
sp_rename 'n5klient_produkt','upg___n5klient_produkt','OBJECT'
go
-- alter table n5recepta
sp_rename 'n5recepta','upg___n5recepta','OBJECT'
go
-- alter table n5zakup
sp_rename 'n5zakup','upg___n5zakup','OBJECT'
go
-- alter table n5pozzamowienie
sp_rename 'n5pozzamowienie','upg___n5pozzamowienie','OBJECT'
go
-- alter table n5pozdokmag
sp_rename 'n5pozdokmag','upg___n5pozdokmag','OBJECT'
go
-- alter table n5pit11
sp_rename 'n5pit11','upg___n5pit11','OBJECT'
go
--========= END INJECT A ==============
--========= BEGIN INJECT B ==============
create table n5rozlvat
(
	IdObj integer not null,
	VersionId integer not null,
	vat7_dDataOd datetime not null,
	vat7_dDataDo datetime not null,
	vat7_pUrzadSkarbowy integer not null,
	vat7_strUS varchar(255) not null,
	vat7_pUzytRej integer not null,
	vat7_strImieRej varchar(32) not null,
	vat7_strNazwiskoRej varchar(32) not null,
	vat7_pZadanie integer not null,
	vat7_pSchematDekr integer not null,
	vat7_pDowKsieg integer not null,
	vat7_pTransakcja integer not null,
	vat7_pUzytModyf integer not null,
	vat7_cKorekta varchar(1) not null,
	vat7_strNIPPlatnik varchar(20) not null,
	vat7_eTypPlatnika integer not null,
	vat7_strNazwaPlatnik varchar(255) not null,
	vat7_strImiePlatnik varchar(32) not null,
	vat7_strNazwiskoPlatnik varchar(32) not null,
	vat7_dDataUrPlatnik datetime not null,
	vat7_strKrajPlatnik varchar(32) not null,
	vat7_strWojewodztwoPlatnik varchar(32) not null,
	vat7_strPowiatPlatnik varchar(32) not null,
	vat7_strGminaPlatnik varchar(32) not null,
	vat7_strUlicaPlatnik varchar(64) not null,
	vat7_strNrDomuPlatnik varchar(8) not null,
	vat7_strNrLokaluPlatnik varchar(8) not null,
	vat7_strKodPlatnik varchar(8) not null,
	vat7_strPocztaPlatnik varchar(64) not null,
	vat7_strMiejscowoscPlatnik varchar(64) not null,
	vat7_curDostawyUslugiKrajZW decimal(12,2) not null,
	vat7_curDostawyUslugiKraj0 decimal(12,2) not null,
	vat7_curDostawyUslugiKraj3 decimal(12,2) not null,
	vat7_curDostawyUslugiKraj3Podatek decimal(12,2) not null,
	vat7_curDostawyUslugiKraj7 decimal(12,2) not null,
	vat7_curDostawyUslugiKraj7Podatek decimal(12,2) not null,
	vat7_curDostawyUslugiKraj22 decimal(12,2) not null,
	vat7_curDostawyUslugiKraj22Podatek decimal(12,2) not null,
	vat7_curWDT decimal(12,2) not null,
	vat7_curEksportTowarow decimal(12,2) not null,
	vat7_curWNT decimal(12,2) not null,
	vat7_curWNTPodatek decimal(12,2) not null,
	-- [virtual] vat7_curImportTowarow,
	-- [virtual] vat7_curImportTowarowPodatek,
	vat7_curImportUslug decimal(12,2) not null,
	vat7_curImportUslugPodatek decimal(12,2) not null,
	vat7_curDostawaPodNab decimal(12,2) not null,
	vat7_curDostawaPodNabPodatek decimal(12,2) not null,
	vat7_curKwotaPodatkuSpis decimal(12,2) not null,
	vat7_curKwotaPodatkuTransport decimal(12,2) not null,
	vat7_curKwotaPodatkuRazem decimal(12,2) not null,
	vat7_curNadwyzkaPop decimal(12,2) not null,
	vat7_curPodatkuNalSpis decimal(12,2) not null,
	vat7_curStrukturaSprzed decimal(12,2) not null,
	vat7_curNabycieTowUslSrtrwNetto decimal(12,2) not null,
	vat7_curNabycieTowUslSrtrwPodatek_0 decimal(12,2) not null,
	vat7_curNabycieTowUslSrtrwPodatek decimal(12,2) not null,
	vat7_curNabycieTowUslNetto decimal(12,2) not null,
	vat7_curNabycieTowUslPodatek decimal(12,2) not null,
	vat7_curKorektaNabycieSrTrwPodatek decimal(12,2) not null,
	vat7_curKorektaNabyciePodatek decimal(12,2) not null,
	vat7_curRazemPodatekOdl decimal(12,2) not null,
	vat7_curZakupKas decimal(12,2) not null,
	vat7_curKwotaZaniechPob decimal(12,2) not null,
	vat7_curKwotaWplataUS decimal(12,2) not null,
	vat7_curZakupKasZwrot decimal(12,2) not null,
	vat7_curNadwyzkaNaliczNalez decimal(12,2) not null,
	vat7_curNNNDoZwrotuRachBank decimal(12,2) not null,
	-- [virtual] vat7_curNNNDoZwrotu25,
	vat7_curNNNDoZwrotu180 decimal(12,2) not null,
	vat7_curNNNDoPrzeniesienia decimal(12,2) not null,
	vat7_strCzynnosc varchar(8) not null,
	vat7_curPodatekPaliwa decimal(12,2) not null,
	vat7_curPodatekPojazdy decimal(12,2) not null,
	vat7_strWniosekZwrot varchar(8) not null,
	vat7_strWniosekPrzyspieszenie varchar(8) not null,
	vat7_dDataWyp datetime not null,
	vat7_strTelefonRej varchar(32) not null,
	vat7_iWersja integer not null,
	vat7_curDostawyUslugiPozaKrajZW decimal(12,2) not null,
	vat7_curDostawyUslugiKraj0Art129 decimal(12,2) not null,
	vat7_curPodstawaPodatkuRazem decimal(12,2) not null,
	vat7_curNNNDoZwrotu60 decimal(12,2) not null,
	-- [virtual] vat7_curDostawyUslugiPozaKrajZW_Art100,
	-- [virtual] vat7_curImportUslug_Art28b,
	-- [virtual] vat7_curImportUslugPodatek_Art28b,
	-- [virtual] vat7_strZwiekszeniePodatku,
	-- [virtual] vat7_strZawiadSkorygPodstawy,
	-- [virtual] vat7_curLiczbaZalVAT_ZD,
	-- [virtual] vat7_curDostawaTowarowSprzedaz,
	-- [virtual] vat7_curDostawaPodNab1_5,
	-- [virtual] vat7_curDostawaPodNabPodatek1_5,
	-- [virtual] vat7_curKorektaPodatkuArt89b,
	-- [virtual] vat7_curKwotaPodatkuNabyciaPaliw,
	-- [virtual] vat7_curKorektaPodatkuArt89bUst4,
	-- [virtual] vat7_curNaRachunekVAT,
	-- [virtual] vat7_strObnizenieZobowPodatkow,
	-- [virtual] vat7_strZwrotPodatkuVAT,
	-- [virtual] vat7_strEmail
)
go

create table n5klient_produkt
(
	IdObj integer not null,
	VersionId integer not null,
	klpr_pKlient integer not null,
	klpr_pProdukt integer not null,
	klpr_strNazwa varchar(128) not null,
	klpr_strIndeks varchar(32) not null,
	-- [virtual] klpr_listOpakowania,
	klpr_cPublic varchar(1) not null
)
go

create table n5recepta
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNorma varchar(64) not null,
	strOpis varchar(1024) not null,
	-- [virtual] listWyrob,
	-- [virtual] listSurowce,
	-- [virtual] listCzynnosci,
	rcpt_eAktywny integer not null,
	-- [virtual] rcpt_listZasob,
	-- [virtual] rcpt_listOper,
	rcpt_eTyp integer not null
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
	zak_cSplit varchar(1) not null,
	-- [virtual] curWartosc75,
	-- [virtual] curWartosc25,
	-- [virtual] curNetto75,
	-- [virtual] curVat75,
	-- [virtual] curNetto25,
	-- [virtual] curVat25
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
	curExtra4 decimal(14,4) not null,
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
	curExtra4 decimal(14,4) not null,
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

create table n5pit11
(
	IdObj integer not null,
	VersionId integer not null,
	pt11_dDataOd datetime not null,
	pt11_dDataDo datetime not null,
	pt11_pUrzadSkarbowy integer not null,
	pt11_strUS varchar(255) not null,
	pt11_pUzytRej integer not null,
	pt11_strImieRej varchar(32) not null,
	pt11_strNazwiskoRej varchar(32) not null,
	pt11_pZadanie integer not null,
	pt11_pSchematDekr integer not null,
	pt11_pDowKsieg integer not null,
	pt11_pTransakcja integer not null,
	pt11_pUzytModyf integer not null,
	pt11_pPodatnik integer not null,
	pt11_strNIPPlatnik varchar(20) not null,
	pt11_eTypPlatnika integer not null,
	pt11_strNazwaPlatnik varchar(255) not null,
	pt11_strImiePlatnik varchar(32) not null,
	pt11_strNazwiskoPlatnik varchar(32) not null,
	pt11_dDataUrPlatnik datetime not null,
	pt11_strKrajPlatnik varchar(32) not null,
	pt11_strWojewodztwoPlatnik varchar(32) not null,
	pt11_strPowiatPlatnik varchar(32) not null,
	pt11_strGminaPlatnik varchar(32) not null,
	pt11_strUlicaPlatnik varchar(64) not null,
	pt11_strNrDomuPlatnik varchar(8) not null,
	pt11_strNrLokaluPlatnik varchar(8) not null,
	pt11_strKodPlatnik varchar(8) not null,
	pt11_strPocztaPlatnik varchar(64) not null,
	pt11_strMiejscowoscPlatnik varchar(64) not null,
	pt11_strNIPPodatnik varchar(20) not null,
	pt11_strImie varchar(32) not null,
	pt11_strNazwisko varchar(32) not null,
	pt11_dDataUr datetime not null,
	pt11_strKraj varchar(32) not null,
	pt11_strWojewodztwo varchar(32) not null,
	pt11_strPowiat varchar(32) not null,
	pt11_strGmina varchar(32) not null,
	pt11_strUlica varchar(64) not null,
	pt11_strNrDomu varchar(8) not null,
	pt11_strNrLokalu varchar(8) not null,
	pt11_strKod varchar(8) not null,
	pt11_strPoczta varchar(64) not null,
	pt11_strMiejscowosc varchar(64) not null,
	pt11_eKosztUPOd integer not null,
	pt11_curPrzychod_WynZas decimal(12,2) not null,
	pt11_curKUPrzychodu_WynZas decimal(12,2) not null,
	pt11_curDochod_WynZas decimal(12,2) not null,
	-- [virtual] pt11_curDochodZwol_WynZas,
	pt11_curZaliczka_WynZas decimal(12,2) not null,
	pt11_curPrzychod_WynZasOdlKU decimal(12,2) not null,
	pt11_curKUPrzychodu_WynZasOdlKU decimal(12,2) not null,
	pt11_curPrzychod_DzialRol decimal(12,2) not null,
	pt11_curDochod_DzialRol decimal(12,2) not null,
	pt11_curZaliczka_DzialRol decimal(12,2) not null,
	pt11_curPrzychod_RenZagr decimal(12,2) not null,
	pt11_curDochod_RenZagr decimal(12,2) not null,
	-- [virtual] pt11_curDochodZwol_RenZagr,
	pt11_curZaliczka_RenZagr decimal(12,2) not null,
	pt11_curPrzychod_AresztSkaz decimal(12,2) not null,
	pt11_curDochod_AresztSkaz decimal(12,2) not null,
	pt11_curZaliczka_AresztSkaz decimal(12,2) not null,
	pt11_curPrzychod_Fund decimal(12,2) not null,
	pt11_curDochod_Fund decimal(12,2) not null,
	pt11_curZaliczka_Fund decimal(12,2) not null,
	pt11_curPrzychod_OsWykDzial decimal(12,2) not null,
	pt11_curKUPrzychodu_OsWykDzial decimal(12,2) not null,
	pt11_curDochod_OsWykDzial decimal(12,2) not null,
	pt11_curZaliczka_OsWykDzial decimal(12,2) not null,
	pt11_curPrzychod_ObowSpol decimal(12,2) not null,
	pt11_curKUPrzychodu_ObowSpol decimal(12,2) not null,
	pt11_curDochod_ObowSpol decimal(12,2) not null,
	pt11_curZaliczka_ObowSpol decimal(12,2) not null,
	pt11_curPrzychod_OrganyStan decimal(12,2) not null,
	pt11_curKUPrzychodu_OrganyStan decimal(12,2) not null,
	pt11_curDochod_OrganyStan decimal(12,2) not null,
	pt11_curZaliczka_OrganyStan decimal(12,2) not null,
	pt11_curPrzychod_Zarzad decimal(12,2) not null,
	pt11_curKUPrzychodu_Zarzad decimal(12,2) not null,
	pt11_curDochod_Zarzad decimal(12,2) not null,
	pt11_curZaliczka_Zarzad decimal(12,2) not null,
	pt11_curPrzychod_PrawaAutor decimal(12,2) not null,
	pt11_curKUPrzychodu_PrawaAutor decimal(12,2) not null,
	pt11_curDochod_PrawaAutor decimal(12,2) not null,
	pt11_curZaliczka_PrawaAutor decimal(12,2) not null,
	pt11_curPrzychod_Inne decimal(12,2) not null,
	pt11_curDochod_Inne decimal(12,2) not null,
	-- [virtual] pt11_curDochodZwol_Inne,
	pt11_curZaliczka_Inne decimal(12,2) not null,
	pt11_curSkladka_UbSpol decimal(12,2) not null,
	-- [virtual] pt11_curSkladka_UbSpol_Zagr,
	pt11_curSkladka_UbZdr decimal(12,2) not null,
	-- [virtual] pt11_curSkladka_UbZdr_Zagr,
	pt11_curPrzychod_Zagranica decimal(12,2) not null,
	pt11_curPrzychod_PomocZagranica decimal(12,2) not null,
	pt11_cPitR varchar(1) not null,
	-- [virtual] pt11_celZlozInfo,
	-- [virtual] pt11_cRodzajObowiazPodat,
	-- [virtual] pt11_strZagrNrIdenty,
	-- [virtual] pt11_cRodzajNrIdenty,
	-- [virtual] pt11_strKrajNrIdenty,
	-- [virtual] pt11_curWynZbiory,
	-- [virtual] pt11_strPrzychody75,
	-- [virtual] pt11_curPrzychody76,
	-- [virtual] pt11_strPrzychody77,
	-- [virtual] pt11_curPrzychody78,
	-- [virtual] pt11_strPrzychody79,
	-- [virtual] pt11_curPrzychody80,
	-- [virtual] pt11_curPrzychodyRazem,
	-- [virtual] pt11_curPrzychodyStypendium
)
go

create table n5klient_grupaprod
(
	IdObj integer not null,
	VersionId integer not null,
	klgpr_pKlient integer not null,
	klgpr_pGrupaProd integer not null,
	klgpr_cPublic varchar(1) not null,
	klgpr_strPublicName varchar(512) not null
)
go



go 
create procedure upd_n5rozlvat as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5rozlvat(
	IdObj,VersionId,vat7_dDataOd,vat7_dDataDo,vat7_pUrzadSkarbowy,vat7_strUS,vat7_pUzytRej,vat7_strImieRej,vat7_strNazwiskoRej,vat7_pZadanie
	,vat7_pSchematDekr,vat7_pDowKsieg,vat7_pTransakcja,vat7_pUzytModyf,vat7_cKorekta,vat7_strNIPPlatnik,vat7_eTypPlatnika,vat7_strNazwaPlatnik
	,vat7_strImiePlatnik,vat7_strNazwiskoPlatnik,vat7_dDataUrPlatnik,vat7_strKrajPlatnik,vat7_strWojewodztwoPlatnik,vat7_strPowiatPlatnik,vat7_strGminaPlatnik,vat7_strUlicaPlatnik
	,vat7_strNrDomuPlatnik,vat7_strNrLokaluPlatnik,vat7_strKodPlatnik,vat7_strPocztaPlatnik,vat7_strMiejscowoscPlatnik,vat7_curDostawyUslugiKrajZW,vat7_curDostawyUslugiKraj0,vat7_curDostawyUslugiKraj3
	,vat7_curDostawyUslugiKraj3Podatek,vat7_curDostawyUslugiKraj7,vat7_curDostawyUslugiKraj7Podatek,vat7_curDostawyUslugiKraj22,vat7_curDostawyUslugiKraj22Podatek,vat7_curWDT,vat7_curEksportTowarow,vat7_curWNT
	,vat7_curWNTPodatek,vat7_curImportUslug,vat7_curImportUslugPodatek,vat7_curDostawaPodNab,vat7_curDostawaPodNabPodatek,vat7_curKwotaPodatkuSpis
	,vat7_curKwotaPodatkuTransport,vat7_curKwotaPodatkuRazem,vat7_curNadwyzkaPop,vat7_curPodatkuNalSpis,vat7_curStrukturaSprzed,vat7_curNabycieTowUslSrtrwNetto,vat7_curNabycieTowUslSrtrwPodatek_0,vat7_curNabycieTowUslSrtrwPodatek
	,vat7_curNabycieTowUslNetto,vat7_curNabycieTowUslPodatek,vat7_curKorektaNabycieSrTrwPodatek,vat7_curKorektaNabyciePodatek,vat7_curRazemPodatekOdl,vat7_curZakupKas,vat7_curKwotaZaniechPob,vat7_curKwotaWplataUS
	,vat7_curZakupKasZwrot,vat7_curNadwyzkaNaliczNalez,vat7_curNNNDoZwrotuRachBank,vat7_curNNNDoZwrotu180,vat7_curNNNDoPrzeniesienia,vat7_strCzynnosc,vat7_curPodatekPaliwa
	,vat7_curPodatekPojazdy,vat7_strWniosekZwrot,vat7_strWniosekPrzyspieszenie,vat7_dDataWyp,vat7_strTelefonRej,vat7_iWersja,vat7_curDostawyUslugiPozaKrajZW,vat7_curDostawyUslugiKraj0Art129
	,vat7_curPodstawaPodatkuRazem,vat7_curNNNDoZwrotu60
	
	)
select
	IdObj,VersionId,vat7_dDataOd,vat7_dDataDo,vat7_pUrzadSkarbowy,vat7_strUS,vat7_pUzytRej,vat7_strImieRej,vat7_strNazwiskoRej,vat7_pZadanie
	,vat7_pSchematDekr,vat7_pDowKsieg,vat7_pTransakcja,vat7_pUzytModyf,vat7_cKorekta,vat7_strNIPPlatnik,vat7_eTypPlatnika,vat7_strNazwaPlatnik
	,vat7_strImiePlatnik,vat7_strNazwiskoPlatnik,vat7_dDataUrPlatnik,vat7_strKrajPlatnik,vat7_strWojewodztwoPlatnik,vat7_strPowiatPlatnik,vat7_strGminaPlatnik,vat7_strUlicaPlatnik
	,vat7_strNrDomuPlatnik,vat7_strNrLokaluPlatnik,vat7_strKodPlatnik,vat7_strPocztaPlatnik,vat7_strMiejscowoscPlatnik,vat7_curDostawyUslugiKrajZW,vat7_curDostawyUslugiKraj0,vat7_curDostawyUslugiKraj3
	,vat7_curDostawyUslugiKraj3Podatek,vat7_curDostawyUslugiKraj7,vat7_curDostawyUslugiKraj7Podatek,vat7_curDostawyUslugiKraj22,vat7_curDostawyUslugiKraj22Podatek,vat7_curWDT,vat7_curEksportTowarow,vat7_curWNT
	,vat7_curWNTPodatek,vat7_curImportUslug,vat7_curImportUslugPodatek,vat7_curDostawaPodNab,vat7_curDostawaPodNabPodatek,vat7_curKwotaPodatkuSpis
	,vat7_curKwotaPodatkuTransport,vat7_curKwotaPodatkuRazem,vat7_curNadwyzkaPop,vat7_curPodatkuNalSpis,vat7_curStrukturaSprzed,vat7_curNabycieTowUslSrtrwNetto,vat7_curNabycieTowUslSrtrwPodatek_0,vat7_curNabycieTowUslSrtrwPodatek
	,vat7_curNabycieTowUslNetto,vat7_curNabycieTowUslPodatek,vat7_curKorektaNabycieSrTrwPodatek,vat7_curKorektaNabyciePodatek,vat7_curRazemPodatekOdl,vat7_curZakupKas,vat7_curKwotaZaniechPob,vat7_curKwotaWplataUS
	,vat7_curZakupKasZwrot,vat7_curNadwyzkaNaliczNalez,vat7_curNNNDoZwrotuRachBank,vat7_curNNNDoZwrotu180,vat7_curNNNDoPrzeniesienia,vat7_strCzynnosc,vat7_curPodatekPaliwa
	,vat7_curPodatekPojazdy,vat7_strWniosekZwrot,vat7_strWniosekPrzyspieszenie,vat7_dDataWyp,vat7_strTelefonRej,vat7_iWersja,vat7_curDostawyUslugiPozaKrajZW,vat7_curDostawyUslugiKraj0Art129
	,vat7_curPodstawaPodatkuRazem,vat7_curNNNDoZwrotu60
	
	
from upg___n5rozlvat

go
exec upd_n5rozlvat
go
drop procedure upd_n5rozlvat
go
drop table upg___n5rozlvat


go
raiserror('transfered n5rozlvat',0,1)
go


go 
create procedure upd_n5klient_produkt as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5klient_produkt(
	IdObj,VersionId,klpr_pKlient,klpr_pProdukt,klpr_strNazwa,klpr_strIndeks,klpr_cPublic)
select
	IdObj,VersionId,klpr_pKlient,klpr_pProdukt,klpr_strNazwa,klpr_strIndeks,''
from upg___n5klient_produkt

go
--TODO:check DEFAULT n5klient_produkt:klpr_cPublic
exec upd_n5klient_produkt
go
drop procedure upd_n5klient_produkt
go
drop table upg___n5klient_produkt


go
raiserror('transfered n5klient_produkt',0,1)
go


go 
create procedure upd_n5recepta as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5recepta(
	IdObj,VersionId,strNazwa,strNorma,strOpis,rcpt_eAktywny
	,rcpt_eTyp)
select
	IdObj,VersionId,strNazwa,strNorma,strOpis,rcpt_eAktywny
	,0
from upg___n5recepta

go
--TODO:check DEFAULT n5recepta:rcpt_eTyp
exec upd_n5recepta
go
drop procedure upd_n5recepta
go
drop table upg___n5recepta


go
raiserror('transfered n5recepta',0,1)
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
	,zak_cSplit
from upg___n5zakup

go
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
	,curIloscOpakPoz,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,pzam_curIloscOpakZreal,pzam_dDataReal,pzam_pZadanie,curCenaBazowaBruttoWal
	,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg)
select
	IdObj,VersionId,pProdukt,curIloscOpak,pOpak,curCenaBazNetto,curCenaBazBrutto,curRabat,eVAT,curCenaNetto
	,curCenaBrutto,curWartNetto,curVAT,curWartBrutto,curCenaBazowaNettoWal,curCenaNettoWal,curWartWal,strUwagi
	,curIloscOpakPoz,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6
	,strExtra7,curExtra8,curExtra9,dExtra10,pzam_curIloscOpakZreal,pzam_dDataReal,pzam_pZadanie,curCenaBazowaBruttoWal
	,curCenaBruttoWal,curWartBruttoWal,pProduktOrg,pOpakOrg
from upg___n5pozzamowienie

go
exec upd_n5pozzamowienie
go
drop procedure upd_n5pozzamowienie
go
drop table upg___n5pozzamowienie


go
raiserror('transfered n5pozzamowienie',0,1)
go


go 
create procedure upd_n5pozdokmag as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pozdokmag(
	IdObj,VersionId,pProdukt,pOpak,nTypDok,pMagZrod,pMagDocel,pJednOpak,curIloscOpak,pJednEwid
	,curIloscEwid,curCenaMag,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10,dDataWazn,pdm_pObiektKlienta,pdm_strNrPartii)
select
	IdObj,VersionId,pProdukt,pOpak,nTypDok,pMagZrod,pMagDocel,pJednOpak,curIloscOpak,pJednEwid
	,curIloscEwid,curCenaMag,curCenaEwid,curWartMag,curWartEwid,nNumOpMagDost,nLpDost,strUwagi
	,strExtra1,strExtra2,dExtra3,curExtra4,curExtra5,pKwalifikatorEx,strExtra6,strExtra7
	,curExtra8,curExtra9,dExtra10,dDataWazn,pdm_pObiektKlienta,pdm_strNrPartii
from upg___n5pozdokmag

go
exec upd_n5pozdokmag
go
drop procedure upd_n5pozdokmag
go
drop table upg___n5pozdokmag


go
raiserror('transfered n5pozdokmag',0,1)
go


go 
create procedure upd_n5pit11 as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5pit11(
	IdObj,VersionId,pt11_dDataOd,pt11_dDataDo,pt11_pUrzadSkarbowy,pt11_strUS,pt11_pUzytRej,pt11_strImieRej,pt11_strNazwiskoRej,pt11_pZadanie
	,pt11_pSchematDekr,pt11_pDowKsieg,pt11_pTransakcja,pt11_pUzytModyf,pt11_pPodatnik,pt11_strNIPPlatnik,pt11_eTypPlatnika,pt11_strNazwaPlatnik
	,pt11_strImiePlatnik,pt11_strNazwiskoPlatnik,pt11_dDataUrPlatnik,pt11_strKrajPlatnik,pt11_strWojewodztwoPlatnik,pt11_strPowiatPlatnik,pt11_strGminaPlatnik,pt11_strUlicaPlatnik
	,pt11_strNrDomuPlatnik,pt11_strNrLokaluPlatnik,pt11_strKodPlatnik,pt11_strPocztaPlatnik,pt11_strMiejscowoscPlatnik,pt11_strNIPPodatnik,pt11_strImie,pt11_strNazwisko
	,pt11_dDataUr,pt11_strKraj,pt11_strWojewodztwo,pt11_strPowiat,pt11_strGmina,pt11_strUlica,pt11_strNrDomu,pt11_strNrLokalu
	,pt11_strKod,pt11_strPoczta,pt11_strMiejscowosc,pt11_eKosztUPOd,pt11_curPrzychod_WynZas,pt11_curKUPrzychodu_WynZas,pt11_curDochod_WynZas
	,pt11_curZaliczka_WynZas,pt11_curPrzychod_WynZasOdlKU,pt11_curKUPrzychodu_WynZasOdlKU,pt11_curPrzychod_DzialRol,pt11_curDochod_DzialRol,pt11_curZaliczka_DzialRol,pt11_curPrzychod_RenZagr,pt11_curDochod_RenZagr
	,pt11_curZaliczka_RenZagr,pt11_curPrzychod_AresztSkaz,pt11_curDochod_AresztSkaz,pt11_curZaliczka_AresztSkaz,pt11_curPrzychod_Fund,pt11_curDochod_Fund,pt11_curZaliczka_Fund
	,pt11_curPrzychod_OsWykDzial,pt11_curKUPrzychodu_OsWykDzial,pt11_curDochod_OsWykDzial,pt11_curZaliczka_OsWykDzial,pt11_curPrzychod_ObowSpol,pt11_curKUPrzychodu_ObowSpol,pt11_curDochod_ObowSpol,pt11_curZaliczka_ObowSpol
	,pt11_curPrzychod_OrganyStan,pt11_curKUPrzychodu_OrganyStan,pt11_curDochod_OrganyStan,pt11_curZaliczka_OrganyStan,pt11_curPrzychod_Zarzad,pt11_curKUPrzychodu_Zarzad,pt11_curDochod_Zarzad,pt11_curZaliczka_Zarzad
	,pt11_curPrzychod_PrawaAutor,pt11_curKUPrzychodu_PrawaAutor,pt11_curDochod_PrawaAutor,pt11_curZaliczka_PrawaAutor,pt11_curPrzychod_Inne,pt11_curDochod_Inne,pt11_curZaliczka_Inne
	,pt11_curSkladka_UbSpol,pt11_curSkladka_UbZdr,pt11_curPrzychod_Zagranica,pt11_curPrzychod_PomocZagranica,pt11_cPitR
	
	)
select
	IdObj,VersionId,pt11_dDataOd,pt11_dDataDo,pt11_pUrzadSkarbowy,pt11_strUS,pt11_pUzytRej,pt11_strImieRej,pt11_strNazwiskoRej,pt11_pZadanie
	,pt11_pSchematDekr,pt11_pDowKsieg,pt11_pTransakcja,pt11_pUzytModyf,pt11_pPodatnik,pt11_strNIPPlatnik,pt11_eTypPlatnika,pt11_strNazwaPlatnik
	,pt11_strImiePlatnik,pt11_strNazwiskoPlatnik,pt11_dDataUrPlatnik,pt11_strKrajPlatnik,pt11_strWojewodztwoPlatnik,pt11_strPowiatPlatnik,pt11_strGminaPlatnik,pt11_strUlicaPlatnik
	,pt11_strNrDomuPlatnik,pt11_strNrLokaluPlatnik,pt11_strKodPlatnik,pt11_strPocztaPlatnik,pt11_strMiejscowoscPlatnik,pt11_strNIPPodatnik,pt11_strImie,pt11_strNazwisko
	,pt11_dDataUr,pt11_strKraj,pt11_strWojewodztwo,pt11_strPowiat,pt11_strGmina,pt11_strUlica,pt11_strNrDomu,pt11_strNrLokalu
	,pt11_strKod,pt11_strPoczta,pt11_strMiejscowosc,pt11_eKosztUPOd,pt11_curPrzychod_WynZas,pt11_curKUPrzychodu_WynZas,pt11_curDochod_WynZas
	,pt11_curZaliczka_WynZas,pt11_curPrzychod_WynZasOdlKU,pt11_curKUPrzychodu_WynZasOdlKU,pt11_curPrzychod_DzialRol,pt11_curDochod_DzialRol,pt11_curZaliczka_DzialRol,pt11_curPrzychod_RenZagr,pt11_curDochod_RenZagr
	,pt11_curZaliczka_RenZagr,pt11_curPrzychod_AresztSkaz,pt11_curDochod_AresztSkaz,pt11_curZaliczka_AresztSkaz,pt11_curPrzychod_Fund,pt11_curDochod_Fund,pt11_curZaliczka_Fund
	,pt11_curPrzychod_OsWykDzial,pt11_curKUPrzychodu_OsWykDzial,pt11_curDochod_OsWykDzial,pt11_curZaliczka_OsWykDzial,pt11_curPrzychod_ObowSpol,pt11_curKUPrzychodu_ObowSpol,pt11_curDochod_ObowSpol,pt11_curZaliczka_ObowSpol
	,pt11_curPrzychod_OrganyStan,pt11_curKUPrzychodu_OrganyStan,pt11_curDochod_OrganyStan,pt11_curZaliczka_OrganyStan,pt11_curPrzychod_Zarzad,pt11_curKUPrzychodu_Zarzad,pt11_curDochod_Zarzad,pt11_curZaliczka_Zarzad
	,pt11_curPrzychod_PrawaAutor,pt11_curKUPrzychodu_PrawaAutor,pt11_curDochod_PrawaAutor,pt11_curZaliczka_PrawaAutor,pt11_curPrzychod_Inne,pt11_curDochod_Inne,pt11_curZaliczka_Inne
	,pt11_curSkladka_UbSpol,pt11_curSkladka_UbZdr,pt11_curPrzychod_Zagranica,pt11_curPrzychod_PomocZagranica,pt11_cPitR
	
	
from upg___n5pit11

go
exec upd_n5pit11
go
drop procedure upd_n5pit11
go
drop table upg___n5pit11


go
raiserror('transfered n5pit11',0,1)
go
--========= END INJECT B ==============
--========= BEGIN INJECT C ==============
--TODO: CHECK ORDER OF UPDATES (when more than 1 collection in object) !! update collections set idCollection=n+1 where idCollection=n
--========= END INJECT C ==============
