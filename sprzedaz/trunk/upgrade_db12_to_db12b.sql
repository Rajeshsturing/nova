--------------------------------------------------------------------
-- Manual upgrade from DB12 (ENABLE_DB12) to DB12_B (ENABLE_DB12_B)
-- created: 2015-01-16
--
-- Notes:
-- 1) first select manually database (i.e. NAVO2002)
-- 2) run once only
--------------------------------------------------------------------

-- NAVO Enterprise SQL script (drop) --
-- generated: 2015-01-16 11:31:05

--========= dropping FK =========
if exists (select * from sysobjects where name='n5klient_candel')
	drop procedure n5klient_candel
go

if exists (select * from sysobjects where name='n5grupaklient_candel')
	drop procedure n5grupaklient_candel
go

if exists (select * from sysobjects where name='n5grupaproduktow_candel')
	drop procedure n5grupaproduktow_candel
go

if exists (select * from sysobjects where name='n5produkt_candel')
	drop procedure n5produkt_candel
go

if exists (select * from sysobjects where name='n5kwalifikator_candel')
	drop procedure n5kwalifikator_candel
go
-- end of script ----


-- generated: 2015-01-16 12:22:11

--========= BEGIN INJECT A ==============
--========= END INJECT A ==============
--========= BEGIN INJECT B ==============
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

--========= END INJECT B ==============
--========= BEGIN INJECT C ==============
--TODO: CHECK ORDER OF UPDATES (when more than 1 collection in object) !! update collections set idCollection=n+1 where idCollection=n
--========= END INJECT C ==============



-- NAVO Enterprise SQL script (create) --
-- generated: 2015-01-16 12:18:56





create procedure n5klient_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10122 as integer),idobj from n5wykonawca where wrefObiekt=@idobj_par and wrefObiekt_wrt=10108
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpNadawca=@idobj_par and wpNadawca_wrt=10108
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where wpAdresat=@idobj_par and wpAdresat_wrt=10108
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where dok_pUFKlient15=@idobj_par
union
select TOP 5 'typeid'=cast(10116 as integer),idobj from n5grupaproduktow where grp_pDostawca=@idobj_par
union
select TOP 5 'typeid'=cast(10114 as integer),idobj from n5_klient_jedn_org where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10112 as integer),idobj from n5klient_pracownik where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10134 as integer),idobj from n5pkpir where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pDostawca=@idobj_par
union
select TOP 5 'typeid'=cast(10128 as integer),idobj from n5SendEmail where wpNadawca=@idobj_par and wpNadawca_wrt=10108
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10108
union
select TOP 5 'typeid'=cast(10151 as integer),idobj from n5klient_produkt where klpr_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10108
union
select TOP 5 'typeid'=cast(10149 as integer),idobj from n5egzemplarz where egze_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where wrefPodmiotRozrach=@idobj_par and wrefPodmiotRozrach_wrt=10108
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where rejdok_pDefKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10144 as integer),idobj from n5pozvatue where pvtue_refKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10156 as integer),idobj from n5pozrata where prat_pPlatnik=@idobj_par
union
select TOP 5 'typeid'=cast(10169 as integer),idobj from n5proglojal where proloj_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpKlientGrupa=@idobj_par and wpKlientGrupa_wrt=10108
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pDostawca=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10234 as integer),idobj from n5klient_obiekt where klob_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10242 as integer),idobj from n5projekt_abas where proj_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10286 as integer),idobj from n5ankieta_toral where ank_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10280 as integer),idobj from n5pojazd where poj_pKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10292 as integer),idobj from n5straznik_cen where scs_wpKlientGrupa=@idobj_par and scs_wpKlientGrupa_wrt=10108
go

create procedure n5grupaklient_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where pGrupaKlient=@idobj_par
union
select TOP 5 'typeid'=cast(10118 as integer),idobj from n5grupaklient where pGrupaNadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpKlientGrupa=@idobj_par and wpKlientGrupa_wrt=10118
union
select TOP 5 'typeid'=cast(10292 as integer),idobj from n5straznik_cen where scs_wpKlientGrupa=@idobj_par and scs_wpKlientGrupa_wrt=10118
go

create procedure n5grupaproduktow_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10108 as integer),idobj from n5klient where kli_pGrupaProd=@idobj_par
union
select TOP 5 'typeid'=cast(10116 as integer),idobj from n5grupaproduktow where pGrupaNadrzedna=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where pGrupaProd=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10116
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10116
union
select TOP 5 'typeid'=cast(10292 as integer),idobj from n5straznik_cen where scs_wpProdGrupa=@idobj_par and scs_wpProdGrupa_wrt=10116
go

create procedure n5produkt_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pProdMag=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik1=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik2=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik3=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik4=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik5=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pProduktOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10151 as integer),idobj from n5klient_produkt where klpr_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10149 as integer),idobj from n5egzemplarz where egze_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10167 as integer),idobj from n5pozdoketyk where pdet_pWyrob=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pProduktOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10184 as integer),idobj from n5pozrecepta where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
union
select TOP 5 'typeid'=cast(10238 as integer),idobj from n5pozdokprod where pdp_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10236 as integer),idobj from n5pltyppracy where tpr_pUsluga=@idobj_par
union
select TOP 5 'typeid'=cast(10234 as integer),idobj from n5klient_obiekt where klob_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10228 as integer),idobj from n5pozistat where pistt_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10226 as integer),idobj from n5gmstan where gms_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10225 as integer),idobj from n5gmop where gmo_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10251 as integer),idobj from n5ptstan where gms_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10250 as integer),idobj from n5ptop where gmo_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10243 as integer),idobj from n5pozprojekt_abas where pproj_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10279 as integer),idobj from n5produkt_magazyn where prmg_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10274 as integer),idobj from n5prop where prop_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10291 as integer),idobj from n5pozinwark where pia_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10292 as integer),idobj from n5straznik_cen where scs_wpProdGrupa=@idobj_par and scs_wpProdGrupa_wrt=10131
go

create procedure n5kwalifikator_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10134 as integer),idobj from n5pkpir where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10158 as integer),idobj from n5rapkas where raka_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10147 as integer),idobj from n5dekret where pKwalifikator=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10167 as integer),idobj from n5pozdoketyk where pdet_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10166 as integer),idobj from n5doketyk where doet_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10234 as integer),idobj from n5klient_obiekt where pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10244 as integer),idobj from n5protokol_abas where prot_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10243 as integer),idobj from n5pozprojekt_abas where pproj_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10242 as integer),idobj from n5projekt_abas where proj_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10287 as integer),idobj from n5pozankieta_toral where pank_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10286 as integer),idobj from n5ankieta_toral where ank_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10285 as integer),idobj from n5srodek_lok where slok_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10284 as integer),idobj from n5poz_koszt_wyjazdu where pdkw_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10283 as integer),idobj from n5polecenie_wyjazdu where pws_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10282 as integer),idobj from n5poz_hist_stan where pstn_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10281 as integer),idobj from n5stanowisko where stn_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10280 as integer),idobj from n5pojazd where poj_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10290 as integer),idobj from n5inwark where ia_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10289 as integer),idobj from n5inwmag where im_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10288 as integer),idobj from n5maszyna_toral where masz_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10291 as integer),idobj from n5pozinwark where pia_pKwalifikatorEx=@idobj_par
union
select TOP 5 'typeid'=cast(10292 as integer),idobj from n5straznik_cen where scs_pKwalifikatorEx=@idobj_par
go

-- table: n5straznik_cen
create procedure n5straznik_cen_select(@idobj_par integer,@versionid_par integer output,
	@scs_strNazwa_par varchar(128) output,
	@scs_wpProdGrupa_par integer output,
	@scs_wpProdGrupa_wrt_par integer output,
	@scs_wpKlientGrupa_par integer output,
	@scs_wpKlientGrupa_wrt_par integer output,
	@scs_curModyfikator_par decimal(12,2) output,
	@scs_eZestawCenowy_par integer output,
	@scs_eAktywny_par integer output,
	@scs_strExtra1_par varchar(32) output,
	@scs_strExtra2_par varchar(128) output,
	@scs_dExtra3_par datetime output,
	@scs_curExtra4_par decimal(12,2) output,
	@scs_curExtra5_par decimal(12,2) output,
	@scs_pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@scs_strNazwa_par=scs_strNazwa,
	@scs_wpProdGrupa_par=scs_wpProdGrupa,
	@scs_wpProdGrupa_wrt_par=scs_wpProdGrupa_wrt,
	@scs_wpKlientGrupa_par=scs_wpKlientGrupa,
	@scs_wpKlientGrupa_wrt_par=scs_wpKlientGrupa_wrt,
	@scs_curModyfikator_par=scs_curModyfikator,
	@scs_eZestawCenowy_par=scs_eZestawCenowy,
	@scs_eAktywny_par=scs_eAktywny,
	@scs_strExtra1_par=scs_strExtra1,
	@scs_strExtra2_par=scs_strExtra2,
	@scs_dExtra3_par=scs_dExtra3,
	@scs_curExtra4_par=scs_curExtra4,
	@scs_curExtra5_par=scs_curExtra5,
	@scs_pKwalifikatorEx_par=scs_pKwalifikatorEx from n5straznik_cen where IdObj=@idobj_par
return @@rowcount
go

create procedure n5straznik_cen_insert(@idobj_par integer,@versionid_par integer,
	@scs_strNazwa_par varchar(128),
	@scs_wpProdGrupa_par integer,
	@scs_wpProdGrupa_wrt_par integer,
	@scs_wpKlientGrupa_par integer,
	@scs_wpKlientGrupa_wrt_par integer,
	@scs_curModyfikator_par decimal(12,2),
	@scs_eZestawCenowy_par integer,
	@scs_eAktywny_par integer,
	@scs_strExtra1_par varchar(32),
	@scs_strExtra2_par varchar(128),
	@scs_dExtra3_par datetime,
	@scs_curExtra4_par decimal(12,2),
	@scs_curExtra5_par decimal(12,2),
	@scs_pKwalifikatorEx_par integer) with encryption as 
	insert into n5straznik_cen values(@idobj_par,@versionid_par,
	@scs_strNazwa_par,
	@scs_wpProdGrupa_par,
	@scs_wpProdGrupa_wrt_par,
	@scs_wpKlientGrupa_par,
	@scs_wpKlientGrupa_wrt_par,
	@scs_curModyfikator_par,
	@scs_eZestawCenowy_par,
	@scs_eAktywny_par,
	@scs_strExtra1_par,
	@scs_strExtra2_par,
	@scs_dExtra3_par,
	@scs_curExtra4_par,
	@scs_curExtra5_par,
	@scs_pKwalifikatorEx_par)
return @@rowcount
go

create procedure n5straznik_cen_update(@idobj_par integer,@versionid_par integer,
	@scs_strNazwa_par varchar(128),
	@scs_wpProdGrupa_par integer,
	@scs_wpProdGrupa_wrt_par integer,
	@scs_wpKlientGrupa_par integer,
	@scs_wpKlientGrupa_wrt_par integer,
	@scs_curModyfikator_par decimal(12,2),
	@scs_eZestawCenowy_par integer,
	@scs_eAktywny_par integer,
	@scs_strExtra1_par varchar(32),
	@scs_strExtra2_par varchar(128),
	@scs_dExtra3_par datetime,
	@scs_curExtra4_par decimal(12,2),
	@scs_curExtra5_par decimal(12,2),
	@scs_pKwalifikatorEx_par integer) with encryption as 
	update n5straznik_cen set VersionId=@versionid_par,
	scs_strNazwa=@scs_strNazwa_par,
	scs_wpProdGrupa=@scs_wpProdGrupa_par,
	scs_wpProdGrupa_wrt=@scs_wpProdGrupa_wrt_par,
	scs_wpKlientGrupa=@scs_wpKlientGrupa_par,
	scs_wpKlientGrupa_wrt=@scs_wpKlientGrupa_wrt_par,
	scs_curModyfikator=@scs_curModyfikator_par,
	scs_eZestawCenowy=@scs_eZestawCenowy_par,
	scs_eAktywny=@scs_eAktywny_par,
	scs_strExtra1=@scs_strExtra1_par,
	scs_strExtra2=@scs_strExtra2_par,
	scs_dExtra3=@scs_dExtra3_par,
	scs_curExtra4=@scs_curExtra4_par,
	scs_curExtra5=@scs_curExtra5_par,
	scs_pKwalifikatorEx=@scs_pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5straznik_cen_delete(@idobj_par integer) with encryption as 
	delete from n5straznik_cen where idobj=@idobj_par
return @@rowcount
go

create procedure n5straznik_cen_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5straznik_cen
go

create procedure n5straznik_cen_candel(@idobj_par integer) with encryption as 
go

alter table n5straznik_cen add constraint PK_n5straznik_cen_IdObj primary key clustered (IdObj)
go

alter table n5straznik_cen add constraint WRT_n5straznik_cen_scs_wpProdGrupa_3 check (
	scs_wpProdGrupa_wrt=0 or 
	scs_wpProdGrupa_wrt=10131 or 
	scs_wpProdGrupa_wrt=10116
)
go
alter table n5straznik_cen add constraint WRT_n5straznik_cen_scs_wpKlientGrupa_4 check (
	scs_wpKlientGrupa_wrt=0 or 
	scs_wpKlientGrupa_wrt=10108 or 
	scs_wpKlientGrupa_wrt=10118
)
go
alter table n5straznik_cen add constraint ENUM_n5straznik_cen_scs_eZestawCenowy_6 check (
scs_eZestawCenowy between 0 and 6
)
go
alter table n5straznik_cen add constraint ENUM_n5straznik_cen_scs_eAktywny_7 check (
scs_eAktywny between 0 and 2
)
go

--========== creating integrity test stored procedure

if exists (select * from sysobjects where name='n5check')
	drop procedure n5check
go

create procedure n5check with encryption as 
select 10125,n5zadaniezal.IdObj, 1 from n5zadaniezal
	left outer join n5dokument on n5zadaniezal.wrefZal=n5dokument.IdObj and n5zadaniezal.wrefZal_wrt=10117
	left outer join n5zadanie on n5zadaniezal.wrefZal=n5zadanie.IdObj and n5zadaniezal.wrefZal_wrt=10119
 where 
	(n5dokument.IdObj is null) and 
	(n5zadanie.IdObj is null)

select 10122,n5wykonawca.IdObj, 1 from n5wykonawca
	left outer join n5pracownik on n5wykonawca.wrefObiekt=n5pracownik.IdObj and n5wykonawca.wrefObiekt_wrt=10109
	left outer join n5klient_pracownik on n5wykonawca.wrefObiekt=n5klient_pracownik.IdObj and n5wykonawca.wrefObiekt_wrt=10112
	left outer join n5klient on n5wykonawca.wrefObiekt=n5klient.IdObj and n5wykonawca.wrefObiekt_wrt=10108
 where 
	(n5pracownik.IdObj is null) and 
	(n5klient_pracownik.IdObj is null) and 
	(n5klient.IdObj is null)

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

select 10213,n5bwinfo_zal.IdObj, 1 from n5bwinfo_zal
	left outer join n5dokument on n5bwinfo_zal.wrefZal=n5dokument.IdObj and n5bwinfo_zal.wrefZal_wrt=10117
	left outer join n5bwinfo on n5bwinfo_zal.wrefZal=n5bwinfo.IdObj and n5bwinfo_zal.wrefZal_wrt=10211
 where 
	(n5dokument.IdObj is null) and 
	(n5bwinfo.IdObj is null)

select 10212,n5bwinfo_produkt.IdObj, 1 from n5bwinfo_produkt
	left outer join n5produkt on n5bwinfo_produkt.wpProdGrupa=n5produkt.IdObj and n5bwinfo_produkt.wpProdGrupa_wrt=10131
	left outer join n5grupaproduktow on n5bwinfo_produkt.wpProdGrupa=n5grupaproduktow.IdObj and n5bwinfo_produkt.wpProdGrupa_wrt=10116
 where 
	(n5produkt.IdObj is null) and 
	(n5grupaproduktow.IdObj is null)

select 10111,t1.IdObj, 2 from n5miejscowosc t1 
 left outer join n5region t2 on t1.pRegion=t2.IdObj where (t1.pRegion<>0 and t2.IdObj is null)

select 10111,t1.IdObj, 2 from n5miejscowosc t1 
 left outer join n5powiat t2 on t1.mie_pPowiat=t2.IdObj where (t1.mie_pPowiat<>0 and t2.IdObj is null)

select 10111,t1.IdObj, 2 from n5miejscowosc t1 
 left outer join n5gmina t2 on t1.mie_pGmina=t2.IdObj where (t1.mie_pGmina<>0 and t2.IdObj is null)

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

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank4=t2.IdObj where (t1.pBank4<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank5=t2.IdObj where (t1.pBank5<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank6=t2.IdObj where (t1.pBank6<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank7=t2.IdObj where (t1.pBank7<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank8=t2.IdObj where (t1.pBank8<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank9=t2.IdObj where (t1.pBank9<>0 and t2.IdObj is null)

select 10110,t1.IdObj, 2 from n5firma t1 
 left outer join n5bank t2 on t1.pBank10=t2.IdObj where (t1.pBank10<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowy=t2.IdObj where (t1.pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5miejscowosc t2 on t1.pprac_Miejscowosc_zameld=t2.IdObj where (t1.pprac_Miejscowosc_zameld<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5kraj t2 on t1.pprac_Kraj_zameld=t2.IdObj where (t1.pprac_Kraj_zameld<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5miejscowosc t2 on t1.pprac_Miejscowosc_koresp=t2.IdObj where (t1.pprac_Miejscowosc_koresp<>0 and t2.IdObj is null)

select 10109,t1.IdObj, 2 from n5pracownik t1 
 left outer join n5kraj t2 on t1.pprac_Kraj_koresp=t2.IdObj where (t1.pprac_Kraj_koresp<>0 and t2.IdObj is null)

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

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5jednostka t2 on t1.kli_pKursIndywidualnyWaluta=t2.IdObj where (t1.kli_pKursIndywidualnyWaluta<>0 and t2.IdObj is null)

select 10108,t1.IdObj, 2 from n5klient t1 
 left outer join n5grupaproduktow t2 on t1.kli_pGrupaProd=t2.IdObj where (t1.kli_pGrupaProd<>0 and t2.IdObj is null)

select 10107,t1.IdObj, 2 from n5uzytkownik t1 
 left outer join n5wykonawca t2 on t1.pWykonawca=t2.IdObj where (t1.pWykonawca<>0 and t2.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank1=t2.IdObj where (t1.pBank1<>0 and t2.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank2=t2.IdObj where (t1.pBank2<>0 and t2.IdObj is null)

select 10105,t1.IdObj, 2 from n5instytucja t1 
 left outer join n5bank t2 on t1.pBank3=t2.IdObj where (t1.pBank3<>0 and t2.IdObj is null)

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

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5klient_obiekt t2 on t1.zad_pKLOB=t2.IdObj where (t1.zad_pKLOB<>0 and t2.IdObj is null)

select 10119,t1.IdObj, 2 from n5zadanie t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

select 10118,t1.IdObj, 2 from n5grupaklient t1 
 left outer join n5grupaklient t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10118,t1.IdObj, 2 from n5grupaklient t1 
 left outer join n5jednostka t2 on t1.pWalutaLimitu=t2.IdObj where (t1.pWalutaLimitu<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5uzytkownik t2 on t1.pUzytkWypoz=t2.IdObj where (t1.pUzytkWypoz<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5dokument t2 on t1.pReplaces=t2.IdObj where (t1.pReplaces<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5dokument t2 on t1.pReplaced=t2.IdObj where (t1.pReplaced<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5klient_pracownik t2 on t1.dok_pUFPracKlient13=t2.IdObj where (t1.dok_pUFPracKlient13<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5klient_pracownik t2 on t1.dok_pUFPracKlient14=t2.IdObj where (t1.dok_pUFPracKlient14<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5klient t2 on t1.dok_pUFKlient15=t2.IdObj where (t1.dok_pUFKlient15<>0 and t2.IdObj is null)

select 10117,t1.IdObj, 2 from n5dokument t1 
 left outer join n5sposplat t2 on t1.dok_pSposobPlatnosci=t2.IdObj where (t1.dok_pSposobPlatnosci<>0 and t2.IdObj is null)

select 10116,t1.IdObj, 2 from n5grupaproduktow t1 
 left outer join n5grupaproduktow t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10116,t1.IdObj, 2 from n5grupaproduktow t1 
 left outer join n5jednostka t2 on t1.grp_pJednostkaEwid=t2.IdObj where (t1.grp_pJednostkaEwid<>0 and t2.IdObj is null)

select 10116,t1.IdObj, 2 from n5grupaproduktow t1 
 left outer join n5klient t2 on t1.grp_pDostawca=t2.IdObj where (t1.grp_pDostawca<>0 and t2.IdObj is null)

select 10116,t1.IdObj, 2 from n5grupaproduktow t1 
 left outer join n5pracownik t2 on t1.grp_pPracownik=t2.IdObj where (t1.grp_pPracownik<>0 and t2.IdObj is null)

select 10115,t1.IdObj, 2 from n5typdokumentu t1 
 left outer join n5typdokumentu t2 on t1.pTypNadrzedny=t2.IdObj where (t1.pTypNadrzedny<>0 and t2.IdObj is null)

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

select 10112,t1.IdObj, 2 from n5klient_pracownik t1 
 left outer join n5_klient_jedn_org t2 on t1.pJednOrgKlienta=t2.IdObj where (t1.pJednOrgKlienta<>0 and t2.IdObj is null)

select 10112,t1.IdObj, 2 from n5klient_pracownik t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5instytucja t2 on t1.vtue_pUrzadSkarbowy=t2.IdObj where (t1.vtue_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5uzytkownik t2 on t1.vtue_pUzytRej=t2.IdObj where (t1.vtue_pUzytRej<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5zadanie t2 on t1.vtue_pZadanie=t2.IdObj where (t1.vtue_pZadanie<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5schematdekr t2 on t1.vtue_pSchematDekr=t2.IdObj where (t1.vtue_pSchematDekr<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5dowodksieg t2 on t1.vtue_pDowKsieg=t2.IdObj where (t1.vtue_pDowKsieg<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5transakcja t2 on t1.vtue_pTransakcja=t2.IdObj where (t1.vtue_pTransakcja<>0 and t2.IdObj is null)

select 10143,t1.IdObj, 2 from n5vatue t1 
 left outer join n5uzytkownik t2 on t1.vtue_pUzytModyf=t2.IdObj where (t1.vtue_pUzytModyf<>0 and t2.IdObj is null)

select 10140,t1.IdObj, 2 from n5gmina t1 
 left outer join n5wojewodztwo t2 on t1.gmi_pWojewodztwo=t2.IdObj where (t1.gmi_pWojewodztwo<>0 and t2.IdObj is null)

select 10140,t1.IdObj, 2 from n5gmina t1 
 left outer join n5powiat t2 on t1.gmi_pPowiat=t2.IdObj where (t1.gmi_pPowiat<>0 and t2.IdObj is null)

select 10139,t1.IdObj, 2 from n5powiat t1 
 left outer join n5wojewodztwo t2 on t1.pow_pWojewodztwo=t2.IdObj where (t1.pow_pWojewodztwo<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5instytucja t2 on t1.pt11_pUrzadSkarbowy=t2.IdObj where (t1.pt11_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5uzytkownik t2 on t1.pt11_pUzytRej=t2.IdObj where (t1.pt11_pUzytRej<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5zadanie t2 on t1.pt11_pZadanie=t2.IdObj where (t1.pt11_pZadanie<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5schematdekr t2 on t1.pt11_pSchematDekr=t2.IdObj where (t1.pt11_pSchematDekr<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5dowodksieg t2 on t1.pt11_pDowKsieg=t2.IdObj where (t1.pt11_pDowKsieg<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5transakcja t2 on t1.pt11_pTransakcja=t2.IdObj where (t1.pt11_pTransakcja<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5uzytkownik t2 on t1.pt11_pUzytModyf=t2.IdObj where (t1.pt11_pUzytModyf<>0 and t2.IdObj is null)

select 10138,t1.IdObj, 2 from n5pit11 t1 
 left outer join n5pracownik t2 on t1.pt11_pPodatnik=t2.IdObj where (t1.pt11_pPodatnik<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5instytucja t2 on t1.pt5l_pUrzadSkarbowy=t2.IdObj where (t1.pt5l_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5uzytkownik t2 on t1.pt5l_pUzytRej=t2.IdObj where (t1.pt5l_pUzytRej<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5zadanie t2 on t1.pt5l_pZadanie=t2.IdObj where (t1.pt5l_pZadanie<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5schematdekr t2 on t1.pt5l_pSchematDekr=t2.IdObj where (t1.pt5l_pSchematDekr<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5dowodksieg t2 on t1.pt5l_pDowKsieg=t2.IdObj where (t1.pt5l_pDowKsieg<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5transakcja t2 on t1.pt5l_pTransakcja=t2.IdObj where (t1.pt5l_pTransakcja<>0 and t2.IdObj is null)

select 10137,t1.IdObj, 2 from n5pit5l t1 
 left outer join n5uzytkownik t2 on t1.pt5l_pUzytModyf=t2.IdObj where (t1.pt5l_pUzytModyf<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5instytucja t2 on t1.pt5_pUrzadSkarbowy=t2.IdObj where (t1.pt5_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5uzytkownik t2 on t1.pt5_pUzytRej=t2.IdObj where (t1.pt5_pUzytRej<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5zadanie t2 on t1.pt5_pZadanie=t2.IdObj where (t1.pt5_pZadanie<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5schematdekr t2 on t1.pt5_pSchematDekr=t2.IdObj where (t1.pt5_pSchematDekr<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5dowodksieg t2 on t1.pt5_pDowKsieg=t2.IdObj where (t1.pt5_pDowKsieg<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5transakcja t2 on t1.pt5_pTransakcja=t2.IdObj where (t1.pt5_pTransakcja<>0 and t2.IdObj is null)

select 10136,t1.IdObj, 2 from n5pit5 t1 
 left outer join n5uzytkownik t2 on t1.pt5_pUzytModyf=t2.IdObj where (t1.pt5_pUzytModyf<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5instytucja t2 on t1.pt4_pUrzadSkarbowy=t2.IdObj where (t1.pt4_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5uzytkownik t2 on t1.pt4_pUzytRej=t2.IdObj where (t1.pt4_pUzytRej<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5zadanie t2 on t1.pt4_pZadanie=t2.IdObj where (t1.pt4_pZadanie<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5schematdekr t2 on t1.pt4_pSchematDekr=t2.IdObj where (t1.pt4_pSchematDekr<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5dowodksieg t2 on t1.pt4_pDowKsieg=t2.IdObj where (t1.pt4_pDowKsieg<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5transakcja t2 on t1.pt4_pTransakcja=t2.IdObj where (t1.pt4_pTransakcja<>0 and t2.IdObj is null)

select 10135,t1.IdObj, 2 from n5pit4 t1 
 left outer join n5uzytkownik t2 on t1.pt4_pUzytModyf=t2.IdObj where (t1.pt4_pUzytModyf<>0 and t2.IdObj is null)

select 10134,t1.IdObj, 2 from n5pkpir t1 
 left outer join n5klient t2 on t1.pKlient=t2.IdObj where (t1.pKlient<>0 and t2.IdObj is null)

select 10134,t1.IdObj, 2 from n5pkpir t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5kodpcn t2 on t1.prod_pKodCelny=t2.IdObj where (t1.prod_pKodCelny<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5dokument t2 on t1.pUlotka=t2.IdObj where (t1.pUlotka<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5dokument t2 on t1.pInstrukcja=t2.IdObj where (t1.pInstrukcja<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5klient t2 on t1.prod_pDostawca=t2.IdObj where (t1.prod_pDostawca<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5kraj t2 on t1.prod_pKrajPoch=t2.IdObj where (t1.prod_pKrajPoch<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5paleta_kolorow t2 on t1.prod_pPaletaKolorow=t2.IdObj where (t1.prod_pPaletaKolorow<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5tabela_rozmiarow t2 on t1.prod_pTabelaRozmiarow=t2.IdObj where (t1.prod_pTabelaRozmiarow<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pProdMag=t2.IdObj where (t1.prod_pProdMag<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5pracownik t2 on t1.prod_pPracownik=t2.IdObj where (t1.prod_pPracownik<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pZamiennik1=t2.IdObj where (t1.prod_pZamiennik1<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pZamiennik2=t2.IdObj where (t1.prod_pZamiennik2<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pZamiennik3=t2.IdObj where (t1.prod_pZamiennik3<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pZamiennik4=t2.IdObj where (t1.prod_pZamiennik4<>0 and t2.IdObj is null)

select 10131,t1.IdObj, 2 from n5produkt t1 
 left outer join n5produkt t2 on t1.prod_pZamiennik5=t2.IdObj where (t1.prod_pZamiennik5<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakowanieJedn=t2.IdObj where (t1.pOpakowanieJedn<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5opakowanie_produktu t2 on t1.pZamiennik=t2.IdObj where (t1.pZamiennik<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5kolor t2 on t1.opak_pKolor=t2.IdObj where (t1.opak_pKolor<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5rozmiar t2 on t1.opak_pRozmiar=t2.IdObj where (t1.opak_pRozmiar<>0 and t2.IdObj is null)

select 10130,t1.IdObj, 2 from n5opakowanie_produktu t1 
 left outer join n5opakowanie_produktu t2 on t1.opak_pOpakMag=t2.IdObj where (t1.opak_pOpakMag<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5zadanie t2 on t1.psprzed_pZadanie=t2.IdObj where (t1.psprzed_pZadanie<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5klient_obiekt t2 on t1.psprzed_pKLOB=t2.IdObj where (t1.psprzed_pKLOB<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5produkt t2 on t1.pProduktOrg=t2.IdObj where (t1.pProduktOrg<>0 and t2.IdObj is null)

select 10132,t1.IdObj, 2 from n5pozsprzedaz t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakOrg=t2.IdObj where (t1.pOpakOrg<>0 and t2.IdObj is null)

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
 left outer join n5rozlvat t2 on t1.pRozlVat=t2.IdObj where (t1.pRozlVat<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5zamowienie t2 on t1.pZamowienie=t2.IdObj where (t1.pZamowienie<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5pkpir t2 on t1.sprzed_pPKPIR=t2.IdObj where (t1.sprzed_pPKPIR<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5sposdost t2 on t1.sprzed_pSposobDostawy=t2.IdObj where (t1.sprzed_pSposobDostawy<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5pracownik t2 on t1.sprzed_pHandlowiec=t2.IdObj where (t1.sprzed_pHandlowiec<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

select 10129,t1.IdObj, 2 from n5sprzedaz t1 
 left outer join n5sprzedaz t2 on t1.sprzed_pDostawa=t2.IdObj where (t1.sprzed_pDostawa<>0 and t2.IdObj is null)

select 10158,t1.IdObj, 2 from n5rapkas t1 
 left outer join n5dowodksieg t2 on t1.raka_pDowodKsieg=t2.IdObj where (t1.raka_pDowodKsieg<>0 and t2.IdObj is null)

select 10158,t1.IdObj, 2 from n5rapkas t1 
 left outer join n5schematdekr t2 on t1.raka_pSchematDekr=t2.IdObj where (t1.raka_pSchematDekr<>0 and t2.IdObj is null)

select 10158,t1.IdObj, 2 from n5rapkas t1 
 left outer join n5pkpir t2 on t1.raka_pPKPIR=t2.IdObj where (t1.raka_pPKPIR<>0 and t2.IdObj is null)

select 10158,t1.IdObj, 2 from n5rapkas t1 
 left outer join n5kwalifikator t2 on t1.raka_pKwalifikatorEx=t2.IdObj where (t1.raka_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10157,t1.IdObj, 2 from n5branza t1 
 left outer join n5branza t2 on t1.pBranzaNad=t2.IdObj where (t1.pBranzaNad<>0 and t2.IdObj is null)

select 10154,t1.IdObj, 2 from n5transakcja t1 
 left outer join n5notaods t2 on t1.pNotaOds=t2.IdObj where (t1.pNotaOds<>0 and t2.IdObj is null)

select 10154,t1.IdObj, 2 from n5transakcja t1 
 left outer join n5pracownik t2 on t1.trn_pHandlowiec=t2.IdObj where (t1.trn_pHandlowiec<>0 and t2.IdObj is null)

select 10153,t1.IdObj, 2 from n5typdzialania t1 
 left outer join n5typdzialania t2 on t1.pTypNadrzedny=t2.IdObj where (t1.pTypNadrzedny<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5pkpir t2 on t1.plat_pPKPIR=t2.IdObj where (t1.plat_pPKPIR<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5rapkas t2 on t1.plat_pRapKas=t2.IdObj where (t1.plat_pRapKas<>0 and t2.IdObj is null)

select 10150,t1.IdObj, 2 from n5platnosc t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

select 10149,t1.IdObj, 2 from n5egzemplarz t1 
 left outer join n5magazyn t2 on t1.egze_pMagazyn=t2.IdObj where (t1.egze_pMagazyn<>0 and t2.IdObj is null)

select 10149,t1.IdObj, 2 from n5egzemplarz t1 
 left outer join n5klient t2 on t1.egze_pKlient=t2.IdObj where (t1.egze_pKlient<>0 and t2.IdObj is null)

select 10149,t1.IdObj, 2 from n5egzemplarz t1 
 left outer join n5jedn_org t2 on t1.egze_pKlientJO=t2.IdObj where (t1.egze_pKlientJO<>0 and t2.IdObj is null)

select 10149,t1.IdObj, 2 from n5egzemplarz t1 
 left outer join n5klient_pracownik t2 on t1.egze_pKlientPracownik=t2.IdObj where (t1.egze_pKlientPracownik<>0 and t2.IdObj is null)

select 10149,t1.IdObj, 2 from n5egzemplarz t1 
 left outer join n5klient_obiekt t2 on t1.egze_pKlientObiekt=t2.IdObj where (t1.egze_pKlientObiekt<>0 and t2.IdObj is null)

select 10147,t1.IdObj, 2 from n5dekret t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10147,t1.IdObj, 2 from n5dekret t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikator=t2.IdObj where (t1.pKwalifikator<>0 and t2.IdObj is null)

select 10146,t1.IdObj, 2 from n5konto t1 
 left outer join n5konto t2 on t1.pKontoNadrz=t2.IdObj where (t1.pKontoNadrz<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5schematdekr t2 on t1.pDefSchematdekr=t2.IdObj where (t1.pDefSchematdekr<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5rokksieg t2 on t1.pRokKsieg=t2.IdObj where (t1.pRokKsieg<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5schematdekr t2 on t1.rejdok_pDefSchematdekr2=t2.IdObj where (t1.rejdok_pDefSchematdekr2<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5klient t2 on t1.rejdok_pDefKlient=t2.IdObj where (t1.rejdok_pDefKlient<>0 and t2.IdObj is null)

select 10145,t1.IdObj, 2 from n5rejestrdok t1 
 left outer join n5rejestrdok t2 on t1.rejdok_pRejestrParam4=t2.IdObj where (t1.rejdok_pRejestrParam4<>0 and t2.IdObj is null)

select 10144,t1.IdObj, 2 from n5pozvatue t1 
 left outer join n5klient t2 on t1.pvtue_refKlient=t2.IdObj where (t1.pvtue_refKlient<>0 and t2.IdObj is null)

select 10156,t1.IdObj, 2 from n5pozrata t1 
 left outer join n5transakcja t2 on t1.prat_pTransakcja=t2.IdObj where (t1.prat_pTransakcja<>0 and t2.IdObj is null)

select 10175,t1.IdObj, 2 from n5pozzakup t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10175,t1.IdObj, 2 from n5pozzakup t1 
 left outer join n5zadanie t2 on t1.pzak_pZadanie=t2.IdObj where (t1.pzak_pZadanie<>0 and t2.IdObj is null)

select 10175,t1.IdObj, 2 from n5pozzakup t1 
 left outer join n5klient_obiekt t2 on t1.pzak_pObiektKlienta=t2.IdObj where (t1.pzak_pObiektKlienta<>0 and t2.IdObj is null)

select 10169,t1.IdObj, 2 from n5proglojal t1 
 left outer join n5klient_pracownik t2 on t1.proloj_pPracKlient=t2.IdObj where (t1.proloj_pPracKlient<>0 and t2.IdObj is null)

select 10169,t1.IdObj, 2 from n5proglojal t1 
 left outer join n5sprzedaz t2 on t1.proloj_pSprzedaz=t2.IdObj where (t1.proloj_pSprzedaz<>0 and t2.IdObj is null)

select 10169,t1.IdObj, 2 from n5proglojal t1 
 left outer join n5dokmag t2 on t1.proloj_pDokMag=t2.IdObj where (t1.proloj_pDokMag<>0 and t2.IdObj is null)

select 10167,t1.IdObj, 2 from n5pozdoketyk t1 
 left outer join n5kwalifikator t2 on t1.pdet_pKwalifikatorEx=t2.IdObj where (t1.pdet_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10166,t1.IdObj, 2 from n5doketyk t1 
 left outer join n5kwalifikator t2 on t1.doet_pKwalifikatorEx=t2.IdObj where (t1.doet_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10166,t1.IdObj, 2 from n5doketyk t1 
 left outer join n5dokmag t2 on t1.doet_pDokMag=t2.IdObj where (t1.doet_pDokMag<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5magazyn t2 on t1.pMagZrod=t2.IdObj where (t1.pMagZrod<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5magazyn t2 on t1.pMagDocel=t2.IdObj where (t1.pMagDocel<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10161,t1.IdObj, 2 from n5pozdokmag t1 
 left outer join n5klient_obiekt t2 on t1.pdm_pObiektKlienta=t2.IdObj where (t1.pdm_pObiektKlienta<>0 and t2.IdObj is null)

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

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5zamowienie t2 on t1.pZamowienie=t2.IdObj where (t1.pZamowienie<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5sposdost t2 on t1.zam_pSposobDostawy=t2.IdObj where (t1.zam_pSposobDostawy<>0 and t2.IdObj is null)

select 10172,t1.IdObj, 2 from n5zamowienie t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

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

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5sposdost t2 on t1.dm_pSposobDostawy=t2.IdObj where (t1.dm_pSposobDostawy<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10162,t1.IdObj, 2 from n5dokmag t1 
 left outer join n5klient_obiekt t2 on t1.pObiektKlienta=t2.IdObj where (t1.pObiektKlienta<>0 and t2.IdObj is null)

select 10173,t1.IdObj, 2 from n5pozzamowienie t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10173,t1.IdObj, 2 from n5pozzamowienie t1 
 left outer join n5zadanie t2 on t1.pzam_pZadanie=t2.IdObj where (t1.pzam_pZadanie<>0 and t2.IdObj is null)

select 10173,t1.IdObj, 2 from n5pozzamowienie t1 
 left outer join n5produkt t2 on t1.pProduktOrg=t2.IdObj where (t1.pProduktOrg<>0 and t2.IdObj is null)

select 10173,t1.IdObj, 2 from n5pozzamowienie t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpakOrg=t2.IdObj where (t1.pOpakOrg<>0 and t2.IdObj is null)

select 10190,t1.IdObj, 2 from n5plschematnal t1 
 left outer join n5jednostka t2 on t1.pJednostkaParam1=t2.IdObj where (t1.pJednostkaParam1<>0 and t2.IdObj is null)

select 10190,t1.IdObj, 2 from n5plschematnal t1 
 left outer join n5jednostka t2 on t1.pJednostkaParam2=t2.IdObj where (t1.pJednostkaParam2<>0 and t2.IdObj is null)

select 10189,t1.IdObj, 2 from n5polrab t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpak=t2.IdObj where (t1.pOpak<>0 and t2.IdObj is null)

select 10189,t1.IdObj, 2 from n5polrab t1 
 left outer join n5jedn_org t2 on t1.polrab_pJednOrg=t2.IdObj where (t1.polrab_pJednOrg<>0 and t2.IdObj is null)

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

select 10187,t1.IdObj, 2 from n5zlecprod t1 
 left outer join n5zlecprod t2 on t1.pNadZlec=t2.IdObj where (t1.pNadZlec<>0 and t2.IdObj is null)

select 10186,t1.IdObj, 2 from n5pozzlecprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10184,t1.IdObj, 2 from n5pozrecepta t1 
 left outer join n5opakowanie_produktu t2 on t1.pZamiennik1=t2.IdObj where (t1.pZamiennik1<>0 and t2.IdObj is null)

select 10184,t1.IdObj, 2 from n5pozrecepta t1 
 left outer join n5opakowanie_produktu t2 on t1.pZamiennik2=t2.IdObj where (t1.pZamiennik2<>0 and t2.IdObj is null)

select 10184,t1.IdObj, 2 from n5pozrecepta t1 
 left outer join n5opakowanie_produktu t2 on t1.pZamiennik3=t2.IdObj where (t1.pZamiennik3<>0 and t2.IdObj is null)

select 10179,t1.IdObj, 2 from n5srtrw t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10179,t1.IdObj, 2 from n5srtrw t1 
 left outer join n5jedn_org t2 on t1.pMUJO=t2.IdObj where (t1.pMUJO<>0 and t2.IdObj is null)

select 10179,t1.IdObj, 2 from n5srtrw t1 
 left outer join n5jedn_org t2 on t1.srtrw_pJednOrg=t2.IdObj where (t1.srtrw_pJednOrg<>0 and t2.IdObj is null)

select 10178,t1.IdObj, 2 from n5grupasrtrw t1 
 left outer join n5grupasrtrw t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5instytucja t2 on t1.vat7_pUrzadSkarbowy=t2.IdObj where (t1.vat7_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5uzytkownik t2 on t1.vat7_pUzytRej=t2.IdObj where (t1.vat7_pUzytRej<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5zadanie t2 on t1.vat7_pZadanie=t2.IdObj where (t1.vat7_pZadanie<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5schematdekr t2 on t1.vat7_pSchematDekr=t2.IdObj where (t1.vat7_pSchematDekr<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5dowodksieg t2 on t1.vat7_pDowKsieg=t2.IdObj where (t1.vat7_pDowKsieg<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5transakcja t2 on t1.vat7_pTransakcja=t2.IdObj where (t1.vat7_pTransakcja<>0 and t2.IdObj is null)

select 10177,t1.IdObj, 2 from n5rozlvat t1 
 left outer join n5uzytkownik t2 on t1.vat7_pUzytModyf=t2.IdObj where (t1.vat7_pUzytModyf<>0 and t2.IdObj is null)

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

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5transakcja t2 on t1.pTransakcjaImport=t2.IdObj where (t1.pTransakcjaImport<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5instytucja t2 on t1.pUrzadCelny=t2.IdObj where (t1.pUrzadCelny<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5zamowienie t2 on t1.pZamowienie=t2.IdObj where (t1.pZamowienie<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5pkpir t2 on t1.zak_pPKPIR=t2.IdObj where (t1.zak_pPKPIR<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5sposdost t2 on t1.zak_pSposobDostawy=t2.IdObj where (t1.zak_pSposobDostawy<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5klient_pracownik t2 on t1.zak_pKlientPracownik=t2.IdObj where (t1.zak_pKlientPracownik<>0 and t2.IdObj is null)

select 10176,t1.IdObj, 2 from n5zakup t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

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

select 10206,t1.IdObj, 2 from n5realprod t1 
 left outer join n5dokstatus t2 on t1.pDokStatus=t2.IdObj where (t1.pDokStatus<>0 and t2.IdObj is null)

select 10205,t1.IdObj, 2 from n5pozrealprod t1 
 left outer join n5magazyn t2 on t1.pMagazyn=t2.IdObj where (t1.pMagazyn<>0 and t2.IdObj is null)

select 10205,t1.IdObj, 2 from n5pozrealprod t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10205,t1.IdObj, 2 from n5pozrealprod t1 
 left outer join n5recepta t2 on t1.pozreal_pRecepta=t2.IdObj where (t1.pozreal_pRecepta<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5zadanie t2 on t1.pZadanie=t2.IdObj where (t1.pZadanie<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5dowodksieg t2 on t1.pDowKsieg=t2.IdObj where (t1.pDowKsieg<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10203,t1.IdObj, 2 from n5rozlcit t1 
 left outer join n5instytucja t2 on t1.pUrzadSkarbowy=t2.IdObj where (t1.pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10202,t1.IdObj, 2 from n5plnieob t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10201,t1.IdObj, 2 from n5plchoroba t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5plumowa t2 on t1.pUmowaPop=t2.IdObj where (t1.pUmowaPop<>0 and t2.IdObj is null)

select 10199,t1.IdObj, 2 from n5plumowa t1 
 left outer join n5plkalcp t2 on t1.pKalendarz=t2.IdObj where (t1.pKalendarz<>0 and t2.IdObj is null)

select 10194,t1.IdObj, 2 from n5pllistaplac t1 
 left outer join n5dowodksieg t2 on t1.lppl_pDowodKsieg=t2.IdObj where (t1.lppl_pDowodKsieg<>0 and t2.IdObj is null)

select 10194,t1.IdObj, 2 from n5pllistaplac t1 
 left outer join n5schematdekr t2 on t1.lppl_pSchematDekr=t2.IdObj where (t1.lppl_pSchematDekr<>0 and t2.IdObj is null)

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

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5pkpir t2 on t1.plnal_pPKPIR=t2.IdObj where (t1.plnal_pPKPIR<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaUS=t2.IdObj where (t1.plnal_pTransakcjaUS<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaZUS51=t2.IdObj where (t1.plnal_pTransakcjaZUS51<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaZUS52=t2.IdObj where (t1.plnal_pTransakcjaZUS52<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaZUS53=t2.IdObj where (t1.plnal_pTransakcjaZUS53<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaInne=t2.IdObj where (t1.plnal_pTransakcjaInne<>0 and t2.IdObj is null)

select 10192,t1.IdObj, 2 from n5plnaliczenie t1 
 left outer join n5transakcja t2 on t1.plnal_pTransakcjaInne2=t2.IdObj where (t1.plnal_pTransakcjaInne2<>0 and t2.IdObj is null)

select 10222,t1.IdObj, 2 from n5plgrupaschemnal t1 
 left outer join n5plgrupaschemnal t2 on t1.pGrupaNadrzedna=t2.IdObj where (t1.pGrupaNadrzedna<>0 and t2.IdObj is null)

select 10221,t1.IdObj, 2 from n5plpozostale t1 
 left outer join n5pracownik t2 on t1.pPracownik=t2.IdObj where (t1.pPracownik<>0 and t2.IdObj is null)

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

select 10216,t1.IdObj, 2 from n5opsrtrw t1 
 left outer join n5pkpir t2 on t1.opsrtrw_pPKPIR=t2.IdObj where (t1.opsrtrw_pPKPIR<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5dowodksieg t2 on t1.pDowodKsieg=t2.IdObj where (t1.pDowodKsieg<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5schematdekr t2 on t1.pSchematDekr=t2.IdObj where (t1.pSchematDekr<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10215,t1.IdObj, 2 from n5notaods t1 
 left outer join n5transakcja t2 on t1.pTransakcja=t2.IdObj where (t1.pTransakcja<>0 and t2.IdObj is null)

select 10212,t1.IdObj, 2 from n5bwinfo_produkt t1 
 left outer join n5opakowanie_produktu t2 on t1.pOpak=t2.IdObj where (t1.pOpak<>0 and t2.IdObj is null)

select 10238,t1.IdObj, 2 from n5pozdokprod t1 
 left outer join n5typdzialania t2 on t1.pdp_pTypDzial=t2.IdObj where (t1.pdp_pTypDzial<>0 and t2.IdObj is null)

select 10236,t1.IdObj, 2 from n5pltyppracy t1 
 left outer join n5produkt t2 on t1.tpr_pUsluga=t2.IdObj where (t1.tpr_pUsluga<>0 and t2.IdObj is null)

select 10236,t1.IdObj, 2 from n5pltyppracy t1 
 left outer join n5opakowanie_produktu t2 on t1.tpr_pOpak=t2.IdObj where (t1.tpr_pOpak<>0 and t2.IdObj is null)

select 10235,t1.IdObj, 2 from n5plrcp t1 
 left outer join n5zadanie t2 on t1.rcp_pZadanie=t2.IdObj where (t1.rcp_pZadanie<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5_klient_jedn_org t2 on t1.klob_pKlientJO=t2.IdObj where (t1.klob_pKlientJO<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5klient_pracownik t2 on t1.klob_pKlientPracownik=t2.IdObj where (t1.klob_pKlientPracownik<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5miejscowosc t2 on t1.klob_pMiejscowosc=t2.IdObj where (t1.klob_pMiejscowosc<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5kraj t2 on t1.klob_pKraj=t2.IdObj where (t1.klob_pKraj<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5pracownik t2 on t1.klob_pPracownik=t2.IdObj where (t1.klob_pPracownik<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5kwalifikator t2 on t1.pKwalifikatorEx=t2.IdObj where (t1.pKwalifikatorEx<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5produkt t2 on t1.klob_pProdukt=t2.IdObj where (t1.klob_pProdukt<>0 and t2.IdObj is null)

select 10234,t1.IdObj, 2 from n5klient_obiekt t1 
 left outer join n5opakowanie_produktu t2 on t1.klob_pOpak=t2.IdObj where (t1.klob_pOpak<>0 and t2.IdObj is null)

select 10228,t1.IdObj, 2 from n5pozistat t1 
 left outer join n5produkt t2 on t1.pistt_pProdukt=t2.IdObj where (t1.pistt_pProdukt<>0 and t2.IdObj is null)

select 10228,t1.IdObj, 2 from n5pozistat t1 
 left outer join n5opakowanie_produktu t2 on t1.pistt_pOpak=t2.IdObj where (t1.pistt_pOpak<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5instytucja t2 on t1.istt_pUrzadSkarbowy=t2.IdObj where (t1.istt_pUrzadSkarbowy<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5uzytkownik t2 on t1.istt_pUzytRej=t2.IdObj where (t1.istt_pUzytRej<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5zadanie t2 on t1.istt_pZadanie=t2.IdObj where (t1.istt_pZadanie<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5schematdekr t2 on t1.istt_pSchematDekr=t2.IdObj where (t1.istt_pSchematDekr<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5dowodksieg t2 on t1.istt_pDowKsieg=t2.IdObj where (t1.istt_pDowKsieg<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5transakcja t2 on t1.istt_pTransakcja=t2.IdObj where (t1.istt_pTransakcja<>0 and t2.IdObj is null)

select 10227,t1.IdObj, 2 from n5istat t1 
 left outer join n5uzytkownik t2 on t1.istt_pUzytModyf=t2.IdObj where (t1.istt_pUzytModyf<>0 and t2.IdObj is null)

select 10244,t1.IdObj, 2 from n5protokol_abas t1 
 left outer join n5projekt_abas t2 on t1.prot_pProjekt=t2.IdObj where (t1.prot_pProjekt<>0 and t2.IdObj is null)

select 10244,t1.IdObj, 2 from n5protokol_abas t1 
 left outer join n5sprzedaz t2 on t1.prot_pFaktura=t2.IdObj where (t1.prot_pFaktura<>0 and t2.IdObj is null)

select 10244,t1.IdObj, 2 from n5protokol_abas t1 
 left outer join n5kwalifikator t2 on t1.prot_pKwalifikatorEx=t2.IdObj where (t1.prot_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10243,t1.IdObj, 2 from n5pozprojekt_abas t1 
 left outer join n5kwalifikator t2 on t1.pproj_pKwalifikatorEx=t2.IdObj where (t1.pproj_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5miejscowosc t2 on t1.proj_pMiejscowosc=t2.IdObj where (t1.proj_pMiejscowosc<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5pracownik t2 on t1.proj_pPracownik=t2.IdObj where (t1.proj_pPracownik<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5_klient_jedn_org t2 on t1.proj_pKlient_JO=t2.IdObj where (t1.proj_pKlient_JO<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5klient_pracownik t2 on t1.proj_pKlientPracTech=t2.IdObj where (t1.proj_pKlientPracTech<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5klient_pracownik t2 on t1.proj_pKlientPracFin=t2.IdObj where (t1.proj_pKlientPracFin<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5zamowienie t2 on t1.proj_pZamowienie=t2.IdObj where (t1.proj_pZamowienie<>0 and t2.IdObj is null)

select 10242,t1.IdObj, 2 from n5projekt_abas t1 
 left outer join n5kwalifikator t2 on t1.proj_pKwalifikatorEx=t2.IdObj where (t1.proj_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10270,t1.IdObj, 2 from n5zasobprod t1 
 left outer join n5plkalcp t2 on t1.zsp_pKalendarz=t2.IdObj where (t1.zsp_pKalendarz<>0 and t2.IdObj is null)

select 10270,t1.IdObj, 2 from n5zasobprod t1 
 left outer join n5pracownik t2 on t1.zsp_pPracownik=t2.IdObj where (t1.zsp_pPracownik<>0 and t2.IdObj is null)

select 10287,t1.IdObj, 2 from n5pozankieta_toral t1 
 left outer join n5maszyna_toral t2 on t1.pank_pMaszyna=t2.IdObj where (t1.pank_pMaszyna<>0 and t2.IdObj is null)

select 10287,t1.IdObj, 2 from n5pozankieta_toral t1 
 left outer join n5kwalifikator t2 on t1.pank_pKwalifikatorEx=t2.IdObj where (t1.pank_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10286,t1.IdObj, 2 from n5ankieta_toral t1 
 left outer join n5kwalifikator t2 on t1.ank_pKwalifikatorEx=t2.IdObj where (t1.ank_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10285,t1.IdObj, 2 from n5srodek_lok t1 
 left outer join n5plstawka t2 on t1.slok_pStawka=t2.IdObj where (t1.slok_pStawka<>0 and t2.IdObj is null)

select 10285,t1.IdObj, 2 from n5srodek_lok t1 
 left outer join n5kwalifikator t2 on t1.slok_pKwalifikatorEx=t2.IdObj where (t1.slok_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10284,t1.IdObj, 2 from n5poz_koszt_wyjazdu t1 
 left outer join n5kwalifikator t2 on t1.pdkw_pKwalifikatorEx=t2.IdObj where (t1.pdkw_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10283,t1.IdObj, 2 from n5polecenie_wyjazdu t1 
 left outer join n5dokstatus t2 on t1.pws_pDokStatus=t2.IdObj where (t1.pws_pDokStatus<>0 and t2.IdObj is null)

select 10283,t1.IdObj, 2 from n5polecenie_wyjazdu t1 
 left outer join n5kwalifikator t2 on t1.pws_pKwalifikatorEx=t2.IdObj where (t1.pws_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10282,t1.IdObj, 2 from n5poz_hist_stan t1 
 left outer join n5kwalifikator t2 on t1.pstn_pKwalifikatorEx=t2.IdObj where (t1.pstn_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10281,t1.IdObj, 2 from n5stanowisko t1 
 left outer join n5kwalifikator t2 on t1.stn_pKwalifikatorEx=t2.IdObj where (t1.stn_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10280,t1.IdObj, 2 from n5pojazd t1 
 left outer join n5jedn_org t2 on t1.poj_pJednOrg=t2.IdObj where (t1.poj_pJednOrg<>0 and t2.IdObj is null)

select 10280,t1.IdObj, 2 from n5pojazd t1 
 left outer join n5kwalifikator t2 on t1.poj_pKwalifikatorEx=t2.IdObj where (t1.poj_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10279,t1.IdObj, 2 from n5produkt_magazyn t1 
 left outer join n5produkt t2 on t1.prmg_pProdukt=t2.IdObj where (t1.prmg_pProdukt<>0 and t2.IdObj is null)

select 10279,t1.IdObj, 2 from n5produkt_magazyn t1 
 left outer join n5magazyn t2 on t1.prmg_pMagazyn=t2.IdObj where (t1.prmg_pMagazyn<>0 and t2.IdObj is null)

select 10278,t1.IdObj, 2 from n5pozrejestrdok_mag t1 
 left outer join n5magazyn t2 on t1.prdm_pMagazyn=t2.IdObj where (t1.prdm_pMagazyn<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5egzemplarz t2 on t1.prop_pEgzemplarz=t2.IdObj where (t1.prop_pEgzemplarz<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5zasobprod t2 on t1.prop_pZasob=t2.IdObj where (t1.prop_pZasob<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5typzasobprod t2 on t1.prop_pTypZasobu=t2.IdObj where (t1.prop_pTypZasobu<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5recepta t2 on t1.prop_pOperacja=t2.IdObj where (t1.prop_pOperacja<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5produkt t2 on t1.prop_pProdukt=t2.IdObj where (t1.prop_pProdukt<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5opakowanie_produktu t2 on t1.prop_pOpak=t2.IdObj where (t1.prop_pOpak<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5dokmag t2 on t1.prop_pDokMag=t2.IdObj where (t1.prop_pDokMag<>0 and t2.IdObj is null)

select 10274,t1.IdObj, 2 from n5prop t1 
 left outer join n5realprod t2 on t1.prop_pRealProd=t2.IdObj where (t1.prop_pRealProd<>0 and t2.IdObj is null)

select 10008,t1.IdObj, 2 from n5dpc t1 
 left outer join n5dokument t2 on t1.pDocTemplate=t2.IdObj where (t1.pDocTemplate<>0 and t2.IdObj is null)

select 10004,t1.IdObj, 2 from n5sodgroup t1 
 left outer join n5sodgroup t2 on t1.pSODGroup=t2.IdObj where (t1.pSODGroup<>0 and t2.IdObj is null)

select 10290,t1.IdObj, 2 from n5inwark t1 
 left outer join n5kwalifikator t2 on t1.ia_pKwalifikatorEx=t2.IdObj where (t1.ia_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10289,t1.IdObj, 2 from n5inwmag t1 
 left outer join n5dokmag t2 on t1.im_pIR=t2.IdObj where (t1.im_pIR<>0 and t2.IdObj is null)

select 10289,t1.IdObj, 2 from n5inwmag t1 
 left outer join n5dokmag t2 on t1.im_pIP=t2.IdObj where (t1.im_pIP<>0 and t2.IdObj is null)

select 10289,t1.IdObj, 2 from n5inwmag t1 
 left outer join n5kwalifikator t2 on t1.im_pKwalifikatorEx=t2.IdObj where (t1.im_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10288,t1.IdObj, 2 from n5maszyna_toral t1 
 left outer join n5kwalifikator t2 on t1.masz_pKwalifikatorEx=t2.IdObj where (t1.masz_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10291,t1.IdObj, 2 from n5pozinwark t1 
 left outer join n5kwalifikator t2 on t1.pia_pKwalifikatorEx=t2.IdObj where (t1.pia_pKwalifikatorEx<>0 and t2.IdObj is null)

select 10292,t1.IdObj, 2 from n5straznik_cen t1 
 left outer join n5kwalifikator t2 on t1.scs_pKwalifikatorEx=t2.IdObj where (t1.scs_pKwalifikatorEx<>0 and t2.IdObj is null)

select idcollection, idparent,3 from collections group by idcollection, idparent having max(lp) > count(*)
select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5pracownik on collections.idparent=n5pracownik.idobj where idcollection=10109077 and n5pracownik.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5WizzardEmail on collections.idparent=n5WizzardEmail.idobj where idcollection=10127002 and n5WizzardEmail.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join choicelist on collections.idparent=choicelist.idobj where idcollection=10124004 and choicelist.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5wykonawca on collections.idparent=n5wykonawca.idobj where idcollection=10122004 and n5wykonawca.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zadanie on collections.idparent=n5zadanie.idobj where idcollection=10119035 and n5zadanie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zadanie on collections.idparent=n5zadanie.idobj where idcollection=10119050 and n5zadanie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokument on collections.idparent=n5dokument.idobj where idcollection=10117023 and n5dokument.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokument on collections.idparent=n5dokument.idobj where idcollection=10117041 and n5dokument.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5vatue on collections.idparent=n5vatue.idobj where idcollection=10143029 and n5vatue.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5vatue on collections.idparent=n5vatue.idobj where idcollection=10143030 and n5vatue.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5vatue on collections.idparent=n5vatue.idobj where idcollection=10143031 and n5vatue.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5produkt on collections.idparent=n5produkt.idobj where idcollection=10131012 and n5produkt.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5SendEmail on collections.idparent=n5SendEmail.idobj where idcollection=10128002 and n5SendEmail.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5sprzedaz on collections.idparent=n5sprzedaz.idobj where idcollection=10129013 and n5sprzedaz.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5sprzedaz on collections.idparent=n5sprzedaz.idobj where idcollection=10129069 and n5sprzedaz.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5sprzedaz on collections.idparent=n5sprzedaz.idobj where idcollection=10129075 and n5sprzedaz.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5klient_produkt on collections.idparent=n5klient_produkt.idobj where idcollection=10151005 and n5klient_produkt.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5platnosc on collections.idparent=n5platnosc.idobj where idcollection=10150010 and n5platnosc.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5platnosc on collections.idparent=n5platnosc.idobj where idcollection=10150026 and n5platnosc.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dowodksieg on collections.idparent=n5dowodksieg.idobj where idcollection=10148008 and n5dowodksieg.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5rejestrdok on collections.idparent=n5rejestrdok.idobj where idcollection=10145028 and n5rejestrdok.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5doketyk on collections.idparent=n5doketyk.idobj where idcollection=10166007 and n5doketyk.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zamowienie on collections.idparent=n5zamowienie.idobj where idcollection=10172013 and n5zamowienie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zamowienie on collections.idparent=n5zamowienie.idobj where idcollection=10172037 and n5zamowienie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zamowienie on collections.idparent=n5zamowienie.idobj where idcollection=10172042 and n5zamowienie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokmag on collections.idparent=n5dokmag.idobj where idcollection=10162011 and n5dokmag.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokmag on collections.idparent=n5dokmag.idobj where idcollection=10162030 and n5dokmag.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5dokmag on collections.idparent=n5dokmag.idobj where idcollection=10162035 and n5dokmag.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plschematnal on collections.idparent=n5plschematnal.idobj where idcollection=10190016 and n5plschematnal.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zlecprod on collections.idparent=n5zlecprod.idobj where idcollection=10187012 and n5zlecprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185004 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185005 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185006 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185008 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5recepta on collections.idparent=n5recepta.idobj where idcollection=10185009 and n5recepta.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zakup on collections.idparent=n5zakup.idobj where idcollection=10176012 and n5zakup.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zakup on collections.idparent=n5zakup.idobj where idcollection=10176074 and n5zakup.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5zakup on collections.idparent=n5zakup.idobj where idcollection=10176079 and n5zakup.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206003 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206004 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206007 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206022 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206023 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206025 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5realprod on collections.idparent=n5realprod.idobj where idcollection=10206026 and n5realprod.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plnieob on collections.idparent=n5plnieob.idobj where idcollection=10202008 and n5plnieob.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plchoroba on collections.idparent=n5plchoroba.idobj where idcollection=10201008 and n5plchoroba.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plumowa on collections.idparent=n5plumowa.idobj where idcollection=10199008 and n5plumowa.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plnaliczenie on collections.idparent=n5plnaliczenie.idobj where idcollection=10192015 and n5plnaliczenie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plnaliczenie on collections.idparent=n5plnaliczenie.idobj where idcollection=10192016 and n5plnaliczenie.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plpozostale on collections.idparent=n5plpozostale.idobj where idcollection=10221008 and n5plpozostale.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5plkalcp on collections.idparent=n5plkalcp.idobj where idcollection=10218003 and n5plkalcp.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5notaods on collections.idparent=n5notaods.idobj where idcollection=10215007 and n5notaods.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211007 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211009 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211012 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5bwinfo on collections.idparent=n5bwinfo.idobj where idcollection=10211015 and n5bwinfo.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5istat on collections.idparent=n5istat.idobj where idcollection=10227055 and n5istat.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5protokol_abas on collections.idparent=n5protokol_abas.idobj where idcollection=10244012 and n5protokol_abas.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5projekt_abas on collections.idparent=n5projekt_abas.idobj where idcollection=10242019 and n5projekt_abas.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5ankieta_toral on collections.idparent=n5ankieta_toral.idobj where idcollection=10286005 and n5ankieta_toral.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5polecenie_wyjazdu on collections.idparent=n5polecenie_wyjazdu.idobj where idcollection=10283016 and n5polecenie_wyjazdu.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5polecenie_wyjazdu on collections.idparent=n5polecenie_wyjazdu.idobj where idcollection=10283026 and n5polecenie_wyjazdu.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002003 and SearchType.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002004 and SearchType.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join SearchType on collections.idparent=SearchType.idobj where idcollection=10002005 and SearchType.idobj is null

select distinct collections.idcollection,collections.idparent,4 from collections left outer join n5inwark on collections.idparent=n5inwark.idobj where idcollection=10290006 and n5inwark.idobj is null

select collections.idcollection, collections.idobj,5 from collections left outer join n5poz_hist_stan on collections.idobj=n5poz_hist_stan.idobj where idcollection=10109077 and (n5poz_hist_stan.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5WizzardEmailDokumElem on collections.idobj=n5WizzardEmailDokumElem.idobj where idcollection=10127002 and (n5WizzardEmailDokumElem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join choicelistitem on collections.idobj=choicelistitem.idobj where idcollection=10124004 and (choicelistitem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5rolawyk on collections.idobj=n5rolawyk.idobj where idcollection=10122004 and (n5rolawyk.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5zadaniezal on collections.idobj=n5zadaniezal.idobj where idcollection=10119035 and (n5zadaniezal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5zadanie_rola on collections.idobj=n5zadanie_rola.idobj where idcollection=10119050 and (n5zadanie_rola.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5dokumentlinks on collections.idobj=n5dokumentlinks.idobj where idcollection=10117023 and (n5dokumentlinks.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokprod on collections.idobj=n5pozdokprod.idobj where idcollection=10117041 and (n5pozdokprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozvatue on collections.idobj=n5pozvatue.idobj where idcollection=10143029 and (n5pozvatue.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozvatue on collections.idobj=n5pozvatue.idobj where idcollection=10143030 and (n5pozvatue.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozvatue on collections.idobj=n5pozvatue.idobj where idcollection=10143031 and (n5pozvatue.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5opakowanie_produktu on collections.idobj=n5opakowanie_produktu.idobj where idcollection=10131012 and (n5opakowanie_produktu.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5WizzardEmailDokumElem on collections.idobj=n5WizzardEmailDokumElem.idobj where idcollection=10128002 and (n5WizzardEmailDokumElem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozsprzedaz on collections.idobj=n5pozsprzedaz.idobj where idcollection=10129013 and (n5pozsprzedaz.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrata on collections.idobj=n5pozrata.idobj where idcollection=10129069 and (n5pozrata.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10129075 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5klient_opakowanie on collections.idobj=n5klient_opakowanie.idobj where idcollection=10151005 and (n5klient_opakowanie.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozplatnosc on collections.idobj=n5pozplatnosc.idobj where idcollection=10150010 and (n5pozplatnosc.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10150026 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5dekret on collections.idobj=n5dekret.idobj where idcollection=10148008 and (n5dekret.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrejestrdok_mag on collections.idobj=n5pozrejestrdok_mag.idobj where idcollection=10145028 and (n5pozrejestrdok_mag.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdoketyk on collections.idobj=n5pozdoketyk.idobj where idcollection=10166007 and (n5pozdoketyk.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzamowienie on collections.idobj=n5pozzamowienie.idobj where idcollection=10172013 and (n5pozzamowienie.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrata on collections.idobj=n5pozrata.idobj where idcollection=10172037 and (n5pozrata.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10172042 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokmag on collections.idobj=n5pozdokmag.idobj where idcollection=10162011 and (n5pozdokmag.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokmag_egz on collections.idobj=n5pozdokmag_egz.idobj where idcollection=10162030 and (n5pozdokmag_egz.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10162035 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plpozschnal on collections.idobj=n5plpozschnal.idobj where idcollection=10190016 and (n5plpozschnal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzlecprod on collections.idobj=n5pozzlecprod.idobj where idcollection=10187012 and (n5pozzlecprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta on collections.idobj=n5pozrecepta.idobj where idcollection=10185004 and (n5pozrecepta.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta on collections.idobj=n5pozrecepta.idobj where idcollection=10185005 and (n5pozrecepta.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta on collections.idobj=n5pozrecepta.idobj where idcollection=10185006 and (n5pozrecepta.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta_zasob on collections.idobj=n5pozrecepta_zasob.idobj where idcollection=10185008 and (n5pozrecepta_zasob.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrecepta_oper on collections.idobj=n5pozrecepta_oper.idobj where idcollection=10185009 and (n5pozrecepta_oper.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozzakup on collections.idobj=n5pozzakup.idobj where idcollection=10176012 and (n5pozzakup.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrata on collections.idobj=n5pozrata.idobj where idcollection=10176074 and (n5pozrata.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10176079 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrealprod on collections.idobj=n5pozrealprod.idobj where idcollection=10206003 and (n5pozrealprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrealprod on collections.idobj=n5pozrealprod.idobj where idcollection=10206004 and (n5pozrealprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrealprod on collections.idobj=n5pozrealprod.idobj where idcollection=10206007 and (n5pozrealprod.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokmag_egz on collections.idobj=n5pozdokmag_egz.idobj where idcollection=10206022 and (n5pozdokmag_egz.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdokmag_egz on collections.idobj=n5pozdokmag_egz.idobj where idcollection=10206023 and (n5pozdokmag_egz.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10206025 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozrealprod_zasob on collections.idobj=n5pozrealprod_zasob.idobj where idcollection=10206026 and (n5pozrealprod_zasob.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklwyn on collections.idobj=n5plsklwyn.idobj where idcollection=10202008 and (n5plsklwyn.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklwyn on collections.idobj=n5plsklwyn.idobj where idcollection=10201008 and (n5plsklwyn.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklwyn on collections.idobj=n5plsklwyn.idobj where idcollection=10199008 and (n5plsklwyn.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklnal on collections.idobj=n5plsklnal.idobj where idcollection=10192015 and (n5plsklnal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pldekret on collections.idobj=n5pldekret.idobj where idcollection=10192016 and (n5pldekret.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plsklwyn on collections.idobj=n5plsklwyn.idobj where idcollection=10221008 and (n5plsklwyn.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5plpozkalcp on collections.idobj=n5plpozkalcp.idobj where idcollection=10218003 and (n5plpozkalcp.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5poznotaods on collections.idobj=n5poznotaods.idobj where idcollection=10215007 and (n5poznotaods.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_produkt on collections.idobj=n5bwinfo_produkt.idobj where idcollection=10211007 and (n5bwinfo_produkt.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211009 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211012 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5bwinfo_zal on collections.idobj=n5bwinfo_zal.idobj where idcollection=10211015 and (n5bwinfo_zal.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozistat on collections.idobj=n5pozistat.idobj where idcollection=10227055 and (n5pozistat.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozprojekt_abas on collections.idobj=n5pozprojekt_abas.idobj where idcollection=10244012 and (n5pozprojekt_abas.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozprojekt_abas on collections.idobj=n5pozprojekt_abas.idobj where idcollection=10242019 and (n5pozprojekt_abas.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozankieta_toral on collections.idobj=n5pozankieta_toral.idobj where idcollection=10286005 and (n5pozankieta_toral.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5poz_koszt_wyjazdu on collections.idobj=n5poz_koszt_wyjazdu.idobj where idcollection=10283016 and (n5poz_koszt_wyjazdu.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozdok_zalacznik on collections.idobj=n5pozdok_zalacznik.idobj where idcollection=10283026 and (n5pozdok_zalacznik.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002003 and (SearchTypeItem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002004 and (SearchTypeItem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join SearchTypeItem on collections.idobj=SearchTypeItem.idobj where idcollection=10002005 and (SearchTypeItem.idobj is null)

select collections.idcollection, collections.idobj,5 from collections left outer join n5pozinwark on collections.idobj=n5pozinwark.idobj where idcollection=10290006 and (n5pozinwark.idobj is null)

select 10282,n5poz_hist_stan.idobj,6 from n5poz_hist_stan where n5poz_hist_stan.idobj not in (select collections.idobj from collections where collections.idcollection=10109077)

select 10126,n5WizzardEmailDokumElem.idobj,6 from n5WizzardEmailDokumElem where n5WizzardEmailDokumElem.idobj not in (select collections.idobj from collections where collections.idcollection=10127002)

select 10123,choicelistitem.idobj,6 from choicelistitem where choicelistitem.idobj not in (select collections.idobj from collections where collections.idcollection=10124004)

select 10233,n5rolawyk.idobj,6 from n5rolawyk where n5rolawyk.idobj not in (select collections.idobj from collections where collections.idcollection=10122004)

select 10125,n5zadaniezal.idobj,6 from n5zadaniezal where n5zadaniezal.idobj not in (select collections.idobj from collections where collections.idcollection=10119035)

select 10232,n5zadanie_rola.idobj,6 from n5zadanie_rola where n5zadanie_rola.idobj not in (select collections.idobj from collections where collections.idcollection=10119050)

select 10133,n5dokumentlinks.idobj,6 from n5dokumentlinks where n5dokumentlinks.idobj not in (select collections.idobj from collections where collections.idcollection=10117023)

select 10238,n5pozdokprod.idobj,6 from n5pozdokprod where n5pozdokprod.idobj not in (select collections.idobj from collections where collections.idcollection=10117041)

select 10144,n5pozvatue.idobj,6 from n5pozvatue where n5pozvatue.idobj not in (select collections.idobj from collections where collections.idcollection=10143029)

select 10144,n5pozvatue.idobj,6 from n5pozvatue where n5pozvatue.idobj not in (select collections.idobj from collections where collections.idcollection=10143030)

select 10144,n5pozvatue.idobj,6 from n5pozvatue where n5pozvatue.idobj not in (select collections.idobj from collections where collections.idcollection=10143031)

select 10130,n5opakowanie_produktu.idobj,6 from n5opakowanie_produktu where n5opakowanie_produktu.idobj not in (select collections.idobj from collections where collections.idcollection=10131012)

select 10126,n5WizzardEmailDokumElem.idobj,6 from n5WizzardEmailDokumElem where n5WizzardEmailDokumElem.idobj not in (select collections.idobj from collections where collections.idcollection=10128002)

select 10132,n5pozsprzedaz.idobj,6 from n5pozsprzedaz where n5pozsprzedaz.idobj not in (select collections.idobj from collections where collections.idcollection=10129013)

select 10156,n5pozrata.idobj,6 from n5pozrata where n5pozrata.idobj not in (select collections.idobj from collections where collections.idcollection=10129069)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10129075)

select 10152,n5klient_opakowanie.idobj,6 from n5klient_opakowanie where n5klient_opakowanie.idobj not in (select collections.idobj from collections where collections.idcollection=10151005)

select 10121,n5pozplatnosc.idobj,6 from n5pozplatnosc where n5pozplatnosc.idobj not in (select collections.idobj from collections where collections.idcollection=10150010)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10150026)

select 10147,n5dekret.idobj,6 from n5dekret where n5dekret.idobj not in (select collections.idobj from collections where collections.idcollection=10148008)

select 10278,n5pozrejestrdok_mag.idobj,6 from n5pozrejestrdok_mag where n5pozrejestrdok_mag.idobj not in (select collections.idobj from collections where collections.idcollection=10145028)

select 10167,n5pozdoketyk.idobj,6 from n5pozdoketyk where n5pozdoketyk.idobj not in (select collections.idobj from collections where collections.idcollection=10166007)

select 10173,n5pozzamowienie.idobj,6 from n5pozzamowienie where n5pozzamowienie.idobj not in (select collections.idobj from collections where collections.idcollection=10172013)

select 10156,n5pozrata.idobj,6 from n5pozrata where n5pozrata.idobj not in (select collections.idobj from collections where collections.idcollection=10172037)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10172042)

select 10161,n5pozdokmag.idobj,6 from n5pozdokmag where n5pozdokmag.idobj not in (select collections.idobj from collections where collections.idcollection=10162011)

select 10168,n5pozdokmag_egz.idobj,6 from n5pozdokmag_egz where n5pozdokmag_egz.idobj not in (select collections.idobj from collections where collections.idcollection=10162030)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10162035)

select 10224,n5plpozschnal.idobj,6 from n5plpozschnal where n5plpozschnal.idobj not in (select collections.idobj from collections where collections.idcollection=10190016)

select 10186,n5pozzlecprod.idobj,6 from n5pozzlecprod where n5pozzlecprod.idobj not in (select collections.idobj from collections where collections.idcollection=10187012)

select 10184,n5pozrecepta.idobj,6 from n5pozrecepta where n5pozrecepta.idobj not in (select collections.idobj from collections where collections.idcollection=10185004)

select 10184,n5pozrecepta.idobj,6 from n5pozrecepta where n5pozrecepta.idobj not in (select collections.idobj from collections where collections.idcollection=10185005)

select 10184,n5pozrecepta.idobj,6 from n5pozrecepta where n5pozrecepta.idobj not in (select collections.idobj from collections where collections.idcollection=10185006)

select 10272,n5pozrecepta_zasob.idobj,6 from n5pozrecepta_zasob where n5pozrecepta_zasob.idobj not in (select collections.idobj from collections where collections.idcollection=10185008)

select 10273,n5pozrecepta_oper.idobj,6 from n5pozrecepta_oper where n5pozrecepta_oper.idobj not in (select collections.idobj from collections where collections.idcollection=10185009)

select 10175,n5pozzakup.idobj,6 from n5pozzakup where n5pozzakup.idobj not in (select collections.idobj from collections where collections.idcollection=10176012)

select 10156,n5pozrata.idobj,6 from n5pozrata where n5pozrata.idobj not in (select collections.idobj from collections where collections.idcollection=10176074)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10176079)

select 10205,n5pozrealprod.idobj,6 from n5pozrealprod where n5pozrealprod.idobj not in (select collections.idobj from collections where collections.idcollection=10206003)

select 10205,n5pozrealprod.idobj,6 from n5pozrealprod where n5pozrealprod.idobj not in (select collections.idobj from collections where collections.idcollection=10206004)

select 10205,n5pozrealprod.idobj,6 from n5pozrealprod where n5pozrealprod.idobj not in (select collections.idobj from collections where collections.idcollection=10206007)

select 10168,n5pozdokmag_egz.idobj,6 from n5pozdokmag_egz where n5pozdokmag_egz.idobj not in (select collections.idobj from collections where collections.idcollection=10206022)

select 10168,n5pozdokmag_egz.idobj,6 from n5pozdokmag_egz where n5pozdokmag_egz.idobj not in (select collections.idobj from collections where collections.idcollection=10206023)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10206025)

select 10275,n5pozrealprod_zasob.idobj,6 from n5pozrealprod_zasob where n5pozrealprod_zasob.idobj not in (select collections.idobj from collections where collections.idcollection=10206026)

select 10220,n5plsklwyn.idobj,6 from n5plsklwyn where n5plsklwyn.idobj not in (select collections.idobj from collections where collections.idcollection=10202008)

select 10220,n5plsklwyn.idobj,6 from n5plsklwyn where n5plsklwyn.idobj not in (select collections.idobj from collections where collections.idcollection=10201008)

select 10220,n5plsklwyn.idobj,6 from n5plsklwyn where n5plsklwyn.idobj not in (select collections.idobj from collections where collections.idcollection=10199008)

select 10193,n5plsklnal.idobj,6 from n5plsklnal where n5plsklnal.idobj not in (select collections.idobj from collections where collections.idcollection=10192015)

select 10198,n5pldekret.idobj,6 from n5pldekret where n5pldekret.idobj not in (select collections.idobj from collections where collections.idcollection=10192016)

select 10220,n5plsklwyn.idobj,6 from n5plsklwyn where n5plsklwyn.idobj not in (select collections.idobj from collections where collections.idcollection=10221008)

select 10219,n5plpozkalcp.idobj,6 from n5plpozkalcp where n5plpozkalcp.idobj not in (select collections.idobj from collections where collections.idcollection=10218003)

select 10214,n5poznotaods.idobj,6 from n5poznotaods where n5poznotaods.idobj not in (select collections.idobj from collections where collections.idcollection=10215007)

select 10212,n5bwinfo_produkt.idobj,6 from n5bwinfo_produkt where n5bwinfo_produkt.idobj not in (select collections.idobj from collections where collections.idcollection=10211007)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211009)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211012)

select 10213,n5bwinfo_zal.idobj,6 from n5bwinfo_zal where n5bwinfo_zal.idobj not in (select collections.idobj from collections where collections.idcollection=10211015)

select 10228,n5pozistat.idobj,6 from n5pozistat where n5pozistat.idobj not in (select collections.idobj from collections where collections.idcollection=10227055)

select 10243,n5pozprojekt_abas.idobj,6 from n5pozprojekt_abas where n5pozprojekt_abas.idobj not in (select collections.idobj from collections where collections.idcollection=10244012)

select 10243,n5pozprojekt_abas.idobj,6 from n5pozprojekt_abas where n5pozprojekt_abas.idobj not in (select collections.idobj from collections where collections.idcollection=10242019)

select 10287,n5pozankieta_toral.idobj,6 from n5pozankieta_toral where n5pozankieta_toral.idobj not in (select collections.idobj from collections where collections.idcollection=10286005)

select 10284,n5poz_koszt_wyjazdu.idobj,6 from n5poz_koszt_wyjazdu where n5poz_koszt_wyjazdu.idobj not in (select collections.idobj from collections where collections.idcollection=10283016)

select 10276,n5pozdok_zalacznik.idobj,6 from n5pozdok_zalacznik where n5pozdok_zalacznik.idobj not in (select collections.idobj from collections where collections.idcollection=10283026)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002003)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002004)

select 10003,SearchTypeItem.idobj,6 from SearchTypeItem where SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002005)

select 10291,n5pozinwark.idobj,6 from n5pozinwark where n5pozinwark.idobj not in (select collections.idobj from collections where collections.idcollection=10290006)


go

create index WFKI_n5straznik_cen_scs_wpProdGrupa on n5straznik_cen (scs_wpProdGrupa,scs_wpProdGrupa_wrt )
go

create index WFKI_n5straznik_cen_scs_wpKlientGrupa on n5straznik_cen (scs_wpKlientGrupa,scs_wpKlientGrupa_wrt )
go

create index FKI_n5straznik_cen_scs_pKwalifikatorEx on n5straznik_cen (scs_pKwalifikatorEx)
go

if exists (select * from sysobjects where name = 'n2001_setprofile_value')
	drop procedure n2001_setprofile_value
go

create procedure n2001_setprofile_value(@Indeks_par integer, @Wartosc_par varchar(255))
as
declare @P1 int
select @P1 = 0
select @P1 = IdObj from n5globprof where Indeks = @Indeks_par
if @P1 = 0
	begin
		exec n5globprof_maxid @P1 output
		set @P1 = isNull(@P1,0) + 1
		execute n5globprof_insert @P1, 1, @Indeks_par, @Wartosc_par
	end
else
	begin
		update n5globprof set Wartosc=@Wartosc_par where idobj= @P1
	end
return 0
go
-- end of script ----

--================================================================================================

-- nak³adki

-- uprawnienia do obiektu n5straznik_cen -----------------------------------------
-- max idSodGroup
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Stra¿nik cen sprzeda¿y')
begin
	-- dodanie grupy dla obiektu n5straznik_cen
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Stra¿nik cen sprzeda¿y',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Stra¿nik cen sprzeda¿y')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102921,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102922,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102923,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102924,0,'EB')
end
go

-- uprawnienia dla Menu Stra¿nik cen sprzeda¿y
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Kartoteka - Handel')
declare @maxSecId int
set @maxSecId = (select max(nSecId)+1 from n5sod where pSODGroup = @idSodGroup)
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'Stra¿nik cen sprzeda¿y',@idSodGroup,13901,0,'EB')
go

n2001_makegrants 'navo2002user'
go
