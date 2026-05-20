-- NAVO Enterprise SQL script--
-- custom drop script ---

use %DBNAME%
go

if exists (select * from sysindexes where name='CUST1')
	drop index n5klient.CUST1
go

if exists (select * from sysindexes where name='CUST2')
	drop index n5produkt.CUST2
go

if exists (select * from sysindexes where name='CUST3')
	drop index n5miejscowosc.CUST3
go

if exists (select * from sysindexes where name='CUST4')
	drop index n5klient.CUST4
go

if exists (select * from sysindexes where name='CUST5')
	drop index n5klient.CUST5
go

if exists (select * from sysindexes where name='CUST6')
	drop index n5klient_pracownik.CUST6
go

if exists (select * from sysindexes where name='CUST7')
	drop index n5klient_pracownik.CUST7
go

if exists (select * from sysindexes where name='CUST8')
	drop index n5klient.CUST8
go

if exists (select * from sysindexes where name='CUST9')
	drop index n5sprzedaz.CUST9
go

if exists (select * from sysindexes where name='CUST10')
	drop index n5platnosc.CUST10
go

if exists (select * from sysobjects where name='CUST_PK_n5dekret_sums')
	alter table n5dekret_sums drop constraint CUST_PK_n5dekret_sums
go

if exists (select * from sysobjects where name='CUST_FK_n5dekret_n5konto_1')
	alter table n5dekret_sums drop constraint CUST_FK_n5dekret_n5konto_1
go

if exists (select * from sysindexes where name='CUST11')
	drop index n5dekret_sums.CUST11
go

if exists (select * from sysobjects where name='n5dekret_change_tr')
	drop trigger n5dekret_change_tr
go

if exists (select * from sysobjects where name='n5dekret_sums_repair')
	drop procedure n5dekret_sums_repair
go

if exists (select * from sysobjects where name='vw_n5dekret_sums_check')
	drop view vw_n5dekret_sums_check
go

if exists (select * from sysobjects where name='n5dekret_sums_check')
	drop procedure n5dekret_sums_check
go



-- p³ace (place) -----------------------------
if exists (select * from sysobjects where name='view_pl_dok_zrod')
	drop view view_pl_dok_zrod
go

-- operacje magazynowe + dokumenty które je tworz¹ (dokmag,realprod)
if exists (select * from sysobjects where name='view_operacje_magazynowe')
	drop view view_operacje_magazynowe
go

if exists (select * from sysobjects where name='n5stanmag_fill_timerange')
	drop procedure n5stanmag_fill_timerange
go
-----------------------------------------------

if exists (select name from sysobjects where name = 'n5klient_insert_tr' and type = 'tr')
   drop trigger n5klient_insert_tr
go


if exists (select * from sysobjects where name='n5check_custom')
	drop procedure n5check_custom
go


-------------------------------------------------------------------------
-- patch na bug w navogm (brak incrementacji wersji VersionId)
-------------------------------------------------------------------------


if exists (select * from sysindexes where name='CUST16')
	drop index n5klient.CUST16
go

if exists (select * from sysindexes where name='CUST17')
	drop index n5userprof.CUST17
go

if exists (select * from sysindexes where name='CUST18')
	drop index n5plstawka.CUST18
go

if exists (select * from sysindexes where name='CUST19')
	drop index n5pldekret.CUST19
go

if exists (select * from sysindexes where name='CUST20')
	drop index n5gmop.CUST20
go

if exists (select * from sysindexes where name='CUST21')
	drop index n5gmop.CUST21
go

if exists (select * from sysobjects where name='vw_gm_check_ilosc')
	drop view vw_gm_check_ilosc
go

if exists (select * from sysobjects where name='gm_check_ilosc')
	drop procedure gm_check_ilosc
go

if exists (select * from sysindexes where name='CUST22')
	drop index n5gmstan.CUST22
go

if exists (select * from sysindexes where name='CUST23')
	drop index n5transakcja.CUST23
go

------------------------------------------------
-- DB5
-------------------------------------------------
if exists (select * from sysobjects where name='ks_lex_order')
	drop function ks_lex_order
go

if exists (select * from sysobjects where name='view_doksp_sum_by_prod')
	drop view  view_doksp_sum_by_prod
go

if exists (select * from sysobjects where name='view_doksp_sum_magic')
	drop view  view_doksp_sum_magic
go

if exists (select * from sysobjects where name='view_dokmag_sum_by_prod_sp')
	drop view  view_dokmag_sum_by_prod_sp
go

if exists (select * from sysobjects where name='view_dokmag_sum_magic')
	drop view  view_dokmag_sum_magic
go

if exists (select * from sysobjects where name='view_dokzak_sum_by_prod')
	drop view  view_dokzak_sum_by_prod
go

if exists (select * from sysobjects where name='view_dokzak_sum_magic')
	drop view  view_dokzak_sum_magic
go

if exists (select * from sysobjects where name='view_dokmag_sum_by_prod_zak')
	drop view  view_dokmag_sum_by_prod_zak
go

if exists (select * from sysobjects where name='view_dokmag_sum_magic2')
	drop view  view_dokmag_sum_magic2
go

----------- DB 9 ---------------------
if exists (select * from sysobjects where name='nx_date2str')
	drop function nx_date2str
go

if exists (select * from sysobjects where name='nx_dec2str')
	drop function nx_dec2str
go

if exists (select * from sysindexes where name='CUST24')
	drop index n5pozrecepta.CUST24
go

------------------------------------------------------------------------
------------------------------------------------------------------------
if exists (select * from sysindexes where name='CUST20_arch')
	drop index n5gmop_arch.CUST20_arch
go

if exists (select * from sysobjects where name='n5gmop_move_to_archive')
	drop procedure n5gmop_move_to_archive
go

if exists (select * from sysobjects where name='n5gmop_map_archive')
	drop procedure n5gmop_map_archive
go

if exists (select * from sysobjects where name='n5gmop_move_from_archive')
	drop procedure n5gmop_move_from_archive
go


if exists (select * from sysobjects where name='view_operacje_magazynowe')
	drop view view_operacje_magazynowe
go

--------------------------------------------------------------
-- DB13
--------------------------------------------------------------
if exists (select * from sysobjects where name='nx_lex_order')
	drop function nx_lex_order
go
--============================================================
