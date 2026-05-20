---------------------------------------------------------------------------------
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
if exists (select * from sysindexes where name='FKI_n5straznik_cen_scs_pKwalifikatorEx')
	drop index n5straznik_cen.FKI_n5straznik_cen_scs_pKwalifikatorEx
go

if exists (select * from sysindexes where name='WFKI_n5straznik_cen_scs_wpProdGrupa')
	drop index n5straznik_cen.WFKI_n5straznik_cen_scs_wpProdGrupa
go

if exists (select * from sysindexes where name='WFKI_n5straznik_cen_scs_wpKlientGrupa')
	drop index n5straznik_cen.WFKI_n5straznik_cen_scs_wpKlientGrupa
go
if exists (select * from sysobjects where name='PK_n5straznik_cen_IdObj')
	alter table n5straznik_cen drop constraint PK_n5straznik_cen_IdObj
go
---------------------------------------------------------------------------------

update n5zakup 
set 
zak_pRozlVat_SP = pRozlVat,
zak_iJPKVAT = 1,
zak_iJPKVAT_oo = 1,
zak_cBezTransakcji = '0'
go

update n5sprzedaz
set
sprzed_iJPKVAT = 1,
sprzed_iJPKVAT_0 = 1,
sprzed_iJPKVAT_np = 1,
sprzed_cBezTransakcji = '0'
go

update n5opakowanie_produktu 
set 
opak_pWaluta7 = pWaluta,
opak_pWaluta8 = pWaluta,
opak_pWaluta9 = pWaluta
go

update n5produkt
set
prod_eRodzaj_VATUE = eRodzaj,
prod_cPublic = '1',
prod_strPublicName = strNazwa
go

update n5grupaproduktow
set
grp_cPublic = '1',
grp_strPublicName = strNazwa
go

--- mark current version full
exec n2001_setprofile_value 1097, 'DB13'
go
--- mark current version
exec n2001_setprofile_value 1000, '13'
go
---------------------------------------------------------------------------------
