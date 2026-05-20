--------------------------------------------------------------------
-- Manual upgrade from DB11 (ENABLE_DB11) to DB11B (ENABLE_DB11_B)
-- created: 2010-12-27
--
-- Notes:
-- 1) first select manually database (i.e. NAVO2002)
-- 2) run once only
--------------------------------------------------------------------

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
--------------------------------------------------------------------
alter table n5grupaproduktow
add grp_iDataWaznosci integer not null default 0
go
--------------------------------------------------------------------

-- table: n5grupaproduktow
create procedure n5grupaproduktow_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@pGrupaNadrzedna_par integer output,
	@grp_strRZC_par varchar(255) output,
	@grp_strRZSM_par varchar(255) output,
	@grp_pJednostkaEwid_par integer output,
	@grp_pDostawca_par integer output,
	@grp_iDataWaznosci_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@pGrupaNadrzedna_par=pGrupaNadrzedna,
	@grp_strRZC_par=grp_strRZC,
	@grp_strRZSM_par=grp_strRZSM,
	@grp_pJednostkaEwid_par=grp_pJednostkaEwid,
	@grp_pDostawca_par=grp_pDostawca,
	@grp_iDataWaznosci_par=grp_iDataWaznosci from n5grupaproduktow where IdObj=@idobj_par
return @@rowcount
go

create procedure n5grupaproduktow_insert(@idobj_par integer,@versionid_par integer,
	@strNazwa_par varchar(128),
	@pGrupaNadrzedna_par integer,
	@grp_strRZC_par varchar(255),
	@grp_strRZSM_par varchar(255),
	@grp_pJednostkaEwid_par integer,
	@grp_pDostawca_par integer,
	@grp_iDataWaznosci_par integer) with encryption as 
	insert into n5grupaproduktow values(@idobj_par,@versionid_par,
	@strNazwa_par,
	@pGrupaNadrzedna_par,
	@grp_strRZC_par,
	@grp_strRZSM_par,
	@grp_pJednostkaEwid_par,
	@grp_pDostawca_par,
	@grp_iDataWaznosci_par)
return @@rowcount
go

create procedure n5grupaproduktow_update(@idobj_par integer,@versionid_par integer,
	@strNazwa_par varchar(128),
	@pGrupaNadrzedna_par integer,
	@grp_strRZC_par varchar(255),
	@grp_strRZSM_par varchar(255),
	@grp_pJednostkaEwid_par integer,
	@grp_pDostawca_par integer,
	@grp_iDataWaznosci_par integer) with encryption as 
	update n5grupaproduktow set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	pGrupaNadrzedna=@pGrupaNadrzedna_par,
	grp_strRZC=@grp_strRZC_par,
	grp_strRZSM=@grp_strRZSM_par,
	grp_pJednostkaEwid=@grp_pJednostkaEwid_par,
	grp_pDostawca=@grp_pDostawca_par,
	grp_iDataWaznosci=@grp_iDataWaznosci_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5grupaproduktow_delete(@idobj_par integer) with encryption as 
	delete from n5grupaproduktow where idobj=@idobj_par
return @@rowcount
go

create procedure n5grupaproduktow_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5grupaproduktow
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

n2001_makegrants 'navo2002user'
go
--------------------------------------------------------------------
-- end of script
--------------------------------------------------------------------
