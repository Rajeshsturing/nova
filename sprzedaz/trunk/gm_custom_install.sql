--============================================================
-- GM Archive support
--============================================================

-- create copy table (gmop below border)

if exists (select * from sysobjects where name='n5gmop_arch')
	drop table n5gmop_arch
go

create table n5gmop_arch
(
	IdObj integer not null,
	VersionId integer not null,
	gmo_eTypOp integer not null,
	gmo_nNumOp integer not null,
	gmo_nLP integer not null,
	gmo_curIlosc decimal(14,4) not null,
	gmo_curCena decimal(14,4) not null,
	gmo_curWartosc decimal(12,2) not null,
	gmo_pProd integer not null,
	gmo_pOpak integer not null,
	gmo_pMag integer not null,
	gmo_idDost integer not null,
	gmo_idDostLP integer not null,
	gmo_dDataWazn datetime not null,
	gmo_nNumOpRel integer not null,
	gmo_nLPRel integer not null,
	gmo_curPrzel decimal(12,2) not null
)
go

alter table n5gmop_arch add constraint PK_n5gmop_arch_IdObj primary key nonclustered (IdObj) 
go
if exists (select * from sysindexes where name='CUST20_arch')
	drop index n5gmop_arch.CUST20_arch
go
create clustered index CUST20_arch on n5gmop_arch(gmo_nNumOp, gmo_nLP, gmo_eTypOp,IdObj)
go
--============================================================

--============================================================
-- move gmop to archive
--============================================================

if exists (select * from sysobjects where name='n5gmop_move_to_archive')
	drop procedure n5gmop_move_to_archive
go

create procedure n5gmop_move_to_archive(@gmo_nNumOpBorder_par integer) with encryption 
as
-- wstawienie kopii
insert into n5gmop_arch select * from n5gmop where gmo_nNumOp <= @gmo_nNumOpBorder_par and gmo_eTypOp <> 9

-- usuniecie oryginalu
delete from n5gmop where gmo_nNumOp <= @gmo_nNumOpBorder_par

-- wymus przeliczenie
update n5globprof set wartosc = 0 where indeks=1063
update n5globprof set wartosc = @gmo_nNumOpBorder_par where indeks=1086
go

--============================================================
-- perform mapping relop
--============================================================

if exists (select * from sysobjects where name='n5gmop_map_archive')
	drop procedure n5gmop_map_archive
go

create procedure n5gmop_map_archive with encryption 
as
declare @GM_ARCHIVE_BORDER integer
go

--============================================================
-- move from archive to gmop (undoes move to archive)
--============================================================
if exists (select * from sysobjects where name='n5gmop_move_from_archive')
	drop procedure n5gmop_move_from_archive
go

create procedure n5gmop_move_from_archive with encryption 
as
declare @GM_ARCHIVE_BORDER integer
select @GM_ARCHIVE_BORDER = isnull((select Wartosc from n5globprof where indeks=1086),0)

delete from n5gmop where gmo_nNumOp <= @GM_ARCHIVE_BORDER
insert into n5gmop select * from n5gmop_arch
delete from n5gmop_arch

-- wymus przeliczenie
update n5globprof set wartosc = 0 where indeks=1063
update n5globprof set wartosc = 0 where indeks=1086
go


--============================================================
-- change constraint (for DB9 and less)
--============================================================
if exists (select * from sysobjects where name='ENUM_n5gmop_gmo_eTypOp_2')
	alter table n5gmop drop constraint ENUM_n5gmop_gmo_eTypOp_2
go

alter table n5gmop add constraint ENUM_n5gmop_gmo_eTypOp_2 check (
gmo_eTypOp between 0 and 10
)
go

--============================================================
-- create new globprofile
--============================================================
if not exists(select * from n5globprof where indeks=1086)
	insert into n5globprof select 1+(select max(idobj) from n5globprof),1,1086,0
go

--============================================================
--
--============================================================


if exists (select * from sysobjects where name='view_operacje_magazynowe')
	drop view view_operacje_magazynowe
go

create view view_operacje_magazynowe as 
select 
'nTypDok'=dm.ntypdok,
'typeid'=10162,
'idobjdok'=dm.idobj,
'strNrDok'=dm.strnrdok,
'dDataOp'=dm.dDataWyst,
om.* from n5gmop om inner join n5dokmag as dm on om.gmo_nNumOp = dm.nnumoper
where gmo_nnumop > (select isnull(Wartosc,0) from n5globprof where indeks=1086)
union all
select 
'nTypDok'=33,
'typeid'=10206,
'idobjdok'=rps.idobj,
'strNrDok'=rps.strnrdok,
'dDataOp'=rps.dDataWyst,
om.* from n5gmop om 
inner join n5realprod rps on om.gmo_nNumOp = rps.nnumoper
where gmo_nnumop > (select isnull(Wartosc,0) from n5globprof where indeks=1086)
union all
select 
'nTypDok'=0,
'typeid'=0,
'idobjdok'=0,
'strNrDok'='ARCHIWUM',
'dDataOp'=0,
om.* from n5gmop om where gmo_etypop=9

go
