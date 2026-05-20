
-- custom create object script ---

use %DBNAME%
go

create index CUST1 on n5klient(strNazwa,strSkrot)	--wyszukiwanie wg nazwy

create index CUST2 on n5produkt(strNazwa,eAktywny)	--wyszukiwanie wg nazwy

create index CUST3 on n5miejscowosc(strNazwa) --wyszukiwanie wg nazwy

create index CUST4 on n5klient(strEmail)

create index CUST5 on n5klient(strTel1)

create index CUST6 on n5klient_pracownik(strNazwisko)

create index CUST7 on n5klient_pracownik(strEmail)

create index CUST8 on n5klient(strRegon,IdObj)

create index CUST9 on n5sprzedaz(strNrDok)

create index CUST10 on n5platnosc(pRejestrDok, curKwotaEwid, dDataOper, wrefPodmiot, wrefPodmiot_wrt )
go

--=========================================================================-----
-- dekret fasteners
--------------------------------------------------------------------------------
if exists (select * from sysobjects where name='CUST_PK_n5dekret_sums')
	alter table n5dekret_sums drop constraint CUST_PK_n5dekret_sums
go

alter table n5dekret_sums add constraint CUST_PK_n5dekret_sums
	primary key clustered (pKonto,dDataKsieg,eTyp,eStatus,pKwalifikator)
go

if exists (select * from sysobjects where name='CUST_FK_n5dekret_n5konto_1')
	alter table n5dekret_sums drop constraint CUST_FK_n5dekret_n5konto_1
go
alter table n5dekret_sums add constraint CUST_FK_n5dekret_n5konto_1 
	foreign key (pKonto ) references n5konto ( IdObj ) on delete cascade
go

if exists (select * from sysindexes where name='CUST11')
	drop index n5dekret_sums.CUST11
go

create index CUST11 on n5dekret_sums(pKonto, dDataKsieg, eTyp, curWn, curMa)
go

-----------------------------------------------------------------------------
if exists (select * from sysobjects where name='n5dekret_sums_smart_update')
	drop procedure n5dekret_sums_smart_update
go

create procedure n5dekret_sums_smart_update(
	@pKonto_par integer,
	@curWn_par decimal(12,2),
	@curMa_par decimal(12,2),
	@dDataKsieg_par datetime,
	@eTyp_par integer,
	@eStatus_par integer,
	@pKwalifikator_par integer) with encryption 
as

	update n5dekret_sums set 
		n5dekret_sums.curWn = n5dekret_sums.curWn + @curWn_par,
		n5dekret_sums.curMa = n5dekret_sums.curMa + @curMa_par
	where 
		@pKonto_par = n5dekret_sums.pkonto 
	and 
		@dDataKsieg_par = n5dekret_sums.ddataksieg 
	and 
		@eTyp_par = n5dekret_sums.etyp
	and 
		@eStatus_par = n5dekret_sums.eStatus
	and 
		@pKwalifikator_par = n5dekret_sums.pKwalifikator

	if @@rowcount < 1 
		insert into n5dekret_sums 
	values(
		@pKonto_par,
		@curWn_par,
		@curMa_par,
		@dDataKsieg_par,
		@eTyp_par,
		@eStatus_par,
		@pKwalifikator_par)
go

------------------------------------------------------------------------------------

if exists (select * from sysobjects where name='n5dekret_change_tr')
	drop trigger n5dekret_change_tr
go

create trigger n5dekret_change_tr on n5dekret
with encryption
for insert,update,delete
as

declare 
	@pKonto_par integer,
	@curWn_par decimal(12,2),
	@curMa_par decimal(12,2),
	@dDataKsieg_par datetime,
	@eTyp_par integer,
	@eStatus_par integer,
	@pKwalifikator_par integer

declare del_cur cursor for 
	select pKonto,-curWn,-curMa,dDataKsieg,eTyp,eStatus,pKwalifikator from deleted

open del_cur

fetch next from del_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
while @@fetch_status = 0
begin
	while @pKonto_par <> 0
	begin
		exec n5dekret_sums_smart_update @pKonto_par, @curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
		select @pKonto_par = pKontoNadrz from n5konto where idobj = @pKonto_par
	end
	fetch next from del_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
end

close del_cur
deallocate del_cur


declare ins_cur cursor for select 
	pKonto,curWn,curMa,dDataKsieg,eTyp,eStatus,pKwalifikator from inserted

open ins_cur 

fetch next from ins_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
while @@fetch_status = 0
begin
	while @pKonto_par <> 0
	begin
		exec n5dekret_sums_smart_update @pKonto_par, @curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
		select @pKonto_par = pKontoNadrz from n5konto where idobj = @pKonto_par
	end
	fetch next from ins_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
end

close ins_cur
deallocate ins_cur

go

if exists (select * from sysobjects where name='n5konto_change_pKontoNadrz_tr')
	drop trigger n5konto_change_pKontoNadrz_tr
go

create trigger n5konto_change_pKontoNadrz_tr on n5konto
with encryption
for update
-- insert: nie ma jeszcze dekretów
-- delete: juz miec nie moze dekretów
as
declare 
	@pKonto_par integer,
	@curWn_par decimal(12,2),
	@curMa_par decimal(12,2),
	@dDataKsieg_par datetime,
	@eTyp_par integer,
	@eStatus_par integer,
	@pKwalifikator_par integer

--todo: warunek na rzeczywista zmiane pKontoNadrz. 
--funkcja update(kolumna) zwraca true nawet jesli wartosc sie nie zmienila
begin
	declare del_cur cursor for 
	select 
		deleted.pKontoNadrz,
		-n5dekret_sums.curWn,
		-n5dekret_sums.curMa,
		n5dekret_sums.dDataKsieg,
		n5dekret_sums.eTyp,
		n5dekret_sums.eStatus,
		n5dekret_sums.pKwalifikator 
	from deleted 
	join n5dekret_sums on deleted.idobj = n5dekret_sums.pKonto

	open del_cur

	fetch next from del_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
	while @@fetch_status = 0
	begin
		while @pKonto_par <> 0
		begin
			exec n5dekret_sums_smart_update @pKonto_par, @curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
			select @pKonto_par = pKontoNadrz from n5konto where idobj = @pKonto_par
		end
		fetch next from del_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
	end

	close del_cur
	deallocate del_cur

	declare ins_cur cursor for 
	select 
		inserted.pKontoNadrz,
		n5dekret_sums.curWn,
		n5dekret_sums.curMa,
		n5dekret_sums.dDataKsieg,
		n5dekret_sums.eTyp,
		n5dekret_sums.eStatus,
		n5dekret_sums.pKwalifikator 
	from inserted 
	join n5dekret_sums on inserted.idobj = n5dekret_sums.pKonto

	open ins_cur 

	fetch next from ins_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
	while @@fetch_status = 0
	begin
		while @pKonto_par <> 0
		begin
			exec n5dekret_sums_smart_update @pKonto_par, @curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
			select @pKonto_par = pKontoNadrz from n5konto where idobj = @pKonto_par
		end
		fetch next from ins_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
	end

	close ins_cur
	deallocate ins_cur
end
go

------------------------------------------------------------------------------

if exists (select * from sysobjects where name='n5dekret_sums_repair')
	drop procedure n5dekret_sums_repair
go

create procedure n5dekret_sums_repair with encryption
as

delete from n5dekret_sums

declare 
	@pKonto_par integer,
	@curWn_par decimal(12,2),
	@curMa_par decimal(12,2),
	@dDataKsieg_par datetime,
	@eTyp_par integer,
	@eStatus_par integer,
	@pKwalifikator_par integer

declare rep_cur cursor for 
	select pkonto,sum(curWn),sum(curMa),dDataKsieg,eTyp,eStatus,pKwalifikator from
	n5dekret group by pkonto,dDataKsieg,eTyp,eStatus,pKwalifikator
open rep_cur 

fetch next from rep_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
while @@fetch_status = 0
begin
	while @pKonto_par <> 0
	begin
		exec n5dekret_sums_smart_update @pKonto_par, @curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
		select @pKonto_par = pKontoNadrz from n5konto where idobj = @pKonto_par
	end
	fetch next from rep_cur into @pKonto_par,@curWn_par,@curMa_par,@dDataKsieg_par,@eTyp_par,@eStatus_par,@pKwalifikator_par
end
close rep_cur
deallocate rep_cur

go

if exists (select * from sysobjects where name='vw_n5dekret_sums_check')
	drop view vw_n5dekret_sums_check
go

create view vw_n5dekret_sums_check as
select pkonto,
	'deltawn' =sum(curWn) - (select sum(curwn) from n5dekret_sums ds where ds.pkonto = d.pkonto and 
	ds.ddataksieg = d.ddataksieg and ds.etyp = d.etyp and ds.estatus = d.estatus and 
	d.pKwalifikator = ds.pKwalifikator),
	'deltama' = sum(curMa) - (select sum(curMa) from n5dekret_sums ds where ds.pkonto = d.pkonto and 
	ds.ddataksieg = d.ddataksieg and ds.etyp = d.etyp and ds.estatus = d.estatus  and 
	d.pKwalifikator = ds.pKwalifikator),
	dDataKsieg,eTyp,eStatus,pKwalifikator from
	n5dekret d
group by
	pkonto,dDataKsieg,eTyp,eStatus,pKwalifikator
go

if exists (select * from sysobjects where name='n5dekret_sums_check')
	drop procedure n5dekret_sums_check
go

create procedure n5dekret_sums_check as
select * from vw_n5dekret_sums_check where deltawn <> 0.0 or deltama <> 0.0 or deltawn is null or deltama is null
go


--------------------------------------------------------------------------------


-- p³ace (place) -----------------------------
if exists (select * from sysobjects where name='view_pl_dok_zrod')
	drop view view_pl_dok_zrod
go

create view view_pl_dok_zrod as 
select 'ordr'=1,'typeid'=10199, idobj, 'pUmowa'=idobj,dDataRej,dDataOd,dDataDo from n5plumowa
union all
select 'ordr'=2, 'typeid'=10201, idobj, pUmowa,dDataRej,dDataOd,dDataDo from n5plchoroba
union all
select 'ordr'=3, 'typeid'=10202, idobj, pUmowa,dDataRej,dDataOd,dDataDo from n5plnieob
union all
select 'ordr'=4, 'typeid'=10221, idobj, pUmowa,dDataRej,dDataOd,dDataDo from n5plpozostale

go

-- operacje magazynowe + dokumenty które je tworz¹ (dokmag,realprod)
-- DB8: begin: zmiana view
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
union all
select 
'nTypDok'=33,
'typeid'=10206,
'idobjdok'=rps.idobj,
'strNrDok'=rps.strnrdok,
'dDataOp'=rps.dDataWyst,
om.* from n5gmop om 
inner join n5realprod rps on om.gmo_nNumOp = rps.nnumoper
go
-- DB8: end: zmiana view

if exists (select * from sysobjects where name='n5stanmag_fill_timerange')
	drop procedure n5stanmag_fill_timerange
go

-- procedura przygotowuj¹ca stany magazynowe ---
-- na dowolny moment -------
create procedure n5stanmag_fill_timerange(@nNumOpStart integer,@nNumOpEnd integer) with encryption as

-- prefill with all existing trios (pmag,pprod,popak)
insert into #tmp_stanmag_moment
select distinct gmo_pMag, gmo_pProd, gmo_pOpak, 0,0,0,0,0,0 from n5gmop

--update
update #tmp_stanmag_moment
set 
curIloscOpakB = (select isnull(sum(n5gmop.gmo_curIlosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_nNumOp < @nNumOpStart)
,
curWartoscB = (select isnull(sum(n5gmop.gmo_curWartosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_nNumOp < @nNumOpStart)
,
curIloscOpakRI = (select isnull(sum(-n5gmop.gmo_curIlosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_curIlosc < 0 and
n5gmop.gmo_nNumOp between @nNumOpStart and @nNumOpEnd)
,
curWartoscRI = (select isnull(sum(-n5gmop.gmo_curWartosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_curIlosc < 0 and
n5gmop.gmo_nNumOp between @nNumOpStart and @nNumOpEnd)
,
curIloscOpakPI = (select isnull(sum(n5gmop.gmo_curIlosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_curIlosc > 0 and
n5gmop.gmo_nNumOp between @nNumOpStart and @nNumOpEnd)
,
curWartoscPI = (select isnull(sum(n5gmop.gmo_curWartosc),0) from n5gmop where 
#tmp_stanmag_moment.pMagazyn = n5gmop.gmo_pMag and
#tmp_stanmag_moment.pProdukt = n5gmop.gmo_pProd and
#tmp_stanmag_moment.pOpak = n5gmop.gmo_pOpak and
n5gmop.gmo_curIlosc > 0 and
n5gmop.gmo_nNumOp between @nNumOpStart and @nNumOpEnd)

go

-----------------------------------------------

if exists (select name from sysobjects
      where name = 'n5klient_insert_tr' and type = 'tr')
   drop trigger n5klient_insert_tr
go

create trigger n5klient_insert_tr
on n5klient
with encryption
for insert,update,delete
as
	exec navo2001_updatekey 'EB1'
	exec navo2001_updatekey 'EB4'
go


if exists (select * from sysobjects where name='n5check_custom')
	drop procedure n5check_custom
go

create procedure n5check_custom with encryption as 

	select 10003,SearchTypeItem.idobj,101 from SearchTypeItem where SearchTypeItem.idobj 
    not in (select collections.idobj from collections where collections.idcollection=10002003)
	and SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002004)
	and SearchTypeItem.idobj not in (select collections.idobj from collections where collections.idcollection=10002005)

go



create index CUST16 on n5klient(strNIP)	--wyszukiwanie wg NIP
go

create index CUST17 on n5userprof(pn5user,Indeks)
go

create index CUST18 on n5plstawka(strKod,dDataOd,dDataDo)
go

create index CUST19 on n5pldekret(pPracownik, pSubKonto, nNumNal,curKwota)
go

-------------------------------------------------------------------------

if exists (select * from sysobjects where name='PK_n5gmop_IdObj')
	alter table n5gmop drop constraint PK_n5gmop_IdObj
go

if exists (select * from sysindexes where name='PK_n5gmop_IdObj')
	drop index n5gmop.PK_n5gmop_IdObj
go

alter table n5gmop add constraint PK_n5gmop_IdObj primary key nonclustered (IdObj)
go

--pre DB8: 
create clustered index CUST20 on n5gmop(gmo_nNumOp, gmo_nLP, gmo_eTypOp,IdObj)
--
go

create index CUST21 on n5gmop(gmo_pProd, gmo_pOpak, gmo_pMag, gmo_eTypOp, gmo_nNumOp, gmo_nLP, IdObj, gmo_idDost)
go

create view vw_gm_check_ilosc as
		select 'curIlosc' = sum(gmo_curIlosc),'pProd'=gmo_pProd,'pOpak'=gmo_pOpak,'pMag'=gmo_pMag 
		from n5gmop 
		group by gmo_pProd,gmo_pOpak,gmo_pMag
	union all
		select 'curIlosc' = -sum(gms_curIlosc), 'pProd'=gms_pPRod,'pOpak'=gms_pOpak,'pMag'=gms_pMag 
		from n5gmstan 
		group by gms_pPRod,gms_pOpak,gms_pMag
go

--------------------------------------------------------
-- wypisuje niezgodnoœci iloœciowe pomiêdzy n5gmstan a n5gmop
--------------------------------------------------------

if exists (select * from sysobjects where name='gm_check_ilosc')
	drop procedure gm_check_ilosc
go

create procedure gm_check_ilosc as
	select 'roznica'=sum(curIlosc),pProd,pOpak,pMag from vw_gm_check_ilosc
	group by pProd,pOpak,pMag
	having sum(curIlosc) <> 0
go

create index CUST22 on n5gmstan(gms_pProd,gms_pOpak,gms_pMag,gms_nNumOp,gms_nLP,gms_curIlosc)
go

create unique index CUST23 on n5transakcja(strSymTrans,wrefPodmiot,wrefPodmiot_wrt)
go

--------------------------------------------------------
-- DB5
--------------------------------------------------------
if exists (select * from sysobjects where name='ks_lex_order')
	drop function ks_lex_order
go

create function dbo.ks_lex_order(@symbol varchar(32))
returns varchar(96)
with encryption
as
begin
    declare @iter int
    declare @start int
    declare @strresult varchar(96)

    set @iter = 1
    set @start = 1
    set @strresult = ''
	
    while @iter <= datalength(@symbol)
        begin
            if substring(@symbol,@iter,1) = '-'
                begin
                    if @start = 1
                        set @strresult = @strresult + substring(@symbol,1,@iter)
					else
                        set @strresult = @strresult + isnull(replicate('0',6-(@iter-@start)),'') + substring(@symbol,@start,@iter-@start+1)

                    set @start=@iter+1
                end
            set @iter = @iter + 1
        end

    if @start = 1
        set @strresult = @strresult + substring(@symbol,1,@iter)
	else
        set @strresult = @strresult + isnull(replicate('0',6-(@iter-@start)),'') + substring(@symbol,@start,@iter-@start)

    return isnull(@strresult,@symbol)
end

go

------------------------------------------------------------------------
if exists (select * from sysobjects where name='view_doksp_sum_by_prod')
	drop view  view_doksp_sum_by_prod
go

create view view_doksp_sum_by_prod as
select 
'iddoksp'=t_sprz.p_idobj,
'ilosc'=sum(t_sprz.c_curiloscopak - isnull(t_orgsprz.c_curiloscopak,0)),
'idprod'=t_sprz.c_pprodukt 
from vlist_n5sprzedaz_listpozycje t_sprz
left outer join vlist_n5sprzedaz_listpozycje t_orgsprz on t_sprz.p_ppopsprzed = t_orgsprz.p_idobj and t_sprz.coll_lp = t_orgsprz.coll_lp
join n5produkt on t_sprz.c_pprodukt = n5produkt.idobj where n5produkt.erodzaj=1
group by t_sprz.p_idobj,t_sprz.c_pprodukt

go

if exists (select * from sysobjects where name='view_doksp_sum_magic')
	drop view  view_doksp_sum_magic
go

create view view_doksp_sum_magic as 
select iddoksp,'magic'=sum(ilosc + cast (idprod as decimal(14,4)) * 1000000) from view_doksp_sum_by_prod
where ilosc <> 0.0
group by iddoksp

go

if exists (select * from sysobjects where name='view_dokmag_sum_by_prod_sp')
	drop view  view_dokmag_sum_by_prod_sp
go

---- ntypdok=19 -> WZ
---- 10129 -> TYPEID_N5SPRZEDAZ

create view view_dokmag_sum_by_prod_sp as 
select 'iddoksp'=p_wrefdokhandl,'ilosc'=sum(case when p_ntypdok=19 then c_curiloscopak else -c_curiloscopak end),'idprod'=c_pprodukt from vlist_n5dokmag_listpozycje
where p_wrefdokhandl_wrt=10129
group by p_wrefdokhandl,c_pprodukt

go

if exists (select * from sysobjects where name='view_dokmag_sum_magic')
	drop view  view_dokmag_sum_magic
go

create view view_dokmag_sum_magic as 
select iddoksp,'magic'=sum(ilosc + cast (idprod as decimal(14,4)) * 1000000) from view_dokmag_sum_by_prod_sp
where ilosc <> 0.0
group by iddoksp

go

----

if exists (select * from sysobjects where name='view_dokzak_sum_by_prod')
	drop view  view_dokzak_sum_by_prod
go

create view view_dokzak_sum_by_prod as
select 
'iddoksp'=t_zakup.p_idobj,
'ilosc'=sum(t_zakup.c_curiloscopak - isnull(t_orgzakup.c_curiloscopak,0)),
'idprod'=t_zakup.c_pprodukt 
from vlist_n5zakup_listPozycje t_zakup
left outer join vlist_n5zakup_listPozycje t_orgzakup on t_zakup.p_ppopzakup = t_orgzakup.p_idobj and t_zakup.coll_lp = t_orgzakup.coll_lp
join n5produkt on t_zakup.c_pprodukt = n5produkt.idobj where n5produkt.erodzaj=1
group by t_zakup.p_idobj,t_zakup.c_pprodukt

go

if exists (select * from sysobjects where name='view_dokzak_sum_magic')
	drop view  view_dokzak_sum_magic
go

create view view_dokzak_sum_magic as 
select iddoksp,'magic'=sum(ilosc + cast (idprod as decimal(14,4)) * 1000000) from view_dokzak_sum_by_prod
where ilosc <> 0.0
group by iddoksp

go

if exists (select * from sysobjects where name='view_dokmag_sum_by_prod_zak')
	drop view  view_dokmag_sum_by_prod_zak
go

---- ntypdok=18 -> PZ
---- 10176 -> TYPEID_N5ZAKUP

create view view_dokmag_sum_by_prod_zak as 
select 'iddoksp'=p_wrefdokhandl,'ilosc'=sum(case when p_ntypdok=18 then c_curiloscopak else -c_curiloscopak end),'idprod'=c_pprodukt from vlist_n5dokmag_listpozycje
where p_wrefdokhandl_wrt=10176
group by p_wrefdokhandl,c_pprodukt

go

if exists (select * from sysobjects where name='view_dokmag_sum_magic2')
	drop view view_dokmag_sum_magic2
go

create view view_dokmag_sum_magic2 as 
select iddoksp,'magic'=sum(ilosc + cast (idprod as decimal(14,4)) * 1000000) from view_dokmag_sum_by_prod_zak
where ilosc <> 0.0
group by iddoksp

go

--------------------------------------------------------
-- DB7
--------------------------------------------------------

if exists (select * from sysobjects where name='view_lastzakup')
	drop view  view_lastzakup
go


create view view_lastzakup as 
select 'vlz_pProd'=vprod.p_idobj,'vlz_pOpak'=vprod.c_idobj,'vlz_ddatazakupu'=max(isnull(vzak.p_ddatazakupu, {d '1899-12-31'} ))
from vlist_n5zakup_listPozycje vzak 
right outer join vlist_n5produkt_listOpakowania vprod 
on vzak.c_pProdukt = vprod.p_idobj and vzak.c_pOpak = vprod.c_idobj
group by vprod.p_idobj,vprod.c_idobj
go

--------------------------------------------------------

----------- DB 9 ---------------------
if exists (select * from sysobjects where name='nx_date2str')
	drop function nx_date2str
go

create function dbo.nx_date2str(@dDate datetime)
returns varchar(10)
with encryption
as
begin
declare @strDate varchar(10)
set @strDate = ltrim(str(datepart(yy,@dDate))) + '-' + right('0' + ltrim(str(datepart(mm,@dDate))),2) 
+ '-' + right('0' + ltrim(str(datepart(dd,@dDate))),2)
return @strDate
end
go

--------------------------------------------------------
if exists (select * from sysobjects where name='nx_dec2str')
	drop function nx_dec2str
go

create function dbo.nx_dec2str(@curValue decimal(14,4),@iPrec integer)
returns varchar(20)
with encryption
as
begin
declare @strValue varchar(20)
set @strValue = ltrim(replace(str(@curValue,14,@iPrec),'.',','))
return @strValue
end
go
--------------------------------------------------------

create index CUST24 on n5pozrecepta(pProdukt,pOpak,IdObj)
go
